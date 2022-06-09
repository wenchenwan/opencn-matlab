function [ ctx ] = splitCurvStruct( ctx, curv )
% SplitCurvStruct : Split the curv structs with a zero speed.
% Inputs  : 
% ctx   : The context
% curv  : The curv struct
% Output  : 
% ctx   : The modified context

if ( curv.Info.Type == CurveType.TransP5 )    
    ctx.q_split.push( curv ); return;
end

if      ( isAZeroSpeed( curv ) )
    [ ctx ] = split_zero_speed_curv( ctx, curv ); return;
end

L       = LengthCurv( ctx, curv, 0, 1 );
L_split = ctx.cfg.LSplit;

% Number of sub segments
N = ceil( L / L_split );

% Length of the sub segments
L_split = L / N;

% Loop
u0 = 0;

for k = 1 : N - 1
    u1_tilda  = cutCurvStructU( ctx, curv, u0, L_split, false );
    u1 = ( u1_tilda - curv.b_param ) / curv.a_param;
    
    if( u1 < 1 )
        curvSplited         = curv;
        curvSplited.a_param = u1_tilda - curvSplited.b_param;

        if( isAZeroStart( curvSplited ) )
            curvSplited.Info.zspdmode = ZSpdMode.ZN;
        else
            curvSplited.Info.zspdmode = ZSpdMode.NN;
        end

        curv.a_param        = curv.a_param  + curv.b_param - u1_tilda;
        curv.b_param        = u1_tilda;

        if( isAZeroEnd( curv ) )
            curv.Info.zspdmode = ZSpdMode.NZ;
        else
            curv.Info.zspdmode = ZSpdMode.NN;
        end
    else 
        curvSplited         = curv;
    end

    ctx.q_split.push( curvSplited );
    
end

ctx.q_split.push( curv );

end

function [ ctx ] = split_zero_speed_curv( ctx, curv )
% split_zero_speed_curv : Split the curv structs with a zero speed.
[ curvS, curvM, curvE ] = cutZeroSpeed( ctx, curv );

if( isAZeroStart( curv ) ), ctx.q_split.push( curvS ); end

ctx = splitCurvStruct( ctx, curvM );

if( isAZeroEnd( curv ) ),   ctx.q_split.push( curvE ); end

end