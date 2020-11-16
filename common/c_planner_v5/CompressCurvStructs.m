function ctx = CompressCurvStructs(ctx)
% We replace each sequence of small g-code segments with a B-Spline
% of degree 3
% A special queue is dedicated to the splines, ctx.q_splines

if ctx.q_gcode.isempty()
    return;
end

spline_index = ctx.q_splines.size() + 1;

Ncrv = ctx.q_gcode.size;

CumulatedLength = 0;
Length_Threshold = ctx.cfg.LThreshold; % [mm]

DebugLog(DebugCfg.Transitions, 'Compressing...\n');
spindle_speed = 75000;

% Satisfy coder
% -------------
if coder.target('rtw') || coder.target('mex')
    pvec = zeros(3, 0);
    coder.varsize('pvec', [3, Inf], [0, 1]);
    CurvStruct1 = ctx.q_gcode.get(1);
end
% -------------

%  ||...
%             (CumulatedLength > 0 && ~CurvCollinear(ctx, ctx.q_gcode.get(k-1), Curv, ctx.cfg.Compressing.MaxCollinearityDegrees)) 

k=1;
while k <= Ncrv
    Curv = ctx.q_gcode.get(k);
    % If the next curve segment is too long for compressing or it is not an NN,
    % we need to stop growing the compressing list and create the spline
    Collinear = false;
    if k > 1
        Collinear = CurvCollinear(ctx, ctx.q_gcode.get(k-1), Curv, ctx.cfg.Compressing.ColTol);
    end
    
    if (LengthCurv(ctx, Curv, 0, 1)>=Length_Threshold) || ...
            (Curv.zspdmode~=ZSpdMode.NN) ||...
            (CumulatedLength == 0 && ~Collinear)

        % If the cumulated length is zero, no compressing is on-going and we can
        % treat the segment individually 
        if CumulatedLength == 0
            
            % If the segment is not a normal one (Nonzero, Nonzero), it needs
            % to be split
            if Curv.zspdmode == ZSpdMode.ZN
                [CurvStruct1_C, CurvStruct2_C] = CutZeroStart(ctx, Curv, k);
                ctx.q_compress.push(CurvStruct1_C);
                ctx.q_compress.push(CurvStruct2_C);
            elseif Curv.zspdmode == ZSpdMode.NZ
                [CurvStruct1_C, CurvStruct2_C] = CutZeroEnd(ctx, Curv, k);
                ctx.q_compress.push(CurvStruct1_C);
                ctx.q_compress.push(CurvStruct2_C);
            elseif Curv.zspdmode == ZSpdMode.ZZ
                [CurvStruct1_C, CurvStruct2_C] = CutZeroStart(ctx, Curv, k);
                [CurvStruct2_C, CurvStruct3_C] = CutZeroEnd(ctx, CurvStruct2_C, k);
                ctx.q_compress.push(CurvStruct1_C);
                ctx.q_compress.push(CurvStruct2_C);
                ctx.q_compress.push(CurvStruct3_C);

            % If the segment is normal, (Nonzero, Nonzero), it can be pushed
            % as-is into the output list
            else
                ctx.q_compress.push(Curv);
            end

        % If there was an on-going compression
        else           
            % We have more than 2 points, thus constructing a spline 
            % is warranted     
            if size(pvec, 2) > 2
                SplineCurve = ConstrCurvStructType;
                SplineCurve.sp=CalcBspline_Lee(ctx.cfg, pvec);
                ctx.q_splines.push(SplineCurve);
                spline = ConstrBSplineStruct(pvec, ZSpdMode.NN, Curv.FeedRate);
                spline.gcode_source_line = Curv.gcode_source_line;
                spline.sp_index = int32(spline_index);
                spline_index = spline_index + 1;
                spline.SpindleSpeed = spindle_speed;
                spindle_speed = 75000;
                ctx.q_compress.push(spline);
                if Curv.zspdmode == ZSpdMode.NZ
                    [CurvStruct1_C, CurvStruct2_C] = CutZeroEnd(ctx, Curv, k);
                    ctx.q_compress.push(CurvStruct1_C);
                    ctx.q_compress.push(CurvStruct2_C);
                else
                    ctx.q_compress.push(Curv);
                end
            % With only two points, construct a line
            else
                C = ctx.q_gcode.get(k-1);
                ctx.q_compress.push(C);
                if Curv.zspdmode == ZSpdMode.NZ
                    [CurvStruct1_C, CurvStruct2_C] = CutZeroEnd(ctx, Curv, k);
                    ctx.q_compress.push(CurvStruct1_C);
                    ctx.q_compress.push(CurvStruct2_C);
                else
                    ctx.q_compress.push(Curv);
                end
                C.gcode_source_line=Curv.gcode_source_line;
            end
            CumulatedLength = 0;
        end
    % If this is the last segment and we have something in the
    % compression list, construct the spline
    elseif (k==Ncrv) && (CumulatedLength ~= 0)
        SplineCurve = ConstrCurvStructType;
        SplineCurve.sp=CalcBspline_Lee(ctx.cfg, pvec);
        ctx.q_splines.push(SplineCurve);
        spline = ConstrBSplineStruct(pvec, ZSpdMode.NN, Curv.FeedRate);
        spline.gcode_source_line = Curv.gcode_source_line;
        spline.sp_index = int32(spline_index);
        spline.SpindleSpeed = spindle_speed;
        ctx.q_compress.push(spline);
    
    % If this is the first (and elligible) WHAT
    elseif k==1
        ctx.q_compress.push(Curv);
    
    % In the general case with an elligible segment, add it to the
    % compression list
    else
        if CumulatedLength == 0
            P0 = EvalCurvStruct(ctx, Curv, 0);
            pvec = P0;
            spindle_speed = Curv.SpindleSpeed;
        end
        CumulatedLength = CumulatedLength + LengthCurv(ctx, Curv, 0, 1);
        P1 = EvalCurvStruct(ctx, Curv, 1);
        pvec = [pvec P1];
        spindle_speed = min(spindle_speed, Curv.SpindleSpeed);
    end
    k = k + 1;
end

end

