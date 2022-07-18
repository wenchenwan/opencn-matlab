function cfg = ConfigSetSource(cfg, filename)
    coder.inline("never");
    
    N = size(filename, 2);
    cfg.source(1:N) = filename;
    cfg.source(N+1:end) = 0;
end