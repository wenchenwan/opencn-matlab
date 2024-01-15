function [ R, V, A, J ] = calcRVAJfromUWithoutCurv( ud_vec, ...
                          udd_vec, uddd_vec, r0D, r1D, r2D, r3D )
% calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
% jerk for a given set of u variable.
%
% Inputs :
%   ud_vec      : [ 1 x M ] The vector of first derivative of u
%   udd_vec     : [ 1 x M ] The vector of second derivative of ddu
%   uddd_vec    : [ 1 x M ] The vector of third derivative of ddu
%   r0D         : [ 1 x M ] The vector of r
%   r1D         : [ 1 x M ] The vector of first derivative of r
%   r2D         : [ 1 x M ] The vector of second derivative of r
%   r3D         : [ 1 x M ] The vector of second derivative of r
%
% Outputs :
%   R           : [ N x M ] pose
%   V           : [ N x M ] velocity
%   A           : [ N x M ] acceleration
%   J           : [ N x M ] jerk
%
R = r0D;
V = r1D .* ud_vec;
A = r2D .* ud_vec .^2 + r1D .* udd_vec;
J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D .* uddd_vec;

end
