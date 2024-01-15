
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_types.h
//
// MATLAB Coder version            : 5.4
//

#ifndef OPENCN_MATLAB_TYPES_H
#define OPENCN_MATLAB_TYPES_H

// Include Files
#include "Kinematics.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include "coder_bounded_array.h"

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct struct0_T {
    bool Skip;
    double CuspThreshold;
};

struct struct1_T {
    bool Skip;
    double ColTolCosLee;
};

struct struct2_T {
    bool Skip;
    double ColTolCosSmooth;
    double ColTolSmooth;
};

struct MsgStruct {
    char msg[2048];
    double size;
};

struct LPCfg {
    char Type[2];
    bool USE_JERK_CONSTRAINTS;
    bool FIND_REASON_INFEASIBILITY;
    double ACC_RAMP_OVER_WINDOWS;
    double VEL_RAMP_OVER_WINDOWS;
    double SLACK_PENALTY;
    bool USE_LENGTH_SCALING;
    bool USE_LINPROG;
    bool FORCE_POSITIV_COEFFS;
};

struct FeedoptConfig {
    bool ENABLE_PRINT_MSG;
    ::coder::bounded_array<bool, 6U, 2U> maskTot;
    ::coder::bounded_array<bool, 6U, 2U> maskCart;
    ::coder::bounded_array<bool, 6U, 2U> maskRot;
    ::coder::bounded_array<int, 3U, 1U> indCart;
    ::coder::bounded_array<int, 3U, 1U> indRot;
    int NumberAxis;
    int NCart;
    int NRot;
    ::coder::bounded_array<double, 6U, 1U> D;
    double coeffD;
    ::coder::bounded_array<double, 32U, 1U> kin_params;
    char kin_type[8];
    int NDiscr;
    int NBreak;
    bool SplitSpecialSpline;
    bool ReleaseMemoryOfTheQueues;
    bool UseDynamicBreakpoints;
    bool UseLinearBreakpoints;
    double DynamicBreakpointsDistance;
    int NHorz;
    double vmax[6];
    double amax[6];
    double jmax[6];
    int LeeSplineDegree;
    int SplineDegree;
    double CutOff;
    double LSplit;
    double LSplitZero;
    double LThresholdMax;
    double LThresholdMin;
    double v_0;
    double at_0;
    double v_1;
    double at_1;
    double dt;
    double DefaultZeroStopCount;
    ::coder::bounded_array<char, 1024U, 2U> source;
    struct0_T Cusp;
    struct1_T Compressing;
    struct2_T Smoothing;
    double GaussLegendreN;
    double GaussLegendreX[5];
    double GaussLegendreW[5];
    LPCfg opt;
    char LogFileName[9];
};

struct b_FeedoptConfig {
    bool ENABLE_PRINT_MSG;
    ::coder::bounded_array<bool, 6U, 2U> maskTot;
    ::coder::bounded_array<bool, 6U, 2U> maskCart;
    ::coder::bounded_array<bool, 6U, 2U> maskRot;
    ::coder::array<int, 1U> indCart;
    ::coder::array<int, 1U> indRot;
    int NumberAxis;
    int NCart;
    int NRot;
    ::coder::array<double, 1U> D;
    double coeffD;
    ::coder::bounded_array<double, 32U, 1U> kin_params;
    char kin_type[8];
    int NDiscr;
    int NBreak;
    bool SplitSpecialSpline;
    bool ReleaseMemoryOfTheQueues;
    bool UseDynamicBreakpoints;
    bool UseLinearBreakpoints;
    double DynamicBreakpointsDistance;
    int NHorz;
    double vmax[6];
    double amax[6];
    double jmax[6];
    int LeeSplineDegree;
    int SplineDegree;
    double CutOff;
    double LSplit;
    double LSplitZero;
    double LThresholdMax;
    double LThresholdMin;
    double v_0;
    double at_0;
    double v_1;
    double at_1;
    double dt;
    double DefaultZeroStopCount;
    ::coder::bounded_array<char, 1024U, 2U> source;
    struct0_T Cusp;
    struct1_T Compressing;
    struct2_T Smoothing;
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
    FeedoptPlanError_NoError = 0, // Default value
    FeedoptPlanError_ReadGCodeFailed,
    FeedoptPlanError_CuspFailed,
    FeedoptPlanError_CompressingFailed,
    FeedoptPlanError_SmoothingFailed,
    FeedoptPlanError_SplittingFailed,
    FeedoptPlanError_OptimizationFailed,
    FeedoptPlanError_Success
};

enum ReadGCodeError : int
{
    ReadGCodeError_InterpOk = 0, // Default value
    ReadGCodeError_InterpExit,
    ReadGCodeError_InterpExecEnd,
    ReadGCodeError_InterpEndFile,
    ReadGCodeError_InterpNotOpen,
    ReadGCodeError_InterpError,
    ReadGCodeError_ToDebug
};

struct b_CurvStruct {
    GcodeInfoStruct Info;
    Tool tool;
    SplineStruct sp;
    ::coder::bounded_array<double, 6U, 1U> R0;
    ::coder::bounded_array<double, 6U, 1U> R1;
    double CorrectedHelixCenter[3];
    double delta;
    double evec[3];
    double theta;
    double pitch;
    ::coder::array<double, 2U> CoeffP5;
    unsigned int sp_index;
    int i_begin_sp;
    int i_end_sp;
    int index_smooth;
    bool UseConstJerk;
    double ConstJerk;
    ::coder::array<double, 1U> Coeff;
    double a_param;
    double b_param;
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
    FeedoptConfig cfg;
    int jmax_increase_count;
    bool zero_start;
    bool zero_end;
    bool zero_forced;
    CurvStruct zero_forced_buffer[2];
    int simplex_calls;
    int forced_stop;
    int programmed_stop;
    ::coder::array<double, 2U> Coeff;
    int Skipped;
    Kinematics kin;
    MsgStruct errmsg;
    FeedoptPlanError errcode;
};

} // namespace ocn

#endif
//
// File trailer for opencn_matlab_types.h
//
// [EOF]
//
