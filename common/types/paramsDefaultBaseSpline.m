function [ params ] = paramsDefaultBaseSpline( ~ ) %#codegen
% paramsDefaultBaseSpline : Get default params for base spline.
ncoeff      = int32( 0 ) ;
breakpoints = zeros( 1, 1 );
handle      = uint64( 0 );
order       = int32( 0 );

if( coder.target( 'MATLAB' ) && nargin > 0 )
    breakpoints = coder.typeof( breakpoints, StructTypeName.dimNBreak{ : } );
end

if( coder.target( 'MATLAB' ) )
    params = { ncoeff, breakpoints, handle, order };
else
    params.ncoeff      = ncoeff ;
    params.breakpoints = breakpoints;
    params.handle      = handle;
    params.order       = order;
end

end