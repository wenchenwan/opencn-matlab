clear; clc;

cfg = FeedoptDefaultConfig;
ctx = InitFeedoptPlan(cfg);
test_helix_struct(ctx)


function test_helix_struct(ctx)
c = ConstrHelixStruct([1,0,0]', [0,1,1]', [0,0,1]', pi/2, 4, 100, ZSpdMode.NN);
u = linspace(0,1,100);
[R0D] = EvalCurvStruct(ctx, c, u);
% R0D = [cos(u*pi/2); sin(u*pi/2); u]; 
figure(1)
subplot(1, 2, 1)
plot(R0D(1, :), R0D(2, :));
grid
title('XY projection')
axis square

subplot(1, 2, 2)
plot(R0D(2, :), R0D(3, :));
grid
title('YZ projection')
axis square
end

function test_spline
t = linspace(0,6, 10);
x = cos(t);
y = sin(t);

tq = linspace(0,6,100);

ppx = pchip(t,x);
ppy = pchip(t,y);

xq = ppval(ppx, tq);
yq = ppval(ppy, tq);

figure(1)
plot(xq, yq, x, y, 'o')
end