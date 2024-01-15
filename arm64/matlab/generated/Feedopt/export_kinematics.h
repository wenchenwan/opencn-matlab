
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: export_kinematics.h
//
// MATLAB Coder version            : 5.4
//

#ifndef EXPORT_KINEMATICS_H
#define EXPORT_KINEMATICS_H

// Include Files
#include "Kinematics.h"
#include "opencn_matlab_types.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void export_kinematics(const FeedoptConfig cfg, const double Rvec_data[],
                              const int Rvec_size[1], const ::coder::array<double, 2U> &RMatrix,
                              Kinematics *kin, double params_data[], int params_size[1],
                              char type[8], double resVec_data[], int resVec_size[1],
                              ::coder::array<double, 2U> &resMatrix);

}

#endif
//
// File trailer for export_kinematics.h
//
// [EOF]
//
