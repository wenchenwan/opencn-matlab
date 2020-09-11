function pvec = PlotCurvStructsBR(ctx, CurvStructs)

N = length(CurvStructs);

pvec = [];

for i = 1:N
  
    if CurvStructs(i).Type == CurveType.Line
        
        uvec = [0 1];
        P0P1 = EvalCurvStruct(ctx, CurvStructs(i), uvec);        
        pvec = [pvec P0P1];
        
        plot3(P0P1(1, :), P0P1(2, :), P0P1(3, :), '-r');
        hold on;
        
    elseif CurvStructs(i).Type == CurveType.Helix        
        uvec = linspace(0,1,100);
        P = EvalCurvStruct(ctx, CurvStructs(i), uvec);
        pvec = [pvec P];
        
        plot3(P(1, :), P(2, :), P(3, :), '-b');
        hold on;
    
    elseif CurvStructs(i).Type == CurveType.TransP5
        
        uvec = linspace(0,1,100);
        P = EvalCurvStruct(ctx, CurvStructs(i), uvec);
        pvec = [pvec P];
        
        plot3(P(1, :), P(2, :), P(3, :), '-m');
        hold on;
                
    elseif CurvStructs(i).Type == CurveType.Spline

        Spline=ctx.q_splines.get(CurvStructs(i).sp_index);
        sp = Spline.sp;
               
        uvec = linspace(0,1,1000);
        P = EvalCurvStruct(ctx, CurvStructs(i), uvec);
        pvec = [pvec P];
        plot3(P(1, :), P(2, :), P(3, :), '-k');
        hold on;
        
        uvec = sp.knots(4:end-3);
        P = EvalCurvStruct(ctx, CurvStructs(i), uvec);
        plot3(P(1, :), P(2, :), P(3, :), 'xg');
        hold on;
              
    end
    
end

end