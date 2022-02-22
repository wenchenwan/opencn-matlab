//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SmoothCurvStructs.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 08:27:14
//

// Include Files
#include "SmoothCurvStructs.h"
#include "CalcTransition.h"
#include "CutCurvStruct.h"
#include "CutZeroEnd.h"
#include "CutZeroStart.h"
#include "EvalCurvStruct.h"
#include "EvalCurvStruct_data.h"
#include "EvalCurvStruct_types.h"
#include "EvalCurvStruct_types1.h"
#include "EvalCurvStruct_types2.h"
#include "GetCurvMaxFeedrate.h"
#include "LengthCurv.h"
#include "bsxfun.h"
#include "colon.h"
#include "find.h"
#include "minOrMax.h"
#include "queue_coder.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>
#include <stdio.h>

// Function Definitions
//
// function ctx = SmoothCurvStructs(ctx)
//
// Optimal transitions calculation between segments whith G2 continuity
//
// Arguments    : FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void SmoothCurvStructs(FeedoptContext *ctx)
{
    static const char d_message[28]{'S', 'i', 'n', 'g', 'l', 'e', ' ', 'C', 'u', 'r',
                                    'v', 'S', 't', 'r', 'u', 'c', 't', ' ', 'w', 'a',
                                    's', ' ', 'n', 'o', 't', ' ', 'Z', 'Z'};
    static const char b_message[27]{'C', 'o', 'm', 'p', 'r', 'e', 's', 's', 'i',
                                    'n', 'g', ' ', 'q', 'u', 'e', 'u', 'e', ' ',
                                    'i', 's', ' ', 'e', 'm', 'p', 't', 'y', '!'};
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> at;
    ::coder::array<double, 2U> b_c;
    ::coder::array<double, 2U> b_d1uk;
    ::coder::array<double, 2U> b_r1D;
    ::coder::array<double, 2U> b_uk;
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
    ::coder::array<bool, 2U> b_max_at;
    ::coder::array<bool, 2U> b_max_jt;
    ::coder::array<bool, 2U> b_x;
    CurvStruct CurvStruct1;
    CurvStruct CurvStruct1_C;
    CurvStruct CurvStruct2_C;
    CurvStruct CurvStruct3_C;
    CurvStruct CurvStruct_T;
    CurvStruct NextCurv;
    CurvStruct b_CurvStruct2_C;
    CurvStruct b_ctx;
    CurvStruct expl_temp;
    double a__1[3];
    double r1D[3];
    int cut_index_vel_size[2];
    int cut_index_acc_data;
    int cut_index_jerk_data;
    int cut_index_vel_data;
    char c_message[28];
    char message[27];
    TransitionResult status;
    // 'SmoothCurvStructs:4' if ctx.q_compress.isempty()
    if (!ctx->q_compress.isempty()) {
        unsigned int Ncrv;
        unsigned int k;
        // 'SmoothCurvStructs:8' if coder.target('rtw')
        // 'SmoothCurvStructs:9' NextCurv = ctx.q_compress.get(1);
        ctx->q_compress.get(static_cast<double>(1.0), &b_ctx);
        //  to satisfy the coder
        // 'SmoothCurvStructs:11' Ncrv = ctx.q_compress.size;
        Ncrv = ctx->q_compress.size();
        // 'SmoothCurvStructs:13' DebugLog(DebugCfg.Validate, 'Smoothing...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Smoothing...\n");
            fflush(stdout);
        }
        // 'SmoothCurvStructs:14' DebugLog(DebugCfg.OptimProgress, 'Smoothing...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Smoothing...\n");
            fflush(stdout);
        }
        // 'SmoothCurvStructs:16' k = 1;
        k = 1U;
        // 'SmoothCurvStructs:18' if Ncrv > 1
        if (Ncrv > 1U) {
            // 'SmoothCurvStructs:19' CurvStruct1 = ctx.q_compress.get(k);
            ctx->q_compress.get(static_cast<double>(1.0), &CurvStruct1);
            // 'SmoothCurvStructs:20' while k < Ncrv
            while (k < Ncrv) {
                // 'SmoothCurvStructs:21' NextCurv = ctx.q_compress.get(k+1);
                ctx->q_compress.get(static_cast<double>(k) + 1.0, &NextCurv);
                // 'SmoothCurvStructs:22' if CurvStruct1.zspdmode == ZSpdMode.NN &&
                // NextCurv.zspdmode == ZSpdMode.NN
                if ((CurvStruct1.zspdmode == ZSpdMode_NN) && (NextCurv.zspdmode == ZSpdMode_NN)) {
                    // 'SmoothCurvStructs:23' [CurvStruct1_C, CurvStruct_T, CurvStruct2_C, status] =
                    // ... 'SmoothCurvStructs:24'                 CalcTransition(ctx, CurvStruct1,
                    // NextCurv);
                    b_CalcTransition(&ctx->q_splines, ctx->cfg.CutOff, ctx->cfg.ColTolCos,
                                     ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &CurvStruct1,
                                     &NextCurv, &CurvStruct1_C, &CurvStruct_T, &CurvStruct2_C,
                                     &status);
                    // 'SmoothCurvStructs:26' if status == TransitionResult.Ok
                    if (status == TransitionResult_Ok) {
                        // 'SmoothCurvStructs:27' ctx.q_smooth.push(CurvStruct1_C);
                        ctx->q_smooth.push(&CurvStruct1_C);
                        // 'SmoothCurvStructs:28' ctx.q_smooth.push(CurvStruct_T);
                        ctx->q_smooth.push(&CurvStruct_T);
                        // 'SmoothCurvStructs:29' CurvStruct1 = CurvStruct2_C;
                        CurvStruct1 = CurvStruct2_C;
                    } else if (status == TransitionResult_Collinear) {
                        // 'SmoothCurvStructs:30' elseif status == TransitionResult.Collinear
                        // 'SmoothCurvStructs:31' ctx.q_smooth.push(CurvStruct1);
                        ctx->q_smooth.push(&CurvStruct1);
                        // 'SmoothCurvStructs:32' CurvStruct1 = NextCurv;
                        CurvStruct1 = NextCurv;
                    } else {
                        // 'SmoothCurvStructs:33' else
                        // 'SmoothCurvStructs:34' CurvStruct1.zspdmode = ZSpdMode.NZ;
                        CurvStruct1.zspdmode = ZSpdMode_NZ;
                        // 'SmoothCurvStructs:35' NextCurv.zspdmode = ZSpdMode.ZN;
                        NextCurv.zspdmode = ZSpdMode_ZN;
                        // 'SmoothCurvStructs:36' CurvStruct2 = NextCurv;
                        //                  SaveTransition;
                        //                  If the transition fails, force a zero-stop
                        // 'SmoothCurvStructs:39' [CurvStruct1_C, CurvStruct2_C] = CutZeroEnd(ctx,
                        // CurvStruct1, k);
                        CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                   ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                   ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                   ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &CurvStruct1,
                                   static_cast<double>(k), &CurvStruct1_C, &CurvStruct2_C);
                        // 'SmoothCurvStructs:40' [CurvStruct3_C, CurvStruct4_C] = CutZeroStart(ctx,
                        // NextCurv, k);
                        CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                     ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                     ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                     ctx->cfg.DebugCutZero, ctx->cfg.GaussLegendreX,
                                     ctx->cfg.GaussLegendreW, &NextCurv, static_cast<double>(k),
                                     &CurvStruct3_C, &CurvStruct1);
                        // 'SmoothCurvStructs:41' ctx.q_smooth.push(CurvStruct1_C);
                        ctx->q_smooth.push(&CurvStruct1_C);
                        // 'SmoothCurvStructs:42' ctx.q_smooth.push(CurvStruct2_C);
                        ctx->q_smooth.push(&CurvStruct2_C);
                        // 'SmoothCurvStructs:43' ctx.q_smooth.push(CurvStruct3_C);
                        ctx->q_smooth.push(&CurvStruct3_C);
                        // 'SmoothCurvStructs:44' CurvStruct1 = CurvStruct4_C;
                        // 'SmoothCurvStructs:46' ctx.forced_stop = ctx.forced_stop + 1;
                        ctx->forced_stop++;
                    }
                    // 'SmoothCurvStructs:48' k = k + 1;
                    k++;
                } else {
                    // 'SmoothCurvStructs:49' else
                    // 'SmoothCurvStructs:51' if (CurvStruct1.zspdmode == ZSpdMode.NZ ||
                    // CurvStruct1.zspdmode == ZSpdMode.ZZ) ... 'SmoothCurvStructs:52' &&
                    // (NextCurv.zspdmode == ZSpdMode.ZN || NextCurv.zspdmode == ZSpdMode.ZZ)
                    if (((CurvStruct1.zspdmode == ZSpdMode_NZ) ||
                         (CurvStruct1.zspdmode == ZSpdMode_ZZ)) &&
                        ((NextCurv.zspdmode == ZSpdMode_ZN) ||
                         (NextCurv.zspdmode == ZSpdMode_ZZ))) {
                        // 'SmoothCurvStructs:53' ctx.programmed_stop = ctx.programmed_stop + 1;
                        ctx->programmed_stop++;
                    }
                    // 'SmoothCurvStructs:56' ctx.q_smooth.push(CurvStruct1);
                    ctx->q_smooth.push(&CurvStruct1);
                    // 'SmoothCurvStructs:57' CurvStruct1 = NextCurv;
                    CurvStruct1 = NextCurv;
                    // 'SmoothCurvStructs:58' k = k + 1;
                    k++;
                }
            }
            // 'SmoothCurvStructs:62' ctx.q_smooth.push(CurvStruct1);
            ctx->q_smooth.push(&CurvStruct1);
        } else if (static_cast<int>(Ncrv) == 1) {
            // 'SmoothCurvStructs:65' elseif Ncrv==1
            // 'SmoothCurvStructs:66' CurvStruct1 = ctx.q_compress.get(1);
            ctx->q_compress.get(static_cast<double>(1.0), &CurvStruct1);
            // 'SmoothCurvStructs:67' if CurvStruct1.zspdmode == ZSpdMode.ZZ
            if (CurvStruct1.zspdmode == ZSpdMode_ZZ) {
                double L;
                double b_ex;
                double b_vmax;
                double ex;
                double ex_tmp;
                double jps;
                double tmax;
                double z1_idx_1;
                double z1_idx_2;
                unsigned long N;
                unsigned long b_k;
                int b_loop_ub;
                int b_m;
                int b_scalarLB;
                int b_vectorUB;
                int c_ex;
                int c_loop_ub;
                int c_scalarLB;
                int c_vectorUB;
                int cut_index;
                int d_loop_ub;
                int e_loop_ub;
                int e_scalarLB;
                int e_vectorUB;
                int f_loop_ub;
                int g_loop_ub;
                int h_loop_ub;
                int i11;
                int i31;
                int i4;
                int i6;
                int i7;
                int l_k;
                int l_loop_ub;
                int m;
                int o_loop_ub;
                int p_loop_ub;
                int q_loop_ub;
                int r_loop_ub;
                int s_loop_ub;
                int scalarLB;
                int t_loop_ub;
                int vectorUB;
                bool exitg1;
                // 'SmoothCurvStructs:68' [CurvStruct1_C, CurvStruct2_C] = CutZeroStart(ctx,
                // CurvStruct1, 1);
                b_CutZeroStart(
                    &ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax, ctx->cfg.jmax,
                    ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit, ctx->cfg.ZeroStartJerkLimit,
                    ctx->cfg.ZeroStartVelLimit, ctx->cfg.DebugCutZero, ctx->cfg.GaussLegendreX,
                    ctx->cfg.GaussLegendreW, &CurvStruct1, &CurvStruct1_C, &CurvStruct2_C);
                // 'SmoothCurvStructs:69' [CurvStruct2_C, CurvStruct3_C] = CutZeroEnd(ctx,
                // CurvStruct2_C, 1); 'CutZeroEnd:2' cfg=ctx.cfg; 'CutZeroEnd:3' [~, r1D] =
                // EvalCurvStruct(ctx, CurvStruct, 0);
                b_EvalCurvStruct(&ctx->q_splines, &CurvStruct2_C, a__1, r1D);
                // 'CutZeroEnd:4' jps = min(cfg.jmax) / max(abs(r1D));
                z1_idx_1 = std::abs(r1D[1]);
                z1_idx_2 = std::abs(r1D[2]);
                // 'CutZeroEnd:6' dt = cfg.dt;
                // 'CutZeroEnd:7' tmax = ceil((6/jps)^(1/3)/dt)*dt;
                ex = ctx->cfg.jmax[0];
                ex_tmp = std::abs(r1D[0]);
                b_ex = ex_tmp;
                if (ex > ctx->cfg.jmax[1]) {
                    ex = ctx->cfg.jmax[1];
                }
                if (ex_tmp < z1_idx_1) {
                    b_ex = z1_idx_1;
                }
                if (ex > ctx->cfg.jmax[2]) {
                    ex = ctx->cfg.jmax[2];
                }
                if (b_ex < z1_idx_2) {
                    b_ex = z1_idx_2;
                }
                tmax = std::ceil(std::pow(6.0 / (ex / b_ex), 0.33333333333333331) / ctx->cfg.dt) *
                       ctx->cfg.dt;
                // 'CutZeroEnd:8' jps = 6/tmax^3;
                jps = 6.0 / std::pow(tmax, 3.0);
                // 'CutZeroEnd:9' t = tmax:-dt:0;
                if ((-ctx->cfg.dt == 0.0) || ((tmax < 0.0) && (-ctx->cfg.dt < 0.0)) ||
                    ((0.0 < tmax) && (-ctx->cfg.dt > 0.0))) {
                    t.set_size(1, 0);
                } else if ((std::floor(tmax) == tmax) &&
                           (std::floor(-ctx->cfg.dt) == -ctx->cfg.dt)) {
                    double d;
                    int loop_ub;
                    d = -ctx->cfg.dt;
                    loop_ub = static_cast<int>(std::floor((0.0 - tmax) / d));
                    t.set_size(1, loop_ub + 1);
                    for (int i2{0}; i2 <= loop_ub; i2++) {
                        t[i2] = tmax + d * static_cast<double>(i2);
                    }
                } else {
                    coder::b_eml_float_colon(tmax, -ctx->cfg.dt, t);
                }
                // 'CutZeroEnd:11' uk = jps*t.^3/6;
                r.set_size(1, t.size(1));
                b_loop_ub = t.size(1);
                for (int i3{0}; i3 < b_loop_ub; i3++) {
                    double varargin_1;
                    varargin_1 = t[i3];
                    r[i3] = std::pow(varargin_1, 3.0);
                }
                uk.set_size(1, r.size(1));
                c_loop_ub = r.size(1);
                scalarLB = (r.size(1) / 2) << 1;
                vectorUB = scalarLB - 2;
                for (i4 = 0; i4 <= vectorUB; i4 += 2) {
                    __m128d r1;
                    r1 = _mm_loadu_pd(&r[i4]);
                    _mm_storeu_pd(&uk[i4],
                                  _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r1), _mm_set1_pd(6.0)));
                }
                for (i4 = scalarLB; i4 < c_loop_ub; i4++) {
                    uk[i4] = jps * r[i4] / 6.0;
                }
                // 'CutZeroEnd:12' d1uk = jps*t.^2/2;
                r.set_size(1, t.size(1));
                d_loop_ub = t.size(1);
                for (int i5{0}; i5 < d_loop_ub; i5++) {
                    double b_varargin_1;
                    b_varargin_1 = t[i5];
                    r[i5] = std::pow(b_varargin_1, 2.0);
                }
                d1uk.set_size(1, r.size(1));
                e_loop_ub = r.size(1);
                b_scalarLB = (r.size(1) / 2) << 1;
                b_vectorUB = b_scalarLB - 2;
                for (i6 = 0; i6 <= b_vectorUB; i6 += 2) {
                    __m128d r2;
                    r2 = _mm_loadu_pd(&r[i6]);
                    _mm_storeu_pd(&d1uk[i6],
                                  _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r2), _mm_set1_pd(2.0)));
                }
                for (i6 = b_scalarLB; i6 < e_loop_ub; i6++) {
                    d1uk[i6] = jps * r[i6] / 2.0;
                }
                // 'CutZeroEnd:13' d2uk = jps*t;
                d2uk.set_size(1, t.size(1));
                f_loop_ub = t.size(1);
                c_scalarLB = (t.size(1) / 2) << 1;
                c_vectorUB = c_scalarLB - 2;
                for (i7 = 0; i7 <= c_vectorUB; i7 += 2) {
                    __m128d r3;
                    r3 = _mm_loadu_pd(&t[i7]);
                    _mm_storeu_pd(&d2uk[i7], _mm_mul_pd(_mm_set1_pd(jps), r3));
                }
                for (i7 = c_scalarLB; i7 < f_loop_ub; i7++) {
                    d2uk[i7] = jps * t[i7];
                }
                // 'CutZeroEnd:14' d3uk = jps;
                // 'CutZeroEnd:16' [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, uk);
                b_uk.set_size(1, uk.size(1));
                g_loop_ub = uk.size(1) - 1;
                for (int i8{0}; i8 <= g_loop_ub; i8++) {
                    b_uk[i8] = uk[i8];
                }
                b_EvalCurvStruct(&ctx->q_splines, &CurvStruct2_C, b_uk, a__2, b_r1D, r2D, r3D);
                // 'CutZeroEnd:18' r3dt = bsxfun(@times, r3D, d1uk.^3) + 3*bsxfun(@times, r2D,
                // d1uk.*d2uk) + bsxfun(@times, r1D, d3uk); 'CutZeroEnd:19' r2dt = bsxfun(@times,
                // r2D, d1uk.^2) + bsxfun(@times, r1D, d2uk); 'CutZeroEnd:20' r1dt = bsxfun(@times,
                // r1D, d1uk); 'CutZeroEnd:22' vmax = CurvStruct.FeedRate;
                b_vmax = CurvStruct2_C.FeedRate;
                // 'CutZeroEnd:23' N = max(k0 - uint64(ctx.cfg.NHorz) + 1, 1);
                N = coder::internal::maximum2(2UL - ctx->cfg.NHorz);
                // 'CutZeroEnd:24' for k = k0:-1:N
                b_k = 1UL;
                exitg1 = false;
                while ((!exitg1) && (b_k >= N)) {
                    double y;
                    // 'CutZeroEnd:25' TmpCurv = ctx.q_gcode.get(k);
                    ctx->q_gcode.get(b_k, &expl_temp);
                    // 'CutZeroEnd:27' vmax_tmp = GetCurvMaxFeedrate(ctx, TmpCurv);
                    y = GetCurvMaxFeedrate(
                        &ctx->q_splines, ctx->cfg.amax, ctx->cfg.jmax, expl_temp.Type, expl_temp.P0,
                        expl_temp.P1, expl_temp.CorrectedHelixCenter, expl_temp.evec,
                        expl_temp.theta, expl_temp.pitch, expl_temp.CoeffP5, expl_temp.sp_index,
                        expl_temp.FeedRate, expl_temp.a_param, expl_temp.b_param);
                    // 'CutZeroEnd:28' vmax = min(vmax, vmax_tmp);
                    b_vmax = std::fmin(b_vmax, y);
                    // 'CutZeroEnd:29' if TmpCurv.zspdmode == ZSpdMode.ZN
                    if (expl_temp.zspdmode == ZSpdMode_ZN) {
                        exitg1 = true;
                    } else {
                        b_k--;
                    }
                }
                // 'CutZeroEnd:34' jt = abs(bsxfun(@rdivide, r3dt.', cfg.jmax));
                c.set_size(3, b_r1D.size(1));
                if (b_r1D.size(1) != 0) {
                    int acoef;
                    int i9;
                    acoef = (b_r1D.size(1) != 1);
                    i9 = b_r1D.size(1) - 1;
                    for (int c_k{0}; c_k <= i9; c_k++) {
                        __m128d r5;
                        int varargin_2;
                        varargin_2 = acoef * c_k;
                        r5 = _mm_loadu_pd(&b_r1D[3 * varargin_2]);
                        _mm_storeu_pd(&c[3 * c_k], _mm_mul_pd(r5, _mm_set1_pd(jps)));
                        c[3 * c_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
                    }
                }
                r.set_size(1, d1uk.size(1));
                h_loop_ub = d1uk.size(1);
                for (int i10{0}; i10 < h_loop_ub; i10++) {
                    double c_varargin_1;
                    c_varargin_1 = d1uk[i10];
                    r[i10] = std::pow(c_varargin_1, 3.0);
                }
                coder::bsxfun(r3D, r, r4);
                if (d1uk.size(1) == d2uk.size(1)) {
                    int d_scalarLB;
                    int d_vectorUB;
                    int i12;
                    int i_loop_ub;
                    b_d1uk.set_size(1, d1uk.size(1));
                    i_loop_ub = d1uk.size(1);
                    d_scalarLB = (d1uk.size(1) / 2) << 1;
                    d_vectorUB = d_scalarLB - 2;
                    for (i12 = 0; i12 <= d_vectorUB; i12 += 2) {
                        __m128d r7;
                        __m128d r8;
                        r7 = _mm_loadu_pd(&d1uk[i12]);
                        r8 = _mm_loadu_pd(&d2uk[i12]);
                        _mm_storeu_pd(&b_d1uk[i12], _mm_mul_pd(r7, r8));
                    }
                    for (i12 = d_scalarLB; i12 < i_loop_ub; i12++) {
                        b_d1uk[i12] = d1uk[i12] * d2uk[i12];
                    }
                    coder::bsxfun(r2D, b_d1uk, r6);
                } else {
                    b_binary_expand_op(r6, r2D, d1uk, d2uk);
                }
                if (r4.size(1) == 1) {
                    i11 = r6.size(1);
                } else {
                    i11 = r4.size(1);
                }
                if ((r4.size(1) == r6.size(1)) && (i11 == c.size(1))) {
                    int j_loop_ub;
                    a.set_size(r4.size(1), 3);
                    j_loop_ub = r4.size(1);
                    for (int i13{0}; i13 < 3; i13++) {
                        for (int i14{0}; i14 < j_loop_ub; i14++) {
                            a[i14 + a.size(0) * i13] =
                                (r4[i13 + 3 * i14] + 3.0 * r6[i13 + 3 * i14]) + c[i13 + 3 * i14];
                        }
                    }
                } else {
                    binary_expand_op(a, r4, r6, c);
                }
                b_c.set_size(a.size(0), 3);
                if (a.size(0) != 0) {
                    int b_acoef;
                    b_acoef = (a.size(0) != 1);
                    for (int d_k{0}; d_k < 3; d_k++) {
                        int i15;
                        i15 = b_c.size(0) - 1;
                        for (int e_k{0}; e_k <= i15; e_k++) {
                            b_c[e_k + b_c.size(0) * d_k] =
                                a[b_acoef * e_k + a.size(0) * d_k] / ctx->cfg.jmax[d_k];
                        }
                    }
                }
                jt.set_size(b_c.size(0), 3);
                if (b_c.size(0) != 0) {
                    int k_loop_ub;
                    int m_loop_ub;
                    at.set_size(b_c.size(0), 3);
                    k_loop_ub = b_c.size(0);
                    for (int i16{0}; i16 < 3; i16++) {
                        for (int i18{0}; i18 < k_loop_ub; i18++) {
                            at[i18 + at.size(0) * i16] = jt[i18 + jt.size(0) * i16];
                        }
                    }
                    for (int f_k{0}; f_k < 3; f_k++) {
                        int i19;
                        i19 = at.size(0);
                        for (int g_k{0}; g_k < i19; g_k++) {
                            at[g_k + at.size(0) * f_k] = std::abs(b_c[g_k + b_c.size(0) * f_k]);
                        }
                    }
                    jt.set_size(at.size(0), 3);
                    m_loop_ub = at.size(0);
                    for (int i20{0}; i20 < 3; i20++) {
                        for (int i21{0}; i21 < m_loop_ub; i21++) {
                            jt[i21 + jt.size(0) * i20] = at[i21 + at.size(0) * i20];
                        }
                    }
                }
                // 'CutZeroEnd:35' at = abs(bsxfun(@rdivide, r2dt.', cfg.amax));
                r.set_size(1, d1uk.size(1));
                l_loop_ub = d1uk.size(1);
                for (int i17{0}; i17 < l_loop_ub; i17++) {
                    double d_varargin_1;
                    d_varargin_1 = d1uk[i17];
                    r[i17] = std::pow(d_varargin_1, 2.0);
                }
                coder::bsxfun(r2D, r, r4);
                coder::bsxfun(b_r1D, d2uk, r6);
                if (r4.size(1) == r6.size(1)) {
                    int n_loop_ub;
                    a.set_size(r4.size(1), 3);
                    n_loop_ub = r4.size(1);
                    for (int i22{0}; i22 < 3; i22++) {
                        for (int i23{0}; i23 < n_loop_ub; i23++) {
                            a[i23 + a.size(0) * i22] = r4[i22 + 3 * i23] + r6[i22 + 3 * i23];
                        }
                    }
                } else {
                    b_binary_expand_op(a, r4, r6);
                }
                b_c.set_size(a.size(0), 3);
                if (a.size(0) != 0) {
                    int c_acoef;
                    c_acoef = (a.size(0) != 1);
                    for (int h_k{0}; h_k < 3; h_k++) {
                        int i24;
                        i24 = b_c.size(0) - 1;
                        for (int j_k{0}; j_k <= i24; j_k++) {
                            b_c[j_k + b_c.size(0) * h_k] =
                                a[c_acoef * j_k + a.size(0) * h_k] / ctx->cfg.amax[h_k];
                        }
                    }
                }
                at.set_size(b_c.size(0), 3);
                if (b_c.size(0) != 0) {
                    for (int i_k{0}; i_k < 3; i_k++) {
                        int i25;
                        i25 = at.size(0);
                        for (int k_k{0}; k_k < i25; k_k++) {
                            at[k_k + at.size(0) * i_k] = std::abs(b_c[k_k + b_c.size(0) * i_k]);
                        }
                    }
                }
                // 'CutZeroEnd:36' norm_vt = mysqrt(sum(r1dt.^2, 1))/vmax;
                // 'mysqrt:3' y = sqrt(x);
                // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                sqrt_calls++;
                // 'CutZeroEnd:37' norm_vt = norm_vt.';
                // 'CutZeroEnd:39' max_jt = max(jt, [], 2);
                m = jt.size(0) - 1;
                max_jt.set_size(jt.size(0));
                if (jt.size(0) >= 1) {
                    for (int b_i{0}; b_i <= m; b_i++) {
                        max_jt[b_i] = jt[b_i];
                    }
                    for (int j{0}; j < 2; j++) {
                        for (int c_i{0}; c_i <= m; c_i++) {
                            double d1;
                            d1 = jt[c_i + jt.size(0) * (j + 1)];
                            if (max_jt[c_i] < d1) {
                                max_jt[c_i] = d1;
                            }
                        }
                    }
                }
                // 'CutZeroEnd:40' max_at = max(at, [], 2);
                b_m = at.size(0) - 1;
                max_at.set_size(at.size(0));
                if (at.size(0) >= 1) {
                    for (int d_i{0}; d_i <= b_m; d_i++) {
                        max_at[d_i] = at[d_i];
                    }
                    for (int b_j{0}; b_j < 2; b_j++) {
                        for (int e_i{0}; e_i <= b_m; e_i++) {
                            double d2;
                            d2 = at[e_i + at.size(0) * (b_j + 1)];
                            if (max_at[e_i] < d2) {
                                max_at[e_i] = d2;
                            }
                        }
                    }
                }
                // 'CutZeroEnd:42' N = length(max_at);
                // 'CutZeroEnd:43' cut_index_jerk = orelse(find(max_jt.' > cfg.ZeroStartJerkLimit,
                // 1, 'last'), 1);
                b_max_jt.set_size(1, max_jt.size(0));
                o_loop_ub = max_jt.size(0);
                for (int i26{0}; i26 < o_loop_ub; i26++) {
                    b_max_jt[i26] = (max_jt[i26] > ctx->cfg.ZeroStartJerkLimit);
                }
                coder::c_eml_find(b_max_jt, (int *)&cut_index_vel_data, cut_index_vel_size);
                p_loop_ub = cut_index_vel_size[1];
                for (int i27{0}; i27 < p_loop_ub; i27++) {
                    cut_index_jerk_data = cut_index_vel_data;
                }
                // 'orelse:2' if isempty(value)
                if (cut_index_vel_size[1] == 0) {
                    // 'orelse:3' v = elsevalue;
                    cut_index_jerk_data = 1;
                } else {
                    // 'orelse:4' else
                    // 'orelse:5' v = value;
                }
                // 'CutZeroEnd:44' cut_index_acc = orelse(find(max_at.' > cfg.ZeroStartAccLimit, 1,
                // 'last'), 1);
                b_max_at.set_size(1, max_at.size(0));
                q_loop_ub = max_at.size(0);
                for (int i28{0}; i28 < q_loop_ub; i28++) {
                    b_max_at[i28] = (max_at[i28] > ctx->cfg.ZeroStartAccLimit);
                }
                coder::c_eml_find(b_max_at, (int *)&cut_index_vel_data, cut_index_vel_size);
                r_loop_ub = cut_index_vel_size[1];
                for (int i29{0}; i29 < r_loop_ub; i29++) {
                    cut_index_acc_data = cut_index_vel_data;
                }
                // 'orelse:2' if isempty(value)
                if (cut_index_vel_size[1] == 0) {
                    // 'orelse:3' v = elsevalue;
                    cut_index_acc_data = 1;
                } else {
                    // 'orelse:4' else
                    // 'orelse:5' v = value;
                }
                // 'CutZeroEnd:45' cut_index_vel = orelse(find(norm_vt.' > cfg.ZeroStartVelLimit, 1,
                // 'last'), 1);
                coder::bsxfun(b_r1D, d1uk, r4);
                r4.set_size(3, r4.size(1));
                s_loop_ub = r4.size(1);
                for (int i30{0}; i30 < s_loop_ub; i30++) {
                    double e_varargin_1;
                    double f_varargin_1;
                    double g_varargin_1;
                    e_varargin_1 = r4[3 * i30];
                    r4[3 * i30] = std::pow(e_varargin_1, 2.0);
                    f_varargin_1 = r4[3 * i30 + 1];
                    r4[3 * i30 + 1] = std::pow(f_varargin_1, 2.0);
                    g_varargin_1 = r4[3 * i30 + 2];
                    r4[3 * i30 + 2] = std::pow(g_varargin_1, 2.0);
                }
                coder::sum(r4, x);
                i31 = x.size(1);
                e_scalarLB = (x.size(1) / 2) << 1;
                e_vectorUB = e_scalarLB - 2;
                for (l_k = 0; l_k <= e_vectorUB; l_k += 2) {
                    __m128d r9;
                    r9 = _mm_loadu_pd(&x[l_k]);
                    _mm_storeu_pd(&x[l_k], _mm_sqrt_pd(r9));
                }
                for (l_k = e_scalarLB; l_k < i31; l_k++) {
                    x[l_k] = std::sqrt(x[l_k]);
                }
                b_x.set_size(1, x.size(1));
                t_loop_ub = x.size(1);
                for (int i32{0}; i32 < t_loop_ub; i32++) {
                    b_x[i32] = (x[i32] / b_vmax > ctx->cfg.ZeroStartVelLimit);
                }
                coder::c_eml_find(b_x, (int *)&cut_index_vel_data, cut_index_vel_size);
                // 'orelse:2' if isempty(value)
                if (cut_index_vel_size[1] == 0) {
                    // 'orelse:3' v = elsevalue;
                    cut_index_vel_data = 1;
                } else {
                    // 'orelse:4' else
                    // 'orelse:5' v = value;
                }
                // 'CutZeroEnd:47' cut_index = max([cut_index_acc, cut_index_jerk, cut_index_vel]);
                // 'CutZeroEnd:48' cut_from_end = int32(max(2, N - cut_index + 1));
                // 'CutZeroEnd:49' cut_index = N - cut_from_end;
                c_ex = cut_index_acc_data;
                if (cut_index_acc_data < cut_index_jerk_data) {
                    c_ex = cut_index_jerk_data;
                }
                if (c_ex < cut_index_vel_data) {
                    c_ex = cut_index_vel_data;
                }
                cut_index = (max_at.size(0) -
                             static_cast<int>(std::fmax(2.0, (static_cast<double>(max_at.size(0)) -
                                                              static_cast<double>(c_ex)) +
                                                                 1.0))) -
                            1;
                // 'CutZeroEnd:51' t_cut = t(cut_index);
                // 'CutZeroEnd:52' actual_jps = 6/t_cut.^3;
                //      actual_jps = jps;
                //      cut_index = N + 1 - cut_index;
                // 'CutZeroEnd:56' u_cut = uk(cut_index);
                // 'CutZeroEnd:57' max_iter = int32(N - cut_index + 1);
                // 'CutZeroEnd:59' L = LengthCurv(ctx, CurvStruct, 0, 1);
                L = LengthCurv(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                               &CurvStruct2_C);
                // 'CutZeroEnd:61' CurvStruct1 = CutCurvStruct(ctx, CurvStruct, 0, u_cut*L);
                b_CurvStruct2_C = CurvStruct2_C;
                CutCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                              &b_CurvStruct2_C, uk[cut_index] * L);
                // 'CutZeroEnd:63' CurvStruct2 = CutCurvStruct(ctx, CurvStruct, L - u_cut*L, 0);
                CurvStruct3_C = CurvStruct2_C;
                b_CutCurvStruct(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                &CurvStruct3_C, L - uk[cut_index] * L);
                // 'CutZeroEnd:64' CurvStruct2.ConstJerkMaxIterations = max_iter;
                CurvStruct3_C.ConstJerkMaxIterations = max_at.size(0) - cut_index;
                // 'CutZeroEnd:65' CurvStruct2.UseConstJerk = true;
                CurvStruct3_C.UseConstJerk = true;
                // 'CutZeroEnd:66' CurvStruct2.ConstJerk = actual_jps;
                CurvStruct3_C.ConstJerk = 6.0 / std::pow(t[cut_index], 3.0);
                // 'CutZeroEnd:68' CurvStruct1.zspdmode = ZSpdMode.NN;
                b_CurvStruct2_C.zspdmode = ZSpdMode_NN;
                // 'CutZeroEnd:69' CurvStruct2.zspdmode = ZSpdMode.NZ;
                CurvStruct3_C.zspdmode = ZSpdMode_NZ;
                // 'CutZeroEnd:71' CurvStruct1.gcode_source_line = CurvStruct.gcode_source_line;
                b_CurvStruct2_C.gcode_source_line = CurvStruct2_C.gcode_source_line;
                // 'CutZeroEnd:72' CurvStruct2.gcode_source_line = CurvStruct.gcode_source_line;
                CurvStruct3_C.gcode_source_line = CurvStruct2_C.gcode_source_line;
                // 'SmoothCurvStructs:70' ctx.q_smooth.push(CurvStruct1_C);
                ctx->q_smooth.push(&CurvStruct1_C);
                // 'SmoothCurvStructs:71' ctx.q_smooth.push(CurvStruct2_C);
                ctx->q_smooth.push(&b_CurvStruct2_C);
                // 'SmoothCurvStructs:72' ctx.q_smooth.push(CurvStruct3_C);
                ctx->q_smooth.push(&CurvStruct3_C);
            } else {
                // 'SmoothCurvStructs:73' else
                // 'SmoothCurvStructs:74' c_assert(false, 'Single CurvStruct was not ZZ');
                // 'c_assert:2' if coder.target('rtw')
                // 'c_assert:3' if ~condition
                // 'c_assert:4' coder.ceval('c_assert_', message);
                for (int i1{0}; i1 < 28; i1++) {
                    c_message[i1] = d_message[i1];
                }
                c_assert_(&c_message[0]);
                // 'c_assert:6' value = condition;
            }
        } else {
            // 'SmoothCurvStructs:76' else
            // 'SmoothCurvStructs:77' c_assert(false, 'Compressing queue is empty!');
            // 'c_assert:2' if coder.target('rtw')
            // 'c_assert:3' if ~condition
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i{0}; i < 27; i++) {
                message[i] = b_message[i];
            }
            c_assert_(&message[0]);
            // 'c_assert:6' value = condition;
        }
    }
}

} // namespace ocn

//
// File trailer for SmoothCurvStructs.cpp
//
// [EOF]
//
