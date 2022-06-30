//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calc_t_nk_kappa.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 29-Jun-2022 18:46:44
//

// Include Files
#include "calc_t_nk_kappa.h"
#include "combineVectorElements.h"
#include "opencn_matlab_data.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 1U> &nk, const ::coder::array<double, 1U> &rD2,
                             double a, const ::coder::array<double, 1U> &rD1, double norm_rD1);

}

// Function Definitions
//
// Arguments    : ::coder::array<double, 1U> &nk
//                const ::coder::array<double, 1U> &rD2
//                double a
//                const ::coder::array<double, 1U> &rD1
//                double norm_rD1
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(::coder::array<double, 1U> &nk, const ::coder::array<double, 1U> &rD2,
                             double a, const ::coder::array<double, 1U> &rD1, double norm_rD1)
{
    double b_norm_rD1;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    b_norm_rD1 = norm_rD1 * norm_rD1;
    if (rD1.size(0) == 1) {
        i = rD2.size(0);
    } else {
        i = rD1.size(0);
    }
    nk.set_size(i);
    stride_0_0 = (rD2.size(0) != 1);
    stride_1_0 = (rD1.size(0) != 1);
    if (rD1.size(0) == 1) {
        loop_ub = rD2.size(0);
    } else {
        loop_ub = rD1.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        nk[i1] = (rD2[i1 * stride_0_0] - a * rD1[i1 * stride_1_0]) / b_norm_rD1;
    }
}

//
// function [t, nk, kappa] = calc_t_nk_kappa(rD1, rD2)
//
// Arguments    : const ::coder::array<double, 1U> &rD1
//                const ::coder::array<double, 1U> &rD2
//                ::coder::array<double, 1U> &t
//                ::coder::array<double, 1U> &nk
//                double *kappa
// Return Type  : void
//
void calc_t_nk_kappa(const ::coder::array<double, 1U> &rD1, const ::coder::array<double, 1U> &rD2,
                     ::coder::array<double, 1U> &t, ::coder::array<double, 1U> &nk, double *kappa)
{
    ::coder::array<double, 1U> r;
    double a;
    double a_tmp;
    double b_rD2;
    double c_rD2;
    double d_rD2;
    double norm_rD1;
    double norm_rD2;
    double num;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int i2;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    //  computes the local Frenet frame (t, n, b) of a curve in R^n
    //  [t, nk, kappa] = calc_t_nk_kappa(rD1, rD2)
    //  where rD1 is the first derivative and rD2 the second one
    // 'calc_t_nk_kappa:5' norm_rD1 = MyNorm(rD1);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    r.set_size(rD1.size(0));
    loop_ub = rD1.size(0);
    for (int i{0}; i < loop_ub; i++) {
        double varargin_1;
        varargin_1 = rD1[i];
        r[i] = std::pow(varargin_1, 2.0);
    }
    norm_rD1 = std::sqrt(coder::combineVectorElements(r));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'calc_t_nk_kappa:6' norm_rD2 = MyNorm(rD2);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    r.set_size(rD2.size(0));
    b_loop_ub = rD2.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        double b_varargin_1;
        b_varargin_1 = rD2[i1];
        r[i1] = std::pow(b_varargin_1, 2.0);
    }
    norm_rD2 = std::sqrt(coder::combineVectorElements(r));
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'calc_t_nk_kappa:8' t = rD1 / norm_rD1;
    t.set_size(rD1.size(0));
    c_loop_ub = rD1.size(0);
    scalarLB = (rD1.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i2 = 0; i2 <= vectorUB; i2 += 2) {
        _mm_storeu_pd(&t[i2],
                      _mm_div_pd(_mm_loadu_pd((const double *)&rD1[i2]), _mm_set1_pd(norm_rD1)));
    }
    for (i2 = scalarLB; i2 < c_loop_ub; i2++) {
        t[i2] = rD1[i2] / norm_rD1;
    }
    //  tangential unit vector
    //
    // 'calc_t_nk_kappa:10' nk     = (rD2 - rD2'*rD1/(norm_rD1*norm_rD1)*rD1)/(norm_rD1*norm_rD1);
    b_rD2 = 0.0;
    d_loop_ub = rD2.size(0);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        b_rD2 += rD2[i3] * rD1[i3];
    }
    a_tmp = norm_rD1 * norm_rD1;
    a = b_rD2 / a_tmp;
    if (rD2.size(0) == rD1.size(0)) {
        int b_scalarLB;
        int b_vectorUB;
        int e_loop_ub;
        int i4;
        nk.set_size(rD2.size(0));
        e_loop_ub = rD2.size(0);
        b_scalarLB = (rD2.size(0) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (i4 = 0; i4 <= b_vectorUB; i4 += 2) {
            _mm_storeu_pd(&nk[i4],
                          _mm_div_pd(_mm_sub_pd(_mm_loadu_pd((const double *)&rD2[i4]),
                                                _mm_mul_pd(_mm_set1_pd(a),
                                                           _mm_loadu_pd((const double *)&rD1[i4]))),
                                     _mm_set1_pd(a_tmp)));
        }
        for (i4 = b_scalarLB; i4 < e_loop_ub; i4++) {
            nk[i4] = (rD2[i4] - a * rD1[i4]) / a_tmp;
        }
    } else {
        binary_expand_op(nk, rD2, a, rD1, norm_rD1);
    }
    //  normal unit vector
    //
    // 'calc_t_nk_kappa:12' num = norm_rD2*norm_rD2*norm_rD1*norm_rD1 - (rD2'*rD1)*(rD2'*rD1);
    c_rD2 = 0.0;
    f_loop_ub = rD2.size(0);
    for (int i5{0}; i5 < f_loop_ub; i5++) {
        c_rD2 += rD2[i5] * rD1[i5];
    }
    d_rD2 = 0.0;
    g_loop_ub = rD2.size(0);
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        d_rD2 += rD2[i6] * rD1[i6];
    }
    num = norm_rD2 * norm_rD2 * norm_rD1 * norm_rD1 - c_rD2 * d_rD2;
    // 'calc_t_nk_kappa:13' if num < 0
    if (num < 0.0) {
        // 'calc_t_nk_kappa:14' num = 0;
        num = 0.0;
    }
    // 'calc_t_nk_kappa:17' kappa = sqrt(num)...
    // 'calc_t_nk_kappa:18'         /(norm_rD1*norm_rD1*norm_rD1);
    //  curvature
    *kappa = std::sqrt(num) / (a_tmp * norm_rD1);
}

//
// function [t, nk, kappa] = calc_t_nk_kappa(rD1, rD2)
//
// Arguments    : const double rD1[5]
//                const double rD2[5]
//                double t[5]
//                double nk[5]
//                double *kappa
// Return Type  : void
//
void calc_t_nk_kappa(const double rD1[5], const double rD2[5], double t[5], double nk[5],
                     double *kappa)
{
    double z1[5];
    double a_tmp;
    double b_rD2;
    double norm_rD1;
    double num;
    //  computes the local Frenet frame (t, n, b) of a curve in R^n
    //  [t, nk, kappa] = calc_t_nk_kappa(rD1, rD2)
    //  where rD1 is the first derivative and rD2 the second one
    // 'calc_t_nk_kappa:5' norm_rD1 = MyNorm(rD1);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    for (int k{0}; k < 5; k++) {
        z1[k] = std::pow(rD1[k], 2.0);
    }
    // 'mysqrt:3' y = sqrt(x);
    norm_rD1 = std::sqrt((((z1[0] + z1[1]) + z1[2]) + z1[3]) + z1[4]);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'calc_t_nk_kappa:6' norm_rD2 = MyNorm(rD2);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'calc_t_nk_kappa:8' t = rD1 / norm_rD1;
    //  tangential unit vector
    //
    // 'calc_t_nk_kappa:10' nk     = (rD2 - rD2'*rD1/(norm_rD1*norm_rD1)*rD1)/(norm_rD1*norm_rD1);
    b_rD2 = 0.0;
    for (int b_k{0}; b_k < 5; b_k++) {
        double d;
        double d1;
        d = rD2[b_k];
        z1[b_k] = std::pow(d, 2.0);
        d1 = rD1[b_k];
        t[b_k] = d1 / norm_rD1;
        b_rD2 += d * d1;
    }
    __m128d r;
    __m128d r1;
    double a;
    double norm_rD2;
    norm_rD2 = std::sqrt((((z1[0] + z1[1]) + z1[2]) + z1[3]) + z1[4]);
    a_tmp = norm_rD1 * norm_rD1;
    a = b_rD2 / a_tmp;
    r = _mm_set1_pd(a);
    r1 = _mm_set1_pd(a_tmp);
    _mm_storeu_pd(&nk[0],
                  _mm_div_pd(_mm_sub_pd(_mm_loadu_pd((const double *)&rD2[0]),
                                        _mm_mul_pd(r, _mm_loadu_pd((const double *)&rD1[0]))),
                             r1));
    _mm_storeu_pd(&nk[2],
                  _mm_div_pd(_mm_sub_pd(_mm_loadu_pd((const double *)&rD2[2]),
                                        _mm_mul_pd(r, _mm_loadu_pd((const double *)&rD1[2]))),
                             r1));
    nk[4] = (rD2[4] - a * rD1[4]) / a_tmp;
    //  normal unit vector
    //
    // 'calc_t_nk_kappa:12' num = norm_rD2*norm_rD2*norm_rD1*norm_rD1 - (rD2'*rD1)*(rD2'*rD1);
    num = norm_rD2 * norm_rD2 * norm_rD1 * norm_rD1 - b_rD2 * b_rD2;
    // 'calc_t_nk_kappa:13' if num < 0
    if (num < 0.0) {
        // 'calc_t_nk_kappa:14' num = 0;
        num = 0.0;
    }
    // 'calc_t_nk_kappa:17' kappa = sqrt(num)...
    // 'calc_t_nk_kappa:18'         /(norm_rD1*norm_rD1*norm_rD1);
    *kappa = std::sqrt(num) / (a_tmp * norm_rD1);
    //  curvature
}

} // namespace ocn

//
// File trailer for calc_t_nk_kappa.cpp
//
// [EOF]
//
