
clear; clc; close all;

cfg = FeedoptDefaultConfig();
cfg.source = 'ngc_test/anchor.ngc';

dt=100e-6; % initial resampling period [s]

ctx = InitFeedoptPlan(cfg);
ctx = FeedoptPlanRun(ctx);

PlotResampled(ctx, dt);
