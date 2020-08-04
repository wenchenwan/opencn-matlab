#pragma once



#if defined(MEX_FEEDOPTPLANRUN)
    #include <FeedoptPlanRun_mex.h>
#else
    #if defined(MEX_READGCODE)
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


