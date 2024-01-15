function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
%#codegen
% EvalCurvStructNoCtx : Eval curve structure and its derivatives on 
% a set of u points without any need of the context structure.
%
% Inputs : 
% cfg       : The configuration structure of the computational chain
% curv      : The curve used in the evaluation
% spline    : The required spline for the evaluation 
% u_vec     : U vectors
%
% Outputs : 
% r0D   : Matrix of points for a given set of u values
% r1D   : Matrix of points (first derivative) for a given set of u values
% r2D   : Matrix of points (second derivative) for a given set of u values
% r3D   : Matrix of points (third derivative) for a given set of u values
%
coder.inline("never");

ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );

%
Type    = curv.Info.Type;
%
N       = numel( u_vec );
M       = cfg.NumberAxis;

r0D     = zeros( M, N );
r1D = r0D; r2D = r0D; r3D = r0D;

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
        if( cfg.NCart > 0 )         % Cartesian axis
            [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC, : )] = ...
                EvalHelix( curv, u_vec_tilda, maskCart );
        end 
        if( cfg.NRot > 0 )      % Rotative axis
            [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR, : )] = ...
                EvalLine( curv, u_vec_tilda, maskRot );
        end
    case CurveType.TransP5  % Polynomial transition
        [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda, maskTot );
    case CurveType.Spline   % Spline
        [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
    otherwise
        ocn_assert( false, "Unknown Curve Type for Eval...", mfilename ); 
end

if( 1 )
    r1D = a     .* r1D;
    r2D = a^2   .* r2D;
    r3D = a^3   .* r3D;
else
    r1D = a     .* r1D;
    r2D = a     .* r2D;
    r3D = a     .* r3D;
end
