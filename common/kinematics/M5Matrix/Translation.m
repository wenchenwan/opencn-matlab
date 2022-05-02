function T = Translation(Vec)
% Rotation
% INPUT :
% vec  = 1x3 vector [x, y, z]
% OUTPUT :
% T    = 4x4 matrix of translation

T = [1, 0, 0, Vec(1);
     0, 1, 0, Vec(2);
     0, 0, 1, Vec(3);
     0, 0, 0,      1];
end