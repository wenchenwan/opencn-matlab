//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalBSplineNoCtx.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:51:01
//

// Include Files
#include "EvalBSplineNoCtx.h"
#include "bspline_eval.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"

// Function Definitions
//
// function [r0D, r1D, r2D, r3D] = EvalBSplineNoCtx(CurvSpline, uvec)
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
    // 'EvalBSplineNoCtx:2' coder.inline('never')
    // 'EvalBSplineNoCtx:3' if coder.target('rtw') || coder.target('mex')
    // 'EvalBSplineNoCtx:4' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalBSplineNoCtx:5' coder.ceval('ZoneScopedN', coder.opaque('const char*',
    // '"EvalBSpline"'));
    ZoneScopedN("EvalBSpline");
    // 'EvalBSplineNoCtx:8' Spline=CurvSpline;
    // 'EvalBSplineNoCtx:9' sp = Spline.sp;
    // 'EvalBSplineNoCtx:10' Bl = sp.Bl;
    // 'EvalBSplineNoCtx:11' [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
    // 'bspline_eval_vec:3' x = zeros(size(u));
    // 'bspline_eval_vec:4' xd = zeros(size(u));
    // 'bspline_eval_vec:5' xdd = zeros(size(u));
    // 'bspline_eval_vec:6' xddd = zeros(size(u));
    // 'bspline_eval_vec:8' for k = 1:length(u)
    // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
    r0Dx = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffX, &r0Dx, &r1Dx, &r2Dx, &r3Dx);
    // 'bspline_eval_vec:10' x(k) = xk;
    // 'bspline_eval_vec:11' xd(k) = xdk;
    // 'bspline_eval_vec:12' xdd(k) = xddk;
    // 'bspline_eval_vec:13' xddd(k) = xdddk;
    // 'EvalBSplineNoCtx:12' [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
    // 'bspline_eval_vec:3' x = zeros(size(u));
    // 'bspline_eval_vec:4' xd = zeros(size(u));
    // 'bspline_eval_vec:5' xdd = zeros(size(u));
    // 'bspline_eval_vec:6' xddd = zeros(size(u));
    // 'bspline_eval_vec:8' for k = 1:length(u)
    // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
    r0Dy = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffY, &r0Dy, &r1Dy, &r2Dy, &r3Dy);
    // 'bspline_eval_vec:10' x(k) = xk;
    // 'bspline_eval_vec:11' xd(k) = xdk;
    // 'bspline_eval_vec:12' xdd(k) = xddk;
    // 'bspline_eval_vec:13' xddd(k) = xdddk;
    // 'EvalBSplineNoCtx:13' [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
    // 'bspline_eval_vec:3' x = zeros(size(u));
    // 'bspline_eval_vec:4' xd = zeros(size(u));
    // 'bspline_eval_vec:5' xdd = zeros(size(u));
    // 'bspline_eval_vec:6' xddd = zeros(size(u));
    // 'bspline_eval_vec:8' for k = 1:length(u)
    // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
    r0Dz = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffZ, &r0Dz, &r1Dz, &r2Dz, &r3Dz);
    // 'bspline_eval_vec:10' x(k) = xk;
    // 'bspline_eval_vec:11' xd(k) = xdk;
    // 'bspline_eval_vec:12' xdd(k) = xddk;
    // 'bspline_eval_vec:13' xddd(k) = xdddk;
    // 'EvalBSplineNoCtx:15' r0D = [r0Dx; r0Dy; r0Dz];
    r0D[0] = r0Dx;
    r0D[1] = r0Dy;
    r0D[2] = r0Dz;
    // 'EvalBSplineNoCtx:16' r1D = [r1Dx; r1Dy; r1Dz];
    r1D[0] = r1Dx;
    r1D[1] = r1Dy;
    r1D[2] = r1Dz;
    // 'EvalBSplineNoCtx:17' r2D = [r2Dx; r2Dy; r2Dz];
    r2D[0] = r2Dx;
    r2D[1] = r2Dy;
    r2D[2] = r2Dz;
    // 'EvalBSplineNoCtx:18' r3D = [r3Dx; r3Dy; r3Dz];
    r3D[0] = r3Dx;
    r3D[1] = r3Dy;
    r3D[2] = r3Dz;
}

//
// function [r0D, r1D, r2D, r3D] = EvalBSplineNoCtx(CurvSpline, uvec)
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
    double d;
    double d1;
    double d2;
    double d3;
    double d4;
    double d5;
    double d6;
    double d7;
    double d8;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i14;
    int i4;
    int i9;
    int i_loop_ub;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int n_loop_ub;
    int o_loop_ub;
    int p_loop_ub;
    int q_loop_ub;
    int r_loop_ub;
    // 'EvalBSplineNoCtx:2' coder.inline('never')
    // 'EvalBSplineNoCtx:3' if coder.target('rtw') || coder.target('mex')
    // 'EvalBSplineNoCtx:4' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalBSplineNoCtx:5' coder.ceval('ZoneScopedN', coder.opaque('const char*',
    // '"EvalBSpline"'));
    ZoneScopedN("EvalBSpline");
    // 'EvalBSplineNoCtx:8' Spline=CurvSpline;
    // 'EvalBSplineNoCtx:9' sp = Spline.sp;
    // 'EvalBSplineNoCtx:10' Bl = sp.Bl;
    // 'EvalBSplineNoCtx:11' [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
    // 'bspline_eval_vec:3' x = zeros(size(u));
    r0Dx.set_size(1, uvec.size(1));
    loop_ub = uvec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        r0Dx[i] = 0.0;
    }
    // 'bspline_eval_vec:4' xd = zeros(size(u));
    r1Dx.set_size(1, uvec.size(1));
    b_loop_ub = uvec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        r1Dx[i1] = 0.0;
    }
    // 'bspline_eval_vec:5' xdd = zeros(size(u));
    r2Dx.set_size(1, uvec.size(1));
    c_loop_ub = uvec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        r2Dx[i2] = 0.0;
    }
    // 'bspline_eval_vec:6' xddd = zeros(size(u));
    r3Dx.set_size(1, uvec.size(1));
    d_loop_ub = uvec.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        r3Dx[i3] = 0.0;
    }
    // 'bspline_eval_vec:8' for k = 1:length(u)
    i4 = uvec.size(1);
    for (int k{0}; k < i4; k++) {
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dx[k] = uvec[k];
        bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffX, &r0Dx[k], &d, &d1, &d2);
        r3Dx[k] = d2;
        r2Dx[k] = d1;
        r1Dx[k] = d;
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
    }
    // 'EvalBSplineNoCtx:12' [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
    // 'bspline_eval_vec:3' x = zeros(size(u));
    r0Dy.set_size(1, uvec.size(1));
    e_loop_ub = uvec.size(1);
    for (int i5{0}; i5 < e_loop_ub; i5++) {
        r0Dy[i5] = 0.0;
    }
    // 'bspline_eval_vec:4' xd = zeros(size(u));
    r1Dy.set_size(1, uvec.size(1));
    f_loop_ub = uvec.size(1);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        r1Dy[i6] = 0.0;
    }
    // 'bspline_eval_vec:5' xdd = zeros(size(u));
    r2Dy.set_size(1, uvec.size(1));
    g_loop_ub = uvec.size(1);
    for (int i7{0}; i7 < g_loop_ub; i7++) {
        r2Dy[i7] = 0.0;
    }
    // 'bspline_eval_vec:6' xddd = zeros(size(u));
    r3Dy.set_size(1, uvec.size(1));
    h_loop_ub = uvec.size(1);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        r3Dy[i8] = 0.0;
    }
    // 'bspline_eval_vec:8' for k = 1:length(u)
    i9 = uvec.size(1);
    for (int b_k{0}; b_k < i9; b_k++) {
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dy[b_k] = uvec[b_k];
        bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffY, &r0Dy[b_k], &d3, &d4, &d5);
        r3Dy[b_k] = d5;
        r2Dy[b_k] = d4;
        r1Dy[b_k] = d3;
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
    }
    // 'EvalBSplineNoCtx:13' [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
    // 'bspline_eval_vec:3' x = zeros(size(u));
    r0Dz.set_size(1, uvec.size(1));
    i_loop_ub = uvec.size(1);
    for (int i10{0}; i10 < i_loop_ub; i10++) {
        r0Dz[i10] = 0.0;
    }
    // 'bspline_eval_vec:4' xd = zeros(size(u));
    r1Dz.set_size(1, uvec.size(1));
    j_loop_ub = uvec.size(1);
    for (int i11{0}; i11 < j_loop_ub; i11++) {
        r1Dz[i11] = 0.0;
    }
    // 'bspline_eval_vec:5' xdd = zeros(size(u));
    r2Dz.set_size(1, uvec.size(1));
    k_loop_ub = uvec.size(1);
    for (int i12{0}; i12 < k_loop_ub; i12++) {
        r2Dz[i12] = 0.0;
    }
    // 'bspline_eval_vec:6' xddd = zeros(size(u));
    r3Dz.set_size(1, uvec.size(1));
    l_loop_ub = uvec.size(1);
    for (int i13{0}; i13 < l_loop_ub; i13++) {
        r3Dz[i13] = 0.0;
    }
    // 'bspline_eval_vec:8' for k = 1:length(u)
    i14 = uvec.size(1);
    for (int c_k{0}; c_k < i14; c_k++) {
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dz[c_k] = uvec[c_k];
        bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffZ, &r0Dz[c_k], &d6, &d7, &d8);
        r3Dz[c_k] = d8;
        r2Dz[c_k] = d7;
        r1Dz[c_k] = d6;
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
    }
    // 'EvalBSplineNoCtx:15' r0D = [r0Dx; r0Dy; r0Dz];
    r0D.set_size(3, r0Dx.size(1));
    m_loop_ub = r0Dx.size(1);
    for (int i15{0}; i15 < m_loop_ub; i15++) {
        r0D[3 * i15] = r0Dx[i15];
    }
    n_loop_ub = r0Dy.size(1);
    for (int i16{0}; i16 < n_loop_ub; i16++) {
        r0D[3 * i16 + 1] = r0Dy[i16];
    }
    o_loop_ub = r0Dz.size(1);
    for (int i17{0}; i17 < o_loop_ub; i17++) {
        r0D[3 * i17 + 2] = r0Dz[i17];
    }
    // 'EvalBSplineNoCtx:16' r1D = [r1Dx; r1Dy; r1Dz];
    r1D.set_size(3, r1Dx.size(1));
    p_loop_ub = r1Dx.size(1);
    for (int i18{0}; i18 < p_loop_ub; i18++) {
        r1D[3 * i18] = r1Dx[i18];
    }
    q_loop_ub = r1Dy.size(1);
    for (int i19{0}; i19 < q_loop_ub; i19++) {
        r1D[3 * i19 + 1] = r1Dy[i19];
    }
    r_loop_ub = r1Dz.size(1);
    for (int i20{0}; i20 < r_loop_ub; i20++) {
        r1D[3 * i20 + 2] = r1Dz[i20];
    }
    // 'EvalBSplineNoCtx:17' r2D = [r2Dx; r2Dy; r2Dz];
    // 'EvalBSplineNoCtx:18' r3D = [r3Dx; r3Dy; r3Dz];
}

//
// function [r0D, r1D, r2D, r3D] = EvalBSplineNoCtx(CurvSpline, uvec)
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
    // 'EvalBSplineNoCtx:2' coder.inline('never')
    // 'EvalBSplineNoCtx:3' if coder.target('rtw') || coder.target('mex')
    // 'EvalBSplineNoCtx:4' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalBSplineNoCtx:5' coder.ceval('ZoneScopedN', coder.opaque('const char*',
    // '"EvalBSpline"'));
    ZoneScopedN("EvalBSpline");
    // 'EvalBSplineNoCtx:8' Spline=CurvSpline;
    // 'EvalBSplineNoCtx:9' sp = Spline.sp;
    // 'EvalBSplineNoCtx:10' Bl = sp.Bl;
    // 'EvalBSplineNoCtx:11' [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
    // 'bspline_eval_vec:3' x = zeros(size(u));
    // 'bspline_eval_vec:4' xd = zeros(size(u));
    // 'bspline_eval_vec:5' xdd = zeros(size(u));
    // 'bspline_eval_vec:6' xddd = zeros(size(u));
    // 'bspline_eval_vec:8' for k = 1:length(u)
    // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
    r0Dx = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffX, &r0Dx, &r1Dx, &xddk, &xdddk);
    // 'bspline_eval_vec:10' x(k) = xk;
    // 'bspline_eval_vec:11' xd(k) = xdk;
    // 'bspline_eval_vec:12' xdd(k) = xddk;
    // 'bspline_eval_vec:13' xddd(k) = xdddk;
    // 'EvalBSplineNoCtx:12' [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
    // 'bspline_eval_vec:3' x = zeros(size(u));
    // 'bspline_eval_vec:4' xd = zeros(size(u));
    // 'bspline_eval_vec:5' xdd = zeros(size(u));
    // 'bspline_eval_vec:6' xddd = zeros(size(u));
    // 'bspline_eval_vec:8' for k = 1:length(u)
    // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
    r0Dy = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffY, &r0Dy, &r1Dy, &b_xddk, &b_xdddk);
    // 'bspline_eval_vec:10' x(k) = xk;
    // 'bspline_eval_vec:11' xd(k) = xdk;
    // 'bspline_eval_vec:12' xdd(k) = xddk;
    // 'bspline_eval_vec:13' xddd(k) = xdddk;
    // 'EvalBSplineNoCtx:13' [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
    // 'bspline_eval_vec:3' x = zeros(size(u));
    // 'bspline_eval_vec:4' xd = zeros(size(u));
    // 'bspline_eval_vec:5' xdd = zeros(size(u));
    // 'bspline_eval_vec:6' xddd = zeros(size(u));
    // 'bspline_eval_vec:8' for k = 1:length(u)
    // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
    r0Dz = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffZ, &r0Dz, &r1Dz, &c_xddk, &c_xdddk);
    // 'bspline_eval_vec:10' x(k) = xk;
    // 'bspline_eval_vec:11' xd(k) = xdk;
    // 'bspline_eval_vec:12' xdd(k) = xddk;
    // 'bspline_eval_vec:13' xddd(k) = xdddk;
    // 'EvalBSplineNoCtx:15' r0D = [r0Dx; r0Dy; r0Dz];
    r0D[0] = r0Dx;
    r0D[1] = r0Dy;
    r0D[2] = r0Dz;
    // 'EvalBSplineNoCtx:16' r1D = [r1Dx; r1Dy; r1Dz];
    r1D[0] = r1Dx;
    r1D[1] = r1Dy;
    r1D[2] = r1Dz;
    // 'EvalBSplineNoCtx:17' r2D = [r2Dx; r2Dy; r2Dz];
    // 'EvalBSplineNoCtx:18' r3D = [r3Dx; r3Dy; r3Dz];
}

//
// function [r0D, r1D, r2D, r3D] = EvalBSplineNoCtx(CurvSpline, uvec)
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
    double b_xdddk;
    double b_xddk;
    double c_xdddk;
    double c_xddk;
    double xdddk;
    double xddk;
    // 'EvalBSplineNoCtx:2' coder.inline('never')
    // 'EvalBSplineNoCtx:3' if coder.target('rtw') || coder.target('mex')
    // 'EvalBSplineNoCtx:4' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalBSplineNoCtx:5' coder.ceval('ZoneScopedN', coder.opaque('const char*',
    // '"EvalBSpline"'));
    ZoneScopedN("EvalBSpline");
    // 'EvalBSplineNoCtx:8' Spline=CurvSpline;
    // 'EvalBSplineNoCtx:9' sp = Spline.sp;
    // 'EvalBSplineNoCtx:10' Bl = sp.Bl;
    // 'EvalBSplineNoCtx:11' [r0Dx, r1Dx, r2Dx, r3Dx] = bspline_eval_vec(Bl, sp.CoeffX, uvec);
    // 'bspline_eval_vec:3' x = zeros(size(u));
    // 'bspline_eval_vec:4' xd = zeros(size(u));
    // 'bspline_eval_vec:5' xdd = zeros(size(u));
    // 'bspline_eval_vec:6' xddd = zeros(size(u));
    // 'bspline_eval_vec:8' for k = 1:length(u)
    for (int k{0}; k < 5; k++) {
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dx[k] = uvec[k];
        bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffX, &r0Dx[k], &r1Dx[k], &xddk,
                     &xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
    }
    // 'EvalBSplineNoCtx:12' [r0Dy, r1Dy, r2Dy, r3Dy] = bspline_eval_vec(Bl, sp.CoeffY, uvec);
    // 'bspline_eval_vec:3' x = zeros(size(u));
    // 'bspline_eval_vec:4' xd = zeros(size(u));
    // 'bspline_eval_vec:5' xdd = zeros(size(u));
    // 'bspline_eval_vec:6' xddd = zeros(size(u));
    // 'bspline_eval_vec:8' for k = 1:length(u)
    for (int b_k{0}; b_k < 5; b_k++) {
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dy[b_k] = uvec[b_k];
        bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffY, &r0Dy[b_k], &r1Dy[b_k], &b_xddk,
                     &b_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
    }
    // 'EvalBSplineNoCtx:13' [r0Dz, r1Dz, r2Dz, r3Dz] = bspline_eval_vec(Bl, sp.CoeffZ, uvec);
    // 'bspline_eval_vec:3' x = zeros(size(u));
    // 'bspline_eval_vec:4' xd = zeros(size(u));
    // 'bspline_eval_vec:5' xdd = zeros(size(u));
    // 'bspline_eval_vec:6' xddd = zeros(size(u));
    // 'bspline_eval_vec:8' for k = 1:length(u)
    for (int c_k{0}; c_k < 5; c_k++) {
        // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
        r0Dz[c_k] = uvec[c_k];
        bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffZ, &r0Dz[c_k], &r1Dz[c_k], &c_xddk,
                     &c_xdddk);
        // 'bspline_eval_vec:10' x(k) = xk;
        // 'bspline_eval_vec:11' xd(k) = xdk;
        // 'bspline_eval_vec:12' xdd(k) = xddk;
        // 'bspline_eval_vec:13' xddd(k) = xdddk;
    }
    // 'EvalBSplineNoCtx:15' r0D = [r0Dx; r0Dy; r0Dz];
    // 'EvalBSplineNoCtx:16' r1D = [r1Dx; r1Dy; r1Dz];
    for (int i{0}; i < 5; i++) {
        r0D[i][0] = r0Dx[i];
        r0D[i][1] = r0Dy[i];
        r0D[i][2] = r0Dz[i];
        r1D[i][0] = r1Dx[i];
        r1D[i][1] = r1Dy[i];
        r1D[i][2] = r1Dz[i];
    }
    // 'EvalBSplineNoCtx:17' r2D = [r2Dx; r2Dy; r2Dz];
    // 'EvalBSplineNoCtx:18' r3D = [r3Dx; r3Dy; r3Dz];
}

} // namespace ocn

//
// File trailer for EvalBSplineNoCtx.cpp
//
// [EOF]
//
