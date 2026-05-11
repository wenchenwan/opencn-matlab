function [x, w]=lgwt(N, a, b)
% lgwt.m
%
% This function precalculates Gauss-Legendre points and weights for computing 
% definite numerical integration (quadrature) on an interval [a,b] 
% using N evaluations of the function being integrated. 
%
% Suppose you have a continuous function f(x) which is defined on [a,b]
% which you can evaluate at any x in [a,b]. Simply evaluate it at all of
% the values contained in the x vector to obtain a vector f. Then compute
% the definite integral using sum(f.*w);
%
% Written by Greg von Winckel - 02/25/2004
% N 点 GL 需要求 N 次 Legendre 多项式 P_N 的 N 个根；降阶后统一用下标
N=N-1;
N1=N+1;   % 节点总数（= 输入 N）
N2=N+2;   % 递推终止列索引，权重公式中作缩放补偿用

% 均匀节点，仅用于初始猜测中的扰动项，不是 GL 节点
xu=linspace(-1,1,N1)';

% 初始猜测：Chebyshev 节点近似 P_{N1} 的根，加 Lether 扰动提升收敛速度
%   Chebyshev 节点：cos((2k+1)π / (2N+2))，k=0,...,N
%   扰动项：(0.27/N1)*sin(π*xu*N/N2) 减少迭代次数
y=cos((2*(0:N)'+1)*pi/(2*N+2))+(0.27/N1)*sin(pi*xu*N/N2);

% L 为 Legendre-Gauss Vandermonde 矩阵，N1×N2
% 约定：L(:,k) 存放 P_{k-1}(y)，即第 k 列为 k-1 次 Legendre 多项式
L=zeros(N1,N2);

% Lp：P_{N1}(y) 的（缩放）导数，用于 Newton-Raphson 分母
Lp=zeros(N1,1);

% 初始旧点设为 2，保证 max|y-y0|>eps，使循环至少执行一次
y0=2*ones(N+1, 1);

% Newton-Raphson 迭代：迭代到所有节点收敛到机器精度
while max(abs(y-y0))>eps

    % Bonnet 递推初始条件
    L(:,1)=1;   % P_0(y) = 1
    L(:,2)=y;   % P_1(y) = y

    % Bonnet 三项递推：k·P_k(y) = (2k-1)·y·P_{k-1}(y) − (k-1)·P_{k-2}(y)
    % 循环结束后 L(:,N2) = P_{N1}(y)，其根即为 GL 节点
    for k=2:N1
        L(:,k+1)=( (2*k-1)*y.*L(:,k)-(k-1)*L(:,k-1) )/k;
    end

    % 导数公式：(1−y²)·P'_n(y) = n·(P_{n-1}(y) − y·P_n(y))，取 n=N1
    % 此处用 N2（= N1+1）替代 N1，引入因子 N2/N1，在权重公式中用 (N2/N1)² 补偿
    Lp=(N2)*( L(:,N1)-y.*L(:,N2) )./(1-y.^2);

    y0=y;
    % Newton-Raphson 更新：y ← y − P_{N1}(y) / P'_{N1}(y)
    y=y0-L(:,N2)./Lp;

end

% 线性映射：将 [-1,1] 上的 GL 节点变换到目标区间 [a,b]
%   x = a*(1-y)/2 + b*(1+y)/2
x=(a*(1-y)+b*(1+y))/2;

% GL 权重公式：w_i = (b-a) / ((1−x_i²)·[P'_{N1}(x_i)]²)
% 因 Lp 比真实导数大 N2/N1 倍，故乘以 (N2/N1)² 补偿
w=(b-a)./((1-y.^2).*Lp.^2)*(N2/N1)^2;