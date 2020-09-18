//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 18-Sep-2020 12:53:48
//
#ifndef SINSPACE_H
#define SINSPACE_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "sinspace_types.h"

// Custom Header Code
#include "functions.h"

// Variable Declarations
namespace ocn
{
    extern double DebugConfig;
}

// Function Declarations
namespace ocn
{
    extern void CalcTransition(const FeedoptContext *ctx, const CurvStruct *CurvStruct1, const
        CurvStruct *CurvStruct2, CurvStruct *CurvStruct1_C, CurvStruct *CurvStruct_T, CurvStruct
        *CurvStruct2_C, TransitionResult *status);
    extern void ConfigSetSource(FeedoptConfig *cfg, const char filename_data[], const int
        filename_size[2]);
    extern void ConstrCurvStructType(CurvStruct *C);
    extern void ConstrHelixStruct(const double P0[3], const double P1[3], const double evec[3],
        double theta, double pitch, double FeedRate, ZSpdMode b_ZSpdMode, CurvStruct *b_CurvStruct);
    extern void ConstrHelixStructFromArcFeed(double p0x, double p0y, double p0z, double p1x, double
        p1y, double p1z, double cx, double cy, double cz, double rotation, const double evec[3],
        CurvStruct *b_CurvStruct);
    extern void ConstrLineStruct(const double P0[3], const double P1[3], double FeedRate, ZSpdMode
        b_ZSpdMode, CurvStruct *b_CurvStruct);
    extern void CopyCurvStruct(const CurvStruct *Curv, CurvStruct *Copy);
    extern void EvalCurvStruct(const FeedoptContext *ctx, const CurvStruct *b_CurvStruct, coder::
        array<double, 2U> &u_vec, coder::array<double, 2U> &r0D, coder::array<double, 2U> &r1D,
        coder::array<double, 2U> &r2D, coder::array<double, 2U> &r3D);
    extern void EvalPosition(const CurvStruct *Curv, const CurvStruct *Spline, double u, double r0D
        [3]);
    extern void FeedoptDefaultConfig(FeedoptConfig *cfg);
    extern void FeedoptPlan(FeedoptContext *ctx, bool *optimized, CurvStruct *opt_struct);
    extern void InitFeedoptPlan(const FeedoptConfig cfg, FeedoptContext *ctx);
    extern void PrintCurvStruct(const FeedoptContext *ctx, const CurvStruct *S);
    extern void ResampleNoCtx(ResampleStateClass *state, const SplineBase *Bl, const CurvStruct
        *Curv);
    extern void ResampleState(double dt, ResampleStateClass *state);
    extern void bspline_copy(const SplineBase *Bl, SplineBase *Copy);
    extern void bspline_create(int degree, const double breakpoints[10], SplineBase *Bl);
    extern void c_roots_(const double coeffs_data[], const int coeffs_size[2], creal_T Y_data[], int
                         Y_size[1]);
    extern void linspace(double d1, double d2, double n1, coder::array<double, 2U> &y);
    extern void sinspace(double x0, double x1, int N, coder::array<double, 2U> &x);
    extern void sinspace_initialize();
    extern void sinspace_terminate();
}

#endif

//
// File trailer for sinspace.h
//
// [EOF]
//
