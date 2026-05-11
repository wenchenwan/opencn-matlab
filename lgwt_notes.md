# lgwt — Gauss-Legendre 节点与权重计算

本文档对 `lgwt.m` 的数学原理逐步推导，包括 Legendre 多项式、Bonnet 递推、Newton-Raphson 迭代和权重公式。

---

## 1. 目标：Gauss-Legendre 数值积分

**问题**：用 $N$ 个函数求值点近似计算定积分：

$$\int_a^b f(x)\, dx \approx \sum_{i=1}^{N} w_i \cdot f(x_i)$$

**Gauss-Legendre 最优性**：在所有 $N$ 点求积公式中，GL 公式对 $\leq 2N-1$ 次多项式**精确成立**，是同等计算量下精度最高的方案。

---

## 2. Legendre 多项式

### 2.1 定义

Legendre 多项式 $P_n(x)$ 定义在 $[-1, 1]$ 上：

$$P_0(x) = 1, \quad P_1(x) = x$$

高次项由 **Bonnet 三项递推**生成：

$$\boxed{k \cdot P_k(x) = (2k-1)\, x \cdot P_{k-1}(x) - (k-1)\, P_{k-2}(x)}$$

| 阶次 | 多项式 |
|------|--------|
| $P_0$ | $1$ |
| $P_1$ | $x$ |
| $P_2$ | $\frac{1}{2}(3x^2-1)$ |
| $P_3$ | $\frac{1}{2}(5x^3-3x)$ |
| $P_4$ | $\frac{1}{8}(35x^4-30x^2+3)$ |

### 2.2 关键性质

- $P_N(x)$ 在 $(-1,1)$ 内恰好有 $N$ 个实根，且关于原点对称
- **正交性**：$\int_{-1}^{1} P_m(x) P_n(x) dx = \frac{2}{2n+1} \delta_{mn}$
- $N$ 点 GL 积分的节点 $\{x_i\}$ **正是 $P_N(x)$ 的 $N$ 个根**

---

## 3. 代码中的下标约定

```matlab
N  = 输入N - 1      % 多项式阶次（= 节点数 - 1）
N1 = N + 1          % 节点总数（= 原始输入 N）
N2 = N + 2          % 递推终止列，补偿因子来源

L(:, k)  存放  P_{k-1}(y)   % 第 k 列 = k-1 次 Legendre 多项式
```

因此：
- `L(:, 1)` = $P_0(y) = 1$
- `L(:, 2)` = $P_1(y) = y$
- `L(:, N2)` = $P_{N1}(y)$，其根即为目标 GL 节点

---

## 4. 初始猜测

Newton-Raphson 需要好的初始值，直接用 **Chebyshev 节点**近似 $P_{N1}$ 的根：

$$y_i^{(0)} = \cos\!\left(\frac{(2i+1)\pi}{2N_1+2}\right) + \frac{0.27}{N_1} \sin\!\left(\frac{\pi \cdot x_u^{(i)} \cdot N}{N_2}\right), \quad i = 0, 1, \ldots, N$$

- **第一项**：Chebyshev 多项式 $T_{N1}(x)$ 的根，与 $P_{N1}$ 的根分布相近
- **第二项**：Lether（1978）扰动项，进一步减少 Newton-Raphson 迭代次数

代码对应：
```matlab
xu = linspace(-1,1,N1)';
y  = cos((2*(0:N)'+1)*pi/(2*N+2)) + (0.27/N1)*sin(pi*xu*N/N2);
```

---

## 5. Bonnet 递推建立 Vandermonde 矩阵

循环按 Bonnet 公式逐列填充 $L$：

```matlab
L(:,1) = 1;    % P_0
L(:,2) = y;    % P_1
for k = 2 : N1
    L(:,k+1) = ((2*k-1)*y.*L(:,k) - (k-1)*L(:,k-1)) / k;
end
```

递推展开（以 $k=2,3$ 为例）：

$$L(:,3) = \frac{3y \cdot y - 1}{2} = \frac{3y^2-1}{2} = P_2(y) \checkmark$$

$$L(:,4) = \frac{5y \cdot P_2 - 2P_1}{3} = \frac{5y(3y^2-1)/2 - 2y}{3} = \frac{5y^3-3y}{2} = P_3(y) \checkmark$$

循环结束后，`L(:, N2)` = $P_{N1}(y)$。

---

## 6. 导数公式

利用 Legendre 多项式导数的恒等式：

$$(1 - x^2)\, P'_n(x) = n\bigl(P_{n-1}(x) - x\, P_n(x)\bigr)$$

取 $n = N1$，得：

$$P'_{N1}(y) = \frac{N1\bigl(L(:,N1) - y \cdot L(:,N2)\bigr)}{1-y^2}$$

代码中用 $N2$ 替代 $N1$（差因子 $N2/N1$，在权重公式中补偿）：

```matlab
Lp = N2 * (L(:,N1) - y.*L(:,N2)) ./ (1-y.^2);
%  ↑ 实际值 = (N2/N1) × P'_{N1}(y)
```

---

## 7. Newton-Raphson 迭代

求 $P_{N1}(y) = 0$ 的根，迭代格式：

$$y^{(n+1)} = y^{(n)} - \frac{P_{N1}(y^{(n)})}{P'_{N1}(y^{(n)})}$$

代码：

```matlab
y = y0 - L(:,N2) ./ Lp;
```

收敛条件：所有节点的变化量均小于机器精度 $\varepsilon$：

```matlab
while max(abs(y - y0)) > eps
```

**收敛速度**：Newton-Raphson 对光滑函数二阶收敛，通常 3-5 次迭代即可达到机器精度。

---

## 8. 区间映射

将 $[-1,1]$ 上的 GL 节点线性映射到 $[a, b]$：

$$x_i = \frac{a(1-y_i) + b(1+y_i)}{2}$$

```matlab
x = (a*(1-y) + b*(1+y)) / 2;
```

---

## 9. 权重公式推导

### 9.1 标准公式

$N$ 点 GL 积分（节点为 $P_N$ 的根 $\{y_i\}$）的权重：

$$w_i = \frac{2}{(1-y_i^2)\,[P'_N(y_i)]^2}$$

映射到 $[a,b]$ 后，雅可比因子 $(b-a)/2$ 进入权重：

$$w_i = \frac{b-a}{(1-y_i^2)\,[P'_{N1}(y_i)]^2}$$

### 9.2 代码中的缩放补偿

代码中 `Lp` 是真实导数的 $N2/N1$ 倍，代入权重公式需补偿：

$$w_i = \frac{b-a}{(1-y_i^2)\cdot \underbrace{\left(\frac{N1}{N2} \cdot Lp_i\right)^2}_{[P'_{N1}]^2}} = \frac{b-a}{(1-y_i^2)\cdot Lp_i^2} \cdot \left(\frac{N2}{N1}\right)^2$$

```matlab
w = (b-a) ./ ((1-y.^2).*Lp.^2) * (N2/N1)^2;
```

---

## 10. 完整算法流程

```
输入：N（积分点数），[a, b]（积分区间）
  │
  ├─ 1. 初始猜测：Chebyshev 节点 + Lether 扰动
  │
  ├─ 2. Newton-Raphson 迭代（直到机器精度收敛）
  │       ├─ Bonnet 递推建立 L，得 P_{N1}(y)
  │       ├─ 导数公式计算 Lp ≈ (N2/N1)·P'_{N1}(y)
  │       └─ y ← y − P_{N1}(y)/Lp
  │
  ├─ 3. 线性映射：y ∈ [-1,1] → x ∈ [a,b]
  │
  └─ 4. 权重：w_i = (b-a)/((1-y_i²)·Lp_i²) × (N2/N1)²

输出：节点 x（N×1），权重 w（N×1）
使用：∫_a^b f(x)dx ≈ sum(f(x) .* w)
```

---

## 11. 与 SplineLengthApproxGL_tot 的关联

`lgwt` 在 `initFeedoptPlan` 阶段预计算一次，结果存入 `cfg`：

```matlab
cfg.GaussLegendreX = x;   % GL 节点（在 [-1,1] 或 [a,b]）
cfg.GaussLegendreW = w;   % GL 权重
cfg.GaussLegendreN = N;   % 节点数
```

`SplineLengthApproxGL_tot` 读取这些值，用 `bsxfun` 批量映射到各样条节点区间，计算 B 样条弧长。参见 [SplineLengthApproxGL_notes.md](SplineLengthApproxGL_notes.md)。
