%% Test the kinematics for the micro5
clear; clc; close all;

w       = 39.93;
h       = 20.06;

% offM = [ 0, 0, -68.802 ]';
offM = [ 0, 0, 0]';
offT = [ 0, 0, 0 ]';
offP = [ 0, 0, 0]';
offB = [ 0, -60.8, -6.6 ]';
% offB = [ 0, 0, 0 ]';
offC = [ 0, 0, 0 ]';

params  = [ offM offT offP offB offC ];
kin     = Kinematics("xyzbc_tt", params);


% Test 1 :

disp("─────────────────────────────────────────────────────────────────────────");
B = 0; C = 0;
fprintf( 1, "<strong>Point A</strong> : B = " + B + " C = " + C + "\n" );
disp("─────────────────────────────────────────────────────────────────────────");
pA = [ 0; 0; h ];
wA = [ 0; 0; h ] + offM;

check_kinematics( wA, pA, B,C, params );

% Test 2 :

disp("─────────────────────────────────────────────────────────────────────────");
B = -90; C = 0;
fprintf( 1, "<strong>Point B</strong> : B = " + B + " C = " + C + "\n" );
disp("─────────────────────────────────────────────────────────────────────────");

pA = [ w/2; w/2; h ];
wA = [ -13.46; 20; 26.6 ] + offM;

check_kinematics( wA, pA, B,C, params );

% Test 3 :

disp("─────────────────────────────────────────────────────────────────────────");
B = 0; C = 0;
fprintf( 1, "<strong>Point C</strong>: B = " + B + " C = " + C + "\n" );
disp("─────────────────────────────────────────────────────────────────────────");

pA = [ w/2; w/2; h ];
wA = [ 20; 20; 20.06 ] + offM;

check_kinematics( wA, pA, B,C, params );

disp("─────────────────────────────────────────────────────────────────────────");
B = -90; C = 0;
fprintf( 1, " <strong>Point D</strong> : B = " + B + " C = " + C + "\n" );
disp("─────────────────────────────────────────────────────────────────────────");

pA = [ w/2; 0; h /2 ];
wA = [ -3.43; 0.035; 26.6 ] + offM;

check_kinematics( wA, pA, B,C, params );

disp("─────────────────────────────────────────────────────────────────────────");
B = -90; C = -90;
fprintf( 1, "<strong>Point E</strong> : B = " + B + " C = " + C + "\n" );
disp("─────────────────────────────────────────────────────────────────────────");


pA = [ w/2; w/2; h ];
wA = [ -13.46; -20; 26.6 ] + offM;

check_kinematics( wA, pA, B,C, params );

function [] = check_kinematics( wB, pB, B,C, params )
B = B / 180 * pi;
C = C / 180 * pi;

qres         = kin_xyzbc_tt_forward( [wB;B;C], params );
pBMatlab    = round( res( 1 : 3 ), 2 );

res         = kin_xyzbc_tt_inverse( [pB;B;C], params );
wBMatlab    = round( res( 1 : 3 ), 2 );


wB          = round( wB, 2 );
pB          = round( pB, 2 );

T = table( [ "q = " + mat2str( wB ); "p = " + mat2str( pB ) ], ...
    [ "p = " + mat2str( pBMatlab ); "q = " + mat2str( wBMatlab) ], 'VariableNames', ...
    { 'PostPro', 'Matlab' }, 'RowName', { 'Inverse', 'Forward' } );

disp( T );
end
