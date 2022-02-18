function [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status]  = ...
    CalcTransition(ctx, CurvStruct1, CurvStruct2)

CutOff=ctx.cfg.CutOff;
CollTolDeg=ctx.cfg.CollTolDeg;
Length_Threshold=3*CutOff;

% DebugLog(DebugCfg.Transitions, ...
%     '========== CalcTransition ==========\n')

if IsEnabledDebugLog(DebugCfg.Global)
    PrintCurvStruct(ctx, CurvStruct1);
    PrintCurvStruct(ctx, CurvStruct2);
end

CurvStruct_T = CurvStruct1; %default value

[r0D0_1, r0D1_1] = EvalCurvStruct(ctx, CurvStruct1, 0);
[r0D0_2, r0D1_2] = EvalCurvStruct(ctx, CurvStruct1, 1);
[r1D0_1, r1D1_1] = EvalCurvStruct(ctx, CurvStruct2, 0);
[r1D0_2, r1D1_2] = EvalCurvStruct(ctx, CurvStruct2, 1);

% colinearity test
if CurvStruct1.Type~=CurveType.Helix && CurvStruct2.Type~=CurveType.Helix && ...
        collinear(r0D1_2, r1D1_1, CollTolDeg) % && norm(r0D2 - r1D2) < 10*eps && collinear(r0D2, r1D2, 1e-2)
    
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
        a = CurvStruct1.a_param;
        b = CurvStruct1.b_param;
        
        % In a very general case we may cut a spline several times
        % at the end;
        % If a spline had already been cut at the end,
        % we must compute the corresponding
        % native spline parameter (u1_tilda) value
        % This value will be different from 1 in this special case
        u1_tilda = a*1+b;
        
        % We need to find the previous spline knot u0_tilda...
        Idx      = find(sp.knots < u1_tilda, 1, 'last');
        u0_tilda = sp.knots(Idx);
        l1 = SplineLengthApprox(ctx, CurvStruct1, u0_tilda, u1_tilda)/2;     
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
        a = CurvStruct2.a_param;
        b = CurvStruct2.b_param;
        
        % In a very general case we may cut a spline several times
        % at the beginning;
        % If a spline had already been cut at the beginning,
        % we must compute the corresponding
        % native spline parameter (u0_tilda) value
        % This value will be different from 0 in this special case
        u0_tilda = a*0+b;
        
        % We need to find the next spline knot u1_tilda...
        Idx      = find(sp.knots > u0_tilda, 1);
        u1_tilda = sp.knots(Idx);
        l2 = SplineLengthApprox(ctx, CurvStruct2, u0_tilda, u1_tilda)/2;
    else
        if L2<Length_Threshold
            l2 = L2/3;
        else
            l2 = CutOff;
        end
    end
    
    CutOff = min (l1,l2);
    
end

% DebugLog(DebugCfg.Transitions, ...
%     'CutOff = %.3f\n', CutOff)

status = TransitionResult.Ok;

CurvStruct1_C = CutCurvStruct(ctx, CurvStruct1, 0, CutOff);
CurvStruct2_C = CutCurvStruct(ctx, CurvStruct2, CutOff, 0);

DebugLog(DebugCfg.Global, ...
    '========== AFTER CUTTING \n')

if IsEnabledDebugLog(DebugCfg.Global)
    PrintCurvStruct(ctx, CurvStruct1_C)
    PrintCurvStruct(ctx, CurvStruct2_C)
end

[r0D0, r0D1, r0D2] = EvalCurvStruct(ctx, CurvStruct1_C, 1);
[r1D0, r1D1, r1D2] = EvalCurvStruct(ctx, CurvStruct2_C, 0);

% G2 transition calculation
[p5, ret, ~, ~] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2);

if ret==1
    
    % standard case
    % transition CurvStruct calculation
    CurvStruct_T = ConstrTransP5Struct(CurvStruct1.TRAFO,...
                   CurvStruct1.Poff, CurvStruct1.Aoff, ...
                   CurvStruct1.Uoff, CurvStruct1.Doff,...
                   [CurvStruct1.A0, CurvStruct1.A1], ...
                   [CurvStruct1.U0, CurvStruct1.U1], ...
                   p5, CurvStruct1.FeedRate);
    status = TransitionResult.Ok;

elseif ret==6
    
    % TODO: decide in the future...
    % Now we ignore and construct the transition curve anyway
    CurvStruct_T = ConstrTransP5Struct(CurvStruct1.TRAFO,...
                   CurvStruct1.Poff, CurvStruct1.Aoff, ...
                   CurvStruct1.Uoff, CurvStruct1.Doff,...
                   [CurvStruct1.A0, CurvStruct1.A1], ...
                   [CurvStruct1.U0, CurvStruct1.U1], ...
                   p5, CurvStruct1.FeedRate);
    status = TransitionResult.Ok;
              
    DebugLog(DebugCfg.Warning, ...
            '========== CalcTransition ==========\n');
    DebugLog(DebugCfg.Warning, ...
        '=========== status = 6 ==========\n');
    DebugLog(DebugCfg.Warning, ...
        'Lines: %d, %d\n\n', CurvStruct1.gcode_source_line, ...
        CurvStruct2.gcode_source_line);
    
%     if coder.target('matlab')
% 
%         figure;
%         PlotCurvStructsBR(ctx, [CurvStruct1 CurvStruct_T CurvStruct2]);
%         hold on;
%         plot3(r0D0(1), r0D0(2), r0D0(3), 'xr', 'LineWidth', 3);
%         hold on;
%         plot3(r1D0(1), r1D0(2), r1D0(3), 'xr', 'LineWidth', 3);
%         title({ctx.cfg.source, 'status_G2_Hermite=6'}, 'Interpreter', 'none');
%         axis equal;
%         camproj('perspective');
% 
%     end
       
else
    
    status = TransitionResult.NoSolution;
    
    DebugLog(DebugCfg.Error, ...
        '========== CalcTransition ==========\n');
    DebugLog(DebugCfg.Error, ...
        '=========== No Solution ==========\n');
    DebugLog(DebugCfg.Error, ...
        'Lines: %d, %d\n\n', CurvStruct1.gcode_source_line, ...
        CurvStruct2.gcode_source_line);
    
%     if coder.target('matlab')
% 
%         figure;
%         PlotCurvStructsBR(ctx, [CurvStruct1 CurvStruct2]);
%         hold on;
%         plot3(r0D0(1), r0D0(2), r0D0(3), 'xr', 'LineWidth', 3);
%         hold on;
%         plot3(r1D0(1), r1D0(2), r1D0(3), 'xr', 'LineWidth', 3);
%         hold on;
%         plot3(r0D0_1(1), r0D0_1(2), r0D0_1(3), 'xc', 'LineWidth', 3);
%         hold on;
%         plot3(r0D0_2(1), r0D0_2(2), r0D0_2(3), 'xc', 'LineWidth', 3);
%         hold on;
%         plot3(r1D0_1(1), r1D0_1(2), r1D0_1(3), 'xc', 'LineWidth', 3);
%         hold on;
%         plot3(r1D0_2(1), r1D0_2(2), r1D0_2(3), 'xc', 'LineWidth', 3);
%         title({ctx.cfg.source, 'No solution'}, 'Interpreter', 'none');
%         axis equal;
%         camproj('perspective');
% 
%     end
            
end

    CurvStruct1_C.gcode_source_line = CurvStruct1.gcode_source_line;
    CurvStruct_T.gcode_source_line = CurvStruct2.gcode_source_line;
    CurvStruct2_C.gcode_source_line = CurvStruct2.gcode_source_line;
    
    CurvStruct1_C.SpindleSpeed = CurvStruct1.SpindleSpeed;
    CurvStruct_T.SpindleSpeed = min(CurvStruct1.SpindleSpeed, CurvStruct2.SpindleSpeed);
    CurvStruct2_C.SpindleSpeed = CurvStruct2.SpindleSpeed;
    
end
