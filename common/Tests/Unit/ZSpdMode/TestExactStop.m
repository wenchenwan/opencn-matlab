% function TestZeroZeroRepeat
clear; clc; %close all;
cfg = FeedoptDefaultConfig;
global DebugActive
DebugActive = false;
cfg.NHorz = 3;
cfg.LSplit = 0.4;
cfg.source = 'ngc_test/unit/exact_stop.ngc';

ctx = InitFeedoptPlan(cfg);
ctx = FeedoptPlanRun(ctx);

PlotResampled(ctx, 1e-4);