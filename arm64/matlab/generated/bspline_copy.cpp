//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_copy.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

// Include Files
#include "bspline_copy.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types3.h"
#include "coder_array.h"
#include "src/c_spline.h"

// Function Definitions
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
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    Copy->ncoeff = (Bl->breakpoints.size(1) + Bl->degree) - 2;
    breakpoints.set_size(1, Bl->breakpoints.size(1));
    loop_ub = Bl->breakpoints.size(1);
    for (int i{0}; i < loop_ub; i++) {
        breakpoints[i] = Bl->breakpoints[i];
    }
    c_bspline_create_with_breakpoints(&Copy->handle, Bl->degree, &breakpoints[0],
                                      Bl->breakpoints.size(1));
    Copy->breakpoints.set_size(1, Bl->breakpoints.size(1));
    b_loop_ub = Bl->breakpoints.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        Copy->breakpoints[i1] = Bl->breakpoints[i1];
    }
    Copy->degree = Bl->degree;
}

} // namespace ocn

//
// File trailer for bspline_copy.cpp
//
// [EOF]
//
