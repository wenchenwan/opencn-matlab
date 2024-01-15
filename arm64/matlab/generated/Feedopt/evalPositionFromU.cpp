
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: evalPositionFromU.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "evalPositionFromU.h"
#include "EvalCurvStructNoCtx.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types111.h"
#include "coder_array.h"
#include "coder_bounded_array.h"

// Function Definitions
//
// function  [ r0D ] = evalPositionFromU( cfg, curv, spline, u )
//
// evalPositionFromU : Eval a curv on a set of u values. No context is
//  required, only the corresponding spline of the curve or a dummy one.
//
//  Inputs :
//  cfg       : The configuration structure of the computational chain
//  curv      : The curve structure
//  spline    : The spline structure
//  u         : The u values
//
//  Outputs :
//  r0D       : Matrix of points for a given set of u values
//
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
    ::coder::array<int, 1U> t29_indCart;
    ::coder::array<int, 1U> t29_indRot;
    int b_loop_ub;
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'evalPositionFromU:15' coder.inline( "never" );
    // 'evalPositionFromU:16' r0D = EvalCurvStructNoCtx( cfg, curv, spline, u );
    t29_indCart.set_size(cfg.indCart.size[0]);
    loop_ub = cfg.indCart.size[0];
    for (int i{0}; i < loop_ub; i++) {
        t29_indCart[i] = cfg.indCart.data[i];
    }
    t29_indRot.set_size(cfg.indRot.size[0]);
    b_loop_ub = cfg.indRot.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        t29_indRot[i1] = cfg.indRot.data[i1];
    }
    b_EvalCurvStructNoCtx(cfg.maskTot.data, cfg.maskTot.size, cfg.maskCart.data, cfg.maskCart.size,
                          cfg.maskRot.data, cfg.maskRot.size, t29_indCart, t29_indRot,
                          cfg.NumberAxis, cfg.NCart, cfg.NRot, curv, spline, u, r0D);
}

} // namespace ocn

//
// File trailer for evalPositionFromU.cpp
//
// [EOF]
//
