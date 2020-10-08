//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 08-Oct-2020 13:35:40
//
#ifndef SINSPACE_H
#define SINSPACE_H

// Include Files
#include "rtwtypes.h"
#include "sinspace_types.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"

// Type Declarations
namespace ocn
{
    struct FeedoptConfig;
    struct FeedoptContext;
}

// Type Definitions
namespace ocn
{
    struct SplineBase
    {
        int ncoeff;
        ::coder::array<double, 2U> breakpoints;
        unsigned long handle;
        int degree;
    };

    struct SplineStruct
    {
        ::coder::array<double, 2U> CoeffX;
        ::coder::array<double, 2U> CoeffY;
        ::coder::array<double, 2U> CoeffZ;
        SplineBase Bl;
        ::coder::array<double, 2U> knots;
    };

    enum ZSpdMode
    {
        ZSpdMode_NN = 0,               // Default value
        ZSpdMode_ZN,
        ZSpdMode_NZ,
        ZSpdMode_ZZ
    };

    enum CurveType
    {
        CurveType_None = 0,            // Default value
        CurveType_Line,
        CurveType_Helix,
        CurveType_Spline,
        CurveType_TransP5
    };

    struct CurvStruct
    {
        CurveType Type;
        ZSpdMode zspdmode;
        double P0[3];
        double P1[3];
        double HelixCenter[3];
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
        ::coder::array<double, 1U> Coeff;
        double a_param;
        double b_param;
        SplineStruct sp;
    };

    class queue_coder
    {
      public:
        void init(const CurvStruct *b_value_type);
        void push(const CurvStruct *value) const;
        void get(int b_index, CurvStruct *value) const;
        bool isempty() const;
        unsigned int size() const;
        void rget(CurvStruct *value) const;
        void get(unsigned int b_index, CurvStruct *value) const;
        void set(unsigned int b_index, const CurvStruct *value) const;
        void get(double b_index, CurvStruct *value) const;
        void get(long b_index, CurvStruct *value) const;
        void get(unsigned long b_index, CurvStruct *value) const;
        queue_coder();
        ~queue_coder();
        unsigned long ptr;
        CurvStruct value_type;
    };

    class ResampleStateClass
    {
      public:
        void init(double b_dt);
        void set_u();
        void set_go_next();
        void set_dt(double val);
        void set_u(double val);
        void b_set_go_next();
        ResampleStateClass();
        ~ResampleStateClass();
        double u;
        bool go_next;
        double dt;
    };
}

// Variable Declarations
namespace ocn
{
    extern double sqrt_calls;
    extern double cos_calls;
    extern double sin_calls;
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
    extern void ConstrHelixStruct(const double P0[3], const double P1[3], const double C[3], const
        double evec[3], double theta, double pitch, double FeedRate, ZSpdMode b_ZSpdMode, CurvStruct
        *b_CurvStruct);
    extern void ConstrHelixStructFromArcFeed(double p0x, double p0y, double p0z, double p1x, double
        p1y, double p1z, double cx, double cy, double cz, double rotation, const double evec[3],
        CurvStruct *b_CurvStruct);
    extern void ConstrLineStruct(const double P0[3], const double P1[3], double FeedRate, ZSpdMode
        b_ZSpdMode, CurvStruct *b_CurvStruct);
    extern void CopyCurvStruct(const CurvStruct *Curv, CurvStruct *Copy);
    extern void DisableDebugLog(DebugCfg cfg);
    extern void EnableDebugLog(DebugCfg cfg);
    extern void EvalCurvStruct(const FeedoptContext *ctx, const CurvStruct *b_CurvStruct, ::coder::
        array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D, ::
        coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D);
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
    namespace coder
    {
        extern void linspace(double d1, double d2, double n, ::coder::array<double, 2U> &y);
    }

    extern void sinspace(double x0, double x1, int N, ::coder::array<double, 2U> &x);
    extern void sinspace_initialize();
    extern void sinspace_terminate();
}

#endif

//
// File trailer for sinspace.h
//
// [EOF]
//
