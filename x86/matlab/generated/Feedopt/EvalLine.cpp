//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalLine.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Jun-2022 16:07:49
//

// Include Files
#include "EvalLine.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"
#include <emmintrin.h>

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &r0D, const ::coder::array<double, 1U> &P1,
                             const ::coder::array<int, 2U> &r,
                             const ::coder::array<double, 2U> &u_vec,
                             const ::coder::array<double, 1U> &P0,
                             const ::coder::array<int, 2U> &r1);

static void binary_expand_op(::coder::array<double, 1U> &r0D, const ::coder::array<double, 1U> &P1,
                             double u_vec, const ::coder::array<double, 1U> &P0);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &r0D
//                const ::coder::array<double, 1U> &P1
//                const ::coder::array<int, 2U> &r
//                const ::coder::array<double, 2U> &u_vec
//                const ::coder::array<double, 1U> &P0
//                const ::coder::array<int, 2U> &r1
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &r0D, const ::coder::array<double, 1U> &P1,
                             const ::coder::array<int, 2U> &r,
                             const ::coder::array<double, 2U> &u_vec,
                             const ::coder::array<double, 1U> &P0,
                             const ::coder::array<int, 2U> &r1)
{
    int aux_1_1;
    int aux_3_1;
    int b_unnamed_idx_0;
    int c_unnamed_idx_0;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_1;
    int stride_2_0;
    int stride_3_1;
    int unnamed_idx_0;
    unnamed_idx_0 = r.size(1);
    b_unnamed_idx_0 = r1.size(1);
    if (b_unnamed_idx_0 == 1) {
        c_unnamed_idx_0 = unnamed_idx_0;
    } else {
        c_unnamed_idx_0 = b_unnamed_idx_0;
    }
    if (u_vec.size(1) == 1) {
        i = 1;
    } else {
        i = u_vec.size(1);
    }
    r0D.set_size(c_unnamed_idx_0, i);
    stride_0_0 = (unnamed_idx_0 != 1);
    stride_1_1 = (u_vec.size(1) != 1);
    stride_2_0 = (b_unnamed_idx_0 != 1);
    stride_3_1 = (u_vec.size(1) != 1);
    aux_1_1 = 0;
    aux_3_1 = 0;
    if (u_vec.size(1) == 1) {
        loop_ub = 1;
    } else {
        loop_ub = u_vec.size(1);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        int b_loop_ub;
        if (b_unnamed_idx_0 == 1) {
            b_loop_ub = unnamed_idx_0;
        } else {
            b_loop_ub = b_unnamed_idx_0;
        }
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            r0D[i2 + r0D.size(0) * i1] =
                P1[i2 * stride_0_0] * u_vec[aux_1_1] + P0[i2 * stride_2_0] * (1.0 - u_vec[aux_3_1]);
        }
        aux_3_1 += stride_3_1;
        aux_1_1 += stride_1_1;
    }
}

//
// Arguments    : ::coder::array<double, 1U> &r0D
//                const ::coder::array<double, 1U> &P1
//                double u_vec
//                const ::coder::array<double, 1U> &P0
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 1U> &r0D, const ::coder::array<double, 1U> &P1,
                             double u_vec, const ::coder::array<double, 1U> &P0)
{
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (P0.size(0) == 1) {
        i = P1.size(0);
    } else {
        i = P0.size(0);
    }
    r0D.set_size(i);
    stride_0_0 = (P1.size(0) != 1);
    stride_1_0 = (P0.size(0) != 1);
    if (P0.size(0) == 1) {
        loop_ub = P1.size(0);
    } else {
        loop_ub = P0.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        r0D[i1] = P1[i1 * stride_0_0] * u_vec + P0[i1 * stride_1_0] * (1.0 - u_vec);
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
//                const ::coder::array<bool, 2U> &mask
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void EvalLine(const double CurvStruct_R0[6], const double CurvStruct_R1[6],
              const ::coder::array<double, 2U> &u_vec, const ::coder::array<bool, 2U> &mask,
              ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D,
              ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 1U> P0;
    ::coder::array<double, 1U> P1;
    ::coder::array<double, 1U> a;
    ::coder::array<int, 2U> r;
    ::coder::array<int, 2U> r1;
    int b_end;
    int b_loop_ub;
    int b_partialTrueCount;
    int b_trueCount;
    int e_loop_ub;
    int end;
    int f_loop_ub;
    int loop_ub;
    int nz;
    int partialTrueCount;
    int trueCount;
    int vlen;
    // 'EvalLine:16' if ~coder.target('MATLAB')
    // 'EvalLine:17' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalLine:18' coder.inline('never')
    // 'EvalLine:19' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalLine"'));
    ZoneScopedN("EvalLine");
    //
    //  parametrization of a straight line between P0 and P1
    // 'EvalLine:23' P0  = CurvStruct.R0( mask );
    end = mask.size(1) - 1;
    trueCount = 0;
    for (int i{0}; i <= end; i++) {
        if (mask[i]) {
            trueCount++;
        }
    }
    r.set_size(1, trueCount);
    partialTrueCount = 0;
    for (int b_i{0}; b_i <= end; b_i++) {
        if (mask[b_i]) {
            r[partialTrueCount] = b_i + 1;
            partialTrueCount++;
        }
    }
    P0.set_size(r.size(1));
    loop_ub = r.size(1);
    for (int c_i{0}; c_i < loop_ub; c_i++) {
        P0[c_i] = CurvStruct_R0[r[c_i] - 1];
    }
    // 'EvalLine:24' P1  = CurvStruct.R1( mask );
    b_end = mask.size(1) - 1;
    b_trueCount = 0;
    for (int d_i{0}; d_i <= b_end; d_i++) {
        if (mask[d_i]) {
            b_trueCount++;
        }
    }
    r1.set_size(1, b_trueCount);
    b_partialTrueCount = 0;
    for (int e_i{0}; e_i <= b_end; e_i++) {
        if (mask[e_i]) {
            r1[b_partialTrueCount] = e_i + 1;
            b_partialTrueCount++;
        }
    }
    P1.set_size(r1.size(1));
    b_loop_ub = r1.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        P1[i1] = CurvStruct_R1[r1[i1] - 1];
    }
    //  Calculate the numbre of dimension
    // 'EvalLine:26' nD  = sum( mask );
    vlen = mask.size(1);
    if (mask.size(1) == 0) {
        nz = 0;
    } else {
        int y;
        y = mask[0];
        for (int k{2}; k <= vlen; k++) {
            int b_y;
            b_y = y;
            if (vlen >= 2) {
                b_y = y + mask[k - 1];
            }
            y = b_y;
        }
        nz = y;
    }
    //
    // 'EvalLine:28' r0D = P1 .* u_vec + P0.*( 1 - u_vec );
    if (r1.size(1) == r.size(1)) {
        int c_loop_ub;
        int unnamed_idx_0;
        unnamed_idx_0 = r1.size(1);
        r0D.set_size(r1.size(1), u_vec.size(1));
        c_loop_ub = u_vec.size(1);
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            int i3;
            int scalarLB;
            int vectorUB;
            scalarLB = (unnamed_idx_0 / 2) << 1;
            vectorUB = scalarLB - 2;
            for (i3 = 0; i3 <= vectorUB; i3 += 2) {
                __m128d r2;
                __m128d r3;
                double d;
                d = u_vec[i2];
                r2 = _mm_loadu_pd(&P1[i3]);
                r3 = _mm_loadu_pd(&P0[i3]);
                _mm_storeu_pd(&r0D[i3 + r0D.size(0) * i2],
                              _mm_add_pd(_mm_mul_pd(r2, _mm_set1_pd(d)),
                                         _mm_mul_pd(r3, _mm_set1_pd(1.0 - d))));
            }
            for (i3 = scalarLB; i3 < unnamed_idx_0; i3++) {
                double d1;
                d1 = u_vec[i2];
                r0D[i3 + r0D.size(0) * i2] = P1[i3] * d1 + P0[i3] * (1.0 - d1);
            }
        }
    } else {
        binary_expand_op(r0D, P1, r1, u_vec, P0, r);
    }
    //
    // 'EvalLine:30' N   = length( u_vec );
    // 'EvalLine:31' r1D = repmat( P1 - P0, 1, N );
    if (P1.size(0) == P0.size(0)) {
        int b_scalarLB;
        int b_vectorUB;
        int d_loop_ub;
        int i5;
        a.set_size(P1.size(0));
        d_loop_ub = P1.size(0);
        b_scalarLB = (P1.size(0) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (i5 = 0; i5 <= b_vectorUB; i5 += 2) {
            __m128d r4;
            __m128d r5;
            r4 = _mm_loadu_pd(&P1[i5]);
            r5 = _mm_loadu_pd(&P0[i5]);
            _mm_storeu_pd(&a[i5], _mm_sub_pd(r4, r5));
        }
        for (i5 = b_scalarLB; i5 < d_loop_ub; i5++) {
            a[i5] = P1[i5] - P0[i5];
        }
    } else {
        minus(a, P1, P0);
    }
    r1D.set_size(a.size(0), u_vec.size(1));
    if ((a.size(0) != 0) && (u_vec.size(1) != 0)) {
        int i4;
        i4 = u_vec.size(1) - 1;
        for (int t{0}; t <= i4; t++) {
            int na;
            na = a.size(0);
            for (int b_k{0}; b_k < na; b_k++) {
                r1D[b_k + r1D.size(0) * t] = a[b_k];
            }
        }
    }
    //
    // 'EvalLine:33' r2D = zeros( nD, N );
    r2D.set_size(nz, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i6{0}; i6 < e_loop_ub; i6++) {
        for (int i7{0}; i7 < nz; i7++) {
            r2D[i7 + r2D.size(0) * i6] = 0.0;
        }
    }
    // 'EvalLine:34' r3D = zeros( nD, N );
    r3D.set_size(nz, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        for (int i9{0}; i9 < nz; i9++) {
            r3D[i9 + r3D.size(0) * i8] = 0.0;
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
//                const ::coder::array<bool, 2U> &mask
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void b_EvalLine(const double CurvStruct_R0[6], const double CurvStruct_R1[6], double u_vec,
                const ::coder::array<bool, 2U> &mask, ::coder::array<double, 1U> &r0D,
                ::coder::array<double, 1U> &r1D, ::coder::array<double, 1U> &r2D,
                ::coder::array<double, 1U> &r3D)
{
    ::coder::array<double, 1U> P0;
    ::coder::array<double, 1U> P1;
    ::coder::array<double, 1U> a;
    ::coder::array<int, 2U> r;
    ::coder::array<int, 2U> r1;
    int b_end;
    int b_loop_ub;
    int b_partialTrueCount;
    int b_trueCount;
    int end;
    int loop_ub;
    int nz;
    int partialTrueCount;
    int trueCount;
    int vlen;
    // 'EvalLine:16' if ~coder.target('MATLAB')
    // 'EvalLine:17' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalLine:18' coder.inline('never')
    // 'EvalLine:19' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalLine"'));
    ZoneScopedN("EvalLine");
    //
    //  parametrization of a straight line between P0 and P1
    // 'EvalLine:23' P0  = CurvStruct.R0( mask );
    end = mask.size(1) - 1;
    trueCount = 0;
    for (int i{0}; i <= end; i++) {
        if (mask[i]) {
            trueCount++;
        }
    }
    r.set_size(1, trueCount);
    partialTrueCount = 0;
    for (int b_i{0}; b_i <= end; b_i++) {
        if (mask[b_i]) {
            r[partialTrueCount] = b_i + 1;
            partialTrueCount++;
        }
    }
    P0.set_size(r.size(1));
    loop_ub = r.size(1);
    for (int c_i{0}; c_i < loop_ub; c_i++) {
        P0[c_i] = CurvStruct_R0[r[c_i] - 1];
    }
    // 'EvalLine:24' P1  = CurvStruct.R1( mask );
    b_end = mask.size(1) - 1;
    b_trueCount = 0;
    for (int d_i{0}; d_i <= b_end; d_i++) {
        if (mask[d_i]) {
            b_trueCount++;
        }
    }
    r1.set_size(1, b_trueCount);
    b_partialTrueCount = 0;
    for (int e_i{0}; e_i <= b_end; e_i++) {
        if (mask[e_i]) {
            r1[b_partialTrueCount] = e_i + 1;
            b_partialTrueCount++;
        }
    }
    P1.set_size(r1.size(1));
    b_loop_ub = r1.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        P1[i1] = CurvStruct_R1[r1[i1] - 1];
    }
    //  Calculate the numbre of dimension
    // 'EvalLine:26' nD  = sum( mask );
    vlen = mask.size(1);
    if (mask.size(1) == 0) {
        nz = 0;
    } else {
        int y;
        y = mask[0];
        for (int k{2}; k <= vlen; k++) {
            int b_y;
            b_y = y;
            if (vlen >= 2) {
                b_y = y + mask[k - 1];
            }
            y = b_y;
        }
        nz = y;
    }
    //
    // 'EvalLine:28' r0D = P1 .* u_vec + P0.*( 1 - u_vec );
    if (P1.size(0) == P0.size(0)) {
        int c_loop_ub;
        int i2;
        int scalarLB;
        int vectorUB;
        r0D.set_size(P1.size(0));
        c_loop_ub = P1.size(0);
        scalarLB = (P1.size(0) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i2 = 0; i2 <= vectorUB; i2 += 2) {
            __m128d r2;
            __m128d r3;
            r2 = _mm_loadu_pd(&P1[i2]);
            r3 = _mm_loadu_pd(&P0[i2]);
            _mm_storeu_pd(&r0D[i2], _mm_add_pd(_mm_mul_pd(r2, _mm_set1_pd(u_vec)),
                                               _mm_mul_pd(r3, _mm_set1_pd(1.0 - u_vec))));
        }
        for (i2 = scalarLB; i2 < c_loop_ub; i2++) {
            r0D[i2] = P1[i2] * u_vec + P0[i2] * (1.0 - u_vec);
        }
    } else {
        binary_expand_op(r0D, P1, u_vec, P0);
    }
    //
    // 'EvalLine:30' N   = length( u_vec );
    // 'EvalLine:31' r1D = repmat( P1 - P0, 1, N );
    if (P1.size(0) == P0.size(0)) {
        int b_scalarLB;
        int b_vectorUB;
        int d_loop_ub;
        int i3;
        a.set_size(P1.size(0));
        d_loop_ub = P1.size(0);
        b_scalarLB = (P1.size(0) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (i3 = 0; i3 <= b_vectorUB; i3 += 2) {
            __m128d r4;
            __m128d r5;
            r4 = _mm_loadu_pd(&P1[i3]);
            r5 = _mm_loadu_pd(&P0[i3]);
            _mm_storeu_pd(&a[i3], _mm_sub_pd(r4, r5));
        }
        for (i3 = b_scalarLB; i3 < d_loop_ub; i3++) {
            a[i3] = P1[i3] - P0[i3];
        }
    } else {
        minus(a, P1, P0);
    }
    r1D.set_size(a.size(0));
    if (a.size(0) != 0) {
        int na;
        na = a.size(0);
        for (int b_k{0}; b_k < na; b_k++) {
            r1D[b_k] = a[b_k];
        }
    }
    //
    // 'EvalLine:33' r2D = zeros( nD, N );
    r2D.set_size(nz);
    // 'EvalLine:34' r3D = zeros( nD, N );
    r3D.set_size(nz);
    for (int i4{0}; i4 < nz; i4++) {
        r2D[i4] = 0.0;
        r3D[i4] = 0.0;
    }
}

//
// Arguments    : ::coder::array<double, 1U> &a
//                const ::coder::array<double, 1U> &P1
//                const ::coder::array<double, 1U> &P0
// Return Type  : void
//
void minus(::coder::array<double, 1U> &a, const ::coder::array<double, 1U> &P1,
           const ::coder::array<double, 1U> &P0)
{
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (P0.size(0) == 1) {
        i = P1.size(0);
    } else {
        i = P0.size(0);
    }
    a.set_size(i);
    stride_0_0 = (P1.size(0) != 1);
    stride_1_0 = (P0.size(0) != 1);
    if (P0.size(0) == 1) {
        loop_ub = P1.size(0);
    } else {
        loop_ub = P0.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        a[i1] = P1[i1 * stride_0_0] - P0[i1 * stride_1_0];
    }
}

} // namespace ocn

//
// File trailer for EvalLine.cpp
//
// [EOF]
//
