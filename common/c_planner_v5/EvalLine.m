function [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec)
coder.inline('never')
coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalLine"'));
%
% parametrization of a straight line between P0 and P1
P0  = CurvStruct.P0;
P1  = CurvStruct.P1;
%
r0D = [P1(1)*u_vec + P0(1)*(1-u_vec);
       P1(2)*u_vec + P0(2)*(1-u_vec);
       P1(3)*u_vec + P0(3)*(1-u_vec)];
%
N   = length(u_vec);
r1D = repmat(P1 - P0, 1, N);
%
r2D = zeros(3, N);
r3D = zeros(3, N);

   
    
