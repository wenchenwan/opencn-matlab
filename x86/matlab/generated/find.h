//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: find.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

#ifndef FIND_H
#define FIND_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct CurvStruct;

}

// Function Declarations
namespace ocn {
void b_binary_expand_op(int Idx2_data[], int Idx2_size[2], const CurvStruct *expl_temp,
                        const double u1_tilda_data[], const int u1_tilda_size[2]);

void binary_expand_op(int Idx2_data[], int Idx2_size[2], const CurvStruct *expl_temp,
                      const double u0_tilda_data[], const int u0_tilda_size[2]);

namespace coder {
void b_eml_find(const ::coder::array<bool, 2U> &x, int i_data[], int i_size[2]);

void c_eml_find(const bool x_data[], int x_size, int i_data[], int *i_size);

void eml_find(const ::coder::array<bool, 2U> &x, int i_data[], int i_size[2]);

} // namespace coder
} // namespace ocn

#endif
//
// File trailer for find.h
//
// [EOF]
//
