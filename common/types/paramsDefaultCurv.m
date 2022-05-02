function [ params ] = paramsDefaultCurv( ~ ) %#codegen
% paramsDefaultCurv : Get default params for curv struct.
R0      = zeros( 1, 1 );
R1      = zeros( 1, 1 );
Cprim   = zeros( 3, 1 );
delta   = 0.0;
evec    = zeros( 3, 1 );
theta   = 0.0;
pitch   = 0.0;
CoeffP5 = zeros( 1, 6 );
Coeff   = zeros( 1, 1 );

if( coder.target( 'MATLAB' ) && nargin > 0 )
    R0 = coder.typeof( R0, StructTypeName.dimR{ : } );
    R1 = coder.typeof( R1, StructTypeName.dimR{ : } );
    CoeffP5 = coder.typeof( CoeffP5, StructTypeName.dimCoeffP5{ : } ) ;
    Coeff  = coder.typeof( Coeff,  StructTypeName.dimCoeffOpt{ : } ) ;
    gcodeInfoStruct = constrGcodeInfoStructType( StructTypeName.MEX );
else
    gcodeInfoStruct = constrGcodeInfoStructType();
end

if( coder.target( 'MATLAB' ) )
    params = { gcodeInfoStruct, R0, R1, Cprim, delta, evec, theta, pitch, ...
               CoeffP5, Coeff };
else
    params.gcodeInfoStruct = gcodeInfoStruct;
    params.R0       = R0;
    params.R1       = R1;
    params.Cprim    = Cprim;
    params.delta    = delta;
    params.evec     = evec;
    params.theta    = theta;
    params.pitch    = pitch;
    params.CoeffP5  = CoeffP5;
    params.Coeff    = Coeff;
end

end