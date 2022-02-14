//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthFindU_down.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "SplineLengthFindU_down.h"
#include "EvalBSplineNoCtx.h"
#include "SplineLengthApprox_Interval1.h"
#include "c_assert.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_types1.h"
#include "sinspace_types11.h"
#include "sinspace_types2.h"
#include "sinspace_types3.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// computes approximately the value of curve parameter u such that the arc
//  length starting from u1 equals L.
//  This function takes usage of the precalculated arc lengths between knots.
//  The last integration interval is approximated by the trapezoidal rule.
//  u1 must satisfy 0 < u1 < 1.
//  In the normal case, u must satisfy 0 < u < u1. If L is too large, u is set to -1
//
// Arguments    : const queue_coder *ctx_q_splines
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                int Curv_sp_index
//                double L
//                double u1
// Return Type  : double
//
namespace ocn {
double SplineLengthFindU_down(const queue_coder *ctx_q_splines,
                              const double ctx_cfg_GaussLegendreX[5],
                              const double ctx_cfg_GaussLegendreW[5], int Curv_sp_index, double L,
                              double u1)
{
    CurvStruct expl_temp;
    double a__1[3];
    double r1D[3];
    double Lcum;
    double u;
    int i;
    int i1;
    int k;
    //
    //  get the sp structure
    ctx_q_splines->get(Curv_sp_index, &expl_temp);
    if (4 > expl_temp.sp.knots.size(1) - 3) {
        i = 0;
        i1 = -1;
    } else {
        i = 3;
        i1 = expl_temp.sp.knots.size(1) - 4;
    }
    //  eliminate multiplicities at the end points
    //
    c_c_assert(u1 >= expl_temp.sp.knots[i]);
    f_c_assert(u1 <= expl_temp.sp.knots[i1]);
    //
    //
    for (k = i1 - i; u1 < expl_temp.sp.knots[i + k]; k--) {
    }
    //
    Lcum =
        SplineLengthApprox_Interval1(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                                     Curv_sp_index, expl_temp.sp.knots[i + k], u1);
    //  length to next break point
    //
    int exitg1;
    do {
        exitg1 = 0;
        if (Lcum < L) {
            if (k < 1) {
                u = -1.0;
                exitg1 = 1;
            } else {
                Lcum += expl_temp.sp.Lk[k - 1];
                //  sum up precalculated length between knots
                k--;
            }
        } else {
            double Lremain;
            double uk;
            double uk_old;
            int u1_tmp;
            //  undo last increment
            Lcum -= expl_temp.sp.Lk[k];
            Lremain = L - Lcum;
            //
            u1_tmp = i + k;
            u1 = expl_temp.sp.knots[u1_tmp + 1];
            uk = 0.5 * (expl_temp.sp.knots[u1_tmp] + expl_temp.sp.knots[u1_tmp + 1]);
            //  initial guess for Newton Raphson iteration
            //  tolerance for Newton Raphson
            uk_old = 2.0;
            //  dummy value to ensure that while loop enters
            while (std::abs(uk - uk_old) > 1.0E-6) {
                double fk;
                //  Iterate until new value of uk is close to old value
                fk = SplineLengthApprox_Interval1(ctx_q_splines, ctx_cfg_GaussLegendreX,
                                                  ctx_cfg_GaussLegendreW, Curv_sp_index, uk, u1) -
                     Lremain;
                //  evaluation of function which should become zero
                EvalBSplineNoCtx(expl_temp.sp.CoeffX, expl_temp.sp.CoeffY, expl_temp.sp.CoeffZ,
                                 expl_temp.sp.Bl.handle, uk, a__1, r1D);
                sqrt_calls++;
                //  evaluation of the derivative of the function which should become zero
                //
                uk_old = uk;
                uk -= fk / -std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) +
                                      std::pow(r1D[2], 2.0));
                //  Newton Raphson update
                if (uk > u1) {
                    uk = u1;
                    //  make sure not to run away
                }
            }
            //
            u = uk;
            exitg1 = 1;
        }
    } while (exitg1 == 0);
    return u;
}

} // namespace ocn

//
// File trailer for SplineLengthFindU_down.cpp
//
// [EOF]
//
