function StudyZeroResampling

    cfg = FeedoptDefaultConfig;
    ctx = InitFeedoptPlan(cfg);
    
%     gcode = ConstrLineStruct([0,0,0]', [1,0,0]', 10, ZSpdMode.ZZ);
%     TestWithCurvStruct(gcode);
    trafo = false;
    A0 = zeros(3,1); A1 = A0; U0 = A0; U1 = A0;

    gcode = ConstrHelixStruct(trafo, [0,0,0]', [1,1,1]', A0, A1, U0, U1, ...
                              [0,0,1]', pi/2, [0,0,0]', 4, 150, ZSpdMode.ZZ);
    TestWithCurvStruct(ctx, gcode);
    
end

function TestWithCurvStruct(ctx, gcode)
    cfg = ctx.cfg;
    dt = 1e-4;
    
    %% Initial Jerk Estimation
    % We perform an initial jerk estimation using the maximal
    % allowed per-axis jerk.
    jps = cfg.jmax(1);
    
    tmax = (6/jps)^(1/3);
    t = 0:dt:tmax;
    
    uk = jps*t.^3/6;
    d1uk = jps*t.^2/2;
    d2uk = jps*t;
    d3uk = jps;
    

    [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, gcode, uk);

    r3dt = r3D.*d1uk.^3 + 3*r2D.*d1uk.*d2uk + r1D.*d3uk;
    
    jt = abs(r3dt.'./cfg.jmax);
    max_jt = max(jt, [], 2);
    
    %% Actual computation using a limited max jerk
    jps = min(jps/max_jt(1), jps);
    
    tmax = (6/jps)^(1/3);
    t = 0:dt:tmax;
    
    uk = jps*t.^3/6;
    d1uk = jps*t.^2/2;
    d2uk = jps*t;
    d3uk = jps;
    

    [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, gcode, uk);

    r3dt = r3D.*d1uk.^3 + 3*r2D.*d1uk.*d2uk + r1D.*d3uk;
    r2dt = r2D.*d1uk.^2 + r1D.*d2uk;
    r1dt = r1D.*d1uk;
    r0dt = r0D;
    
    jt = abs(r3dt.'./cfg.jmax);
    at = abs(r2dt.'./cfg.amax);
    vt = abs(r1dt.'./gcode.FeedRate);
    norm_vt = mysqrt(sum(vt.^2, 2));
    
    max_jt = max(jt, [], 2);
    max_at = max(at, [], 2);
    
    stop_index_acc = find(max_at > 1, 1);
    stop_index_jerk = find(max_jt > 1, 1);
    stop_index_vel = find(norm_vt > 1, 1);

    figure;
    
    ax(1) = subplot(2,2,1);
    plot(t, jt,'--', t, max_jt);
    
    xlim([t(1), t(end)]);
    hold on;
    plot([t(stop_index_jerk), t(stop_index_jerk)], ylim, '-.k',...
        xlim, [1, 1], '-.k');
    hold off;
    title('Normalized jerk')
    legend('x', 'y', 'z', 'max')
    

    ax(2) = subplot(2,2,2);
    plot(t, at, '--', t, max_at);
    hold on;
    plot([t(stop_index_acc), t(stop_index_acc)], ylim, '-.k',...
        xlim, [1, 1], '-.k');
    hold off;
    title('Normalized acceleration')
    xlim([t(1), t(end)]);
    legend('x', 'y', 'z', 'max')
    
    
    ax(3) = subplot(2,2,3);
    plot(t, vt, t, norm_vt);
    xlim([t(1), t(end)]);
    hold on;
    plot([t(stop_index_vel), t(stop_index_vel)], ylim, '-.k',...
        xlim, [1, 1], '-.k');
    hold off;
    title('Normalized velocity')
    legend('x', 'y', 'z', 'norm')
    
    ax(4) = subplot(2,2,4);
    plot(t, r0dt');
    legend('x', 'y', 'z')
    title('Position')
    xlim([t(1), t(end)]);

end
