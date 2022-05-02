function T = M5_TMB_sym(d2)
% M5_TMB
syms x z

T = [1, 0, 0,      x;
     0, 1, 0,      0;
     0, 0, 1, z + d2;
     0, 0, 0,      1];
end