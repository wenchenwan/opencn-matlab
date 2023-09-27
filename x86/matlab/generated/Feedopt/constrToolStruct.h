//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrToolStruct.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 09:15:18
//

#ifndef CONSTRTOOLSTRUCT_H
#define CONSTRTOOLSTRUCT_H

// Include Files
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void b_constrToolStruct(int *CStruct_toolno, int *CStruct_pocketno, double *CStruct_offset_x,
                        double *CStruct_offset_y, double *CStruct_offset_z,
                        double *CStruct_offset_a, double *CStruct_offset_b,
                        double *CStruct_offset_c, double *CStruct_offset_u,
                        double *CStruct_offset_v, double *CStruct_offset_w,
                        double *CStruct_diameter, double *CStruct_frontangle,
                        double *CStruct_backangle, int *CStruct_orientation);

extern void constrToolStruct(int toolno, int pocketno, const Axes *offset, double diameter,
                             double frontangle, double backangle, int orientation, Tool *CStruct);

} // namespace ocn

#endif
//
// File trailer for constrToolStruct.h
//
// [EOF]
//
