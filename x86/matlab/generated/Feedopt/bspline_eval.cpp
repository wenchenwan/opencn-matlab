
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_eval.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "bspline_eval.h"
#include "ocn_print1.h"
#include "opencn_matlab_data.h"
#include "string1.h"
#include "c_spline.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
#include <stdio.h>

// Function Definitions
//
// function [ x, xd, xdd, xddd ] = bspline_eval( Bl, coeffs, x )
//
// bspline_eval  : Eval Bspline bases for a given set of points and
//  coefficients
//
//  Inputs :
//  Bl            : BSpline bases
//  coeffs        : Coefficients used during the evaluation
//  x             : Given set of points
//
//  Outputs:
//  x             : Evaluated points
//  xd            : Evaluated points derivative
//  xdd           : Evaluated points 2nd derivative
//  xddd          : Evaluated points 3rd derivative
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
    coder::rtString obj;
    double X[4];
    char st[24];
    char obj2Value_data[23];
    // 'bspline_eval:15' enablePrint = true;
    // 'bspline_eval:16' X = zeros(1, 4);
    // 'bspline_eval:17' ocn_assert( isreal( x ), "x should be real", mfilename );
    // 'bspline_eval:19' if coder.target( "MATLAB" )
    // 'bspline_eval:22' else
    // 'bspline_eval:23' if ( x < 0 )
    if (*x < 0.0) {
        int obj2Value_size_idx_1;
        // 'bspline_eval:24' ocn_print( enablePrint, ...
        // 'bspline_eval:25'                 "ERROR: C_BSPLINE_EVAL: X < 0 (" + x + ")", mfilename
        // );
        if (*x == 0.0) {
            obj2Value_size_idx_1 = 1;
            obj2Value_data[0] = '0';
        } else {
            int resCount;
            resCount = sprintf(&st[0], "%.16g", *x);
            obj2Value_size_idx_1 = resCount;
            if (resCount - 1 >= 0) {
                std::copy(&st[0], &st[resCount], &obj2Value_data[0]);
            }
        }
        obj.Value.size[0] = 1;
        obj.Value.size[1] = obj2Value_size_idx_1 + 31;
        for (int i{0}; i < 30; i++) {
            obj.Value.data[i] = cv2[i];
        }
        if (obj2Value_size_idx_1 - 1 >= 0) {
            std::copy(&obj2Value_data[0], &obj2Value_data[obj2Value_size_idx_1],
                      &obj.Value.data[30]);
        }
        obj.Value.data[obj2Value_size_idx_1 + 30] = ')';
        ocn_print(&obj);
        // 'bspline_eval:26' x = 0;
        *x = 0.0;
    } else if (*x > 1.0) {
        int obj2Value_size_idx_1;
        // 'bspline_eval:27' elseif ( x > 1 )
        // 'bspline_eval:28' ocn_print( enablePrint, ...
        // 'bspline_eval:29'                 "ERROR: C_BSPLINE_EVAL: X > 1 (" + x + ")", mfilename
        // );
        if (*x == 0.0) {
            obj2Value_size_idx_1 = 1;
            obj2Value_data[0] = '0';
        } else {
            int b_resCount;
            b_resCount = sprintf(&st[0], "%.16g", *x);
            obj2Value_size_idx_1 = b_resCount;
            if (b_resCount - 1 >= 0) {
                std::copy(&st[0], &st[b_resCount], &obj2Value_data[0]);
            }
        }
        obj.Value.size[0] = 1;
        obj.Value.size[1] = obj2Value_size_idx_1 + 31;
        for (int i1{0}; i1 < 30; i1++) {
            obj.Value.data[i1] = cv3[i1];
        }
        if (obj2Value_size_idx_1 - 1 >= 0) {
            std::copy(&obj2Value_data[0], &obj2Value_data[obj2Value_size_idx_1],
                      &obj.Value.data[30]);
        }
        obj.Value.data[obj2Value_size_idx_1 + 30] = ')';
        ocn_print(&obj);
        // 'bspline_eval:30' x = 1;
        *x = 1.0;
    }
    // 'bspline_eval:32' my_path = StructTypeName.WDIR + "/src";
    // 'bspline_eval:33' coder.updateBuildInfo('addIncludePaths',my_path);
    // 'bspline_eval:34' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
    // 'bspline_eval:35' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_eval:36' coder.cinclude('c_spline.h');
    // 'bspline_eval:38' coder.ceval( 'c_bspline_eval', coder.rref(Bl.handle), ...
    // 'bspline_eval:39'             coder.rref(coeffs), x, coder.wref(X));
    c_bspline_eval(&Bl_handle, &coeffs[0], *x, &X[0]);
    // 'bspline_eval:40' x       = X(1);
    *x = X[0];
    // 'bspline_eval:41' xd      = X(2);
    *xd = X[1];
    // 'bspline_eval:42' xdd     = X(3);
    *xdd = X[2];
    // 'bspline_eval:43' xddd    = X(4);
    *xddd = X[3];
}

} // namespace ocn

//
// File trailer for bspline_eval.cpp
//
// [EOF]
//
