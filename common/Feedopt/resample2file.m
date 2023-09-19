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
state           = ResampleState( dt, ctx.cfg.DefaultZeroStopCount );
countInPercent  = double( 0 );

ind = 0; sizeBuffer = 1E7; t = 0;
buffer = zeros( sizeBuffer, 5 + 3 * ctx.cfg.NumberAxis );
firstTime = true;

counter = 0;

for k = 1 : N
    countInPercent = printAvancement(countInPercent, k, N);

    Curv                        = ctx.q_opt.get( k );
    Curv.MaxConstantFeedRate    = 0;%GetCurvMaxFeedrate( ctx, Curv );
    state.go_next               = false;

    while ~state.go_next

        [ state ] = resampleCurv( state, ctx.Bl, ...
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

            u       = state.u + double(k) - 1 ;
            cf      = Curv.Info.FeedRate;
            [ r, ~, a, j ]  = calcRVAJfromU( ctx, Curv, state.u, state.ud, ...
                                             state.udd, state.uddd );
            [ r0D, r1D ]    = EvalCurvStruct( ctx, Curv, state.u );
            
            ctx.kin = ctx.kin.set_tool_length( Curv.tool.offset.z );
%             r = ctx.kin.r_relative(r);

            if( ~Curv.Info.TRAFO )
                r1D = ctx.kin.v_relative( r0D, r1D );
            end
            v       = r1D .* state.ud;
            feed    = vecnorm( v( ctx.cfg.indCart ) );

            f_norm  = feed / Curv.Info.FeedRate;
            a       = abs( a ./ ctx.cfg.amax( ctx.cfg.maskTot )' );
            j       = abs( j ./ ctx.cfg.jmax( ctx.cfg.maskTot )' );
            
            % Control numerical derivatives
            
            [v_norm, a_norm, j_norm] = assert_numerical_derivative( r, ctx.cfg );

%             assert( all(v_norm <= 1), "Counter " + counter + " : Velocity is above the limits");
%             assert( all(a_norm <= 1), "Counter " + counter + " : Acceleration is above the limits");
%             assert( all(j_norm <= 1), "Counter " + counter + " : Jerk is above the limits");

            buffer( ind, : ) = [ t, u, f_norm, feed, cf, r', a', j' ];
            counter = counter + 1;
        end
    end
    state = ResampleState( state.dt, ctx.cfg.DefaultZeroStopCount );
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

function [v_norm, a_norm, j_norm] = assert_numerical_derivative( pos, cfg )
    persistent buffer;
    if( isempty(buffer) ), buffer = []; end

    [ buffer, v, a, j ] = numerical_derivatives( buffer, pos, cfg.dt );

    v_norm = abs( v ./ cfg.vmax( cfg.maskTot )' );
    a_norm = abs( a ./ cfg.amax( cfg.maskTot )' );
    j_norm = abs( j ./ cfg.jmax( cfg.maskTot )' );
    
    if(any(v_norm > 1))
        disp("Velocity is not in the limits");
    end

    if(any(a_norm > 1))
        disp("Acceleration is not in the limits");
    end

    if(any(j_norm > 1))
        disp("Jerk is not in the limits");
    end
end