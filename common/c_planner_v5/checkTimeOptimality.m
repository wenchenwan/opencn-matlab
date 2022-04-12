function [ status_res, t_opt_res, maxJerk ] = checkTimeOptimality( ctx , tol )
% checkTimeOptimality : Performe the resampling on the whole queue q_opt.
% Compute the overall time optimality. The resampled data are not stored.
% 
% Inputs : 
%       ctx : The current context
%       tol : Tolerance structure
% Output :
%       

status_res      = 0;
t_opt_res       = zeros(1, 5);

if ctx.q_opt.isempty(), return; end % No optimization performed

N               = ctx.q_opt.size();
dt              = ctx.cfg.dt;
state           = ResampleState( dt );
countInPercent  = double( 0 );
maxJerk         = 0;
for k = 1 : N

    countInPercent = printAvancement(countInPercent, k, N);

    Curv                        = ctx.q_opt.get( k );
    SplineCurv                  = ctx.q_splines.get( Curv.sp_index );
    Curv.MaxConstantFeedRate    = GetCurvMaxFeedrate( ctx, Curv );
    
    
    while ~state.go_next

        [state, qk, qd_k, qdd_k] = resampleCurv( state, ctx.Bl, Curv, dt );
        
        if( ~state.isOutsideRange )
            [r, rd, rdd, rddd]  = EvalCurvStructNoCtx( Curv, SplineCurv, state.u );
            feed    = vecnorm( rd * mysqrt( qk ) );
            a       = rdd * qk + rd * qd_k /2;
            j       = ( rddd * qk + 3 * rdd * qd_k / 2 + rd * qdd_k / 2 ) * mysqrt( qk );
            
            feed    = feed / Curv.FeedRate;
            a       = abs( a ./ ctx.cfg.amax' );
            j       = abs( j ./ ctx.cfg.jmax' );
            
            if(  (Curv.zspdmode == ZSpdMode.NN) && max(j) > maxJerk )
                maxJerk = max(j); 
            end

            [status]    = check_constraints( tol, feed, a, j );
            status_res  = bitor( status_res, status );
            [t_opt]     = check_time_optimality( tol, feed, a, j );
            t_opt_res   = t_opt_res + [1, t_opt, any( t_opt ) ];
        end
    end

    state.go_next = false;
end

printAvancement(countInPercent, N, N);
end

function [countInPercent] = printAvancement(countInPercent, k, N)
% printAvancement : Print the avancement of the sampling in percent
    if( floor( k * 100 / N ) > countInPercent )
        if( coder.target('matlab') )
            DebugLog(DebugCfg.OptimProgress, '%3d [%%]\n', countInPercent);
        else
            disp( '%3d [%%]\n', countInPercent );
        end
        countInPercent = double( countInPercent + max( 1, floor( 100 / N ) ) );
    end

end

function [status] = check_constraints( tol, feed, a, j )
status = 0;
% max constraints respect verif
if ( feed > 1 + tol.v_tol ), bitset(status, 1); end

if any( a > 1 + tol.a_tol ), bitset(status, 2); end

if any( j > 1 + tol.j_tol ), bitset(status, 3); end

end

function [t_opt] = check_time_optimality( tol, feed, a, j )
t_opt = zeros(1, 3);

% max constraints respect verif
if ( feed > 1 - tol.tol_opt_v ), t_opt(1) = 1; end

if any( a > 1 - tol.tol_opt_a ), t_opt(2) = 1; end

if any( j > 1 - tol.tol_opt_j ), t_opt(3) = 1; end

end