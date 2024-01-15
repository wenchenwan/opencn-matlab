
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: splineLengthFindU.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "splineLengthFindU.h"
#include "EvalBSpline.h"
#include "find.h"
#include "ocn_assert.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function [ u ]  = splineLengthFindU( cfg, spline, L, u0, isEnd )
//
// splineLengthFindU : Computes approximately the value of curve parameter
//  u such that the arc length starting from u1 equals L.
//  This function takes usage of the precalculated arc lengths between knots.
//  The last integration interval is approximated by the trapezoidal rule.
//  u1 must satisfy 0 < u1 < 1.
//  In the normal case, u must satisfy 0 < u < u1. If L is too large, u is
//  set to -1.
//  The parameter isEnd is used to start inverse the problem, the length is
//  estimated starting from u quals to 1 to 0. It's used to cut a specific
//  length at the beginning of the curv.
//
//  Inputs :
//    cfg     : The configuration structure
//    spline  : The spline
//    L       : The length of the spline
//    u0      : The starting u
//    isEnd   : Boolean value. TRUE means the computation should start from
//              the end.
//
//  Outputs :
//    u       : The resulting u value
//
//
// Arguments    : const double cfg_GaussLegendreX[5]
//                const double cfg_GaussLegendreW[5]
//                unsigned long spline_sp_Bl_handle
//                int spline_sp_Bl_order
//                const ::coder::array<double, 2U> &spline_sp_coeff
//                const ::coder::array<double, 2U> &spline_sp_knots
//                const ::coder::array<double, 2U> &spline_sp_Lk
//                double L
//                double u0
// Return Type  : double
//
namespace ocn {
double b_splineLengthFindU(const double cfg_GaussLegendreX[5], const double cfg_GaussLegendreW[5],
                           unsigned long spline_sp_Bl_handle, int spline_sp_Bl_order,
                           const ::coder::array<double, 2U> &spline_sp_coeff,
                           const ::coder::array<double, 2U> &spline_sp_knots,
                           const ::coder::array<double, 2U> &spline_sp_Lk, double L, double u0)
{
    ::coder::array<double, 2U> Knots;
    ::coder::array<double, 2U> LEnd;
    ::coder::array<double, 2U> Lk;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> x;
    ::coder::array<bool, 2U> b_Knots;
    ::coder::array<bool, 2U> b_LEnd;
    double dv[5];
    double r1Dnorm[5];
    double LStart;
    double d;
    double u;
    int LkEndVec_size[2];
    int LkEndVec_data;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int i;
    int i1;
    int i2;
    int i7;
    int i8;
    int kStartVec_data;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    bool b_r1Dnorm[5];
    // 'splineLengthFindU:25' ITER_MAX    = 1000;
    // 'splineLengthFindU:26' DEFAULT_TOL = 1E-7;
    //  Get the sp structure
    // 'splineLengthFindU:29' sp     = spline.sp;
    // 'splineLengthFindU:31' IND_KNOTS_MULT  = sp.Bl.order;
    //  Index used to remove multiple knots
    //  Eliminate multiplicities at the end points
    // 'splineLengthFindU:33' Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
    i = spline_sp_knots.size(1) - spline_sp_Bl_order;
    if (spline_sp_Bl_order > i + 1) {
        i1 = 0;
        i2 = -1;
    } else {
        i1 = spline_sp_Bl_order - 1;
        i2 = i;
    }
    // 'splineLengthFindU:34' Lk     = sp.Lk;
    // 'splineLengthFindU:35' kMax   = numel( Lk );
    // 'splineLengthFindU:37' if( isEnd )
    // 'splineLengthFindU:38' u0      = 1 - u0;
    u0 = 1.0 - u0;
    // 'splineLengthFindU:39' Knots   = flip( 1 - Knots );
    loop_ub = i2 - i1;
    Knots.set_size(1, loop_ub + 1);
    scalarLB = ((loop_ub + 1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i3{0}; i3 <= vectorUB; i3 += 2) {
        _mm_storeu_pd(
            &Knots[i3],
            _mm_sub_pd(_mm_set1_pd(1.0), _mm_loadu_pd((const double *)&spline_sp_knots[i1 + i3])));
    }
    for (int i3{scalarLB}; i3 <= loop_ub; i3++) {
        Knots[i3] = 1.0 - spline_sp_knots[i1 + i3];
    }
    if (Knots.size(1) > 1) {
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
    // 'splineLengthFindU:40' Lk      = flip( Lk );
    Lk.set_size(1, spline_sp_Lk.size(1));
    b_loop_ub = spline_sp_Lk.size(1);
    for (int i4{0}; i4 < b_loop_ub; i4++) {
        Lk[i4] = spline_sp_Lk[i4];
    }
    if (spline_sp_Lk.size(1) > 1) {
        int b_lup;
        b_lup = spline_sp_Lk.size(1) >> 1;
        for (int b_k{0}; b_k < b_lup; b_k++) {
            double b_tmp;
            int b_subs2_idx_1;
            b_subs2_idx_1 = Lk.size(1) - b_k;
            b_tmp = Lk[b_k];
            Lk[b_k] = Lk[b_subs2_idx_1 - 1];
            Lk[b_subs2_idx_1 - 1] = b_tmp;
        }
    }
    // 'splineLengthFindU:43' C_ASSERT_MSG = 'u0 must be %s or equal than the first spline knot';
    // 'splineLengthFindU:44' ocn_assert( u0 >= Knots(1),   sprintf(C_ASSERT_MSG, 'greater'),
    // mfilename );
    s_ocn_assert(u0 >= Knots[0]);
    // 'splineLengthFindU:45' ocn_assert( u0 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller'),
    // mfilename );
    t_ocn_assert(u0 <= Knots[Knots.size(1) - 1]);
    // 'splineLengthFindU:47' kStartVec = find( Knots <= u0, 1, "last" );
    b_Knots.set_size(1, Knots.size(1));
    c_loop_ub = Knots.size(1);
    for (int i5{0}; i5 < c_loop_ub; i5++) {
        b_Knots[i5] = (Knots[i5] <= u0);
    }
    coder::eml_find(b_Knots, (int *)&LkEndVec_data, LkEndVec_size);
    d_loop_ub = LkEndVec_size[1];
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        kStartVec_data = LkEndVec_data;
    }
    // 'splineLengthFindU:48' kStart    = kStartVec( 1 );
    // 'splineLengthFindU:50' if( Knots( kStart ) < u0 )
    d = Knots[kStartVec_data - 1];
    if (d < u0) {
        __m128d r1;
        __m128d r2;
        __m128d r3;
        __m128d r4;
        __m128d r5;
        double c_r1Dnorm;
        int h_loop_ub;
        // 'splineLengthFindU:51' LStart = splineLengthApprox_Interval( cfg, spline, Knots( kStart
        // ), u0, isEnd );
        //  splineLengthApprox_Interval : Computes approximately the arc length L
        //  with integration bounds u1 and u2.
        //
        //  IMPORTANT : u0 and u1 should lie in the same knot interval.
        //  The computation is based on numerical Gauss Legendre integration
        //
        //  Inputs :
        //    cfg     : The configuration structure
        //    spline  : The spline
        //    u0      : The starting u
        //    u1      : The ending u
        //    isEnd   : Boolean value. TRUE means the length is computed from the
        //              curve's end.
        //
        //  Outputs :
        //    L       : The resulting length
        //
        //  get Gauss-Legendre knots and weights
        // 'splineLengthApprox_Interval:22' GL_X   = cfg.GaussLegendreX;
        // 'splineLengthApprox_Interval:23' GL_W   = cfg.GaussLegendreW;
        // 'splineLengthApprox_Interval:25' if( isEnd )
        // 'splineLengthApprox_Interval:26' a   = 1 - u0;
        // 'splineLengthApprox_Interval:27' u0  = 1 - u1;
        // 'splineLengthApprox_Interval:28' u1  = a;
        //  apply linear map from[-1, 1] to [u0, u1]
        // 'splineLengthApprox_Interval:32' uvec   = ( ( u0 * ( 1 - GL_X ) + u1 * ( 1 + GL_X ) ) / 2
        // ).';
        //
        // 'splineLengthApprox_Interval:35' [ ~, r1D ]  = EvalBSpline( spline, uvec );
        r1 = _mm_loadu_pd((const double *)&cfg_GaussLegendreX[0]);
        r2 = _mm_set1_pd(1.0);
        r3 = _mm_set1_pd(1.0 - u0);
        r4 = _mm_set1_pd(1.0 - d);
        r5 = _mm_set1_pd(2.0);
        _mm_storeu_pd(&dv[0], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r3, _mm_sub_pd(r2, r1)),
                                                    _mm_mul_pd(r4, _mm_add_pd(r1, r2))),
                                         r5));
        r1 = _mm_loadu_pd((const double *)&cfg_GaussLegendreX[2]);
        _mm_storeu_pd(&dv[2], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r3, _mm_sub_pd(r2, r1)),
                                                    _mm_mul_pd(r4, _mm_add_pd(r1, r2))),
                                         r5));
        dv[4] = ((1.0 - u0) * (1.0 - cfg_GaussLegendreX[4]) +
                 (1.0 - d) * (cfg_GaussLegendreX[4] + 1.0)) /
                2.0;
        EvalBSpline(spline_sp_Bl_handle, spline_sp_coeff, dv, a__1, r1D);
        // 'splineLengthApprox_Interval:36' r1Dnorm     = MyNorm( r1D );
        //  MyNorm : My implementation of the norm computation.
        //
        //  Inputs :
        //    x   : The input vector.
        //
        //  Outputs :
        //    n   : The resulting norm.
        //
        // 'MyNorm:10' coder.inline( 'always' );
        // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
        r6.set_size(r1D.size(0), 5);
        h_loop_ub = r1D.size(0);
        for (int i13{0}; i13 < 5; i13++) {
            for (int i14{0}; i14 < h_loop_ub; i14++) {
                double varargin_1;
                varargin_1 = r1D[i14 + r1D.size(0) * i13];
                r6[i14 + r6.size(0) * i13] = std::pow(varargin_1, 2.0);
            }
        }
        coder::sum(r6, r1Dnorm);
        //  mysqrt : Custom implementation of the sqrt method.
        //
        //  Inputs :
        //    x : Value used for the computation
        //  Outputs :
        //    y : Resulting value
        //
        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
        for (int i15{0}; i15 < 5; i15++) {
            b_r1Dnorm[i15] = (r1Dnorm[i15] >= 0.0);
        }
        n_ocn_assert(b_r1Dnorm);
        // 'mysqrt:11' y = sqrt(x);
        // 'splineLengthApprox_Interval:37' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
        c_r1Dnorm = 0.0;
        for (int d_k{0}; d_k < 5; d_k++) {
            double d1;
            d1 = std::sqrt(r1Dnorm[d_k]);
            r1Dnorm[d_k] = d1;
            c_r1Dnorm += d1 * cfg_GaussLegendreW[d_k];
        }
        LStart = c_r1Dnorm * ((1.0 - d) - (1.0 - u0)) / 2.0;
        //  Gauss Legendre integration
        // 'splineLengthApprox_Interval:38' L = L( 1 );
        //  to satisfy Matlab Coder
    } else {
        // 'splineLengthFindU:52' else
        // 'splineLengthFindU:53' LStart = 0;
        LStart = 0.0;
    }
    // 'splineLengthFindU:56' LEnd = cumsum( Lk( kStart : kMax) ) - LStart;
    if (kStartVec_data > spline_sp_Lk.size(1)) {
        i7 = -1;
        i8 = -1;
    } else {
        i7 = kStartVec_data - 2;
        i8 = spline_sp_Lk.size(1) - 1;
    }
    e_loop_ub = i8 - i7;
    x.set_size(1, e_loop_ub);
    for (int i9{0}; i9 < e_loop_ub; i9++) {
        x[i9] = Lk[(i7 + i9) + 1];
    }
    if ((e_loop_ub != 0) && (e_loop_ub != 1)) {
        int i10;
        i10 = e_loop_ub - 2;
        for (int c_k{0}; c_k <= i10; c_k++) {
            x[c_k + 1] = x[c_k] + x[c_k + 1];
        }
    }
    LEnd.set_size(1, x.size(1));
    f_loop_ub = x.size(1);
    b_scalarLB = (x.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (int i11{0}; i11 <= b_vectorUB; i11 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&x[i11]);
        _mm_storeu_pd(&LEnd[i11], _mm_sub_pd(r, _mm_set1_pd(LStart)));
    }
    for (int i11{b_scalarLB}; i11 < f_loop_ub; i11++) {
        LEnd[i11] = x[i11] - LStart;
    }
    // 'splineLengthFindU:58' LkEndVec = find( LEnd >= L, 1, "first" );
    b_LEnd.set_size(1, LEnd.size(1));
    g_loop_ub = LEnd.size(1);
    for (int i12{0}; i12 < g_loop_ub; i12++) {
        b_LEnd[i12] = (LEnd[i12] >= L);
    }
    coder::b_eml_find(b_LEnd, (int *)&LkEndVec_data, LkEndVec_size);
    // 'splineLengthFindU:59' if( isempty( LkEndVec ) )
    if (LkEndVec_size[1] == 0) {
        // 'splineLengthFindU:60' u = -1;
        u = -1.0;
    } else {
        double LDiff;
        double b_u;
        double fk;
        double kEnd;
        double uLeft;
        double uMiddle;
        double uRight;
        double uRight_tmp;
        double uStart_tmp;
        int count;
        // 'splineLengthFindU:61' else
        // 'splineLengthFindU:62' LkEnd    = LkEndVec( 1 );
        // 'splineLengthFindU:63' if( LkEnd > 1 )
        if (LkEndVec_data > 1) {
            // 'splineLengthFindU:64' LDiff = L - LEnd( LkEnd - 1 );
            LDiff = L - LEnd[LkEndVec_data - 2];
        } else {
            // 'splineLengthFindU:65' else
            // 'splineLengthFindU:66' LDiff = L + LStart;
            LDiff = L + LStart;
        }
        // 'splineLengthFindU:70' kEnd = LkEnd + kStart;
        kEnd = static_cast<double>(LkEndVec_data) + static_cast<double>(kStartVec_data);
        // 'splineLengthFindU:72' uLeft       = Knots( kEnd -1 );
        uLeft = Knots[static_cast<int>(kEnd - 1.0) - 1];
        // 'splineLengthFindU:73' uRight      = Knots( kEnd );
        uRight_tmp = Knots[static_cast<int>(kEnd) - 1];
        uRight = uRight_tmp;
        // 'splineLengthFindU:75' [ u, count ] = bisection( uLeft, uRight, cfg, spline, LDiff,
        // ITER_MAX, DEFAULT_TOL, isEnd );
        // -------------------------------------------------------------------------%
        //  Functions
        // -------------------------------------------------------------------------%
        // 'splineLengthFindU:90' count   = 0;
        count = 0;
        // 'splineLengthFindU:91' uStart  = uLeft;
        uStart_tmp = Knots[static_cast<int>(kEnd) - 2];
        // 'splineLengthFindU:92' fk      = tol * 1.1;
        fk = 1.1E-7;
        // 'splineLengthFindU:94' uMiddle = ( uLeft + uRight ) / 2;
        uMiddle = (uStart_tmp + uRight_tmp) / 2.0;
        // 'splineLengthFindU:96' while( count < iterMax && abs( fk ) > tol )
        while ((count < 1000) && (std::abs(fk) > 1.0E-7)) {
            __m128d r10;
            __m128d r11;
            __m128d r7;
            __m128d r8;
            __m128d r9;
            double d_r1Dnorm;
            int i_loop_ub;
            // 'splineLengthFindU:97' uMiddle = ( uLeft + uRight ) / 2;
            uMiddle = (uLeft + uRight) / 2.0;
            // 'splineLengthFindU:99' fk  = splineLengthApprox_Interval( cfg, spline, uStart,
            // uMiddle, isEnd ) - LDiff;
            //  splineLengthApprox_Interval : Computes approximately the arc length L
            //  with integration bounds u1 and u2.
            //
            //  IMPORTANT : u0 and u1 should lie in the same knot interval.
            //  The computation is based on numerical Gauss Legendre integration
            //
            //  Inputs :
            //    cfg     : The configuration structure
            //    spline  : The spline
            //    u0      : The starting u
            //    u1      : The ending u
            //    isEnd   : Boolean value. TRUE means the length is computed from the
            //              curve's end.
            //
            //  Outputs :
            //    L       : The resulting length
            //
            //  get Gauss-Legendre knots and weights
            // 'splineLengthApprox_Interval:22' GL_X   = cfg.GaussLegendreX;
            // 'splineLengthApprox_Interval:23' GL_W   = cfg.GaussLegendreW;
            // 'splineLengthApprox_Interval:25' if( isEnd )
            // 'splineLengthApprox_Interval:26' a   = 1 - u0;
            // 'splineLengthApprox_Interval:27' u0  = 1 - u1;
            // 'splineLengthApprox_Interval:28' u1  = a;
            //  apply linear map from[-1, 1] to [u0, u1]
            // 'splineLengthApprox_Interval:32' uvec   = ( ( u0 * ( 1 - GL_X ) + u1 * ( 1 + GL_X ) )
            // / 2 ).';
            //
            // 'splineLengthApprox_Interval:35' [ ~, r1D ]  = EvalBSpline( spline, uvec );
            r7 = _mm_loadu_pd((const double *)&cfg_GaussLegendreX[0]);
            r8 = _mm_set1_pd(1.0);
            r9 = _mm_set1_pd(1.0 - uMiddle);
            r10 = _mm_set1_pd(1.0 - uStart_tmp);
            r11 = _mm_set1_pd(2.0);
            _mm_storeu_pd(&dv[0], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r9, _mm_sub_pd(r8, r7)),
                                                        _mm_mul_pd(r10, _mm_add_pd(r7, r8))),
                                             r11));
            r7 = _mm_loadu_pd((const double *)&cfg_GaussLegendreX[2]);
            _mm_storeu_pd(&dv[2], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r9, _mm_sub_pd(r8, r7)),
                                                        _mm_mul_pd(r10, _mm_add_pd(r7, r8))),
                                             r11));
            dv[4] = ((1.0 - uMiddle) * (1.0 - cfg_GaussLegendreX[4]) +
                     (1.0 - uStart_tmp) * (cfg_GaussLegendreX[4] + 1.0)) /
                    2.0;
            EvalBSpline(spline_sp_Bl_handle, spline_sp_coeff, dv, a__1, r1D);
            // 'splineLengthApprox_Interval:36' r1Dnorm     = MyNorm( r1D );
            //  MyNorm : My implementation of the norm computation.
            //
            //  Inputs :
            //    x   : The input vector.
            //
            //  Outputs :
            //    n   : The resulting norm.
            //
            // 'MyNorm:10' coder.inline( 'always' );
            // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
            r6.set_size(r1D.size(0), 5);
            i_loop_ub = r1D.size(0);
            for (int i16{0}; i16 < 5; i16++) {
                for (int i17{0}; i17 < i_loop_ub; i17++) {
                    double b_varargin_1;
                    b_varargin_1 = r1D[i17 + r1D.size(0) * i16];
                    r6[i17 + r6.size(0) * i16] = std::pow(b_varargin_1, 2.0);
                }
            }
            coder::sum(r6, r1Dnorm);
            //  mysqrt : Custom implementation of the sqrt method.
            //
            //  Inputs :
            //    x : Value used for the computation
            //  Outputs :
            //    y : Resulting value
            //
            // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
            // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
            for (int i18{0}; i18 < 5; i18++) {
                b_r1Dnorm[i18] = (r1Dnorm[i18] >= 0.0);
            }
            n_ocn_assert(b_r1Dnorm);
            // 'mysqrt:11' y = sqrt(x);
            // 'splineLengthApprox_Interval:37' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
            //  Gauss Legendre integration
            // 'splineLengthApprox_Interval:38' L = L( 1 );
            //  to satisfy Matlab Coder
            d_r1Dnorm = 0.0;
            for (int e_k{0}; e_k < 5; e_k++) {
                double d2;
                d2 = std::sqrt(r1Dnorm[e_k]);
                r1Dnorm[e_k] = d2;
                d_r1Dnorm += d2 * cfg_GaussLegendreW[e_k];
            }
            fk = d_r1Dnorm * ((1.0 - uStart_tmp) - (1.0 - uMiddle)) / 2.0 - LDiff;
            // 'splineLengthFindU:101' if( fk > 0 )
            if (fk > 0.0) {
                // 'splineLengthFindU:102' uRight = uMiddle;
                uRight = uMiddle;
            } else {
                // 'splineLengthFindU:103' else
                // 'splineLengthFindU:104' uLeft  = uMiddle;
                uLeft = uMiddle;
            }
            // 'splineLengthFindU:106' count = count + 1;
            count++;
        }
        // 'splineLengthFindU:109' if( count >= iterMax )
        if (count >= 1000) {
            // 'splineLengthFindU:110' u = -1;
            b_u = -1.0;
        } else {
            // 'splineLengthFindU:111' else
            // 'splineLengthFindU:112' u = uMiddle;
            b_u = uMiddle;
        }
        u = b_u;
        // 'splineLengthFindU:77' ocn_assert(~(u < 0), "Fails to compute length", mfilename);
        u_ocn_assert(b_u >= 0.0);
        // 'splineLengthFindU:79' if( isEnd && u >= 0 )
        if (b_u >= 0.0) {
            // 'splineLengthFindU:80' u = 1 -u;
            u = 1.0 - b_u;
        }
    }
    return u;
}

//
// function [ u ]  = splineLengthFindU( cfg, spline, L, u0, isEnd )
//
// splineLengthFindU : Computes approximately the value of curve parameter
//  u such that the arc length starting from u1 equals L.
//  This function takes usage of the precalculated arc lengths between knots.
//  The last integration interval is approximated by the trapezoidal rule.
//  u1 must satisfy 0 < u1 < 1.
//  In the normal case, u must satisfy 0 < u < u1. If L is too large, u is
//  set to -1.
//  The parameter isEnd is used to start inverse the problem, the length is
//  estimated starting from u quals to 1 to 0. It's used to cut a specific
//  length at the beginning of the curv.
//
//  Inputs :
//    cfg     : The configuration structure
//    spline  : The spline
//    L       : The length of the spline
//    u0      : The starting u
//    isEnd   : Boolean value. TRUE means the computation should start from
//              the end.
//
//  Outputs :
//    u       : The resulting u value
//
//
// Arguments    : const double cfg_GaussLegendreX[5]
//                const double cfg_GaussLegendreW[5]
//                unsigned long spline_sp_Bl_handle
//                int spline_sp_Bl_order
//                const ::coder::array<double, 2U> &spline_sp_coeff
//                const ::coder::array<double, 2U> &spline_sp_knots
//                const ::coder::array<double, 2U> &spline_sp_Lk
//                double L
//                double u0
// Return Type  : double
//
double splineLengthFindU(const double cfg_GaussLegendreX[5], const double cfg_GaussLegendreW[5],
                         unsigned long spline_sp_Bl_handle, int spline_sp_Bl_order,
                         const ::coder::array<double, 2U> &spline_sp_coeff,
                         const ::coder::array<double, 2U> &spline_sp_knots,
                         const ::coder::array<double, 2U> &spline_sp_Lk, double L, double u0)
{
    ::coder::array<double, 2U> LEnd;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> x;
    ::coder::array<bool, 2U> b_LEnd;
    ::coder::array<bool, 2U> b_spline_sp_knots;
    double d_spline_sp_knots[5];
    double r1Dnorm[5];
    double uStart[5];
    double LStart;
    double c_spline_sp_knots;
    double u;
    int LkEndVec_size[2];
    int LkEndVec_data;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int i;
    int i1;
    int i2;
    int i5;
    int i6;
    int kStartVec_data;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    bool b_r1Dnorm[5];
    // 'splineLengthFindU:25' ITER_MAX    = 1000;
    // 'splineLengthFindU:26' DEFAULT_TOL = 1E-7;
    //  Get the sp structure
    // 'splineLengthFindU:29' sp     = spline.sp;
    // 'splineLengthFindU:31' IND_KNOTS_MULT  = sp.Bl.order;
    //  Index used to remove multiple knots
    //  Eliminate multiplicities at the end points
    // 'splineLengthFindU:33' Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
    i = spline_sp_knots.size(1) - spline_sp_Bl_order;
    if (spline_sp_Bl_order > i + 1) {
        i1 = -1;
        i2 = -1;
    } else {
        i1 = spline_sp_Bl_order - 2;
        i2 = i;
    }
    // 'splineLengthFindU:34' Lk     = sp.Lk;
    // 'splineLengthFindU:35' kMax   = numel( Lk );
    // 'splineLengthFindU:37' if( isEnd )
    // 'splineLengthFindU:43' C_ASSERT_MSG = 'u0 must be %s or equal than the first spline knot';
    // 'splineLengthFindU:44' ocn_assert( u0 >= Knots(1),   sprintf(C_ASSERT_MSG, 'greater'),
    // mfilename );
    s_ocn_assert(u0 >= spline_sp_knots[i1 + 1]);
    // 'splineLengthFindU:45' ocn_assert( u0 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller'),
    // mfilename );
    t_ocn_assert(u0 <= spline_sp_knots[i2]);
    // 'splineLengthFindU:47' kStartVec = find( Knots <= u0, 1, "last" );
    loop_ub = i2 - i1;
    b_spline_sp_knots.set_size(1, loop_ub);
    for (int i3{0}; i3 < loop_ub; i3++) {
        b_spline_sp_knots[i3] = (spline_sp_knots[(i1 + i3) + 1] <= u0);
    }
    coder::eml_find(b_spline_sp_knots, (int *)&LkEndVec_data, LkEndVec_size);
    b_loop_ub = LkEndVec_size[1];
    for (int i4{0}; i4 < b_loop_ub; i4++) {
        kStartVec_data = LkEndVec_data;
    }
    // 'splineLengthFindU:48' kStart    = kStartVec( 1 );
    // 'splineLengthFindU:50' if( Knots( kStart ) < u0 )
    c_spline_sp_knots = spline_sp_knots[i1 + kStartVec_data];
    if (c_spline_sp_knots < u0) {
        __m128d r1;
        __m128d r2;
        __m128d r3;
        __m128d r4;
        __m128d r5;
        double c_r1Dnorm;
        int f_loop_ub;
        // 'splineLengthFindU:51' LStart = splineLengthApprox_Interval( cfg, spline, Knots( kStart
        // ), u0, isEnd );
        //  splineLengthApprox_Interval : Computes approximately the arc length L
        //  with integration bounds u1 and u2.
        //
        //  IMPORTANT : u0 and u1 should lie in the same knot interval.
        //  The computation is based on numerical Gauss Legendre integration
        //
        //  Inputs :
        //    cfg     : The configuration structure
        //    spline  : The spline
        //    u0      : The starting u
        //    u1      : The ending u
        //    isEnd   : Boolean value. TRUE means the length is computed from the
        //              curve's end.
        //
        //  Outputs :
        //    L       : The resulting length
        //
        //  get Gauss-Legendre knots and weights
        // 'splineLengthApprox_Interval:22' GL_X   = cfg.GaussLegendreX;
        // 'splineLengthApprox_Interval:23' GL_W   = cfg.GaussLegendreW;
        // 'splineLengthApprox_Interval:25' if( isEnd )
        //  apply linear map from[-1, 1] to [u0, u1]
        // 'splineLengthApprox_Interval:32' uvec   = ( ( u0 * ( 1 - GL_X ) + u1 * ( 1 + GL_X ) ) / 2
        // ).';
        //
        // 'splineLengthApprox_Interval:35' [ ~, r1D ]  = EvalBSpline( spline, uvec );
        r1 = _mm_loadu_pd((const double *)&cfg_GaussLegendreX[0]);
        r2 = _mm_set1_pd(1.0);
        r3 = _mm_set1_pd(c_spline_sp_knots);
        r4 = _mm_set1_pd(u0);
        r5 = _mm_set1_pd(2.0);
        _mm_storeu_pd(&d_spline_sp_knots[0],
                      _mm_div_pd(_mm_add_pd(_mm_mul_pd(r3, _mm_sub_pd(r2, r1)),
                                            _mm_mul_pd(r4, _mm_add_pd(r1, r2))),
                                 r5));
        r1 = _mm_loadu_pd((const double *)&cfg_GaussLegendreX[2]);
        _mm_storeu_pd(&d_spline_sp_knots[2],
                      _mm_div_pd(_mm_add_pd(_mm_mul_pd(r3, _mm_sub_pd(r2, r1)),
                                            _mm_mul_pd(r4, _mm_add_pd(r1, r2))),
                                 r5));
        d_spline_sp_knots[4] = (c_spline_sp_knots * (1.0 - cfg_GaussLegendreX[4]) +
                                u0 * (cfg_GaussLegendreX[4] + 1.0)) /
                               2.0;
        EvalBSpline(spline_sp_Bl_handle, spline_sp_coeff, d_spline_sp_knots, a__1, r1D);
        // 'splineLengthApprox_Interval:36' r1Dnorm     = MyNorm( r1D );
        //  MyNorm : My implementation of the norm computation.
        //
        //  Inputs :
        //    x   : The input vector.
        //
        //  Outputs :
        //    n   : The resulting norm.
        //
        // 'MyNorm:10' coder.inline( 'always' );
        // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
        r6.set_size(r1D.size(0), 5);
        f_loop_ub = r1D.size(0);
        for (int i11{0}; i11 < 5; i11++) {
            for (int i12{0}; i12 < f_loop_ub; i12++) {
                double varargin_1;
                varargin_1 = r1D[i12 + r1D.size(0) * i11];
                r6[i12 + r6.size(0) * i11] = std::pow(varargin_1, 2.0);
            }
        }
        coder::sum(r6, r1Dnorm);
        //  mysqrt : Custom implementation of the sqrt method.
        //
        //  Inputs :
        //    x : Value used for the computation
        //  Outputs :
        //    y : Resulting value
        //
        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
        for (int i13{0}; i13 < 5; i13++) {
            b_r1Dnorm[i13] = (r1Dnorm[i13] >= 0.0);
        }
        n_ocn_assert(b_r1Dnorm);
        // 'mysqrt:11' y = sqrt(x);
        // 'splineLengthApprox_Interval:37' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
        c_r1Dnorm = 0.0;
        for (int b_k{0}; b_k < 5; b_k++) {
            double d;
            d = std::sqrt(r1Dnorm[b_k]);
            r1Dnorm[b_k] = d;
            c_r1Dnorm += d * cfg_GaussLegendreW[b_k];
        }
        LStart = c_r1Dnorm * (u0 - c_spline_sp_knots) / 2.0;
        //  Gauss Legendre integration
        // 'splineLengthApprox_Interval:38' L = L( 1 );
        //  to satisfy Matlab Coder
    } else {
        // 'splineLengthFindU:52' else
        // 'splineLengthFindU:53' LStart = 0;
        LStart = 0.0;
    }
    // 'splineLengthFindU:56' LEnd = cumsum( Lk( kStart : kMax) ) - LStart;
    if (kStartVec_data > spline_sp_Lk.size(1)) {
        i5 = -1;
        i6 = -1;
    } else {
        i5 = kStartVec_data - 2;
        i6 = spline_sp_Lk.size(1) - 1;
    }
    c_loop_ub = i6 - i5;
    x.set_size(1, c_loop_ub);
    for (int i7{0}; i7 < c_loop_ub; i7++) {
        x[i7] = spline_sp_Lk[(i5 + i7) + 1];
    }
    if ((c_loop_ub != 0) && (c_loop_ub != 1)) {
        int i8;
        i8 = c_loop_ub - 2;
        for (int k{0}; k <= i8; k++) {
            x[k + 1] = x[k] + x[k + 1];
        }
    }
    LEnd.set_size(1, x.size(1));
    d_loop_ub = x.size(1);
    scalarLB = (x.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i9{0}; i9 <= vectorUB; i9 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&x[i9]);
        _mm_storeu_pd(&LEnd[i9], _mm_sub_pd(r, _mm_set1_pd(LStart)));
    }
    for (int i9{scalarLB}; i9 < d_loop_ub; i9++) {
        LEnd[i9] = x[i9] - LStart;
    }
    // 'splineLengthFindU:58' LkEndVec = find( LEnd >= L, 1, "first" );
    b_LEnd.set_size(1, LEnd.size(1));
    e_loop_ub = LEnd.size(1);
    for (int i10{0}; i10 < e_loop_ub; i10++) {
        b_LEnd[i10] = (LEnd[i10] >= L);
    }
    coder::b_eml_find(b_LEnd, (int *)&LkEndVec_data, LkEndVec_size);
    // 'splineLengthFindU:59' if( isempty( LkEndVec ) )
    if (LkEndVec_size[1] == 0) {
        // 'splineLengthFindU:60' u = -1;
        u = -1.0;
    } else {
        double LDiff;
        double b_u;
        double b_uRight_tmp;
        double fk;
        double kEnd;
        double uLeft;
        double uMiddle;
        double uRight;
        double uStart_tmp;
        int count;
        int uRight_tmp;
        // 'splineLengthFindU:61' else
        // 'splineLengthFindU:62' LkEnd    = LkEndVec( 1 );
        // 'splineLengthFindU:63' if( LkEnd > 1 )
        if (LkEndVec_data > 1) {
            // 'splineLengthFindU:64' LDiff = L - LEnd( LkEnd - 1 );
            LDiff = L - LEnd[LkEndVec_data - 2];
        } else {
            // 'splineLengthFindU:65' else
            // 'splineLengthFindU:66' LDiff = L + LStart;
            LDiff = L + LStart;
        }
        // 'splineLengthFindU:70' kEnd = LkEnd + kStart;
        kEnd = static_cast<double>(LkEndVec_data) + static_cast<double>(kStartVec_data);
        // 'splineLengthFindU:72' uLeft       = Knots( kEnd -1 );
        uLeft = spline_sp_knots[i1 + static_cast<int>(kEnd - 1.0)];
        // 'splineLengthFindU:73' uRight      = Knots( kEnd );
        uRight_tmp = i1 + static_cast<int>(kEnd);
        b_uRight_tmp = spline_sp_knots[uRight_tmp];
        uRight = b_uRight_tmp;
        // 'splineLengthFindU:75' [ u, count ] = bisection( uLeft, uRight, cfg, spline, LDiff,
        // ITER_MAX, DEFAULT_TOL, isEnd );
        // -------------------------------------------------------------------------%
        //  Functions
        // -------------------------------------------------------------------------%
        // 'splineLengthFindU:90' count   = 0;
        count = 0;
        // 'splineLengthFindU:91' uStart  = uLeft;
        uStart_tmp = spline_sp_knots[uRight_tmp - 1];
        // 'splineLengthFindU:92' fk      = tol * 1.1;
        fk = 1.1E-7;
        // 'splineLengthFindU:94' uMiddle = ( uLeft + uRight ) / 2;
        uMiddle = (uStart_tmp + b_uRight_tmp) / 2.0;
        // 'splineLengthFindU:96' while( count < iterMax && abs( fk ) > tol )
        while ((count < 1000) && (std::abs(fk) > 1.0E-7)) {
            __m128d r10;
            __m128d r11;
            __m128d r7;
            __m128d r8;
            __m128d r9;
            double d_r1Dnorm;
            int g_loop_ub;
            // 'splineLengthFindU:97' uMiddle = ( uLeft + uRight ) / 2;
            uMiddle = (uLeft + uRight) / 2.0;
            // 'splineLengthFindU:99' fk  = splineLengthApprox_Interval( cfg, spline, uStart,
            // uMiddle, isEnd ) - LDiff;
            //  splineLengthApprox_Interval : Computes approximately the arc length L
            //  with integration bounds u1 and u2.
            //
            //  IMPORTANT : u0 and u1 should lie in the same knot interval.
            //  The computation is based on numerical Gauss Legendre integration
            //
            //  Inputs :
            //    cfg     : The configuration structure
            //    spline  : The spline
            //    u0      : The starting u
            //    u1      : The ending u
            //    isEnd   : Boolean value. TRUE means the length is computed from the
            //              curve's end.
            //
            //  Outputs :
            //    L       : The resulting length
            //
            //  get Gauss-Legendre knots and weights
            // 'splineLengthApprox_Interval:22' GL_X   = cfg.GaussLegendreX;
            // 'splineLengthApprox_Interval:23' GL_W   = cfg.GaussLegendreW;
            // 'splineLengthApprox_Interval:25' if( isEnd )
            //  apply linear map from[-1, 1] to [u0, u1]
            // 'splineLengthApprox_Interval:32' uvec   = ( ( u0 * ( 1 - GL_X ) + u1 * ( 1 + GL_X ) )
            // / 2 ).';
            //
            // 'splineLengthApprox_Interval:35' [ ~, r1D ]  = EvalBSpline( spline, uvec );
            r7 = _mm_loadu_pd((const double *)&cfg_GaussLegendreX[0]);
            r8 = _mm_set1_pd(1.0);
            r9 = _mm_set1_pd(uStart_tmp);
            r10 = _mm_set1_pd(uMiddle);
            r11 = _mm_set1_pd(2.0);
            _mm_storeu_pd(&uStart[0], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r9, _mm_sub_pd(r8, r7)),
                                                            _mm_mul_pd(r10, _mm_add_pd(r7, r8))),
                                                 r11));
            r7 = _mm_loadu_pd((const double *)&cfg_GaussLegendreX[2]);
            _mm_storeu_pd(&uStart[2], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r9, _mm_sub_pd(r8, r7)),
                                                            _mm_mul_pd(r10, _mm_add_pd(r7, r8))),
                                                 r11));
            uStart[4] = (uStart_tmp * (1.0 - cfg_GaussLegendreX[4]) +
                         uMiddle * (cfg_GaussLegendreX[4] + 1.0)) /
                        2.0;
            EvalBSpline(spline_sp_Bl_handle, spline_sp_coeff, uStart, a__1, r1D);
            // 'splineLengthApprox_Interval:36' r1Dnorm     = MyNorm( r1D );
            //  MyNorm : My implementation of the norm computation.
            //
            //  Inputs :
            //    x   : The input vector.
            //
            //  Outputs :
            //    n   : The resulting norm.
            //
            // 'MyNorm:10' coder.inline( 'always' );
            // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
            r6.set_size(r1D.size(0), 5);
            g_loop_ub = r1D.size(0);
            for (int i14{0}; i14 < 5; i14++) {
                for (int i15{0}; i15 < g_loop_ub; i15++) {
                    double b_varargin_1;
                    b_varargin_1 = r1D[i15 + r1D.size(0) * i14];
                    r6[i15 + r6.size(0) * i14] = std::pow(b_varargin_1, 2.0);
                }
            }
            coder::sum(r6, r1Dnorm);
            //  mysqrt : Custom implementation of the sqrt method.
            //
            //  Inputs :
            //    x : Value used for the computation
            //  Outputs :
            //    y : Resulting value
            //
            // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
            // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
            for (int i16{0}; i16 < 5; i16++) {
                b_r1Dnorm[i16] = (r1Dnorm[i16] >= 0.0);
            }
            n_ocn_assert(b_r1Dnorm);
            // 'mysqrt:11' y = sqrt(x);
            // 'splineLengthApprox_Interval:37' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
            //  Gauss Legendre integration
            // 'splineLengthApprox_Interval:38' L = L( 1 );
            //  to satisfy Matlab Coder
            d_r1Dnorm = 0.0;
            for (int c_k{0}; c_k < 5; c_k++) {
                double d1;
                d1 = std::sqrt(r1Dnorm[c_k]);
                r1Dnorm[c_k] = d1;
                d_r1Dnorm += d1 * cfg_GaussLegendreW[c_k];
            }
            fk = d_r1Dnorm * (uMiddle - uStart_tmp) / 2.0 - LDiff;
            // 'splineLengthFindU:101' if( fk > 0 )
            if (fk > 0.0) {
                // 'splineLengthFindU:102' uRight = uMiddle;
                uRight = uMiddle;
            } else {
                // 'splineLengthFindU:103' else
                // 'splineLengthFindU:104' uLeft  = uMiddle;
                uLeft = uMiddle;
            }
            // 'splineLengthFindU:106' count = count + 1;
            count++;
        }
        // 'splineLengthFindU:109' if( count >= iterMax )
        if (count >= 1000) {
            // 'splineLengthFindU:110' u = -1;
            b_u = -1.0;
        } else {
            // 'splineLengthFindU:111' else
            // 'splineLengthFindU:112' u = uMiddle;
            b_u = uMiddle;
        }
        u = b_u;
        // 'splineLengthFindU:77' ocn_assert(~(u < 0), "Fails to compute length", mfilename);
        u_ocn_assert(b_u >= 0.0);
        // 'splineLengthFindU:79' if( isEnd && u >= 0 )
    }
    return u;
}

} // namespace ocn

//
// File trailer for splineLengthFindU.cpp
//
// [EOF]
//
