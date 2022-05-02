function [ params ] = paramsDefaultHelixFromArcFeed( ~ ) %#codegen
% paramsDefaultHelix : Get default params for a Helix struct.

if( coder.target( 'MATLAB' ) && nargin > 0 )
    paramHelix = paramsDefaultCurv( StructTypeName.MEX );
else
    paramHelix = paramsDefaultCurv( );
end

if( coder.target( 'MATLAB' ) )
    R0 = zeros( 3, 1 ); R1 = R0;
    A0 = paramHelix{ 2 }; A1 = paramHelix{ 3 };
    params = { paramHelix{ 1 }, R0, R1, paramHelix{ 4 }, A0, A1, ...
               paramHelix{ 5:6 } };
end

end