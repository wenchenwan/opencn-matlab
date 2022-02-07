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

trafo = false;
A0 = zeros(3,1); A1 = A0; U0 = A0; U1 = A0;

gcode1 = ConstrLineStruct(trafo, [0,0,0]', [1,0,0]', A0, A1, U0, U1, ...
                            FeedRate, ZSpdMode.ZZ);
gcode2 = ConstrLineStruct(trafo, [1,0,0]', [1,1,0]', A0, A1, U0, U1, ...
                            FeedRate, ZSpdMode.ZZ);
gcode3 = ConstrLineStruct(trafo, [1,1,0]', [1,1,1]', A0, A1, U0, U1, ...
                            FeedRate, ZSpdMode.ZZ);

ctx = InitFeedoptPlan(cfg);
ctx.q_gcode.push(gcode1);
ctx.q_gcode.push(gcode2);
ctx.q_gcode.push(gcode3);
ctx.op = Fopt.Check;
ctx = FeedoptPlanRun(ctx);

PlotResampled(ctx, 1e-4);