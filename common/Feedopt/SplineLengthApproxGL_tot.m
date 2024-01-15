function [ L, Lk ]  = SplineLengthApproxGL_tot( cfg, Curv )
% SplineLengthApproxGL_tot : Precomputes approximately the total arc length
% L as well as the individual arc lengths between knot points of a 
% parametric spline. The computation is based on numerical Gauss Legendre 
% integration. SplineLengthApproxGL_tot should only be called once since 
% the result of the computation is stored and reused later.
%
% Inputs :
%   cfg     : The configuration structure
%   Curv    : The spline
%
% Outputs :
%   L       : The resulting length
%   Lk      : The resulting length of each nodes intervals
%

% get the sp structure
% Spline = ctx.q_spline.get(Curv.sp_index);
% sp     = Spline.sp;
sp     = Curv.sp;
Knots  = sp.knots(4:end-3);  % eliminate multiplicities at the end points
a      = Knots(1:end-1);     % lower integration limits
b      = Knots(2:end);       % upper integration limits
% get Gauss-Legendre knots and weights
GL_N   = cfg.GaussLegendreN;
GL_X   = cfg.GaussLegendreX;
GL_W   = cfg.GaussLegendreW;
% apply linear map from[-1, 1] to [a, b]
Umat   = (bsxfun(@times, a, (1-GL_X)) + bsxfun(@times, b, (1+GL_X)))/2;
Uvec   = Umat(:)';  % all evaluation points as row vector

[~, r1D]  = EvalBSpline(Curv, Uvec);
r1Dnorm   = MyNorm(r1D);
r1DnormM  = reshape(r1Dnorm, GL_N, length(Knots)-1); 
Lk        = sum(bsxfun(@times, GL_W, r1DnormM)) .* (b-a)/2; % Gauss Legendre integration
L         = sum(Lk);
