//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 11:18:27
//

// Include Files
#include "EvalCurvStruct.h"
#include "EvalBSpline.h"
#include "EvalHelix.h"
#include "EvalLine.h"
#include "EvalTransP5.h"
#include "bspline_eval.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const FeedoptContext *ctx
//                const CurvStruct *b_CurvStruct
//                ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
namespace ocn {
void EvalCurvStruct(const FeedoptContext *ctx, const CurvStruct *b_CurvStruct,
                    ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                    ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                    ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<bool, 2U> x;
    double b_c;
    double c;
    int b_k;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i_loop_ub;
    int j_loop_ub;
    int k;
    int loop_ub;
    char message[30];
    bool b_y;
    bool exitg1;
    bool y;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:4' if any(u_vec - 1.0 > 10*eps)
    x.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        x[i] = (u_vec[i] - 1.0 > 2.2204460492503131E-15);
    }
    y = false;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(1) - 1)) {
        if (x[k]) {
            y = true;
            exitg1 = true;
        } else {
            k++;
        }
    }
    if (y) {
        int end;
        // 'EvalCurvStruct:5' if coder.target('matlab')
        // 'EvalCurvStruct:7' else
        // 'EvalCurvStruct:8' fprintf('EvalCurvStruct: u_vec > 1\n');
        printf("EvalCurvStruct: u_vec > 1\n");
        fflush(stdout);
        // 'EvalCurvStruct:10' u_vec(u_vec > 1.0) = 1.0;
        end = u_vec.size(1);
        for (int b_i{0}; b_i < end; b_i++) {
            if (u_vec[b_i] > 1.0) {
                u_vec[b_i] = 1.0;
            }
        }
    }
    // 'EvalCurvStruct:13' if any(u_vec < 0.0)
    x.set_size(1, u_vec.size(1));
    b_loop_ub = u_vec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        x[i1] = (u_vec[i1] < 0.0);
    }
    b_y = false;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k <= x.size(1) - 1)) {
        if (x[b_k]) {
            b_y = true;
            exitg1 = true;
        } else {
            b_k++;
        }
    }
    if (b_y) {
        int b_end;
        // 'EvalCurvStruct:14' fprintf('EvalCurvStruct: u_vec < 0\n');
        printf("EvalCurvStruct: u_vec < 0\n");
        fflush(stdout);
        // 'EvalCurvStruct:15' u_vec(u_vec < 0.0) = 0.0;
        b_end = u_vec.size(1);
        for (int c_i{0}; c_i < b_end; c_i++) {
            if (u_vec[c_i] < 0.0) {
                u_vec[c_i] = 0.0;
            }
        }
    }
    //
    // 'EvalCurvStruct:19' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStruct:21' N = numel(u_vec);
    // 'EvalCurvStruct:22' r0D = zeros(3, N);
    r0D.set_size(3, u_vec.size(1));
    c_loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        r0D[3 * i2] = 0.0;
        r0D[3 * i2 + 1] = 0.0;
        r0D[3 * i2 + 2] = 0.0;
    }
    // 'EvalCurvStruct:23' r1D = zeros(3, N);
    r1D.set_size(3, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        r1D[3 * i3] = 0.0;
        r1D[3 * i3 + 1] = 0.0;
        r1D[3 * i3 + 2] = 0.0;
    }
    // 'EvalCurvStruct:24' r2D = zeros(3, N);
    r2D.set_size(3, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        r2D[3 * i4] = 0.0;
        r2D[3 * i4 + 1] = 0.0;
        r2D[3 * i4 + 2] = 0.0;
    }
    // 'EvalCurvStruct:25' r3D = zeros(3, N);
    r3D.set_size(3, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    for (int i5{0}; i5 < f_loop_ub; i5++) {
        r3D[3 * i5] = 0.0;
        r3D[3 * i5 + 1] = 0.0;
        r3D[3 * i5 + 2] = 0.0;
    }
    // 'EvalCurvStruct:27' a=CurvStruct.a_param;
    // 'EvalCurvStruct:28' b=CurvStruct.b_param;
    // 'EvalCurvStruct:30' u_vec_tilda = a*u_vec+b;
    u_vec_tilda.set_size(1, u_vec.size(1));
    g_loop_ub = u_vec.size(1);
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        u_vec_tilda[i6] = b_CurvStruct->a_param * u_vec[i6] + b_CurvStruct->b_param;
    }
    // 'EvalCurvStruct:32' switch Type
    switch (b_CurvStruct->Type) {
    case CurveType_Line:
        // 'EvalCurvStruct:33' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStruct:34' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(b_CurvStruct->P0, b_CurvStruct->P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        // 'EvalCurvStruct:35' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStruct:36' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(b_CurvStruct->P0, b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                  b_CurvStruct->theta, b_CurvStruct->pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        // 'EvalCurvStruct:37' case CurveType.TransP5
        //  polynomial transition
        // 'EvalCurvStruct:38' [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
        EvalTransP5(b_CurvStruct->CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        // 'EvalCurvStruct:39' case CurveType.Spline
        //  BSpline
        // 'EvalCurvStruct:40' [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
        EvalBSpline(&ctx->q_splines, b_CurvStruct->sp_index, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        // 'EvalCurvStruct:41' otherwise
        // 'EvalCurvStruct:42' c_assert(false, 'Unknown Curve Type for Eval.\n');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i7{0}; i7 < 30; i7++) {
            message[i7] = cv[i7];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStruct:45' r1D = a.*r1D;
    r1D.set_size(3, r1D.size(1));
    h_loop_ub = r1D.size(1);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        r1D[3 * i8] = b_CurvStruct->a_param * r1D[3 * i8];
        r1D[3 * i8 + 1] = b_CurvStruct->a_param * r1D[3 * i8 + 1];
        r1D[3 * i8 + 2] = b_CurvStruct->a_param * r1D[3 * i8 + 2];
    }
    // 'EvalCurvStruct:46' r2D = a^2.*r2D;
    c = b_CurvStruct->a_param * b_CurvStruct->a_param;
    r2D.set_size(3, r2D.size(1));
    i_loop_ub = r2D.size(1);
    for (int i9{0}; i9 < i_loop_ub; i9++) {
        r2D[3 * i9] = c * r2D[3 * i9];
        r2D[3 * i9 + 1] = c * r2D[3 * i9 + 1];
        r2D[3 * i9 + 2] = c * r2D[3 * i9 + 2];
    }
    // 'EvalCurvStruct:47' r3D = a^3.*r3D;
    b_c = std::pow(b_CurvStruct->a_param, 3.0);
    r3D.set_size(3, r3D.size(1));
    j_loop_ub = r3D.size(1);
    for (int i10{0}; i10 < j_loop_ub; i10++) {
        r3D[3 * i10] = b_c * r3D[3 * i10];
        r3D[3 * i10 + 1] = b_c * r3D[3 * i10 + 1];
        r3D[3 * i10 + 2] = b_c * r3D[3 * i10 + 2];
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[10][3]
//                double r1D[10][3]
//                double r2D[10][3]
//                double r3D[10][3]
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[10][3], double r1D[10][3], double r2D[10][3], double r3D[10][3])
{
    CurvStruct expl_temp;
    double r0Dx[10];
    double r0Dy[10];
    double r0Dz[10];
    double r1Dx[10];
    double r1Dy[10];
    double r1Dz[10];
    double r2Dx[10];
    double r2Dy[10];
    double r2Dz[10];
    double r3Dx[10];
    double r3Dy[10];
    double r3Dz[10];
    double u_vec_tilda[10];
    double b_c;
    double c;
    char message[30];
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:4' if any(u_vec - 1.0 > 10*eps)
    // 'EvalCurvStruct:13' if any(u_vec < 0.0)
    //
    // 'EvalCurvStruct:19' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStruct:21' N = numel(u_vec);
    // 'EvalCurvStruct:22' r0D = zeros(3, N);
    // 'EvalCurvStruct:23' r1D = zeros(3, N);
    // 'EvalCurvStruct:24' r2D = zeros(3, N);
    // 'EvalCurvStruct:25' r3D = zeros(3, N);
    // 'EvalCurvStruct:27' a=CurvStruct.a_param;
    // 'EvalCurvStruct:28' b=CurvStruct.b_param;
    // 'EvalCurvStruct:30' u_vec_tilda = a*u_vec+b;
    for (int i{0}; i < 10; i++) {
        r0D[i][0] = 0.0;
        r1D[i][0] = 0.0;
        r2D[i][0] = 0.0;
        r3D[i][0] = 0.0;
        r0D[i][1] = 0.0;
        r1D[i][1] = 0.0;
        r2D[i][1] = 0.0;
        r3D[i][1] = 0.0;
        r0D[i][2] = 0.0;
        r1D[i][2] = 0.0;
        r2D[i][2] = 0.0;
        r3D[i][2] = 0.0;
        u_vec_tilda[i] =
            CurvStruct_a_param * (0.1111111111111111 * static_cast<double>(i)) + CurvStruct_b_param;
    }
    // 'EvalCurvStruct:32' switch Type
    switch (CurvStruct_Type) {
    case CurveType_Line:
        // 'EvalCurvStruct:33' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStruct:34' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        // 'EvalCurvStruct:35' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStruct:36' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        // 'EvalCurvStruct:37' case CurveType.TransP5
        //  polynomial transition
        // 'EvalCurvStruct:38' [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        unsigned long Spline_sp_Bl_handle;
        // 'EvalCurvStruct:39' case CurveType.Spline
        //  BSpline
        // 'EvalCurvStruct:40' [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
        //  if coder.target('rtw') || coder.target('mex')
        // 'EvalBSpline:4' Spline=ctx.q_splines.get(CurvStruct.sp_index);
        ctx_q_splines->get(CurvStruct_sp_index, &expl_temp);
        Spline_sp_Bl_handle = expl_temp.sp.Bl.handle;
        // 'EvalBSpline:5' sp = Spline.sp;
        // 'EvalBSpline:6' Bl = sp.Bl;
        // 'EvalBSpline:7' [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        for (int k{0}; k < 10; k++) {
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0Dx[k] = u_vec_tilda[k];
            bspline_eval(Spline_sp_Bl_handle, expl_temp.sp.CoeffX, &r0Dx[k], &r1Dx[k], &r2Dx[k],
                         &r3Dx[k]);
            // 'bspline_eval_vec:10' x(k) = xk;
            // 'bspline_eval_vec:11' xd(k) = xdk;
            // 'bspline_eval_vec:12' xdd(k) = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
        // 'EvalBSpline:8' [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        for (int b_k{0}; b_k < 10; b_k++) {
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0Dy[b_k] = u_vec_tilda[b_k];
            bspline_eval(Spline_sp_Bl_handle, expl_temp.sp.CoeffY, &r0Dy[b_k], &r1Dy[b_k],
                         &r2Dy[b_k], &r3Dy[b_k]);
            // 'bspline_eval_vec:10' x(k) = xk;
            // 'bspline_eval_vec:11' xd(k) = xdk;
            // 'bspline_eval_vec:12' xdd(k) = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
        // 'EvalBSpline:9' [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        for (int c_k{0}; c_k < 10; c_k++) {
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0Dz[c_k] = u_vec_tilda[c_k];
            bspline_eval(Spline_sp_Bl_handle, expl_temp.sp.CoeffZ, &r0Dz[c_k], &r1Dz[c_k],
                         &r2Dz[c_k], &r3Dz[c_k]);
            // 'bspline_eval_vec:10' x(k) = xk;
            // 'bspline_eval_vec:11' xd(k) = xdk;
            // 'bspline_eval_vec:12' xdd(k) = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
        // 'EvalBSpline:11' r0D = [r0Dx; r0Dy; r0Dz];
        // 'EvalBSpline:12' r1D = [r1Dx; r1Dy; r1Dz];
        // 'EvalBSpline:13' r2D = [r2Dx; r2Dy; r2Dz];
        // 'EvalBSpline:14' r3D = [r3Dx; r3Dy; r3Dz];
        for (int i3{0}; i3 < 10; i3++) {
            r0D[i3][0] = r0Dx[i3];
            r0D[i3][1] = r0Dy[i3];
            r0D[i3][2] = r0Dz[i3];
            r1D[i3][0] = r1Dx[i3];
            r1D[i3][1] = r1Dy[i3];
            r1D[i3][2] = r1Dz[i3];
            r2D[i3][0] = r2Dx[i3];
            r2D[i3][1] = r2Dy[i3];
            r2D[i3][2] = r2Dz[i3];
            r3D[i3][0] = r3Dx[i3];
            r3D[i3][1] = r3Dy[i3];
            r3D[i3][2] = r3Dz[i3];
        }
        //  else
        //      Spline=ctx.q_splines.get(CurvStruct.sp_index);
        //      sp = Spline.sp;
        //      r0D = spval(sp, uvec);
        //
        //      sp1D = fnder(sp, 1);
        //      r1D = spval(sp1D, uvec);
        //
        //      sp2D = fnder(sp, 2);
        //      r2D = spval(sp2D, uvec);
        //
        //      sp3D = fnder(sp, 3);
        //      r3D = spval(sp3D, uvec);
        //  end
    } break;
    default:
        // 'EvalCurvStruct:41' otherwise
        // 'EvalCurvStruct:42' c_assert(false, 'Unknown Curve Type for Eval.\n');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i1{0}; i1 < 30; i1++) {
            message[i1] = cv[i1];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStruct:45' r1D = a.*r1D;
    // 'EvalCurvStruct:46' r2D = a^2.*r2D;
    c = CurvStruct_a_param * CurvStruct_a_param;
    // 'EvalCurvStruct:47' r3D = a^3.*r3D;
    b_c = std::pow(CurvStruct_a_param, 3.0);
    for (int i2{0}; i2 < 10; i2++) {
        r1D[i2][0] *= CurvStruct_a_param;
        r2D[i2][0] *= c;
        r3D[i2][0] *= b_c;
        r1D[i2][1] *= CurvStruct_a_param;
        r2D[i2][1] *= c;
        r3D[i2][1] *= b_c;
        r1D[i2][2] *= CurvStruct_a_param;
        r2D[i2][2] *= c;
        r3D[i2][2] *= b_c;
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                const CurvStruct *b_CurvStruct
//                double r0D[3]
//                double r1D[3]
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, const CurvStruct *b_CurvStruct,
                      double r0D[3], double r1D[3])
{
    CurvStruct expl_temp;
    double r2D[3];
    double r3D[3];
    double b_xdddk;
    double b_xddk;
    double c_xdddk;
    double c_xddk;
    double r0Dx;
    double r0Dy;
    double r0Dz;
    double r1Dx;
    double r1Dy;
    double r1Dz;
    double xdddk;
    double xddk;
    char message[30];
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:4' if any(u_vec - 1.0 > 10*eps)
    // 'EvalCurvStruct:13' if any(u_vec < 0.0)
    //
    // 'EvalCurvStruct:19' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStruct:21' N = numel(u_vec);
    // 'EvalCurvStruct:22' r0D = zeros(3, N);
    // 'EvalCurvStruct:23' r1D = zeros(3, N);
    r0D[0] = 0.0;
    r1D[0] = 0.0;
    r0D[1] = 0.0;
    r1D[1] = 0.0;
    r0D[2] = 0.0;
    r1D[2] = 0.0;
    // 'EvalCurvStruct:24' r2D = zeros(3, N);
    // 'EvalCurvStruct:25' r3D = zeros(3, N);
    // 'EvalCurvStruct:27' a=CurvStruct.a_param;
    // 'EvalCurvStruct:28' b=CurvStruct.b_param;
    // 'EvalCurvStruct:30' u_vec_tilda = a*u_vec+b;
    // 'EvalCurvStruct:32' switch Type
    switch (b_CurvStruct->Type) {
    case CurveType_Line:
        // 'EvalCurvStruct:33' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStruct:34' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(b_CurvStruct->P0, b_CurvStruct->P1, b_CurvStruct->b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        // 'EvalCurvStruct:35' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStruct:36' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(b_CurvStruct->P0, b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                  b_CurvStruct->theta, b_CurvStruct->pitch, b_CurvStruct->b_param, r0D, r1D, r2D,
                  r3D);
        break;
    case CurveType_TransP5:
        // 'EvalCurvStruct:37' case CurveType.TransP5
        //  polynomial transition
        // 'EvalCurvStruct:38' [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
        EvalTransP5(b_CurvStruct->CoeffP5, b_CurvStruct->b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        double r0Dx_tmp;
        // 'EvalCurvStruct:39' case CurveType.Spline
        //  BSpline
        // 'EvalCurvStruct:40' [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
        //  if coder.target('rtw') || coder.target('mex')
        // 'EvalBSpline:4' Spline=ctx.q_splines.get(CurvStruct.sp_index);
        ctx_q_splines->get(b_CurvStruct->sp_index, &expl_temp);
        // 'EvalBSpline:5' sp = Spline.sp;
        // 'EvalBSpline:6' Bl = sp.Bl;
        // 'EvalBSpline:7' [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dx_tmp = b_CurvStruct->b_param;
        r0Dx = r0Dx_tmp;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, &r0Dx, &r1Dx, &xddk, &xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:8' [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dy = r0Dx_tmp;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, &r0Dy, &r1Dy, &b_xddk, &b_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:9' [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dz = r0Dx_tmp;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, &r0Dz, &r1Dz, &c_xddk, &c_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:11' r0D = [r0Dx; r0Dy; r0Dz];
        r0D[0] = r0Dx;
        r0D[1] = r0Dy;
        r0D[2] = r0Dz;
        // 'EvalBSpline:12' r1D = [r1Dx; r1Dy; r1Dz];
        r1D[0] = r1Dx;
        r1D[1] = r1Dy;
        r1D[2] = r1Dz;
        // 'EvalBSpline:13' r2D = [r2Dx; r2Dy; r2Dz];
        // 'EvalBSpline:14' r3D = [r3Dx; r3Dy; r3Dz];
        //  else
        //      Spline=ctx.q_splines.get(CurvStruct.sp_index);
        //      sp = Spline.sp;
        //      r0D = spval(sp, uvec);
        //
        //      sp1D = fnder(sp, 1);
        //      r1D = spval(sp1D, uvec);
        //
        //      sp2D = fnder(sp, 2);
        //      r2D = spval(sp2D, uvec);
        //
        //      sp3D = fnder(sp, 3);
        //      r3D = spval(sp3D, uvec);
        //  end
    } break;
    default:
        // 'EvalCurvStruct:41' otherwise
        // 'EvalCurvStruct:42' c_assert(false, 'Unknown Curve Type for Eval.\n');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStruct:45' r1D = a.*r1D;
    r1D[0] *= b_CurvStruct->a_param;
    r1D[1] *= b_CurvStruct->a_param;
    r1D[2] *= b_CurvStruct->a_param;
    // 'EvalCurvStruct:46' r2D = a^2.*r2D;
    // 'EvalCurvStruct:47' r3D = a^3.*r3D;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_b_param
//                double r0D[3]
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_b_param, double r0D[3])
{
    CurvStruct expl_temp;
    double r1D[3];
    double r2D[3];
    double r3D[3];
    double b_xdddk;
    double b_xddk;
    double b_xdk;
    double c_xdddk;
    double c_xddk;
    double c_xdk;
    double r0Dx;
    double r0Dy;
    double r0Dz;
    double xdddk;
    double xddk;
    double xdk;
    char message[30];
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:4' if any(u_vec - 1.0 > 10*eps)
    // 'EvalCurvStruct:13' if any(u_vec < 0.0)
    //
    // 'EvalCurvStruct:19' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStruct:21' N = numel(u_vec);
    // 'EvalCurvStruct:22' r0D = zeros(3, N);
    r0D[0] = 0.0;
    r0D[1] = 0.0;
    r0D[2] = 0.0;
    // 'EvalCurvStruct:23' r1D = zeros(3, N);
    // 'EvalCurvStruct:24' r2D = zeros(3, N);
    // 'EvalCurvStruct:25' r3D = zeros(3, N);
    // 'EvalCurvStruct:27' a=CurvStruct.a_param;
    // 'EvalCurvStruct:28' b=CurvStruct.b_param;
    // 'EvalCurvStruct:30' u_vec_tilda = a*u_vec+b;
    // 'EvalCurvStruct:32' switch Type
    switch (CurvStruct_Type) {
    case CurveType_Line:
        // 'EvalCurvStruct:33' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStruct:34' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(CurvStruct_P0, CurvStruct_P1, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        // 'EvalCurvStruct:35' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStruct:36' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        // 'EvalCurvStruct:37' case CurveType.TransP5
        //  polynomial transition
        // 'EvalCurvStruct:38' [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
        EvalTransP5(CurvStruct_CoeffP5, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        // 'EvalCurvStruct:39' case CurveType.Spline
        //  BSpline
        // 'EvalCurvStruct:40' [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
        //  if coder.target('rtw') || coder.target('mex')
        // 'EvalBSpline:4' Spline=ctx.q_splines.get(CurvStruct.sp_index);
        ctx_q_splines->get(CurvStruct_sp_index, &expl_temp);
        // 'EvalBSpline:5' sp = Spline.sp;
        // 'EvalBSpline:6' Bl = sp.Bl;
        // 'EvalBSpline:7' [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dx = CurvStruct_b_param;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, &r0Dx, &xdk, &xddk, &xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:8' [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dy = CurvStruct_b_param;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, &r0Dy, &b_xdk, &b_xddk, &b_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:9' [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dz = CurvStruct_b_param;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, &r0Dz, &c_xdk, &c_xddk, &c_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:11' r0D = [r0Dx; r0Dy; r0Dz];
        r0D[0] = r0Dx;
        r0D[1] = r0Dy;
        r0D[2] = r0Dz;
        // 'EvalBSpline:12' r1D = [r1Dx; r1Dy; r1Dz];
        // 'EvalBSpline:13' r2D = [r2Dx; r2Dy; r2Dz];
        // 'EvalBSpline:14' r3D = [r3Dx; r3Dy; r3Dz];
        //  else
        //      Spline=ctx.q_splines.get(CurvStruct.sp_index);
        //      sp = Spline.sp;
        //      r0D = spval(sp, uvec);
        //
        //      sp1D = fnder(sp, 1);
        //      r1D = spval(sp1D, uvec);
        //
        //      sp2D = fnder(sp, 2);
        //      r2D = spval(sp2D, uvec);
        //
        //      sp3D = fnder(sp, 3);
        //      r3D = spval(sp3D, uvec);
        //  end
        break;
    default:
        // 'EvalCurvStruct:41' otherwise
        // 'EvalCurvStruct:42' c_assert(false, 'Unknown Curve Type for Eval.\n');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStruct:45' r1D = a.*r1D;
    // 'EvalCurvStruct:46' r2D = a^2.*r2D;
    // 'EvalCurvStruct:47' r3D = a^3.*r3D;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3])
{
    CurvStruct expl_temp;
    double r1D[3];
    double r2D[3];
    double r3D[3];
    double b_xdddk;
    double b_xddk;
    double b_xdk;
    double c_xdddk;
    double c_xddk;
    double c_xdk;
    double r0Dx;
    double r0Dy;
    double r0Dz;
    double u_vec_tilda;
    double xdddk;
    double xddk;
    double xdk;
    char message[30];
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:4' if any(u_vec - 1.0 > 10*eps)
    // 'EvalCurvStruct:13' if any(u_vec < 0.0)
    //
    // 'EvalCurvStruct:19' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStruct:21' N = numel(u_vec);
    // 'EvalCurvStruct:22' r0D = zeros(3, N);
    r0D[0] = 0.0;
    r0D[1] = 0.0;
    r0D[2] = 0.0;
    // 'EvalCurvStruct:23' r1D = zeros(3, N);
    // 'EvalCurvStruct:24' r2D = zeros(3, N);
    // 'EvalCurvStruct:25' r3D = zeros(3, N);
    // 'EvalCurvStruct:27' a=CurvStruct.a_param;
    // 'EvalCurvStruct:28' b=CurvStruct.b_param;
    // 'EvalCurvStruct:30' u_vec_tilda = a*u_vec+b;
    u_vec_tilda = CurvStruct_a_param + CurvStruct_b_param;
    // 'EvalCurvStruct:32' switch Type
    switch (CurvStruct_Type) {
    case CurveType_Line:
        // 'EvalCurvStruct:33' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStruct:34' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        // 'EvalCurvStruct:35' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStruct:36' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        // 'EvalCurvStruct:37' case CurveType.TransP5
        //  polynomial transition
        // 'EvalCurvStruct:38' [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        // 'EvalCurvStruct:39' case CurveType.Spline
        //  BSpline
        // 'EvalCurvStruct:40' [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
        //  if coder.target('rtw') || coder.target('mex')
        // 'EvalBSpline:4' Spline=ctx.q_splines.get(CurvStruct.sp_index);
        ctx_q_splines->get(CurvStruct_sp_index, &expl_temp);
        // 'EvalBSpline:5' sp = Spline.sp;
        // 'EvalBSpline:6' Bl = sp.Bl;
        // 'EvalBSpline:7' [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dx = u_vec_tilda;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, &r0Dx, &xdk, &xddk, &xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:8' [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dy = u_vec_tilda;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, &r0Dy, &b_xdk, &b_xddk, &b_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:9' [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dz = u_vec_tilda;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, &r0Dz, &c_xdk, &c_xddk, &c_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:11' r0D = [r0Dx; r0Dy; r0Dz];
        r0D[0] = r0Dx;
        r0D[1] = r0Dy;
        r0D[2] = r0Dz;
        // 'EvalBSpline:12' r1D = [r1Dx; r1Dy; r1Dz];
        // 'EvalBSpline:13' r2D = [r2Dx; r2Dy; r2Dz];
        // 'EvalBSpline:14' r3D = [r3Dx; r3Dy; r3Dz];
        //  else
        //      Spline=ctx.q_splines.get(CurvStruct.sp_index);
        //      sp = Spline.sp;
        //      r0D = spval(sp, uvec);
        //
        //      sp1D = fnder(sp, 1);
        //      r1D = spval(sp1D, uvec);
        //
        //      sp2D = fnder(sp, 2);
        //      r2D = spval(sp2D, uvec);
        //
        //      sp3D = fnder(sp, 3);
        //      r3D = spval(sp3D, uvec);
        //  end
        break;
    default:
        // 'EvalCurvStruct:41' otherwise
        // 'EvalCurvStruct:42' c_assert(false, 'Unknown Curve Type for Eval.\n');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStruct:45' r1D = a.*r1D;
    // 'EvalCurvStruct:46' r2D = a^2.*r2D;
    // 'EvalCurvStruct:47' r3D = a^3.*r3D;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
//                double r3D[3]
// Return Type  : void
//
void b_EvalCurvStruct(CurveType CurvStruct_Type, const double CurvStruct_P0[3],
                      const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3], double r2D[3], double r3D[3])
{
    double b_c;
    double c;
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:4' if any(u_vec - 1.0 > 10*eps)
    // 'EvalCurvStruct:13' if any(u_vec < 0.0)
    //
    // 'EvalCurvStruct:19' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStruct:21' N = numel(u_vec);
    // 'EvalCurvStruct:22' r0D = zeros(3, N);
    // 'EvalCurvStruct:23' r1D = zeros(3, N);
    // 'EvalCurvStruct:24' r2D = zeros(3, N);
    // 'EvalCurvStruct:25' r3D = zeros(3, N);
    // 'EvalCurvStruct:27' a=CurvStruct.a_param;
    // 'EvalCurvStruct:28' b=CurvStruct.b_param;
    // 'EvalCurvStruct:30' u_vec_tilda = a*u_vec+b;
    // 'EvalCurvStruct:32' switch Type
    if (CurvStruct_Type == CurveType_Line) {
        // 'EvalCurvStruct:33' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStruct:34' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(CurvStruct_P0, CurvStruct_P1, CurvStruct_b_param, r0D, r1D, r2D, r3D);
    } else {
        // 'EvalCurvStruct:35' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStruct:36' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
    }
    // 'EvalCurvStruct:45' r1D = a.*r1D;
    // 'EvalCurvStruct:46' r2D = a^2.*r2D;
    c = CurvStruct_a_param * CurvStruct_a_param;
    // 'EvalCurvStruct:47' r3D = a^3.*r3D;
    b_c = std::pow(CurvStruct_a_param, 3.0);
    r1D[0] *= CurvStruct_a_param;
    r2D[0] *= c;
    r3D[0] *= b_c;
    r1D[1] *= CurvStruct_a_param;
    r2D[1] *= c;
    r3D[1] *= b_c;
    r1D[2] *= CurvStruct_a_param;
    r2D[2] *= c;
    r3D[2] *= b_c;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                      ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D)
{
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<bool, 2U> x;
    double c;
    int b_k;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int k;
    int loop_ub;
    char message[30];
    bool b_y;
    bool exitg1;
    bool y;
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:4' if any(u_vec - 1.0 > 10*eps)
    x.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        x[i] = (u_vec[i] - 1.0 > 2.2204460492503131E-15);
    }
    y = false;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(1) - 1)) {
        if (x[k]) {
            y = true;
            exitg1 = true;
        } else {
            k++;
        }
    }
    if (y) {
        int end;
        // 'EvalCurvStruct:5' if coder.target('matlab')
        // 'EvalCurvStruct:7' else
        // 'EvalCurvStruct:8' fprintf('EvalCurvStruct: u_vec > 1\n');
        printf("EvalCurvStruct: u_vec > 1\n");
        fflush(stdout);
        // 'EvalCurvStruct:10' u_vec(u_vec > 1.0) = 1.0;
        end = u_vec.size(1);
        for (int b_i{0}; b_i < end; b_i++) {
            if (u_vec[b_i] > 1.0) {
                u_vec[b_i] = 1.0;
            }
        }
    }
    // 'EvalCurvStruct:13' if any(u_vec < 0.0)
    x.set_size(1, u_vec.size(1));
    b_loop_ub = u_vec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        x[i1] = (u_vec[i1] < 0.0);
    }
    b_y = false;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k <= x.size(1) - 1)) {
        if (x[b_k]) {
            b_y = true;
            exitg1 = true;
        } else {
            b_k++;
        }
    }
    if (b_y) {
        int b_end;
        // 'EvalCurvStruct:14' fprintf('EvalCurvStruct: u_vec < 0\n');
        printf("EvalCurvStruct: u_vec < 0\n");
        fflush(stdout);
        // 'EvalCurvStruct:15' u_vec(u_vec < 0.0) = 0.0;
        b_end = u_vec.size(1);
        for (int c_i{0}; c_i < b_end; c_i++) {
            if (u_vec[c_i] < 0.0) {
                u_vec[c_i] = 0.0;
            }
        }
    }
    //
    // 'EvalCurvStruct:19' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStruct:21' N = numel(u_vec);
    // 'EvalCurvStruct:22' r0D = zeros(3, N);
    r0D.set_size(3, u_vec.size(1));
    c_loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        r0D[3 * i2] = 0.0;
        r0D[3 * i2 + 1] = 0.0;
        r0D[3 * i2 + 2] = 0.0;
    }
    // 'EvalCurvStruct:23' r1D = zeros(3, N);
    r1D.set_size(3, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        r1D[3 * i3] = 0.0;
        r1D[3 * i3 + 1] = 0.0;
        r1D[3 * i3 + 2] = 0.0;
    }
    // 'EvalCurvStruct:24' r2D = zeros(3, N);
    r2D.set_size(3, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        r2D[3 * i4] = 0.0;
        r2D[3 * i4 + 1] = 0.0;
        r2D[3 * i4 + 2] = 0.0;
    }
    // 'EvalCurvStruct:25' r3D = zeros(3, N);
    // 'EvalCurvStruct:27' a=CurvStruct.a_param;
    // 'EvalCurvStruct:28' b=CurvStruct.b_param;
    // 'EvalCurvStruct:30' u_vec_tilda = a*u_vec+b;
    u_vec_tilda.set_size(1, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    for (int i5{0}; i5 < f_loop_ub; i5++) {
        u_vec_tilda[i5] = CurvStruct_a_param * u_vec[i5] + CurvStruct_b_param;
    }
    // 'EvalCurvStruct:32' switch Type
    switch (CurvStruct_Type) {
    case CurveType_Line:
        // 'EvalCurvStruct:33' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStruct:34' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        // 'EvalCurvStruct:35' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStruct:36' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        // 'EvalCurvStruct:37' case CurveType.TransP5
        //  polynomial transition
        // 'EvalCurvStruct:38' [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        // 'EvalCurvStruct:39' case CurveType.Spline
        //  BSpline
        // 'EvalCurvStruct:40' [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
        EvalBSpline(ctx_q_splines, CurvStruct_sp_index, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        // 'EvalCurvStruct:41' otherwise
        // 'EvalCurvStruct:42' c_assert(false, 'Unknown Curve Type for Eval.\n');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i6{0}; i6 < 30; i6++) {
            message[i6] = cv[i6];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStruct:45' r1D = a.*r1D;
    r1D.set_size(3, r1D.size(1));
    g_loop_ub = r1D.size(1);
    for (int i7{0}; i7 < g_loop_ub; i7++) {
        r1D[3 * i7] = CurvStruct_a_param * r1D[3 * i7];
        r1D[3 * i7 + 1] = CurvStruct_a_param * r1D[3 * i7 + 1];
        r1D[3 * i7 + 2] = CurvStruct_a_param * r1D[3 * i7 + 2];
    }
    // 'EvalCurvStruct:46' r2D = a^2.*r2D;
    c = CurvStruct_a_param * CurvStruct_a_param;
    r2D.set_size(3, r2D.size(1));
    h_loop_ub = r2D.size(1);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        r2D[3 * i8] = c * r2D[3 * i8];
        r2D[3 * i8 + 1] = c * r2D[3 * i8 + 1];
        r2D[3 * i8 + 2] = c * r2D[3 * i8 + 2];
    }
    // 'EvalCurvStruct:47' r3D = a^3.*r3D;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
//                double r1D[3]
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3])
{
    CurvStruct expl_temp;
    double r2D[3];
    double r3D[3];
    double b_xdddk;
    double b_xddk;
    double c_xdddk;
    double c_xddk;
    double r0Dx;
    double r0Dy;
    double r0Dz;
    double r1Dx;
    double r1Dy;
    double r1Dz;
    double u_vec_tilda;
    double xdddk;
    double xddk;
    char message[30];
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:4' if any(u_vec - 1.0 > 10*eps)
    // 'EvalCurvStruct:13' if any(u_vec < 0.0)
    //
    // 'EvalCurvStruct:19' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStruct:21' N = numel(u_vec);
    // 'EvalCurvStruct:22' r0D = zeros(3, N);
    // 'EvalCurvStruct:23' r1D = zeros(3, N);
    r0D[0] = 0.0;
    r1D[0] = 0.0;
    r0D[1] = 0.0;
    r1D[1] = 0.0;
    r0D[2] = 0.0;
    r1D[2] = 0.0;
    // 'EvalCurvStruct:24' r2D = zeros(3, N);
    // 'EvalCurvStruct:25' r3D = zeros(3, N);
    // 'EvalCurvStruct:27' a=CurvStruct.a_param;
    // 'EvalCurvStruct:28' b=CurvStruct.b_param;
    // 'EvalCurvStruct:30' u_vec_tilda = a*u_vec+b;
    u_vec_tilda = CurvStruct_a_param + CurvStruct_b_param;
    // 'EvalCurvStruct:32' switch Type
    switch (CurvStruct_Type) {
    case CurveType_Line:
        // 'EvalCurvStruct:33' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStruct:34' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        // 'EvalCurvStruct:35' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStruct:36' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        // 'EvalCurvStruct:37' case CurveType.TransP5
        //  polynomial transition
        // 'EvalCurvStruct:38' [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        // 'EvalCurvStruct:39' case CurveType.Spline
        //  BSpline
        // 'EvalCurvStruct:40' [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
        //  if coder.target('rtw') || coder.target('mex')
        // 'EvalBSpline:4' Spline=ctx.q_splines.get(CurvStruct.sp_index);
        ctx_q_splines->get(CurvStruct_sp_index, &expl_temp);
        // 'EvalBSpline:5' sp = Spline.sp;
        // 'EvalBSpline:6' Bl = sp.Bl;
        // 'EvalBSpline:7' [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dx = u_vec_tilda;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, &r0Dx, &r1Dx, &xddk, &xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:8' [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dy = u_vec_tilda;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, &r0Dy, &r1Dy, &b_xddk, &b_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:9' [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dz = u_vec_tilda;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, &r0Dz, &r1Dz, &c_xddk, &c_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:11' r0D = [r0Dx; r0Dy; r0Dz];
        r0D[0] = r0Dx;
        r0D[1] = r0Dy;
        r0D[2] = r0Dz;
        // 'EvalBSpline:12' r1D = [r1Dx; r1Dy; r1Dz];
        r1D[0] = r1Dx;
        r1D[1] = r1Dy;
        r1D[2] = r1Dz;
        // 'EvalBSpline:13' r2D = [r2Dx; r2Dy; r2Dz];
        // 'EvalBSpline:14' r3D = [r3Dx; r3Dy; r3Dz];
        //  else
        //      Spline=ctx.q_splines.get(CurvStruct.sp_index);
        //      sp = Spline.sp;
        //      r0D = spval(sp, uvec);
        //
        //      sp1D = fnder(sp, 1);
        //      r1D = spval(sp1D, uvec);
        //
        //      sp2D = fnder(sp, 2);
        //      r2D = spval(sp2D, uvec);
        //
        //      sp3D = fnder(sp, 3);
        //      r3D = spval(sp3D, uvec);
        //  end
        break;
    default:
        // 'EvalCurvStruct:41' otherwise
        // 'EvalCurvStruct:42' c_assert(false, 'Unknown Curve Type for Eval.\n');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStruct:45' r1D = a.*r1D;
    r1D[0] *= CurvStruct_a_param;
    r1D[1] *= CurvStruct_a_param;
    r1D[2] *= CurvStruct_a_param;
    // 'EvalCurvStruct:46' r2D = a^2.*r2D;
    // 'EvalCurvStruct:47' r3D = a^3.*r3D;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                const CurvStruct *b_CurvStruct
//                ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, const CurvStruct *b_CurvStruct,
                      ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                      ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                      ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<bool, 2U> x;
    double b_c;
    double c;
    int b_k;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i_loop_ub;
    int j_loop_ub;
    int k;
    int loop_ub;
    char message[30];
    bool b_y;
    bool exitg1;
    bool y;
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:4' if any(u_vec - 1.0 > 10*eps)
    x.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        x[i] = (u_vec[i] - 1.0 > 2.2204460492503131E-15);
    }
    y = false;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(1) - 1)) {
        if (x[k]) {
            y = true;
            exitg1 = true;
        } else {
            k++;
        }
    }
    if (y) {
        int end;
        // 'EvalCurvStruct:5' if coder.target('matlab')
        // 'EvalCurvStruct:7' else
        // 'EvalCurvStruct:8' fprintf('EvalCurvStruct: u_vec > 1\n');
        printf("EvalCurvStruct: u_vec > 1\n");
        fflush(stdout);
        // 'EvalCurvStruct:10' u_vec(u_vec > 1.0) = 1.0;
        end = u_vec.size(1);
        for (int b_i{0}; b_i < end; b_i++) {
            if (u_vec[b_i] > 1.0) {
                u_vec[b_i] = 1.0;
            }
        }
    }
    // 'EvalCurvStruct:13' if any(u_vec < 0.0)
    x.set_size(1, u_vec.size(1));
    b_loop_ub = u_vec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        x[i1] = (u_vec[i1] < 0.0);
    }
    b_y = false;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k <= x.size(1) - 1)) {
        if (x[b_k]) {
            b_y = true;
            exitg1 = true;
        } else {
            b_k++;
        }
    }
    if (b_y) {
        int b_end;
        // 'EvalCurvStruct:14' fprintf('EvalCurvStruct: u_vec < 0\n');
        printf("EvalCurvStruct: u_vec < 0\n");
        fflush(stdout);
        // 'EvalCurvStruct:15' u_vec(u_vec < 0.0) = 0.0;
        b_end = u_vec.size(1);
        for (int c_i{0}; c_i < b_end; c_i++) {
            if (u_vec[c_i] < 0.0) {
                u_vec[c_i] = 0.0;
            }
        }
    }
    //
    // 'EvalCurvStruct:19' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStruct:21' N = numel(u_vec);
    // 'EvalCurvStruct:22' r0D = zeros(3, N);
    r0D.set_size(3, u_vec.size(1));
    c_loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        r0D[3 * i2] = 0.0;
        r0D[3 * i2 + 1] = 0.0;
        r0D[3 * i2 + 2] = 0.0;
    }
    // 'EvalCurvStruct:23' r1D = zeros(3, N);
    r1D.set_size(3, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        r1D[3 * i3] = 0.0;
        r1D[3 * i3 + 1] = 0.0;
        r1D[3 * i3 + 2] = 0.0;
    }
    // 'EvalCurvStruct:24' r2D = zeros(3, N);
    r2D.set_size(3, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        r2D[3 * i4] = 0.0;
        r2D[3 * i4 + 1] = 0.0;
        r2D[3 * i4 + 2] = 0.0;
    }
    // 'EvalCurvStruct:25' r3D = zeros(3, N);
    r3D.set_size(3, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    for (int i5{0}; i5 < f_loop_ub; i5++) {
        r3D[3 * i5] = 0.0;
        r3D[3 * i5 + 1] = 0.0;
        r3D[3 * i5 + 2] = 0.0;
    }
    // 'EvalCurvStruct:27' a=CurvStruct.a_param;
    // 'EvalCurvStruct:28' b=CurvStruct.b_param;
    // 'EvalCurvStruct:30' u_vec_tilda = a*u_vec+b;
    u_vec_tilda.set_size(1, u_vec.size(1));
    g_loop_ub = u_vec.size(1);
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        u_vec_tilda[i6] = b_CurvStruct->a_param * u_vec[i6] + b_CurvStruct->b_param;
    }
    // 'EvalCurvStruct:32' switch Type
    switch (b_CurvStruct->Type) {
    case CurveType_Line:
        // 'EvalCurvStruct:33' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStruct:34' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(b_CurvStruct->P0, b_CurvStruct->P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        // 'EvalCurvStruct:35' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStruct:36' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(b_CurvStruct->P0, b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                  b_CurvStruct->theta, b_CurvStruct->pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        // 'EvalCurvStruct:37' case CurveType.TransP5
        //  polynomial transition
        // 'EvalCurvStruct:38' [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
        EvalTransP5(b_CurvStruct->CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        // 'EvalCurvStruct:39' case CurveType.Spline
        //  BSpline
        // 'EvalCurvStruct:40' [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
        EvalBSpline(ctx_q_splines, b_CurvStruct->sp_index, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        // 'EvalCurvStruct:41' otherwise
        // 'EvalCurvStruct:42' c_assert(false, 'Unknown Curve Type for Eval.\n');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i7{0}; i7 < 30; i7++) {
            message[i7] = cv[i7];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStruct:45' r1D = a.*r1D;
    r1D.set_size(3, r1D.size(1));
    h_loop_ub = r1D.size(1);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        r1D[3 * i8] = b_CurvStruct->a_param * r1D[3 * i8];
        r1D[3 * i8 + 1] = b_CurvStruct->a_param * r1D[3 * i8 + 1];
        r1D[3 * i8 + 2] = b_CurvStruct->a_param * r1D[3 * i8 + 2];
    }
    // 'EvalCurvStruct:46' r2D = a^2.*r2D;
    c = b_CurvStruct->a_param * b_CurvStruct->a_param;
    r2D.set_size(3, r2D.size(1));
    i_loop_ub = r2D.size(1);
    for (int i9{0}; i9 < i_loop_ub; i9++) {
        r2D[3 * i9] = c * r2D[3 * i9];
        r2D[3 * i9 + 1] = c * r2D[3 * i9 + 1];
        r2D[3 * i9 + 2] = c * r2D[3 * i9 + 2];
    }
    // 'EvalCurvStruct:47' r3D = a^3.*r3D;
    b_c = std::pow(b_CurvStruct->a_param, 3.0);
    r3D.set_size(3, r3D.size(1));
    j_loop_ub = r3D.size(1);
    for (int i10{0}; i10 < j_loop_ub; i10++) {
        r3D[3 * i10] = b_c * r3D[3 * i10];
        r3D[3 * i10 + 1] = b_c * r3D[3 * i10 + 1];
        r3D[3 * i10 + 2] = b_c * r3D[3 * i10 + 2];
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3], double r2D[3])
{
    CurvStruct expl_temp;
    double r3D[3];
    double b_xdddk;
    double c;
    double c_xdddk;
    double r0Dx;
    double r0Dy;
    double r0Dz;
    double r1Dx;
    double r1Dy;
    double r1Dz;
    double r2Dx;
    double r2Dy;
    double r2Dz;
    double u_vec_tilda;
    double xdddk;
    char message[30];
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:4' if any(u_vec - 1.0 > 10*eps)
    // 'EvalCurvStruct:13' if any(u_vec < 0.0)
    //
    // 'EvalCurvStruct:19' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStruct:21' N = numel(u_vec);
    // 'EvalCurvStruct:22' r0D = zeros(3, N);
    // 'EvalCurvStruct:23' r1D = zeros(3, N);
    // 'EvalCurvStruct:24' r2D = zeros(3, N);
    r0D[0] = 0.0;
    r1D[0] = 0.0;
    r2D[0] = 0.0;
    r0D[1] = 0.0;
    r1D[1] = 0.0;
    r2D[1] = 0.0;
    r0D[2] = 0.0;
    r1D[2] = 0.0;
    r2D[2] = 0.0;
    // 'EvalCurvStruct:25' r3D = zeros(3, N);
    // 'EvalCurvStruct:27' a=CurvStruct.a_param;
    // 'EvalCurvStruct:28' b=CurvStruct.b_param;
    // 'EvalCurvStruct:30' u_vec_tilda = a*u_vec+b;
    u_vec_tilda = CurvStruct_a_param + CurvStruct_b_param;
    // 'EvalCurvStruct:32' switch Type
    switch (CurvStruct_Type) {
    case CurveType_Line:
        // 'EvalCurvStruct:33' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStruct:34' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        // 'EvalCurvStruct:35' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStruct:36' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        // 'EvalCurvStruct:37' case CurveType.TransP5
        //  polynomial transition
        // 'EvalCurvStruct:38' [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        // 'EvalCurvStruct:39' case CurveType.Spline
        //  BSpline
        // 'EvalCurvStruct:40' [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
        //  if coder.target('rtw') || coder.target('mex')
        // 'EvalBSpline:4' Spline=ctx.q_splines.get(CurvStruct.sp_index);
        ctx_q_splines->get(CurvStruct_sp_index, &expl_temp);
        // 'EvalBSpline:5' sp = Spline.sp;
        // 'EvalBSpline:6' Bl = sp.Bl;
        // 'EvalBSpline:7' [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dx = u_vec_tilda;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, &r0Dx, &r1Dx, &r2Dx, &xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:8' [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dy = u_vec_tilda;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, &r0Dy, &r1Dy, &r2Dy, &b_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:9' [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dz = u_vec_tilda;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, &r0Dz, &r1Dz, &r2Dz, &c_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:11' r0D = [r0Dx; r0Dy; r0Dz];
        r0D[0] = r0Dx;
        r0D[1] = r0Dy;
        r0D[2] = r0Dz;
        // 'EvalBSpline:12' r1D = [r1Dx; r1Dy; r1Dz];
        r1D[0] = r1Dx;
        r1D[1] = r1Dy;
        r1D[2] = r1Dz;
        // 'EvalBSpline:13' r2D = [r2Dx; r2Dy; r2Dz];
        r2D[0] = r2Dx;
        r2D[1] = r2Dy;
        r2D[2] = r2Dz;
        // 'EvalBSpline:14' r3D = [r3Dx; r3Dy; r3Dz];
        //  else
        //      Spline=ctx.q_splines.get(CurvStruct.sp_index);
        //      sp = Spline.sp;
        //      r0D = spval(sp, uvec);
        //
        //      sp1D = fnder(sp, 1);
        //      r1D = spval(sp1D, uvec);
        //
        //      sp2D = fnder(sp, 2);
        //      r2D = spval(sp2D, uvec);
        //
        //      sp3D = fnder(sp, 3);
        //      r3D = spval(sp3D, uvec);
        //  end
        break;
    default:
        // 'EvalCurvStruct:41' otherwise
        // 'EvalCurvStruct:42' c_assert(false, 'Unknown Curve Type for Eval.\n');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStruct:45' r1D = a.*r1D;
    // 'EvalCurvStruct:46' r2D = a^2.*r2D;
    c = CurvStruct_a_param * CurvStruct_a_param;
    r1D[0] *= CurvStruct_a_param;
    r2D[0] *= c;
    r1D[1] *= CurvStruct_a_param;
    r2D[1] *= c;
    r1D[2] *= CurvStruct_a_param;
    r2D[2] *= c;
    // 'EvalCurvStruct:47' r3D = a^3.*r3D;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
// Return Type  : void
//
void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3], double r2D[3])
{
    CurvStruct expl_temp;
    double r3D[3];
    double b_xdddk;
    double c;
    double c_xdddk;
    double r0Dx;
    double r0Dy;
    double r0Dz;
    double r1Dx;
    double r1Dy;
    double r1Dz;
    double r2Dx;
    double r2Dy;
    double r2Dz;
    double xdddk;
    char message[30];
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:4' if any(u_vec - 1.0 > 10*eps)
    // 'EvalCurvStruct:13' if any(u_vec < 0.0)
    //
    // 'EvalCurvStruct:19' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStruct:21' N = numel(u_vec);
    // 'EvalCurvStruct:22' r0D = zeros(3, N);
    // 'EvalCurvStruct:23' r1D = zeros(3, N);
    // 'EvalCurvStruct:24' r2D = zeros(3, N);
    r0D[0] = 0.0;
    r1D[0] = 0.0;
    r2D[0] = 0.0;
    r0D[1] = 0.0;
    r1D[1] = 0.0;
    r2D[1] = 0.0;
    r0D[2] = 0.0;
    r1D[2] = 0.0;
    r2D[2] = 0.0;
    // 'EvalCurvStruct:25' r3D = zeros(3, N);
    // 'EvalCurvStruct:27' a=CurvStruct.a_param;
    // 'EvalCurvStruct:28' b=CurvStruct.b_param;
    // 'EvalCurvStruct:30' u_vec_tilda = a*u_vec+b;
    // 'EvalCurvStruct:32' switch Type
    switch (CurvStruct_Type) {
    case CurveType_Line:
        // 'EvalCurvStruct:33' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStruct:34' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(CurvStruct_P0, CurvStruct_P1, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        // 'EvalCurvStruct:35' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStruct:36' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        // 'EvalCurvStruct:37' case CurveType.TransP5
        //  polynomial transition
        // 'EvalCurvStruct:38' [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
        EvalTransP5(CurvStruct_CoeffP5, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        // 'EvalCurvStruct:39' case CurveType.Spline
        //  BSpline
        // 'EvalCurvStruct:40' [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
        //  if coder.target('rtw') || coder.target('mex')
        // 'EvalBSpline:4' Spline=ctx.q_splines.get(CurvStruct.sp_index);
        ctx_q_splines->get(CurvStruct_sp_index, &expl_temp);
        // 'EvalBSpline:5' sp = Spline.sp;
        // 'EvalBSpline:6' Bl = sp.Bl;
        // 'EvalBSpline:7' [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dx = CurvStruct_b_param;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, &r0Dx, &r1Dx, &r2Dx, &xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:8' [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dy = CurvStruct_b_param;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, &r0Dy, &r1Dy, &r2Dy, &b_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:9' [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dz = CurvStruct_b_param;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, &r0Dz, &r1Dz, &r2Dz, &c_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:11' r0D = [r0Dx; r0Dy; r0Dz];
        r0D[0] = r0Dx;
        r0D[1] = r0Dy;
        r0D[2] = r0Dz;
        // 'EvalBSpline:12' r1D = [r1Dx; r1Dy; r1Dz];
        r1D[0] = r1Dx;
        r1D[1] = r1Dy;
        r1D[2] = r1Dz;
        // 'EvalBSpline:13' r2D = [r2Dx; r2Dy; r2Dz];
        r2D[0] = r2Dx;
        r2D[1] = r2Dy;
        r2D[2] = r2Dz;
        // 'EvalBSpline:14' r3D = [r3Dx; r3Dy; r3Dz];
        //  else
        //      Spline=ctx.q_splines.get(CurvStruct.sp_index);
        //      sp = Spline.sp;
        //      r0D = spval(sp, uvec);
        //
        //      sp1D = fnder(sp, 1);
        //      r1D = spval(sp1D, uvec);
        //
        //      sp2D = fnder(sp, 2);
        //      r2D = spval(sp2D, uvec);
        //
        //      sp3D = fnder(sp, 3);
        //      r3D = spval(sp3D, uvec);
        //  end
        break;
    default:
        // 'EvalCurvStruct:41' otherwise
        // 'EvalCurvStruct:42' c_assert(false, 'Unknown Curve Type for Eval.\n');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStruct:45' r1D = a.*r1D;
    // 'EvalCurvStruct:46' r2D = a^2.*r2D;
    c = CurvStruct_a_param * CurvStruct_a_param;
    r1D[0] *= CurvStruct_a_param;
    r2D[0] *= c;
    r1D[1] *= CurvStruct_a_param;
    r2D[1] *= c;
    r1D[2] *= CurvStruct_a_param;
    r2D[2] *= c;
    // 'EvalCurvStruct:47' r3D = a^3.*r3D;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStruct, u_vec)
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
//                double r3D[3]
// Return Type  : void
//
void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3], double r2D[3], double r3D[3])
{
    CurvStruct expl_temp;
    double b_c;
    double c;
    double r0Dx;
    double r0Dy;
    double r0Dz;
    double r1Dx;
    double r1Dy;
    double r1Dz;
    double r2Dx;
    double r2Dy;
    double r2Dz;
    double r3Dx;
    double r3Dy;
    double r3Dz;
    double u_vec_tilda;
    char message[30];
    // 'EvalCurvStruct:3' coder.inline("never");
    // 'EvalCurvStruct:4' if any(u_vec - 1.0 > 10*eps)
    // 'EvalCurvStruct:13' if any(u_vec < 0.0)
    //
    // 'EvalCurvStruct:19' Type  = CurvStruct.Type;
    //
    // 'EvalCurvStruct:21' N = numel(u_vec);
    // 'EvalCurvStruct:22' r0D = zeros(3, N);
    // 'EvalCurvStruct:23' r1D = zeros(3, N);
    // 'EvalCurvStruct:24' r2D = zeros(3, N);
    // 'EvalCurvStruct:25' r3D = zeros(3, N);
    r0D[0] = 0.0;
    r1D[0] = 0.0;
    r2D[0] = 0.0;
    r3D[0] = 0.0;
    r0D[1] = 0.0;
    r1D[1] = 0.0;
    r2D[1] = 0.0;
    r3D[1] = 0.0;
    r0D[2] = 0.0;
    r1D[2] = 0.0;
    r2D[2] = 0.0;
    r3D[2] = 0.0;
    // 'EvalCurvStruct:27' a=CurvStruct.a_param;
    // 'EvalCurvStruct:28' b=CurvStruct.b_param;
    // 'EvalCurvStruct:30' u_vec_tilda = a*u_vec+b;
    u_vec_tilda = CurvStruct_a_param + CurvStruct_b_param;
    // 'EvalCurvStruct:32' switch Type
    switch (CurvStruct_Type) {
    case CurveType_Line:
        // 'EvalCurvStruct:33' case CurveType.Line
        //  line (G01)
        // 'EvalCurvStruct:34' [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec_tilda);
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        // 'EvalCurvStruct:35' case CurveType.Helix
        //  arc of circle / helix (G02, G03)
        // 'EvalCurvStruct:36' [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec_tilda);
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        // 'EvalCurvStruct:37' case CurveType.TransP5
        //  polynomial transition
        // 'EvalCurvStruct:38' [r0D, r1D, r2D, r3D] = EvalTransP5(CurvStruct, u_vec_tilda);
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        // 'EvalCurvStruct:39' case CurveType.Spline
        //  BSpline
        // 'EvalCurvStruct:40' [r0D, r1D, r2D, r3D] = EvalBSpline(ctx, CurvStruct, u_vec_tilda);
        //  if coder.target('rtw') || coder.target('mex')
        // 'EvalBSpline:4' Spline=ctx.q_splines.get(CurvStruct.sp_index);
        ctx_q_splines->get(CurvStruct_sp_index, &expl_temp);
        // 'EvalBSpline:5' sp = Spline.sp;
        // 'EvalBSpline:6' Bl = sp.Bl;
        // 'EvalBSpline:7' [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dx = u_vec_tilda;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, &r0Dx, &r1Dx, &r2Dx, &r3Dx);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:8' [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dy = u_vec_tilda;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, &r0Dy, &r1Dy, &r2Dy, &r3Dy);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:9' [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
        // 'bspline_eval_vec:3' x = zeros(size(u));
        // 'bspline_eval_vec:4' xd = zeros(size(u));
        // 'bspline_eval_vec:5' xdd = zeros(size(u));
        // 'bspline_eval_vec:6' xddd = zeros(size(u));
        // 'bspline_eval_vec:8' for k = 1:length(u)
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dz = u_vec_tilda;
        bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, &r0Dz, &r1Dz, &r2Dz, &r3Dz);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
        // 'EvalBSpline:11' r0D = [r0Dx; r0Dy; r0Dz];
        r0D[0] = r0Dx;
        r0D[1] = r0Dy;
        r0D[2] = r0Dz;
        // 'EvalBSpline:12' r1D = [r1Dx; r1Dy; r1Dz];
        r1D[0] = r1Dx;
        r1D[1] = r1Dy;
        r1D[2] = r1Dz;
        // 'EvalBSpline:13' r2D = [r2Dx; r2Dy; r2Dz];
        r2D[0] = r2Dx;
        r2D[1] = r2Dy;
        r2D[2] = r2Dz;
        // 'EvalBSpline:14' r3D = [r3Dx; r3Dy; r3Dz];
        r3D[0] = r3Dx;
        r3D[1] = r3Dy;
        r3D[2] = r3Dz;
        //  else
        //      Spline=ctx.q_splines.get(CurvStruct.sp_index);
        //      sp = Spline.sp;
        //      r0D = spval(sp, uvec);
        //
        //      sp1D = fnder(sp, 1);
        //      r1D = spval(sp1D, uvec);
        //
        //      sp2D = fnder(sp, 2);
        //      r2D = spval(sp2D, uvec);
        //
        //      sp3D = fnder(sp, 3);
        //      r3D = spval(sp3D, uvec);
        //  end
        break;
    default:
        // 'EvalCurvStruct:41' otherwise
        // 'EvalCurvStruct:42' c_assert(false, 'Unknown Curve Type for Eval.\n');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStruct:45' r1D = a.*r1D;
    // 'EvalCurvStruct:46' r2D = a^2.*r2D;
    c = CurvStruct_a_param * CurvStruct_a_param;
    // 'EvalCurvStruct:47' r3D = a^3.*r3D;
    b_c = std::pow(CurvStruct_a_param, 3.0);
    r1D[0] *= CurvStruct_a_param;
    r2D[0] *= c;
    r3D[0] *= b_c;
    r1D[1] *= CurvStruct_a_param;
    r2D[1] *= c;
    r3D[1] *= b_c;
    r1D[2] *= CurvStruct_a_param;
    r2D[2] *= c;
    r3D[2] *= b_c;
}

} // namespace ocn

//
// File trailer for EvalCurvStruct.cpp
//
// [EOF]
//
