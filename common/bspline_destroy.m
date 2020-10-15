function bspline_destroy(Bl) %#codegen
    if coder.target('rtw') || coder.target('mex')
        coder.updateBuildInfo('addSourceFiles','c_spline.c', '$(START_DIR)/src');
        coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
        coder.cinclude('src/c_spline.h');
        if Bl.handle > 0
            coder.ceval('c_bspline_destroy', coder.rref(Bl.handle));
        end
    else
        bspline_destroy_mex('bspline_destroy', Bl);
    end
end