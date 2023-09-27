//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalLine.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:07:13
//

// Include Files
#include "EvalLine.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &in1, const double in2_data[],
                             const int in3_size[2], const ::coder::array<double, 2U> &in4,
                             const double in5_data[], const int in6_size[2]);

static void binary_expand_op(double in1_data[], int *in1_size, const double in2_data[],
                             const int *in2_size, double in3, const double in4_data[],
                             const int *in4_size);

static void binary_expand_op(::coder::array<double, 1U> &in1, const double in2_data[],
                             const int *in2_size, const double in3_data[], const int *in3_size);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &in1
//                const double in2_data[]
//                const int in3_size[2]
//                const ::coder::array<double, 2U> &in4
//                const double in5_data[]
//                const int in6_size[2]
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &in1, const double in2_data[],
                             const int in3_size[2], const ::coder::array<double, 2U> &in4,
                             const double in5_data[], const int in6_size[2])
{
    int b_in6_idx_0;
    int in3_idx_0;
    int in6_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_2_0;
    in3_idx_0 = in3_size[1];
    in6_idx_0 = in6_size[1];
    if (in6_idx_0 == 1) {
        b_in6_idx_0 = in3_idx_0;
    } else {
        b_in6_idx_0 = in6_idx_0;
    }
    in1.set_size(b_in6_idx_0, in4.size(1));
    stride_0_0 = (in3_idx_0 != 1);
    stride_2_0 = (in6_idx_0 != 1);
    loop_ub = in4.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        if (in6_idx_0 == 1) {
            b_loop_ub = in3_idx_0;
        } else {
            b_loop_ub = in6_idx_0;
        }
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            in1[i1 + in1.size(0) * i] =
                in2_data[i1 * stride_0_0] * in4[i] + in5_data[i1 * stride_2_0] * (1.0 - in4[i]);
        }
    }
}

//
// Arguments    : double in1_data[]
//                int *in1_size
//                const double in2_data[]
//                const int *in2_size
//                double in3
//                const double in4_data[]
//                const int *in4_size
// Return Type  : void
//
static void binary_expand_op(double in1_data[], int *in1_size, const double in2_data[],
                             const int *in2_size, double in3, const double in4_data[],
                             const int *in4_size)
{
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (*in4_size == 1) {
        *in1_size = *in2_size;
    } else {
        *in1_size = *in4_size;
    }
    stride_0_0 = (*in2_size != 1);
    stride_1_0 = (*in4_size != 1);
    if (*in4_size == 1) {
        loop_ub = *in2_size;
    } else {
        loop_ub = *in4_size;
    }
    for (int i{0}; i < loop_ub; i++) {
        in1_data[i] = in2_data[i * stride_0_0] * in3 + in4_data[i * stride_1_0] * (1.0 - in3);
    }
}

//
// Arguments    : ::coder::array<double, 1U> &in1
//                const double in2_data[]
//                const int *in2_size
//                const double in3_data[]
//                const int *in3_size
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 1U> &in1, const double in2_data[],
                             const int *in2_size, const double in3_data[], const int *in3_size)
{
    int b_in3_size;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (*in3_size == 1) {
        b_in3_size = *in2_size;
    } else {
        b_in3_size = *in3_size;
    }
    in1.set_size(b_in3_size);
    stride_0_0 = (*in2_size != 1);
    stride_1_0 = (*in3_size != 1);
    if (*in3_size == 1) {
        loop_ub = *in2_size;
    } else {
        loop_ub = *in3_size;
    }
    for (int i{0}; i < loop_ub; i++) {
        in1[i] = in2_data[i * stride_0_0] - in3_data[i * stride_1_0];
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalLine( CurvStruct, u_vec, mask )
//
// EvalLine :
//
//  Input
//  CurvStruct    : struct : Line segment
//  u_vec         :    1xn : Vector for evaluation of the curv
//  ind           :        : Vector of indices
//
//  Output
//  r0D           :   nDxn : Evaluation of the line at u\_vec points
//  r1D           :   nDxn : 1rst order parametric derivative for the line at u\_vec points
//  r2D           :   nDxn : 2nd order parametric derivative for the line at u\_vec points
//  r3D           :   nDxn : 3rd order parametric derivative for the line at u\_vec points
//
// Arguments    : const double CurvStruct_R0[6]
//                const double CurvStruct_R1[6]
//                const ::coder::array<double, 2U> &u_vec
//                const bool mask_data[]
//                const int mask_size[2]
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void EvalLine(const double CurvStruct_R0[6], const double CurvStruct_R1[6],
              const ::coder::array<double, 2U> &u_vec, const bool mask_data[],
              const int mask_size[2], ::coder::array<double, 2U> &r0D,
              ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
              ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> b;
    ::coder::array<double, 1U> a;
    double P0_data[6];
    double P1_data[6];
    int b_tmp_size[2];
    int tmp_size[2];
    int b_loop_ub;
    int b_partialTrueCount;
    int b_trueCount;
    int d_loop_ub;
    int e_loop_ub;
    int end_tmp;
    int nz;
    int partialTrueCount;
    int trueCount;
    int vlen;
    signed char b_tmp_data[6];
    signed char tmp_data[6];
    // 'EvalLine:16' if ~coder.target('MATLAB')
    // 'EvalLine:17' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalLine:18' coder.inline('never')
    // 'EvalLine:19' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalLine"'));
    ZoneScopedN("EvalLine");
    //
    //  parametrization of a straight line between P0 and P1
    // 'EvalLine:23' P0  = CurvStruct.R0( mask );
    end_tmp = mask_size[1] - 1;
    trueCount = 0;
    tmp_size[0] = 1;
    partialTrueCount = 0;
    for (int i{0}; i <= end_tmp; i++) {
        if (mask_data[i]) {
            trueCount++;
            tmp_data[partialTrueCount] = static_cast<signed char>(i + 1);
            partialTrueCount++;
        }
    }
    tmp_size[1] = trueCount;
    for (int b_i{0}; b_i < trueCount; b_i++) {
        P0_data[b_i] = CurvStruct_R0[tmp_data[b_i] - 1];
    }
    // 'EvalLine:24' P1  = CurvStruct.R1( mask );
    b_trueCount = 0;
    b_tmp_size[0] = 1;
    b_partialTrueCount = 0;
    for (int c_i{0}; c_i <= end_tmp; c_i++) {
        if (mask_data[c_i]) {
            b_trueCount++;
            b_tmp_data[b_partialTrueCount] = static_cast<signed char>(c_i + 1);
            b_partialTrueCount++;
        }
    }
    b_tmp_size[1] = b_trueCount;
    for (int i1{0}; i1 < b_trueCount; i1++) {
        P1_data[i1] = CurvStruct_R1[b_tmp_data[i1] - 1];
    }
    //  Calculate the numbre of dimension
    // 'EvalLine:26' nD  = sum( mask );
    vlen = mask_size[1];
    if (mask_size[1] == 0) {
        nz = 0;
    } else {
        int y;
        y = mask_data[0];
        for (int k{2}; k <= vlen; k++) {
            int b_y;
            b_y = y;
            if (vlen >= 2) {
                b_y = y + mask_data[k - 1];
            }
            y = b_y;
        }
        nz = y;
    }
    //
    // 'EvalLine:28' r0D = P1 .* u_vec + P0.*( 1 - u_vec );
    if (b_trueCount == trueCount) {
        int loop_ub;
        r0D.set_size(b_trueCount, u_vec.size(1));
        loop_ub = u_vec.size(1);
        for (int i2{0}; i2 < loop_ub; i2++) {
            for (int i3{0}; i3 < b_trueCount; i3++) {
                double d;
                d = u_vec[i2];
                r0D[i3 + r0D.size(0) * i2] = P1_data[i3] * d + P0_data[i3] * (1.0 - d);
            }
        }
    } else {
        binary_expand_op(r0D, P1_data, b_tmp_size, u_vec, P0_data, tmp_size);
    }
    //
    // 'EvalLine:30' N   = length( u_vec );
    // 'EvalLine:31' r1D = repmat( P1 - P0, 1, N );
    if (b_trueCount == trueCount) {
        a.set_size(b_trueCount);
        for (int i4{0}; i4 < b_trueCount; i4++) {
            a[i4] = P1_data[i4] - P0_data[i4];
        }
    } else {
        binary_expand_op(a, P1_data, &b_tmp_size[1], P0_data, &tmp_size[1]);
    }
    b.set_size(a.size(0), u_vec.size(1));
    if ((a.size(0) != 0) && (u_vec.size(1) != 0)) {
        int i5;
        int na;
        i5 = u_vec.size(1) - 1;
        na = a.size(0);
        for (int t{0}; t <= i5; t++) {
            for (int b_k{0}; b_k < na; b_k++) {
                b[b_k + b.size(0) * t] = a[b_k];
            }
        }
    }
    r1D.set_size(b.size(0), b.size(1));
    b_loop_ub = b.size(1);
    for (int i6{0}; i6 < b_loop_ub; i6++) {
        int c_loop_ub;
        c_loop_ub = b.size(0);
        for (int i7{0}; i7 < c_loop_ub; i7++) {
            r1D[i7 + r1D.size(0) * i6] = b[i7 + b.size(0) * i6];
        }
    }
    //
    // 'EvalLine:33' r2D = zeros( nD, N );
    r2D.set_size(nz, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i8{0}; i8 < d_loop_ub; i8++) {
        for (int i9{0}; i9 < nz; i9++) {
            r2D[i9 + r2D.size(0) * i8] = 0.0;
        }
    }
    // 'EvalLine:34' r3D = zeros( nD, N );
    r3D.set_size(nz, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i10{0}; i10 < e_loop_ub; i10++) {
        for (int i11{0}; i11 < nz; i11++) {
            r3D[i11 + r3D.size(0) * i10] = 0.0;
        }
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalLine( CurvStruct, u_vec, mask )
//
// EvalLine :
//
//  Input
//  CurvStruct    : struct : Line segment
//  u_vec         :    1xn : Vector for evaluation of the curv
//  ind           :        : Vector of indices
//
//  Output
//  r0D           :   nDxn : Evaluation of the line at u\_vec points
//  r1D           :   nDxn : 1rst order parametric derivative for the line at u\_vec points
//  r2D           :   nDxn : 2nd order parametric derivative for the line at u\_vec points
//  r3D           :   nDxn : 3rd order parametric derivative for the line at u\_vec points
//
// Arguments    : const double CurvStruct_R0[6]
//                const double CurvStruct_R1[6]
//                double u_vec
//                const bool mask_data[]
//                const int mask_size[2]
//                double r0D_data[]
//                int *r0D_size
//                double r1D_data[]
//                int *r1D_size
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void b_EvalLine(const double CurvStruct_R0[6], const double CurvStruct_R1[6], double u_vec,
                const bool mask_data[], const int mask_size[2], double r0D_data[], int *r0D_size,
                double r1D_data[], int *r1D_size, ::coder::array<double, 1U> &r2D,
                ::coder::array<double, 1U> &r3D)
{
    ::coder::array<double, 1U> a;
    ::coder::array<double, 1U> b;
    double P0_data[6];
    double P1_data[6];
    int b_partialTrueCount;
    int b_trueCount;
    int end_tmp;
    int loop_ub;
    int nz;
    int partialTrueCount;
    int trueCount;
    int vlen;
    signed char b_tmp_data[6];
    signed char tmp_data[6];
    // 'EvalLine:16' if ~coder.target('MATLAB')
    // 'EvalLine:17' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalLine:18' coder.inline('never')
    // 'EvalLine:19' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalLine"'));
    ZoneScopedN("EvalLine");
    //
    //  parametrization of a straight line between P0 and P1
    // 'EvalLine:23' P0  = CurvStruct.R0( mask );
    end_tmp = mask_size[1] - 1;
    trueCount = 0;
    partialTrueCount = 0;
    for (int i{0}; i <= end_tmp; i++) {
        if (mask_data[i]) {
            trueCount++;
            tmp_data[partialTrueCount] = static_cast<signed char>(i + 1);
            partialTrueCount++;
        }
    }
    for (int b_i{0}; b_i < trueCount; b_i++) {
        P0_data[b_i] = CurvStruct_R0[tmp_data[b_i] - 1];
    }
    // 'EvalLine:24' P1  = CurvStruct.R1( mask );
    b_trueCount = 0;
    b_partialTrueCount = 0;
    for (int c_i{0}; c_i <= end_tmp; c_i++) {
        if (mask_data[c_i]) {
            b_trueCount++;
            b_tmp_data[b_partialTrueCount] = static_cast<signed char>(c_i + 1);
            b_partialTrueCount++;
        }
    }
    for (int i1{0}; i1 < b_trueCount; i1++) {
        P1_data[i1] = CurvStruct_R1[b_tmp_data[i1] - 1];
    }
    //  Calculate the numbre of dimension
    // 'EvalLine:26' nD  = sum( mask );
    vlen = mask_size[1];
    if (mask_size[1] == 0) {
        nz = 0;
    } else {
        int y;
        y = mask_data[0];
        for (int k{2}; k <= vlen; k++) {
            int b_y;
            b_y = y;
            if (vlen >= 2) {
                b_y = y + mask_data[k - 1];
            }
            y = b_y;
        }
        nz = y;
    }
    //
    // 'EvalLine:28' r0D = P1 .* u_vec + P0.*( 1 - u_vec );
    if (b_trueCount == trueCount) {
        *r0D_size = b_trueCount;
        for (int i2{0}; i2 < b_trueCount; i2++) {
            r0D_data[i2] = P1_data[i2] * u_vec + P0_data[i2] * (1.0 - u_vec);
        }
    } else {
        binary_expand_op(r0D_data, r0D_size, P1_data, &b_trueCount, u_vec, P0_data, &trueCount);
    }
    //
    // 'EvalLine:30' N   = length( u_vec );
    // 'EvalLine:31' r1D = repmat( P1 - P0, 1, N );
    if (b_trueCount == trueCount) {
        a.set_size(b_trueCount);
        for (int i3{0}; i3 < b_trueCount; i3++) {
            a[i3] = P1_data[i3] - P0_data[i3];
        }
    } else {
        binary_expand_op(a, P1_data, &b_trueCount, P0_data, &trueCount);
    }
    b.set_size(static_cast<int>(static_cast<signed char>(a.size(0))));
    if (static_cast<signed char>(a.size(0)) != 0) {
        int na;
        na = a.size(0);
        for (int b_k{0}; b_k < na; b_k++) {
            b[b_k] = a[b_k];
        }
    }
    *r1D_size = b.size(0);
    loop_ub = b.size(0);
    for (int i4{0}; i4 < loop_ub; i4++) {
        r1D_data[i4] = b[i4];
    }
    //
    // 'EvalLine:33' r2D = zeros( nD, N );
    r2D.set_size(nz);
    // 'EvalLine:34' r3D = zeros( nD, N );
    r3D.set_size(nz);
    for (int i5{0}; i5 < nz; i5++) {
        r2D[i5] = 0.0;
        r3D[i5] = 0.0;
    }
}

} // namespace ocn

//
// File trailer for EvalLine.cpp
//
// [EOF]
//
