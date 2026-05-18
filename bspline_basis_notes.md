# OpenCN B 样条基函数矩阵：BasisVal / BasisValD / BasisValDD

---

## 目录

1. [概述：三个矩阵是什么](#一概述三个矩阵是什么)
2. [计算来源：精确解析导数](#二计算来源精确解析导数)
3. [在 LP 中的物理映射](#三在-lp-中的物理映射)
4. [加速度约束：精确推导](#四加速度约束精确推导)
5. [Jerk 约束：为何需要线性化](#五jerk-约束为何需要线性化)
6. [buildConstr.m 注释勘误](#六buildconstrm-注释勘误)
7. [三个矩阵用途汇总](#七三个矩阵用途汇总)
8. [代码调用链](#八代码调用链)

---

## 一、概述：三个矩阵是什么

`BasisVal`、`BasisValD`、`BasisValDD` 是 **B 样条基函数对路径参数 $u$ 的解析导数**，在 $M$ 个离散采样点 `u_vec` $= [u_1, u_2, \ldots, u_M]$ 处预先求值后存为矩阵，尺寸均为 $[M \times N]$（$N$ = 每段 B 样条基函数数 = 系数数）：

$$
\text{BasisVal}[p,\, i] = B_i(u_p)
$$

$$
\text{BasisValD}[p,\, i] = \frac{dB_i}{du}\bigg|_{u_p}
$$

$$
\text{BasisValDD}[p,\, i] = \frac{d^2B_i}{du^2}\bigg|_{u_p}
$$

直观含义：**第 $p$ 行**是在参数点 $u_p$ 处，所有 $N$ 个基函数（及其导数）的值组成的行向量。

---

## 二、计算来源：精确解析导数

### 2.1 函数调用路径

```
initFeedoptPlan.m
  └── bspline_base_eval( Bl, u_vec )     % MATLAB 入口（一次性预计算）
        └── c_bspline_base_eval(...)      % C 底层实现（GSL B 样条库）
              └── 返回 BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr
```

`bspline_base_eval` 的函数签名：

```matlab
function [BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr] = ...
    bspline_base_eval(Bl, xvec)
%
% Outputs:
%   BasisVal    : [M×N] B 样条基函数值
%   BasisValD   : [M×N] B 样条基函数一阶导数（对 u）
%   BasisValDD  : [M×N] B 样条基函数二阶导数（对 u）
%   BasisValDDD : [M×N] B 样条基函数三阶导数（对 u，备用）
%   BasisIntegr : [N×1] 各基函数在 [0,1] 上的积分（目标函数用）
```

### 2.2 B 样条微分递推公式

计算使用**精确解析递推**，不是数值差分：

$$
B_{i,k}'(u) = \frac{k}{t_{i+k} - t_i}\,B_{i,k-1}(u) - \frac{k}{t_{i+k+1} - t_{i+1}}\,B_{i+1,k-1}(u)
$$

其中 $k$ 为 B 样条阶次，$\{t_i\}$ 为节点向量（knot vector）。高阶导数通过对上式递推应用得到。

### 2.3 预计算与复用

这三个矩阵在 `initFeedoptPlan` 中**只计算一次**，然后存入 `ctx`：

```matlab
% initFeedoptPlan.m
[BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr] = ...
    bspline_base_eval(Bl, u_vec);

ctx.BasisVal   = BasisVal;    % [M×N] 基函数值（LP 速度约束用）
ctx.BasisValD  = BasisValD;   % [M×N] 一阶导（LP 加速度约束用）
ctx.BasisValDD = BasisValDD;  % [M×N] 二阶导（LP Jerk 约束用）
```

整个优化过程中每次调用 `buildConstr` / `buildConstrJerk` 都**直接复用**，不重复计算。

---

## 三、在 LP 中的物理映射

### 3.1 决策变量与基函数的关系

LP 决策变量 $\mathbf{x} \in \mathbb{R}^N$ 是 B 样条系数向量。物理量 $w(u) = \dot{u}^2$（参数速度平方）用 B 样条展开为：

$$
w(u) = \mathbf{B}(u) \cdot \mathbf{x} = \text{BasisVal}[p, :] \cdot \mathbf{x} \quad (u = u_p)
$$

对路径参数 $u$ 求导（$'$ 表示 $d/du$）：

$$
w'(u_p) = \mathbf{B}'(u_p) \cdot \mathbf{x} = \text{BasisValD}[p,:] \cdot \mathbf{x}
$$

$$
w''(u_p) = \mathbf{B}''(u_p) \cdot \mathbf{x} = \text{BasisValDD}[p,:] \cdot \mathbf{x}
$$

这三个量均是 $\mathbf{x}$ 的**线性函数**——这正是选 $\dot{u}^2$ 而非 $\dot{u}$ 作为决策变量的核心原因。

### 3.2 时间导数与路径导数的关系

| 物理量 | 与决策变量的关系 | 线性性 |
|---|---|---|
| $\dot{u} = \sqrt{w}$ | $\sqrt{\text{BasisVal} \cdot \mathbf{x}}$ | **非线性** |
| $\dot{u}^2 = w$ | $\text{BasisVal} \cdot \mathbf{x}$ | **线性** |
| $\dot{u}^3 = w\sqrt{w}$ | $(\text{BasisVal} \cdot \mathbf{x})^{3/2}$ | **非线性** |
| $\ddot{u} = \frac{1}{2}w'$ | $\frac{1}{2}\text{BasisValD} \cdot \mathbf{x}$ | **线性** |
| $\dddot{u} = \frac{1}{2}w''\dot{u}$ | $\frac{1}{2}\text{BasisValDD} \cdot \mathbf{x} \cdot \sqrt{w}$ | **非线性** |

---

## 四、加速度约束：精确推导

### 4.1 $\ddot{u}$ 的精确表达式

这是整个加速度线性化的关键等式。令 $w = \dot{u}^2$，则：

$$
\frac{dw}{du} = \frac{dw/dt}{du/dt} = \frac{2\dot{u}\ddot{u}}{\dot{u}} = 2\ddot{u}
$$

$$
\boxed{\ddot{u} = \frac{1}{2}w'(u) = \frac{1}{2}\,\text{BasisValD}(u)\cdot\mathbf{x}}
\quad\text{（精确等式，无任何近似）}
$$

注意：分母中**没有** $\dot{u}$（即 $\sqrt{w}$）。

### 4.2 关节加速度的精确线性展开

以关节角 $q_i(u)$ 为例（`buildConstr.m` 中为广义坐标 `r_j`）：

$$
\ddot{q}_i = q''_i(u)\cdot\dot{u}^2 + q'_i(u)\cdot\ddot{u}
$$

代入 $\dot{u}^2 = w = \mathbf{B}\mathbf{x}$ 和 $\ddot{u} = \frac{1}{2}w' = \frac{1}{2}\mathbf{B}'\mathbf{x}$：

$$
\ddot{q}_i = q''_i(u_p)\cdot\mathbf{B}(u_p)\mathbf{x} + q'_i(u_p)\cdot\frac{1}{2}\mathbf{B}'(u_p)\mathbf{x}
= \underbrace{\left[q''_i(u_p)\,\text{BasisVal}[p,:] + \frac{1}{2}q'_i(u_p)\,\text{BasisValD}[p,:]\right]}_{\text{Acc}_i(p,:)}
\cdot\mathbf{x}
$$

即 `buildConstr.m` 中的代码：

```matlab
% buildConstr.m 第 220 行
Acc(ind,:,1) = r2D_a(j,:)' .* BasisVal + 0.5 * r1D_a(j,:)' .* BasisValD;
```

**这是精确等式**，不是近似。

### 4.3 LP 加速度不等式约束

$$
\pm\,\text{Acc}_i(p,:)\,\mathbf{x} \leq \ddot{q}_{i,\max}
\qquad\text{（第 $p$ 离散点，关节 $i$）}
$$

---

## 五、Jerk 约束：为何需要线性化

### 5.1 Jerk 的精确展开

对加速度 $\ddot{q}_i = q''_i w + \frac{1}{2}q'_i w'$ 再对 $t$ 求导：

$$
\dddot{q}_i = \sqrt{w}\left[q'''_i(u)\,w + \frac{3}{2}q''_i(u)\,w' + \frac{1}{2}q'_i(u)\,w''\right]
$$

各阶关系汇总（利用 $\dddot{u} = \frac{1}{2}w''\sqrt{w}$）：

$$
\begin{aligned}
\dot{u}     &= \sqrt{w}     & \dot{u}^2 &= w            & \dot{u}^3     &= w\sqrt{w}            \\[4pt]
\ddot{u}    &= \tfrac{1}{2}w' & \dddot{u} &= \tfrac{1}{2}w''\sqrt{w} & \dot{u}\cdot\ddot{u} &= \tfrac{1}{2}w'\sqrt{w}
\end{aligned}
$$

Jerk 含 $\sqrt{w}$ 因子，对 $\mathbf{x}$ 是 $O(w^{3/2})$ 的**非线性项**，无法直接写成 $[\ldots]\mathbf{x} \leq j_\text{max}$ 的线性约束。

### 5.2 两阶段 LP 线性化

**第一阶 LP**：只含速度 + 加速度约束（精确线性），求解得 $\mathbf{x}^*$，计算参考速度：

$$
\dot{u}_\text{ref}(u_p) = \sqrt{\text{BasisVal}[p,:]\cdot\mathbf{x}^*}
$$

**第二阶 LP**：冻结 $\sqrt{w} \approx \dot{u}_\text{ref}$（常数标量，不参与优化），Jerk 线性化为：

$$
\dddot{q}_i \approx \dot{u}_\text{ref}(u_p)\left[q'''_i\,\text{BasisVal}[p,:] + \frac{3}{2}q''_i\,\text{BasisValD}[p,:] + \frac{1}{2}q'_i\,\text{BasisValDD}[p,:]\right]\mathbf{x}
$$

LP Jerk 约束行：

$$
\boxed{
\text{Jerk}_i(p,:) = \dot{u}_\text{ref}(u_p)\left[
q'''_i\,\text{BasisVal}[p,:] + \frac{3}{2}q''_i\,\text{BasisValD}[p,:] + \frac{1}{2}q'_i\,\text{BasisValDD}[p,:]
\right]
}
$$

### 5.3 加速度与 Jerk 线性性的本质对比

| 约束类型 | 线性性 | 原因 | 处理方式 |
|---|---|---|---|
| **速度** $\dot{q}_i$ | 精确线性 | $\dot{q}_i^2 = q_i'^2 \cdot w$，$w = \mathbf{B}\mathbf{x}$ | 第一阶 LP 直接求解 |
| **加速度** $\ddot{q}_i$ | 精确线性 | $\ddot{u} = \frac{1}{2}w'$，$w' = \mathbf{B}'\mathbf{x}$ | 第一阶 LP 直接求解 |
| **Jerk** $\dddot{q}_i$ | 非线性 | 含 $\dot{u} = \sqrt{w}$ 因子 | 第二阶 LP（冻结 $\dot{u}_\text{ref}$）|

---

## 六、buildConstr.m 注释勘误

`buildConstr.m` 第 205~211 行注释写道：

```
由 udd = (dw/du) / (2·ud) = (B'(u)·x) / (2·sqrt(B(u)·x))
```

这个中间步骤**有误**——分母多除了一个 $\dot{u}$（即 $\sqrt{w}$）。

正确推导：

$$
\frac{dw}{du} = \frac{d(\dot{u}^2)/dt}{du/dt} = \frac{2\dot{u}\ddot{u}}{\dot{u}} = 2\ddot{u}
\;\Rightarrow\; \ddot{u} = \frac{w'}{2}
$$

代入后，注释中最终给出的代码 `Acc_j = r2D_j·BasisVal + 0.5·r1D_j·BasisValD` 对应的是**精确**的加速度表达式，结果是正确的。注释中的"$\approx$"（近似符号）是**误导性写法**，应为精确等式 "$=$"。

---

## 七、三个矩阵用途汇总

| 矩阵 | 尺寸 | 用途 | 出现位置 |
|---|---|---|---|
| `BasisVal` | $[M \times N]$ | 速度约束：$w(u_p) = \mathbf{B}[p,:]\mathbf{x}$；等式约束端点值；加速度约束第一项 | `buildConstr.m` |
| `BasisValD` | $[M \times N]$ | 加速度约束第二项：$\frac{1}{2}r'_j \cdot \mathbf{B}'[p,:]\mathbf{x}$；Jerk 约束第二项 | `buildConstr.m`, `buildConstrJerk.m` |
| `BasisValDD` | $[M \times N]$ | Jerk 约束第三项：$\frac{1}{2}q'_i \cdot \mathbf{B}''[p,:]\mathbf{x}$ | `buildConstrJerk.m` |
| `BasisIntegr` | $[N \times 1]$ | 目标函数：$\min -\mathbf{b}_\text{intgr}^\top \mathbf{x}$（最大化参数速度积分） | `FeedratePlanning_LP.m` |

---

## 八、代码调用链

```
initFeedoptPlan(cfg)
│
├── bspline_create(cfg.SplineDegree, linspace(0,1,cfg.NBreak))
│   └── 返回 Bl（含节点向量、阶次）
│
├── u_vec = linspace(0, 1, cfg.NDiscr)        % M 个离散采样点
│
└── bspline_base_eval(Bl, u_vec)               % 一次性预计算
    └── c_bspline_base_eval(...)               % C/GSL 底层精确递推
          ├── BasisVal    [M×N]  → ctx.BasisVal
          ├── BasisValD   [M×N]  → ctx.BasisValD
          ├── BasisValDD  [M×N]  → ctx.BasisValDD
          ├── BasisValDDD [M×N]  → ctx.BasisValDDD（备用）
          └── BasisIntegr [N×1]  → ctx.BasisIntegr

FeedratePlanning_LP(ctx, ...)
│
├── buildConstr(ctx, windowCurv, ...)
│   ├── 速度约束：A += [BasisVal; -BasisVal]
│   ├── 加速度约束：Acc = r2D·BasisVal + 0.5·r1D·BasisValD   ← 精确
│   └── 连续性等式：Aeq 端点行 = BasisVal([1,end], :)
│
└── buildConstrJerk(ctx, ...)                 % 第二阶 LP
    └── Jerk 约束：dot_u_ref · [q'''·BasisVal + 1.5·q''·BasisValD + 0.5·q'·BasisValDD]
                                                                    ← 线性化（冻结 dot_u_ref）
```

---

## 附录：关键等式速查

$$
w(u) = \dot{u}^2 = \mathbf{B}(u)\mathbf{x} \quad\Rightarrow\quad
\begin{cases}
\dot{u}   = \sqrt{w} \\[4pt]
\ddot{u}  = \dfrac{1}{2}w'(u) = \dfrac{1}{2}\mathbf{B}'(u)\mathbf{x} \quad\text{（精确）}\\[8pt]
\dddot{u} = \dfrac{1}{2}w''(u)\,\dot{u} = \dfrac{1}{2}\mathbf{B}''(u)\mathbf{x}\cdot\sqrt{w} \quad\text{（含 $\sqrt{w}$，非线性）}
\end{cases}
$$

$$
\underbrace{\ddot{q}_i = q''_i\,\mathbf{B}\mathbf{x} + \tfrac{1}{2}q'_i\,\mathbf{B}'\mathbf{x}}_{\text{精确线性，第一阶 LP}}
\qquad
\underbrace{\dddot{q}_i \approx \dot{u}_\text{ref}\!\left[q'''_i\mathbf{B} + \tfrac{3}{2}q''_i\mathbf{B}' + \tfrac{1}{2}q'_i\mathbf{B}''\right]\!\mathbf{x}}_{\text{线性化，第二阶 LP}}
$$

---

*文档版本：v1.0 | 日期：2026-05-15 | 对应代码：`bspline_base_eval.m`、`buildConstr.m`、`buildConstrJerk.m`*
