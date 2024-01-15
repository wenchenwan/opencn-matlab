
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calc_t_nk_kappa.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "calc_t_nk_kappa.h"
#include "norm.h"
#include "ocn_assert.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 1U> &in1, const ::coder::array<double, 1U> &in2,
                             const ::coder::array<double, 1U> &in3, double in4, double in5);

}

// Function Definitions
//
// Arguments    : ::coder::array<double, 1U> &in1
//                const ::coder::array<double, 1U> &in2
//                const ::coder::array<double, 1U> &in3
//                double in4
//                double in5
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(::coder::array<double, 1U> &in1, const ::coder::array<double, 1U> &in2,
                             const ::coder::array<double, 1U> &in3, double in4, double in5)
{
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (in3.size(0) == 1) {
        i = in2.size(0);
    } else {
        i = in3.size(0);
    }
    in1.set_size(i);
    stride_0_0 = (in2.size(0) != 1);
    stride_1_0 = (in3.size(0) != 1);
    if (in3.size(0) == 1) {
        loop_ub = in2.size(0);
    } else {
        loop_ub = in3.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        in1[i1] = (in2[i1 * stride_0_0] - in3[i1 * stride_1_0] * in4 / in5) / in5;
    }
}

//
// function [ t, nk, kappa ] = calc_t_nk_kappa( rD1, rD2 )
//
// Arguments    : const double rD1[6]
//                const double rD2[6]
//                double t[6]
//                double nk[6]
//                double *kappa
// Return Type  : void
//
void calc_t_nk_kappa(const double rD1[6], const double rD2[6], double t[6], double nk[6],
                     double *kappa)
{
    double a;
    double b_scale;
    double dot_rD1_rD2;
    double norm_rD1;
    double norm_rD1_2;
    double num;
    double scale;
    double unnamed_idx_0;
    //  computes the local Frenet frame (t, n, b) of a curve in R^n
    //  [t, nk, kappa] = calc_t_nk_kappa(rD1, rD2)
    //  where rD1 is the first derivative and rD2 the second one
    // 'calc_t_nk_kappa:5' norm_rD1    = vecnorm( rD1 );
    norm_rD1 = 0.0;
    scale = 3.3121686421112381E-170;
    // 'calc_t_nk_kappa:6' norm_rD1_2  = norm_rD1.^2;
    // 'calc_t_nk_kappa:7' norm_rD1_3  = norm_rD1_2 .* norm_rD1;
    // 'calc_t_nk_kappa:8' norm_rD2    = vecnorm( rD2 );
    a = 0.0;
    b_scale = 3.3121686421112381E-170;
    // 'calc_t_nk_kappa:9' norm_rD2_2  = norm_rD2.^2;
    // 'calc_t_nk_kappa:10' dot_rD1_rD2 = dot( rD2, rD1 );
    dot_rD1_rD2 = 0.0;
    for (int k{0}; k < 6; k++) {
        double absxk;
        double b_absxk;
        double d;
        double d1;
        d = rD1[k];
        absxk = std::abs(d);
        if (absxk > scale) {
            double b_t;
            b_t = scale / absxk;
            norm_rD1 = norm_rD1 * b_t * b_t + 1.0;
            scale = absxk;
        } else {
            double b_t;
            b_t = absxk / scale;
            norm_rD1 += b_t * b_t;
        }
        d1 = rD2[k];
        b_absxk = std::abs(d1);
        if (b_absxk > b_scale) {
            double c_t;
            c_t = b_scale / b_absxk;
            a = a * c_t * c_t + 1.0;
            b_scale = b_absxk;
        } else {
            double c_t;
            c_t = b_absxk / b_scale;
            a += c_t * c_t;
        }
        dot_rD1_rD2 += d1 * d;
    }
    norm_rD1 = scale * std::sqrt(norm_rD1);
    norm_rD1_2 = norm_rD1 * norm_rD1;
    a = b_scale * std::sqrt(a);
    //  tangential unit vector
    // 'calc_t_nk_kappa:13' t = rD1 / norm_rD1;
    //  Normal unit vector
    // 'calc_t_nk_kappa:15' nk          = ( rD2 - rD1 .* dot_rD1_rD2 ./ norm_rD1_2 ) ./ norm_rD1_2;
    for (int i{0}; i < 6; i++) {
        double d2;
        d2 = rD1[i];
        t[i] = d2 / norm_rD1;
        nk[i] = (rD2[i] - d2 * dot_rD1_rD2 / norm_rD1_2) / norm_rD1_2;
    }
    //  Curvature
    // 'calc_t_nk_kappa:17' num         = norm_rD2_2 .* norm_rD1_2 - dot_rD1_rD2.^2;
    num = a * a * norm_rD1_2 - dot_rD1_rD2 * dot_rD1_rD2;
    // 'calc_t_nk_kappa:19' num( num < 0 ) = 0;
    unnamed_idx_0 = num;
    if (num < 0.0) {
        unnamed_idx_0 = 0.0;
    }
    // 'calc_t_nk_kappa:20' kappa       = mysqrt( num ) ./ norm_rD1_3;
    //  mysqrt : Custom implementation of the sqrt method.
    //
    //  Inputs :
    //    x : Value used for the computation
    //  Outputs :
    //    y : Resulting value
    //
    // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
    // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
    ocn_assert(unnamed_idx_0 >= 0.0);
    // 'mysqrt:11' y = sqrt(x);
    *kappa = std::sqrt(unnamed_idx_0) / (norm_rD1_2 * norm_rD1);
}

//
// function [ t, nk, kappa ] = calc_t_nk_kappa( rD1, rD2 )
//
// Arguments    : const ::coder::array<double, 1U> &rD1
//                const ::coder::array<double, 1U> &rD2
//                ::coder::array<double, 1U> &t
//                ::coder::array<double, 1U> &nk
//                double *kappa
// Return Type  : void
//
void calc_t_nk_kappa(const ::coder::array<double, 1U> &rD1, const ::coder::array<double, 1U> &rD2,
                     ::coder::array<double, 1U> &t, ::coder::array<double, 1U> &nk, double *kappa)
{
    double a;
    double dot_rD1_rD2;
    double norm_rD1;
    double norm_rD1_2;
    double num;
    double unnamed_idx_0;
    int loop_ub;
    //  computes the local Frenet frame (t, n, b) of a curve in R^n
    //  [t, nk, kappa] = calc_t_nk_kappa(rD1, rD2)
    //  where rD1 is the first derivative and rD2 the second one
    // 'calc_t_nk_kappa:5' norm_rD1    = vecnorm( rD1 );
    norm_rD1 = coder::b_norm(rD1);
    // 'calc_t_nk_kappa:6' norm_rD1_2  = norm_rD1.^2;
    norm_rD1_2 = norm_rD1 * norm_rD1;
    // 'calc_t_nk_kappa:7' norm_rD1_3  = norm_rD1_2 .* norm_rD1;
    // 'calc_t_nk_kappa:8' norm_rD2    = vecnorm( rD2 );
    a = coder::b_norm(rD2);
    // 'calc_t_nk_kappa:9' norm_rD2_2  = norm_rD2.^2;
    // 'calc_t_nk_kappa:10' dot_rD1_rD2 = dot( rD2, rD1 );
    dot_rD1_rD2 = 0.0;
    if (rD2.size(0) >= 1) {
        int ixlast;
        ixlast = rD2.size(0);
        for (int k{0}; k < ixlast; k++) {
            dot_rD1_rD2 += rD2[k] * rD1[k];
        }
    }
    //  tangential unit vector
    // 'calc_t_nk_kappa:13' t = rD1 / norm_rD1;
    t.set_size(rD1.size(0));
    loop_ub = rD1.size(0);
    for (int i{0}; i < loop_ub; i++) {
        t[i] = rD1[i] / norm_rD1;
    }
    //  Normal unit vector
    // 'calc_t_nk_kappa:15' nk          = ( rD2 - rD1 .* dot_rD1_rD2 ./ norm_rD1_2 ) ./ norm_rD1_2;
    if (rD2.size(0) == rD1.size(0)) {
        int b_loop_ub;
        nk.set_size(rD2.size(0));
        b_loop_ub = rD2.size(0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            nk[i1] = (rD2[i1] - rD1[i1] * dot_rD1_rD2 / norm_rD1_2) / norm_rD1_2;
        }
    } else {
        binary_expand_op(nk, rD2, rD1, dot_rD1_rD2, norm_rD1_2);
    }
    //  Curvature
    // 'calc_t_nk_kappa:17' num         = norm_rD2_2 .* norm_rD1_2 - dot_rD1_rD2.^2;
    num = a * a * norm_rD1_2 - dot_rD1_rD2 * dot_rD1_rD2;
    // 'calc_t_nk_kappa:19' num( num < 0 ) = 0;
    unnamed_idx_0 = num;
    if (num < 0.0) {
        unnamed_idx_0 = 0.0;
    }
    // 'calc_t_nk_kappa:20' kappa       = mysqrt( num ) ./ norm_rD1_3;
    //  mysqrt : Custom implementation of the sqrt method.
    //
    //  Inputs :
    //    x : Value used for the computation
    //  Outputs :
    //    y : Resulting value
    //
    // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
    // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
    ocn_assert(unnamed_idx_0 >= 0.0);
    // 'mysqrt:11' y = sqrt(x);
    *kappa = std::sqrt(unnamed_idx_0) / (norm_rD1_2 * norm_rD1);
}

} // namespace ocn

//
// File trailer for calc_t_nk_kappa.cpp
//
// [EOF]
//
