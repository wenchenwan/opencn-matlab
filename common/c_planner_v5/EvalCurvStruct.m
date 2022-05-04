function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, CurvStruct, u_vec )
%#codegen
% coder.cstructname(CurvStruct, 'CurvStruct')
coder.inline("never");
if any(u_vec - 1.0 > 10*eps)
    u_vec(u_vec > 1.0) = 1.0; printMsg("Error : u_vec > 1\n");
end

if any(u_vec < 0.0)
    u_vec(u_vec < 0.0) = 0.0; printMsg("Error : u_vec < 0\n");
end

%
Type  = CurvStruct.Info.Type;
%
<<<<<<< HEAD
N = numel(u_vec);
nD = ctx.cfg.NCart + ctx.cfg.NRot;
r0D = zeros(nD, N);
r1D = zeros(nD, N);
r2D = zeros(nD, N);
r3D = zeros(nD, N);
=======
N   = numel( u_vec );
M   = ctx.cfg.NumberAxis;
r0D = zeros(M, N);
r1D = zeros(M, N);
r2D = zeros(M, N);
r3D = zeros(M, N);
>>>>>>> 628ddae114382a1f0119d134e8f35f84e6768ef4

a = CurvStruct.a_param;
b = CurvStruct.b_param;

u_vec_tilda = a * u_vec + b;

indC   = ctx.cfg.indCart;
indR   = ctx.cfg.indRot;
indTot = [ indC, indR ];

switch Type
<<<<<<< HEAD
    case CurveType.Line % line (G01)
        [r0D, r1D, r2D, r3D] = EvalLine(ctx, CurvStruct, u_vec_tilda);
    case CurveType.Helix % arc of circle / helix (G02, G03)
        [r0D, r1D, r2D, r3D] = EvalHelix(ctx, CurvStruct, u_vec_tilda);
    case CurveType.TransP5 % polynomial transition
        [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
    case CurveType.Spline % BSpline
        [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
=======
    case CurveType.Line     % Line (G01)
        [r0D, r1D, r2D, r3D] = EvalLine( CurvStruct, u_vec_tilda, indTot );
    case CurveType.Helix    % Arc of circle / helix (G02, G03)
        [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR, : )] = ...
                                EvalLine( CurvStruct, u_vec_tilda, indR );    
        [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC, : )] = ...
                                EvalHelix( CurvStruct, u_vec_tilda );
    case CurveType.TransP5  % Polynomial transition
        [r0D, r1D, r2D, r3D] = EvalTransP5( CurvStruct, u_vec_tilda );
    case CurveType.Spline   % Spline
        [r0D, r1D, r2D, r3D] = EvalSpline( CurvStruct, u_vec_tilda, ...
                                                            ctx.q_spline );
>>>>>>> 628ddae114382a1f0119d134e8f35f84e6768ef4
    otherwise
        c_assert( false, 'Unknown Curve Type for Eval.\n' );
end

r1D = a   .* r1D;
r2D = a^2 .* r2D;
r3D = a^3 .* r3D;

function [] = printMsg( err_msg )
% printMsg : Print erro message according to the coder.target.
err_msg = "EvalCurvStruct : " + err_msg;
if coder.target('matlab')
    error(err_msg);
else
    fprintf(err_msg);
end
