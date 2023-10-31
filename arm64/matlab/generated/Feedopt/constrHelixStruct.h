
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrHelixStruct.h
//
// MATLAB Coder version            : 5.4
//

#ifndef CONSTRHELIXSTRUCT_H
#define CONSTRHELIXSTRUCT_H

// Include Files
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "rtwtypes.h"
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
void b_constrHelixStruct(ZSpdMode gcodeInfoStruct_zspdmode, bool gcodeInfoStruct_TRAFO,
                         bool gcodeInfoStruct_HSC, double gcodeInfoStruct_FeedRate,
                         double gcodeInfoStruct_SpindleSpeed, int gcodeInfoStruct_gcode_source_line,
                         bool gcodeInfoStruct_G91, bool gcodeInfoStruct_G91_1, int tool_toolno,
                         int tool_pocketno, const Axes *tool_offset, double tool_diameter,
                         double tool_frontangle, double tool_backangle, int tool_orientation,
                         const double R0[6], const double R1[6], const double Cprim[3],
                         double delta, const double evec[3], double theta, double pitch,
                         CurvStruct *CStrct);

extern void constrHelixStruct(GcodeInfoStruct *gcodeInfoStruct, const Tool *tool,
                              const double R0_data[], const int R0_size[1], const double R1_data[],
                              const int R1_size[1], const double Cprim[3], double delta,
                              const double evec[3], double theta, double pitch, CurvStruct *CStrct);

} // namespace ocn

#endif
//
// File trailer for constrHelixStruct.h
//
// [EOF]
//
