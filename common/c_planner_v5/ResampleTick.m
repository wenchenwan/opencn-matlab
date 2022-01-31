function [ctx, again, again_t] = ResampleTick(ctx, dt)
again = false;
again_t = 0;

if ctx.resample_end || ctx.q_opt.size < ctx.resample_k
    ctx.resample_end = true;
    return;
end

uk = ctx.resample_u;
k = ctx.resample_k;

CurOptStruct = ctx.q_opt.get(k);

[ukp1, qk, ~] = Resample(CurOptStruct, ctx.Bl, uk, dt);

% Don't get stuck on numerical precision
if ukp1 - uk < eps
    ukp1 = uk + eps;
end

if ukp1 < 1
    ctx.resample_u = ukp1;
else
    ukp1      = 1;

    [~, qkp1, ~] = Resample(CurOptStruct, ctx.Bl, ukp1, dt);
    Trest     = 2*(ukp1 - uk) / (mysqrt(qkp1) + mysqrt(qk));
    
    if Trest > dt
        dt_begin = 0;
    else
        dt_begin  = dt - Trest;
    end
    
    ctx.resample_u = 0;
    ctx.resample_k = ctx.resample_k + 1;
    
    again = true;
    again_t = dt_begin;
end

end

function [ukp1, qk, dk] = Resample(CurOptStruct, Bl, u, dt)
    if CurOptStruct.zspdmode == ZSpdMode.ZN
        [ukp1,qk, dk] = ResampleZN(CurOptStruct, u, dt);
    elseif CurOptStruct.zspdmode == ZSpdMode.NN
        [ukp1, qk, dk] = ResampleNN(CurOptStruct, Bl, u, dt);
    elseif CurOptStruct.zspdmode == ZSpdMode.NZ
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
    qk = CurOptStruct.ConstJerk*t.^2/2;
    dk = 2*CurOptStruct.ConstJerk*t;

    ukp1 = CurOptStruct.ConstJerk.*(t+dt).^3/6;
end

function [ukp1, qk, dk] = ResampleNN(CurOptStruct, Bl, u, dt)
    c_assert(~CurOptStruct.UseConstJerk, 'NN is using jerk');

    uk = u;
    [qk, dk, ~] = bspline_eval(Bl, CurOptStruct.Coeff, uk);
    ukp1 = uk + dk*dt^2/4 + mysqrt(qk)*dt;
end

function [ukp1, qk, dk] = ResampleNZ(CurOptStruct, u, dt)
    c_assert(CurOptStruct.UseConstJerk, 'NZ is not using const jerk');

    t = (6*(1-u)/CurOptStruct.ConstJerk)^(1/3);
    
    qk = CurOptStruct.ConstJerk*t.^2/2;
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
