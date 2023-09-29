
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
#include "TransP5LengthApprox.h"
#include "calc_t_nk_kappa.h"
#include "constrTransP5Struct.h"
#include "cutCurvStruct.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "splineLength.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
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
    bool y;
    // 'calcTransition:78' tol         = ctx.cfg.Smoothing.ColTolSmooth;
    // 'calcTransition:79' tol_cos     = ctx.cfg.Smoothing.ColTolCosSmooth;
    // 'calcTransition:80' tol_kappa   = 1E-3;
    // 'calcTransition:82' [ r11, r1d1, r1dd1 ] = EvalCurvStruct( ctx, curv1, 1 );
    f_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv1, r11, r1d1, r1dd1);
    // 'calcTransition:83' [ r21, r2d1, r2dd1 ] = EvalCurvStruct( ctx, curv2, 0 );
    g_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
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
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> a__3;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r0D0;
    ::coder::array<double, 1U> r0D1;
    ::coder::array<double, 1U> r0D2;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r1D0;
    ::coder::array<double, 1U> r1D1;
    ::coder::array<double, 1U> r1D2;
    CurvStruct a__4;
    CurvStruct b_a__2;
    CurvStruct b_expl_temp;
    CurvStruct expl_temp;
    double L1;
    double L2;
    double b_a__1;
    double b_a__3;
    int ret;
    TransitionResult b_status;
    // 'calcTransition:15' coder.inline( "never" );
    // 'calcTransition:17' CutOff = ctx.cfg.CutOff;
    // 'calcTransition:18' Lcut1 = CutOff;
    // 'calcTransition:18' Lcut2 = CutOff;
    // 'calcTransition:20' L1 = LengthCurv( ctx, curv1, 0, 1 );
    // 'LengthCurv:3' if ( curv.Info.Type == CurveType.Helix ) || ( curv.Info.Type == CurveType.Line
    // )
    if ((curv1->Info.Type == CurveType_Helix) || (curv1->Info.Type == CurveType_Line)) {
        int loop_ub;
        // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
        c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv1, a__1, r1D, a__2, a__3);
        // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        r.set_size(r1D.size(0));
        loop_ub = r1D.size(0);
        for (int i{0}; i < loop_ub; i++) {
            double varargin_1;
            varargin_1 = r1D[i];
            r[i] = std::pow(varargin_1, 2.0);
        }
        L1 = std::sqrt(coder::sum(r));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
    } else if (curv1->Info.Type == CurveType_Spline) {
        // 'LengthCurv:6' elseif ( curv.Info.Type == CurveType.Spline )
        // 'LengthCurv:7' a        = curv.a_param;
        // 'LengthCurv:8' b        = curv.b_param;
        // 'LengthCurv:9' u0_tilda = a * u0 + b;
        // 'LengthCurv:10' u1_tilda = a * u1 + b;
        // 'LengthCurv:11' spline   = ctx.q_spline.get( curv.sp_index );
        ctx_q_spline->get(curv1->sp_index, &expl_temp);
        // 'LengthCurv:12' [ L ]    = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda );
        L1 = splineLength(ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, expl_temp.sp.Bl.handle,
                          expl_temp.sp.Bl.order, expl_temp.sp.coeff, expl_temp.sp.knots,
                          expl_temp.sp.Lk, curv1->b_param, curv1->a_param + curv1->b_param);
    } else if (curv1->Info.Type == CurveType_TransP5) {
        // 'LengthCurv:13' elseif ( curv.Info.Type == CurveType.TransP5 )
        // 'LengthCurv:14' L = TransP5LengthApprox( curv );
        L1 = TransP5LengthApprox(curv1);
    } else {
        // 'LengthCurv:15' else
        // 'LengthCurv:16' ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV", mfilename );
    }
    // 'calcTransition:21' L2 = LengthCurv( ctx, curv2, 0, 1 );
    // 'LengthCurv:3' if ( curv.Info.Type == CurveType.Helix ) || ( curv.Info.Type == CurveType.Line
    // )
    if ((curv2->Info.Type == CurveType_Helix) || (curv2->Info.Type == CurveType_Line)) {
        int b_loop_ub;
        // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
        c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv2, a__1, r1D, a__2, a__3);
        // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        r.set_size(r1D.size(0));
        b_loop_ub = r1D.size(0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            double b_varargin_1;
            b_varargin_1 = r1D[i1];
            r[i1] = std::pow(b_varargin_1, 2.0);
        }
        L2 = std::sqrt(coder::sum(r));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
    } else if (curv2->Info.Type == CurveType_Spline) {
        int c_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        // 'LengthCurv:6' elseif ( curv.Info.Type == CurveType.Spline )
        // 'LengthCurv:7' a        = curv.a_param;
        // 'LengthCurv:8' b        = curv.b_param;
        // 'LengthCurv:9' u0_tilda = a * u0 + b;
        // 'LengthCurv:10' u1_tilda = a * u1 + b;
        // 'LengthCurv:11' spline   = ctx.q_spline.get( curv.sp_index );
        ctx_q_spline->get(curv2->sp_index, &b_expl_temp);
        expl_temp.sp.coeff.set_size(b_expl_temp.sp.coeff.size(0), b_expl_temp.sp.coeff.size(1));
        c_loop_ub = b_expl_temp.sp.coeff.size(1);
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            int d_loop_ub;
            d_loop_ub = b_expl_temp.sp.coeff.size(0);
            for (int i3{0}; i3 < d_loop_ub; i3++) {
                expl_temp.sp.coeff[i3 + expl_temp.sp.coeff.size(0) * i2] =
                    b_expl_temp.sp.coeff[i3 + b_expl_temp.sp.coeff.size(0) * i2];
            }
        }
        expl_temp.sp.knots.set_size(1, b_expl_temp.sp.knots.size(1));
        e_loop_ub = b_expl_temp.sp.knots.size(1);
        for (int i4{0}; i4 < e_loop_ub; i4++) {
            expl_temp.sp.knots[i4] = b_expl_temp.sp.knots[i4];
        }
        expl_temp.sp.Lk.set_size(1, b_expl_temp.sp.Lk.size(1));
        f_loop_ub = b_expl_temp.sp.Lk.size(1);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            expl_temp.sp.Lk[i5] = b_expl_temp.sp.Lk[i5];
        }
        // 'LengthCurv:12' [ L ]    = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda );
        L2 = splineLength(ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, b_expl_temp.sp.Bl.handle,
                          b_expl_temp.sp.Bl.order, expl_temp.sp.coeff, expl_temp.sp.knots,
                          expl_temp.sp.Lk, curv2->b_param, curv2->a_param + curv2->b_param);
    } else if (curv2->Info.Type == CurveType_TransP5) {
        // 'LengthCurv:13' elseif ( curv.Info.Type == CurveType.TransP5 )
        // 'LengthCurv:14' L = TransP5LengthApprox( curv );
        L2 = TransP5LengthApprox(curv2);
    } else {
        // 'LengthCurv:15' else
        // 'LengthCurv:16' ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV", mfilename );
    }
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
                      curv1, L1 - ctx_cfg_CutOff, &b_a__1, curv1C, &b_a__2);
        // 'calcTransition:31' ocn_assert( check_curv_length( ctx, curv1C, L1-Lcut1 ), "Curve Length
        // not valide", mfilename ); 'calcTransition:96' tol = 1E-3; 'calcTransition:98' isValid = (
        // abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol ); 'LengthCurv:3' if ( curv.Info.Type ==
        // CurveType.Helix ) || ( curv.Info.Type == CurveType.Line )
        if ((curv1C->Info.Type == CurveType_Helix) || (curv1C->Info.Type == CurveType_Line)) {
            // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
            c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                             ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                             ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot,
                             ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot, curv1C, a__1, r1D,
                             a__2, a__3);
            // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
            // 'MyNorm:2' coder.inline('always');
            // 'MyNorm:3' n = mysqrt(sum(x.^2));
            // 'mysqrt:3' y = sqrt(x);
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
        } else if (curv1C->Info.Type == CurveType_Spline) {
            int g_loop_ub;
            int i_loop_ub;
            int j_loop_ub;
            // 'LengthCurv:6' elseif ( curv.Info.Type == CurveType.Spline )
            // 'LengthCurv:7' a        = curv.a_param;
            // 'LengthCurv:8' b        = curv.b_param;
            // 'LengthCurv:9' u0_tilda = a * u0 + b;
            // 'LengthCurv:10' u1_tilda = a * u1 + b;
            // 'LengthCurv:11' spline   = ctx.q_spline.get( curv.sp_index );
            ctx_q_spline->get(curv1C->sp_index, &b_expl_temp);
            expl_temp.sp.coeff.set_size(b_expl_temp.sp.coeff.size(0), b_expl_temp.sp.coeff.size(1));
            g_loop_ub = b_expl_temp.sp.coeff.size(1);
            for (int i6{0}; i6 < g_loop_ub; i6++) {
                int h_loop_ub;
                h_loop_ub = b_expl_temp.sp.coeff.size(0);
                for (int i7{0}; i7 < h_loop_ub; i7++) {
                    expl_temp.sp.coeff[i7 + expl_temp.sp.coeff.size(0) * i6] =
                        b_expl_temp.sp.coeff[i7 + b_expl_temp.sp.coeff.size(0) * i6];
                }
            }
            expl_temp.sp.knots.set_size(1, b_expl_temp.sp.knots.size(1));
            i_loop_ub = b_expl_temp.sp.knots.size(1);
            for (int i8{0}; i8 < i_loop_ub; i8++) {
                expl_temp.sp.knots[i8] = b_expl_temp.sp.knots[i8];
            }
            expl_temp.sp.Lk.set_size(1, b_expl_temp.sp.Lk.size(1));
            j_loop_ub = b_expl_temp.sp.Lk.size(1);
            for (int i9{0}; i9 < j_loop_ub; i9++) {
                expl_temp.sp.Lk[i9] = b_expl_temp.sp.Lk[i9];
            }
            // 'LengthCurv:12' [ L ]    = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda );
            splineLength(ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, b_expl_temp.sp.Bl.handle,
                         b_expl_temp.sp.Bl.order, expl_temp.sp.coeff, expl_temp.sp.knots,
                         expl_temp.sp.Lk, curv1C->b_param, curv1C->a_param + curv1C->b_param);
        } else if (curv1C->Info.Type == CurveType_TransP5) {
            // 'LengthCurv:13' elseif ( curv.Info.Type == CurveType.TransP5 )
            // 'LengthCurv:14' L = TransP5LengthApprox( curv );
            TransP5LengthApprox(curv1C);
        } else {
            // 'LengthCurv:15' else
            // 'LengthCurv:16' ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV", mfilename );
        }
        // 'calcTransition:32' [ ~, ~, curv2C ] = cutCurvStruct( ctx, curv2, 1, L2-Lcut2, true );
        b_cutCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                        ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                        ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                        curv2, L2 - ctx_cfg_CutOff, &b_a__3, &a__4, curv2C);
        // 'calcTransition:33' ocn_assert( check_curv_length( ctx, curv2C, L2-Lcut2 ), "Curve Length
        // not valide", mfilename ); 'calcTransition:96' tol = 1E-3; 'calcTransition:98' isValid = (
        // abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol ); 'LengthCurv:3' if ( curv.Info.Type ==
        // CurveType.Helix ) || ( curv.Info.Type == CurveType.Line )
        if ((curv2C->Info.Type == CurveType_Helix) || (curv2C->Info.Type == CurveType_Line)) {
            // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
            c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                             ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                             ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot,
                             ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot, curv2C, a__1, r1D,
                             a__2, a__3);
            // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
            // 'MyNorm:2' coder.inline('always');
            // 'MyNorm:3' n = mysqrt(sum(x.^2));
            // 'mysqrt:3' y = sqrt(x);
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
        } else if (curv2C->Info.Type == CurveType_Spline) {
            int k_loop_ub;
            int m_loop_ub;
            int n_loop_ub;
            // 'LengthCurv:6' elseif ( curv.Info.Type == CurveType.Spline )
            // 'LengthCurv:7' a        = curv.a_param;
            // 'LengthCurv:8' b        = curv.b_param;
            // 'LengthCurv:9' u0_tilda = a * u0 + b;
            // 'LengthCurv:10' u1_tilda = a * u1 + b;
            // 'LengthCurv:11' spline   = ctx.q_spline.get( curv.sp_index );
            ctx_q_spline->get(curv2C->sp_index, &b_expl_temp);
            expl_temp.sp.coeff.set_size(b_expl_temp.sp.coeff.size(0), b_expl_temp.sp.coeff.size(1));
            k_loop_ub = b_expl_temp.sp.coeff.size(1);
            for (int i10{0}; i10 < k_loop_ub; i10++) {
                int l_loop_ub;
                l_loop_ub = b_expl_temp.sp.coeff.size(0);
                for (int i11{0}; i11 < l_loop_ub; i11++) {
                    expl_temp.sp.coeff[i11 + expl_temp.sp.coeff.size(0) * i10] =
                        b_expl_temp.sp.coeff[i11 + b_expl_temp.sp.coeff.size(0) * i10];
                }
            }
            expl_temp.sp.knots.set_size(1, b_expl_temp.sp.knots.size(1));
            m_loop_ub = b_expl_temp.sp.knots.size(1);
            for (int i12{0}; i12 < m_loop_ub; i12++) {
                expl_temp.sp.knots[i12] = b_expl_temp.sp.knots[i12];
            }
            expl_temp.sp.Lk.set_size(1, b_expl_temp.sp.Lk.size(1));
            n_loop_ub = b_expl_temp.sp.Lk.size(1);
            for (int i13{0}; i13 < n_loop_ub; i13++) {
                expl_temp.sp.Lk[i13] = b_expl_temp.sp.Lk[i13];
            }
            // 'LengthCurv:12' [ L ]    = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda );
            splineLength(ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, b_expl_temp.sp.Bl.handle,
                         b_expl_temp.sp.Bl.order, expl_temp.sp.coeff, expl_temp.sp.knots,
                         expl_temp.sp.Lk, curv2C->b_param, curv2C->a_param + curv2C->b_param);
        } else if (curv2C->Info.Type == CurveType_TransP5) {
            // 'LengthCurv:13' elseif ( curv.Info.Type == CurveType.TransP5 )
            // 'LengthCurv:14' L = TransP5LengthApprox( curv );
            TransP5LengthApprox(curv2C);
        } else {
            // 'LengthCurv:15' else
            // 'LengthCurv:16' ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV", mfilename );
        }
        // 'calcTransition:35' [r0D0, r0D1, r0D2] = EvalCurvStruct( ctx, curv1C, 1 );
        f_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv1C, r0D0, r0D1, r0D2);
        // 'calcTransition:36' [r1D0, r1D1, r1D2] = EvalCurvStruct( ctx, curv2C, 0 );
        g_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
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
            for (int i14{0}; i14 < 6; i14++) {
                for (int i15{0}; i15 < 6; i15++) {
                    x[i14][i15] = (p5[i14][i15] <= 0.0);
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
