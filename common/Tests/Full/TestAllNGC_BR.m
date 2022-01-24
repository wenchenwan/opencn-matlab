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

ngc_list = string(fullfile('ngc_test/utility_test_gcodes', {dir('ngc_test/utility_test_gcodes/*.ngc').name}));

EnableDebugLog(DebugCfg.Transitions);
EnableDebugLog(DebugCfg.Error);
EnableDebugLog(DebugCfg.Warning);
EnableDebugLog(DebugCfg.OptimProgress);
EnableDebugLog(DebugCfg.Plots);

for k=1:numel(ngc_list)

    cfg.source = char(ngc_list(k));
    DebugLog(DebugCfg.Transitions, [cfg.source, '\n']);
    ctx = InitFeedoptPlan(cfg);
    ctx = FeedoptPlanRun(ctx);
    PlotResampled_BR(ctx, 10, 1e-3);
    DestroyContext(ctx);

end
