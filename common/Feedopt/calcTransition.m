function [ status, curv1C, curv2C, curvT, ret ] = ...
calcTransition( ctx, curv1, curv2 )
%#codegen
% calcTransition : 在两条相邻曲线间计算 G2 连续的 5 次多项式过渡曲线
%
% 过渡原理：
%   在曲线 curv1 末端和 curv2 起端各切掉一段长度 CutOff，
%   然后在切割点处用 G2 Hermite 插值构造 5 次多项式（TransP5），
%   保证过渡曲线与两端曲线在连接处满足：
%     C0（位置连续）、G1（切线方向连续）、G2（曲率连续）
%
% Inputs  :
%   ctx   : 上下文（含 CutOff 配置、运动学等）
%   curv1 : 当前曲线段（将被截短）
%   curv2 : 下一曲线段（将被截短）
%
% Outputs :
%   status : 计算结果（TransitionResult.Ok 或 NoSolution）
%   curv1C : 截短后的 curv1
%   curv2C : 截短后的 curv2
%   curvT  : 生成的 5 次多项式过渡曲线段
%   ret    : G2_Hermite 内部返回码（用于诊断）
%

coder.inline( "never" );

ret     = int32( 9 ); % 默认返回码（未执行到正常分支）
CutOff  = ctx.cfg.CutOff; % 过渡曲线切割长度（mm）
Lcut1   = CutOff; Lcut2 = CutOff;

% 计算两段曲线的总弧长
L1 = LengthCurv( ctx, curv1, 0, 1 );
L2 = LengthCurv( ctx, curv2, 0, 1 );

% 安全检查：若曲线太短（< 3×CutOff），无法切割，放弃过渡
if( ( L1 < 3 * Lcut1 ) || ( L2 < 3 * Lcut2 ) )
    curv1C  = curv1; curv2C  = curv2; curvT   = curv1;
    status  = TransitionResult.NoSolution;
    return;
end

% 切割 curv1：保留 [0, L1-CutOff] 部分（去掉末端 CutOff 长度）
[ ~, curv1C, ~ ] = cutCurvStruct( ctx, curv1, 0, L1-Lcut1, false );
ocn_assert( check_curv_length( ctx, curv1C, L1-Lcut1 ), ...
    "Curve Length not valide", mfilename );
% 切割 curv2：保留 [CutOff, L2] 部分（去掉起端 CutOff 长度）
[ ~, ~, curv2C ] = cutCurvStruct( ctx, curv2, 1, L2-Lcut2, true );
ocn_assert( check_curv_length( ctx, curv2C, L2-Lcut2 ), ...
    "Curve Length not valide", mfilename );

% 在切割点处求位置、一阶导、二阶导（用于 Hermite 插值的边界条件）
[r0D0, r0D1, r0D2] = EvalCurvStruct( ctx, curv1C, 1 ); % curv1 末端（u=1）
[r1D0, r1D1, r1D2] = EvalCurvStruct( ctx, curv2C, 0 ); % curv2 起端（u=0）

% G2 Hermite 插值：用两端的位置、一阶导、二阶导构造 5 次多项式
[p5, ret] = G2_Hermite_Interpolation_nAxis(ctx, r0D0, r0D1, r0D2, ...
                                                r1D0, r1D1, r1D2);

% 构造过渡曲线段（TransP5 类型）
R0T = zeros( length(ctx.cfg.maskTot), 1 ); R1T = R0T;
R0T( ctx.cfg.maskTot ) = r0D0; % 过渡段起点（在全轴坐标系中）
R1T( ctx.cfg.maskTot ) = r1D0; % 过渡段终点
curvT = constrTransP5Struct( curv1.Info, curv1.tool, R0T, R1T, p5 );
% 过渡曲线的加工参数取两段中的最小值（保守策略）
curvT.Info.SpindleSpeed = min( curv1.Info.SpindleSpeed, curv2.Info.SpindleSpeed );
curvT.Info.FeedRate     = min( curv1.Info.FeedRate,     curv2.Info.FeedRate );

% 根据 G2_Hermite 返回码确定过渡结果
if( ret == 1 )
    status = TransitionResult.Ok;         % 标准情况，正常构造
elseif( ret == 2 )
    status = TransitionResult.NoSolution; % 矩阵病态，无法求解
elseif( ret == 6 )
    % 数值警告，但仍构造过渡曲线（实际经验认为可接受）
    status = TransitionResult.Ok;
else
    status = TransitionResult.NoSolution;
end

% 额外检查：若多项式系数全部 ≤ 0，说明过渡曲线退化，放弃
if( ( status ~= TransitionResult.NoSolution ) && ...
    ( all( p5 <= 0, 'all' ) ) )
    status = TransitionResult.NoSolution;
    ret = int32( 7 );
end

% 验证 G2 连续性：检查连接处的位置、切线、曲率是否在容差内
if( status == TransitionResult.Ok )
    isValid = check_continuity( ctx, curv1C, curvT );
    isValid = isValid && check_continuity( ctx, curvT, curv2C );
    if( ~isValid )
        status = TransitionResult.NoSolution;
        ret = int32( 8 );
    end
end

end

%--------------------------------------------------------------------------

function [ isValid ] = check_continuity( ctx, curv1, curv2 )
% 验证两段曲线在连接处的 G2 连续性
tol         = ctx.cfg.Smoothing.ColTolSmooth;      % 位置容差
tol_cos     = ctx.cfg.Smoothing.ColTolCosSmooth;   % 切线角度容差（cos 值）
tol_kappa   = 1E-3;                                % 曲率容差

% 求 curv1 末端和 curv2 起端的位置、切线、曲率
[ r11, r1d1, r1dd1 ] = EvalCurvStruct( ctx, curv1, 1 ); % curv1 末端
[ r21, r2d1, r2dd1 ] = EvalCurvStruct( ctx, curv2, 0 ); % curv2 起端

% 从一阶/二阶导数计算切线 t、法线 n、曲率 κ
[t1, ~,  kappa1] = calc_t_nk_kappa( r1d1, r1dd1 );
[t2, ~,  kappa2] = calc_t_nk_kappa( r2d1, r2dd1 );

isC0    = all( abs( r11 - r21 ) < tol, 'all' ); % C0：位置连续
isG1    = collinear( t1, t2, tol_cos );          % G1：切线方向连续
isG2    = abs( kappa1 - kappa2 ) < tol_kappa;   % G2：曲率连续

isValid = isC0 && isG1 && isG2;
end

function [ isValid ] = check_curv_length( ctx, curv, L )
% 验证曲线切割后的实际弧长与期望弧长 L 的误差在容差内
tol = 1E-3;
isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
end
