% function TestZeroZeroRepeat
clear; clc; %close all;
cfg = FeedoptDefaultConfig;
global DebugActive
DebugActive = false;
cfg.NHorz = 3;
cfg.LSplit = 0.4;
% cfg.CutOff = 0.3;
N = 1;
FeedRate = 50;
gcode1 = ConstrLineStruct([0,0,0]', [1,0,0]', FeedRate, ZSpdMode.ZZ);
gcode2 = ConstrLineStruct([1,0,0]', [1,1,0]', FeedRate, ZSpdMode.ZZ);
gcode3 = ConstrLineStruct([1,1,0]', [1,1,1]', FeedRate, ZSpdMode.ZZ);

ctx = InitFeedoptPlan(cfg);
ctx.q_gcode.push(gcode1);
ctx.q_gcode.push(gcode2);
ctx.q_gcode.push(gcode3);
ctx.op = Fopt.Check;
ctx = FeedoptPlanRun(ctx);

PlotResampled(ctx, 1e-4);