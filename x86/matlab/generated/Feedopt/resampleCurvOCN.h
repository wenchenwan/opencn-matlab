//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: resampleCurvOCN.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 12:49:58
//

#ifndef RESAMPLECURVOCN_H
#define RESAMPLECURVOCN_H

// Include Files
#include "ResampleStateClass.h"
#include "opencn_matlab_types3.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void resampleCurvOCN(ResampleStateClass *state, const BaseSplineStruct *Bl,
                            ZSpdMode curv_mode, const ::coder::array<double, 1U> &coeff,
                            double constJerk, double dt, double curv_a, double curv_b,
                            const ::coder::array<double, 1U> &GaussLegendreX,
                            const ::coder::array<double, 1U> &GaussLegendreW);

}

#endif
//
// File trailer for resampleCurvOCN.h
//
// [EOF]
//
