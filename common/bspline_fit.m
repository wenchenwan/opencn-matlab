function [CoeffX, CoeffY, CoeffZ] = bspline_fit(Bl, u, Points) %#codegen

if coder.target('rtw') || coder.target('mex')
    coder.updateBuildInfo('addSourceFiles','c_spline.c', '$(START_DIR)/src');
    coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    coder.cinclude('src/c_spline.h');
    CoeffX = zeros(1, Bl.n);
    CoeffY = zeros(1, Bl.n);
    CoeffZ = zeros(1, Bl.n);
    PointsX = Points(1, :);
    PointsY = Points(2, :);
    PointsZ = Points(3, :);
    coder.ceval('c_bspline_fit', coder.ref(Bl.handle), ...
        coder.ref(u), uint32(length(u)), ...
        coder.ref(PointsX), coder.wref(CoeffX), ...
        coder.ref(PointsY), coder.wref(CoeffY), ...
        coder.ref(PointsZ), coder.wref(CoeffZ));
else
    [CoeffX, CoeffY, CoeffZ] = bspline_fit_mex(Bl, u, Points);
end
end