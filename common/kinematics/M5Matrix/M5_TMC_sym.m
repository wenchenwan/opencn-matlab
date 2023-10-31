function T = M5_TMC_sym(y, b, c, d1)
% M5_TMC

T1 = [1, 0, 0, 0;
      0, 1, 0, y;
      0, 0, 1, 0;
      0, 0, 0, 1];

T2 = [ cos(b), 0, sin(b), 0;
            0, 1,      0, 0;
      -sin(b), 0, cos(b), 0;
            0, 0,      0, 1];

T3 = [cos(c), -sin(c), 0, 0;
      sin(c),  cos(c), 0, 0;
           0,       0, 1, 0;
           0,       0, 0, 1];

T = T1 * T2 * Translation([0, 0, -d1]) * T3;
T = simplify(T);
end