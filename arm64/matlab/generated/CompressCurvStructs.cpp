//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CompressCurvStructs.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 25-Feb-2022 11:29:52
//

// Include Files
#include "CompressCurvStructs.h"
#include "CalcBspline_Lee.h"
#include "ConstrCurvStruct.h"
#include "ConstrCurvStructType.h"
#include "CutZeroEnd.h"
#include "CutZeroStart.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "SplineLengthApproxGL_tot.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// function ctx = CompressCurvStructs(ctx)
//
// We replace each sequence of small g-code segments with a B-Spline
//  of degree 3
//  A special queue is dedicated to the splines, ctx.q_splines
//
// Arguments    : const FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void CompressCurvStructs(const FeedoptContext *ctx)
{
    static const char b_message[17]{'N', 'o', 't', ' ', 'e', 'n', 'o', 'u', 'g',
                                    'h', ' ', 'p', 'o', 'i', 'n', 't', 's'};
    ::coder::array<double, 2U> pvec;
    CurvStruct C;
    CurvStruct Curv;
    CurvStruct CurvStruct1_C;
    CurvStruct CurvStruct2_C;
    CurvStruct CurvStruct3_C;
    CurvStruct SplineCurve;
    CurvStruct b_CurvStruct2_C;
    CurvStruct b_ctx;
    CurvStruct expl_temp;
    CurvStruct spline;
    double dv3[6][3];
    double avec[2][3];
    double uvec[2][3];
    double P0[3];
    double P1[3];
    double V0[3];
    double V1[3];
    double a__1[3];
    double a__2[3];
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv4[3];
    double dv5[3];
    double dv6[3];
    unsigned long t0_Bl_handle;
    int t0_Bl_degree;
    int t0_Bl_ncoeff;
    char message[17];
    // 'CompressCurvStructs:6' if ctx.q_gcode.isempty()
    if (!ctx->q_gcode.isempty()) {
        double CumulatedLength;
        double spindle_speed;
        unsigned int Ncrv;
        unsigned int spline_index;
        // 'CompressCurvStructs:10' spline_index = ctx.q_splines.size() + 1;
        spline_index = ctx->q_splines.size() + 1U;
        // 'CompressCurvStructs:12' Ncrv = ctx.q_gcode.size;
        Ncrv = ctx->q_gcode.size();
        // 'CompressCurvStructs:14' CumulatedLength = 0;
        CumulatedLength = 0.0;
        // 'CompressCurvStructs:15' Length_Threshold = ctx.cfg.LThreshold;
        //  [mm]
        // 'CompressCurvStructs:17' DebugLog(DebugCfg.Validate, 'Compressing...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Compressing...\n");
            fflush(stdout);
        }
        // 'CompressCurvStructs:18' DebugLog(DebugCfg.OptimProgress, 'Compressing...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf(1, varargin{:});
            printf("Compressing...\n");
            fflush(stdout);
        }
        // 'CompressCurvStructs:20' spindle_speed = 75000;
        spindle_speed = 75000.0;
        //  Satisfy coder
        //  -------------
        // 'CompressCurvStructs:24' if coder.target('rtw') || coder.target('mex')
        // 'CompressCurvStructs:25' pvec = zeros(3, 0);
        pvec.set_size(3, 0);
        // 'CompressCurvStructs:26' coder.varsize('pvec', [3, Inf], [0, 1]);
        // 'CompressCurvStructs:27' CurvStruct1 = ctx.q_gcode.get(1);
        ctx->q_gcode.get(static_cast<double>(1.0), &b_ctx);
        //  -------------
        //   ||...
        //              (CumulatedLength > 0 && ~CurvCollinear(ctx, ctx.q_gcode.get(k-1), Curv,
        //              ctx.cfg.Compressing.MaxCollinearityDegrees))
        // 'CompressCurvStructs:34' k = 1;
        // 'CompressCurvStructs:35' while k <= Ncrv
        for (double k{1.0}; k <= Ncrv; k++) {
            bool Collinear;
            // 'CompressCurvStructs:36' Curv = ctx.q_gcode.get(k);
            ctx->q_gcode.get(k, &Curv);
            //  If the next curve segment is too long for compressing or it is not an NN,
            //  we need to stop growing the compressing list and create the spline
            // 'CompressCurvStructs:39' Collinear = false;
            Collinear = false;
            // 'CompressCurvStructs:40' if k > 1
            if (k > 1.0) {
                double absxk;
                double scale;
                double t;
                double y;
                // 'CompressCurvStructs:41' Collinear = CurvCollinear(ctx, ctx.q_gcode.get(k-1),
                // Curv, ctx.cfg.Compressing.ColTolCos);
                ctx->q_gcode.get(k - 1.0, &expl_temp);
                // 'CurvCollinear:3' [~, V0] = EvalCurvStruct(ctx, Curv1, 1);
                b_EvalCurvStruct(&ctx->q_splines, expl_temp.Type, expl_temp.P0, expl_temp.P1,
                                 expl_temp.CorrectedHelixCenter, expl_temp.evec, expl_temp.theta,
                                 expl_temp.pitch, expl_temp.CoeffP5, expl_temp.sp_index,
                                 expl_temp.a_param, expl_temp.b_param, a__1, V0);
                // 'CurvCollinear:4' [~, V1] = EvalCurvStruct(ctx, Curv2, 0);
                b_EvalCurvStruct(&ctx->q_splines, &Curv, a__2, V1);
                // 'CurvCollinear:6' result = collinear(V0, V1, ToleranceCos);
                // 'collinear:2' if (norm(u) < eps || norm(v) < eps)
                scale = 3.3121686421112381E-170;
                absxk = std::abs(V0[0]);
                if (absxk > 3.3121686421112381E-170) {
                    y = 1.0;
                    scale = absxk;
                } else {
                    t = absxk / 3.3121686421112381E-170;
                    y = t * t;
                }
                absxk = std::abs(V0[1]);
                if (absxk > scale) {
                    t = scale / absxk;
                    y = y * t * t + 1.0;
                    scale = absxk;
                } else {
                    t = absxk / scale;
                    y += t * t;
                }
                absxk = std::abs(V0[2]);
                if (absxk > scale) {
                    t = scale / absxk;
                    y = y * t * t + 1.0;
                    scale = absxk;
                } else {
                    t = absxk / scale;
                    y += t * t;
                }
                y = scale * std::sqrt(y);
                if (y < 2.2204460492503131E-16) {
                    // 'collinear:3' value = true;
                    Collinear = true;
                } else {
                    double b_absxk;
                    double b_scale;
                    double b_t;
                    double b_y;
                    b_scale = 3.3121686421112381E-170;
                    b_absxk = std::abs(V1[0]);
                    if (b_absxk > 3.3121686421112381E-170) {
                        b_y = 1.0;
                        b_scale = b_absxk;
                    } else {
                        b_t = b_absxk / 3.3121686421112381E-170;
                        b_y = b_t * b_t;
                    }
                    b_absxk = std::abs(V1[1]);
                    if (b_absxk > b_scale) {
                        b_t = b_scale / b_absxk;
                        b_y = b_y * b_t * b_t + 1.0;
                        b_scale = b_absxk;
                    } else {
                        b_t = b_absxk / b_scale;
                        b_y += b_t * b_t;
                    }
                    b_absxk = std::abs(V1[2]);
                    if (b_absxk > b_scale) {
                        b_t = b_scale / b_absxk;
                        b_y = b_y * b_t * b_t + 1.0;
                        b_scale = b_absxk;
                    } else {
                        b_t = b_absxk / b_scale;
                        b_y += b_t * b_t;
                    }
                    b_y = b_scale * std::sqrt(b_y);
                    if (b_y < 2.2204460492503131E-16) {
                        // 'collinear:3' value = true;
                        Collinear = true;
                    } else {
                        // 'collinear:6' cos_angle = dot(u,v)/(MyNorm(u)*MyNorm(v));
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        // 'mysqrt:3' y = sqrt(x);
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        // 'mysqrt:3' y = sqrt(x);
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                        // 'collinear:7' value = cos_angle > tol_cos;
                        Collinear = (((V0[0] * V1[0] + V0[1] * V1[1]) + V0[2] * V1[2]) /
                                         (std::sqrt((std::pow(V0[0], 2.0) + std::pow(V0[1], 2.0)) +
                                                    std::pow(V0[2], 2.0)) *
                                          std::sqrt((std::pow(V1[0], 2.0) + std::pow(V1[1], 2.0)) +
                                                    std::pow(V1[2], 2.0))) >
                                     ctx->cfg.Compressing.ColTolCos);
                    }
                }
            }
            // 'CompressCurvStructs:44' if (LengthCurv(ctx, Curv, 0, 1)>=Length_Threshold) || ...
            // 'CompressCurvStructs:45'             (Curv.zspdmode~=ZSpdMode.NN) ||...
            // 'CompressCurvStructs:46'             (CumulatedLength == 0 && ~Collinear)
            if ((LengthCurv(&ctx->q_splines, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                            &Curv) >= ctx->cfg.LThreshold) ||
                (Curv.zspdmode != ZSpdMode_NN) || ((CumulatedLength == 0.0) && (!Collinear))) {
                //  If the cumulated length is zero, no compressing is on-going and we can
                //  treat the segment individually
                // 'CompressCurvStructs:50' if CumulatedLength == 0
                if (CumulatedLength == 0.0) {
                    //  If the segment is not a normal one (Nonzero, Nonzero), it needs
                    //  to be split
                    // 'CompressCurvStructs:54' if Curv.zspdmode == ZSpdMode.ZN
                    if (Curv.zspdmode == ZSpdMode_ZN) {
                        // 'CompressCurvStructs:55' [CurvStruct1_C, CurvStruct2_C] =
                        // CutZeroStart(ctx, Curv, k);
                        CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                     ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                     ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                     ctx->cfg.DebugCutZero, ctx->cfg.GaussLegendreX,
                                     ctx->cfg.GaussLegendreW, &Curv, k, &CurvStruct1_C,
                                     &CurvStruct2_C);
                        // 'CompressCurvStructs:56' ctx.q_compress.push(CurvStruct1_C);
                        ctx->q_compress.push(&CurvStruct1_C);
                        // 'CompressCurvStructs:57' ctx.q_compress.push(CurvStruct2_C);
                        ctx->q_compress.push(&CurvStruct2_C);
                    } else if (Curv.zspdmode == ZSpdMode_NZ) {
                        // 'CompressCurvStructs:58' elseif Curv.zspdmode == ZSpdMode.NZ
                        // 'CompressCurvStructs:59' [CurvStruct1_C, CurvStruct2_C] = CutZeroEnd(ctx,
                        // Curv, k);
                        CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                   ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                   ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                   ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &Curv, k,
                                   &CurvStruct1_C, &CurvStruct2_C);
                        // 'CompressCurvStructs:60' ctx.q_compress.push(CurvStruct1_C);
                        ctx->q_compress.push(&CurvStruct1_C);
                        // 'CompressCurvStructs:61' ctx.q_compress.push(CurvStruct2_C);
                        ctx->q_compress.push(&CurvStruct2_C);
                    } else if (Curv.zspdmode == ZSpdMode_ZZ) {
                        // 'CompressCurvStructs:62' elseif Curv.zspdmode == ZSpdMode.ZZ
                        // 'CompressCurvStructs:63' [CurvStruct1_C, CurvStruct2_C] =
                        // CutZeroStart(ctx, Curv, k);
                        CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                     ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                     ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                     ctx->cfg.DebugCutZero, ctx->cfg.GaussLegendreX,
                                     ctx->cfg.GaussLegendreW, &Curv, k, &CurvStruct1_C,
                                     &CurvStruct2_C);
                        // 'CompressCurvStructs:64' [CurvStruct2_C, CurvStruct3_C] = CutZeroEnd(ctx,
                        // CurvStruct2_C, k);
                        CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                   ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                   ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                   ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &CurvStruct2_C,
                                   k, &b_CurvStruct2_C, &CurvStruct3_C);
                        // 'CompressCurvStructs:65' ctx.q_compress.push(CurvStruct1_C);
                        ctx->q_compress.push(&CurvStruct1_C);
                        // 'CompressCurvStructs:66' ctx.q_compress.push(CurvStruct2_C);
                        ctx->q_compress.push(&b_CurvStruct2_C);
                        // 'CompressCurvStructs:67' ctx.q_compress.push(CurvStruct3_C);
                        ctx->q_compress.push(&CurvStruct3_C);
                        //  If the segment is normal, (Nonzero, Nonzero), it can be pushed
                        //  as-is into the output list
                    } else {
                        // 'CompressCurvStructs:71' else
                        // 'CompressCurvStructs:72' ctx.q_compress.push(Curv);
                        ctx->q_compress.push(&Curv);
                    }
                    //  If there was an on-going compression
                } else {
                    // 'CompressCurvStructs:76' else
                    //  We have more than 2 points, thus constructing a spline
                    //  is warranted
                    // 'CompressCurvStructs:79' if size(pvec, 2) > 2
                    if (pvec.size(1) > 2) {
                        int b_pvec;
                        // 'CompressCurvStructs:80' SplineCurve = ConstrCurvStructType;
                        ConstrCurvStructType(&SplineCurve);
                        // 'CompressCurvStructs:81' SplineCurve.sp=CalcBspline_Lee(ctx.cfg, pvec);
                        CalcBspline_Lee(ctx->cfg.SplineDegree, pvec, SplineCurve.sp.CoeffX,
                                        SplineCurve.sp.CoeffY, SplineCurve.sp.CoeffZ, &t0_Bl_ncoeff,
                                        SplineCurve.sp.Bl.breakpoints, &t0_Bl_handle, &t0_Bl_degree,
                                        SplineCurve.sp.knots);
                        SplineCurve.sp.Bl.ncoeff = t0_Bl_ncoeff;
                        SplineCurve.sp.Bl.handle = t0_Bl_handle;
                        SplineCurve.sp.Bl.degree = t0_Bl_degree;
                        // 'CompressCurvStructs:82' SplineCurve.sp.Ltot = 0;
                        //  satisfy coder
                        // 'CompressCurvStructs:83' SplineCurve.sp.Lk = 0;
                        //  satisfy coder
                        // 'CompressCurvStructs:84' [Ltot, Lk]    = SplineLengthApproxGL_tot(ctx,
                        // SplineCurve);
                        SplineLengthApproxGL_tot(ctx->cfg.GaussLegendreN, ctx->cfg.GaussLegendreX,
                                                 ctx->cfg.GaussLegendreW, SplineCurve.sp.CoeffX,
                                                 SplineCurve.sp.CoeffY, SplineCurve.sp.CoeffZ,
                                                 t0_Bl_handle, SplineCurve.sp.knots,
                                                 &SplineCurve.sp.Ltot, SplineCurve.sp.Lk);
                        // 'CompressCurvStructs:85' SplineCurve.sp.Ltot = Ltot;
                        // 'CompressCurvStructs:86' SplineCurve.sp.Lk   = Lk;
                        // 'CompressCurvStructs:87' ctx.q_splines.push(SplineCurve);
                        ctx->q_splines.push(&SplineCurve);
                        // 'CompressCurvStructs:88' spline = ConstrBSplineStruct(Curv.TRAFO,
                        // Curv.HSC,... 'CompressCurvStructs:89' Curv.Poff, ...
                        // 'CompressCurvStructs:90' Curv.Aoff, Curv.Uoff, ...
                        // 'CompressCurvStructs:91' Curv.Doff, pvec,... 'CompressCurvStructs:92'
                        // [Curv.A0,Curv.A1], ... 'CompressCurvStructs:93' [Curv.U0,Curv.U1], ...
                        // 'CompressCurvStructs:94' ZSpdMode.NN, Curv.FeedRate);
                        // 'ConstrBSplineStruct:5' P0          = pvec (:, 1);
                        // 'ConstrBSplineStruct:6' P1          = pvec (:, end);
                        // 'ConstrBSplineStruct:7' A0          = avec (:, 1);
                        // 'ConstrBSplineStruct:8' A1          = avec (:, end);
                        // 'ConstrBSplineStruct:9' U0          = uvec (:, 1);
                        // 'ConstrBSplineStruct:10' U1          = uvec (:, end);
                        // 'ConstrBSplineStruct:11' evec        = zeros(3, 1);
                        // 'ConstrBSplineStruct:12' theta       = 0;
                        // 'ConstrBSplineStruct:13' pitch       = 0;
                        // 'ConstrBSplineStruct:15' c_assert(size(pvec,2) > 2, 'Not enough points');
                        // 'c_assert:2' if coder.target('rtw')
                        // 'c_assert:3' if ~condition
                        // 'c_assert:6' value = condition;
                        // 'ConstrBSplineStruct:17' CoeffP5     = zeros(3, 6);
                        // 'ConstrBSplineStruct:19' CurvStruct  = ConstrCurvStruct(CurveType.Spline,
                        // zspdmode, trafo, HSC,... 'ConstrBSplineStruct:20' Poff, Aoff, Uoff, Doff,
                        // P0, P1, ... 'ConstrBSplineStruct:21'                                 A0,
                        // A1, U0, U1, [0,0,0]', 0.0, evec, ... 'ConstrBSplineStruct:22' theta,
                        // pitch, CoeffP5, FeedRate);
                        b_pvec = pvec.size(1);
                        avec[0][0] = Curv.A0[0];
                        avec[1][0] = Curv.A1[0];
                        uvec[0][0] = Curv.U0[0];
                        uvec[1][0] = Curv.U1[0];
                        dv[0] = 0.0;
                        dv1[0] = 0.0;
                        avec[0][1] = Curv.A0[1];
                        avec[1][1] = Curv.A1[1];
                        uvec[0][1] = Curv.U0[1];
                        uvec[1][1] = Curv.U1[1];
                        dv[1] = 0.0;
                        dv1[1] = 0.0;
                        avec[0][2] = Curv.A0[2];
                        avec[1][2] = Curv.A1[2];
                        uvec[0][2] = Curv.U0[2];
                        uvec[1][2] = Curv.U1[2];
                        dv[2] = 0.0;
                        dv1[2] = 0.0;
                        for (int i3{0}; i3 < 6; i3++) {
                            dv3[i3][0] = 0.0;
                            dv3[i3][1] = 0.0;
                            dv3[i3][2] = 0.0;
                        }
                        dv5[0] = (*(double(*)[3]) & pvec[0])[0];
                        dv5[1] = (*(double(*)[3]) & pvec[0])[1];
                        dv5[2] = (*(double(*)[3]) & pvec[0])[2];
                        dv6[0] = (*(double(*)[3]) & pvec[3 * (b_pvec - 1)])[0];
                        dv6[1] = (*(double(*)[3]) & pvec[3 * (b_pvec - 1)])[1];
                        dv6[2] = (*(double(*)[3]) & pvec[3 * (b_pvec - 1)])[2];
                        ConstrCurvStruct(CurveType_Spline, ZSpdMode_NN, Curv.TRAFO, Curv.HSC,
                                         Curv.Poff, Curv.Aoff, Curv.Uoff, Curv.Doff, dv5, dv6,
                                         *(double(*)[3]) & avec[0][0], *(double(*)[3]) & avec[1][0],
                                         *(double(*)[3]) & uvec[0][0], *(double(*)[3]) & uvec[1][0],
                                         dv, 0.0, dv1, 0.0, 0.0, dv3, Curv.FeedRate, &spline);
                        // 'CompressCurvStructs:95' spline.gcode_source_line =
                        // Curv.gcode_source_line;
                        spline.gcode_source_line = Curv.gcode_source_line;
                        // 'CompressCurvStructs:96' spline.sp_index = int32(spline_index);
                        spline.sp_index = static_cast<int>(spline_index);
                        // 'CompressCurvStructs:97' spline_index = spline_index + 1;
                        spline_index++;
                        // 'CompressCurvStructs:98' spline.SpindleSpeed = spindle_speed;
                        spline.SpindleSpeed = spindle_speed;
                        // 'CompressCurvStructs:99' spindle_speed = 75000;
                        spindle_speed = 75000.0;
                        // 'CompressCurvStructs:100' ctx.q_compress.push(spline);
                        ctx->q_compress.push(&spline);
                        // 'CompressCurvStructs:101' if Curv.zspdmode == ZSpdMode.NZ
                        if (Curv.zspdmode == ZSpdMode_NZ) {
                            // 'CompressCurvStructs:102' [CurvStruct1_C, CurvStruct2_C] =
                            // CutZeroEnd(ctx, Curv, k);
                            CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz,
                                       ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                       ctx->cfg.ZeroStartAccLimit, ctx->cfg.ZeroStartJerkLimit,
                                       ctx->cfg.ZeroStartVelLimit, ctx->cfg.GaussLegendreX,
                                       ctx->cfg.GaussLegendreW, &Curv, k, &CurvStruct1_C,
                                       &CurvStruct2_C);
                            // 'CompressCurvStructs:103' ctx.q_compress.push(CurvStruct1_C);
                            ctx->q_compress.push(&CurvStruct1_C);
                            // 'CompressCurvStructs:104' ctx.q_compress.push(CurvStruct2_C);
                            ctx->q_compress.push(&CurvStruct2_C);
                        } else {
                            // 'CompressCurvStructs:105' else
                            // 'CompressCurvStructs:106' ctx.q_compress.push(Curv);
                            ctx->q_compress.push(&Curv);
                        }
                        //  With only two points, construct a line
                    } else {
                        // 'CompressCurvStructs:109' else
                        // 'CompressCurvStructs:110' C = ctx.q_gcode.get(k-1);
                        ctx->q_gcode.get(k - 1.0, &C);
                        // 'CompressCurvStructs:111' C.gcode_source_line=Curv.gcode_source_line;
                        C.gcode_source_line = Curv.gcode_source_line;
                        // 'CompressCurvStructs:112' ctx.q_compress.push(C);
                        ctx->q_compress.push(&C);
                        // 'CompressCurvStructs:113' if Curv.zspdmode == ZSpdMode.NZ
                        if (Curv.zspdmode == ZSpdMode_NZ) {
                            // 'CompressCurvStructs:114' [CurvStruct1_C, CurvStruct2_C] =
                            // CutZeroEnd(ctx, Curv, k);
                            CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz,
                                       ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                       ctx->cfg.ZeroStartAccLimit, ctx->cfg.ZeroStartJerkLimit,
                                       ctx->cfg.ZeroStartVelLimit, ctx->cfg.GaussLegendreX,
                                       ctx->cfg.GaussLegendreW, &Curv, k, &CurvStruct1_C,
                                       &CurvStruct2_C);
                            // 'CompressCurvStructs:115' ctx.q_compress.push(CurvStruct1_C);
                            ctx->q_compress.push(&CurvStruct1_C);
                            // 'CompressCurvStructs:116' ctx.q_compress.push(CurvStruct2_C);
                            ctx->q_compress.push(&CurvStruct2_C);
                        } else {
                            // 'CompressCurvStructs:117' else
                            // 'CompressCurvStructs:118' ctx.q_compress.push(Curv);
                            ctx->q_compress.push(&Curv);
                        }
                    }
                    // 'CompressCurvStructs:121' CumulatedLength = 0;
                    CumulatedLength = 0.0;
                }
                //  If this is the last segment and we have something in the
                //  compression list, construct the spline
            } else if ((static_cast<unsigned int>(k) == Ncrv) && (CumulatedLength != 0.0)) {
                int c_pvec;
                // 'CompressCurvStructs:125' elseif (k==Ncrv) && (CumulatedLength ~= 0)
                // 'CompressCurvStructs:126' SplineCurve = ConstrCurvStructType;
                ConstrCurvStructType(&SplineCurve);
                // 'CompressCurvStructs:127' SplineCurve.sp=CalcBspline_Lee(ctx.cfg, pvec);
                CalcBspline_Lee(ctx->cfg.SplineDegree, pvec, SplineCurve.sp.CoeffX,
                                SplineCurve.sp.CoeffY, SplineCurve.sp.CoeffZ, &t0_Bl_ncoeff,
                                SplineCurve.sp.Bl.breakpoints, &t0_Bl_handle, &t0_Bl_degree,
                                SplineCurve.sp.knots);
                SplineCurve.sp.Bl.ncoeff = t0_Bl_ncoeff;
                SplineCurve.sp.Bl.handle = t0_Bl_handle;
                SplineCurve.sp.Bl.degree = t0_Bl_degree;
                // 'CompressCurvStructs:128' SplineCurve.sp.Ltot = 0;
                //  satisfy coder
                // 'CompressCurvStructs:129' SplineCurve.sp.Lk = 0;
                //  satisfy coder
                // 'CompressCurvStructs:130' [Ltot, Lk]     = SplineLengthApproxGL_tot(ctx,
                // SplineCurve);
                SplineLengthApproxGL_tot(
                    ctx->cfg.GaussLegendreN, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                    SplineCurve.sp.CoeffX, SplineCurve.sp.CoeffY, SplineCurve.sp.CoeffZ,
                    t0_Bl_handle, SplineCurve.sp.knots, &SplineCurve.sp.Ltot, SplineCurve.sp.Lk);
                // 'CompressCurvStructs:131' SplineCurve.sp.Ltot = Ltot;
                // 'CompressCurvStructs:132' SplineCurve.sp.Lk   = Lk;
                // 'CompressCurvStructs:133' ctx.q_splines.push(SplineCurve);
                ctx->q_splines.push(&SplineCurve);
                // 'CompressCurvStructs:134' spline = ConstrBSplineStruct(Curv.TRAFO, Curv.HSC,...
                // 'CompressCurvStructs:135'                                     Curv.Poff,...
                // 'CompressCurvStructs:136'                                     Curv.Aoff,
                // Curv.Uoff, ... 'CompressCurvStructs:137' Curv.Doff, pvec,...
                // 'CompressCurvStructs:138' [Curv.A0,Curv.A1], ... 'CompressCurvStructs:139'
                // [Curv.U0,Curv.U1], ... 'CompressCurvStructs:140' ZSpdMode.NN, Curv.FeedRate);
                avec[0][0] = Curv.A0[0];
                avec[1][0] = Curv.A1[0];
                uvec[0][0] = Curv.U0[0];
                uvec[1][0] = Curv.U1[0];
                avec[0][1] = Curv.A0[1];
                avec[1][1] = Curv.A1[1];
                uvec[0][1] = Curv.U0[1];
                uvec[1][1] = Curv.U1[1];
                avec[0][2] = Curv.A0[2];
                avec[1][2] = Curv.A1[2];
                uvec[0][2] = Curv.U0[2];
                uvec[1][2] = Curv.U1[2];
                // 'ConstrBSplineStruct:5' P0          = pvec (:, 1);
                // 'ConstrBSplineStruct:6' P1          = pvec (:, end);
                // 'ConstrBSplineStruct:7' A0          = avec (:, 1);
                // 'ConstrBSplineStruct:8' A1          = avec (:, end);
                // 'ConstrBSplineStruct:9' U0          = uvec (:, 1);
                // 'ConstrBSplineStruct:10' U1          = uvec (:, end);
                // 'ConstrBSplineStruct:11' evec        = zeros(3, 1);
                // 'ConstrBSplineStruct:12' theta       = 0;
                // 'ConstrBSplineStruct:13' pitch       = 0;
                // 'ConstrBSplineStruct:15' c_assert(size(pvec,2) > 2, 'Not enough points');
                // 'c_assert:2' if coder.target('rtw')
                // 'c_assert:3' if ~condition
                if (pvec.size(1) <= 2) {
                    // 'c_assert:4' coder.ceval('c_assert_', message);
                    for (int i1{0}; i1 < 17; i1++) {
                        message[i1] = b_message[i1];
                    }
                    c_assert_(&message[0]);
                }
                // 'c_assert:6' value = condition;
                // 'ConstrBSplineStruct:17' CoeffP5     = zeros(3, 6);
                // 'ConstrBSplineStruct:19' CurvStruct  = ConstrCurvStruct(CurveType.Spline,
                // zspdmode, trafo, HSC,... 'ConstrBSplineStruct:20' Poff, Aoff, Uoff, Doff, P0, P1,
                // ... 'ConstrBSplineStruct:21'                                 A0, A1, U0, U1,
                // [0,0,0]', 0.0, evec, ... 'ConstrBSplineStruct:22' theta, pitch, CoeffP5,
                // FeedRate);
                c_pvec = pvec.size(1);
                dv[0] = 0.0;
                dv1[0] = 0.0;
                dv[1] = 0.0;
                dv1[1] = 0.0;
                dv[2] = 0.0;
                dv1[2] = 0.0;
                for (int i2{0}; i2 < 6; i2++) {
                    dv3[i2][0] = 0.0;
                    dv3[i2][1] = 0.0;
                    dv3[i2][2] = 0.0;
                }
                dv2[0] = (*(double(*)[3]) & pvec[0])[0];
                dv2[1] = (*(double(*)[3]) & pvec[0])[1];
                dv2[2] = (*(double(*)[3]) & pvec[0])[2];
                dv4[0] = (*(double(*)[3]) & pvec[3 * (c_pvec - 1)])[0];
                dv4[1] = (*(double(*)[3]) & pvec[3 * (c_pvec - 1)])[1];
                dv4[2] = (*(double(*)[3]) & pvec[3 * (c_pvec - 1)])[2];
                ConstrCurvStruct(CurveType_Spline, ZSpdMode_NN, Curv.TRAFO, Curv.HSC, Curv.Poff,
                                 Curv.Aoff, Curv.Uoff, Curv.Doff, dv2, dv4,
                                 *(double(*)[3]) & avec[0][0], *(double(*)[3]) & avec[1][0],
                                 *(double(*)[3]) & uvec[0][0], *(double(*)[3]) & uvec[1][0], dv,
                                 0.0, dv1, 0.0, 0.0, dv3, Curv.FeedRate, &spline);
                // 'CompressCurvStructs:141' spline.gcode_source_line = Curv.gcode_source_line;
                spline.gcode_source_line = Curv.gcode_source_line;
                // 'CompressCurvStructs:142' spline.sp_index = int32(spline_index);
                spline.sp_index = static_cast<int>(spline_index);
                // 'CompressCurvStructs:143' spline.SpindleSpeed = spindle_speed;
                spline.SpindleSpeed = spindle_speed;
                // 'CompressCurvStructs:144' ctx.q_compress.push(spline);
                ctx->q_compress.push(&spline);
                //  If this is the first (and elligible) WHAT
            } else if (k == 1.0) {
                // 'CompressCurvStructs:147' elseif k==1
                // 'CompressCurvStructs:148' ctx.q_compress.push(Curv);
                ctx->q_compress.push(&Curv);
                //  In the general case with an elligible segment, add it to the
                //  compression list
            } else {
                int i;
                // 'CompressCurvStructs:152' else
                // 'CompressCurvStructs:153' if CumulatedLength == 0
                if (CumulatedLength == 0.0) {
                    // 'CompressCurvStructs:154' P0 = EvalCurvStruct(ctx, Curv, 0);
                    b_EvalCurvStruct(&ctx->q_splines, Curv.Type, Curv.P0, Curv.P1,
                                     Curv.CorrectedHelixCenter, Curv.evec, Curv.theta, Curv.pitch,
                                     Curv.CoeffP5, Curv.sp_index, Curv.b_param, P0);
                    // 'CompressCurvStructs:155' pvec = P0;
                    pvec.set_size(3, 1);
                    pvec[0] = P0[0];
                    pvec[1] = P0[1];
                    pvec[2] = P0[2];
                    // 'CompressCurvStructs:156' spindle_speed = Curv.SpindleSpeed;
                    spindle_speed = Curv.SpindleSpeed;
                }
                // 'CompressCurvStructs:158' CumulatedLength = CumulatedLength + LengthCurv(ctx,
                // Curv, 0, 1);
                CumulatedLength += LengthCurv(&ctx->q_splines, ctx->cfg.GaussLegendreX,
                                              ctx->cfg.GaussLegendreW, &Curv);
                // 'CompressCurvStructs:159' P1 = EvalCurvStruct(ctx, Curv, 1);
                b_EvalCurvStruct(&ctx->q_splines, Curv.Type, Curv.P0, Curv.P1,
                                 Curv.CorrectedHelixCenter, Curv.evec, Curv.theta, Curv.pitch,
                                 Curv.CoeffP5, Curv.sp_index, Curv.a_param, Curv.b_param, P1);
                // 'CompressCurvStructs:160' pvec = [pvec P1];
                i = pvec.size(1);
                pvec.set_size(3, pvec.size(1) + 1);
                pvec[3 * i] = P1[0];
                pvec[3 * i + 1] = P1[1];
                pvec[3 * i + 2] = P1[2];
                // 'CompressCurvStructs:161' spindle_speed = min(spindle_speed, Curv.SpindleSpeed);
                spindle_speed = std::fmin(spindle_speed, Curv.SpindleSpeed);
            }
            // 'CompressCurvStructs:163' k = k + 1;
        }
    }
}

} // namespace ocn

//
// File trailer for CompressCurvStructs.cpp
//
// [EOF]
//
