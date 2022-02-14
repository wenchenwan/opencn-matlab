//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CorrectArcCenter.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

// Include Files
#include "CorrectArcCenter.h"
#include "sinspace_data.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const double P0[2]
//                const double P1[2]
//                double C[2]
//                double *R
//                double *delta
// Return Type  : void
//
namespace ocn {
void CorrectArcCenter(const double P0[2], const double P1[2], double C[2], double *R, double *delta)
{
    double P1P0_idx_0;
    double P1P0_idx_1;
    double d;
    double z1_idx_1_tmp_tmp;
    //  [R, Cprim] = CorrectArcCenter(P0, P1, C)
    //  recalculate the center point Cprim of an arc in the plane passing by P0 and P1,
    //  C being the approximate center point
    sqrt_calls++;
    P1P0_idx_0 = P1[0] - P0[0];
    P1P0_idx_1 = P1[1] - P0[1];
    sqrt_calls++;
    *R = 0.5 * (std::sqrt(std::pow(C[0] - P0[0], 2.0) + std::pow(C[1] - P0[1], 2.0)) +
                std::sqrt(std::pow(C[0] - P1[0], 2.0) + std::pow(C[1] - P1[1], 2.0)));
    //  mean value of radius
    //
    z1_idx_1_tmp_tmp = std::pow(P1P0_idx_1, 2.0);
    sqrt_calls++;
    d = std::sqrt(std::pow(P1P0_idx_0, 2.0) + z1_idx_1_tmp_tmp);
    if (d < 1.0E-6) {
        //  do nothing if P0 and P1 are extremely close
        *delta = 0.0;
    } else {
        double Cprim1_idx_0;
        double Cprim2_idx_0;
        double a;
        double b_a;
        double b_z1_idx_0;
        double d1;
        double d2;
        double d3;
        double d4;
        double n;
        double z1_idx_0;
        sqrt_calls++;
        //  bisecting line (90° rotation)
        n = std::sqrt(z1_idx_1_tmp_tmp + std::pow(-P1P0_idx_0, 2.0));
        sqrt_calls++;
        //  unit vector on bisecting line
        //  dealing with limit cases...
        a = std::pow(*R, 2.0) - std::pow(d / 2.0, 2.0);
        if (a <= 0.0) {
            b_a = 0.0;
        } else {
            b_a = std::sqrt(a);
            sqrt_calls++;
        }
        *delta = a;
        //  midpoint
        //  two choices for the center point
        //
        sqrt_calls++;
        d1 = 0.5 * (P0[0] + P1[0]);
        d2 = b_a * (P1P0_idx_1 / n);
        d3 = d1 + d2;
        Cprim1_idx_0 = d3;
        d4 = d1 - d2;
        Cprim2_idx_0 = d4;
        z1_idx_0 = std::pow(C[0] - d3, 2.0);
        b_z1_idx_0 = std::pow(C[0] - d4, 2.0);
        d1 = 0.5 * (P0[1] + P1[1]);
        d2 = b_a * (-P1P0_idx_0 / n);
        d3 = d1 + d2;
        d4 = d1 - d2;
        sqrt_calls++;
        if (std::sqrt(z1_idx_0 + std::pow(C[1] - d3, 2.0)) <
            std::sqrt(b_z1_idx_0 + std::pow(C[1] - d4, 2.0))) {
            //  determine on which side the center point lies
            C[0] = Cprim1_idx_0;
            C[1] = d3;
        } else {
            C[0] = Cprim2_idx_0;
            C[1] = d4;
        }
    }
}

} // namespace ocn

//
// File trailer for CorrectArcCenter.cpp
//
// [EOF]
//
