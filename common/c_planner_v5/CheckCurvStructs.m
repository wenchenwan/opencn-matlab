function ctx = CheckCurvStructs(ctx)

N = ctx.q_gcode.size;

DebugLog(DebugCfg.Validate, 'Checking for cusps...\n');
DebugLog(DebugCfg.OptimProgress, 'Checking for cusps...\n');

for k = 1:N-1
    Curv1 = ctx.q_gcode.get(k);
    Curv2 = ctx.q_gcode.get(k+1);
    
    [~, r0D1] = EvalCurvStruct( ctx, Curv1, 1 );
    [~, r1D1] = EvalCurvStruct( ctx, Curv2, 0 );
    
    if iscusp(r0D1, r1D1, ctx.cfg.CuspThreshold)
        switch Curv1.Info.zspdmode
            case ZSpdMode.NN
                Curv1.Info.zspdmode = ZSpdMode.NZ;
            case ZSpdMode.ZN
                Curv1.Info.zspdmode = ZSpdMode.ZZ;
            case ZSpdMode.NZ
                % Nothing to do
            case ZSpdMode.ZZ
                % Nothing to do
        end
        
        switch Curv2.Info.zspdmode
            case ZSpdMode.NN
                Curv2.Info.zspdmode = ZSpdMode.ZN;
            case ZSpdMode.ZN
                % Nothing to do
            case ZSpdMode.NZ
                Curv2.Info.zspdmode = ZSpdMode.ZZ;
            case ZSpdMode.ZZ
                % Nothing to do
        end
        
        ctx.q_gcode.set(k,   Curv1);
        ctx.q_gcode.set(k+1, Curv2);
    end
end    
end