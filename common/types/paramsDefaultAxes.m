function [ params ] = paramsDefaultAxes( ~ ) %#codegen
% paramsDefaultAxes : Get default params for the axes.

x   = 0.0; y   = 0.0; z   = 0.0;
a   = 0.0; b   = 0.0; c   = 0.0;
u   = 0.0; v   = 0.0; w   = 0.0;

if( coder.target( 'MATLAB' ) )
    params = { x, y, z, a, b, c, u, v, w };
else
    params.x       = x;
    params.y       = y;
    params.z       = z;
    params.a       = a;
    params.b       = b;
    params.c       = c;
    params.u       = u;
    params.v       = v;
    params.w       = w;
end

end