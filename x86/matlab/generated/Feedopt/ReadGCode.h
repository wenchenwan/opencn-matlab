//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ReadGCode.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:13:50
//

#ifndef READGCODE_H
#define READGCODE_H

// Include Files
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void ReadGCode(ReadGCodeCmd cmd, const char filename_data[], const int filename_size[2],
                      int *status, CurvStruct *b_CurvStruct);

}

#endif
//
// File trailer for ReadGCode.h
//
// [EOF]
//
