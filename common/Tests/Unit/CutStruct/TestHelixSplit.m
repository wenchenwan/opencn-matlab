function [] = TestHelixSplit()
trafo = false;
A0 = zeros(3,1); A1 = A0; U0 = A0; U1 = A0;

gcode = ConstrHelixStruct(trafo, [0,0,0]', [1,1,1]', A0, A1, U0, U1, ...
                          [0,0,1]', pi/2, [0,0,0]', 4, 15, ZSpdMode.ZZ);
cfg = FeedoptDefaultConfig;
cfg.LSplit = LengthCurv(gcode)/3;
ctx = InitFeedoptPlan(cfg);

ctx = SplitCurvStruct(ctx, gcode, cfg.LSplit);
CurvStructs = ctx.q_split.getall();
PlotCurvStructs(ctx, CurvStructs);
end