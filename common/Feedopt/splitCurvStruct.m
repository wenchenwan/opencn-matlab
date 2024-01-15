function [ ctx ] = splitCurvStruct( ctx, curv )
%#codegen
% SplitCurvStruct : Split the curv structs based on the cutting lengeht 
% the zero speed curve are also cutted during this step.
%
% Inputs  : 
% ctx   : The context
% curv  : The curv struct
%
% Outputs  : 
% ctx   : The modified context
%

if( ~coder.target( 'MATLAB' ) ), curvE = constrCurvStructType; end

if ( curv.Info.Type == CurveType.TransP5 )    
    ctx.q_split.push( curv ); return;
end

if( isAZeroStart( curv ) )
    % cut zero Start
    [ ret, curvS, curv ] = cutZeroStart( ctx, curv );
    ctx.q_split.push( curvS );
    if( ret < 0 ), return; end
end

hasEndSpeed = false;
if( isAZeroEnd( curv ) )
    % cut zero End
    [ ret, curv, curvE ] = cutZeroEnd( ctx, curv );
    if( ret < 0 )
        ctx.q_split.push( curv );
        return; 
    end
    hasEndSpeed     = true;
end

if( ctx.cfg.SplitSpecialSpline && curv.Info.Type == CurveType.Spline )
    bspline     = ctx.q_spline.get( curv.sp_index );
    breakPoints = bspline.sp.Bl.breakpoints;
    uMin        = curv.b_param;
    uMax        = curv.b_param + curv.a_param;
    ind         = find( breakPoints > uMin & breakPoints < uMax );
    breakPoints = [ uMin, breakPoints( ind ), uMax ] ;
    deltaU      = diff( breakPoints );
    uPrevious   = uMin;
    for j = 1 : length( deltaU )
        curvSplited         = curv;
        
    	curvSplited.a_param = deltaU( j );
        
        curvSplited.b_param = uPrevious;
        uPrevious           = curvSplited.a_param + curvSplited.b_param;
        ctx.q_split.push( curvSplited );
    end
else
    L       = LengthCurv( ctx, curv, 0, 1 );
    L_split = ctx.cfg.LSplit;
    
    % Number of sub segments
    N = ceil( L / L_split );
    
    % Length of the sub segments
    L_split = L / N;
    
    for k = 1 : N - 1
        [ ret, curvSplited, curv ] = cutCurvStruct( ctx, curv, 0, L_split, false );
        if( ret < 0 ), break; end
    
        ocn_assert( check_curv_length( ctx, curvSplited, L_split ), ...
            "Curve Length not valide", mfilename );
    
        ctx.q_split.push( curvSplited );
    end
    ctx.q_split.push( curv );
end

if( hasEndSpeed )
    % cut zero End
    ctx.q_split.push( curvE );
end

end

function [ isValid ] = check_curv_length( ctx, curv, L )
tol = 1E-3;

isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
end
