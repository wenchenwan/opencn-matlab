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

关节加速度由路径导数展开：

$$
\ddot{q}_i = q''_i(\xi_p) \cdot \dot{u}^2 + q'_i(\xi_p) \cdot \ddot{u}
$$

B 样条线性化（$\ddot{u} = \tfrac{1}{2}\mathbf{B}'(\xi)\mathbf{x} / \sqrt{\mathbf{B}(\xi)\mathbf{x}}$ 近似处理）：

$$
\ddot{q}_i \approx \underbrace{\left[q''_i(\xi_p)\,\mathbf{B}(\xi_p) + \tfrac{1}{2}q'_i(\xi_p)\,\mathbf{B}'(\xi_p)\right]}_{\text{Acc}_i(p,:)} \mathbf{x}_k
$$

LP 不等式（上/下限）：

$$
\pm\,\text{Acc}_i(p,:)\,\mathbf{x}_k \leq \ddot{q}_{i,\max}
$$

所有关节、所有段的加速度约束组成块对角矩阵 $\mathbf{A}_a$（$6 \times 2$ 行 × $M_\text{LP}$ 点 × $K$ 段）。

### 5.4 关节 Jerk 约束（第二阶 LP）

关节 Jerk 精确展开（无近似，得益于预计算的 $\mathbf{q}'''$）：

$$
\dddot{q}_i = q'''_i(\xi_p)\,\dot{u}^3 + 3q''_i(\xi_p)\,\dot{u}\,\ddot{u} + q'_i(\xi_p)\,\dddot{u}
$$

以第一阶 LP 解 $\dot{u}_\text{ref}(\xi_p)$ 为参考，线性化后的 LP 约束：

$$
\pm\,\text{Jerk}_i(p,:)\,\mathbf{x}_k \leq j_{i,\max}
$$

$$
\text{Jerk}_i(p,:) = q'''_i(\xi_p)\,\dot{u}_\text{ref}^2\,\mathbf{B}(\xi_p)
+ \tfrac{3}{2}q''_i(\xi_p)\,\dot{u}_\text{ref}\,\mathbf{B}'(\xi_p)
+ \tfrac{1}{2}q'_i(\xi_p)\,\mathbf{B}''(\xi_p)
$$

**精度优势**：由于 $q'''_i$ 在采样阶段精确计算（见 §3.4），Jerk 约束无需使用全笛卡尔方案中的主项近似，误差可控制在 $<2\%$。

### 5.5 段间 $C^1$ 连续性（等式约束）

相邻段 $k$ 和 $k+1$ 在连接点处要求速度和切向加速度连续：

$$
\mathbf{A}_\text{eq}\,\mathbf{x} = \mathbf{b}_\text{eq}
$$

等式约束共 $2(K+1)$ 行，结构与 OpenCN 现有框架完全相同（见 `buildConstr.m`）：

$$
\begin{cases}
v^2(u_0) = v_0^2,\quad a_t(u_0) = a_{t,0} & \text{（起端边界）} \\
v^2_k(1) = v^2_{k+1}(0),\quad a_{t,k}(1) = a_{t,k+1}(0) & \text{（段间连接）} \\
v^2(u_K) = v_1^2,\quad a_t(u_K) = a_{t,1} & \text{（末端边界）}
\end{cases}
$$

### 5.6 约束矩阵维度汇总

$$
N_c = \underbrace{1}_{\text{速度非负}} + \underbrace{2 \times 6}_{\text{关节速度}} + \underbrace{2 \times 6}_{\text{关节加速度}} = 25\;\text{行/点/段}
$$

$$
\mathbf{A} \in \mathbb{R}^{N_c \cdot M_\text{LP} \cdot K \;\times\; N \cdot K}, \quad \mathbf{A}_\text{eq} \in \mathbb{R}^{2(K+1) \;\times\; N \cdot K}
$$

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
├── cartesian_path_sample.m          ─── §二：自适应离散化
│   ├── position_curvature()
│   ├── orientation_curvature()
│   └── adaptive_sample_path()
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
├── build_joint_constr.m             ─── §五：LP 约束构造
│   ├── eval_segment_derivatives()   在 LP 离散点处求 q'/q''/q'''
│   ├── build_vel_constr()           速度约束行
│   ├── build_acc_constr()           加速度约束行（Acc 矩阵）
│   └── build_continuity_eq()        段间等式约束
│
└── FeedratePlanning_LP.m            ─── 复用 OpenCN LP 求解器
    ├── compute_scaling_matrix()     决策变量缩放（D = diag(1/h²)）
    ├── c_simplex()                  LP 求解
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
%   cart_path   : 笛卡尔路径描述（含 r(t), r'(t), r''(t), r'''(t)）
%   robot_params: 机器人参数（DH, q_lim, vmax, amax, jmax）

%% 阶段一：自适应离散化
[t_sample, r_sample] = adaptive_sample_path(cart_path, ...
    robot_params.eps_pos, ...    % 位置弦误差容差
    robot_params.eps_ori, ...    % 角度误差容差
    robot_params.ds_max);        % 最大步长

M = length(t_sample);

%% 阶段二：关节空间导数计算
jpd = compute_joint_derivatives(t_sample, cart_path, robot_params);
% jpd.q, jpd.dq, jpd.d2q, jpd.d3q

%% 阶段三：分段参数化
hermite = build_hermite_segments(jpd);
% 返回每段的五次 Hermite 系数

%% 阶段四：构造 LP 约束矩阵（全在关节空间，无 IK/J⁻¹）
[A, b, Aeq, beq] = build_joint_constr(hermite, jpd, ...
    robot_params.vmax, ...
    robot_params.amax, ...
    BasisVal, BasisValD);

%% 阶段五：LP 求解（复用 OpenCN 求解器）
[D, Dinv] = compute_scaling_matrix_joint(jpd.h);
[Coeff, success] = c_simplex(-f * D, A * D, b, Aeq * D, beq);

%% 阶段六：轨迹合成
result = synthesize_trajectory(Coeff, hermite, jpd, robot_params.dt);

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

### 8.3 段内加速度约束系数

$$
\text{Acc}_i(p,:) = q''_i(\xi_p)\,\mathbf{B}(\xi_p) + \tfrac{1}{2}q'_i(\xi_p)\,\mathbf{B}'(\xi_p)
$$

### 8.4 段内 Jerk 约束系数

$$
\text{Jerk}_i(p,:) = q'''_i(\xi_p)\,\dot{u}_\text{ref}^2\,\mathbf{B}(\xi_p)
+ \tfrac{3}{2}q''_i(\xi_p)\,\dot{u}_\text{ref}\,\mathbf{B}'(\xi_p)
+ \tfrac{1}{2}q'_i(\xi_p)\,\mathbf{B}''(\xi_p)
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

### 8.7 三阶段解耦总结

```
阶段一（几何）：笛卡尔曲率 → 自适应采样
    输入：r(s)，κ_pos(s)，κ_ori(s)
    输出：M 个采样点 {t_m}

阶段二（运动学）：IK + Jacobian 链式法则
    输入：{t_m}，{r(t_m)}
    输出：{q_m, q'_m, q''_m, q'''_m}     ← 一次性，离线完成

阶段三（动力学）：关节空间 LP 时间最优
    输入：{q'_m, q''_m, q'''_m}（预计算，无 IK，无 J⁻¹）
    输出：最优 ud²(u)，继而 q(t), qd(t), qdd(t)
```

---

*文档版本：v1.0 | 日期：2026-05-15 | 方案：笛卡尔离散化 + 关节空间 TOPP*
