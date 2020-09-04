function CurvStruct1 = CutCurvStruct(ctx, CurvStruct, d0, d1)
% We cut d0 [mm] in the beginning and d1 [mm] in the end of the segment
% We determine a new value of the parameter u_tilda (u_tilda_prim)

a = CurvStruct.a_param;
b = CurvStruct.b_param;

[~, r1D0] = EvalCurvStruct(ctx, CurvStruct, 0);
[~, r1D1] = EvalCurvStruct(ctx, CurvStruct, 1);

u0 = d0/MyNorm(r1D0);
u1 = 1 - d1/MyNorm(r1D1);

if CurvStruct.Type == CurveType.Spline
    
    SplineStruct =ctx.q_splines.get(CurvStruct.sp_index);
    sp1D      = fnder(SplineStruct.sp); % derivative
    
    if d0 ~= 0
        
        u_vec = linspace(0, SplineStruct.sp.knots(5), 100);
        u_mid     = 0.5*(u_vec(1:end-1)+u_vec(2:end)); % midpoint values
        du        = diff(u_vec);
        r1D = spval(sp1D, u_mid);
        L_cum = 0;
        k = 1;
        while (L_cum < d0) && (k <= length(u_mid))
            L_cum = L_cum + MyNorm(r1D(:,k))*du(k);
            k = k + 1;
        end
        
        u0 = u_vec(k); 
        
    end
    
    if d1 ~= 0
                
        u_vec = linspace(SplineStruct.sp.knots(end-4), 1, 100);
        u_mid     = 0.5*(u_vec(1:end-1)+u_vec(2:end)); % midpoint values
        du        = diff(u_vec);
        r1D = spval(sp1D, u_mid);
        L_cum = 0;
        k = length(u_mid);
        while L_cum < d1 && k > 0
            L_cum = L_cum + MyNorm(r1D(:,k))*du(k);
            k = k - 1;
        end
               
        u1 = u_vec(k);        
    end
        
end

u_tilda_0 = a*u0+b;
u_tilda_1 = a*u1+b;

CurvStruct1 = CurvStruct;

CurvStruct1.a_param = u_tilda_1 - u_tilda_0;
CurvStruct1.b_param = u_tilda_0;

end
