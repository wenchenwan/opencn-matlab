 clc; close all;

%% Machine constants
GenerateKinematic = true;

d1 = 24.876;            % [mm]     Distance between table and the axis of rotation B
d2 = 57.501;            % [mm]     Distance between rotation axis B and Z axis reference face in zero position
t_l = 0;                % [mm]     Tool length      
mx = 0;                 % [mm]     X origin offset
my = 0;                 % [mm]     Y origin offset
mz = 0;                 % [mm]     Z origin offset
px = 0;                 % [mm]     X piece offset
py = 0;                 % [mm]     Y piece offset
pz = 0;                 % [mm]     Z piece offset
tx = 0;                 % [mm]     X tool offset
ty = 0;                 % [mm]     Y tool offset
tz = t_l-d2-d1;         % [mm]     Z tool offset (tool on the table)

l = load('r_a_and_r_r.mat');
N = 100;%length(l.r_a);

%% Kinematic model
r_ax = -80;
r_ay = -800;
r_az = 40;
r_ab = 50;
r_ac = 10;

r_ab = pi/180*r_ab;
r_ac = pi/180*r_ac;

r_a1 = [r_ax; r_ay; r_az; r_ab; r_ac];

A = 1;
fun1 = @(u)[A*sin(u); 2*A*sin(u+30); 10.5*A*sin(u+60); 4*u; 1*u];      %A*sin(phi+90); A*sin(phi+120)];
fun2 = @(u)[A*u.*u.*u; 10*A*u.*u.*u; 3.3*A*u.*u.*u; 1*u; 1*u];
fun3 = @(u)[u; u; u; u; u];
fun4 = l.r_a';
fun5 = [linspace(0, 1, N); linspace(0, 1, N); linspace(0, 1, N); linspace(0, 1, N); linspace(0, 1, N)];

u_start = 0;
u_stop = 1;
u = linspace(u_start, u_stop, N);

r_a = fun5;%(u);
r_r = zeros(size(r_a)); r_av = r_r; r_rv = r_r;

for i = 1:length(r_a)
    r_r(:, i)  = MGD(r_a,mx,my,mz,tx,ty,tz,px,py,pz,d1,d2,t_l);
    r_av(:, i) = MGI(r_r,mx,my,mz,tx,ty,tz,px,py,pz,d1,d2,t_l);
    r_rv(:, i) = MGD(r_av,mx,my,mz,tx,ty,tz,px,py,pz,d1,d2,t_l);

%     r_r(:, i)  = Fct_LinuxMGD(r_a(1, i),r_a(2, i),r_a(3, i),r_a(4, i),r_a(5, i), 0, d1);
%     r_av(:, i) = Fct_LinuxMGI(r_r(1, i),r_r(2, i),r_r(3, i),r_r(4, i),r_r(5, i), 0, d1);
%     r_rv(:, i) = Fct_LinuxMGD(r_av(1, i),r_av(2, i),r_av(3, i),r_av(4, i),r_av(5, i), 0, d1);

end

verifr_a2   = max(ErrRn(r_a, r_av))
verifr_r2   = max(ErrRn(r_r, r_rv))

figure;
plot3(r_a(1, :), r_a(2, :), r_a(3, :));
hold on
plot3(r_r(1, :), r_r(2, :), r_r(3, :));
title('r\_2 XYZ');
legend('r\_a2', 'r\_r2');
xlabel('X [mm]'); ylabel('Y [mm]'); zlabel('Z [mm]');
grid;

figure;
plot(u, r_a(4, :), u, r_a(5, :));
hold on
plot(u, r_r(4, :), u, r_r(5, :));
title('r\_2 BC');
legend('r\_a2', 'r\_r2');
xlabel('X [mm]'); ylabel('Y [mm]'); zlabel('Z [mm]');
grid;

%% Jocobian
uP     = diff(u, 1, 2)*(N-1)/(u_stop-u_start);
uPP    = diff(uP, 1, 2)*(N-1)/(u_stop-u_start)*(N-1)/(u_stop-u_start);
uPPP   = diff(uPP, 1, 2)*(N-1)/(u_stop-u_start)*(N-1)/(u_stop-u_start)*(N-1)/(u_stop-u_start);

% JE PEUX PAS FAIR CA
r_r    = r_r;
r_rP   = diff(r_r, 1, 2)*(N-1)/(u_stop-u_start);
r_rPP  = diff(r_rP, 1, 2)*(N-1)/(u_stop-u_start);
r_rPPP = diff(r_rPP, 1, 2)*(N-1)/(u_stop-u_start);

r_aP = zeros(3, length(r_rPPP)); r_aPP = r_aP; r_aPPP = r_aP; v_a = r_aP; a_a = r_aP; j_a = r_aP; 
for k = 1:length(r_rPPP)
%     J_ar   = Fct_J_ar(r_r(1, k),r_r(2, k),r_r(3, k),r_r(4, k),r_r(5, k),mx,my,mz,tx,ty,tz,px,py,pz,d1,d2,t_l);
%     J_arP  = Fct_J_arP(r_r(1, k),r_r(2, k),r_r(3, k),r_r(4, k),r_r(5, k),r_rP(1, k),r_rP(2, k),r_rP(3, k),r_rP(4, k),r_rP(5, k),mx,my,mz,tx,ty,tz,px,py,pz,d1,d2,t_l);
%     J_arPP = Fct_J_arPP(r_r(1, k),r_r(2, k),r_r(3, k),r_r(4, k),r_r(5, k),r_rP(1, k),r_rP(2, k),r_rP(3, k),r_rP(4, k),r_rP(5, k),r_rPP(1, k),r_rPP(2, k),r_rPP(3, k),r_rPP(4, k),r_rPP(5, k),mx,my,mz,tx,ty,tz,px,py,pz,d1,d2,t_l);
    
    J_ar   = Fct_LinuxJ_ar(r_r(1, k),r_r(2, k),r_r(3, k),r_r(4, k),r_r(5, k), 0, d1);
    J_arP  = Fct_LinuxJ_arP(r_r(1, k),r_r(2, k),r_r(3, k),r_r(4, k),r_r(5, k),r_rP(1, k),r_rP(2, k),r_rP(3, k),r_rP(4, k),r_rP(5, k), 0, d1);
    J_arPP = Fct_LinuxJ_arPP(r_r(1, k),r_r(2, k),r_r(3, k),r_r(4, k),r_r(5, k),r_rP(1, k),r_rP(2, k),r_rP(3, k),r_rP(4, k),r_rP(5, k),r_rPP(1, k),r_rPP(2, k),r_rPP(3, k),r_rPP(4, k),r_rPP(5, k), 0, d1);

    r_aP(:, k)   = J_ar*r_rP(:, k);
    r_aPP(:, k)  = J_arP*r_rP(:, k) + J_ar*r_rPP(:, k);
    r_aPPP(:, k) = J_arPP*r_rP(:, k) + 2*J_arP*r_rPP(:, k) + J_ar*r_rPPP(:, k);

    v_a(:, k) = r_aP(:, k)*uP(:, k);
    a_a(:, k) = r_aPP(:, k)*uP(:, k)*uP(:, k) + r_aP(:, k)*uPP(:, k);
    j_a(:, k) = r_aPPP(:, k)*uP(:, k)*uP(:, k)*uP(:, k) + 3*r_aPP(:, k)*uP(:, k)*uPP(:, k) + r_aP(:, k)*uPPP(:, k);

end

r_aPn   = diff(r_a, 1, 2)*(N-1)/(u_stop-u_start);
r_aPPn  = diff(r_aPn, 1, 2)*(N-1)/(u_stop-u_start);
r_aPPPn = diff(r_aPPn, 1, 2)*(N-1)/(u_stop-u_start);

EP   = max(ErrRn(r_aP, r_aPn(1:3, 1:end-2)))
EPP  = max(ErrRn(r_aPP, r_aPPn(1:3, 1:end-1)))
EPPP = max(ErrRn(r_aPPP, r_aPPPn(1:3, :)))

Axe = 1;

figure;
plot(u(1:end), r_a(Axe, :));
title('r\_a X');
legend('r\_a');
xlabel('u');
grid;

figure;
plot(u(1:end-3), r_aP(Axe, :));
hold on
plot(u(1:end-1), r_aPn(Axe, :));
title('r\_aP X');
legend('r\_a''', 'r\_a''n');
xlabel('u');
grid;

figure;
plot(u(1:end-3), r_aPP(Axe, :));
hold on
plot(u(1:end-2), r_aPPn(Axe, :));
title('r\_aPP X');
legend('r\_aPP2', 'r\_aPPn');
xlabel('u');
grid;

figure;
plot(u(1:end-3), r_aPPP(Axe, :));
hold on
plot(u(1:end-3), r_aPPPn(Axe, :));
title('r\_aPPP X');
legend('r\_aPPP2', 'r\_aPPPn');
xlabel('u');
grid;

% ERROR between numeric derivative and jacobian
figure;
plot(u(1:end-3), r_aP(Axe, :)-r_aPn(Axe, 1:end-2));
title('E\_aP X');
xlabel('u');
grid;

figure;
plot(u(1:end-3), r_aPP(Axe, :)-r_aPPn(Axe, 1:end-1));
title('E\_aPP X');
xlabel('u');
grid;

figure;
plot(u(1:end-3), r_aPPP(Axe, :)-r_aPPPn(Axe, :));
title('E\_aPPP X');
xlabel('u');
grid;

%% Plots
% figure;
% plot(u, r_a1(1, :));
% hold on
% plot(u(1:end-3), v_a1(1, :));
% plot(u(1:end-3), a_a1(1, :));
% plot(u(1:end-3), j_a1(1, :));
% title('Axe X')
% legend('r\_a', 'v\_a', 'a\_a', 'j\_a');
% xlabel('u');
% grid;
% 
% figure;
% plot(u, r_a1(2, :));
% hold on
% plot(u(1:end-3), v_a1(2, :));
% plot(u(1:end-3), a_a1(2, :));
% plot(u(1:end-3), j_a1(2, :));
% title('Axe Y')
% legend('r\_a', 'v\_a', 'a\_a', 'j\_a');
% xlabel('u');
% grid;
% 
% figure;
% plot(u, r_a1(3, :));
% hold on
% plot(u(1:end-3), v_a1(3, :));
% plot(u(1:end-3), a_a1(3, :));
% plot(u(1:end-3), j_a1(3, :));
% title('Axe Z')
% legend('r\_a', 'v\_a', 'a\_a', 'j\_a');
% xlabel('u');
% grid;


