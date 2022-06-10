//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStructNoCtx.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
//

#ifndef EVALCURVSTRUCTNOCTX_H
#define EVALCURVSTRUCTNOCTX_H

// Include Files
#include "opencn_matlab_types31.h"
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
void EvalCurvStructNoCtx(int cfg_NumberAxis, int cfg_NCart, int cfg_NRot,
                         const int cfg_indCart_data[], int cfg_indCart_size,
                         const int cfg_indRot_data[], int cfg_indRot_size,
                         const int cfg_indTot_data[], int cfg_indTot_size, CurveType curv_Info_Type,
                         const double curv_R0[6], const double curv_R1[6],
                         const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                         double curv_theta, double curv_pitch,
                         const ::coder::array<double, 2U> &curv_CoeffP5, double curv_a_param,
                         double curv_b_param, const CurvStruct *spline, double u_vec,
                         ::coder::array<double, 1U> &r0D);

void EvalCurvStructNoCtx(int cfg_NumberAxis, int cfg_NCart, int cfg_NRot,
                         const int cfg_indCart_data[], int cfg_indCart_size,
                         const int cfg_indRot_data[], int cfg_indRot_size,
                         const int cfg_indTot_data[], int cfg_indTot_size, CurveType curv_Info_Type,
                         const double curv_R0[6], const double curv_R1[6],
                         const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                         double curv_theta, double curv_pitch,
                         const ::coder::array<double, 2U> &curv_CoeffP5, double curv_a_param,
                         double curv_b_param, const CurvStruct *spline,
                         ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                         ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D);

void EvalCurvStructNoCtx(int cfg_NumberAxis, int cfg_NCart, int cfg_NRot,
                         const int cfg_indCart_data[], int cfg_indCart_size,
                         const int cfg_indRot_data[], int cfg_indRot_size,
                         const int cfg_indTot_data[], int cfg_indTot_size, CurveType curv_Info_Type,
                         const double curv_R0[6], const double curv_R1[6],
                         const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                         double curv_theta, double curv_pitch,
                         const ::coder::array<double, 2U> &curv_CoeffP5, double curv_a_param,
                         double curv_b_param, const CurvStruct *spline,
                         ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                         ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                         ::coder::array<double, 2U> &r3D);

void EvalCurvStructNoCtx(int cfg_NumberAxis, int cfg_NCart, int cfg_NRot,
                         const int cfg_indCart_data[], int cfg_indCart_size,
                         const int cfg_indRot_data[], int cfg_indRot_size,
                         const int cfg_indTot_data[], int cfg_indTot_size, CurveType curv_Info_Type,
                         const double curv_R0[6], const double curv_R1[6],
                         const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                         double curv_theta, double curv_pitch,
                         const ::coder::array<double, 2U> &curv_CoeffP5, double curv_a_param,
                         double curv_b_param, const CurvStruct *spline, double u_vec,
                         ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                         ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D);

void b_EvalCurvStructNoCtx(int cfg_NumberAxis, int cfg_NCart, int cfg_NRot,
                           const int cfg_indCart_data[], int cfg_indCart_size,
                           const int cfg_indRot_data[], int cfg_indRot_size,
                           const int cfg_indTot_data[], int cfg_indTot_size,
                           CurveType curv_Info_Type, const double curv_R0[6],
                           const double curv_R1[6], const double curv_CorrectedHelixCenter[3],
                           const double curv_evec[3], double curv_theta, double curv_pitch,
                           const ::coder::array<double, 2U> &curv_CoeffP5, double curv_a_param,
                           double curv_b_param, const CurvStruct *spline,
                           ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                           ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D);

} // namespace ocn

#endif
//
// File trailer for EvalCurvStructNoCtx.h
//
// [EOF]
//
