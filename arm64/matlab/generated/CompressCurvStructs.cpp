//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CompressCurvStructs.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "CompressCurvStructs.h"
#include "CalcBspline_Lee.h"
#include "ConstrBSplineStruct.h"
#include "ConstrCurvStructType.h"
#include "CurvCollinear.h"
#include "CutZeroEnd.h"
#include "CutZeroStart.h"
#include "DebugLog.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_types.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
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
    double P0[3];
    double P1[3];
    if (!ctx->q_gcode.isempty()) {
        double CumulatedLength;
        double spindle_speed;
        unsigned int Ncrv;
        unsigned int spline_index;
        spline_index = ctx->q_splines.size() + 1U;
        Ncrv = ctx->q_gcode.size();
        CumulatedLength = 0.0;
        //  [mm]
        j_DebugLog();
        spindle_speed = 75000.0;
        //  Satisfy coder
        //  -------------
        pvec.set_size(3, 0);
        ctx->q_gcode.get(static_cast<double>(1.0), &b_ctx);
        //  -------------
        //   ||...
        //              (CumulatedLength > 0 && ~CurvCollinear(ctx, ctx.q_gcode.get(k-1), Curv,
        //              ctx.cfg.Compressing.MaxCollinearityDegrees))
        for (double k{1.0}; k <= Ncrv; k++) {
            bool Collinear;
            ctx->q_gcode.get(k, &Curv);
            //  If the next curve segment is too long for compressing or it is not an NN,
            //  we need to stop growing the compressing list and create the spline
            Collinear = false;
            if (k > 1.0) {
                ctx->q_gcode.get(k - 1.0, &expl_temp);
                Collinear = CurvCollinear(&ctx->q_splines, expl_temp.Type, expl_temp.P0,
                                          expl_temp.P1, expl_temp.CorrectedHelixCenter,
                                          expl_temp.evec, expl_temp.theta, expl_temp.pitch,
                                          expl_temp.CoeffP5, expl_temp.sp_index, expl_temp.a_param,
                                          expl_temp.b_param, &Curv, ctx->cfg.Compressing.ColTolDeg);
            }
            if ((LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, Curv.Type, Curv.P0,
                            Curv.P1, Curv.CorrectedHelixCenter, Curv.evec, Curv.theta, Curv.pitch,
                            Curv.CoeffP5, Curv.sp_index, Curv.a_param,
                            Curv.b_param) >= ctx->cfg.LThreshold) ||
                (Curv.zspdmode != ZSpdMode_NN) || ((CumulatedLength == 0.0) && (!Collinear))) {
                //  If the cumulated length is zero, no compressing is on-going and we can
                //  treat the segment individually
                if (CumulatedLength == 0.0) {
                    //  If the segment is not a normal one (Nonzero, Nonzero), it needs
                    //  to be split
                    if (Curv.zspdmode == ZSpdMode_ZN) {
                        CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                     ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                     ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                     ctx->cfg.DebugCutZero, ctx->cfg.NGridLengthSpline, &Curv, k,
                                     &CurvStruct1_C, &CurvStruct2_C);
                        ctx->q_compress.push(&CurvStruct1_C);
                        ctx->q_compress.push(&CurvStruct2_C);
                    } else if (Curv.zspdmode == ZSpdMode_NZ) {
                        CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                   ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                   ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                   ctx->cfg.NGridLengthSpline, &Curv, k, &CurvStruct1_C,
                                   &CurvStruct2_C);
                        ctx->q_compress.push(&CurvStruct1_C);
                        ctx->q_compress.push(&CurvStruct2_C);
                    } else if (Curv.zspdmode == ZSpdMode_ZZ) {
                        CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                     ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                     ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                     ctx->cfg.DebugCutZero, ctx->cfg.NGridLengthSpline, &Curv, k,
                                     &CurvStruct1_C, &CurvStruct2_C);
                        CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                   ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                   ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                   ctx->cfg.NGridLengthSpline, &CurvStruct2_C, k, &b_CurvStruct2_C,
                                   &CurvStruct3_C);
                        ctx->q_compress.push(&CurvStruct1_C);
                        ctx->q_compress.push(&b_CurvStruct2_C);
                        ctx->q_compress.push(&CurvStruct3_C);
                        //  If the segment is normal, (Nonzero, Nonzero), it can be pushed
                        //  as-is into the output list
                    } else {
                        ctx->q_compress.push(&Curv);
                    }
                    //  If there was an on-going compression
                } else {
                    //  We have more than 2 points, thus constructing a spline
                    //  is warranted
                    if (pvec.size(1) > 2) {
                        ConstrCurvStructType(&SplineCurve);
                        CalcBspline_Lee(ctx->cfg.SplineDegree, pvec, SplineCurve.sp.CoeffX,
                                        SplineCurve.sp.CoeffY, SplineCurve.sp.CoeffZ,
                                        &SplineCurve.sp.Bl.ncoeff, SplineCurve.sp.Bl.breakpoints,
                                        &SplineCurve.sp.Bl.handle, &SplineCurve.sp.Bl.degree,
                                        SplineCurve.sp.knots);
                        ctx->q_splines.push(&SplineCurve);
                        ConstrBSplineStruct(pvec, Curv.FeedRate, &spline);
                        spline.gcode_source_line = Curv.gcode_source_line;
                        spline.sp_index = static_cast<int>(spline_index);
                        spline_index++;
                        spline.SpindleSpeed = spindle_speed;
                        spindle_speed = 75000.0;
                        ctx->q_compress.push(&spline);
                        if (Curv.zspdmode == ZSpdMode_NZ) {
                            CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz,
                                       ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                       ctx->cfg.ZeroStartAccLimit, ctx->cfg.ZeroStartJerkLimit,
                                       ctx->cfg.ZeroStartVelLimit, ctx->cfg.NGridLengthSpline,
                                       &Curv, k, &CurvStruct1_C, &CurvStruct2_C);
                            ctx->q_compress.push(&CurvStruct1_C);
                            ctx->q_compress.push(&CurvStruct2_C);
                        } else {
                            ctx->q_compress.push(&Curv);
                        }
                        //  With only two points, construct a line
                    } else {
                        ctx->q_gcode.get(k - 1.0, &C);
                        ctx->q_compress.push(&C);
                        if (Curv.zspdmode == ZSpdMode_NZ) {
                            CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz,
                                       ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                       ctx->cfg.ZeroStartAccLimit, ctx->cfg.ZeroStartJerkLimit,
                                       ctx->cfg.ZeroStartVelLimit, ctx->cfg.NGridLengthSpline,
                                       &Curv, k, &CurvStruct1_C, &CurvStruct2_C);
                            ctx->q_compress.push(&CurvStruct1_C);
                            ctx->q_compress.push(&CurvStruct2_C);
                        } else {
                            ctx->q_compress.push(&Curv);
                        }
                    }
                    CumulatedLength = 0.0;
                }
                //  If this is the last segment and we have something in the
                //  compression list, construct the spline
            } else if ((static_cast<unsigned int>(k) == Ncrv) && (CumulatedLength != 0.0)) {
                ConstrCurvStructType(&SplineCurve);
                CalcBspline_Lee(
                    ctx->cfg.SplineDegree, pvec, SplineCurve.sp.CoeffX, SplineCurve.sp.CoeffY,
                    SplineCurve.sp.CoeffZ, &SplineCurve.sp.Bl.ncoeff, SplineCurve.sp.Bl.breakpoints,
                    &SplineCurve.sp.Bl.handle, &SplineCurve.sp.Bl.degree, SplineCurve.sp.knots);
                ctx->q_splines.push(&SplineCurve);
                ConstrBSplineStruct(pvec, Curv.FeedRate, &spline);
                spline.gcode_source_line = Curv.gcode_source_line;
                spline.sp_index = static_cast<int>(spline_index);
                spline.SpindleSpeed = spindle_speed;
                ctx->q_compress.push(&spline);
                //  If this is the first (and elligible) WHAT
            } else if (k == 1.0) {
                ctx->q_compress.push(&Curv);
                //  In the general case with an elligible segment, add it to the
                //  compression list
            } else {
                int i;
                if (CumulatedLength == 0.0) {
                    b_EvalCurvStruct(&ctx->q_splines, Curv.Type, Curv.P0, Curv.P1,
                                     Curv.CorrectedHelixCenter, Curv.evec, Curv.theta, Curv.pitch,
                                     Curv.CoeffP5, Curv.sp_index, Curv.b_param, P0);
                    pvec.set_size(3, 1);
                    pvec[0] = P0[0];
                    pvec[1] = P0[1];
                    pvec[2] = P0[2];
                    spindle_speed = Curv.SpindleSpeed;
                }
                CumulatedLength +=
                    LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, Curv.Type, Curv.P0,
                               Curv.P1, Curv.CorrectedHelixCenter, Curv.evec, Curv.theta,
                               Curv.pitch, Curv.CoeffP5, Curv.sp_index, Curv.a_param, Curv.b_param);
                b_EvalCurvStruct(&ctx->q_splines, Curv.Type, Curv.P0, Curv.P1,
                                 Curv.CorrectedHelixCenter, Curv.evec, Curv.theta, Curv.pitch,
                                 Curv.CoeffP5, Curv.sp_index, Curv.a_param, Curv.b_param, P1);
                i = pvec.size(1);
                pvec.set_size(3, pvec.size(1) + 1);
                pvec[3 * i] = P1[0];
                pvec[3 * i + 1] = P1[1];
                pvec[3 * i + 2] = P1[2];
                spindle_speed = std::fmin(spindle_speed, Curv.SpindleSpeed);
            }
        }
    }
}

} // namespace ocn

//
// File trailer for CompressCurvStructs.cpp
//
// [EOF]
//
