function ctx = SplitCurvStruct(ctx, CurvStrct)
% coder.varsize('CrvStructs', [1, 100], [0, 1]);
%
Type  = CurvStrct.Info.Type;

if Type~=CurveType.TransP5 && CurvStrct.UseConstJerk == 0
    
    if Type==CurveType.Line || Type==CurveType.Helix
        ctx = splitLineHelix(ctx, CurvStrct);
    else
        ctx = splitSpline(ctx, CurvStrct);
    end
    
else
    ctx.q_split.push(CurvStrct);
end
