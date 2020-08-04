clear;
cfg = FeedoptDefaultConfig;


%% Test Helix 1/4 Circle matlab
c = ConstrHelixStructFromArcFeed(0,0,0,... % p0
                                 1,1,0,... % p1
                                 0,1,  ... % center
                                 1,    ... % rotation
                                 0);       % pitch
assert(c.theta == pi/2);

%% Test Helix 1/2 Circle matlab
c = ConstrHelixStructFromArcFeed(0,0,0,... % p0
                                 0,2,0,... % p1
                                 0,1,  ... % center
                                 1,    ... % rotation
                                 0);       % pitch
assert(c.theta == pi);

%% Test Helix Full Circle matlab
% TODO: This test fails right now, the full circle in a plane is ambiguous
c = ConstrHelixStructFromArcFeed(0,0,0,... % p0
                                 0,0,1,... % p1
                                 0,1,  ... % center
                                 1,    ... % rotation
                                 1);       % pitch
assert(c.theta == 2*pi);

%% Test Helix 1/4 Circle Pitch1 matlab
c = ConstrHelixStructFromArcFeed(0,0,0,... % p0
                                 1,1,1,... % p1
                                 0,1,  ... % center
                                 1,    ... % rotation
                                 4);       % pitch
ctx = InitFeedoptPlan(cfg);
assert_helix(ctx, c, pi/2);

%% Test Helix 1 + 1/4 Circle Pitch1 matlab
c = ConstrHelixStructFromArcFeed(0,0,0,... % p0
                                 1,1,5,... % p1
                                 0,1,  ... % center
                                 2,    ... % rotation
                                 4);       % pitch
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