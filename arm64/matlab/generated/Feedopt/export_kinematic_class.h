
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: export_kinematic_class.h
//
// MATLAB Coder version            : 5.4
//

#ifndef EXPORT_KINEMATIC_CLASS_H
#define EXPORT_KINEMATIC_CLASS_H

// Include Files
#include "opencn_matlab_types.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void export_kinematic_class(const FeedoptConfig cfg, const ::coder::array<double, 2U> &vec,
                                   const ::coder::array<double, 2U> &vecd,
                                   const ::coder::array<double, 2U> &vecdd,
                                   const ::coder::array<double, 2U> &vecddd,
                                   ::coder::array<double, 2U> &res,
                                   ::coder::array<double, 2U> &resd,
                                   ::coder::array<double, 2U> &resdd,
                                   ::coder::array<double, 2U> &resddd);

}

#endif
//
// File trailer for export_kinematic_class.h
//
// [EOF]
//
