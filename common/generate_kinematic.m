clc; clear;

R    = sym('R', [6, 1], 'real');
Rp   = sym('Rp', [6, 1], 'real');
Rpp  = sym('Rpp', [6, 1], 'real');
Rppp = sym('Rppp', [6, 1], 'real');

A    = sym('A', [6, 1], 'real');
Ap   = sym('Ap', [6, 1], 'real');
App  = sym('App', [6, 1], 'real');
Appp = sym('Appp', [6, 1], 'real');

P   = sym('P', [3, 4], 'real');
% P = [mx, tx,  px,  d1;
%      my, ty, p_y,  d2;
%      mz, tz,  pz, t_l];

%% Interface paramètre OpenCN -> mondel
% P = paramInter(P_ocn);

%% Kinematic models
world = forwardKinematicModel_Factory( A, P );
joint = backwardKinematicModel_Factory( R, P );

outputDir = "kinematics/gen_fun/";
path_mex = genpath( outputDir );
rmpath( path_mex );

if( isfolder( outputDir ) ), rmdir( outputDir, 's' ); end
mkdir( outputDir );
addpath( path_mex );

% Create function
matlabFunction(world, 'vars', {A, P}, 'file', outputDir + "kin_forward_xyzbc");
matlabFunction(joint, 'vars', {R, P}, 'file', outputDir + "kin_inverse_xyzbc");

%% Jacobian
J_ra   = simplify(jacobian(world( 1 : 3 ), A));
J_raP  = simplify(jacobian(J_ra * Ap,  A));
J_raPP = simplify(jacobian(J_raP * Ap, A) + jacobian(J_raP * App, Ap));

J_ar   = simplify(jacobian(joint( 1 : 3 ), R));
J_arP  = simplify(jacobian(J_ar * Rp,  R));
J_arPP = simplify(jacobian(J_arP * Rp, R) + jacobian(J_arP * Rpp, Rp));

speed_w = J_ra*Ap;
speed_j = J_ar*Rp;

acc_w   = J_raP*Ap + J_ra*App;
acc_j   = J_arP*Rp + J_ar*Rpp;

jerk_w  = J_raPP*Ap + 2*J_raP*App + J_ra*Appp;
jerk_j  = J_arPP*Rp + 2*J_arP*Rpp + J_ar*Rppp;

% Create function
matlabFunction(speed_w, 'vars',  {A, Ap, P}, 'file', outputDir + "/kin_forward_jacobian_xyzbc");
matlabFunction(speed_j, 'vars',  {R, Rp, P}, 'file', outputDir + "/kin_inverse_jacobian_xyzbc");

matlabFunction(acc_w,   'vars',  {A, Ap, App, P}, 'file', outputDir + "/kin_forward_jacobian_1pd_xyzbc");
matlabFunction(acc_j,   'vars',  {R, Rp, Rpp, P}, 'file', outputDir + "/kin_inverse_jacobian_1pd_xyzbc");

matlabFunction(jerk_w,  'vars',  {A, Ap, App, Appp, P}, 'file', outputDir + "/kin_forward_jacobian_2pd_xyzbc");
matlabFunction(jerk_j,  'vars',  {R, Rp, Rpp, Rppp, P}, 'file', outputDir + "/kin_inverse_jacobian_2pd_xyzbc");




