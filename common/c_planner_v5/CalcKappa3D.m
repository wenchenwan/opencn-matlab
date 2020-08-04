% compute the arc length s, cumulated u, and curvature kappa for a piecewise defined 3D curve
% [s_vec, utot_vec, kappa_vec] = CalcKappa3D(ctx, CurvStructs, u_vec)
% u_vec is supposed to be an equidistant grid
function [s_vec, utot_vec, kappa_vec] = CalcKappa3D(ctx, CurvStructs, u_vec)
%
N        = length(CurvStructs);
M        = length(u_vec);
delta_u  = u_vec(2)-u_vec(1);     % equidistant grid
utot_vec = reshape((1:N) + u_vec', 1, N*M); % using implicit expansion
%
kappa_vec = zeros(N, M);   % preallocation
s_vec     = zeros(N, M);   % preallocation
%
for k = 1:N
    [~, r1D, r2D, ~] = EvalCurvStruct(ctx, CurvStructs(k), u_vec);
    %
    r1Dnorm         = sqrt(sum(r1D.^2));
    CrossProd       = [r1D(2, :).*r2D(3, :) - r1D(3, :).*r2D(2, :);
        r1D(3, :).*r2D(1, :) - r1D(1, :).*r2D(3, :);
        r1D(1, :).*r2D(2, :) - r1D(2, :).*r2D(1, :)];
    CrossProdNorm   = sqrt(sum(CrossProd.^2));
    kappa_vec(k, :) = CrossProdNorm ./ r1Dnorm.^3;
    s_vec(k, :)     = cumsum(r1Dnorm)*delta_u; % integral approximated with sum of rectangles
end
%
kappa_vec = reshape(kappa_vec', 1, N*M);
s_vec     = s_vec + cumsum([0; s_vec(1:end-1, end)]); % cumulate arc length
s_vec     = reshape(s_vec', 1, N*M);
