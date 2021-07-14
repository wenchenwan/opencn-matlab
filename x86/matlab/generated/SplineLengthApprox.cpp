//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApprox.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "SplineLengthApprox.h"
#include "bspline_eval_vec.h"
#include "diff.h"
#include "find.h"
#include "linspace.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// computes approximately the arc length of a parametric spline
//
// Arguments    : const queue_coder *ctx_q_splines
//                double ctx_cfg_NGridLengthSpline
//                int Curv_sp_index
//                const double u0_tilda_data[]
//                const int u0_tilda_size[2]
//                double u1_tilda
// Return Type  : double
//
namespace ocn {
double SplineLengthApprox(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                          int Curv_sp_index, const double u0_tilda_data[],
                          const int u0_tilda_size[2], double u1_tilda)
{
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1Dx;
    ::coder::array<double, 2U> r1Dy;
    ::coder::array<double, 2U> r1Dz;
    ::coder::array<double, 2U> u_mid_tilda;
    ::coder::array<double, 2U> u_tilda;
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 2U> z1;
    ::coder::array<bool, 2U> b_expl_temp;
    CurvStruct expl_temp;
    int tmp_size[2];
    int N;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int c_loop_ub;
    int c_scalarLB;
    int c_vectorUB;
    int d_k;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i13;
    int i14;
    int i3;
    int i5;
    int i7;
    int loop_ub;
    int scalarLB;
    int tmp_data;
    int vectorUB;
    //  get the sp structure
    ctx_q_splines->get(Curv_sp_index, &expl_temp);
    //  the ORIGINAL spline is parametrized with u_tilda
    //  after cut-off, new parameter is called u.
    //  u=0 corresponds to the first lift-off point
    //  u=1 corresponds to the second lift-off point
    //  u is NOT used in this function
    //  if coder.target('matlab')
    //      % derivative whith respect to u_tilda !!!
    //      sp1D      = fnder(sp);
    //      Knots     = sp1D.knots;
    //  else
    //  end
    b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
    loop_ub = expl_temp.sp.knots.size(1);
    for (int i{0}; i < loop_ub; i++) {
        b_expl_temp[i] = (expl_temp.sp.knots[i] < u1_tilda);
    }
    coder::b_eml_find(b_expl_temp, (int *)&tmp_data, tmp_size);
    u_vec_tilda.set_size(1, (u0_tilda_size[1] + tmp_data) + 1);
    b_loop_ub = u0_tilda_size[1];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        u_vec_tilda[0] = u0_tilda_data[0];
    }
    for (int i2{0}; i2 < tmp_data; i2++) {
        u_vec_tilda[i2 + u0_tilda_size[1]] = expl_temp.sp.knots[i2];
    }
    u_vec_tilda[u0_tilda_size[1] + tmp_data] = u1_tilda;
    u_tilda.set_size(1, 0);
    //  N equally spaced u_tilda values between each pair of knots
    //  from u0_tilda until u1_tilda
    i3 = u_vec_tilda.size(1);
    for (int k{0}; k <= i3 - 2; k++) {
        int d_loop_ub;
        int i4;
        int i6;
        i4 = u_tilda.size(1);
        if (u_tilda.size(1) != 0) {
            if (1 > u_tilda.size(1) - 1) {
                i4 = 0;
            } else {
                i4 = u_tilda.size(1) - 1;
            }
        }
        coder::linspace(u_vec_tilda[k], u_vec_tilda[k + 1], ctx_cfg_NGridLengthSpline, r);
        i6 = i4;
        d_loop_ub = r.size(1);
        i4 += r.size(1);
        u_tilda.set_size(u_tilda.size(0), i4);
        for (int i8{0}; i8 < d_loop_ub; i8++) {
            u_tilda[i6 + i8] = r[i8];
        }
    }
    //  midpoint values
    if (1 > u_tilda.size(1) - 1) {
        c_loop_ub = 0;
    } else {
        c_loop_ub = u_tilda.size(1) - 1;
    }
    i5 = (2 <= u_tilda.size(1));
    u_mid_tilda.set_size(1, c_loop_ub);
    scalarLB = (c_loop_ub / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i7 = 0; i7 <= vectorUB; i7 += 2) {
        __m128d r1;
        __m128d r2;
        r1 = _mm_loadu_pd(&u_tilda[i7]);
        r2 = _mm_loadu_pd(&u_tilda[i5 + i7]);
        _mm_storeu_pd(&u_mid_tilda[i7], _mm_mul_pd(_mm_set1_pd(0.5), _mm_add_pd(r1, r2)));
    }
    for (i7 = scalarLB; i7 < c_loop_ub; i7++) {
        u_mid_tilda[i7] = 0.5 * (u_tilda[i7] + u_tilda[i5 + i7]);
    }
    //  midpoint values
    //  parametric derivative calculation at each midpoint value
    //  with respect to u_tilda
    //  if coder.target('rtw') || coder.target('mex')
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_mid_tilda, a__1, r1Dx);
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_mid_tilda, a__2, r1Dy);
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_mid_tilda, a__3, r1Dz);
    //  else
    //      r1D = spval(sp1D, u_mid_tilda);
    //  end
    //  length (between u0_tilda and u1_tilda) calculation by rectangles method
    sqrt_calls++;
    a.set_size(3, r1Dx.size(1));
    e_loop_ub = r1Dx.size(1);
    for (int i9{0}; i9 < e_loop_ub; i9++) {
        a[3 * i9] = r1Dx[i9];
    }
    f_loop_ub = r1Dy.size(1);
    for (int i10{0}; i10 < f_loop_ub; i10++) {
        a[3 * i10 + 1] = r1Dy[i10];
    }
    g_loop_ub = r1Dz.size(1);
    for (int i11{0}; i11 < g_loop_ub; i11++) {
        a[3 * i11 + 2] = r1Dz[i11];
    }
    z1.set_size(3, a.size(1));
    N = a.size(1);
    for (int b_k{0}; b_k < N; b_k++) {
        z1[3 * b_k] = std::pow(a[3 * b_k], 2.0);
        z1[3 * b_k + 1] = std::pow(a[3 * b_k + 1], 2.0);
        z1[3 * b_k + 2] = std::pow(a[3 * b_k + 2], 2.0);
    }
    if (z1.size(1) == 0) {
        x.set_size(1, 0);
    } else {
        int i12;
        x.set_size(1, z1.size(1));
        i12 = z1.size(1);
        for (int c_k{0}; c_k < i12; c_k++) {
            x[c_k] = z1[3 * c_k];
            x[c_k] = x[c_k] + z1[3 * c_k + 1];
            x[c_k] = x[c_k] + z1[3 * c_k + 2];
        }
    }
    i13 = x.size(1);
    b_scalarLB = (x.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (d_k = 0; d_k <= b_vectorUB; d_k += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&x[d_k]);
        _mm_storeu_pd(&x[d_k], _mm_sqrt_pd(r3));
    }
    for (d_k = b_scalarLB; d_k < i13; d_k++) {
        x[d_k] = std::sqrt(x[d_k]);
    }
    coder::diff(u_tilda, r);
    x.set_size(1, x.size(1));
    h_loop_ub = x.size(1);
    c_scalarLB = (x.size(1) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (i14 = 0; i14 <= c_vectorUB; i14 += 2) {
        __m128d r4;
        __m128d r5;
        r4 = _mm_loadu_pd(&x[i14]);
        r5 = _mm_loadu_pd(&r[i14]);
        _mm_storeu_pd(&x[i14], _mm_mul_pd(r4, r5));
    }
    for (i14 = c_scalarLB; i14 < h_loop_ub; i14++) {
        x[i14] = x[i14] * r[i14];
    }
    return coder::sum(x);
}

//
// computes approximately the arc length of a parametric spline
//
// Arguments    : const queue_coder *ctx_q_splines
//                double ctx_cfg_NGridLengthSpline
//                int Curv_sp_index
//                double u0_tilda
//                const double u1_tilda_data[]
//                const int u1_tilda_size[2]
// Return Type  : double
//
double SplineLengthApprox(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                          int Curv_sp_index, double u0_tilda, const double u1_tilda_data[],
                          const int u1_tilda_size[2])
{
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1Dx;
    ::coder::array<double, 2U> r1Dy;
    ::coder::array<double, 2U> r1Dz;
    ::coder::array<double, 2U> u_mid_tilda;
    ::coder::array<double, 2U> u_tilda;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 2U> z1;
    ::coder::array<bool, 2U> b_expl_temp;
    CurvStruct expl_temp;
    double u_vec_tilda_data[3];
    int Idx1_size[2];
    int Idx1_data;
    int N;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int c_loop_ub;
    int c_scalarLB;
    int c_vectorUB;
    int d_k;
    int d_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i1;
    int i13;
    int i14;
    int i2;
    int i5;
    int i7;
    int i_loop_ub;
    int loop_ub;
    int scalarLB;
    int u_vec_tilda_size_idx_1;
    int vectorUB;
    //  get the sp structure
    ctx_q_splines->get(Curv_sp_index, &expl_temp);
    //  the ORIGINAL spline is parametrized with u_tilda
    //  after cut-off, new parameter is called u.
    //  u=0 corresponds to the first lift-off point
    //  u=1 corresponds to the second lift-off point
    //  u is NOT used in this function
    //  if coder.target('matlab')
    //      % derivative whith respect to u_tilda !!!
    //      sp1D      = fnder(sp);
    //      Knots     = sp1D.knots;
    //  else
    //  end
    b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
    loop_ub = expl_temp.sp.knots.size(1);
    for (int i{0}; i < loop_ub; i++) {
        b_expl_temp[i] = (expl_temp.sp.knots[i] > u0_tilda);
    }
    coder::eml_find(b_expl_temp, (int *)&Idx1_data, Idx1_size);
    if (Idx1_data > 1) {
        i1 = -2;
        i2 = -1;
    } else {
        i1 = Idx1_data - 3;
        i2 = 0;
    }
    b_loop_ub = i2 - i1;
    u_vec_tilda_size_idx_1 = b_loop_ub + u1_tilda_size[1];
    u_vec_tilda_data[0] = u0_tilda;
    for (int i3{0}; i3 <= b_loop_ub - 2; i3++) {
        u_vec_tilda_data[i3 + 1] = expl_temp.sp.knots[(i1 + i3) + 2];
    }
    c_loop_ub = u1_tilda_size[1];
    if (0 <= c_loop_ub - 1) {
        u_vec_tilda_data[b_loop_ub] = u1_tilda_data[0];
    }
    u_tilda.set_size(1, 0);
    //  N equally spaced u_tilda values between each pair of knots
    //  from u0_tilda until u1_tilda
    for (int k{0}; k <= u_vec_tilda_size_idx_1 - 2; k++) {
        int e_loop_ub;
        int i4;
        int i6;
        i4 = u_tilda.size(1);
        if (u_tilda.size(1) != 0) {
            if (1 > u_tilda.size(1) - 1) {
                i4 = 0;
            } else {
                i4 = u_tilda.size(1) - 1;
            }
        }
        coder::linspace(u_vec_tilda_data[k], u_vec_tilda_data[k + 1], ctx_cfg_NGridLengthSpline, r);
        i6 = i4;
        e_loop_ub = r.size(1);
        i4 += r.size(1);
        u_tilda.set_size(u_tilda.size(0), i4);
        for (int i8{0}; i8 < e_loop_ub; i8++) {
            u_tilda[i6 + i8] = r[i8];
        }
    }
    //  midpoint values
    if (1 > u_tilda.size(1) - 1) {
        d_loop_ub = 0;
    } else {
        d_loop_ub = u_tilda.size(1) - 1;
    }
    i5 = (2 <= u_tilda.size(1));
    u_mid_tilda.set_size(1, d_loop_ub);
    scalarLB = (d_loop_ub / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i7 = 0; i7 <= vectorUB; i7 += 2) {
        __m128d r1;
        __m128d r2;
        r1 = _mm_loadu_pd(&u_tilda[i7]);
        r2 = _mm_loadu_pd(&u_tilda[i5 + i7]);
        _mm_storeu_pd(&u_mid_tilda[i7], _mm_mul_pd(_mm_set1_pd(0.5), _mm_add_pd(r1, r2)));
    }
    for (i7 = scalarLB; i7 < d_loop_ub; i7++) {
        u_mid_tilda[i7] = 0.5 * (u_tilda[i7] + u_tilda[i5 + i7]);
    }
    //  midpoint values
    //  parametric derivative calculation at each midpoint value
    //  with respect to u_tilda
    //  if coder.target('rtw') || coder.target('mex')
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_mid_tilda, a__1, r1Dx);
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_mid_tilda, a__2, r1Dy);
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_mid_tilda, a__3, r1Dz);
    //  else
    //      r1D = spval(sp1D, u_mid_tilda);
    //  end
    //  length (between u0_tilda and u1_tilda) calculation by rectangles method
    sqrt_calls++;
    a.set_size(3, r1Dx.size(1));
    f_loop_ub = r1Dx.size(1);
    for (int i9{0}; i9 < f_loop_ub; i9++) {
        a[3 * i9] = r1Dx[i9];
    }
    g_loop_ub = r1Dy.size(1);
    for (int i10{0}; i10 < g_loop_ub; i10++) {
        a[3 * i10 + 1] = r1Dy[i10];
    }
    h_loop_ub = r1Dz.size(1);
    for (int i11{0}; i11 < h_loop_ub; i11++) {
        a[3 * i11 + 2] = r1Dz[i11];
    }
    z1.set_size(3, a.size(1));
    N = a.size(1);
    for (int b_k{0}; b_k < N; b_k++) {
        z1[3 * b_k] = std::pow(a[3 * b_k], 2.0);
        z1[3 * b_k + 1] = std::pow(a[3 * b_k + 1], 2.0);
        z1[3 * b_k + 2] = std::pow(a[3 * b_k + 2], 2.0);
    }
    if (z1.size(1) == 0) {
        x.set_size(1, 0);
    } else {
        int i12;
        x.set_size(1, z1.size(1));
        i12 = z1.size(1);
        for (int c_k{0}; c_k < i12; c_k++) {
            x[c_k] = z1[3 * c_k];
            x[c_k] = x[c_k] + z1[3 * c_k + 1];
            x[c_k] = x[c_k] + z1[3 * c_k + 2];
        }
    }
    i13 = x.size(1);
    b_scalarLB = (x.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (d_k = 0; d_k <= b_vectorUB; d_k += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&x[d_k]);
        _mm_storeu_pd(&x[d_k], _mm_sqrt_pd(r3));
    }
    for (d_k = b_scalarLB; d_k < i13; d_k++) {
        x[d_k] = std::sqrt(x[d_k]);
    }
    coder::diff(u_tilda, r);
    x.set_size(1, x.size(1));
    i_loop_ub = x.size(1);
    c_scalarLB = (x.size(1) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (i14 = 0; i14 <= c_vectorUB; i14 += 2) {
        __m128d r4;
        __m128d r5;
        r4 = _mm_loadu_pd(&x[i14]);
        r5 = _mm_loadu_pd(&r[i14]);
        _mm_storeu_pd(&x[i14], _mm_mul_pd(r4, r5));
    }
    for (i14 = c_scalarLB; i14 < i_loop_ub; i14++) {
        x[i14] = x[i14] * r[i14];
    }
    return coder::sum(x);
}

//
// computes approximately the arc length of a parametric spline
//
// Arguments    : const queue_coder *ctx_q_splines
//                double ctx_cfg_NGridLengthSpline
//                int Curv_sp_index
//                double u0_tilda
//                double u1_tilda
//                double *L
//                ::coder::array<double, 2U> &Integrand
//                ::coder::array<double, 2U> &u_mid_tilda
//                ::coder::array<double, 2U> &du_tilda
// Return Type  : void
//
void SplineLengthApprox(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                        int Curv_sp_index, double u0_tilda, double u1_tilda, double *L,
                        ::coder::array<double, 2U> &Integrand,
                        ::coder::array<double, 2U> &u_mid_tilda,
                        ::coder::array<double, 2U> &du_tilda)
{
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> b_Integrand;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1Dx;
    ::coder::array<double, 2U> r1Dy;
    ::coder::array<double, 2U> r1Dz;
    ::coder::array<double, 2U> u_tilda;
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<double, 2U> z1;
    ::coder::array<bool, 2U> b_expl_temp;
    CurvStruct expl_temp;
    int Idx2_size[2];
    int Idx1_data;
    int Idx2_data;
    int N;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int c_k;
    int c_loop_ub;
    int c_scalarLB;
    int c_vectorUB;
    int d_loop_ub;
    int e_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i10;
    int i15;
    int i16;
    int i3;
    int i4;
    int i6;
    int i8;
    int i_loop_ub;
    int j_loop_ub;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    //  get the sp structure
    ctx_q_splines->get(Curv_sp_index, &expl_temp);
    //  the ORIGINAL spline is parametrized with u_tilda
    //  after cut-off, new parameter is called u.
    //  u=0 corresponds to the first lift-off point
    //  u=1 corresponds to the second lift-off point
    //  u is NOT used in this function
    //  if coder.target('matlab')
    //      % derivative whith respect to u_tilda !!!
    //      sp1D      = fnder(sp);
    //      Knots     = sp1D.knots;
    //  else
    //  end
    b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
    loop_ub = expl_temp.sp.knots.size(1);
    for (int i{0}; i < loop_ub; i++) {
        b_expl_temp[i] = (expl_temp.sp.knots[i] > u0_tilda);
    }
    coder::eml_find(b_expl_temp, (int *)&Idx2_data, Idx2_size);
    b_loop_ub = Idx2_size[1];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        Idx1_data = Idx2_data;
    }
    b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
    c_loop_ub = expl_temp.sp.knots.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        b_expl_temp[i2] = (expl_temp.sp.knots[i2] < u1_tilda);
    }
    coder::b_eml_find(b_expl_temp, (int *)&Idx2_data, Idx2_size);
    if (Idx1_data > Idx2_data) {
        i3 = 0;
        i4 = 0;
    } else {
        i3 = Idx1_data - 1;
        i4 = Idx2_data;
    }
    d_loop_ub = i4 - i3;
    u_vec_tilda.set_size(1, d_loop_ub + 2);
    u_vec_tilda[0] = u0_tilda;
    for (int i5{0}; i5 < d_loop_ub; i5++) {
        u_vec_tilda[i5 + 1] = expl_temp.sp.knots[i3 + i5];
    }
    u_vec_tilda[d_loop_ub + 1] = u1_tilda;
    u_tilda.set_size(1, 0);
    //  N equally spaced u_tilda values between each pair of knots
    //  from u0_tilda until u1_tilda
    i6 = u_vec_tilda.size(1);
    for (int k{0}; k <= i6 - 2; k++) {
        int f_loop_ub;
        int i7;
        int i9;
        i7 = u_tilda.size(1);
        if (u_tilda.size(1) != 0) {
            if (1 > u_tilda.size(1) - 1) {
                i7 = 0;
            } else {
                i7 = u_tilda.size(1) - 1;
            }
        }
        coder::linspace(u_vec_tilda[k], u_vec_tilda[k + 1], ctx_cfg_NGridLengthSpline, r);
        i9 = i7;
        f_loop_ub = r.size(1);
        i7 += r.size(1);
        u_tilda.set_size(u_tilda.size(0), i7);
        for (int i11{0}; i11 < f_loop_ub; i11++) {
            u_tilda[i9 + i11] = r[i11];
        }
    }
    //  midpoint values
    if (1 > u_tilda.size(1) - 1) {
        e_loop_ub = 0;
    } else {
        e_loop_ub = u_tilda.size(1) - 1;
    }
    i8 = (2 <= u_tilda.size(1));
    u_mid_tilda.set_size(1, e_loop_ub);
    scalarLB = (e_loop_ub / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i10 = 0; i10 <= vectorUB; i10 += 2) {
        __m128d r1;
        __m128d r2;
        r1 = _mm_loadu_pd(&u_tilda[i10]);
        r2 = _mm_loadu_pd(&u_tilda[i8 + i10]);
        _mm_storeu_pd(&u_mid_tilda[i10], _mm_mul_pd(_mm_set1_pd(0.5), _mm_add_pd(r1, r2)));
    }
    for (i10 = scalarLB; i10 < e_loop_ub; i10++) {
        u_mid_tilda[i10] = 0.5 * (u_tilda[i10] + u_tilda[i8 + i10]);
    }
    //  midpoint values
    coder::diff(u_tilda, du_tilda);
    //  parametric derivative calculation at each midpoint value
    //  with respect to u_tilda
    //  if coder.target('rtw') || coder.target('mex')
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_mid_tilda, a__1, r1Dx);
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_mid_tilda, a__2, r1Dy);
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_mid_tilda, a__3, r1Dz);
    //  else
    //      r1D = spval(sp1D, u_mid_tilda);
    //  end
    //  length (between u0_tilda and u1_tilda) calculation by rectangles method
    a.set_size(3, r1Dx.size(1));
    g_loop_ub = r1Dx.size(1);
    for (int i12{0}; i12 < g_loop_ub; i12++) {
        a[3 * i12] = r1Dx[i12];
    }
    h_loop_ub = r1Dy.size(1);
    for (int i13{0}; i13 < h_loop_ub; i13++) {
        a[3 * i13 + 1] = r1Dy[i13];
    }
    i_loop_ub = r1Dz.size(1);
    for (int i14{0}; i14 < i_loop_ub; i14++) {
        a[3 * i14 + 2] = r1Dz[i14];
    }
    z1.set_size(3, a.size(1));
    N = a.size(1);
    for (int b_k{0}; b_k < N; b_k++) {
        z1[3 * b_k] = std::pow(a[3 * b_k], 2.0);
        z1[3 * b_k + 1] = std::pow(a[3 * b_k + 1], 2.0);
        z1[3 * b_k + 2] = std::pow(a[3 * b_k + 2], 2.0);
    }
    coder::sum(z1, Integrand);
    i15 = Integrand.size(1);
    b_scalarLB = (Integrand.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (c_k = 0; c_k <= b_vectorUB; c_k += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&Integrand[c_k]);
        _mm_storeu_pd(&Integrand[c_k], _mm_sqrt_pd(r3));
    }
    for (c_k = b_scalarLB; c_k < i15; c_k++) {
        Integrand[c_k] = std::sqrt(Integrand[c_k]);
    }
    sqrt_calls++;
    b_Integrand.set_size(1, Integrand.size(1));
    j_loop_ub = Integrand.size(1);
    c_scalarLB = (Integrand.size(1) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (i16 = 0; i16 <= c_vectorUB; i16 += 2) {
        __m128d r4;
        __m128d r5;
        r4 = _mm_loadu_pd(&Integrand[i16]);
        r5 = _mm_loadu_pd(&du_tilda[i16]);
        _mm_storeu_pd(&b_Integrand[i16], _mm_mul_pd(r4, r5));
    }
    for (i16 = c_scalarLB; i16 < j_loop_ub; i16++) {
        b_Integrand[i16] = Integrand[i16] * du_tilda[i16];
    }
    double b_L;
    b_L = coder::sum(b_Integrand);
    *L = b_L;
}

//
// computes approximately the arc length of a parametric spline
//
// Arguments    : const queue_coder *ctx_q_splines
//                double ctx_cfg_NGridLengthSpline
//                int Curv_sp_index
//                double u0_tilda
//                double u1_tilda
// Return Type  : double
//
double SplineLengthApprox(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                          int Curv_sp_index, double u0_tilda, double u1_tilda)
{
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1Dx;
    ::coder::array<double, 2U> r1Dy;
    ::coder::array<double, 2U> r1Dz;
    ::coder::array<double, 2U> u_mid_tilda;
    ::coder::array<double, 2U> u_tilda;
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 2U> z1;
    ::coder::array<bool, 2U> b_expl_temp;
    CurvStruct expl_temp;
    int Idx2_size[2];
    int Idx1_data;
    int Idx2_data;
    int N;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int c_loop_ub;
    int c_scalarLB;
    int c_vectorUB;
    int d_k;
    int d_loop_ub;
    int e_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i10;
    int i16;
    int i17;
    int i3;
    int i4;
    int i6;
    int i8;
    int i_loop_ub;
    int j_loop_ub;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    //  get the sp structure
    ctx_q_splines->get(Curv_sp_index, &expl_temp);
    //  the ORIGINAL spline is parametrized with u_tilda
    //  after cut-off, new parameter is called u.
    //  u=0 corresponds to the first lift-off point
    //  u=1 corresponds to the second lift-off point
    //  u is NOT used in this function
    //  if coder.target('matlab')
    //      % derivative whith respect to u_tilda !!!
    //      sp1D      = fnder(sp);
    //      Knots     = sp1D.knots;
    //  else
    //  end
    b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
    loop_ub = expl_temp.sp.knots.size(1);
    for (int i{0}; i < loop_ub; i++) {
        b_expl_temp[i] = (expl_temp.sp.knots[i] > u0_tilda);
    }
    coder::eml_find(b_expl_temp, (int *)&Idx2_data, Idx2_size);
    b_loop_ub = Idx2_size[1];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        Idx1_data = Idx2_data;
    }
    b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
    c_loop_ub = expl_temp.sp.knots.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        b_expl_temp[i2] = (expl_temp.sp.knots[i2] < u1_tilda);
    }
    coder::b_eml_find(b_expl_temp, (int *)&Idx2_data, Idx2_size);
    if (Idx1_data > Idx2_data) {
        i3 = 0;
        i4 = 0;
    } else {
        i3 = Idx1_data - 1;
        i4 = Idx2_data;
    }
    d_loop_ub = i4 - i3;
    u_vec_tilda.set_size(1, d_loop_ub + 2);
    u_vec_tilda[0] = u0_tilda;
    for (int i5{0}; i5 < d_loop_ub; i5++) {
        u_vec_tilda[i5 + 1] = expl_temp.sp.knots[i3 + i5];
    }
    u_vec_tilda[d_loop_ub + 1] = u1_tilda;
    u_tilda.set_size(1, 0);
    //  N equally spaced u_tilda values between each pair of knots
    //  from u0_tilda until u1_tilda
    i6 = u_vec_tilda.size(1);
    for (int k{0}; k <= i6 - 2; k++) {
        int f_loop_ub;
        int i7;
        int i9;
        i7 = u_tilda.size(1);
        if (u_tilda.size(1) != 0) {
            if (1 > u_tilda.size(1) - 1) {
                i7 = 0;
            } else {
                i7 = u_tilda.size(1) - 1;
            }
        }
        coder::linspace(u_vec_tilda[k], u_vec_tilda[k + 1], ctx_cfg_NGridLengthSpline, r);
        i9 = i7;
        f_loop_ub = r.size(1);
        i7 += r.size(1);
        u_tilda.set_size(u_tilda.size(0), i7);
        for (int i11{0}; i11 < f_loop_ub; i11++) {
            u_tilda[i9 + i11] = r[i11];
        }
    }
    //  midpoint values
    if (1 > u_tilda.size(1) - 1) {
        e_loop_ub = 0;
    } else {
        e_loop_ub = u_tilda.size(1) - 1;
    }
    i8 = (2 <= u_tilda.size(1));
    u_mid_tilda.set_size(1, e_loop_ub);
    scalarLB = (e_loop_ub / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i10 = 0; i10 <= vectorUB; i10 += 2) {
        __m128d r1;
        __m128d r2;
        r1 = _mm_loadu_pd(&u_tilda[i10]);
        r2 = _mm_loadu_pd(&u_tilda[i8 + i10]);
        _mm_storeu_pd(&u_mid_tilda[i10], _mm_mul_pd(_mm_set1_pd(0.5), _mm_add_pd(r1, r2)));
    }
    for (i10 = scalarLB; i10 < e_loop_ub; i10++) {
        u_mid_tilda[i10] = 0.5 * (u_tilda[i10] + u_tilda[i8 + i10]);
    }
    //  midpoint values
    //  parametric derivative calculation at each midpoint value
    //  with respect to u_tilda
    //  if coder.target('rtw') || coder.target('mex')
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_mid_tilda, a__1, r1Dx);
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_mid_tilda, a__2, r1Dy);
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_mid_tilda, a__3, r1Dz);
    //  else
    //      r1D = spval(sp1D, u_mid_tilda);
    //  end
    //  length (between u0_tilda and u1_tilda) calculation by rectangles method
    sqrt_calls++;
    a.set_size(3, r1Dx.size(1));
    g_loop_ub = r1Dx.size(1);
    for (int i12{0}; i12 < g_loop_ub; i12++) {
        a[3 * i12] = r1Dx[i12];
    }
    h_loop_ub = r1Dy.size(1);
    for (int i13{0}; i13 < h_loop_ub; i13++) {
        a[3 * i13 + 1] = r1Dy[i13];
    }
    i_loop_ub = r1Dz.size(1);
    for (int i14{0}; i14 < i_loop_ub; i14++) {
        a[3 * i14 + 2] = r1Dz[i14];
    }
    z1.set_size(3, a.size(1));
    N = a.size(1);
    for (int b_k{0}; b_k < N; b_k++) {
        z1[3 * b_k] = std::pow(a[3 * b_k], 2.0);
        z1[3 * b_k + 1] = std::pow(a[3 * b_k + 1], 2.0);
        z1[3 * b_k + 2] = std::pow(a[3 * b_k + 2], 2.0);
    }
    if (z1.size(1) == 0) {
        x.set_size(1, 0);
    } else {
        int i15;
        x.set_size(1, z1.size(1));
        i15 = z1.size(1);
        for (int c_k{0}; c_k < i15; c_k++) {
            x[c_k] = z1[3 * c_k];
            x[c_k] = x[c_k] + z1[3 * c_k + 1];
            x[c_k] = x[c_k] + z1[3 * c_k + 2];
        }
    }
    i16 = x.size(1);
    b_scalarLB = (x.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (d_k = 0; d_k <= b_vectorUB; d_k += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&x[d_k]);
        _mm_storeu_pd(&x[d_k], _mm_sqrt_pd(r3));
    }
    for (d_k = b_scalarLB; d_k < i16; d_k++) {
        x[d_k] = std::sqrt(x[d_k]);
    }
    coder::diff(u_tilda, r);
    x.set_size(1, x.size(1));
    j_loop_ub = x.size(1);
    c_scalarLB = (x.size(1) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (i17 = 0; i17 <= c_vectorUB; i17 += 2) {
        __m128d r4;
        __m128d r5;
        r4 = _mm_loadu_pd(&x[i17]);
        r5 = _mm_loadu_pd(&r[i17]);
        _mm_storeu_pd(&x[i17], _mm_mul_pd(r4, r5));
    }
    for (i17 = c_scalarLB; i17 < j_loop_ub; i17++) {
        x[i17] = x[i17] * r[i17];
    }
    return coder::sum(x);
}

} // namespace ocn

//
// File trailer for SplineLengthApprox.cpp
//
// [EOF]
//
