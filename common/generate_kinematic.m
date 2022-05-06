clc; clear;

R   = sym('R', [6, 1], 'real');
Rp  = sym('Rp', [6, 1], 'real');
Rpp = sym('RpP', [6, 1], 'real');
P   = sym('P', [3, 4], 'real');
% P = [mx, tx,  px,  d1;
%      my, ty, p_y,  d2;
%      mz, tz,  pz, t_l];


%% Kinematic models
[MGD] = forwardKinematicModel_Factory( R, P );
[MGI] = backwardKinematicModel_Factory( R, P );

outputDir = "kinematics/gen_fun/";
path_mex = genpath( outputDir );
rmpath( path_mex );

if( isfolder( outputDir ) ), rmdir( outputDir, 's' ); end
mkdir( outputDir );
addpath( path_mex );

% Create function
matlabFunction(MGD, 'vars', {R, P}, 'file', outputDir + "MGD");
matlabFunction(MGI, 'vars', {R, P}, 'file', outputDir + "MGI");

%% Jacobian
J_ar   = simplify(jacobian(MGI( 1 : 3 ), R));
J_arP  = simplify(jacobian(J_ar * Rp,  R));
J_arPP = simplify(jacobian(J_arP * Rp, R) + jacobian(J_arP*Rpp, Rp));

% Create function
matlabFunction(J_ar,  'vars',  {R, P}, 'file', outputDir + "/J_ar");
matlabFunction(J_arP, 'vars',  {R, Rp, P}, 'file', outputDir + "/J_arP");
matlabFunction(J_arPP,'vars',  {R, Rp, Rpp, P}, 'file', outputDir + "/J_arPP");




