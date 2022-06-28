//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_types.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Jun-2022 16:07:49
//

#ifndef OPENCN_MATLAB_TYPES_H
#define OPENCN_MATLAB_TYPES_H

// Include Files
#include "Kinematics.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "rtwtypes.h"
#include "coder_array.h"

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct struct0_T {
    bool Skip;
    double ColTolCosLee;
};

struct struct1_T {
    bool Skip;
    double ColTolCosSmooth;
    double ColTolSmooth;
};

struct LPCfg {
    char Type[2];
    bool EnableFindReasonInfeasibility;
    double ACC_RAMP_OVER_WINDOWS;
    double VEL_RAMP_OVER_WINDOWS;
    double SLACK_PENALTY;
    bool USE_LINPROG;
};

struct emxArray_boolean_T_1x6 {
    bool data[6];
    int size[2];
};

struct emxArray_int32_T_3 {
    int data[3];
    int size[1];
};

struct emxArray_real_T_32 {
    double data[32];
    int size[1];
};

struct FeedoptConfig {
    emxArray_boolean_T_1x6 maskTot;
    emxArray_boolean_T_1x6 maskCart;
    emxArray_boolean_T_1x6 maskRot;
    emxArray_int32_T_3 indCart;
    emxArray_int32_T_3 indRot;
    int NumberAxis;
    int NCart;
    int NRot;
    emxArray_real_T_32 kin_params;
    char kin_type[5];
    int NDiscr;
    int NBreak;
    bool UseDynamicBreakpoints;
    bool UseLinearBreakpoints;
    double DynamicBreakpointsDistance;
    int NHorz;
    double fmax;
    double smax;
    double vmax[6];
    double amax[6];
    double jmax[6];
    int LeeSplineDegree;
    int SplineDegree;
    double CutOff;
    double LSplit;
    double LSplitZero;
    double LThreshold;
    double CuspThreshold;
    double v_0;
    double at_0;
    double v_1;
    double at_1;
    double dt;
    double ZeroStartAccLimit;
    double ZeroStartJerkLimit;
    double ZeroStartVelLimit;
    char source[1024];
    bool DebugCutZero;
    struct0_T Compressing;
    struct1_T Smoothing;
    double GaussLegendreN;
    double GaussLegendreX[5];
    double GaussLegendreW[5];
    LPCfg opt;
    char LogFileName[9];
};

struct b_FeedoptConfig {
    emxArray_boolean_T_1x6 maskTot;
    ::coder::array<bool, 2U> maskCart;
    ::coder::array<bool, 2U> maskRot;
    emxArray_int32_T_3 indCart;
    emxArray_int32_T_3 indRot;
    int NumberAxis;
    int NCart;
    int NRot;
    ::coder::array<double, 1U> kin_params;
    char kin_type[5];
    int NDiscr;
    int NBreak;
    bool UseDynamicBreakpoints;
    bool UseLinearBreakpoints;
    double DynamicBreakpointsDistance;
    int NHorz;
    double fmax;
    double smax;
    double vmax[6];
    double amax[6];
    double jmax[6];
    int LeeSplineDegree;
    int SplineDegree;
    double CutOff;
    double LSplit;
    double LSplitZero;
    double LThreshold;
    double CuspThreshold;
    double v_0;
    double at_0;
    double v_1;
    double at_1;
    double dt;
    double ZeroStartAccLimit;
    double ZeroStartJerkLimit;
    double ZeroStartVelLimit;
    char source[1024];
    bool DebugCutZero;
    struct0_T Compressing;
    struct1_T Smoothing;
    double GaussLegendreN;
    double GaussLegendreX[5];
    double GaussLegendreW[5];
    LPCfg opt;
    char LogFileName[9];
};

enum ReadGCodeCmd : int
{
    ReadGCodeCmd_Load = 1, // Default value
    ReadGCodeCmd_Read
};

enum Fopt : int
{
    Fopt_Init = 0, // Default value
    Fopt_GCode = 1,
    Fopt_Check = 2,
    Fopt_Compress = 3,
    Fopt_Smooth = 4,
    Fopt_Split = 5,
    Fopt_Opt = 6,
    Fopt_Finished = 67
};

enum FeedoptPlanError : int
{
    FeedoptPlanError_Success = 0, // Default value
    FeedoptPlanError_SmoothingFailed,
    FeedoptPlanError_SplittingFailed,
    FeedoptPlanError_OptimizationFailed
};

struct FeedoptContext {
    ::coder::array<double, 2U> BasisVal;
    ::coder::array<double, 2U> BasisValD;
    ::coder::array<double, 2U> BasisValDD;
    ::coder::array<double, 2U> BasisValDDD;
    ::coder::array<double, 1U> BasisIntegr;
    BaseSplineStruct Bl;
    ::coder::array<double, 2U> u_vec;
    queue_coder q_spline;
    queue_coder q_gcode;
    queue_coder q_compress;
    queue_coder q_smooth;
    queue_coder q_split;
    queue_coder q_opt;
    Fopt op;
    bool go_next;
    bool try_push_again;
    int n_optimized;
    bool reached_end;
    int k0;
    double v_0;
    double v_1;
    double at_0;
    double at_1;
    b_FeedoptConfig cfg;
    FeedoptPlanError errcode;
    int jmax_increase_count;
    bool zero_start;
    bool zero_end;
    int simplex_calls;
    int forced_stop;
    int programmed_stop;
    ::coder::array<double, 2U> Coeff;
    int Skipped;
    Kinematics kin;
};

} // namespace ocn

#endif
//
// File trailer for opencn_matlab_types.h
//
// [EOF]
//
