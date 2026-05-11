function y = tridiag( a, b, c, f )
%#codegen
%  Solve the  n x n  tridiagonal system for y:
%
%  [ a(1)  c(1)                                  ] [  y(1)  ]   [  f(1)  ]
%  [ b(2)  a(2)  c(2)                            ] [  y(2)  ]   [  f(2)  ]
%  [       b(3)  a(3)  c(3)                      ] [        ]   [        ]
%  [            ...   ...   ...                  ] [  ...   ] = [  ...   ]
%  [                    ...    ...    ...        ] [        ]   [        ]
%  [                        b(n-1) a(n-1) c(n-1) ] [ y(n-1) ]   [ f(n-1) ]
%  [                                 b(n)  a(n)  ] [  y(n)  ]   [  f(n)  ]
%
%  The right hand side f may be a matrix composed of column vectors of length n
%  a, b, c must be vectors of length n (note that b(1) and c(n) are not used)

if( coder.target( "MATLAB" ) )
    % 如果在 MATLAB 环境中运行，使用 MEX 文件版本以提高性能
    y = tridiag_mex( a, b, c, f );
else
    % 纯 MATLAB 实现，使用 Thomas 算法求解三对角矩阵系统
    % some additional information is at the end of the file

    % 获取右端项 f 的尺寸，n 为行数（方程个数）
    [ n, ~ ]  = size( f );
    % 初始化临时向量 v，用于存储消去过程中的系数
    v         = zeros( n, 1 );
    % 初始化解向量 y，与 f 相同尺寸
    y         = zeros( size( f ) );
    % 初始化第一个对角元素 w = a(1)
    w         = a( 1 );
    % 计算第一个解分量 y(1,:) = f(1,:) / w
    y( 1, : ) = f( 1, : ) / w;  % 第一行无下对角元素，直接除以主对角元素 a(1)

    % 前向消去阶段：从第二个方程开始，逐步消去下对角元素
    for i = 2 : n
        % 计算消去系数 v(i-1) = c(i-1) / w
        v( i -1 ) = c( i -1 ) / w;
        % 更新 w = a(i) - b(i) * v(i-1)，这是修改后的主对角元素
        w         = a( i ) - b( i ) * v( i -1 );
        % 计算当前解分量 y(i,:) = (f(i,:) - b(i) * y(i-1,:)) / w
        y( i, : ) = ( f( i, : ) - b( i ) * y( i -1, : ) ) / w;
    end

    % 后向替换阶段：从倒数第二个方程开始，逐步回代求解
    for j = n-1 : -1 : 1
        % 更新 y(j,:) = y(j,:) - v(j) * y(j+1,:)
        y( j, : ) = y( j, : ) - v( j ) * y( j + 1, : );
    end

end

%  This is an implementation of the Thomas algorithm.  It does not overwrite a, b, c, f but
%  it does introduce a working n-vector (v).

%%%%%  Example
% n = 5; a = 4*ones(n,1); b = ones(n,1); c = 3*ones(n,1);
% f = rand(n,1);
% y = tridiag(a,b,c,f);
%%%%%  check solution
% A = diag(a,0) + diag(ones(n-1,1),-1) + diag(3*ones(n-1,1),1)
% A*y - f

%%%%% Conditions that will guarantee the matrix equation can be solved using this algorithm:
%%%%%  1. matrix strictly diagonally dominant
%%%%%  2. matrix diagonally dominant, c_i not zero for all i, and abs(b_n) < abs(a_n)

%  It has been tested on MATLAB, version R2010b and version R2012a
%  version: 1.0
%  March 9, 2013

