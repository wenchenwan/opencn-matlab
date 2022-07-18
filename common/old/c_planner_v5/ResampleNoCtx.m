function state = ResampleNoCtx(state, Bl, Curv)
coder.inline("never");

[ukp1, qk, ~] = Resample(Curv, Bl, state.u, state.dt);


if ukp1 < state.u
    ukp1 = 1;
end

if ukp1 - state.u < eps
    ukp1 = state.u + eps;
end



if ukp1 < 1
    state.u = ukp1;
else
    ukp1      = 1;
    
    [~, qkp1, ~] = Resample(Curv, Bl, ukp1, state.dt);
    Trest     = 2*(ukp1 - state.u) / (mysqrt(qkp1) + mysqrt(qk));
    
    if Trest > state.dt
        dt_begin = 0;
    else
        dt_begin  = state.dt - Trest;
    end
    
    state.u = 0;
    state.go_next = true;
    state.dt = dt_begin;
    % This recursive call was replaced by the 'again' output params
    % Callers should make sure to use them
    %    ctx = ResampleTick(ctx, dt_begin);
end

end



function [ukp1, qk, dk] = Resample(CurOptStruct, Bl, u, dt)
if CurOptStruct.Info.zspdmode == ZSpdMode.ZN
    [ukp1,qk, dk] = ResampleZN(CurOptStruct, u, dt);
elseif CurOptStruct.Info.zspdmode == ZSpdMode.NN
    [ukp1, qk, dk] = ResampleNN(CurOptStruct, Bl, u, dt);
elseif CurOptStruct.Info.zspdmode == ZSpdMode.NZ
    [ukp1, qk, dk] = ResampleNZ(CurOptStruct, u, dt);
else
    error('Should not get here');
end
end

function [ukp1,  qk, dk] = ResampleZN(CurOptStruct, u, dt)
c_assert(CurOptStruct.UseConstJerk, 'ZN is not using const jerk');

t = (6*u/CurOptStruct.ConstJerk)^(1/3);
if dt > 0
    t = round(t/dt)*dt;
end
qk = (CurOptStruct.ConstJerk*t^2/2)^2;
dk = 2*CurOptStruct.ConstJerk*t;

ukp1 = CurOptStruct.ConstJerk.*(t+dt).^3/6;
end

function [ukp1, qk, dk] = ResampleNN(CurOptStruct, Bl, u, dt)
c_assert(~CurOptStruct.UseConstJerk, 'NN is using jerk');

uk = u;
[qk, dk, ~] = bspline_eval(Bl, CurOptStruct.Coeff', uk);
ukp1 = uk + dk*dt^2/4 + mysqrt(qk)*dt;
end

function [ukp1, qk, dk] = ResampleNZ(CurOptStruct, u, dt)
c_assert(CurOptStruct.UseConstJerk, 'NZ is not using const jerk');

t = (6*(1-u)/CurOptStruct.ConstJerk)^(1/3);

qk = (CurOptStruct.ConstJerk*t^2/2)^2;
dk = -2*CurOptStruct.ConstJerk*t;

ukp1 = 1 - CurOptStruct.ConstJerk.*(t-dt).^3/6;
end

function T = EstimateT(CurOptStruct, Bl, u, target_u, sub_dt)
T = 0;
n = 0;
while u < target_u - eps
    [u, ~, ~] = Resample(CurOptStruct, Bl, u, sub_dt);
    T = T + sub_dt;
    n = n + 1;
end
fprintf('EstimateT: %d iterations, T = %f\n', n, T);
end
