#pragma once

#include <matlab_headers.h>

int cpp_interp_init(const char* filename);
int cpp_interp_read(ocn::CurvStruct* curv_struct);
int cpp_interp_loaded();


