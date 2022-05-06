function T = M5_TMB_sym(x, z, d2)
% M5_TMB

T = [1, 0, 0,      x;
     0, 1, 0,      0;
     0, 0, 1, z + d2;
     0, 0, 0,      1];
end