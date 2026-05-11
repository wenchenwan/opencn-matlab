# SplineLengthApproxGL_tot — B 样条弧长的 Gauss-Legendre 数值积分

---

## 1. 问题：参数曲线的弧长

对于一条由参数 $u$ 描述的空间曲线 $\mathbf{r}(u) = (x(u),\, y(u),\, z(u))$，其在参数区间 $[a, b]$ 上的弧长定义为：

$$L = \int_a^b \left\| \mathbf{r}'(u) \right\| du = \int_a^b \sqrt{x'(u)^2 + y'(u)^2 + z'(u)^2} \; du$$

B 样条曲线的导数 $\mathbf{r}'(u)$ 没有解析积分，因此必须用**数值积分**方法近似计算。

---

## 2. 为什么按节点区间分段积分

夹紧 B 样条（Clamped B-spline）的节点向量形如：

```
[t0, t0, t0, t0,  t1, t2, ..., tK,  tK, tK, tK, tK]
  ← 端点重节点 →   ← 内部节点 →   ← 端点重节点 →
```

两端各有 4 个重节点（4 阶样条），去掉后得到 $K+1$ 个有效节点，划分出 $K$ 个区间：

$$[t_0, t_1],\; [t_1, t_2],\; \ldots,\; [t_{K-1}, t_K]$$

在每个区间内，B 样条基函数的支撑域恒定，$\mathbf{r}'(u)$ 光滑，适合用 GL 积分。

代码对应：

```matlab
Knots = sp.knots(4:end-3);   % 去掉两端各3个重节点
a = Knots(1:end-1);          % 各区间左端点向量
b = Knots(2:end);            % 各区间右端点向量
```

---

## 3. Gauss-Legendre 数值积分

### 3.1 标准形式（定义在 $[-1, 1]$）

$N$ 点 Gauss-Legendre 积分公式：

$$\int_{-1}^{1} g(\xi)\, d\xi \approx \sum_{j=1}^{N} w_j \cdot g(\xi_j)$$

其中 $\xi_j$ 是 Legendre 多项式 $P_N(\xi) = 0$ 的根（GL 节点），$w_j$ 是对应权重。

对于 $N=5$ 点 GL 积分，节点和权重为（对称分布）：

| 节点 $\xi_j$ | 权重 $w_j$ |
|-------------|-----------|
| $0$ | $8/9 \approx 0.5689$ |
| $\pm 0.5385$ | $0.4786$ |
| $\pm 0.9062$ | $0.2369$ |

$N=5$ 对 $\leq 9$ 次多项式精确，对光滑函数收敛极快。

### 3.2 换元：从 $[-1,1]$ 映射到任意区间 $[a_k, b_k]$

令

$$u = \varphi(\xi) = \frac{a_k(1-\xi) + b_k(1+\xi)}{2} = \frac{a_k+b_k}{2} + \frac{b_k-a_k}{2}\xi$$

则

$$du = \frac{b_k - a_k}{2} \, d\xi$$

代入弧长积分：

$$L_k = \int_{a_k}^{b_k} \left\| \mathbf{r}'(u) \right\| du = \int_{-1}^{1} \left\| \mathbf{r}'\!\left(\varphi(\xi)\right) \right\| \cdot \frac{b_k-a_k}{2} \, d\xi$$

用 GL 公式近似：

$$\boxed{L_k \approx \frac{b_k - a_k}{2} \sum_{j=1}^{N} w_j \cdot \left\| \mathbf{r}'(u_{k,j}) \right\|}$$

其中 GL 节点映射到第 $k$ 个区间：

$$u_{k,j} = \frac{a_k(1-\xi_j) + b_k(1+\xi_j)}{2}$$

---

## 4. 代码实现的矩阵化推导

代码将所有区间的计算**批量并行**，避免循环。

### 4.1 节点批量映射（第32行）

```matlab
Umat = (bsxfun(@times, a, (1-GL_X)) + bsxfun(@times, b, (1+GL_X))) / 2;
```

`GL_X` 是 $N \times 1$ 列向量，`a`、`b` 是 $1 \times K$ 行向量。

`bsxfun` 广播后得到 $N \times K$ 矩阵：

$$U_{mat} = \begin{bmatrix}
u_{1,1} & u_{2,1} & \cdots & u_{K,1} \\
u_{1,2} & u_{2,2} & \cdots & u_{K,2} \\
\vdots  & \vdots  & \ddots & \vdots  \\
u_{1,N} & u_{2,N} & \cdots & u_{K,N}
\end{bmatrix}$$

第 $k$ 列 = 第 $k$ 个区间的所有 GL 节点坐标。

### 4.2 展平后批量求导（第33-37行）

```matlab
Uvec = Umat(:)';            % 展平为 1 × (N·K) 行向量
[~, r1D]  = EvalBSpline(Curv, Uvec);  % 批量求 r'(u)，尺寸 dim × (N·K)
r1Dnorm   = MyNorm(r1D);    % 逐列取模，得 1 × (N·K)
```

将所有区间的所有 GL 节点拼成一个长向量，**一次调用**完成所有导数计算，避免逐区间循环的开销。

### 4.3 重组并加权求和（第40-41行）

```matlab
r1DnormM = reshape(r1Dnorm, GL_N, length(Knots)-1);
Lk = sum(bsxfun(@times, GL_W, r1DnormM)) .* (b-a) / 2;
```

`reshape` 还原为 $N \times K$ 矩阵，每列对应一个区间的 $N$ 个 $\|\mathbf{r}'(u_{k,j})\|$ 值。

`bsxfun(@times, GL_W, r1DnormM)` 将权重 $w_j$ 广播乘到每列：

$$\begin{bmatrix} w_1 \|\mathbf{r}'_{1,1}\| & w_1 \|\mathbf{r}'_{2,1}\| & \cdots \\ w_2 \|\mathbf{r}'_{1,2}\| & w_2 \|\mathbf{r}'_{2,2}\| & \cdots \\ \vdots & \vdots \end{bmatrix}$$

`sum(...)` 对每列求和，得到 $1 \times K$ 的行向量，再乘以 $\frac{b_k - a_k}{2}$：

$$L_k = \frac{b_k - a_k}{2} \sum_{j=1}^{N} w_j \cdot \|\mathbf{r}'(u_{k,j})\|$$

### 4.4 总弧长

```matlab
L = sum(Lk);
```

$$L = \sum_{k=1}^{K} L_k$$

---

## 5. 完整公式汇总

$$u_{k,j} = \frac{a_k(1-\xi_j) + b_k(1+\xi_j)}{2}, \quad j=1,\ldots,N,\; k=1,\ldots,K$$

$$L_k = \frac{b_k - a_k}{2} \sum_{j=1}^{N} w_j \cdot \left\|\mathbf{r}'(u_{k,j})\right\|$$

$$L = \sum_{k=1}^{K} L_k$$

---

## 6. 数值精度与设计取舍

| 设计选择 | 原因 |
|---------|------|
| 5 点 GL（$N=5$）| 对 9 次以下多项式精确，B 样条导数光滑，5 点已足够 |
| 按节点区间分段 | 每段内 $\mathbf{r}'(u)$ 光滑，GL 收敛快；跨节点积分会遇到导数跳跃 |
| 矩阵批量化 | MATLAB 向量化操作比等价 for 循环快 10-100 倍 |
| 只计算一次（`initFeedoptPlan`）| 弧长不随进给速度变化，预计算后供 `splineLengthFindU` 查表复用 |

---

## 7. 在进给优化中的位置

```
initFeedoptPlan
    └── SplineLengthApproxGL_tot   ← 预算各区间弧长 Lk（本函数）
            ↓
        Lk 存入计划结构体
            ↓
splineLengthFindU（弧长反演）
    └── 用 Lk 做粗查表，定位参数 u 对应的弧长区间
            ↓
        细化插值，输出 u(s)
```

`Lk` 是弧长反演的基础数据，也是路径总长 `L` 的来源。
