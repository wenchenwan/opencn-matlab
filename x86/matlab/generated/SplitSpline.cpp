//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplitSpline.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

// Include Files
#include "SplitSpline.h"
#include "SplineLengthApprox.h"
#include "find.h"
#include "queue_coder.h"
#include "sinspace_types.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const FeedoptContext *ctx
//                CurvStruct *Curv
// Return Type  : void
//
namespace ocn {
void SplitSpline(const FeedoptContext *ctx, CurvStruct *Curv)
{
    ::coder::array<double, 2U> knots;
    ::coder::array<bool, 2U> b_expl_temp;
    CurvStruct expl_temp;
    double L;
    double u1_tilda;
    int Idx2_size[2];
    int Idx1_data;
    int Idx2_data;
    int b_loop_ub;
    int c_loop_ub;
    int i;
    int i1;
    int i5;
    int i6;
    int k;
    int loop_ub;
    ctx->q_splines.get(Curv->sp_index, &expl_temp);
    u1_tilda = Curv->a_param + Curv->b_param;
    if (4 > expl_temp.sp.knots.size(1) - 3) {
        i = 0;
        i1 = -1;
    } else {
        i = 3;
        i1 = expl_temp.sp.knots.size(1) - 4;
    }
    loop_ub = i1 - i;
    b_expl_temp.set_size(1, loop_ub + 1);
    for (int i2{0}; i2 <= loop_ub; i2++) {
        b_expl_temp[i2] = (expl_temp.sp.knots[i + i2] > Curv->b_param);
    }
    coder::eml_find(b_expl_temp, (int *)&Idx2_data, Idx2_size);
    b_loop_ub = Idx2_size[1];
    for (int i3{0}; i3 < b_loop_ub; i3++) {
        Idx1_data = Idx2_data;
    }
    b_expl_temp.set_size(1, loop_ub + 1);
    for (int i4{0}; i4 <= loop_ub; i4++) {
        b_expl_temp[i4] = (expl_temp.sp.knots[i + i4] < u1_tilda);
    }
    coder::b_eml_find(b_expl_temp, (int *)&Idx2_data, Idx2_size);
    if (Idx1_data > Idx2_data) {
        i5 = 0;
        i6 = 0;
    } else {
        i5 = Idx1_data - 1;
        i6 = Idx2_data;
    }
    c_loop_ub = i6 - i5;
    knots.set_size(1, c_loop_ub + 2);
    knots[0] = Curv->b_param;
    for (int i7{0}; i7 < c_loop_ub; i7++) {
        knots[i7 + 1] = expl_temp.sp.knots[(i + i5) + i7];
    }
    knots[c_loop_ub + 1] = u1_tilda;
    L = 0.0;
    k = 0;
    while (k + 1 < knots.size(1)) {
        int b_i;
        b_i = k;
        while ((L < ctx->cfg.LSplit) && (k + 1 < knots.size(1))) {
            double delta_L;
            delta_L = SplineLengthApprox(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                                         Curv->sp_index, knots[k], knots[k + 1]);
            L += delta_L;
            k++;
        }
        Curv->a_param = knots[k] - knots[b_i];
        Curv->b_param = knots[b_i];
        ctx->q_split.push(Curv);
        L = 0.0;
    }
}

} // namespace ocn

//
// File trailer for SplitSpline.cpp
//
// [EOF]
//
