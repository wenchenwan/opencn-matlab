%% Basic example
% This is script provides a rapid overview of the different steps required
% by the algorithm.
%
clc; close all; clear all;

% Load default configuration parameters
cfg = FeedoptDefaultConfig;

% Set the path to the gcode file
cfg.source = 'ngc_test/anchor.ngc';

% Initialization of the feed operator
ctx = InitFeedoptPlan(cfg);

% Run the geometrics operations, then solve the LP problem
ctx = FeedoptPlanRun(ctx);                                     % q(u)

% Load parameters for validation
PfileName = pwd + "/Validate_OpenCN/params.m";
run(PfileName);

% Resampling of the parameter
uvec = PlotResampled_BR(ctx, max_time, ctx.cfg.dt);            % u(t)

% Create tolerance structure
tol.v_tol       = vmax_norm_tol;
tol.a_tol       = amax_xyz_tol;
tol.j_tol       = jmax_xyz_tol;
tol.tol_opt_v   = tol_opt_vnorm;
tol.tol_opt_a   = tol_opt_a;
tol.tol_opt_j   = tol_opt_j;
tol.TOpt_tol    = TOpt_tol;

% Check constraints and time-optimality are respected
[fOpt_vec, status] = checkFopt(ctx, uvec, tol);
disp(optSolStatus2String(status));

% Plot the resulting trajectories
plotTrajectories(ctx, fOpt_vec);

% Free external memory (see queue function)
DestroyContext(ctx);

%-------------------------------------------------------------------------%
                        %% Utility Functions
%-------------------------------------------------------------------------%

function [fOpt_vec, status] = checkFopt(ctx, uvec, tol)
% checkFopt : 
% Check the validity of the solution obtained. The constrainsts in speed, 
% acceleration and jerks are evaluated. A struct which contains the
% resulting trajectory is returned.
%
% ctx       : The contex
% uvec      : U vector after resampling
% tol       : Allowed tolerance used to evaluation the quality of the
%             solution
%
% fOpt_vec  : A structure of the resulting trajectories
% status    : The status of the optimization problem

status = 0;                                             % Success default
t_max  = 0;

% uvec will be empty if q_opt is empty
if isempty(uvec)
    bitset(status, 5);
    return;
end

t = -ctx.cfg.dt;
k_max = size(uvec, 1);

fOpt_vec.uvec       = uvec;
fOpt_vec.tvec       = zeros(k_max, 1);
fOpt_vec.pvec       = zeros(k_max, 3);
fOpt_vec.vvec       = zeros(k_max, 1);
fOpt_vec.vvec_norm  = zeros(k_max, 1);
fOpt_vec.fvec       = zeros(k_max, 1);
fOpt_vec.cfvec      = zeros(k_max, 1);
fOpt_vec.avec       = zeros(k_max, 3);
fOpt_vec.jvec       = zeros(k_max, 3);

for k=1:k_max

    ucum = uvec(k);
    u = ucum - floor(ucum);

    if k == 1
        Curv = ctx.q_opt.get(1);
    else
        Curv = ctx.q_opt.get(ceil(ucum));
    end

    SplineCurv = ctx.q_splines.get(Curv.sp_index);

    fOpt_vec.pvec(k, :) = EvalPosition(Curv, SplineCurv, u);

    [fOpt_vec.vvec(k, :), fOpt_vec.avec(k, :), fOpt_vec.jvec(k, :)] =...
        CalcVAJ(ctx, Curv, ctx.Bl, u);

    fOpt_vec.fvec(k, :) = Curv.FeedRate*60;
    fOpt_vec.cfvec(k, :) = Curv.MaxConstantFeedRate*60;

    t = t + ctx.cfg.dt;

    fOpt_vec.tvec(k) = t;

    fOpt_vec.vvec_norm(k, :) = fOpt_vec.vvec(k, :)*60./fOpt_vec.fvec(k, :);
    fOpt_vec.avec(k, :) = abs(fOpt_vec.avec(k, :)./ctx.cfg.amax); % abs normalized
    fOpt_vec.jvec(k, :) = abs(fOpt_vec.jvec(k, :)./ctx.cfg.jmax); % abs normalized

    % max constraints respect verif
    if any(fOpt_vec.vvec_norm(k, :) > 1+tol.v_tol)
        bitset(status, 1);
    end

    if any(fOpt_vec.avec(k, :) > 1+tol.a_tol)
        bitset(status, 2);
    end

    if any(fOpt_vec.jvec(k, :) > 1+tol.j_tol)
        bitset(status, 3);
    end

    % time-optimatity verif
    condv = fOpt_vec.vvec_norm(k, :) > 1-tol.tol_opt_v;
    conda = any(fOpt_vec.avec(k, :) > 1-tol.tol_opt_a);
    condj = any(fOpt_vec.jvec(k, :) > 1-tol.tol_opt_j);

    if any([condv, conda, condj])
        t_max = t_max + ctx.cfg.dt;
        fOpt_vec.max_vec_logic(k) = 1;
    end

end

ratioTOpt = t_max / fOpt_vec.tvec(end);

if ratioTOpt < tol.TOpt_tol
    bitset(status, 4);
end

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

function plotTrajectories(ctx, fOpt_vec)
% plotTrajectories :
%
% Plot the resluting trajectory of the optimization problem.
%
% ctx       : The contex
% fOpt_vec  : A structure of the resulting trajectories
data = table(fOpt_vec.uvec, fOpt_vec.tvec, fOpt_vec.pvec, fOpt_vec.vvec,...
             fOpt_vec.avec, fOpt_vec.jvec, fOpt_vec.fvec, fOpt_vec.cfvec);

figure
subplot(2,4,[1,2,5,6])
scatter3(fOpt_vec.pvec(:, 1), fOpt_vec.pvec(:, 2), fOpt_vec.pvec(:, 3), 1,...
         fOpt_vec.vvec*60, 'o')
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

ax(1) = subplot(2,4,3);
plot(fOpt_vec.uvec, fOpt_vec.vvec*60, 'b', fOpt_vec.uvec, fOpt_vec.fvec,...
    'r', fOpt_vec.uvec, fOpt_vec.cfvec, 'm')
title('Velocity in mm/min')
xlabel('Cumulative u')
legend('norm', 'Specified Feedrate', 'Max Constant Feedrate')
grid

ax(2) = subplot(2,4,4);
plot(fOpt_vec.uvec, fOpt_vec.avec)
title('Normalized acceleration in mm/s^2')
xlabel('Cumulative u')
legend('x', 'y', 'z')
ylim([-1.2 1.2])
grid

ax(3) = subplot(2,4,7);
plot(fOpt_vec.uvec, fOpt_vec.pvec)
title('Position')
xlabel('Cumulative u')
legend('x', 'y', 'z')
grid

ax(4) = subplot(2,4,8);
plot(fOpt_vec.uvec, fOpt_vec.jvec)
title('Normalized jerk in mm/s^3')
xlabel('Cumulative u')
ylim([-1.4 1.4])
legend('x', 'y', 'z')
grid


linkaxes(ax, 'x');
xlim([fOpt_vec.uvec(1) fOpt_vec.uvec(end)])
end