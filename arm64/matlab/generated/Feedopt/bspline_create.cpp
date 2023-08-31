//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_create.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 31-Aug-2023 09:29:48
//

// Include Files
#include "bspline_create.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types3.h"
#include "c_spline.h"
#include "coder_array.h"
#include <algorithm>

// Function Definitions
//
// function Bl = bspline_create(degree, breakpoints)
//
// Arguments    : int degree
//                const double breakpoints[10]
//                BaseSplineStruct *Bl
// Return Type  : void
//
namespace ocn {
void bspline_create(int degree, const double breakpoints[10], BaseSplineStruct *Bl)
{
    double b_breakpoints[10];
    unsigned long t9_handle;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'bspline_create:2' if  coder.target('rtw') || coder.target('mex')
    // 'bspline_create:3' nbreak = length(breakpoints);
    // 'bspline_create:4' ncoeff = nbreak + degree - 2;
    // 'bspline_create:5' h = uint64(0);
    // 'bspline_create:6' my_path = StructTypeName.WDIR + "/src";
    // 'bspline_create:7' coder.updateBuildInfo('addIncludePaths',my_path);
    // 'bspline_create:8' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
    // 'bspline_create:9' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_create:10' coder.cinclude('c_spline.h');
    // 'bspline_create:11' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), degree,
    // breakpoints, int32(nbreak) );
    std::copy(&breakpoints[0], &breakpoints[10], &b_breakpoints[0]);
    c_bspline_create_with_breakpoints(&t9_handle, degree, &b_breakpoints[0], 10);
    // 'bspline_create:12' Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
    //  Construct a struct base spline.
    //
    //  Inputs :
    //  ncoeff       : Number of coefficients
    //  breakpoints  : Number of breakpoints
    //  handle       : Pointer on the structure
    //  degree       : order of the spline
    //
    //  Outputs :
    //  CStrct    : The resulting structure
    // 'constrBaseSpline:14' BaseSplineStrct = struct( 'ncoeff', ncoeff,...
    // 'constrBaseSpline:15'         'breakpoints', breakpoints,...
    // 'constrBaseSpline:16'         'handle', handle,...
    // 'constrBaseSpline:17'         'order', order );
    Bl->ncoeff = degree + 8;
    Bl->breakpoints.set_size(1, 10);
    for (int i{0}; i < 10; i++) {
        Bl->breakpoints[i] = breakpoints[i];
    }
    Bl->handle = t9_handle;
    Bl->order = degree;
    // 'constrBaseSpline:19' if ~coder.target( 'MATLAB' )
    // 'constrBaseSpline:20' coder.varsize( 'BaseSplineStrct.breakpoints', StructTypeName.dimNBreak{
    // : } ); 'constrBaseSpline:21' coder.cstructname( BaseSplineStrct, StructTypeName.BaseSpline );
}

} // namespace ocn

//
// File trailer for bspline_create.cpp
//
// [EOF]
//
