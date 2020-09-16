function DisableDebugLog(cfg)
global DebugConfig

    DebugConfig = bitset(DebugConfig, cfg, 0); 

end