//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CutZeroEnd.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "CutZeroEnd.h"
#include "CutCurvStruct.h"
#include "EvalCurvStruct.h"
#include "GetCurvMaxFeedrate.h"
#include "LengthCurv.h"
#include "bsxfun.h"
#include "colon.h"
#include "find.h"
#include "minOrMax.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "coder_array.h"
#include <cmath>
#include <math.h>

// Function Definitions
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
//                double ctx_cfg_NGridLengthSpline
//                const CurvStruct *b_CurvStruct
//                CurvStruct *CurvStruct1
//                CurvStruct *CurvStruct2
// Return Type  : void
//
namespace ocn {
void CutZeroEnd(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int ctx_cfg_NHorz,
                const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3], double ctx_cfg_dt,
                double ctx_cfg_ZeroStartAccLimit, double ctx_cfg_ZeroStartJerkLimit,
                double ctx_cfg_ZeroStartVelLimit, double ctx_cfg_NGridLengthSpline,
                const CurvStruct *b_CurvStruct, CurvStruct *CurvStruct1, CurvStruct *CurvStruct2)
{
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> at;
    ::coder::array<double, 2U> b_a;
    ::coder::array<double, 2U> b_d1uk;
    ::coder::array<double, 2U> b_r1D;
    ::coder::array<double, 2U> b_uk;
    ::coder::array<double, 2U> b_x;
    ::coder::array<double, 2U> b_z1;
    ::coder::array<double, 2U> c;
    ::coder::array<double, 2U> d1uk;
    ::coder::array<double, 2U> d2uk;
    ::coder::array<double, 2U> jt;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> t;
    ::coder::array<double, 2U> uk;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 2U> z1;
    ::coder::array<double, 1U> max_at;
    ::coder::array<double, 1U> max_jt;
    ::coder::array<bool, 2U> b_max_at;
    ::coder::array<bool, 2U> b_max_jt;
    ::coder::array<bool, 2U> c_x;
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
    unsigned long c_N;
    unsigned long c_k;
    int value_size[2];
    int N;
    int b_N;
    int b_loop_ub;
    int b_m;
    int b_value_data;
    int c_ex;
    int c_loop_ub;
    int c_value_data;
    int cut_index;
    int d_N;
    int d_loop_ub;
    int e_N;
    int e_loop_ub;
    int f_N;
    int f_loop_ub;
    int g_loop_ub;
    int i24;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int m;
    int m_loop_ub;
    int n_loop_ub;
    int o_loop_ub;
    int value_data;
    bool exitg1;
    b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                     b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                     b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                     b_CurvStruct->a_param, b_CurvStruct->b_param, a__1, r1D);
    z1_idx_1 = std::abs(r1D[1]);
    z1_idx_2 = std::abs(r1D[2]);
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
    jps = 6.0 / std::pow(tmax, 3.0);
    if ((-ctx_cfg_dt == 0.0) || ((tmax < 0.0) && (-ctx_cfg_dt < 0.0)) ||
        ((0.0 < tmax) && (-ctx_cfg_dt > 0.0))) {
        t.set_size(1, 0);
    } else if ((std::floor(tmax) == tmax) && (std::floor(-ctx_cfg_dt) == -ctx_cfg_dt)) {
        int loop_ub;
        loop_ub = static_cast<int>(std::floor((0.0 - tmax) / -ctx_cfg_dt));
        t.set_size(1, loop_ub + 1);
        for (int i{0}; i <= loop_ub; i++) {
            t[i] = tmax + -ctx_cfg_dt * static_cast<double>(i);
        }
    } else {
        coder::b_eml_float_colon(tmax, -ctx_cfg_dt, t);
    }
    z1.set_size(1, t.size(1));
    N = t.size(1);
    for (int k{0}; k < N; k++) {
        z1[k] = std::pow(t[k], 3.0);
    }
    uk.set_size(1, z1.size(1));
    b_loop_ub = z1.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        uk[i1] = jps * z1[i1] / 6.0;
    }
    z1.set_size(1, t.size(1));
    b_N = t.size(1);
    for (int b_k{0}; b_k < b_N; b_k++) {
        z1[b_k] = std::pow(t[b_k], 2.0);
    }
    d1uk.set_size(1, z1.size(1));
    c_loop_ub = z1.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        d1uk[i2] = jps * z1[i2] / 2.0;
    }
    d2uk.set_size(1, t.size(1));
    d_loop_ub = t.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        d2uk[i3] = jps * t[i3];
    }
    b_uk.set_size(1, uk.size(1));
    e_loop_ub = uk.size(1) - 1;
    for (int i4{0}; i4 <= e_loop_ub; i4++) {
        b_uk[i4] = uk[i4];
    }
    b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                     b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                     b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                     b_CurvStruct->a_param, b_CurvStruct->b_param, b_uk, a__2, b_r1D, r2D, r3D);
    b_vmax = b_CurvStruct->FeedRate;
    c_N = coder::internal::maximum2(2UL - ctx_cfg_NHorz);
    c_k = 1UL;
    exitg1 = false;
    while ((!exitg1) && (c_k >= c_N)) {
        double y;
        ctx_q_gcode->get(c_k, &expl_temp);
        y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                               expl_temp.P0, expl_temp.P1, expl_temp.CorrectedHelixCenter,
                               expl_temp.evec, expl_temp.theta, expl_temp.pitch, expl_temp.CoeffP5,
                               expl_temp.sp_index, expl_temp.FeedRate, expl_temp.a_param,
                               expl_temp.b_param);
        b_vmax = std::fmin(b_vmax, y);
        if (expl_temp.zspdmode == ZSpdMode_ZN) {
            exitg1 = true;
        } else {
            c_k--;
        }
    }
    z1.set_size(1, d1uk.size(1));
    d_N = d1uk.size(1);
    for (int d_k{0}; d_k < d_N; d_k++) {
        z1[d_k] = std::pow(d1uk[d_k], 3.0);
    }
    c.set_size(3, b_r1D.size(1));
    if (b_r1D.size(1) != 0) {
        int acoef;
        int i5;
        acoef = (b_r1D.size(1) != 1);
        i5 = b_r1D.size(1) - 1;
        for (int e_k{0}; e_k <= i5; e_k++) {
            int varargin_2;
            varargin_2 = acoef * e_k;
            c[3 * e_k] = b_r1D[3 * varargin_2] * jps;
            c[3 * e_k + 1] = b_r1D[3 * varargin_2 + 1] * jps;
            c[3 * e_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
        }
    }
    coder::bsxfun(r3D, z1, r);
    b_d1uk.set_size(1, d1uk.size(1));
    f_loop_ub = d1uk.size(1);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        b_d1uk[i6] = d1uk[i6] * d2uk[i6];
    }
    coder::bsxfun(r2D, b_d1uk, r1);
    a.set_size(r.size(1), 3);
    g_loop_ub = r.size(1);
    for (int i7{0}; i7 < 3; i7++) {
        for (int i8{0}; i8 < g_loop_ub; i8++) {
            a[i8 + a.size(0) * i7] = (r[i7 + 3 * i8] + 3.0 * r1[i7 + 3 * i8]) + c[i7 + 3 * i8];
        }
    }
    x.set_size(a.size(0), 3);
    if (a.size(0) != 0) {
        int b_acoef;
        b_acoef = (a.size(0) != 1);
        for (int f_k{0}; f_k < 3; f_k++) {
            int i9;
            i9 = x.size(0) - 1;
            for (int g_k{0}; g_k <= i9; g_k++) {
                x[g_k + x.size(0) * f_k] = a[b_acoef * g_k + a.size(0) * f_k] / ctx_cfg_jmax[f_k];
            }
        }
    }
    jt.set_size(x.size(0), 3);
    if (x.size(0) != 0) {
        int h_loop_ub;
        int i_loop_ub;
        at.set_size(x.size(0), 3);
        h_loop_ub = x.size(0);
        for (int i10{0}; i10 < 3; i10++) {
            for (int i11{0}; i11 < h_loop_ub; i11++) {
                at[i11 + at.size(0) * i10] = jt[i11 + jt.size(0) * i10];
            }
        }
        for (int i_k{0}; i_k < 3; i_k++) {
            int i12;
            i12 = at.size(0);
            for (int j_k{0}; j_k < i12; j_k++) {
                at[j_k + at.size(0) * i_k] = std::abs(x[j_k + x.size(0) * i_k]);
            }
        }
        jt.set_size(at.size(0), 3);
        i_loop_ub = at.size(0);
        for (int i13{0}; i13 < 3; i13++) {
            for (int i15{0}; i15 < i_loop_ub; i15++) {
                jt[i15 + jt.size(0) * i13] = at[i15 + at.size(0) * i13];
            }
        }
    }
    z1.set_size(1, d1uk.size(1));
    e_N = d1uk.size(1);
    for (int h_k{0}; h_k < e_N; h_k++) {
        z1[h_k] = std::pow(d1uk[h_k], 2.0);
    }
    coder::bsxfun(r2D, z1, r);
    coder::bsxfun(b_r1D, d2uk, r1);
    a.set_size(r.size(1), 3);
    j_loop_ub = r.size(1);
    for (int i14{0}; i14 < 3; i14++) {
        for (int i16{0}; i16 < j_loop_ub; i16++) {
            a[i16 + a.size(0) * i14] = r[i14 + 3 * i16] + r1[i14 + 3 * i16];
        }
    }
    x.set_size(a.size(0), 3);
    if (a.size(0) != 0) {
        int c_acoef;
        c_acoef = (a.size(0) != 1);
        for (int k_k{0}; k_k < 3; k_k++) {
            int i17;
            i17 = x.size(0) - 1;
            for (int m_k{0}; m_k <= i17; m_k++) {
                x[m_k + x.size(0) * k_k] = a[c_acoef * m_k + a.size(0) * k_k] / ctx_cfg_amax[k_k];
            }
        }
    }
    at.set_size(x.size(0), 3);
    if (x.size(0) != 0) {
        for (int l_k{0}; l_k < 3; l_k++) {
            int i18;
            i18 = at.size(0);
            for (int n_k{0}; n_k < i18; n_k++) {
                at[n_k + at.size(0) * l_k] = std::abs(x[n_k + x.size(0) * l_k]);
            }
        }
    }
    sqrt_calls++;
    m = jt.size(0) - 1;
    max_jt.set_size(jt.size(0));
    if (jt.size(0) >= 1) {
        for (int b_i{0}; b_i <= m; b_i++) {
            max_jt[b_i] = jt[b_i];
        }
        for (int j{0}; j < 2; j++) {
            for (int d_i{0}; d_i <= m; d_i++) {
                double d;
                d = jt[d_i + jt.size(0) * (j + 1)];
                if (max_jt[d_i] < d) {
                    max_jt[d_i] = d;
                }
            }
        }
    }
    b_m = at.size(0) - 1;
    max_at.set_size(at.size(0));
    if (at.size(0) >= 1) {
        for (int c_i{0}; c_i <= b_m; c_i++) {
            max_at[c_i] = at[c_i];
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
    b_max_at.set_size(1, max_at.size(0));
    k_loop_ub = max_at.size(0);
    for (int i19{0}; i19 < k_loop_ub; i19++) {
        b_max_at[i19] = (max_at[i19] > ctx_cfg_ZeroStartAccLimit);
    }
    coder::b_eml_find(b_max_at, (int *)&value_data, value_size);
    l_loop_ub = value_size[1];
    for (int i20{0}; i20 < l_loop_ub; i20++) {
        b_value_data = value_data;
    }
    if (value_size[1] == 0) {
        b_value_data = 1;
    }
    b_max_jt.set_size(1, max_jt.size(0));
    m_loop_ub = max_jt.size(0);
    for (int i21{0}; i21 < m_loop_ub; i21++) {
        b_max_jt[i21] = (max_jt[i21] > ctx_cfg_ZeroStartJerkLimit);
    }
    coder::b_eml_find(b_max_jt, (int *)&value_data, value_size);
    n_loop_ub = value_size[1];
    for (int i22{0}; i22 < n_loop_ub; i22++) {
        c_value_data = value_data;
    }
    if (value_size[1] == 0) {
        c_value_data = 1;
    }
    coder::bsxfun(b_r1D, d1uk, b_a);
    b_z1.set_size(3, b_a.size(1));
    f_N = b_a.size(1);
    for (int o_k{0}; o_k < f_N; o_k++) {
        b_z1[3 * o_k] = std::pow(b_a[3 * o_k], 2.0);
        b_z1[3 * o_k + 1] = std::pow(b_a[3 * o_k + 1], 2.0);
        b_z1[3 * o_k + 2] = std::pow(b_a[3 * o_k + 2], 2.0);
    }
    if (b_z1.size(1) == 0) {
        b_x.set_size(1, 0);
    } else {
        int i23;
        b_x.set_size(1, b_z1.size(1));
        i23 = b_z1.size(1);
        for (int p_k{0}; p_k < i23; p_k++) {
            b_x[p_k] = b_z1[3 * p_k];
            b_x[p_k] = b_x[p_k] + b_z1[3 * p_k + 1];
            b_x[p_k] = b_x[p_k] + b_z1[3 * p_k + 2];
        }
    }
    i24 = b_x.size(1);
    for (int q_k{0}; q_k < i24; q_k++) {
        b_x[q_k] = std::sqrt(b_x[q_k]);
    }
    c_x.set_size(1, b_x.size(1));
    o_loop_ub = b_x.size(1);
    for (int i25{0}; i25 < o_loop_ub; i25++) {
        c_x[i25] = (b_x[i25] / b_vmax > ctx_cfg_ZeroStartVelLimit);
    }
    coder::b_eml_find(c_x, (int *)&value_data, value_size);
    if (value_size[1] == 0) {
        value_data = 1;
    }
    c_ex = b_value_data;
    if (b_value_data < c_value_data) {
        c_ex = c_value_data;
    }
    if (c_ex < value_data) {
        c_ex = value_data;
    }
    cut_index =
        (max_at.size(0) -
         static_cast<int>(std::fmax(
             2.0, (static_cast<double>(max_at.size(0)) - static_cast<double>(c_ex)) + 1.0))) -
        1;
    //      actual_jps = jps;
    //      cut_index = N + 1 - cut_index;
    L = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->Type, b_CurvStruct->P0,
                   b_CurvStruct->P1, b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                   b_CurvStruct->theta, b_CurvStruct->pitch, b_CurvStruct->CoeffP5,
                   b_CurvStruct->sp_index, b_CurvStruct->a_param, b_CurvStruct->b_param);
    *CurvStruct1 = *b_CurvStruct;
    CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1, uk[cut_index] * L);
    *CurvStruct2 = *b_CurvStruct;
    b_CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2, L - uk[cut_index] * L);
    CurvStruct2->ConstJerkMaxIterations = max_at.size(0) - cut_index;
    CurvStruct2->UseConstJerk = true;
    CurvStruct2->ConstJerk = 6.0 / std::pow(t[cut_index], 3.0);
    CurvStruct1->zspdmode = ZSpdMode_NN;
    CurvStruct2->zspdmode = ZSpdMode_NZ;
    CurvStruct1->gcode_source_line = b_CurvStruct->gcode_source_line;
    CurvStruct2->gcode_source_line = b_CurvStruct->gcode_source_line;
}

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
//                double ctx_cfg_NGridLengthSpline
//                const CurvStruct *b_CurvStruct
//                double k0
//                CurvStruct *CurvStruct1
//                CurvStruct *CurvStruct2
// Return Type  : void
//
void CutZeroEnd(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int ctx_cfg_NHorz,
                const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3], double ctx_cfg_dt,
                double ctx_cfg_ZeroStartAccLimit, double ctx_cfg_ZeroStartJerkLimit,
                double ctx_cfg_ZeroStartVelLimit, double ctx_cfg_NGridLengthSpline,
                const CurvStruct *b_CurvStruct, double k0, CurvStruct *CurvStruct1,
                CurvStruct *CurvStruct2)
{
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> at;
    ::coder::array<double, 2U> b_a;
    ::coder::array<double, 2U> b_d1uk;
    ::coder::array<double, 2U> b_r1D;
    ::coder::array<double, 2U> b_uk;
    ::coder::array<double, 2U> b_x;
    ::coder::array<double, 2U> b_z1;
    ::coder::array<double, 2U> c;
    ::coder::array<double, 2U> d1uk;
    ::coder::array<double, 2U> d2uk;
    ::coder::array<double, 2U> jt;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> t;
    ::coder::array<double, 2U> uk;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 2U> z1;
    ::coder::array<double, 1U> max_at;
    ::coder::array<double, 1U> max_jt;
    ::coder::array<bool, 2U> b_max_at;
    ::coder::array<bool, 2U> b_max_jt;
    ::coder::array<bool, 2U> c_x;
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
    unsigned long c_N;
    unsigned long c_k;
    unsigned long z;
    int value_size[2];
    int N;
    int b_N;
    int b_exp;
    int b_loop_ub;
    int b_m;
    int b_value_data;
    int c_ex;
    int c_loop_ub;
    int c_value_data;
    int cut_index;
    int d_N;
    int d_loop_ub;
    int e_N;
    int e_loop_ub;
    int f_N;
    int f_loop_ub;
    int g_loop_ub;
    int i24;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int m;
    int m_loop_ub;
    int n_loop_ub;
    int o_loop_ub;
    int value_data;
    bool exitg1;
    b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                     b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                     b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                     b_CurvStruct->a_param, b_CurvStruct->b_param, a__1, r1D);
    z1_idx_1 = std::abs(r1D[1]);
    z1_idx_2 = std::abs(r1D[2]);
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
    jps = 6.0 / std::pow(tmax, 3.0);
    if ((-ctx_cfg_dt == 0.0) || ((tmax < 0.0) && (-ctx_cfg_dt < 0.0)) ||
        ((0.0 < tmax) && (-ctx_cfg_dt > 0.0))) {
        t.set_size(1, 0);
    } else if ((std::floor(tmax) == tmax) && (std::floor(-ctx_cfg_dt) == -ctx_cfg_dt)) {
        int loop_ub;
        loop_ub = static_cast<int>(std::floor((0.0 - tmax) / -ctx_cfg_dt));
        t.set_size(1, loop_ub + 1);
        for (int i{0}; i <= loop_ub; i++) {
            t[i] = tmax + -ctx_cfg_dt * static_cast<double>(i);
        }
    } else {
        coder::b_eml_float_colon(tmax, -ctx_cfg_dt, t);
    }
    z1.set_size(1, t.size(1));
    N = t.size(1);
    for (int k{0}; k < N; k++) {
        z1[k] = std::pow(t[k], 3.0);
    }
    uk.set_size(1, z1.size(1));
    b_loop_ub = z1.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        uk[i1] = jps * z1[i1] / 6.0;
    }
    z1.set_size(1, t.size(1));
    b_N = t.size(1);
    for (int b_k{0}; b_k < b_N; b_k++) {
        z1[b_k] = std::pow(t[b_k], 2.0);
    }
    d1uk.set_size(1, z1.size(1));
    c_loop_ub = z1.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        d1uk[i2] = jps * z1[i2] / 2.0;
    }
    d2uk.set_size(1, t.size(1));
    d_loop_ub = t.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        d2uk[i3] = jps * t[i3];
    }
    b_uk.set_size(1, uk.size(1));
    e_loop_ub = uk.size(1) - 1;
    for (int i4{0}; i4 <= e_loop_ub; i4++) {
        b_uk[i4] = uk[i4];
    }
    b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                     b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                     b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                     b_CurvStruct->a_param, b_CurvStruct->b_param, b_uk, a__2, b_r1D, r2D, r3D);
    b_vmax = b_CurvStruct->FeedRate;
    if ((0.0 <= k0) && (k0 < 1.8446744073709552E+19)) {
        z = static_cast<unsigned long>(k0) - ctx_cfg_NHorz;
    } else {
        double xd;
        unsigned long dif;
        xd = frexp(k0, &b_exp);
        dif = static_cast<unsigned long>(std::ldexp(xd, 64)) -
              (static_cast<unsigned long>(ctx_cfg_NHorz) >> 1);
        if ((dif & 9223372036854775808UL) > 0UL) {
            z = MAX_uint64_T;
        } else {
            z = dif << 1;
            if ((ctx_cfg_NHorz & 1UL) == 1UL) {
                z--;
            }
        }
    }
    c_N = coder::internal::maximum2(z + 1UL);
    c_k = static_cast<unsigned long>(std::round(k0));
    exitg1 = false;
    while ((!exitg1) && (c_k >= c_N)) {
        double y;
        ctx_q_gcode->get(c_k, &expl_temp);
        y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                               expl_temp.P0, expl_temp.P1, expl_temp.CorrectedHelixCenter,
                               expl_temp.evec, expl_temp.theta, expl_temp.pitch, expl_temp.CoeffP5,
                               expl_temp.sp_index, expl_temp.FeedRate, expl_temp.a_param,
                               expl_temp.b_param);
        b_vmax = std::fmin(b_vmax, y);
        if (expl_temp.zspdmode == ZSpdMode_ZN) {
            exitg1 = true;
        } else {
            c_k--;
        }
    }
    z1.set_size(1, d1uk.size(1));
    d_N = d1uk.size(1);
    for (int d_k{0}; d_k < d_N; d_k++) {
        z1[d_k] = std::pow(d1uk[d_k], 3.0);
    }
    c.set_size(3, b_r1D.size(1));
    if (b_r1D.size(1) != 0) {
        int acoef;
        int i5;
        acoef = (b_r1D.size(1) != 1);
        i5 = b_r1D.size(1) - 1;
        for (int e_k{0}; e_k <= i5; e_k++) {
            int varargin_2;
            varargin_2 = acoef * e_k;
            c[3 * e_k] = b_r1D[3 * varargin_2] * jps;
            c[3 * e_k + 1] = b_r1D[3 * varargin_2 + 1] * jps;
            c[3 * e_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
        }
    }
    coder::bsxfun(r3D, z1, r);
    b_d1uk.set_size(1, d1uk.size(1));
    f_loop_ub = d1uk.size(1);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        b_d1uk[i6] = d1uk[i6] * d2uk[i6];
    }
    coder::bsxfun(r2D, b_d1uk, r1);
    a.set_size(r.size(1), 3);
    g_loop_ub = r.size(1);
    for (int i7{0}; i7 < 3; i7++) {
        for (int i8{0}; i8 < g_loop_ub; i8++) {
            a[i8 + a.size(0) * i7] = (r[i7 + 3 * i8] + 3.0 * r1[i7 + 3 * i8]) + c[i7 + 3 * i8];
        }
    }
    x.set_size(a.size(0), 3);
    if (a.size(0) != 0) {
        int b_acoef;
        b_acoef = (a.size(0) != 1);
        for (int f_k{0}; f_k < 3; f_k++) {
            int i9;
            i9 = x.size(0) - 1;
            for (int g_k{0}; g_k <= i9; g_k++) {
                x[g_k + x.size(0) * f_k] = a[b_acoef * g_k + a.size(0) * f_k] / ctx_cfg_jmax[f_k];
            }
        }
    }
    jt.set_size(x.size(0), 3);
    if (x.size(0) != 0) {
        int h_loop_ub;
        int i_loop_ub;
        at.set_size(x.size(0), 3);
        h_loop_ub = x.size(0);
        for (int i10{0}; i10 < 3; i10++) {
            for (int i11{0}; i11 < h_loop_ub; i11++) {
                at[i11 + at.size(0) * i10] = jt[i11 + jt.size(0) * i10];
            }
        }
        for (int i_k{0}; i_k < 3; i_k++) {
            int i12;
            i12 = at.size(0);
            for (int j_k{0}; j_k < i12; j_k++) {
                at[j_k + at.size(0) * i_k] = std::abs(x[j_k + x.size(0) * i_k]);
            }
        }
        jt.set_size(at.size(0), 3);
        i_loop_ub = at.size(0);
        for (int i13{0}; i13 < 3; i13++) {
            for (int i15{0}; i15 < i_loop_ub; i15++) {
                jt[i15 + jt.size(0) * i13] = at[i15 + at.size(0) * i13];
            }
        }
    }
    z1.set_size(1, d1uk.size(1));
    e_N = d1uk.size(1);
    for (int h_k{0}; h_k < e_N; h_k++) {
        z1[h_k] = std::pow(d1uk[h_k], 2.0);
    }
    coder::bsxfun(r2D, z1, r);
    coder::bsxfun(b_r1D, d2uk, r1);
    a.set_size(r.size(1), 3);
    j_loop_ub = r.size(1);
    for (int i14{0}; i14 < 3; i14++) {
        for (int i16{0}; i16 < j_loop_ub; i16++) {
            a[i16 + a.size(0) * i14] = r[i14 + 3 * i16] + r1[i14 + 3 * i16];
        }
    }
    x.set_size(a.size(0), 3);
    if (a.size(0) != 0) {
        int c_acoef;
        c_acoef = (a.size(0) != 1);
        for (int k_k{0}; k_k < 3; k_k++) {
            int i17;
            i17 = x.size(0) - 1;
            for (int m_k{0}; m_k <= i17; m_k++) {
                x[m_k + x.size(0) * k_k] = a[c_acoef * m_k + a.size(0) * k_k] / ctx_cfg_amax[k_k];
            }
        }
    }
    at.set_size(x.size(0), 3);
    if (x.size(0) != 0) {
        for (int l_k{0}; l_k < 3; l_k++) {
            int i18;
            i18 = at.size(0);
            for (int n_k{0}; n_k < i18; n_k++) {
                at[n_k + at.size(0) * l_k] = std::abs(x[n_k + x.size(0) * l_k]);
            }
        }
    }
    sqrt_calls++;
    m = jt.size(0) - 1;
    max_jt.set_size(jt.size(0));
    if (jt.size(0) >= 1) {
        for (int b_i{0}; b_i <= m; b_i++) {
            max_jt[b_i] = jt[b_i];
        }
        for (int j{0}; j < 2; j++) {
            for (int d_i{0}; d_i <= m; d_i++) {
                double d;
                d = jt[d_i + jt.size(0) * (j + 1)];
                if (max_jt[d_i] < d) {
                    max_jt[d_i] = d;
                }
            }
        }
    }
    b_m = at.size(0) - 1;
    max_at.set_size(at.size(0));
    if (at.size(0) >= 1) {
        for (int c_i{0}; c_i <= b_m; c_i++) {
            max_at[c_i] = at[c_i];
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
    b_max_at.set_size(1, max_at.size(0));
    k_loop_ub = max_at.size(0);
    for (int i19{0}; i19 < k_loop_ub; i19++) {
        b_max_at[i19] = (max_at[i19] > ctx_cfg_ZeroStartAccLimit);
    }
    coder::b_eml_find(b_max_at, (int *)&value_data, value_size);
    l_loop_ub = value_size[1];
    for (int i20{0}; i20 < l_loop_ub; i20++) {
        b_value_data = value_data;
    }
    if (value_size[1] == 0) {
        b_value_data = 1;
    }
    b_max_jt.set_size(1, max_jt.size(0));
    m_loop_ub = max_jt.size(0);
    for (int i21{0}; i21 < m_loop_ub; i21++) {
        b_max_jt[i21] = (max_jt[i21] > ctx_cfg_ZeroStartJerkLimit);
    }
    coder::b_eml_find(b_max_jt, (int *)&value_data, value_size);
    n_loop_ub = value_size[1];
    for (int i22{0}; i22 < n_loop_ub; i22++) {
        c_value_data = value_data;
    }
    if (value_size[1] == 0) {
        c_value_data = 1;
    }
    coder::bsxfun(b_r1D, d1uk, b_a);
    b_z1.set_size(3, b_a.size(1));
    f_N = b_a.size(1);
    for (int o_k{0}; o_k < f_N; o_k++) {
        b_z1[3 * o_k] = std::pow(b_a[3 * o_k], 2.0);
        b_z1[3 * o_k + 1] = std::pow(b_a[3 * o_k + 1], 2.0);
        b_z1[3 * o_k + 2] = std::pow(b_a[3 * o_k + 2], 2.0);
    }
    if (b_z1.size(1) == 0) {
        b_x.set_size(1, 0);
    } else {
        int i23;
        b_x.set_size(1, b_z1.size(1));
        i23 = b_z1.size(1);
        for (int p_k{0}; p_k < i23; p_k++) {
            b_x[p_k] = b_z1[3 * p_k];
            b_x[p_k] = b_x[p_k] + b_z1[3 * p_k + 1];
            b_x[p_k] = b_x[p_k] + b_z1[3 * p_k + 2];
        }
    }
    i24 = b_x.size(1);
    for (int q_k{0}; q_k < i24; q_k++) {
        b_x[q_k] = std::sqrt(b_x[q_k]);
    }
    c_x.set_size(1, b_x.size(1));
    o_loop_ub = b_x.size(1);
    for (int i25{0}; i25 < o_loop_ub; i25++) {
        c_x[i25] = (b_x[i25] / b_vmax > ctx_cfg_ZeroStartVelLimit);
    }
    coder::b_eml_find(c_x, (int *)&value_data, value_size);
    if (value_size[1] == 0) {
        value_data = 1;
    }
    c_ex = b_value_data;
    if (b_value_data < c_value_data) {
        c_ex = c_value_data;
    }
    if (c_ex < value_data) {
        c_ex = value_data;
    }
    cut_index =
        (max_at.size(0) -
         static_cast<int>(std::fmax(
             2.0, (static_cast<double>(max_at.size(0)) - static_cast<double>(c_ex)) + 1.0))) -
        1;
    //      actual_jps = jps;
    //      cut_index = N + 1 - cut_index;
    L = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->Type, b_CurvStruct->P0,
                   b_CurvStruct->P1, b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                   b_CurvStruct->theta, b_CurvStruct->pitch, b_CurvStruct->CoeffP5,
                   b_CurvStruct->sp_index, b_CurvStruct->a_param, b_CurvStruct->b_param);
    *CurvStruct1 = *b_CurvStruct;
    CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1, uk[cut_index] * L);
    *CurvStruct2 = *b_CurvStruct;
    b_CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2, L - uk[cut_index] * L);
    CurvStruct2->ConstJerkMaxIterations = max_at.size(0) - cut_index;
    CurvStruct2->UseConstJerk = true;
    CurvStruct2->ConstJerk = 6.0 / std::pow(t[cut_index], 3.0);
    CurvStruct1->zspdmode = ZSpdMode_NN;
    CurvStruct2->zspdmode = ZSpdMode_NZ;
    CurvStruct1->gcode_source_line = b_CurvStruct->gcode_source_line;
    CurvStruct2->gcode_source_line = b_CurvStruct->gcode_source_line;
}

} // namespace ocn

//
// File trailer for CutZeroEnd.cpp
//
// [EOF]
//
