clc; clear; close all;

d         = datestr(datetime('now'));
Cd        = cd;                             % current folder

%% Choose directory with G-code validation files
fs         = filesep; % file separation character
% Gdir       = uigetdir('.', 'Choose directory with G-code validation files');

% temporary line!
Gdir       = char(pwd + "/ngc_test/");
dircontent = dir([Gdir, fs, '*.ngc']);
NGcodes    = length(dircontent);
Str        = sprintf('%d G-code files found', NGcodes);
uiwait(msgbox(Str,'','modal'));

%% Choose parameter file
% [Pfile, Ppath] = uigetfile('*.m');
% PfileName      = [Ppath, Pfile];

% temporary line!
PfileName = char(pwd + "/Validate_OpenCN/params.m");
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

%% Tolerance struct
tol.v_tol = vmax_norm_tol;
tol.a_tol = amax_xyz_tol;
tol.j_tol = jmax_xyz_tol;
tol.tol_opt_v = tol_opt_vnorm;
tol.tol_opt_a = tol_opt_a;
tol.tol_opt_j = tol_opt_j;
tol.TOpt_tol = TOpt_tol;

%% setup wait bar
fw = waitbar(0, '');

%% Feedopt config
cfg = FeedoptDefaultConfig;

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
        
        Report.MaxConstraints(k, i).Exceeded = 0;
        Report.MaxConstraints(k, i).vnorm = 0;
        Report.MaxConstraints(k, i).acc = 0;
        Report.MaxConstraints(k, i).jerk = 0;
        Report.NotTimeOptimal(k, i) = 0;
        Report.RatioTOpt(k, i) = 0;
    end
end

% logs init
if exist('logs', 'dir') == 7
   status = rmdir('logs', 's');
   pause(0.2);
   assert(status==1, [sprintf('Impossible to delete folder:\n %s\n',...
       'logs'), 'Do it manually']);
end
mkdir('logs');

diary ([cfg.LogFileName, '_', ...
        datestr(now,'yyyy_mm_dd_HH_MM_SS'), ...
        '.txt']);
diary on;
tic

% debug config init
global DebugConfig
DebugConfig = 0;

EnableDebugLog(DebugCfg.OptimProgress);
EnableDebugLog(DebugCfg.Validate);
EnableDebugLog(DebugCfg.Error);
EnableDebugLog(DebugCfg.Plots);

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
        
        % Log file header
        DebugLog(DebugCfg.Validate, [cfg.source, '\n']);
        DebugLog(DebugCfg.Validate, 'amax x: %.2e, y: %.2e, z: %.2e\n',...
            cfg.amax(1), cfg.amax(2), cfg.amax(3));
        DebugLog(DebugCfg.Validate, 'jmax x: %.2e, y: %.2e, z: %.2e\n',...
            cfg.jmax(1), cfg.jmax(2), cfg.jmax(3));
        DebugLog(DebugCfg.Validate, 'CutOff: %.3f\n', cfg.CutOff);
        DebugLog(DebugCfg.Validate,...
            'Tol opt V: %.0f%%\n', tol.tol_opt_v*100);
        DebugLog(DebugCfg.Validate,...
            'Tol opt A: %.0f%%\n', tol.tol_opt_a*100);
        DebugLog(DebugCfg.Validate,...
            'Tol opt J: %.0f%%\n', tol.tol_opt_j*100);
        DebugLog(DebugCfg.Validate,...
            'Tol max V: %.0f%%\n', tol.v_tol*100);
        DebugLog(DebugCfg.Validate,...
            'Tol max A: %.0f%%\n', tol.a_tol*100);
        DebugLog(DebugCfg.Validate,...
            'Tol max J: %.0f%%\n', tol.j_tol*100);

        try
            
            NCtr = NCtr + 1;
            Str  = sprintf('processing G-code file %s, parameter setting %d',...
                dircontent(k).name(5:end), i);
            waitbar(NCtr/Ncomb, fw, Str); % update waitbar 
            
            profile on
            
            ctx = FeedoptPlanRun(ctx);                          % q(u)   
            diary on;
            % Resampling of the parameter
            paramsPlotBr = containers.Map('disablePlot', true);
            uvec = PlotResampled_BR(ctx, ...
                max_time, ctx.cfg.dt, paramsPlotBr);                          % u(t)
            diary on;
            
            profile off
            
            ProfilCell{k, i} = profile('info');
            
            Report.ExactStopsNbr(k, i).forced = ctx.forced_stop;
            if Report.ExactStopsNbr(k, i).forced ~= 0
                OK = 0;
            end
            
            Report.ExactStopsNbr(k, i).programmed = ctx.programmed_stop;
            
            % Check constraints and time-optimality respect
            [status, ratioTOpt] = FoptVerif(ctx, uvec, tol);
            
            diary on;
            constr = bitand(status, 7);
            if constr ~= 0
                OK = 0;
                Report.MaxConstraints(k, i).Exceeded = 1;
                if bitget(constr, 1)
                    Report.MaxConstraints(k, i).vnorm = 1;
                    DebugLog(DebugCfg.Validate, 'V max exceeded!.\n');
                end
                if bitget(constr, 2)
                    Report.MaxConstraints(k, i).acc = 1;
                    DebugLog(DebugCfg.Validate, 'A max exceeded!.\n');
                end
                if bitget(constr, 3)
                    Report.MaxConstraints(k, i).jerk = 1;
                    DebugLog(DebugCfg.Validate, 'J max exceeded!.\n');
                end
            end
            
            if bitand(status, 8) ~= 0
                OK = 0;
                Report.NotTimeOptimal(k, i) = 1;
                DebugLog(DebugCfg.Validate, 'Not time optimal!.\n');
            end
            
            DebugLog(DebugCfg.Validate,...
                'Time optimality ratio: %.1f%%\n', ratioTOpt*100);
            Report.RatioTOpt(k, i) = ratioTOpt;
            
        catch ME % here an assert is detected
            
            profile off
            OK       = 0;
            AssertErrorCtr = AssertErrorCtr + 1;
            MEcell{AssertErrorCtr}   = ME;
            diary on
            DebugLog(DebugCfg.Validate,...
                'Assert detected:\n');
            DebugLog(DebugCfg.Validate,...
                '  Message: %s\n', ME.message);
            DebugLog(DebugCfg.Validate,...
                '  Function: %s\n', ME.stack(2).name);
            DebugLog(DebugCfg.Validate,...
                '  Line: %d\n', ME.stack(2).line);
            
        end
        
        DestroyContext(ctx);
        
        DebugLog(DebugCfg.Validate, 'End.\n');
    
    end

end

close(fw);

%% Last commit hex number (first 8 digits) of Matlab submodule recorded in textfile

% Linux command
system('git log -1 -p > commit_info.txt');

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

% copy selected parameter file and validate file
copyfile(PfileName, DirName);                   
copyfile('Validate_OpenCN/Validate_OpenCN.m', DirName);

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
        if isempty(ProfilCell{k, i})
            break;
        end
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
save(fname, 'd', 'MEcell', 'ProfilCell', 'Report', '-v7.3');

status = copyfile(fname, DirName);
if status == 1
    delete(fname);
end

%% Finalizing logs
endTime_s = toc;
endTime_h = floor(endTime_s/3600);
endTime_m = floor((endTime_s - endTime_h * 3600)/60);
endTime_s = endTime_s - endTime_h * 3600 - endTime_m *60;

fprintf('Elapsed time (HH:MM:SS.S): %02.0f:%02.0f:%02.1f\n',...
    endTime_h, endTime_m, endTime_s);
diary off;

% Copy logs
mkdir([DirName, fs, 'logs']);
status = copyfile('logs', [DirName, fs, 'logs']);
if status == 1
    rmdir('logs', 's');
end
