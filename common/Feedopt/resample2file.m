function [ ] = resample2file( ctx, fileName )
% resample2file : 将 q_opt 队列中所有优化曲线段重采样为等时间步轨迹，写入文件
%
% ═══════════════════════════════════════════════════════════════════════════
% 【一、整体流程：LP 结果 → 机器人轨迹】
%
%   LP 优化（feedratePlanning）输出的是每条曲线段的进给率系数 Coeff，
%   描述的是速度平方 v²(u) 在参数 u 上的 B 样条展开：
%
%       v²(u) = Σ Coeff_i × B_i(u)
%
%   物理速度 v = |r'(u)| × du/dt，因此：
%
%       du/dt = v(u) / |r'(u)| = sqrt( v²(u) ) / |r'(u)|
%
%   resampling 的任务是：对上式做数值积分，求出每个等时间步 t×dt 对应的
%   参数位置 u(t)，再通过 B 样条求值得到物理位置 r(t)、速度、加速度、跃度。
%
%   ┌─────────────────────────────────────────────────────────────────────┐
%   │  LP 输出 Coeff（v²(u) 系数）                                         │
%   │      ↓  resampleCurv（数值积分，求 u(t)）                             │
%   │  u(t) — 每个采样步的参数位置                                           │
%   │      ↓  computeUDerivative（求 ud, udd, uddd）                       │
%   │  参数导数：du/dt, d²u/dt², d³u/dt³                                   │
%   │      ↓  calcRVAJfromU（链式法则）                                     │
%   │  物理轨迹：位置 r(t), 加速度 a(t), 跃度 j(t)                           │
%   │      ↓  写入 buffer → 文件                                            │
%   └─────────────────────────────────────────────────────────────────────┘
%
% ═══════════════════════════════════════════════════════════════════════════
% 【二、零速段的特殊处理】
%
%   ZeroStart（ZN）/ ZeroEnd（NZ）段不使用 LP Coeff，而是用预算的 ConstJerk：
%
%       u(t) = ConstJerk × t³ / 6   （ZeroStart，从零速加速）
%       u(t) = 1 - ConstJerk×(T-t)³/6  （ZeroEnd，减速到零）
%
%   computeUDerivative 根据 zspdmode 选择两条路径：
%     NN / ZZ → B 样条 Coeff（LP 结果）
%     ZN / NZ → constJerkU（恒定伪跃度解析公式）
%
% ═══════════════════════════════════════════════════════════════════════════
% 【三、输出文件格式】
%   每行 = 一个采样时间步，列定义：
%     [ t,  u_global,  f_norm,  feed,  cf,  r(轴)',  a(轴)',  j(轴)',  Pr0D(轴)' ]
%
%   t        : 全局时间步编号（从 1 开始）
%   u_global : 全局参数（= 局部 u + 曲线序号k-1，区分不同曲线段）
%   f_norm   : 归一化进给率（实际 / 指令，= 1 表示完全跟上）
%   feed     : 实际路径线速度（mm/s）
%   cf       : 指令进给率（Curv.Info.FeedRate，mm/min 或 mm/s）
%   r        : 机器人各轴位置（由 maskTot 选出的轴）
%   a        : 各轴加速度（归一化到 amax）
%   j        : 各轴跃度（归一化到 jmax）
%   Pr0D     : 段坐标系（piece frame）下的位置
%
% ═══════════════════════════════════════════════════════════════════════════
% Inputs :
%   ctx      : 计算链上下文（含 q_opt、Bl、cfg、GaussLegendre 参数等）
%   fileName : 输出文件路径（CSV 格式，超过缓冲区时分批追加写入）

if ctx.q_opt.isempty(), return; end % q_opt 为空说明未执行任何优化，直接退出

N              = ctx.q_opt.size();
dt             = ctx.cfg.dt;
% ResampleState 维护重采样的积分状态（当前 u、上一步 u、积分余量等）
state          = ResampleState( dt, ctx.cfg.DefaultZeroStopCount );
countInPercent = double( 0 );

% 预分配大缓冲区（避免频繁 I/O）；每列对应一个采样点的完整数据行
ind = 0; sizeBuffer = 1E7; t = 0;
buffer    = zeros( sizeBuffer, 5 + 4 * ctx.cfg.NumberAxis );
firstTime = true;   % 第一次写文件用覆盖模式，之后用追加模式

counter = 0;

for k = 1 : N
    countInPercent = printAvancement( countInPercent, k, N, ...
        ctx.cfg.ENABLE_PRINT_MSG );

    Curv                     = ctx.q_opt.get( k );
    Curv.MaxConstantFeedRate = 0;   % 保留字段，当前版本置 0
    state.go_next            = false;

    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseNbCurvCounter();
    end

    % ── 内层循环：对当前曲线段逐采样步推进 ──────────────────────────────────
    % resampleCurv 每次调用推进一个 dt 步长，有两种结果：
    %
    %   情况 A：u_new ≤ 1（段内正常步）
    %     isOutsideRange = false，go_next = false
    %     → 记录轨迹点，继续循环
    %
    %   情况 B：u_new > 1（本步内越过了段终点 u=1）
    %     isOutsideRange = true，go_next = true
    %     resampleCurv 内部：
    %       1. 精确计算越界时刻 Tr（GL积分估算 + 二次方程求根）
    %       2. 将剩余时间 dt-Tr 存入 state.dt（供下一段首步使用）
    %     → 不记录轨迹点（u 值无物理意义），while 条件失败退出循环
    %
    % 【段间时间无缝拼接】
    %   段 k 最后一步用了 Tr，剩余 dt-Tr 存入 state.dt。
    %   循环结束后 ResampleState(state.dt,...) 用此残差初始化下一段，
    %   下一段首步从 dt-Tr 起跑（而非完整 dt），整条轨迹采样点严格等时间间隔：
    %
    %     段k：  |──步1──|──步2──|──步3──Tr─→ 越界
    %     段k+1：                        |←dt-Tr→|──步1──|──步2──|...
    while ~state.go_next
        [ state ] = resampleCurv( state, ctx.Bl, ...
            Curv.Info.zspdmode, Curv.Coeff, ...
            Curv.ConstJerk, dt, ctx.cfg.GaussLegendreX, ...
            ctx.cfg.GaussLegendreW, ctx.cfg.ENABLE_PRINT_MSG );

        if( ~state.isOutsideRange )
            % 情况 A：u ∈ [0,1]，本步有效，写入轨迹点
            t   = t + 1;
            ind = ind + 1;
            if( ind > sizeBuffer )
                % 缓冲区写满，刷入文件，重置游标
                ind       = 1;
                firstTime = write2files( firstTime, buffer, fileName );
            end

            % u_global：将局部参数 u∈[0,1] 偏移到全局坐标（第 k 段偏移 k-1）
            % 用于可视化时区分各段在整条轨迹上的位置
            u  = state.u + double(k) - 1;
            cf = Curv.Info.FeedRate;   % 当前段的指令进给率

            % ── 计算参数导数 ud / udd / uddd ─────────────────────────────
            % 根据 zspdmode 选择两种方案：
            %   NN/ZZ → B 样条 Coeff：q=B(u)×Coeff, ud=calcUfromQ(q,qd,qdd)
            %   ZN/NZ → 恒定伪跃度：constJerkTime(u) → constJerkU(t)
            [ ud, udd, uddd ] = computeUDerivative( ctx.Bl, Curv.Info.zspdmode, ...
                Curv.Coeff, Curv.ConstJerk, state.u );

            % 将当前步的参数导数写回 state，供 calcRVAJfromU 使用
            state = state.setU( state.u, ud, udd, uddd );

            % ── 链式法则：参数导数 → 物理加速度 / 跃度 ─────────────────────
            % r   = 各轴位置（由 EvalCurvStruct 通过 B 样条求值）
            % a   = d²r/dt²（via ud,udd 和 r''(u)）
            % j   = d³r/dt³（via ud,udd,uddd 和 r'''(u)）
            [ r, ~, a, j ] = calcRVAJfromU( ctx, Curv, state.u, state.ud, ...
                                            state.udd, state.uddd );

            % ── 在段坐标系（piece frame）中求位置和切向 ───────────────────
            % Pr0D：段坐标系下的位置（用于工件坐标输出）
            % Pr1D：段坐标系下的切向，用于计算路径线速度
            [ r0D, r1D  ] = EvalCurvStruct( ctx, Curv, state.u );           %#ok
            [ Pr0D, Pr1D] = EvalCurvStructInPieceFrame( ctx, Curv, state.u );

            % 路径线速度：v = r'(u) × ud，取笛卡尔轴的模（vecnorm）
            v    = Pr1D .* state.ud;
            feed = vecnorm( v( ctx.cfg.indCart ) );

            % 归一化指标（供分析与可视化）
            f_norm = feed / Curv.Info.FeedRate;                        % 进给率比值
            a      = abs( a ./ ctx.cfg.amax( ctx.cfg.maskTot )' );    % 加速度/上限
            j      = abs( j ./ ctx.cfg.jmax( ctx.cfg.maskTot )' );    % 跃度/上限

            % 数值微分验证（调试用，正常运行时 if(0) 跳过）
            if(0)
                [v_norm, a_norm, j_norm] = assert_numerical_derivative( r, ctx.cfg );
                assert( all(v_norm <= 1), "Counter " + counter + " : Velocity is above the limits");
                assert( all(a_norm <= 1), "Counter " + counter + " : Acceleration is above the limits");
                assert( all(j_norm <= 1), "Counter " + counter + " : Jerk is above the limits");
            end

            % 无论 if(0) 是否启用，数值导数始终计算（用于打印超限警告）
            assert_numerical_derivative( r, ctx.cfg );

            % 写入缓冲区：[时间步, 全局参数, f_norm, 实际进给, 指令进给,
            %              位置, 归一化加速度, 归一化跃度, 段坐标位置]
            buffer( ind, : ) = [ t, u, f_norm, feed, cf, r', a', j', Pr0D' ];
            counter = counter + 1;
        end
        % 情况 B（isOutsideRange=true）：越界帧，跳过 if 块，
        % go_next=true 使 while 在本次迭代结束后退出。
    end

    % 当前曲线段处理完毕，用 state.dt（= 残差时间 dt-Tr，或整步 dt）
    % 初始化下一段的 ResampleState，实现段间时间无缝拼接。
    state = ResampleState( state.dt, ctx.cfg.DefaultZeroStopCount );
end

% 将缓冲区剩余数据写入文件
write2files( firstTime, buffer( 1 : ind , : ) , fileName );

printAvancement( 100 , N, N, ctx.cfg.ENABLE_PRINT_MSG );
end

% ─────────────────────────────────────────────────────────────────────────
function [countInPercent] = printAvancement(countInPercent, k, N, enablePrint)
% printAvancement : 每增加约 1% 进度时打印一次百分比
if( floor( k * 100 / N ) > countInPercent )
    if( coder.target( 'MATLAB' ) )
        DebugLog(DebugCfg.OptimProgress, '%3d [%%]\n', countInPercent);
    else
        ocn_print( enablePrint, '%3d [%%]\n', countInPercent, mfilename );
    end
    countInPercent = double( countInPercent + max( 1, floor( 100 / N ) ) );
end
end

% ─────────────────────────────────────────────────────────────────────────
function [ firstTime ] = write2files( firstTime, A, fileName )
% write2files : 首次覆盖写，后续追加写，以支持超大轨迹分批输出
if( firstTime )
    param     = {};
    firstTime = false;
else
    param = {'WriteMode', 'append'};
end
writematrix( A, fileName, param{:} );
end

% ─────────────────────────────────────────────────────────────────────────
function [ ud, udd, uddd ] = computeUDerivative( Bl, zspdmode, Coeff, ...
    constJerk, u )
% computeUDerivative : 根据速度剖面类型，计算当前参数位置 u 处的参数导数
%
% 【两条路径的数学含义】
%
%   路径 1 — ZeroStart（ZN）：恒定伪跃度加速，u(t) = constJerk × t³/6
%     isEnd=false → constJerkTime 由 u 反解时间 t，再用 constJerkU 求导
%     ud   = du/dt = constJerk × t² / 2
%     udd  = d²u/dt² = constJerk × t
%     uddd = d³u/dt³ = constJerk
%
%   路径 2 — ZeroEnd（NZ）：恒定伪跃度减速，u(t) = 1 - constJerk×(T-t)³/6
%     isEnd=true → 同上，时间轴反转
%
%   路径 3 — 正常段（NN/ZZ）：B 样条速度剖面，v²(u) = Σ Coeff_i × B_i(u)
%     q   = B(u) × Coeff  （B 样条在 u 处的基函数值 × 系数 = ud²(u)）
%     qd  = B'(u)× Coeff  （ud²(u) 对 u 的一阶导数）
%     qdd = B''(u)×Coeff  （ud²(u) 对 u 的二阶导数）
%
%     LP 优化的决策变量是"参数速度的平方" ud²(u)，而非物理速度的平方 v²(u)。
%     二者关系：v = |r'(u)| × ud，即 v² = |r'|² × ud²。
%     velocity 约束 w ≤ (vj_max/r'j)² 写成 ud² ≤ (vj_max/r'j)²，
%     恰好等价于 |r'j × ud| = |vj| ≤ vj_max，形式更简洁且无需除 |r'|。
%
%     calcUfromQ 从 q = ud², qd = d(ud²)/du, qdd = d²(ud²)/du² 反推导数：
%       ud   = sqrt(q)
%              （q = ud² 开方）
%       udd  = qd / 2
%              （链式法则：d(ud)/dt = d(ud)/du × ud = qd/(2ud) × ud = qd/2）
%       uddd = qdd / 2 × ud
%              （链式法则：d(udd)/dt = d(qd/2)/du × ud = (qdd/2) × ud）

if( zspdmode == ZSpdMode.ZN )
    isEnd = false; forcelimit = false;
    [ time ] = constJerkTime( constJerk, u, isEnd );
    [ ~, ud, udd, uddd ] = constJerkU( constJerk, time, isEnd, forcelimit );
elseif( zspdmode == ZSpdMode.NZ )
    isEnd = true; forcelimit = false;
    [ time ] = constJerkTime( constJerk, u, isEnd );
    [ ~, ud, udd, uddd ] = constJerkU( constJerk, time, isEnd, forcelimit );
else
    % 正常段：从 B 样条 Coeff 重建参数导数
    [ q, qd, qdd ]    = bspline_eval( Bl, Coeff', u );
    [ ud, udd, uddd ] = calcUfromQ( q, qd, qdd );
end

end

% ─────────────────────────────────────────────────────────────────────────
function [v_norm, a_norm, j_norm] = assert_numerical_derivative( pos, cfg )
% assert_numerical_derivative : 用有限差分验证轨迹的速度/加速度/跃度是否超限
%
% 方法：对位置序列 pos(t) 做数值微分（三点差分），得到 v/a/j 的估计值，
%   再除以各轴约束上限，得到归一化值。> 1 表示超限，打印警告。
%
% persistent buffer 保存上几帧的位置，用于跨帧差分计算高阶导数。
persistent buffer;
if( isempty(buffer) ), buffer = []; end

[ buffer, v, a, j ] = numerical_derivatives( buffer, pos, cfg.dt );

v_norm = abs( v ./ cfg.vmax( cfg.maskTot )' );
a_norm = abs( a ./ cfg.amax( cfg.maskTot )' );
j_norm = abs( j ./ cfg.jmax( cfg.maskTot )' );

if(any(v_norm > 1))
    ocn_print( cfg.ENABLE_PRINT_MSG, "Velocity is not in the limits", mfilename );
end
if(any(a_norm > 1))
    ocn_print( cfg.ENABLE_PRINT_MSG, "Acceleration is not in the limits", mfilename );
end
if(any(j_norm > 1))
    ocn_print( cfg.ENABLE_PRINT_MSG, "Jerk is not in the limits", mfilename );
end
end
