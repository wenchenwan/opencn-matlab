function EnableDebugLog(cfg)
global DebugConfig

    DebugConfig = bitset(DebugConfig, int32(cfg));  

end