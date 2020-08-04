clc; clear; close all;

RTW.TargetRegistry.getInstance('reset');
cfg = coder.config('lib', 'ecoder', true);
cfg.CodeReplacementLibrary = 'blas';
cfg.SupportNonFinite = false;
cfg.GenerateReport = true;
cfg.LaunchReport = true;
cfg.EnableOpenMP = false;
% cfg.TargetLangStandard = 'C99 (ISO)';
cfg.SaturateOnIntegerOverflow = false;
cfg.TargetLang = 'C++';
cfg.GenerateCodeReplacementReport = true;

% Code Style
cfg.IndentSize = 4;

load buildconst_v4_arguments.mat

% [A, b, Aeq, beq] = BuildConstr_v4(CurvStructs, amax, jmax, v_0, at_0, v_1, at_1, ...
%                                   BasisVal, BasisValD, BasisValDD, BasisIntegr, u_vec);

codegen('BuildConstr_v4', '-config', cfg, '-args', ...
    {CurvStructs, amax, jmax, v_0, at_0, v_1, at_1, ...
     BasisVal, BasisValD, BasisValDD, BasisIntegr, u_vec});

% A = [1 2; 3 4];
% codegen('test_crl', '-config', cfg, '-args', {A});
