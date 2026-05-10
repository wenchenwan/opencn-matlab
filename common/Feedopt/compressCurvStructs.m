function [ ctx ] = compressCurvStructs( ctx )
% compressCurvStructs : 曲线压缩阶段
% 读取 q_gcode，将连续的短直线段合并为 B 样条曲线，写入 q_compress。
%
% 压缩策略（批次 batch 机制）：
%   将满足条件的连续直线段收集到一个 batch 中：
%     - 曲线类型必须是直线（Line）
%     - 长度不超过 LThresholdMax
%     - 与前一段共线（cos 角度阈值：ColTolCosLee）
%     - 机床参数相同（进给率、主轴转速等）
%     - 没有零速要求（isAZeroStart == false）
%   batch 关闭时，若超过 1 段，则用 Lee 算法拟合 B 样条；否则直接透传。
%
% Inputs :  ctx : 计算链上下文
% Outputs : ctx : 更新后的上下文（q_compress 和 q_spline 已填充）
%

if ctx.q_gcode.isempty(), return; end

spline_index        = ctx.q_spline.size() + 1;  % q_spline 中新样条的起始索引
Ncrv                = ctx.q_gcode.size;          % 待处理的曲线总数
[ batch ]           = batch_init();              % 初始化空批次

DebugLog( DebugCfg.Validate, 'Compressing...\n' );

ctx.k0 = int32( 1 ); % 重置曲线计数器

for k = 1 : Ncrv

    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + Ncrv, mfilename );
    curv = ctx.q_gcode.get( k ); % 取第 k 条曲线

    % 判断：当前曲线是否可以加入批次
    [ addBatch ]    = check_add_batch( ctx, curv );
    % 判断：当前批次是否需要关闭（输出已收集的曲线）
    [ closeBatch ]  = check_close_batch( ctx, batch, curv, addBatch);

    if( closeBatch )
        % 关闭批次：生成 B 样条或直接推送单曲线
        [ ctx, batch, spline_index ] = batch_close( ctx, batch, spline_index );
    end

    if( addBatch )
        [ batch ] = batch_add_curv( batch, curv ); % 将曲线加入批次
    else
        ctx.q_compress.push( curv ); % 不可压缩（弧线等），直接透传
    end
    ctx.k0 = ctx.k0 + 1;
end

% 处理最后一个未关闭的批次
[ ctx ] = batch_close( ctx, batch, spline_index );

end

%-------------------------------------------------------------------------%
% 辅助函数
%-------------------------------------------------------------------------%

function [ addBatch ] = check_add_batch( ctx, curv )
% 判断曲线是否可以加入当前批次（两个必要条件）
if( coder.target( "MATLAB" ) ), coder.inline( "always" ); end

addBatch = true;

% 条件 1：只压缩直线段（Line），圆弧、螺旋线、样条直接排除
if( curv.Info.Type ~= CurveType.Line )
    if( coder.target( "MATLAB" ) ), DebugCompressing.getInstance.NotALineInc; end
    addBatch = false; return;
end
% 条件 2：线段长度不能超过 LThresholdMax（过长的线不值得压缩）
if( LengthCurv( ctx, curv, 0, 1 ) >  ctx.cfg.LThresholdMax )
    if( coder.target( "MATLAB" ) ), DebugCompressing.getInstance.TooLargeInc; end
    addBatch = false; return;
end

end

function [ closeBatch ] = check_close_batch( ctx, batch, curv, addBatch )
% 判断是否需要关闭当前批次（五个触发条件，任一满足即关闭）
if( coder.target( "MATLAB" ) ), coder.inline( "always" ); end

closeBatch = false;
if( batch.size == 0 ), return; end % 批次为空则无需关闭

% 条件 1：当前曲线不能加入批次（类型不符或过长）
if( ~addBatch )
    closeBatch = true;
end

% 条件 2：当前曲线有零速起始要求（如换刀、程序停止后重启）
if( isAZeroStart( curv ) )
    if( coder.target( "MATLAB" ) ), DebugCompressing.getInstance.IsAZeroStartInc; end
    closeBatch = true;
end

% 条件 3：机床参数发生变化（进给率/主轴转速不同，不能合并）
if( ~isSameMachiningParameters( batch.lastCurv, curv ) )
    if( coder.target( "MATLAB" ) ), DebugCompressing.getInstance.NotSameMachineParamsInc; end
    closeBatch = true;
end

% 条件 4：曲线太短（短于 LThresholdMin）则跳过共线检查，允许加入批次
if( LengthCurv( ctx, curv, 0, 1 ) <=  ctx.cfg.LThresholdMin )
    if( coder.target( "MATLAB" ) ), DebugCompressing.getInstance.IsReallySmallInc; end
    return; % 直接返回（closeBatch 保持上面的判断结果）
end

% 条件 5：与批次最后一段不共线（方向偏转角超过 ColTolCosLee 阈值）
collinear = curvCollinear( ctx, batch.lastCurv, curv, ...
    ctx.cfg.Compressing.ColTolCosLee );
if( ~collinear )
    if( coder.target( "MATLAB" ) ), DebugCompressing.getInstance.NotCollinearInc; end
    closeBatch = true;
end

end

function [ batch ] = batch_init()
% 初始化空批次结构体
batch = struct( ...
    'pvec',          zeros( StructTypeName.NumberAxisMax, 1 ),... % 控制点集合（列向量拼接），后续添加曲线段，会往后增加控制点
    'lastCurv',      constrCurvStructType,...                    % 批次中的最后一条曲线
    'size',          0, ...                                      % 批次中的曲线数量
    'zspdmode',      ZSpdMode.NN ...                             % 批次的零速模式继承自首曲线
    );

if( ~coder.target( "MATLAB" ) )
    coder.varsize( 'batch.pvec', StructTypeName.dimPvec{ : } );
end
end

function [ ctx, batch, spline_index ] = batch_close( ctx, batch, spline_index )
% 关闭批次：输出压缩结果到 q_compress
if( batch.size == 0 )
    batch = batch_init(); % 空批次直接重置
    return
end

if( batch.size > 1 )
    % 多段直线：用 Lee 算法拟合 B 样条，生成压缩后的曲线
    [ curvCompressed, spline, spline_index ] = ...
        create_spline( ctx, batch, spline_index );

    ctx.q_compress.push( curvCompressed ); % 推入压缩队列
    ctx.q_spline.push( spline );           % 推入 B 样条队列（供后续求值）

    if( coder.target( "MATLAB" ) )
        DebugCompressing.getInstance.addSplineBatch( curvCompressed, batch );
        DebugCompressing.getInstance.printSplineBatch( ctx, curvCompressed, batch );
    end

else
    % 单段直线：不值得压缩，直接透传
    ctx.q_compress.push( batch.lastCurv );
end

if( coder.target( "MATLAB" ) )
    DebugCompressing.getInstance.addBatch( batch.size, batch.zspdmode );
end

batch = batch_init(); % 重置批次，准备下一个
end

function [ batch ] = batch_add_curv( batch, curv )
% 将曲线加入批次，更新控制点集合和零速模式
%
% batch.zspdmode 的维护规则：
%   - 第一条曲线加入时，直接取其 zspdmode 作为批次初始值（携带起端零速信息）
%   - 后续曲线加入时，只在末端变为零速时才更新（保留起端，更新末端）
%   - 最终 batch.zspdmode 正确反映整批的起止零速状态：
%       起端：来自第一条曲线                （batch_add_curv 第一条时设定）
%       末端：若任一后续曲线为 ZeroEnd 则更新（isAZeroEnd 检测）
if( batch.size == 0 )
    % 第一条曲线：同时记录起点 R0 和终点 R1
    batch.pvec      = [ curv.R0, curv.R1 ];
    batch.lastCurv  = curv;
    batch.size      = 1;
    batch.zspdmode  = curv.Info.zspdmode;  % 起端零速状态由首曲线决定
else
    % 后续曲线：只追加终点 R1（起点与前一段终点重合，无需重复存储）
    batch.pvec      = [ batch.pvec, curv.R1 ];
    batch.lastCurv  = curv;
    batch.size      = batch.size + 1;
    % 动态更新末端零速：若当前曲线以零速结束，则更新批次末端标记
    % 起端标记保持不变（始终来自第一条曲线）
    if( isAZeroEnd( curv ) )
        if( isAZeroStart( batch.zspdmode ) )
            batch.zspdmode = ZSpdMode.ZZ; % 起止均零速
        else
            batch.zspdmode = ZSpdMode.NZ; % 仅末尾零速
        end
    end
end

end

function [ curv, spline, spline_index ] = create_spline( ctx, batch, spline_index )
% 用 Lee 算法对批次中的控制点序列拟合 B 样条

% ── 注入批次零速模式 ─────────────────────────────────────────────────────
% 问题根源：constrSplineStruct 从 batch.lastCurv.Info 取元信息，
%           但 lastCurv 是批次中最后一段，它的 zspdmode 只代表自身，
%           不知道第一段是否零速起步。
%
% 示例：
%   批次 3 条曲线：ZN → NN → NN
%     batch.lastCurv.Info.zspdmode = NN  （仅第3段自身状态）
%     batch.zspdmode               = ZN  （整批：起端零速来自第1段）
%   若不做此赋值 → 压缩样条得到 NN，起端零速信息丢失（错误）
%   做此赋值后  → 压缩样条得到 ZN，起止零速均正确（正确）
%
% batch.zspdmode 由 batch_add_curv 动态维护，到此处已正确表示整批状态：
%   起端：第一条曲线加入时设定
%   末端：后续有 ZeroEnd 曲线加入时更新
batch.lastCurv.Info.zspdmode = batch.zspdmode;

% 构造压缩后的曲线段（类型变为 Spline，起终点取批次首尾）
curv    = constrSplineStruct( ...
                              batch.lastCurv.Info, ...
                              batch.lastCurv.tool, ...
                              batch.pvec( :, 1 ), ...    % 起点（批次第一段 R0）
                              batch.pvec( :,end ), ...   % 终点（批次最后段 R1）
                              uint32( spline_index ) );

% 用 Lee 算法在激活轴（maskTot）上拟合 B 样条
spline          = curv;
spline.sp       = CalcBspline_Lee( ctx.cfg, batch.pvec( ctx.cfg.maskTot, : ) );
% 预计算弧长（用于后续进给率规划中的长度查询）
[ Ltot, Lk ]    = SplineLengthApproxGL_tot( ctx.cfg, spline );
spline.sp.Ltot  = Ltot;  % 总弧长
spline.sp.Lk    = Lk;    % 每段弧长分布
spline_index    = spline_index + 1; % 递增 B 样条索引
end
