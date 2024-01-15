function [ r_0D, r_1D, r_2D, r_3D ] = EvalTransP5( CurvStruct, u_vec, ...
                                      maskTot )
%#codegen
% EvalTransP5 : Eval the 5th order polynom used to describe the transition.
%
% Inputs :
% CurvStruct    : A curve structure used for the evaluation of the polynom
% u_vec         : A vector of u values
% maskTot       : A mask with all the index of interest
%
% Outputs :
% r0D   : Matrix of points for a given set of u values
% r1D   : Matrix of points (first derivative) for a given set of u values
% r2D   : Matrix of points (second derivative) for a given set of u values
% r3D   : Matrix of points (third derivative) for a given set of u values
%
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
% 
r_0D = D0( maskTot, : );
r_1D = D1( maskTot, : );
r_2D = D2( maskTot, : );
r_3D = D3( maskTot, : );
