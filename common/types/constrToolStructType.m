function [ C ] = constrToolStructType( ~ ) %#codegen
% constrToolStructType : Constructs a constrToolStructType with
% default values.

if( nargin > 0 )
    [ params ] = paramsDefaultTool( StructTypeName.MEX );
else
    [ params ] = paramsDefaultTool;
end

if( coder.target( "MATLAB" ) )
    C = constrToolStruct( params{ : } );
else
    C = constrToolStruct( params.toolno, params.pocketno, params.offset,...
        params.diameter, params.frontangle, params.backangle, ...
        params.orientation );
end

end