function [ R, V, A, J ] = calcRVAJfromU( ctx, curv, u_vec, ud_vec, udd_vec, ...
                          uddd_vec )
%#codegen
% calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
% jerk for a given set of u variable.
%
% Inputs :
%   ctx     : The context 
%   Curv    : The curve struct
%   u_vec   : [ 1 x M ] The vector of u
%   ud_vec  : [ 1 x M ] The vector of first derivative of u
%   udd_vec : [ 1 x M ] The vector of second derivative of u
%   uddd_vec: [ 1 x M ] The vector of third derivative of u
%
% Outputs :
%   R       : [ N x M ] pose
%   V       : [ N x M ] velocity
%   A       : [ N x M ] acceleration
%   J       : [ N x M ] jerk
%

[ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u_vec );

ctx.kin = ctx.kin.set_tool_length( -curv.tool.offset.z );

if( curv.Info.TRAFO )
    [ r0D, r1D, r2D, r3D ] = ctx.kin.joint( r0D, r1D, r2D, r3D );
end

[ R, V, A, J ]          = calcRVAJfromUWithoutCurv( ud_vec, ...
                          udd_vec, uddd_vec, r0D, r1D, r2D, r3D );
end
