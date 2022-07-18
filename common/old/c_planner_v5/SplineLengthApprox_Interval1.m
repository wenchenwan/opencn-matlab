function L = SplineLengthApprox_Interval1(ctx, Curv, u0, u1)
% computes approximately the arc length L with integration bounds u1 and u2.
% IMPORTANT : u1 and u2 should lie in the same knot interval.
% The computation is based on numerical Gauss Legendre integration 
%
% get the spline
Spline = ctx.q_spline.get(Curv.sp_index);
% get Gauss-Legendre knots and weights
GL_X   = ctx.cfg.GaussLegendreX;
GL_W   = ctx.cfg.GaussLegendreW;
% apply linear map from[-1, 1] to [u0, u1]
uvec   = ((u0*(1-GL_X) + u1*(1+GL_X))/2)';
%
[~, r1D]  = EvalBSpline(Spline, uvec);
r1Dnorm   = MyNorm(r1D);
L         = r1Dnorm * GL_W * (u1-u0)/2; % Gauss Legendre integration
L = L(1); % to satisfy Matlab Coder

