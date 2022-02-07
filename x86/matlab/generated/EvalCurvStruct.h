//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

#ifndef EVALCURVSTRUCT_H
#define EVALCURVSTRUCT_H

// Include Files
#include "rtwtypes.h"
#include "sinspace_types.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
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
extern void EvalCurvStruct(const FeedoptContext *ctx, const CurvStruct *b_CurvStruct,
                           ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                           ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                           ::coder::array<double, 2U> &r3D);

void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[10][3], double r1D[10][3], double r2D[10][3], double r3D[10][3]);

void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3]);

void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_b_param, double r0D[3]);

void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3]);

void b_EvalCurvStruct(CurveType CurvStruct_Type, const double CurvStruct_P0[3],
                      const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3], double r2D[3], double r3D[3]);

void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                      ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D);

void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                      ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                      ::coder::array<double, 2U> &r3D);

void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3], double r2D[3]);

void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3], double r2D[3]);

void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3], double r2D[3], double r3D[3]);

void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3]);

} // namespace ocn

#endif
//
// File trailer for EvalCurvStruct.h
//
// [EOF]
//
