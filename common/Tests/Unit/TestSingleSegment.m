cfg = FeedoptDefaultConfig;
cfg.NDiscr = 10;
cfg.NBreak = 5;
ctx = InitFeedoptPlan(cfg);

trafo = false; 

A0 = zeros(3,1); A1 = A0; U0 = A0; U1 = A0;

C1 = ConstrLineStruct(trafo, [0,0,0]', [1,1,1]', A0, A1, U0, U1, 30, ZSpdMode.NN);
C2 = ConstrLineStruct(trafo, [1,1,1]', [2,2,2]', A0, A1, U0, U1, 2, ZSpdMode.NN);

CurvStructs = [C1, C2];

v_0 = 0.1;
v_1 = 0.1;
at_0 = 0;
at_1 = 0;

[Coeff, NCoeff, v_0, at_0, success, status] = FeedratePlanning_v4(CurvStructs, ctx.cfg.amax, ctx.cfg.jmax, v_0, at_0, v_1, at_1,...
    ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ctx.Bl, ctx.u_vec, 2);

v_1 = v_0;
at_1 = at_0;
v_0 = 0.1;
at_0 = 0;

[Coeff, NCoeff, v_0, at_0, success, status] = FeedratePlanning_v4(CurvStructs, ctx.cfg.amax, ctx.cfg.jmax, v_0, at_0, v_1, at_1,...
    ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr, ctx.Bl, ctx.u_vec, 1);
% 
% %% Study
% data_2 = load('two_segments');
% data_1 = load('one_segment');
% 
% A2 = full(data_2.A(1:70, 1:7));
% A1 = full(data_1.A);
% fprintf('|A2 - A1| = %f\n', norm(A2 - A1));
% 
% b2 = data_2.b(1:70);
% b1 = data_1.b;
% fprintf('|b2 - b1| = %f\n', norm(b2 - b1));
% 
% A2eq = data_2.Aeq(1:4, 1:7);
% A1eq = data_1.Aeq;
% fprintf('|A2eq - A1eq| = %f\n', norm(A2eq - A1eq));
% 
% b2eq = data_2.beq(1:4);
% b1eq = data_1.beq;
% fprintf('|b2eq - b1eq| = %f\n', norm(b2eq - b1eq));
% 
