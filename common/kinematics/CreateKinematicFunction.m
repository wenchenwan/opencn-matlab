clc; clear;

syms mx my mz tx ty tz px p_y pz d1 d2 t_l
syms dx dz % For Linux
syms x y z b c 
syms xP yP zP bP cP
syms xPP yPP zPP bPP cPP

r_rP = [xP; yP; zP; bP; cP];
r_rPP = [xPP; yPP; zPP; bPP; cPP];

MGD = ForwardKinematicModel_Factory();
MGI = BackwardKinematicModel_Factory();

% MGD = LinuxForwardKinematicModel_Factory();
% MGI = LinuxBackwardKinematicModel_Factory();

J_ar   = simplify(jacobian(MGI(1:3), [x y z b c]));
J_arP  = simplify(jacobian(J_ar*r_rP, [x, y, z, b, c]));
J_arPP = simplify(jacobian(J_arP*r_rP, [x, y, z, b, c]) + jacobian(J_arP*r_rPP, [xP, yP, zP, bP, cP]));

%% Create function
matlabFunction(J_ar, 'vars',  [x y z b c mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', "kinematics/Fct_J_ar");
matlabFunction(J_arP, 'vars',  [x y z b c xP yP zP bP cP mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', "kinematics/Fct_J_arP");
matlabFunction(J_arPP, 'vars',  [x y z b c xP yP zP bP cP xPP yPP zPP bPP cPP mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', "kinematics/Fct_J_arPP");

% matlabFunction(J_ar,   'vars',  [x y z b c dx dz], 'file', "dev/fct/Fct_LinuxJ_ar");
% matlabFunction(J_arP,  'vars',  [x y z b c xP yP zP bP cP dx dz], 'file', "dev/fct/Fct_LinuxJ_arP");
% matlabFunction(J_arPP, 'vars',  [x y z b c xP yP zP bP cP xPP yPP zPP bPP cPP dx dz], 'file', "dev/fct/Fct_LinuxJ_arPP");
% 




