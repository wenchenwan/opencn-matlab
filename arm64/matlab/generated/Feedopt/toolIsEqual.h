//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: toolIsEqual.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:24:15
//

#ifndef TOOLISEQUAL_H
#define TOOLISEQUAL_H

// Include Files
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
bool toolIsEqual(int tool1_toolno, int tool1_pocketno, double tool1_offset_x, double tool1_offset_y,
                 double tool1_offset_z, double tool1_offset_a, double tool1_offset_b,
                 double tool1_offset_c, double tool1_offset_u, double tool1_offset_v,
                 double tool1_offset_w, double tool1_diameter, double tool1_frontangle,
                 double tool1_backangle, int tool1_orientation, int tool2_toolno,
                 int tool2_pocketno, const Axes *tool2_offset, double tool2_diameter,
                 double tool2_frontangle, double tool2_backangle, int tool2_orientation);

}

#endif
//
// File trailer for toolIsEqual.h
//
// [EOF]
//
