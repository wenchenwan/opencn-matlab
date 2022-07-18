function [ BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr ] = ...
         bspline_base_eval(Bl, xvec) 
%#codegen
    if coder.target('rtw') || coder.target('mex')
        % n, bspline_n
        samples     = int32(numel(xvec));
        BasisVal    = zeros(samples, Bl.ncoeff);
        BasisValD   = BasisVal;
        BasisValDD  = BasisVal; 
        BasisValDDD = BasisVal;
        BasisIntegr = BasisVal(1, :)';
        
        coder.updateBuildInfo('addSourceFiles','c_spline.c', ...
                              '$(START_DIR)/src' );
        coder.updateBuildInfo( 'addLinkFlags', LibInfo.gsl.lflags );
        coder.cinclude('src/c_spline.h');
        coder.ceval( 'c_bspline_base_eval', coder.rref( Bl.handle ), samples, ...
                     coder.rref( xvec ), coder.ref( BasisVal ), ...
                     coder.ref( BasisValD ), coder.ref( BasisValDD ), ...
                     coder.ref( BasisValDDD ), coder.ref( BasisIntegr ) );
    else
        [ BasisVal, BasisValD, BasisValDD, BasisValDDD, BasisIntegr ] = ...
            bspline_base_eval_mex( 'bspline_base_eval', Bl, xvec );
    end
end
