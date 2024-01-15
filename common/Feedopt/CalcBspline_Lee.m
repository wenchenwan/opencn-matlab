function [ spnD ] = CalcBspline_Lee( cfg, points )
% CalcBspline_Lee :
%
% Inputs :
% cfg       : struct : Configuration variables
% points    :   nDxN : Set of points in n dimension for the spline
%
% Outputs
% spnD      : struct : Output spline structure

% number of points in nD space
[ ~, N ] = size( points ); 
nAxis    = cfg.NumberAxis;
% Number of multiplicity at start and end ( clamped BSpline )
nMult    = cfg.LeeSplineDegree - 1; 
nCoeff   = N + 2;

du     = sum( ( diff( points.' ).^2 ).' );
u      = cumsum( [ 0, du.^( 1 / 4 ) ] );
% normalize knots to interval [0...1]
u      = u / u( end );  
knots  = [ zeros( 1, nMult ), u, ones( 1, nMult ) ];

Bl = bspline_create( cfg.LeeSplineDegree, u );
%
[ BasisVal, BasisValDD0, BasisValDD1 ] = bspline_eval_lee( Bl, int32( nCoeff ), u );
%
A = [ BasisValDD0; BasisVal; BasisValDD1 ];
%
B = [zeros(1, nAxis);
    points.';
    zeros(1, nAxis)];
%
[ A ] = swap_lines( A );
[ B ] = swap_lines( B );
[ v_m, v_l, v_u ] = extract_vectors( A );

c = tridiag( v_m, v_l, v_u, B );

spnD = constrSpline( c.', knots, Bl );
end


function [ M ] = swap_lines( M )
% Swap the lines of the matrice M. The goal is to obtain a tridiagonal
% matrice.
M( [ 1, 2, end-1, end ], : ) = M( [ 2, 1, end, end-1 ], :);

end

function [ v_m, v_l, v_u ] = extract_vectors( A )
% Extract the three vectors of the triagonal matrix A.
% Output :
% v_m   :   The vector of the middle of the matrix 
% v_l   :   The vector of the lower diagonal of the matrix
% v_u   :   The vector of the upper diagonal of the matrix
v_m = diag( A );
v_l = [ 0; diag( A, -1 ) ];
v_u = [ diag( A, 1 ); 0 ];
end
