function ctx = SplitCurvStructs(ctx)

if ctx.q_smooth.isempty()
    return;
end

N = ctx.q_smooth.size;

DebugLog(DebugCfg.Validate, 'Splitting...\n');
DebugLog(DebugCfg.OptimProgress, 'Splitting...\n');

for k = 1:N
    ctx = SplitCurvStruct(ctx, ctx.q_smooth.get(k));
end

end
