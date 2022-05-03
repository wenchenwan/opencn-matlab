function T = Translation_sym
% Translation
% OUTPUT :
% T    = 4x4 matrix of translation

syms x y z

T = [1, 0, 0, x;
     0, 1, 0, y;
     0, 0, 1, z;
     0, 0, 0, 1];
end