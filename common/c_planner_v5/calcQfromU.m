function [ q, qd, qdd ] = calcQfromU( ud, udd, uddd )
% calcQfromU : Compute q( u ) based on u and its derivatives.
% Inputs : 
% ud    : [ N x M ] First derivative of u 
% udd   : [ N x M ] Second derivative of u
% uddd  : [ N x M ] Third derivative of u
% Outputs :
% q     : [ N x M ] q( u ) 
% qd    : [ N x M ] First derivative of q
% qdd   : [ N x M ] Second derivative of q

q   = ud .^2;
qd  = 2 * udd;
qdd = 2 * uddd ./ ud;
end