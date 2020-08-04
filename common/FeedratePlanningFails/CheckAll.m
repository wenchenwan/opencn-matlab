%% Load
clear; clc;
load DemoPartNHorz3.mat
ctx = InitFeedoptPlanBR(cfg);

%% Plot
k0 = length(opt)+1;

PlotCurvStructs(ctx, split(k0:k0+cfg.NHorz-1));
