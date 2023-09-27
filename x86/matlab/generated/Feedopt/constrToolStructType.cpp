//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrToolStructType.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:17:01
//

// Include Files
#include "constrToolStructType.h"
#include "constrToolStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"

// Function Definitions
//
// function [ C ] = constrToolStructType( ~ )
//
// constrToolStructType : Constructs a constrToolStructType with
//  default values.
//
// Arguments    : double a__1
//                Tool *C
// Return Type  : void
//
namespace ocn {
void constrToolStructType(double, Tool *C)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrToolStructType:5' if( nargin > 0 )
    // 'constrToolStructType:6' [ params ] = paramsDefaultTool( StructTypeName.MEX );
    // 'constrToolStructType:11' if( coder.target( "MATLAB" ) )
    // 'constrToolStructType:13' else
    // 'constrToolStructType:14' C = constrToolStruct( params.toolno, params.pocketno,
    // params.offset,... 'constrToolStructType:15'         params.diameter, params.frontangle,
    // params.backangle, ... 'constrToolStructType:16'         params.orientation );
    b_constrToolStruct(&C->toolno, &C->pocketno, &C->offset.x, &C->offset.y, &C->offset.z,
                       &C->offset.a, &C->offset.b, &C->offset.c, &C->offset.u, &C->offset.v,
                       &C->offset.w, &C->diameter, &C->frontangle, &C->backangle, &C->orientation);
}

} // namespace ocn

//
// File trailer for constrToolStructType.cpp
//
// [EOF]
//
