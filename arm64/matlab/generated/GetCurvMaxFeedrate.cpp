//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: GetCurvMaxFeedrate.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "GetCurvMaxFeedrate.h"
#include "GetCurvPeakAJ.h"
#include "queue_coder.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const queue_coder *ctx_q_splines
//                const double ctx_cfg_amax[3]
//                const double ctx_cfg_jmax[3]
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_FeedRate
//                double CurvStruct_a_param
//                double CurvStruct_b_param
// Return Type  : double
//
namespace ocn {
double GetCurvMaxFeedrate(const queue_coder *ctx_q_splines, const double ctx_cfg_amax[3],
                          const double ctx_cfg_jmax[3], CurveType CurvStruct_Type,
                          const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                          const double CurvStruct_CorrectedHelixCenter[3],
                          const double CurvStruct_evec[3], double CurvStruct_theta,
                          double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                          int CurvStruct_sp_index, double CurvStruct_FeedRate,
                          double CurvStruct_a_param, double CurvStruct_b_param)
{
    double b_z_data[9];
    double z_data[9];
    double A[3];
    double J[3];
    double Feedrate;
    int b_partialTrueCount;
    int b_trueCount;
    int partialTrueCount;
    int trueCount;
    signed char b_tmp_data[3];
    signed char tmp_data[3];
    GetCurvPeakAJ(ctx_q_splines, CurvStruct_Type, CurvStruct_P0, CurvStruct_P1,
                  CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, CurvStruct_CoeffP5, CurvStruct_sp_index, CurvStruct_a_param,
                  CurvStruct_b_param, A, J);
    trueCount = 0;
    if (A[0] != 0.0) {
        trueCount = 1;
    }
    if (A[1] != 0.0) {
        trueCount++;
    }
    if (A[2] != 0.0) {
        trueCount++;
    }
    partialTrueCount = 0;
    if (A[0] != 0.0) {
        tmp_data[0] = 1;
        partialTrueCount = 1;
    }
    if (A[1] != 0.0) {
        tmp_data[partialTrueCount] = 2;
        partialTrueCount++;
    }
    if (A[2] != 0.0) {
        tmp_data[partialTrueCount] = 3;
    }
    for (int i{0}; i < trueCount; i++) {
        int z_tmp;
        z_tmp = tmp_data[i] - 1;
        z_data[i] = A[z_tmp] / ctx_cfg_amax[z_tmp];
    }
    b_trueCount = 0;
    if (J[0] != 0.0) {
        b_trueCount = 1;
    }
    if (J[1] != 0.0) {
        b_trueCount++;
    }
    if (J[2] != 0.0) {
        b_trueCount++;
    }
    b_partialTrueCount = 0;
    if (J[0] != 0.0) {
        b_tmp_data[0] = 1;
        b_partialTrueCount = 1;
    }
    if (J[1] != 0.0) {
        b_tmp_data[b_partialTrueCount] = 2;
        b_partialTrueCount++;
    }
    if (J[2] != 0.0) {
        b_tmp_data[b_partialTrueCount] = 3;
    }
    for (int i1{0}; i1 < b_trueCount; i1++) {
        int b_z_tmp;
        b_z_tmp = b_tmp_data[i1] - 1;
        b_z_data[i1] = J[b_z_tmp] / ctx_cfg_jmax[b_z_tmp];
    }
    if ((trueCount == 0) || (b_trueCount == 0)) {
        Feedrate = CurvStruct_FeedRate;
    } else {
        double b_ex;
        double d_ex;
        double e_ex;
        double ex_tmp;
        double x_idx_1;
        if (trueCount <= 2) {
            if (trueCount == 1) {
                b_ex = z_data[0];
            } else if (z_data[0] < z_data[1]) {
                b_ex = z_data[1];
            } else {
                b_ex = z_data[0];
            }
        } else {
            double ex;
            ex = z_data[0];
            for (int k{2}; k <= trueCount; k++) {
                double d;
                d = z_data[k - 1];
                if (ex < d) {
                    ex = d;
                }
            }
            b_ex = ex;
        }
        if (b_trueCount <= 2) {
            if (b_trueCount == 1) {
                d_ex = b_z_data[0];
            } else if (b_z_data[0] < b_z_data[1]) {
                d_ex = b_z_data[1];
            } else {
                d_ex = b_z_data[0];
            }
        } else {
            double c_ex;
            c_ex = b_z_data[0];
            for (int b_k{2}; b_k <= b_trueCount; b_k++) {
                double d1;
                d1 = b_z_data[b_k - 1];
                if (c_ex < d1) {
                    c_ex = d1;
                }
            }
            d_ex = c_ex;
        }
        x_idx_1 = 1.0 / std::pow(d_ex, 0.33333333333333331);
        ex_tmp = 1.0 / std::pow(b_ex, 0.5);
        e_ex = ex_tmp;
        if (ex_tmp > x_idx_1) {
            e_ex = x_idx_1;
        }
        if (e_ex > CurvStruct_FeedRate) {
            e_ex = CurvStruct_FeedRate;
        }
        Feedrate = e_ex;
    }
    return Feedrate;
}

} // namespace ocn

//
// File trailer for GetCurvMaxFeedrate.cpp
//
// [EOF]
//
