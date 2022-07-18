clear;
cfg = FeedoptDefaultConfig;

A0 = zeros(3,1); A1 = A0;

TOL_DEFAULT = 1E-6;

ctx = initFeedoptPlan(cfg);

%% Test Helix 1/4 Circle matlab

p0x = 0; p0y = 0; p0z = 0;
p1x = 1; p1y = 1; p1z = 0;
cx = 0; cy = 1; cz = 0;
rotation = 1;
evec    = [0,0,1]';
pitch   = 0;
P0 = [ p0x; p0y; p0z ];
P1 = [ p1x; p1y; p1z ];
C  = [ cx; cy; cz ];

info          = constrGcodeInfoStructType;
info.FeedRate = 20;
info.zspdmode = ZSpdMode.ZZ;
c   = constrHelixStructFromArcFeed( info, P0, P1, C, A0, A1, rotation, evec );

assert_helix( ctx, c, pi/2, TOL_DEFAULT );

%% Test Helix 1/2 Circle matlab

p0x = 0; p0y = 0; p0z = 0;
p1x = 0; p1y = 2; p1z = 0;
cx = 0; cy = 1; cz = 0;
rotation = 1;
evec    = [0,0,1]';
pitch   = 0;
P0 = [ p0x; p0y; p0z ];
P1 = [ p1x; p1y; p1z ];
C  = [ cx; cy; cz ];

info          = constrGcodeInfoStructType;
info.FeedRate = 20;
info.zspdmode = ZSpdMode.ZZ;
c   = constrHelixStructFromArcFeed( info, P0, P1, C, A0, A1, rotation, evec );

assert_helix( ctx, c, pi, TOL_DEFAULT );

%% Test Helix Full Circle matlab
% TODO: This test fails right now, the full circle in a plane is ambiguous

p0x = 0; p0y = 0; p0z = 0;
p1x = 0; p1y = 0; p1z = 1;
cx = 0; cy = 1; cz = 0;
rotation = 1;
evec    = [0,0,1]';
pitch   = 1;

P0 = [ p0x; p0y; p0z ];
P1 = [ p1x; p1y; p1z ];
C  = [ cx; cy; cz ];

info          = constrGcodeInfoStructType;
info.FeedRate = 20;
info.zspdmode = ZSpdMode.ZZ;
c   = constrHelixStructFromArcFeed( info, P0, P1, C, A0, A1, rotation, evec );
assert_helix( ctx, c, 2*pi, TOL_DEFAULT );

%% Test Helix 1/4 Circle Pitch1 matlab

p0x = 0; p0y = 0; p0z = 0;
p1x = 1; p1y = 1; p1z = 1;
cx = 0; cy = 1; cz = 0;
rotation = 2;
evec    = [0,0,1]';
pitch   = 4;

P0 = [ p0x; p0y; p0z ];
P1 = [ p1x; p1y; p1z ];
C  = [ cx; cy; cz ];

info          = constrGcodeInfoStructType;
info.FeedRate = 20;
info.zspdmode = ZSpdMode.ZZ;
c   = constrHelixStructFromArcFeed( info, P0, P1, C, A0, A1, rotation, evec );

assert_helix( ctx, c, pi/2, TOL_DEFAULT );

%% Test Helix 1 + 1/4 Circle Pitch1 matlab

p0x = 0; p0y = 0; p0z = 0;
p1x = 1; p1y = 1; p1z = 5;
cx = 0; cy = 1; cz = 0;
rotation = 2;
evec    = [0,0,0]';
pitch   = 4;

P0 = [ p0x; p0y; p0z ];
P1 = [ p1x; p1y; p1z ];
C  = [ cx; cy; cz ];

info          = constrGcodeInfoStructType;
info.FeedRate = 20;
info.zspdmode = ZSpdMode.ZZ;
c   = constrHelixStructFromArcFeed( info, P0, P1, C, A0, A1, rotation, evec );

assert_helix(ctx, c, 2*pi + pi/2, TOL_DEFAULT);

%% Test Helix 1/4 Circle Pitch RS274
cfg.source = 'ngc_test/unit/helix_qcircle_pitch.ngc';
ctx = InitFeedoptPlan(cfg);
ctx = FeedoptPlanRun(ctx);
assert_helix(ctx, ctx.q_gcode.get(1), pi/2, TOL_DEFAULT );

%% Test Anchor
cfg = FeedoptDefaultConfig;
cfg.source = 'ngc_test/anchor.ngc';
ctx = InitFeedoptPlan(cfg);
ctx = FeedoptPlanRun(ctx);

%% Test Demo Piece
cfg = FeedoptDefaultConfig;
cfg.NHorz = 5; % Fails with NHorz = 3
cfg.source = 'ngc_test/PieceDemoLinuxCNC_HV_V05.ngc';
ctx = InitFeedoptPlan(cfg);
ctx = FeedoptPlanRun(ctx);

%% Test Helix with Pitch
cfg.source = 'ngc_test/unit/helix_pitch.ngc';
cfg.LSplit = 200;
ctx = InitFeedoptPlan(cfg);
ctx = FeedoptPlanRun(ctx);
gcode = ctx.q_gcode.getall;
h = gcode(3);
dz = h.P1(3) - h.P0(3);

function assert_helix( ctx, c, theta, tol )
assert( abs( c.theta - theta ) < tol );
assert(all( EvalCurvStruct(ctx, c, 0) - c.R0( ctx.cfg.maskTot ) < tol ));
assert(all( EvalCurvStruct(ctx, c, 1) - c.R1( ctx.cfg.maskTot )  < tol ));
end