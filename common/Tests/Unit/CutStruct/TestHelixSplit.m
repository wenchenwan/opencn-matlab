function TestHelixSplit
gcode = ConstrHelixStruct([0,0,0]', [1,1,1]', [0,0,1]', pi/2, 4, 15, ZSpdMode.ZZ);
cfg = FeedoptDefaultConfig;
cfg.LSplit = LengthCurv(gcode)/3;
ctx = InitFeedoptPlan(cfg);

ctx = SplitCurvStruct(ctx, gcode, cfg.LSplit);
CurvStructs = ctx.q_split.getall();
PlotCurvStructs(ctx, CurvStructs);
end