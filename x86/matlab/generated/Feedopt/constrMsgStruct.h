
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrMsgStruct.h
//
// MATLAB Coder version            : 5.4
//

#ifndef CONSTRMSGSTRUCT_H
#define CONSTRMSGSTRUCT_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
namespace coder {
class rtString;

}
} // namespace ocn

// Function Declarations
namespace ocn {
void constrMsgStruct(const coder::rtString *msg, char CStruct_msg[2048], double *CStruct_size);

}

#endif
//
// File trailer for constrMsgStruct.h
//
// [EOF]
//
