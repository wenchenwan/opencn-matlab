//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalBSpline.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
//

// Include Files
#include "EvalBSpline.h"
#include "bspline_eval.h"
#include "bspline_eval_vec.h"
#include "queue_coder.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "sinspace_types3.h"
#include "coder_array.h"

// Function Definitions
//
// if coder.target('rtw') || coder.target('mex')
//
// Arguments    : const queue_coder *ctx_q_splines
//                int CurvStruct_sp_index
//                const double uvec[10]
//                double r0D[10][3]
//                double r1D[10][3]
//                double r2D[10][3]
//                double r3D[10][3]
// Return Type  : void
//
namespace ocn {
void EvalBSpline(const queue_coder *ctx_q_splines, int CurvStruct_sp_index, const double uvec[10],
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
    unsigned long Spline_sp_Bl_handle;
    ctx_q_splines->get(CurvStruct_sp_index, &expl_temp);
    Spline_sp_Bl_handle = expl_temp.sp.Bl.handle;
    for (int k{0}; k < 10; k++) {
        r0Dx[k] = uvec[k];
        bspline_eval(Spline_sp_Bl_handle, expl_temp.sp.CoeffX, &r0Dx[k], &r1Dx[k], &r2Dx[k],
                     &r3Dx[k]);
    }
    for (int b_k{0}; b_k < 10; b_k++) {
        r0Dy[b_k] = uvec[b_k];
        bspline_eval(Spline_sp_Bl_handle, expl_temp.sp.CoeffY, &r0Dy[b_k], &r1Dy[b_k], &r2Dy[b_k],
                     &r3Dy[b_k]);
    }
    for (int c_k{0}; c_k < 10; c_k++) {
        r0Dz[c_k] = uvec[c_k];
        bspline_eval(Spline_sp_Bl_handle, expl_temp.sp.CoeffZ, &r0Dz[c_k], &r1Dz[c_k], &r2Dz[c_k],
                     &r3Dz[c_k]);
    }
    for (int i{0}; i < 10; i++) {
        r0D[i][0] = r0Dx[i];
        r0D[i][1] = r0Dy[i];
        r0D[i][2] = r0Dz[i];
        r1D[i][0] = r1Dx[i];
        r1D[i][1] = r1Dy[i];
        r1D[i][2] = r1Dz[i];
        r2D[i][0] = r2Dx[i];
        r2D[i][1] = r2Dy[i];
        r2D[i][2] = r2Dz[i];
        r3D[i][0] = r3Dx[i];
        r3D[i][1] = r3Dy[i];
        r3D[i][2] = r3Dz[i];
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
}

//
// if coder.target('rtw') || coder.target('mex')
//
// Arguments    : const queue_coder *ctx_q_splines
//                int CurvStruct_sp_index
//                const ::coder::array<double, 2U> &uvec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void EvalBSpline(const queue_coder *ctx_q_splines, int CurvStruct_sp_index,
                 const ::coder::array<double, 2U> &uvec, ::coder::array<double, 2U> &r0D,
                 ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                 ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> r0Dx;
    ::coder::array<double, 2U> r0Dy;
    ::coder::array<double, 2U> r0Dz;
    ::coder::array<double, 2U> r1Dx;
    ::coder::array<double, 2U> r1Dy;
    ::coder::array<double, 2U> r1Dz;
    ::coder::array<double, 2U> r2Dx;
    ::coder::array<double, 2U> r2Dy;
    ::coder::array<double, 2U> r2Dz;
    ::coder::array<double, 2U> r3Dx;
    ::coder::array<double, 2U> r3Dy;
    ::coder::array<double, 2U> r3Dz;
    CurvStruct expl_temp;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i_loop_ub;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    ctx_q_splines->get(CurvStruct_sp_index, &expl_temp);
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, uvec, r0Dx, r1Dx, r2Dx, r3Dx);
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, uvec, r0Dy, r1Dy, r2Dy, r3Dy);
    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, uvec, r0Dz, r1Dz, r2Dz, r3Dz);
    r0D.set_size(3, r0Dx.size(1));
    loop_ub = r0Dx.size(1);
    for (int i{0}; i < loop_ub; i++) {
        r0D[3 * i] = r0Dx[i];
    }
    b_loop_ub = r0Dy.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        r0D[3 * i1 + 1] = r0Dy[i1];
    }
    c_loop_ub = r0Dz.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        r0D[3 * i2 + 2] = r0Dz[i2];
    }
    r1D.set_size(3, r1Dx.size(1));
    d_loop_ub = r1Dx.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        r1D[3 * i3] = r1Dx[i3];
    }
    e_loop_ub = r1Dy.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        r1D[3 * i4 + 1] = r1Dy[i4];
    }
    f_loop_ub = r1Dz.size(1);
    for (int i5{0}; i5 < f_loop_ub; i5++) {
        r1D[3 * i5 + 2] = r1Dz[i5];
    }
    r2D.set_size(3, r2Dx.size(1));
    g_loop_ub = r2Dx.size(1);
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        r2D[3 * i6] = r2Dx[i6];
    }
    h_loop_ub = r2Dy.size(1);
    for (int i7{0}; i7 < h_loop_ub; i7++) {
        r2D[3 * i7 + 1] = r2Dy[i7];
    }
    i_loop_ub = r2Dz.size(1);
    for (int i8{0}; i8 < i_loop_ub; i8++) {
        r2D[3 * i8 + 2] = r2Dz[i8];
    }
    r3D.set_size(3, r3Dx.size(1));
    j_loop_ub = r3Dx.size(1);
    for (int i9{0}; i9 < j_loop_ub; i9++) {
        r3D[3 * i9] = r3Dx[i9];
    }
    k_loop_ub = r3Dy.size(1);
    for (int i10{0}; i10 < k_loop_ub; i10++) {
        r3D[3 * i10 + 1] = r3Dy[i10];
    }
    l_loop_ub = r3Dz.size(1);
    for (int i11{0}; i11 < l_loop_ub; i11++) {
        r3D[3 * i11 + 2] = r3Dz[i11];
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
}

//
// if coder.target('rtw') || coder.target('mex')
//
// Arguments    : const queue_coder *ctx_q_splines
//                int CurvStruct_sp_index
//                double uvec
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
//                double r3D[3]
// Return Type  : void
//
void EvalBSpline(const queue_coder *ctx_q_splines, int CurvStruct_sp_index, double uvec,
                 double r0D[3], double r1D[3], double r2D[3], double r3D[3])
{
    CurvStruct expl_temp;
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
    ctx_q_splines->get(CurvStruct_sp_index, &expl_temp);
    r0Dx = uvec;
    bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, &r0Dx, &r1Dx, &r2Dx, &r3Dx);
    r0Dy = uvec;
    bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, &r0Dy, &r1Dy, &r2Dy, &r3Dy);
    r0Dz = uvec;
    bspline_eval(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, &r0Dz, &r1Dz, &r2Dz, &r3Dz);
    r0D[0] = r0Dx;
    r0D[1] = r0Dy;
    r0D[2] = r0Dz;
    r1D[0] = r1Dx;
    r1D[1] = r1Dy;
    r1D[2] = r1Dz;
    r2D[0] = r2Dx;
    r2D[1] = r2Dy;
    r2D[2] = r2Dz;
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
}

} // namespace ocn

//
// File trailer for EvalBSpline.cpp
//
// [EOF]
//
