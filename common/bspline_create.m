function Bl = bspline_create(degree, breakpoints) %#codegen
if coder.target('rtw') || coder.target('mex')
    nbreak = length(breakpoints);
    ncoeff = nbreak + degree - 2;
    h = uint64(0);

    coder.updateBuildInfo('addSourceFiles','c_spline.c', '$(START_DIR)/src');
    coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    coder.cinclude('src/c_spline.h');
    coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), degree, breakpoints, int32(nbreak) );
    Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
else
    Bl = bspline_create_mex( int32(degree), breakpoints );
end
end
