function [r_a] = BackwardKinematicModel_Factory()
% BackwardKinematicModel_Factory
%
% Variable :         unit : size : description
% OUTPUT 
% Fct_MGI  :                     : Function for the Backward Kinematic Model
% r_a   : [mm and rad] :  1x5 : 

% symbolic variables
syms x y z b c mx my mz tx ty tz px p_y pz d1 d2 t_l

BW_RTCP_sym = simplify(Translation([0, 0, t_l]) * M5_T0M(mx, my, mz+d1) * subs(M5_TMC_sym(d1), y, 0)  * M5_TCP(px, -p_y, pz) * inv(subs(M5_TMC_sym(d1), [b, c], [0, 0])) * M5_TMB_sym(d2) * M5_TBO(t_l) * Translation([tx, ty, tz]));
% BW_RTCP_sym
% Output vector assignation
r_a(1) = BW_RTCP_sym(1, 4)';
r_a(2) = -BW_RTCP_sym(2, 4)';
r_a(3) = BW_RTCP_sym(3, 4)';
r_a(4) = b';
r_a(5) = c';

matlabFunction(r_a, 'vars', [x y z b c mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', "kinematics/MGI");

end