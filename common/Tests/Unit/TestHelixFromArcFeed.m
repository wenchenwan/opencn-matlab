function TestHelixFromArcFeed
% N1660 Z-1.4
% N1665 G19 G2 Y23.1 Z-1.7 J-0.3 K0.
cfg = FeedoptDefaultConfig();
ctx = InitFeedoptPlan(cfg);
close all
phi0 = 0;
phi1 = pi/2;
rotation = -2;
A0 = zeros(3,1); A1 = A0;

p0x = cos(phi0); p0y = sin(phi0) + 1; p0z = 0;
p1x = cos(phi1); p1y = sin(phi1) + 1; p1z = -1;

cx = 0; cy = 1; cz = 0;

P0 = [ p0x; p0y; p0z ];
P1 = [ p1x; p1y; p1z ];
C  = [ cx; cy; cz ];

evec = [0,0,1]';

info          = constrGcodeInfoStructType;
info.FeedRate = 20;
info.zspdmode = ZSpdMode.ZZ;
Curv   = constrHelixStructFromArcFeed( info, P0, P1, C, A0, A1, rotation, evec );

PlotCurvStructs(ctx, Curv);
grid
axis equal

end