function uvec = PlotResampled_BR(ctx, t_max, dt)

uvec = [];

if ctx.q_opt.isempty()
    return;
end

t_mach_max_s = t_max*60; % [s]

ktick_max = round(t_mach_max_s/dt);

uvec = zeros(ktick_max, 1);

ktick = 1;

state = ResampleState(dt);
N = ctx.q_opt.size();
DebugLog(DebugCfg.Validate, 'Resampling ...\n');

if coder.target('matlab')
    diary off;
end

t = 0;

for k = 1:N
    
    DebugLog(DebugCfg.OptimProgress, '%4d/%d\n', k, N);
    Curv = ctx.q_opt.get(k);
    Curv.MaxConstantFeedRate = GetCurvMaxFeedrate(ctx, Curv);
    state = ResampleNoCtx(state, ctx.Bl, Curv);
    
    while ~state.go_next
        state.dt = dt;  
        uvec(ktick) = state.u + double(k) - 1;
        ktick = ktick + 1;
        state = ResampleNoCtx(state, ctx.Bl, ctx.q_opt.get(k));
    end

    state.go_next = false;
    if ktick > ktick_max
        DebugLog(DebugCfg.Warning, 'Breaking because ktick > %d', ktick_max);
        break;
    end
end

ktick = ktick - 1;
uvec = [0; uvec(1:ktick)];

end
