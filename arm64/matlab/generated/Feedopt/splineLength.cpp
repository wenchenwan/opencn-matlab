
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
#include "opencn_matlab_data.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>

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
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> b_spline_sp_Lk;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1D;
    ::coder::array<bool, 2U> b_spline_sp_knots;
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
    // 'splineLength:9' ocn_assert( u2 > u1,          'u2 must be greater than u1', mfilename);
    // 'splineLength:10' ocn_assert( u1 >= Knots(1),   'u1 must be greater or equal than the first
    // spline knot', mfilename); 'splineLength:11' ocn_assert( u2 <= Knots(end), 'u2 must be smaller
    // or equal than the last spline knot', mfilename); 'splineLength:13' kStartVec  = find( Knots
    // <= u1, 1, "last" );
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
    // 'splineLength:14' kEndVec    = find( Knots >= u2, 1, "first" );
    b_spline_sp_knots.set_size(1, loop_ub);
    for (int i5{0}; i5 < loop_ub; i5++) {
        b_spline_sp_knots[i5] = (spline_sp_knots[(i1 + i5) + 1] >= u2);
    }
    coder::b_eml_find(b_spline_sp_knots, (int *)&kEndVec_data, kEndVec_size);
    // 'splineLength:15' kStart     = kStartVec( 1 );
    // 'splineLength:16' kEnd       = kEndVec( 1 );
    // 'splineLength:18' if( Knots( kStart ) < u1 )
    c_spline_sp_knots = spline_sp_knots[i1 + kStartVec_data];
    if (c_spline_sp_knots < u1) {
        double e_spline_sp_knots[5];
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
        for (int i8{0}; i8 < 5; i8++) {
            double d;
            d = cfg_GaussLegendreX[i8];
            e_spline_sp_knots[i8] = (c_spline_sp_knots * (1.0 - d) + u1 * (d + 1.0)) / 2.0;
        }
        EvalBSpline(spline_sp_Bl_handle, spline_sp_coeff, e_spline_sp_knots, a__1, r1D);
        // 'splineLengthApprox_Interval:21' r1Dnorm     = MyNorm( r1D );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        r.set_size(r1D.size(0), 5);
        d_loop_ub = r1D.size(0);
        for (int i11{0}; i11 < 5; i11++) {
            for (int i12{0}; i12 < d_loop_ub; i12++) {
                double varargin_1;
                varargin_1 = r1D[i12 + r1D.size(0) * i11];
                r[i12 + r.size(0) * i11] = std::pow(varargin_1, 2.0);
            }
        }
        coder::sum(r, r1Dnorm);
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'splineLengthApprox_Interval:22' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
        b_r1Dnorm = 0.0;
        for (int k{0}; k < 5; k++) {
            double d2;
            d2 = std::sqrt(r1Dnorm[k]);
            r1Dnorm[k] = d2;
            b_r1Dnorm += d2 * cfg_GaussLegendreW[k];
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
        double b_u2[5];
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
        for (int i10{0}; i10 < 5; i10++) {
            double d1;
            d1 = cfg_GaussLegendreX[i10];
            b_u2[i10] = (u2 * (1.0 - d1) + d_spline_sp_knots * (d1 + 1.0)) / 2.0;
        }
        EvalBSpline(spline_sp_Bl_handle, spline_sp_coeff, b_u2, a__1, r1D);
        // 'splineLengthApprox_Interval:21' r1Dnorm     = MyNorm( r1D );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        r.set_size(r1D.size(0), 5);
        e_loop_ub = r1D.size(0);
        for (int i13{0}; i13 < 5; i13++) {
            for (int i14{0}; i14 < e_loop_ub; i14++) {
                double b_varargin_1;
                b_varargin_1 = r1D[i14 + r1D.size(0) * i13];
                r[i14 + r.size(0) * i13] = std::pow(b_varargin_1, 2.0);
            }
        }
        coder::sum(r, r1Dnorm);
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'splineLengthApprox_Interval:22' L           = r1Dnorm * GL_W * ( u1 - u0 ) / 2;
        c_r1Dnorm = 0.0;
        for (int b_k{0}; b_k < 5; b_k++) {
            double d3;
            d3 = std::sqrt(r1Dnorm[b_k]);
            r1Dnorm[b_k] = d3;
            c_r1Dnorm += d3 * cfg_GaussLegendreW[b_k];
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
        i6 = 0;
        i7 = 0;
    } else {
        i6 = kStartVec_data - 1;
        i7 = kEndVec_data - 1;
    }
    c_loop_ub = i7 - i6;
    b_spline_sp_Lk.set_size(1, c_loop_ub);
    for (int i9{0}; i9 < c_loop_ub; i9++) {
        b_spline_sp_Lk[i9] = spline_sp_Lk[i6 + i9];
    }
    return (coder::sum(b_spline_sp_Lk) - LStart) - LEnd;
}

} // namespace ocn

//
// File trailer for splineLength.cpp
//
// [EOF]
//
