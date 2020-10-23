clc; clear; close all;

%% Choose directory with G-code validation files
fs         = filesep; % file separation character according to Win/Linux
% Gdir       = uigetdir('.', 'Choose directory with G-code validation files');
Gdir       = '/home/rozanov/opencn/agency/usr/matlab/common/ngc_test/full';
dircontent = dir([Gdir, fs, '*.ngc']);
dircontent = dircontent(1:4);
NGcodes    = length(dircontent);
Str        = sprintf('%d G-code files found', NGcodes);
uiwait(msgbox(Str,'','modal'));

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

%% Config INI file reading with params to sweep
PfileName = 'config.ini';
ini = IniConfig(); % class got from Mathworks community
ini.ReadFile(PfileName);
% reading keys list from section
[keys, count_keys] = ini.GetKeys('Extreme values');
% getting key values
values = ini.GetValues('Extreme values', keys);

%% Params sweep
Str = sprintf('%d different parameter settings', length(keys));
uiwait(msgbox(Str,'','modal'));

DirProfileAll = 'profile_results';
mkdir(DirProfileAll);

% Main loop
for k = 1:NGcodes
    % For each g-code file...
    cfg.source = [dircontent(k).folder, fs, dircontent(k).name];

    % all params combinations are tested
    for a=1:2   
        cfg.amax(1:3) = str2double(values{a});
        for j=3:4
            cfg.jmax(1:3) = str2double(values{j});
            for co=5:6
                cfg.CutOff = values{co};
                ctx = InitFeedoptPlan(cfg);
                try
                    profile on
                    ctx = FeedoptPlanRun(ctx);
                    
                    % Saving profiling info for current params combination
                    % in project folder
                    % in html format
                    DirProfile = [DirProfileAll, fs, sprintf('profile_results_%d_%s_%s_%s',...
                        k, keys{a}, keys{j}, keys{co})];
                    mkdir(DirProfile);
                    profsave(profile('info'), DirProfile);
                    
                    if ctx.forced_stop ~= 0
                        Ok = 0;
                    end
                    
                catch ME % here an assert is detected
                    profile off
                    Ok       = 0;
                    AssertErrorCtr = AssertErrorCtr + 1;
                    Str = sprintf('%s did not work with parameters combination: %s, %s, %s',...
                        dircontent(k).name, keys{a}, keys{j}, keys{co});
                    ErrorStr{AssertErrorCtr} = Str;
                    MEcell{AssertErrorCtr}   = ME;
                end

            end
        end
    end
    
end

d         = datestr(datetime('now'));
Cd        = cd;
GdirSplit = regexp(Gdir, fs, 'split');
GdirEnd   = GdirSplit{end};

%% Make directory and copy all relevant info
if Ok == 1
    DirName = [Cd, fs, 'Val_', GdirEnd, '_', 'OK'];
else
    DirName = [Cd, fs, 'Val_', GdirEnd, '_', 'FAILED'];
end
%
if exist(DirName, 'dir') == 7
   rmdir(DirName, 's');   % sometimes this line throws an error
end

mkdir(DirName);
SubGDir = [DirName, fs, GdirEnd];
mkdir(SubGDir);
SubProfileDir = [DirName, fs, 'profile_results'];
mkdir(SubProfileDir);

copyfile(PfileName, DirName);                         % copy selected parameter file
copyfile('Validate_OpenCN.m', DirName);               % copy this .m source file

for k=1:NGcodes
    % copy all G-code files
    copyfile([dircontent(k).folder, fs, dircontent(k).name], SubGDir);
    
    % copy all profiling info relevant to this G-code file
    SubGDir_k = [SubProfileDir, fs, sprintf('profile_results_%d', k)];
    mkdir(SubGDir_k);
    
    % move profiling info safely
    status = copyfile([DirProfileAll, fs,...
        sprintf('profile_results_%d_*', k)], SubGDir_k);            
    if status == 1
        rmdir(sprintf('profile_results_%d_*', k), 's');
    end
      
end

%% Report text file editing
sep = '--------------------';
fileID = fopen('OpenCN_report.txt','w');

fprintf(fileID,'Date:\n');
fprintf(fileID,'%s\n%s\n',d,sep);

fprintf(fileID,'Forced stops:\n');
fprintf(fileID,'%d\n%s\n', ctx.forced_stop, sep);
fprintf(fileID,'Programmed stops:\n');
fprintf(fileID,'%d\n%s\n', ctx.programmed_stop, sep);

fclose(fileID);

status = copyfile('OpenCN_report.txt', DirName);
if status == 1
    delete('OpenCN_report.txt'); 
end


%% Last commit of Matlab submodule recorded in textfile, with git-diff
cd '~/opencn/agency/usr/matlab/common';
% No need for terminal
[status, CommitStr] = system('TERM=ansi git log -1 -p > commit_info.txt');

if status == 0
    copyfile('commit_info.txt', DirName);
    if status == 1
        delete('commit_info.txt');
    end
end
