function [ n ] = MyNorm( x )
% MyNorm : 向量欧几里得范数（‖x‖₂ = sqrt(Σ xᵢ²)）
%
% 使用 mysqrt 而非内建 norm，以兼容 codegen（MATLAB Coder 生成 C 代码）。
% coder.inline('always') 指示 Coder 将此函数内联，消除调用开销。
%
% Inputs :
%   x : 输入向量（任意维数的列向量或行向量）
%
% Outputs :
%   n : 欧几里得范数（标量，‖x‖₂）
%
coder.inline( 'always' );
n = mysqrt( sum( x.^2 ) );
end
