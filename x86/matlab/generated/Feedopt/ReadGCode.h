
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ReadGCode.h
//
// MATLAB Coder version            : 5.4
//

#ifndef READGCODE_H
#define READGCODE_H

// Include Files
#include "opencn_matlab_types.h"
#include "opencn_matlab_types111.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void ReadGCode(const FeedoptConfig cfg, ReadGCodeCmd cmd, const char filename_data[],
                      const int filename_size[2], ReadGCodeError *status, CurvStruct *c_CurvStruct,
                      MsgStruct *err_msg);

void b_ReadGCode(ReadGCodeError *status, CurvStruct *c_CurvStruct);

} // namespace ocn

#endif
//
// File trailer for ReadGCode.h
//
// [EOF]
//
