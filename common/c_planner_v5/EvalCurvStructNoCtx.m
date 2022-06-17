function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
% 
%#codegen

coder.inline("never");
if any( u_vec - 1.0 > 10 * eps )
    u_vec( u_vec > 1.0 ) = 1.0; printMsg( "Error : u_vec > 1\n" );
end

if any( u_vec < 0.0 )
    u_vec( u_vec < 0.0 ) = 0.0; printMsg( "Error : u_vec < 0\n" );
end

%
Type  = curv.Info.Type;
%
N   = numel( u_vec );
M   = cfg.NumberAxis;

r0D = zeros( M, N );
r1D = r0D;
r2D = r0D;
r3D = r0D;

a = curv.a_param;
b = curv.b_param;

u_vec_tilda = a * u_vec + b;

indC     = cfg.indCart;
indR     = cfg.indRot;
maskTot  = cfg.maskTot;
maskRot  = cfg.maskRot;
maskCart = cfg.maskCart;

switch Type
    case CurveType.Line     % Line (G01)
        [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
    case CurveType.Helix    % Arc of circle / helix (G02, G03)
        if( cfg.NCart > 0 )         % Only rotation
            [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC, : )] = ...
                EvalHelix( curv, u_vec_tilda, maskCart );
        elseif( cfg.NRot > 0 )      % Only cartesian
            [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR, : )] = ...
                EvalLine( curv, u_vec_tilda, maskRot );
        end
    case CurveType.TransP5  % Polynomial transition
        [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda, cfg.NumberAxis );
    case CurveType.Spline   % Spline
        [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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