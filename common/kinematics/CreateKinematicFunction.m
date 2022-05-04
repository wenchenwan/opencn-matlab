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
path_mex = genpath( outputDir );
rmpath( path_mex );

if( isfolder( outputDir ) ), rmdir( outputDir, 's' ); end
mkdir( outputDir );
addpath( path_mex );

matlabFunction(r_a, 'vars', [x y z b c mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', outputDir + "MGI");
matlabFunction(r_r, 'vars', [x y z b c mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', outputDir + "MGD");

J_ar   = simplify(jacobian(r_a( 1 : 3 ), [x y z b c]));
J_arP  = simplify(jacobian(J_ar * r_rP,  [x, y, z, b, c]));
J_arPP = simplify(jacobian(J_arP * r_rP, [x, y, z, b, c]) + jacobian(J_arP*r_rPP, [xP, yP, zP, bP, cP]));

%% Create function
matlabFunction(J_ar,  'vars',  [x y z b c mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', outputDir + "/J_ar");
matlabFunction(J_arP, 'vars',  [x y z b c xP yP zP bP cP mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', outputDir + "/J_arP");
matlabFunction(J_arPP,'vars',  [x y z b c xP yP zP bP cP xPP yPP zPP bPP cPP mx my mz tx ty tz px p_y pz d1 d2 t_l], 'file', outputDir + "/J_arPP");




