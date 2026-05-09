# OpenCN MATLAB 源码阅读笔记

> 项目路径：`agency/usr/matlab/opencn-matlab/common/`
> 最后更新：2026-04-24

---

## 一、项目定位

OpenCN 是一个 **CNC 数控机床进给率优化库**。

- 输入：G-code 加工程序（`.ngc` 文件）
- 输出：满足速度 / 加速度 / 跃度约束的**时间最优轨迹**（位置、速度、加速度、跃度时序数据）
- 支持多轴（X/Y/Z + 旋转轴 B/C），目标机型为 `xyzbc_tt`（桌台式五轴）
- 核心算法：几何预处理 + **线性规划（LP）** 求解最优进给率
- 可通过 MATLAB Coder 生成 C/C++ 代码部署到实时系统

---

## 二、目录结构

```text
opencn-matlab/
├── common/                    主源码目录
│   ├── basic_example.m        完整流程示例（入口）
│   ├── startup.m              MATLAB 路径初始化
│   ├── opencn.slx             Simulink 主模型
│   ├── libopencn.slx          Simulink 库模型
│   │
│   ├── Feedopt/               核心算法（~116 个 .m 文件）
│   │   ├── bspline/           B 样条基础函数
│   │   ├── angles/            旋转轴角度处理
│   │   ├── queue/             队列数据结构
│   │   └── *.m                各阶段算法实现
│   │
│   ├── kinematics/            机器运动学
│   ├── types/                 数据结构定义（~30 个文件）
│   ├── utils/                 调试工具、绘图
│   │   └── plot/
│   ├── Tests/                 测试套件
│   │   ├── Full/              集成测试
│   │   └── Unit/              单元测试
│   ├── Validate_OpenCN/       验证套件
│   ├── mex/                   C/C++ MEX 源码
│   ├── ngc_test/              G-code 测试文件
│   │   └── E2C/               主要测试加工程序
│   └── generate/              代码生成脚本
│
├── arm64/                     生成的 ARM64 C/C++ 代码
└── x86/                       生成的 x86 C/C++ 代码
```

---

## 三、完整处理流水线

### 3.1 顶层调用链

```text
basic_example.m
  │
  ├── FeedoptDefaultConfig()       加载默认配置
  ├── ConfigSetSource(cfg, file)   设置 G-code 文件路径
  ├── initFeedoptPlan(cfg)         初始化上下文 ctx
  │
  ├── FeedoptPlanRun(ctx)          ← 主循环，驱动 FSM
  │     └── FeedoptPlan(ctx)       ← FSM 单步执行
  │
  ├── resample2file(ctx, fileName) 重采样输出 CSV（dt=1ms）
  ├── get_res_struct(...)          解析 CSV 列索引为命名结构体
  ├── analyse_optimality(...)      分析约束满足性和时间最优性
  ├── plotTrajectories(...)        绘制速度/加速度/跃度轨迹
  └── plotAxisCommands(...)        绘制各轴位置/速度/加速度/跃度
```

### 3.2 FSM 状态机（核心）

状态定义见 `Feedopt/Fopt.m`，调度逻辑见 `Feedopt/FeedoptPlan.m`：

```text
Init(0)
  → GCode(1)      解析 G-code → q_gcode
  → Check(2)      尖点检测、几何验证
  → Compress(3)   合并共线线段 → q_compress
  → Smooth(4)     添加平滑过渡 → q_smooth
  → Split(5)      分窗口处理 → q_split
  → Opt(6)        LP 优化进给率 → q_opt
  → Finished(67)
```

每个状态结束后都执行 `assert_queue`，验证：

- 几何有效性（`checkGeometry`）
- 零速模式合法性（`checkZSpdmode`）
- 参数化合法性（`checkParametrisationQueue`）

---

## 四、核心上下文结构 `ctx`

由 `initFeedoptPlan.m` 创建，贯穿整条流水线：

| 字段 | 类型 | 说明 |
| --- | --- | --- |
| `cfg` | struct | 所有配置参数 |
| `op` | Fopt | 当前 FSM 状态 |
| `q_gcode` | queue | G-code 解析结果队列 |
| `q_compress` | queue | 压缩后曲线队列 |
| `q_smooth` | queue | 平滑后曲线队列 |
| `q_split` | queue | 分窗后曲线队列 |
| `q_opt` | queue | 优化结果队列 |
| `q_spline` | queue | B 样条队列（压缩阶段产生） |
| `Bl` | struct | B 样条基（`bspline_create` 创建） |
| `BasisVal/D/DD/DDD` | matrix | 预计算样条基函数值及各阶导数 |
| `BasisIntegr` | matrix | 预计算样条基积分（目标函数用） |
| `u_vec` | vector | 离散化参数向量 [0,1] |
| `kin` | Kinematics | 运动学对象（封装正/逆运动学） |
| `v_0`, `v_1` | double | 当前窗口起/末端速度边界 |
| `at_0`, `at_1` | double | 当前窗口起/末端切向加速度边界 |
| `k0` | int32 | 当前处理的 q_split 游标 |
| `go_next` | bool | 下次调用前是否前进游标 |
| `zero_start/end` | bool | 当前段是否为零速起/止 |
| `Coeff` | matrix | LP 优化系数（[N×Nwindow]） |
| `errcode` | FeedoptPlanError | 错误码 |
| `errmsg` | struct | 错误信息 |

---

## 五、配置参数 `cfg`（`FeedoptDefaultConfig.m`）

### 机器约束

| 参数 | 默认值 | 说明 |
| --- | --- | --- |
| `maskTot` | `[1,1,1,0,1,1]` | 使用的轴：X/Y/Z/A(关)/B/C |
| `vmax` | `[500,500,500,0,40,50]` | 各轴最大速度 mm/s 或 rad/s |
| `amax` | `[15000,15000,15000,0,200,1000]` | 各轴最大加速度 mm/s² |
| `jmax` | `[1.5e6,1.5e6,1.5e6,0,1e4,5e4]` | 各轴最大跃度 mm/s³ |
| `dt` | `1e-3` | 离散时间步长（1ms） |
| `kin_type` | `'xyzbc_tt'` | 运动学类型 |

### 几何预处理

| 参数 | 默认值 | 说明 |
| --- | --- | --- |
| `CutOff` | `0.1` | 过渡算法切割长度阈值（mm） |
| `LSplit` | `3` | 曲线分割长度（mm） |
| `LThresholdMax` | `3` | 压缩算法最大长度（mm） |
| `LThresholdMin` | `0.5` | 压缩算法最小长度（mm） |
| `Cusp.CuspThreshold` | `10` | 尖点判定角度（度） |
| `Compressing.ColTolCosLee` | `cos(30°)` | 压缩共线容差 |
| `Smoothing.ColTolCosSmooth` | `cos(10°)` | 平滑共线容差 |

### LP 优化器

| 参数 | 默认值 | 说明 |
| --- | --- | --- |
| `NHorz` | `5` | 优化窗口曲线数（预瞻段数） |
| `NBreak` | `10` | B 样条断点数 |
| `NDiscr` | `20` | 每段离散点数 |
| `SplineDegree` | `3` | 优化用 B 样条阶次 |
| `USE_JERK_CONSTRAINTS` | `true` | 启用跃度约束（两阶段 LP） |
| `SLACK_PENALTY` | `10000` | 松弛变量惩罚系数 |

---

## 六、关键模块详解

### 6.1 G-code 解析（`Fopt.GCode` 阶段）

**`ReadGCode.m`** — 包装层，两种调用方式：

- MATLAB 模式：通过 `ReadGCode_mex` 调用 C++ G-code 解释器（LinuxCNC rs274ngc）
- 代码生成模式：直接将 `cpp_interp.cpp` 等 C++ 源码编译进目标代码

两步调用流程：

1. `cmd = Load`：打开文件，初始化解释器（读取 `config.ini` 机床参数）
2. `cmd = Read`：每次返回一条曲线段（循环直到 `InterpExit`）

G-code 读取后处理（在 `FeedoptPlan.m` 的 GCode 状态中）：

- 换刀检测 → 插入零速标记
- 刀具偏移补偿（`add_tool_offset`）
- 旋转轴单位转换（度 → 弧度）
- NaN 值替换为 0

**曲线类型（`CurveType.m`）：**

| 类型 | G-code | 说明 |
| --- | --- | --- |
| `Line` | G0/G1 | 直线段 |
| `Helix` | G2/G3 | 圆弧/螺旋线 |
| `TransP5` | — | 5 次多项式过渡曲线（平滑阶段插入） |
| `Spline` | — | B 样条曲线（压缩阶段生成） |

### 6.2 几何预处理（详解）

几何预处理分四个子阶段，依次完成：**压缩 → 平滑 → 分割**，以及贯穿其中的**曲线截取**工具。

---

#### 6.2.1 压缩（Compress）— `compressCurvStructs.m` + `CalcBspline_Lee.m`

**目的：** 把大量连续短直线段（CAM 轨迹离散化产物）合并成一条光滑 B 样条曲线，减少后续处理段数，提升曲线连续性。

**整体流程：**

```text
for 每条曲线 curv in q_gcode:
    check_add_batch(curv)   → 判断是否可进入批次（2 个 AND 条件）
    check_close_batch(...)  → 判断是否需要关闭当前批次（5 个 OR 条件）
    若 closeBatch → batch_close()  → 拟合 B 样条或透传
    若 addBatch   → batch_add_curv()  → 追加到批次
    否则          → 直接 push 到 q_compress（圆弧等不可压缩类型）
loop 结束后关闭最后一个批次
```

**可加入批次的条件（两个必须同时满足）：**

| 条件 | 代码 | 含义 |
| --- | --- | --- |
| 类型是直线 | `curv.Info.Type == CurveType.Line` | 圆弧/螺旋线/样条不压缩 |
| 长度不超过阈值 | `L ≤ LThresholdMax`（3mm） | 过长的直线不值得压缩 |

**关闭批次的条件（五个，任一触发）：**

| 触发条件 | 含义 | 处理 |
| --- | --- | --- |
| 当前曲线不满足加入条件 | 类型/长度不符 | 先关闭，再直接透传当前曲线 |
| 当前曲线有零速起始 | 换刀/程序停止后的第一段 | 必须从独立段开始，不能合并 |
| 机床参数不同 | 进给率或主轴转速变了 | 合并后无法保留参数变化 |
| 当前曲线极短（< 0.5mm） | `LThresholdMin`，数值上不稳定 | 跳过共线判断，**保持**批次不关闭 |
| 与批次最后段不共线 | 切线夹角 > 30°（`cos(30°)≈0.866`） | 方向变化太大，不能合并 |

注意：条件 4（极短线段）只影响共线判断，并不独立触发关闭。这是一个特殊豁免：极短段数值不稳定，跳过共线检查直接加入批次。

**批次关闭时的处理：**

```text
if batch.size > 1:
    用 Lee 算法拟合 B 样条（CalcBspline_Lee）
    → q_compress 写入一条 Spline 曲线
    → q_spline 写入对应的 B 样条参数（Ltot/Lk 预计算好）
else:
    直接透传到 q_compress（单段不值得拟合）
```

**pvec 数据结构：**

```text
第一条曲线加入时：pvec = [R0, R1]         (起点 + 终点，各一列)
后续每条追加：    pvec = [pvec, R1_new]   (只追加终点，起点=前段终点)
最终：pvec 是一个 6×(N+1) 矩阵，代表 N 段直线的折线顶点序列
```

**Lee 算法数学原理（`CalcBspline_Lee.m`）：**

输入：折线顶点序列 $p_1, p_2, \ldots, p_{N+1}$（从 `pvec` 取出激活轴数据）

**第一步：弦长参数化（Lee 参数化，1/4 次方）** — 普通弦长参数化用相邻点距离，但 Lee 参数化使用 1/4 次方（实验表明对 CNC 轨迹有更好的曲率分布）：

```matlab
du = sum((diff(points.').^2).')   % 各段距离的平方和（= 距离²）
u  = cumsum([0, du.^(1/4)])       % 累积 1/4 次方距离
u  = u / u(end)                   % 归一化到 [0, 1]
```

**第二步：构造 Clamped B 样条基** — 以上面的 `u` 作为内部断点，两端各添加 `(degree-1)` 重复节点（Clamped B 样条，端点插值）：

```text
knots = [0,0,...,0, u_1, u_2, ..., u_N, 1,1,...,1]
        ←(deg-1)→                       ←(deg-1)→
```

B 样条阶次由 `cfg.LeeSplineDegree`（默认 4，即三次 B 样条）控制。

**第三步：建立线性方程组（自然边界条件）** — 目标：找到控制点 $c_1, \ldots, c_M$，使 B 样条在每个 $u_k$ 处通过对应的折线顶点 $p_k$，同时在两端点的二阶导数为 0（自然样条）。

```text
边界条件（2 行）：  B''(u_0)·c = 0   （起点二阶导 = 0）
                   B''(u_N)·c = 0   （终点二阶导 = 0）
插值条件（N 行）：  B(u_k)·c  = p_k  （通过每个折线顶点）

拼合后：A = [BasisValDD0; BasisVal; BasisValDD1]   (行重排使 A 变三对角)
        B = [zeros(1,nAxis); points.'; zeros(1,nAxis)]
```

由于 B 样条基的局部支撑性，矩阵 A 是**三对角矩阵**，用 Thomas 算法（`tridiag`）$O(N)$ 求解。

**第四步：预计算弧长** — B 样条拟合完后立即调用 `SplineLengthApproxGL_tot` 预计算：

- `Ltot`：整条曲线总弧长
- `Lk`：每个子区间 $[u_k, u_{k+1}]$ 的弧长（GL 积分）

这些数据在后续弧长截取和 LP 约束构造中反复使用。

---

#### 6.2.2 平滑（Smooth）— `smoothCurvStructs.m` + `calcTransition.m`

**目的：** G-code 中两段相邻曲线的连接处通常不光滑（切线不连续，更不用说曲率），直接优化会导致加速度跳变。平滑阶段在连接处插入 **G2 连续的 5 次多项式过渡曲线（TransP5）**。

**顶层逻辑（smoothCurvStructs）：**

对 q_compress 中每对相邻曲线 `(curv, nextCurv)` 调用 `check_stop_and_transition`，得出三种结论：

```text
情况 A — needStop = true：
    curv 有零速末端（isAZeroEnd）→ 直接推入 q_smooth，不插入过渡
    （零速停止本身就是边界，不需要平滑）

情况 B — needTransition = true：
    连接处不光滑（非 G2）→ 尝试 calcTransition()
        → 成功（Ok）：推入 curv1C、curvT、继续处理 curv2C
        → 失败（NoSolution）：退化为强制零速停止（create_zero_end）

情况 C — 两者都 false：
    连接处已经够光滑（G2 满足容差）→ 直接推入 curv，不插入过渡
```

**何时不需要过渡（`nextCurv.b_param > 0`）：**

`check_stop_and_transition` 的第二个提前返回条件（`smoothCurvStructs.m:95`）：

```matlab
if( nextCurv.b_param > 0 ), return; end   % needStop=false, needTransition=false
```

**`b_param` 的物理含义：** 它是曲线在父曲线参数空间中的起始偏移量。

- `b_param = 0`：从父曲线起点开始，是完整段或左半段；
- `b_param > 0`：从父曲线中间某处开始，是**右半段子段**。

`cutCurvStruct` 切割时（`cutCurvStruct.m:28-29`）：

```matlab
curvRight.b_param = u_tilda;              % 右半段：起点在切割点（> 0）
curvLeft.b_param  = 原值不变;             % 左半段：起点不变（通常为 0）
```

**为什么右半段不需要过渡检查？**

`nextCurv.b_param > 0` 说明它是某条原始曲线被切割后的右半段，其左边界（`u=0`）恰好就是那次切割的切割点。切割点两侧（左半段末端、右半段起端）来自**同一条原始曲线**，位置、切线方向、曲率三者完全相同：

```text
check_smoothness 检查三个条件：
    C0（位置）：切割点两侧位置相同 → 必然满足
    G1（切线）：来自同一曲线，方向相同 → 必然满足
    G2（曲率）：来自同一曲线，曲率相同 → 必然满足
```

因此，不是"已处理过跳过"，而是"切割点天然满足 G2，检查是多余的"。更重要的是：**若错误地对右半段起端插入 Hermite 过渡，反而会破坏原本完整曲线的连续性**。

**G2 连续性判定（`check_smoothness`）：**

在连接处求 curv1 末端和 curv2 起端的位置、切线方向、曲率，三者必须同时满足：

```text
C0（位置连续）：‖r1(1) - r2(0)‖ < tol（1e-5 mm）
G1（切线连续）：cos(angle(t1, t2)) > cos(10°) ≈ 0.985
G2（曲率连续）：|κ1 - κ2| < tol（1e-3）
```

**calcTransition 详细流程：**

```text
1. 安全检查：L1 < 3*CutOff 或 L2 < 3*CutOff → 放弃（曲线太短无法切割）

2. 截取曲线：
   curv1C = curv1 的前 (L1 - CutOff) 部分  （去掉末端 0.1mm）
   curv2C = curv2 的后 (L2 - CutOff) 部分  （去掉起端 0.1mm）

3. 在截取点处求边界值：
   (r0D0, r0D1, r0D2) = EvalCurvStruct(curv1C, u=1)  （位置、一阶导、二阶导）
   (r1D0, r1D1, r1D2) = EvalCurvStruct(curv2C, u=0)

4. G2 Hermite 插值 → 得到 p5（5×6 系数矩阵）
   status = Ok(1) / 矩阵病态(2) / 无正实数解(3/4/5) / 数值警告(6) / 系数退化(7) / G2验证失败(8)

5. 最终验证：check_continuity(curv1C, curvT) && check_continuity(curvT, curv2C)
```

**G2 Hermite 插值数学原理（`G2_Hermite_Interpolation_nAxis.m`）：**

已知：两端的位置 $r_0, r_1$，切线 $r_0', r_1'$，二阶导 $r_0'', r_1''$（共 6 个向量边界条件）。

**核心思路：Frenet 分解降维** — 把切线和法线分离，将 N 维问题降到 2 个标量未知数：

```text
r'(0) = α₀·t₀   （切线方向分量，α₀ > 0 标量）
r'(1) = α₁·t₁   （终端同理）

r''(0) = β₀·t₀ + α₀²·κ₀·n₀   （法向曲率项固定，β₀ 是另一标量）
r''(1) = β₁·t₁ + α₁²·κ₁·n₁
```

其中 $t_0, n_0, \kappa_0$ 是由输入边界值计算的切线、法向和曲率。$\beta_0, \beta_1$ 由 $\alpha_0, \alpha_1$ 唯一确定（`Calc_beta0_beta1`）。

因此只剩 2 个未知数 $(\alpha_0, \alpha_1)$。

**多项式方程组求解（2 个耦合方程）** — 由 G2 条件推出：

- 方程 $p_1(\alpha_0, \alpha_1) = 0$（最高次 $\alpha_0^2\cdot\alpha_1^3$）
- 方程 $p_2(\alpha_0, \alpha_1) = 0$（最高次 $\alpha_0^3\cdot\alpha_1^2$）

消去 $\alpha_0$（结式法），得到一个关于 $\alpha_1$ 的 9 次多项式（一般情况），用 `c_roots_` 求所有根，筛选正实数根。若有多个正实数解，选最小化 $\int\|r'''\|^2\,dt$（跃度积分，`EvalCostIntegral`）的那组。

特殊情况（一端或两端曲率为 0，即直线端）：方程组退化为低阶，分支处理（线性 / 3 次）。

**构造 5 次多项式（Hermite 基）** — Hermite 基函数（参数 $t \in [0,1]$）：

```text
h00 = -6t⁵ + 15t⁴ - 10t³ + 1     （左端位置插值基）
h10 = -3t⁵ +  8t⁴ -  6t³ + t     （左端一阶导基）
h20 = -0.5t⁵ + 1.5t⁴ - 1.5t³ + 0.5t²  （左端二阶导基）
h01 =  6t⁵ - 15t⁴ + 10t³          （右端位置插值基）
h11 = -3t⁵ +  7t⁴ -  4t³          （右端一阶导基）
h21 =  0.5t⁵ - t⁴ + 0.5t³         （右端二阶导基）
```

最终：

```text
p5(t) = r₀·h00 + α₀·t₀·h10 + (β₀·t₀ + α₀²·n₀)·h20
       + r₁·h01 + α₁·t₁·h11 + (β₁·t₁ + α₁²·n₁)·h21
```

p5 是 N_AXES × 6 的系数矩阵，对每个轴独立存储多项式系数。

*最后验证：* 检查 $|p_1(\alpha_0,\alpha_1)| < 10^{-7}$ 且 $|p_2(\alpha_0,\alpha_1)| < 10^{-7}$，不满足则 `status=6`（数值警告，代码仍接受此情况继续）。

---

#### 6.2.3 分割（Split）— `splitCurvStruct.m`

**目的：** 把长曲线切成长度 ≤ `LSplit`（3mm）的短段，让滑动窗口优化器（NHorz=5 段/窗口）能在合理精度下求解。零速段的短桩（stub）在此阶段单独截取出来。

**处理逻辑（每条曲线）：**

```text
情况 1：TransP5 过渡曲线
    → 直接推入 q_split（过渡曲线本来就很短，不需分割）

情况 2：有零速起始（isAZeroStart）
    → cutZeroStart：在起端切出一个 LSplitZero（1mm）的小桩，单独推入
    → 剩余部分继续处理

情况 3：有零速末端（isAZeroEnd）
    → cutZeroEnd：在末端切出一个 LSplitZero（1mm）的小桩，暂存到 curvE

情况 4：Spline 且 SplitSpecialSpline=true
    → 按 B 样条的内部断点（breakpoints）分段
    → 这样每一子段恰好对应样条的一个多项式段，计算效率高

情况 5（通用）：
    N = ceil(L / LSplit)        % 计算需要分成几段（向上取整）
    L_split = L / N             % 每段等长（比 LSplit 略短或相等）
    for k = 1 to N-1:
        cutCurvStruct → 取前 L_split，剩余继续
    最后一段直接推入

情况 3 的末尾：将 curvE（零速末端桩）推入 q_split
```

**为什么 Spline 要按断点分割（SplitSpecialSpline）？**

B 样条在断点处的多项式段切换，恰好是曲线上有意义的几何节点。按断点分割后，每个子段的曲率变化更均匀，LP 离散化误差更小。若不按断点分割，可能出现一个子段横跨多个曲率变化剧烈的区域，导致约束点密度不足。

---

#### 6.2.4 弧长截取（Arc-Length Cutting）— `cutCurvStruct.m` / `cutCurvStructU.m`

截取是平滑和分割两个阶段共用的基础工具。**比喻**：把一段绳子在距某端 L 处剪断，得到左段和右段。截取不修改曲线的几何数据（B 样条系数不变），只更新参数映射，告诉后续代码"可以使用这段曲线的哪个区间"。

**函数层次：**

```text
cutCurvStruct(ctx, curv, u0, L, isEnd)
  ├── 第一步：cutCurvStructU → 求截点全局参数 u_tilda（按曲线类型分支）
  │     ├── Spline：splineLengthFindU（弧长反求，二分法）
  │     └── Line/Helix：解析公式（均匀参数化，Δu = L / ‖r'‖）
  ├── 第二步：更新 curvRight 的 a_param/b_param
  ├── 第三步：更新 curvLeft  的 a_param/b_param
  └── 第四步：修正两段各自的 ZSpdMode（零速模式）
```

**参数映射机制（核心）：**

**先理解问题**：所有求值代码（`EvalCurvStruct`）传入的参数永远是 $u_{local} \in [0,1]$，"0 代表起点，1 代表终点"。但 B 样条数据只有一份，存在全局参数空间里。截取后的子段并不重新拟合，只记录"自己对应原曲线哪个区间"。这个"区间记录"就是 `a_param` 和 `b_param`。

**映射公式**（`EvalCurvStructNoCtx.m:35`）：

$$u_{global} = a\_param \times u_{local} + b\_param$$

| 字段 | 物理含义 |
| --- | --- |
| `b_param` | 这段曲线在全局参数空间的**起点**（窗口左边界） |
| `a_param` | 这段曲线在全局参数空间的**跨度**（窗口宽度） |

**具体数字例子**：原曲线 `a=1, b=0`，在 $u_{tilda}=0.93$ 处截取（从末端切掉 7%）：

```text
左段（保留大部分，全局范围 [0, 0.93]）：
    b_param = 0      → u_local=0 时查 u_global=0   （起点正确）
    a_param = 0.93   → u_local=1 时查 u_global=0.93（终点正确，不是原来的1）
    中点验证：u_local=0.5 → u_global = 0.93×0.5 + 0 = 0.465 ✓

右段（切掉的末端，全局范围 [0.93, 1]）：
    b_param = 0.93   → u_local=0 时查 u_global=0.93（起点正确）
    a_param = 0.07   → u_local=1 时查 u_global=1.00（终点正确）
    中点验证：u_local=0.5 → u_global = 0.07×0.5 + 0.93 = 0.965 ✓
```

**截取后如何更新**（原区间 $[b,\, b+a]$，截点 $u\_tilda$）：

```text
左段（保留 [b, u_tilda]）：
    curvLeft.b_param = b              （窗口起点不变）
    curvLeft.a_param = u_tilda - b    （窗口宽度收缩到截点）

右段（保留 [u_tilda, b+a]）：
    curvRight.b_param = u_tilda       （窗口起点移到截点，必然 > 0）
    curvRight.a_param = (b+a) - u_tilda  （窗口宽度 = 原终点 - 截点）
```

截取后 B 样条数据本身不动，只有"窗口"变了。

**导数的连带缩放**（`EvalCurvStructNoCtx.m:64-66`）：

由于 $u_g = a \cdot u_l + b$，对 $u_l$ 求导需要乘以 $a$（链式法则）：

```matlab
r1D = a    .* r1D;   % 一阶导 × a
r2D = a^2  .* r2D;   % 二阶导 × a²
r3D = a^3  .* r3D;   % 三阶导 × a³
```

子段的 `a_param < 1`，所以截取后的子段速度、加速度会自动按正确比例缩放，无需额外处理。

**参数化合法性约束（`checkParametrisation.m`）：**

```matlab
a_param > 0  &&  a_param <= 1    % 区间长度合法
b_param >= 0 &&  b_param < 1     % 起始偏移合法
a_param + b_param <= 1 + eps     % 不超过全局区间 [0,1]
```

这三条约束保证了子段始终在 $[0,1]$ 内，不会越界。

**各类型截取方法：**

| 类型 | 参数化特性 | `cutCurvStructU` 的做法 |
| --- | --- | --- |
| Line | 均匀（`‖r'‖ = const`） | `u1 = u0 ± L / ‖r'‖`，再转换 `u_tilda = a*u1 + b` |
| Helix | 均匀（`‖r'‖ = const`） | 同 Line |
| Spline | 非均匀 | 两阶段弧长反演（cumsum 粗查 + 二分法精确） |
| TransP5 | 非均匀 | 同 Spline |

**Spline 弧长反演（`splineLengthFindU.m`）：**

**问题**：给定起点 $u_0$、目标弧长 $L$，求 $u$ 使 $s(u_0, u) = L$。弧长积分 $\int_{u_0}^{u}\|r'(t)\|dt$ 无解析逆，必须数值求解。

**阶段 0：按节点区间预计算弧长表（`SplineLengthApproxGL_tot`，初始化时一次性完成）**

B 样条节点向量把参数域分成 $K$ 个区间（去掉端点重节点后）。对每个区间 $[t_k, t_{k+1}]$ 用 GL-5 积分预算弧长，结果存入 `sp.Lk`：

$$Lk[k] = \int_{t_k}^{t_{k+1}} \|r'(u)\| \, du \quad \text{（GL-5，一次性算好）}$$

**阶段 1：粗查表定位目标区间（O(K)）** — 步骤如下：

```text
① 找 u0 所在节点区间：kStart = 最后一个满足 Knots[k] ≤ u0 的 k

② 计算 LStart：u0 不一定恰好在节点上，可能在区间中间
       若 Knots[kStart] < u0：LStart = GL积分(Knots[kStart], u0)
       否则：LStart = 0   （u0 恰好在节点上，不需要扣）

③ 从 kStart 起累积弧长，扣掉已走的 LStart：
       LEnd = cumsum(Lk[kStart:end]) - LStart

④ 找第一个 LEnd[i] ≥ L 的位置 → 目标落在第 k* 个节点区间
       [uLeft, uRight] = [Knots[kEnd-1], Knots[kEnd]]
       LDiff = 在这个区间内还需走的弧长
```

具体数字例子（Lk = [2, 3, 1.5, 2.5]，u0 在第 1 个节点上，L = 6mm）：

```text
LEnd = cumsum([2, 3, 1.5, 2.5]) - 0 = [2, 5, 6.5, 9]
                                              ↑ 第一个 ≥ 6
目标在第 3 个区间 [t_2, t_3]
LDiff = 6 - 5 = 1mm  （在这段区间内还需走 1mm）
```

**阶段 2：区间内二分精确定位（O(log(1/tol))）** — 在定位到的区间内搜索：

```text
在 [uLeft, uRight] 内二分：
    uMiddle = (uLeft + uRight) / 2
    fk = splineLengthApprox_Interval(uLeft, uMiddle) - LDiff

    fk > 0：积分超了，目标在左边 → uRight = uMiddle
    fk < 0：积分不足，目标在右边 → uLeft  = uMiddle

收敛条件：|fk| < 1e-7（即弧长误差 < 0.1μm），最多 1000 次
```

每次迭代区间减半，约 23 次即可收敛到 1e-7 精度（$\log_2(10^7) \approx 23$）。

**`isEnd` 镜像翻转：**

`isEnd = true` 表示从末端往回截，即找 $u$ 使 $s(u, 1) = L$。把整个参数空间关于 0.5 镜像，把"从末端量"变成"从起端量"：

```matlab
u0    = 1 - u0          % 起点镜像
Knots = flip(1 - Knots) % 节点向量镜像并反转
Lk    = flip(Lk)        % 区间弧长反转顺序
% ... 正常跑算法 ...
u = 1 - u               % 结果翻回原坐标
```

**GL 积分细节（`splineLengthApprox_Interval`）：**

```matlab
uvec = (u0*(1-GL_X) + u1*(1+GL_X)) / 2   % [-1,1] 线性映射到 [u0,u1]
[~, r1D] = EvalBSpline(spline, uvec)       % 各节点处的参数导数
L = r1Dnorm * GL_W * (u1-u0) / 2          % 加权求和 = GL 积分
```

GL-5 对 ≤ 9 次多项式精确，3 阶 B 样条的 $\|r'(u)\|$ 在每段区间内充分光滑，5 个节点已足够。

**截取后零速模式（ZSpdMode）更新：**

`ZSpdMode` 枚举编码曲线两端的零速状态（Z=零速，N=正常速度）：

| 枚举值 | 起端 | 末端 | 含义 |
| --- | --- | --- | --- |
| `NN (0)` | 正常 | 正常 | 两端都不停 |
| `ZN (1)` | 零速 | 正常 | 从静止启动 |
| `NZ (2)` | 正常 | 零速 | 减速到停止 |
| `ZZ (3)` | 零速 | 零速 | 两端都停 |

截取后，截点（内部点）的速度由优化器决定，不是零速边界。因此：

```text
curvLeft（保留起端）：
    起端 = 原曲线起端（若原为 ZN/ZZ → 保留 ZN；否则 NN）
    末端 = 截点（内部点，不是零速边界 → N）

curvRight（保留末端）：
    起端 = 截点（内部点 → N）
    末端 = 原曲线末端（若原为 NZ/ZZ → 保留 NZ；否则 NN）
```

**截点天然 G2 连续的推论（`smoothCurvStructs.m:95`）：**

`curvRight.b_param > 0` 意味着这是截取的右半段，其起端（局部 `u=0`）处的位置、切线、曲率与 `curvLeft` 末端完全相同（来自同一条原始曲线），天然满足 G2。因此 `smoothCurvStructs` 在见到 `nextCurv.b_param > 0` 时直接跳过过渡检查，无需插入 Hermite 过渡曲线。

**各类型弧长计算（`LengthCurv.m`）：**

弧长的通用公式是 $L = \int_{u_0}^{u_1} \|r'(u)\| \, du$。四种曲线类型的 $\|r'(u)\|$ 性质各异，采用不同策略。

**① Line（直线，G01）— 解析，O(1)** — 参数化：$r(u) = P_0(1-u) + P_1 u$，对 $u$ 求导：

$$r'(u) = P_1 - P_0 \quad \text{（常向量，与 } u \text{ 无关）}$$

$\|r'(u)\|$ 是常数，积分退化为乘法：

$$L = \|P_1 - P_0\| \times (u_1 - u_0)$$

代码只需在任意点（取 $u_0$）求一次导，再乘以区间长度：

```matlab
[~, r1D] = EvalCurvStruct(ctx, curv, u0);  % r1D = a_param*(P1-P0)（含链式法则缩放）
L = MyNorm(r1D) * (u1 - u0);               % u1-u0 为局部参数区间宽度
```

**② Helix（圆弧/螺旋线，G02/G03）— 解析，O(1)** — 螺旋线参数化（$\varphi = \theta u$，$\theta$ = 总圆心角，$p$ = 螺距）：

$$r(\varphi) = C + R\cos\varphi \cdot \hat{x} + R\sin\varphi \cdot \hat{y} + \frac{p}{2\pi}\varphi \cdot \hat{e}$$

对局部参数 $u$ 求导（用 `EvalHelix` 计算）：

$$r'(u) = \underbrace{\theta(-\sin\varphi \cdot \vec{CP_0} + \cos\varphi \cdot (\hat{e}\times\vec{CP_0}))}_{\text{旋转分量（圆周方向）}} + \underbrace{\frac{\theta p}{2\pi}\hat{e}}_{\text{轴向分量（螺旋前进）}}$$

进一步求二阶、三阶导数：

$$r''(u) = \theta^2\big(-\cos\varphi \cdot \vec{CP_0} - \sin\varphi \cdot (\hat{e}\times\vec{CP_0})\big)$$

$$r'''(u) = \theta^3\big(\sin\varphi \cdot \vec{CP_0} - \cos\varphi \cdot (\hat{e}\times\vec{CP_0})\big)$$

这里的关键点是：
- 轴向分量 $\frac{\theta p}{2\pi}\hat{e}$ 是对 $u$ 的一次线性项，其二阶、三阶导数为 0；
- 因此二阶、三阶导数仅来自圆周旋转部分；
- 这也说明 Helix 在笛卡尔轴上的曲率与纯圆弧一致，旋转部分导数的模长为常数。

两个分量**相互垂直**（$\hat{e} \perp$ 旋转平面），因此模长：

$$\|r'(u)\|^2 = \theta^2 R^2 \underbrace{(\sin^2\varphi + \cos^2\varphi)}_{=1} + \left(\frac{\theta p}{2\pi}\right)^2 = \theta^2 R^2 + \left(\frac{\theta p}{2\pi}\right)^2 = \text{const}$$

$\|r'(u)\|$ 也是常数（与 $u$ 无关），弧长公式与 Line 完全相同：

```matlab
[~, r1D] = EvalCurvStruct(ctx, curv, u0);  % 任意点求导，模长不变
L = MyNorm(r1D) * (u1 - u0);
```

纯圆弧（$p=0$）退化为 $L = \theta R \cdot (u_1-u_0)$（弧长 = 半径 × 弧度角 × 参数比例）。

**③ Spline（B 样条）— 数值，预计算 + 查表，O(K)** — B 样条的 $\|r'(u)\|$ 逐点变化，无解析积分，用 `splineLength` 调用预建的 Lk 表：

```matlab
u0_tilda = a * u0 + b;   % 局部参数 → 全局参数
u1_tilda = a * u1 + b;
L = splineLength(cfg, spline, u0_tilda, u1_tilda);
```

`splineLength` 的计算逻辑（"两端 GL，中间查表"）：

```text
定位 u0_tilda 所在区间 kStart，u1_tilda 所在区间 kEnd

若 u0_tilda 不在节点上：
    LStart = GL积分(Knots[kStart], u0_tilda)   （左端不完整区间）
否则 LStart = 0

若 u1_tilda 不在节点上：
    LEnd = GL积分(u1_tilda, Knots[kEnd])       （右端不完整区间）
否则 LEnd = 0

L = sum(Lk[kStart : kEnd-1]) - LStart - LEnd
    ↑ 中间所有完整区间直接查表（O(1) 每个）
```

**④ TransP5（5 次多项式过渡曲线）— 中点法近似，O(1)** — 5 次多项式导数有解析式，但 $\|\text{多项式}\|$ 的积分无闭合形式。过渡曲线极短（约 0.2mm），用**中点积分法**粗略近似即可：

```matlab
u_vec = linspace(u0, u1, 10);                     % 10 个均匀点
u_mid = 0.5*(u_vec(1:end-1) + u_vec(2:end));      % 9 个子区间中点
Integrand = ‖p5'(u_mid)‖                          % 各中点处的速度（多项式求导 mypolyder）
L = sum(Integrand .* diff(u_vec))                  % 中点法：Σ f(u_mid)*Δu
```

中点法的精度为 $O(h^2)$（$h = \Delta u$），9 个子区间对 ~0.2mm 的短曲线足够。

| 类型 | $\|r'(u)\|$ 性质 | 方法 | 复杂度 |
| --- | --- | --- | --- |
| Line | 常数 | 解析（一次导数 × 区间宽） | O(1) |
| Helix | 常数（旋转+轴向正交） | 解析（同 Line） | O(1) |
| Spline | 逐点变化 | 查 Lk 表 + 边界 GL 积分 | O(K) |
| TransP5 | 逐点变化 | 中点法（9 段） | O(1) |

### 6.3 进给率优化（核心，详解）

#### 6.3.1 数学建模：LP 问题的构造

**核心思路：把进给率优化转化为线性规划（LP）** — 曲线已被参数化为 $u \in [0,1]$，轨迹速度 $v(t) = \|r'(u)\| \cdot \dot{u}$。令 $w(u) = v^2(u) = \|r'(u)\|^2 \cdot \dot{u}^2$（速度的平方），用 B 样条近似：

$$w(u) \approx \sum_{j=1}^{N} c_j B_j(u) = B(u) \cdot x_k$$

其中 $x_k = [c_1, \ldots, c_N]^T$ 是第 $k$ 段的决策变量（B 样条系数），$B(u)$ 是行向量形式的基函数。$w(u) \geq 0$ 天然对应物理约束（速度实数）。

**决策变量**（窗口内 K 段，每段 N 个 B 样条系数，加 1 个松弛变量，共 N×K+1 维）：

```text
x = [x_1; x_2; ...; x_K; s]          维度：N×K + 1
    x_k ∈ R^N : 第 k 段的 B 样条系数（描述 v²(u)）
    s ≥ 0     : 松弛变量（允许约束轻微违反，防止无解）
K = NWindow（窗口内曲线段数），N = NBreak + SplineDegree - 2
```

**目标函数：最小化加工时间（近似为最大化速度积分）** — 优化形式为：

$$\min -\int_0^1 w(u)\,du \approx \min -\sum_j c_j \int_0^1 B_j(u)\,du = \min -\mathrm{BasisIntegr}^T \cdot x_k$$

`BasisIntegr` 在 `initFeedoptPlan` 中预计算一次，多窗口复用。加上松弛惩罚项后：

```text
f = [-BasisIntegr ⊗ I_K; SLACK_PENALTY]     (SLACK_PENALTY = 10000)
```

#### 6.3.2 约束矩阵构造（`buildConstr.m`）

**不等式约束 $A \cdot x \leq b$（每段每个离散点 M 行，4 组）：**

**组 1：速度上限**（来自各轴速度约束和 G-code 编程进给率）

$$w(u) \leq f_{\max}(u) \quad \Rightarrow \quad B(u) \cdot x_k \leq f_{\max}(u)$$

速度上限推导：对第 j 轴，$v_j = r'_j(u) \cdot \dot{u}$，要求 $|v_j| \leq v_{j,\max}$，则：

$$w \leq \left(\frac{v_{j,\max}}{r'_j(u)}\right)^2 \quad \text{取所有轴的最小值}$$

同时还有编程进给率约束（G-code F 指令）：

$$w \leq \left(\frac{F_{\text{prog}}}{\|r'_{\text{cart}}(u)\|}\right)^2$$

代码中 `v_max = min(v_max, [], 1)` 取逐点最小值作为最终上限 `f_max`。

**组 2：速度非负**

$$-B(u) \cdot x_k \leq 0$$

**组 3 & 4：加速度约束**（各轴上限和下限）

对参数 $u$ 求导，速度和加速度的链式法则展开：

$$A_j = r''_j \cdot w + \frac{1}{2} r'_j \cdot w'$$

其中 $w' = B'(u) \cdot x_k$，代入 B 样条：

$$A_j(u) \approx \underbrace{\left(r''_j \cdot B + 0.5 \cdot r'_j \cdot B'\right)}_{\text{Acc}_{j}} \cdot x_k$$

约束：$|A_j| \leq a_{j,\max}$，拆为：

```text
 Acc · x ≤ a_max    （上限）
-Acc · x ≤ a_max    （下限，等价于 A ≥ -a_max）
```

**等式约束 $A_{eq} \cdot x = b_{eq}$（段间连续性 + 窗口边界）：**

每段在 $u=0$（起）和 $u=1$（末）需满足与相邻段相同的 $w$ 和切向加速度 $a_t$。

切向加速度 $a_t = t^T \cdot A$（切线单位向量投影），通过 `t_vec × Acc[start/end, :]` 计算。

段间连续性（$k$ 段末 = $k+1$ 段起）用符号矩阵实现：

```matlab
mask_continuity = [1; 1; -1; -1]   % 前段末为正，后段起为负
% 叠加到 Aeq 中：前段末 +1，后段起 -1，等式右端为 0
Aeq(rows, cols) += continuity .* mask_continuity
```

窗口两端的边界固定值写入 `beq`：

```text
beq([1,2]) = [v_0²; at_0]        （窗口起端：速度² 和切向加速度）
beq([end-1,end]) = [-v_1²; -at_1]（窗口末端：注意符号由 mask 决定）
```

**约束斜坡（Ramp）— 防止末尾过度优化：**

若只优化当前窗口，LP 可能把所有速度集中在末尾（因为末尾的约束是松的）。为此，对窗口**最后一段**施加斜坡软化：

```text
vel_ramp = linspace(1, VEL_RAMP_OVER_WINDOWS, M)   % VEL_RAMP ≈ 0.999
acc_ramp = linspace(1, ACC_RAMP_OVER_WINDOWS, M)
b ← b .* ramp     （将末段的约束上限略微降低）
```

这使得末尾段的允许速度比理论最大值稍低，给下一窗口留下余量，保证滑动的平滑性。

#### 6.3.3 跃度约束线性化（`buildConstrJerk.m`）

跃度约束本身非线性（含 $v^3 = w^{3/2}$），无法直接放入 LP。第二阶段在第一阶段解 $x^{(1)}$ 的基础上做泰勒线性化：

**跃度时间域展开（链式法则）：**

$$J_j = r'''_j \cdot v^3 + 3r''_j \cdot v \cdot a_t + r'_j \cdot j_t$$

改写为 B 样条形式，$w = B \cdot x$，$w' = B' \cdot x$，$w'' = B'' \cdot x$，则：

$$J_j \approx \left(r'''_j \cdot B + 1.5 \cdot r''_j \cdot B' + 0.5 \cdot r'_j \cdot B''\right) \cdot x \cdot \underbrace{\sqrt{Bx}}_{\approx \sqrt{Bx^{(1)}}}$$

线性化关键：用第一阶段解 $x^{(1)}$ 代入 $\sqrt{B \cdot x}$，使其成为已知常数，整个跃度约束变为关于 $x$ 的线性形式：

```matlab
Jerk(j, :) = (r3D(j,:)'.*BasisVal + 1.5*r2D(j,:)'.*BasisValD + ...
              0.5*r1D(j,:)'.*BasisValDD) .* mysqrt(BasisVal * coeff(:,k))
% 约束：Jerk·x ≤ j_max 和 -Jerk·x ≤ j_max
```

跃度约束行添加到松弛变量（`indSlack`），允许轻微违反以保持可行性。

#### 6.3.4 松弛机制（`add_slack`）

每次 LP 添加一个全局松弛变量 $s \geq 0$：

```text
原约束：A·x ≤ b
改为：  A·x - s ≤ b    （允许违反量为 s）
目标：  min (...) + SLACK_PENALTY · s    （惩罚违反）
```

`SLACK_PENALTY = 10000`：足够大使得只有在无其他选择时才允许违反。第一阶段对**所有约束**使用同一个 $s$；第二阶段对**跃度约束行**专门引入松弛（加速度约束行不引入，保持严格）。

#### 6.3.5 滑动窗口策略（`feedratePlanning.m`）

```text
外层（FeedoptPlan 的 Opt 状态，多次重入）：
  k0 = 1, 2, ..., q_split.size     （每次进入 feedratePlanning 处理一段）

内层（feedratePlanning）：
  取 window = q_split[k0 : k0+NHorz-1]   （NHorz=5 段窗口）
  → feedratePlanningSetupCurves           （处理零速边界，调整窗口）
  → buildConstr + FeedratePlanning_LP     （第一阶段 LP）
  → buildConstrJerk + FeedratePlanning_LP （第二阶段 LP，含跃度）
  → 提取 Coeff[:,1]（第一段结果）写入 opt_struct
  → 更新 ctx.v_0 = √(continuity·Coeff[:,1])  （滑动传递连续性）
  → ctx.k0++，push opt_struct 到 q_opt
```

`persistent kopt`：跨调用保持窗口内游标，在 `zero_end` 分发路径中按序分发系数列。

**窗口边界连续性传递：** 每次 LP 解出后，从第一段末端的连续性方程取出下一窗口的起始边界：

```matlab
X       = continuity * Coeff(:,1)   % 取第一段末端的 [v²; at]
ctx.v_0 = sqrt(X(1))                % 下一窗口起始速度
ctx.at_0 = X(2)                     % 下一窗口起始切向加速度
```

这保证了相邻两个窗口的连接处在速度和加速度上完全连续。

#### 6.3.6 零速边界处理

零速段（停止点前后的短桩段，由 Split 阶段切出）需要特殊的边界条件处理。

**为什么需要特殊处理？**

在零速点处 $v=0$，B 样条系数 $c_1 = 0$（速度为零边界），但加速度/跃度不为零（机器从零速以恒定跃度加速，逻辑上像汽车启动）。如果直接用 $a_t = 0$ 作为边界条件，LP 会求出"从零速到零加速"的平滑曲线，这在物理上是错误的（应该是突然从零启动）。

**恒跃度模型（`calcZeroConstraints.m`）：**

在零速桩段（`UseConstJerk=true`，`ConstJerk = jmax`）处，假设机器以恒定跃度 $j_0$ 从零速启动：

```text
j(t) = j₀ = const          （跃度恒定）
a(t) = j₀·t               （从 a=0 开始线性增加）
v(t) = j₀·t²/2             （从 v=0 开始二次增加）
```

在零速桩段末端（过渡到正常段的连接点），速度和切向加速度由以下参数唯一确定：

```text
k = (6/j₀)^(1/3)           （特征时间参数，由 ConstJerk 决定）
u, ud, udd, uddd = constJerkU(j₀, k, isEnd, true)
[V, A, ...] = calcRVAJfromUWithoutCurv(ud, udd, uddd, r0D, r1D, r2D, r3D)
vNorm  = ‖V‖               （连接点处的速度大小）
atNorm = t·A               （连接点处的切向加速度）
```

这两个值作为 LP 的边界条件（`v_0/at_0` 或 `v_1/at_1`），使得 LP 不需要从零速"摸索"如何启动，直接以物理正确的 ramp 速度连接。

**零速边界 LP 失败时的松弛（`relax_intial_constraints`）：**

零速桩段的 `ConstJerk` 初始设为 `jmax`（最大跃度），有时 LP 仍然不可行（约束过紧）。此时进入松弛循环：

```text
while !success and count < 15:
    curv.ConstJerk = curv.ConstJerk / 8    （每次将 ConstJerk 减小为原来的 1/8）
    重新计算 vNorm, atNorm
    更新 beq 中对应的边界行
    重新调用 c_simplex 求解
```

每次将跃度减小到 1/8，等价于允许更长的加速段（更低的峰值加速度），给 LP 更宽松的边界，直到找到可行解或超过 15 次。

**零速分发路径（`ctx.zero_end=true`）：**

当窗口末端是零速段时，LP 一次性把整个含零速末端的窗口都求解了（含最后的零速桩段）。之后对每个 `k0++`，不再重新求解 LP，而是从已有的 `ctx.Coeff` 中逐列取出系数分发：

```text
opt_struct.Coeff = ctx.Coeff(:, kopt)   （按序分发已求解的系数）
kopt++
```

直到 `kopt` 超过 `Coeff` 的列数（`NWindow`），才转回正常路径。

**紧急零速插入（`feedratePlanningForceZeroStop`）：**

若 LP 在非零速窗口下失败（几何约束过紧，速度无法连续过渡），强制在当前窗口末尾插入一个零速停止点：

```text
1. 对窗口最后一段 curv1：设置 ZSpdMode.NZ，调用 cutZeroEnd
   → curv1NN（主段）+ curv1NZ（零速末桩）
2. 若后面还有曲线 curv2：设置 ZSpdMode.ZN，调用 cutZeroStart
   → curv2ZN（零速起桩）+ curv2NN（主段）
3. 将 curv1NZ 和 curv2ZN 存入 ctx.zero_forced_buffer（备用缓冲）
4. 重构窗口：window = [原窗口 curv1NN, curv1NZ（新加的零速末桩）]
5. 重新 feedratePlanningSetupCurves + 再次调用 LP
```

若此次 LP 也失败，触发 `ocn_assert`（系统认为这是不可恢复的错误）。

#### 6.3.7 变量缩放矩阵（`compute_scaling_matrix`）

默认 `USE_LENGTH_SCALING = false`，$D = I$（单位矩阵）。

启用时（实验功能），按各段弧长平方对决策变量缩放：

```matlab
D = diag(1 ./ L²)    % L 是各段弧长
x_scaled = D · x     % 变量变换，使各段系数数量级相近
```

目的是改善 LP 的数值条件数：短段的 $v^2$ 系数通常比长段小得多，缩放后所有段系数量级相当，避免数值病态。

#### 6.3.8 运动学约束模式（TRAFO 标志）

在 `buildConstr` 中，每条曲线根据 `Info.TRAFO` 标志选择约束模式：

**TRAFO = false（纯笛卡尔，如 3 轴铣床）：**

```text
r1D_a = r1D          （加速度约束用笛卡尔导数）
r1D_r = kin.v_relative(r0D, r1D)   （速度约束用相对速度，考虑旋转基）
```

**TRAFO = true（5 轴机，需要运动学变换）：**

```text
[~, r1D_a, r2D_a] = kin.joint(r0D, r1D, r2D, r3D)
（将笛卡尔空间导数变换到关节空间，关节速度/加速度才受 vmax/amax 约束）
r1D_r = r1D    （相对速度约束保持笛卡尔空间）
```

运动学变换确保 5 轴机的旋转轴速度和加速度也被正确约束，而不是只看末端执行器速度。

### 6.4 链式法则计算运动学量（`calcRVAJfromU.m`）

曲线用弧长参数 u∈[0,1] 表达，LP 给出 u'(t)（速度平方的 B 样条）。

通过链式法则从几何导数转换为时间域运动学量：

```text
R = r(u)                                     位置
V = r'(u) · u'                               速度
A = r''(u) · u'² + r'(u) · u''              加速度
J = r'''(u) · u'³ + 3·r''(u)·u'·u'' + r'(u)·u'''   跃度
```

其中 u' = du/dt（由 LP 解得到），r'、r''、r''' 是曲线对参数 u 的几何导数。

### 6.5 B 样条（`Feedopt/bspline/`）

| 函数 | 说明 |
| --- | --- |
| `bspline_create.m` | 创建 B 样条基（给定阶次和断点序列） |
| `bspline_eval.m` | 在参数点求值（位置） |
| `bspline_base_eval.m` | 预计算基函数值及各阶导数（优化用） |
| `bspline_fit.m` | 最小二乘拟合 B 样条 |
| `bspline_eval_lee.m` | Lee 算法专用求值 |

### 6.6 运动学（`kinematics/`）

- **`Kinematics.m`**：运动学基类，封装正/逆运动学接口
- **`kinematic_factory.m`**：根据 `kin_type` 字符串创建对应运动学实例
- **`xyzbc_tt_H.m`**：XYZBC 桌台式五轴机床齐次变换矩阵
- **`homogeneous_transform.m`**：通用齐次变换工具函数

### 6.7 调试系统

项目使用单例模式的调试对象，在 MATLAB 模式下收集中间结果：

| 类 | 监控阶段 |
| --- | --- |
| `DebugCusp` | 尖点检测 |
| `DebugCompressing` | 曲线压缩 |
| `DebugTransition` | 过渡曲线生成 |
| `DebugOptimization` | LP 优化过程 |
| `DebugResampling` | 重采样 |

---

## 七、数据结构（`types/`）

### CurvStruct（核心数据载体）

每条 G-code 指令对应一个 `CurvStruct`，贯穿所有处理阶段。

| 字段 | 说明 |
| --- | --- |
| `Info` | G-code 元信息（曲线类型、进给率、主轴速度、零速标记等） |
| `tool` | 刀具定义（偏移量） |
| `sp` | B 样条结构（压缩后曲线填充） |
| `R0/R1` | 起/终点位姿向量 `[X,Y,Z,A,B,C]`（mm/rad） |
| `CorrectedHelixCenter` | 修正圆心（圆弧/螺旋线专用） |
| `delta` | 起终点半径差（螺旋线专用） |
| `evec` | 螺旋线轴方向单位向量 |
| `theta` | 螺旋线总旋转角（rad） |
| `pitch` | 螺旋线螺距（mm/rad） |
| `CoeffP5` | 5 次多项式过渡曲线系数（平滑阶段填充） |
| `Coeff` | LP 优化进给率 B 样条系数（优化阶段填充） |
| `a_param/b_param` | 子参数化映射（`u_local = a·u_global + b`） |
| `UseConstJerk/ConstJerk` | 零速段恒跃度约束 |

### 其他结构体

| 结构体 | 文件 | 说明 |
| --- | --- | --- |
| `SplineStruct` | `constrSplineStruct.m` | B 样条参数 |
| `HelixStruct` | `constrHelixStruct.m` | 螺旋线参数 |
| `TransP5Struct` | `constrTransP5Struct.m` | 5 次多项式过渡参数 |
| `AxesStruct` | `constrAxesStruct.m` | 机器轴配置 |
| `GcodeInfoStruct` | `constrGcodeInfoStruct.m` | G-code 元信息 |
| `ToolStruct` | `constrToolStruct.m` | 刀具定义 |
| `FeedoptCtxType` | `constrFeedoptCtxType.m` | 上下文完整类型（代码生成用） |

---

## 八、CSV 输出格式（重采样结果）

`resample2file` 按 `dt=1ms` 输出，每行一个时间步，列布局：

| 列 | 内容 | 单位 |
| --- | --- | --- |
| 1 | 时间步索引（× dt = 秒） | — |
| 2 | 参数 u | [0,1] |
| 3 | 归一化进给率（v/v_programmed） | — |
| 4 | 速度标量 | mm/s |
| 5 | 编程进给率 | mm/s |
| 6~5+N | 各轴位置 | mm/rad |
| 6+N~5+2N | 各轴加速度 | mm/s²/rad/s² |
| 6+2N~5+3N | 各轴跃度 | mm/s³/rad/s³ |
| 6+3N~5+4N | 机床坐标位置（含运动学变换） | mm/rad |

---

## 九、代码生成

项目支持将 MATLAB 代码编译为 C/C++，用于实时部署：

- **`generate/generate_c.m`**：主生成脚本（调用 MATLAB Coder）
- **`generate/generate_mex.m`**：生成 MEX 文件
- 函数标注 `%#codegen` 表示支持代码生成
- `coder.target('MATLAB')` 块中的代码仅在 MATLAB 模式执行（调试/可视化）
- 输出到 `arm64/` 或 `x86/` 目录

---

## 十、测试与验证

### 运行完整示例

```matlab
cd common/
startup          % 初始化路径
basic_example    % 运行完整流程
```

### 验证约束满足性

`Validate_OpenCN/Validate_OpenCN.m`：自动化验证套件，检查速度/加速度/跃度约束是否超限，以及时间最优性百分比。

### 测试 G-code 文件

`ngc_test/E2C/`：

- `037_dome_gravure_v1.ngc`（`basic_example.m` 默认使用）
- 多个版本的穹顶雕刻路径，用于回归测试

---

## 十一、外部依赖

| 依赖 | 用途 | 接口 |
| --- | --- | --- |
| COIN-OR CLP | LP 求解器 | MEX：`c_simplex.m` |
| LinuxCNC rs274ngc | G-code 解释器 | MEX 或直接 C++ 编译 |
| GSL | 数学函数库（GL 积分节点等） | MEX 封装 |
| MATLAB Coder | C/C++ 代码生成 | `generate_c.m` |

---

## 十二、阅读路线图（推荐顺序）

| 步骤 | 文件 | 关注点 |
| --- | --- | --- |
| 1 | `basic_example.m` | 全流程，理解输入/输出 |
| 2 | `Feedopt/Fopt.m` | 状态枚举（6 行） |
| 3 | `Feedopt/FeedoptDefaultConfig.m` | 所有参数含义 |
| 4 | `types/constrCurvStruct.m` | 核心数据载体字段 |
| 5 | `Feedopt/initFeedoptPlan.m` | ctx 初始化细节 |
| 6 | `Feedopt/FeedoptPlan.m` | FSM 调度逻辑 |
| 7 | `Feedopt/ReadGCode.m` | G-code 解析，MEX/代码生成双模式 |
| 8 | `Feedopt/compressCurvStructs.m` | 几何压缩，batch 机制 |
| 9 | `Feedopt/calcTransition.m` | G2 过渡曲线，Hermite 插值 |
| 10 | `Feedopt/feedratePlanning.m` | 滑动窗口策略 |
| 11 | `Feedopt/buildConstr.m` | LP 约束矩阵构造 |
| 12 | `Feedopt/FeedratePlanning_LP.m` | 两阶段 LP，松弛迭代 |
| 13 | `Feedopt/calcRVAJfromU.m` | 链式法则计算 V/A/J |

---

## 十三、阅读记录

### `basic_example.m`

- [x] 已阅读（注释已添加）
- 备注：全流程入口。注意 `get_res_struct` 解析 CSV 列索引的方式，后续分析结果时会用到。`plotAxisCommands` 用有限差分（`diff`）重新计算 v/a/j，与 LP 优化内部的解析计算有微小差异。

### `Feedopt/Fopt.m`

- [x] 已阅读（注释已添加）
- 备注：`Finished(67)` 的值设为 67 而非 7，是刻意避开与其他枚举值碰撞。继承 int32 使得代码生成中可以直接作为整数使用。

### `Feedopt/FeedoptDefaultConfig.m`

- [x] 已阅读（注释已添加）
- 备注：`maskTot=[1,1,1,0,1,1]` 是 XYZBC 五轴配置，A 轴未使用。`setMachineAxisInConfig` 会自动从 maskTot 派生 `indCart`/`indRot`/`NumberAxis` 等字段，这些字段不要手动修改。

### `types/constrCurvStruct.m`

- [x] 已阅读（注释已添加）
- 备注：`Coeff` 字段在 G-code 解析后为空，LP 优化阶段才写入。`a_param/b_param` 是子参数化（当一段 B 样条被分割成多段时，每个子段有各自的参数映射）。

### `Feedopt/initFeedoptPlan.m`

- [x] 已阅读（注释已添加）
- 备注：`BasisVal/D/DD/DDD` 和 `BasisIntegr` 是优化中用到的常量，提前计算。`try_push_again`、`simplex_calls`、`Skipped`、`forced_stop` 等字段注释中标注了"已废弃/历史遗留"。

### `Feedopt/FeedoptPlan.m` / `FeedoptPlanRun.m`

- [x] 已阅读（注释已添加）
- 备注：`FeedoptPlanRun` 只是外层驱动循环（含状态变化打印）；真正的逻辑在 `FeedoptPlan`。`Opt` 状态与其他状态不同，它会被**多次重入**直到 q_split 遍历完。`ReleaseMemoryOfTheQueues=true` 时，每个阶段完成后会删除前置队列节省内存。

### `Feedopt/ReadGCode.m`

- [x] 已阅读（注释已添加）
- 备注：MATLAB 模式通过 MEX 调用 C++；代码生成模式将 rs274ngc 的多个 `.cc` 文件直接编译进目标代码。支持读取 `.mat` 格式（预先导出的 CurvStructs 表），可用于调试回放。

### `Feedopt/compressCurvStructs.m`

- [x] 已阅读（注释已添加）
- 备注：关键是理解 batch 的 5 个关闭条件。极短线段（< 0.5mm）的处理：满足其他条件时仍加入 batch，跳过共线检查（共线检查在极短段上数值不稳定）。

### `Feedopt/smoothCurvStructs.m` / `calcTransition.m`

- [x] 已阅读（注释已添加）
- 备注：`calcTransition` 中 `ret==6` 的情况（数值警告）被允许继续构造过渡曲线，这是经验性决策（代码注释中有 TODO）。最终检查 `all(p5 <= 0)` 是防止多项式系数退化。

### `Feedopt/feedratePlanning.m`

- [x] 已阅读（注释已添加）
- 备注：`persistent kopt` 跨调用保持窗口内游标。`zero_end=true` 路径（从 ctx.Coeff 直接分发）只在上次 LP 已求解整个窗口（含零速末端段）时进入。两次 LP 失败后强制插入零速停止（`feedratePlanningForceZeroStop`）是容错机制。

### `Feedopt/buildConstr.m`

- [x] 已阅读（注释已添加）
- 备注：约束矩阵按曲线段分块对角排列。连续性等式约束用 `mask_continuity=[1;1;-1;-1]` 实现"前段末等于后段起"。窗口末端的速度/加速度斜坡（ramp）是为了避免 LP 只关注当前窗口末尾而忽略跨窗口连续性。

### `Feedopt/FeedratePlanning_LP.m`

- [x] 已阅读（注释已添加）
- 备注：变量缩放矩阵 D 默认为单位矩阵（`USE_LENGTH_SCALING=false`），仅在实验性配置下使用。松弛变量 `slack≥0` 允许约束轻微违反，`Coeff0(end)` 为松弛量，打印非零值即代表有约束违反。

### `Feedopt/calcRVAJfromU.m`

- [x] 已阅读（注释已添加）
- 备注：实际计算在 `calcRVAJfromUWithoutCurv` 中（4 行公式）。TRAFO 标志控制是否做运动学变换（五轴机需要将工件坐标转换为关节坐标）。同时注释了 `calcRVAJfromUWithoutCurv.m` 中的链式法则公式。

### `Feedopt/cutCurvStruct.m` / `cutCurvStructU.m` / `splineLengthFindU.m` / `LengthCurv.m`

- [x] 已阅读并添加详细注释
- 备注：弧长截取系统。核心设计：截取只更新 `a_param`/`b_param` 参数映射，B 样条系数不变。Line/Helix 均匀参数化 → 解析截取（`Δu = L/‖r'‖`）；Spline/TransP5 → 两阶段弧长反演（cumsum 粗查断点区间 + bisection 精确反演，tol=1e-7，最多 1000 次迭代）。截取后右半段 `b_param > 0`，在 `smoothCurvStructs` 中用于跳过 G2 检查（截点天然连续）。`ZSpdMode` 更新规则：截点是内部点（N），各半段继承原曲线对应端的零速状态。`checkParametrisation` 验证 `a>0, b>=0, a+b<=1`。

### `bspline_*.m`

- [ ] 待阅读
- 备注：

### `kinematics/`

- [ ] 待阅读
- 备注：

---

## 十四、疑问与待确认

- [ ] `ctx.go_next` 和 `ctx.try_push_again` 的实际作用区别？（`try_push_again` 注释标注已废弃）
- [ ] `ctx.Skipped` / `ctx.forced_stop` 字段的用途？（初始化注释中均标注为"历史遗留/用途不明"）
- [ ] `ZSpdMode` 枚举的完整语义：`ZZ`（起止均零速）、`ZN`（零速起 → 正常末）、`NZ`（正常起 → 零速末）、`NN`（全程非零速）—— 换刀时如何触发这四种模式？
- [ ] 优化窗口 `NHorz=5` 的滑动策略：每次取第 k0 段开始的 5 段，但只提取第 k0 段的解。这是否意味着同一段会被多次求解（但只用第一次的结果）？
- [ ] `buildConstrJerk` 的线性化方法：跃度约束本身是非线性（含 v³），如何在第一阶段解的基础上做 Taylor 线性化？需要读 `buildConstrJerk.m`。
- [ ] `calcTransition` 中 `ret==6` 的触发条件？（G2_Hermite 内部何时返回 6？）
