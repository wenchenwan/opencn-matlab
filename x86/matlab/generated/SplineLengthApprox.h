//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApprox.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

#ifndef SPLINELENGTHAPPROX_H
#define SPLINELENGTHAPPROX_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
class queue_coder;

}

// Function Declarations
namespace ocn {
double SplineLengthApprox(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                          int Curv_sp_index, const double u0_tilda_data[],
                          const int u0_tilda_size[2], double u1_tilda);

double SplineLengthApprox(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                          int Curv_sp_index, double u0_tilda, const double u1_tilda_data[],
                          const int u1_tilda_size[2]);

void SplineLengthApprox(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                        int Curv_sp_index, double u0_tilda, double u1_tilda, double *L,
                        ::coder::array<double, 2U> &Integrand,
                        ::coder::array<double, 2U> &u_mid_tilda,
                        ::coder::array<double, 2U> &du_tilda);

double SplineLengthApprox(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                          int Curv_sp_index, double u0_tilda, double u1_tilda);

} // namespace ocn

#endif
//
// File trailer for SplineLengthApprox.h
//
// [EOF]
//
