function [r0D, r1D, r2D, r3D] = EvalBSplineNoCtx(CurvSpline, uvec)
coder.inline('never')
if coder.target('rtw') || coder.target('mex')
    coder.cinclude('common/tracy/Tracy.hpp');
    coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalBSpline"'));
end

    Spline=CurvSpline;
    sp = Spline.sp;
    Bl = sp.Bl;
    [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
    [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
    [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
    
    r0D = [r0Dx; r0Dy; r0Dz];
    r1D = [r1Dx; r1Dy; r1Dz];
    r2D = [r2Dx; r2Dy; r2Dz];
    r3D = [r3Dx; r3Dy; r3Dz];


end
