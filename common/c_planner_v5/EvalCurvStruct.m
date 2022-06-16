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
N   = numel( u_vec );
M   = ctx.cfg.NumberAxis;
r0D = zeros(M, N);
r1D = zeros(M, N);
r2D = zeros(M, N);
r3D = zeros(M, N);

a = CurvStruct.a_param;
b = CurvStruct.b_param;

u_vec_tilda = a * u_vec + b;

indC   = ctx.cfg.indCart;
indR   = ctx.cfg.indRot;
indTot = ctx.cfg.indTot;

switch Type
    case CurveType.Line     % Line (G01)
        [r0D, r1D, r2D, r3D] = EvalLine( CurvStruct, u_vec_tilda, indTot );
    case CurveType.Helix    % Arc of circle / helix (G02, G03)
        if( ctx.cfg.NCart > 0 )         % Only rotation
            [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC, : )] = ...
                EvalHelix( CurvStruct, u_vec_tilda, indC );
        end
        if( ctx.cfg.NRot > 0 )      % Only cartesian
            [r0D( ctx.cfg.NCart+1:end, : ), r1D( ctx.cfg.NCart+1:end, : ), r2D( ctx.cfg.NCart+1:end, : ), r3D( ctx.cfg.NCart+1:end, : )] = ...
                EvalLine( CurvStruct, u_vec_tilda, indR );
        end
    case CurveType.TransP5  % Polynomial transition
        [r0D, r1D, r2D, r3D] = EvalTransP5( CurvStruct, u_vec_tilda, M );
    case CurveType.Spline   % Spline
        [r0D, r1D, r2D, r3D] = EvalSpline( CurvStruct, u_vec_tilda, ...
                                                            ctx.q_spline );
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
