//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrCurvStructType.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:04:10
//

// Include Files
#include "constrCurvStructType.h"
#include "constrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"

// Function Definitions
//
// function [ C ] = constrCurvStructType( ~ )
//
// constrCurvStructType : Constructs a constrCurvStruct with default values.
//
// Arguments    : double a__1
//                CurvStruct *C
// Return Type  : void
//
namespace ocn {
void constrCurvStructType(double, CurvStruct *C)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrCurvStructType:4' if( nargin > 0 )
    // 'constrCurvStructType:5' [ params ] = paramsDefaultCurv( StructTypeName.MEX );
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.R0, params.R1,
    // ... 'constrCurvStructType:14'         params.Cprim, params.delta, params.evec, params.theta,
    // ... 'constrCurvStructType:15'         params.pitch, params.CoeffP5, params.Coeff );
    b_constrCurvStruct(C);
}

} // namespace ocn

//
// File trailer for constrCurvStructType.cpp
//
// [EOF]
//
