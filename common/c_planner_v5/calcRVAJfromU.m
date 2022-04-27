function [ R, V, A, J ] = calcRVAJfromU( ctx, Curv, u_vec, ud_vec, udd_vec, ...
                          uddd_vec )
% calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
% jerk for a given set of u variable.
% Inputs :
%   ctx     : The context 
%   Curv    : The curve struct
%   u_vec   : [ 1 x M ] The vector of u
%   ud_vec  : [ 1 x M ] The vector of first derivative of u
%   udd_vec : [ 1 x M ] The vector of second derivative of ddu
% Outputs :
%   R   : [ N x M ] pose
%   V   : [ N x M ] velocity
%   A   : [ N x M ] acceleration
%   J   : [ N x M ] jerk
[ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, Curv, u_vec );
R = r0D;
V = r1D .* ud_vec;
A = r2D .* ud_vec .^2 + r1D .* udd_vec;
J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D .* uddd_vec;

end