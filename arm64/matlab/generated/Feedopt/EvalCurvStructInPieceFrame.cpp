
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStructInPieceFrame.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "EvalCurvStructInPieceFrame.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "opencn_matlab_types2.h"
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
//                const Kinematics *ctx_kin
//                const GcodeInfoStruct curv_Info
//                const ::coder::array<double, 1U> &curv_R0
//                const ::coder::array<double, 1U> &curv_R1
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
    int ctx_cfg_NRot, const Kinematics *ctx_kin, const GcodeInfoStruct curv_Info,
    const ::coder::array<double, 1U> &curv_R0, const ::coder::array<double, 1U> &curv_R1,
    const double curv_CorrectedHelixCenter[3], const double curv_evec[3], double curv_theta,
    double curv_pitch, const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
    double curv_a_param, double curv_b_param, ::coder::array<double, 1U> &r0D,
    ::coder::array<double, 1U> &r1D)
{
    ::coder::array<double, 1U> b_r0D;
    ::coder::array<double, 1U> b_r1D;
    ::coder::array<double, 1U> b_r2D;
    ::coder::array<double, 1U> b_r3D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    // 'EvalCurvStructInPieceFrame:3' coder.inline("never");
    //  Detect cusp in piece frame
    // 'EvalCurvStructInPieceFrame:6' [r0D, r1D, r2D, r3D]= EvalCurvStruct( ctx, curv, u_vec );
    b_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv_Info, curv_R0, curv_R1,
                     curv_CorrectedHelixCenter, curv_evec, curv_theta, curv_pitch, curv_CoeffP5,
                     curv_sp_index, curv_a_param, curv_b_param, r0D, r1D, r2D, r3D);
    // 'EvalCurvStructInPieceFrame:8' if( ~curv.Info.TRAFO )
    if (!curv_Info.TRAFO) {
        int b_loop_ub;
        int loop_ub;
        //  Aply Kinematic transform
        // 'EvalCurvStructInPieceFrame:10' ctx.kin.set_tool_length( curv.tool.offset.z );
        // 'EvalCurvStructInPieceFrame:11' [r0D, r1D, r2D, r3D] = ctx.kin.relative(r0D, r1D, r2D,
        // r3D);
        b_r0D.set_size(r0D.size(0));
        loop_ub = r0D.size(0) - 1;
        for (int i{0}; i <= loop_ub; i++) {
            b_r0D[i] = r0D[i];
        }
        b_r1D.set_size(r1D.size(0));
        b_loop_ub = r1D.size(0) - 1;
        for (int i1{0}; i1 <= b_loop_ub; i1++) {
            b_r1D[i1] = r1D[i1];
        }
        ctx_kin->relative(b_r0D, b_r1D, r2D, r3D, r0D, r1D, b_r2D, b_r3D);
    }
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
//                const Kinematics *ctx_kin
//                const GcodeInfoStruct curv_Info
//                const ::coder::array<double, 1U> &curv_R0
//                const ::coder::array<double, 1U> &curv_R1
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
void b_EvalCurvStructInPieceFrame(
    const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
    const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
    const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
    const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
    const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
    int ctx_cfg_NRot, const Kinematics *ctx_kin, const GcodeInfoStruct curv_Info,
    const ::coder::array<double, 1U> &curv_R0, const ::coder::array<double, 1U> &curv_R1,
    const double curv_CorrectedHelixCenter[3], const double curv_evec[3], double curv_theta,
    double curv_pitch, const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
    double curv_a_param, double curv_b_param, ::coder::array<double, 1U> &r0D,
    ::coder::array<double, 1U> &r1D)
{
    ::coder::array<double, 1U> b_r0D;
    ::coder::array<double, 1U> b_r1D;
    ::coder::array<double, 1U> b_r2D;
    ::coder::array<double, 1U> b_r3D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    // 'EvalCurvStructInPieceFrame:3' coder.inline("never");
    //  Detect cusp in piece frame
    // 'EvalCurvStructInPieceFrame:6' [r0D, r1D, r2D, r3D]= EvalCurvStruct( ctx, curv, u_vec );
    c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, curv_Info, curv_R0, curv_R1,
                     curv_CorrectedHelixCenter, curv_evec, curv_theta, curv_pitch, curv_CoeffP5,
                     curv_sp_index, curv_a_param, curv_b_param, r0D, r1D, r2D, r3D);
    // 'EvalCurvStructInPieceFrame:8' if( ~curv.Info.TRAFO )
    if (!curv_Info.TRAFO) {
        int b_loop_ub;
        int loop_ub;
        //  Aply Kinematic transform
        // 'EvalCurvStructInPieceFrame:10' ctx.kin.set_tool_length( curv.tool.offset.z );
        // 'EvalCurvStructInPieceFrame:11' [r0D, r1D, r2D, r3D] = ctx.kin.relative(r0D, r1D, r2D,
        // r3D);
        b_r0D.set_size(r0D.size(0));
        loop_ub = r0D.size(0) - 1;
        for (int i{0}; i <= loop_ub; i++) {
            b_r0D[i] = r0D[i];
        }
        b_r1D.set_size(r1D.size(0));
        b_loop_ub = r1D.size(0) - 1;
        for (int i1{0}; i1 <= b_loop_ub; i1++) {
            b_r1D[i1] = r1D[i1];
        }
        ctx_kin->relative(b_r0D, b_r1D, r2D, r3D, r0D, r1D, b_r2D, b_r3D);
    }
}

} // namespace ocn

//
// File trailer for EvalCurvStructInPieceFrame.cpp
//
// [EOF]
//
