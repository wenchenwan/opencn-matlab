function [ u1_tilda ] = cutCurvStructU( ctx, curv, u0, L, isEnd )
% cutCurvStructU: Cut a piece of the structure with a size of L
% starting at point u0
% Inputs :
% ctx   : Context
% curv  : Curvature
% u0    : Starting point of the spline
% L     : Length of the segment of curv
% isEnd : Is a cut from the end
% Outputs :
% u1    : The last point of the splitted curv

a = curv.a_param;
b = curv.b_param;

if ( curv.Info.Type == CurveType.Spline )
    spline = ctx.q_spline.get( curv.sp_index );
    u1_tilda = splineLenghtFindU_new( ctx.cfg, spline, L, a * u0 + b, isEnd );
else
    
    % In case of helix and line, ||r'(u)||=const,
    % for 0 < u < 1
    if( isEnd )
        [ ~, r1D1 ] = EvalCurvStruct( ctx, curv, 1 );
        u1 = u0 - L / MyNorm( r1D1 );
    else
        [ ~, r1D0 ] = EvalCurvStruct( ctx, curv, 0 );
        u1 = u0 + L / MyNorm( r1D0 );
    end
    u1_tilda = a * u1 + b;
end

end