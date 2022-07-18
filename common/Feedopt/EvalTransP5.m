function [r_0D, r_1D, r_2D, r_3D] = EvalTransP5(CurvStruct, u_vec, nAxis)
if ~coder.target('MATLAB')
coder.cinclude('common/tracy/Tracy.hpp');
coder.inline('never')
coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalTransP5"'));
end
%
p5    = CurvStruct.CoeffP5;
p5_1D = mypolyder(p5);
p5_2D = mypolyder(p5_1D);
p5_3D = mypolyder(p5_2D);
%
D0 = mypolyval(p5,    u_vec);
D1 = mypolyval(p5_1D, u_vec);
D2 = mypolyval(p5_2D, u_vec);
D3 = mypolyval(p5_3D, u_vec);

r_0D = D0(1:nAxis, :);
r_1D = D1(1:nAxis, :);
r_2D = D2(1:nAxis, :);
r_3D = D3(1:nAxis, :);
