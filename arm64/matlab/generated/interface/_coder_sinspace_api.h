/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_sinspace_api.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 29-Mar-2021 16:21:48
 */

#ifndef _CODER_SINSPACE_API_H
#define _CODER_SINSPACE_API_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Type Definitions */
#ifndef enum_CurveType
#define enum_CurveType

enum CurveType
{
  CurveType_None = 0,                  /* Default value */
  CurveType_Line,
  CurveType_Helix,
  CurveType_Spline,
  CurveType_TransP5
};

#endif                                 /*enum_CurveType*/

#ifndef typedef_CurveType
#define typedef_CurveType

typedef enum CurveType CurveType;

#endif                                 /*typedef_CurveType*/

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

#ifndef typedef_SplineBase
#define typedef_SplineBase

typedef struct {
  int32_T ncoeff;
  emxArray_real_T *breakpoints;
  uint64_T handle;
  int32_T degree;
} SplineBase;

#endif                                 /*typedef_SplineBase*/

#ifndef typedef_SplineStruct
#define typedef_SplineStruct

typedef struct {
  emxArray_real_T *CoeffX;
  emxArray_real_T *CoeffY;
  emxArray_real_T *CoeffZ;
  SplineBase Bl;
  emxArray_real_T *knots;
} SplineStruct;

#endif                                 /*typedef_SplineStruct*/

#ifndef enum_ZSpdMode
#define enum_ZSpdMode

enum ZSpdMode
{
  ZSpdMode_NN = 0,                     /* Default value */
  ZSpdMode_ZN,
  ZSpdMode_NZ,
  ZSpdMode_ZZ
};

#endif                                 /*enum_ZSpdMode*/

#ifndef typedef_ZSpdMode
#define typedef_ZSpdMode

typedef enum ZSpdMode ZSpdMode;

#endif                                 /*typedef_ZSpdMode*/

#ifndef typedef_CurvStruct
#define typedef_CurvStruct

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
  emxArray_real_T *Coeff;
  real_T a_param;
  real_T b_param;
  SplineStruct sp;
} CurvStruct;

#endif                                 /*typedef_CurvStruct*/

#ifndef enum_DebugCfg
#define enum_DebugCfg

enum DebugCfg
{
  DebugCfg_Transitions = 1,            /* Default value */
  DebugCfg_OptimProgress,
  DebugCfg_FeedratePlanning,
  DebugCfg_Global,
  DebugCfg_Warning,
  DebugCfg_Error,
  DebugCfg_Plots,
  DebugCfg_Validate
};

#endif                                 /*enum_DebugCfg*/

#ifndef typedef_DebugCfg
#define typedef_DebugCfg

typedef enum DebugCfg DebugCfg;

#endif                                 /*typedef_DebugCfg*/

#ifndef typedef_struct0_T
#define typedef_struct0_T

typedef struct {
  boolean_T Skip;
  real_T ColTolDeg;
} struct0_T;

#endif                                 /*typedef_struct0_T*/

#ifndef typedef_FeedoptConfig
#define typedef_FeedoptConfig

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
  real_T CollTolDeg;
  real_T NGridLengthSpline;
  char_T LogFileName[9];
} FeedoptConfig;

#endif                                 /*typedef_FeedoptConfig*/

#ifndef enum_FeedoptPlanError
#define enum_FeedoptPlanError

enum FeedoptPlanError
{
  FeedoptPlanError_Success = 0,        /* Default value */
  c_FeedoptPlanError_SmoothingFai,
  c_FeedoptPlanError_SplittingFai,
  c_FeedoptPlanError_Optimization
};

#endif                                 /*enum_FeedoptPlanError*/

#ifndef typedef_FeedoptPlanError
#define typedef_FeedoptPlanError

typedef enum FeedoptPlanError FeedoptPlanError;

#endif                                 /*typedef_FeedoptPlanError*/

#ifndef enum_Fopt
#define enum_Fopt

enum Fopt
{
  Fopt_Init = 0,                       /* Default value */
  Fopt_GCode = 1,
  Fopt_Check = 2,
  Fopt_Compress = 3,
  Fopt_Smooth = 4,
  Fopt_Split = 5,
  Fopt_Opt = 6,
  Fopt_Finished = 67
};

#endif                                 /*enum_Fopt*/

#ifndef typedef_Fopt
#define typedef_Fopt

typedef enum Fopt Fopt;

#endif                                 /*typedef_Fopt*/

#ifndef struct_queue_coder_tag
#define struct_queue_coder_tag

struct queue_coder_tag
{
  uint64_T ptr;
  CurvStruct value_type;
};

#endif                                 /*struct_queue_coder_tag*/

#ifndef typedef_queue_coder
#define typedef_queue_coder

typedef struct queue_coder_tag queue_coder;

#endif                                 /*typedef_queue_coder*/

#ifndef typedef_FeedoptContext
#define typedef_FeedoptContext

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
  emxArray_real_T *u_vec;
  FeedoptPlanError errcode;
  int32_T jmax_increase_count;
  boolean_T zero_start;
  boolean_T zero_end;
  int32_T forced_stop;
  int32_T programmed_stop;
  emxArray_real_T *BasisVal;
  emxArray_real_T *BasisValD;
  emxArray_real_T *BasisValDD;
  emxArray_real_T *BasisIntegr;
  emxArray_real_T *Coeff;
  int32_T Skipped;
} FeedoptContext;

#endif                                 /*typedef_FeedoptContext*/

#ifndef struct_ResampleStateClass_tag
#define struct_ResampleStateClass_tag

struct ResampleStateClass_tag
{
  real_T u;
  boolean_T go_next;
  real_T dt;
};

#endif                                 /*struct_ResampleStateClass_tag*/

#ifndef typedef_ResampleStateClass
#define typedef_ResampleStateClass

typedef struct ResampleStateClass_tag ResampleStateClass;

#endif                                 /*typedef_ResampleStateClass*/

#ifndef enum_TransitionResult
#define enum_TransitionResult

enum TransitionResult
{
  TransitionResult_Ok = 0,             /* Default value */
  TransitionResult_Collinear,
  TransitionResult_NoSolution
};

#endif                                 /*enum_TransitionResult*/

#ifndef typedef_TransitionResult
#define typedef_TransitionResult

typedef enum TransitionResult TransitionResult;

#endif                                 /*typedef_TransitionResult*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void CalcTransition(FeedoptContext ctx, CurvStruct CurvStruct1,
  CurvStruct CurvStruct2, CurvStruct *CurvStruct1_C, CurvStruct *CurvStruct_T,
  CurvStruct *CurvStruct2_C, TransitionResult *status);
extern void CalcTransition_api(const mxArray * const prhs[3], int32_T nlhs,
  const mxArray *plhs[4]);
extern void ConfigSetSource(FeedoptConfig *cfg, char_T filename_data[], int32_T
  filename_size[2]);
extern void ConfigSetSource_api(const mxArray * const prhs[2], int32_T nlhs,
  const mxArray *plhs[1]);
extern void ConstrCurvStructType(CurvStruct *C);
extern void ConstrCurvStructType_api(int32_T nlhs, const mxArray *plhs[1]);
extern void ConstrHelixStruct(real_T P0[3], real_T P1[3], real_T Cprim[3],
  real_T delta, real_T evec[3], real_T theta, real_T pitch, real_T FeedRate,
  ZSpdMode b_ZSpdMode, CurvStruct *b_CurvStruct);
extern void ConstrHelixStructFromArcFeed(real_T p0x, real_T p0y, real_T p0z,
  real_T p1x, real_T p1y, real_T p1z, real_T cx, real_T cy, real_T cz, real_T
  rotation, real_T evec[3], CurvStruct *b_CurvStruct);
extern void ConstrHelixStructFromArcFeed_api(const mxArray * const prhs[11],
  int32_T nlhs, const mxArray *plhs[1]);
extern void ConstrHelixStruct_api(const mxArray * const prhs[9], int32_T nlhs,
  const mxArray *plhs[1]);
extern void ConstrLineStruct(real_T P0[3], real_T P1[3], real_T FeedRate,
  ZSpdMode b_ZSpdMode, CurvStruct *b_CurvStruct);
extern void ConstrLineStruct_api(const mxArray * const prhs[4], int32_T nlhs,
  const mxArray *plhs[1]);
extern void CopyCurvStruct(CurvStruct Curv, CurvStruct *Copy);
extern void CopyCurvStruct_api(const mxArray * const prhs[1], int32_T nlhs,
  const mxArray *plhs[1]);
extern void DisableDebugLog(DebugCfg cfg);
extern void DisableDebugLog_api(const mxArray * const prhs[1], int32_T nlhs);
extern void EnableDebugLog(DebugCfg cfg);
extern void EnableDebugLog_api(const mxArray * const prhs[1], int32_T nlhs);
extern void EvalCurvStruct(FeedoptContext ctx, CurvStruct b_CurvStruct,
  emxArray_real_T *u_vec, emxArray_real_T *r0D, emxArray_real_T *r1D,
  emxArray_real_T *r2D, emxArray_real_T *r3D);
extern void EvalCurvStruct_api(const mxArray * const prhs[3], int32_T nlhs,
  const mxArray *plhs[4]);
extern void EvalPosition(CurvStruct Curv, CurvStruct Spline, real_T u, real_T
  r0D[3]);
extern void EvalPosition_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[1]);
extern void FeedoptDefaultConfig(FeedoptConfig *cfg);
extern void FeedoptDefaultConfig_api(int32_T nlhs, const mxArray *plhs[1]);
extern void FeedoptPlan(FeedoptContext *ctx, boolean_T *optimized, CurvStruct
  *opt_struct);
extern void FeedoptPlan_api(const mxArray * const prhs[1], int32_T nlhs, const
  mxArray *plhs[3]);
extern void InitFeedoptPlan(FeedoptConfig cfg, FeedoptContext *ctx);
extern void InitFeedoptPlan_api(const mxArray * const prhs[1], int32_T nlhs,
  const mxArray *plhs[1]);
extern void PrintCurvStruct(FeedoptContext ctx, CurvStruct S);
extern void PrintCurvStruct_api(const mxArray * const prhs[2], int32_T nlhs);
extern void ResampleNoCtx(ResampleStateClass *state, SplineBase Bl, CurvStruct
  Curv);
extern void ResampleNoCtx_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[1]);
extern void ResampleState(real_T dt, ResampleStateClass *state);
extern void ResampleState_api(const mxArray * const prhs[1], int32_T nlhs, const
  mxArray *plhs[1]);
extern void bspline_copy(SplineBase Bl, SplineBase *Copy);
extern void bspline_copy_api(const mxArray * const prhs[1], int32_T nlhs, const
  mxArray *plhs[1]);
extern void bspline_create(int32_T degree, real_T breakpoints[10], SplineBase
  *Bl);
extern void bspline_create_api(const mxArray * const prhs[2], int32_T nlhs,
  const mxArray *plhs[1]);
extern void c_roots_(real_T coeffs_data[], int32_T coeffs_size[2], creal_T
                     Y_data[], int32_T Y_size[1]);
extern void c_roots__api(const mxArray * const prhs[1], int32_T nlhs, const
  mxArray *plhs[1]);
extern void linspace(real_T d1, real_T d2, real_T n1, emxArray_real_T *y);
extern void linspace_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[1]);
extern void sinspace(real_T x0, real_T x1, int32_T N, emxArray_real_T *x);
extern void sinspace_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[1]);
extern void sinspace_atexit(void);
extern void sinspace_initialize(void);
extern void sinspace_terminate(void);
extern void sinspace_xil_shutdown(void);
extern void sinspace_xil_terminate(void);

#endif

/*
 * File trailer for _coder_sinspace_api.h
 *
 * [EOF]
 */
