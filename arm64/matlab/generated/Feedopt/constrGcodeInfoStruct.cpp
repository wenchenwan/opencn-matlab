//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrGcodeInfoStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

// Include Files
#include "constrGcodeInfoStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"

// Function Definitions
//
// function [ GCodeInfoStrct ] = constrGcodeInfoStruct( Type, ...
//     ZSpdMode, trafo, HSC, G91, G91_1 , FeedRate, SpindleSpeed, ...
//     gcode_source_line )
//
// Construct a struct containing the information from the Gcode.
//
//  Inputs :
//  Type      : Type of curve
//  ZSpdMode  : Zero speed mode
//  trafo     : Flag for the trafo directive (true : on, false : off)
//  HSC       : High speed cutting (true : on, false : off)
//  Feedrate  : Feedrate of the spindle
//  SpindleSpeed : Rotation speed of the spindle
//  gcode_source_line : Line of the gcode
//  G91       : Flag for incremental mode (true : on, false : off)
//  G91_1     : Flag for incremental mode for arc center (true : on, false : off)
//
//  Outputs :
//  CStrct    : The resulting structure
//
// Arguments    : CurveType Type
//                ZSpdMode b_ZSpdMode
//                bool trafo
//                bool HSC
//                bool G91
//                bool G91_1
//                double FeedRate
//                double SpindleSpeed
//                int gcode_source_line
//                GcodeInfoStruct *GCodeInfoStrct
// Return Type  : void
//
namespace ocn {
void constrGcodeInfoStruct(CurveType Type, ZSpdMode b_ZSpdMode, bool trafo, bool HSC, bool G91,
                           bool G91_1, double FeedRate, double SpindleSpeed, int gcode_source_line,
                           GcodeInfoStruct *GCodeInfoStrct)
{
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'constrGcodeInfoStruct:20' GCodeInfoStrct = struct( 'Type', Type, ...
    // 'constrGcodeInfoStruct:21'                 'zspdmode', ZSpdMode, ...
    // 'constrGcodeInfoStruct:22'                 'TRAFO', trafo, ...
    // 'constrGcodeInfoStruct:23'                 'HSC', HSC, ...
    // 'constrGcodeInfoStruct:24'                 'FeedRate', FeedRate,...
    // 'constrGcodeInfoStruct:25'                 'SpindleSpeed', SpindleSpeed,...
    // 'constrGcodeInfoStruct:26'                 'gcode_source_line', gcode_source_line, ...
    // 'constrGcodeInfoStruct:27'                 'G91', G91, ...
    // 'constrGcodeInfoStruct:28'                 'G91_1', G91_1 ...
    // 'constrGcodeInfoStruct:29'                 );
    GCodeInfoStrct->Type = Type;
    GCodeInfoStrct->zspdmode = b_ZSpdMode;
    GCodeInfoStrct->TRAFO = trafo;
    GCodeInfoStrct->HSC = HSC;
    GCodeInfoStrct->FeedRate = FeedRate;
    GCodeInfoStrct->SpindleSpeed = SpindleSpeed;
    GCodeInfoStrct->gcode_source_line = gcode_source_line;
    GCodeInfoStrct->G91 = G91;
    GCodeInfoStrct->G91_1 = G91_1;
    // 'constrGcodeInfoStruct:31' coder.cstructname( GCodeInfoStrct, StructTypeName.GCodeInfo );
}

} // namespace ocn

//
// File trailer for constrGcodeInfoStruct.cpp
//
// [EOF]
//
