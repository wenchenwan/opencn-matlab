clc; clear;

syms mx my mz tx ty tz px p_y pz d1 d2 t_l real
syms dx dz  real% For Linux
syms x y z b c  real
syms xP yP zP bP cP  real
syms xPP yPP zPP bPP cPP  real

r_rP = [xP; yP; zP; bP; cP];
r_rPP = [xPP; yPP; zPP; bPP; cPP];

[r_r] = ForwardKinematicModel_Factory( x, y, z, b, c, mx, my, mz, tx, ty, ...
    tz, px, p_y, pz, d1, d2, t_l );
[r_a] = BackwardKinematicModel_Factory( x, y, z, b, c, mx, my, mz, tx, ty, ...
    tz, px, p_y, pz, d1, d2, t_l );
outputDir = "kinematics/gen_fun/";

if( isfolder( outputDir ) ), rmdir( outputDir, 's' ); end
mkdir( outputDir );

matlabFunction(r_a, 'vars', [x y z b c mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', outputDir + "Fct_MGI");
matlabFunction(r_r, 'vars', [x y z b c mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', outputDir + "Fct_MGD");

J_ar   = simplify(jacobian(r_a( 1 : 3 ), [x y z b c]));
J_arP  = simplify(jacobian(J_ar * r_rP,  [x, y, z, b, c]));
J_arPP = simplify(jacobian(J_arP * r_rP, [x, y, z, b, c]) + jacobian(J_arP*r_rPP, [xP, yP, zP, bP, cP]));

%% Create function
matlabFunction(J_ar,  'vars',  [x y z b c mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', outputDir + "/Fct_J_ar");
matlabFunction(J_arP, 'vars',  [x y z b c xP yP zP bP cP mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', outputDir + "/Fct_J_arP");
matlabFunction(J_arPP,'vars',  [x y z b c xP yP zP bP cP xPP yPP zPP bPP cPP mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', outputDir + "/Fct_J_arPP");

% matlabFunction(J_ar,   'vars',  [x y z b c dx dz], 'file', "dev/fct/Fct_LinuxJ_ar");
% matlabFunction(J_arP,  'vars',  [x y z b c xP yP zP bP cP dx dz], 'file', "dev/fct/Fct_LinuxJ_arP");
% matlabFunction(J_arPP, 'vars',  [x y z b c xP yP zP bP cP xPP yPP zPP bPP cPP dx dz], 'file', "dev/fct/Fct_LinuxJ_arPP");
% 




