function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
%#codegen
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