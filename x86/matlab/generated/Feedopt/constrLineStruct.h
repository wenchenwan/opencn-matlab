
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrLineStruct.h
//
// MATLAB Coder version            : 5.4
//

#ifndef CONSTRLINESTRUCT_H
#define CONSTRLINESTRUCT_H

// Include Files
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
extern void constrLineStruct(GcodeInfoStruct *gcodeInfoStruct, const Tool *tool,
                             const double R0_data[], const int R0_size[1], const double R1_data[],
                             const int R1_size[1], CurvStruct *CStrct);

}

#endif
//
// File trailer for constrLineStruct.h
//
// [EOF]
//
