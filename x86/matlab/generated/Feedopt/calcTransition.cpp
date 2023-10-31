
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calcTransition.cpp
//
// MATLAB Coder version            : 5.4
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
#include "ocn_assert.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>
#include <emmintrin.h>

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
    ::coder::array<double, 1U> r11;
    ::coder::array<double, 1U> r1d1;
    ::coder::array<double, 1U> r1dd1;
    ::coder::array<double, 1U> r2;
    ::coder::array<double, 1U> r21;
    ::coder::array<double, 1U> r2d1;
    ::coder::array<double, 1U> r2dd1;
    ::coder::array<double, 1U> r3;
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
    bool varargout_1;
    // 'calcTransition:89' tol         = ctx.cfg.Smoothing.ColTolSmooth;
    // 'calcTransition:90' tol_cos     = ctx.cfg.Smoothing.ColTolCosSmooth;
    // 'calcTransition:91' tol_kappa   = 1E-3;
    // 'calcTransition:93' [ r11, r1d1, r1dd1 ] = EvalCurvStruct( ctx, curv1, 1 );
    f_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv1, r11, r1d1, r1dd1);
    // 'calcTransition:94' [ r21, r2d1, r2dd1 ] = EvalCurvStruct( ctx, curv2, 0 );
    g_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv2, r21, r2d1, r2dd1);
    // 'calcTransition:96' [t1, ~,  kappa1] = calc_t_nk_kappa( r1d1, r1dd1 );
    calc_t_nk_kappa(r1d1, r1dd1, t1, a__5, &kappa1);
    // 'calcTransition:97' [t2, ~,  kappa2] = calc_t_nk_kappa( r2d1, r2dd1 );
    calc_t_nk_kappa(r2d1, r2dd1, t2, a__6, &kappa2);
    // 'calcTransition:99' isC0    = all( abs( r11    -r21 ) < tol, 'all' );
    if (r11.size(0) == r21.size(0)) {
        int loop_ub;
        int scalarLB;
        int vectorUB;
        x.set_size(r11.size(0));
        loop_ub = r11.size(0);
        scalarLB = (r11.size(0) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (int i1{0}; i1 <= vectorUB; i1 += 2) {
            __m128d r;
            __m128d r1;
            r = _mm_loadu_pd(&r11[i1]);
            r1 = _mm_loadu_pd(&r21[i1]);
            _mm_storeu_pd(&x[i1], _mm_sub_pd(r, r1));
        }
        for (int i1{scalarLB}; i1 < loop_ub; i1++) {
            x[i1] = r11[i1] - r21[i1];
        }
    } else {
        minus(x, r11, r21);
    }
    z1.set_size(x.size(0));
    if (x.size(0) != 0) {
        int i;
        i = x.size(0);
        for (int k{0}; k < i; k++) {
            z1[k] = std::abs(x[k]);
        }
    }
    // 'calcTransition:100' isG1    = collinear( t1, t2, tol_cos );
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
        r2.set_size(t1.size(0));
        c_loop_ub = t1.size(0);
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            double varargin_1;
            varargin_1 = t1[i3];
            r2[i3] = std::pow(varargin_1, 2.0);
        }
        r3.set_size(t2.size(0));
        d_loop_ub = t2.size(0);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            double b_varargin_1;
            b_varargin_1 = t2[i4];
            r3[i4] = std::pow(b_varargin_1, 2.0);
        }
        isG1 = (c / (std::sqrt(coder::sum(r2)) * std::sqrt(coder::sum(r3))) >=
                ctx_cfg_Smoothing_ColTolCosSmooth);
    }
    // 'calcTransition:101' isG2    = abs( kappa1 -kappa2 )   < tol_kappa;
    // 'calcTransition:103' isValid = isC0 && isG1 && isG2;
    b_x.set_size(z1.size(0));
    b_loop_ub = z1.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        b_x[i2] = (z1[i2] < ctx_cfg_Smoothing_ColTolSmooth);
    }
    varargout_1 = true;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k <= b_x.size(0) - 1)) {
        if (!b_x[b_k]) {
            varargout_1 = false;
            exitg1 = true;
        } else {
            b_k++;
        }
    }
    if (varargout_1 && isG1 && (std::abs(kappa1 - kappa2) < 0.001)) {
        isValid = true;
    } else {
        isValid = false;
    }
    return isValid;
}

//
// function [ status, curv1C, curv2C, curvT, ret ] = ...
// calcTransition( ctx, curv1, curv2 )
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
//                int *ret
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
                    CurvStruct *curv1C, CurvStruct *curv2C, CurvStruct *curvT, int *ret)
{
    ::coder::array<double, 1U> r0D0;
    ::coder::array<double, 1U> r0D1;
    ::coder::array<double, 1U> r0D2;
    ::coder::array<double, 1U> r1D0;
    ::coder::array<double, 1U> r1D1;
    ::coder::array<double, 1U> r1D2;
    CurvStruct a__2;
    CurvStruct a__4;
    double R0T_data[6];
    double R1T_data[6];
    double L1;
    double L2;
    double a__1;
    double a__3;
    int b_ret;
    int c_ret;
    TransitionResult b_status;
    // 'calcTransition:16' coder.inline( "never" );
    // 'calcTransition:18' ret     = int32( 9 );
    b_ret = 9;
    // 'calcTransition:19' CutOff  = ctx.cfg.CutOff;
    // 'calcTransition:20' Lcut1   = CutOff;
    // 'calcTransition:20' Lcut2 = CutOff;
    // 'calcTransition:22' L1 = LengthCurv( ctx, curv1, 0, 1 );
    L1 = LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                    ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                    ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                    ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv1);
    // 'calcTransition:23' L2 = LengthCurv( ctx, curv2, 0, 1 );
    L2 = LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                    ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                    ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                    ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv2);
    //  If curv length is lower that cutting length return
    // 'calcTransition:26' if( ( L1 < 3 * Lcut1 ) || ( L2 < 3 * Lcut2 ) )
    if ((L1 < 3.0 * ctx_cfg_CutOff) || (L2 < 3.0 * ctx_cfg_CutOff)) {
        // 'calcTransition:27' curv1C  = curv1;
        *curv1C = *curv1;
        // 'calcTransition:27' curv2C  = curv2;
        *curv2C = *curv2;
        // 'calcTransition:27' curvT   = curv1;
        *curvT = *curv1;
        // 'calcTransition:28' status  = TransitionResult.NoSolution;
        b_status = TransitionResult_NoSolution;
    } else {
        double p5[6][6];
        double b_x;
        double x;
        int b_end;
        int b_loop_ub;
        int b_partialTrueCount;
        int end;
        int loop_ub;
        int partialTrueCount;
        // 'calcTransition:32' [ ~, curv1C, ~ ] = cutCurvStruct( ctx, curv1, 0, L1-Lcut1, false );
        cutCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                      ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                      ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                      ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                      curv1, L1 - ctx_cfg_CutOff, &a__1, curv1C, &a__2);
        // 'calcTransition:33' ocn_assert( check_curv_length( ctx, curv1C, L1-Lcut1 ), "Curve Length
        // not valide", mfilename ); 'calcTransition:107' tol = 1E-3; 'calcTransition:109' isValid =
        // ( abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
        x = LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                       ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                       ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                       ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                       curv1C) -
            (L1 - ctx_cfg_CutOff);
        o_ocn_assert(std::abs(x) <= 0.001);
        // 'calcTransition:34' [ ~, ~, curv2C ] = cutCurvStruct( ctx, curv2, 1, L2-Lcut2, true );
        b_cutCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                        ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                        ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                        curv2, L2 - ctx_cfg_CutOff, &a__3, &a__4, curv2C);
        // 'calcTransition:35' ocn_assert( check_curv_length( ctx, curv2C, L2-Lcut2 ), "Curve Length
        // not valide", mfilename ); 'calcTransition:107' tol = 1E-3; 'calcTransition:109' isValid =
        // ( abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
        b_x = LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX,
                         ctx_cfg_GaussLegendreW, curv2C) -
              (L2 - ctx_cfg_CutOff);
        o_ocn_assert(std::abs(b_x) <= 0.001);
        // 'calcTransition:37' [r0D0, r0D1, r0D2] = EvalCurvStruct( ctx, curv1C, 1 );
        f_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv1C, r0D0, r0D1, r0D2);
        // 'calcTransition:38' [r1D0, r1D1, r1D2] = EvalCurvStruct( ctx, curv2C, 0 );
        g_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv2C, r1D0, r1D1, r1D2);
        // 'calcTransition:41' [p5, ret] = G2_Hermite_Interpolation_nAxis(ctx, r0D0, r0D1, r0D2, ...
        // 'calcTransition:42'                                                 r1D0, r1D1, r1D2);
        G2_Hermite_Interpolation_nAxis(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_D, r0D0,
                                       r0D1, r0D2, r1D0, r1D1, r1D2, p5, &c_ret);
        b_ret = c_ret;
        // 'calcTransition:44' R0T = zeros( length(ctx.cfg.maskTot), 1 );
        loop_ub = ctx_cfg_maskTot_size[1];
        if (loop_ub - 1 >= 0) {
            std::memset(&R0T_data[0], 0, loop_ub * sizeof(double));
        }
        // 'calcTransition:44' R1T = R0T;
        b_loop_ub = ctx_cfg_maskTot_size[1];
        if (b_loop_ub - 1 >= 0) {
            std::memset(&R1T_data[0], 0, b_loop_ub * sizeof(double));
        }
        // 'calcTransition:45' R0T( ctx.cfg.maskTot ) = r0D0;
        end = ctx_cfg_maskTot_size[1];
        partialTrueCount = 0;
        for (int i{0}; i < end; i++) {
            if (ctx_cfg_maskTot_data[i]) {
                R0T_data[i] = r0D0[partialTrueCount];
                partialTrueCount++;
            }
        }
        // 'calcTransition:46' R1T( ctx.cfg.maskTot ) = r1D0;
        b_end = ctx_cfg_maskTot_size[1];
        b_partialTrueCount = 0;
        for (int b_i{0}; b_i < b_end; b_i++) {
            if (ctx_cfg_maskTot_data[b_i]) {
                R1T_data[b_i] = r1D0[b_partialTrueCount];
                b_partialTrueCount++;
            }
        }
        // 'calcTransition:48' curvT = constrTransP5Struct( curv1.Info, curv1.tool, R0T, ...
        // 'calcTransition:49'                              R1T, p5 );
        b_constrTransP5Struct(
            curv1->Info.TRAFO, curv1->Info.HSC, curv1->Info.FeedRate, curv1->Info.SpindleSpeed,
            curv1->Info.gcode_source_line, curv1->Info.G91, curv1->Info.G91_1, curv1->tool.toolno,
            curv1->tool.pocketno, &curv1->tool.offset, curv1->tool.diameter, curv1->tool.frontangle,
            curv1->tool.backangle, curv1->tool.orientation, R0T_data, ctx_cfg_maskTot_size[1],
            R1T_data, ctx_cfg_maskTot_size[1], p5, curvT);
        // 'calcTransition:50' curvT.Info.SpindleSpeed = min( curv1.Info.SpindleSpeed, ...
        // 'calcTransition:51'                                curv2.Info.SpindleSpeed );
        curvT->Info.SpindleSpeed = std::fmin(curv1->Info.SpindleSpeed, curv2->Info.SpindleSpeed);
        // 'calcTransition:52' curvT.Info.FeedRate     = min( curv1.Info.FeedRate, ...
        // 'calcTransition:53'                                curv2.Info.FeedRate );
        curvT->Info.FeedRate = std::fmin(curv1->Info.FeedRate, curv2->Info.FeedRate);
        // 'calcTransition:55' if( ret== 1 )
        if (c_ret == 1) {
            //  standard case
            //  transition CurvStruct calculation
            // 'calcTransition:58' status = TransitionResult.Ok;
            b_status = TransitionResult_Ok;
        } else if (c_ret == 2) {
            // 'calcTransition:59' elseif( ret == 2 )
            //  Is never set in the function !
            //  badly conditioned matrix in G2_Hermite()
            // 'calcTransition:62' status = TransitionResult.NoSolution;
            b_status = TransitionResult_NoSolution;
        } else if (c_ret == 6) {
            // 'calcTransition:63' elseif( ret == 6 )
            //  TODO: decide in the future...
            //  Now we ignore and construct the transition curve anyway
            // 'calcTransition:66' status = TransitionResult.Ok;
            b_status = TransitionResult_Ok;
        } else {
            // 'calcTransition:67' else
            // 'calcTransition:68' status = TransitionResult.NoSolution;
            b_status = TransitionResult_NoSolution;
        }
        // 'calcTransition:71' if( ( status ~= TransitionResult.NoSolution ) && ...
        // 'calcTransition:72'     ( all( p5 <= 0, 'all' ) ) )
        if (b_status != TransitionResult_NoSolution) {
            int k;
            bool c_x[6][6];
            bool exitg1;
            bool y;
            for (int c_i{0}; c_i < 6; c_i++) {
                for (int i1{0}; i1 < 6; i1++) {
                    c_x[c_i][i1] = (p5[c_i][i1] <= 0.0);
                }
            }
            y = true;
            k = 0;
            exitg1 = false;
            while ((!exitg1) && (k < 36)) {
                if (!(&c_x[0][0])[k]) {
                    y = false;
                    exitg1 = true;
                } else {
                    k++;
                }
            }
            if (y) {
                // 'calcTransition:73' status = TransitionResult.NoSolution;
                b_status = TransitionResult_NoSolution;
                // 'calcTransition:74' ret = int32( 7 );
                b_ret = 7;
            }
        }
        // 'calcTransition:77' if( status == TransitionResult.Ok )
        if (b_status == TransitionResult_Ok) {
            bool b_isValid;
            bool isValid;
            // 'calcTransition:78' isValid = check_continuity( ctx, curv1C, curvT );
            isValid = check_continuity(
                ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size, ctx_cfg_indCart,
                ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                ctx_cfg_Smoothing_ColTolCosSmooth, ctx_cfg_Smoothing_ColTolSmooth, curv1C, curvT);
            // 'calcTransition:79' isValid = isValid && check_continuity( ctx, curvT, curv2C );
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
            // 'calcTransition:80' if( ~isValid )
            if (!b_isValid) {
                // 'calcTransition:81' status = TransitionResult.NoSolution;
                b_status = TransitionResult_NoSolution;
                // 'calcTransition:82' ret = int32( 8 );
                b_ret = 8;
            }
        }
    }
    *status = b_status;
    *ret = b_ret;
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
