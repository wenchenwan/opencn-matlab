# B 样条曲线学习笔记

> 本文结合 OpenCN 项目代码（`common/Feedopt/bspline/`、`CalcBspline_Lee.m` 等）系统讲解 B 样条的数学原理与工程实现。

---

## 一、为什么用 B 样条

CNC 加工中轨迹有这些特点：

- G-code 由大量短直线段组成，直接执行会产生速度突变；
- 需要一种**光滑、局部可控、对数值友好**的曲线表示。

B 样条恰好满足：

| 性质 | 说明 |
| --- | --- |
| 局部支撑 | 移动一个控制点，只影响附近一段曲线，不改变全局形状 |
| 任意阶光滑 | 可以是 C² 甚至更高连续的（由阶次决定） |
| 凸包性 | 曲线在控制点的凸包内，数值稳定 |
| 变差缩减性 | 不会比控制折线振荡更多 |
| 包含多项式 | Bézier、多项式曲线都是 B 样条的特殊情况 |

---

## 二、核心概念：节点向量

### 2.1 什么是节点向量

节点向量 $T = [t_0, t_1, \ldots, t_{m}]$ 是一列**非递减实数**，定义了参数域的分割方式。

```text
t_0 ≤ t_1 ≤ ... ≤ t_m
```

节点数 $m+1$、控制点数 $n+1$、阶次 $p$ 满足：

$$m = n + p + 1$$

即：**节点数 = 控制点数 + 阶次 + 1**

### 2.2 节点的重复度

同一个值出现多次叫做**重节点（knot multiplicity）**，重复度为 $k$ 的节点使曲线在该处降低 $k-1$ 阶连续性：

| 重复度 | 连续性 |
| --- | --- |
| 1 | $C^{p-1}$（最光滑） |
| 2 | $C^{p-2}$ |
| p（最大） | $C^0$（位置连续，导数不连续） |
| p+1 | 不连续（端点夹紧时用） |

### 2.3 夹紧 B 样条（Clamped B-Spline）

端点节点重复度 = 阶次，这样**曲线端点恰好通过第一个和最后一个控制点**：

```text
T = [0,0,...,0, t_p, ..., t_{m-p}, 1,1,...,1]
     ←p个0→                         ←p个1→
```

OpenCN 中 Lee 算法生成的样条正是夹紧 B 样条：

```matlab
% CalcBspline_Lee.m
nMult = cfg.LeeSplineDegree - 1;          % 端点重复度 = 阶次 - 1（注意 order = degree + 1）
knots = [ zeros(1, nMult), u, ones(1, nMult) ];
```

---

## 三、基函数：Cox-de Boor 递推

B 样条基函数 $N_{i,p}(t)$ 由递推定义。

**零阶（p=0）：**

$$N_{i,0}(t) = \begin{cases} 1 & t_i \leq t < t_{i+1} \\ 0 & \text{其他} \end{cases}$$

**p 阶递推（p ≥ 1）：**

$$N_{i,p}(t) = \frac{t - t_i}{t_{i+p} - t_i} N_{i,p-1}(t) + \frac{t_{i+p+1} - t}{t_{i+p+1} - t_{i+1}} N_{i+1,p-1}(t)$$

> 约定 $0/0 = 0$（当节点间距为 0 时）。

### 直觉理解

把参数 $t$ 想象成一列火车在时间轴上行进：

- $N_{i,0}(t)$ 是一个"矩形脉冲"，只在 $[t_i, t_{i+1})$ 有值；
- $N_{i,1}$ 是两个矩形的加权平均，得到三角形；
- $N_{i,2}$ 是三角形的加权平均，得到二次（抛物线形）；
- $N_{i,p}$ 是 $p$ 个矩形"平均"出来的，得到 $p$ 次多项式，支撑区间为 $[t_i, t_{i+p+1})$。

### 关键性质

- **局部支撑**：$N_{i,p}(t) \neq 0$ 只在 $[t_i, t_{i+p+1})$ 内；
- **非负性**：$N_{i,p}(t) \geq 0$；
- **单位分解**：$\sum_i N_{i,p}(t) = 1$（这保证了仿射不变性）；
- **支撑宽度**：每个基函数恰好跨 $p+1$ 个节点区间。

---

## 四、B 样条曲线定义

给定 $n+1$ 个控制点 $P_0, P_1, \ldots, P_n \in \mathbb{R}^d$，$p$ 阶 B 样条曲线为：

$$r(t) = \sum_{i=0}^{n} N_{i,p}(t) \cdot P_i, \quad t \in [t_p, t_{n+1}]$$

矩阵形式（在 M 个离散点 $t_1, \ldots, t_M$ 处）：

$$\begin{bmatrix} r(t_1) \\ \vdots \\ r(t_M) \end{bmatrix} = \underbrace{\begin{bmatrix} N_{0,p}(t_1) & \cdots & N_{n,p}(t_1) \\ \vdots & & \vdots \\ N_{0,p}(t_M) & \cdots & N_{n,p}(t_M) \end{bmatrix}}_{\text{BasisVal} \in \mathbb{R}^{M \times (n+1)}} \cdot \underbrace{\begin{bmatrix} P_0 \\ \vdots \\ P_n \end{bmatrix}}_{\text{coeff}}$$

OpenCN 代码中：

```matlab
% EvalBSpline.m
for j = 1 : M
    [r0D(j,:), r1D(j,:), r2D(j,:), r3D(j,:)] = ...
        bspline_eval_vec(sp.Bl, sp.coeff(j,:), u_vec);
end
% r0D(j,:) 是第 j 个维度（轴）在 u_vec 各点的位置值
```

---

## 五、导数

### 5.1 参数导数

B 样条的导数仍然是 B 样条，阶次降低 1，系数差分：

$$r'(t) = p \sum_{i=0}^{n-1} \frac{P_{i+1} - P_i}{t_{i+p+1} - t_{i+1}} N_{i,p-1}(t)$$

类似地，$r''(t)$、$r'''(t)$ 可以继续对系数差分。实际实现中底层 C 库（`c_spline.c`，基于 GSL）直接计算各阶导数，接口：

```matlab
% bspline_base_eval 返回：
BasisVal     % N_{i,p}(u)     -- 0阶
BasisValD    % N'_{i,p}(u)    -- 1阶导数对应的基函数矩阵
BasisValDD   % N''_{i,p}(u)   -- 2阶
BasisValDDD  % N'''_{i,p}(u)  -- 3阶
BasisIntegr  % ∫N_{i,p}(u)du  -- 积分（用于目标函数）
```

### 5.2 物理量与参数导数的关系

轨迹参数化为 $u \in [0,1]$（与时间无关，纯几何参数）：

| 物理量 | 公式 |
| --- | --- |
| 速度 | $V = r'(u) \cdot \dot{u}$ |
| 加速度 | $A = r''(u) \cdot \dot{u}^2 + r'(u) \cdot \ddot{u}$ |
| 跃度（jerk） | $J = r'''(u) \cdot \dot{u}^3 + 3r''(u)\cdot\dot{u}\ddot{u} + r'(u)\cdot\dddot{u}$ |

令 $w(u) = v^2(u) = \|r'(u)\|^2 \cdot \dot{u}^2$（速度平方），则：

$$\ddot{u} = \frac{w'(u)}{2\|r'(u)\|^2}, \quad w'(u) = \frac{dw}{du}$$

这是进给率 LP 优化的出发点（把速度平方作为决策变量，使加速度约束线性化）。

---

## 六、参数化：如何给数据点分配参数值

拟合数据点 $Q_0, Q_1, \ldots, Q_N$ 时，需要为每个点分配参数 $u_k$。参数化方法影响结果曲线的质量。

### 6.1 等距参数化（均匀）

$$u_k = \frac{k}{N}$$

简单，但当数据点间距不均匀时曲线会变形。

### 6.2 弦长参数化（Chord Length）

$$d_k = \|Q_k - Q_{k-1}\|, \quad u_k = \frac{\sum_{j=1}^{k} d_j}{\sum_{j=1}^{N} d_j}$$

更符合物理距离，最常见的方法。

### 6.3 四分之一次幂参数化（1/4-power，Lee 方法）

$$d_k = \|Q_k - Q_{k-1}\|^{1/2}, \quad u_k \propto \sum_{j=1}^{k} d_j^{1/2}$$

Lee（1989）提出，等价于：

$$u_k \propto \sum_{j=1}^{k} \|Q_j - Q_{j-1}\|^{1/2}$$

OpenCN 代码：

```matlab
% CalcBspline_Lee.m
du = sum( (diff(points.').^2).' );   % du(k) = ||Q_k - Q_{k-1}||²
u  = cumsum( [0, du.^(1/4)] );       % u(k) ∝ ||Q_k - Q_{k-1}||^(1/2)
u  = u / u(end);                     % 归一化到 [0,1]
```

**为什么用 1/4 次幂（而不是 1/2 次幂即弦长）？**

理论上，最优参数化应使节点分布与曲率变化率（挠曲率）成正比。经验和数学分析表明 1/4 次幂在控制点不均匀分布时能更好地抑制龙格（Runge）振荡，拟合精度更高。这是 Lee 算法的核心贡献之一。

---

## 七、样条插值：Lee 算法

目标：给定 $N+1$ 个插值点 $Q_0, \ldots, Q_N$，求 $N+2$ 个 B 样条系数 $c_0, \ldots, c_{N+1}$，使曲线**精确通过每个数据点**，且**端点二阶导数（曲率）为 0**（自然样条条件）。

### 7.1 建立线性方程组

在每个插值点 $u_k$ 处要求 $r(u_k) = Q_k$，写成矩阵方程：

$$\underbrace{N(u_k)}_{N_{i,p}(u_k)} \cdot c = Q_k$$

加上端点曲率边界条件（二阶导数为 0）：

$$r''(0) = 0 \Rightarrow \text{BasisValDD0} \cdot c = 0$$
$$r''(1) = 0 \Rightarrow \text{BasisValDD1} \cdot c = 0$$

组合成完整方程组（$(N+2) \times (N+2)$ 方阵）：

$$A \cdot c = B$$

$$A = \begin{bmatrix} \text{BasisValDD0} \\ N(u_0) \\ N(u_1) \\ \vdots \\ N(u_N) \\ \text{BasisValDD1} \end{bmatrix}, \quad B = \begin{bmatrix} 0 \\ Q_0 \\ Q_1 \\ \vdots \\ Q_N \\ 0 \end{bmatrix}$$

代码：

```matlab
% CalcBspline_Lee.m
[BasisVal, BasisValDD0, BasisValDD1] = bspline_eval_lee(Bl, nCoeff, u);
A = [BasisValDD0; BasisVal; BasisValDD1];
B = [zeros(1,nAxis); points.'; zeros(1,nAxis)];
```

### 7.2 为什么是三对角矩阵

B 样条基函数具有**局部支撑**性：$N_{i,p}(u_k)$ 只在 $u_k \in [t_i, t_{i+p+1})$ 时非零。对 3 阶（degree=3）样条，每个参数值 $u_k$ 至多激活相邻 4 个基函数。

插值矩阵的每一行最多有 $p+1$ 个非零元素，对 3 阶样条排列后近似三对角（更准确说是带状矩阵）。经过 `swap_lines` 对行重排后，矩阵变为严格三对角：

```matlab
[A] = swap_lines(A);   % 将边界条件行与相邻插值行对换
[v_m, v_l, v_u] = extract_vectors(A);   % 提取主对角、下对角、上对角
c = tridiag(v_m, v_l, v_u, B);          % Thomas 算法 O(N) 求解
```

### 7.3 Thomas 算法（追赶法）

对于 $n \times n$ 三对角线性方程组：

$$\begin{bmatrix} a_1 & c_1 & & \\ b_2 & a_2 & c_2 & \\ & \ddots & \ddots & \ddots \\ & & b_n & a_n \end{bmatrix} \begin{bmatrix} y_1 \\ y_2 \\ \vdots \\ y_n \end{bmatrix} = \begin{bmatrix} f_1 \\ f_2 \\ \vdots \\ f_n \end{bmatrix}$$

**前向消元（消去下对角 $b$）：**

```text
w = a[1];  y[1] = f[1] / w
for i = 2 to n:
    v[i-1] = c[i-1] / w
    w = a[i] - b[i] * v[i-1]
    y[i] = (f[i] - b[i] * y[i-1]) / w
```

**后向回代（消去上对角 $c$）：**

```text
for j = n-1 downto 1:
    y[j] = y[j] - v[j] * y[j+1]
```

复杂度 $O(N)$，远优于通用高斯消元 $O(N^3)$。代码：

```matlab
% tridiag.m（Thomas 算法实现）
w = a(1); y(1,:) = f(1,:) / w;
for i = 2 : n
    v(i-1) = c(i-1) / w;
    w       = a(i) - b(i) * v(i-1);
    y(i,:)  = (f(i,:) - b(i) * y(i-1,:)) / w;
end
for j = n-1 : -1 : 1
    y(j,:) = y(j,:) - v(j) * y(j+1,:);
end
```

---

## 八、弧长计算

B 样条曲线的弧长没有解析表达式，需要数值积分：

$$L(u_1, u_2) = \int_{u_1}^{u_2} \|r'(u)\| \, du$$

### 8.1 Gauss-Legendre 积分

将积分区间 $[a, b]$ 变换到 $[-1, 1]$：

$$\int_a^b f(u) \, du = \frac{b-a}{2} \int_{-1}^{1} f\!\left(\frac{a(1-\xi)+b(1+\xi)}{2}\right) d\xi \approx \frac{b-a}{2} \sum_{k=1}^{N} w_k f(\xi_k)$$

其中 $\xi_k, w_k$ 是预计算的 GL 节点和权重（5 节点精度高于 10 阶多项式）。

代码：

```matlab
% splineLengthApprox_Interval.m
uvec = (u0*(1-GL_X) + u1*(1+GL_X)) / 2;   % 线性映射 [-1,1] → [u0,u1]
[~, r1D] = EvalBSpline(spline, uvec);       % 计算各点的参数导数
r1Dnorm = MyNorm(r1D);                      % ||r'(u)||
L = r1Dnorm * GL_W * (u1-u0) / 2;          % GL 积分
```

### 8.2 分段预计算（加速查找）

将总弧长拆为各节点区间的弧长之和，预存在 `sp.Lk`：

```matlab
% SplineLengthApproxGL_tot.m
Knots = sp.knots(4:end-3);      % 去掉端点重节点
a = Knots(1:end-1);  b = Knots(2:end);     % 各区间端点
Umat = (a.*(1-GL_X) + b.*(1+GL_X)) / 2;   % 各区间 GL 节点
Lk = sum(GL_W .* reshape(‖r'(Umat)‖, GL_N, K)) .* (b-a)/2;
L  = sum(Lk);
```

查询 $L(u_1, u_2)$ 时：

1. 定位 $u_1, u_2$ 所在节点区间；
2. 中间完整区间直接查表（$O(1)$）；
3. 两端不完整区间再做一次 GL 积分；
4. 结果 = $\sum L_k^{\text{中间}} - L_{\text{start}} - L_{\text{end}}$。

### 8.3 弧长反求参数（弧长重参数化）

给定弧长 $L$，求参数 $u$ 使 $L(u_0, u) = L$：

```matlab
% splineLengthFindU.m
% 第一步：利用 Lk 表快速定位目标区间（O(K) 累计和查找）
LEnd = cumsum(Lk(kStart:kMax)) - LStart;
kEnd = find(LEnd >= L, 1, "first");

% 第二步：在目标节点区间内二分法 (bisection)
% 精度 tol = 1E-7，最多 1000 次迭代
[u, count] = bisection(uLeft, uRight, cfg, spline, LDiff, ...);
```

---

## 九、项目中的两类 B 样条

OpenCN 中 B 样条有两种完全不同的用途，要注意区分：

### 9.1 几何 B 样条（描述轨迹形状）

| 属性 | 值 |
| --- | --- |
| 用途 | 拟合压缩后的折线点集，生成光滑轨迹 |
| 阶次 | `cfg.LeeSplineDegree = 4`（三次，C² 连续） |
| 参数化 | Lee 1/4 次幂 |
| 系数意义 | 控制点坐标（单位：mm 或 rad） |
| 生成函数 | `CalcBspline_Lee()` |
| 存储 | `CurvStruct.sp`（`constrSpline` 结构体） |
| 求值 | `EvalBSpline()` → 返回 $r, r', r'', r'''$ |

### 9.2 优化 B 样条（描述速度平方 $w(u) = v^2(u)$）

| 属性 | 值 |
| --- | --- |
| 用途 | LP 优化的决策变量基底（把速度平方展开为 B 样条） |
| 阶次 | `cfg.SplineDegree = 3`（二次，计算快） |
| 断点分布 | 均匀断点（`UseLinearBreakpoints = true`） |
| 系数意义 | $c_j$（B 样条系数，$w(u) \approx \sum c_j B_j(u)$） |
| 生成函数 | `bspline_create(degree, breakpoints)` |
| 存储 | `ctx.Bl`（基底句柄），系数 `Coeff` 是 LP 求解结果 |
| 求值 | `bspline_base_eval()` → 返回 `BasisVal, BasisValD, ...` |

**关键区别**：几何样条的系数是控制点坐标，插值后固定不变；优化样条的系数是 LP 求解的决策变量 $x$，每个窗口求解一次。

---

## 十、数据结构总结

```text
constrSpline（几何样条结构体）：
    .Bl      : BaseSpline 结构体
        .handle   : C 库 GSL 样条对象句柄
        .ncoeff   : 系数数量 = nbreak + degree - 2
        .order    : 阶次（= degree + 1）
    .coeff   : [NDim × ncoeff] 控制点坐标
    .knots   : [1 × m+1] 节点向量
    .Ltot    : 总弧长（预计算）
    .Lk      : [1 × K] 各节点区间弧长（预计算）
```

```text
ctx.Bl（优化样条基底，单段，复用）：
    .handle  : C 库句柄
    .ncoeff  : N = NBreak + SplineDegree - 2
    .order   : SplineDegree + 1

LP 求解变量：
    Coeff    : [N × K] 每段的 B 样条系数（速度平方展开）
    BasisVal : [M × N] 在 M 个离散点处的基函数矩阵（buildConstr 中计算）
```

---

## 十一、完整流程图（OpenCN 中样条的生命周期）

```text
G-code 折线点集
    │
    ├─ 压缩（compressCurvStructs）
    │      将共线线段合并，收集批次点集
    │
    ├─ Lee 拟合（CalcBspline_Lee）
    │      1/4-power 参数化 → 建三对角方程组 → Thomas 算法求系数 c
    │      → CurvStruct.sp（几何 B 样条）
    │
    ├─ 弧长预计算（SplineLengthApproxGL_tot）
    │      GL 积分逐区间 → sp.Lk, sp.Ltot
    │
    ├─ 分割（splitCurvStruct）
    │      按弧长 LSplit 用 splineLengthFindU 定位分割点 → cutCurvStructU
    │
    ├─ 优化（buildConstr + LP 求解）
    │      bspline_base_eval(ctx.Bl, u_disc) → BasisVal, BasisValD, ...
    │      约束矩阵 A, b → c_simplex → 系数 Coeff
    │
    └─ 重采样（resampleCurv）
           EvalBSpline(sp, u) + computeProfileU(Coeff, BasisVal) → 位置+速度时间序列
```

---

## 十二、常见疑问

**Q1：为什么样条系数数量是 `nbreak + degree - 2` 而不是 `nbreak`？**

`bspline_create` 的 `ncoeff = nbreak + degree - 2`，这是 GSL 库的约定。对于 B 样条：系数数 = 节点区间数 + degree - 1 = (nbreak - 1) + degree - 1 = nbreak + degree - 2（因为夹紧节点两端各有 degree 重节点，去掉后有 nbreak 个不同节点，形成 nbreak-1 个区间）。

**Q2：Lee 算法的矩阵为什么不是严格三对角，需要 swap_lines？**

原始矩阵的第一行是边界条件（$r''(0)=0$），对应节点 $u=0$ 处的基函数二阶导数，其非零列不是第 1 列而是靠前的几列；最后一行类似。通过 swap_lines 把第 2 行（第一个插值点）换到第 1 行位置，把边界条件移到第 2 行，使矩阵结构满足三对角求解的要求。

**Q3：GL 积分为什么选 5 个节点？**

5 节点 GL 积分对 $\leq 9$ 次多项式精确，三次 B 样条的 $\|r'(u)\|$ 是分段 $C^2$ 函数，每段区间内用 5 个节点已足够精确。节点数在 `cfg.GaussLegendreN = 5` 中可调整。

**Q4：几何样条和优化样条的阶次不同（4 vs 3），为什么？**

几何样条需要 $C^2$ 连续（加速度连续，避免运动突变）→ 3 次（degree=3，order=4）；优化样条只需要 $C^1$（速度连续）→ 2 次（degree=2），而且越低阶次 LP 规模越小，求解越快。

---

> 参考代码：`agency/usr/matlab/opencn-matlab/common/Feedopt/`
