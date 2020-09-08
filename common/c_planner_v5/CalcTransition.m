function [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status]  = CalcTransition(ctx, CurvStruct1, CurvStruct2)

global DebugActive

CutOff=ctx.cfg.CutOff;
CollTolDeg=ctx.cfg.CollTolDeg;
Length_Threshold=3*CutOff;

DebugLog('========== CalcTransition ==========\n')
DebugLog('CutOff = %.3f\n', CutOff)
if DebugActive
    PrintCurvStruct(ctx, CurvStruct1);
    PrintCurvStruct(ctx, CurvStruct2);
end

CurvStruct_T = CurvStruct1; %default value

[~, r0D1_1] = EvalCurvStruct(ctx, CurvStruct1, 1);
[~, r1D1_1] = EvalCurvStruct(ctx, CurvStruct2, 0);

% colinearity test
if CurvStruct1.Type~=CurveType.Helix && CurvStruct2.Type~=CurveType.Helix && ...
        collinear(r0D1_1, r1D1_1, CollTolDeg) % && norm(r0D2 - r1D2) < 10*eps && collinear(r0D2, r1D2, 1e-2)
    
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
        l1 = SplineLengthApprox(ctx, CurvStruct1, sp.knots(end-4), 1)/2;
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
        l2 = SplineLengthApprox(ctx, CurvStruct2, 0, sp.knots(5))/2;
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
    
    if status==6
        % TODO: manage this case in the future
        CurvStruct_T = ConstrTransP5Struct(p5, CurvStruct1.FeedRate);
        status = TransitionResult.Ok;
    else
        status = TransitionResult.NoSolution;
    end
%     PlotCurvStructsBR(ctx, [CurvStruct1 CurvStruct_T CurvStruct2]);
%     plot3(r0D0(1), r0D0(2), r0D0(3), 'xr', 'LineWidth', 3);
%     plot3(r1D0(1), r1D0(2), r1D0(3), 'xr', 'LineWidth', 3);
%     axis equal;
%     hold off;
    
end

    CurvStruct1_C.gcode_source_line = CurvStruct1.gcode_source_line;
    CurvStruct_T.gcode_source_line = CurvStruct2.gcode_source_line;
    CurvStruct2_C.gcode_source_line = CurvStruct2.gcode_source_line;
    
end
