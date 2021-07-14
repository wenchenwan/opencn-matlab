//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_create.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "bspline_create.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <algorithm>

// Function Definitions
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
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    Bl->ncoeff = degree + 8;
    std::copy(&breakpoints[0], &breakpoints[10], &b_breakpoints[0]);
    c_bspline_create_with_breakpoints(&Bl->handle, degree, &b_breakpoints[0], 10);
    Bl->breakpoints.set_size(1, 10);
    for (int i{0}; i < 10; i++) {
        Bl->breakpoints[i] = breakpoints[i];
    }
    Bl->degree = degree;
}

} // namespace ocn

//
// File trailer for bspline_create.cpp
//
// [EOF]
//
