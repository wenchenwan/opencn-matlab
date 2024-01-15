function [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx )
%#codegen
% FeedratePlanning : Compute the optimal feedrate w.r.t to a set of
% constraints.
%
% Inputs :
%   ctx : The context of the computational chain
%
% Outputs :
%   ctx         : The context of the computational chain
%   optimized   : Is optimized
%   opt_struct  : optimized structure
%   quit        : Quit flag
%
persistent kopt;
if( isempty( kopt ) ), kopt = 1; end

opt_struct  = constrCurvStructType;    % Type of returned curvStruct
quit        = false;                   % Flag used to quit the optimization
optimized   = false;                   % Does the optimization successed
ctx.op      = Fopt.Opt;                % Current state of the FSM

% Check if empty queue after splitting. If yes, stop optimization
if ctx.q_split.isempty
    [ ctx.op, quit ] = empty_queue_split( ctx.cfg.ENABLE_PRINT_MSG ); 
    return; 
end

ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + ...
    ctx.q_split.size, mfilename );

% Increment index on q_split
if ctx.go_next, ctx.k0 = ctx.k0 + 1; end

if ( ctx.k0 <= ctx.q_split.size )
    
    if ~ctx.zero_end
        % Get window of interest in from a given queue
        [ window, NWindow ] = feedratePlanningGetwindow( ctx.k0, ...
                                ctx.cfg.NHorz, ctx.q_split );

        % Prepare the boundaries conditions of the problem
        [ ctx, window, NWindow ] = feedratePlanningSetupCurves( ...
                ctx, window, NWindow );

        
            % Start the optimization
            [ ctx, Coeff, success, status, msg ] = ...
                FeedratePlanning_LP( ctx, window, ctx.cfg.amax, ctx.cfg.jmax, ...
                ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ...
                ctx.u_vec, NWindow );
            
            if( ~( success || ctx.zero_start || ctx.zero_end ) )
                [ ctx, window, NWindow ] = feedratePlanningForceZeroStop( ...
                    ctx, window, NWindow );
                [ ctx, Coeff, success, status, msg ] = ...
                    FeedratePlanning_LP( ctx, window, ctx.cfg.amax, ctx.cfg.jmax, ...
                    ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ...
                    ctx.u_vec, NWindow );
            end
        
        % Extract the solution
        if( success )      
            % Optimization succed
            if( coder.target( 'MATLAB' ) )
                curvArray = window( 1 : NWindow );
                DebugOptimization.getInstance().add_result( ctx, ctx.Bl, ...
                    ctx.BasisVal, curvArray, Coeff );
            end

            kopt = 1;
            
            optimized   = true;
            opt_struct  = ctx.q_split.get( ctx.k0 );
            
            if( ~isAZeroStart( opt_struct ) )
                opt_struct.Coeff = Coeff( :, kopt );
                kopt = kopt + 1;
            else
                ctx.zero_start  = false;
            end

            % Check if end of the queue
            if( ctx.zero_end && ( ctx.k0 + NWindow ) >= ctx.q_split.size )
                ctx.reached_end = true;
            end

        else
            ocn_assert( true, "OPTIMIZATION FAILED...", mfilename );
        end
    else
        optimized   = true;

        if( ctx.zero_forced && ( kopt > size( ctx.Coeff, 2 ) ) )
            opt_struct  = ctx.zero_forced_buffer( 1 );
            ctx.q_split.set( ctx.k0, ctx.zero_forced_buffer( 2 ) );
            ctx.k0      = ctx.k0 - 1;
            ctx.zero_forced = false;
        else
            opt_struct = ctx.q_split.get( ctx.k0 );
        end

        if( ~isAZeroEnd( opt_struct ) )
            opt_struct.Coeff = ctx.Coeff( :, kopt );
        else
            ctx.zero_end  = false;
        end
        
        kopt = kopt + 1;
    end
    
else
    ctx.op = Fopt.Finished;
end
end

function [ op, quit ] = empty_queue_split( enablePrint )
% Treat the case of an empty queue after splitting operation
if coder.target( 'MATLAB' )
    diary on;
end

ocn_print( enablePrint, "Queue empty...", mfilename );
op      = Fopt.Finished;
quit    = true;
end

