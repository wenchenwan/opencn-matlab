#pragma once

#ifdef MATLAB_MEX_FILE
    #include <ReadGCode_mex.h>
#else
    #include <ReadGCode.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if 0
    #ifndef RS274_DEV
    #include <opencn/uapi/feedopt.h>
    #endif
#endif 

#include <soo/uapi/debug.h>

#ifdef __cplusplus
} // extern C
#endif


