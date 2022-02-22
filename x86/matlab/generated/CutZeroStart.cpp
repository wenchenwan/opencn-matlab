//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CutZeroStart.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 08:27:14
//

// Include Files
#include "CutZeroStart.h"
#include "CutCurvStruct.h"
#include "EvalCurvStruct.h"
#include "EvalCurvStruct_data.h"
#include "EvalCurvStruct_types1.h"
#include "EvalCurvStruct_types2.h"
#include "GetCurvMaxFeedrate.h"
#include "LengthCurv.h"
#include "PrintCurvStruct.h"
#include "bsxfun.h"
#include "colon.h"
#include "find.h"
#include "queue_coder.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>
#include <stdio.h>

// Function Definitions
//
// function [CurvStruct1, CurvStruct2] = CutZeroStart(ctx, CurvStruct, k0)
//
// Arguments    : const queue_coder *ctx_q_gcode
//                const queue_coder *ctx_q_splines
//                int ctx_cfg_NHorz
//                const double ctx_cfg_amax[3]
//                const double ctx_cfg_jmax[3]
//                double ctx_cfg_dt
//                double ctx_cfg_ZeroStartAccLimit
//                double ctx_cfg_ZeroStartJerkLimit
//                double ctx_cfg_ZeroStartVelLimit
//                bool ctx_cfg_DebugCutZero
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *b_CurvStruct
//                double k0
//                CurvStruct *CurvStruct1
//                CurvStruct *CurvStruct2
// Return Type  : void
//
namespace ocn {
void CutZeroStart(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines,
                  int ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3],
                  double ctx_cfg_dt, double ctx_cfg_ZeroStartAccLimit,
                  double ctx_cfg_ZeroStartJerkLimit, double ctx_cfg_ZeroStartVelLimit,
                  bool ctx_cfg_DebugCutZero, const double ctx_cfg_GaussLegendreX[5],
                  const double ctx_cfg_GaussLegendreW[5], const CurvStruct *b_CurvStruct, double k0,
                  CurvStruct *CurvStruct1, CurvStruct *CurvStruct2)
{
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> at;
    ::coder::array<double, 2U> b_d1uk;
    ::coder::array<double, 2U> b_r1D;
    ::coder::array<double, 2U> b_uk;
    ::coder::array<double, 2U> b_x;
    ::coder::array<double, 2U> c;
    ::coder::array<double, 2U> c_x;
    ::coder::array<double, 2U> d1uk;
    ::coder::array<double, 2U> d2uk;
    ::coder::array<double, 2U> jt;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> t;
    ::coder::array<double, 2U> uk;
    ::coder::array<double, 1U> max_at;
    ::coder::array<double, 1U> max_jt;
    ::coder::array<double, 1U> norm_vt;
    ::coder::array<bool, 2U> b_max_at;
    ::coder::array<bool, 2U> b_max_jt;
    ::coder::array<bool, 2U> b_norm_vt;
    CurvStruct expl_temp;
    double a__1[3];
    double r1D[3];
    double L;
    double b_ex;
    double b_vmax;
    double ex;
    double ex_tmp;
    double jps;
    double tmax;
    double z1_idx_1;
    double z1_idx_2;
    long N;
    long k;
    long x;
    long y;
    int cut_index_vel_size[2];
    int b_loop_ub;
    int b_m;
    int b_scalarLB;
    int b_vectorUB;
    int c_ex;
    int c_loop_ub;
    int c_scalarLB;
    int c_vectorUB;
    int cut_index;
    int cut_index_acc_data;
    int cut_index_jerk_data;
    int cut_index_vel_data;
    int d_loop_ub;
    int e_loop_ub;
    int e_scalarLB;
    int e_vectorUB;
    int f_loop_ub;
    int f_scalarLB;
    int f_vectorUB;
    int g_loop_ub;
    int h_loop_ub;
    int i2;
    int i25;
    int i26;
    int i4;
    int i5;
    int i9;
    int k_k;
    int l_loop_ub;
    int m;
    int o_loop_ub;
    int p_loop_ub;
    int q_loop_ub;
    int r_loop_ub;
    int s_loop_ub;
    int scalarLB;
    int t_loop_ub;
    int u0;
    int u1;
    int u_loop_ub;
    int vectorUB;
    bool exitg1;
    // 'CutZeroStart:2' cfg=ctx.cfg;
    // 'CutZeroStart:3' [~, r1D] = EvalCurvStruct(ctx, CurvStruct, 0);
    b_EvalCurvStruct(ctx_q_splines, b_CurvStruct, a__1, r1D);
    // 'CutZeroStart:4' jps = min(cfg.jmax) / max(abs(r1D));
    z1_idx_1 = std::abs(r1D[1]);
    z1_idx_2 = std::abs(r1D[2]);
    // 'CutZeroStart:6' dt = cfg.dt;
    // 'CutZeroStart:7' tmax = ceil((6/jps)^(1/3)/dt)*dt;
    ex = ctx_cfg_jmax[0];
    ex_tmp = std::abs(r1D[0]);
    b_ex = ex_tmp;
    if (ctx_cfg_jmax[0] > ctx_cfg_jmax[1]) {
        ex = ctx_cfg_jmax[1];
    }
    if (ex_tmp < z1_idx_1) {
        b_ex = z1_idx_1;
    }
    if (ex > ctx_cfg_jmax[2]) {
        ex = ctx_cfg_jmax[2];
    }
    if (b_ex < z1_idx_2) {
        b_ex = z1_idx_2;
    }
    tmax = std::ceil(std::pow(6.0 / (ex / b_ex), 0.33333333333333331) / ctx_cfg_dt) * ctx_cfg_dt;
    // 'CutZeroStart:8' jps = 6/tmax^3;
    jps = 6.0 / std::pow(tmax, 3.0);
    // 'CutZeroStart:9' t = 0:dt:tmax;
    if ((ctx_cfg_dt == 0.0) || ((0.0 < tmax) && (ctx_cfg_dt < 0.0)) ||
        ((tmax < 0.0) && (ctx_cfg_dt > 0.0))) {
        t.set_size(1, 0);
    } else if (std::floor(ctx_cfg_dt) == ctx_cfg_dt) {
        int loop_ub;
        loop_ub = static_cast<int>(std::floor(tmax / ctx_cfg_dt));
        t.set_size(1, loop_ub + 1);
        for (int i{0}; i <= loop_ub; i++) {
            t[i] = ctx_cfg_dt * static_cast<double>(i);
        }
    } else {
        coder::eml_float_colon(ctx_cfg_dt, tmax, t);
    }
    // 'CutZeroStart:11' uk = jps*t.^3/6;
    r.set_size(1, t.size(1));
    b_loop_ub = t.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        double varargin_1;
        varargin_1 = t[i1];
        r[i1] = std::pow(varargin_1, 3.0);
    }
    uk.set_size(1, r.size(1));
    c_loop_ub = r.size(1);
    scalarLB = (r.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i2 = 0; i2 <= vectorUB; i2 += 2) {
        __m128d r1;
        r1 = _mm_loadu_pd(&r[i2]);
        _mm_storeu_pd(&uk[i2], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r1), _mm_set1_pd(6.0)));
    }
    for (i2 = scalarLB; i2 < c_loop_ub; i2++) {
        uk[i2] = jps * r[i2] / 6.0;
    }
    // 'CutZeroStart:12' d1uk = jps*t.^2/2;
    r.set_size(1, t.size(1));
    d_loop_ub = t.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        double b_varargin_1;
        b_varargin_1 = t[i3];
        r[i3] = std::pow(b_varargin_1, 2.0);
    }
    d1uk.set_size(1, r.size(1));
    e_loop_ub = r.size(1);
    b_scalarLB = (r.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (i4 = 0; i4 <= b_vectorUB; i4 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r[i4]);
        _mm_storeu_pd(&d1uk[i4], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r2), _mm_set1_pd(2.0)));
    }
    for (i4 = b_scalarLB; i4 < e_loop_ub; i4++) {
        d1uk[i4] = jps * r[i4] / 2.0;
    }
    // 'CutZeroStart:13' d2uk = jps*t;
    d2uk.set_size(1, t.size(1));
    f_loop_ub = t.size(1);
    c_scalarLB = (t.size(1) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (i5 = 0; i5 <= c_vectorUB; i5 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&t[i5]);
        _mm_storeu_pd(&d2uk[i5], _mm_mul_pd(_mm_set1_pd(jps), r3));
    }
    for (i5 = c_scalarLB; i5 < f_loop_ub; i5++) {
        d2uk[i5] = jps * t[i5];
    }
    // 'CutZeroStart:14' d3uk = jps;
    // 'CutZeroStart:16' [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, uk);
    b_uk.set_size(1, uk.size(1));
    g_loop_ub = uk.size(1) - 1;
    for (int i6{0}; i6 <= g_loop_ub; i6++) {
        b_uk[i6] = uk[i6];
    }
    b_EvalCurvStruct(ctx_q_splines, b_CurvStruct, b_uk, a__2, b_r1D, r2D, r3D);
    // 'CutZeroStart:18' r3dt = bsxfun(@times, r3D, d1uk.^3) + 3*bsxfun(@times, r2D, d1uk.*d2uk) +
    // bsxfun(@times, r1D, d3uk); 'CutZeroStart:19' r2dt = bsxfun(@times, r2D, d1uk.^2) +
    // bsxfun(@times, r1D, d2uk); 'CutZeroStart:20' r1dt = bsxfun(@times, r1D, d1uk);
    // 'CutZeroStart:22' vmax = CurvStruct.FeedRate;
    b_vmax = b_CurvStruct->FeedRate;
    // 'CutZeroStart:23' N = min(int64(k0 + ctx.cfg.NHorz - 1), int64(ctx.q_gcode.size()));
    x = static_cast<int>(std::round(k0 + static_cast<double>(ctx_cfg_NHorz))) - 1;
    y = ctx_q_gcode->size();
    if (x > y) {
        N = y;
    } else {
        N = x;
    }
    // 'CutZeroStart:25' for k = k0:N
    k = static_cast<long>(std::round(k0));
    exitg1 = false;
    while ((!exitg1) && (k <= N)) {
        double b_y;
        // 'CutZeroStart:26' TmpCurv = ctx.q_gcode.get(k);
        ctx_q_gcode->get(k, &expl_temp);
        // 'CutZeroStart:28' vmax_tmp = GetCurvMaxFeedrate(ctx, TmpCurv);
        b_y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                                 expl_temp.P0, expl_temp.P1, expl_temp.CorrectedHelixCenter,
                                 expl_temp.evec, expl_temp.theta, expl_temp.pitch,
                                 expl_temp.CoeffP5, expl_temp.sp_index, expl_temp.FeedRate,
                                 expl_temp.a_param, expl_temp.b_param);
        // 'CutZeroStart:29' vmax = min(vmax, vmax_tmp);
        b_vmax = std::fmin(b_vmax, b_y);
        // 'CutZeroStart:30' if TmpCurv.zspdmode == ZSpdMode.NZ
        if (expl_temp.zspdmode == ZSpdMode_NZ) {
            exitg1 = true;
        } else {
            k++;
        }
    }
    // 'CutZeroStart:35' jt = abs(bsxfun(@rdivide, r3dt.', cfg.jmax));
    c.set_size(3, b_r1D.size(1));
    if (b_r1D.size(1) != 0) {
        int acoef;
        int i7;
        acoef = (b_r1D.size(1) != 1);
        i7 = b_r1D.size(1) - 1;
        for (int b_k{0}; b_k <= i7; b_k++) {
            __m128d r5;
            int varargin_2;
            varargin_2 = acoef * b_k;
            r5 = _mm_loadu_pd(&b_r1D[3 * varargin_2]);
            _mm_storeu_pd(&c[3 * b_k], _mm_mul_pd(r5, _mm_set1_pd(jps)));
            c[3 * b_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
        }
    }
    r.set_size(1, d1uk.size(1));
    h_loop_ub = d1uk.size(1);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        double c_varargin_1;
        c_varargin_1 = d1uk[i8];
        r[i8] = std::pow(c_varargin_1, 3.0);
    }
    coder::bsxfun(r3D, r, r4);
    if (d1uk.size(1) == d2uk.size(1)) {
        int d_scalarLB;
        int d_vectorUB;
        int i10;
        int i_loop_ub;
        b_d1uk.set_size(1, d1uk.size(1));
        i_loop_ub = d1uk.size(1);
        d_scalarLB = (d1uk.size(1) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (i10 = 0; i10 <= d_vectorUB; i10 += 2) {
            __m128d r7;
            __m128d r8;
            r7 = _mm_loadu_pd(&d1uk[i10]);
            r8 = _mm_loadu_pd(&d2uk[i10]);
            _mm_storeu_pd(&b_d1uk[i10], _mm_mul_pd(r7, r8));
        }
        for (i10 = d_scalarLB; i10 < i_loop_ub; i10++) {
            b_d1uk[i10] = d1uk[i10] * d2uk[i10];
        }
        coder::bsxfun(r2D, b_d1uk, r6);
    } else {
        b_binary_expand_op(r6, r2D, d1uk, d2uk);
    }
    if (r4.size(1) == 1) {
        i9 = r6.size(1);
    } else {
        i9 = r4.size(1);
    }
    if ((r4.size(1) == r6.size(1)) && (i9 == c.size(1))) {
        int j_loop_ub;
        a.set_size(r4.size(1), 3);
        j_loop_ub = r4.size(1);
        for (int i11{0}; i11 < 3; i11++) {
            for (int i12{0}; i12 < j_loop_ub; i12++) {
                a[i12 + a.size(0) * i11] =
                    (r4[i11 + 3 * i12] + 3.0 * r6[i11 + 3 * i12]) + c[i11 + 3 * i12];
            }
        }
    } else {
        binary_expand_op(a, r4, r6, c);
    }
    b_x.set_size(a.size(0), 3);
    if (a.size(0) != 0) {
        int b_acoef;
        b_acoef = (a.size(0) != 1);
        for (int c_k{0}; c_k < 3; c_k++) {
            int i13;
            i13 = b_x.size(0) - 1;
            for (int d_k{0}; d_k <= i13; d_k++) {
                b_x[d_k + b_x.size(0) * c_k] =
                    a[b_acoef * d_k + a.size(0) * c_k] / ctx_cfg_jmax[c_k];
            }
        }
    }
    jt.set_size(b_x.size(0), 3);
    if (b_x.size(0) != 0) {
        int k_loop_ub;
        int m_loop_ub;
        at.set_size(b_x.size(0), 3);
        k_loop_ub = b_x.size(0);
        for (int i14{0}; i14 < 3; i14++) {
            for (int i16{0}; i16 < k_loop_ub; i16++) {
                at[i16 + at.size(0) * i14] = jt[i16 + jt.size(0) * i14];
            }
        }
        for (int e_k{0}; e_k < 3; e_k++) {
            int i17;
            i17 = at.size(0);
            for (int f_k{0}; f_k < i17; f_k++) {
                at[f_k + at.size(0) * e_k] = std::abs(b_x[f_k + b_x.size(0) * e_k]);
            }
        }
        jt.set_size(at.size(0), 3);
        m_loop_ub = at.size(0);
        for (int i18{0}; i18 < 3; i18++) {
            for (int i19{0}; i19 < m_loop_ub; i19++) {
                jt[i19 + jt.size(0) * i18] = at[i19 + at.size(0) * i18];
            }
        }
    }
    // 'CutZeroStart:36' at = abs(bsxfun(@rdivide, r2dt.', cfg.amax));
    r.set_size(1, d1uk.size(1));
    l_loop_ub = d1uk.size(1);
    for (int i15{0}; i15 < l_loop_ub; i15++) {
        double d_varargin_1;
        d_varargin_1 = d1uk[i15];
        r[i15] = std::pow(d_varargin_1, 2.0);
    }
    coder::bsxfun(r2D, r, r4);
    coder::bsxfun(b_r1D, d2uk, r6);
    if (r4.size(1) == r6.size(1)) {
        int n_loop_ub;
        a.set_size(r4.size(1), 3);
        n_loop_ub = r4.size(1);
        for (int i20{0}; i20 < 3; i20++) {
            for (int i21{0}; i21 < n_loop_ub; i21++) {
                a[i21 + a.size(0) * i20] = r4[i20 + 3 * i21] + r6[i20 + 3 * i21];
            }
        }
    } else {
        b_binary_expand_op(a, r4, r6);
    }
    b_x.set_size(a.size(0), 3);
    if (a.size(0) != 0) {
        int c_acoef;
        c_acoef = (a.size(0) != 1);
        for (int g_k{0}; g_k < 3; g_k++) {
            int i22;
            i22 = b_x.size(0) - 1;
            for (int i_k{0}; i_k <= i22; i_k++) {
                b_x[i_k + b_x.size(0) * g_k] =
                    a[c_acoef * i_k + a.size(0) * g_k] / ctx_cfg_amax[g_k];
            }
        }
    }
    at.set_size(b_x.size(0), 3);
    if (b_x.size(0) != 0) {
        for (int h_k{0}; h_k < 3; h_k++) {
            int i23;
            i23 = at.size(0);
            for (int j_k{0}; j_k < i23; j_k++) {
                at[j_k + at.size(0) * h_k] = std::abs(b_x[j_k + b_x.size(0) * h_k]);
            }
        }
    }
    // 'CutZeroStart:37' norm_vt = mysqrt(sum(r1dt.^2, 1))/vmax;
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'CutZeroStart:38' norm_vt = norm_vt.';
    coder::bsxfun(b_r1D, d1uk, r4);
    r4.set_size(3, r4.size(1));
    o_loop_ub = r4.size(1);
    for (int i24{0}; i24 < o_loop_ub; i24++) {
        double e_varargin_1;
        double f_varargin_1;
        double g_varargin_1;
        e_varargin_1 = r4[3 * i24];
        r4[3 * i24] = std::pow(e_varargin_1, 2.0);
        f_varargin_1 = r4[3 * i24 + 1];
        r4[3 * i24 + 1] = std::pow(f_varargin_1, 2.0);
        g_varargin_1 = r4[3 * i24 + 2];
        r4[3 * i24 + 2] = std::pow(g_varargin_1, 2.0);
    }
    coder::sum(r4, c_x);
    i25 = c_x.size(1);
    e_scalarLB = (c_x.size(1) / 2) << 1;
    e_vectorUB = e_scalarLB - 2;
    for (k_k = 0; k_k <= e_vectorUB; k_k += 2) {
        __m128d r9;
        r9 = _mm_loadu_pd(&c_x[k_k]);
        _mm_storeu_pd(&c_x[k_k], _mm_sqrt_pd(r9));
    }
    for (k_k = e_scalarLB; k_k < i25; k_k++) {
        c_x[k_k] = std::sqrt(c_x[k_k]);
    }
    norm_vt.set_size(c_x.size(1));
    p_loop_ub = c_x.size(1);
    f_scalarLB = (c_x.size(1) / 2) << 1;
    f_vectorUB = f_scalarLB - 2;
    for (i26 = 0; i26 <= f_vectorUB; i26 += 2) {
        __m128d r10;
        r10 = _mm_loadu_pd(&c_x[i26]);
        _mm_storeu_pd(&norm_vt[i26], _mm_div_pd(r10, _mm_set1_pd(b_vmax)));
    }
    for (i26 = f_scalarLB; i26 < p_loop_ub; i26++) {
        norm_vt[i26] = c_x[i26] / b_vmax;
    }
    // 'CutZeroStart:40' max_jt = max(jt, [], 2);
    m = jt.size(0) - 1;
    max_jt.set_size(jt.size(0));
    if (jt.size(0) >= 1) {
        for (int b_i{0}; b_i <= m; b_i++) {
            max_jt[b_i] = jt[b_i];
        }
        for (int j{0}; j < 2; j++) {
            for (int c_i{0}; c_i <= m; c_i++) {
                double d;
                d = jt[c_i + jt.size(0) * (j + 1)];
                if (max_jt[c_i] < d) {
                    max_jt[c_i] = d;
                }
            }
        }
    }
    // 'CutZeroStart:41' max_at = max(at, [], 2);
    b_m = at.size(0) - 1;
    max_at.set_size(at.size(0));
    if (at.size(0) >= 1) {
        for (int d_i{0}; d_i <= b_m; d_i++) {
            max_at[d_i] = at[d_i];
        }
        for (int b_j{0}; b_j < 2; b_j++) {
            for (int e_i{0}; e_i <= b_m; e_i++) {
                double d1;
                d1 = at[e_i + at.size(0) * (b_j + 1)];
                if (max_at[e_i] < d1) {
                    max_at[e_i] = d1;
                }
            }
        }
    }
    // 'CutZeroStart:43' N = length(max_jt);
    // 'CutZeroStart:45' cut_index_jerk = orelse(find(max_jt.' > cfg.ZeroStartJerkLimit, 1), N);
    b_max_jt.set_size(1, max_jt.size(0));
    q_loop_ub = max_jt.size(0);
    for (int i27{0}; i27 < q_loop_ub; i27++) {
        b_max_jt[i27] = (max_jt[i27] > ctx_cfg_ZeroStartJerkLimit);
    }
    coder::b_eml_find(b_max_jt, (int *)&cut_index_vel_data, cut_index_vel_size);
    r_loop_ub = cut_index_vel_size[1];
    for (int i28{0}; i28 < r_loop_ub; i28++) {
        cut_index_jerk_data = cut_index_vel_data;
    }
    // 'orelse:2' if isempty(value)
    if (cut_index_vel_size[1] == 0) {
        // 'orelse:3' v = elsevalue;
        cut_index_jerk_data = max_jt.size(0);
    } else {
        // 'orelse:4' else
        // 'orelse:5' v = value;
    }
    // 'CutZeroStart:46' cut_index_acc = orelse(find(max_at.' > cfg.ZeroStartAccLimit, 1), N);
    b_max_at.set_size(1, max_at.size(0));
    s_loop_ub = max_at.size(0);
    for (int i29{0}; i29 < s_loop_ub; i29++) {
        b_max_at[i29] = (max_at[i29] > ctx_cfg_ZeroStartAccLimit);
    }
    coder::b_eml_find(b_max_at, (int *)&cut_index_vel_data, cut_index_vel_size);
    t_loop_ub = cut_index_vel_size[1];
    for (int i30{0}; i30 < t_loop_ub; i30++) {
        cut_index_acc_data = cut_index_vel_data;
    }
    // 'orelse:2' if isempty(value)
    if (cut_index_vel_size[1] == 0) {
        // 'orelse:3' v = elsevalue;
        cut_index_acc_data = max_jt.size(0);
    } else {
        // 'orelse:4' else
        // 'orelse:5' v = value;
    }
    // 'CutZeroStart:47' cut_index_vel = orelse(find(norm_vt.' > cfg.ZeroStartVelLimit, 1), N);
    b_norm_vt.set_size(1, norm_vt.size(0));
    u_loop_ub = norm_vt.size(0);
    for (int i31{0}; i31 < u_loop_ub; i31++) {
        b_norm_vt[i31] = (norm_vt[i31] > ctx_cfg_ZeroStartVelLimit);
    }
    coder::b_eml_find(b_norm_vt, (int *)&cut_index_vel_data, cut_index_vel_size);
    // 'orelse:2' if isempty(value)
    if (cut_index_vel_size[1] == 0) {
        // 'orelse:3' v = elsevalue;
        cut_index_vel_data = max_jt.size(0);
    } else {
        // 'orelse:4' else
        // 'orelse:5' v = value;
    }
    // 'CutZeroStart:49' cut_index = min([cut_index_acc, cut_index_jerk, cut_index_vel]);
    // 'CutZeroStart:50' cut_index = max(2, int32(cut_index) - 1);
    c_ex = cut_index_acc_data;
    if (cut_index_acc_data > cut_index_jerk_data) {
        c_ex = cut_index_jerk_data;
    }
    if (c_ex > cut_index_vel_data) {
        c_ex = cut_index_vel_data;
    }
    // 'CutZeroStart:51' cut_index = min(int32(N/2), cut_index);
    u0 = static_cast<int>(std::round(static_cast<double>(max_jt.size(0)) / 2.0));
    if (2 < c_ex - 1) {
        u1 = c_ex - 1;
    } else {
        u1 = 2;
    }
    if (u0 <= u1) {
        cut_index = u0;
    } else {
        cut_index = u1;
    }
    // 'CutZeroStart:52' u_cut = uk(cut_index);
    // 'CutZeroStart:53' t_cut = t(cut_index);
    // 'CutZeroStart:54' L = LengthCurv(ctx, CurvStruct, 0, 1);
    L = LengthCurv(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, b_CurvStruct);
    // 'CutZeroStart:56' actual_jps = 6/t_cut.^3;
    // 'CutZeroStart:58' CurvStruct1 = CutCurvStruct(ctx, CurvStruct, 0, L - u_cut*L);
    *CurvStruct1 = *b_CurvStruct;
    CutCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1,
                  L - uk[cut_index - 1] * L);
    // 'CutZeroStart:59' CurvStruct1.UseConstJerk = true;
    CurvStruct1->UseConstJerk = true;
    // 'CutZeroStart:60' CurvStruct1.ConstJerk = actual_jps;
    CurvStruct1->ConstJerk = 6.0 / std::pow(t[cut_index - 1], 3.0);
    // 'CutZeroStart:61' CurvStruct1.ConstJerkMaxIterations = int32(cut_index);
    CurvStruct1->ConstJerkMaxIterations = cut_index;
    // 'CutZeroStart:62' CurvStruct2 = CutCurvStruct(ctx, CurvStruct, u_cut*L, 0);
    *CurvStruct2 = *b_CurvStruct;
    b_CutCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct2,
                    uk[cut_index - 1] * L);
    // 'CutZeroStart:64' norm_vt_at_index = norm_vt(cut_index);
    // 'CutZeroStart:66' CurvStruct1.zspdmode = ZSpdMode.ZN;
    CurvStruct1->zspdmode = ZSpdMode_ZN;
    // 'CutZeroStart:67' CurvStruct2.zspdmode = ZSpdMode.NN;
    CurvStruct2->zspdmode = ZSpdMode_NN;
    // 'CutZeroStart:69' CurvStruct1.gcode_source_line = CurvStruct.gcode_source_line;
    CurvStruct1->gcode_source_line = b_CurvStruct->gcode_source_line;
    // 'CutZeroStart:70' CurvStruct2.gcode_source_line = CurvStruct.gcode_source_line;
    CurvStruct2->gcode_source_line = b_CurvStruct->gcode_source_line;
    // 'CutZeroStart:72' if ctx.cfg.DebugCutZero
    if (ctx_cfg_DebugCutZero) {
        // 'CutZeroStart:73' fprintf('======== CUT ZERO START =========\n');
        printf("======== CUT ZERO START =========\n");
        fflush(stdout);
        // 'CutZeroStart:74' fprintf('Initial: \n');
        printf("Initial: \n");
        fflush(stdout);
        // 'CutZeroStart:75' PrintCurvStruct(ctx, CurvStruct);
        PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                        b_CurvStruct);
        // 'CutZeroStart:77' fprintf('\nCut:\n');
        printf("\nCut:\n");
        fflush(stdout);
        // 'CutZeroStart:78' fprintf('Index = %d, t_cut = %e, vmax = %.1f\n', cut_index, t_cut,
        // vmax);
        printf("Index = %d, t_cut = %e, vmax = %.1f\n", cut_index, t[cut_index - 1], b_vmax);
        fflush(stdout);
        // 'CutZeroStart:79' fprintf('jps = %e, norm_vt(%d) = %f\n', jps, cut_index,
        // norm_vt_at_index);
        printf("jps = %e, norm_vt(%d) = %f\n", jps, cut_index, norm_vt[cut_index - 1]);
        fflush(stdout);
        // 'CutZeroStart:81' PrintCurvStruct(ctx, CurvStruct1);
        PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1);
        // 'CutZeroStart:82' PrintCurvStruct(ctx, CurvStruct2);
        PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct2);
    }
}

//
// function [CurvStruct1, CurvStruct2] = CutZeroStart(ctx, CurvStruct, k0)
//
// Arguments    : const queue_coder *ctx_q_gcode
//                const queue_coder *ctx_q_splines
//                int ctx_cfg_NHorz
//                const double ctx_cfg_amax[3]
//                const double ctx_cfg_jmax[3]
//                double ctx_cfg_dt
//                double ctx_cfg_ZeroStartAccLimit
//                double ctx_cfg_ZeroStartJerkLimit
//                double ctx_cfg_ZeroStartVelLimit
//                bool ctx_cfg_DebugCutZero
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *b_CurvStruct
//                CurvStruct *CurvStruct1
//                CurvStruct *CurvStruct2
// Return Type  : void
//
void b_CutZeroStart(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines,
                    int ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3],
                    double ctx_cfg_dt, double ctx_cfg_ZeroStartAccLimit,
                    double ctx_cfg_ZeroStartJerkLimit, double ctx_cfg_ZeroStartVelLimit,
                    bool ctx_cfg_DebugCutZero, const double ctx_cfg_GaussLegendreX[5],
                    const double ctx_cfg_GaussLegendreW[5], const CurvStruct *b_CurvStruct,
                    CurvStruct *CurvStruct1, CurvStruct *CurvStruct2)
{
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> at;
    ::coder::array<double, 2U> b_d1uk;
    ::coder::array<double, 2U> b_r1D;
    ::coder::array<double, 2U> b_uk;
    ::coder::array<double, 2U> b_x;
    ::coder::array<double, 2U> c;
    ::coder::array<double, 2U> d1uk;
    ::coder::array<double, 2U> d2uk;
    ::coder::array<double, 2U> jt;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> t;
    ::coder::array<double, 2U> uk;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 1U> max_at;
    ::coder::array<double, 1U> max_jt;
    ::coder::array<double, 1U> norm_vt;
    ::coder::array<bool, 2U> b_max_at;
    ::coder::array<bool, 2U> b_max_jt;
    ::coder::array<bool, 2U> b_norm_vt;
    CurvStruct expl_temp;
    double a__1[3];
    double r1D[3];
    double L;
    double b_ex;
    double b_vmax;
    double ex;
    double ex_tmp;
    double jps;
    double tmax;
    double z1_idx_1;
    double z1_idx_2;
    long N;
    long k;
    long y;
    int cut_index_vel_size[2];
    int b_loop_ub;
    int b_m;
    int b_scalarLB;
    int b_vectorUB;
    int c_ex;
    int c_loop_ub;
    int c_scalarLB;
    int c_vectorUB;
    int cut_index;
    int cut_index_acc_data;
    int cut_index_jerk_data;
    int cut_index_vel_data;
    int d_loop_ub;
    int e_loop_ub;
    int e_scalarLB;
    int e_vectorUB;
    int f_loop_ub;
    int f_scalarLB;
    int f_vectorUB;
    int g_loop_ub;
    int h_loop_ub;
    int i2;
    int i25;
    int i26;
    int i4;
    int i5;
    int i9;
    int k_k;
    int l_loop_ub;
    int m;
    int o_loop_ub;
    int p_loop_ub;
    int q_loop_ub;
    int r_loop_ub;
    int s_loop_ub;
    int scalarLB;
    int t_loop_ub;
    int u0;
    int u1;
    int u_loop_ub;
    int vectorUB;
    bool exitg1;
    // 'CutZeroStart:2' cfg=ctx.cfg;
    // 'CutZeroStart:3' [~, r1D] = EvalCurvStruct(ctx, CurvStruct, 0);
    b_EvalCurvStruct(ctx_q_splines, b_CurvStruct, a__1, r1D);
    // 'CutZeroStart:4' jps = min(cfg.jmax) / max(abs(r1D));
    z1_idx_1 = std::abs(r1D[1]);
    z1_idx_2 = std::abs(r1D[2]);
    // 'CutZeroStart:6' dt = cfg.dt;
    // 'CutZeroStart:7' tmax = ceil((6/jps)^(1/3)/dt)*dt;
    ex = ctx_cfg_jmax[0];
    ex_tmp = std::abs(r1D[0]);
    b_ex = ex_tmp;
    if (ctx_cfg_jmax[0] > ctx_cfg_jmax[1]) {
        ex = ctx_cfg_jmax[1];
    }
    if (ex_tmp < z1_idx_1) {
        b_ex = z1_idx_1;
    }
    if (ex > ctx_cfg_jmax[2]) {
        ex = ctx_cfg_jmax[2];
    }
    if (b_ex < z1_idx_2) {
        b_ex = z1_idx_2;
    }
    tmax = std::ceil(std::pow(6.0 / (ex / b_ex), 0.33333333333333331) / ctx_cfg_dt) * ctx_cfg_dt;
    // 'CutZeroStart:8' jps = 6/tmax^3;
    jps = 6.0 / std::pow(tmax, 3.0);
    // 'CutZeroStart:9' t = 0:dt:tmax;
    if ((ctx_cfg_dt == 0.0) || ((0.0 < tmax) && (ctx_cfg_dt < 0.0)) ||
        ((tmax < 0.0) && (ctx_cfg_dt > 0.0))) {
        t.set_size(1, 0);
    } else if (std::floor(ctx_cfg_dt) == ctx_cfg_dt) {
        int loop_ub;
        loop_ub = static_cast<int>(std::floor(tmax / ctx_cfg_dt));
        t.set_size(1, loop_ub + 1);
        for (int i{0}; i <= loop_ub; i++) {
            t[i] = ctx_cfg_dt * static_cast<double>(i);
        }
    } else {
        coder::eml_float_colon(ctx_cfg_dt, tmax, t);
    }
    // 'CutZeroStart:11' uk = jps*t.^3/6;
    r.set_size(1, t.size(1));
    b_loop_ub = t.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        double varargin_1;
        varargin_1 = t[i1];
        r[i1] = std::pow(varargin_1, 3.0);
    }
    uk.set_size(1, r.size(1));
    c_loop_ub = r.size(1);
    scalarLB = (r.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i2 = 0; i2 <= vectorUB; i2 += 2) {
        __m128d r1;
        r1 = _mm_loadu_pd(&r[i2]);
        _mm_storeu_pd(&uk[i2], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r1), _mm_set1_pd(6.0)));
    }
    for (i2 = scalarLB; i2 < c_loop_ub; i2++) {
        uk[i2] = jps * r[i2] / 6.0;
    }
    // 'CutZeroStart:12' d1uk = jps*t.^2/2;
    r.set_size(1, t.size(1));
    d_loop_ub = t.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        double b_varargin_1;
        b_varargin_1 = t[i3];
        r[i3] = std::pow(b_varargin_1, 2.0);
    }
    d1uk.set_size(1, r.size(1));
    e_loop_ub = r.size(1);
    b_scalarLB = (r.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (i4 = 0; i4 <= b_vectorUB; i4 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r[i4]);
        _mm_storeu_pd(&d1uk[i4], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r2), _mm_set1_pd(2.0)));
    }
    for (i4 = b_scalarLB; i4 < e_loop_ub; i4++) {
        d1uk[i4] = jps * r[i4] / 2.0;
    }
    // 'CutZeroStart:13' d2uk = jps*t;
    d2uk.set_size(1, t.size(1));
    f_loop_ub = t.size(1);
    c_scalarLB = (t.size(1) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (i5 = 0; i5 <= c_vectorUB; i5 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&t[i5]);
        _mm_storeu_pd(&d2uk[i5], _mm_mul_pd(_mm_set1_pd(jps), r3));
    }
    for (i5 = c_scalarLB; i5 < f_loop_ub; i5++) {
        d2uk[i5] = jps * t[i5];
    }
    // 'CutZeroStart:14' d3uk = jps;
    // 'CutZeroStart:16' [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, uk);
    b_uk.set_size(1, uk.size(1));
    g_loop_ub = uk.size(1) - 1;
    for (int i6{0}; i6 <= g_loop_ub; i6++) {
        b_uk[i6] = uk[i6];
    }
    b_EvalCurvStruct(ctx_q_splines, b_CurvStruct, b_uk, a__2, b_r1D, r2D, r3D);
    // 'CutZeroStart:18' r3dt = bsxfun(@times, r3D, d1uk.^3) + 3*bsxfun(@times, r2D, d1uk.*d2uk) +
    // bsxfun(@times, r1D, d3uk); 'CutZeroStart:19' r2dt = bsxfun(@times, r2D, d1uk.^2) +
    // bsxfun(@times, r1D, d2uk); 'CutZeroStart:20' r1dt = bsxfun(@times, r1D, d1uk);
    // 'CutZeroStart:22' vmax = CurvStruct.FeedRate;
    b_vmax = b_CurvStruct->FeedRate;
    // 'CutZeroStart:23' N = min(int64(k0 + ctx.cfg.NHorz - 1), int64(ctx.q_gcode.size()));
    y = ctx_q_gcode->size();
    if (ctx_cfg_NHorz > y) {
        N = y;
    } else {
        N = ctx_cfg_NHorz;
    }
    // 'CutZeroStart:25' for k = k0:N
    k = 1L;
    exitg1 = false;
    while ((!exitg1) && (k <= N)) {
        double b_y;
        // 'CutZeroStart:26' TmpCurv = ctx.q_gcode.get(k);
        ctx_q_gcode->get(k, &expl_temp);
        // 'CutZeroStart:28' vmax_tmp = GetCurvMaxFeedrate(ctx, TmpCurv);
        b_y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                                 expl_temp.P0, expl_temp.P1, expl_temp.CorrectedHelixCenter,
                                 expl_temp.evec, expl_temp.theta, expl_temp.pitch,
                                 expl_temp.CoeffP5, expl_temp.sp_index, expl_temp.FeedRate,
                                 expl_temp.a_param, expl_temp.b_param);
        // 'CutZeroStart:29' vmax = min(vmax, vmax_tmp);
        b_vmax = std::fmin(b_vmax, b_y);
        // 'CutZeroStart:30' if TmpCurv.zspdmode == ZSpdMode.NZ
        if (expl_temp.zspdmode == ZSpdMode_NZ) {
            exitg1 = true;
        } else {
            k++;
        }
    }
    // 'CutZeroStart:35' jt = abs(bsxfun(@rdivide, r3dt.', cfg.jmax));
    c.set_size(3, b_r1D.size(1));
    if (b_r1D.size(1) != 0) {
        int acoef;
        int i7;
        acoef = (b_r1D.size(1) != 1);
        i7 = b_r1D.size(1) - 1;
        for (int b_k{0}; b_k <= i7; b_k++) {
            __m128d r5;
            int varargin_2;
            varargin_2 = acoef * b_k;
            r5 = _mm_loadu_pd(&b_r1D[3 * varargin_2]);
            _mm_storeu_pd(&c[3 * b_k], _mm_mul_pd(r5, _mm_set1_pd(jps)));
            c[3 * b_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
        }
    }
    r.set_size(1, d1uk.size(1));
    h_loop_ub = d1uk.size(1);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        double c_varargin_1;
        c_varargin_1 = d1uk[i8];
        r[i8] = std::pow(c_varargin_1, 3.0);
    }
    coder::bsxfun(r3D, r, r4);
    if (d1uk.size(1) == d2uk.size(1)) {
        int d_scalarLB;
        int d_vectorUB;
        int i10;
        int i_loop_ub;
        b_d1uk.set_size(1, d1uk.size(1));
        i_loop_ub = d1uk.size(1);
        d_scalarLB = (d1uk.size(1) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (i10 = 0; i10 <= d_vectorUB; i10 += 2) {
            __m128d r7;
            __m128d r8;
            r7 = _mm_loadu_pd(&d1uk[i10]);
            r8 = _mm_loadu_pd(&d2uk[i10]);
            _mm_storeu_pd(&b_d1uk[i10], _mm_mul_pd(r7, r8));
        }
        for (i10 = d_scalarLB; i10 < i_loop_ub; i10++) {
            b_d1uk[i10] = d1uk[i10] * d2uk[i10];
        }
        coder::bsxfun(r2D, b_d1uk, r6);
    } else {
        b_binary_expand_op(r6, r2D, d1uk, d2uk);
    }
    if (r4.size(1) == 1) {
        i9 = r6.size(1);
    } else {
        i9 = r4.size(1);
    }
    if ((r4.size(1) == r6.size(1)) && (i9 == c.size(1))) {
        int j_loop_ub;
        a.set_size(r4.size(1), 3);
        j_loop_ub = r4.size(1);
        for (int i11{0}; i11 < 3; i11++) {
            for (int i12{0}; i12 < j_loop_ub; i12++) {
                a[i12 + a.size(0) * i11] =
                    (r4[i11 + 3 * i12] + 3.0 * r6[i11 + 3 * i12]) + c[i11 + 3 * i12];
            }
        }
    } else {
        binary_expand_op(a, r4, r6, c);
    }
    x.set_size(a.size(0), 3);
    if (a.size(0) != 0) {
        int b_acoef;
        b_acoef = (a.size(0) != 1);
        for (int c_k{0}; c_k < 3; c_k++) {
            int i13;
            i13 = x.size(0) - 1;
            for (int d_k{0}; d_k <= i13; d_k++) {
                x[d_k + x.size(0) * c_k] = a[b_acoef * d_k + a.size(0) * c_k] / ctx_cfg_jmax[c_k];
            }
        }
    }
    jt.set_size(x.size(0), 3);
    if (x.size(0) != 0) {
        int k_loop_ub;
        int m_loop_ub;
        at.set_size(x.size(0), 3);
        k_loop_ub = x.size(0);
        for (int i14{0}; i14 < 3; i14++) {
            for (int i16{0}; i16 < k_loop_ub; i16++) {
                at[i16 + at.size(0) * i14] = jt[i16 + jt.size(0) * i14];
            }
        }
        for (int e_k{0}; e_k < 3; e_k++) {
            int i17;
            i17 = at.size(0);
            for (int f_k{0}; f_k < i17; f_k++) {
                at[f_k + at.size(0) * e_k] = std::abs(x[f_k + x.size(0) * e_k]);
            }
        }
        jt.set_size(at.size(0), 3);
        m_loop_ub = at.size(0);
        for (int i18{0}; i18 < 3; i18++) {
            for (int i19{0}; i19 < m_loop_ub; i19++) {
                jt[i19 + jt.size(0) * i18] = at[i19 + at.size(0) * i18];
            }
        }
    }
    // 'CutZeroStart:36' at = abs(bsxfun(@rdivide, r2dt.', cfg.amax));
    r.set_size(1, d1uk.size(1));
    l_loop_ub = d1uk.size(1);
    for (int i15{0}; i15 < l_loop_ub; i15++) {
        double d_varargin_1;
        d_varargin_1 = d1uk[i15];
        r[i15] = std::pow(d_varargin_1, 2.0);
    }
    coder::bsxfun(r2D, r, r4);
    coder::bsxfun(b_r1D, d2uk, r6);
    if (r4.size(1) == r6.size(1)) {
        int n_loop_ub;
        a.set_size(r4.size(1), 3);
        n_loop_ub = r4.size(1);
        for (int i20{0}; i20 < 3; i20++) {
            for (int i21{0}; i21 < n_loop_ub; i21++) {
                a[i21 + a.size(0) * i20] = r4[i20 + 3 * i21] + r6[i20 + 3 * i21];
            }
        }
    } else {
        b_binary_expand_op(a, r4, r6);
    }
    x.set_size(a.size(0), 3);
    if (a.size(0) != 0) {
        int c_acoef;
        c_acoef = (a.size(0) != 1);
        for (int g_k{0}; g_k < 3; g_k++) {
            int i22;
            i22 = x.size(0) - 1;
            for (int i_k{0}; i_k <= i22; i_k++) {
                x[i_k + x.size(0) * g_k] = a[c_acoef * i_k + a.size(0) * g_k] / ctx_cfg_amax[g_k];
            }
        }
    }
    at.set_size(x.size(0), 3);
    if (x.size(0) != 0) {
        for (int h_k{0}; h_k < 3; h_k++) {
            int i23;
            i23 = at.size(0);
            for (int j_k{0}; j_k < i23; j_k++) {
                at[j_k + at.size(0) * h_k] = std::abs(x[j_k + x.size(0) * h_k]);
            }
        }
    }
    // 'CutZeroStart:37' norm_vt = mysqrt(sum(r1dt.^2, 1))/vmax;
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'CutZeroStart:38' norm_vt = norm_vt.';
    coder::bsxfun(b_r1D, d1uk, r4);
    r4.set_size(3, r4.size(1));
    o_loop_ub = r4.size(1);
    for (int i24{0}; i24 < o_loop_ub; i24++) {
        double e_varargin_1;
        double f_varargin_1;
        double g_varargin_1;
        e_varargin_1 = r4[3 * i24];
        r4[3 * i24] = std::pow(e_varargin_1, 2.0);
        f_varargin_1 = r4[3 * i24 + 1];
        r4[3 * i24 + 1] = std::pow(f_varargin_1, 2.0);
        g_varargin_1 = r4[3 * i24 + 2];
        r4[3 * i24 + 2] = std::pow(g_varargin_1, 2.0);
    }
    coder::sum(r4, b_x);
    i25 = b_x.size(1);
    e_scalarLB = (b_x.size(1) / 2) << 1;
    e_vectorUB = e_scalarLB - 2;
    for (k_k = 0; k_k <= e_vectorUB; k_k += 2) {
        __m128d r9;
        r9 = _mm_loadu_pd(&b_x[k_k]);
        _mm_storeu_pd(&b_x[k_k], _mm_sqrt_pd(r9));
    }
    for (k_k = e_scalarLB; k_k < i25; k_k++) {
        b_x[k_k] = std::sqrt(b_x[k_k]);
    }
    norm_vt.set_size(b_x.size(1));
    p_loop_ub = b_x.size(1);
    f_scalarLB = (b_x.size(1) / 2) << 1;
    f_vectorUB = f_scalarLB - 2;
    for (i26 = 0; i26 <= f_vectorUB; i26 += 2) {
        __m128d r10;
        r10 = _mm_loadu_pd(&b_x[i26]);
        _mm_storeu_pd(&norm_vt[i26], _mm_div_pd(r10, _mm_set1_pd(b_vmax)));
    }
    for (i26 = f_scalarLB; i26 < p_loop_ub; i26++) {
        norm_vt[i26] = b_x[i26] / b_vmax;
    }
    // 'CutZeroStart:40' max_jt = max(jt, [], 2);
    m = jt.size(0) - 1;
    max_jt.set_size(jt.size(0));
    if (jt.size(0) >= 1) {
        for (int b_i{0}; b_i <= m; b_i++) {
            max_jt[b_i] = jt[b_i];
        }
        for (int j{0}; j < 2; j++) {
            for (int c_i{0}; c_i <= m; c_i++) {
                double d;
                d = jt[c_i + jt.size(0) * (j + 1)];
                if (max_jt[c_i] < d) {
                    max_jt[c_i] = d;
                }
            }
        }
    }
    // 'CutZeroStart:41' max_at = max(at, [], 2);
    b_m = at.size(0) - 1;
    max_at.set_size(at.size(0));
    if (at.size(0) >= 1) {
        for (int d_i{0}; d_i <= b_m; d_i++) {
            max_at[d_i] = at[d_i];
        }
        for (int b_j{0}; b_j < 2; b_j++) {
            for (int e_i{0}; e_i <= b_m; e_i++) {
                double d1;
                d1 = at[e_i + at.size(0) * (b_j + 1)];
                if (max_at[e_i] < d1) {
                    max_at[e_i] = d1;
                }
            }
        }
    }
    // 'CutZeroStart:43' N = length(max_jt);
    // 'CutZeroStart:45' cut_index_jerk = orelse(find(max_jt.' > cfg.ZeroStartJerkLimit, 1), N);
    b_max_jt.set_size(1, max_jt.size(0));
    q_loop_ub = max_jt.size(0);
    for (int i27{0}; i27 < q_loop_ub; i27++) {
        b_max_jt[i27] = (max_jt[i27] > ctx_cfg_ZeroStartJerkLimit);
    }
    coder::b_eml_find(b_max_jt, (int *)&cut_index_vel_data, cut_index_vel_size);
    r_loop_ub = cut_index_vel_size[1];
    for (int i28{0}; i28 < r_loop_ub; i28++) {
        cut_index_jerk_data = cut_index_vel_data;
    }
    // 'orelse:2' if isempty(value)
    if (cut_index_vel_size[1] == 0) {
        // 'orelse:3' v = elsevalue;
        cut_index_jerk_data = max_jt.size(0);
    } else {
        // 'orelse:4' else
        // 'orelse:5' v = value;
    }
    // 'CutZeroStart:46' cut_index_acc = orelse(find(max_at.' > cfg.ZeroStartAccLimit, 1), N);
    b_max_at.set_size(1, max_at.size(0));
    s_loop_ub = max_at.size(0);
    for (int i29{0}; i29 < s_loop_ub; i29++) {
        b_max_at[i29] = (max_at[i29] > ctx_cfg_ZeroStartAccLimit);
    }
    coder::b_eml_find(b_max_at, (int *)&cut_index_vel_data, cut_index_vel_size);
    t_loop_ub = cut_index_vel_size[1];
    for (int i30{0}; i30 < t_loop_ub; i30++) {
        cut_index_acc_data = cut_index_vel_data;
    }
    // 'orelse:2' if isempty(value)
    if (cut_index_vel_size[1] == 0) {
        // 'orelse:3' v = elsevalue;
        cut_index_acc_data = max_jt.size(0);
    } else {
        // 'orelse:4' else
        // 'orelse:5' v = value;
    }
    // 'CutZeroStart:47' cut_index_vel = orelse(find(norm_vt.' > cfg.ZeroStartVelLimit, 1), N);
    b_norm_vt.set_size(1, norm_vt.size(0));
    u_loop_ub = norm_vt.size(0);
    for (int i31{0}; i31 < u_loop_ub; i31++) {
        b_norm_vt[i31] = (norm_vt[i31] > ctx_cfg_ZeroStartVelLimit);
    }
    coder::b_eml_find(b_norm_vt, (int *)&cut_index_vel_data, cut_index_vel_size);
    // 'orelse:2' if isempty(value)
    if (cut_index_vel_size[1] == 0) {
        // 'orelse:3' v = elsevalue;
        cut_index_vel_data = max_jt.size(0);
    } else {
        // 'orelse:4' else
        // 'orelse:5' v = value;
    }
    // 'CutZeroStart:49' cut_index = min([cut_index_acc, cut_index_jerk, cut_index_vel]);
    // 'CutZeroStart:50' cut_index = max(2, int32(cut_index) - 1);
    c_ex = cut_index_acc_data;
    if (cut_index_acc_data > cut_index_jerk_data) {
        c_ex = cut_index_jerk_data;
    }
    if (c_ex > cut_index_vel_data) {
        c_ex = cut_index_vel_data;
    }
    // 'CutZeroStart:51' cut_index = min(int32(N/2), cut_index);
    u0 = static_cast<int>(std::round(static_cast<double>(max_jt.size(0)) / 2.0));
    if (2 < c_ex - 1) {
        u1 = c_ex - 1;
    } else {
        u1 = 2;
    }
    if (u0 <= u1) {
        cut_index = u0;
    } else {
        cut_index = u1;
    }
    // 'CutZeroStart:52' u_cut = uk(cut_index);
    // 'CutZeroStart:53' t_cut = t(cut_index);
    // 'CutZeroStart:54' L = LengthCurv(ctx, CurvStruct, 0, 1);
    L = LengthCurv(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, b_CurvStruct);
    // 'CutZeroStart:56' actual_jps = 6/t_cut.^3;
    // 'CutZeroStart:58' CurvStruct1 = CutCurvStruct(ctx, CurvStruct, 0, L - u_cut*L);
    *CurvStruct1 = *b_CurvStruct;
    CutCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1,
                  L - uk[cut_index - 1] * L);
    // 'CutZeroStart:59' CurvStruct1.UseConstJerk = true;
    CurvStruct1->UseConstJerk = true;
    // 'CutZeroStart:60' CurvStruct1.ConstJerk = actual_jps;
    CurvStruct1->ConstJerk = 6.0 / std::pow(t[cut_index - 1], 3.0);
    // 'CutZeroStart:61' CurvStruct1.ConstJerkMaxIterations = int32(cut_index);
    CurvStruct1->ConstJerkMaxIterations = cut_index;
    // 'CutZeroStart:62' CurvStruct2 = CutCurvStruct(ctx, CurvStruct, u_cut*L, 0);
    *CurvStruct2 = *b_CurvStruct;
    b_CutCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct2,
                    uk[cut_index - 1] * L);
    // 'CutZeroStart:64' norm_vt_at_index = norm_vt(cut_index);
    // 'CutZeroStart:66' CurvStruct1.zspdmode = ZSpdMode.ZN;
    CurvStruct1->zspdmode = ZSpdMode_ZN;
    // 'CutZeroStart:67' CurvStruct2.zspdmode = ZSpdMode.NN;
    CurvStruct2->zspdmode = ZSpdMode_NN;
    // 'CutZeroStart:69' CurvStruct1.gcode_source_line = CurvStruct.gcode_source_line;
    CurvStruct1->gcode_source_line = b_CurvStruct->gcode_source_line;
    // 'CutZeroStart:70' CurvStruct2.gcode_source_line = CurvStruct.gcode_source_line;
    CurvStruct2->gcode_source_line = b_CurvStruct->gcode_source_line;
    // 'CutZeroStart:72' if ctx.cfg.DebugCutZero
    if (ctx_cfg_DebugCutZero) {
        // 'CutZeroStart:73' fprintf('======== CUT ZERO START =========\n');
        printf("======== CUT ZERO START =========\n");
        fflush(stdout);
        // 'CutZeroStart:74' fprintf('Initial: \n');
        printf("Initial: \n");
        fflush(stdout);
        // 'CutZeroStart:75' PrintCurvStruct(ctx, CurvStruct);
        PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                        b_CurvStruct);
        // 'CutZeroStart:77' fprintf('\nCut:\n');
        printf("\nCut:\n");
        fflush(stdout);
        // 'CutZeroStart:78' fprintf('Index = %d, t_cut = %e, vmax = %.1f\n', cut_index, t_cut,
        // vmax);
        printf("Index = %d, t_cut = %e, vmax = %.1f\n", cut_index, t[cut_index - 1], b_vmax);
        fflush(stdout);
        // 'CutZeroStart:79' fprintf('jps = %e, norm_vt(%d) = %f\n', jps, cut_index,
        // norm_vt_at_index);
        printf("jps = %e, norm_vt(%d) = %f\n", jps, cut_index, norm_vt[cut_index - 1]);
        fflush(stdout);
        // 'CutZeroStart:81' PrintCurvStruct(ctx, CurvStruct1);
        PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1);
        // 'CutZeroStart:82' PrintCurvStruct(ctx, CurvStruct2);
        PrintCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct2);
    }
}

//
// Arguments    : ::coder::array<double, 2U> &r
//                const ::coder::array<double, 2U> &r2D
//                const ::coder::array<double, 2U> &d1uk
//                const ::coder::array<double, 2U> &d2uk
// Return Type  : void
//
void b_binary_expand_op(::coder::array<double, 2U> &r, const ::coder::array<double, 2U> &r2D,
                        const ::coder::array<double, 2U> &d1uk,
                        const ::coder::array<double, 2U> &d2uk)
{
    ::coder::array<double, 2U> b_d1uk;
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (d2uk.size(1) == 1) {
        i = d1uk.size(1);
    } else {
        i = d2uk.size(1);
    }
    b_d1uk.set_size(1, i);
    stride_0_1 = (d1uk.size(1) != 1);
    stride_1_1 = (d2uk.size(1) != 1);
    if (d2uk.size(1) == 1) {
        loop_ub = d1uk.size(1);
    } else {
        loop_ub = d2uk.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        b_d1uk[i1] = d1uk[i1 * stride_0_1] * d2uk[i1 * stride_1_1];
    }
    coder::bsxfun(r2D, b_d1uk, r);
}

//
// Arguments    : ::coder::array<double, 2U> &a
//                const ::coder::array<double, 2U> &r
//                const ::coder::array<double, 2U> &r1
// Return Type  : void
//
void b_binary_expand_op(::coder::array<double, 2U> &a, const ::coder::array<double, 2U> &r,
                        const ::coder::array<double, 2U> &r1)
{
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (r1.size(1) == 1) {
        i = r.size(1);
    } else {
        i = r1.size(1);
    }
    a.set_size(i, 3);
    stride_0_0 = (r.size(1) != 1);
    stride_1_0 = (r1.size(1) != 1);
    if (r1.size(1) == 1) {
        loop_ub = r.size(1);
    } else {
        loop_ub = r1.size(1);
    }
    for (int i1{0}; i1 < 3; i1++) {
        for (int i2{0}; i2 < loop_ub; i2++) {
            a[i2 + a.size(0) * i1] = r[i1 + 3 * (i2 * stride_0_0)] + r1[i1 + 3 * (i2 * stride_1_0)];
        }
    }
}

//
// Arguments    : ::coder::array<double, 2U> &a
//                const ::coder::array<double, 2U> &r
//                const ::coder::array<double, 2U> &r1
//                const ::coder::array<double, 2U> &c
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &a, const ::coder::array<double, 2U> &r,
                      const ::coder::array<double, 2U> &r1, const ::coder::array<double, 2U> &c)
{
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    if (c.size(1) == 1) {
        if (r1.size(1) == 1) {
            i = r.size(1);
        } else {
            i = r1.size(1);
        }
    } else {
        i = c.size(1);
    }
    a.set_size(i, 3);
    stride_0_0 = (r.size(1) != 1);
    stride_1_0 = (r1.size(1) != 1);
    stride_2_0 = (c.size(1) != 1);
    if (c.size(1) == 1) {
        if (r1.size(1) == 1) {
            loop_ub = r.size(1);
        } else {
            loop_ub = r1.size(1);
        }
    } else {
        loop_ub = c.size(1);
    }
    for (int i1{0}; i1 < 3; i1++) {
        for (int i2{0}; i2 < loop_ub; i2++) {
            a[i2 + a.size(0) * i1] =
                (r[i1 + 3 * (i2 * stride_0_0)] + 3.0 * r1[i1 + 3 * (i2 * stride_1_0)]) +
                c[i1 + 3 * (i2 * stride_2_0)];
        }
    }
}

} // namespace ocn

//
// File trailer for CutZeroStart.cpp
//
// [EOF]
//
