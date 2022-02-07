% function TestZeroZero
clear; clc; %close all;
cfg = FeedoptDefaultConfig;
global DebugActive
DebugActive = true;
cfg.NHorz = 3;
cfg.LSplit = 0.2;
% cfg.NDiscr = 50;
% cfg.NBreak = 20;
% cfg.CutOff = 0.3;
N = 1;
FeedRate = 50;
gcode = ConstrHelixStruct(trafo, [0,0,0]', [1,1,1 + (N-1)*4]', A0, A1, ...
                          U0, U1, [0,0,1]', (N-1)*pi+pi/2, [0,0,0]', 4, ...
                          FeedRate, ZSpdMode.ZZ);
% gcode = ConstrLineStruct([0,0,0]', [1,0,0]', FeedRate, ZSpdMode.ZZ);

ctx = InitFeedoptPlan(cfg);
ctx.q_gcode.push(gcode);
ctx.op = Fopt.Check;
ctx = FeedoptPlanRun(ctx);

PlotResampled(ctx, 1e-4);