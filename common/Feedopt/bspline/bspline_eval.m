function [ x, xd, xdd, xddd ] = bspline_eval( Bl, coeffs, x ) %#codegen
% void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
    X = zeros(1, 4);
    if( ~isreal(x) )
        disp("error here");
    end
    
    if coder.target('matlab')
        cond = numel(coeffs) == Bl.ncoeff;
        if( ~cond )
            disp( "error" );
        end
%         assert();
    end
    if coder.target('rtw') || coder.target('mex')
        if x < 0
            fprintf('ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n', x);
            x = 0;
        elseif x > 1
            fprintf('ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n', x);
            x = 1;
        end
        my_path = StructTypeName.WDIR + "/src";
        coder.updateBuildInfo('addIncludePaths',my_path);
        coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
        coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
        coder.cinclude('c_spline.h');

        coder.ceval('c_bspline_eval', coder.rref(Bl.handle), coder.rref(coeffs),...
                    x, coder.wref(X));
        x       = X(1);
        xd      = X(2);
        xdd     = X(3);
        xddd    = X(4);
    else
        [x, xd, xdd, xddd] = bspline_eval_mex('bspline_eval', Bl, coeffs, x);
    end
end
