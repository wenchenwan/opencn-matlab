//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalHelix.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Feb-2022 14:58:55
//

// Include Files
#include "EvalHelix.h"
#include "opencn_matlab_data.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"
#include <cmath>
#include <emmintrin.h>

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
        __m128d r;
        r = _mm_loadu_pd((const double *)&CurvStruct_evec[0]);
        _mm_storeu_pd(&b_a[3 * i],
                      _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a), r), _mm_set1_pd(phi_vec[i])));
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
        __m128d r1;
        __m128d r2;
        __m128d r3;
        r1 = _mm_loadu_pd((const double *)&cphiTCP0[3 * aux_0_1]);
        r2 = _mm_loadu_pd((const double *)&sphiTEcrCP0[3 * aux_1_1]);
        r3 = _mm_loadu_pd(&b_a[3 * aux_2_1]);
        _mm_storeu_pd(&b[3 * i2], _mm_add_pd(_mm_add_pd(r1, r2), r3));
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
        __m128d r;
        __m128d r1;
        r = _mm_loadu_pd((const double *)&sphiTCP0[3 * aux_0_1]);
        r1 = _mm_loadu_pd((const double *)&cphiTEcrCP0[3 * aux_1_1]);
        _mm_storeu_pd(&a[3 * i1], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(-CurvStruct_theta), r),
                                             _mm_mul_pd(_mm_set1_pd(CurvStruct_theta), r1)));
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
        __m128d r;
        __m128d r1;
        r = _mm_loadu_pd((const double *)&sphiTCP0[3 * aux_0_1]);
        r1 = _mm_loadu_pd((const double *)&cphiTEcrCP0[3 * aux_1_1]);
        _mm_storeu_pd(&r3D[3 * i1],
                      _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(a), r), _mm_mul_pd(_mm_set1_pd(b_a), r1)));
        r3D[3 * i1 + 2] = a * sphiTCP0[3 * aux_0_1 + 2] - b_a * cphiTEcrCP0[3 * aux_1_1 + 2];
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec)
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
// Arguments    : const double CurvStruct_P0[3]
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
void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_CorrectedHelixCenter[3],
               const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
               const double u_vec[10], double r0D[10][3], double r1D[10][3], double r2D[10][3],
               double r3D[10][3])
{
    __m128d r;
    __m128d r1;
    __m128d r5;
    __m128d r7;
    double cphiTCP0[10][3];
    double cphiTEcrCP0[10][3];
    double sphiTCP0[10][3];
    double sphiTEcrCP0[10][3];
    double CP0[3];
    double EcrCP0[3];
    double y[3];
    double a;
    double a_tmp;
    double b_a_tmp;
    // 'EvalHelix:18' if ~coder.target('MATLAB')
    // 'EvalHelix:19' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalHelix:20' coder.inline('never')
    // 'EvalHelix:21' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalHelix"'));
    ZoneScopedN("EvalHelix");
    //  Extract parameters from the struct
    // 'EvalHelix:24' P0      = CurvStruct.P0;
    // 'EvalHelix:25' P1      = CurvStruct.P1;
    // 'EvalHelix:26' evec    = CurvStruct.evec;
    // 'EvalHelix:27' theta   = CurvStruct.theta;
    // 'EvalHelix:28' pitch   = CurvStruct.pitch;
    // 'EvalHelix:30' N       = length(u_vec);
    // 'EvalHelix:31' P0P1    = P0 - P1;
    // 'EvalHelix:33' r0D = zeros(3, N);
    // 'EvalHelix:34' r1D = zeros(3, N);
    // 'EvalHelix:35' r2D = zeros(3, N);
    // 'EvalHelix:36' r3D = zeros(3, N);
    //
    // 'EvalHelix:39' C           = CurvStruct.CorrectedHelixCenter;
    // 'EvalHelix:40' CP0         = P0 - C;
    _mm_storeu_pd(&CP0[0],
                  _mm_sub_pd(_mm_loadu_pd((const double *)&CurvStruct_P0[0]),
                             _mm_loadu_pd((const double *)&CurvStruct_CorrectedHelixCenter[0])));
    CP0[2] = CurvStruct_P0[2] - CurvStruct_CorrectedHelixCenter[2];
    // 'EvalHelix:41' phi_vec     = theta*u_vec;
    // 'EvalHelix:42' EcrCP0      = cross(evec, CP0);
    EcrCP0[0] = CurvStruct_evec[1] * CP0[2] - CP0[1] * CurvStruct_evec[2];
    EcrCP0[1] = CP0[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * CP0[2];
    EcrCP0[2] = CurvStruct_evec[0] * CP0[1] - CP0[0] * CurvStruct_evec[1];
    //  clockwise tangent vector
    // 'EvalHelix:43' cphi        = mycos(phi_vec);
    // 'mycos:3' y = cos(x);
    // 'mycos:4' cos_calls = cos_calls + 1;
    cos_calls++;
    // 'EvalHelix:44' sphi        = mysin(phi_vec);
    // 'mysin:3' y = sin(x);
    // 'mysin:4' sin_calls = sin_calls + 1;
    sin_calls++;
    //
    // 'EvalHelix:47' cphiTCP0    = CP0 * cphi;
    // 'EvalHelix:48' sphiTCP0    = CP0 * sphi;
    // 'EvalHelix:49' cphiTEcrCP0 = EcrCP0 * cphi;
    // 'EvalHelix:50' sphiTEcrCP0 = EcrCP0 * sphi;
    // 'EvalHelix:51' Sign        = sign(P0P1'*evec);
    //
    // 'EvalHelix:53' r0D       = bsxfun(@plus, C, cphiTCP0  + sphiTEcrCP0  + ...
    // 'EvalHelix:54'                    pitch/(2*pi)*evec*phi_vec);
    a = CurvStruct_pitch / 6.2831853071795862;
    r = _mm_loadu_pd(&CP0[0]);
    r1 = _mm_loadu_pd(&EcrCP0[0]);
    for (int k{0}; k < 10; k++) {
        __m128d r2;
        __m128d r3;
        __m128d r4;
        __m128d r6;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        d = CurvStruct_theta * u_vec[k];
        d1 = std::cos(d);
        d2 = std::sin(d);
        r2 = _mm_set1_pd(d1);
        r3 = _mm_mul_pd(r, r2);
        _mm_storeu_pd(&cphiTCP0[k][0], r3);
        r4 = _mm_set1_pd(d2);
        _mm_storeu_pd(&sphiTCP0[k][0], _mm_mul_pd(r, r4));
        _mm_storeu_pd(&cphiTEcrCP0[k][0], _mm_mul_pd(r1, r2));
        r6 = _mm_mul_pd(r1, r4);
        _mm_storeu_pd(&sphiTEcrCP0[k][0], r6);
        _mm_storeu_pd(
            &r0D[k][0],
            _mm_add_pd(
                _mm_loadu_pd((const double *)&CurvStruct_CorrectedHelixCenter[0]),
                _mm_add_pd(
                    _mm_add_pd(r3, r6),
                    _mm_add_pd(
                        _mm_set1_pd(0.0),
                        _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a),
                                              _mm_loadu_pd((const double *)&CurvStruct_evec[0])),
                                   _mm_set1_pd(d))))));
        d3 = CP0[2] * d1;
        cphiTCP0[k][2] = d3;
        sphiTCP0[k][2] = CP0[2] * d2;
        cphiTEcrCP0[k][2] = EcrCP0[2] * d1;
        d4 = EcrCP0[2] * d2;
        sphiTEcrCP0[k][2] = d4;
        r0D[k][2] = CurvStruct_CorrectedHelixCenter[2] + ((d3 + d4) + a * CurvStruct_evec[2] * d);
    }
    double b_a;
    // 'EvalHelix:55' r1D       = bsxfun(@plus, -theta  *sphiTCP0  + theta  *cphiTEcrCP0, ...
    // 'EvalHelix:56'                    theta * pitch/(2*pi) * evec);
    b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
    _mm_storeu_pd(&y[0],
                  _mm_mul_pd(_mm_set1_pd(b_a), _mm_loadu_pd((const double *)&CurvStruct_evec[0])));
    y[2] = b_a * CurvStruct_evec[2];
    // 'EvalHelix:57' r2D       = -theta^2*cphiTCP0  - theta^2*sphiTEcrCP0;
    a_tmp = CurvStruct_theta * CurvStruct_theta;
    // 'EvalHelix:58' r3D       =  theta^3*sphiTCP0  - theta^3*cphiTEcrCP0;
    b_a_tmp = std::pow(CurvStruct_theta, 3.0);
    r5 = _mm_loadu_pd(&y[0]);
    r7 = _mm_set1_pd(b_a_tmp);
    for (int b_k{0}; b_k < 10; b_k++) {
        __m128d r10;
        __m128d r11;
        __m128d r8;
        __m128d r9;
        double d5;
        double d6;
        r8 = _mm_loadu_pd(&sphiTCP0[b_k][0]);
        r9 = _mm_loadu_pd(&cphiTEcrCP0[b_k][0]);
        _mm_storeu_pd(&r1D[b_k][0],
                      _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(-CurvStruct_theta), r8),
                                            _mm_mul_pd(_mm_set1_pd(CurvStruct_theta), r9)),
                                 r5));
        r10 = _mm_loadu_pd(&cphiTCP0[b_k][0]);
        r11 = _mm_loadu_pd(&sphiTEcrCP0[b_k][0]);
        _mm_storeu_pd(&r2D[b_k][0], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(-a_tmp), r10),
                                               _mm_mul_pd(_mm_set1_pd(a_tmp), r11)));
        _mm_storeu_pd(&r3D[b_k][0], _mm_sub_pd(_mm_mul_pd(r7, r8), _mm_mul_pd(r7, r9)));
        d5 = sphiTCP0[b_k][2];
        d6 = cphiTEcrCP0[b_k][2];
        r1D[b_k][2] = (-CurvStruct_theta * d5 + CurvStruct_theta * d6) + y[2];
        r2D[b_k][2] = -a_tmp * cphiTCP0[b_k][2] - a_tmp * sphiTEcrCP0[b_k][2];
        r3D[b_k][2] = b_a_tmp * d5 - b_a_tmp * d6;
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec)
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
// Arguments    : const double CurvStruct_P0[3]
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
void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_CorrectedHelixCenter[3],
               const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
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
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> sphi;
    ::coder::array<double, 2U> sphiTCP0;
    ::coder::array<double, 2U> sphiTEcrCP0;
    double CP0[3];
    double EcrCP0[3];
    double y[3];
    double a;
    double a_tmp;
    double b_a;
    double b_a_tmp;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i;
    int i10;
    int i2;
    int i4;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    // 'EvalHelix:18' if ~coder.target('MATLAB')
    // 'EvalHelix:19' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalHelix:20' coder.inline('never')
    // 'EvalHelix:21' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalHelix"'));
    ZoneScopedN("EvalHelix");
    //  Extract parameters from the struct
    // 'EvalHelix:24' P0      = CurvStruct.P0;
    // 'EvalHelix:25' P1      = CurvStruct.P1;
    // 'EvalHelix:26' evec    = CurvStruct.evec;
    // 'EvalHelix:27' theta   = CurvStruct.theta;
    // 'EvalHelix:28' pitch   = CurvStruct.pitch;
    // 'EvalHelix:30' N       = length(u_vec);
    // 'EvalHelix:31' P0P1    = P0 - P1;
    // 'EvalHelix:33' r0D = zeros(3, N);
    // 'EvalHelix:34' r1D = zeros(3, N);
    // 'EvalHelix:35' r2D = zeros(3, N);
    // 'EvalHelix:36' r3D = zeros(3, N);
    //
    // 'EvalHelix:39' C           = CurvStruct.CorrectedHelixCenter;
    // 'EvalHelix:40' CP0         = P0 - C;
    _mm_storeu_pd(&CP0[0],
                  _mm_sub_pd(_mm_loadu_pd((const double *)&CurvStruct_P0[0]),
                             _mm_loadu_pd((const double *)&CurvStruct_CorrectedHelixCenter[0])));
    CP0[2] = CurvStruct_P0[2] - CurvStruct_CorrectedHelixCenter[2];
    // 'EvalHelix:41' phi_vec     = theta*u_vec;
    phi_vec.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1);
    scalarLB = (u_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i = 0; i <= vectorUB; i += 2) {
        _mm_storeu_pd(&phi_vec[i], _mm_mul_pd(_mm_set1_pd(CurvStruct_theta),
                                              _mm_loadu_pd((const double *)&u_vec[i])));
    }
    for (i = scalarLB; i < loop_ub; i++) {
        phi_vec[i] = CurvStruct_theta * u_vec[i];
    }
    // 'EvalHelix:42' EcrCP0      = cross(evec, CP0);
    EcrCP0[0] = CurvStruct_evec[1] * CP0[2] - CP0[1] * CurvStruct_evec[2];
    EcrCP0[1] = CP0[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * CP0[2];
    EcrCP0[2] = CurvStruct_evec[0] * CP0[1] - CP0[0] * CurvStruct_evec[1];
    //  clockwise tangent vector
    // 'EvalHelix:43' cphi        = mycos(phi_vec);
    // 'mycos:3' y = cos(x);
    cphi.set_size(1, phi_vec.size(1));
    b_loop_ub = phi_vec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        cphi[i1] = phi_vec[i1];
    }
    i2 = phi_vec.size(1);
    for (int k{0}; k < i2; k++) {
        cphi[k] = std::cos(cphi[k]);
    }
    // 'mycos:4' cos_calls = cos_calls + 1;
    cos_calls++;
    // 'EvalHelix:44' sphi        = mysin(phi_vec);
    // 'mysin:3' y = sin(x);
    sphi.set_size(1, phi_vec.size(1));
    c_loop_ub = phi_vec.size(1);
    for (int i3{0}; i3 < c_loop_ub; i3++) {
        sphi[i3] = phi_vec[i3];
    }
    i4 = phi_vec.size(1);
    for (int b_k{0}; b_k < i4; b_k++) {
        sphi[b_k] = std::sin(sphi[b_k]);
    }
    // 'mysin:4' sin_calls = sin_calls + 1;
    sin_calls++;
    //
    // 'EvalHelix:47' cphiTCP0    = CP0 * cphi;
    cphiTCP0.set_size(3, cphi.size(1));
    d_loop_ub = cphi.size(1);
    for (int i5{0}; i5 < d_loop_ub; i5++) {
        __m128d r;
        r = _mm_loadu_pd(&CP0[0]);
        _mm_storeu_pd(&cphiTCP0[3 * i5], _mm_mul_pd(r, _mm_set1_pd(cphi[i5])));
        cphiTCP0[3 * i5 + 2] = CP0[2] * cphi[i5];
    }
    // 'EvalHelix:48' sphiTCP0    = CP0 * sphi;
    sphiTCP0.set_size(3, sphi.size(1));
    e_loop_ub = sphi.size(1);
    for (int i6{0}; i6 < e_loop_ub; i6++) {
        __m128d r1;
        r1 = _mm_loadu_pd(&CP0[0]);
        _mm_storeu_pd(&sphiTCP0[3 * i6], _mm_mul_pd(r1, _mm_set1_pd(sphi[i6])));
        sphiTCP0[3 * i6 + 2] = CP0[2] * sphi[i6];
    }
    // 'EvalHelix:49' cphiTEcrCP0 = EcrCP0 * cphi;
    cphiTEcrCP0.set_size(3, cphi.size(1));
    f_loop_ub = cphi.size(1);
    for (int i7{0}; i7 < f_loop_ub; i7++) {
        __m128d r2;
        r2 = _mm_loadu_pd(&EcrCP0[0]);
        _mm_storeu_pd(&cphiTEcrCP0[3 * i7], _mm_mul_pd(r2, _mm_set1_pd(cphi[i7])));
        cphiTEcrCP0[3 * i7 + 2] = EcrCP0[2] * cphi[i7];
    }
    // 'EvalHelix:50' sphiTEcrCP0 = EcrCP0 * sphi;
    sphiTEcrCP0.set_size(3, sphi.size(1));
    g_loop_ub = sphi.size(1);
    for (int i8{0}; i8 < g_loop_ub; i8++) {
        __m128d r3;
        r3 = _mm_loadu_pd(&EcrCP0[0]);
        _mm_storeu_pd(&sphiTEcrCP0[3 * i8], _mm_mul_pd(r3, _mm_set1_pd(sphi[i8])));
        sphiTEcrCP0[3 * i8 + 2] = EcrCP0[2] * sphi[i8];
    }
    // 'EvalHelix:51' Sign        = sign(P0P1'*evec);
    //
    // 'EvalHelix:53' r0D       = bsxfun(@plus, C, cphiTCP0  + sphiTEcrCP0  + ...
    // 'EvalHelix:54'                    pitch/(2*pi)*evec*phi_vec);
    a = CurvStruct_pitch / 6.2831853071795862;
    r4.set_size(3, phi_vec.size(1));
    h_loop_ub = phi_vec.size(1);
    for (int i9{0}; i9 < h_loop_ub; i9++) {
        _mm_storeu_pd(&r4[3 * i9],
                      _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a),
                                            _mm_loadu_pd((const double *)&CurvStruct_evec[0])),
                                 _mm_set1_pd(phi_vec[i9])));
        r4[3 * i9 + 2] = a * CurvStruct_evec[2] * phi_vec[i9];
    }
    if (cphiTCP0.size(1) == 1) {
        i10 = sphiTEcrCP0.size(1);
    } else {
        i10 = cphiTCP0.size(1);
    }
    if ((cphiTCP0.size(1) == sphiTEcrCP0.size(1)) && (i10 == r4.size(1))) {
        int i_loop_ub;
        b.set_size(3, phi_vec.size(1));
        i_loop_ub = phi_vec.size(1);
        for (int i11{0}; i11 < i_loop_ub; i11++) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&cphiTCP0[3 * i11]);
            r6 = _mm_loadu_pd(&sphiTEcrCP0[3 * i11]);
            _mm_storeu_pd(
                &b[3 * i11],
                _mm_add_pd(
                    _mm_add_pd(r5, r6),
                    _mm_add_pd(
                        _mm_set1_pd(0.0),
                        _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a),
                                              _mm_loadu_pd((const double *)&CurvStruct_evec[0])),
                                   _mm_set1_pd(phi_vec[i11])))));
            b[3 * i11 + 2] = (cphiTCP0[3 * i11 + 2] + sphiTEcrCP0[3 * i11 + 2]) +
                             a * CurvStruct_evec[2] * phi_vec[i11];
        }
    } else {
        binary_expand_op(b, cphiTCP0, sphiTEcrCP0, a, CurvStruct_evec, phi_vec);
    }
    r0D.set_size(3, b.size(1));
    if (b.size(1) != 0) {
        int bcoef;
        int i12;
        bcoef = (b.size(1) != 1);
        i12 = b.size(1) - 1;
        for (int c_k{0}; c_k <= i12; c_k++) {
            __m128d r7;
            int varargin_3;
            varargin_3 = bcoef * c_k;
            r7 = _mm_loadu_pd(&b[3 * varargin_3]);
            _mm_storeu_pd(
                &r0D[3 * c_k],
                _mm_add_pd(_mm_loadu_pd((const double *)&CurvStruct_CorrectedHelixCenter[0]), r7));
            r0D[3 * c_k + 2] = CurvStruct_CorrectedHelixCenter[2] + b[3 * varargin_3 + 2];
        }
    }
    // 'EvalHelix:55' r1D       = bsxfun(@plus, -theta  *sphiTCP0  + theta  *cphiTEcrCP0, ...
    // 'EvalHelix:56'                    theta * pitch/(2*pi) * evec);
    b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
    _mm_storeu_pd(&y[0],
                  _mm_mul_pd(_mm_set1_pd(b_a), _mm_loadu_pd((const double *)&CurvStruct_evec[0])));
    y[2] = b_a * CurvStruct_evec[2];
    if (sphiTCP0.size(1) == cphiTEcrCP0.size(1)) {
        int j_loop_ub;
        c_a.set_size(3, sphiTCP0.size(1));
        j_loop_ub = sphiTCP0.size(1);
        for (int i13{0}; i13 < j_loop_ub; i13++) {
            __m128d r8;
            __m128d r9;
            r8 = _mm_loadu_pd(&sphiTCP0[3 * i13]);
            r9 = _mm_loadu_pd(&cphiTEcrCP0[3 * i13]);
            _mm_storeu_pd(&c_a[3 * i13], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(-CurvStruct_theta), r8),
                                                    _mm_mul_pd(_mm_set1_pd(CurvStruct_theta), r9)));
            c_a[3 * i13 + 2] = -CurvStruct_theta * sphiTCP0[3 * i13 + 2] +
                               CurvStruct_theta * cphiTEcrCP0[3 * i13 + 2];
        }
    } else {
        binary_expand_op(c_a, CurvStruct_theta, sphiTCP0, cphiTEcrCP0);
    }
    r1D.set_size(3, c_a.size(1));
    if (c_a.size(1) != 0) {
        int acoef;
        int i14;
        acoef = (c_a.size(1) != 1);
        i14 = c_a.size(1) - 1;
        for (int d_k{0}; d_k <= i14; d_k++) {
            __m128d r10;
            __m128d r11;
            int varargin_2;
            varargin_2 = acoef * d_k;
            r10 = _mm_loadu_pd(&c_a[3 * varargin_2]);
            r11 = _mm_loadu_pd(&y[0]);
            _mm_storeu_pd(&r1D[3 * d_k], _mm_add_pd(r10, r11));
            r1D[3 * d_k + 2] = c_a[3 * varargin_2 + 2] + y[2];
        }
    }
    // 'EvalHelix:57' r2D       = -theta^2*cphiTCP0  - theta^2*sphiTEcrCP0;
    a_tmp = CurvStruct_theta * CurvStruct_theta;
    if (cphiTCP0.size(1) == sphiTEcrCP0.size(1)) {
        int k_loop_ub;
        r2D.set_size(3, cphiTCP0.size(1));
        k_loop_ub = cphiTCP0.size(1);
        for (int i15{0}; i15 < k_loop_ub; i15++) {
            __m128d r12;
            __m128d r13;
            r12 = _mm_loadu_pd(&cphiTCP0[3 * i15]);
            r13 = _mm_loadu_pd(&sphiTEcrCP0[3 * i15]);
            _mm_storeu_pd(&r2D[3 * i15], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(-a_tmp), r12),
                                                    _mm_mul_pd(_mm_set1_pd(a_tmp), r13)));
            r2D[3 * i15 + 2] = -a_tmp * cphiTCP0[3 * i15 + 2] - a_tmp * sphiTEcrCP0[3 * i15 + 2];
        }
    } else {
        binary_expand_op(r2D, -a_tmp, cphiTCP0, a_tmp, sphiTEcrCP0);
    }
    // 'EvalHelix:58' r3D       =  theta^3*sphiTCP0  - theta^3*cphiTEcrCP0;
    b_a_tmp = std::pow(CurvStruct_theta, 3.0);
    if (sphiTCP0.size(1) == cphiTEcrCP0.size(1)) {
        int l_loop_ub;
        r3D.set_size(3, sphiTCP0.size(1));
        l_loop_ub = sphiTCP0.size(1);
        for (int i16{0}; i16 < l_loop_ub; i16++) {
            __m128d r14;
            __m128d r15;
            __m128d r16;
            r14 = _mm_loadu_pd(&sphiTCP0[3 * i16]);
            r15 = _mm_loadu_pd(&cphiTEcrCP0[3 * i16]);
            r16 = _mm_set1_pd(b_a_tmp);
            _mm_storeu_pd(&r3D[3 * i16], _mm_sub_pd(_mm_mul_pd(r16, r14), _mm_mul_pd(r16, r15)));
            r3D[3 * i16 + 2] = b_a_tmp * sphiTCP0[3 * i16 + 2] - b_a_tmp * cphiTEcrCP0[3 * i16 + 2];
        }
    } else {
        binary_expand_op(r3D, b_a_tmp, sphiTCP0, b_a_tmp, cphiTEcrCP0);
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalHelix(CurvStruct, u_vec)
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
// Arguments    : const double CurvStruct_P0[3]
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
void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_CorrectedHelixCenter[3],
               const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
               double u_vec, double r0D[3], double r1D[3], double r2D[3], double r3D[3])
{
    __m128d r;
    __m128d r1;
    __m128d r2;
    __m128d r3;
    __m128d r4;
    __m128d r5;
    __m128d r6;
    __m128d r7;
    __m128d r8;
    __m128d r9;
    double CP0[3];
    double EcrCP0[3];
    double cphiTCP0[3];
    double sphiTCP0[3];
    double a;
    double a_tmp;
    double b_a;
    double b_a_tmp;
    double cphi;
    double d;
    double d1;
    double d2;
    double phi_vec;
    double sphi;
    // 'EvalHelix:18' if ~coder.target('MATLAB')
    // 'EvalHelix:19' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalHelix:20' coder.inline('never')
    // 'EvalHelix:21' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalHelix"'));
    ZoneScopedN("EvalHelix");
    //  Extract parameters from the struct
    // 'EvalHelix:24' P0      = CurvStruct.P0;
    // 'EvalHelix:25' P1      = CurvStruct.P1;
    // 'EvalHelix:26' evec    = CurvStruct.evec;
    // 'EvalHelix:27' theta   = CurvStruct.theta;
    // 'EvalHelix:28' pitch   = CurvStruct.pitch;
    // 'EvalHelix:30' N       = length(u_vec);
    // 'EvalHelix:31' P0P1    = P0 - P1;
    // 'EvalHelix:33' r0D = zeros(3, N);
    // 'EvalHelix:34' r1D = zeros(3, N);
    // 'EvalHelix:35' r2D = zeros(3, N);
    // 'EvalHelix:36' r3D = zeros(3, N);
    //
    // 'EvalHelix:39' C           = CurvStruct.CorrectedHelixCenter;
    // 'EvalHelix:40' CP0         = P0 - C;
    // 'EvalHelix:41' phi_vec     = theta*u_vec;
    phi_vec = CurvStruct_theta * u_vec;
    // 'EvalHelix:42' EcrCP0      = cross(evec, CP0);
    //  clockwise tangent vector
    // 'EvalHelix:43' cphi        = mycos(phi_vec);
    // 'mycos:3' y = cos(x);
    cphi = std::cos(phi_vec);
    // 'mycos:4' cos_calls = cos_calls + 1;
    cos_calls++;
    // 'EvalHelix:44' sphi        = mysin(phi_vec);
    // 'mysin:3' y = sin(x);
    sphi = std::sin(phi_vec);
    // 'mysin:4' sin_calls = sin_calls + 1;
    sin_calls++;
    //
    // 'EvalHelix:47' cphiTCP0    = CP0 * cphi;
    // 'EvalHelix:48' sphiTCP0    = CP0 * sphi;
    r = _mm_sub_pd(_mm_loadu_pd((const double *)&CurvStruct_P0[0]),
                   _mm_loadu_pd((const double *)&CurvStruct_CorrectedHelixCenter[0]));
    _mm_storeu_pd(&CP0[0], r);
    r1 = _mm_set1_pd(cphi);
    _mm_storeu_pd(&cphiTCP0[0], _mm_mul_pd(r, r1));
    r2 = _mm_set1_pd(sphi);
    _mm_storeu_pd(&sphiTCP0[0], _mm_mul_pd(r, r2));
    d = CurvStruct_P0[2] - CurvStruct_CorrectedHelixCenter[2];
    cphiTCP0[2] = d * cphi;
    sphiTCP0[2] = d * sphi;
    EcrCP0[0] = CurvStruct_evec[1] * d - CP0[1] * CurvStruct_evec[2];
    EcrCP0[1] = CP0[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * d;
    EcrCP0[2] = CurvStruct_evec[0] * CP0[1] - CP0[0] * CurvStruct_evec[1];
    // 'EvalHelix:49' cphiTEcrCP0 = EcrCP0 * cphi;
    // 'EvalHelix:50' sphiTEcrCP0 = EcrCP0 * sphi;
    // 'EvalHelix:51' Sign        = sign(P0P1'*evec);
    //
    // 'EvalHelix:53' r0D       = bsxfun(@plus, C, cphiTCP0  + sphiTEcrCP0  + ...
    // 'EvalHelix:54'                    pitch/(2*pi)*evec*phi_vec);
    a = CurvStruct_pitch / 6.2831853071795862;
    // 'EvalHelix:55' r1D       = bsxfun(@plus, -theta  *sphiTCP0  + theta  *cphiTEcrCP0, ...
    // 'EvalHelix:56'                    theta * pitch/(2*pi) * evec);
    b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
    // 'EvalHelix:57' r2D       = -theta^2*cphiTCP0  - theta^2*sphiTEcrCP0;
    a_tmp = CurvStruct_theta * CurvStruct_theta;
    // 'EvalHelix:58' r3D       =  theta^3*sphiTCP0  - theta^3*cphiTEcrCP0;
    b_a_tmp = std::pow(CurvStruct_theta, 3.0);
    r3 = _mm_loadu_pd(&EcrCP0[0]);
    r4 = _mm_mul_pd(r3, r1);
    r5 = _mm_mul_pd(r3, r2);
    r6 = _mm_loadu_pd(&cphiTCP0[0]);
    r7 = _mm_loadu_pd((const double *)&CurvStruct_evec[0]);
    _mm_storeu_pd(
        &r0D[0],
        _mm_add_pd(_mm_loadu_pd((const double *)&CurvStruct_CorrectedHelixCenter[0]),
                   _mm_add_pd(_mm_add_pd(r6, r5),
                              _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a), r7), _mm_set1_pd(phi_vec)))));
    r8 = _mm_loadu_pd(&sphiTCP0[0]);
    _mm_storeu_pd(&r1D[0], _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(-CurvStruct_theta), r8),
                                                 _mm_mul_pd(_mm_set1_pd(CurvStruct_theta), r4)),
                                      _mm_mul_pd(_mm_set1_pd(b_a), r7)));
    _mm_storeu_pd(&r2D[0], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(-a_tmp), r6),
                                      _mm_mul_pd(_mm_set1_pd(a_tmp), r5)));
    r9 = _mm_set1_pd(b_a_tmp);
    _mm_storeu_pd(&r3D[0], _mm_sub_pd(_mm_mul_pd(r9, r8), _mm_mul_pd(r9, r4)));
    d1 = EcrCP0[2] * cphi;
    d2 = EcrCP0[2] * sphi;
    r0D[2] = CurvStruct_CorrectedHelixCenter[2] +
             ((cphiTCP0[2] + d2) + a * CurvStruct_evec[2] * phi_vec);
    r1D[2] = (-CurvStruct_theta * sphiTCP0[2] + CurvStruct_theta * d1) + b_a * CurvStruct_evec[2];
    r2D[2] = -a_tmp * cphiTCP0[2] - a_tmp * d2;
    r3D[2] = b_a_tmp * sphiTCP0[2] - b_a_tmp * d1;
}

} // namespace ocn

//
// File trailer for EvalHelix.cpp
//
// [EOF]
//
