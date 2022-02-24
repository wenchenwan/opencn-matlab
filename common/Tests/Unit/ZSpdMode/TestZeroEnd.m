% function TestZeroEnd
clear; clc;
cfg = FeedoptDefaultConfig;
global DebugActive
DebugActive = true;
cfg.NHorz = 3;
cfg.LSplit = 30;
cfg.NBreak = 50;
cfg.NDiscr = 100;
% cfg.CutOff = 0.3;
N = 1;

trafo = false; % TRAFO flag disable 
HSC = false; HSC_cmd  =  char(zeros(1,256));
Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

gcode1 = ConstrLineStruct(trafo, HSC, HSC_cmd, Poff, Aoff, Uoff, ...
                               Doff, [-1,0,0]', [0,0,0]', A0, A1, U0, ...
                               U1, 15, ZSpdMode.NZ);

P0      = zeros(3, 1);
P1      = [1,1,1 + (N-1)*4]';
Cprim   = [0,0,1]';
delta   = 0;
evec    = [0,0,0]';
theta   = (N-1)*pi+pi/2;
pitch   = 4;
FeedRate = 15;

gcode2   = ConstrHelixStruct(trafo, HSC, HSC_cmd, Poff, Aoff, Uoff, Doff,...
                            P0, P1, A0, A1, U0, U1, Cprim, delta, evec, ...
                            theta, pitch, FeedRate, ZSpdMode.NZ);

% [CurvStruct1, CurvStruct2] = CutZeroEnd(gcode2, cfg);
% PlotCurvStructs([CurvStruct1, CurvStruct2])
% cfg.v_0 = CurvStruct1.v_0;
% cfg.at_0 = CurvStruct1.at_0;
ctx = InitFeedoptPlan(cfg);
% ctx.q_opt.push(CurvStruct2);
% PlotResampled(ctx, 1e-4);

ctx.q_gcode.push(gcode1);
ctx.q_gcode.push(gcode2);
ctx.op = Fopt.Smooth;
% ctx.q_opt.push(CurvStruct1);
ctx = FeedoptPlanRun(ctx);

PlotResampled(ctx, 1e-4);

% PlotCurvStructs([CurvStruct1, CurvStruct2])
% end