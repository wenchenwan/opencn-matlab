function [ wMp, pMw ] = xyzbc_tt_H( joint, params ) %#codegen
% xyzbc_tt_H
% Compute the Homogeneous matrices used to represent the kinematics of a 5 
% axis machine : xyzbc (TABLE -TABLE)
% 
% INPUT : 
% joint (5x1) : 
%       (1x1) : X - command send to the drive
%       (1x1) : Y - command send to the drive
%       (1x1) : Z - command send to the drive
%       (1x1) : B - command send to the drive
%       (1x1) : C - command send to the drive
% params(3x5) : Parameters
%       (3x1) : offM - Offset vector between the HEAD and the center of 
%               the TABLE
%       (3x1) : offT - Offset vector between the HEAD and the TOOL tip
%       (3x1) : offP - Offset vector between the center of the TABLE and 
%               the piece reference (see G54-G59)
%       (3x1) : offB - Offset vector between the rotation axe B and C
%       (3x1) : offC - Offset vector between the rotation axe B and the 
%               center of the table 
% OUTPUT : 
% wMp  (4x4) : Homogeneous transformation between WORLD frame to PIECE frame
% pMw  (4x4) : Homogeneous transformation between PIECE frame to WORLD frame
%
% Author    : Hugo Grall Lucas (HGS)
% Date      : 04.10.2023

[ ~, ~, F_OT ] = xyzbc_tt_H_intern( joint(1), joint(2), joint(3), joint(4), ...
    joint(5), params( : ,1 ), params( :, 2 ), params( :, 3 ), params( :, 4 ), ...
    params( :, 5 ) );


wMp = F_OT;
pMw = simplify(inv( wMp ));
end

function [ F_HT, F_TH, F_OT ] = xyzbc_tt_H_intern( x, y, z, b, c, offM, offT, ...
    offP, offB, offC )
% xyzbc_tt_H_intern
% See xyzbc_tt_H for more information.
%
% Author    : Hugo Grall Lucas (HGS)
% Date      : 04.10.2023

axe_x = [ 1; 0; 0 ];
axe_y = [ 0; 1; 0 ];
axe_z = [ 0; 0; 1 ];

x_tilde = x;
y_tilde = y;
z_tilde = z;

% Homogeneous transformation between the ORIGIN and the TABLE

F_OT =  rotation_H( axe_y, b ) *...
        translation_H( offB ) * ...
        rotation_H( axe_z, c ) *...
        translation_H( offC );

% Homogeneous transformation between the ORIGIN and the HEAD
F_OH =  translation_H([x_tilde, 0, 0]) * ...
        translation_H([0, y_tilde, 0]) * ...
        translation_H([0, 0, z_tilde]);

F_OT = simplify( F_OT );
F_OH = simplify( F_OH );

% Homogeneous transformation between the HEAD and the TABLE
F_HT = F_OH \ F_OT;
F_HT = simplify( F_HT );

% Homogeneous transformation between the TABLE and the HEAD
F_TH = inv(F_HT);%inv( F_OT ) * F_OH;
F_TH = simplify( F_TH );

end