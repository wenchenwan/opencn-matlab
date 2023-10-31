function [ C ] = constrMsgStructType( ~ ) %#codegen
% constrMsgStructType : Constructs a constrMsgStruct with
% default values.

if( nargin > 0 )
    [ params ] = paramsDefaultMsg( StructTypeName.MEX );
else
    [ params ] = paramsDefaultMsg;
end

if( coder.target( "MATLAB" ) )
    C = constrMsgStruct( params{ : } );
else
    C = constrMsgStruct( params.msg );
end

end