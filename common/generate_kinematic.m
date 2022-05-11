clc; clear;

R   = sym('R', [6, 1], 'real');
Rp  = sym('Rp', [6, 1], 'real');
Rpp = sym('Rpp', [6, 1], 'real');
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
TO_REPLACE  = 'TO_REPLACE';
fileName    = outputDir + "MGD" + ".m";
matlabFunction( MGD, 'vars', {R, P}, 'file', fileName, 'Comments', TO_REPLACE );
comments    = [ "Direct Kinematics (Model Geometrique Direct) : ", ...
                "R : 6 x 1 : vector of pose", "P : parameters" ];
write_comments( fileName, TO_REPLACE, comments );

matlabFunction(MGI, 'vars', {R, P}, 'file', outputDir + "MGI");

%% Jacobian
J_ar   = simplify(jacobian(MGI( 1 : 3 ), R));
J_arP  = simplify(jacobian(J_ar * Rp,  R));
J_arPP = simplify(jacobian(J_arP * Rp, R) + jacobian(J_arP*Rpp, Rp));

% Create function
matlabFunction(J_ar,  'vars',  {R, P}, 'file', outputDir + "/J_ar");
matlabFunction(J_arP, 'vars',  {R, Rp, P}, 'file', outputDir + "/J_arP");
matlabFunction(J_arPP,'vars',  {R, Rp, Rpp, P}, 'file', outputDir + "/J_arPP");


function [] = write_comments( fileName, to_replace, comments )
comments= join( comments , "\n%" );
fid     = fopen( fileName, 'r' );
f       =fread( fid, '*char' )';
fclose( fid );
f       = regexprep( f, to_replace, comments );
fid     = fopen( fileName, 'w' );
fprintf( fid, '%s', f );
fclose( fid );
end



