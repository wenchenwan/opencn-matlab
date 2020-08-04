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
gcode1 = ConstrLineStruct([-1,0,0]', [0,0,0]', 15, ZSpdMode.NN);
gcode2 = ConstrHelixStruct([0,0,0]', [1,1,1 + (N-1)*4]', [0,0,1]', (N-1)*pi+pi/2, 4, 15, ZSpdMode.NZ);

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