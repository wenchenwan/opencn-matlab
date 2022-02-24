//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_types.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 24-Feb-2022 11:51:03
//

#ifndef OPENCN_MATLAB_TYPES_H
#define OPENCN_MATLAB_TYPES_H

// Include Files
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types21.h"
#include "queue_coder.h"
#include "rtwtypes.h"
#include "coder_array.h"

// Custom Header Code
#include "functions.h"
// Type Definitions
namespace ocn {
struct struct0_T {
    bool Skip;
    double ColTolCos;
};

struct FeedoptConfig {
    int NDiscr;
    int NBreak;
    bool UseDynamicBreakpoints;
    bool UseLinearBreakpoints;
    double DynamicBreakpointsDistance;
    int NHorz;
    double vmax;
    double amax[3];
    double jmax[3];
    int SplineDegree;
    double CutOff;
    double LSplit;
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
    double ColTolCos;
    double GaussLegendreN;
    double GaussLegendreX[5];
    double GaussLegendreW[5];
    char LogFileName[4];
    double Simplex_params[4];
};

struct struct_T {
    int ncoeff;
    unsigned long handle;
    int degree;
};

struct b_struct_T {
    double CoeffX;
    double CoeffY;
    double CoeffZ;
    struct_T Bl;
    double knots;
    double Ltot;
    double Lk;
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

enum TransitionResult : int
{
    TransitionResult_Ok = 0, // Default value
    TransitionResult_Collinear,
    TransitionResult_NoSolution
};

struct c_struct_T {
    CurveType Type;
    ZSpdMode zspdmode;
    bool TRAFO;
    bool HSC;
    char HSC_cmd[256];
    double Poff[3];
    double Aoff[3];
    double Uoff[3];
    double Doff;
    double P0[3];
    double P1[3];
    double A0[3];
    double A1[3];
    double U0[3];
    double U1[3];
    double CorrectedHelixCenter[3];
    double delta;
    double evec[3];
    double theta;
    double pitch;
    double CoeffP5[6][3];
    int sp_index;
    double FeedRate;
    double SpindleSpeed;
    double MaxConstantFeedRate;
    int i_begin_sp;
    int i_end_sp;
    int gcode_source_line;
    int index_smooth;
    bool UseConstJerk;
    double ConstJerk;
    int ConstJerkMaxIterations;
    double a_param;
    double b_param;
    b_struct_T sp;
};

struct FeedoptContext {
    Fopt op;
    bool go_next;
    queue_coder q_gcode;
    queue_coder q_compress;
    queue_coder q_splines;
    queue_coder q_smooth;
    queue_coder q_split;
    queue_coder q_opt;
    bool try_push_again;
    int n_optimized;
    bool reached_end;
    int k0;
    double v_0;
    double v_1;
    double at_0;
    double at_1;
    FeedoptConfig cfg;
    SplineBase Bl;
    ::coder::array<double, 2U> u_vec;
    FeedoptPlanError errcode;
    int jmax_increase_count;
    bool zero_start;
    bool zero_end;
    int simplex_calls;
    int forced_stop;
    int programmed_stop;
    ::coder::array<double, 2U> BasisVal;
    ::coder::array<double, 2U> BasisValD;
    ::coder::array<double, 2U> BasisValDD;
    ::coder::array<double, 1U> BasisIntegr;
    ::coder::array<double, 2U> Coeff;
    int Skipped;
};

} // namespace ocn

#endif
//
// File trailer for opencn_matlab_types.h
//
// [EOF]
//
