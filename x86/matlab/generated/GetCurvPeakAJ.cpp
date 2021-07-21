//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: GetCurvPeakAJ.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "GetCurvPeakAJ.h"
#include "EvalCurvStruct.h"
#include "queue_coder.h"
#include <cmath>
#include <cstring>
#include <emmintrin.h>

// Function Definitions
//
// rdot = r1D * u1d
//  rdot'*rdot = r1D'*r1D * u1d
//  ConstantFeedrate = r1D'*r1D * u1d     (1)
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double A[3]
//                double J[3]
// Return Type  : void
//
namespace ocn {
void GetCurvPeakAJ(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                   const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                   const double CurvStruct_CorrectedHelixCenter[3], const double CurvStruct_evec[3],
                   double CurvStruct_theta, double CurvStruct_pitch,
                   const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index,
                   double CurvStruct_a_param, double CurvStruct_b_param, double A[3], double J[3])
{
    double a__1[10][3];
    double r1D[10][3];
    double r2D[10][3];
    double r2t[10][3];
    double r3D[10][3];
    double r3t[10][3];
    double z1[10][3];
    double y[10];
    double d;
    double d10;
    double d2;
    double d4;
    double d7;
    double d8;
    b_EvalCurvStruct(ctx_q_splines, CurvStruct_Type, CurvStruct_P0, CurvStruct_P1,
                     CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                     CurvStruct_pitch, CurvStruct_CoeffP5, CurvStruct_sp_index, CurvStruct_a_param,
                     CurvStruct_b_param, a__1, r1D, r2D, r3D);
    //  from (1):
    std::memset(&y[0], 0, 10U * sizeof(double));
    for (int k{0}; k < 10; k++) {
        y[k] = (std::abs(r1D[k][0]) + std::abs(r1D[k][1])) + std::abs(r1D[k][2]);
    }
    //  u2d = 0;
    //  u3d = 0;
    //  + r1D*u2d
    //  + 3*r2D*u1d*u2d + r1d*u3d
    //  These 2 equations tell us that to obtain the values for other
    //  feedrates, they have to be multiplied by the scale.^2 and scale.^3
    for (int b_k{0}; b_k < 10; b_k++) {
        __m128d r;
        double d1;
        double d3;
        d1 = 1.0 / y[b_k];
        d3 = std::pow(d1, 2.0);
        r = _mm_loadu_pd(&r2D[b_k][0]);
        _mm_storeu_pd(&r2t[b_k][0], _mm_mul_pd(r, _mm_set1_pd(d3)));
        r2t[b_k][2] = r2D[b_k][2] * d3;
        d3 = std::pow(d1, 3.0);
        r3t[b_k][0] = r3D[b_k][0] * d3;
        z1[b_k][0] = std::abs(r2t[b_k][0]);
        r3t[b_k][1] = r3D[b_k][1] * d3;
        z1[b_k][1] = std::abs(r2t[b_k][1]);
        r3t[b_k][2] = r3D[b_k][2] * d3;
        z1[b_k][2] = std::abs(r2t[b_k][2]);
    }
    d = z1[0][0];
    d2 = z1[0][1];
    d4 = z1[0][2];
    for (int j{0}; j < 9; j++) {
        double d5;
        double d6;
        double d9;
        d5 = z1[j + 1][0];
        if (d < d5) {
            d = d5;
        }
        d6 = z1[j + 1][1];
        if (d2 < d6) {
            d2 = d6;
        }
        d9 = z1[j + 1][2];
        if (d4 < d9) {
            d4 = d9;
        }
    }
    A[2] = d4;
    A[1] = d2;
    A[0] = d;
    for (int c_k{0}; c_k < 10; c_k++) {
        z1[c_k][0] = std::abs(r3t[c_k][0]);
        z1[c_k][1] = std::abs(r3t[c_k][1]);
        z1[c_k][2] = std::abs(r3t[c_k][2]);
    }
    d7 = z1[0][0];
    d8 = z1[0][1];
    d10 = z1[0][2];
    for (int b_j{0}; b_j < 9; b_j++) {
        double d11;
        double d12;
        double d13;
        d11 = z1[b_j + 1][0];
        if (d7 < d11) {
            d7 = d11;
        }
        d12 = z1[b_j + 1][1];
        if (d8 < d12) {
            d8 = d12;
        }
        d13 = z1[b_j + 1][2];
        if (d10 < d13) {
            d10 = d13;
        }
    }
    J[2] = d10;
    J[1] = d8;
    J[0] = d7;
}

} // namespace ocn

//
// File trailer for GetCurvPeakAJ.cpp
//
// [EOF]
//
