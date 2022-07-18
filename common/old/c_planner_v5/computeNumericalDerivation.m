function [ v, a, j ] = computeNumericalDerivation( pos, dt )
% computeNumericalDerivation :
% 
% Inputs : 
% pos : [T x D] (T : Time steps, D : Dimension) Array of position to derive
% dt  : Time step used in the derivation
%
% Ouputs : 
% v   : [ (T-1) x D] Speed
% a   : [ (T-1) x D] Acceleration
% j   : [ (T-1) x D] Jerk

    v = diff( pos )' / dt ;
    a = diff( v' )'  / dt;
    j = diff( a' )'  / dt;
end