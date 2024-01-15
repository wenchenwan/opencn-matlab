function [ a ] = mypolyder( u )
% mypolyder : Compute the derivative of input polynom of coefficient u.
%
% Inputs :
%   u : Coefficients of the polynom vector.
% Outputs :
%   a : Coefficient of the derivative of the polynom vector.
%
% u  = u( : ).'; 
[ nD, nu ] = size( u );
if nu < 2
    a = 0; 
else
    a = u( :, 1 : nu-1 ) .* repmat( nu-1 :-1 : 1 , nD, 1 ); 
end

