//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_eval.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "bspline_eval.h"
#include "sinspace_types11.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <stdio.h>

// Function Definitions
//
// void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
//
// Arguments    : const uint64m_T Bl_handle
//                const double coeffs[4]
//                double *x
//                double *xd
//                double *xdd
// Return Type  : void
//
namespace ocn {
void bspline_eval(const uint64m_T Bl_handle, const double coeffs[4], double *x, double *xd,
                  double *xdd)
{
    double X[4];
    c_bspline_eval(&Bl_handle, &coeffs[0], *x, &X[0]);
    *x = X[0];
    *xd = X[1];
    *xdd = X[2];
}

//
// void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
//
// Arguments    : const uint64m_T Bl_handle
//                const ::coder::array<double, 2U> &coeffs
//                double *x
//                double *xd
//                double *xdd
//                double *xddd
// Return Type  : void
//
void bspline_eval(const uint64m_T Bl_handle, const ::coder::array<double, 2U> &coeffs, double *x,
                  double *xd, double *xdd, double *xddd)
{
    double X[4];
    if (*x < 0.0) {
        printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", *x);
        fflush(stdout);
        *x = 0.0;
    } else if (*x > 1.0) {
        printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", *x);
        fflush(stdout);
        *x = 1.0;
    }
    c_bspline_eval(&Bl_handle, &coeffs[0], *x, &X[0]);
    *x = X[0];
    *xd = X[1];
    *xdd = X[2];
    *xddd = X[3];
}

//
// void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
//
// Arguments    : const uint64m_T Bl_handle
//                const ::coder::array<double, 2U> &coeffs
//                double *x
//                double *xd
//                double *xdd
// Return Type  : void
//
void bspline_eval(const uint64m_T Bl_handle, const ::coder::array<double, 2U> &coeffs, double *x,
                  double *xd, double *xdd)
{
    double X[4];
    if (*x < 0.0) {
        printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", *x);
        fflush(stdout);
        *x = 0.0;
    } else if (*x > 1.0) {
        printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", *x);
        fflush(stdout);
        *x = 1.0;
    }
    c_bspline_eval(&Bl_handle, &coeffs[0], *x, &X[0]);
    *x = X[0];
    *xd = X[1];
    *xdd = X[2];
}

} // namespace ocn

//
// File trailer for bspline_eval.cpp
//
// [EOF]
//
