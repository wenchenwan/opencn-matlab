%% Projection of the anchor into the dome

% 0) Parameters
center      = [ 0; 0; -275 / 14 ];
RSphere     = 373 / 14;
ToolAngle   = 0;

ZBounds = [ 0; 7 ]; XYBounds = [ -18; 18 ];
scaleXY = 0.9;
DXY     = ( XYBounds( 2 ) - XYBounds( 1 ) ) * scaleXY;
offset  = 0.5; % in [ mm ]

BMax    = 12;   BMin    = -102;
CMax    = inf;  CMin    = -inf;
% Functions for rotation
R       = RSphere - offset;
roty = @( x ) [ cosd(x) 0 sind(x); 0 1 0; -sind(x) 0 cosd(x)];
rotz = @( x ) [ cosd(x) sind(x) 0; -sind(x) cosd(x) 0; 0 0 1];

% 1) Load and prepare data points ( center + resizing the anchor )
load( "utils/projectIntoSphere.mat" );
N           = size( points, 2 );
points2D    = points( 1 : 2, : );
points2D    = ( points2D - mean( points2D, 2 ) );
bounds      = [ min( points2D, [], 2 ), max( points2D, [], 2 )];
distance    = bounds( :, 2  ) - bounds( :, 1  );
points2D    = points2D ./ distance * DXY;
points3D    = [ points2D; ZBounds( 2 ) * ones( 1, N )];
% Plot result
[ f ] = plot_center_points3D( center, points3D );

% 2) Project the data points into a sphere
            
CPoints3D   = points3D - center;
CPoints3D   = CPoints3D ./ vecnorm( CPoints3D ) * R;
% Plot result
[ f ]       = plot_center_points3D( center, CPoints3D + center , f );

% 3) Compute the spherical coodinate for the RTCP

C = rad2deg( atan2( CPoints3D( 2,: ), CPoints3D( 1, : ) ) );
vy = zeros( 3, N );
for j = 1 : N
    vy( :, j ) = rotz( C( j ) ) * CPoints3D( :, j );
end
B = rad2deg( atan2( vy( 3,: ), vy( 1, : ) ) );
B = rad2deg( unwrap( deg2rad( B ) ) );
C = rad2deg( unwrap( deg2rad( C ) ) );

B = -B +180 + ToolAngle;
C = -C +180;

while( any( B < 0 ) )
B( B < 0 ) = B( B < 0 ) + 360;
end

while( any( C < 0 ) )
C( C < 0 ) = C( C < 0 ) + 360;
end

points5D = [ CPoints3D + center; B - 180; C - 180 ];

Matrix = @( B, C ) R * rotz( C ) * roty( B ) * [ 1; 0; 0 ];

[ f ] = plot_angles_orientation( center, points5D, Matrix, f );

% 4) Assert boundaries limits

if( any( points5D( 4, : ) > BMax, "all" ) ), error( "B is not valid" ); end
if( any( points5D( 4, : ) < BMin, "all" ) ), error( "B is not valid" ); end
if( any( points5D( 5, : ) > CMax, "all" ) ), error( "C is not valid" ); end
if( any( points5D( 5, : ) < CMin, "all" ) ), error( "C is not valid" ); end

disp( "Projection worked !" );

% 5) Write points into Gcode files

write_gcode_from_points( points5D, "anchor_5D_RTCP" );

%--------------------------------------------------------------------------
% Functions
%--------------------------------------------------------------------------

function [ f ] = plot_center_points3D( center, points3D, f )
if( nargin < 3 ) 
    f = figure(); 
else
    figure( f );
end

subplot( 2, 2, [ 1, 3 ] );
plot3( points3D( 1, : ) , points3D( 2, : ) , points3D( 3, : ) ); hold on;
plot3( center(1), center(2), center(3), 'xr' ); grid on; axis equal;

end

function [ f ] = plot_angles_orientation( center, points5D, M, f )

[ f ] = plot_center_points3D( center, points5D( 1 : 3, : ), f );

subplot( 2, 2, [ 1, 3 ] );

u       = linspace( 0, 1, 20 );
NOrVect = 10;

N = size( points5D, 2 );
for j = 1 : floor( N / NOrVect ) + 1 : N
    v = points5D( 1 : 3, j ) + M( points5D( 4, j ), points5D( 5, j ) );
    p = u .* points5D( 1 : 3, j ) + ( 1- u ) .* v;
    plot3( p(1, : ), p(2, : ), p(3, : ), 'r-' );
end

subplot( 2, 2, 2);
plot( points5D( 4, : ), '.'); grid on;
title( "axe B [deg]");

subplot( 2, 2, 4 );
plot( points5D( 5, : ), '.'); grid on;
title( "axe C [deg]");

end

function [] = write_gcode_from_points( points, name )
% write_gcode_from_points : Write a simple Gcode file from input points matrix
% Inputs :
%   points: [ 5 x N ]
%   name  : str     File name

feedrate = 500;

% Write GCode
msg = "G01 X%f Y%f Z%f B%f C%f";

fileID = fopen( name,'w');

fprintf(fileID, "%%\n");

fprintf(fileID, "TRAFO ON\n");

fprintf(fileID, "#1=" + feedrate + "\n");

fprintf(fileID, "G90\n"); 

K = size( points, 2 );

for k = 1 : K
    msg1 = sprintf(msg, points(1,k), points(2,k), points(3,k), points(4,k), points(5,k));
    if( k == 1 ), msg1 = msg1 + " F#1"; end
    fprintf(fileID, msg1 + "\n");
end

fprintf(fileID, "TRAFO OFF\n");

fprintf(fileID, "M2\n");

fprintf(fileID, "%%\n");

fclose(fileID);

end
