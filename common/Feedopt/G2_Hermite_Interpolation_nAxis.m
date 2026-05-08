%
%     This file is part of the Optimal G^2 Hermite Interpolation Software.
%
%     Copyright (C) 2017-2019 Raoul Herzog, Philippe Blanc
%                             mecatronYx group at HEIG-VD
%                             University of Applied Sciences Western Switzerland
%                             CH-1401 Yverdon-les-Bains
%                             All rights reserved.
%
%     This is free software; you can redistribute it and/or
%     modify it under the terms of the GNU Lesser General Public
%     License as published by the Free Software Foundation; either
%     version 3 of the License, or (at your option) any later version.
%
%     This software is distributed in the hope that it will be useful,
%     but WITHOUT ANY WARRANTY; without even the implied warranty of
%     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
%     Lesser General Public License for more details.
%
%     You should have received a copy of the GNU Lesser General Public
%     License along with this software; if not, write to the Free Software
%     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
%
%
% [p5_3D, alpha0, alpha1] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2)
%
% Compute an optimal trajectory in R^3, connecting the point r0 to r1 with
% C^2 smoothness while minimizing the integral of the norm of the third
% derivative.
function [ p5, status, alpha0, alpha1 ] = G2_Hermite_Interpolation_nAxis( ...
    ctx, r0D0_in, r0D1_in, r0D2_in, r1D0_in, r1D1_in, r1D2_in )
% G2_Hermite_Interpolation_nAxis : 最优 G2 Hermite 插值——生成五次多项式过渡曲线
%
% 【算法概述】
%   给定两条曲线在连接点处各阶导数（位置/切向/曲率），构造一条五次多项式过渡曲线，
%   使其满足 G2 连续条件（位置、切向、曲率在两端均连续），
%   并最小化三阶导数范数的积分（即最小化"跃度代价"）。
%
%   参考文献：Herzog & Blanc, "Optimal G^2 Hermite Interpolation for 3D Curves",
%             HEIG-VD mecatronYx group, 2017–2019。
%
% 【参数化与边界条件】
%   过渡曲线用五次多项式描述，参数 u ∈ [0,1]：
%     r(u) = Σ_{j=0}^{5} c_j · u^j
%
%   边界条件（G2 = C0 + G1 + G2）：
%     位置：r(0) = r0D0，r(1) = r1D0
%     切向：r'(0) ∝ t0（方向一致即可，不要求模长），r'(1) ∝ t1
%     曲率：κ(0) = κ0，κ(1) = κ1
%
%   G2 边界条件用 Frenet 框架参数化为：
%     r'(0)  = alpha0 · t0                     （一阶导方向 = 切向，模长自由度 alpha0）
%     r''(0) = beta0  · t0 + alpha0² · n0·κ0   （二阶导含切向分量 beta0 和法向曲率项）
%   同理在 u=1 处用 alpha1, beta1。
%
%   alpha0, alpha1 > 0 是主自由度（控制过渡曲线的"拉伸"），
%   beta0, beta1 由 alpha0, alpha1 通过线性方程唯一确定（Calc_beta0_beta1）。
%
% 【求解流程】
%   将边界条件代入 G2 约束后，得到关于 alpha0, alpha1 的多项式方程组：
%     p1(alpha0, alpha1) = 0   （由左端 G2 导出）
%     p2(alpha0, alpha1) = 0   （由右端 G2 导出）
%   方程形式（CoefPolySys 计算系数）：
%     p1 = (a1·α1+a0)·α0² + (b1·α1+b0)·α0 + c3·α1³+c2·α1²+c1·α1+c0
%     p2 = (d1·α0+d0)·α1² + (e1·α0+e0)·α1 + f3·α0³+f2·α0²+f1·α0+f0
%
%   按曲率是否为零分四种情况求解（详见后文各分支注释）。
%   若有多个正实根，取最小化代价积分（EvalCostIntegral）的解。
%
%   最终用六个 Hermite 基函数 h00..h21 构造多项式系数矩阵 p5 [NDim × 6]。
%
% Inputs :
%   ctx     : 计算链上下文（含 cfg.maskTot / cfg.D 等）
%   r0D0_in : 左端位置向量（激活轴坐标）
%   r0D1_in : 左端一阶导（参数导数，已乘 a_param 补偿）
%   r0D2_in : 左端二阶导
%   r1D0_in : 右端位置向量
%   r1D1_in : 右端一阶导
%   r1D2_in : 右端二阶导
%
% Outputs :
%   p5      : 五次多项式系数矩阵 [N_AXES_MAX × 6]（每行一个轴，每列一个系数）
%   status  : 计算状态（1=成功，3/4/5=无正实根，6=最终验证失败）
%   alpha0  : 左端切向拉伸参数
%   alpha1  : 右端切向拉伸参数
%

N_AXES_MAX = 6;

% 将激活轴向量填入 N_AXES_MAX 维零向量（未激活轴保持 0，确保矩阵运算维度一致）
r0D0 = zeros(N_AXES_MAX, 1); r0D1 = r0D0; r0D2 = r0D0; r1D0 = r0D0;
r1D1 = r0D0; r1D2 = r0D0;

% Place input vector in : Set padding on vector
r0D0( ctx.cfg.maskTot ) = r0D0_in;
r0D1( ctx.cfg.maskTot ) = r0D1_in;
r0D2( ctx.cfg.maskTot ) = r0D2_in;
r1D0( ctx.cfg.maskTot ) = r1D0_in;
r1D1( ctx.cfg.maskTot ) = r1D1_in;
r1D2( ctx.cfg.maskTot ) = r1D2_in;

% 各轴的"特征长度"D（用于方程组规范化，防止不同量纲轴混合时数值病态）
D = zeros( N_AXES_MAX,1);
D(ctx.cfg.maskTot) = ctx.cfg.D;

status = int32(1); % default success

p5 = zeros(N_AXES_MAX,6);

alpha0 = 0;
alpha1 = 0;

%% compute Frenet frame
% 计算两端点的 Frenet 框架：切向量 t、法向量 n、曲率 kappa
% calc_t_nk_kappa 从参数导数计算几何量（与参数化无关）
[t0, n0, kappa0] = calc_t_nk_kappa(r0D1, r0D2);
[t1, n1, kappa1] = calc_t_nk_kappa(r1D1, r1D2);

%% reduce to polynomial system of 2 equations in unknowns alpha0 and alpha1
% 将 G2 边界条件化为关于 alpha0, alpha1 的多项式方程组
% p1   = (a1*alpha1+a0)*alpha0^2 + (b1*alpha1+b0)*alpha0 +
%         c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
% p2   = (d1*alpha0+d0)*alpha1^2 + (e1*alpha0+e0)*alpha1 +
%         f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
%
%% compute CoefPS = [a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0]
% CoefPolySys 计算上述方程组的 16 个系数（依赖 r0/r1、t0/t1、n0/n1、D）
CoefPS = CoefPolySys(r0D0, t0, n0, r1D0, t1, n1, D);
%
a1     = CoefPS(1);
a0     = CoefPS(2);
b1     = CoefPS(3);
b0     = CoefPS(4);
c3     = CoefPS(5);
c2     = CoefPS(6);
c1     = CoefPS(7);
c0     = CoefPS(8);
d1     = CoefPS(9);
d0     = CoefPS(10);
e1     = CoefPS(11);
e0     = CoefPS(12);
f3     = CoefPS(13);
f2     = CoefPS(14);
f1     = CoefPS(15);
f0     = CoefPS(16);
TolZero = 1e-11;   % 判断系数/根为零的数值阈值

%
if (kappa0 == 0) && (kappa1 == 0)
    % ── 情况 1：两端曲率均为零（直线-直线连接）─────────────────────────────
    % 当 kappa0=kappa1=0 时，方程组退化为线性方程组（高次项系数为零）：
    %   b0·α0 + c1·α1 = -c0
    %   f1·α0 + e0·α1 = -f0
    % 直接用 2×2 线性系统 M\B 求解。
    M       = [b0, c1;
               f1, e0];
    %
    B       = [-c0;
               -f0];
    %
    X       = M \ B;  % resolution of linear system
    alpha0  = X(1);
    alpha1  = X(2);

    if ~((alpha0 > 0) && (alpha1 > 0))
        % 无正实解：过渡曲线方向不合法（α 必须 > 0 以保证切向一致）
        return
    end

    [beta0, beta1] = Calc_beta0_beta1(alpha0, alpha1, ...
                                      r0D0, t0, n0, ...
                                      r1D0, t1, n1, D);

elseif kappa0 == 0
    % ── 情况 2：左端曲率为零（直线-曲线连接）────────────────────────────────
    % kappa0=0 时，p1 中 alpha0² 项消失，方程组可化为关于 alpha1 的三次多项式：
    %   结式（Resultant）= [b1·d0-c3·f1, b0·d0+b1·e0-c2·f1, ...]
    % 求三次多项式的根，筛选正实根，再由 p1=0 回代求 alpha0。
    Coef = [b1*d0 - c3*f1, b0*d0 + b1*e0 - c2*f1, b0*e0 + b1*f0 - c1*f1, b0*f0 - c0*f1];
    %
    alpha1_v = c_roots_(Coef);             % all roots of 3th degree polynomial in alpha1
    alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) < TolZero) & (real(alpha1_v) >  0))); % retain only positive real roots

    % 由 alpha1 回代求 alpha0（两个公式分别处理系数近零的退化情况）
    if (abs(b1) < TolZero) && (abs(b0) < TolZero)
        alpha0_t = -(d0*alpha1_t.^2+e0*alpha1_t+f0)/f1;
    else
        alpha0_t = -(c3*alpha1_t.^3+c2*alpha1_t.^2+c1*alpha1_t+c0)./(b1*alpha1_t+b0);
    end

    % 筛选 alpha0 > 0 的有效解
    Idx       = find(alpha0_t > 0);
    alpha1_u  = alpha1_t(Idx);
    alpha0_u  = alpha0_t(Idx);

    if ~(numel(alpha0_u) > 0)
        status = int32(3);   % 错误码 3：无正实根
        return
    end
    %c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');

    if length(alpha0_u) > 1
        % 多个正实根：计算各解的代价积分，选取最优解
        CostInt = zeros(size(alpha0_u));  % preallocating
        beta0_u = zeros(size(alpha0_u));  % preallocating
        beta1_u = zeros(size(alpha0_u));  % preallocating

        for k = 1:length(alpha0_u)

            [beta0_u(k), beta1_u(k)] = Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                                                        r0D0, t0, n0, ...
                                                        r1D0, t1, n1, D);
            % EvalCostIntegral：计算三阶导范数积分（跃度代价），越小越好
            CostInt(k)     = EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                                              r0D0, t0, n0, ...
                                              r1D0, t1, n1, D);

        end

        [~, Idx] = min(CostInt);
        alpha0   = alpha0_u(Idx);
        alpha1   = alpha1_u(Idx);
        beta0    = beta0_u(Idx);
        beta1    = beta1_u(Idx);

    else
        % 唯一正实根，直接使用
        alpha0   = alpha0_u(1);
        alpha1   = alpha1_u(1);
        [beta0, beta1] = Calc_beta0_beta1(alpha0, alpha1, ...
                                          r0D0, t0, n0, ...
                                          r1D0, t1, n1, D);

    end
    %
elseif kappa1 == 0
    % ── 情况 3：右端曲率为零（曲线-直线连接）────────────────────────────────
    % 与情况 2 对称：此时 p2 中 alpha1² 项消失，化为关于 alpha0 的三次多项式。
    Coef = [c1*f3 - a0*e1, c1*f2 - b0*e1 - a0*e0, c1*f1 - c0*e1 - b0*e0, c1*f0 - c0*e0];
    %
    alpha0_v  = c_roots_(Coef);             % all roots of 3th degree polynomial in alpha0
    alpha0_t  = real(alpha0_v((abs(imag(alpha0_v)) < TolZero) & (real(alpha0_v) >  0))); % retain only positive real roots

    if (abs(e1) < TolZero) && (abs(e0) < TolZero)
        alpha1_t = -(a0*alpha0_t.^2+b0*alpha0_t+c0)/c1;
    else
        alpha1_t = -(f3*alpha0_t.^3+f2*alpha0_t.^2+f1*alpha0_t+f0)./(e1*alpha0_t+e0);
    end

    Idx      = find(alpha1_t > 0);
    alpha1_u = alpha1_t(Idx);
    alpha0_u = alpha0_t(Idx);
    %
    if ~(numel(alpha0_u) > 0)
        status = int32(4);   % 错误码 4：无正实根
        return
    end
    %c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');

    if length(alpha0_u) > 1
        CostInt = zeros(size(alpha0_u));  % preallocating
        beta0_u = zeros(size(alpha0_u));  % preallocating
        beta1_u = zeros(size(alpha0_u));  % preallocating

        for k = 1:length(alpha0_u)
            [beta0_u(k), beta1_u(k)] = Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                                                        r0D0, t0, n0, ...
                                                        r1D0, t1, n1, D);
            CostInt(k)     = EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                                              r0D0, t0, n0, ...
                                              r1D0, t1, n1, D);
        end
        [~, Idx] = min(CostInt);
        alpha0   = alpha0_u(Idx);
        alpha1   = alpha1_u(Idx);
        beta0    = beta0_u(Idx);
        beta1    = beta1_u(Idx);

    else

        alpha0   = alpha0_u(1);
        alpha1   = alpha1_u(1);
        [beta0, beta1] = Calc_beta0_beta1(alpha0, alpha1, ...
                                          r0D0, t0, n0, ...
                                          r1D0, t1, n1, D);

    end
    %
else
    % ── 情况 4：一般情况（曲线-曲线连接，两端曲率均非零）────────────────────
    % 通过计算两个多项式的结式（Characteristic Polynomial）消去 alpha0，
    % 得到关于 alpha1 的 9 次多项式，再逐步求 alpha0。
    % CharPolyAlpha1 计算该 9 次多项式的系数，c_roots_ 计算所有根。
    Coef = CharPolyAlpha1(CoefPS);
    %
    alpha1_v = c_roots_(Coef);             % all roots of 9th degree polynomial in alpha1
    alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) < TolZero) & (real(alpha1_v) >  0))); % retain only positive real roots

    % CalcAlpha0：由 alpha1 回代求对应的 alpha0
    alpha0_t  = CalcAlpha0(alpha1_t,   CoefPS);
    %
    Idx       = find(alpha0_t > 0);
    alpha1_u  = alpha1_t(Idx);
    alpha0_u  = alpha0_t(Idx);
    %
    if ~(numel(alpha0_u) > 0)
        status = int32(5);   % 错误码 5：无正实根
        return
    end
    %c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');

    if length(alpha0_u) > 1
        % 多个正实根：选最优解
        CostInt = zeros(size(alpha0_u));  % preallocating
        beta0_u = zeros(size(alpha0_u));  % preallocating
        beta1_u = zeros(size(alpha0_u));  % preallocating

        for k = 1:length(alpha0_u)

            [beta0_u(k), beta1_u(k)] = Calc_beta0_beta1(alpha0_u(k), alpha1_u(k), ...
                                                        r0D0, t0, n0, ...
                                                        r1D0, t1, n1, D);
            CostInt(k)     = EvalCostIntegral(alpha0_u(k),  beta0_u(k), alpha1_u(k), beta1_u(k), ...
                                              r0D0, t0, n0, ...
                                              r1D0, t1, n1, D);

        end

        [~, Idx] = min(CostInt);
        alpha0   = alpha0_u(Idx);
        alpha1   = alpha1_u(Idx);
        beta0    = beta0_u(Idx);
        beta1    = beta1_u(Idx);

    else

        alpha0   = alpha0_u(1);
        alpha1   = alpha1_u(1);
        [beta0, beta1] = Calc_beta0_beta1(alpha0, alpha1, ...
                                          r0D0, t0, n0, ...
                                          r1D0, t1, n1, D);

    end

end

%% Hermite basis
% 五次 Hermite 基函数（标准形式，参数 u ∈ [0,1]），系数按降幂排列：
%   h00(u) = -6u⁵+15u⁴-10u³+1   （左端位置基，h00(0)=1, h00(1)=0）
%   h10(u) = -3u⁵+8u⁴-6u³+u     （左端一阶导基，h10'(0)=1）
%   h20(u) = -0.5u⁵+1.5u⁴-1.5u³+0.5u² （左端二阶导基，h20''(0)=1）
%   h01/h11/h21 为右端对应基
h00 = [-6,    15,   -10,     0,     0,     1];
h10 = [-3,     8,    -6,     0,     1,     0];
h20 = [-0.5,  1.5,   -1.5,   0.5,   0,     0];
h01 = [6,   -15,     10,     0,     0,     0];
h11 = [-3,    7,     -4,     0,     0,     0];
h21 = [0.5,  -1,    0.5,     0,     0,     0];

%% evaluate coefficients as sum of basis functions
% 构造五次多项式系数矩阵 p5 [N_AXES_MAX × 6]：
%   p5(u) = r0D0·h00 + (α0·t0)·h10 + (β0·t0 + α0²·n0)·h20
%         + r1D0·h01 + (α1·t1)·h11 + (β1·t1 + α1²·n1)·h21
%
% 含义：
%   r0D0·h00 + r1D0·h01       位置边界条件
%   α0·t0·h10 + α1·t1·h11    一阶导（切向）边界条件
%   (β0·t0+α0²·n0·κ0)·h20   二阶导（曲率）边界条件（注：n0 已含 κ 方向）
p5 = r0D0 * h00 + alpha0*t0 * h10 + (beta0*t0 + alpha0^2*n0) * h20 + ...
     r1D0 * h01 + alpha1*t1 * h11 + (beta1*t1 + alpha1^2*n1) * h21;

%% last cross check ...
% 将求得的 alpha0, alpha1 代入原方程组验证（p1≈0, p2≈0），
% 若残差过大（> 1e-7）则置状态码 6（数值误差，解不可靠）
p1val = (a1*alpha1+a0)*alpha0^2  +  (b1*alpha1+b0)*alpha0  +  c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
p2val = (d1*alpha0+d0)*alpha1^2  +  (e1*alpha0+e0)*alpha1  +  f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
%
if ~(abs(p1val) < 1e-7) || ~(abs(p2val) < 1e-7)
    status = int32(6);
    return
end
