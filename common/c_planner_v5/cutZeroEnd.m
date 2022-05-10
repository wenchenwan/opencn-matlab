function [ CurvStruct1, CurvStruct2 ] = cutZeroEnd( ctx, CurvStruct )
% cutZeroEnd : Cut the end of the given to handle the zero speed.
    [ u, jps ] = zeroSpeedCurv( ctx, CurvStruct, true );

    CurvStruct1 = CurvStruct;
    CurvStruct1.b_param = 0;
    CurvStruct1.a_param = u;
    CurvStruct1.UseConstJerk = false;
    CurvStruct1.Info.zspdmode = ZSpdMode.NN;
    CurvStruct1.gcode_source_line = CurvStruct.Info.gcode_source_line;
    
    CurvStruct2 = CurvStruct1;
    CurvStruct2.UseConstJerk = true;
    CurvStruct2.ConstJerk = jps;
    CurvStruct2.b_param = CurvStruct1.a_param + CurvStruct1.b_param;
    CurvStruct2.a_param = 1 - CurvStruct2.b_param;
    CurvStruct2.Info.zspdmode = ZSpdMode.NZ;
    
    if( coder.target("MATLAB") )
%         check_continuity( ctx, CurvStruct1, CurvStruct2 );
    end
end

function [] = check_continuity( ctx, CurvStruct1, CurvStruct2 )
    [ r11, r1d1, r1dd1 ] = EvalCurvStruct( ctx, CurvStruct1, 1 );
    [ r21, r2d1, r2dd1 ] = EvalCurvStruct( ctx, CurvStruct2, 0 );

    r1d1    = r1d1 / CurvStruct1.a_param;
    r1dd1   = r1dd1 / CurvStruct1.a_param^2;
    r2d1    = r2d1 / CurvStruct2.a_param;
    r2dd1   = r2dd1 / CurvStruct2.a_param^2;

    diff_r      = abs( r11    -r21 );
    diff_rd     = abs( r1d1   -r2d1 );
    diff_rdd    = abs( r1dd1  -r2dd1 );

    tol = 1E-12;

    assert( all( diff_r    < tol ), mfilename + ...
                        ".m : continuity C0 failed " + mat2str( diff_r' ) );
    assert( all( diff_rd   < tol ), mfilename + ...
                        " : continuity C1 failed"  + mat2str( diff_rd' ) );
    assert( all( diff_rdd  < tol ), mfilename + ...
                        " : continuity C2 failed"  + mat2str( diff_rdd' ) );
end