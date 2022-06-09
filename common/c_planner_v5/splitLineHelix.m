function [ ctx ] = splitLineHelix( ctx, curv )

L       = LengthCurv( ctx, curv, 0, 1 );
L_split = ctx.cfg.LSplit;

% Number of sub segments
N = ceil( L / L_split );

% Length of the sub segments
L_split = L / N;

u0 = curv.b_param;
% Loop
for k = 1 : N
    
    curvSplited = cutCurvStruct( ctx, curv, u0, L_split, false );

    u0 = curvSplited.a_param + curvSplited.b_param; 
    
    ctx.q_split.push( curvSplited );
    
end

end


