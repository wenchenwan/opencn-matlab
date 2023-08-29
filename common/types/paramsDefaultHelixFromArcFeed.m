function [ params ] = paramsDefaultHelixFromArcFeed( ~ ) %#codegen
% paramsDefaultHelix : Get default params for a Helix struct.

if( coder.target( 'MATLAB' ) && nargin > 0 )
    paramHelix = paramsDefaultCurv( StructTypeName.MEX );
else
    paramHelix = paramsDefaultCurv( );
end

if( coder.target( 'MATLAB' ) )
    P0 = zeros( 3, 1 ); P1 = P0;
    A0 = P0; A1 = P0;
    params = { paramHelix{ 1 : 2 }, P0, P1, paramHelix{ 6 }, A0, A1, ...
               paramHelix{ 7 : 8 } };
end

end