clear; clc;

cfg = coder.config('lib', 'ecoder', true);
cfg.IndentSize = 4;
cfg.BuildConfiguration = 'Faster Runs';
cfg.GenCodeOnly = true;
cfg.FilePartitionMethod = 'MapMFileTOCFile';
cfg.PreserveArrayDimensions = true;
cfg.GenerateReport = false;
cfg.GenerateCodeMetricsReport = false;
cfg.SupportNonFinite = false;
cfg.TargetLang = 'C++';

cfg.HardwareImplementation.ProdHWDeviceType = 'Intel->x86-64 (Linux 64)';

cfg.EnableVariableSizing = true;
cfg.DynamicMemoryAllocation = 'Threshold';
cfg.SILPILCheckConstantInputs = false;
cfg.SILPILSyncGlobalData = false;
cfg.SaturateOnIntegerOverflow = false;

% config = DefaultConfig;
ctxType = coder.OutputType('InitializeContext');
configType = coder.OutputType('DefaultConfig');

codegen('-config', cfg,'-d', './generated', ...
    'DefaultConfig',...
    'InitializeContext', '-args', configType, ...
    'UseContext', '-args', ctxType);
