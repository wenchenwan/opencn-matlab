//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalBSplineNoCtx.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

// Include Files
#include "EvalBSplineNoCtx.h"
#include "bspline_eval.h"
#include "bspline_eval_vec.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ
//                unsigned long CurvSpline_sp_Bl_handle
//                double uvec
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
//                double r3D[3]
// Return Type  : void
//
namespace ocn {
void EvalBSplineNoCtx(const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ,
                      unsigned long CurvSpline_sp_Bl_handle, double uvec, double r0D[3],
                      double r1D[3], double r2D[3], double r3D[3])
{
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
    ZoneScopedN("EvalBSpline");
    r0Dx = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffX, &r0Dx, &r1Dx, &r2Dx, &r3Dx);
    r0Dy = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffY, &r0Dy, &r1Dy, &r2Dy, &r3Dy);
    r0Dz = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffZ, &r0Dz, &r1Dz, &r2Dz, &r3Dz);
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
}

//
// Arguments    : const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ
//                unsigned long CurvSpline_sp_Bl_handle
//                const ::coder::array<double, 2U> &uvec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
// Return Type  : void
//
void EvalBSplineNoCtx(const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ,
                      unsigned long CurvSpline_sp_Bl_handle, const ::coder::array<double, 2U> &uvec,
                      ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D)
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
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int loop_ub;
    ZoneScopedN("EvalBSpline");
    bspline_eval_vec(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffX, uvec, r0Dx, r1Dx, r2Dx, r3Dx);
    bspline_eval_vec(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffY, uvec, r0Dy, r1Dy, r2Dy, r3Dy);
    bspline_eval_vec(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffZ, uvec, r0Dz, r1Dz, r2Dz, r3Dz);
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
}

//
// Arguments    : const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ
//                unsigned long CurvSpline_sp_Bl_handle
//                double uvec
//                double r0D[3]
//                double r1D[3]
// Return Type  : void
//
void EvalBSplineNoCtx(const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ,
                      unsigned long CurvSpline_sp_Bl_handle, double uvec, double r0D[3],
                      double r1D[3])
{
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
    ZoneScopedN("EvalBSpline");
    r0Dx = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffX, &r0Dx, &r1Dx, &xddk, &xdddk);
    r0Dy = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffY, &r0Dy, &r1Dy, &b_xddk, &b_xdddk);
    r0Dz = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffZ, &r0Dz, &r1Dz, &c_xddk, &c_xdddk);
    r0D[0] = r0Dx;
    r0D[1] = r0Dy;
    r0D[2] = r0Dz;
    r1D[0] = r1Dx;
    r1D[1] = r1Dy;
    r1D[2] = r1Dz;
}

//
// Arguments    : const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ
//                unsigned long CurvSpline_sp_Bl_handle
//                const double uvec[5]
//                double r0D[5][3]
//                double r1D[5][3]
// Return Type  : void
//
void EvalBSplineNoCtx(const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ,
                      unsigned long CurvSpline_sp_Bl_handle, const double uvec[5], double r0D[5][3],
                      double r1D[5][3])
{
    double r0Dx[5];
    double r0Dy[5];
    double r0Dz[5];
    double r1Dx[5];
    double r1Dy[5];
    double r1Dz[5];
    double r2Dx[5];
    double r2Dy[5];
    double r2Dz[5];
    double r3Dx[5];
    double r3Dy[5];
    double r3Dz[5];
    ZoneScopedN("EvalBSpline");
    for (int k{0}; k < 5; k++) {
        r0Dx[k] = uvec[k];
        bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffX, &r0Dx[k], &r1Dx[k], &r2Dx[k],
                     &r3Dx[k]);
    }
    for (int b_k{0}; b_k < 5; b_k++) {
        r0Dy[b_k] = uvec[b_k];
        bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffY, &r0Dy[b_k], &r1Dy[b_k],
                     &r2Dy[b_k], &r3Dy[b_k]);
    }
    for (int c_k{0}; c_k < 5; c_k++) {
        r0Dz[c_k] = uvec[c_k];
        bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffZ, &r0Dz[c_k], &r1Dz[c_k],
                     &r2Dz[c_k], &r3Dz[c_k]);
    }
    for (int i{0}; i < 5; i++) {
        r0D[i][0] = r0Dx[i];
        r0D[i][1] = r0Dy[i];
        r0D[i][2] = r0Dz[i];
        r1D[i][0] = r1Dx[i];
        r1D[i][1] = r1Dy[i];
        r1D[i][2] = r1Dz[i];
    }
}

} // namespace ocn

//
// File trailer for EvalBSplineNoCtx.cpp
//
// [EOF]
//
