clc; close all; clear;
%
vmax   = 10; % max feedrate in [mm/s]
%

trafo = false;
A0 = zeros(3,1); A1 = A0; U0 = A0; U1 = A0;

CurvStructs = [ConstrLineStruct(trafo, [-1;0;0], [0;0;0], A0, A1, U0, U1, ...
                                vmax, ZSpdMode.ZN), ...
               ConstrHelixStruct(trafo, [0;0;0], [0;1;0], A0, A1, U0, U1, ...
                                 [0;0;1], pi,[0,0,0]', 0, vmax, ZSpdMode.NN), ...
               ConstrLineStruct(trafo, [0;1;0], [-1;1;0], A0, A1, U0, U1, ...
                                vmax, ZSpdMode.NZ)];
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
