function [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx )
%#codegen
% FeedratePlanning : Compute the optimal feedrate w.r.t to a set of
% constraints.
persistent kopt;
if( isempty( kopt ) ), kopt = 1; end
opt_struct  = constrCurvStructType;    % Type of returned curvStruct
quit        = false;                   % Flag used to quit the optimization
optimized   = false;                   % Does the optimization successed
ctx.op      = Fopt.Opt;                % Current state of the FSM

% Check if empty queue after splitting. If yes, stop optimization
if ctx.q_split.isempty, [ ctx.op, quit ] = empty_queue_split(); return; end

if coder.target( 'MATLAB' )
    if IsEnabledDebugLog( DebugCfg.OptimProgress )
        fprintf( '%4d/%u\n', ctx.k0, ctx.q_split.size );
    end
end

% Increment index on q_split
if ctx.go_next, ctx.k0 = ctx.k0 + 1; end

if ( ctx.k0 <= ctx.q_split.size )
    if ctx.try_push_again
        % Do nothing, we already have the last one optimized
    elseif ~ctx.zero_end

        [ window, NWindow ] = get_window( ctx.k0, ctx.cfg.NHorz, ctx.q_split );

        first = window( 1 );
        last  = window( NWindow );

        % Handle the zero speed at start
        if ( isAZeroStart( first ) )
            ctx.zero_start  = true;
            window          = window( 2 : end );
            NWindow         = NWindow -1;
        else
            ctx.zero_start  = false;
        end

        % Handle the zero speed at end
        if( isAZeroEnd( last ) )
            NWindow         = NWindow -1;
        end

        if( isAZeroEnd( last ) && ~ctx.zero_start )
            ctx.zero_end    = true;
        else
            ctx.zero_end    = false;
        end

        if( ctx.zero_start )
            [ v_0, at_0 ]   = calcZeroConstraints( ctx, first, false );
            ctx.v_0         = v_0;
            ctx.at_0        = at_0;
        end

        if( ctx.zero_end )
            [ v_1, at_1 ]   = calcZeroConstraints( ctx, last, true );
            ctx.v_1         = -v_1;
            ctx.at_1        = -at_1;
        else
            ctx.v_1         = -ctx.cfg.v_1;
            ctx.at_1        = -ctx.cfg.at_1;
        end

        [ ctx, Coeff, success, status, msg ] = ...
            FeedratePlanning_LP( ctx, window, ctx.cfg.amax, ctx.cfg.jmax, ...
            ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ...
            ctx.u_vec, NWindow );

        if( success == 1 )      % Optimization succed
            optimized   = true;
            opt_struct  = ctx.q_split.get( ctx.k0 );
            opt_struct.Coeff = Coeff( :, 1 );

            % Check if end of the queue
            if( ctx.zero_end && ( ctx.k0 + NWindow ) >= ctx.q_split.size )
                ctx.reached_end = true;
            end

        else
            [ quit, ctx ] = opt_error( ctx, msg ); return;
        end
    else
        optimized   = true;
        kopt = kopt + 1;
        opt_struct = ctx.q_split.get( ctx.k0 );

        if( ~isAZeroEnd( opt_struct ) )
            opt_struct.Coeff = ctx.Coeff( :, kopt );
        else
            ctx.zero_end  = false;
            kopt = 1;
        end
    end
else
    ctx.op = Fopt.Finished;
end
end

function [ op, quit ] = empty_queue_split()
% Treat the case of an empty queue after splitting operation
if coder.target( 'MATLAB' )
    diary on;
end
DebugLog( DebugCfg.Validate, 'Queue empty...\n' );
op      = Fopt.Finished;
quit    = true;
end

function [ window, NWindow ] = get_window( k0, NHorz, q_curves )

window = repmat( constrCurvStructType, 1, NHorz );

kend = min( double( k0 + NHorz -1 ), q_curves.size );

ind = 0;

for curv_ind = k0 : int32( kend )
    ind = ind + 1;

    % store the value in the queue
    curv            = q_curves.get( curv_ind );
    window( ind )   = curv;
    % Check if zero speed at the end
    if( isAZeroEnd( curv ) ), break; end
end

NWindow = ind;
end

function [ quit, ctx ] = opt_error( ctx, msg )
if coder.target('MATLAB')
    c_assert( true, 'OPTIMIZATION FAILED' );
else
    DebugLog( DebugCfg.Global, 'OPTIMIZATION FAILED!\n' );
    ctx.errcode = FeedoptPlanError.OptimizationFailed;
end
ctx.op = Fopt.Finished;
quit = true;
return;
end