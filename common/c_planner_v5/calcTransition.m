function [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status]  = ...
    calcTransition(ctx, CurvStruct1, CurvStruct2)
% CalcTransition : Compute a transition curve using on a polynome of degree
% 5.
%
% ctx           : The context
% CurvStruct1   : Current structure of the curve
% CurvStruct2   : Next structure of the curve
%
% CurvStruct1_C : New calculated curve structure (replace CurvStruct1)
% CurvStruct_T  : New calculated transition curve
% CurvStruct2_C : New calculated curve structure (replace CurvStruct2)
% status        : Status of the compuation see TransitionResult

coder.inline("never");

CutOff              = ctx.cfg.CutOff;                   % Length removed
ColTolCos           = ctx.cfg.ColTolCosSmooth;          % Tol for colinear

% If the 1st or the 2nd Curve lenth is shorter than 3*CutOff,
% we will recalculate Cutoff. This new value will be smaller than before.
% The 3 factor is an attempt to obtain:
% new CutOff at beginning + rest of Curve + new CutOff at end = curve length before cutting,
% with: new CutOff at beginning = rest of Curve = new CutOff at end, approx.
Length_Threshold    = 3*CutOff;                         % 
    
line1 = CurvStruct1.Info.gcode_source_line;
line2 = CurvStruct2.Info.gcode_source_line;

if coder.target( 'MATLAB' )
    if IsEnabledDebugLog(DebugCfg.Global)
        PrintCurvStruct(ctx, CurvStruct1);
        PrintCurvStruct(ctx, CurvStruct2);
    end
end

CurvStruct_T = CurvStruct1; % default value
CurvStruct_T.Info.zspdmode = ZSpdMode.NN; % only value possible for a transition

[r0D0_1, r0D1_1] = EvalCurvStruct(ctx, CurvStruct1, 0); % Curv1 @0
[r0D0_2, r0D1_2] = EvalCurvStruct(ctx, CurvStruct1, 1); % Curv1 @1
[r1D0_1, r1D1_1] = EvalCurvStruct(ctx, CurvStruct2, 0); % Curv2 @0
[r1D0_2, r1D1_2] = EvalCurvStruct(ctx, CurvStruct2, 1); % Curv2 @1

% colinearity test
if  CurvStruct1.Info.Type ~= CurveType.Helix ...
    && CurvStruct2.Info.Type ~= CurveType.Helix ...
    && collinear(r0D1_2, r1D1_1, ColTolCos)

    status = TransitionResult.Collinear;    
    CurvStruct1_C = CurvStruct1;
    CurvStruct2_C = CurvStruct2;
    
    return
    
end

L1 = LengthCurv(ctx, CurvStruct1, 0, 1);
L2 = LengthCurv(ctx, CurvStruct2, 0, 1);

% CutOff calculation
if CurvStruct1.Info.Type ~= CurveType.Spline ...
   && CurvStruct2.Info.Type ~= CurveType.Spline
    % If L1 or L2 is smaller than 3*CutOff
    if L1 < Length_Threshold || L2 < Length_Threshold
        CutOff = min (L1,L2)/3;
    end
else
    if CurvStruct1.Info.Type == CurveType.Spline
        Spline=ctx.q_spline.get(CurvStruct1.sp_index);
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
        % 
        k = length(sp.knots);
        while sp.knots(k) >= u1_tilda
            k = k - 1;
        end
        u0_tilda = sp.knots(k);
        spline = ctx.q_spline.get( CurvStruct1.sp_index );
        [ l1 ] = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda ) / 2 ;
    else
        if L1<Length_Threshold
            l1 = L1/3;
        else
            l1 = CutOff;
        end
    end
    
    if CurvStruct2.Info.Type == CurveType.Spline
        Spline=ctx.q_spline.get(CurvStruct2.sp_index);
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
        % 
        k = 1;
        while sp.knots(k) <= u0_tilda
            k = k + 1;
        end
        u1_tilda = sp.knots(k);
        spline = ctx.q_spline.get( CurvStruct2.sp_index );
        [ l2 ] = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda ) / 2 ;
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

% Cut the curve structures
CurvStruct1_C = cutCurvStruct( ctx, CurvStruct1, 0, L1 - CutOff, false );
CurvStruct2_C = cutCurvStruct( ctx, CurvStruct2, 1, L2 - CutOff, true  );

if coder.target( 'MATLAB' )
    if IsEnabledDebugLog(DebugCfg.Global)
        PrintCurvStruct(ctx, CurvStruct1_C)
        PrintCurvStruct(ctx, CurvStruct2_C)
    end
end

[r0D0, r0D1, r0D2] = EvalCurvStruct(ctx, CurvStruct1_C, 1);
[r1D0, r1D1, r1D2] = EvalCurvStruct(ctx, CurvStruct2_C, 0);

% G2 transition calculation
% [p5, ret, ~, ~] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2);
[p5, ret, ~, ~] = G2_Hermite_Interpolation_nAxis(ctx, r0D0, r0D1, r0D2, r1D0, r1D1, r1D2);

if ret==1

    % standard case
    % transition CurvStruct calculation
    CurvStruct_T = constrTransP5Struct(CurvStruct1.Info, CurvStruct1.R0,...
                                       CurvStruct1.R1, p5);
    CurvStruct_T.Info.zspdmode = ZSpdMode.NN; % only value possible for a transition
    status = TransitionResult.Ok;
    
elseif ret==2
    
    % badly conditioned matrix in G2_Hermite()
    status = TransitionResult.NoSolution;
    
    if coder.target( 'MATLAB' )
        DebugLog(DebugCfg.Error, '========== CalcTransition ==========\n');
        DebugLog(DebugCfg.Error, '=========== Badly Cond. Matrix in G2_Hermite() ==========\n');
        DebugLog(DebugCfg.Error, 'Lines: %d, %d\n\n', line1, line2);
    end
    
    if coder.target('matlab')
    if IsEnabledDebugLog(DebugCfg.Plots)
        
        figure;
        PlotCurvStructsBR(ctx, [CurvStruct1 CurvStruct2]);
        hold on;
        plot3(r0D0(1), r0D0(2), r0D0(3), 'xr', 'LineWidth', 3);
        hold on;
        plot3(r1D0(1), r1D0(2), r1D0(3), 'xr', 'LineWidth', 3);
        hold on;
        plot3(r0D0_1(1), r0D0_1(2), r0D0_1(3), 'xc', 'LineWidth', 3);
        hold on;
        plot3(r0D0_2(1), r0D0_2(2), r0D0_2(3), 'xc', 'LineWidth', 3);
        hold on;
        plot3(r1D0_1(1), r1D0_1(2), r1D0_1(3), 'xc', 'LineWidth', 3);
        hold on;
        plot3(r1D0_2(1), r1D0_2(2), r1D0_2(3), 'xc', 'LineWidth', 3);
        str = regexp(ctx.cfg.source, '/', 'split'); % to get only g-code file name
        title({str{end}, 'Badly Cond. Matrix', ...
            ['Lines: ', num2str(line1), ' ', num2str(line2)]}, 'Interpreter', 'none');
        axis equal;
        camproj('perspective');
    end
    end
    
elseif ret==6
    
    % TODO: decide in the future...
    % Now we ignore and construct the transition curve anyway
    CurvStruct_T = constrTransP5Struct(CurvStruct1.Info, CurvStruct1.R0,...
                                       CurvStruct1.R1, p5);
    CurvStruct_T.Info.zspdmode = ZSpdMode.NN; % only value possible for a transition
    status = TransitionResult.Ok;
    
    if coder.target( 'MATLAB' )
        DebugLog(DebugCfg.Warning, '========== CalcTransition ==========\n');
        DebugLog(DebugCfg.Warning, '=========== status = 6 ==========\n');
        DebugLog(DebugCfg.Warning, 'Lines: %d, %d\n\n', line1, line2);
    end
    
    if coder.target('matlab')
    if  IsEnabledDebugLog(DebugCfg.Plots)

        figure;
        PlotCurvStructsBR(ctx, [CurvStruct1 CurvStruct_T CurvStruct2]);
        hold on;
        plot3(r0D0(1), r0D0(2), r0D0(3), 'xr', 'LineWidth', 3);
        hold on;
        plot3(r1D0(1), r1D0(2), r1D0(3), 'xr', 'LineWidth', 3);
        str = regexp(ctx.cfg.source, '/', 'split'); % to get only g-code file name
        title({str{end}, 'status_G2_Hermite=6', ...
            ['Lines: ', num2str(line1), ' ', num2str(line2)]}, 'Interpreter', 'none');
        axis equal;
        camproj('perspective');
    end
    end
       
else
    
    status = TransitionResult.NoSolution;
    if coder.target( 'MATLAB' )
        DebugLog(DebugCfg.Error, '========== CalcTransition ==========\n');
        DebugLog(DebugCfg.Error, '=========== No Solution ==========\n');
        DebugLog(DebugCfg.Error, 'Lines: %d, %d\n\n', line1, line2);
    end
    
    if coder.target('matlab')
    if IsEnabledDebugLog(DebugCfg.Plots)
        
        figure;
        PlotCurvStructsBR(ctx, [CurvStruct1 CurvStruct2]);
        hold on;
        plot3(r0D0(1), r0D0(2), r0D0(3), 'xr', 'LineWidth', 3);
        hold on;
        plot3(r1D0(1), r1D0(2), r1D0(3), 'xr', 'LineWidth', 3);
        hold on;
        plot3(r0D0_1(1), r0D0_1(2), r0D0_1(3), 'xc', 'LineWidth', 3);
        hold on;
        plot3(r0D0_2(1), r0D0_2(2), r0D0_2(3), 'xc', 'LineWidth', 3);
        hold on;
        plot3(r1D0_1(1), r1D0_1(2), r1D0_1(3), 'xc', 'LineWidth', 3);
        hold on;
        plot3(r1D0_2(1), r1D0_2(2), r1D0_2(3), 'xc', 'LineWidth', 3);
        str = regexp(ctx.cfg.source, '/', 'split'); % to get only g-code file name
        title({str{end}, 'No solution', ...
            ['Lines: ', num2str(line1), ' ', num2str(line2)]}, 'Interpreter', 'none');
        axis equal;
        camproj('perspective');
    end
    end
    
end
    CurvStruct_T.Info.gcode_source_line = line2;    
    CurvStruct_T.Info.SpindleSpeed = min(CurvStruct1.Info.SpindleSpeed, CurvStruct2.Info.SpindleSpeed); 
    if( coder.target("MATLAB") )
        check_continuity( ctx, CurvStruct1_C, CurvStruct_T );
        check_continuity( ctx, CurvStruct_T, CurvStruct2_C );
    end
end


function [] = check_continuity( ctx, CurvStruct1, CurvStruct2 )
    tol = 1E-6;
    [ r11, r1d1, r1dd1 ] = EvalCurvStruct( ctx, CurvStruct1, 1 );
    [ r21, r2d1, r2dd1 ] = EvalCurvStruct( ctx, CurvStruct2, 0 );
    
%     [t1F, ~,  kappa1F] = CalcFrenet( r1d1, r1dd1 );
%     [t2F, ~,  kappa2F] = CalcFrenet( r2d1, r2dd1 );
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