function [ ] = resample2file( ctx, fileName )
% resample2file : Performe the resampling on the whole queue q_opt.
% The resampled data are stored in a file.
%
% Inputs :
%       ctx :       The current context
%       fileName :  The name of the file used to store the data

if ctx.q_opt.isempty(), return; end % No optimization performed

N               = ctx.q_opt.size();
dt              = ctx.cfg.dt;
state           = ResampleState( dt );
countInPercent  = double( 0 );

ind = 0; sizeBuffer = 1E7; t = 0;
buffer = zeros( sizeBuffer, 5 + 3 * ctx.cfg.NumberAxis );
firstTime = true;

for k = 1 : N
    countInPercent = printAvancement(countInPercent, k, N);

    Curv                        = ctx.q_opt.get( k );
    Curv.MaxConstantFeedRate    = 0;%GetCurvMaxFeedrate( ctx, Curv );

    while ~state.go_next

        [ state, ud, udd, uddd ] = resampleCurv( state, ctx.Bl, ...
            Curv.Info.zspdmode, Curv.Coeff, ...
            Curv.ConstJerk, dt, Curv.a_param, ...
            Curv.b_param, ctx.cfg.GaussLegendreX, ...
            ctx.cfg.GaussLegendreW );

        if( ~state.isOutsideRange )
            t = t + 1;
            ind = ind + 1;
            if( ind > sizeBuffer )
                ind = 1;
                firstTime = write2files( firstTime, buffer, fileName );
            end

            u       = state.u + double(k) - 1 ;
            cf      = 0; %GetCurvMaxFeedrate(ctx, Curv);
            f       = Curv.Info.FeedRate;
            [ r, ~, a, j ]  = calcRVAJfromU( ctx, Curv, state.u, ud, udd, uddd );
            [ r0D, r1D ]    = EvalCurvStruct( ctx, Curv, state.u );
            
            r = ctx.kin.r_relative(r);

            if( ~Curv.Info.TRAFO )
                r1D = ctx.kin.v_relative( r0D, r1D );
            end
            v       = r1D .* state.ud;
            feed    = vecnorm( v( ctx.cfg.indCart ) );
            feed    = feed / Curv.Info.FeedRate;
            a       = abs( a ./ ctx.cfg.amax( ctx.cfg.maskTot )' );
            j       = abs( j ./ ctx.cfg.jmax( ctx.cfg.maskTot )' );
            
            buffer( ind, : ) = [ t, u, feed, f, cf, r', a', j' ];
        end
    end
    state.u = 0;
    state.ud = 0;
    state.isOutsideRange = false;
    state.go_next = false;
end

write2files( firstTime, buffer( 1 : ind , : ) , fileName );

printAvancement( 100 , N, N);
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

function [ firstTime ] = write2files( firstTime, A, fileName )

if( firstTime )
    param = {};
    firstTime = false;
else
    param = {'WriteMode', 'append'};
end

writematrix( A, fileName, param{:} );

end