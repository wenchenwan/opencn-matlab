function [ params ] = paramsDefaultHelix( ~ ) %#codegen
% paramsDefaultHelix : Get default params for a Helix struct.

if( coder.target( 'MATLAB' ) && nargin > 0 )
    paramHelix = paramsDefaultCurv( StructTypeName.MEX );
else
    paramHelix = paramsDefaultCurv( );
end

if( coder.target( 'MATLAB' ) )
    params = { paramHelix{ 1 }, paramHelix{ 3 : end -2 } };
end

end