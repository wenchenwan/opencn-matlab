% amax = [20000,20000,20000];...
%         3e4 3e4 3e4];       % [mm/s²]
amax = [ 15000,  15000,  15000,   0, 200,   1000 ];
jmax = [ 750000, 750000, 3000000, 0, 10000, 50000];
    
% jmax = [1500000,1500000,1500000] / 10;...
%         2e8 2e8 2e8];       % [mm/s³]
    
% CutOff = [0.1 0.15];        % [mm]   
CutOff = 0.15;

vmax_norm_tol = 0.05;       % ratios
amax_xyz_tol  = 0.05;
jmax_xyz_tol  = 0.05;

tol_opt_vnorm  = 0.10;      % bang-bang tolerances
tol_opt_a      = 0.10;
tol_opt_j      = 0.30;
TOpt_tol       = 0.80;       

ProfiledFcts = {'FeedoptPlanRun';...
                'ReadGCode';...
                'CheckCurvStructs';...
                'CompressCurvStructs';...
                'SmoothCurvStructs';...
                'SplitCurvStructs';...
                'FeedratePlanning';...
                'ResampleNoCtx'};
            

max_time = 20;              % machining max time [min]
