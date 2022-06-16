function [ curv1, curv2 ] = cutZeroEnd( ctx, curv )
% cutZeroEnd : Cut the end of the given to handle the zero speed.
    u  = cutCurvStructU( ctx, curv, 1, ctx.cfg.LSplitZero, true );
    
    if( u >= curv.b_param + curv.a_param || u <= curv.b_param)
        u = curv.a_param / 2 + curv.b_param;
    end

    curv2                   = curv;
    curv2.UseConstJerk      = true;
    curv2.b_param           = u;
    curv2.a_param           = curv.a_param  + curv.b_param - curv2.b_param;
    [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2, true );
    curv2.ConstJerk         = jps;
    curv2.Info.zspdmode     = ZSpdMode.NZ;
    
    curv1                   = curv;
    curv1.a_param           = u - curv1.b_param;
    curv1.UseConstJerk      = false;
    curv1.Info.gcode_source_line = curv.Info.gcode_source_line;
    
    if( isAZeroStart( curv ) )
        curv1.Info.zspdmode = ZSpdMode.ZN;
    else
        curv1.Info.zspdmode = ZSpdMode.NN;
    end
    
    if( coder.target("MATLAB") )
        check_continuity( ctx, curv, curv1, curv2 );
    end
end

function [] = check_continuity( ctx, curv, curv1, curv2 )
    curv_vec    = [ curv; curv1; curv2 ];
    u_vec       = [ 0, 1 ];
    r           = repmat( curv.R0( ctx.cfg.maskTot ), 1, 2, 3 );
    rd          = r;
    rdd         = r;

    for j = 1 : 3
        [ r( :, :, j ) , rd( :, :, j ), rdd( :, :, j ) ] = ...
                            EvalCurvStruct( ctx, curv_vec( j ),  u_vec );
        rd( :, :, j )    = rd( :, :, j )  / curv_vec( j ).a_param;
        rdd( :, :, j )   = rdd( :, :, j ) / curv_vec( j ).a_param^2;
   
    end

    ind1 = [ 1, 1; 1, 2; 2, 2 ];
    ind2 = [ 2, 1; 3, 2; 3, 1 ];
    
    for j = 1 : 3
        r1   = r( : , ind1( j, 2 ), ind1( j, 1 ) );
        r1d  = rd( : , ind1( j, 2 ), ind1( j, 1 ) );
        r1dd = rdd( : , ind1( j, 2 ), ind1( j, 1 ) );
        r2   = r( : , ind2( j, 2 ), ind2( j, 1 ) );
        r2d  = rd( : , ind2( j, 2 ), ind2( j, 1 ) );
        r2dd = rdd( : , ind2( j, 2 ), ind2( j, 1 ) );
        assert_continuity( r1, r1d, r1dd, r2, r2d, r2dd );
    end
    
end


function [] = assert_continuity( r1, r1d, r1dd, r2, r2d, r2dd )
    diff_r      = abs( r1    -r2 );
    diff_rd     = abs( r1d   -r2d );
    diff_rdd    = abs( r1dd  -r2dd );

    tol = 1E-12;

    assert( all( diff_r    < tol ), mfilename + ...
                        ".m : continuity C0 failed " + mat2str( diff_r' ) );
    assert( all( diff_rd   < tol ), mfilename + ...
                        " : continuity C1 failed"  + mat2str( diff_rd' ) );
    assert( all( diff_rdd  < tol ), mfilename + ...
                        " : continuity C2 failed"  + mat2str( diff_rdd' ) );
end