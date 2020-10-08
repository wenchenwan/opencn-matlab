function ctx = TestAllNGC_BR

    clear; clc; close all;
    
    global DebugConfig
    DebugConfig = 0;
    
    cfg = FeedoptDefaultConfig;
    cfg.NDiscr = 20;
    cfg.NBreak = 10;
    cfg.NHorz = 5;
    cfg.DebugPrint = false;
    cfg.SkipCompressing = false;
    cfg.DebugOptimProgress = true;
    
    ngc_unit_list = string(fullfile('ngc_test/unit', {dir('ngc_test/unit/*.ngc').name}));
    ngc_full_list = string(fullfile('ngc_test/full', {dir('ngc_test/full/*.ngc').name}));
    ngc_full_Montres_list = string(fullfile('ngc_test/full', {dir('ngc_test/full/021_Montre_V12.ngc').name}));
            
%     if coder.target('matlab')
%         diary ([cfg.LogFileName, '_', ...
%             datestr(now,'yyyy_mm_dd_HH_MM_SS'), ...
%             '.txt']);
%         diary on;
%     end
    
    EnableDebugLog(DebugCfg.OptimProgress);
    EnableDebugLog(DebugCfg.Transitions);
        
    for k=1:numel(ngc_full_Montres_list)
        
        cfg.source = char(ngc_full_Montres_list(k));
        DebugLog(DebugCfg.Transitions, [cfg.source, '\n']);
        ctx = InitFeedoptPlan(cfg);
        ctx = FeedoptPlanRun(ctx);
%         figure;
%         PlotCurvStructsBR_2(ctx, ctx.q_split.getall());
%         title(ngc_full_Montres_list(k), 'Interpreter', 'none');

%         PlotResampled(ctx, 1e-3);
        
    end
    
%     if coder.target('matlab')
%         diary off;
%     end

end

