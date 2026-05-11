function [ spnD ] = CalcBspline_Lee( cfg, points )
% CalcBspline_Lee : Lee 算法——将折线端点序列拟合为夹持 B 样条曲线
%
% 算法分四步：
%   1. 1/4 幂弦长参数化：将折线端点映射到参数域 [0,1]
%   2. 构造夹持节点向量 + 自然端点边界条件（r''=0）
%   3. 组装插值线性方程组 A·C = B
%   4. Thomas 算法 O(N) 求解三对角方程组，得控制点 C
%
% Inputs :
%   cfg    : 配置结构体（含 LeeSplineDegree、NumberAxis 等）
%   points : [nAxis × N] 折线端点坐标矩阵（每列一个端点）
%
% Outputs :
%   spnD   : B 样条结构体（含控制点、节点向量、基函数对象）

[ ~, N ] = size( points );
nAxis    = cfg.NumberAxis;
nMult    = cfg.LeeSplineDegree - 1;  % 端部节点重复数（夹持 B 样条）
nCoeff   = N + 2;                    % 控制点数 = 端点数 + 2（加入边界条件）

% ── 步骤 1：1/4 幂弦长参数化 ────────────────────────────────────────────
% 计算每段弦长的 1/2 次幂（即 ‖ΔP_k‖^(1/2)，由 du^(1/4) 得来）
% 相比均匀参数化（α=0）和弦长参数化（α=1），1/4 幂（α=1/4）在曲率
% 变化较大处能更均匀地分配参数，减少振荡和拟合误差。
du = sum( ( diff( points.' ).^2 ).' );   % 各段弦长的平方 ‖ΔP_k‖²
u  = cumsum( [ 0, du.^( 1 / 4 ) ] );    % 累积 1/4 幂弦长
u  = u / u( end );                        % 归一化到 [0, 1]

% ── 步骤 2：构造夹持节点向量 ────────────────────────────────────────────
% 在两端各补 nMult 个重复节点（0 和 1），形成夹持（clamped）B 样条：
%   - 保证曲线严格通过首尾端点
%   - 端点处切线由相邻控制点决定，行为直观可控
knots = [ zeros( 1, nMult ), u, ones( 1, nMult ) ];

Bl = bspline_create( cfg.LeeSplineDegree, u );

% bspline_eval_lee 返回三个基函数矩阵：
%   BasisVal   : 各参数点处的基函数值（用于插值约束 r(u_k) = P_k）
%   BasisValDD0: 起端二阶导基函数值（用于自然边界条件 r''(0) = 0）
%   BasisValDD1: 末端二阶导基函数值（用于自然边界条件 r''(1) = 0）

% BasisVal实际上是一个 N×N 的矩阵, 其中就表示计算了[1 t t^2 t^3] * T_Mat表示其中的一行的中的支撑点附近的基函数值
% P(t) = [1 t t^2 t^3] * T_Mat * [P0; P1; P2; P3]
[ BasisVal, BasisValDD0, BasisValDD1 ] = bspline_eval_lee( Bl, int32( nCoeff ), u );

% ── 步骤 3：组装线性方程组 A·C = B ──────────────────────────────────────
% A 的结构（从上到下）：
%   第1行  : 起端 r''=0 约束（BasisValDD0）
%   中间行 : 插值约束 r(u_k) = P_k（BasisVal，每行对应一个端点）
%   最后行 : 末端 r''=0 约束（BasisValDD1）

% 这里BasisVal实际上表示的是基函数在各个参数点的值
A = [ BasisValDD0; BasisVal; BasisValDD1 ];

% B 的结构（对应右端项）：
%   第1行  : 起端导数目标 = 0
%   中间行 : 插值目标坐标（折线各端点）
%   最后行 : 末端导数目标 = 0
B = [ zeros( 1, nAxis );
      points.';
      zeros( 1, nAxis ) ];

% ── 步骤 4：Thomas 算法求解三对角方程组 ─────────────────────────────────
% swap_lines 交换边界行（第1↔2行，倒数第1↔2行），使 A 变为严格三对角形式：
%   原始排列：边界条件行在首尾，不在对角线带上
%   交换后  ：边界条件行归入对角线带，整体变为三对角矩阵
%   意义    ：Thomas 算法要求严格三对角，swap 是使其满足条件的预处理步骤
[ A ] = swap_lines( A );
[ B ] = swap_lines( B );

% 提取三对角矩阵的三条带（主对角、下对角、上对角）
[ v_m, v_l, v_u ] = extract_vectors( A );

% Thomas 算法：O(N) 前向消元 + 回代，远优于 Gaussian 消元的 O(N³)
% 解出控制点矩阵 c，每行对应一个控制点（各轴坐标）
c = tridiag( v_m, v_l, v_u, B );

spnD = constrSpline( c.', knots, Bl );
end


function [ M ] = swap_lines( M )
% swap_lines : 交换矩阵首尾两对行，使矩阵变为三对角形式
%
% 交换方案：行1↔行2，行(end-1)↔行end
% 原因：bspline_eval_lee 将边界条件行（DD0/DD1）放在第1和最后1行，
%       而插值行放在第2和倒数第2行；交换后边界行归入对角线带，
%       整体矩阵满足 Thomas 算法所要求的三对角结构。
M( [ 1, 2, end-1, end ], : ) = M( [ 2, 1, end, end-1 ], : );
end

function [ v_m, v_l, v_u ] = extract_vectors( A )
% extract_vectors : 从三对角矩阵中提取三条对角带
%
% Outputs :
%   v_m : 主对角线向量（长度 N）
%   v_l : 下对角线向量（长度 N，首元素补 0）
%   v_u : 上对角线向量（长度 N，末元素补 0）
v_m = diag( A );
v_l = [ 0; diag( A, -1 ) ];   % 下对角补首 0，与主对角对齐
v_u = [ diag( A, 1 ); 0 ];    % 上对角补末 0，与主对角对齐
end
