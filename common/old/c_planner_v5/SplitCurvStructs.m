function ctx = SplitCurvStructs(ctx)

if ctx.q_smooth.isempty()%ctx.q_smooth.isempty() IL FAUDRA REMETTRE Q_SMOOTH
    return;
end

N = ctx.q_smooth.size;

DebugLog(DebugCfg.Validate, 'Splitting...\n');
DebugLog(DebugCfg.OptimProgress, 'Splitting...\n');

for k = 1:N
    CurvStruct = ctx.q_smooth.get(k);
%     CurvStruct.Info.Type
%     CurvStruct.R0'
%     CurvStruct.R1'
    ctx = SplitCurvStruct(ctx, CurvStruct);
end

% Check_zspdmode(ctx); WIP

end
