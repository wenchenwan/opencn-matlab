function [ vNorm, atNorm ] = calcZeroConstraints( ctx, Curv, isEnd )
%#codegen
% calcZeroStartConstraints : Compute the velocity and acceleration
% required for the continuity at zero start.
% Inputs :
% ctx   : The context
% Curv  : The curve
% isEnd : (boolean) Is the end of the curve
% Outputs :
% v_0   : Norm of the velocity
% at_0  : Norm of the tangential acceleration
jps = Curv.ConstJerk;

[ u, ud, udd, uddd ]   = constJerkU( jps, ctx.cfg.dt, isEnd, ...
    Curv.a_param, Curv.b_param );

[ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, Curv, u );

[ ~, V, A, ~ ]          = calcRVAJfromUWithoutCurv( ud, ...
    udd, uddd, r0D, r1D, r2D, r3D );

[ vNorm, atNorm ]   = calcNormVNormAT( V, A, r1D );
end