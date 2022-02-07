function TestAll
close all
load Fail1

cfg = FeedoptDefaultConfig();
ctx = InitFeedoptPlanBR(cfg);

% [~, r0D1] = EvalCurvStruct(ctx, CurvStruct1, 1);
% [~, r1D1] = EvalCurvStruct(ctx, CurvStruct2, 0);

% CurvStruct2.P1(3) = -0.5;
% CutOff = 0.2;
% PlotCurvStructs(ctx, [CurvStruct1, CurvStruct2])
% [CurvStruct1_C, CurvStruct_T, CurvStruct2_C] = CalcTransition(ctx, CurvStruct1, CurvStruct2, CutOff);
% PlotCurvStructs(ctx, [CurvStruct1, CurvStruct2], [CurvStruct1_C, CurvStruct_T, CurvStruct2_C]);
% TestRightAngle(ctx)
% TestColinear(ctx)
% TestParPlane(ctx)

% TestOffAngle(ctx)
% TestColinear(ctx)

end

function TestOffAngle(ctx)
L = 1;
CutOff = 0.1;
Offset = 0.8;
trafo = false; % TRAFO flag disable 
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 
CurvStruct1 = ConstrLineStruct(trafo, [0,0,0]', [L,0,0]', A0, A1, U0, U1, 1, ZSpdMode.NN);
CurvStruct2 = ConstrLineStruct(trafo, [L+Offset,0,0]', [3*L + Offset,L,0]', A0, A1, U0, U1, 1, ZSpdMode.NN);
PlotCurvStructs(ctx, [CurvStruct1, CurvStruct2])
[CurvStruct1_C, CurvStruct_T, CurvStruct2_C] = CalcTransition(ctx, CurvStruct1, CurvStruct2, CutOff);
close all
PlotCurvStructs(ctx, [CurvStruct1_C, CurvStruct_T, CurvStruct2_C]);
end

function TestRightAngle(ctx)
CutOff = 0.1;

trafo = false; % TRAFO flag disable 
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

for L = [10, 5, 1, 3*CutOff, 2*CutOff, CutOff]
    CurvStruct1 = ConstrLineStruct(trafo, [0,0,0]', [L,0,0]', A0, A1, U0, U1, 1, ZSpdMode.NN);
    CurvStruct2 = ConstrLineStruct(trafo, [L,0,0]', [L,L,0]', A0, A1, U0, U1, 1, ZSpdMode.NN);
    CalcTransition(ctx, CurvStruct1, CurvStruct2, CutOff);
end
end

function TestColinear(ctx)
CutOff = 0.1; L = 1;

trafo = false; % TRAFO flag disable 
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

for A = 1e-7
% for A = [90, 45, 20, 10, 5, 1, 0.1, 0.01, 0.001, 1e-6]
    a = deg2rad(A);
    CurvStruct1 = ConstrLineStruct(trafo, [0,0,0]', [L,0,0]', A0, A1, U0, U1, 1, ZSpdMode.NN);
    CurvStruct2 = ConstrLineStruct(trafo, [L,0,0]', [L + L*cos(a),L*sin(a),0]', A0, A1, U0, U1, 1, ZSpdMode.NN);
    CalcTransition(ctx, CurvStruct1, CurvStruct2, CutOff);
end
end

function TestParPlane(ctx)
CutOff = 0.1; L = 1;

trafo = false; % TRAFO flag disable 
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

CurvStruct1 = ConstrLineStruct(trafo, [0,0,0]', [L,0,0]', A0, A1, U0, U1, 1, ZSpdMode.NN);
CurvStruct2 = ConstrLineStruct(trafo, [L,0,0.2]', [L,L,0.2]', A0, A1, U0, U1, 1, ZSpdMode.NN);
CalcTransition(ctx, CurvStruct1, CurvStruct2, CutOff);
end
