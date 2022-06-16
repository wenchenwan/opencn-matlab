 clc; clear; close all;

%% Machine constants
GenerateKinematic = true;

d1  = 24.876;               % [mm]     Distance between table and the axis of rotation B
d2  = 57.501;               % [mm]     Distance between rotation axis B and Z axis reference face in zero position
t_l = 0*rand(1);            % [mm]     Tool length      
mx  = 0*rand(1);            % [mm]     X origin offset
my  = 0*rand(1);            % [mm]     Y origin offset
mz  = 0*rand(1);            % [mm]     Z origin offset
px  = 0*rand(1);            % [mm]     X piece offset
py  = 0*rand(1);            % [mm]     Y piece offset
pz  = 0*rand(1);            % [mm]     Z piece offset
tx  = 0*rand(1);            % [mm]     X tool offset
ty  = 0*rand(1);            % [mm]     Y tool offset
tz  = 0*rand(1)+t_l-d2-d1;  % [mm]     Z tool offset (tool on the table)

P = [mx, tx, px,  d1;
     my, ty, py,  d2;
     mz, tz, pz, t_l];

N = 100;

%% Coherence verification
u_start = 0;
u_stop = 1;
u = linspace(u_start, u_stop, N);

A = 1;
x = 10; y = 0; z = 0; a = 0; b = 0*pi/180; c = 90*pi/180;
fun0 = [x; y; z; a; b; c];
fun1 = @(u)[A*sin(u); 2*A*sin(u+30); 10.5*A*sin(u+60); 0*u; 4*u; 1*u];
fun2 = @(u)[A*u.*u.*u; 10*A*u.*u.*u; 3.3*A*u.*u.*u; 0*u; 1*u; 1*u];
fun3 = @(u)[u; u; u; 0*u; u; u];
fun4 = [linspace(0, 1, N); linspace(0, 1, N); linspace(0, 1, N); linspace(0, 0, N); linspace(0, 1, N); linspace(0, 1, N)];
fun5 = @(u)50*[rand(size(u)); rand(size(u)); rand(size(u)); 0*rand(size(u)); rand(size(u)); rand(size(u))];

r_a = fun5(u);
r_r = zeros(size(r_a)); r_av = r_r; r_rv = r_r;

[~, l] = size(r_a);
for i = 1:l
    r_r(:, i)  = MGD(r_a(:, i), P)';
    r_av(:, i) = MGI(r_r(:, i), P)';
    r_rv(:, i) = MGD(r_av(:, i), P)';
end

verifr_a2   = max(ErrRn(r_a, r_av))
verifr_r2   = max(ErrRn(r_r, r_rv))

% figure;
% plot3(r_a(1, :), r_a(2, :), r_a(3, :));
% hold on
% plot3(r_r(1, :), r_r(2, :), r_r(3, :));
% title('r\_2 XYZ');
% legend('r\_a2', 'r\_r2');
% xlabel('X [mm]'); ylabel('Y [mm]'); zlabel('Z [mm]');
% grid;
% 
% figure;
% plot(u, r_a(4, :), u, r_a(5, :));
% hold on
% plot(u, r_r(4, :), u, r_r(5, :));
% title('r\_2 BC');
% legend('r\_a2', 'r\_r2');
% xlabel('X [mm]'); ylabel('Y [mm]'); zlabel('Z [mm]');
% grid;

%% Model verifications
csv = readmatrix('dev/test_TM/data_TwinCAT/G01_X50_B90_C90_ON_T0.csv');
[t_csv, r_a_csv, r_r_csv] = CleanDataRaRr(csv);

r_a = zeros(size(r_a_csv));
r_r = zeros(size(r_r_csv));
for i = 1:length(t_csv)
    r_a(i, :) = MGI(r_r_csv(i, :)', P);
    r_r(i, :) = MGD(r_a_csv(i, :)', P);
end

err_r_a = ErrRn(r_a_csv, r_a);
mean(err_r_a)
max(err_r_a);

err_r_r = ErrRn(r_r_csv, r_r);
mean(err_r_r)
max(err_r_r);

figure;
plot3(r_a_csv(:, 1), r_a_csv(:, 2), r_a_csv(:, 3));
title('Parcours des variables articulaires cartésiennes de TwinCAT');
xlabel('X [mm]'); ylabel('Y [mm]'); zlabel('Z [mm]');
grid;

figure;
plot(180/pi*r_a_csv(:, 5), 180/pi*r_a_csv(:, 6));
title('Parcours des variables articulaires rotatives de TwinCAT');
xlabel('B [degré]'); ylabel('C [degré]');
grid;

figure;
plot3(r_r_csv(:, 1), r_r_csv(:, 2), r_r_csv(:, 3));
title('Positions cartésiennes de l''outil dans le référentiel de la pièce de TwinCAT');
xlabel('X [mm]'); ylabel('Y [mm]'); zlabel('Z [mm]');
grid;

figure;
plot(180/pi*r_r_csv(:, 5), 180/pi*r_r_csv(:, 6));
title('Orientation de l''outil dans le référentiel de la pièce de TwinCAT');
xlabel('B [degré]'); ylabel('C [degré]');
grid;

axe = 1;
figure;
plot(t_csv, r_a_csv(:, axe), t_csv, r_a(:, axe));
title('r\_ax');
legend('TwinCAT', 'Model calculé');
xlabel('t [s]'); ylabel('position [mm]');
grid;

err_r_ax = ErrRn(r_a_csv(:, axe), r_a(:, axe));
mean_err_r_ax = mean(err_r_ax)

figure;
plot(t_csv, err_r_ax);
hold on
plot([t_csv(1), t_csv(end)], [mean_err_r_ax, mean_err_r_ax], 'LineWidth', 2);
title('Norme de l''erreur entre le signal de la variable articulaire de TwinCAT et celui de modèle cinématique');
xlabel('t [s]'); ylabel('erreur [mm]');
grid;

Y = fft(err_r_ax');
L = length(err_r_ax);
Fs = 1/(t_csv(2)-t_csv(1));

P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);

f = Fs*(0:(L/2))/L;
figure;
plot(f,P1) 
title('Single-Sided Amplitude Spectrum of X(t)')
xlabel('f (Hz)')
ylabel('|P1(f)|')

err_r_ax = ErrRn(r_a_csv(:, 1), r_a(:, 1));
err_r_ay = ErrRn(r_a_csv(:, 2), r_a(:, 2));
err_r_az = ErrRn(r_a_csv(:, 3), r_a(:, 3));
e = sqrt(err_r_ax.*err_r_ax + err_r_ay.*err_r_ay + err_r_az.*err_r_az);
mean_e = mean(e)

figure;
plot(t_csv, r_r_csv(:, axe), t_csv, r_r(:, axe));
title('r\_rx');
legend('TwinCAT', 'Model calculé');
xlabel('t [s]'); ylabel('position [mm]');
grid;

err_r_rx = ErrRn(r_r_csv(:, axe), r_r(:, axe));
mean_err_r_rx = mean(err_r_rx);

figure;
plot(t_csv, err_r_rx);
hold on
plot([t_csv(1), t_csv(end)], [mean_err_r_rx, mean_err_r_rx], 'LineWidth', 2);
title('Norme de l''erreur entre le signal de la variable articulaire de TwinCAT et celui de modèle cinématique');
xlabel('t [s]'); ylabel('erreur [mm]');
grid;

figure;
plot(err_r_a);
title('Norme de l''erreur dans R5');
xlabel('ech [-]'); ylabel('erreur [-]');
grid;

figure;
plot(err_r_r);
title('Norme de l''erreur dans R5');
xlabel('ech [-]'); ylabel('erreur [-]');
grid;

figure;
plot3(r_a_csv(:, 1), r_a_csv(:, 2), r_a_csv(:, 3));
hold on
plot3(r_a(:, 1), r_a(:, 2), r_a(:, 3));
title('Parcours des variables articulaires cartésiennes');
legend('TwinCAT', 'Model calculé', 'Location','best');
xlabel('X [mm]'); ylabel('Y [mm]'); zlabel('Z [mm]');
grid;

err_r_axyz = ErrRn(r_a_csv(:, 1:3), r_a(:, 1:3));
mean_err_r_axyz = mean(err_r_axyz)

max(err_r_axyz)
% DiscreteFrechetDist(r_a_csv(:, 1:3), r_a(:, 1:3))

figure;
plot(t_csv, err_r_axyz);
hold on
plot([t_csv(1), t_csv(end)], [mean_err_r_axyz, mean_err_r_axyz], 'LineWidth', 2);
title('Norme de l''erreur dans R3 pour la partie cartésienne');
xlabel('t [s]'); ylabel('erreur [mm]');
grid;

figure;
plot(180/pi*r_a_csv(:, 5), 180/pi*r_a_csv(:, 6));
hold on
plot(180/pi*r_a(:, 5), 180/pi*r_a(:, 6));
title('Parcours des variables articulaires rotatives');
legend('TwinCAT', 'Model calculé');
xlabel('B [degré]'); ylabel('C [degré]');
grid;

err_r_abc = ErrRn(r_a_csv(:, 5:6), r_a(:, 5:6));
mean_err_r_abc = mean(err_r_abc);

figure;
plot(t_csv, err_r_abc);
hold on
plot([t_csv(1), t_csv(end)], [mean_err_r_abc, mean_err_r_abc], 'LineWidth', 2);
title('Norme de l''erreur dans R2 pour la partie rotative');
xlabel('t [s]'); ylabel('erreur [rad]');
grid;

figure;
plot3(r_r_csv(:, 1), r_r_csv(:, 2), r_r_csv(:, 3));
hold on 
plot3(r_r(:, 1), r_r(:, 2), r_r(:, 3));
title('Positions cartésiennes de l''outil dans le référentiel de la pièce de TwinCAT');
legend('TwinCAT', 'Model calculé', 'Location','northeast');
xlabel('X [mm]'); ylabel('Y [mm]'); zlabel('Z [mm]');
grid;

err_r_rxyz = ErrRn(r_r_csv(:, 1:3), r_r(:, 1:3));
mean_err_r_rxyz = mean(err_r_rxyz)

figure;
plot(t_csv, err_r_rxyz);
hold on
plot([t_csv(1), t_csv(end)], [mean_err_r_rxyz, mean_err_r_rxyz], 'LineWidth', 2);
title('Norme de l''erreur dans R3 pour la partie cartésienne');
xlabel('t [s]'); ylabel('erreur [rad]');
grid;

figure;
plot(180/pi*r_r_csv(:, 5), 180/pi*r_r_csv(:, 6));
hold on
plot(180/pi*r_r(:, 5), 180/pi*r_r(:, 6));
title('Orientation de l''outil dans le référentiel de la pièce de TwinCAT');
legend('TwinCAT', 'Model calculé', 'Location','northwest');
xlabel('B [degré]'); ylabel('C [degré]');
grid;

err_r_rbc = ErrRn(r_a_csv(:, 5:6), r_a(:, 5:6));
mean_err_r_rbc = mean(err_r_rbc);

figure;
plot(t_csv, err_r_rbc);
hold on
plot([t_csv(1), t_csv(end)], [mean_err_r_rbc, mean_err_r_rbc], 'LineWidth', 2);
title('Norme de l''erreur dans R2 pour la partie rotative');
xlabel('t [s]'); ylabel('erreur [rad]');
grid;


