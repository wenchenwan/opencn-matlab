function EnableDebugLog( cfg )
% EnableDebugLog : Enable debug log
%
% Inputs :
% cfg   : Configuration structure
%
global DebugConfig
    DebugConfig = bitset(DebugConfig, int32(cfg));  
end
