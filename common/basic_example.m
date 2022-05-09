%% Basic example
% This is script provides a rapid overview of the different steps required
% by the algorithm.
%
clc; clear all; close all;

% Load default configuration parameters
cfg = FeedoptDefaultConfig;

% For testing B spline
cfg.Compressing.Skip = 0;
cfg.Compressing.ColTolCos = 0.1 * cfg.Compressing.ColTolCos;

% Set the path to the gcode file
cfg.source = 'ngc_test/unit/012_spline.ngc';

% Logging
setupLogs( cfg.LogFileName ); diary on;

% Initialization of the feed operator
ctx = initFeedoptPlan( cfg );

try

    % Run the geometrics operations, then solve the LP problem
    ctx = FeedoptPlanRun( ctx );                                     
    
    geometricPlot( ctx )

    % Resampling of the parameter
    fileName = '.tmp.csv' ;
    resample2file( ctx, fileName ); ctx.q_opt.delete();

    % Load resampled data points
    res = readmatrix( fileName );
    delete( fileName );

    % Transforms structure into vector for analysis
    [res_struct, indFeed, indAcc, indJerk] = get_res_struct( res );

    % Analyse time optimality and constraints satisfaction
    analyse_optimality( res, indFeed, indAcc, indJerk, ctx.cfg.dt );

    % Plot the resulting trajectories
    plotTrajectories( ctx, res_struct );

catch ME
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

function [res_struct, indFeed, indAcc, indJerk] = get_res_struct( res )
indFeed = 3;
indR    = 5  + [ 1 : 3 ];
indAcc  = 8  + [ 1 : 3 ];
indJerk = 11 + [ 1 : 3 ];

res_struct.tvec       = res( :, 1 );
res_struct.uvec       = res( :, 2 );
res_struct.vvec       = res( :, 3 );
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

function plotTrajectories(ctx, res_struct)
% plotTrajectories :
%
% Plot the resluting trajectory of the optimization problem.
%
% ctx       : The contex
% fOpt_vec  : A structure of the resulting trajectories
PLOT_DIFF = true;

data = table(res_struct.uvec, res_struct.tvec, res_struct.pvec, res_struct.vvec,...
    res_struct.avec, res_struct.jvec, res_struct.fvec, res_struct.cfvec);

figure
subplot(3,3,[1,2,4,5,7,8])
scatter3(res_struct.pvec(:, 1), res_struct.pvec(:, 2), res_struct.pvec(:, 3), 1,...
    res_struct.vvec*60, 'o')
colormap jet
set(gca, 'Projection','orthographic')
% axis vis3d
% equal
xlabel('x')
ylabel('y')
zlabel('z')
colorbar

dcm_obj = datacursormode(gcf);
set(dcm_obj,'UpdateFcn',{@myupdatefcn,ctx, data})

if( PLOT_DIFF )
    %     fOpt_vec.uvec = 1 : length(fOpt_vec.uvec);
    [ v_diff, a_diff, j_diff ] = ...
        computeNumericalDerivation( res_struct.pvec, ctx.cfg.dt );

    v_diff = vecnorm( v_diff )';
    a_diff = a_diff ./ ctx.cfg.amax';
    j_diff = j_diff ./ ctx.cfg.jmax';
    %     fOpt_vec.uvec = fOpt_vec.tvec;
end

ax(1) = subplot(3,3,3);

if( PLOT_DIFF )
    plot(res_struct.uvec(2:end), v_diff * 60, 'b.', res_struct.uvec(2:end), ...
        res_struct.fvec(2:end), 'r');
else
    plot(res_struct.uvec, res_struct.vvec*60, 'b', res_struct.uvec, ...
        res_struct.fvec, 'r');
end

title('Velocity in mm/min')
xlabel('Cumulative u')
legend('norm', 'Specified Feedrate')
grid

ax(2) = subplot(3,3,6);

if( PLOT_DIFF )
    plot(res_struct.uvec(3:end), a_diff);
else
    plot(res_struct.uvec, res_struct.avec);
end

title('Normalized acceleration in mm/s^2')
xlabel('Cumulative u')
legend('x', 'y', 'z')
ylim([-1.2 1.2])
grid
%
% ax(3) = subplot(3,3,9);
% plot(fOpt_vec.uvec, fOpt_vec.pvec)
% title('Position')
% xlabel('Cumulative u')
% legend('x', 'y', 'z')
% grid


ax(3) = subplot(3,3,9);

if( PLOT_DIFF )
    plot(res_struct.uvec(4:end), j_diff);
else
    plot(res_struct.uvec, res_struct.jvec);
end
title('Normalized jerk in mm/s^3')
xlabel('Cumulative u')
ylim([-1.4 1.4])
legend('x', 'y', 'z')
grid


linkaxes(ax, 'x');
xlim([res_struct.uvec(1) res_struct.uvec(end)])
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