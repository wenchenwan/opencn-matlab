function plotTrajectories(ctx, res_struct)
% plotTrajectories :
%
% Plot the resluting trajectory of the optimization problem.
%
% ctx       : The context
% fOpt_vec  : A structure of the resulting trajectories
PLOT_DIFF = false;

axisNameGen = {"x", "y", "z", "a", "b", "c"};
axisUnitGen = {"mm", "mm", "mm", "rad", "rad", "rad"};
axisName    = axisNameGen(1, ctx.cfg.maskTot);
axisUnit    = axisUnitGen(1, ctx.cfg.maskTot);

data = table(res_struct.uvec, res_struct.tvec, res_struct.pvec, res_struct.vvec,...
    res_struct.avec, res_struct.jvec, res_struct.fvec, res_struct.cfvec);

figure
subplot(3,3,[1,2,4,5,7,8])
scatter3(res_struct.pvec(:, 1), res_struct.pvec(:, 2), res_struct.pvec(:, 3), 1,...
    res_struct.vvec, 'o')
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
    a_diff = a_diff ./ ctx.cfg.amax( ctx.cfg.maskTot )';
    j_diff = j_diff ./ ctx.cfg.jmax( ctx.cfg.maskTot )';
    %     fOpt_vec.uvec = fOpt_vec.tvec;
end

ax(1) = subplot(3,3,3);

if( PLOT_DIFF )
    plot(res_struct.uvec(2:end), v_diff * 60, 'b.', res_struct.uvec(2:end), ...
        res_struct.cfvec(2:end), 'r');
else
    plot(res_struct.uvec, res_struct.vvec, 'b', res_struct.uvec, ...
        res_struct.cfvec, 'r');
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

title('Normalized acceleration')
xlabel('Cumulative u');
legend( axisName{ : } );
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
title('Normalized jerk')
xlabel('Cumulative u')
ylim([-1.4 1.4])
legend(axisName{ : });
grid


linkaxes(ax, 'x');
xlim([res_struct.uvec(1) res_struct.uvec(end)])
end