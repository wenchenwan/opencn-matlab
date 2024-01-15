function [ T ] = homogeneous_transform( R, p ) 
%#codegen
% homogeneous_transform
% Compute the Homogeneous matrices from a Rotation matrice and position
% vector.
% 
% INPUTS : 
% R     (3x3) : Rotation matrice
% p     (3x1) : Position vector
% 
% OUTPUTS : 
% T     (4x4) : Homogeneous transformation
%
% Author    : Hugo Grall Lucas (HGS)
% Date      : 04.10.2023
if( isrow(p) ), p = p'; end

T = [ R, p ; zeros( 1, 3 ), 1 ];
end