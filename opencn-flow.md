# OpenCN 进给率优化系统——完整代码流程文档

本文档梳理 `common/Feedopt/` 目录下全部代码的调用链路与数据流向。  
所有流程图使用 Mermaid 语法（VSCode / GitHub / Obsidian 可直接渲染）。

---

## 目录

1. [系统总览](#1-系统总览)
2. [核心数据结构详解](#2-核心数据结构详解)
3. [初始化：initFeedoptPlan](#3-初始化initfeedoptplan)
4. [FSM 状态机与外层驱动](#4-fsm-状态机与外层驱动)
5. [阶段 1：G-Code 解析（GCode）](#5-阶段-1g-code-解析gcode)
6. [阶段 2：几何检查（Check）](#6-阶段-2几何检查check)
7. [阶段 3：曲线压缩（Compress）](#7-阶段-3曲线压缩compress)
8. [阶段 4：平滑过渡（Smooth）](#8-阶段-4平滑过渡smooth)
9. [阶段 5：曲线分割（Split）](#9-阶段-5曲线分割split)
10. [阶段 6：进给率优化（Opt）](#10-阶段-6进给率优化opt)
11. [LP 约束矩阵构建详解](#11-lp-约束矩阵构建详解)
12. [曲线截取子系统（cutCurvStruct）](#12-曲线截取子系统cutcurvstruct)
13. [曲线求值子系统（EvalCurvStruct）](#13-曲线求值子系统evalcurvstruct)
14. [弧长计算子系统](#14-弧长计算子系统)
15. [关键参数速查表](#15-关键参数速查表)
16. [完整函数调用树](#16-完整函数调用树)

---

## 1. 系统总览

### 1.1 七阶段数据流

```mermaid
flowchart LR
    Input([G-Code 文件\n.ngc / .nc]) --> INIT

    INIT["initFeedoptPlan()\n① 创建 B 样条基 Bl\n② 预计算 BasisVal/D/DD\n③ 分配 6 个队列\n④ 设 ctx.op = Init"]

    INIT --> FSM

    subgraph FSM["FeedoptPlanRun → FeedoptPlan FSM"]
        direction TB
        S1["① GCode\nReadGCode → rs274ngc 解释器\n换刀零速 / 刀具偏移 / 角度转换\n→ q_gcode"]
        S2["② Check\nCheckCurvStructs → 尖点检测\n超阈值角度 → 插零速停顿\n→ q_gcode（原地修改）"]
        S3["③ Compress\ncompressCurvStructs\nLee B 样条批次拟合\n→ q_compress + q_spline"]
        S4["④ Smooth\nsmoothCurvStructs\nG2 Hermite 过渡曲线\n→ q_smooth"]
        S5["⑤ Split\nsplitQueue\n零速段切割 + 等弧长分段\n→ q_split"]
        S6["⑥ Opt\nfeedratePlanning\n滑动窗口两阶段 LP\n→ q_opt"]
        S1 --> S2 --> S3 --> S4 --> S5 --> S6
    end

    S6 --> Output([q_opt\n各段含 Coeff\nB 样条进给率系数])
    Output --> Resample([resample\n插补输出\n等时间步 setpoint])
```

### 1.2 各阶段输入输出汇总

| 阶段 | 入口函数 | 读取队列 | 写入队列 | 关键变换 |
|------|---------|---------|---------|---------|
| Init | `initFeedoptPlan` | — | 创建所有队列 | 预计算 B 样条基矩阵 |
| GCode | `ReadGCode` | G-Code 文件 | `q_gcode` | rs274ngc 解析、换刀零速、deg→rad |
| Check | `CheckCurvStructs` | `q_gcode` | `q_gcode`（原地） | 尖点→零速停顿 |
| Compress | `compressCurvStructs` | `q_gcode` | `q_compress`, `q_spline` | 直线批次 Lee B 样条拟合 |
| Smooth | `smoothCurvStructs` | `q_compress` | `q_smooth` | G2 Hermite 过渡曲线插入 |
| Split | `splitQueue` | `q_smooth` | `q_split` | 零速段切割 + 等弧长分段 |
| Opt | `feedratePlanning` | `q_split` | `q_opt` | 滑动窗口两阶段 LP |

---

## 2. 核心数据结构详解

### 2.1 CurvStruct 完整字段

```
CurvStruct                          说明
├── Info
│   ├── Type        CurveType       曲线几何类型（见下表）
│   ├── zspdmode    ZSpdMode        零速模式（NN/ZN/NZ/ZZ）
│   ├── FeedRate    double          G-Code 编程进给率（mm/min）
│   ├── SpindleSpeed double         主轴转速（rpm）
│   ├── gcode_source_line int32     对应 G-Code 的行号（调试用）
│   └── TRAFO       bool            是否需要运动学坐标变换（5 轴联动）
│
├── a_param         double ∈(0,1]   参数窗口宽度（全局参数区间长度）
├── b_param         double ∈[0,1)   参数窗口起点（全局参数区间起始）
│       → 曲线在全局参数空间 [b, b+a] 上定义
│       → 求值时：u_global = a*u_local + b，u_local ∈ [0,1]
│
├── R0              [NAxis×1]       全轴起点坐标（含旋转轴，弧度）
├── R1              [NAxis×1]       全轴终点坐标
│
├── ── Line 专用 ──────────────────────────────────────────────
│   （无额外字段，R0/R1 即为起终点）
│
├── ── Helix 专用 ─────────────────────────────────────────────
│   ├── evec            [3×1]       螺旋轴方向单位向量 ê
│   ├── theta           double      总圆心角 θ（rad，正/负对应方向）
│   ├── pitch           double      螺距（mm/圈，纯圆弧时=0）
│   └── CorrectedHelixCenter [3×1] 修正后的圆心 C
│
├── ── Spline 专用 ─────────────────────────────────────────────
│   └── sp_index        int32       q_spline 中 B 样条数据的索引
│
├── ── TransP5 专用 ────────────────────────────────────────────
│   └── CoeffP5         [NDim×6]    五次多项式系数矩阵（每行一轴，降幂排列）
│
├── ── 零速段专用 ──────────────────────────────────────────────
│   ├── UseConstJerk    bool        是否使用恒定跃度速度曲线（cutZeroStart/End 设置）
│   └── ConstJerk       double      恒定跃度参数 jps（zeroSpeedCurv 预计算）
│
├── tool                            刀具信息（类型、偏移量）
└── Coeff           [N×1]           优化后的 B 样条进给率系数（Opt 阶段填入）
```

### 2.2 CurveType 枚举

| 值 | 名称 | 参数化公式 | 弧长均匀性 |
|----|------|-----------|-----------|
| 0 | None | — | — |
| 1 | Line | `r(u) = P0(1-u) + P1·u` | 均匀（‖r'‖=‖P1-P0‖=常数） |
| 2 | Helix | `r(u) = C + cos(θu)·CP0 + sin(θu)·(ê×CP0) + (p/2π)·θu·ê` | 均匀（‖r'‖=√(θ²R²+(θp/2π)²)=常数） |
| 3 | Spline | B 样条，4 次，C2 连续 | 非均匀（需数值积分） |
| 4 | TransP5 | `r(u) = Σ c_j·u^j`，j=0..5 | 非均匀（需中点积分） |

### 2.3 ZSpdMode 枚举与转换关系

```mermaid
flowchart TD
    NN["NN (0)\n普通-普通\n两端正常速度"] 
    ZN["ZN (1)\n零速起始-普通终止\n从零速加速段"]
    NZ["NZ (2)\n普通起始-零速终止\n减速到零速段"]
    ZZ["ZZ (3)\n零速-零速\n孤立短段"]

    NN -- "遇到停顿需求\n(尖点/换刀/失败)" --> NZ
    NN -- "cutZeroStart\n切出加速段" --> ZN
    NZ -- "cutZeroStart\n切出加速段" --> ZZ
    ZN -- "遇到停顿需求" --> ZZ

    style NN fill:#9cf,color:#000
    style ZN fill:#9f9,color:#000
    style NZ fill:#f96,color:#000
    style ZZ fill:#f66,color:#000
```

### 2.4 六个流水线队列

```mermaid
flowchart LR
    qG[(q_gcode\nCurvStruct[]\nGCode 阶段填充)]
    qC[(q_compress\nCurvStruct[]\nCompress 填充)]
    qSp[(q_spline\nBSpline[]\nCompress 填充)]
    qSm[(q_smooth\nCurvStruct[]\nSmooth 填充)]
    qSplit[(q_split\nCurvStruct[]\nSplit 填充)]
    qOpt[(q_opt\nCurvStruct[含Coeff]\nOpt 填充)]

    qG --> qC
    qG -.-> qSp
    qC --> qSm
    qSm --> qSplit
    qSplit --> qOpt

    note1["Compress 阶段:\n消费 q_gcode\n产出 q_compress\n同步产出 q_spline"]
    note2["Smooth 阶段:\n读 q_compress + q_spline\n产出 q_smooth"]
    note3["Opt 阶段:\n读 q_split + q_spline\n产出 q_opt"]
```

### 2.5 ctx 上下文关键字段

```
ctx
├── cfg             FeedoptDefaultConfig   配置结构体（所有可调参数）
├── op              Fopt                   当前 FSM 状态
├── k0              int32                  当前处理曲线的索引指针
├── go_next         bool                   上次是否产出结果（驱动 k0++）
├── zero_start      bool                   当前窗口起端为零速
├── zero_end        bool                   当前窗口末端为零速
├── zero_forced     bool                   是否强制插入了零速停顿
├── zero_forced_buffer [2]CurvStruct       强制零速时的缓冲曲线
├── v_0/v_1         double                 窗口起/末端速度边界条件
├── at_0/at_1       double                 窗口起/末端切向加速度边界
├── BasisVal        [M×N]                  B 样条基函数值（预计算）
├── BasisValD       [M×N]                  B 样条基一阶导（预计算）
├── BasisValDD      [M×N]                  B 样条基二阶导（预计算）
├── BasisIntegr     [N×1]                  B 样条基积分（目标函数用）
├── u_vec           [1×M]                  离散化参数点
├── Bl              BSpline                B 样条基结构体
├── Coeff           [N×NWindow]            上一次 LP 的解（分配给零速路径）
├── kin             Kinematics             运动学对象（5 轴坐标变换）
├── q_gcode / q_compress / q_spline / q_smooth / q_split / q_opt
└── errcode / errmsg                       错误信息（异常时设置）
```

---

## 3. 初始化：initFeedoptPlan

```mermaid
flowchart TD
    A([外部调用\ninitFeedoptPlan cfg]) --> B{"cfg.UseLinear\nBreakpoints?"}

    B -- "true（均匀断点）" --> C["Bl = bspline_create(\n  SplineDegree,\n  linspace(0,1,NBreak)\n)\nu_vec = linspace(0,1,NDiscr)"]

    B -- "false（正弦密端断点）" --> D["Bl = bspline_create(\n  SplineDegree,\n  sinspace(0,1,NBreak)\n)\nu_vec = sinspace(0,1,NDiscr)"]

    C & D --> E["bspline_base_eval(Bl, u_vec)\n预计算 5 个矩阵：\n  BasisVal    [M×N]  基函数值\n  BasisValD   [M×N]  一阶导\n  BasisValDD  [M×N]  二阶导\n  BasisValDDD [M×N]  三阶导\n  BasisIntegr [N×1]  基函数在[0,1]的积分"]

    E --> F["初始化 6 个队列\nconstrCurvStructType 作为类型模板\nq_gcode / q_compress / q_spline\nq_smooth / q_split / q_opt"]

    F --> G["FSM 控制变量\nctx.op = Fopt.Init\nctx.k0 = 1\nctx.go_next = false\nctx.v_0 = cfg.v_0（通常=0）\nctx.v_1 = cfg.v_1（通常=0）"]

    G --> H["运动学对象\nctx.kin = export_kinematic_class()\n包含 joint() / v_relative() 等方法"]

    H --> I([返回完整 ctx])

    subgraph why["为何预计算 BasisVal？"]
        W1["LP 优化每轮都需要\n对同一 u_vec 求 B 样条基值"]
        W2["预计算避免重复计算\n（优化循环可能数万次调用）"]
    end
```

---

## 4. FSM 状态机与外层驱动

### 4.1 FeedoptPlanRun 外层循环

```mermaid
flowchart TD
    A([FeedoptPlanRun ctx]) --> B["prev_op = Fopt.Init"]
    B --> LOOP{"ctx.op\n!= Finished?"}
    LOOP -- "否" --> END([返回 ctx])
    LOOP -- "是" --> DBG{"coder.target MATLAB\n且状态切换?"}
    DBG -- "是" --> PRINT["打印上一阶段的\n队列长度\n(GCode→q_gcode.size等)"]
    DBG -- "否" --> TRY
    PRINT --> TRY
    TRY["try\n  [ctx, optimized, opt_curv]\n   = FeedoptPlan(ctx)"]
    TRY -- "成功" --> LOOP
    TRY -- "catch ME" --> ERR["ctx.errcode = ctx.op\nctx.errmsg = ME.message\nctx.op = Finished"]
    ERR --> LOOP
```

### 4.2 FeedoptPlan FSM 状态转换

```mermaid
stateDiagram-v2
    [*] --> Init : initFeedoptPlan()

    Init --> GCode : 无条件跳转

    GCode --> Check : assert_queue()\n三项验证通过

    Check --> Compress : 尖点处理完成

    Compress --> Smooth : assert_queue()\nq_compress 已填充

    Smooth --> Split : assert_queue()\nq_smooth 已填充

    Split --> Opt : assert_queue()\nq_split 已填充\nDebugOptimization.reset()

    Opt --> Opt : 每次调用产出 1 段\nq_opt.push(opt_struct)\nk0++（go_next=true）
    Opt --> Finished : k0 > q_split.size\n或 q_split 为空

    Finished --> [*]

    note right of Opt
        Opt 是唯一"多次重入"状态
        每次 FeedoptPlan 调用推进一个窗口
        FeedoptPlanRun 循环调用直到 k0 超出
    end note

    note left of Check
        assert_queue 检验：
        1. checkGeometry() 几何合法
        2. checkZSpdmode() 零速标记传递合法
        3. checkParametrisationQueue() 参数窗口合法
    end note
```

---

## 5. 阶段 1：G-Code 解析（GCode）

**入口**：`FeedoptPlan` case `Fopt.GCode`  
**核心**：`ReadGCode()` 封装 rs274ngc 解释器（MATLAB: MEX；codegen: 内嵌 C++）

### 5.1 主流程

```mermaid
flowchart TD
    A([进入 GCode 状态]) --> B["ReadGCode(Load, 文件路径)\n打开并初始化解释器"]

    B --> C{"ReadGCodeError?\n文件可以打开?"}
    C -- "InterpNotOpen\n（无法打开）" --> ERR([断言失败 / 退出])

    C -- "正常" --> LOOP["初始化:\nCurvStruct.Type = None\nk0 = 1"]

    LOOP --> D["ReadGCode(Read)\n读一条 G-Code 指令"]

    D --> E{"返回的\nCurvStruct.Type\n!= None?"}

    E -- "None（注释/空行）" --> F{"status ==\nInterpExit?"}
    F -- "是" --> LAST["处理最后一段:\n若 isAZeroStart → ZZ\n否则 → NZ（末段必须零速）\nq_gcode.set(last)"]
    F -- "否" --> D

    E -- "有效曲线" --> G{"队列非空？\n检测换刀？\ntoolIsEqual(prev,cur)"}

    G -- "刀具相同" --> TC["跳过换刀处理"]
    G -- "刀具不同\n(换刀)" --> TOOL["换刀零速处理:\n  前段(prev):\n    isAZeroStart? → ZZ : NZ\n  后段(cur):\n    isAZeroEnd?   → ZZ : ZN\nq_gcode.set(size, prev)"]

    TC & TOOL --> OFF["add_tool_offset(CurvStruct, prev_tool)\n将刀具长度偏移加到 Z 轴坐标"]

    OFF --> DEG["旋转轴单位转换:\nR0(4:end) = deg2rad(R0(4:end))\nR1(4:end) = deg2rad(R1(4:end))"]

    DEG --> NAN["NaN → 0\n（未指定轴保持上一位置，\n简化时取 0）"]

    NAN --> CHK["断言 FeedRate > 0"]

    CHK --> PUSH["q_gcode.push(CurvStruct)\nk0++"]

    PUSH --> F

    LAST --> VALID["assert_queue(q_gcode)\n①checkGeometry()\n②checkZSpdmode()\n③checkParametrisationQueue()"]

    VALID --> END([ctx.op = Check])
```

### 5.2 assert_queue 三项验证

```mermaid
flowchart LR
    Q[(队列)] --> A["checkGeometry()\n遍历相邻曲线对\ncurv_k.R1 ≈ curv_{k+1}.R0?\n几何首尾连续"]

    Q --> B["checkZSpdmode()\n验证零速模式传递合法：\n- NZ 段后面必须是 ZN 或 ZZ\n- 最后一段必须是 NZ 或 ZZ"]

    Q --> C["checkParametrisationQueue()\n对每条曲线调用\ncheckParametrisation():\n  a>0, a≤1\n  b≥0, b<1\n  a+b≤1"]

    A & B & C --> RES{全部通过?}
    RES -- "是" --> OK([继续])
    RES -- "否" --> FAIL([ocn_assert 失败])
```

---

## 6. 阶段 2：几何检查（Check）

**入口**：`FeedoptPlan` case `Fopt.Check`  
**核心**：`CheckCurvStructs()` + `iscusp()`

```mermaid
flowchart TD
    A([进入 Check 状态]) --> B{"cfg.Cusp.Skip?"}
    B -- "true（跳过）" --> SKIP

    B -- "false" --> C["遍历 q_gcode 相邻曲线对 (curv_k, curv_{k+1})"]

    C --> D["EvalCurvStruct(curv_k, u=1)\n求 curv_k 末端的一阶导 r1D_k"]

    D --> E["EvalCurvStruct(curv_{k+1}, u=0)\n求 curv_{k+1} 起端的一阶导 r1D_{k+1}"]

    E --> F["iscusp(r1D_k, r1D_{k+1}, cfg.Cusp.Threshold)\ncos_angle = dot(t1,t2) / (‖t1‖·‖t2‖)\niscusp = cos_angle < threshold"]

    F -- "不是尖点" --> NEXT
    F -- "是尖点\n（方向突变）" --> INS["插入零速停顿:\n  curv_k → 设 NZ（末端零速）\n  curv_{k+1} → 设 ZN（起端零速）\n  更新 q_gcode 中对应位置"]

    INS --> NEXT["下一对"] --> C

    C -- 遍历结束 --> SKIP["assert_queue(q_gcode)"]
    SKIP --> END([ctx.op = Compress])
```

---

## 7. 阶段 3：曲线压缩（Compress）

**入口**：`FeedoptPlan` case `Fopt.Compress`  
**核心**：`compressCurvStructs()` → 批次机制 + Lee 算法

### 7.1 主流程

```mermaid
flowchart TD
    A([进入 Compress 状态]) --> B{"cfg.Compressing.Skip?"}

    B -- "true" --> COPY["直接复制:\n for k=1:q_gcode.size\n   q_compress.push(q_gcode.get(k))\n end"]

    B -- "false" --> INIT["compressCurvStructs(ctx)\ninitialize: batch = batch_init()\nspline_index = q_spline.size+1"]

    INIT --> LOOP["遍历 q_gcode 逐条处理 k=1..Ncrv"]

    LOOP --> D["curv = q_gcode.get(k)"]

    D --> E["check_add_batch(ctx, curv)\n判断是否可加入当前批次"]
    E --> F["check_close_batch(ctx, batch, curv, addBatch)\n判断当前批次是否需要关闭"]

    F -- "closeBatch=true" --> G["batch_close(ctx, batch, spline_index)"]
    G --> H{"批次中的曲线数量\nbatch.N > 1?"}
    H -- "是（多段，可拟合）" --> LEE["CalcBspline_Lee(batch)\nLee 算法拟合一条 B 样条\n→ 生成 sp_index\nq_compress.push(Spline曲线)\nq_spline.push(BSpline数据)"]
    H -- "否（单段，直接传）" --> PASS["q_compress.push(batch中唯一曲线)"]
    LEE & PASS --> J

    F -- "closeBatch=false" --> J{"addBatch?"}

    J -- "true" --> ADD["batch_add_curv(batch, curv)\n将 curv 加入批次\n记录端点坐标 + 弧长"]
    J -- "false（非直线等）" --> DIRECT["q_compress.push(curv)\n直接透传（不压缩）"]

    ADD & DIRECT --> NEXT["下一条曲线"] --> LOOP

    LOOP -- 结束 --> FINAL["batch_close(batch, spline_index)\n处理最后未关闭批次"]

    COPY & FINAL --> VALID["assert_queue(q_compress)"]
    VALID --> END([ctx.op = Smooth\n释放 q_gcode 内存])
```

### 7.2 批次准入条件（check_add_batch）

```mermaid
flowchart TD
    C1{"Type == Line?"} -- "否" --> NO([addBatch = false])
    C1 -- "是" --> C2{"Length <= LThresholdMax?"}
    C2 -- "否" --> NO
    C2 -- "是" --> C3{"与前一段共线?\ncos_angle >= ColTolCosLee\n(即夹角 < ~2°)"}
    C3 -- "否" --> NO
    C3 -- "是" --> C4{"机床参数相同?\n进给率 + 主轴转速\n+ 刀具类型"}
    C4 -- "否" --> NO
    C4 -- "是" --> C5{"isAZeroStart == false?\n零速起始段不进批次\n（防止压缩越过零速边界）"}
    C5 -- "否" --> NO
    C5 -- "是" --> YES([addBatch = true])
```

### 7.3 批次关闭条件（check_close_batch）

```mermaid
flowchart TD
    P1{"批次非空？\nbatch.N > 0"} -- "否（空批次）" --> NO([closeBatch = false])
    P1 -- "是" --> P2{"addBatch == false?\n当前曲线不能加入"}
    P2 -- "是" --> YES([closeBatch = true\n当前曲线会触发关闭])
    P2 -- "否（可以加入）" --> P3{"批次已满？\nbatch.N >= NLeeMax"}
    P3 -- "是" --> YES
    P3 -- "否" --> P4{"当前曲线是 ZeroEnd？\n零速边界强制关闭批次"}
    P4 -- "是" --> YES
    P4 -- "否" --> NO
```

### 7.4 Lee 算法 B 样条拟合（CalcBspline_Lee）

```mermaid
flowchart TD
    A["输入: N 个折线段端点 P_0, P_1, ..., P_N\n（累积的批次直线段端点）"] 

    A --> B["步骤 1：弦长参数化（1/4 幂）\n弦长 Δs_k = ‖P_{k+1} - P_k‖\n参数 t_k = cumsum(Δs_k^(1/4)) / total\n（1/4 幂比均匀参数化更适合曲线拟合）"]

    B --> C["步骤 2：构造 B 样条基矩阵 B\n次数 = SplineDegree（通常 4）\n节点向量均匀分布在 [0,1]\n求 B 在参数点 {t_k} 处的值\nB ∈ R^{N×NCtrl}"]

    C --> D["步骤 3：求解三对角线性方程组\nB·P_ctrl = R（R 为插值点坐标）\nThomas 算法 O(N) 求解\ntridiag(B, R) → 控制点 P_ctrl"]

    D --> E["步骤 4：构造 BSpline 结构体\nbspline_create(degree, knots)\n存入 q_spline\n对应的 CurvStruct 设 Type=Spline\nsp_index 指向 q_spline"]

    E --> F["输出: CurvStruct (Spline)\n+ BSpline 几何数据 sp"]

    subgraph why["为何使用 1/4 幂参数化？"]
        W1["‖Δr_k‖^(1/4) ≈ 等角度参数化近似"]
        W2["比均匀参数化 (α=1) 和弦长参数化 (α=1)\n更能适应曲率变化，减少振荡"]
    end
```

---

## 8. 阶段 4：平滑过渡（Smooth）

**入口**：`FeedoptPlan` case `Fopt.Smooth`  
**核心**：`smoothCurvStructs()` + `calcTransition()` + `G2_Hermite_Interpolation_nAxis()`

### 8.1 主循环逻辑

```mermaid
flowchart TD
    A([进入 Smooth 状态]) --> INIT["curv = q_compress.get(1)\n从第 1 段开始"]

    INIT --> LOOP["k = 2 .. Ncrv\nnextCurv = q_compress.get(k)"]

    LOOP --> CST["check_stop_and_transition(\n  ctx, curv, nextCurv,\n  ColTolSmooth, ColTolCosSmooth)"]

    CST --> D1{"isAZeroEnd(curv)?"}
    D1 -- "是" --> BRKA["分支 A：零速停顿\nadd_zero_stop()\n  q_smooth.push(curv)\n  curv = nextCurv"]

    D1 -- "否" --> D2{"nextCurv.b_param > 0?\n（是截取右半段，\n G2 由截取操作保证）"}
    D2 -- "是（跳过检测）" --> BRKD["分支 D：直接 push\nq_smooth.push(curv)\ncurv = nextCurv"]

    D2 -- "否" --> D3["check_smoothness(curv, nextCurv)\n三项几何连续性检验"]

    D3 -- "isSmooth=true" --> BRKD

    D3 -- "isSmooth=false" --> D4{"cfg.Smoothing.Skip?"}
    D4 -- "true（调试模式）" --> BRKB["分支 B：强制零速\ncreate_zero_end(curv,nextCurv)\nadd_zero_stop()"]

    D4 -- "false" --> D5["calcTransition(ctx, curv, nextCurv)"]

    D5 --> D6{"TransitionResult?"}

    D6 -- "Ok" --> BRKC["分支 C-OK：插入过渡\nq_smooth.push(curv1C)\nq_smooth.push(curvT)\ncurv = curv2C"]

    D6 -- "NoSolution" --> BRKCF["分支 C-Fail：退化零速\ncreate_zero_end()\nadd_zero_stop()"]

    BRKA & BRKB & BRKC & BRKD & BRKCF --> NEXT["下一对"] --> LOOP

    LOOP -- 结束 --> LAST["q_smooth.push(curv)\n推入最后一段"]
    LAST --> END([ctx.op = Split])
```

### 8.2 G2 连续性三项检验（check_smoothness）

```mermaid
flowchart LR
    subgraph Left["curv0 末端（u=1）"]
        E0["EvalCurvStruct(curv0, 1)\n→ r11（位置）\n→ r1d1（一阶导）\n→ r1dd1（二阶导）"]
        T0["calc_t_nk_kappa(r1d1, r1dd1)\n→ t1（切向单位向量）\n→ κ1（曲率标量）"]
        E0 --> T0
    end

    subgraph Right["curv1 起端（u=0）"]
        E1["EvalCurvStruct(curv1, 0)\n→ r21（位置）\n→ r2d1（一阶导）\n→ r2dd1（二阶导）"]
        T1["calc_t_nk_kappa(r2d1, r2dd1)\n→ t2\n→ κ2"]
        E1 --> T1
    end

    T0 & T1 --> C0["C0 位置连续:\nall(|r11 - r21| < ColTolSmooth)"]
    T0 & T1 --> G1["G1 切向连续:\ncollinear(t1, t2, ColTolCosSmooth)\n= dot(t1,t2)/(‖t1‖‖t2‖) ≥ tol_cos"]
    T0 & T1 --> G2c["G2 曲率连续:\nall(|κ1 - κ2| < ColTolSmooth)"]

    C0 & G1 & G2c --> AND{全部 true?}
    AND -- "是" --> OK([isSmooth = true])
    AND -- "否" --> FAIL([isSmooth = false\n需要过渡曲线或零速])
```

### 8.3 calcTransition 过渡曲线计算

```mermaid
flowchart TD
    A["calcTransition(ctx, curv1, curv2)"] 

    A --> L["计算弧长:\nL1 = LengthCurv(curv1)\nL2 = LengthCurv(curv2)\nCutOff = cfg.CutOff (~0.1mm)"]

    L --> CHK{"L1 < 3×CutOff\n或 L2 < 3×CutOff?"}
    CHK -- "是（太短）" --> NOSOL1([NoSolution: 曲线太短])

    CHK -- "否" --> CUT["截取两端:\n① cutCurvStruct(curv1, isEnd=false, L1-CutOff)\n   → curv1C（去掉末端 CutOff）\n② cutCurvStruct(curv2, isEnd=true, L2-CutOff)\n   → curv2C（去掉起端 CutOff）"]

    CUT --> EVAL["在截点处求几何量:\n[r0D0, r0D1, r0D2] = EvalCurvStruct(curv1C, u=1)\n[r1D0, r1D1, r1D2] = EvalCurvStruct(curv2C, u=0)"]

    EVAL --> HERM["G2_Hermite_Interpolation_nAxis(\n  ctx,\n  r0D0, r0D1, r0D2,\n  r1D0, r1D1, r1D2\n)\n→ p5[NDim×6], ret"]

    HERM --> RET{"ret 值?"}

    RET -- "1（正常）" --> OK1[status = Ok]
    RET -- "6（数值警告但可接受）" --> OK1
    RET -- "2 或其他" --> NOSOL2([NoSolution: 矩阵病态])

    OK1 --> P5CHK{"all(p5 ≤ 0)?\n多项式系数全非正\n→ 退化曲线"}
    P5CHK -- "是" --> NOSOL3([NoSolution: 系数退化])

    P5CHK -- "否" --> CTRANS["constrTransP5Struct()\n构造 curvT (TransP5):\n  R0T = r0D0（过渡段起点）\n  R1T = r1D0（过渡段终点）\n  CoeffP5 = p5\n  FeedRate = min(f1, f2)（保守）\n  SpindleSpeed = min(s1, s2)"]

    CTRANS --> VERIF["check_continuity(curv1C, curvT)\ncheck_continuity(curvT, curv2C)\n验证连接处 C0+G1+G2"]

    VERIF -- "不满足（ret=8）" --> NOSOL4([NoSolution: 连续性验证失败])
    VERIF -- "满足" --> FINAL([Ok: 返回 curv1C, curv2C, curvT])
```

### 8.4 G2 Hermite 插值（G2_Hermite_Interpolation_nAxis）

```mermaid
flowchart TD
    IN["输入（6 个向量）:\n左端: r0D0（位置）、r0D1（一阶导）、r0D2（二阶导）\n右端: r1D0、r1D1、r1D2\n（已 padding 到 N_AXES_MAX=6 维）"]

    IN --> FR["calc_t_nk_kappa(r0D1, r0D2) → t0, n0, κ0\ncalc_t_nk_kappa(r1D1, r1D2) → t1, n1, κ1"]

    FR --> NOTE["【边界条件参数化】\n用 Frenet 框架将 G2 边界条件转换为:\n  r'(0) = α0·t0         （切向拉伸参数 α0 > 0）\n  r''(0) = β0·t0 + α0²·n0·κ0  （含曲率的二阶导）\n  r'(1) = α1·t1\n  r''(1) = β1·t1 + α1²·n1·κ1\n→ 求最优 (α0, α1) 使 ∫‖r'''‖²du 最小"]

    NOTE --> CS["CoefPolySys(r0D0, t0, n0, r1D0, t1, n1, D)\n计算多项式方程组的 16 个系数\n[a1,a0,b1,b0,c3,c2,c1,c0,d1,d0,e1,e0,f3,f2,f1,f0]"]

    CS --> CASE{"κ 的情况"}

    subgraph Case1["情况1: κ0=0 且 κ1=0（直线-直线）"]
        C1A["p1 和 p2 各退化为线性\n→ 2×2 线性方程组:\n  [b0  c1] [α0]   [-c0]\n  [f1  e0] [α1] = [-f0]\nM\\B 直接求解"]
    end

    subgraph Case2["情况2: κ0=0（直线-曲线）"]
        C2A["p1 线性化，p2 仍三次\n结式消元得 α1 的三次多项式:\n  Coef = [b1d0-c3f1, b0d0+b1e0-c2f1, b0e0+b1f0-c1f1, b0f0-c0f1]\nc_roots_(Coef) → α1 正实根\n回代 → α0"]
    end

    subgraph Case3["情况3: κ1=0（曲线-直线）"]
        C3A["与情况2对称\np2 线性化 → α0 的三次多项式\nc_roots_ → α0 正实根\n回代 → α1"]
    end

    subgraph Case4["情况4: 一般（κ0≠0 且 κ1≠0）"]
        C4A["CharPolyAlpha1(CoefPS)\n计算结式 → α1 的 9 次多项式\nc_roots_ → 所有根\nCalcAlpha0 → 对应 α0"]
    end

    CASE -- "κ0=0∧κ1=0" --> Case1
    CASE -- "κ0=0,κ1≠0" --> Case2
    CASE -- "κ0≠0,κ1=0" --> Case3
    CASE -- "κ0≠0∧κ1≠0" --> Case4

    Case1 & Case2 & Case3 & Case4 --> FILT["筛选 α0>0 且 α1>0 的正实根\n（负根意味着切向反转，不合法）"]

    FILT -- "无正实根" --> FAIL([status=3/4/5, NoSolution])
    FILT -- "1 个正实根" --> BETA
    FILT -- "多个正实根" --> COST["EvalCostIntegral(α0,β0,α1,β1,...)\n计算每个解的代价 ∫‖r'''‖²du\n选最小代价的解"]

    COST --> BETA["Calc_beta0_beta1(α0,α1,...)\n由 α 线性方程组求 β0,β1\n（满足 G2 曲率约束的 β 值）"]

    BETA --> HERMB["Hermite 基函数合成系数:\nh00=[-6,15,-10,0,0,1]  （u=0 位置基）\nh01=[6,-15,10,0,0,0]    （u=1 位置基）\nh10=[-3,8,-6,0,1,0]     （u=0 切向基）\nh11=[-3,7,-4,0,0,0]     （u=1 切向基）\nh20=[-0.5,1.5,-1.5,0.5,0,0]（u=0 曲率基）\nh21=[0.5,-1,0.5,0,0,0]  （u=1 曲率基）\n\np5 = r0D0·h00 + α0·t0·h10 + (β0·t0+α0²·n0)·h20\n   + r1D0·h01 + α1·t1·h11 + (β1·t1+α1²·n1)·h21"]

    HERMB --> VER["验证: |p1val|<1e-7 且 |p2val|<1e-7\n（代入原方程组检验数值误差）"]
    VER -- "通过" --> OKOUT([status=1, 返回 p5])
    VER -- "失败" --> NUMFAIL([status=6, 数值误差])
```

---

## 9. 阶段 5：曲线分割（Split）

**入口**：`FeedoptPlan` case `Fopt.Split`  
**核心**：`splitQueue()` → `splitCurvStruct()` 逐条处理

### 9.1 splitCurvStruct 主流程

```mermaid
flowchart TD
    A["splitCurvStruct(ctx, curv)"] --> TP{"Type == TransP5?"}
    TP -- "是（过渡曲线已极短~0.2mm）" --> PUSHTP["q_split.push(curv)\n直接推入，不分割"]

    TP -- "否" --> ZS{"isAZeroStart(curv)?"}

    ZS -- "是" --> CZS["cutZeroStart(ctx, curv):\n① L = LengthCurv(curv)\n② Lcut = min(cfg.LSplitZero, L/3)\n③ cutCurvStruct(curv, isEnd=false, Lcut)\n   → curvS(ZN) + curv(余下主段)\n④ curvS.UseConstJerk = true\n⑤ zeroSpeedCurv(curvS, false) → curvS.ConstJerk\n⑥ q_split.push(curvS)"]

    CZS --> CZSRET{"ret < 0?\n（曲线过短，截取失败）"}
    CZSRET -- "是" --> EARLY([直接返回])
    CZSRET -- "否" --> ZE

    ZS -- "否" --> ZE{"isAZeroEnd(curv)?"}

    ZE -- "是" --> CZE["cutZeroEnd(ctx, curv):\n① Lcut = min(cfg.LSplitZero, L/3)\n② cutCurvStruct(curv, isEnd=true, Lcut)\n   → curv(主段) + curvE(NZ)\n③ curvE.UseConstJerk = true\n④ zeroSpeedCurv(curvE, true) → curvE.ConstJerk\n记录 hasEndSpeed=true"]

    CZE --> CZEOK{"ret < 0?"}
    CZEOK -- "是" --> EARLYZE["q_split.push(curv)\n返回"]
    CZEOK -- "否" --> SPLIT

    ZE -- "否" --> SPLIT

    SPLIT{"cfg.SplitSpecialSpline\n且 Type==Spline?"}

    SPLIT -- "是" --> BPT["B 样条断点分割:\nbspline.sp.Bl.breakpoints\n→ 筛选落在(uMin,uMax)内的内部断点\n→ 组合 [uMin, 内部断点, uMax]\n→ deltaU = diff(breakPoints)\n→ 逐段设 a_param=deltaU_j, b_param=uPrevious\n→ q_split.push(curvSplited)"]

    SPLIT -- "否（通用等弧长分割）" --> EQL["L = LengthCurv(ctx, curv, 0, 1)\nN = ceil(L / cfg.LSplit)\nL_split = L / N（精确均分）\n循环 k=1..N-1:\n  cutCurvStruct(curv, isEnd=false, L_split)\n  → curvSplited + curv（余下）\n  q_split.push(curvSplited)\nq_split.push(curv)（最后一段）"]

    BPT & EQL --> HASEND{"hasEndSpeed?"}
    HASEND -- "是" --> PUSHE["q_split.push(curvE)"]
    HASEND -- "否" --> DONE
    PUSHE --> DONE([下一条曲线])
```

### 9.2 恒定跃度速度曲线（constJerkU）

```mermaid
flowchart LR
    subgraph Forward["起始零速段（isEnd=false）"]
        F1["u(k) = jps · k³/6\nu'(k) = jps · k²/2\nu''(k) = jps · k\nu'''(k) = jps"]
        F2["k=0 → u=0（起点，零速）\nk=k_end=(6/jps)^(1/3) → u=1（终点）"]
        F1 & F2
    end

    subgraph Backward["终止零速段（isEnd=true）"]
        B1["时间反向:\nk_rev = k_max - k_vec\n先计算正向 u(k_rev)\n再翻转 u = 1 - u'\n加速度取反 u'' = -u''"]
        B2["k=0 → k_rev=k_max → u'=1 → u=0（起点）\nk=k_max → k_rev=0 → u'=0 → u=1（终点，零速）"]
        B1 & B2
    end

    subgraph Inverse["逆运算：constJerkTime"]
        INV["由 u 求 k:\nk = (6u/jps)^(1/3)\nisEnd=true 时先翻转 u=1-u\n再求 k = k_max - k"]
    end
```

---

## 10. 阶段 6：进给率优化（Opt）

**入口**：`FeedoptPlan` case `Fopt.Opt`（多次重入）  
**核心**：`feedratePlanning()` → 滑动窗口 + `FeedratePlanning_LP()`

### 10.1 滑动窗口主逻辑

```mermaid
flowchart TD
    A([进入 Opt\n首次 k0=1 kopt=1]) --> B{"q_split 为空?"}
    B -- "是" --> FIN([op=Finished, quit=true])

    B -- "否" --> C{"go_next=true?\n上次成功产出"}
    C -- "是" --> D["k0 = k0 + 1\n窗口游标前移"]
    C -- "否" --> E

    D --> E{"k0 <= q_split.size?"}
    E -- "否" --> FIN

    E -- "是" --> PATH{"ctx.zero_end?\n上一窗口已进入\n减速路径"}

    PATH -- "否（正常路径）" --> G1["feedratePlanningGetwindow(\n  k0, NHorz, q_split)\n→ window[1..NWindow]"]

    G1 --> G2["feedratePlanningSetupCurves(\n  ctx, window, NWindow)\n剥离首尾零速段:\n  if ZeroStart: window=window(2:end), NWindow-=1\n  if ZeroEnd:   window=window(1:end-1), NWindow-=1\n计算边界条件 v_0/at_0/v_1/at_1"]

    G2 --> G3["FeedratePlanning_LP(\n  ctx, window, amax, jmax,\n  BasisVal, BasisValD, BasisValDD,\n  BasisIntegr, u_vec, NWindow\n)\n→ Coeff, success"]

    G3 --> G4{"success?"}

    G4 -- "否，且非零速边界" --> FORCE["feedratePlanningForceZeroStop()\n① curv1.zspdmode = NZ\n② cutZeroEnd(curv1) → curv1NN + curv1NZ\n③ buffer[1] = curv1NZ\n④ q_split.set(ind1, curv1NN)\n⑤ curv2.zspdmode = ZN\n⑥ cutZeroStart(curv2) → curv2ZN + curv2NN\n⑦ buffer[2] = curv2ZN\n⑧ q_split.set(ind2, curv2NN)\n重新 GetWindow + SetupCurves"]
    FORCE --> G3

    G4 -- "是" --> DIST["分发结果:\nkopt=1\nopt_struct = q_split.get(k0)\nif ~ZeroStart:\n  opt_struct.Coeff = Coeff(:,kopt)\n  kopt++\nelse:\n  ctx.zero_start=false（消费零速起始标记）"]

    PATH -- "是（零速结束路径）" --> ZERO["从 ctx.Coeff 按序分发:\nopt_struct = q_split.get(k0)\nif ~ZeroEnd:\n  opt_struct.Coeff = ctx.Coeff(:,kopt)\nelse:\n  ctx.zero_end=false\nkopt++"]

    DIST & ZERO --> PUSH["q_opt.push(opt_struct)\nctx.go_next = true\n返回 optimized=true"]

    PUSH --> A
```

### 10.2 窗口边界条件建立（feedratePlanningSetupCurves）

```mermaid
flowchart TD
    subgraph IN["输入窗口（最多 NHorz 段）"]
        direction LR
        CS["first\nZN（零速起始）"] --> M1["middle1\nNN"] --> M2["middle2\nNN"] --> M3["...\nNN"] --> CE["last\nNZ（零速终止）"]
    end

    IN --> PROC

    subgraph PROC["处理逻辑"]
        P1{"first 是 ZeroStart?"}
        P1 -- "是" --> P1Y["ctx.zero_start = true\nwindow = window(2:end)\nNWindow -= 1"]
        P1 -- "否" --> P1N["ctx.zero_start = false"]

        P2{"last 是 ZeroEnd?"}
        P2 -- "是" --> P2Y["ctx.zero_end = true\nwindow = window(1:end-1)\nNWindow -= 1"]
        P2 -- "否" --> P2N["ctx.zero_end = false"]
    end

    PROC --> BC

    subgraph BC["边界条件计算"]
        BC1{"zero_start=true?"}
        BC1 -- "是" --> BC1Y["calcZeroConstraints(ctx, first, false)\n在 curvS 末端（连接处）求:\n  k = (6/jps)^(1/3) → u=1\n  [u,ud,udd,uddd] = constJerkU(jps,k,false)\n  [r0D,r1D,r2D,r3D] = EvalCurvStruct(curvS,u)\n  [v_0, at_0] = calcNormVNormAT(V,A,r1D)\nctx.v_0 = v_0\nctx.at_0 = at_0"]

        BC2{"zero_end=true?"}
        BC2 -- "是" --> BC2Y["calcZeroConstraints(ctx, last, true)\n在 curvE 起端（连接处）求:\n  k = 0 → 对应反向时间起点\n  [u,ud,udd,uddd] = constJerkU(jps,0,true)\n  [v_1, at_1] = calcNormVNormAT(...)\nctx.v_1 = -v_1（取负，适配约束形式）\nctx.at_1 = -at_1"]
        BC2 -- "否" --> BC2N["ctx.v_1 = -cfg.v_1（配置预设值）\nctx.at_1 = -cfg.at_1"]
    end
```

---

## 11. LP 约束矩阵构建详解

**入口**：`FeedratePlanning_LP()` → `buildConstr()` + `buildConstrJerk()`

### 11.1 LP 问题完整形式

```
决策变量：
  x = [w_1; w_2; ...; w_NWindow]   ∈ R^(N×NWindow)
  w_k(u) = BasisVal(u) · x_k ≈ v²(u)（第 k 段速度的平方）

  （实际求解时 x 会加上 slack 变量，防止不可行）

目标函数（最小化，等价于最大化 ∫v²du）：
  min  f^T · x = -BasisIntegr^T · x_k（各段求和）
  → 最大化速度积分 ≈ 最小化行程时间

第一阶段约束（速度 + 加速度）：
  不等式 A·x ≤ b：
    ①  BasisVal·x_k ≤ f_max(u)       速度上限 v² ≤ min(v_axis²/‖r'‖², F²/‖r'‖²)
    ② -BasisVal·x_k ≤ 0              速度非负 v² ≥ 0
    ③  Acc·x_k ≤ amax                各轴加速度上限（M×Ndim 个约束）
    ④ -Acc·x_k ≤ amax                各轴加速度下限
  等式 Aeq·x = beq：
    ⑤ v²(u=0 of w_1) = v_0²          起端速度条件
    ⑥ at(u=0 of w_1) = at_0          起端切向加速度条件
    ⑦ v²(u=1 of w_k) = v²(u=0 of w_{k+1})  段间速度连续
    ⑧ at(u=1 of w_k) = at(u=0 of w_{k+1})  段间加速度连续
    ⑨ v²(u=1 of w_NW) = v_1²         末端速度条件
    ⑩ at(u=1 of w_NW) = at_1         末端切向加速度条件

第二阶段约束（在第一阶段基础上添加跃度）：
  [r'''·BasisVal + 1.5·r''·BasisValD + 0.5·r'·BasisValDD]·x_k·v ≤ jmax
  （其中 v=sqrt(BasisVal·Coeff_phase1) 是线性化点，使约束关于 x 线性）
```

### 11.2 buildConstr 约束矩阵构建

```mermaid
flowchart TD
    A["buildConstr(ctx, windowCurv, amax,\n v_0, at_0, v_1, at_1, BasisVal, BasisValD, u_vec)"]

    A --> DIM["维度计算:\nNdim = NumberAxis（激活轴数）\nNwindow = len(windowCurv)\nM,N = size(BasisVal)\nNx = N×Nwindow\nNc = 2 + 2×Ndim（每点不等式数）\nNec = 2×(Nwindow+1)（等式约束数）"]

    DIM --> ALLOC["预分配矩阵:\nA   [Nc×M×Nwindow,  Nx]  不等式约束\nb   [Nc×M×Nwindow,  1 ]\nAeq [Nec, Nx]             等式约束\nbeq [Nec, 1]"]

    ALLOC --> LOOP["for k=1..Nwindow"]

    LOOP --> EVAL["EvalCurvStruct(windowCurv(k), u_vec)\n→ r0D, r1D, r2D, r3D"]

    EVAL --> KIN{"TRAFO=true?"}
    KIN -- "是（5轴）" --> KIN5["ctx.kin.joint(r0D, r1D, r2D, r3D)\n笛卡尔→关节空间\n→ r1D_a（关节一阶导）\n→ r2D_a（关节二阶导）"]
    KIN -- "否" --> KIN3["ctx.kin.v_relative(r0D, r1D)\n→ r1D_r（相对速度，用于进给率约束）\nr1D_a = r1D（直接用于加速度约束）"]

    KIN5 & KIN3 --> VMAX["速度上限 f_max（取所有约束中最小值）:\n  轴速度约束: v_k_max² = (vmax_j/r1D_a_j)²\n  进给率约束: F²/‖r1D_r(CartAxes)‖²\n  f_max = min(所有约束) 逐点取最小"]

    VMAX --> ACC["加速度约束矩阵 Acc [M×Ndim, N]:\n对每轴 j:\n  Acc_j = r2D_a_j · BasisVal\n        + 0.5 · r1D_a_j · BasisValD"]

    ACC --> ASSMB["装配不等式约束块（第 k 段）:\n行 indAL = (k-1)×Nc×M + 1 : k×Nc×M\n列 indAC = (k-1)×N + 1 : k×N\nA(indAL, indAC) =\n  [  BasisVal  ]  → 速度上限\n  [ -BasisVal  ]  → 速度非负\n  [  Acc       ]  → 加速度上限\n  [ -Acc       ]  → 加速度下限\nb(indAL) = [f_max; 0; amax; amax]"]

    ASSMB --> CONT["连续性方程（等式约束）:\n起/末端切线向量 t = r1D(:,[1,end])/‖r1D‖\n起/末端 v²行 = ‖r1D([1,end])‖² × BasisVal([1,end],:)\n起/末端 at行 = t' × Acc([indAT_1,:]) / (...)\n\nAeq(indAEL, indAEC) += continuity × mask\nmask_continuity = [+1;+1;-1;-1]\n（前段末端+，后段起端-，差=0实现连续性）"]

    CONT --> NEXT["下一段"] --> LOOP

    LOOP -- 结束 --> BEQ["设置边界条件等式右端:\nbeq([1,2,end-1,end]) =\n  [v_0²; at_0; v_1²; at_1] × mask_continuity"]

    BEQ --> RAMP["约束斜坡（Ramp）:\n末尾段适当降低速度/加速度上限\n避免优化器在窗口末尾"超前"规划\nvel_ramp = linspace(1, VEL_RAMP_OVER_WINDOWS, M)\nacc_ramp = linspace(1, ACC_RAMP_OVER_WINDOWS, M)\nb = b .* ramp（逐元素乘以斜坡系数）"]

    RAMP --> OUT([返回 A, b, Aeq, beq, continuity])
```

### 11.3 两阶段 LP 求解流程

```mermaid
flowchart TD
    IN["FeedratePlanning_LP(ctx, window, amax, jmax,\n BasisVal, BasisValD, BasisValDD,\n BasisIntegr, u_vec, NWindow)"]

    IN --> SCALE["compute_scaling_matrix(ctx, CurvArray, N)\n按各段弧长计算缩放矩阵 D\n改善 LP 条件数（不同量级轴）\nDCon = D(1:N, 1:N)（单段缩放）"]

    SCALE --> OBJ["目标函数:\nf = -BasisIntegr（最大化速度积分）\nf = reshape(f' * D, [], NWindow)（应用缩放）"]

    OBJ --> C1["buildConstr(ctx, ...)\n构造速度+加速度约束\n→ A, b, Aeq, beq, continuity\n对约束矩阵应用缩放:\n  A = A*D, Aeq = Aeq*D\n  continuity = continuity*DCon"]

    C1 --> S1["add_slack(cfg.opt, f, A, b, Aeq, beq, [], LP)\n添加松弛变量（防止不可行）:\n  x_slack ≥ 0\n  f_slack = penalty（惩罚松弛）\n  A_slack = [A; I]（松弛影响所有约束）"]

    S1 --> LP1["solve_LP(fSlack, ASlack, bSlack,\n  AeqSlack, beqSlack, ctx, N, NWindow)\n调用 COIN-OR CLP（或 linprog）\n→ Coeff（N×NWindow 矩阵）, success"]

    LP1 --> R1{"第一阶段\nsuccess?"}
    R1 -- "否" --> FAIL([返回 success=false])

    R1 -- "是" --> JERK{"cfg.opt.USE_JERK_CONSTRAINTS?"}

    JERK -- "否" --> UPD["更新下一窗口起始边界:\nctx.v_0 = 从 Coeff 最后段末端提取\nctx.at_0 = 切向加速度\nctx.Coeff = Coeff"]

    JERK -- "是" --> RS["Coeff = D * Coeff\n反缩放（还原到物理空间）"]

    RS --> CJ["buildConstrJerk(ctx, CurvArray,\n  Coeff, jmax,\n  BasisVal, BasisValD, BasisValDD, u_vec)\n基于第一阶段解线性化跃度约束:\n  v = sqrt(BasisVal × Coeff(:,k))（当前速度，视为已知）\n  Jerk_j = [r'''_j·BasisVal + 1.5r''_j·BasisValD\n           + 0.5r'_j·BasisValDD] × v\n  Aj[indAL, indAC] = [Jerk; -Jerk]\n  bj[indAL] = [jmax; jmax]"]

    CJ --> S2["add_slack()\n再次添加松弛变量"]

    S2 --> LP2["solve_LP()\n第二阶段 LP\n（速度+加速度+跃度联合约束）"]

    LP2 --> R2{"第二阶段\nsuccess?"}
    R2 -- "否" --> FAIL
    R2 -- "是" --> UPD

    UPD --> OK([返回 Coeff, success=true])
```

---

## 12. 曲线截取子系统（cutCurvStruct）

### 12.1 cutCurvStruct 核心逻辑

```mermaid
flowchart TD
    A["cutCurvStruct(ctx, curv, u0, L, isEnd)\n在弧长 L 处截取曲线，只更新参数窗口，不重新拟合几何"]

    A --> U["cutCurvStructU(ctx, curv, u0, L, isEnd)\n求截点的全局参数 u_tilda"]

    U --> TYPE{"curv.Info.Type?"}

    TYPE -- "Spline" --> SP["splineLengthFindU(\n  cfg, spline, L,\n  a*u0+b,   ← 全局参数起点\n  isEnd\n)\n→ u_tilda（二分法弧长反演）"]

    TYPE -- "Line / Helix\n（弧长均匀）" --> LH{"isEnd?"}
    LH -- "false（从起端截）" --> LH0["EvalCurvStruct(curv, 0) → r1D0\nΔu = L / ‖r1D0‖\nu_local = u0 + Δu\nu_tilda = a*u_local + b"]
    LH -- "true（从末端截）" --> LH1["EvalCurvStruct(curv, 1) → r1D1\nΔu = L / ‖r1D1‖\nu_local = u0 - Δu\nu_tilda = a*u_local + b"]

    SP & LH0 & LH1 --> CHK{"u_tilda ≤ 0?\n（截取失败）"}
    CHK -- "是" --> FAIL([ret=-1, 失败])

    CHK -- "否" --> RIGHT["构造右半段 curvRight:\n  b_param = u_tilda\n  a_param = a+b - u_tilda\n  zspdmode:\n    isAZeroEnd? → NZ（保留末端零速）\n              : → NN（两端普通）"]

    RIGHT --> LEFT["构造左半段 curvLeft:\n  a_param = u_tilda - b（原起点）\n  b_param 不变（与原曲线相同）\n  zspdmode:\n    isAZeroStart? → ZN（保留起端零速）\n                : → NN"]

    LEFT --> VALID["checkParametrisation(curvLeft)\ncheckParametrisation(curvRight)\n验证参数窗口合法"]
    VALID --> OUT([ret=0, curvLeft, curvRight])

    subgraph WHY["为何只更新参数窗口？"]
        W1["B 样条/圆弧/直线的几何数据\n（控制点/圆心/方向向量）\n是原始完整曲线的属性"]
        W2["子段只记录'我在原始曲线的哪一段'\n求值时通过 a_param/b_param 映射\n到正确的全局参数区间"]
        W3["无需复制或重新拟合几何数据\n节省内存，计算量 O(1)"]
    end
```

### 12.2 splineLengthFindU 弧长反演（二分法）

```mermaid
flowchart TD
    A["splineLengthFindU(cfg, spline, L, u0, isEnd)"]

    A --> ISO{"isEnd=true?"}
    ISO -- "是" --> MIR["镜像翻转（还原为正向截取）:\nu0 = 1 - u0\nKnots = flip(1 - Knots)\nLk = flip(Lk)"]
    ISO -- "否" --> PHASE1

    MIR --> PHASE1

    PHASE1["── 阶段1：粗查 O(K) ──"]
    
    PHASE1 --> K1["kStart = 最后一个 ≤ u0 的节点区间索引"]
    K1 --> K2{"Knots(kStart) < u0?"}
    K2 -- "是" --> K2Y["LStart = splineLengthApprox_Interval(\n  cfg, spline,\n  Knots(kStart), u0\n)\n（u0 在区间中间，需减去起始弧长）"]
    K2 -- "否" --> K2N["LStart = 0（u0 恰在节点处）"]

    K2Y & K2N --> K3["LEnd = cumsum(Lk(kStart:end)) - LStart\n（从 u0 出发的累积弧长）"]

    K3 --> K4["LkEnd = first(LEnd ≥ L)\n找第一个累积弧长超过 L 的区间"]

    K4 --> K5{"找到?"}
    K5 -- "否" --> NFAIL([u=-1，L超过剩余总长])

    K5 -- "是" --> K6["目标区间 [uLeft, uRight]:\n  uLeft  = Knots(kStart+LkEnd-1)\n  uRight = Knots(kStart+LkEnd)\n  LDiff  = L - LEnd(LkEnd-1)（区间内还需走的弧长）"]

    K6 --> PHASE2["── 阶段2：区间内二分法 O(log(1/tol)) ──"]

    PHASE2 --> BIS["bisection():\n  容差 tol=1e-7\n  最大迭代 1000 次\n  每步:\n    u_mid = (uLeft+uRight)/2\n    L_mid = splineLengthApprox_Interval(\n              cfg, spline, uLeft, u_mid\n            ) （GL-5 积分）\n    L_mid ≥ LDiff? → uRight=u_mid\n                  : → uLeft=u_mid\n  收敛后 u = (uLeft+uRight)/2"]

    BIS --> ISO2{"isEnd=true（原始）?"}
    ISO2 -- "是" --> FLIP["u = 1 - u（还原到原始坐标）"]
    ISO2 -- "否" --> DONE
    FLIP --> DONE([返回 u])
```

### 12.3 GL-5 Gauss-Legendre 积分（splineLengthApprox_Interval）

```
目标：计算 ∫[u0,u1] ‖r'(u)‖ du（弧长）

Gauss-Legendre 5 点公式：
  积分区间变换 [-1,1] → [u0,u1]：
    u(ξ) = (u0·(1-ξ) + u1·(1+ξ)) / 2

  GL 节点 GL_X = [x1, x2, x3, x4, x5]（5 个高斯点）
  GL 权重 GL_W = [w1, w2, w3, w4, w5]（对应权重）

  uvec = (u0*(1-GL_X) + u1*(1+GL_X)) / 2
  Integrand = ‖r'(uvec)‖（在 5 个积分点处求曲线速度范数）
  L = sum(Integrand .* GL_W) × (u1-u0)/2

精度：O(h^10)（GL-5 在光滑函数上精度极高）
```

---

## 13. 曲线求值子系统（EvalCurvStruct）

```mermaid
flowchart TD
    A["EvalCurvStruct(ctx, curv, u_vec)\n= EvalCurvStructNoCtx(cfg, curv, spline, u_vec)"]

    A --> MAP["参数映射:\na = curv.a_param\nb = curv.b_param\nu_g = a × u_vec + b  （局部→全局参数）\n验证: u_g ∈ [0,1]"]

    MAP --> SW{"curv.Info.Type"}

    subgraph LINE["Line: r(u) = P0(1-u) + P1·u"]
        L0["P0 = R0(maskTot)\nP1 = R1(maskTot)"]
        L1["r0D = P1·u_g + P0·(1-u_g)  [NDim×M]"]
        L2["r1D = repmat(P1-P0, 1, M)   常向量"]
        L3["r2D = zeros(NDim, M)\nr3D = zeros(NDim, M)"]
        L0 --> L1 --> L2 --> L3
    end

    subgraph HELIX["Helix（圆弧/螺旋线）"]
        H0["P0=R0(maskCart), C=CorrectedHelixCenter\nCP0 = P0-C, EcrCP0 = ê×CP0\nφ = θ·u_g"]
        H1["r0D = C + cos(φ)·CP0 + sin(φ)·(ê×CP0) + (p/2π)·φ·ê"]
        H2["r1D = θ·[-sin(φ)·CP0 + cos(φ)·(ê×CP0)] + θ(p/2π)·ê"]
        H3["r2D = -θ²·[cos(φ)·CP0 + sin(φ)·(ê×CP0)]"]
        H4["r3D = θ³·[sin(φ)·CP0 - cos(φ)·(ê×CP0)]"]
        HROT["旋转轴（maskRot）:\nEvalLine(旋转轴线性同步)"]
        H0 --> H1 --> H2 --> H3 --> H4
    end

    subgraph TRANSP5["TransP5（五次多项式）"]
        T0["p5 = CoeffP5  [NDim×6]\np5_1D = mypolyder(p5)   [NDim×5]\np5_2D = mypolyder(p5_1D)[NDim×4]\np5_3D = mypolyder(p5_2D)[NDim×3]"]
        T1["D0 = mypolyval(p5,    u_g)  位置\nD1 = mypolyval(p5_1D, u_g)  一阶导\nD2 = mypolyval(p5_2D, u_g)  二阶导\nD3 = mypolyval(p5_3D, u_g)  三阶导"]
        T2["r0D = D0(maskTot,:)\n...（掩码筛选激活轴）"]
        T0 --> T1 --> T2
    end

    subgraph SPLINE["Spline（B 样条）"]
        S0["spline = q_spline.get(sp_index)\nbspline_eval_vec(spline, u_g)\n→ 调用 GSL 库计算基函数"]
        S1["r0D = 位置（0阶）\nr1D = 一阶导\nr2D = 二阶导\nr3D = 三阶导"]
        S0 --> S1
    end

    SW -- "Line"    --> LINE
    SW -- "Helix"   --> HELIX
    SW -- "TransP5" --> TRANSP5
    SW -- "Spline"  --> SPLINE

    LINE & HELIX & TRANSP5 & SPLINE --> CHAIN["链式法则补偿:\n底层返回的是 d/du_g（全局参数导数）\n转换为 d/du_l（局部参数导数）：\n  r1D = a × r1D    （×a）\n  r2D = a² × r2D   （×a²）\n  r3D = a³ × r3D   （×a³）\n因为 u_g = a·u_l+b → du_g/du_l = a"]

    CHAIN --> OUT["输出:\nr0D [NDim×M]  位置（各轴）\nr1D [NDim×M]  一阶参数导数\nr2D [NDim×M]  二阶参数导数\nr3D [NDim×M]  三阶参数导数"]
```

---

## 14. 弧长计算子系统

**入口**：`LengthCurv(ctx, curv, u0, u1)` → 按类型分发

```mermaid
flowchart TD
    A["LengthCurv(ctx, curv, u0, u1)"]

    A --> SW{"curv.Info.Type"}

    SW -- "Line" --> LL["弧长均匀性：‖r'‖ = ‖P1-P0‖ = 常数\n[~, r1D] = EvalCurvStruct(curv, u0)\nL = ‖r1D‖ × (u1-u0)\nO(1)，解析计算"]

    SW -- "Helix" --> LH["弧长均匀性：‖r'‖ = √(θ²R² + (θp/2π)²) = 常数\n[~, r1D] = EvalCurvStruct(curv, u0)\nL = ‖r1D‖ × (u1-u0)\nO(1)，解析计算"]

    SW -- "Spline" --> LSP["splineLength(cfg, spline, u0, u1)\n'两端GL，中间查表'策略:\n  u0..u1 跨越若干节点区间\n  边界区间用 GL-5 精确积分\n  中间完整区间从 sp.Lk 累加\n  O(K+1)（K=跨越区间数）"]

    SW -- "TransP5" --> LTP["TransP5LengthApprox(CurvStruct, u0, u1)\n中点积分法（9 个子区间）:\n  u_mid_k = 各子区间中点\n  Δu = (u1-u0)/9\n  L = Σ ‖p5'(u_mid_k)‖ × Δu\nO(9)，固定代价"]

    subgraph splineLength["splineLength 详细策略"]
        SL1["① 确定 u0 所在的节点区间 kStart\n   u1 所在的节点区间 kEnd"]
        SL2["② 起始区间（不完整）:\n   L_start = GL-5积分(Knots[kStart], u0..u0_end)"]
        SL3["③ 终止区间（不完整）:\n   L_end = GL-5积分(Knots[kEnd], u1_start..u1)"]
        SL4["④ 中间完整区间:\n   L_mid = sum(sp.Lk[kStart:kEnd-1])\n   sp.Lk 是 SplineLengthApproxGL_tot\n   预计算的各区间弧长"]
        SL5["L = L_mid - L_start - L_end"]
        SL1 --> SL2 --> SL3 --> SL4 --> SL5
    end
```

---

## 15. 关键参数速查表

### 15.1 配置参数（FeedoptDefaultConfig）

| 参数名 | 含义 | 单位 | 典型值 |
|--------|------|------|--------|
| `LSplit` | 等弧长分割的目标段长 | mm | 5–20 |
| `LSplitZero` | 零速段切出长度 | mm | 0.5–2 |
| `NHorz` | 滑动窗口曲线数量 | 段 | 10–30 |
| `NBreak` | B 样条基函数断点数 | — | 5–10 |
| `NDiscr` | 离散化参数点数（= M） | — | 20–50 |
| `SplineDegree` | 进给率 B 样条次数 | — | 3（三次） |
| `CutOff` | 过渡曲线截取半长 | mm | 0.05–0.2 |
| `ColTolSmooth` | 平滑阶段位置/曲率公差 | mm | 1e-4 |
| `ColTolCosSmooth` | 平滑阶段切向余弦阈值 | — | cos(0.1°)≈0.99999 |
| `ColTolCosLee` | 压缩阶段共线余弦阈值 | — | cos(2°)≈0.9994 |
| `LThresholdMax` | 批次直线段最大长度 | mm | 0.5–5 |
| `amax` | 各轴加速度上限 | mm/s² | 配置 |
| `jmax` | 各轴跃度上限 | mm/s³ | 配置 |
| `vmax` | 各轴速度上限 | mm/s | 配置 |
| `VEL_RAMP_OVER_WINDOWS` | 窗口末尾速度斜坡系数 | — | 0.7–1.0 |
| `ACC_RAMP_OVER_WINDOWS` | 窗口末尾加速度斜坡系数 | — | 0.7–1.0 |
| `SLACK_PENALTY` | 松弛变量惩罚系数 | — | 1e6 |
| `USE_JERK_CONSTRAINTS` | 是否启用两阶段跃度约束 | bool | true |

### 15.2 各阶段数据量估算（示例：1000 段 G-Code）

| 阶段 | 输入曲线数 | 输出曲线数 | 说明 |
|------|-----------|-----------|------|
| GCode | — | ~1000 | 原始 G-Code 段数 |
| Check | ~1000 | ~1050 | 尖点处可能插入额外零速停顿 |
| Compress | ~1050 | ~200 | 共线短直线批次合并为 B 样条 |
| Smooth | ~200 | ~300 | 每个不连续处插入 curv1C+curvT（+1~2段） |
| Split | ~300 | ~3000 | 每段按 LSplit=10mm 分割（若平均 100mm） |
| Opt | ~3000 | ~3000 | 每段加上 Coeff（进给率系数） |

---

## 16. 完整函数调用树

```
FeedoptPlanRun(ctx)
└── while ctx.op != Finished
    └── [try] FeedoptPlan(ctx)
        │
        ├── [Init] → ctx.op = GCode
        │
        ├── [GCode]
        │   ├── ReadGCode(Load, 文件)        rs274ngc 解释器初始化
        │   ├── ReadGCode(Read)              逐条读取 → CurvStruct
        │   ├── toolIsEqual(prev, cur)       换刀检测
        │   ├── add_tool_offset(CurvStruct)  刀具长度补偿
        │   ├── deg2rad(R0/R1[4:end])        旋转轴单位转换
        │   └── assert_queue(q_gcode)
        │       ├── checkGeometry(q)
        │       ├── checkZSpdmode(ctx, q)
        │       └── checkParametrisationQueue(q)
        │           └── checkParametrisation(curv)   [每段]
        │
        ├── [Check]
        │   └── CheckCurvStructs(ctx)
        │       ├── EvalCurvStruct(curv_k, 1)   末端导数
        │       ├── EvalCurvStruct(curv_{k+1}, 0) 起端导数
        │       └── iscusp(r1D_k, r1D_{k+1})   夹角检测
        │
        ├── [Compress]
        │   └── compressCurvStructs(ctx)
        │       ├── batch_init()
        │       ├── check_add_batch(ctx, curv)   准入判断
        │       ├── check_close_batch(ctx, batch, curv, addBatch) 关闭判断
        │       ├── batch_close(ctx, batch, spline_index)
        │       │   └── CalcBspline_Lee(batch)
        │       │       ├── （1/4幂参数化）
        │       │       ├── bspline_create(degree, knots)
        │       │       └── tridiag(B, R)              Thomas 算法
        │       └── batch_add_curv(batch, curv)
        │
        ├── [Smooth]
        │   └── smoothCurvStructs(ctx)
        │       ├── check_stop_and_transition(ctx, curv, nextCurv, ...)
        │       │   ├── isAZeroEnd(curv)
        │       │   ├── isAZeroStart(nextCurv)         [b_param 检查]
        │       │   └── check_smoothness(ctx, curv, nextCurv, ...)
        │       │       ├── EvalCurvStruct(curv0, 1)
        │       │       ├── EvalCurvStruct(curv1, 0)
        │       │       ├── calc_t_nk_kappa(r1D, r2D)
        │       │       └── collinear(t1, t2, tol_cos)
        │       ├── calcTransition(ctx, curv, nextCurv)
        │       │   ├── LengthCurv(ctx, curv, 0, 1)  [两段]
        │       │   ├── cutCurvStruct(curv1, isEnd=false, L1-CutOff)
        │       │   ├── cutCurvStruct(curv2, isEnd=true, L2-CutOff)
        │       │   ├── EvalCurvStruct(curv1C, 1)
        │       │   ├── EvalCurvStruct(curv2C, 0)
        │       │   ├── G2_Hermite_Interpolation_nAxis(...)
        │       │   │   ├── calc_t_nk_kappa(r0D1, r0D2)    [两端]
        │       │   │   ├── CoefPolySys(r0D0, t0, n0, ...)  16系数
        │       │   │   ├── [kappa=0∧kappa=0] M\B
        │       │   │   ├── [kappa0=0]        c_roots_(3次)
        │       │   │   ├── [kappa1=0]        c_roots_(3次)
        │       │   │   ├── [一般]            CharPolyAlpha1() → c_roots_(9次)
        │       │   │   │                     CalcAlpha0()
        │       │   │   ├── [多解]            EvalCostIntegral() → 取最优
        │       │   │   └── Calc_beta0_beta1() + Hermite基合成 p5
        │       │   ├── constrTransP5Struct(...)    构造 curvT
        │       │   └── check_continuity(curv1C, curvT)  [+curvT,curv2C]
        │       ├── create_zero_end(curv, nextCurv)  [失败时]
        │       └── add_zero_stop(ctx, curv, nextCurv)
        │
        ├── [Split]
        │   └── splitQueue(ctx)
        │       └── splitCurvStruct(ctx, curv)  [每段]
        │           ├── cutZeroStart(ctx, curv)
        │           │   ├── LengthCurv(...)
        │           │   ├── cutCurvStruct(curv, isEnd=false, Lcut)
        │           │   │   └── cutCurvStructU(...)
        │           │   │       └── [Spline] splineLengthFindU(...)
        │           │   │           ├── splineLengthApprox_Interval(...)×多次
        │           │   │           └── bisection(...)  ←GL-5积分
        │           │   │       └── [Line/Helix] Δu=L/‖r'‖
        │           │   └── zeroSpeedCurv(ctx, curvS, false) → ConstJerk
        │           ├── cutZeroEnd(ctx, curv)       [对称逻辑]
        │           └── [等弧长] cutCurvStruct(curv, ...) × N-1次
        │
        └── [Opt]
            └── feedratePlanning(ctx)
                ├── feedratePlanningGetwindow(k0, NHorz, q_split)
                ├── feedratePlanningSetupCurves(ctx, window, NWindow)
                │   └── calcZeroConstraints(ctx, first/last, isEnd)
                │       ├── constJerkU(jps, k, isEnd, true)
                │       ├── EvalCurvStruct(ctx, curv, u)
                │       ├── calcRVAJfromUWithoutCurv(ud,udd,uddd,r0D,r1D,r2D,r3D)
                │       └── calcNormVNormAT(V, A, r1D)
                ├── FeedratePlanning_LP(ctx, window, amax, jmax, ...)
                │   ├── compute_scaling_matrix(ctx, CurvArray, N)
                │   ├── buildConstr(ctx, window, amax, v_0, at_0, v_1, at_1, ...)
                │   │   └── EvalCurvStruct(ctx, windowCurv(k), u_vec)  [每段]
                │   │       └── ctx.kin.joint() / ctx.kin.v_relative()
                │   ├── add_slack(cfg.opt, f, A, b, Aeq, beq, ...)
                │   ├── solve_LP(fSlack, ASlack, bSlack, AeqSlack, beqSlack, ...)
                │   │   └── c_simplex(...)  COIN-OR CLP 调用
                │   ├── [USE_JERK] buildConstrJerk(ctx, CurvArray, Coeff, jmax, ...)
                │   │             └── EvalCurvStruct(ctx, windowCurv(k), u_vec)
                │   └── solve_LP(...)    第二阶段
                └── feedratePlanningForceZeroStop(ctx, window, NWindow)
                    ├── cutZeroEnd(ctx, curv1)
                    ├── cutZeroStart(ctx, curv2)
                    ├── feedratePlanningGetwindow(...)
                    └── feedratePlanningSetupCurves(...)
```
