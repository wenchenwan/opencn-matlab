function TestHelixCut(ctx)
trafo = false; % TRAFO flag disable 
HSC = false;
Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

P0      = zeros(3, 1);
P1      = ones(3, 1);
Cprim   = [0,0,1]';
delta   = 0;
evec    = [0,0,0]';
theta   = pi/2;
pitch   = 4;
FeedRate = 15;

gcode   = ConstrHelixStruct(trafo, HSC, Poff, Aoff, Uoff, Doff,...
                            P0, P1, A0, A1, U0, U1, Cprim, delta, evec,...
                            theta, pitch, FeedRate, ZSpdMode.ZZ);

[L,R] = LengthHelix(ctx, gcode);
u = 0.7;
C1 = CutHelix(ctx, gcode, 0, L - u*L);
C2 = CutHelix(ctx, gcode, u*L, 0);
PlotCurvStructs(ctx, [C1,C2])
end