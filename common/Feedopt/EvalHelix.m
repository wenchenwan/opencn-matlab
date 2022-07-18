function [r0D, r1D, r2D, r3D] = EvalHelix( CurvStruct, u_vec, maskCart )
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
P0      = CurvStruct.R0( maskCart );
P1      = CurvStruct.R1( maskCart );
evec    = CurvStruct.evec;
theta   = CurvStruct.theta;
pitch   = CurvStruct.pitch;

P0P1    = P0 - P1;

%
C           = CurvStruct.CorrectedHelixCenter;
CP0         = P0 - C;
phi_vec     = theta * u_vec;
EcrCP0      = cross( evec, CP0 ); % clockwise tangent vector
cphi        = mycos( phi_vec );
sphi        = mysin( phi_vec );
%

cphiTCP0    = CP0 * cphi;
sphiTCP0    = CP0 * sphi;
cphiTEcrCP0 = EcrCP0 * cphi;
sphiTEcrCP0 = EcrCP0 * sphi;
Sign        = sign( P0P1'*evec );
%
r0D       = bsxfun(@plus, C, cphiTCP0  + sphiTEcrCP0  + ...
                   pitch/(2*pi)*evec*phi_vec);
r1D       = bsxfun(@plus, -theta  *sphiTCP0  + theta  *cphiTEcrCP0, ...
                   theta * pitch/(2*pi) * evec);
r2D       = -theta^2*cphiTCP0  - theta^2*sphiTEcrCP0;
r3D       =  theta^3*sphiTCP0  - theta^3*cphiTEcrCP0;
