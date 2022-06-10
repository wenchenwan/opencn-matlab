//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalHelix.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
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

static void binary_expand_op(double CP0[3], const double CurvStruct_R0[6], const int indC_data[],
                             const int *indC_size, const double CurvStruct_CorrectedHelixCenter[3]);

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
// Arguments    : double CP0[3]
//                const double CurvStruct_R0[6]
//                const int indC_data[]
//                const int *indC_size
//                const double CurvStruct_CorrectedHelixCenter[3]
// Return Type  : void
//
static void binary_expand_op(double CP0[3], const double CurvStruct_R0[6], const int indC_data[],
                             const int *indC_size, const double CurvStruct_CorrectedHelixCenter[3])
{
    int stride_0_0;
    stride_0_0 = (*indC_size != 1);
    CP0[0] = CurvStruct_R0[indC_data[0] - 1] - CurvStruct_CorrectedHelixCenter[0];
    CP0[1] = CurvStruct_R0[indC_data[stride_0_0] - 1] - CurvStruct_CorrectedHelixCenter[1];
    CP0[2] = CurvStruct_R0[indC_data[stride_0_0 << 1] - 1] - CurvStruct_CorrectedHelixCenter[2];
}

//
// function [r0D, r1D, r2D, r3D] = EvalHelix( CurvStruct, u_vec, indC )
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
//                const int indC_data[]
//                int indC_size
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void EvalHelix(const double CurvStruct_R0[6], const double CurvStruct_CorrectedHelixCenter[3],
               const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
               const ::coder::array<double, 2U> &u_vec, const int indC_data[], int indC_size,
               ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D,
               ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D)
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
    int i1;
    int i11;
    int i3;
    int i5;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    // 'EvalHelix:18' if ~coder.target('MATLAB')
    // 'EvalHelix:19' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalHelix:20' coder.inline('never')
    // 'EvalHelix:21' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalHelix"'));
    ZoneScopedN("EvalHelix");
    //  Extract parameters from the struct
    // 'EvalHelix:24' indCart = indC;
    // 'EvalHelix:25' P0      = CurvStruct.R0( indCart );
    // 'EvalHelix:26' P1      = CurvStruct.R1( indCart );
    // 'EvalHelix:27' evec    = CurvStruct.evec;
    // 'EvalHelix:28' theta   = CurvStruct.theta;
    // 'EvalHelix:29' pitch   = CurvStruct.pitch;
    // 'EvalHelix:31' P0P1    = P0 - P1;
    //
    // 'EvalHelix:34' C           = CurvStruct.CorrectedHelixCenter;
    // 'EvalHelix:35' CP0         = P0 - C;
    if (indC_size == 3) {
        for (int i{0}; i < 3; i++) {
            CP0[i] = CurvStruct_R0[indC_data[i] - 1] - CurvStruct_CorrectedHelixCenter[i];
        }
    } else {
        binary_expand_op(CP0, CurvStruct_R0, indC_data, &indC_size,
                         CurvStruct_CorrectedHelixCenter);
    }
    // 'EvalHelix:36' phi_vec     = theta * u_vec;
    phi_vec.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1);
    scalarLB = (u_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i1 = 0; i1 <= vectorUB; i1 += 2) {
        _mm_storeu_pd(&phi_vec[i1], _mm_mul_pd(_mm_set1_pd(CurvStruct_theta),
                                               _mm_loadu_pd((const double *)&u_vec[i1])));
    }
    for (i1 = scalarLB; i1 < loop_ub; i1++) {
        phi_vec[i1] = CurvStruct_theta * u_vec[i1];
    }
    // 'EvalHelix:37' EcrCP0      = cross( evec, CP0 );
    EcrCP0[0] = CurvStruct_evec[1] * CP0[2] - CP0[1] * CurvStruct_evec[2];
    EcrCP0[1] = CP0[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * CP0[2];
    EcrCP0[2] = CurvStruct_evec[0] * CP0[1] - CP0[0] * CurvStruct_evec[1];
    //  clockwise tangent vector
    // 'EvalHelix:38' cphi        = mycos( phi_vec );
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
    // 'EvalHelix:39' sphi        = mysin( phi_vec );
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
    // 'EvalHelix:42' cphiTCP0    = CP0 * cphi;
    cphiTCP0.set_size(3, cphi.size(1));
    d_loop_ub = cphi.size(1);
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        __m128d r;
        r = _mm_loadu_pd(&CP0[0]);
        _mm_storeu_pd(&cphiTCP0[3 * i6], _mm_mul_pd(r, _mm_set1_pd(cphi[i6])));
        cphiTCP0[3 * i6 + 2] = CP0[2] * cphi[i6];
    }
    // 'EvalHelix:43' sphiTCP0    = CP0 * sphi;
    sphiTCP0.set_size(3, sphi.size(1));
    e_loop_ub = sphi.size(1);
    for (int i7{0}; i7 < e_loop_ub; i7++) {
        __m128d r1;
        r1 = _mm_loadu_pd(&CP0[0]);
        _mm_storeu_pd(&sphiTCP0[3 * i7], _mm_mul_pd(r1, _mm_set1_pd(sphi[i7])));
        sphiTCP0[3 * i7 + 2] = CP0[2] * sphi[i7];
    }
    // 'EvalHelix:44' cphiTEcrCP0 = EcrCP0 * cphi;
    cphiTEcrCP0.set_size(3, cphi.size(1));
    f_loop_ub = cphi.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        __m128d r2;
        r2 = _mm_loadu_pd(&EcrCP0[0]);
        _mm_storeu_pd(&cphiTEcrCP0[3 * i8], _mm_mul_pd(r2, _mm_set1_pd(cphi[i8])));
        cphiTEcrCP0[3 * i8 + 2] = EcrCP0[2] * cphi[i8];
    }
    // 'EvalHelix:45' sphiTEcrCP0 = EcrCP0 * sphi;
    sphiTEcrCP0.set_size(3, sphi.size(1));
    g_loop_ub = sphi.size(1);
    for (int i9{0}; i9 < g_loop_ub; i9++) {
        __m128d r3;
        r3 = _mm_loadu_pd(&EcrCP0[0]);
        _mm_storeu_pd(&sphiTEcrCP0[3 * i9], _mm_mul_pd(r3, _mm_set1_pd(sphi[i9])));
        sphiTEcrCP0[3 * i9 + 2] = EcrCP0[2] * sphi[i9];
    }
    // 'EvalHelix:46' Sign        = sign( P0P1'*evec );
    //
    // 'EvalHelix:48' r0D       = bsxfun(@plus, C, cphiTCP0  + sphiTEcrCP0  + ...
    // 'EvalHelix:49'                    pitch/(2*pi)*evec*phi_vec);
    a = CurvStruct_pitch / 6.2831853071795862;
    r4.set_size(3, phi_vec.size(1));
    h_loop_ub = phi_vec.size(1);
    for (int i10{0}; i10 < h_loop_ub; i10++) {
        _mm_storeu_pd(&r4[3 * i10],
                      _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a),
                                            _mm_loadu_pd((const double *)&CurvStruct_evec[0])),
                                 _mm_set1_pd(phi_vec[i10])));
        r4[3 * i10 + 2] = a * CurvStruct_evec[2] * phi_vec[i10];
    }
    if (cphiTCP0.size(1) == 1) {
        i11 = sphiTEcrCP0.size(1);
    } else {
        i11 = cphiTCP0.size(1);
    }
    if ((cphiTCP0.size(1) == sphiTEcrCP0.size(1)) && (i11 == r4.size(1))) {
        int i_loop_ub;
        b.set_size(3, phi_vec.size(1));
        i_loop_ub = phi_vec.size(1);
        for (int i12{0}; i12 < i_loop_ub; i12++) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&cphiTCP0[3 * i12]);
            r6 = _mm_loadu_pd(&sphiTEcrCP0[3 * i12]);
            _mm_storeu_pd(
                &b[3 * i12],
                _mm_add_pd(
                    _mm_add_pd(r5, r6),
                    _mm_add_pd(
                        _mm_set1_pd(0.0),
                        _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a),
                                              _mm_loadu_pd((const double *)&CurvStruct_evec[0])),
                                   _mm_set1_pd(phi_vec[i12])))));
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
    // 'EvalHelix:50' r1D       = bsxfun(@plus, -theta  *sphiTCP0  + theta  *cphiTEcrCP0, ...
    // 'EvalHelix:51'                    theta * pitch/(2*pi) * evec);
    b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
    _mm_storeu_pd(&y[0],
                  _mm_mul_pd(_mm_set1_pd(b_a), _mm_loadu_pd((const double *)&CurvStruct_evec[0])));
    y[2] = b_a * CurvStruct_evec[2];
    if (sphiTCP0.size(1) == cphiTEcrCP0.size(1)) {
        int j_loop_ub;
        c_a.set_size(3, sphiTCP0.size(1));
        j_loop_ub = sphiTCP0.size(1);
        for (int i14{0}; i14 < j_loop_ub; i14++) {
            __m128d r8;
            __m128d r9;
            r8 = _mm_loadu_pd(&sphiTCP0[3 * i14]);
            r9 = _mm_loadu_pd(&cphiTEcrCP0[3 * i14]);
            _mm_storeu_pd(&c_a[3 * i14], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(-CurvStruct_theta), r8),
                                                    _mm_mul_pd(_mm_set1_pd(CurvStruct_theta), r9)));
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
    // 'EvalHelix:52' r2D       = -theta^2*cphiTCP0  - theta^2*sphiTEcrCP0;
    a_tmp = CurvStruct_theta * CurvStruct_theta;
    if (cphiTCP0.size(1) == sphiTEcrCP0.size(1)) {
        int k_loop_ub;
        r2D.set_size(3, cphiTCP0.size(1));
        k_loop_ub = cphiTCP0.size(1);
        for (int i16{0}; i16 < k_loop_ub; i16++) {
            __m128d r12;
            __m128d r13;
            r12 = _mm_loadu_pd(&cphiTCP0[3 * i16]);
            r13 = _mm_loadu_pd(&sphiTEcrCP0[3 * i16]);
            _mm_storeu_pd(&r2D[3 * i16], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(-a_tmp), r12),
                                                    _mm_mul_pd(_mm_set1_pd(a_tmp), r13)));
            r2D[3 * i16 + 2] = -a_tmp * cphiTCP0[3 * i16 + 2] - a_tmp * sphiTEcrCP0[3 * i16 + 2];
        }
    } else {
        binary_expand_op(r2D, -a_tmp, cphiTCP0, a_tmp, sphiTEcrCP0);
    }
    // 'EvalHelix:53' r3D       =  theta^3*sphiTCP0  - theta^3*cphiTEcrCP0;
    b_a_tmp = std::pow(CurvStruct_theta, 3.0);
    if (sphiTCP0.size(1) == cphiTEcrCP0.size(1)) {
        int l_loop_ub;
        r3D.set_size(3, sphiTCP0.size(1));
        l_loop_ub = sphiTCP0.size(1);
        for (int i17{0}; i17 < l_loop_ub; i17++) {
            __m128d r14;
            __m128d r15;
            __m128d r16;
            r14 = _mm_loadu_pd(&sphiTCP0[3 * i17]);
            r15 = _mm_loadu_pd(&cphiTEcrCP0[3 * i17]);
            r16 = _mm_set1_pd(b_a_tmp);
            _mm_storeu_pd(&r3D[3 * i17], _mm_sub_pd(_mm_mul_pd(r16, r14), _mm_mul_pd(r16, r15)));
            r3D[3 * i17 + 2] = b_a_tmp * sphiTCP0[3 * i17 + 2] - b_a_tmp * cphiTEcrCP0[3 * i17 + 2];
        }
    } else {
        binary_expand_op(r3D, b_a_tmp, sphiTCP0, b_a_tmp, cphiTEcrCP0);
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalHelix( CurvStruct, u_vec, indC )
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
//                const int indC_data[]
//                int indC_size
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
//                double r3D[3]
// Return Type  : void
//
void EvalHelix(const double CurvStruct_R0[6], const double CurvStruct_CorrectedHelixCenter[3],
               const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
               double u_vec, const int indC_data[], int indC_size, double r0D[3], double r1D[3],
               double r2D[3], double r3D[3])
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
    // 'EvalHelix:18' if ~coder.target('MATLAB')
    // 'EvalHelix:19' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalHelix:20' coder.inline('never')
    // 'EvalHelix:21' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalHelix"'));
    ZoneScopedN("EvalHelix");
    //  Extract parameters from the struct
    // 'EvalHelix:24' indCart = indC;
    // 'EvalHelix:25' P0      = CurvStruct.R0( indCart );
    // 'EvalHelix:26' P1      = CurvStruct.R1( indCart );
    // 'EvalHelix:27' evec    = CurvStruct.evec;
    // 'EvalHelix:28' theta   = CurvStruct.theta;
    // 'EvalHelix:29' pitch   = CurvStruct.pitch;
    // 'EvalHelix:31' P0P1    = P0 - P1;
    //
    // 'EvalHelix:34' C           = CurvStruct.CorrectedHelixCenter;
    // 'EvalHelix:35' CP0         = P0 - C;
    if (indC_size == 3) {
        for (int i{0}; i < 3; i++) {
            CP0[i] = CurvStruct_R0[indC_data[i] - 1] - CurvStruct_CorrectedHelixCenter[i];
        }
    } else {
        binary_expand_op(CP0, CurvStruct_R0, indC_data, &indC_size,
                         CurvStruct_CorrectedHelixCenter);
    }
    // 'EvalHelix:36' phi_vec     = theta * u_vec;
    phi_vec = CurvStruct_theta * u_vec;
    // 'EvalHelix:37' EcrCP0      = cross( evec, CP0 );
    EcrCP0[0] = CurvStruct_evec[1] * CP0[2] - CP0[1] * CurvStruct_evec[2];
    EcrCP0[1] = CP0[0] * CurvStruct_evec[2] - CurvStruct_evec[0] * CP0[2];
    EcrCP0[2] = CurvStruct_evec[0] * CP0[1] - CP0[0] * CurvStruct_evec[1];
    //  clockwise tangent vector
    // 'EvalHelix:38' cphi        = mycos( phi_vec );
    // 'mycos:3' y = cos(x);
    cphi = std::cos(phi_vec);
    // 'mycos:4' cos_calls = cos_calls + 1;
    cos_calls++;
    // 'EvalHelix:39' sphi        = mysin( phi_vec );
    // 'mysin:3' y = sin(x);
    sphi = std::sin(phi_vec);
    // 'mysin:4' sin_calls = sin_calls + 1;
    sin_calls++;
    //
    // 'EvalHelix:42' cphiTCP0    = CP0 * cphi;
    // 'EvalHelix:43' sphiTCP0    = CP0 * sphi;
    // 'EvalHelix:44' cphiTEcrCP0 = EcrCP0 * cphi;
    // 'EvalHelix:45' sphiTEcrCP0 = EcrCP0 * sphi;
    // 'EvalHelix:46' Sign        = sign( P0P1'*evec );
    //
    // 'EvalHelix:48' r0D       = bsxfun(@plus, C, cphiTCP0  + sphiTEcrCP0  + ...
    // 'EvalHelix:49'                    pitch/(2*pi)*evec*phi_vec);
    a = CurvStruct_pitch / 6.2831853071795862;
    // 'EvalHelix:50' r1D       = bsxfun(@plus, -theta  *sphiTCP0  + theta  *cphiTEcrCP0, ...
    // 'EvalHelix:51'                    theta * pitch/(2*pi) * evec);
    b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
    // 'EvalHelix:52' r2D       = -theta^2*cphiTCP0  - theta^2*sphiTEcrCP0;
    a_tmp = CurvStruct_theta * CurvStruct_theta;
    // 'EvalHelix:53' r3D       =  theta^3*sphiTCP0  - theta^3*cphiTEcrCP0;
    b_a_tmp = std::pow(CurvStruct_theta, 3.0);
    r = _mm_loadu_pd(&CP0[0]);
    r1 = _mm_set1_pd(cphi);
    r2 = _mm_mul_pd(r, r1);
    r3 = _mm_set1_pd(sphi);
    r4 = _mm_mul_pd(r, r3);
    r5 = _mm_loadu_pd(&EcrCP0[0]);
    r6 = _mm_mul_pd(r5, r1);
    r7 = _mm_mul_pd(r5, r3);
    r8 = _mm_loadu_pd((const double *)&CurvStruct_evec[0]);
    _mm_storeu_pd(
        &r0D[0],
        _mm_add_pd(_mm_loadu_pd((const double *)&CurvStruct_CorrectedHelixCenter[0]),
                   _mm_add_pd(_mm_add_pd(r2, r7),
                              _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a), r8), _mm_set1_pd(phi_vec)))));
    _mm_storeu_pd(&r1D[0], _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(-CurvStruct_theta), r4),
                                                 _mm_mul_pd(_mm_set1_pd(CurvStruct_theta), r6)),
                                      _mm_mul_pd(_mm_set1_pd(b_a), r8)));
    _mm_storeu_pd(&r2D[0], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(-a_tmp), r2),
                                      _mm_mul_pd(_mm_set1_pd(a_tmp), r7)));
    r9 = _mm_set1_pd(b_a_tmp);
    _mm_storeu_pd(&r3D[0], _mm_sub_pd(_mm_mul_pd(r9, r4), _mm_mul_pd(r9, r6)));
    d = CP0[2] * cphi;
    d1 = CP0[2] * sphi;
    d2 = EcrCP0[2] * cphi;
    d3 = EcrCP0[2] * sphi;
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
