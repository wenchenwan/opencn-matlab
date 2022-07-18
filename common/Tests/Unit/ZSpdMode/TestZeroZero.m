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

A0 = zeros(3,1); A1 = A0;

P0      = zeros(3, 1);
P1      = ones(3, 1);
Cprim   = [0,0,1]';
delta   = 0;
evec    = [0,0,0]';
theta   = pi/2;
pitch   = 4;
FeedRate = 50;
mode    = ZSpdMode.NN;

info          = constrGcodeInfoStructType;
info.FeedRate = FeedRate;
info.zspdmode = mode;
gcode   = constrHelixStruct( info, [ P0; A0 ], [ P1; A1 ], Cprim, delta, ...
                             evec, theta, pitch);

ctx = InitFeedoptPlan(cfg);
ctx.q_gcode.push(gcode);
ctx.op = Fopt.Check;
ctx = FeedoptPlanRun(ctx);

PlotResampled(ctx, 1e-4);