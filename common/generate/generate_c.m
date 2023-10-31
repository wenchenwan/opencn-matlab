clear; clc;

% the current folder must be 'opencn/agency/usr/matlab/common'
check_wkdir();

% please choose the target first ( only 1 target is generated at the time )
generate_for_x86_64 = false;
generate_for_arm_64 = true;

[cfg, output_root] = generate_c_config( generate_for_arm_64, ...
                                        generate_for_x86_64 );

% please choose the libraries to generate ( All can be generated )
GenerateAll = true;

if( ~GenerateAll )
    GenerateFeedopt    = true;
    GenerateKinematics = false;
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
        remove_date_from_headers( dirName, "*.*" );
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
        remove_date_from_headers( dirName, "*.*" );
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


function [] = remove_date_from_headers( output_dir, fileType )
% remove_date_from_headers : Remove the date from generated files. 
% It is a must have to simplify the git history of the generated files.
% Inputs :
%   output_dir  : The folder which contains the files to parse
%   fileType    : The file extenssion to consider
% 
% Outputs : 
%
files = {dir(fullfile(output_dir, fileType)).name};
    
    % Return if fails to find any files
    if( isempty(files) ), return; end
    
    expression = "code generated on";

    for f_ = files
        fileName = fullfile(output_dir, f_{:});

        fid = fopen(fileName,'r');          % Open File to read
        if( fid < 0 ), continue; end
        tline = 's';
        A = {[]};
        while ischar(tline)
            tline = fgetl(fid);
            if ischar(tline) && ~contains(tline, expression)                
                A{ end + 1 } = tline;
            end
        end
        fclose(fid);

        fid2=fopen(fileName,'w');            % Open file to write
        for i = 1:length(A)
            fprintf(fid2,'%s\n', A{i});
        end
        fclose(fid2);
    end

end
