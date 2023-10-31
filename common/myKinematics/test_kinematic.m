%% Test the kinematics for the micro5
clear; clc; close all;

d    = [ 10, 20 , 30];

offM = [ 0, 0, -68.802 ]';
% offM = [ 0, 0, 0]';
offT = [ 0, 0, 0 ]';
offP = [ -d(1)/2, -d(2)/2, d(3) ]';
% offP = [ 0, 0, 0]';
offB = [ 0, -60.8, -6.6 ]';
% offB = [ 0, 0, 0 ]';
offC = [ 0, 0, 0 ]';

% syms( 'offM',   [3, 1], 'real' );
% syms( 'offP',   [3, 1], 'real' );
% syms( 'offT',   [3, 1], 'real' );
% syms( 'offB',   [3, 1], 'real' );
% syms( 'offC',   [3, 1], 'real' );

params = [ offM offT offP offB offC ];

syms( 'x',      [1,1],  'real' );
syms( 'y',      [1,1],  'real' );
syms( 'z',      [1,1],  'real' );
syms( 'b',      [1,1],  'real' );
syms( 'c',      [1,1],  'real' );

kin = Kinematics("xyzbc_tt", params);


% Test 1 :
B = 0; C = 0;
disp("*******************************************************************");
fprintf( 1, "Test 1 : B = " + B + " C = " + C + "\n" );
disp("------------------------------------------------------------------");

pA = [0;0;0];
wA = [0;0;0];

kin_xyzbc_tt_forward( [wA;B;C], params )
kin_xyzbc_tt_inverse( [pA;B;C], params )

pA = [0;0;0];
wA = -offM + offP;

check_kinematics( wA, pA, B,C, params );

disp("------------------------------------------------------------------");
pB = [d(1)/2;d(2)/2;0];
wB = [0;0;d(3)] - offM;
check_kinematics( wB, pB, B,C, params );

% Test 2 :
B = 90; C = 0;
disp("*******************************************************************");
fprintf( 1, "Test 1 : B = " + B + " C = " + C + "\n" );
disp("------------------------------------------------------------------");

pC = -offP;

D = norm(offB([1,3]) + offC([1,3]));
wC = [-D; 0; D] - offM;
check_kinematics( wC, pC, B,C, params );

disp("------------------------------------------------------------------");
B = 90; C = 90;
disp("*******************************************************************");
fprintf( 1, "Test 1 : B = " + B + " C = " + C + "\n" );
disp("------------------------------------------------------------------");

pD = -offP;

D = norm(offB([1,3]) + offC([1,3]));
wD = [-D; 0; D] - offM;
check_kinematics( wD, pD, B,C, params );

disp("------------------------------------------------------------------");

function [] = check_kinematics( wB, pB, B,C, params )
B = B / 180 * pi;
C = C / 180 * pi;

disp( "Test forward model : " );
fprintf( 1, "\t" + mat2str(pB) + " \t= " + ...
    mat2str( kin_xyzbc_tt_forward( [wB;B;C], params ) ) );
fprintf( 1, "\n" );

disp( "Test inverse model : " );
fprintf( 1, "\t" + mat2str(wB) + " \t= " + ...
    mat2str( kin_xyzbc_tt_inverse( [pB;B;C], params ) ) );
fprintf( 1, "\n" );
end

function [ F_HT, F_TH ] = test_micro5_forward_kinematics()
axe_x   = [1 0 0];
axe_y   = [0 1 0];
axe_z   = [0 0 1];
null    = zeros(3,1);
I       = eye(3,3);

syms( 'x',      [1,1],  'real' );
syms( 'y',      [1,1],  'real' );
syms( 'z',      [1,1],  'real' );
syms( 'b',      [1,1],  'real' );
syms( 'c',      [1,1],  'real' );

if(0)
    offM = zeros(3,1);
    offP = zeros(3,1);
    offT = zeros(3,1);
    offB = zeros(3,1);
    offC = zeros(3,1);
else
    syms( 'offM',   [3, 1], 'real' );
    syms( 'offP',   [3, 1], 'real' );
    syms( 'offT',   [3, 1], 'real' );
    syms( 'offB',   [3, 1], 'real' );
    syms( 'offC',   [3, 1], 'real' );
end

x_tilde = x - offM(1) - offT(1);
y_tilde = y - offM(2) - offT(2);
z_tilde = z - offM(3) - offT(3);


F_OT = translation_H([0, -y_tilde, 0]) * ...
    homogeneous_transform( rot3D( axe_y, b ), null ) * ...
    translation_H(offB) * ...
    homogeneous_transform( rot3D( axe_z, c ), null ) * ...
    translation_H(offC) * ...
    translation_H(offP);

F_OH = translation_H([x_tilde, 0, 0]) * translation_H([0, 0, z_tilde]);

F_OT = simplify( F_OT );
F_OH = simplify( F_OH );

F_HT = F_OH \ F_OT;
F_HT = simplify( F_HT );
F_TH = F_OT \ F_OH;
F_TH = simplify( F_TH );

disp("Forward transform :")
disp("Q : ");
disp( string(F_TH(1:3,4)));
disp("K : ");
K = F_HT(1:3,3);
disp(K);

disp("Inverse transform :")
disp("P : ");
disp(string(F_HT(1:3,4)));
K = F_TH(1:3,3);
c_ang   = atan2(-K(2), K(1));
c_ang   = simplify(c_ang);
b_ang   = atan2(-K(1), K(3) * cos(c_ang) );
b_ang   = simplify(b_ang);

disp("B : ");
disp(string(b_ang));
disp("C : ");
disp(string(c_ang));
end

function [] = test_rotation_with_lever()

useSymbolic = false;

if( useSymbolic )
    syms('B');
    syms('C');
    syms( 'offB', [3,1]);
else
    B = 45;
    C = 0;
    offB = [1; 2; 3];
end

axe_x   = [1 0 0];
axe_y   = [0 1 0];
axe_z   = [0 0 1];
null    = zeros(3,1);
I       = eye(3,3);

Ry = homogeneous_transform( rot3D( axe_y, B), null );
ty = homogeneous_transform( I, offB );

T1  = Ry * ty;
A   = norm( [offB(1); 0; offB(3)] );
delta = atan2( offB(1), offB(3) );

off_manual = [ sin(B + delta) * A; offB(2); cos(B + delta) * A ];
T2 = homogeneous_transform( rot3D( axe_y, B), off_manual );
DiffT = T2 - T1;

if( useSymbolic )
    T1 = simplify( T1 );
    T2 = simplify( T2 );
    DiffT = simplify( DiffT );
end

disp( DiffT );

end
