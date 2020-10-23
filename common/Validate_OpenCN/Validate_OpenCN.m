clc; clear; close all;

d         = datestr(datetime('now'));
homeDir = '/home/rozanov/opencn/agency/usr/matlab/common/Validate_OpenCN';
cd(homeDir);

%% Choose directory with G-code validation files
fs         = filesep; % file separation character according to Win/Linux
% Gdir       = uigetdir('.', 'Choose directory with G-code validation files');
Gdir       = '/home/rozanov/opencn/agency/usr/matlab/common/ngc_test/utility_test_gcodes';
dircontent = dir([Gdir, fs, '*.ngc']);
NGcodes    = length(dircontent);
Str        = sprintf('%d G-code files found', NGcodes);
% uiwait(msgbox(Str,'','modal'));

%% Initialization
Ok         = 1;
ErrorStr   = {};
MEcell     = {};
ProfilCell = {};
AssertErrorCtr   = 0;
NCtr       = 0;

%% Config
global DebugConfig
DebugConfig = 0;

cfg = FeedoptDefaultConfig;
cfg.NDiscr = 20;
cfg.NBreak = 10;
cfg.NHorz = 5;

%% Reading params to sweep from INI file
PfileName = 'config.ini';
ini = IniConfig(); % class got from Mathworks community
ini.ReadFile(PfileName);
% reading keys list from sections
[keys1, count_keys1] = ini.GetKeys('Extreme values');
[keys2, count_keys2] = ini.GetKeys('Max constrains tolerances');
[keys3, count_keys3] = ini.GetKeys('Time optimality tolerance');
% getting key values
values1 = ini.GetValues('Extreme values', keys1);
values2 = ini.GetValues('Max constrains tolerances', keys2);
values3 = ini.GetValues('Time optimality tolerance', keys3);

Str = sprintf('%d different parameter settings',...
    length(keys1)+length(keys2)+length(keys2));
% uiwait(msgbox(Str,'','modal'));

%% Preparing for profiling

DirProfileAll = [homeDir, fs, 'profile_results'];

if exist(DirProfileAll, 'dir') == 7
   status = rmdir(DirProfileAll, 's');
   assert(status==1, [sprintf('Impossible to delete folder:\n %s\n',...
       [homeDir, fs, DirProfileAll]), 'Do it manually']);
end

mkdir(DirProfileAll);
addpath(DirProfileAll);

param = ...
    {'Date';...
    '';...
    'G-code';...
    'amax[mm/s²]';...
    'jmax[mm/s³]';...
    'CutOff[mm]';...
    '';...
    'vmax_norm_tol[%]';...
    'amax_xyz_tol[%]';...
    'jmax_xyz_tol[%]';...
    'TimeOpt_tol[%]';...
    '';...
    'FeedoptPlanRun';...
    'ReadGCode';...
    'CheckCurvStructs';...
    'CompressCurvStructs';...
    'SmoothCurvStructs';...
    'SplitCurvStructs';...
    'FeedratePlanning_v4';...
    'ResampleNoCtx';...
    '';...
    'Forced Stops';...
    'Programmed Stops'};

Number = [1:length(param)];

% table preallocation
T = table('Size', [Number(end), 4],...
    'VariableTypes', {'uint16', 'string', 'double', 'double'},...
    'VariableNames', {'Number', 'Param', 'Value', 'TotalTime'});

for k=1:Number(end)
    T.Param(k)=param(k);
end

%% Params sweep

% Main loop
for k = 1:NGcodes
    % For each g-code file...
    cfg.source = [dircontent(k).folder, fs, dircontent(k).name];

    % all params combinations are tested
    for a=1:2   
        cfg.amax(1:3) = str2double(values1{a});
        for j=3:4
            cfg.jmax(1:3) = str2double(values1{j});
            for co=5:6
                cfg.CutOff = values1{co};
                ctx = InitFeedoptPlan(cfg);
                try
                    profile on
                    ctx = FeedoptPlanRun(ctx);                % q(u)            
                    uvec = PlotResampled_BR(ctx, ctx.cfg.dt); % u(t)
                    profile off
                   
                    conf = {k, keys1{a}, keys1{j}, keys1{co}};
                   
                    [~, T] = SaveProfileInfo(DirProfileAll, conf, T);
                    
                    
%                     T.Param
                    
                    [v_norm, acc, jerk] = CalcVAJ(ctx, CurvStruct, Bl, u_vec);
                    
%                     if ctx.forced_stop ~= 0 ||
%                         max(vnorm) > 
%                         Ok = 0;
%                     end
                    
                catch ME % here an assert is detected
                    profile off
                    Ok       = 0;
                    AssertErrorCtr = AssertErrorCtr + 1;
                    Str = sprintf('%s did not work with parameters combination: %s, %s, %s',...
                        dircontent(k).name, keys1{a}, keys1{j}, keys1{co});
                    ErrorStr{AssertErrorCtr} = Str;
                    MEcell{AssertErrorCtr}   = ME;
                end

            end
        end
    end
    
end

%% Make directory and copy all relevant info
GdirSplit = regexp(Gdir, fs, 'split');
GdirEnd   = GdirSplit{end};

DirNameGen = [homeDir, fs, 'Val_', GdirEnd, '_'];
DirNameOK = [DirNameGen, 'OK'];
DirNameFAILED = [DirNameGen, 'FAILED'];

if exist(DirNameOK, 'dir') == 7 || exist(DirNameFAILED, 'dir') == 7
   status = rmdir('Val_*', 's');
   assert(status==1, [sprintf('Impossible to delete folder:\n %s\n',...
       [DirNameGen, '*']), 'Do it manually']);
end

if Ok == 1
    DirName = DirNameOK;
else
    DirName = DirNameFAILED;
end

mkdir(DirName);
addpath(DirName);
SubGDir = [DirName, fs, GdirEnd];

if exist(SubGDir, 'dir') == 7
   status = rmdir(SubGDir, 's');
   assert(status==1, [sprintf('Impossible to delete folder:\n %s\n',...
       SubGDir), 'Do it manually']);
end

mkdir(SubGDir);
addpath(SubGDir);
SubProfileDir = [DirName, fs, 'profile_results'];
mkdir(SubProfileDir);
addpath(SubProfileDir);

copyfile(PfileName, DirName);                   % copy selected parameter file
copyfile('Validate_OpenCN.m', DirName);         % copy this .m source file

status = 1; % Success default
for k=1:NGcodes
    % copy all G-code files
    copyfile([dircontent(k).folder, fs, dircontent(k).name], SubGDir);
    
    % copy all profiling info relevant to this G-code file
    % .html files
    SubGDir_k = [SubProfileDir, fs, sprintf('%d_profile_results', k)];
    mkdir(SubGDir_k);
    addpath(SubGDir_k);
    
    % move profiling info safely
    ret = copyfile([DirProfileAll, fs,...
        sprintf('%d_*', k)], SubGDir_k);            
    if ret ~= 1
        status = 0;
    end
      
end

% No more need profile info folder here...
if status == 1
    rmdir(DirProfileAll, 's');
end


%% Last commit of Matlab submodule recorded in textfile

% Linux command
[status, CommitStr] = system('git log -1 > commit_info.txt');

if status == 0
    status = copyfile([homeDir, fs, 'commit_info.txt'], DirName);
    if status == 1
        delete([homeDir, fs, 'commit_info.txt']);
    end
end
