//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrGcodeInfoStructType.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
//

// Include Files
#include "constrGcodeInfoStructType.h"
#include "constrGcodeInfoStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types31.h"

// Function Definitions
//
// function [ C ] = constrGcodeInfoStructType( ~ )
//
// constrGcodeInfoStructType : Constructs a constrGcodeInfoStruct with
//  default values.
//
// Arguments    : double a__1
//                GcodeInfoStruct *C
// Return Type  : void
//
namespace ocn {
void constrGcodeInfoStructType(double, GcodeInfoStruct *C)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrGcodeInfoStructType:5' if( nargin > 0 )
    // 'constrGcodeInfoStructType:6' [ params ] = paramsDefaultGCodeInfo( StructTypeName.MEX );
    // 'constrGcodeInfoStructType:11' if( coder.target( "MATLAB" ) )
    // 'constrGcodeInfoStructType:13' else
    // 'constrGcodeInfoStructType:14' C = constrGcodeInfoStruct( params.Type, params.zspdmode,
    // params.TRAFO, ... 'constrGcodeInfoStructType:15'         params.HSC, params.G91,
    // params.G91_1, params.FeedRate, ... 'constrGcodeInfoStructType:16' params.SpindleSpeed,
    // params.gcode_source_line );
    constrGcodeInfoStruct(CurveType_Line, ZSpdMode_NN, false, false, false, true, 0.0, 0.0, 0, C);
}

} // namespace ocn

//
// File trailer for constrGcodeInfoStructType.cpp
//
// [EOF]
//
