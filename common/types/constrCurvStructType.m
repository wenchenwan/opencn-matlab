function [ C ] = constrCurvStructType( ~ )%#codegen
% constrCurvStructType : Constructs a constrCurvStruct with default values.

if( nargin > 0 )
    [ params ] = paramsDefaultCurv( StructTypeName.MEX );
else
    [ params ] = paramsDefaultCurv;
end

if( coder.target( "MATLAB" ) )
    C = constrCurvStruct( params{ : } );
else
    C = constrCurvStruct( params.gcodeInfoStruct, params.spline, ...
        params.R0, params.R1, ...
        params.Cprim, params.delta, params.evec, params.theta, ...
        params.pitch, params.CoeffP5, params.Coeff );
end

end