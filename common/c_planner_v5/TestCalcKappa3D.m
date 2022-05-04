clc; close all; clear;
%
vmax   = 10; % max feedrate in [mm/s]
%
info          = constrGcodeInfoStructType;
info.FeedRate = vmax;
info.zspdmode = ZSpdMode.NN;
A0 = zeros(3,1); A1 = A0;

Curv1 = ConstrLineStruct( trafo, HSC, Poff, Aoff, Uoff, ...
                               Doff, [-1;0;0], [0;0;0], A0, A1, U0, ...
                               U1, vmax, ZSpdMode.NN); 
delta   = 0;
evec    = [0,0,0]';
theta   = pi/2;
pitch   = 4;

Curv2 = constrHelixStruct( info, [ [0;0;0]; A0 ], [ [0;1;0]; A1 ], Cprim, delta, ...
                             [0;0;1], evec, pitch );

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
