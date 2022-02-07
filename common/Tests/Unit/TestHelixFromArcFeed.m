function TestHelixFromArcFeed
% N1660 Z-1.4
% N1665 G19 G2 Y23.1 Z-1.7 J-0.3 K0.
cfg = FeedoptDefaultConfig();
ctx = InitFeedoptPlan(cfg);
close all
phi0 = 0;
phi1 = pi/2;
rotation = -2;

trafo = false;
A0 = zeros(3,1); A1 = A0; U0 = A0; U1 = A0;

Curv = ConstrHelixStructFromArcFeed(...
    trafo,...
    cos(phi0),sin(phi0) + 1,0,... % P0
    cos(phi1),sin(phi1) + 1,-1,... % P1
    0,1,0,...   % Center
    A0, A1, U0, U1,...
    rotation,...   % rotation
    [0,0,1]'); %evec

    PlotCurvStructs(ctx, Curv);
    grid
    axis equal
end