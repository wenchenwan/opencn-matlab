#pragma once

#ifdef MATLAB_MEX_FILE
    #include <ReadGCode_mex.h>
#else
    #include <ReadGCode.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef RS274_DEV
#include <opencn/uapi/feedopt.h>
#endif

#include <soo/uapi/debug.h>

#ifdef __cplusplus
} // extern C
#endif


