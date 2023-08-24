function [ C ] = constrAxesStructType( ~ ) %#codegen
% constrAxesStructType : Constructs a constrAxesStructType with
% default values.

if( nargin > 0 )
    [ params ] = paramsDefaultAxes( StructTypeName.MEX );
else
    [ params ] = paramsDefaultAxes;
end

if( coder.target( "MATLAB" ) )
    C = constrAxesStruct( params{ : } );
else
    C = constrAxesStruct( params.x, params.y, params.z, params.a, ...
        params.b, params.c, params.u, params.v, params.w );
end

end