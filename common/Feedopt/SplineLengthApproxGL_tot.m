function [ L, Lk ]  = SplineLengthApproxGL_tot( cfg, Curv )
% SplineLengthApproxGL_tot : 预计算 B 样条各节点区间的弧长（一次性，结果复用）
%
% 弧长反演（splineLengthFindU）的"粗查表"由此函数建立。
% B 样条节点向量把参数域分成 K 个区间（去掉端点重节点后），
% 对每个区间 [t_k, t_{k+1}] 用 GL-5 积分预算弧长，存入 Lk：
%
%   Lk[k] = ∫_{t_k}^{t_{k+1}} ‖r'(u)‖ du
%
% 此函数只需调用一次（在 initFeedoptPlan 阶段），后续截取/查询复用 Lk。
%
% Inputs :
%   cfg  : 配置结构体（含 GaussLegendreN/X/W）
%   Curv : 样条曲线结构体（Curv.sp 含节点向量和 B 样条数据）
%
% Outputs :
%   L  : 总弧长（所有区间之和，mm）
%   Lk : 各节点区间弧长向量（长度 = 节点数 - 1）
%

sp    = Curv.sp;
Knots = sp.knots(4:end-3);   % 去掉端点重节点（夹紧样条两端各有 3 个重节点）
a     = Knots(1:end-1);      % 各区间左端
b     = Knots(2:end);        % 各区间右端

GL_N = cfg.GaussLegendreN;   % GL 节点数（= 5）
GL_X = cfg.GaussLegendreX;   % GL 节点坐标（在 [-1,1] 上）
GL_W = cfg.GaussLegendreW;   % GL 权重

% 将所有区间的 GL 节点批量映射到各自的 [a_k, b_k]
% Umat: GL_N × K 矩阵，每列是一个区间的 GL 节点
Umat = (bsxfun(@times, a, (1-GL_X)) + bsxfun(@times, b, (1+GL_X))) / 2;
Uvec = Umat(:)';   % 展平为行向量，一次性求值

% 批量计算所有节点处的参数导数 ‖r'(u)‖
[~, r1D]   = EvalBSpline(Curv, Uvec);
r1Dnorm    = MyNorm(r1D);

% 按区间重组，每列做 GL 加权求和 → 各区间弧长
r1DnormM = reshape(r1Dnorm, GL_N, length(Knots)-1);
Lk       = sum(bsxfun(@times, GL_W, r1DnormM)) .* (b-a) / 2;

L = sum(Lk);
