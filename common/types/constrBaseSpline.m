function [ BaseSplineStrct ] = constrBaseSpline( ncoeff, breakpoints, ...
    handle, order ) %#codegen
% Construct a struct base spline.
% 
% Inputs :
% ncoeff       : Number of coefficients
% breakpoints  : Number of breakpoints
% handle       : Pointer on the structure
% degree       : order of the spline
% 
% Outputs :
% CStrct    : The resulting structure

BaseSplineStrct = struct( 'ncoeff', ncoeff,...
        'breakpoints', breakpoints,...
        'handle', handle,...
        'order', order );

if ~coder.target( 'MATLAB' )
    coder.varsize( 'BaseSplineStrct.breakpoints', StructTypeName.dimNBreak{ : } );
    coder.cstructname( BaseSplineStrct, StructTypeName.BaseSpline );
end

end