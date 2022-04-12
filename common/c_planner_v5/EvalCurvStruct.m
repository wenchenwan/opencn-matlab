function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
% coder.cstructname(CurvStruct, 'CurvStruct')
coder.inline("never");
if any(u_vec - 1.0 > 10*eps)
    u_vec(u_vec > 1.0) = 1.0; printMsg("Error : u_vec > 1\n");
end

if any(u_vec < 0.0)
    u_vec(u_vec < 0.0) = 0.0; printMsg("Error : u_vec < 0\n");
end

%
Type  = CurvStruct.Type;
%
N = numel(u_vec);
r0D = zeros(3, N);
r1D = zeros(3, N);
r2D = zeros(3, N);
r3D = zeros(3, N);

a=CurvStruct.a_param;
b=CurvStruct.b_param;

u_vec_tilda = a*u_vec+b;

switch Type
    case CurveType.Line % line (G01)
        [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
    case CurveType.Helix % arc of circle / helix (G02, G03)
        [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
    case CurveType.TransP5 % polynomial transition
        [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
    case CurveType.Spline % BSpline
        [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
    otherwise
        c_assert(false, 'Unknown Curve Type for Eval.\n');
end

r1D = a.*r1D;
r2D = a^2.*r2D;
r3D = a^3.*r3D;

function [] = printMsg( err_msg )
% printMsg : Print erro message according to the coder.target.
err_msg = "EvalCurvStruct : " + err_msg;
if coder.target('matlab')
    error(err_msg);
else
    fprintf(err_msg);
end
