function ctx = ExpandZeroStructs(ctx)

% We replace each sequence of small g-code segments with a B-Spline
% of degree 3
% A special queue is dedicated to the splines, ctx.q_splines

if ctx.q_gcode.isempty()
    return;
end

Ncrv = double(ctx.q_gcode.size);
DebugLog(DebugCfg.Transitions, 'Expanding ...\n');

for k = 1:Ncrv
    Curv = ctx.q_gcode.get(k);

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

end

end

