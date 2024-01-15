% computes the local Frenet frame (t, n, b) of a curve in R^n
% [t, nk, kappa] = calc_t_nk_kappa(rD1, rD2)
% where rD1 is the first derivative and rD2 the second one
function [ t, nk, kappa ] = calc_t_nk_kappa( rD1, rD2 )
norm_rD1    = vecnorm( rD1 );
norm_rD1_2  = norm_rD1.^2;
norm_rD1_3  = norm_rD1_2 .* norm_rD1;
norm_rD2    = vecnorm( rD2 );
norm_rD2_2  = norm_rD2.^2;
dot_rD1_rD2 = dot( rD2, rD1 );

% tangential unit vector
t = rD1 / norm_rD1;        
% Normal unit vector
nk          = ( rD2 - rD1 .* dot_rD1_rD2 ./ norm_rD1_2 ) ./ norm_rD1_2;
% Curvature
num         = norm_rD2_2 .* norm_rD1_2 - dot_rD1_rD2.^2;

num( num < 0 ) = 0;
kappa       = mysqrt( num ) ./ norm_rD1_3;

end
    

