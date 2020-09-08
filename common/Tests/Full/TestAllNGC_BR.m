function ctx = TestAllNGC_BR

    clear; clc;
    
    cfg = FeedoptDefaultConfig;
    cfg.NDiscr = 20;
    cfg.NBreak = 10;
    cfg.NHorz = 5;
    cfg.DebugPrint = false;
    cfg.SkipCompressing = false;
    cfg.DebugOptimProgress = true;

    ngc_unit_list = string(fullfile('ngc_test/unit', {dir('ngc_test/unit/*.ngc').name}));
    ngc_full_list = string(fullfile('ngc_test/full', {dir('ngc_test/full/*.ngc').name}));
    ngc_full_Montre_list = string(fullfile('ngc_test/full', {dir('ngc_test/full/*Montre*.ngc').name}));
        
    for k=1:numel(ngc_full_Montre_list)
        
        cfg.source = char(ngc_full_Montre_list(k));
        ctx = InitFeedoptPlan(cfg);
        ctx = FeedoptPlanRun(ctx);
        PlotCurvStructsBR(ctx, ctx.q_split.getall());
        title(ngc_full_Montre_list(k), 'Interpreter', 'none');
        
    end

    % PlotResampled(ctx, 1e-3)

end

