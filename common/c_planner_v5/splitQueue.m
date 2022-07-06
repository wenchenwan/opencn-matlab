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

curv = queue.get( 1 );

for k = 2 : N
    curvNext = queue.get( k );

    if( isAZeroEnd( curv ) && ~isAZeroStart( curvNext ) || ...
       ~isAZeroEnd( curv ) &&  isAZeroStart( curvNext ) )
        error( mfilename + ".m : splitted zspdmode failed " );
    end

    curv = curvNext;
end


end