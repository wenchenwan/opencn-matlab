function [ ud, udd, uddd ] = calcUfromQ( q, qd, qdd )
% calcQfromU : Compute q( u ) based on u and its derivatives.
% Inputs : 
% q     : [ N x M ] q( u ) 
% qd    : [ N x M ] First derivative of q
% qdd   : [ N x M ] Second derivative of q
% Outputs :
% ud    : [ N x M ] First derivative of u 
% udd   : [ N x M ] Second derivative of u
% uddd  : [ N x M ] Third derivative of u
ud      = sqrt( q );
udd     = qd / 2;
uddd    = qdd / 2 .* ud;
end