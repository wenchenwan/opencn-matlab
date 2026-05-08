function [ L ] = LengthCurv( ctx, curv, u0, u1 )
% LengthCurv : 计算曲线在局部参数 [u0, u1] 区间内的弧长
%
% 弧长通用公式：L = ∫_{u0}^{u1} ‖r'(u)‖ du
% 四种曲线类型的 ‖r'(u)‖ 性质不同，采用不同策略：
%
%   Line   : r'(u) = P1-P0（常向量）→ L = ‖P1-P0‖ × (u1-u0)，O(1)
%   Helix  : ‖r'(u)‖ 也是常数（旋转分量与轴向分量正交）→ 同 Line，O(1)
%   Spline : ‖r'(u)‖ 随 u 变化 → 查预建 Lk 表 + 边界 GL 积分，O(K)
%   TransP5: 极短过渡曲线（~0.2mm）→ 中点法近似（9 段），O(1)
%
% Inputs :
%   ctx  : 上下文（含 q_spline 队列和配置）
%   curv : 曲线结构体（CurvStruct）
%   u0   : 起始局部参数（∈ [0,1]）
%   u1   : 终止局部参数（∈ [0,1]，u1 > u0）
%
% Outputs :
%   L : 弧长（mm）
%

if ( curv.Info.Type == CurveType.Helix ) || ...
   ( curv.Info.Type == CurveType.Line )
    % Line/Helix：‖r'(u)‖ 为常数，在 u0 处求一次导即可
    % EvalCurvStruct 已按链式法则将 r1D 乘以 a_param，
    % 所以 ‖r1D‖ × (u1-u0) 直接给出子段弧长（局部参数域）
    [~, r1D] = EvalCurvStruct( ctx, curv, u0 );
    L        = MyNorm( r1D ) * ( u1 - u0 );

elseif ( curv.Info.Type == CurveType.Spline )
    % Spline：先把局部参数转换为全局参数，再调用 splineLength
    % splineLength 内部用 Lk 预计算表（中间完整区间查表，边界 GL 积分）
    a        = curv.a_param;
    b        = curv.b_param;
    u0_tilda = a * u0 + b;   % 局部 → 全局
    u1_tilda = a * u1 + b;
    spline   = ctx.q_spline.get( curv.sp_index );
    [ L ]    = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda );

elseif ( curv.Info.Type == CurveType.TransP5 )
    % TransP5：5次多项式，导数可解析求出，但模长积分无闭合式
    % 用中点法（9段）近似，对极短（~0.2mm）的过渡曲线精度足够
    a        = curv.a_param;
    b        = curv.b_param;
    u0_tilda = a * u0 + b;
    u1_tilda = a * u1 + b;
    L = TransP5LengthApprox( curv, u0_tilda, u1_tilda );

else
    ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV", mfilename );
    L = 0;
end

end
