function [ r0D, r1D, r2D, r3D ] = EvalCurvStruct( ctx, curv, u_vec )
%#codegen
% EvalCurvStruct : Eval curve structure and its derivatives on a set of u
% points.
%
% Inputs : 
% ctx   : The context of the computational chain
% curv  : The curve used in the evaluation
% u_vec : U vectors.
%
% Outputs : 
% r0D   : Matrix of points for a given set of u values
% r1D   : Matrix of points (first derivative) for a given set of u values
% r2D   : Matrix of points (second derivative) for a given set of u values
% r3D   : Matrix of points (third derivative) for a given set of u values
%

coder.inline("never");

persistent splineDefault;

if( isempty( splineDefault ) ), splineDefault = constrCurvStructType; end

if( curv.Info.Type == CurveType.Spline )
    ptr    = curv.sp_index;
    spline = ctx.q_spline.get( ptr );
else
    spline = splineDefault;
end

[ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline, u_vec );

end
