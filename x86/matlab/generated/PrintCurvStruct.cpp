//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PrintCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 22-Feb-2022 11:10:49
//

// Include Files
#include "PrintCurvStruct.h"
#include "CalcZeroStartConstraints.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "string1.h"
#include <algorithm>
#include <stdio.h>

// Function Definitions
//
// function PrintCurvStruct(ctx, S)
//
// Arguments    : const queue_coder *ctx_q_splines
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *S
// Return Type  : void
//
namespace ocn {
void PrintCurvStruct(const queue_coder *ctx_q_splines, const double ctx_cfg_GaussLegendreX[5],
                     const double ctx_cfg_GaussLegendreW[5], const CurvStruct *S)
{
    static const char b_cv[9]{'<', 'U', 'N', 'K', 'N', 'O', 'W', 'N', '>'};
    static const char b_cv2[7]{'T', 'r', 'a', 'n', 's', 'P', '5'};
    static const char cv3[6]{'S', 'p', 'l', 'i', 'n', 'e'};
    static const char b_cv1[5]{'H', 'e', 'l', 'i', 'x'};
    coder::rtString formatSpec;
    double dv[3][6];
    double P0[3];
    double P1[3];
    double b_validatedHoleFilling_idx_0;
    double validatedHoleFilling_f2;
    double validatedHoleFilling_idx_0;
    int varargin_1_size_idx_1;
    char b_varargin_1_data[10];
    char varargin_2_data[10];
    char varargin_1_data[9];
    // 'PrintCurvStruct:3' fprintf('--------- CURVE STRUCT ---------\n')
    printf("--------- CURVE STRUCT ---------\n");
    fflush(stdout);
    // 'PrintCurvStruct:4' fprintf('%10s: %s\n', 'Type', CurveTypeToStr(S.Type));
    // 'PrintCurvStruct:59' switch Type
    switch (S->Type) {
    case CurveType_Line:
        // 'PrintCurvStruct:60' case CurveType.Line
        // 'PrintCurvStruct:61' str = 'Line';
        varargin_1_size_idx_1 = 4;
        varargin_1_data[0] = 'L';
        varargin_1_data[1] = 'i';
        varargin_1_data[2] = 'n';
        varargin_1_data[3] = 'e';
        break;
    case CurveType_Helix:
        // 'PrintCurvStruct:62' case CurveType.Helix
        // 'PrintCurvStruct:63' str = 'Helix';
        varargin_1_size_idx_1 = 5;
        for (int i1{0}; i1 < 5; i1++) {
            varargin_1_data[i1] = b_cv1[i1];
        }
        break;
    case CurveType_TransP5:
        // 'PrintCurvStruct:64' case CurveType.TransP5
        // 'PrintCurvStruct:65' str = 'TransP5';
        varargin_1_size_idx_1 = 7;
        for (int i2{0}; i2 < 7; i2++) {
            varargin_1_data[i2] = b_cv2[i2];
        }
        break;
    case CurveType_Spline:
        // 'PrintCurvStruct:66' case CurveType.Spline
        // 'PrintCurvStruct:67' str = 'Spline';
        varargin_1_size_idx_1 = 6;
        for (int i3{0}; i3 < 6; i3++) {
            varargin_1_data[i3] = cv3[i3];
        }
        break;
    default:
        // 'PrintCurvStruct:68' otherwise
        // 'PrintCurvStruct:69' str = '<UNKNOWN>';
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
    // 'PrintCurvStruct:6' switch S.Type
    switch (S->Type) {
    case CurveType_Line:
        // 'PrintCurvStruct:7' case CurveType.Line
        break;
    case CurveType_Helix:
        // 'PrintCurvStruct:9' case CurveType.Helix
        // 'PrintCurvStruct:10' fprintf('%10s: [%.3f %.3f %.3f]\n', 'evec', S.evec(1), S.evec(2),
        // S.evec(3))
        printf("%10s: [%.3f %.3f %.3f]\n", "evec", S->evec[0], S->evec[1], S->evec[2]);
        fflush(stdout);
        // 'PrintCurvStruct:11' fprintf('%10s: %.3f\n', 'theta', S.theta);
        printf("%10s: %.3f\n", "theta", S->theta);
        fflush(stdout);
        // 'PrintCurvStruct:12' fprintf('%10s: %.3f\n', 'pitch', S.pitch);
        printf("%10s: %.3f\n", "pitch", S->pitch);
        fflush(stdout);
        break;
    case CurveType_TransP5:
        // 'PrintCurvStruct:13' case CurveType.TransP5
        // 'PrintCurvStruct:14' fprintf(' CoeffP5: \n');
        printf(" CoeffP5: \n");
        fflush(stdout);
        // 'PrintCurvStruct:15' fprintf('| ')
        printf("| ");
        fflush(stdout);
        // 'PrintCurvStruct:16' for CoeffRow = S.CoeffP5'
        for (int i4{0}; i4 < 3; i4++) {
            for (int i5{0}; i5 < 6; i5++) {
                dv[i4][i5] = S->CoeffP5[i5][i4];
            }
        }
        // 'PrintCurvStruct:17' for v = CoeffRow
        // 'PrintCurvStruct:18' fprintf('%.3f ', v(1))
        printf("%.3f ", dv[0][0]);
        fflush(stdout);
        // 'PrintCurvStruct:20' fprintf('| ')
        printf("| ");
        fflush(stdout);
        // 'PrintCurvStruct:17' for v = CoeffRow
        // 'PrintCurvStruct:18' fprintf('%.3f ', v(1))
        printf("%.3f ", dv[1][0]);
        fflush(stdout);
        // 'PrintCurvStruct:20' fprintf('| ')
        printf("| ");
        fflush(stdout);
        // 'PrintCurvStruct:17' for v = CoeffRow
        // 'PrintCurvStruct:18' fprintf('%.3f ', v(1))
        printf("%.3f ", dv[2][0]);
        fflush(stdout);
        // 'PrintCurvStruct:20' fprintf('| ')
        printf("| ");
        fflush(stdout);
        // 'PrintCurvStruct:22' fprintf('\n')
        printf("\n");
        fflush(stdout);
        // 'PrintCurvStruct:23' fprintf('FeedRate: %.2f\n', S.FeedRate)
        printf("FeedRate: %.2f\n", S->FeedRate);
        fflush(stdout);
        break;
    case CurveType_Spline:
        // 'PrintCurvStruct:24' case CurveType.Spline
        break;
    default:
        // 'PrintCurvStruct:25' otherwise
        // 'PrintCurvStruct:26' fprintf('!!! Type = %d, UNKNOWN !!!\n', int32(S.Type))
        printf("!!! Type = %d, UNKNOWN !!!\n", static_cast<int>(S->Type));
        fflush(stdout);
        break;
    }
    // 'PrintCurvStruct:28' P0 = EvalCurvStruct(ctx, S, 0);
    b_EvalCurvStruct(ctx_q_splines, S->Type, S->P0, S->P1, S->CorrectedHelixCenter, S->evec,
                     S->theta, S->pitch, S->CoeffP5, S->sp_index, S->b_param, P0);
    // 'PrintCurvStruct:29' P1 = EvalCurvStruct(ctx, S, 1);
    b_EvalCurvStruct(ctx_q_splines, S->Type, S->P0, S->P1, S->CorrectedHelixCenter, S->evec,
                     S->theta, S->pitch, S->CoeffP5, S->sp_index, S->a_param, S->b_param, P1);
    // 'PrintCurvStruct:30' fprintf('%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n',...
    // 'PrintCurvStruct:31'     'P', P0(1), P0(2), P0(3), P1(1), P1(2), P1(3))
    printf("%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n", "P", P0[0], P0[1], P0[2], P1[0], P1[1],
           P1[2]);
    fflush(stdout);
    // 'PrintCurvStruct:32' fprintf('%10s: %e\n', 'Length', LengthCurv(ctx, S, 0, 1));
    validatedHoleFilling_f2 =
        LengthCurv(ctx_q_splines, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, S);
    printf("%10s: %e\n", "Length", validatedHoleFilling_f2);
    fflush(stdout);
    // 'PrintCurvStruct:33' fprintf('ZSpdMode: %s\n', PrintZSpdMode(S.zspdmode))
    // 'PrintCurvStruct:44' switch m
    switch (S->zspdmode) {
    case ZSpdMode_NN:
        // 'PrintCurvStruct:45' case ZSpdMode.NN
        // 'PrintCurvStruct:46' str = "NN";
        formatSpec.Value.data[0] = 'N';
        formatSpec.Value.data[1] = 'N';
        break;
    case ZSpdMode_ZN:
        // 'PrintCurvStruct:47' case ZSpdMode.ZN
        // 'PrintCurvStruct:48' str = "ZN";
        formatSpec.Value.data[0] = 'Z';
        formatSpec.Value.data[1] = 'N';
        break;
    case ZSpdMode_NZ:
        // 'PrintCurvStruct:49' case ZSpdMode.NZ
        // 'PrintCurvStruct:50' str = "NZ";
        formatSpec.Value.data[0] = 'N';
        formatSpec.Value.data[1] = 'Z';
        break;
    default:
        // 'PrintCurvStruct:51' case ZSpdMode.ZZ
        // 'PrintCurvStruct:52' str = "ZZ";
        formatSpec.Value.data[0] = 'Z';
        formatSpec.Value.data[1] = 'Z';
        break;
    }
    for (int i6{0}; i6 < 2; i6++) {
        b_varargin_1_data[i6] = formatSpec.Value.data[i6];
    }
    b_varargin_1_data[2] = '\x00';
    printf("ZSpdMode: %s\n", &b_varargin_1_data[0]);
    fflush(stdout);
    // 'PrintCurvStruct:34' fprintf('FeedRate: %.2f\n', S.FeedRate)
    printf("FeedRate: %.2f\n", S->FeedRate);
    fflush(stdout);
    // 'PrintCurvStruct:35' if S.UseConstJerk
    if (S->UseConstJerk) {
        // 'PrintCurvStruct:36' [v_0, at_0] = CalcZeroStartConstraints(ctx, S, 1);
        CalcZeroStartConstraints(ctx_q_splines, S->Type, S->P0, S->P1, S->CorrectedHelixCenter,
                                 S->evec, S->theta, S->pitch, S->CoeffP5, S->sp_index,
                                 S->UseConstJerk, S->ConstJerk, S->a_param, S->b_param, 1.0,
                                 &validatedHoleFilling_idx_0, &b_validatedHoleFilling_idx_0);
        // 'PrintCurvStruct:37' fprintf('ConstJerk: %e\n', S.ConstJerk)
        printf("ConstJerk: %e\n", S->ConstJerk);
        fflush(stdout);
        // 'PrintCurvStruct:38' fprintf('v_0      : %f\n', v_0)
        printf("v_0      : %f\n", validatedHoleFilling_idx_0);
        fflush(stdout);
        // 'PrintCurvStruct:39' fprintf('at_0     : %f\n', at_0)
        printf("at_0     : %f\n", b_validatedHoleFilling_idx_0);
        fflush(stdout);
    }
}

} // namespace ocn

//
// File trailer for PrintCurvStruct.cpp
//
// [EOF]
//
