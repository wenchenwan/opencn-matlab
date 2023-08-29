//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_eval.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 16:48:46
//

// Include Files
#include "bspline_eval.h"
#include "c_spline.h"
#include "coder_array.h"
#include <stdio.h>

// Function Definitions
//
// function [ x, xd, xdd, xddd ] = bspline_eval( Bl, coeffs, x )
//
// void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
//
// Arguments    : unsigned long Bl_handle
//                const ::coder::array<double, 2U> &coeffs
//                double *x
//                double *xd
//                double *xdd
//                double *xddd
// Return Type  : void
//
namespace ocn {
void bspline_eval(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs, double *x,
                  double *xd, double *xdd, double *xddd)
{
    double X[4];
    // 'bspline_eval:3' X = zeros(1, 4);
    // 'bspline_eval:4' if( ~isreal(x) )
    // 'bspline_eval:8' if coder.target('matlab')
    // 'bspline_eval:15' if coder.target('rtw') || coder.target('mex')
    // 'bspline_eval:16' if x < 0
    if (*x < 0.0) {
        // 'bspline_eval:17' fprintf('ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n', x);
        printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", *x);
        fflush(stdout);
        // 'bspline_eval:18' x = 0;
        *x = 0.0;
    } else if (*x > 1.0) {
        // 'bspline_eval:19' elseif x > 1
        // 'bspline_eval:20' fprintf('ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n', x);
        printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", *x);
        fflush(stdout);
        // 'bspline_eval:21' x = 1;
        *x = 1.0;
    }
    // 'bspline_eval:23' my_path = StructTypeName.WDIR + "/src";
    // 'bspline_eval:24' coder.updateBuildInfo('addIncludePaths',my_path);
    // 'bspline_eval:25' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
    // 'bspline_eval:26' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_eval:27' coder.cinclude('c_spline.h');
    // 'bspline_eval:29' coder.ceval('c_bspline_eval', coder.rref(Bl.handle), coder.rref(coeffs),...
    // 'bspline_eval:30'                     x, coder.wref(X));
    c_bspline_eval(&Bl_handle, &coeffs[0], *x, &X[0]);
    // 'bspline_eval:31' x       = X(1);
    *x = X[0];
    // 'bspline_eval:32' xd      = X(2);
    *xd = X[1];
    // 'bspline_eval:33' xdd     = X(3);
    *xdd = X[2];
    // 'bspline_eval:34' xddd    = X(4);
    *xddd = X[3];
}

} // namespace ocn

//
// File trailer for bspline_eval.cpp
//
// [EOF]
//
