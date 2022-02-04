clear; clc;

generate_for_arm_32 = true;
generate_for_x86_64 = false;
generate_for_arm_64 = false;

cfg = coder.config('lib', 'ecoder', true);
cfg.IndentSize = 4;
cfg.BuildConfiguration = 'Faster Runs';
cfg.ColumnLimit = 100;
cfg.GenCodeOnly = true;
cfg.InlineBetweenUserFunctions = 'Speed';
cfg.PreserveArrayDimensions = true;
cfg.GenerateReport = false;
cfg.GenerateCodeMetricsReport = false;
cfg.SupportNonFinite = false;
cfg.TargetLang = 'C++';
cfg.TargetLangStandard = 'C++11 (ISO)';
cfg.MATLABSourceComments = true;
cfg.EnableAutoExtrinsicCalls = false;

if  generate_for_x86_64
    cfg.HardwareImplementation.TargetHWDeviceType = 'Intel->x86-64 (Linux 64)';
    cfg.HardwareImplementation.ProdHWDeviceType = 'Intel->x86-64 (Linux 64)';
    cfg.CodeReplacementLibrary = 'Intel SSE (Linux)';
    output_root = '../x86/matlab/generated';
elseif generate_for_arm_32
    cfg.HardwareImplementation.TargetHWDeviceType = 'ARM Compatible->ARM Cortex';
    cfg.HardwareImplementation.ProdHWDeviceType = 'ARM Compatible->ARM Cortex';
    output_root = '../arm/matlab/generated';
elseif generate_for_arm_64
    cfg.HardwareImplementation.TargetHWDeviceType = 'ARM Compatible->ARM 64-bit (LP64)';
    cfg.HardwareImplementation.ProdHWDeviceType = 'ARM Compatible->ARM 64-bit (LP64)';
    output_root = '../arm64/matlab/generated';
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

cfg.HighlightPotentialDataTypeIssues = true;
cfg.HighlightPotentialRowMajorIssues = true;

cfg.CustomHeaderCode = '#include "functions.h"';

configType = coder.OutputType('FeedoptDefaultConfig');
ctxType = coder.OutputType('InitFeedoptPlan');
resampleType = coder.OutputType('ResampleState');
SplineType = coder.OutputType('bspline_create');
CurvType = coder.OutputType('ConstrCurvStructType');

global sqrt_calls sin_calls cos_calls cot_calls DebugConfig
sqrt_calls = 0;
sin_calls = 0;
cos_calls = 0;
cot_calls = 0;
DebugConfig = 0;

codegen('-config', cfg,'-d', output_root, '-o', 'opencn_matlab',...
    'EvalCurvStruct', '-args', {ctxType, CurvType, coder.typeof(0.0, [1, Inf], [0, 1])},...
	'FeedoptDefaultConfig',...
	'InitFeedoptPlan', '-args', configType,...
	'FeedoptPlan', '-args', ctxType,...
	'linspace', '-args', {0,1,100},...
    'CalcTransition', '-args', {ctxType, CurvType, CurvType},...
	'ConstrCurvStructType', ...
    'ConstrLineStruct', '-args', {[0,0,0]', [0,0,0]', 0.1, ZSpdMode.NN},...
    'ConstrHelixStructFromArcFeed', '-args', {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,[0,0,0]'},...
    'bspline_create', '-args', {int32(4), linspace(0,1,10)},...
    'ResampleState', '-args', 0,...
    'ResampleNoCtx', '-args', {resampleType, SplineType, CurvType},...
    'EvalPosition', '-args', {CurvType, CurvType, 0},...
    'bspline_copy', '-args', SplineType,...
    'ConfigSetSource', '-args', {configType, coder.typeof(' ', [1, 1024], [0, 1])});