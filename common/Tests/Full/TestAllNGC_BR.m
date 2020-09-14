function ctx = TestAllNGC_BR

    clear; clc;
    
    global DebugActive;
    DebugActive = false;
    
    global DebugActiveBR;
    DebugActiveBR = true;
    
    cfg = FeedoptDefaultConfig;
    cfg.NDiscr = 20;
    cfg.NBreak = 10;
    cfg.NHorz = 5;
    cfg.DebugPrint = false;
    cfg.SkipCompressing = false;
    cfg.DebugOptimProgress = true;
    cfg.logID = fopen('log.txt', 'w');

    ngc_unit_list = string(fullfile('ngc_test/unit', {dir('ngc_test/unit/*.ngc').name}));
    ngc_full_list = string(fullfile('ngc_test/full', {dir('ngc_test/full/*.ngc').name}));
    ngc_full_Montres_list = string(fullfile('ngc_test/full', {dir('ngc_test/full/020_Montre_V11.ngc').name}));
        
    for k=1:numel(ngc_full_Montres_list)
        
        cfg.source = char(ngc_full_Montres_list(k));
        ctx = InitFeedoptPlan(cfg);
        DebugLogBR(ctx, [ctx.cfg.source, '\n']);
        ctx = FeedoptPlanRun(ctx);
%         figure;
%         PlotCurvStructsBR_2(ctx, ctx.q_split.getall());
%         title(ngc_full_Montres_list(k), 'Interpreter', 'none');
        
    end

    % PlotResampled(ctx, 1e-3)

end

