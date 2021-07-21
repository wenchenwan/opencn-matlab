//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: BuildConstr_v4.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

#ifndef BUILDCONSTR_V4_H
#define BUILDCONSTR_V4_H

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

struct CurvStruct;

namespace coder {
class sparse;

}
} // namespace ocn

// Function Declarations
namespace ocn {
void BuildConstr_v4(const queue_coder *ctx_q_splines, bool ctx_cfg_UseDynamicBreakpoints,
                    bool ctx_cfg_UseLinearBreakpoints, double ctx_cfg_DynamicBreakpointsDistance,
                    int ctx_cfg_SplineDegree, double ctx_cfg_NGridLengthSpline, int ctx_Bl_ncoeff,
                    unsigned long ctx_Bl_handle, const ::coder::array<CurvStruct, 2U> &CurvStructs,
                    const double amax[3], double v_0, double at_0, double v_1, double at_1,
                    ::coder::array<double, 2U> &BasisVal, ::coder::array<double, 2U> &BasisValD,
                    const ::coder::array<double, 2U> &u_vec, coder::sparse *A,
                    ::coder::array<double, 1U> &b, ::coder::array<double, 2U> &Aeq,
                    ::coder::array<double, 1U> &beq);

}

#endif
//
// File trailer for BuildConstr_v4.h
//
// [EOF]
//
