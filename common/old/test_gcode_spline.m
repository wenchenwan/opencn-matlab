clc; clear; close all;

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

u0 = 0;
u1 = 10;
nu = 1000;
u = linspace(u0, u1, nu);

Ntour  = 20;
Rpiece = 50;
offset_secu_z = 2;
unit_rot = 2*pi;

% code G pour un dôme en mode RTCP
f_r = @(u) [-Rpiece*cos(Ntour*2*pi/u1*u).*sin(pi/2*(1 - u/u1)); -Rpiece*sin(Ntour*2*pi/u1*u).*sin(pi/2*(1 - u/u1)); offset_secu_z+(Rpiece-offset_secu_z)*cos(pi/2*(1 - u/u1)); unit_rot/4*(1 - u/u1); Ntour*unit_rot/u1*u];
% code G pour un dôme bizarre sans RTCP
f_a = @(u) [(-d1+offset_secu_z)*sin(pi/2*(1 - u/u1)); 0*u; Rpiece+d1-d1*cos(pi/2*(1 - u/u1)); unit_rot/4*(1 - u/u1); Ntour*unit_rot/u1*u];

fr_r = f_r(u);
fr_a = f_a(u);

r_a = zeros(size(fr_r));
r_r = zeros(size(fr_a));

[~, l] = size(fr_r);
for i = 1:l
    r_a(:, i) = kin_inverse_xyzbc(fr_r(:, i), P)';
    r_r(:, i) = kin_forward_xyzbc(fr_a(:, i), P)';
end

figure;
plot(u, r_a(1,:), u, r_a(2,:), u, r_a(3,:));%, u, r_a(5,:), u, r_a(5,:));
hold on
plot(u, fr_a(1,:), u, fr_a(2,:), u, fr_a(3,:));%, u, fr_a(5,:), u, fr_a(5,:));
legend('r_aX', 'r_aY', 'r_aZ', 'fr_aX', 'fr_aY', 'fr_aZ');%, 'r_aB', 'r_aC');
grid;

figure;
plot(u, fr_r(1,:), u, fr_r(2,:), u, fr_r(3,:), u, fr_r(4,:), u, fr_r(5,:));
legend('X', 'Y', 'Z', 'B', 'C');
grid;

% figure;
% plot3(r_a(1, :), r_a(2, :), r_a(3, :));
% title('Parcours des variables articulaires cartésiennes');
% xlabel('X [mm]'); ylabel('Y [mm]'); zlabel('Z [mm]');
% grid;
% 
% figure;
% plot(180/pi*r_a(4, :), 180/pi*r_a(5, :));
% title('Parcours des variables articulaires rotatives');
% xlabel('B [degré]'); ylabel('C [degré]');
% grid;
% 
figure;
plot3(fr_r(1, :), fr_r(2, :), fr_r(3, :));
hold on
plot3(r_r(1, :), r_r(2, :), r_r(3, :));
title('Parcours de l''outil relatif');
xlabel('X [mm]'); ylabel('Y [mm]'); zlabel('Z [mm]');
grid;

figure;
plot(180/pi*fr_r(4, :), 180/pi*fr_r(5, :));
hold on
plot(180/pi*r_r(4, :), 180/pi*r_r(5, :));
title('Orientation de l''outil relatif');
xlabel('B [degré]'); ylabel('C [degré]');
grid;

figure;
plot3(fr_a(1, :), fr_a(2, :), fr_a(3, :));
hold on
plot3(r_a(1, :), r_a(2, :), r_a(3, :));
title('Parcours de l''outil relatif');
xlabel('X [mm]'); ylabel('Y [mm]'); zlabel('Z [mm]');
grid;

figure;
plot(180/pi*fr_a(4, :), 180/pi*fr_a(5, :));
hold on
plot(180/pi*r_a(4, :), 180/pi*r_a(5, :));
title('Orientation de l''outil relatif');
xlabel('B [degré]'); ylabel('C [degré]');
grid;