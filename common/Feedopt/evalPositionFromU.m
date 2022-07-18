function  [ r0D ] = evalPositionFromU( cfg, curv, spline, u )
    %#codegen
    coder.inline( "never" );
    r0D = EvalCurvStructNoCtx( cfg, curv, spline, u );
end