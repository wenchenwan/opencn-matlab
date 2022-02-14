function uvec = PlotResampled_BR(ctx, t_max_min, dt, params)
% PlotResample_BR : Do the resampling of the time continuous curves. The
% plot can be disable with the param containers.
%
% ctx       : Context
% t_max_min : Maximum time in minutes
% dt        : Sampling time in seconds
% params    : 
%   - disablePlot = True / False (Default) : Disable the plot 

uvec = [];

if ctx.q_opt.isempty()
    return;
end

t_mach_max_s = t_max_min*60; % [s]

ktick_max = round(t_mach_max_s/dt);

uvec = zeros(ktick_max, 1);

ktick = 1;

state = ResampleState(dt);
N = ctx.q_opt.size();
DebugLog(DebugCfg.Validate, 'Resampling ...\n');
DebugLog(DebugCfg.OptimProgress, 'Resampling ...\n');

pvec = zeros(200000, 3);
vvec = zeros(200000, 1);

for k = 1:N
    
    DebugLog(DebugCfg.OptimProgress, '%4d/%d\n', k, N);
    Curv = ctx.q_opt.get(k);
    SplineCurv = ctx.q_splines.get(Curv.sp_index);
    Curv.MaxConstantFeedRate = GetCurvMaxFeedrate(ctx, Curv);
    state = ResampleNoCtx(state, ctx.Bl, Curv);
    
    while ~state.go_next
        state.dt = dt;  
        uvec(ktick) = state.u + double(k) - 1;
        r0D = EvalPosition(Curv, SplineCurv, state.u);
        [Vnorm, ~, ~] = CalcVAJ(ctx, Curv, ctx.Bl, state.u);
        pvec(ktick, :) = r0D;
        vvec(ktick) = Vnorm;
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

if( nargin < 4 || ~params('disablePlot') )
    figure
    scatter3(pvec(:, 1), pvec(:, 2), pvec(:, 3), 1, vvec*60, 'o')
    colormap jet
    set(gca, 'Projection','orthographic')
    xlabel('x')
    ylabel('y')
    zlabel('z')
    colorbar
end

end
