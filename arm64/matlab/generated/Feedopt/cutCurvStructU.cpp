//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutCurvStructU.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

// Include Files
#include "cutCurvStructU.h"
#include "EvalBSpline.h"
#include "EvalCurvStruct.h"
#include "bspline_eval.h"
#include "combineVectorElements.h"
#include "find.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>

// Variable Definitions
namespace ocn {
static const char cv2[54]{'u', '1', ' ', 'm', 'u', 's', 't', ' ', 'b', 'e', ' ', 's', 'm', 'a',
                          'l', 'l', 'e', 'r', ' ', 'o', 'r', ' ', 'e', 'q', 'u', 'a', 'l', ' ',
                          't', 'h', 'a', 'n', ' ', 't', 'h', 'e', ' ', 'f', 'i', 'r', 's', 't',
                          ' ', 's', 'p', 'l', 'i', 'n', 'e', ' ', 'k', 'n', 'o', 't'};

}

// Function Definitions
//
// function [ u1_tilda ] = cutCurvStructU( ctx, curv, u0, L, isEnd )
//
// cutCurvStructU: Cut a piece of the structure with a size of L
//  starting at point u0
//  Inputs :
//  ctx   : Context
//  curv  : Curvature
//  u0    : Starting point of the spline
//  L     : Length of the segment of curv
//  isEnd : Is a cut from the end
//  Outputs :
//  u1    : The last point of the splitted curv
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &ctx_cfg_maskCart
//                const ::coder::array<bool, 2U> &ctx_cfg_maskRot
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *curv
//                double L
// Return Type  : double
//
namespace ocn {
double b_cutCurvStructU(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                        const int ctx_cfg_maskTot_size[2],
                        const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                        const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                        const ::coder::array<int, 1U> &ctx_cfg_indCart,
                        const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                        int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_GaussLegendreX[5],
                        const double ctx_cfg_GaussLegendreW[5], const CurvStruct *curv, double L)
{
    ::coder::array<double, 2U> Knots;
    ::coder::array<double, 2U> Lk;
    ::coder::array<double, 2U> b_a__1;
    ::coder::array<double, 2U> b_expl_temp;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> b_r1D;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D1;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    ::coder::array<bool, 2U> b_Knots;
    ::coder::array<bool, 2U> b_x;
    CurvStruct expl_temp;
    double dv[5];
    double r1Dnorm[5];
    double d4;
    double d5;
    double d6;
    double u1_tilda;
    int kEndVec_size[2];
    int tmp_size[2];
    int kEndVec_data;
    int kStartVec_data;
    int tmp_data;
    char message[54];
    // 'cutCurvStructU:13' a = curv.a_param;
    // 'cutCurvStructU:14' b = curv.b_param;
    // 'cutCurvStructU:16' if ( curv.Info.Type == CurveType.Spline )
    if (curv->Info.Type == CurveType_Spline) {
        double LStart;
        double d;
        double kEnd;
        double u1;
        double uRight;
        double uRightOld;
        double uRight_tmp;
        unsigned long spline_sp_Bl_handle;
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int i;
        int i1;
        int i10;
        int i11;
        int i3;
        int kStart;
        // 'cutCurvStructU:17' spline = ctx.q_spline.get( curv.sp_index );
        ctx_q_spline->get(curv->sp_index, &expl_temp);
        spline_sp_Bl_handle = expl_temp.sp.Bl.handle;
        // 'cutCurvStructU:18' u1_tilda = splineLenghtFindU_new( ctx.cfg, spline, L, a * u0 + b,
        // isEnd );
        //  Get the sp structure
        // 'splineLenghtFindU_new:3' sp     = spline.sp;
        // 'splineLenghtFindU_new:5' DEFAULT_TOL_NR  = 1e-12;
        //  Default tolerance for Newton Raphson
        // 'splineLenghtFindU_new:6' IND_KNOTS_MULT  = sp.Bl.order;
        //  Index used to remove multiple knots
        //  Eliminate multiplicities at the end points
        // 'splineLenghtFindU_new:8' Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1
        // );
        i = (expl_temp.sp.knots.size(1) - expl_temp.sp.Bl.order) + 1;
        if (expl_temp.sp.Bl.order > i) {
            i1 = 0;
            i3 = 0;
        } else {
            i1 = expl_temp.sp.Bl.order - 1;
            i3 = i;
        }
        // 'splineLenghtFindU_new:9' Lk     = sp.Lk;
        // 'splineLenghtFindU_new:10' kMax   = numel( Lk );
        // 'splineLenghtFindU_new:12' if( isEnd )
        // 'splineLenghtFindU_new:13' u1      = 1 - u1;
        u1 = 1.0 - (curv->a_param + curv->b_param);
        // 'splineLenghtFindU_new:14' Knots   = flip( 1 - Knots );
        b_loop_ub = i3 - i1;
        Knots.set_size(1, b_loop_ub);
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            Knots[i4] = 1.0 - expl_temp.sp.knots[i1 + i4];
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
        // 'splineLenghtFindU_new:15' Lk      = flip( Lk );
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
        // 'splineLenghtFindU_new:18' C_ASSERT_MSG = 'u1 must be %s or equal than the first spline
        // knot'; 'splineLenghtFindU_new:19' c_assert( u1 >= Knots(1),   sprintf(C_ASSERT_MSG,
        // 'greater') ); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
        if (u1 < Knots[0]) {
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i6{0}; i6 < 54; i6++) {
                message[i6] = cv1[i6];
            }
            c_assert_(&message[0]);
        }
        // 'c_assert:6' value = condition;
        // 'splineLenghtFindU_new:20' c_assert( u1 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller')
        // ); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
        if (u1 > Knots[Knots.size(1) - 1]) {
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i7{0}; i7 < 54; i7++) {
                message[i7] = cv2[i7];
            }
            c_assert_(&message[0]);
        }
        // 'c_assert:6' value = condition;
        // 'splineLenghtFindU_new:22' kStartVec = find( Knots <= u1, 1, "last" );
        b_Knots.set_size(1, Knots.size(1));
        d_loop_ub = Knots.size(1);
        for (int i8{0}; i8 < d_loop_ub; i8++) {
            b_Knots[i8] = (Knots[i8] <= u1);
        }
        coder::eml_find(b_Knots, (int *)&kEndVec_data, kEndVec_size);
        e_loop_ub = kEndVec_size[1];
        for (int i9{0}; i9 < e_loop_ub; i9++) {
            kStartVec_data = kEndVec_data;
        }
        // 'splineLenghtFindU_new:23' kStart    = kStartVec( 1 );
        kStart = kStartVec_data - 1;
        // 'splineLenghtFindU_new:25' if( Knots( kStart ) < u1 )
        d = Knots[kStartVec_data - 1];
        if (d < u1) {
            double b_r1Dnorm;
            int h_loop_ub;
            // 'splineLenghtFindU_new:26' LStart = splineLengthApprox_Interval( cfg, spline, Knots(
            // kStart ), u1, isEnd );
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
            for (int i13{0}; i13 < 5; i13++) {
                double d1;
                d1 = ctx_cfg_GaussLegendreX[i13];
                dv[i13] = ((1.0 - u1) * (1.0 - d1) + (1.0 - d) * (d1 + 1.0)) / 2.0;
            }
            EvalBSpline(expl_temp.sp.Bl.handle, expl_temp.sp.coeff, dv, b_a__1, r1D);
            // 'splineLengthApprox_Interval:21' r1Dnorm     = MyNorm( r1D );
            // 'MyNorm:2' coder.inline('always');
            // 'MyNorm:3' n = mysqrt(sum(x.^2));
            r1.set_size(r1D.size(0), 5);
            h_loop_ub = r1D.size(0);
            for (int i15{0}; i15 < 5; i15++) {
                for (int i16{0}; i16 < h_loop_ub; i16++) {
                    double b_varargin_1;
                    b_varargin_1 = r1D[i16 + r1D.size(0) * i15];
                    r1[i16 + r1.size(0) * i15] = std::pow(b_varargin_1, 2.0);
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
            LStart = b_r1Dnorm * ((1.0 - d) - (1.0 - u1)) / 2.0;
            //  Gauss Legendre integration
            // 'splineLengthApprox_Interval:23' L = L( 1 );
            //  to satisfy Matlab Coder
        } else {
            // 'splineLenghtFindU_new:27' else
            // 'splineLenghtFindU_new:28' LStart = 0;
            LStart = 0.0;
        }
        // 'splineLenghtFindU_new:31' LEnd = cumsum( Lk( kStart : kMax ) ) - LStart;
        if (kStartVec_data > expl_temp.sp.Lk.size(1)) {
            i10 = -1;
            i11 = -1;
        } else {
            i10 = kStartVec_data - 2;
            i11 = expl_temp.sp.Lk.size(1) - 1;
        }
        f_loop_ub = i11 - i10;
        x.set_size(1, f_loop_ub);
        for (int i12{0}; i12 < f_loop_ub; i12++) {
            x[i12] = Lk[(i10 + i12) + 1];
        }
        if ((f_loop_ub != 0) && (f_loop_ub != 1)) {
            for (int c_k{0}; c_k <= f_loop_ub - 2; c_k++) {
                x[c_k + 1] = x[c_k] + x[c_k + 1];
            }
        }
        // 'splineLenghtFindU_new:33' kEndVec = find( LEnd >= L, 1, "first" );
        b_x.set_size(1, x.size(1));
        g_loop_ub = x.size(1);
        for (int i14{0}; i14 < g_loop_ub; i14++) {
            b_x[i14] = (x[i14] - LStart >= L);
        }
        // 'splineLenghtFindU_new:34' kEnd    = kEndVec( 1 );
        // 'splineLenghtFindU_new:35' if( isempty( kEnd ) )
        // 'splineLenghtFindU_new:36' kEnd = kEnd + kStart;
        coder::b_eml_find(b_x, (int *)&tmp_data, tmp_size);
        kEnd = static_cast<double>(tmp_data) + static_cast<double>(kStartVec_data);
        // 'splineLenghtFindU_new:38' uLeft       = u1;
        // 'splineLenghtFindU_new:39' uRight      = Knots( kEnd );
        uRight_tmp = Knots[static_cast<int>(kEnd) - 1];
        uRight = uRight_tmp;
        // 'splineLenghtFindU_new:40' uRightOld   = uLeft;
        uRightOld = u1;
        // 'splineLenghtFindU_new:42' while( abs( uRightOld - uRight ) > DEFAULT_TOL_NR )
        while (std::abs(uRightOld - uRight) > 1.0E-12) {
            double c_r1Dnorm;
            int i24;
            int i_loop_ub;
            int j_loop_ub;
            int k_loop_ub;
            int l_loop_ub;
            int m_loop_ub;
            int o_loop_ub;
            //  Evaluation of function which should become zero
            // 'splineLenghtFindU_new:44' fk  = splineLengthApprox_Interval( cfg, spline, uLeft,
            // uRight, isEnd ) - L;
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
            for (int i17{0}; i17 < 5; i17++) {
                double d3;
                d3 = ctx_cfg_GaussLegendreX[i17];
                dv[i17] = ((1.0 - uRight) * (1.0 - d3) + (1.0 - u1) * (d3 + 1.0)) / 2.0;
            }
            EvalBSpline(spline_sp_Bl_handle, expl_temp.sp.coeff, dv, b_a__1, r1D);
            // 'splineLengthApprox_Interval:21' r1Dnorm     = MyNorm( r1D );
            // 'MyNorm:2' coder.inline('always');
            // 'MyNorm:3' n = mysqrt(sum(x.^2));
            r1.set_size(r1D.size(0), 5);
            i_loop_ub = r1D.size(0);
            for (int i18{0}; i18 < 5; i18++) {
                for (int i19{0}; i19 < i_loop_ub; i19++) {
                    double c_varargin_1;
                    c_varargin_1 = r1D[i19 + r1D.size(0) * i18];
                    r1[i19 + r1.size(0) * i18] = std::pow(c_varargin_1, 2.0);
                }
            }
            coder::sum(r1, r1Dnorm);
            // 'mysqrt:3' y = sqrt(x);
            for (int e_k{0}; e_k < 5; e_k++) {
                r1Dnorm[e_k] = std::sqrt(r1Dnorm[e_k]);
            }
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
            // 'splineLengthApprox_Interval:22' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
            //  Gauss Legendre integration
            // 'splineLengthApprox_Interval:23' L = L( 1 );
            //  to satisfy Matlab Coder
            // 'splineLenghtFindU_new:45' [ ~, r1D ] = EvalBSpline( spline, uRight );
            //  EvalBSpline
            //
            //  INPUT
            //  spline        : struct : Spline structure
            //  u_vec         :    1xn : Vector for evaluation of the curv
            //
            //  OUTPUT
            //  r0D           :   nDxn : The evaluated B spline at u\_vec points
            //  r1D           :   nDxn : 1rst order parametric derivative for the B spline at u\_vec
            //  points r2D           :   nDxn : 2nd order parametric derivative for the B spline at
            //  u\_vec points r3D           :   nDxn : 3rd order parametric derivative for the B
            //  spline at u\_vec points
            // 'EvalBSpline:14' sp = spline.sp;
            // 'EvalBSpline:15' N  = length( u_vec );
            // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
            // 'EvalBSpline:18' r0D = zeros( M, N );
            a__1.set_size(expl_temp.sp.coeff.size(0));
            j_loop_ub = expl_temp.sp.coeff.size(0);
            for (int i20{0}; i20 < j_loop_ub; i20++) {
                a__1[i20] = 0.0;
            }
            // 'EvalBSpline:18' r1D = r0D;
            b_r1D.set_size(expl_temp.sp.coeff.size(0));
            k_loop_ub = expl_temp.sp.coeff.size(0);
            for (int i21{0}; i21 < k_loop_ub; i21++) {
                b_r1D[i21] = 0.0;
            }
            // 'EvalBSpline:18' r2D = r1D;
            r2D.set_size(expl_temp.sp.coeff.size(0));
            l_loop_ub = expl_temp.sp.coeff.size(0);
            for (int i22{0}; i22 < l_loop_ub; i22++) {
                r2D[i22] = 0.0;
            }
            // 'EvalBSpline:18' r3D = r2D;
            r3D.set_size(expl_temp.sp.coeff.size(0));
            m_loop_ub = expl_temp.sp.coeff.size(0);
            for (int i23{0}; i23 < m_loop_ub; i23++) {
                r3D[i23] = 0.0;
            }
            // 'EvalBSpline:20' for j = 1 : M
            i24 = expl_temp.sp.coeff.size(0);
            for (int j{0}; j < i24; j++) {
                int n_loop_ub;
                // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
                // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff(
                // j, : ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
                // 'bspline_eval_vec:4' xd      = zeros(size(u));
                // 'bspline_eval_vec:5' xdd     = zeros(size(u));
                // 'bspline_eval_vec:6' xddd    = zeros(size(u));
                // 'bspline_eval_vec:8' for k = 1:length(u)
                // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
                a__1[j] = uRight;
                n_loop_ub = expl_temp.sp.coeff.size(1);
                b_expl_temp.set_size(1, expl_temp.sp.coeff.size(1));
                for (int i26{0}; i26 < n_loop_ub; i26++) {
                    b_expl_temp[i26] = expl_temp.sp.coeff[j + expl_temp.sp.coeff.size(0) * i26];
                }
                bspline_eval(spline_sp_Bl_handle, b_expl_temp, &a__1[j], &d4, &d5, &d6);
                r3D[j] = d6;
                r2D[j] = d5;
                b_r1D[j] = d4;
                // 'bspline_eval_vec:10' x(k)    = xk;
                // 'bspline_eval_vec:11' xd(k)   = xdk;
                // 'bspline_eval_vec:12' xdd(k)  = xddk;
                // 'bspline_eval_vec:13' xddd(k) = xdddk;
            }
            // 'splineLenghtFindU_new:46' Dfk = MyNorm( r1D );
            // 'MyNorm:2' coder.inline('always');
            // 'MyNorm:3' n = mysqrt(sum(x.^2));
            // 'mysqrt:3' y = sqrt(x);
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
            // 'splineLenghtFindU_new:47' uRightOld = uRight;
            uRightOld = uRight;
            // 'splineLenghtFindU_new:48' uRight    = uRight - fk / Dfk;
            r.set_size(b_r1D.size(0));
            o_loop_ub = b_r1D.size(0);
            for (int i25{0}; i25 < o_loop_ub; i25++) {
                double d_varargin_1;
                d_varargin_1 = b_r1D[i25];
                r[i25] = std::pow(d_varargin_1, 2.0);
            }
            c_r1Dnorm = 0.0;
            for (int i27{0}; i27 < 5; i27++) {
                c_r1Dnorm += r1Dnorm[i27] * ctx_cfg_GaussLegendreW[i27];
            }
            uRight -= (c_r1Dnorm * ((1.0 - u1) - (1.0 - uRight)) / 2.0 - L) /
                      std::sqrt(coder::combineVectorElements(r));
            // 'splineLenghtFindU_new:49' if( uRight > Knots( kEnd ) )
            if (uRight > uRight_tmp) {
                // 'splineLenghtFindU_new:49' uRight = Knots( kEnd );
                uRight = Knots[static_cast<int>(kEnd) - 1];
            }
            // 'splineLenghtFindU_new:50' if( uRight < Knots( kStart ) )
            if (uRight < Knots[kStart]) {
                // 'splineLenghtFindU_new:50' uRight = Knots( kStart );
                uRight = Knots[kStart];
            }
        }
        // 'splineLenghtFindU_new:53' u = uRight;
        // 'splineLenghtFindU_new:55' if( isEnd )
        // 'splineLenghtFindU_new:56' u = 1 -u;
        u1_tilda = 1.0 - uRight;
    } else {
        int loop_ub;
        // 'cutCurvStructU:19' else
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        // 'cutCurvStructU:23' if( isEnd )
        // 'cutCurvStructU:24' [ ~, r1D1 ] = EvalCurvStruct( ctx, curv, 1 );
        b_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                         ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, a__1, r1D1);
        // 'cutCurvStructU:25' u1 = u0 - L / MyNorm( r1D1 );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'cutCurvStructU:30' u1_tilda = a * u1 + b;
        r.set_size(r1D1.size(0));
        loop_ub = r1D1.size(0);
        for (int i2{0}; i2 < loop_ub; i2++) {
            double varargin_1;
            varargin_1 = r1D1[i2];
            r[i2] = std::pow(varargin_1, 2.0);
        }
        u1_tilda =
            curv->a_param * (1.0 - L / std::sqrt(coder::combineVectorElements(r))) + curv->b_param;
    }
    return u1_tilda;
}

//
// function [ u1_tilda ] = cutCurvStructU( ctx, curv, u0, L, isEnd )
//
// cutCurvStructU: Cut a piece of the structure with a size of L
//  starting at point u0
//  Inputs :
//  ctx   : Context
//  curv  : Curvature
//  u0    : Starting point of the spline
//  L     : Length of the segment of curv
//  isEnd : Is a cut from the end
//  Outputs :
//  u1    : The last point of the splitted curv
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &ctx_cfg_maskCart
//                const ::coder::array<bool, 2U> &ctx_cfg_maskRot
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *curv
//                double L
// Return Type  : double
//
double cutCurvStructU(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2],
                      const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                      const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_GaussLegendreX[5],
                      const double ctx_cfg_GaussLegendreW[5], const CurvStruct *curv, double L)
{
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> e_expl_temp;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> x;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> b_a__1;
    ::coder::array<double, 1U> b_r1D;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D0;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    ::coder::array<bool, 2U> b_expl_temp;
    ::coder::array<bool, 2U> b_x;
    CurvStruct expl_temp;
    double b_b[5];
    double d_expl_temp[5];
    double r1Dnorm[5];
    double b;
    double d3;
    double d4;
    double d5;
    double u1_tilda;
    int kEndVec_size[2];
    int tmp_size[2];
    int kEndVec_data;
    int kStartVec_data;
    int tmp_data;
    char message[54];
    // 'cutCurvStructU:13' a = curv.a_param;
    // 'cutCurvStructU:14' b = curv.b_param;
    b = curv->b_param;
    // 'cutCurvStructU:16' if ( curv.Info.Type == CurveType.Spline )
    if (curv->Info.Type == CurveType_Spline) {
        double LStart;
        double uRight;
        double uRightOld;
        unsigned long spline_sp_Bl_handle;
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int i;
        int i1;
        int i10;
        int i2;
        int i8;
        int i9;
        int uRight_tmp;
        // 'cutCurvStructU:17' spline = ctx.q_spline.get( curv.sp_index );
        ctx_q_spline->get(curv->sp_index, &expl_temp);
        spline_sp_Bl_handle = expl_temp.sp.Bl.handle;
        // 'cutCurvStructU:18' u1_tilda = splineLenghtFindU_new( ctx.cfg, spline, L, a * u0 + b,
        // isEnd );
        //  Get the sp structure
        // 'splineLenghtFindU_new:3' sp     = spline.sp;
        // 'splineLenghtFindU_new:5' DEFAULT_TOL_NR  = 1e-12;
        //  Default tolerance for Newton Raphson
        // 'splineLenghtFindU_new:6' IND_KNOTS_MULT  = sp.Bl.order;
        //  Index used to remove multiple knots
        //  Eliminate multiplicities at the end points
        // 'splineLenghtFindU_new:8' Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1
        // );
        i = (expl_temp.sp.knots.size(1) - expl_temp.sp.Bl.order) + 1;
        if (expl_temp.sp.Bl.order > i) {
            i1 = 0;
            i2 = 0;
        } else {
            i1 = expl_temp.sp.Bl.order - 1;
            i2 = i;
        }
        // 'splineLenghtFindU_new:9' Lk     = sp.Lk;
        // 'splineLenghtFindU_new:10' kMax   = numel( Lk );
        // 'splineLenghtFindU_new:12' if( isEnd )
        // 'splineLenghtFindU_new:18' C_ASSERT_MSG = 'u1 must be %s or equal than the first spline
        // knot'; 'splineLenghtFindU_new:19' c_assert( u1 >= Knots(1),   sprintf(C_ASSERT_MSG,
        // 'greater') ); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
        if (curv->b_param < expl_temp.sp.knots[i1]) {
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i4{0}; i4 < 54; i4++) {
                message[i4] = cv1[i4];
            }
            c_assert_(&message[0]);
        }
        // 'c_assert:6' value = condition;
        // 'splineLenghtFindU_new:20' c_assert( u1 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller')
        // ); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
        if (curv->b_param > expl_temp.sp.knots[i2 - 1]) {
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i5{0}; i5 < 54; i5++) {
                message[i5] = cv2[i5];
            }
            c_assert_(&message[0]);
        }
        // 'c_assert:6' value = condition;
        // 'splineLenghtFindU_new:22' kStartVec = find( Knots <= u1, 1, "last" );
        b_loop_ub = i2 - i1;
        b_expl_temp.set_size(1, b_loop_ub);
        for (int i6{0}; i6 < b_loop_ub; i6++) {
            b_expl_temp[i6] = (expl_temp.sp.knots[i1 + i6] <= curv->b_param);
        }
        coder::eml_find(b_expl_temp, (int *)&kEndVec_data, kEndVec_size);
        c_loop_ub = kEndVec_size[1];
        for (int i7{0}; i7 < c_loop_ub; i7++) {
            kStartVec_data = kEndVec_data;
        }
        // 'splineLenghtFindU_new:23' kStart    = kStartVec( 1 );
        // 'splineLenghtFindU_new:25' if( Knots( kStart ) < u1 )
        i8 = (i1 + kStartVec_data) - 1;
        if (expl_temp.sp.knots[i8] < curv->b_param) {
            double b_r1Dnorm;
            double c_expl_temp;
            int f_loop_ub;
            // 'splineLenghtFindU_new:26' LStart = splineLengthApprox_Interval( cfg, spline, Knots(
            // kStart ), u1, isEnd );
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
            c_expl_temp = expl_temp.sp.knots[i8];
            for (int i12{0}; i12 < 5; i12++) {
                double d;
                d = ctx_cfg_GaussLegendreX[i12];
                d_expl_temp[i12] = (c_expl_temp * (1.0 - d) + curv->b_param * (d + 1.0)) / 2.0;
            }
            EvalBSpline(expl_temp.sp.Bl.handle, expl_temp.sp.coeff, d_expl_temp, a__1, r1D);
            // 'splineLengthApprox_Interval:21' r1Dnorm     = MyNorm( r1D );
            // 'MyNorm:2' coder.inline('always');
            // 'MyNorm:3' n = mysqrt(sum(x.^2));
            r1.set_size(r1D.size(0), 5);
            f_loop_ub = r1D.size(0);
            for (int i14{0}; i14 < 5; i14++) {
                for (int i15{0}; i15 < f_loop_ub; i15++) {
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
            for (int b_k{0}; b_k < 5; b_k++) {
                double d1;
                d1 = std::sqrt(r1Dnorm[b_k]);
                r1Dnorm[b_k] = d1;
                b_r1Dnorm += d1 * ctx_cfg_GaussLegendreW[b_k];
            }
            LStart = b_r1Dnorm * (curv->b_param - expl_temp.sp.knots[i8]) / 2.0;
            //  Gauss Legendre integration
            // 'splineLengthApprox_Interval:23' L = L( 1 );
            //  to satisfy Matlab Coder
        } else {
            // 'splineLenghtFindU_new:27' else
            // 'splineLenghtFindU_new:28' LStart = 0;
            LStart = 0.0;
        }
        // 'splineLenghtFindU_new:31' LEnd = cumsum( Lk( kStart : kMax ) ) - LStart;
        if (kStartVec_data > expl_temp.sp.Lk.size(1)) {
            i9 = -1;
            i10 = -1;
        } else {
            i9 = kStartVec_data - 2;
            i10 = expl_temp.sp.Lk.size(1) - 1;
        }
        d_loop_ub = i10 - i9;
        x.set_size(1, d_loop_ub);
        for (int i11{0}; i11 < d_loop_ub; i11++) {
            x[i11] = expl_temp.sp.Lk[(i9 + i11) + 1];
        }
        if ((d_loop_ub != 0) && (d_loop_ub != 1)) {
            for (int k{0}; k <= d_loop_ub - 2; k++) {
                x[k + 1] = x[k] + x[k + 1];
            }
        }
        // 'splineLenghtFindU_new:33' kEndVec = find( LEnd >= L, 1, "first" );
        b_x.set_size(1, x.size(1));
        e_loop_ub = x.size(1);
        for (int i13{0}; i13 < e_loop_ub; i13++) {
            b_x[i13] = (x[i13] - LStart >= L);
        }
        // 'splineLenghtFindU_new:34' kEnd    = kEndVec( 1 );
        // 'splineLenghtFindU_new:35' if( isempty( kEnd ) )
        // 'splineLenghtFindU_new:36' kEnd = kEnd + kStart;
        // 'splineLenghtFindU_new:38' uLeft       = u1;
        // 'splineLenghtFindU_new:39' uRight      = Knots( kEnd );
        coder::b_eml_find(b_x, (int *)&tmp_data, tmp_size);
        uRight_tmp = ((i1 + tmp_data) + kStartVec_data) - 1;
        uRight = expl_temp.sp.knots[uRight_tmp];
        // 'splineLenghtFindU_new:40' uRightOld   = uLeft;
        uRightOld = curv->b_param;
        // 'splineLenghtFindU_new:42' while( abs( uRightOld - uRight ) > DEFAULT_TOL_NR )
        while (std::abs(uRightOld - uRight) > 1.0E-12) {
            double c_r1Dnorm;
            int g_loop_ub;
            int h_loop_ub;
            int i23;
            int i27;
            int i_loop_ub;
            int j_loop_ub;
            int k_loop_ub;
            int m_loop_ub;
            //  Evaluation of function which should become zero
            // 'splineLenghtFindU_new:44' fk  = splineLengthApprox_Interval( cfg, spline, uLeft,
            // uRight, isEnd ) - L;
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
            for (int i16{0}; i16 < 5; i16++) {
                double d2;
                d2 = ctx_cfg_GaussLegendreX[i16];
                b_b[i16] = (b * (1.0 - d2) + uRight * (d2 + 1.0)) / 2.0;
            }
            EvalBSpline(spline_sp_Bl_handle, expl_temp.sp.coeff, b_b, a__1, r1D);
            // 'splineLengthApprox_Interval:21' r1Dnorm     = MyNorm( r1D );
            // 'MyNorm:2' coder.inline('always');
            // 'MyNorm:3' n = mysqrt(sum(x.^2));
            r1.set_size(r1D.size(0), 5);
            g_loop_ub = r1D.size(0);
            for (int i17{0}; i17 < 5; i17++) {
                for (int i18{0}; i18 < g_loop_ub; i18++) {
                    double c_varargin_1;
                    c_varargin_1 = r1D[i18 + r1D.size(0) * i17];
                    r1[i18 + r1.size(0) * i17] = std::pow(c_varargin_1, 2.0);
                }
            }
            coder::sum(r1, r1Dnorm);
            // 'mysqrt:3' y = sqrt(x);
            for (int c_k{0}; c_k < 5; c_k++) {
                r1Dnorm[c_k] = std::sqrt(r1Dnorm[c_k]);
            }
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
            // 'splineLengthApprox_Interval:22' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
            //  Gauss Legendre integration
            // 'splineLengthApprox_Interval:23' L = L( 1 );
            //  to satisfy Matlab Coder
            // 'splineLenghtFindU_new:45' [ ~, r1D ] = EvalBSpline( spline, uRight );
            //  EvalBSpline
            //
            //  INPUT
            //  spline        : struct : Spline structure
            //  u_vec         :    1xn : Vector for evaluation of the curv
            //
            //  OUTPUT
            //  r0D           :   nDxn : The evaluated B spline at u\_vec points
            //  r1D           :   nDxn : 1rst order parametric derivative for the B spline at u\_vec
            //  points r2D           :   nDxn : 2nd order parametric derivative for the B spline at
            //  u\_vec points r3D           :   nDxn : 3rd order parametric derivative for the B
            //  spline at u\_vec points
            // 'EvalBSpline:14' sp = spline.sp;
            // 'EvalBSpline:15' N  = length( u_vec );
            // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
            // 'EvalBSpline:18' r0D = zeros( M, N );
            b_a__1.set_size(expl_temp.sp.coeff.size(0));
            h_loop_ub = expl_temp.sp.coeff.size(0);
            for (int i19{0}; i19 < h_loop_ub; i19++) {
                b_a__1[i19] = 0.0;
            }
            // 'EvalBSpline:18' r1D = r0D;
            b_r1D.set_size(expl_temp.sp.coeff.size(0));
            i_loop_ub = expl_temp.sp.coeff.size(0);
            for (int i20{0}; i20 < i_loop_ub; i20++) {
                b_r1D[i20] = 0.0;
            }
            // 'EvalBSpline:18' r2D = r1D;
            r2D.set_size(expl_temp.sp.coeff.size(0));
            j_loop_ub = expl_temp.sp.coeff.size(0);
            for (int i21{0}; i21 < j_loop_ub; i21++) {
                r2D[i21] = 0.0;
            }
            // 'EvalBSpline:18' r3D = r2D;
            r3D.set_size(expl_temp.sp.coeff.size(0));
            k_loop_ub = expl_temp.sp.coeff.size(0);
            for (int i22{0}; i22 < k_loop_ub; i22++) {
                r3D[i22] = 0.0;
            }
            // 'EvalBSpline:20' for j = 1 : M
            i23 = expl_temp.sp.coeff.size(0);
            for (int j{0}; j < i23; j++) {
                int l_loop_ub;
                // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
                // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff(
                // j, : ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
                // 'bspline_eval_vec:4' xd      = zeros(size(u));
                // 'bspline_eval_vec:5' xdd     = zeros(size(u));
                // 'bspline_eval_vec:6' xddd    = zeros(size(u));
                // 'bspline_eval_vec:8' for k = 1:length(u)
                // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
                b_a__1[j] = uRight;
                l_loop_ub = expl_temp.sp.coeff.size(1);
                e_expl_temp.set_size(1, expl_temp.sp.coeff.size(1));
                for (int i25{0}; i25 < l_loop_ub; i25++) {
                    e_expl_temp[i25] = expl_temp.sp.coeff[j + expl_temp.sp.coeff.size(0) * i25];
                }
                bspline_eval(spline_sp_Bl_handle, e_expl_temp, &b_a__1[j], &d3, &d4, &d5);
                r3D[j] = d5;
                r2D[j] = d4;
                b_r1D[j] = d3;
                // 'bspline_eval_vec:10' x(k)    = xk;
                // 'bspline_eval_vec:11' xd(k)   = xdk;
                // 'bspline_eval_vec:12' xdd(k)  = xddk;
                // 'bspline_eval_vec:13' xddd(k) = xdddk;
            }
            // 'splineLenghtFindU_new:46' Dfk = MyNorm( r1D );
            // 'MyNorm:2' coder.inline('always');
            // 'MyNorm:3' n = mysqrt(sum(x.^2));
            // 'mysqrt:3' y = sqrt(x);
            // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
            sqrt_calls++;
            // 'splineLenghtFindU_new:47' uRightOld = uRight;
            uRightOld = uRight;
            // 'splineLenghtFindU_new:48' uRight    = uRight - fk / Dfk;
            r.set_size(b_r1D.size(0));
            m_loop_ub = b_r1D.size(0);
            for (int i24{0}; i24 < m_loop_ub; i24++) {
                double d_varargin_1;
                d_varargin_1 = b_r1D[i24];
                r[i24] = std::pow(d_varargin_1, 2.0);
            }
            c_r1Dnorm = 0.0;
            for (int i26{0}; i26 < 5; i26++) {
                c_r1Dnorm += r1Dnorm[i26] * ctx_cfg_GaussLegendreW[i26];
            }
            uRight -=
                (c_r1Dnorm * (uRight - b) / 2.0 - L) / std::sqrt(coder::combineVectorElements(r));
            // 'splineLenghtFindU_new:49' if( uRight > Knots( kEnd ) )
            if (uRight > expl_temp.sp.knots[uRight_tmp]) {
                // 'splineLenghtFindU_new:49' uRight = Knots( kEnd );
                uRight = expl_temp.sp.knots[uRight_tmp];
            }
            // 'splineLenghtFindU_new:50' if( uRight < Knots( kStart ) )
            i27 = (i1 + kStartVec_data) - 1;
            if (uRight < expl_temp.sp.knots[i27]) {
                // 'splineLenghtFindU_new:50' uRight = Knots( kStart );
                uRight = expl_temp.sp.knots[i27];
            }
        }
        // 'splineLenghtFindU_new:53' u = uRight;
        u1_tilda = uRight;
        // 'splineLenghtFindU_new:55' if( isEnd )
    } else {
        int loop_ub;
        // 'cutCurvStructU:19' else
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        // 'cutCurvStructU:23' if( isEnd )
        // 'cutCurvStructU:26' else
        // 'cutCurvStructU:27' [ ~, r1D0 ] = EvalCurvStruct( ctx, curv, 0 );
        c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                         ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, a__2, r1D0);
        // 'cutCurvStructU:28' u1 = u0 + L / MyNorm( r1D0 );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'cutCurvStructU:30' u1_tilda = a * u1 + b;
        r.set_size(r1D0.size(0));
        loop_ub = r1D0.size(0);
        for (int i3{0}; i3 < loop_ub; i3++) {
            double varargin_1;
            varargin_1 = r1D0[i3];
            r[i3] = std::pow(varargin_1, 2.0);
        }
        u1_tilda = curv->a_param * (L / std::sqrt(coder::combineVectorElements(r))) + curv->b_param;
    }
    return u1_tilda;
}

} // namespace ocn

//
// File trailer for cutCurvStructU.cpp
//
// [EOF]
//
