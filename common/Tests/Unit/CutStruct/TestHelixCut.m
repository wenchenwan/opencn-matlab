function TestHelixCut(ctx)
gcode = ConstrHelixStruct([0,0,0]', [1,1,1]', [0,0,1]', pi/2, 4, 15, ZSpdMode.ZZ);
[L,R] = LengthHelix(ctx, gcode);
u = 0.7;
C1 = CutHelix(ctx, gcode, 0, L - u*L);
C2 = CutHelix(ctx, gcode, u*L, 0);
PlotCurvStructs(ctx, [C1,C2])
end