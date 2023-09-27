//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalHelix.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:07:13
//

// Include Files
#include "EvalHelix.h"
#include "opencn_matlab_data.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"
#include <cmath>

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                             const ::coder::array<double, 2U> &in3, double in4, const double in5[3],
                             const ::coder::array<double, 2U> &in6);

static void binary_expand_op(::coder::array<double, 2U> &in1, double in2,
                             const ::coder::array<double, 2U> &in3,
                             const ::coder::array<double, 2U> &in4);

static void binary_expand_op(::coder::array<double, 2U> &in1, double in2,
                             const ::coder::array<double, 2U> &in3, double in4,
                             const ::coder::array<double, 2U> &in5);

static void binary_expand_op(double in1[3], const double in2[6], const signed char in3_data[],
                             const int in3_size[2], const double in4[3]);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<double, 2U> &in3
//                double in4
//                const double in5[3]
//                const ::coder::array<double, 2U> &in6
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                             const ::coder::array<double, 2U> &in3, double in4, const double in5[3],
                             const ::coder::array<double, 2U> &in6)
{
    ::coder::array<double, 2U> b_in4;
    int aux_0_1;
    int aux_1_1;
    int aux_2_1;
    int b_loop_ub;
    int i1;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    int stride_2_1;
    b_in4.set_size(3, in6.size(1));
    loop_ub = in6.size(1);
    for (int i{0}; i < loop_ub; i++) {
        b_in4[3 * i] = in4 * in5[0] * in6[i];
        b_in4[3 * i + 1] = in4 * in5[1] * in6[i];
        b_in4[3 * i + 2] = in4 * in5[2] * in6[i];
    }
    if (b_in4.size(1) == 1) {
        if (in3.size(1) == 1) {
            i1 = in2.size(1);
        } else {
            i1 = in3.size(1);
        }
    } else {
        i1 = b_in4.size(1);
    }
    in1.set_size(3, i1);
    stride_0_1 = (in2.size(1) != 1);
    stride_1_1 = (in3.size(1) != 1);
    stride_2_1 = (b_in4.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    if (b_in4.size(1) == 1) {
        if (in3.size(1) == 1) {
            b_loop_ub = in2.size(1);
        } else {
            b_loop_ub = in3.size(1);
        }
    } else {
        b_loop_ub = b_in4.size(1);
    }
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        in1[3 * i2] = (in2[3 * aux_0_1] + in3[3 * aux_1_1]) + b_in4[3 * aux_2_1];
        in1[3 * i2 + 1] = (in2[3 * aux_0_1 + 1] + in3[3 * aux_1_1 + 1]) + b_in4[3 * aux_2_1 + 1];
        in1[3 * i2 + 2] = (in2[3 * aux_0_1 + 2] + in3[3 * aux_1_1 + 2]) + b_in4[3 * aux_2_1 + 2];
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                double in2
//                const ::coder::array<double, 2U> &in3
//                const ::coder::array<double, 2U> &in4
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 2U> &in1, double in2,
                             const ::coder::array<double, 2U> &in3,
                             const ::coder::array<double, 2U> &in4)
{
    int aux_0_1;
    int aux_1_1;
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (in4.size(1) == 1) {
        i = in3.size(1);
    } else {
        i = in4.size(1);
    }
    in1.set_size(3, i);
    stride_0_1 = (in3.size(1) != 1);
    stride_1_1 = (in4.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (in4.size(1) == 1) {
        loop_ub = in3.size(1);
    } else {
        loop_ub = in4.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        in1[3 * i1] = -in2 * in3[3 * aux_0_1] + in2 * in4[3 * aux_1_1];
        in1[3 * i1 + 1] = -in2 * in3[3 * aux_0_1 + 1] + in2 * in4[3 * aux_1_1 + 1];
        in1[3 * i1 + 2] = -in2 * in3[3 * aux_0_1 + 2] + in2 * in4[3 * aux_1_1 + 2];
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                double in2
//                const ::coder::array<double, 2U> &in3
//                double in4
//                const ::coder::array<double, 2U> &in5
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 2U> &in1, double in2,
                             const ::coder::array<double, 2U> &in3, double in4,
                             const ::coder::array<double, 2U> &in5)
{
    int aux_0_1;
    int aux_1_1;
    int i;
    int loop_ub;
    int stride_0_1;
    int stride_1_1;
    if (in5.size(1) == 1) {
        i = in3.size(1);
    } else {
        i = in5.size(1);
    }
    in1.set_size(3, i);
    stride_0_1 = (in3.size(1) != 1);
    stride_1_1 = (in5.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    if (in5.size(1) == 1) {
        loop_ub = in3.size(1);
    } else {
        loop_ub = in5.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        in1[3 * i1] = in2 * in3[3 * aux_0_1] - in4 * in5[3 * aux_1_1];
        in1[3 * i1 + 1] = in2 * in3[3 * aux_0_1 + 1] - in4 * in5[3 * aux_1_1 + 1];
        in1[3 * i1 + 2] = in2 * in3[3 * aux_0_1 + 2] - in4 * in5[3 * aux_1_1 + 2];
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// Arguments    : double in1[3]
//                const double in2[6]
//                const signed char in3_data[]
//                const int in3_size[2]
//                const double in4[3]
// Return Type  : void
//
static void binary_expand_op(double in1[3], const double in2[6], const signed char in3_data[],
                             const int in3_size[2], const double in4[3])
{
    int stride_0_0;
    stride_0_0 = (in3_size[1] != 1);
    in1[0] = in2[in3_data[0] - 1] - in4[0];
    in1[1] = in2[in3_data[stride_0_0] - 1] - in4[1];
    in1[2] = in2[in3_data[stride_0_0 << 1] - 1] - in4[2];
}

//
// function [r0D, r1D, r2D, r3D] = EvalHelix( CurvStruct, u_vec, maskCart )
//
// EvalHelix : Evalue the helix curv and its corresponding parametric
//  derivatives. The evaluation occurs on the specified points in the u
//  vector.
//
//  CurvStruct    : A struct filled the parameters correspondin to a Helix
//  u_vec         : A vector of specifided points for the evaluation of the
//                  curve
//
//  r0D           : The evaluated helix at the specified points
//  r1D           : The 1rst order parametric derivative of the curve at the
//                  specified points
//  r2D           : The 2nd order parametric derivative of the curve at the
//                  specified points
//  r3D           : The 3rd order parametric derivative of the curve at the
//                  specified points
//
// Arguments    : const double CurvStruct_R0[6]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const ::coder::array<double, 2U> &u_vec
//                const bool maskCart_data[]
//                const int maskCart_size[2]
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void EvalHelix(const double CurvStruct_R0[6], const double CurvStruct_CorrectedHelixCenter[3],
               const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
               const ::coder::array<double, 2U> &u_vec, const bool maskCart_data[],
               const int maskCart_size[2], ::coder::array<double, 2U> &r0D,
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
    double CP0[3];
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
    int tmp_size[2];
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int end;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i11;
    int i3;
    int i5;
    int loop_ub;
    int partialTrueCount;
    int trueCount;
    signed char tmp_data[6];
    // 'EvalHelix:18' if ~coder.target('MATLAB')
    // 'EvalHelix:19' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalHelix:20' coder.inline('never')
    // 'EvalHelix:21' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalHelix"'));
    ZoneScopedN("EvalHelix");
    //  Extract parameters from the struct
    // 'EvalHelix:24' P0      = CurvStruct.R0( maskCart );
    end = maskCart_size[1] - 1;
    trueCount = 0;
    tmp_size[0] = 1;
    partialTrueCount = 0;
    for (int i{0}; i <= end; i++) {
        if (maskCart_data[i]) {
            trueCount++;
            tmp_data[partialTrueCount] = static_cast<signed char>(i + 1);
            partialTrueCount++;
        }
    }
    tmp_size[1] = trueCount;
    // 'EvalHelix:25' P1      = CurvStruct.R1( maskCart );
    // 'EvalHelix:26' evec    = CurvStruct.evec;
    // 'EvalHelix:27' theta   = CurvStruct.theta;
    // 'EvalHelix:28' pitch   = CurvStruct.pitch;
    // 'EvalHelix:30' P0P1    = P0 - P1;
    //
    // 'EvalHelix:33' C           = CurvStruct.CorrectedHelixCenter;
    // 'EvalHelix:34' CP0         = P0 - C;
    if (trueCount == 3) {
        for (int b_i{0}; b_i < 3; b_i++) {
            CP0[b_i] = CurvStruct_R0[tmp_data[b_i] - 1] - CurvStruct_CorrectedHelixCenter[b_i];
        }
    } else {
        binary_expand_op(CP0, CurvStruct_R0, tmp_data, tmp_size, CurvStruct_CorrectedHelixCenter);
    }
    // 'EvalHelix:35' phi_vec     = theta * u_vec;
    phi_vec.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i1{0}; i1 < loop_ub; i1++) {
        phi_vec[i1] = CurvStruct_theta * u_vec[i1];
    }
    // 'EvalHelix:36' EcrCP0      = cross( evec, CP0 );
    EcrCP0_idx_0 = CurvStruct_evec[1] * CP0[2] - CP0[1] * CurvStruct_evec[2];
    EcrCP0_idx_1 = CP0[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * CP0[2];
    EcrCP0_idx_2 = CurvStruct_evec[0] * CP0[1] - CP0[0] * CurvStruct_evec[1];
    //  clockwise tangent vector
    // 'EvalHelix:37' cphi        = mycos( phi_vec );
    // 'mycos:3' y = cos(x);
    cphi.set_size(1, phi_vec.size(1));
    b_loop_ub = phi_vec.size(1);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        cphi[i2] = phi_vec[i2];
    }
    i3 = phi_vec.size(1);
    for (int k{0}; k < i3; k++) {
        cphi[k] = std::cos(cphi[k]);
    }
    // 'mycos:4' cos_calls = cos_calls + 1;
    cos_calls++;
    // 'EvalHelix:38' sphi        = mysin( phi_vec );
    // 'mysin:3' y = sin(x);
    sphi.set_size(1, phi_vec.size(1));
    c_loop_ub = phi_vec.size(1);
    for (int i4{0}; i4 < c_loop_ub; i4++) {
        sphi[i4] = phi_vec[i4];
    }
    i5 = phi_vec.size(1);
    for (int b_k{0}; b_k < i5; b_k++) {
        sphi[b_k] = std::sin(sphi[b_k]);
    }
    // 'mysin:4' sin_calls = sin_calls + 1;
    sin_calls++;
    //
    // 'EvalHelix:41' cphiTCP0    = CP0 * cphi;
    cphiTCP0.set_size(3, cphi.size(1));
    d_loop_ub = cphi.size(1);
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        cphiTCP0[3 * i6] = CP0[0] * cphi[i6];
        cphiTCP0[3 * i6 + 1] = CP0[1] * cphi[i6];
        cphiTCP0[3 * i6 + 2] = CP0[2] * cphi[i6];
    }
    // 'EvalHelix:42' sphiTCP0    = CP0 * sphi;
    sphiTCP0.set_size(3, sphi.size(1));
    e_loop_ub = sphi.size(1);
    for (int i7{0}; i7 < e_loop_ub; i7++) {
        sphiTCP0[3 * i7] = CP0[0] * sphi[i7];
        sphiTCP0[3 * i7 + 1] = CP0[1] * sphi[i7];
        sphiTCP0[3 * i7 + 2] = CP0[2] * sphi[i7];
    }
    // 'EvalHelix:43' cphiTEcrCP0 = EcrCP0 * cphi;
    cphiTEcrCP0.set_size(3, cphi.size(1));
    f_loop_ub = cphi.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        cphiTEcrCP0[3 * i8] = EcrCP0_idx_0 * cphi[i8];
        cphiTEcrCP0[3 * i8 + 1] = EcrCP0_idx_1 * cphi[i8];
        cphiTEcrCP0[3 * i8 + 2] = EcrCP0_idx_2 * cphi[i8];
    }
    // 'EvalHelix:44' sphiTEcrCP0 = EcrCP0 * sphi;
    sphiTEcrCP0.set_size(3, sphi.size(1));
    g_loop_ub = sphi.size(1);
    for (int i9{0}; i9 < g_loop_ub; i9++) {
        sphiTEcrCP0[3 * i9] = EcrCP0_idx_0 * sphi[i9];
        sphiTEcrCP0[3 * i9 + 1] = EcrCP0_idx_1 * sphi[i9];
        sphiTEcrCP0[3 * i9 + 2] = EcrCP0_idx_2 * sphi[i9];
    }
    // 'EvalHelix:45' Sign        = sign( P0P1'*evec );
    //
    // 'EvalHelix:47' r0D       = bsxfun(@plus, C, cphiTCP0  + sphiTEcrCP0  + ...
    // 'EvalHelix:48'                    pitch/(2*pi)*evec*phi_vec);
    a = CurvStruct_pitch / 6.2831853071795862;
    r.set_size(3, phi_vec.size(1));
    h_loop_ub = phi_vec.size(1);
    for (int i10{0}; i10 < h_loop_ub; i10++) {
        r[3 * i10] = a * CurvStruct_evec[0] * phi_vec[i10];
        r[3 * i10 + 1] = a * CurvStruct_evec[1] * phi_vec[i10];
        r[3 * i10 + 2] = a * CurvStruct_evec[2] * phi_vec[i10];
    }
    if (cphiTCP0.size(1) == 1) {
        i11 = sphiTEcrCP0.size(1);
    } else {
        i11 = cphiTCP0.size(1);
    }
    if ((cphiTCP0.size(1) == sphiTEcrCP0.size(1)) && (i11 == r.size(1))) {
        int i_loop_ub;
        b.set_size(3, phi_vec.size(1));
        i_loop_ub = phi_vec.size(1);
        for (int i12{0}; i12 < i_loop_ub; i12++) {
            b[3 * i12] =
                (cphiTCP0[3 * i12] + sphiTEcrCP0[3 * i12]) + a * CurvStruct_evec[0] * phi_vec[i12];
            b[3 * i12 + 1] = (cphiTCP0[3 * i12 + 1] + sphiTEcrCP0[3 * i12 + 1]) +
                             a * CurvStruct_evec[1] * phi_vec[i12];
            b[3 * i12 + 2] = (cphiTCP0[3 * i12 + 2] + sphiTEcrCP0[3 * i12 + 2]) +
                             a * CurvStruct_evec[2] * phi_vec[i12];
        }
    } else {
        binary_expand_op(b, cphiTCP0, sphiTEcrCP0, a, CurvStruct_evec, phi_vec);
    }
    r0D.set_size(3, b.size(1));
    if (b.size(1) != 0) {
        int bcoef;
        int i13;
        bcoef = (b.size(1) != 1);
        i13 = b.size(1) - 1;
        for (int c_k{0}; c_k <= i13; c_k++) {
            int varargin_3;
            varargin_3 = bcoef * c_k;
            r0D[3 * c_k] = CurvStruct_CorrectedHelixCenter[0] + b[3 * varargin_3];
            r0D[3 * c_k + 1] = CurvStruct_CorrectedHelixCenter[1] + b[3 * varargin_3 + 1];
            r0D[3 * c_k + 2] = CurvStruct_CorrectedHelixCenter[2] + b[3 * varargin_3 + 2];
        }
    }
    // 'EvalHelix:49' r1D       = bsxfun(@plus, -theta  *sphiTCP0  + theta  *cphiTEcrCP0, ...
    // 'EvalHelix:50'                    theta * pitch/(2*pi) * evec);
    b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
    y_idx_0 = b_a * CurvStruct_evec[0];
    y_idx_1 = b_a * CurvStruct_evec[1];
    y_idx_2 = b_a * CurvStruct_evec[2];
    if (sphiTCP0.size(1) == cphiTEcrCP0.size(1)) {
        int j_loop_ub;
        c_a.set_size(3, sphiTCP0.size(1));
        j_loop_ub = sphiTCP0.size(1);
        for (int i14{0}; i14 < j_loop_ub; i14++) {
            c_a[3 * i14] =
                -CurvStruct_theta * sphiTCP0[3 * i14] + CurvStruct_theta * cphiTEcrCP0[3 * i14];
            c_a[3 * i14 + 1] = -CurvStruct_theta * sphiTCP0[3 * i14 + 1] +
                               CurvStruct_theta * cphiTEcrCP0[3 * i14 + 1];
            c_a[3 * i14 + 2] = -CurvStruct_theta * sphiTCP0[3 * i14 + 2] +
                               CurvStruct_theta * cphiTEcrCP0[3 * i14 + 2];
        }
    } else {
        binary_expand_op(c_a, CurvStruct_theta, sphiTCP0, cphiTEcrCP0);
    }
    r1D.set_size(3, c_a.size(1));
    if (c_a.size(1) != 0) {
        int acoef;
        int i15;
        acoef = (c_a.size(1) != 1);
        i15 = c_a.size(1) - 1;
        for (int d_k{0}; d_k <= i15; d_k++) {
            int varargin_2;
            varargin_2 = acoef * d_k;
            r1D[3 * d_k] = c_a[3 * varargin_2] + y_idx_0;
            r1D[3 * d_k + 1] = c_a[3 * varargin_2 + 1] + y_idx_1;
            r1D[3 * d_k + 2] = c_a[3 * varargin_2 + 2] + y_idx_2;
        }
    }
    // 'EvalHelix:51' r2D       = -theta^2*cphiTCP0  - theta^2*sphiTEcrCP0;
    a_tmp = CurvStruct_theta * CurvStruct_theta;
    if (cphiTCP0.size(1) == sphiTEcrCP0.size(1)) {
        int k_loop_ub;
        r2D.set_size(3, cphiTCP0.size(1));
        k_loop_ub = cphiTCP0.size(1);
        for (int i16{0}; i16 < k_loop_ub; i16++) {
            r2D[3 * i16] = -a_tmp * cphiTCP0[3 * i16] - a_tmp * sphiTEcrCP0[3 * i16];
            r2D[3 * i16 + 1] = -a_tmp * cphiTCP0[3 * i16 + 1] - a_tmp * sphiTEcrCP0[3 * i16 + 1];
            r2D[3 * i16 + 2] = -a_tmp * cphiTCP0[3 * i16 + 2] - a_tmp * sphiTEcrCP0[3 * i16 + 2];
        }
    } else {
        binary_expand_op(r2D, -a_tmp, cphiTCP0, a_tmp, sphiTEcrCP0);
    }
    // 'EvalHelix:52' r3D       =  theta^3*sphiTCP0  - theta^3*cphiTEcrCP0;
    b_a_tmp = std::pow(CurvStruct_theta, 3.0);
    if (sphiTCP0.size(1) == cphiTEcrCP0.size(1)) {
        int l_loop_ub;
        r3D.set_size(3, sphiTCP0.size(1));
        l_loop_ub = sphiTCP0.size(1);
        for (int i17{0}; i17 < l_loop_ub; i17++) {
            r3D[3 * i17] = b_a_tmp * sphiTCP0[3 * i17] - b_a_tmp * cphiTEcrCP0[3 * i17];
            r3D[3 * i17 + 1] = b_a_tmp * sphiTCP0[3 * i17 + 1] - b_a_tmp * cphiTEcrCP0[3 * i17 + 1];
            r3D[3 * i17 + 2] = b_a_tmp * sphiTCP0[3 * i17 + 2] - b_a_tmp * cphiTEcrCP0[3 * i17 + 2];
        }
    } else {
        binary_expand_op(r3D, b_a_tmp, sphiTCP0, b_a_tmp, cphiTEcrCP0);
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalHelix( CurvStruct, u_vec, maskCart )
//
// EvalHelix : Evalue the helix curv and its corresponding parametric
//  derivatives. The evaluation occurs on the specified points in the u
//  vector.
//
//  CurvStruct    : A struct filled the parameters correspondin to a Helix
//  u_vec         : A vector of specifided points for the evaluation of the
//                  curve
//
//  r0D           : The evaluated helix at the specified points
//  r1D           : The 1rst order parametric derivative of the curve at the
//                  specified points
//  r2D           : The 2nd order parametric derivative of the curve at the
//                  specified points
//  r3D           : The 3rd order parametric derivative of the curve at the
//                  specified points
//
// Arguments    : const double CurvStruct_R0[6]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                double u_vec
//                const bool maskCart_data[]
//                const int maskCart_size[2]
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
//                double r3D[3]
// Return Type  : void
//
void b_EvalHelix(const double CurvStruct_R0[6], const double CurvStruct_CorrectedHelixCenter[3],
                 const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
                 double u_vec, const bool maskCart_data[], const int maskCart_size[2],
                 double r0D[3], double r1D[3], double r2D[3], double r3D[3])
{
    double CP0[3];
    double EcrCP0_idx_0;
    double EcrCP0_idx_1;
    double EcrCP0_idx_2;
    double a;
    double a_tmp;
    double b_a;
    double b_a_tmp;
    double cphi;
    double d;
    double d1;
    double d2;
    double d3;
    double phi_vec;
    double sphi;
    int tmp_size[2];
    int end;
    int partialTrueCount;
    int trueCount;
    signed char tmp_data[6];
    // 'EvalHelix:18' if ~coder.target('MATLAB')
    // 'EvalHelix:19' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalHelix:20' coder.inline('never')
    // 'EvalHelix:21' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalHelix"'));
    ZoneScopedN("EvalHelix");
    //  Extract parameters from the struct
    // 'EvalHelix:24' P0      = CurvStruct.R0( maskCart );
    end = maskCart_size[1] - 1;
    trueCount = 0;
    tmp_size[0] = 1;
    partialTrueCount = 0;
    for (int i{0}; i <= end; i++) {
        if (maskCart_data[i]) {
            trueCount++;
            tmp_data[partialTrueCount] = static_cast<signed char>(i + 1);
            partialTrueCount++;
        }
    }
    tmp_size[1] = trueCount;
    // 'EvalHelix:25' P1      = CurvStruct.R1( maskCart );
    // 'EvalHelix:26' evec    = CurvStruct.evec;
    // 'EvalHelix:27' theta   = CurvStruct.theta;
    // 'EvalHelix:28' pitch   = CurvStruct.pitch;
    // 'EvalHelix:30' P0P1    = P0 - P1;
    //
    // 'EvalHelix:33' C           = CurvStruct.CorrectedHelixCenter;
    // 'EvalHelix:34' CP0         = P0 - C;
    if (trueCount == 3) {
        for (int b_i{0}; b_i < 3; b_i++) {
            CP0[b_i] = CurvStruct_R0[tmp_data[b_i] - 1] - CurvStruct_CorrectedHelixCenter[b_i];
        }
    } else {
        binary_expand_op(CP0, CurvStruct_R0, tmp_data, tmp_size, CurvStruct_CorrectedHelixCenter);
    }
    // 'EvalHelix:35' phi_vec     = theta * u_vec;
    phi_vec = CurvStruct_theta * u_vec;
    // 'EvalHelix:36' EcrCP0      = cross( evec, CP0 );
    EcrCP0_idx_0 = CurvStruct_evec[1] * CP0[2] - CP0[1] * CurvStruct_evec[2];
    EcrCP0_idx_1 = CP0[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * CP0[2];
    EcrCP0_idx_2 = CurvStruct_evec[0] * CP0[1] - CP0[0] * CurvStruct_evec[1];
    //  clockwise tangent vector
    // 'EvalHelix:37' cphi        = mycos( phi_vec );
    // 'mycos:3' y = cos(x);
    cphi = std::cos(phi_vec);
    // 'mycos:4' cos_calls = cos_calls + 1;
    cos_calls++;
    // 'EvalHelix:38' sphi        = mysin( phi_vec );
    // 'mysin:3' y = sin(x);
    sphi = std::sin(phi_vec);
    // 'mysin:4' sin_calls = sin_calls + 1;
    sin_calls++;
    //
    // 'EvalHelix:41' cphiTCP0    = CP0 * cphi;
    // 'EvalHelix:42' sphiTCP0    = CP0 * sphi;
    // 'EvalHelix:43' cphiTEcrCP0 = EcrCP0 * cphi;
    // 'EvalHelix:44' sphiTEcrCP0 = EcrCP0 * sphi;
    // 'EvalHelix:45' Sign        = sign( P0P1'*evec );
    //
    // 'EvalHelix:47' r0D       = bsxfun(@plus, C, cphiTCP0  + sphiTEcrCP0  + ...
    // 'EvalHelix:48'                    pitch/(2*pi)*evec*phi_vec);
    a = CurvStruct_pitch / 6.2831853071795862;
    // 'EvalHelix:49' r1D       = bsxfun(@plus, -theta  *sphiTCP0  + theta  *cphiTEcrCP0, ...
    // 'EvalHelix:50'                    theta * pitch/(2*pi) * evec);
    b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
    // 'EvalHelix:51' r2D       = -theta^2*cphiTCP0  - theta^2*sphiTEcrCP0;
    a_tmp = CurvStruct_theta * CurvStruct_theta;
    // 'EvalHelix:52' r3D       =  theta^3*sphiTCP0  - theta^3*cphiTEcrCP0;
    b_a_tmp = std::pow(CurvStruct_theta, 3.0);
    d = CP0[0] * cphi;
    d1 = CP0[0] * sphi;
    d2 = EcrCP0_idx_0 * cphi;
    d3 = EcrCP0_idx_0 * sphi;
    r0D[0] = CurvStruct_CorrectedHelixCenter[0] + ((d + d3) + a * CurvStruct_evec[0] * phi_vec);
    r1D[0] = (-CurvStruct_theta * d1 + CurvStruct_theta * d2) + b_a * CurvStruct_evec[0];
    r2D[0] = -a_tmp * d - a_tmp * d3;
    r3D[0] = b_a_tmp * d1 - b_a_tmp * d2;
    d = CP0[1] * cphi;
    d1 = CP0[1] * sphi;
    d2 = EcrCP0_idx_1 * cphi;
    d3 = EcrCP0_idx_1 * sphi;
    r0D[1] = CurvStruct_CorrectedHelixCenter[1] + ((d + d3) + a * CurvStruct_evec[1] * phi_vec);
    r1D[1] = (-CurvStruct_theta * d1 + CurvStruct_theta * d2) + b_a * CurvStruct_evec[1];
    r2D[1] = -a_tmp * d - a_tmp * d3;
    r3D[1] = b_a_tmp * d1 - b_a_tmp * d2;
    d = CP0[2] * cphi;
    d1 = CP0[2] * sphi;
    d2 = EcrCP0_idx_2 * cphi;
    d3 = EcrCP0_idx_2 * sphi;
    r0D[2] = CurvStruct_CorrectedHelixCenter[2] + ((d + d3) + a * CurvStruct_evec[2] * phi_vec);
    r1D[2] = (-CurvStruct_theta * d1 + CurvStruct_theta * d2) + b_a * CurvStruct_evec[2];
    r2D[2] = -a_tmp * d - a_tmp * d3;
    r3D[2] = b_a_tmp * d1 - b_a_tmp * d2;
}

} // namespace ocn

//
// File trailer for EvalHelix.cpp
//
// [EOF]
//
