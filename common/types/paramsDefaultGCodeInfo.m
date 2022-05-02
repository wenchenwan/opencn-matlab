function [ params ] = paramsDefaultGCodeInfo( ~ ) %#codegen
% paramsDefaultGCodeInfo : Get default params for GCode information.
Type         = CurveType.Line;
zspdmode     = ZSpdMode.NN;
TRAFO        = false;
HSC          = false;
G91          = false;
G91_1        = true;
FeedRate     = 0.0;
SpindleSpeed = 0.0;
gcode_source_line = uint64( 0 );

if( coder.target( 'MATLAB' ) )
    params = { Type, zspdmode, TRAFO, HSC, G91, G91_1, FeedRate, ...
               SpindleSpeed, gcode_source_line };
else
    params.Type     = Type;
    params.zspdmode = zspdmode;
    params.TRAFO    = TRAFO;
    params.HSC      = HSC;
    params.G91      = G91;
    params.G91_1    = G91_1;
    params.FeedRate = FeedRate;
    params.SpindleSpeed = SpindleSpeed;
    params.gcode_source_line = gcode_source_line;
end

end