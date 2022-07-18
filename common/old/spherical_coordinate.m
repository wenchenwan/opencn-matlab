
u   = linspace( 0, 1, 10 );
P0  = zeros( 3, 1 );
P1_vec  = ( rand( 3, 20 ) -0.5 ) * 4;

figure();

for P1 = P1_vec
v   = ( 1 - u ) .* P0 + u .* P1;
vpz = ( 1 - u ) .* P0 + u .* [ P1( 1 : 2 ); 0 ];
vpy = ( 1 - u ) .* P0 + u .* [ P1( 1 ); 0; P1( 3 ) ];

C = atan2( P1( 2 ), P1( 1 ) );

rotz = @(x) [ cos(x) sin(x) 0 ; -sin(x) cos(x) 0; 0 0 1 ];
roty = @(x) [ cos(x) 0 sin(x) ; 0 1 0; -sin(x) 0 cos(x) ];

vy = rotz( C ) * v;

B = atan2( vy( 3, end ), vy( 1, end ) );

ez = roty( B ) * vy;

P1_rot = rotz( -C )* roty( -B ) * ez;

plot3( P1( 1 ,: ), P1( 2, : ), P1( 3, : ), 'rx'); grid on; hold on;
plot3( P1_rot( 1 ,: ), P1_rot( 2 ,: ), P1_rot( 3  ,: ), 'b:' ); 
end

axis equal;
xlim( [ -4; 4 ] );
ylim( [ -4; 4 ] );
zlim( [ -4; 4 ] );