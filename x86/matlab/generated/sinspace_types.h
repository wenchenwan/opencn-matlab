//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace_types.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 16-Sep-2020 12:34:56
//
#ifndef SINSPACE_TYPES_H
#define SINSPACE_TYPES_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#ifdef _MSC_VER

#pragma warning(push)
#pragma warning(disable : 4251)

#endif

// Type Definitions
namespace ocn
{
    enum CurveType
    {
        CurveType_None = 0,            // Default value
        CurveType_Line,
        CurveType_Helix,
        CurveType_Spline,
        CurveType_TransP5
    };

    enum FeedoptPlanError
    {
        FeedoptPlanError_Success = 0,  // Default value
        c_FeedoptPlanError_SmoothingFai,
        c_FeedoptPlanError_SplittingFai,
        c_FeedoptPlanError_Optimization
    };

    enum Fopt
    {
        Fopt_Init = 0,                 // Default value
        Fopt_GCode = 1,
        Fopt_Check = 2,
        Fopt_Compress = 3,
        Fopt_Smooth = 4,
        Fopt_Split = 5,
        Fopt_Opt = 6,
        Fopt_Finished = 67
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
        double u;
        bool go_next;
        double dt;
    };

    enum TransitionResult
    {
        TransitionResult_Ok = 0,       // Default value
        TransitionResult_Collinear,
        TransitionResult_NoSolution
    };

    enum ZSpdMode
    {
        ZSpdMode_NN = 0,               // Default value
        ZSpdMode_ZN,
        ZSpdMode_NZ,
        ZSpdMode_ZZ
    };

    struct SplineBase
    {
        int ncoeff;
        coder::array<double, 2U> breakpoints;
        unsigned long handle;
        int degree;
    };

    struct SplineStruct
    {
        coder::array<double, 2U> CoeffX;
        coder::array<double, 2U> CoeffY;
        coder::array<double, 2U> CoeffZ;
        SplineBase Bl;
        coder::array<double, 2U> knots;
    };

    struct CurvStruct
    {
        CurveType Type;
        ZSpdMode zspdmode;
        double P0[3];
        double P1[3];
        double evec[3];
        double theta;
        double cottheta2;
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
        coder::array<double, 1U> Coeff;
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
        unsigned long ptr;
        CurvStruct value_type;
    };

    struct FeedoptConfig
    {
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
        bool DebugFeedratePlanning;
        bool DebugCutZero;
        bool SkipCompressing;
        bool DebugOptimProgress;
    };

    struct FeedoptContext
    {
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
        coder::array<double, 2U> u_vec;
        FeedoptPlanError errcode;
        int jmax_increase_count;
        bool zero_start;
        bool zero_end;
        coder::array<double, 2U> BasisVal;
        coder::array<double, 2U> BasisValD;
        coder::array<double, 2U> BasisValDD;
        coder::array<double, 1U> BasisIntegr;
        coder::array<double, 2U> Coeff;
        int Skipped;
    };
}

#ifdef _MSC_VER

#pragma warning(pop)

#endif
#endif

//
// File trailer for sinspace_types.h
//
// [EOF]
//
