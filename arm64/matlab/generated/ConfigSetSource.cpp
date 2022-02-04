//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConfigSetSource.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

// Include Files
#include "ConfigSetSource.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// Arguments    : FeedoptConfig *cfg
//                const char filename_data[]
//                const int filename_size[2]
// Return Type  : void
//
namespace ocn {
void ConfigSetSource(FeedoptConfig *cfg, const char filename_data[], const int filename_size[2])
{
    int b_loop_ub;
    int i;
    int i1;
    int loop_ub;
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    if (1 > filename_size[1]) {
        loop_ub = 0;
    } else {
        loop_ub = filename_size[1];
    }
    if (0 <= loop_ub - 1) {
        std::copy(&filename_data[0], &filename_data[loop_ub], &cfg->source[0]);
    }
    if (filename_size[1] + 1 > 1024) {
        i = 0;
        i1 = -1;
    } else {
        i = filename_size[1];
        i1 = 1023;
    }
    b_loop_ub = (i1 - i) + 1;
    if (0 <= b_loop_ub - 1) {
        std::memset(&cfg->source[i], 0, ((b_loop_ub + i) - i) * sizeof(char));
    }
}

} // namespace ocn

//
// File trailer for ConfigSetSource.cpp
//
// [EOF]
//
