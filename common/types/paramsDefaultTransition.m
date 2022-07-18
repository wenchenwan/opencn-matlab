function [ params ] = paramsDefaultTransition( ~ ) %#codegen
% paramsDefaultTransition : Get default params for a transition struct.

if( coder.target( 'MATLAB' ) && nargin > 0 )
    paramTrans = paramsDefaultCurv( StructTypeName.MEX );
else
    paramTrans = paramsDefaultCurv( );
end

if( coder.target( 'MATLAB' ) )
    params = { paramTrans{ 1 }, paramTrans{ 3 : 4 }, paramTrans{ end -1 } };
end

end