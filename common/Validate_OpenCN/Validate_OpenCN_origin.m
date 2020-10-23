% This file shows an example how validation of OpenCN could be realized (RHG, oct 2, 2020)
clc; clear; close all;
%% Choose directory with G-code validation files
fs         = filesep; % file separation character according to Win/Linux
Gdir       = uigetdir('.', 'Choose directory with G-code validation files');
dircontent = dir(Gdir);
dircontent = dircontent(3:end);  % suppress . and ..
Str        = sprintf('%d G-code files found', length(dircontent));
uiwait(msgbox(Str,'','modal'));
%% Choose parameter file
[Pfile, Ppath] = uigetfile('*.m');
PfileName      = [Ppath, Pfile];
run(PfileName);
Str        = sprintf('%d different parameter settings', length(param));
uiwait(msgbox(Str,'','modal'));
%
Ok         = 1;
ErrorStr   = {};
MEcell     = {};
ProfilCell = {};
ErrorCtr   = 0;
NCtr       = 0;
NGcodes    = length(dircontent);
Nparam     = length(param);
Ntot       = NGcodes*Nparam;
%% setup wait bar
fw = waitbar(0, '');
%% sweep through all G-Code files and all parameter settings
for k = 1:NGcodes
    A = readmatrix([dircontent(k).folder, fs, dircontent(k).name]);  % to be replaced by G-code interpreter of LinuxCNC
    for l = 1:Nparam
        pause(0.2);  % remove later
        NCtr = NCtr + 1;
        Str  = sprintf('processing G-code file %s, parameter setting %d', dircontent(k).name(1), l);
        waitbar(NCtr/Ntot, fw, Str); % update waitbar 
        try
            profile on
            assert(A ~= param(l));   % to be replaced by OpenCN trajectory optimization algorithms
            nn = 100;                % to be replaced by OpenCN trajectory optimization algorithms
            MM = magic(nn);          % to be replaced by OpenCN trajectory optimization algorithms
            profile off
            ProfilCell{k, l} = profile('info');
        catch ME
            Ok       = 0;
            ErrorCtr = ErrorCtr + 1;
            Str      = sprintf('%s did not work with parameter setting %d', dircontent(k).name, l);
            ErrorStr{ErrorCtr} = Str;
            msgbox(ErrorStr,'','modal');
            MEcell{ErrorCtr}   = ME;
        end
    end
end
%
close(fw);
%
d         = date;
Cd        = cd;
GdirSplit = regexp(Gdir, fs, 'split');
GdirEnd   = GdirSplit{end};
%
if Ok == 1
    DirName = [Cd, fs, 'Val_', GdirEnd, '_', Pfile(1:end-2), '_', 'OK'];
else
    DirName = [Cd, fs, 'Val_', GdirEnd, '_', Pfile(1:end-2), '_', 'FAILED'];
end
%
if exist(DirName) == 7
    try
       rmdir(DirName, 's');   % sometimes this line throws an error
    end
end
%% make directory and copy all relevant files and directories
mkdir(DirName);
SubGDir = [DirName, fs, GdirEnd];
mkdir(SubGDir);
copyfile(PfileName, DirName);                          % copy selected parameter file
copyfile('Validate_OpenCN.m', DirName);                % copy this .m source file
copyfile(Gdir, SubGDir);                               % copy all G-code files
save([DirName, '_status'], ...
     'ErrorStr', 'd', 'MEcell', 'ProfilCell');         % save relevant data to status.mat file




