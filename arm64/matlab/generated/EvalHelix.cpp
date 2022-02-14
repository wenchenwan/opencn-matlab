//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalHelix.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

// Include Files
#include "EvalHelix.h"
#include "c_assert.h"
#include "sinspace_data.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"
#include <cmath>

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &b,
                             const ::coder::array<double, 2U> &cphiTCP0,
                             const ::coder::array<double, 2U> &sphiTEcrCP0, double a,
                             const double CurvStruct_evec[3],
                             const ::coder::array<double, 2U> &phi_vec);

static void binary_expand_op(::coder::array<double, 2U> &a, double CurvStruct_theta,
                             const ::coder::array<double, 2U> &sphiTCP0,
                             const ::coder::array<double, 2U> &cphiTEcrCP0);

static void binary_expand_op(::coder::array<double, 2U> &r3D, double a,
                             const ::coder::array<double, 2U> &sphiTCP0, double b_a,
                             const ::coder::array<double, 2U> &cphiTEcrCP0);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &b
//                const ::coder::array<double, 2U> &cphiTCP0
//                const ::coder::array<double, 2U> &sphiTEcrCP0
//                double a
//                const double CurvStruct_evec[3]
//                const ::coder::array<double, 2U> &phi_vec
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &b,
                             const ::coder::array<double, 2U> &cphiTCP0,
                             const ::coder::array<double, 2U> &sphiTEcrCP0, double a,
                             const double CurvStruct_evec[3],
                             const ::coder::array<double, 2U> &phi_vec)
{
    ::coder::array<double, 2U> b_a;
    int aux_0_1;
    int aux_1_1;
    int aux_2_1;
    int b_loop_ub;
    int i1;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    int stride_2_1;
    b_a.set_size(3, phi_vec.size(1));
    loop_ub = phi_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        b_a[3 * i] = a * CurvStruct_evec[0] * phi_vec[i];
        b_a[3 * i + 1] = a * CurvStruct_evec[1] * phi_vec[i];
        b_a[3 * i + 2] = a * CurvStruct_evec[2] * phi_vec[i];
    }
    if (b_a.size(1) == 1) {
        if (sphiTEcrCP0.size(1) == 1) {
            i1 = cphiTCP0.size(1);
        } else {
            i1 = sphiTEcrCP0.size(1);
        }
    } else {
        i1 = b_a.size(1);
    }
    b.set_size(3, i1);
    stride_0_1 = (cphiTCP0.size(1) != 1);
    stride_1_1 = (sphiTEcrCP0.size(1) != 1);
    stride_2_1 = (b_a.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    if (b_a.size(1) == 1) {
        if (sphiTEcrCP0.size(1) == 1) {
            b_loop_ub = cphiTCP0.size(1);
        } else {
            b_loop_ub = sphiTEcrCP0.size(1);
        }
    } else {
        b_loop_ub = b_a.size(1);
    }
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        b[3 * i2] = (cphiTCP0[3 * aux_0_1] + sphiTEcrCP0[3 * aux_1_1]) + b_a[3 * aux_2_1];
        b[3 * i2 + 1] =
            (cphiTCP0[3 * aux_0_1 + 1] + sphiTEcrCP0[3 * aux_1_1 + 1]) + b_a[3 * aux_2_1 + 1];
        b[3 * i2 + 2] =
            (cphiTCP0[3 * aux_0_1 + 2] + sphiTEcrCP0[3 * aux_1_1 + 2]) + b_a[3 * aux_2_1 + 2];
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &a
//                double CurvStruct_theta
//                const ::coder::array<double, 2U> &sphiTCP0
//                const ::coder::array<double, 2U> &cphiTEcrCP0
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 2U> &a, double CurvStruct_theta,
                             const ::coder::array<double, 2U> &sphiTCP0,
                             const ::coder::array<double, 2U> &cphiTEcrCP0)
{
    int aux_0_1;
    int aux_1_1;
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (cphiTEcrCP0.size(1) == 1) {
        i = sphiTCP0.size(1);
    } else {
        i = cphiTEcrCP0.size(1);
    }
    a.set_size(3, i);
    stride_0_1 = (sphiTCP0.size(1) != 1);
    stride_1_1 = (cphiTEcrCP0.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (cphiTEcrCP0.size(1) == 1) {
        loop_ub = sphiTCP0.size(1);
    } else {
        loop_ub = cphiTEcrCP0.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        a[3 * i1] =
            -CurvStruct_theta * sphiTCP0[3 * aux_0_1] + CurvStruct_theta * cphiTEcrCP0[3 * aux_1_1];
        a[3 * i1 + 1] = -CurvStruct_theta * sphiTCP0[3 * aux_0_1 + 1] +
                        CurvStruct_theta * cphiTEcrCP0[3 * aux_1_1 + 1];
        a[3 * i1 + 2] = -CurvStruct_theta * sphiTCP0[3 * aux_0_1 + 2] +
                        CurvStruct_theta * cphiTEcrCP0[3 * aux_1_1 + 2];
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &r3D
//                double a
//                const ::coder::array<double, 2U> &sphiTCP0
//                double b_a
//                const ::coder::array<double, 2U> &cphiTEcrCP0
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 2U> &r3D, double a,
                             const ::coder::array<double, 2U> &sphiTCP0, double b_a,
                             const ::coder::array<double, 2U> &cphiTEcrCP0)
{
    int aux_0_1;
    int aux_1_1;
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (cphiTEcrCP0.size(1) == 1) {
        i = sphiTCP0.size(1);
    } else {
        i = cphiTEcrCP0.size(1);
    }
    r3D.set_size(3, i);
    stride_0_1 = (sphiTCP0.size(1) != 1);
    stride_1_1 = (cphiTEcrCP0.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (cphiTEcrCP0.size(1) == 1) {
        loop_ub = sphiTCP0.size(1);
    } else {
        loop_ub = cphiTEcrCP0.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        r3D[3 * i1] = a * sphiTCP0[3 * aux_0_1] - b_a * cphiTEcrCP0[3 * aux_1_1];
        r3D[3 * i1 + 1] = a * sphiTCP0[3 * aux_0_1 + 1] - b_a * cphiTEcrCP0[3 * aux_1_1 + 1];
        r3D[3 * i1 + 2] = a * sphiTCP0[3 * aux_0_1 + 2] - b_a * cphiTEcrCP0[3 * aux_1_1 + 2];
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// Arguments    : const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double u_vec[10]
//                double r0D[10][3]
//                double r1D[10][3]
//                double r2D[10][3]
//                double r3D[10][3]
// Return Type  : void
//
void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3],
               const double CurvStruct_CorrectedHelixCenter[3], const double CurvStruct_evec[3],
               double CurvStruct_theta, double CurvStruct_pitch, const double u_vec[10],
               double r0D[10][3], double r1D[10][3], double r2D[10][3], double r3D[10][3])
{
    double P0P1_idx_0;
    double P0P1_idx_1;
    double P0P1_idx_2;
    ZoneScopedN("EvalHelix");
    //
    P0P1_idx_0 = CurvStruct_P1[0] - CurvStruct_P0[0];
    P0P1_idx_1 = CurvStruct_P1[1] - CurvStruct_P0[1];
    P0P1_idx_2 = CurvStruct_P1[2] - CurvStruct_P0[2];
    for (int i{0}; i < 10; i++) {
        r0D[i][0] = 0.0;
        r1D[i][0] = 0.0;
        r2D[i][0] = 0.0;
        r3D[i][0] = 0.0;
        r0D[i][1] = 0.0;
        r1D[i][1] = 0.0;
        r2D[i][1] = 0.0;
        r3D[i][1] = 0.0;
        r0D[i][2] = 0.0;
        r1D[i][2] = 0.0;
        r2D[i][2] = 0.0;
        r3D[i][2] = 0.0;
    }
    sqrt_calls++;
    if (c_assert(
            std::sqrt(
                (std::pow(CurvStruct_evec[1] * P0P1_idx_2 - P0P1_idx_1 * CurvStruct_evec[2], 2.0) +
                 std::pow(P0P1_idx_0 * CurvStruct_evec[2] - CurvStruct_evec[0] * P0P1_idx_2, 2.0)) +
                std::pow(CurvStruct_evec[0] * P0P1_idx_1 - P0P1_idx_0 * CurvStruct_evec[1], 2.0)) >
            2.2204460492503131E-16)) {
        double CP0_idx_0;
        double CP0_idx_1;
        double CP0_idx_2;
        double EcrCP0_idx_0;
        double EcrCP0_idx_1;
        double EcrCP0_idx_2;
        double a;
        double a_tmp;
        double b_a;
        double b_a_tmp;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        double d5;
        double y_idx_0;
        double y_idx_1;
        double y_idx_2;
        //  if pitch == 0
        //      if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
        //          return;
        //      end
        //  end
        //
        CP0_idx_0 = CurvStruct_P0[0] - CurvStruct_CorrectedHelixCenter[0];
        CP0_idx_1 = CurvStruct_P0[1] - CurvStruct_CorrectedHelixCenter[1];
        CP0_idx_2 = CurvStruct_P0[2] - CurvStruct_CorrectedHelixCenter[2];
        EcrCP0_idx_0 = CurvStruct_evec[1] * CP0_idx_2 - CP0_idx_1 * CurvStruct_evec[2];
        EcrCP0_idx_1 = CP0_idx_0 * CurvStruct_evec[2] - CurvStruct_evec[0] * CP0_idx_2;
        EcrCP0_idx_2 = CurvStruct_evec[0] * CP0_idx_1 - CP0_idx_0 * CurvStruct_evec[1];
        cos_calls++;
        sin_calls++;
        //
        //
        a = CurvStruct_pitch / 6.2831853071795862;
        b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
        y_idx_0 = b_a * CurvStruct_evec[0];
        y_idx_1 = b_a * CurvStruct_evec[1];
        y_idx_2 = b_a * CurvStruct_evec[2];
        a_tmp = CurvStruct_theta * CurvStruct_theta;
        b_a_tmp = std::pow(CurvStruct_theta, 3.0);
        d = CurvStruct_CorrectedHelixCenter[0];
        d1 = CurvStruct_CorrectedHelixCenter[1];
        d2 = CurvStruct_CorrectedHelixCenter[2];
        d3 = CurvStruct_evec[0];
        d4 = CurvStruct_evec[1];
        d5 = CurvStruct_evec[2];
        for (int k{0}; k < 10; k++) {
            double d10;
            double d11;
            double d12;
            double d13;
            double d14;
            double d15;
            double d16;
            double d17;
            double d18;
            double d19;
            double d20;
            double d6;
            double d7;
            double d8;
            double d9;
            d6 = CurvStruct_theta * u_vec[k];
            d7 = std::cos(d6);
            d8 = std::sin(d6);
            d9 = CP0_idx_0 * d7;
            d10 = d9;
            d11 = CP0_idx_0 * d8;
            d12 = EcrCP0_idx_0 * d7;
            d13 = EcrCP0_idx_0 * d8;
            d14 = d13;
            r0D[k][0] = d + ((d9 + d13) + a * d3 * d6);
            d9 = CP0_idx_1 * d7;
            d15 = d9;
            d16 = CP0_idx_1 * d8;
            d17 = EcrCP0_idx_1 * d7;
            d13 = EcrCP0_idx_1 * d8;
            d18 = d13;
            r0D[k][1] = d1 + ((d9 + d13) + a * d4 * d6);
            d9 = CP0_idx_2 * d7;
            d19 = CP0_idx_2 * d8;
            d20 = EcrCP0_idx_2 * d7;
            d13 = EcrCP0_idx_2 * d8;
            r0D[k][2] = d2 + ((d9 + d13) + a * d5 * d6);
            r1D[k][0] = (-CurvStruct_theta * d11 + CurvStruct_theta * d12) + y_idx_0;
            r2D[k][0] = -a_tmp * d10 - a_tmp * d14;
            r3D[k][0] = b_a_tmp * d11 - b_a_tmp * d12;
            r1D[k][1] = (-CurvStruct_theta * d16 + CurvStruct_theta * d17) + y_idx_1;
            r2D[k][1] = -a_tmp * d15 - a_tmp * d18;
            r3D[k][1] = b_a_tmp * d16 - b_a_tmp * d17;
            r1D[k][2] = (-CurvStruct_theta * d19 + CurvStruct_theta * d20) + y_idx_2;
            r2D[k][2] = -a_tmp * d9 - a_tmp * d13;
            r3D[k][2] = b_a_tmp * d19 - b_a_tmp * d20;
        }
    }
}

//
// Arguments    : const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3],
               const double CurvStruct_CorrectedHelixCenter[3], const double CurvStruct_evec[3],
               double CurvStruct_theta, double CurvStruct_pitch,
               const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
               ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
               ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> c_a;
    ::coder::array<double, 2U> cphi;
    ::coder::array<double, 2U> cphiTCP0;
    ::coder::array<double, 2U> cphiTEcrCP0;
    ::coder::array<double, 2U> phi_vec;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> sphi;
    ::coder::array<double, 2U> sphiTCP0;
    ::coder::array<double, 2U> sphiTEcrCP0;
    double P0P1_idx_0;
    double P0P1_idx_1;
    double P0P1_idx_2;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int loop_ub;
    ZoneScopedN("EvalHelix");
    //
    P0P1_idx_0 = CurvStruct_P1[0] - CurvStruct_P0[0];
    P0P1_idx_1 = CurvStruct_P1[1] - CurvStruct_P0[1];
    P0P1_idx_2 = CurvStruct_P1[2] - CurvStruct_P0[2];
    r0D.set_size(3, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        r0D[3 * i] = 0.0;
        r0D[3 * i + 1] = 0.0;
        r0D[3 * i + 2] = 0.0;
    }
    r1D.set_size(3, u_vec.size(1));
    b_loop_ub = u_vec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        r1D[3 * i1] = 0.0;
        r1D[3 * i1 + 1] = 0.0;
        r1D[3 * i1 + 2] = 0.0;
    }
    r2D.set_size(3, u_vec.size(1));
    c_loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        r2D[3 * i2] = 0.0;
        r2D[3 * i2 + 1] = 0.0;
        r2D[3 * i2 + 2] = 0.0;
    }
    r3D.set_size(3, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        r3D[3 * i3] = 0.0;
        r3D[3 * i3 + 1] = 0.0;
        r3D[3 * i3 + 2] = 0.0;
    }
    sqrt_calls++;
    if (c_assert(
            std::sqrt(
                (std::pow(CurvStruct_evec[1] * P0P1_idx_2 - P0P1_idx_1 * CurvStruct_evec[2], 2.0) +
                 std::pow(P0P1_idx_0 * CurvStruct_evec[2] - CurvStruct_evec[0] * P0P1_idx_2, 2.0)) +
                std::pow(CurvStruct_evec[0] * P0P1_idx_1 - P0P1_idx_0 * CurvStruct_evec[1], 2.0)) >
            2.2204460492503131E-16)) {
        double CP0_idx_0;
        double CP0_idx_1;
        double CP0_idx_2;
        double EcrCP0_idx_0;
        double EcrCP0_idx_1;
        double EcrCP0_idx_2;
        double a;
        double a_tmp;
        double b_a;
        double b_a_tmp;
        double y_idx_0;
        double y_idx_1;
        double y_idx_2;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i14;
        int i6;
        int i8;
        int i_loop_ub;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        //  if pitch == 0
        //      if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
        //          return;
        //      end
        //  end
        //
        CP0_idx_0 = CurvStruct_P0[0] - CurvStruct_CorrectedHelixCenter[0];
        CP0_idx_1 = CurvStruct_P0[1] - CurvStruct_CorrectedHelixCenter[1];
        CP0_idx_2 = CurvStruct_P0[2] - CurvStruct_CorrectedHelixCenter[2];
        phi_vec.set_size(1, u_vec.size(1));
        e_loop_ub = u_vec.size(1);
        for (int i4{0}; i4 < e_loop_ub; i4++) {
            phi_vec[i4] = CurvStruct_theta * u_vec[i4];
        }
        EcrCP0_idx_0 = CurvStruct_evec[1] * CP0_idx_2 - CP0_idx_1 * CurvStruct_evec[2];
        EcrCP0_idx_1 = CP0_idx_0 * CurvStruct_evec[2] - CurvStruct_evec[0] * CP0_idx_2;
        EcrCP0_idx_2 = CurvStruct_evec[0] * CP0_idx_1 - CP0_idx_0 * CurvStruct_evec[1];
        cphi.set_size(1, phi_vec.size(1));
        f_loop_ub = phi_vec.size(1);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            cphi[i5] = phi_vec[i5];
        }
        i6 = phi_vec.size(1);
        for (int k{0}; k < i6; k++) {
            cphi[k] = std::cos(cphi[k]);
        }
        cos_calls++;
        sphi.set_size(1, phi_vec.size(1));
        g_loop_ub = phi_vec.size(1);
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            sphi[i7] = phi_vec[i7];
        }
        i8 = phi_vec.size(1);
        for (int b_k{0}; b_k < i8; b_k++) {
            sphi[b_k] = std::sin(sphi[b_k]);
        }
        sin_calls++;
        //
        cphiTCP0.set_size(3, cphi.size(1));
        h_loop_ub = cphi.size(1);
        for (int i9{0}; i9 < h_loop_ub; i9++) {
            cphiTCP0[3 * i9] = CP0_idx_0 * cphi[i9];
            cphiTCP0[3 * i9 + 1] = CP0_idx_1 * cphi[i9];
            cphiTCP0[3 * i9 + 2] = CP0_idx_2 * cphi[i9];
        }
        sphiTCP0.set_size(3, sphi.size(1));
        i_loop_ub = sphi.size(1);
        for (int i10{0}; i10 < i_loop_ub; i10++) {
            sphiTCP0[3 * i10] = CP0_idx_0 * sphi[i10];
            sphiTCP0[3 * i10 + 1] = CP0_idx_1 * sphi[i10];
            sphiTCP0[3 * i10 + 2] = CP0_idx_2 * sphi[i10];
        }
        cphiTEcrCP0.set_size(3, cphi.size(1));
        j_loop_ub = cphi.size(1);
        for (int i11{0}; i11 < j_loop_ub; i11++) {
            cphiTEcrCP0[3 * i11] = EcrCP0_idx_0 * cphi[i11];
            cphiTEcrCP0[3 * i11 + 1] = EcrCP0_idx_1 * cphi[i11];
            cphiTEcrCP0[3 * i11 + 2] = EcrCP0_idx_2 * cphi[i11];
        }
        sphiTEcrCP0.set_size(3, sphi.size(1));
        k_loop_ub = sphi.size(1);
        for (int i12{0}; i12 < k_loop_ub; i12++) {
            sphiTEcrCP0[3 * i12] = EcrCP0_idx_0 * sphi[i12];
            sphiTEcrCP0[3 * i12 + 1] = EcrCP0_idx_1 * sphi[i12];
            sphiTEcrCP0[3 * i12 + 2] = EcrCP0_idx_2 * sphi[i12];
        }
        //
        a = CurvStruct_pitch / 6.2831853071795862;
        r.set_size(3, phi_vec.size(1));
        l_loop_ub = phi_vec.size(1);
        for (int i13{0}; i13 < l_loop_ub; i13++) {
            r[3 * i13] = a * CurvStruct_evec[0] * phi_vec[i13];
            r[3 * i13 + 1] = a * CurvStruct_evec[1] * phi_vec[i13];
            r[3 * i13 + 2] = a * CurvStruct_evec[2] * phi_vec[i13];
        }
        if (cphiTCP0.size(1) == 1) {
            i14 = sphiTEcrCP0.size(1);
        } else {
            i14 = cphiTCP0.size(1);
        }
        if ((cphiTCP0.size(1) == sphiTEcrCP0.size(1)) && (i14 == r.size(1))) {
            int m_loop_ub;
            b.set_size(3, phi_vec.size(1));
            m_loop_ub = phi_vec.size(1);
            for (int i15{0}; i15 < m_loop_ub; i15++) {
                b[3 * i15] = (cphiTCP0[3 * i15] + sphiTEcrCP0[3 * i15]) +
                             a * CurvStruct_evec[0] * phi_vec[i15];
                b[3 * i15 + 1] = (cphiTCP0[3 * i15 + 1] + sphiTEcrCP0[3 * i15 + 1]) +
                                 a * CurvStruct_evec[1] * phi_vec[i15];
                b[3 * i15 + 2] = (cphiTCP0[3 * i15 + 2] + sphiTEcrCP0[3 * i15 + 2]) +
                                 a * CurvStruct_evec[2] * phi_vec[i15];
            }
        } else {
            binary_expand_op(b, cphiTCP0, sphiTEcrCP0, a, CurvStruct_evec, phi_vec);
        }
        r0D.set_size(3, b.size(1));
        if (b.size(1) != 0) {
            int bcoef;
            int i16;
            bcoef = (b.size(1) != 1);
            i16 = b.size(1) - 1;
            for (int c_k{0}; c_k <= i16; c_k++) {
                int varargin_3;
                varargin_3 = bcoef * c_k;
                r0D[3 * c_k] = CurvStruct_CorrectedHelixCenter[0] + b[3 * varargin_3];
                r0D[3 * c_k + 1] = CurvStruct_CorrectedHelixCenter[1] + b[3 * varargin_3 + 1];
                r0D[3 * c_k + 2] = CurvStruct_CorrectedHelixCenter[2] + b[3 * varargin_3 + 2];
            }
        }
        b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
        y_idx_0 = b_a * CurvStruct_evec[0];
        y_idx_1 = b_a * CurvStruct_evec[1];
        y_idx_2 = b_a * CurvStruct_evec[2];
        if (sphiTCP0.size(1) == cphiTEcrCP0.size(1)) {
            int n_loop_ub;
            c_a.set_size(3, sphiTCP0.size(1));
            n_loop_ub = sphiTCP0.size(1);
            for (int i17{0}; i17 < n_loop_ub; i17++) {
                c_a[3 * i17] =
                    -CurvStruct_theta * sphiTCP0[3 * i17] + CurvStruct_theta * cphiTEcrCP0[3 * i17];
                c_a[3 * i17 + 1] = -CurvStruct_theta * sphiTCP0[3 * i17 + 1] +
                                   CurvStruct_theta * cphiTEcrCP0[3 * i17 + 1];
                c_a[3 * i17 + 2] = -CurvStruct_theta * sphiTCP0[3 * i17 + 2] +
                                   CurvStruct_theta * cphiTEcrCP0[3 * i17 + 2];
            }
        } else {
            binary_expand_op(c_a, CurvStruct_theta, sphiTCP0, cphiTEcrCP0);
        }
        r1D.set_size(3, c_a.size(1));
        if (c_a.size(1) != 0) {
            int acoef;
            int i18;
            acoef = (c_a.size(1) != 1);
            i18 = c_a.size(1) - 1;
            for (int d_k{0}; d_k <= i18; d_k++) {
                int varargin_2;
                varargin_2 = acoef * d_k;
                r1D[3 * d_k] = c_a[3 * varargin_2] + y_idx_0;
                r1D[3 * d_k + 1] = c_a[3 * varargin_2 + 1] + y_idx_1;
                r1D[3 * d_k + 2] = c_a[3 * varargin_2 + 2] + y_idx_2;
            }
        }
        a_tmp = CurvStruct_theta * CurvStruct_theta;
        if (cphiTCP0.size(1) == sphiTEcrCP0.size(1)) {
            int o_loop_ub;
            r2D.set_size(3, cphiTCP0.size(1));
            o_loop_ub = cphiTCP0.size(1);
            for (int i19{0}; i19 < o_loop_ub; i19++) {
                r2D[3 * i19] = -a_tmp * cphiTCP0[3 * i19] - a_tmp * sphiTEcrCP0[3 * i19];
                r2D[3 * i19 + 1] =
                    -a_tmp * cphiTCP0[3 * i19 + 1] - a_tmp * sphiTEcrCP0[3 * i19 + 1];
                r2D[3 * i19 + 2] =
                    -a_tmp * cphiTCP0[3 * i19 + 2] - a_tmp * sphiTEcrCP0[3 * i19 + 2];
            }
        } else {
            binary_expand_op(r2D, -a_tmp, cphiTCP0, a_tmp, sphiTEcrCP0);
        }
        b_a_tmp = std::pow(CurvStruct_theta, 3.0);
        if (sphiTCP0.size(1) == cphiTEcrCP0.size(1)) {
            int p_loop_ub;
            r3D.set_size(3, sphiTCP0.size(1));
            p_loop_ub = sphiTCP0.size(1);
            for (int i20{0}; i20 < p_loop_ub; i20++) {
                r3D[3 * i20] = b_a_tmp * sphiTCP0[3 * i20] - b_a_tmp * cphiTEcrCP0[3 * i20];
                r3D[3 * i20 + 1] =
                    b_a_tmp * sphiTCP0[3 * i20 + 1] - b_a_tmp * cphiTEcrCP0[3 * i20 + 1];
                r3D[3 * i20 + 2] =
                    b_a_tmp * sphiTCP0[3 * i20 + 2] - b_a_tmp * cphiTEcrCP0[3 * i20 + 2];
            }
        } else {
            binary_expand_op(r3D, b_a_tmp, sphiTCP0, b_a_tmp, cphiTEcrCP0);
        }
    }
}

//
// Arguments    : const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                double u_vec
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
//                double r3D[3]
// Return Type  : void
//
void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3],
               const double CurvStruct_CorrectedHelixCenter[3], const double CurvStruct_evec[3],
               double CurvStruct_theta, double CurvStruct_pitch, double u_vec, double r0D[3],
               double r1D[3], double r2D[3], double r3D[3])
{
    double P0P1_idx_0;
    double P0P1_idx_1;
    double P0P1_idx_2;
    ZoneScopedN("EvalHelix");
    //
    P0P1_idx_0 = CurvStruct_P1[0] - CurvStruct_P0[0];
    r0D[0] = 0.0;
    r1D[0] = 0.0;
    r2D[0] = 0.0;
    r3D[0] = 0.0;
    P0P1_idx_1 = CurvStruct_P1[1] - CurvStruct_P0[1];
    r0D[1] = 0.0;
    r1D[1] = 0.0;
    r2D[1] = 0.0;
    r3D[1] = 0.0;
    P0P1_idx_2 = CurvStruct_P1[2] - CurvStruct_P0[2];
    r0D[2] = 0.0;
    r1D[2] = 0.0;
    r2D[2] = 0.0;
    r3D[2] = 0.0;
    sqrt_calls++;
    if (c_assert(
            std::sqrt(
                (std::pow(CurvStruct_evec[1] * P0P1_idx_2 - P0P1_idx_1 * CurvStruct_evec[2], 2.0) +
                 std::pow(P0P1_idx_0 * CurvStruct_evec[2] - CurvStruct_evec[0] * P0P1_idx_2, 2.0)) +
                std::pow(CurvStruct_evec[0] * P0P1_idx_1 - P0P1_idx_0 * CurvStruct_evec[1], 2.0)) >
            2.2204460492503131E-16)) {
        double CP0_idx_0;
        double CP0_idx_1;
        double EcrCP0_idx_0;
        double EcrCP0_idx_1;
        double EcrCP0_idx_2;
        double a;
        double a_tmp;
        double b_a;
        double b_a_tmp;
        double cphi;
        double cphiTCP0_idx_0;
        double cphiTCP0_idx_1;
        double cphiTCP0_idx_2;
        double d;
        double d1;
        double d2;
        double phi_vec;
        double sphi;
        double sphiTCP0_idx_0;
        double sphiTCP0_idx_1;
        double sphiTCP0_idx_2;
        //  if pitch == 0
        //      if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
        //          return;
        //      end
        //  end
        //
        phi_vec = CurvStruct_theta * u_vec;
        cphi = std::cos(phi_vec);
        cos_calls++;
        sphi = std::sin(phi_vec);
        sin_calls++;
        //
        d = CurvStruct_P0[0] - CurvStruct_CorrectedHelixCenter[0];
        CP0_idx_0 = d;
        cphiTCP0_idx_0 = d * cphi;
        sphiTCP0_idx_0 = d * sphi;
        d = CurvStruct_P0[1] - CurvStruct_CorrectedHelixCenter[1];
        CP0_idx_1 = d;
        cphiTCP0_idx_1 = d * cphi;
        sphiTCP0_idx_1 = d * sphi;
        d = CurvStruct_P0[2] - CurvStruct_CorrectedHelixCenter[2];
        cphiTCP0_idx_2 = d * cphi;
        sphiTCP0_idx_2 = d * sphi;
        EcrCP0_idx_0 = CurvStruct_evec[1] * d - CP0_idx_1 * CurvStruct_evec[2];
        EcrCP0_idx_1 = CP0_idx_0 * CurvStruct_evec[2] - CurvStruct_evec[0] * d;
        EcrCP0_idx_2 = CurvStruct_evec[0] * CP0_idx_1 - CP0_idx_0 * CurvStruct_evec[1];
        //
        a = CurvStruct_pitch / 6.2831853071795862;
        b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
        a_tmp = CurvStruct_theta * CurvStruct_theta;
        b_a_tmp = std::pow(CurvStruct_theta, 3.0);
        d1 = EcrCP0_idx_0 * cphi;
        d2 = EcrCP0_idx_0 * sphi;
        r0D[0] = CurvStruct_CorrectedHelixCenter[0] +
                 ((cphiTCP0_idx_0 + d2) + a * CurvStruct_evec[0] * phi_vec);
        r1D[0] =
            (-CurvStruct_theta * sphiTCP0_idx_0 + CurvStruct_theta * d1) + b_a * CurvStruct_evec[0];
        r2D[0] = -a_tmp * cphiTCP0_idx_0 - a_tmp * d2;
        r3D[0] = b_a_tmp * sphiTCP0_idx_0 - b_a_tmp * d1;
        d1 = EcrCP0_idx_1 * cphi;
        d2 = EcrCP0_idx_1 * sphi;
        r0D[1] = CurvStruct_CorrectedHelixCenter[1] +
                 ((cphiTCP0_idx_1 + d2) + a * CurvStruct_evec[1] * phi_vec);
        r1D[1] =
            (-CurvStruct_theta * sphiTCP0_idx_1 + CurvStruct_theta * d1) + b_a * CurvStruct_evec[1];
        r2D[1] = -a_tmp * cphiTCP0_idx_1 - a_tmp * d2;
        r3D[1] = b_a_tmp * sphiTCP0_idx_1 - b_a_tmp * d1;
        d1 = EcrCP0_idx_2 * cphi;
        d2 = EcrCP0_idx_2 * sphi;
        r0D[2] = CurvStruct_CorrectedHelixCenter[2] +
                 ((cphiTCP0_idx_2 + d2) + a * CurvStruct_evec[2] * phi_vec);
        r1D[2] =
            (-CurvStruct_theta * sphiTCP0_idx_2 + CurvStruct_theta * d1) + b_a * CurvStruct_evec[2];
        r2D[2] = -a_tmp * cphiTCP0_idx_2 - a_tmp * d2;
        r3D[2] = b_a_tmp * sphiTCP0_idx_2 - b_a_tmp * d1;
    }
}

} // namespace ocn

//
// File trailer for EvalHelix.cpp
//
// [EOF]
//
