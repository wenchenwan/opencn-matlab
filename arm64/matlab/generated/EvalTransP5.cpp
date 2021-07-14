//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalTransP5.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "EvalTransP5.h"
#include "mypolyval.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"

// Function Definitions
//
// Arguments    : const double CurvStruct_CoeffP5[6][3]
//                const double u_vec[10]
//                double r_0D[10][3]
//                double r_1D[10][3]
//                double r_2D[10][3]
//                double r_3D[10][3]
// Return Type  : void
//
namespace ocn {
void EvalTransP5(const double CurvStruct_CoeffP5[6][3], const double u_vec[10], double r_0D[10][3],
                 double r_1D[10][3], double r_2D[10][3], double r_3D[10][3])
{
    double p5_1D[5][3];
    double p5_2D[4][3];
    double b_p5_2D[3][3];
    ZoneScopedN("EvalTransP5");
    //
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    for (int k{0}; k < 5; k++) {
        p5_1D[k][0] = CurvStruct_CoeffP5[k][0] * (5.0 - static_cast<double>(k));
        p5_1D[k][1] = CurvStruct_CoeffP5[k][1] * (5.0 - static_cast<double>(k));
        p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
    }
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    for (int b_k{0}; b_k < 4; b_k++) {
        p5_2D[b_k][0] = p5_1D[b_k][0] * (4.0 - static_cast<double>(b_k));
        p5_2D[b_k][1] = p5_1D[b_k][1] * (4.0 - static_cast<double>(b_k));
        p5_2D[b_k][2] = p5_1D[b_k][2] * (4.0 - static_cast<double>(b_k));
    }
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    //
    mypolyval(CurvStruct_CoeffP5, u_vec, r_0D);
    b_mypolyval(p5_1D, u_vec, r_1D);
    c_mypolyval(p5_2D, u_vec, r_2D);
    for (int c_k{0}; c_k < 3; c_k++) {
        b_p5_2D[c_k][0] = p5_2D[c_k][0] * (3.0 - static_cast<double>(c_k));
        b_p5_2D[c_k][1] = p5_2D[c_k][1] * (3.0 - static_cast<double>(c_k));
        b_p5_2D[c_k][2] = p5_2D[c_k][2] * (3.0 - static_cast<double>(c_k));
    }
    d_mypolyval(b_p5_2D, u_vec, r_3D);
}

//
// Arguments    : const double CurvStruct_CoeffP5[6][3]
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r_0D
//                ::coder::array<double, 2U> &r_1D
//                ::coder::array<double, 2U> &r_2D
//                ::coder::array<double, 2U> &r_3D
// Return Type  : void
//
void EvalTransP5(const double CurvStruct_CoeffP5[6][3], const ::coder::array<double, 2U> &u_vec,
                 ::coder::array<double, 2U> &r_0D, ::coder::array<double, 2U> &r_1D,
                 ::coder::array<double, 2U> &r_2D, ::coder::array<double, 2U> &r_3D)
{
    double p5_1D[5][3];
    double p5_2D[4][3];
    double b_p5_2D[3][3];
    ZoneScopedN("EvalTransP5");
    //
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    for (int k{0}; k < 5; k++) {
        p5_1D[k][0] = CurvStruct_CoeffP5[k][0] * (5.0 - static_cast<double>(k));
        p5_1D[k][1] = CurvStruct_CoeffP5[k][1] * (5.0 - static_cast<double>(k));
        p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
    }
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    for (int b_k{0}; b_k < 4; b_k++) {
        p5_2D[b_k][0] = p5_1D[b_k][0] * (4.0 - static_cast<double>(b_k));
        p5_2D[b_k][1] = p5_1D[b_k][1] * (4.0 - static_cast<double>(b_k));
        p5_2D[b_k][2] = p5_1D[b_k][2] * (4.0 - static_cast<double>(b_k));
    }
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    //
    mypolyval(CurvStruct_CoeffP5, u_vec, r_0D);
    b_mypolyval(p5_1D, u_vec, r_1D);
    c_mypolyval(p5_2D, u_vec, r_2D);
    for (int c_k{0}; c_k < 3; c_k++) {
        b_p5_2D[c_k][0] = p5_2D[c_k][0] * (3.0 - static_cast<double>(c_k));
        b_p5_2D[c_k][1] = p5_2D[c_k][1] * (3.0 - static_cast<double>(c_k));
        b_p5_2D[c_k][2] = p5_2D[c_k][2] * (3.0 - static_cast<double>(c_k));
    }
    d_mypolyval(b_p5_2D, u_vec, r_3D);
}

//
// Arguments    : const double CurvStruct_CoeffP5[6][3]
//                double u_vec
//                double r_0D[3]
//                double r_1D[3]
//                double r_2D[3]
//                double r_3D[3]
// Return Type  : void
//
void EvalTransP5(const double CurvStruct_CoeffP5[6][3], double u_vec, double r_0D[3],
                 double r_1D[3], double r_2D[3], double r_3D[3])
{
    double p5_1D[5][3];
    double p5_2D[4][3];
    double b_p5_2D[3][3];
    ZoneScopedN("EvalTransP5");
    //
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    for (int k{0}; k < 5; k++) {
        p5_1D[k][0] = CurvStruct_CoeffP5[k][0] * (5.0 - static_cast<double>(k));
        p5_1D[k][1] = CurvStruct_CoeffP5[k][1] * (5.0 - static_cast<double>(k));
        p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
    }
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    for (int b_k{0}; b_k < 4; b_k++) {
        p5_2D[b_k][0] = p5_1D[b_k][0] * (4.0 - static_cast<double>(b_k));
        p5_2D[b_k][1] = p5_1D[b_k][1] * (4.0 - static_cast<double>(b_k));
        p5_2D[b_k][2] = p5_1D[b_k][2] * (4.0 - static_cast<double>(b_k));
    }
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    //
    mypolyval(CurvStruct_CoeffP5, u_vec, r_0D);
    b_mypolyval(p5_1D, u_vec, r_1D);
    c_mypolyval(p5_2D, u_vec, r_2D);
    for (int c_k{0}; c_k < 3; c_k++) {
        b_p5_2D[c_k][0] = p5_2D[c_k][0] * (3.0 - static_cast<double>(c_k));
        b_p5_2D[c_k][1] = p5_2D[c_k][1] * (3.0 - static_cast<double>(c_k));
        b_p5_2D[c_k][2] = p5_2D[c_k][2] * (3.0 - static_cast<double>(c_k));
    }
    d_mypolyval(b_p5_2D, u_vec, r_3D);
}

} // namespace ocn

//
// File trailer for EvalTransP5.cpp
//
// [EOF]
//
