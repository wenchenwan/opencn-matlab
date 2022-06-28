function [ status, curv1C, curv2C, curvT ] = calcTransition_new( ctx, curv1, curv2 )
%#codegen
% calcTransition_new : Compute a transition curve using on a polynome of 
% degree 5.
%
% ctx           : The context
% curv          : Current structure of the curve
% nextCurv      : Next structure of the curve
%
% curv          : New calculated curve structure (replace CurvStruct1)
% curvT         : New calculated transition curve
% nextCurv      : New calculated curve structure (replace CurvStruct2)
% status        : Status of the compuation see TransitionResult

coder.inline( "never" );

CutOff = ctx.cfg.CutOff; 
Lcut1 = CutOff; Lcut2 = CutOff;

L1 = LengthCurv( ctx, curv1, 0, 1 );
L2 = LengthCurv( ctx, curv2, 0, 1 );

if( L1 / 3  < Lcut1 )
    Lcut1 = L1 / 3;
end

if( L2 / 3 < Lcut2 )
    Lcut2 = L2 / 3;
end

[ u1_tilda ] = cutCurvStructU( ctx, curv1, 0, L1 - Lcut1, false );
curv1C              = curv1;
curv1C.a_param      = u1_tilda -curv1C.b_param;

[ u2_tilda ] = cutCurvStructU( ctx, curv2, 1, L2 - Lcut2, true );

curv2C              = curv2;
curv2C.b_param      = u2_tilda;
curv2C.a_param      = curv2.a_param  + curv2.b_param - curv2C.b_param;

[r0D0, r0D1, r0D2] = EvalCurvStruct( ctx, curv1C, 1 );
[r1D0, r1D1, r1D2] = EvalCurvStruct( ctx, curv2C, 0 );


[p5, ret] = G2_Hermite_Interpolation_nAxis(ctx, r0D0, r0D1, r0D2, ...
                                                r1D0, r1D1, r1D2);

curvT = constrTransP5Struct( curv1.Info, curv1.R1, curv2.R0, p5 );
curvT.Info.SpindleSpeed = min( curv1.Info.SpindleSpeed, ...
                               curv2.Info.SpindleSpeed );
curvT.Info.FeedRate     = min( curv1.Info.FeedRate, ...
                               curv2.Info.FeedRate );
if( ret== 1 )
    % standard case
    % transition CurvStruct calculation
    status = TransitionResult.Ok;
elseif( ret == 2)
    % badly conditioned matrix in G2_Hermite()
    status = TransitionResult.NoSolution;
elseif( ret == 6)
    % TODO: decide in the future...
    % Now we ignore and construct the transition curve anyway
    status = TransitionResult.Ok;
else
    status = TransitionResult.NoSolution;
end

if( coder.target("MATLAB") && TransitionResult.Ok )
    check_continuity( ctx, curv1C, curvT );
    check_continuity( ctx, curvT, curv2C );
end

end

function [] = check_continuity( ctx, curv1, curv2 )
    tol = 1E-3;
    [ r11, r1d1, r1dd1 ] = EvalCurvStruct( ctx, curv1, 1 );
    [ r21, r2d1, r2dd1 ] = EvalCurvStruct( ctx, curv2, 0 );
    
    [t1, ~,  kappa1] = calc_t_nk_kappa( r1d1, r1dd1 );
    [t2, ~,  kappa2] = calc_t_nk_kappa( r2d1, r2dd1 );

    diff_r      = abs( r11    -r21 )        < tol;
%     diff_rd     = norm( cross( t1, t2 ) )   < tol;
    diff_rdd    = abs( kappa1 -kappa2 )     < tol;

    assert( all( diff_r ), mfilename + ...
                        ".m : continuity C0 failed " + mat2str( diff_r' ) );
%     assert( diff_rd  , mfilename + ...
%                         ".m : continuity G1 failed "  + diff_rd );
    assert( diff_rdd , mfilename + ...
                        ".m : continuity G2 failed "  + mat2str( diff_rdd' ) );

end