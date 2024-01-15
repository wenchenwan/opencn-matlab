function [ status, curv1C, curv2C, curvT, ret ] = ...
calcTransition( ctx, curv1, curv2 )
%#codegen
% calcTransition_new : Compute a transition curve using on a polynome of 
% degree 5.
%
% Inputs    :
% ctx           : The context
% curv          : Current structure of the curve
% nextCurv      : Next structure of the curve
%
% Outputs   : 
% curv          : New calculated curve structure (replace CurvStruct1)
% curvT         : New calculated transition curve
% nextCurv      : New calculated curve structure (replace CurvStruct2)
% status        : Status of the compuation see TransitionResult
% ret           : Return number based on the transition equation

coder.inline( "never" );

ret     = int32( 9 );
CutOff  = ctx.cfg.CutOff; 
Lcut1   = CutOff; Lcut2 = CutOff;

L1 = LengthCurv( ctx, curv1, 0, 1 );
L2 = LengthCurv( ctx, curv2, 0, 1 );

% If curv length is lower that cutting length return
if( ( L1 < 3 * Lcut1 ) || ( L2 < 3 * Lcut2 ) )
    curv1C  = curv1; curv2C  = curv2; curvT   = curv1;
    status  = TransitionResult.NoSolution;
    return;
end

[ ~, curv1C, ~ ] = cutCurvStruct( ctx, curv1, 0, L1-Lcut1, false );
ocn_assert( check_curv_length( ctx, curv1C, L1-Lcut1 ), ...
    "Curve Length not valide", mfilename );
[ ~, ~, curv2C ] = cutCurvStruct( ctx, curv2, 1, L2-Lcut2, true );
ocn_assert( check_curv_length( ctx, curv2C, L2-Lcut2 ), ...
    "Curve Length not valide", mfilename );

[r0D0, r0D1, r0D2] = EvalCurvStruct( ctx, curv1C, 1 );
[r1D0, r1D1, r1D2] = EvalCurvStruct( ctx, curv2C, 0 );


[p5, ret] = G2_Hermite_Interpolation_nAxis(ctx, r0D0, r0D1, r0D2, ...
                                                r1D0, r1D1, r1D2);

R0T = zeros( length(ctx.cfg.maskTot), 1 ); R1T = R0T;
R0T( ctx.cfg.maskTot ) = r0D0;
R1T( ctx.cfg.maskTot ) = r1D0;

curvT = constrTransP5Struct( curv1.Info, curv1.tool, R0T, ...
                             R1T, p5 );
curvT.Info.SpindleSpeed = min( curv1.Info.SpindleSpeed, ...
                               curv2.Info.SpindleSpeed );
curvT.Info.FeedRate     = min( curv1.Info.FeedRate, ...
                               curv2.Info.FeedRate );

if( ret== 1 )
    % standard case
    % transition CurvStruct calculation
    status = TransitionResult.Ok;
elseif( ret == 2 )
    % Is never set in the function !
    % badly conditioned matrix in G2_Hermite()
    status = TransitionResult.NoSolution;
elseif( ret == 6 )
    % TODO: decide in the future...
    % Now we ignore and construct the transition curve anyway
    status = TransitionResult.Ok;
else
    status = TransitionResult.NoSolution;
end

if( ( status ~= TransitionResult.NoSolution ) && ...
    ( all( p5 <= 0, 'all' ) ) )
    status = TransitionResult.NoSolution;
    ret = int32( 7 );
end

if( status == TransitionResult.Ok ) 
    isValid = check_continuity( ctx, curv1C, curvT );
    isValid = isValid && check_continuity( ctx, curvT, curv2C );
    if( ~isValid ) 
        status = TransitionResult.NoSolution; 
        ret = int32( 8 );
    end
end

end

function [ isValid ] = check_continuity( ctx, curv1, curv2 )
    tol         = ctx.cfg.Smoothing.ColTolSmooth;
    tol_cos     = ctx.cfg.Smoothing.ColTolCosSmooth;
    tol_kappa   = 1E-3;

    [ r11, r1d1, r1dd1 ] = EvalCurvStruct( ctx, curv1, 1 );
    [ r21, r2d1, r2dd1 ] = EvalCurvStruct( ctx, curv2, 0 );
    
    [t1, ~,  kappa1] = calc_t_nk_kappa( r1d1, r1dd1 );
    [t2, ~,  kappa2] = calc_t_nk_kappa( r2d1, r2dd1 );

    isC0    = all( abs( r11    -r21 ) < tol, 'all' );
    isG1    = collinear( t1, t2, tol_cos );
    isG2    = abs( kappa1 -kappa2 )   < tol_kappa;
    
    isValid = isC0 && isG1 && isG2;
end

function [ isValid ] = check_curv_length( ctx, curv, L )
tol = 1E-3;

isValid = ( abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
end
