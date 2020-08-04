function ctx = SplitCurvStruct(ctx, CurvStrct)
% coder.varsize('CrvStructs', [1, 100], [0, 1]);
%
Type  = CurvStrct.Type;

if Type~=CurveType.TransP5 && CurvStrct.UseConstJerk == 0
    
    if Type==CurveType.Line || Type==CurveType.Helix
        ctx = SplitLineHelix(ctx, CurvStrct);
    else
        ctx = SplitSpline(ctx, CurvStrct);
    end
    
else
    ctx.q_split.push(CurvStrct);
end
