//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: evalPositionFromU.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:07:13
//

// Include Files
#include "evalPositionFromU.h"
#include "EvalCurvStructNoCtx.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "coder_array.h"
#include "coder_bounded_array.h"

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
    ::coder::array<int, 1U> t8_indCart;
    ::coder::array<int, 1U> t8_indRot;
    int b_loop_ub;
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'evalPositionFromU:3' coder.inline( "never" );
    // 'evalPositionFromU:4' r0D = EvalCurvStructNoCtx( cfg, curv, spline, u );
    t8_indCart.set_size(cfg.indCart.size[0]);
    loop_ub = cfg.indCart.size[0];
    for (int i{0}; i < loop_ub; i++) {
        t8_indCart[i] = cfg.indCart.data[i];
    }
    t8_indRot.set_size(cfg.indRot.size[0]);
    b_loop_ub = cfg.indRot.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        t8_indRot[i1] = cfg.indRot.data[i1];
    }
    b_EvalCurvStructNoCtx(cfg.maskTot.data, cfg.maskTot.size, cfg.maskCart.data, cfg.maskCart.size,
                          cfg.maskRot.data, cfg.maskRot.size, t8_indCart, t8_indRot, cfg.NumberAxis,
                          cfg.NCart, cfg.NRot, curv, spline, u, r0D);
}

} // namespace ocn

//
// File trailer for evalPositionFromU.cpp
//
// [EOF]
//
