function [ y ] = mysin( x )
% mysin : Custom implementation of the sinus.
%
% Inputs :
% Inputs values of the function.
% 
% Outputs : 
% Resulting values.
%
global sin_calls
y = sin( x );
sin_calls = sin_calls + 1;
end
