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
A0 = zeros(3,1); A1 = A0;

gcode1 = ConstrLineStruct(trafo, HSC, Poff, Aoff, Uoff, ...
                               Doff, [-1,0,0]', [0,0,0]', A0, A1, U0, ...
                               U1, FeedRate, ZSpdMode.ZN);

P0      = zeros(3, 1);
P1      = [1,1,1 + (N-1)*4]';
Cprim   = [0,0,1]';
delta   = 0;
evec    = [0,0,0]';
theta   = (N-1)*pi+pi/2;
pitch   = 4;
FeedRate = 15;

info          = constrGcodeInfoStructType;
info.FeedRate = FeedRate;
info.zspdmode = ZSpdMode.ZN;
gcode   = constrHelixStruct( info, [ P0; A0 ], [ P1; A1 ], Cprim, delta, ...
                             evec, theta, pitch );

ctx = InitFeedoptPlan(cfg);
ctx.q_gcode.push(gcode1);
ctx.q_gcode.push(gcode2);
ctx.op = Fopt.Compress;
ctx = FeedoptPlanRun(ctx);

PlotResampled(ctx, 1e-4);