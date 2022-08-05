//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_copy.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:07:54
//

// Include Files
#include "bspline_copy.h"
#include "constrBaseSpline.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"
#include "src/c_spline.h"

// Function Definitions
//
// function Copy = bspline_copy(Bl)
//
// Arguments    : const BaseSplineStruct *Bl
//                BaseSplineStruct *Copy
// Return Type  : void
//
namespace ocn {
void bspline_copy(const BaseSplineStruct *Bl, BaseSplineStruct *Copy)
{
    ::coder::array<double, 2U> breakpoints;
    unsigned long h;
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'bspline_copy:2' coder.inline("never");
    // 'bspline_copy:3' Copy = bspline_create(Bl.order, Bl.breakpoints);
    // 'bspline_create:2' if coder.target('rtw') || coder.target('mex')
    // 'bspline_create:3' nbreak = length(breakpoints);
    // 'bspline_create:4' ncoeff = nbreak + degree - 2;
    // 'bspline_create:5' h = uint64(0);
    // 'bspline_create:7' coder.updateBuildInfo('addSourceFiles','c_spline.c', '$(START_DIR)/src');
    // 'bspline_create:8' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_create:9' coder.cinclude('src/c_spline.h');
    // 'bspline_create:10' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), degree,
    // breakpoints, int32(nbreak) );
    breakpoints.set_size(1, Bl->breakpoints.size(1));
    loop_ub = Bl->breakpoints.size(1);
    for (int i{0}; i < loop_ub; i++) {
        breakpoints[i] = Bl->breakpoints[i];
    }
    c_bspline_create_with_breakpoints(&h, Bl->order, &breakpoints[0], Bl->breakpoints.size(1));
    // 'bspline_create:11' Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
    constrBaseSpline((Bl->breakpoints.size(1) + Bl->order) - 2, Bl->breakpoints, h, Bl->order,
                     Copy);
}

} // namespace ocn

//
// File trailer for bspline_copy.cpp
//
// [EOF]
//
