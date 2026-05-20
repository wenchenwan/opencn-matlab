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

> **更新记录**：
> - §2.5 重写：G2 平滑改为基于 `G2_Hermite_Interpolation_nAxis` / `calcTransition`，明确 zone 距离（CutOff）工程含义
> - §五 重写：决策变量说明补充 $w=\dot{u}^2$ 含义；不等式/等式约束分章节清晰描述；两阶段 LP 合并为 §5.4 集中说明（第一阶段精确线性 + 第二阶段仅 Jerk 线性化），修正不等式约束行数（26行/点 = 2速度+12加速度+12力矩）；滑动窗口 MPC 整理为 §5.5
> - §5.2.4 修正：速度约束以 $x$ 上界（`xbound`）实现，不进约束矩阵（对照 TOPPRA `JointVelocityConstraint` 实际实现）；TCP 速度约束合并至 $f_\text{max}$ 的 min 操作
> - §5.2.5 修正：关节力矩约束为精确线性（科氏项对 $x=\dot{s}^2$ 天然线性），通过三次逆动力学调用分离 $u$ 系数和 $x$ 系数，无需冻结参考解线性化（对照 TOPPRA `JointTorqueConstraint` 实际实现）；力矩约束与加速度约束同属**第一阶段 LP**，仅 Jerk 约束在第二阶段叠加；§8.5b 公式同步更新
> - §5.2.5 扩展：新增电机 T-N 曲线速度相关力矩约束（参考 Ardeshiri 等 2011）：在 $(\tau_i, \dot{q}_i^2)$ 空间用仿射切线内近似 T-N 边界（保守凸化），代入 $\dot{q}_i^2 = q_i'^2 x$ 后得精确线性 LP 行 $[(T_{ij}/2)a_i\mathbf{B}' + (T_{ij}b_i+\overline{U}_{ij}q_i'^2)\mathbf{B}]\bar{\mathbf{x}} \leq P_{ij}-T_{ij}c_i$，仍属第一阶段；§8.5b 和 §9.2 同步更新

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
| $s \in [0,L]$ | 笛卡尔路径弧长（公共路径参数） | 标量 |
| $\xi \in [0,1]$ | 段内局部归一化参数，$\xi = (s-s_m)/h_m$ | 标量 |
| $h_m = s_{m+1} - s_m$ | 第 $m$ 段的弧长 | 标量 |
| $\mathbf{r}(s) = [\mathbf{p}(s);\,\boldsymbol{\varphi}(s)]$ | 笛卡尔位姿（弧长函数） | $6\times1$ |
| $\mathbf{q}(s) = \text{IK}(\mathbf{r}(s))$ | 关节角（**同一参数 $s$**） | $6\times1$ |
| $(\cdot)' \triangleq d(\cdot)/ds$ | 对弧长 $s$ 求导（路径导数） | — |
| $\dot{(\cdot)} \triangleq d(\cdot)/dt$ | 对时间 $t$ 求导（时间导数） | — |
| $\dot{s} = ds/dt$ | 路径速度（标量） | 标量 |
| $w(s) = \dot{s}^2$ | **LP 决策变量**（路径速度平方） | 标量 |
| $\mathbf{J}(\mathbf{q})$ | 几何 Jacobian，$\dot{\mathbf{r}} = \mathbf{J}\dot{\mathbf{q}}$ | $6\times6$ |
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

本方案直接复用项目已有的 `G2_Hermite_Interpolation_nAxis`（`common/Feedopt/`）和 `calcTransition`（`common/Feedopt/`）实现 G2 平滑，不另行开发混合曲线算法。

#### 2.5.1 G2 连续的几何含义

对于弧长参数化路径 $\mathbf{r}(s)$，G2 连续要求曲率向量在交接点 $s_j$ 处匹配：

$$
\mathbf{r}''(s_j^-) = \mathbf{r}''(s_j^+)
$$

G0（位置）和 G1（切线方向）是 G2 的必要前提，五次多项式过渡曲线（TransP5）可同时满足这三个条件。

#### 2.5.2 `G2_Hermite_Interpolation_nAxis` 的工作原理

**函数接口**（`common/Feedopt/G2_Hermite_Interpolation_nAxis.m`）：

```matlab
[p5, status, alpha0, alpha1] = G2_Hermite_Interpolation_nAxis( ...
    ctx, r0D0, r0D1, r0D2, r1D0, r1D1, r1D2)
```

| 参数 | 含义 |
|---|---|
| `r0D0/r0D1/r0D2` | 左端（截短曲线末端 $u=1$）的位置/一阶导/二阶导 |
| `r1D0/r1D1/r1D2` | 右端（截短曲线起端 $u=0$）的位置/一阶导/二阶导 |
| `p5` | 五次多项式系数矩阵 `[6×6]`（每行一个轴，降幂排列） |
| `status` | 1 = 成功；3/4/5 = 无正实根；6 = 最终验证失败（数值警告，仍可用） |
| `alpha0/alpha1` | 最优切向拉伸参数（>0），控制过渡曲线的"拉伸"程度 |

**求解逻辑**：利用 Frenet 框架将 G2 边界条件（位置 + 切向方向 + 曲率）化为关于自由参数 $\alpha_0,\alpha_1$ 的多项式方程组，按两端曲率是否为零分四种情况（详见函数注释）：

| 情况 | 条件 | 求解方法 |
|---|---|---|
| 1 | $\kappa_0=0,\;\kappa_1=0$（直线-直线） | 2×2 线性方程组，直接解 |
| 2 | $\kappa_0=0,\;\kappa_1\neq0$（直线-曲线） | 关于 $\alpha_1$ 的三次多项式 |
| 3 | $\kappa_0\neq0,\;\kappa_1=0$（曲线-直线） | 关于 $\alpha_0$ 的三次多项式 |
| 4 | $\kappa_0\neq0,\;\kappa_1\neq0$（曲线-曲线） | 结式消元 → 关于 $\alpha_1$ 的九次多项式 |

多根时按最小化三阶导范数积分（跃度代价 `EvalCostIntegral`）选最优解。五次 Hermite 基函数：

$$
p_5(u) = \mathbf{r}_L \cdot h_{00} + \alpha_0\mathbf{t}_0 \cdot h_{10} + (\beta_0\mathbf{t}_0 + \alpha_0^2\kappa_0\mathbf{n}_0) \cdot h_{20}
+ \mathbf{r}_R \cdot h_{01} + \alpha_1\mathbf{t}_1 \cdot h_{11} + (\beta_1\mathbf{t}_1 + \alpha_1^2\kappa_1\mathbf{n}_1) \cdot h_{21}
$$

其中 $\mathbf{t},\mathbf{n},\kappa$ 为端点处的 Frenet 框架参数（切向、法向、曲率），$\beta_0,\beta_1$ 由 $\alpha_0,\alpha_1$ 线性确定。

#### 2.5.3 zone 距离（CutOff）与过渡区间

对应工业机器人编程中的 **zone 参数**（如 ABB 的 z5/z10，KUKA 的 C_DIS），`CutOff` 定义了在交接点两侧各截去的弧长，即过渡曲线插入的**单侧 zone 距离**：

$$
\boxed{\Delta_j = \min\!\left(\Delta_\text{max},\; \frac{L_1}{3},\; \frac{L_2}{3}\right)}
$$

| 参数 | 含义 |
|---|---|
| $\Delta_\text{max}$ | 用户设定的最大 zone 距离（`ctx.cfg.CutOff` 或 `robot_params.delta_max`，m） |
| $L_1 / L_2$ | 交接点两侧相邻段的弧长 |
| $L/3$ 上限 | 防止相邻过渡区重叠（两侧各截 1/3，中间留 1/3 原始段） |

截短操作（`cutCurvStruct`）：在左段末端截去 $\Delta_j$，在右段起端截去 $\Delta_j$，然后在截短端点处调用 `G2_Hermite_Interpolation_nAxis` 构造 TransP5 过渡段。

典型工程取值：机器人路径 $\Delta_j = 1\,\text{mm}\sim10\,\text{mm}$（对应 CutOff），精加工取小值，搬运取大值。

#### 2.5.4 位姿联合路径的 G2 平滑

`G2_Hermite_Interpolation_nAxis` 天然支持 N 维路径（`r0D0` 等为 `[N_active×1]` 向量，`ctx.cfg.maskTot` 指定激活轴）。对于 6D 位姿路径 $\mathbf{r}=[p_x;p_y;p_z;\varphi_x;\varphi_y;\varphi_z]$，位置轴和姿态轴同时纳入 Frenet 框架，统一使用同一个 zone 距离 $\Delta_j$。特征长度 $D$（`ctx.cfg.D`）用于量纲归一化，防止 mm 级位置与 rad 级姿态混合时数值病态。

#### 2.5.5 `calcTransition` 封装的完整流程

项目已有的 `calcTransition`（`common/Feedopt/`）将上述步骤封装为标准接口：

```
calcTransition(ctx, curv1, curv2)
  ①  LengthCurv → L1, L2
  ②  安全检查：L1 < 3·CutOff 或 L2 < 3·CutOff → 放弃，返回 NoSolution
  ③  cutCurvStruct(curv1, L1-CutOff) → curv1_cut（去末端 CutOff）
  ④  cutCurvStruct(curv2, L2-CutOff) → curv2_cut（去起端 CutOff）
  ⑤  EvalCurvStruct(curv1_cut, u=1) → r0D0/r0D1/r0D2（含 robot_mode 分支）
  ⑥  EvalCurvStruct(curv2_cut, u=0) → r1D0/r1D1/r1D2
  ⑦  G2_Hermite_Interpolation_nAxis → p5, status
  ⑧  constrTransP5Struct → curvT（TransP5 类型曲线结构体）
  ⑨  check_continuity → 验证 G2 连续性（位置/切线/曲率容差）
  输出：status(Ok/NoSolution), curv1_cut, curv2_cut, curvT
```

对机器人路径，`EvalCurvStruct` 经过 `ctx.robot_mode=true` 分支调用 `EvalRobotCurv`，正确处理 Line/Helix 类型段的导数。

完整预处理流程：

```
原始分段路径（G0/G1 连续，CurvStruct 数组）
     ↓ §2.5  对每对相邻段调用 calcTransition
             成功 → 插入 TransP5 过渡段，两端段截短
             失败 → 保留原始角点（G1 退化，LP 自动降速）
G2 连续路径（原始段截短 + TransP5 段交替）
     ↓ §2.1~2.3  自适应离散化（过渡段曲率高 → 自动加密）
M 个采样点 {t_m}
     ↓ §三  关节空间导数计算（q', q'', q''' 精确）
```

---

## 三、离散点处的关节空间导数计算

### 3.0 参数化框架

#### 3.0.1 公共路径参数 $s$（弧长）

本方案选用笛卡尔路径的**弧长 $s$** 作为路径参数：

$$
s = \int_0^t \|\dot{\mathbf{r}}(\tau)\|\,d\tau \in [0, L], \quad L = \text{路径总弧长}
$$

弧长参数的优点是 $\|\mathbf{r}'(s)\|_\text{pos} = 1$（位置分量单位切向量），导数有直接的几何意义（单位：mm/mm = 无量纲方向向量）。

**笛卡尔路径和关节路径使用同一个参数 $s$**：

$$
\mathbf{r}(s) = [\mathbf{p}(s);\,\boldsymbol{\varphi}(s)] \in \mathbb{R}^6
\qquad\text{（笛卡尔位姿，函数自变量为弧长 $s$）}
$$

$$
\mathbf{q}(s) = \text{IK}(\mathbf{r}(s)) \in \mathbb{R}^6
\qquad\text{（关节角，同样是 $s$ 的函数）}
$$

两者描述的是**同一条路径在不同坐标系中的表示**——弧长 $s$ 是路径本身的几何属性，与坐标系无关。§2 中自适应采样得到的 $\{s_m\}$ 即为本节的采样参数序列（§2 中记作 $\{t_m\}$，本节统一改写为 $\{s_m\}$）。

#### 3.0.2 路径参数导数与时间导数的关系

路径参数 $s$ 是**几何量**，时间 $t$ 是**运动量**，二者通过路径速度 $\dot{s} = ds/dt$ 联系：

$$
\frac{d(\cdot)}{dt} = \frac{d(\cdot)}{ds} \cdot \dot{s}
$$

约定符号：$(\cdot)' \triangleq d(\cdot)/ds$（路径导数），$\dot{(\cdot)} \triangleq d(\cdot)/dt$（时间导数）。

**笛卡尔速度与加速度**（由路径导数 + 路径速度合成）：

$$
\dot{\mathbf{r}} = \mathbf{r}'(s)\,\dot{s}, \qquad
\ddot{\mathbf{r}} = \mathbf{r}''(s)\,\dot{s}^2 + \mathbf{r}'(s)\,\ddot{s}
$$

**关节速度与加速度**（同一公式，参数相同）：

$$
\dot{\mathbf{q}} = \mathbf{q}'(s)\,\dot{s}, \qquad
\ddot{\mathbf{q}} = \mathbf{q}''(s)\,\dot{s}^2 + \mathbf{q}'(s)\,\ddot{s}
$$

LP 优化的决策变量为 $w(s) = \dot{s}^2$（路径速度的平方），并利用恒等式：

$$
\ddot{s} = \frac{1}{2}w'(s), \qquad \dddot{s} = \frac{1}{2}w''(s)\,\dot{s}
$$

因此关节速度、加速度、Jerk 对决策变量的约束形式为：

| 物理量 | 对 $s$ 的路径导数 | 对 $w(s) = \dot{s}^2$ 的约束形式 |
|---|---|---|
| $\dot{q}_i$ | $q'_i(s)\,\dot{s}$ | $q_i'^2(s)\cdot w \leq \dot{q}_{i,\max}^2$ |
| $\ddot{q}_i$ | $q''_i\,\dot{s}^2 + q'_i\,\ddot{s}$ | $q''_i\,w + \frac{1}{2}q'_i\,w' = \text{Acc}_i \cdot \mathbf{x}$（精确线性）|
| $\dddot{q}_i$ | $q'''_i\,\dot{s}^3 + 3q''_i\,\dot{s}\ddot{s} + q'_i\,\dddot{s}$ | $\dot{s}_\text{ref}\!\left[q'''_i\,\mathbf{B} + \frac{3}{2}q''_i\,\mathbf{B}' + \frac{1}{2}q'_i\,\mathbf{B}''\right]\!\mathbf{x}$（线性化）|

#### 3.0.3 段内局部参数 $\xi$

相邻采样点 $s_m$ 和 $s_{m+1}$ 之间，段弧长 $h_m = s_{m+1} - s_m$，定义局部归一化参数：

$$
\xi = \frac{s - s_m}{h_m} \in [0,1]
$$

路径导数在两套参数下的换算（链式法则）：

$$
\frac{d(\cdot)}{d\xi} = h_m \cdot \frac{d(\cdot)}{ds}, \qquad
\frac{d^2(\cdot)}{d\xi^2} = h_m^2 \cdot \frac{d^2(\cdot)}{ds^2}, \qquad
\frac{d^3(\cdot)}{d\xi^3} = h_m^3 \cdot \frac{d^3(\cdot)}{ds^3}
$$

§四 的 Hermite 插值使用 $\xi$ 作为段内参数，端点条件直接使用 $s$ 的路径导数（带 $h_m$ 缩放）。

---

### 3.1 逆运动学（IK）

在每个采样点 $s_m$，由笛卡尔位姿求关节角（**连续解选择**是关键）：

$$
\mathbf{q}_m = \text{IK}(\mathbf{r}(s_m))
$$

连续解选择策略（按优先级）：
1. **最近解**：从所有候选 IK 解中选 $\|\mathbf{q} - \mathbf{q}_{m-1}\|$ 最小者
2. **构型一致**：保持 elbow_up/down 不变（除非关节限位迫使切换）
3. **关节限位合法**：排除违反 $\mathbf{q}_\text{lim}$ 的解

### 3.2 一阶路径导数（$d\mathbf{q}/ds$）

笛卡尔速度 $\dot{\mathbf{r}} = \mathbf{J}(\mathbf{q})\,\dot{\mathbf{q}}$ 两边同除以 $\dot{s}$（注意 $\dot{\mathbf{r}} = \mathbf{r}'(s)\dot{s}$，$\dot{\mathbf{q}} = \mathbf{q}'(s)\dot{s}$，$\dot{s}$ 约去）：

$$
\mathbf{r}'(s) = \mathbf{J}(\mathbf{q}(s))\,\mathbf{q}'(s)
\;\Rightarrow\;
\boxed{\mathbf{q}'(s) = \mathbf{J}^{-1}(\mathbf{q}(s))\,\mathbf{r}'(s)}
$$

该等式对任意路径速度 $\dot{s}$ 均成立——它是纯几何关系，与路径怎么走（快还是慢）无关。在采样点 $s_m$ 处：

$$
\mathbf{q}'_m \triangleq \mathbf{q}'(s_m) = \mathbf{J}^{-1}_m \cdot \mathbf{r}'(s_m)
$$

其中 $\mathbf{r}'(s_m)$ 是笛卡尔路径在 $s_m$ 处对弧长的一阶导数（由路径表示解析求得，见 §2.4）。

> **注意**：$\mathbf{r}'(s)$ 和 $\mathbf{q}'(s)$ 的自变量是**同一个参数 $s$**，这不是巧合——两者都描述同一条路径，只是坐标系不同。Jacobian $\mathbf{J}$ 正是两个坐标系的"速度换算矩阵"，弧长 $\dot{s}$ 是公共的标量缩放因子，两边约去后得到纯路径导数关系。

### 3.3 二阶路径导数（$d^2\mathbf{q}/ds^2$）

对 $\mathbf{q}'(s) = \mathbf{J}^{-1}(\mathbf{q}(s))\,\mathbf{r}'(s)$ 再对 $s$ 求导（乘积法则），利用：

$$
\frac{d\mathbf{J}^{-1}}{ds} = -\mathbf{J}^{-1}\,\frac{d\mathbf{J}}{ds}\,\mathbf{J}^{-1},
\qquad
\frac{d\mathbf{J}}{ds} = \sum_{i=1}^{6} \frac{\partial \mathbf{J}}{\partial q_i}\,q'_i(s)
$$

得：

$$
\boxed{\mathbf{q}''_m = \mathbf{J}^{-1}_m\,\mathbf{r}''(s_m) - \mathbf{J}^{-1}_m\,\mathbf{J}'_m\,\mathbf{q}'_m}
$$

其中 $\mathbf{J}'_m \triangleq d\mathbf{J}/ds|_{s_m}$ 用前向差分近似（沿路径方向微扰）：

$$
\mathbf{J}'_m \approx \frac{\mathbf{J}(\mathbf{q}_m + \varepsilon\,\mathbf{q}'_m) - \mathbf{J}(\mathbf{q}_m)}{\varepsilon}, \quad \varepsilon = 10^{-7}
$$

**含义**：$\mathbf{J}^{-1}\mathbf{r}''$ 是笛卡尔路径曲率在关节空间的映射；$\mathbf{J}^{-1}\mathbf{J}'\mathbf{q}'$ 是 Jacobian 沿路径变化的补偿项（类似科里奥利修正）。

### 3.4 三阶路径导数（$d^3\mathbf{q}/ds^3$）

对 $\mathbf{q}''(s)$ 再对 $s$ 求导，完整展开（无截断）：

$$
\boxed{\mathbf{q}'''_m = \mathbf{J}^{-1}_m\,\mathbf{r}'''(s_m) - \mathbf{J}^{-1}_m\,\mathbf{J}'_m\,\mathbf{q}''_m - \mathbf{J}^{-1}_m\,\mathbf{J}''_m\,\mathbf{q}'_m}
$$

其中 $\mathbf{J}''_m \triangleq d^2\mathbf{J}/ds^2|_{s_m}$ 用中心差分近似：

$$
\mathbf{J}''_m \approx \frac{\mathbf{J}(\mathbf{q}_m + \varepsilon\mathbf{q}'_m) - 2\mathbf{J}(\mathbf{q}_m) + \mathbf{J}(\mathbf{q}_m - \varepsilon\mathbf{q}'_m)}{\varepsilon^2}
$$

> **三阶导数的含义**：$\mathbf{q}'''(s)$ 与路径 Jerk 的方向系数直接对应（见 §5.4），精确计算它（包含 $\mathbf{J}''$ 项）是保证 Jerk 约束精度 $<2\%$ 的关键。

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

### 5.1 决策变量与目标函数

#### 5.1.1 决策变量

每段 $k$（对应相邻采样点 $[t_m,t_{m+1}]$）引入 B 样条系数向量 $\mathbf{x}_k \in \mathbb{R}^N$，用于近似**参数速度平方**：

$$
w(\xi) \triangleq \dot{u}^2(\xi) \approx \mathbf{B}(\xi)\,\mathbf{x}_k, \quad \xi \in [0,1], \quad \mathbf{x}_k \geq 0
$$

> **注意**：$w = \dot{u}^2$ 是路径参数 $u$ 的变化速率的平方，**不是**关节空间或笛卡尔空间的物理速度平方。物理速度需通过 $v_i = q'_i(\xi)\cdot\dot{u}$ 计算（$q'_i$ 是关节角对参数的导数，§四已预计算）。

滑动窗口内 $W$ 段的全局决策变量：$\mathbf{x} \in \mathbb{R}^{N \times W}$。

#### 5.1.2 目标函数（最大化速度积分）

$$
\min_{\mathbf{x}} \;\; -\sum_{k=1}^{W} \mathbf{b}_\text{intgr}^\top \mathbf{D}_k \, \mathbf{x}_k
$$

其中 $\mathbf{b}_\text{intgr} = \int_0^1 \mathbf{B}(\xi)\,d\xi$（B 样条基积分向量），$\mathbf{D}_k = \mathrm{diag}(h_k^{-2})$ 为弧长归一化缩放矩阵（$h_k$ = 第 $k$ 段弧长）。最大化 $\int w\,d\xi$ 等价于最大化参数速度积分，即近似最小化轨迹总时间。

#### 5.1.3 关键链式法则

$w = \dot{u}^2$，$'$ 表示对路径参数 $u$ 求导，各阶时间导数的精确关系：

$$
\begin{aligned}
\dot{u} &= \sqrt{w} & \quad \ddot{u} &= \frac{1}{2}w' = \frac{1}{2}\mathbf{B}'\mathbf{x} \\[4pt]
\dddot{u} &= \frac{1}{2}w''\dot{u} = \frac{1}{2}\mathbf{B}''\mathbf{x}\cdot\sqrt{w}
\end{aligned}
$$

**关键结论**：$\ddot{u} = \frac{1}{2}w'$ 是 $\mathbf{x}$ 的精确线性函数；$\dddot{u}$ 含 $\sqrt{w}$ 因子，是非线性的。这一区别决定了速度/加速度约束可精确线性化，而 Jerk 约束必须分两阶段处理。

---

### 5.2 不等式约束（速度 + 加速度）

#### 5.2.1 关节速度约束

关节 $i$ 的物理速度约束：

$$
|\dot{q}_i(\xi_p)| = |q'_i(\xi_p)| \cdot \dot{u} \leq \dot{q}_{i,\max}
$$

两边平方，代入 $\dot{u}^2 = w = \mathbf{B}(\xi_p)\mathbf{x}_k$，得精确线性不等式：

$$
q'_i(\xi_p)^2 \cdot \mathbf{B}(\xi_p)\,\mathbf{x}_k \leq \dot{q}_{i,\max}^2
$$

对所有 $M$ 个离散点和 $N_\text{axis}=6$ 个关节，速度约束写成**单行**形式（取逐点最紧约束 `f_max`）：

$$
\mathbf{B}(\xi_p)\,\mathbf{x}_k \leq f_\text{max}(\xi_p), \quad
f_\text{max}(\xi_p) = \min_{i=1}^{6}\frac{\dot{q}_{i,\max}^2}{q'_i(\xi_p)^2}
$$

同时加入速度非负约束 $w \geq 0$，即 $-\mathbf{B}(\xi_p)\mathbf{x}_k \leq 0$。

> 对应 `buildConstr.m`：`v_max = min((vmax./r1D_a).^2, [], 1)`，速度约束合并为 1 行，速度非负约束 1 行，共 **2 行**每点。

#### 5.2.2 关节加速度约束

**精确推导**（无近似）：将关节加速度按链式法则展开，代入 $\dot{u}^2 = \mathbf{B}\mathbf{x}$ 和 $\ddot{u} = \frac{1}{2}\mathbf{B}'\mathbf{x}$：

$$
\ddot{q}_i(\xi_p) = q''_i(\xi_p)\underbrace{\dot{u}^2}_{\mathbf{B}\mathbf{x}} + q'_i(\xi_p)\underbrace{\ddot{u}}_{\frac{1}{2}\mathbf{B}'\mathbf{x}}
= \underbrace{\Bigl[q''_i(\xi_p)\,\mathbf{B}(\xi_p) + \tfrac{1}{2}q'_i(\xi_p)\,\mathbf{B}'(\xi_p)\Bigr]}_{\text{Acc}_i(p,:)}\,\mathbf{x}_k
$$

$\text{Acc}_i(p,:) \in \mathbb{R}^{1\times N}$ 是预计算的常数行向量（依赖 $q'_i, q''_i$ 和 B 样条基，均已在 §四离线计算好）。加速度约束（上/下限各一行）：

$$
+\text{Acc}_i(p,:)\,\mathbf{x}_k \leq \ddot{q}_{i,\max}, \quad -\text{Acc}_i(p,:)\,\mathbf{x}_k \leq \ddot{q}_{i,\max}
$$

对 $N_\text{axis}=6$ 个关节，每个离散点 $\xi_p$ 共 $2\times 6 = 12$ 行。

> 对应 `buildConstr.m`：`Acc_j = r2D_a(j,:).*BasisVal + 0.5.*r1D_a(j,:).*BasisValD`

#### 5.2.3 不等式约束结构汇总（第一阶段 LP 输入）

每段 $k$，每个离散点 $\xi_p$（共 $M$ 个点）的不等式约束行：

$$
\underbrace{1}_{\text{速度上限}} + \underbrace{1}_{\text{速度非负}} + \underbrace{2\times N_\text{axis}}_{\text{加速度上/下限}} = 2 + 2N_\text{axis} = 14\;\text{行/点（6轴机器人）}
$$

窗口内完整不等式约束矩阵（块对角，第 $k$ 段约束只涉及 $\mathbf{x}_k$）：

$$
\mathbf{A}_\text{ineq} \in \mathbb{R}^{14\,M W \;\times\; NW}, \quad \mathbf{b}_\text{ineq} \in \mathbb{R}^{14\,MW}
$$

具体行结构（段 $k$，点 $p$）：

$$
\mathbf{A}_k(p) = \begin{bmatrix}
\mathbf{B}(\xi_p)      \\
-\mathbf{B}(\xi_p)     \\
+\text{Acc}_1(p,:)     \\
\vdots                 \\
+\text{Acc}_6(p,:)     \\
-\text{Acc}_1(p,:)     \\
\vdots                 \\
-\text{Acc}_6(p,:)
\end{bmatrix},\quad
\mathbf{b}_k(p) = \begin{bmatrix}
f_\text{max}(\xi_p)    \\
0                      \\
\ddot{q}_{1,\max}      \\
\vdots                 \\
\ddot{q}_{6,\max}      \\
\ddot{q}_{1,\max}      \\
\vdots                 \\
\ddot{q}_{6,\max}
\end{bmatrix}
$$

#### 5.2.4 笛卡尔 TCP 速度约束

除关节空间约束外，工业机器人路径跟踪中往往需要限制 TCP（工具中心点）在笛卡尔空间中的线速度和角速度，以保证加工质量或安全性（如焊接、涂胶的工艺速度窗口）。

**TCP 线速度的参数化**

TCP 线速度由正运动学 Jacobian 的位置分量 $\mathbf{J}_v(\mathbf{q}) \in \mathbb{R}^{3\times6}$ 给出：

$$
\mathbf{v}_\text{tcp} = \mathbf{J}_v(\mathbf{q})\,\dot{\mathbf{q}} = \mathbf{J}_v(\mathbf{q})\,\mathbf{q}'(\xi)\cdot\dot{s}
$$

TCP 线速度模长的平方（令 $x = \dot{s}^2$）：

$$
\|\mathbf{v}_\text{tcp}\|^2 = \|\mathbf{J}_v\,\mathbf{q}'(\xi)\|^2 \cdot x = c_v(\xi)^2 \cdot x
$$

其中 $c_v(\xi_p) = \|\mathbf{J}_v(\mathbf{q}(\xi_p))\,\mathbf{q}'(\xi_p)\|$（标量，依赖路径参数，**预计算**）。

TCP 线速度约束（上限 $v_\text{tcp,max}$，对 $x$ 精确线性）等价于对 $x$ 的上界约束：

$$
x \leq \frac{v_\text{tcp,max}^2}{c_v(\xi_p)^2}
$$

**TCP 角速度约束**

TCP 角速度由 Jacobian 的角速度分量 $\mathbf{J}_\omega(\mathbf{q}) \in \mathbb{R}^{3\times6}$ 给出，约束形式与线速度完全对称：

$$
x \leq \frac{\omega_\text{tcp,max}^2}{c_\omega(\xi_p)^2}, \quad
c_\omega(\xi_p) = \|\mathbf{J}_\omega(\mathbf{q}(\xi_p))\,\mathbf{q}'(\xi_p)\|
$$

**与关节速度约束的合并**

TCP 速度约束与关节速度约束均为对 $x = \dot{s}^2$ 的上界约束，可合并为单一的 $x_\text{bound}$：

$$
x \leq f_\text{max}(\xi_p) = \min\!\left(
\min_{i=1}^{6}\frac{\dot{q}_{i,\max}^2}{q'_i(\xi_p)^2},\;\;
\frac{v_\text{tcp,max}^2}{c_v(\xi_p)^2},\;\;
\frac{\omega_\text{tcp,max}^2}{c_\omega(\xi_p)^2}
\right)
$$

**预计算**：$c_v(\xi_p)$ 和 $c_\omega(\xi_p)$ 均在离散化阶段（§四）与 $q'_i, q''_i$ 一起预计算，LP 阶段仅做系数查表，不增加 LP 规模（仍为每点 1 个 $x$ 上界，体现在 `xbound` 中而非约束矩阵行）。

> **对照 TOPPRA 实现**（`linear_joint_velocity.py`）：`JointVelocityConstraint.compute_constraint_params` 调用 `_create_velocity_constraint(qs, vlim)`，直接返回 `xbound`（对 $x=\dot{s}^2$ 的上下界数组），其余返回值均为 `None`。即速度约束不进入 $\mathbf{A}\mathbf{x} \leq \mathbf{b}$ 矩阵，而是以独立的 `xbound` 传入求解器——本框架中对应 $f_\text{max}$ 的上界约束，与此处推导一致。

#### 5.2.5 关节力矩约束（动力学约束）

关节力矩约束是 TOPPRA 相对于纯运动学 TOPP 的核心扩展，将机器人动力学方程（惯性、科氏力、重力、摩擦力）纳入 LP 约束，确保规划轨迹在电机额定力矩范围内可执行。

**机器人动力学方程**

$$
\boldsymbol{\tau} = \mathbf{M}(\mathbf{q})\ddot{\mathbf{q}} + \mathbf{C}(\mathbf{q},\dot{\mathbf{q}})\dot{\mathbf{q}} + \mathbf{g}(\mathbf{q}) + \mathbf{f}(\dot{\mathbf{q}})
$$

其中：$\mathbf{M}(\mathbf{q}) \in \mathbb{R}^{6\times6}$ 为关节空间惯性矩阵，$\mathbf{C}(\mathbf{q},\dot{\mathbf{q}})$ 为科氏/离心矩阵，$\mathbf{g}(\mathbf{q})$ 为重力向量，$\mathbf{f}(\dot{\mathbf{q}})$ 为摩擦力（干摩擦 $f_s \operatorname{sgn}(\dot{q})$）。

**代入路径参数化——精确线性分离**

使用 toppra 的变量定义：$x = \dot{s}^2$，$u = \ddot{s}$，则：

$$
\dot{\mathbf{q}} = \mathbf{q}'(\xi)\,\dot{s}, \quad
\ddot{\mathbf{q}} = \mathbf{q}'(\xi)\,u + \mathbf{q}''(\xi)\,x
$$

代入动力学方程：

$$
\boldsymbol{\tau} = \underbrace{\mathbf{M}(\mathbf{q})\,\mathbf{q}'(\xi)}_{\mathbf{a}(\xi)}\, u
+ \underbrace{\mathbf{M}(\mathbf{q})\,\mathbf{q}''(\xi) + \mathbf{C}(\mathbf{q},\,\mathbf{q}'\dot{s})\,\mathbf{q}'\dot{s}}_{\mathbf{b}(\xi)}\, x
+ \underbrace{\mathbf{g}(\mathbf{q}) + \mathbf{f}(\mathbf{q}'\dot{s})}_{\mathbf{c}(\xi)}
$$

**关键点**：科氏项 $\mathbf{C}(\mathbf{q},\dot{\mathbf{q}})\dot{\mathbf{q}} = \mathbf{C}(\mathbf{q},\mathbf{q}'\dot{s})\mathbf{q}'\dot{s}^2$ 对 $x=\dot{s}^2$ 天然是线性的（$\mathbf{C}$ 对 $\dot{\mathbf{q}}$ 一次齐次），无需任何线性化近似。因此力矩约束对 $(u, x)$ 精确线性。

**三次逆动力学调用分离系数（对照 TOPPRA `joint_torque.py`）**

在离散点 $\xi_p$ 处，定义 $\mathbf{q}_p = \mathbf{q}(\xi_p)$，$\mathbf{q}'_p = \mathbf{q}'(\xi_p)$，$\mathbf{q}''_p = \mathbf{q}''(\xi_p)$，通过三次逆动力学调用精确分离系数：

$$
\mathbf{c}(\xi_p) = \text{inv\_dyn}(\mathbf{q}_p,\;\mathbf{0},\;\mathbf{0})
$$

$$
\mathbf{a}(\xi_p) = \text{inv\_dyn}(\mathbf{q}_p,\;\mathbf{0},\;\mathbf{q}'_p) - \mathbf{c}(\xi_p)
$$

$$
\mathbf{b}(\xi_p) = \text{inv\_dyn}(\mathbf{q}_p,\;\mathbf{q}'_p,\;\mathbf{q}''_p) - \mathbf{c}(\xi_p)
$$

其中 $\text{inv\_dyn}(\mathbf{q},\dot{\mathbf{q}},\ddot{\mathbf{q}})$ 为完整逆动力学（输出关节力矩向量）。干摩擦项单独叠加至 $\mathbf{c}$：$c_i \mathrel{+}= f_{s,i}\operatorname{sgn}(q'_{p,i})$。

**约束形式（正则线性约束）**

$$
\boldsymbol{\tau}_{\min} \leq \mathbf{a}(\xi_p)\,u + \mathbf{b}(\xi_p)\,x + \mathbf{c}(\xi_p) \leq \boldsymbol{\tau}_{\max}
$$

写成标准不等式形式（$2\times6$ 行/点，以矩阵 $\mathbf{F}$、$\mathbf{g}$ 表示）：

$$
\mathbf{F}\,\bigl(\mathbf{a}(\xi_p)\,u + \mathbf{b}(\xi_p)\,x + \mathbf{c}(\xi_p)\bigr) \leq \mathbf{g}
$$

$$
\mathbf{F} = \begin{bmatrix}\mathbf{I}_6 \\ -\mathbf{I}_6\end{bmatrix}, \quad
\mathbf{g} = \begin{bmatrix}\boldsymbol{\tau}_{\max} \\ -\boldsymbol{\tau}_{\min}\end{bmatrix}
$$

**与加速度约束的对比**

| 约束类型 | $u$ 系数 $\mathbf{a}(\xi)$ | $x$ 系数 $\mathbf{b}(\xi)$ | 是否需线性化 | 对应 TOPPRA 类 |
|---|---|---|---|---|
| 关节速度 | $\mathbf{0}$ | — | 否（直接 $x$ 上界） | `JointVelocityConstraint` |
| 关节加速度 | $\mathbf{q}'(\xi)$ | $\mathbf{q}''(\xi)$ | 否（精确线性） | `JointAccelerationConstraint` |
| TCP 速度 | $\mathbf{0}$ | — | 否（直接 $x$ 上界） | — |
| 关节力矩 | $\mathbf{M}\mathbf{q}'$ | $\mathbf{M}\mathbf{q}''+\mathbf{C}\mathbf{q}'\dot{s}$ | 否（精确线性） | `JointTorqueConstraint` |

力矩约束与加速度约束形式完全相同（均为 TOPPRA 的 `CanonicalLinear` 类型：$\mathbf{a}\,u + \mathbf{b}\,x + \mathbf{c} = v$，$\mathbf{F}\,v \leq \mathbf{g}$），无需引入近似，可直接添加到 LP 约束矩阵中。

**动力学参数的获取**

逆动力学函数 $\text{inv\_dyn}$ 由外部动力学库提供（如 Robotics Toolbox 的 `rne`、Pinocchio 的 `rnea`），在 §四 离线采样点处调用，与 IK/Jacobian 一并预计算，不增加 LP 在线计算量。

---

**电机 T-N 曲线：速度相关力矩约束（参考 Ardeshiri 等 2011）**

实际无刷直流电机的可用力矩并非常数：低速段受电流（热耗散）限制，力矩恒定为额定值 $\tau_{r,i}$；高速段受反电动势（back-EMF）限制，可用力矩随角速度近似线性降低，形成 T-N 曲线（见论文 Fig. 1）：

$$\tau_{i,\max}(\dot{q}_i) \approx \tau_{r,i} - k_{e,i}|\dot{q}_i|, \quad |\dot{q}_i| > \dot{q}_{b,i}$$

若直接将 $\dot{q}_i = q'_i(s)\dot{s}$ 代入仿射约束 $\tilde{T}\tau_i + W_i\dot{q}_i \leq P$，得：

$$\tilde{T}\tau_i + W_iq'_i\sqrt{b(s)} \leq P$$

含 $\sqrt{b}$ 非线性项，在 $(a,b)$ 空间不保凸（Ardeshiri 等 Eq. 15b）。

**凸化策略：在 $(\tau_i, \dot{q}_i^2)$ 空间内近似 T-N 边界**

T-N 上界曲线在 $(\tau_i, \dot{q}_i^2)$ 空间的形式为 $\tau_i = \tau_{r,i} - k_{e,i}\sqrt{\dot{q}_i^2}$，其对 $\dot{q}_i^2$ 是**凸函数**（$f'' > 0$）。凸函数在任意点的切线位于函数曲线**下方**，因此以切线族（仿射约束）对 T-N 边界做内近似，所得多面体可行域是真实可行域的**子集**（保守），同时是 $(τ_i, \dot{q}_i^2)$ 空间中的凸集（见论文 Fig. 3）：

$$T_{ij}\tau_i(\xi) + \overline{U}_{ij}\,\dot{q}_i^2(\xi) \leq P_{ij}, \quad j = 1, \ldots, m_i$$

其中 $m_i$ 为关节 $i$ 的 T-N 折线段数（典型 $m_i = 2$：恒转矩段 + 线性降速段）。参数 $(T_{ij}, \overline{U}_{ij}, P_{ij})$ 由 T-N 曲线各切触点确定：

| 段 $j$ | $T_{ij}$ | 物理含义 | $\overline{U}_{ij}$ | $P_{ij}$ |
|---|---|---|---|---|
| 1（上限，热约束） | $+1$ | 低速段恒定力矩上限 | $0$ | $\tau_{r,i}$ |
| 2（上限，back-EMF） | $+1$ | 高速段切线（切触点 $\dot{q}_{0,ij}$） | $k_{e,i}/(2\dot{q}_{0,ij})$ | $\tau_{r,i} - k_{e,i}\dot{q}_{0,ij}/2$ |
| 3（下限，热约束） | $-1$ | 低速段恒定力矩下限 | $0$ | $\tau_{r,i}$ |
| 4（下限，back-EMF） | $-1$ | 高速段切线 | $k_{e,i}/(2\dot{q}_{0,ij})$ | $\tau_{r,i} - k_{e,i}\dot{q}_{0,ij}/2$ |

**代入路径参数：联合动力学 + T-N 约束的 LP 行**

将 $\dot{q}_i^2 = q_i'^2(\xi_p)\,x$（其中 $x = \dot{s}^2 = \mathbf{B}\bar{\mathbf{x}}$）代入，同时将 $\tau_i = a_i u + b_i x + c_i$ 展开：

$$T_{ij}(a_i u + b_i x + c_i) + \overline{U}_{ij}\,q_i'^2(\xi_p)\,x \leq P_{ij}$$

整理为标准不等式形式（令 $u = \frac{1}{2}\mathbf{B}'\bar{\mathbf{x}}$，$x = \mathbf{B}\bar{\mathbf{x}}$）：

$$\boxed{\left[\frac{T_{ij}}{2}a_i(\xi_p)\,\mathbf{B}'(\xi_p) + \bigl(T_{ij}b_i(\xi_p) + \overline{U}_{ij}\,q_i'^2(\xi_p)\bigr)\,\mathbf{B}(\xi_p)\right]\bar{\mathbf{x}} \leq P_{ij} - T_{ij}c_i(\xi_p)}$$

**关键性质**：
- 右端项 $P_{ij} - T_{ij}c_i(\xi_p)$ 为常数（离线预计算）
- 左端对 $\bar{\mathbf{x}}$ 精确线性，无需任何近似
- 与纯动力学约束相比，仅 $x$ 系数增加了 $\overline{U}_{ij}q_i'^2$ 项（T-N 速度惩罚）
- 当 $\overline{U}_{ij}=0$ 时，退化为标准常数力矩约束

**退化关系**：若 T-N 曲线近似为常数力矩（$\overline{U}_{ij}=0$），则每关节上下限各 1 行（共 $2$ 行/关节），即 §5.2.5 中的原始 $\mathbf{F}(\mathbf{a}u+\mathbf{b}x+\mathbf{c})\leq\mathbf{g}$ 形式。T-N 模型每关节 $2m_i$ 行（典型 $2\times2=4$ 行/关节）。

#### 5.2.6 约束全集汇总（两阶段 LP）

| LP 阶段 | 约束类型 | 实现形式 | 每点行数 | 硬/软约束 | 是否精确线性 |
|---|---|---|---|---|---|
| 第一阶段 | 速度上限（关节 + TCP） | $x$ 上界（`xbound`） | 0（不进矩阵） | 硬 | 是 |
| 第一阶段 | 速度非负 | $x$ 下界（`xbound`） | 0（不进矩阵） | 硬 | 是 |
| 第一阶段 | 关节加速度（上/下） | $\mathbf{a}\,u+\mathbf{b}\,x \leq \mathbf{g}$ | $2\times6=12$ | 硬 | 是（精确） |
| 第一阶段 | 关节力矩 T-N（上/下，每关节 $m_i$ 段） | $[\frac{T_{ij}}{2}a_i\mathbf{B}' + (T_{ij}b_i+\overline{U}_{ij}q_i'^2)\mathbf{B}]\bar{\mathbf{x}} \leq P_{ij}-T_{ij}c_i$ | $2m_i\times6$（典型 $m_i=2$：$24$行） | 硬 | 是（精确） |
| 第二阶段（叠加） | 关节 Jerk（上/下） | $\mathbf{A}_j\,\mathbf{x} \leq \mathbf{b}_j$ | $2\times6=12$ | 软 | 是（线性化） |

速度约束（关节 + TCP）以 $x$ 的上下界 `xbound` 传入求解器，不占用约束矩阵行数。第一阶段矩阵约束：$2(\text{速度}) + 12(\text{加速度}) + 2m\times6(\text{T-N力矩})$ 行/点（$m=1$常数力矩：26行；$m=2$ T-N：38行）；第二阶段再叠加 $12$（Jerk）行。

---

### 5.3 等式约束（速度与切向加速度连续性）

等式约束保证窗口内相邻段间以及窗口起/末端边界处的速度和切向加速度连续。

#### 5.3.1 连续性的物理意义

相邻段 $k$ 末端和段 $k+1$ 起端在连接点处要求：

$$
w_k(1) = w_{k+1}(0) \quad\Rightarrow\quad \mathbf{B}(1)\,\mathbf{x}_k - \mathbf{B}(0)\,\mathbf{x}_{k+1} = 0
$$

$$
w'_k(1) = w'_{k+1}(0) \quad\Rightarrow\quad \mathbf{B}'(1)\,\mathbf{x}_k - \mathbf{B}'(0)\,\mathbf{x}_{k+1} = 0
$$

第一个方程保证 $\dot{u}^2$（参数速度）连续，第二个保证 $\ddot{u} = \frac{1}{2}w'$（切向加速度）连续，两者合保证整条轨迹 $C^1$ 平滑。

#### 5.3.2 窗口起端边界条件

| 场景 | $v_0^2$（$= w(0)$） | $2a_{t,0}$（$= w'(0)$） |
|---|---|---|
| 全局起点（第一窗口） | $0$（静止出发） | $0$ |
| 中间窗口（从上一窗口提取） | $\mathbf{B}(1)\cdot\mathbf{x}_{k_\text{prev}}$ | $\mathbf{B}'(1)\cdot\mathbf{x}_{k_\text{prev}}$ |

其中 $\mathbf{x}_{k_\text{prev}}$ 是上一窗口**提交段**（第1段）的已求 B 样条系数。下一窗口起端约束：

$$
\boxed{\mathbf{B}(0)\,\mathbf{x}_{k+1} = \mathbf{B}(1)\,\mathbf{x}_k} \quad \mathbf{B}'(0)\,\mathbf{x}_{k+1} = \mathbf{B}'(1)\,\mathbf{x}_k
$$

> 对应 `FeedratePlanning_LP.m`：`ctx.v_0 = sqrt(continuity(1,:)*Coeff(:,1))`，`ctx.at_0 = 0.5*continuity(2,:)*Coeff(:,1)`

#### 5.3.3 窗口末端边界条件（MPC 保守停止）

**中间窗口**：强制末端速度和加速度为零（MPC 保守停止策略），LP 据此提前规划减速；**实际仅提交第一段**，下一窗口重规划后速度连续过渡，整条轨迹不会真正停止：

$$
\mathbf{B}(1)\,\mathbf{x}_W = 0, \quad \mathbf{B}'(1)\,\mathbf{x}_W = 0
$$

**最后窗口**：末端约束改为实际终点（机器人在目标点停止），等式右端同为零，但所有 $W$ 段均提交执行。

#### 5.3.4 完整等式约束矩阵

窗口内 $W$ 段，共 $W+1$ 个连接节点（含首尾），每节点 2 行，合计 $\mathbf{A}_\text{eq} \in \mathbb{R}^{2(W+1)\times NW}$：

$$
\mathbf{A}_\text{eq} = \begin{bmatrix}
+\mathbf{B}(0) & \mathbf{0} & \cdots & \mathbf{0} \\
+\mathbf{B}'(0) & \mathbf{0} & \cdots & \mathbf{0} \\[4pt]
+\mathbf{B}(1) & -\mathbf{B}(0) & \cdots & \mathbf{0} \\
+\mathbf{B}'(1) & -\mathbf{B}'(0) & \cdots & \mathbf{0} \\
& \ddots & \ddots & \vdots \\
\mathbf{0} & \cdots & +\mathbf{B}(1) & -\mathbf{B}(0) \\
\mathbf{0} & \cdots & +\mathbf{B}'(1) & -\mathbf{B}'(0) \\[4pt]
\mathbf{0} & \cdots & \mathbf{0} & +\mathbf{B}(1) \\
\mathbf{0} & \cdots & \mathbf{0} & +\mathbf{B}'(1)
\end{bmatrix},\quad
\mathbf{b}_\text{eq} = \begin{bmatrix}
v_0^2 \\ 2a_{t,0} \\[4pt] 0 \\ 0 \\ \vdots \\ 0 \\ 0 \\[4pt] 0 \\ 0
\end{bmatrix}
$$

行计数：$\underbrace{2}_{\text{起端}} + \underbrace{2(W-1)}_{\text{段间}} + \underbrace{2}_{\text{末端}} = 2(W+1)$。

---

### 5.4 两阶段 LP 求解策略

两个阶段共用同一个等式约束 $(\mathbf{A}_\text{eq}, \mathbf{b}_\text{eq})$，不等式约束逐步叠加。对应 `FeedratePlanning_LP.m`。

#### 5.4.1 第一阶段 LP（速度 + 加速度 + 力矩，精确线性）

求解：

$$
\min_\mathbf{x} \;-\mathbf{f}^\top\mathbf{x}, \quad \text{s.t.}\;
\mathbf{A}_\text{ineq}\mathbf{x} \leq \mathbf{b}_\text{ineq},\;
\mathbf{A}_\text{eq}\mathbf{x} = \mathbf{b}_\text{eq},\;
\mathbf{x} \geq 0
$$

**不等式约束**：§5.2（速度上限 + 速度非负 + 加速度上下限 + 力矩上下限），全部精确线性——加速度因 $\ddot{u} = \frac{1}{2}w'$ 精确线性；力矩因科氏项对 $x=\dot{s}^2$ 天然线性，同样无需近似。共 $2 + 12 + 12 = 26$ 行/点（6轴机器人）。

力矩约束的 LP 行形式（T-N 曲线，第 $j$ 段，代入 $u = \frac{1}{2}\mathbf{B}'\bar{\mathbf{x}}$，$x = \mathbf{B}\bar{\mathbf{x}}$，$\dot{q}_i^2 = q_i'^2\mathbf{B}\bar{\mathbf{x}}$）：

$$
\left[\frac{T_{ij}}{2}a_i(\xi_p)\,\mathbf{B}'(\xi_p) + \bigl(T_{ij}b_i(\xi_p) + \overline{U}_{ij}q_i'^2(\xi_p)\bigr)\mathbf{B}(\xi_p)\right]\bar{\mathbf{x}} \leq P_{ij} - T_{ij}c_i(\xi_p)
$$

常数力矩退化情形（$\overline{U}_{ij}=0$，$T_{ij}=\pm1$，$P_{ij}=\tau_{i,\max/\min}$）即为 $[\frac{1}{2}a_i\mathbf{B}'+b_i\mathbf{B}]\bar{\mathbf{x}}\leq\tau_{i,\max}-c_i$。

**松弛变量**：添加全局松弛 $s \geq 0$（惩罚项加入目标函数），防止约束不可行导致无解。速度/加速度/力矩约束均保持硬约束（不在松弛索引 `indSlack` 中）。

**零速松弛迭代**：若路径起端或末端为零速（`ctx.zero_start/zero_end`），LP 可能因约束过紧失败；此时逐步放松 `ConstJerk` 参数（每次除以8，最多15次）重试。

得到解 $\mathbf{x}^*$，提取参考速度 $\dot{u}_\text{ref}(\xi_p) = \sqrt{\mathbf{B}(\xi_p)\mathbf{x}^*}$。

#### 5.4.2 第二阶段 LP（仅叠加 Jerk 约束，线性化近似）

**Jerk 展开**（精确）：

$$
\dddot{q}_i = \dot{u}\!\left[q'''_i w + \tfrac{3}{2}q''_i w' + \tfrac{1}{2}q'_i w''\right]
$$

含 $\dot{u} = \sqrt{w}$ 非线性因子。冻结 $\dot{u} \approx \dot{u}_\text{ref}(\xi_p)$（第一阶段解），Jerk 变为 $\mathbf{x}$ 的线性函数：

$$
\dddot{q}_i \approx \dot{u}_\text{ref}(\xi_p)\underbrace{\Bigl[q'''_i(\xi_p)\,\mathbf{B} + \tfrac{3}{2}q''_i(\xi_p)\,\mathbf{B}' + \tfrac{1}{2}q'_i(\xi_p)\,\mathbf{B}''\Bigr]}_{\text{Jerk}_i(p,:)}\,\mathbf{x}_k
$$

Jerk 约束（上/下限）：$\pm\text{Jerk}_i(p,:)\,\mathbf{x}_k \leq j_{i,\max}$，叠加到第一阶段的 $\mathbf{A}_\text{ineq}$ 上，再次求解：

$$
\mathbf{A}_\text{tot} = \begin{bmatrix}\mathbf{A}_\text{ineq} \\ \mathbf{A}_\text{jerk}\end{bmatrix}, \quad
\mathbf{b}_\text{tot} = \begin{bmatrix}\mathbf{b}_\text{ineq} \\ \mathbf{b}_\text{jerk}\end{bmatrix}
$$

**Jerk 约束的软化**：Jerk 约束行进入 `indSlack`（软约束），允许少量违反——原因是 Jerk 行由线性化近似得到，存在近似误差，若保持硬约束可能引入虚假不可行；而速度/加速度硬约束保证物理安全性。

#### 5.4.3 两阶段对比

| 阶段 | 不等式约束 | 是否精确线性 | 等式约束 | Jerk 是否包含 |
|---|---|---|---|---|
| 第一阶段 | 速度 + 加速度 + 力矩 | 是（全部精确） | $\mathbf{A}_\text{eq}\mathbf{x}=\mathbf{b}_\text{eq}$ | 否 |
| 第二阶段 | 速度 + 加速度 + 力矩 + Jerk | 近似（仅Jerk线性化） | 同上（不变） | 是（软约束） |

两个阶段**复用同一目标函数和等式约束**，仅不等式约束矩阵在第一阶段基础上叠加 Jerk 行。力矩约束精确线性，属于第一阶段；Jerk 含 $\sqrt{w}$ 非线性因子，需冻结 $\dot{u}_\text{ref}$ 线性化后叠加为软约束。第二阶段结果可能比第一阶段更保守（速度略低），换取 Jerk 满足。

> 对应代码：`FeedratePlanning_LP.m` 第39~68行为第一阶段，第72~101行为第二阶段（`if ctx.cfg.opt.USE_JERK_CONSTRAINTS`）。

---

### 5.5 滑动窗口 MPC 策略

#### 5.5.1 窗口化动机

全路径 $K$ 段同时纳入 LP，约束矩阵规模 $O(K \times N)$，长路径（$K > 500$）计算时间不可接受。**滑动窗口 MPC** 策略：每次仅对 $W \ll K$ 段求解，**仅提交第一段**，窗口向前滑动一段后重规划。直接复用 OpenCN 的 `FeedratePlanning_LP.m` 框架。

#### 5.5.2 窗口滑动流程

```
全路径（K 段）：[seg1 | seg2 | ... | segK]

窗口 1（W=5）：[seg1  seg2  seg3  seg4  seg5]
                 ↑提交 seg1 → 提取末端 v₀², at₀ 传递给窗口2
窗口 2：        [seg2  seg3  seg4  seg5  seg6]
                 ↑提交 seg2 → 提取末端边界...
...
最后窗口：      [seg_{K-W+1} ... seg_K]
                 ↑提交全部剩余段（末端为实际终点零速）
```

#### 5.5.3 窗口大小 $W$ 的选择

$W$ 需满足前瞻距离 $\geq$ 最大制动距离：

$$
\boxed{W \cdot \bar{h} \;\geq\; \frac{\dot{q}_{\max}^2}{2\,\ddot{q}_{\max}}}
$$

$\bar{h}$ 为平均段弧长。典型 UR5（$\dot{q}_{\max}=3.15$ rad/s，$\ddot{q}_{\max}=40$ rad/s²，$\bar{h}=0.02$ rad）：$d_\text{brake} = 3.15^2/80 \approx 0.12$ rad，$W \geq 6$，建议取 $W=15\sim30$。

#### 5.5.4 约束矩阵维度（每个窗口）

$$
\mathbf{A}_\text{ineq} \in \mathbb{R}^{26\,MW \;\times\; NW}, \quad
\mathbf{A}_\text{eq} \in \mathbb{R}^{2(W+1) \;\times\; NW}
$$

行数说明：每点 $2$（速度上限/非负）$+ 12$（加速度上下限）$+ 12$（力矩上下限）$= 26$ 行（第一阶段）；第二阶段叠加 Jerk 后：$\mathbf{A}_\text{tot} \in \mathbb{R}^{38\,MW \;\times\; NW}$，即每点再增加 $2\times6=12$ 行 Jerk 约束。

---

## 六、实现架构

### 6.1 模块划分

```
robot_topp.m（主入口）
│
├── robot_g2_smooth.m                ─── §2.5：G2 路径平滑（新建，薄包装）
│   │   对每对相邻段调用 calcTransition，组装增广 CurvStruct 数组
│   ├── [复用] calcTransition()      完整 G2 过渡流程（common/Feedopt）
│   │   ├── [复用] LengthCurv()     计算段弧长（= zone 候选上限）
│   │   ├── [复用] cutCurvStruct()  截短相邻段两端（各截 CutOff）
│   │   ├── [复用] EvalCurvStruct() 评估截短端点处 r0D/r1D/r2D
│   │   │       含 robot_mode 分支 → EvalRobotCurv（Line/Helix）
│   │   ├── [复用] G2_Hermite_Interpolation_nAxis()
│   │   │       Frenet 框架 + α0/α1 最优化 → 五次多项式系数 p5
│   │   ├── [复用] constrTransP5Struct()  构造 TransP5 曲线段
│   │   └── [复用] check_continuity()    G2 连续性验证（位置/切线/曲率）
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
%   cart_path   : CurvStruct 数组（直线/圆弧段，由 RobotCurvStruct/RobotArcSegment 构造）
%   robot_params: 机器人参数（DH, q_lim, vmax, amax, jmax, W, eps_pos, eps_ori, delta_max）

%% 初始化机器人上下文（复用 initRobotPlan）
cfg = RobotDefaultConfig(robot_params);
kin = RobotKinematics(cfg.dh_params, cfg.robot_config, cfg.q_lim);
ctx = initRobotPlan(cfg, kin);   % 含 B 样条基、ctx.robot_mode=true
% ctx.cfg.CutOff 由 FeedoptDefaultConfig 设定，可被 robot_params.delta_max 覆盖
if isfield(robot_params, 'delta_max')
    ctx.cfg.CutOff = robot_params.delta_max;
end

%% 预处理一：G2 路径平滑（§2.5）
% robot_g2_smooth 对每对相邻段调用 calcTransition（common/Feedopt），
% 在交接点两端各截去 CutOff（= zone 距离），插入 TransP5 过渡段。
% 输出：增广 CurvStruct 数组（原始截短段 + TransP5 段交替排列）
cart_path_g2 = robot_g2_smooth(ctx, cart_path, robot_params.delta_max);

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

| OpenCN 组件 | 所在目录 | 复用方式 |
|---|---|---|
| `calcTransition` | `common/Feedopt/` | **直接调用**（完整 G2 过渡流程，含截短+插值+验证） |
| `G2_Hermite_Interpolation_nAxis` | `common/Feedopt/` | **直接调用**（Frenet 框架最优 α0/α1 求解，§2.5.2） |
| `cutCurvStruct` | `common/Feedopt/` | **直接调用**（弧长截短，实现 zone 距离） |
| `LengthCurv` | `common/Feedopt/` | **直接调用**（计算段弧长，用于 zone 上限判断） |
| `EvalCurvStruct` | `common/Feedopt/` | **直接调用**（含 robot_mode 分支 → EvalRobotCurv） |
| `constrTransP5Struct` | `common/types/` | **直接调用**（构造 TransP5 过渡曲线结构体） |
| `c_simplex`（LP 求解器） | `common/Feedopt/` | 直接复用，接口不变 |
| `FeedratePlanning_LP` | `common/Feedopt/` | 直接复用（LP 两阶段策略不变） |
| `resample2file`（重采样） | `common/Feedopt/` | 直接复用（输出已是关节空间） |
| `buildConstr.m` | `common/Feedopt/` | **替换**为 `build_joint_constr.m`（系数来源不同） |
| 滑动窗口 MPC | `common/Feedopt/` | 直接复用（窗口 = 连续若干段） |

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

LP 约束中速度系数误差 $C_1 h^4$，加速度系数误差 $C_2 h^3$。实践中取 $h$ 使得 $C_2 h^3 < 0.01 \cdot \ddot{q}_{\max}$（加速度约束误差 $< 1\%$）。

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

### 8.5 有效速度上限（含笛卡尔 TCP 约束）

$$
f_\text{max}(\xi_p) = \min\!\left(
\min_{i=1}^{6}\frac{\dot{q}_{i,\max}^2}{q'_i(\xi_p)^2},\;\;
\frac{v_\text{tcp,max}^2}{c_v(\xi_p)^2},\;\;
\frac{\omega_\text{tcp,max}^2}{c_\omega(\xi_p)^2}
\right)
$$

### 8.5b 力矩约束系数（第一阶段，精确线性）

通过三次逆动力学调用精确分离系数（对照 TOPPRA `JointTorqueConstraint`）：

$$
\mathbf{c}(\xi_p) = \text{inv\_dyn}(\mathbf{q}_p, \mathbf{0}, \mathbf{0})
$$

$$
\mathbf{a}(\xi_p) = \text{inv\_dyn}(\mathbf{q}_p, \mathbf{0}, \mathbf{q}'_p) - \mathbf{c}(\xi_p)
$$

$$
\mathbf{b}(\xi_p) = \text{inv\_dyn}(\mathbf{q}_p, \mathbf{q}'_p, \mathbf{q}''_p) - \mathbf{c}(\xi_p)
$$

约束形式——**标准常数力矩**（每关节上/下各 1 行，共 12 行）：

$$
\mathbf{F}\,\bigl(\mathbf{a}(\xi_p)\,u + \mathbf{b}(\xi_p)\,x + \mathbf{c}(\xi_p)\bigr) \leq \mathbf{g}, \quad
\mathbf{F} = \begin{bmatrix}\mathbf{I}_6\\-\mathbf{I}_6\end{bmatrix},\quad
\mathbf{g} = \begin{bmatrix}\boldsymbol{\tau}_{\max}\\-\boldsymbol{\tau}_{\min}\end{bmatrix}
$$

约束形式——**T-N 曲线速度相关力矩**（每关节 $j$ 段，代入 $\dot{q}_i^2 = q_i'^2 x$，共 $2m_i$ 行）：

$$
\left[\frac{T_{ij}}{2}a_i(\xi_p)\,\mathbf{B}'(\xi_p) + \bigl(T_{ij}b_i(\xi_p) + \overline{U}_{ij}q_i'^2(\xi_p)\bigr)\mathbf{B}(\xi_p)\right]\bar{\mathbf{x}} \leq P_{ij} - T_{ij}c_i(\xi_p)
$$

T-N 参数 $(T_{ij}, \overline{U}_{ij}, P_{ij})$ 标定（切触点 $\dot{q}_{0,ij}$ 处的切线，$k_{e,i} = \tau_{r,i}/(\dot{q}_{max,i}-\dot{q}_{b,i})$）：

$$
T_{ij} = \pm1, \quad
\overline{U}_{ij} = \frac{k_{e,i}}{2\dot{q}_{0,ij}}, \quad
P_{ij} = \tau_{r,i} - \frac{k_{e,i}\dot{q}_{0,ij}}{2}
$$

科氏项 $\mathbf{C}(\mathbf{q},\mathbf{q}'\dot{s})\mathbf{q}'\dot{s}^2$ 天然对 $x$ 线性，T-N 项 $\overline{U}_{ij}q_i'^2 x$ 同样对 $x$ 线性，故两者合并后的约束**无需线性化**，直接精确成立，归属第一阶段 LP。

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

### 8.9 完整解耦阶段总结

| 阶段 | 名称 | 输入 | 输出 | 核心操作 |
|---|---|---|---|---|
| 0 | G2 路径平滑 | 分段路径（G0/G1） | G2 连续路径 | `calcTransition` → TransP5 过渡段 |
| 1 | 自适应离散化 | G2 路径 $r(s)$ | $M$ 个采样点 $\{t_m\}$ | 曲率驱动步长 |
| 2 | 关节空间预计算 | $\{r(t_m)\}$ | $\{q_m, q'_m, q''_m, q'''_m, \mathbf{M}_m, \mathbf{C}_m, \mathbf{g}_m, \mathbf{J}_m\}$ | IK + Jacobian + 动力学 |
| 3 | 两阶段 LP（每窗口） | 预计算数据 + 边界 | $w^*(\xi)$ → $q(t), \dot{q}(t), \ddot{q}(t)$ | 第一阶段（速度+加速度+力矩，精确线性）+ 第二阶段（仅Jerk，线性化软约束） |

---

## 九、完整算法流程图

### 9.1 总体流程（离线预处理 + 在线规划）

```
┌─────────────────────────────────────────────────────────────────────┐
│                         输 入                                        │
│  笛卡尔路径段数组（直线/圆弧 CurvStruct），机器人参数                   │
│  （DH参数、q_lim、vmax、amax、jmax、τ_max、v_tcp_max、ω_tcp_max）     │
└───────────────────────────┬─────────────────────────────────────────┘
                            │
            ════════════════╪════════════════
            ║  阶段 0：G2 路径平滑（§2.5）  ║
            ════════════════╪════════════════
                            │
        ┌───────────────────▼───────────────────┐
        │  对每对相邻段 (curv_j, curv_{j+1})：   │
        │  ① LengthCurv → L1, L2               │
        │  ② delta = min(CutOff, L1/3, L2/3)   │
        │  ③ L1 < 3·delta 或 L2 < 3·delta?      │
        │     是 → 跳过（保留G1角点）            │
        │     否 → cutCurvStruct 截短两端        │
        │  ④ EvalCurvStruct → r0D0/r1D/r2D      │
        │                      r1D0/r1D/r2D     │
        │  ⑤ G2_Hermite_Interpolation_nAxis     │
        │     → p5系数，status                   │
        │     status∈{1,6}? 是 → constrTransP5  │
        │                   否 → 保留G1角点      │
        │  ⑥ check_continuity 验证               │
        └───────────────────┬───────────────────┘
                            │
              输出：G2连续路径（截短段+TransP5段交替）
                            │
            ════════════════╪════════════════════════
            ║  阶段 1：笛卡尔路径自适应离散化（§2.1-2.4）║
            ════════════════╪════════════════════════
                            │
        ┌───────────────────▼───────────────────┐
        │  t = 0，SampleList = {0}              │
        │  while t < t_end:                     │
        │    ① 计算位置曲率 κ_pos(t)             │
        │       计算姿态曲率 κ_ori(t)            │
        │    ② Δs_pos = sqrt(8·ε_pos / κ_pos)  │
        │       Δs_ori = sqrt(8·ε_ori / κ_ori)  │
        │    ③ Δs = clamp(min(Δs_pos,Δs_ori),  │
        │                  Δs_min, Δs_max)      │
        │    ④ t_next = t + Δs / |r'(t)|       │
        │       SampleList.append(t_next)       │
        └───────────────────┬───────────────────┘
                            │
              输出：M 个采样参数 {t_m}，{r(t_m)}
                            │
            ════════════════╪══════════════════════════════
            ║  阶段 2：关节空间导数预计算（§三 + 动力学）  ║
            ════════════════╪══════════════════════════════
                            │
        ┌───────────────────▼─────────────────────────────┐
        │  for m = 1 .. M:                                │
        │    ① IK: q_m = IK(r(t_m))                      │
        │          选最近解，保持构型连续                    │
        │    ② J_m = geometric_jacobian(q_m)              │
        │          rcond(J_m) < 1e-6 → DLS (λ=0.05)      │
        │    ③ q'_m  = J_m⁻¹ · r'(t_m)    （一阶导）     │
        │    ④ q''_m = J_m⁻¹·r''(t_m) - J_m⁻¹·dJ/du·q'_m│
        │    ⑤ q'''_m = J_m⁻¹·r'''(t_m) - ...（三阶导）  │
        │    ⑥ 预计算约束系数：                            │
        │       · c_v(t_m)  = |J_v·q'_m|  （TCP线速度）   │
        │       · c_ω(t_m)  = |J_ω·q'_m|  （TCP角速度）   │
        │       · M_m = inertia(q_m)      （惯性矩阵）    │
        │       · C_m = coriolis(q_m,q'_m)（科氏矩阵）    │
        │       · c_m = inv_dyn(q_m,0,0)  （重力+摩擦）   │
        │       · a_m = inv_dyn(q_m,0,q'_m) - c_m（惯性项）│
        │       · b_m = inv_dyn(q_m,q'_m,q''_m) - c_m    │
        │               （科氏+惯性二阶项）                │
        └───────────────────┬─────────────────────────────┘
                            │
              输出：{q_m, q'_m, q''_m, q'''_m,
                     c_v_m, c_ω_m, a_m, b_m, c_m}
                            │
            ════════════════╪══════════════════════════════════
            ║  阶段 3：滑动窗口 MPC + 两阶段 LP（§五）      ║
            ════════════════╪══════════════════════════════════
                            │
        ┌───────────────────▼────────────────────────────────┐
        │  初始化：k=1, v₀²=0, at₀=0, result=[]            │
        │                                                    │
        │  while k ≤ K:                                      │
        │    W_cur = min(W, K-k+1)    （当前窗口实际段数）   │
        │                                                    │
        │  ┌─ 构造等式约束（§5.3）─────────────────────────┐ │
        │  │  Aeq·x = beq                                  │ │
        │  │  行结构：起端(v₀²,2at₀) + 段间(0,0) + 末端(0,0)│ │
        │  └────────────────────────────────────────────────┘ │
        │                                                    │
        │  ┌─ 第一阶段 LP（§5.4.1）────────────────────────┐ │
        │  │  构造 A_ineq（26行/点×M×W_cur）：              │ │
        │  │    · 速度上限：B·x ≤ f_max（含TCP速度约束）   │ │
        │  │    · 速度非负：-B·x ≤ 0                       │ │
        │  │    · 加速度±：Acc_i·x ≤ ±amax_i（精确）      │ │
        │  │    · 力矩±：[0.5·a_i·B' + b_i·B]·x ≤         │ │
        │  │              τmax_i - c_i（精确，硬）          │ │
        │  │  调用 buildConstr → [A,b,Aeq,beq]             │ │
        │  │  添加松弛变量，调用 c_simplex                  │ │
        │  │  LP失败且零速端? → relax_initial重试（≤15次）  │ │
        │  │  成功 → 得到 x*，计算 ůref = sqrt(B·x*)       │ │
        │  └────────────────────────────────────────────────┘ │
        │                  │                                  │
        │                  ↓ x* 可用                          │
        │  ┌─ 第二阶段 LP（§5.4.2）────────────────────────┐ │
        │  │  基于 ůref 线性化，叠加软约束（indSlack）：     │ │
        │  │    · Jerk ±：Jerk_i·x ≤ ±jmax_i（软）        │ │
        │  │  A_tot = [A_ineq; A_jerk]                     │ │
        │  │  调用 buildConstrJerk → Aj                     │ │
        │  │  调用 c_simplex（含软化松弛）                   │ │
        │  │  成功 → 得到最终 x**                            │ │
        │  └────────────────────────────────────────────────┘ │
        │                  │                                  │
        │                  ↓ x** 已求                         │
        │    提交第一段（段 k）：                              │
        │      · resampleCurv(x**[:,1]) → q(t),qd(t),qdd(t) │
        │      · result.append(当前段轨迹)                    │
        │    提取下一窗口边界（§5.3.2）：                     │
        │      · v₀² = B(1)·x**[:,1]                        │
        │      · at₀ = 0.5·B'(1)·x**[:,1]                  │
        │    k = k + 1，窗口前滑                              │
        └───────────────────┬────────────────────────────────┘
                            │
            ════════════════╪═══════════
            ║  输 出                   ║
            ════════════════╪═══════════
                            │
        ┌───────────────────▼────────────┐
        │  q(t)   ：[6×T] 关节角轨迹     │
        │  qd(t)  ：[6×T] 关节速度轨迹   │
        │  qdd(t) ：[6×T] 关节加速度轨迹 │
        │  全程 C¹ 连续，满足：          │
        │    · 关节速度/加速度/Jerk 约束  │
        │    · TCP 线速度/角速度约束      │
        │    · 关节力矩约束（电机额定）   │
        └────────────────────────────────┘
```

### 9.2 约束构建细节流程（阶段3 内部）

```
每个 LP 离散点 ξ_p（共 M×W_cur 个点）：

  已知（预计算）：q'(ξ_p), q''(ξ_p), q'''(ξ_p)
                  c_v(ξ_p), c_ω(ξ_p)
                  a(ξ_p), b(ξ_p), c(ξ_p)  [力矩系数：惯性/科氏/重力]
                  B(ξ_p), B'(ξ_p), B''(ξ_p)  [B样条基]

  ─────────────── 第一阶段约束行（精确线性，硬约束）──
  行 1   速度上限：   B(ξ_p) · x   ≤  f_max(ξ_p)
                  f_max = min(vmax_i²/q'_i², v_tcp²/c_v², ω_tcp²/c_ω²)

  行 2   速度非负：  -B(ξ_p) · x   ≤  0

  行 3~8  加速度上限：  Acc_i · x  ≤  amax_i
  行 9~14 加速度下限： -Acc_i · x  ≤  amax_i
             Acc_i = q''_i·B + 0.5·q'_i·B'  [精确线性]

  行 15~20 T-N力矩上限（j段）：
             [(T_ij/2)·a_i·B' + (T_ij·b_i + Ū_ij·q'_i²)·B]·x ≤ P_ij - T_ij·c_i
             （T_ij=+1，Ū_ij=k_e/(2q̇_0)，P_ij=τ_r-k_e·q̇_0/2）

  行 21~26 T-N力矩下限（j段）：
             [(T_ij/2)·a_i·B' + (T_ij·b_i + Ū_ij·q'_i²)·B]·x ≤ P_ij - T_ij·c_i
             （T_ij=-1，对称参数；m_i段共2m_i行/关节，典型m_i=2→24行）

             Ū_ij=0时退化为常数力矩：[±0.5·a_i·B' ± b_i·B]·x ≤ ±τmax_i ∓ c_i

  ─────────────── 第二阶段追加（软约束）────────────
  行 27~32 Jerk 上限：  Jerk_i · x  ≤  jmax_i
  行 33~38 Jerk 下限： -Jerk_i · x  ≤  jmax_i
             Jerk_i = ůref·[q'''_i·B + 1.5·q''_i·B' + 0.5·q'_i·B'']

  ─────────────── 等式约束（与离散点无关）──────────
  行 1~2   窗口起端：  B(0)·x₁ = v₀²，  B'(0)·x₁ = 2·at₀
  行 3~4   段间连续：  B(1)·xₖ = B(0)·x_{k+1}（速度²）
                       B'(1)·xₖ = B'(0)·x_{k+1}（切向加速度）
  行 end-1~end 末端：  B(1)·x_W = 0，  B'(1)·x_W = 0
```

### 9.3 数据依赖关系图（阶段间的数据流）

```
  robot_params                    cart_path（CurvStruct数组）
  (DH, q_lim,                          │
   vmax, amax,                          │
   jmax, τmax,              ┌───────────▼──────────┐
   v_tcp_max,               │  阶段0：G2路径平滑     │
   ω_tcp_max,               │  calcTransition       │
   delta_max)               │  G2_Hermite + TransP5 │
        │                   └───────────┬──────────┘
        │                               │ path_g2（G2连续）
        │                   ┌───────────▼──────────┐
        │                   │  阶段1：自适应离散化   │
        │                   │  κ驱动步长 → {t_m}   │
        │                   └───────────┬──────────┘
        │                               │ {t_m, r(t_m)}（M点）
        ├──────────────────►┌───────────▼──────────┐
        │  DH, q_lim        │  阶段2：关节空间预计算 │
        │  vmax(speed ck)   │  IK→q_m              │
        │                   │  Jacobian→q'_m,q''_m  │
        │                   │  Dynamics→a_m,b_m,c_m │
        │                   │  TCP→c_v_m, c_ω_m     │
        │                   └───────────┬──────────┘
        │                               │ JointPathData（M点预计算值）
        ├──────────────────►┌───────────▼──────────┐
        │  vmax,amax,jmax   │  阶段3：滑动窗口LP    │
        │  τmax,v_tcp_max   │  ┌──────────────────┐ │
        │  ω_tcp_max, W     │  │ 等式约束（§5.3）  │ │
        │                   │  │ 第一阶段LP（§5.4.1)│ │
        │                   │  │ 速度+加速度+力矩  │ │
        │                   │  │ （全部硬约束）    │ │
        │                   │  └────────┬─────────┘ │
        │                   │           │ x*,ůref   │
        │                   │  ┌────────▼─────────┐ │
        │                   │  │ 第二阶段LP（§5.4.2)│ │
        │                   │  │ +Jerk（软，线性化）│ │
        │                   │  └────────┬─────────┘ │
        │                   │           │ x**       │
        │                   └───────────┬──────────┘
        │                               │ 提交段1，边界传递
        │                               ▼
        │                    q(t), qd(t), qdd(t)
        │                    满足全部约束
        └──────────────────────────────────┘

  [前向数据流：每箭头代表一次数据传递，无反馈循环（全离线预计算）]
  [唯一在线循环：滑动窗口 MPC 的窗口前滑（k=1..K），但每次LP独立求解]
```

---

*文档版本：v1.5 | 日期：2026-05-20 | 更新：§5.2.5 新增电机 T-N 曲线速度相关力矩约束（Ardeshiri 等 2011），凸化策略（$(\tau_i,\dot{q}_i^2)$ 空间切线内近似），合并动力学+T-N 的统一 LP 行公式；§5.2.6/§5.4.1/§8.5b/§9.2 同步更新行数与公式；常数力矩作为 $\overline{U}_{ij}=0$ 的特例保留兼容*
