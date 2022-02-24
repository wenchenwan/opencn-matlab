clear;
cfg = FeedoptDefaultConfig;

trafo = false; % TRAFO flag disable 
HSC = false; HSC_cmd  =  char(zeros(1,256));
Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

%% Test Helix 1/4 Circle matlab

p0x = 0; p0y = 0; p0z = 0;
p1x = 1; p1y = 1; p1z = 0;
cx = 0; cy = 1; cz = 0;
rotation = 1;
evec    = [0,0,0]';
pitch   = 0;

c = ConstrHelixStructFromArcFeed(trafo, HSC, HSC_cmd, ...
                      Poff, Aoff, Uoff, Doff, p0x, p0y, p0z, ...
                      p1x, p1y, p1z, cx, cy, cz, A0, A1, U0, U1, rotation,...
                      evec);

assert(c.theta == pi/2);

%% Test Helix 1/2 Circle matlab

p0x = 0; p0y = 0; p0z = 0;
p1x = 0; p1y = 2; p1z = 0;
cx = 0; cy = 1; cz = 0;
rotation = 1;
evec    = [0,0,0]';
pitch   = 0;

c = ConstrHelixStructFromArcFeed(trafo, HSC, HSC_cmd, ...
                      Poff, Aoff, Uoff, Doff, p0x, p0y, p0z, ...
                      p1x, p1y, p1z, cx, cy, cz, A0, A1, U0, U1, rotation,...
                      evec);

assert(c.theta == pi);

%% Test Helix Full Circle matlab
% TODO: This test fails right now, the full circle in a plane is ambiguous

p0x = 0; p0y = 0; p0z = 0;
p1x = 0; p1y = 0; p1z = 1;
cx = 0; cy = 1; cz = 0;
rotation = 1;
evec    = [0,0,0]';
pitch   = 1;

c = ConstrHelixStructFromArcFeed(trafo, HSC, HSC_cmd,...
                      Poff, Aoff, Uoff, Doff, p0x, p0y, p0z, ...
                      p1x, p1y, p1z, cx, cy, cz, A0, A1, U0, U1, rotation,...
                      evec);

assert(c.theta == 2*pi);

%% Test Helix 1/4 Circle Pitch1 matlab

p0x = 0; p0y = 0; p0z = 0;
p1x = 1; p1y = 1; p1z = 1;
cx = 0; cy = 1; cz = 0;
rotation = 2;
evec    = [0,0,0]';
pitch   = 4;

c = ConstrHelixStructFromArcFeed(trafo, HSC, HSC_cmd,...
                      Poff, Aoff, Uoff, Doff, p0x, p0y, p0z, ...
                      p1x, p1y, p1z, cx, cy, cz, A0, A1, U0, U1, rotation,...
                      evec);

ctx = InitFeedoptPlan(cfg);
assert_helix(ctx, c, pi/2);

%% Test Helix 1 + 1/4 Circle Pitch1 matlab

p0x = 0; p0y = 0; p0z = 0;
p1x = 1; p1y = 1; p1z = 5;
cx = 0; cy = 1; cz = 0;
rotation = 2;
evec    = [0,0,0]';
pitch   = 4;

c = ConstrHelixStructFromArcFeed(trafo, HSC, HSC_cmd, ...
                      Poff, Aoff, Uoff, Doff, p0x, p0y, p0z, ...
                      p1x, p1y, p1z, cx, cy, cz, A0, A1, U0, U1, rotation,...
                      evec);

ctx = InitFeedoptPlan(cfg);
assert_helix(ctx, c, 2*pi + pi/2);

%% Test Helix 1/4 Circle Pitch RS274
cfg.source = 'ngc_test/unit/helix_qcircle_pitch.ngc';
ctx = InitFeedoptPlan(cfg);
ctx = FeedoptPlanRun(ctx);
assert_helix(ctx, ctx.q_gcode.get(1), pi/2);

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

function assert_helix(ctx, c, theta)
assert(c.theta == theta);
assert(all(EvalCurvStruct(ctx, c, 0) - c.P0 < eps));
assert(all(EvalCurvStruct(ctx, c, 1) - c.P1 < eps));
end