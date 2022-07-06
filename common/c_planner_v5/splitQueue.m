function ctx = splitQueue( ctx )

if ctx.q_smooth.isempty(), return; end

DebugLog( DebugCfg.Validate,        'Splitting...\n' );
DebugLog( DebugCfg.OptimProgress,   'Splitting...\n' );


N = ctx.q_smooth.size;

for k = 1 : N
    ctx = splitCurvStruct( ctx, ctx.q_smooth.get( k ) );
end

checkZSpdmode( ctx.q_split );

end

function checkZSpdmode( queue )
N = queue.size;
ok = 0;

for k = 1 : N-1
    ok = 1;

    zspdmode1 = queue.get( k ).Info.zspdmode; 
    zspdmode2 = queue.get( k+1 ).Info.zspdmode;

    if( ( ( zspdmode1 == ZSpdMode.NN || zspdmode1 == ZSpdMode.ZN ) && ( zspdmode2 == ZSpdMode.NN || zspdmode2 == ZSpdMode.NZ ) ) || ...
        ( ( zspdmode1 == ZSpdMode.NZ || zspdmode1 == ZSpdMode.ZZ ) && ( zspdmode2 == ZSpdMode.ZN || zspdmode2 == ZSpdMode.ZZ ) ) )
        ok = ok+1;
    end
end

assert( ok ~= N, mfilename + ".m : splitted zspdmode failed " );

end