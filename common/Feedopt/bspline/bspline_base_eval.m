function [ BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr ] = ...
         bspline_base_eval( Bl, xvec ) %#codegen
% bspline_base_eval : Eval Bspline bases for a given set of points.
% 
% Inputs :
% Bl            : BSpline bases
% xvec          : Given set of points 
%
% Outputs:
% BasisVal      : Basis of B-Spline
% BasisValD     : Basis of derivative of B-Spline
% BasisValDD    : Basis of 2nd derivative of B-Spline
% BasisValDDD   : Basis of 3rd derivative of B-Spline
% BasisIntegr   : Basis of Intregation of B-Spline
    if coder.target( "MATLAB" )
        [ BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr ] = ...
            bspline_base_eval_mex( 'bspline_base_eval', Bl, xvec );
    else
        samples     = int32( numel( xvec ) );
        BasisVal    = zeros( samples, Bl.ncoeff );
        BasisValD   = BasisVal;
        BasisValDD  = BasisVal;
        BasisValDDD = BasisVal;
        BasisIntegr = BasisVal( 1, : )';

        my_path = StructTypeName.WDIR + "/src";
        coder.updateBuildInfo( 'addIncludePaths',my_path );
        coder.updateBuildInfo( 'addSourceFiles','c_spline.c', my_path );
        coder.updateBuildInfo( 'addLinkFlags', LibInfo.gsl.lflags );
        coder.cinclude( 'c_spline.h' );
        coder.ceval( 'c_bspline_base_eval', coder.rref( Bl.handle ), samples, ...
            coder.rref( xvec ), coder.ref( BasisVal ), ...
            coder.ref( BasisValD ), coder.ref( BasisValDD ), ...
            coder.ref( BasisValDDD ), coder.ref( BasisIntegr ) );
    end
end
