function L = splineLengthApprox_Interval( cfg, spline, u0, u1, isEnd )
% computes approximately the arc length L with integration bounds u1 and u2.
% IMPORTANT : u0 and u1 should lie in the same knot interval.
% The computation is based on numerical Gauss Legendre integration 
%
% get Gauss-Legendre knots and weights
GL_X   = cfg.GaussLegendreX;
GL_W   = cfg.GaussLegendreW;

if( isEnd )
    a   = 1 - u0;
    u0  = 1 - u1;
    u1  = a;
end

% apply linear map from[-1, 1] to [u0, u1]
uvec   = ( ( u0 * ( 1 - GL_X ) + u1 * ( 1 + GL_X ) ) / 2 ).';
%

[ ~, r1D ]  = EvalBSpline( spline, uvec );
r1Dnorm     = MyNorm( r1D );
L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2; % Gauss Legendre integration
L = L( 1 ); % to satisfy Matlab Coder

