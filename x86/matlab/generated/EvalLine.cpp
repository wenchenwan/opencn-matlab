//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalLine.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:46:02
//

// Include Files
#include "EvalLine.h"
#include "cat.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"
#include <emmintrin.h>

// Function Definitions
//
// function [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec)
//
// Arguments    : const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double u_vec[10]
//                double r0D[10][3]
//                double r1D[10][3]
//                double r2D[10][3]
//                double r3D[10][3]
// Return Type  : void
//
namespace ocn {
void EvalLine(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const double u_vec[10],
              double r0D[10][3], double r1D[10][3], double r2D[10][3], double r3D[10][3])
{
    double a[3];
    double d;
    double d1;
    double d2;
    double d3;
    double d4;
    double d5;
    double d6;
    double d7;
    double d8;
    // 'EvalLine:2' if ~coder.target('MATLAB')
    // 'EvalLine:3' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalLine:4' coder.inline('never')
    // 'EvalLine:5' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalLine"'));
    ZoneScopedN("EvalLine");
    //
    //  parametrization of a straight line between P0 and P1
    // 'EvalLine:9' P0  = CurvStruct.P0;
    // 'EvalLine:10' P1  = CurvStruct.P1;
    //
    // 'EvalLine:12' r0D = [P1(1)*u_vec + P0(1)*(1-u_vec);
    // 'EvalLine:13'        P1(2)*u_vec + P0(2)*(1-u_vec);
    // 'EvalLine:14'        P1(3)*u_vec + P0(3)*(1-u_vec)];
    //
    // 'EvalLine:16' N   = length(u_vec);
    // 'EvalLine:17' r1D = repmat(P1 - P0, 1, N);
    _mm_storeu_pd(&a[0], _mm_sub_pd(_mm_loadu_pd((const double *)&CurvStruct_P1[0]),
                                    _mm_loadu_pd((const double *)&CurvStruct_P0[0])));
    //
    // 'EvalLine:19' r2D = zeros(3, N);
    // 'EvalLine:20' r3D = zeros(3, N);
    d = CurvStruct_P1[0];
    d1 = CurvStruct_P1[1];
    d2 = CurvStruct_P1[2];
    d3 = CurvStruct_P0[0];
    d4 = CurvStruct_P0[1];
    d5 = CurvStruct_P0[2];
    d6 = a[0];
    d7 = a[1];
    d8 = CurvStruct_P1[2] - CurvStruct_P0[2];
    for (int t{0}; t < 10; t++) {
        double d9;
        d9 = u_vec[t];
        r0D[t][0] = d * d9 + d3 * (1.0 - d9);
        r0D[t][1] = d1 * d9 + d4 * (1.0 - d9);
        r0D[t][2] = d2 * d9 + d5 * (1.0 - d9);
        r1D[t][0] = d6;
        r2D[t][0] = 0.0;
        r3D[t][0] = 0.0;
        r1D[t][1] = d7;
        r2D[t][1] = 0.0;
        r3D[t][1] = 0.0;
        r1D[t][2] = d8;
        r2D[t][2] = 0.0;
        r3D[t][2] = 0.0;
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec)
//
// Arguments    : const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void EvalLine(const double CurvStruct_P0[3], const double CurvStruct_P1[3],
              const ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
              ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
              ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> b_tmp;
    double a[3];
    int e_loop_ub;
    int f_loop_ub;
    int i;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    // 'EvalLine:2' if ~coder.target('MATLAB')
    // 'EvalLine:3' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalLine:4' coder.inline('never')
    // 'EvalLine:5' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalLine"'));
    ZoneScopedN("EvalLine");
    //
    //  parametrization of a straight line between P0 and P1
    // 'EvalLine:9' P0  = CurvStruct.P0;
    // 'EvalLine:10' P1  = CurvStruct.P1;
    //
    // 'EvalLine:12' r0D = [P1(1)*u_vec + P0(1)*(1-u_vec);
    // 'EvalLine:13'        P1(2)*u_vec + P0(2)*(1-u_vec);
    // 'EvalLine:14'        P1(3)*u_vec + P0(3)*(1-u_vec)];
    b_tmp.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1);
    scalarLB = (u_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i = 0; i <= vectorUB; i += 2) {
        _mm_storeu_pd(&b_tmp[i],
                      _mm_sub_pd(_mm_set1_pd(1.0), _mm_loadu_pd((const double *)&u_vec[i])));
    }
    for (i = scalarLB; i < loop_ub; i++) {
        b_tmp[i] = 1.0 - u_vec[i];
    }
    if (u_vec.size(1) == b_tmp.size(1)) {
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        r0D.set_size(3, u_vec.size(1));
        b_loop_ub = u_vec.size(1);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            r0D[3 * i1] = CurvStruct_P1[0] * u_vec[i1] + CurvStruct_P0[0] * b_tmp[i1];
        }
        c_loop_ub = u_vec.size(1);
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            r0D[3 * i2 + 1] = CurvStruct_P1[1] * u_vec[i2] + CurvStruct_P0[1] * b_tmp[i2];
        }
        d_loop_ub = u_vec.size(1);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            r0D[3 * i3 + 2] = CurvStruct_P1[2] * u_vec[i3] + CurvStruct_P0[2] * b_tmp[i3];
        }
    } else {
        binary_expand_op(r0D, CurvStruct_P1, u_vec, CurvStruct_P0, b_tmp);
    }
    //
    // 'EvalLine:16' N   = length(u_vec);
    // 'EvalLine:17' r1D = repmat(P1 - P0, 1, N);
    _mm_storeu_pd(&a[0], _mm_sub_pd(_mm_loadu_pd((const double *)&CurvStruct_P1[0]),
                                    _mm_loadu_pd((const double *)&CurvStruct_P0[0])));
    a[2] = CurvStruct_P1[2] - CurvStruct_P0[2];
    r1D.set_size(3, u_vec.size(1));
    if (u_vec.size(1) != 0) {
        int i4;
        i4 = u_vec.size(1) - 1;
        for (int t{0}; t <= i4; t++) {
            r1D[3 * t] = a[0];
            r1D[3 * t + 1] = a[1];
            r1D[3 * t + 2] = a[2];
        }
    }
    //
    // 'EvalLine:19' r2D = zeros(3, N);
    r2D.set_size(3, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i5{0}; i5 < e_loop_ub; i5++) {
        r2D[3 * i5] = 0.0;
        r2D[3 * i5 + 1] = 0.0;
        r2D[3 * i5 + 2] = 0.0;
    }
    // 'EvalLine:20' r3D = zeros(3, N);
    r3D.set_size(3, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        r3D[3 * i6] = 0.0;
        r3D[3 * i6 + 1] = 0.0;
        r3D[3 * i6 + 2] = 0.0;
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalLine(CurvStruct, u_vec)
//
// Arguments    : const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                double u_vec
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
//                double r3D[3]
// Return Type  : void
//
void EvalLine(const double CurvStruct_P0[3], const double CurvStruct_P1[3], double u_vec,
              double r0D[3], double r1D[3], double r2D[3], double r3D[3])
{
    __m128d r;
    // 'EvalLine:2' if ~coder.target('MATLAB')
    // 'EvalLine:3' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalLine:4' coder.inline('never')
    // 'EvalLine:5' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalLine"'));
    ZoneScopedN("EvalLine");
    //
    //  parametrization of a straight line between P0 and P1
    // 'EvalLine:9' P0  = CurvStruct.P0;
    // 'EvalLine:10' P1  = CurvStruct.P1;
    //
    // 'EvalLine:12' r0D = [P1(1)*u_vec + P0(1)*(1-u_vec);
    // 'EvalLine:13'        P1(2)*u_vec + P0(2)*(1-u_vec);
    // 'EvalLine:14'        P1(3)*u_vec + P0(3)*(1-u_vec)];
    r0D[0] = CurvStruct_P1[0] * u_vec + CurvStruct_P0[0] * (1.0 - u_vec);
    r0D[1] = CurvStruct_P1[1] * u_vec + CurvStruct_P0[1] * (1.0 - u_vec);
    r0D[2] = CurvStruct_P1[2] * u_vec + CurvStruct_P0[2] * (1.0 - u_vec);
    //
    // 'EvalLine:16' N   = length(u_vec);
    // 'EvalLine:17' r1D = repmat(P1 - P0, 1, N);
    //
    // 'EvalLine:19' r2D = zeros(3, N);
    // 'EvalLine:20' r3D = zeros(3, N);
    _mm_storeu_pd(&r1D[0], _mm_sub_pd(_mm_loadu_pd((const double *)&CurvStruct_P1[0]),
                                      _mm_loadu_pd((const double *)&CurvStruct_P0[0])));
    r = _mm_set1_pd(0.0);
    _mm_storeu_pd(&r2D[0], r);
    _mm_storeu_pd(&r3D[0], r);
    r1D[2] = CurvStruct_P1[2] - CurvStruct_P0[2];
    r2D[2] = 0.0;
    r3D[2] = 0.0;
}

} // namespace ocn

//
// File trailer for EvalLine.cpp
//
// [EOF]
//
