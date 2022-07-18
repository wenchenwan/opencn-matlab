function value = IsEnabledDebugLog(cfg)
global DebugConfig

    value = false;

    if bitget(DebugConfig, int32(cfg))
        value = true;
    end

end