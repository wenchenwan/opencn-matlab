
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
    void get_params(double params_data[], int *params_size) const;
    void get_type(char b_type[8]) const;
    void r_relative(const double r_j_data[], int r_j_size, double r_t_data[], int *r_t_size) const;
    void r_relative(const ::coder::array<double, 2U> &r_j, ::coder::array<double, 2U> &r_t) const;
    void r_joint(const double r_t_data[], int r_t_size, double r_j_data[], int *r_j_size) const;
    void r_joint(const ::coder::array<double, 2U> &r_t, ::coder::array<double, 2U> &r_j) const;
    void v_relative(const double r_j_data[], int r_j_size, const double v_j_data[], int v_j_size,
                    double v_t_data[], int *v_t_size) const;
    void v_relative(const ::coder::array<double, 2U> &r_j, const ::coder::array<double, 2U> &v_j,
                    ::coder::array<double, 2U> &v_t) const;
    void v_joint(const ::coder::array<double, 1U> &r_t, const ::coder::array<double, 1U> &v_t,
                 ::coder::array<double, 1U> &v_j) const;
    void v_joint(const ::coder::array<double, 2U> &r_t, const ::coder::array<double, 2U> &v_t,
                 ::coder::array<double, 2U> &v_j) const;
    void a_relative(const double r_j_data[], int r_j_size, const double v_j_data[], int v_j_size,
                    const double a_j_data[], int a_j_size, double a_t_data[], int *a_t_size) const;
    void a_relative(const ::coder::array<double, 2U> &r_j, const ::coder::array<double, 2U> &v_j,
                    const ::coder::array<double, 2U> &a_j, ::coder::array<double, 2U> &a_t) const;
    void a_joint(const double r_t_data[], int r_t_size, const double v_t_data[], int v_t_size,
                 const double a_t_data[], int a_t_size, double a_j_data[], int *a_j_size) const;
    void a_joint(const ::coder::array<double, 2U> &r_t, const ::coder::array<double, 2U> &v_t,
                 const ::coder::array<double, 2U> &a_t, ::coder::array<double, 2U> &a_j) const;
    void j_relative(const double r_j_data[], int r_j_size, const double v_j_data[], int v_j_size,
                    const double a_j_data[], int a_j_size, const double j_j_data[], int j_j_size,
                    double j_t_data[], int *j_t_size) const;
    void j_relative(const ::coder::array<double, 2U> &r_j, const ::coder::array<double, 2U> &v_j,
                    const ::coder::array<double, 2U> &a_j, const ::coder::array<double, 2U> &j_j,
                    ::coder::array<double, 2U> &j_t) const;
    void j_joint(const double r_t_data[], int r_t_size, const double v_t_data[], int v_t_size,
                 const double a_t_data[], int a_t_size, const double j_t_data[], int j_t_size,
                 double j_j_data[], int *j_j_size) const;
    void j_joint(const ::coder::array<double, 2U> &r_t, const ::coder::array<double, 2U> &v_t,
                 const ::coder::array<double, 2U> &a_t, const ::coder::array<double, 2U> &j_t,
                 ::coder::array<double, 2U> &j_j) const;
    void relative(const ::coder::array<double, 1U> &r_j, const ::coder::array<double, 1U> &v_j,
                  const ::coder::array<double, 1U> &a_j, const ::coder::array<double, 1U> &j_j,
                  ::coder::array<double, 1U> &r_t, ::coder::array<double, 1U> &v_t,
                  ::coder::array<double, 1U> &a_t, ::coder::array<double, 1U> &j_t) const;
    void joint(const double r_t_data[], int r_t_size, const double v_t_data[], int v_t_size,
               const double a_t_data[], int a_t_size, const double j_t_data[], int j_t_size,
               double r_j_data[], int *r_j_size, double v_j_data[], int *v_j_size,
               double a_j_data[], int *a_j_size, double j_j_data[], int *j_j_size) const;
    void joint(const ::coder::array<double, 2U> &r_t, const ::coder::array<double, 2U> &v_t,
               const ::coder::array<double, 2U> &a_t, const ::coder::array<double, 2U> &j_t,
               ::coder::array<double, 2U> &r_j, ::coder::array<double, 2U> &v_j,
               ::coder::array<double, 2U> &a_j, ::coder::array<double, 2U> &j_j) const;
    void joint(const ::coder::array<double, 2U> &r_t, const ::coder::array<double, 2U> &v_t,
               const ::coder::array<double, 2U> &a_t, ::coder::array<double, 2U> &r_j,
               ::coder::array<double, 2U> &v_j, ::coder::array<double, 2U> &a_j) const;
    void set_params(const double parameters_data[], int parameters_size);
    void set_type(const char b_type[8]);
    void set_machine_offset(const double offset[3]);
    void set_piece_offset(const double offset[3]);
    void set_tool_offset(const double offset[3]);
    void set_tool_length(double tool_length);
    void set_piece_offset();
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
