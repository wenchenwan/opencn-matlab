clear; clc;
cfg = coder.config('lib', 'ecoder', true);
cfg.IndentSize = 4;
cfg.BuildConfiguration = 'Faster Runs';
% cfg.ColumnLimit = 100;
cfg.GenCodeOnly = true;
cfg.FilePartitionMethod = 'MapMFileTOCFile';
% cfg.PreserveArrayDimensions = true;
cfg.GenerateReport = false;
cfg.SupportNonFinite = false;
cfg.TargetLang = 'C';
% cfg.CodeReplacementLibrary = 'Intel AVX (Linux)';
% cfg.Hardware = 'Intel->x86-64 (Linux 64)';
% cfg.HardwareImplementation.TargetHWDeviceType = 'Intel->x86-64 (Linux 64)';
cfg.HardwareImplementation.ProdHWDeviceType = 'Intel->x86-64 (Linux 64)';

cfg.CustomInclude = './c_functions/';
cfg.CustomSource = './c_functions/functions.c';
cfg.CustomLibrary = '/usr/lib/libgsl.so /usr/lib/libgslcblas.so';
cfg.CustomHeaderCode = '#include "c_simplex.hpp"';
cfg.EnableVariableSizing = true;
cfg.DynamicMemoryAllocation = 'Threshold';
cfg.SILPILCheckConstantInputs = false;
cfg.SILPILSyncGlobalData = false;
cfg.SaturateOnIntegerOverflow = false;
% cfg.StackUsageMax = 8096*1024;
cfg.TargetLangStandard = 'C89/C90 (ANSI)';

cfg.HighlightPotentialDataTypeIssues = true;
cfg.HighlightPotentialRowMajorIssues = true;

cfg.EnableMemcpy = false;           % Disabme memcopy
cfg.InitFltsAndDblsToZero = false;  % Disable memset

%cfg.DynamicMemoryAllocationThreshold = Nmax*Ndiscr_max*8 + 1;

codegen('-config', cfg,'-d', 'test_gen', ...
    'TestDynamicInterop');



