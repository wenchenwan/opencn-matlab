//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: resampleCurvOCN.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 13:07:08
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
// function [ state ] = resampleCurvOCN( state, Bl, curv_mode, ...
//     coeff, constJerk, dt, ...
//     curv_a, curv_b, GaussLegendreX, GaussLegendreW )
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
//                const ::coder::array<double, 1U> &GaussLegendreX
//                const ::coder::array<double, 1U> &GaussLegendreW
// Return Type  : void
//
namespace ocn {
void resampleCurvOCN(ResampleStateClass *state, const BaseSplineStruct *Bl, ZSpdMode curv_mode,
                     const ::coder::array<double, 1U> &coeff, double constJerk, double dt, double,
                     double, const ::coder::array<double, 1U> &GaussLegendreX,
                     const ::coder::array<double, 1U> &GaussLegendreW)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'resampleCurvOCN:6' [ state ] = resampleCurv(state, Bl, curv_mode, coeff, constJerk, dt, ...
    // 'resampleCurvOCN:7'             curv_a, curv_b, GaussLegendreX, GaussLegendreW );
    resampleCurv(state, Bl->handle, curv_mode, coeff, constJerk, dt, GaussLegendreX,
                 GaussLegendreW);
}

} // namespace ocn

//
// File trailer for resampleCurvOCN.cpp
//
// [EOF]
//
