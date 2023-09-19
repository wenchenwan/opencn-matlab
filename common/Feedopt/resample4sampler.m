function [] = resample4sampler( ctx, fileName )
% resample4sampler : Performe the resampling on the whole queue q_opt.
% The resampled data are stored in a csv file used by the sampler.
% 
% Inputs : 
%       ctx :       The current context
%       fileName :  The name of the file used to store the data  

if ctx.q_opt.isempty(), return; end % No optimization performed

N               = ctx.q_opt.size();
dt              = ctx.cfg.dt;
state           = ResampleState( dt, ctx.cfg.DefaultZeroStopCount );
countInPercent  = double( 0 );

ind = 0; sizeBuffer = 1E4; t = 0;
buffer = zeros( sizeBuffer, ctx.cfg.NumberAxis );
firstTime = true;

for k = 1 : N

    countInPercent = printAvancement(countInPercent, k, N);

    Curv                        = ctx.q_opt.get( k );
    SplineCurv                  = ctx.q_spline.get( Curv.sp_index );
    Curv.MaxConstantFeedRate    = 0;%GetCurvMaxFeedrate( ctx, Curv );
        
    while ~state.go_next

         [ state ] = resampleCurv(state, ctx.Bl, ...
                                    Curv.Info.zspdmode, Curv.Coeff, ...
                                    Curv.ConstJerk, dt, ctx.cfg.GaussLegendreX, ...
                                    ctx.cfg.GaussLegendreW );
        
        if( ~state.isOutsideRange )
            t = t + 1;
            ind = ind + 1;
            if( ind > sizeBuffer )
                ind = 1;
                firstTime = write2files( firstTime, buffer, fileName );
            end
   
            [ r ]  = calcRVAJfromU( ctx, Curv, state.u, state.ud, ...
                                    state.udd, state.uddd );
            
            if( ctx.cfg.NRot > 0 )
                r( ctx.cfg.indRot ) = rad2deg( r( ctx.cfg.indRot ) ); 
            end 

            buffer( ind, : ) = r( : ).';
        end
    end
    state.u              = 0;
    state.ud             = 0;
    state.isOutsideRange = false;
    state.go_next        = false;
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

p_default = { 'Delimiter', ' ' };

if( firstTime )
    param = p_default;
    firstTime = false;   
else
    param = [ p_default, { 'WriteMode', 'append' } ];
end

writematrix( A, fileName, param{ : } );

end