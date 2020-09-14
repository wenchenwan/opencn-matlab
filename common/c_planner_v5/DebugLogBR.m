function DebugLogBR(ctx, varargin)
global DebugActiveBR
if DebugActiveBR
    % 1 -> stdout
    % 2 -> stderr
    fprintf(1, varargin{:});
    fprintf(ctx.cfg.logID, varargin{:});
end
end
