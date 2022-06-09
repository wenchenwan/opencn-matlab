function [ ctx ] = splitLineHelix( ctx, curv )

L       = LengthCurv( ctx, curv, 0, 1 );
L_split = ctx.cfg.LSplit;

% Number of sub segments
N = ceil( L / L_split );

% Length of the sub segments
L_split = L / N;

l1 =  0;
% Loop
for k = 1 : N
    
    l0 = l1;
    l1 = l1 + L_split;

    curvSplited = cutCurvStruct( ctx, curv, l0, l1 );

    ctx.q_split.push( curvSplited );
    
end

end


