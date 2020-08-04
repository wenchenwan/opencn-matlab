clear all; close all; clc;

cfg = FeedoptDefaultConfig;
K = 11;
t = linspace(0, 1, K);
points = [t*10; cos(t*10); sin(t*10)];

sp3D = CalcBspline_Lee_coder(cfg, points);

% sp3Dmatlab = CalcBspline_Lee_matlab(points);


u = linspace(0, 1, 100);
x = zeros(size(u));
y = zeros(size(u));
z = zeros(size(u));

xk = zeros(size(sp3D.knots));
yk = zeros(size(sp3D.knots));
zk = zeros(size(sp3D.knots));

% X = spval(sp3Dmatlab, u);

for k = 1:length(sp3D.knots)
    xk(k) = bspline_eval(sp3D.Bl, sp3D.CoeffX, sp3D.knots(k));
    yk(k) = bspline_eval(sp3D.Bl, sp3D.CoeffY, sp3D.knots(k));
    zk(k) = bspline_eval(sp3D.Bl, sp3D.CoeffZ, sp3D.knots(k));
end

for k = 1:length(u)
    x(k) = bspline_eval(sp3D.Bl, sp3D.CoeffX, u(k));
    y(k) = bspline_eval(sp3D.Bl, sp3D.CoeffY, u(k));
    z(k) = bspline_eval(sp3D.Bl, sp3D.CoeffZ, u(k));
end

subplot(1, 2, 1)
scatter3(points(1, :), points(2, :), points(3, :));
hold on
plot3(xk, yk, zk, 'x', x, y, z)
hold off

subplot(1,2,2)
plot(u, x, u, y, u, z)
legend('x', 'y', 'z')

% subplot(2,2,4)
% plot(u, X(1, :), u, X(2, :),u, X(3, :));

