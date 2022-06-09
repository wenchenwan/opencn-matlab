function [ spnD ] = CalcBspline_Lee( cfg, points )
% CalcBspline_Lee :
%
% INPUT
% cfg       : struct : Configuration variables
% points    :   nDxN : Set of points in n dimension for the spline
%
% OUTPUT
% spnD      : struct : Output spline structure

[ ~, N ] = size( points ); % number of points in nD space
nAxis    = cfg.NumberAxis;
nMult    = cfg.LeeSplineDegree - 1; % Number of multiplicity at start and end ( clamped BSpline )
nCoeff   = N + 2;

du     = sum( ( diff( points.' ).^2 ).' );
u      = cumsum( [ 0, du.^( 1 / 4 ) ] );
u      = u / u( end );  % normalize knots to interval [0...1]
knots  = [ zeros( 1, nMult ), u, ones( 1, nMult ) ];

Bl = bspline_create( cfg.LeeSplineDegree, u );

BasisVal    = zeros( N, nCoeff ); % preallocation
BasisValDD0 = zeros( 1, nCoeff ); % preallocation
BasisValDD1 = zeros( 1, nCoeff ); % preallocation
%
coef        = eye( nCoeff );

for k = 1: nCoeff                 % evaluate basis functions at the knots
    [ X, ~, Xdd ] = bspline_eval_vec(Bl, coef( k, : ), u);
    BasisVal(:, k)   = X';
    BasisValDD0( k ) = Xdd( 1 );
    BasisValDD1( k ) = Xdd( end );
end
%
A = [ BasisValDD0; BasisVal; BasisValDD1 ];
%
b = [zeros(1, nAxis);
             points';
     zeros(1, nAxis)];
%
c = A \ b;
%

spnD = constrSpline( c.', knots, Bl );

end