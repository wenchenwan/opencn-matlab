function [ L ] = TransP5LengthApprox( CurvStruct, u0, u1 )
%#codegen
% TransP5LengthApprox : 用中点积分法近似计算 5 次多项式过渡曲线的弧长
%
% 5 次多项式的参数导数 p5'(u) 有解析表达式（mypolyder），
% 但 ‖p5'(u)‖ 的积分没有闭合形式，需要数值方法。
%
% 由于过渡曲线极短（CutOff = 0.1mm，总长约 0.2mm），
% 用中点积分法（9 个子区间）近似精度足够：
%
%   L ≈ Σ_{k=1}^{9} ‖p5'(u_mid_k)‖ × Δu
%
% 中点法误差 O(h²)，h = Δu/9 ≈ 0.11/9，满足工程精度要求。
%
% Inputs :
%   CurvStruct : 曲线结构体（含 CoeffP5：5次多项式系数矩阵）
%   u0         : 积分起点（全局参数）
%   u1         : 积分终点（全局参数）
%
% Outputs :
%   L : 弧长近似值（mm）
%

p5    = CurvStruct.CoeffP5;
p5_1D = mypolyder( p5 );   % 对多项式系数求导，得到 p5'(u) 的系数

% 将 [u0, u1] 均匀分成 9 个子区间（10 个端点）
u_vec   = linspace( u0, u1, 10 );
u_mid   = 0.5 * ( u_vec( 1 : end-1 ) + u_vec( 2 : end ) );  % 各子区间中点
du      = diff( u_vec );                                       % 各子区间宽度（等距）

% 在各中点处求导数向量 p5'(u_mid)，取模得到速度（弧长微元密度）
Integrand = mysqrt( sum( mypolyval( p5_1D, u_mid ) .^ 2 ) );

% 中点法：弧长 = Σ 速度 × 子区间宽度
L = sum( Integrand .* du );
