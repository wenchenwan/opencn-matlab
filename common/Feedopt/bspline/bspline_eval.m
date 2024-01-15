function [ x, xd, xdd, xddd ] = bspline_eval( Bl, coeffs, x ) %#codegen
% bspline_eval  : Eval Bspline bases for a given set of points and
% coefficients
% 
% Inputs :
% Bl            : BSpline bases
% coeffs        : Coefficients used during the evaluation
% x             : Given set of points 
%
% Outputs:
% x             : Evaluated points 
% xd            : Evaluated points derivative
% xdd           : Evaluated points 2nd derivative
% xddd          : Evaluated points 3rd derivative
    enablePrint = true;
    X = zeros(1, 4);
    ocn_assert( isreal( x ), "x should be real", mfilename );
    
    if coder.target( "MATLAB" )
        [ x, xd, xdd, xddd ] = bspline_eval_mex( 'bspline_eval', Bl, ...
            coeffs, x );
    else
        if ( x < 0 )
            ocn_print( enablePrint, ...
                "ERROR: C_BSPLINE_EVAL: X < 0 (" + x + ")", mfilename );
            x = 0;
        elseif ( x > 1 )
            ocn_print( enablePrint, ...
                "ERROR: C_BSPLINE_EVAL: X > 1 (" + x + ")", mfilename );
            x = 1;
        end
        my_path = StructTypeName.WDIR + "/src";
        coder.updateBuildInfo('addIncludePaths',my_path);
        coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
        coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
        coder.cinclude('c_spline.h');

        coder.ceval( 'c_bspline_eval', coder.rref(Bl.handle), ...
            coder.rref(coeffs), x, coder.wref(X));
        x       = X(1);
        xd      = X(2);
        xdd     = X(3);
        xddd    = X(4);
    end
end
