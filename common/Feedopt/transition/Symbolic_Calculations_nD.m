%
%     This file is part of the Optimal G^2 Hermite Interpolation Software.
%
%     Copyright (C) 2017-2019 Raoul Herzog, Philippe Blanc
%                             mecatronYx group at HEIG-VD
%                             University of Applied Sciences Western Switzerland
%                             CH-1401 Yverdon-les-Bains
%                             All rights reserved.
%     Updated : summer 2022 by Quentin  PERROT      v.2.0.0 (support 6 axes)
%     Updated : summer 2023 by Hugo     GRALL LUCAS v.2.0.1 (remove old files)
%
%     This is free software; you can redistribute it and/or
%     modify it under the terms of the GNU Lesser General Public
%     License as published by the Free Software Foundation; either
%     version 3 of the License, or (at your option) any later version.
%
%     This software is distributed in the hope that it will be useful,
%     but WITHOUT ANY WARRANTY; without even the implied warranty of
%     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
%     Lesser General Public License for more details.
%
%     You should have received a copy of the GNU Lesser General Public
%     License along with this software; if not, write to the Free Software
%     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
%
%   README
%   AUTOR       :   Quentin PERROT, Hugo GRALL LUCAS 
%   DATE        :   Summer 2023
%   VERSION     :   2.0.1
%
%   1. The number of axes can be changed with the variable nAxis
%   2. The generated code are stored in dev/gen_transition and their are not
%   track in git history   
%   3. The code generation hase been tested and validated for 3 and 5 axis yet
%   4. The two functions CalAlpha1.m and CharPolyAlpha0.m are not used in the
%   our feedrate planning algorithm.
clc; clear; close all

check_wkdir();
PATH_TRANSITION_FOLDER = "Feedopt/transition/gen_transition/";
%
%% define symbolic parameters (later these parameters will have numerical values)

nAxis     = 6; % CHANGE THE NUMBER AXIS HERE
p0_vec    = sym('p0_vec',  [nAxis, 1], 'real');  % initial point
t0_vec    = sym('t0_vec',  [nAxis, 1], 'real');  % tangent vector @ initial point
nk0_vec   = sym('nk0_vec', [nAxis, 1], 'real');  % normal vector  @ initial point
p1_vec    = sym('p1_vec',  [nAxis, 1], 'real');  % final point
t1_vec    = sym('t1_vec',  [nAxis, 1], 'real');  % tangent vector @ final   point
nk1_vec   = sym('nk1_vec', [nAxis, 1], 'real');  % normal  vector @ final   point
%
%% define matrix of scaling between [mm] and [rad]

D_vec     = sym('D_vec',   [nAxis, 1], 'real');  % Scaling matrix
%
%% define 4 symbolic unknowns

syms alpha0 beta0 alpha1 beta1 real
%
%% define symbolic variable for curve parametrization

syms u real

%% Path for function saving
disp(" Generation :  part1");
path = PATH_TRANSITION_FOLDER;

if( isfolder( path ) ), rmdir( path, 's' ); end

mkdir( path );

%% define Hermite basis

h00 = simplify( (6*u^2+3*u+1)*(1-u)^3 );
h10 = simplify( (3*u^2+u)*(1-u)^3 );
h20 = simplify( (1/2)*u^2*(1-u)^3 );
h01 = simplify( u^3*(6*u^2-15*u+10) );
h11 = simplify( u^3*(-3*u^2+7*u-4) );
h21 = simplify( (1/2)*u^3*(u-1)^2 );

%% parametric polynomial curve in R^n with unknown parameters

r_0D_vec(u) = simplify( p0_vec*h00 + alpha0*t0_vec*h10 + (beta0*t0_vec + alpha0^2*nk0_vec)*h20 + ...
              p1_vec*h01 + alpha1*t1_vec*h11 + (beta1*t1_vec + alpha1^2*nk1_vec)*h21 );
%% derivatives of parametric curve

r_3D_vec(u) = simplify(  diff(r_0D_vec(u), u, 3) ); % 3rd derivative
r_4D_vec(u) = simplify( diff(r_0D_vec(u), u, 4) ); % 4th derivative
%% evaluate integral of square of norm of 3rd derivative

% D = [1, 1, 1, 1, 1];%eye(nAxis); % for tests

R3D_vec = r_3D_vec(u);
I       = simplify( int(R3D_vec'*(D_vec.*R3D_vec), u, 0, 1) ); 
matlabFunction(I, 'Vars', {alpha0, beta0, alpha1, beta1, p0_vec, t0_vec, nk0_vec,...
                           p1_vec, t1_vec, nk1_vec, D_vec}, 'file', path + "EvalCostIntegral.m");
%% formulate linear equations (17) and (18)

eq1_vec = simplify( r_3D_vec(0)'*(D_vec.*t0_vec) == 0 );
eq2_vec = simplify( r_3D_vec(1)'*(D_vec.*t1_vec) == 0 );
LinSys  = [eq1_vec; eq2_vec];

% eq1_vec1 = -D_vec.*t0_vec'*(9*nk0_vec*alpha0^2 + 36*t0_vec*alpha0 - 3*nk1_vec*alpha1^2 + 24*t1_vec*alpha1 + 60*p0_vec - 60*p1_vec + 9*beta0*t0_vec - 3*beta1*t1_vec) == 0;
% eq2_vec1 = -D_vec.*t1_vec'*(3*nk0_vec*alpha0^2 + 24*t0_vec*alpha0 - 9*nk1_vec*alpha1^2 + 36*t1_vec*alpha1 + 60*p0_vec - 60*p1_vec + 3*beta0*t0_vec - 9*beta1*t1_vec) == 0;
% LinSys_vec = [eq1_vec1; eq2_vec1];

%% formulate nonlinear equations (19) and (20)

eq3_vec = simplify(  2*alpha0*r_3D_vec(0)'*(D_vec.*nk0_vec) - r_4D_vec(0)'*(D_vec.*t0_vec) );
eq4_vec = simplify( 2*alpha1*r_3D_vec(1)'*(D_vec.*nk1_vec) - r_4D_vec(1)'*(D_vec.*t1_vec) );
%
%% solve linear part (free variables : alpha_0 and alpha_1)

S     = solve(LinSys, [beta0, beta1]);
% S_vec = solve(LinSys_vec, [beta0, beta1])
%

%
% eq3_vec_new = simplify(subs(eq3_vec, S));
eq3_vec_new = subs(eq3_vec, [beta0, beta1], [S.beta0, S.beta1] );
eq3_vec_new = simplify( eq3_vec_new );
% eq4_vec_new = simplify(subs(eq4_vec, S));
eq4_vec_new = simplify(subs(eq4_vec, [beta0, beta1], [S.beta0, S.beta1]));
%

beta0 = S.beta0;
beta1 = S.beta1;
%
matlabFunction(beta0, beta1, 'Vars', {alpha0, alpha1, p0_vec, t0_vec, nk0_vec, p1_vec, t1_vec, nk1_vec, D_vec}, ...
               'file', path + "Calc_beta0_beta1.m");  

L3  = fliplr(coeffs(eq4_vec_new, alpha0));
%
L31 = simplify(fliplr(coeffs(L3(1), alpha1)));
a1  = L31(1);
a0  = L31(2);
L32 = simplify(fliplr(coeffs(L3(2), alpha1)));
b1  = L32(1);
b0  = L32(2);
L33 = simplify(fliplr(coeffs(L3(3), alpha1)));
c3  = L33(1);
c2  = L33(2);
c1  = L33(3);
c0  = L33(4);
%
C3  = fliplr(coeffs(eq3_vec_new, alpha1));
%
C31 = simplify(fliplr(coeffs(C3(1), alpha0)));
d1 = C31(1);
d0 = C31(2);
C32 = simplify(fliplr(coeffs(C3(2), alpha0)));
e1 = C32(1);
e0 = C32(2);
C33 = simplify(fliplr(coeffs(C3(3), alpha0)));
f3  = C33(1);
f2  = C33(2);
f1  = C33(3);
f0  = C33(4);

CoefPS = [a1, a0, b1, b0, c3, c2, c1, c0, d1, d0, e1, e0, f3, f2, f1, f0];
matlabFunction(CoefPS, 'Vars', {p0_vec, t0_vec, nk0_vec, p1_vec, t1_vec, nk1_vec, D_vec},...
               'file', path + "CoefPolySys.m");  

%% degenerate case kappa0 = 0
%
clear all; 
syms a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0 alpha0 alpha1 real
%
disp(" Generation :  part2");
path = PATH_TRANSITION_FOLDER;
%
CoefPS = [a1, a0, b1, b0, c3, c2, c1, c0, d1, d0, e1, e0, f3, f2, f1, f0];
%
p1   = simplify( (b1*alpha1+b0)*alpha0 + c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0 );
p2   = simplify( d0*alpha1^2 + e0*alpha1 + f1*alpha0+f0 );
%
Fdetalpha0 = feval(symengine, 'polylib::resultant', p1, p2, alpha1);
Coeff_Poly_Alpha0 = fliplr(coeffs(Fdetalpha0, alpha0));
matlabFunction(Coeff_Poly_Alpha0, 'Vars', {CoefPS}, 'file',  path + "CharPolyAlpha0.m");  
%
Fdetalpha1 = feval(symengine, 'polylib::resultant', p1, p2, alpha0);
Coeff_Poly_Alpha1 = fliplr(coeffs(Fdetalpha1, alpha1));
matlabFunction(Coeff_Poly_Alpha1, 'Vars', {CoefPS}, 'file',  path + "CharPolyAlpha1.m");  
%
%% degenerate case kappa1 = 0
%
clear all; 
syms a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0 alpha0 alpha1 real
%
disp(" Generation :  part3");
path = PATH_TRANSITION_FOLDER;
%
CoefPS = [a1, a0, b1, b0, c3, c2, c1, c0, d1, d0, e1, e0, f3, f2, f1, f0];
%
p1   = simplify( a0*alpha0^2 + b0*alpha0 + c1*alpha1+c0 );
p2   = simplify( (e1*alpha0+e0)*alpha1 + f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0 );
%
Fdetalpha0 = feval(symengine, 'polylib::resultant', p1, p2, alpha1);
Coeff_Poly_Alpha0 = fliplr(coeffs(Fdetalpha0, alpha0));
matlabFunction(Coeff_Poly_Alpha0, 'Vars', {CoefPS}, 'file',  path + "CharPolyAlpha0.m");  
%
Fdetalpha1 = feval(symengine, 'polylib::resultant', p1, p2, alpha0);
Coeff_Poly_Alpha1 = fliplr(coeffs(Fdetalpha1, alpha1));
matlabFunction(Coeff_Poly_Alpha1, 'Vars', {CoefPS}, 'file',  path + "CharPolyAlpha1.m");  
%
%% compute resultant
%
clear all; 
syms a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0 alpha1 alpha0 real
%
disp(" Generation :  part4");
path = PATH_TRANSITION_FOLDER;
%
CoefPS = sym('CoefPS', 16, 'real');
a1 = CoefPS(1);
a0 = CoefPS(2);
b1 = CoefPS(3);
b0 = CoefPS(4);
c3 = CoefPS(5);
c2 = CoefPS(6);
c1 = CoefPS(7);
c0 = CoefPS(8);
d1 = CoefPS(9);
d0 = CoefPS(10);
e1 = CoefPS(11);
e0 = CoefPS(12);
f3 = CoefPS(13);
f2 = CoefPS(14);
f1 = CoefPS(15);
f0 = CoefPS(16);

p1   = simplify( (a1*alpha1+a0)*alpha0^2 + (b1*alpha1+b0)*alpha0 + c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0 );
p2   = simplify( (d1*alpha0+d0)*alpha1^2 + (e1*alpha0+e0)*alpha1 + f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0 );
%
Fdetalpha0 = feval(symengine, 'polylib::resultant', p1, p2, alpha1);
Coeff_Poly_Alpha0 = fliplr(coeffs(Fdetalpha0, alpha0));
matlabFunction(Coeff_Poly_Alpha0, 'Vars', {CoefPS}, 'file',  path + "CharPolyAlpha0.m");  
%
Fdetalpha1 = feval(symengine, 'polylib::resultant', p1, p2, alpha0);
Coeff_Poly_Alpha1 = fliplr(coeffs(Fdetalpha1, alpha1));
matlabFunction(Coeff_Poly_Alpha1, 'Vars', {CoefPS}, 'file',  path + "CharPolyAlpha1.m");  
%
clear; 
%
% (a1*alpha1+a0)*alpha0^2  +  (b1*alpha1+b0)*alpha0  +  c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0
% (d1*alpha0+d0)*alpha1^2  +  (e1*alpha0+e0)*alpha1  +  f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0
%%
syms a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0 alpha1 alpha0 real
CoefPS = [a1, a0, b1, b0, c3, c2, c1, c0, d1, d0, e1, e0, f3, f2, f1, f0];
%
path = PATH_TRANSITION_FOLDER;

%% out of the 2nd equation

alpha1_2 = simplify( -(1/(d1*alpha0+d0)) * ((e1*alpha0+e0)*alpha1 + f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0) );
alpha1_3 = simplify( -(1/(d1*alpha0+d0)) * ((e1*alpha0+e0)*alpha1_2 + (f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0)*alpha1) );
p1_vec   = simplify( (a1*alpha1+a0)*alpha0^2 + (b1*alpha1+b0)*alpha0 + c3*alpha1_3+c2*alpha1_2+c1*alpha1+c0 );
alpha1_s = solve(p1_vec==0, alpha1);
matlabFunction(alpha1_s, 'Vars', {alpha0, CoefPS}, 'file', path + "CalcAlpha1.m");
%% out of 1st equation

alpha0_2   = simplify( -(1/(a1*alpha1+a0)) * ((b1*alpha1+b0)*alpha0 + c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0) );
alpha0_3   = simplify( -(1/(a1*alpha1+a0)) * ((b1*alpha1+b0)*alpha0_2 + (c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0)*alpha0) );
p2        = simplify( (d1*alpha0+d0)*alpha1^2  +  (e1*alpha0+e0)*alpha1  +  f3*alpha0_3+f2*alpha0_2+f1*alpha0+f0 );
alpha0_s   = solve(p2==0, alpha0);
matlabFunction(alpha0_s, 'Vars', {alpha1, CoefPS}, 'file', path + "CalcAlpha0.m");
