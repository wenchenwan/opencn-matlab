close all;
NDiscr = int32(50);
NBreak = int32(5);
Degree = int32(4);
Bl = bspline_create_mex(0,1, Degree, NBreak);
% Bl = bspline_create_with_breakpoints(Degree, linspace(0,1,NBreak));
u = sinspace(0, 1, NDiscr);
[BasisVal] = bspline_base_eval_mex(Bl, u);

% b = [0.000000 0.000000 0.000000 0.000000 0.250000 0.500000 0.750000 1.000000 1.000000 1.000000 1.000000];
b = [0,0,0,linspace(0,1,NBreak), 1, 1, 1];

rng('default');
c = rand(NBreak + Degree - 2, 1);
h = plot(u, BasisVal*c, u, BasisVal.*c');
v = randn(NBreak + Degree - 2, 1)*1e-2;
v = zeros(NBreak + Degree - 2, 1);
v(4) = 1e-2;
for k = 1:1
    c = c + v;
    v(c<0) = -v(c<0);
    v(c>1) = -v(c>1);
    c(c<0) = 0;
    c(c>1) = 1;
    plot(u, BasisVal*c,'o-', u, BasisVal.*c');
    ylim([0 1])
    drawnow
    pause(0.1)
end
% hold on;
% for v = b
%     plot([v,v], [0,1], 'b--');
% end

bspline_destroy_mex(Bl);