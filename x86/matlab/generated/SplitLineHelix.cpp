//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplitLineHelix.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "SplitLineHelix.h"
#include "LengthCurv.h"
#include "queue_coder.h"
#include "sinspace_types.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const FeedoptContext *ctx
//                CurvStruct *Curv
// Return Type  : void
//
namespace ocn {
void SplitLineHelix(const FeedoptContext *ctx, CurvStruct *Curv)
{
    double L;
    double a;
    double b;
    a = Curv->a_param;
    b = Curv->b_param;
    L = LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, Curv->Type, Curv->P0, Curv->P1,
                   Curv->CorrectedHelixCenter, Curv->evec, Curv->theta, Curv->pitch, Curv->CoeffP5,
                   Curv->sp_index, Curv->a_param, Curv->b_param);
    if (L < 2.0 * ctx->cfg.LSplit) {
        ctx->q_split.push(Curv);
    } else {
        double L_split;
        double N;
        int i;
        N = std::ceil(L / ctx->cfg.LSplit);
        L_split = L / N;
        i = static_cast<int>(N);
        for (int k{0}; k < i; k++) {
            double u_tilda_0;
            u_tilda_0 = a * (((static_cast<double>(k) + 1.0) - 1.0) * (L_split / L)) + b;
            Curv->a_param = (a * ((static_cast<double>(k) + 1.0) * (L_split / L)) + b) - u_tilda_0;
            Curv->b_param = u_tilda_0;
            ctx->q_split.push(Curv);
        }
    }
}

} // namespace ocn

//
// File trailer for SplitLineHelix.cpp
//
// [EOF]
//
