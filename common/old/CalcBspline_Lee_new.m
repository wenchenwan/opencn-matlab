function [ spnD ] = CalcBspline_Lee_new( cfg, points )
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

[ BasisVal, BasisValDD0, BasisValDD1 ] = bspline_eval_lee( Bl, int32( nCoeff ), u );

%
A = [ BasisValDD0; BasisVal; BasisValDD1 ];
%
b = [zeros(1, nAxis);
            points.';
     zeros(1, nAxis)];
%
c = A \ b;
%

spnD = constrSpline( c.', knots, Bl );

end