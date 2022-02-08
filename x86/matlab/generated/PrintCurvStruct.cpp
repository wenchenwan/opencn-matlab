//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PrintCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "PrintCurvStruct.h"
#include "CalcZeroStartConstraints.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_internal_types.h"
#include "sinspace_types.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "string1.h"
#include <algorithm>
#include <stdio.h>

// Function Declarations
namespace ocn {
static void CurveTypeToStr(CurveType Type, char str_data[], int str_size[2]);

static void PrintZSpdMode(ZSpdMode m, coder::rtString *str);

} // namespace ocn

// Function Definitions
//
// Arguments    : CurveType Type
//                char str_data[]
//                int str_size[2]
// Return Type  : void
//
namespace ocn {
static void CurveTypeToStr(CurveType Type, char str_data[], int str_size[2])
{
    static const char b_cv[9]{'<', 'U', 'N', 'K', 'N', 'O', 'W', 'N', '>'};
    static const char cv2[7]{'T', 'r', 'a', 'n', 's', 'P', '5'};
    static const char cv3[6]{'S', 'p', 'l', 'i', 'n', 'e'};
    static const char cv1[5]{'H', 'e', 'l', 'i', 'x'};
    switch (Type) {
    case CurveType_Line:
        str_size[0] = 1;
        str_size[1] = 4;
        str_data[0] = 'L';
        str_data[1] = 'i';
        str_data[2] = 'n';
        str_data[3] = 'e';
        break;
    case CurveType_Helix:
        str_size[0] = 1;
        str_size[1] = 5;
        for (int i1{0}; i1 < 5; i1++) {
            str_data[i1] = cv1[i1];
        }
        break;
    case CurveType_TransP5:
        str_size[0] = 1;
        str_size[1] = 7;
        for (int i2{0}; i2 < 7; i2++) {
            str_data[i2] = cv2[i2];
        }
        break;
    case CurveType_Spline:
        str_size[0] = 1;
        str_size[1] = 6;
        for (int i3{0}; i3 < 6; i3++) {
            str_data[i3] = cv3[i3];
        }
        break;
    default:
        str_size[0] = 1;
        str_size[1] = 9;
        for (int i{0}; i < 9; i++) {
            str_data[i] = b_cv[i];
        }
        break;
    }
}

//
// Arguments    : ZSpdMode m
//                coder::rtString *str
// Return Type  : void
//
static void PrintZSpdMode(ZSpdMode m, coder::rtString *str)
{
    switch (m) {
    case ZSpdMode_NN:
        str->Value.size[0] = 1;
        str->Value.size[1] = 2;
        str->Value.data[0] = 'N';
        str->Value.data[1] = 'N';
        break;
    case ZSpdMode_ZN:
        str->Value.size[0] = 1;
        str->Value.size[1] = 2;
        str->Value.data[0] = 'Z';
        str->Value.data[1] = 'N';
        break;
    case ZSpdMode_NZ:
        str->Value.size[0] = 1;
        str->Value.size[1] = 2;
        str->Value.data[0] = 'N';
        str->Value.data[1] = 'Z';
        break;
    default:
        str->Value.size[0] = 1;
        str->Value.size[1] = 2;
        str->Value.data[0] = 'Z';
        str->Value.data[1] = 'Z';
        break;
    }
}

//
// Arguments    : const FeedoptContext *ctx
//                const CurvStruct *S
// Return Type  : void
//
void PrintCurvStruct(const FeedoptContext *ctx, const CurvStruct *S)
{
    coder::rtString r;
    double dv[3][6];
    double P0[3];
    double P1[3];
    double b_validatedHoleFilling_idx_0;
    double validatedHoleFilling_f2;
    double validatedHoleFilling_idx_0;
    int varargin_1_size[2];
    int b_loop_ub;
    int loop_ub;
    char b_varargin_1_data[10];
    char varargin_2_data[10];
    char varargin_1_data[9];
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    printf("--------- CURVE STRUCT ---------\n");
    fflush(stdout);
    CurveTypeToStr(S->Type, varargin_1_data, varargin_1_size);
    loop_ub = varargin_1_size[1];
    if (0 <= loop_ub - 1) {
        std::copy(&varargin_1_data[0], &varargin_1_data[loop_ub], &varargin_2_data[0]);
    }
    varargin_2_data[varargin_1_size[1]] = '\x00';
    printf("%10s: %s\n", "Type", &varargin_2_data[0]);
    fflush(stdout);
    switch (S->Type) {
    case CurveType_Line:
    case CurveType_Spline:
        break;
    case CurveType_Helix:
        printf("%10s: [%.3f %.3f %.3f]\n", "evec", S->evec[0], S->evec[1], S->evec[2]);
        fflush(stdout);
        printf("%10s: %.3f\n", "theta", S->theta);
        fflush(stdout);
        printf("%10s: %.3f\n", "pitch", S->pitch);
        fflush(stdout);
        break;
    case CurveType_TransP5:
        printf(" CoeffP5: \n");
        fflush(stdout);
        printf("| ");
        fflush(stdout);
        for (int i{0}; i < 3; i++) {
            for (int i1{0}; i1 < 6; i1++) {
                dv[i][i1] = S->CoeffP5[i1][i];
            }
        }
        printf("%.3f ", dv[0][0]);
        fflush(stdout);
        printf("| ");
        fflush(stdout);
        printf("%.3f ", dv[1][0]);
        fflush(stdout);
        printf("| ");
        fflush(stdout);
        printf("%.3f ", dv[2][0]);
        fflush(stdout);
        printf("| ");
        fflush(stdout);
        printf("\n");
        fflush(stdout);
        printf("FeedRate: %.2f\n", S->FeedRate);
        fflush(stdout);
        break;
    default:
        printf("!!! Type = %d, UNKNOWN !!!\n", static_cast<int>(S->Type));
        fflush(stdout);
        break;
    }
    b_EvalCurvStruct(&ctx->q_splines, S->Type, S->P0, S->P1, S->CorrectedHelixCenter, S->evec,
                     S->theta, S->pitch, S->CoeffP5, S->sp_index, S->b_param, P0);
    b_EvalCurvStruct(&ctx->q_splines, S->Type, S->P0, S->P1, S->CorrectedHelixCenter, S->evec,
                     S->theta, S->pitch, S->CoeffP5, S->sp_index, S->a_param, S->b_param, P1);
    printf("%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n", "P", P0[0], P0[1], P0[2], P1[0], P1[1],
           P1[2]);
    fflush(stdout);
    validatedHoleFilling_f2 = LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, S->Type,
                                         S->P0, S->P1, S->CorrectedHelixCenter, S->evec, S->theta,
                                         S->pitch, S->CoeffP5, S->sp_index, S->a_param, S->b_param);
    printf("%10s: %e\n", "Length", validatedHoleFilling_f2);
    fflush(stdout);
    PrintZSpdMode(S->zspdmode, &r);
    b_loop_ub = r.Value.size[1];
    if (0 <= b_loop_ub - 1) {
        std::copy(&r.Value.data[0], &r.Value.data[b_loop_ub], &b_varargin_1_data[0]);
    }
    b_varargin_1_data[r.Value.size[1]] = '\x00';
    printf("ZSpdMode: %s\n", &b_varargin_1_data[0]);
    fflush(stdout);
    printf("FeedRate: %.2f\n", S->FeedRate);
    fflush(stdout);
    if (S->UseConstJerk) {
        CalcZeroStartConstraints(&ctx->q_splines, S->Type, S->P0, S->P1, S->CorrectedHelixCenter,
                                 S->evec, S->theta, S->pitch, S->CoeffP5, S->sp_index,
                                 S->UseConstJerk, S->ConstJerk, S->a_param, S->b_param, 1.0,
                                 &validatedHoleFilling_idx_0, &b_validatedHoleFilling_idx_0);
        printf("ConstJerk: %e\n", S->ConstJerk);
        fflush(stdout);
        printf("v_0      : %f\n", validatedHoleFilling_idx_0);
        fflush(stdout);
        printf("at_0     : %f\n", b_validatedHoleFilling_idx_0);
        fflush(stdout);
    }
}

//
// Arguments    : const queue_coder *ctx_q_splines
//                double ctx_cfg_NGridLengthSpline
//                const CurvStruct *S
// Return Type  : void
//
void b_PrintCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
                       const CurvStruct *S)
{
    coder::rtString r;
    double dv[3][6];
    double P0[3];
    double P1[3];
    double b_validatedHoleFilling_idx_0;
    double validatedHoleFilling_f2;
    double validatedHoleFilling_idx_0;
    int varargin_1_size[2];
    int b_loop_ub;
    int loop_ub;
    char b_varargin_1_data[10];
    char varargin_2_data[10];
    char varargin_1_data[9];
    printf("--------- CURVE STRUCT ---------\n");
    fflush(stdout);
    CurveTypeToStr(S->Type, varargin_1_data, varargin_1_size);
    loop_ub = varargin_1_size[1];
    if (0 <= loop_ub - 1) {
        std::copy(&varargin_1_data[0], &varargin_1_data[loop_ub], &varargin_2_data[0]);
    }
    varargin_2_data[varargin_1_size[1]] = '\x00';
    printf("%10s: %s\n", "Type", &varargin_2_data[0]);
    fflush(stdout);
    switch (S->Type) {
    case CurveType_Line:
    case CurveType_Spline:
        break;
    case CurveType_Helix:
        printf("%10s: [%.3f %.3f %.3f]\n", "evec", S->evec[0], S->evec[1], S->evec[2]);
        fflush(stdout);
        printf("%10s: %.3f\n", "theta", S->theta);
        fflush(stdout);
        printf("%10s: %.3f\n", "pitch", S->pitch);
        fflush(stdout);
        break;
    case CurveType_TransP5:
        printf(" CoeffP5: \n");
        fflush(stdout);
        printf("| ");
        fflush(stdout);
        for (int i{0}; i < 3; i++) {
            for (int i1{0}; i1 < 6; i1++) {
                dv[i][i1] = S->CoeffP5[i1][i];
            }
        }
        printf("%.3f ", dv[0][0]);
        fflush(stdout);
        printf("| ");
        fflush(stdout);
        printf("%.3f ", dv[1][0]);
        fflush(stdout);
        printf("| ");
        fflush(stdout);
        printf("%.3f ", dv[2][0]);
        fflush(stdout);
        printf("| ");
        fflush(stdout);
        printf("\n");
        fflush(stdout);
        printf("FeedRate: %.2f\n", S->FeedRate);
        fflush(stdout);
        break;
    default:
        printf("!!! Type = %d, UNKNOWN !!!\n", static_cast<int>(S->Type));
        fflush(stdout);
        break;
    }
    b_EvalCurvStruct(ctx_q_splines, S->Type, S->P0, S->P1, S->CorrectedHelixCenter, S->evec,
                     S->theta, S->pitch, S->CoeffP5, S->sp_index, S->b_param, P0);
    b_EvalCurvStruct(ctx_q_splines, S->Type, S->P0, S->P1, S->CorrectedHelixCenter, S->evec,
                     S->theta, S->pitch, S->CoeffP5, S->sp_index, S->a_param, S->b_param, P1);
    printf("%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n", "P", P0[0], P0[1], P0[2], P1[0], P1[1],
           P1[2]);
    fflush(stdout);
    validatedHoleFilling_f2 = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, S->Type, S->P0,
                                         S->P1, S->CorrectedHelixCenter, S->evec, S->theta,
                                         S->pitch, S->CoeffP5, S->sp_index, S->a_param, S->b_param);
    printf("%10s: %e\n", "Length", validatedHoleFilling_f2);
    fflush(stdout);
    PrintZSpdMode(S->zspdmode, &r);
    b_loop_ub = r.Value.size[1];
    if (0 <= b_loop_ub - 1) {
        std::copy(&r.Value.data[0], &r.Value.data[b_loop_ub], &b_varargin_1_data[0]);
    }
    b_varargin_1_data[r.Value.size[1]] = '\x00';
    printf("ZSpdMode: %s\n", &b_varargin_1_data[0]);
    fflush(stdout);
    printf("FeedRate: %.2f\n", S->FeedRate);
    fflush(stdout);
    if (S->UseConstJerk) {
        CalcZeroStartConstraints(ctx_q_splines, S->Type, S->P0, S->P1, S->CorrectedHelixCenter,
                                 S->evec, S->theta, S->pitch, S->CoeffP5, S->sp_index,
                                 S->UseConstJerk, S->ConstJerk, S->a_param, S->b_param, 1.0,
                                 &validatedHoleFilling_idx_0, &b_validatedHoleFilling_idx_0);
        printf("ConstJerk: %e\n", S->ConstJerk);
        fflush(stdout);
        printf("v_0      : %f\n", validatedHoleFilling_idx_0);
        fflush(stdout);
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
