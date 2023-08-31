//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: splineLength.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 31-Aug-2023 09:10:03
//

// Include Files
#include "splineLength.h"
#include "EvalBSpline.h"
#include "find.h"
#include "opencn_matlab_data.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function [ L ] = splineLength( cfg, spline, u1, u2 )
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
    static const char d_message[54]{
        'u', '1', ' ', 'm', 'u', 's', 't', ' ', 'b', 'e', ' ', 'g', 'r', 'e', 'a', 't', 'e', 'r',
        ' ', 'o', 'r', ' ', 'e', 'q', 'u', 'a', 'l', ' ', 't', 'h', 'a', 'n', ' ', 't', 'h', 'e',
        ' ', 'f', 'i', 'r', 's', 't', ' ', 's', 'p', 'l', 'i', 'n', 'e', ' ', 'k', 'n', 'o', 't'};
    static const char f_message[53]{
        'u', '2', ' ', 'm', 'u', 's', 't', ' ', 'b', 'e', ' ', 's', 'm', 'a', 'l', 'l', 'e', 'r',
        ' ', 'o', 'r', ' ', 'e', 'q', 'u', 'a', 'l', ' ', 't', 'h', 'a', 'n', ' ', 't', 'h', 'e',
        ' ', 'l', 'a', 's', 't', ' ', 's', 'p', 'l', 'i', 'n', 'e', ' ', 'k', 'n', 'o', 't'};
    static const char b_message[26]{'u', '2', ' ', 'm', 'u', 's', 't', ' ', 'b',
                                    'e', ' ', 'g', 'r', 'e', 'a', 't', 'e', 'r',
                                    ' ', 't', 'h', 'a', 'n', ' ', 'u', '1'};
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
    int i10;
    int i2;
    int i9;
    int kEndVec_data;
    int kStartVec_data;
    int loop_ub;
    // 'splineLength:3' sp = spline.sp;
    // 'splineLength:4' IND_KNOTS_MULT  = sp.Bl.order;
    //  Index used to remove multiple knots
    //  Eliminate multiplicities at the end points
    // 'splineLength:6' Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
    i = spline_sp_knots.size(1) - spline_sp_Bl_order;
    if (spline_sp_Bl_order > i + 1) {
        i1 = -1;
        i2 = -1;
    } else {
        i1 = spline_sp_Bl_order - 2;
        i2 = i;
    }
    // 'splineLength:7' Lk     = sp.Lk;
    // 'splineLength:9' c_assert(u2 > u1,          'u2 must be greater than u1');
    // 'c_assert:2' if coder.target('rtw')
    // 'c_assert:3' if ~condition
    if (u2 <= u1) {
        char message[26];
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i3{0}; i3 < 26; i3++) {
            message[i3] = b_message[i3];
        }
        c_assert_(&message[0]);
    }
    // 'c_assert:6' value = condition;
    // 'splineLength:10' c_assert(u1 >= Knots(1),   'u1 must be greater or equal than the first
    // spline knot'); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
    if (u1 < spline_sp_knots[i1 + 1]) {
        char c_message[54];
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i4{0}; i4 < 54; i4++) {
            c_message[i4] = d_message[i4];
        }
        c_assert_(&c_message[0]);
    }
    // 'c_assert:6' value = condition;
    // 'splineLength:11' c_assert(u2 <= Knots(end), 'u2 must be smaller or equal than the last
    // spline knot'); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
    if (u2 > spline_sp_knots[i2]) {
        char e_message[53];
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i5{0}; i5 < 53; i5++) {
            e_message[i5] = f_message[i5];
        }
        c_assert_(&e_message[0]);
    }
    // 'c_assert:6' value = condition;
    // 'splineLength:13' kStartVec  = find( Knots <= u1, 1, "last" );
    loop_ub = i2 - i1;
    b_spline_sp_knots.set_size(1, loop_ub);
    for (int i6{0}; i6 < loop_ub; i6++) {
        b_spline_sp_knots[i6] = (spline_sp_knots[(i1 + i6) + 1] <= u1);
    }
    coder::eml_find(b_spline_sp_knots, (int *)&kEndVec_data, kEndVec_size);
    b_loop_ub = kEndVec_size[1];
    for (int i7{0}; i7 < b_loop_ub; i7++) {
        kStartVec_data = kEndVec_data;
    }
    // 'splineLength:14' kEndVec    = find( Knots >= u2, 1, "first" );
    b_spline_sp_knots.set_size(1, loop_ub);
    for (int i8{0}; i8 < loop_ub; i8++) {
        b_spline_sp_knots[i8] = (spline_sp_knots[(i1 + i8) + 1] >= u2);
    }
    coder::b_eml_find(b_spline_sp_knots, (int *)&kEndVec_data, kEndVec_size);
    // 'splineLength:15' kStart     = kStartVec( 1 );
    // 'splineLength:16' kEnd       = kEndVec( 1 );
    // 'splineLength:18' if( Knots( kStart ) < u1 )
    c_spline_sp_knots = spline_sp_knots[i1 + kStartVec_data];
    if (c_spline_sp_knots < u1) {
        __m128d r;
        __m128d r1;
        __m128d r2;
        __m128d r3;
        __m128d r4;
        double b_r1Dnorm;
        int d_loop_ub;
        // 'splineLength:19' LStart = splineLengthApprox_Interval( cfg, spline, Knots( kStart ), u1,
        // false );
        //  computes approximately the arc length L with integration bounds u1 and u2.
        //  IMPORTANT : u0 and u1 should lie in the same knot interval.
        //  The computation is based on numerical Gauss Legendre integration
        //
        //  get Gauss-Legendre knots and weights
        // 'splineLengthApprox_Interval:7' GL_X   = cfg.GaussLegendreX;
        // 'splineLengthApprox_Interval:8' GL_W   = cfg.GaussLegendreW;
        // 'splineLengthApprox_Interval:10' if( isEnd )
        //  apply linear map from[-1, 1] to [u0, u1]
        // 'splineLengthApprox_Interval:17' uvec   = ( ( u0 * ( 1 - GL_X ) + u1 * ( 1 + GL_X ) ) / 2
        // ).';
        //
        // 'splineLengthApprox_Interval:20' [ ~, r1D ]  = EvalBSpline( spline, uvec );
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
        // 'splineLengthApprox_Interval:21' r1Dnorm     = MyNorm( r1D );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        r10.set_size(r1D.size(0), 5);
        d_loop_ub = r1D.size(0);
        for (int i12{0}; i12 < 5; i12++) {
            for (int i13{0}; i13 < d_loop_ub; i13++) {
                double varargin_1;
                varargin_1 = r1D[i13 + r1D.size(0) * i12];
                r10[i13 + r10.size(0) * i12] = std::pow(varargin_1, 2.0);
            }
        }
        coder::sum(r10, r1Dnorm);
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'splineLengthApprox_Interval:22' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
        b_r1Dnorm = 0.0;
        for (int k{0}; k < 5; k++) {
            double d;
            d = std::sqrt(r1Dnorm[k]);
            r1Dnorm[k] = d;
            b_r1Dnorm += d * cfg_GaussLegendreW[k];
        }
        LStart = b_r1Dnorm * (u1 - c_spline_sp_knots) / 2.0;
        //  Gauss Legendre integration
        // 'splineLengthApprox_Interval:23' L = L( 1 );
        //  to satisfy Matlab Coder
    } else {
        // 'splineLength:20' else
        // 'splineLength:21' LStart = 0;
        LStart = 0.0;
    }
    // 'splineLength:25' if( Knots( kEnd ) > u2 )
    d_spline_sp_knots = spline_sp_knots[i1 + kEndVec_data];
    if (d_spline_sp_knots > u2) {
        __m128d r5;
        __m128d r6;
        __m128d r7;
        __m128d r8;
        __m128d r9;
        double c_r1Dnorm;
        int e_loop_ub;
        // 'splineLength:26' LEnd = splineLengthApprox_Interval( cfg, spline, u2, Knots( kEnd ),
        // false );
        //  computes approximately the arc length L with integration bounds u1 and u2.
        //  IMPORTANT : u0 and u1 should lie in the same knot interval.
        //  The computation is based on numerical Gauss Legendre integration
        //
        //  get Gauss-Legendre knots and weights
        // 'splineLengthApprox_Interval:7' GL_X   = cfg.GaussLegendreX;
        // 'splineLengthApprox_Interval:8' GL_W   = cfg.GaussLegendreW;
        // 'splineLengthApprox_Interval:10' if( isEnd )
        //  apply linear map from[-1, 1] to [u0, u1]
        // 'splineLengthApprox_Interval:17' uvec   = ( ( u0 * ( 1 - GL_X ) + u1 * ( 1 + GL_X ) ) / 2
        // ).';
        //
        // 'splineLengthApprox_Interval:20' [ ~, r1D ]  = EvalBSpline( spline, uvec );
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
        // 'splineLengthApprox_Interval:21' r1Dnorm     = MyNorm( r1D );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        r10.set_size(r1D.size(0), 5);
        e_loop_ub = r1D.size(0);
        for (int i14{0}; i14 < 5; i14++) {
            for (int i15{0}; i15 < e_loop_ub; i15++) {
                double b_varargin_1;
                b_varargin_1 = r1D[i15 + r1D.size(0) * i14];
                r10[i15 + r10.size(0) * i14] = std::pow(b_varargin_1, 2.0);
            }
        }
        coder::sum(r10, r1Dnorm);
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'splineLengthApprox_Interval:22' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
        c_r1Dnorm = 0.0;
        for (int b_k{0}; b_k < 5; b_k++) {
            double d1;
            d1 = std::sqrt(r1Dnorm[b_k]);
            r1Dnorm[b_k] = d1;
            c_r1Dnorm += d1 * cfg_GaussLegendreW[b_k];
        }
        LEnd = c_r1Dnorm * (d_spline_sp_knots - u2) / 2.0;
        //  Gauss Legendre integration
        // 'splineLengthApprox_Interval:23' L = L( 1 );
        //  to satisfy Matlab Coder
    } else {
        // 'splineLength:27' else
        // 'splineLength:28' LEnd = 0;
        LEnd = 0.0;
    }
    // 'splineLength:31' L = sum( Lk( kStart : ( kEnd -1 ) ) ) - LStart - LEnd;
    if (kStartVec_data > static_cast<double>(kEndVec_data) - 1.0) {
        i9 = 0;
        i10 = 0;
    } else {
        i9 = kStartVec_data - 1;
        i10 = kEndVec_data - 1;
    }
    c_loop_ub = i10 - i9;
    b_spline_sp_Lk.set_size(1, c_loop_ub);
    for (int i11{0}; i11 < c_loop_ub; i11++) {
        b_spline_sp_Lk[i11] = spline_sp_Lk[i9 + i11];
    }
    return (coder::sum(b_spline_sp_Lk) - LStart) - LEnd;
}

} // namespace ocn

//
// File trailer for splineLength.cpp
//
// [EOF]
//
