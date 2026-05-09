function [ y ] = mypolyval( p, x )
% mypolyval : 计算一组多项式在给定 x 值处的值。
%
% 输入 :
%   p : [nD x nc] 的多项式系数矩阵。
%       每一行对应一个多项式。
%       系数按降幂顺序存储：
%           p(:,1)*x^(nc-1) + p(:,2)*x^(nc-2) + ... + p(:,nc)
%   x : 要求值的 x 向量。
%
% 输出 :
%   y : [nD x length(x)] 的多项式值矩阵。
%       y(i,j) 为第 i 条多项式在 x(j) 处的值。
%
[ nD, nc ] = size( p );
siz_x      = length( x );
%
% 对于 x 为数组的情形，采用 Horner 法计算。
% Horner 法减少乘法次数，并具有较好的数值稳定性。
y = zeros( nD, siz_x );
if nc > 0
    % 先使用每个多项式的最高阶系数作为初始值。
    y( : ) = repmat( p( :, 1 ), 1, siz_x ); 
end
for i = 2 : nc
    % y = y .* x + 下一个系数
    y = repmat( x, nD, 1 ) .* y + repmat( p( :, i ), 1, siz_x );
end
