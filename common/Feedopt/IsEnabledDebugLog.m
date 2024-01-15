function [ value ] = IsEnabledDebugLog( cfg )
% IsEnableDebugLog : Is the Debug log enable
% 
% Inputs :
%   cfg : Configuration structure
%
% Outputs :
% Value : Boolean Value. TRUE means the debug log is enable.
%

global DebugConfig

    value = false;

    if bitget( DebugConfig, int32( cfg ) )
        value = true;
    end

end
