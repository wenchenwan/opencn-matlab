% - Cannot generate part of the mex files first, because there will be redefinition conflicts
% - If everything is generated at once, matlab creates a multiple entry function mex file, which is painfuly slow when calling it a lot
% What do we do???

clear; clc;
cfg = coder.config('mex');
cfg.GenCodeOnly = false;
cfg.FilePartitionMethod = 'MapMFileTOCFile';
cfg.PreserveArrayDimensions = true;
cfg.GenerateReport = false;
cfg.TargetLang = 'C++';
% cfg.CodeReplacementLibrary = 'Intel AVX (Linux)';
% cfg.Hardware = 'Intel->x86-64 (Linux 64)';
% cfg.HardwareImplementation.TargetHWDeviceType = 'Intel->x86-64 (Linux 64)';
% cfg.HardwareImplementation.ProdHWDeviceType = 'Intel->x86-64 (Linux 64)';
cfg.HardwareImplementation.ProdHWDeviceType = 'Generic->MATLAB Host Computer';

codegen('-config', cfg, 'main_call', 'matlab_function1');
