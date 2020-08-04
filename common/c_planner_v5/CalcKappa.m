% compute the curvature and arc length
% [s_vec, kappa] = CalcKappa(r1D, r2D, u_vec)
% u_vec is supposed to be an equidistant grid
function [s_vec, kappa] = CalcKappa(r1D, r2D, u_vec)
kappa = zeros(size(u_vec));
s_vec = zeros(size(u_vec));
%
if (norm(r1D(3, :)) == 0) && (norm(r2D(3, :)) == 0)  % signed curvature 2D
    for k = 1:length(u_vec)
        kappa(k) = (r1D(1, k)*r2D(2, k) - r1D(2, k)*r2D(1, k)) / norm(r1D(:, k))^3;
        s_vec(k) = norm(r1D(:, k));
    end
else                                             % unsigned curvature 3D
    for k = 1:length(u_vec)
        kappa(k) = norm(cross(r1D(:, k), r2D(:, k))) / norm(r1D(:, k))^3;
        s_vec(k) = norm(r1D(:, k));
    end
end
s_vec = cumsum(s_vec)*(u_vec(2)-u_vec(1));

