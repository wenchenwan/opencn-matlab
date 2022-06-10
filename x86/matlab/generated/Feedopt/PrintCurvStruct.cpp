//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PrintCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

// Include Files
#include "PrintCurvStruct.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "combineVectorElements.h"
#include "constJerkU.h"
#include "fprintf.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "string1.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <emmintrin.h>
#include <stdio.h>

// Function Definitions
//
// function PrintCurvStruct(ctx, S)
//
// Arguments    : const queue_coder *ctx_q_spline
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const int ctx_cfg_indCart_data[]
//                int ctx_cfg_indCart_size
//                const int ctx_cfg_indRot_data[]
//                int ctx_cfg_indRot_size
//                const int ctx_cfg_indTot_data[]
//                int ctx_cfg_indTot_size
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                CurveType S_Info_Type
//                ZSpdMode S_Info_zspdmode
//                double S_Info_FeedRate
//                const double S_R0[6]
//                const double S_R1[6]
//                const double S_CorrectedHelixCenter[3]
//                const double S_evec[3]
//                double S_theta
//                double S_pitch
//                const ::coder::array<double, 2U> &S_CoeffP5
//                unsigned int S_sp_index
//                bool S_UseConstJerk
//                double S_ConstJerk
//                double S_a_param
//                double S_b_param
// Return Type  : void
//
namespace ocn {
void PrintCurvStruct(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                     int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                     const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                     const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                     const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
                     CurveType S_Info_Type, ZSpdMode S_Info_zspdmode, double S_Info_FeedRate,
                     const double S_R0[6], const double S_R1[6],
                     const double S_CorrectedHelixCenter[3], const double S_evec[3], double S_theta,
                     double S_pitch, const ::coder::array<double, 2U> &S_CoeffP5,
                     unsigned int S_sp_index, bool S_UseConstJerk, double S_ConstJerk,
                     double S_a_param, double S_b_param)
{
    static const char b_cv[9]{'<', 'U', 'N', 'K', 'N', 'O', 'W', 'N', '>'};
    static const char b_cv2[7]{'T', 'r', 'a', 'n', 's', 'P', '5'};
    static const char cv3[6]{'S', 'p', 'l', 'i', 'n', 'e'};
    static const char b_cv1[5]{'H', 'e', 'l', 'i', 'x'};
    coder::rtString formatSpec;
    ::coder::array<double, 1U> P0;
    ::coder::array<double, 1U> P1;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    double u;
    double ud;
    double udd;
    double uddd;
    double validatedHoleFilling_f2;
    int varargin_1_size_idx_1;
    char b_varargin_1_data[10];
    char varargin_2_data[10];
    char varargin_1_data[9];
    // 'PrintCurvStruct:3' fprintf( '--------- CURVE STRUCT ---------\n' );
    printf("--------- CURVE STRUCT ---------\n");
    fflush(stdout);
    // 'PrintCurvStruct:4' fprintf( '%10s: %s\n', 'Type', CurveTypeToStr( S.Info.Type ) );
    // 'PrintCurvStruct:62' switch Type
    switch (S_Info_Type) {
    case CurveType_Line:
        // 'PrintCurvStruct:63' case CurveType.Line
        // 'PrintCurvStruct:64' str = 'Line';
        varargin_1_size_idx_1 = 4;
        varargin_1_data[0] = 'L';
        varargin_1_data[1] = 'i';
        varargin_1_data[2] = 'n';
        varargin_1_data[3] = 'e';
        break;
    case CurveType_Helix:
        // 'PrintCurvStruct:65' case CurveType.Helix
        // 'PrintCurvStruct:66' str = 'Helix';
        varargin_1_size_idx_1 = 5;
        for (int i1{0}; i1 < 5; i1++) {
            varargin_1_data[i1] = b_cv1[i1];
        }
        break;
    case CurveType_TransP5:
        // 'PrintCurvStruct:67' case CurveType.TransP5
        // 'PrintCurvStruct:68' str = 'TransP5';
        varargin_1_size_idx_1 = 7;
        for (int i2{0}; i2 < 7; i2++) {
            varargin_1_data[i2] = b_cv2[i2];
        }
        break;
    case CurveType_Spline:
        // 'PrintCurvStruct:69' case CurveType.Spline
        // 'PrintCurvStruct:70' str = 'Spline';
        varargin_1_size_idx_1 = 6;
        for (int i3{0}; i3 < 6; i3++) {
            varargin_1_data[i3] = cv3[i3];
        }
        break;
    default:
        // 'PrintCurvStruct:71' otherwise
        // 'PrintCurvStruct:72' str = '<UNKNOWN>';
        varargin_1_size_idx_1 = 9;
        for (int i{0}; i < 9; i++) {
            varargin_1_data[i] = b_cv[i];
        }
        break;
    }
    if (0 <= varargin_1_size_idx_1 - 1) {
        std::copy(&varargin_1_data[0], &varargin_1_data[varargin_1_size_idx_1],
                  &varargin_2_data[0]);
    }
    varargin_2_data[varargin_1_size_idx_1] = '\x00';
    printf("%10s: %s\n", "Type", &varargin_2_data[0]);
    fflush(stdout);
    // 'PrintCurvStruct:6' switch S.Info.Type
    switch (S_Info_Type) {
    case CurveType_Line:
        // 'PrintCurvStruct:7' case CurveType.Line
        break;
    case CurveType_Helix:
        // 'PrintCurvStruct:9' case CurveType.Helix
        // 'PrintCurvStruct:10' fprintf( '%10s: [%.3f %.3f %.3f]\n', 'evec', S.evec(1), S.evec(2),
        // S.evec(3) )
        printf("%10s: [%.3f %.3f %.3f]\n", "evec", S_evec[0], S_evec[1], S_evec[2]);
        fflush(stdout);
        // 'PrintCurvStruct:11' fprintf( '%10s: %.3f\n', 'theta', S.theta );
        printf("%10s: %.3f\n", "theta", S_theta);
        fflush(stdout);
        // 'PrintCurvStruct:12' fprintf( '%10s: %.3f\n', 'pitch', S.pitch );
        printf("%10s: %.3f\n", "pitch", S_pitch);
        fflush(stdout);
        break;
    case CurveType_TransP5: {
        int i4;
        // 'PrintCurvStruct:13' case CurveType.TransP5
        // 'PrintCurvStruct:14' fprintf( ' CoeffP5: \n' );
        printf(" CoeffP5: \n");
        fflush(stdout);
        // 'PrintCurvStruct:15' fprintf( '| ' )
        printf("| ");
        fflush(stdout);
        // 'PrintCurvStruct:16' [ NLine, NRow ] = size( S.CoeffP5 );
        // 'PrintCurvStruct:17' for j = 1 : NLine
        i4 = S_CoeffP5.size(0);
        for (int j{0}; j < i4; j++) {
            // 'PrintCurvStruct:18' for k = 1 : NRow
            for (int k{0}; k < 6; k++) {
                // 'PrintCurvStruct:19' fprintf( '%.3f ', S.CoeffP5( j, k ) )
                printf("%.3f ", S_CoeffP5[j + S_CoeffP5.size(0) * k]);
                fflush(stdout);
            }
            // 'PrintCurvStruct:21' fprintf( '| ' )
            printf("| ");
            fflush(stdout);
        }
        // 'PrintCurvStruct:23' fprintf( '\n' )
        printf("\n");
        fflush(stdout);
        // 'PrintCurvStruct:24' fprintf( 'FeedRate: %.2f\n', S.Info.FeedRate )
        printf("FeedRate: %.2f\n", S_Info_FeedRate);
        fflush(stdout);
    } break;
    case CurveType_Spline:
        // 'PrintCurvStruct:25' case CurveType.Spline
        break;
    default:
        // 'PrintCurvStruct:26' otherwise
        // 'PrintCurvStruct:27' fprintf( '!!! Type = %d, UNKNOWN !!!\n', int32( S.Info.Type ) )
        printf("!!! Type = %d, UNKNOWN !!!\n", static_cast<int>(S_Info_Type));
        fflush(stdout);
        break;
    }
    // 'PrintCurvStruct:29' P0 = EvalCurvStruct( ctx, S, 0 );
    b_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                     ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                     ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size, S_Info_Type,
                     S_R0, S_R1, S_CorrectedHelixCenter, S_evec, S_theta, S_pitch, S_CoeffP5,
                     S_sp_index, S_a_param, S_b_param, P0);
    // 'PrintCurvStruct:30' P1 = EvalCurvStruct( ctx, S, 1 );
    c_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                     ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                     ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size, S_Info_Type,
                     S_R0, S_R1, S_CorrectedHelixCenter, S_evec, S_theta, S_pitch, S_CoeffP5,
                     S_sp_index, S_a_param, S_b_param, P1);
    // 'PrintCurvStruct:31' fprintf( '%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n',...
    // 'PrintCurvStruct:32'     'P', P0(1), P0(2), P0(3), P1(1), P1(2), P1(3) )
    printf("%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n", "P", P0[0], P0[1], P0[2], P1[0], P1[1],
           P1[2]);
    fflush(stdout);
    // 'PrintCurvStruct:33' fprintf( '%10s: %e\n', 'Length', LengthCurv( ctx, S, 0, 1 ) );
    validatedHoleFilling_f2 = LengthCurv(
        ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_indCart_data,
        ctx_cfg_indCart_size, ctx_cfg_indRot_data, ctx_cfg_indRot_size, ctx_cfg_indTot_data,
        ctx_cfg_indTot_size, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, S_Info_Type, S_R0,
        S_R1, S_CorrectedHelixCenter, S_evec, S_theta, S_pitch, S_CoeffP5, S_sp_index, S_a_param,
        S_b_param);
    printf("%10s: %e\n", "Length", validatedHoleFilling_f2);
    fflush(stdout);
    // 'PrintCurvStruct:34' fprintf( 'ZSpdMode: %s\n', PrintZSpdMode( S.Info.zspdmode ) )
    // 'PrintCurvStruct:47' switch m
    switch (S_Info_zspdmode) {
    case ZSpdMode_NN:
        // 'PrintCurvStruct:48' case ZSpdMode.NN
        // 'PrintCurvStruct:49' str = "NN";
        formatSpec.Value.data[0] = 'N';
        formatSpec.Value.data[1] = 'N';
        break;
    case ZSpdMode_ZN:
        // 'PrintCurvStruct:50' case ZSpdMode.ZN
        // 'PrintCurvStruct:51' str = "ZN";
        formatSpec.Value.data[0] = 'Z';
        formatSpec.Value.data[1] = 'N';
        break;
    case ZSpdMode_NZ:
        // 'PrintCurvStruct:52' case ZSpdMode.NZ
        // 'PrintCurvStruct:53' str = "NZ";
        formatSpec.Value.data[0] = 'N';
        formatSpec.Value.data[1] = 'Z';
        break;
    default:
        // 'PrintCurvStruct:54' case ZSpdMode.ZZ
        // 'PrintCurvStruct:55' str = "ZZ";
        formatSpec.Value.data[0] = 'Z';
        formatSpec.Value.data[1] = 'Z';
        break;
    }
    for (int i5{0}; i5 < 2; i5++) {
        b_varargin_1_data[i5] = formatSpec.Value.data[i5];
    }
    b_varargin_1_data[2] = '\x00';
    printf("ZSpdMode: %s\n", &b_varargin_1_data[0]);
    fflush(stdout);
    // 'PrintCurvStruct:35' fprintf( 'FeedRate: %.2f\n', S.Info.FeedRate )
    printf("FeedRate: %.2f\n", S_Info_FeedRate);
    fflush(stdout);
    // 'PrintCurvStruct:36' if S.UseConstJerk
    if (S_UseConstJerk) {
        double b_k;
        double n;
        double y;
        int b_loop_ub;
        int i8;
        int loop_ub;
        bool isEnd;
        // 'PrintCurvStruct:37' isEnd = false;
        isEnd = false;
        // 'PrintCurvStruct:38' if( S.Info.zspdmode == ZSpdMode.NZ )
        if (S_Info_zspdmode == ZSpdMode_NZ) {
            // 'PrintCurvStruct:38' isEnd = true;
            isEnd = true;
        }
        // 'PrintCurvStruct:39' [v_0, at_0] = calcZeroConstraints( ctx, S, isEnd );
        //  calcZeroConstraints : Compute the velocity and acceleration
        //  required for the continuity at zero start.
        //  Inputs :
        //  ctx   : The context
        //  Curv  : The curve
        //  isEnd : (boolean) Is the end of the curve
        //  Outputs :
        //  v_0   : Norm of the velocity
        //  at_0  : Norm of the tangential acceleration
        // 'calcZeroConstraints:12' jps = curv.ConstJerk;
        // 'calcZeroConstraints:14' if( isEnd )
        if (isEnd) {
            // 'calcZeroConstraints:15' k  = 0;
            b_k = 0.0;
        } else {
            // 'calcZeroConstraints:16' else
            // 'calcZeroConstraints:17' k   = ( 6 / jps )^( 1 / 3 );
            b_k = std::pow(6.0 / S_ConstJerk, 0.33333333333333331);
        }
        // 'calcZeroConstraints:20' [ u, ud, udd, uddd ]    = constJerkU( jps, k, isEnd );
        constJerkU(S_ConstJerk, b_k, isEnd, &u, &ud, &udd, &uddd);
        // 'calcZeroConstraints:22' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u );
        b_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                         ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                         ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size, S_Info_Type,
                         S_R0, S_R1, S_CorrectedHelixCenter, S_evec, S_theta, S_pitch, S_CoeffP5,
                         S_sp_index, S_a_param, S_b_param, u, r0D, r1D, r2D, r3D);
        // 'calcZeroConstraints:24' [ ~, V, A, ~ ]          = calcRVAJfromUWithoutCurv( ud, udd,
        // uddd, r0D, ... 'calcZeroConstraints:25'                           r1D, r2D, r3D );
        //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
        //  jerk for a given set of u variable.
        //  Inputs :
        //    ud_vec  : [ 1 x M ] The vector of first derivative of u
        //    udd_vec : [ 1 x M ] The vector of second derivative of ddu
        //    uddd_vec: [ 1 x M ] The vector of third derivative of ddu
        //    r0D     : [ 1 x M ] The vector of r
        //    r1D     : [ 1 x M ] The vector of first derivative of r
        //    r2D     : [ 1 x M ] The vector of second derivative of r
        //    r3D     : [ 1 x M ] The vector of second derivative of r
        //  Outputs :
        //    R   : [ N x M ] pose
        //    V   : [ N x M ] velocity
        //    A   : [ N x M ] acceleration
        //    J   : [ N x M ] jerk
        // 'calcRVAJfromUWithoutCurv:18' R = r0D;
        // 'calcRVAJfromUWithoutCurv:19' V = r1D .* ud_vec;
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        y = std::pow(ud, 2.0);
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec; 'calcZeroConstraints:27' [ vNorm, atNorm ]       = calcNormVNormAT( V, A,
        // r1D );
        //  calcNormVNormAT : Compute the norm of velocity and the norm of tangential
        //  acceleration.
        //  Inputs :
        //  V     : The velovity vector
        //  A     : The acceleration vector
        //  r1D   : The partial derivative of R
        //  Outputs :
        //  vNorm   : Norm of the velocity
        //  atNorm  : Norm of the tangential acceleration
        // 'calcNormVNormAT:12' vNorm   = mysqrt( sum( V.^2, 1 ) );
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'calcNormVNormAT:13' t       = r1D / MyNorm( r1D );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        r.set_size(r1D.size(0));
        loop_ub = r1D.size(0);
        for (int i6{0}; i6 < loop_ub; i6++) {
            double varargin_1;
            varargin_1 = r1D[i6];
            r[i6] = std::pow(varargin_1, 2.0);
        }
        n = std::sqrt(coder::combineVectorElements(r));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'calcNormVNormAT:14' atNorm  = norm( A.*t );
        // 'PrintCurvStruct:40' fprintf( 'ConstJerk: %e\n', S.ConstJerk )
        printf("ConstJerk: %e\n", S_ConstJerk);
        fflush(stdout);
        // 'PrintCurvStruct:41' fprintf( 'v_0      : %f\n', v_0 )
        r.set_size(r1D.size(0));
        b_loop_ub = r1D.size(0);
        for (int i7{0}; i7 < b_loop_ub; i7++) {
            double b_varargin_1;
            b_varargin_1 = r1D[i7] * ud;
            r[i7] = std::pow(b_varargin_1, 2.0);
        }
        printf("v_0      : %f\n", std::sqrt(coder::combineVectorElements(r)));
        fflush(stdout);
        // 'PrintCurvStruct:42' fprintf( 'at_0     : %f\n', at_0 )
        if (r2D.size(0) == 1) {
            i8 = r1D.size(0);
        } else {
            i8 = r2D.size(0);
        }
        if ((r2D.size(0) == r1D.size(0)) && (i8 == r1D.size(0))) {
            int c_loop_ub;
            int i9;
            int scalarLB;
            int vectorUB;
            c_loop_ub = r2D.size(0);
            scalarLB = (r2D.size(0) / 2) << 1;
            vectorUB = scalarLB - 2;
            for (i9 = 0; i9 <= vectorUB; i9 += 2) {
                __m128d r1;
                __m128d r2;
                r1 = _mm_loadu_pd(&r2D[i9]);
                r2 = _mm_loadu_pd(&r1D[i9]);
                _mm_storeu_pd(&r2D[i9], _mm_mul_pd(_mm_add_pd(_mm_mul_pd(r1, _mm_set1_pd(y)),
                                                              _mm_mul_pd(r2, _mm_set1_pd(udd))),
                                                   _mm_div_pd(r2, _mm_set1_pd(n))));
            }
            for (i9 = scalarLB; i9 < c_loop_ub; i9++) {
                r2D[i9] = (r2D[i9] * y + r1D[i9] * udd) * (r1D[i9] / n);
            }
            printf("at_0     : %f\n", coder::b_norm(r2D));
        } else {
            binary_expand_op(r2D, y, r1D, udd, n);
        }
        fflush(stdout);
    }
}

} // namespace ocn

//
// File trailer for PrintCurvStruct.cpp
//
// [EOF]
//
