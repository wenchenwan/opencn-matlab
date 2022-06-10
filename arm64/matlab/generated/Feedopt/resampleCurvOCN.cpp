//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: resampleCurvOCN.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

// Include Files
#include "resampleCurvOCN.h"
#include "ResampleStateClass.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types3.h"
#include "resampleCurv.h"
#include "coder_array.h"

// Function Definitions
//
// function [ state ] = resampleCurvOCN(state, Bl, curv_mode, ...
//     coeff, constJerk, dt, ...
//     curv_a, curv_b)
//
// resampleCurvOCN :
//  Interface for the resampling in ocn
//
// Arguments    : ResampleStateClass *state
//                const BaseSplineStruct *Bl
//                ZSpdMode curv_mode
//                const ::coder::array<double, 1U> &coeff
//                double constJerk
//                double dt
//                double curv_a
//                double curv_b
// Return Type  : void
//
namespace ocn {
void resampleCurvOCN(ResampleStateClass *state, const BaseSplineStruct *Bl, ZSpdMode curv_mode,
                     const ::coder::array<double, 1U> &coeff, double constJerk, double dt, double,
                     double)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'resampleCurvOCN:6' [ state ] = resampleCurv(state, Bl, curv_mode, coeff, constJerk, dt, ...
    // 'resampleCurvOCN:7'             curv_a, curv_b);
    resampleCurv(state, Bl->handle, curv_mode, coeff, constJerk, dt);
}

} // namespace ocn

//
// File trailer for resampleCurvOCN.cpp
//
// [EOF]
//
