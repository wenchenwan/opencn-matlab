
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: resampleCurvOCN.h
//
// MATLAB Coder version            : 5.4
//

#ifndef RESAMPLECURVOCN_H
#define RESAMPLECURVOCN_H

// Include Files
#include "ResampleStateClass.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
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
                            double constJerk, double dt,
                            const ::coder::array<double, 1U> &GaussLegendreX,
                            const ::coder::array<double, 1U> &GaussLegendreW, bool enablePrint);

}

#endif
//
// File trailer for resampleCurvOCN.h
//
// [EOF]
//
