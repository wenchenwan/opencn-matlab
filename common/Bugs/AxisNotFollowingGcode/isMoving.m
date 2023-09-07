function [ x, y ] = isMoving(s, t)

if( nargin  < 2 )
    t = [1 : 1 : size(s, 1)]';
end

is_moving               = true( size(s) );
ds                      = diff( s, 1 );
is_moving( ds == 0 )    = false;

s_min                   = min( s );
s_max                   = max( s );

s_A                     = s_max - s_min;

s_resized               = is_moving * s_A + s_min;
y                       = [ s_resized; ones(size(s))* s_min ];
x                       = [t; flip(t)];

% figure();
% plot( s );
% hold on ; fill( x, y, 'r', 'FaceAlpha', 0.1 ); hold off;

end