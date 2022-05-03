function [cfg] = generate_mex_config()
% generate_mex_config
% 
% Prepares the Coder to generate source files intended to be built,
% and to generate MEX (matlab executable) file in laguage specified
% by 'cfg.TargetLang' option (hereafter C++).
% These files can then be built after setting the 'cfg.GenCodeOnly' to false.
cfg = coder.config('mex');
% We want to generate MEX files, in order to be able to run
% G-code Interpreter with MATLAB.
% Mexing MATLAB functions also much improves execution speed.
% This helps when doing opencn matlab part validation, and debug.
cfg.GenCodeOnly = false;
% The code generator produces a single file for C/C++ functions,
% that map to MATLAB entry-point functions.
% The code generator produces separate C/C++ files for utility functions.
cfg.FilePartitionMethod = 'SingleFile';
% Generate code that uses N-dimensional indexing.
cfg.PreserveArrayDimensions = true;
% Report will only be generated when errors or warnings occur.
cfg.GenerateReport = false;
% Source files that will then be built, will be generated in C++.
% They will not be removed after build.
cfg.TargetLang = 'C++';
% Namespace used for opencn, custom code, as well as generated code.
cfg.CppNamespace = 'ocn';
% Variable-size arrays will be allowed for code generation.
cfg.EnableVariableSizing = true;
% The code generator allocates memory
% dynamically on the heap for variable-size arrays,
% whose size (in bytes) is greater than or equal to
% DynamicMemoryAllocationThreshold = 65536 (default).
cfg.DynamicMemoryAllocation = 'Threshold';
% The code generator does not produce code to handle integer overflow.
cfg.SaturateOnIntegerOverflow = false;
% Global data synchronization disabled.
% Before disabling synchronization, verify that your
% MEX function does not interact with MATLAB global data.
cfg.GlobalDataSyncMethod = 'NoSync';
% Disables Just-in-Time (JIT) compilation mode.
% The code generator creates a C/C++ MEX function
% by generating and compiling C/C++ code.
cfg.EnableJIT = false;
% The code generation report displays potential
% efficiency issues due to row-major layout.
cfg.HighlightPotentialRowMajorIssues = true;
% The generated code does not detect memory integrity violations.
% Setting 'cfg.IntegrityChecks' to false can improve performance.
cfg.IntegrityChecks = false;
% To end a long-running MEX function, you might have to terminate MATLAB.
cfg.ResponsivenessChecks = false;
% If possible, the code generator uses the memcpy optimization.
% To optimize code that copies consecutive array elements,
% the memcpy optimization replaces the code with a memcpy call.
cfg.EnableMemcpy = true;
% If possible, the code generator uses the memset optimization
% for assignment of floating-point zero to consecutive array elements.
% To assign consecutive array elements, the memset optimization uses a memset call.
cfg.InitFltsAndDblsToZero = true;

end