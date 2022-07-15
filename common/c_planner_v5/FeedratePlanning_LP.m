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

indSlack =  []; %1 : numel( b );

[ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( f, ...
    A, b, Aeq, beq, indSlack, LP );

% C. Solve the optimization problem
[ ctx, Coeff, success, status, msg, beq ] = solve_LP( fSlack, ASlack, bSlack, ...
    AeqSlack, beqSlack, ctx, ...
    N, NWindow, "First LP" );

% 2) Optimization : second LP with jerk constraints and slack

if( true )
    % B. Constraints : Inequality and Equality
    % Feedrate, acceleration and jerk
    [ Aj, bj ] =  buildConstrJerk( ctx, CurvArray, Coeff, jmax, ...
        BasisVal, BasisValD, BasisValDD, u_vec );

    Atot = [ A; Aj ]; btot = [ b; bj ];

    indSlack = [ indSlack, numel( b ) + [ 1 : numel( bj ) ] ];

    [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( f, ...
        Atot, btot, Aeq, beq, indSlack, LP );

    [ ctx, Coeff, success, status, msg ] = solve_LP( fSlack, ASlack, bSlack, ...
        AeqSlack, beqSlack, ctx, ...
        N, NWindow, "Second LP" );
end

% Compute the continuity equations
X  = continuity * Coeff( : , 1 );

if( ~ctx.zero_start )
    ctx.v_0     = sqrt( X( 1 ) );
    ctx.at_0    = X( 2 );
end

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
% If optimization failed due with zero end constaints, decrease pseudo jerk
if( ~success && ( ctx.zero_end || ctx.zero_start ) )
    if( ctx.zero_end )
        % Read last curve ( NZ )
        last    = ctx.q_split.get( ctx.k0 + NWindow );
        count   = 0; iterMax = 15;
        atNorm  = -ctx.at_1;
        vNorm   = -ctx.v_1;

        while( ~success && count < iterMax )
            [ last, vNorm , atNorm ] = decrease_constjerk( ctx, last, true );
            beq( end-1 )   = -vNorm^2;
            beq( end )     = atNorm;
            [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b, ...
                Aeq, beq, ctx );
            count = count + 1;
        end
        % Set back the change into the queue
        ctx.q_split.set( ctx.k0 + NWindow, last );
        ctx.at_1    = -atNorm;
        ctx.v_1     = -vNorm;
    else
        % Read first curve ( ZN )
        first   = ctx.q_split.get( ctx.k0 );
        count   = 0; iterMax = 15;
        atNorm  = ctx.at_0;
        vNorm   = ctx.v_0;
        while( ~success && count < iterMax )
            [ first, vNorm , atNorm ] = decrease_constjerk( ctx, first, false );
            beq( 1 )   = vNorm^2;
            beq( 2 )   = atNorm;
            [ Coeff0, success, status, msg ] = c_simplex( f, sparse( A ), b, ...
                Aeq, beq, ctx );
            count = count + 1;
        end
        % Set back the change into the queue
        ctx.q_split.set( ctx.k0, first );
        ctx.at_0    = atNorm;
        ctx.v_0     = vNorm;
    end

end

% Check the status of the optimization
if( ~success )
    Coeff = [];
    if( coder.target( "MATLAB" ) ), fprintf( msg ); end
    error( optName + " failed...");
    return;
else
    Coeff   = reshape( Coeff0( 1 : end -1 ), N, NWindow );
    if( coder.target( "MATLAB" ) && Coeff0( end ) > 0.0 ) 
        fprintf( "Slack : " + Coeff0( end ) + "\n" ); 
    end
end

end

function [ fSlack, ASlack, bSlack, AeqSlack, beqSlack ] = add_slack( f, ...
    A, b, Aeq, beq, indSlack, LP )
[ nAL, nAc ] = size( A );

% Add condition of positivity on coeffs the 2 first and the two last are
% nto
Apos = zeros( nAc -4 , nAc + 1 ); bpos = -1E-3 * ones( nAc -4 , 1);
Apos( : , 3 : end-3  ) = -eye( nAc -4  );

% Slack variables
vecSlack    = zeros( nAL, 1 ); vecSlack( indSlack ) = -1;
fSlack      = [ f( : ); LP.SLACK_PENALTY ];
ASlack      = [ Apos; A, vecSlack; zeros( 1, nAc ), -1 ];
bSlack      = [ bpos; b ; 0 ];
AeqSlack    = [ Aeq, zeros( size( Aeq, 1), 1 ) ];
beqSlack    = beq;

end

function [ curv, vNorm, atNorm ] = decrease_constjerk( ctx, curv, isEnd )
curv.ConstJerk = curv.ConstJerk / 2;
[ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd );
end