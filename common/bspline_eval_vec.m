function [x, xd, xdd, xddd] = bspline_eval_vec(Bl, coeffs, u) %#codegen

x = zeros(size(u));
xd = zeros(size(u));
xdd = zeros(size(u));
xddd = zeros(size(u));

for k = 1:length(u)
    [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
    x(k) = xk;
    xd(k) = xdk;
    xdd(k) = xddk;
    xddd(k) = xdddk;
end
end