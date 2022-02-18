function Test_FeedratePlanning_v4
%
clc; clear; close all;
%
% meco_binaries('cpp_splines','develop')
% import splines.*
%
%% kinematic constraints
vmax   = 1.5;              % max feedrate in [m/s]
amax   = 4.5*ones(3, 1);   % max acceleration per axis [m/s^2]
jmax   = 100*ones(3, 1);   % max jerk per axis [m/s^3]
%% geometry
Points = [-1,    0,    0,    -1,   -1;
           0,    0,    1,     0,    0;
           0,    0,    0.5, 0.5,    0];
%       
% Points = [-1,    0,    0;
%            0,    0,    1;
%            0,    0,    0.5];
%
CurvStructs0 = ConstrPolygon3D(Points, vmax);
%
%
CutOff      = 0.2;
CurvStructs = SmoothCurvStructs(CurvStructs0, CutOff, vmax);
%
%% plot curve pieces
cfg = FeedoptDefaultConfig;
ctx = InitFeedoptPlan(cfg);
PlotCurvStructs_v4(ctx, CurvStructs0, CurvStructs);
%% boundary conditions
v_0    =  0.0;
at_0   =  0.0;
v_1    =  0.1;
at_1   =  0.0;
%
%% generate BSpline basis functions and their derivatives evaluated on a grid
N      = 100;    % number of discretization points on u axis
Ndiscr = 200;    % number of constraint discretization
u_vec  = linspace(0, 1, Ndiscr);
%
d       = 3;   % degree of spline
s_end   = 1;   % normalized path coordinate
%
Bl      = BSplineBasis([0, s_end], d, N);
knots   = Bl.knots;
%
[BasisVal, BasisValD, BasisValDD, BasisIntegr] = EvalSplineBasis(knots, d, u_vec);
% save SplineBasisFunc BasisVal BasisValD BasisValDD BasisIntegr
% load SplineBasisFunc
%
N_Hor = 7; % number of curve pieces in the receding horizon
%
Coeff = RecedingHorizon(ctx, CurvStructs, amax, jmax, v_0, at_0, v_1, at_1, ...
                        BasisVal, BasisValD, BasisValDD, BasisIntegr, Bl, u_vec, N_Hor);
% 
% Coeff = FeedratePlanning_v4(ctx, CurvStructs, amax, jmax, v_0, at_0, v_1, at_1, ...
%                             BasisVal, BasisValD, BasisValDD, BasisIntegr, Bl, u_vec);
%
%% resampling
dt     = 1e-3;
u_vecr = u_vec;
%
[u_cell, t] = Calc_u_v4(Bl, Coeff, dt, CurvStructs, jmax);
T           = t(end);  % final time
%
[v_norm, a, j] = CalcVAJ_v5(CurvStructs, Bl, Coeff, u_cell);
%
%
figure;
plot(t, v_norm, [0, T], [vmax, vmax], 'r--');
grid;
axis('tight');
title('optimal ||v(t)||');
xlabel('t');
ylabel('v [m/s]');
ylim([0, max([1.1*vmax, max(max(v_norm))])]);
%
figure;
plot(t, a(1, :), 'b', t, a(2, :), 'g', t, a(3, :), 'r', ...
     [0, t(end)], [amax, amax], 'r--', [0, t(end)], [-amax, -amax], 'r--');
grid;
legend('a_x(t)', 'a_y(t)', 'a_z(t)');
axis('tight');
title('optimal a(t)');
xlabel('t');
ylabel('a [m/s^2]');
ylim([min([-1.1*amax(1), min(min(a))]), max([1.1*amax(1), max(max(a))])]);
%% active constraints 
figure;
plot(t, j(1, :), 'b', t, j(2, :), 'g', t, j(3, :), 'r', ...
     [0, t(end)], [jmax, jmax], 'r--', [0, t(end)], [-jmax, -jmax], 'r--');
grid;
axis('tight');
title('optimal j(t)');
xlabel('t');
ylabel('j [m/s^3]');
legend('j_x(t)', 'j_y(t)', 'j_z(t)');
ylim([min([-1.1*jmax(1), min(min(j))]), max([1.1*jmax(1), max(max(j))])]);
%
figure;
plot(t, v_norm/vmax, 'b', ...
     t, abs(a(1, :))/amax(1), 'g', t, abs(a(2, :))/amax(2), 'g', t, abs(a(3, :))/amax(3), 'g', ...
     t, abs(j(1, :))/jmax(1), 'r', t, abs(j(2, :))/jmax(2), 'r', t, abs(j(3, :))/jmax(3), 'r');
xlabel('t');
title('active constraints : v (blue), a (green), j (red)');
ylim([0, 1.1]);
