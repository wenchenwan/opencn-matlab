//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: kin_J2P_ra_xyzbc.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Sep-2023 09:32:18
//

#ifndef KIN_J2P_RA_XYZBC_H
#define KIN_J2P_RA_XYZBC_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void kin_J2P_ra_xyzbc(const ::coder::array<double, 1U> &in1, const ::coder::array<double, 1U> &in2,
                      const ::coder::array<double, 1U> &in3, const double in4_data[],
                      double J2P_ra[5][5]);

}

#endif
//
// File trailer for kin_J2P_ra_xyzbc.h
//
// [EOF]
//
