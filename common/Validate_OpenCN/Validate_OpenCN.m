clc; clear; close all;

d         = datestr(datetime('now'));
Cd        = cd;                             % current folder

%% Choose directory with G-code validation files
fs         = filesep; % file separation character
Gdir       = uigetdir('.', 'Choose directory with G-code validation files');
% Gdir       = '/home/rozanov/opencn/agency/usr/matlab/common/ngc_test/utility_test_gcodes';
dircontent = dir([Gdir, fs, '*.ngc']);
NGcodes    = length(dircontent);
Str        = sprintf('%d G-code files found', NGcodes);
uiwait(msgbox(Str,'','modal'));

%% Choose parameter file
[Pfile, Ppath] = uigetfile('*.m');
PfileName      = [Ppath, Pfile];
run(PfileName);

%% Form all params combinations to test
Ncomb = 0;
for line_a = 1:size(amax, 1)
    for line_j = 1:size(jmax, 1)
        for co = 1:size(CutOff, 2)
            Ncomb = Ncomb + 1;
            Comb(Ncomb).a_max = amax(line_a, :);
            Comb(Ncomb).j_max = jmax(line_j, :);
            Comb(Ncomb).Cut_Off = CutOff(co);
        end
    end
end

Str = [sprintf('%d different parameter settings\n', Ncomb),...
            'will be tested with each g-code'];
        
uiwait(msgbox(Str,'','modal'));

%% setup wait bar
fw = waitbar(0, '');

%% Feedopt config
global DebugConfig
DebugConfig = 0;

cfg = FeedoptDefaultConfig;
cfg.NDiscr = 20;
cfg.NBreak = 10;
cfg.NHorz = 5;

%% Initialization
OK               = 1;
MEcell           = cell(NGcodes, Ncomb);
ProfilCell       = cell(NGcodes, Ncomb);
AssertErrorCtr   = 0;
NCtr             = 0;

% Report struct init
for k=1:NGcodes
    for i=1:Ncomb
        Report.ExactStopsNbr(k, i).forced = 0;
        Report.ExactStopsNbr(k, i).programmed = 0;
        
        for m=1:size(ProfiledFcts, 1)
            Report.Profiling(k, i).Function(m).Name = ProfiledFcts{m};
            Report.Profiling(k, i).Function(m).TotalTime = 0;
        end
    end
end

%% Params sweep

% Main loop
for k = 1:NGcodes
    % For each g-code file...
    cfg.source = [dircontent(k).folder, fs, dircontent(k).name];

    % all params combinations are tested
    for i = 1:Ncomb
        
        cfg.amax = Comb(i).a_max;
        cfg.jmax = Comb(i).j_max;
        cfg.CutOff = Comb(i).Cut_Off;
        ctx = InitFeedoptPlan(cfg);

        try
            
            NCtr = NCtr + 1;
            Str  = sprintf('processing G-code file %s, parameter setting %d',...
                dircontent(k).name(5:end), i);
            waitbar(NCtr/Ncomb, fw, Str); % update waitbar 
            
            profile on
            ctx = FeedoptPlanRun(ctx);                % q(u)            
            uvec = PlotResampled_BR(ctx, ctx.cfg.dt); % u(t)
            profile off
                        
            ProfilCell{k, i} = profile('info');
            
            Report.ExactStopsNbr(k, i).forced = ctx.forced_stop;
            if Report.ExactStopsNbr(k, i).forced ~= 0
                OK = 0;
            end
            
            Report.ExactStopsNbr(k, i).programmed = ctx.programmed_stop;
            
            % Check constraints and time-optimality respect
            [status, ratioTOpt] = FoptVerif(ctx, uvec, vmax_norm_tol, amax_xyz_tol,...
                jmax_xyz_tol, TOpt_tol);
            if status ~= 1
                OK = 0;
            end
            Report.RatioTOpt(k, i) = ratioTOpt;
           
        catch ME % here an assert is detected
            
            profile off
            OK       = 0;
            AssertErrorCtr = AssertErrorCtr + 1;
            MEcell{AssertErrorCtr}   = ME;
            
        end
        
        DestroyContext(ctx);
    
    end

end

% close waitbar
close(fw);

%% Last commit hex number (first 8 digits) of Matlab submodule recorded in textfile

% Linux command
status = system('git log -1 -p > commit_info.txt');

% Relevant info is on the 1-st line
fid = fopen('commit_info.txt', 'r');
lineStr = fgetl(fid);
fclose(fid);

lineStrSplit = regexp(lineStr, ' ', 'split');
commitNbrStr = lineStrSplit{2}(1:8);

%% Make directory and copy all relevant info

% Remove test results folder, if any
DirNameGen = [Cd, fs, 'Val_', commitNbrStr, '_'];
DirNameOK = [DirNameGen, 'OK'];
DirNameFAILED = [DirNameGen, 'FAILED'];

if exist(DirNameOK, 'dir') == 7 || exist(DirNameFAILED, 'dir') == 7
   status = rmdir('Val_*', 's');
   pause(0.2);
   assert(status==1, [sprintf('Impossible to delete folder:\n %s\n',...
       [DirNameGen, '*']), 'Do it manually']);
end

% Dir to copy results
if OK == 1
    DirName = DirNameOK;
else
    DirName = DirNameFAILED;
end
mkdir(DirName);

% Subdir to copy g-codes tested
GdirSplit = regexp(Gdir, fs, 'split');
GdirEnd   = GdirSplit{end};
SubGDir = [DirName, fs, GdirEnd];

% Eventually remove existing subfolder
if exist(SubGDir, 'dir') == 7
   status = rmdir(SubGDir, 's');
   pause(0.2);
   assert(status==1, [sprintf('Impossible to delete folder:\n %s\n',...
       SubGDir), 'Do it manually']);
end

% Copy all g-files to the folder
mkdir(SubGDir);
copyfile(Gdir, SubGDir);

% Copy commit info text file
status = copyfile([Cd, fs, 'commit_info.txt'], DirName);
if status == 1
    delete([Cd, fs, 'commit_info.txt']);
end

copyfile(PfileName, DirName);                   % copy selected parameter file
copyfile('Validate_OpenCN.m', DirName);         % copy this .m source file

% Ask user whether to save profiling results 
answer = questdlg('Save profiling info in html format?', ...
	'Profiling', ...
	'Yes','No','No');

% Handle response
switch answer
    
    case 'Yes'
        
        DirProfile = [DirName, fs, 'profile_results'];

        if exist(DirProfile, 'dir') == 7
           status = rmdir(DirProfile, 's');
           assert(status==1, [sprintf('Impossible to delete folder:\n %s\n',...
               DirProfile), 'Do it manually']);
        end

        status = mkdir(DirProfile);
        
        if status ==1
            SaveProfileInfo(DirProfile, ProfilCell);
        end
               
    case 'No'
        
        % Do nothing
        
end

% Profiling report save for chosen fcts
for k=1:NGcodes
    for i=1:Ncomb
        for m=1:size(ProfilCell{k, i}.FunctionTable, 1)
            for l=1:size(ProfiledFcts, 1)
                if strcmp(ProfilCell{k, i}.FunctionTable(m).FunctionName,...
                        ProfiledFcts{l})
                    Report.Profiling(k, i).Function(l).TotalTime =...
                        ProfilCell{k, i}.FunctionTable(m).TotalTime;
                end
            end
        end
    end
end

%% Saving relevant info in .mat file
fname = [DirName, '_status.mat'];
save(fname, 'd', 'MEcell', 'ProfilCell', 'Report');

status = copyfile(fname, DirName);
if status == 1
    delete(fname);
end





