//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: TransP5LengthApprox.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
//

// Include Files
#include "TransP5LengthApprox.h"
#include "mypolyval.h"
#include "sinspace_data.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// computes approximately the arc length of a parametric spline / RHG
//
// Arguments    : const double CurvStruct_CoeffP5[6][3]
// Return Type  : double
//
namespace ocn {
double TransP5LengthApprox(const double CurvStruct_CoeffP5[6][3])
{
    double a[9][3];
    double b_CurvStruct_CoeffP5[5][3];
    double Integrand[9];
    double b_y1[9];
    double x[9];
    double work;
    double y;
    int ixLead;
    signed char b[5][3];
    // MYPOLYDER Differentiate polynomial.
    //
    // u  = u(:).';
    for (int k{0}; k < 5; k++) {
        b[k][0] = static_cast<signed char>(5 - k);
        b[k][1] = static_cast<signed char>(5 - k);
        b[k][2] = static_cast<signed char>(5 - k);
    }
    //  derivative
    //  midpoint values
    ixLead = 1;
    work = 0.0;
    for (int m{0}; m < 9; m++) {
        double tmp2;
        double work_tmp;
        tmp2 = work;
        work_tmp = 0.1111111111111111 * static_cast<double>(ixLead);
        work = work_tmp;
        b_y1[m] = work_tmp - tmp2;
        ixLead++;
    }
    for (int i{0}; i < 5; i++) {
        b_CurvStruct_CoeffP5[i][0] = CurvStruct_CoeffP5[i][0] * static_cast<double>(b[i][0]);
        b_CurvStruct_CoeffP5[i][1] = CurvStruct_CoeffP5[i][1] * static_cast<double>(b[i][1]);
        b_CurvStruct_CoeffP5[i][2] = CurvStruct_CoeffP5[i][2] * static_cast<double>(b[i][2]);
    }
    mypolyval(b_CurvStruct_CoeffP5, a);
    for (int b_k{0}; b_k < 9; b_k++) {
        Integrand[b_k] = std::pow(a[b_k][0], 2.0);
        Integrand[b_k] += std::pow(a[b_k][1], 2.0);
        Integrand[b_k] += std::pow(a[b_k][2], 2.0);
    }
    __m128d r;
    __m128d r1;
    __m128d r2;
    sqrt_calls++;
    r = _mm_loadu_pd(&Integrand[0]);
    r1 = _mm_sqrt_pd(r);
    _mm_storeu_pd(&Integrand[0], r1);
    r2 = _mm_loadu_pd(&b_y1[0]);
    _mm_storeu_pd(&x[0], _mm_mul_pd(r1, r2));
    r = _mm_loadu_pd(&Integrand[2]);
    r1 = _mm_sqrt_pd(r);
    _mm_storeu_pd(&Integrand[2], r1);
    r2 = _mm_loadu_pd(&b_y1[2]);
    _mm_storeu_pd(&x[2], _mm_mul_pd(r1, r2));
    r = _mm_loadu_pd(&Integrand[4]);
    r1 = _mm_sqrt_pd(r);
    _mm_storeu_pd(&Integrand[4], r1);
    r2 = _mm_loadu_pd(&b_y1[4]);
    _mm_storeu_pd(&x[4], _mm_mul_pd(r1, r2));
    r = _mm_loadu_pd(&Integrand[6]);
    r1 = _mm_sqrt_pd(r);
    _mm_storeu_pd(&Integrand[6], r1);
    r2 = _mm_loadu_pd(&b_y1[6]);
    _mm_storeu_pd(&x[6], _mm_mul_pd(r1, r2));
    x[8] = std::sqrt(Integrand[8]) * b_y1[8];
    y = x[0];
    for (int c_k{0}; c_k < 8; c_k++) {
        y += x[c_k + 1];
    }
    return y;
}

} // namespace ocn

//
// File trailer for TransP5LengthApprox.cpp
//
// [EOF]
//
