function ctx = splitQueue( ctx )

if ctx.q_smooth.isempty(), return; end

DebugLog( DebugCfg.Validate,        'Splitting...\n' );
DebugLog( DebugCfg.OptimProgress,   'Splitting...\n' );


N = ctx.q_smooth.size;

for k = 1 : N
    ctx = splitCurvStruct( ctx, ctx.q_smooth.get( k ) );
end

end
