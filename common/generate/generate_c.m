clear; clc;

% the current folder must be 'opencn/agency/usr/matlab/common'
check_wkdir();

% please choose the target first ( only 1 target is generated at the time )
generate_for_x86_64 = true;
generate_for_arm_64 = false;

[cfg, output_root] = generate_c_config( generate_for_arm_64, ...
                                        generate_for_x86_64 );

% please choose the libraries to generate ( All can be generated )
GenerateAll = true;

if( ~GenerateAll )
    GenerateFeedopt    = true;
    GenerateKinematics = true;
end

DEBUG = false;

output_root = output_root + "/matlab/generated/";

ERROR_COLOR = 2;

if( GenerateAll || GenerateFeedopt )
    cfg.CustomHeaderCode = '#include "functions.h"';
    name    = "Feedopt Code generation : ";
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
cfg.TargetLangStandard  = 'C89/C90 (ANSI)';
cfg.FilePartitionMethod = 'SingleFile';
end
