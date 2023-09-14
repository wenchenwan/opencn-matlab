//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: toolIsEqual.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 13:07:08
//

// Include Files
#include "toolIsEqual.h"
#include "opencn_matlab_types3.h"

// Function Definitions
//
// function [isEqual] = toolIsEqual(tool1, tool2)
//
// Check the tools are equals
//
// Arguments    : int tool1_toolno
//                int tool1_pocketno
//                double tool1_offset_x
//                double tool1_offset_y
//                double tool1_offset_z
//                double tool1_offset_a
//                double tool1_offset_b
//                double tool1_offset_c
//                double tool1_offset_u
//                double tool1_offset_v
//                double tool1_offset_w
//                double tool1_diameter
//                double tool1_frontangle
//                double tool1_backangle
//                int tool1_orientation
//                int tool2_toolno
//                int tool2_pocketno
//                const Axes *tool2_offset
//                double tool2_diameter
//                double tool2_frontangle
//                double tool2_backangle
//                int tool2_orientation
// Return Type  : bool
//
namespace ocn {
bool toolIsEqual(int tool1_toolno, int tool1_pocketno, double tool1_offset_x, double tool1_offset_y,
                 double tool1_offset_z, double tool1_offset_a, double tool1_offset_b,
                 double tool1_offset_c, double tool1_offset_u, double tool1_offset_v,
                 double tool1_offset_w, double tool1_diameter, double tool1_frontangle,
                 double tool1_backangle, int tool1_orientation, int tool2_toolno,
                 int tool2_pocketno, const Axes *tool2_offset, double tool2_diameter,
                 double tool2_frontangle, double tool2_backangle, int tool2_orientation)
{
    bool isEqual;
    // 'toolIsEqual:3' isEqual = false;
    isEqual = false;
    // 'toolIsEqual:5' if( tool1.toolno        ~= tool2.toolno )
    if ((tool1_toolno == tool2_toolno) && (tool1_pocketno == tool2_pocketno) &&
        (tool1_diameter == tool2_diameter) && (tool1_frontangle == tool2_frontangle) &&
        (tool1_backangle == tool2_backangle) && (tool1_orientation == tool2_orientation) &&
        (tool1_offset_x == tool2_offset->x) && (tool1_offset_y == tool2_offset->y) &&
        (tool1_offset_z == tool2_offset->z) && (tool1_offset_a == tool2_offset->a) &&
        (tool1_offset_b == tool2_offset->b) && (tool1_offset_c == tool2_offset->c) &&
        (tool1_offset_u == tool2_offset->u) && (tool1_offset_v == tool2_offset->v) &&
        (tool1_offset_w == tool2_offset->w)) {
        // 'toolIsEqual:6' if( tool1.pocketno      ~= tool2.pocketno )
        // 'toolIsEqual:7' if( tool1.diameter      ~= tool2.diameter )
        // 'toolIsEqual:8' if( tool1.frontangle    ~= tool2.frontangle )
        // 'toolIsEqual:9' if( tool1.backangle     ~= tool2.backangle )
        // 'toolIsEqual:10' if( tool1.orientation   ~= tool2.orientation )
        // 'toolIsEqual:11' if( tool1.offset.x      ~= tool2.offset.x )
        // 'toolIsEqual:12' if( tool1.offset.y      ~= tool2.offset.y )
        // 'toolIsEqual:13' if( tool1.offset.z      ~= tool2.offset.z )
        // 'toolIsEqual:14' if( tool1.offset.a      ~= tool2.offset.a )
        // 'toolIsEqual:15' if( tool1.offset.b      ~= tool2.offset.b )
        // 'toolIsEqual:16' if( tool1.offset.c      ~= tool2.offset.c )
        // 'toolIsEqual:17' if( tool1.offset.u      ~= tool2.offset.u )
        // 'toolIsEqual:18' if( tool1.offset.v      ~= tool2.offset.v )
        // 'toolIsEqual:19' if( tool1.offset.w      ~= tool2.offset.w )
        // 'toolIsEqual:21' isEqual = true;
        isEqual = true;
    }
    return isEqual;
}

} // namespace ocn

//
// File trailer for toolIsEqual.cpp
//
// [EOF]
//
