function [ params ] = paramsDefaultTool( ~ ) %#codegen
% paramsDefaultTool : Get default params for the tool.

toolno        = int32(0);
pocketno      = int32(0);
diameter      = 0.0;
frontangle    = 0.0;
backangle     = 0.0;
orientation   = int32(0);

if( coder.target( 'MATLAB' ) && nargin > 0 )
    offset        = constrAxesStructType( StructTypeName.MEX );
else
    offset        = constrAxesStructType;
end

if( coder.target( 'MATLAB' ) )
    params = {  toolno, pocketno, offset, diameter, frontangle, ...
                backangle, orientation };
else
    params.toolno       = toolno;
    params.pocketno     = pocketno;
    params.offset       = offset;
    params.diameter     = diameter;
    params.frontangle   = frontangle;
    params.backangle    = backangle;
    params.orientation  = orientation;
end

end