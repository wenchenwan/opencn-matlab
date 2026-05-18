# 六轴机器人时间最优轨迹规划：离散化 + 关节空间 TOPP 方案

---

## 目录

1. [方案总体架构](#一方案总体架构)
2. [笛卡尔路径的自适应离散化](#二笛卡尔路径的自适应离散化)
3. [离散点处的关节空间导数计算](#三离散点处的关节空间导数计算)
4. [分段关节空间路径参数化](#四分段关节空间路径参数化)
5. [关节空间时间最优规划（LP 框架）](#五关节空间时间最优规划lp-框架)
6. [实现架构](#六实现架构)
7. [数值考虑](#七数值考虑)
8. [关键公式汇总](#八关键公式汇总)

> **本次更新新增内容**：
> - §2.5：路径段间 G2 连续平滑（角点混合方案）
> - §5.5：滑动窗口 MPC 策略（复用 OpenCN 窗口框架）
> - §5.6：跨窗口边界连续性约束（速度平方 + 切向加速度传递）
> - 原 §5.5、§5.6 顺延为 §5.7、§5.8

---

## 一、方案总体架构

### 1.1 核心思路

本方案将问题分为**两个完全解耦的阶段**：

- **几何阶段**（离线预处理）：在笛卡尔空间做路径离散化和运动学变换，输出关节空间路径的离散描述（位置 + 各阶导数）
- **动力学阶段**（时间最优规划）：在关节空间中用 LP 求解时间最优速度剖面，所有运动学信息已预先编码进约束矩阵，无需在 LP 内循环调用 IK 或 Jacobian

这种解耦带来两个核心优势：
1. LP 内部完全在关节空间操作，无矩阵求逆，无奇异性问题
2. 离散化密度可根据路径几何自适应调整，平坦段用稀疏采样，弯曲/快速旋转段用密集采样

### 1.2 处理流程

```
┌────────────────────────────────────────────────────────────────────┐
│  输入：笛卡尔空间路径  r(s) = [p(s); φ(s)]                          │
│         p(s) ∈ R³（位置），φ(s) ∈ R³（ZYX 欧拉角）                  │
└──────────────────────┬─────────────────────────────────────────────┘
                       │
           ┌───────────▼────────────┐
           │  阶段一：自适应离散化   │   § 二
           │  位置曲率 + 姿态曲率   │
           │  → M 个采样点 {u_m}    │
           └───────────┬────────────┘
                       │
           ┌───────────▼────────────┐
           │  阶段二：运动学变换    │   § 三
           │  每点 IK + J 链式法则  │
           │  → q_m, q'_m, q''_m,  │
           │    q'''_m              │
           └───────────┬────────────┘
                       │
           ┌───────────▼────────────┐
           │  阶段三：分段参数化    │   § 四
           │  五次 Hermite 插值     │
           │  → 每段连续的 q(u)     │
           └───────────┬────────────┘
                       │
           ┌───────────▼────────────┐
           │  阶段四：LP 时间最优   │   § 五
           │  决策变量：ud²(u)      │
           │  关节速度/加速度/Jerk  │
           │  约束（全关节空间）    │
           └───────────┬────────────┘
                       │
           ┌───────────▼────────────┐
           │  阶段五：轨迹合成      │
           │  积分 dt = du/ud       │
           │  → q(t), qd(t), qdd(t)│
           └────────────────────────┘
```

### 1.3 符号约定

| 符号 | 含义 | 维度 |
|---|---|---|
| $s$ | 笛卡尔路径弧长参数 | 标量 |
| $u \in [0,1]$ | 每段归一化参数 | 标量 |
| $\mathbf{r}(s) = [\mathbf{p}(s);\,\boldsymbol{\varphi}(s)]$ | 笛卡尔位姿 | $6\times1$ |
| $\mathbf{q}(u)$ | 关节角 | $6\times1$ |
| $\mathbf{J}(\mathbf{q})$ | 几何 Jacobian | $6\times6$ |
| $\dot{u} = du/dt$ | 参数速度 | 标量 |
| $\dot{u}^2$ | **LP 决策变量**（参数速度平方） | 标量 |
| $M$ | 总采样点数 | 整数 |
| $K$ | 总段数（$= M - 1$） | 整数 |
| $N$ | 每段 B 样条基函数数 | 整数 |

---

## 二、笛卡尔路径的自适应离散化

### 2.1 位置曲率

对参数 $t$（可以是弧长 $s$ 或任意单调参数）下的位置路径 $\mathbf{p}(t)$，位置曲率定义为：

$$
\kappa_\text{pos}(t) = \frac{\|\mathbf{p}'(t) \times \mathbf{p}''(t)\|}{\|\mathbf{p}'(t)\|^3}
$$

直线段 $\kappa_\text{pos} = 0$，半径为 $R$ 的圆弧 $\kappa_\text{pos} = 1/R$。

弦误差（离散步长 $\Delta s$ 下，离散直线与真实路径的最大偏差）：

$$
\delta_\text{chord}(t) \approx \frac{\kappa_\text{pos}(t)}{8} \cdot \Delta s^2
$$

给定位置弦误差容差 $\varepsilon_\text{pos}$，对应的最大步长：

$$
\Delta s_\text{pos}(t) = \sqrt{\frac{8\,\varepsilon_\text{pos}}{\kappa_\text{pos}(t) + \epsilon}}
$$

### 2.2 姿态曲率

姿态路径 $\boldsymbol{\varphi}(t) = [\alpha(t),\,\beta(t),\,\gamma(t)]^\top$（ZYX 欧拉角）的角速度方向向量：

$$
\boldsymbol{\omega}(t) = \mathbf{E}(\beta, \gamma)\,\boldsymbol{\varphi}'(t)
$$

其中 $\mathbf{E}$ 是欧拉角到角速度的变换矩阵（对 ZYX 约定）：

$$
\mathbf{E}(\beta, \gamma) = \begin{bmatrix}
\cos\beta\cos\gamma & -\sin\gamma & 0 \\
\cos\beta\sin\gamma &  \cos\gamma & 0 \\
-\sin\beta          &  0          & 1
\end{bmatrix}
$$

姿态曲率定义为角速度方向向量对路径参数的变化率（类比位置曲率）：

$$
\kappa_\text{ori}(t) = \frac{\|\boldsymbol{\omega}(t) \times \boldsymbol{\omega}'(t)\|}{\|\boldsymbol{\omega}(t)\|^3 + \epsilon}
$$

姿态插值弦误差（角度意义）：

$$
\delta_\text{angle}(t) \approx \frac{\kappa_\text{ori}(t)}{8} \cdot \Delta s^2
$$

给定角度误差容差 $\varepsilon_\text{ori}$（rad），对应最大步长：

$$
\Delta s_\text{ori}(t) = \sqrt{\frac{8\,\varepsilon_\text{ori}}{\kappa_\text{ori}(t) + \epsilon}}
$$

### 2.3 综合曲率与自适应步长

综合位置和姿态的采样约束，在每个当前点 $t_m$ 处的自适应步长：

$$
\boxed{\Delta s_m = \min\!\left(\Delta s_\text{max},\;\Delta s_\text{pos}(t_m),\;\Delta s_\text{ori}(t_m)\right)}
$$

其中 $\Delta s_\text{max}$ 是上限（保证密集段不过稀疏）。

**自适应采样算法**：

```
输入：路径 r(t)，容差 ε_pos、ε_ori，最大步长 Δs_max，最小步长 Δs_min

t₀ = 0，SampleList = {t₀}
while t_current < t_end:
    κ_pos = position_curvature(r, t_current)
    κ_ori = orientation_curvature(r, t_current)

    Δs_pos = sqrt(8·ε_pos / (κ_pos + ε))
    Δs_ori = sqrt(8·ε_ori / (κ_ori + ε))
    Δs     = clamp(min(Δs_pos, Δs_ori), Δs_min, Δs_max)

    t_next = t_current + Δs / ||r'(t_current)||    # 弧长步进
    SampleList.append(t_next)
    t_current = t_next

输出：M 个采样参数值 {t_m}，对应位姿 {r(t_m)}
```

### 2.4 路径导数的计算方式

各阶笛卡尔路径导数 $\mathbf{r}'(t_m)$、$\mathbf{r}''(t_m)$、$\mathbf{r}'''(t_m)$ 的获取方式取决于路径表示：

| 路径类型 | 导数来源 |
|---|---|
| 解析直线/圆弧 | 封闭公式（精确） |
| B 样条/Bézier 曲线 | 递推导数公式（精确） |
| G-code 折线 | 有限差分（近似，需平滑处理） |
| 测量/示教点云 | 三次样条拟合后求导（近似） |

### 2.5 路径段间 G2 连续平滑

输入路径往往由多段基元拼接（直线 → 圆弧 → 直线），各段交接处可能仅有 G0（位置连续）或 G1（切线方向连续），G2（曲率连续）不满足。G2 间断的后果：
- 笛卡尔路径在交接点处存在曲率跳变 → $\mathbf{r}''(t_j^-)  \neq \mathbf{r}''(t_j^+)$
- 由链式法则（§三）计算的 $\mathbf{q}''_m$ 在交接点两侧跳变
- LP 被迫在交接点附近强制降速，无法实现真正时间最优

#### 2.5.1 G2 连续的几何含义

对于弧长参数化路径 $\mathbf{r}(s)$，G2 连续要求曲率向量在交接点 $s_j$ 处匹配：

$$
\mathbf{r}''(s_j^-) = \mathbf{r}''(s_j^+)
$$

G0（位置）和 G1（切线方向）是 G2 的必要前提，五次 Hermite 混合可同时满足这三个条件。

#### 2.5.2 五次 Hermite 混合平滑

在每个路径交接点 $s_j$ 附近引入一段**混合区间** $[s_j - \delta_j,\; s_j + \delta_j]$，用五次 Hermite 曲线代替原始角点。

**混合端点的信息**（从原始路径各自段评估）：

$$
\text{左端：}\; \mathbf{r}_L = \mathbf{r}(s_j - \delta_j),\; \mathbf{r}'_L,\; \mathbf{r}''_L \quad\text{（来自左侧路径段）}
$$

$$
\text{右端：}\; \mathbf{r}_R = \mathbf{r}(s_j + \delta_j),\; \mathbf{r}'_R,\; \mathbf{r}''_R \quad\text{（来自右侧路径段）}
$$

混合曲线（复用 §四 的五次 Hermite 基函数）：

$$
\mathbf{r}_\text{blend}(\xi) = H_{00}\,\mathbf{r}_L + H_{10}\,\delta_j\mathbf{r}'_L + H_{20}\,\delta_j^2\mathbf{r}''_L
+ H_{01}\,\mathbf{r}_R + H_{11}\,\delta_j\mathbf{r}'_R + H_{21}\,\delta_j^2\mathbf{r}''_R,\quad \xi\in[0,1]
$$

该曲线在 $\xi=0$ 和 $\xi=1$ 处自动满足 C2（即 G2）连续。

#### 2.5.3 混合长度 $\delta_j$ 的选择

$$
\boxed{\delta_j = \min\!\left(\delta_\text{max},\; \frac{l_{\text{adj},j}}{2},\; \sqrt{\frac{\varepsilon_\text{blend}}{\kappa_\text{corner}}}\right)}
$$

| 参数 | 含义 |
|---|---|
| $l_{\text{adj},j}$ | 交接点两侧相邻段的最短弧长（防止相邻混合区重叠） |
| $\varepsilon_\text{blend}$ | 允许的路径偏离容差（通常与 $\varepsilon_\text{pos}$ 同量级） |
| $\kappa_\text{corner}$ | 交接点处名义曲率，可用角点半角 $\theta_j$ 估计：$\kappa_\text{corner} \approx 2\sin(\theta_j/2)/\delta_j$ |

典型工程取值：机器人加工路径 $\delta_j = 0.5\,\text{mm}\sim5\,\text{mm}$，大臂展机器人可放宽至 $10\,\text{mm}$。

#### 2.5.4 姿态路径的 G2 平滑

欧拉角路径 $\boldsymbol{\varphi}(s)$ 在交接点处同样适用相同的五次 Hermite 混合策略，混合量为角度（rad）。对于位姿联合路径 $\mathbf{r}(s) = [\mathbf{p}(s);\,\boldsymbol{\varphi}(s)]$，位置和姿态分别独立混合，混合长度取两者约束的最小值：

$$
\delta_j = \min\!\left(\delta_j^\text{pos},\; \delta_j^\text{ori}\right)
$$

#### 2.5.5 与自适应离散化的集成

G2 混合完成后，混合区内曲率仍高于两侧平坦段，自适应离散化（§2.1~2.3）会在混合区内自动加密采样，无需额外处理。

完整预处理流程：

```
原始分段路径（G0/G1 连续）
     ↓ §2.5  G2 混合平滑（角点 → 光滑混合段）
G2 连续路径
     ↓ §2.1~2.3  自适应离散化（曲率驱动步长）
M 个采样点 {t_m}（混合区内自动加密）
     ↓ §三  关节空间导数计算（q', q'', q''' 精确）
```

---

## 三、离散点处的关节空间导数计算

### 3.1 逆运动学（IK）

在每个采样点 $t_m$，由笛卡尔位姿求关节角（**连续解选择**是关键）：

$$
\mathbf{q}_m = \text{IK}(\mathbf{r}(t_m))
$$

连续解选择策略（按优先级）：
1. **最近解**：从所有候选 IK 解中选 $\|\mathbf{q} - \mathbf{q}_{m-1}\|$ 最小者
2. **构型一致**：保持 elbow_up/down 不变（除非关节限位迫使切换）
3. **关节限位合法**：排除违反 $\mathbf{q}_\text{lim}$ 的解

### 3.2 一阶导数（关节速度方向）

利用正向 Jacobian 和链式法则：

$$
\frac{d\mathbf{q}}{dt} = \mathbf{J}^{-1}(\mathbf{q}_m) \cdot \frac{d\mathbf{r}}{dt} = \mathbf{J}^{-1}(\mathbf{q}_m) \cdot \mathbf{r}'(t_m)
$$

定义对路径参数 $u$（归一化后）的一阶导数：

$$
\boxed{\mathbf{q}'_m \triangleq \frac{d\mathbf{q}}{du}\bigg|_{t_m} = \mathbf{J}^{-1}(\mathbf{q}_m) \cdot \mathbf{r}'(t_m)}
$$

### 3.3 二阶导数（关节加速度方向）

对 $\dot{\mathbf{q}} = \mathbf{J}^{-1}\mathbf{r}'\dot{u}$ 对 $u$ 再求导（乘积法则）：

$$
\frac{d^2\mathbf{q}}{du^2} = \mathbf{J}^{-1} \cdot \mathbf{r}''(t_m) + \frac{d\mathbf{J}^{-1}}{du} \cdot \mathbf{r}'(t_m)
$$

利用 $\dfrac{d\mathbf{J}^{-1}}{du} = -\mathbf{J}^{-1} \dfrac{d\mathbf{J}}{du} \mathbf{J}^{-1}$，展开后：

$$
\boxed{\mathbf{q}''_m = \mathbf{J}^{-1}_m \cdot \mathbf{r}''(t_m) - \mathbf{J}^{-1}_m \cdot \frac{d\mathbf{J}}{du}\bigg|_{t_m} \cdot \mathbf{q}'_m}
$$

其中 $\dfrac{d\mathbf{J}}{du}\bigg|_{t_m}$ 用数值差分近似：

$$
\frac{d\mathbf{J}}{du}\bigg|_{t_m} \approx \frac{\mathbf{J}(\mathbf{q}_m + \varepsilon\,\mathbf{q}'_m) - \mathbf{J}(\mathbf{q}_m)}{\varepsilon}, \quad \varepsilon = 10^{-7}
$$

### 3.4 三阶导数（关节 Jerk 方向，精确版）

继续对 $\mathbf{q}''(u)$ 求导（完整展开，无近似）：

$$
\mathbf{q}'''_m = \mathbf{J}^{-1}_m \cdot \mathbf{r}'''(t_m)
- \mathbf{J}^{-1}_m \cdot \frac{d\mathbf{J}}{du}\bigg|_{t_m} \cdot \mathbf{q}''_m
- \mathbf{J}^{-1}_m \cdot \frac{d^2\mathbf{J}}{du^2}\bigg|_{t_m} \cdot \mathbf{q}'_m
$$

其中 Jacobian 二阶数值导数：

$$
\frac{d^2\mathbf{J}}{du^2}\bigg|_{t_m} \approx \frac{\mathbf{J}(\mathbf{q}_m + \varepsilon\mathbf{q}'_m) - 2\mathbf{J}(\mathbf{q}_m) + \mathbf{J}(\mathbf{q}_m - \varepsilon\mathbf{q}'_m)}{\varepsilon^2}
$$

> **与全笛卡尔方案的区别**：全笛卡尔方案在 LP 内部每个 B 样条离散点都做一次 IK + Jacobian 计算（总计 $M \times N_w$ 次）。本方案**仅在采样点处做一次**，LP 内部直接使用预计算的多项式系数，计算量降低一到两个数量级。

### 3.5 奇异点处的处理

当 $\mathrm{rcond}(\mathbf{J}_m) < 10^{-6}$ 时，切换为阻尼最小二乘逆（DLS）：

$$
\mathbf{J}^{-1}_\text{dls} = \mathbf{J}^\top \left(\mathbf{J}\mathbf{J}^\top + \lambda^2\mathbf{I}\right)^{-1}, \quad \lambda = 0.05 \; \text{rad/s}
$$

DLS 在采样阶段使用时，建议适当**加密奇异点附近的采样**（$\Delta s_\text{min}$ 局部收紧），确保奇异区域的 LP 约束足够精细。

采样点处奇异检测与处理流程：

```
if rcond(J_m) < 1e-6:
    # 标记奇异区间
    singularity_flag[m] = true
    J_inv_m = DLS_inv(J_m, λ=0.05)
    # 局部加密：在 [t_{m-1}, t_m] 内补充采样点
    refine_local(t_{m-1}, t_m, factor=4)
else:
    J_inv_m = J_m \ I   # 标准逆
```

---

## 四、分段关节空间路径参数化

### 4.1 参数归一化

将相邻两个采样点 $t_m$ 和 $t_{m+1}$ 之间的弧长记为 $h_m = s_{m+1} - s_m$（沿路径弧长），定义局部归一化参数 $\xi \in [0,1]$：

$$
\xi = \frac{u - u_m}{h_m}, \quad u_m = s_m / s_\text{total}
$$

每段独立地将 LP 决策变量 $\dot{u}^2(\xi)$ 用 B 样条展开。

### 4.2 五次 Hermite 插值（推荐）

利用两个端点处的位置、一阶、二阶导数（共 $2 \times 3 = 6$ 个条件），构造五次 Hermite 多项式：

$$
\mathbf{q}^{(k)}(\xi) = \sum_{j=0}^{5} \mathbf{c}^{(k)}_j \, \xi^j
$$

基函数（Hermite 基）：

$$
H_{00}(\xi) = 1 - 10\xi^3 + 15\xi^4 - 6\xi^5 \quad \text{（左端位置）}
$$

$$
H_{10}(\xi) = \xi - 6\xi^3 + 8\xi^4 - 3\xi^5 \quad \text{（左端一阶导×}h_m\text{）}
$$

$$
H_{20}(\xi) = \tfrac{1}{2}\xi^2 - \tfrac{3}{2}\xi^3 + \tfrac{3}{2}\xi^4 - \tfrac{1}{2}\xi^5 \quad \text{（左端二阶导×}h_m^2\text{）}
$$

$$
H_{01}(\xi) = 10\xi^3 - 15\xi^4 + 6\xi^5, \quad
H_{11}(\xi) = -4\xi^3 + 7\xi^4 - 3\xi^5, \quad
H_{21}(\xi) = \tfrac{1}{2}\xi^3 - \xi^4 + \tfrac{1}{2}\xi^5
$$

插值公式：

$$
\mathbf{q}^{(k)}(\xi) = H_{00}\,\mathbf{q}_m + H_{10}\,h_m\mathbf{q}'_m + H_{20}\,h_m^2\mathbf{q}''_m
+ H_{01}\,\mathbf{q}_{m+1} + H_{11}\,h_m\mathbf{q}'_{m+1} + H_{21}\,h_m^2\mathbf{q}''_{m+1}
$$

段内各阶导数（对 $\xi$ 求导，再乘以 $1/h_m^n$ 转换为对 $u$ 的导数）：

$$
\frac{d\mathbf{q}}{d\xi} = H'_{00}\,\mathbf{q}_m + H'_{10}\,h_m\mathbf{q}'_m + H'_{20}\,h_m^2\mathbf{q}''_m
+ H'_{01}\,\mathbf{q}_{m+1} + H'_{11}\,h_m\mathbf{q}'_{m+1} + H'_{21}\,h_m^2\mathbf{q}''_{m+1}
$$

**保证性质**：
- $C^2$ 连续（端点处位置、一阶、二阶导数精确匹配）
- 段内单调性（在合理步长下，关节角不会在段内出现非物理振荡）

### 4.3 段内任意点的导数估值

在 LP 离散化参数 $\xi_p \in [0,1]$（$p = 1, \ldots, M_\text{LP}$）处，由五次 Hermite 公式直接计算：

$$
\mathbf{q}'(\xi_p) = \frac{1}{h_m} \frac{d\mathbf{q}}{d\xi}\bigg|_{\xi_p}
$$

$$
\mathbf{q}''(\xi_p) = \frac{1}{h_m^2} \frac{d^2\mathbf{q}}{d\xi^2}\bigg|_{\xi_p}
$$

$$
\mathbf{q}'''(\xi_p) = \frac{1}{h_m^3} \frac{d^3\mathbf{q}}{d\xi^3}\bigg|_{\xi_p}
$$

这些值作为 LP 约束矩阵的系数，**全部在预处理阶段计算**，LP 求解时仅做矩阵乘法。

### 4.4 三次 Hermite 的备选方案

若需要减少预处理计算量（仅用 $\mathbf{q}_m$、$\mathbf{q}'_m$，不计算 $\mathbf{q}''_m$），可使用三次 Hermite：

$$
\mathbf{q}^{(k)}(\xi) = H_{00}^\text{3rd}\,\mathbf{q}_m + H_{10}^\text{3rd}\,h_m\mathbf{q}'_m
+ H_{01}^\text{3rd}\,\mathbf{q}_{m+1} + H_{11}^\text{3rd}\,h_m\mathbf{q}'_{m+1}
$$

代价：段内 $\mathbf{q}''$ 不连续（$C^1$ 连续而非 $C^2$），加速度约束精度下降，需要更密集的采样来补偿。

---

## 五、关节空间时间最优规划（LP 框架）

### 5.1 决策变量

每段 $k$（对应采样区间 $[t_m, t_{m+1}]$）的决策变量为 B 样条系数向量：

$$
\mathbf{x}_k \in \mathbb{R}^N, \quad \dot{u}^2(\xi) = \mathbf{B}(\xi)\,\mathbf{x}_k
$$

全局决策变量：$\mathbf{x} \in \mathbb{R}^{N \times K}$（$K$ = 总段数）。

目标函数（最小化总时间 $\approx$ 最大化参数速度积分）：

$$
\min_{\mathbf{x}} \;\; -\sum_{k=1}^{K} \mathbf{b}_\text{intgr}^\top \mathbf{D}_k \, \mathbf{x}_k, \quad \mathbf{x}_k \geq 0
$$

其中 $\mathbf{b}_\text{intgr}$ 是 B 样条基函数的积分向量，$\mathbf{D}_k = \mathrm{diag}(1/h_k^2)$ 是弧长归一化缩放矩阵。

### 5.2 关节速度约束

在段 $k$ 的第 $p$ 个 LP 离散点 $\xi_p$ 处，对关节 $i$：

$$
|\dot{q}_i| = |q'_i(\xi_p)| \cdot \dot{u} \leq \dot{q}_{i,\max}
$$

等价 LP 不等式：

$$
q'_i(\xi_p)^2 \cdot \mathbf{B}(\xi_p)\,\mathbf{x}_k \leq \dot{q}_{i,\max}^2
$$

所有关节的速度约束合并：

$$
\mathbf{A}_v^{(k,p)} = \mathrm{diag}\!\left(q'_1(\xi_p)^2, \ldots, q'_6(\xi_p)^2\right) \otimes \mathbf{B}(\xi_p)
\in \mathbb{R}^{6 \times N}
$$

有效速度上限（取所有关节最紧约束）：

$$
\dot{u}^2_\text{max}(\xi_p) = \min_{i=1}^{6} \frac{\dot{q}_{i,\max}^2}{q'_i(\xi_p)^2}
$$

### 5.3 关节加速度约束

#### 关键推导：$\ddot{u}$ 的精确表达式

令 LP 决策变量为 $w(u) \triangleq \dot{u}^2$（参数速度平方），则：

$$
\frac{dw}{du} = \frac{d(\dot{u}^2)/dt}{du/dt} = \frac{2\dot{u}\ddot{u}}{\dot{u}} = 2\ddot{u}
$$

$$
\boxed{\ddot{u} = \frac{1}{2}w'(u) = \frac{1}{2}\mathbf{B}'(u)\,\mathbf{x}} \quad\text{（精确等式）}
$$

由于 $w = \mathbf{B}\mathbf{x}$ 和 $w' = \mathbf{B}'\mathbf{x}$ 均是 $\mathbf{x}$ 的线性函数，加速度对决策变量**天然线性**，无需任何近似。

#### 精确加速度约束

关节加速度展开，代入 $\dot{u}^2 = w = \mathbf{B}\mathbf{x}$ 和 $\ddot{u} = \frac{1}{2}w' = \frac{1}{2}\mathbf{B}'\mathbf{x}$：

$$
\ddot{q}_i = q''_i(\xi_p)\cdot\mathbf{B}(\xi_p)\,\mathbf{x}_k + q'_i(\xi_p)\cdot\frac{1}{2}\mathbf{B}'(\xi_p)\,\mathbf{x}_k
= \underbrace{\left[q''_i(\xi_p)\,\mathbf{B}(\xi_p) + \frac{1}{2}q'_i(\xi_p)\,\mathbf{B}'(\xi_p)\right]}_{\text{Acc}_i(p,:)}\mathbf{x}_k
\quad\text{（精确）}
$$

> 对应 OpenCN `buildConstr.m` 中的加速度行（注释中"$\approx$"实为**精确等式**）：
> `Acc_j = r''_j·BasisVal + 0.5·r'_j·BasisValD`

LP 不等式（上/下限）：

$$
\pm\,\text{Acc}_i(p,:)\,\mathbf{x}_k \leq \ddot{q}_{i,\max}
$$

所有关节、所有段的加速度约束组成块对角矩阵 $\mathbf{A}_a$（$6 \times 2$ 行 × $M_\text{LP}$ 点 × $K$ 段）。

### 5.4 关节 Jerk 约束（第二阶 LP）

#### Jerk 精确展开

对加速度 $\ddot{q}_i = q''_i w + \frac{1}{2}q'_i w'$ 再对 $t$ 求导，利用 $\dddot{u} = \frac{1}{2}w''\dot{u}$：

$$
\dddot{q}_i = \frac{d\ddot{q}_i}{dt}
= \dot{u}\left[q'''_i(\xi_p)\,w + \frac{3}{2}q''_i(\xi_p)\,w' + \frac{1}{2}q'_i(\xi_p)\,w''\right]
= \sqrt{w}\left[q'''_i w + \frac{3}{2}q''_i w' + \frac{1}{2}q'_i w''\right]
$$

其中 $w = \mathbf{B}\mathbf{x}$，$w' = \mathbf{B}'\mathbf{x}$，$w'' = \mathbf{B}''\mathbf{x}$，而 $\sqrt{w} = \dot{u}$ 是非线性项——这使得 Jerk 对 $\mathbf{x}$ **非线性**（$O(w^{3/2})$ 项）。

各阶关系汇总（$w = \dot{u}^2$，$'$ 表示对 $u$ 求导）：

$$
\begin{aligned}
\dot{u}  &= \sqrt{w}, &\quad \dot{u}^2  &= w, &\quad \dot{u}^3 &= w\sqrt{w} \\[4pt]
\ddot{u} &= \tfrac{1}{2}w', &\quad \dddot{u} &= \tfrac{1}{2}w''\sqrt{w}, &\quad \dot{u}\cdot\ddot{u} &= \tfrac{1}{2}w'\sqrt{w}
\end{aligned}
$$

#### 两阶段 LP：线性化 Jerk

加速度约束是精确线性的（第一阶 LP 直接求解），求得 $\mathbf{x}^*$ 后以 $\dot{u}_\text{ref}(\xi_p) = \sqrt{\mathbf{B}(\xi_p)\mathbf{x}^*}$ 为参考，冻结 $\sqrt{w} \approx \dot{u}_\text{ref}$（常数标量），Jerk 变为对 $\mathbf{x}$ 线性：

$$
\dddot{q}_i \approx \dot{u}_\text{ref}(\xi_p)\left[q'''_i(\xi_p)\,\mathbf{B}(\xi_p) + \frac{3}{2}q''_i(\xi_p)\,\mathbf{B}'(\xi_p) + \frac{1}{2}q'_i(\xi_p)\,\mathbf{B}''(\xi_p)\right]\mathbf{x}_k
$$

LP 约束行（第二阶 LP）：

$$
\boxed{\text{Jerk}_i(p,:) = \dot{u}_\text{ref}(\xi_p)\left[q'''_i(\xi_p)\,\mathbf{B}(\xi_p) + \frac{3}{2}q''_i(\xi_p)\,\mathbf{B}'(\xi_p) + \frac{1}{2}q'_i(\xi_p)\,\mathbf{B}''(\xi_p)\right]}
$$

$$
\pm\,\text{Jerk}_i(p,:)\,\mathbf{x}_k \leq j_{i,\max}
$$

**与加速度约束的本质区别**：

| | 是否线性于 $\mathbf{x}$ | 原因 |
|---|---|---|
| **加速度** | 精确线性 | $\ddot{u} = \frac{1}{2}w'$，$w'$ 是 $\mathbf{x}$ 的线性函数 |
| **Jerk** | 非线性（需线性化） | 含 $\dot{u} = \sqrt{w}$ 因子，对 $\mathbf{x}$ 为 $O(w^{3/2})$ |

**精度优势**：由于 $q'''_i$ 在采样阶段用完整链式法则精确计算（见 §3.4），第一项 $q'''_i \mathbf{B}$ 无截断误差，Jerk 约束精度 $<2\%$（相比全笛卡尔方案的 5~15%）。

### 5.5 滑动窗口 MPC 策略

#### 5.5.1 窗口化动机

将全路径 $K$ 段同时纳入单一 LP，约束矩阵规模为 $O(K \times N)$，对长路径（$K = 500\sim5000$）LP 求解时间不可接受。**滑动窗口 MPC（Model Predictive Control）** 策略：

- 每次仅对 $W$ 段（$W \ll K$）构造并求解 LP
- **仅提交第一段**的 B 样条系数（实际执行）
- 窗口向前滑动一段，重新规划

本方案可直接复用 OpenCN 的 `feedratePlanningGetwindow.m` + `FeedratePlanning_LP.m` 滑动窗口框架。

#### 5.5.2 窗口结构

```
全路径（K 段）：[seg1 | seg2 | seg3 | ... | segK]

窗口 1（W=5）：┌─────────────────────────┐
               │ seg1  seg2  seg3  seg4  seg5 │
               └──┬──────────────────────────┘
                  │ 提交 seg1，窗口滑动
窗口 2：       ┌─────────────────────────┐
               │ seg2  seg3  seg4  seg5  seg6 │
               └──┬──────────────────────────┘
                  │ 提交 seg2，窗口滑动
...
窗口 K-W+1：   ┌───────────────────────────┐
               │ seg_{K-W+1} ... seg_K        │  ← 最后窗口
               └──┬────────────────────────────┘
                  │ 提交全部剩余段
```

每个窗口包含 $W$ 段、$W+1$ 个约束节点（含首尾），LP 规模固定为 $O(W)$，不随 $K$ 增长。

#### 5.5.3 窗口大小 $W$ 的选择

$W$ 需满足"前瞻距离 $\geq$ 最大制动距离"，防止 LP 无法提前预见减速段：

$$
\boxed{W \cdot \bar{h} \;\geq\; d_\text{brake} = \frac{v_{\max}^2}{2\,\max_i\{\ddot{q}_{i,\max}\}}}
$$

其中 $\bar{h}$ 为平均段关节空间弧长。示例（UR5：$v_\max = 2$ rad/s，$\ddot{q}_\max = 10$ rad/s²，$\bar{h} = 0.02$ rad）：

$$
d_\text{brake} = \frac{4}{20} = 0.2\;\text{rad} \;\Rightarrow\; W \geq \left\lceil\frac{0.2}{0.02}\right\rceil = 10
$$

建议取 $W = 15\sim30$，留有 $1.5\sim3\times$ 制动距离的余量。

#### 5.5.4 末端零速保守策略（MPC Conservative Stop）

对**中间窗口**（非最后窗口），末端边界强制设为：

$$
v_1 = 0,\quad a_{t,1} = 0 \quad\text{（MPC 保守停止）}
$$

LP 被迫规划在窗口末端减速到零，但**实际仅提交第一段**，下一窗口重新规划后速度连续。整条轨迹**不会真正停止**，窗口边界处的"停止点"随窗口前移而持续前移。

$$
\underbrace{\text{LP 规划：需减速到零}}_{\text{窗口末端约束}}
\xrightarrow{\text{仅提交第一段}}
\underbrace{\text{实际：速度连续过渡}}_{\text{下一窗口重规划}}
$$

对**最后窗口**，末端约束改为实际终端条件（机器人停止在目标点，$v_1 = 0$）。

### 5.6 跨窗口边界连续性约束

#### 5.6.1 连续性约束的三个来源

窗口 $i$ 的 LP 起端边界条件 $(v_0^2,\; a_{t,0})$ 来自三个来源（与 OpenCN `feedratePlanningSetupCurves.m` 的 `ctx.v_0 / ctx.at_0` 一一对应）：

| 场景 | $v_0^2$ | $a_{t,0}$ |
|---|---|---|
| 第一个窗口（全局起点） | $0$（从静止出发） | $0$ |
| 中间窗口（从上一窗口 LP 解提取） | $\mathbf{b}_\text{cont} \cdot \mathbf{x}_k$ | $\dfrac{1}{2}\mathbf{b}'_\text{cont} \cdot \mathbf{x}_k$ |
| LP 失败松弛后重规划 | 从松弛后零速曲线连接点重新计算 | 同上 |

#### 5.6.2 从 LP 解中提取边界条件

设窗口 $i$ 中提交段（段 $k$）的 B 样条系数向量为 $\mathbf{x}_k$，B 样条基函数在段末（$u=1$）的求值行向量为：

$$
\mathbf{b}_\text{cont} = \mathbf{B}(1) \in \mathbb{R}^{1\times N}, \qquad
\mathbf{b}'_\text{cont} = \mathbf{B}'(1) \in \mathbb{R}^{1\times N}
$$

下一窗口（窗口 $i+1$）的起端边界条件：

$$
\boxed{v_0^2[\text{next}] = \mathbf{b}_\text{cont} \cdot \mathbf{x}_k}
$$

$$
\boxed{a_{t,0}[\text{next}] = \frac{1}{2}\,\mathbf{b}'_\text{cont} \cdot \mathbf{x}_k}
$$

因子 $\tfrac{1}{2}$ 来自关系 $a_t = \tfrac{1}{2}\dfrac{d(\dot{u}^2)}{du} = \tfrac{1}{2}\,\mathbf{B}'(u)\mathbf{x}$。

#### 5.6.3 窗口 LP 的完整等式约束矩阵

窗口内 $W$ 段、$W+1$ 个节点，等式约束共 $2(W+1)$ 行：

$$
\mathbf{A}_\text{eq} = \begin{bmatrix}
\mathbf{B}(0)  & \mathbf{0}     & \cdots & \mathbf{0}      \\[2pt]
\mathbf{B}'(0) & \mathbf{0}     & \cdots & \mathbf{0}      \\[4pt]
\mathbf{B}(1)  & -\mathbf{B}(0) & \cdots & \mathbf{0}      \\
\mathbf{B}'(1) & -\mathbf{B}'(0)& \cdots & \mathbf{0}      \\
               & \ddots         & \ddots & \vdots          \\
\mathbf{0}     & \cdots & \mathbf{B}(1)  & -\mathbf{B}(0)  \\
\mathbf{0}     & \cdots & \mathbf{B}'(1) & -\mathbf{B}'(0) \\[4pt]
\mathbf{0}     & \cdots & \mathbf{0}  & \mathbf{B}(1)   \\
\mathbf{0}     & \cdots & \mathbf{0}  & \mathbf{B}'(1)  \\
\end{bmatrix},
\quad
\mathbf{b}_\text{eq} = \begin{bmatrix}
v_0^2           \\
2\,a_{t,0}      \\[4pt]
0 \\ 0          \\
\vdots          \\
0 \\ 0          \\[4pt]
v_1^2           \\
2\,a_{t,1}
\end{bmatrix}
$$

其中 $v_0^2, a_{t,0}$ 由 §5.6.2 从上一窗口提取；$v_1^2 = 0, a_{t,1} = 0$ 为 MPC 保守终端（最后窗口改为实际终端）。

该结构与 OpenCN `buildConstr.m` 完全一致，可直接复用。

#### 5.6.4 跨窗口 C¹ 连续性保证

每次滑动窗口后，下一窗口的起端等式约束精确等于当前提交段末端的 LP 解，因此：

- **速度连续**：$w(u)$ 在提交点处完全匹配（$v^2$ 无跳变）
- **切向加速度连续**：$dw/du$ 在提交点处完全匹配（$a_t$ 无跳变）
- **整条轨迹 $C^1$ 连续**：无论窗口如何滑动，速度和加速度均连续

> 这与 OpenCN `feedratePlanningSetupCurves.m` 中 `zero_start=false` 路径的行为一致：
> `ctx.v_0 = sqrt(continuity * Coeff(:,1))` 即 $\mathbf{b}_\text{cont} \cdot \mathbf{x}_k$ 的平方根，
> `ctx.at_0 = continuity_acc * Coeff(:,1)` 即 $\tfrac{1}{2}\mathbf{b}'_\text{cont} \cdot \mathbf{x}_k$。

### 5.7 窗口内段间 $C^1$ 连续性（等式约束）

§5.6.3 的 $\mathbf{A}_\text{eq}$ 中间行已包含窗口内相邻段间的连续性：相邻段 $k$ 和 $k+1$ 在连接点处要求速度和切向加速度连续：

$$
\begin{cases}
v^2_k(1) = v^2_{k+1}(0) & \Rightarrow\quad \mathbf{B}(1)\,\mathbf{x}_k - \mathbf{B}(0)\,\mathbf{x}_{k+1} = 0 \\[4pt]
a_{t,k}(1) = a_{t,k+1}(0) & \Rightarrow\quad \mathbf{B}'(1)\,\mathbf{x}_k - \mathbf{B}'(0)\,\mathbf{x}_{k+1} = 0
\end{cases}
$$

结合窗口起端（§5.6.2）和末端（MPC 保守停止）边界，完整等式约束已在 §5.6.3 的 $\mathbf{A}_\text{eq}$ 中给出，共 $2(W+1)$ 行：

$$
\underbrace{2}_{\text{起端}} + \underbrace{2(W-1)}_{\text{段间连接}} + \underbrace{2}_{\text{末端}} = 2(W+1) \;\text{行}
$$

### 5.8 约束矩阵维度汇总（每个滑动窗口）

窗口大小 $W$ 段，每段 $M_\text{LP}$ 个离散点，B 样条阶次 $N$：

$$
N_c^\text{ineq} = \underbrace{1}_{\text{速度非负}} + \underbrace{2 \times 6}_{\text{关节速度}} + \underbrace{2 \times 6}_{\text{关节加速度}} = 25\;\text{行/点}
$$

$$
\mathbf{A}_\text{ineq} \in \mathbb{R}^{N_c^\text{ineq} \cdot M_\text{LP} \cdot W \;\times\; N \cdot W},
\quad \mathbf{A}_\text{eq} \in \mathbb{R}^{2(W+1) \;\times\; N \cdot W}
$$

与全局一次规划（$K$ 替换 $W$）相比，矩阵规模缩减 $K/W$ 倍，LP 求解时间显著降低（稀疏矩阵下约降低 $(K/W)^{1.5\sim2.5}$ 倍）。

完整约束矩阵结构（段 $k$，点 $p$）：

$$
\mathbf{A}_{k}(p) = \begin{bmatrix}
-\mathbf{B}(\xi_p) \\[3pt]
q'_1(\xi_p)^2\,\mathbf{B}(\xi_p) \\
\vdots \\
q'_6(\xi_p)^2\,\mathbf{B}(\xi_p) \\[3pt]
+\text{Acc}_1(p,:) \\
\vdots \\
+\text{Acc}_6(p,:) \\[3pt]
-\text{Acc}_1(p,:) \\
\vdots \\
-\text{Acc}_6(p,:)
\end{bmatrix},
\quad
\mathbf{b}_{k}(p) = \begin{bmatrix}
0 \\[3pt]
\dot{q}_{1,\max}^2 \\
\vdots \\
\dot{q}_{6,\max}^2 \\[3pt]
\ddot{q}_{1,\max} \\
\vdots \\
\ddot{q}_{6,\max} \\[3pt]
\ddot{q}_{1,\max} \\
\vdots \\
\ddot{q}_{6,\max}
\end{bmatrix}
$$

---

## 六、实现架构

### 6.1 模块划分

```
robot_topp.m（主入口）
│
├── g2_blend_path.m                  ─── §2.5：G2 路径平滑
│   ├── detect_junctions()           检测分段路径交接点
│   ├── compute_blend_length()       计算混合长度 δ_j
│   └── quintic_hermite_blend()      五次 Hermite 混合曲线
│
├── cartesian_path_sample.m          ─── §2.1~2.4：自适应离散化
│   ├── position_curvature()         位置曲率 κ_pos
│   ├── orientation_curvature()      姿态曲率 κ_ori
│   └── adaptive_sample_path()       曲率驱动自适应步长
│
├── compute_joint_derivatives.m      ─── §三：关节空间导数
│   ├── solve_ik_sequence()          逐点 IK（连续解选择）
│   ├── compute_q1()                 一阶导数（J⁻¹·r'）
│   ├── compute_q2()                 二阶导数（含 dJ/du 项）
│   └── compute_q3()                 三阶导数（含 d²J/du² 项）
│
├── hermite_interpolate.m            ─── §四：分段参数化
│   ├── quintic_hermite_coeffs()     五次 Hermite 系数
│   └── eval_hermite_segment()       段内任意点求值
│
├── build_joint_constr.m             ─── §5.7~5.8：LP 约束构造（每窗口）
│   ├── eval_segment_derivatives()   在 LP 离散点处求 q'/q''/q'''
│   ├── build_vel_constr()           速度约束行
│   ├── build_acc_constr()           加速度约束行（Acc 矩阵）
│   └── build_window_eq()            窗口等式约束（§5.6.3）
│
├── sliding_window_mpc.m             ─── §5.5~5.6：滑动窗口控制
│   ├── get_window()                 获取当前窗口（复用 feedratePlanningGetwindow）
│   ├── extract_boundary()           从提交段提取 v_0², a_t0（§5.6.2）
│   └── advance_window()             窗口滑动 + 边界条件更新
│
└── FeedratePlanning_LP.m            ─── 复用 OpenCN LP 求解器
    ├── compute_scaling_matrix()     决策变量缩放（D = diag(1/h²)）
    ├── c_simplex()                  LP 求解（含 Jerk 两阶段）
    └── resample2file()              轨迹合成输出
```

### 6.2 核心数据结构

**预处理结果结构体**（`JointPathData`）：

```matlab
JointPathData
  .M          : 总采样点数
  .K          : 总段数（= M-1）
  .t_sample   : [1×M] 采样参数值（弧长参数）
  .h          : [1×K] 每段弧长 h_k = t_{m+1} - t_m
  .q          : [6×M] 各采样点关节角
  .dq         : [6×M] 各采样点 dq/du（一阶导数）
  .d2q        : [6×M] 各采样点 d²q/du²（二阶导数）
  .d3q        : [6×M] 各采样点 d³q/du³（三阶导数）
  .singular   : [1×M] 奇异标志（0/1）
  .J_inv      : {M×1 cell} 各采样点的逆 Jacobian（含 DLS）
```

**段约束系数结构体**（`SegConstrData`，每段 $k$）：

```matlab
SegConstrData(k)
  .xi_vec    : [1×M_LP] LP 离散点参数
  .Q1        : [6×M_LP] q'(ξ_p)，各点各关节一阶导数
  .Q2        : [6×M_LP] q''(ξ_p)，各点各关节二阶导数
  .Q3        : [6×M_LP] q'''(ξ_p)，各点各关节三阶导数
  .BVal      : [M_LP×N] B 样条基函数值
  .BValD     : [M_LP×N] B 样条基函数一阶导数
  .BValDD    : [M_LP×N] B 样条基函数二阶导数
  .h_k       : 段弧长
```

### 6.3 主流程代码框架

```matlab
function result = robot_topp(cart_path, robot_params)
%
% 输入：
%   cart_path   : 笛卡尔路径描述（含分段列表、各段 r/r'/r''/r'''）
%   robot_params: 机器人参数（DH, q_lim, vmax, amax, jmax, W, eps_pos, eps_ori）

%% 预处理一：G2 路径平滑（§2.5）
cart_path_g2 = g2_blend_path(cart_path, ...
    robot_params.eps_blend, ...   % 混合容差
    robot_params.delta_max);      % 最大混合长度

%% 预处理二：自适应离散化（§2.1~2.4）
[t_sample, r_sample] = adaptive_sample_path(cart_path_g2, ...
    robot_params.eps_pos, ...
    robot_params.eps_ori, ...
    robot_params.ds_max);
M = length(t_sample);

%% 预处理三：关节空间导数计算（§三，一次性离线）
jpd = compute_joint_derivatives(t_sample, cart_path_g2, robot_params);
% jpd: .q, .dq, .d2q, .d3q, .J_inv, .singular

%% 预处理四：分段 Hermite 参数化（§四）
hermite = build_hermite_segments(jpd);
% hermite(k).coeffs: 每段五次 Hermite 系数

%% 滑动窗口 MPC 循环（§5.5~5.6）
W   = robot_params.W;          % 窗口大小
ctx = init_window_ctx();       % 初始化：v_0=0, a_t0=0

for k = 1 : jpd.K
    % 获取当前窗口 [k, k+W-1]（超出 K 时截断）
    win_segs = get_window(jpd, k, W);

    % 构造窗口 LP 约束矩阵（§5.7~5.8）
    [A, b] = build_joint_constr(hermite, win_segs, ...
        robot_params.vmax, robot_params.amax, BasisVal, BasisValD);

    % 构造等式约束（§5.6.3）：起端由 ctx 提供，末端 MPC 保守停止
    [Aeq, beq] = build_window_eq(ctx, win_segs, BasisVal, BasisValD, ...
        k == jpd.K - W + 1);   % 是否最后窗口

    % LP 求解（两阶段：先速度/加速度，再 Jerk）
    [D, ~] = compute_scaling_matrix_joint(win_segs.h);
    [Coeff, success] = FeedratePlanning_LP(A*D, b, Aeq*D, beq, ...
        robot_params, ctx);

    if ~success
        % LP 失败：松弛末端零速约束，减小 ConstJerk 后重试（复用 OpenCN 策略）
        [Coeff, ctx] = relax_and_retry(ctx, win_segs, robot_params);
    end

    % 提交第一段，提取下一窗口起端边界条件（§5.6.2）
    commit_segment(Coeff(:,1), hermite(k), result);
    ctx = extract_boundary(Coeff(:,1), BasisVal_end, BasisValD_end, ctx);
    % ctx.v_0  = sqrt(B(1) · Coeff(:,1))
    % ctx.at_0 = 0.5 * B'(1) · Coeff(:,1)
end

%% 轨迹合成
result = synthesize_trajectory(result, hermite, jpd, robot_params.dt);

end
```

### 6.4 与 OpenCN 框架的复用关系

| OpenCN 组件 | 复用方式 |
|---|---|
| `c_simplex`（LP 求解器） | 直接复用，接口不变 |
| `compute_scaling_matrix` | 弧长改为关节空间弧长 $h_k$ |
| `resample2file`（重采样） | 直接复用（输出已是关节空间） |
| `buildConstr.m` | **替换**为 `build_joint_constr.m`（结构相同，系数来源不同） |
| `EvalCurvStruct` | **替换**为 `eval_hermite_segment`（从预计算数据取值） |
| `FeedratePlanning_LP` | 直接复用（LP 两阶段策略不变） |
| 滑动窗口 MPC | 直接复用（窗口 = 连续若干段） |

---

## 七、数值考虑

### 7.1 采样点密度与 LP 精度的关系

LP 约束在每段内的 $M_\text{LP}$ 个点处评估约束。若段内关节空间路径变化剧烈（高曲率）而采样点过稀，Hermite 插值误差会导致 LP 约束失准。

**误差传递分析**：

设相邻采样点间距为 $h$，五次 Hermite 插值的截断误差为 $O(h^6)$，导数估计误差：

$$
\|\mathbf{q}'_\text{hermite}(\xi) - \mathbf{q}'_\text{true}(\xi)\|_\infty \leq C_1 h^4
$$

$$
\|\mathbf{q}''_\text{hermite}(\xi) - \mathbf{q}''_\text{true}(\xi)\|_\infty \leq C_2 h^3
$$

LP 约束中速度系数误差 $C_1 h^4$，加速度系数误差 $C_2 h^3$。实践中取 $h$ 使得 $C_2 h^3 < 0.01 \cdot \ddot{q}_\max$（加速度约束误差 $< 1\%$）。

**建议分段步长**（典型 UR5 参数）：

| 路径类型 | 推荐步长 $h$ | 估计采样点数（1m 路径） |
|---|---|---|
| 直线段（低曲率） | 5~10 cm | 10~20 |
| 圆弧（$R = 0.1$ m） | 1~2 cm | 50~100 |
| 高速变姿态段 | 0.5~1 cm | 100~200 |

### 7.2 关节角连续性与构型跳变

IK 在每个采样点独立求解，存在构型跳变风险（例如 elbow_up → elbow_down 突变）。检测方法：

$$
\Delta\mathbf{q}_m = \mathbf{q}_{m+1} - \mathbf{q}_m
$$

若 $\|\Delta\mathbf{q}_m\| > \theta_\text{jump}$（如 $\theta_\text{jump} = 0.5$ rad），判定为构型跳变，需要：
1. 在 $[t_m, t_{m+1}]$ 内重新选择构型（强制 elbow_up/down 约束）
2. 或在跳变处插入零速停顿点，分为两段独立规划

### 7.3 决策变量缩放

每段的等效"弧长"为 $h_k$（两采样点间的弧长），缩放矩阵：

$$
\mathbf{D} = \mathrm{diag}\!\left(\underbrace{\frac{1}{h_1^2}, \ldots, \frac{1}{h_1^2}}_{N \text{ 个}}, \ldots, \underbrace{\frac{1}{h_K^2}, \ldots, \frac{1}{h_K^2}}_{N \text{ 个}}\right)
$$

关节速度约束行在缩放后：

$$
q'_i(\xi_p)^2 \cdot \mathbf{B}(\xi_p)\,\mathbf{D}\,\tilde{\mathbf{x}} \leq \dot{q}_{i,\max}^2
$$

$\mathbf{D}$ 的作用与全笛卡尔方案完全相同（量级统一），可直接复用 `compute_scaling_matrix`。

### 7.4 Jerk 精度对比

由于本方案在采样阶段精确计算 $\mathbf{q}'''$（而非在 LP 内近似），Jerk 约束精度对比：

| 方案 | Jerk 系数来源 | 典型误差 |
|---|---|---|
| 全笛卡尔方案（§二~六） | $\mathbf{J}^{-1}\mathbf{r}'''$ 主项近似 | 5%~15% |
| 本方案（关节空间 TOPP） | 精确 $\mathbf{q}'''$ + 完整展开 | $< 2\%$ |

---

## 八、关键公式汇总

### 8.1 自适应步长

$$
\Delta s_m = \min\!\left(\Delta s_\text{max},\; \sqrt{\frac{8\varepsilon_\text{pos}}{\kappa_\text{pos}(t_m)}},\; \sqrt{\frac{8\varepsilon_\text{ori}}{\kappa_\text{ori}(t_m)}}\right)
$$

### 8.2 关节空间路径导数（在采样点 $t_m$ 处）

$$
\mathbf{q}'_m = \mathbf{J}^{-1}_m\,\mathbf{r}'_m
$$

$$
\mathbf{q}''_m = \mathbf{J}^{-1}_m\,\mathbf{r}''_m - \mathbf{J}^{-1}_m\,\dot{\mathbf{J}}_m\,\mathbf{q}'_m
\qquad \left(\dot{\mathbf{J}}_m = \frac{d\mathbf{J}}{du}\bigg|_{t_m}\right)
$$

$$
\mathbf{q}'''_m = \mathbf{J}^{-1}_m\,\mathbf{r}'''_m - \mathbf{J}^{-1}_m\,\dot{\mathbf{J}}_m\,\mathbf{q}''_m - \mathbf{J}^{-1}_m\,\ddot{\mathbf{J}}_m\,\mathbf{q}'_m
$$

### 8.3 加速度约束系数（精确线性，无近似）

由 $\ddot{u} = \frac{1}{2}w'(u)$ 精确推导（$w = \dot{u}^2$ 为 LP 决策变量）：

$$
\text{Acc}_i(p,:) = q''_i(\xi_p)\,\mathbf{B}(\xi_p) + \frac{1}{2}q'_i(\xi_p)\,\mathbf{B}'(\xi_p)
\qquad\text{（对 $\mathbf{x}$ 精确线性）}
$$

### 8.4 Jerk 约束系数（第二阶 LP 线性化）

含 $\sqrt{w}$ 因子使 Jerk 非线性，冻结 $\dot{u}_\text{ref} = \sqrt{\mathbf{B}\mathbf{x}^*}$ 后线性化：

$$
\text{Jerk}_i(p,:) = \dot{u}_\text{ref}(\xi_p)\left[q'''_i(\xi_p)\,\mathbf{B}(\xi_p)
+ \frac{3}{2}q''_i(\xi_p)\,\mathbf{B}'(\xi_p)
+ \frac{1}{2}q'_i(\xi_p)\,\mathbf{B}''(\xi_p)\right]
$$

### 8.5 有效速度上限

$$
\dot{u}^2_\text{max}(\xi_p) = \min_{i=1}^{6} \frac{\dot{q}_{i,\max}^2}{q'_i(\xi_p)^2}
$$

### 8.6 LP 目标函数

$$
\min_{\mathbf{x} \geq 0} \;\; -\sum_{k=1}^{K} \mathbf{b}_\text{intgr}^\top \mathbf{D}_k\,\mathbf{x}_k
\quad \text{s.t.}\quad \mathbf{A}\mathbf{x} \leq \mathbf{b},\quad \mathbf{A}_\text{eq}\mathbf{x} = \mathbf{b}_\text{eq}
$$

### 8.7 G2 混合长度

$$
\delta_j = \min\!\left(\delta_\text{max},\; \frac{l_{\text{adj},j}}{2},\; \sqrt{\frac{\varepsilon_\text{blend}}{\kappa_\text{corner}}}\right)
$$

### 8.8 跨窗口边界条件提取

$$
v_0^2[\text{next}] = \mathbf{B}(1)\cdot\mathbf{x}_k, \qquad
a_{t,0}[\text{next}] = \frac{1}{2}\,\mathbf{B}'(1)\cdot\mathbf{x}_k
$$

### 8.9 完整五阶段解耦总结

```
阶段 0（G2 平滑）：角点混合，消除曲率跳变
    输入：分段路径（G0/G1 连续）
    输出：G2 连续路径（保证 q'' 无跳变）

阶段一（几何）：笛卡尔曲率 → 自适应采样
    输入：r(s)，κ_pos(s)，κ_ori(s)
    输出：M 个采样点 {t_m}

阶段二（运动学）：IK + Jacobian 链式法则
    输入：{t_m}，{r(t_m)}
    输出：{q_m, q'_m, q''_m, q'''_m}     ← 一次性，离线完成

阶段三（动力学 · 滑动窗口）：关节空间 LP 时间最优
    每窗口（W 段）：
      - 起端约束：v_0², a_t0（从上一窗口提取）
      - 末端约束：v_1=0（MPC 保守停止）
      - 仅提交第一段，窗口前滑
    输出：最优 ud²(u)，继而 q(t), qd(t), qdd(t)，全程 C¹ 连续
```

---

*文档版本：v1.1 | 日期：2026-05-15 | 更新：G2 路径平滑 + 滑动窗口 MPC + 跨窗口连续性约束*
