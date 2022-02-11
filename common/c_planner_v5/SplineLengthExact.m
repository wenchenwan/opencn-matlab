function L = SplineLengthExact(ctx, Curv, u0, u1, AbsTol, RelTol)
% numerically computes the arc length of a parametric spline
% uses Matlab build-in function based on adaptive quadrature with error
% bounds.
% This function is ONLY for debugging purposes, not intended for code generation !
% 

DEFAULT_ABS_TOL = 1e-10;     % Default absolute tolerance
DEFAULT_RES_TOL = 1e-6;      % Default relative tolerance
IND_KNOTS_MULT  = 4;         % Index used to remove multiple knots 
%                              (ONLY TRUE FOR CUBIC SPLINE)
                                    
% Define standard default parameters if not passed in function call
if( nargin < 4 )   
    RelTol = DEFAULT_RES_TOL;
elseif( nargin < 5 )
    AbsTol = DEFAULT_ABS_TOL;
end

% get the sp structure
Spline = ctx.q_splines.get(Curv.sp_index);
sp     = Spline.sp;
% Eliminate multiplicities at the end points
Knots  = sp.knots(IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1);  

% for better numerical precision Waypoints are specified
WayPoints = Knots;
WayPoints = WayPoints(WayPoints > u0);
WayPoints = WayPoints(WayPoints < u1);
L     = integral(@(u) Integrand(ctx, Curv, u), u0, u1, ...
                'Waypoints', WayPoints, 'AbsTol', AbsTol, 'RelTol', RelTol);
end

function I = Integrand(ctx, Curv, u)
Spline    = ctx.q_splines.get(Curv.sp_index);
[~, r1D]  = EvalBSplineNoCtx(Spline, u);
I         = MyNorm(r1D);
end
