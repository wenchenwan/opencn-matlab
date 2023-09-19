//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: setMachineAxisInConfig.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 19-Sep-2023 12:24:15
//

#ifndef SETMACHINEAXISINCONFIG_H
#define SETMACHINEAXISINCONFIG_H

// Include Files
#include "opencn_matlab_types.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void b_setMachineAxisInConfig(b_FeedoptConfig *cfg, const bool maskTot_data[]);

extern void setMachineAxisInConfig(FeedoptConfig *cfg, const bool maskTot[6]);

} // namespace ocn

#endif
//
// File trailer for setMachineAxisInConfig.h
//
// [EOF]
//
