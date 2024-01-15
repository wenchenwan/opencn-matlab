function [ state ] = resampleCurv(state, Bl, curv_mode, ...
    coeff, constJerk, dt, GaussLegendreX, GaussLegendreW, enablePrint )
%#codegen
% resampleCurv : Resampling step.
%
% Inputs :
%
% state             : Structure containing the current state
% Bl                : Structure for the spline object used during the optimization
% curv_mode         : Zero speed mode for the curve
% coeff             : The resulting coeff of the optimization
% useConstJerk      : ( Boolean ) Use a constant jerk for u
% constJerk         : The actual value of the const jerk
% dt                : Sampling time
% GaussLegendreX    : Nodes used for the gauss-legendre integration
% GaussLegendreW    : Weights used for the gauss-legendre integration
%
% Outputs :
% state             : Updated input state.

coder.inline( "never" );

if( coder.target( "MATLAB" ) )
    DebugResampling.getInstance().increaseUCounter();
end

if coder.target( "MATLAB" )
    [ state ] = resampling_mex( 'resampleCurv', state, Bl, curv_mode, ...
    coeff, constJerk, dt, GaussLegendreX, GaussLegendreW, enablePrint );
else
    % Check for a zero stop 
    if( state.isAStop )
        state = state.decreaseStopCounter(); 
        return;
    end
    
    % Compute new u state depending of zspdmode
    if( curv_mode == ZSpdMode.ZN )
        [ time ] = constJerkTime(constJerk, state.u, false);
        isEnd = false; forcelimit = false;
        [ u, ud, udd, uddd ] = constJerkU( constJerk, time + state.dt, isEnd, ...
            forcelimit );
    elseif( curv_mode == ZSpdMode.NZ )
        [ time ] = constJerkTime(constJerk, state.u, true);
        isEnd = true; forcelimit = false;
        [ u, ud, udd, uddd ] = constJerkU( constJerk, time + state.dt, isEnd, ...
            forcelimit );
    else
        [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, state.u, state.dt, enablePrint );
    end
    state.dt = dt;

    u = check_u_state_validity( u, state, enablePrint );
    
    % Check if u is outside the range
    if( u > 1 )
        state.isOutsideRange = true;
        if( curv_mode == ZSpdMode.NN )
            TrVec   = zeros( 1, 4 );
            % Numerical integration : Gauss-Legendre
            GL_X   = GaussLegendreX;
            GL_W   = GaussLegendreW;
    
            % Linear mapping from[-1, 1] to [state.u, 1]
            uval  = ( state.u * ( 1 - GL_X ) + ( 1 + GL_X) ) / 2;
            Ival  = 1 ./ mysqrt( bspline_eval_vec( Bl, coeff', uval ) );
            % Gauss Legendre integration
            Tr    = Ival.' * GL_W * ( 1 - state.u ) / 2;
            
            if( ~isreal( Tr ) || isnan( Tr ) )
                Tr = dt;
            end

            if( Tr >= dt )
                a = udd/2; b = ud; c = state.u -1;

                Delta   = b^2 - 4 * a * c;
                
                if( Delta <= 0)
                    TrVec( 2 )  = -c / b;
                    TrVec( 3 )  = -b / a;
                elseif( b > 0 )
                    TrVec( 2 )  = 2 *  c / ( -b - mysqrt(Delta) );
                    TrVec( 3 )  = (-b - mysqrt(Delta) ) / ( 2 *  a );
                else
                    TrVec( 2 )  = (-b + mysqrt(Delta) ) / ( 2 *  a );
                    TrVec( 3 )  = 2 *  c / ( -b + mysqrt(Delta) );          
                end

                TrVec( 4 )  = -c / b;
                
                % Check validity
                TrVec( isnan( TrVec ) )     = dt;
                TrVec( ~isreal( TrVec ) )   = dt;                
                TrVec( ~( TrVec >= 0 ) )    = dt;
                TrVec( ~( TrVec <= dt ) )   = dt;

                yVec            = abs( a * TrVec.^2 + b * TrVec + c );
                [ ~, ind ]      = min( yVec );
                Tr              = TrVec( ind );
            end

        elseif( curv_mode == ZSpdMode.ZN )
            [ time ] = constJerkTime(constJerk, [state.u, 1], false);
            Tr = time(2) - time(1);
        else
            state = state.startZeroStopTime();
            return;
        end
        % Ensure Tr <= dt and Tr >= 0 and real
        state.dt = check_minimum_precision_dt( dt - Tr, dt, enablePrint );

        if( coder.target( "MATLAB" ) )
            DebugResampling.getInstance().addDT( state.dt );
        end

    else
        state.isOutsideRange = false;
        state = state.setU( u, ud, udd, uddd );
    end
    
    % Need to use the next curve structure
    if( u >= 1 )
        state.go_next = true;
    else
        state.go_next = false;
    end

end

end

function [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, uk, dt, enablePrint )
[ q, qd, qdd ] = bspline_eval( Bl, coeff', uk );

if( q < 0 )
    % Non-positive function, it is better to go out
    u = uk; ud = 0; udd = 0; uddd = 0;
    ocn_print( enablePrint, "Q should not be negative", mfilename );

    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseQNegativeCounter();
    end
    return;
end

[ ud, udd, uddd ] = calcUfromQ( q, qd, qdd );

% Taylor odre 2
u = uk + ud * dt + ( udd * dt ^ 2 ) / 2;  %+ ( uddd * dt ^ 3 ) / 6;

% Ensure u > uk
if( u  <= uk )
    % Taylor odre 1. Note since ud > 0
    u = uk + ud * dt;
end
end

function [ d_up ] = check_minimum_precision( d_low, d_up )
% check_minimum_precision : Avoid effect numerical problem

if( ~( d_up > d_low ) )
    d_up = d_up + eps( d_up );  
end

end

function [ d ] = check_minimum_precision_dt( d, dt, enablePrint )
% check_minimum_precision : Avoid effect numerical problem
if( isnan( d ) )
    d = 0.0;
    ocn_print( enablePrint, "Tr should not be nan", mfilename );
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseTNanCounter();
    end
end

if( ~isreal( d ) )
    d = 0.0;
    ocn_print( enablePrint, "Tr should be real", mfilename );
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseTNotRealCounter();
    end
end

if( d <= 0.0 ) 
    d = 0.0;
    ocn_print( enablePrint, "Tr should be positive", mfilename );
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseTNegativeCounter();
    end
end

% if( d > dt ) 
%     d = dt;
%     disp("Tr should not be larger than Ts", mfilename);
%     if( coder.target( "MATLAB" ) )
%         DebugResampling.getInstance().increaseTTooLargeCounter();
%     end
% end
end

function [ u ] = check_u_state_validity( u, state, enablePrint )
if( isnan( u ) )
    u = state.u;
    ocn_print( enablePrint, "U should not be nan", mfilename );

    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseUNanCounter();
    end
end

if( ~isreal( u ) )
    u = state.u;
    ocn_print( enablePrint, "U should be real", mfilename );

    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseUNotRealCounter();
    end
end

if( u < 0 )
    ocn_print( enablePrint, ...
        "U parameter should not be negative during resampling", mfilename );
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseUNegativeCounter();
    end
end

if( ~( u > state.u ) )
    ocn_print( enablePrint, ...
        "U parameter is too close from the previous one during resampling", ...
        mfilename );
        
    if( coder.target( "MATLAB" ) )
        DebugResampling.getInstance().increaseUNotIncreasingCounter();
    end
end

% ocn_assert( u > 0, "U parameter should not be negative during resampling", mfilename);
u  = check_minimum_precision( state.u, u );
end
