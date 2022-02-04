//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: GetCurvPeakAJ.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

// Include Files
#include "GetCurvPeakAJ.h"
#include "EvalCurvStruct.h"
#include "queue_coder.h"
#include "sinspace_types2.h"
#include <cmath>
#include <cstring>

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
    double r3D[10][3];
    double r3t[10][3];
    double z1[10][3];
    double y[10];
    double d;
    double d10;
    double d11;
    double d13;
    double d2;
    double d4;
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
        double d12;
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
        d12 = z1[j + 1][2];
        if (d4 < d12) {
            d4 = d12;
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
    d10 = z1[0][0];
    d11 = z1[0][1];
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
        if (d11 < d15) {
            d11 = d15;
        }
        d16 = z1[b_j + 1][2];
        if (d13 < d16) {
            d13 = d16;
        }
    }
    J[2] = d13;
    J[1] = d11;
    J[0] = d10;
}

} // namespace ocn

//
// File trailer for GetCurvPeakAJ.cpp
//
// [EOF]
//
