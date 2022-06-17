function [ vNorm, atNorm ] = calcNormVNormAT( V, A, r1D )
%#codegen
% calcNormVNormAT : Compute the norm of velocity and the norm of tangential
% acceleration.
% Inputs :
% V     : The velovity vector
% A     : The acceleration vector
% r1D   : The partial derivative of R
% Outputs :
% vNorm   : Norm of the velocity
% atNorm  : Norm of the tangential acceleration
vNorm   = mysqrt( sum( V.^2, 1 ) );
t       = r1D / MyNorm( r1D );
atNorm  = MyNorm( A.*t );
end