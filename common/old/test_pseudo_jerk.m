load( 'dev/c.mat' );
cfg = FeedoptDefaultConfig;
ctx = initFeedoptPlan( cfg );
dt  = 1E-4;
N   = 100;


jps = 0.003;
k   = linspace( 0, 1, N ) / ( jps * dt );
u   = k * dt * jps;
ud  = ( k * dt ).^2 * jps  / 2;
udd = ( k * dt ).^3 * jps  / 6;
[ BasisValk, BasisValDk ] = bspline_base_eval( ctx.Bl, u );
ud_opt  = sqrt( BasisValk * c )';
udd_opt = (BasisValDk * c / 2)';
v_opt   = [ udd_opt; ud_opt; u ];
v       = [ udd;     ud;     u ];
d       = v - v_opt;
d       = d ./ vecnorm( d );
s       = zeros( N-1, 1 );

for j = 1 : N -1
    s( j ) = d( :, j )' * d( :, j + 1 );
    if( ( j > 1 ) && ( s( j ) * s( j -1 ) < 0 ) ), break; end
end



figure();
plot3( v_opt(1,: ), v_opt(2,: ), v_opt(3,: ) );hold on; grid on;
plot3( v(1,: ), v(2,: ), v(3,: ) );

NJps = 1000;
jps = logspace( -7, 0, NJps );

figure();
for j = 1 : NJps
    k   = linspace( 0, 1, N ) / ( jps( j ) * dt );
    u   = k * dt * jps( j );
    ud  = ( k * dt ).^2 * jps( j )  / 2;
    udd = ( k * dt ).^3 * jps( j )  / 6;
    v   = [ udd;     ud;     u ];
    plot3( v( 1, : ), v( 2, : ), v( 3, : ), '.'); hold on;
end

axe_lim = [ min( v_opt, [], 2 ), max( v_opt, [], 2 ) ];

xlim( axe_lim( 1, : ) * 1.1 );
ylim( axe_lim( 2, : ) * 1.1 );
zlim( axe_lim( 3, : ) * 1.1 );

plot3( v_opt(1,: ), v_opt(2,: ), v_opt(3,: ), '-k', 'LineWidth', 2);

grid on;

% N   = 1000 / jps;
% k   = 1 : N;
% u   = k * dt;
% ud  = u.*u  / 2;
% udd = ud.*u / 3;
% v   = [ udd;     ud;     u ] * jps ;
% plot3( v(1,: ), v(2,: ), v(3,: ) );
% % 
%     kT  = ( j -1 ) * dt;
%     v   = [ kT ; kT^2 /2 ; kT^3 / 6 ];
%     [ BasisVal, BasisValD ] = bspline_base_eval( ctx.Bl, u( j ) );
%     p   = [ BasisValD * c / 2; sqrt( BasisVal * c ); u( j ) ];
%     s( j )  = v' * ( v - p );
%     
%     if( j > 1 && s( j - 1 ) * s( j ) <= 0 )
%             disp( j );
%             lim = [ j-1, j ];
%             if( s( j ) < 0 ), lim = flip( lim ); end
%             um = sum( lim ) / 2  * dt;
%             %
%             %         count = 0;
%             %         while( count < 10000 )
%             %             um  = sum( lim ) / 2;
%             %             kT  = um * dt;
%             %             v   = [ kT ; kT^2 /2 ; kT^3 / 6 ];
%             %             v   = v / vecnorm( v );
%             %             [ BasisVal, BasisValD ] = bspline_base_eval( ctx.Bl, um );
%             %             p   = [ BasisValD * c / 2; sqrt( BasisVal * c ); um ];
%             %             p = p / vecnorm( p );
%             %             sm  = v' * p;
%             %             if( sm <= 0 )
%             %                 lim( 1 ) = um;
%             %             else
%             %                 lim( 2 ) = um;
%             %             end
%             %             count = count + 1;
%             %             if( abs( sm ) < 10e-3  )
%             %                 disp( 'here' );
%             %                 disp( count );
%             %                 break;
%             %             end
%             %         end
%             %         jpsM = ( 6 * um ) / ( kT )^3;
%             %         disp( jpsM );
%             %         if( jpsM < jps )
%             %             break;
%             %         end
%     end
% end

% plot( s ); hold on;
% yline( 0 );
%
% disp( um );
% disp( jpsM );
%
% [ BasisVal, BasisValD ] = bspline_base_eval( ctx.Bl, u );
% qu  = BasisVal  * c;
% qdu = BasisValD * c;
%
% figure();
% plot3( qdu, qu, u ); hold on; grid on;
%
% u_jps   = jps .* ( u ).^3 / 6;
% ud_jps  = u_jps * 3 ./ u;
% udd_jps = u_jps * 2 ./ u;
% ind = find( u_jps < 1 );
% plot3( udd_jps( ind ) * 2, ud_jps( ind ).^2, u_jps( ind ) );
%
% u_jpsM   = jpsM .* ( u ).^3 / 6;
% ud_jpsM  = u_jpsM * 3 ./ u;
% udd_jpsM = u_jpsM * 2 ./ u;
% ind = find( u_jpsM < 1 );
% plot3( udd_jpsM( ind ) * 2, ud_jpsM( ind ).^2, u_jpsM( ind ) );

