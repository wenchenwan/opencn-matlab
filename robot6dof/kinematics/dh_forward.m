function [T, T_frames] = dh_forward(dh_params, q)
% dh_forward : 标准 DH 正运动学——计算末端齐次变换矩阵及中间坐标系
%
% 标准 DH 参数定义（Craig 约定）：
%   对第 i 个关节，从坐标系 {i-1} 到 {i} 的变换：
%     T_i = Rot_x(alpha_{i-1}) · Trans_x(a_{i-1}) · Rot_z(theta_i) · Trans_z(d_i)
%
%   dh_params 每行对应一个关节：
%     列 1 : a_{i-1}           — 连杆长度（m）
%     列 2 : d_i               — 关节偏距（m）
%     列 3 : alpha_{i-1}       — 连杆扭角（rad）
%     列 4 : theta_offset_i    — 关节角零位偏置（rad，叠加到关节变量 q_i 上）
%
% Inputs :
%   dh_params : [6×4] DH 参数矩阵
%   q         : [6×1] 关节角向量（rad）
%
% Outputs :
%   T        : [4×4] 末端齐次变换矩阵（基座→末端）
%   T_frames : {7×1} cell，T_frames{i} 为基座到第 i 个坐标系的变换
%              T_frames{1} = 单位阵（基座坐标系）
%              T_frames{2..7} = 各关节坐标系
%              T_frames{7} = T（末端坐标系，等于第一个输出）

n = size(dh_params, 1);  % 关节数（通常为 6）

T_frames = cell(n + 1, 1);
T_frames{1} = eye(4);   % 基座坐标系（世界坐标系）

T_cur = eye(4);

for i = 1:n
    a_im1    = dh_params(i, 1);   % a_{i-1}
    d_i      = dh_params(i, 2);   % d_i
    alpha_im1= dh_params(i, 3);   % alpha_{i-1}
    theta_off= dh_params(i, 4);   % theta_offset_i

    theta_i = q(i) + theta_off;   % 实际关节角 = 变量 + 零位偏置

    % 标准 DH 单步变换矩阵（4×4）
    % T_i = Tx(a_{i-1}) * Rx(alpha_{i-1}) * Rz(theta_i) * Tz(d_i)
    ct = cos(theta_i);
    st = sin(theta_i);
    ca = cos(alpha_im1);
    sa = sin(alpha_im1);

    % 展开后的复合变换矩阵（标准 DH 公式）
    T_i = [
        ct,      -st,       0,      a_im1;
        st*ca,    ct*ca,   -sa,    -sa*d_i;
        st*sa,    ct*sa,    ca,     ca*d_i;
        0,        0,        0,      1
    ];

    T_cur = T_cur * T_i;
    T_frames{i + 1} = T_cur;
end

T = T_cur;  % 末端变换矩阵

end
