//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcVAJ_v5.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

#ifndef CALCVAJ_V5_H
#define CALCVAJ_V5_H

// Include Files
#include "queue_coder.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void CalcVAJ_v5(const queue_coder *ctx_q_splines, CurveType CurvStructs_Type,
                ZSpdMode CurvStructs_zspdmode, const double CurvStructs_P0[3],
                const double CurvStructs_P1[3], const double CurvStructs_CorrectedHelixCenter[3],
                const double CurvStructs_evec[3], double CurvStructs_theta,
                double CurvStructs_pitch, const double CurvStructs_CoeffP5[6][3],
                int CurvStructs_sp_index, double CurvStructs_ConstJerk, double CurvStructs_a_param,
                double CurvStructs_b_param, unsigned long Bl_handle,
                const ::coder::array<double, 1U> &Coeff, double *v_norm, double a[3]);

}

#endif
//
// File trailer for CalcVAJ_v5.h
//
// [EOF]
//
