//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApproxGL_tot.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 08:27:14
//

// Include Files
#include "SplineLengthApproxGL_tot.h"
#include "EvalBSplineNoCtx.h"
#include "EvalCurvStruct_data.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &Lk, const ::coder::array<double, 2U> &y,
                             const ::coder::array<double, 2U> &Curv_sp_knots, int i4, int i5,
                             int i6);

static void c_binary_expand_op(::coder::array<double, 2U> &Umat,
                               const ::coder::array<double, 2U> &c,
                               const ::coder::array<double, 2U> &b_c);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &Lk
//                const ::coder::array<double, 2U> &y
//                const ::coder::array<double, 2U> &Curv_sp_knots
//                int i4
//                int i5
//                int i6
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &Lk, const ::coder::array<double, 2U> &y,
                             const ::coder::array<double, 2U> &Curv_sp_knots, int i4, int i5,
                             int i6)
{
    int i;
    int i1;
    int i2;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    int stride_2_1;
    if (i6 + 1 == 1) {
        i = (i5 - i4) + 1;
    } else {
        i = i6 + 1;
    }
    if (i == 1) {
        i1 = y.size(1);
    } else if (i6 + 1 == 1) {
        i1 = (i5 - i4) + 1;
    } else {
        i1 = i6 + 1;
    }
    Lk.set_size(1, i1);
    stride_0_1 = (y.size(1) != 1);
    stride_1_1 = ((i5 - i4) + 1 != 1);
    stride_2_1 = (i6 + 1 != 1);
    if (i6 + 1 == 1) {
        i2 = (i5 - i4) + 1;
    } else {
        i2 = i6 + 1;
    }
    if (i2 == 1) {
        loop_ub = y.size(1);
    } else if (i6 + 1 == 1) {
        loop_ub = (i5 - i4) + 1;
    } else {
        loop_ub = i6 + 1;
    }
    for (int i3{0}; i3 < loop_ub; i3++) {
        Lk[i3] = y[i3 * stride_0_1] *
                 (Curv_sp_knots[(i4 + i3 * stride_1_1) + 3] - Curv_sp_knots[i3 * stride_2_1 + 3]) /
                 2.0;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &Umat
//                const ::coder::array<double, 2U> &c
//                const ::coder::array<double, 2U> &b_c
// Return Type  : void
//
static void c_binary_expand_op(::coder::array<double, 2U> &Umat,
                               const ::coder::array<double, 2U> &c,
                               const ::coder::array<double, 2U> &b_c)
{
    int aux_0_1;
    int aux_1_1;
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (b_c.size(1) == 1) {
        i = c.size(1);
    } else {
        i = b_c.size(1);
    }
    Umat.set_size(5, i);
    stride_0_1 = (c.size(1) != 1);
    stride_1_1 = (b_c.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (b_c.size(1) == 1) {
        loop_ub = c.size(1);
    } else {
        loop_ub = b_c.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        __m128d r;
        __m128d r1;
        __m128d r2;
        r = _mm_loadu_pd((const double *)&c[5 * aux_0_1]);
        r1 = _mm_loadu_pd((const double *)&b_c[5 * aux_1_1]);
        r2 = _mm_set1_pd(2.0);
        _mm_storeu_pd(&Umat[5 * i1], _mm_div_pd(_mm_add_pd(r, r1), r2));
        r = _mm_loadu_pd((const double *)&c[5 * aux_0_1 + 2]);
        r1 = _mm_loadu_pd((const double *)&b_c[5 * aux_1_1 + 2]);
        _mm_storeu_pd(&Umat[5 * i1 + 2], _mm_div_pd(_mm_add_pd(r, r1), r2));
        Umat[5 * i1 + 4] = (c[5 * aux_0_1 + 4] + b_c[5 * aux_1_1 + 4]) / 2.0;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// function [L, Lk]  = SplineLengthApproxGL_tot(ctx, Curv)
//
// Precomputes approximately the total arc length L as well as the individual
//  arc lengths between knot points of a parametric spline.
//  The computation is based on numerical Gauss Legendre integration.
//  SplineLengthApproxGL_tot should only be called once since the result
//  of the computation is stored and reused later.
//
// Arguments    : double ctx_cfg_GaussLegendreN
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const ::coder::array<double, 2U> &Curv_sp_CoeffX
//                const ::coder::array<double, 2U> &Curv_sp_CoeffY
//                const ::coder::array<double, 2U> &Curv_sp_CoeffZ
//                unsigned long Curv_sp_Bl_handle
//                const ::coder::array<double, 2U> &Curv_sp_knots
//                double *L
//                ::coder::array<double, 2U> &Lk
// Return Type  : void
//
void SplineLengthApproxGL_tot(double ctx_cfg_GaussLegendreN, const double ctx_cfg_GaussLegendreX[5],
                              const double ctx_cfg_GaussLegendreW[5],
                              const ::coder::array<double, 2U> &Curv_sp_CoeffX,
                              const ::coder::array<double, 2U> &Curv_sp_CoeffY,
                              const ::coder::array<double, 2U> &Curv_sp_CoeffZ,
                              unsigned long Curv_sp_Bl_handle,
                              const ::coder::array<double, 2U> &Curv_sp_knots, double *L,
                              ::coder::array<double, 2U> &Lk)
{
    __m128d r;
    ::coder::array<double, 2U> Umat;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_Umat;
    ::coder::array<double, 2U> b_c;
    ::coder::array<double, 2U> c;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r1Dnorm;
    ::coder::array<double, 2U> r8;
    ::coder::array<double, 2U> y;
    double b[5];
    double b_L;
    int b_bcoef;
    int b_loop_ub;
    int c_loop_ub;
    int csz_idx_1_tmp;
    int ctx_cfg_GaussLegendreN_idx_0;
    int d_k;
    int i;
    int i1;
    int i10;
    int i13;
    int i2;
    int scalarLB;
    int vectorUB;
    int vlen;
    //  get the sp structure
    //  Spline = ctx.q_splines.get(Curv.sp_index);
    //  sp     = Spline.sp;
    // 'SplineLengthApproxGL_tot:11' sp     = Curv.sp;
    // 'SplineLengthApproxGL_tot:12' Knots  = sp.knots(4:end-3);
    //  eliminate multiplicities at the end points
    // 'SplineLengthApproxGL_tot:13' a      = Knots(1:end-1);
    if (1 > Curv_sp_knots.size(1) - 7) {
        i = 0;
    } else {
        i = Curv_sp_knots.size(1) - 7;
    }
    //  lower integration limits
    // 'SplineLengthApproxGL_tot:14' b      = Knots(2:end);
    if (2 > Curv_sp_knots.size(1) - 6) {
        i1 = -1;
        i2 = -1;
    } else {
        i1 = 0;
        i2 = Curv_sp_knots.size(1) - 7;
    }
    //  upper integration limits
    //  get Gauss-Legendre knots and weights
    // 'SplineLengthApproxGL_tot:16' GL_N   = ctx.cfg.GaussLegendreN;
    // 'SplineLengthApproxGL_tot:17' GL_X   = ctx.cfg.GaussLegendreX;
    // 'SplineLengthApproxGL_tot:18' GL_W   = ctx.cfg.GaussLegendreW;
    //  apply linear map from[-1, 1] to [a, b]
    // 'SplineLengthApproxGL_tot:20' Umat   = (bsxfun(@times, a, (1-GL_X)) + bsxfun(@times, b,
    // (1+GL_X)))/2;
    r = _mm_set1_pd(1.0);
    _mm_storeu_pd(&b[0], _mm_sub_pd(r, _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0])));
    _mm_storeu_pd(&b[2], _mm_sub_pd(r, _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2])));
    b[4] = 1.0 - ctx_cfg_GaussLegendreX[4];
    c.set_size(5, i);
    if (i != 0) {
        int acoef;
        int i3;
        acoef = (i != 1);
        i3 = i - 1;
        for (int k{0}; k <= i3; k++) {
            __m128d r1;
            __m128d r2;
            int varargin_2;
            varargin_2 = acoef * k + 3;
            r1 = _mm_loadu_pd(&b[0]);
            r2 = _mm_set1_pd(Curv_sp_knots[varargin_2]);
            _mm_storeu_pd(&c[5 * k], _mm_mul_pd(r2, r1));
            r1 = _mm_loadu_pd(&b[2]);
            _mm_storeu_pd(&c[5 * k + 2], _mm_mul_pd(r2, r1));
            c[5 * k + 4] = Curv_sp_knots[varargin_2] * b[4];
        }
    }
    _mm_storeu_pd(&b[0], _mm_add_pd(_mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0]), r));
    _mm_storeu_pd(&b[2], _mm_add_pd(_mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2]), r));
    b[4] = ctx_cfg_GaussLegendreX[4] + 1.0;
    csz_idx_1_tmp = i2 - i1;
    b_c.set_size(5, csz_idx_1_tmp);
    if (csz_idx_1_tmp != 0) {
        int b_acoef;
        int i4;
        b_acoef = (csz_idx_1_tmp != 1);
        i4 = csz_idx_1_tmp - 1;
        for (int b_k{0}; b_k <= i4; b_k++) {
            __m128d r3;
            __m128d r5;
            int i6;
            i6 = (i1 + b_acoef * b_k) + 4;
            r3 = _mm_loadu_pd(&b[0]);
            r5 = _mm_set1_pd(Curv_sp_knots[i6]);
            _mm_storeu_pd(&b_c[5 * b_k], _mm_mul_pd(r5, r3));
            r3 = _mm_loadu_pd(&b[2]);
            _mm_storeu_pd(&b_c[5 * b_k + 2], _mm_mul_pd(r5, r3));
            b_c[5 * b_k + 4] = Curv_sp_knots[i6] * b[4];
        }
    }
    if (c.size(1) == b_c.size(1)) {
        int loop_ub;
        Umat.set_size(5, c.size(1));
        loop_ub = c.size(1);
        for (int i5{0}; i5 < loop_ub; i5++) {
            __m128d r4;
            __m128d r6;
            __m128d r7;
            r4 = _mm_loadu_pd(&c[5 * i5]);
            r6 = _mm_loadu_pd(&b_c[5 * i5]);
            r7 = _mm_set1_pd(2.0);
            _mm_storeu_pd(&Umat[5 * i5], _mm_div_pd(_mm_add_pd(r4, r6), r7));
            r4 = _mm_loadu_pd(&c[5 * i5 + 2]);
            r6 = _mm_loadu_pd(&b_c[5 * i5 + 2]);
            _mm_storeu_pd(&Umat[5 * i5 + 2], _mm_div_pd(_mm_add_pd(r4, r6), r7));
            Umat[5 * i5 + 4] = (c[5 * i5 + 4] + b_c[5 * i5 + 4]) / 2.0;
        }
    } else {
        c_binary_expand_op(Umat, c, b_c);
    }
    // 'SplineLengthApproxGL_tot:21' Uvec   = Umat(:)';
    //  all evaluation points as row vector
    // 'SplineLengthApproxGL_tot:23' [~, r1D]  = EvalBSplineNoCtx(Curv, Uvec);
    b_loop_ub = 5 * Umat.size(1);
    b_Umat.set_size(1, b_loop_ub);
    for (int i7{0}; i7 < b_loop_ub; i7++) {
        b_Umat[i7] = Umat[i7];
    }
    EvalBSplineNoCtx(Curv_sp_CoeffX, Curv_sp_CoeffY, Curv_sp_CoeffZ, Curv_sp_Bl_handle, b_Umat,
                     a__1, r1D);
    // 'SplineLengthApproxGL_tot:24' r1Dnorm   = MyNorm(r1D);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    // 'mysqrt:3' y = sqrt(x);
    r8.set_size(3, r1D.size(1));
    c_loop_ub = r1D.size(1);
    for (int i8{0}; i8 < c_loop_ub; i8++) {
        double b_varargin_1;
        double c_varargin_1;
        double varargin_1;
        varargin_1 = r1D[3 * i8];
        r8[3 * i8] = std::pow(varargin_1, 2.0);
        b_varargin_1 = r1D[3 * i8 + 1];
        r8[3 * i8 + 1] = std::pow(b_varargin_1, 2.0);
        c_varargin_1 = r1D[3 * i8 + 2];
        r8[3 * i8 + 2] = std::pow(c_varargin_1, 2.0);
    }
    if (r8.size(1) == 0) {
        r1Dnorm.set_size(1, 0);
    } else {
        int i9;
        r1Dnorm.set_size(1, r8.size(1));
        i9 = r8.size(1);
        for (int c_k{0}; c_k < i9; c_k++) {
            r1Dnorm[c_k] = r8[3 * c_k];
            r1Dnorm[c_k] = r1Dnorm[c_k] + r8[3 * c_k + 1];
            r1Dnorm[c_k] = r1Dnorm[c_k] + r8[3 * c_k + 2];
        }
    }
    i10 = r1Dnorm.size(1);
    scalarLB = (r1Dnorm.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (d_k = 0; d_k <= vectorUB; d_k += 2) {
        __m128d r9;
        r9 = _mm_loadu_pd(&r1Dnorm[d_k]);
        _mm_storeu_pd(&r1Dnorm[d_k], _mm_sqrt_pd(r9));
    }
    for (d_k = scalarLB; d_k < i10; d_k++) {
        r1Dnorm[d_k] = std::sqrt(r1Dnorm[d_k]);
    }
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'SplineLengthApproxGL_tot:25' r1DnormM  = reshape(r1Dnorm, GL_N, length(Knots)-1);
    // 'SplineLengthApproxGL_tot:26' Lk        = sum(bsxfun(@times, GL_W, r1DnormM)) .* (b-a)/2;
    c.set_size(5, Curv_sp_knots.size(1) - 7);
    if (Curv_sp_knots.size(1) - 7 != 0) {
        int bcoef;
        int i11;
        bcoef = (Curv_sp_knots.size(1) - 7 != 1);
        i11 = Curv_sp_knots.size(1) - 8;
        if (0 <= Curv_sp_knots.size(1) - 8) {
            b_bcoef = (static_cast<int>(ctx_cfg_GaussLegendreN) != 1);
            ctx_cfg_GaussLegendreN_idx_0 = static_cast<int>(ctx_cfg_GaussLegendreN);
        }
        for (int f_k{0}; f_k <= i11; f_k++) {
            int varargin_3;
            varargin_3 = bcoef * f_k;
            for (int g_k{0}; g_k < 5; g_k++) {
                c[g_k + 5 * f_k] =
                    ctx_cfg_GaussLegendreW[g_k] *
                    r1Dnorm[b_bcoef * g_k + ctx_cfg_GaussLegendreN_idx_0 * varargin_3];
            }
        }
    }
    if (c.size(1) == 0) {
        y.set_size(1, 0);
    } else {
        int i12;
        y.set_size(1, c.size(1));
        i12 = c.size(1);
        for (int e_k{0}; e_k < i12; e_k++) {
            y[e_k] = c[5 * e_k];
            y[e_k] = y[e_k] + c[5 * e_k + 1];
            y[e_k] = y[e_k] + c[5 * e_k + 2];
            y[e_k] = y[e_k] + c[5 * e_k + 3];
            y[e_k] = y[e_k] + c[5 * e_k + 4];
        }
    }
    if (i2 - i1 == 1) {
        i13 = i;
    } else {
        i13 = i2 - i1;
    }
    if ((csz_idx_1_tmp == i) && (y.size(1) == i13)) {
        int b_scalarLB;
        int b_vectorUB;
        int d_loop_ub;
        int i14;
        Lk.set_size(1, y.size(1));
        d_loop_ub = y.size(1);
        b_scalarLB = (y.size(1) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (i14 = 0; i14 <= b_vectorUB; i14 += 2) {
            __m128d r10;
            r10 = _mm_loadu_pd(&y[i14]);
            _mm_storeu_pd(
                &Lk[i14],
                _mm_div_pd(
                    _mm_mul_pd(
                        r10,
                        _mm_sub_pd(_mm_loadu_pd((const double *)&Curv_sp_knots[(i1 + i14) + 4]),
                                   _mm_loadu_pd((const double *)&Curv_sp_knots[i14 + 3]))),
                    _mm_set1_pd(2.0)));
        }
        for (i14 = b_scalarLB; i14 < d_loop_ub; i14++) {
            Lk[i14] = y[i14] * (Curv_sp_knots[(i1 + i14) + 4] - Curv_sp_knots[i14 + 3]) / 2.0;
        }
    } else {
        binary_expand_op(Lk, y, Curv_sp_knots, i1 + 1, i2, i - 1);
    }
    //  Gauss Legendre integration
    // 'SplineLengthApproxGL_tot:27' L         = sum(Lk);
    vlen = Lk.size(1);
    if (Lk.size(1) == 0) {
        b_L = 0.0;
    } else {
        double b_y;
        int firstBlockLength;
        int lastBlockLength;
        int nblocks;
        if (Lk.size(1) <= 1024) {
            firstBlockLength = Lk.size(1);
            lastBlockLength = 0;
            nblocks = 1;
        } else {
            firstBlockLength = 1024;
            nblocks = Lk.size(1) / 1024;
            lastBlockLength = Lk.size(1) - (nblocks << 10);
            if (lastBlockLength > 0) {
                nblocks++;
            } else {
                lastBlockLength = 1024;
            }
        }
        b_y = Lk[0];
        for (int h_k{2}; h_k <= firstBlockLength; h_k++) {
            double c_y;
            c_y = b_y;
            if (vlen >= 2) {
                c_y = b_y + Lk[h_k - 1];
            }
            b_y = c_y;
        }
        for (int ib{2}; ib <= nblocks; ib++) {
            double bsum;
            int hi;
            int offset;
            offset = (ib - 1) << 10;
            bsum = Lk[offset];
            if (ib == nblocks) {
                hi = lastBlockLength;
            } else {
                hi = 1024;
            }
            for (int i_k{2}; i_k <= hi; i_k++) {
                double b_bsum;
                b_bsum = bsum;
                if (vlen >= 2) {
                    b_bsum = bsum + Lk[(offset + i_k) - 1];
                }
                bsum = b_bsum;
            }
            b_y += bsum;
        }
        b_L = b_y;
    }
    *L = b_L;
}

} // namespace ocn

//
// File trailer for SplineLengthApproxGL_tot.cpp
//
// [EOF]
//
