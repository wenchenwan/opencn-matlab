function TestHelixCut(ctx)
trafo = false;
A0 = zeros(3,1); A1 = A0; U0 = A0; U1 = A0;

gcode = ConstrHelixStruct(trafo, [0,0,0]', [1,1,1]', A0, A1, U0, U1, ...
                            [0,0,1]', pi/2, [0,0,0]', 4, 15, ZSpdMode.ZZ);
[L,R] = LengthHelix(ctx, gcode);
u = 0.7;
C1 = CutHelix(ctx, gcode, 0, L - u*L);
C2 = CutHelix(ctx, gcode, u*L, 0);
PlotCurvStructs(ctx, [C1,C2])
end