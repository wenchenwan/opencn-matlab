
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: LengthCurv.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "LengthCurv.h"
#include "EvalCurvStruct.h"
#include "TransP5LengthApprox.h"
#include "ocn_assert.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "splineLength.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function L = LengthCurv( ctx, curv, u0, u1 )
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
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *curv
// Return Type  : double
//
namespace ocn {
double LengthCurv(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                  const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                  const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                  const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
                  const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                  int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_GaussLegendreX[5],
                  const double ctx_cfg_GaussLegendreW[5], const CurvStruct *curv)
{
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D;
    CurvStruct expl_temp;
    double L;
    // 'LengthCurv:3' if ( curv.Info.Type == CurveType.Helix ) || ...
    // 'LengthCurv:4'    ( curv.Info.Type == CurveType.Line )
    if ((curv->Info.Type == CurveType_Helix) || (curv->Info.Type == CurveType_Line)) {
        int loop_ub;
        // 'LengthCurv:5' [~, r1D] = EvalCurvStruct( ctx, curv, u0 );
        d_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, a__1, r1D);
        // 'LengthCurv:6' L        = MyNorm( r1D ) * ( u1 - u0 );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        r.set_size(r1D.size(0));
        loop_ub = r1D.size(0);
        for (int i{0}; i < loop_ub; i++) {
            double varargin_1;
            varargin_1 = r1D[i];
            r[i] = std::pow(varargin_1, 2.0);
        }
        L = std::sqrt(coder::sum(r));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
    } else if (curv->Info.Type == CurveType_Spline) {
        // 'LengthCurv:7' elseif ( curv.Info.Type == CurveType.Spline )
        // 'LengthCurv:8' a        = curv.a_param;
        // 'LengthCurv:9' b        = curv.b_param;
        // 'LengthCurv:10' u0_tilda = a * u0 + b;
        // 'LengthCurv:11' u1_tilda = a * u1 + b;
        // 'LengthCurv:12' spline   = ctx.q_spline.get( curv.sp_index );
        ctx_q_spline->get(curv->sp_index, &expl_temp);
        // 'LengthCurv:13' [ L ]    = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda );
        L = splineLength(ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, expl_temp.sp.Bl.handle,
                         expl_temp.sp.Bl.order, expl_temp.sp.coeff, expl_temp.sp.knots,
                         expl_temp.sp.Lk, curv->b_param, curv->a_param + curv->b_param);
    } else if (curv->Info.Type == CurveType_TransP5) {
        // 'LengthCurv:14' elseif ( curv.Info.Type == CurveType.TransP5 )
        // 'LengthCurv:15' a        = curv.a_param;
        // 'LengthCurv:16' b        = curv.b_param;
        // 'LengthCurv:17' u0_tilda = a * u0 + b;
        // 'LengthCurv:18' u1_tilda = a * u1 + b;
        // 'LengthCurv:19' L = TransP5LengthApprox( curv, u0_tilda, u1_tilda );
        L = TransP5LengthApprox(curv->CoeffP5, curv->b_param, curv->a_param + curv->b_param);
    } else {
        // 'LengthCurv:20' else
        // 'LengthCurv:21' ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV", mfilename );
        jb_ocn_assert();
        // 'LengthCurv:22' L = 0;
        L = 0.0;
    }
    return L;
}

} // namespace ocn

//
// File trailer for LengthCurv.cpp
//
// [EOF]
//
