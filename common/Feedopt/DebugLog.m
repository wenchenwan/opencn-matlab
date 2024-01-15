function DebugLog( cfg, varargin )
%#codegen
% DebugLog : Print msg in log pipe.
%
% Inputs : 
% cfg       : The configuration structure
% varargin  : Variable types of arguments (a.k.a print msg)
%   
    if IsEnabledDebugLog( cfg )
    %   Output
    %   stdout : 1
    %   stderr : 2
        output  = 1;
        fprintf( output, varargin{ : } );        
    end

end
