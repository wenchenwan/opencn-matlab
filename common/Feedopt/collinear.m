function [ valid ] = collinear( u, v, tol_cos )
% collinear : 判断两向量是否共线（方向相同），基于余弦角容差
%
% 【判断原理】
%   两单位向量 u/‖u‖ 与 v/‖v‖ 的夹角余弦：
%     cos(θ) = (u·v) / (‖u‖·‖v‖)
%   当 cos(θ) ≥ tol_cos 时认为两向量共线（方向相同）。
%
%   典型用法（smoothCurvStructs 中 G1 检查）：
%     tol_cos ≈ cos(0.1°) ≈ 0.9999985
%   即允许切向量夹角最大约 0.1°，超过则认为不连续（需要过渡曲线）。
%
%   注意：此函数检查的是"方向相同"（cos ≥ 0），不检查"方向相反"（反向共线）。
%   在 G1 连续性检查中，两端切向量应方向一致（曲线方向一致性保证）。
%
% 退化情况：
%   若任一向量模长 < eps（接近零向量），视为共线（返回 true）。
%   这处理了直线端点处切向量数值为零的特殊情形。
%
% Inputs :
%   u       : R^n 中的向量（任意维数）
%   v       : R^n 中的向量（与 u 同维）
%   tol_cos : 余弦容差（判断阈值）
%
% Outputs :
%   valid   : 逻辑值，true = 两向量共线（夹角余弦 ≥ tol_cos）
%

    % 退化：零向量视为共线（避免除零）
    if ( norm( u ) < eps || norm( v ) < eps )
        valid = true;
        return;
    end
    % cos(θ) = u·v / (‖u‖·‖v‖)
    cos_angle   = dot( u, v ) / ( MyNorm( u ) * MyNorm( v ) );
    valid       = ( cos_angle >= tol_cos );
end
