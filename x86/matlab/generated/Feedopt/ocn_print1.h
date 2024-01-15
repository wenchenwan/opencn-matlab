
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ocn_print1.h
//
// MATLAB Coder version            : 5.4
//

#ifndef OCN_PRINT1_H
#define OCN_PRINT1_H

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
void b_ocn_print(bool condition);

void c_ocn_print(bool condition);

void d_ocn_print(bool condition);

void e_ocn_print(bool condition);

void f_ocn_print(bool condition, const coder::rtString *msg);

void g_ocn_print(bool condition, const coder::rtString *msg);

void h_ocn_print(bool condition, const coder::rtString *msg);

void i_ocn_print(bool condition, const coder::rtString *msg);

void j_ocn_print(bool condition);

void k_ocn_print(bool condition, const coder::rtString *msg);

void ocn_print(const coder::rtString *msg);

} // namespace ocn

#endif
//
// File trailer for ocn_print1.h
//
// [EOF]
//
