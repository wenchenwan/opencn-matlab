function [ x, xd, xdd, xddd ] = bspline_eval_vec( Bl, coeffs, uVec ) %#codegen
% bspline_eval_vec  : Eval Bspline bases for a given set of u value. 
% 
% Inputs    :
% Bl            : BSpline bases
% coeffs        : BSpline coefficients
% uVec          : U vector of points to evaluate
% 
% Outputs   :
% x             : Evaluation of the BSpline
% xd            : Evaluation of the first derivative of the BSpline
% xdd           : Evaluation of the second derivative of the BSpline
% xddd          : Evaluation of the third derivative of the BSpline
%
x       = zeros(size(uVec));
xd      = zeros(size(uVec));
xdd     = zeros(size(uVec));
xddd    = zeros(size(uVec));

for k = 1:length(uVec)
    [xk, xdk, xddk, xdddk] = bspline_eval( Bl, coeffs, uVec( k ) );
    x(k)    = xk;
    xd(k)   = xdk;
    xdd(k)  = xddk;
    xddd(k) = xdddk;
end
end
