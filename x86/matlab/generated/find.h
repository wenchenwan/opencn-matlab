//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: find.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:09:54
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
namespace coder {
class sparse;

}
} // namespace ocn

// Function Declarations
namespace ocn {
namespace coder {
void b_eml_find(const sparse *x, ::coder::array<int, 1U> &i, ::coder::array<int, 1U> &j,
                ::coder::array<double, 1U> &v);

void eml_find(const bool x_data[], int x_size, int i_data[], int *i_size);

} // namespace coder
} // namespace ocn

#endif
//
// File trailer for find.h
//
// [EOF]
//
