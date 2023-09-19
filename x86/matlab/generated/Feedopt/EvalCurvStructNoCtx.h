//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStructNoCtx.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:13:50
//

#ifndef EVALCURVSTRUCTNOCTX_H
#define EVALCURVSTRUCTNOCTX_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct CurvStruct;

}

// Function Declarations
namespace ocn {
void EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                         const bool cfg_maskCart_data[], const int cfg_maskCart_size[2],
                         const bool cfg_maskRot_data[], const int cfg_maskRot_size[2],
                         const ::coder::array<int, 1U> &cfg_indCart,
                         const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                         int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                         const CurvStruct *spline, ::coder::array<double, 2U> &u_vec,
                         ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D,
                         ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D);

void b_EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                           const bool cfg_maskCart_data[], const int cfg_maskCart_size[2],
                           const bool cfg_maskRot_data[], const int cfg_maskRot_size[2],
                           const ::coder::array<int, 1U> &cfg_indCart,
                           const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                           int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                           const CurvStruct *spline, double u_vec, ::coder::array<double, 1U> &r0D);

void c_EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                           const bool cfg_maskCart_data[], const int cfg_maskCart_size[2],
                           const bool cfg_maskRot_data[], const int cfg_maskRot_size[2],
                           const ::coder::array<int, 1U> &cfg_indCart,
                           const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                           int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                           const CurvStruct *spline, ::coder::array<double, 1U> &r0D,
                           ::coder::array<double, 1U> &r1D, ::coder::array<double, 1U> &r2D,
                           ::coder::array<double, 1U> &r3D);

void d_EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                           const bool cfg_maskCart_data[], const int cfg_maskCart_size[2],
                           const bool cfg_maskRot_data[], const int cfg_maskRot_size[2],
                           const ::coder::array<int, 1U> &cfg_indCart,
                           const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                           int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                           const CurvStruct *spline, ::coder::array<double, 1U> &r0D,
                           ::coder::array<double, 1U> &r1D, ::coder::array<double, 1U> &r2D,
                           ::coder::array<double, 1U> &r3D);

void e_EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                           const bool cfg_maskCart_data[], const int cfg_maskCart_size[2],
                           const bool cfg_maskRot_data[], const int cfg_maskRot_size[2],
                           const ::coder::array<int, 1U> &cfg_indCart,
                           const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                           int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                           const CurvStruct *spline, double u_vec, ::coder::array<double, 1U> &r0D,
                           ::coder::array<double, 1U> &r1D, ::coder::array<double, 1U> &r2D,
                           ::coder::array<double, 1U> &r3D);

} // namespace ocn

#endif
//
// File trailer for EvalCurvStructNoCtx.h
//
// [EOF]
//
