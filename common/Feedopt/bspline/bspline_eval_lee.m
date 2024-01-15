function [ BasisVal, BasisValDD0, BasisValDD1 ] = bspline_eval_lee( Bl, nCoeff, uVec )
%#codegen
% bspline_eval_lee  : Eval Bspline bases for a given set of u value. 
% 
% Inputs    :
% Bl            : BSpline bases
% nCoeff        : Number of Coefficient
% uVec          : U vector of points to evaluate
% 
% Outputs   :
% BasisVal      : Evaluation of the BSpline for a given set of points
% BasisValDD0   : Evaluation of the 2nd derivative of the BSpline a u = 0
% BasisValDD1   : Evaluation of the 2nd derivative of the BSpline a u = 1
%
    ocn_assert( all( uVec >= 0, 'all' ), ...
        "u_vec should be greater or equal to 0", mfilename );
    ocn_assert( all( uVec <= 1, 'all' ), ...
        "u_vec should be greater or equal to 1", mfilename );
    
    if ( coder.target( "MATLAB" ) )
        [ BasisVal, BasisValDD0, BasisValDD1 ] = ...
        bspline_eval_lee_mex( 'bspline_eval_lee', Bl, nCoeff, uVec );
    else
        N = numel( uVec );

        BasisVal    = zeros( N, nCoeff );
        BasisValDD0 = BasisVal( 1, : );
        BasisValDD1 = BasisValDD0;
        
        my_path = StructTypeName.WDIR + "/src";
        coder.updateBuildInfo('addIncludePaths',my_path);
        coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
        coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
        coder.cinclude( 'c_spline.h' );

        coder.ceval( 'c_bspline_base_eval_lee', coder.rref(Bl.handle), ...
            int32( nCoeff ), int32( N ), coder.rref( uVec ), ...
            coder.wref( BasisVal ), coder.wref( BasisValDD0 ), ...
            coder.wref( BasisValDD1 ) );
    end
end
