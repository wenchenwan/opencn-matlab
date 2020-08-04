function pvec = PlotCurvStructsBR(ctx, CurvStructs, i_begin, i_end)

uvec = linspace(0,1,100);

P0 = EvalCurvStruct(ctx, CurvStructs(i_begin),0);
pvec = P0;

for i=i_begin:i_end
  
    if CurvStructs(i).Type == CurveType.Line
        
        P1 = EvalCurvStruct(ctx, CurvStructs(i), 1);        
        pvec = [pvec P1];
        
    elseif (CurvStructs(i).Type == CurveType.Helix) || ...
            (CurvStructs(i).Type == CurveType.TransP5)
        
        P = EvalCurvStruct(ctx, CurvStructs(i), uvec(2:end));
        pvec = [pvec P];
                
    elseif CurvStructs(i).Type == CurveType.Spline
        
        sp=ctx.q_splines.get(CurvStructs(i).sp_index);
        
        N=(length(sp.knots)-8+2-1)*10;
        uvec = linspace(sp.knots(1), sp.knots(end), N);
        
        P = EvalCurvStruct(ctx, CurvStructs(i), uvec(2:end));
        pvec = [pvec P];
        
    end
    
end

end