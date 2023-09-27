//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrAxesStructType.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 09:27:31
//

// Include Files
#include "constrAxesStructType.h"
#include "constrAxesStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types3.h"

// Function Definitions
//
// function [ C ] = constrAxesStructType( ~ )
//
// constrAxesStructType : Constructs a constrAxesStructType with
//  default values.
//
// Arguments    : double a__1
//                Axes *C
// Return Type  : void
//
namespace ocn {
void constrAxesStructType(double, Axes *C)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrAxesStructType:5' if( nargin > 0 )
    // 'constrAxesStructType:6' [ params ] = paramsDefaultAxes( StructTypeName.MEX );
    // 'constrAxesStructType:11' if( coder.target( "MATLAB" ) )
    // 'constrAxesStructType:13' else
    // 'constrAxesStructType:14' C = constrAxesStruct( params.x, params.y, params.z, params.a, ...
    // 'constrAxesStructType:15'         params.b, params.c, params.u, params.v, params.w );
    constrAxesStruct(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, C);
}

} // namespace ocn

//
// File trailer for constrAxesStructType.cpp
//
// [EOF]
//
