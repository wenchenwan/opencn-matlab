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
function [p5, status, alpha0, alpha1] = G2_Hermite_Interpolation_nAxis(ctx, r0D0_in, r0D1_in, r0D2_in, r1D0_in, r1D1_in, r1D2_in)

N_AXES_MAX = 6;

% Function are calculated for 5 axis
r0D0 = zeros(N_AXES_MAX, 1); r0D1 = r0D0; r0D2 = r0D0; r1D0 = r0D0; 
r1D1 = r0D0; r1D2 = r0D0;

% Place input vector in : Set padding on vector
r0D0(ctx.cfg.maskTot) = r0D0_in;
r0D1(ctx.cfg.maskTot) = r0D1_in;
r0D2(ctx.cfg.maskTot) = r0D2_in;
r1D0(ctx.cfg.maskTot) = r1D0_in;
r1D1(ctx.cfg.maskTot) = r1D1_in;
r1D2(ctx.cfg.maskTot) = r1D2_in;

D = zeros( N_AXES_MAX,1);
D(ctx.cfg.maskTot) = ctx.cfg.D;

status = int32(1); % default success

p5 = zeros(N_AXES_MAX,6);

alpha0 = 0;
alpha1 = 0;

%% compute Frenet frame
[t0, n0, kappa0] = calc_t_nk_kappa(r0D1, r0D2);
[t1, n1, kappa1] = calc_t_nk_kappa(r1D1, r1D2);
%% reduce to polynomial system of 2 equations in unknowns alpha0 and alpha1
% p1   = (a1*alpha1+a0)*alpha0^2 + (b1*alpha1+b0)*alpha0 + 
%         c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
% p2   = (d1*alpha0+d0)*alpha1^2 + (e1*alpha0+e0)*alpha1 + 
%         f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
%
%% compute CoefPS = [a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0]
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
TolZero = 1e-11;
%
if (kappa0 == 0) && (kappa1 == 0)   % degenerated case where the polynomial system degenerates to a linear one
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
        return
    end    

    [beta0, beta1] = Calc_beta0_beta1(alpha0, alpha1, ...
                                      r0D0, t0, n0, ...
                                      r1D0, t1, n1, D);   
elseif kappa0 == 0
    % compute resultant of the polynomial system
    Coef = [b1*d0 - c3*f1, b0*d0 + b1*e0 - c2*f1, b0*e0 + b1*f0 - c1*f1, b0*f0 - c0*f1];
    %
    alpha1_v = c_roots_(Coef);             % all roots of 3th degree polynomial in alpha1
    alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) < TolZero) & (real(alpha1_v) >  0))); % retain only positive real roots
    
    if (abs(b1) < TolZero) && (abs(b0) < TolZero)
        alpha0_t = -(d0*alpha1_t.^2+e0*alpha1_t+f0)/f1; 
    else
        alpha0_t = -(c3*alpha1_t.^3+c2*alpha1_t.^2+c1*alpha1_t+c0)./(b1*alpha1_t+b0);
    end
    
    Idx       = find(alpha0_t > 0);
    alpha1_u  = alpha1_t(Idx);
    alpha0_u  = alpha0_t(Idx);
    
    if ~(numel(alpha0_u) > 0)
        status = int32(3);
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
elseif kappa1 == 0
    % compute resultant of the polynomial system
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
        status = int32(4);
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
    % compute resultant of the polynomial system
    Coef = CharPolyAlpha1(CoefPS);
    %
    alpha1_v = c_roots_(Coef);             % all roots of 9th degree polynomial in alpha1
    alpha1_t = real(alpha1_v((abs(imag(alpha1_v)) < TolZero) & (real(alpha1_v) >  0))); % retain only positive real roots
    
    % compute corresponding values of alpha0
    alpha0_t  = CalcAlpha0(alpha1_t,   CoefPS);
    %
    Idx       = find(alpha0_t > 0);
    alpha1_u  = alpha1_t(Idx);
    alpha0_u  = alpha0_t(Idx);
    %
    if ~(numel(alpha0_u) > 0)
        status = int32(5);
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

end
%
%% Hermite basis 
h00 = [-6,    15,   -10,     0,     0,     1];
h10 = [-3,     8,    -6,     0,     1,     0];
h20 = [-0.5,  1.5,   -1.5,   0.5,   0,     0];
h01 = [6,   -15,     10,     0,     0,     0];
h11 = [-3,    7,     -4,     0,     0,     0];
h21 = [0.5,  -1,    0.5,     0,     0,     0];
%% evaluate coefficients as sum of basis functions
p5 = r0D0 * h00 + alpha0*t0 * h10 + (beta0*t0 + alpha0^2*n0) * h20 + ...
     r1D0 * h01 + alpha1*t1 * h11 + (beta1*t1 + alpha1^2*n1) * h21;
%% last cross check ...
p1val = (a1*alpha1+a0)*alpha0^2  +  (b1*alpha1+b0)*alpha0  +  c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
p2val = (d1*alpha0+d0)*alpha1^2  +  (e1*alpha0+e0)*alpha1  +  f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
%
if ~(abs(p1val) < 1e-7) || ~(abs(p2val) < 1e-7)
    status = int32(6);
    return
end

