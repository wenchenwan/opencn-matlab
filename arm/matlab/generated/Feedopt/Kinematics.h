//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Kinematics.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:45:22
//

#ifndef KINEMATICS_H
#define KINEMATICS_H

// Include Files
#include "rtwtypes.h"
#include "string1.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
class Kinematics {
  public:
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
    coder::rtString type;
    ::coder::array<double, 1U> parameters;
};

} // namespace ocn

#endif
//
// File trailer for Kinematics.h
//
// [EOF]
//
