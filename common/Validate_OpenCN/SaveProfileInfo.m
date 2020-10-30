function [status, T] = SaveProfileInfo(dir, pcell)
% Record all profile info
% Called from Validate_OpenCN

status = 1;     % success default

fs = filesep;   % file separation character

NGcodes = size(pcell,1);
Ncomb = size(pcell,2);

for k = 1:NGcodes

    dir_k = [dir, fs, sprintf('%d_profile_results', k)];
    status = mkdir(dir_k);
    
    if status ~= 1
        continue;
    end

    for i = 1:Ncomb
        
        dir_k_i = [dir_k, fs, sprintf('%d_%d_profile_results', k, i)];
        status = mkdir(dir_k_i);

        if status ~= 1
            continue;
        end

        p = pcell{k, i};
        profsaveNoWeb(p, dir_k_i);


    end

end
    
end

