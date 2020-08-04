clear; clc;

generate_for_arm = false;

cfg = coder.config('lib', 'ecoder', true);
cfg.IndentSize = 4;
cfg.BuildConfiguration = 'Faster Runs';
cfg.ColumnLimit = 100;
cfg.GenCodeOnly = true;
cfg.FilePartitionMethod = 'SingleFile';
cfg.PreserveArrayDimensions = true;
cfg.GenerateReport = false;
cfg.GenerateCodeMetricsReport = false;
cfg.SupportNonFinite = false;
cfg.TargetLang = 'C++';
cfg.TargetLangStandard = 'C++11 (ISO)';
cfg.MATLABSourceComments = false;
cfg.EnableAutoExtrinsicCalls = false;

% cfg.Hardware = 'Intel->x86-64 (Linux 64)';
if ~generate_for_arm
    cfg.HardwareImplementation.TargetHWDeviceType = 'Intel->x86-64 (Linux 64)';
    cfg.HardwareImplementation.ProdHWDeviceType = 'Intel->x86-64 (Linux 64)';
    cfg.CodeReplacementLibrary = 'Intel AVX (Linux)';
    output_root = '../x86/matlab/generated';
else
    cfg.HardwareImplementation.TargetHWDeviceType = 'ARM Compatible->ARM Cortex';
    cfg.HardwareImplementation.ProdHWDeviceType = 'ARM Compatible->ARM Cortex';
    output_root = '../arm/matlab/generated';
end

cfg.CppNamespace = 'ocn';
cfg.GenerateExampleMain = 'DoNotGenerate';
cfg.GenerateMakefile = false;

cfg.EnableVariableSizing = true;
cfg.DynamicMemoryAllocation = 'Threshold';
cfg.SILPILCheckConstantInputs = false;
cfg.SILPILSyncGlobalData = false;
cfg.SaturateOnIntegerOverflow = false;
cfg.PreserveVariableNames = 'All';
% cfg.StackUsageMax = 8096*1024;

cfg.HighlightPotentialDataTypeIssues = true;
cfg.HighlightPotentialRowMajorIssues = true;

cfg.CustomHeaderCode = '#include "functions.h"';

configType = coder.OutputType('FeedoptDefaultConfig');
ctxType = coder.OutputType('InitFeedoptPlan');
resampleType = coder.OutputType('ResampleState');

% C = ConstrLineStruct([0,0,0]', [0,0,0]', 0.1, ZSpdMode.NN);
C = coder.OutputType('ConstrCurvStructType');

splineType = coder.OutputType('bspline_create');

global DebugActive
DebugActive = false;

% 
% R0D0 = [0,0,0]';
% codegen('-config', cfg, '-d', 'gen_c/g2hermite',...
%     'G2_Hermite_Interpolation', '-args', {R0D0,R0D0,R0D0,R0D0,R0D0,R0D0});
% 
% 
% return;
% %% FEEDOPT USERSPACE
codegen('-config', cfg,'-d', output_root, ...
    'sinspace', '-args', {2,3,int32(20)},...
    'EvalCurvStruct', '-args', {ctxType, C, coder.typeof(0.0, [1, Inf], [0, 1])},...
    'c_roots_', '-args', coder.typeof(0, [1, 12], [0, 1]),...
    'PrintCurvStruct', '-args', {ctxType, C},...
    'CalcTransition', '-args', {ctxType, C, C},...
    'FeedoptDefaultConfig',...
    'InitFeedoptPlan', '-args', configType, ...
    'FeedoptPlan', '-args', ctxType,...
    'linspace', '-args', {0,1,100},...
    'ConstrCurvStructType', ...
    'ConstrLineStruct', '-args', {[0,0,0]', [0,0,0]', 0.1, ZSpdMode.NN},...
    'ConstrHelixStruct', '-args', {[0,0,0]', [0,0,0]', [0,0,0]', 0, 0, 0, ZSpdMode.NN},...
    'ConstrHelixStructFromArcFeed', '-args', {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,[0,0,0]'},...
    'bspline_create', '-args', {int32(4), linspace(0,1,10)},...
    'ResampleState', '-args', 0,...
    'ResampleNoCtx', '-args', {resampleType, splineType, C},...
    'EvalPosition', '-args', {C, C, 0},...
    'bspline_copy', '-args', splineType,...
    'CopyCurvStruct', '-args', C,...
    'ConfigSetSource', '-args', {configType, coder.typeof(' ', [1, 1024], [0, 1])});

