//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcTransition.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 31-Aug-2023 09:29:48
//

// Include Files
#include "calcTransition.h"
#include "EvalCurvStruct.h"
#include "G2_Hermite_Interpolation_nAxis.h"
#include "LengthCurv.h"
#include "calc_t_nk_kappa.h"
#include "constrTransP5Struct.h"
#include "cutCurvStruct.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
namespace ocn {
static bool check_continuity(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                             const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                             const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                             const int ctx_cfg_maskRot_size[2],
                             const ::coder::array<int, 1U> &ctx_cfg_indCart,
                             const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                             int ctx_cfg_NCart, int ctx_cfg_NRot,
                             double ctx_cfg_Smoothing_ColTolCosSmooth,
                             double ctx_cfg_Smoothing_ColTolSmooth, const CurvStruct *curv1,
                             const CurvStruct *curv2);

}

// Function Definitions
//
// function [ isValid ] = check_continuity( ctx, curv1, curv2 )
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const bool ctx_cfg_maskCart_data[]
//                const int ctx_cfg_maskCart_size[2]
//                const bool ctx_cfg_maskRot_data[]
//                const int ctx_cfg_maskRot_size[2]
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                double ctx_cfg_Smoothing_ColTolCosSmooth
//                double ctx_cfg_Smoothing_ColTolSmooth
//                const CurvStruct *curv1
//                const CurvStruct *curv2
// Return Type  : bool
//
namespace ocn {
static bool check_continuity(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                             const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                             const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                             const int ctx_cfg_maskRot_size[2],
                             const ::coder::array<int, 1U> &ctx_cfg_indCart,
                             const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                             int ctx_cfg_NCart, int ctx_cfg_NRot,
                             double ctx_cfg_Smoothing_ColTolCosSmooth,
                             double ctx_cfg_Smoothing_ColTolSmooth, const CurvStruct *curv1,
                             const CurvStruct *curv2)
{
    ::coder::array<double, 1U> a__5;
    ::coder::array<double, 1U> a__6;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    ::coder::array<double, 1U> r11;
    ::coder::array<double, 1U> r1d1;
    ::coder::array<double, 1U> r1dd1;
    ::coder::array<double, 1U> r21;
    ::coder::array<double, 1U> r2d1;
    ::coder::array<double, 1U> r2dd1;
    ::coder::array<double, 1U> t1;
    ::coder::array<double, 1U> t2;
    ::coder::array<double, 1U> x;
    ::coder::array<double, 1U> z1;
    ::coder::array<bool, 1U> b_x;
    double kappa1;
    double kappa2;
    int b_k;
    int b_loop_ub;
    bool exitg1;
    bool isG1;
    bool isValid;
    bool y;
    // 'calcTransition:78' tol         = ctx.cfg.Smoothing.ColTolSmooth;
    // 'calcTransition:79' tol_cos     = ctx.cfg.Smoothing.ColTolCosSmooth;
    // 'calcTransition:80' tol_kappa   = 1E-3;
    // 'calcTransition:82' [ r11, r1d1, r1dd1 ] = EvalCurvStruct( ctx, curv1, 1 );
    e_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv1, r11, r1d1, r1dd1);
    // 'calcTransition:83' [ r21, r2d1, r2dd1 ] = EvalCurvStruct( ctx, curv2, 0 );
    f_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv2, r21, r2d1, r2dd1);
    // 'calcTransition:85' [t1, ~,  kappa1] = calc_t_nk_kappa( r1d1, r1dd1 );
    calc_t_nk_kappa(r1d1, r1dd1, t1, a__5, &kappa1);
    // 'calcTransition:86' [t2, ~,  kappa2] = calc_t_nk_kappa( r2d1, r2dd1 );
    calc_t_nk_kappa(r2d1, r2dd1, t2, a__6, &kappa2);
    // 'calcTransition:88' isC0    = all( abs( r11    -r21 ) < tol, 'all' );
    if (r11.size(0) == r21.size(0)) {
        int loop_ub;
        x.set_size(r11.size(0));
        loop_ub = r11.size(0);
        for (int i{0}; i < loop_ub; i++) {
            x[i] = r11[i] - r21[i];
        }
    } else {
        minus(x, r11, r21);
    }
    z1.set_size(x.size(0));
    if (x.size(0) != 0) {
        int i1;
        i1 = x.size(0);
        for (int k{0}; k < i1; k++) {
            z1[k] = std::abs(x[k]);
        }
    }
    // 'calcTransition:89' isG1    = collinear( t1, t2, tol_cos );
    // 'collinear:2' if (norm(u) < eps || norm(v) < eps)
    if ((coder::b_norm(t1) < 2.2204460492503131E-16) ||
        (coder::b_norm(t2) < 2.2204460492503131E-16)) {
        // 'collinear:3' value = true;
        isG1 = true;
    } else {
        double c;
        int c_loop_ub;
        int d_loop_ub;
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
        // 'collinear:7' value = cos_angle >= tol_cos;
        c = 0.0;
        if (t1.size(0) >= 1) {
            int ixlast;
            ixlast = t1.size(0);
            for (int c_k{0}; c_k < ixlast; c_k++) {
                c += t1[c_k] * t2[c_k];
            }
        }
        r.set_size(t1.size(0));
        c_loop_ub = t1.size(0);
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            double varargin_1;
            varargin_1 = t1[i3];
            r[i3] = std::pow(varargin_1, 2.0);
        }
        r1.set_size(t2.size(0));
        d_loop_ub = t2.size(0);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            double b_varargin_1;
            b_varargin_1 = t2[i4];
            r1[i4] = std::pow(b_varargin_1, 2.0);
        }
        isG1 = (c / (std::sqrt(coder::sum(r)) * std::sqrt(coder::sum(r1))) >=
                ctx_cfg_Smoothing_ColTolCosSmooth);
    }
    // 'calcTransition:90' isG2    = abs( kappa1 -kappa2 )   < tol_kappa;
    // 'calcTransition:92' isValid = isC0 && isG1 && isG2;
    b_x.set_size(z1.size(0));
    b_loop_ub = z1.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        b_x[i2] = (z1[i2] < ctx_cfg_Smoothing_ColTolSmooth);
    }
    y = true;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k <= b_x.size(0) - 1)) {
        if (!b_x[b_k]) {
            y = false;
            exitg1 = true;
        } else {
            b_k++;
        }
    }
    if (y && isG1 && (std::abs(kappa1 - kappa2) < 0.001)) {
        isValid = true;
    } else {
        isValid = false;
    }
    return isValid;
}

//
// function [ status, curv1C, curv2C, curvT ] = calcTransition( ctx, curv1, curv2 )
//
// calcTransition_new : Compute a transition curve using on a polynome of
//  degree 5.
//
//  ctx           : The context
//  curv          : Current structure of the curve
//  nextCurv      : Next structure of the curve
//
//  curv          : New calculated curve structure (replace CurvStruct1)
//  curvT         : New calculated transition curve
//  nextCurv      : New calculated curve structure (replace CurvStruct2)
//  status        : Status of the compuation see TransitionResult
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const bool ctx_cfg_maskCart_data[]
//                const int ctx_cfg_maskCart_size[2]
//                const bool ctx_cfg_maskRot_data[]
//                const int ctx_cfg_maskRot_size[2]
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const ::coder::array<double, 1U> &ctx_cfg_D
//                double ctx_cfg_CutOff
//                double ctx_cfg_Smoothing_ColTolCosSmooth
//                double ctx_cfg_Smoothing_ColTolSmooth
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *curv1
//                const CurvStruct *curv2
//                TransitionResult *status
//                CurvStruct *curv1C
//                CurvStruct *curv2C
//                CurvStruct *curvT
// Return Type  : void
//
void calcTransition(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                    const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                    const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                    const int ctx_cfg_maskRot_size[2],
                    const ::coder::array<int, 1U> &ctx_cfg_indCart,
                    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                    int ctx_cfg_NCart, int ctx_cfg_NRot,
                    const ::coder::array<double, 1U> &ctx_cfg_D, double ctx_cfg_CutOff,
                    double ctx_cfg_Smoothing_ColTolCosSmooth, double ctx_cfg_Smoothing_ColTolSmooth,
                    const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
                    const CurvStruct *curv1, const CurvStruct *curv2, TransitionResult *status,
                    CurvStruct *curv1C, CurvStruct *curv2C, CurvStruct *curvT)
{
    ::coder::array<double, 1U> r0D0;
    ::coder::array<double, 1U> r0D1;
    ::coder::array<double, 1U> r0D2;
    ::coder::array<double, 1U> r1D0;
    ::coder::array<double, 1U> r1D1;
    ::coder::array<double, 1U> r1D2;
    CurvStruct a__2;
    CurvStruct a__4;
    double L1;
    double L2;
    double a__1;
    double a__3;
    int ret;
    TransitionResult b_status;
    // 'calcTransition:15' coder.inline( "never" );
    // 'calcTransition:17' CutOff = ctx.cfg.CutOff;
    // 'calcTransition:18' Lcut1 = CutOff;
    // 'calcTransition:18' Lcut2 = CutOff;
    // 'calcTransition:20' L1 = LengthCurv( ctx, curv1, 0, 1 );
    L1 = LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                    ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                    ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                    ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv1);
    // 'calcTransition:21' L2 = LengthCurv( ctx, curv2, 0, 1 );
    L2 = LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                    ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                    ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                    ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv2);
    //  If curv length is lower that cutting length return
    // 'calcTransition:24' if( ( L1 < 3 * Lcut1 ) || ( L2 < 3 * Lcut2 ) )
    if ((L1 < 3.0 * ctx_cfg_CutOff) || (L2 < 3.0 * ctx_cfg_CutOff)) {
        // 'calcTransition:25' curv1C  = curv1;
        *curv1C = *curv1;
        // 'calcTransition:25' curv2C  = curv2;
        *curv2C = *curv2;
        // 'calcTransition:25' curvT   = curv1;
        *curvT = *curv1;
        // 'calcTransition:26' status  = TransitionResult.NoSolution;
        b_status = TransitionResult_NoSolution;
    } else {
        double p5[6][6];
        // 'calcTransition:30' [ ~, curv1C, ~ ] = cutCurvStruct( ctx, curv1, 0, L1-Lcut1, false );
        cutCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                      ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                      ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                      ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                      curv1, L1 - ctx_cfg_CutOff, &a__1, curv1C, &a__2);
        // 'calcTransition:31' assert( check_curv_length( ctx, curv1C, L1-Lcut1 ), mfilename + "
        // Curve Length not valide"); 'calcTransition:96' tol = 1E-3; 'calcTransition:98' isValid =
        // ( abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
        LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                   ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                   ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                   ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv1C);
        b_cutCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                        ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                        ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                        curv2, L2 - ctx_cfg_CutOff, &a__3, &a__4, curv2C);
        // 'calcTransition:33' assert( check_curv_length( ctx, curv2C, L2-Lcut2 ), mfilename + "
        // Curve Length not valide"); 'calcTransition:96' tol = 1E-3; 'calcTransition:98' isValid =
        // ( abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
        LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                   ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                   ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                   ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv2C);
        e_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv1C, r0D0, r0D1, r0D2);
        // 'calcTransition:36' [r1D0, r1D1, r1D2] = EvalCurvStruct( ctx, curv2C, 0 );
        f_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv2C, r1D0, r1D1, r1D2);
        // 'calcTransition:39' [p5, ret] = G2_Hermite_Interpolation_nAxis(ctx, r0D0, r0D1, r0D2, ...
        // 'calcTransition:40'                                                 r1D0, r1D1, r1D2);
        G2_Hermite_Interpolation_nAxis(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_D, r0D0,
                                       r0D1, r0D2, r1D0, r1D1, r1D2, p5, &ret);
        // 'calcTransition:42' curvT = constrTransP5Struct( curv1.Info, curv1.tool, curv1.R1, ...
        // 'calcTransition:43'                              curv2.R0, p5 );
        b_constrTransP5Struct(
            curv1->Info.TRAFO, curv1->Info.HSC, curv1->Info.FeedRate, curv1->Info.SpindleSpeed,
            curv1->Info.gcode_source_line, curv1->Info.G91, curv1->Info.G91_1, curv1->tool.toolno,
            curv1->tool.pocketno, &curv1->tool.offset, curv1->tool.diameter, curv1->tool.frontangle,
            curv1->tool.backangle, curv1->tool.orientation, curv1->R1, curv2->R0, p5, curvT);
        // 'calcTransition:44' curvT.Info.SpindleSpeed = min( curv1.Info.SpindleSpeed, ...
        // 'calcTransition:45'                                curv2.Info.SpindleSpeed );
        curvT->Info.SpindleSpeed = std::fmin(curv1->Info.SpindleSpeed, curv2->Info.SpindleSpeed);
        // 'calcTransition:46' curvT.Info.FeedRate     = min( curv1.Info.FeedRate, ...
        // 'calcTransition:47'                                curv2.Info.FeedRate );
        curvT->Info.FeedRate = std::fmin(curv1->Info.FeedRate, curv2->Info.FeedRate);
        // 'calcTransition:49' if( ret== 1 )
        if (ret == 1) {
            //  standard case
            //  transition CurvStruct calculation
            // 'calcTransition:52' status = TransitionResult.Ok;
            b_status = TransitionResult_Ok;
        } else if (ret == 2) {
            // 'calcTransition:53' elseif( ret == 2 )
            //  badly conditioned matrix in G2_Hermite()
            // 'calcTransition:55' status = TransitionResult.NoSolution;
            b_status = TransitionResult_NoSolution;
        } else if (ret == 6) {
            // 'calcTransition:56' elseif( ret == 6 )
            //  TODO: decide in the future...
            //  Now we ignore and construct the transition curve anyway
            // 'calcTransition:59' status = TransitionResult.Ok;
            b_status = TransitionResult_Ok;
        } else {
            // 'calcTransition:60' else
            // 'calcTransition:61' status = TransitionResult.NoSolution;
            b_status = TransitionResult_NoSolution;
        }
        // 'calcTransition:64' if( ( status ~= TransitionResult.NoSolution ) && ...
        // 'calcTransition:65'     ( all( p5 <= 0, 'all' ) ) )
        if (b_status != TransitionResult_NoSolution) {
            int k;
            bool x[6][6];
            bool exitg1;
            bool y;
            for (int i{0}; i < 6; i++) {
                for (int i1{0}; i1 < 6; i1++) {
                    x[i][i1] = (p5[i][i1] <= 0.0);
                }
            }
            y = true;
            k = 0;
            exitg1 = false;
            while ((!exitg1) && (k < 36)) {
                if (!(&x[0][0])[k]) {
                    y = false;
                    exitg1 = true;
                } else {
                    k++;
                }
            }
            if (y) {
                // 'calcTransition:66' status = TransitionResult.NoSolution;
                b_status = TransitionResult_NoSolution;
            }
        }
        // 'calcTransition:69' if( status == TransitionResult.Ok )
        if (b_status == TransitionResult_Ok) {
            bool b_isValid;
            bool isValid;
            // 'calcTransition:70' isValid = check_continuity( ctx, curv1C, curvT );
            isValid = check_continuity(
                ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size, ctx_cfg_indCart,
                ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                ctx_cfg_Smoothing_ColTolCosSmooth, ctx_cfg_Smoothing_ColTolSmooth, curv1C, curvT);
            // 'calcTransition:71' isValid = isValid && check_continuity( ctx, curvT, curv2C );
            if (isValid &&
                check_continuity(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                                 ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                                 ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot,
                                 ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                                 ctx_cfg_Smoothing_ColTolCosSmooth, ctx_cfg_Smoothing_ColTolSmooth,
                                 curvT, curv2C)) {
                b_isValid = true;
            } else {
                b_isValid = false;
            }
            // 'calcTransition:72' if( ~isValid )
            if (!b_isValid) {
                // 'calcTransition:72' status = TransitionResult.NoSolution;
                b_status = TransitionResult_NoSolution;
            }
        }
    }
    *status = b_status;
}

//
// Arguments    : ::coder::array<double, 1U> &in1
//                const ::coder::array<double, 1U> &in2
//                const ::coder::array<double, 1U> &in3
// Return Type  : void
//
void minus(::coder::array<double, 1U> &in1, const ::coder::array<double, 1U> &in2,
           const ::coder::array<double, 1U> &in3)
{
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (in3.size(0) == 1) {
        i = in2.size(0);
    } else {
        i = in3.size(0);
    }
    in1.set_size(i);
    stride_0_0 = (in2.size(0) != 1);
    stride_1_0 = (in3.size(0) != 1);
    if (in3.size(0) == 1) {
        loop_ub = in2.size(0);
    } else {
        loop_ub = in3.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        in1[i1] = in2[i1 * stride_0_0] - in3[i1 * stride_1_0];
    }
}

} // namespace ocn

//
// File trailer for calcTransition.cpp
//
// [EOF]
//
