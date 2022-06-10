//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: evalPositionFromU.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
//

// Include Files
#include "evalPositionFromU.h"
#include "EvalCurvStructNoCtx.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types31.h"
#include "coder_array.h"

// Function Definitions
//
// function  [ r0D ] = evalPositionFromU( cfg, curv, spline, u )
//
// Arguments    : const FeedoptConfig cfg
//                const CurvStruct *curv
//                const CurvStruct *spline
//                double u
//                ::coder::array<double, 1U> &r0D
// Return Type  : void
//
namespace ocn {
void evalPositionFromU(const FeedoptConfig cfg, const CurvStruct *curv, const CurvStruct *spline,
                       double u, ::coder::array<double, 1U> &r0D)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'evalPositionFromU:3' coder.inline( "never" );
    // 'evalPositionFromU:4' r0D = EvalCurvStructNoCtx( cfg, curv, spline, u );
    EvalCurvStructNoCtx(cfg.NumberAxis, cfg.NCart, cfg.NRot, cfg.indCart.data, cfg.indCart.size[0],
                        cfg.indRot.data, cfg.indRot.size[0], cfg.indTot.data, cfg.indTot.size[0],
                        curv->Info.Type, curv->R0, curv->R1, curv->CorrectedHelixCenter, curv->evec,
                        curv->theta, curv->pitch, curv->CoeffP5, curv->a_param, curv->b_param,
                        spline, u, r0D);
}

} // namespace ocn

//
// File trailer for evalPositionFromU.cpp
//
// [EOF]
//
