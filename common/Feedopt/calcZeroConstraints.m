function [ vNorm, atNorm ] = calcZeroConstraints( ctx, curv, isEnd )
%#codegen
% calcZeroConstraints : Compute the velocity and acceleration
% required for the continuity at zero start.
%
% Inputs :
% ctx       : The context
% Curv      : The curve
% isEnd     : (boolean) Is the end of the curve
%
% Outputs :
% vNorm     : Norm of the velocity
% atNorm    : Norm of the tangential acceleration
%
jps = curv.ConstJerk;

if( isEnd )
    k  = 0;
else
    k   = ( 6 / jps )^( 1 / 3 );
end

[ u, ud, udd, uddd ]    = constJerkU( jps, k, isEnd, true );

[ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u );

[ ~, V, A, ~ ]          = calcRVAJfromUWithoutCurv( ud, udd, uddd, r0D, ...
                          r1D, r2D, r3D );

[ vNorm, atNorm ]       = calcNormVNormAT( V, A, r1D );
end
