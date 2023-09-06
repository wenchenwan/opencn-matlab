function [zspdmode, error] = getZspdmode( speed ) %#codegen
% Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
error = false;

if( isenum( speed ) )
    zspdmode = speed;
elseif( isfield( speed, "Info") )
    zspdmode = speed.Info.zspdmode;
elseif( isfield( speed, "zspdmode") )
    zspdmode = speed.zspdmode;
else
    error = false;
    return;
end
end