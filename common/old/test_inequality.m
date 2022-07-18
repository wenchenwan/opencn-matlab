at_norm = sym( 'at_norm', 'real' );
v_norm_2= sym( 'v_norm_2','real' );
m       = sym( 'm', [ 2, 2 ], 'real' );
X       = sym( 'X', [ 2, 1 ], 'real' );
epsi    = sym( 'epsi', 'positive' );

k = sym( 'k', 'real' );

% Equalities constraints
M = [ 0, m(1,2); m(2,1), m(2,2) ]
b = [ v_norm_2; at_norm ]
X = M \ b

% Look for positivity of the coefficients
eqn     = ( X(1) == 0 );
ka      = solve( eqn, at_norm );

% Look for the positivity of the parameter
b(2)    = ka + epsi;
Xa      = M \ b;
