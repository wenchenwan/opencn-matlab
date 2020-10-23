function [status, T] = SaveProfileInfo(DirProfileAll, conf, T)
% Record all profile info
% Called from Validate_OpenCN

status = 1; % Success by default

fs = filesep; % file separator

% Saving profiling info for current params combination
% in project folder, then in subfolder
% in html format
DirProfile = [DirProfileAll, fs, sprintf('%d_%s_%s_%s',...
    conf{1}, conf{2}, conf{3}, conf{4})];
mkdir(DirProfile);
addpath
p = profile('info');
profsaveNoWeb(p, DirProfile);

% Renaming all .html files in profiling directory
% with <profiled function name>_<fct nbr>.html
% Default output of profsave(): file<nbr>.html

% The first file file0.html is renamed as: list.html
ret = movefile([DirProfile, fs, 'file0.html'],...
    [DirProfile, fs, 'list.html']);
if ret ~= 1
    status = 0;
end

for k=1:size(p.FunctionTable, 1)
    
    HtmlFullFileName = [DirProfile, fs, sprintf('file%d.html', k)];
    NewFullFileName = [DirProfile, fs, ...
        sprintf('%d_%s.html', k, p.FunctionTable(k).FunctionName)];
    ret = movefile(HtmlFullFileName, NewFullFileName);
    if ret ~= 1
        status = 0;
    end     
    
    for i=1:length(T.Param)
        if T.Param(i) == p.FunctionTable(k).FunctionName
            T.TotalTime(i) = p.FunctionTable(k).TotalTime;
            T.Number(i) = k;
            break;
        end
    end
   
end

