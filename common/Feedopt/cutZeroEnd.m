function [ ret, curv1, curv2 ] = cutZeroEnd( ctx, curv )
%#codegen
% cutZeroEnd : 从曲线尾部切出零速终止子段，并为其预计算恒定跃度速度曲线
%
% 【零速终止处理原理】
%   当曲线以零速结束（ZeroEnd），需要在终点附近规划一段"减速区"：
%   减速区弧长 = Lcut（由 cfg.LSplitZero 给出，不超过总长的 1/3）。
%   减速区子段 curv2 标记为 UseConstJerk=true，优化阶段将用解析的
%   恒定跃度（常数 jerk）速度曲线代替 LP 规划，以精确处理零终速边界。
%
%   切割结果（正常情况）：
%     curv1 [0 → L-Lcut]  UseConstJerk=false，后续按常规分割优化
%     curv2 [L-Lcut → L]  UseConstJerk=true，zspdmode=NZ（普通起、零速止）
%
%   切割失败（曲线总长 < 3×Lcut，即 Lcut 被夹到 L/3 后仍切割失败）：
%     整段 curv 作为 curv1 返回，UseConstJerk=true，ret=-1
%
%   注意：本函数与 cutZeroStart 对称，区别在于：
%     - 从尾部切（isEnd=true → cutCurvStruct 从右端反向切割）
%     - zeroSpeedCurv 的 isEnd=true（减速方向）
%
% Inputs :
%   ctx   : 计算链上下文（含 cfg.LSplitZero 等配置）
%   curv  : 待处理的零速终止曲线（zspdmode 含 ZeroEnd 标记）
%
% Outputs :
%   ret   : 操作状态（≥ 0 = 成功，< 0 = 失败/曲线过短）
%   curv1 : 主段（UseConstJerk=false）；切割失败时为整段（UseConstJerk=true）
%   curv2 : 零速减速区子段（UseConstJerk=true）；切割失败时未定义
%

L       = LengthCurv( ctx, curv, 0, 1 );   % 曲线总弧长（mm）
Lcut    = ctx.cfg.LSplitZero;               % 零速段目标长度（mm）

% 防护：Lcut 不得超过总长的 1/3（保证剩余主段有足够长度）
if( Lcut > L / 3 ), Lcut = L / 3; end

% 从尾部（isEnd=true）切出弧长 Lcut 的子段
% cutCurvStruct 以反向方式截取：curv1 为左主段，curv2 为右零速段
[ ret, curv1, curv2 ] = cutCurvStruct( ctx, curv, 1, Lcut, true );

if( ret < 0 )
    % 切割失败（曲线整体过短）：将整段曲线作为恒定跃度段返回
    curv1 = curv;
    curv1.UseConstJerk      = true;
    % zeroSpeedCurv 预计算驶入零速所需的恒定跃度速度曲线参数
    % isEnd=true 表示零速在终点（减速方向）
    [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1, true );
    curv1.ConstJerk         = jps;
else
    % 切割成功
    % 验证 curv2 的实际弧长与目标 Lcut 一致（公差 0.1 mm）
    ocn_assert( check_curv_length( ctx, curv2, Lcut ), "Curve Length not valide", mfilename );

    % curv2：零速减速区 → 恒定跃度速度曲线（从末端反向预计算）
    curv2.UseConstJerk      = true;
    [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2, true );
    curv2.ConstJerk         = jps;

    % curv1：主段 → 普通 LP 规划
    curv1.UseConstJerk      = false;

    % 调试验证：检查截取点处 curv/curv1/curv2 的 C2 连续性
    check_continuity( ctx, curv, curv1, curv2 );
end

%     if( u >= curv.b_param + curv.a_param || u <= curv.b_param)
%         u = curv.a_param / 2 + curv.b_param;
%     end

%     curv2                   = curv;
% curv2.UseConstJerk      = true;
% curv2.b_param           = u;
% curv2.a_param           = curv.a_param  + curv.b_param - curv2.b_param;
% [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2, true );
% curv2.ConstJerk         = jps;
% curv2.Info.zspdmode     = ZSpdMode.NZ;
%
% curv1                   = curv;
% curv1.a_param           = u - curv1.b_param;
% curv1.UseConstJerk      = false;
% curv1.Info.gcode_source_line = curv.Info.gcode_source_line;
%
% if( isAZeroStart( curv ) )
%     curv1.Info.zspdmode = ZSpdMode.ZN;
% else
%     curv1.Info.zspdmode = ZSpdMode.NN;
% end
%
% if( coder.target("MATLAB") )
%     check_continuity( ctx, curv, curv1, curv2 );
% end
end

function [] = check_continuity( ctx, curv, curv1, curv2 )
% 调试辅助：验证截取前后三段曲线在连接点处的 C2 连续性
%
% 逻辑与 cutZeroStart 中的 check_continuity 相同（见该函数的注释）。
% 此处验证的是从尾部截取后，curv1/curv2 与原始 curv 的几何一致性。

curv_vec    = [ curv; curv1; curv2 ];
u_vec       = [ 0, 1 ];
r           = repmat( curv.R0( ctx.cfg.maskTot ), 1, 2, 3 );
rd          = r;
rdd         = r;

for j = 1 : 3
    [ r( :, :, j ) , rd( :, :, j ), rdd( :, :, j ) ] = ...
        EvalCurvStruct( ctx, curv_vec( j ),  u_vec );
    rd( :, :, j )    = rd( :, :, j )  / curv_vec( j ).a_param;
    if( 1 )
        rdd( :, :, j )   = rdd( :, :, j ) / curv_vec( j ).a_param^2;
    else
        rdd( :, :, j )   = rdd( :, :, j ) / curv_vec( j ).a_param;
    end
end

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
% 断言两点的位置（C0）、一阶导（C1）、二阶导（C2）在公差（1e-9）内一致
% 注：cutZeroEnd 的公差（1e-9）比 cutZeroStart（1e-6）更严格，
%     因为尾部截取点处的几何应与头部一样精确（数值上差异在浮点误差量级）。

diff_r      = abs( r1    -r2 );
diff_rd     = abs( r1d   -r2d );
diff_rdd    = abs( r1dd  -r2dd );

tol = 1E-9;

ocn_assert( all( diff_r    < tol, 'all' ), "Continuity C0 failed", mfilename );
ocn_assert( all( diff_rd   < tol, 'all' ), "Continuity C1 failed", mfilename );
ocn_assert( all( diff_rdd   < tol, 'all' ),"Continuity C2 failed", mfilename );
end


function [ isValid ] = check_curv_length( ctx, curv, L )
% 验证曲线弧长与期望值 L 之差在公差（0.1 mm）内
tol = 1E-1;
isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
end
