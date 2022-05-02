function T = M5_TMC(d1, qy, qb, qc)
% M5_TMC
T = Translation([0, qy, 0]) * Rotation('y', qb) * Translation([0, 0, -d1]) * Rotation('z', qc);
end