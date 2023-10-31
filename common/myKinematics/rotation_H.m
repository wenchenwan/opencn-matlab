function [ T ] = rotation_H( axe, angle ) %#codegen
% rotation_H
% Compute an homogeneous matrix for a 3D rotation based on the provided 
% angle in radian and the unit vector.
% 
% INPUT : 
% vec   (3x1) : Unit vector of rotation
% angle (1x1) : Rotation angle in radian
% 
% OUTPUT : 
% T     (4x4) : homogeneous matrix for a 3D rotatione
%
% Author    : Hugo Grall Lucas (HGS)
% Date      : 04.10.2023
T = homogeneous_transform( rot3D( axe, angle ), zeros(3,1) );
end