% computes the local Frenet frame (t, n, b) of a curve in R^n
% [t, nk, kappa] = calc_t_nk_kappa(rD1, rD2)
% where rD1 is the first derivative and rD2 the second one
function [ t, nk, kappa ] = calc_t_nk_kappa( rD1, rD2 )
% calc_t_nk_kappa : 从参数导数计算曲线的 Frenet 框架（切向 t、法向 nk、曲率 kappa）
%
% 【公式推导】
%   设曲线 r(u)，一阶导 r'=rD1，二阶导 r''=rD2。
%
%   切向量（单位化）：
%     t = r' / ‖r'‖
%
%   法向量（Gram-Schmidt 正交化，去除 r'' 中平行于 r' 的分量）：
%     r''_perp = r'' - (r''·r')/‖r'‖² · r'       （r'' 在 r' 法平面内的投影）
%     nk = r''_perp / ‖r'‖²
%
%   曲率（Lagrange 恒等式：‖a×b‖² = ‖a‖²·‖b‖² - (a·b)²，推广到 Rⁿ）：
%     κ = ‖r' × r''‖ / ‖r'‖³
%       = sqrt(‖r'‖²·‖r''‖² - (r'·r'')²) / ‖r'‖³
%
%   注意：
%     - 这些公式是几何量（与参数化无关）。在 EvalCurvStructNoCtx 中，
%       r'是对局部参数 u_l 的导数（已乘 a_param 链式法则补偿），
%       因此传入本函数前应确保导数已正确缩放。
%     - num 可能因浮点误差出现负值（理论 ≥ 0），夹到 0 防止 sqrt 产生 NaN。
%
% Inputs :
%   rD1 : 一阶参数导数向量（列向量或矩阵，每列为一个采样点）
%   rD2 : 二阶参数导数向量
%
% Outputs :
%   t     : 单位切向量（与 rD1 方向相同）
%   nk    : 法向量（Gram-Schmidt 正交化后未单位化，模长 = κ）
%   kappa : 曲率标量（κ = 1/R，R 为曲率半径；直线处 κ=0）
%

norm_rD1    = vecnorm( rD1 );          % ‖r'‖
norm_rD1_2  = norm_rD1.^2;             % ‖r'‖²
norm_rD1_3  = norm_rD1_2 .* norm_rD1; % ‖r'‖³
norm_rD2    = vecnorm( rD2 );          % ‖r''‖
norm_rD2_2  = norm_rD2.^2;             % ‖r''‖²
dot_rD1_rD2 = dot( rD2, rD1 );        % r'·r''

% 切向量：t = r' / ‖r'‖
t = rD1 / norm_rD1;

% 法向量：nk = (r'' - r'·(r'·r'')/‖r'‖²) / ‖r'‖²
% 即 r'' 在 r' 法平面内的分量，再除以 ‖r'‖²（使 ‖nk‖ = κ/‖r'‖ 形式）
nk          = ( rD2 - rD1 .* dot_rD1_rD2 ./ norm_rD1_2 ) ./ norm_rD1_2;

% 曲率：κ = sqrt(‖r'‖²·‖r''‖² - (r'·r'')²) / ‖r'‖³
% 分子 = ‖r' × r''‖（Lagrange 恒等式推广到 Rⁿ，无需显式叉积）
num         = norm_rD2_2 .* norm_rD1_2 - dot_rD1_rD2.^2;

% 防止浮点误差导致 num 略小于 0（理论上 num ≥ 0）
num( num < 0 ) = 0;
kappa       = mysqrt( num ) ./ norm_rD1_3;

end
