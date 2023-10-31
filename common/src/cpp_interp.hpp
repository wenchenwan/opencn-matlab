#pragma once

#include <matlab_headers.h>

ocn::ReadGCodeError cpp_interp_init(const char* filename, ocn::MsgStruct* msg_struct);
ocn::ReadGCodeError cpp_interp_read(ocn::CurvStruct* curv_struct, ocn::MsgStruct* msg_struct );
bool                cpp_interp_loaded(ocn::MsgStruct* msg_struct);


