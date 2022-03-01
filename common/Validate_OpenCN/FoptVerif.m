function [status, ratioTOpt, pvec, max_vec_logic] = FoptVerif(ctx, uvec, tol)

status = 0;         % Success default
ratioTOpt = 0;

% uvec will be empty if q_opt is empty
if isempty(uvec)
    bitset(status, 5);
    return;
end

DebugLog(DebugCfg.Validate, 'Fopt Verif...\n');

t = -ctx.cfg.dt;
t_max = 0;

k_max = size(uvec, 1);

tvec = zeros(k_max, 1);
pvec = zeros(k_max, 3);
vvec = zeros(k_max, 1);
vvec_norm = zeros(k_max, 1);
fvec = zeros(k_max, 1);
avec = zeros(k_max, 3);
jvec = zeros(k_max, 3);
max_vec_logic = zeros(k_max, 1);

diary off;

countInPercent = 0;
for k=1:k_max
    
    if( floor(k / k_max * 100) > countInPercent )  
        DebugLog(DebugCfg.OptimProgress, '%3d [%%] \n', countInPercent);
        countInPercent = countInPercent + max(5, floor(100/k_max));
    end

    ucum = uvec(k);
    u = ucum - floor(ucum);
    
    if k == 1
        Curv = ctx.q_opt.get(1);
    else
        Curv = ctx.q_opt.get(ceil(ucum));
    end
            
    SplineCurv = ctx.q_splines.get(Curv.sp_index);
    
    pvec(k, :) = EvalPosition(Curv, SplineCurv, u);
    
    [vvec(k, :), avec(k, :), jvec(k, :)] =...
        CalcVAJ(ctx, Curv, ctx.Bl, u);
    
    fvec(k, :) = Curv.FeedRate*60;     
    
    t = t + ctx.cfg.dt;
    
    tvec(k) = t;
    
    % vvec in [mm/s], fvec in [mm/min]
    % fvec - specified feedrate (F code in gcode file)
    % vvec_norm - normalized feedrate
    vvec_norm(k, :) = vvec(k, :)*60./fvec(k, :);
    avec(k, :) = abs(avec(k, :)./ctx.cfg.amax); % abs normalized
    jvec(k, :) = abs(jvec(k, :)./ctx.cfg.jmax); % abs normalized
    
    % max constraints respect verif
    if any(vvec_norm(k, :) > 1+tol.v_tol)
        bitset(status, 1);
    end
    
    if any(avec(k, :) > 1+tol.a_tol)
        bitset(status, 2);
    end
    
    if any(jvec(k, :) > 1+tol.j_tol)
        bitset(status, 3);
    end
    
    % time-optimatity verif
    condv = vvec_norm(k, :) > 1-tol.tol_opt_v;
    conda = any(avec(k, :) > 1-tol.tol_opt_a);
    condj = any(jvec(k, :) > 1-tol.tol_opt_j);
    
    if any([condv, conda, condj])
        t_max = t_max + ctx.cfg.dt;
        max_vec_logic(k) = 1;
    end

     
end

DebugLog(DebugCfg.OptimProgress, '%3d [%%] \n', 100);

ratioTOpt = t_max/tvec(end);

if ratioTOpt < tol.TOpt_tol
    bitset(status, 4);
end

%% Plots

if IsEnabledDebugLog(DebugCfg.Plots)
    
    % Max time plot
    figure
    plot(tvec, vvec_norm)
    hold on
    plot(tvec, avec)
    hold on
    plot(tvec, jvec)
    title('Nomalized absolute vnorm, axyz, jxyz')
    xlabel('time [s]')
    xlim([0 tvec(end)]);
    ylim([-0.2 1.2])
    legend('vnorm', 'ax', 'ay', 'az', 'jx', 'jy', 'jz')
    grid

    % Max plot
    figure
    scatter(pvec(:, 1), pvec(:, 2), 1, max_vec_logic, 'o')
    map = [1 0 0; ... % red
           0 1 0];    % green
    colormap(map)
    title('Maximum parameter, absolute value, normalized')
    xlabel('x')
    ylabel('y')
    zlabel('z')
    grid

    
end
   
end