function bspline_destroy(Bl) %#codegen
    if coder.target('rtw') || coder.target('mex')
        
        my_path = StructTypeName.WDIR + "/src";
        coder.updateBuildInfo('addIncludePaths',my_path);
        coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
        coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
        coder.cinclude('c_spline.h');
        if Bl.handle > 0
            coder.ceval('c_bspline_destroy', coder.rref(Bl.handle));
        end
    else
        bspline_destroy_mex('bspline_destroy', Bl);
    end
end