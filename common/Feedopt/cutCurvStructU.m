function [ u1_tilda ] = cutCurvStructU( ctx, curv, u0, L, isEnd )
%#codegen
% cutCurvStructU : 求截取点的全局参数值 u_tilda
%
% cutCurvStruct 的子函数，负责"在哪里切"。
% 给定从局部参数 u0 出发截取弧长 L，返回截点的全局参数 u_tilda。
% 全局参数通过 u_global = a_param * u_local + b_param 转换（见 cutCurvStruct）。
%
% 两种曲线类型的处理方式不同：
%   Spline  → ‖r'(u)‖ 不是常数，需弧长反求（二分法）
%   Line/Helix → ‖r'(u)‖ = 常数，直接 Δu = L / ‖r'‖
%
% Inputs :
%   ctx   : 上下文
%   curv  : 待截取曲线
%   u0    : 截取起始局部参数（通常 0 = 从起端，1 = 从末端）
%   L     : 截取弧长（mm）
%   isEnd : true = 从末端往回截；false = 从 u0 往前截
%
% Outputs :
%   u1_tilda : 截点的全局参数值；-1 表示截取失败
%

% 安全检查：若曲线总长 ≤ 要截取的长度，无法截取
if( LengthCurv( ctx, curv, 0, 1 ) <= L ), u1_tilda = -1; return; end

a = curv.a_param;   % 参数映射斜率
b = curv.b_param;   % 参数映射偏移
% 局部参数 u_l → 全局参数 u_g = a * u_l + b

if ( curv.Info.Type == CurveType.Spline )
    % Spline：‖r'(u)‖ 随参数变化，无解析公式，用弧长反求
    % a*u0+b 把局部参数 u0 转换为全局参数，再调用二分法
    spline = ctx.q_spline.get( curv.sp_index );
    u1_tilda = splineLengthFindU( ctx.cfg, spline, L, a * u0 + b, isEnd );
else
    % Line 和 Helix：均匀参数化（‖r'(u)‖ = 常数）
    % → 弧长 = ‖r'‖ × Δu → Δu = L / ‖r'‖，直接加减
    if( isEnd )
        % 从末端（u=1）往回截 L：新截点 = u0 - L/‖r'(u=1)‖
        [ ~, r1D1 ] = EvalCurvStruct( ctx, curv, 1 );
        u1 = u0 - L / MyNorm( r1D1 );
    else
        % 从起端（u=0）往前截 L：新截点 = u0 + L/‖r'(u=0)‖
        [ ~, r1D0 ] = EvalCurvStruct( ctx, curv, 0 );
        u1 = u0 + L / MyNorm( r1D0 );
    end
    % 把局部截点 u1 转换为全局参数
    u1_tilda = a * u1 + b;
end

end
