clear; clc;

% the current folder must be 'opencn/agency/usr/matlab/common'

% please choose the target first ( only 1 target is generated at the time )
generate_for_arm_32 = false;
generate_for_x86_64 = true;
generate_for_arm_64 = false;

[cfg, output_root] = generate_c_config( generate_for_arm_32, ...
    generate_for_arm_64, ...
    generate_for_x86_64 );
% please choose the libraries to generate ( All can be generated )

GenerateAll = false;

if( ~GenerateAll )
    GenerateFeedopt    = false;
    GenerateKinematics = true;
end

DEBUG = false;

output_root = output_root + "/matlab/generated/";

ERROR_COLOR = 2;

if( GenerateAll || GenerateFeedopt )
    name = "Feedopt Code generation : ";
    dirName = output_root + "Feedopt/";
    disp(name + "start" );
    try
        generate_feedopt_c( cfg, dirName, DEBUG );
    catch ME
        fprintf( ERROR_COLOR, name + "failed : " + ME.message + "\n" );
    end
end

if( GenerateAll || GenerateKinematics )
    cfg = configure_kernel( cfg );
    name = "Kinematics Code generation : ";
    dirName = output_root + "Kinematics/";
    disp(name + "start" );
    try
        generate_kinematics_c( cfg, dirName, DEBUG );
    catch ME
        fprintf( ERROR_COLOR, name + "failed : " + ME.message + "\n" );
    end
end

function [ cfg ] = configure_kernel( cfg )
cfg.TargetLang = 'C';
% Language standard to use for the generated code.
% For C, the default library is 'C99 (ISO)'.
cfg.TargetLangStandard = 'C89/C90 (ANSI)';
end

function [cfg, output_root] = generate_c_config(generate_for_arm_32, ...
                                                generate_for_arm_64, ...
                                                generate_for_x86_64 )
% generate_c_config
%
% Comments from the Mathworks coder reference documentation.

% config_obj = coder.config(build_type,'ecoder',ecoder_flag)
% ----------------------------------------------------------
% build_type = 'lib': Create a code generation configuration object for a standalone C static library.
% ecoder_flag, 'ecoder', true: Create a coder.EmbeddedCodeConfig object without Embedded Coder.
cfg = coder.config('lib', 'ecoder', true);
% Number of characters per indentation level,
% specified as a positive integer in the range [2,8]
cfg.IndentSize = 4;
% Build configuration selected for code generation from MATLAB code.
% This property is present only if you generate standalone code.
cfg.BuildConfiguration = 'Faster Runs';
% This value is the default value.
% The code generator produces separate C/C++
% files for each MATLAB language file.
cfg.FilePartitionMethod = 'MapMFileToCFile';
% The code generator produces a single file for C/C++.
% functions that map to your MATLAB entry-point functions.
% The code generator produces separate C/C++ files for utility functions.
% Important: Matlab crash with 'SingleFile' option and 32-bit ARM target.
% cfg.FilePartitionMethod = 'SingleFile';
% ----------------------------------------
% Maximum number of columns before a line break in the generated code,
% specified as a positive integer in the range [45, 65536].
cfg.ColumnLimit = 100;
% The code generator produces C/C++ source code,
% but does not invoke the make command or build object code.
cfg.GenCodeOnly = true;
% This value is the default value.
% Uses internal heuristics to determine whether to perform inlining at a call site.
% This setting usually leads to highly optimized code.
cfg.InlineBetweenUserFunctions = 'Speed';
% Generate code that uses N-dimensional indexing.
cfg.PreserveArrayDimensions = true;
% This value is the default value.
% The code generator produces a report only if error or warning messages
% occur, or if you set LaunchReport to true.
cfg.GenerateReport = false;
% This value is the default value.
% The code generator does not run static code
% metrics analysis at code generation time.
cfg.GenerateCodeMetricsReport = false;
% The code generator does not produce code to
% support nonfinite values (NaN, Inf, ...).
cfg.SupportNonFinite = false;
% Language to use in generated code, specified as 'C' or 'C++'.
% If you specify C++, the code generator wraps the C code into .cpp files,
% so that you can use a C++ compiler and interface with external C++ applications.
cfg.TargetLang = 'C++';
% Language standard to use for the generated code.
% For C++, the default library is 'C++11 (ISO)'.
cfg.TargetLangStandard = 'C++11 (ISO)';

% The code generator inserts MATLAB source code as comments in the generated code.
% A traceability tag immediately precedes each line of source code.
% The traceability tag helps you to locate the corresponding MATLAB source code.
% The code generator also includes the MATLAB function signature in the function banner.
cfg.MATLABSourceComments = true;
% The code generator does not treat common
% visualization functions as extrinsic functions.
% unless you declare them as extrinsic.
cfg.EnableAutoExtrinsicCalls = false;
% Namespace for the generated C++ code.
cfg.CppNamespace = 'ocn';
% The code generator does not generate an example C/C++ main function.
cfg.GenerateExampleMain = 'DoNotGenerate';
% The code generator does not generate a makefile during the build process.
cfg.GenerateMakefile = false;
% This value is the default value.
% Variable-size arrays are allowed for code generation.
cfg.EnableVariableSizing = true;
% This value is the default value.
% The code generator allocates memory dynamically on the heap for variable-size arrays,
% whose size (in bytes) is greater than or equal to
% DynamicMemoryAllocationThreshold (default: 65536).
cfg.DynamicMemoryAllocation = 'Threshold';
% Constant input checking mode for a software-in-the-loop (SIL) execution
% or processor-in-the-loop (PIL) execution.
% The SIL or PIL execution does not compare the
% value that a test file provides for a constant input
% argument with the value specified at code
% generation time. The SIL or PIL execution uses
% the value specified at code generation time. If the
% test file uses a different value, then the results in
% MATLAB might differ from the results in the SIL
% or PIL execution.
% It is possible to speed up a SIL or PIL execution
% by setting SILPILCheckConstantInputs to false.
cfg.SILPILCheckConstantInputs = false;
% The SIL or PIL execution does not synchronize
% the values of global variables in the SIL or PIL
% execution environment with the values in the
% MATLAB workspace. If the values are not
% synchronized, the results in MATLAB might differ
% from the results in the SIL or PIL execution.
% It is possible to speed up a SIL or PIL execution
% by setting SILPILSyncGlobalData to false.
cfg.SILPILSyncGlobalData = false;
% The code generator does not produce code to
% handle integer overflow. Do not set
% SaturateOnIntegerOverflow to false unless
% you are sure that your code does not depend on
% integer overflow support.
% If you disable integer overflow support
% and integrity checks are enabled (default),
% the generated code produces an error for overflows.
% If you disable integer overflow support and
% you disable integrity checks,
% the overflow behavior depends on your target C compiler.
% In the C standard, the behavior for integer overflow is undefined.
% However, most C compilers wrap on overflow.
% --------------------------------------
% cfg.IntegrityChecks — Memory integrity checking.
% The generated code detects memory integrity
% violations and stops execution with a diagnostic message.
cfg.SaturateOnIntegerOverflow = false;
% Preserve all variable names. This parameter value disables variable reuse.
cfg.PreserveVariableNames = 'All';
% The code generation report highlights MATLAB
% code that results in single-precision or double-
% precision operations in the generated C/C++ code.
cfg.HighlightPotentialDataTypeIssues = true;
% The code generation report displays potential
% efficiency issues due to row-major layout. This
% value is the default value.
cfg.HighlightPotentialRowMajorIssues = true;
% Custom code that appears near the top of each C/C++
% header file generated from your MATLAB code,
% except rtwtypes.h and rtwhalf.h
cfg.CustomHeaderCode = '#include "functions.h"';

if  generate_for_x86_64
    %     Manufacturer and type of the target (test) hardware board
    cfg.HardwareImplementation.TargetHWDeviceType = 'Intel->x86-64 (Linux 64)';
    %     Manufacturer and type of the production hardware board.
    %     Specifying the ProdHWDeviceType property sets device-specific properties
    %     for the production hardware.
    cfg.HardwareImplementation.ProdHWDeviceType = 'Intel->x86-64 (Linux 64)';
    %     Code replacement library for generated code.
    %     Generates calls to a specific platform, compiler,
    %     or standards code replacement library. The list of
    %     named libraries depends on:
    %     • Installed support packages.
    %     • System target file, language, language
    %       standard, and device vendor configuration.
    %     • Whether you created and registered code
    %       replacement libraries, using the Embedded
    %       Coder product.
    cfg.CodeReplacementLibrary = 'Intel SSE (Linux)';
    output_root = '../x86';
elseif generate_for_arm_32
    cfg.HardwareImplementation.TargetHWDeviceType = 'ARM Compatible->ARM Cortex';
    cfg.HardwareImplementation.ProdHWDeviceType = 'ARM Compatible->ARM Cortex';
    output_root = '../arm';
elseif generate_for_arm_64
    cfg.HardwareImplementation.TargetHWDeviceType = 'ARM Compatible->ARM 64-bit (LP64)';
    cfg.HardwareImplementation.ProdHWDeviceType = 'ARM Compatible->ARM 64-bit (LP64)';
    output_root = '../arm64';
end

end