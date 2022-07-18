% queue = ctx.q_gcode;
% 
% N   = double( queue.size() );
% Nu  = 300;
% 
% points = zeros( ctx.cfg.NumberAxis, N * Nu );
% u_vec = linspace( 0, 1, Nu );

% for j = 1 : N
%     ind = [ 1 : Nu ] + ( j -1 ) * Nu;
%     curv = queue.get( j );
%     points( :, ind ) = EvalCurvStruct( ctx, curv, u_vec
% 
% ) *S;
% end

load("dev/anchor.mat");
points = ( points - mean( points, 2 ) ) * 3;
N   = size( points, 2 );
Nt  = 20;

roty = @( x ) [ cosd(x) 0 sind(x); 0 1 0; -sind(x) 0 cosd(x)];
rotz = @( x ) [ cosd(x) sind(x) 0; -sind(x) cosd(x) 0; 0 0 1];

S   = 0.5;
S1  = 3;

points( 1 : 3 , : ) = roty( 0 ) * points( 1 : 3 , : );

bounds = [ min( points( 1:2, : ), [], 2 ), max(points( 1:2, : ), [], 2 )];
M = ( bounds( :, 2 ) -  bounds( :, 1 ) )/ 2;
R = max( abs(M) ) /3;
Center = roty( 0 ) * [ ( bounds( :, 2 ) +  bounds( :, 1 ) )/ 2; -R * S1];

R = 0.5 * R * S1;

figure();
subplot( 2, 2, [ 1, 3 ] );
plot3( points(1, : ) / 3, points(2, : ) / 3, points(3, : ) /3 ); hold on;
plot3(Center(1), Center(2), Center(3), ':r')

points( 1:3, : )  = points( 1:3, : )  -Center;

points( 1:3, : )    = ( points( 1:3, : ) ) ./ vecnorm( ( points( 1:3, : ) ) ) * R;

offset = -min( points( 1:3, : ) + Center, [], 2 ) + [0;0;10];
offset( 1 ) = 0;

v = points( 1:3, : ) ;
C = rad2deg( atan2( v( 2,: ), v( 1, : ) ) );

vy = zeros( 3, N );

for j = 1 : N
    vy( :, j ) = rotz( C( j ) ) * v( :, j );
end

B = rad2deg( atan2( vy( 3,: ), vy( 1, : ) ) );

B = rad2deg( unwrap( deg2rad( B ) ) );
C = rad2deg( unwrap( deg2rad( C ) ) );

% 
B = -B +180;
C = -C +180;

while( any( B < 0 ) )
B( B < 0 ) = B( B < 0 ) + 360;
end

while( any( C < 0 ) )
C( C < 0 ) = C( C < 0 ) + 360;
end

points( 4, : ) = B -180;
points( 5, : ) = C -180;


% points( 4, : )      = -B;
% points( 5, : )      = -C;

points( 1 : 3, : )  = points( 1 : 3, : ) + Center + offset;
subplot( 2, 2, [ 1, 3 ] );
plot3( points(1, : ), points(2, : ), points(3, : ), '.' );

u = linspace( 0, 1, 20 );
Nt = Nt;
M = @( B, C ) R * rotz( C ) * roty( B ) * [ 1; 0; 0 ];

for j = 1 : floor( N / Nt ) + 1 : N
    v = Center + M( points( 4, j ), points( 5, j ) );
    p = u .* v + ( 1- u ) .* Center;
    p = p + offset;
    plot3( p(1, : ), p(2, : ), p(3, : ), 'r-' );
end

grid on;
axis equal;

% subplot( 2, 2, [2, 4] );
% plot( points( 4, : ), points( 5, : ), '.'); grid on;

subplot( 2, 2, 2);
plot( points( 4, : ), '.'); grid on;
title( "axe B [deg]");

subplot( 2, 2, 4 );
plot( points( 5, : ), '.'); grid on;
title( "axe C [deg]");
