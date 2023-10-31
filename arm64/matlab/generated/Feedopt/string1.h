
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: string1.h
//
// MATLAB Coder version            : 5.4
//

#ifndef STRING1_H
#define STRING1_H

// Include Files
#include "opencn_matlab_types.h"
#include "rtwtypes.h"
#include "coder_bounded_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
namespace coder {
class rtString {
  public:
    void init(Fopt val);
    void init();
    void b_init();
    ::coder::bounded_array<char, 2156U, 2U> Value;
};

} // namespace coder
} // namespace ocn

#endif
//
// File trailer for string1.h
//
// [EOF]
//
