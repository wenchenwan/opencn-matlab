function [ y ] = mysqrt( x )
% mysqrt : Custom implementation of the sqrt method.
%
% Inputs :
%   x : Value used for the computation
% Outputs : 
%   y : Resulting value
%
ocn_assert( isreal( x ), "x should be real...", mfilename );
ocn_assert( x >= 0, "x should not be negative...", mfilename );
y = sqrt(x);
end
