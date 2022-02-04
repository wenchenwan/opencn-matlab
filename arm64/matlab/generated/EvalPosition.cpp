//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalPosition.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

// Include Files
#include "EvalPosition.h"
#include "EvalCurvStructNoCtx.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "sinspace_types3.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const CurvStruct *Curv
//                const CurvStruct *Spline
//                double u
//                double r0D[3]
// Return Type  : void
//
namespace ocn {
void EvalPosition(const CurvStruct *Curv, const CurvStruct *Spline, double u, double r0D[3])
{
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    EvalCurvStructNoCtx(Curv->Type, Curv->P0, Curv->P1, Curv->CorrectedHelixCenter, Curv->evec,
                        Curv->theta, Curv->pitch, Curv->CoeffP5, Curv->a_param, Curv->b_param,
                        Spline->sp.CoeffX, Spline->sp.CoeffY, Spline->sp.CoeffZ,
                        Spline->sp.Bl.handle, u, r0D);
}

} // namespace ocn

//
// File trailer for EvalPosition.cpp
//
// [EOF]
//
