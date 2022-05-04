function L = LengthCurv(ctx, Curv, u0, u1)

if ( Curv.Info.Type == CurveType.Helix ) || ( Curv.Info.Type == CurveType.Line )
    [~, r1D, ~, ~] = EvalCurvStruct( ctx, Curv, u0 );
    L = MyNorm( r1D ) * ( u1 - u0 );
elseif Curv.Info.Type == CurveType.Spline
    a = Curv.a_param;
    b = Curv.b_param;
    u0_tilda = a * u0 + b;
    u1_tilda = a * u1 + b;
    L = SplineLengthApproxGL_bounds(ctx, Curv, u0_tilda, u1_tilda);
elseif Curv.Info.Type == CurveType.TransP5
    L = TransP5LengthApprox(Curv);
else
    c_assert(false, 'BAD CURVE TYPE IN LENGTH CURV');
    L = 0;
end

end
