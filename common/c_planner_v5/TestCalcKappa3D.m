clc; close all; clear;
%
vmax   = 10; % max feedrate in [mm/s]
%

trafo = false; % TRAFO flag disable 
HSC = false;
Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

Curv1 = ConstrLineStruct(trafo, HSC, Poff, Aoff, Uoff, ...
                               Doff, [-1;0;0], [0;0;0], A0, A1, U0, ...
                               U1, vmax, ZSpdMode.NN);

Curv2 = ConstrHelixStruct(trafo, HSC, Poff, Aoff, Uoff, Doff,...
                            [0;0;0], [0;1;0], A0, A1, U0, U1, [0;0;1], ...
                            0, [0;0;0], pi, 0, vmax, ZSpdMode.NN);

Curv3 = ConstrLineStruct(trafo, HSC, Poff, Aoff, Uoff, ...
                               Doff, [0;1;0], [-1;1;0], A0, A1, U0, ...
                               U1, vmax, ZSpdMode.NN);

CurvStructs = [Curv1, Curv2, Curv3];
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
