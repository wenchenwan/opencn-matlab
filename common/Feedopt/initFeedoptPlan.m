function [ ctx ] = initFeedoptPlan( cfg )
%#codegen
% initFeedoptPlan : 初始化计算链上下文 ctx
% 这是进入 FeedoptPlanRun 前必须调用的准备函数，负责：
%   1. 创建 B 样条基并预计算基函数值（避免优化循环中重复计算）
%   2. 初始化所有阶段的曲线队列（6 个队列）
%   3. 初始化运动学对象
%   4. 设置 FSM 初始状态和所有控制变量
%
% Inputs :
%   cfg : 配置结构体（由 FeedoptDefaultConfig 创建并由用户修改）
%
% Outputs :
%   ctx : 初始化完成的上下文结构体
%

coder.inline("never");

% -------------------------------------------------------------------------
% 第一步：创建 B 样条基（优化中用于表示进给率 v²(u)）
% -------------------------------------------------------------------------
if cfg.UseLinearBreakpoints
    % 均匀断点分布：适合大多数场景
    Bl      = bspline_create( cfg.SplineDegree, linspace( 0, 1, cfg.NBreak ) );
    u_vec   = linspace( 0, 1, cfg.NDiscr );
else
    % 正弦空间断点（两端密中间疏）：适合加减速密集的场景
    Bl      = bspline_create( cfg.SplineDegree, sinspace( 0, 1, cfg.NBreak ) );
    u_vec   = sinspace( 0, 1, cfg.NDiscr );
end

% 预计算 B 样条基函数在 u_vec 处的值及各阶导数
% 这些矩阵在每次 LP 求解时都会用到，提前计算可大幅减少重复计算量
[ BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr] = ...
                                    bspline_base_eval( Bl , u_vec );

% 存入上下文（LP 求解时作为常量输入）
ctx.BasisVal            = BasisVal;     % [M×N] B 样条基在 u_vec 的值
ctx.BasisValD           = BasisValD;    % [M×N] 一阶导
ctx.BasisValDD          = BasisValDD;   % [M×N] 二阶导（跃度约束用）
ctx.BasisValDDD         = BasisValDDD;  % [M×N] 三阶导（备用）
ctx.BasisIntegr         = BasisIntegr;  % [N×1] 各基函数在 [0,1] 上的积分（目标函数用）
ctx.Bl                  = Bl;           % B 样条基结构体（含断点、阶次）
ctx.u_vec               = u_vec;        % [1×M] 离散化参数点

% -------------------------------------------------------------------------
% 第二步：初始化六个阶段队列（存储各阶段处理后的曲线段）
% -------------------------------------------------------------------------
Curv                    = constrCurvStructType; % 默认空曲线（作为队列元素类型模板）
ctx.q_spline            = queue( Curv ); % B 样条参数队列（压缩阶段的 spline 数据）
ctx.q_gcode             = queue( Curv ); % G-code 解析结果队列
ctx.q_compress          = queue( Curv ); % 压缩后的曲线队列
ctx.q_smooth            = queue( Curv ); % 平滑（加过渡）后的队列
ctx.q_split             = queue( Curv ); % 分割后的短段队列
ctx.q_opt               = queue( Curv ); % 优化结果队列（最终输出）

% -------------------------------------------------------------------------
% 第三步：FSM 控制变量初始化
% -------------------------------------------------------------------------
ctx.op                  = Fopt.Init;    % 当前 FSM 状态，从 Init 开始
ctx.go_next             = false;        % 是否在下一步推进游标 k0
ctx.try_push_again      = false;        % 已废弃标记（历史遗留，不再使用）
ctx.n_optimized         = int32( 0 );   % 已优化的曲线段总计数
ctx.reached_end         = false;        % 是否已处理到 q_split 末尾

% -------------------------------------------------------------------------
% 第四步：优化游标和边界条件
% -------------------------------------------------------------------------
ctx.k0                  = int32( 1 );   % 当前处理的曲线段索引（指向 q_split）
ctx.v_0                 = cfg.v_0;      % 窗口起始速度（从配置中读取，通常为 0）
ctx.v_1                 = cfg.v_1;      % 窗口末端速度（通常为 0）
ctx.at_0                = cfg.at_0;     % 窗口起始切向加速度
ctx.at_1                = cfg.at_1;     % 窗口末端切向加速度

% -------------------------------------------------------------------------
% 第五步：配置和其他运行时变量
% -------------------------------------------------------------------------
ctx.cfg                 = cfg;          % 完整配置结构体
ctx.jmax_increase_count = int32(0);     % 跃度上限被放大的累计次数

% -------------------------------------------------------------------------
% 第六步：零速相关状态标记
% -------------------------------------------------------------------------
ctx.zero_start          = false;        % 当前处理的曲线段是否有零速起始
ctx.zero_end            = false;        % 当前处理的曲线段是否有零速结束
ctx.zero_forced         = false;        % 是否强制插入了零速停止
ctx.zero_forced_buffer  = [ Curv, Curv ]; % 强制零速时的备用曲线缓冲（前后各一段）

% -------------------------------------------------------------------------
% 第七步：其他历史/统计变量
% -------------------------------------------------------------------------
ctx.simplex_calls       = int32(0);     % LP 求解器调用次数（已废弃，历史遗留）
ctx.forced_stop         = int32(0);     % 强制停止计数（用途不明，历史遗留）
ctx.programmed_stop     = int32(0);     % G-code 中编程停止（M00/M01）的计数
ctx.Coeff               = zeros( 1, 1 ); % LP 优化系数（动态分配，初始化为标量）
ctx.Skipped             = int32(0);     % 被跳过的段计数（用途不明，历史遗留）

% -------------------------------------------------------------------------
% 第八步：运动学对象（封装正/逆运动学变换）
% -------------------------------------------------------------------------
ctx.kin                 = Kinematics( cfg.kin_type, cfg.kin_params );

% -------------------------------------------------------------------------
% 第九步：错误处理
% -------------------------------------------------------------------------
Curv.Info.Type          = CurveType.Spline; % q_spline 中存放 Spline 类型曲线
Curv.sp.Bl              = Bl;               % 关联 B 样条基
ctx.errmsg              = constrMsgStructType; % 错误消息结构体
ctx.errcode             = FeedoptPlanError.NoError; % 初始无错误

% -------------------------------------------------------------------------
% 代码生成：声明可变尺寸字段（供 MATLAB Coder 生成 C 代码时使用）
% -------------------------------------------------------------------------
if ~coder.target('matlab')
    coder.varsize( 'ctx.cfg.indCart',       StructTypeName.dimInd{ : } );
    coder.varsize( 'ctx.cfg.indRot',        StructTypeName.dimInd{ : } );
    coder.varsize( 'ctx.cfg.maskTot',       StructTypeName.dimMask{ : } );
    coder.varsize( 'ctx.cfg.maskCart',      StructTypeName.dimMask{ : } );
    coder.varsize( 'ctx.cfg.maskRot',       StructTypeName.dimMask{ : } );
    coder.varsize( 'ctx.cfg.D',             StructTypeName.dimD{ : } );
    coder.varsize( 'ctx.cfg.source',        StructTypeName.dimFileName{ : } );
    coder.varsize( 'ctx.cfg.kin_params',    StructTypeName.dimKinParams{ : } );
    coder.cstructname( ctx.cfg,             StructTypeName.FeedoptCfg );
    coder.varsize( 'ctx.BasisVal',          StructTypeName.dimBasis{ : } );
    coder.varsize( 'ctx.BasisValD',         StructTypeName.dimBasis{ : } );
    coder.varsize( 'ctx.BasisValDD',        StructTypeName.dimBasis{ : } );
    coder.varsize( 'ctx.BasisIntegr',       StructTypeName.dimBasisInt{ : } );
    coder.varsize( 'ctx.u_vec',             StructTypeName.dimCtxUvec{ : } );
    coder.varsize( 'ctx.Bl.breakpoints',    StructTypeName.dimCtxBlBreaks{ : } );
    coder.varsize( 'ctx.Coeff',             StructTypeName.dimCtxCoeff{ : } );
    coder.cstructname(ctx, StructTypeName.FeedoptCtx );
end

% 将初始 Spline 曲线推入 q_spline（作为第一个 B 样条占位）
ctx.q_spline.push( Curv );

end
