//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_copy.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 08:27:14
//

// Include Files
#include "bspline_copy.h"
#include "EvalCurvStruct_data.h"
#include "EvalCurvStruct_initialize.h"
#include "EvalCurvStruct_types3.h"
#include "coder_array.h"
#include "src/c_spline.h"

// Function Definitions
//
// function Copy = bspline_copy(Bl)
//
// Arguments    : const SplineBase *Bl
//                SplineBase *Copy
// Return Type  : void
//
namespace ocn {
void bspline_copy(const SplineBase *Bl, SplineBase *Copy)
{
    ::coder::array<double, 2U> breakpoints;
    int b_loop_ub;
    int loop_ub;
    if (!isInitialized_EvalCurvStruct) {
        EvalCurvStruct_initialize();
    }
    // 'bspline_copy:2' coder.inline("never");
    // 'bspline_copy:3' Copy = bspline_create(Bl.degree, Bl.breakpoints);
    // 'bspline_create:2' nbreak = length(breakpoints);
    // 'bspline_create:3' ncoeff = nbreak + degree - 2;
    Copy->ncoeff = (Bl->breakpoints.size(1) + Bl->degree) - 2;
    // 'bspline_create:5' h = uint64(0);
    // 'bspline_create:7' if coder.target('rtw') || coder.target('mex')
    // 'bspline_create:8' coder.updateBuildInfo('addSourceFiles','c_spline.c', '$(START_DIR)/src');
    // 'bspline_create:9' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_create:10' coder.cinclude('src/c_spline.h');
    // 'bspline_create:11' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), degree,
    // breakpoints, int32(nbreak));
    breakpoints.set_size(1, Bl->breakpoints.size(1));
    loop_ub = Bl->breakpoints.size(1);
    for (int i{0}; i < loop_ub; i++) {
        breakpoints[i] = Bl->breakpoints[i];
    }
    c_bspline_create_with_breakpoints(&Copy->handle, Bl->degree, &breakpoints[0],
                                      Bl->breakpoints.size(1));
    // 'bspline_create:12' Bl.ncoeff = ncoeff;
    // 'bspline_create:13' Bl.breakpoints = breakpoints;
    Copy->breakpoints.set_size(1, Bl->breakpoints.size(1));
    b_loop_ub = Bl->breakpoints.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        Copy->breakpoints[i1] = Bl->breakpoints[i1];
    }
    // 'bspline_create:14' Bl.handle = h;
    // 'bspline_create:15' Bl.degree = int32(degree);
    Copy->degree = Bl->degree;
    // 'bspline_create:16' coder.varsize('Bl.breakpoints', [1, Inf], [0, 1]);
}

} // namespace ocn

//
// File trailer for bspline_copy.cpp
//
// [EOF]
//
