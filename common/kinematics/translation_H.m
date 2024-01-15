function [ T ] = translation_H( p ) 
%#codegen
% translation_H
% Compute an homogeneous matrix for a 3D translation based on the provided 
% position vector.
% 
% INPUTS : 
% vec   (3x1) : Vector
% 
% OUTPUTS : 
% T     (4x4) : homogeneous matrix for a 3D rotatione
%
% Author    : Hugo Grall Lucas (HGS)
% Date      : 04.10.2023
T = homogeneous_transform(eye(3,3), p);
end