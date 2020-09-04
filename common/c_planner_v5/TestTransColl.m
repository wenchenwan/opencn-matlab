    clear; close all; clc;

    cfg = FeedoptDefaultConfig;
    ctx = InitFeedoptPlan(cfg);
    
    P0 = [0 0 0]';
    P1 = [0 0 1]';
    P2 = [1e-8 0 2]';
    LineStruct1 = ConstrLineStruct(P0, P1, 100, ZSpdMode.NN);
    LineStruct2 = ConstrLineStruct(P1, P2, 100, ZSpdMode.NN);
    
    [~, r0D1] = EvalCurvStruct(ctx, LineStruct1, 1);
    [~, r1D1] = EvalCurvStruct(ctx, LineStruct2, 0);
    
    [value, real_angle_d] = collinear(r0D1, r1D1, ctx.cfg.CollTolDeg);
    
    [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status]  = ... 
        CalcTransition(ctx, LineStruct1, LineStruct2);
    
    PlotCurvStructsBR(ctx, [CurvStruct1_C CurvStruct_T CurvStruct2_C]);
    axis equal;