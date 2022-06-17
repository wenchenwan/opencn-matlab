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

% Slack variables
fSlack = [ f( : ); LP.SLACK_PENALTY ];
[ nAL, nAc ] = size( A );
ASlack = [ A, - ones( nAL, 1 ) ; zeros( 1, nAc ), -1 ];
bSlack = [ b ; 0 ];
AeqSlack   = [ Aeq, zeros( size( Aeq, 1), 1 ) ];

% C. Solve the optimization problem
[ Coeff0, success, status, msg ] = c_simplex( fSlack, sparse( ASlack ), ...
    bSlack, AeqSlack, beq, ctx );


if( ~success )
    Coeff = [];
    NCoeff = int32(0);
    if( coder.target( "MATLAB" ) ), fprintf( msg ); end
    error("First LP failed...");
    return;
else
    Coeff   = reshape( Coeff0( 1 : end -1 ), N, NWindow );
end

% 2) Optimization : second LP with jerk constraints and slack

% % A. Linear objectif
ftot = [ f( : ); LP.SLACK_PENALTY ];

% B. Constraints : Inequality and Equality
% Feedrate, acceleration and jerk
[ Aj, bj ] =  buildConstrJerk( ctx, CurvArray, Coeff, jmax, ...
    BasisVal, BasisValD, BasisValDD, u_vec );

Atot    = [ A, -ones( size( A, 1), 1 ) ;
    Aj ];
btot    = [ b; bj ];

AEtot   = [ Aeq, zeros( size( Aeq, 1), 1 ) ];

[ Coeff2, success, status, msg ] = c_simplex( ftot, sparse( Atot ), btot, ...
    AEtot, beq, ctx );


if( ~success ) % The optimization successed
    if( coder.target( "MATLAB" ) ), fprintf( msg ); end
    error( "Second LP failed..." );
else
    Coeff   = reshape( Coeff2( 1 : end -1 ), N, NWindow );
    if( coder.target( "MATLAB" ) ), fprintf( "slack : " + Coeff2(end) + "\n"); end
end

% Compute the continuity equations
X           = continuity * Coeff( : , 1 );
ctx.v_0     = sqrt( X( 1, : ) );
ctx.at_0    = X( 2, : );
ctx.Coeff   = Coeff;

end