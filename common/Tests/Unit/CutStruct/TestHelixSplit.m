function [] = TestHelixSplit()
A0 = zeros(3,1); A1 = A0;

P0      = zeros(3, 1);
P1      = ones(3, 1);
Cprim   = [0,0,1]';
delta   = 0;
evec    = [0,0,0]';
theta   = pi/2;
pitch   = 4;
FeedRate = 15;

info          = constrGcodeInfoStructType;
info.FeedRate = FeedRate;
info.zspdmode = ZSpdMode.ZZ;
gcode   = constrHelixStruct( info, [ P0; A0 ], [ P1; A1 ], Cprim, delta, ...
                             evec, theta, pitch);

cfg = FeedoptDefaultConfig;
cfg.LSplit = LengthCurv( gcode ) / 3;
ctx = InitFeedoptPlan( cfg );

ctx = SplitCurvStruct( ctx, gcode, cfg.LSplit );
CurvStructs = ctx.q_split.getall();
PlotCurvStructs( ctx, CurvStructs );
end