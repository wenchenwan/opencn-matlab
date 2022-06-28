//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: evalPositionFromU.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Jun-2022 16:07:49
//

// Include Files
#include "evalPositionFromU.h"
#include "EvalCurvStructNoCtx.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
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
    ::coder::array<int, 1U> t6_indCart;
    ::coder::array<int, 1U> t6_indRot;
    ::coder::array<bool, 2U> t6_maskCart;
    ::coder::array<bool, 2U> t6_maskRot;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'evalPositionFromU:3' coder.inline( "never" );
    // 'evalPositionFromU:4' r0D = EvalCurvStructNoCtx( cfg, curv, spline, u );
    t6_maskCart.set_size(1, cfg.maskCart.size[1]);
    loop_ub = cfg.maskCart.size[1];
    for (int i{0}; i < loop_ub; i++) {
        t6_maskCart[i] = cfg.maskCart.data[i];
    }
    t6_maskRot.set_size(1, cfg.maskRot.size[1]);
    b_loop_ub = cfg.maskRot.size[1];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        t6_maskRot[i1] = cfg.maskRot.data[i1];
    }
    t6_indCart.set_size(cfg.indCart.size[0]);
    c_loop_ub = cfg.indCart.size[0];
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        t6_indCart[i2] = cfg.indCart.data[i2];
    }
    t6_indRot.set_size(cfg.indRot.size[0]);
    d_loop_ub = cfg.indRot.size[0];
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        t6_indRot[i3] = cfg.indRot.data[i3];
    }
    b_EvalCurvStructNoCtx(cfg.maskTot.data, cfg.maskTot.size, t6_maskCart, t6_maskRot, t6_indCart,
                          t6_indRot, cfg.NumberAxis, cfg.NCart, cfg.NRot, curv, spline, u, r0D);
}

} // namespace ocn

//
// File trailer for evalPositionFromU.cpp
//
// [EOF]
//
