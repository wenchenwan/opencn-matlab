function ctx = SplitCurvStructs(ctx)

if ctx.q_smooth.isempty()%ctx.q_smooth.isempty() IL FAUDRA REMETTRE Q_SMOOTH
    return;
end

N = ctx.q_smooth.size;%ctx.q_smooth.size; IL FAUDRA REMETTRE Q_SMOOTH

DebugLog(DebugCfg.Validate, 'Splitting...\n');
DebugLog(DebugCfg.OptimProgress, 'Splitting...\n');

for k = 1:N
    ctx = SplitCurvStruct(ctx, ctx.q_smooth.get(k));%ctx.q_smooth.get(k));IL FAUDRA REMETTRE Q_SMOOTH
end

end
