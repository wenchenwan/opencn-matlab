# 六轴工业机器人时间最优轨迹规划方案

基于 OpenCN LP 进给率优化框架的扩展设计

---

## 目录

1. [问题定义与目标](#一问题定义与目标)
2. [数学基础：Jacobian 链式展开](#二数学基础jacobian-链式展开)
3. [LP 约束体系](#三lp-约束体系)
4. [约束矩阵构造细节](#四约束矩阵构造细节)
5. [奇异点处理](#五奇异点处理)
6. [实现架构](#六实现架构)
7. [数值考虑](#七数值考虑)
8. [测试验证方案](#八测试验证方案)
9. [与现有 CNC 框架的差异对比](#九与现有-cnc-框架的差异对比)
10. [简化方案：关节空间规划 + 笛卡尔速度约束](#十简化方案关节空间规划--笛卡尔速度约束)

---

## 一、问题定义与目标

### 1.1 优化目标

给定笛卡尔空间路径（或关节空间路径点序列），在满足全部运动学约束的前提下，**最小化轨迹总执行时间**：

$$
\min \; T = \int_0^L \frac{ds}{v(s)} \quad \text{（路径总时间）}
$$

等价于最大化参数速度积分（LP 目标函数）：

$$
\min \; -\int_0^1 \dot{u}^2(u) \, du \quad \text{（最大化 } \dot{u}^2 \text{ 的积分，近似最小化时间）}
$$

### 1.2 约束分类

| 约束类型 | 数学表达 | 空间 | 备注 |
|---|---|---|---|
| TCP 笛卡尔速度上限 | $v_\text{tcp} \leq v_\text{cart,max}$ | 笛卡尔 | 工艺/安全要求 |
| 关节速度 | $\lvert\dot{q}_i\rvert \leq \dot{q}_{i,\max}$ | 关节 | 电机/驱动器限制 |
| 关节加速度 | $\lvert\ddot{q}_i\rvert \leq \ddot{q}_{i,\max}$ | 关节 | 电机电流/扭矩限制 |
| 关节 Jerk | $\lvert\dddot{q}_i\rvert \leq j_{i,\max}$ | 关节 | 振动/冲击抑制 |
| 速度非负 | $\dot{u}^2 \geq 0$ | 参数 | LP 可行性 |
| 起/末端边界 | $v=0,\; a_t=0$（零速零加速） | 两者 | 从静止出发、静止停止 |
| 中间连接点 | $v$ 和 $a_t$ 连续（$C^1$） | 两者 | 跨窗口平滑 |

### 1.3 符号约定

| 符号 | 含义 | 维度 |
|---|---|---|
| $u \in [0,1]$ | 归一化路径参数（每段独立） | 标量 |
| $\mathbf{r}(u)$ | 笛卡尔路径：$[p_x,\, p_y,\, p_z,\, r_x,\, r_y,\, r_z]^\top$ | $6\times1$ |
| $\mathbf{q}(u)$ | 关节角路径（由逆运动学确定） | $6\times1$ |
| $\dot{u} = du/dt$ | 参数速度（路径参数对时间的导数） | 标量 |
| $\dot{u}^2 = (du/dt)^2$ | 参数速度平方（**LP 核心决策变量**） | 标量 |
| $\mathbf{r}'(u) = d\mathbf{r}/du$ | 笛卡尔路径切线向量 | $6\times1$ |
| $\mathbf{r}''(u) = d^2\mathbf{r}/du^2$ | 笛卡尔路径二阶导数 | $6\times1$ |
| $\mathbf{J}(\mathbf{q})$ | $6\times6$ 几何雅可比矩阵 | $6\times6$ |
| $L_k$ | 第 $k$ 段路径等效弧长 | 标量 |
| $N$ | 每段 B 样条基函数个数 | 整数 |
| $M$ | 每段路径参数离散点数 | 整数 |
| $N_w$ | 优化窗口段数（`NWindow`） | 整数 |

### 1.4 路径类型支持

| 路径类型 | 描述 | 关键字段 |
|---|---|---|
| 关节空间直线 | 相邻路径点之间关节角线性插值 | `TRAFO=false` |
| 笛卡尔直线 | TCP 在空间中沿直线运动 | `TRAFO=true, Type=Line` |
| 笛卡尔圆弧 | TCP 沿三点确定的圆弧运动 | `TRAFO=true, Type=Helix` |
| 混合路径 | 直线/圆弧任意拼接 | 多段 CurvStruct |

---

## 二、数学基础：Jacobian 链式展开

### 2.1 路径参数化与决策变量

OpenCN 框架将每段路径用归一化参数 $u \in [0,1]$ 描述。决策变量是参数速度平方 $\dot{u}^2(u)$ 的 B 样条展开：

$$
\dot{u}^2(u) = \sum_{j=1}^{N} x_j \, B_j(u) = \mathbf{B}(u) \, \mathbf{x}
$$

其中：
- $\mathbf{x} \in \mathbb{R}^N$：第 $k$ 段的 B 样条系数向量（LP 决策变量）
- $B_j(u)$：第 $j$ 个 B 样条基函数（3 阶，两端结点重叠）
- $\mathbf{B}(u) = [B_1(u), \ldots, B_N(u)]$：基函数行向量（代码中 `BasisVal` 的一行）

**为何用 $\dot{u}^2$ 而非物理速度 $v^2$？**

速度和加速度约束均可写为 $\dot{u}^2$ 的**线性**函数（因为加速度 $a = f(\dot{u}^2, \ddot{u})$，而 $\ddot{u}$ 通过 B 样条导数线性表达），从而整个优化问题保持线性（LP），避免了 QP 或非线性规划。

### 2.2 一阶：速度的 Jacobian 映射

笛卡尔空间 TCP 速度通过几何雅可比与关节速度连接：

$$
\frac{d\mathbf{x}}{dt} = \mathbf{J}(\mathbf{q}) \, \frac{d\mathbf{q}}{dt}
$$

沿路径参数 $u$ 展开（链式法则）：

$$
\frac{d\mathbf{x}}{dt} = \frac{d\mathbf{r}}{du} \cdot \frac{du}{dt} = \mathbf{r}'(u) \cdot \dot{u}
$$

$$
\frac{d\mathbf{q}}{dt} = \mathbf{J}^{-1}(\mathbf{q}) \, \mathbf{r}'(u) \cdot \dot{u}
$$

**定义关节速度方向系数向量**（每个离散点 $u_m$ 处单独计算）：

$$
\boxed{\mathbf{c}(u_m) = \mathbf{J}^{-1}(\mathbf{q}(u_m)) \, \mathbf{r}'(u_m) \in \mathbb{R}^6}
$$

则各关节速度为：

$$
\dot{q}_i(u_m) = c_i(u_m) \cdot \dot{u}(u_m)
$$

$$
\dot{q}_i^2 = c_i(u_m)^2 \cdot \dot{u}^2(u_m) \quad \longleftarrow \text{对 LP 决策变量 } \dot{u}^2 \text{ 的线性函数}
$$

TCP 路径速度（位置分量）：

$$
v_\text{tcp}(u_m) = \|\mathbf{r}'_\text{pos}(u_m)\| \cdot \dot{u}(u_m)
$$

**关键性质**：$\mathbf{c}(u_m)$ 随路径位置变化（通过 $\mathbf{q}(u_m)$ 和 $\mathbf{r}'(u_m)$），每个离散点需单独计算，这构成了"配置相关速度约束"的核心。

### 2.3 二阶：加速度的 Jacobian 映射

对 $\dot{\mathbf{q}} = \mathbf{J}^{-1}(\mathbf{q}) \, \mathbf{r}'(u) \cdot \dot{u}$ 对时间求导（乘积法则 + 链式法则）：

$$
\ddot{\mathbf{q}} = \mathbf{J}^{-1} \Big[ \mathbf{r}''(u) \cdot \dot{u}^2 + \mathbf{r}'(u) \cdot \ddot{u} \Big]
+ \frac{d\mathbf{J}^{-1}}{du} \, \mathbf{r}'(u) \cdot \dot{u}^2
$$

整理后定义两个系数向量：

$$
\mathbf{A}_1(u) = \mathbf{J}^{-1}(\mathbf{q}) \, \mathbf{r}'(u) = \mathbf{c}(u)
\quad \longleftarrow \ddot{u} \text{ 的系数（即 } \mathbf{c}(u) \text{）}
$$

$$
\mathbf{A}_2(u) = \mathbf{J}^{-1}(\mathbf{q}) \, \mathbf{r}''(u) + \frac{d\mathbf{J}^{-1}}{du} \, \mathbf{r}'(u)
\quad \longleftarrow \dot{u}^2 \text{ 的系数（含 Jacobian 变化项）}
$$

$$
\boxed{\ddot{\mathbf{q}} = \mathbf{A}_2(u) \cdot \dot{u}^2 + \mathbf{A}_1(u) \cdot \ddot{u}}
$$

其中 $\dfrac{d\mathbf{J}^{-1}}{du}$ 的计算方式：

$$
\frac{d\mathbf{J}^{-1}}{du} = -\mathbf{J}^{-1} \cdot \frac{d\mathbf{J}}{du} \cdot \mathbf{J}^{-1}
$$

$$
\frac{d\mathbf{J}}{du} \approx \frac{\mathbf{J}(\mathbf{q} + \varepsilon \, \mathbf{c}) - \mathbf{J}(\mathbf{q})}{\varepsilon}, \quad \varepsilon = 10^{-7}
\quad \text{（数值差分）}
$$

**B 样条线性化**：将 $\dot{u}^2$ 的 B 样条展开代入后，$\ddot{u}$ 也线性依赖于系数 $\mathbf{x}$：

$$
\ddot{u} = \frac{d(\dot{u}^2)/du}{2\dot{u}} \approx \frac{\mathbf{B}'(u) \, \mathbf{x}}{2\sqrt{\mathbf{B}(u) \, \mathbf{x}}}
$$

加速度约束的线性化（LP 可用）：

$$
\ddot{q}_i(u_m) \approx \underbrace{\Big[ A_{2,i}(u_m) \, \mathbf{B}(u_m) + \tfrac{1}{2} A_{1,i}(u_m) \, \mathbf{B}'(u_m) \Big]}_{\text{Acc}_i(m,\,:)} \mathbf{x} = \text{Acc}_i(m,:) \cdot \mathbf{x}
$$

这正是 `buildConstr.m` 中 `Acc` 矩阵第 $i$ 轴、第 $m$ 行的物理含义。

### 2.4 三阶：Jerk 的 Jacobian 映射

完整的三阶链式法则展开包含七项耦合，简化保留主要项：

$$
\dddot{\mathbf{q}} \approx \mathbf{J}^{-1} \Big[ \mathbf{r}'''(u) \cdot \dot{u}^3 + 3\,\mathbf{r}''(u) \cdot \dot{u} \cdot \ddot{u} + \mathbf{r}'(u) \cdot \dddot{u} \Big]
+ \frac{d\mathbf{J}^{-1}}{du} \, \mathbf{r}'(u) \Big[ \mathbf{r}'' \dot{u}^2 + \cdots \Big] \quad \text{（高阶耦合，近似忽略）}
$$

**工程近似**（用于 Jerk 软约束）：

$$
\boxed{\dddot{\mathbf{q}} \approx \mathbf{J}^{-1} \, \mathbf{r}'''(u) \cdot \dot{u}^3} \quad \text{（只保留最高阶主项）}
$$

Jerk 在 OpenCN 中已是软约束（第二阶 LP），此近似精度足够。

> **误差来源**：忽略了含 $\dot{u}\ddot{u}$ 和 $\dddot{u}$ 的耦合项，在速度变化剧烈（大加速度段）处误差较大，可能导致关节 Jerk 约束略有违反（5%~15%），实际应用中通过安全系数补偿。

---

## 三、LP 约束体系

### 3.1 决策变量定义

$$
\mathbf{x} \in \mathbb{R}^{N \times N_w}
$$

- $\mathbf{x}_{:,k}$：第 $k$ 段的 B 样条系数向量（$N$ 个系数）
- $\dot{u}^2_k(u) = \mathbf{B}(u) \, \mathbf{x}_{:,k}$：第 $k$ 段的参数速度平方

**约束矩阵维度汇总（扩展后）**：

$$
N_c = \underbrace{1}_{\text{TCP速度上限}} + \underbrace{1}_{\text{速度非负}} + \underbrace{2\times6}_{\text{关节加速度上/下限}} + \underbrace{2\times6}_{\text{关节速度上/下限（新增）}} = 26 \; \text{行/点/段}
$$

$$
\mathbf{A} \in \mathbb{R}^{N_c \cdot M \cdot N_w \;\times\; N \cdot N_w} \quad \text{（块对角结构）}
$$

$$
\mathbf{A}_\text{eq} \in \mathbb{R}^{2(N_w+1) \;\times\; N \cdot N_w} \quad \text{（连接点连续性，不变）}
$$

### 3.2 TCP 笛卡尔速度约束（已有，无需修改）

TCP 路径速度约束（位置分量）：

$$
v_\text{tcp}(u_m) = \|\mathbf{r}'_\text{pos}(u_m)\| \cdot \dot{u}(u_m) \leq v_\text{cart,max}
$$

等价 LP 不等式：

$$
\|\mathbf{r}'_\text{pos}(u_m)\|^2 \cdot \mathbf{B}(u_m) \, \mathbf{x}_k \leq v_\text{cart,max}^2
$$

矩阵行：

$$
\mathbf{A}_\text{tcp}(m, :) = \|\mathbf{r}'_\text{pos}(u_m)\|^2 \cdot \mathbf{B}(u_m), \qquad b_\text{tcp}(m) = v_\text{cart,max}^2
$$

同时，G-code 编程进给率 $F$ 也作为速度上限（代码中 `windowCurv(k).Info.FeedRate`）：

$$
\dot{u}^2(u_m) \leq \left(\frac{F}{\|\mathbf{r}'(u_m)\|}\right)^2
$$

两者取最小值（逐点），即 `buildConstr.m` 中 `f_max = min(v_max, [], 1)`：

$$
f_\text{max}(u_m) = \min\!\left(\frac{v_\text{cart,max}^2}{\|\mathbf{r}'_\text{pos}(u_m)\|^2},\; \frac{F^2}{\|\mathbf{r}'(u_m)\|^2}\right)
$$

### 3.3 关节速度约束（新增）

在每个离散点 $u_m$，对每个关节 $i = 1,\ldots,6$：

$$
|\dot{q}_i(u_m)| = |c_i(u_m)| \cdot \dot{u}(u_m) \leq \dot{q}_{i,\max}
$$

等价 LP 不等式（上/下限合并，因 $c_i^2 \geq 0$）：

$$
c_i(u_m)^2 \cdot \mathbf{B}(u_m) \, \mathbf{x}_k \leq \dot{q}_{i,\max}^2
$$

矩阵行：

$$
\mathbf{A}_\text{jv}(i, m, :) = c_i(u_m)^2 \cdot \mathbf{B}(u_m), \qquad b_\text{jv}(i,m) = \dot{q}_{i,\max}^2
$$

**有效速度上限**（综合 TCP 速度 + 所有关节速度，取最紧约束）：

$$
\dot{u}^2_\text{max}(u_m) = \min\!\left(\frac{v_\text{cart,max}^2}{\|\mathbf{r}'_\text{pos}(u_m)\|^2},\;\; \min_{i=1}^{6} \frac{\dot{q}_{i,\max}^2}{c_i(u_m)^2}\right)
$$

### 3.4 关节加速度约束（修改 amax 为关节量）

对每个离散点 $u_m$、每个关节 $i$：

$$
|\ddot{q}_i(u_m)| = |\text{Acc}_i(m,:) \cdot \mathbf{x}_k| \leq \ddot{q}_{i,\max}
$$

LP 不等式（上下限各一行）：

$$
+ \text{Acc}_i(m,:) \cdot \mathbf{x}_k \leq +\ddot{q}_{i,\max}
$$

$$
- \text{Acc}_i(m,:) \cdot \mathbf{x}_k \leq +\ddot{q}_{i,\max}
$$

`Acc` 矩阵的完整计算式（机器人情形，关节空间）：

$$
\text{Acc}_i(m,:) = A_{2,i}(u_m) \cdot \mathbf{B}(u_m) + \frac{1}{2} A_{1,i}(u_m) \cdot \mathbf{B}'(u_m)
$$

$$
A_{1,i}(u_m) = \left[\mathbf{J}^{-1}(\mathbf{q}) \, \mathbf{r}'(u_m)\right]_i = c_i(u_m)
\quad \text{（}\ddot{u}\text{ 系数，即关节速度方向系数）}
$$

$$
A_{2,i}(u_m) = \left[\mathbf{J}^{-1}(\mathbf{q}) \, \mathbf{r}''(u_m) + \frac{d\mathbf{J}^{-1}}{du} \, \mathbf{r}'(u_m)\right]_i
\quad \text{（}\dot{u}^2\text{ 系数，含 Jacobian 变化项）}
$$

**关键**：`amax` 传入 `buildConstr` 时必须是**关节加速度上限** $\ddot{q}_{i,\max}$（而非笛卡尔加速度上限），因为 $\text{Acc}_i$ 已经通过 $\mathbf{J}^{-1}$ 将路径加速度映射到了关节空间。

### 3.5 关节 Jerk 约束（第二阶 LP，软约束）

第二阶 LP 在第一阶解的基础上引入 Jerk 约束。对每个关节 $i$：

$$
|\dddot{q}_i(u_m)| \leq j_{i,\max}
$$

近似表达（保留主项）：

$$
\dddot{q}_i \approx \left[\mathbf{J}^{-1} \, \mathbf{r}'''(u_m)\right]_i \cdot \dot{u}^3(u_m)
= \left[\mathbf{J}^{-1} \, \mathbf{r}'''(u_m)\right]_i \cdot \dot{u}_\text{ref}(u_m) \cdot \dot{u}^2(u_m)
$$

LP 线性化（以第一阶解的 $\dot{u}_\text{ref}(u_m)$ 为参考）：

$$
\pm \left[\mathbf{J}^{-1} \, \mathbf{r}'''(u_m)\right]_i \cdot \dot{u}_\text{ref}(u_m) \cdot \mathbf{B}(u_m) \, \mathbf{x}_k \leq j_{i,\max}
$$

Jerk 约束在 OpenCN 中由 `FeedratePlanning_LP.m` 的第二阶 LP 处理，机器人情形只需将 $\mathbf{r}'''_j(u) = \mathbf{J}^{-1} \mathbf{r}'''(u)$ 注入即可（`RobotKinematics.joint()` 已有第三阶近似）。

### 3.6 边界条件（等式约束）

等式约束 $\mathbf{A}_\text{eq} \, \mathbf{x} = \mathbf{b}_\text{eq}$ 的结构不变，共 $2(N_w+1)$ 行：

$$
\begin{cases}
v^2(0) = v_0^2, \quad a_t(0) = a_{t,0} & \text{（窗口起端）} \\[4pt]
v^2_k(1) = v^2_{k+1}(0), \quad a_{t,k}(1) = a_{t,k+1}(0) & \text{（段间连接点，} k = 1,\ldots,N_w-1\text{）} \\[4pt]
v^2(1) = v_1^2, \quad a_t(1) = a_{t,1} & \text{（窗口末端）}
\end{cases}
$$

边界速度/加速度的来源（`ctx.v_1 / ctx.at_1` 生命周期，见 `opencn-notes.md §16.5`）：

| 来源 | 场景 | 值 |
|---|---|---|
| 初始化 | 规划开始 | $v_1=0,\; a_{t,1}=0$ |
| `calcZeroConstraints` | 窗口末端有零速段 | 恒定跃度曲线连接点 |
| MPC 保守停止 | 普通中间窗口 | $v_1=0$（迫使减速到零，但不真正停止） |
| LP 松弛 | LP 求解失败 | 松弛后的连接点速度 |

---

## 四、约束矩阵构造细节

### 4.1 预处理：路径离散与 Jacobian 序列计算

在 `buildConstr` 内循环外，需要为每段路径预计算 Jacobian 相关系数序列：

```matlab
function [C, A2, q_seq] = precompute_jacobian_seq(kin, r0D, r1D, r2D, u_vec)
% 输入：
%   kin   : RobotKinematics 对象
%   r0D   : [6×M] 笛卡尔位姿（含姿态，ZYX 欧拉角）
%   r1D   : [6×M] 路径切线（∂r/∂u）
%   r2D   : [6×M] 路径二阶导数（∂²r/∂u²）
%
% 输出：
%   C     : [6×M] 关节速度方向系数，c(u_m) = J⁻¹(q) · r'(u_m)
%   A2    : [6×M] 关节加速度 ud² 系数，A₂(u_m) = J⁻¹·r''(u_m) + dJ⁻¹/du·r'(u_m)
%   q_seq : [6×M] 对应的关节角序列（IK 结果）

M  = size(r0D, 2);
C  = zeros(6, M);
A2 = zeros(6, M);
q_seq = zeros(6, M);

for m = 1:M
    % 逆运动学：笛卡尔位姿 → 关节角
    T   = kin.pose_to_T(r0D(:, m));
    q   = kin.inverse_kinematics(T);
    q_seq(:, m) = q;
    kin.q_prev  = q;                  % 保持 IK 连续解选择

    % 几何 Jacobian + 安全逆
    J     = kin.geometric_jacobian(q);
    J_inv = kin.safe_J_inv(J);        % 含 DLS 奇异保护

    % 一阶系数：c = J⁻¹ · r'(u)
    c = J_inv * r1D(:, m);
    C(:, m) = c;

    % Jacobian 对 u 的数值导数：dJ/du ≈ (J(q+ε·c) - J(q)) / ε
    J_pert = kin.geometric_jacobian(q + 1e-7 * c);
    dJdu   = (J_pert - J) / 1e-7;

    % 二阶系数：A₂ = J⁻¹·r''(u) + (dJ⁻¹/du)·r'(u)
    %   其中 dJ⁻¹/du = -J⁻¹ · dJ/du · J⁻¹
    dJinv_du_r1 = -J_inv * dJdu * c;   % (dJ⁻¹/du) · r'(u)
    A2(:, m) = J_inv * r2D(:, m) + dJinv_du_r1;
end
end
```

### 4.2 有效速度上限的逐点计算

每个离散点 $u_m$ 的有效 $\dot{u}^2$ 上限综合 TCP 和关节速度约束：

$$
\dot{u}^2_\text{max}(u_m) = \min\!\left(\frac{v_\text{cart,max}^2}{\|\mathbf{r}'_\text{pos}(u_m)\|^2 + \epsilon},\;\; \min_{i=1}^{6} \frac{\dot{q}_{i,\max}^2}{c_i(u_m)^2 + \epsilon}\right)
$$

```matlab
function f_max = compute_joint_vel_fmax(C, r1D_pos, v_cart_max, qd_max)
% 计算每个离散点处考虑关节速度约束后的有效 ud² 上限
%
% 输入：
%   C          : [6×M] 关节速度系数 c(u_m)
%   r1D_pos    : [3×M] 路径切线的位置分量（仅 xyz）
%   v_cart_max : TCP 速度上限（标量，m/s）
%   qd_max     : [6×1] 关节速度上限（rad/s）
%
% 输出：
%   f_max      : [1×M] 有效 ud² 上限（供填入 b 向量）

M     = size(C, 2);
f_max = zeros(1, M);

for m = 1:M
    tcp_lim    = (v_cart_max / (norm(r1D_pos(:, m)) + 1e-12))^2;
    joint_lims = (qd_max ./ (abs(C(:, m)) + 1e-12)).^2;
    f_max(m)   = min([tcp_lim; joint_lims]);
end
end
```

### 4.3 关节速度约束行注入 buildConstr

在现有 `buildConstr.m` 的主循环中（第 $k$ 段），在速度上限行之后追加关节速度约束行：

$$
c_i(u_m)^2 \cdot \mathbf{B}(u_m) \, \mathbf{x}_k \leq \dot{q}_{i,\max}^2 \quad i = 1,\ldots,6
$$

```matlab
if strcmp(ctx.kin.get_type(), 'robot6dof') && ctx.cfg.use_joint_vel_constr

    [C_k, A2_k, ~] = precompute_jacobian_seq(ctx.kin, r0D, r1D, r2D, u_vec);

    f_max = compute_joint_vel_fmax(C_k, r1D(1:3,:), ctx.cfg.v_cart, ctx.cfg.vmax);

    for i = 1:6
        ci_sq    = C_k(i, :).^2;            % [1×M] c_i² 逐点值
        A_jv_row = ci_sq' .* BasisVal;       % [M×N]，每行 = c_i² × B(u_m,:)
        A(row_offset + (1:M), indAC) = A_jv_row;
        b(row_offset + (1:M))        = ctx.cfg.vmax(i)^2 * ones(M, 1);
        row_offset = row_offset + M;
    end

    for j = 1:Ndim
        ind = int32(1:M) + (j-1)*M;
        Acc(ind, :, 1) = A2_k(j,:)' .* BasisVal + 0.5 * C_k(j,:)' .* BasisValD;
    end
end
```

### 4.4 amax 传入方式的修正

现有 `buildConstr.m` 中 `amaxTot = amax(ctx.cfg.maskTot)` 对应各轴加速度上限。

机器人情形：`amax` 必须是**关节加速度上限** $\ddot{q}_{i,\max}$（$6\times1$），而非笛卡尔加速度：

```matlab
% robot_traj_opt.m 中调用 FeedratePlanning_LP 时：
amax = robot_params.amax;    % [6×1] 关节加速度上限（rad/s²）
jmax = robot_params.jmax;    % [6×1] 关节 Jerk 上限（rad/s³）
```

### 4.5 等式约束中切向加速度的正确处理

等式约束（连接点连续性）中的切向加速度使用 `Acc(:,:,2)`，该切片在**原始笛卡尔坐标**下计算：

$$
\text{Acc}_j(m,:)\big|_{\text{slice 2}} = r''_j(u_m) \cdot \mathbf{B}(u_m) + \tfrac{1}{2} r'_j(u_m) \cdot \mathbf{B}'(u_m)
$$

不经过 $\mathbf{J}^{-1}$ 映射，确保相邻窗口连接点处路径的几何加速度连续，与坐标系无关。

---

## 五、奇异点处理

### 5.1 六轴机器人的奇异点类型

| 奇异类型 | 触发条件 | $\mathbf{J}$ 的变化 | 对约束的影响 |
|---|---|---|---|
| 肩部奇异 | 腕心在 $z_0$ 轴上（$q_1$ 不定） | $\mathbf{J}$ 第1列近零 | $\dot{q}_1$ 趋无穷 |
| 肘部奇异 | $q_3 \approx 0$ 或 $\pi$（臂完全伸/折） | $\mathbf{J}$ 秩亏1 | $\dot{q}_2/\dot{q}_3$ 耦合速度趋无穷 |
| 腕部奇异 | $q_5 \approx 0$ 或 $\pi$（$q_4/q_6$ 共线） | $\mathbf{J}$ 后3列相关 | $\dot{q}_4/\dot{q}_6$ 速度趋无穷 |

### 5.2 关节速度约束的隐式奇异减速效应

**这是本方案的核心优势之一**：不需要显式奇异检测，LP 框架自动在奇异点附近减速。

物理机理：

$$
\text{接近奇异时：}\quad \mathrm{rcond}(\mathbf{J}) \to 0 \implies \|\mathbf{J}^{-1}\| \to \infty
$$

$$
\mathbf{c}(u_m) = \mathbf{J}^{-1} \mathbf{r}'(u_m) \implies c_i(u_m) \to \infty
$$

关节速度约束右端固定：

$$
c_i(u_m)^2 \cdot \dot{u}^2(u_m) \leq \dot{q}_{i,\max}^2
\implies \dot{u}^2(u_m) \leq \frac{\dot{q}_{i,\max}^2}{c_i(u_m)^2} \to 0
$$

**LP 效果**：$\dot{u}^2_\text{max}(u_m)$ 在奇异点附近被自动压到接近零，轨迹在奇异点附近形成局部速度最小值，通过后自动加速。

速度剖面示意图（肘部奇异情形，$q_3$ 经过 $\pi$ 后恢复）：

```
v_tcp
  │
  │    ╭────────╮              ╭────────╮
  │   ╱          ╲            ╱          ╲
  │──╱            ╲──────────╱            ╲──→ 路径弧长 s
                   奇异点附近（c_i → ∞，v → 0）
```

### 5.3 DLS 正则化的影响分析

当前 `RobotKinematics.safe_J_inv()` 在 $\mathrm{rcond}(\mathbf{J}) < 10^{-6}$ 时切换为阻尼最小二乘（DLS）：

$$
\mathbf{J}_\text{dls}^{-1} = \mathbf{J}^\top \left(\mathbf{J}\mathbf{J}^\top + \lambda^2 \mathbf{I}\right)^{-1}, \quad \lambda = 0.01 \; \text{rad/s}
$$

DLS 的效果：奇异轴方向上 $\|\mathbf{J}^{-1}_\text{dls}\|$ 被 $\lambda^2$ 截断，$c_i$ 不再趋向无穷，机器人仍以有限速度

$$
\dot{u}_\text{pass} = \frac{\dot{q}_{i,\max}}{c_{i,\text{dls}}} > 0
$$

通过奇异点，但对应的实际关节速度可能略超 $\dot{q}_{i,\max}$（软违反）。

**$\lambda$ 值选择建议**：

| $\lambda$ | 奇异减速效果 | 关节速度误差 | 适用场景 |
|---|---|---|---|
| $0.001$ | 极强（接近完全停止） | 极小 | 高精度焊接、精密装配 |
| $0.01$ | 较强（速度减至 1%~5%） | 小 | 通用工业场景（推荐） |
| $0.05$ | 中等（速度减至 5%~20%） | 中 | 精度要求不高的搬运 |
| $0.1$ | 较弱（速度减至 10%~30%） | 较大 | 快速通过奇异的特殊需求 |

### 5.4 腕部奇异的特殊处理

腕部奇异（$q_5 \approx 0$）时，$q_4$ 与 $q_6$ 绕同一轴旋转，两者之和固定但各自不唯一。IK 会出现 $q_4$、$q_6$ 的突变（从一次 IK 到下一次 IK 任意分配旋转）。

**解决方案**：
1. **约定** $q_4 = 0$（现有代码已实现），保证解的唯一性
2. **路径层绕开** $q_5 \approx 0$：通过微调末端姿态中的一个欧拉角（偏置几度）使路径绕开腕部奇异
3. **后处理滤波**：对 IK 结果中 $q_4/q_6$ 的变化做低通滤波，消除数值噪声引起的关节角抖动

### 5.5 可达性（工作空间边界）

IK 无解时，`inverse_kinematics()` 返回 `numerical_ik_fallback()` 的结果。路径规划层应在前期做工作空间检验：

```matlab
for k = 1:N_waypoints
    T = kin.pose_to_T(waypoints(:, k));
    q = kin.inverse_kinematics(T);
    if norm(kin.forward_kinematics(q) - waypoints(:, k)) > 1e-3
        error('路径点 %d 不可达或精度不足', k);
    end
end
```

---

## 六、实现架构

### 6.1 模块依赖与调用关系

```
robot_traj_opt.m（主入口）
│
├── RobotDefaultConfig.m        ← 新增 qd_max, qdd_max, jmax, v_cart 字段
│
├── RobotKinematics.m           ← 扩展接口
│   ├── precompute_jacobian_seq()  ← 新增：批量计算 C, A2
│   ├── get_jacobian()             ← 新增：公开接口
│   ├── joint()                    ← 已有，返回 r0D_j/r1D_j/r2D_j/r3D_j
│   └── safe_J_inv()              ← 已有，DLS 奇异保护
│
├── initRobotPlan.m             ← 注入约束参数到 ctx
│
└── FeedoptPlanRun（FSM 主循环）
    └── feedratePlanning（每窗口调用）
        ├── feedratePlanningSetupCurves   ← 不变（边界条件三来源机制）
        │
        └── FeedratePlanning_LP
            ├── compute_scaling_matrix    ← 不变（D = diag(1/L²)）
            │
            └── buildConstr_robot.m       ← 新文件（或 buildConstr.m 扩展）
                ├── precompute_jacobian_seq()  调用
                ├── TCP 速度上限行（原有）
                ├── 关节速度约束行（新增）     ← 核心新增
                ├── 关节加速度约束（修改 amax）
                └── 连接点连续性等式（不变）
```

### 6.2 RobotDefaultConfig 扩展

```matlab
function cfg = RobotDefaultConfig(params)
cfg.NumberAxis  = 6;
cfg.dt          = getfield_default(params, 'dt',  1e-3);
cfg.dh_params   = params.dh;
cfg.robot_config= getfield_default(params, 'config', 'elbow_up');
cfg.q_lim       = getfield_default(params, 'q_lim', repmat([-2*pi,2*pi],6,1));

% 关节约束（rad, rad/s, rad/s², rad/s³）
cfg.vmax        = params.vmax;          % [6×1] 关节速度上限
cfg.amax        = params.amax;          % [6×1] 关节加速度上限（传入 buildConstr）
cfg.jmax        = params.jmax;          % [6×1] 关节 Jerk 上限
cfg.feedrate    = min(params.vmax);     % 默认编程进给率

% 笛卡尔约束
cfg.v_cart      = getfield_default(params, 'v_cart', Inf);   % TCP 速度上限 (m/s)

% LP 框架相关
cfg.maskTot              = 1:6;
cfg.indCart              = 1:6;
cfg.use_joint_vel_constr = true;
cfg.kin_type             = 'robot6dof';
end
```

### 6.3 buildConstr_robot.m 整体结构

约束行的组织顺序（每段 $k$，每个离散点 $m$）：

$$
\mathbf{A}_{k}(m) = \begin{bmatrix}
\|\mathbf{r}'_\text{pos}\|^2 \cdot \mathbf{B}(u_m) \\[2pt]
-\mathbf{B}(u_m) \\[2pt]
c_1^2 \, \mathbf{B}(u_m) \\[-1pt]
\vdots \\[-1pt]
c_6^2 \, \mathbf{B}(u_m) \\[2pt]
+\text{Acc}_1(m,:) \\[-1pt]
\vdots \\[-1pt]
+\text{Acc}_6(m,:) \\[2pt]
-\text{Acc}_1(m,:) \\[-1pt]
\vdots \\[-1pt]
-\text{Acc}_6(m,:)
\end{bmatrix}, \quad
\mathbf{b}_{k}(m) = \begin{bmatrix}
f_\text{max}(u_m) \\[2pt]
0 \\[2pt]
\dot{q}_{1,\max}^2 \\[-1pt]
\vdots \\[-1pt]
\dot{q}_{6,\max}^2 \\[2pt]
\ddot{q}_{1,\max} \\[-1pt]
\vdots \\[-1pt]
\ddot{q}_{6,\max} \\[2pt]
\ddot{q}_{1,\max} \\[-1pt]
\vdots \\[-1pt]
\ddot{q}_{6,\max}
\end{bmatrix}
$$

```matlab
function [A, b, Aeq, beq, continuity] = buildConstr_robot( ...
    ctx, windowCurv, amax, v_0, at_0, v_1, at_1, BasisVal, BasisValD, u_vec)

[M, N]   = size(BasisVal);
Ndim     = 6;
Nwindow  = length(windowCurv);
Nc       = 2 + 2*Ndim + 2*Ndim;
Nx       = N * Nwindow;
Nec      = 2 * (Nwindow + 1);

A   = zeros(Nc * M * Nwindow, Nx);
b   = zeros(Nc * M * Nwindow, 1);
Aeq = zeros(Nec, Nx);
beq = zeros(Nec, 1);
amaxTot = amax(ctx.cfg.maskTot);
b_amax  = repmat(amaxTot, M, 1);
mask_continuity = [1; 1; -1; -1];
at_norm  = zeros(2, N, Nwindow);
t_vec    = zeros(Ndim, 2, Nwindow);
v2_vec   = zeros(2, N, Nwindow);
Acc      = zeros(M * Ndim, N, 2);
indAT    = (int32(1:Ndim)-1)*M + int32([1;M]);

for k = 1:Nwindow
    [r0D, r1D, r2D, ~] = EvalCurvStruct(ctx, windowCurv(k), u_vec);
    [C_k, A2_k] = precompute_jacobian_seq(ctx.kin, r0D, r1D, r2D, u_vec);

    f_max   = compute_joint_vel_fmax(C_k, r1D(1:3,:), ctx.cfg.v_cart, ctx.cfg.vmax);
    normR1D = vecnorm(r1D);
    t_vec(:,:,k) = r1D(:,[1,end]) ./ normR1D([1,end]);

    for j = 1:Ndim
        ind = int32(1:M) + (j-1)*M;
        Acc(ind,:,1) = A2_k(j,:)' .* BasisVal + 0.5 * C_k(j,:)' .* BasisValD;
        Acc(ind,:,2) = r2D(j,:)'   .* BasisVal + 0.5 * r1D(j,:)' .* BasisValD;
    end

    indAL = int32(1:Nc*M) + (k-1)*Nc*M;
    indAC = int32(1:N)    + (k-1)*N;
    A_jv  = zeros(Ndim*M, N);
    for i = 1:Ndim
        rows_i = int32(1:M) + (i-1)*M;
        A_jv(rows_i, :) = C_k(i,:)'.^2 .* BasisVal;
    end

    A(indAL, indAC) = [BasisVal; -BasisVal; A_jv; -A_jv; Acc(:,:,1); -Acc(:,:,1)];
    b_jv = repmat(ctx.cfg.vmax.^2, M, 1);
    b(indAL) = [f_max'; zeros(M,1); b_jv; b_jv; b_amax(:); b_amax(:)];

    at_norm(1,:,k) = t_vec(:,1,k)' * Acc(indAT(1,:),:,2);
    at_norm(2,:,k) = t_vec(:,2,k)' * Acc(indAT(2,:),:,2);
    v2_vec(:,:,k)  = normR1D([1,end]).^2' .* BasisVal([1;end],:);
    continuity = [v2_vec(1,:,k); at_norm(1,:,k); v2_vec(2,:,k); at_norm(2,:,k)];

    indAEL = int32(1:4) + (k-1)*2;
    indAEC = int32(1:N) + (k-1)*N;
    Aeq(indAEL, indAEC) = Aeq(indAEL, indAEC) + continuity .* mask_continuity;
end

beq([1, 2, end-1, end]) = [v_0^2; at_0; v_1^2; at_1] .* mask_continuity;
end
```

### 6.4 robot_traj_opt.m 修改点

```matlab
function result = robot_traj_opt(waypoints, robot_params, mode, varargin)

cfg = RobotDefaultConfig(robot_params);
kin = RobotKinematics(cfg.dh_params, cfg.robot_config, cfg.q_lim);
ctx = initRobotPlan(cfg, kin);

% 可达性预检查（新增）
if strcmp(mode, 'cartesian') || strcmp(mode, 'arc')
    verify_reachability(kin, waypoints, mode);
end

% 曲线段构造（原有）
% ...

% 指定机器人专用约束构造函数（新增）
ctx.buildConstrFcn = @buildConstr_robot;
ctx.op = Fopt.Check;
ctx    = FeedoptPlanRun(ctx);

% 重采样和结果加载（原有）
% ...
end
```

---

## 七、数值考虑

### 7.1 决策变量缩放（复用现有机制）

现有 `compute_scaling_matrix` 构造缩放矩阵：

$$
\mathbf{D} = \mathrm{diag}\!\left(\frac{1}{L_1^2}, \ldots, \frac{1}{L_1^2}, \frac{1}{L_2^2}, \ldots, \frac{1}{L_{N_w}^2}\right) \in \mathbb{R}^{N \cdot N_w \times N \cdot N_w}
$$

物理含义：$\dot{u}^2 = v^2/L^2$，同一物理速度 $v$ 下，短段的 $\dot{u}^2$ 比长段大 $(L_\text{max}/L_\text{min})^2$ 倍，缩放后量级统一为 $v^2$。

变量替换 $\tilde{\mathbf{x}} = \mathbf{D}^{-1} \mathbf{x}$（即 $\mathbf{x}_\text{orig} = \mathbf{D} \, \tilde{\mathbf{x}}$）：

$$
\mathbf{A} \leftarrow \mathbf{A} \mathbf{D}, \quad \mathbf{A}_\text{eq} \leftarrow \mathbf{A}_\text{eq} \mathbf{D}, \quad \mathbf{f} \leftarrow \mathbf{f} \mathbf{D}
$$

LP 求解后恢复：$\mathbf{x}_\text{orig} = \mathbf{D} \, \tilde{\mathbf{x}}_\text{solver}$。

关节速度约束行 $c_i^2 \cdot \mathbf{B}(u_m)$ 在 $\mathbf{A} \leftarrow \mathbf{A}\mathbf{D}$ 后自动被正确缩放，**无需额外处理**。

### 7.2 约束矩阵条件数分析

接近奇异时 $c_i(u_m) \to \infty$，关节速度约束行的范数 $\|c_i^2 \cdot \mathbf{B}\| \to \infty$，可能恶化条件数。

**缓解措施**：对关节速度约束行做行归一化（等价变换，不改变可行域）：

$$
\frac{\mathbf{a}^\top}{\|\mathbf{a}\|} \, \mathbf{x} \leq \frac{b}{\|\mathbf{a}\|}
$$

条件数监控：

```matlab
cond_A = condest(A);
if cond_A > 1e10
    warning('LP 约束矩阵条件数过高 (%.1e)，考虑增大 DLS λ', cond_A);
end
```

### 7.3 IK 计算开销分析

典型参数：$M = 20$，$N_w = 5$，每次 LP 构造需要 $100$ 次 IK。

| IK 方法 | 每次耗时 | 100次总耗时 | 备注 |
|---|---|---|---|
| 解析 IK（腕部分离法） | ~0.1ms | ~10ms | 适用 UR 型机器人 |
| 数值 IK（梯度下降） | ~1~5ms | ~100~500ms | 奇异/退化位形备用 |
| 缓存复用（路径不变） | ~0ms | ~0ms | 同一段跨窗口复用 |

### 7.4 Jerk 近似误差的工程补偿

由于三阶链式法则采用近似（忽略耦合项），Jerk 约束可能有 5%~15% 的违反。

**建议**：设置 Jerk 约束时引入安全系数 $\alpha = 0.85$：

$$
j_{i,\max}^\text{eff} = 0.85 \cdot j_{i,\max}
$$

---

## 八、测试验证方案

### 8.1 单元测试

**测试1：关节速度约束有效性**

```matlab
function test_joint_vel_constraint()
tol = 1.01;
for i = 1:length(result.t) - 1
    qd = (result.q(:, i+1) - result.q(:, i)) / cfg.dt;
    assert(all(abs(qd) <= cfg.vmax * tol));
end
end
```

**测试2：关节加速度约束有效性**

```matlab
function test_joint_acc_constraint()
tol = 1.02;
for i = 2:length(result.t) - 1
    qdd = (result.q(:,i+1) - 2*result.q(:,i) + result.q(:,i-1)) / cfg.dt^2;
    assert(all(abs(qdd) <= cfg.amax * tol));
end
end
```

**测试3：TCP 速度约束有效性**

```matlab
function test_tcp_vel_constraint()
tol = 1.01;
for i = 1:length(result.t) - 1
    v_tcp = norm(result.pos(1:3,i+1) - result.pos(1:3,i)) / cfg.dt;
    assert(v_tcp <= cfg.v_cart * tol);
end
end
```

**测试4：轨迹 $C^1$ 连续性**（跨窗口连接点处速度和加速度连续，误差 $< 10^{-3}$）

### 8.2 典型测试场景

| 场景 | 路径描述 | 验证重点 | 预期现象 |
|---|---|---|---|
| **S1：点对点（无奇异）** | 关节空间 6 点路径，构型温和 | 关节速度/加速度/Jerk 在约束内 | 时间最优，平滑加减速 |
| **S2：肘部奇异穿越** | 笛卡尔直线，$q_3$ 经过 $\pi$ | 奇异点处速度自动降低 | $v_\text{tcp}$ 形成局部最小值 |
| **S3：快速笛卡尔直线** | $v_\text{cart,max}$ 约束主导 | TCP 速度不超限 | 关节速度约束不激活 |
| **S4：小幅关节运动** | 短路径，$\dot{q}_{i,\max}$ 约束主导 | 关节速度约束主导 | TCP 速度约束不激活 |
| **S5：圆弧路径** | 半径 0.1m 圆弧，姿态同步变化 | 弧长参数化 + 混合约束 | 速度在弯道处适当降低 |
| **S6：多段混合路径** | 直线+圆弧+直线，带停顿点 | 跨段连续性 + 零速节点 | 停顿点处完全停止 |
| **S7：接近工作空间边界** | 目标点接近臂展极限 | 可达性检查 + 肘奇异 | 报告警告或切换数值 IK |

### 8.3 性能基准

| 指标 | CNC 3轴（参考） | 机器人扩展（目标） |
|---|---|---|
| LP 构造时间（每窗口） | ~5ms | ~20ms（含 IK 计算） |
| LP 求解时间（每窗口） | ~10ms | ~30ms（约束行增加） |
| 全路径规划时间（100段） | ~1.5s | ~5s |

---

## 九、与现有 CNC 框架的差异对比

### 9.1 约束维度对比

| 约束项 | CNC 3轴 | CNC 5轴 | 机器人 6轴 |
|---|---|---|---|
| 速度上限 | 3轴各1行 | 5轴各1行 | TCP 速度1行 |
| 速度下限 | 1行（非负） | 1行 | 1行 |
| 关节速度 | 不需要 | 不需要 | **新增 $6\times2$ 行** |
| 加速度上/下限 | $3\times2$ 行 | $5\times2$ 行 | $6\times2$ 行（关节空间） |
| 等式约束 | $2(N_w+1)$ 行 | $2(N_w+1)$ 行 | $2(N_w+1)$ 行（不变） |

### 9.2 运动学映射差异

| 方面 | CNC 框架（TRAFO=true） | 机器人扩展 |
|---|---|---|
| 正运动学 | 简单线性变换（5轴桌面角） | DH 正运动学（链式矩阵乘积） |
| 逆运动学 | 解析（线性关系） | 解析（腕部分离法）+ DLS 备用 |
| $\mathbf{J}(\mathbf{q})$ | 常数或简单三角函数 | $\mathbf{q}$ 相关，沿路径逐点变化 |
| 奇异性 | 基本无（线性机） | 3类奇异，需要 DLS 处理 |
| 约束配置相关性 | 否（各轴独立） | **是（通过 $\mathbf{J}(\mathbf{q})$ 耦合）** |

### 9.3 代码层面的继承与新增

```
继承不变（直接复用）：
  ✅ B 样条框架（BasisVal, BasisValD, BasisValDD, BasisIntegr）
  ✅ LP 两阶段求解（FeedratePlanning_LP.m）
  ✅ 决策变量缩放（compute_scaling_matrix，D = diag(1/L²)）
  ✅ 滑动窗口 MPC（feedratePlanningGetwindow, feedratePlanningSetupCurves）
  ✅ 边界条件三来源机制（v_1/at_1 生命周期）
  ✅ LP 约束松弛重试（relax_intial_constraints）
  ✅ 重采样输出（resample2file）
  ✅ 等式约束结构（段间 C¹ 连续性）

需要新增或修改：
  🔧 buildConstr_robot.m（新文件）：增加关节速度约束行，修改 amax 为关节量
  🔧 RobotKinematics.m：新增 precompute_jacobian_seq(), get_jacobian()
  🔧 RobotDefaultConfig.m：新增 v_cart, jmax, use_joint_vel_constr 字段
  🔧 robot_traj_opt.m：指定 buildConstrFcn 句柄，添加可达性预检查
  🆕 compute_joint_vel_fmax.m（新工具函数）：逐点计算有效 ud² 上限
  🆕 precompute_jacobian_seq.m（新工具函数）：批量 IK + Jacobian 计算
  🆕 verify_reachability.m（新工具函数）：路径点可达性预检
```

---

## 附录：关键公式汇总

### A.1 速度映射

$$
v_\text{tcp} = \|\mathbf{r}'_\text{pos}(u)\| \cdot \dot{u}
$$

$$
\dot{q}_i = c_i(u) \cdot \dot{u}, \qquad \mathbf{c}(u) = \mathbf{J}^{-1}(\mathbf{q}(u)) \, \mathbf{r}'(u) \in \mathbb{R}^6
$$

### A.2 加速度映射

$$
\ddot{\mathbf{q}} = \mathbf{A}_2(u) \cdot \dot{u}^2 + \mathbf{A}_1(u) \cdot \ddot{u}
$$

$$
\mathbf{A}_1(u) = \mathbf{c}(u) = \mathbf{J}^{-1} \mathbf{r}'(u)
$$

$$
\mathbf{A}_2(u) = \mathbf{J}^{-1} \mathbf{r}''(u) - \mathbf{J}^{-1} \frac{d\mathbf{J}}{du} \mathbf{J}^{-1} \mathbf{r}'(u)
$$

**B 样条线性化**：

$$
\ddot{q}_i \approx \underbrace{\Big[ A_{2,i}(u_m) \, \mathbf{B}(u_m) + \tfrac{1}{2} A_{1,i}(u_m) \, \mathbf{B}'(u_m) \Big]}_{\text{Acc}_i(m,:)} \mathbf{x}
$$

### A.3 LP 不等式约束行（机器人完整版）

| 约束类型 | 不等式行 | 右端 |
|---|---|---|
| TCP 速度上限 | $\|\mathbf{r}'_\text{pos}\|^2 \cdot \mathbf{B}(u_m) \, \mathbf{x}_k$ | $\leq v_\text{cart,max}^2$ |
| 速度非负 | $-\mathbf{B}(u_m) \, \mathbf{x}_k$ | $\leq 0$ |
| 关节速度（新增） | $c_i(u_m)^2 \cdot \mathbf{B}(u_m) \, \mathbf{x}_k$ | $\leq \dot{q}_{i,\max}^2$ |
| 关节加速度上限 | $+\text{Acc}_i(m,:) \, \mathbf{x}_k$ | $\leq \ddot{q}_{i,\max}$ |
| 关节加速度下限 | $-\text{Acc}_i(m,:) \, \mathbf{x}_k$ | $\leq \ddot{q}_{i,\max}$ |

### A.4 奇异点处的速度极限

DLS 正则化后，奇异点附近的 TCP 速度极限近似为：

$$
v_\text{tcp,sing} \approx \frac{\lambda \cdot \dot{q}_{i,\max}}{\|\mathbf{r}'_\text{pos}(u_\text{sing})\|}
$$

其中 $\lambda = 0.01 \; \text{rad/s}$ 为阻尼系数，典型量级为 $\text{mm/s} \sim \text{cm/s}$，视路径切线长度而定。

### A.5 目标函数

$$
\min_{\mathbf{x}} \; -\sum_{k=1}^{N_w} \mathbf{b}_\text{intgr}^\top \mathbf{D}_k \, \mathbf{x}_{:,k}
\quad \text{s.t.} \quad \mathbf{A}\mathbf{x} \leq \mathbf{b}, \quad \mathbf{A}_\text{eq}\mathbf{x} = \mathbf{b}_\text{eq}, \quad \mathbf{x} \geq 0
$$

其中 $\mathbf{b}_\text{intgr}$ 是 B 样条基函数在 $[0,1]$ 上的积分向量（代码中 `BasisIntegr`），$\mathbf{D}_k = \text{diag}(1/L_k^2)$ 为第 $k$ 段的缩放矩阵。

---

---

## 十、简化方案：关节空间规划 + 笛卡尔速度约束

本章描述一种比第二~六章更轻量的方案：**路径在关节空间定义，同时附加 TCP 笛卡尔速度上限约束**。适用于对路径形状（直线/圆弧）无严格要求，但需要控制末端速度的场景（搬运、点位控制等）。

### 10.1 方案核心思路

| 方面 | 第二~六章（全笛卡尔方案） | 本章（关节空间简化方案） |
|---|---|---|
| 路径定义 | 笛卡尔空间直线/圆弧 | 关节角序列线性插值 |
| 需要 IK | 是（每点一次） | 否 |
| 需要 $\mathbf{J}^{-1}$ | 是（速度/加速度约束） | 否 |
| 需要 $\mathbf{J}$（正向） | 否 | 是（笛卡尔速度约束） |
| 加速度约束推导 | $\mathbf{J}^{-1}$ 链式法则，含 $d\mathbf{J}/du$ 项 | 直接用 $\mathbf{q}''(u)$，无耦合项 |
| 笛卡尔路径精度 | 精确 | 近似（关节线性 ≠ 笛卡尔直线） |
| 代码改动量 | 大 | 极小（仅设置 FeedRate） |

### 10.2 数学推导

#### 10.2.1 路径参数化

关节角路径 $\mathbf{q}(u)$ 由相邻路径点线性插值给出，$u \in [0,1]$：

$$
\mathbf{q}(u) = (1-u)\,\mathbf{q}_0 + u\,\mathbf{q}_1 \implies \mathbf{q}'(u) = \mathbf{q}_1 - \mathbf{q}_0 = \text{const}
$$

决策变量不变：$\dot{u}^2(u) = \mathbf{B}(u)\,\mathbf{x}$。

#### 10.2.2 关节速度约束（无需 Jacobian）

关节速度由路径导数直接给出：

$$
\dot{q}_i(u_m) = q'_i(u_m) \cdot \dot{u}(u_m)
$$

约束系数退化为简单标量（线性段为常数）：

$$
c_i(u_m) = q'_i(u_m) \quad \text{（无需 Jacobian 计算）}
$$

LP 不等式：

$$
q'_i(u_m)^2 \cdot \mathbf{B}(u_m)\,\mathbf{x}_k \leq \dot{q}_{i,\max}^2
$$

#### 10.2.3 关节加速度约束（无耦合项）

加速度在关节空间直接表达，**无需 $\mathbf{J}^{-1}$ 和 $d\mathbf{J}/du$ 修正**：

$$
\ddot{q}_i = q''_i(u) \cdot \dot{u}^2 + q'_i(u) \cdot \ddot{u}
$$

$$
\text{Acc}_i(m,:) = q''_i(u_m) \cdot \mathbf{B}(u_m) + \tfrac{1}{2}\,q'_i(u_m) \cdot \mathbf{B}'(u_m)
$$

对线性插值段：$q''_i = 0$，故 $\text{Acc}_i(m,:) = \tfrac{1}{2}\,q'_i \cdot \mathbf{B}'(u_m)$，计算极为简洁。

#### 10.2.4 笛卡尔速度约束（唯一需要 Jacobian 的步骤）

TCP 位置速度通过**正向 Jacobian** 计算：

$$
\frac{d\mathbf{p}_\text{tcp}}{dt} = \mathbf{J}_\text{pos}(\mathbf{q}(u)) \cdot \mathbf{q}'(u) \cdot \dot{u}
$$

其中 $\mathbf{J}_\text{pos} \in \mathbb{R}^{3\times6}$ 是 Jacobian 的位置分量（前3行）。

定义**笛卡尔速度标量系数**（每个离散点 $u_m$ 处计算）：

$$
\boxed{\kappa(u_m) = \left\|\mathbf{J}_\text{pos}(\mathbf{q}(u_m)) \cdot \mathbf{q}'(u_m)\right\|^2}
$$

LP 不等式：

$$
\kappa(u_m) \cdot \mathbf{B}(u_m)\,\mathbf{x}_k \leq v_\text{cart,max}^2
$$

**综合有效速度上限**（三类约束取最紧者）：

$$
\dot{u}^2_\text{max}(u_m) = \min\!\left(
\min_{i=1}^{6} \frac{\dot{q}_{i,\max}^2}{q'_i(u_m)^2},\;\;
\frac{v_\text{cart,max}^2}{\kappa(u_m)}
\right)
$$

#### 10.2.5 Jerk 约束（直接关节空间，无近似误差）

关节 Jerk 直接来自路径三阶导数，**无任何 Jacobian 耦合项**：

$$
\dddot{q}_i = q'''_i(u) \cdot \dot{u}^3 + 3\,q''_i(u) \cdot \dot{u}\,\ddot{u} + q'_i(u) \cdot \dddot{u}
$$

对线性插值段 $q''' = q'' = 0$，Jerk 完全退化为 $q'_i \cdot \dddot{u}$，精度远高于全笛卡尔方案的近似。

### 10.3 完整约束矩阵结构

每段 $k$，每个离散点 $m$ 的约束行数：

$$
N_c = \underbrace{1}_{\text{Cartesian速度}} + \underbrace{1}_{\text{非负}} + \underbrace{2\times6}_{\text{关节速度}} + \underbrace{2\times6}_{\text{关节加速度}} = 26\;\text{行/点}
$$

$$
\mathbf{A}_k(m) = \begin{bmatrix}
\kappa(u_m) \cdot \mathbf{B}(u_m) \\[2pt]
-\mathbf{B}(u_m) \\[2pt]
q'_1(u_m)^2 \cdot \mathbf{B}(u_m) \\[-1pt] \vdots \\[-1pt] q'_6(u_m)^2 \cdot \mathbf{B}(u_m) \\[2pt]
+\text{Acc}_i(m,:) \\[-1pt] \vdots \\[2pt]
-\text{Acc}_i(m,:) \\[-1pt] \vdots
\end{bmatrix},
\quad
\mathbf{b}_k(m) = \begin{bmatrix}
v_\text{cart,max}^2 \\[2pt] 0 \\[2pt]
\dot{q}_{1,\max}^2 \\[-1pt] \vdots \\[-1pt] \dot{q}_{6,\max}^2 \\[2pt]
\ddot{q}_{i,\max} \\[-1pt] \vdots \\[2pt]
\ddot{q}_{i,\max} \\[-1pt] \vdots
\end{bmatrix}
$$

与全笛卡尔方案的区别仅在：
- TCP 速度行系数 $\kappa(u_m)$ 由正向 $\mathbf{J}$ 计算，而非 $\|\mathbf{r}'_\text{pos}\|^2$
- 关节速度/加速度行系数直接用 $q'(u_m)$，无需 $\mathbf{J}^{-1}$

### 10.4 奇异点附近的行为

关节空间方案下，Jacobian 以**正向**方式进入约束，行为与全笛卡尔方案相反：

$$
\text{奇异点处：} \quad \mathrm{rank}(\mathbf{J}) < 6 \implies \mathbf{J}_\text{pos} \cdot \mathbf{q}'(u) \to \mathbf{0}\;\text{（若 } \mathbf{q}' \text{ 接近 } \ker\mathbf{J} \text{）}
$$

$$
\kappa(u_\text{sing}) = \|\mathbf{J}_\text{pos} \cdot \mathbf{q}'\|^2 \to 0
\implies \frac{v_\text{cart,max}^2}{\kappa} \to \infty
$$

**笛卡尔速度约束在奇异点附近自动放松**（因为关节在动但 TCP 不动），关节速度约束主导，LP 无需做任何特殊处理。

速度剖面对比（穿越肘部奇异，$q_3 \to \pi$）：

```
v_tcp
  │
  │  全笛卡尔方案（c_i → ∞，减速）
  │    ╭───────╮           ╭───────╮
  │   ╱         ╲         ╱         ╲
  │──╱            ╲───────            ╲──
  │                ↑ 奇异点（v → 0）
  │
  │  关节空间方案（κ → 0，约束放松，速度由关节约束决定）
  │    ╭───────────────────────────────╮
  │   ╱                                 ╲
  │──╱                                   ╲──
  │         奇异点处 v_tcp 可能很小，但不由 LP 强制
```

### 10.5 与现有代码的对应关系

这个方案与现有 `TRAFO=false` 分支（关节坐标编程）**高度吻合**，核心机制已经实现：

```matlab
% buildConstr.m（TRAFO=false 分支，已有代码）
r1D_r = ctx.kin.v_relative(r0D, r1D);
%         ↑ 调用 RobotKinematics.v_relative()
%         内部计算：v_t = J(q) · r1D，即 J(q) · q'(u)

v_max(end, :) = (windowCurv(k).Info.FeedRate ./ vecnorm(r1D_r(ctx.cfg.indCart, :))).^2;
%                                               ↑ vecnorm(J_pos · q'(u)) = √κ(u_m)
%               → f_max_cart = (v_cart_max / √κ)² = v_cart_max² / κ    ✓
```

**唯一需要的修改**：在构造关节空间曲线段时，将 `FeedRate` 字段设为 $v_\text{cart,max}$：

```matlab
% build_joint_curves（修改）
function CurvArray = build_joint_curves(waypoints, v_cart_max)
N = size(waypoints, 2);
for k = 1:N-1
    CurvArray(k) = RobotCurvStruct(CurveType.Line, ...
        waypoints(:, k), waypoints(:, k+1), ...
        v_cart_max, false);   % ← FeedRate = v_cart_max（原来传入 feedrate 关节速度，现改为 TCP 速度上限）
end
end
```

`v_relative()` 内部已经调用 `geometric_jacobian()` 并执行 $\mathbf{J} \cdot \mathbf{q}'$，无需任何新接口。

### 10.6 $\kappa(u_m)$ 的几何含义

$\kappa(u_m) = \|\mathbf{J}_\text{pos}(\mathbf{q})\,\mathbf{q}'\|^2$ 是关节速度方向 $\mathbf{q}'$ 在笛卡尔位置空间的**投影放大率**，反映了"单位参数速度 $\dot{u}$ 驱动多大的 TCP 线速度"：

$$
v_\text{tcp} = \sqrt{\kappa(u_m)} \cdot \dot{u}
$$

| $\kappa$ 的值 | 物理含义 | $\dot{u}^2$ 上限 |
|---|---|---|
| $\kappa \gg 1$ | 该方向关节运动高效传递到 TCP 位移 | $v_\text{cart,max}^2 / \kappa$ 很小，TCP 速度约束紧 |
| $\kappa \approx 1$ | 关节运动与 TCP 位移约等比 | 与关节速度约束量级相当 |
| $\kappa \to 0$ | 接近奇异或关节运动在零空间内 | 笛卡尔约束自动放松，不激活 |

对于直线段（$\mathbf{q}' = \text{const}$），$\kappa(u_m)$ 随 $u_m$ 变化（因为 $\mathbf{J}(\mathbf{q}(u_m))$ 随关节角变化），需要在每个离散点逐点计算。

### 10.7 两种方案的适用场景选择指南

```
需要精确笛卡尔路径（直线/圆弧）？
  ├─ 是 → 全笛卡尔方案（第二~六章）
  │         需要 IK + J⁻¹，代码改动大
  │         适用：焊接、涂胶、精密装配
  │
  └─ 否 → 关节空间 + 笛卡尔速度约束（本章）
            仅需正向 J，代码改动极小
            适用：搬运、点位控制、教导再现

  在选择关节空间方案后，还需考虑：
    笛卡尔路径形状要求？
    ├─ 无要求 → 直接线性插值（本章 10.2.1）
    └─ 需要近似直线 → 细分路径点（增大 N），相邻点间弦误差 ≈ L²/(8R)
```

### 10.8 附录：两方案关键公式对比

| 公式项 | 全笛卡尔方案 | 关节空间简化方案 |
|---|---|---|
| 速度系数 $c_i$ | $[\mathbf{J}^{-1}(\mathbf{q})\,\mathbf{r}'(u)]_i$（逆向，奇异敏感） | $q'_i(u)$（直接，无奇异问题） |
| 笛卡尔速度系数 | $\|\mathbf{r}'_\text{pos}(u)\|^2$（已知，路径切线） | $\kappa(u_m) = \|\mathbf{J}_\text{pos}\,\mathbf{q}'\|^2$（需正向 $\mathbf{J}$） |
| 加速度系数 $A_{2,i}$ | $[\mathbf{J}^{-1}\mathbf{r}'' - \mathbf{J}^{-1}\frac{d\mathbf{J}}{du}\mathbf{J}^{-1}\mathbf{r}']_i$ | $q''_i(u)$（线性段为 0） |
| Jerk 精度 | 近似（忽略耦合项，误差 5%~15%） | 精确（关节空间无耦合） |
| 奇异点速度趋势 | $\dot{u} \to 0$（约束越来越紧） | $\kappa \to 0$（约束自动放松） |
| IK 调用 | 每个 $u_m$ 一次 | 不需要 |
| $\mathbf{J}^{-1}$ 调用 | 每个 $u_m$ 一次 | 不需要 |
| $\mathbf{J}$ 正向调用 | 不需要 | 每个 $u_m$ 一次（仅 `v_relative`） |

---

*文档版本：v1.2（新增§10 关节空间简化方案）| 日期：2026-05-15 | 基于 OpenCN r3.x 框架*
