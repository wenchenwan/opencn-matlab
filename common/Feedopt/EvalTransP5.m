function [ r_0D, r_1D, r_2D, r_3D ] = EvalTransP5( CurvStruct, u_vec, maskTot )
%#codegen
% EvalTransP5 : 在给定参数点处求五次多项式过渡曲线的位置和各阶导数
%
% 过渡曲线用五次多项式描述（G2 Hermite 插值结果），系数存于 CoeffP5。
% CoeffP5 是 [NDim × 6] 矩阵，每行对应一个轴，每列对应一个多项式系数：
%   r_j(u) = c0 + c1·u + c2·u² + c3·u³ + c4·u⁴ + c5·u⁵   (j = 轴序号)
%
% 各阶导数通过对系数逐阶差分求得（mypolyder）：
%   r'(u)  = 导数系数按 mypolyval 求值
%   r''(u) = 二阶导数系数求值
%   r'''(u)= 三阶导数系数求值
%
% 注意：u_vec 是全局参数（已经过 a_param/b_param 映射），
%       外部链式法则补偿由 EvalCurvStructNoCtx 负责（r1D×a, r2D×a², r3D×a³）。
%
% Inputs :
%   CurvStruct : 曲线结构体（含 CoeffP5 [NDim×6] 和 maskTot）
%   u_vec      : 全局参数向量
%   maskTot    : 全轴掩码（选出激活轴）
%
% Outputs :
%   r_0D : [sum(maskTot) × N] 位置
%   r_1D : [sum(maskTot) × N] 一阶导
%   r_2D : [sum(maskTot) × N] 二阶导
%   r_3D : [sum(maskTot) × N] 三阶导
%

if ~coder.target('MATLAB')
    coder.cinclude('common/tracy/Tracy.hpp');
    coder.inline('never')
    coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalTransP5"'));
end

p5    = CurvStruct.CoeffP5;       % [NDim × 6] 五次多项式系数
p5_1D = mypolyder( p5 );          % 一阶导系数 [NDim × 5]
p5_2D = mypolyder( p5_1D );       % 二阶导系数 [NDim × 4]
p5_3D = mypolyder( p5_2D );       % 三阶导系数 [NDim × 3]

% 在 u_vec 各点处求值（mypolyval 逐行对每个轴多项式求值）
D0 = mypolyval( p5,    u_vec );   % 位置    [NDim × N]
D1 = mypolyval( p5_1D, u_vec );   % 一阶导  [NDim × N]
D2 = mypolyval( p5_2D, u_vec );   % 二阶导  [NDim × N]
D3 = mypolyval( p5_3D, u_vec );   % 三阶导  [NDim × N]

% 用 maskTot 选出激活轴（去掉未使用的轴，如 A 轴）
r_0D = D0( maskTot, : );
r_1D = D1( maskTot, : );
r_2D = D2( maskTot, : );
r_3D = D3( maskTot, : );
