//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_eval.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 11:16:30
//

// Include Files
#include "bspline_eval.h"
#include "opencn_matlab_types11.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <stdio.h>

// Function Definitions
//
// function [x, xd, xdd, xddd] = bspline_eval(Bl, coeffs, x)
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
namespace ocn {
void bspline_eval(const uint64m_T Bl_handle, const ::coder::array<double, 2U> &coeffs, double *x,
                  double *xd, double *xdd, double *xddd)
{
    double X[4];
    // 'bspline_eval:3' X = zeros(1, 4);
    // 'bspline_eval:4' if coder.target('matlab')
    // 'bspline_eval:7' if coder.target('rtw') || coder.target('mex')
    // 'bspline_eval:8' if x < 0
    if (*x < 0.0) {
        // 'bspline_eval:9' fprintf('ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n', x);
        printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", *x);
        fflush(stdout);
        // 'bspline_eval:10' x = 0;
        *x = 0.0;
    } else if (*x > 1.0) {
        // 'bspline_eval:11' elseif x > 1
        // 'bspline_eval:12' fprintf('ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n', x);
        printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", *x);
        fflush(stdout);
        // 'bspline_eval:13' x = 1;
        *x = 1.0;
    }
    // 'bspline_eval:15' coder.updateBuildInfo('addSourceFiles','c_spline.c', '$(START_DIR)/src');
    // 'bspline_eval:16' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_eval:17' coder.cinclude('src/c_spline.h');
    // 'bspline_eval:18' coder.ceval('c_bspline_eval', coder.rref(Bl.handle), coder.rref(coeffs),...
    // 'bspline_eval:19'             x, coder.wref(X));
    c_bspline_eval(&Bl_handle, &coeffs[0], *x, &X[0]);
    // 'bspline_eval:20' x = X(1);
    *x = X[0];
    // 'bspline_eval:21' xd = X(2);
    *xd = X[1];
    // 'bspline_eval:22' xdd = X(3);
    *xdd = X[2];
    // 'bspline_eval:23' xddd = X(4);
    *xddd = X[3];
}

//
// function [x, xd, xdd, xddd] = bspline_eval(Bl, coeffs, x)
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
    // 'bspline_eval:3' X = zeros(1, 4);
    // 'bspline_eval:4' if coder.target('matlab')
    // 'bspline_eval:7' if coder.target('rtw') || coder.target('mex')
    // 'bspline_eval:8' if x < 0
    if (*x < 0.0) {
        // 'bspline_eval:9' fprintf('ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n', x);
        printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", *x);
        fflush(stdout);
        // 'bspline_eval:10' x = 0;
        *x = 0.0;
    } else if (*x > 1.0) {
        // 'bspline_eval:11' elseif x > 1
        // 'bspline_eval:12' fprintf('ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n', x);
        printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", *x);
        fflush(stdout);
        // 'bspline_eval:13' x = 1;
        *x = 1.0;
    }
    // 'bspline_eval:15' coder.updateBuildInfo('addSourceFiles','c_spline.c', '$(START_DIR)/src');
    // 'bspline_eval:16' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_eval:17' coder.cinclude('src/c_spline.h');
    // 'bspline_eval:18' coder.ceval('c_bspline_eval', coder.rref(Bl.handle), coder.rref(coeffs),...
    // 'bspline_eval:19'             x, coder.wref(X));
    c_bspline_eval(&Bl_handle, &coeffs[0], *x, &X[0]);
    // 'bspline_eval:20' x = X(1);
    *x = X[0];
    // 'bspline_eval:21' xd = X(2);
    *xd = X[1];
    // 'bspline_eval:22' xdd = X(3);
    *xdd = X[2];
    // 'bspline_eval:23' xddd = X(4);
}

} // namespace ocn

//
// File trailer for bspline_eval.cpp
//
// [EOF]
//
