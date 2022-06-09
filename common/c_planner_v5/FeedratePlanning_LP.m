function [ctx, Coeff, success, status, msg] = ...
    FeedratePlanning_LP( ctx, window, amax, jmax, BasisVal, ...
    BasisValD, BasisValDD, BasisIntegr, u_vec, NWindow )

% 0) Initialization of the problem

% M     : number of discretization
% N     : number of coefficients
[ M, N ]    = size( BasisVal );               
LP          = ctx.cfg.opt;              % Load parameters of the LP
CurvArray   = window( 1 : NWindow );    % Extract window of interest

%% 1) Optimization : first LP

% A. Linear objectif
f = -repmat( BasisIntegr, 1, NWindow ); 

% B. Constraints : Inequality and Equality 
% Feedrate and acceleration
[ A, b, Aeq, beq, continuity ] = buildConstr( ctx, CurvArray, amax, ctx.v_0, ...
    ctx.at_0, ctx.v_1, ctx.at_1, BasisVal, BasisValD, u_vec);

% C. Solve the optimization problem
[ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b, Aeq, beq, ctx );

if( ~success )
    Coeff0 = zeros( size( A, 2),  1);
    M = Aeq( 1 : 2, 1 : 2 );
    m = beq( 1 : 2 );
    Coeff0( 1 : 2 ) = M \ m;
    M1 = Aeq( end- 1:end, end- 1:end);
    m1 = beq( end-1 : end );
    Coeff0( end-1 :end ) = M1 \ m1;
    CoeffInt = linspace( Coeff0(2), Coeff0(3), size( A, 2) -2 );
    Coeff0( 3 :end -2 ) = CoeffInt( 2 : end -1 );
    resIneq = A* Coeff0 -b;
    errIneq = find( resIneq >= 0 );
    error("First LP failed...");
else 
    Coeff  = reshape( Coeff0, N, NWindow );
end

% 2) Optimization : second LP with jerk constraints and slack

% % A. Linear objectif
ftot = [ f( : ); LP.SLACK_PENALTY ];

% B. Constraints : Inequality and Equality
% Feedrate, acceleration and jerk
[ Aj, bj ] =  buildConstrJerk( ctx, CurvArray, Coeff, jmax, ...
    BasisVal, BasisValD, BasisValDD, u_vec );

Atot    = [ A, zeros( size( A, 1), 1 ) ;
    Aj ];
btot    = [ b; bj ];

AEtot   = [ Aeq, zeros( size( Aeq, 1), 1 ) ];

[ Coeff2, success, status, msg ] = c_simplex( ftot, sparse( Atot ), btot, ...
    AEtot, beq, ctx );


if( ~success ) % The optimization successed
    error( "Second LP failed..." );
else
    Coeff   = reshape( Coeff2( 1 : end -1 ), N, NWindow );
    disp( "slack : " + Coeff2(end) );
end

% Compute the continuity equations
X           = continuity * Coeff( : , 1 );
ctx.v_0     = sqrt( X( 1, : ) );
ctx.at_0    = X( 2, : );
ctx.Coeff   = Coeff;

end