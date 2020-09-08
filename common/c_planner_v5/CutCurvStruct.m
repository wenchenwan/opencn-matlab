function CurvStruct1 = CutCurvStruct(ctx, CurvStruct, d0, d1)
% We cut d0 [mm] in the beginning and d1 [mm] in the end of the segment
% We determine a new value of the parameter u_tilda

a = CurvStruct.a_param;
b = CurvStruct.b_param;

if CurvStruct.Type == CurveType.Spline

    [L_tot, Integrand, u_mid_tilda, du_tilda]  = ...
        SplineLengthApprox(ctx, CurvStruct, 0, 1);

    if d0 ~= 0
        
        L = 0;
        k = 1;
        while (L < d0) && (k <= length(du_tilda))
            L = L + Integrand(k)*du_tilda(k);
            k = k + 1;
        end
        
        u0_tilda = u_mid_tilda(k);
    
    else
        
        u0_tilda = a*0+b;
        
    end
    
    if d1 ~= 0
                
        L = 0;
        k = 1;
        while (L < L_tot-d1) && (k <= length(du_tilda))
            L = L + Integrand(k)*du_tilda(k);
            k = k + 1;
        end
               
        u1_tilda = u_mid_tilda(k);
        
    else

        u1_tilda = a*1+b; 
        
    end

else
    
    [~, r1D0] = EvalCurvStruct(ctx, CurvStruct, 0);
    [~, r1D1] = EvalCurvStruct(ctx, CurvStruct, 1);

    u0 = d0/MyNorm(r1D0);
    u1 = 1 - d1/MyNorm(r1D1);
    
    u0_tilda = a*u0+b;
    u1_tilda = a*u1+b;
        
end

CurvStruct1 = CurvStruct;

CurvStruct1.a_param = u1_tilda - u0_tilda;
CurvStruct1.b_param = u0_tilda;

end
