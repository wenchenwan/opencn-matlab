//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrTransP5Struct.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 15:40:50
//

#ifndef CONSTRTRANSP5STRUCT_H
#define CONSTRTRANSP5STRUCT_H

// Include Files
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types21.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct Axes;

}

// Function Declarations
namespace ocn {
void b_constrTransP5Struct(bool gcodeInfoStruct_TRAFO, bool gcodeInfoStruct_HSC,
                           double gcodeInfoStruct_FeedRate, double gcodeInfoStruct_SpindleSpeed,
                           int gcodeInfoStruct_gcode_source_line, bool gcodeInfoStruct_G91,
                           bool gcodeInfoStruct_G91_1, int tool_toolno, int tool_pocketno,
                           const Axes *tool_offset, double tool_diameter, double tool_frontangle,
                           double tool_backangle, int tool_orientation, const double R0[6],
                           const double R1[6], const double CoeffP5[6][6], CurvStruct *CStrct);

extern void constrTransP5Struct(GcodeInfoStruct *gcodeInfoStruct, const Tool *tool,
                                const double R0[6], const double R1[6],
                                const ::coder::array<double, 2U> &CoeffP5, CurvStruct *CStrct);

} // namespace ocn

#endif
//
// File trailer for constrTransP5Struct.h
//
// [EOF]
//
