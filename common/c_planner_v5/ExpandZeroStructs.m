function ctx = ExpandZeroStructs(ctx)
% ExpandZeroStructs : 
% - Is feeded by the queue : q_gcode
% - Check speed boundaries conditions (ZZ,ZN,NZ,NN) and split the curves if
% they contain a zero speed.
% - Fill the queue : q_compress
% 
% Note : No compression is performed

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

