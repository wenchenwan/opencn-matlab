//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalTransP5.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "EvalTransP5.h"
#include "mypolyval.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"
#include <emmintrin.h>

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
        _mm_storeu_pd(&p5_1D[k][0], _mm_mul_pd(_mm_loadu_pd((double *)&CurvStruct_CoeffP5[k][0]),
                                               _mm_set1_pd(5.0 - static_cast<double>(k))));
        p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
    }
    __m128d r;
    __m128d r1;
    __m128d r2;
    __m128d r3;
    __m128d r4;
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    r = _mm_loadu_pd(&p5_1D[0][0]);
    _mm_storeu_pd(&p5_2D[0][0], _mm_mul_pd(r, _mm_set1_pd(4.0)));
    p5_2D[0][2] = p5_1D[0][2] * 4.0;
    r = _mm_loadu_pd(&p5_1D[1][0]);
    r1 = _mm_set1_pd(3.0);
    _mm_storeu_pd(&p5_2D[1][0], _mm_mul_pd(r, r1));
    p5_2D[1][2] = p5_1D[1][2] * 3.0;
    r = _mm_loadu_pd(&p5_1D[2][0]);
    r2 = _mm_set1_pd(2.0);
    _mm_storeu_pd(&p5_2D[2][0], _mm_mul_pd(r, r2));
    p5_2D[2][2] = p5_1D[2][2] * 2.0;
    r = _mm_loadu_pd(&p5_1D[3][0]);
    r3 = _mm_set1_pd(1.0);
    _mm_storeu_pd(&p5_2D[3][0], _mm_mul_pd(r, r3));
    p5_2D[3][2] = p5_1D[3][2];
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    //
    mypolyval(CurvStruct_CoeffP5, u_vec, r_0D);
    b_mypolyval(p5_1D, u_vec, r_1D);
    c_mypolyval(p5_2D, u_vec, r_2D);
    r4 = _mm_loadu_pd(&p5_2D[0][0]);
    _mm_storeu_pd(&b_p5_2D[0][0], _mm_mul_pd(r4, r1));
    b_p5_2D[0][2] = p5_2D[0][2] * 3.0;
    r4 = _mm_loadu_pd(&p5_2D[1][0]);
    _mm_storeu_pd(&b_p5_2D[1][0], _mm_mul_pd(r4, r2));
    b_p5_2D[1][2] = p5_2D[1][2] * 2.0;
    r4 = _mm_loadu_pd(&p5_2D[2][0]);
    _mm_storeu_pd(&b_p5_2D[2][0], _mm_mul_pd(r4, r3));
    b_p5_2D[2][2] = p5_2D[2][2];
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
        _mm_storeu_pd(&p5_1D[k][0], _mm_mul_pd(_mm_loadu_pd((double *)&CurvStruct_CoeffP5[k][0]),
                                               _mm_set1_pd(5.0 - static_cast<double>(k))));
        p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
    }
    __m128d r;
    __m128d r1;
    __m128d r2;
    __m128d r3;
    __m128d r4;
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    r = _mm_loadu_pd(&p5_1D[0][0]);
    _mm_storeu_pd(&p5_2D[0][0], _mm_mul_pd(r, _mm_set1_pd(4.0)));
    p5_2D[0][2] = p5_1D[0][2] * 4.0;
    r = _mm_loadu_pd(&p5_1D[1][0]);
    r1 = _mm_set1_pd(3.0);
    _mm_storeu_pd(&p5_2D[1][0], _mm_mul_pd(r, r1));
    p5_2D[1][2] = p5_1D[1][2] * 3.0;
    r = _mm_loadu_pd(&p5_1D[2][0]);
    r2 = _mm_set1_pd(2.0);
    _mm_storeu_pd(&p5_2D[2][0], _mm_mul_pd(r, r2));
    p5_2D[2][2] = p5_1D[2][2] * 2.0;
    r = _mm_loadu_pd(&p5_1D[3][0]);
    r3 = _mm_set1_pd(1.0);
    _mm_storeu_pd(&p5_2D[3][0], _mm_mul_pd(r, r3));
    p5_2D[3][2] = p5_1D[3][2];
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    //
    mypolyval(CurvStruct_CoeffP5, u_vec, r_0D);
    b_mypolyval(p5_1D, u_vec, r_1D);
    c_mypolyval(p5_2D, u_vec, r_2D);
    r4 = _mm_loadu_pd(&p5_2D[0][0]);
    _mm_storeu_pd(&b_p5_2D[0][0], _mm_mul_pd(r4, r1));
    b_p5_2D[0][2] = p5_2D[0][2] * 3.0;
    r4 = _mm_loadu_pd(&p5_2D[1][0]);
    _mm_storeu_pd(&b_p5_2D[1][0], _mm_mul_pd(r4, r2));
    b_p5_2D[1][2] = p5_2D[1][2] * 2.0;
    r4 = _mm_loadu_pd(&p5_2D[2][0]);
    _mm_storeu_pd(&b_p5_2D[2][0], _mm_mul_pd(r4, r3));
    b_p5_2D[2][2] = p5_2D[2][2];
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
        _mm_storeu_pd(&p5_1D[k][0], _mm_mul_pd(_mm_loadu_pd((double *)&CurvStruct_CoeffP5[k][0]),
                                               _mm_set1_pd(5.0 - static_cast<double>(k))));
        p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
    }
    __m128d r;
    __m128d r1;
    __m128d r2;
    __m128d r3;
    __m128d r4;
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    r = _mm_loadu_pd(&p5_1D[0][0]);
    _mm_storeu_pd(&p5_2D[0][0], _mm_mul_pd(r, _mm_set1_pd(4.0)));
    p5_2D[0][2] = p5_1D[0][2] * 4.0;
    r = _mm_loadu_pd(&p5_1D[1][0]);
    r1 = _mm_set1_pd(3.0);
    _mm_storeu_pd(&p5_2D[1][0], _mm_mul_pd(r, r1));
    p5_2D[1][2] = p5_1D[1][2] * 3.0;
    r = _mm_loadu_pd(&p5_1D[2][0]);
    r2 = _mm_set1_pd(2.0);
    _mm_storeu_pd(&p5_2D[2][0], _mm_mul_pd(r, r2));
    p5_2D[2][2] = p5_1D[2][2] * 2.0;
    r = _mm_loadu_pd(&p5_1D[3][0]);
    r3 = _mm_set1_pd(1.0);
    _mm_storeu_pd(&p5_2D[3][0], _mm_mul_pd(r, r3));
    p5_2D[3][2] = p5_1D[3][2];
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    //
    mypolyval(CurvStruct_CoeffP5, u_vec, r_0D);
    b_mypolyval(p5_1D, u_vec, r_1D);
    c_mypolyval(p5_2D, u_vec, r_2D);
    r4 = _mm_loadu_pd(&p5_2D[0][0]);
    _mm_storeu_pd(&b_p5_2D[0][0], _mm_mul_pd(r4, r1));
    b_p5_2D[0][2] = p5_2D[0][2] * 3.0;
    r4 = _mm_loadu_pd(&p5_2D[1][0]);
    _mm_storeu_pd(&b_p5_2D[1][0], _mm_mul_pd(r4, r2));
    b_p5_2D[1][2] = p5_2D[1][2] * 2.0;
    r4 = _mm_loadu_pd(&p5_2D[2][0]);
    _mm_storeu_pd(&b_p5_2D[2][0], _mm_mul_pd(r4, r3));
    b_p5_2D[2][2] = p5_2D[2][2];
    d_mypolyval(b_p5_2D, u_vec, r_3D);
}

} // namespace ocn

//
// File trailer for EvalTransP5.cpp
//
// [EOF]
//
