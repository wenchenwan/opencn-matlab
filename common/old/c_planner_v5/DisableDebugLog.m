function DisableDebugLog(cfg)
global DebugConfig

    DebugConfig = bitset(DebugConfig, int32(cfg), 0); 

end