function CurvStruct1 = CutCurvStruct(ctx, CurvStruct, d0, d1)
% We cut d0 [mm] in the beginning and d1 [mm] in the end of the segment
% We determine a new value of the parameter u_tilda (u_tilda_prim)

a = CurvStruct.a_param;
b = CurvStruct.b_param;

[~, r1D0] = EvalCurvStruct(ctx, CurvStruct, 0);
[~, r1D1] = EvalCurvStruct(ctx, CurvStruct, 1);

u_0 = d0/MyNorm(r1D0);
u_1 = 1 - d1/MyNorm(r1D1);

u_tilda_0 = a*u_0+b;
u_tilda_1 = a*u_1+b;

CurvStruct1 = CurvStruct;

CurvStruct1.a_param = u_tilda_1 - u_tilda_0;
CurvStruct1.b_param = u_tilda_0;

end
