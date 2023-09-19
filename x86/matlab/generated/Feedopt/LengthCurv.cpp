//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: LengthCurv.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:13:50
//

// Include Files
#include "LengthCurv.h"
#include "EvalCurvStruct.h"
#include "TransP5LengthApprox.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
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
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> a__3;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D;
    CurvStruct expl_temp;
    double L;
    // 'LengthCurv:3' if ( curv.Info.Type == CurveType.Helix ) || ( curv.Info.Type == CurveType.Line
    // )
    if ((curv->Info.Type == CurveType_Helix) || (curv->Info.Type == CurveType_Line)) {
        int loop_ub;
        // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
        c_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, a__1, r1D, a__2, a__3);
        // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        r.set_size(r1D.size(0));
        loop_ub = r1D.size(0);
        for (int i1{0}; i1 < loop_ub; i1++) {
            double varargin_1;
            varargin_1 = r1D[i1];
            r[i1] = std::pow(varargin_1, 2.0);
        }
        L = std::sqrt(coder::sum(r));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
    } else if (curv->Info.Type == CurveType_Spline) {
        // 'LengthCurv:6' elseif ( curv.Info.Type == CurveType.Spline )
        // 'LengthCurv:7' a        = curv.a_param;
        // 'LengthCurv:8' b        = curv.b_param;
        // 'LengthCurv:9' u0_tilda = a * u0 + b;
        // 'LengthCurv:10' u1_tilda = a * u1 + b;
        // 'LengthCurv:11' spline   = ctx.q_spline.get( curv.sp_index );
        ctx_q_spline->get(curv->sp_index, &expl_temp);
        // 'LengthCurv:12' [ L ]    = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda );
        L = splineLength(ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, expl_temp.sp.Bl.handle,
                         expl_temp.sp.Bl.order, expl_temp.sp.coeff, expl_temp.sp.knots,
                         expl_temp.sp.Lk, curv->b_param, curv->a_param + curv->b_param);
    } else if (curv->Info.Type == CurveType_TransP5) {
        // 'LengthCurv:13' elseif ( curv.Info.Type == CurveType.TransP5 )
        // 'LengthCurv:14' L = TransP5LengthApprox( curv );
        L = TransP5LengthApprox(curv->CoeffP5);
    } else {
        char message[29];
        // 'LengthCurv:15' else
        // 'LengthCurv:16' c_assert(false, 'BAD CURVE TYPE IN LENGTH CURV');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i{0}; i < 29; i++) {
            message[i] = cv1[i];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        // 'LengthCurv:17' L = 0;
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
