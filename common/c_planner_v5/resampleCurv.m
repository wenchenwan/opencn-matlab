function [state, qk, qd_k, qdd_k] = resampleCurv(state, Bl, Curv, dt)
% resampleCurv : 
% 
% Inputs : 
%
% state     : Structure about the current state 
%           u :       curv parameter [0,1]
%           go_next : {0 : stay at on the same curve, 1 : move to the next}
%           dt :      time step used for the discretization
%           isOutsideRange : {true : if u is out of range}
% Bl        : Structure for the spline object used during the optimization
% Curv      : Structure of the geometric curve
% dt        : Sampling time 
%
% Outputs : 
% state     : Updated input state
% qk        : Spline basis evaluated at k
% qd_k      : First order time derivative spline basis evaluated at k
% qdd_k     : Second order time derivative spline basis evaluated at k
coder.inline( "never" );

% Compute uk based on the typed of curves

if Curv.zspdmode == ZSpdMode.ZN
    [ukp1, qk, qd_k, qdd_k, q_1] = ResampleZN(Curv, state.u, state.dt);
elseif Curv.zspdmode == ZSpdMode.NN
    [ukp1, qk, qd_k, qdd_k] = ResampleNN(Curv, Bl, state.u, state.dt);
elseif Curv.zspdmode == ZSpdMode.NZ
    [ukp1, qk, qd_k, qdd_k, q_1] = ResampleNZ(Curv, state.u, state.dt);
else
    ukp1 = 0; qk   = 0; qd_k = 0; qdd_k  = 0; q_1 = 0;
    error('Should not get here');
end

du      = ukp1 - state.u;
du_min  = check_minimum_precision( du );

if( du_min > du )
    ukp1 = state.u + du_min; 
end

state.isOutsideRange = ( ukp1 > 1.0 );

% Handle case of uk is out of range
if( state.isOutsideRange ) % if uk is not in [0,1]
    % Compute Tr remaining in the current struct
    if( Curv.zspdmode == ZSpdMode.NN )
        q_1 = bspline_eval(Bl, Curv.Coeff', 1);
    end
    Tr = 2 * ( 1 - state.u )  / ( mysqrt(q_1) + mysqrt(qk) );
    state.dt        = check_minimum_precision( state.dt - Tr );
    state.u         = 0;
    state.go_next   = true;
else 
    state.dt        = dt;
    state.u         = ukp1;
    state.go_next   = false;
end

end

function [uk1,  q_uk, qd_uk, qdd_uk, q_1] = ResampleZN( ...
                                            CurOptStruct, uk, dt)
c_assert(CurOptStruct.UseConstJerk, 'ZN is not using const jerk');

t       = ( 6 * uk / CurOptStruct.ConstJerk )^(1/3);
uk1     = CurOptStruct.ConstJerk / 6 * (t + dt)^3;
q_uk    = ( CurOptStruct.ConstJerk^2 * t^4 ) / 4;
qd_uk   = ( CurOptStruct.ConstJerk^2 * t^3 ) * 3 / 4;
qdd_uk  = ( CurOptStruct.ConstJerk^2 * t^2 ) * 3 / 2;
q_1     = ( CurOptStruct.ConstJerk^2 ) / 4;
end

function [uk1,  q_uk, qd_uk, qdd_uk, q_1] = ResampleNZ( ...
                                            CurOptStruct, uk, dt)
c_assert(CurOptStruct.UseConstJerk, 'NZ is not using const jerk');

[uk1,  q_uk, qd_uk, qdd_uk] = ResampleZN(CurOptStruct, 1-uk, -dt);
uk1 = 1-uk1;
q_1 = 0;
end

function [uk1,  q_uk, qd_uk, qdd_uk ] = ResampleNN( ...
                                        CurOptStruct, Bl, uk, dt)
c_assert(~CurOptStruct.UseConstJerk, 'NN is using jerk');

[q_uk, qd_uk, qdd_uk , ~ ] = bspline_eval(Bl, CurOptStruct.Coeff', uk);

uk1 = uk + mysqrt( q_uk ) * dt + (qd_uk * dt^2 )/4;
end

function [ d ] = check_minimum_precision( d )

MIN_PRES = 1E-7;
if(d < MIN_PRES)
    d = MIN_PRES;
%     disp("Minimum supported precision reached...");
end
end