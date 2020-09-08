function L = LengthCurv(ctx, Curv, u0, u1)

if (Curv.Type == CurveType.Helix) || (Curv.Type == CurveType.Line)
    [~, r1D, ~, ~] = EvalCurvStruct(ctx, Curv, u0);
    L = MyNorm(r1D)*(u1-u0);
elseif Curv.Type == CurveType.Spline
    L = SplineLengthApprox(ctx, Curv, u0, u1);
elseif Curv.Type == CurveType.TransP5
    L = TransP5LengthApprox(Curv);
else
    c_assert(false, 'BAD CURVE TYPE IN LENGTH CURV');
    L = 0;
end

end
