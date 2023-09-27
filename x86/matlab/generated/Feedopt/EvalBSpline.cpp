//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalBSpline.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:17:01
//

// Include Files
#include "EvalBSpline.h"
#include "bspline_eval.h"
#include "coder_array.h"

// Function Definitions
//
// function [ r0D, r1D, r2D, r3D ] = EvalBSpline( spline, u_vec )
//
// EvalBSpline
//
//  INPUT
//  spline        : struct : Spline structure
//  u_vec         :    1xn : Vector for evaluation of the curv
//
//  OUTPUT
//  r0D           :   nDxn : The evaluated B spline at u\_vec points
//  r1D           :   nDxn : 1rst order parametric derivative for the B spline at u\_vec points
//  r2D           :   nDxn : 2nd order parametric derivative for the B spline at u\_vec points
//  r3D           :   nDxn : 3rd order parametric derivative for the B spline at u\_vec points
//
// Arguments    : unsigned long spline_sp_Bl_handle
//                const ::coder::array<double, 2U> &spline_sp_coeff
//                const double u_vec[5]
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
// Return Type  : void
//
namespace ocn {
void EvalBSpline(unsigned long spline_sp_Bl_handle,
                 const ::coder::array<double, 2U> &spline_sp_coeff, const double u_vec[5],
                 ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D)
{
    ::coder::array<double, 2U> b_spline_sp_coeff;
    double dv[5];
    double dv1[5];
    double dv2[5];
    double dv3[5];
    int i2;
    int loop_ub;
    // 'EvalBSpline:14' sp = spline.sp;
    // 'EvalBSpline:15' N  = length( u_vec );
    // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
    // 'EvalBSpline:18' r0D = zeros( M, N );
    // 'EvalBSpline:18' r1D = r0D;
    r1D.set_size(spline_sp_coeff.size(0), 5);
    loop_ub = spline_sp_coeff.size(0);
    for (int i{0}; i < 5; i++) {
        for (int i1{0}; i1 < loop_ub; i1++) {
            r1D[i1 + r1D.size(0) * i] = 0.0;
        }
    }
    // 'EvalBSpline:18' r2D = r1D;
    // 'EvalBSpline:18' r3D = r2D;
    // 'EvalBSpline:20' for j = 1 : M
    i2 = spline_sp_coeff.size(0);
    r0D.set_size(spline_sp_coeff.size(0), 5);
    for (int j{0}; j < i2; j++) {
        int b_loop_ub;
        // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
        // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, : ),
        // u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd      =
        // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6' xddd
        // = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
        b_loop_ub = spline_sp_coeff.size(1);
        for (int k{0}; k < 5; k++) {
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            dv[k] = u_vec[k];
            b_spline_sp_coeff.set_size(1, b_loop_ub);
            for (int i4{0}; i4 < b_loop_ub; i4++) {
                b_spline_sp_coeff[i4] = spline_sp_coeff[j + spline_sp_coeff.size(0) * i4];
            }
            bspline_eval(spline_sp_Bl_handle, b_spline_sp_coeff, &dv[k], &dv1[k], &dv2[k], &dv3[k]);
            // 'bspline_eval_vec:10' x(k)    = xk;
            // 'bspline_eval_vec:11' xd(k)   = xdk;
            // 'bspline_eval_vec:12' xdd(k)  = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
        for (int i3{0}; i3 < 5; i3++) {
            r0D[j + r0D.size(0) * i3] = dv[i3];
            r1D[j + r1D.size(0) * i3] = dv1[i3];
        }
    }
}

} // namespace ocn

//
// File trailer for EvalBSpline.cpp
//
// [EOF]
//
