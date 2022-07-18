//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrBaseSpline.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:54:02
//

// Include Files
#include "constrBaseSpline.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"

// Function Definitions
//
// function [ BaseSplineStrct ] = constrBaseSpline( ncoeff, breakpoints, ...
//     handle, order )
//
// Construct a struct base spline.
//
//  Inputs :
//  ncoeff       : Number of coefficients
//  breakpoints  : Number of breakpoints
//  handle       : Pointer on the structure
//  degree       : order of the spline
//
//  Outputs :
//  CStrct    : The resulting structure
//
// Arguments    : int ncoeff
//                const ::coder::array<double, 2U> &breakpoints
//                unsigned long handle
//                int order
//                BaseSplineStruct *BaseSplineStrct
// Return Type  : void
//
namespace ocn {
void constrBaseSpline(int ncoeff, const ::coder::array<double, 2U> &breakpoints,
                      unsigned long handle, int order, BaseSplineStruct *BaseSplineStrct)
{
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrBaseSpline:14' BaseSplineStrct = struct( 'ncoeff', ncoeff,...
    // 'constrBaseSpline:15'         'breakpoints', breakpoints,...
    // 'constrBaseSpline:16'         'handle', handle,...
    // 'constrBaseSpline:17'         'order', order );
    BaseSplineStrct->ncoeff = ncoeff;
    BaseSplineStrct->breakpoints.set_size(1, breakpoints.size(1));
    loop_ub = breakpoints.size(1);
    for (int i{0}; i < loop_ub; i++) {
        BaseSplineStrct->breakpoints[i] = breakpoints[i];
    }
    BaseSplineStrct->handle = handle;
    BaseSplineStrct->order = order;
    // 'constrBaseSpline:19' if ~coder.target( 'MATLAB' )
    // 'constrBaseSpline:20' coder.varsize( 'BaseSplineStrct.breakpoints', StructTypeName.dimNBreak{
    // : } ); 'constrBaseSpline:21' coder.cstructname( BaseSplineStrct, StructTypeName.BaseSpline );
}

} // namespace ocn

//
// File trailer for constrBaseSpline.cpp
//
// [EOF]
//
