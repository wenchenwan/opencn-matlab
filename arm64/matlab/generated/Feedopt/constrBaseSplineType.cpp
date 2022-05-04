//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrBaseSplineType.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-May-2022 16:43:53
//

// Include Files
#include "constrBaseSplineType.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"

// Function Definitions
//
// function [ C ] = constrBaseSplineType( ~ )
//
// constrBaseSplineType : Constructs a constrBaseSpline with default values.
//
// Arguments    : double a__1
//                BaseSplineStruct *C
// Return Type  : void
//
namespace ocn {
void constrBaseSplineType(double, BaseSplineStruct *C)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrBaseSplineType:4' if( nargin > 0 )
    // 'constrBaseSplineType:5' [ params ] = paramsDefaultBaseSpline( StructTypeName.MEX );
    // 'constrBaseSplineType:10' if( coder.target( "MATLAB" ) )
    // 'constrBaseSplineType:12' else
    // 'constrBaseSplineType:13' C = constrBaseSpline( params.ncoeff, params.breakpoints, ...
    // 'constrBaseSplineType:14'         params.handle, params.order );
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
    C->ncoeff = 0;
    C->breakpoints.set_size(1, 1);
    C->breakpoints[0] = 0.0;
    C->handle = 0UL;
    C->order = 0;
    // 'constrBaseSpline:19' if ~coder.target( 'MATLAB' )
    // 'constrBaseSpline:20' coder.varsize( 'BaseSplineStrct.breakpoints', StructTypeName.dimNBreak{
    // : } ); 'constrBaseSpline:21' coder.cstructname( BaseSplineStrct, StructTypeName.BaseSpline );
}

} // namespace ocn

//
// File trailer for constrBaseSplineType.cpp
//
// [EOF]
//
