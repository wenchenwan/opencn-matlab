function cfg = DefaultConfig
%#codegen
cfg = struct(...
    'dim1', 4,...
    'dim2', 5);
coder.cstructname(cfg, 'Config');
end