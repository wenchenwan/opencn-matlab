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

DebugLog('Compressing...\n');

% Satisfy coder
% -------------
if coder.target('rtw') || coder.target('mex')
    pvec = zeros(3, 0);
    coder.varsize('pvec', [3, Inf], [0, 1]);
    CurvStruct1 = ctx.q_gcode.get(1);
end
% -------------

k=1;
while k <= Ncrv
    Curv = ctx.q_gcode.get(k);
    if (LengthCurv(ctx, Curv, 0, 1)>=Length_Threshold) || (Curv.zspdmode~=ZSpdMode.NN)
        if CumulatedLength == 0
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
            else
                ctx.q_compress.push(Curv);
            end
        else                
            if size(pvec, 2) > 2
                SplineCurve = ConstrCurvStructType;
                SplineCurve.sp=CalcBspline_Lee(ctx.cfg, pvec);
                ctx.q_splines.push(SplineCurve);
                spline = ConstrBSplineStruct(pvec, ZSpdMode.NN, Curv.FeedRate);
                spline.gcode_source_line = Curv.gcode_source_line;
                spline.sp_index = int32(spline_index);
                spline_index = spline_index + 1;
                ctx.q_compress.push(spline);
                if Curv.zspdmode == ZSpdMode.NZ
                    [CurvStruct1_C, CurvStruct2_C] = CutZeroEnd(ctx, Curv, k);
                    ctx.q_compress.push(CurvStruct1_C);
                    ctx.q_compress.push(CurvStruct2_C);
                else
                    ctx.q_compress.push(Curv);
                end
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
    elseif (k==Ncrv) && (CumulatedLength ~= 0)
        SplineCurve = ConstrCurvStructType;
        SplineCurve.sp=CalcBspline_Lee(ctx.cfg, pvec);
        ctx.q_splines.push(SplineCurve);
        spline = ConstrBSplineStruct(pvec, ZSpdMode.NN, Curv.FeedRate);
        spline.gcode_source_line = Curv.gcode_source_line;
        spline.sp_index = int32(spline_index);
        ctx.q_compress.push(spline);
    elseif k==1
        ctx.q_compress.push(Curv);
    else
        if CumulatedLength == 0
            P0 = EvalCurvStruct(ctx, Curv, 0);
            pvec = P0;
        end
        CumulatedLength = CumulatedLength + LengthCurv(ctx, Curv, 0, 1);
        P1 = EvalCurvStruct(ctx, Curv, 1);
        pvec = [pvec P1];
    end
    k = k + 1;
end

end

