function T = M5_TMB(d2, qx, qz)
% M5_TMB
T = Translation([0, 0, d2]) * Translation([qx, 0, 0]) * Translation([0, 0, qz]);
end