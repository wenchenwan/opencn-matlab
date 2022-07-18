function [ state, ud, udd, uddd ] = resampleCurv(state, Bl, curv_mode, ...
    coeff, constJerk, dt, curv_a, curv_b, GaussLegendreX, GaussLegendreW )
% resampleCurv :
%
% Inputs :
%
% state         : Structure about the current state
%           u :       curv parameter [0,1]
%           go_next : {0 : stay at on the same curve, 1 : move to the next}
%           dt :      time step used for the discretization
%           isOutsideRange : {true : if u is out of range}
% Bl                : Structure for the spline object used during the optimization
% curv_mode         : Zero speed mode for the curve
% coeff             : The resulting coeff of the optimization
% useConstJerk      : ( Boolean ) Use a constant jerk for u
% constJerk         : The actual value of the const jerk
% dt                : Sampling time
% curv_a            : Curve parameter a for affine transform
% curv_b            : Curve parameter b for affine transform
% GaussLegendreX    : Nodes used for the gauss-legendre integration
% GaussLegendreW    : Weights used for the gauss-legendre integration
%
% Outputs :
% state         : Updated input state
% ud            : Derivative of u
% udd           : Second derivative of u
% uddd          : Third derivatibe of u

coder.inline( "never" );

if coder.target( "MATLAB" )
    [ state, ud, udd, uddd ] = resampling_mex( state, Bl, curv_mode, ...
    coeff, constJerk, dt, curv_a, curv_b, GaussLegendreX, GaussLegendreW );
else

    if      ( curv_mode == ZSpdMode.ZN )
        [ u, ud, udd, uddd ] = constJerkU( constJerk, state.dt, false );
        
        if( u == 1 )
            u = constJerk .* state.dt .^3 / 6;
        end
        state.dt = state.dt + dt;

    elseif  ( curv_mode == ZSpdMode.NZ )        
        [ u, ud, udd, uddd ] = constJerkU( constJerk, state.dt, true );
        
        if( u == 1 )
            k_max  = ( 6 / constJerk )^( 1 / 3 );
            u = 1 - constJerk .* ( k_max - state.dt ) .^3 / 6;
        end        
        state.dt = state.dt + dt;
    else
        [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, state.u, state.dt );
        state.dt = dt;
    end
    
    if( state.u > 0 )
        du      = u - state.u;
        du_min  = check_minimum_precision( du );    
        if( du_min > du ), u = state.u + du_min - du; end
    end
    
    if( u > 1 )
        if      ( curv_mode == ZSpdMode.NN )
            [ q ]     = bspline_eval_vec( Bl, coeff', [ state.u, 1 ] );
            % Numerical integration : Gauss-Legendre
            GL_X   = GaussLegendreX;
            GL_W   = GaussLegendreW;

            % Linear map from[-1, 1] to [state.u, 1]
            uval  = ( state.u * ( 1 - GL_X ) + ( 1 + GL_X) ) / 2;
            Ival  = 1 ./ sqrt( bspline_eval_vec( Bl, coeff', uval ) );
            % Gauss Legendre integration
            Tr    = Ival.' * GL_W * ( 1 - state.u ) / 2;
        else
            Tuk = ( 6 * state.u / constJerk )^( 1 / 3 );
            T1  = ( 6 / constJerk )^( 1 / 3 );
            Tr  = T1 - Tuk; 
        end
        % Ensure Tr <= dt
        state.dt = check_minimum_precision_dt( dt - Tr, dt );
        state.isOutsideRange = true;
    else
        state.u     = u;
        state.ud    = ud;
        state.udd   = udd;
    end

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

if(d < dMin )
    d = dMin; 
end

end

function [ d ] = check_minimum_precision_dt( d, dt )
% check_minimum_precision : Avoid effect numerical problem
if(d <= 0.0 )
    d = 0.0; 
end

if(d > dt )
    d = dt; 
end

end