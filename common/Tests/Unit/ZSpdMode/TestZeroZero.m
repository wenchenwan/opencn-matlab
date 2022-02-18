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

trafo = false; % TRAFO flag disable 
Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

P0      = zeros(3, 1);
P1      = ones(3, 1);
Cprim   = [0,0,1]';
delta   = 0;
evec    = [0,0,0]';
theta   = pi/2;
pitch   = 4;
FeedRate = 50;
mode    = ZSpdMode.NN;

gcode   = ConstrHelixStruct(trafo, Poff, Aoff, Uoff, Doff,...
                            P0, P1, A0, A1, U0, U1, Cprim, delta, evec, ...
                            theta, pitch, FeedRate, mode);

ctx = InitFeedoptPlan(cfg);
ctx.q_gcode.push(gcode);
ctx.op = Fopt.Check;
ctx = FeedoptPlanRun(ctx);

PlotResampled(ctx, 1e-4);