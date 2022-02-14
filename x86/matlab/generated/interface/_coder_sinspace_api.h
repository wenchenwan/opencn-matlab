//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: _coder_sinspace_api.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:47:09
//

#ifndef _CODER_SINSPACE_API_H
#define _CODER_SINSPACE_API_H

// Include Files
#include "coder_array_mex.h"
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Type Definitions
typedef struct {
    boolean_T Skip;
    real_T ColTolCos;
} struct0_T;

struct ResampleStateClass_tag_0 {
    real_T u;
    boolean_T go_next;
    real_T dt;
};
typedef ResampleStateClass_tag_0 ResampleStateClass;

typedef struct {
    int32_T NDiscr;
    int32_T NBreak;
    boolean_T UseDynamicBreakpoints;
    boolean_T UseLinearBreakpoints;
    real_T DynamicBreakpointsDistance;
    int32_T NHorz;
    real_T vmax;
    real_T amax[3];
    real_T jmax[3];
    int32_T SplineDegree;
    real_T CutOff;
    real_T LSplit;
    real_T LThreshold;
    real_T CuspThreshold;
    real_T v_0;
    real_T at_0;
    real_T v_1;
    real_T at_1;
    real_T dt;
    real_T ZeroStartAccLimit;
    real_T ZeroStartJerkLimit;
    real_T ZeroStartVelLimit;
    char_T source[1024];
    boolean_T DebugCutZero;
    struct0_T Compressing;
    real_T ColTolCos;
    real_T GaussLegendreN;
    real_T GaussLegendreX[5];
    real_T GaussLegendreW[5];
    char_T LogFileName[4];
    real_T Simplex_params[4];
} FeedoptConfig;

typedef struct {
    int32_T ncoeff;
    coder::array<real_T, 2U> breakpoints;
    uint64_T handle;
    int32_T degree;
} SplineBase;

typedef struct {
    coder::array<real_T, 2U> CoeffX;
    coder::array<real_T, 2U> CoeffY;
    coder::array<real_T, 2U> CoeffZ;
    SplineBase Bl;
    coder::array<real_T, 2U> knots;
    real_T Ltot;
    coder::array<real_T, 2U> Lk;
} SplineStruct;

enum Fopt : int32_T
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

enum CurveType : int32_T
{
    CurveType_None = 0, // Default value
    CurveType_Line,
    CurveType_Helix,
    CurveType_Spline,
    CurveType_TransP5
};

enum ZSpdMode : int32_T
{
    ZSpdMode_NN = 0, // Default value
    ZSpdMode_ZN,
    ZSpdMode_NZ,
    ZSpdMode_ZZ
};

enum FeedoptPlanError : int32_T
{
    FeedoptPlanError_Success = 0, // Default value
    FeedoptPlanError_SmoothingFailed,
    FeedoptPlanError_SplittingFailed,
    FeedoptPlanError_OptimizationFailed
};

enum TransitionResult : int32_T
{
    TransitionResult_Ok = 0, // Default value
    TransitionResult_Collinear,
    TransitionResult_NoSolution
};

enum DebugCfg : int32_T
{
    DebugCfg_Transitions = 1, // Default value
    DebugCfg_OptimProgress,
    DebugCfg_FeedratePlanning,
    DebugCfg_Global,
    DebugCfg_Warning,
    DebugCfg_Error,
    DebugCfg_Plots,
    DebugCfg_Validate
};

typedef struct {
    CurveType Type;
    ZSpdMode zspdmode;
    real_T P0[3];
    real_T P1[3];
    real_T CorrectedHelixCenter[3];
    real_T delta;
    real_T evec[3];
    real_T theta;
    real_T pitch;
    real_T CoeffP5[6][3];
    int32_T sp_index;
    real_T FeedRate;
    real_T SpindleSpeed;
    real_T MaxConstantFeedRate;
    int32_T i_begin_sp;
    int32_T i_end_sp;
    int32_T gcode_source_line;
    int32_T index_smooth;
    boolean_T UseConstJerk;
    real_T ConstJerk;
    int32_T ConstJerkMaxIterations;
    coder::array<real_T, 1U> Coeff;
    real_T a_param;
    real_T b_param;
    SplineStruct sp;
} CurvStruct;

struct queue_coder_tag_0 {
    uint64_T ptr;
    CurvStruct value_type;
};
typedef queue_coder_tag_0 queue_coder;

typedef struct {
    Fopt op;
    boolean_T go_next;
    queue_coder q_gcode;
    queue_coder q_compress;
    queue_coder q_splines;
    queue_coder q_smooth;
    queue_coder q_split;
    queue_coder q_opt;
    boolean_T try_push_again;
    int32_T n_optimized;
    boolean_T reached_end;
    int32_T k0;
    real_T v_0;
    real_T v_1;
    real_T at_0;
    real_T at_1;
    FeedoptConfig cfg;
    SplineBase Bl;
    coder::array<real_T, 2U> u_vec;
    FeedoptPlanError errcode;
    int32_T jmax_increase_count;
    boolean_T zero_start;
    boolean_T zero_end;
    int32_T simplex_calls;
    int32_T forced_stop;
    int32_T programmed_stop;
    coder::array<real_T, 2U> BasisVal;
    coder::array<real_T, 2U> BasisValD;
    coder::array<real_T, 2U> BasisValDD;
    coder::array<real_T, 1U> BasisIntegr;
    coder::array<real_T, 2U> Coeff;
    int32_T Skipped;
} FeedoptContext;

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void CalcTransition(FeedoptContext *ctx, CurvStruct *CurvStruct1, CurvStruct *CurvStruct2,
                    CurvStruct *CurvStruct1_C, CurvStruct *CurvStruct_T, CurvStruct *CurvStruct2_C,
                    TransitionResult *status);

void CalcTransition_api(const mxArray *const prhs[3], int32_T nlhs, const mxArray *plhs[4]);

void ConfigSetSource(FeedoptConfig *cfg, char_T filename_data[], int32_T filename_size[2]);

void ConfigSetSource_api(const mxArray *const prhs[2], const mxArray **plhs);

void ConstrCurvStructType(CurvStruct *C);

void ConstrCurvStructType_api(const mxArray **plhs);

void ConstrHelixStruct(real_T P0[3], real_T P1[3], real_T Cprim[3], real_T delta, real_T evec[3],
                       real_T theta, real_T pitch, real_T FeedRate, ZSpdMode b_ZSpdMode,
                       CurvStruct *b_CurvStruct);

void ConstrHelixStructFromArcFeed(real_T p0x, real_T p0y, real_T p0z, real_T p1x, real_T p1y,
                                  real_T p1z, real_T cx, real_T cy, real_T cz, real_T rotation,
                                  real_T evec[3], CurvStruct *b_CurvStruct);

void ConstrHelixStructFromArcFeed_api(const mxArray *const prhs[11], const mxArray **plhs);

void ConstrHelixStruct_api(const mxArray *const prhs[9], const mxArray **plhs);

void ConstrLineStruct(real_T P0[3], real_T P1[3], real_T FeedRate, ZSpdMode b_ZSpdMode,
                      CurvStruct *b_CurvStruct);

void ConstrLineStruct_api(const mxArray *const prhs[4], const mxArray **plhs);

void CopyCurvStruct(CurvStruct *Curv, CurvStruct *Copy);

void CopyCurvStruct_api(const mxArray *prhs, const mxArray **plhs);

void DisableDebugLog(DebugCfg cfg);

void DisableDebugLog_api(const mxArray *prhs);

void EnableDebugLog(DebugCfg cfg);

void EnableDebugLog_api(const mxArray *prhs);

void EvalCurvStruct(FeedoptContext *ctx, CurvStruct *b_CurvStruct, coder::array<real_T, 2U> *u_vec,
                    coder::array<real_T, 2U> *r0D, coder::array<real_T, 2U> *r1D,
                    coder::array<real_T, 2U> *r2D, coder::array<real_T, 2U> *r3D);

void EvalCurvStruct_api(const mxArray *const prhs[3], int32_T nlhs, const mxArray *plhs[4]);

void EvalPosition(CurvStruct *Curv, CurvStruct *Spline, real_T u, real_T r0D[3]);

void EvalPosition_api(const mxArray *const prhs[3], const mxArray **plhs);

void FeedoptDefaultConfig(FeedoptConfig *cfg);

void FeedoptDefaultConfig_api(const mxArray **plhs);

void FeedoptPlan(FeedoptContext *ctx, boolean_T *optimized, CurvStruct *opt_struct);

void FeedoptPlan_api(const mxArray *prhs, int32_T nlhs, const mxArray *plhs[3]);

void InitFeedoptPlan(FeedoptConfig cfg, FeedoptContext *ctx);

void InitFeedoptPlan_api(const mxArray *prhs, const mxArray **plhs);

void PrintCurvStruct(FeedoptContext *ctx, CurvStruct *S);

void PrintCurvStruct_api(const mxArray *const prhs[2]);

void ResampleNoCtx(ResampleStateClass *state, SplineBase *Bl, CurvStruct *Curv);

void ResampleNoCtx_api(const mxArray *const prhs[3], const mxArray **plhs);

void ResampleState(real_T dt, ResampleStateClass *state);

void ResampleState_api(const mxArray *prhs, const mxArray **plhs);

void bspline_copy(SplineBase *Bl, SplineBase *Copy);

void bspline_copy_api(const mxArray *prhs, const mxArray **plhs);

void bspline_create(int32_T degree, real_T breakpoints[10], SplineBase *Bl);

void bspline_create_api(const mxArray *const prhs[2], const mxArray **plhs);

void c_roots_(real_T coeffs_data[], int32_T coeffs_size[2], creal_T Y_data[], int32_T Y_size[1]);

void c_roots__api(const mxArray *prhs, const mxArray **plhs);

void linspace(real_T d1, real_T d2, real_T n, coder::array<real_T, 2U> *y);

void linspace_api(const mxArray *const prhs[3], const mxArray **plhs);

void sinspace(real_T x0, real_T x1, int32_T N, coder::array<real_T, 2U> *x);

void sinspace_api(const mxArray *const prhs[3], const mxArray **plhs);

void sinspace_atexit();

void sinspace_initialize();

void sinspace_terminate();

void sinspace_xil_shutdown();

void sinspace_xil_terminate();

#endif
//
// File trailer for _coder_sinspace_api.h
//
// [EOF]
//
