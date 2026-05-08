function [ r0D, r1D, r2D, r3D ] = EvalHelix( CurvStruct, u_vec, maskCart )
% EvalHelix : 在给定参数点处求圆弧/螺旋线的位置和各阶参数导数
%
% 螺旋线参数化（φ = θ·u，θ = 总圆心角，p = 螺距，ê = 轴向单位向量）：
%
%   r(u) = C + cos(φ)·CP0 + sin(φ)·(ê × CP0) + (p/2π)·φ·ê
%
%   其中：CP0 = P0 - C（圆心到起点的向量，‖CP0‖ = R 为半径）
%         ê × CP0  是 CP0 绕 ê 旋转 90° 的向量（顺时针切线方向）
%
% 一阶导（对 u 求导，φ = θ·u → dφ/du = θ）：
%   r'(u) = θ·[-sin(φ)·CP0 + cos(φ)·(ê×CP0)] + θ·(p/2π)·ê
%            ←─────────────────────────────────→   ←──────────→
%                    旋转分量（圆周方向）              轴向分量
%
% 二阶导：
%   r''(u) = -θ²·cos(φ)·CP0 - θ²·sin(φ)·(ê×CP0)
%           = -θ²·[cos(φ)·CP0 + sin(φ)·(ê×CP0)]
%   （始终指向圆心方向，即向心加速度）
%
% 三阶导：
%   r'''(u) = θ³·[sin(φ)·CP0 - cos(φ)·(ê×CP0)]
%
% 模长性质：
%   ‖r'(u)‖² = θ²R²(sin²φ + cos²φ) + (θp/2π)² = θ²R² + (θp/2π)² = const
%   ‖r'(u)‖ 为常数（旋转分量与轴向分量正交），弧长均匀。
%   纯圆弧（p=0）时 ‖r'(u)‖ = θR（速度 = 角速度 × 半径）。
%
% Inputs :
%   CurvStruct : 曲线结构体，含：
%       R0     : 起点全轴坐标
%       R1     : 终点全轴坐标
%       evec   : 螺旋轴方向单位向量 ê（3×1）
%       theta  : 总圆心角（rad，可正可负）
%       pitch  : 螺距（mm/圈，纯圆弧时 = 0）
%       CorrectedHelixCenter : 修正后的圆心 C
%   u_vec      : 全局参数向量（已经过 a_param/b_param 映射）
%   maskCart   : 笛卡尔轴掩码（选出 X/Y/Z 等参与圆弧的轴）
%
% Outputs :
%   r0D : [NCart × N] 位置
%   r1D : [NCart × N] 一阶参数导数
%   r2D : [NCart × N] 二阶参数导数
%   r3D : [NCart × N] 三阶参数导数
%

if ~coder.target('MATLAB')
    coder.cinclude('common/tracy/Tracy.hpp');
    coder.inline('never')
    coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalHelix"'));
end

P0    = CurvStruct.R0( maskCart );
evec  = CurvStruct.evec;
theta = CurvStruct.theta;    % 总圆心角（rad）
pitch = CurvStruct.pitch;    % 螺距（mm/圈）

C    = CurvStruct.CorrectedHelixCenter;   % 修正圆心
CP0  = P0 - C;                            % 圆心 → 起点向量（‖CP0‖ = R）

phi_vec  = theta * u_vec;                 % 各点的圆心角 φ(u) = θ·u
EcrCP0   = cross( evec, CP0 );           % ê × CP0：CP0 旋转 90° 的向量（切线方向）

cphi = mycos( phi_vec );   % cos(φ)，逐点
sphi = mysin( phi_vec );   % sin(φ)，逐点

% 预计算四个分量（避免重复乘法）
cphiTCP0    = CP0  * cphi;       % cos(φ)·CP0     [NCart × N]
sphiTCP0    = CP0  * sphi;       % sin(φ)·CP0
cphiTEcrCP0 = EcrCP0 * cphi;    % cos(φ)·(ê×CP0)
sphiTEcrCP0 = EcrCP0 * sphi;    % sin(φ)·(ê×CP0)

% 位置：r(u) = C + cos(φ)·CP0 + sin(φ)·(ê×CP0) + (p/2π)·φ·ê
r0D = bsxfun(@plus, C, cphiTCP0 + sphiTEcrCP0 + ...
              pitch / (2*pi) * evec * phi_vec);

% 一阶导：r'(u) = θ·[-sin(φ)·CP0 + cos(φ)·(ê×CP0)] + θ·(p/2π)·ê
r1D = bsxfun(@plus, -theta * sphiTCP0 + theta * cphiTEcrCP0, ...
              theta * pitch / (2*pi) * evec);

% 二阶导：r''(u) = -θ²·[cos(φ)·CP0 + sin(φ)·(ê×CP0)]  （向心加速度，无轴向项）
r2D = -theta^2 * cphiTCP0 - theta^2 * sphiTEcrCP0;

% 三阶导：r'''(u) = θ³·[sin(φ)·CP0 - cos(φ)·(ê×CP0)]
r3D =  theta^3 * sphiTCP0 - theta^3 * cphiTEcrCP0;
