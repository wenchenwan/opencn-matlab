clear; close all;

cfg = FeedoptDefaultConfig;
cfg.amax = [4,4,4];
% cfg.jmax = [2,8,8];
ctx = InitFeedoptPlan(cfg);

Arc = ConstrHelixStruct([0,0,0]', [1,1,0]', [0,0,1]',...
    pi/2, 0, 1, ZSpdMode.NN);

GetCurvMaxFeedrate(ctx, Arc)