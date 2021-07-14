//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplitCurvStructs.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "SplitCurvStructs.h"
#include "DebugLog.h"
#include "SplitCurvStruct.h"
#include "queue_coder.h"
#include "sinspace_types.h"

// Function Definitions
//
// Arguments    : const FeedoptContext *ctx
// Return Type  : void
//
namespace ocn {
void SplitCurvStructs(const FeedoptContext *ctx)
{
    CurvStruct r;
    if (!ctx->q_smooth.isempty()) {
        unsigned int N;
        int i;
        N = ctx->q_smooth.size();
        l_DebugLog();
        i = static_cast<int>(N);
        for (int k{0}; k < i; k++) {
            ctx->q_smooth.get(k + 1U, &r);
            SplitCurvStruct(ctx, &r);
        }
    }
}

} // namespace ocn

//
// File trailer for SplitCurvStructs.cpp
//
// [EOF]
//
