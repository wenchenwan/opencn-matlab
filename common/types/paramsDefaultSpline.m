function [ params ] = paramsDefaultSpline( ~ ) %#codegen
% paramsDefaultSpline : Get default params for spline.

coeff       = zeros( 1, 1 ) ;
knots       = zeros( 1, 1 );

if( coder.target( 'MATLAB' ) && nargin > 0 )
    coeff    = coder.typeof( coeff, StructTypeName.dimCoeffs{ : } );
    knots    = coder.typeof( knots, StructTypeName.dimKnots{ : } ) ;
    BlStruct = constrBaseSplineType( StructTypeName.MEX );
else
    BlStruct = constrBaseSplineType;
end

if( coder.target( 'MATLAB' ) )
    params = { coeff, knots, BlStruct };
else
    params.coeff       = coeff;
    params.knots       = knots;
    params.BlStruct    = BlStruct;
end

end