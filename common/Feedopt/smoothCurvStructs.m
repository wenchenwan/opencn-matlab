function [ ctx ] = smoothCurvStructs( ctx )
% smoothCurvStructs : Check if the curves in the q_compress queue are G2.
% If not, a transition is required. 
%
% Note : If the computation of a transition fails. A zero stop is forced.
%
% Inputs :
%   ctx : Context of the computational chain.
%
% Outputs :
%   ctx : Context of the computational chain.
%

% Optimal transitions calculation between segments whith G2 continuity

if ctx.q_compress.isempty(), return; end
ctx.k0  = int32( 1 );
Ncrv    = ctx.q_compress.size;

DebugLog( DebugCfg.Validate,         'Smoothing...\n' );
DebugLog( DebugCfg.OptimProgress,    'Smoothing...\n' );

curv = ctx.q_compress.get( 1 );
for k = 2 : Ncrv
    ctx.k0 = ctx.k0 + 1;
    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + Ncrv, mfilename );

    nextCurv = ctx.q_compress.get( k );

    [ needStop, needTransition ] = check_stop_and_transition( ctx, ...
        curv, nextCurv, ctx.cfg.Smoothing.ColTolSmooth, ...
        ctx.cfg.Smoothing.ColTolCosSmooth );

    if( needStop )
        % Add a zero stop
        [ ctx, curv ] = add_zero_stop( ctx, curv, nextCurv );
        if( coder.target( "MATLAB" ) )
            DebugTransition.getInstance.incZeroCurv;
        end
    elseif( needTransition  )
        if( ctx.cfg.Smoothing.Skip  )
            % Force a zero stop
            [ curv, nextCurv ]  = create_zero_end( curv, nextCurv );
            [ ctx, curv ]       = add_zero_stop( ctx, curv, nextCurv );
            if( coder.target( "MATLAB" ) )
                DebugTransition.getInstance.incZeroCurv;
            end
        else
            % Do the transition
            [ status, curv1C, curv2C, curvT, ret ] = ...
                calcTransition( ctx, curv, nextCurv );
            if( status == TransitionResult.Ok )
                ctx.q_smooth.push( curv1C );
                ctx.q_smooth.push( curvT );
                curv = curv2C;

                if( coder.target( "MATLAB" ) )
                    DebugTransition.getInstance.addTransition( curv1C, curvT, curv2C );
                end
            else
                % Force a zero stop
                [ curv, nextCurv ]  = create_zero_end( curv, nextCurv );

                if( coder.target( "MATLAB" ) )
                    DebugTransition.getInstance.addTransitionFail( curv, nextCurv, ret );
                end
                [ ctx, curv ]       = add_zero_stop( ctx, curv, nextCurv );

            end
        end
    else
        % Nothing to do with the curve
        ctx.q_smooth.push( curv );
        curv = nextCurv;
        if( coder.target( "MATLAB" ) )
            DebugTransition.getInstance.incNoNeedForTransition;
        end
    end
end

ctx.q_smooth.push( curv );

end

%-------------------------------------------------------------------------%
% Functions
%-------------------------------------------------------------------------%
function [ needStop, needTransition ] = check_stop_and_transition( ctx, ...
    curv, nextCurv, tol, tol_cos  )
needStop        = false;
needTransition  = false;

if( isAZeroEnd( curv ) ), needStop = true; return; end

if( nextCurv.b_param > 0 ), return; end

[ isSmooth ] = check_smoothness( ctx, curv, nextCurv, tol, tol_cos );

if( ~isSmooth ), needTransition = true; end

end
%-------------------------------------------------------------------------%
function [ curv, nextCurv ] = create_zero_end( curv, nextCurv )

if( isAZeroStart( curv ) )
    curv.Info.zspdmode = ZSpdMode.ZZ;
else
    curv.Info.zspdmode = ZSpdMode.NZ;
end

if( isAZeroEnd( nextCurv ) )
    nextCurv.Info.zspdmode = ZSpdMode.ZZ;
else
    nextCurv.Info.zspdmode = ZSpdMode.ZN;
end

end
%-------------------------------------------------------------------------%
function [ isSmooth ] = check_smoothness( ctx, curv0, curv1, tol, tol_cos )
[ r11, r1d1, r1dd1 ] = EvalCurvStruct( ctx, curv0, 1 );
[ r21, r2d1, r2dd1 ] = EvalCurvStruct( ctx, curv1, 0 );

[t1, ~,  kappa1] = calc_t_nk_kappa( r1d1, r1dd1 );
[t2, ~,  kappa2] = calc_t_nk_kappa( r2d1, r2dd1 );

isC0   = all( abs( r11 - r21 ) < tol, 'all' );
isG1   = collinear( t1, t2, tol_cos );
isG2   = all( abs( kappa1 -kappa2 ) < tol, 'all' );

isSmooth = ( isC0 && isG1 && isG2 );

end
%-------------------------------------------------------------------------%
%
function [ ctx, curv ] = add_zero_stop( ctx, curv, nextCurv )
ctx.q_smooth.push( curv );
curv = nextCurv;
end
