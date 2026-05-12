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
% 即使在很短的ZZ轨迹的情况下，也会被拆分为ZN+NZ两段(L/3和2L/3)，保证加速区有足够长度进行恒定跃度规划
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
% check_continuity : 调试辅助——验证截取前后三段曲线在连接点处的 C2 连续性
%
% 【背景】
%   cutCurvStruct 将 curv 在弧长 Lcut 处切为左段 curv1、右段 curv2。
%   切割操作只改变参数窗口 [b_param, b_param+a_param]，不改变几何形状，
%   故三段曲线在以下三个连接点处应严格 C2 连续：
%
%   连接点 j=1：curv(u=0)  == curv1(u=0)  → 起点相同（切割未移动起点）
%   连接点 j=2：curv(u=1)  == curv2(u=1)  → 终点相同（切割未移动终点）
%   连接点 j=3：curv1(u=1) == curv2(u=0)  → 截取点处两段无缝拼接（核心检查）
%
% 【三维数组布局】
%   r / rd / rdd 均为 (dim × 2 × 3) 张量：
%     第 1 维：空间维度（轴数，由 maskTot 选出）
%     第 2 维：端点索引，1 = u=0（起点），2 = u=1（终点）
%     第 3 维：曲线索引，1=curv，2=curv1，3=curv2
%
% 【导数归一化——为何除以 a_param】
%   EvalCurvStruct 返回的是对局部参数 u_l ∈ [0,1] 的导数。
%   局部参数与全局参数的关系：u_l = (u_g - b_param) / a_param
%   因此链式法则给出：
%     dr/du_g = dr/du_l × (du_l/du_g) = (dr/du_l) / a_param
%     d²r/du_g² = (d²r/du_l²) / a_param²
%   三段曲线的 a_param 不同（curv1/curv2 是 curv 的子窗口），
%   只有归一化到全局参数导数后才能直接比较。
%
% 【ind1/ind2 索引表】
%   每行格式：[曲线序号, 端点序号]，端点 1=u=0，端点 2=u=1
%
%   j | ind1          | ind2          | 含义
%   --|---------------|---------------|----------------------------
%   1 | curv(1),  起(1)| curv1(2), 起(1)| curv 起点 == curv1 起点
%   2 | curv(1),  止(2)| curv2(3), 止(2)| curv 终点 == curv2 终点
%   3 | curv1(2), 止(2)| curv2(3), 起(1)| 截取点：curv1 止 == curv2 起

curv_vec = [ curv; curv1; curv2 ];
u_vec    = [ 0, 1 ];                        % 同时求各段的起点和终点

% 预分配 (dim × 2端点 × 3曲线) 张量
r   = repmat( curv.R0( ctx.cfg.maskTot ), 1, 2, 3 );
rd  = r;
rdd = r;

for j = 1 : 3
    [ r( :, :, j ), rd( :, :, j ), rdd( :, :, j ) ] = ...
        EvalCurvStruct( ctx, curv_vec( j ), u_vec );

    % 归一化：局部参数导数 → 全局参数导数
    %   一阶：dr/du_g = (dr/du_l) / a_param
    %   二阶：d²r/du_g² = (d²r/du_l²) / a_param²
    rd(  :, :, j ) = rd(  :, :, j ) / curv_vec( j ).a_param;
    if( 1 )
        % 正确的二阶归一化（除以 a_param²）
        rdd( :, :, j ) = rdd( :, :, j ) / curv_vec( j ).a_param^2;
    else
        % 遗留的调试分支（除以 a_param 为错误实现，已废弃，勿启用）
        rdd( :, :, j ) = rdd( :, :, j ) / curv_vec( j ).a_param;
    end
end

% 三对连接点索引：[曲线序号, 端点序号]（端点 1=起, 2=止）
ind1 = [ 1, 1;   % j=1：curv  起点
         1, 2;   % j=2：curv  终点
         2, 2 ]; % j=3：curv1 终点（截取点左侧）
ind2 = [ 2, 1;   % j=1：curv1 起点
         3, 2;   % j=2：curv2 终点
         3, 1 ]; % j=3：curv2 起点（截取点右侧）

% 逐对提取并断言 C2 连续性
% 数组索引：r(空间维, 端点, 曲线) → r(:, ind(j,2), ind(j,1))
for j = 1 : 3
    r1   = r(   :, ind1(j,2), ind1(j,1) );
    r1d  = rd(  :, ind1(j,2), ind1(j,1) );
    r1dd = rdd( :, ind1(j,2), ind1(j,1) );
    r2   = r(   :, ind2(j,2), ind2(j,1) );
    r2d  = rd(  :, ind2(j,2), ind2(j,1) );
    r2dd = rdd( :, ind2(j,2), ind2(j,1) );
    assert_continuity( r1, r1d, r1dd, r2, r2d, r2dd );
end

end


function [] = assert_continuity( r1, r1d, r1dd, r2, r2d, r2dd )
% assert_continuity : 断言两端点的 C0/C1/C2 连续性均在公差（1e-6）内
%
% C0（位置连续）：|r1    - r2   | < tol  → 两点位置完全重合
% C1（切向连续）：|r1d   - r2d  | < tol  → 归一化后一阶导相等（切线方向一致）
% C2（曲率连续）：|r1dd  - r2dd | < tol  → 归一化后二阶导相等（曲率大小一致）
%
% 公差 1e-6（mm 量级）：严于 smoothCurvStructs 的 G2 检查（~1e-3），
% 因为截取操作在同一几何曲线上切割，误差应来自浮点精度，远小于几何公差。

tol = 1E-6;

diff_r   = abs( r1   - r2   );
diff_rd  = abs( r1d  - r2d  );
diff_rdd = abs( r1dd - r2dd );

ocn_assert( all( diff_r   < tol, 'all' ), "Continuity C0 failed", mfilename );
ocn_assert( all( diff_rd  < tol, 'all' ), "Continuity C1 failed", mfilename );
ocn_assert( all( diff_rdd < tol, 'all' ), "Continuity C2 failed", mfilename );
end

function [ isValid ] = check_curv_length( ctx, curv, L )
% 验证曲线弧长与期望值 L 之差在公差（0.1 mm）内
tol = 1E-1;
isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
end
