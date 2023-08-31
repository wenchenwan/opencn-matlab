//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStruct.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 31-Aug-2023 09:10:03
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
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "coder_array.h"
#include "coder_bounded_array.h"

// Variable Definitions
namespace ocn {
static CurvStruct splineDefault;

static bool splineDefault_not_empty;

} // namespace ocn

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
    ::coder::array<int, 1U> t10_indCart;
    ::coder::array<int, 1U> t10_indRot;
    CurvStruct spline;
    int b_loop_ub;
    int c_loop_ub;
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
    t10_indCart.set_size(ctx->cfg.indCart.size[0]);
    loop_ub = ctx->cfg.indCart.size[0];
    for (int i{0}; i < loop_ub; i++) {
        t10_indCart[i] = ctx->cfg.indCart.data[i];
    }
    t10_indRot.set_size(ctx->cfg.indRot.size[0]);
    b_loop_ub = ctx->cfg.indRot.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        t10_indRot[i1] = ctx->cfg.indRot.data[i1];
    }
    b_u_vec.set_size(1, u_vec.size(1));
    c_loop_ub = u_vec.size(1) - 1;
    for (int i2{0}; i2 <= c_loop_ub; i2++) {
        b_u_vec[i2] = u_vec[i2];
    }
    EvalCurvStructNoCtx(ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.maskCart.data,
                        ctx->cfg.maskCart.size, ctx->cfg.maskRot.data, ctx->cfg.maskRot.size,
                        t10_indCart, t10_indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                        curv, &spline, b_u_vec, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : void
// Return Type  : void
//
void EvalCurvStruct_init()
{
    Axes params_tool_offset;
    SplineStruct params_spline;
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
    double params_tool_backangle;
    double params_tool_diameter;
    double params_tool_frontangle;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
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
    paramsDefaultCurv(&params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                      &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                      &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                      &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                      &params_gcodeInfoStruct_G91_1, &params_tool_toolno, &params_tool_pocketno,
                      &params_tool_offset, &params_tool_diameter, &params_tool_frontangle,
                      &params_tool_backangle, &params_tool_orientation, &params_spline, params_R0,
                      params_R1, params_Cprim, &expl_temp, params_evec, &b_expl_temp, &c_expl_temp,
                      params_CoeffP5, &d_expl_temp);
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.tool, ...
    // 'constrCurvStructType:14'         params.spline, params.R0, params.R1, params.Cprim, ...
    // 'constrCurvStructType:15'         params.delta, params.evec, params.theta, params.pitch, ...
    // 'constrCurvStructType:16'         params.CoeffP5, params.Coeff );
    b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                       params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                       params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                       params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                       params_gcodeInfoStruct_G91_1, params_tool_toolno, params_tool_pocketno,
                       &params_tool_offset, params_tool_diameter, params_tool_frontangle,
                       params_tool_backangle, params_tool_orientation, &params_spline, params_R0,
                       params_R1, params_Cprim, params_evec, params_CoeffP5, &splineDefault);
    splineDefault_not_empty = true;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : const bool ctx_cfg_maskTot_data[]
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
//                const CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void b_EvalCurvStruct(const bool ctx_cfg_maskTot_data[], const int ctx_cfg_maskTot_size[2],
                      const bool ctx_cfg_maskCart_data[], const int ctx_cfg_maskCart_size[2],
                      const bool ctx_cfg_maskRot_data[], const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                      ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D)
{
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:7' if( isempty( splineDefault ) )
    // 'EvalCurvStruct:9' if( curv.Info.Type == CurveType.Spline )
    // 'EvalCurvStruct:12' else
    // 'EvalCurvStruct:13' spline = splineDefault;
    // 'EvalCurvStruct:16' [ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline,
    // u_vec );
    c_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                          ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                          ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                          ctx_cfg_NRot, curv, &splineDefault, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
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
//                const CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
// Return Type  : void
//
void c_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
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
    d_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                          ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                          ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                          ctx_cfg_NRot, curv, &spline, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
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
//                const CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
// Return Type  : void
//
void d_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
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
    c_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                          ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                          ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                          ctx_cfg_NRot, curv, &spline, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
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
//                const CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
// Return Type  : void
//
void e_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
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
    d_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                          ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                          ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                          ctx_cfg_NRot, curv, &spline, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
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
//                const CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
// Return Type  : void
//
void f_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
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
    c_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                          ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                          ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                          ctx_cfg_NRot, curv, &spline, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
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
//                const CurvStruct *curv
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void g_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
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
    EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                        ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                        ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                        ctx_cfg_NRot, curv, &spline, b_u_vec, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
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
//                const CurvStruct *curv
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
// Return Type  : void
//
void h_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
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
    EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                        ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                        ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                        ctx_cfg_NRot, curv, &spline, b_u_vec, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
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
//                const CurvStruct *curv
//                double u_vec
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void i_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
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
    e_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                          ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                          ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                          ctx_cfg_NRot, curv, &spline, u_vec, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
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
//                const CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
// Return Type  : void
//
void j_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D)
{
    ::coder::array<double, 1U> r1D;
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
    c_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                          ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                          ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                          ctx_cfg_NRot, curv, &spline, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
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
//                const CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
// Return Type  : void
//
void k_EvalCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                      const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                      const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                      const int ctx_cfg_maskRot_size[2],
                      const ::coder::array<int, 1U> &ctx_cfg_indCart,
                      const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                      int ctx_cfg_NCart, int ctx_cfg_NRot, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D)
{
    ::coder::array<double, 1U> r1D;
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
    d_EvalCurvStructNoCtx(ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                          ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                          ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                          ctx_cfg_NRot, curv, &spline, r0D, r1D, r2D, r3D);
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct( ctx, curv, u_vec )
//
// Arguments    : const FeedoptConfig *ctx_cfg
//                const CurvStruct *curv
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void l_EvalCurvStruct(const FeedoptConfig *ctx_cfg, const CurvStruct *curv,
                      ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                      ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D)
{
    ::coder::array<int, 1U> t3_indCart;
    ::coder::array<int, 1U> t3_indRot;
    Axes params_tool_offset;
    SplineStruct params_spline;
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
    double params_tool_backangle;
    double params_tool_diameter;
    double params_tool_frontangle;
    int b_loop_ub;
    int loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:7' if( isempty( splineDefault ) )
    if (!splineDefault_not_empty) {
        // 'EvalCurvStruct:7' splineDefault = constrCurvStructType;
        //  constrCurvStructType : Constructs a constrCurvStruct with default values.
        // 'constrCurvStructType:4' if( nargin > 0 )
        // 'constrCurvStructType:6' else
        // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
        paramsDefaultCurv(&params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                          &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                          &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                          &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                          &params_gcodeInfoStruct_G91_1, &params_tool_toolno, &params_tool_pocketno,
                          &params_tool_offset, &params_tool_diameter, &params_tool_frontangle,
                          &params_tool_backangle, &params_tool_orientation, &params_spline,
                          params_R0, params_R1, params_Cprim, &expl_temp, params_evec, &b_expl_temp,
                          &c_expl_temp, params_CoeffP5, &d_expl_temp);
        // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
        // 'constrCurvStructType:12' else
        // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.tool, ...
        // 'constrCurvStructType:14'         params.spline, params.R0, params.R1, params.Cprim, ...
        // 'constrCurvStructType:15'         params.delta, params.evec, params.theta, params.pitch,
        // ... 'constrCurvStructType:16'         params.CoeffP5, params.Coeff );
        b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                           params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                           params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                           params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                           params_gcodeInfoStruct_G91_1, params_tool_toolno, params_tool_pocketno,
                           &params_tool_offset, params_tool_diameter, params_tool_frontangle,
                           params_tool_backangle, params_tool_orientation, &params_spline,
                           params_R0, params_R1, params_Cprim, params_evec, params_CoeffP5,
                           &splineDefault);
        splineDefault_not_empty = true;
    }
    // 'EvalCurvStruct:9' if( curv.Info.Type == CurveType.Spline )
    // 'EvalCurvStruct:12' else
    // 'EvalCurvStruct:13' spline = splineDefault;
    // 'EvalCurvStruct:16' [ r0D, r1D, r2D, r3D ] = EvalCurvStructNoCtx( ctx.cfg, curv, spline,
    // u_vec );
    t3_indCart.set_size(ctx_cfg->indCart.size[0]);
    loop_ub = ctx_cfg->indCart.size[0];
    for (int i{0}; i < loop_ub; i++) {
        t3_indCart[i] = ctx_cfg->indCart.data[i];
    }
    t3_indRot.set_size(ctx_cfg->indRot.size[0]);
    b_loop_ub = ctx_cfg->indRot.size[0];
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        t3_indRot[i1] = ctx_cfg->indRot.data[i1];
    }
    c_EvalCurvStructNoCtx(ctx_cfg->maskTot.data, ctx_cfg->maskTot.size, ctx_cfg->maskCart.data,
                          ctx_cfg->maskCart.size, ctx_cfg->maskRot.data, ctx_cfg->maskRot.size,
                          t3_indCart, t3_indRot, ctx_cfg->NumberAxis, ctx_cfg->NCart, ctx_cfg->NRot,
                          curv, &splineDefault, r0D, r1D, r2D, r3D);
}

} // namespace ocn

//
// File trailer for EvalCurvStruct.cpp
//
// [EOF]
//
