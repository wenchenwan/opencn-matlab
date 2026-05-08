function [ ctx ] = smoothCurvStructs( ctx )
%#codegen
% smoothCurvStructs : 平滑阶段主函数——检测相邻曲线是否满足 G2 连续性，
%                     并按需插入五次多项式过渡曲线或强制零速停顿。
%
% 【平滑阶段的任务】
%   q_compress 队列中存放的是经过压缩（合并共线直线）后的曲线段。
%   相邻曲线在连接点处可能存在切向不连续（G1 缺失）或曲率跳变（G2 缺失）。
%   若不处理，插补时速度/加速度会出现突变，损伤机床。
%
%   本函数逐对处理相邻曲线 (curv, nextCurv)，策略如下：
%
%   ┌──────────────────┬────────────────────────────────────────────────┐
%   │ 判断结果          │ 处理方式                                        │
%   ├──────────────────┼────────────────────────────────────────────────┤
%   │ needStop=true    │ 强制零速停顿：curv 以零速结束，nextCurv 以零速开始 │
%   │ needTransition   │                                                │
%   │   Skip=true      │ 配置禁止过渡：也强制零速停顿                      │
%   │   Skip=false     │ 调用 calcTransition 插入五次多项式过渡曲线 curvT  │
%   │     Ok           │ push curv1C, push curvT；curv ← curv2C         │
%   │     Failed       │ calcTransition 失败：强制零速停顿                │
%   │ 无需处理          │ curv 满足 G2：直接 push curv；curv ← nextCurv   │
%   └──────────────────┴────────────────────────────────────────────────┘
%
%   输出队列 q_smooth 中的曲线已全部满足 G2 连续性（或被零速隔开）。
%
% 过渡曲线插入机制（calcTransition 成功时）：
%   原始曲线对：  [curv] → [nextCurv]
%   插入后：      [curv1C] → [curvT] → [curv2C] → ...
%
%   curv1C  = curv 的左半段（从起点到过渡曲线起点）
%   curvT   = 五次多项式过渡曲线（G2 Hermite 插值，极短，约 0.2mm）
%   curv2C  = nextCurv 的右半段（从过渡曲线终点到 nextCurv 终点）
%   curv2C 不立即 push，留作下一轮的 curv 继续处理。
%
% Inputs :
%   ctx : 计算链上下文（含 q_compress、q_smooth、cfg 等字段）
%
% Outputs :
%   ctx : 更新后的上下文（q_smooth 已填入平滑结果）
%

% Optimal transitions calculation between segments whith G2 continuity

if ctx.q_compress.isempty(), return; end
ctx.k0  = int32( 1 );
Ncrv    = ctx.q_compress.size;

DebugLog( DebugCfg.Validate,         'Smoothing...\n' );
DebugLog( DebugCfg.OptimProgress,    'Smoothing...\n' );

% 取第一段曲线作为"当前曲线"，从第二段开始循环
curv = ctx.q_compress.get( 1 );
for k = 2 : Ncrv
    ctx.k0 = ctx.k0 + 1;
    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + Ncrv, mfilename );

    nextCurv = ctx.q_compress.get( k );

    % ── 步骤 1：判断连接点需要零速停顿还是过渡曲线 ────────────────────────
    [ needStop, needTransition ] = check_stop_and_transition( ctx, ...
        curv, nextCurv, ctx.cfg.Smoothing.ColTolSmooth, ...
        ctx.cfg.Smoothing.ColTolCosSmooth );

    if( needStop )
        % ── 分支 A：强制零速停顿 ─────────────────────────────────────────
        % curv 被标记为 ZeroEnd，nextCurv 标记为 ZeroStart，
        % add_zero_stop 将 curv 推入队列，curv ← nextCurv。
        [ ctx, curv ] = add_zero_stop( ctx, curv, nextCurv );
        if( coder.target( "MATLAB" ) )
            DebugTransition.getInstance.incZeroCurv;
        end
    elseif( needTransition  )
        if( ctx.cfg.Smoothing.Skip  )
            % ── 分支 B：配置禁止过渡，也强制零速 ───────────────────────────
            % Smoothing.Skip=true 时跳过过渡曲线计算（调试/快速模式）
            [ curv, nextCurv ]  = create_zero_end( curv, nextCurv );
            [ ctx, curv ]       = add_zero_stop( ctx, curv, nextCurv );
            if( coder.target( "MATLAB" ) )
                DebugTransition.getInstance.incZeroCurv;
            end
        else
            % ── 分支 C：计算 G2 过渡曲线 ────────────────────────────────
            % calcTransition 在两曲线连接点附近截取短段，
            % 用 G2 Hermite 插值生成五次多项式过渡曲线 curvT。
            [ status, curv1C, curv2C, curvT, ret ] = ...
                calcTransition( ctx, curv, nextCurv );
            if( status == TransitionResult.Ok )
                % 过渡成功：push 左半段 + 过渡曲线；curv2C 留待下轮处理
                ctx.q_smooth.push( curv1C );
                ctx.q_smooth.push( curvT );
                curv = curv2C;

                if( coder.target( "MATLAB" ) )
                    DebugTransition.getInstance.addTransition( curv1C, curvT, curv2C );
                end
            else
                % 过渡失败（曲线太短/曲率过大等）：退化为零速停顿
                [ curv, nextCurv ]  = create_zero_end( curv, nextCurv );

                if( coder.target( "MATLAB" ) )
                    DebugTransition.getInstance.addTransitionFail( curv, nextCurv, ret );
                end
                [ ctx, curv ]       = add_zero_stop( ctx, curv, nextCurv );

            end
        end
    else
        % ── 分支 D：连接点已满足 G2，无需处理 ───────────────────────────
        % 直接将 curv push 入输出队列，curv ← nextCurv 继续
        ctx.q_smooth.push( curv );
        curv = nextCurv;
        if( coder.target( "MATLAB" ) )
            DebugTransition.getInstance.incNoNeedForTransition;
        end
    end
end

% 循环结束后，最后一段曲线（curv）尚未 push，在此补充
ctx.q_smooth.push( curv );

end

%-------------------------------------------------------------------------%
% Functions
%-------------------------------------------------------------------------%
function [ needStop, needTransition ] = check_stop_and_transition( ctx, ...
    curv, nextCurv, tol, tol_cos  )
% check_stop_and_transition : 判断 (curv, nextCurv) 连接点的处理策略
%
% 三个短路退出条件（优先级从高到低）：
%   1. curv 是零速终止段（isAZeroEnd）→ 必须零速停顿，不做过渡
%   2. nextCurv.b_param > 0           → 跳过检查（见下方详解）
%   3. 检查 G2 平滑性                  → 不光滑则 needTransition=true
%
% 关于 nextCurv.b_param > 0 的含义：
%   b_param 是全局参数窗口的起点。若 b_param > 0，说明 nextCurv 是
%   某条原始曲线经过截取（cutCurvStruct）后的右半段。
%   右半段的左端点（即与 curv 的连接点）是截取操作产生的切点，
%   而截取本身保证了切点处 G2 连续（cutCurvStructU 在同一几何曲线上切割，
%   切点两侧导数完全一致）。因此无需再次检查，也不应插入过渡曲线。

needStop        = false;
needTransition  = false;

% 条件 1：curv 以零速结束（如加工区域边界），必须停顿
if( isAZeroEnd( curv ) ), needStop = true; return; end

% 条件 2：nextCurv 是截取右半段，连接点处 G2 由截取操作保证，跳过检查
if( nextCurv.b_param > 0 ), return; end

% 条件 3：检查连接点的位置/切向/曲率连续性
[ isSmooth ] = check_smoothness( ctx, curv, nextCurv, tol, tol_cos );

if( ~isSmooth ), needTransition = true; end

end
%-------------------------------------------------------------------------%
function [ curv, nextCurv ] = create_zero_end( curv, nextCurv )
% create_zero_end : 将 (curv, nextCurv) 标记为零速停顿对
%
% ZSpdMode 枚举说明：
%   ZN = ZeroStart（以零速开始）
%   NZ = ZeroEnd  （以零速结束）
%   ZZ = 既以零速开始又以零速结束（孤立短段）
%
% 逻辑：
%   curv  已是 ZeroStart → 标记为 ZZ（首尾均停）
%   curv  不是 ZeroStart → 标记为 NZ（仅末端停）
%   nextCurv 已是 ZeroEnd → 标记为 ZZ
%   nextCurv 不是 ZeroEnd → 标记为 ZN（仅起端停）

if( isAZeroStart( curv ) )
    curv.Info.zspdmode = ZSpdMode.ZZ;
else
    curv.Info.zspdmode = ZSpdMode.NZ;
end

if( isAZeroEnd( nextCurv ) )
    nextCurv.Info.zspdmode = ZSpdMode.ZZ;
else
    nextCurv.Info.zspdmode = ZSpdMode.ZN;
end

end
%-------------------------------------------------------------------------%
function [ isSmooth ] = check_smoothness( ctx, curv0, curv1, tol, tol_cos )
% check_smoothness : 在连接点处检查两段曲线的 G2 连续性
%
% 采样点：curv0 的终点（u=1）与 curv1 的起点（u=0）
%
% G2 连续性三项检查：
%   C0：位置连续   ‖r1(1) - r2(0)‖ < tol（逐轴）
%   G1：切向连续   cos(∠t1, t2) > cos(tol_cos)，即切向夹角极小
%   G2：曲率连续   ‖κ1 - κ2‖ < tol（逐轴曲率向量之差）
%
% 注：G1/G2 是几何条件（与参数化无关），calc_t_nk_kappa 已将参数导数
%     转换为曲率向量 κ = (r'×r'')/(‖r'‖³) 的方向和模长。

% 在连接点两侧各采样一个点
[ r11, r1d1, r1dd1 ] = EvalCurvStruct( ctx, curv0, 1 );   % curv0 末点
[ r21, r2d1, r2dd1 ] = EvalCurvStruct( ctx, curv1, 0 );   % curv1 首点

% 计算切向量 t、法向量 n、曲率向量 kappa
[t1, ~,  kappa1] = calc_t_nk_kappa( r1d1, r1dd1 );
[t2, ~,  kappa2] = calc_t_nk_kappa( r2d1, r2dd1 );

% C0：位置连续（逐轴差值均在公差内）
isC0   = all( abs( r11 - r21 ) < tol, 'all' );
% G1：切向连续（collinear 检查两单位向量夹角余弦）
isG1   = collinear( t1, t2, tol_cos );
% G2：曲率连续（曲率向量逐分量差值在公差内）
isG2   = all( abs( kappa1 -kappa2 ) < tol, 'all' );

isSmooth = ( isC0 && isG1 && isG2 );

end
%-------------------------------------------------------------------------%
%
function [ ctx, curv ] = add_zero_stop( ctx, curv, nextCurv )
% add_zero_stop : 执行零速停顿——将 curv 推入输出队列，curv ← nextCurv
%
% 此函数不修改 zspdmode 标记（调用前已由 create_zero_end 设置）。
% 推入后，两段曲线之间的速度将在插补阶段被约束为零。

ctx.q_smooth.push( curv );
curv = nextCurv;
end
