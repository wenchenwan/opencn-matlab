//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_create.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:51:01
//

// Include Files
#include "bspline_create.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <algorithm>

// Function Definitions
//
// function Bl = bspline_create(degree, breakpoints)
//
// Arguments    : int degree
//                const double breakpoints[10]
//                SplineBase *Bl
// Return Type  : void
//
namespace ocn {
void bspline_create(int degree, const double breakpoints[10], SplineBase *Bl)
{
    double b_breakpoints[10];
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'bspline_create:2' if coder.target('rtw') || coder.target('mex')
    // 'bspline_create:3' nbreak = length(breakpoints);
    // 'bspline_create:4' ncoeff = nbreak + degree - 2;
    Bl->ncoeff = degree + 8;
    // 'bspline_create:5' h = uint64(0);
    // 'bspline_create:7' coder.updateBuildInfo('addSourceFiles','c_spline.c', '$(START_DIR)/src');
    // 'bspline_create:8' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_create:9' coder.cinclude('src/c_spline.h');
    // 'bspline_create:10' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), degree,
    // breakpoints, int32(nbreak) );
    std::copy(&breakpoints[0], &breakpoints[10], &b_breakpoints[0]);
    c_bspline_create_with_breakpoints(&Bl->handle, degree, &b_breakpoints[0], 10);
    // 'bspline_create:11' Bl.ncoeff = ncoeff;
    // 'bspline_create:12' Bl.breakpoints = breakpoints;
    Bl->breakpoints.set_size(1, 10);
    for (int i{0}; i < 10; i++) {
        Bl->breakpoints[i] = breakpoints[i];
    }
    // 'bspline_create:13' Bl.handle = h;
    // 'bspline_create:14' Bl.degree = int32(degree);
    Bl->degree = degree;
    // 'bspline_create:15' coder.varsize('Bl.breakpoints', [1, Inf], [0, 1]);
}

} // namespace ocn

//
// File trailer for bspline_create.cpp
//
// [EOF]
//
