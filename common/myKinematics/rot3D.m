function [ R3D ] = rot3D( vec, angle ) %#codegen
% rot3D
% Compute the 3D rotation matrice based on the provided angle in radian and 
% the unit vector.
% 
% INPUT : 
% vec   (3x1) : Unit vector of rotation
% angle (1x1) : Rotation angle in radian
% 
% OUTPUT : 
% R3D   (3x3) : 3D Rotation matrice
%
% Author    : Hugo Grall Lucas (HGS)
% Date      : 04.10.2023
vec = vec ./ norm(vec);

K = skrew( vec );

% Rodrigues' rotation formula
R3D = eye(3,3) + ( sin(angle) ) * K + ( 1 - cos(angle) ) * K * K;

end

function [ K ] = skrew( vec )
% Compute the skrew matrice
K =      [ 0         -vec(3)      vec(2);
           vec(3)     0          -vec(1);
          -vec(2)     vec(1)      0     ];

end