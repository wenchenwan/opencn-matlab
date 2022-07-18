function [ C ] = constrBaseSplineType( ~ ) %#codegen
% constrBaseSplineType : Constructs a constrBaseSpline with default values.

if( nargin > 0 )
    [ params ] = paramsDefaultBaseSpline( StructTypeName.MEX );
else
    [ params ] = paramsDefaultBaseSpline;
end

if( coder.target( "MATLAB" ) )
    C = constrBaseSpline( params{ : } );
else
    C = constrBaseSpline( params.ncoeff, params.breakpoints, ...
        params.handle, params.order );
end

end