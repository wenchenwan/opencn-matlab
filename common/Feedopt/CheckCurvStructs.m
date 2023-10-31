function [ ctx ] = CheckCurvStructs( ctx )
ctx.k0 = int32( 1 );
N = ctx.q_gcode.size;

DebugLog( DebugCfg.Validate, 'Checking for cusps...\n' );
DebugLog( DebugCfg.OptimProgress, 'Checking for cusps...\n' );

curv1 = ctx.q_gcode.get( 1 );
for k = 2 : N
    ctx.k0  = ctx.k0 + 1;
    if(coder.target("MATLAB")), disp( "" + ctx.k0 + "/" + N ); end
    curv2   = ctx.q_gcode.get( k );

    % Detect cusp in piece frame
    [~, r0D1] = EvalCurvStructInPieceFrame( ctx, curv1, 1 );
    [~, r1D1] = EvalCurvStructInPieceFrame( ctx, curv2, 0 );

    if ( ~isAZeroEnd( curv1 ) ) && ... 
        iscusp( r0D1( ctx.cfg.indCart ), r1D1( ctx.cfg.indCart ), ...
                ctx.cfg.Cusp.CuspThreshold )

        switch curv1.Info.zspdmode
            case ZSpdMode.NN
                curv1.Info.zspdmode = ZSpdMode.NZ;
            case ZSpdMode.ZN
                curv1.Info.zspdmode = ZSpdMode.ZZ;
        end
        
        switch curv2.Info.zspdmode
            case ZSpdMode.NN
                curv2.Info.zspdmode = ZSpdMode.ZN;
            case ZSpdMode.NZ
                curv2.Info.zspdmode = ZSpdMode.ZZ;
        end
        
        ctx.q_gcode.set( k - 1,   curv1 );
        ctx.q_gcode.set( k, curv2 );
        
        if( coder.target( "MATLAB" ) )
            DebugCusp.getInstance.add( curv1, curv2 );
        end
    end

    curv1 = curv2;
end    
end