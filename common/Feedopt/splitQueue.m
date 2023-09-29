function ctx = splitQueue( ctx )

if ctx.q_smooth.isempty(), return; end
ctx.k0 = int32( 1 );
DebugLog( DebugCfg.Validate,        'Splitting...\n' );
DebugLog( DebugCfg.OptimProgress,   'Splitting...\n' );


N = ctx.q_smooth.size;

for k = 1 : N
    ctx.k0  = ctx.k0 + 1;
    if(coder.target("MATLAB")), disp( "" + ctx.k0 + "/" + N ); end

    ctx     = splitCurvStruct( ctx, ctx.q_smooth.get( k ) );
end

end