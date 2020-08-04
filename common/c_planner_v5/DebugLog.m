function DebugLog(varargin)
global DebugActive
if DebugActive
    % 1 -> stdout
    % 2 -> stderr
    fprintf(2, varargin{:});
end
end
