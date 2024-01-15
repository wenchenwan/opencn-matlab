function [ y ] = mycos( x )
% mycos : My implementation of cosinus.
%
% Inputs :
%   x   : The value use to evaluate the cosinus.
% Outputs :
%   y   : The resulting value of the cosinus.
%
global cos_calls
y = cos( x );
cos_calls = cos_calls + 1;
end
