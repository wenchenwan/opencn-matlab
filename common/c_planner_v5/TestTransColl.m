    clear; close all; clc;

    cfg = FeedoptDefaultConfig;
    ctx = InitFeedoptPlan(cfg);
    
    P0 = [0 0 0]';
    P1 = [0 0 1]';
    P2 = [1e-8 0 2]';
    
    trafo = false; % TRAFO flag disable
    Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
    A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0;

    LineStruct1 = ConstrLineStruct(trafo, Poff, Aoff, Uoff, ...
                                   Doff, P0, P1, A0, A1, U0, U1, 100, ...
                                   ZSpdMode.NN);

    LineStruct2 = ConstrLineStruct(trafo, Poff, Aoff, Uoff, ...
                                    Doff, P0, P2, A0, A1, U0, U1, 100, ...
                                    ZSpdMode.NN);
    
    [~, r0D1] = EvalCurvStruct(ctx, LineStruct1, 1);
    [~, r1D1] = EvalCurvStruct(ctx, LineStruct2, 0);
    
    [value, real_angle_d] = collinear(r0D1, r1D1, ctx.cfg.CollTolDeg);
    
    [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status]  = ... 
        CalcTransition(ctx, LineStruct1, LineStruct2);
    
    PlotCurvStructsBR(ctx, [CurvStruct1_C CurvStruct_T CurvStruct2_C]);
    axis equal;