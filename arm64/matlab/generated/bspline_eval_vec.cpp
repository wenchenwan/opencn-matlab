//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_eval_vec.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

// Include Files
#include "bspline_eval_vec.h"
#include "bspline_eval.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <stdio.h>

// Function Definitions
//
// Arguments    : unsigned long Bl_handle
//                const double coeffs[4]
//                const double u[2]
//                double x[2]
// Return Type  : void
//
namespace ocn {
void bspline_eval_vec(unsigned long Bl_handle, const double coeffs[4], const double u[2],
                      double x[2])
{
    double X[4];
    double b_x;
    //  void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
    b_x = u[0];
    if (u[0] < 0.0) {
        printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", u[0]);
        fflush(stdout);
        b_x = 0.0;
    } else if (u[0] > 1.0) {
        printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", u[0]);
        fflush(stdout);
        b_x = 1.0;
    }
    c_bspline_eval(&Bl_handle, &coeffs[0], b_x, &X[0]);
    x[0] = X[0];
    //  void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
    b_x = u[1];
    if (u[1] < 0.0) {
        printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", u[1]);
        fflush(stdout);
        b_x = 0.0;
    } else if (u[1] > 1.0) {
        printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", u[1]);
        fflush(stdout);
        b_x = 1.0;
    }
    c_bspline_eval(&Bl_handle, &coeffs[0], b_x, &X[0]);
    x[1] = X[0];
}

//
// Arguments    : unsigned long Bl_handle
//                const ::coder::array<double, 2U> &coeffs
//                const ::coder::array<double, 2U> &u
//                ::coder::array<double, 2U> &x
// Return Type  : void
//
void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
                      const ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &x)
{
    ::coder::array<double, 2U> xd;
    ::coder::array<double, 2U> xdd;
    ::coder::array<double, 2U> xddd;
    double d;
    double d1;
    double d2;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int i4;
    int loop_ub;
    x.set_size(1, u.size(1));
    loop_ub = u.size(1);
    for (int i{0}; i < loop_ub; i++) {
        x[i] = 0.0;
    }
    xd.set_size(1, u.size(1));
    b_loop_ub = u.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        xd[i1] = 0.0;
    }
    xdd.set_size(1, u.size(1));
    c_loop_ub = u.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        xdd[i2] = 0.0;
    }
    xddd.set_size(1, u.size(1));
    d_loop_ub = u.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        xddd[i3] = 0.0;
    }
    i4 = u.size(1);
    for (int k{0}; k < i4; k++) {
        x[k] = u[k];
        bspline_eval(Bl_handle, coeffs, &x[k], &d, &d1, &d2);
        xddd[k] = d2;
        xdd[k] = d1;
        xd[k] = d;
    }
}

//
// Arguments    : unsigned long Bl_handle
//                const ::coder::array<double, 2U> &coeffs
//                const ::coder::array<double, 2U> &u
//                ::coder::array<double, 2U> &x
//                ::coder::array<double, 2U> &xd
//                ::coder::array<double, 2U> &xdd
//                ::coder::array<double, 2U> &xddd
// Return Type  : void
//
void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
                      const ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &x,
                      ::coder::array<double, 2U> &xd, ::coder::array<double, 2U> &xdd,
                      ::coder::array<double, 2U> &xddd)
{
    double d;
    double d1;
    double d2;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int i4;
    int loop_ub;
    x.set_size(1, u.size(1));
    loop_ub = u.size(1);
    for (int i{0}; i < loop_ub; i++) {
        x[i] = 0.0;
    }
    xd.set_size(1, u.size(1));
    b_loop_ub = u.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        xd[i1] = 0.0;
    }
    xdd.set_size(1, u.size(1));
    c_loop_ub = u.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        xdd[i2] = 0.0;
    }
    xddd.set_size(1, u.size(1));
    d_loop_ub = u.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        xddd[i3] = 0.0;
    }
    i4 = u.size(1);
    for (int k{0}; k < i4; k++) {
        x[k] = u[k];
        bspline_eval(Bl_handle, coeffs, &x[k], &d, &d1, &d2);
        xddd[k] = d2;
        xdd[k] = d1;
        xd[k] = d;
    }
}

} // namespace ocn

//
// File trailer for bspline_eval_vec.cpp
//
// [EOF]
//
