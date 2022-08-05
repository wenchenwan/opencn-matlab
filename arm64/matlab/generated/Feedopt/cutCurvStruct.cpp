//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:02:16
//

// Include Files
#include "cutCurvStruct.h"
#include "EvalBSpline.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "find.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// function [ ret, curv1, curv2 ] = cutCurvStruct( ctx, curv, u0, L, isEnd )
//
// cutCurvStruct: Cut a piece of the structure with a size of L
//  starting at point u0
//  Inputs :
//  ctx   : Context
//  curv  : Curvature
//  u0    : Starting point of the spline
//  L     : Length of the segment of curv
//  isEnd : Is a zero stop curv
//  Outputs :
//  u1    : The last point of the splitted curv
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
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *curv
//                double L
//                double *ret
//                CurvStruct *curv1
//                CurvStruct *curv2
// Return Type  : void
//
namespace ocn {
void b_cutCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                     const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                     const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                     const int ctx_cfg_maskRot_size[2],
                     const ::coder::array<int, 1U> &ctx_cfg_indCart,
                     const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                     int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_GaussLegendreX[5],
                     const double ctx_cfg_GaussLegendreW[5], const CurvStruct *curv, double L,
                     double *ret, CurvStruct *curv1, CurvStruct *curv2)
{
    ::coder::array<double, 2U> Knots;
    ::coder::array<double, 2U> LEnd;
    ::coder::array<double, 2U> Lk;
    ::coder::array<double, 2U> b_a__1;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D1;
    ::coder::array<bool, 2U> b_Knots;
    ::coder::array<bool, 2U> b_LEnd;
    CurvStruct expl_temp;
    double dv[5];
    double r1Dnorm[5];
    double u_tilda;
    int LkEndVec_size[2];
    int LkEndVec_data;
    int b_ret;
    int kStartVec_data;
    // 'cutCurvStruct:12' curv1 = curv;
    *curv1 = *curv;
    // 'cutCurvStruct:12' curv2 = curv1;
    *curv2 = *curv;
    // 'cutCurvStruct:13' ret   = 0;
    b_ret = 0;
    // 'cutCurvStruct:15' u_tilda = cutCurvStructU( ctx, curv, u0, L, isEnd );
    //  cutCurvStructU: Cut a piece of the structure with a size of L
    //  starting at point u0
    //  Inputs :
    //  ctx   : Context
    //  curv  : Curvature
    //  u0    : Starting point of the spline
    //  L     : Length of the segment of curv
    //  isEnd : Is a cut from the end
    //  Outputs :
    //  u1    : The last point of the splitted curv
    // 'cutCurvStructU:13' if( L <= 1E-6 )
    if (L <= 1.0E-6) {
        // 'cutCurvStructU:14' disp( "here" );
        printf("%s\n", "here");
        fflush(stdout);
    }
    // 'cutCurvStructU:17' if( LengthCurv( ctx, curv, 0, 1 ) <= L )
    if (LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                   ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                   ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                   ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv) <= L) {
        // 'cutCurvStructU:17' u1_tilda = -1;
        u_tilda = -1.0;

        // 'cutCurvStructU:19' a = curv.a_param;
        // 'cutCurvStructU:20' b = curv.b_param;
        // 'cutCurvStructU:22' if ( curv.Info.Type == CurveType.Spline )
    } else if (curv->Info.Type == CurveType_Spline) {
        double LStart;
        double d;
        double u0;
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i1;
        int i2;
        int i3;
        int i8;
        int i9;
        // 'cutCurvStructU:23' spline = ctx.q_spline.get( curv.sp_index );
        ctx_q_spline->get(curv->sp_index, &expl_temp);
        // 'cutCurvStructU:24' u1_tilda = splineLengthFindU( ctx.cfg, spline, L, a * u0 + b, isEnd
        // );
        //  Computes approximately the value of curve parameter u such that the arc
        //  length starting from u1 equals L.
        //  This function takes usage of the precalculated arc lengths between knots.
        //  The last integration interval is approximated by the trapezoidal rule.
        //  u1 must satisfy 0 < u1 < 1.
        //  In the normal case, u must satisfy 0 < u < u1. If L is too large, u is
        //  set to -1.
        //  The parameter isEnd is used to start inverse the problem, the length is
        //  estimated starting from u quals to 1 to 0. It's used to cut a specific
        //  length at the beginning of the curv.
        // 'splineLengthFindU:13' ITER_MAX    = 1000;
        // 'splineLengthFindU:14' DEFAULT_TOL = 1E-7;
        //  Get the sp structure
        // 'splineLengthFindU:17' sp     = spline.sp;
        // 'splineLengthFindU:19' IND_KNOTS_MULT  = sp.Bl.order;
        //  Index used to remove multiple knots
        //  Eliminate multiplicities at the end points
        // 'splineLengthFindU:21' Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
        i1 = (expl_temp.sp.knots.size(1) - expl_temp.sp.Bl.order) + 1;
        if (expl_temp.sp.Bl.order > i1) {
            i2 = 0;
            i3 = 0;
        } else {
            i2 = expl_temp.sp.Bl.order - 1;
            i3 = i1;
        }
        // 'splineLengthFindU:22' Lk     = sp.Lk;
        // 'splineLengthFindU:23' kMax   = numel( Lk );
        // 'splineLengthFindU:25' if( isEnd )
        // 'splineLengthFindU:26' u0      = 1 - u0;
        u0 = 1.0 - (curv->a_param + curv->b_param);
        // 'splineLengthFindU:27' Knots   = flip( 1 - Knots );
        b_loop_ub = i3 - i2;
        Knots.set_size(1, b_loop_ub);
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            Knots[i4] = 1.0 - expl_temp.sp.knots[i2 + i4];
        }
        if ((Knots.size(1) != 0) && (Knots.size(1) > 1)) {
            int lup;
            lup = Knots.size(1) >> 1;
            for (int k{0}; k < lup; k++) {
                double tmp;
                int subs2_idx_1;
                subs2_idx_1 = Knots.size(1) - k;
                tmp = Knots[k];
                Knots[k] = Knots[subs2_idx_1 - 1];
                Knots[subs2_idx_1 - 1] = tmp;
            }
        }
        // 'splineLengthFindU:28' Lk      = flip( Lk );
        Lk.set_size(1, expl_temp.sp.Lk.size(1));
        c_loop_ub = expl_temp.sp.Lk.size(1);
        for (int i5{0}; i5 < c_loop_ub; i5++) {
            Lk[i5] = expl_temp.sp.Lk[i5];
        }
        if ((expl_temp.sp.Lk.size(1) != 0) && (expl_temp.sp.Lk.size(1) > 1)) {
            int b_lup;
            b_lup = expl_temp.sp.Lk.size(1) >> 1;
            for (int b_k{0}; b_k < b_lup; b_k++) {
                double b_tmp;
                int b_subs2_idx_1;
                b_subs2_idx_1 = Lk.size(1) - b_k;
                b_tmp = Lk[b_k];
                Lk[b_k] = Lk[b_subs2_idx_1 - 1];
                Lk[b_subs2_idx_1 - 1] = b_tmp;
            }
        }
        // 'splineLengthFindU:31' C_ASSERT_MSG = 'u0 must be %s or equal than the first spline
        // knot'; 'splineLengthFindU:32' assert( u0 >= Knots(1),   sprintf(C_ASSERT_MSG, 'greater')
        // ); 'splineLengthFindU:33' assert( u0 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller') );
        // 'splineLengthFindU:35' kStartVec = find( Knots <= u0, 1, "last" );
        b_Knots.set_size(1, Knots.size(1));
        d_loop_ub = Knots.size(1);
        for (int i6{0}; i6 < d_loop_ub; i6++) {
            b_Knots[i6] = (Knots[i6] <= u0);
        }
        coder::eml_find(b_Knots, (int *)&LkEndVec_data, LkEndVec_size);
        e_loop_ub = LkEndVec_size[1];
        for (int i7{0}; i7 < e_loop_ub; i7++) {
            kStartVec_data = LkEndVec_data;
        }
        // 'splineLengthFindU:36' kStart    = kStartVec( 1 );
        // 'splineLengthFindU:38' if( Knots( kStart ) < u0 )
        d = Knots[kStartVec_data - 1];
        if (d < u0) {
            double b_r1Dnorm;
            int i_loop_ub;
            // 'splineLengthFindU:39' LStart = splineLengthApprox_Interval( cfg, spline, Knots(
            // kStart ), u0, isEnd );
            //  computes approximately the arc length L with integration bounds u1 and u2.
            //  IMPORTANT : u0 and u1 should lie in the same knot interval.
            //  The computation is based on numerical Gauss Legendre integration
            //
            //  get Gauss-Legendre knots and weights
            // 'splineLengthApprox_Interval:7' GL_X   = cfg.GaussLegendreX;
            // 'splineLengthApprox_Interval:8' GL_W   = cfg.GaussLegendreW;
            // 'splineLengthApprox_Interval:10' if( isEnd )
            // 'splineLengthApprox_Interval:11' a   = 1 - u0;
            // 'splineLengthApprox_Interval:12' u0  = 1 - u1;
            // 'splineLengthApprox_Interval:13' u1  = a;
            //  apply linear map from[-1, 1] to [u0, u1]
            // 'splineLengthApprox_Interval:17' uvec   = ( ( u0 * ( 1 - GL_X ) + u1 * ( 1 + GL_X ) )
            // / 2 ).';
            //
            // 'splineLengthApprox_Interval:20' [ ~, r1D ]  = EvalBSpline( spline, uvec );
            for (int i11{0}; i11 < 5; i11++) {
                double d1;
                d1 = ctx_cfg_GaussLegendreX[i11];
                dv[i11] = ((1.0 - u0) * (1.0 - d1) + (1.0 - d) * (d1 + 1.0)) / 2.0;
            }
            EvalBSpline(expl_temp.sp.Bl.handle, expl_temp.sp.coeff, dv, b_a__1, r1D);
            // 'splineLengthApprox_Interval:21' r1Dnorm     = MyNorm( r1D );
            // 'MyNorm:2' coder.inline('always');
            // 'MyNorm:3' n = mysqrt(sum(x.^2));
            r1.set_size(r1D.size(0), 5);
            i_loop_ub = r1D.size(0);
            for (int i14{0}; i14 < 5; i14++) {
                for (int i15{0}; i15 < i_loop_ub; i15++) {
                    double b_varargin_1;
                    b_varargin_1 = r1D[i15 + r1D.size(0) * i14];
                    r1[i15 + r1.size(0) * i14] = std::pow(b_varargin_1, 2.0);
                }
            }
            coder::sum(r1, r1Dnorm);
            // 'mysqrt:3' y = sqrt(x);
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
            // 'splineLengthApprox_Interval:22' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
            b_r1Dnorm = 0.0;
            for (int d_k{0}; d_k < 5; d_k++) {
                double d2;
                d2 = std::sqrt(r1Dnorm[d_k]);
                r1Dnorm[d_k] = d2;
                b_r1Dnorm += d2 * ctx_cfg_GaussLegendreW[d_k];
            }
            LStart = b_r1Dnorm * ((1.0 - d) - (1.0 - u0)) / 2.0;
            //  Gauss Legendre integration
            // 'splineLengthApprox_Interval:23' L = L( 1 );
            //  to satisfy Matlab Coder
        } else {
            // 'splineLengthFindU:40' else
            // 'splineLengthFindU:41' LStart = 0;
            LStart = 0.0;
        }
        // 'splineLengthFindU:44' LEnd = cumsum( Lk( kStart : kMax) ) - LStart;
        if (kStartVec_data > expl_temp.sp.Lk.size(1)) {
            i8 = -1;
            i9 = -1;
        } else {
            i8 = kStartVec_data - 2;
            i9 = expl_temp.sp.Lk.size(1) - 1;
        }
        f_loop_ub = i9 - i8;
        x.set_size(1, f_loop_ub);
        for (int i10{0}; i10 < f_loop_ub; i10++) {
            x[i10] = Lk[(i8 + i10) + 1];
        }
        if ((f_loop_ub != 0) && (f_loop_ub != 1)) {
            for (int c_k{0}; c_k <= f_loop_ub - 2; c_k++) {
                x[c_k + 1] = x[c_k] + x[c_k + 1];
            }
        }
        LEnd.set_size(1, x.size(1));
        g_loop_ub = x.size(1);
        for (int i12{0}; i12 < g_loop_ub; i12++) {
            LEnd[i12] = x[i12] - LStart;
        }
        // 'splineLengthFindU:46' LkEndVec = find( LEnd >= L, 1, "first" );
        b_LEnd.set_size(1, LEnd.size(1));
        h_loop_ub = LEnd.size(1);
        for (int i13{0}; i13 < h_loop_ub; i13++) {
            b_LEnd[i13] = (LEnd[i13] >= L);
        }
        coder::b_eml_find(b_LEnd, (int *)&LkEndVec_data, LkEndVec_size);
        // 'splineLengthFindU:47' if( isempty( LkEndVec ) )
        if (LkEndVec_size[1] == 0) {
            // 'splineLengthFindU:48' u = -1;
            u_tilda = -1.0;
        } else {
            double LDiff;
            double fk;
            double kEnd;
            double u;
            double uLeft;
            double uMiddle;
            double uRight;
            double uRight_tmp;
            double uStart_tmp;
            int count;
            // 'splineLengthFindU:49' else
            // 'splineLengthFindU:50' LkEnd    = LkEndVec( 1 );
            // 'splineLengthFindU:51' if( LkEnd > 1 )
            if (LkEndVec_data > 1) {
                // 'splineLengthFindU:52' LDiff = L - LEnd( LkEnd - 1 );
                LDiff = L - LEnd[LkEndVec_data - 2];
            } else {
                // 'splineLengthFindU:53' else
                // 'splineLengthFindU:54' LDiff = L + LStart;
                LDiff = L + LStart;
            }
            // 'splineLengthFindU:58' kEnd = LkEnd + kStart;
            kEnd = static_cast<double>(LkEndVec_data) + static_cast<double>(kStartVec_data);
            // 'splineLengthFindU:60' uLeft       = Knots( kEnd -1 );
            uLeft = Knots[static_cast<int>(kEnd - 1.0) - 1];
            // 'splineLengthFindU:61' uRight      = Knots( kEnd );
            uRight_tmp = Knots[static_cast<int>(kEnd) - 1];
            uRight = uRight_tmp;
            // 'splineLengthFindU:63' [ u, count ] = bisection( uLeft, uRight, cfg, spline, LDiff,
            // ITER_MAX, DEFAULT_TOL, isEnd );
            // -------------------------------------------------------------------------%
            //  Functions
            // -------------------------------------------------------------------------%
            // 'splineLengthFindU:78' count   = 0;
            count = 0;
            // 'splineLengthFindU:79' uStart  = uLeft;
            uStart_tmp = Knots[static_cast<int>(kEnd) - 2];
            // 'splineLengthFindU:80' fk      = tol * 1.1;
            fk = 1.1E-7;
            // 'splineLengthFindU:82' uMiddle = ( uLeft + uRight ) / 2;
            uMiddle = (uStart_tmp + uRight_tmp) / 2.0;
            // 'splineLengthFindU:84' while( count < iterMax && abs( fk ) > tol )
            while ((count < 1000) && (std::abs(fk) > 1.0E-7)) {
                double c_r1Dnorm;
                int j_loop_ub;
                // 'splineLengthFindU:85' uMiddle = ( uLeft + uRight ) / 2;
                uMiddle = (uLeft + uRight) / 2.0;
                // 'splineLengthFindU:87' fk  = splineLengthApprox_Interval( cfg, spline, uStart,
                // uMiddle, isEnd ) - LDiff;
                //  computes approximately the arc length L with integration bounds u1 and u2.
                //  IMPORTANT : u0 and u1 should lie in the same knot interval.
                //  The computation is based on numerical Gauss Legendre integration
                //
                //  get Gauss-Legendre knots and weights
                // 'splineLengthApprox_Interval:7' GL_X   = cfg.GaussLegendreX;
                // 'splineLengthApprox_Interval:8' GL_W   = cfg.GaussLegendreW;
                // 'splineLengthApprox_Interval:10' if( isEnd )
                // 'splineLengthApprox_Interval:11' a   = 1 - u0;
                // 'splineLengthApprox_Interval:12' u0  = 1 - u1;
                // 'splineLengthApprox_Interval:13' u1  = a;
                //  apply linear map from[-1, 1] to [u0, u1]
                // 'splineLengthApprox_Interval:17' uvec   = ( ( u0 * ( 1 - GL_X ) + u1 * ( 1 + GL_X
                // ) ) / 2 ).';
                //
                // 'splineLengthApprox_Interval:20' [ ~, r1D ]  = EvalBSpline( spline, uvec );
                for (int i16{0}; i16 < 5; i16++) {
                    double d3;
                    d3 = ctx_cfg_GaussLegendreX[i16];
                    dv[i16] =
                        ((1.0 - uMiddle) * (1.0 - d3) + (1.0 - uStart_tmp) * (d3 + 1.0)) / 2.0;
                }
                EvalBSpline(expl_temp.sp.Bl.handle, expl_temp.sp.coeff, dv, b_a__1, r1D);
                // 'splineLengthApprox_Interval:21' r1Dnorm     = MyNorm( r1D );
                // 'MyNorm:2' coder.inline('always');
                // 'MyNorm:3' n = mysqrt(sum(x.^2));
                r1.set_size(r1D.size(0), 5);
                j_loop_ub = r1D.size(0);
                for (int i17{0}; i17 < 5; i17++) {
                    for (int i18{0}; i18 < j_loop_ub; i18++) {
                        double c_varargin_1;
                        c_varargin_1 = r1D[i18 + r1D.size(0) * i17];
                        r1[i18 + r1.size(0) * i17] = std::pow(c_varargin_1, 2.0);
                    }
                }
                coder::sum(r1, r1Dnorm);
                // 'mysqrt:3' y = sqrt(x);
                // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                sqrt_calls++;
                // 'splineLengthApprox_Interval:22' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
                //  Gauss Legendre integration
                // 'splineLengthApprox_Interval:23' L = L( 1 );
                //  to satisfy Matlab Coder
                c_r1Dnorm = 0.0;
                for (int e_k{0}; e_k < 5; e_k++) {
                    double d4;
                    d4 = std::sqrt(r1Dnorm[e_k]);
                    r1Dnorm[e_k] = d4;
                    c_r1Dnorm += d4 * ctx_cfg_GaussLegendreW[e_k];
                }
                fk = c_r1Dnorm * ((1.0 - uStart_tmp) - (1.0 - uMiddle)) / 2.0 - LDiff;
                // 'splineLengthFindU:89' if( fk > 0 )
                if (fk > 0.0) {
                    // 'splineLengthFindU:90' uRight = uMiddle;
                    uRight = uMiddle;
                } else {
                    // 'splineLengthFindU:91' else
                    // 'splineLengthFindU:92' uLeft  = uMiddle;
                    uLeft = uMiddle;
                }
                // 'splineLengthFindU:94' count = count + 1;
                count++;
            }
            // 'splineLengthFindU:97' if( count >= iterMax )
            if (count >= 1000) {
                // 'splineLengthFindU:98' u = -1;
                u = -1.0;
            } else {
                // 'splineLengthFindU:99' else
                // 'splineLengthFindU:100' u = uMiddle;
                u = uMiddle;
            }
            u_tilda = u;
            // 'splineLengthFindU:65' if( u < 0 )
            // 'splineLengthFindU:67' if( isEnd && u >= 0 )
            if (u >= 0.0) {
                // 'splineLengthFindU:68' u = 1 -u;
                u_tilda = 1.0 - u;
            }
        }
    } else {
        int loop_ub;
        // 'cutCurvStructU:25' else
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        // 'cutCurvStructU:29' if( isEnd )
        // 'cutCurvStructU:30' [ ~, r1D1 ] = EvalCurvStruct( ctx, curv, 1 );
        b_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, a__1, r1D1);
        // 'cutCurvStructU:31' u1 = u0 - L / MyNorm( r1D1 );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'cutCurvStructU:36' u1_tilda = a * u1 + b;
        r.set_size(r1D1.size(0));
        loop_ub = r1D1.size(0);
        for (int i{0}; i < loop_ub; i++) {
            double varargin_1;
            varargin_1 = r1D1[i];
            r[i] = std::pow(varargin_1, 2.0);
        }
        u_tilda = curv->a_param * (1.0 - L / std::sqrt(coder::sum(r))) + curv->b_param;
    }
    // 'cutCurvStruct:17' if( u_tilda <= 0 )
    if (u_tilda <= 0.0) {
        // 'cutCurvStruct:17' ret = -1;
        b_ret = -1;
    } else {
        // 'cutCurvStruct:19' a = curv.a_param;
        // 'cutCurvStruct:20' b = curv.b_param;
        // 'cutCurvStruct:22' curv2.b_param = u_tilda;
        curv2->b_param = u_tilda;
        // 'cutCurvStruct:23' curv2.a_param = a + b - curv2.b_param;
        curv2->a_param = (curv->a_param + curv->b_param) - u_tilda;
        // 'cutCurvStruct:25' if( isAZeroEnd( curv2 ) )
        //  isAZeroEnd : Return true if the curv ends with zero speed
        //  Input :
        //  curv  : The curve struct
        // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
        // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
        if ((curv->Info.zspdmode == ZSpdMode_NZ) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroEnd:7' zeroFlag = true;
            // 'cutCurvStruct:26' curv2.Info.zspdmode = ZSpdMode.NZ;
            curv2->Info.zspdmode = ZSpdMode_NZ;
        } else {
            // 'isAZeroEnd:9' zeroFlag = false;
            // 'cutCurvStruct:27' else
            // 'cutCurvStruct:28' curv2.Info.zspdmode = ZSpdMode.NN;
            curv2->Info.zspdmode = ZSpdMode_NN;
        }
        // 'cutCurvStruct:31' curv1.a_param = u_tilda - curv1.b_param;
        curv1->a_param = u_tilda - curv->b_param;
        // 'cutCurvStruct:32' if( isAZeroStart( curv1 ) )
        //  isAZeroStart : Return true if the curv starts with zero speed
        //  curv  : The curve struct
        // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
        // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
        if ((curv->Info.zspdmode == ZSpdMode_ZN) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroStart:6' zeroFlag = true;
            // 'cutCurvStruct:33' curv1.Info.zspdmode = ZSpdMode.ZN;
            curv1->Info.zspdmode = ZSpdMode_ZN;
        } else {
            // 'isAZeroStart:8' zeroFlag = false;
            // 'cutCurvStruct:34' else
            // 'cutCurvStruct:35' curv1.Info.zspdmode = ZSpdMode.NN;
            curv1->Info.zspdmode = ZSpdMode_NN;
        }
    }
    *ret = b_ret;
}

//
// function [ ret, curv1, curv2 ] = cutCurvStruct( ctx, curv, u0, L, isEnd )
//
// cutCurvStruct: Cut a piece of the structure with a size of L
//  starting at point u0
//  Inputs :
//  ctx   : Context
//  curv  : Curvature
//  u0    : Starting point of the spline
//  L     : Length of the segment of curv
//  isEnd : Is a zero stop curv
//  Outputs :
//  u1    : The last point of the splitted curv
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
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *curv
//                double L
//                double *ret
//                CurvStruct *curv1
//                CurvStruct *curv2
// Return Type  : void
//
void cutCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                   const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                   const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                   const int ctx_cfg_maskRot_size[2],
                   const ::coder::array<int, 1U> &ctx_cfg_indCart,
                   const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                   int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_GaussLegendreX[5],
                   const double ctx_cfg_GaussLegendreW[5], const CurvStruct *curv, double L,
                   double *ret, CurvStruct *curv1, CurvStruct *curv2)
{
    ::coder::array<double, 2U> LEnd;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D0;
    ::coder::array<bool, 2U> b_LEnd;
    ::coder::array<bool, 2U> b_expl_temp;
    CurvStruct expl_temp;
    double b_uStart[5];
    double d_expl_temp[5];
    double r1Dnorm[5];
    double u_tilda;
    int LkEndVec_size[2];
    int LkEndVec_data;
    int b_ret;
    int kStartVec_data;
    // 'cutCurvStruct:12' curv1 = curv;
    *curv1 = *curv;
    // 'cutCurvStruct:12' curv2 = curv1;
    *curv2 = *curv;
    // 'cutCurvStruct:13' ret   = 0;
    b_ret = 0;
    // 'cutCurvStruct:15' u_tilda = cutCurvStructU( ctx, curv, u0, L, isEnd );
    //  cutCurvStructU: Cut a piece of the structure with a size of L
    //  starting at point u0
    //  Inputs :
    //  ctx   : Context
    //  curv  : Curvature
    //  u0    : Starting point of the spline
    //  L     : Length of the segment of curv
    //  isEnd : Is a cut from the end
    //  Outputs :
    //  u1    : The last point of the splitted curv
    // 'cutCurvStructU:13' if( L <= 1E-6 )
    if (L <= 1.0E-6) {
        // 'cutCurvStructU:14' disp( "here" );
        printf("%s\n", "here");
        fflush(stdout);
    }
    // 'cutCurvStructU:17' if( LengthCurv( ctx, curv, 0, 1 ) <= L )
    if (LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                   ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                   ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                   ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv) <= L) {
        // 'cutCurvStructU:17' u1_tilda = -1;
        u_tilda = -1.0;

        // 'cutCurvStructU:19' a = curv.a_param;
        // 'cutCurvStructU:20' b = curv.b_param;
        // 'cutCurvStructU:22' if ( curv.Info.Type == CurveType.Spline )
    } else if (curv->Info.Type == CurveType_Spline) {
        double LStart;
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int i1;
        int i2;
        int i3;
        int i6;
        int i7;
        int i8;
        // 'cutCurvStructU:23' spline = ctx.q_spline.get( curv.sp_index );
        ctx_q_spline->get(curv->sp_index, &expl_temp);
        // 'cutCurvStructU:24' u1_tilda = splineLengthFindU( ctx.cfg, spline, L, a * u0 + b, isEnd
        // );
        //  Computes approximately the value of curve parameter u such that the arc
        //  length starting from u1 equals L.
        //  This function takes usage of the precalculated arc lengths between knots.
        //  The last integration interval is approximated by the trapezoidal rule.
        //  u1 must satisfy 0 < u1 < 1.
        //  In the normal case, u must satisfy 0 < u < u1. If L is too large, u is
        //  set to -1.
        //  The parameter isEnd is used to start inverse the problem, the length is
        //  estimated starting from u quals to 1 to 0. It's used to cut a specific
        //  length at the beginning of the curv.
        // 'splineLengthFindU:13' ITER_MAX    = 1000;
        // 'splineLengthFindU:14' DEFAULT_TOL = 1E-7;
        //  Get the sp structure
        // 'splineLengthFindU:17' sp     = spline.sp;
        // 'splineLengthFindU:19' IND_KNOTS_MULT  = sp.Bl.order;
        //  Index used to remove multiple knots
        //  Eliminate multiplicities at the end points
        // 'splineLengthFindU:21' Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
        i1 = (expl_temp.sp.knots.size(1) - expl_temp.sp.Bl.order) + 1;
        if (expl_temp.sp.Bl.order > i1) {
            i2 = -1;
            i3 = -2;
        } else {
            i2 = expl_temp.sp.Bl.order - 2;
            i3 = i1 - 2;
        }
        // 'splineLengthFindU:22' Lk     = sp.Lk;
        // 'splineLengthFindU:23' kMax   = numel( Lk );
        // 'splineLengthFindU:25' if( isEnd )
        // 'splineLengthFindU:31' C_ASSERT_MSG = 'u0 must be %s or equal than the first spline
        // knot'; 'splineLengthFindU:32' assert( u0 >= Knots(1),   sprintf(C_ASSERT_MSG, 'greater')
        // ); 'splineLengthFindU:33' assert( u0 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller') );
        // 'splineLengthFindU:35' kStartVec = find( Knots <= u0, 1, "last" );
        b_loop_ub = i3 - i2;
        b_expl_temp.set_size(1, b_loop_ub + 1);
        for (int i4{0}; i4 <= b_loop_ub; i4++) {
            b_expl_temp[i4] = (expl_temp.sp.knots[(i2 + i4) + 1] <= curv->b_param);
        }
        coder::eml_find(b_expl_temp, (int *)&LkEndVec_data, LkEndVec_size);
        c_loop_ub = LkEndVec_size[1];
        for (int i5{0}; i5 < c_loop_ub; i5++) {
            kStartVec_data = LkEndVec_data;
        }
        // 'splineLengthFindU:36' kStart    = kStartVec( 1 );
        // 'splineLengthFindU:38' if( Knots( kStart ) < u0 )
        i6 = i2 + kStartVec_data;
        if (expl_temp.sp.knots[i6] < curv->b_param) {
            double b_r1Dnorm;
            double c_expl_temp;
            int g_loop_ub;
            // 'splineLengthFindU:39' LStart = splineLengthApprox_Interval( cfg, spline, Knots(
            // kStart ), u0, isEnd );
            //  computes approximately the arc length L with integration bounds u1 and u2.
            //  IMPORTANT : u0 and u1 should lie in the same knot interval.
            //  The computation is based on numerical Gauss Legendre integration
            //
            //  get Gauss-Legendre knots and weights
            // 'splineLengthApprox_Interval:7' GL_X   = cfg.GaussLegendreX;
            // 'splineLengthApprox_Interval:8' GL_W   = cfg.GaussLegendreW;
            // 'splineLengthApprox_Interval:10' if( isEnd )
            //  apply linear map from[-1, 1] to [u0, u1]
            // 'splineLengthApprox_Interval:17' uvec   = ( ( u0 * ( 1 - GL_X ) + u1 * ( 1 + GL_X ) )
            // / 2 ).';
            //
            // 'splineLengthApprox_Interval:20' [ ~, r1D ]  = EvalBSpline( spline, uvec );
            c_expl_temp = expl_temp.sp.knots[i6];
            for (int i10{0}; i10 < 5; i10++) {
                double d;
                d = ctx_cfg_GaussLegendreX[i10];
                d_expl_temp[i10] = (c_expl_temp * (1.0 - d) + curv->b_param * (d + 1.0)) / 2.0;
            }
            EvalBSpline(expl_temp.sp.Bl.handle, expl_temp.sp.coeff, d_expl_temp, a__1, r1D);
            // 'splineLengthApprox_Interval:21' r1Dnorm     = MyNorm( r1D );
            // 'MyNorm:2' coder.inline('always');
            // 'MyNorm:3' n = mysqrt(sum(x.^2));
            r1.set_size(r1D.size(0), 5);
            g_loop_ub = r1D.size(0);
            for (int i13{0}; i13 < 5; i13++) {
                for (int i14{0}; i14 < g_loop_ub; i14++) {
                    double b_varargin_1;
                    b_varargin_1 = r1D[i14 + r1D.size(0) * i13];
                    r1[i14 + r1.size(0) * i13] = std::pow(b_varargin_1, 2.0);
                }
            }
            coder::sum(r1, r1Dnorm);
            // 'mysqrt:3' y = sqrt(x);
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
            // 'splineLengthApprox_Interval:22' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
            b_r1Dnorm = 0.0;
            for (int b_k{0}; b_k < 5; b_k++) {
                double d1;
                d1 = std::sqrt(r1Dnorm[b_k]);
                r1Dnorm[b_k] = d1;
                b_r1Dnorm += d1 * ctx_cfg_GaussLegendreW[b_k];
            }
            LStart = b_r1Dnorm * (curv->b_param - expl_temp.sp.knots[i6]) / 2.0;
            //  Gauss Legendre integration
            // 'splineLengthApprox_Interval:23' L = L( 1 );
            //  to satisfy Matlab Coder
        } else {
            // 'splineLengthFindU:40' else
            // 'splineLengthFindU:41' LStart = 0;
            LStart = 0.0;
        }
        // 'splineLengthFindU:44' LEnd = cumsum( Lk( kStart : kMax) ) - LStart;
        if (kStartVec_data > expl_temp.sp.Lk.size(1)) {
            i7 = -1;
            i8 = -1;
        } else {
            i7 = kStartVec_data - 2;
            i8 = expl_temp.sp.Lk.size(1) - 1;
        }
        d_loop_ub = i8 - i7;
        x.set_size(1, d_loop_ub);
        for (int i9{0}; i9 < d_loop_ub; i9++) {
            x[i9] = expl_temp.sp.Lk[(i7 + i9) + 1];
        }
        if ((d_loop_ub != 0) && (d_loop_ub != 1)) {
            for (int k{0}; k <= d_loop_ub - 2; k++) {
                x[k + 1] = x[k] + x[k + 1];
            }
        }
        LEnd.set_size(1, x.size(1));
        e_loop_ub = x.size(1);
        for (int i11{0}; i11 < e_loop_ub; i11++) {
            LEnd[i11] = x[i11] - LStart;
        }
        // 'splineLengthFindU:46' LkEndVec = find( LEnd >= L, 1, "first" );
        b_LEnd.set_size(1, LEnd.size(1));
        f_loop_ub = LEnd.size(1);
        for (int i12{0}; i12 < f_loop_ub; i12++) {
            b_LEnd[i12] = (LEnd[i12] >= L);
        }
        coder::b_eml_find(b_LEnd, (int *)&LkEndVec_data, LkEndVec_size);
        // 'splineLengthFindU:47' if( isempty( LkEndVec ) )
        if (LkEndVec_size[1] == 0) {
            // 'splineLengthFindU:48' u = -1;
            u_tilda = -1.0;
        } else {
            double LDiff;
            double fk;
            double kEnd;
            double uLeft;
            double uMiddle;
            double uRight;
            double uStart;
            int count;
            int uRight_tmp;
            // 'splineLengthFindU:49' else
            // 'splineLengthFindU:50' LkEnd    = LkEndVec( 1 );
            // 'splineLengthFindU:51' if( LkEnd > 1 )
            if (LkEndVec_data > 1) {
                // 'splineLengthFindU:52' LDiff = L - LEnd( LkEnd - 1 );
                LDiff = L - LEnd[LkEndVec_data - 2];
            } else {
                // 'splineLengthFindU:53' else
                // 'splineLengthFindU:54' LDiff = L + LStart;
                LDiff = L + LStart;
            }
            // 'splineLengthFindU:58' kEnd = LkEnd + kStart;
            kEnd = static_cast<double>(LkEndVec_data) + static_cast<double>(kStartVec_data);
            // 'splineLengthFindU:60' uLeft       = Knots( kEnd -1 );
            uLeft = expl_temp.sp.knots[i2 + static_cast<int>(kEnd - 1.0)];
            // 'splineLengthFindU:61' uRight      = Knots( kEnd );
            uRight_tmp = i2 + static_cast<int>(kEnd);
            uRight = expl_temp.sp.knots[uRight_tmp];
            // 'splineLengthFindU:63' [ u, count ] = bisection( uLeft, uRight, cfg, spline, LDiff,
            // ITER_MAX, DEFAULT_TOL, isEnd );
            // -------------------------------------------------------------------------%
            //  Functions
            // -------------------------------------------------------------------------%
            // 'splineLengthFindU:78' count   = 0;
            count = 0;
            // 'splineLengthFindU:79' uStart  = uLeft;
            uStart = expl_temp.sp.knots[uRight_tmp - 1];
            // 'splineLengthFindU:80' fk      = tol * 1.1;
            fk = 1.1E-7;
            // 'splineLengthFindU:82' uMiddle = ( uLeft + uRight ) / 2;
            uMiddle = (expl_temp.sp.knots[uRight_tmp - 1] + expl_temp.sp.knots[uRight_tmp]) / 2.0;
            // 'splineLengthFindU:84' while( count < iterMax && abs( fk ) > tol )
            while ((count < 1000) && (std::abs(fk) > 1.0E-7)) {
                double c_r1Dnorm;
                int h_loop_ub;
                // 'splineLengthFindU:85' uMiddle = ( uLeft + uRight ) / 2;
                uMiddle = (uLeft + uRight) / 2.0;
                // 'splineLengthFindU:87' fk  = splineLengthApprox_Interval( cfg, spline, uStart,
                // uMiddle, isEnd ) - LDiff;
                //  computes approximately the arc length L with integration bounds u1 and u2.
                //  IMPORTANT : u0 and u1 should lie in the same knot interval.
                //  The computation is based on numerical Gauss Legendre integration
                //
                //  get Gauss-Legendre knots and weights
                // 'splineLengthApprox_Interval:7' GL_X   = cfg.GaussLegendreX;
                // 'splineLengthApprox_Interval:8' GL_W   = cfg.GaussLegendreW;
                // 'splineLengthApprox_Interval:10' if( isEnd )
                //  apply linear map from[-1, 1] to [u0, u1]
                // 'splineLengthApprox_Interval:17' uvec   = ( ( u0 * ( 1 - GL_X ) + u1 * ( 1 + GL_X
                // ) ) / 2 ).';
                //
                // 'splineLengthApprox_Interval:20' [ ~, r1D ]  = EvalBSpline( spline, uvec );
                for (int i15{0}; i15 < 5; i15++) {
                    double d2;
                    d2 = ctx_cfg_GaussLegendreX[i15];
                    b_uStart[i15] = (uStart * (1.0 - d2) + uMiddle * (d2 + 1.0)) / 2.0;
                }
                EvalBSpline(expl_temp.sp.Bl.handle, expl_temp.sp.coeff, b_uStart, a__1, r1D);
                // 'splineLengthApprox_Interval:21' r1Dnorm     = MyNorm( r1D );
                // 'MyNorm:2' coder.inline('always');
                // 'MyNorm:3' n = mysqrt(sum(x.^2));
                r1.set_size(r1D.size(0), 5);
                h_loop_ub = r1D.size(0);
                for (int i16{0}; i16 < 5; i16++) {
                    for (int i17{0}; i17 < h_loop_ub; i17++) {
                        double c_varargin_1;
                        c_varargin_1 = r1D[i17 + r1D.size(0) * i16];
                        r1[i17 + r1.size(0) * i16] = std::pow(c_varargin_1, 2.0);
                    }
                }
                coder::sum(r1, r1Dnorm);
                // 'mysqrt:3' y = sqrt(x);
                // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                sqrt_calls++;
                // 'splineLengthApprox_Interval:22' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
                //  Gauss Legendre integration
                // 'splineLengthApprox_Interval:23' L = L( 1 );
                //  to satisfy Matlab Coder
                c_r1Dnorm = 0.0;
                for (int c_k{0}; c_k < 5; c_k++) {
                    double d3;
                    d3 = std::sqrt(r1Dnorm[c_k]);
                    r1Dnorm[c_k] = d3;
                    c_r1Dnorm += d3 * ctx_cfg_GaussLegendreW[c_k];
                }
                fk = c_r1Dnorm * (uMiddle - uStart) / 2.0 - LDiff;
                // 'splineLengthFindU:89' if( fk > 0 )
                if (fk > 0.0) {
                    // 'splineLengthFindU:90' uRight = uMiddle;
                    uRight = uMiddle;
                } else {
                    // 'splineLengthFindU:91' else
                    // 'splineLengthFindU:92' uLeft  = uMiddle;
                    uLeft = uMiddle;
                }
                // 'splineLengthFindU:94' count = count + 1;
                count++;
            }
            // 'splineLengthFindU:97' if( count >= iterMax )
            if (count >= 1000) {
                // 'splineLengthFindU:98' u = -1;
                u_tilda = -1.0;
            } else {
                // 'splineLengthFindU:99' else
                // 'splineLengthFindU:100' u = uMiddle;
                u_tilda = uMiddle;
            }
            // 'splineLengthFindU:65' if( u < 0 )
            // 'splineLengthFindU:67' if( isEnd && u >= 0 )
        }
    } else {
        int loop_ub;
        // 'cutCurvStructU:25' else
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        // 'cutCurvStructU:29' if( isEnd )
        // 'cutCurvStructU:32' else
        // 'cutCurvStructU:33' [ ~, r1D0 ] = EvalCurvStruct( ctx, curv, 0 );
        c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, a__2, r1D0);
        // 'cutCurvStructU:34' u1 = u0 + L / MyNorm( r1D0 );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'cutCurvStructU:36' u1_tilda = a * u1 + b;
        r.set_size(r1D0.size(0));
        loop_ub = r1D0.size(0);
        for (int i{0}; i < loop_ub; i++) {
            double varargin_1;
            varargin_1 = r1D0[i];
            r[i] = std::pow(varargin_1, 2.0);
        }
        u_tilda = curv->a_param * (L / std::sqrt(coder::sum(r))) + curv->b_param;
    }
    // 'cutCurvStruct:17' if( u_tilda <= 0 )
    if (u_tilda <= 0.0) {
        // 'cutCurvStruct:17' ret = -1;
        b_ret = -1;
    } else {
        // 'cutCurvStruct:19' a = curv.a_param;
        // 'cutCurvStruct:20' b = curv.b_param;
        // 'cutCurvStruct:22' curv2.b_param = u_tilda;
        curv2->b_param = u_tilda;
        // 'cutCurvStruct:23' curv2.a_param = a + b - curv2.b_param;
        curv2->a_param = (curv->a_param + curv->b_param) - u_tilda;
        // 'cutCurvStruct:25' if( isAZeroEnd( curv2 ) )
        //  isAZeroEnd : Return true if the curv ends with zero speed
        //  Input :
        //  curv  : The curve struct
        // 'isAZeroEnd:5' if( curv.Info.zspdmode == ZSpdMode.NZ || ...
        // 'isAZeroEnd:6'         curv.Info.zspdmode == ZSpdMode.ZZ )
        if ((curv->Info.zspdmode == ZSpdMode_NZ) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroEnd:7' zeroFlag = true;
            // 'cutCurvStruct:26' curv2.Info.zspdmode = ZSpdMode.NZ;
            curv2->Info.zspdmode = ZSpdMode_NZ;
        } else {
            // 'isAZeroEnd:9' zeroFlag = false;
            // 'cutCurvStruct:27' else
            // 'cutCurvStruct:28' curv2.Info.zspdmode = ZSpdMode.NN;
            curv2->Info.zspdmode = ZSpdMode_NN;
        }
        // 'cutCurvStruct:31' curv1.a_param = u_tilda - curv1.b_param;
        curv1->a_param = u_tilda - curv->b_param;
        // 'cutCurvStruct:32' if( isAZeroStart( curv1 ) )
        //  isAZeroStart : Return true if the curv starts with zero speed
        //  curv  : The curve struct
        // 'isAZeroStart:4' if( curv.Info.zspdmode == ZSpdMode.ZN || ...
        // 'isAZeroStart:5'         curv.Info.zspdmode == ZSpdMode.ZZ )
        if ((curv->Info.zspdmode == ZSpdMode_ZN) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroStart:6' zeroFlag = true;
            // 'cutCurvStruct:33' curv1.Info.zspdmode = ZSpdMode.ZN;
            curv1->Info.zspdmode = ZSpdMode_ZN;
        } else {
            // 'isAZeroStart:8' zeroFlag = false;
            // 'cutCurvStruct:34' else
            // 'cutCurvStruct:35' curv1.Info.zspdmode = ZSpdMode.NN;
            curv1->Info.zspdmode = ZSpdMode_NN;
        }
    }
    *ret = b_ret;
}

} // namespace ocn

//
// File trailer for cutCurvStruct.cpp
//
// [EOF]
//
