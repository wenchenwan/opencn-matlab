function [ n ] = MyNorm( x )
% MyNorm : My implementation of the norm computation.
%
% Inputs :
%   x   : The input vector.
%
% Outputs :
%   n   : The resulting norm.
%
coder.inline( 'always' );
n = mysqrt( sum( x.^2 ) );
end

