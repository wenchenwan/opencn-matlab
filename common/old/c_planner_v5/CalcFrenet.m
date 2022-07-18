% computes the local Frenet frame (t, n, b) of a curve in R^3
% [t, n, b, kappa] = CalcFrenet(rD1, rD2)
% where rD1 is the first derivative and rD2 the second one
function [t, n, kappa] = CalcFrenet(rD1, rD2)
t = rD1 / MyNorm(rD1);        % tangential unit vector
%
if  abs(abs(t'*rD2) - MyNorm(rD2)) > eps  % regular case
    b     = cross(rD1, rD2);  
    b     = b / MyNorm(b);    % binormal unit vector
    n     = cross(b, t);      % normal unit vector
    kappa = MyNorm(cross(rD1, rD2)) / MyNorm(rD1)^3;  % curvature
else                          % special case if rD2 = 0
    n     = zeros(3,1);       % normal unit vector not defined
    kappa = 0;
end
    




