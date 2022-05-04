% function TestZeroStart
clear; clc;
cfg = FeedoptDefaultConfig;
ctx = InitFeedoptPlan(cfg);
% cfg.NHorz = 5;
cfg.LSplit = 30;
N = 1;

A0      = zeros(3,1); A1 = A0; 
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
gcode1   = constrHelixStruct( info, [ P0; A0 ], [ P1; A1 ], Cprim, delta, ...
                             evec, theta, pitch );

gcode2 = ConstrLineStruct(trafo, HSC, Poff, Aoff, Uoff, ...
                               Doff, [1,1,1 + (N-1)*4]', ...
                               [1,2,1 + (N-1)*4]', A0, A1, U0, U1, 15, ...
                               ZSpdMode.ZN);

% [CurvStruct1, CurvStruct2] = CutZeroStart(ctx, gcode);
% 
% cfg.v_0 = CurvStruct1.v_0;
% cfg.at_0 = CurvStruct1.at_0;



ctx.q_smooth.push(CurvStruct2);
ctx.opt = Fopt.Split;
ctx.q_opt.push(CurvStruct1);
ctx = FeedoptPlanRun(ctx);

PlotResampled(ctx, 1e-4);

% PlotCurvStructs(ctx, [CurvStruct1, CurvStruct2])
% end
