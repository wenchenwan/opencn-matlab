//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStructInPieceFrame.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 09:27:31
//

// Include Files
#include "EvalCurvStructInPieceFrame.h"
#include "EvalCurvStruct.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types21.h"
#include "queue_coder.h"
#include "coder_array.h"

// Function Definitions
//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructInPieceFrame( ctx, curv, u_vec )
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const bool ctx_cfg_maskCart_data[]
//                const int ctx_cfg_maskCart_size[2]
//                const bool ctx_cfg_maskRot_data[]
//                const int ctx_cfg_maskRot_size[2]
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                GcodeInfoStruct curv_Info
//                const double curv_R0[6]
//                const double curv_R1[6]
//                const double curv_CorrectedHelixCenter[3]
//                const double curv_evec[3]
//                double curv_theta
//                double curv_pitch
//                const ::coder::array<double, 2U> &curv_CoeffP5
//                unsigned int curv_sp_index
//                double curv_a_param
//                double curv_b_param
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
// Return Type  : void
//
namespace ocn {
void EvalCurvStructInPieceFrame(
    const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
    const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
    const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
    const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
    int ctx_cfg_NRot, GcodeInfoStruct curv_Info, const double curv_R0[6], const double curv_R1[6],
    const double curv_CorrectedHelixCenter[3], const double curv_evec[3], double curv_theta,
    double curv_pitch, const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
    double curv_a_param, double curv_b_param, ::coder::array<double, 1U> &r0D,
    ::coder::array<double, 1U> &r1D)
{
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    // 'EvalCurvStructInPieceFrame:3' coder.inline("never");
    //  Detect cusp in piece frame
    // 'EvalCurvStructInPieceFrame:6' trafo_flag          = curv.Info.TRAFO;
    // 'EvalCurvStructInPieceFrame:7' curv.Info.TRAFO     = true;
    curv_Info.TRAFO = true;
    // 'EvalCurvStructInPieceFrame:9' [r0D, r1D, r2D, r3D]= EvalCurvStruct( ctx, curv, u_vec );
    b_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv_Info, curv_R0, curv_R1,
                     curv_CorrectedHelixCenter, curv_evec, curv_theta, curv_pitch, curv_CoeffP5,
                     curv_sp_index, curv_a_param, curv_b_param, r0D, r1D, r2D, r3D);
    // 'EvalCurvStructInPieceFrame:11' curv.Info.TRAFO     = trafo_flag;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructInPieceFrame( ctx, curv, u_vec )
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const bool ctx_cfg_maskCart_data[]
//                const int ctx_cfg_maskCart_size[2]
//                const bool ctx_cfg_maskRot_data[]
//                const int ctx_cfg_maskRot_size[2]
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
// Return Type  : void
//
void b_EvalCurvStructInPieceFrame(
    const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
    const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
    const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
    const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
    int ctx_cfg_NRot, CurvStruct *curv, ::coder::array<double, 1U> &r0D,
    ::coder::array<double, 1U> &r1D)
{
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    // 'EvalCurvStructInPieceFrame:3' coder.inline("never");
    //  Detect cusp in piece frame
    // 'EvalCurvStructInPieceFrame:6' trafo_flag          = curv.Info.TRAFO;
    // 'EvalCurvStructInPieceFrame:7' curv.Info.TRAFO     = true;
    curv->Info.TRAFO = true;
    // 'EvalCurvStructInPieceFrame:9' [r0D, r1D, r2D, r3D]= EvalCurvStruct( ctx, curv, u_vec );
    c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv, r0D, r1D, r2D, r3D);
    // 'EvalCurvStructInPieceFrame:11' curv.Info.TRAFO     = trafo_flag;
}

} // namespace ocn

//
// File trailer for EvalCurvStructInPieceFrame.cpp
//
// [EOF]
//
