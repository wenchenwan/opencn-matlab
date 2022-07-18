clear; close all;

cfg = FeedoptDefaultConfig;
cfg.amax = [4,4,4];
% cfg.jmax = [2,8,8];
ctx = InitFeedoptPlan(cfg);

A0 = zeros(3,1); A1 = A0;
P0 = zeros(3, 1); P1 = [1, 1, 0]';
Cprim = [0,0,1]'; delta = 0; evec = [0,0,0]'; theta = 0; pitch = 1; 
mode = ZSpdMode.NN; FeedRate = 1;


info          = constrGcodeInfoStructType;
info.FeedRate = FeedRate;
info.zspdmode = mode;
Arc = constrHelixStruct( info, [ P0; A0 ], [ P1; A1 ], Cprim, delta, ...
                             evec, theta, pitch);

GetCurvMaxFeedrate(ctx, Arc)