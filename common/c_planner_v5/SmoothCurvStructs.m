function ctx = SmoothCurvStructs(ctx)
% Optimal transitions calculation between segments whith G2 continuity

if ctx.q_compress.isempty()
    return;
end

if coder.target('rtw')
    NextCurv = ctx.q_compress.get(1); % to satisfy the coder
end
Ncrv = ctx.q_compress.size;

DebugLog(DebugCfg.Validate, 'Smoothing...\n');
DebugLog(DebugCfg.OptimProgress, 'Smoothing...\n');

k = 1;

if Ncrv > 1
    CurvStruct1 = ctx.q_compress.get(k);
    while k < Ncrv
        NextCurv = ctx.q_compress.get(k+1);
        if CurvStruct1.zspdmode == ZSpdMode.NN && NextCurv.zspdmode == ZSpdMode.NN
            [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status] = ...
                CalcTransition(ctx, CurvStruct1, NextCurv);
            
            if status == TransitionResult.Ok
                ctx.q_smooth.push(CurvStruct1_C);
                ctx.q_smooth.push(CurvStruct_T);
                CurvStruct1 = CurvStruct2_C;
            elseif status == TransitionResult.Collinear
                ctx.q_smooth.push(CurvStruct1);
                CurvStruct1 = NextCurv;
            else
                CurvStruct1.zspdmode = ZSpdMode.NZ;
                NextCurv.zspdmode = ZSpdMode.ZN;
                CurvStruct2 = NextCurv;
%                 SaveTransition;
%                 If the transition fails, force a zero-stop
                [CurvStruct1_C, CurvStruct2_C] = CutZeroEnd(ctx, CurvStruct1, k);
                [CurvStruct3_C, CurvStruct4_C] = CutZeroStart(ctx, NextCurv, k);
                ctx.q_smooth.push(CurvStruct1_C);
                ctx.q_smooth.push(CurvStruct2_C);
                ctx.q_smooth.push(CurvStruct3_C);                
                CurvStruct1 = CurvStruct4_C;
                
                ctx.forced_stop = ctx.forced_stop + 1;
            end
            k = k + 1;
        else
            
            if (CurvStruct1.zspdmode == ZSpdMode.NZ || CurvStruct1.zspdmode == ZSpdMode.ZZ) ...
                    && (NextCurv.zspdmode == ZSpdMode.ZN || NextCurv.zspdmode == ZSpdMode.ZZ)
                ctx.programmed_stop = ctx.programmed_stop + 1;
            end
            
            ctx.q_smooth.push(CurvStruct1);
            CurvStruct1 = NextCurv;
            k = k + 1;
        end
    end
    
    ctx.q_smooth.push(CurvStruct1);

    
elseif Ncrv==1
    CurvStruct1 = ctx.q_compress.get(1);
    if CurvStruct1.zspdmode == ZSpdMode.ZZ
        [CurvStruct1_C, CurvStruct2_C] = CutZeroStart(ctx, CurvStruct1, 1);
        [CurvStruct2_C, CurvStruct3_C] = CutZeroEnd(ctx, CurvStruct2_C, 1);
        ctx.q_smooth.push(CurvStruct1_C);
        ctx.q_smooth.push(CurvStruct2_C);
        ctx.q_smooth.push(CurvStruct3_C);
    else
        c_assert(false, 'Single CurvStruct was not ZZ');
    end
else
    c_assert(false, 'Compressing queue is empty!');
end

end
