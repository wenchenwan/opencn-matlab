#pragma once

// #define MEX_FEEDOPTPLANRUN

#ifndef MEX_FEEDOPTPLANRUN
    #define MEX_READGCODE
#endif

#ifdef MEX_FEEDOPTPLANRUN
    #include <FeedoptPlanRun_mex.h>
#else
    #ifdef MEX_READGCODE
        #include <ReadGCode_mex.h>
    #endif
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


