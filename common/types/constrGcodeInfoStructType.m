function [ C ] = constrGcodeInfoStructType( ~ ) %#codegen
% constrGcodeInfoStructType : Constructs a constrGcodeInfoStruct with
% default values.

if( nargin > 0 )
    [ params ] = paramsDefaultGCodeInfo( StructTypeName.MEX );
else
    [ params ] = paramsDefaultGCodeInfo;
end

if( coder.target( "MATLAB" ) )
    C = constrGcodeInfoStruct( params{ : } );
else
    C = constrGcodeInfoStruct( params.Type, params.zspdmode, params.TRAFO, ...
        params.HSC, params.G91, params.G91_1, params.FeedRate, ...
        params.SpindleSpeed, params.gcode_source_line );
end

end