
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: splineLength.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "splineLength.h"
#include "EvalBSpline.h"
#include "find.h"
#include "ocn_assert.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function [ L ] = splineLength( cfg, spline, u1, u2 )
//
// splineLength : Compute the spline length between u1 and u2.
//
//  Inputs :
//  cfg       : The configuration structure
//  spline    : The spline
//  u1        : The starting u
//  u2        : The endind u
//
//  Outputs :
//  L         : The resulting length of the spline
//
//
// Arguments    : const double cfg_GaussLegendreX[5]
//                const double cfg_GaussLegendreW[5]
//                unsigned long spline_sp_Bl_handle
//                int spline_sp_Bl_order
//                const ::coder::array<double, 2U> &spline_sp_coeff
//                const ::coder::array<double, 2U> &spline_sp_knots
//                const ::coder::array<double, 2U> &spline_sp_Lk
//                double u1
//                double u2
// Return Type  : double
//
namespace ocn {
double splineLength(const double cfg_GaussLegendreX[5], const double cfg_GaussLegendreW[5],
                    unsigned long spline_sp_Bl_handle, int spline_sp_Bl_order,
                    const ::coder::array<double, 2U> &spline_sp_coeff,
                    const ::coder::array<double, 2U> &spline_sp_knots,
                    const ::coder::array<double, 2U> &spline_sp_Lk, double u1, double u2)
{
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_spline_sp_Lk;
    ::coder::array<double, 2U> r10;
    ::coder::array<double, 2U> r1D;
    ::coder::array<bool, 2U> b_spline_sp_knots;
    double b_u2[5];
    double e_spline_sp_knots[5];
    double r1Dnorm[5];
    double LEnd;
    double LStart;
    double c_spline_sp_knots;
    double d_spline_sp_knots;
    int kEndVec_size[2];
    int b_loop_ub;
    int c_loop_ub;
    int i;
    int i1;
    int i2;
    int i6;
    int i7;
    int kEndVec_data;
    int kStartVec_data;
    int loop_ub;
    bool b_r1Dnorm[5];
    // 'splineLength:13' sp = spline.sp;
    // 'splineLength:14' IND_KNOTS_MULT  = sp.Bl.order;
    //  Index used to remove multiple knots
    //  Eliminate multiplicities at the end points
    // 'splineLength:16' Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
    i = spline_sp_knots.size(1) - spline_sp_Bl_order;
    if (spline_sp_Bl_order > i + 1) {
        i1 = -1;
        i2 = -1;
    } else {
        i1 = spline_sp_Bl_order - 2;
        i2 = i;
    }
    // 'splineLength:17' Lk     = sp.Lk;
    // 'splineLength:19' ocn_assert( u2 > u1,          'u2 must be greater than u1', mfilename);
    k_ocn_assert(u2 > u1);
    // 'splineLength:20' ocn_assert( u1 >= Knots(1),   'u1 must be greater or equal than the first
    // spline knot', mfilename);
    l_ocn_assert(u1 >= spline_sp_knots[i1 + 1]);
    // 'splineLength:21' ocn_assert( u2 <= Knots(end), 'u2 must be smaller or equal than the last
    // spline knot', mfilename);
    m_ocn_assert(u2 <= spline_sp_knots[i2]);
    // 'splineLength:23' kStartVec  = find( Knots <= u1, 1, "last" );
    loop_ub = i2 - i1;
    b_spline_sp_knots.set_size(1, loop_ub);
    for (int i3{0}; i3 < loop_ub; i3++) {
        b_spline_sp_knots[i3] = (spline_sp_knots[(i1 + i3) + 1] <= u1);
    }
    coder::eml_find(b_spline_sp_knots, (int *)&kEndVec_data, kEndVec_size);
    b_loop_ub = kEndVec_size[1];
    for (int i4{0}; i4 < b_loop_ub; i4++) {
        kStartVec_data = kEndVec_data;
    }
    // 'splineLength:24' kEndVec    = find( Knots >= u2, 1, "first" );
    b_spline_sp_knots.set_size(1, loop_ub);
    for (int i5{0}; i5 < loop_ub; i5++) {
        b_spline_sp_knots[i5] = (spline_sp_knots[(i1 + i5) + 1] >= u2);
    }
    coder::b_eml_find(b_spline_sp_knots, (int *)&kEndVec_data, kEndVec_size);
    // 'splineLength:25' kStart     = kStartVec( 1 );
    // 'splineLength:26' kEnd       = kEndVec( 1 );
    // 'splineLength:28' if( Knots( kStart ) < u1 )
    c_spline_sp_knots = spline_sp_knots[i1 + kStartVec_data];
    if (c_spline_sp_knots < u1) {
        __m128d r;
        __m128d r1;
        __m128d r2;
        __m128d r3;
        __m128d r4;
        double c_r1Dnorm;
        int d_loop_ub;
        // 'splineLength:29' LStart = splineLengthApprox_Interval( cfg, spline, Knots( kStart ), u1,
        // false );
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
        r = _mm_loadu_pd((const double *)&cfg_GaussLegendreX[0]);
        r1 = _mm_set1_pd(1.0);
        r2 = _mm_set1_pd(c_spline_sp_knots);
        r3 = _mm_set1_pd(u1);
        r4 = _mm_set1_pd(2.0);
        _mm_storeu_pd(&e_spline_sp_knots[0],
                      _mm_div_pd(_mm_add_pd(_mm_mul_pd(r2, _mm_sub_pd(r1, r)),
                                            _mm_mul_pd(r3, _mm_add_pd(r, r1))),
                                 r4));
        r = _mm_loadu_pd((const double *)&cfg_GaussLegendreX[2]);
        _mm_storeu_pd(&e_spline_sp_knots[2],
                      _mm_div_pd(_mm_add_pd(_mm_mul_pd(r2, _mm_sub_pd(r1, r)),
                                            _mm_mul_pd(r3, _mm_add_pd(r, r1))),
                                 r4));
        e_spline_sp_knots[4] = (c_spline_sp_knots * (1.0 - cfg_GaussLegendreX[4]) +
                                u1 * (cfg_GaussLegendreX[4] + 1.0)) /
                               2.0;
        EvalBSpline(spline_sp_Bl_handle, spline_sp_coeff, e_spline_sp_knots, a__1, r1D);
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
        r10.set_size(r1D.size(0), 5);
        d_loop_ub = r1D.size(0);
        for (int i9{0}; i9 < 5; i9++) {
            for (int i10{0}; i10 < d_loop_ub; i10++) {
                double varargin_1;
                varargin_1 = r1D[i10 + r1D.size(0) * i9];
                r10[i10 + r10.size(0) * i9] = std::pow(varargin_1, 2.0);
            }
        }
        coder::sum(r10, r1Dnorm);
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
        for (int k{0}; k < 5; k++) {
            double d;
            d = std::sqrt(r1Dnorm[k]);
            r1Dnorm[k] = d;
            c_r1Dnorm += d * cfg_GaussLegendreW[k];
        }
        LStart = c_r1Dnorm * (u1 - c_spline_sp_knots) / 2.0;
        //  Gauss Legendre integration
        // 'splineLengthApprox_Interval:38' L = L( 1 );
        //  to satisfy Matlab Coder
    } else {
        // 'splineLength:30' else
        // 'splineLength:31' LStart = 0;
        LStart = 0.0;
    }
    // 'splineLength:35' if( Knots( kEnd ) > u2 )
    d_spline_sp_knots = spline_sp_knots[i1 + kEndVec_data];
    if (d_spline_sp_knots > u2) {
        __m128d r5;
        __m128d r6;
        __m128d r7;
        __m128d r8;
        __m128d r9;
        double d_r1Dnorm;
        int e_loop_ub;
        // 'splineLength:36' LEnd = splineLengthApprox_Interval( cfg, spline, u2, Knots( kEnd ),
        // false );
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
        r5 = _mm_loadu_pd((const double *)&cfg_GaussLegendreX[0]);
        r6 = _mm_set1_pd(1.0);
        r7 = _mm_set1_pd(u2);
        r8 = _mm_set1_pd(d_spline_sp_knots);
        r9 = _mm_set1_pd(2.0);
        _mm_storeu_pd(&b_u2[0], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r7, _mm_sub_pd(r6, r5)),
                                                      _mm_mul_pd(r8, _mm_add_pd(r5, r6))),
                                           r9));
        r5 = _mm_loadu_pd((const double *)&cfg_GaussLegendreX[2]);
        _mm_storeu_pd(&b_u2[2], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r7, _mm_sub_pd(r6, r5)),
                                                      _mm_mul_pd(r8, _mm_add_pd(r5, r6))),
                                           r9));
        b_u2[4] = (u2 * (1.0 - cfg_GaussLegendreX[4]) +
                   d_spline_sp_knots * (cfg_GaussLegendreX[4] + 1.0)) /
                  2.0;
        EvalBSpline(spline_sp_Bl_handle, spline_sp_coeff, b_u2, a__1, r1D);
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
        r10.set_size(r1D.size(0), 5);
        e_loop_ub = r1D.size(0);
        for (int i11{0}; i11 < 5; i11++) {
            for (int i12{0}; i12 < e_loop_ub; i12++) {
                double b_varargin_1;
                b_varargin_1 = r1D[i12 + r1D.size(0) * i11];
                r10[i12 + r10.size(0) * i11] = std::pow(b_varargin_1, 2.0);
            }
        }
        coder::sum(r10, r1Dnorm);
        //  mysqrt : Custom implementation of the sqrt method.
        //
        //  Inputs :
        //    x : Value used for the computation
        //  Outputs :
        //    y : Resulting value
        //
        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
        for (int i14{0}; i14 < 5; i14++) {
            b_r1Dnorm[i14] = (r1Dnorm[i14] >= 0.0);
        }
        n_ocn_assert(b_r1Dnorm);
        // 'mysqrt:11' y = sqrt(x);
        // 'splineLengthApprox_Interval:37' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
        d_r1Dnorm = 0.0;
        for (int b_k{0}; b_k < 5; b_k++) {
            double d1;
            d1 = std::sqrt(r1Dnorm[b_k]);
            r1Dnorm[b_k] = d1;
            d_r1Dnorm += d1 * cfg_GaussLegendreW[b_k];
        }
        LEnd = d_r1Dnorm * (d_spline_sp_knots - u2) / 2.0;
        //  Gauss Legendre integration
        // 'splineLengthApprox_Interval:38' L = L( 1 );
        //  to satisfy Matlab Coder
    } else {
        // 'splineLength:37' else
        // 'splineLength:38' LEnd = 0;
        LEnd = 0.0;
    }
    // 'splineLength:41' L = sum( Lk( kStart : ( kEnd -1 ) ) ) - LStart - LEnd;
    if (kStartVec_data > static_cast<double>(kEndVec_data) - 1.0) {
        i6 = 0;
        i7 = 0;
    } else {
        i6 = kStartVec_data - 1;
        i7 = kEndVec_data - 1;
    }
    c_loop_ub = i7 - i6;
    b_spline_sp_Lk.set_size(1, c_loop_ub);
    for (int i8{0}; i8 < c_loop_ub; i8++) {
        b_spline_sp_Lk[i8] = spline_sp_Lk[i6 + i8];
    }
    return (coder::sum(b_spline_sp_Lk) - LStart) - LEnd;
}

} // namespace ocn

//
// File trailer for splineLength.cpp
//
// [EOF]
//
