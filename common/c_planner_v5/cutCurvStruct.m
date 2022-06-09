function [ u1_tilda ] = cutCurvStruct( ctx, curv, u0, L, isEnd )
% cutCurvStruct: Cut a piece of the structure with a size of L
% starting at point u0
% Inputs :
% ctx   : Context
% curv  : Curvature
% u0    : Starting point of the spline
% L     : Length of the segment of curv
% isEnd : Is a zero stop curv
% Outputs :
% u1    : The last point of the splitted curv

a = curv.a_param;
b = curv.b_param;

if ( curv.Info.Type == CurveType.Spline )
    u1_tilda = splineLengthFindU( ctx, curv, L, a * u0 + b, isEnd );
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

if( u1_tilda >= 1 )
    u1_tilda = curv.a_param / 2 + curv.b_param;
end
end