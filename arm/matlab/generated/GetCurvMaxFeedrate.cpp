//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: GetCurvMaxFeedrate.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 01-Mar-2022 10:58:42
//

// Include Files
#include "GetCurvMaxFeedrate.h"
#include "EvalCurvStruct.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// function Feedrate = GetCurvMaxFeedrate(ctx, CurvStruct)
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
    double a__1[10][3];
    double r1D[10][3];
    double r2D[10][3];
    double r3D[10][3];
    double r3t[10][3];
    double z1[10][3];
    double y[10];
    double b_z_data[9];
    double z_data[9];
    double A[3];
    double J[3];
    double Feedrate;
    double d;
    double d10;
    double d12;
    double d13;
    double d2;
    double d4;
    int b_partialTrueCount;
    int b_trueCount;
    int partialTrueCount;
    int trueCount;
    signed char b_tmp_data[3];
    signed char tmp_data[3];
    // 'GetCurvMaxFeedrate:3' BaseFeedrate = 1;
    // 'GetCurvMaxFeedrate:4' [A, J] = GetCurvPeakAJ(ctx, CurvStruct, BaseFeedrate, 10);
    //  rdot = r1D * u1d
    //  rdot'*rdot = r1D'*r1D * u1d
    //  ConstantFeedrate = r1D'*r1D * u1d     (1)
    // 'GetCurvPeakAJ:6' uvec = linspace(0,1,NSample);
    // 'GetCurvPeakAJ:7' [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, uvec);
    b_EvalCurvStruct(ctx_q_splines, CurvStruct_Type, CurvStruct_P0, CurvStruct_P1,
                     CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                     CurvStruct_pitch, CurvStruct_CoeffP5, CurvStruct_sp_index, CurvStruct_a_param,
                     CurvStruct_b_param, a__1, r1D, r2D, r3D);
    //  from (1):
    // 'GetCurvPeakAJ:10' u1d = ConstantFeedrate./vecnorm(r1D, 1);
    std::memset(&y[0], 0, 10U * sizeof(double));
    for (int k{0}; k < 10; k++) {
        y[k] = (std::abs(r1D[k][0]) + std::abs(r1D[k][1])) + std::abs(r1D[k][2]);
    }
    //  u2d = 0;
    //  u3d = 0;
    // 'GetCurvPeakAJ:14' r2t = bsxfun(@times, r2D, u1d.^2);
    //  + r1D*u2d
    // 'GetCurvPeakAJ:15' r3t = bsxfun(@times, r3D, u1d.^3);
    //  + 3*r2D*u1d*u2d + r1d*u3d
    //  These 2 equations tell us that to obtain the values for other
    //  feedrates, they have to be multiplied by the scale.^2 and scale.^3
    // 'GetCurvPeakAJ:19' A = max(abs(r2t), [], 2);
    for (int b_k{0}; b_k < 10; b_k++) {
        double d1;
        double d3;
        double d5;
        double d6;
        double d7;
        d1 = 1.0 / y[b_k];
        d3 = std::pow(d1, 2.0);
        d5 = r2D[b_k][0] * d3;
        d6 = r2D[b_k][1] * d3;
        d7 = r2D[b_k][2] * d3;
        d3 = std::pow(d1, 3.0);
        r3t[b_k][0] = r3D[b_k][0] * d3;
        z1[b_k][0] = std::abs(d5);
        r3t[b_k][1] = r3D[b_k][1] * d3;
        z1[b_k][1] = std::abs(d6);
        r3t[b_k][2] = r3D[b_k][2] * d3;
        z1[b_k][2] = std::abs(d7);
    }
    d = z1[0][0];
    d2 = z1[0][1];
    d4 = z1[0][2];
    for (int j{0}; j < 9; j++) {
        double d11;
        double d8;
        double d9;
        d8 = z1[j + 1][0];
        if (d < d8) {
            d = d8;
        }
        d9 = z1[j + 1][1];
        if (d2 < d9) {
            d2 = d9;
        }
        d11 = z1[j + 1][2];
        if (d4 < d11) {
            d4 = d11;
        }
    }
    A[2] = d4;
    A[1] = d2;
    A[0] = d;
    // 'GetCurvPeakAJ:20' J = max(abs(r3t), [], 2);
    for (int c_k{0}; c_k < 10; c_k++) {
        z1[c_k][0] = std::abs(r3t[c_k][0]);
        z1[c_k][1] = std::abs(r3t[c_k][1]);
        z1[c_k][2] = std::abs(r3t[c_k][2]);
    }
    d10 = z1[0][0];
    d12 = z1[0][1];
    d13 = z1[0][2];
    for (int b_j{0}; b_j < 9; b_j++) {
        double d14;
        double d15;
        double d16;
        d14 = z1[b_j + 1][0];
        if (d10 < d14) {
            d10 = d14;
        }
        d15 = z1[b_j + 1][1];
        if (d12 < d15) {
            d12 = d15;
        }
        d16 = z1[b_j + 1][2];
        if (d13 < d16) {
            d13 = d16;
        }
    }
    J[2] = d13;
    J[1] = d12;
    J[0] = d10;
    // 'GetCurvMaxFeedrate:5' NonZeroA = A ~= 0;
    // 'GetCurvMaxFeedrate:6' NonZeroJ = J ~= 0;
    // 'GetCurvMaxFeedrate:7' ascale = A(NonZeroA)./ctx.cfg.amax(NonZeroA)';
    trueCount = 0;
    if (d != 0.0) {
        trueCount = 1;
    }
    if (d2 != 0.0) {
        trueCount++;
    }
    if (d4 != 0.0) {
        trueCount++;
    }
    partialTrueCount = 0;
    if (d != 0.0) {
        tmp_data[0] = 1;
        partialTrueCount = 1;
    }
    if (d2 != 0.0) {
        tmp_data[partialTrueCount] = 2;
        partialTrueCount++;
    }
    if (d4 != 0.0) {
        tmp_data[partialTrueCount] = 3;
    }
    for (int i{0}; i < trueCount; i++) {
        int z_tmp;
        z_tmp = tmp_data[i] - 1;
        z_data[i] = A[z_tmp] / ctx_cfg_amax[z_tmp];
    }
    // 'GetCurvMaxFeedrate:8' jscale = J(NonZeroJ)./ctx.cfg.jmax(NonZeroJ)';
    b_trueCount = 0;
    if (d10 != 0.0) {
        b_trueCount = 1;
    }
    if (d12 != 0.0) {
        b_trueCount++;
    }
    if (d13 != 0.0) {
        b_trueCount++;
    }
    b_partialTrueCount = 0;
    if (d10 != 0.0) {
        b_tmp_data[0] = 1;
        b_partialTrueCount = 1;
    }
    if (d12 != 0.0) {
        b_tmp_data[b_partialTrueCount] = 2;
        b_partialTrueCount++;
    }
    if (d13 != 0.0) {
        b_tmp_data[b_partialTrueCount] = 3;
    }
    for (int i1{0}; i1 < b_trueCount; i1++) {
        int b_z_tmp;
        b_z_tmp = b_tmp_data[i1] - 1;
        b_z_data[i1] = J[b_z_tmp] / ctx_cfg_jmax[b_z_tmp];
    }
    // 'GetCurvMaxFeedrate:10' if isempty(ascale) || isempty(jscale)
    if ((trueCount == 0) || (b_trueCount == 0)) {
        // 'GetCurvMaxFeedrate:11' Feedrate = CurvStruct.FeedRate;
        Feedrate = CurvStruct_FeedRate;
    } else {
        double b_ex;
        double d_ex;
        double e_ex;
        double ex_tmp;
        double x_idx_1;
        // 'GetCurvMaxFeedrate:12' else
        // 'GetCurvMaxFeedrate:13' ascale = max(ascale);
        // 'GetCurvMaxFeedrate:14' jscale = max(jscale);
        // 'GetCurvMaxFeedrate:15' Feedrate = min([BaseFeedrate/ascale.^(1/2),
        // BaseFeedrate/jscale.^(1/3), CurvStruct.FeedRate]);
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
            for (int d_k{2}; d_k <= trueCount; d_k++) {
                double d17;
                d17 = z_data[d_k - 1];
                if (ex < d17) {
                    ex = d17;
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
            for (int e_k{2}; e_k <= b_trueCount; e_k++) {
                double d18;
                d18 = b_z_data[e_k - 1];
                if (c_ex < d18) {
                    c_ex = d18;
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
