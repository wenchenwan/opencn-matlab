
function ctx = smoothCurvStructs(ctx)
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
    CurvStruct1 = ctx.q_compress.get(k);  % get current curv in q_compress
    while k < Ncrv
        NextCurv = ctx.q_compress.get(k+1); % get next curv in q_compress
        % Check neither of the two curves has a zero speed.
        if ( CurvStruct1.Info.zspdmode == ZSpdMode.NN || CurvStruct1.Info.zspdmode == ZSpdMode.ZN ) ...
           && ( NextCurv.Info.zspdmode == ZSpdMode.NN || NextCurv.Info.zspdmode == ZSpdMode.NZ )

            [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status] = ...
                calcTransition(ctx, CurvStruct1, NextCurv);
            
            if status == TransitionResult.Ok
                ctx.q_smooth.push(CurvStruct1_C);
                ctx.q_smooth.push(CurvStruct_T);
                CurvStruct1 = CurvStruct2_C;
            elseif status == TransitionResult.Collinear
                ctx.q_smooth.push(CurvStruct1);
                CurvStruct1 = NextCurv;
            else % If the transition fails, force a zero-stop
                CurvStruct1.Info.zspdmode = ZSpdMode.NZ;
                NextCurv.Info.zspdmode = ZSpdMode.ZN;
                [CurvStruct1_C, CurvStruct2_C] = cutZeroEnd(ctx, CurvStruct1);
                [CurvStruct3_C, CurvStruct4_C] = cutZeroStart(ctx, NextCurv);
                ctx.q_smooth.push(CurvStruct1_C);
                ctx.q_smooth.push(CurvStruct2_C);
                ctx.q_smooth.push(CurvStruct3_C);                
                CurvStruct1 = CurvStruct4_C;
                
                ctx.forced_stop = ctx.forced_stop + 1;
            end
            k = k + 1;
        else
            ctx.programmed_stop = ctx.programmed_stop + 1;
            ctx.q_smooth.push(CurvStruct1);
            CurvStruct1 = NextCurv;
            k = k + 1;
        end
    end
    
    ctx.q_smooth.push(CurvStruct1);

elseif Ncrv==1
    CurvStruct1 = ctx.q_compress.get(1);
    if CurvStruct1.Info.zspdmode == ZSpdMode.ZZ
        ctx.q_smooth.push(CurvStruct1);
    else
        c_assert(false, 'Single CurvStruct was not ZZ');
    end
else
    c_assert(false, 'Compressing queue is empty!');
end

end
