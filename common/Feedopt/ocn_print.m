function ocn_print( condition, msg, fileName )  
%#codegen
% ocn_print : Custom implementation of the print function. se C++ code for 
% the real time implementation.
%
% Inputs :
%   condition : Enable print
%   msg : Message to print
%   filename : Filename calling the function
%
coder.inline( "never" )

if( ~(coder.target( "MATLAB" ) || coder.target( "MEX" )) )
    my_path = StructTypeName.WDIR + "/src";
    coder.updateBuildInfo( 'addIncludePaths', my_path );
    coder.updateBuildInfo( 'addSourceFiles','ocn_print.cpp', my_path );
    coder.cinclude( 'ocn_print.hpp' );
end

if( condition )
    msg_long = "[" + fileName + "]" + msg;
    
    if( coder.target( "MATLAB" ) || coder.target( "MEX" ) )
        disp( msg_long );
    else
        ocn_msg = constrMsgStruct( msg_long );
        coder.ceval( 'ocn_print_msg', coder.ref( ocn_msg ) );
    end
end
end