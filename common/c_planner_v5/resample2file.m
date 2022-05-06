function [ ] = resample2file( ctx, fileName )
% resample2fileDebug : Performe the resampling on the whole queue q_opt.
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

ind = 0; sizeBuffer = 1E4; t = 0;
buffer = zeros( sizeBuffer, 5 + 3 * ctx.cfg.NumberAxis );
firstTime = true;

for k = 1 : N

    countInPercent = printAvancement(countInPercent, k, N);

    Curv                        = ctx.q_opt.get( k );
    SplineCurv                  = ctx.q_spline.get( Curv.sp_index );
    Curv.MaxConstantFeedRate    = GetCurvMaxFeedrate( ctx, Curv );
        
    while ~state.go_next

         [ state, ud, udd, uddd ] = resampleCurv(state, ctx.Bl, ...
                                    Curv.Info.zspdmode, Curv.Coeff, ...
                                    Curv.ConstJerk, dt, Curv.a_param, ...
                                    Curv.b_param);
        
        if( ~state.isOutsideRange )
            state.dt = dt;
            t = t + 1;
            ind = ind + 1;
            if( ind > sizeBuffer )
                ind = 1;
                firstTime = write2files( firstTime, buffer, fileName );
            end
    
            u       = state.u + double(k) - 1 ; 
            cf      = GetCurvMaxFeedrate(ctx, Curv);
            f       = Curv.FeedRate;
            [ r, v, a, j ] = calcRVAJfromU( ctx, Curv, state.u, ud, udd, uddd );
            feed    = vecnorm( v );   
            feed    = feed / Curv.FeedRate;
            a       = abs( a ./ ctx.cfg.amax' );
            j       = abs( j ./ ctx.cfg.jmax' );
            
            buffer( ind, : ) = [ t, u, feed, f, cf, r', a', j' ];
        end
    end
    state.u = 0;
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