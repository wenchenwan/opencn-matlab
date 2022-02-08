//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplitCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "SplitCurvStruct.h"
#include "SplitLineHelix.h"
#include "SplitSpline.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_types.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"

// Function Definitions
//
// coder.varsize('CrvStructs', [1, 100], [0, 1]);
//
//
// Arguments    : const FeedoptContext *ctx
//                const CurvStruct *CurvStrct
// Return Type  : void
//
namespace ocn {
void SplitCurvStruct(const FeedoptContext *ctx, const CurvStruct *CurvStrct)
{
    CurvStruct b_CurvStrct;
    CurvStruct c_CurvStrct;
    if ((CurvStrct->Type != CurveType_TransP5) && (!CurvStrct->UseConstJerk)) {
        if ((CurvStrct->Type == CurveType_Line) || (CurvStrct->Type == CurveType_Helix)) {
            c_CurvStrct = *CurvStrct;
            SplitLineHelix(ctx, &c_CurvStrct);
        } else {
            b_CurvStrct = *CurvStrct;
            SplitSpline(ctx, &b_CurvStrct);
        }
    } else {
        ctx->q_split.push(CurvStrct);
    }
}

} // namespace ocn

//
// File trailer for SplitCurvStruct.cpp
//
// [EOF]
//
