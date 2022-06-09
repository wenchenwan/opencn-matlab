
function ctx = smoothCurvStructs(ctx)
% Optimal transitions calculation between segments whith G2 continuity

if ctx.q_compress.isempty(), return; end

Ncrv = ctx.q_compress.size;

DebugLog( DebugCfg.Validate,         'Smoothing...\n' );
DebugLog( DebugCfg.OptimProgress,    'Smoothing...\n' );


curv = ctx.q_compress.get( 1 );
for k = 2 : Ncrv
    nextCurv = ctx.q_compress.get( k );
    % Check neither of the two curves has a zero speed.
    if( isAZeroEnd( curv ) || isAZeroStart( nextCurv ) )
        ctx.programmed_stop = ctx.programmed_stop + 1;
        ctx.q_smooth.push( curv );
        curv = nextCurv;
    else
         % Computes transition
        [ curvC1, curvT, curvC2, status ] = ... 
        calcTransition( ctx, curv, nextCurv );

        if      ( status == TransitionResult.Ok )
            ctx.q_smooth.push( curvC1 );
            ctx.q_smooth.push( curvT );
            curv = curvC2;
        elseif  ( status == TransitionResult.Collinear )
            ctx.q_smooth.push( curv );
            curv = nextCurv;
        else  % If the transition fails, force a zero-stop
            ctx.forced_stop = ctx.forced_stop + 1;
            curv.Info.zspdmode      = ZSpdMode.NZ;
            nextCurv.Info.zspdmode  = ZSpdMode.ZN;
            ctx.q_smooth.push( curv );
            curv = nextCurv;
        end
    end
end

ctx.q_smooth.push( curv );

end
