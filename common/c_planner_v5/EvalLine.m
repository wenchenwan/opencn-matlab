<<<<<<< HEAD
function [r0D, r1D, r2D, r3D] = EvalLine(ctx, CurvStruct, u_vec)
% EvalLineND :
=======
function [r0D, r1D, r2D, r3D] = EvalLine( CurvStruct, u_vec, ind )
%#codegen
% EvalLine :
>>>>>>> 628ddae114382a1f0119d134e8f35f84e6768ef4
%
% Input 
% CurvStruct    : struct : Line segment
% u_vec         :    1xn : Vector for evaluation of the curv
% ind           :        : Vector of indices
%
% Output
% r0D           :   nDxn : Evaluation of the line at u\_vec points
% r1D           :   nDxn : 1rst order parametric derivative for the line at u\_vec points
% r2D           :   nDxn : 2nd order parametric derivative for the line at u\_vec points
% r3D           :   nDxn : 3rd order parametric derivative for the line at u\_vec points

if ~coder.target('MATLAB')
    coder.cinclude('common/tracy/Tracy.hpp');
    coder.inline('never')
    coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalLine"'));
end

% Calculate the numbre of dimension 
nD = ctx.cfg.NCart + ctx.cfg.NRot;

% parametrization of a straight line between P0 and P1
<<<<<<< HEAD
P0  = CurvStruct.P0;
P1  = CurvStruct.P1;
=======
P0  = CurvStruct.R0( ind );
P1  = CurvStruct.R1( ind );
% Calculate the numbre of dimension 
nD = length( ind );
>>>>>>> 628ddae114382a1f0119d134e8f35f84e6768ef4
%
r0D = P1.*u_vec + P0.*(1-u_vec);
%
N   = length( u_vec );
r1D = repmat( P1 - P0, 1, N );
%
r2D = zeros(nD, N);
r3D = zeros(nD, N);

   
    
