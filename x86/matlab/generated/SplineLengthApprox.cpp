//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApprox.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

// Include Files
#include "SplineLengthApprox.h"
#include "bspline_eval_vec.h"
#include "diff.h"
#include "eml_mtimes_helper.h"
#include "find.h"
#include "linspace.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "sinspace_types3.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static double binary_expand_op(const ::coder::array<double, 2U> &x,
                               const ::coder::array<double, 2U> &r);

}

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
//                const ::coder::array<double, 2U> &r
// Return Type  : double
//
namespace ocn {
static double binary_expand_op(const ::coder::array<double, 2U> &x,
                               const ::coder::array<double, 2U> &r)
{
    ::coder::array<double, 2U> b_x;
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (r.size(1) == 1) {
        i = x.size(1);
    } else {
        i = r.size(1);
    }
    b_x.set_size(1, i);
    stride_0_1 = (x.size(1) != 1);
    stride_1_1 = (r.size(1) != 1);
    if (r.size(1) == 1) {
        loop_ub = x.size(1);
    } else {
        loop_ub = r.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        b_x[i1] = x[i1 * stride_0_1] * r[i1 * stride_1_1];
    }
    return coder::sum(b_x);
}

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
double SplineLengthApprox(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                          int Curv_sp_index, const double u0_tilda_data[],
                          const int u0_tilda_size[2], double u1_tilda)
{
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> b_r1Dx;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1Dx;
    ::coder::array<double, 2U> r1Dy;
    ::coder::array<double, 2U> r1Dz;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> u_mid_tilda;
    ::coder::array<double, 2U> u_tilda;
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<double, 2U> x;
    ::coder::array<bool, 2U> b_expl_temp;
    CurvStruct expl_temp;
    double L;
    int Idx2_size[2];
    int Idx1_data;
    int Idx2_data;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int c_k;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int h_loop_ub;
    int i10;
    int i11;
    int i19;
    int i3;
    int i4;
    int i7;
    int i_loop_ub;
    int j_loop_ub;
    int k_loop_ub;
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
    if (expl_temp.sp.knots.size(1) == u0_tilda_size[1]) {
        int loop_ub;
        b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
        loop_ub = expl_temp.sp.knots.size(1);
        for (int i{0}; i < loop_ub; i++) {
            b_expl_temp[i] = (expl_temp.sp.knots[i] > u0_tilda_data[i]);
        }
        coder::eml_find(b_expl_temp, (int *)&Idx2_data, Idx2_size);
    } else {
        binary_expand_op((int *)&Idx2_data, Idx2_size, &expl_temp, u0_tilda_data, u0_tilda_size);
    }
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
    u_vec_tilda.set_size(1, ((u0_tilda_size[1] + i4) - i3) + 1);
    d_loop_ub = u0_tilda_size[1];
    for (int i5{0}; i5 < d_loop_ub; i5++) {
        u_vec_tilda[0] = u0_tilda_data[0];
    }
    e_loop_ub = i4 - i3;
    for (int i6{0}; i6 < e_loop_ub; i6++) {
        u_vec_tilda[i6 + u0_tilda_size[1]] = expl_temp.sp.knots[i3 + i6];
    }
    u_vec_tilda[(u0_tilda_size[1] + i4) - i3] = u1_tilda;
    u_tilda.set_size(1, 0);
    //  N equally spaced u_tilda values between each pair of knots
    //  from u0_tilda until u1_tilda
    i7 = u_vec_tilda.size(1);
    for (int k{0}; k <= i7 - 2; k++) {
        int g_loop_ub;
        int i8;
        int i9;
        i8 = u_tilda.size(1);
        if (u_tilda.size(1) != 0) {
            if (1 > u_tilda.size(1) - 1) {
                i8 = 0;
            } else {
                i8 = u_tilda.size(1) - 1;
            }
        }
        coder::linspace(u_vec_tilda[k], u_vec_tilda[k + 1], ctx_cfg_NGridLengthSpline, r);
        i9 = i8;
        g_loop_ub = r.size(1);
        i8 += r.size(1);
        u_tilda.set_size(u_tilda.size(0), i8);
        for (int i12{0}; i12 < g_loop_ub; i12++) {
            u_tilda[i9 + i12] = r[i12];
        }
    }
    //  midpoint values
    if (1 > u_tilda.size(1) - 1) {
        f_loop_ub = 0;
    } else {
        f_loop_ub = u_tilda.size(1) - 1;
    }
    if (2 > u_tilda.size(1)) {
        i10 = 0;
        i11 = 0;
    } else {
        i10 = 1;
        i11 = u_tilda.size(1);
    }
    if (f_loop_ub == i11 - i10) {
        int i13;
        int scalarLB;
        int vectorUB;
        u_mid_tilda.set_size(1, f_loop_ub);
        scalarLB = (f_loop_ub / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i13 = 0; i13 <= vectorUB; i13 += 2) {
            __m128d r1;
            __m128d r2;
            r1 = _mm_loadu_pd(&u_tilda[i13]);
            r2 = _mm_loadu_pd(&u_tilda[i10 + i13]);
            _mm_storeu_pd(&u_mid_tilda[i13], _mm_mul_pd(_mm_set1_pd(0.5), _mm_add_pd(r1, r2)));
        }
        for (i13 = scalarLB; i13 < f_loop_ub; i13++) {
            u_mid_tilda[i13] = 0.5 * (u_tilda[i13] + u_tilda[i10 + i13]);
        }
    } else {
        binary_expand_op(u_mid_tilda, u_tilda, f_loop_ub - 1, i10, i11 - 1);
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
    b_r1Dx.set_size(3, r1Dx.size(1));
    h_loop_ub = r1Dx.size(1);
    for (int i14{0}; i14 < h_loop_ub; i14++) {
        b_r1Dx[3 * i14] = r1Dx[i14];
    }
    i_loop_ub = r1Dy.size(1);
    for (int i15{0}; i15 < i_loop_ub; i15++) {
        b_r1Dx[3 * i15 + 1] = r1Dy[i15];
    }
    j_loop_ub = r1Dz.size(1);
    for (int i16{0}; i16 < j_loop_ub; i16++) {
        b_r1Dx[3 * i16 + 2] = r1Dz[i16];
    }
    r3.set_size(3, b_r1Dx.size(1));
    k_loop_ub = b_r1Dx.size(1);
    for (int i17{0}; i17 < k_loop_ub; i17++) {
        double b_varargin_1;
        double c_varargin_1;
        double varargin_1;
        varargin_1 = b_r1Dx[3 * i17];
        r3[3 * i17] = std::pow(varargin_1, 2.0);
        b_varargin_1 = b_r1Dx[3 * i17 + 1];
        r3[3 * i17 + 1] = std::pow(b_varargin_1, 2.0);
        c_varargin_1 = b_r1Dx[3 * i17 + 2];
        r3[3 * i17 + 2] = std::pow(c_varargin_1, 2.0);
    }
    if (r3.size(1) == 0) {
        x.set_size(1, 0);
    } else {
        int i18;
        x.set_size(1, r3.size(1));
        i18 = r3.size(1);
        for (int b_k{0}; b_k < i18; b_k++) {
            x[b_k] = r3[3 * b_k];
            x[b_k] = x[b_k] + r3[3 * b_k + 1];
            x[b_k] = x[b_k] + r3[3 * b_k + 2];
        }
    }
    i19 = x.size(1);
    b_scalarLB = (x.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (c_k = 0; c_k <= b_vectorUB; c_k += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&x[c_k]);
        _mm_storeu_pd(&x[c_k], _mm_sqrt_pd(r4));
    }
    for (c_k = b_scalarLB; c_k < i19; c_k++) {
        x[c_k] = std::sqrt(x[c_k]);
    }
    coder::diff(u_tilda, r);
    if (x.size(1) == r.size(1)) {
        int c_scalarLB;
        int c_vectorUB;
        int i20;
        int l_loop_ub;
        x.set_size(1, x.size(1));
        l_loop_ub = x.size(1);
        c_scalarLB = (x.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (i20 = 0; i20 <= c_vectorUB; i20 += 2) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&x[i20]);
            r6 = _mm_loadu_pd(&r[i20]);
            _mm_storeu_pd(&x[i20], _mm_mul_pd(r5, r6));
        }
        for (i20 = c_scalarLB; i20 < l_loop_ub; i20++) {
            x[i20] = x[i20] * r[i20];
        }
        L = coder::sum(x);
    } else {
        L = binary_expand_op(x, r);
    }
    return L;
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
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> b_r1Dx;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1Dx;
    ::coder::array<double, 2U> r1Dy;
    ::coder::array<double, 2U> r1Dz;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> u_mid_tilda;
    ::coder::array<double, 2U> u_tilda;
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<double, 2U> x;
    ::coder::array<bool, 2U> b_expl_temp;
    CurvStruct expl_temp;
    double L;
    int Idx2_size[2];
    int Idx1_data;
    int Idx2_data;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int c_k;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int h_loop_ub;
    int i10;
    int i11;
    int i19;
    int i3;
    int i4;
    int i7;
    int i_loop_ub;
    int j_loop_ub;
    int k_loop_ub;
    int loop_ub;
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
    if (expl_temp.sp.knots.size(1) == u1_tilda_size[1]) {
        int c_loop_ub;
        b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
        c_loop_ub = expl_temp.sp.knots.size(1);
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            b_expl_temp[i2] = (expl_temp.sp.knots[i2] < u1_tilda_data[i2]);
        }
        coder::b_eml_find(b_expl_temp, (int *)&Idx2_data, Idx2_size);
    } else {
        b_binary_expand_op((int *)&Idx2_data, Idx2_size, &expl_temp, u1_tilda_data, u1_tilda_size);
    }
    if (Idx1_data > Idx2_data) {
        i3 = -2;
        i4 = -1;
    } else {
        i3 = Idx1_data - 3;
        i4 = Idx2_data - 1;
    }
    d_loop_ub = i4 - i3;
    u_vec_tilda.set_size(1, d_loop_ub + u1_tilda_size[1]);
    u_vec_tilda[0] = u0_tilda;
    for (int i5{0}; i5 <= d_loop_ub - 2; i5++) {
        u_vec_tilda[i5 + 1] = expl_temp.sp.knots[(i3 + i5) + 2];
    }
    e_loop_ub = u1_tilda_size[1];
    for (int i6{0}; i6 < e_loop_ub; i6++) {
        u_vec_tilda[d_loop_ub] = u1_tilda_data[0];
    }
    u_tilda.set_size(1, 0);
    //  N equally spaced u_tilda values between each pair of knots
    //  from u0_tilda until u1_tilda
    i7 = u_vec_tilda.size(1);
    for (int k{0}; k <= i7 - 2; k++) {
        int g_loop_ub;
        int i8;
        int i9;
        i8 = u_tilda.size(1);
        if (u_tilda.size(1) != 0) {
            if (1 > u_tilda.size(1) - 1) {
                i8 = 0;
            } else {
                i8 = u_tilda.size(1) - 1;
            }
        }
        coder::linspace(u_vec_tilda[k], u_vec_tilda[k + 1], ctx_cfg_NGridLengthSpline, r);
        i9 = i8;
        g_loop_ub = r.size(1);
        i8 += r.size(1);
        u_tilda.set_size(u_tilda.size(0), i8);
        for (int i12{0}; i12 < g_loop_ub; i12++) {
            u_tilda[i9 + i12] = r[i12];
        }
    }
    //  midpoint values
    if (1 > u_tilda.size(1) - 1) {
        f_loop_ub = 0;
    } else {
        f_loop_ub = u_tilda.size(1) - 1;
    }
    if (2 > u_tilda.size(1)) {
        i10 = 0;
        i11 = 0;
    } else {
        i10 = 1;
        i11 = u_tilda.size(1);
    }
    if (f_loop_ub == i11 - i10) {
        int i13;
        int scalarLB;
        int vectorUB;
        u_mid_tilda.set_size(1, f_loop_ub);
        scalarLB = (f_loop_ub / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i13 = 0; i13 <= vectorUB; i13 += 2) {
            __m128d r1;
            __m128d r2;
            r1 = _mm_loadu_pd(&u_tilda[i13]);
            r2 = _mm_loadu_pd(&u_tilda[i10 + i13]);
            _mm_storeu_pd(&u_mid_tilda[i13], _mm_mul_pd(_mm_set1_pd(0.5), _mm_add_pd(r1, r2)));
        }
        for (i13 = scalarLB; i13 < f_loop_ub; i13++) {
            u_mid_tilda[i13] = 0.5 * (u_tilda[i13] + u_tilda[i10 + i13]);
        }
    } else {
        binary_expand_op(u_mid_tilda, u_tilda, f_loop_ub - 1, i10, i11 - 1);
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
    b_r1Dx.set_size(3, r1Dx.size(1));
    h_loop_ub = r1Dx.size(1);
    for (int i14{0}; i14 < h_loop_ub; i14++) {
        b_r1Dx[3 * i14] = r1Dx[i14];
    }
    i_loop_ub = r1Dy.size(1);
    for (int i15{0}; i15 < i_loop_ub; i15++) {
        b_r1Dx[3 * i15 + 1] = r1Dy[i15];
    }
    j_loop_ub = r1Dz.size(1);
    for (int i16{0}; i16 < j_loop_ub; i16++) {
        b_r1Dx[3 * i16 + 2] = r1Dz[i16];
    }
    r3.set_size(3, b_r1Dx.size(1));
    k_loop_ub = b_r1Dx.size(1);
    for (int i17{0}; i17 < k_loop_ub; i17++) {
        double b_varargin_1;
        double c_varargin_1;
        double varargin_1;
        varargin_1 = b_r1Dx[3 * i17];
        r3[3 * i17] = std::pow(varargin_1, 2.0);
        b_varargin_1 = b_r1Dx[3 * i17 + 1];
        r3[3 * i17 + 1] = std::pow(b_varargin_1, 2.0);
        c_varargin_1 = b_r1Dx[3 * i17 + 2];
        r3[3 * i17 + 2] = std::pow(c_varargin_1, 2.0);
    }
    if (r3.size(1) == 0) {
        x.set_size(1, 0);
    } else {
        int i18;
        x.set_size(1, r3.size(1));
        i18 = r3.size(1);
        for (int b_k{0}; b_k < i18; b_k++) {
            x[b_k] = r3[3 * b_k];
            x[b_k] = x[b_k] + r3[3 * b_k + 1];
            x[b_k] = x[b_k] + r3[3 * b_k + 2];
        }
    }
    i19 = x.size(1);
    b_scalarLB = (x.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (c_k = 0; c_k <= b_vectorUB; c_k += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&x[c_k]);
        _mm_storeu_pd(&x[c_k], _mm_sqrt_pd(r4));
    }
    for (c_k = b_scalarLB; c_k < i19; c_k++) {
        x[c_k] = std::sqrt(x[c_k]);
    }
    coder::diff(u_tilda, r);
    if (x.size(1) == r.size(1)) {
        int c_scalarLB;
        int c_vectorUB;
        int i20;
        int l_loop_ub;
        x.set_size(1, x.size(1));
        l_loop_ub = x.size(1);
        c_scalarLB = (x.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (i20 = 0; i20 <= c_vectorUB; i20 += 2) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&x[i20]);
            r6 = _mm_loadu_pd(&r[i20]);
            _mm_storeu_pd(&x[i20], _mm_mul_pd(r5, r6));
        }
        for (i20 = c_scalarLB; i20 < l_loop_ub; i20++) {
            x[i20] = x[i20] * r[i20];
        }
        L = coder::sum(x);
    } else {
        L = binary_expand_op(x, r);
    }
    return L;
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
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> b_Integrand;
    ::coder::array<double, 2U> b_r1Dx;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1Dx;
    ::coder::array<double, 2U> r1Dy;
    ::coder::array<double, 2U> r1Dz;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> u_tilda;
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<bool, 2U> b_expl_temp;
    CurvStruct expl_temp;
    double b_L;
    int Idx2_size[2];
    int Idx1_data;
    int Idx2_data;
    int b_k;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i10;
    int i17;
    int i3;
    int i4;
    int i6;
    int i9;
    int i_loop_ub;
    int j_loop_ub;
    int loop_ub;
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
        int i8;
        i7 = u_tilda.size(1);
        if (u_tilda.size(1) != 0) {
            if (1 > u_tilda.size(1) - 1) {
                i7 = 0;
            } else {
                i7 = u_tilda.size(1) - 1;
            }
        }
        coder::linspace(u_vec_tilda[k], u_vec_tilda[k + 1], ctx_cfg_NGridLengthSpline, r);
        i8 = i7;
        f_loop_ub = r.size(1);
        i7 += r.size(1);
        u_tilda.set_size(u_tilda.size(0), i7);
        for (int i11{0}; i11 < f_loop_ub; i11++) {
            u_tilda[i8 + i11] = r[i11];
        }
    }
    //  midpoint values
    if (1 > u_tilda.size(1) - 1) {
        e_loop_ub = 0;
    } else {
        e_loop_ub = u_tilda.size(1) - 1;
    }
    if (2 > u_tilda.size(1)) {
        i9 = 0;
        i10 = 0;
    } else {
        i9 = 1;
        i10 = u_tilda.size(1);
    }
    if (e_loop_ub == i10 - i9) {
        int i12;
        int scalarLB;
        int vectorUB;
        u_mid_tilda.set_size(1, e_loop_ub);
        scalarLB = (e_loop_ub / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i12 = 0; i12 <= vectorUB; i12 += 2) {
            __m128d r1;
            __m128d r2;
            r1 = _mm_loadu_pd(&u_tilda[i12]);
            r2 = _mm_loadu_pd(&u_tilda[i9 + i12]);
            _mm_storeu_pd(&u_mid_tilda[i12], _mm_mul_pd(_mm_set1_pd(0.5), _mm_add_pd(r1, r2)));
        }
        for (i12 = scalarLB; i12 < e_loop_ub; i12++) {
            u_mid_tilda[i12] = 0.5 * (u_tilda[i12] + u_tilda[i9 + i12]);
        }
    } else {
        binary_expand_op(u_mid_tilda, u_tilda, e_loop_ub - 1, i9, i10 - 1);
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
    b_r1Dx.set_size(3, r1Dx.size(1));
    g_loop_ub = r1Dx.size(1);
    for (int i13{0}; i13 < g_loop_ub; i13++) {
        b_r1Dx[3 * i13] = r1Dx[i13];
    }
    h_loop_ub = r1Dy.size(1);
    for (int i14{0}; i14 < h_loop_ub; i14++) {
        b_r1Dx[3 * i14 + 1] = r1Dy[i14];
    }
    i_loop_ub = r1Dz.size(1);
    for (int i15{0}; i15 < i_loop_ub; i15++) {
        b_r1Dx[3 * i15 + 2] = r1Dz[i15];
    }
    r3.set_size(3, b_r1Dx.size(1));
    j_loop_ub = b_r1Dx.size(1);
    for (int i16{0}; i16 < j_loop_ub; i16++) {
        double b_varargin_1;
        double c_varargin_1;
        double varargin_1;
        varargin_1 = b_r1Dx[3 * i16];
        r3[3 * i16] = std::pow(varargin_1, 2.0);
        b_varargin_1 = b_r1Dx[3 * i16 + 1];
        r3[3 * i16 + 1] = std::pow(b_varargin_1, 2.0);
        c_varargin_1 = b_r1Dx[3 * i16 + 2];
        r3[3 * i16 + 2] = std::pow(c_varargin_1, 2.0);
    }
    coder::sum(r3, Integrand);
    i17 = Integrand.size(1);
    b_scalarLB = (Integrand.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (b_k = 0; b_k <= b_vectorUB; b_k += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&Integrand[b_k]);
        _mm_storeu_pd(&Integrand[b_k], _mm_sqrt_pd(r4));
    }
    for (b_k = b_scalarLB; b_k < i17; b_k++) {
        Integrand[b_k] = std::sqrt(Integrand[b_k]);
    }
    sqrt_calls++;
    if (Integrand.size(1) == du_tilda.size(1)) {
        int c_scalarLB;
        int c_vectorUB;
        int i18;
        int k_loop_ub;
        b_Integrand.set_size(1, Integrand.size(1));
        k_loop_ub = Integrand.size(1);
        c_scalarLB = (Integrand.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (i18 = 0; i18 <= c_vectorUB; i18 += 2) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&Integrand[i18]);
            r6 = _mm_loadu_pd(&du_tilda[i18]);
            _mm_storeu_pd(&b_Integrand[i18], _mm_mul_pd(r5, r6));
        }
        for (i18 = c_scalarLB; i18 < k_loop_ub; i18++) {
            b_Integrand[i18] = Integrand[i18] * du_tilda[i18];
        }
        b_L = coder::sum(b_Integrand);
    } else {
        b_L = binary_expand_op(Integrand, du_tilda);
    }
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
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> b_r1Dx;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1Dx;
    ::coder::array<double, 2U> r1Dy;
    ::coder::array<double, 2U> r1Dz;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> u_mid_tilda;
    ::coder::array<double, 2U> u_tilda;
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<double, 2U> x;
    ::coder::array<bool, 2U> b_expl_temp;
    CurvStruct expl_temp;
    double L;
    int Idx2_size[2];
    int Idx1_data;
    int Idx2_data;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int c_k;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i10;
    int i18;
    int i3;
    int i4;
    int i6;
    int i9;
    int i_loop_ub;
    int j_loop_ub;
    int loop_ub;
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
        int i8;
        i7 = u_tilda.size(1);
        if (u_tilda.size(1) != 0) {
            if (1 > u_tilda.size(1) - 1) {
                i7 = 0;
            } else {
                i7 = u_tilda.size(1) - 1;
            }
        }
        coder::linspace(u_vec_tilda[k], u_vec_tilda[k + 1], ctx_cfg_NGridLengthSpline, r);
        i8 = i7;
        f_loop_ub = r.size(1);
        i7 += r.size(1);
        u_tilda.set_size(u_tilda.size(0), i7);
        for (int i11{0}; i11 < f_loop_ub; i11++) {
            u_tilda[i8 + i11] = r[i11];
        }
    }
    //  midpoint values
    if (1 > u_tilda.size(1) - 1) {
        e_loop_ub = 0;
    } else {
        e_loop_ub = u_tilda.size(1) - 1;
    }
    if (2 > u_tilda.size(1)) {
        i9 = 0;
        i10 = 0;
    } else {
        i9 = 1;
        i10 = u_tilda.size(1);
    }
    if (e_loop_ub == i10 - i9) {
        int i12;
        int scalarLB;
        int vectorUB;
        u_mid_tilda.set_size(1, e_loop_ub);
        scalarLB = (e_loop_ub / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i12 = 0; i12 <= vectorUB; i12 += 2) {
            __m128d r1;
            __m128d r2;
            r1 = _mm_loadu_pd(&u_tilda[i12]);
            r2 = _mm_loadu_pd(&u_tilda[i9 + i12]);
            _mm_storeu_pd(&u_mid_tilda[i12], _mm_mul_pd(_mm_set1_pd(0.5), _mm_add_pd(r1, r2)));
        }
        for (i12 = scalarLB; i12 < e_loop_ub; i12++) {
            u_mid_tilda[i12] = 0.5 * (u_tilda[i12] + u_tilda[i9 + i12]);
        }
    } else {
        binary_expand_op(u_mid_tilda, u_tilda, e_loop_ub - 1, i9, i10 - 1);
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
    b_r1Dx.set_size(3, r1Dx.size(1));
    g_loop_ub = r1Dx.size(1);
    for (int i13{0}; i13 < g_loop_ub; i13++) {
        b_r1Dx[3 * i13] = r1Dx[i13];
    }
    h_loop_ub = r1Dy.size(1);
    for (int i14{0}; i14 < h_loop_ub; i14++) {
        b_r1Dx[3 * i14 + 1] = r1Dy[i14];
    }
    i_loop_ub = r1Dz.size(1);
    for (int i15{0}; i15 < i_loop_ub; i15++) {
        b_r1Dx[3 * i15 + 2] = r1Dz[i15];
    }
    r3.set_size(3, b_r1Dx.size(1));
    j_loop_ub = b_r1Dx.size(1);
    for (int i16{0}; i16 < j_loop_ub; i16++) {
        double b_varargin_1;
        double c_varargin_1;
        double varargin_1;
        varargin_1 = b_r1Dx[3 * i16];
        r3[3 * i16] = std::pow(varargin_1, 2.0);
        b_varargin_1 = b_r1Dx[3 * i16 + 1];
        r3[3 * i16 + 1] = std::pow(b_varargin_1, 2.0);
        c_varargin_1 = b_r1Dx[3 * i16 + 2];
        r3[3 * i16 + 2] = std::pow(c_varargin_1, 2.0);
    }
    if (r3.size(1) == 0) {
        x.set_size(1, 0);
    } else {
        int i17;
        x.set_size(1, r3.size(1));
        i17 = r3.size(1);
        for (int b_k{0}; b_k < i17; b_k++) {
            x[b_k] = r3[3 * b_k];
            x[b_k] = x[b_k] + r3[3 * b_k + 1];
            x[b_k] = x[b_k] + r3[3 * b_k + 2];
        }
    }
    i18 = x.size(1);
    b_scalarLB = (x.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (c_k = 0; c_k <= b_vectorUB; c_k += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&x[c_k]);
        _mm_storeu_pd(&x[c_k], _mm_sqrt_pd(r4));
    }
    for (c_k = b_scalarLB; c_k < i18; c_k++) {
        x[c_k] = std::sqrt(x[c_k]);
    }
    coder::diff(u_tilda, r);
    if (x.size(1) == r.size(1)) {
        int c_scalarLB;
        int c_vectorUB;
        int i19;
        int k_loop_ub;
        x.set_size(1, x.size(1));
        k_loop_ub = x.size(1);
        c_scalarLB = (x.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (i19 = 0; i19 <= c_vectorUB; i19 += 2) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&x[i19]);
            r6 = _mm_loadu_pd(&r[i19]);
            _mm_storeu_pd(&x[i19], _mm_mul_pd(r5, r6));
        }
        for (i19 = c_scalarLB; i19 < k_loop_ub; i19++) {
            x[i19] = x[i19] * r[i19];
        }
        L = coder::sum(x);
    } else {
        L = binary_expand_op(x, r);
    }
    return L;
}

} // namespace ocn

//
// File trailer for SplineLengthApprox.cpp
//
// [EOF]
//
