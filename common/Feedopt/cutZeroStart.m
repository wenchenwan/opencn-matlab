function [ ret, curv1, curv2 ] = cutZeroStart( ctx, curv )
%#codegen
% cutZeroStart : 从曲线头部切出零速起始子段，并为其预计算恒定跃度速度曲线
%
% 【零速起始处理原理】
%   当曲线以零速开始（ZeroStart），需要在起点附近规划一段"加速区"：
%   加速区弧长 = Lcut（由 cfg.LSplitZero 给出，不超过总长的 1/3）。
%   加速区子段 curv1 标记为 UseConstJerk=true，优化阶段将用解析的
%   恒定跃度（常数 jerk）速度曲线代替 LP 规划，以精确处理零初速边界。
%
%   切割结果（正常情况）：
%     curv1 [0 → Lcut]  UseConstJerk=true，zspdmode=ZN（零速起、普通止）
%     curv2 [Lcut → L]  UseConstJerk=false，后续按常规分割优化
%
%   切割失败（曲线总长 < 3×Lcut，即 Lcut 被夹到 L/3 后仍切割失败）：
%     整段 curv 作为 curv1 返回，UseConstJerk=true，ret=-1
%
% Inputs :
%   ctx   : 计算链上下文（含 cfg.LSplitZero 等配置）
%   curv  : 待处理的零速起始曲线（zspdmode 含 ZeroStart 标记）
%
% Outputs :
%   ret   : 操作状态（≥ 0 = 成功，< 0 = 失败/曲线过短）
%   curv1 : 零速加速区子段（UseConstJerk=true）
%   curv2 : 剩余主段（UseConstJerk=false）；切割失败时未定义
%

L       = LengthCurv( ctx, curv, 0, 1 );   % 曲线总弧长（mm）
Lcut    = ctx.cfg.LSplitZero;               % 零速段目标长度（mm）

% 防护：Lcut 不得超过总长的 1/3（保证剩余主段有足够长度）
if( Lcut > L / 3 ), Lcut = L / 3; end

% 从头部（isEnd=false）切出弧长 Lcut 的子段
% cutCurvStruct 返回：ret（状态）、curvSplited（左半段）、curv（右半段）
[ ret, curv1, curv2 ] = cutCurvStruct( ctx, curv, 0, Lcut, false );

if( ret < 0 )
    % 切割失败（曲线整体过短）：将整段曲线作为恒定跃度段返回
    curv1                   = curv;
    curv1.UseConstJerk      = true;
    % zeroSpeedCurv 预计算从零速加速所需的恒定跃度速度曲线参数
    % isEnd=false 表示零速在起点（加速方向）
    [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1, false );
    curv1.ConstJerk         = jps;
else
    % 切割成功
    % 验证 curv1 的实际弧长与目标 Lcut 一致（公差 0.1 mm）
    ocn_assert( check_curv_length( ctx, curv1, Lcut ), "Curve Length not valide", mfilename );

    % curv1：零速加速区 → 恒定跃度速度曲线
    curv1.UseConstJerk      = true;
    [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1, false );
    curv1.ConstJerk         = jps;

    % curv2：主段 → 普通 LP 规划（不使用恒定跃度）
    curv2.UseConstJerk      = false;

    % 调试验证：检查截取点处 curv/curv1/curv2 的 C2 连续性
    check_continuity( ctx, curv, curv1, curv2 );
end


%     if( u >= curv.b_param + curv.a_param || u <= curv.b_param)
%         u = curv.a_param / 2 + curv.b_param;
%     end

%     curv1               = curv;
%     curv1.a_param       = u -curv1.b_param;
% curv1.UseConstJerk  = true;
% [ ~, ~, ~, jps ]    = zeroSpeedCurv( ctx, curv1, false );
% curv1.ConstJerk     = jps;
%     curv1.Info.zspdmode = ZSpdMode.ZN;
%     curv1.Info.gcode_source_line = curv.Info.gcode_source_line;

%     curv2               = curv;
% curv2.UseConstJerk  = false;
%     curv2.b_param       = u;
%     curv2.a_param       = curv.a_param  + curv.b_param - curv2.b_param;
%
%     if( isAZeroEnd( curv ) )
%         curv2.Info.zspdmode = ZSpdMode.NZ;
%     else
%         curv2.Info.zspdmode = ZSpdMode.NN;
%     end

% if( coder.target("MATLAB") )
%     check_continuity( ctx, curv, curv1, curv2 );
% end
end

function [] = check_continuity( ctx, curv, curv1, curv2 )
% 调试辅助：验证截取前后三段曲线在连接点处的 C2 连续性
%
% 检查的连接点：
%   curv[end] == curv1[end]（curv1 是 curv 的左子段）
%   curv1[end] == curv2[start]（截取点处两段拼接）
%   curv[start] == curv1[start]（起点应完全相同）
%
% 导数规范化：EvalCurvStruct 返回对局部参数 u_l 的导数，
%   为了比较几何导数（与参数化无关），需要除以 a_param 和 a_param²

curv_vec    = [ curv; curv1; curv2 ];
u_vec       = [ 0, 1 ];
r           = repmat( curv.R0( ctx.cfg.maskTot ), 1, 2, 3 );
rd          = r;
rdd         = r;

for j = 1 : 3
    [ r( :, :, j ) , rd( :, :, j ), rdd( :, :, j ) ] = ...
        EvalCurvStruct( ctx, curv_vec( j ),  u_vec );
    % 归一化为弧长导数（除以参数窗口宽度 a_param）
    rd( :, :, j )    = rd( :, :, j )  / curv_vec( j ).a_param;
    if( 1 )
        rdd( :, :, j )   = rdd( :, :, j ) / curv_vec( j ).a_param^2;
    else
        rdd( :, :, j )   = rdd( :, :, j ) / curv_vec( j ).a_param;
    end
end

% ind1/ind2 定义三对连接点索引：[曲线序号, 端点序号(1=u=0, 2=u=1)]
ind1 = [ 1, 1; 1, 2; 2, 2 ];
ind2 = [ 2, 1; 3, 2; 3, 1 ];

for j = 1 : 3
    r1   = r( : , ind1( j, 2 ), ind1( j, 1 ) );
    r1d  = rd( : , ind1( j, 2 ), ind1( j, 1 ) );
    r1dd = rdd( : , ind1( j, 2 ), ind1( j, 1 ) );
    r2   = r( : , ind2( j, 2 ), ind2( j, 1 ) );
    r2d  = rd( : , ind2( j, 2 ), ind2( j, 1 ) );
    r2dd = rdd( : , ind2( j, 2 ), ind2( j, 1 ) );
    assert_continuity( r1, r1d, r1dd, r2, r2d, r2dd );
end

end


function [] = assert_continuity( r1, r1d, r1dd, r2, r2d, r2dd )
% 断言两点的位置（C0）、一阶导（C1）、二阶导（C2）在公差内一致
diff_r      = abs( r1    -r2 );
diff_rd     = abs( r1d   -r2d );
diff_rdd    = abs( r1dd  -r2dd );

tol = 1E-6;

ocn_assert( all( diff_r    < tol, 'all' ), "Continuity C0 failed", mfilename );
ocn_assert( all( diff_rd   < tol, 'all' ), "Continuity C1 failed", mfilename );
ocn_assert( all( diff_rdd   < tol, 'all' ),"Continuity C2 failed", mfilename );
end

function [ isValid ] = check_curv_length( ctx, curv, L )
% 验证曲线弧长与期望值 L 之差在公差（0.1 mm）内
tol = 1E-1;
isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
end
