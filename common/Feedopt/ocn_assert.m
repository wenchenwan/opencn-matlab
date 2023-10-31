function ocn_assert( condition, msg, fileName )  %#codegen
coder.inline( "never" )

if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    my_path = StructTypeName.WDIR + "/src";
    coder.updateBuildInfo( 'addIncludePaths', my_path );
    coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    coder.cinclude( 'ocn_error.hpp' );
end

if( ~condition )
    err_msg         = "[" + fileName + "]" + msg + "\n";
    err_msg_char    = [ char(err_msg) 0 ];

    if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        error( err_msg_char );
    else
        ocn_error_msg = constrMsgStruct( err_msg_char );
        coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
    end
end
end