//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
//

// Include Files
#include "EvalCurvStruct.h"
#include "EvalBSpline.h"
#include "EvalHelix.h"
#include "EvalLine.h"
#include "EvalTransP5.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>
#include <stdio.h>

// Function Definitions
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const FeedoptContext *ctx
//                const CurvStruct *b_CurvStruct
//                ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
namespace ocn {
void EvalCurvStruct(const FeedoptContext *ctx, const CurvStruct *b_CurvStruct,
                    ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                    ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                    ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<bool, 2U> x;
    double b_c;
    double c;
    int b_k;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i6;
    int i_loop_ub;
    int j_loop_ub;
    int k;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    char message[30];
    bool b_y;
    bool exitg1;
    bool y;
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    x.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        x[i] = (u_vec[i] - 1.0 > 2.2204460492503131E-15);
    }
    y = false;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(1) - 1)) {
        if (x[k]) {
            y = true;
            exitg1 = true;
        } else {
            k++;
        }
    }
    if (y) {
        int end;
        printf("EvalCurvStruct: u_vec > 1\n");
        fflush(stdout);
        end = u_vec.size(1);
        for (int b_i{0}; b_i < end; b_i++) {
            if (u_vec[b_i] > 1.0) {
                u_vec[b_i] = 1.0;
            }
        }
    }
    x.set_size(1, u_vec.size(1));
    b_loop_ub = u_vec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        x[i1] = (u_vec[i1] < 0.0);
    }
    b_y = false;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k <= x.size(1) - 1)) {
        if (x[b_k]) {
            b_y = true;
            exitg1 = true;
        } else {
            b_k++;
        }
    }
    if (b_y) {
        int b_end;
        printf("EvalCurvStruct: u_vec < 0\n");
        fflush(stdout);
        b_end = u_vec.size(1);
        for (int c_i{0}; c_i < b_end; c_i++) {
            if (u_vec[c_i] < 0.0) {
                u_vec[c_i] = 0.0;
            }
        }
    }
    //
    r0D.set_size(3, u_vec.size(1));
    c_loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        r0D[3 * i2] = 0.0;
        r0D[3 * i2 + 1] = 0.0;
        r0D[3 * i2 + 2] = 0.0;
    }
    r1D.set_size(3, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        r1D[3 * i3] = 0.0;
        r1D[3 * i3 + 1] = 0.0;
        r1D[3 * i3 + 2] = 0.0;
    }
    r2D.set_size(3, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        r2D[3 * i4] = 0.0;
        r2D[3 * i4 + 1] = 0.0;
        r2D[3 * i4 + 2] = 0.0;
    }
    r3D.set_size(3, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    for (int i5{0}; i5 < f_loop_ub; i5++) {
        r3D[3 * i5] = 0.0;
        r3D[3 * i5 + 1] = 0.0;
        r3D[3 * i5 + 2] = 0.0;
    }
    u_vec_tilda.set_size(1, u_vec.size(1));
    g_loop_ub = u_vec.size(1);
    scalarLB = (u_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i6 = 0; i6 <= vectorUB; i6 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&u_vec[i6]);
        _mm_storeu_pd(&u_vec_tilda[i6],
                      _mm_add_pd(_mm_mul_pd(_mm_set1_pd(b_CurvStruct->a_param), r),
                                 _mm_set1_pd(b_CurvStruct->b_param)));
    }
    for (i6 = scalarLB; i6 < g_loop_ub; i6++) {
        u_vec_tilda[i6] = b_CurvStruct->a_param * u_vec[i6] + b_CurvStruct->b_param;
    }
    switch (b_CurvStruct->Type) {
    case CurveType_Line:
        //  line (G01)
        EvalLine(b_CurvStruct->P0, b_CurvStruct->P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        //  arc of circle / helix (G02, G03)
        EvalHelix(b_CurvStruct->P0, b_CurvStruct->CorrectedHelixCenter, b_CurvStruct->evec,
                  b_CurvStruct->theta, b_CurvStruct->pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        //  polynomial transition
        EvalTransP5(b_CurvStruct->CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        //  BSpline
        EvalBSpline(&ctx->q_splines, b_CurvStruct->sp_index, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        for (int i7{0}; i7 < 30; i7++) {
            message[i7] = cv[i7];
        }
        c_assert_(&message[0]);
        break;
    }
    r1D.set_size(3, r1D.size(1));
    h_loop_ub = r1D.size(1);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        __m128d r1;
        r1 = _mm_loadu_pd(&r1D[3 * i8]);
        _mm_storeu_pd(&r1D[3 * i8], _mm_mul_pd(_mm_set1_pd(b_CurvStruct->a_param), r1));
        r1D[3 * i8 + 2] = b_CurvStruct->a_param * r1D[3 * i8 + 2];
    }
    c = b_CurvStruct->a_param * b_CurvStruct->a_param;
    r2D.set_size(3, r2D.size(1));
    i_loop_ub = r2D.size(1);
    for (int i9{0}; i9 < i_loop_ub; i9++) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r2D[3 * i9]);
        _mm_storeu_pd(&r2D[3 * i9], _mm_mul_pd(_mm_set1_pd(c), r2));
        r2D[3 * i9 + 2] = c * r2D[3 * i9 + 2];
    }
    b_c = std::pow(b_CurvStruct->a_param, 3.0);
    r3D.set_size(3, r3D.size(1));
    j_loop_ub = r3D.size(1);
    for (int i10{0}; i10 < j_loop_ub; i10++) {
        __m128d r3;
        r3 = _mm_loadu_pd(&r3D[3 * i10]);
        _mm_storeu_pd(&r3D[3 * i10], _mm_mul_pd(_mm_set1_pd(b_c), r3));
        r3D[3 * i10 + 2] = b_c * r3D[3 * i10 + 2];
    }
}

//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[10][3]
//                double r1D[10][3]
//                double r2D[10][3]
//                double r3D[10][3]
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[10][3], double r1D[10][3], double r2D[10][3], double r3D[10][3])
{
    double u_vec_tilda[10];
    double b_c;
    double c;
    char message[30];
    //
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
        u_vec_tilda[i] =
            CurvStruct_a_param * (0.1111111111111111 * static_cast<double>(i)) + CurvStruct_b_param;
    }
    switch (CurvStruct_Type) {
    case CurveType_Line:
        //  line (G01)
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        //  arc of circle / helix (G02, G03)
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        //  polynomial transition
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        //  BSpline
        EvalBSpline(ctx_q_splines, CurvStruct_sp_index, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        for (int i1{0}; i1 < 30; i1++) {
            message[i1] = cv[i1];
        }
        c_assert_(&message[0]);
        break;
    }
    c = CurvStruct_a_param * CurvStruct_a_param;
    b_c = std::pow(CurvStruct_a_param, 3.0);
    for (int i2{0}; i2 < 10; i2++) {
        __m128d r;
        __m128d r1;
        __m128d r2;
        r = _mm_loadu_pd(&r1D[i2][0]);
        _mm_storeu_pd(&r1D[i2][0], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r));
        r1 = _mm_loadu_pd(&r2D[i2][0]);
        _mm_storeu_pd(&r2D[i2][0], _mm_mul_pd(_mm_set1_pd(c), r1));
        r2 = _mm_loadu_pd(&r3D[i2][0]);
        _mm_storeu_pd(&r3D[i2][0], _mm_mul_pd(_mm_set1_pd(b_c), r2));
        r1D[i2][2] *= CurvStruct_a_param;
        r2D[i2][2] *= c;
        r3D[i2][2] *= b_c;
    }
}

//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
//                double r1D[3]
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3])
{
    __m128d r;
    double r2D[3];
    double r3D[3];
    char message[30];
    //
    r0D[0] = 0.0;
    r1D[0] = 0.0;
    r0D[1] = 0.0;
    r1D[1] = 0.0;
    r0D[2] = 0.0;
    r1D[2] = 0.0;
    switch (CurvStruct_Type) {
    case CurveType_Line:
        //  line (G01)
        EvalLine(CurvStruct_P0, CurvStruct_P1, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        //  arc of circle / helix (G02, G03)
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        //  polynomial transition
        EvalTransP5(CurvStruct_CoeffP5, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        //  BSpline
        EvalBSpline(ctx_q_splines, CurvStruct_sp_index, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    default:
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        break;
    }
    r = _mm_loadu_pd(&r1D[0]);
    _mm_storeu_pd(&r1D[0], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r));
    r1D[2] *= CurvStruct_a_param;
}

//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_b_param
//                double r0D[3]
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_b_param, double r0D[3])
{
    double r1D[3];
    double r2D[3];
    double r3D[3];
    char message[30];
    //
    r0D[0] = 0.0;
    r0D[1] = 0.0;
    r0D[2] = 0.0;
    switch (CurvStruct_Type) {
    case CurveType_Line:
        //  line (G01)
        EvalLine(CurvStruct_P0, CurvStruct_P1, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        //  arc of circle / helix (G02, G03)
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        //  polynomial transition
        EvalTransP5(CurvStruct_CoeffP5, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        //  BSpline
        EvalBSpline(ctx_q_splines, CurvStruct_sp_index, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    default:
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        break;
    }
}

//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3])
{
    double r1D[3];
    double r2D[3];
    double r3D[3];
    double u_vec_tilda;
    char message[30];
    //
    r0D[0] = 0.0;
    r0D[1] = 0.0;
    r0D[2] = 0.0;
    u_vec_tilda = CurvStruct_a_param + CurvStruct_b_param;
    switch (CurvStruct_Type) {
    case CurveType_Line:
        //  line (G01)
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        //  arc of circle / helix (G02, G03)
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        //  polynomial transition
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        //  BSpline
        EvalBSpline(ctx_q_splines, CurvStruct_sp_index, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        break;
    }
}

//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
//                double r3D[3]
// Return Type  : void
//
void b_EvalCurvStruct(CurveType CurvStruct_Type, const double CurvStruct_P0[3],
                      const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3], double r2D[3], double r3D[3])
{
    __m128d r;
    __m128d r1;
    __m128d r2;
    double b_c;
    double c;
    //
    if (CurvStruct_Type == CurveType_Line) {
        //  line (G01)
        EvalLine(CurvStruct_P0, CurvStruct_P1, CurvStruct_b_param, r0D, r1D, r2D, r3D);
    } else {
        //  arc of circle / helix (G02, G03)
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
    }
    c = CurvStruct_a_param * CurvStruct_a_param;
    b_c = std::pow(CurvStruct_a_param, 3.0);
    r = _mm_loadu_pd(&r1D[0]);
    _mm_storeu_pd(&r1D[0], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r));
    r1 = _mm_loadu_pd(&r2D[0]);
    _mm_storeu_pd(&r2D[0], _mm_mul_pd(_mm_set1_pd(c), r1));
    r2 = _mm_loadu_pd(&r3D[0]);
    _mm_storeu_pd(&r3D[0], _mm_mul_pd(_mm_set1_pd(b_c), r2));
    r1D[2] *= CurvStruct_a_param;
    r2D[2] *= c;
    r3D[2] *= b_c;
}

//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                      ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D)
{
    ::coder::array<double, 2U> r3D;
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<bool, 2U> x;
    double c;
    int b_k;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i5;
    int k;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    char message[30];
    bool b_y;
    bool exitg1;
    bool y;
    x.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        x[i] = (u_vec[i] - 1.0 > 2.2204460492503131E-15);
    }
    y = false;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(1) - 1)) {
        if (x[k]) {
            y = true;
            exitg1 = true;
        } else {
            k++;
        }
    }
    if (y) {
        int end;
        printf("EvalCurvStruct: u_vec > 1\n");
        fflush(stdout);
        end = u_vec.size(1);
        for (int b_i{0}; b_i < end; b_i++) {
            if (u_vec[b_i] > 1.0) {
                u_vec[b_i] = 1.0;
            }
        }
    }
    x.set_size(1, u_vec.size(1));
    b_loop_ub = u_vec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        x[i1] = (u_vec[i1] < 0.0);
    }
    b_y = false;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k <= x.size(1) - 1)) {
        if (x[b_k]) {
            b_y = true;
            exitg1 = true;
        } else {
            b_k++;
        }
    }
    if (b_y) {
        int b_end;
        printf("EvalCurvStruct: u_vec < 0\n");
        fflush(stdout);
        b_end = u_vec.size(1);
        for (int c_i{0}; c_i < b_end; c_i++) {
            if (u_vec[c_i] < 0.0) {
                u_vec[c_i] = 0.0;
            }
        }
    }
    //
    r0D.set_size(3, u_vec.size(1));
    c_loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        r0D[3 * i2] = 0.0;
        r0D[3 * i2 + 1] = 0.0;
        r0D[3 * i2 + 2] = 0.0;
    }
    r1D.set_size(3, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        r1D[3 * i3] = 0.0;
        r1D[3 * i3 + 1] = 0.0;
        r1D[3 * i3 + 2] = 0.0;
    }
    r2D.set_size(3, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        r2D[3 * i4] = 0.0;
        r2D[3 * i4 + 1] = 0.0;
        r2D[3 * i4 + 2] = 0.0;
    }
    u_vec_tilda.set_size(1, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    scalarLB = (u_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i5 = 0; i5 <= vectorUB; i5 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&u_vec[i5]);
        _mm_storeu_pd(&u_vec_tilda[i5], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r),
                                                   _mm_set1_pd(CurvStruct_b_param)));
    }
    for (i5 = scalarLB; i5 < f_loop_ub; i5++) {
        u_vec_tilda[i5] = CurvStruct_a_param * u_vec[i5] + CurvStruct_b_param;
    }
    switch (CurvStruct_Type) {
    case CurveType_Line:
        //  line (G01)
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        //  arc of circle / helix (G02, G03)
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        //  polynomial transition
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        //  BSpline
        EvalBSpline(ctx_q_splines, CurvStruct_sp_index, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        for (int i6{0}; i6 < 30; i6++) {
            message[i6] = cv[i6];
        }
        c_assert_(&message[0]);
        break;
    }
    r1D.set_size(3, r1D.size(1));
    g_loop_ub = r1D.size(1);
    for (int i7{0}; i7 < g_loop_ub; i7++) {
        __m128d r1;
        r1 = _mm_loadu_pd(&r1D[3 * i7]);
        _mm_storeu_pd(&r1D[3 * i7], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r1));
        r1D[3 * i7 + 2] = CurvStruct_a_param * r1D[3 * i7 + 2];
    }
    c = CurvStruct_a_param * CurvStruct_a_param;
    r2D.set_size(3, r2D.size(1));
    h_loop_ub = r2D.size(1);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r2D[3 * i8]);
        _mm_storeu_pd(&r2D[3 * i8], _mm_mul_pd(_mm_set1_pd(c), r2));
        r2D[3 * i8 + 2] = c * r2D[3 * i8 + 2];
    }
}

//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                      ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                      ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<bool, 2U> x;
    double b_c;
    double c;
    int b_k;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i6;
    int i_loop_ub;
    int j_loop_ub;
    int k;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    char message[30];
    bool b_y;
    bool exitg1;
    bool y;
    x.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        x[i] = (u_vec[i] - 1.0 > 2.2204460492503131E-15);
    }
    y = false;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(1) - 1)) {
        if (x[k]) {
            y = true;
            exitg1 = true;
        } else {
            k++;
        }
    }
    if (y) {
        int end;
        printf("EvalCurvStruct: u_vec > 1\n");
        fflush(stdout);
        end = u_vec.size(1);
        for (int b_i{0}; b_i < end; b_i++) {
            if (u_vec[b_i] > 1.0) {
                u_vec[b_i] = 1.0;
            }
        }
    }
    x.set_size(1, u_vec.size(1));
    b_loop_ub = u_vec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        x[i1] = (u_vec[i1] < 0.0);
    }
    b_y = false;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k <= x.size(1) - 1)) {
        if (x[b_k]) {
            b_y = true;
            exitg1 = true;
        } else {
            b_k++;
        }
    }
    if (b_y) {
        int b_end;
        printf("EvalCurvStruct: u_vec < 0\n");
        fflush(stdout);
        b_end = u_vec.size(1);
        for (int c_i{0}; c_i < b_end; c_i++) {
            if (u_vec[c_i] < 0.0) {
                u_vec[c_i] = 0.0;
            }
        }
    }
    //
    r0D.set_size(3, u_vec.size(1));
    c_loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        r0D[3 * i2] = 0.0;
        r0D[3 * i2 + 1] = 0.0;
        r0D[3 * i2 + 2] = 0.0;
    }
    r1D.set_size(3, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        r1D[3 * i3] = 0.0;
        r1D[3 * i3 + 1] = 0.0;
        r1D[3 * i3 + 2] = 0.0;
    }
    r2D.set_size(3, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        r2D[3 * i4] = 0.0;
        r2D[3 * i4 + 1] = 0.0;
        r2D[3 * i4 + 2] = 0.0;
    }
    r3D.set_size(3, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    for (int i5{0}; i5 < f_loop_ub; i5++) {
        r3D[3 * i5] = 0.0;
        r3D[3 * i5 + 1] = 0.0;
        r3D[3 * i5 + 2] = 0.0;
    }
    u_vec_tilda.set_size(1, u_vec.size(1));
    g_loop_ub = u_vec.size(1);
    scalarLB = (u_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i6 = 0; i6 <= vectorUB; i6 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&u_vec[i6]);
        _mm_storeu_pd(&u_vec_tilda[i6], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r),
                                                   _mm_set1_pd(CurvStruct_b_param)));
    }
    for (i6 = scalarLB; i6 < g_loop_ub; i6++) {
        u_vec_tilda[i6] = CurvStruct_a_param * u_vec[i6] + CurvStruct_b_param;
    }
    switch (CurvStruct_Type) {
    case CurveType_Line:
        //  line (G01)
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        //  arc of circle / helix (G02, G03)
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        //  polynomial transition
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        //  BSpline
        EvalBSpline(ctx_q_splines, CurvStruct_sp_index, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        for (int i7{0}; i7 < 30; i7++) {
            message[i7] = cv[i7];
        }
        c_assert_(&message[0]);
        break;
    }
    r1D.set_size(3, r1D.size(1));
    h_loop_ub = r1D.size(1);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        __m128d r1;
        r1 = _mm_loadu_pd(&r1D[3 * i8]);
        _mm_storeu_pd(&r1D[3 * i8], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r1));
        r1D[3 * i8 + 2] = CurvStruct_a_param * r1D[3 * i8 + 2];
    }
    c = CurvStruct_a_param * CurvStruct_a_param;
    r2D.set_size(3, r2D.size(1));
    i_loop_ub = r2D.size(1);
    for (int i9{0}; i9 < i_loop_ub; i9++) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r2D[3 * i9]);
        _mm_storeu_pd(&r2D[3 * i9], _mm_mul_pd(_mm_set1_pd(c), r2));
        r2D[3 * i9 + 2] = c * r2D[3 * i9 + 2];
    }
    b_c = std::pow(CurvStruct_a_param, 3.0);
    r3D.set_size(3, r3D.size(1));
    j_loop_ub = r3D.size(1);
    for (int i10{0}; i10 < j_loop_ub; i10++) {
        __m128d r3;
        r3 = _mm_loadu_pd(&r3D[3 * i10]);
        _mm_storeu_pd(&r3D[3 * i10], _mm_mul_pd(_mm_set1_pd(b_c), r3));
        r3D[3 * i10 + 2] = b_c * r3D[3 * i10 + 2];
    }
}

//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
// Return Type  : void
//
void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3], double r2D[3])
{
    __m128d r;
    __m128d r1;
    double r3D[3];
    double c;
    double u_vec_tilda;
    char message[30];
    //
    r0D[0] = 0.0;
    r1D[0] = 0.0;
    r2D[0] = 0.0;
    r0D[1] = 0.0;
    r1D[1] = 0.0;
    r2D[1] = 0.0;
    r0D[2] = 0.0;
    r1D[2] = 0.0;
    r2D[2] = 0.0;
    u_vec_tilda = CurvStruct_a_param + CurvStruct_b_param;
    switch (CurvStruct_Type) {
    case CurveType_Line:
        //  line (G01)
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        //  arc of circle / helix (G02, G03)
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        //  polynomial transition
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        //  BSpline
        EvalBSpline(ctx_q_splines, CurvStruct_sp_index, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        break;
    }
    c = CurvStruct_a_param * CurvStruct_a_param;
    r = _mm_loadu_pd(&r1D[0]);
    _mm_storeu_pd(&r1D[0], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r));
    r1 = _mm_loadu_pd(&r2D[0]);
    _mm_storeu_pd(&r2D[0], _mm_mul_pd(_mm_set1_pd(c), r1));
    r1D[2] *= CurvStruct_a_param;
    r2D[2] *= c;
}

//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
// Return Type  : void
//
void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3], double r2D[3])
{
    __m128d r;
    __m128d r1;
    double r3D[3];
    double c;
    char message[30];
    //
    r0D[0] = 0.0;
    r1D[0] = 0.0;
    r2D[0] = 0.0;
    r0D[1] = 0.0;
    r1D[1] = 0.0;
    r2D[1] = 0.0;
    r0D[2] = 0.0;
    r1D[2] = 0.0;
    r2D[2] = 0.0;
    switch (CurvStruct_Type) {
    case CurveType_Line:
        //  line (G01)
        EvalLine(CurvStruct_P0, CurvStruct_P1, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        //  arc of circle / helix (G02, G03)
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        //  polynomial transition
        EvalTransP5(CurvStruct_CoeffP5, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        //  BSpline
        EvalBSpline(ctx_q_splines, CurvStruct_sp_index, CurvStruct_b_param, r0D, r1D, r2D, r3D);
        break;
    default:
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        break;
    }
    c = CurvStruct_a_param * CurvStruct_a_param;
    r = _mm_loadu_pd(&r1D[0]);
    _mm_storeu_pd(&r1D[0], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r));
    r1 = _mm_loadu_pd(&r2D[0]);
    _mm_storeu_pd(&r2D[0], _mm_mul_pd(_mm_set1_pd(c), r1));
    r1D[2] *= CurvStruct_a_param;
    r2D[2] *= c;
}

//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
//                double r3D[3]
// Return Type  : void
//
void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3], double r2D[3], double r3D[3])
{
    __m128d r;
    __m128d r1;
    __m128d r2;
    double b_c;
    double c;
    double u_vec_tilda;
    char message[30];
    //
    r0D[0] = 0.0;
    r1D[0] = 0.0;
    r2D[0] = 0.0;
    r3D[0] = 0.0;
    r0D[1] = 0.0;
    r1D[1] = 0.0;
    r2D[1] = 0.0;
    r3D[1] = 0.0;
    r0D[2] = 0.0;
    r1D[2] = 0.0;
    r2D[2] = 0.0;
    r3D[2] = 0.0;
    u_vec_tilda = CurvStruct_a_param + CurvStruct_b_param;
    switch (CurvStruct_Type) {
    case CurveType_Line:
        //  line (G01)
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        //  arc of circle / helix (G02, G03)
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        //  polynomial transition
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        //  BSpline
        EvalBSpline(ctx_q_splines, CurvStruct_sp_index, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        break;
    }
    c = CurvStruct_a_param * CurvStruct_a_param;
    b_c = std::pow(CurvStruct_a_param, 3.0);
    r = _mm_loadu_pd(&r1D[0]);
    _mm_storeu_pd(&r1D[0], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r));
    r1 = _mm_loadu_pd(&r2D[0]);
    _mm_storeu_pd(&r2D[0], _mm_mul_pd(_mm_set1_pd(c), r1));
    r2 = _mm_loadu_pd(&r3D[0]);
    _mm_storeu_pd(&r3D[0], _mm_mul_pd(_mm_set1_pd(b_c), r2));
    r1D[2] *= CurvStruct_a_param;
    r2D[2] *= c;
    r3D[2] *= b_c;
}

//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                int CurvStruct_sp_index
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                double r0D[3]
//                double r1D[3]
// Return Type  : void
//
void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type,
                      const double CurvStruct_P0[3], const double CurvStruct_P1[3],
                      const double CurvStruct_CorrectedHelixCenter[3],
                      const double CurvStruct_evec[3], double CurvStruct_theta,
                      double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                      int CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param,
                      double r0D[3], double r1D[3])
{
    __m128d r;
    double r2D[3];
    double r3D[3];
    double u_vec_tilda;
    char message[30];
    //
    r0D[0] = 0.0;
    r1D[0] = 0.0;
    r0D[1] = 0.0;
    r1D[1] = 0.0;
    r0D[2] = 0.0;
    r1D[2] = 0.0;
    u_vec_tilda = CurvStruct_a_param + CurvStruct_b_param;
    switch (CurvStruct_Type) {
    case CurveType_Line:
        //  line (G01)
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        //  arc of circle / helix (G02, G03)
        EvalHelix(CurvStruct_P0, CurvStruct_CorrectedHelixCenter, CurvStruct_evec, CurvStruct_theta,
                  CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        //  polynomial transition
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        //  BSpline
        EvalBSpline(ctx_q_splines, CurvStruct_sp_index, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        break;
    }
    r = _mm_loadu_pd(&r1D[0]);
    _mm_storeu_pd(&r1D[0], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r));
    r1D[2] *= CurvStruct_a_param;
}

} // namespace ocn

//
// File trailer for EvalCurvStruct.cpp
//
// [EOF]
//
