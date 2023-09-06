//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: find.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Sep-2023 13:36:32
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
// Function Declarations
namespace ocn {
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
