
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bspline_copy.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "bspline_copy.h"
#include "constrBaseSpline.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types2.h"
#include "c_spline.h"
#include "coder_array.h"

// Function Definitions
//
// function [ copy ] = bspline_copy( Bl )
//
// bspline_copy : Copy the bspline bases
//  Inputs :
//  Bl            : BSpline bases
//  Outputs :
//  Copy          : Copy of the BSpline bases
//
// Arguments    : const BaseSplineStruct *Bl
//                BaseSplineStruct *copy
// Return Type  : void
//
namespace ocn {
void bspline_copy(const BaseSplineStruct *Bl, BaseSplineStruct *copy)
{
    ::coder::array<double, 2U> breakpoints;
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'bspline_copy:7' coder.inline("never");
    // 'bspline_copy:8' copy = bspline_create( Bl.order, Bl.breakpoints );
    //  bspline_create : Create the BSpline basis functions
    //
    //  Inputs :
    //  degree        : BSpline degree
    //  breakpoints   : Vector of breakpoints
    //
    //  Outputs :
    //  Bl            : Bspline basis
    // 'bspline_create:10' if  coder.target( "MATLAB" )
    // 'bspline_create:12' else
    // 'bspline_create:13' nbreak  = length(breakpoints);
    // 'bspline_create:14' ncoeff  = nbreak + degree - 2;
    // 'bspline_create:15' h       = uint64(0);
    // 'bspline_create:16' my_path = StructTypeName.WDIR + "/src";
    // 'bspline_create:17' coder.updateBuildInfo('addIncludePaths',my_path);
    // 'bspline_create:18' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
    // 'bspline_create:19' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_create:20' coder.cinclude('c_spline.h');
    // 'bspline_create:21' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), ...
    // 'bspline_create:22'         degree, breakpoints, int32(nbreak) );
    breakpoints.set_size(1, Bl->breakpoints.size(1));
    loop_ub = Bl->breakpoints.size(1);
    for (int i{0}; i < loop_ub; i++) {
        breakpoints[i] = Bl->breakpoints[i];
    }
    unsigned long h;
    c_bspline_create_with_breakpoints(&h, Bl->order, &breakpoints[0], Bl->breakpoints.size(1));
    // 'bspline_create:23' Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
    constrBaseSpline((Bl->breakpoints.size(1) + Bl->order) - 2, Bl->breakpoints, h, Bl->order,
                     copy);
}

} // namespace ocn

//
// File trailer for bspline_copy.cpp
//
// [EOF]
//
