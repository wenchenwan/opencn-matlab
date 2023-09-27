function [ state ] = resampleCurv(state, Bl, curv_mode, ...
    coeff, constJerk, dt, GaussLegendreX, GaussLegendreW )
% resampleCurv :
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
% state         : Updated input state

coder.inline( "never" );

if coder.target( "MATLAB" )
    [ state ] = resampling_mex( 'resampleCurv', state, Bl, curv_mode, ...
    coeff, constJerk, dt, GaussLegendreX, GaussLegendreW );
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
        [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, state.u, state.dt );
    end
    state.dt = dt;

    u = check_u_state_validity( u, state );
    
    % Check if u is outside the range
    if( u > 1 )
        state.isOutsideRange = true;
        if( curv_mode == ZSpdMode.NN )
            % Numerical integration : Gauss-Legendre
            GL_X   = GaussLegendreX;
            GL_W   = GaussLegendreW;
    
            % Linear mapping from[-1, 1] to [state.u, 1]
            uval  = ( state.u * ( 1 - GL_X ) + ( 1 + GL_X) ) / 2;
            Ival  = 1 ./ sqrt( bspline_eval_vec( Bl, coeff', uval ) );
            % Gauss Legendre integration
            Tr    = Ival.' * GL_W * ( 1 - state.u ) / 2;
            % Check remaining time is bellow current time step
            if( Tr >= dt )
                % Second order Taylor interpolation
                a = udd/2; b = ud; c = state.u -1;
            
                Delta = b^2 - 4 * a * c;
                Tr  = (-b + sqrt(Delta) ) / ( 2 *  a);
                
                % Need to use first order Taylor
                if( isnan(Tr) )
                    Tr = -c / b;
                else
                    % Check the second solution
                    Tr2 = (-b - sqrt(Delta) ) / ( 2 *  a);
                
                    if((Tr2 > 0) && (Tr2 <= dt))
                        Tr = Tr2;
                    end
                end
            end
        elseif( curv_mode == ZSpdMode.ZN )
            [ time ] = constJerkTime(constJerk, [state.u, 1], false);
            Tr = time(2) - time(1);
        else
            state = state.startZeroStopTime();
            return;
        end
        % Ensure Tr <= dt and Tr >= 0
        state.dt = check_minimum_precision_dt( dt - Tr, dt );
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

function [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, uk, dt )
[ q, qd, qdd ] = bspline_eval( Bl, coeff', uk );

[ ud, udd, uddd ] = calcUfromQ( q, qd, qdd );

% Taylor odre 2
u = uk + ud * dt + ( udd * dt ^ 2 ) / 2;

% Ensure u > uk
if( u  <= uk )
    % Taylor odre 1. Note since ud > 0
    u = uk + ud * dt;
end
end

function [ d ] = check_minimum_precision( d )
% check_minimum_precision : Avoid effect numerical problem
persistent dMin;

if( isempty( dMin ) ), dMin = eps; end

if(d < dMin ), d = dMin;  end

end

function [ d ] = check_minimum_precision_dt( d, dt )
% check_minimum_precision : Avoid effect numerical problem
if(d <= 0.0 ) d = 0.0;  end

if(d > dt ), d = dt; end
end

function [ u ] = check_u_state_validity( u, state )
assert( u > 0, "U parameter should not be negative during resampling" );

u  = state.u + check_minimum_precision( u - state.u );
end