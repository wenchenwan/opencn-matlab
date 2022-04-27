function CurvStruct1 = CutCurvStruct(ctx, CurvStruct, d0, d1)
% We cut d0 [mm] in the beginning and d1 [mm] in the end of the segment
% We determine a new value of the parameter u_tilda

a = CurvStruct.a_param;
b = CurvStruct.b_param;

if CurvStruct.Type == CurveType.Spline
        
    u0_tilda = a*0+b;
    u1_tilda = a*1+b;
    
    if d0 ~= 0        
        u0_tilda  = SplineLengthFindU_up(ctx, CurvStruct, d0, u0_tilda);
    else
        u0_tilda = a*0+b;
    end
    
    if d1 ~= 0
        u1_tilda  = SplineLengthFindU_down(ctx, CurvStruct, d1, u1_tilda);
    else
        u1_tilda = a*1+b; 
    end

else
    
    % In case of helix and line, ||r'(u)||=const,
    % for 0 < u < 1
    
    % r1D0 and r1D1 are with respect to u
    [~, r1D0] = EvalCurvStruct(ctx, CurvStruct, 0);
    [~, r1D1] = EvalCurvStruct(ctx, CurvStruct, 1);

    % d0 = Integral_0_u0 ||r'(u)||du
    % d1 = Integral_u1_1 ||r'(u)||du
    u0 = d0/MyNorm(r1D0);
    u1 = 1 - d1/MyNorm(r1D1);
    
    % conversion to native curve parameter u_tilda
    u0_tilda = a*u0+b;
    u1_tilda = a*u1+b;
        
end

CurvStruct1 = CurvStruct;

CurvStruct1.a_param = u1_tilda - u0_tilda;
CurvStruct1.b_param = u0_tilda;

end