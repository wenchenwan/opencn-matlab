//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApproxGL_bounds.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "SplineLengthApproxGL_bounds.h"
#include "SplineLengthApprox_Interval1.h"
#include "c_assert.h"
#include "queue_coder.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "coder_array.h"

// Function Definitions
//
// computes approximately the arc length L with arbitrary integration bounds u1 and u2.
//  The computation is based on numerical Gauss Legendre integration.
//  This function takes usage of the precalculated arc lengths between knots.
//
//  get the sp structure
//
// Arguments    : const queue_coder *ctx_q_splines
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                int Curv_sp_index
//                double u1
//                double u2
// Return Type  : double
//
namespace ocn {
double SplineLengthApproxGL_bounds(const queue_coder *ctx_q_splines,
                                   const double ctx_cfg_GaussLegendreX[5],
                                   const double ctx_cfg_GaussLegendreW[5], int Curv_sp_index,
                                   double u1, double u2)
{
    CurvStruct expl_temp;
    double L;
    int i;
    int i1;
    int i2;
    int k;
    ctx_q_splines->get(Curv_sp_index, &expl_temp);
    if (4 > expl_temp.sp.knots.size(1) - 3) {
        i = -1;
        i1 = 3;
    } else {
        i = 2;
        i1 = expl_temp.sp.knots.size(1);
    }
    //  eliminate multiplicities at the end points
    //
    b_c_assert(u2 > u1);
    c_c_assert(u1 >= expl_temp.sp.knots[i + 1]);
    d_c_assert(u2 <= expl_temp.sp.knots[i1 - 4]);
    //
    k = 1;
    //
    int exitg1;
    do {
        exitg1 = 0;
        i2 = i + k;
        if (u1 > expl_temp.sp.knots[i2]) {
            k++;
        } else {
            exitg1 = 1;
        }
    } while (exitg1 == 0);
    //
    if (u2 < expl_temp.sp.knots[i2]) {
        L = SplineLengthApprox_Interval1(ctx_q_splines, ctx_cfg_GaussLegendreX,
                                         ctx_cfg_GaussLegendreW, Curv_sp_index, u1, u2);
        //  u1 and u2 in the same break interval
    } else {
        L = SplineLengthApprox_Interval1(ctx_q_splines, ctx_cfg_GaussLegendreX,
                                         ctx_cfg_GaussLegendreW, Curv_sp_index, u1,
                                         expl_temp.sp.knots[i + k]);
        //  remaining length to next break point
        while (u2 > expl_temp.sp.knots[i + k]) {
            L += expl_temp.sp.Lk[k - 1];
            //  sum up precalculated length between knots
            k++;
        }
        L += SplineLengthApprox_Interval1(ctx_q_splines, ctx_cfg_GaussLegendreX,
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
