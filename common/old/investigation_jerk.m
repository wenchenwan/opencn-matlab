% clear all; clc;

Ndim    = 5;
jps     = sym( 'jps', [ 1, 1] ,    'real');
r0D     = sym( 'r0D', [ Ndim, 1] , 'real');
r1D     = sym( 'r1D', [ Ndim, 1] , 'real');
r2D     = sym( 'r2D', [ Ndim, 1] , 'real');
r3D     = sym( 'r3D', [ Ndim, 1] , 'real');
alpha   = sym( 'alpha', [ 1, 1] ,  'real');

% Predefined profile
u       = 1;
ud      = ( jps )^( 5 / 2 ) * ( 6 ) ^ ( 3 / 2 ) / 2;
udd     = ( jps )^( 4 / 3 );
uddd    = ( jps )^( 1 / 3 );

% Compute dynamic
[ R, V, A, J ]      = calcRVAJfromUWithoutCurv( ud, udd, uddd, r0D, r1D, r2D, r3D );

R = simplify( R );
V = simplify( V );
A = simplify( A );
J = simplify( J );

[ vNorm, atNorm ]   = calcNormVNormAT( V, A, r1D );

vNorm  = simplify( vNorm );
atNorm = simplify( atNorm );

ratio = atNorm / vNorm; ratio = simplify( ratio );

% solve equation
f   = simplify( ratio - alpha );
Df  = simplify( jacobian( f, jps ) );

fn  = ( 6^( 1/2) *( jps^(8/3)* (sum( r1D.^4 ) + ...
    108*jps^(11/3)* sum( r1D.^3 .* r2D ) + ...
    2916*jps^(22/3)* sum( r1D.^2 .* r2D.^2 ) ) )^( 1 / 2 ) ) ...
/ (18*jps^(5/2)* sum( r1D.^2)) - alpha;


F   = matlabFunction(f, 'Vars', {jps, r1D, r2D, alpha});
Fn  = matlabFunction(fn,'Vars', {jps, r1D, r2D, alpha});

t_jps   = rand;
t_alpha = rand;
t_r1D   = rand( Ndim, 1);
t_r2D   = rand( Ndim, 1);

y   = F(  t_jps, t_r1D, t_r2D, t_alpha );
yn  = Fn( t_jps, t_r1D, t_r2D, t_alpha );

Dfn = ...
( ...
    6^(1/2)*( ...
        432*jps^(11/3) * sum( r1D.^3 .* r2D )...
        - 7 * sum( r1D.^4 )...
      + 43740*jps^(22/3) * sum( r1D .^2 .* r2D.^2 ) ) ...
) / ...
( ...
    108*jps^(5/6)* ...
    ( ...
        jps^(8/3) * ...
        (...
            sum( r1D .^ 4 ) + ...
            108*jps^(11/3)*sum( r1D.^3 .* r2D) +...
            2916*jps^(22/3)*sum( r1D.^2 .* r2D.^2)...
         ) ...
     )^(1/2)* sum( r1D.^2 ) );

DF   = matlabFunction(Df, 'Vars', {jps, r1D, r2D, alpha});
DFn  = matlabFunction(Dfn,'Vars', {jps, r1D, r2D, alpha});

Dy   = DF(  t_jps, t_r1D, t_r2D, t_alpha );
Dyn  = DFn( t_jps, t_r1D, t_r2D, t_alpha );
