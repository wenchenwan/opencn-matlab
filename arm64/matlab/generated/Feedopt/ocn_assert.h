
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ocn_assert.h
//
// MATLAB Coder version            : 5.4
//

#ifndef OCN_ASSERT_H
#define OCN_ASSERT_H

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
void ab_ocn_assert(bool condition);

void b_ocn_assert(bool condition);

void bb_ocn_assert(bool condition);

void c_ocn_assert(bool condition, const coder::rtString *msg);

void cb_ocn_assert(bool condition);

void d_ocn_assert(bool condition);

void db_ocn_assert(bool condition);

void e_ocn_assert(bool condition);

void eb_ocn_assert(bool condition);

void f_ocn_assert(bool condition, const coder::rtString *msg);

void fb_ocn_assert(bool condition);

void g_ocn_assert(bool condition);

void gb_ocn_assert(bool condition);

void h_ocn_assert(bool condition);

void hb_ocn_assert(bool condition);

void i_ocn_assert(bool condition);

void ib_ocn_assert();

void j_ocn_assert(bool condition);

void jb_ocn_assert();

void k_ocn_assert(bool condition);

void l_ocn_assert(bool condition);

void m_ocn_assert(bool condition);

void n_ocn_assert(bool condition);

void o_ocn_assert(bool condition);

void ocn_assert(bool condition);

void p_ocn_assert(bool condition);

void q_ocn_assert(bool condition);

void r_ocn_assert(bool condition);

void s_ocn_assert(bool condition);

void t_ocn_assert(bool condition);

void u_ocn_assert(bool condition);

void v_ocn_assert(bool condition);

void w_ocn_assert(bool condition);

void x_ocn_assert(bool condition);

void y_ocn_assert(bool condition);

} // namespace ocn

#endif
//
// File trailer for ocn_assert.h
//
// [EOF]
//
