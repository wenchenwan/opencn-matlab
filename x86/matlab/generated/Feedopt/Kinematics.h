//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Kinematics.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:07:54
//

#ifndef KINEMATICS_H
#define KINEMATICS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
class Kinematics {
  public:
    void init(const char b_type[5], const double parameters_data[], int parameters_size);
    void v_joint(const ::coder::array<double, 1U> &r_r, const ::coder::array<double, 1U> &v_r,
                 ::coder::array<double, 1U> &v_a) const;
    void joint(const ::coder::array<double, 2U> &r_r, const ::coder::array<double, 2U> &v_r,
               const ::coder::array<double, 2U> &a_r, const ::coder::array<double, 2U> &j_r,
               ::coder::array<double, 2U> &r_a, ::coder::array<double, 2U> &v_a,
               ::coder::array<double, 2U> &a_a, ::coder::array<double, 2U> &j_a) const;
    void v_relative(const ::coder::array<double, 2U> &r_a, const ::coder::array<double, 2U> &v_a,
                    ::coder::array<double, 2U> &v_r) const;
    void joint(const ::coder::array<double, 2U> &r_r, const ::coder::array<double, 2U> &v_r,
               const ::coder::array<double, 2U> &a_r, ::coder::array<double, 2U> &r_a,
               ::coder::array<double, 2U> &v_a, ::coder::array<double, 2U> &a_a) const;
    Kinematics();
    ~Kinematics();
    char type[5];
    ::coder::array<double, 1U> parameters;
};

} // namespace ocn

#endif
//
// File trailer for Kinematics.h
//
// [EOF]
//
