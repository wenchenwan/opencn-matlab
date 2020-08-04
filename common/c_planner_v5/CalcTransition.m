function [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status]  = CalcTransition(ctx, CurvStruct1, CurvStruct2)

global DebugActive

CutOff=ctx.cfg.CutOff;
Length_Threshold=3*CutOff;
DebugLog('========== CalcTransition ==========\n')
DebugLog('CutOff = %.3f\n', CutOff)
if DebugActive
    PrintCurvStruct(ctx, CurvStruct1);
    PrintCurvStruct(ctx, CurvStruct2);
end

CurvStruct_T = CurvStruct1; %default value

[~, r0D1] = EvalCurvStruct(ctx, CurvStruct1, 1);

[~, r1D1] = EvalCurvStruct(ctx, CurvStruct2, 0);


% In case of max. 2° collinearity between two lines, NO transition P5
% is calculated
if CurvStruct1.Type~=CurveType.Helix && CurvStruct2.Type~=CurveType.Helix && ...
        collinear(r0D1, r1D1, 1e-6) % && norm(r0D2 - r1D2) < 10*eps && collinear(r0D2, r1D2, 1e-2)
    
    status = TransitionResult.Collinear;
    CurvStruct1_C = CurvStruct1;
    CurvStruct2_C = CurvStruct2;
    return
    
end

L1 = LengthCurv(ctx, CurvStruct1, 0, 1);
L2 = LengthCurv(ctx, CurvStruct2, 0, 1);

% CutOff calculation
if CurvStruct1.Type ~= CurveType.Spline && CurvStruct2.Type ~= CurveType.Spline
    if L1 < Length_Threshold || L2 < Length_Threshold
        CutOff = min (L1,L2)/3;
    end
else
    if CurvStruct1.Type == CurveType.Spline
        Spline=ctx.q_splines.get(CurvStruct1.sp_index);
        sp = Spline.sp;
        if length(sp.knots)>8
            l1 = SplineLengthApprox(ctx, CurvStruct1, sp.knots(end-4), 1)/2;
        else
            l1 = SplineLengthApprox(ctx, CurvStruct1, 0, 1)/3;
        end
    else
        if L1<Length_Threshold
            l1 = L1/3;
        else
            l1 = CutOff;
        end
    end
    
    if CurvStruct2.Type == CurveType.Spline
        Spline=ctx.q_splines.get(CurvStruct2.sp_index);
        sp = Spline.sp;
        if length(sp.knots)>8
            l2 = SplineLengthApprox(ctx, CurvStruct2, 0, sp.knots(5))/2;
        else
            l2 = SplineLengthApprox(ctx, CurvStruct2, 0, 1)/3;
        end
    else
        if L2<Length_Threshold
            l2 = L2/3;
        else
            l2 = CutOff;
        end
    end
    
    CutOff = min (l1,l2);
end

status = TransitionResult.Ok;


CurvStruct1_C = CutCurvStruct(ctx, CurvStruct1, 0, CutOff);
CurvStruct2_C = CutCurvStruct(ctx, CurvStruct2, CutOff, 0);

DebugLog('========== AFTER CUTTING \n')
if DebugActive
    PrintCurvStruct(ctx, CurvStruct1_C)
    PrintCurvStruct(ctx, CurvStruct2_C)
end

[r0D0, r0D1, r0D2] = EvalCurvStruct(ctx, CurvStruct1_C, 1);
[r1D0, r1D1, r1D2] = EvalCurvStruct(ctx, CurvStruct2_C, 0);

% G2 transition calculation
[p5, status] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2);

if status==1
    % transition CurvStruct calculation
    CurvStruct_T = ConstrTransP5Struct(p5, CurvStruct1.FeedRate);
    status = TransitionResult.Ok;
else
    %PlotCurvStructs(ctx, [CurvStruct1 CurvStruct2]);
%     SaveTransition
%     PrintCurvStruct(ctx, CurvStruct1);
%     PrintCurvStruct(ctx, CurvStruct2);
    status = TransitionResult.NoSolution;
%     warning('Unable to calculate transition');
end

% CurvStruct1_C.index_gcode = CurvStruct1.index_gcode;
% CurvStruct_T.index_gcode = CurvStruct1.index_gcode;
% CurvStruct2_C.index_gcode = CurvStruct2.index_gcode;

    CurvStruct1_C.gcode_source_line = CurvStruct1.gcode_source_line;
    CurvStruct_T.gcode_source_line = CurvStruct2.gcode_source_line;
    CurvStruct2_C.gcode_source_line = CurvStruct2.gcode_source_line;
    
end
