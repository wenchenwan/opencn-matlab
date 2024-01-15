function ocn_assert( condition, msg, fileName )  
%#codegen
% ocn_assert: Custom assert function. Use C++ code for the real time
% implementation. An error is throw when assertion fails.
%
% Inputs :
%   condition : Assertion equation.
%   msg : Error message
%   fileName : The calling filename
%
coder.inline( "never" )

if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    my_path = StructTypeName.WDIR + "/src";
    coder.updateBuildInfo( 'addIncludePaths', my_path );
    coder.updateBuildInfo( 'addSourceFiles','ocn_error.cpp', my_path );
    coder.cinclude( 'ocn_error.hpp' );
end

if( ~condition )
    err_msg         = "[" + fileName + "]" + msg;
    err_msg_char    = [ char( err_msg + "\n" ) 0 ];

    if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
%         messagePrompt( "An error occurs...\n" + err_msg + "Do want to continue ?" );
        error( err_msg );
    else
        ocn_error_msg = constrMsgStruct( err_msg_char );
        coder.ceval( 'ocn_throw_error', coder.ref( ocn_error_msg ) )
    end
end
end
