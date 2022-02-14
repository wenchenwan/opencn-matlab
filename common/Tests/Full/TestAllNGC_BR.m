% This script implements the minimum configuration
% to be able to run geometric optimisation, feedrate planning,
% and resampling, with selected gcode file(s), with Matlab.

% In current implementation, theses files have to be placed in:
% agency/usr/matlab/common/ngc_test/utility_test_gcodes

% Be sure to have already generated all needed MEX files with
% generate_mex.m and
% mex_queue.m

% You can activate different debug configurations with EnableDebugLog().
% See DebugCfg enum definition to know all supported options, in DebugCfg.m.

% PlotResampled_BR() plot routine makes a 3D plot of the machined piece
% after all optimisations and resamling.
% This plot includes velocity information along all the path, with a color code.

% We need to invoke DestoyContext() function in the end of each for iteration,
% in order to prorerly free and deallocate memory space.
% Without this call, Matlab may crash when many gcodes have been treated.

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
