function [ state ] = resampleCurv(state, Bl, curv_mode, ...
    coeff, constJerk, dt, GaussLegendreX, GaussLegendreW, enablePrint )
%#codegen
% resampleCurv : 执行一个采样步，将参数 u 从当前位置推进一个时间步 dt
%
% ═══════════════════════════════════════════════════════════════════════════
% 【核心任务】
%   已知当前参数位置 state.u（上一步的终点），求下一步的参数位置 u_new。
%
%   物理意义：机器人沿 B 样条曲线运动，参数 u ∈ [0,1] 描述路径进度。
%   进给率优化已知 v²(u)（速度平方关于 u 的函数），需要积分求 u(t)：
%
%       du/dt = f(u)  →  u_new = u_old + ∫₀^dt f(u) dt  （Taylor 近似）
%
% ═══════════════════════════════════════════════════════════════════════════
% 【三种推进模式，由 curv_mode 选择】
%
%   ZN（ZeroStart，零速起始）：
%     u(t) = constJerk × t³/6，由当前 u 反解时间 t，再推进 dt
%
%   NZ（ZeroEnd，零速终止）：
%     同上，但时间轴反转（减速到零）
%
%   NN/ZZ（正常段）：
%     从 B 样条 Coeff 取 q=v²(u)，用 Taylor 二阶展开：
%       u_new = u + ud×dt + udd×dt²/2
%
% ═══════════════════════════════════════════════════════════════════════════
% 【段边界处理（u > 1 时）】
%   当 u_new 超过 1，说明本时间步内曲线段已走完。需要：
%   1. 用 GL 积分或二次方程精确求出越界时刻 Tr（从 u_old 到 u=1 的时间）
%   2. 将剩余时间 dt - Tr 存入 state.dt，供下一段的第一步使用
%   3. 标记 isOutsideRange=true（本步不记录轨迹点）、go_next=true（换段）
%
% ═══════════════════════════════════════════════════════════════════════════
% Inputs :
%   state          : ResampleState（含 u、ud、udd、uddd、dt、isAStop 等）
%   Bl             : B 样条对象（含节点向量、阶次，用于基函数求值）
%   curv_mode      : ZSpdMode 枚举（ZN/NZ/NN/ZZ）
%   coeff          : LP 优化结果：v²(u) 的 B 样条系数（正常段用）
%   constJerk      : 恒定伪跃度值（零速段用）
%   dt             : 采样周期（可能为 state.dt 的分数步，用于边界对齐）
%   GaussLegendreX : GL 积分节点（用于精确计算越界时刻）
%   GaussLegendreW : GL 积分权重
%   enablePrint    : 是否打印调试信息
%
% Outputs :
%   state : 更新后的状态（u、ud、udd、uddd、go_next、isOutsideRange、dt）

coder.inline( "never" );

if( coder.target( "MATLAB" ) )
    DebugResampling.getInstance().increaseUCounter();
end

if coder.target( "MATLAB" )
    % MATLAB 环境：调用 MEX 加速版，逻辑与下方完全等价
    [ state ] = resampling_mex( 'resampleCurv', state, Bl, curv_mode, ...
    coeff, constJerk, dt, GaussLegendreX, GaussLegendreW, enablePrint );
else

    % ── 零速停顿计数器（ZeroEnd 段结束后原地等待若干步）────────────────────
    % 当前一曲线以零速结束（NZ），下一曲线以零速开始（ZN），
    % 两者之间需要"停在原地" DefaultZeroStopCount 步（保持 u=1 不变），
    % 由 state.isAStop 和 stopCounter 控制。
    if( state.isAStop )
        state = state.decreaseStopCounter();
        return;  % 本步不推进 u，直接返回（停顿帧）
    end

    % ══════════════════════════════════════════════════════════════════════
    % 步骤 1：根据 curv_mode 推进 u
    % ══════════════════════════════════════════════════════════════════════

    if( curv_mode == ZSpdMode.ZN )
        % ZeroStart：u(t) = constJerk × t³/6，从零速加速
        % constJerkTime(u) 由当前 u 反解对应时间 t
        % 推进一步：t_new = t + dt → 得到 u_new, ud_new, ...
        [ time ]             = constJerkTime( constJerk, state.u, false );
        isEnd = false; forcelimit = false;
        [ u, ud, udd, uddd ] = constJerkU( constJerk, time + state.dt, isEnd, ...
            forcelimit );

    elseif( curv_mode == ZSpdMode.NZ )
        % ZeroEnd：与 ZN 对称，isEnd=true 使时间轴反转（减速到零）
        [ time ]             = constJerkTime( constJerk, state.u, true );
        isEnd = true; forcelimit = false;
        [ u, ud, udd, uddd ] = constJerkU( constJerk, time + state.dt, isEnd, ...
            forcelimit );

    else
        % 正常段（NN/ZZ）：Taylor 二阶展开积分
        % 从 coeff（v²(u) 系数）求 ud，再积分推进 u
        [ u, ud, udd, uddd ] = ResampleNN( coeff, Bl, state.u, state.dt, enablePrint );
    end

    % 重置 dt 到标准采样周期（边界步骤会临时修改 state.dt）
    state.dt = dt;

    % 合法性检查：NaN / 复数 / 不单调递增等异常情况回退到 state.u
    u = check_u_state_validity( u, state, enablePrint );

    % ══════════════════════════════════════════════════════════════════════
    % 步骤 2：处理 u > 1（本步内曲线段走完）
    % ══════════════════════════════════════════════════════════════════════

    if( u > 1 )
        % 本时间步内参数越过了终点 u=1，需要精确计算越界时刻 Tr，
        % 以便将剩余时间 (dt - Tr) 传递给下一段的第一步。
        state.isOutsideRange = true;

        if( curv_mode == ZSpdMode.NN )
            % ── NN 模式：两步法求精确越界时刻 Tr ──────────────────────────
            TrVec = zeros( 1, 4 );

            % 【方法一：GL 数值积分估算 Tr】
            % Tr = ∫_{u_old}^{1}  1/sqrt(v²(u))  du
            % 其中 1/sqrt(v²(u)) = dt/du（单位参数所需时间）
            % 积分给出从 u_old 走到 u=1 所需的总时间
            GL_X = GaussLegendreX;
            GL_W = GaussLegendreW;
            % GL 节点从 [-1,1] 线性映射到 [state.u, 1]
            uval = ( state.u * ( 1 - GL_X ) + ( 1 + GL_X ) ) / 2;
            Ival = 1 ./ mysqrt( bspline_eval_vec( Bl, coeff', uval ) );
            % GL 积分：Tr = Σ w_j × Ival(u_j) × (1-state.u)/2
            Tr   = Ival.' * GL_W * ( 1 - state.u ) / 2;

            % GL 结果无效（复数或 NaN）时退化到整步 dt
            if( ~isreal( Tr ) || isnan( Tr ) )
                Tr = dt;
            end

            if( Tr >= dt )
                % 【方法二：Taylor 二次方程精确求根】
                % GL 积分估算 Tr≥dt（说明在本步内确实越界），
                % 用 Taylor 展开 u(t) = state.u + ud×t + udd/2×t²
                % 令 u(Tr) = 1：udd/2×Tr² + ud×Tr + (state.u-1) = 0
                % 即：a×t² + b×t + c = 0，c = state.u - 1 < 0
                a = udd / 2;  b = ud;  c = state.u - 1;
                Delta = b^2 - 4 * a * c;

                % 数值稳定的二次方程求根（避免相近数相减的精度损失）
                if( Delta <= 0 )
                    % 判别式非正：退化为一次近似
                    TrVec( 2 ) = -c / b;        % 线性近似根
                    TrVec( 3 ) = -b / a;        % 另一候选（udd 主导时）
                elseif( b > 0 )
                    % b > 0：用共轭形式避免大数相减
                    TrVec( 2 ) = 2 * c / ( -b - mysqrt(Delta) );
                    TrVec( 3 ) = ( -b - mysqrt(Delta) ) / ( 2 * a );
                else
                    % b ≤ 0：另一组共轭形式
                    TrVec( 2 ) = ( -b + mysqrt(Delta) ) / ( 2 * a );
                    TrVec( 3 ) = 2 * c / ( -b + mysqrt(Delta) );
                end
                TrVec( 4 ) = -c / b;   % 线性近似备选（a≈0 时最稳定）

                % 过滤无效根（NaN / 复数 / 负数 / 超过 dt）
                TrVec( isnan( TrVec ) )   = dt;
                TrVec( ~isreal(TrVec) )   = dt;
                TrVec( ~( TrVec >= 0 ) )  = dt;
                TrVec( ~( TrVec <= dt ) ) = dt;

                % 取残差 |u(Tr)-1| 最小的根作为最终 Tr
                yVec       = abs( a * TrVec.^2 + b * TrVec + c );
                [ ~, ind ] = min( yVec );
                Tr         = TrVec( ind );
            end

        elseif( curv_mode == ZSpdMode.ZN )
            % ZN 模式：用解析公式直接求越界时刻
            % constJerkTime([state.u, 1]) 返回两个时刻，差值即为 Tr
            [ time ] = constJerkTime( constJerk, [state.u, 1], false );
            Tr = time(2) - time(1);

        else
            % NZ 模式（ZeroEnd 终点）：曲线以零速结束，启动零速停顿计数器
            % startZeroStopTime 将 state.isAStop=true，后续若干步保持 u=1
            state = state.startZeroStopTime();
            return;
        end

        % 将剩余时间存入 state.dt，供下一段第一步使用（分数步对齐）
        % check_minimum_precision_dt 过滤 NaN / 复数 / 负值
        state.dt = check_minimum_precision_dt( dt - Tr, dt, enablePrint );

        if( coder.target( "MATLAB" ) )
            DebugResampling.getInstance().addDT( state.dt );
        end

    else
        % u ≤ 1：本步正常，更新状态
        state.isOutsideRange = false;
        state = state.setU( u, ud, udd, uddd );
    end

    % u ≥ 1 时通知外层换到下一段曲线（go_next 触发 resample2file 的 while 退出）
    if( u >= 1 )
        state.go_next = true;
    else
        state.go_next = false;
    end

end

end

% ─────────────────────────────────────────────────────────────────────────
function [ u, ud, udd, uddd ] = ResampleNN( coeff, Bl, uk, dt, enablePrint )
% ResampleNN : 正常段（NN）的参数推进——Taylor 二阶展开
%
% 步骤：
%   1. q   = v²(uk)         B 样条在 uk 处求值（= 速度平方）
%   2. qd  = dv²/du|_{uk}   速度平方对 u 的一阶导
%   3. qdd = d²v²/du²|_{uk} 速度平方对 u 的二阶导
%   4. calcUfromQ(q,qd,qdd) → ud, udd, uddd（参数导数，链式法则）
%   5. Taylor：u_new = uk + ud×dt + udd/2×dt²

[ q, qd, qdd ] = bspline_eval( Bl, coeff', uk );

if( q < 0 )
    % q=v²(u) < 0：B 样条系数异常（优化后理论上不应出现），
    % 安全退化：u 不前进，ud=0（速度归零），报告并跳出
    u = uk; ud = 0; udd = 0; uddd = 0;
    ocn_print( enablePrint, "Q should not be negative", mfilename );
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseQNegativeCounter();
    end
    return;
end

% 从 v²(u) 及其导数反推参数导数
[ ud, udd, uddd ] = calcUfromQ( q, qd, qdd );

% Taylor 二阶近似：u(t+dt) ≈ u + ud×dt + udd/2×dt²
% （三阶项 uddd/6×dt³ 精度已足够，注释中保留供参考）
u = uk + ud * dt + ( udd * dt ^ 2 ) / 2;

if( u <= uk )
    % Taylor 二阶给出的 u_new ≤ u_old（udd 为负且主导时可能发生），
    % 退化到一阶近似保证单调递增（ud > 0 由 LP 约束保证）
    u = uk + ud * dt;
end
end

% ─────────────────────────────────────────────────────────────────────────
function [ d_up ] = check_minimum_precision( d_low, d_up )
% check_minimum_precision : 保证 d_up 严格大于 d_low（避免浮点相等导致死循环）
if( ~( d_up > d_low ) )
    d_up = d_up + eps( d_up );
end
end

% ─────────────────────────────────────────────────────────────────────────
function [ d ] = check_minimum_precision_dt( d, dt, enablePrint )
% check_minimum_precision_dt : 过滤剩余时间 d = dt - Tr 的数值异常
%   NaN / 复数 / 负值 → 置 0（下一段从整步开始，无残差）
%   注释掉的 d > dt 检查：理论上不会发生，暂时宽松处理

if( isnan( d ) )
    d = 0.0;
    ocn_print( enablePrint, "Tr should not be nan", mfilename );
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseTNanCounter();
    end
end

if( ~isreal( d ) )
    d = 0.0;
    ocn_print( enablePrint, "Tr should be real", mfilename );
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseTNotRealCounter();
    end
end

if( d <= 0.0 )
    d = 0.0;
    ocn_print( enablePrint, "Tr should be positive", mfilename );
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseTNegativeCounter();
    end
end
end

% ─────────────────────────────────────────────────────────────────────────
function [ u ] = check_u_state_validity( u, state, enablePrint )
% check_u_state_validity : 检查并修正 u 的数值合法性
%   NaN / 复数 → 回退到 state.u（保持原位，不让 u 跳变）
%   负值 / 不单调 → 警告但不强制修正（由 check_minimum_precision 保证最小增量）

if( isnan( u ) )
    u = state.u;
    ocn_print( enablePrint, "U should not be nan", mfilename );
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseUNanCounter();
    end
end

if( ~isreal( u ) )
    u = state.u;
    ocn_print( enablePrint, "U should be real", mfilename );
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseUNotRealCounter();
    end
end

if( u < 0 )
    ocn_print( enablePrint, ...
        "U parameter should not be negative during resampling", mfilename );
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseUNegativeCounter();
    end
end

if( ~( u > state.u ) )
    % u 未前进：速度极低或数值误差，报告但允许通过（eps 补偿保证单调）
    ocn_print( enablePrint, ...
        "U parameter is too close from the previous one during resampling", ...
        mfilename );
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseUNotIncreasingCounter();
    end
end

% 最终保证 u 严格大于 state.u（至少差一个机器精度 eps）
u = check_minimum_precision( state.u, u );
end
