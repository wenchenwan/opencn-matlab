function [ R2D ] = rot2D( angle ) %#codegen
% rot2D
% Compute the 2D rotation matrice based on the provided angle in radian.
% 
% INPUT : 
% angle (1x1) : Rotation angle in radian
% 
% OUTPUT : 
% R2D   (2x2) : 2D Rotation matrice
%
% Author    : Hugo Grall Lucas (HGS)
% Date      : 04.10.2023
R2D = [ cos(angle), -sin(angle);  
        sin(angle),  cos(angle) ];
end