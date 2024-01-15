
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConfigSetSource.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "ConfigSetSource.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "coder_bounded_array.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// function [ cfg ] = ConfigSetSource( cfg, filename )
//
// ConfigSetSource : Set the path to the G code file.
//
//  Inputs :
//    cfg         : The structure of configuration of the compuational chain
//    filename    : The path to the G code to use
//
//  Outputs :
//    cfg         : The structure of configuration of the compuational chain
//
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
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'ConfigSetSource:12' N = size(filename, 2);
    // 'ConfigSetSource:13' cfg.source(1:N) = filename;
    if (filename_size[1] < 1) {
        loop_ub = 0;
    } else {
        loop_ub = filename_size[1];
    }
    if (loop_ub - 1 >= 0) {
        std::copy(&filename_data[0], &filename_data[loop_ub], &cfg->source.data[0]);
    }
    // 'ConfigSetSource:14' cfg.source(N+1:end) = 0;
    if (filename_size[1] + 1 > cfg->source.size[1]) {
        i = 0;
        i1 = 0;
    } else {
        i = filename_size[1];
        i1 = cfg->source.size[1];
    }
    b_loop_ub = i1 - i;
    if (b_loop_ub - 1 >= 0) {
        std::memset(&cfg->source.data[i], 0, ((b_loop_ub + i) - i) * sizeof(char));
    }
}

} // namespace ocn

//
// File trailer for ConfigSetSource.cpp
//
// [EOF]
//
