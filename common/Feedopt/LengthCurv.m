function [ L ] = LengthCurv( ctx, curv, u0, u1 )
% LengthCurv : Compute the curve length between  u0 and u1.
%
% Inputs :
%   ctx     : The context of the computational chain
%   curv    : The curv to compute the length
%   u0      : The starting u0
%   u1      : The ending u1
%
% Outputs :
%   L       : The resulting length of the queue
%
if ( curv.Info.Type == CurveType.Helix ) || ...
   ( curv.Info.Type == CurveType.Line )
    [~, r1D] = EvalCurvStruct( ctx, curv, u0 );
    L        = MyNorm( r1D ) * ( u1 - u0 );
elseif ( curv.Info.Type == CurveType.Spline )
    a        = curv.a_param;
    b        = curv.b_param;
    u0_tilda = a * u0 + b;
    u1_tilda = a * u1 + b;
    spline   = ctx.q_spline.get( curv.sp_index );
    [ L ]    = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda );
elseif ( curv.Info.Type == CurveType.TransP5 )
    a        = curv.a_param;
    b        = curv.b_param;
    u0_tilda = a * u0 + b;
    u1_tilda = a * u1 + b;
    L = TransP5LengthApprox( curv, u0_tilda, u1_tilda );
else
    ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV", mfilename );
    L = 0;
end

end
