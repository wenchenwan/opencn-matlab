//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CutZeroEnd.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "CutZeroEnd.h"
#include "CutCurvStruct.h"
#include "CutZeroStart.h"
#include "EvalCurvStruct.h"
#include "GetCurvMaxFeedrate.h"
#include "LengthCurv.h"
#include "bsxfun.h"
#include "colon.h"
#include "find.h"
#include "minOrMax.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_rtwutil.h"
#include "sinspace_types1.h"
#include "sinspace_types11.h"
#include "sinspace_types2.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
namespace ocn {
static void MultiWordSub(const unsigned int u1[], const unsigned int u2[], unsigned int y[]);

}

// Function Definitions
//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
//                unsigned int y[]
// Return Type  : void
//
namespace ocn {
static void MultiWordSub(const unsigned int u1[], const unsigned int u2[], unsigned int y[])
{
    int borrow{0};
    for (int i{0}; i < 2; i++) {
        unsigned int u1i;
        unsigned int yi;
        u1i = u1[i];
        yi = (u1i - u2[i]) - borrow;
        y[i] = yi;
        if (static_cast<unsigned int>(borrow) != 0U) {
            borrow = (yi >= u1i);
        } else {
            borrow = (yi > u1i);
        }
    }
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
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *b_CurvStruct
//                CurvStruct *CurvStruct1
//                CurvStruct *CurvStruct2
// Return Type  : void
//
void CutZeroEnd(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int ctx_cfg_NHorz,
                const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3], double ctx_cfg_dt,
                double ctx_cfg_ZeroStartAccLimit, double ctx_cfg_ZeroStartJerkLimit,
                double ctx_cfg_ZeroStartVelLimit, const double ctx_cfg_GaussLegendreX[5],
                const double ctx_cfg_GaussLegendreW[5], const CurvStruct *b_CurvStruct,
                CurvStruct *CurvStruct1, CurvStruct *CurvStruct2)
{
    static const uint64m_T r2{
        {2U, 0U} // chunks
    };
    static const uint64m_T r4{
        {1U, 0U} // chunks
    };
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
    ::coder::array<double, 2U> r5;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> t;
    ::coder::array<double, 2U> uk;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 1U> max_at;
    ::coder::array<double, 1U> max_jt;
    ::coder::array<bool, 2U> b_max_at;
    ::coder::array<bool, 2U> b_max_jt;
    ::coder::array<bool, 2U> c_x;
    CurvStruct expl_temp;
    uint64m_T N;
    uint64m_T k;
    uint64m_T r1;
    uint64m_T r3;
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
    int value_size[2];
    int b_loop_ub;
    int b_m;
    int b_value_data;
    int c_ex;
    int c_loop_ub;
    int c_value_data;
    int cut_index;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i10;
    int i30;
    int l_loop_ub;
    int m;
    int o_loop_ub;
    int p_loop_ub;
    int q_loop_ub;
    int r_loop_ub;
    int s_loop_ub;
    int t_loop_ub;
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
    r.set_size(1, t.size(1));
    b_loop_ub = t.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        double varargin_1;
        varargin_1 = t[i1];
        r[i1] = std::pow(varargin_1, 3.0);
    }
    uk.set_size(1, r.size(1));
    c_loop_ub = r.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        uk[i2] = jps * r[i2] / 6.0;
    }
    r.set_size(1, t.size(1));
    d_loop_ub = t.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        double b_varargin_1;
        b_varargin_1 = t[i3];
        r[i3] = std::pow(b_varargin_1, 2.0);
    }
    d1uk.set_size(1, r.size(1));
    e_loop_ub = r.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        d1uk[i4] = jps * r[i4] / 2.0;
    }
    d2uk.set_size(1, t.size(1));
    f_loop_ub = t.size(1);
    for (int i5{0}; i5 < f_loop_ub; i5++) {
        d2uk[i5] = jps * t[i5];
    }
    b_uk.set_size(1, uk.size(1));
    g_loop_ub = uk.size(1) - 1;
    for (int i6{0}; i6 <= g_loop_ub; i6++) {
        b_uk[i6] = uk[i6];
    }
    b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                     b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                     b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                     b_CurvStruct->a_param, b_CurvStruct->b_param, b_uk, a__2, b_r1D, r2D, r3D);
    b_vmax = b_CurvStruct->FeedRate;
    sLong2MultiWord(ctx_cfg_NHorz, (unsigned int *)&r1.chunks[0U]);
    MultiWordSub((unsigned int *)&r2.chunks[0U], (unsigned int *)&r1.chunks[0U],
                 (unsigned int *)&r3.chunks[0U]);
    N = coder::internal::maximum2(r3);
    k = r4;
    exitg1 = false;
    while ((!exitg1) &&
           uMultiWordGe((unsigned int *)&k.chunks[0U], (unsigned int *)&N.chunks[0U])) {
        double y;
        ctx_q_gcode->get(k, &expl_temp);
        y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                               expl_temp.P0, expl_temp.P1, expl_temp.CorrectedHelixCenter,
                               expl_temp.evec, expl_temp.theta, expl_temp.pitch, expl_temp.CoeffP5,
                               expl_temp.sp_index, expl_temp.FeedRate, expl_temp.a_param,
                               expl_temp.b_param);
        b_vmax = std::fmin(b_vmax, y);
        if (expl_temp.zspdmode == ZSpdMode_ZN) {
            exitg1 = true;
        } else {
            MultiWordSub((unsigned int *)&k.chunks[0U], (unsigned int *)&r4.chunks[0U],
                         (unsigned int *)&r1.chunks[0U]);
            k = r1;
        }
    }
    c.set_size(3, b_r1D.size(1));
    if (b_r1D.size(1) != 0) {
        int acoef;
        int i7;
        acoef = (b_r1D.size(1) != 1);
        i7 = b_r1D.size(1) - 1;
        for (int b_k{0}; b_k <= i7; b_k++) {
            int varargin_2;
            varargin_2 = acoef * b_k;
            c[3 * b_k] = b_r1D[3 * varargin_2] * jps;
            c[3 * b_k + 1] = b_r1D[3 * varargin_2 + 1] * jps;
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
    coder::bsxfun(r3D, r, r5);
    if (d1uk.size(1) == d2uk.size(1)) {
        int i_loop_ub;
        b_d1uk.set_size(1, d1uk.size(1));
        i_loop_ub = d1uk.size(1);
        for (int i9{0}; i9 < i_loop_ub; i9++) {
            b_d1uk[i9] = d1uk[i9] * d2uk[i9];
        }
        coder::bsxfun(r2D, b_d1uk, r6);
    } else {
        b_binary_expand_op(r6, r2D, d1uk, d2uk);
    }
    if (r5.size(1) == 1) {
        i10 = r6.size(1);
    } else {
        i10 = r5.size(1);
    }
    if ((r5.size(1) == r6.size(1)) && (i10 == c.size(1))) {
        int j_loop_ub;
        a.set_size(r5.size(1), 3);
        j_loop_ub = r5.size(1);
        for (int i11{0}; i11 < 3; i11++) {
            for (int i12{0}; i12 < j_loop_ub; i12++) {
                a[i12 + a.size(0) * i11] =
                    (r5[i11 + 3 * i12] + 3.0 * r6[i11 + 3 * i12]) + c[i11 + 3 * i12];
            }
        }
    } else {
        binary_expand_op(a, r5, r6, c);
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
            for (int i20{0}; i20 < m_loop_ub; i20++) {
                jt[i20 + jt.size(0) * i18] = at[i20 + at.size(0) * i18];
            }
        }
    }
    r.set_size(1, d1uk.size(1));
    l_loop_ub = d1uk.size(1);
    for (int i15{0}; i15 < l_loop_ub; i15++) {
        double d_varargin_1;
        d_varargin_1 = d1uk[i15];
        r[i15] = std::pow(d_varargin_1, 2.0);
    }
    coder::bsxfun(r2D, r, r5);
    coder::bsxfun(b_r1D, d2uk, r6);
    if (r5.size(1) == r6.size(1)) {
        int n_loop_ub;
        a.set_size(r5.size(1), 3);
        n_loop_ub = r5.size(1);
        for (int i19{0}; i19 < 3; i19++) {
            for (int i21{0}; i21 < n_loop_ub; i21++) {
                a[i21 + a.size(0) * i19] = r5[i19 + 3 * i21] + r6[i19 + 3 * i21];
            }
        }
    } else {
        b_binary_expand_op(a, r5, r6);
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
    o_loop_ub = max_at.size(0);
    for (int i24{0}; i24 < o_loop_ub; i24++) {
        b_max_at[i24] = (max_at[i24] > ctx_cfg_ZeroStartAccLimit);
    }
    coder::c_eml_find(b_max_at, (int *)&value_data, value_size);
    p_loop_ub = value_size[1];
    for (int i25{0}; i25 < p_loop_ub; i25++) {
        b_value_data = value_data;
    }
    if (value_size[1] == 0) {
        b_value_data = 1;
    }
    b_max_jt.set_size(1, max_jt.size(0));
    q_loop_ub = max_jt.size(0);
    for (int i26{0}; i26 < q_loop_ub; i26++) {
        b_max_jt[i26] = (max_jt[i26] > ctx_cfg_ZeroStartJerkLimit);
    }
    coder::c_eml_find(b_max_jt, (int *)&value_data, value_size);
    r_loop_ub = value_size[1];
    for (int i27{0}; i27 < r_loop_ub; i27++) {
        c_value_data = value_data;
    }
    if (value_size[1] == 0) {
        c_value_data = 1;
    }
    coder::bsxfun(b_r1D, d1uk, r5);
    r5.set_size(3, r5.size(1));
    s_loop_ub = r5.size(1);
    for (int i28{0}; i28 < s_loop_ub; i28++) {
        double e_varargin_1;
        double f_varargin_1;
        double g_varargin_1;
        e_varargin_1 = r5[3 * i28];
        r5[3 * i28] = std::pow(e_varargin_1, 2.0);
        f_varargin_1 = r5[3 * i28 + 1];
        r5[3 * i28 + 1] = std::pow(f_varargin_1, 2.0);
        g_varargin_1 = r5[3 * i28 + 2];
        r5[3 * i28 + 2] = std::pow(g_varargin_1, 2.0);
    }
    if (r5.size(1) == 0) {
        b_x.set_size(1, 0);
    } else {
        int i29;
        b_x.set_size(1, r5.size(1));
        i29 = r5.size(1);
        for (int k_k{0}; k_k < i29; k_k++) {
            b_x[k_k] = r5[3 * k_k];
            b_x[k_k] = b_x[k_k] + r5[3 * k_k + 1];
            b_x[k_k] = b_x[k_k] + r5[3 * k_k + 2];
        }
    }
    i30 = b_x.size(1);
    for (int l_k{0}; l_k < i30; l_k++) {
        b_x[l_k] = std::sqrt(b_x[l_k]);
    }
    c_x.set_size(1, b_x.size(1));
    t_loop_ub = b_x.size(1);
    for (int i31{0}; i31 < t_loop_ub; i31++) {
        c_x[i31] = (b_x[i31] / b_vmax > ctx_cfg_ZeroStartVelLimit);
    }
    coder::c_eml_find(c_x, (int *)&value_data, value_size);
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
    L = LengthCurv(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                   b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                   b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                   b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                   b_CurvStruct->a_param, b_CurvStruct->b_param);
    *CurvStruct1 = *b_CurvStruct;
    CutCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1,
                  uk[cut_index] * L);
    *CurvStruct2 = *b_CurvStruct;
    b_CutCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct2,
                    L - uk[cut_index] * L);
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
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *b_CurvStruct
//                double k0
//                CurvStruct *CurvStruct1
//                CurvStruct *CurvStruct2
// Return Type  : void
//
void CutZeroEnd(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int ctx_cfg_NHorz,
                const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3], double ctx_cfg_dt,
                double ctx_cfg_ZeroStartAccLimit, double ctx_cfg_ZeroStartJerkLimit,
                double ctx_cfg_ZeroStartVelLimit, const double ctx_cfg_GaussLegendreX[5],
                const double ctx_cfg_GaussLegendreW[5], const CurvStruct *b_CurvStruct, double k0,
                CurvStruct *CurvStruct1, CurvStruct *CurvStruct2)
{
    static const uint64m_T r4{
        {1U, 0U} // chunks
    };
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
    ::coder::array<double, 2U> r5;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> t;
    ::coder::array<double, 2U> uk;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 1U> max_at;
    ::coder::array<double, 1U> max_jt;
    ::coder::array<bool, 2U> b_max_at;
    ::coder::array<bool, 2U> b_max_jt;
    ::coder::array<bool, 2U> c_x;
    CurvStruct expl_temp;
    uint64m_T N;
    uint64m_T k;
    uint64m_T r1;
    uint64m_T r2;
    uint64m_T r3;
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
    int value_size[2];
    int b_loop_ub;
    int b_m;
    int b_value_data;
    int c_ex;
    int c_loop_ub;
    int c_value_data;
    int cut_index;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i10;
    int i30;
    int l_loop_ub;
    int m;
    int o_loop_ub;
    int p_loop_ub;
    int q_loop_ub;
    int r_loop_ub;
    int s_loop_ub;
    int t_loop_ub;
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
    r.set_size(1, t.size(1));
    b_loop_ub = t.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        double varargin_1;
        varargin_1 = t[i1];
        r[i1] = std::pow(varargin_1, 3.0);
    }
    uk.set_size(1, r.size(1));
    c_loop_ub = r.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        uk[i2] = jps * r[i2] / 6.0;
    }
    r.set_size(1, t.size(1));
    d_loop_ub = t.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        double b_varargin_1;
        b_varargin_1 = t[i3];
        r[i3] = std::pow(b_varargin_1, 2.0);
    }
    d1uk.set_size(1, r.size(1));
    e_loop_ub = r.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        d1uk[i4] = jps * r[i4] / 2.0;
    }
    d2uk.set_size(1, t.size(1));
    f_loop_ub = t.size(1);
    for (int i5{0}; i5 < f_loop_ub; i5++) {
        d2uk[i5] = jps * t[i5];
    }
    b_uk.set_size(1, uk.size(1));
    g_loop_ub = uk.size(1) - 1;
    for (int i6{0}; i6 <= g_loop_ub; i6++) {
        b_uk[i6] = uk[i6];
    }
    b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                     b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                     b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                     b_CurvStruct->a_param, b_CurvStruct->b_param, b_uk, a__2, b_r1D, r2D, r3D);
    b_vmax = b_CurvStruct->FeedRate;
    Double2MultiWord(k0, (unsigned int *)&r1.chunks[0U]);
    sLong2MultiWord(ctx_cfg_NHorz, (unsigned int *)&r2.chunks[0U]);
    MultiWordSub((unsigned int *)&r1.chunks[0U], (unsigned int *)&r2.chunks[0U],
                 (unsigned int *)&r3.chunks[0U]);
    r1 = r4;
    MultiWordAdd((unsigned int *)&r3.chunks[0U], (unsigned int *)&r4.chunks[0U],
                 (unsigned int *)&r2.chunks[0U]);
    N = coder::internal::maximum2(r2);
    Double2MultiWord(std::round(k0), (unsigned int *)&k.chunks[0U]);
    exitg1 = false;
    while ((!exitg1) &&
           uMultiWordGe((unsigned int *)&k.chunks[0U], (unsigned int *)&N.chunks[0U])) {
        double y;
        ctx_q_gcode->get(k, &expl_temp);
        y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                               expl_temp.P0, expl_temp.P1, expl_temp.CorrectedHelixCenter,
                               expl_temp.evec, expl_temp.theta, expl_temp.pitch, expl_temp.CoeffP5,
                               expl_temp.sp_index, expl_temp.FeedRate, expl_temp.a_param,
                               expl_temp.b_param);
        b_vmax = std::fmin(b_vmax, y);
        if (expl_temp.zspdmode == ZSpdMode_ZN) {
            exitg1 = true;
        } else {
            MultiWordSub((unsigned int *)&k.chunks[0U], (unsigned int *)&r4.chunks[0U],
                         (unsigned int *)&r1.chunks[0U]);
            k = r1;
        }
    }
    c.set_size(3, b_r1D.size(1));
    if (b_r1D.size(1) != 0) {
        int acoef;
        int i7;
        acoef = (b_r1D.size(1) != 1);
        i7 = b_r1D.size(1) - 1;
        for (int b_k{0}; b_k <= i7; b_k++) {
            int varargin_2;
            varargin_2 = acoef * b_k;
            c[3 * b_k] = b_r1D[3 * varargin_2] * jps;
            c[3 * b_k + 1] = b_r1D[3 * varargin_2 + 1] * jps;
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
    coder::bsxfun(r3D, r, r5);
    if (d1uk.size(1) == d2uk.size(1)) {
        int i_loop_ub;
        b_d1uk.set_size(1, d1uk.size(1));
        i_loop_ub = d1uk.size(1);
        for (int i9{0}; i9 < i_loop_ub; i9++) {
            b_d1uk[i9] = d1uk[i9] * d2uk[i9];
        }
        coder::bsxfun(r2D, b_d1uk, r6);
    } else {
        b_binary_expand_op(r6, r2D, d1uk, d2uk);
    }
    if (r5.size(1) == 1) {
        i10 = r6.size(1);
    } else {
        i10 = r5.size(1);
    }
    if ((r5.size(1) == r6.size(1)) && (i10 == c.size(1))) {
        int j_loop_ub;
        a.set_size(r5.size(1), 3);
        j_loop_ub = r5.size(1);
        for (int i11{0}; i11 < 3; i11++) {
            for (int i12{0}; i12 < j_loop_ub; i12++) {
                a[i12 + a.size(0) * i11] =
                    (r5[i11 + 3 * i12] + 3.0 * r6[i11 + 3 * i12]) + c[i11 + 3 * i12];
            }
        }
    } else {
        binary_expand_op(a, r5, r6, c);
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
            for (int i20{0}; i20 < m_loop_ub; i20++) {
                jt[i20 + jt.size(0) * i18] = at[i20 + at.size(0) * i18];
            }
        }
    }
    r.set_size(1, d1uk.size(1));
    l_loop_ub = d1uk.size(1);
    for (int i15{0}; i15 < l_loop_ub; i15++) {
        double d_varargin_1;
        d_varargin_1 = d1uk[i15];
        r[i15] = std::pow(d_varargin_1, 2.0);
    }
    coder::bsxfun(r2D, r, r5);
    coder::bsxfun(b_r1D, d2uk, r6);
    if (r5.size(1) == r6.size(1)) {
        int n_loop_ub;
        a.set_size(r5.size(1), 3);
        n_loop_ub = r5.size(1);
        for (int i19{0}; i19 < 3; i19++) {
            for (int i21{0}; i21 < n_loop_ub; i21++) {
                a[i21 + a.size(0) * i19] = r5[i19 + 3 * i21] + r6[i19 + 3 * i21];
            }
        }
    } else {
        b_binary_expand_op(a, r5, r6);
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
    o_loop_ub = max_at.size(0);
    for (int i24{0}; i24 < o_loop_ub; i24++) {
        b_max_at[i24] = (max_at[i24] > ctx_cfg_ZeroStartAccLimit);
    }
    coder::c_eml_find(b_max_at, (int *)&value_data, value_size);
    p_loop_ub = value_size[1];
    for (int i25{0}; i25 < p_loop_ub; i25++) {
        b_value_data = value_data;
    }
    if (value_size[1] == 0) {
        b_value_data = 1;
    }
    b_max_jt.set_size(1, max_jt.size(0));
    q_loop_ub = max_jt.size(0);
    for (int i26{0}; i26 < q_loop_ub; i26++) {
        b_max_jt[i26] = (max_jt[i26] > ctx_cfg_ZeroStartJerkLimit);
    }
    coder::c_eml_find(b_max_jt, (int *)&value_data, value_size);
    r_loop_ub = value_size[1];
    for (int i27{0}; i27 < r_loop_ub; i27++) {
        c_value_data = value_data;
    }
    if (value_size[1] == 0) {
        c_value_data = 1;
    }
    coder::bsxfun(b_r1D, d1uk, r5);
    r5.set_size(3, r5.size(1));
    s_loop_ub = r5.size(1);
    for (int i28{0}; i28 < s_loop_ub; i28++) {
        double e_varargin_1;
        double f_varargin_1;
        double g_varargin_1;
        e_varargin_1 = r5[3 * i28];
        r5[3 * i28] = std::pow(e_varargin_1, 2.0);
        f_varargin_1 = r5[3 * i28 + 1];
        r5[3 * i28 + 1] = std::pow(f_varargin_1, 2.0);
        g_varargin_1 = r5[3 * i28 + 2];
        r5[3 * i28 + 2] = std::pow(g_varargin_1, 2.0);
    }
    if (r5.size(1) == 0) {
        b_x.set_size(1, 0);
    } else {
        int i29;
        b_x.set_size(1, r5.size(1));
        i29 = r5.size(1);
        for (int k_k{0}; k_k < i29; k_k++) {
            b_x[k_k] = r5[3 * k_k];
            b_x[k_k] = b_x[k_k] + r5[3 * k_k + 1];
            b_x[k_k] = b_x[k_k] + r5[3 * k_k + 2];
        }
    }
    i30 = b_x.size(1);
    for (int l_k{0}; l_k < i30; l_k++) {
        b_x[l_k] = std::sqrt(b_x[l_k]);
    }
    c_x.set_size(1, b_x.size(1));
    t_loop_ub = b_x.size(1);
    for (int i31{0}; i31 < t_loop_ub; i31++) {
        c_x[i31] = (b_x[i31] / b_vmax > ctx_cfg_ZeroStartVelLimit);
    }
    coder::c_eml_find(c_x, (int *)&value_data, value_size);
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
    L = LengthCurv(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                   b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                   b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                   b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                   b_CurvStruct->a_param, b_CurvStruct->b_param);
    *CurvStruct1 = *b_CurvStruct;
    CutCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct1,
                  uk[cut_index] * L);
    *CurvStruct2 = *b_CurvStruct;
    b_CutCurvStruct(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, CurvStruct2,
                    L - uk[cut_index] * L);
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
