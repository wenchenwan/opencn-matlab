function [ zspdmode, error ] = getZspdmode( speed ) 
%#codegen
% getZspdmode: Get the current zero speed mode
% 
% Inputs : 
%   speed    : structure with zspdmode for the speed
%
% Outputs :
%   zspdmode : Zero speed mode
%   error    : Error bolean value. TRUE if no zspdmode has been found.
%

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
