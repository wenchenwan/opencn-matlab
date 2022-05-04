function [r0D, r1D, r2D, r3D] = EvalHelix(ctx, CurvStruct, u_vec)
% EvalHelix : Evalue the helix curv and its corresponding parametric
% derivatives. The evaluation occurs on the specified points in the u
% vector.
%
% CurvStruct    : A struct filled the parameters correspondin to a Helix
% u_vec         : A vector of specifided points for the evaluation of the
%                 curve
%
% r0D           : The evaluated helix at the specified points
% r1D           : The 1rst order parametric derivative of the curve at the
%                 specified points
% r2D           : The 2nd order parametric derivative of the curve at the
%                 specified points
% r3D           : The 3rd order parametric derivative of the curve at the
%                 specified points

if ~coder.target('MATLAB')
    coder.cinclude('common/tracy/Tracy.hpp');
    coder.inline('never')
    coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalHelix"'));
end
% Extract parameters from the struct
P0      = CurvStruct.P0;
P1      = CurvStruct.P1;
evec    = CurvStruct.evec;
theta   = CurvStruct.theta;
pitch   = CurvStruct.pitch;
NCart   = ctx.cfg.NCart;
NRot    = ctx.cfg.NRot;
nD      = NCart + NRot;

% Splitting cartesian an rotary axis
[P0_cart ,P0_rot] = SplitCartRot(ctx, P0);
[P1_cart ,P1_rot] = SplitCartRot(ctx, P1);

N       = length(u_vec);
P0P1    = P0_cart - P1_cart;

r0D = zeros(nD, N);
r1D = zeros(nD, N);
r2D = zeros(nD, N);
r3D = zeros(nD, N);

% Calculate the Helix for the cartesian axis
C           = CurvStruct.CorrectedHelixCenter;
CP0         = P0_cart - C;
phi_vec     = theta*u_vec;
EcrCP0      = cross(evec, CP0); % clockwise tangent vector
cphi        = mycos(phi_vec);
sphi        = mysin(phi_vec);
%

cphiTCP0    = CP0 * cphi;
sphiTCP0    = CP0 * sphi;
cphiTEcrCP0 = EcrCP0 * cphi;
sphiTEcrCP0 = EcrCP0 * sphi;
Sign        = sign(P0P1'*evec);
%
r0D_cart    = bsxfun(@plus, C, cphiTCP0  + sphiTEcrCP0  + ...
                   pitch/(2*pi)*evec*phi_vec);
r1D_cart    = bsxfun(@plus, -theta  *sphiTCP0  + theta  *cphiTEcrCP0, ...
                   theta * pitch/(2*pi) * evec);
r2D_cart    = -theta^2*cphiTCP0  - theta^2*sphiTEcrCP0;
r3D_cart    =  theta^3*sphiTCP0  - theta^3*cphiTEcrCP0;

% Calculate a line for rotary axis and make a warning
r0D_rot     = P1_rot.*u_vec + P0_rot.*(1-u_vec);
r1D_rot     = repmat(P1_rot - P0_rot, 1, N);
r2D_rot     = zeros(NRot, N);
r3D_rot     = zeros(NRot, N);
if( P1_rot-P0_rot )
    fprintf('WARNING : Rotary axis shouldn''t move during G02/G03\n');
end

% Merge cartesian and rotary parts
r0D = MergeCartRot(ctx, r0D_cart, r0D_rot);
r1D = MergeCartRot(ctx, r1D_cart, r1D_rot);
r2D = MergeCartRot(ctx, r2D_cart, r2D_rot);
r3D = MergeCartRot(ctx, r3D_cart, r3D_rot);














