//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:17:54
//

// Include Files
#include "EvalCurvStruct.h"
#include "EvalCurvStructNoCtx.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "coder_array.h"

// Variable Definitions
namespace ocn {
static CurvStruct splineDefault;

}

// Function Definitions
//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : const FeedoptContext *ctx
//                const CurvStruct *curv
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
namespace ocn {
void EvalCurvStruct(const FeedoptContext *ctx, const CurvStruct *curv,
                    const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                    ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                    ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> b_u_vec;
    CurvStruct spline;
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:7' if( isempty( splineDefault ) )
    // 'EvalCurvStruct:9' if( curv.Info.Type == CurveType.Spline )
    if (curv->Info.Type == CurveType_Spline) {
        // 'EvalCurvStruct:10' ptr    = curv.sp_index;
        // 'EvalCurvStruct:11' spline = ctx.q_spline.get( ptr );
        ctx->q_spline.get(curv->sp_index, &spline);
    } else {
        // 'EvalCurvStruct:12' else
        // 'EvalCurvStruct:13' spline = splineDefault;
        spline = splineDefault;
    }
    // 'EvalCurvStruct:16' [ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline,
    // u_vec );
    b_u_vec.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1) - 1;
    for (int i{0}; i <= loop_ub; i++) {
        b_u_vec[i] = u_vec[i];
    }
    f_EvalCurvStructNoCtx(ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.maskCart,
                          ctx->cfg.maskRot, ctx->cfg.indCart.data, ctx->cfg.indRot.data,
                          ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, curv, &spline,
                          b_u_vec, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : void
// Return Type  : void
//
void EvalCurvStruct_init()
{
    ::coder::array<double, 2U> params_spline_Bl_breakpoints;
    ::coder::array<double, 2U> params_spline_Lk;
    ::coder::array<double, 2U> params_spline_coeff;
    ::coder::array<double, 2U> params_spline_knots;
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
    double params_Cprim[3];
    double params_evec[3];
    double b_expl_temp;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double params_gcodeInfoStruct_FeedRate;
    double params_gcodeInfoStruct_SpindleSpeed;
    double params_spline_Ltot;
    unsigned long params_spline_Bl_handle;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_spline_Bl_ncoeff;
    int params_spline_Bl_order;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    // 'EvalCurvStruct:7' splineDefault = constrCurvStructType;
    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
    // 'constrCurvStructType:4' if( nargin > 0 )
    // 'constrCurvStructType:6' else
    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
    paramsDefaultCurv(
        &params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
        &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
        &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
        &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
        &params_gcodeInfoStruct_G91_1, &params_spline_Bl_ncoeff, params_spline_Bl_breakpoints,
        &params_spline_Bl_handle, &params_spline_Bl_order, params_spline_coeff, params_spline_knots,
        &params_spline_Ltot, params_spline_Lk, params_R0, params_R1, params_Cprim, &expl_temp,
        params_evec, &b_expl_temp, &c_expl_temp, params_CoeffP5, &d_expl_temp);
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.spline, ...
    // 'constrCurvStructType:14'         params.R0, params.R1, ...
    // 'constrCurvStructType:15'         params.Cprim, params.delta, params.evec, params.theta, ...
    // 'constrCurvStructType:16'         params.pitch, params.CoeffP5, params.Coeff );
    b_constrCurvStruct(
        params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode, params_gcodeInfoStruct_TRAFO,
        params_gcodeInfoStruct_HSC, params_gcodeInfoStruct_FeedRate,
        params_gcodeInfoStruct_SpindleSpeed, params_gcodeInfoStruct_gcode_source_line,
        params_gcodeInfoStruct_G91, params_gcodeInfoStruct_G91_1, params_spline_Bl_ncoeff,
        params_spline_Bl_breakpoints, params_spline_Bl_handle, params_spline_Bl_order,
        params_spline_coeff, params_spline_knots, params_spline_Ltot, params_spline_Lk, params_R0,
        params_R1, params_Cprim, params_evec, params_CoeffP5, &splineDefault);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &ctx_cfg_maskCart
//                const ::coder::array<bool, 2U> &ctx_cfg_maskRot
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2],
                      const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                      const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D)
{
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    CurvStruct spline;
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:7' if( isempty( splineDefault ) )
    // 'EvalCurvStruct:9' if( curv.Info.Type == CurveType.Spline )
    if (curv->Info.Type == CurveType_Spline) {
        // 'EvalCurvStruct:10' ptr    = curv.sp_index;
        // 'EvalCurvStruct:11' spline = ctx.q_spline.get( ptr );
        ctx_q_spline->get(curv->sp_index, &spline);
    } else {
        // 'EvalCurvStruct:12' else
        // 'EvalCurvStruct:13' spline = splineDefault;
        spline = splineDefault;
    }
    // 'EvalCurvStruct:16' [ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline,
    // u_vec );
    c_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                          ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                          ctx_cfg_NCart, ctx_cfg_NRot, curv, &spline, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &ctx_cfg_maskCart
//                const ::coder::array<bool, 2U> &ctx_cfg_maskRot
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
// Return Type  : void
//
void c_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2],
                      const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                      const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D)
{
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    CurvStruct spline;
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:7' if( isempty( splineDefault ) )
    // 'EvalCurvStruct:9' if( curv.Info.Type == CurveType.Spline )
    if (curv->Info.Type == CurveType_Spline) {
        // 'EvalCurvStruct:10' ptr    = curv.sp_index;
        // 'EvalCurvStruct:11' spline = ctx.q_spline.get( ptr );
        ctx_q_spline->get(curv->sp_index, &spline);
    } else {
        // 'EvalCurvStruct:12' else
        // 'EvalCurvStruct:13' spline = splineDefault;
        spline = splineDefault;
    }
    // 'EvalCurvStruct:16' [ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline,
    // u_vec );
    d_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                          ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                          ctx_cfg_NCart, ctx_cfg_NRot, curv, &spline, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &ctx_cfg_maskCart
//                const ::coder::array<bool, 2U> &ctx_cfg_maskRot
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const GcodeInfoStruct curv_Info
//                const double curv_R0[6]
//                const double curv_R1[6]
//                const double curv_CorrectedHelixCenter[3]
//                const double curv_evec[3]
//                double curv_theta
//                double curv_pitch
//                const ::coder::array<double, 2U> &curv_CoeffP5
//                double curv_a_param
//                double curv_b_param
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void d_EvalCurvStruct(const bool ctx_cfg_maskTot_data[], const int ctx_cfg_maskTot_size[2],
                      const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                      const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const GcodeInfoStruct curv_Info,
                      const double curv_R0[6], const double curv_R1[6],
                      const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                      double curv_theta, double curv_pitch,
                      const ::coder::array<double, 2U> &curv_CoeffP5, double curv_a_param,
                      double curv_b_param, ::coder::array<double, 1U> &r0D,
                      ::coder::array<double, 1U> &r1D, ::coder::array<double, 1U> &r2D,
                      ::coder::array<double, 1U> &r3D)
{
    CurvStruct expl_temp;
    int loop_ub;
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:7' if( isempty( splineDefault ) )
    // 'EvalCurvStruct:9' if( curv.Info.Type == CurveType.Spline )
    // 'EvalCurvStruct:12' else
    // 'EvalCurvStruct:13' spline = splineDefault;
    // 'EvalCurvStruct:16' [ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline,
    // u_vec );
    expl_temp.b_param = curv_b_param;
    expl_temp.a_param = curv_a_param;
    expl_temp.CoeffP5.set_size(curv_CoeffP5.size(0), 6);
    loop_ub = curv_CoeffP5.size(0);
    expl_temp.pitch = curv_pitch;
    expl_temp.theta = curv_theta;
    expl_temp.evec[0] = curv_evec[0];
    expl_temp.CorrectedHelixCenter[0] = curv_CorrectedHelixCenter[0];
    expl_temp.evec[1] = curv_evec[1];
    expl_temp.CorrectedHelixCenter[1] = curv_CorrectedHelixCenter[1];
    expl_temp.evec[2] = curv_evec[2];
    expl_temp.CorrectedHelixCenter[2] = curv_CorrectedHelixCenter[2];
    for (int i{0}; i < 6; i++) {
        for (int b_i{0}; b_i < loop_ub; b_i++) {
            expl_temp.CoeffP5[b_i + expl_temp.CoeffP5.size(0) * i] =
                curv_CoeffP5[b_i + curv_CoeffP5.size(0) * i];
        }
        expl_temp.R1[i] = curv_R1[i];
        expl_temp.R0[i] = curv_R0[i];
    }
    expl_temp.Info = curv_Info;
    d_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                          ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                          ctx_cfg_NCart, ctx_cfg_NRot, &expl_temp, &splineDefault, r0D, r1D, r2D,
                          r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &ctx_cfg_maskCart
//                const ::coder::array<bool, 2U> &ctx_cfg_maskRot
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
// Return Type  : void
//
void e_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2],
                      const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                      const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                      ::coder::array<double, 1U> &r2D)
{
    ::coder::array<double, 1U> r3D;
    CurvStruct spline;
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:7' if( isempty( splineDefault ) )
    // 'EvalCurvStruct:9' if( curv.Info.Type == CurveType.Spline )
    if (curv->Info.Type == CurveType_Spline) {
        // 'EvalCurvStruct:10' ptr    = curv.sp_index;
        // 'EvalCurvStruct:11' spline = ctx.q_spline.get( ptr );
        ctx_q_spline->get(curv->sp_index, &spline);
    } else {
        // 'EvalCurvStruct:12' else
        // 'EvalCurvStruct:13' spline = splineDefault;
        spline = splineDefault;
    }
    // 'EvalCurvStruct:16' [ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline,
    // u_vec );
    c_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                          ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                          ctx_cfg_NCart, ctx_cfg_NRot, curv, &spline, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &ctx_cfg_maskCart
//                const ::coder::array<bool, 2U> &ctx_cfg_maskRot
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
// Return Type  : void
//
void f_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2],
                      const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                      const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                      ::coder::array<double, 1U> &r2D)
{
    ::coder::array<double, 1U> r3D;
    CurvStruct spline;
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:7' if( isempty( splineDefault ) )
    // 'EvalCurvStruct:9' if( curv.Info.Type == CurveType.Spline )
    if (curv->Info.Type == CurveType_Spline) {
        // 'EvalCurvStruct:10' ptr    = curv.sp_index;
        // 'EvalCurvStruct:11' spline = ctx.q_spline.get( ptr );
        ctx_q_spline->get(curv->sp_index, &spline);
    } else {
        // 'EvalCurvStruct:12' else
        // 'EvalCurvStruct:13' spline = splineDefault;
        spline = splineDefault;
    }
    // 'EvalCurvStruct:16' [ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline,
    // u_vec );
    d_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                          ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                          ctx_cfg_NCart, ctx_cfg_NRot, curv, &spline, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &ctx_cfg_maskCart
//                const ::coder::array<bool, 2U> &ctx_cfg_maskRot
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const CurvStruct *curv
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void g_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2],
                      const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                      const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                      ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                      ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> b_u_vec;
    CurvStruct spline;
    int loop_ub;
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:7' if( isempty( splineDefault ) )
    // 'EvalCurvStruct:9' if( curv.Info.Type == CurveType.Spline )
    if (curv->Info.Type == CurveType_Spline) {
        // 'EvalCurvStruct:10' ptr    = curv.sp_index;
        // 'EvalCurvStruct:11' spline = ctx.q_spline.get( ptr );
        ctx_q_spline->get(curv->sp_index, &spline);
    } else {
        // 'EvalCurvStruct:12' else
        // 'EvalCurvStruct:13' spline = splineDefault;
        spline = splineDefault;
    }
    // 'EvalCurvStruct:16' [ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline,
    // u_vec );
    b_u_vec.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1) - 1;
    for (int i{0}; i <= loop_ub; i++) {
        b_u_vec[i] = u_vec[i];
    }
    EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                        ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, curv, &spline, b_u_vec, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &ctx_cfg_maskCart
//                const ::coder::array<bool, 2U> &ctx_cfg_maskRot
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const CurvStruct *curv
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
// Return Type  : void
//
void h_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2],
                      const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                      const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                      ::coder::array<double, 2U> &r1D)
{
    ::coder::array<double, 2U> b_u_vec;
    ::coder::array<double, 2U> r2D;
    ::coder::array<double, 2U> r3D;
    CurvStruct spline;
    int loop_ub;
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:7' if( isempty( splineDefault ) )
    // 'EvalCurvStruct:9' if( curv.Info.Type == CurveType.Spline )
    if (curv->Info.Type == CurveType_Spline) {
        // 'EvalCurvStruct:10' ptr    = curv.sp_index;
        // 'EvalCurvStruct:11' spline = ctx.q_spline.get( ptr );
        ctx_q_spline->get(curv->sp_index, &spline);
    } else {
        // 'EvalCurvStruct:12' else
        // 'EvalCurvStruct:13' spline = splineDefault;
        spline = splineDefault;
    }
    // 'EvalCurvStruct:16' [ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline,
    // u_vec );
    b_u_vec.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1) - 1;
    for (int i{0}; i <= loop_ub; i++) {
        b_u_vec[i] = u_vec[i];
    }
    EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                        ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, curv, &spline, b_u_vec, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &ctx_cfg_maskCart
//                const ::coder::array<bool, 2U> &ctx_cfg_maskRot
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const CurvStruct *curv
//                double u_vec
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void i_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2],
                      const ::coder::array<bool, 2U> &ctx_cfg_maskCart,
                      const ::coder::array<bool, 2U> &ctx_cfg_maskRot,
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv, double u_vec,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                      ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D)
{
    CurvStruct spline;
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:7' if( isempty( splineDefault ) )
    // 'EvalCurvStruct:9' if( curv.Info.Type == CurveType.Spline )
    if (curv->Info.Type == CurveType_Spline) {
        // 'EvalCurvStruct:10' ptr    = curv.sp_index;
        // 'EvalCurvStruct:11' spline = ctx.q_spline.get( ptr );
        ctx_q_spline->get(curv->sp_index, &spline);
    } else {
        // 'EvalCurvStruct:12' else
        // 'EvalCurvStruct:13' spline = splineDefault;
        spline = splineDefault;
    }
    // 'EvalCurvStruct:16' [ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline,
    // u_vec );
    e_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart,
                          ctx_cfg_maskRot, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                          ctx_cfg_NCart, ctx_cfg_NRot, curv, &spline, u_vec, r0D, r1D, r2D, r3D);
}

} // namespace ocn

//
// File trailer for EvalCurvStruct.cpp
//
// [EOF]
//
