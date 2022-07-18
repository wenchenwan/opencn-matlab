% computes the local Frenet frame (t, n, b) of a curve in R^n
% [t, nk, kappa] = calc_t_nk_kappa(rD1, rD2)
% where rD1 is the first derivative and rD2 the second one
function [t, nk, kappa] = calc_t_nk_kappa(rD1, rD2)
norm_rD1 = MyNorm(rD1);
norm_rD2 = MyNorm(rD2);

t = rD1 / norm_rD1;        % tangential unit vector
%
nk     = (rD2 - rD2'*rD1/(norm_rD1*norm_rD1)*rD1)/(norm_rD1*norm_rD1);      % normal unit vector
%
num = norm_rD2*norm_rD2*norm_rD1*norm_rD1 - (rD2'*rD1)*(rD2'*rD1);
if num < 0
    num = 0;
end

kappa = sqrt(num)...
        /(norm_rD1*norm_rD1*norm_rD1);  % curvature

end
    

