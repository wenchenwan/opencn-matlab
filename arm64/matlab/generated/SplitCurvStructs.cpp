//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplitCurvStructs.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 01-Mar-2022 11:01:39
//

// Include Files
#include "SplitCurvStructs.h"
#include "LengthCurv.h"
#include "SplineLengthFindU_up.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// function ctx = SplitCurvStructs(ctx)
//
// Arguments    : const FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void SplitCurvStructs(const FeedoptContext *ctx)
{
    CurvStruct CurvStrct;
    CurvStruct b_ctx;
    // 'SplitCurvStructs:3' if ctx.q_smooth.isempty()
    if (!ctx->q_smooth.isempty()) {
        unsigned int N;
        int i;
        // 'SplitCurvStructs:7' N = ctx.q_smooth.size;
        N = ctx->q_smooth.size();
        // 'SplitCurvStructs:9' DebugLog(DebugCfg.Validate, 'Splitting...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Splitting...\n");
            fflush(stdout);
        }
        // 'SplitCurvStructs:10' DebugLog(DebugCfg.OptimProgress, 'Splitting...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Splitting...\n");
            fflush(stdout);
        }
        // 'SplitCurvStructs:12' for k = 1:N
        i = static_cast<int>(N);
        for (int k{0}; k < i; k++) {
            // 'SplitCurvStructs:13' ctx = SplitCurvStruct(ctx, ctx.q_smooth.get(k));
            ctx->q_smooth.get(k + 1U, &CurvStrct);
            //  coder.varsize('CrvStructs', [1, 100], [0, 1]);
            //
            // 'SplitCurvStruct:4' Type  = CurvStrct.Type;
            // 'SplitCurvStruct:6' if Type~=CurveType.TransP5 && CurvStrct.UseConstJerk == 0
            if ((CurvStrct.Type != CurveType_TransP5) && (!CurvStrct.UseConstJerk)) {
                // 'SplitCurvStruct:8' if Type==CurveType.Line || Type==CurveType.Helix
                if ((CurvStrct.Type == CurveType_Line) || (CurvStrct.Type == CurveType_Helix)) {
                    double L;
                    double a;
                    double b;
                    // 'SplitCurvStruct:9' ctx = SplitLineHelix(ctx, CurvStrct);
                    // 'SplitLineHelix:3' a=Curv.a_param;
                    a = CurvStrct.a_param;
                    // 'SplitLineHelix:4' b=Curv.b_param;
                    b = CurvStrct.b_param;
                    // 'SplitLineHelix:6' L=LengthCurv(ctx, Curv, 0, 1);
                    L = LengthCurv(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                   ctx->cfg.GaussLegendreW, &CurvStrct);
                    // 'SplitLineHelix:7' L_split=ctx.cfg.LSplit;
                    // 'SplitLineHelix:9' if L<2*L_split
                    if (L < 2.0 * ctx->cfg.LSplit) {
                        // 'SplitLineHelix:10' ctx.q_split.push(Curv);
                        ctx->q_split.push(&CurvStrct);
                    } else {
                        double L_split;
                        double b_N;
                        int i1;
                        // 'SplitLineHelix:14' N = ceil(L/L_split);
                        b_N = std::ceil(L / ctx->cfg.LSplit);
                        // 'SplitLineHelix:16' L_split = L/N;
                        L_split = L / b_N;
                        // 'SplitLineHelix:18' for k = 1:N
                        i1 = static_cast<int>(b_N);
                        for (int b_k{0}; b_k < i1; b_k++) {
                            double u_tilda_0;
                            double u_tilda_0_tmp;
                            // 'SplitLineHelix:20' u_0 = (k-1)*(L_split/L);
                            // 'SplitLineHelix:21' u_1 = k*(L_split/L);
                            // 'SplitLineHelix:23' u_tilda_0 = a*u_0+b;
                            u_tilda_0_tmp = L_split / L;
                            u_tilda_0 =
                                a * (((static_cast<double>(b_k) + 1.0) - 1.0) * u_tilda_0_tmp) + b;
                            // 'SplitLineHelix:24' u_tilda_1 = a*u_1+b;
                            // 'SplitLineHelix:26' Curv.a_param = u_tilda_1 - u_tilda_0;
                            CurvStrct.a_param =
                                (a * ((static_cast<double>(b_k) + 1.0) * u_tilda_0_tmp) + b) -
                                u_tilda_0;
                            // 'SplitLineHelix:27' Curv.b_param = u_tilda_0;
                            CurvStrct.b_param = u_tilda_0;
                            // 'SplitLineHelix:29' ctx.q_split.push(Curv);
                            ctx->q_split.push(&CurvStrct);
                        }
                    }
                } else {
                    double ux_tilda;
                    // 'SplitCurvStruct:10' else
                    // 'SplitCurvStruct:11' ctx = SplitSpline(ctx, CurvStrct);
                    // 'SplitSpline:4' Spline=ctx.q_splines.get(Curv.sp_index);
                    ctx->q_splines.get(CurvStrct.sp_index, &b_ctx);
                    // 'SplitSpline:5' sp = Spline.sp;
                    // 'SplitSpline:7' L_split=ctx.cfg.LSplit;
                    // 'SplitSpline:9' a=Curv.a_param;
                    // 'SplitSpline:10' b=Curv.b_param;
                    // 'SplitSpline:11' u0_tilda = a*0+b;
                    // 'SplitSpline:12' u1_tilda = a*1+b;
                    // 'SplitSpline:14' ux_tilda  = SplineLengthFindU_up(ctx, Curv, L_split,
                    // u0_tilda);
                    ux_tilda = SplineLengthFindU_up(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                                    ctx->cfg.GaussLegendreW, CurvStrct.sp_index,
                                                    ctx->cfg.LSplit, CurvStrct.b_param);
                    // 'SplitSpline:16' if ux_tilda ~= -1
                    if (ux_tilda != -1.0) {
                        //  if spline is not too short
                        // 'SplitSpline:17' Curv.a_param = ux_tilda - u0_tilda;
                        CurvStrct.a_param = ux_tilda - CurvStrct.b_param;
                    }
                    // 'SplitSpline:19' ctx.q_split.push(Curv);
                    ctx->q_split.push(&CurvStrct);
                }
            } else {
                // 'SplitCurvStruct:14' else
                // 'SplitCurvStruct:15' ctx.q_split.push(CurvStrct);
                ctx->q_split.push(&CurvStrct);
            }
        }
    }
}

} // namespace ocn

//
// File trailer for SplitCurvStructs.cpp
//
// [EOF]
//
