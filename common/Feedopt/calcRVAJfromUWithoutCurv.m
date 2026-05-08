function [ R, V, A, J ] = calcRVAJfromUWithoutCurv( ud_vec, ...
                          udd_vec, uddd_vec, r0D, r1D, r2D, r3D )
% calcRVAJfromUWithoutCurv : 链式法则核心计算
% 将弧长参数 u 的几何导数（r', r'', r'''）与时间导数（u', u'', u'''）组合，
% 得到时间域的位置/速度/加速度/跃度。
%
% 数学公式：
%   R =  r(u)                                         （位置，直接取值）
%   V =  r'(u) · u'                                   （速度，一阶链式法则）
%   A =  r''(u) · u'^2  +  r'(u) · u''               （加速度，二阶链式法则）
%   J =  r'''(u) · u'^3 + 3·r''(u)·u'·u''  + r'(u)·u'''（跃度，三阶链式法则）
%
% Inputs :
%   ud_vec   : [1×M] u'   = du/dt，进给率决定此值
%   udd_vec  : [1×M] u''  = d²u/dt²
%   uddd_vec : [1×M] u''' = d³u/dt³
%   r0D      : [N×M] r(u)   曲线位置
%   r1D      : [N×M] r'(u)  曲线一阶几何导数
%   r2D      : [N×M] r''(u) 曲线二阶几何导数
%   r3D      : [N×M] r'''(u) 曲线三阶几何导数
%
% Outputs :
%   R        : [N×M] 时间域位置
%   V        : [N×M] 时间域速度
%   A        : [N×M] 时间域加速度
%   J        : [N×M] 时间域跃度
%

R = r0D;                                                    % 位置直接等于几何位置

V = r1D .* ud_vec;                                          % V = r'·u'

A = r2D .* ud_vec .^2 + r1D .* udd_vec;                    % A = r''·u'^2 + r'·u''

J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec ...   % J = r'''·u'^3
    + r1D .* uddd_vec;                                      %   + 3·r''·u'·u'' + r'·u'''

end
