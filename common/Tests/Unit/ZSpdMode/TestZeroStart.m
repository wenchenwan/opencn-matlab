% function TestZeroStart
clear; clc;
cfg = FeedoptDefaultConfig;
ctx = InitFeedoptPlan(cfg);
% cfg.NHorz = 5;
cfg.LSplit = 30;
N = 1;
gcode1 = ConstrHelixStruct([0,0,0]', [1,1,1 + (N-1)*4]', [0,0,1]', (N-1)*pi+pi/2, 4, 15, ZSpdMode.ZN);
gcode2 = ConstrLineStruct([1,1,1 + (N-1)*4]', [1,2,1 + (N-1)*4]', 15, ZSpdMode.NN);
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
