function [ BasisVal, BasisValDD0, BasisValDD1 ] = bspline_eval_lee( Bl, nCoeff, u_vec )
%#codegen
    assert( all( u_vec >= 0, 'all' ), "ERROR : u_vec should be greater or equal to 0" );
    assert( all( u_vec <= 1, 'all' ), "ERROR : u_vec should be lower or equal to 1" );

    if ( coder.target('rtw') || coder.target('mex') )
        N = numel( u_vec );

        BasisVal    = zeros( N, nCoeff );
        BasisValDD0 = BasisVal( 1, : );
        BasisValDD1 = BasisValDD0;
        
        coder.updateBuildInfo('addSourceFiles','c_spline.c', '$(START_DIR)/src');
        coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
        coder.cinclude('src/c_spline.h');
        coder.ceval('c_bspline_base_eval_lee', coder.rref(Bl.handle), ...
            int32( nCoeff ), int32( N ), coder.rref( u_vec ), ...
            coder.wref( BasisVal ), coder.wref( BasisValDD0 ), ...
            coder.wref( BasisValDD1 ) );

    else
        [ BasisVal, BasisValDD0, BasisValDD1 ] = ...
        bspline_eval_lee_mex( 'bspline_eval_lee', Bl, nCoeff, u_vec );
    end
end
