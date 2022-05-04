function pvec = PlotCurvStructsBR_2(ctx, CurvStructs)

N = length(CurvStructs);

pvec = [];

for i = 1:N
  
    if CurvStructs(i).Info.Type == CurveType.Line
        
        uvec = [0 1];
        P0P1 = EvalCurvStruct(ctx, CurvStructs(i), uvec);        
        pvec = [pvec P0P1];
        
    elseif CurvStructs(i).Info.Type == CurveType.Helix        
        uvec = linspace(0,1,100);
        P = EvalCurvStruct(ctx, CurvStructs(i), uvec);
        pvec = [pvec P];
        
        plot3(P(1, :), P(2, :), P(3, :), '-b');
        hold on;
    
    elseif CurvStructs(i).Info.Type == CurveType.TransP5
        
        uvec = linspace(0,1,100);
        P = EvalCurvStruct(ctx, CurvStructs(i), uvec);
        pvec = [pvec P];
                
    elseif CurvStructs(i).Info.Type == CurveType.Spline

        Spline=ctx.q_splines.get(CurvStructs(i).sp_index);
        sp = Spline.sp;
               
        uvec = linspace(0,1,1000);
        P = EvalCurvStruct(ctx, CurvStructs(i), uvec);
        pvec = [pvec P];

    end
    
end

plot3(pvec(1, :), pvec(2, :), pvec(3, :));

end