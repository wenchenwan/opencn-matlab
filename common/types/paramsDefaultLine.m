function [ params ] = paramsDefaultLine( ~ ) %#codegen
% paramsDefaultLine : Get default params for a Line struct.

if( coder.target( 'MATLAB' ) && nargin > 0 )
    paramLine = paramsDefaultCurv( StructTypeName.MEX );
else
    paramLine = paramsDefaultCurv( );
end

if( coder.target( 'MATLAB' ) )
    params = paramLine( 1 : 3 );
end

end