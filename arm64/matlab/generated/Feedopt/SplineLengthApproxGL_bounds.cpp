//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApproxGL_bounds.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

// Include Files
#include "SplineLengthApproxGL_bounds.h"
#include "SplineLengthApprox_Interval1.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "coder_array.h"

// Function Definitions
//
// function L  = SplineLengthApproxGL_bounds(ctx, Curv, u1, u2)
//
// computes approximately the arc length L with arbitrary integration bounds u1 and u2.
//  The computation is based on numerical Gauss Legendre integration.
//  This function takes usage of the precalculated arc lengths between knots.
//
//  get the sp structure
//
// Arguments    : const queue_coder *ctx_q_spline
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                unsigned int Curv_sp_index
//                double u1
//                double u2
// Return Type  : double
//
namespace ocn {
double SplineLengthApproxGL_bounds(const queue_coder *ctx_q_spline,
                                   const double ctx_cfg_GaussLegendreX[5],
                                   const double ctx_cfg_GaussLegendreW[5],
                                   unsigned int Curv_sp_index, double u1, double u2)
{
    static const char e_message[53]{
        'u', '2', ' ', 'm', 'u', 's', 't', ' ', 'b', 'e', ' ', 's', 'm', 'a', 'l', 'l', 'e', 'r',
        ' ', 'o', 'r', ' ', 'e', 'q', 'u', 'a', 'l', ' ', 't', 'h', 'a', 'n', ' ', 't', 'h', 'e',
        ' ', 'l', 'a', 's', 't', ' ', 's', 'p', 'l', 'i', 'n', 'e', ' ', 'k', 'n', 'o', 't'};
    static const char b_message[26]{'u', '2', ' ', 'm', 'u', 's', 't', ' ', 'b',
                                    'e', ' ', 'g', 'r', 'e', 'a', 't', 'e', 'r',
                                    ' ', 't', 'h', 'a', 'n', ' ', 'u', '1'};
    CurvStruct expl_temp;
    double L;
    int i;
    int i1;
    int i5;
    int k;
    char c_message[54];
    char d_message[53];
    char message[26];
    // 'SplineLengthApproxGL_bounds:7' Spline = ctx.q_spline.get( Curv.sp_index );
    ctx_q_spline->get(Curv_sp_index, &expl_temp);
    // 'SplineLengthApproxGL_bounds:8' sp     = Spline.sp;
    // 'SplineLengthApproxGL_bounds:9' Knots  = sp.knots( 4 : end-3 );
    if (4 > expl_temp.sp.knots.size(1) - 3) {
        i = -1;
        i1 = 3;
    } else {
        i = 2;
        i1 = expl_temp.sp.knots.size(1);
    }
    //  eliminate multiplicities at the end points
    // 'SplineLengthApproxGL_bounds:10' Lk     = sp.Lk;
    //
    // 'SplineLengthApproxGL_bounds:12' c_assert(u2 > u1,          'u2 must be greater than u1');
    // 'c_assert:2' if coder.target('rtw')
    // 'c_assert:3' if ~condition
    if (u2 <= u1) {
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i2{0}; i2 < 26; i2++) {
            message[i2] = b_message[i2];
        }
        c_assert_(&message[0]);
    }
    // 'c_assert:6' value = condition;
    // 'SplineLengthApproxGL_bounds:13' c_assert(u1 >= Knots(1),   'u1 must be greater or equal than
    // the first spline knot'); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
    if (u1 < expl_temp.sp.knots[i + 1]) {
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i3{0}; i3 < 54; i3++) {
            c_message[i3] = cv1[i3];
        }
        c_assert_(&c_message[0]);
    }
    // 'c_assert:6' value = condition;
    // 'SplineLengthApproxGL_bounds:14' c_assert(u2 <= Knots(end), 'u2 must be smaller or equal than
    // the last spline knot'); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
    if (u2 > expl_temp.sp.knots[i1 - 4]) {
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i4{0}; i4 < 53; i4++) {
            d_message[i4] = e_message[i4];
        }
        c_assert_(&d_message[0]);
    }
    // 'c_assert:6' value = condition;
    //
    // 'SplineLengthApproxGL_bounds:16' k = 1;
    k = 1;
    //
    // 'SplineLengthApproxGL_bounds:18' while u1 > Knots(k)
    int exitg1;
    do {
        exitg1 = 0;
        i5 = i + k;
        if (u1 > expl_temp.sp.knots[i5]) {
            // 'SplineLengthApproxGL_bounds:19' k = k + 1;
            k++;
        } else {
            exitg1 = 1;
        }
    } while (exitg1 == 0);
    //
    // 'SplineLengthApproxGL_bounds:22' if u2 < Knots(k)
    if (u2 < expl_temp.sp.knots[i5]) {
        // 'SplineLengthApproxGL_bounds:23' L = SplineLengthApprox_Interval1(ctx, Curv, u1, u2);
        L = SplineLengthApprox_Interval1(ctx_q_spline, ctx_cfg_GaussLegendreX,
                                         ctx_cfg_GaussLegendreW, Curv_sp_index, u1, u2);
        //  u1 and u2 in the same break interval
    } else {
        // 'SplineLengthApproxGL_bounds:24' else
        // 'SplineLengthApproxGL_bounds:25' L = SplineLengthApprox_Interval1(ctx, Curv, u1,
        // Knots(k));
        L = SplineLengthApprox_Interval1(ctx_q_spline, ctx_cfg_GaussLegendreX,
                                         ctx_cfg_GaussLegendreW, Curv_sp_index, u1,
                                         expl_temp.sp.knots[i + k]);
        //  remaining length to next break point
        // 'SplineLengthApproxGL_bounds:26' while u2 > Knots(k)
        while (u2 > expl_temp.sp.knots[i + k]) {
            // 'SplineLengthApproxGL_bounds:27' L = L + Lk(k);
            L += expl_temp.sp.Lk[k - 1];
            //  sum up precalculated length between knots
            // 'SplineLengthApproxGL_bounds:28' k = k + 1;
            k++;
        }
        // 'SplineLengthApproxGL_bounds:30' L = L + SplineLengthApprox_Interval1(ctx, Curv,
        // Knots(k), u2);
        L += SplineLengthApprox_Interval1(ctx_q_spline, ctx_cfg_GaussLegendreX,
                                          ctx_cfg_GaussLegendreW, Curv_sp_index,
                                          expl_temp.sp.knots[i + k], u2);
        //  remaining length to u2
    }
    return L;
}

} // namespace ocn

//
// File trailer for SplineLengthApproxGL_bounds.cpp
//
// [EOF]
//
