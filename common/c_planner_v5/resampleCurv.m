function [ state, ud, udd, uddd ] = resampleCurv(state, Bl, curv_mode, ...
    coeff, constJerk, dt, ...
    curv_a, curv_b)

% resampleCurvDebug :
%
% Inputs :
%
% state         : Structure about the current state
%           u :       curv parameter [0,1]
%           go_next : {0 : stay at on the same curve, 1 : move to the next}
%           dt :      time step used for the discretization
%           isOutsideRange : {true : if u is out of range}
% Bl            : Structure for the spline object used during the optimization
% curv_mode     : Zero speed mode for the curve
% coeff         : The resulting coeff of the optimization
% useConstJerk  : ( Boolean ) Use a constant jerk for u
% constJerk     : The actual value of the const jerk
% dt            : Sampling time
% curv_a        :  Curve parameter a for affine transform
% curv_b        :  Curve parameter b for affine transform
%
% Outputs :
% state         : Updated input state
% ud            : Derivative of u
% udd           : Second derivative of u
% uddd          : Third derivatibe of u

coder.inline( "never" );

if coder.target( "MATLAB" )
    [ state, ud, udd, uddd ] = resampling_mex( state, Bl, curv_mode, ...
    coeff, constJerk, dt, ...
    curv_a, curv_b);
else

    if      ( curv_mode == ZSpdMode.ZN )
        [ u, ud, udd, uddd ] = constJerkU( constJerk, dt, false, ...
            curv_a, curv_b );
    elseif  ( curv_mode == ZSpdMode.NZ )
        T = dt - min( state.dt, dt );
        [ u, ud, udd, uddd ] = constJerkU( constJerk, T, true, ...
            curv_a, curv_b );
    else
        [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, state.u, state.dt );
    end

    du      = u - state.u;
    du_min  = check_minimum_precision( du );
    if( du_min > du ), u = state.u + du_min; end

    if( u > 1 )
        [ q ]    = bspline_eval_vec( Bl, coeff', [ state.u, 1 ] );
        Tr       = 2 * ( 1 - state.u ) / ( sqrt( q( end ) ) + sqrt( q( 1 ) ) );
        state.dt = check_minimum_precision( state.dt - Tr );
        state.isOutsideRange = true;
    end

    state.u = u;

    if( state.u >= 1 )
        state.go_next = true;
    else
        state.go_next = false;
    end
end
end

function [ u,  ud, udd, uddd ] = ResampleNN( coeff, Bl, uk, dt )

[ q, qd, qdd ] = bspline_eval( Bl, coeff', uk );

[ ud, udd, uddd ] = calcUfromQ( q, qd, qdd );

u = uk + mysqrt( q ) * dt + (qd * dt ^ 2 ) / 4;
end

function [ d ] = check_minimum_precision( d )
% check_minimum_precision : Avoid effect numerical problem
MIN_PRES = eps;
if(d < MIN_PRES), d = MIN_PRES; end
end