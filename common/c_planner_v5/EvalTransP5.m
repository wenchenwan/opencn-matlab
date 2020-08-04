function [r_0D, r_1D, r_2D, r_3D] = EvalTransP5(CurvStruct, u_vec)
%
p5    = CurvStruct.CoeffP5;
p5_1D = mypolyder(p5);
p5_2D = mypolyder(p5_1D);
p5_3D = mypolyder(p5_2D);
%
r_0D = mypolyval(p5,    u_vec);
r_1D = mypolyval(p5_1D, u_vec);
r_2D = mypolyval(p5_2D, u_vec);
r_3D = mypolyval(p5_3D, u_vec);

