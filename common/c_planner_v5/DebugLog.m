function DebugLog(cfg, varargin)
    % 1 -> stdout
    % 2 -> stderr
    
    if IsEnabledDebugLog(cfg)
        fprintf(1, varargin{:});        
    end

end
