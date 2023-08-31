%% Basic example
% This is script provides a rapid overview of the different steps required
% by the algorithm.
%
clc; clear all; %close all;

check_wkdir(); % If current directory is the working directory

% Load default configuration parameters
cfg = FeedoptDefaultConfig;
% Set the path to the gcode file
cfg.source = 'ngc_test/misc/031_surfacage_TopLeftBack_V2.ngc';
% cfg.source = 'ngc_test/misc/031_surfacage_TopLeftBack_V2_untouched.ngc';

% Logging
setupLogs( cfg.LogFileName ); diary on;

% Initialization of the feed operator
ctx = initFeedoptPlan( cfg );
% DestroyContext( ctx );
% [ ret, ctx ] = loadCtx( "dev/test.mat" );
try

    % Run the geometrics operations, then solve the LP problem
    ctx = FeedoptPlanRun( ctx );                                     
%     [ ret ] = saveCtx( ctx, "dev/test.mat" );

    % Plot geometry
    plotGeometry(ctx, ctx.cfg, ctx.q_gcode, ctx.q_spline, false);
    plotGeometry(ctx, ctx.cfg, ctx.q_gcode, ctx.q_spline, true);
    return;
    pause( 0.5 );
% 
%     % Resampling of the parameter
%     fileName = "PR2/sampler/dome.csv";
%     resample4sampler( ctx, fileName );

    %Resampling of the parameter
    if( ctx.q_opt.isempty ), error("Queue empty before resampling"); end
    fileName = '.tmp.csv' ;
    resample2file( ctx, fileName ); ctx.q_opt.delete();

    % Load resampled data points
    res = readmatrix( fileName );    
    delete( fileName );
 
    % Transforms structure into vector for analysis
    [res_struct, indFeed, indAcc, indJerk] = get_res_struct( res, ctx.cfg.maskTot );

    % Analyse time optimality and constraints satisfaction
    analyse_optimality( res, indFeed, indAcc, indJerk, ctx.cfg.dt );

    % Plot the resulting trajectories
    plotTrajectories( ctx, res_struct );

catch ME
    DestroyContext(ctx);
    error( '%s\n%s\n%s\n', ME.message, "File name : " + ME.stack(1).name, ...
                           "Line : " + ME.stack(1).line );
end
% Free external memory (see queue function)
DestroyContext(ctx);

diary off;

%-------------------------------------------------------------------------%
%% Utility Functions
%-------------------------------------------------------------------------%

function [status] = check_constraints( tol, feed, a, j )
status = 0;
% max constraints respect verif
if ( feed > 1 + tol.v_tol ), bitset(status, 1); end

if any( a > 1 + tol.a_tol ), bitset(status, 2); end

if any( j > 1 + tol.j_tol ), bitset(status, 3); end

end

function [t_opt] = check_time_optimality( tol, feed, a, j )
N = length( feed );
t_opt = zeros(N, 4);

% max constraints respect verif
t_opt( : ,1 ) = ( feed > 1 - tol.tol_opt_v );

t_opt( : ,2 ) = any( a > 1 - tol.tol_opt_a, 2);

t_opt( :, 3 ) = any( j > 1 - tol.tol_opt_j, 2);

t_opt( :, 4 ) = any( t_opt( :, 1:3 ) ,2 );

end

function [] = analyse_optimality( res, indFeed, indAcc, indJerk, dt )
% Load parameters for validation
PfileName = pwd + "/Validate_OpenCN/params.m";
run(PfileName);

tol.v_tol       = vmax_norm_tol;
tol.a_tol       = amax_xyz_tol;
tol.j_tol       = jmax_xyz_tol;
tol.tol_opt_v   = tol_opt_vnorm;
tol.tol_opt_a   = tol_opt_a;
tol.tol_opt_j   = tol_opt_j;
tol.TOpt_tol    = TOpt_tol;

status     = check_constraints( tol, res( :, indFeed ), ...
                                     res( :, indAcc ), ...
                                     res( :, indJerk ) );
disp( optSolStatus2String( status ) );

t_opt_res  = check_time_optimality( tol, res( :, indFeed ), ...
                                         res( :, indAcc ), ...
                                         res( :, indJerk ) );

disp("Machining time : " + res(end, 1) * dt);

disp("Optimality : "                + sum( t_opt_res(:, end) ) / ...
    res(end, 1) * 100 + "[%]" );

disp("Optimality feedrate : "       + sum( t_opt_res(:, 1) ) / ...
    res(end, 1) * 100 + "[%]" );
disp("Optimality acceleration : "   + sum( t_opt_res(:, 2) ) / ...
    res(end, 1) * 100 + "[%]" );
disp("Optimality jerk : "           + sum( t_opt_res(:, 3) ) / ...
    res(end, 1) * 100 + "[%]" );
end

function [res_struct, indFeed, indAcc, indJerk] = get_res_struct( res, mask )
ind     = 1 : sum( mask );
indFeed = 3;
indR    = 5  + ind;
indAcc  = indR( end )    + ind;
indJerk = indAcc( end )  + ind;

res_struct.tvec       = res( :, 1 );
res_struct.uvec       = res( :, 2 );
res_struct.vvec       = res( :, 3 ) .* res( :, 4 ) * 60;
res_struct.fvec       = res( :, 4 ) * 60;
res_struct.cfvec      = res( :, 5 ) * 60;
res_struct.pvec       = res( :, indR );
res_struct.avec       = res( :, indAcc );
res_struct.jvec       = res( :, indJerk );
end

function [msg] = optSolStatus2String(status)
% optSolStatus2String :
% Translate the returned status of the optimization into its corresponding
% message
%
% status : Status of the returned solution.
%
% msg    : Message corresponding to a given status

msg = "Optimization successed !";

constr = bitand(status, 7);
if constr ~= 0
    if bitget(constr, 1)
        msg = 'V max exceeded!.\n';
    elseif bitget(constr, 2)
        msg = 'A max exceeded!.\n';
    elseif bitget(constr, 3)
        msg = 'J max exceeded!.\n';
    end
end

if bitand(status, 8) ~= 0
    msg = 'Not time optimal!\n';
end
end

function [] = setupLogs( logFileName )

mkdir logs;

diary ([logFileName, '_', ...
    datestr(now,'yyyy_mm_dd_HH_MM_SS'), ...
    '.txt']);

% debug config init
global DebugConfig
DebugConfig = 0;

EnableDebugLog(DebugCfg.OptimProgress);
EnableDebugLog(DebugCfg.Validate);
EnableDebugLog(DebugCfg.FeedratePlanning);
EnableDebugLog(DebugCfg.Error);
EnableDebugLog(DebugCfg.Plots);
end