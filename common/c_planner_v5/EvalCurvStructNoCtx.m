function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx(CurvStruct, CurvSpline, u_vec)
% coder.cstructname(CurvStruct, 'CurvStruct')
if any(u_vec - 1.0 > 10*eps)
    if coder.target('matlab')
        error('EvalCurvStruct: u_vec > 1\n');
    else
        fprintf('EvalCurvStruct: u_vec > 1\n');
    end
    u_vec(u_vec > 1.0) = 1.0;
end

if any(u_vec < 0.0)
    fprintf('EvalCurvStruct: u_vec < 0\n');
    u_vec(u_vec < 0.0) = 0.0;
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
        [r0D, r1D, r2D, r3D] = EvalBSplineNoCtx(CurvSpline, u_vec_tilda);
    otherwise
        c_assert(false, 'Unknown Curve Type for Eval.\n');
end

r1D = a.*r1D;
r2D = a^2.*r2D;
r3D = a^3.*r3D;
