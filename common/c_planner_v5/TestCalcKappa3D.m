clc; close all; clear;
%
vmax   = 10; % max feedrate in [mm/s]
%
CurvStructs = [ConstrLineStruct([-1;0;0], [0;0;0], vmax, ZSpdMode.ZN), ...
               ConstrHelixStruct([0;0;0], [0;1;0], [0;0;1], pi, 0, vmax, ZSpdMode.NN), ...
               ConstrLineStruct([0;1;0], [-1;1;0], vmax, ZSpdMode.NZ)];
%
u_vec        = linspace(0, 1, 1000);
[s_vec, utot_vec, kappa_vec] = CalcKappa3D(ctx, CurvStructs, u_vec);

figure; 
plot(s_vec, kappa_vec);
grid;
title('curvature as a function of curve length');
xlabel('s [mm]');
ylabel('\kappa');
%
figure; 
plot(utot_vec, kappa_vec);
grid;
title('curvature as a function of cumulated u');
xlabel('u');
ylabel('\kappa');
