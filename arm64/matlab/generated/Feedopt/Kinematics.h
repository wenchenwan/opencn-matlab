
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Kinematics.h
//
// MATLAB Coder version            : 5.4
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
    void init(const char b_type[8], const double parameters_data[], int parameters_size);
    void relative(const ::coder::array<double, 1U> &r_j, const ::coder::array<double, 1U> &v_j,
                  const ::coder::array<double, 1U> &a_j, const ::coder::array<double, 1U> &j_j,
                  ::coder::array<double, 1U> &r_t, ::coder::array<double, 1U> &v_t,
                  ::coder::array<double, 1U> &a_t, ::coder::array<double, 1U> &j_t) const;
    void v_joint(const ::coder::array<double, 1U> &r_t, const ::coder::array<double, 1U> &v_t,
                 ::coder::array<double, 1U> &v_j) const;
    void joint(const ::coder::array<double, 2U> &r_t, const ::coder::array<double, 2U> &v_t,
               const ::coder::array<double, 2U> &a_t, const ::coder::array<double, 2U> &j_t,
               ::coder::array<double, 2U> &r_j, ::coder::array<double, 2U> &v_j,
               ::coder::array<double, 2U> &a_j, ::coder::array<double, 2U> &j_j) const;
    void v_relative(const ::coder::array<double, 2U> &r_j, const ::coder::array<double, 2U> &v_j,
                    ::coder::array<double, 2U> &v_t) const;
    void joint(const ::coder::array<double, 2U> &r_t, const ::coder::array<double, 2U> &v_t,
               const ::coder::array<double, 2U> &a_t, ::coder::array<double, 2U> &r_j,
               ::coder::array<double, 2U> &v_j, ::coder::array<double, 2U> &a_j) const;
    void r_joint(const ::coder::array<double, 2U> &r_t, ::coder::array<double, 2U> &r_j) const;
    void r_relative(const ::coder::array<double, 2U> &r_j, ::coder::array<double, 2U> &r_t) const;
    void v_joint(const ::coder::array<double, 2U> &r_t, const ::coder::array<double, 2U> &v_t,
                 ::coder::array<double, 2U> &v_j) const;
    void a_joint(const ::coder::array<double, 2U> &r_t, const ::coder::array<double, 2U> &v_t,
                 const ::coder::array<double, 2U> &a_t, ::coder::array<double, 2U> &a_j) const;
    void a_relative(const ::coder::array<double, 2U> &r_j, const ::coder::array<double, 2U> &v_j,
                    const ::coder::array<double, 2U> &a_j, ::coder::array<double, 2U> &a_t) const;
    void j_joint(const ::coder::array<double, 2U> &r_t, const ::coder::array<double, 2U> &v_t,
                 const ::coder::array<double, 2U> &a_t, const ::coder::array<double, 2U> &j_t,
                 ::coder::array<double, 2U> &j_j) const;
    void j_relative(const ::coder::array<double, 2U> &r_j, const ::coder::array<double, 2U> &v_j,
                    const ::coder::array<double, 2U> &a_j, const ::coder::array<double, 2U> &j_j,
                    ::coder::array<double, 2U> &j_t) const;
    void relative(const ::coder::array<double, 2U> &r_j, const ::coder::array<double, 2U> &v_j,
                  const ::coder::array<double, 2U> &a_j, const ::coder::array<double, 2U> &j_j,
                  ::coder::array<double, 2U> &r_t, ::coder::array<double, 2U> &v_t,
                  ::coder::array<double, 2U> &a_t, ::coder::array<double, 2U> &j_t) const;
    void set_tool_length(double tool_length);
    void set_params(const double parameters_data[], int parameters_size);
    void set_type(const char b_type[8]);
    Kinematics();
    ~Kinematics();
    char type[8];
    ::coder::array<double, 1U> parameters;
    double indM[3];
    double indT[3];
    double indP[3];
};

} // namespace ocn

#endif
//
// File trailer for Kinematics.h
//
// [EOF]
//
