function plotTrajectories(ctx, res_struct)
% plotTrajectories :
%
% Plot the resluting trajectory of the optimization problem.
%
% ctx       : The context
% fOpt_vec  : A structure of the resulting trajectories
axisNameGen = {"x", "y", "z", "a", "b", "c"};
axisUnitGen = {"mm", "mm", "mm", "rad", "rad", "rad"};
axisName    = axisNameGen(1, ctx.cfg.maskTot);
axisUnit    = axisUnitGen(1, ctx.cfg.maskTot);

data = table(res_struct.uvec, res_struct.tvec, res_struct.pvec, res_struct.vvec,...
    res_struct.avec, res_struct.jvec, res_struct.fvec, res_struct.cfvec);

ind3D       = [ 1 15 ];
ind2D       = [ 4 12 ];

figure
subplot(6,6,ind3D)
scatter3(res_struct.pvec(:, 1), res_struct.pvec(:, 2), res_struct.pvec(:, 3), 1,...
    res_struct.vvec, 'o')
colormap jet
set(gca, 'Projection','orthographic')
% axis vis3d
% equal
xlabel('x mm');
ylabel('y mm');
zlabel('z mm');
title( "Joint Space" );
colorbar

subplot(6,6,18 + ind3D)
scatter3(res_struct.rpiece(:, 1), res_struct.rpiece(:, 2), ...
    res_struct.rpiece(:, 3), 1, res_struct.vvec, 'o')
colormap jet
set(gca, 'Projection','orthographic')
% axis vis3d
% equal
xlabel('x mm');
ylabel('y mm');
zlabel('z mm');
title( "Piece Space" );
colorbar

dcm_obj = datacursormode(gcf);
set(dcm_obj,'UpdateFcn',{@myupdatefcn,ctx, data})

ax(1) = subplot(6, 6, ind2D);

plot(res_struct.uvec, res_struct.vvec, 'b', res_struct.uvec, ...
    res_struct.cfvec, 'r');

title('Velocity in mm/min')
% xlabel('Cumulative u')
legend('norm', 'Specified Feedrate')
grid

ax(2) = subplot(6, 6, 12 + ind2D);

plot(res_struct.uvec, res_struct.avec);

title('Normalized acceleration')

% xlabel('Cumulative u');
legend( axisName{ : } );
ylim([-1.2 1.2])
grid

ax(3) = subplot(6, 6, 2 * 12 + ind2D);

plot(res_struct.uvec, res_struct.jvec);

title('Normalized jerk')
xlabel('Cumulative u')
ylim([-1.4 1.4])
legend(axisName{ : });
grid


linkaxes(ax, 'x');
xlim([res_struct.uvec(1) res_struct.uvec(end)])
end