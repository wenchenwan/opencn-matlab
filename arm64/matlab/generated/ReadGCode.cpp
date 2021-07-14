//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ReadGCode.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "ReadGCode.h"
#include "ConstrLineStruct.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include <algorithm>

// Function Definitions
//
// coder.extrinsic('ReadGCode_mex');
//  Wrapper for pulling the next gcode line from the interpreter
//
// Arguments    : const char filename[1024]
// Return Type  : int
//
namespace ocn {
int ReadGCode(const char filename[1024])
{
    CurvStruct b_CurvStruct;
    double dv[3];
    double dv1[3];
    char b_cv[1025];
    dv[0] = 1.0;
    dv1[0] = 4.0;
    dv[1] = 2.0;
    dv1[1] = 5.0;
    dv[2] = 3.0;
    dv1[2] = 6.0;
    ConstrLineStruct(dv, dv1, 0.2, ZSpdMode_NN, &b_CurvStruct);
    std::copy(&filename[0], &filename[1024], &b_cv[0]);
    b_cv[1024] = '\x00';
    return c_open_gcode(&b_cv[0], &b_CurvStruct);
}

} // namespace ocn

//
// File trailer for ReadGCode.cpp
//
// [EOF]
//
