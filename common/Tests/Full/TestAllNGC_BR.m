function ctx = TestAllNGC_BR

    clear; clc;
    
    global DebugActive;
    DebugActive = true;
    
    cfg = FeedoptDefaultConfig;
    cfg.NDiscr = 20;
    cfg.NBreak = 10;
    cfg.NHorz = 5;
    cfg.DebugPrint = false;
    cfg.SkipCompressing = false;
    cfg.DebugOptimProgress = true;

    ngc_unit_list = string(fullfile('ngc_test/unit', {dir('ngc_test/unit/*.ngc').name}));
    ngc_full_list = string(fullfile('ngc_test/full', {dir('ngc_test/full/*.ngc').name}));
    ngc_full_Montres_list = string(fullfile('ngc_test/full', {dir('ngc_test/full/*Montre*.ngc').name}));
        
    for k=1:numel(ngc_full_Montres_list)
        
        cfg.source = char(ngc_full_Montres_list(k));
        ctx = InitFeedoptPlan(cfg);
        DebugLog([ctx.cfg.source, '\n']);
        tic;
        ctx = FeedoptPlanRun(ctx);
        time = toc;
        time_str = sprintf('time: %.2f seconds', time);
        figure;
        PlotCurvStructsBR_2(ctx, ctx.q_split.getall());
        title({ngc_full_Montres_list(k), time_str}, 'Interpreter', 'none');
        
    end

    % PlotResampled(ctx, 1e-3)

end

