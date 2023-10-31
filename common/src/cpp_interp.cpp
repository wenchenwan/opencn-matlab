#include "cpp_interp.hpp"

#ifndef MATLAB_MEX_FILE
#include "rs274ngc_interp.hh"
#include "interp_return.hh"
#else
#include "src/rs274ngc_interp.hh"
#include "src/interp_return.hh"
#endif

#include <unistd.h>
#include <string.h>

namespace {
Interp interp;
bool was_init;
ocn::CurvStruct curv;
char buffer[1024];
}

bool cpp_check_status_error( ocn::ReadGCodeError status )
{
    return (status > ocn::ReadGCodeError_InterpEndFile);
}

void cpp_write_error_msg( ocn::MsgStruct* msg_struct, const char* msg_ptr ){   
    auto msg_size = strlen(msg_ptr);
    msg_size = (msg_size <  msg_struct->size ? msg_size : msg_struct->size );

    for( auto j=0 ; j < msg_size; j++ )
        msg_struct->msg[j] = msg_ptr[j];
    msg_struct->msg[msg_size] = '\0';
}

bool cpp_interp_loaded( ocn::MsgStruct* msg_struct ) {
    static const char ERROR_MSG_FILE_NOT_OPEN[] = "cpp_interp_loaded: File is not open...\n";

    if( !was_init )
        cpp_write_error_msg( msg_struct, ERROR_MSG_FILE_NOT_OPEN );

    return was_init;
}

ocn::ReadGCodeError cpp_interp_init(const char* filename, ocn::MsgStruct* msg_struct) {
    static const char ERROR_MSG_PATH[] = "cpp_interp_init: Failed to get current path\n";
    static const char ERROR_MSG_FILE_NOT_OPEN[] = "cpp_interp_init: Failed to open gcode file\n";
    static const char ERROR_MSG_FAILED[] = "cpp_interp_init: Something went wrong\n";
    
    was_init = false;

    char* path = getcwd(buffer, sizeof(buffer));
    if (!path) {
        cpp_write_error_msg( msg_struct, ERROR_MSG_PATH );
        return ocn::ReadGCodeError_InterpNotOpen;
    }

    auto status = (ocn::ReadGCodeError)interp.init();

    if ( cpp_check_status_error( status ) ) {
        cpp_write_error_msg( msg_struct, ERROR_MSG_FILE_NOT_OPEN );
        return status;
    }

    status = (ocn::ReadGCodeError)interp.open( filename );

	was_init = !cpp_check_status_error( status );
    
    if( !was_init )
        cpp_write_error_msg( msg_struct, ERROR_MSG_FAILED );

    return status;
}



ocn::ReadGCodeError cpp_interp_read(ocn::CurvStruct* curv_struct, ocn::MsgStruct* msg_struct ) {
    curv.Info.Type  = ocn::CurveType_None;
    auto status     = (ocn::ReadGCodeError)interp.read();
    
    *curv_struct    = curv;
    curv_struct->Info.gcode_source_line = interp.line();

    cpp_write_error_msg( msg_struct, interp.getSavedError() );
    interp.setSavedError("");
            
    if ( cpp_check_status_error( status ) )
        return status;
    
	status          = (ocn::ReadGCodeError)interp.execute();
    *curv_struct    = curv;
    curv_struct->Info.gcode_source_line = interp.line();

    
    cpp_write_error_msg( msg_struct, interp.getSavedError() );
    interp.setSavedError("");

    if ( cpp_check_status_error( status ) )
        return status;
    
   return status;
}

void push_curv_struct(const ocn::CurvStruct* curv_struct) {
    // printf("push_curv_struct: type = %d\n", curv_struct->Type);
    curv                        = *curv_struct;
// 	ocn::CopyCurvStruct(curv_struct, &curv);
}
