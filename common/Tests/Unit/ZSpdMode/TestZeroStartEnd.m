% function TestZeroStartEnd
clear; clc; %close all;
cfg = FeedoptDefaultConfig;
global DebugActive
DebugActive = true;
cfg.NHorz = 3;
cfg.LSplit = 30;
% cfg.CutOff = 0.3;
N = 1;
FeedRate = 50;
gcode1 = ConstrLineStruct([-1,0,0]', [0,0,0]', FeedRate, ZSpdMode.ZN);
gcode2 = ConstrHelixStruct([0,0,0]', [1,1,1 + (N-1)*4]', [0,0,1]', (N-1)*pi+pi/2, 4, FeedRate, ZSpdMode.NZ);

ctx = InitFeedoptPlan(cfg);
ctx.q_gcode.push(gcode1);
ctx.q_gcode.push(gcode2);
ctx.op = Fopt.Compress;
ctx = FeedoptPlanRun(ctx);

PlotResampled(ctx, 1e-4);