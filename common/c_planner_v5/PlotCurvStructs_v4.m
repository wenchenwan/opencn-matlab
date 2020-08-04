function PlotCurvStructs_v4(ctx, CurvStructs0, CurvStructs)
%
Npts  = 200;
Ncrv  = length(CurvStructs);
%
r0             = EvalStructs(CurvStructs0, Npts);
[r, r1D, r2D]  = EvalStructs(CurvStructs, Npts);
%
figure(1);
%
if norm(r0(3, :)) == 0
    plot(r0(1, :), r0(2, :), 'k--', r(1, :), r(2, :), ...
          r(1, Npts:Npts:end-1), r(2, Npts:Npts:end-1), 'rx', ...
          r(1, 1), r(2, 1), 'ro');
else
    plot3(r0(1, :), r0(2, :), r0(3, :), 'k--', r(1, :), r(2, :), r(3, :), ...
          r(1, Npts:Npts:end-1), r(2, Npts:Npts:end-1), r(3, Npts:Npts:end-1), 'rx', ...
          r(1, 1), r(2, 1), r(3, 1), 'ro');
    xlabel('z');
end
grid;
axis('equal');
xlabel('x');
ylabel('y');
title('Curves');
% xl = xlim;
% xlim([xl(1)-0.1, xl(2)+0.1]);
% yl = ylim;
% ylim([yl(1)-0.1, yl(2)+0.1]);

xlim([-0.2, 1.2])
ylim([-0.2, 1.2])

%% calculate curvature
u_vec = linspace(0, Ncrv, Npts*Ncrv);
[s_vec, kappa] = CalcKappa(r1D, r2D, u_vec);
% figure
% plot(u_vec, kappa);
% grid;
% title('Curvature');
% ylabel('\kappa');
end

function [r0D, r1D, r2D] = EvalStructs(CurvStructs, Npts)
Ncrv  = length(CurvStructs);
u_vec = linspace(0, 1, Npts);
r0D   = zeros(3, Npts*Ncrv);
r1D   = zeros(3, Npts*Ncrv);
r2D   = zeros(3, Npts*Ncrv);
%
for k = 1:Ncrv
    [q0D, q1D, q2D] = EvalCurvStruct(ctx, CurvStructs(k), u_vec);
    r0D(:, 1+(k-1)*Npts:k*Npts) = q0D;
    r1D(:, 1+(k-1)*Npts:k*Npts) = q1D;
    r2D(:, 1+(k-1)*Npts:k*Npts) = q2D;
end
end



