function [ x ] = sinspace( x0, x1, N )
% sinspace : Other type of noead distribution for a BSpline based on a
% sinus-like distribution (more points at start and end of the curve).
% 
% Note : I don't know this code (HGS).
%
% Inputs :
%   x0  :
%   x1  :
%   N   :
%
% Outputs :
%   x   : Resulting points
%

t = linspace(-1,0,N);
if coder.target('rtw')
    coder.varsize('x', [1, Inf], [0, 1]);
end
x = (cos(pi*t)*0.5 + 0.5)*(x1-x0) + x0;
end
