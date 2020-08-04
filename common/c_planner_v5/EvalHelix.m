function [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec)
%
P0      = CurvStruct.P0;
P1      = CurvStruct.P1;
evec    = CurvStruct.evec;
theta   = CurvStruct.theta;
pitch   = CurvStruct.pitch;
N       = length(u_vec);
%
P0P1    = P1 - P0;
EcrP0P1 = cross(evec, P0P1);

r0D = zeros(3, N);
r1D = zeros(3, N);
r2D = zeros(3, N);
r3D = zeros(3, N);


if ~c_assert(MyNorm(EcrP0P1) > eps, 'e cross P0P1 = 0')
    return;
end

% if pitch == 0
%     if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
%         return;
%     end
% end
%
P1proj      = P1 - (P0P1'*evec)*evec;
C           = ((P0 + P1proj) + cot(theta/2)*EcrP0P1) / 2;
CP0         = P0 - C;
phi_vec     = theta*u_vec;
EcrCP0      = cross(evec, CP0);
cphi        = cos(phi_vec);
sphi        = sin(phi_vec);
%

cphiTCP0    = repmat(cphi, 3, 1).*repmat(CP0, 1, N);
sphiTCP0    = repmat(sphi, 3, 1).*repmat(CP0, 1, N);
cphiTEcrCP0 = repmat(cphi, 3, 1).*repmat(EcrCP0, 1, N);
sphiTEcrCP0 = repmat(sphi, 3, 1).*repmat(EcrCP0, 1, N);
Sign        = sign(P0P1'*evec);
%
r0D       = repmat(C, 1, N)  + cphiTCP0  + sphiTEcrCP0  + pitch/(2*pi)*repmat(phi_vec, 3, 1).*repmat(evec, 1, N);
r1D       = -theta  *sphiTCP0  + theta  *cphiTEcrCP0  + theta * pitch/(2*pi) * repmat(evec, 1, N);
r2D       = -theta^2*cphiTCP0  - theta^2*sphiTEcrCP0;
r3D       =  theta^3*sphiTCP0  - theta^3*cphiTEcrCP0;
