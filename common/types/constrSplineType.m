function [ C ] = constrSplineType( ~ ) %#codegen
% constrSplineType : Constructs a constrSpline with default values.

if( nargin > 0 )
    [ params ] = paramsDefaultSpline( StructTypeName.MEX );
else
    [ params ] = paramsDefaultSpline;
end

if( coder.target( "MATLAB" ) )
    C = constrSpline( params{ : } );
else
    C = constrSpline( params.coeff, params.knots, params.BlStruct );
end

end