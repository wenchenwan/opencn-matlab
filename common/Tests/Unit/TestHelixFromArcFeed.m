function TestHelixFromArcFeed
% N1660 Z-1.4
% N1665 G19 G2 Y23.1 Z-1.7 J-0.3 K0.
cfg = FeedoptDefaultConfig();
ctx = InitFeedoptPlan(cfg);
close all
phi0 = 0;
phi1 = pi/2;
rotation = -2;

trafo = false; % TRAFO flag disable 
HSC = false;
Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

p0x = cos(phi0); p0y = sin(phi0) + 1; p0z = 0;
p1x = cos(phi1); p1y = sin(phi1) + 1; p1z = -1;
cx = 0; cy = 1; cz = 0;
evec = [0,0,1]';

Curv = ConstrHelixStructFromArcFeed(trafo, HSC, ...
                                   Poff, Aoff, Uoff, Doff, p0x, p0y, p0z,...
                                   p1x, p1y, p1z, cx, cy, cz, A0, A1, U0,...
                                   U1, rotation, evec);

PlotCurvStructs(ctx, Curv);
grid
axis equal

end