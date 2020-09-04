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
        uvec = linspace(0,1,1000);
        P = EvalCurvStruct(ctx, CurvStructs(i), uvec);
        pvec = [pvec P];
        
        plot3(P(1, :), P(2, :), P(3, :), '-b');
        hold on;
    
    elseif CurvStructs(i).Type == CurveType.TransP5
        
        uvec = linspace(0,1,10);
        P = EvalCurvStruct(ctx, CurvStructs(i), uvec);
        pvec = [pvec P];
        
        plot3(P(1, :), P(2, :), P(3, :), '-m');
        hold on;
                
    elseif CurvStructs(i).Type == CurveType.Spline
        
        a=CurvStructs(i).a_param;
        b=CurvStructs(i).b_param;
        u0 = a*0+b;
        u1 = a*1+b;
        
        Curv=CurvStructs(i);
        
        Spline=ctx.q_splines.get(CurvStructs(i).sp_index);
        sp = Spline.sp;
        
        Knots = sp.knots;

%         Idx1      = find(Knots > u0, 1);
%         Idx2      = find(Knots < u1, 1, 'last');
% 
%         uvec     = [u0, Knots(Idx1(1):Idx2(1)), u1];
%         [P, ~, ~, ~] = EvalBSpline(ctx, CurvStructs(i), uvec);
%         pvec = [pvec P];
%         
%         plot3(P(1, :), P(2, :), P(3, :), 'xk');
        hold on;
        
        uvec     = linspace(u0, u1, 10000);
        [P, ~, ~, ~] = EvalBSpline(ctx, CurvStructs(i), uvec);
        pvec = [pvec P];
        plot3(P(1, :), P(2, :), P(3, :), '-k', 'LineWidth', 2);
        hold on;
        
%         uvec = Knots;
%         [P, ~, ~, ~] = EvalBSpline(ctx, CurvStructs(i), uvec);
%         scatter3(P(1, :), P(2, :), P(3, :), 'xg', 'LineWidth', 3);
%         hold on;
        
        
    end
    
end

end