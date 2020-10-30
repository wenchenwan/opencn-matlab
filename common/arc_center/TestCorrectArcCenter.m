clc; clear; close all;
%
P0 = [2; 3];
P1 = [1; 5];
C  = [3; 6];
[R, Cprim] = CorrectArcCenter(P0, P1, C);
% 
format long
norm(P0 - Cprim)
norm(P1 - Cprim)
%
phi = 0:pi/100:2*pi;
x   = Cprim(1) + R*sin(phi);
y   = Cprim(2) + R*cos(phi);
%
plot(P0(1), P0(2), 'bx', ...
     P1(1), P1(2), 'rx', ...
     Cprim(1), Cprim(2), 'go', ...
     x, y, 'k--');
 axis('equal');