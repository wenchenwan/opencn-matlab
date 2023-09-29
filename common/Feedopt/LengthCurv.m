function L = LengthCurv( ctx, curv, u0, u1 )

if ( curv.Info.Type == CurveType.Helix ) || ( curv.Info.Type == CurveType.Line )
    [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
    L = MyNorm( r1D ) * ( u1 - u0 );
elseif ( curv.Info.Type == CurveType.Spline )
    a        = curv.a_param;
    b        = curv.b_param;
    u0_tilda = a * u0 + b;
    u1_tilda = a * u1 + b;
    spline   = ctx.q_spline.get( curv.sp_index );
    [ L ]    = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda );
elseif ( curv.Info.Type == CurveType.TransP5 )
    L = TransP5LengthApprox( curv );
else
    ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV", mfilename );
    L = 0;
end

end
