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
[ D, Dinv ] = compute_scaling_matrix( ctx, CurvArray, N );
DCon        = D( [ 1 : N ], [ 1 : N ] ); 

% A. Linear objectif
f = -repmat( BasisIntegr, 1, NWindow );
f = reshape( f( : )'  * D, [], NWindow );

% B. Constraints : Inequality and Equality
% Feedrate and acceleration
[ A, b, Aeq, beq, continuity ] = buildConstr( ctx, CurvArray, amax, ctx.v_0, ...
    ctx.at_0, ctx.v_1, ctx.at_1, BasisVal, BasisValD, u_vec);


A           = A * D;
Aeq         = Aeq * D;
continuity  = continuity * DCon;

indSlack =  []; %1 : numel( b );

[ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( f, ...
    A, b, Aeq, beq, indSlack, LP );


% C. Solve the optimization problem
[ ctx, Coeff, success, status, msg, beq ] = solve_LP( fSlack, ASlack, bSlack, ...
    AeqSlack, beqSlack, ctx, N, NWindow, "First LP" );

if( ~success ), return; end

% 2) Optimization : second LP with jerk constraints and slack

if( ctx.cfg.opt.UseConstraintsOnJerk )
    Coeff       = reshape( D * Coeff( : ), N, [] );
    % B. Constraints : Inequality and Equality
    % Feedrate, acceleration and jerk
    [ Aj, bj ] =  buildConstrJerk( ctx, CurvArray, Coeff, jmax, ...
        BasisVal, BasisValD, BasisValDD, u_vec );

    Aj   = Aj * D;
    Atot = [ A; Aj ]; btot = [ b; bj ];

    indSlack = [ indSlack, numel( b ) + [ 1 : numel( bj ) ] ];

    [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( f, ...
        Atot, btot, Aeq, beq, indSlack, LP );

    [ ctx, Coeff, success, status, msg ] = solve_LP( fSlack, ASlack, bSlack, ...
        AeqSlack, beqSlack, ctx, N, NWindow, "Second LP" );
end

if( ~success ), return; end

if( ~ctx.zero_start )
    % Compute the continuity equations
    X           = continuity * Coeff( : , 1 );
    ctx.v_0     = sqrt( X( 1 ) );
    ctx.at_0    = X( 2 );
end

Coeff       = reshape( D * Coeff( : ), N, [] );

ctx.Coeff   = Coeff;

end

%-------------------------------------------------------------------------
% Functions
%-------------------------------------------------------------------------

function [ ctx, Coeff, success, status, msg, beq ] = solve_LP( f, A, b, Aeq, ...
    beq, ctx, N, NWindow, optName )
% Call the solver
[ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b, Aeq, ...
    beq, ctx );

if( ~success && ( ctx.zero_start || ctx.zero_end ) )
        % ZN or NZ case :
        % Optimization failed due with zero end constaints, decrease pseudo jerk
        Ntot        = NWindow;
        maxIter     = 15;

        if( ~success && ctx.zero_start )
            Ntot        = Ntot + 1;
            indStart    = ctx.k0;
            [ctx, Coeff0, success, status, msg] = relax_intial_constraints( ...
                f, A, b, Aeq, beq, ctx, indStart, false, maxIter);
        end

        if( ~success && ctx.zero_end )
            Ntot        = Ntot + 1;
            indEnd      = ctx.k0 + Ntot -1;
            [ctx, Coeff0, success, status, msg] = relax_intial_constraints( ...
                f, A, b, Aeq, beq, ctx, indEnd, true, maxIter);
        end
end

% Check the status of the optimization
Coeff = [];
if( success )
    Coeff   = reshape( Coeff0( 1 : end -1 ), N, NWindow );

    if( coder.target( "MATLAB" ) && Coeff0( end ) > 0.0 )
        fprintf( "Slack : " + Coeff0( end ) + "\n" );
    end
else
    msg = optName + " failed...";
end

end

function [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( f, ...
    A, b, Aeq, beq, indSlack, LP )
[ nAL, nAc ] = size( A );

if( 0 ) 
    % HGS : Not working as expected... Removed for now
    % Add condition of positivity on coeffs the 2 first and the two last are
    % not
    Apos = zeros( nAc-4 , nAc + 1 ); bpos = -1e-4 * ones( nAc-4 , 1);
    Apos( : , 3 : end -3   ) = -eye( nAc-4  );
else
    Apos = [];
    bpos = [];
end

% Slack variables
vecSlack    = zeros( nAL, 1 ); vecSlack( indSlack ) = -1;
fSlack      = [ f( : ); LP.SLACK_PENALTY ];
ASlack      = [ Apos; A, vecSlack; zeros( 1, nAc ), -1 ];
bSlack      = [ bpos; b ; 0 ];
AeqSlack    = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
beqSlack    = beq;

end

function [ curv, vNorm, atNorm ] = decrease_constjerk( ctx, curv, isEnd )
curv.ConstJerk = curv.ConstJerk / 8;
[ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd );
end

function [ctx, Coeff0, success, status, msg] = relax_intial_constraints( ...
    f, A, b, Aeq, beq, ctx, indCurv, isEnd, maxIter)
success     = false;
count       = 0;
curv        = ctx.q_split.get( indCurv );
atNorm      = 0;
vNorm       = 0;
status      = int32( 0 );
Coeff0      = zeros( size( f ) );
msg         = "";

while( ~success && count < maxIter )
    [ curv, vNorm , atNorm ] = decrease_constjerk( ctx, curv, isEnd );

    if(isEnd)
        beq( end-1 )    = -vNorm^2;
        beq( end )      = atNorm;
    else
        beq( 1 )        = vNorm^2;
        beq( 2 )        = atNorm;
    end

    [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b, ...
        Aeq, beq, ctx );
    count = count + 1;

end

% Set back the change into the queue
ctx.q_split.set( indCurv, curv );
if(isEnd)
    ctx.at_1    = -atNorm;
    ctx.v_1     = -vNorm;
else
    ctx.at_0    = atNorm;
    ctx.v_0     = vNorm;
end

end

function [ D, Dinv ] = compute_scaling_matrix( ctx, curvArray, NCoeff )
    N       = length( curvArray );
    
    if( ctx.cfg.opt.USE_LENGTH_SCALING )
        lCurvs  = zeros( NCoeff, N );

        for ind = 1 : N
            lCurvs( :, ind ) = ones( NCoeff, 1 ) * LengthCurv( ctx, ...
                curvArray( ind ), 0, 1 );
        end
        t       = lCurvs( : ).^2;
    else
        t       = ones( N * NCoeff, 1  );
    end

    D       = diag( 1 ./ t );
    Dinv    = diag( t ); 
end