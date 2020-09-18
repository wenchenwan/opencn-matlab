//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 18-Sep-2020 12:55:43
//

// Include Files
#include "sinspace.h"
#include "cpp_simplex.hpp"
#include "functions.h"
#include "src/c_spline.h"
#include <cfloat>
#include <cmath>
#include <cstring>
#include <immintrin.h>
#include <math.h>
#include <stdio.h>

// Type Definitions
namespace ocn
{
    class coder_internal_sparse
    {
      public:
        void init(double ridx, double cidx);
        int nnzInt() const;
        void vertcat(const coder::array<double, 2U> &varargin_2, coder_internal_sparse *c) const;
        bool isempty() const;
        static void spallocLike(int b_m, int b_n, int nzmax, coder_internal_sparse *s);
        void init(int b_m, int b_n, int nzmaxval);
        void vertcat(const coder_internal_sparse *varargin_2, coder_internal_sparse *c) const;
        void parenAssign(const coder::array<double, 2U> &rhs, const coder::array<double, 2U>
                         &varargin_1, const coder::array<double, 2U> &varargin_2);
        void parenAssign2D(const coder::array<double, 2U> &rhs, const coder::array<double, 2U> &r,
                           const coder::array<double, 2U> &c);
        coder::array<double, 1U> d;
        coder::array<int, 1U> colidx;
        coder::array<int, 1U> rowidx;
        int m;
        int n;
        int maxnz;
    };

    struct emxArray_char_T_1x10
    {
        char data[10];
        int size[2];
    };

    struct cell_wrap_9
    {
        emxArray_char_T_1x10 f1;
    };

    struct cell_wrap_3
    {
        coder::array<double, 2U> f1;
    };

    struct emxArray_char_T_1x9
    {
        char data[9];
        int size[2];
    };

    class rtString
    {
      public:
        void init();
        void b_init();
        void c_init();
        void d_init();
        void uncheckedChar(char result_data[], int result_size[2]) const;
      private:
        emxArray_char_T_1x9 Value;
    };
}

// Variable Definitions
namespace ocn
{
    double DebugConfig;
    static const char cv[30] = { 'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ', 'C', 'u', 'r', 'v', 'e',
        ' ', 'T', 'y', 'p', 'e', ' ', 'f', 'o', 'r', ' ', 'E', 'v', 'a', 'l', '.', '\\', 'n' };

    static const char cv1[16] = { 'e', ' ', 'c', 'r', 'o', 's', 's', ' ', 'P', '0', 'P', '1', ' ',
        '=', ' ', '0' };

    static const char cv2[9] = { '<', 'U', 'N', 'K', 'N', 'O', 'W', 'N', '>' };

    static bool isInitialized_sinspace = false;
}

// Function Declarations
namespace ocn
{
    static void BuildConstrJerk_v4(const queue_coder *ctx_q_splines, const coder::array<CurvStruct,
        2U> &CurvStructs, const coder::array<double, 2U> &Coeff, const double jmax[3], const coder::
        array<double, 2U> &BasisVal, const coder::array<double, 2U> &BasisValD, const coder::array<
        double, 2U> &BasisValDD, const coder::array<double, 2U> &u_vec, coder_internal_sparse *A,
        coder::array<double, 1U> &b);
    static void BuildConstr_v4(const queue_coder *ctx_q_splines, bool ctx_cfg_UseDynamicBreakpoints,
        bool ctx_cfg_UseLinearBreakpoints, double c_ctx_cfg_DynamicBreakpointsDis, int
        ctx_cfg_SplineDegree, double ctx_cfg_NGridLengthSpline, int ctx_Bl_ncoeff, unsigned long
        ctx_Bl_handle, const coder::array<CurvStruct, 2U> &CurvStructs, const double amax[3], double
        v_0, double at_0, double v_1, double at_1, coder::array<double, 2U> &BasisVal, coder::array<
        double, 2U> &BasisValD, const coder::array<double, 2U> &u_vec, coder_internal_sparse *A,
        coder::array<double, 1U> &b, coder::array<double, 2U> &Aeq, coder::array<double, 1U> &beq);
    static void CalcAlpha0(const double alpha1_data[], const int alpha1_size[1], const double in2[16],
                           double alpha0_s_data[], int alpha0_s_size[1]);
    static void CalcBspline_Lee(int cfg_SplineDegree, const coder::array<double, 2U> &points, coder::
        array<double, 2U> &sp3D_CoeffX, coder::array<double, 2U> &sp3D_CoeffY, coder::array<double,
        2U> &sp3D_CoeffZ, int *sp3D_Bl_ncoeff, coder::array<double, 2U> &sp3D_Bl_breakpoints,
        unsigned long *sp3D_Bl_handle, int *sp3D_Bl_degree, coder::array<double, 2U> &sp3D_knots);
    static void CalcFrenet(const double rD1[3], const double rD2[3], double t[3], double n[3],
                           double *kappa);
    static void CalcZeroStartConstraints(const queue_coder *ctx_q_splines, CurveType Curv_Type,
        const double Curv_P0[3], const double Curv_P1[3], const double Curv_evec[3], double
        Curv_theta, double Curv_pitch, const double Curv_CoeffP5[6][3], int Curv_sp_index, bool
        Curv_UseConstJerk, double Curv_ConstJerk, double Curv_a_param, double Curv_b_param, double
        JerkScale, double *v_0, double *at_0);
    static void Calc_beta0_beta1(double alpha0, double alpha1, const double in3[3], const double
        in4[3], const double in5[3], double kappa0, const double in7[3], const double in8[3], const
        double in9[3], double kappa1, double *beta0, double *beta1);
    static void CharPolyAlpha1(const double in1[16], double Coeff_Poly_Alpha1[10]);
    static void CheckCurvStructs(const FeedoptContext *ctx);
    static void CoefPolySys(const double in1[3], const double in2[3], const double in3[3], double
                            kappa0, const double in5[3], const double in6[3], const double in7[3],
                            double kappa1, double CoefPS[16]);
    static void CompressCurvStructs(const FeedoptContext *ctx);
    static void ConstrBSplineStruct(const coder::array<double, 2U> &pvec, double FeedRate,
        CurvStruct *b_CurvStruct);
    static void ConstrTransP5Struct(const double CoeffP5[6][3], double FeedRate, CurvStruct
        *b_CurvStruct);
    static void CutCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        CurvStruct *b_CurvStruct, double d1);
    static void CutZeroEnd(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int
                           ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3],
                           double ctx_cfg_dt, double ctx_cfg_ZeroStartAccLimit, double
                           ctx_cfg_ZeroStartJerkLimit, double ctx_cfg_ZeroStartVelLimit, double
                           ctx_cfg_NGridLengthSpline, const CurvStruct *b_CurvStruct, double k0,
                           CurvStruct *CurvStruct1, CurvStruct *CurvStruct2);
    static void CutZeroStart(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int
        ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3], double ctx_cfg_dt,
        double ctx_cfg_ZeroStartAccLimit, double ctx_cfg_ZeroStartJerkLimit, double
        ctx_cfg_ZeroStartVelLimit, bool ctx_cfg_DebugCutZero, double ctx_cfg_NGridLengthSpline,
        const CurvStruct *b_CurvStruct, double k0, CurvStruct *CurvStruct1, CurvStruct *CurvStruct2);
    static double EvalCostIntegral(double alpha0, double beta0, double alpha1, double beta1, const
        double in5[3], const double in6[3], const double in7[3], double kappa0, const double in9[3],
        const double in10[3], const double in11[3], double kappa1);
    static void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const double
                          CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
                          const coder::array<double, 2U> &u_vec, coder::array<double, 2U> &r0D,
                          coder::array<double, 2U> &r1D, coder::array<double, 2U> &r2D, coder::array<
                          double, 2U> &r3D);
    static void EvalTransP5(const double CurvStruct_CoeffP5[6][3], const coder::array<double, 2U>
                            &u_vec, coder::array<double, 2U> &r_0D, coder::array<double, 2U> &r_1D,
                            coder::array<double, 2U> &r_2D, coder::array<double, 2U> &r_3D);
    static void ExpandZeroStructs(const FeedoptContext *ctx);
    static void FeedratePlanning_v4(FeedoptContext *ctx, const coder::array<CurvStruct, 2U>
        &CurvStructs0, const double amax[3], double jmax[3], const coder::array<double, 2U>
        &BasisVal, const coder::array<double, 2U> &BasisValD, const coder::array<double, 2U>
        &BasisValDD, const coder::array<double, 1U> &BasisIntegr, unsigned long Bl_handle, const
        coder::array<double, 2U> &u_vec, int N_Hor, coder::array<double, 2U> &Coeff, int *NCoeff,
        bool *success);
    static void G2_Hermite_Interpolation(const double r0D0[3], const double r0D1[3], const double
        r0D2[3], const double r1D0[3], const double r1D1[3], const double r1D2[3], double p5_3D[6][3],
        int *status, double *alpha0, double *alpha1);
    static double GetCurvMaxFeedrate(const queue_coder *ctx_q_splines, const double ctx_cfg_amax[3],
        const double ctx_cfg_jmax[3], CurveType CurvStruct_Type, const double CurvStruct_P0[3],
        const double CurvStruct_P1[3], const double CurvStruct_evec[3], double CurvStruct_theta,
        double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index,
        double CurvStruct_FeedRate, double CurvStruct_a_param, double CurvStruct_b_param);
    static double LengthCurv(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        CurveType Curv_Type, const double Curv_P0[3], const double Curv_P1[3], const double
        Curv_evec[3], double Curv_theta, double Curv_pitch, const double Curv_CoeffP5[6][3], int
        Curv_sp_index, double Curv_a_param, double Curv_b_param);
    static void Resample(ZSpdMode CurOptStruct_zspdmode, bool CurOptStruct_UseConstJerk, double
                         CurOptStruct_ConstJerk, const coder::array<double, 1U> &CurOptStruct_Coeff,
                         unsigned long Bl_handle, double u, double dt, double *ukp1, double *qk,
                         double *dk);
    static void SmoothCurvStructs(const FeedoptContext *ctx);
    static double SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, double u0_tilda, double u1_tilda);
    static void SplitCurvStructs(const FeedoptContext *ctx);
    static void b_CalcTransition(const queue_coder *ctx_q_splines, double ctx_cfg_CutOff, double
        ctx_cfg_CollTolDeg, double ctx_cfg_NGridLengthSpline, const CurvStruct *CurvStruct1, const
        CurvStruct *CurvStruct2, CurvStruct *CurvStruct1_C, CurvStruct *CurvStruct_T, CurvStruct
        *CurvStruct2_C, TransitionResult *status);
    static void b_CutCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        CurvStruct *b_CurvStruct, double d0);
    static void b_CutZeroEnd(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int
        ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3], double ctx_cfg_dt,
        double ctx_cfg_ZeroStartAccLimit, double ctx_cfg_ZeroStartJerkLimit, double
        ctx_cfg_ZeroStartVelLimit, double ctx_cfg_NGridLengthSpline, const CurvStruct *b_CurvStruct,
        CurvStruct *CurvStruct1, CurvStruct *CurvStruct2);
    static void b_CutZeroStart(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int
        ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3], double ctx_cfg_dt,
        double ctx_cfg_ZeroStartAccLimit, double ctx_cfg_ZeroStartJerkLimit, double
        ctx_cfg_ZeroStartVelLimit, bool ctx_cfg_DebugCutZero, double ctx_cfg_NGridLengthSpline,
        const CurvStruct *b_CurvStruct, CurvStruct *CurvStruct1, CurvStruct *CurvStruct2);
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_b_param, double r0D[3]);
    static void b_EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const
                            double CurvStruct_evec[3], double CurvStruct_theta, double
                            CurvStruct_pitch, double u_vec, double r0D[3], double r1D[3], double
                            r2D[3], double r3D[3]);
    static void b_EvalTransP5(const double CurvStruct_CoeffP5[6][3], double u_vec, double r_0D[3],
        double r_1D[3], double r_2D[3], double r_3D[3]);
    static void b_PrintCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        CurveType S_Type, ZSpdMode S_zspdmode, const double S_P0[3], const double S_P1[3], const
        double S_evec[3], double S_theta, double S_pitch, const double S_CoeffP5[6][3], int
        S_sp_index, double S_FeedRate, bool S_UseConstJerk, double S_ConstJerk, double S_a_param,
        double S_b_param);
    static double b_SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, const double u0_tilda_data[], const int
        u0_tilda_size[2], double u1_tilda);
    static void b_bspline_create(int degree, const coder::array<double, 2U> &breakpoints, int
        *Bl_ncoeff, coder::array<double, 2U> &Bl_breakpoints, unsigned long *Bl_handle, int
        *Bl_degree);
    static void b_bspline_eval(unsigned long Bl_handle, const coder::array<double, 1U> &coeffs,
        double *x, double *xd, double *xdd);
    static void b_bspline_eval_vec(unsigned long Bl_handle, const coder::array<double, 2U> &coeffs,
        double u, double *x, double *xd, double *xdd, double *xddd);
    static void b_bsxfun(const coder::array<double, 1U> &a, const coder::array<double, 2U> &b, coder::
                         array<double, 2U> &c);
    static void b_cosd(double *x);
    static void b_eml_find(const coder::array<bool, 2U> &x, int i_data[], int i_size[2]);
    static void b_eml_float_colon(double a, double d, coder::array<double, 2U> &y);
    static void b_linspace(int n1, coder::array<double, 2U> &y);
    static double b_norm(const double x[3]);
    static void bspline_base_eval(int Bl_ncoeff, unsigned long Bl_handle, const coder::array<double,
        2U> &xvec, coder::array<double, 2U> &BasisVal, coder::array<double, 2U> &BasisValD);
    static void bspline_eval(unsigned long Bl_handle, const coder::array<double, 2U> &coeffs, double
        *x, double *xd, double *xdd, double *xddd);
    static void bspline_eval_vec(unsigned long Bl_handle, const coder::array<double, 2U> &coeffs,
        const coder::array<double, 2U> &u, coder::array<double, 2U> &x, coder::array<double, 2U> &xd,
        coder::array<double, 2U> &xdd, coder::array<double, 2U> &xddd);
    static void bsxfun(const coder::array<double, 2U> &a, const coder::array<double, 2U> &b, coder::
                       array<double, 2U> &c);
    static void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, double r0D[3]);
    static void c_EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const
                            double CurvStruct_evec[3], double CurvStruct_theta, double
                            CurvStruct_pitch, const double u_vec[10], double r0D[10][3], double r1D
                            [10][3], double r2D[10][3], double r3D[10][3]);
    static double c_SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, double u0_tilda, const double u1_tilda_data[],
        const int u1_tilda_size[2]);
    static void c_bspline_eval_vec(unsigned long Bl_handle, const coder::array<double, 2U> &coeffs,
        const coder::array<double, 2U> &u, coder::array<double, 2U> &x, coder::array<double, 2U> &xd);
    static void c_bsxfun(const coder::array<double, 2U> &a, const coder::array<double, 1U> &b, coder::
                         array<double, 2U> &c);
    static void c_eml_find(const bool x_data[], const int x_size[1], int i_data[], int i_size[1]);
    static void c_simplex(const coder::array<double, 2U> &f, const coder_internal_sparse *A, coder::
                          array<double, 2U> &b, const coder::array<double, 2U> &Aeq, const coder::
                          array<double, 2U> &beq, coder::array<double, 2U> &C, bool *success, int
                          *status);
    static bool collinear(const double u[3], const double v[3], double tol_angle_d);
    static void d_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, double r0D[3],
        double r1D[3], double r2D[3]);
    static void d_SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, double u0_tilda, double u1_tilda, double *L,
        coder::array<double, 2U> &Integrand, coder::array<double, 2U> &u_mid_tilda, coder::array<
        double, 2U> &du_tilda);
    static void d_bspline_eval_vec(unsigned long Bl_handle, const coder::array<double, 2U> &coeffs,
        const double u[10], double x[10], double xd[10], double xdd[10], double xddd[10]);
    static void diff(const coder::array<double, 2U> &x, coder::array<double, 2U> &y);
    static int div_s32_floor(int numerator, int denominator);
    static void e_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, double r0D[3],
        double r1D[3]);
    static void eml_find(const coder::array<bool, 2U> &x, int i_data[], int i_size[2]);
    static void eml_float_colon(double d, double b, coder::array<double, 2U> &y);
    static void f_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, double r0D[3],
        double r1D[3]);
    static void g_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, double r0D[3],
        double r1D[3], double r2D[3]);
    static void h_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, coder::array<
        double, 2U> &u_vec, coder::array<double, 2U> &r0D, coder::array<double, 2U> &r1D, coder::
        array<double, 2U> &r2D, coder::array<double, 2U> &r3D);
    static void i_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, double r0D[10][3],
        double r1D[10][3], double r2D[10][3], double r3D[10][3]);
    static void j_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, coder::array<
        double, 2U> &u_vec, coder::array<double, 2U> &r0D, coder::array<double, 2U> &r1D, coder::
        array<double, 2U> &r2D);
    static void minimum(const double x_data[], const int x_size[1], double *ex, int *idx);
    static void mldiv(const coder::array<double, 2U> &A, const coder::array<double, 1U> &B, coder::
                      array<double, 1U> &Y);
    static void mtimes(const double A[3], const coder::array<double, 2U> &B, coder::array<double, 2U>
                       &C);
    static void power(const coder::array<double, 2U> &a, coder::array<double, 2U> &y);
    static void qrpf(coder::array<double, 2U> &A, int m, int n, coder::array<double, 1U> &tau, coder::
                     array<int, 2U> &jpvt);
    static double rt_hypotd(double u0, double u1);
    static double rt_remd(double u0, double u1);
    static void sum(const coder::array<double, 2U> &x, coder::array<double, 2U> &y);
    static double xnrm2(int n, const coder::array<double, 2U> &x, int ix0);
}

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
namespace ocn
{
    void rtString::b_init()
    {
        this->Value.size[0] = 1;
        this->Value.size[1] = 2;
        this->Value.data[0] = 'Z';
        this->Value.data[1] = 'N';
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void ResampleStateClass::b_set_go_next()
    {
        this->go_next = true;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void rtString::c_init()
    {
        this->Value.size[0] = 1;
        this->Value.size[1] = 2;
        this->Value.data[0] = 'N';
        this->Value.data[1] = 'Z';
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void rtString::d_init()
    {
        this->Value.size[0] = 1;
        this->Value.size[1] = 2;
        this->Value.data[0] = 'Z';
        this->Value.data[1] = 'Z';
    }

    //
    // Arguments    : unsigned int b_index
    //                CurvStruct *value
    // Return Type  : void
    //
    void queue_coder::get(unsigned int b_index, CurvStruct *value) const
    {
        *value = this->value_type;

        // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
        c_queue_get(this->ptr, b_index, value);
    }

    //
    // Arguments    : double b_index
    //                CurvStruct *value
    // Return Type  : void
    //
    void queue_coder::get(double b_index, CurvStruct *value) const
    {
        *value = this->value_type;

        // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
        c_queue_get(this->ptr, static_cast<unsigned int>(std::round(b_index)), value);
    }

    //
    // Arguments    : long b_index
    //                CurvStruct *value
    // Return Type  : void
    //
    void queue_coder::get(long b_index, CurvStruct *value) const
    {
        *value = this->value_type;

        // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
        c_queue_get(this->ptr, static_cast<unsigned int>(b_index), value);
    }

    //
    // Arguments    : unsigned long b_index
    //                CurvStruct *value
    // Return Type  : void
    //
    void queue_coder::get(unsigned long b_index, CurvStruct *value) const
    {
        *value = this->value_type;

        // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
        c_queue_get(this->ptr, static_cast<unsigned int>(b_index), value);
    }

    //
    // Arguments    : int b_index
    //                CurvStruct *value
    // Return Type  : void
    //
    void queue_coder::get(int b_index, CurvStruct *value) const
    {
        *value = this->value_type;

        // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
        c_queue_get(this->ptr, static_cast<unsigned int>(b_index), value);
    }

    //
    // Arguments    : double b_dt
    // Return Type  : void
    //
    void ResampleStateClass::init(double b_dt)
    {
        this->set_u();
        this->set_go_next();
        this->set_dt(b_dt);
    }

    //
    // Arguments    : int b_m
    //                int b_n
    //                int nzmaxval
    // Return Type  : void
    //
    void coder_internal_sparse::init(int b_m, int b_n, int nzmaxval)
    {
        int numalloc;
        int i1;
        this->m = b_m;
        this->n = b_n;
        if (nzmaxval >= 1) {
            numalloc = nzmaxval;
        } else {
            numalloc = 1;
        }

        this->d.set_size(numalloc);
        this->maxnz = numalloc;
        this->colidx.set_size((b_n + 1));
        this->colidx[0] = 1;
        this->rowidx.set_size(numalloc);
        for (int i = 0; i < numalloc; i++) {
            this->d[i] = 0.0;
            this->rowidx[i] = 0;
        }

        for (int c = 0; c < b_n; c++) {
            this->colidx[c + 1] = 1;
        }

        i1 = this->colidx.size(0);
        for (int b_c = 0; b_c <= i1 - 2; b_c++) {
            this->colidx[b_c] = 1;
        }

        this->colidx[this->colidx.size(0) - 1] = 1;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void rtString::init()
    {
        this->Value.size[0] = 1;
        this->Value.size[1] = 2;
        this->Value.data[0] = 'N';
        this->Value.data[1] = 'N';
    }

    //
    // Arguments    : double ridx
    //                double cidx
    // Return Type  : void
    //
    void coder_internal_sparse::init(double ridx, double cidx)
    {
        int this_tmp;
        int loop_ub;
        this->m = static_cast<int>(ridx);
        this_tmp = static_cast<int>(cidx);
        this->n = this_tmp;
        this->d.set_size(1);
        this->d[0] = 0.0;
        loop_ub = this_tmp + 1;
        this->colidx.set_size(loop_ub);
        for (int i = 0; i < loop_ub; i++) {
            this->colidx[i] = 1;
        }

        this->rowidx.set_size(1);
        this->rowidx[0] = 1;
        this->maxnz = 1;
    }

    //
    // Arguments    : const CurvStruct *b_value_type
    // Return Type  : void
    //
    void queue_coder::init(const CurvStruct *b_value_type)
    {
        //              fprintf('queue_coder::ctor\n');
        this->value_type = *b_value_type;
        this->ptr = c_queue_new();
    }

    //
    // Arguments    : void
    // Return Type  : bool
    //
    bool queue_coder::isempty() const
    {
        return this->size() == 0U;
    }

    //
    // Arguments    : void
    // Return Type  : bool
    //
    bool coder_internal_sparse::isempty() const
    {
        bool p;
        if ((this->m == 0) || (this->n == 0)) {
            p = true;
        } else {
            p = false;
        }

        return p;
    }

    //
    // Arguments    : void
    // Return Type  : int
    //
    int coder_internal_sparse::nnzInt() const
    {
        return this->colidx[this->colidx.size(0) - 1] - 1;
    }

    //
    // Arguments    : const coder::array<double, 2U> &rhs
    //                const coder::array<double, 2U> &varargin_1
    //                const coder::array<double, 2U> &varargin_2
    // Return Type  : void
    //
    void coder_internal_sparse::parenAssign(const coder::array<double, 2U> &rhs, const coder::array<
        double, 2U> &varargin_1, const coder::array<double, 2U> &varargin_2)
    {
        this->parenAssign2D(rhs, varargin_1, varargin_2);
    }

    //
    // Arguments    : const coder::array<double, 2U> &rhs
    //                const coder::array<double, 2U> &r
    //                const coder::array<double, 2U> &c
    // Return Type  : void
    //
    void coder_internal_sparse::parenAssign2D(const coder::array<double, 2U> &rhs, const coder::
        array<double, 2U> &r, const coder::array<double, 2U> &c)
    {
        int sm;
        int sn;
        int rhsIter_idx;
        coder::array<int, 1U> rowidxt;
        coder::array<double, 1U> dt;
        sm = r.size(1);
        sn = c.size(1);
        rhsIter_idx = 0;
        for (int cidx = 0; cidx < sn; cidx++) {
            double b_d;
            b_d = c[cidx];
            for (int ridx = 0; ridx < sm; ridx++) {
                double nt;
                int i;
                int i1;
                int vidx;
                bool found;
                double thisv;
                double rhsv;
                nt = r[ridx];
                i = static_cast<int>(b_d);
                i1 = i - 1;
                if (this->colidx[i1] < this->colidx[i]) {
                    int i2;
                    int i3;
                    i2 = this->colidx[i1] - 1;
                    i3 = static_cast<int>(nt);
                    if (i3 < this->rowidx[i2]) {
                        vidx = i2;
                        found = false;
                    } else {
                        int high_i;
                        int low_i;
                        int low_ip1;
                        high_i = this->colidx[i];
                        low_i = this->colidx[i1];
                        low_ip1 = this->colidx[i1];
                        while (high_i > low_ip1 + 1) {
                            int mid_i;
                            mid_i = (low_i >> 1) + (high_i >> 1);
                            if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
                                mid_i++;
                            }

                            if (i3 >= this->rowidx[mid_i - 1]) {
                                low_i = mid_i;
                                low_ip1 = mid_i;
                            } else {
                                high_i = mid_i;
                            }
                        }

                        vidx = low_i;
                        found = (this->rowidx[low_i - 1] == i3);
                    }
                } else if (this->colidx[i1] == this->colidx[i]) {
                    vidx = this->colidx[i1] - 1;
                    found = false;
                } else {
                    vidx = 0;
                    found = false;
                }

                if (found) {
                    thisv = this->d[vidx - 1];
                } else {
                    thisv = 0.0;
                }

                rhsv = rhs[rhsIter_idx];
                rhsIter_idx++;
                if ((thisv != 0.0) || (rhsv != 0.0)) {
                    int n_tmp;
                    int nz;
                    n_tmp = this->nnzInt();
                    nz = n_tmp + 10;
                    if ((thisv != 0.0) && (rhsv != 0.0)) {
                        this->d[vidx - 1] = rhsv;
                    } else if (thisv == 0.0) {
                        int idx;
                        int i7;
                        int i9;
                        idx = vidx + 1;
                        if (n_tmp == this->maxnz) {
                            int loop_ub;
                            int b_loop_ub;
                            int highOrderA;
                            int highOrderB;
                            int lowOrderB;
                            int partialResults_idx_0_tmp;
                            int tmp;
                            int partialResults_idx_1;
                            int overflow;
                            int numAlloc;
                            rowidxt.set_size(this->rowidx.size(0));
                            loop_ub = this->rowidx.size(0);
                            for (int i6 = 0; i6 < loop_ub; i6++) {
                                rowidxt[i6] = this->rowidx[i6];
                            }

                            dt.set_size(this->d.size(0));
                            b_loop_ub = this->d.size(0);
                            for (int i8 = 0; i8 < b_loop_ub; i8++) {
                                dt[i8] = this->d[i8];
                            }

                            int lowOrderA;
                            highOrderA = this->m >> 16;
                            lowOrderA = this->m & 65535;
                            highOrderB = this->n >> 16;
                            lowOrderB = this->n & 65535;
                            partialResults_idx_0_tmp = lowOrderA * lowOrderB;
                            tmp = lowOrderA * highOrderB;
                            partialResults_idx_1 = tmp << 16;
                            overflow = tmp >> 16;
                            if (overflow <= 0) {
                                tmp = highOrderA * lowOrderB;
                                overflow = tmp >> 16;
                                if (overflow <= 0) {
                                    overflow = highOrderA * highOrderB;
                                    if (overflow <= 0) {
                                        int unusedU3;
                                        if (partialResults_idx_0_tmp > MAX_int32_T
                                                - partialResults_idx_1) {
                                            unusedU3 = (partialResults_idx_0_tmp +
                                                        partialResults_idx_1) - MAX_int32_T;
                                            overflow = 1;
                                        } else {
                                            unusedU3 = partialResults_idx_0_tmp +
                                                partialResults_idx_1;
                                        }

                                        if (unusedU3 > MAX_int32_T - (tmp << 16)) {
                                            overflow++;
                                        }
                                    }
                                }
                            }

                            if (overflow == 0) {
                                int y;
                                int b;
                                y = this->m * this->n;
                                if (nz <= y) {
                                    b = nz;
                                } else {
                                    b = y;
                                }

                                if (1 >= b) {
                                    numAlloc = 1;
                                } else {
                                    numAlloc = b;
                                }
                            } else if (1 >= nz) {
                                numAlloc = 1;
                            } else {
                                numAlloc = nz;
                            }

                            this->rowidx.set_size(numAlloc);
                            for (int i10 = 0; i10 < numAlloc; i10++) {
                                this->rowidx[i10] = 0;
                            }

                            this->d.set_size(numAlloc);
                            for (int i11 = 0; i11 < numAlloc; i11++) {
                                this->d[i11] = 0.0;
                            }

                            this->maxnz = numAlloc;
                            for (int c_k = 0; c_k < vidx; c_k++) {
                                this->rowidx[c_k] = rowidxt[c_k];
                                this->d[c_k] = dt[c_k];
                            }

                            for (int d_k = idx; d_k <= nz - 10; d_k++) {
                                this->rowidx[d_k] = rowidxt[d_k - 1];
                                this->d[d_k] = dt[d_k - 1];
                            }

                            this->rowidx[vidx] = static_cast<int>(nt);
                            this->d[vidx] = rhsv;
                        } else {
                            int b_nelem;
                            b_nelem = n_tmp - vidx;
                            if (b_nelem > 0) {
                                std::memmove((void *)&this->rowidx[vidx + 1], (void *)&this->
                                             rowidx[vidx], (unsigned int)((size_t)b_nelem * sizeof
                                              (int)));
                                std::memmove((void *)&this->d[vidx + 1], (void *)&this->d[vidx],
                                             (unsigned int)((size_t)b_nelem * sizeof(double)));
                            }

                            this->d[vidx] = rhsv;
                            this->rowidx[vidx] = static_cast<int>(nt);
                        }

                        i7 = static_cast<int>(b_d) + 1;
                        i9 = this->n + 1;
                        for (int b_k = i7; b_k <= i9; b_k++) {
                            this->colidx[b_k - 1] = this->colidx[b_k - 1] + 1;
                        }
                    } else {
                        int nelem;
                        int i4;
                        int i5;
                        nelem = n_tmp - vidx;
                        if (nelem > 0) {
                            std::memmove((void *)&this->rowidx[vidx - 1], (void *)&this->rowidx[vidx],
                                         (unsigned int)((size_t)nelem * sizeof(int)));
                            std::memmove((void *)&this->d[vidx - 1], (void *)&this->d[vidx],
                                         (unsigned int)((size_t)nelem * sizeof(double)));
                        }

                        i4 = i + 1;
                        i5 = this->n + 1;
                        for (int k = i4; k <= i5; k++) {
                            this->colidx[k - 1] = this->colidx[k - 1] - 1;
                        }
                    }
                }
            }
        }
    }

    //
    // Arguments    : const CurvStruct *value
    // Return Type  : void
    //
    void queue_coder::push(const CurvStruct *value) const
    {
        c_queue_push(this->ptr, *value);
    }

    //
    // Arguments    : CurvStruct *value
    // Return Type  : void
    //
    void queue_coder::rget(CurvStruct *value) const
    {
        this->size();
        this->get(this->size(), value);
    }

    //
    // Arguments    : unsigned int b_index
    //                const CurvStruct *value
    // Return Type  : void
    //
    void queue_coder::set(unsigned int b_index, const CurvStruct *value) const
    {
        c_queue_set(this->ptr, b_index, *value);
    }

    //
    // Arguments    : double val
    // Return Type  : void
    //
    void ResampleStateClass::set_dt(double val)
    {
        this->dt = val;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void ResampleStateClass::set_go_next()
    {
        this->go_next = false;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void ResampleStateClass::set_u()
    {
        this->u = 0.0;
    }

    //
    // Arguments    : double val
    // Return Type  : void
    //
    void ResampleStateClass::set_u(double val)
    {
        this->u = val;
    }

    //
    // Arguments    : void
    // Return Type  : unsigned int
    //
    unsigned int queue_coder::size() const
    {
        return c_queue_size(this->ptr);
    }

    //
    // Arguments    : int b_m
    //                int b_n
    //                int nzmax
    //                coder_internal_sparse *s
    // Return Type  : void
    //
    void coder_internal_sparse::spallocLike(int b_m, int b_n, int nzmax, coder_internal_sparse *s)
    {
        s->init(b_m, b_n, nzmax);
    }

    //
    // Arguments    : char result_data[]
    //                int result_size[2]
    // Return Type  : void
    //
    void rtString::uncheckedChar(char result_data[], int result_size[2]) const
    {
        int loop_ub;
        rtString localCopyOfThis;
        localCopyOfThis = *this;
        result_size[0] = 1;
        result_size[1] = localCopyOfThis.Value.size[1];
        loop_ub = localCopyOfThis.Value.size[1];
        if (0 <= loop_ub - 1) {
            std::memcpy(&result_data[0], &localCopyOfThis.Value.data[0], loop_ub * sizeof(char));
        }
    }

    //
    // Arguments    : const coder::array<double, 2U> &varargin_2
    //                coder_internal_sparse *c
    // Return Type  : void
    //
    void coder_internal_sparse::vertcat(const coder::array<double, 2U> &varargin_2,
        coder_internal_sparse *c) const
    {
        int cnfixeddim;
        bool isAcceptableEmpty_tmp_tmp;
        bool isAcceptableEmpty;
        bool allEmpty;
        int cnnz;
        int cnvardim;
        int nzCount;
        bool emptyflag_idx_1;
        int i1;
        cnfixeddim = this->n;
        isAcceptableEmpty_tmp_tmp = this->isempty();
        isAcceptableEmpty = (varargin_2.size(1) == 0);
        allEmpty = (isAcceptableEmpty_tmp_tmp && isAcceptableEmpty);
        if ((!isAcceptableEmpty) && isAcceptableEmpty_tmp_tmp) {
            cnfixeddim = varargin_2.size(1);
        }

        cnnz = 0;
        cnvardim = 0;
        if (allEmpty || (!isAcceptableEmpty_tmp_tmp)) {
            cnnz = this->nnzInt();
            cnvardim = this->m;
        }

        if (allEmpty || (varargin_2.size(1) != 0)) {
            int b_n;
            int i;
            b_n = 0;
            i = varargin_2.size(0) * varargin_2.size(1);
            for (int k = 0; k < i; k++) {
                if (varargin_2[k] != 0.0) {
                    b_n++;
                }
            }

            cnnz += b_n;
            cnvardim += varargin_2.size(0);
        }

        coder_internal_sparse::spallocLike((cnvardim), (cnfixeddim), (cnnz), (c));
        nzCount = -1;
        emptyflag_idx_1 = (varargin_2.size(1) == 0);
        i1 = c->n;
        for (int ccol = 0; ccol < i1; ccol++) {
            int crowoffs;
            int cidx;
            crowoffs = 1;
            if (!isAcceptableEmpty_tmp_tmp) {
                int kpstart;
                int kpend_tmp;
                int kpend;
                cidx = nzCount;
                kpstart = this->colidx[ccol];
                kpend_tmp = this->colidx[ccol + 1];
                kpend = kpend_tmp - 1;
                for (int kp = kpstart; kp <= kpend; kp++) {
                    cidx++;
                    c->rowidx[cidx] = this->rowidx[kp - 1];
                    c->d[cidx] = this->d[kp - 1];
                }

                nzCount = (nzCount + kpend_tmp) - this->colidx[ccol];
                crowoffs = this->m + 1;
            }

            if (!emptyflag_idx_1) {
                int nrowk;
                nrowk = varargin_2.size(0);
                cidx = nzCount;
                for (int row = 0; row < nrowk; row++) {
                    double dk;
                    dk = varargin_2[row + varargin_2.size(0) * ccol];
                    if (dk != 0.0) {
                        cidx++;
                        c->rowidx[cidx] = row + crowoffs;
                        c->d[cidx] = dk;
                    }
                }

                nzCount = cidx;
            }

            c->colidx[ccol + 1] = nzCount + 2;
        }
    }

    //
    // Arguments    : const coder_internal_sparse *varargin_2
    //                coder_internal_sparse *c
    // Return Type  : void
    //
    void coder_internal_sparse::vertcat(const coder_internal_sparse *varargin_2,
        coder_internal_sparse *c) const
    {
        int cnfixeddim;
        bool isAcceptableEmpty_tmp_tmp;
        bool b_isAcceptableEmpty_tmp_tmp;
        bool allEmpty;
        int cnnz;
        int cnvardim;
        int nzCount;
        int i;
        cnfixeddim = this->n;
        isAcceptableEmpty_tmp_tmp = this->isempty();
        b_isAcceptableEmpty_tmp_tmp = varargin_2->isempty();
        allEmpty = (isAcceptableEmpty_tmp_tmp && b_isAcceptableEmpty_tmp_tmp);
        if ((!b_isAcceptableEmpty_tmp_tmp) && isAcceptableEmpty_tmp_tmp) {
            cnfixeddim = varargin_2->n;
        }

        cnnz = 0;
        cnvardim = 0;
        if (allEmpty || (!isAcceptableEmpty_tmp_tmp)) {
            cnnz = this->nnzInt();
            cnvardim = this->m;
        }

        if (allEmpty || (!b_isAcceptableEmpty_tmp_tmp)) {
            cnnz += varargin_2->nnzInt();
            cnvardim += varargin_2->m;
        }

        coder_internal_sparse::spallocLike((cnvardim), (cnfixeddim), (cnnz), (c));
        nzCount = -1;
        i = c->n;
        for (int ccol = 0; ccol < i; ccol++) {
            int crowoffs;
            int cidx;
            int kpstart;
            int kpend;
            crowoffs = 0;
            if (!isAcceptableEmpty_tmp_tmp) {
                int kpend_tmp;
                cidx = nzCount;
                kpstart = this->colidx[ccol];
                kpend_tmp = this->colidx[ccol + 1];
                kpend = kpend_tmp - 1;
                for (int kp = kpstart; kp <= kpend; kp++) {
                    cidx++;
                    c->rowidx[cidx] = this->rowidx[kp - 1];
                    c->d[cidx] = this->d[kp - 1];
                }

                nzCount = (nzCount + kpend_tmp) - this->colidx[ccol];
                crowoffs = this->m;
            }

            if (!b_isAcceptableEmpty_tmp_tmp) {
                int b_kpend_tmp;
                cidx = nzCount;
                kpstart = varargin_2->colidx[ccol];
                b_kpend_tmp = varargin_2->colidx[ccol + 1];
                kpend = b_kpend_tmp - 1;
                for (int b_kp = kpstart; b_kp <= kpend; b_kp++) {
                    cidx++;
                    c->rowidx[cidx] = varargin_2->rowidx[b_kp - 1] + crowoffs;
                    c->d[cidx] = varargin_2->d[b_kp - 1];
                }

                nzCount = (nzCount + b_kpend_tmp) - varargin_2->colidx[ccol];
            }

            c->colidx[ccol + 1] = nzCount + 2;
        }
    }

    //
    // Arguments    : const queue_coder *ctx_q_splines
    //                const coder::array<CurvStruct, 2U> &CurvStructs
    //                const coder::array<double, 2U> &Coeff
    //                const double jmax[3]
    //                const coder::array<double, 2U> &BasisVal
    //                const coder::array<double, 2U> &BasisValD
    //                const coder::array<double, 2U> &BasisValDD
    //                const coder::array<double, 2U> &u_vec
    //                coder_internal_sparse *A
    //                coder::array<double, 1U> &b
    // Return Type  : void
    //
    static void BuildConstrJerk_v4(const queue_coder *ctx_q_splines, const coder::array<CurvStruct,
        2U> &CurvStructs, const coder::array<double, 2U> &Coeff, const double jmax[3], const coder::
        array<double, 2U> &BasisVal, const coder::array<double, 2U> &BasisValD, const coder::array<
        double, 2U> &BasisValDD, const coder::array<double, 2U> &u_vec, coder_internal_sparse *A,
        coder::array<double, 1U> &b)
    {
        int N;
        int M;
        int unnamed_idx_0;
        coder::array<double, 2U> b_u_vec;
        int loop_ub;
        coder::array<double, 2U> unusedU0;
        coder::array<double, 2U> r1D;
        coder::array<double, 2U> r2D;
        coder::array<double, 2U> r3D;
        int mc;
        int inner;
        coder::array<double, 1U> R1_tmp;
        int i2;
        int b_scalarLB;
        int b_vectorUB;
        int c_i;
        int b_k;
        int b_loop_ub;
        coder::array<double, 1U> b_r3D;
        coder::array<double, 2U> r2;
        int c_loop_ub;
        coder::array<double, 1U> b_r2D;
        coder::array<double, 2U> r3;
        int d_loop_ub;
        coder::array<double, 1U> b_r1D;
        coder::array<double, 2U> r4;
        int e_loop_ub;
        coder::array<double, 2U> R1;
        int g_loop_ub;
        int i8;
        int h_loop_ub;
        int i_loop_ub;
        int j_loop_ub;
        coder::array<double, 2U> R2;
        int l_loop_ub;
        int i13;
        int m_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        coder::array<double, 2U> R3;
        int i17;
        coder::array<double, 2U> varargin_2;
        int q_loop_ub;
        coder::array<double, 2U> varargin_4;
        int s_loop_ub;
        int i20;
        coder::array<double, 2U> varargin_6;
        int u_loop_ub;
        int i22;
        int result;
        bool empty_non_axis_sizes;
        int i23;
        int input_sizes_idx_0;
        int b_input_sizes_idx_0;
        int c_input_sizes_idx_0;
        int d_input_sizes_idx_0;
        int e_input_sizes_idx_0;
        int f_input_sizes_idx_0;
        double b_b;
        coder::array<double, 2U> y;
        coder::array<double, 2U> b_y;
        int g_input_sizes_idx_0;
        int i26;
        coder::array<double, 2U> b_R1;
        coder::array<double, 1U> bC2;
        int y_loop_ub;
        coder::array<double, 1U> bC3;
        int ab_loop_ub;
        coder::array<double, 1U> bC4;
        int bb_loop_ub;
        double d;
        coder::array<double, 1U> r17;
        int cb_loop_ub;
        int db_loop_ub;
        int eb_loop_ub;
        int fb_loop_ub;
        int gb_loop_ub;
        int hb_loop_ub;
        int ib_loop_ub;
        int i49;
        int b_mc;
        int b_inner;
        coder::array<double, 2U> c_u_vec;
        coder::array<double, 2U> unusedU1;
        int e_i;
        int e_k;
        int i57;
        int i62;
        int i66;
        int i69;
        int i71;
        int i72;

        //  import splines.*
        //
        N = BasisVal.size(1);
        M = BasisVal.size(0);

        //
        A->init((6.0 * static_cast<double>(BasisVal.size(0)) * static_cast<double>(CurvStructs.size
                  (1))), (static_cast<double>(BasisVal.size(1)) * static_cast<double>
                          (CurvStructs.size(1))));

        //  preallocation
        unnamed_idx_0 = static_cast<int>(6.0 * static_cast<double>(BasisVal.size(0)) * static_cast<
            double>(CurvStructs.size(1)));
        b.set_size(unnamed_idx_0);
        for (int i = 0; i < unnamed_idx_0; i++) {
            b[i] = 0.0;
        }

        //  preallocation
        //  coder.varsize('A', [6*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz, FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz], [1,1]); 
        //  coder.varsize('b', [6*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz, 1], [1,0]);
        //
        //  q_opt  = Function(Bl, Coeff(:, 1));
        //  q_val  = q_opt.fast_eval(u_vec);
        b_u_vec.set_size(1, u_vec.size(1));
        loop_ub = u_vec.size(1) - 1;
        for (int i1 = 0; i1 <= loop_ub; i1++) {
            b_u_vec[i1] = u_vec[i1];
        }

        h_EvalCurvStruct(ctx_q_splines, CurvStructs[0].Type, CurvStructs[0].P0, CurvStructs[0].P1,
                         CurvStructs[0].evec, CurvStructs[0].theta, CurvStructs[0].pitch,
                         CurvStructs[0].CoeffP5, CurvStructs[0].sp_index, CurvStructs[0].a_param,
                         CurvStructs[0].b_param, b_u_vec, unusedU0, r1D, r2D, r3D);

        //
        mc = BasisVal.size(0) - 1;
        inner = BasisVal.size(1);
        R1_tmp.set_size(BasisVal.size(0));
        for (int b_i = 0; b_i <= mc; b_i++) {
            R1_tmp[b_i] = 0.0;
        }

        for (int k = 0; k < inner; k++) {
            int scalarLB;
            int vectorUB;
            scalarLB = (mc + 1) & -4;
            vectorUB = scalarLB - 4;
            for (c_i = 0; c_i <= vectorUB; c_i += 4) {
                __m256d r;
                r = _mm256_loadu_pd(&R1_tmp[c_i]);
                _mm256_storeu_pd(&R1_tmp[c_i], _mm256_add_pd(r, _mm256_mul_pd(_mm256_loadu_pd
                                   (&BasisVal[c_i + BasisVal.size(0) * k]), _mm256_set1_pd(Coeff[k]))));
            }

            for (c_i = scalarLB; c_i <= mc; c_i++) {
                R1_tmp[c_i] = R1_tmp[c_i] + BasisVal[c_i + BasisVal.size(0) * k] * Coeff[k];
            }
        }

        i2 = R1_tmp.size(0);
        b_scalarLB = R1_tmp.size(0) & -4;
        b_vectorUB = b_scalarLB - 4;
        for (b_k = 0; b_k <= b_vectorUB; b_k += 4) {
            __m256d r1;
            r1 = _mm256_loadu_pd(&R1_tmp[b_k]);
            _mm256_storeu_pd(&R1_tmp[b_k], _mm256_sqrt_pd(r1));
        }

        for (b_k = b_scalarLB; b_k < i2; b_k++) {
            R1_tmp[b_k] = std::sqrt(R1_tmp[b_k]);
        }

        b_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i3 = 0; i3 < b_loop_ub; i3++) {
            b_r3D[i3] = r3D[3 * i3];
        }

        c_bsxfun(BasisVal, b_r3D, r2);
        c_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i4 = 0; i4 < c_loop_ub; i4++) {
            b_r2D[i4] = r2D[3 * i4];
        }

        c_bsxfun(BasisValD, b_r2D, r3);
        d_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i5 = 0; i5 < d_loop_ub; i5++) {
            b_r1D[i5] = r1D[3 * i5];
        }

        c_bsxfun(BasisValDD, b_r1D, r4);
        e_loop_ub = r2.size(1);
        for (int i6 = 0; i6 < e_loop_ub; i6++) {
            int f_loop_ub;
            int c_scalarLB;
            int c_vectorUB;
            f_loop_ub = r2.size(0);
            c_scalarLB = r2.size(0) & -4;
            c_vectorUB = c_scalarLB - 4;
            for (i8 = 0; i8 <= c_vectorUB; i8 += 4) {
                __m256d r5;
                __m256d r6;
                __m256d r7;
                r5 = _mm256_loadu_pd(&r3[i8 + r3.size(0) * i6]);
                r6 = _mm256_loadu_pd(&r2[i8 + r2.size(0) * i6]);
                r7 = _mm256_loadu_pd(&r4[i8 + r4.size(0) * i6]);
                _mm256_storeu_pd(&r2[i8 + r2.size(0) * i6], _mm256_add_pd(_mm256_add_pd(r6,
                                   _mm256_mul_pd(_mm256_set1_pd(1.5), r5)), _mm256_mul_pd
                                  (_mm256_set1_pd(0.5), r7)));
            }

            for (i8 = c_scalarLB; i8 < f_loop_ub; i8++) {
                r2[i8 + r2.size(0) * i6] = (r2[i8 + r2.size(0) * i6] + 1.5 * r3[i8 + r3.size(0) * i6])
                    + 0.5 * r4[i8 + r4.size(0) * i6];
            }
        }

        c_bsxfun(r2, R1_tmp, R1);
        g_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i7 = 0; i7 < g_loop_ub; i7++) {
            b_r3D[i7] = r3D[3 * i7 + 1];
        }

        c_bsxfun(BasisVal, b_r3D, r2);
        h_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i9 = 0; i9 < h_loop_ub; i9++) {
            b_r2D[i9] = r2D[3 * i9 + 1];
        }

        c_bsxfun(BasisValD, b_r2D, r3);
        i_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i10 = 0; i10 < i_loop_ub; i10++) {
            b_r1D[i10] = r1D[3 * i10 + 1];
        }

        c_bsxfun(BasisValDD, b_r1D, r4);
        j_loop_ub = r2.size(1);
        for (int i11 = 0; i11 < j_loop_ub; i11++) {
            int k_loop_ub;
            int d_scalarLB;
            int d_vectorUB;
            k_loop_ub = r2.size(0);
            d_scalarLB = r2.size(0) & -4;
            d_vectorUB = d_scalarLB - 4;
            for (i13 = 0; i13 <= d_vectorUB; i13 += 4) {
                __m256d r8;
                __m256d r9;
                __m256d r10;
                r8 = _mm256_loadu_pd(&r3[i13 + r3.size(0) * i11]);
                r9 = _mm256_loadu_pd(&r2[i13 + r2.size(0) * i11]);
                r10 = _mm256_loadu_pd(&r4[i13 + r4.size(0) * i11]);
                _mm256_storeu_pd(&r2[i13 + r2.size(0) * i11], _mm256_add_pd(_mm256_add_pd(r9,
                                   _mm256_mul_pd(_mm256_set1_pd(1.5), r8)), _mm256_mul_pd
                                  (_mm256_set1_pd(0.5), r10)));
            }

            for (i13 = d_scalarLB; i13 < k_loop_ub; i13++) {
                r2[i13 + r2.size(0) * i11] = (r2[i13 + r2.size(0) * i11] + 1.5 * r3[i13 + r3.size(0)
                    * i11]) + 0.5 * r4[i13 + r4.size(0) * i11];
            }
        }

        c_bsxfun(r2, R1_tmp, R2);
        l_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i12 = 0; i12 < l_loop_ub; i12++) {
            b_r3D[i12] = r3D[3 * i12 + 2];
        }

        c_bsxfun(BasisVal, b_r3D, r2);
        m_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i14 = 0; i14 < m_loop_ub; i14++) {
            b_r2D[i14] = r2D[3 * i14 + 2];
        }

        c_bsxfun(BasisValD, b_r2D, r3);
        n_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i15 = 0; i15 < n_loop_ub; i15++) {
            b_r1D[i15] = r1D[3 * i15 + 2];
        }

        c_bsxfun(BasisValDD, b_r1D, r4);
        o_loop_ub = r2.size(1);
        for (int i16 = 0; i16 < o_loop_ub; i16++) {
            int p_loop_ub;
            int e_scalarLB;
            int e_vectorUB;
            p_loop_ub = r2.size(0);
            e_scalarLB = r2.size(0) & -4;
            e_vectorUB = e_scalarLB - 4;
            for (i17 = 0; i17 <= e_vectorUB; i17 += 4) {
                __m256d r11;
                __m256d r12;
                __m256d r13;
                r11 = _mm256_loadu_pd(&r3[i17 + r3.size(0) * i16]);
                r12 = _mm256_loadu_pd(&r2[i17 + r2.size(0) * i16]);
                r13 = _mm256_loadu_pd(&r4[i17 + r4.size(0) * i16]);
                _mm256_storeu_pd(&r2[i17 + r2.size(0) * i16], _mm256_add_pd(_mm256_add_pd(r12,
                                   _mm256_mul_pd(_mm256_set1_pd(1.5), r11)), _mm256_mul_pd
                                  (_mm256_set1_pd(0.5), r13)));
            }

            for (i17 = e_scalarLB; i17 < p_loop_ub; i17++) {
                r2[i17 + r2.size(0) * i16] = (r2[i17 + r2.size(0) * i16] + 1.5 * r3[i17 + r3.size(0)
                    * i16]) + 0.5 * r4[i17 + r4.size(0) * i16];
            }
        }

        c_bsxfun(r2, R1_tmp, R3);

        //  R2 = (BasisVal .* r3D(2, :)' + ...
        //        1.5*BasisValD .* r2D(2, :)' + ...
        //        0.5*BasisValDD.*r1D(2, :)') .* sqrt(q_val);
        //  R3 = (BasisVal .* r3D(3, :)' + ...
        //        1.5*BasisValD .* r2D(3, :)' + ...
        //        0.5*BasisValDD.*r1D(3, :)') .* sqrt(q_val);
        //
        varargin_2.set_size(R1.size(0), R1.size(1));
        q_loop_ub = R1.size(1);
        for (int i18 = 0; i18 < q_loop_ub; i18++) {
            int r_loop_ub;
            int f_scalarLB;
            int f_vectorUB;
            r_loop_ub = R1.size(0);
            f_scalarLB = R1.size(0) & -4;
            f_vectorUB = f_scalarLB - 4;
            for (i20 = 0; i20 <= f_vectorUB; i20 += 4) {
                __m256d r14;
                r14 = _mm256_loadu_pd(&R1[i20 + R1.size(0) * i18]);
                _mm256_storeu_pd(&varargin_2[i20 + varargin_2.size(0) * i18], _mm256_mul_pd(r14,
                                  _mm256_set1_pd(-1.0)));
            }

            for (i20 = f_scalarLB; i20 < r_loop_ub; i20++) {
                varargin_2[i20 + varargin_2.size(0) * i18] = -R1[i20 + R1.size(0) * i18];
            }
        }

        varargin_4.set_size(R2.size(0), R2.size(1));
        s_loop_ub = R2.size(1);
        for (int i19 = 0; i19 < s_loop_ub; i19++) {
            int t_loop_ub;
            int g_scalarLB;
            int g_vectorUB;
            t_loop_ub = R2.size(0);
            g_scalarLB = R2.size(0) & -4;
            g_vectorUB = g_scalarLB - 4;
            for (i22 = 0; i22 <= g_vectorUB; i22 += 4) {
                __m256d r15;
                r15 = _mm256_loadu_pd(&R2[i22 + R2.size(0) * i19]);
                _mm256_storeu_pd(&varargin_4[i22 + varargin_4.size(0) * i19], _mm256_mul_pd(r15,
                                  _mm256_set1_pd(-1.0)));
            }

            for (i22 = g_scalarLB; i22 < t_loop_ub; i22++) {
                varargin_4[i22 + varargin_4.size(0) * i19] = -R2[i22 + R2.size(0) * i19];
            }
        }

        varargin_6.set_size(R3.size(0), R3.size(1));
        u_loop_ub = R3.size(1);
        for (int i21 = 0; i21 < u_loop_ub; i21++) {
            int v_loop_ub;
            int h_scalarLB;
            int h_vectorUB;
            v_loop_ub = R3.size(0);
            h_scalarLB = R3.size(0) & -4;
            h_vectorUB = h_scalarLB - 4;
            for (i23 = 0; i23 <= h_vectorUB; i23 += 4) {
                __m256d r16;
                r16 = _mm256_loadu_pd(&R3[i23 + R3.size(0) * i21]);
                _mm256_storeu_pd(&varargin_6[i23 + varargin_6.size(0) * i21], _mm256_mul_pd(r16,
                                  _mm256_set1_pd(-1.0)));
            }

            for (i23 = h_scalarLB; i23 < v_loop_ub; i23++) {
                varargin_6[i23 + varargin_6.size(0) * i21] = -R3[i23 + R3.size(0) * i21];
            }
        }

        if ((R1.size(0) != 0) && (R1.size(1) != 0)) {
            result = R1.size(1);
        } else if ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0)) {
            result = varargin_2.size(1);
        } else if ((R2.size(0) != 0) && (R2.size(1) != 0)) {
            result = R2.size(1);
        } else if ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0)) {
            result = varargin_4.size(1);
        } else if ((R3.size(0) != 0) && (R3.size(1) != 0)) {
            result = R3.size(1);
        } else if ((varargin_6.size(0) != 0) && (varargin_6.size(1) != 0)) {
            result = varargin_6.size(1);
        } else {
            int u0;
            u0 = R1.size(1);
            if (u0 > 0) {
                result = u0;
            } else {
                result = 0;
            }

            if (varargin_2.size(1) > result) {
                result = varargin_2.size(1);
            }

            if (R2.size(1) > result) {
                result = R2.size(1);
            }

            if (varargin_4.size(1) > result) {
                result = varargin_4.size(1);
            }

            if (R3.size(1) > result) {
                result = R3.size(1);
            }

            if (varargin_6.size(1) > result) {
                result = varargin_6.size(1);
            }
        }

        empty_non_axis_sizes = (result == 0);
        if (empty_non_axis_sizes || ((R1.size(0) != 0) && (R1.size(1) != 0))) {
            input_sizes_idx_0 = R1.size(0);
        } else {
            input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0))) {
            b_input_sizes_idx_0 = varargin_2.size(0);
        } else {
            b_input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || ((R2.size(0) != 0) && (R2.size(1) != 0))) {
            c_input_sizes_idx_0 = R2.size(0);
        } else {
            c_input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0))) {
            d_input_sizes_idx_0 = varargin_4.size(0);
        } else {
            d_input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || ((R3.size(0) != 0) && (R3.size(1) != 0))) {
            e_input_sizes_idx_0 = R3.size(0);
        } else {
            e_input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || ((varargin_6.size(0) != 0) && (varargin_6.size(1) != 0))) {
            f_input_sizes_idx_0 = varargin_6.size(0);
        } else {
            f_input_sizes_idx_0 = 0;
        }

        b_b = 6.0 * static_cast<double>(BasisVal.size(0));
        if (b_b < 1.0) {
            y.set_size(1, 0);
        } else {
            int w_loop_ub;
            w_loop_ub = static_cast<int>(b_b - 1.0);
            y.set_size(1, (w_loop_ub + 1));
            for (int i24 = 0; i24 <= w_loop_ub; i24++) {
                y[i24] = static_cast<double>(i24) + 1.0;
            }
        }

        if (BasisVal.size(1) < 1) {
            b_y.set_size(1, 0);
        } else {
            int x_loop_ub;
            b_y.set_size(1, BasisVal.size(1));
            x_loop_ub = BasisVal.size(1) - 1;
            for (int i25 = 0; i25 <= x_loop_ub; i25++) {
                b_y[i25] = static_cast<double>(i25) + 1.0;
            }
        }

        g_input_sizes_idx_0 = input_sizes_idx_0;
        input_sizes_idx_0 = b_input_sizes_idx_0;
        b_input_sizes_idx_0 = c_input_sizes_idx_0;
        c_input_sizes_idx_0 = d_input_sizes_idx_0;
        i26 = g_input_sizes_idx_0 + input_sizes_idx_0;
        b_R1.set_size(((((i26 + b_input_sizes_idx_0) + c_input_sizes_idx_0) + e_input_sizes_idx_0) +
                       f_input_sizes_idx_0), result);
        for (int i27 = 0; i27 < result; i27++) {
            for (int i29 = 0; i29 < g_input_sizes_idx_0; i29++) {
                b_R1[i29 + b_R1.size(0) * i27] = R1[i29 + g_input_sizes_idx_0 * i27];
            }
        }

        for (int i28 = 0; i28 < result; i28++) {
            for (int i31 = 0; i31 < input_sizes_idx_0; i31++) {
                b_R1[(i31 + g_input_sizes_idx_0) + b_R1.size(0) * i28] = varargin_2[i31 +
                    input_sizes_idx_0 * i28];
            }
        }

        for (int i30 = 0; i30 < result; i30++) {
            for (int i33 = 0; i33 < b_input_sizes_idx_0; i33++) {
                b_R1[((i33 + g_input_sizes_idx_0) + input_sizes_idx_0) + b_R1.size(0) * i30] =
                    R2[i33 + b_input_sizes_idx_0 * i30];
            }
        }

        for (int i32 = 0; i32 < result; i32++) {
            for (int i35 = 0; i35 < c_input_sizes_idx_0; i35++) {
                b_R1[(((i35 + g_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                    b_R1.size(0) * i32] = varargin_4[i35 + c_input_sizes_idx_0 * i32];
            }
        }

        for (int i34 = 0; i34 < result; i34++) {
            for (int i37 = 0; i37 < e_input_sizes_idx_0; i37++) {
                b_R1[((((i37 + g_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0) +
                      c_input_sizes_idx_0) + b_R1.size(0) * i34] = R3[i37 + e_input_sizes_idx_0 *
                    i34];
            }
        }

        for (int i36 = 0; i36 < result; i36++) {
            for (int i38 = 0; i38 < f_input_sizes_idx_0; i38++) {
                b_R1[((((i38 + i26) + b_input_sizes_idx_0) + c_input_sizes_idx_0) +
                      e_input_sizes_idx_0) + b_R1.size(0) * i36] = varargin_6[i38 +
                    f_input_sizes_idx_0 * i36];
            }
        }

        A->parenAssign(b_R1, y, b_y);

        //
        bC2.set_size(BasisVal.size(0));
        y_loop_ub = BasisVal.size(0);
        for (int i39 = 0; i39 < y_loop_ub; i39++) {
            bC2[i39] = jmax[0];
        }

        bC3.set_size(BasisVal.size(0));
        ab_loop_ub = BasisVal.size(0);
        for (int i40 = 0; i40 < ab_loop_ub; i40++) {
            bC3[i40] = jmax[1];
        }

        bC4.set_size(BasisVal.size(0));
        bb_loop_ub = BasisVal.size(0);
        for (int i41 = 0; i41 < bb_loop_ub; i41++) {
            bC4[i41] = jmax[2];
        }

        //
        d = 6.0 * static_cast<double>(BasisVal.size(0));
        r17.set_size((((((bC2.size(0) + bC2.size(0)) + bC3.size(0)) + bC3.size(0)) + bC4.size(0)) +
                      bC4.size(0)));
        cb_loop_ub = bC2.size(0);
        for (int i42 = 0; i42 < cb_loop_ub; i42++) {
            r17[i42] = bC2[i42];
        }

        db_loop_ub = bC2.size(0);
        for (int i43 = 0; i43 < db_loop_ub; i43++) {
            r17[i43 + bC2.size(0)] = bC2[i43];
        }

        eb_loop_ub = bC3.size(0);
        for (int i44 = 0; i44 < eb_loop_ub; i44++) {
            r17[(i44 + bC2.size(0)) + bC2.size(0)] = bC3[i44];
        }

        fb_loop_ub = bC3.size(0);
        for (int i45 = 0; i45 < fb_loop_ub; i45++) {
            r17[((i45 + bC2.size(0)) + bC2.size(0)) + bC3.size(0)] = bC3[i45];
        }

        gb_loop_ub = bC4.size(0);
        for (int i46 = 0; i46 < gb_loop_ub; i46++) {
            r17[(((i46 + bC2.size(0)) + bC2.size(0)) + bC3.size(0)) + bC3.size(0)] = bC4[i46];
        }

        hb_loop_ub = bC4.size(0);
        for (int i47 = 0; i47 < hb_loop_ub; i47++) {
            r17[((((i47 + bC2.size(0)) + bC2.size(0)) + bC3.size(0)) + bC3.size(0)) + bC4.size(0)] =
                bC4[i47];
        }

        if (1.0 > d) {
            ib_loop_ub = 0;
        } else {
            ib_loop_ub = static_cast<int>(d);
        }

        for (int i48 = 0; i48 < ib_loop_ub; i48++) {
            b[i48] = r17[i48];
        }

        //
        i49 = CurvStructs.size(1);
        if (0 <= CurvStructs.size(1) - 2) {
            b_mc = BasisVal.size(0) - 1;
            b_inner = BasisVal.size(1);
        }

        for (int c_k = 0; c_k <= i49 - 2; c_k++) {
            int jb_loop_ub;
            int i51;
            int j_scalarLB;
            int j_vectorUB;
            int kb_loop_ub;
            int lb_loop_ub;
            int mb_loop_ub;
            int nb_loop_ub;
            int pb_loop_ub;
            int qb_loop_ub;
            int rb_loop_ub;
            int sb_loop_ub;
            int ub_loop_ub;
            int vb_loop_ub;
            int wb_loop_ub;
            int xb_loop_ub;
            int ac_loop_ub;
            int cc_loop_ub;
            int ec_loop_ub;
            int b_result;
            bool b_empty_non_axis_sizes;
            int h_input_sizes_idx_0;
            int i_input_sizes_idx_0;
            int j_input_sizes_idx_0;
            int k_input_sizes_idx_0;
            int l_input_sizes_idx_0;
            int m_input_sizes_idx_0;
            double a_tmp;
            double b_tmp;
            double a;
            double c_b;
            int i87;
            int i88;
            int ic_loop_ub;
            c_u_vec.set_size(1, u_vec.size(1));
            jb_loop_ub = u_vec.size(1) - 1;
            for (int i50 = 0; i50 <= jb_loop_ub; i50++) {
                c_u_vec[i50] = u_vec[i50];
            }

            h_EvalCurvStruct(ctx_q_splines, CurvStructs[c_k + 1].Type, CurvStructs[c_k + 1].P0,
                             CurvStructs[c_k + 1].P1, CurvStructs[c_k + 1].evec, CurvStructs[c_k + 1]
                             .theta, CurvStructs[c_k + 1].pitch, CurvStructs[c_k + 1].CoeffP5,
                             CurvStructs[c_k + 1].sp_index, CurvStructs[c_k + 1].a_param,
                             CurvStructs[c_k + 1].b_param, c_u_vec, unusedU1, r1D, r2D, r3D);

            //
            //      q_opt  = Function(Bl, Coeff(:, k+1));
            //      q_val  = q_opt.fast_eval(u_vec);
            //
            R1_tmp.set_size(BasisVal.size(0));
            for (int d_i = 0; d_i <= b_mc; d_i++) {
                R1_tmp[d_i] = 0.0;
            }

            for (int d_k = 0; d_k < b_inner; d_k++) {
                int i_scalarLB;
                int i_vectorUB;
                i_scalarLB = (b_mc + 1) & -4;
                i_vectorUB = i_scalarLB - 4;
                for (e_i = 0; e_i <= i_vectorUB; e_i += 4) {
                    __m256d r18;
                    r18 = _mm256_loadu_pd(&R1_tmp[e_i]);
                    _mm256_storeu_pd(&R1_tmp[e_i], _mm256_add_pd(r18, _mm256_mul_pd(_mm256_loadu_pd(
                                        &BasisVal[e_i + BasisVal.size(0) * d_k]), _mm256_set1_pd
                                       (Coeff[d_k + Coeff.size(0) * (c_k + 1)]))));
                }

                for (e_i = i_scalarLB; e_i <= b_mc; e_i++) {
                    R1_tmp[e_i] = R1_tmp[e_i] + BasisVal[e_i + BasisVal.size(0) * d_k] * Coeff[d_k +
                        Coeff.size(0) * (c_k + 1)];
                }
            }

            i51 = R1_tmp.size(0);
            j_scalarLB = R1_tmp.size(0) & -4;
            j_vectorUB = j_scalarLB - 4;
            for (e_k = 0; e_k <= j_vectorUB; e_k += 4) {
                __m256d r19;
                r19 = _mm256_loadu_pd(&R1_tmp[e_k]);
                _mm256_storeu_pd(&R1_tmp[e_k], _mm256_sqrt_pd(r19));
            }

            for (e_k = j_scalarLB; e_k < i51; e_k++) {
                R1_tmp[e_k] = std::sqrt(R1_tmp[e_k]);
            }

            kb_loop_ub = r3D.size(1);
            b_r3D.set_size(r3D.size(1));
            for (int i52 = 0; i52 < kb_loop_ub; i52++) {
                b_r3D[i52] = r3D[3 * i52];
            }

            c_bsxfun(BasisVal, b_r3D, r2);
            lb_loop_ub = r2D.size(1);
            b_r2D.set_size(r2D.size(1));
            for (int i53 = 0; i53 < lb_loop_ub; i53++) {
                b_r2D[i53] = r2D[3 * i53];
            }

            c_bsxfun(BasisValD, b_r2D, r3);
            mb_loop_ub = r1D.size(1);
            b_r1D.set_size(r1D.size(1));
            for (int i54 = 0; i54 < mb_loop_ub; i54++) {
                b_r1D[i54] = r1D[3 * i54];
            }

            c_bsxfun(BasisValDD, b_r1D, r4);
            nb_loop_ub = r2.size(1);
            for (int i55 = 0; i55 < nb_loop_ub; i55++) {
                int ob_loop_ub;
                int k_scalarLB;
                int k_vectorUB;
                ob_loop_ub = r2.size(0);
                k_scalarLB = r2.size(0) & -4;
                k_vectorUB = k_scalarLB - 4;
                for (i57 = 0; i57 <= k_vectorUB; i57 += 4) {
                    __m256d r20;
                    __m256d r21;
                    __m256d r22;
                    r20 = _mm256_loadu_pd(&r3[i57 + r3.size(0) * i55]);
                    r21 = _mm256_loadu_pd(&r2[i57 + r2.size(0) * i55]);
                    r22 = _mm256_loadu_pd(&r4[i57 + r4.size(0) * i55]);
                    _mm256_storeu_pd(&r2[i57 + r2.size(0) * i55], _mm256_add_pd(_mm256_add_pd(r21,
                                       _mm256_mul_pd(_mm256_set1_pd(1.5), r20)), _mm256_mul_pd
                                      (_mm256_set1_pd(0.5), r22)));
                }

                for (i57 = k_scalarLB; i57 < ob_loop_ub; i57++) {
                    r2[i57 + r2.size(0) * i55] = (r2[i57 + r2.size(0) * i55] + 1.5 * r3[i57 +
                        r3.size(0) * i55]) + 0.5 * r4[i57 + r4.size(0) * i55];
                }
            }

            c_bsxfun(r2, R1_tmp, R1);
            pb_loop_ub = r3D.size(1);
            b_r3D.set_size(r3D.size(1));
            for (int i56 = 0; i56 < pb_loop_ub; i56++) {
                b_r3D[i56] = r3D[3 * i56 + 1];
            }

            c_bsxfun(BasisVal, b_r3D, r2);
            qb_loop_ub = r2D.size(1);
            b_r2D.set_size(r2D.size(1));
            for (int i58 = 0; i58 < qb_loop_ub; i58++) {
                b_r2D[i58] = r2D[3 * i58 + 1];
            }

            c_bsxfun(BasisValD, b_r2D, r3);
            rb_loop_ub = r1D.size(1);
            b_r1D.set_size(r1D.size(1));
            for (int i59 = 0; i59 < rb_loop_ub; i59++) {
                b_r1D[i59] = r1D[3 * i59 + 1];
            }

            c_bsxfun(BasisValDD, b_r1D, r4);
            sb_loop_ub = r2.size(1);
            for (int i60 = 0; i60 < sb_loop_ub; i60++) {
                int tb_loop_ub;
                int l_scalarLB;
                int l_vectorUB;
                tb_loop_ub = r2.size(0);
                l_scalarLB = r2.size(0) & -4;
                l_vectorUB = l_scalarLB - 4;
                for (i62 = 0; i62 <= l_vectorUB; i62 += 4) {
                    __m256d r23;
                    __m256d r24;
                    __m256d r25;
                    r23 = _mm256_loadu_pd(&r3[i62 + r3.size(0) * i60]);
                    r24 = _mm256_loadu_pd(&r2[i62 + r2.size(0) * i60]);
                    r25 = _mm256_loadu_pd(&r4[i62 + r4.size(0) * i60]);
                    _mm256_storeu_pd(&r2[i62 + r2.size(0) * i60], _mm256_add_pd(_mm256_add_pd(r24,
                                       _mm256_mul_pd(_mm256_set1_pd(1.5), r23)), _mm256_mul_pd
                                      (_mm256_set1_pd(0.5), r25)));
                }

                for (i62 = l_scalarLB; i62 < tb_loop_ub; i62++) {
                    r2[i62 + r2.size(0) * i60] = (r2[i62 + r2.size(0) * i60] + 1.5 * r3[i62 +
                        r3.size(0) * i60]) + 0.5 * r4[i62 + r4.size(0) * i60];
                }
            }

            c_bsxfun(r2, R1_tmp, R2);
            ub_loop_ub = r3D.size(1);
            b_r3D.set_size(r3D.size(1));
            for (int i61 = 0; i61 < ub_loop_ub; i61++) {
                b_r3D[i61] = r3D[3 * i61 + 2];
            }

            c_bsxfun(BasisVal, b_r3D, r2);
            vb_loop_ub = r2D.size(1);
            b_r2D.set_size(r2D.size(1));
            for (int i63 = 0; i63 < vb_loop_ub; i63++) {
                b_r2D[i63] = r2D[3 * i63 + 2];
            }

            c_bsxfun(BasisValD, b_r2D, r3);
            wb_loop_ub = r1D.size(1);
            b_r1D.set_size(r1D.size(1));
            for (int i64 = 0; i64 < wb_loop_ub; i64++) {
                b_r1D[i64] = r1D[3 * i64 + 2];
            }

            c_bsxfun(BasisValDD, b_r1D, r4);
            xb_loop_ub = r2.size(1);
            for (int i65 = 0; i65 < xb_loop_ub; i65++) {
                int yb_loop_ub;
                int m_scalarLB;
                int m_vectorUB;
                yb_loop_ub = r2.size(0);
                m_scalarLB = r2.size(0) & -4;
                m_vectorUB = m_scalarLB - 4;
                for (i66 = 0; i66 <= m_vectorUB; i66 += 4) {
                    __m256d r26;
                    __m256d r27;
                    __m256d r28;
                    r26 = _mm256_loadu_pd(&r3[i66 + r3.size(0) * i65]);
                    r27 = _mm256_loadu_pd(&r2[i66 + r2.size(0) * i65]);
                    r28 = _mm256_loadu_pd(&r4[i66 + r4.size(0) * i65]);
                    _mm256_storeu_pd(&r2[i66 + r2.size(0) * i65], _mm256_add_pd(_mm256_add_pd(r27,
                                       _mm256_mul_pd(_mm256_set1_pd(1.5), r26)), _mm256_mul_pd
                                      (_mm256_set1_pd(0.5), r28)));
                }

                for (i66 = m_scalarLB; i66 < yb_loop_ub; i66++) {
                    r2[i66 + r2.size(0) * i65] = (r2[i66 + r2.size(0) * i65] + 1.5 * r3[i66 +
                        r3.size(0) * i65]) + 0.5 * r4[i66 + r4.size(0) * i65];
                }
            }

            c_bsxfun(r2, R1_tmp, R3);

            //      R2 = (BasisVal .* r3D(2, :)' + ...
            //            1.5*BasisValD .* r2D(2, :)' + ...
            //            0.5*BasisValDD.*r1D(2, :)') .* sqrt(q_val);
            //      R3 = (BasisVal .* r3D(3, :)' + ...
            //            1.5*BasisValD .* r2D(3, :)' + ...
            //            0.5*BasisValDD.*r1D(3, :)') .* sqrt(q_val);
            //
            varargin_2.set_size(R1.size(0), R1.size(1));
            ac_loop_ub = R1.size(1);
            for (int i67 = 0; i67 < ac_loop_ub; i67++) {
                int bc_loop_ub;
                int n_scalarLB;
                int n_vectorUB;
                bc_loop_ub = R1.size(0);
                n_scalarLB = R1.size(0) & -4;
                n_vectorUB = n_scalarLB - 4;
                for (i69 = 0; i69 <= n_vectorUB; i69 += 4) {
                    __m256d r29;
                    r29 = _mm256_loadu_pd(&R1[i69 + R1.size(0) * i67]);
                    _mm256_storeu_pd(&varargin_2[i69 + varargin_2.size(0) * i67], _mm256_mul_pd(r29,
                                      _mm256_set1_pd(-1.0)));
                }

                for (i69 = n_scalarLB; i69 < bc_loop_ub; i69++) {
                    varargin_2[i69 + varargin_2.size(0) * i67] = -R1[i69 + R1.size(0) * i67];
                }
            }

            varargin_4.set_size(R2.size(0), R2.size(1));
            cc_loop_ub = R2.size(1);
            for (int i68 = 0; i68 < cc_loop_ub; i68++) {
                int dc_loop_ub;
                int o_scalarLB;
                int o_vectorUB;
                dc_loop_ub = R2.size(0);
                o_scalarLB = R2.size(0) & -4;
                o_vectorUB = o_scalarLB - 4;
                for (i71 = 0; i71 <= o_vectorUB; i71 += 4) {
                    __m256d r30;
                    r30 = _mm256_loadu_pd(&R2[i71 + R2.size(0) * i68]);
                    _mm256_storeu_pd(&varargin_4[i71 + varargin_4.size(0) * i68], _mm256_mul_pd(r30,
                                      _mm256_set1_pd(-1.0)));
                }

                for (i71 = o_scalarLB; i71 < dc_loop_ub; i71++) {
                    varargin_4[i71 + varargin_4.size(0) * i68] = -R2[i71 + R2.size(0) * i68];
                }
            }

            varargin_6.set_size(R3.size(0), R3.size(1));
            ec_loop_ub = R3.size(1);
            for (int i70 = 0; i70 < ec_loop_ub; i70++) {
                int fc_loop_ub;
                int p_scalarLB;
                int p_vectorUB;
                fc_loop_ub = R3.size(0);
                p_scalarLB = R3.size(0) & -4;
                p_vectorUB = p_scalarLB - 4;
                for (i72 = 0; i72 <= p_vectorUB; i72 += 4) {
                    __m256d r31;
                    r31 = _mm256_loadu_pd(&R3[i72 + R3.size(0) * i70]);
                    _mm256_storeu_pd(&varargin_6[i72 + varargin_6.size(0) * i70], _mm256_mul_pd(r31,
                                      _mm256_set1_pd(-1.0)));
                }

                for (i72 = p_scalarLB; i72 < fc_loop_ub; i72++) {
                    varargin_6[i72 + varargin_6.size(0) * i70] = -R3[i72 + R3.size(0) * i70];
                }
            }

            if ((R1.size(0) != 0) && (R1.size(1) != 0)) {
                b_result = R1.size(1);
            } else if ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0)) {
                b_result = varargin_2.size(1);
            } else if ((R2.size(0) != 0) && (R2.size(1) != 0)) {
                b_result = R2.size(1);
            } else if ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0)) {
                b_result = varargin_4.size(1);
            } else if ((R3.size(0) != 0) && (R3.size(1) != 0)) {
                b_result = R3.size(1);
            } else if ((varargin_6.size(0) != 0) && (varargin_6.size(1) != 0)) {
                b_result = varargin_6.size(1);
            } else {
                int b_u0;
                b_u0 = R1.size(1);
                if (b_u0 > 0) {
                    b_result = b_u0;
                } else {
                    b_result = 0;
                }

                if (varargin_2.size(1) > b_result) {
                    b_result = varargin_2.size(1);
                }

                if (R2.size(1) > b_result) {
                    b_result = R2.size(1);
                }

                if (varargin_4.size(1) > b_result) {
                    b_result = varargin_4.size(1);
                }

                if (R3.size(1) > b_result) {
                    b_result = R3.size(1);
                }

                if (varargin_6.size(1) > b_result) {
                    b_result = varargin_6.size(1);
                }
            }

            b_empty_non_axis_sizes = (b_result == 0);
            if (b_empty_non_axis_sizes || ((R1.size(0) != 0) && (R1.size(1) != 0))) {
                h_input_sizes_idx_0 = R1.size(0);
            } else {
                h_input_sizes_idx_0 = 0;
            }

            if (b_empty_non_axis_sizes || ((varargin_2.size(0) != 0) && (varargin_2.size(1) != 0)))
            {
                i_input_sizes_idx_0 = varargin_2.size(0);
            } else {
                i_input_sizes_idx_0 = 0;
            }

            if (b_empty_non_axis_sizes || ((R2.size(0) != 0) && (R2.size(1) != 0))) {
                j_input_sizes_idx_0 = R2.size(0);
            } else {
                j_input_sizes_idx_0 = 0;
            }

            if (b_empty_non_axis_sizes || ((varargin_4.size(0) != 0) && (varargin_4.size(1) != 0)))
            {
                k_input_sizes_idx_0 = varargin_4.size(0);
            } else {
                k_input_sizes_idx_0 = 0;
            }

            if (b_empty_non_axis_sizes || ((R3.size(0) != 0) && (R3.size(1) != 0))) {
                l_input_sizes_idx_0 = R3.size(0);
            } else {
                l_input_sizes_idx_0 = 0;
            }

            if (b_empty_non_axis_sizes || ((varargin_6.size(0) != 0) && (varargin_6.size(1) != 0)))
            {
                m_input_sizes_idx_0 = varargin_6.size(0);
            } else {
                m_input_sizes_idx_0 = 0;
            }

            a_tmp = (static_cast<double>(c_k) + 1.0) * 6.0 * static_cast<double>(M) + 1.0;
            b_tmp = ((static_cast<double>(c_k) + 1.0) + 1.0) * 6.0 * static_cast<double>(M);
            if (b_tmp < a_tmp) {
                y.set_size(1, 0);
            } else {
                int gc_loop_ub;
                gc_loop_ub = static_cast<int>(b_tmp - a_tmp);
                y.set_size(1, (gc_loop_ub + 1));
                for (int i73 = 0; i73 <= gc_loop_ub; i73++) {
                    y[i73] = a_tmp + static_cast<double>(i73);
                }
            }

            a = (static_cast<double>(c_k) + 1.0) * static_cast<double>(N) + 1.0;
            c_b = ((static_cast<double>(c_k) + 1.0) + 1.0) * static_cast<double>(N);
            if (c_b < a) {
                b_y.set_size(1, 0);
            } else {
                int hc_loop_ub;
                hc_loop_ub = static_cast<int>(c_b - a);
                b_y.set_size(1, (hc_loop_ub + 1));
                for (int i74 = 0; i74 <= hc_loop_ub; i74++) {
                    b_y[i74] = a + static_cast<double>(i74);
                }
            }

            b_R1.set_size((((((h_input_sizes_idx_0 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                             k_input_sizes_idx_0) + l_input_sizes_idx_0) + m_input_sizes_idx_0),
                          b_result);
            for (int i75 = 0; i75 < b_result; i75++) {
                for (int i77 = 0; i77 < h_input_sizes_idx_0; i77++) {
                    b_R1[i77 + b_R1.size(0) * i75] = R1[i77 + h_input_sizes_idx_0 * i75];
                }
            }

            for (int i76 = 0; i76 < b_result; i76++) {
                for (int i79 = 0; i79 < i_input_sizes_idx_0; i79++) {
                    b_R1[(i79 + h_input_sizes_idx_0) + b_R1.size(0) * i76] = varargin_2[i79 +
                        i_input_sizes_idx_0 * i76];
                }
            }

            for (int i78 = 0; i78 < b_result; i78++) {
                for (int i81 = 0; i81 < j_input_sizes_idx_0; i81++) {
                    b_R1[((i81 + h_input_sizes_idx_0) + i_input_sizes_idx_0) + b_R1.size(0) * i78] =
                        R2[i81 + j_input_sizes_idx_0 * i78];
                }
            }

            for (int i80 = 0; i80 < b_result; i80++) {
                for (int i83 = 0; i83 < k_input_sizes_idx_0; i83++) {
                    b_R1[(((i83 + h_input_sizes_idx_0) + i_input_sizes_idx_0) + j_input_sizes_idx_0)
                        + b_R1.size(0) * i80] = varargin_4[i83 + k_input_sizes_idx_0 * i80];
                }
            }

            for (int i82 = 0; i82 < b_result; i82++) {
                for (int i85 = 0; i85 < l_input_sizes_idx_0; i85++) {
                    b_R1[((((i85 + h_input_sizes_idx_0) + i_input_sizes_idx_0) + j_input_sizes_idx_0)
                          + k_input_sizes_idx_0) + b_R1.size(0) * i82] = R3[i85 +
                        l_input_sizes_idx_0 * i82];
                }
            }

            for (int i84 = 0; i84 < b_result; i84++) {
                for (int i86 = 0; i86 < m_input_sizes_idx_0; i86++) {
                    b_R1[(((((i86 + h_input_sizes_idx_0) + i_input_sizes_idx_0) +
                            j_input_sizes_idx_0) + k_input_sizes_idx_0) + l_input_sizes_idx_0) +
                        b_R1.size(0) * i84] = varargin_6[i86 + m_input_sizes_idx_0 * i84];
                }
            }

            A->parenAssign(b_R1, y, b_y);

            //
            if (a_tmp > b_tmp) {
                i87 = -1;
                i88 = 0;
            } else {
                i87 = static_cast<int>(a_tmp) - 2;
                i88 = static_cast<int>(b_tmp);
            }

            ic_loop_ub = (i88 - i87) - 1;
            for (int i89 = 0; i89 < ic_loop_ub; i89++) {
                b[(i87 + i89) + 1] = r17[i89];
            }

            //
        }
    }

    //
    // Arguments    : const queue_coder *ctx_q_splines
    //                bool ctx_cfg_UseDynamicBreakpoints
    //                bool ctx_cfg_UseLinearBreakpoints
    //                double c_ctx_cfg_DynamicBreakpointsDis
    //                int ctx_cfg_SplineDegree
    //                double ctx_cfg_NGridLengthSpline
    //                int ctx_Bl_ncoeff
    //                unsigned long ctx_Bl_handle
    //                const coder::array<CurvStruct, 2U> &CurvStructs
    //                const double amax[3]
    //                double v_0
    //                double at_0
    //                double v_1
    //                double at_1
    //                coder::array<double, 2U> &BasisVal
    //                coder::array<double, 2U> &BasisValD
    //                const coder::array<double, 2U> &u_vec
    //                coder_internal_sparse *A
    //                coder::array<double, 1U> &b
    //                coder::array<double, 2U> &Aeq
    //                coder::array<double, 1U> &beq
    // Return Type  : void
    //
    static void BuildConstr_v4(const queue_coder *ctx_q_splines, bool ctx_cfg_UseDynamicBreakpoints,
        bool ctx_cfg_UseLinearBreakpoints, double c_ctx_cfg_DynamicBreakpointsDis, int
        ctx_cfg_SplineDegree, double ctx_cfg_NGridLengthSpline, int ctx_Bl_ncoeff, unsigned long
        ctx_Bl_handle, const coder::array<CurvStruct, 2U> &CurvStructs, const double amax[3], double
        v_0, double at_0, double v_1, double at_1, coder::array<double, 2U> &BasisVal, coder::array<
        double, 2U> &BasisValD, const coder::array<double, 2U> &u_vec, coder_internal_sparse *A,
        coder::array<double, 1U> &b, coder::array<double, 2U> &Aeq, coder::array<double, 1U> &beq)
    {
        int Bl_ncoeff;
        unsigned long Bl_handle;
        int N;
        coder::array<double, 2U> y;
        int unnamed_idx_0;
        int b_unnamed_idx_0;
        int unnamed_idx_1;
        coder::array<double, 2U> breakpoints;
        coder::array<double, 2U> b_u_vec;
        int b_loop_ub;
        coder::array<double, 2U> unusedU0;
        coder::array<double, 2U> r1D;
        coder::array<double, 2U> r2D;
        coder::array<double, 2U> r;
        coder::array<double, 2U> r1D_sqnorm;
        int c_loop_ub;
        coder::array<double, 1U> b_r2D;
        coder::array<double, 2U> r1;
        int d_loop_ub;
        coder::array<double, 1U> b_r1D;
        coder::array<double, 2U> r2;
        coder::array<double, 2U> R1;
        int e_loop_ub;
        int f_loop_ub;
        int i11;
        int h_loop_ub;
        coder::array<double, 2U> R2;
        int i_loop_ub;
        int j_loop_ub;
        int i15;
        int l_loop_ub;
        coder::array<double, 2U> R3;
        int m_loop_ub;
        coder::array<double, 2U> varargin_3;
        int o_loop_ub;
        int i19;
        coder::array<double, 2U> varargin_5;
        int q_loop_ub;
        int i21;
        coder::array<double, 2U> varargin_7;
        int s_loop_ub;
        int i23;
        int result;
        bool empty_non_axis_sizes;
        int i24;
        int input_sizes_idx_0;
        int b_input_sizes_idx_0;
        int c_input_sizes_idx_0;
        int d_input_sizes_idx_0;
        int e_input_sizes_idx_0;
        int f_input_sizes_idx_0;
        int g_input_sizes_idx_0;
        double b_b;
        coder::array<double, 2U> b_y;
        int h_input_sizes_idx_0;
        int i27;
        int i28;
        coder::array<double, 2U> b_BasisVal;
        double x;
        coder::array<double, 1U> bC2;
        int w_loop_ub;
        coder::array<double, 1U> bC3;
        int x_loop_ub;
        coder::array<double, 1U> bC4;
        int y_loop_ub;
        coder::array<double, 1U> r12;
        int ab_loop_ub;
        int b_unnamed_idx_1;
        int c_unnamed_idx_1;
        int d_unnamed_idx_1;
        int e_unnamed_idx_1;
        int f_unnamed_idx_1;
        int bb_loop_ub;
        int g_scalarLB;
        int g_vectorUB;
        int i47;
        int cb_loop_ub;
        int db_loop_ub;
        int eb_loop_ub;
        int fb_loop_ub;
        int gb_loop_ub;
        int hb_loop_ub;
        double a;
        double b_a;
        double c_a;
        double d_a;
        double e_a;
        double f_a;
        double c_r1D[3];
        int ib_loop_ub;
        int jb_loop_ub;
        int kb_loop_ub;
        coder::array<double, 2U> g_a;
        coder::array<double, 2U> r14;
        int lb_loop_ub;
        int mb_loop_ub;
        coder::array<double, 2U> r1Dn_sqnorm;
        int nb_loop_ub;
        int i60;
        int ob_loop_ub;
        double h_a;
        coder::array<double, 2U> c_u_vec;
        int pb_loop_ub;
        double i_a;
        int rb_loop_ub;
        double j_a;
        int sb_loop_ub;
        double k_a;
        int tb_loop_ub;
        double l_a;
        coder::array<double, 2U> unusedU1;
        coder::array<double, 2U> r1Dn;
        coder::array<double, 2U> r2Dn;
        int ub_loop_ub;
        double m_a;
        coder::array<double, 2U> r15;
        double d1;
        int i64;
        double t_1[3];
        int e_r1D;
        double d3;
        int xb_loop_ub;
        coder::array<double, 1U> b_r2Dn;
        int yb_loop_ub;
        int ac_loop_ub;
        coder::array<double, 1U> b_r1Dn;
        int dc_loop_ub;
        int gc_loop_ub;
        int i75;
        int i79;
        int i83;
        int i85;
        int i87;
        int i88;
        cell_wrap_3 reshapes[3];
        coder::array<double, 2U> b_reshapes;

        //  1 -> stdout
        //  2 -> stderr
        if ((static_cast<unsigned long>(std::round(DebugConfig)) & 8UL) != 0UL) {
            printf("BuildConstr_v4 with Ncrv = %d, amax = [%f, %f, %f], v_0 = %f, at_0 = %f, v_1 = %f, at_1 = %f\n",
                   CurvStructs.size(1), amax[0], amax[1], amax[2], v_0, at_0, v_1, at_1);
            fflush(stdout);
        }

        Bl_ncoeff = ctx_Bl_ncoeff;
        Bl_handle = ctx_Bl_handle;
        if (ctx_cfg_UseDynamicBreakpoints) {
            double varargin_1;
            varargin_1 = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStructs[0].Type,
                                    CurvStructs[0].P0, CurvStructs[0].P1, CurvStructs[0].evec,
                                    CurvStructs[0].theta, CurvStructs[0].pitch, CurvStructs[0].
                                    CoeffP5, CurvStructs[0].sp_index, CurvStructs[0].a_param,
                                    CurvStructs[0].b_param) / c_ctx_cfg_DynamicBreakpointsDis;
            if (ctx_cfg_UseLinearBreakpoints) {
                double delta1;
                int i;
                int loop_ub;
                y.set_size(1, (static_cast<int>(std::fmax(std::floor(varargin_1), 4.0))));
                y[static_cast<int>(std::fmax(std::floor(varargin_1), 4.0)) - 1] = 1.0;
                y[0] = 0.0;
                delta1 = 1.0 / (static_cast<double>(y.size(1)) - 1.0);
                i = y.size(1);
                for (int k = 0; k <= i - 3; k++) {
                    y[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
                }

                Bl_ncoeff = (y.size(1) + ctx_cfg_SplineDegree) - 2;
                breakpoints.set_size(1, y.size(1));
                loop_ub = y.size(1);
                for (int i3 = 0; i3 < loop_ub; i3++) {
                    breakpoints[i3] = y[i3];
                }

                c_bspline_create_with_breakpoints(&Bl_handle, ctx_cfg_SplineDegree, &breakpoints[0],
                    y.size(1));
            }

            bspline_base_eval(Bl_ncoeff, Bl_handle, u_vec, BasisVal, BasisValD);
        }

        N = BasisVal.size(1);

        //
        A->init((7.0 * static_cast<double>(BasisVal.size(0)) * static_cast<double>(CurvStructs.size
                  (1))), (static_cast<double>(BasisVal.size(1)) * static_cast<double>
                          (CurvStructs.size(1))));

        //  preallocation
        unnamed_idx_0 = static_cast<int>(7.0 * static_cast<double>(BasisVal.size(0)) * static_cast<
            double>(CurvStructs.size(1)));
        b.set_size(unnamed_idx_0);
        for (int i1 = 0; i1 < unnamed_idx_0; i1++) {
            b[i1] = 0.0;
        }

        //  preallocation
        b_unnamed_idx_0 = static_cast<int>(2.0 * (static_cast<double>(CurvStructs.size(1)) + 1.0));
        unnamed_idx_1 = static_cast<int>(static_cast<double>(BasisVal.size(1)) * static_cast<double>
            (CurvStructs.size(1)));
        Aeq.set_size(b_unnamed_idx_0, unnamed_idx_1);
        for (int i2 = 0; i2 < unnamed_idx_1; i2++) {
            for (int i4 = 0; i4 < b_unnamed_idx_0; i4++) {
                Aeq[i4 + Aeq.size(0) * i2] = 0.0;
            }
        }

        //  preallocation
        unnamed_idx_0 = static_cast<int>(2.0 * (static_cast<double>(CurvStructs.size(1)) + 1.0));
        beq.set_size(unnamed_idx_0);
        for (int i5 = 0; i5 < unnamed_idx_0; i5++) {
            beq[i5] = 0.0;
        }

        //  preallocation
        //  coder.varsize('b', [7*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz, 1], [1,0]);
        //  coder.varsize('Aeq', [2*(FeedoptLimits.MaxNHorz+1), FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz], [1,1]); 
        //  coder.varsize('beq', [2*(FeedoptLimits.MaxNHorz+1), 1], [1,0]);
        //
        b_u_vec.set_size(1, u_vec.size(1));
        b_loop_ub = u_vec.size(1) - 1;
        for (int i6 = 0; i6 <= b_loop_ub; i6++) {
            b_u_vec[i6] = u_vec[i6];
        }

        j_EvalCurvStruct(ctx_q_splines, CurvStructs[0].Type, CurvStructs[0].P0, CurvStructs[0].P1,
                         CurvStructs[0].evec, CurvStructs[0].theta, CurvStructs[0].pitch,
                         CurvStructs[0].CoeffP5, CurvStructs[0].sp_index, CurvStructs[0].a_param,
                         CurvStructs[0].b_param, b_u_vec, unusedU0, r1D, r2D);
        power(r1D, r);
        sum(r, r1D_sqnorm);

        //  squared norm
        //
        //  unit tangent vector @ start
        //
        //
        c_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i7 = 0; i7 < c_loop_ub; i7++) {
            b_r2D[i7] = r2D[3 * i7];
        }

        b_bsxfun(b_r2D, BasisVal, r1);
        d_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i8 = 0; i8 < d_loop_ub; i8++) {
            b_r1D[i8] = r1D[3 * i8];
        }

        b_bsxfun(b_r1D, BasisValD, r2);
        R1.set_size(r1.size(0), r1.size(1));
        e_loop_ub = r1.size(1);
        for (int i9 = 0; i9 < e_loop_ub; i9++) {
            int g_loop_ub;
            int scalarLB;
            int vectorUB;
            g_loop_ub = r1.size(0);
            scalarLB = r1.size(0) & -4;
            vectorUB = scalarLB - 4;
            for (i11 = 0; i11 <= vectorUB; i11 += 4) {
                __m256d r3;
                __m256d r4;
                r3 = _mm256_loadu_pd(&r2[i11 + r2.size(0) * i9]);
                r4 = _mm256_loadu_pd(&r1[i11 + r1.size(0) * i9]);
                _mm256_storeu_pd(&R1[i11 + R1.size(0) * i9], _mm256_add_pd(r4, _mm256_mul_pd
                                  (_mm256_set1_pd(0.5), r3)));
            }

            for (i11 = scalarLB; i11 < g_loop_ub; i11++) {
                R1[i11 + R1.size(0) * i9] = r1[i11 + r1.size(0) * i9] + 0.5 * r2[i11 + r2.size(0) *
                    i9];
            }
        }

        f_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i10 = 0; i10 < f_loop_ub; i10++) {
            b_r2D[i10] = r2D[3 * i10 + 1];
        }

        b_bsxfun(b_r2D, BasisVal, r1);
        h_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i12 = 0; i12 < h_loop_ub; i12++) {
            b_r1D[i12] = r1D[3 * i12 + 1];
        }

        b_bsxfun(b_r1D, BasisValD, r2);
        R2.set_size(r1.size(0), r1.size(1));
        i_loop_ub = r1.size(1);
        for (int i13 = 0; i13 < i_loop_ub; i13++) {
            int k_loop_ub;
            int b_scalarLB;
            int b_vectorUB;
            k_loop_ub = r1.size(0);
            b_scalarLB = r1.size(0) & -4;
            b_vectorUB = b_scalarLB - 4;
            for (i15 = 0; i15 <= b_vectorUB; i15 += 4) {
                __m256d r5;
                __m256d r6;
                r5 = _mm256_loadu_pd(&r2[i15 + r2.size(0) * i13]);
                r6 = _mm256_loadu_pd(&r1[i15 + r1.size(0) * i13]);
                _mm256_storeu_pd(&R2[i15 + R2.size(0) * i13], _mm256_add_pd(r6, _mm256_mul_pd
                                  (_mm256_set1_pd(0.5), r5)));
            }

            for (i15 = b_scalarLB; i15 < k_loop_ub; i15++) {
                R2[i15 + R2.size(0) * i13] = r1[i15 + r1.size(0) * i13] + 0.5 * r2[i15 + r2.size(0) *
                    i13];
            }
        }

        j_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i14 = 0; i14 < j_loop_ub; i14++) {
            b_r2D[i14] = r2D[3 * i14 + 2];
        }

        b_bsxfun(b_r2D, BasisVal, r1);
        l_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i16 = 0; i16 < l_loop_ub; i16++) {
            b_r1D[i16] = r1D[3 * i16 + 2];
        }

        b_bsxfun(b_r1D, BasisValD, r2);
        R3.set_size(r1.size(0), r1.size(1));
        m_loop_ub = r1.size(1);
        for (int i17 = 0; i17 < m_loop_ub; i17++) {
            int n_loop_ub;
            int c_scalarLB;
            int c_vectorUB;
            n_loop_ub = r1.size(0);
            c_scalarLB = r1.size(0) & -4;
            c_vectorUB = c_scalarLB - 4;
            for (i19 = 0; i19 <= c_vectorUB; i19 += 4) {
                __m256d r7;
                __m256d r8;
                r7 = _mm256_loadu_pd(&r2[i19 + r2.size(0) * i17]);
                r8 = _mm256_loadu_pd(&r1[i19 + r1.size(0) * i17]);
                _mm256_storeu_pd(&R3[i19 + R3.size(0) * i17], _mm256_add_pd(r8, _mm256_mul_pd
                                  (_mm256_set1_pd(0.5), r7)));
            }

            for (i19 = c_scalarLB; i19 < n_loop_ub; i19++) {
                R3[i19 + R3.size(0) * i17] = r1[i19 + r1.size(0) * i17] + 0.5 * r2[i19 + r2.size(0) *
                    i17];
            }
        }

        //
        varargin_3.set_size(R1.size(0), R1.size(1));
        o_loop_ub = R1.size(1);
        for (int i18 = 0; i18 < o_loop_ub; i18++) {
            int p_loop_ub;
            int d_scalarLB;
            int d_vectorUB;
            p_loop_ub = R1.size(0);
            d_scalarLB = R1.size(0) & -4;
            d_vectorUB = d_scalarLB - 4;
            for (i21 = 0; i21 <= d_vectorUB; i21 += 4) {
                __m256d r9;
                r9 = _mm256_loadu_pd(&R1[i21 + R1.size(0) * i18]);
                _mm256_storeu_pd(&varargin_3[i21 + varargin_3.size(0) * i18], _mm256_mul_pd(r9,
                                  _mm256_set1_pd(-1.0)));
            }

            for (i21 = d_scalarLB; i21 < p_loop_ub; i21++) {
                varargin_3[i21 + varargin_3.size(0) * i18] = -R1[i21 + R1.size(0) * i18];
            }
        }

        varargin_5.set_size(R2.size(0), R2.size(1));
        q_loop_ub = R2.size(1);
        for (int i20 = 0; i20 < q_loop_ub; i20++) {
            int r_loop_ub;
            int e_scalarLB;
            int e_vectorUB;
            r_loop_ub = R2.size(0);
            e_scalarLB = R2.size(0) & -4;
            e_vectorUB = e_scalarLB - 4;
            for (i23 = 0; i23 <= e_vectorUB; i23 += 4) {
                __m256d r10;
                r10 = _mm256_loadu_pd(&R2[i23 + R2.size(0) * i20]);
                _mm256_storeu_pd(&varargin_5[i23 + varargin_5.size(0) * i20], _mm256_mul_pd(r10,
                                  _mm256_set1_pd(-1.0)));
            }

            for (i23 = e_scalarLB; i23 < r_loop_ub; i23++) {
                varargin_5[i23 + varargin_5.size(0) * i20] = -R2[i23 + R2.size(0) * i20];
            }
        }

        varargin_7.set_size(R3.size(0), R3.size(1));
        s_loop_ub = R3.size(1);
        for (int i22 = 0; i22 < s_loop_ub; i22++) {
            int t_loop_ub;
            int f_scalarLB;
            int f_vectorUB;
            t_loop_ub = R3.size(0);
            f_scalarLB = R3.size(0) & -4;
            f_vectorUB = f_scalarLB - 4;
            for (i24 = 0; i24 <= f_vectorUB; i24 += 4) {
                __m256d r11;
                r11 = _mm256_loadu_pd(&R3[i24 + R3.size(0) * i22]);
                _mm256_storeu_pd(&varargin_7[i24 + varargin_7.size(0) * i22], _mm256_mul_pd(r11,
                                  _mm256_set1_pd(-1.0)));
            }

            for (i24 = f_scalarLB; i24 < t_loop_ub; i24++) {
                varargin_7[i24 + varargin_7.size(0) * i22] = -R3[i24 + R3.size(0) * i22];
            }
        }

        if ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0)) {
            result = BasisVal.size(1);
        } else if ((R1.size(0) != 0) && (R1.size(1) != 0)) {
            result = R1.size(1);
        } else if ((varargin_3.size(0) != 0) && (varargin_3.size(1) != 0)) {
            result = varargin_3.size(1);
        } else if ((R2.size(0) != 0) && (R2.size(1) != 0)) {
            result = R2.size(1);
        } else if ((varargin_5.size(0) != 0) && (varargin_5.size(1) != 0)) {
            result = varargin_5.size(1);
        } else if ((R3.size(0) != 0) && (R3.size(1) != 0)) {
            result = R3.size(1);
        } else if ((varargin_7.size(0) != 0) && (varargin_7.size(1) != 0)) {
            result = varargin_7.size(1);
        } else {
            int u0;
            u0 = BasisVal.size(1);
            if (u0 > 0) {
                result = u0;
            } else {
                result = 0;
            }

            if (R1.size(1) > result) {
                result = R1.size(1);
            }

            if (varargin_3.size(1) > result) {
                result = varargin_3.size(1);
            }

            if (R2.size(1) > result) {
                result = R2.size(1);
            }

            if (varargin_5.size(1) > result) {
                result = varargin_5.size(1);
            }

            if (R3.size(1) > result) {
                result = R3.size(1);
            }

            if (varargin_7.size(1) > result) {
                result = varargin_7.size(1);
            }
        }

        empty_non_axis_sizes = (result == 0);
        if (empty_non_axis_sizes || ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0))) {
            input_sizes_idx_0 = BasisVal.size(0);
        } else {
            input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || ((R1.size(0) != 0) && (R1.size(1) != 0))) {
            b_input_sizes_idx_0 = R1.size(0);
        } else {
            b_input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || ((varargin_3.size(0) != 0) && (varargin_3.size(1) != 0))) {
            c_input_sizes_idx_0 = varargin_3.size(0);
        } else {
            c_input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || ((R2.size(0) != 0) && (R2.size(1) != 0))) {
            d_input_sizes_idx_0 = R2.size(0);
        } else {
            d_input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || ((varargin_5.size(0) != 0) && (varargin_5.size(1) != 0))) {
            e_input_sizes_idx_0 = varargin_5.size(0);
        } else {
            e_input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || ((R3.size(0) != 0) && (R3.size(1) != 0))) {
            f_input_sizes_idx_0 = R3.size(0);
        } else {
            f_input_sizes_idx_0 = 0;
        }

        if (empty_non_axis_sizes || ((varargin_7.size(0) != 0) && (varargin_7.size(1) != 0))) {
            g_input_sizes_idx_0 = varargin_7.size(0);
        } else {
            g_input_sizes_idx_0 = 0;
        }

        b_b = 7.0 * static_cast<double>(BasisVal.size(0));
        if (b_b < 1.0) {
            y.set_size(1, 0);
        } else {
            int u_loop_ub;
            u_loop_ub = static_cast<int>(b_b - 1.0);
            y.set_size(1, (u_loop_ub + 1));
            for (int i25 = 0; i25 <= u_loop_ub; i25++) {
                y[i25] = static_cast<double>(i25) + 1.0;
            }
        }

        if (BasisVal.size(1) < 1) {
            b_y.set_size(1, 0);
        } else {
            int v_loop_ub;
            b_y.set_size(1, BasisVal.size(1));
            v_loop_ub = BasisVal.size(1) - 1;
            for (int i26 = 0; i26 <= v_loop_ub; i26++) {
                b_y[i26] = static_cast<double>(i26) + 1.0;
            }
        }

        h_input_sizes_idx_0 = input_sizes_idx_0;
        input_sizes_idx_0 = b_input_sizes_idx_0;
        b_input_sizes_idx_0 = c_input_sizes_idx_0;
        c_input_sizes_idx_0 = d_input_sizes_idx_0;
        d_input_sizes_idx_0 = e_input_sizes_idx_0;
        i27 = h_input_sizes_idx_0 + input_sizes_idx_0;
        i28 = i27 + b_input_sizes_idx_0;
        b_BasisVal.set_size(((((i28 + c_input_sizes_idx_0) + d_input_sizes_idx_0) +
                              f_input_sizes_idx_0) + g_input_sizes_idx_0), result);
        for (int i29 = 0; i29 < result; i29++) {
            for (int i31 = 0; i31 < h_input_sizes_idx_0; i31++) {
                b_BasisVal[i31 + b_BasisVal.size(0) * i29] = BasisVal[i31 + h_input_sizes_idx_0 *
                    i29];
            }
        }

        for (int i30 = 0; i30 < result; i30++) {
            for (int i33 = 0; i33 < input_sizes_idx_0; i33++) {
                b_BasisVal[(i33 + h_input_sizes_idx_0) + b_BasisVal.size(0) * i30] = R1[i33 +
                    input_sizes_idx_0 * i30];
            }
        }

        for (int i32 = 0; i32 < result; i32++) {
            for (int i35 = 0; i35 < b_input_sizes_idx_0; i35++) {
                b_BasisVal[((i35 + h_input_sizes_idx_0) + input_sizes_idx_0) + b_BasisVal.size(0) *
                    i32] = varargin_3[i35 + b_input_sizes_idx_0 * i32];
            }
        }

        for (int i34 = 0; i34 < result; i34++) {
            for (int i37 = 0; i37 < c_input_sizes_idx_0; i37++) {
                b_BasisVal[(((i37 + h_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0)
                    + b_BasisVal.size(0) * i34] = R2[i37 + c_input_sizes_idx_0 * i34];
            }
        }

        for (int i36 = 0; i36 < result; i36++) {
            for (int i39 = 0; i39 < d_input_sizes_idx_0; i39++) {
                b_BasisVal[((((i39 + h_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0)
                            + c_input_sizes_idx_0) + b_BasisVal.size(0) * i36] = varargin_5[i39 +
                    d_input_sizes_idx_0 * i36];
            }
        }

        for (int i38 = 0; i38 < result; i38++) {
            for (int i41 = 0; i41 < f_input_sizes_idx_0; i41++) {
                b_BasisVal[((((i41 + i27) + b_input_sizes_idx_0) + c_input_sizes_idx_0) +
                            d_input_sizes_idx_0) + b_BasisVal.size(0) * i38] = R3[i41 +
                    f_input_sizes_idx_0 * i38];
            }
        }

        for (int i40 = 0; i40 < result; i40++) {
            for (int i42 = 0; i42 < g_input_sizes_idx_0; i42++) {
                b_BasisVal[((((i42 + i28) + c_input_sizes_idx_0) + d_input_sizes_idx_0) +
                            f_input_sizes_idx_0) + b_BasisVal.size(0) * i40] = varargin_7[i42 +
                    g_input_sizes_idx_0 * i40];
            }
        }

        A->parenAssign(b_BasisVal, y, b_y);

        //
        x = std::pow(CurvStructs[0].FeedRate, 2.0);
        bC2.set_size(BasisVal.size(0));
        w_loop_ub = BasisVal.size(0);
        for (int i43 = 0; i43 < w_loop_ub; i43++) {
            bC2[i43] = amax[0];
        }

        bC3.set_size(BasisVal.size(0));
        x_loop_ub = BasisVal.size(0);
        for (int i44 = 0; i44 < x_loop_ub; i44++) {
            bC3[i44] = amax[1];
        }

        bC4.set_size(BasisVal.size(0));
        y_loop_ub = BasisVal.size(0);
        for (int i45 = 0; i45 < y_loop_ub; i45++) {
            bC4[i45] = amax[2];
        }

        //
        r12.set_size(r1D_sqnorm.size(1));
        ab_loop_ub = r1D_sqnorm.size(1);
        for (int i46 = 0; i46 < ab_loop_ub; i46++) {
            r12[i46] = r1D_sqnorm[i46];
        }

        unnamed_idx_1 = r12.size(0);
        b_unnamed_idx_1 = bC2.size(0);
        c_unnamed_idx_1 = bC2.size(0);
        d_unnamed_idx_1 = bC3.size(0);
        e_unnamed_idx_1 = bC3.size(0);
        f_unnamed_idx_1 = bC4.size(0);
        bb_loop_ub = r12.size(0);
        g_scalarLB = r12.size(0) & -4;
        g_vectorUB = g_scalarLB - 4;
        for (i47 = 0; i47 <= g_vectorUB; i47 += 4) {
            __m256d r13;
            r13 = _mm256_loadu_pd(&r12[i47]);
            _mm256_storeu_pd(&b[i47], _mm256_div_pd(_mm256_set1_pd(x), r13));
        }

        for (i47 = g_scalarLB; i47 < bb_loop_ub; i47++) {
            b[i47] = x / r12[i47];
        }

        cb_loop_ub = bC2.size(0);
        for (int i48 = 0; i48 < cb_loop_ub; i48++) {
            b[i48 + unnamed_idx_1] = bC2[i48];
        }

        db_loop_ub = bC2.size(0);
        for (int i49 = 0; i49 < db_loop_ub; i49++) {
            b[(i49 + unnamed_idx_1) + b_unnamed_idx_1] = bC2[i49];
        }

        eb_loop_ub = bC3.size(0);
        for (int i50 = 0; i50 < eb_loop_ub; i50++) {
            b[((i50 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1] = bC3[i50];
        }

        fb_loop_ub = bC3.size(0);
        for (int i51 = 0; i51 < fb_loop_ub; i51++) {
            b[(((i51 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1] =
                bC3[i51];
        }

        gb_loop_ub = bC4.size(0);
        for (int i52 = 0; i52 < gb_loop_ub; i52++) {
            b[((((i52 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1) +
                e_unnamed_idx_1] = bC4[i52];
        }

        hb_loop_ub = bC4.size(0);
        for (int i53 = 0; i53 < hb_loop_ub; i53++) {
            b[(((((i53 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1) +
                e_unnamed_idx_1) + f_unnamed_idx_1] = bC4[i53];
        }

        double d;

        //
        a = r2D[0];
        b_a = 0.5 * r1D[0];
        c_a = r2D[1];
        d_a = 0.5 * r1D[1];
        e_a = r2D[2];
        f_a = 0.5 * r1D[2];
        d = b_norm(*(double (*)[3])&r1D[0]);
        c_r1D[0] = r1D[0] / d;
        c_r1D[1] = r1D[1] / d;
        c_r1D[2] = r1D[2] / d;
        ib_loop_ub = BasisVal.size(1);
        jb_loop_ub = BasisVal.size(1);
        kb_loop_ub = BasisVal.size(1);
        g_a.set_size(3, BasisVal.size(1));
        for (int i54 = 0; i54 < ib_loop_ub; i54++) {
            g_a[3 * i54] = a * BasisVal[BasisVal.size(0) * i54] + b_a * BasisValD[BasisValD.size(0) *
                i54];
        }

        for (int i55 = 0; i55 < jb_loop_ub; i55++) {
            g_a[3 * i55 + 1] = c_a * BasisVal[BasisVal.size(0) * i55] + d_a *
                BasisValD[BasisValD.size(0) * i55];
        }

        for (int i56 = 0; i56 < kb_loop_ub; i56++) {
            g_a[3 * i56 + 2] = e_a * BasisVal[BasisVal.size(0) * i56] + f_a *
                BasisValD[BasisValD.size(0) * i56];
        }

        mtimes(c_r1D, g_a, r14);
        lb_loop_ub = BasisVal.size(1);
        for (int i57 = 0; i57 < lb_loop_ub; i57++) {
            Aeq[Aeq.size(0) * i57] = BasisVal[BasisVal.size(0) * i57];
        }

        mb_loop_ub = r14.size(1);
        for (int i58 = 0; i58 < mb_loop_ub; i58++) {
            Aeq[Aeq.size(0) * i58 + 1] = r14[i58];
        }

        beq[0] = std::pow(v_0, 2.0) / r1D_sqnorm[0];
        beq[1] = at_0;

        //  This should be the correct behavior for a single segment,
        //  reusing the r1D norm
        r1Dn_sqnorm.set_size(1, r1D_sqnorm.size(1));
        nb_loop_ub = r1D_sqnorm.size(1);
        for (int i59 = 0; i59 < nb_loop_ub; i59++) {
            r1Dn_sqnorm[i59] = r1D_sqnorm[i59];
        }

        i60 = CurvStructs.size(1);
        if (0 <= CurvStructs.size(1) - 2) {
            b_unnamed_idx_1 = bC2.size(0);
            c_unnamed_idx_1 = bC2.size(0);
            d_unnamed_idx_1 = bC3.size(0);
            e_unnamed_idx_1 = bC3.size(0);
            f_unnamed_idx_1 = bC4.size(0);
            ob_loop_ub = bC2.size(0);
            pb_loop_ub = bC2.size(0);
            rb_loop_ub = bC3.size(0);
            sb_loop_ub = bC3.size(0);
            tb_loop_ub = bC4.size(0);
            ub_loop_ub = bC4.size(0);
        }

        for (int b_k = 0; b_k <= i60 - 2; b_k++) {
            int qb_loop_ub;
            double b_x;
            int wb_loop_ub;
            int bc_loop_ub;
            int cc_loop_ub;
            int ec_loop_ub;
            int hc_loop_ub;
            int ic_loop_ub;
            int jc_loop_ub;
            int lc_loop_ub;
            int mc_loop_ub;
            int oc_loop_ub;
            int qc_loop_ub;
            int sc_loop_ub;
            int b_result;
            bool b_empty_non_axis_sizes;
            int i_input_sizes_idx_0;
            int j_input_sizes_idx_0;
            int k_input_sizes_idx_0;
            int l_input_sizes_idx_0;
            int m_input_sizes_idx_0;
            int n_input_sizes_idx_0;
            int o_input_sizes_idx_0;
            double a_tmp;
            double n_a;
            double b_tmp;
            double c_b;
            double o_a;
            double d_b;
            double d4;
            int i105;
            int wc_loop_ub;
            int xc_loop_ub;
            double d5;
            int i114;
            int i115;
            double p_a;
            int yc_loop_ub;
            double d6;
            int i117;
            double c;
            int ad_loop_ub;
            double q_a;
            double r_a;
            double s_a;
            double t_a;
            double u_a;
            double v_a;
            double d7;
            int i119;
            int i120;
            int bd_loop_ub;
            int cd_loop_ub;
            double w_a;
            double x_a;
            double y_a;
            double ab_a;
            double bb_a;
            double cb_a;
            double d10;
            int i123;
            int dd_loop_ub;
            int ed_loop_ub;
            int fd_loop_ub;
            int gd_loop_ub;
            int hd_loop_ub;
            int id_loop_ub;
            int jd_loop_ub;
            if (ctx_cfg_UseDynamicBreakpoints) {
                double varargin_2;
                varargin_2 = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStructs[b_k +
                                        1].Type, CurvStructs[b_k + 1].P0, CurvStructs[b_k + 1].P1,
                                        CurvStructs[b_k + 1].evec, CurvStructs[b_k + 1].theta,
                                        CurvStructs[b_k + 1].pitch, CurvStructs[b_k + 1].CoeffP5,
                                        CurvStructs[b_k + 1].sp_index, CurvStructs[b_k + 1].a_param,
                                        CurvStructs[b_k + 1].b_param) /
                    c_ctx_cfg_DynamicBreakpointsDis;
                if (ctx_cfg_UseLinearBreakpoints) {
                    int i61;
                    double b_delta1;
                    int i63;
                    int vb_loop_ub;
                    i61 = static_cast<int>(std::fmax(4.0, std::floor(varargin_2)));
                    y.set_size(1, i61);
                    y[i61 - 1] = 1.0;
                    y[0] = 0.0;
                    b_delta1 = 1.0 / (static_cast<double>(y.size(1)) - 1.0);
                    i63 = y.size(1);
                    for (int c_k = 0; c_k <= i63 - 3; c_k++) {
                        y[c_k + 1] = (static_cast<double>(c_k) + 1.0) * b_delta1;
                    }

                    Bl_ncoeff = (y.size(1) + ctx_cfg_SplineDegree) - 2;
                    breakpoints.set_size(1, y.size(1));
                    vb_loop_ub = y.size(1);
                    for (int i65 = 0; i65 < vb_loop_ub; i65++) {
                        breakpoints[i65] = y[i65];
                    }

                    c_bspline_create_with_breakpoints(&Bl_handle, ctx_cfg_SplineDegree,
                        &breakpoints[0], y.size(1));
                }

                bspline_base_eval(Bl_ncoeff, Bl_handle, u_vec, BasisVal, BasisValD);
            }

            N = BasisVal.size(1);
            c_u_vec.set_size(1, u_vec.size(1));
            qb_loop_ub = u_vec.size(1) - 1;
            for (int i62 = 0; i62 <= qb_loop_ub; i62++) {
                c_u_vec[i62] = u_vec[i62];
            }

            int d_r1D;
            double d2;
            j_EvalCurvStruct(ctx_q_splines, CurvStructs[b_k + 1].Type, CurvStructs[b_k + 1].P0,
                             CurvStructs[b_k + 1].P1, CurvStructs[b_k + 1].evec, CurvStructs[b_k + 1]
                             .theta, CurvStructs[b_k + 1].pitch, CurvStructs[b_k + 1].CoeffP5,
                             CurvStructs[b_k + 1].sp_index, CurvStructs[b_k + 1].a_param,
                             CurvStructs[b_k + 1].b_param, c_u_vec, unusedU1, r1Dn, r2Dn);
            power(r1Dn, r15);
            sum(r15, r1Dn_sqnorm);

            //  squared norm
            b_x = std::pow(CurvStructs[b_k + 1].FeedRate, 2.0);
            d_r1D = r1D.size(1);
            d2 = b_norm(*(double (*)[3])&r1D[3 * (d_r1D - 1)]);
            t_1[0] = r1D[3 * (r1D.size(1) - 1)] / d2;
            t_1[1] = r1D[3 * (r1D.size(1) - 1) + 1] / d2;
            t_1[2] = r1D[3 * (r1D.size(1) - 1) + 2] / d2;

            //  unit tangent vector @ end of previous piece
            //
            wb_loop_ub = r2Dn.size(1);
            b_r2Dn.set_size(r2Dn.size(1));
            for (int i66 = 0; i66 < wb_loop_ub; i66++) {
                b_r2Dn[i66] = r2Dn[3 * i66];
            }

            b_bsxfun(b_r2Dn, BasisVal, r1);
            bc_loop_ub = r1Dn.size(1);
            b_r1Dn.set_size(r1Dn.size(1));
            for (int i69 = 0; i69 < bc_loop_ub; i69++) {
                b_r1Dn[i69] = r1Dn[3 * i69];
            }

            b_bsxfun(b_r1Dn, BasisValD, r2);
            R1.set_size(r1.size(0), r1.size(1));
            cc_loop_ub = r1.size(1);
            for (int i71 = 0; i71 < cc_loop_ub; i71++) {
                int fc_loop_ub;
                int h_scalarLB;
                int h_vectorUB;
                fc_loop_ub = r1.size(0);
                h_scalarLB = r1.size(0) & -4;
                h_vectorUB = h_scalarLB - 4;
                for (i75 = 0; i75 <= h_vectorUB; i75 += 4) {
                    __m256d r16;
                    __m256d r17;
                    r16 = _mm256_loadu_pd(&r2[i75 + r2.size(0) * i71]);
                    r17 = _mm256_loadu_pd(&r1[i75 + r1.size(0) * i71]);
                    _mm256_storeu_pd(&R1[i75 + R1.size(0) * i71], _mm256_add_pd(r17, _mm256_mul_pd
                                      (_mm256_set1_pd(0.5), r16)));
                }

                for (i75 = h_scalarLB; i75 < fc_loop_ub; i75++) {
                    R1[i75 + R1.size(0) * i71] = r1[i75 + r1.size(0) * i71] + 0.5 * r2[i75 + r2.size
                        (0) * i71];
                }
            }

            ec_loop_ub = r2Dn.size(1);
            b_r2Dn.set_size(r2Dn.size(1));
            for (int i74 = 0; i74 < ec_loop_ub; i74++) {
                b_r2Dn[i74] = r2Dn[3 * i74 + 1];
            }

            b_bsxfun(b_r2Dn, BasisVal, r1);
            hc_loop_ub = r1Dn.size(1);
            b_r1Dn.set_size(r1Dn.size(1));
            for (int i76 = 0; i76 < hc_loop_ub; i76++) {
                b_r1Dn[i76] = r1Dn[3 * i76 + 1];
            }

            b_bsxfun(b_r1Dn, BasisValD, r2);
            R2.set_size(r1.size(0), r1.size(1));
            ic_loop_ub = r1.size(1);
            for (int i77 = 0; i77 < ic_loop_ub; i77++) {
                int kc_loop_ub;
                int i_scalarLB;
                int i_vectorUB;
                kc_loop_ub = r1.size(0);
                i_scalarLB = r1.size(0) & -4;
                i_vectorUB = i_scalarLB - 4;
                for (i79 = 0; i79 <= i_vectorUB; i79 += 4) {
                    __m256d r18;
                    __m256d r19;
                    r18 = _mm256_loadu_pd(&r2[i79 + r2.size(0) * i77]);
                    r19 = _mm256_loadu_pd(&r1[i79 + r1.size(0) * i77]);
                    _mm256_storeu_pd(&R2[i79 + R2.size(0) * i77], _mm256_add_pd(r19, _mm256_mul_pd
                                      (_mm256_set1_pd(0.5), r18)));
                }

                for (i79 = i_scalarLB; i79 < kc_loop_ub; i79++) {
                    R2[i79 + R2.size(0) * i77] = r1[i79 + r1.size(0) * i77] + 0.5 * r2[i79 + r2.size
                        (0) * i77];
                }
            }

            jc_loop_ub = r2Dn.size(1);
            b_r2Dn.set_size(r2Dn.size(1));
            for (int i78 = 0; i78 < jc_loop_ub; i78++) {
                b_r2Dn[i78] = r2Dn[3 * i78 + 2];
            }

            b_bsxfun(b_r2Dn, BasisVal, r1);
            lc_loop_ub = r1Dn.size(1);
            b_r1Dn.set_size(r1Dn.size(1));
            for (int i80 = 0; i80 < lc_loop_ub; i80++) {
                b_r1Dn[i80] = r1Dn[3 * i80 + 2];
            }

            b_bsxfun(b_r1Dn, BasisValD, r2);
            R3.set_size(r1.size(0), r1.size(1));
            mc_loop_ub = r1.size(1);
            for (int i81 = 0; i81 < mc_loop_ub; i81++) {
                int nc_loop_ub;
                int j_scalarLB;
                int j_vectorUB;
                nc_loop_ub = r1.size(0);
                j_scalarLB = r1.size(0) & -4;
                j_vectorUB = j_scalarLB - 4;
                for (i83 = 0; i83 <= j_vectorUB; i83 += 4) {
                    __m256d r20;
                    __m256d r21;
                    r20 = _mm256_loadu_pd(&r2[i83 + r2.size(0) * i81]);
                    r21 = _mm256_loadu_pd(&r1[i83 + r1.size(0) * i81]);
                    _mm256_storeu_pd(&R3[i83 + R3.size(0) * i81], _mm256_add_pd(r21, _mm256_mul_pd
                                      (_mm256_set1_pd(0.5), r20)));
                }

                for (i83 = j_scalarLB; i83 < nc_loop_ub; i83++) {
                    R3[i83 + R3.size(0) * i81] = r1[i83 + r1.size(0) * i81] + 0.5 * r2[i83 + r2.size
                        (0) * i81];
                }
            }

            //
            varargin_3.set_size(R1.size(0), R1.size(1));
            oc_loop_ub = R1.size(1);
            for (int i82 = 0; i82 < oc_loop_ub; i82++) {
                int pc_loop_ub;
                int k_scalarLB;
                int k_vectorUB;
                pc_loop_ub = R1.size(0);
                k_scalarLB = R1.size(0) & -4;
                k_vectorUB = k_scalarLB - 4;
                for (i85 = 0; i85 <= k_vectorUB; i85 += 4) {
                    __m256d r22;
                    r22 = _mm256_loadu_pd(&R1[i85 + R1.size(0) * i82]);
                    _mm256_storeu_pd(&varargin_3[i85 + varargin_3.size(0) * i82], _mm256_mul_pd(r22,
                                      _mm256_set1_pd(-1.0)));
                }

                for (i85 = k_scalarLB; i85 < pc_loop_ub; i85++) {
                    varargin_3[i85 + varargin_3.size(0) * i82] = -R1[i85 + R1.size(0) * i82];
                }
            }

            varargin_5.set_size(R2.size(0), R2.size(1));
            qc_loop_ub = R2.size(1);
            for (int i84 = 0; i84 < qc_loop_ub; i84++) {
                int rc_loop_ub;
                int l_scalarLB;
                int l_vectorUB;
                rc_loop_ub = R2.size(0);
                l_scalarLB = R2.size(0) & -4;
                l_vectorUB = l_scalarLB - 4;
                for (i87 = 0; i87 <= l_vectorUB; i87 += 4) {
                    __m256d r23;
                    r23 = _mm256_loadu_pd(&R2[i87 + R2.size(0) * i84]);
                    _mm256_storeu_pd(&varargin_5[i87 + varargin_5.size(0) * i84], _mm256_mul_pd(r23,
                                      _mm256_set1_pd(-1.0)));
                }

                for (i87 = l_scalarLB; i87 < rc_loop_ub; i87++) {
                    varargin_5[i87 + varargin_5.size(0) * i84] = -R2[i87 + R2.size(0) * i84];
                }
            }

            varargin_7.set_size(R3.size(0), R3.size(1));
            sc_loop_ub = R3.size(1);
            for (int i86 = 0; i86 < sc_loop_ub; i86++) {
                int tc_loop_ub;
                int m_scalarLB;
                int m_vectorUB;
                tc_loop_ub = R3.size(0);
                m_scalarLB = R3.size(0) & -4;
                m_vectorUB = m_scalarLB - 4;
                for (i88 = 0; i88 <= m_vectorUB; i88 += 4) {
                    __m256d r24;
                    r24 = _mm256_loadu_pd(&R3[i88 + R3.size(0) * i86]);
                    _mm256_storeu_pd(&varargin_7[i88 + varargin_7.size(0) * i86], _mm256_mul_pd(r24,
                                      _mm256_set1_pd(-1.0)));
                }

                for (i88 = m_scalarLB; i88 < tc_loop_ub; i88++) {
                    varargin_7[i88 + varargin_7.size(0) * i86] = -R3[i88 + R3.size(0) * i86];
                }
            }

            if ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0)) {
                b_result = BasisVal.size(1);
            } else if ((R1.size(0) != 0) && (R1.size(1) != 0)) {
                b_result = R1.size(1);
            } else if ((varargin_3.size(0) != 0) && (varargin_3.size(1) != 0)) {
                b_result = varargin_3.size(1);
            } else if ((R2.size(0) != 0) && (R2.size(1) != 0)) {
                b_result = R2.size(1);
            } else if ((varargin_5.size(0) != 0) && (varargin_5.size(1) != 0)) {
                b_result = varargin_5.size(1);
            } else if ((R3.size(0) != 0) && (R3.size(1) != 0)) {
                b_result = R3.size(1);
            } else if ((varargin_7.size(0) != 0) && (varargin_7.size(1) != 0)) {
                b_result = varargin_7.size(1);
            } else {
                int b_u0;
                b_u0 = BasisVal.size(1);
                if (b_u0 > 0) {
                    b_result = b_u0;
                } else {
                    b_result = 0;
                }

                if (R1.size(1) > b_result) {
                    b_result = R1.size(1);
                }

                if (varargin_3.size(1) > b_result) {
                    b_result = varargin_3.size(1);
                }

                if (R2.size(1) > b_result) {
                    b_result = R2.size(1);
                }

                if (varargin_5.size(1) > b_result) {
                    b_result = varargin_5.size(1);
                }

                if (R3.size(1) > b_result) {
                    b_result = R3.size(1);
                }

                if (varargin_7.size(1) > b_result) {
                    b_result = varargin_7.size(1);
                }
            }

            b_empty_non_axis_sizes = (b_result == 0);
            if (b_empty_non_axis_sizes || ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0))) {
                i_input_sizes_idx_0 = BasisVal.size(0);
            } else {
                i_input_sizes_idx_0 = 0;
            }

            if (b_empty_non_axis_sizes || ((R1.size(0) != 0) && (R1.size(1) != 0))) {
                j_input_sizes_idx_0 = R1.size(0);
            } else {
                j_input_sizes_idx_0 = 0;
            }

            if (b_empty_non_axis_sizes || ((varargin_3.size(0) != 0) && (varargin_3.size(1) != 0)))
            {
                k_input_sizes_idx_0 = varargin_3.size(0);
            } else {
                k_input_sizes_idx_0 = 0;
            }

            if (b_empty_non_axis_sizes || ((R2.size(0) != 0) && (R2.size(1) != 0))) {
                l_input_sizes_idx_0 = R2.size(0);
            } else {
                l_input_sizes_idx_0 = 0;
            }

            if (b_empty_non_axis_sizes || ((varargin_5.size(0) != 0) && (varargin_5.size(1) != 0)))
            {
                m_input_sizes_idx_0 = varargin_5.size(0);
            } else {
                m_input_sizes_idx_0 = 0;
            }

            if (b_empty_non_axis_sizes || ((R3.size(0) != 0) && (R3.size(1) != 0))) {
                n_input_sizes_idx_0 = R3.size(0);
            } else {
                n_input_sizes_idx_0 = 0;
            }

            if (b_empty_non_axis_sizes || ((varargin_7.size(0) != 0) && (varargin_7.size(1) != 0)))
            {
                o_input_sizes_idx_0 = varargin_7.size(0);
            } else {
                o_input_sizes_idx_0 = 0;
            }

            a_tmp = (static_cast<double>(b_k) + 1.0) * 7.0;
            n_a = a_tmp * static_cast<double>(BasisVal.size(0)) + 1.0;
            b_tmp = ((static_cast<double>(b_k) + 1.0) + 1.0) * 7.0;
            c_b = b_tmp * static_cast<double>(BasisVal.size(0));
            if (c_b < n_a) {
                y.set_size(1, 0);
            } else {
                int uc_loop_ub;
                uc_loop_ub = static_cast<int>(c_b - n_a);
                y.set_size(1, (uc_loop_ub + 1));
                for (int i89 = 0; i89 <= uc_loop_ub; i89++) {
                    y[i89] = n_a + static_cast<double>(i89);
                }
            }

            o_a = (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
            d_b = ((static_cast<double>(b_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1));
            if (d_b < o_a) {
                b_y.set_size(1, 0);
            } else {
                int vc_loop_ub;
                vc_loop_ub = static_cast<int>(d_b - o_a);
                b_y.set_size(1, (vc_loop_ub + 1));
                for (int i90 = 0; i90 <= vc_loop_ub; i90++) {
                    b_y[i90] = o_a + static_cast<double>(i90);
                }
            }

            b_BasisVal.set_size(((((((i_input_sizes_idx_0 + j_input_sizes_idx_0) +
                k_input_sizes_idx_0) + l_input_sizes_idx_0) + m_input_sizes_idx_0) +
                                  n_input_sizes_idx_0) + o_input_sizes_idx_0), b_result);
            for (int i91 = 0; i91 < b_result; i91++) {
                for (int i93 = 0; i93 < i_input_sizes_idx_0; i93++) {
                    b_BasisVal[i93 + b_BasisVal.size(0) * i91] = BasisVal[i93 + i_input_sizes_idx_0 *
                        i91];
                }
            }

            for (int i92 = 0; i92 < b_result; i92++) {
                for (int i95 = 0; i95 < j_input_sizes_idx_0; i95++) {
                    b_BasisVal[(i95 + i_input_sizes_idx_0) + b_BasisVal.size(0) * i92] = R1[i95 +
                        j_input_sizes_idx_0 * i92];
                }
            }

            for (int i94 = 0; i94 < b_result; i94++) {
                for (int i97 = 0; i97 < k_input_sizes_idx_0; i97++) {
                    b_BasisVal[((i97 + i_input_sizes_idx_0) + j_input_sizes_idx_0) + b_BasisVal.size
                        (0) * i94] = varargin_3[i97 + k_input_sizes_idx_0 * i94];
                }
            }

            for (int i96 = 0; i96 < b_result; i96++) {
                for (int i99 = 0; i99 < l_input_sizes_idx_0; i99++) {
                    b_BasisVal[(((i99 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                                k_input_sizes_idx_0) + b_BasisVal.size(0) * i96] = R2[i99 +
                        l_input_sizes_idx_0 * i96];
                }
            }

            for (int i98 = 0; i98 < b_result; i98++) {
                for (int i101 = 0; i101 < m_input_sizes_idx_0; i101++) {
                    b_BasisVal[((((i101 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                                 k_input_sizes_idx_0) + l_input_sizes_idx_0) + b_BasisVal.size(0) *
                        i98] = varargin_5[i101 + m_input_sizes_idx_0 * i98];
                }
            }

            for (int i100 = 0; i100 < b_result; i100++) {
                for (int i103 = 0; i103 < n_input_sizes_idx_0; i103++) {
                    b_BasisVal[(((((i103 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                                  k_input_sizes_idx_0) + l_input_sizes_idx_0) + m_input_sizes_idx_0)
                        + b_BasisVal.size(0) * i100] = R3[i103 + n_input_sizes_idx_0 * i100];
                }
            }

            for (int i102 = 0; i102 < b_result; i102++) {
                for (int i104 = 0; i104 < o_input_sizes_idx_0; i104++) {
                    b_BasisVal[((((((i104 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                                   k_input_sizes_idx_0) + l_input_sizes_idx_0) + m_input_sizes_idx_0)
                                + n_input_sizes_idx_0) + b_BasisVal.size(0) * i102] =
                        varargin_7[i104 + o_input_sizes_idx_0 * i102];
                }
            }

            A->parenAssign(b_BasisVal, y, b_y);

            //
            d4 = a_tmp * static_cast<double>(BasisVal.size(0)) + 1.0;
            if (d4 > b_tmp * static_cast<double>(BasisVal.size(0))) {
                i105 = 0;
            } else {
                i105 = static_cast<int>(d4) - 1;
            }

            r12.set_size(r1Dn_sqnorm.size(1));
            wc_loop_ub = r1Dn_sqnorm.size(1);
            for (int i106 = 0; i106 < wc_loop_ub; i106++) {
                r12[i106] = r1Dn_sqnorm[i106];
            }

            unnamed_idx_1 = r12.size(0);
            xc_loop_ub = r12.size(0);
            for (int i107 = 0; i107 < xc_loop_ub; i107++) {
                b[i105 + i107] = b_x / r12[i107];
            }

            for (int i108 = 0; i108 < ob_loop_ub; i108++) {
                b[(i105 + i108) + unnamed_idx_1] = bC2[i108];
            }

            for (int i109 = 0; i109 < pb_loop_ub; i109++) {
                b[((i105 + i109) + unnamed_idx_1) + b_unnamed_idx_1] = bC2[i109];
            }

            for (int i110 = 0; i110 < rb_loop_ub; i110++) {
                b[(((i105 + i110) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1] = bC3[i110];
            }

            for (int i111 = 0; i111 < sb_loop_ub; i111++) {
                b[((((i105 + i111) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
                    d_unnamed_idx_1] = bC3[i111];
            }

            for (int i112 = 0; i112 < tb_loop_ub; i112++) {
                b[(((((i105 + i112) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
                    d_unnamed_idx_1) + e_unnamed_idx_1] = bC4[i112];
            }

            for (int i113 = 0; i113 < ub_loop_ub; i113++) {
                b[((((((i105 + i113) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
                    d_unnamed_idx_1) + e_unnamed_idx_1) + f_unnamed_idx_1] = bC4[i113];
            }

            //
            d5 = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(BasisVal.size(1)) +
                1.0;
            if (d5 > (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1))) {
                i114 = 1;
            } else {
                i114 = static_cast<int>(d5);
            }

            i115 = static_cast<int>(static_cast<unsigned int>(b_k + 1) << 1);
            p_a = std::pow((t_1[0] * r1D[3 * (r1D.size(1) - 1)] + t_1[1] * r1D[3 * (r1D.size(1) - 1)
                            + 1]) + t_1[2] * r1D[3 * (r1D.size(1) - 1) + 2], 2.0);
            yc_loop_ub = BasisVal.size(1);
            for (int i116 = 0; i116 < yc_loop_ub; i116++) {
                Aeq[i115 + Aeq.size(0) * ((i114 + i116) - 1)] = p_a * BasisVal[(BasisVal.size(0) +
                    BasisVal.size(0) * i116) - 1];
            }

            d6 = (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
            if (d6 > ((static_cast<double>(b_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1)))
            {
                i117 = 1;
            } else {
                i117 = static_cast<int>(d6);
            }

            c = std::pow((t_1[0] * r1Dn[0] + t_1[1] * r1Dn[1]) + t_1[2] * r1Dn[2], 2.0);
            ad_loop_ub = BasisVal.size(1);
            for (int i118 = 0; i118 < ad_loop_ub; i118++) {
                Aeq[i115 + Aeq.size(0) * ((i117 + i118) - 1)] = -c * BasisVal[BasisVal.size(0) *
                    i118];
            }

            q_a = r2D[3 * (r2D.size(1) - 1)];
            r_a = 0.5 * r1D[3 * (r1D.size(1) - 1)];
            s_a = r2D[3 * (r2D.size(1) - 1) + 1];
            t_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 1];
            u_a = r2D[3 * (r2D.size(1) - 1) + 2];
            v_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 2];
            d7 = ((static_cast<double>(b_k) + 1.0) - 1.0) * static_cast<double>(BasisVal.size(1)) +
                1.0;
            if (d7 > (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1))) {
                i119 = 1;
            } else {
                i119 = static_cast<int>(d7);
            }

            i120 = i115 + 1;
            bd_loop_ub = BasisVal.size(1);
            g_a.set_size(3, BasisVal.size(1));
            for (int i121 = 0; i121 < bd_loop_ub; i121++) {
                double d8;
                double d9;
                d8 = BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i121) - 1];
                d9 = BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i121) - 1];
                g_a[3 * i121] = q_a * d8 + r_a * d9;
                g_a[3 * i121 + 1] = s_a * d8 + t_a * d9;
                g_a[3 * i121 + 2] = u_a * d8 + v_a * d9;
            }

            mtimes(t_1, g_a, r14);
            cd_loop_ub = r14.size(1);
            for (int i122 = 0; i122 < cd_loop_ub; i122++) {
                Aeq[i120 + Aeq.size(0) * ((i119 + i122) - 1)] = r14[i122];
            }

            //
            w_a = r2Dn[0];
            x_a = 0.5 * r1Dn[0];
            y_a = r2Dn[1];
            ab_a = 0.5 * r1Dn[1];
            bb_a = r2Dn[2];
            cb_a = 0.5 * r1Dn[2];
            d10 = (static_cast<double>(b_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
            if (d10 > ((static_cast<double>(b_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1)))
            {
                i123 = 1;
            } else {
                i123 = static_cast<int>(d10);
            }

            dd_loop_ub = BasisVal.size(1);
            reshapes[0].f1.set_size(1, BasisVal.size(1));
            reshapes[1].f1.set_size(1, BasisVal.size(1));
            reshapes[2].f1.set_size(1, BasisVal.size(1));
            for (int i124 = 0; i124 < dd_loop_ub; i124++) {
                double d11;
                double d12;
                d11 = BasisVal[BasisVal.size(0) * i124];
                d12 = BasisValD[BasisValD.size(0) * i124];
                reshapes[0].f1[i124] = w_a * d11 + x_a * d12;
                reshapes[1].f1[i124] = y_a * d11 + ab_a * d12;
                reshapes[2].f1[i124] = bb_a * d11 + cb_a * d12;
            }

            ed_loop_ub = reshapes[0].f1.size(1);
            b_reshapes.set_size(3, reshapes[0].f1.size(1));
            for (int i125 = 0; i125 < ed_loop_ub; i125++) {
                b_reshapes[3 * i125] = reshapes[0].f1[i125];
            }

            fd_loop_ub = reshapes[1].f1.size(1);
            for (int i126 = 0; i126 < fd_loop_ub; i126++) {
                b_reshapes[3 * i126 + 1] = reshapes[1].f1[i126];
            }

            gd_loop_ub = reshapes[2].f1.size(1);
            for (int i127 = 0; i127 < gd_loop_ub; i127++) {
                b_reshapes[3 * i127 + 2] = reshapes[2].f1[i127];
            }

            mtimes(t_1, b_reshapes, r14);
            hd_loop_ub = r14.size(1);
            for (int i128 = 0; i128 < hd_loop_ub; i128++) {
                Aeq[i120 + Aeq.size(0) * ((i123 + i128) - 1)] = -r14[i128];
            }

            //
            r1D.set_size(3, r1Dn.size(1));
            id_loop_ub = r1Dn.size(1);
            for (int i129 = 0; i129 < id_loop_ub; i129++) {
                r1D[3 * i129] = r1Dn[3 * i129];
                r1D[3 * i129 + 1] = r1Dn[3 * i129 + 1];
                r1D[3 * i129 + 2] = r1Dn[3 * i129 + 2];
            }

            jd_loop_ub = r2Dn.size(1);
            r2D.set_size(3, r2Dn.size(1));
            for (int i130 = 0; i130 < jd_loop_ub; i130++) {
                r2D[3 * i130] = r2Dn[3 * i130];
                r2D[3 * i130 + 1] = r2Dn[3 * i130 + 1];
                r2D[3 * i130 + 2] = r2Dn[3 * i130 + 2];
            }
        }

        //
        //  unit tangent vector @ end of previous piece
        //
        h_a = r2D[3 * (r2D.size(1) - 1)];
        i_a = 0.5 * r1D[3 * (r1D.size(1) - 1)];
        j_a = r2D[3 * (r2D.size(1) - 1) + 1];
        k_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 1];
        l_a = r2D[3 * (r2D.size(1) - 1) + 2];
        m_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 2];
        d1 = static_cast<double>(Aeq.size(1) - N) + 1.0;
        if (d1 > Aeq.size(1)) {
            i64 = 0;
        } else {
            i64 = static_cast<int>(d1) - 1;
        }

        b_unnamed_idx_0 = Aeq.size(0) - 2;
        unnamed_idx_1 = Aeq.size(0) - 1;
        e_r1D = r1D.size(1);
        d3 = b_norm(*(double (*)[3])&r1D[3 * (e_r1D - 1)]);
        c_r1D[0] = r1D[3 * (r1D.size(1) - 1)] / d3;
        c_r1D[1] = r1D[3 * (r1D.size(1) - 1) + 1] / d3;
        c_r1D[2] = r1D[3 * (r1D.size(1) - 1) + 2] / d3;
        xb_loop_ub = BasisVal.size(1);
        yb_loop_ub = BasisVal.size(1);
        ac_loop_ub = BasisVal.size(1);
        g_a.set_size(3, BasisVal.size(1));
        for (int i67 = 0; i67 < xb_loop_ub; i67++) {
            g_a[3 * i67] = h_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i67) - 1] + i_a *
                BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i67) - 1];
        }

        for (int i68 = 0; i68 < yb_loop_ub; i68++) {
            g_a[3 * i68 + 1] = j_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i68) - 1] + k_a
                * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i68) - 1];
        }

        for (int i70 = 0; i70 < ac_loop_ub; i70++) {
            g_a[3 * i70 + 2] = l_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i70) - 1] + m_a
                * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i70) - 1];
        }

        mtimes(c_r1D, g_a, r14);
        dc_loop_ub = BasisVal.size(1);
        for (int i72 = 0; i72 < dc_loop_ub; i72++) {
            Aeq[b_unnamed_idx_0 + Aeq.size(0) * (i64 + i72)] = BasisVal[(BasisVal.size(0) +
                BasisVal.size(0) * i72) - 1];
        }

        gc_loop_ub = r14.size(1);
        for (int i73 = 0; i73 < gc_loop_ub; i73++) {
            Aeq[unnamed_idx_1 + Aeq.size(0) * (i64 + i73)] = r14[i73];
        }

        int b_beq;

        //
        b_beq = beq.size(0) - 1;
        beq[beq.size(0) - 2] = std::pow(v_1, 2.0) / r1Dn_sqnorm[r1Dn_sqnorm.size(1) - 1];
        beq[b_beq] = at_1;
    }

    //
    // CALCALPHA0
    //     ALPHA0_S = CALCALPHA0(ALPHA1,IN2)
    // Arguments    : const double alpha1_data[]
    //                const int alpha1_size[1]
    //                const double in2[16]
    //                double alpha0_s_data[]
    //                int alpha0_s_size[1]
    // Return Type  : void
    //
    static void CalcAlpha0(const double alpha1_data[], const int alpha1_size[1], const double in2[16],
                           double alpha0_s_data[], int alpha0_s_size[1])
    {
        int loop_ub;
        double z1_data[9];
        double t5_data[9];
        int N;
        double b_in2;
        double c_in2;
        int t10_size_idx_0;
        int b_loop_ub;
        int scalarLB_tmp;
        int vectorUB;
        int i;
        double t10_data[9];
        double d_in2;
        double e_in2;
        int t11_size_idx_0;
        int c_loop_ub;
        int b_vectorUB;
        int i1;
        double t11_data[9];
        int b_N;
        double f_in2;
        double b_z1_data[9];
        double g_in2;
        double h_in2;
        double i_in2;
        int d_loop_ub;
        int c_vectorUB;
        int i2;
        double t12_data[9];
        double j_in2;
        double c_z1_data[9];
        double k_in2;
        double l_in2;
        double m_in2;
        double n_in2;
        double o_in2;
        double p_in2;
        double q_in2;
        double r_in2;
        double s_in2;
        int e_loop_ub;
        int d_vectorUB;
        int i3;

        //     This function was generated by the Symbolic Math Toolbox version 8.3.
        //     25-May-2019 09:07:35
        loop_ub = alpha1_size[0];
        if (0 <= loop_ub - 1) {
            std::memcpy(&z1_data[0], &t5_data[0], loop_ub * sizeof(double));
        }

        N = alpha1_size[0];
        for (int k = 0; k < N; k++) {
            z1_data[k] = std::pow(alpha1_data[k], 2.0);
        }

        b_in2 = in2[3];
        c_in2 = in2[2];
        t10_size_idx_0 = alpha1_size[0];
        b_loop_ub = alpha1_size[0];
        scalarLB_tmp = alpha1_size[0] & -4;
        vectorUB = scalarLB_tmp - 4;
        for (i = 0; i <= vectorUB; i += 4) {
            _mm256_storeu_pd(&t10_data[i], _mm256_add_pd(_mm256_set1_pd(b_in2), _mm256_mul_pd
                              (_mm256_loadu_pd((double *)&alpha1_data[i]), _mm256_set1_pd(c_in2))));
        }

        for (i = scalarLB_tmp; i < b_loop_ub; i++) {
            t10_data[i] = b_in2 + alpha1_data[i] * c_in2;
        }

        d_in2 = in2[1];
        e_in2 = in2[0];
        t11_size_idx_0 = alpha1_size[0];
        c_loop_ub = alpha1_size[0];
        b_vectorUB = scalarLB_tmp - 4;
        for (i1 = 0; i1 <= b_vectorUB; i1 += 4) {
            _mm256_storeu_pd(&t11_data[i1], _mm256_div_pd(_mm256_set1_pd(1.0), _mm256_add_pd
                              (_mm256_set1_pd(d_in2), _mm256_mul_pd(_mm256_set1_pd(e_in2),
                                _mm256_loadu_pd((double *)&alpha1_data[i1])))));
        }

        for (i1 = scalarLB_tmp; i1 < c_loop_ub; i1++) {
            t11_data[i1] = 1.0 / (d_in2 + e_in2 * alpha1_data[i1]);
        }

        b_N = alpha1_size[0];
        for (int b_k = 0; b_k < b_N; b_k++) {
            b_z1_data[b_k] = std::pow(alpha1_data[b_k], 3.0);
        }

        f_in2 = in2[7];
        g_in2 = in2[6];
        h_in2 = in2[5];
        i_in2 = in2[4];
        d_loop_ub = alpha1_size[0];
        c_vectorUB = scalarLB_tmp - 4;
        for (i2 = 0; i2 <= c_vectorUB; i2 += 4) {
            __m256d r;
            __m256d r1;
            r = _mm256_loadu_pd(&z1_data[i2]);
            r1 = _mm256_loadu_pd(&b_z1_data[i2]);
            _mm256_storeu_pd(&t12_data[i2], _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_set1_pd
                                (f_in2), _mm256_mul_pd(_mm256_loadu_pd((double *)&alpha1_data[i2]),
                                 _mm256_set1_pd(g_in2))), _mm256_mul_pd(_mm256_set1_pd(h_in2), r)),
                              _mm256_mul_pd(_mm256_set1_pd(i_in2), r1)));
        }

        for (i2 = scalarLB_tmp; i2 < d_loop_ub; i2++) {
            t12_data[i2] = ((f_in2 + alpha1_data[i2] * g_in2) + h_in2 * z1_data[i2]) + i_in2 *
                b_z1_data[i2];
        }

        for (int c_k = 0; c_k < t11_size_idx_0; c_k++) {
            b_z1_data[c_k] = std::pow(t11_data[c_k], 2.0);
        }

        for (int d_k = 0; d_k < t10_size_idx_0; d_k++) {
            c_z1_data[d_k] = std::pow(t10_data[d_k], 2.0);
        }

        j_in2 = in2[15];
        k_in2 = in2[11];
        l_in2 = in2[9];
        m_in2 = in2[13];
        n_in2 = in2[12];
        o_in2 = in2[14];
        p_in2 = in2[10];
        q_in2 = in2[8];
        r_in2 = in2[13];
        s_in2 = in2[12];
        alpha0_s_size[0] = alpha1_size[0];
        e_loop_ub = alpha1_size[0];
        d_vectorUB = scalarLB_tmp - 4;
        for (i3 = 0; i3 <= d_vectorUB; i3 += 4) {
            __m256d r2;
            __m256d r3;
            __m256d r4;
            __m256d r5;
            __m256d r6;
            __m256d r7;
            __m256d r8;
            r2 = _mm256_loadu_pd((double *)&alpha1_data[i3]);
            r3 = _mm256_loadu_pd(&z1_data[i3]);
            r4 = _mm256_loadu_pd(&t11_data[i3]);
            r5 = _mm256_loadu_pd(&t12_data[i3]);
            r6 = _mm256_loadu_pd(&t10_data[i3]);
            r7 = _mm256_loadu_pd(&b_z1_data[i3]);
            r8 = _mm256_loadu_pd(&c_z1_data[i3]);
            _mm256_storeu_pd(&alpha0_s_data[i3], _mm256_div_pd(_mm256_mul_pd(_mm256_add_pd
                               (_mm256_sub_pd(_mm256_add_pd(_mm256_add_pd(_mm256_set1_pd(j_in2),
                                   _mm256_mul_pd(r2, _mm256_set1_pd(k_in2))), _mm256_mul_pd
                                  (_mm256_set1_pd(l_in2), r3)), _mm256_mul_pd(_mm256_mul_pd
                                  (_mm256_set1_pd(m_in2), r4), r5)), _mm256_mul_pd(_mm256_mul_pd
                                 (_mm256_mul_pd(_mm256_set1_pd(n_in2), r6), r7), r5)),
                               _mm256_set1_pd(-1.0)), _mm256_sub_pd(_mm256_sub_pd(_mm256_add_pd
                                (_mm256_add_pd(_mm256_set1_pd(o_in2), _mm256_mul_pd(r2,
                                   _mm256_set1_pd(p_in2))), _mm256_mul_pd(_mm256_set1_pd(q_in2), r3)),
                                _mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(r_in2), r6), r4)),
                               _mm256_mul_pd(_mm256_mul_pd(_mm256_set1_pd(s_in2), r4), _mm256_sub_pd
                                (r5, _mm256_mul_pd(r8, r4))))));
        }

        for (i3 = scalarLB_tmp; i3 < e_loop_ub; i3++) {
            alpha0_s_data[i3] = -((((j_in2 + alpha1_data[i3] * k_in2) + l_in2 * z1_data[i3]) - m_in2
                                   * t11_data[i3] * t12_data[i3]) + n_in2 * t10_data[i3] *
                                  b_z1_data[i3] * t12_data[i3]) / ((((o_in2 + alpha1_data[i3] *
                p_in2) + q_in2 * z1_data[i3]) - r_in2 * t10_data[i3] * t11_data[i3]) - s_in2 *
                t11_data[i3] * (t12_data[i3] - c_z1_data[i3] * t11_data[i3]));
        }
    }

    //
    // Arguments    : int cfg_SplineDegree
    //                const coder::array<double, 2U> &points
    //                coder::array<double, 2U> &sp3D_CoeffX
    //                coder::array<double, 2U> &sp3D_CoeffY
    //                coder::array<double, 2U> &sp3D_CoeffZ
    //                int *sp3D_Bl_ncoeff
    //                coder::array<double, 2U> &sp3D_Bl_breakpoints
    //                unsigned long *sp3D_Bl_handle
    //                int *sp3D_Bl_degree
    //                coder::array<double, 2U> &sp3D_knots
    // Return Type  : void
    //
    static void CalcBspline_Lee(int cfg_SplineDegree, const coder::array<double, 2U> &points, coder::
        array<double, 2U> &sp3D_CoeffX, coder::array<double, 2U> &sp3D_CoeffY, coder::array<double,
        2U> &sp3D_CoeffZ, int *sp3D_Bl_ncoeff, coder::array<double, 2U> &sp3D_Bl_breakpoints,
        unsigned long *sp3D_Bl_handle, int *sp3D_Bl_degree, coder::array<double, 2U> &sp3D_knots)
    {
        int N;
        coder::array<double, 2U> x;
        int loop_ub;
        int dimSize;
        coder::array<double, 2U> b_y1;
        coder::array<double, 2U> z1;
        coder::array<double, 2U> b_z1;
        int b_loop_ub;
        int ixStart;
        coder::array<double, 2U> du;
        coder::array<double, 2U> c_z1;
        int c_N;
        coder::array<double, 2U> u;
        int c_loop_ub;
        double b_u;
        int d_loop_ub;
        int scalarLB;
        int vectorUB;
        int i6;
        int e_loop_ub;
        coder::array<double, 2U> breakpoints;
        int f_loop_ub;
        unsigned long Bl_handle;
        coder::array<double, 2U> BasisVal;
        int g_loop_ub;
        coder::array<double, 2U> BasisValDD0;
        int i_loop_ub;
        coder::array<double, 2U> BasisValDD1;
        int j_loop_ub;
        int i13;
        int i14;
        unsigned int unnamed_idx_1;
        int k_loop_ub;
        int l_loop_ub;
        coder::array<signed char, 2U> coef;
        int input_sizes_idx_0;
        coder::array<double, 2U> A;
        int m_loop_ub;
        coder::array<double, 1U> coeffs;
        int n_loop_ub;
        int p_loop_ub;
        coder::array<double, 2U> r1;
        double unusedU1;
        coder::array<double, 1U> b_coef;
        double X[4];
        double unusedU2;
        double unusedU3;
        double unusedU4;
        int t_loop_ub;
        coder::array<double, 1U> r2;
        coder::array<double, 1U> r3;
        int u_loop_ub;
        int v_loop_ub;
        int w_loop_ub;
        int x_loop_ub;
        int y_loop_ub;
        int b_sp3D_Bl_ncoeff;
        int ab_loop_ub;
        N = points.size(1);

        //  number of points in 3D space
        x.set_size(points.size(1), 3);
        loop_ub = points.size(1);
        for (int i = 0; i < 3; i++) {
            for (int i1 = 0; i1 < loop_ub; i1++) {
                x[i1 + x.size(0) * i] = points[i + 3 * i1];
            }
        }

        dimSize = x.size(0);
        if (x.size(0) == 0) {
            b_y1.set_size(0, 3);
        } else {
            int u0;
            int y;
            u0 = x.size(0) - 1;
            if (u0 < 1) {
                y = u0;
            } else {
                y = 1;
            }

            if (y < 1) {
                b_y1.set_size(0, 3);
            } else {
                b_y1.set_size((x.size(0) - 1), 3);
                if (x.size(0) - 1 != 0) {
                    int iyStart;
                    ixStart = 0;
                    iyStart = 0;
                    for (int r = 0; r < 3; r++) {
                        int ixLead;
                        int iyLead;
                        double work_data_idx_0;
                        ixLead = ixStart + 1;
                        iyLead = iyStart;
                        work_data_idx_0 = x[ixStart];
                        for (int m = 2; m <= dimSize; m++) {
                            double tmp1;
                            tmp1 = x[ixLead] - work_data_idx_0;
                            work_data_idx_0 = x[ixLead];
                            ixLead++;
                            b_y1[iyLead] = tmp1;
                            iyLead++;
                        }

                        ixStart += dimSize;
                        iyStart = (iyStart + dimSize) - 1;
                    }
                }
            }
        }

        z1.set_size(b_y1.size(0), 3);
        for (int k = 0; k < 3; k++) {
            int b_N;
            b_N = z1.size(0);
            for (int b_k = 0; b_k < b_N; b_k++) {
                z1[b_k + z1.size(0) * k] = std::pow(b_y1[b_k + b_y1.size(0) * k], 2.0);
            }
        }

        b_z1.set_size(3, z1.size(0));
        b_loop_ub = z1.size(0);
        for (int i2 = 0; i2 < b_loop_ub; i2++) {
            b_z1[3 * i2] = z1[i2];
            b_z1[3 * i2 + 1] = z1[i2 + z1.size(0)];
            b_z1[3 * i2 + 2] = z1[i2 + z1.size(0) * 2];
        }

        if (b_z1.size(1) == 0) {
            du.set_size(1, 0);
        } else {
            int i3;
            du.set_size(1, b_z1.size(1));
            i3 = b_z1.size(1);
            for (int c_k = 0; c_k < i3; c_k++) {
                du[c_k] = b_z1[3 * c_k];
                du[c_k] = du[c_k] + b_z1[3 * c_k + 1];
                du[c_k] = du[c_k] + b_z1[3 * c_k + 2];
            }
        }

        c_z1.set_size(1, du.size(1));
        c_N = du.size(1);
        for (int d_k = 0; d_k < c_N; d_k++) {
            c_z1[d_k] = std::pow(du[d_k], 0.25);
        }

        u.set_size(1, (c_z1.size(1) + 1));
        u[0] = 0.0;
        c_loop_ub = c_z1.size(1);
        for (int i4 = 0; i4 < c_loop_ub; i4++) {
            u[i4 + 1] = c_z1[i4];
        }

        if (u.size(1) != 1) {
            int i5;
            i5 = u.size(1);
            for (int e_k = 0; e_k <= i5 - 2; e_k++) {
                u[e_k + 1] = u[e_k] + u[e_k + 1];
            }
        }

        b_u = u[u.size(1) - 1];
        u.set_size(1, u.size(1));
        d_loop_ub = u.size(1);
        scalarLB = u.size(1) & -4;
        vectorUB = scalarLB - 4;
        for (i6 = 0; i6 <= vectorUB; i6 += 4) {
            __m256d b_r;
            b_r = _mm256_loadu_pd(&u[i6]);
            _mm256_storeu_pd(&u[i6], _mm256_div_pd(b_r, _mm256_set1_pd(b_u)));
        }

        for (i6 = scalarLB; i6 < d_loop_ub; i6++) {
            u[i6] = u[i6] / b_u;
        }

        //  normalize knots to interval [0...1]
        sp3D_knots.set_size(1, (u.size(1) + 6));
        sp3D_knots[0] = 0.0;
        sp3D_knots[1] = 0.0;
        sp3D_knots[2] = 0.0;
        e_loop_ub = u.size(1);
        for (int i7 = 0; i7 < e_loop_ub; i7++) {
            sp3D_knots[i7 + 3] = u[i7];
        }

        sp3D_knots[u.size(1) + 3] = 1.0;
        sp3D_knots[u.size(1) + 4] = 1.0;
        sp3D_knots[u.size(1) + 5] = 1.0;
        breakpoints.set_size(1, u.size(1));
        f_loop_ub = u.size(1);
        for (int i8 = 0; i8 < f_loop_ub; i8++) {
            breakpoints[i8] = u[i8];
        }

        c_bspline_create_with_breakpoints(&Bl_handle, cfg_SplineDegree, &breakpoints[0], u.size(1));
        BasisVal.set_size(points.size(1), (points.size(1) + 2));
        g_loop_ub = points.size(1) + 2;
        for (int i9 = 0; i9 < g_loop_ub; i9++) {
            int h_loop_ub;
            h_loop_ub = points.size(1);
            for (int i10 = 0; i10 < h_loop_ub; i10++) {
                BasisVal[i10 + BasisVal.size(0) * i9] = 0.0;
            }
        }

        //  preallocation
        BasisValDD0.set_size(1, (points.size(1) + 2));
        i_loop_ub = points.size(1) + 2;
        for (int i11 = 0; i11 < i_loop_ub; i11++) {
            BasisValDD0[i11] = 0.0;
        }

        //  preallocation
        BasisValDD1.set_size(1, (points.size(1) + 2));
        j_loop_ub = points.size(1) + 2;
        for (int i12 = 0; i12 < j_loop_ub; i12++) {
            BasisValDD1[i12] = 0.0;
        }

        //  preallocation
        //
        i13 = points.size(1) + 1;
        if (0 <= points.size(1) + 1) {
            i14 = u.size(1);
            unnamed_idx_1 = static_cast<unsigned int>(u.size(1));
        }

        if (0 <= i13) {
            k_loop_ub = N + 2;
            l_loop_ub = static_cast<int>(unnamed_idx_1);
        }

        for (int f_k = 0; f_k <= i13; f_k++) {
            int o_loop_ub;
            int q_loop_ub;
            int r_loop_ub;
            int s_loop_ub;

            //  evaluate basis functions at the knots
            coef.set_size(1, (N + 2));
            for (int i15 = 0; i15 < k_loop_ub; i15++) {
                coef[i15] = 0;
            }

            coef[f_k] = 1;

            //      sp             = spmak(knots, coef);
            //      BasisVal(:, k) = spval(sp, u);          % tridiagonal matrix
            coeffs.set_size(coef.size(1));
            o_loop_ub = coef.size(1);
            for (int i18 = 0; i18 < o_loop_ub; i18++) {
                coeffs[i18] = coef[i18];
            }

            r1.set_size(1, (static_cast<int>(unnamed_idx_1)));
            for (int i21 = 0; i21 < l_loop_ub; i21++) {
                r1[i21] = 0.0;
            }

            for (int g_k = 0; g_k < i14; g_k++) {
                double d;
                double xk;
                d = u[g_k];
                xk = d;

                //  void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
                if (d < 0.0) {
                    printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", d);
                    fflush(stdout);
                    xk = 0.0;
                } else {
                    if (d > 1.0) {
                        printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", d);
                        fflush(stdout);
                        xk = 1.0;
                    }
                }

                c_bspline_eval(&Bl_handle, &(coeffs.data())[0], xk, &X[0]);
                r1[g_k] = X[0];
            }

            q_loop_ub = BasisVal.size(0);
            for (int i23 = 0; i23 < q_loop_ub; i23++) {
                BasisVal[i23 + BasisVal.size(0) * f_k] = r1[i23];
            }

            //      sp2D           = fnder(sp, 2);          % evaluate 2nd derivative of basis functions @u=0,1 
            unusedU1 = 0.0;
            b_coef.set_size(coef.size(1));
            r_loop_ub = coef.size(1);
            for (int i24 = 0; i24 < r_loop_ub; i24++) {
                b_coef[i24] = coef[i24];
            }

            b_bspline_eval(Bl_handle, b_coef, &unusedU1, &unusedU2, &BasisValDD0[f_k]);
            unusedU3 = 1.0;
            b_coef.set_size(coef.size(1));
            s_loop_ub = coef.size(1);
            for (int i25 = 0; i25 < s_loop_ub; i25++) {
                b_coef[i25] = coef[i25];
            }

            b_bspline_eval(Bl_handle, b_coef, &unusedU3, &unusedU4, &BasisValDD1[f_k]);

            //      BasisValDD0(k) = spval(sp2D, 0);
            //      BasisValDD1(k) = spval(sp2D, 1);
        }

        //
        if ((BasisValDD0.size(1) == 0) || ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0))) {
            input_sizes_idx_0 = BasisVal.size(0);
        } else {
            input_sizes_idx_0 = 0;
        }

        A.set_size((input_sizes_idx_0 + 2), BasisValDD0.size(1));
        m_loop_ub = BasisValDD0.size(1);
        for (int i16 = 0; i16 < m_loop_ub; i16++) {
            A[A.size(0) * i16] = BasisValDD0[i16];
        }

        n_loop_ub = BasisValDD0.size(1);
        for (int i17 = 0; i17 < n_loop_ub; i17++) {
            for (int i19 = 0; i19 < input_sizes_idx_0; i19++) {
                A[(i19 + A.size(0) * i17) + 1] = BasisVal[i19 + input_sizes_idx_0 * i17];
            }
        }

        p_loop_ub = BasisValDD0.size(1);
        for (int i20 = 0; i20 < p_loop_ub; i20++) {
            for (int i22 = 0; i22 < 1; i22++) {
                A[(input_sizes_idx_0 + A.size(0) * i20) + 1] = BasisValDD1[i20];
            }
        }

        //  warning('NOT using a sparse matrix here because it pulled the CXSparse project into generation') 
        //  A = sparse(A);
        //  figure;
        //  spy(A)
        //
        //
        //  mmdflag = spparms('autommd'); % protect current spparms setting
        //  spparms('autommd',0);         % suppress pivoting
        //
        // tic
        //  solve sparse banded linear system
        //  solve sparse banded linear system
        //  solve sparse banded linear system
        // toc
        //
        //  spparms('autommd',mmdflag);   % restore spparms setting
        //
        //  sp3D = spmak(knots, [cx'; cy'; cz']);
        //  coder.varsize('cx', 'cy', 'cz', [1, Inf], [0, 1]);
        t_loop_ub = points.size(1);
        r2.set_size((points.size(1) + 2));
        r2[0] = 0.0;
        for (int i26 = 0; i26 < t_loop_ub; i26++) {
            r2[i26 + 1] = points[3 * i26];
        }

        r2[points.size(1) + 1] = 0.0;
        mldiv(A, r2, r3);
        sp3D_CoeffX.set_size(1, r3.size(0));
        u_loop_ub = r3.size(0);
        for (int i27 = 0; i27 < u_loop_ub; i27++) {
            sp3D_CoeffX[i27] = r3[i27];
        }

        v_loop_ub = points.size(1);
        r2.set_size((points.size(1) + 2));
        r2[0] = 0.0;
        for (int i28 = 0; i28 < v_loop_ub; i28++) {
            r2[i28 + 1] = points[3 * i28 + 1];
        }

        r2[points.size(1) + 1] = 0.0;
        mldiv(A, r2, r3);
        sp3D_CoeffY.set_size(1, r3.size(0));
        w_loop_ub = r3.size(0);
        for (int i29 = 0; i29 < w_loop_ub; i29++) {
            sp3D_CoeffY[i29] = r3[i29];
        }

        x_loop_ub = points.size(1);
        r2.set_size((points.size(1) + 2));
        r2[0] = 0.0;
        for (int i30 = 0; i30 < x_loop_ub; i30++) {
            r2[i30 + 1] = points[3 * i30 + 2];
        }

        r2[points.size(1) + 1] = 0.0;
        mldiv(A, r2, r3);
        sp3D_CoeffZ.set_size(1, r3.size(0));
        y_loop_ub = r3.size(0);
        for (int i31 = 0; i31 < y_loop_ub; i31++) {
            sp3D_CoeffZ[i31] = r3[i31];
        }

        b_sp3D_Bl_ncoeff = (u.size(1) + cfg_SplineDegree) - 2;
        sp3D_Bl_breakpoints.set_size(1, u.size(1));
        ab_loop_ub = u.size(1);
        for (int i32 = 0; i32 < ab_loop_ub; i32++) {
            sp3D_Bl_breakpoints[i32] = u[i32];
        }

        *sp3D_Bl_ncoeff = b_sp3D_Bl_ncoeff;
        *sp3D_Bl_handle = Bl_handle;
        *sp3D_Bl_degree = cfg_SplineDegree;
    }

    //
    // Arguments    : const double rD1[3]
    //                const double rD2[3]
    //                double t[3]
    //                double n[3]
    //                double *kappa
    // Return Type  : void
    //
    static void CalcFrenet(const double rD1[3], const double rD2[3], double t[3], double n[3],
                           double *kappa)
    {
        double n_tmp;

        //  computes the local Frenet frame (t, n, b) of a curve in R^3
        //  [t, n, b, kappa] = CalcFrenet(rD1, rD2)
        //  where rD1 is the first derivative and rD2 the second one
        n_tmp = std::sqrt((std::pow(rD1[0], 2.0) + std::pow(rD1[1], 2.0)) + std::pow(rD1[2], 2.0));

        //  tangential unit vector
        //
        t[0] = rD1[0] / n_tmp;
        t[1] = rD1[1] / n_tmp;
        t[2] = rD1[2] / n_tmp;
        if (std::abs(std::abs((t[0] * rD2[0] + t[1] * rD2[1]) + t[2] * rD2[2]) - std::sqrt((std::pow
                (rD2[0], 2.0) + std::pow(rD2[1], 2.0)) + std::pow(rD2[2], 2.0))) >
                2.2204460492503131E-16) {
            double b_idx_0_tmp;
            double b_idx_1_tmp;
            double b_idx_2_tmp;
            double b_n_tmp;
            double b_idx_0;
            double b_idx_1;
            double b_idx_2;

            //  regular case
            b_idx_0_tmp = rD1[1] * rD2[2] - rD1[2] * rD2[1];
            b_idx_1_tmp = rD1[2] * rD2[0] - rD1[0] * rD2[2];
            b_idx_2_tmp = rD1[0] * rD2[1] - rD1[1] * rD2[0];
            b_n_tmp = std::sqrt((std::pow(b_idx_0_tmp, 2.0) + std::pow(b_idx_1_tmp, 2.0)) + std::pow
                                (b_idx_2_tmp, 2.0));
            b_idx_0 = b_idx_0_tmp / b_n_tmp;
            b_idx_1 = b_idx_1_tmp / b_n_tmp;
            b_idx_2 = b_idx_2_tmp / b_n_tmp;

            //  binormal unit vector
            n[0] = b_idx_1 * t[2] - b_idx_2 * t[1];
            n[1] = b_idx_2 * t[0] - b_idx_0 * t[2];
            n[2] = b_idx_0 * t[1] - b_idx_1 * t[0];

            //  normal unit vector
            *kappa = b_n_tmp / std::pow(n_tmp, 3.0);

            //  curvature
        } else {
            //  special case if rD2 = 0
            n[0] = 0.0;
            n[1] = 0.0;
            n[2] = 0.0;

            //  normal unit vector not defined
            *kappa = 0.0;
        }
    }

    //
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType Curv_Type
    //                const double Curv_P0[3]
    //                const double Curv_P1[3]
    //                const double Curv_evec[3]
    //                double Curv_theta
    //                double Curv_pitch
    //                const double Curv_CoeffP5[6][3]
    //                int Curv_sp_index
    //                bool Curv_UseConstJerk
    //                double Curv_ConstJerk
    //                double Curv_a_param
    //                double Curv_b_param
    //                double JerkScale
    //                double *v_0
    //                double *at_0
    // Return Type  : void
    //
    static void CalcZeroStartConstraints(const queue_coder *ctx_q_splines, CurveType Curv_Type,
        const double Curv_P0[3], const double Curv_P1[3], const double Curv_evec[3], double
        Curv_theta, double Curv_pitch, const double Curv_CoeffP5[6][3], int Curv_sp_index, bool
        Curv_UseConstJerk, double Curv_ConstJerk, double Curv_a_param, double Curv_b_param, double
        JerkScale, double *v_0, double *at_0)
    {
        double jps;
        double t;
        char message[50];
        static const char b_message[50] = { 'C', 'a', 'l', 'c', 'Z', 'e', 'r', 'o', 'S', 't', 'a',
            'r', 't', 'C', 'o', 'n', 's', 't', 'r', 'a', 'i', 'n', 't', 's', ':', ' ', 'C', 'a', 'l',
            'l', 'e', 'd', ' ', 'o', 'n', ' ', 'n', 'o', 'n', '-', 'c', 'o', 'n', 's', 't', ' ', 'j',
            'e', 'r', 'k' };

        double d1uk;
        double b;
        double unusedU0[3];
        double r1D[3];
        double r2D[3];
        double b_b;
        double n;
        double scale;
        double absxk;
        double b_t;
        if (!Curv_UseConstJerk) {
            for (int i = 0; i < 50; i++) {
                message[i] = b_message[i];
            }

            c_assert_(&message[0]);
        }

        jps = Curv_ConstJerk * JerkScale;
        t = std::pow(6.0 / jps, 0.33333333333333331);
        d1uk = jps * std::pow(t, 2.0) / 2.0;
        b = jps * t;
        d_EvalCurvStruct(ctx_q_splines, Curv_Type, Curv_P0, Curv_P1, Curv_evec, Curv_theta,
                         Curv_pitch, Curv_CoeffP5, Curv_sp_index, Curv_a_param, Curv_b_param,
                         unusedU0, r1D, r2D);
        b_b = std::pow(d1uk, 2.0);
        *v_0 = std::sqrt((std::pow(r1D[0] * d1uk, 2.0) + std::pow(r1D[1] * d1uk, 2.0)) + std::pow
                         (r1D[2] * d1uk, 2.0));
        n = std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0));
        scale = 3.3121686421112381E-170;
        absxk = std::abs((r2D[0] * b_b + r1D[0] * b) * (r1D[0] / n));
        if (absxk > 3.3121686421112381E-170) {
            *at_0 = 1.0;
            scale = absxk;
        } else {
            b_t = absxk / 3.3121686421112381E-170;
            *at_0 = b_t * b_t;
        }

        absxk = std::abs((r2D[1] * b_b + r1D[1] * b) * (r1D[1] / n));
        if (absxk > scale) {
            b_t = scale / absxk;
            *at_0 = *at_0 * b_t * b_t + 1.0;
            scale = absxk;
        } else {
            b_t = absxk / scale;
            *at_0 += b_t * b_t;
        }

        absxk = std::abs((r2D[2] * b_b + r1D[2] * b) * (r1D[2] / n));
        if (absxk > scale) {
            b_t = scale / absxk;
            *at_0 = *at_0 * b_t * b_t + 1.0;
            scale = absxk;
        } else {
            b_t = absxk / scale;
            *at_0 += b_t * b_t;
        }

        *at_0 = scale * std::sqrt(*at_0);
    }

    //
    // CALC_BETA0_BETA1
    //     [BETA0,BETA1] = CALC_BETA0_BETA1(ALPHA0,ALPHA1,IN3,IN4,IN5,KAPPA0,IN7,IN8,IN9,KAPPA1)
    // Arguments    : double alpha0
    //                double alpha1
    //                const double in3[3]
    //                const double in4[3]
    //                const double in5[3]
    //                double kappa0
    //                const double in7[3]
    //                const double in8[3]
    //                const double in9[3]
    //                double kappa1
    //                double *beta0
    //                double *beta1
    // Return Type  : void
    //
    static void Calc_beta0_beta1(double alpha0, double alpha1, const double in3[3], const double
        in4[3], const double in5[3], double kappa0, const double in7[3], const double in8[3], const
        double in9[3], double kappa1, double *beta0, double *beta1)
    {
        double t2;
        double t3;
        double t4;
        double t5;
        double t6;
        double t7;
        double t8;
        double t9;
        double t29;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        double d5;
        double d6;
        double d7;
        double d8;
        double d9;
        double d10;
        double d11;
        double d12;
        double beta0_tmp;
        double beta0_tmp_tmp;
        double b_beta0_tmp_tmp;
        double b_beta0_tmp;
        double c_beta0_tmp_tmp;
        double c_beta0_tmp;
        double d_beta0_tmp_tmp;
        double e_beta0_tmp_tmp;
        double d_beta0_tmp;
        double f_beta0_tmp_tmp;
        double g_beta0_tmp_tmp;
        double e_beta0_tmp;
        double h_beta0_tmp_tmp;
        double i_beta0_tmp_tmp;
        double f_beta0_tmp;
        double j_beta0_tmp_tmp;
        double g_beta0_tmp;
        double h_beta0_tmp;
        double i_beta0_tmp;
        double j_beta0_tmp;
        double k_beta0_tmp;
        double l_beta0_tmp;
        double m_beta0_tmp;
        double n_beta0_tmp;
        double o_beta0_tmp;
        double p_beta0_tmp;
        double q_beta0_tmp;
        double r_beta0_tmp;
        double s_beta0_tmp;
        double t_beta0_tmp;
        double u_beta0_tmp;
        double d13;
        double d14;
        double d15;
        double d16;
        double beta1_tmp;
        double b_beta1_tmp;
        double c_beta1_tmp;

        //     This function was generated by the Symbolic Math Toolbox version 8.3.
        //     25-May-2019 09:07:07
        t2 = std::pow(alpha0, 2.0);
        t3 = std::pow(alpha1, 2.0);
        t4 = std::pow(in4[0], 2.0);
        t5 = std::pow(in4[1], 2.0);
        t6 = std::pow(in4[2], 2.0);
        t7 = std::pow(in8[0], 2.0);
        t8 = std::pow(in8[1], 2.0);
        t9 = std::pow(in8[2], 2.0);
        t29 = 1.0 / (((((((((((-(in4[0] * in4[1] * in8[0] * in8[1] * 2.0) + -(in4[0] * in4[2] * in8
                                [0] * in8[2] * 2.0)) + -(in4[1] * in4[2] * in8[1] * in8[2] * 2.0)) +
                             t4 * t7 * 8.0) + t4 * t8 * 9.0) + t5 * t7 * 9.0) + t5 * t8 * 8.0) + t4 *
                         t9 * 9.0) + t6 * t7 * 9.0) + t5 * t9 * 9.0) + t6 * t8 * 9.0) + t6 * t9 *
                     8.0);
        d = alpha0 * t4;
        d1 = alpha0 * t5;
        d2 = alpha0 * t6;
        d3 = in3[0] * in4[0];
        d4 = in3[1] * in4[1];
        d5 = in3[2] * in4[2];
        d6 = in7[0] * in4[0];
        d7 = in7[1] * in4[1];
        d8 = in7[2] * in4[2];
        d9 = alpha1 * in4[0];
        d10 = alpha1 * in4[1];
        d11 = alpha1 * in4[2];
        d12 = in3[1] * in4[0];
        beta0_tmp = alpha0 * in4[0];
        beta0_tmp_tmp = kappa0 * in5[0];
        b_beta0_tmp_tmp = beta0_tmp_tmp * in4[0];
        b_beta0_tmp = b_beta0_tmp_tmp * t2;
        c_beta0_tmp_tmp = kappa0 * in5[1];
        c_beta0_tmp = c_beta0_tmp_tmp * in4[1] * t2;
        d_beta0_tmp_tmp = kappa0 * in5[2];
        e_beta0_tmp_tmp = d_beta0_tmp_tmp * t2;
        d_beta0_tmp = e_beta0_tmp_tmp * in4[2];
        f_beta0_tmp_tmp = kappa1 * in9[0];
        g_beta0_tmp_tmp = f_beta0_tmp_tmp * in4[0];
        e_beta0_tmp = g_beta0_tmp_tmp * t3;
        h_beta0_tmp_tmp = kappa1 * in9[1];
        i_beta0_tmp_tmp = h_beta0_tmp_tmp * in4[1];
        f_beta0_tmp = i_beta0_tmp_tmp * t3;
        j_beta0_tmp_tmp = kappa1 * in9[2];
        g_beta0_tmp = j_beta0_tmp_tmp * in4[2] * t3;
        h_beta0_tmp = alpha0 * in4[1];
        i_beta0_tmp = in3[2] * in4[0];
        j_beta0_tmp = in3[2] * in4[1];
        k_beta0_tmp = in7[1] * in4[0];
        l_beta0_tmp = in7[2] * in4[0];
        m_beta0_tmp = in7[2] * in4[1];
        n_beta0_tmp = beta0_tmp_tmp * t2;
        o_beta0_tmp = c_beta0_tmp_tmp * t2;
        p_beta0_tmp = c_beta0_tmp_tmp * in4[0];
        q_beta0_tmp = d_beta0_tmp_tmp * in4[0] * t2;
        r_beta0_tmp = d_beta0_tmp_tmp * in4[1] * t2;
        s_beta0_tmp = h_beta0_tmp_tmp * in4[0];
        t_beta0_tmp = j_beta0_tmp_tmp * in4[0];
        u_beta0_tmp = j_beta0_tmp_tmp * in4[1];
        *beta0 = -t29 *
            (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((d9 * std::
            pow(in8[0], 3.0) * 12.0 + d10 * std::pow(in8[1], 3.0) * 12.0) + d11 * std::pow(in8[2],
            3.0) * 12.0) + d * t7 * 28.0) + d * t8 * 36.0) + d1 * t7 * 36.0) + d * t9 * 36.0) + d1 *
            t8 * 28.0) + d2 * t7 * 36.0) + d1 * t9 * 36.0) + d2 * t8 * 36.0) + d2 * t9 * 28.0) + d3 *
            t7 * 40.0) + d3 * t8 * 60.0) + d3 * t9 * 60.0) + d4 * t7 * 60.0) + d4 * t8 * 40.0) + d4 *
            t9 * 60.0) + d5 * t7 * 60.0) + d5 * t8 * 60.0) + d5 * t9 * 40.0) - d6 * t7 * 40.0) - d6 *
            t8 * 60.0) - d6 * t9 * 60.0) - d7 * t7 * 60.0) - d7 * t8 * 40.0) - d7 * t9 * 60.0) - d8 *
            t7 * 60.0) - d8 * t8 * 60.0) - d8 * t9 * 40.0) + d9 * t8 * in8[0] * 12.0) + d9 * t9 *
            in8[0] * 12.0) + d10 * t7 * in8[1] * 12.0) + d10 * t9 * in8[1] * 12.0) + d11 * t7 * in8
            [2] * 12.0) + d11 * t8 * in8[2] * 12.0) - in3[0] * in4[1] * in8[0] * in8[1] * 20.0) -
            d12 * in8[0] * in8[1] * 20.0) - in3[0] * in4[2] * in8[0] * in8[2] * 20.0) - i_beta0_tmp *
            in8[0] * in8[2] * 20.0) - in3[1] * in4[2] * in8[1] * in8[2] * 20.0) - j_beta0_tmp * in8
            [1] * in8[2] * 20.0) + in7[0] * in4[1] * in8[0] * in8[1] * 20.0) + k_beta0_tmp * in8[0] *
            in8[1] * 20.0) + in7[0] * in4[2] * in8[0] * in8[2] * 20.0) + l_beta0_tmp * in8[0] * in8
            [2] * 20.0) + in7[1] * in4[2] * in8[1] * in8[2] * 20.0) + m_beta0_tmp * in8[1] * in8[2] *
            20.0) - beta0_tmp * in4[1] * in8[0] * in8[1] * 16.0) - beta0_tmp * in4[2] * in8[0] *
            in8[2] * 16.0) - h_beta0_tmp * in4[2] * in8[1] * in8[2] * 16.0) + b_beta0_tmp * t7 * 8.0)
            + b_beta0_tmp * t8 * 9.0) + b_beta0_tmp * t9 * 9.0) + c_beta0_tmp * t7 * 9.0) +
            c_beta0_tmp * t8 * 8.0) + c_beta0_tmp * t9 * 9.0) + d_beta0_tmp * t7 * 9.0) +
            d_beta0_tmp * t8 * 9.0) + d_beta0_tmp * t9 * 8.0) - e_beta0_tmp * t8 * 3.0) -
                             e_beta0_tmp * t9 * 3.0) - f_beta0_tmp * t7 * 3.0) - f_beta0_tmp * t9 *
                           3.0) - g_beta0_tmp * t7 * 3.0) - g_beta0_tmp * t8 * 3.0) - beta0_tmp_tmp *
                        in4[1] * t2 * in8[0] * in8[1]) - p_beta0_tmp * t2 * in8[0] * in8[1]) -
                      n_beta0_tmp * in4[2] * in8[0] * in8[2]) - q_beta0_tmp * in8[0] * in8[2]) -
                    o_beta0_tmp * in4[2] * in8[1] * in8[2]) - r_beta0_tmp * in8[1] * in8[2]) +
                  f_beta0_tmp_tmp * in4[1] * t3 * in8[0] * in8[1] * 3.0) + s_beta0_tmp * t3 * in8[0]
                 * in8[1] * 3.0) + f_beta0_tmp_tmp * in4[2] * t3 * in8[0] * in8[2] * 3.0) +
               t_beta0_tmp * t3 * in8[0] * in8[2] * 3.0) + h_beta0_tmp_tmp * in4[2] * t3 * in8[1] *
              in8[2] * 3.0) + u_beta0_tmp * t3 * in8[1] * in8[2] * 3.0);
        d13 = alpha1 * t4;
        d14 = alpha1 * t5;
        d15 = alpha1 * t6;
        d16 = alpha0 * in4[2];
        beta1_tmp = f_beta0_tmp_tmp * t3;
        b_beta1_tmp = h_beta0_tmp_tmp * t3;
        c_beta1_tmp = j_beta0_tmp_tmp * t3;
        *beta1 = t29 *
            (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((alpha0 *
            std::pow(in4[0], 3.0) * in8[0] * 12.0 + alpha0 * std::pow(in4[1], 3.0) * in8[1] * 12.0)
            + alpha0 * std::pow(in4[2], 3.0) * in8[2] * 12.0) + d13 * t7 * 28.0) + d13 * t8 * 36.0)
            + d14 * t7 * 36.0) + d13 * t9 * 36.0) + d14 * t8 * 28.0) + d15 * t7 * 36.0) + d14 * t9 *
            36.0) + d15 * t8 * 36.0) + d15 * t9 * 28.0) + in3[0] * t4 * in8[0] * 40.0) + in3[0] * t5
            * in8[0] * 60.0) + in3[0] * t6 * in8[0] * 60.0) + in3[1] * t4 * in8[1] * 60.0) + in3[1] *
            t5 * in8[1] * 40.0) + in3[1] * t6 * in8[1] * 60.0) + in3[2] * t4 * in8[2] * 60.0) + in3
            [2] * t5 * in8[2] * 60.0) + in3[2] * t6 * in8[2] * 40.0) - in7[0] * t4 * in8[0] * 40.0)
            - in7[0] * t5 * in8[0] * 60.0) - in7[0] * t6 * in8[0] * 60.0) - in7[1] * t4 * in8[1] *
            60.0) - in7[1] * t5 * in8[1] * 40.0) - in7[1] * t6 * in8[1] * 60.0) - in7[2] * t4 * in8
            [2] * 60.0) - in7[2] * t5 * in8[2] * 60.0) - in7[2] * t6 * in8[2] * 40.0) + beta0_tmp *
            t5 * in8[0] * 12.0) + beta0_tmp * t6 * in8[0] * 12.0) + h_beta0_tmp * t4 * in8[1] * 12.0)
            + h_beta0_tmp * t6 * in8[1] * 12.0) + d16 * t4 * in8[2] * 12.0) + d16 * t5 * in8[2] *
            12.0) - d3 * in4[1] * in8[1] * 20.0) - d12 * in4[1] * in8[0] * 20.0) - d3 * in4[2] *
            in8[2] * 20.0) - i_beta0_tmp * in4[2] * in8[0] * 20.0) - d4 * in4[2] * in8[2] * 20.0) -
            j_beta0_tmp * in4[2] * in8[1] * 20.0) + d6 * in4[1] * in8[1] * 20.0) + k_beta0_tmp *
            in4[1] * in8[0] * 20.0) + d6 * in4[2] * in8[2] * 20.0) + l_beta0_tmp * in4[2] * in8[0] *
            20.0) + d7 * in4[2] * in8[2] * 20.0) + m_beta0_tmp * in4[2] * in8[1] * 20.0) - d9 * in4
            [1] * in8[0] * in8[1] * 16.0) - d9 * in4[2] * in8[0] * in8[2] * 16.0) - d10 * in4[2] *
            in8[1] * in8[2] * 16.0) + n_beta0_tmp * t5 * in8[0] * 3.0) + n_beta0_tmp * t6 * in8[0] *
            3.0) + o_beta0_tmp * t4 * in8[1] * 3.0) + o_beta0_tmp * t6 * in8[1] * 3.0) +
            e_beta0_tmp_tmp * t4 * in8[2] * 3.0) + e_beta0_tmp_tmp * t5 * in8[2] * 3.0) - beta1_tmp *
            t4 * in8[0] * 8.0) - beta1_tmp * t5 * in8[0] * 9.0) - beta1_tmp * t6 * in8[0] * 9.0) -
                              b_beta1_tmp * t4 * in8[1] * 9.0) - b_beta1_tmp * t5 * in8[1] * 8.0) -
                            b_beta1_tmp * t6 * in8[1] * 9.0) - c_beta1_tmp * t4 * in8[2] * 9.0) -
                          c_beta1_tmp * t5 * in8[2] * 9.0) - c_beta1_tmp * t6 * in8[2] * 8.0) -
                        b_beta0_tmp_tmp * in4[1] * t2 * in8[1] * 3.0) - p_beta0_tmp * in4[1] * t2 *
                       in8[0] * 3.0) - b_beta0_tmp * in4[2] * in8[2] * 3.0) - q_beta0_tmp * in4[2] *
                     in8[0] * 3.0) - c_beta0_tmp * in4[2] * in8[2] * 3.0) - r_beta0_tmp * in4[2] *
                   in8[1] * 3.0) + g_beta0_tmp_tmp * in4[1] * t3 * in8[1]) + s_beta0_tmp * in4[1] *
                 t3 * in8[0]) + g_beta0_tmp_tmp * in4[2] * t3 * in8[2]) + t_beta0_tmp * in4[2] * t3 *
               in8[0]) + i_beta0_tmp_tmp * in4[2] * t3 * in8[2]) + u_beta0_tmp * in4[2] * t3 * in8[1]);
    }

    //
    // CHARPOLYALPHA1
    //     COEFF_POLY_ALPHA1 = CHARPOLYALPHA1(IN1)
    // Arguments    : const double in1[16]
    //                double Coeff_Poly_Alpha1[10]
    // Return Type  : void
    //
    static void CharPolyAlpha1(const double in1[16], double Coeff_Poly_Alpha1[10])
    {
        double t2;
        double t3;
        double t4;
        double t5;
        double t6;
        double t7;
        double t8;
        double t9;
        double t10;
        double t11;
        double t12;
        double t13;
        double t14;
        double t15;
        double t16;
        double t17;
        double t18;
        double t19;
        double t20;
        double t21;
        double Coeff_Poly_Alpha1_tmp;
        double b_Coeff_Poly_Alpha1_tmp;
        double c_Coeff_Poly_Alpha1_tmp;
        double d_Coeff_Poly_Alpha1_tmp;
        double e_Coeff_Poly_Alpha1_tmp;
        double f_Coeff_Poly_Alpha1_tmp;
        double g_Coeff_Poly_Alpha1_tmp;
        double h_Coeff_Poly_Alpha1_tmp;
        double i_Coeff_Poly_Alpha1_tmp;
        double j_Coeff_Poly_Alpha1_tmp;
        double k_Coeff_Poly_Alpha1_tmp;
        double Coeff_Poly_Alpha1_tmp_tmp;
        double l_Coeff_Poly_Alpha1_tmp;
        double m_Coeff_Poly_Alpha1_tmp;
        double n_Coeff_Poly_Alpha1_tmp;
        double o_Coeff_Poly_Alpha1_tmp;
        double p_Coeff_Poly_Alpha1_tmp;
        double q_Coeff_Poly_Alpha1_tmp;
        double r_Coeff_Poly_Alpha1_tmp;
        double s_Coeff_Poly_Alpha1_tmp;
        double t_Coeff_Poly_Alpha1_tmp;
        double u_Coeff_Poly_Alpha1_tmp;
        double v_Coeff_Poly_Alpha1_tmp;
        double w_Coeff_Poly_Alpha1_tmp;
        double x_Coeff_Poly_Alpha1_tmp;
        double y_Coeff_Poly_Alpha1_tmp;
        double ab_Coeff_Poly_Alpha1_tmp;
        double bb_Coeff_Poly_Alpha1_tmp;
        double cb_Coeff_Poly_Alpha1_tmp;
        double b_Coeff_Poly_Alpha1_tmp_tmp;
        double db_Coeff_Poly_Alpha1_tmp;
        double d;
        double d1;
        double eb_Coeff_Poly_Alpha1_tmp;
        double fb_Coeff_Poly_Alpha1_tmp;
        double c_Coeff_Poly_Alpha1_tmp_tmp;
        double gb_Coeff_Poly_Alpha1_tmp;
        double d_Coeff_Poly_Alpha1_tmp_tmp;
        double hb_Coeff_Poly_Alpha1_tmp;
        double ib_Coeff_Poly_Alpha1_tmp;
        double jb_Coeff_Poly_Alpha1_tmp;
        double kb_Coeff_Poly_Alpha1_tmp;
        double e_Coeff_Poly_Alpha1_tmp_tmp;
        double Coeff_Poly_Alpha1_tmp_tmp_tmp;
        double lb_Coeff_Poly_Alpha1_tmp;
        double mb_Coeff_Poly_Alpha1_tmp;
        double nb_Coeff_Poly_Alpha1_tmp;
        double ob_Coeff_Poly_Alpha1_tmp;
        double pb_Coeff_Poly_Alpha1_tmp;
        double qb_Coeff_Poly_Alpha1_tmp;
        double rb_Coeff_Poly_Alpha1_tmp;
        double sb_Coeff_Poly_Alpha1_tmp;
        double tb_Coeff_Poly_Alpha1_tmp;
        double ub_Coeff_Poly_Alpha1_tmp;
        double vb_Coeff_Poly_Alpha1_tmp;
        double wb_Coeff_Poly_Alpha1_tmp;
        double xb_Coeff_Poly_Alpha1_tmp;
        double yb_Coeff_Poly_Alpha1_tmp;
        double ac_Coeff_Poly_Alpha1_tmp;
        double bc_Coeff_Poly_Alpha1_tmp;
        double cc_Coeff_Poly_Alpha1_tmp;
        double dc_Coeff_Poly_Alpha1_tmp;
        double ec_Coeff_Poly_Alpha1_tmp;
        double fc_Coeff_Poly_Alpha1_tmp;
        double gc_Coeff_Poly_Alpha1_tmp;
        double hc_Coeff_Poly_Alpha1_tmp;
        double ic_Coeff_Poly_Alpha1_tmp;
        double f_Coeff_Poly_Alpha1_tmp_tmp;
        double jc_Coeff_Poly_Alpha1_tmp;
        double d2;
        double d3;
        double d4;
        double d5;
        double d6;
        double d7;
        double d8;
        double d9;
        double d10;
        double d11;
        double d12;
        double d13;
        double d14;
        double d15;
        double d16;
        double d17;
        double d18;
        double kc_Coeff_Poly_Alpha1_tmp;
        double lc_Coeff_Poly_Alpha1_tmp;
        double mc_Coeff_Poly_Alpha1_tmp;
        double g_Coeff_Poly_Alpha1_tmp_tmp;
        double nc_Coeff_Poly_Alpha1_tmp;
        double h_Coeff_Poly_Alpha1_tmp_tmp;
        double oc_Coeff_Poly_Alpha1_tmp;
        double pc_Coeff_Poly_Alpha1_tmp;
        double qc_Coeff_Poly_Alpha1_tmp;
        double rc_Coeff_Poly_Alpha1_tmp;
        double sc_Coeff_Poly_Alpha1_tmp;
        double tc_Coeff_Poly_Alpha1_tmp;
        double uc_Coeff_Poly_Alpha1_tmp;
        double vc_Coeff_Poly_Alpha1_tmp;
        double i_Coeff_Poly_Alpha1_tmp_tmp;
        double wc_Coeff_Poly_Alpha1_tmp;
        double xc_Coeff_Poly_Alpha1_tmp;
        double yc_Coeff_Poly_Alpha1_tmp;
        double ad_Coeff_Poly_Alpha1_tmp;
        double bd_Coeff_Poly_Alpha1_tmp;
        double cd_Coeff_Poly_Alpha1_tmp;
        double dd_Coeff_Poly_Alpha1_tmp;
        double d19;
        double d20;
        double d21;
        double d22;
        double d23;
        double d24;
        double d25;
        double d26;
        double d27;
        double d28;
        double d29;
        double d30;
        double d31;
        double d32;
        double d33;
        double d34;
        double d35;
        double d36;
        double ed_Coeff_Poly_Alpha1_tmp;
        double fd_Coeff_Poly_Alpha1_tmp;
        double gd_Coeff_Poly_Alpha1_tmp;
        double hd_Coeff_Poly_Alpha1_tmp;
        double id_Coeff_Poly_Alpha1_tmp;
        double jd_Coeff_Poly_Alpha1_tmp;
        double kd_Coeff_Poly_Alpha1_tmp;
        double ld_Coeff_Poly_Alpha1_tmp;
        double md_Coeff_Poly_Alpha1_tmp;
        double nd_Coeff_Poly_Alpha1_tmp;
        double od_Coeff_Poly_Alpha1_tmp;
        double d37;
        double d38;
        double d39;
        double d40;
        double d41;
        double d42;
        double d43;
        double d44;
        double d45;
        double d46;
        double d47;
        double d48;
        double d49;
        double d50;
        double d51;
        double pd_Coeff_Poly_Alpha1_tmp;
        double qd_Coeff_Poly_Alpha1_tmp;
        double rd_Coeff_Poly_Alpha1_tmp;
        double sd_Coeff_Poly_Alpha1_tmp;
        double td_Coeff_Poly_Alpha1_tmp;
        double ud_Coeff_Poly_Alpha1_tmp;
        double vd_Coeff_Poly_Alpha1_tmp;
        double wd_Coeff_Poly_Alpha1_tmp;
        double xd_Coeff_Poly_Alpha1_tmp;
        double yd_Coeff_Poly_Alpha1_tmp;
        double ae_Coeff_Poly_Alpha1_tmp;
        double be_Coeff_Poly_Alpha1_tmp;
        double ce_Coeff_Poly_Alpha1_tmp;

        //     This function was generated by the Symbolic Math Toolbox version 8.3.
        //     25-May-2019 09:07:33
        t2 = std::pow(in1[0], 2.0);
        t3 = std::pow(in1[0], 3.0);
        t4 = std::pow(in1[1], 2.0);
        t5 = std::pow(in1[1], 3.0);
        t6 = std::pow(in1[2], 2.0);
        t7 = std::pow(in1[2], 3.0);
        t8 = std::pow(in1[3], 2.0);
        t9 = std::pow(in1[3], 3.0);
        t10 = std::pow(in1[4], 2.0);
        t11 = std::pow(in1[5], 2.0);
        t12 = std::pow(in1[6], 2.0);
        t13 = std::pow(in1[7], 2.0);
        t14 = std::pow(in1[8], 2.0);
        t15 = std::pow(in1[9], 2.0);
        t16 = std::pow(in1[10], 2.0);
        t17 = std::pow(in1[11], 2.0);
        t18 = std::pow(in1[12], 2.0);
        t19 = std::pow(in1[13], 2.0);
        t20 = std::pow(in1[14], 2.0);
        t21 = std::pow(in1[15], 2.0);
        Coeff_Poly_Alpha1_tmp = in1[4] * t2;
        b_Coeff_Poly_Alpha1_tmp = in1[0] * in1[8] * in1[12];
        Coeff_Poly_Alpha1[0] = (std::pow(in1[4], 3.0) * t18 + Coeff_Poly_Alpha1_tmp * t14) -
            b_Coeff_Poly_Alpha1_tmp * t10 * 2.0;
        c_Coeff_Poly_Alpha1_tmp = in1[0] * in1[1];
        d_Coeff_Poly_Alpha1_tmp = in1[4] * in1[8];
        e_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp * in1[4];
        f_Coeff_Poly_Alpha1_tmp = in1[0] * in1[4];
        g_Coeff_Poly_Alpha1_tmp = f_Coeff_Poly_Alpha1_tmp * in1[5];
        h_Coeff_Poly_Alpha1_tmp = in1[5] * t2;
        i_Coeff_Poly_Alpha1_tmp = in1[1] * in1[8] * in1[12];
        j_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp * in1[10];
        k_Coeff_Poly_Alpha1_tmp = in1[0] * in1[10] * in1[12];
        Coeff_Poly_Alpha1[1] = (((((h_Coeff_Poly_Alpha1_tmp * t14 + in1[5] * t10 * t18 * 3.0) +
            e_Coeff_Poly_Alpha1_tmp * t14 * 2.0) - i_Coeff_Poly_Alpha1_tmp * t10 * 2.0) +
            j_Coeff_Poly_Alpha1_tmp * t2 * 2.0) - k_Coeff_Poly_Alpha1_tmp * t10 * 2.0) -
            g_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0;
        Coeff_Poly_Alpha1_tmp_tmp = in1[0] * in1[2];
        l_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp * in1[4];
        m_Coeff_Poly_Alpha1_tmp = in1[2] * in1[8];
        n_Coeff_Poly_Alpha1_tmp = in1[5] * in1[8];
        o_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp * in1[5];
        p_Coeff_Poly_Alpha1_tmp = e_Coeff_Poly_Alpha1_tmp * in1[8];
        q_Coeff_Poly_Alpha1_tmp = in1[1] * in1[4];
        r_Coeff_Poly_Alpha1_tmp = f_Coeff_Poly_Alpha1_tmp * in1[6];
        s_Coeff_Poly_Alpha1_tmp = q_Coeff_Poly_Alpha1_tmp * in1[5];
        t_Coeff_Poly_Alpha1_tmp = in1[4] * t4;
        u_Coeff_Poly_Alpha1_tmp = in1[6] * t2;
        v_Coeff_Poly_Alpha1_tmp = m_Coeff_Poly_Alpha1_tmp * in1[9];
        w_Coeff_Poly_Alpha1_tmp = n_Coeff_Poly_Alpha1_tmp * in1[10];
        x_Coeff_Poly_Alpha1_tmp = in1[1] * in1[10] * in1[12];
        y_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp * in1[12];
        ab_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp * in1[14];
        bb_Coeff_Poly_Alpha1_tmp = in1[4] * in1[9] * in1[13];
        cb_Coeff_Poly_Alpha1_tmp = in1[0] * in1[12] * in1[14];
        b_Coeff_Poly_Alpha1_tmp_tmp = in1[2] * in1[12];
        db_Coeff_Poly_Alpha1_tmp = b_Coeff_Poly_Alpha1_tmp_tmp * in1[13];
        Coeff_Poly_Alpha1[2] = (((((((((((((((((((((t3 * t15 + in1[0] * t10 * t19) +
            Coeff_Poly_Alpha1_tmp * t16) + t_Coeff_Poly_Alpha1_tmp * t14) + in1[4] * t11 * t18 * 3.0)
            + u_Coeff_Poly_Alpha1_tmp * t14) + in1[6] * t10 * t18 * 3.0) + o_Coeff_Poly_Alpha1_tmp *
            t14 * 2.0) - v_Coeff_Poly_Alpha1_tmp * t2) - b_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
            w_Coeff_Poly_Alpha1_tmp * t2 * 2.0) - x_Coeff_Poly_Alpha1_tmp * t10 * 2.0) +
            y_Coeff_Poly_Alpha1_tmp * t6) + ab_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
            bb_Coeff_Poly_Alpha1_tmp * t2 * 2.0) - cb_Coeff_Poly_Alpha1_tmp * t10 * 2.0) -
            db_Coeff_Poly_Alpha1_tmp * t10) + p_Coeff_Poly_Alpha1_tmp * in1[10] * 4.0) -
            l_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + l_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12]
            * 3.0) - r_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) - s_Coeff_Poly_Alpha1_tmp *
                                in1[8] * in1[12] * 4.0) - g_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12]
            * 4.0;
        d = in1[9] * in1[11];
        d1 = in1[1] * t2;
        eb_Coeff_Poly_Alpha1_tmp = in1[4] * in1[10];
        fb_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp * in1[5];
        c_Coeff_Poly_Alpha1_tmp_tmp = in1[0] * in1[3];
        gb_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp_tmp * in1[4];
        d_Coeff_Poly_Alpha1_tmp_tmp = in1[1] * in1[2];
        hb_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[4];
        ib_Coeff_Poly_Alpha1_tmp = in1[4] * in1[5];
        jb_Coeff_Poly_Alpha1_tmp = in1[3] * in1[8];
        kb_Coeff_Poly_Alpha1_tmp = in1[2] * in1[9];
        e_Coeff_Poly_Alpha1_tmp_tmp = in1[6] * in1[8];
        Coeff_Poly_Alpha1_tmp_tmp_tmp = c_Coeff_Poly_Alpha1_tmp * in1[2];
        lb_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp_tmp * in1[8];
        mb_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp * in1[6];
        nb_Coeff_Poly_Alpha1_tmp = o_Coeff_Poly_Alpha1_tmp * in1[8];
        ob_Coeff_Poly_Alpha1_tmp = in1[2] * in1[3];
        pb_Coeff_Poly_Alpha1_tmp = ob_Coeff_Poly_Alpha1_tmp * in1[4];
        qb_Coeff_Poly_Alpha1_tmp = in1[0] * in1[5];
        rb_Coeff_Poly_Alpha1_tmp = f_Coeff_Poly_Alpha1_tmp * in1[7];
        sb_Coeff_Poly_Alpha1_tmp = qb_Coeff_Poly_Alpha1_tmp * in1[6];
        tb_Coeff_Poly_Alpha1_tmp = q_Coeff_Poly_Alpha1_tmp * in1[6];
        ub_Coeff_Poly_Alpha1_tmp = in1[2] * in1[4];
        vb_Coeff_Poly_Alpha1_tmp = in1[5] * t4;
        wb_Coeff_Poly_Alpha1_tmp = in1[7] * t2;
        xb_Coeff_Poly_Alpha1_tmp = jb_Coeff_Poly_Alpha1_tmp * in1[9];
        yb_Coeff_Poly_Alpha1_tmp = m_Coeff_Poly_Alpha1_tmp * in1[11];
        ac_Coeff_Poly_Alpha1_tmp = kb_Coeff_Poly_Alpha1_tmp * in1[10];
        bc_Coeff_Poly_Alpha1_tmp = e_Coeff_Poly_Alpha1_tmp_tmp * in1[10];
        cc_Coeff_Poly_Alpha1_tmp = n_Coeff_Poly_Alpha1_tmp * in1[12];
        dc_Coeff_Poly_Alpha1_tmp = eb_Coeff_Poly_Alpha1_tmp * in1[12];
        ec_Coeff_Poly_Alpha1_tmp = n_Coeff_Poly_Alpha1_tmp * in1[14];
        fc_Coeff_Poly_Alpha1_tmp = in1[5] * in1[9] * in1[13];
        gc_Coeff_Poly_Alpha1_tmp = in1[1] * in1[12] * in1[14];
        hc_Coeff_Poly_Alpha1_tmp = eb_Coeff_Poly_Alpha1_tmp * in1[14];
        ic_Coeff_Poly_Alpha1_tmp = in1[4] * in1[11] * in1[13];
        f_Coeff_Poly_Alpha1_tmp_tmp = in1[3] * in1[12];
        jc_Coeff_Poly_Alpha1_tmp = f_Coeff_Poly_Alpha1_tmp_tmp * in1[13];
        Coeff_Poly_Alpha1[3] = (((((((((((((((((((((((((((((((((((((((((((((std::pow(in1[5], 3.0) *
            t18 + d * t3 * 2.0) + d1 * t15 * 3.0) + in1[1] * t10 * t19) + h_Coeff_Poly_Alpha1_tmp *
            t16) + vb_Coeff_Poly_Alpha1_tmp * t14) + wb_Coeff_Poly_Alpha1_tmp * t14) + in1[7] * t10 *
            t18 * 3.0) + e_Coeff_Poly_Alpha1_tmp * t16 * 2.0) + mb_Coeff_Poly_Alpha1_tmp * t14 * 2.0)
            + g_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + ib_Coeff_Poly_Alpha1_tmp * in1[6] * t18 * 6.0)
            - xb_Coeff_Poly_Alpha1_tmp * t2) - yb_Coeff_Poly_Alpha1_tmp * t2) -
            ac_Coeff_Poly_Alpha1_tmp * t2) - i_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
            j_Coeff_Poly_Alpha1_tmp * t4 * 2.0) - k_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
            bc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) + cc_Coeff_Poly_Alpha1_tmp * t6) +
            dc_Coeff_Poly_Alpha1_tmp * t6) + ec_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
            fc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) - gc_Coeff_Poly_Alpha1_tmp * t10 * 2.0) +
            hc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) - ic_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
            jc_Coeff_Poly_Alpha1_tmp * t10) - lb_Coeff_Poly_Alpha1_tmp * in1[9] * 2.0) +
            nb_Coeff_Poly_Alpha1_tmp * in1[10] * 4.0) + p_Coeff_Poly_Alpha1_tmp * in1[14] * 4.0) -
            e_Coeff_Poly_Alpha1_tmp * in1[9] * in1[13] * 4.0) - fb_Coeff_Poly_Alpha1_tmp * in1[8] *
            in1[13]) + fb_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - gb_Coeff_Poly_Alpha1_tmp
            * in1[8] * in1[13]) + gb_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
            hb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + hb_Coeff_Poly_Alpha1_tmp * in1[9] * in1
            [12] * 3.0) - l_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + l_Coeff_Poly_Alpha1_tmp *
            in1[11] * in1[12] * 3.0) + pb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 2.0) -
            rb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) - sb_Coeff_Poly_Alpha1_tmp * in1[8] *
            in1[12] * 4.0) - tb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
            r_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) - s_Coeff_Poly_Alpha1_tmp * in1[10] *
            in1[12] * 4.0) - g_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
            ub_Coeff_Poly_Alpha1_tmp * in1[5] * in1[12] * in1[13] * 2.0;
        d2 = in1[0] * in1[9];
        d3 = in1[1] * in1[9];
        d4 = in1[3] * in1[9];
        d5 = in1[2] * in1[10];
        d6 = c_Coeff_Poly_Alpha1_tmp * in1[7];
        d7 = in1[0] * t4;
        d8 = in1[6] * t4;
        d9 = jb_Coeff_Poly_Alpha1_tmp * in1[11];
        d10 = d4 * in1[10];
        d11 = d2 * in1[13];
        d12 = d5 * in1[11];
        d13 = m_Coeff_Poly_Alpha1_tmp * in1[15];
        d14 = kb_Coeff_Poly_Alpha1_tmp * in1[14];
        d15 = in1[9] * in1[12];
        d16 = in1[9] * in1[15];
        d17 = in1[7] * in1[8];
        d18 = d17 * in1[10];
        kc_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp * in1[6];
        lc_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp_tmp * in1[5];
        mc_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[5];
        g_Coeff_Poly_Alpha1_tmp_tmp = in1[1] * in1[3];
        nc_Coeff_Poly_Alpha1_tmp = g_Coeff_Poly_Alpha1_tmp_tmp * in1[4];
        h_Coeff_Poly_Alpha1_tmp_tmp = c_Coeff_Poly_Alpha1_tmp * in1[3];
        oc_Coeff_Poly_Alpha1_tmp = h_Coeff_Poly_Alpha1_tmp_tmp * in1[8];
        pc_Coeff_Poly_Alpha1_tmp = ob_Coeff_Poly_Alpha1_tmp * in1[5];
        qc_Coeff_Poly_Alpha1_tmp = in1[1] * in1[5];
        rc_Coeff_Poly_Alpha1_tmp = qb_Coeff_Poly_Alpha1_tmp * in1[7];
        sc_Coeff_Poly_Alpha1_tmp = q_Coeff_Poly_Alpha1_tmp * in1[7];
        tc_Coeff_Poly_Alpha1_tmp = qc_Coeff_Poly_Alpha1_tmp * in1[6];
        uc_Coeff_Poly_Alpha1_tmp = in1[3] * in1[4];
        vc_Coeff_Poly_Alpha1_tmp = in1[6] * in1[9] * in1[13];
        i_Coeff_Poly_Alpha1_tmp_tmp = in1[5] * in1[10];
        wc_Coeff_Poly_Alpha1_tmp = i_Coeff_Poly_Alpha1_tmp_tmp * in1[14];
        xc_Coeff_Poly_Alpha1_tmp = in1[5] * in1[11] * in1[13];
        yc_Coeff_Poly_Alpha1_tmp = in1[4] * in1[12] * in1[14];
        ad_Coeff_Poly_Alpha1_tmp = in1[4] * in1[13] * in1[15];
        bd_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp_tmp * in1[9];
        cd_Coeff_Poly_Alpha1_tmp = i_Coeff_Poly_Alpha1_tmp_tmp * in1[12];
        dd_Coeff_Poly_Alpha1_tmp = e_Coeff_Poly_Alpha1_tmp_tmp * in1[14];
        Coeff_Poly_Alpha1[4] =
            (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t3 * t17 -
            d15 * t7) + d16 * t3 * 2.0) + d7 * t15 * 3.0) + in1[0] * t11 * t19) +
            t_Coeff_Poly_Alpha1_tmp * t16) + Coeff_Poly_Alpha1_tmp * t20) + in1[4] * t12 * t18 * 3.0)
            + u_Coeff_Poly_Alpha1_tmp * t16) + d8 * t14) + in1[6] * t11 * t18 * 3.0) +
            o_Coeff_Poly_Alpha1_tmp * t16 * 2.0) + d6 * t14 * 2.0) + r_Coeff_Poly_Alpha1_tmp * t19 *
            2.0) + s_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + ib_Coeff_Poly_Alpha1_tmp * in1[7] * t18 *
            6.0) - v_Coeff_Poly_Alpha1_tmp * t4) - b_Coeff_Poly_Alpha1_tmp * t12 * 2.0) + d3 * in1
            [11] * t2 * 6.0) - d9 * t2) - d10 * t2) + d11 * t6) - d12 * t2) +
            w_Coeff_Poly_Alpha1_tmp * t4 * 2.0) - x_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
            y_Coeff_Poly_Alpha1_tmp * t8) - d13 * t2) - d14 * t2) + d18 * t2 * 2.0) +
            ab_Coeff_Poly_Alpha1_tmp * t4 * 2.0) - bb_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
            e_Coeff_Poly_Alpha1_tmp_tmp * in1[12] * t6) - cb_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
            cd_Coeff_Poly_Alpha1_tmp * t6) - db_Coeff_Poly_Alpha1_tmp * t11) +
            dd_Coeff_Poly_Alpha1_tmp * t2 * 2.0) - vc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) +
            wc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) - xc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) +
            yc_Coeff_Poly_Alpha1_tmp * t6) - ad_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
            oc_Coeff_Poly_Alpha1_tmp * in1[9] * 2.0) - lb_Coeff_Poly_Alpha1_tmp * in1[11] * 2.0) -
            bd_Coeff_Poly_Alpha1_tmp * in1[10] * 2.0) + mb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[10] *
            4.0) + nb_Coeff_Poly_Alpha1_tmp * in1[14] * 4.0) - o_Coeff_Poly_Alpha1_tmp * in1[9] *
            in1[13] * 4.0) + e_Coeff_Poly_Alpha1_tmp * in1[10] * in1[14] * 4.0) -
            e_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 4.0) - kc_Coeff_Poly_Alpha1_tmp * in1[8] *
            in1[13]) + kc_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - lc_Coeff_Poly_Alpha1_tmp
            * in1[8] * in1[13]) + lc_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
            mc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + mc_Coeff_Poly_Alpha1_tmp * in1[9] * in1
            [12] * 3.0) - nc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + nc_Coeff_Poly_Alpha1_tmp *
            in1[9] * in1[12] * 3.0) - fb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                              fb_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                             gb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                            gb_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                           hb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + hb_Coeff_Poly_Alpha1_tmp *
                          in1[11] * in1[12] * 3.0) + pc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] *
                         2.0) + pb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 2.0) -
                       rc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) - sc_Coeff_Poly_Alpha1_tmp
                      * in1[8] * in1[12] * 4.0) - tc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0)
                    + l_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - l_Coeff_Poly_Alpha1_tmp *
                   in1[13] * in1[14]) - rb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) -
                 sb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) - tb_Coeff_Poly_Alpha1_tmp *
                in1[10] * in1[12] * 4.0) - r_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
              s_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - ub_Coeff_Poly_Alpha1_tmp * in1[6]
             * in1[12] * in1[13] * 2.0) - uc_Coeff_Poly_Alpha1_tmp * in1[5] * in1[12] * in1[13] *
            2.0;
        d19 = in1[11] * in1[15];
        d20 = in1[6] * in1[10];
        d21 = in1[3] * in1[10];
        d22 = in1[7] * t4;
        d23 = d3 * in1[13];
        d24 = d21 * in1[11];
        d25 = in1[0] * in1[11];
        d26 = d25 * in1[13];
        d27 = in1[2] * in1[11];
        d28 = jb_Coeff_Poly_Alpha1_tmp * in1[15];
        d29 = d4 * in1[14];
        d30 = d5 * in1[15];
        d31 = d27 * in1[14];
        d32 = in1[7] * in1[9] * in1[13];
        d33 = d20 * in1[14];
        d34 = in1[6] * in1[11] * in1[13];
        d35 = in1[5] * in1[12] * in1[14];
        d36 = in1[5] * in1[13] * in1[15];
        ed_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp * in1[7];
        fd_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp_tmp * in1[6];
        gd_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[6];
        hd_Coeff_Poly_Alpha1_tmp = g_Coeff_Poly_Alpha1_tmp_tmp * in1[5];
        id_Coeff_Poly_Alpha1_tmp = ob_Coeff_Poly_Alpha1_tmp * in1[6];
        jd_Coeff_Poly_Alpha1_tmp = in1[0] * in1[6] * in1[7];
        kd_Coeff_Poly_Alpha1_tmp = qc_Coeff_Poly_Alpha1_tmp * in1[7];
        ld_Coeff_Poly_Alpha1_tmp = in1[2] * in1[5];
        md_Coeff_Poly_Alpha1_tmp = h_Coeff_Poly_Alpha1_tmp_tmp * in1[9];
        nd_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp_tmp * in1[10];
        od_Coeff_Poly_Alpha1_tmp = d17 * in1[12];
        Coeff_Poly_Alpha1[5] =
            (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
            ((((((t5 * t15 - in1[11] * in1[12] * t7) + d19 * t3 * 2.0) + d1 * t17 * 3.0) + in1[1] *
            t11 * t19) + vb_Coeff_Poly_Alpha1_tmp * t16) + h_Coeff_Poly_Alpha1_tmp * t20) + in1[5] *
            t12 * t18 * 3.0) + wb_Coeff_Poly_Alpha1_tmp * t16) + d22 * t14) + in1[7] * t11 * t18 *
            3.0) + e_Coeff_Poly_Alpha1_tmp * t20 * 2.0) + mb_Coeff_Poly_Alpha1_tmp * t16 * 2.0) +
            rb_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + sb_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
            tb_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + in1[4] * in1[6] * in1[7] * t18 * 6.0) + d2 *
            in1[11] * t4 * 6.0) - xb_Coeff_Poly_Alpha1_tmp * t4) - yb_Coeff_Poly_Alpha1_tmp * t4) -
            ac_Coeff_Poly_Alpha1_tmp * t4) - i_Coeff_Poly_Alpha1_tmp * t12 * 2.0) -
            k_Coeff_Poly_Alpha1_tmp * t12 * 2.0) + d23 * t6) - d24 * t2) + bc_Coeff_Poly_Alpha1_tmp *
            t4 * 2.0) + d26 * t6) - d4 * in1[12] * t6 * 3.0) + d3 * in1[15] * t2 * 6.0) +
            cc_Coeff_Poly_Alpha1_tmp * t8) - d28 * t2) - d29 * t2) + dc_Coeff_Poly_Alpha1_tmp * t8)
            - d30 * t2) - d31 * t2) + ec_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
            fc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) + od_Coeff_Poly_Alpha1_tmp * t6) -
            gc_Coeff_Poly_Alpha1_tmp * t11 * 2.0) + hc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
            ic_Coeff_Poly_Alpha1_tmp * t4 * 2.0) + d20 * in1[12] * t6) - jc_Coeff_Poly_Alpha1_tmp *
            t11) + d17 * in1[14] * t2 * 2.0) - d32 * t2 * 2.0) + d33 * t2 * 2.0) - d34 * t2 * 2.0) +
            d35 * t6) - d36 * t2 * 2.0) - oc_Coeff_Poly_Alpha1_tmp * in1[11] * 2.0) -
            md_Coeff_Poly_Alpha1_tmp * in1[10] * 2.0) - nd_Coeff_Poly_Alpha1_tmp * in1[11] * 2.0) -
            lb_Coeff_Poly_Alpha1_tmp * in1[15] * 2.0) - bd_Coeff_Poly_Alpha1_tmp * in1[14] * 2.0) +
            d6 * in1[8] * in1[10] * 4.0) + Coeff_Poly_Alpha1_tmp_tmp * in1[3] * in1[9] * in1[13] *
            2.0) + c_Coeff_Poly_Alpha1_tmp * in1[6] * in1[8] * in1[14] * 4.0) - in1[0] * in1[1] *
            in1[6] * in1[9] * in1[13] * 4.0) + o_Coeff_Poly_Alpha1_tmp * in1[10] * in1[14] * 4.0) -
            o_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 4.0) - ed_Coeff_Poly_Alpha1_tmp * in1[8] *
            in1[13]) + ed_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - fd_Coeff_Poly_Alpha1_tmp
            * in1[8] * in1[13]) + fd_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
            gd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + gd_Coeff_Poly_Alpha1_tmp * in1[9] * in1
            [12] * 3.0) - hd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + hd_Coeff_Poly_Alpha1_tmp *
            in1[9] * in1[12] * 3.0) - kc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
            kc_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - lc_Coeff_Poly_Alpha1_tmp * in1[10]
            * in1[13]) + lc_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
            mc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + mc_Coeff_Poly_Alpha1_tmp * in1[11] *
            in1[12] * 3.0) - nc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
            nc_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) + id_Coeff_Poly_Alpha1_tmp * in1[8] *
            in1[12] * 2.0) + pc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 2.0) -
                              e_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 4.0) -
                             jd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
                            kd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) +
                           fb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
                          fb_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) + gb_Coeff_Poly_Alpha1_tmp *
                         in1[12] * in1[15] * 3.0) - gb_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) -
                       rc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) +
                      hb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - hb_Coeff_Poly_Alpha1_tmp
                     * in1[13] * in1[14]) - sc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) -
                   tc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) + pb_Coeff_Poly_Alpha1_tmp *
                  in1[12] * in1[14] * 2.0) - rb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
                sb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - tb_Coeff_Poly_Alpha1_tmp *
               in1[12] * in1[14] * 4.0) - ub_Coeff_Poly_Alpha1_tmp * in1[7] * in1[12] * in1[13] *
              2.0) - ld_Coeff_Poly_Alpha1_tmp * in1[6] * in1[12] * in1[13] * 2.0) -
            uc_Coeff_Poly_Alpha1_tmp * in1[6] * in1[12] * in1[13] * 2.0;
        d37 = in1[1] * in1[11];
        d38 = in1[3] * in1[11];
        d39 = in1[7] * in1[10];
        d40 = d37 * in1[13];
        d41 = d21 * in1[15];
        d42 = d38 * in1[14];
        d43 = in1[0] * in1[13] * in1[15];
        d44 = d39 * in1[12];
        d45 = in1[2] * in1[14] * in1[15];
        d46 = d39 * in1[14];
        d47 = in1[7] * in1[11] * in1[13];
        d48 = in1[12] * in1[15];
        d49 = in1[6] * in1[12] * in1[14];
        d50 = in1[6] * in1[13] * in1[15];
        d51 = h_Coeff_Poly_Alpha1_tmp_tmp * in1[10];
        pd_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp_tmp * in1[7];
        qd_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[7];
        rd_Coeff_Poly_Alpha1_tmp = g_Coeff_Poly_Alpha1_tmp_tmp * in1[6];
        sd_Coeff_Poly_Alpha1_tmp = ob_Coeff_Poly_Alpha1_tmp * in1[7];
        td_Coeff_Poly_Alpha1_tmp = in1[1] * in1[6] * in1[7];
        ud_Coeff_Poly_Alpha1_tmp = in1[3] * in1[5];
        vd_Coeff_Poly_Alpha1_tmp = in1[0] * in1[2] * in1[3];
        Coeff_Poly_Alpha1[6] =
            (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
            ((((t3 * t21 + std::pow(in1[6], 3.0) * t18) + d * t5 * 2.0) - d48 * t7) + d7 * t17 * 3.0)
            + in1[0] * t12 * t19) + t_Coeff_Poly_Alpha1_tmp * t20) + in1[4] * t13 * t18 * 3.0) + d8 *
            t16) + u_Coeff_Poly_Alpha1_tmp * t20) + o_Coeff_Poly_Alpha1_tmp * t20 * 2.0) + d6 * t16 *
            2.0) + rc_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + sc_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
            tc_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + in1[5] * in1[6] * in1[7] * t18 * 6.0) -
            b_Coeff_Poly_Alpha1_tmp * t13 * 2.0) - d9 * t4) - d10 * t4) + d11 * t8) - d12 * t4) -
            kb_Coeff_Poly_Alpha1_tmp * in1[12] * t8 * 3.0) - x_Coeff_Poly_Alpha1_tmp * t12 * 2.0) +
            d2 * in1[15] * t4 * 6.0) - d13 * t4) - d14 * t4) + d18 * t4 * 2.0) + d40 * t6) - d38 *
            in1[12] * t6 * 3.0) + in1[6] * in1[8] * in1[12] * t8) - cb_Coeff_Poly_Alpha1_tmp * t12 *
            2.0) + d37 * in1[15] * t2 * 6.0) + cd_Coeff_Poly_Alpha1_tmp * t8) -
            db_Coeff_Poly_Alpha1_tmp * t12) - d41 * t2) - d42 * t2) + dd_Coeff_Poly_Alpha1_tmp * t4 *
            2.0) - vc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) + d43 * t6) + wc_Coeff_Poly_Alpha1_tmp * t4 *
            2.0) - xc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) + d44 * t6) + yc_Coeff_Poly_Alpha1_tmp * t8)
            - d45 * t2) + d46 * t2 * 2.0) - d47 * t2 * 2.0) - ad_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
            d49 * t6) - d50 * t2 * 2.0) - d51 * in1[11] * 2.0) - oc_Coeff_Poly_Alpha1_tmp * in1[15] *
            2.0) - md_Coeff_Poly_Alpha1_tmp * in1[14] * 2.0) - nd_Coeff_Poly_Alpha1_tmp * in1[15] *
            2.0) - Coeff_Poly_Alpha1_tmp_tmp_tmp * in1[11] * in1[14] * 2.0) +
            d_Coeff_Poly_Alpha1_tmp_tmp * in1[3] * in1[9] * in1[13] * 2.0) +
            vd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 2.0) + in1[0] * in1[1] * in1[7] * in1[8] *
            in1[14] * 4.0) - d6 * in1[9] * in1[13] * 4.0) + mb_Coeff_Poly_Alpha1_tmp * in1[10] *
            in1[14] * 4.0) - mb_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 4.0) -
            pd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + pd_Coeff_Poly_Alpha1_tmp * in1[9] * in1
            [12] * 3.0) - qd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + qd_Coeff_Poly_Alpha1_tmp *
            in1[9] * in1[12] * 3.0) - rd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
            rd_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - ed_Coeff_Poly_Alpha1_tmp * in1[10] *
            in1[13]) + ed_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
            fd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + fd_Coeff_Poly_Alpha1_tmp * in1[11] *
            in1[12] * 3.0) - gd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
            gd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - hd_Coeff_Poly_Alpha1_tmp * in1[10]
            * in1[13]) + hd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) +
            sd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 2.0) + id_Coeff_Poly_Alpha1_tmp * in1[10] *
                               in1[12] * 2.0) - o_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 4.0) -
                             td_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) +
                            kc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
                           kc_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) + lc_Coeff_Poly_Alpha1_tmp *
                          in1[12] * in1[15] * 3.0) - lc_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) -
                        jd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) +
                       mc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
                      mc_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) + nc_Coeff_Poly_Alpha1_tmp *
                     in1[12] * in1[15] * 3.0) - nc_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) -
                   kd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) + pc_Coeff_Poly_Alpha1_tmp *
                  in1[12] * in1[14] * 2.0) - rc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
                sc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - tc_Coeff_Poly_Alpha1_tmp *
               in1[12] * in1[14] * 4.0) - ld_Coeff_Poly_Alpha1_tmp * in1[7] * in1[12] * in1[13] *
              2.0) - uc_Coeff_Poly_Alpha1_tmp * in1[7] * in1[12] * in1[13] * 2.0) -
            ud_Coeff_Poly_Alpha1_tmp * in1[6] * in1[12] * in1[13] * 2.0;
        wd_Coeff_Poly_Alpha1_tmp = g_Coeff_Poly_Alpha1_tmp_tmp * in1[7];
        xd_Coeff_Poly_Alpha1_tmp = in1[1] * in1[2] * in1[3];
        yd_Coeff_Poly_Alpha1_tmp = in1[1] * in1[13] * in1[15];
        ae_Coeff_Poly_Alpha1_tmp = in1[3] * in1[14] * in1[15];
        be_Coeff_Poly_Alpha1_tmp = in1[7] * in1[12] * in1[14];
        ce_Coeff_Poly_Alpha1_tmp = in1[7] * in1[13] * in1[15];
        Coeff_Poly_Alpha1[7] =
            ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t5 * t17 - d15 * t9)
            + d16 * t5 * 2.0) + d1 * t21 * 3.0) + in1[1] * t12 * t19) + vb_Coeff_Poly_Alpha1_tmp *
            t20) + in1[5] * t13 * t18 * 3.0) + d22 * t16) + wb_Coeff_Poly_Alpha1_tmp * t20) + in1[7]
            * t12 * t18 * 3.0) + mb_Coeff_Poly_Alpha1_tmp * t20 * 2.0) + jd_Coeff_Poly_Alpha1_tmp *
            t19 * 2.0) + kd_Coeff_Poly_Alpha1_tmp * t19 * 2.0) - i_Coeff_Poly_Alpha1_tmp * t13 * 2.0)
            - k_Coeff_Poly_Alpha1_tmp * t13 * 2.0) + d23 * t8) - d24 * t4) + d26 * t8) - d27 * in1
            [12] * t8 * 3.0) + d25 * in1[15] * t4 * 6.0) - d28 * t4) - d29 * t4) - d30 * t4) - d31 *
            t4) + od_Coeff_Poly_Alpha1_tmp * t8) - gc_Coeff_Poly_Alpha1_tmp * t12 * 2.0) + in1[6] *
            in1[10] * in1[12] * t8) - jc_Coeff_Poly_Alpha1_tmp * t12) + in1[7] * in1[8] * in1[14] *
            t4 * 2.0) - d32 * t4 * 2.0) + yd_Coeff_Poly_Alpha1_tmp * t6) + d33 * t4 * 2.0) - d34 *
            t4 * 2.0) - f_Coeff_Poly_Alpha1_tmp_tmp * in1[15] * t6 * 3.0) + d35 * t8) -
            ae_Coeff_Poly_Alpha1_tmp * t2) - d36 * t4 * 2.0) + be_Coeff_Poly_Alpha1_tmp * t6) -
            ce_Coeff_Poly_Alpha1_tmp * t2 * 2.0) - d51 * in1[15] * 2.0) -
            h_Coeff_Poly_Alpha1_tmp_tmp * in1[11] * in1[14] * 2.0) + xd_Coeff_Poly_Alpha1_tmp * in1
            [11] * in1[13] * 2.0) - Coeff_Poly_Alpha1_tmp_tmp_tmp * in1[14] * in1[15] * 2.0) + d6 *
            in1[10] * in1[14] * 4.0) - d6 * in1[11] * in1[13] * 4.0) - wd_Coeff_Poly_Alpha1_tmp *
            in1[8] * in1[13]) + wd_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) +
            vd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 2.0) - pd_Coeff_Poly_Alpha1_tmp * in1[10]
            * in1[13]) + pd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                               qd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                              qd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                             rd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                            rd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) +
                           sd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 2.0) -
                          mb_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 4.0) +
                         ed_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
                        ed_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) + fd_Coeff_Poly_Alpha1_tmp *
                       in1[12] * in1[15] * 3.0) - fd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
                     gd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - gd_Coeff_Poly_Alpha1_tmp *
                    in1[13] * in1[14]) + hd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
                  hd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) - td_Coeff_Poly_Alpha1_tmp * in1[10]
                 * in1[12] * 4.0) + id_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 2.0) -
               jd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - kd_Coeff_Poly_Alpha1_tmp * in1
              [12] * in1[14] * 4.0) - in1[2] * in1[6] * in1[7] * in1[12] * in1[13] * 2.0) -
            ud_Coeff_Poly_Alpha1_tmp * in1[7] * in1[12] * in1[13] * 2.0;
        Coeff_Poly_Alpha1[8] = ((((((((((((((((((((((((((((((((((-in1[11] * in1[12] * t9 + d19 * t5 *
            2.0) + d7 * t21 * 3.0) + in1[0] * t13 * t19) + d8 * t20) + in1[6] * t13 * t18 * 3.0) +
            d6 * t20 * 2.0) + td_Coeff_Poly_Alpha1_tmp * t19 * 2.0) - x_Coeff_Poly_Alpha1_tmp * t13 *
            2.0) + d40 * t8) - cb_Coeff_Poly_Alpha1_tmp * t13 * 2.0) - db_Coeff_Poly_Alpha1_tmp *
            t13) - d41 * t4) - d42 * t4) + d43 * t8) - b_Coeff_Poly_Alpha1_tmp_tmp * in1[15] * t8 *
            3.0) + d44 * t8) - d45 * t4) + d46 * t4 * 2.0) - d47 * t4 * 2.0) + d49 * t8) - d50 * t4 *
            2.0) - h_Coeff_Poly_Alpha1_tmp_tmp * in1[14] * in1[15] * 2.0) + xd_Coeff_Poly_Alpha1_tmp
            * in1[13] * in1[15] * 2.0) - wd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
            wd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - d6 * in1[13] * in1[15] * 4.0) +
            pd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - pd_Coeff_Poly_Alpha1_tmp * in1[13]
            * in1[14]) + qd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
            qd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) + rd_Coeff_Poly_Alpha1_tmp * in1[12] *
            in1[15] * 3.0) - rd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
            sd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 2.0) - td_Coeff_Poly_Alpha1_tmp * in1[12]
                                * in1[14] * 4.0) - in1[3] * in1[6] * in1[7] * in1[12] * in1[13] *
            2.0;
        Coeff_Poly_Alpha1[9] = (((((((((((t5 * t21 + std::pow(in1[7], 3.0) * t18) - d48 * t9) + in1
            [1] * t13 * t19) + d22 * t20) - gc_Coeff_Poly_Alpha1_tmp * t13 * 2.0) -
            jc_Coeff_Poly_Alpha1_tmp * t13) + yd_Coeff_Poly_Alpha1_tmp * t8) -
            ae_Coeff_Poly_Alpha1_tmp * t4) + be_Coeff_Poly_Alpha1_tmp * t8) -
            ce_Coeff_Poly_Alpha1_tmp * t4 * 2.0) + wd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] *
                                3.0) - wd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14];
    }

    //
    // Arguments    : const FeedoptContext *ctx
    // Return Type  : void
    //
    static void CheckCurvStructs(const FeedoptContext *ctx)
    {
        unsigned int N;
        int i;
        CurvStruct Curv1;
        CurvStruct Curv2;
        double unusedU0[3];
        double r0D1[3];
        double unusedU1[3];
        double r1D1[3];
        double y;
        double b_y;
        double d;
        N = ctx->q_gcode.size();

        //  1 -> stdout
        //  2 -> stderr
        if ((static_cast<unsigned long>(std::round(DebugConfig)) & 1UL) != 0UL) {
            printf("Checking for cusps...\n");
            fflush(stdout);
        }

        i = static_cast<int>(N - 1U);
        for (int k = 0; k < i; k++) {
            double scale;
            double b_scale;
            double absxk;
            double t;
            double b_absxk;
            double b_t;
            ctx->q_gcode.get((k + 1U), (&Curv1));
            ctx->q_gcode.get((k - 4294967294U), (&Curv2));
            e_EvalCurvStruct(&ctx->q_splines, Curv1.Type, Curv1.P0, Curv1.P1, Curv1.evec,
                             Curv1.theta, Curv1.pitch, Curv1.CoeffP5, Curv1.sp_index, Curv1.a_param,
                             Curv1.b_param, unusedU0, r0D1);
            f_EvalCurvStruct(&ctx->q_splines, Curv2.Type, Curv2.P0, Curv2.P1, Curv2.evec,
                             Curv2.theta, Curv2.pitch, Curv2.CoeffP5, Curv2.sp_index, Curv2.a_param,
                             Curv2.b_param, unusedU1, r1D1);
            scale = 3.3121686421112381E-170;
            b_scale = 3.3121686421112381E-170;
            absxk = std::abs(r0D1[0]);
            if (absxk > 3.3121686421112381E-170) {
                y = 1.0;
                scale = absxk;
            } else {
                t = absxk / 3.3121686421112381E-170;
                y = t * t;
            }

            b_absxk = std::abs(r1D1[0]);
            if (b_absxk > 3.3121686421112381E-170) {
                b_y = 1.0;
                b_scale = b_absxk;
            } else {
                b_t = b_absxk / 3.3121686421112381E-170;
                b_y = b_t * b_t;
            }

            absxk = std::abs(r0D1[1]);
            if (absxk > scale) {
                t = scale / absxk;
                y = y * t * t + 1.0;
                scale = absxk;
            } else {
                t = absxk / scale;
                y += t * t;
            }

            b_absxk = std::abs(r1D1[1]);
            if (b_absxk > b_scale) {
                b_t = b_scale / b_absxk;
                b_y = b_y * b_t * b_t + 1.0;
                b_scale = b_absxk;
            } else {
                b_t = b_absxk / b_scale;
                b_y += b_t * b_t;
            }

            absxk = std::abs(r0D1[2]);
            if (absxk > scale) {
                t = scale / absxk;
                y = y * t * t + 1.0;
                scale = absxk;
            } else {
                t = absxk / scale;
                y += t * t;
            }

            b_absxk = std::abs(r1D1[2]);
            if (b_absxk > b_scale) {
                b_t = b_scale / b_absxk;
                b_y = b_y * b_t * b_t + 1.0;
                b_scale = b_absxk;
            } else {
                b_t = b_absxk / b_scale;
                b_y += b_t * b_t;
            }

            y = scale * std::sqrt(y);
            b_y = b_scale * std::sqrt(b_y);
            d = 180.0 - ctx->cfg.CuspThreshold;
            b_cosd(&d);
            if (((r0D1[0] * r1D1[0] + r0D1[1] * r1D1[1]) + r0D1[2] * r1D1[2]) / (y * b_y) < d) {
                switch (Curv1.zspdmode) {
                  case ZSpdMode_NN:
                    Curv1.zspdmode = ZSpdMode_NZ;
                    break;

                  case ZSpdMode_ZN:
                    Curv1.zspdmode = ZSpdMode_ZZ;
                    break;

                  case ZSpdMode_NZ:
                    //  Nothing to do
                    break;

                  default:
                    //  Nothing to do
                    break;
                }

                switch (Curv2.zspdmode) {
                  case ZSpdMode_NN:
                    Curv2.zspdmode = ZSpdMode_ZN;
                    break;

                  case ZSpdMode_ZN:
                    //  Nothing to do
                    break;

                  case ZSpdMode_NZ:
                    Curv2.zspdmode = ZSpdMode_ZZ;
                    break;

                  default:
                    //  Nothing to do
                    break;
                }

                ctx->q_gcode.set((k + 1U), (&Curv1));
                ctx->q_gcode.set((k - 4294967294U), (&Curv2));
            }
        }
    }

    //
    // COEFPOLYSYS
    //     COEFPS = COEFPOLYSYS(IN1,IN2,IN3,KAPPA0,IN5,IN6,IN7,KAPPA1)
    // Arguments    : const double in1[3]
    //                const double in2[3]
    //                const double in3[3]
    //                double kappa0
    //                const double in5[3]
    //                const double in6[3]
    //                const double in7[3]
    //                double kappa1
    //                double CoefPS[16]
    // Return Type  : void
    //
    static void CoefPolySys(const double in1[3], const double in2[3], const double in3[3], double
                            kappa0, const double in5[3], const double in6[3], const double in7[3],
                            double kappa1, double CoefPS[16])
    {
        double t2;
        double t3;
        double t4;
        double t5;
        double t6;
        double t7;
        double t8;
        double t9;
        double t10;
        double t14;
        double t15;
        double t16;
        double t18;
        double t19;
        double t21;
        double t23;
        double t24;
        double t25;
        double t27;
        double t28;
        double t30;
        double t17;
        double t20;
        double t22;
        double t26;
        double t29;
        double t31;
        double t32_tmp;
        double t32;
        double t33_tmp;
        double t33;
        double t34;
        double t35;
        double t36;
        double t37_tmp;
        double t37;
        double t38;
        double t39;
        double t40;
        double t41;
        double t42;
        double t43;
        double t44_tmp;
        double t44;
        double t45;
        double t46_tmp;
        double t46;
        double t47;
        double t48_tmp;
        double t48;
        double t49;
        double t50_tmp;
        double t50;
        double t51;
        double t52_tmp;
        double t52;
        double t53;
        double t54_tmp;
        double t54;
        double t55;
        double t83_tmp;
        double t83;
        double t84_tmp;
        double t84;
        double t85_tmp;
        double t85;
        double t86_tmp;
        double t86;
        double t87;
        double t88_tmp;
        double t88;
        double t89;
        double t90;
        double t91_tmp;
        double t91;
        double t111;
        double t201_tmp;
        double b_t201_tmp;
        double c_t201_tmp;
        double t201;
        double t203_tmp;
        double b_t203_tmp;
        double c_t203_tmp;
        double d_t203_tmp;
        double e_t203_tmp;
        double f_t203_tmp;
        double g_t203_tmp;
        double h_t203_tmp;
        double i_t203_tmp;
        double t203;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        double d5;
        double d6;
        double d7;
        double d8;
        double d9;
        double d10;
        double d11;
        double d12;
        double d13;
        double d14;
        double t205_tmp;
        double t205;
        double CoefPS_tmp_tmp;
        double CoefPS_tmp;
        double b_CoefPS_tmp;
        double c_CoefPS_tmp;
        double d_CoefPS_tmp;
        double e_CoefPS_tmp;
        double f_CoefPS_tmp;
        double d15;
        double d16;
        double d17;
        double d18;
        double d19;
        double d20;
        double d21;
        double d22;
        double d23;
        double d24;
        double d25;
        double d26;
        double d27;
        double d28;
        double d29;
        double d30;
        double d31;
        double d32;
        double d33;
        double d34;
        double d35;
        double d36;
        double d37;
        double d38;
        double d39;
        double d40;
        double d41;
        double d42;
        double d43;
        double d44;
        double d45;
        double d46;
        double d47;
        double CoefPS_tmp_tmp_tmp;
        double g_CoefPS_tmp;
        double b_CoefPS_tmp_tmp;
        double h_CoefPS_tmp;
        double c_CoefPS_tmp_tmp;
        double i_CoefPS_tmp;
        double d_CoefPS_tmp_tmp;
        double j_CoefPS_tmp;
        double k_CoefPS_tmp;
        double l_CoefPS_tmp;
        double e_CoefPS_tmp_tmp;
        double m_CoefPS_tmp;
        double n_CoefPS_tmp;
        double o_CoefPS_tmp;
        double p_CoefPS_tmp;
        double q_CoefPS_tmp;
        double r_CoefPS_tmp;
        double d48;
        double d49;
        double d50;
        double d51;
        double d52;
        double d53;
        double d54;
        double d55;
        double d56;
        double d57;
        double d58;
        double d59;
        double d60;
        double d61;
        double d62;
        double d63;
        double d64;
        double d65;
        double d66;
        double d67;
        double d68;
        double d69;
        double d70;
        double d71;
        double s_CoefPS_tmp;
        double t_CoefPS_tmp;
        double u_CoefPS_tmp;
        double v_CoefPS_tmp;
        double w_CoefPS_tmp;
        double x_CoefPS_tmp;
        double y_CoefPS_tmp;
        double ab_CoefPS_tmp;
        double bb_CoefPS_tmp;
        double cb_CoefPS_tmp;
        double db_CoefPS_tmp;
        double eb_CoefPS_tmp;
        double fb_CoefPS_tmp;
        double gb_CoefPS_tmp;
        double hb_CoefPS_tmp;
        double ib_CoefPS_tmp;
        double jb_CoefPS_tmp;
        double kb_CoefPS_tmp;
        double lb_CoefPS_tmp;
        double mb_CoefPS_tmp;
        double d72;
        double d73;
        double d74;
        double d75;
        double d76;
        double d77;
        double d78;
        double d79;
        double d80;
        double d81;
        double d82;
        double d83;
        double d84;
        double d85;
        double d86;
        double d87;
        double d88;
        double d89;
        double d90;
        double d91;
        double d92;
        double d93;
        double d94;
        double d95;
        double d96;
        double d97;
        double d98;
        double d99;
        double d100;
        double d101;
        double d102;
        double d103;
        double d104;
        double d105;
        double d106;
        double d107;
        double d108;
        double f_CoefPS_tmp_tmp;
        double g_CoefPS_tmp_tmp;
        double nb_CoefPS_tmp;
        double ob_CoefPS_tmp;
        double pb_CoefPS_tmp;
        double qb_CoefPS_tmp;
        double rb_CoefPS_tmp;
        double sb_CoefPS_tmp;
        double tb_CoefPS_tmp;
        double ub_CoefPS_tmp;
        double vb_CoefPS_tmp;
        double wb_CoefPS_tmp;
        double xb_CoefPS_tmp;
        double d109;
        double d110;
        double d111;
        double d112;
        double d113;
        double d114;
        double d115;
        double d116;
        double d117;
        double d118;
        double d119;
        double yb_CoefPS_tmp;
        double ac_CoefPS_tmp;
        double bc_CoefPS_tmp;
        double cc_CoefPS_tmp;
        double dc_CoefPS_tmp;
        double ec_CoefPS_tmp;
        double fc_CoefPS_tmp;
        double gc_CoefPS_tmp;
        double hc_CoefPS_tmp;
        double ic_CoefPS_tmp;
        double jc_CoefPS_tmp;

        //     This function was generated by the Symbolic Math Toolbox version 8.3.
        //     25-May-2019 09:07:21
        t2 = in2[0] * in6[0];
        t3 = in2[1] * in6[1];
        t4 = in2[2] * in6[2];
        t5 = std::pow(in3[0], 2.0);
        t6 = std::pow(in3[1], 2.0);
        t7 = std::pow(in3[2], 2.0);
        t8 = std::pow(in7[0], 2.0);
        t9 = std::pow(in7[1], 2.0);
        t10 = std::pow(in7[2], 2.0);
        t14 = std::pow(in2[0], 2.0);
        t15 = std::pow(in2[0], 3.0);
        t16 = std::pow(in2[1], 2.0);
        t18 = std::pow(in2[1], 3.0);
        t19 = std::pow(in2[2], 2.0);
        t21 = std::pow(in2[2], 3.0);
        t23 = std::pow(in6[0], 2.0);
        t24 = std::pow(in6[0], 3.0);
        t25 = std::pow(in6[1], 2.0);
        t27 = std::pow(in6[1], 3.0);
        t28 = std::pow(in6[2], 2.0);
        t30 = std::pow(in6[2], 3.0);
        t17 = std::pow(t14, 2.0);
        t20 = std::pow(t16, 2.0);
        t22 = std::pow(t19, 2.0);
        t26 = std::pow(t23, 2.0);
        t29 = std::pow(t25, 2.0);
        t31 = std::pow(t28, 2.0);
        t32_tmp = in3[0] * in2[0];
        t32 = t32_tmp * t3;
        t33_tmp = in3[1] * in2[1];
        t33 = t33_tmp * t2;
        t34 = t32_tmp * t4;
        t35 = in3[2] * t2 * in2[2];
        t36 = t33_tmp * t4;
        t37_tmp = in3[2] * in2[2];
        t37 = t37_tmp * t3;
        t38 = in7[0] * t3 * in6[0];
        t39 = in7[1] * t2 * in6[1];
        t40 = in7[0] * t4 * in6[0];
        t41 = in7[2] * t2 * in6[2];
        t42 = in7[1] * t4 * in6[1];
        t43 = in7[2] * t3 * in6[2];
        t44_tmp = in3[0] * in6[0];
        t44 = t44_tmp * t16;
        t45 = t44_tmp * t19;
        t46_tmp = in3[1] * in6[1];
        t46 = t46_tmp * t14;
        t47 = t46_tmp * t19;
        t48_tmp = in3[2] * in6[2];
        t48 = t48_tmp * t14;
        t49 = t48_tmp * t16;
        t50_tmp = in7[0] * in2[0];
        t50 = t50_tmp * t25;
        t51 = t50_tmp * t28;
        t52_tmp = in7[1] * in2[1];
        t52 = t52_tmp * t23;
        t53 = t52_tmp * t28;
        t54_tmp = in7[2] * in2[2];
        t54 = t54_tmp * t23;
        t55 = t54_tmp * t25;
        t83_tmp = std::pow(t2, 2.0);
        t83 = t83_tmp * 8.0;
        t84_tmp = t14 * t25;
        t84 = t84_tmp * 9.0;
        t85_tmp = t16 * t23;
        t85 = t85_tmp * 9.0;
        t86_tmp = std::pow(t3, 2.0);
        t86 = t86_tmp * 8.0;
        t87 = t14 * t28 * 9.0;
        t88_tmp = t19 * t23;
        t88 = t88_tmp * 9.0;
        t89 = t16 * t28 * 9.0;
        t90 = t19 * t25 * 9.0;
        t91_tmp = std::pow(t4, 2.0);
        t91 = t91_tmp * 8.0;
        t111 = (t2 + t3) + t4;
        t201_tmp = t2 * t3;
        b_t201_tmp = t2 * t4;
        c_t201_tmp = t3 * t4;
        t201 = 1.0 / (((((((((((-(t201_tmp * 2.0) + -(b_t201_tmp * 2.0)) + -(c_t201_tmp * 2.0)) +
                              t83) + t84) + t85) + t86) + t87) + t88) + t89) + t90) + t91);
        t203_tmp = t2 * t14;
        b_t203_tmp = t3 * t16;
        c_t203_tmp = t4 * t19;
        d_t203_tmp = t2 * t16;
        e_t203_tmp = t2 * t19;
        f_t203_tmp = t3 * t19;
        g_t203_tmp = t3 * t14;
        h_t203_tmp = t4 * t14;
        i_t203_tmp = t4 * t16;
        t203 = t201 * (((((((((((((((((((((((((((std::pow(t2, 3.0) * 40.0 + std::pow(t3, 3.0) * 40.0)
            + std::pow(t4, 3.0) * 40.0) + t201_tmp * t4 * 24.0) + d_t203_tmp * t23 * 36.0) +
            e_t203_tmp * t23 * 36.0) + g_t203_tmp * t25 * 36.0) + f_t203_tmp * t25 * 36.0) +
            h_t203_tmp * t28 * 36.0) + i_t203_tmp * t28 * 36.0) + t203_tmp * t25 * 36.0) + t203_tmp *
            t28 * 36.0) + b_t203_tmp * t23 * 36.0) + b_t203_tmp * t28 * 36.0) + c_t203_tmp * t23 *
            36.0) + c_t203_tmp * t25 * 36.0) + d_t203_tmp * t28 * 36.0) + e_t203_tmp * t25 * 36.0) +
                                f_t203_tmp * t23 * 36.0) + g_t203_tmp * t28 * 36.0) + h_t203_tmp *
                              t25 * 36.0) + i_t203_tmp * t23 * 36.0) + t2 * t86_tmp * 48.0) +
                           t83_tmp * t3 * 48.0) + t2 * t91_tmp * 48.0) + t83_tmp * t4 * 48.0) + t3 *
                        t91_tmp * 48.0) + t86_tmp * t4 * 48.0) * 6.0;
        d = in3[0] * in7[0];
        d1 = d * t2;
        d2 = in3[1] * in7[1];
        d3 = d2 * t2;
        d4 = in3[2] * in7[2];
        d5 = in3[0] * in7[1] * in2[1];
        d6 = in3[1] * in7[0] * in2[0];
        d7 = in3[0] * in7[2];
        d8 = in3[2] * in7[0] * in2[0];
        d9 = in3[1] * in7[2];
        d10 = in3[2] * in7[1] * in2[1];
        d11 = d7 * in2[2];
        d12 = in7[1] * in6[1];
        d13 = in7[2] * in6[2];
        d14 = in7[0] * in6[0];
        t205_tmp = d9 * in2[2];
        t205 = kappa0 * kappa1 * t201 * ((((((((((((((((((((((((((((((((((((((((((((((((((((((((d5 *
            t4 * in6[0] + d11 * t3 * in6[0]) + d6 * t4 * in6[1]) + d9 * t2 * in2[2] * in6[1]) + d8 *
            t3 * in6[2]) + d10 * t2 * in6[2]) + d * t3 * t4 * -2.0) + d3 * t4 * -2.0) + d4 * t2 * t3
            * -2.0) + d1 * t3 * 8.0) + d1 * t4 * 8.0) + d3 * t3 * 8.0) + d12 * t34 * 9.0) + d13 *
            t32 * 9.0) + d14 * t36 * 9.0) + d13 * t33 * 9.0) + d14 * t37 * 9.0) + d12 * t35 * 9.0) +
            d2 * t3 * t4 * 8.0) + in3[2] * in7[2] * t2 * t4 * 8.0) + d4 * t3 * t4 * 8.0) + d * t86)
            + d2 * t83) + d * t89) + d * t90) + d * t91) + d4 * t83) + d2 * t87) + d2 * t88) + d2 *
            t91) + d4 * t84) + d4 * t85) + d4 * t86) + -(d5 * t2 * in6[0] * 8.0)) + -(d6 * t3 * in6
            [1] * 8.0)) + -(d7 * t2 * in2[2] * in6[0] * 8.0)) + -(t32_tmp * t53 * 9.0)) + -(t33_tmp *
            t51 * 9.0)) + -(t32_tmp * t55 * 9.0)) + -(t37_tmp * t50 * 9.0)) + -(d8 * t4 * in6[2] *
            8.0)) + -(t33_tmp * t54 * 9.0)) + -(t205_tmp * t3 * in6[1] * 8.0)) + -(t37_tmp * t52 *
            9.0)) + -(d10 * t4 * in6[2] * 8.0)) + -(d6 * t2 * in6[1] * 8.0)) + -(d5 * t3 * in6[0] *
            8.0)) + -(d8 * t2 * in6[2] * 8.0)) + -(d12 * t45 * 9.0)) + -(d14 * t47 * 9.0)) + -(d13 *
            t44 * 9.0)) + -(d11 * t4 * in6[0] * 8.0)) + -(d14 * t49 * 9.0)) + -(d13 * t46 * 9.0)) +
            -(d12 * t48 * 9.0)) + -(d10 * t3 * in6[2] * 8.0)) + -(t205_tmp * t4 * in6[1] * 8.0)) *
            6.0;
        CoefPS[0] = -t205;
        CoefPS_tmp_tmp = ((((((((((t32 + t33) + t34) + t35) + t36) + t37) - t44) - t45) - t46) - t47)
                          - t48) - t49;
        CoefPS_tmp = kappa0 * ((t23 + t25) + t28) * t201 * CoefPS_tmp_tmp;
        CoefPS[1] = CoefPS_tmp * -108.0;
        b_CoefPS_tmp = ((((((((((t38 + t39) + t40) + t41) + t42) + t43) - t50) - t51) - t52) - t53)
                        - t54) - t55;
        c_CoefPS_tmp = kappa1 * ((t14 + t16) + t19) * t201 * b_CoefPS_tmp;
        CoefPS[2] = c_CoefPS_tmp * 216.0;
        CoefPS[3] = t203;
        d_CoefPS_tmp = t8 * t14;
        e_CoefPS_tmp = t9 * t16;
        f_CoefPS_tmp = t10 * t19;
        CoefPS[4] = std::pow(kappa1, 2.0) * t201 * ((((((((((((((((((((((((((((((((((((((t9 * t83 +
            t10 * t83) + t8 * t86) + t10 * t84) + t10 * t85) + t9 * t87) + t10 * t86) + t8 * t89) +
            t9 * t88) + t8 * t90) + t8 * t91) + t9 * t91) - t50_tmp * t39 * 16.0) - t52_tmp * t38 *
            16.0) - t50_tmp * t41 * 16.0) + t50_tmp * t42 * 2.0) + t52_tmp * t40 * 2.0) + t54_tmp *
            t38 * 2.0) + t50_tmp * t43 * 2.0) + t52_tmp * t41 * 2.0) + t54_tmp * t39 * 2.0) -
            t54_tmp * t40 * 16.0) - t52_tmp * t43 * 16.0) - t54_tmp * t42 * 16.0) - t52_tmp * t51 *
            2.0) - t54_tmp * t50 * 2.0) - t54_tmp * t52 * 2.0) - t201_tmp * t10 * 2.0) - b_t201_tmp *
            t9 * 2.0) - c_t201_tmp * t8 * 2.0) + d_CoefPS_tmp * t25 * 8.0) + e_CoefPS_tmp * t23 *
            8.0) + d_CoefPS_tmp * t28 * 8.0) + f_CoefPS_tmp * t23 * 8.0) + e_CoefPS_tmp * t28 * 8.0)
            + f_CoefPS_tmp * t25 * 8.0) - in7[0] * in7[2] * in6[0] * in6[2] * t16 * 18.0) - in7[1] *
            in7[2] * in6[1] * in6[2] * t14 * 18.0) - in7[0] * in7[1] * in6[0] * in6[1] * t19 * 18.0)
            * 18.0;
        CoefPS[5] = kappa1 * t111 * t201 * b_CoefPS_tmp * -108.0;
        d15 = kappa1 * in1[0] * in2[0];
        d16 = kappa1 * in1[1] * in2[1];
        d17 = kappa1 * in1[2] * in2[2];
        d18 = kappa1 * in5[0] * in2[0];
        d19 = kappa1 * in5[1] * in2[1];
        d20 = kappa1 * in5[2] * in2[2];
        d21 = kappa1 * in7[0];
        d22 = d21 * in1[0];
        d23 = kappa1 * in7[1];
        d24 = d23 * in1[1];
        d25 = kappa1 * in7[2];
        d26 = d25 * in1[2];
        d27 = d21 * in5[0];
        d28 = d23 * in5[1];
        d29 = d25 * in5[2];
        d30 = d26 * t2;
        d31 = d27 * t2;
        d32 = d28 * t2;
        d33 = d29 * t2;
        d34 = d22 * t14;
        d35 = d24 * t16;
        d36 = d26 * t19;
        d37 = d27 * t14;
        d38 = d28 * t16;
        d39 = d29 * t19;
        d40 = d21 * in1[1];
        d41 = d40 * in2[0];
        d42 = d23 * in1[0];
        d43 = d42 * in2[1];
        d44 = d21 * in1[2];
        d45 = d44 * in2[0];
        d46 = d25 * in1[0];
        d47 = d23 * in1[2];
        CoefPS_tmp_tmp_tmp = d25 * in1[1];
        g_CoefPS_tmp = CoefPS_tmp_tmp_tmp * in2[2];
        b_CoefPS_tmp_tmp = d21 * in5[1];
        h_CoefPS_tmp = b_CoefPS_tmp_tmp * in2[0];
        c_CoefPS_tmp_tmp = d23 * in5[0];
        i_CoefPS_tmp = c_CoefPS_tmp_tmp * in2[1];
        d_CoefPS_tmp_tmp = d21 * in5[2];
        j_CoefPS_tmp = d_CoefPS_tmp_tmp * in2[0];
        k_CoefPS_tmp = d25 * in5[0];
        l_CoefPS_tmp = k_CoefPS_tmp * in2[2];
        e_CoefPS_tmp_tmp = d23 * in5[2];
        m_CoefPS_tmp = e_CoefPS_tmp_tmp * in2[1];
        n_CoefPS_tmp = d25 * in5[1];
        o_CoefPS_tmp = n_CoefPS_tmp * in2[2];
        p_CoefPS_tmp = d22 * t2;
        q_CoefPS_tmp = d24 * t2;
        r_CoefPS_tmp = kappa1 * in7[1] * in1[2] * in2[1];
        CoefPS[6] = t201 *
            (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
            (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t16 * t26 *
            72.0 + t14 * t29 * 72.0) + t14 * t31 * 72.0) + t19 * t26 * 72.0) + t16 * t31 * 72.0) +
            t19 * t29 * 72.0) + t83_tmp * t23 * 40.0) + t86_tmp * t23 * 112.0) + t83_tmp * t25 *
            112.0) + t91_tmp * t23 * 112.0) + t86_tmp * t25 * 40.0) + t91_tmp * t25 * 112.0) +
            t83_tmp * t28 * 112.0) + t86_tmp * t28 * 112.0) + t91_tmp * t28 * 40.0) - t201_tmp * t23
            * 64.0) - b_t201_tmp * t23 * 64.0) - t201_tmp * t25 * 64.0) - c_t201_tmp * t23 * 64.0) -
            b_t201_tmp * t25 * 64.0) - c_t201_tmp * t25 * 64.0) - t201_tmp * t28 * 64.0) -
            b_t201_tmp * t28 * 64.0) - c_t201_tmp * t28 * 64.0) + t84_tmp * t28 * 144.0) + t85_tmp *
            t28 * 144.0) + t88_tmp * t25 * 144.0) + d15 * t39 * 120.0) + d16 * t38 * 120.0) + d15 *
            t41 * 120.0) - d15 * t42 * 60.0) - d16 * t40 * 60.0) - d17 * t38 * 60.0) - d15 * t43 *
            60.0) - d16 * t41 * 60.0) - d17 * t39 * 60.0) + d17 * t40 * 120.0) + d16 * t43 * 120.0)
            + d17 * t42 * 120.0) - d18 * t39 * 120.0) - d19 * t38 * 120.0) - d18 * t41 * 120.0) +
            d18 * t42 * 60.0) + d19 * t40 * 60.0) + d20 * t38 * 60.0) + d15 * t53 * 60.0) + d16 *
            t51 * 60.0) + d18 * t43 * 60.0) + d19 * t41 * 60.0) + d20 * t39 * 60.0) + d17 * t50 *
            60.0) - d20 * t40 * 120.0) + d15 * t55 * 60.0) - d19 * t43 * 120.0) + d16 * t54 * 60.0)
            + d17 * t52 * 60.0) - d20 * t42 * 120.0) - d18 * t53 * 60.0) - d19 * t51 * 60.0) - d20 *
            t50 * 60.0) - d18 * t55 * 60.0) - d19 * t54 * 60.0) - d20 * t52 * 60.0) - d22 * t86_tmp *
            160.0) - d22 * t91_tmp * 160.0) - d24 * t83_tmp * 160.0) - d24 * t91_tmp * 160.0) - d26 *
            t83_tmp * 160.0) - d26 * t86_tmp * 160.0) + d27 * t86_tmp * 160.0) + d27 * t91_tmp *
            160.0) + d28 * t83_tmp * 160.0) + d28 * t91_tmp * 160.0) + d29 * t83_tmp * 160.0) + d29 *
            t86_tmp * 160.0) - p_CoefPS_tmp * t3 * 40.0) - p_CoefPS_tmp * t4 * 40.0) + d22 * t3 * t4
            * 40.0) - q_CoefPS_tmp * t3 * 40.0) + q_CoefPS_tmp * t4 * 40.0) - d24 * t3 * t4 * 40.0)
            + d30 * t3 * 40.0) - d30 * t4 * 40.0) - d26 * t3 * t4 * 40.0) + d31 * t3 * 40.0) + d31 *
            t4 * 40.0) - d27 * t3 * t4 * 40.0) + d32 * t3 * 40.0) - d32 * t4 * 40.0) + d28 * t3 * t4
            * 40.0) - d33 * t3 * 40.0) + d33 * t4 * 40.0) + d29 * t3 * t4 * 40.0) - d34 * t25 *
            120.0) - d35 * t23 * 120.0) - d34 * t28 * 120.0) - d26 * t14 * t25 * 180.0) - d26 * t16 *
            t23 * 180.0) - d22 * t16 * t28 * 180.0) - d22 * t19 * t25 * 180.0) - d24 * t14 * t28 *
            180.0) - d24 * t19 * t23 * 180.0) - d35 * t28 * 120.0) - d36 * t23 * 120.0) - d36 * t25 *
            120.0) + d37 * t25 * 120.0) + d38 * t23 * 120.0) + d37 * t28 * 120.0) + d29 * t14 * t25 *
            180.0) + d29 * t16 * t23 * 180.0) + d27 * t16 * t28 * 180.0) + d27 * t19 * t25 * 180.0)
            + d28 * t14 * t28 * 180.0) + d28 * t19 * t23 * 180.0) + d38 * t28 * 120.0) + d39 * t23 *
            120.0) + d39 * t25 * 120.0) + d41 * t2 * in6[1] * 160.0) + d43 * t2 * in6[0] * 40.0) +
            d41 * t3 * in6[1] * 40.0) + d43 * t3 * in6[0] * 160.0) - d41 * t4 * in6[1] * 20.0) + d45
            * t2 * in6[2] * 160.0) - d43 * t4 * in6[0] * 20.0) + d46 * t2 * in2[2] * in6[0] * 40.0)
            - d45 * t3 * in6[2] * 20.0) - d46 * in2[2] * t3 * in6[0] * 20.0) + d45 * t4 * in6[2] *
            40.0) - d47 * in2[1] * t2 * in6[2] * 20.0) + d25 * in1[0] * in2[2] * t4 * in6[0] * 160.0)
            - CoefPS_tmp_tmp_tmp * t2 * in2[2] * in6[1] * 20.0) + r_CoefPS_tmp * t3 * in6[2] * 160.0)
            + g_CoefPS_tmp * t3 * in6[1] * 40.0) + r_CoefPS_tmp * t4 * in6[2] * 40.0) + g_CoefPS_tmp
            * t4 * in6[1] * 160.0) - h_CoefPS_tmp * t2 * in6[1] * 160.0) - i_CoefPS_tmp * t2 * in6[0]
            * 40.0) - h_CoefPS_tmp * t3 * in6[1] * 40.0) - i_CoefPS_tmp * t3 * in6[0] * 160.0) +
            h_CoefPS_tmp * t4 * in6[1] * 20.0) - j_CoefPS_tmp * t2 * in6[2] * 160.0) + i_CoefPS_tmp *
            t4 * in6[0] * 20.0) - k_CoefPS_tmp * t2 * in2[2] * in6[0] * 40.0) + j_CoefPS_tmp * t3 *
            in6[2] * 20.0) + l_CoefPS_tmp * t3 * in6[0] * 20.0) - j_CoefPS_tmp * t4 * in6[2] * 40.0)
                               + m_CoefPS_tmp * t2 * in6[2] * 20.0) - l_CoefPS_tmp * t4 * in6[0] *
                              160.0) + n_CoefPS_tmp * t2 * in2[2] * in6[1] * 20.0) - m_CoefPS_tmp *
                            t3 * in6[2] * 160.0) - o_CoefPS_tmp * t3 * in6[1] * 40.0) - m_CoefPS_tmp
                          * t4 * in6[2] * 40.0) - o_CoefPS_tmp * t4 * in6[1] * 160.0) + d44 * in6[0]
                        * in6[2] * t16 * 180.0) + d47 * in6[1] * in6[2] * t14 * 180.0) + d46 * in6[0]
                      * in6[2] * t16 * 180.0) + CoefPS_tmp_tmp_tmp * in6[1] * in6[2] * t14 * 180.0)
                    + d40 * in6[0] * in6[1] * t19 * 180.0) + d42 * in6[0] * in6[1] * t19 * 180.0) -
                  d_CoefPS_tmp_tmp * in6[0] * in6[2] * t16 * 180.0) - e_CoefPS_tmp_tmp * in6[1] *
                 in6[2] * t14 * 180.0) - k_CoefPS_tmp * in6[0] * in6[2] * t16 * 180.0) -
               n_CoefPS_tmp * in6[1] * in6[2] * t14 * 180.0) - b_CoefPS_tmp_tmp * in6[0] * in6[1] *
              t19 * 180.0) - c_CoefPS_tmp_tmp * in6[0] * in6[1] * t19 * 180.0) * 6.0;
        d48 = in1[2] * t83_tmp;
        d49 = in1[0] * t2;
        d50 = in1[1] * t2;
        d51 = in1[2] * t2;
        d52 = in5[0] * t2;
        d53 = in1[0] * in2[0];
        d54 = in1[1] * in2[1];
        d55 = in5[1] * t2;
        d56 = d53 * t2;
        d57 = d53 * t4;
        d58 = d54 * t2;
        d59 = d54 * t3;
        d60 = d54 * t4;
        d61 = in5[2] * t83_tmp;
        d62 = d53 * t3;
        d63 = d51 * in2[2];
        d64 = in1[0] * t3;
        d65 = in1[1] * t3;
        d66 = in1[2] * t3;
        d67 = in5[0] * t3;
        d68 = in5[1] * t3;
        d69 = in5[2] * t2;
        d70 = in1[2] * in2[2];
        d71 = d70 * t3;
        s_CoefPS_tmp = in5[0] * in2[0];
        t_CoefPS_tmp = in5[1] * in2[1];
        u_CoefPS_tmp = s_CoefPS_tmp * t2;
        v_CoefPS_tmp = s_CoefPS_tmp * t3;
        w_CoefPS_tmp = d69 * in2[2];
        x_CoefPS_tmp = in5[2] * in2[2];
        y_CoefPS_tmp = s_CoefPS_tmp * t4;
        ab_CoefPS_tmp = t_CoefPS_tmp * t2;
        bb_CoefPS_tmp = x_CoefPS_tmp * t3;
        cb_CoefPS_tmp = t_CoefPS_tmp * t3;
        db_CoefPS_tmp = x_CoefPS_tmp * t4;
        eb_CoefPS_tmp = t_CoefPS_tmp * t4;
        fb_CoefPS_tmp = in1[2] * in6[2];
        gb_CoefPS_tmp = in1[0] * in6[0];
        hb_CoefPS_tmp = in1[1] * in6[1];
        ib_CoefPS_tmp = in5[2] * in6[2];
        jb_CoefPS_tmp = in5[0] * in6[0];
        kb_CoefPS_tmp = in5[1] * in6[1];
        lb_CoefPS_tmp = in5[2] * t3;
        mb_CoefPS_tmp = d70 * t4;
        CoefPS[7] = t201 *
            (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
            ((((((in1[0] * t83_tmp * in6[0] * 80.0 + in1[0] * t86_tmp * in6[0] * 200.0) + in1[0] *
            t91_tmp * in6[0] * 200.0) + in1[1] * t83_tmp * in6[1] * 200.0) + in1[1] * t86_tmp * in6
            [1] * 80.0) + in1[1] * t91_tmp * in6[1] * 200.0) + d48 * in6[2] * 200.0) + in1[2] *
            t86_tmp * in6[2] * 200.0) + in1[2] * t91_tmp * in6[2] * 80.0) - in5[0] * t83_tmp * in6[0]
            * 80.0) - in5[0] * t86_tmp * in6[0] * 200.0) - in5[0] * t91_tmp * in6[0] * 200.0) - in5
            [1] * t83_tmp * in6[1] * 200.0) - in5[1] * t86_tmp * in6[1] * 80.0) - in5[1] * t91_tmp *
            in6[1] * 200.0) - d61 * in6[2] * 200.0) - in5[2] * t86_tmp * in6[2] * 200.0) - in5[2] *
            t91_tmp * in6[2] * 80.0) + in1[0] * t16 * t24 * 180.0) + in1[1] * t14 * t27 * 180.0) +
            in1[0] * t19 * t24 * 180.0) + in1[2] * t14 * t30 * 180.0) + in1[1] * t19 * t27 * 180.0)
            + in1[2] * t16 * t30 * 180.0) - in5[0] * t16 * t24 * 180.0) - in5[1] * t14 * t27 * 180.0)
            - in5[0] * t19 * t24 * 180.0) - in5[2] * t14 * t30 * 180.0) - in5[1] * t19 * t27 * 180.0)
            - in5[2] * t16 * t30 * 180.0) - d49 * t3 * in6[0] * 80.0) - d49 * t4 * in6[0] * 80.0) +
            d64 * t4 * in6[0] * 40.0) - d50 * t3 * in6[1] * 80.0) + d50 * t4 * in6[1] * 40.0) - d65 *
            t4 * in6[1] * 80.0) + d51 * t3 * in6[2] * 40.0) - d51 * t4 * in6[2] * 80.0) - d66 * t4 *
            in6[2] * 80.0) + d52 * t3 * in6[0] * 80.0) + d52 * t4 * in6[0] * 80.0) + d56 * t25 *
            60.0) - d58 * t23 * 120.0) - d67 * t4 * in6[0] * 40.0) + d55 * t3 * in6[1] * 80.0) - d62
            * t25 * 120.0) + d59 * t23 * 60.0) - d55 * t4 * in6[1] * 40.0) - d57 * t25 * 120.0) -
            d60 * t23 * 120.0) - d63 * t23 * 120.0) + d68 * t4 * in6[1] * 80.0) - d69 * t3 * in6[2] *
            40.0) + d56 * t28 * 60.0) - d71 * t23 * 120.0) + d69 * t4 * in6[2] * 80.0) - d62 * t28 *
            120.0) - d63 * t25 * 120.0) + mb_CoefPS_tmp * t23 * 60.0) + lb_CoefPS_tmp * t4 * in6[2] *
            80.0) - d57 * t28 * 120.0) - d58 * t28 * 120.0) - d71 * t25 * 120.0) + d59 * t28 * 60.0)
            + mb_CoefPS_tmp * t25 * 60.0) - d60 * t28 * 120.0) - u_CoefPS_tmp * t25 * 60.0) +
            ab_CoefPS_tmp * t23 * 120.0) + v_CoefPS_tmp * t25 * 120.0) - cb_CoefPS_tmp * t23 * 60.0)
            + y_CoefPS_tmp * t25 * 120.0) + eb_CoefPS_tmp * t23 * 120.0) + w_CoefPS_tmp * t23 *
            120.0) - u_CoefPS_tmp * t28 * 60.0) + bb_CoefPS_tmp * t23 * 120.0) + v_CoefPS_tmp * t28 *
            120.0) + w_CoefPS_tmp * t25 * 120.0) - db_CoefPS_tmp * t23 * 60.0) + y_CoefPS_tmp * t28 *
                              120.0) + ab_CoefPS_tmp * t28 * 120.0) + bb_CoefPS_tmp * t25 * 120.0) -
                           cb_CoefPS_tmp * t28 * 60.0) - db_CoefPS_tmp * t25 * 60.0) + eb_CoefPS_tmp
                         * t28 * 120.0) + fb_CoefPS_tmp * t14 * t25 * 180.0) + fb_CoefPS_tmp * t16 *
                       t23 * 180.0) + gb_CoefPS_tmp * t16 * t28 * 180.0) + gb_CoefPS_tmp * t19 * t25
                     * 180.0) + hb_CoefPS_tmp * t14 * t28 * 180.0) + hb_CoefPS_tmp * t19 * t23 *
                   180.0) - ib_CoefPS_tmp * t14 * t25 * 180.0) - ib_CoefPS_tmp * t16 * t23 * 180.0)
                - jb_CoefPS_tmp * t16 * t28 * 180.0) - jb_CoefPS_tmp * t19 * t25 * 180.0) -
              kb_CoefPS_tmp * t14 * t28 * 180.0) - kb_CoefPS_tmp * t19 * t23 * 180.0) * 6.0;
        CoefPS[8] = t205;
        CoefPS[9] = c_CoefPS_tmp * -108.0;
        CoefPS[10] = CoefPS_tmp * 216.0;
        CoefPS[11] = -t203;
        CoefPS[12] = std::pow(kappa0, 2.0) * t201 * ((((((((((((((((((((((((((((((((((((((t6 * t83 +
            t7 * t83) + t5 * t86) + t7 * t84) + t7 * t85) + t6 * t87) + t7 * t86) + t5 * t89) + t6 *
            t88) + t5 * t90) + t5 * t91) + t6 * t91) - t44_tmp * t33 * 16.0) - t46_tmp * t32 * 16.0)
            - t44_tmp * t35 * 16.0) + t44_tmp * t36 * 2.0) + t46_tmp * t34 * 2.0) + t48_tmp * t32 *
            2.0) + t44_tmp * t37 * 2.0) + t46_tmp * t35 * 2.0) + t48_tmp * t33 * 2.0) - t48_tmp *
            t34 * 16.0) - t46_tmp * t37 * 16.0) - t48_tmp * t36 * 16.0) - t46_tmp * t45 * 2.0) -
            t48_tmp * t44 * 2.0) - t48_tmp * t46 * 2.0) - t201_tmp * t7 * 2.0) - b_t201_tmp * t6 *
            2.0) - c_t201_tmp * t5 * 2.0) + t5 * t16 * t23 * 8.0) + t6 * t14 * t25 * 8.0) + t5 * t19
            * t23 * 8.0) + t7 * t14 * t28 * 8.0) + t6 * t19 * t25 * 8.0) + t7 * t16 * t28 * 8.0) -
            in3[0] * in3[2] * in2[0] * in2[2] * t25 * 18.0) - in3[1] * in3[2] * in2[1] * in2[2] *
            t23 * 18.0) - in3[0] * in3[1] * in2[0] * in2[1] * t28 * 18.0) * -18.0;
        CoefPS[13] = kappa0 * t111 * t201 * CoefPS_tmp_tmp * -108.0;
        d72 = kappa0 * in1[0] * in6[0];
        d73 = kappa0 * in1[1] * in6[1];
        d74 = kappa0 * in1[2] * in6[2];
        d75 = kappa0 * in5[0] * in6[0];
        d76 = kappa0 * in5[1] * in6[1];
        d77 = kappa0 * in5[2] * in6[2];
        d78 = kappa0 * in3[0];
        d79 = d78 * in1[0];
        d80 = kappa0 * in3[1];
        d81 = d80 * in1[1];
        d82 = kappa0 * in3[2];
        d83 = d82 * in1[2];
        d84 = d78 * in5[0];
        d85 = d80 * in5[1];
        d86 = d82 * in5[2];
        d87 = d83 * t2;
        d88 = d84 * t2;
        d89 = d85 * t2;
        d90 = d86 * t2;
        d91 = d79 * t16;
        d92 = d79 * t19;
        d93 = d81 * t14;
        d94 = d81 * t19;
        d95 = d83 * t14;
        d96 = d83 * t16;
        d97 = d84 * t16;
        d98 = d84 * t19;
        d99 = d85 * t14;
        d100 = d85 * t19;
        d101 = d86 * t14;
        d102 = d86 * t16;
        d103 = d78 * in1[1];
        d104 = d103 * in2[1];
        d105 = d80 * in1[0] * in2[0];
        d106 = d78 * in1[2];
        d107 = d82 * in1[0] * in2[0];
        d108 = d80 * in1[2];
        f_CoefPS_tmp_tmp = d82 * in1[1] * in2[1];
        g_CoefPS_tmp_tmp = d78 * in5[1];
        nb_CoefPS_tmp = g_CoefPS_tmp_tmp * in2[1];
        ob_CoefPS_tmp = d80 * in5[0] * in2[0];
        pb_CoefPS_tmp = d78 * in5[2];
        qb_CoefPS_tmp = d82 * in5[0] * in2[0];
        rb_CoefPS_tmp = pb_CoefPS_tmp * in2[2];
        sb_CoefPS_tmp = d80 * in5[2];
        tb_CoefPS_tmp = d82 * in5[1] * in2[1];
        ub_CoefPS_tmp = sb_CoefPS_tmp * in2[2];
        vb_CoefPS_tmp = d79 * t2;
        wb_CoefPS_tmp = d81 * t2;
        xb_CoefPS_tmp = d106 * in2[2];
        CoefPS[14] = t201 *
            (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
            (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t17 * t25 *
            72.0 + t20 * t23 * 72.0) + t17 * t28 * 72.0) + t22 * t23 * 72.0) + t22 * t25 * 72.0) +
            t20 * t28 * 72.0) + t83_tmp * t14 * 40.0) + t86_tmp * t14 * 112.0) + t83_tmp * t16 *
            112.0) + t91_tmp * t14 * 112.0) + t86_tmp * t16 * 40.0) + t91_tmp * t16 * 112.0) +
            t83_tmp * t19 * 112.0) + t86_tmp * t19 * 112.0) + t91_tmp * t19 * 40.0) - t201_tmp * t14
            * 64.0) - b_t201_tmp * t14 * 64.0) - t201_tmp * t16 * 64.0) - c_t201_tmp * t14 * 64.0) -
            b_t201_tmp * t16 * 64.0) - c_t201_tmp * t16 * 64.0) - t201_tmp * t19 * 64.0) -
            b_t201_tmp * t19 * 64.0) - c_t201_tmp * t19 * 64.0) + t14 * t16 * t28 * 144.0) + t14 *
            t19 * t25 * 144.0) + t16 * t19 * t23 * 144.0) - d72 * t33 * 120.0) - d73 * t32 * 120.0)
            - d72 * t35 * 120.0) + d72 * t36 * 60.0) + d73 * t34 * 60.0) + d74 * t32 * 60.0) + d72 *
            t37 * 60.0) + d73 * t35 * 60.0) + d74 * t33 * 60.0) - d74 * t34 * 120.0) - d73 * t37 *
            120.0) - d74 * t36 * 120.0) + d75 * t33 * 120.0) + d76 * t32 * 120.0) + d75 * t35 *
            120.0) - d75 * t36 * 60.0) - d76 * t34 * 60.0) - d77 * t32 * 60.0) - d72 * t47 * 60.0) -
            d73 * t45 * 60.0) - d75 * t37 * 60.0) - d76 * t35 * 60.0) - d77 * t33 * 60.0) - d74 *
            t44 * 60.0) + d77 * t34 * 120.0) - d72 * t49 * 60.0) + d76 * t37 * 120.0) - d73 * t48 *
            60.0) - d74 * t46 * 60.0) + d77 * t36 * 120.0) + d75 * t47 * 60.0) + d76 * t45 * 60.0) +
            d77 * t44 * 60.0) + d75 * t49 * 60.0) + d76 * t48 * 60.0) + d77 * t46 * 60.0) + d79 *
            t86_tmp * 160.0) + d79 * t91_tmp * 160.0) + d81 * t83_tmp * 160.0) + d81 * t91_tmp *
            160.0) + d83 * t83_tmp * 160.0) + d83 * t86_tmp * 160.0) - d84 * t86_tmp * 160.0) - d84 *
            t91_tmp * 160.0) - d85 * t83_tmp * 160.0) - d85 * t91_tmp * 160.0) - d86 * t83_tmp *
            160.0) - d86 * t86_tmp * 160.0) + vb_CoefPS_tmp * t3 * 40.0) + vb_CoefPS_tmp * t4 * 40.0)
            - d79 * t3 * t4 * 40.0) + wb_CoefPS_tmp * t3 * 40.0) - wb_CoefPS_tmp * t4 * 40.0) + d81 *
            t3 * t4 * 40.0) - d87 * t3 * 40.0) + d87 * t4 * 40.0) + d83 * t3 * t4 * 40.0) - d88 * t3
            * 40.0) - d88 * t4 * 40.0) + d84 * t3 * t4 * 40.0) - d89 * t3 * 40.0) + d89 * t4 * 40.0)
            - d85 * t3 * t4 * 40.0) + d90 * t3 * 40.0) - d90 * t4 * 40.0) - d86 * t3 * t4 * 40.0) +
            d91 * t23 * 120.0) + d93 * t25 * 120.0) + d92 * t23 * 120.0) + d95 * t25 * 180.0) + d96 *
            t23 * 180.0) + d91 * t28 * 180.0) + d92 * t25 * 180.0) + d93 * t28 * 180.0) + d94 * t23 *
            180.0) + d94 * t25 * 120.0) + d95 * t28 * 120.0) + d96 * t28 * 120.0) - d97 * t23 *
            120.0) - d99 * t25 * 120.0) - d98 * t23 * 120.0) - d101 * t25 * 180.0) - d102 * t23 *
            180.0) - d97 * t28 * 180.0) - d98 * t25 * 180.0) - d99 * t28 * 180.0) - d100 * t23 *
            180.0) - d100 * t25 * 120.0) - d101 * t28 * 120.0) - d102 * t28 * 120.0) - d104 * t2 *
            in6[0] * 160.0) - d105 * t2 * in6[1] * 40.0) - d104 * t3 * in6[0] * 40.0) - d105 * t3 *
            in6[1] * 160.0) + d104 * t4 * in6[0] * 20.0) - d106 * t2 * in2[2] * in6[0] * 160.0) +
            d105 * t4 * in6[1] * 20.0) - d107 * t2 * in6[2] * 40.0) + xb_CoefPS_tmp * t3 * in6[0] *
            20.0) + d107 * t3 * in6[2] * 20.0) - xb_CoefPS_tmp * t4 * in6[0] * 40.0) + d108 * t2 *
            in2[2] * in6[1] * 20.0) - d107 * t4 * in6[2] * 160.0) + f_CoefPS_tmp_tmp * t2 * in6[2] *
            20.0) - kappa0 * in3[1] * in1[2] * in2[2] * t3 * in6[1] * 160.0) - f_CoefPS_tmp_tmp * t3
            * in6[2] * 40.0) - d108 * in2[2] * t4 * in6[1] * 40.0) - f_CoefPS_tmp_tmp * t4 * in6[2] *
            160.0) + nb_CoefPS_tmp * t2 * in6[0] * 160.0) + ob_CoefPS_tmp * t2 * in6[1] * 40.0) +
            nb_CoefPS_tmp * t3 * in6[0] * 40.0) + ob_CoefPS_tmp * t3 * in6[1] * 160.0) -
            nb_CoefPS_tmp * t4 * in6[0] * 20.0) + pb_CoefPS_tmp * t2 * in2[2] * in6[0] * 160.0) -
            ob_CoefPS_tmp * t4 * in6[1] * 20.0) + qb_CoefPS_tmp * t2 * in6[2] * 40.0) -
            rb_CoefPS_tmp * t3 * in6[0] * 20.0) - qb_CoefPS_tmp * t3 * in6[2] * 20.0) +
            rb_CoefPS_tmp * t4 * in6[0] * 40.0) - sb_CoefPS_tmp * t2 * in2[2] * in6[1] * 20.0) +
                              qb_CoefPS_tmp * t4 * in6[2] * 160.0) - tb_CoefPS_tmp * t2 * in6[2] *
                             20.0) - d106 * in2[0] * in2[2] * t25 * 180.0) - d108 * in2[1] * in2[2] *
                           t23 * 180.0) + ub_CoefPS_tmp * t3 * in6[1] * 160.0) - d107 * in2[2] * t25
                         * 180.0) - f_CoefPS_tmp_tmp * in2[2] * t23 * 180.0) + tb_CoefPS_tmp * t3 *
                       in6[2] * 40.0) - d103 * in2[0] * in2[1] * t28 * 180.0) - d105 * in2[1] * t28 *
                     180.0) + ub_CoefPS_tmp * t4 * in6[1] * 40.0) + tb_CoefPS_tmp * t4 * in6[2] *
                   160.0) + pb_CoefPS_tmp * in2[0] * in2[2] * t25 * 180.0) + sb_CoefPS_tmp * in2[1] *
                 in2[2] * t23 * 180.0) + qb_CoefPS_tmp * in2[2] * t25 * 180.0) + tb_CoefPS_tmp *
               in2[2] * t23 * 180.0) + g_CoefPS_tmp_tmp * in2[0] * in2[1] * t28 * 180.0) +
             ob_CoefPS_tmp * in2[1] * t28 * 180.0) * -6.0;
        d109 = in1[0] * t15;
        d110 = in1[1] * t18;
        d111 = in1[2] * t21;
        d112 = in5[0] * t15;
        d113 = in5[1] * t18;
        d114 = in5[2] * t21;
        d115 = d49 * in6[0];
        d116 = d50 * in6[1];
        d117 = d65 * in6[1];
        d118 = in1[0] * t4 * in6[0];
        d119 = in1[1] * t4 * in6[1];
        yb_CoefPS_tmp = in1[2] * t4 * in6[2];
        ac_CoefPS_tmp = d52 * in6[0];
        bc_CoefPS_tmp = d67 * in6[0];
        cc_CoefPS_tmp = d69 * in6[2];
        dc_CoefPS_tmp = in5[0] * t4 * in6[0];
        ec_CoefPS_tmp = d55 * in6[1];
        fc_CoefPS_tmp = lb_CoefPS_tmp * in6[2];
        gc_CoefPS_tmp = d68 * in6[1];
        hc_CoefPS_tmp = in5[2] * t4 * in6[2];
        ic_CoefPS_tmp = in5[1] * t4 * in6[1];
        jc_CoefPS_tmp = d64 * in6[0];
        CoefPS[15] = t201 *
            (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
            ((((((d53 * t83_tmp * 80.0 + d53 * t86_tmp * 200.0) + d53 * t91_tmp * 200.0) + d54 *
            t83_tmp * 200.0) + d54 * t86_tmp * 80.0) + d54 * t91_tmp * 200.0) + d48 * in2[2] * 200.0)
            + d70 * t86_tmp * 200.0) + d70 * t91_tmp * 80.0) - s_CoefPS_tmp * t83_tmp * 80.0) -
            s_CoefPS_tmp * t86_tmp * 200.0) - s_CoefPS_tmp * t91_tmp * 200.0) - t_CoefPS_tmp *
            t83_tmp * 200.0) - t_CoefPS_tmp * t86_tmp * 80.0) - t_CoefPS_tmp * t91_tmp * 200.0) -
            d61 * in2[2] * 200.0) - x_CoefPS_tmp * t86_tmp * 200.0) - x_CoefPS_tmp * t91_tmp * 80.0)
            + d109 * t25 * 180.0) + d110 * t23 * 180.0) + d109 * t28 * 180.0) + d111 * t23 * 180.0)
            + d110 * t28 * 180.0) + d111 * t25 * 180.0) - d112 * t25 * 180.0) - d113 * t23 * 180.0)
            - d112 * t28 * 180.0) - d114 * t23 * 180.0) - d113 * t28 * 180.0) - d114 * t25 * 180.0)
            - d56 * t3 * 80.0) - d56 * t4 * 80.0) + d62 * t4 * 40.0) - d58 * t3 * 80.0) + d58 * t4 *
            40.0) - d59 * t4 * 80.0) + d63 * t3 * 40.0) - d63 * t4 * 80.0) - d71 * t4 * 80.0) +
            u_CoefPS_tmp * t3 * 80.0) + u_CoefPS_tmp * t4 * 80.0) - v_CoefPS_tmp * t4 * 40.0) +
            ab_CoefPS_tmp * t3 * 80.0) - ab_CoefPS_tmp * t4 * 40.0) + cb_CoefPS_tmp * t4 * 80.0) -
            w_CoefPS_tmp * t3 * 40.0) + w_CoefPS_tmp * t4 * 80.0) + bb_CoefPS_tmp * t4 * 80.0) +
            d115 * t16 * 60.0) - d116 * t14 * 120.0) - jc_CoefPS_tmp * t16 * 120.0) + d117 * t14 *
            60.0) - d118 * t16 * 120.0) - d119 * t14 * 120.0) - d51 * in6[2] * t14 * 120.0) + d115 *
            t19 * 60.0) - d66 * in6[2] * t14 * 120.0) - jc_CoefPS_tmp * t19 * 120.0) - in1[2] * t2 *
            in6[2] * t16 * 120.0) + yb_CoefPS_tmp * t14 * 60.0) - d118 * t19 * 120.0) - d116 * t19 *
            120.0) - in1[2] * t3 * in6[2] * t16 * 120.0) + d117 * t19 * 60.0) + yb_CoefPS_tmp * t16 *
            60.0) - d119 * t19 * 120.0) - ac_CoefPS_tmp * t16 * 60.0) + ec_CoefPS_tmp * t14 * 120.0)
            + bc_CoefPS_tmp * t16 * 120.0) - gc_CoefPS_tmp * t14 * 60.0) + dc_CoefPS_tmp * t16 *
            120.0) + ic_CoefPS_tmp * t14 * 120.0) + cc_CoefPS_tmp * t14 * 120.0) - ac_CoefPS_tmp *
            t19 * 60.0) + fc_CoefPS_tmp * t14 * 120.0) + bc_CoefPS_tmp * t19 * 120.0) +
            cc_CoefPS_tmp * t16 * 120.0) - hc_CoefPS_tmp * t14 * 60.0) + d70 * t14 * t25 * 180.0) +
                             d70 * t16 * t23 * 180.0) + dc_CoefPS_tmp * t19 * 120.0) + ec_CoefPS_tmp
                           * t19 * 120.0) + fc_CoefPS_tmp * t16 * 120.0) + d53 * t16 * t28 * 180.0)
                        + d53 * t19 * t25 * 180.0) + d54 * t14 * t28 * 180.0) + d54 * t19 * t23 *
                      180.0) - gc_CoefPS_tmp * t19 * 60.0) - hc_CoefPS_tmp * t16 * 60.0) +
                   ic_CoefPS_tmp * t19 * 120.0) - x_CoefPS_tmp * t14 * t25 * 180.0) - x_CoefPS_tmp *
                 t16 * t23 * 180.0) - s_CoefPS_tmp * t16 * t28 * 180.0) - s_CoefPS_tmp * t19 * t25 *
               180.0) - t_CoefPS_tmp * t14 * t28 * 180.0) - t_CoefPS_tmp * t19 * t23 * 180.0) * -6.0;
    }

    //
    // We replace each sequence of small g-code segments with a B-Spline
    //  of degree 3
    //  A special queue is dedicated to the splines, ctx.q_splines
    // Arguments    : const FeedoptContext *ctx
    // Return Type  : void
    //
    static void CompressCurvStructs(const FeedoptContext *ctx)
    {
        double CumulatedLength;
        coder::array<double, 2U> pvec;
        CurvStruct b_ctx;
        CurvStruct Curv;
        CurvStruct SplineCurve;
        CurvStruct C;
        CurvStruct CurvStruct1_C;
        CurvStruct CurvStruct2_C;
        double P0[3];
        CurvStruct spline;
        double P1[3];
        CurvStruct b_CurvStruct2_C;
        CurvStruct CurvStruct3_C;
        coder::array<double, 2U> b_pvec;
        if (!ctx->q_gcode.isempty()) {
            unsigned int spline_index;
            unsigned int Ncrv;
            spline_index = ctx->q_splines.size() + 1U;
            Ncrv = ctx->q_gcode.size();
            CumulatedLength = 0.0;

            //  [mm]
            //  1 -> stdout
            //  2 -> stderr
            if ((static_cast<unsigned long>(std::round(DebugConfig)) & 1UL) != 0UL) {
                printf("Compressing...\n");
                fflush(stdout);
            }

            //  Satisfy coder
            //  -------------
            pvec.set_size(3, 0);
            ctx->q_gcode.get(1.0, (&b_ctx));

            //  -------------
            for (double k = 1.0; k <= Ncrv; k++) {
                ctx->q_gcode.get(k, (&Curv));
                if ((LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, Curv.Type, Curv.P0,
                                Curv.P1, Curv.evec, Curv.theta, Curv.pitch, Curv.CoeffP5,
                                Curv.sp_index, Curv.a_param, Curv.b_param) >= ctx->cfg.LThreshold) ||
                    (Curv.zspdmode != ZSpdMode_NN)) {
                    if (CumulatedLength == 0.0) {
                        if (Curv.zspdmode == ZSpdMode_ZN) {
                            CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz,
                                         ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                         ctx->cfg.ZeroStartAccLimit, ctx->cfg.ZeroStartJerkLimit,
                                         ctx->cfg.ZeroStartVelLimit, ctx->cfg.DebugCutZero,
                                         ctx->cfg.NGridLengthSpline, &Curv, k, &CurvStruct1_C,
                                         &CurvStruct2_C);
                            ctx->q_compress.push((&CurvStruct1_C));
                            ctx->q_compress.push((&CurvStruct2_C));
                        } else if (Curv.zspdmode == ZSpdMode_NZ) {
                            CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                       ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                       ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                       ctx->cfg.NGridLengthSpline, &Curv, k, &CurvStruct1_C,
                                       &CurvStruct2_C);
                            ctx->q_compress.push((&CurvStruct1_C));
                            ctx->q_compress.push((&CurvStruct2_C));
                        } else if (Curv.zspdmode == ZSpdMode_ZZ) {
                            CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz,
                                         ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                         ctx->cfg.ZeroStartAccLimit, ctx->cfg.ZeroStartJerkLimit,
                                         ctx->cfg.ZeroStartVelLimit, ctx->cfg.DebugCutZero,
                                         ctx->cfg.NGridLengthSpline, &Curv, k, &CurvStruct1_C,
                                         &CurvStruct2_C);
                            CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                       ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                       ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                       ctx->cfg.NGridLengthSpline, &CurvStruct2_C, k,
                                       &b_CurvStruct2_C, &CurvStruct3_C);
                            ctx->q_compress.push((&CurvStruct1_C));
                            ctx->q_compress.push((&b_CurvStruct2_C));
                            ctx->q_compress.push((&CurvStruct3_C));
                        } else {
                            ctx->q_compress.push((&Curv));
                        }
                    } else {
                        if (pvec.size(1) > 2) {
                            ConstrCurvStructType(&SplineCurve);
                            CalcBspline_Lee(ctx->cfg.SplineDegree, pvec, SplineCurve.sp.CoeffX,
                                            SplineCurve.sp.CoeffY, SplineCurve.sp.CoeffZ,
                                            &SplineCurve.sp.Bl.ncoeff, SplineCurve.sp.Bl.breakpoints,
                                            &SplineCurve.sp.Bl.handle, &SplineCurve.sp.Bl.degree,
                                            SplineCurve.sp.knots);
                            ctx->q_splines.push((&SplineCurve));
                            ConstrBSplineStruct(pvec, Curv.FeedRate, &spline);
                            spline.gcode_source_line = Curv.gcode_source_line;
                            spline.sp_index = static_cast<int>(spline_index);
                            spline_index++;
                            ctx->q_compress.push((&spline));
                            if (Curv.zspdmode == ZSpdMode_NZ) {
                                CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz,
                                           ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                           ctx->cfg.ZeroStartAccLimit, ctx->cfg.ZeroStartJerkLimit,
                                           ctx->cfg.ZeroStartVelLimit, ctx->cfg.NGridLengthSpline,
                                           &Curv, k, &CurvStruct1_C, &CurvStruct2_C);
                                ctx->q_compress.push((&CurvStruct1_C));
                                ctx->q_compress.push((&CurvStruct2_C));
                            } else {
                                ctx->q_compress.push((&Curv));
                            }
                        } else {
                            ctx->q_gcode.get((k - 1.0), (&C));
                            ctx->q_compress.push((&C));
                            if (Curv.zspdmode == ZSpdMode_NZ) {
                                CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz,
                                           ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                           ctx->cfg.ZeroStartAccLimit, ctx->cfg.ZeroStartJerkLimit,
                                           ctx->cfg.ZeroStartVelLimit, ctx->cfg.NGridLengthSpline,
                                           &Curv, k, &CurvStruct1_C, &CurvStruct2_C);
                                ctx->q_compress.push((&CurvStruct1_C));
                                ctx->q_compress.push((&CurvStruct2_C));
                            } else {
                                ctx->q_compress.push((&Curv));
                            }
                        }

                        CumulatedLength = 0.0;
                    }
                } else if ((static_cast<unsigned int>(k) == Ncrv) && (CumulatedLength != 0.0)) {
                    ConstrCurvStructType(&SplineCurve);
                    CalcBspline_Lee(ctx->cfg.SplineDegree, pvec, SplineCurve.sp.CoeffX,
                                    SplineCurve.sp.CoeffY, SplineCurve.sp.CoeffZ,
                                    &SplineCurve.sp.Bl.ncoeff, SplineCurve.sp.Bl.breakpoints,
                                    &SplineCurve.sp.Bl.handle, &SplineCurve.sp.Bl.degree,
                                    SplineCurve.sp.knots);
                    ctx->q_splines.push((&SplineCurve));
                    ConstrBSplineStruct(pvec, Curv.FeedRate, &spline);
                    spline.gcode_source_line = Curv.gcode_source_line;
                    spline.sp_index = static_cast<int>(spline_index);
                    ctx->q_compress.push((&spline));
                } else if (k == 1.0) {
                    ctx->q_compress.push((&Curv));
                } else {
                    int loop_ub;
                    int b_loop_ub;
                    if (CumulatedLength == 0.0) {
                        b_EvalCurvStruct(&ctx->q_splines, Curv.Type, Curv.P0, Curv.P1, Curv.evec,
                                         Curv.theta, Curv.pitch, Curv.CoeffP5, Curv.sp_index,
                                         Curv.b_param, P0);
                        pvec.set_size(3, 1);
                        pvec[0] = P0[0];
                        pvec[1] = P0[1];
                        pvec[2] = P0[2];
                    }

                    CumulatedLength += LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                        Curv.Type, Curv.P0, Curv.P1, Curv.evec, Curv.theta, Curv.pitch, Curv.CoeffP5,
                        Curv.sp_index, Curv.a_param, Curv.b_param);
                    c_EvalCurvStruct(&ctx->q_splines, Curv.Type, Curv.P0, Curv.P1, Curv.evec,
                                     Curv.theta, Curv.pitch, Curv.CoeffP5, Curv.sp_index,
                                     Curv.a_param, Curv.b_param, P1);
                    b_pvec.set_size(3, (pvec.size(1) + 1));
                    loop_ub = pvec.size(1);
                    for (int i = 0; i < loop_ub; i++) {
                        b_pvec[3 * i] = pvec[3 * i];
                        b_pvec[3 * i + 1] = pvec[3 * i + 1];
                        b_pvec[3 * i + 2] = pvec[3 * i + 2];
                    }

                    b_pvec[3 * pvec.size(1)] = P1[0];
                    b_pvec[3 * pvec.size(1) + 1] = P1[1];
                    b_pvec[3 * pvec.size(1) + 2] = P1[2];
                    pvec.set_size(3, b_pvec.size(1));
                    b_loop_ub = b_pvec.size(1);
                    for (int i1 = 0; i1 < b_loop_ub; i1++) {
                        pvec[3 * i1] = b_pvec[3 * i1];
                        pvec[3 * i1 + 1] = b_pvec[3 * i1 + 1];
                        pvec[3 * i1 + 2] = b_pvec[3 * i1 + 2];
                    }
                }
            }
        }
    }

    //
    // Arguments    : const coder::array<double, 2U> &pvec
    //                double FeedRate
    //                CurvStruct *b_CurvStruct
    // Return Type  : void
    //
    static void ConstrBSplineStruct(const coder::array<double, 2U> &pvec, double FeedRate,
        CurvStruct *b_CurvStruct)
    {
        //
        //
        //  ctxType = coder.OutputType('InitFeedoptPlan');
        b_CurvStruct->Type = CurveType_Spline;
        b_CurvStruct->zspdmode = ZSpdMode_NN;
        b_CurvStruct->P0[0] = pvec[0];
        b_CurvStruct->P1[0] = pvec[3 * (pvec.size(1) - 1)];
        b_CurvStruct->evec[0] = 0.0;
        b_CurvStruct->P0[1] = pvec[1];
        b_CurvStruct->P1[1] = pvec[3 * (pvec.size(1) - 1) + 1];
        b_CurvStruct->evec[1] = 0.0;
        b_CurvStruct->P0[2] = pvec[2];
        b_CurvStruct->P1[2] = pvec[3 * (pvec.size(1) - 1) + 2];
        b_CurvStruct->evec[2] = 0.0;
        b_CurvStruct->theta = 0.0;
        b_CurvStruct->pitch = 0.0;
        for (int i = 0; i < 6; i++) {
            b_CurvStruct->CoeffP5[i][0] = 0.0;
            b_CurvStruct->CoeffP5[i][1] = 0.0;
            b_CurvStruct->CoeffP5[i][2] = 0.0;
        }

        b_CurvStruct->sp_index = 1;
        b_CurvStruct->FeedRate = FeedRate;
        b_CurvStruct->MaxConstantFeedRate = 0.0;
        b_CurvStruct->i_begin_sp = 0;
        b_CurvStruct->i_end_sp = 0;
        b_CurvStruct->gcode_source_line = 0;
        b_CurvStruct->index_smooth = 0;
        b_CurvStruct->UseConstJerk = false;
        b_CurvStruct->ConstJerk = 0.0;
        b_CurvStruct->ConstJerkMaxIterations = 0;
        b_CurvStruct->Coeff.set_size(0);
        b_CurvStruct->a_param = 1.0;
        b_CurvStruct->b_param = 0.0;
        b_CurvStruct->sp.CoeffX.set_size(1, 1);
        b_CurvStruct->sp.CoeffX[0] = 0.0;
        b_CurvStruct->sp.CoeffY.set_size(1, 1);
        b_CurvStruct->sp.CoeffY[0] = 0.0;
        b_CurvStruct->sp.CoeffZ.set_size(1, 1);
        b_CurvStruct->sp.CoeffZ[0] = 0.0;
        b_CurvStruct->sp.Bl.ncoeff = 0;
        b_CurvStruct->sp.Bl.breakpoints.set_size(1, 0);
        b_CurvStruct->sp.Bl.handle = 0UL;
        b_CurvStruct->sp.Bl.degree = 0;
        b_CurvStruct->sp.knots.set_size(1, 1);
        b_CurvStruct->sp.knots[0] = 0.0;
    }

    //
    // Arguments    : const double CoeffP5[6][3]
    //                double FeedRate
    //                CurvStruct *b_CurvStruct
    // Return Type  : void
    //
    static void ConstrTransP5Struct(const double CoeffP5[6][3], double FeedRate, CurvStruct
        *b_CurvStruct)
    {
        double P1_idx_0;
        double P1_idx_1;
        double P1_idx_2;
        double P0_idx_0;
        double P0_idx_1;
        double P0_idx_2;

        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        P1_idx_0 = CoeffP5[0][0];
        P1_idx_1 = CoeffP5[0][1];
        P1_idx_2 = CoeffP5[0][2];
        for (int i = 0; i < 5; i++) {
            double d;
            double d1;
            double d2;
            d = CoeffP5[i + 1][0];
            P0_idx_0 = d;
            d1 = CoeffP5[i + 1][1];
            P0_idx_1 = d1;
            d2 = CoeffP5[i + 1][2];
            P0_idx_2 = d2;
            P1_idx_0 += d;
            P1_idx_1 += d1;
            P1_idx_2 += d2;
        }

        //
        //
        //  ctxType = coder.OutputType('InitFeedoptPlan');
        b_CurvStruct->Type = CurveType_TransP5;
        b_CurvStruct->zspdmode = ZSpdMode_NN;
        b_CurvStruct->P0[0] = P0_idx_0;
        b_CurvStruct->P1[0] = P1_idx_0;
        b_CurvStruct->evec[0] = 0.0;
        b_CurvStruct->P0[1] = P0_idx_1;
        b_CurvStruct->P1[1] = P1_idx_1;
        b_CurvStruct->evec[1] = 0.0;
        b_CurvStruct->P0[2] = P0_idx_2;
        b_CurvStruct->P1[2] = P1_idx_2;
        b_CurvStruct->evec[2] = 0.0;
        b_CurvStruct->theta = 0.0;
        b_CurvStruct->pitch = 0.0;
        for (int b_i = 0; b_i < 6; b_i++) {
            b_CurvStruct->CoeffP5[b_i][0] = CoeffP5[b_i][0];
            b_CurvStruct->CoeffP5[b_i][1] = CoeffP5[b_i][1];
            b_CurvStruct->CoeffP5[b_i][2] = CoeffP5[b_i][2];
        }

        b_CurvStruct->sp_index = 1;
        b_CurvStruct->FeedRate = FeedRate;
        b_CurvStruct->MaxConstantFeedRate = 0.0;
        b_CurvStruct->i_begin_sp = 0;
        b_CurvStruct->i_end_sp = 0;
        b_CurvStruct->gcode_source_line = 0;
        b_CurvStruct->index_smooth = 0;
        b_CurvStruct->UseConstJerk = false;
        b_CurvStruct->ConstJerk = 0.0;
        b_CurvStruct->ConstJerkMaxIterations = 0;
        b_CurvStruct->Coeff.set_size(0);
        b_CurvStruct->a_param = 1.0;
        b_CurvStruct->b_param = 0.0;
        b_CurvStruct->sp.CoeffX.set_size(1, 1);
        b_CurvStruct->sp.CoeffX[0] = 0.0;
        b_CurvStruct->sp.CoeffY.set_size(1, 1);
        b_CurvStruct->sp.CoeffY[0] = 0.0;
        b_CurvStruct->sp.CoeffZ.set_size(1, 1);
        b_CurvStruct->sp.CoeffZ[0] = 0.0;
        b_CurvStruct->sp.Bl.ncoeff = 0;
        b_CurvStruct->sp.Bl.breakpoints.set_size(1, 0);
        b_CurvStruct->sp.Bl.handle = 0UL;
        b_CurvStruct->sp.Bl.degree = 0;
        b_CurvStruct->sp.knots.set_size(1, 1);
        b_CurvStruct->sp.knots[0] = 0.0;
    }

    //
    // We cut d0 [mm] in the beginning and d1 [mm] in the end of the segment
    //  We determine a new value of the parameter u_tilda
    // Arguments    : const queue_coder *ctx_q_splines
    //                double ctx_cfg_NGridLengthSpline
    //                CurvStruct *b_CurvStruct
    //                double d1
    // Return Type  : void
    //
    static void CutCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        CurvStruct *b_CurvStruct, double d1)
    {
        CurvStruct b_ctx_q_splines;
        double unusedU0[3];
        double r1D0[3];
        double L_tot;
        coder::array<double, 2U> Integrand;
        coder::array<double, 2U> u_mid_tilda;
        coder::array<double, 2U> du_tilda;
        double unusedU1[3];
        double r1D1[3];
        double u0_tilda;
        double u1_tilda;
        double L;
        if (b_CurvStruct->Type == CurveType_Spline) {
            ctx_q_splines->get(b_CurvStruct->sp_index, (&b_ctx_q_splines));

            //  discretizing along the total spline
            //  from u=0 to u=1
            d_SplineLengthApprox(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->sp_index,
                                 b_CurvStruct->b_param, b_CurvStruct->a_param +
                                 b_CurvStruct->b_param, &L_tot, Integrand, u_mid_tilda, du_tilda);
            u0_tilda = b_CurvStruct->b_param;
            if (d1 != 0.0) {
                unsigned int k;

                //  spline-long length calculation by rectangles method
                //  beginning from u=0
                //  until L_tot-d1 is reached
                L = 0.0;
                k = 1U;
                while ((L < L_tot - d1) && (k <= static_cast<unsigned int>(du_tilda.size(1)))) {
                    int L_tmp;
                    L_tmp = static_cast<int>(k) - 1;
                    L += Integrand[L_tmp] * du_tilda[L_tmp];
                    k++;
                }

                u1_tilda = u_mid_tilda[static_cast<int>(k) - 1];
            } else {
                u1_tilda = b_CurvStruct->a_param + b_CurvStruct->b_param;
            }
        } else {
            //  In case of helix and line, ||r'(u)||=const,
            //  for 0 < u < 1
            //  r1D0 and r1D1 are with respect to u
            f_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                             b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                             b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                             b_CurvStruct->b_param, unusedU0, r1D0);
            e_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                             b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                             b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                             b_CurvStruct->b_param, unusedU1, r1D1);

            //  d0 = Integral_0_u0 ||r'(u)||du
            //  d1 = Integral_u1_1 ||r'(u)||du
            //  conversion to native curve parameter u_tilda
            u0_tilda = b_CurvStruct->a_param * (0.0 / std::sqrt((std::pow(r1D0[0], 2.0) + std::pow
                (r1D0[1], 2.0)) + std::pow(r1D0[2], 2.0))) + b_CurvStruct->b_param;
            u1_tilda = b_CurvStruct->a_param * (1.0 - d1 / std::sqrt((std::pow(r1D1[0], 2.0) + std::
                pow(r1D1[1], 2.0)) + std::pow(r1D1[2], 2.0))) + b_CurvStruct->b_param;
        }

        b_CurvStruct->a_param = u1_tilda - u0_tilda;
        b_CurvStruct->b_param = u0_tilda;
    }

    //
    // Arguments    : const queue_coder *ctx_q_gcode
    //                const queue_coder *ctx_q_splines
    //                int ctx_cfg_NHorz
    //                const double ctx_cfg_amax[3]
    //                const double ctx_cfg_jmax[3]
    //                double ctx_cfg_dt
    //                double ctx_cfg_ZeroStartAccLimit
    //                double ctx_cfg_ZeroStartJerkLimit
    //                double ctx_cfg_ZeroStartVelLimit
    //                double ctx_cfg_NGridLengthSpline
    //                const CurvStruct *b_CurvStruct
    //                double k0
    //                CurvStruct *CurvStruct1
    //                CurvStruct *CurvStruct2
    // Return Type  : void
    //
    static void CutZeroEnd(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int
                           ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3],
                           double ctx_cfg_dt, double ctx_cfg_ZeroStartAccLimit, double
                           ctx_cfg_ZeroStartJerkLimit, double ctx_cfg_ZeroStartVelLimit, double
                           ctx_cfg_NGridLengthSpline, const CurvStruct *b_CurvStruct, double k0,
                           CurvStruct *CurvStruct1, CurvStruct *CurvStruct2)
    {
        double unusedU0[3];
        double r1D[3];
        double ex;
        double z1_idx_1;
        double z1_idx_2;
        double ex_tmp;
        double b_ex;
        double tmax;
        double jps;
        coder::array<double, 2U> t;
        coder::array<double, 2U> z1;
        int N;
        coder::array<double, 2U> uk;
        int b_loop_ub;
        int scalarLB;
        int vectorUB;
        int i1;
        int b_N;
        coder::array<double, 2U> d1uk;
        int c_loop_ub;
        int b_scalarLB;
        int b_vectorUB;
        int i2;
        coder::array<double, 2U> d2uk;
        int d_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int i3;
        coder::array<double, 2U> b_uk;
        int e_loop_ub;
        coder::array<double, 2U> unusedU1;
        coder::array<double, 2U> b_r1D;
        coder::array<double, 2U> r2D;
        coder::array<double, 2U> r3D;
        double b_vmax;
        int b_exp;
        unsigned long z;
        bool p;
        double DBLMAXFLINT;
        bool blarge;
        bool alarge;
        unsigned long c_N;
        unsigned long c_k;
        bool exitg1;
        CurvStruct expl_temp;
        int d_N;
        double TmpCurv_P0[3];
        double TmpCurv_P1[3];
        double TmpCurv_evec[3];
        coder::array<double, 2U> c;
        coder::array<double, 2U> r3;
        coder::array<double, 2U> b_d1uk;
        int f_loop_ub;
        int d_scalarLB;
        int d_vectorUB;
        int i7;
        double TmpCurv_CoeffP5[6][3];
        coder::array<double, 2U> r6;
        coder::array<double, 2U> a;
        int g_loop_ub;
        coder::array<double, 2U> x;
        coder::array<double, 2U> jt;
        coder::array<double, 2U> b_z1;
        int e_N;
        int j_loop_ub;
        coder::array<double, 2U> at;
        int m;
        coder::array<double, 1U> max_jt;
        int b_m;
        coder::array<double, 1U> max_at;
        coder::array<bool, 2U> b_max_jt;
        int m_loop_ub;
        int tmp_data[1];
        int tmp_size[2];
        int cut_index_jerk_size_idx_1;
        int n_loop_ub;
        int cut_index_jerk_data[1];
        coder::array<bool, 2U> b_max_at;
        int o_loop_ub;
        int cut_index_acc_size_idx_1;
        int p_loop_ub;
        int cut_index_acc_data[1];
        coder::array<double, 2U> b_a;
        coder::array<double, 2U> c_z1;
        int f_N;
        coder::array<double, 2U> b_x;
        int i26;
        int e_scalarLB;
        int e_vectorUB;
        int p_k;
        coder::array<bool, 2U> c_x;
        int q_loop_ub;
        int cut_index_vel_size_idx_1;
        int r_loop_ub;
        int cut_index_vel_data[1];
        int varargin_1_data[3];
        int c_ex;
        int cut_index;
        double L;
        f_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                         b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                         b_CurvStruct->b_param, unusedU0, r1D);
        ex = ctx_cfg_jmax[0];
        if (ctx_cfg_jmax[0] > ctx_cfg_jmax[1]) {
            ex = ctx_cfg_jmax[1];
        }

        if (ex > ctx_cfg_jmax[2]) {
            ex = ctx_cfg_jmax[2];
        }

        z1_idx_1 = std::abs(r1D[1]);
        z1_idx_2 = std::abs(r1D[2]);
        ex_tmp = std::abs(r1D[0]);
        b_ex = ex_tmp;
        if (ex_tmp < z1_idx_1) {
            b_ex = z1_idx_1;
        }

        if (b_ex < z1_idx_2) {
            b_ex = z1_idx_2;
        }

        tmax = std::ceil(std::pow(6.0 / (ex / b_ex), 0.33333333333333331) / ctx_cfg_dt) * ctx_cfg_dt;
        jps = 6.0 / std::pow(tmax, 3.0);
        if ((-ctx_cfg_dt == 0.0) || ((tmax < 0.0) && (-ctx_cfg_dt < 0.0)) || ((0.0 < tmax) &&
                (-ctx_cfg_dt > 0.0))) {
            t.set_size(1, 0);
        } else if ((std::floor(tmax) == tmax) && (std::floor(-ctx_cfg_dt) == -ctx_cfg_dt)) {
            int loop_ub;
            loop_ub = static_cast<int>(std::floor((0.0 - tmax) / -ctx_cfg_dt));
            t.set_size(1, (loop_ub + 1));
            for (int i = 0; i <= loop_ub; i++) {
                t[i] = tmax + -ctx_cfg_dt * static_cast<double>(i);
            }
        } else {
            b_eml_float_colon(tmax, -ctx_cfg_dt, t);
        }

        z1.set_size(1, t.size(1));
        N = t.size(1);
        for (int k = 0; k < N; k++) {
            z1[k] = std::pow(t[k], 3.0);
        }

        uk.set_size(1, z1.size(1));
        b_loop_ub = z1.size(1);
        scalarLB = z1.size(1) & -4;
        vectorUB = scalarLB - 4;
        for (i1 = 0; i1 <= vectorUB; i1 += 4) {
            __m256d r;
            r = _mm256_loadu_pd(&z1[i1]);
            _mm256_storeu_pd(&uk[i1], _mm256_div_pd(_mm256_mul_pd(_mm256_set1_pd(jps), r),
                              _mm256_set1_pd(6.0)));
        }

        for (i1 = scalarLB; i1 < b_loop_ub; i1++) {
            uk[i1] = jps * z1[i1] / 6.0;
        }

        z1.set_size(1, t.size(1));
        b_N = t.size(1);
        for (int b_k = 0; b_k < b_N; b_k++) {
            z1[b_k] = std::pow(t[b_k], 2.0);
        }

        d1uk.set_size(1, z1.size(1));
        c_loop_ub = z1.size(1);
        b_scalarLB = z1.size(1) & -4;
        b_vectorUB = b_scalarLB - 4;
        for (i2 = 0; i2 <= b_vectorUB; i2 += 4) {
            __m256d r1;
            r1 = _mm256_loadu_pd(&z1[i2]);
            _mm256_storeu_pd(&d1uk[i2], _mm256_div_pd(_mm256_mul_pd(_mm256_set1_pd(jps), r1),
                              _mm256_set1_pd(2.0)));
        }

        for (i2 = b_scalarLB; i2 < c_loop_ub; i2++) {
            d1uk[i2] = jps * z1[i2] / 2.0;
        }

        d2uk.set_size(1, t.size(1));
        d_loop_ub = t.size(1);
        c_scalarLB = t.size(1) & -4;
        c_vectorUB = c_scalarLB - 4;
        for (i3 = 0; i3 <= c_vectorUB; i3 += 4) {
            __m256d r2;
            r2 = _mm256_loadu_pd(&t[i3]);
            _mm256_storeu_pd(&d2uk[i3], _mm256_mul_pd(_mm256_set1_pd(jps), r2));
        }

        for (i3 = c_scalarLB; i3 < d_loop_ub; i3++) {
            d2uk[i3] = jps * t[i3];
        }

        b_uk.set_size(1, uk.size(1));
        e_loop_ub = uk.size(1) - 1;
        for (int i4 = 0; i4 <= e_loop_ub; i4++) {
            b_uk[i4] = uk[i4];
        }

        h_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                         b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                         b_CurvStruct->b_param, b_uk, unusedU1, b_r1D, r2D, r3D);
        b_vmax = b_CurvStruct->FeedRate;
        if ((0.0 <= k0) && (k0 < 1.8446744073709552E+19)) {
            z = static_cast<unsigned long>(k0) - ctx_cfg_NHorz;
        } else {
            double xd;
            unsigned long dif;
            xd = frexp(k0, &b_exp);
            dif = static_cast<unsigned long>(std::ldexp(xd, 64)) - (static_cast<unsigned long>
                (ctx_cfg_NHorz) >> 1);
            if ((dif & 9223372036854775808UL) > 0UL) {
                z = MAX_uint64_T;
            } else {
                z = dif << 1;
                if ((ctx_cfg_NHorz & 1UL) == 1UL) {
                    z--;
                }
            }
        }

        p = false;
        DBLMAXFLINT = std::pow(2.0, 52.0);
        blarge = (1.0 >= DBLMAXFLINT);
        alarge = (z + 1UL >= static_cast<unsigned long>(std::round(DBLMAXFLINT)));
        if ((!alarge) && blarge) {
            p = true;
        } else if (alarge && blarge) {
            p = (z + 1UL < 1UL);
        } else {
            if (!alarge) {
                p = (z + 1UL < 1.0);
            }
        }

        if (p) {
            c_N = 1UL;
        } else {
            c_N = z + 1UL;
        }

        c_k = static_cast<unsigned long>(std::round(k0));
        exitg1 = false;
        while ((!exitg1) && (c_k >= c_N)) {
            ctx_q_gcode->get(c_k, (&expl_temp));
            TmpCurv_P0[0] = expl_temp.P0[0];
            TmpCurv_P1[0] = expl_temp.P1[0];
            TmpCurv_evec[0] = expl_temp.evec[0];
            TmpCurv_P0[1] = expl_temp.P0[1];
            TmpCurv_P1[1] = expl_temp.P1[1];
            TmpCurv_evec[1] = expl_temp.evec[1];
            TmpCurv_P0[2] = expl_temp.P0[2];
            TmpCurv_P1[2] = expl_temp.P1[2];
            TmpCurv_evec[2] = expl_temp.evec[2];
            for (int i6 = 0; i6 < 6; i6++) {
                TmpCurv_CoeffP5[i6][0] = expl_temp.CoeffP5[i6][0];
                TmpCurv_CoeffP5[i6][1] = expl_temp.CoeffP5[i6][1];
                TmpCurv_CoeffP5[i6][2] = expl_temp.CoeffP5[i6][2];
            }

            double y;
            y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                                   TmpCurv_P0, TmpCurv_P1, TmpCurv_evec, expl_temp.theta,
                                   expl_temp.pitch, TmpCurv_CoeffP5, expl_temp.sp_index,
                                   expl_temp.FeedRate, expl_temp.a_param, expl_temp.b_param);
            b_vmax = std::fmin(b_vmax, y);
            if (expl_temp.zspdmode == ZSpdMode_ZN) {
                exitg1 = true;
            } else {
                c_k--;
            }
        }

        z1.set_size(1, d1uk.size(1));
        d_N = d1uk.size(1);
        for (int d_k = 0; d_k < d_N; d_k++) {
            z1[d_k] = std::pow(d1uk[d_k], 3.0);
        }

        c.set_size(3, b_r1D.size(1));
        if (b_r1D.size(1) != 0) {
            int acoef;
            int i5;
            acoef = (b_r1D.size(1) != 1);
            i5 = b_r1D.size(1) - 1;
            for (int e_k = 0; e_k <= i5; e_k++) {
                int varargin_2;
                varargin_2 = acoef * e_k;
                c[3 * e_k] = b_r1D[3 * varargin_2] * jps;
                c[3 * e_k + 1] = b_r1D[3 * varargin_2 + 1] * jps;
                c[3 * e_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
            }
        }

        bsxfun(r3D, z1, r3);
        b_d1uk.set_size(1, d1uk.size(1));
        f_loop_ub = d1uk.size(1);
        d_scalarLB = d1uk.size(1) & -4;
        d_vectorUB = d_scalarLB - 4;
        for (i7 = 0; i7 <= d_vectorUB; i7 += 4) {
            __m256d r4;
            __m256d r5;
            r4 = _mm256_loadu_pd(&d1uk[i7]);
            r5 = _mm256_loadu_pd(&d2uk[i7]);
            _mm256_storeu_pd(&b_d1uk[i7], _mm256_mul_pd(r4, r5));
        }

        for (i7 = d_scalarLB; i7 < f_loop_ub; i7++) {
            b_d1uk[i7] = d1uk[i7] * d2uk[i7];
        }

        bsxfun(r2D, b_d1uk, r6);
        a.set_size(r3.size(1), 3);
        g_loop_ub = r3.size(1);
        for (int i8 = 0; i8 < 3; i8++) {
            for (int i9 = 0; i9 < g_loop_ub; i9++) {
                a[i9 + a.size(0) * i8] = (r3[i8 + 3 * i9] + 3.0 * r6[i8 + 3 * i9]) + c[i8 + 3 * i9];
            }
        }

        x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int b_acoef;
            b_acoef = (a.size(0) != 1);
            for (int f_k = 0; f_k < 3; f_k++) {
                int i10;
                i10 = x.size(0) - 1;
                for (int g_k = 0; g_k <= i10; g_k++) {
                    x[g_k + x.size(0) * f_k] = a[b_acoef * g_k + a.size(0) * f_k] / ctx_cfg_jmax[f_k];
                }
            }
        }

        jt.set_size(x.size(0), 3);
        if (x.size(0) != 0) {
            int h_loop_ub;
            int i_loop_ub;
            b_z1.set_size(x.size(0), 3);
            h_loop_ub = x.size(0);
            for (int i11 = 0; i11 < 3; i11++) {
                for (int i12 = 0; i12 < h_loop_ub; i12++) {
                    b_z1[i12 + b_z1.size(0) * i11] = jt[i12 + jt.size(0) * i11];
                }
            }

            for (int i_k = 0; i_k < 3; i_k++) {
                int i13;
                i13 = b_z1.size(0);
                for (int j_k = 0; j_k < i13; j_k++) {
                    b_z1[j_k + b_z1.size(0) * i_k] = std::abs(x[j_k + x.size(0) * i_k]);
                }
            }

            jt.set_size(b_z1.size(0), 3);
            i_loop_ub = b_z1.size(0);
            for (int i14 = 0; i14 < 3; i14++) {
                for (int i16 = 0; i16 < i_loop_ub; i16++) {
                    jt[i16 + jt.size(0) * i14] = b_z1[i16 + b_z1.size(0) * i14];
                }
            }
        }

        z1.set_size(1, d1uk.size(1));
        e_N = d1uk.size(1);
        for (int h_k = 0; h_k < e_N; h_k++) {
            z1[h_k] = std::pow(d1uk[h_k], 2.0);
        }

        bsxfun(r2D, z1, r3);
        bsxfun(b_r1D, d2uk, r6);
        a.set_size(r3.size(1), 3);
        j_loop_ub = r3.size(1);
        for (int i15 = 0; i15 < 3; i15++) {
            for (int i17 = 0; i17 < j_loop_ub; i17++) {
                a[i17 + a.size(0) * i15] = r3[i15 + 3 * i17] + r6[i15 + 3 * i17];
            }
        }

        x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int c_acoef;
            c_acoef = (a.size(0) != 1);
            for (int k_k = 0; k_k < 3; k_k++) {
                int i18;
                i18 = x.size(0) - 1;
                for (int l_k = 0; l_k <= i18; l_k++) {
                    x[l_k + x.size(0) * k_k] = a[c_acoef * l_k + a.size(0) * k_k] / ctx_cfg_amax[k_k];
                }
            }
        }

        at.set_size(x.size(0), 3);
        if (x.size(0) != 0) {
            int k_loop_ub;
            int l_loop_ub;
            b_z1.set_size(x.size(0), 3);
            k_loop_ub = x.size(0);
            for (int i19 = 0; i19 < 3; i19++) {
                for (int i20 = 0; i20 < k_loop_ub; i20++) {
                    b_z1[i20 + b_z1.size(0) * i19] = at[i20 + at.size(0) * i19];
                }
            }

            for (int m_k = 0; m_k < 3; m_k++) {
                int i21;
                i21 = b_z1.size(0);
                for (int n_k = 0; n_k < i21; n_k++) {
                    b_z1[n_k + b_z1.size(0) * m_k] = std::abs(x[n_k + x.size(0) * m_k]);
                }
            }

            at.set_size(b_z1.size(0), 3);
            l_loop_ub = b_z1.size(0);
            for (int i22 = 0; i22 < 3; i22++) {
                for (int i23 = 0; i23 < l_loop_ub; i23++) {
                    at[i23 + at.size(0) * i22] = b_z1[i23 + b_z1.size(0) * i22];
                }
            }
        }

        m = jt.size(0) - 1;
        max_jt.set_size(jt.size(0));
        if (jt.size(0) >= 1) {
            int c_i;
            double d;
            for (int b_i = 0; b_i <= m; b_i++) {
                max_jt[b_i] = jt[b_i];
            }

            for (c_i = 0; c_i <= m; c_i++) {
                d = jt[c_i + jt.size(0)];
                if (max_jt[c_i] < d) {
                    max_jt[c_i] = d;
                }
            }

            for (c_i = 0; c_i <= m; c_i++) {
                d = jt[c_i + jt.size(0) * 2];
                if (max_jt[c_i] < d) {
                    max_jt[c_i] = d;
                }
            }
        }

        b_m = at.size(0) - 1;
        max_at.set_size(at.size(0));
        if (at.size(0) >= 1) {
            int e_i;
            double d1;
            for (int d_i = 0; d_i <= b_m; d_i++) {
                max_at[d_i] = at[d_i];
            }

            for (e_i = 0; e_i <= b_m; e_i++) {
                d1 = at[e_i + at.size(0)];
                if (max_at[e_i] < d1) {
                    max_at[e_i] = d1;
                }
            }

            for (e_i = 0; e_i <= b_m; e_i++) {
                d1 = at[e_i + at.size(0) * 2];
                if (max_at[e_i] < d1) {
                    max_at[e_i] = d1;
                }
            }
        }

        b_max_jt.set_size(1, max_jt.size(0));
        m_loop_ub = max_jt.size(0);
        for (int i24 = 0; i24 < m_loop_ub; i24++) {
            b_max_jt[i24] = (max_jt[i24] > ctx_cfg_ZeroStartJerkLimit);
        }

        b_eml_find(b_max_jt, tmp_data, tmp_size);
        cut_index_jerk_size_idx_1 = tmp_size[1];
        n_loop_ub = tmp_size[1];
        if (0 <= n_loop_ub - 1) {
            std::memcpy(&cut_index_jerk_data[0], &tmp_data[0], n_loop_ub * sizeof(int));
        }

        if (tmp_size[1] == 0) {
            cut_index_jerk_size_idx_1 = 1;
            cut_index_jerk_data[0] = 1;
        }

        b_max_at.set_size(1, max_at.size(0));
        o_loop_ub = max_at.size(0);
        for (int i25 = 0; i25 < o_loop_ub; i25++) {
            b_max_at[i25] = (max_at[i25] > ctx_cfg_ZeroStartAccLimit);
        }

        b_eml_find(b_max_at, tmp_data, tmp_size);
        cut_index_acc_size_idx_1 = tmp_size[1];
        p_loop_ub = tmp_size[1];
        if (0 <= p_loop_ub - 1) {
            std::memcpy(&cut_index_acc_data[0], &tmp_data[0], p_loop_ub * sizeof(int));
        }

        if (tmp_size[1] == 0) {
            cut_index_acc_size_idx_1 = 1;
            cut_index_acc_data[0] = 1;
        }

        bsxfun(b_r1D, d1uk, b_a);
        c_z1.set_size(3, b_a.size(1));
        f_N = b_a.size(1);
        for (int o_k = 0; o_k < f_N; o_k++) {
            c_z1[3 * o_k] = std::pow(b_a[3 * o_k], 2.0);
            c_z1[3 * o_k + 1] = std::pow(b_a[3 * o_k + 1], 2.0);
            c_z1[3 * o_k + 2] = std::pow(b_a[3 * o_k + 2], 2.0);
        }

        sum(c_z1, b_x);
        i26 = b_x.size(1);
        e_scalarLB = b_x.size(1) & -4;
        e_vectorUB = e_scalarLB - 4;
        for (p_k = 0; p_k <= e_vectorUB; p_k += 4) {
            __m256d r7;
            r7 = _mm256_loadu_pd(&b_x[p_k]);
            _mm256_storeu_pd(&b_x[p_k], _mm256_sqrt_pd(r7));
        }

        for (p_k = e_scalarLB; p_k < i26; p_k++) {
            b_x[p_k] = std::sqrt(b_x[p_k]);
        }

        c_x.set_size(1, b_x.size(1));
        q_loop_ub = b_x.size(1);
        for (int i27 = 0; i27 < q_loop_ub; i27++) {
            c_x[i27] = (b_x[i27] / b_vmax > ctx_cfg_ZeroStartVelLimit);
        }

        b_eml_find(c_x, tmp_data, tmp_size);
        cut_index_vel_size_idx_1 = tmp_size[1];
        r_loop_ub = tmp_size[1];
        if (0 <= r_loop_ub - 1) {
            std::memcpy(&cut_index_vel_data[0], &tmp_data[0], r_loop_ub * sizeof(int));
        }

        if (tmp_size[1] == 0) {
            cut_index_vel_size_idx_1 = 1;
            cut_index_vel_data[0] = 1;
        }

        if (0 <= cut_index_acc_size_idx_1 - 1) {
            std::memcpy(&varargin_1_data[0], &cut_index_acc_data[0], cut_index_acc_size_idx_1 *
                        sizeof(int));
        }

        for (int i28 = 0; i28 < cut_index_jerk_size_idx_1; i28++) {
            varargin_1_data[i28 + cut_index_acc_size_idx_1] = cut_index_jerk_data[i28];
        }

        for (int i29 = 0; i29 < cut_index_vel_size_idx_1; i29++) {
            varargin_1_data[(i29 + cut_index_acc_size_idx_1) + cut_index_jerk_size_idx_1] =
                cut_index_vel_data[i29];
        }

        c_ex = varargin_1_data[0];
        if (varargin_1_data[0] < varargin_1_data[1]) {
            c_ex = varargin_1_data[1];
        }

        if (c_ex < varargin_1_data[2]) {
            c_ex = varargin_1_data[2];
        }

        cut_index = (max_at.size(0) - static_cast<int>(std::fmax(2.0, (static_cast<double>
                        (max_at.size(0)) - static_cast<double>(c_ex)) + 1.0))) - 1;

        //      actual_jps = jps;
        //      cut_index = N + 1 - cut_index;
        L = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->Type,
                       b_CurvStruct->P0, b_CurvStruct->P1, b_CurvStruct->evec, b_CurvStruct->theta,
                       b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                       b_CurvStruct->a_param, b_CurvStruct->b_param);
        *CurvStruct1 = *b_CurvStruct;
        CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1, uk[cut_index] * L);
        *CurvStruct2 = *b_CurvStruct;
        b_CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2, L - uk[cut_index] * L);
        CurvStruct2->ConstJerkMaxIterations = max_at.size(0) - cut_index;
        CurvStruct2->UseConstJerk = true;
        CurvStruct2->ConstJerk = 6.0 / std::pow(t[cut_index], 3.0);
        CurvStruct1->zspdmode = ZSpdMode_NN;
        CurvStruct2->zspdmode = ZSpdMode_NZ;
        CurvStruct1->gcode_source_line = b_CurvStruct->gcode_source_line;
        CurvStruct2->gcode_source_line = b_CurvStruct->gcode_source_line;
    }

    //
    // Arguments    : const queue_coder *ctx_q_gcode
    //                const queue_coder *ctx_q_splines
    //                int ctx_cfg_NHorz
    //                const double ctx_cfg_amax[3]
    //                const double ctx_cfg_jmax[3]
    //                double ctx_cfg_dt
    //                double ctx_cfg_ZeroStartAccLimit
    //                double ctx_cfg_ZeroStartJerkLimit
    //                double ctx_cfg_ZeroStartVelLimit
    //                bool ctx_cfg_DebugCutZero
    //                double ctx_cfg_NGridLengthSpline
    //                const CurvStruct *b_CurvStruct
    //                double k0
    //                CurvStruct *CurvStruct1
    //                CurvStruct *CurvStruct2
    // Return Type  : void
    //
    static void CutZeroStart(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int
        ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3], double ctx_cfg_dt,
        double ctx_cfg_ZeroStartAccLimit, double ctx_cfg_ZeroStartJerkLimit, double
        ctx_cfg_ZeroStartVelLimit, bool ctx_cfg_DebugCutZero, double ctx_cfg_NGridLengthSpline,
        const CurvStruct *b_CurvStruct, double k0, CurvStruct *CurvStruct1, CurvStruct *CurvStruct2)
    {
        double unusedU0[3];
        double r1D[3];
        double ex;
        double z1_idx_1;
        double z1_idx_2;
        double ex_tmp;
        double b_ex;
        double tmax;
        double jps;
        coder::array<double, 2U> t;
        coder::array<double, 2U> z1;
        int N;
        coder::array<double, 2U> uk;
        int b_loop_ub;
        int scalarLB;
        int vectorUB;
        int i1;
        int b_N;
        coder::array<double, 2U> d1uk;
        int c_loop_ub;
        int b_scalarLB;
        int b_vectorUB;
        int i2;
        coder::array<double, 2U> d2uk;
        int d_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int i3;
        coder::array<double, 2U> b_uk;
        int e_loop_ub;
        coder::array<double, 2U> unusedU1;
        coder::array<double, 2U> b_r1D;
        coder::array<double, 2U> r2D;
        coder::array<double, 2U> r3D;
        double b_vmax;
        long x;
        long y;
        long c_N;
        long c_k;
        bool exitg1;
        CurvStruct expl_temp;
        int d_N;
        double TmpCurv_P0[3];
        double TmpCurv_P1[3];
        double TmpCurv_evec[3];
        coder::array<double, 2U> c;
        coder::array<double, 2U> r3;
        coder::array<double, 2U> b_d1uk;
        int f_loop_ub;
        int d_scalarLB;
        int d_vectorUB;
        int i7;
        double TmpCurv_CoeffP5[6][3];
        coder::array<double, 2U> r6;
        coder::array<double, 2U> a;
        int g_loop_ub;
        coder::array<double, 2U> b_x;
        coder::array<double, 2U> jt;
        coder::array<double, 2U> b_z1;
        int e_N;
        int j_loop_ub;
        coder::array<double, 2U> at;
        coder::array<double, 2U> b_a;
        coder::array<double, 2U> c_z1;
        int f_N;
        coder::array<double, 2U> c_x;
        int i22;
        int e_scalarLB;
        int e_vectorUB;
        int p_k;
        coder::array<double, 1U> norm_vt;
        int m_loop_ub;
        int f_scalarLB;
        int f_vectorUB;
        int i25;
        int m;
        coder::array<double, 1U> max_jt;
        int b_m;
        coder::array<double, 1U> max_at;
        coder::array<bool, 2U> b_max_jt;
        int n_loop_ub;
        int tmp_data[1];
        int tmp_size[2];
        int cut_index_jerk_size_idx_1;
        int o_loop_ub;
        int cut_index_jerk_data[1];
        coder::array<bool, 2U> b_max_at;
        int p_loop_ub;
        int cut_index_acc_size_idx_1;
        int q_loop_ub;
        int cut_index_acc_data[1];
        coder::array<bool, 2U> b_norm_vt;
        int r_loop_ub;
        int cut_index_vel_size_idx_1;
        int s_loop_ub;
        int cut_index_vel_data[1];
        int varargin_1_data[3];
        int c_ex;
        int u0;
        int u1;
        int cut_index;
        double L;
        f_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                         b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                         b_CurvStruct->b_param, unusedU0, r1D);
        ex = ctx_cfg_jmax[0];
        if (ctx_cfg_jmax[0] > ctx_cfg_jmax[1]) {
            ex = ctx_cfg_jmax[1];
        }

        if (ex > ctx_cfg_jmax[2]) {
            ex = ctx_cfg_jmax[2];
        }

        z1_idx_1 = std::abs(r1D[1]);
        z1_idx_2 = std::abs(r1D[2]);
        ex_tmp = std::abs(r1D[0]);
        b_ex = ex_tmp;
        if (ex_tmp < z1_idx_1) {
            b_ex = z1_idx_1;
        }

        if (b_ex < z1_idx_2) {
            b_ex = z1_idx_2;
        }

        tmax = std::ceil(std::pow(6.0 / (ex / b_ex), 0.33333333333333331) / ctx_cfg_dt) * ctx_cfg_dt;
        jps = 6.0 / std::pow(tmax, 3.0);
        if ((ctx_cfg_dt == 0.0) || ((0.0 < tmax) && (ctx_cfg_dt < 0.0)) || ((tmax < 0.0) &&
                (ctx_cfg_dt > 0.0))) {
            t.set_size(1, 0);
        } else if (std::floor(ctx_cfg_dt) == ctx_cfg_dt) {
            int loop_ub;
            loop_ub = static_cast<int>(std::floor(tmax / ctx_cfg_dt));
            t.set_size(1, (loop_ub + 1));
            for (int i = 0; i <= loop_ub; i++) {
                t[i] = ctx_cfg_dt * static_cast<double>(i);
            }
        } else {
            eml_float_colon(ctx_cfg_dt, tmax, t);
        }

        z1.set_size(1, t.size(1));
        N = t.size(1);
        for (int k = 0; k < N; k++) {
            z1[k] = std::pow(t[k], 3.0);
        }

        uk.set_size(1, z1.size(1));
        b_loop_ub = z1.size(1);
        scalarLB = z1.size(1) & -4;
        vectorUB = scalarLB - 4;
        for (i1 = 0; i1 <= vectorUB; i1 += 4) {
            __m256d r;
            r = _mm256_loadu_pd(&z1[i1]);
            _mm256_storeu_pd(&uk[i1], _mm256_div_pd(_mm256_mul_pd(_mm256_set1_pd(jps), r),
                              _mm256_set1_pd(6.0)));
        }

        for (i1 = scalarLB; i1 < b_loop_ub; i1++) {
            uk[i1] = jps * z1[i1] / 6.0;
        }

        z1.set_size(1, t.size(1));
        b_N = t.size(1);
        for (int b_k = 0; b_k < b_N; b_k++) {
            z1[b_k] = std::pow(t[b_k], 2.0);
        }

        d1uk.set_size(1, z1.size(1));
        c_loop_ub = z1.size(1);
        b_scalarLB = z1.size(1) & -4;
        b_vectorUB = b_scalarLB - 4;
        for (i2 = 0; i2 <= b_vectorUB; i2 += 4) {
            __m256d r1;
            r1 = _mm256_loadu_pd(&z1[i2]);
            _mm256_storeu_pd(&d1uk[i2], _mm256_div_pd(_mm256_mul_pd(_mm256_set1_pd(jps), r1),
                              _mm256_set1_pd(2.0)));
        }

        for (i2 = b_scalarLB; i2 < c_loop_ub; i2++) {
            d1uk[i2] = jps * z1[i2] / 2.0;
        }

        d2uk.set_size(1, t.size(1));
        d_loop_ub = t.size(1);
        c_scalarLB = t.size(1) & -4;
        c_vectorUB = c_scalarLB - 4;
        for (i3 = 0; i3 <= c_vectorUB; i3 += 4) {
            __m256d r2;
            r2 = _mm256_loadu_pd(&t[i3]);
            _mm256_storeu_pd(&d2uk[i3], _mm256_mul_pd(_mm256_set1_pd(jps), r2));
        }

        for (i3 = c_scalarLB; i3 < d_loop_ub; i3++) {
            d2uk[i3] = jps * t[i3];
        }

        b_uk.set_size(1, uk.size(1));
        e_loop_ub = uk.size(1) - 1;
        for (int i4 = 0; i4 <= e_loop_ub; i4++) {
            b_uk[i4] = uk[i4];
        }

        h_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                         b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                         b_CurvStruct->b_param, b_uk, unusedU1, b_r1D, r2D, r3D);
        b_vmax = b_CurvStruct->FeedRate;
        x = static_cast<int>(std::round(k0 + static_cast<double>(ctx_cfg_NHorz))) - 1;
        y = ctx_q_gcode->size();
        if (x > y) {
            c_N = y;
        } else {
            c_N = x;
        }

        c_k = static_cast<long>(std::round(k0));
        exitg1 = false;
        while ((!exitg1) && (c_k <= c_N)) {
            ctx_q_gcode->get(c_k, (&expl_temp));
            TmpCurv_P0[0] = expl_temp.P0[0];
            TmpCurv_P1[0] = expl_temp.P1[0];
            TmpCurv_evec[0] = expl_temp.evec[0];
            TmpCurv_P0[1] = expl_temp.P0[1];
            TmpCurv_P1[1] = expl_temp.P1[1];
            TmpCurv_evec[1] = expl_temp.evec[1];
            TmpCurv_P0[2] = expl_temp.P0[2];
            TmpCurv_P1[2] = expl_temp.P1[2];
            TmpCurv_evec[2] = expl_temp.evec[2];
            for (int i6 = 0; i6 < 6; i6++) {
                TmpCurv_CoeffP5[i6][0] = expl_temp.CoeffP5[i6][0];
                TmpCurv_CoeffP5[i6][1] = expl_temp.CoeffP5[i6][1];
                TmpCurv_CoeffP5[i6][2] = expl_temp.CoeffP5[i6][2];
            }

            double b_y;
            b_y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                TmpCurv_P0, TmpCurv_P1, TmpCurv_evec, expl_temp.theta, expl_temp.pitch,
                TmpCurv_CoeffP5, expl_temp.sp_index, expl_temp.FeedRate, expl_temp.a_param,
                expl_temp.b_param);
            b_vmax = std::fmin(b_vmax, b_y);
            if (expl_temp.zspdmode == ZSpdMode_NZ) {
                exitg1 = true;
            } else {
                c_k++;
            }
        }

        z1.set_size(1, d1uk.size(1));
        d_N = d1uk.size(1);
        for (int d_k = 0; d_k < d_N; d_k++) {
            z1[d_k] = std::pow(d1uk[d_k], 3.0);
        }

        c.set_size(3, b_r1D.size(1));
        if (b_r1D.size(1) != 0) {
            int acoef;
            int i5;
            acoef = (b_r1D.size(1) != 1);
            i5 = b_r1D.size(1) - 1;
            for (int e_k = 0; e_k <= i5; e_k++) {
                int varargin_2;
                varargin_2 = acoef * e_k;
                c[3 * e_k] = b_r1D[3 * varargin_2] * jps;
                c[3 * e_k + 1] = b_r1D[3 * varargin_2 + 1] * jps;
                c[3 * e_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
            }
        }

        bsxfun(r3D, z1, r3);
        b_d1uk.set_size(1, d1uk.size(1));
        f_loop_ub = d1uk.size(1);
        d_scalarLB = d1uk.size(1) & -4;
        d_vectorUB = d_scalarLB - 4;
        for (i7 = 0; i7 <= d_vectorUB; i7 += 4) {
            __m256d r4;
            __m256d r5;
            r4 = _mm256_loadu_pd(&d1uk[i7]);
            r5 = _mm256_loadu_pd(&d2uk[i7]);
            _mm256_storeu_pd(&b_d1uk[i7], _mm256_mul_pd(r4, r5));
        }

        for (i7 = d_scalarLB; i7 < f_loop_ub; i7++) {
            b_d1uk[i7] = d1uk[i7] * d2uk[i7];
        }

        bsxfun(r2D, b_d1uk, r6);
        a.set_size(r3.size(1), 3);
        g_loop_ub = r3.size(1);
        for (int i8 = 0; i8 < 3; i8++) {
            for (int i9 = 0; i9 < g_loop_ub; i9++) {
                a[i9 + a.size(0) * i8] = (r3[i8 + 3 * i9] + 3.0 * r6[i8 + 3 * i9]) + c[i8 + 3 * i9];
            }
        }

        b_x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int b_acoef;
            b_acoef = (a.size(0) != 1);
            for (int f_k = 0; f_k < 3; f_k++) {
                int i10;
                i10 = b_x.size(0) - 1;
                for (int g_k = 0; g_k <= i10; g_k++) {
                    b_x[g_k + b_x.size(0) * f_k] = a[b_acoef * g_k + a.size(0) * f_k] /
                        ctx_cfg_jmax[f_k];
                }
            }
        }

        jt.set_size(b_x.size(0), 3);
        if (b_x.size(0) != 0) {
            int h_loop_ub;
            int i_loop_ub;
            b_z1.set_size(b_x.size(0), 3);
            h_loop_ub = b_x.size(0);
            for (int i11 = 0; i11 < 3; i11++) {
                for (int i12 = 0; i12 < h_loop_ub; i12++) {
                    b_z1[i12 + b_z1.size(0) * i11] = jt[i12 + jt.size(0) * i11];
                }
            }

            for (int i_k = 0; i_k < 3; i_k++) {
                int i13;
                i13 = b_z1.size(0);
                for (int j_k = 0; j_k < i13; j_k++) {
                    b_z1[j_k + b_z1.size(0) * i_k] = std::abs(b_x[j_k + b_x.size(0) * i_k]);
                }
            }

            jt.set_size(b_z1.size(0), 3);
            i_loop_ub = b_z1.size(0);
            for (int i14 = 0; i14 < 3; i14++) {
                for (int i16 = 0; i16 < i_loop_ub; i16++) {
                    jt[i16 + jt.size(0) * i14] = b_z1[i16 + b_z1.size(0) * i14];
                }
            }
        }

        z1.set_size(1, d1uk.size(1));
        e_N = d1uk.size(1);
        for (int h_k = 0; h_k < e_N; h_k++) {
            z1[h_k] = std::pow(d1uk[h_k], 2.0);
        }

        bsxfun(r2D, z1, r3);
        bsxfun(b_r1D, d2uk, r6);
        a.set_size(r3.size(1), 3);
        j_loop_ub = r3.size(1);
        for (int i15 = 0; i15 < 3; i15++) {
            for (int i17 = 0; i17 < j_loop_ub; i17++) {
                a[i17 + a.size(0) * i15] = r3[i15 + 3 * i17] + r6[i15 + 3 * i17];
            }
        }

        b_x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int c_acoef;
            c_acoef = (a.size(0) != 1);
            for (int k_k = 0; k_k < 3; k_k++) {
                int i18;
                i18 = b_x.size(0) - 1;
                for (int l_k = 0; l_k <= i18; l_k++) {
                    b_x[l_k + b_x.size(0) * k_k] = a[c_acoef * l_k + a.size(0) * k_k] /
                        ctx_cfg_amax[k_k];
                }
            }
        }

        at.set_size(b_x.size(0), 3);
        if (b_x.size(0) != 0) {
            int k_loop_ub;
            int l_loop_ub;
            b_z1.set_size(b_x.size(0), 3);
            k_loop_ub = b_x.size(0);
            for (int i19 = 0; i19 < 3; i19++) {
                for (int i20 = 0; i20 < k_loop_ub; i20++) {
                    b_z1[i20 + b_z1.size(0) * i19] = at[i20 + at.size(0) * i19];
                }
            }

            for (int n_k = 0; n_k < 3; n_k++) {
                int i21;
                i21 = b_z1.size(0);
                for (int o_k = 0; o_k < i21; o_k++) {
                    b_z1[o_k + b_z1.size(0) * n_k] = std::abs(b_x[o_k + b_x.size(0) * n_k]);
                }
            }

            at.set_size(b_z1.size(0), 3);
            l_loop_ub = b_z1.size(0);
            for (int i23 = 0; i23 < 3; i23++) {
                for (int i24 = 0; i24 < l_loop_ub; i24++) {
                    at[i24 + at.size(0) * i23] = b_z1[i24 + b_z1.size(0) * i23];
                }
            }
        }

        bsxfun(b_r1D, d1uk, b_a);
        c_z1.set_size(3, b_a.size(1));
        f_N = b_a.size(1);
        for (int m_k = 0; m_k < f_N; m_k++) {
            c_z1[3 * m_k] = std::pow(b_a[3 * m_k], 2.0);
            c_z1[3 * m_k + 1] = std::pow(b_a[3 * m_k + 1], 2.0);
            c_z1[3 * m_k + 2] = std::pow(b_a[3 * m_k + 2], 2.0);
        }

        sum(c_z1, c_x);
        i22 = c_x.size(1);
        e_scalarLB = c_x.size(1) & -4;
        e_vectorUB = e_scalarLB - 4;
        for (p_k = 0; p_k <= e_vectorUB; p_k += 4) {
            __m256d r7;
            r7 = _mm256_loadu_pd(&c_x[p_k]);
            _mm256_storeu_pd(&c_x[p_k], _mm256_sqrt_pd(r7));
        }

        for (p_k = e_scalarLB; p_k < i22; p_k++) {
            c_x[p_k] = std::sqrt(c_x[p_k]);
        }

        norm_vt.set_size(c_x.size(1));
        m_loop_ub = c_x.size(1);
        f_scalarLB = c_x.size(1) & -4;
        f_vectorUB = f_scalarLB - 4;
        for (i25 = 0; i25 <= f_vectorUB; i25 += 4) {
            __m256d r8;
            r8 = _mm256_loadu_pd(&c_x[i25]);
            _mm256_storeu_pd(&norm_vt[i25], _mm256_div_pd(r8, _mm256_set1_pd(b_vmax)));
        }

        for (i25 = f_scalarLB; i25 < m_loop_ub; i25++) {
            norm_vt[i25] = c_x[i25] / b_vmax;
        }

        m = jt.size(0) - 1;
        max_jt.set_size(jt.size(0));
        if (jt.size(0) >= 1) {
            int c_i;
            double d;
            for (int b_i = 0; b_i <= m; b_i++) {
                max_jt[b_i] = jt[b_i];
            }

            for (c_i = 0; c_i <= m; c_i++) {
                d = jt[c_i + jt.size(0)];
                if (max_jt[c_i] < d) {
                    max_jt[c_i] = d;
                }
            }

            for (c_i = 0; c_i <= m; c_i++) {
                d = jt[c_i + jt.size(0) * 2];
                if (max_jt[c_i] < d) {
                    max_jt[c_i] = d;
                }
            }
        }

        b_m = at.size(0) - 1;
        max_at.set_size(at.size(0));
        if (at.size(0) >= 1) {
            int e_i;
            double d1;
            for (int d_i = 0; d_i <= b_m; d_i++) {
                max_at[d_i] = at[d_i];
            }

            for (e_i = 0; e_i <= b_m; e_i++) {
                d1 = at[e_i + at.size(0)];
                if (max_at[e_i] < d1) {
                    max_at[e_i] = d1;
                }
            }

            for (e_i = 0; e_i <= b_m; e_i++) {
                d1 = at[e_i + at.size(0) * 2];
                if (max_at[e_i] < d1) {
                    max_at[e_i] = d1;
                }
            }
        }

        b_max_jt.set_size(1, max_jt.size(0));
        n_loop_ub = max_jt.size(0);
        for (int i26 = 0; i26 < n_loop_ub; i26++) {
            b_max_jt[i26] = (max_jt[i26] > ctx_cfg_ZeroStartJerkLimit);
        }

        eml_find(b_max_jt, tmp_data, tmp_size);
        cut_index_jerk_size_idx_1 = tmp_size[1];
        o_loop_ub = tmp_size[1];
        if (0 <= o_loop_ub - 1) {
            std::memcpy(&cut_index_jerk_data[0], &tmp_data[0], o_loop_ub * sizeof(int));
        }

        if (tmp_size[1] == 0) {
            cut_index_jerk_size_idx_1 = 1;
            cut_index_jerk_data[0] = max_jt.size(0);
        }

        b_max_at.set_size(1, max_at.size(0));
        p_loop_ub = max_at.size(0);
        for (int i27 = 0; i27 < p_loop_ub; i27++) {
            b_max_at[i27] = (max_at[i27] > ctx_cfg_ZeroStartAccLimit);
        }

        eml_find(b_max_at, tmp_data, tmp_size);
        cut_index_acc_size_idx_1 = tmp_size[1];
        q_loop_ub = tmp_size[1];
        if (0 <= q_loop_ub - 1) {
            std::memcpy(&cut_index_acc_data[0], &tmp_data[0], q_loop_ub * sizeof(int));
        }

        if (tmp_size[1] == 0) {
            cut_index_acc_size_idx_1 = 1;
            cut_index_acc_data[0] = max_jt.size(0);
        }

        b_norm_vt.set_size(1, norm_vt.size(0));
        r_loop_ub = norm_vt.size(0);
        for (int i28 = 0; i28 < r_loop_ub; i28++) {
            b_norm_vt[i28] = (norm_vt[i28] > ctx_cfg_ZeroStartVelLimit);
        }

        eml_find(b_norm_vt, tmp_data, tmp_size);
        cut_index_vel_size_idx_1 = tmp_size[1];
        s_loop_ub = tmp_size[1];
        if (0 <= s_loop_ub - 1) {
            std::memcpy(&cut_index_vel_data[0], &tmp_data[0], s_loop_ub * sizeof(int));
        }

        if (tmp_size[1] == 0) {
            cut_index_vel_size_idx_1 = 1;
            cut_index_vel_data[0] = max_jt.size(0);
        }

        if (0 <= cut_index_acc_size_idx_1 - 1) {
            std::memcpy(&varargin_1_data[0], &cut_index_acc_data[0], cut_index_acc_size_idx_1 *
                        sizeof(int));
        }

        for (int i29 = 0; i29 < cut_index_jerk_size_idx_1; i29++) {
            varargin_1_data[i29 + cut_index_acc_size_idx_1] = cut_index_jerk_data[i29];
        }

        for (int i30 = 0; i30 < cut_index_vel_size_idx_1; i30++) {
            varargin_1_data[(i30 + cut_index_acc_size_idx_1) + cut_index_jerk_size_idx_1] =
                cut_index_vel_data[i30];
        }

        c_ex = varargin_1_data[0];
        if (varargin_1_data[0] > varargin_1_data[1]) {
            c_ex = varargin_1_data[1];
        }

        if (c_ex > varargin_1_data[2]) {
            c_ex = varargin_1_data[2];
        }

        u0 = static_cast<int>(std::round(static_cast<double>(max_jt.size(0)) / 2.0));
        if (2 < c_ex - 1) {
            u1 = c_ex - 1;
        } else {
            u1 = 2;
        }

        if (u0 < u1) {
            cut_index = u0;
        } else {
            cut_index = u1;
        }

        L = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->Type,
                       b_CurvStruct->P0, b_CurvStruct->P1, b_CurvStruct->evec, b_CurvStruct->theta,
                       b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                       b_CurvStruct->a_param, b_CurvStruct->b_param);
        *CurvStruct1 = *b_CurvStruct;
        CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1, L - uk[cut_index - 1] *
                      L);
        CurvStruct1->UseConstJerk = true;
        CurvStruct1->ConstJerk = 6.0 / std::pow(t[cut_index - 1], 3.0);

        //      CurvStruct1.ConstJerkTime = t_cut;
        CurvStruct1->ConstJerkMaxIterations = cut_index;
        *CurvStruct2 = *b_CurvStruct;
        b_CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2, uk[cut_index - 1] * L);
        CurvStruct1->zspdmode = ZSpdMode_ZN;
        CurvStruct2->zspdmode = ZSpdMode_NN;
        CurvStruct1->gcode_source_line = b_CurvStruct->gcode_source_line;
        CurvStruct2->gcode_source_line = b_CurvStruct->gcode_source_line;
        if (ctx_cfg_DebugCutZero) {
            printf("======== CUT ZERO START =========\n");
            fflush(stdout);
            printf("Initial: \n");
            fflush(stdout);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->Type,
                              b_CurvStruct->zspdmode, b_CurvStruct->P0, b_CurvStruct->P1,
                              b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                              b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->FeedRate,
                              b_CurvStruct->UseConstJerk, b_CurvStruct->ConstJerk,
                              b_CurvStruct->a_param, b_CurvStruct->b_param);
            printf("\nCut:\n");
            fflush(stdout);
            printf("Index = %d, t_cut = %e, vmax = %.1f\n", cut_index, t[cut_index - 1], b_vmax);
            fflush(stdout);
            printf("jps = %e, norm_vt(%d) = %f\n", jps, cut_index, norm_vt[cut_index - 1]);
            fflush(stdout);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1->Type,
                              ZSpdMode_ZN, CurvStruct1->P0, CurvStruct1->P1, CurvStruct1->evec,
                              CurvStruct1->theta, CurvStruct1->pitch, CurvStruct1->CoeffP5,
                              CurvStruct1->sp_index, CurvStruct1->FeedRate, true,
                              CurvStruct1->ConstJerk, CurvStruct1->a_param, CurvStruct1->b_param);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2->Type,
                              ZSpdMode_NN, CurvStruct2->P0, CurvStruct2->P1, CurvStruct2->evec,
                              CurvStruct2->theta, CurvStruct2->pitch, CurvStruct2->CoeffP5,
                              CurvStruct2->sp_index, CurvStruct2->FeedRate,
                              CurvStruct2->UseConstJerk, CurvStruct2->ConstJerk,
                              CurvStruct2->a_param, CurvStruct2->b_param);
        }
    }

    //
    // EVALCOSTINTEGRAL
    //     I = EVALCOSTINTEGRAL(ALPHA0,BETA0,ALPHA1,BETA1,IN5,IN6,IN7,KAPPA0,IN9,IN10,IN11,KAPPA1)
    // Arguments    : double alpha0
    //                double beta0
    //                double alpha1
    //                double beta1
    //                const double in5[3]
    //                const double in6[3]
    //                const double in7[3]
    //                double kappa0
    //                const double in9[3]
    //                const double in10[3]
    //                const double in11[3]
    //                double kappa1
    // Return Type  : double
    //
    static double EvalCostIntegral(double alpha0, double beta0, double alpha1, double beta1, const
        double in5[3], const double in6[3], const double in7[3], double kappa0, const double in9[3],
        const double in10[3], const double in11[3], double kappa1)
    {
        double t2;
        double t3;
        double t4;
        double t6;
        double t8;
        double t9;
        double t10;
        double t14;
        double t15;
        double t16;
        double t17;
        double t18;
        double t19;
        double t20;
        double t5;
        double t7;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        double I_tmp_tmp;
        double I_tmp;
        double b_I_tmp;
        double c_I_tmp;
        double d_I_tmp;
        double e_I_tmp;
        double f_I_tmp;
        double g_I_tmp;
        double h_I_tmp;
        double i_I_tmp;
        double j_I_tmp;
        double k_I_tmp;
        double l_I_tmp;
        double m_I_tmp;

        //     This function was generated by the Symbolic Math Toolbox version 8.3.
        //     25-May-2019 09:07:06
        t2 = std::pow(alpha0, 2.0);
        t3 = std::pow(alpha0, 3.0);
        t4 = std::pow(alpha1, 2.0);
        t6 = std::pow(alpha1, 3.0);
        t8 = std::pow(beta0, 2.0);
        t9 = std::pow(beta1, 2.0);
        t10 = std::pow(kappa0, 2.0);
        t14 = std::pow(kappa1, 2.0);
        t15 = std::pow(in6[0], 2.0);
        t16 = std::pow(in6[1], 2.0);
        t17 = std::pow(in6[2], 2.0);
        t18 = std::pow(in10[0], 2.0);
        t19 = std::pow(in10[1], 2.0);
        t20 = std::pow(in10[2], 2.0);
        t5 = std::pow(t2, 2.0);
        t7 = std::pow(t4, 2.0);
        d = alpha0 * beta0;
        d1 = alpha1 * beta1;
        d2 = alpha0 * alpha1;
        d3 = alpha0 * beta1;
        d4 = alpha1 * beta0;
        I_tmp_tmp = beta0 * beta1;
        I_tmp = kappa0 * in7[0];
        b_I_tmp = kappa0 * in7[1];
        c_I_tmp = kappa0 * in7[2];
        d_I_tmp = kappa1 * in11[0];
        e_I_tmp = kappa1 * in11[1];
        f_I_tmp = kappa1 * in11[2];
        g_I_tmp = alpha1 * kappa0;
        h_I_tmp = alpha0 * kappa1;
        i_I_tmp = beta0 * kappa0;
        j_I_tmp = beta1 * kappa0;
        k_I_tmp = beta0 * kappa1;
        l_I_tmp = beta1 * kappa1;
        m_I_tmp = kappa0 * kappa1;
        return
            (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
            (((((((((((((((((in5[0] * in9[0] * -1440.0 - in5[1] * in9[1] * 1440.0) - in5[2] * in9[2]
            * 1440.0) + t2 * t15 * 192.0) + t2 * t16 * 192.0) + t2 * t17 * 192.0) + t4 * t18 * 192.0)
            + t4 * t19 * 192.0) + t8 * t15 * 9.0) + t4 * t20 * 192.0) + t8 * t16 * 9.0) + t8 * t17 *
            9.0) + t9 * t18 * 9.0) + t9 * t19 * 9.0) + t9 * t20 * 9.0) + std::pow(in5[0], 2.0) *
            720.0) + std::pow(in5[1], 2.0) * 720.0) + std::pow(in5[2], 2.0) * 720.0) + std::pow(in9
            [0], 2.0) * 720.0) + std::pow(in9[1], 2.0) * 720.0) + std::pow(in9[2], 2.0) * 720.0) +
            std::pow(in7[0], 2.0) * t5 * t10 * 9.0) + std::pow(in7[1], 2.0) * t5 * t10 * 9.0) + std::
            pow(in7[2], 2.0) * t5 * t10 * 9.0) + std::pow(in11[0], 2.0) * t7 * t14 * 9.0) + std::pow
            (in11[1], 2.0) * t7 * t14 * 9.0) + std::pow(in11[2], 2.0) * t7 * t14 * 9.0) + d * t15 *
            72.0) + d * t16 * 72.0) + d * t17 * 72.0) - d1 * t18 * 72.0) - d1 * t19 * 72.0) - d1 *
            t20 * 72.0) + alpha0 * in5[0] * in6[0] * 720.0) + alpha0 * in5[1] * in6[1] * 720.0) +
            alpha0 * in5[2] * in6[2] * 720.0) - alpha0 * in9[0] * in6[0] * 720.0) + alpha1 * in5[0] *
            in10[0] * 720.0) - alpha0 * in9[1] * in6[1] * 720.0) + alpha1 * in5[1] * in10[1] * 720.0)
            - alpha0 * in9[2] * in6[2] * 720.0) + alpha1 * in5[2] * in10[2] * 720.0) - alpha1 * in9
            [0] * in10[0] * 720.0) - alpha1 * in9[1] * in10[1] * 720.0) - alpha1 * in9[2] * in10[2] *
            720.0) + beta0 * in5[0] * in6[0] * 120.0) + beta0 * in5[1] * in6[1] * 120.0) + beta0 *
            in5[2] * in6[2] * 120.0) - beta0 * in9[0] * in6[0] * 120.0) - beta1 * in5[0] * in10[0] *
            120.0) - beta0 * in9[1] * in6[1] * 120.0) - beta1 * in5[1] * in10[1] * 120.0) - beta0 *
            in9[2] * in6[2] * 120.0) - beta1 * in5[2] * in10[2] * 120.0) + beta1 * in9[0] * in10[0] *
            120.0) + beta1 * in9[1] * in10[1] * 120.0) + beta1 * in9[2] * in10[2] * 120.0) + d2 *
            in6[0] * in10[0] * 336.0) + d2 * in6[1] * in10[1] * 336.0) + d2 * in6[2] * in10[2] *
            336.0) - d3 * in6[0] * in10[0] * 48.0) + d4 * in6[0] * in10[0] * 48.0) - d3 * in6[1] *
            in10[1] * 48.0) + d4 * in6[1] * in10[1] * 48.0) - d3 * in6[2] * in10[2] * 48.0) + d4 *
            in6[2] * in10[2] * 48.0) - I_tmp_tmp * in6[0] * in10[0] * 6.0) - I_tmp_tmp * in6[1] *
            in10[1] * 6.0) - I_tmp_tmp * in6[2] * in10[2] * 6.0) + I_tmp * in5[0] * t2 * 120.0) +
            b_I_tmp * in5[1] * t2 * 120.0) + c_I_tmp * in5[2] * t2 * 120.0) - I_tmp * in9[0] * t2 *
            120.0) - b_I_tmp * in9[1] * t2 * 120.0) - d_I_tmp * in5[0] * t4 * 120.0) - c_I_tmp *
            in9[2] * t2 * 120.0) - e_I_tmp * in5[1] * t4 * 120.0) - f_I_tmp * in5[2] * t4 * 120.0) +
            d_I_tmp * in9[0] * t4 * 120.0) + e_I_tmp * in9[1] * t4 * 120.0) + f_I_tmp * in9[2] * t4 *
            120.0) + I_tmp * in6[0] * t3 * 72.0) + b_I_tmp * in6[1] * t3 * 72.0) + c_I_tmp * in6[2] *
            t3 * 72.0) - d_I_tmp * t6 * in10[0] * 72.0) - e_I_tmp * t6 * in10[1] * 72.0) - f_I_tmp *
            t6 * in10[2] * 72.0) + g_I_tmp * in7[0] * t2 * in10[0] * 48.0) - h_I_tmp * in11[0] *
                               in6[0] * t4 * 48.0) + g_I_tmp * in7[1] * t2 * in10[1] * 48.0) -
                             h_I_tmp * in11[1] * in6[1] * t4 * 48.0) + g_I_tmp * in7[2] * t2 * in10
                            [2] * 48.0) - h_I_tmp * in11[2] * in6[2] * t4 * 48.0) + i_I_tmp * in7[0]
                          * in6[0] * t2 * 18.0) + i_I_tmp * in7[1] * in6[1] * t2 * 18.0) + i_I_tmp *
                        in7[2] * t2 * in6[2] * 18.0) - j_I_tmp * in7[0] * t2 * in10[0] * 6.0) -
                      k_I_tmp * in11[0] * in6[0] * t4 * 6.0) - j_I_tmp * in7[1] * t2 * in10[1] * 6.0)
                    - k_I_tmp * in11[1] * in6[1] * t4 * 6.0) - j_I_tmp * in7[2] * t2 * in10[2] * 6.0)
                  - k_I_tmp * in11[2] * in6[2] * t4 * 6.0) + l_I_tmp * in11[0] * t4 * in10[0] * 18.0)
                + l_I_tmp * in11[1] * t4 * in10[1] * 18.0) + l_I_tmp * in11[2] * t4 * in10[2] * 18.0)
              - m_I_tmp * in7[0] * in11[0] * t2 * t4 * 6.0) - m_I_tmp * in7[1] * in11[1] * t2 * t4 *
             6.0) - m_I_tmp * in7[2] * in11[2] * t2 * t4 * 6.0;
    }

    //
    // Arguments    : const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const coder::array<double, 2U> &u_vec
    //                coder::array<double, 2U> &r0D
    //                coder::array<double, 2U> &r1D
    //                coder::array<double, 2U> &r2D
    //                coder::array<double, 2U> &r3D
    // Return Type  : void
    //
    static void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const double
                          CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
                          const coder::array<double, 2U> &u_vec, coder::array<double, 2U> &r0D,
                          coder::array<double, 2U> &r1D, coder::array<double, 2U> &r2D, coder::array<
                          double, 2U> &r3D)
    {
        double P0P1_idx_0;
        double P0P1_idx_1;
        double P0P1_idx_2;
        double EcrP0P1_idx_0;
        double EcrP0P1_idx_1;
        double EcrP0P1_idx_2;
        int loop_ub;
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        char message[16];
        coder::array<double, 2U> phi_vec;
        int i5;
        coder::array<double, 2U> cphi;
        coder::array<double, 2U> sphi;
        coder::array<double, 2U> r;
        coder::array<double, 2U> r1;
        coder::array<double, 2U> cphiTCP0;
        coder::array<double, 2U> r2;
        coder::array<double, 2U> sphiTCP0;
        coder::array<double, 2U> cphiTEcrCP0;
        coder::array<double, 2U> sphiTEcrCP0;
        coder::array<double, 2U> b;
        coder::array<double, 2U> b_b;
        coder::array<double, 2U> c_b;

        //
        P0P1_idx_0 = CurvStruct_P1[0] - CurvStruct_P0[0];
        P0P1_idx_1 = CurvStruct_P1[1] - CurvStruct_P0[1];
        P0P1_idx_2 = CurvStruct_P1[2] - CurvStruct_P0[2];
        EcrP0P1_idx_0 = CurvStruct_evec[1] * P0P1_idx_2 - CurvStruct_evec[2] * P0P1_idx_1;
        EcrP0P1_idx_1 = CurvStruct_evec[2] * P0P1_idx_0 - CurvStruct_evec[0] * P0P1_idx_2;
        EcrP0P1_idx_2 = CurvStruct_evec[0] * P0P1_idx_1 - CurvStruct_evec[1] * P0P1_idx_0;
        r0D.set_size(3, u_vec.size(1));
        loop_ub = u_vec.size(1);
        for (int i = 0; i < loop_ub; i++) {
            r0D[3 * i] = 0.0;
            r0D[3 * i + 1] = 0.0;
            r0D[3 * i + 2] = 0.0;
        }

        r1D.set_size(3, u_vec.size(1));
        b_loop_ub = u_vec.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            r1D[3 * i1] = 0.0;
            r1D[3 * i1 + 1] = 0.0;
            r1D[3 * i1 + 2] = 0.0;
        }

        r2D.set_size(3, u_vec.size(1));
        c_loop_ub = u_vec.size(1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            r2D[3 * i2] = 0.0;
            r2D[3 * i2 + 1] = 0.0;
            r2D[3 * i2 + 2] = 0.0;
        }

        r3D.set_size(3, u_vec.size(1));
        d_loop_ub = u_vec.size(1);
        for (int i3 = 0; i3 < d_loop_ub; i3++) {
            r3D[3 * i3] = 0.0;
            r3D[3 * i3 + 1] = 0.0;
            r3D[3 * i3 + 2] = 0.0;
        }

        if (std::sqrt((std::pow(EcrP0P1_idx_0, 2.0) + std::pow(EcrP0P1_idx_1, 2.0)) + std::pow
                      (EcrP0P1_idx_2, 2.0)) <= 2.2204460492503131E-16) {
            for (int i4 = 0; i4 < 16; i4++) {
                message[i4] = cv1[i4];
            }

            c_assert_(&message[0]);
        } else {
            double P0P1;
            double a;
            double d;
            double C_idx_0;
            double CP0_idx_0;
            double C_idx_1;
            double CP0_idx_1;
            double CP0_idx_2;
            int e_loop_ub;
            int scalarLB;
            int vectorUB;
            int f_loop_ub;
            int i7;
            int g_loop_ub;
            int i9;
            int h_loop_ub;
            int i_loop_ub;
            double a_idx_0;
            double a_idx_1;
            double a_idx_2;
            int j_loop_ub;
            int k_loop_ub;
            double b_a;
            int l_loop_ub;
            double c_a;
            int m_loop_ub;
            double a_tmp;
            int n_loop_ub;
            double b_a_tmp;
            int o_loop_ub;

            //  if pitch == 0
            //      if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
            //          return;
            //      end
            //  end
            //
            P0P1 = (P0P1_idx_0 * CurvStruct_evec[0] + P0P1_idx_1 * CurvStruct_evec[1]) + P0P1_idx_2 *
                CurvStruct_evec[2];
            a = 1.0 / std::tan(CurvStruct_theta / 2.0);
            d = ((CurvStruct_P0[0] + (CurvStruct_P1[0] - P0P1 * CurvStruct_evec[0])) + a *
                 EcrP0P1_idx_0) / 2.0;
            C_idx_0 = d;
            CP0_idx_0 = CurvStruct_P0[0] - d;
            d = ((CurvStruct_P0[1] + (CurvStruct_P1[1] - P0P1 * CurvStruct_evec[1])) + a *
                 EcrP0P1_idx_1) / 2.0;
            C_idx_1 = d;
            CP0_idx_1 = CurvStruct_P0[1] - d;
            d = ((CurvStruct_P0[2] + (CurvStruct_P1[2] - P0P1 * CurvStruct_evec[2])) + a *
                 EcrP0P1_idx_2) / 2.0;
            CP0_idx_2 = CurvStruct_P0[2] - d;
            phi_vec.set_size(1, u_vec.size(1));
            e_loop_ub = u_vec.size(1);
            scalarLB = u_vec.size(1) & -4;
            vectorUB = scalarLB - 4;
            for (i5 = 0; i5 <= vectorUB; i5 += 4) {
                _mm256_storeu_pd(&phi_vec[i5], _mm256_mul_pd(_mm256_set1_pd(CurvStruct_theta),
                                  _mm256_loadu_pd(&u_vec[i5])));
            }

            for (i5 = scalarLB; i5 < e_loop_ub; i5++) {
                phi_vec[i5] = CurvStruct_theta * u_vec[i5];
            }

            cphi.set_size(1, phi_vec.size(1));
            f_loop_ub = phi_vec.size(1);
            for (int i6 = 0; i6 < f_loop_ub; i6++) {
                cphi[i6] = phi_vec[i6];
            }

            i7 = phi_vec.size(1);
            for (int k = 0; k < i7; k++) {
                cphi[k] = std::cos(cphi[k]);
            }

            sphi.set_size(1, phi_vec.size(1));
            g_loop_ub = phi_vec.size(1);
            for (int i8 = 0; i8 < g_loop_ub; i8++) {
                sphi[i8] = phi_vec[i8];
            }

            i9 = phi_vec.size(1);
            for (int b_k = 0; b_k < i9; b_k++) {
                sphi[b_k] = std::sin(sphi[b_k]);
            }

            //
            r.set_size(3, cphi.size(1));
            if (cphi.size(1) != 0) {
                int na;
                na = cphi.size(1);
                for (int c_k = 0; c_k < na; c_k++) {
                    r[3 * c_k] = cphi[c_k];
                    r[3 * c_k + 1] = cphi[c_k];
                    r[3 * c_k + 2] = cphi[c_k];
                }
            }

            r1.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int i10;
                i10 = u_vec.size(1) - 1;
                for (int t = 0; t <= i10; t++) {
                    r1[3 * t] = CP0_idx_0;
                    r1[3 * t + 1] = CP0_idx_1;
                    r1[3 * t + 2] = CP0_idx_2;
                }
            }

            cphiTCP0.set_size(3, r.size(1));
            h_loop_ub = r.size(1);
            for (int i11 = 0; i11 < h_loop_ub; i11++) {
                cphiTCP0[3 * i11] = r[3 * i11] * r1[3 * i11];
                cphiTCP0[3 * i11 + 1] = r[3 * i11 + 1] * r1[3 * i11 + 1];
                cphiTCP0[3 * i11 + 2] = r[3 * i11 + 2] * r1[3 * i11 + 2];
            }

            r2.set_size(3, sphi.size(1));
            if (sphi.size(1) != 0) {
                int b_na;
                b_na = sphi.size(1);
                for (int d_k = 0; d_k < b_na; d_k++) {
                    r2[3 * d_k] = sphi[d_k];
                    r2[3 * d_k + 1] = sphi[d_k];
                    r2[3 * d_k + 2] = sphi[d_k];
                }
            }

            sphiTCP0.set_size(3, r2.size(1));
            i_loop_ub = r2.size(1);
            for (int i12 = 0; i12 < i_loop_ub; i12++) {
                sphiTCP0[3 * i12] = r2[3 * i12] * r1[3 * i12];
                sphiTCP0[3 * i12 + 1] = r2[3 * i12 + 1] * r1[3 * i12 + 1];
                sphiTCP0[3 * i12 + 2] = r2[3 * i12 + 2] * r1[3 * i12 + 2];
            }

            a_idx_0 = CurvStruct_evec[1] * CP0_idx_2 - CurvStruct_evec[2] * CP0_idx_1;
            a_idx_1 = CurvStruct_evec[2] * CP0_idx_0 - CurvStruct_evec[0] * CP0_idx_2;
            a_idx_2 = CurvStruct_evec[0] * CP0_idx_1 - CurvStruct_evec[1] * CP0_idx_0;
            r1.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int i13;
                i13 = u_vec.size(1) - 1;
                for (int b_t = 0; b_t <= i13; b_t++) {
                    r1[3 * b_t] = a_idx_0;
                    r1[3 * b_t + 1] = a_idx_1;
                    r1[3 * b_t + 2] = a_idx_2;
                }
            }

            cphiTEcrCP0.set_size(3, r.size(1));
            j_loop_ub = r.size(1);
            for (int i14 = 0; i14 < j_loop_ub; i14++) {
                cphiTEcrCP0[3 * i14] = r[3 * i14] * r1[3 * i14];
                cphiTEcrCP0[3 * i14 + 1] = r[3 * i14 + 1] * r1[3 * i14 + 1];
                cphiTEcrCP0[3 * i14 + 2] = r[3 * i14 + 2] * r1[3 * i14 + 2];
            }

            sphiTEcrCP0.set_size(3, r2.size(1));
            k_loop_ub = r2.size(1);
            for (int i15 = 0; i15 < k_loop_ub; i15++) {
                sphiTEcrCP0[3 * i15] = r2[3 * i15] * r1[3 * i15];
                sphiTEcrCP0[3 * i15 + 1] = r2[3 * i15 + 1] * r1[3 * i15 + 1];
                sphiTEcrCP0[3 * i15 + 2] = r2[3 * i15 + 2] * r1[3 * i15 + 2];
            }

            //
            b_a = CurvStruct_pitch / 6.2831853071795862;
            b.set_size(3, phi_vec.size(1));
            if (phi_vec.size(1) != 0) {
                int c_na;
                c_na = phi_vec.size(1);
                for (int e_k = 0; e_k < c_na; e_k++) {
                    b[3 * e_k] = phi_vec[e_k];
                    b[3 * e_k + 1] = phi_vec[e_k];
                    b[3 * e_k + 2] = phi_vec[e_k];
                }
            }

            b_b.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int i16;
                i16 = u_vec.size(1) - 1;
                for (int c_t = 0; c_t <= i16; c_t++) {
                    b_b[3 * c_t] = CurvStruct_evec[0];
                    b_b[3 * c_t + 1] = CurvStruct_evec[1];
                    b_b[3 * c_t + 2] = CurvStruct_evec[2];
                }
            }

            c_b.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int i17;
                i17 = u_vec.size(1) - 1;
                for (int d_t = 0; d_t <= i17; d_t++) {
                    c_b[3 * d_t] = C_idx_0;
                    c_b[3 * d_t + 1] = C_idx_1;
                    c_b[3 * d_t + 2] = d;
                }
            }

            r0D.set_size(3, c_b.size(1));
            l_loop_ub = c_b.size(1);
            for (int i18 = 0; i18 < l_loop_ub; i18++) {
                r0D[3 * i18] = ((c_b[3 * i18] + cphiTCP0[3 * i18]) + sphiTEcrCP0[3 * i18]) + b_a *
                    b[3 * i18] * b_b[3 * i18];
                r0D[3 * i18 + 1] = ((c_b[3 * i18 + 1] + cphiTCP0[3 * i18 + 1]) + sphiTEcrCP0[3 * i18
                                    + 1]) + b_a * b[3 * i18 + 1] * b_b[3 * i18 + 1];
                r0D[3 * i18 + 2] = ((c_b[3 * i18 + 2] + cphiTCP0[3 * i18 + 2]) + sphiTEcrCP0[3 * i18
                                    + 2]) + b_a * b[3 * i18 + 2] * b_b[3 * i18 + 2];
            }

            c_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
            r1D.set_size(3, sphiTCP0.size(1));
            m_loop_ub = sphiTCP0.size(1);
            for (int i19 = 0; i19 < m_loop_ub; i19++) {
                r1D[3 * i19] = (-CurvStruct_theta * sphiTCP0[3 * i19] + CurvStruct_theta *
                                cphiTEcrCP0[3 * i19]) + c_a * b_b[3 * i19];
                r1D[3 * i19 + 1] = (-CurvStruct_theta * sphiTCP0[3 * i19 + 1] + CurvStruct_theta *
                                    cphiTEcrCP0[3 * i19 + 1]) + c_a * b_b[3 * i19 + 1];
                r1D[3 * i19 + 2] = (-CurvStruct_theta * sphiTCP0[3 * i19 + 2] + CurvStruct_theta *
                                    cphiTEcrCP0[3 * i19 + 2]) + c_a * b_b[3 * i19 + 2];
            }

            a_tmp = std::pow(CurvStruct_theta, 2.0);
            r2D.set_size(3, cphiTCP0.size(1));
            n_loop_ub = cphiTCP0.size(1);
            for (int i20 = 0; i20 < n_loop_ub; i20++) {
                r2D[3 * i20] = -a_tmp * cphiTCP0[3 * i20] - a_tmp * sphiTEcrCP0[3 * i20];
                r2D[3 * i20 + 1] = -a_tmp * cphiTCP0[3 * i20 + 1] - a_tmp * sphiTEcrCP0[3 * i20 + 1];
                r2D[3 * i20 + 2] = -a_tmp * cphiTCP0[3 * i20 + 2] - a_tmp * sphiTEcrCP0[3 * i20 + 2];
            }

            b_a_tmp = std::pow(CurvStruct_theta, 3.0);
            r3D.set_size(3, sphiTCP0.size(1));
            o_loop_ub = sphiTCP0.size(1);
            for (int i21 = 0; i21 < o_loop_ub; i21++) {
                r3D[3 * i21] = b_a_tmp * sphiTCP0[3 * i21] - b_a_tmp * cphiTEcrCP0[3 * i21];
                r3D[3 * i21 + 1] = b_a_tmp * sphiTCP0[3 * i21 + 1] - b_a_tmp * cphiTEcrCP0[3 * i21 +
                    1];
                r3D[3 * i21 + 2] = b_a_tmp * sphiTCP0[3 * i21 + 2] - b_a_tmp * cphiTEcrCP0[3 * i21 +
                    2];
            }
        }
    }

    //
    // Arguments    : const double CurvStruct_CoeffP5[6][3]
    //                const coder::array<double, 2U> &u_vec
    //                coder::array<double, 2U> &r_0D
    //                coder::array<double, 2U> &r_1D
    //                coder::array<double, 2U> &r_2D
    //                coder::array<double, 2U> &r_3D
    // Return Type  : void
    //
    static void EvalTransP5(const double CurvStruct_CoeffP5[6][3], const coder::array<double, 2U>
                            &u_vec, coder::array<double, 2U> &r_0D, coder::array<double, 2U> &r_1D,
                            coder::array<double, 2U> &r_2D, coder::array<double, 2U> &r_3D)
    {
        double p5_1D[5][3];
        double p5_2D[4][3];
        double p5_3D[3][3];
        coder::array<double, 2U> r;
        coder::array<double, 2U> b;

        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        for (int k = 0; k < 5; k++) {
            int p5_1D_tmp;
            p5_1D_tmp = 5 - k;
            p5_1D[k][0] = CurvStruct_CoeffP5[k][0] * static_cast<double>(p5_1D_tmp);
            p5_1D[k][1] = CurvStruct_CoeffP5[k][1] * static_cast<double>(p5_1D_tmp);
            p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * static_cast<double>(p5_1D_tmp);
        }

        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        for (int b_k = 0; b_k < 4; b_k++) {
            int p5_2D_tmp;
            p5_2D_tmp = 4 - b_k;
            p5_2D[b_k][0] = p5_1D[b_k][0] * static_cast<double>(p5_2D_tmp);
            p5_2D[b_k][1] = p5_1D[b_k][1] * static_cast<double>(p5_2D_tmp);
            p5_2D[b_k][2] = p5_1D[b_k][2] * static_cast<double>(p5_2D_tmp);
        }

        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        for (int c_k = 0; c_k < 3; c_k++) {
            int p5_3D_tmp;
            p5_3D_tmp = 3 - c_k;
            p5_3D[c_k][0] = p5_2D[c_k][0] * static_cast<double>(p5_3D_tmp);
            p5_3D[c_k][1] = p5_2D[c_k][1] * static_cast<double>(p5_3D_tmp);
            p5_3D[c_k][2] = p5_2D[c_k][2] * static_cast<double>(p5_3D_tmp);
        }

        //
        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        r_0D.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int i;
            i = u_vec.size(1) - 1;
            for (int t = 0; t <= i; t++) {
                r_0D[3 * t] = CurvStruct_CoeffP5[0][0];
                r_0D[3 * t + 1] = CurvStruct_CoeffP5[0][1];
                r_0D[3 * t + 2] = CurvStruct_CoeffP5[0][2];
            }
        }

        for (int b_i = 0; b_i < 5; b_i++) {
            int loop_ub;
            r.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int na;
                na = u_vec.size(1);
                for (int d_k = 0; d_k < na; d_k++) {
                    r[3 * d_k] = u_vec[d_k];
                    r[3 * d_k + 1] = u_vec[d_k];
                    r[3 * d_k + 2] = u_vec[d_k];
                }
            }

            b.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int i1;
                i1 = u_vec.size(1) - 1;
                for (int b_t = 0; b_t <= i1; b_t++) {
                    b[3 * b_t] = CurvStruct_CoeffP5[b_i + 1][0];
                    b[3 * b_t + 1] = CurvStruct_CoeffP5[b_i + 1][1];
                    b[3 * b_t + 2] = CurvStruct_CoeffP5[b_i + 1][2];
                }
            }

            r_0D.set_size(3, r.size(1));
            loop_ub = r.size(1);
            for (int i3 = 0; i3 < loop_ub; i3++) {
                r_0D[3 * i3] = r[3 * i3] * r_0D[3 * i3] + b[3 * i3];
                r_0D[3 * i3 + 1] = r[3 * i3 + 1] * r_0D[3 * i3 + 1] + b[3 * i3 + 1];
                r_0D[3 * i3 + 2] = r[3 * i3 + 2] * r_0D[3 * i3 + 2] + b[3 * i3 + 2];
            }
        }

        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        r_1D.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int i2;
            i2 = u_vec.size(1) - 1;
            for (int c_t = 0; c_t <= i2; c_t++) {
                r_1D[3 * c_t] = p5_1D[0][0];
                r_1D[3 * c_t + 1] = p5_1D[0][1];
                r_1D[3 * c_t + 2] = p5_1D[0][2];
            }
        }

        for (int c_i = 0; c_i < 4; c_i++) {
            int b_loop_ub;
            r.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int b_na;
                b_na = u_vec.size(1);
                for (int e_k = 0; e_k < b_na; e_k++) {
                    r[3 * e_k] = u_vec[e_k];
                    r[3 * e_k + 1] = u_vec[e_k];
                    r[3 * e_k + 2] = u_vec[e_k];
                }
            }

            b.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int i4;
                i4 = u_vec.size(1) - 1;
                for (int d_t = 0; d_t <= i4; d_t++) {
                    b[3 * d_t] = p5_1D[c_i + 1][0];
                    b[3 * d_t + 1] = p5_1D[c_i + 1][1];
                    b[3 * d_t + 2] = p5_1D[c_i + 1][2];
                }
            }

            r_1D.set_size(3, r.size(1));
            b_loop_ub = r.size(1);
            for (int i6 = 0; i6 < b_loop_ub; i6++) {
                r_1D[3 * i6] = r[3 * i6] * r_1D[3 * i6] + b[3 * i6];
                r_1D[3 * i6 + 1] = r[3 * i6 + 1] * r_1D[3 * i6 + 1] + b[3 * i6 + 1];
                r_1D[3 * i6 + 2] = r[3 * i6 + 2] * r_1D[3 * i6 + 2] + b[3 * i6 + 2];
            }
        }

        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        r_2D.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int i5;
            i5 = u_vec.size(1) - 1;
            for (int e_t = 0; e_t <= i5; e_t++) {
                r_2D[3 * e_t] = p5_2D[0][0];
                r_2D[3 * e_t + 1] = p5_2D[0][1];
                r_2D[3 * e_t + 2] = p5_2D[0][2];
            }
        }

        for (int d_i = 0; d_i < 3; d_i++) {
            int c_loop_ub;
            r.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int c_na;
                c_na = u_vec.size(1);
                for (int f_k = 0; f_k < c_na; f_k++) {
                    r[3 * f_k] = u_vec[f_k];
                    r[3 * f_k + 1] = u_vec[f_k];
                    r[3 * f_k + 2] = u_vec[f_k];
                }
            }

            b.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int i7;
                i7 = u_vec.size(1) - 1;
                for (int f_t = 0; f_t <= i7; f_t++) {
                    b[3 * f_t] = p5_2D[d_i + 1][0];
                    b[3 * f_t + 1] = p5_2D[d_i + 1][1];
                    b[3 * f_t + 2] = p5_2D[d_i + 1][2];
                }
            }

            r_2D.set_size(3, r.size(1));
            c_loop_ub = r.size(1);
            for (int i9 = 0; i9 < c_loop_ub; i9++) {
                r_2D[3 * i9] = r[3 * i9] * r_2D[3 * i9] + b[3 * i9];
                r_2D[3 * i9 + 1] = r[3 * i9 + 1] * r_2D[3 * i9 + 1] + b[3 * i9 + 1];
                r_2D[3 * i9 + 2] = r[3 * i9 + 2] * r_2D[3 * i9 + 2] + b[3 * i9 + 2];
            }
        }

        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        r_3D.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int i8;
            i8 = u_vec.size(1) - 1;
            for (int g_t = 0; g_t <= i8; g_t++) {
                r_3D[3 * g_t] = p5_3D[0][0];
                r_3D[3 * g_t + 1] = p5_3D[0][1];
                r_3D[3 * g_t + 2] = p5_3D[0][2];
            }
        }

        for (int e_i = 0; e_i < 2; e_i++) {
            int d_loop_ub;
            r.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int d_na;
                d_na = u_vec.size(1);
                for (int g_k = 0; g_k < d_na; g_k++) {
                    r[3 * g_k] = u_vec[g_k];
                    r[3 * g_k + 1] = u_vec[g_k];
                    r[3 * g_k + 2] = u_vec[g_k];
                }
            }

            b.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int i10;
                i10 = u_vec.size(1) - 1;
                for (int h_t = 0; h_t <= i10; h_t++) {
                    b[3 * h_t] = p5_3D[e_i + 1][0];
                    b[3 * h_t + 1] = p5_3D[e_i + 1][1];
                    b[3 * h_t + 2] = p5_3D[e_i + 1][2];
                }
            }

            r_3D.set_size(3, r.size(1));
            d_loop_ub = r.size(1);
            for (int i11 = 0; i11 < d_loop_ub; i11++) {
                r_3D[3 * i11] = r[3 * i11] * r_3D[3 * i11] + b[3 * i11];
                r_3D[3 * i11 + 1] = r[3 * i11 + 1] * r_3D[3 * i11 + 1] + b[3 * i11 + 1];
                r_3D[3 * i11 + 2] = r[3 * i11 + 2] * r_3D[3 * i11 + 2] + b[3 * i11 + 2];
            }
        }
    }

    //
    // We replace each sequence of small g-code segments with a B-Spline
    //  of degree 3
    //  A special queue is dedicated to the splines, ctx.q_splines
    // Arguments    : const FeedoptContext *ctx
    // Return Type  : void
    //
    static void ExpandZeroStructs(const FeedoptContext *ctx)
    {
        CurvStruct Curv;
        CurvStruct CurvStruct1_C;
        CurvStruct CurvStruct2_C;
        CurvStruct b_CurvStruct2_C;
        CurvStruct CurvStruct3_C;
        if (!ctx->q_gcode.isempty()) {
            unsigned int Ncrv;
            int i;
            Ncrv = ctx->q_gcode.size();

            //  1 -> stdout
            //  2 -> stderr
            if ((static_cast<unsigned long>(std::round(DebugConfig)) & 1UL) != 0UL) {
                printf("Expanding ...\n");
                fflush(stdout);
            }

            i = static_cast<int>(Ncrv);
            for (int k = 0; k < i; k++) {
                ctx->q_gcode.get((static_cast<double>(k) + 1.0), (&Curv));
                if (Curv.zspdmode == ZSpdMode_ZN) {
                    CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                 ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                 ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                 ctx->cfg.DebugCutZero, ctx->cfg.NGridLengthSpline, &Curv,
                                 static_cast<double>(k) + 1.0, &CurvStruct1_C, &CurvStruct2_C);
                    ctx->q_compress.push((&CurvStruct1_C));
                    ctx->q_compress.push((&CurvStruct2_C));
                } else if (Curv.zspdmode == ZSpdMode_NZ) {
                    CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                               ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                               ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                               ctx->cfg.NGridLengthSpline, &Curv, static_cast<double>(k) + 1.0,
                               &CurvStruct1_C, &CurvStruct2_C);
                    ctx->q_compress.push((&CurvStruct1_C));
                    ctx->q_compress.push((&CurvStruct2_C));
                } else if (Curv.zspdmode == ZSpdMode_ZZ) {
                    CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                 ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                 ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                 ctx->cfg.DebugCutZero, ctx->cfg.NGridLengthSpline, &Curv,
                                 static_cast<double>(k) + 1.0, &CurvStruct1_C, &CurvStruct2_C);
                    CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                               ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                               ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                               ctx->cfg.NGridLengthSpline, &CurvStruct2_C, static_cast<double>(k) +
                               1.0, &b_CurvStruct2_C, &CurvStruct3_C);
                    ctx->q_compress.push((&CurvStruct1_C));
                    ctx->q_compress.push((&b_CurvStruct2_C));
                    ctx->q_compress.push((&CurvStruct3_C));
                } else {
                    ctx->q_compress.push((&Curv));
                }
            }
        }
    }

    //
    // Arguments    : FeedoptContext *ctx
    //                const coder::array<CurvStruct, 2U> &CurvStructs0
    //                const double amax[3]
    //                double jmax[3]
    //                const coder::array<double, 2U> &BasisVal
    //                const coder::array<double, 2U> &BasisValD
    //                const coder::array<double, 2U> &BasisValDD
    //                const coder::array<double, 1U> &BasisIntegr
    //                unsigned long Bl_handle
    //                const coder::array<double, 2U> &u_vec
    //                int N_Hor
    //                coder::array<double, 2U> &Coeff
    //                int *NCoeff
    //                bool *success
    // Return Type  : void
    //
    static void FeedratePlanning_v4(FeedoptContext *ctx, const coder::array<CurvStruct, 2U>
        &CurvStructs0, const double amax[3], double jmax[3], const coder::array<double, 2U>
        &BasisVal, const coder::array<double, 2U> &BasisValD, const coder::array<double, 2U>
        &BasisValDD, const coder::array<double, 1U> &BasisIntegr, unsigned long Bl_handle, const
        coder::array<double, 2U> &u_vec, int N_Hor, coder::array<double, 2U> &Coeff, int *NCoeff,
        bool *success)
    {
        int varargin_2;
        unsigned long u;
        unsigned long u1;
        coder::array<double, 2U> b;
        coder::array<double, 2U> f;
        int loop_ub;
        int i2;
        coder::array<CurvStruct, 2U> b_CurvStructs0;
        coder::array<double, 2U> b_BasisVal;
        int c_loop_ub;
        coder::array<double, 2U> b_BasisValD;
        int e_loop_ub;
        coder_internal_sparse A;
        coder::array<double, 1U> b_b;
        coder::array<double, 2U> Aeq;
        coder::array<double, 1U> beq;
        int beq_idx_0;
        coder::array<double, 2U> c_b;
        int g_loop_ub;
        coder::array<double, 2U> b_beq;
        coder::array<double, 2U> Coeff0;
        bool b_success;
        int status;
        bool c_success;
        int b_NCoeff;
        coder::array<double, 2U> Coeff2;
        coder_internal_sparse A_jerk;
        coder::array<double, 1U> b_jerk;
        coder::array<double, 2U> d_b;
        coder_internal_sparse r1;
        coder::array<double, 2U> c_beq;
        bool d_success;
        int b_status;
        double r1D[3];
        double r2D[3];
        double unusedU0[3];
        double r3D[3];
        CurvStruct expl_temp;
        char message[30];
        coder::array<double, 2U> Spline_sp_CoeffX;
        coder::array<double, 2U> Spline_sp_CoeffY;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        double r0Dx;
        double r1Dx;
        double r2Dx;
        double r3Dx;
        double r0Dy;
        double r1Dy;
        double r2Dy;
        double r3Dy;
        double r0Dz;
        double r1Dz;
        double r2Dz;
        double r3Dz;
        double q_val;
        double qD_val;
        coder::array<double, 1U> b_Coeff2;
        double unusedU1[3];
        double v3;
        if (1 > N_Hor) {
            varargin_2 = 0;
        } else {
            varargin_2 = N_Hor;
        }

        //  1 -> stdout
        //  2 -> stderr
        u = static_cast<unsigned long>(std::round(DebugConfig));
        u1 = u & 4UL;
        if (u1 != 0UL) {
            printf("===============================\n");
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u1 != 0UL) {
            printf("====== FEEDRATE PLANNING ======\n");
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u1 != 0UL) {
            printf("===============================\n");
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u1 != 0UL) {
            printf("v_0  = %f\n", ctx->v_0);
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u1 != 0UL) {
            printf("at_0 = %f\n", ctx->at_0);
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u1 != 0UL) {
            printf("v_1  = %f\n", ctx->v_1);
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u1 != 0UL) {
            printf("at_1 = %f\n", ctx->at_1);
            fflush(stdout);
            for (int k = 0; k < varargin_2; k++) {
                b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStructs0[k].Type,
                                  CurvStructs0[k].zspdmode, CurvStructs0[k].P0, CurvStructs0[k].P1,
                                  CurvStructs0[k].evec, CurvStructs0[k].theta, CurvStructs0[k].pitch,
                                  CurvStructs0[k].CoeffP5, CurvStructs0[k].sp_index, CurvStructs0[k]
                                  .FeedRate, CurvStructs0[k].UseConstJerk, CurvStructs0[k].ConstJerk,
                                  CurvStructs0[k].a_param, CurvStructs0[k].b_param);
            }
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u1 != 0UL) {
            printf("===============================\n");
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u1 != 0UL) {
            printf("===============================\n");
            fflush(stdout);
        }

        //
        //  FIRST setup of Linear Program (LP) WITHOUT jerk constraint
        b.set_size(BasisIntegr.size(0), varargin_2);
        if ((BasisIntegr.size(0) != 0) && (varargin_2 != 0)) {
            int i;
            i = varargin_2 - 1;
            for (int t = 0; t <= i; t++) {
                int na;
                na = BasisIntegr.size(0);
                for (int b_k = 0; b_k < na; b_k++) {
                    b[b_k + b.size(0) * t] = BasisIntegr[b_k];
                }
            }
        }

        f.set_size(b.size(0), b.size(1));
        loop_ub = b.size(1);
        for (int i1 = 0; i1 < loop_ub; i1++) {
            int b_loop_ub;
            int scalarLB;
            int vectorUB;
            b_loop_ub = b.size(0);
            scalarLB = b.size(0) & -4;
            vectorUB = scalarLB - 4;
            for (i2 = 0; i2 <= vectorUB; i2 += 4) {
                __m256d r;
                r = _mm256_loadu_pd(&b[i2 + b.size(0) * i1]);
                _mm256_storeu_pd(&f[i2 + f.size(0) * i1], _mm256_mul_pd(r, _mm256_set1_pd(-1.0)));
            }

            for (i2 = scalarLB; i2 < b_loop_ub; i2++) {
                f[i2 + f.size(0) * i1] = -b[i2 + b.size(0) * i1];
            }
        }

        //  maximize integral of q
        //  equality constraints
        //  to satisfy the coder
        //  -----------
        b_CurvStructs0.set_size(1, varargin_2);
        for (int i3 = 0; i3 < varargin_2; i3++) {
            b_CurvStructs0[i3] = CurvStructs0[i3];
        }

        b_BasisVal.set_size(BasisVal.size(0), BasisVal.size(1));
        c_loop_ub = BasisVal.size(1) - 1;
        for (int i4 = 0; i4 <= c_loop_ub; i4++) {
            int d_loop_ub;
            d_loop_ub = BasisVal.size(0) - 1;
            for (int i5 = 0; i5 <= d_loop_ub; i5++) {
                b_BasisVal[i5 + b_BasisVal.size(0) * i4] = BasisVal[i5 + BasisVal.size(0) * i4];
            }
        }

        b_BasisValD.set_size(BasisValD.size(0), BasisValD.size(1));
        e_loop_ub = BasisValD.size(1) - 1;
        for (int i6 = 0; i6 <= e_loop_ub; i6++) {
            int f_loop_ub;
            f_loop_ub = BasisValD.size(0) - 1;
            for (int i7 = 0; i7 <= f_loop_ub; i7++) {
                b_BasisValD[i7 + b_BasisValD.size(0) * i6] = BasisValD[i7 + BasisValD.size(0) * i6];
            }
        }

        int b_idx_0;
        BuildConstr_v4(&ctx->q_splines, ctx->cfg.UseDynamicBreakpoints,
                       ctx->cfg.UseLinearBreakpoints, ctx->cfg.DynamicBreakpointsDistance,
                       ctx->cfg.SplineDegree, ctx->cfg.NGridLengthSpline, ctx->Bl.ncoeff,
                       ctx->Bl.handle, b_CurvStructs0, amax, ctx->v_0, ctx->at_0, ctx->v_1,
                       ctx->at_1, b_BasisVal, b_BasisValD, u_vec, &A, b_b, Aeq, beq);
        b_idx_0 = b_b.size(0);
        beq_idx_0 = beq.size(0);
        c_b.set_size(b_idx_0, 1);
        g_loop_ub = b_idx_0 - 1;
        for (int i8 = 0; i8 <= g_loop_ub; i8++) {
            c_b[i8] = b_b[i8];
        }

        b_beq = beq.reshape(beq_idx_0, 1);
        c_simplex(f, &A, c_b, Aeq, b_beq, Coeff0, &b_success, &status);
        c_success = b_success;

        //
        //  tic
        //  Coeff1 = linprog(f, A, b, Aeq, beq, [], [], options);
        //  toc Coeff(:, end-N_Hor+2:end) = C(:, 2:end);
        //
        if (!b_success) {
            Coeff.set_size(0, 0);
            b_NCoeff = 0;
        } else {
            unsigned long u2;
            int i9;
            int max_increase;

            //  1 -> stdout
            //  2 -> stderr
            u2 = u & 8UL;
            if (u2 != 0UL) {
                printf("Coeff1 = ");
                fflush(stdout);
            }

            i9 = BasisVal.size(1);
            for (int c_k = 0; c_k < i9; c_k++) {
                //  1 -> stdout
                //  2 -> stderr
                if (u2 != 0UL) {
                    printf("%.4f ", Coeff0[c_k]);
                    fflush(stdout);
                }
            }

            //  1 -> stdout
            //  2 -> stderr
            if (u2 != 0UL) {
                printf("\n");
                fflush(stdout);
            }

            //  SECOND setup of Linear Program (LP) WITH jerk constraint
            c_success = false;
            max_increase = 20;
            Coeff2.set_size(BasisVal.size(1), varargin_2);
            for (int i10 = 0; i10 < varargin_2; i10++) {
                int h_loop_ub;
                h_loop_ub = BasisVal.size(1);
                for (int i11 = 0; i11 < h_loop_ub; i11++) {
                    Coeff2[i11 + Coeff2.size(0) * i10] = 0.0;
                }
            }

            //  satisfy the coder
            while ((!c_success) && (max_increase > 0)) {
                int N_idx_0;
                int input_sizes_idx_0;
                int b_input_sizes_idx_0;
                int c_input_sizes_idx_0;
                N_idx_0 = BasisVal.size(1);
                b_CurvStructs0.set_size(1, varargin_2);
                for (int i12 = 0; i12 < varargin_2; i12++) {
                    b_CurvStructs0[i12] = CurvStructs0[i12];
                }

                coder::array<double, 2U> b_Coeff0;
                b_Coeff0 = Coeff0.reshape(N_idx_0, varargin_2);
                BuildConstrJerk_v4(&ctx->q_splines, b_CurvStructs0, b_Coeff0, jmax, BasisVal,
                                   BasisValD, BasisValDD, u_vec, &A_jerk, b_jerk);

                //
                //
                if (b_b.size(0) != 0) {
                    input_sizes_idx_0 = b_b.size(0);
                } else {
                    input_sizes_idx_0 = 0;
                }

                if (b_jerk.size(0) != 0) {
                    b_input_sizes_idx_0 = b_jerk.size(0);
                } else {
                    b_input_sizes_idx_0 = 0;
                }

                if (b_b.size(0) != 0) {
                    c_input_sizes_idx_0 = b_b.size(0);
                } else {
                    c_input_sizes_idx_0 = 0;
                }

                beq_idx_0 = beq.size(0);
                d_b.set_size((input_sizes_idx_0 + b_input_sizes_idx_0), 1);
                for (int i14 = 0; i14 < input_sizes_idx_0; i14++) {
                    d_b[i14] = b_b[i14];
                }

                for (int i15 = 0; i15 < b_input_sizes_idx_0; i15++) {
                    d_b[i15 + c_input_sizes_idx_0] = b_jerk[i15];
                }

                A.vertcat((&A_jerk), (&r1));
                c_beq = beq.reshape(beq_idx_0, 1);
                c_simplex(f, &r1, d_b, Aeq, c_beq, Coeff2, &d_success, &b_status);
                c_success = d_success;
                if (!d_success) {
                    //          amax = amax*1.1;
                    ctx->jmax_increase_count++;
                    jmax[0] *= 2.0;
                    jmax[1] *= 2.0;
                    jmax[2] *= 2.0;

                    //  TODO: valeur à ajuster, avant: 1.1...
                    //  1 -> stdout
                    //  2 -> stderr
                    if ((u & 16UL) != 0UL) {
                        printf("WARNING: (Jerk) Increasing jmax to [%f,%f,%f]\n", jmax[0], jmax[1],
                               jmax[2]);
                        fflush(stdout);
                    }

                    max_increase--;
                }
            }

            if (!c_success) {
                Coeff.set_size(0, 0);
                b_NCoeff = 0;
            } else {
                int i13;
                double u_vec_tilda;
                double c;
                double d;
                double z1_idx_0;
                double z1_idx_1;
                double b_b_idx_0;
                double b_idx_1;
                double n;
                int BasisVal_idx_0;

                //
                //  tic
                //  Coeff1 = linprog(f, Atot, btot, Aeq, beq, [], [], options);
                //  toc
                //
                //  1 -> stdout
                //  2 -> stderr
                if (u2 != 0UL) {
                    printf("Coeff3 = ");
                    fflush(stdout);
                }

                i13 = BasisVal.size(1);
                for (int d_k = 0; d_k < i13; d_k++) {
                    //  1 -> stdout
                    //  2 -> stderr
                    if (u2 != 0UL) {
                        printf("%.4f ", Coeff2[d_k]);
                        fflush(stdout);
                    }
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u2 != 0UL) {
                    printf("\n");
                    fflush(stdout);
                }

                //
                //
                //  import splines.*
                //
                //  Ntot = 0;
                //  for k = 1:Ncrv
                //      Ntot = Ntot + size(u_cell{k}, 2);
                //  end
                //  v_norm = [];
                //  a = [];
                //  j = [];
                //
                //      qSpl = Function(Bl, Coeff(:, k));
                //
                //  coder.cstructname(CurvStruct, 'CurvStruct')
                //
                //
                r1D[0] = 0.0;
                r2D[0] = 0.0;
                r1D[1] = 0.0;
                r2D[1] = 0.0;
                r1D[2] = 0.0;
                r2D[2] = 0.0;
                u_vec_tilda = CurvStructs0[0].a_param + CurvStructs0[0].b_param;
                switch (CurvStructs0[0].Type) {
                  case CurveType_Line:
                    //  line (G01)
                    //
                    //  parametrization of a straight line between P0 and P1
                    //
                    //
                    r1D[0] = CurvStructs0[0].P1[0] - CurvStructs0[0].P0[0];
                    r1D[1] = CurvStructs0[0].P1[1] - CurvStructs0[0].P0[1];
                    r1D[2] = CurvStructs0[0].P1[2] - CurvStructs0[0].P0[2];

                    //
                    break;

                  case CurveType_Helix:
                    //  arc of circle / helix (G02, G03)
                    b_EvalHelix(CurvStructs0[0].P0, CurvStructs0[0].P1, CurvStructs0[0].evec,
                                CurvStructs0[0].theta, CurvStructs0[0].pitch, u_vec_tilda, unusedU0,
                                r1D, r2D, r3D);
                    break;

                  case CurveType_TransP5:
                    //  polynomial transition
                    b_EvalTransP5(CurvStructs0[0].CoeffP5, u_vec_tilda, unusedU0, r1D, r2D, r3D);
                    break;

                  case CurveType_Spline:
                    {
                        int i_loop_ub;
                        int j_loop_ub;
                        int k_loop_ub;

                        //  BSpline
                        ctx->q_splines.get(CurvStructs0[0].sp_index, (&expl_temp));
                        Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
                        i_loop_ub = expl_temp.sp.CoeffX.size(1);
                        for (int i17 = 0; i17 < i_loop_ub; i17++) {
                            Spline_sp_CoeffX[i17] = expl_temp.sp.CoeffX[i17];
                        }

                        Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
                        j_loop_ub = expl_temp.sp.CoeffY.size(1);
                        for (int i18 = 0; i18 < j_loop_ub; i18++) {
                            Spline_sp_CoeffY[i18] = expl_temp.sp.CoeffY[i18];
                        }

                        Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
                        k_loop_ub = expl_temp.sp.CoeffZ.size(1);
                        for (int i19 = 0; i19 < k_loop_ub; i19++) {
                            Spline_sp_CoeffZ[i19] = expl_temp.sp.CoeffZ[i19];
                        }

                        b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, u_vec_tilda,
                                           &r0Dx, &r1Dx, &r2Dx, &r3Dx);
                        b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, u_vec_tilda,
                                           &r0Dy, &r1Dy, &r2Dy, &r3Dy);
                        b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, u_vec_tilda,
                                           &r0Dz, &r1Dz, &r2Dz, &r3Dz);
                        r1D[0] = r1Dx;
                        r1D[1] = r1Dy;
                        r1D[2] = r1Dz;
                        r2D[0] = r2Dx;
                        r2D[1] = r2Dy;
                        r2D[2] = r2Dz;
                    }
                    break;

                  default:
                    for (int i16 = 0; i16 < 30; i16++) {
                        message[i16] = cv[i16];
                    }

                    c_assert_(&message[0]);
                    break;
                }

                c = std::pow(CurvStructs0[0].a_param, 2.0);
                d = CurvStructs0[0].a_param * r1D[0];
                r1D[0] = d;
                r2D[0] *= c;
                z1_idx_0 = std::pow(d, 2.0);
                d = CurvStructs0[0].a_param * r1D[1];
                r1D[1] = d;
                r2D[1] *= c;
                z1_idx_1 = std::pow(d, 2.0);
                d = CurvStructs0[0].a_param * r1D[2];
                r2D[2] *= c;

                //  norm
                //
                //      q_val   = qSpl.fast_eval(u_vec);
                //      qD_val  = qSpl.derivative.fast_eval(u_vec);
                //      qDD_val = qSpl.derivative(2).fast_eval(u_vec);
                //  TODO: Optimize this with a single call to eval, and maybe a basis
                //  precompute?
                if (CurvStructs0[0].zspdmode == ZSpdMode_ZN) {
                    double b_t;
                    b_t = std::pow(6.0 / CurvStructs0[0].ConstJerk, 0.33333333333333331);
                    q_val = std::pow(CurvStructs0[0].ConstJerk * std::pow(b_t, 2.0) / 2.0, 2.0);
                    qD_val = 2.0 * CurvStructs0[0].ConstJerk * b_t;
                } else if (CurvStructs0[0].zspdmode == ZSpdMode_NZ) {
                    double b_t;
                    b_t = std::pow(0.0 / CurvStructs0[0].ConstJerk, 0.33333333333333331);
                    q_val = std::pow(CurvStructs0[0].ConstJerk * std::pow(b_t, 2.0) / 2.0, 2.0);
                    qD_val = -2.0 * CurvStructs0[0].ConstJerk * b_t;
                } else {
                    if (!(CurvStructs0[0].zspdmode == ZSpdMode_ZZ)) {
                        int l_loop_ub;

                        //  ZSpdMode.NN
                        q_val = 1.0;
                        l_loop_ub = BasisVal.size(1);
                        b_Coeff2.set_size(BasisVal.size(1));
                        for (int i20 = 0; i20 < l_loop_ub; i20++) {
                            b_Coeff2[i20] = Coeff2[i20];
                        }

                        b_bspline_eval(Bl_handle, b_Coeff2, &q_val, &qD_val, &v3);
                    }
                }

                b_b_idx_0 = r1D[0] * qD_val;
                b_idx_1 = r1D[1] * qD_val;

                // zeros(3, size(tmp2, 2));
                e_EvalCurvStruct(&ctx->q_splines, CurvStructs0[0].Type, CurvStructs0[0].P0,
                                 CurvStructs0[0].P1, CurvStructs0[0].evec, CurvStructs0[0].theta,
                                 CurvStructs0[0].pitch, CurvStructs0[0].CoeffP5, CurvStructs0[0].
                                 sp_index, CurvStructs0[0].a_param, CurvStructs0[0].b_param,
                                 unusedU1, r1D);
                n = std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0));

                //  unit tangential vector
                ctx->at_0 = ((r2D[0] * q_val + 0.5 * b_b_idx_0) * (r1D[0] / n) + (r2D[1] * q_val +
                              0.5 * b_idx_1) * (r1D[1] / n)) + (r2D[2] * q_val + 0.5 * (d * qD_val))
                    * (r1D[2] / n);

                //  tangential acceleration at the end of first piece in horizon
                ctx->v_0 = std::sqrt((z1_idx_0 + z1_idx_1) + std::pow(d, 2.0)) * std::sqrt(q_val);

                //  Coeff = Coeff3(:, 1);
                //  Coeff = zeros(FeedoptLimits.MaxNCoeff, FeedoptLimits.MaxNHorz);
                //  coder.varsize('Coeff', [Inf, Inf], [1,1]);
                BasisVal_idx_0 = BasisVal.size(1);
                Coeff.set_size(BasisVal.size(1), varargin_2);
                for (int i21 = 0; i21 < varargin_2; i21++) {
                    for (int i22 = 0; i22 < BasisVal_idx_0; i22++) {
                        Coeff[i22 + Coeff.size(0) * i21] = Coeff2[i22 + BasisVal_idx_0 * i21];
                    }
                }

                b_NCoeff = BasisVal.size(1);
            }
        }

        *NCoeff = b_NCoeff;
        *success = c_success;
    }

    //
    // Arguments    : const double r0D0[3]
    //                const double r0D1[3]
    //                const double r0D2[3]
    //                const double r1D0[3]
    //                const double r1D1[3]
    //                const double r1D2[3]
    //                double p5_3D[6][3]
    //                int *status
    //                double *alpha0
    //                double *alpha1
    // Return Type  : void
    //
    static void G2_Hermite_Interpolation(const double r0D0[3], const double r0D1[3], const double
        r0D2[3], const double r1D0[3], const double r1D1[3], const double r1D2[3], double p5_3D[6][3],
        int *status, double *alpha0, double *alpha1)
    {
        double t0[3];
        double n0[3];
        double kappa0;
        double t1[3];
        double n1[3];
        double kappa1;
        double CoefPS[16];
        bool guard1 = false;
        creal_T alpha1_v[3];
        double A[2][2];
        creal_T b_alpha1_v[9];
        creal_T alpha0_v[3];
        double dv[10];
        double B[2];
        double dv1[10];
        double dv2[4];
        int alpha1_t_size[1];
        double alpha1_t_data[9];
        double alpha0_t_data[9];
        int alpha0_t_size[1];
        int b_alpha0_t_size[1];
        double a;
        double b_a;
        bool b_alpha0_t_data[9];
        int tmp_data[9];
        int tmp_size[1];
        int Idx_data[9];
        signed char b_tmp_data[3];
        int CostInt_size[1];
        double b_r0D0[6][3];
        static const signed char b_b[6] = { -6, 15, -10, 0, 0, 1 };

        static const signed char c_b[6] = { -3, 8, -6, 0, 1, 0 };

        static const double d_b[6] = { -0.5, 1.5, -1.5, 0.5, 0.0, 0.0 };

        double CostInt_data[9];
        double b_r1D0[6][3];
        static const signed char e_b[6] = { 6, -15, 10, 0, 0, 0 };

        double beta0_u_data[9];
        static const signed char f_b[6] = { -3, 7, -4, 0, 0, 0 };

        static const double g_b[6] = { 0.5, -1.0, 0.5, 0.0, 0.0, 0.0 };

        double z1_data[9];
        double b_z1_data[9];
        double beta1_u_data[9];
        int c_alpha0_t_size[1];
        int b_alpha1_t_size[1];
        double unusedU2;
        int iindx;
        bool c_alpha0_t_data[3];
        bool b_alpha1_t_data[3];
        double unusedU0;
        int b_iindx;
        double unusedU1;
        int c_iindx;

        //
        //      This file is part of the Optimal G^2 Hermite Interpolation Software.
        //
        //      Copyright (C) 2017-2019 Raoul Herzog, Philippe Blanc
        //                              mecatronYx group at HEIG-VD
        //                              University of Applied Sciences Western Switzerland
        //                              CH-1401 Yverdon-les-Bains
        //                              All rights reserved.
        //
        //      This is free software; you can redistribute it and/or
        //      modify it under the terms of the GNU Lesser General Public
        //      License as published by the Free Software Foundation; either
        //      version 3 of the License, or (at your option) any later version.
        //
        //      This software is distributed in the hope that it will be useful,
        //      but WITHOUT ANY WARRANTY; without even the implied warranty of
        //      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
        //      Lesser General Public License for more details.
        //
        //      You should have received a copy of the GNU Lesser General Public
        //      License along with this software; if not, write to the Free Software
        //      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
        //
        //
        //  [p5_3D, alpha0, alpha1] = G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2)
        //
        //  Compute an optimal trajectory in R^3, connecting the point r0 to r1 with
        //  C^2 smoothness while minimizing the integral of the norm of the third
        //  derivative.
        *status = 1;

        //  default success
        for (int i = 0; i < 6; i++) {
            p5_3D[i][0] = 0.0;
            p5_3D[i][1] = 0.0;
            p5_3D[i][2] = 0.0;
        }

        *alpha0 = 0.0;
        *alpha1 = 0.0;

        //  compute Frenet frame
        CalcFrenet(r0D1, r0D2, t0, n0, &kappa0);
        CalcFrenet(r1D1, r1D2, t1, n1, &kappa1);

        //  reduce to polynomial system of 2 equations in unknowns alpha0 and alpha1
        //  p1   = (a1*alpha1+a0)*alpha0^2 + (b1*alpha1+b0)*alpha0 +
        //          c3*alpha1^3+c2*alpha1^2+c1*alpha1+c0;
        //  p2   = (d1*alpha0+d0)*alpha1^2 + (e1*alpha0+e0)*alpha1 +
        //          f3*alpha0^3+f2*alpha0^2+f1*alpha0+f0;
        //
        //  compute CoefPS = [a1 a0 b1 b0 c3 c2 c1 c0 d1 d0 e1 e0 f3 f2 f1 f0]
        CoefPolySys(r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, CoefPS);

        //
        //
        guard1 = false;
        if ((kappa0 == 0.0) && (kappa1 == 0.0)) {
            int r1;
            int r2;
            double a21;
            double X_idx_1;
            double X_idx_0;

            //  degenerated case where the polynomial system degenerates to a linear one
            //
            //
            A[0][0] = CoefPS[3];
            A[1][0] = CoefPS[6];
            A[0][1] = CoefPS[14];
            A[1][1] = CoefPS[11];
            B[0] = -CoefPS[7];
            B[1] = -CoefPS[15];
            if (std::abs(CoefPS[14]) > std::abs(CoefPS[3])) {
                r1 = 1;
                r2 = 0;
            } else {
                r1 = 0;
                r2 = 1;
            }

            a21 = A[0][r2] / A[0][r1];
            X_idx_1 = (B[r2] - B[r1] * a21) / (A[1][r2] - a21 * A[1][r1]);
            X_idx_0 = (B[r1] - X_idx_1 * A[1][r1]) / A[0][r1];

            //  resolution of linear system
            *alpha0 = X_idx_0;
            *alpha1 = X_idx_1;
            if ((X_idx_0 > 0.0) && (X_idx_1 > 0.0)) {
                Calc_beta0_beta1(X_idx_0, X_idx_1, r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, &a,
                                 &b_a);
                guard1 = true;
            }
        } else if (kappa0 == 0.0) {
            int b_trueCount;
            bool unnamed_idx_2;
            bool unnamed_idx_0;
            bool unnamed_idx_1;
            int Idx_size_idx_0;
            int b_partialTrueCount;
            int f_loop_ub;
            int h_loop_ub;

            //  compute resultant of the polynomial system
            //
            alpha1_v[0].re = 0.0;
            alpha1_v[0].im = 0.0;
            alpha1_v[1].re = 0.0;
            alpha1_v[1].im = 0.0;
            alpha1_v[2].re = 0.0;
            alpha1_v[2].im = 0.0;
            dv2[0] = CoefPS[3] * CoefPS[15] - CoefPS[7] * CoefPS[14];
            dv2[1] = (CoefPS[3] * CoefPS[11] + CoefPS[2] * CoefPS[15]) - CoefPS[6] * CoefPS[14];
            dv2[2] = (CoefPS[3] * CoefPS[9] + CoefPS[2] * CoefPS[11]) - CoefPS[5] * CoefPS[14];
            dv2[3] = CoefPS[2] * CoefPS[9] - CoefPS[4] * CoefPS[14];
            c_roots(&dv2[0], &alpha1_v[0], 4);

            //  all roots of 3th degree polynomial in alpha1
            b_trueCount = 0;
            unnamed_idx_2 = (std::abs(alpha1_v[0].im) < 1.0E-11);
            unnamed_idx_0 = unnamed_idx_2;
            if (unnamed_idx_2 && (alpha1_v[0].re > 0.0)) {
                b_trueCount = 1;
            }

            unnamed_idx_2 = (std::abs(alpha1_v[1].im) < 1.0E-11);
            unnamed_idx_1 = unnamed_idx_2;
            if (unnamed_idx_2 && (alpha1_v[1].re > 0.0)) {
                b_trueCount++;
            }

            unnamed_idx_2 = (std::abs(alpha1_v[2].im) < 1.0E-11);
            if (unnamed_idx_2 && (alpha1_v[2].re > 0.0)) {
                b_trueCount++;
            }

            b_partialTrueCount = 0;
            if (unnamed_idx_0 && (alpha1_v[0].re > 0.0)) {
                b_tmp_data[0] = 1;
                b_partialTrueCount = 1;
            }

            if (unnamed_idx_1 && (alpha1_v[1].re > 0.0)) {
                b_tmp_data[b_partialTrueCount] = 2;
                b_partialTrueCount++;
            }

            if (unnamed_idx_2 && (alpha1_v[2].re > 0.0)) {
                b_tmp_data[b_partialTrueCount] = 3;
            }

            for (int i4 = 0; i4 < b_trueCount; i4++) {
                alpha1_t_data[i4] = alpha1_v[b_tmp_data[i4] - 1].re;
            }

            //  retain only positive real roots
            if ((std::abs(CoefPS[2]) < 1.0E-11) && (std::abs(CoefPS[3]) < 1.0E-11)) {
                for (int c_k = 0; c_k < b_trueCount; c_k++) {
                    z1_data[c_k] = std::pow(alpha1_t_data[c_k], 2.0);
                }

                alpha0_t_size[0] = b_trueCount;
                for (int i7 = 0; i7 < b_trueCount; i7++) {
                    alpha0_t_data[i7] = -((CoefPS[9] * z1_data[i7] + CoefPS[11] * alpha1_t_data[i7])
                                          + CoefPS[15]) / CoefPS[14];
                }
            } else {
                for (int b_k = 0; b_k < b_trueCount; b_k++) {
                    z1_data[b_k] = std::pow(alpha1_t_data[b_k], 3.0);
                }

                for (int f_k = 0; f_k < b_trueCount; f_k++) {
                    b_z1_data[f_k] = std::pow(alpha1_t_data[f_k], 2.0);
                }

                alpha0_t_size[0] = b_trueCount;
                for (int i9 = 0; i9 < b_trueCount; i9++) {
                    alpha0_t_data[i9] = -(((CoefPS[4] * z1_data[i9] + CoefPS[5] * b_z1_data[i9]) +
                                           CoefPS[6] * alpha1_t_data[i9]) + CoefPS[7]) / (CoefPS[2] *
                        alpha1_t_data[i9] + CoefPS[3]);
                }
            }

            c_alpha0_t_size[0] = alpha0_t_size[0];
            f_loop_ub = alpha0_t_size[0];
            for (int i11 = 0; i11 < f_loop_ub; i11++) {
                c_alpha0_t_data[i11] = (alpha0_t_data[i11] > 0.0);
            }

            c_eml_find(c_alpha0_t_data, c_alpha0_t_size, tmp_data, tmp_size);
            Idx_size_idx_0 = tmp_size[0];
            h_loop_ub = tmp_size[0];
            if (0 <= h_loop_ub - 1) {
                std::memcpy(&Idx_data[0], &tmp_data[0], h_loop_ub * sizeof(int));
            }

            if (tmp_size[0] <= 0) {
                *status = 3;
            } else {
                // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
                if (tmp_size[0] > 1) {
                    int j_loop_ub;
                    int l_loop_ub;
                    int n_loop_ub;
                    CostInt_size[0] = static_cast<signed char>(tmp_size[0]);
                    j_loop_ub = static_cast<signed char>(tmp_size[0]);
                    if (0 <= j_loop_ub - 1) {
                        std::memset(&CostInt_data[0], 0, j_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    l_loop_ub = static_cast<signed char>(tmp_size[0]);
                    if (0 <= l_loop_ub - 1) {
                        std::memset(&beta0_u_data[0], 0, l_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    n_loop_ub = static_cast<signed char>(tmp_size[0]);
                    if (0 <= n_loop_ub - 1) {
                        std::memset(&beta1_u_data[0], 0, n_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    for (int i_k = 0; i_k < Idx_size_idx_0; i_k++) {
                        Calc_beta0_beta1(alpha0_t_data[Idx_data[i_k] - 1],
                                         alpha1_t_data[Idx_data[i_k] - 1], r0D0, t0, n0, kappa0,
                                         r1D0, t1, n1, kappa1, &beta0_u_data[i_k], &beta1_u_data[i_k]);
                        CostInt_data[i_k] = EvalCostIntegral(alpha0_t_data[Idx_data[i_k] - 1],
                            beta0_u_data[i_k], alpha1_t_data[Idx_data[i_k] - 1], beta1_u_data[i_k],
                            r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1);
                    }

                    int b_alpha0_tmp;
                    minimum(CostInt_data, CostInt_size, &unusedU0, &b_iindx);
                    b_alpha0_tmp = Idx_data[b_iindx - 1] - 1;
                    *alpha0 = alpha0_t_data[b_alpha0_tmp];
                    *alpha1 = alpha1_t_data[b_alpha0_tmp];
                    a = beta0_u_data[b_iindx - 1];
                    b_a = beta1_u_data[b_iindx - 1];
                } else {
                    *alpha0 = alpha0_t_data[Idx_data[0] - 1];
                    *alpha1 = alpha1_t_data[Idx_data[0] - 1];
                    Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                     r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, &a, &b_a);
                }

                guard1 = true;
            }
        } else if (kappa1 == 0.0) {
            int c_trueCount;
            bool unnamed_idx_0;
            bool b_unnamed_idx_2;
            bool unnamed_idx_1;
            int Idx_size_idx_0;
            int c_partialTrueCount;
            int g_loop_ub;
            int i_loop_ub;

            //
            //  compute resultant of the polynomial system
            //
            alpha0_v[0].re = 0.0;
            alpha0_v[0].im = 0.0;
            alpha0_v[1].re = 0.0;
            alpha0_v[1].im = 0.0;
            alpha0_v[2].re = 0.0;
            alpha0_v[2].im = 0.0;
            dv2[0] = CoefPS[6] * CoefPS[15] - CoefPS[7] * CoefPS[11];
            dv2[1] = (CoefPS[6] * CoefPS[14] - CoefPS[7] * CoefPS[10]) - CoefPS[3] * CoefPS[11];
            dv2[2] = (CoefPS[6] * CoefPS[13] - CoefPS[3] * CoefPS[10]) - CoefPS[1] * CoefPS[11];
            dv2[3] = CoefPS[6] * CoefPS[12] - CoefPS[1] * CoefPS[10];
            c_roots(&dv2[0], &alpha0_v[0], 4);

            //  all roots of 3th degree polynomial in alpha0
            c_trueCount = 0;
            b_unnamed_idx_2 = (std::abs(alpha0_v[0].im) < 1.0E-11);
            unnamed_idx_0 = b_unnamed_idx_2;
            if (b_unnamed_idx_2 && (alpha0_v[0].re > 0.0)) {
                c_trueCount = 1;
            }

            b_unnamed_idx_2 = (std::abs(alpha0_v[1].im) < 1.0E-11);
            unnamed_idx_1 = b_unnamed_idx_2;
            if (b_unnamed_idx_2 && (alpha0_v[1].re > 0.0)) {
                c_trueCount++;
            }

            b_unnamed_idx_2 = (std::abs(alpha0_v[2].im) < 1.0E-11);
            if (b_unnamed_idx_2 && (alpha0_v[2].re > 0.0)) {
                c_trueCount++;
            }

            c_partialTrueCount = 0;
            if (unnamed_idx_0 && (alpha0_v[0].re > 0.0)) {
                b_tmp_data[0] = 1;
                c_partialTrueCount = 1;
            }

            if (unnamed_idx_1 && (alpha0_v[1].re > 0.0)) {
                b_tmp_data[c_partialTrueCount] = 2;
                c_partialTrueCount++;
            }

            if (b_unnamed_idx_2 && (alpha0_v[2].re > 0.0)) {
                b_tmp_data[c_partialTrueCount] = 3;
            }

            for (int i5 = 0; i5 < c_trueCount; i5++) {
                alpha0_t_data[i5] = alpha0_v[b_tmp_data[i5] - 1].re;
            }

            //  retain only positive real roots
            if ((std::abs(CoefPS[10]) < 1.0E-11) && (std::abs(CoefPS[11]) < 1.0E-11)) {
                for (int e_k = 0; e_k < c_trueCount; e_k++) {
                    z1_data[e_k] = std::pow(alpha0_t_data[e_k], 2.0);
                }

                alpha1_t_size[0] = c_trueCount;
                for (int i8 = 0; i8 < c_trueCount; i8++) {
                    alpha1_t_data[i8] = -((CoefPS[1] * z1_data[i8] + CoefPS[3] * alpha0_t_data[i8])
                                          + CoefPS[7]) / CoefPS[6];
                }
            } else {
                for (int d_k = 0; d_k < c_trueCount; d_k++) {
                    z1_data[d_k] = std::pow(alpha0_t_data[d_k], 3.0);
                }

                for (int g_k = 0; g_k < c_trueCount; g_k++) {
                    b_z1_data[g_k] = std::pow(alpha0_t_data[g_k], 2.0);
                }

                alpha1_t_size[0] = c_trueCount;
                for (int i10 = 0; i10 < c_trueCount; i10++) {
                    alpha1_t_data[i10] = -(((CoefPS[12] * z1_data[i10] + CoefPS[13] * b_z1_data[i10])
                                            + CoefPS[14] * alpha0_t_data[i10]) + CoefPS[15]) /
                        (CoefPS[10] * alpha0_t_data[i10] + CoefPS[11]);
                }
            }

            b_alpha1_t_size[0] = alpha1_t_size[0];
            g_loop_ub = alpha1_t_size[0];
            for (int i12 = 0; i12 < g_loop_ub; i12++) {
                b_alpha1_t_data[i12] = (alpha1_t_data[i12] > 0.0);
            }

            c_eml_find(b_alpha1_t_data, b_alpha1_t_size, tmp_data, tmp_size);
            Idx_size_idx_0 = tmp_size[0];
            i_loop_ub = tmp_size[0];
            if (0 <= i_loop_ub - 1) {
                std::memcpy(&Idx_data[0], &tmp_data[0], i_loop_ub * sizeof(int));
            }

            //
            if (tmp_size[0] <= 0) {
                *status = 4;
            } else {
                // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
                if (tmp_size[0] > 1) {
                    int k_loop_ub;
                    int m_loop_ub;
                    int o_loop_ub;
                    CostInt_size[0] = static_cast<signed char>(tmp_size[0]);
                    k_loop_ub = static_cast<signed char>(tmp_size[0]);
                    if (0 <= k_loop_ub - 1) {
                        std::memset(&CostInt_data[0], 0, k_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    m_loop_ub = static_cast<signed char>(tmp_size[0]);
                    if (0 <= m_loop_ub - 1) {
                        std::memset(&beta0_u_data[0], 0, m_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    o_loop_ub = static_cast<signed char>(tmp_size[0]);
                    if (0 <= o_loop_ub - 1) {
                        std::memset(&beta1_u_data[0], 0, o_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    for (int j_k = 0; j_k < Idx_size_idx_0; j_k++) {
                        Calc_beta0_beta1(alpha0_t_data[Idx_data[j_k] - 1],
                                         alpha1_t_data[Idx_data[j_k] - 1], r0D0, t0, n0, kappa0,
                                         r1D0, t1, n1, kappa1, &beta0_u_data[j_k], &beta1_u_data[j_k]);
                        CostInt_data[j_k] = EvalCostIntegral(alpha0_t_data[Idx_data[j_k] - 1],
                            beta0_u_data[j_k], alpha1_t_data[Idx_data[j_k] - 1], beta1_u_data[j_k],
                            r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1);
                    }

                    int c_alpha0_tmp;
                    minimum(CostInt_data, CostInt_size, &unusedU1, &c_iindx);
                    c_alpha0_tmp = Idx_data[c_iindx - 1] - 1;
                    *alpha0 = alpha0_t_data[c_alpha0_tmp];
                    *alpha1 = alpha1_t_data[c_alpha0_tmp];
                    a = beta0_u_data[c_iindx - 1];
                    b_a = beta1_u_data[c_iindx - 1];
                } else {
                    *alpha0 = alpha0_t_data[Idx_data[0] - 1];
                    *alpha1 = alpha1_t_data[Idx_data[0] - 1];
                    Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                     r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, &a, &b_a);
                }

                //
                guard1 = true;
            }
        } else {
            int trueCount;
            int partialTrueCount;
            int loop_ub;
            int Idx_size_idx_0;
            int b_loop_ub;

            //  compute resultant of the polynomial system
            //
            std::memset(&b_alpha1_v[0], 0, 9U * sizeof(creal_T));
            CharPolyAlpha1(CoefPS, dv);
            for (int i1 = 0; i1 < 10; i1++) {
                dv1[i1] = dv[9 - i1];
            }

            c_roots(&dv1[0], &b_alpha1_v[0], 10);

            //  all roots of 9th degree polynomial in alpha1
            trueCount = 0;
            partialTrueCount = 0;
            for (int k = 0; k < 9; k++) {
                bool b;
                b = (std::abs(b_alpha1_v[k].im) < 1.0E-11);
                if (b && (b_alpha1_v[k].re > 0.0)) {
                    trueCount++;
                    alpha1_t_data[partialTrueCount] = b_alpha1_v[k].re;
                    partialTrueCount++;
                }
            }

            alpha1_t_size[0] = trueCount;

            //  retain only positive real roots
            //  compute corresponding values of alpha0
            CalcAlpha0(alpha1_t_data, alpha1_t_size, CoefPS, alpha0_t_data, alpha0_t_size);

            //
            b_alpha0_t_size[0] = alpha0_t_size[0];
            loop_ub = alpha0_t_size[0];
            for (int i2 = 0; i2 < loop_ub; i2++) {
                b_alpha0_t_data[i2] = (alpha0_t_data[i2] > 0.0);
            }

            c_eml_find(b_alpha0_t_data, b_alpha0_t_size, tmp_data, tmp_size);
            Idx_size_idx_0 = tmp_size[0];
            b_loop_ub = tmp_size[0];
            if (0 <= b_loop_ub - 1) {
                std::memcpy(&Idx_data[0], &tmp_data[0], b_loop_ub * sizeof(int));
            }

            //
            if (tmp_size[0] <= 0) {
                *status = 5;
            } else {
                // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
                if (tmp_size[0] > 1) {
                    int c_loop_ub;
                    int d_loop_ub;
                    int e_loop_ub;
                    CostInt_size[0] = static_cast<signed char>(tmp_size[0]);
                    c_loop_ub = static_cast<signed char>(tmp_size[0]);
                    if (0 <= c_loop_ub - 1) {
                        std::memset(&CostInt_data[0], 0, c_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    d_loop_ub = static_cast<signed char>(tmp_size[0]);
                    if (0 <= d_loop_ub - 1) {
                        std::memset(&beta0_u_data[0], 0, d_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    e_loop_ub = static_cast<signed char>(tmp_size[0]);
                    if (0 <= e_loop_ub - 1) {
                        std::memset(&beta1_u_data[0], 0, e_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    for (int h_k = 0; h_k < Idx_size_idx_0; h_k++) {
                        Calc_beta0_beta1(alpha0_t_data[Idx_data[h_k] - 1],
                                         alpha1_t_data[Idx_data[h_k] - 1], r0D0, t0, n0, kappa0,
                                         r1D0, t1, n1, kappa1, &beta0_u_data[h_k], &beta1_u_data[h_k]);
                        CostInt_data[h_k] = EvalCostIntegral(alpha0_t_data[Idx_data[h_k] - 1],
                            beta0_u_data[h_k], alpha1_t_data[Idx_data[h_k] - 1], beta1_u_data[h_k],
                            r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1);
                    }

                    int alpha0_tmp;
                    minimum(CostInt_data, CostInt_size, &unusedU2, &iindx);
                    alpha0_tmp = Idx_data[iindx - 1] - 1;
                    *alpha0 = alpha0_t_data[alpha0_tmp];
                    *alpha1 = alpha1_t_data[alpha0_tmp];
                    a = beta0_u_data[iindx - 1];
                    b_a = beta1_u_data[iindx - 1];
                } else {
                    *alpha0 = alpha0_t_data[Idx_data[0] - 1];
                    *alpha1 = alpha1_t_data[Idx_data[0] - 1];
                    Calc_beta0_beta1(alpha0_t_data[Idx_data[0] - 1], alpha1_t_data[Idx_data[0] - 1],
                                     r0D0, t0, n0, kappa0, r1D0, t1, n1, kappa1, &a, &b_a);
                }

                guard1 = true;
            }
        }

        if (guard1) {
            double a_tmp;
            double c_a;
            double b_a_tmp;
            double d_a;
            double a_idx_0;
            double a_idx_1;
            double a_idx_2;

            //
            //  Hermite basis
            //  evaluate coefficients as sum of basis functions
            a_tmp = std::pow(*alpha0, 2.0);
            c_a = kappa0 * a_tmp;
            b_a_tmp = std::pow(*alpha1, 2.0);
            d_a = kappa1 * b_a_tmp;
            a_idx_0 = a * t0[0] + c_a * n0[0];
            a_idx_1 = a * t0[1] + c_a * n0[1];
            a_idx_2 = a * t0[2] + c_a * n0[2];
            for (int i3 = 0; i3 < 6; i3++) {
                b_r0D0[i3][0] = (r0D0[0] * static_cast<double>(b_b[i3]) + *alpha0 * t0[0] *
                                 static_cast<double>(c_b[i3])) + a_idx_0 * d_b[i3];
                b_r1D0[i3][0] = r1D0[0] * static_cast<double>(e_b[i3]);
                b_r0D0[i3][1] = (r0D0[1] * static_cast<double>(b_b[i3]) + *alpha0 * t0[1] *
                                 static_cast<double>(c_b[i3])) + a_idx_1 * d_b[i3];
                b_r1D0[i3][1] = r1D0[1] * static_cast<double>(e_b[i3]);
                b_r0D0[i3][2] = (r0D0[2] * static_cast<double>(b_b[i3]) + *alpha0 * t0[2] *
                                 static_cast<double>(c_b[i3])) + a_idx_2 * d_b[i3];
                b_r1D0[i3][2] = r1D0[2] * static_cast<double>(e_b[i3]);
            }

            a_idx_0 = b_a * t1[0] + d_a * n1[0];
            a_idx_1 = b_a * t1[1] + d_a * n1[1];
            a_idx_2 = b_a * t1[2] + d_a * n1[2];
            for (int i6 = 0; i6 < 6; i6++) {
                p5_3D[i6][0] = ((b_r0D0[i6][0] + b_r1D0[i6][0]) + *alpha1 * t1[0] * static_cast<
                                double>(f_b[i6])) + a_idx_0 * g_b[i6];
                p5_3D[i6][1] = ((b_r0D0[i6][1] + b_r1D0[i6][1]) + *alpha1 * t1[1] * static_cast<
                                double>(f_b[i6])) + a_idx_1 * g_b[i6];
                p5_3D[i6][2] = ((b_r0D0[i6][2] + b_r1D0[i6][2]) + *alpha1 * t1[2] * static_cast<
                                double>(f_b[i6])) + a_idx_2 * g_b[i6];
            }

            //  last cross check ...
            //
            if ((std::abs((((((CoefPS[0] * *alpha1 + CoefPS[1]) * a_tmp + (CoefPS[2] * *alpha1 +
                       CoefPS[3]) * *alpha0) + CoefPS[4] * std::pow(*alpha1, 3.0)) + CoefPS[5] *
                            b_a_tmp) + CoefPS[6] * *alpha1) + CoefPS[7]) >= 1.0E-7) || (std::abs
                    ((((((CoefPS[8] * *alpha0 + CoefPS[9]) * b_a_tmp + (CoefPS[10] * *alpha0 +
                       CoefPS[11]) * *alpha1) + CoefPS[12] * std::pow(*alpha0, 3.0)) + CoefPS[13] *
                       a_tmp) + CoefPS[14] * *alpha0) + CoefPS[15]) >= 1.0E-7)) {
                *status = 6;
            }
        }
    }

    //
    // Arguments    : const queue_coder *ctx_q_splines
    //                const double ctx_cfg_amax[3]
    //                const double ctx_cfg_jmax[3]
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double CurvStruct_CoeffP5[6][3]
    //                int CurvStruct_sp_index
    //                double CurvStruct_FeedRate
    //                double CurvStruct_a_param
    //                double CurvStruct_b_param
    // Return Type  : double
    //
    static double GetCurvMaxFeedrate(const queue_coder *ctx_q_splines, const double ctx_cfg_amax[3],
        const double ctx_cfg_jmax[3], CurveType CurvStruct_Type, const double CurvStruct_P0[3],
        const double CurvStruct_P1[3], const double CurvStruct_evec[3], double CurvStruct_theta,
        double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index,
        double CurvStruct_FeedRate, double CurvStruct_a_param, double CurvStruct_b_param)
    {
        double Feedrate;
        double unusedU0[10][3];
        double r1D[10][3];
        double r2D[10][3];
        double r3D[10][3];
        double y[10];
        double d;
        double z1[10][3];
        double d2;
        double d4;
        double A[3];
        double r3t[10][3];
        double d10;
        double d11;
        double d13;
        double J[3];
        int trueCount;
        int partialTrueCount;
        signed char tmp_data[3];
        double x_data[9];
        double y_data[9];
        int b_trueCount;
        double z_data[9];
        int b_partialTrueCount;
        signed char b_tmp_data[3];
        double b_z_data[9];

        //  rdot = r1D * u1d
        //  rdot'*rdot = r1D'*r1D * u1d
        //  ConstantFeedrate = r1D'*r1D * u1d     (1)
        i_EvalCurvStruct(ctx_q_splines, CurvStruct_Type, CurvStruct_P0, CurvStruct_P1,
                         CurvStruct_evec, CurvStruct_theta, CurvStruct_pitch, CurvStruct_CoeffP5,
                         CurvStruct_sp_index, CurvStruct_a_param, CurvStruct_b_param, unusedU0, r1D,
                         r2D, r3D);

        //  from (1):
        for (int k = 0; k < 10; k++) {
            y[k] = (std::abs(r1D[k][0]) + std::abs(r1D[k][1])) + std::abs(r1D[k][2]);
        }

        //  u2d = 0;
        //  u3d = 0;
        //  + r1D*u2d
        //  + 3*r2D*u1d*u2d + r1d*u3d
        //  These 2 equations tell us that to obtain the values for other
        //  feedrates, they have to be multiplied by the scale.^2 and scale.^3
        for (int b_k = 0; b_k < 10; b_k++) {
            double d1;
            double d3;
            double d5;
            double d6;
            double d7;
            d1 = 1.0 / y[b_k];
            d3 = std::pow(d1, 2.0);
            d5 = r2D[b_k][0] * d3;
            d6 = r2D[b_k][1] * d3;
            d7 = r2D[b_k][2] * d3;
            d3 = std::pow(d1, 3.0);
            r3t[b_k][0] = r3D[b_k][0] * d3;
            z1[b_k][0] = std::abs(d5);
            r3t[b_k][1] = r3D[b_k][1] * d3;
            z1[b_k][1] = std::abs(d6);
            r3t[b_k][2] = r3D[b_k][2] * d3;
            z1[b_k][2] = std::abs(d7);
        }

        d = z1[0][0];
        d2 = z1[0][1];
        d4 = z1[0][2];
        for (int j = 0; j < 9; j++) {
            double d8;
            double d9;
            double d12;
            d8 = z1[j + 1][0];
            if (d < d8) {
                d = d8;
            }

            d9 = z1[j + 1][1];
            if (d2 < d9) {
                d2 = d9;
            }

            d12 = z1[j + 1][2];
            if (d4 < d12) {
                d4 = d12;
            }
        }

        A[2] = d4;
        A[1] = d2;
        A[0] = d;
        for (int c_k = 0; c_k < 10; c_k++) {
            z1[c_k][0] = std::abs(r3t[c_k][0]);
            z1[c_k][1] = std::abs(r3t[c_k][1]);
            z1[c_k][2] = std::abs(r3t[c_k][2]);
        }

        d10 = z1[0][0];
        d11 = z1[0][1];
        d13 = z1[0][2];
        for (int b_j = 0; b_j < 9; b_j++) {
            double d14;
            double d15;
            double d16;
            d14 = z1[b_j + 1][0];
            if (d10 < d14) {
                d10 = d14;
            }

            d15 = z1[b_j + 1][1];
            if (d11 < d15) {
                d11 = d15;
            }

            d16 = z1[b_j + 1][2];
            if (d13 < d16) {
                d13 = d16;
            }
        }

        J[2] = d13;
        J[1] = d11;
        J[0] = d10;
        trueCount = 0;
        if (d != 0.0) {
            trueCount = 1;
        }

        if (d2 != 0.0) {
            trueCount++;
        }

        if (d4 != 0.0) {
            trueCount++;
        }

        partialTrueCount = 0;
        if (d != 0.0) {
            tmp_data[0] = 1;
            partialTrueCount = 1;
        }

        if (d2 != 0.0) {
            tmp_data[partialTrueCount] = 2;
            partialTrueCount++;
        }

        if (d4 != 0.0) {
            tmp_data[partialTrueCount] = 3;
        }

        for (int i = 0; i < trueCount; i++) {
            x_data[i] = A[tmp_data[i] - 1];
        }

        for (int i1 = 0; i1 < trueCount; i1++) {
            y_data[i1] = ctx_cfg_amax[tmp_data[i1] - 1];
        }

        for (int i2 = 0; i2 < trueCount; i2++) {
            z_data[i2] = x_data[i2] / y_data[i2];
        }

        b_trueCount = 0;
        if (d10 != 0.0) {
            b_trueCount = 1;
        }

        if (d11 != 0.0) {
            b_trueCount++;
        }

        if (d13 != 0.0) {
            b_trueCount++;
        }

        b_partialTrueCount = 0;
        if (d10 != 0.0) {
            b_tmp_data[0] = 1;
            b_partialTrueCount = 1;
        }

        if (d11 != 0.0) {
            b_tmp_data[b_partialTrueCount] = 2;
            b_partialTrueCount++;
        }

        if (d13 != 0.0) {
            b_tmp_data[b_partialTrueCount] = 3;
        }

        for (int i3 = 0; i3 < b_trueCount; i3++) {
            x_data[i3] = J[b_tmp_data[i3] - 1];
        }

        for (int i4 = 0; i4 < b_trueCount; i4++) {
            y_data[i4] = ctx_cfg_jmax[b_tmp_data[i4] - 1];
        }

        for (int i5 = 0; i5 < b_trueCount; i5++) {
            b_z_data[i5] = x_data[i5] / y_data[i5];
        }

        if ((trueCount == 0) || (b_trueCount == 0)) {
            Feedrate = CurvStruct_FeedRate;
        } else {
            double a;
            double b_a;
            double varargin_1_idx_1;
            double ex_tmp;
            double c_ex;
            if (static_cast<signed char>(trueCount) <= 2) {
                if (static_cast<signed char>(trueCount) == 1) {
                    a = z_data[0];
                } else if (z_data[0] < z_data[1]) {
                    a = z_data[1];
                } else {
                    a = z_data[0];
                }
            } else {
                double ex;
                ex = z_data[0];
                if (z_data[0] < z_data[1]) {
                    ex = z_data[1];
                }

                if (ex < z_data[2]) {
                    ex = z_data[2];
                }

                a = ex;
            }

            if (b_trueCount <= 2) {
                if (b_trueCount == 1) {
                    b_a = b_z_data[0];
                } else if (b_z_data[0] < b_z_data[1]) {
                    b_a = b_z_data[1];
                } else {
                    b_a = b_z_data[0];
                }
            } else {
                double b_ex;
                b_ex = b_z_data[0];
                if (b_z_data[0] < b_z_data[1]) {
                    b_ex = b_z_data[1];
                }

                if (b_ex < b_z_data[2]) {
                    b_ex = b_z_data[2];
                }

                b_a = b_ex;
            }

            varargin_1_idx_1 = 1.0 / std::pow(b_a, 0.33333333333333331);
            ex_tmp = 1.0 / std::pow(a, 0.5);
            c_ex = ex_tmp;
            if (ex_tmp > varargin_1_idx_1) {
                c_ex = varargin_1_idx_1;
            }

            if (c_ex > CurvStruct_FeedRate) {
                c_ex = CurvStruct_FeedRate;
            }

            Feedrate = c_ex;
        }

        return Feedrate;
    }

    //
    // Arguments    : const queue_coder *ctx_q_splines
    //                double ctx_cfg_NGridLengthSpline
    //                CurveType Curv_Type
    //                const double Curv_P0[3]
    //                const double Curv_P1[3]
    //                const double Curv_evec[3]
    //                double Curv_theta
    //                double Curv_pitch
    //                const double Curv_CoeffP5[6][3]
    //                int Curv_sp_index
    //                double Curv_a_param
    //                double Curv_b_param
    // Return Type  : double
    //
    static double LengthCurv(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        CurveType Curv_Type, const double Curv_P0[3], const double Curv_P1[3], const double
        Curv_evec[3], double Curv_theta, double Curv_pitch, const double Curv_CoeffP5[6][3], int
        Curv_sp_index, double Curv_a_param, double Curv_b_param)
    {
        double L;
        char message[29];
        static const char b_message[29] = { 'B', 'A', 'D', ' ', 'C', 'U', 'R', 'V', 'E', ' ', 'T',
            'Y', 'P', 'E', ' ', 'I', 'N', ' ', 'L', 'E', 'N', 'G', 'T', 'H', ' ', 'C', 'U', 'R', 'V'
        };

        double unusedU0[3];
        double r1D[3];
        double unusedU1[3];
        double unusedU2[3];
        double p5_1D[5][3];
        double b_y1[9];
        double y[9];
        double b_y[9][3];
        double x[9];
        static const double a[9] = { 0.055555555555555552, 0.16666666666666666, 0.27777777777777779,
            0.38888888888888884, 0.5, 0.61111111111111116, 0.7222222222222221, 0.83333333333333326,
            0.94444444444444442 };

        double c_y;
        if ((Curv_Type == CurveType_Helix) || (Curv_Type == CurveType_Line)) {
            //  coder.cstructname(CurvStruct, 'CurvStruct')
            //
            //
            if (Curv_Type == CurveType_Line) {
                //  line (G01)
                //
                //  parametrization of a straight line between P0 and P1
                //
                //
                r1D[0] = Curv_P1[0] - Curv_P0[0];
                r1D[1] = Curv_P1[1] - Curv_P0[1];
                r1D[2] = Curv_P1[2] - Curv_P0[2];

                //
            } else {
                //  arc of circle / helix (G02, G03)
                b_EvalHelix(Curv_P0, Curv_P1, Curv_evec, Curv_theta, Curv_pitch, Curv_b_param,
                            unusedU0, r1D, unusedU1, unusedU2);
            }

            L = std::sqrt((std::pow(Curv_a_param * r1D[0], 2.0) + std::pow(Curv_a_param * r1D[1],
                            2.0)) + std::pow(Curv_a_param * r1D[2], 2.0));
        } else if (Curv_Type == CurveType_Spline) {
            L = SplineLengthApprox(ctx_q_splines, ctx_cfg_NGridLengthSpline, Curv_sp_index,
                                   Curv_b_param, Curv_a_param + Curv_b_param);
        } else if (Curv_Type == CurveType_TransP5) {
            int ixLead;
            int iyLead;
            double work;

            //  computes approximately the arc length of a parametric spline / RHG
            // MYPOLYDER Differentiate polynomial.
            //
            // u  = u(:).';
            for (int k = 0; k < 5; k++) {
                int p5_1D_tmp;
                p5_1D_tmp = 5 - k;
                p5_1D[k][0] = Curv_CoeffP5[k][0] * static_cast<double>(p5_1D_tmp);
                p5_1D[k][1] = Curv_CoeffP5[k][1] * static_cast<double>(p5_1D_tmp);
                p5_1D[k][2] = Curv_CoeffP5[k][2] * static_cast<double>(p5_1D_tmp);
            }

            //  derivative
            //  midpoint values
            ixLead = 1;
            iyLead = 0;
            work = 0.0;

            // POLYVAL Evaluate array of polynomials with same degree.
            //
            //
            //  Use Horner's method for general case where X is an array.
            for (int t = 0; t < 9; t++) {
                double tmp2;
                double work_tmp;
                tmp2 = work;
                work_tmp = 0.1111111111111111 * static_cast<double>(ixLead);
                work = work_tmp;
                b_y1[iyLead] = work_tmp - tmp2;
                ixLead++;
                iyLead++;
                b_y[t][0] = p5_1D[0][0];
                b_y[t][1] = p5_1D[0][1];
                b_y[t][2] = p5_1D[0][2];
            }

            for (int b_i = 0; b_i < 4; b_i++) {
                double d;
                double d1;
                double d2;
                d = p5_1D[b_i + 1][0];
                d1 = p5_1D[b_i + 1][1];
                d2 = p5_1D[b_i + 1][2];
                for (int c_k = 0; c_k < 9; c_k++) {
                    b_y[c_k][0] = a[c_k] * b_y[c_k][0] + d;
                    b_y[c_k][1] = a[c_k] * b_y[c_k][1] + d1;
                    b_y[c_k][2] = a[c_k] * b_y[c_k][2] + d2;
                }
            }

            for (int b_k = 0; b_k < 9; b_k++) {
                y[b_k] = std::pow(b_y[b_k][0], 2.0);
                y[b_k] += std::pow(b_y[b_k][1], 2.0);
                y[b_k] += std::pow(b_y[b_k][2], 2.0);
            }

            __m256d r;
            __m256d r1;
            r = _mm256_loadu_pd(&y[0]);
            r1 = _mm256_loadu_pd(&b_y1[0]);
            _mm256_storeu_pd(&x[0], _mm256_mul_pd(_mm256_sqrt_pd(r), r1));
            r = _mm256_loadu_pd(&y[4]);
            r1 = _mm256_loadu_pd(&b_y1[4]);
            _mm256_storeu_pd(&x[4], _mm256_mul_pd(_mm256_sqrt_pd(r), r1));
            x[8] = std::sqrt(y[8]) * b_y1[8];
            c_y = x[0];
            for (int d_k = 0; d_k < 8; d_k++) {
                c_y += x[d_k + 1];
            }

            L = c_y;
        } else {
            for (int i = 0; i < 29; i++) {
                message[i] = b_message[i];
            }

            c_assert_(&message[0]);
            L = 0.0;
        }

        return L;
    }

    //
    // Arguments    : ZSpdMode CurOptStruct_zspdmode
    //                bool CurOptStruct_UseConstJerk
    //                double CurOptStruct_ConstJerk
    //                const coder::array<double, 1U> &CurOptStruct_Coeff
    //                unsigned long Bl_handle
    //                double u
    //                double dt
    //                double *ukp1
    //                double *qk
    //                double *dk
    // Return Type  : void
    //
    static void Resample(ZSpdMode CurOptStruct_zspdmode, bool CurOptStruct_UseConstJerk, double
                         CurOptStruct_ConstJerk, const coder::array<double, 1U> &CurOptStruct_Coeff,
                         unsigned long Bl_handle, double u, double dt, double *ukp1, double *qk,
                         double *dk)
    {
        double b_qk;
        char message[26];
        static const char b_message[26] = { 'Z', 'N', ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'u',
            's', 'i', 'n', 'g', ' ', 'c', 'o', 'n', 's', 't', ' ', 'j', 'e', 'r', 'k' };

        double b_dk;
        double unusedU3;
        char c_message[16];
        static const char d_message[16] = { 'N', 'N', ' ', 'i', 's', ' ', 'u', 's', 'i', 'n', 'g',
            ' ', 'j', 'e', 'r', 'k' };

        static const char e_message[26] = { 'N', 'Z', ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'u',
            's', 'i', 'n', 'g', ' ', 'c', 'o', 'n', 's', 't', ' ', 'j', 'e', 'r', 'k' };

        if (CurOptStruct_zspdmode == ZSpdMode_ZN) {
            double t;
            if (!CurOptStruct_UseConstJerk) {
                for (int i = 0; i < 26; i++) {
                    message[i] = b_message[i];
                }

                c_assert_(&message[0]);
            }

            t = std::pow(6.0 * u / CurOptStruct_ConstJerk, 0.33333333333333331);
            if (dt > 0.0) {
                t = std::round(t / dt) * dt;
            }

            *qk = std::pow(CurOptStruct_ConstJerk * std::pow(t, 2.0) / 2.0, 2.0);
            *dk = 2.0 * CurOptStruct_ConstJerk * t;
            *ukp1 = CurOptStruct_ConstJerk * std::pow(t + dt, 3.0) / 6.0;
        } else if (CurOptStruct_zspdmode == ZSpdMode_NN) {
            if (CurOptStruct_UseConstJerk) {
                for (int i1 = 0; i1 < 16; i1++) {
                    c_message[i1] = d_message[i1];
                }

                c_assert_(&c_message[0]);
            }

            b_qk = u;
            b_bspline_eval(Bl_handle, CurOptStruct_Coeff, &b_qk, &b_dk, &unusedU3);
            *qk = b_qk;
            *dk = b_dk;
            *ukp1 = (u + b_dk * std::pow(dt, 2.0) / 4.0) + std::sqrt(b_qk) * dt;
        } else {
            if (CurOptStruct_zspdmode == ZSpdMode_NZ) {
                double b_t;
                if (!CurOptStruct_UseConstJerk) {
                    for (int i2 = 0; i2 < 26; i2++) {
                        message[i2] = e_message[i2];
                    }

                    c_assert_(&message[0]);
                }

                b_t = std::pow(6.0 * (1.0 - u) / CurOptStruct_ConstJerk, 0.33333333333333331);
                *qk = std::pow(CurOptStruct_ConstJerk * std::pow(b_t, 2.0) / 2.0, 2.0);
                *dk = -2.0 * CurOptStruct_ConstJerk * b_t;
                *ukp1 = 1.0 - CurOptStruct_ConstJerk * std::pow(b_t - dt, 3.0) / 6.0;
            }
        }
    }

    //
    // Optimal transitions calculation between segments whith G2 continuity
    // Arguments    : const FeedoptContext *ctx
    // Return Type  : void
    //
    static void SmoothCurvStructs(const FeedoptContext *ctx)
    {
        CurvStruct b_ctx;
        CurvStruct CurvStruct1;
        char message[27];
        static const char b_message[27] = { 'C', 'o', 'm', 'p', 'r', 'e', 's', 's', 'i', 'n', 'g',
            ' ', 'q', 'u', 'e', 'u', 'e', ' ', 'i', 's', ' ', 'e', 'm', 'p', 't', 'y', '!' };

        CurvStruct CurvStruct1_C;
        CurvStruct CurvStruct2_C;
        CurvStruct NextCurv;
        CurvStruct b_CurvStruct2_C;
        CurvStruct CurvStruct3_C;
        CurvStruct CurvStruct_T;
        TransitionResult status;
        if (!ctx->q_compress.isempty()) {
            unsigned int Ncrv;
            unsigned int k;
            ctx->q_compress.get(1.0, (&b_ctx));

            //  to satisfy the coder
            Ncrv = ctx->q_compress.size();

            //  1 -> stdout
            //  2 -> stderr
            if ((static_cast<unsigned long>(std::round(DebugConfig)) & 1UL) != 0UL) {
                printf("Smoothing...\n");
                fflush(stdout);
            }

            k = 1U;
            if (Ncrv > 1U) {
                ctx->q_compress.get(1.0, (&CurvStruct1));
                while (k < Ncrv) {
                    ctx->q_compress.get((static_cast<double>(k) + 1.0), (&NextCurv));
                    if ((CurvStruct1.zspdmode == ZSpdMode_NN) && (NextCurv.zspdmode == ZSpdMode_NN))
                    {
                        b_CalcTransition(&ctx->q_splines, ctx->cfg.CutOff, ctx->cfg.CollTolDeg,
                                         ctx->cfg.NGridLengthSpline, &CurvStruct1, &NextCurv,
                                         &CurvStruct1_C, &CurvStruct_T, &CurvStruct2_C, &status);
                        if (status == TransitionResult_Ok) {
                            ctx->q_smooth.push((&CurvStruct1_C));
                            ctx->q_smooth.push((&CurvStruct_T));
                            CurvStruct1 = CurvStruct2_C;
                        } else if (status == TransitionResult_Collinear) {
                            ctx->q_smooth.push((&CurvStruct1));
                            CurvStruct1 = NextCurv;
                        } else {
                            CurvStruct1.zspdmode = ZSpdMode_NZ;
                            NextCurv.zspdmode = ZSpdMode_ZN;

                            //                  SaveTransition;
                            //                  If the transition fails, force a zero-stop
                            CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                       ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                       ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                       ctx->cfg.NGridLengthSpline, &CurvStruct1, static_cast<double>
                                       (k), &CurvStruct1_C, &CurvStruct2_C);
                            CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz,
                                         ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt,
                                         ctx->cfg.ZeroStartAccLimit, ctx->cfg.ZeroStartJerkLimit,
                                         ctx->cfg.ZeroStartVelLimit, ctx->cfg.DebugCutZero,
                                         ctx->cfg.NGridLengthSpline, &NextCurv, static_cast<double>
                                         (k), &CurvStruct3_C, &CurvStruct1);
                            ctx->q_smooth.push((&CurvStruct1_C));
                            ctx->q_smooth.push((&CurvStruct2_C));
                            ctx->q_smooth.push((&CurvStruct3_C));
                        }

                        k++;
                    } else {
                        ctx->q_smooth.push((&CurvStruct1));
                        CurvStruct1 = NextCurv;
                        k++;
                    }
                }

                ctx->q_smooth.push((&CurvStruct1));
            } else if (static_cast<int>(Ncrv) == 1) {
                ctx->q_compress.get(1.0, (&CurvStruct1));
                if (CurvStruct1.zspdmode == ZSpdMode_ZZ) {
                    b_CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                   ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                   ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                   ctx->cfg.DebugCutZero, ctx->cfg.NGridLengthSpline, &CurvStruct1,
                                   &CurvStruct1_C, &CurvStruct2_C);
                    b_CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                 ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                 ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                 ctx->cfg.NGridLengthSpline, &CurvStruct2_C, &b_CurvStruct2_C,
                                 &CurvStruct3_C);
                    ctx->q_smooth.push((&CurvStruct1_C));
                    ctx->q_smooth.push((&b_CurvStruct2_C));
                    ctx->q_smooth.push((&CurvStruct3_C));
                }
            } else {
                for (int i = 0; i < 27; i++) {
                    message[i] = b_message[i];
                }

                c_assert_(&message[0]);
            }
        }
    }

    //
    // computes approximately the arc length of a parametric spline
    // Arguments    : const queue_coder *ctx_q_splines
    //                double ctx_cfg_NGridLengthSpline
    //                int Curv_sp_index
    //                double u0_tilda
    //                double u1_tilda
    // Return Type  : double
    //
    static double SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, double u0_tilda, double u1_tilda)
    {
        double L;
        CurvStruct expl_temp;
        coder::array<double, 2U> Spline_sp_CoeffX;
        int loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffY;
        int b_loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        int c_loop_ub;
        coder::array<double, 2U> Spline_sp_knots;
        int d_loop_ub;
        coder::array<bool, 2U> x;
        int e_loop_ub;
        int k;
        int idx;
        int ii_size_idx_1;
        int ii;
        bool exitg1;
        int ii_data[1];
        unsigned int Idx1_data[1];
        int f_loop_ub;
        int b_k;
        int b_ii;
        int b_idx;
        unsigned int Idx2_data[1];
        int i6;
        int i7;
        int g_loop_ub;
        coder::array<double, 2U> u_vec_tilda;
        coder::array<double, 2U> u_tilda;
        int i9;
        int i10;
        int h_loop_ub;
        coder::array<double, 2U> r;
        int i11;
        coder::array<double, 2U> u_mid_tilda;
        int scalarLB;
        int vectorUB;
        int i13;
        coder::array<double, 2U> unusedU0;
        coder::array<double, 2U> r1Dx;
        coder::array<double, 2U> unusedU1;
        coder::array<double, 2U> r1Dy;
        coder::array<double, 2U> unusedU2;
        coder::array<double, 2U> r1Dz;
        coder::array<double, 2U> a;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        coder::array<double, 2U> z1;
        int N;
        coder::array<double, 2U> b_x;
        int i19;
        int b_scalarLB;
        int b_vectorUB;
        int f_k;
        int m_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int i20;
        int vlen;

        //  get the sp structure
        ctx_q_splines->get(Curv_sp_index, (&expl_temp));
        Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
        loop_ub = expl_temp.sp.CoeffX.size(1);
        for (int i = 0; i < loop_ub; i++) {
            Spline_sp_CoeffX[i] = expl_temp.sp.CoeffX[i];
        }

        Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
        b_loop_ub = expl_temp.sp.CoeffY.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            Spline_sp_CoeffY[i1] = expl_temp.sp.CoeffY[i1];
        }

        Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
        c_loop_ub = expl_temp.sp.CoeffZ.size(1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            Spline_sp_CoeffZ[i2] = expl_temp.sp.CoeffZ[i2];
        }

        Spline_sp_knots.set_size(1, expl_temp.sp.knots.size(1));
        d_loop_ub = expl_temp.sp.knots.size(1);
        for (int i3 = 0; i3 < d_loop_ub; i3++) {
            Spline_sp_knots[i3] = expl_temp.sp.knots[i3];
        }

        //  the ORIGINAL spline is parametrized with u_tilda
        //  after cut-off, new parameter is called u.
        //  u=0 corresponds to the first lift-off point
        //  u=1 corresponds to the second lift-off point
        //  u is NOT used in this function
        x.set_size(1, Spline_sp_knots.size(1));
        e_loop_ub = Spline_sp_knots.size(1);
        for (int i4 = 0; i4 < e_loop_ub; i4++) {
            x[i4] = (Spline_sp_knots[i4] > u0_tilda);
        }

        k = (1 <= x.size(1));
        idx = 0;
        ii_size_idx_1 = k;
        ii = 0;
        exitg1 = false;
        while ((!exitg1) && (ii <= x.size(1) - 1)) {
            if (x[ii]) {
                idx = 1;
                ii_data[0] = ii + 1;
                exitg1 = true;
            } else {
                ii++;
            }
        }

        if (k == 1) {
            if (idx == 0) {
                ii_size_idx_1 = 0;
            }
        } else {
            ii_size_idx_1 = (1 <= idx);
        }

        if (0 <= ii_size_idx_1 - 1) {
            Idx1_data[0] = static_cast<unsigned int>(ii_data[0]);
        }

        x.set_size(1, Spline_sp_knots.size(1));
        f_loop_ub = Spline_sp_knots.size(1);
        for (int i5 = 0; i5 < f_loop_ub; i5++) {
            x[i5] = (Spline_sp_knots[i5] < u1_tilda);
        }

        b_k = (1 <= x.size(1));
        b_ii = x.size(1);
        b_idx = 0;
        ii_size_idx_1 = b_k;
        exitg1 = false;
        while ((!exitg1) && (b_ii > 0)) {
            if (x[b_ii - 1]) {
                b_idx = 1;
                ii_data[0] = b_ii;
                exitg1 = true;
            } else {
                b_ii--;
            }
        }

        if (b_k == 1) {
            if (b_idx == 0) {
                ii_size_idx_1 = 0;
            }
        } else {
            ii_size_idx_1 = (1 <= b_idx);
        }

        if (0 <= ii_size_idx_1 - 1) {
            Idx2_data[0] = static_cast<unsigned int>(ii_data[0]);
        }

        if (static_cast<int>(Idx1_data[0]) > static_cast<int>(Idx2_data[0])) {
            i6 = 0;
            i7 = 0;
        } else {
            i6 = static_cast<int>(Idx1_data[0]) - 1;
            i7 = static_cast<int>(Idx2_data[0]);
        }

        g_loop_ub = i7 - i6;
        u_vec_tilda.set_size(1, (g_loop_ub + 2));
        u_vec_tilda[0] = u0_tilda;
        for (int i8 = 0; i8 < g_loop_ub; i8++) {
            u_vec_tilda[i8 + 1] = Spline_sp_knots[i6 + i8];
        }

        u_vec_tilda[g_loop_ub + 1] = u1_tilda;
        u_tilda.set_size(1, 0);

        //  N equally spaced u_tilda values between each pair of knots
        //  from u0_tilda until u1_tilda
        i9 = u_vec_tilda.size(1);
        for (int c_k = 0; c_k <= i9 - 2; c_k++) {
            int i12;
            int i_loop_ub;
            i10 = u_tilda.size(1);
            if (u_tilda.size(1) != 0) {
                if (1 > u_tilda.size(1) - 1) {
                    i10 = 0;
                } else {
                    i10 = u_tilda.size(1) - 1;
                }
            }

            linspace(u_vec_tilda[c_k], u_vec_tilda[c_k + 1], ctx_cfg_NGridLengthSpline, r);
            i12 = i10;
            i_loop_ub = r.size(1);
            i10 += r.size(1);
            u_tilda.set_size(u_tilda.size(0), i10);
            for (int i14 = 0; i14 < i_loop_ub; i14++) {
                u_tilda[i12 + i14] = r[i14];
            }
        }

        //  midpoint values
        if (1 > u_tilda.size(1) - 1) {
            h_loop_ub = 0;
        } else {
            h_loop_ub = u_tilda.size(1) - 1;
        }

        i11 = (2 <= u_tilda.size(1));
        u_mid_tilda.set_size(1, h_loop_ub);
        scalarLB = h_loop_ub & -4;
        vectorUB = scalarLB - 4;
        for (i13 = 0; i13 <= vectorUB; i13 += 4) {
            __m256d r1;
            __m256d r2;
            r1 = _mm256_loadu_pd(&u_tilda[i13]);
            r2 = _mm256_loadu_pd(&u_tilda[i11 + i13]);
            _mm256_storeu_pd(&u_mid_tilda[i13], _mm256_mul_pd(_mm256_set1_pd(0.5), _mm256_add_pd(r1,
                               r2)));
        }

        for (i13 = scalarLB; i13 < h_loop_ub; i13++) {
            u_mid_tilda[i13] = 0.5 * (u_tilda[i13] + u_tilda[i11 + i13]);
        }

        //  midpoint values
        //  parametric derivative calculation at each midpoint value
        //  with respect to u_tilda
        c_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, u_mid_tilda, unusedU0, r1Dx);
        c_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, u_mid_tilda, unusedU1, r1Dy);
        c_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, u_mid_tilda, unusedU2, r1Dz);

        //  length (between u0_tilda and u1_tilda) calculation by rectangles method
        a.set_size(3, r1Dx.size(1));
        j_loop_ub = r1Dx.size(1);
        for (int i15 = 0; i15 < j_loop_ub; i15++) {
            a[3 * i15] = r1Dx[i15];
        }

        k_loop_ub = r1Dy.size(1);
        for (int i16 = 0; i16 < k_loop_ub; i16++) {
            a[3 * i16 + 1] = r1Dy[i16];
        }

        l_loop_ub = r1Dz.size(1);
        for (int i17 = 0; i17 < l_loop_ub; i17++) {
            a[3 * i17 + 2] = r1Dz[i17];
        }

        z1.set_size(3, a.size(1));
        N = a.size(1);
        for (int d_k = 0; d_k < N; d_k++) {
            z1[3 * d_k] = std::pow(a[3 * d_k], 2.0);
            z1[3 * d_k + 1] = std::pow(a[3 * d_k + 1], 2.0);
            z1[3 * d_k + 2] = std::pow(a[3 * d_k + 2], 2.0);
        }

        if (z1.size(1) == 0) {
            b_x.set_size(1, 0);
        } else {
            int i18;
            b_x.set_size(1, z1.size(1));
            i18 = z1.size(1);
            for (int e_k = 0; e_k < i18; e_k++) {
                b_x[e_k] = z1[3 * e_k];
                b_x[e_k] = b_x[e_k] + z1[3 * e_k + 1];
                b_x[e_k] = b_x[e_k] + z1[3 * e_k + 2];
            }
        }

        i19 = b_x.size(1);
        b_scalarLB = b_x.size(1) & -4;
        b_vectorUB = b_scalarLB - 4;
        for (f_k = 0; f_k <= b_vectorUB; f_k += 4) {
            __m256d r3;
            r3 = _mm256_loadu_pd(&b_x[f_k]);
            _mm256_storeu_pd(&b_x[f_k], _mm256_sqrt_pd(r3));
        }

        for (f_k = b_scalarLB; f_k < i19; f_k++) {
            b_x[f_k] = std::sqrt(b_x[f_k]);
        }

        diff(u_tilda, r);
        b_x.set_size(1, b_x.size(1));
        m_loop_ub = b_x.size(1);
        c_scalarLB = b_x.size(1) & -4;
        c_vectorUB = c_scalarLB - 4;
        for (i20 = 0; i20 <= c_vectorUB; i20 += 4) {
            __m256d r4;
            __m256d r5;
            r4 = _mm256_loadu_pd(&b_x[i20]);
            r5 = _mm256_loadu_pd(&r[i20]);
            _mm256_storeu_pd(&b_x[i20], _mm256_mul_pd(r4, r5));
        }

        for (i20 = c_scalarLB; i20 < m_loop_ub; i20++) {
            b_x[i20] = b_x[i20] * r[i20];
        }

        vlen = b_x.size(1);
        if (b_x.size(1) == 0) {
            L = 0.0;
        } else {
            double y;
            y = b_x[0];
            for (int g_k = 2; g_k <= vlen; g_k++) {
                double b_y;
                b_y = y;
                if (vlen >= 2) {
                    b_y = y + b_x[g_k - 1];
                }

                y = b_y;
            }

            L = y;
        }

        return L;
    }

    //
    // Arguments    : const FeedoptContext *ctx
    // Return Type  : void
    //
    static void SplitCurvStructs(const FeedoptContext *ctx)
    {
        CurvStruct Curv;
        CurvStruct expl_temp;
        coder::array<double, 2U> Spline_sp_knots;
        coder::array<bool, 2U> x;
        int ii_data[1];
        int Idx1_data[1];
        int Idx2_data[1];
        coder::array<double, 2U> knots;
        double b_L;
        if (!ctx->q_smooth.isempty()) {
            unsigned int N;
            int i;
            N = ctx->q_smooth.size();

            //  1 -> stdout
            //  2 -> stderr
            if ((static_cast<unsigned long>(std::round(DebugConfig)) & 1UL) != 0UL) {
                printf("Splitting...\n");
                fflush(stdout);
            }

            i = static_cast<int>(N);
            for (int k = 0; k < i; k++) {
                ctx->q_smooth.get((k + 1U), (&Curv));

                //  coder.varsize('CrvStructs', [1, 100], [0, 1]);
                //
                if ((Curv.Type != CurveType_TransP5) && (!Curv.UseConstJerk)) {
                    if ((Curv.Type == CurveType_Line) || (Curv.Type == CurveType_Helix)) {
                        double d;
                        double d1;
                        double L;
                        d = Curv.a_param;
                        d1 = Curv.b_param;
                        L = LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, Curv.Type,
                                       Curv.P0, Curv.P1, Curv.evec, Curv.theta, Curv.pitch,
                                       Curv.CoeffP5, Curv.sp_index, Curv.a_param, Curv.b_param);
                        if (L < 2.0 * ctx->cfg.LSplit) {
                            ctx->q_split.push((&Curv));
                        } else {
                            double b_N;
                            double L_split;
                            int i2;
                            b_N = std::ceil(L / ctx->cfg.LSplit);
                            L_split = L / b_N;
                            i2 = static_cast<int>(b_N);
                            for (int b_k = 0; b_k < i2; b_k++) {
                                double u_tilda_0_tmp;
                                double u_tilda_0;
                                u_tilda_0_tmp = L_split / L;
                                u_tilda_0 = d * (((static_cast<double>(b_k) + 1.0) - 1.0) *
                                                 u_tilda_0_tmp) + d1;
                                Curv.a_param = (d * ((static_cast<double>(b_k) + 1.0) *
                                                     u_tilda_0_tmp) + d1) - u_tilda_0;
                                Curv.b_param = u_tilda_0;
                                ctx->q_split.push((&Curv));
                            }
                        }
                    } else {
                        int loop_ub;
                        double u1_tilda;
                        int i3;
                        int i4;
                        int b_loop_ub;
                        int i5;
                        int c_k;
                        int idx;
                        int ii_size_idx_1;
                        int ii;
                        bool exitg1;
                        int d_k;
                        int b_ii;
                        int b_idx;
                        int i8;
                        int i9;
                        int c_loop_ub;
                        int e_k;
                        ctx->q_splines.get(Curv.sp_index, (&expl_temp));
                        Spline_sp_knots.set_size(1, expl_temp.sp.knots.size(1));
                        loop_ub = expl_temp.sp.knots.size(1);
                        for (int i1 = 0; i1 < loop_ub; i1++) {
                            Spline_sp_knots[i1] = expl_temp.sp.knots[i1];
                        }

                        u1_tilda = Curv.a_param + Curv.b_param;
                        if (4 > Spline_sp_knots.size(1) - 3) {
                            i3 = 0;
                            i4 = -1;
                        } else {
                            i3 = 3;
                            i4 = Spline_sp_knots.size(1) - 4;
                        }

                        b_loop_ub = i4 - i3;
                        i5 = b_loop_ub + 1;
                        x.set_size(1, i5);
                        for (int i6 = 0; i6 <= b_loop_ub; i6++) {
                            x[i6] = (Spline_sp_knots[i3 + i6] > Curv.b_param);
                        }

                        c_k = (1 <= x.size(1));
                        idx = 0;
                        ii_size_idx_1 = c_k;
                        ii = 0;
                        exitg1 = false;
                        while ((!exitg1) && (ii <= x.size(1) - 1)) {
                            if (x[ii]) {
                                idx = 1;
                                ii_data[0] = ii + 1;
                                exitg1 = true;
                            } else {
                                ii++;
                            }
                        }

                        if (c_k == 1) {
                            if (idx == 0) {
                                ii_size_idx_1 = 0;
                            }
                        } else {
                            ii_size_idx_1 = (1 <= idx);
                        }

                        if (0 <= ii_size_idx_1 - 1) {
                            Idx1_data[0] = ii_data[0];
                        }

                        x.set_size(1, i5);
                        for (int i7 = 0; i7 <= b_loop_ub; i7++) {
                            x[i7] = (Spline_sp_knots[i3 + i7] < u1_tilda);
                        }

                        d_k = (1 <= x.size(1));
                        b_ii = x.size(1);
                        b_idx = 0;
                        ii_size_idx_1 = d_k;
                        exitg1 = false;
                        while ((!exitg1) && (b_ii > 0)) {
                            if (x[b_ii - 1]) {
                                b_idx = 1;
                                ii_data[0] = b_ii;
                                exitg1 = true;
                            } else {
                                b_ii--;
                            }
                        }

                        if (d_k == 1) {
                            if (b_idx == 0) {
                                ii_size_idx_1 = 0;
                            }
                        } else {
                            ii_size_idx_1 = (1 <= b_idx);
                        }

                        if (0 <= ii_size_idx_1 - 1) {
                            Idx2_data[0] = ii_data[0];
                        }

                        if (Idx1_data[0] > Idx2_data[0]) {
                            i8 = 0;
                            i9 = 0;
                        } else {
                            i8 = Idx1_data[0] - 1;
                            i9 = Idx2_data[0];
                        }

                        c_loop_ub = i9 - i8;
                        knots.set_size(1, (c_loop_ub + 2));
                        knots[0] = Curv.b_param;
                        for (int i10 = 0; i10 < c_loop_ub; i10++) {
                            knots[i10 + 1] = Spline_sp_knots[(i3 + i8) + i10];
                        }

                        knots[c_loop_ub + 1] = u1_tilda;
                        b_L = 0.0;
                        e_k = 0;
                        while (e_k + 1 < knots.size(1)) {
                            int b_i;
                            b_i = e_k;
                            while ((b_L < ctx->cfg.LSplit) && (e_k + 1 < knots.size(1))) {
                                double delta_L;
                                delta_L = SplineLengthApprox(&ctx->q_splines,
                                    ctx->cfg.NGridLengthSpline, Curv.sp_index, knots[e_k], knots[e_k
                                    + 1]);
                                b_L += delta_L;
                                e_k++;
                            }

                            Curv.a_param = knots[e_k] - knots[b_i];
                            Curv.b_param = knots[b_i];
                            ctx->q_split.push((&Curv));
                            b_L = 0.0;
                        }
                    }
                } else {
                    ctx->q_split.push((&Curv));
                }
            }
        }
    }

    //
    // Arguments    : const queue_coder *ctx_q_splines
    //                double ctx_cfg_CutOff
    //                double ctx_cfg_CollTolDeg
    //                double ctx_cfg_NGridLengthSpline
    //                const CurvStruct *CurvStruct1
    //                const CurvStruct *CurvStruct2
    //                CurvStruct *CurvStruct1_C
    //                CurvStruct *CurvStruct_T
    //                CurvStruct *CurvStruct2_C
    //                TransitionResult *status
    // Return Type  : void
    //
    static void b_CalcTransition(const queue_coder *ctx_q_splines, double ctx_cfg_CutOff, double
        ctx_cfg_CollTolDeg, double ctx_cfg_NGridLengthSpline, const CurvStruct *CurvStruct1, const
        CurvStruct *CurvStruct2, CurvStruct *CurvStruct1_C, CurvStruct *CurvStruct_T, CurvStruct
        *CurvStruct2_C, TransitionResult *status)
    {
        double CutOff;
        double Length_Threshold;
        unsigned long u;
        unsigned long u1;
        double unusedU0[3];
        double r0D1_1[3];
        double unusedU1[3];
        double r1D1_1[3];
        TransitionResult b_status;
        CurvStruct expl_temp;
        coder::array<double, 2U> Spline_sp_knots;
        double r0D0[3];
        double r0D1[3];
        double r0D2[3];
        double r1D0[3];
        double r1D1[3];
        double r1D2[3];
        coder::array<bool, 2U> b_x;
        double p5[6][3];
        int c_status;
        double alpha0;
        double alpha1;
        int ii_data[1];
        int Spline_sp_knots_size[2];
        double Spline_sp_knots_data[1];
        CutOff = ctx_cfg_CutOff;
        Length_Threshold = 3.0 * ctx_cfg_CutOff;

        //  1 -> stdout
        //  2 -> stderr
        u = static_cast<unsigned long>(std::round(DebugConfig));
        u1 = u & 8UL;
        if (u1 != 0UL) {
            printf("========== CalcTransition ==========\n");
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u1 != 0UL) {
            printf("CutOff = %.3f\n", ctx_cfg_CutOff);
            fflush(stdout);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1->Type,
                              CurvStruct1->zspdmode, CurvStruct1->P0, CurvStruct1->P1,
                              CurvStruct1->evec, CurvStruct1->theta, CurvStruct1->pitch,
                              CurvStruct1->CoeffP5, CurvStruct1->sp_index, CurvStruct1->FeedRate,
                              CurvStruct1->UseConstJerk, CurvStruct1->ConstJerk,
                              CurvStruct1->a_param, CurvStruct1->b_param);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2->Type,
                              CurvStruct2->zspdmode, CurvStruct2->P0, CurvStruct2->P1,
                              CurvStruct2->evec, CurvStruct2->theta, CurvStruct2->pitch,
                              CurvStruct2->CoeffP5, CurvStruct2->sp_index, CurvStruct2->FeedRate,
                              CurvStruct2->UseConstJerk, CurvStruct2->ConstJerk,
                              CurvStruct2->a_param, CurvStruct2->b_param);
        }

        *CurvStruct_T = *CurvStruct1;

        // default value
        e_EvalCurvStruct(ctx_q_splines, CurvStruct1->Type, CurvStruct1->P0, CurvStruct1->P1,
                         CurvStruct1->evec, CurvStruct1->theta, CurvStruct1->pitch,
                         CurvStruct1->CoeffP5, CurvStruct1->sp_index, CurvStruct1->a_param,
                         CurvStruct1->b_param, unusedU0, r0D1_1);
        f_EvalCurvStruct(ctx_q_splines, CurvStruct2->Type, CurvStruct2->P0, CurvStruct2->P1,
                         CurvStruct2->evec, CurvStruct2->theta, CurvStruct2->pitch,
                         CurvStruct2->CoeffP5, CurvStruct2->sp_index, CurvStruct2->a_param,
                         CurvStruct2->b_param, unusedU1, r1D1_1);

        //  colinearity test
        if ((CurvStruct1->Type != CurveType_Helix) && (CurvStruct2->Type != CurveType_Helix) &&
                collinear(r0D1_1, r1D1_1, ctx_cfg_CollTolDeg)) {
            //  && norm(r0D2 - r1D2) < 10*eps && collinear(r0D2, r1D2, 1e-2)
            b_status = TransitionResult_Collinear;
            *CurvStruct1_C = *CurvStruct1;
            *CurvStruct2_C = *CurvStruct2;
        } else {
            double L1;
            double L2;
            L1 = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1->Type,
                            CurvStruct1->P0, CurvStruct1->P1, CurvStruct1->evec, CurvStruct1->theta,
                            CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                            CurvStruct1->a_param, CurvStruct1->b_param);
            L2 = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2->Type,
                            CurvStruct2->P0, CurvStruct2->P1, CurvStruct2->evec, CurvStruct2->theta,
                            CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                            CurvStruct2->a_param, CurvStruct2->b_param);

            //  CutOff calculation
            if ((CurvStruct1->Type != CurveType_Spline) && (CurvStruct2->Type != CurveType_Spline))
            {
                if ((L1 < Length_Threshold) || (L2 < Length_Threshold)) {
                    CutOff = std::fmin(L1, L2) / 3.0;
                }
            } else {
                double x;
                double y;
                int ii_size_idx_1;
                bool exitg1;
                if (CurvStruct1->Type == CurveType_Spline) {
                    int loop_ub;
                    double u1_tilda;
                    int c_loop_ub;
                    int k;
                    int ii;
                    int idx;
                    ctx_q_splines->get(CurvStruct1->sp_index, (&expl_temp));
                    Spline_sp_knots.set_size(1, expl_temp.sp.knots.size(1));
                    loop_ub = expl_temp.sp.knots.size(1);
                    for (int i = 0; i < loop_ub; i++) {
                        Spline_sp_knots[i] = expl_temp.sp.knots[i];
                    }

                    //  In a very general case we may cut a spline several times
                    //  at the end;
                    //  If a spline had already been cut at the end,
                    //  we must compute the corresponding
                    //  native spline parameter (u1_tilda) value
                    //  This value will be different from 1 in this special case
                    u1_tilda = CurvStruct1->a_param + CurvStruct1->b_param;

                    //  We need to find the previous spline knot u0_tilda...
                    b_x.set_size(1, Spline_sp_knots.size(1));
                    c_loop_ub = Spline_sp_knots.size(1);
                    for (int i2 = 0; i2 < c_loop_ub; i2++) {
                        b_x[i2] = (Spline_sp_knots[i2] < u1_tilda);
                    }

                    k = (1 <= b_x.size(1));
                    ii = b_x.size(1);
                    idx = 0;
                    ii_size_idx_1 = k;
                    exitg1 = false;
                    while ((!exitg1) && (ii > 0)) {
                        if (b_x[ii - 1]) {
                            idx = 1;
                            ii_data[0] = ii;
                            exitg1 = true;
                        } else {
                            ii--;
                        }
                    }

                    if (k == 1) {
                        if (idx == 0) {
                            ii_size_idx_1 = 0;
                        }
                    } else {
                        ii_size_idx_1 = (1 <= idx);
                    }

                    Spline_sp_knots_size[0] = 1;
                    Spline_sp_knots_size[1] = ii_size_idx_1;
                    if (0 <= ii_size_idx_1 - 1) {
                        Spline_sp_knots_data[0] = Spline_sp_knots[ii_data[0] - 1];
                    }

                    x = b_SplineLengthApprox(ctx_q_splines, ctx_cfg_NGridLengthSpline,
                        CurvStruct1->sp_index, Spline_sp_knots_data, Spline_sp_knots_size, u1_tilda)
                        / 2.0;
                } else if (L1 < Length_Threshold) {
                    x = L1 / 3.0;
                } else {
                    x = ctx_cfg_CutOff;
                }

                if (CurvStruct2->Type == CurveType_Spline) {
                    int b_loop_ub;
                    int d_loop_ub;
                    int b_k;
                    int b_idx;
                    int b_ii;
                    ctx_q_splines->get(CurvStruct2->sp_index, (&expl_temp));
                    Spline_sp_knots.set_size(1, expl_temp.sp.knots.size(1));
                    b_loop_ub = expl_temp.sp.knots.size(1);
                    for (int i1 = 0; i1 < b_loop_ub; i1++) {
                        Spline_sp_knots[i1] = expl_temp.sp.knots[i1];
                    }

                    //  In a very general case we may cut a spline several times
                    //  at the beginning;
                    //  If a spline had already been cut at the beginning,
                    //  we must compute the corresponding
                    //  native spline parameter (u0_tilda) value
                    //  This value will be different from 0 in this special case
                    //  We need to find the next spline knot u1_tilda...
                    b_x.set_size(1, Spline_sp_knots.size(1));
                    d_loop_ub = Spline_sp_knots.size(1);
                    for (int i3 = 0; i3 < d_loop_ub; i3++) {
                        b_x[i3] = (Spline_sp_knots[i3] > CurvStruct2->b_param);
                    }

                    b_k = (1 <= b_x.size(1));
                    b_idx = 0;
                    ii_size_idx_1 = b_k;
                    b_ii = 0;
                    exitg1 = false;
                    while ((!exitg1) && (b_ii <= b_x.size(1) - 1)) {
                        if (b_x[b_ii]) {
                            b_idx = 1;
                            ii_data[0] = b_ii + 1;
                            exitg1 = true;
                        } else {
                            b_ii++;
                        }
                    }

                    if (b_k == 1) {
                        if (b_idx == 0) {
                            ii_size_idx_1 = 0;
                        }
                    } else {
                        ii_size_idx_1 = (1 <= b_idx);
                    }

                    Spline_sp_knots_size[0] = 1;
                    Spline_sp_knots_size[1] = ii_size_idx_1;
                    if (0 <= ii_size_idx_1 - 1) {
                        Spline_sp_knots_data[0] = Spline_sp_knots[ii_data[0] - 1];
                    }

                    y = c_SplineLengthApprox(ctx_q_splines, ctx_cfg_NGridLengthSpline,
                        CurvStruct2->sp_index, CurvStruct2->b_param, Spline_sp_knots_data,
                        Spline_sp_knots_size) / 2.0;
                } else if (L2 < Length_Threshold) {
                    y = L2 / 3.0;
                } else {
                    y = ctx_cfg_CutOff;
                }

                CutOff = std::fmin(x, y);
            }

            *CurvStruct1_C = *CurvStruct1;
            CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1_C, CutOff);
            *CurvStruct2_C = *CurvStruct2;
            b_CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2_C, CutOff);

            //  1 -> stdout
            //  2 -> stderr
            if (u1 != 0UL) {
                printf("========== AFTER CUTTING \n");
                fflush(stdout);
                b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1_C->Type,
                                  CurvStruct1_C->zspdmode, CurvStruct1_C->P0, CurvStruct1_C->P1,
                                  CurvStruct1_C->evec, CurvStruct1_C->theta, CurvStruct1_C->pitch,
                                  CurvStruct1_C->CoeffP5, CurvStruct1_C->sp_index,
                                  CurvStruct1_C->FeedRate, CurvStruct1_C->UseConstJerk,
                                  CurvStruct1_C->ConstJerk, CurvStruct1_C->a_param,
                                  CurvStruct1_C->b_param);
                b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2_C->Type,
                                  CurvStruct2_C->zspdmode, CurvStruct2_C->P0, CurvStruct2_C->P1,
                                  CurvStruct2_C->evec, CurvStruct2_C->theta, CurvStruct2_C->pitch,
                                  CurvStruct2_C->CoeffP5, CurvStruct2_C->sp_index,
                                  CurvStruct2_C->FeedRate, CurvStruct2_C->UseConstJerk,
                                  CurvStruct2_C->ConstJerk, CurvStruct2_C->a_param,
                                  CurvStruct2_C->b_param);
            }

            d_EvalCurvStruct(ctx_q_splines, CurvStruct1_C->Type, CurvStruct1_C->P0,
                             CurvStruct1_C->P1, CurvStruct1_C->evec, CurvStruct1_C->theta,
                             CurvStruct1_C->pitch, CurvStruct1_C->CoeffP5, CurvStruct1_C->sp_index,
                             CurvStruct1_C->a_param, CurvStruct1_C->b_param, r0D0, r0D1, r0D2);
            g_EvalCurvStruct(ctx_q_splines, CurvStruct2_C->Type, CurvStruct2_C->P0,
                             CurvStruct2_C->P1, CurvStruct2_C->evec, CurvStruct2_C->theta,
                             CurvStruct2_C->pitch, CurvStruct2_C->CoeffP5, CurvStruct2_C->sp_index,
                             CurvStruct2_C->a_param, CurvStruct2_C->b_param, r1D0, r1D1, r1D2);

            //  G2 transition calculation
            G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2, p5, &c_status, &alpha0,
                &alpha1);
            if (c_status == 1) {
                //  standard case
                //  transition CurvStruct calculation
                ConstrTransP5Struct(p5, CurvStruct1->FeedRate, CurvStruct_T);
                b_status = TransitionResult_Ok;
            } else if (c_status == 6) {
                unsigned long u3;

                //  TODO: decide in the future...
                //  Now we ignore and construct the transition curve anyway
                ConstrTransP5Struct(p5, CurvStruct1->FeedRate, CurvStruct_T);
                b_status = TransitionResult_Ok;

                //  1 -> stdout
                //  2 -> stderr
                u3 = static_cast<unsigned long>(std::round(DebugConfig)) & 1UL;
                if (u3 != 0UL) {
                    printf("========== CalcTransition ==========\n");
                    fflush(stdout);
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u3 != 0UL) {
                    printf("=========== status = 6 ==========\n");
                    fflush(stdout);
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u3 != 0UL) {
                    printf("Lines: %d, %d\n\n", CurvStruct1->gcode_source_line,
                           CurvStruct2->gcode_source_line);
                    fflush(stdout);
                }
            } else {
                unsigned long u2;
                b_status = TransitionResult_NoSolution;

                //  1 -> stdout
                //  2 -> stderr
                u2 = u & 1UL;
                if (u2 != 0UL) {
                    printf("========== CalcTransition ==========\n");
                    fflush(stdout);
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u2 != 0UL) {
                    printf("=========== No Solution ==========\n");
                    fflush(stdout);
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u2 != 0UL) {
                    printf("Lines: %d, %d\n\n", CurvStruct1->gcode_source_line,
                           CurvStruct2->gcode_source_line);
                    fflush(stdout);
                }
            }

            CurvStruct1_C->gcode_source_line = CurvStruct1->gcode_source_line;
            CurvStruct_T->gcode_source_line = CurvStruct2->gcode_source_line;
            CurvStruct2_C->gcode_source_line = CurvStruct2->gcode_source_line;
        }

        *status = b_status;
    }

    //
    // We cut d0 [mm] in the beginning and d1 [mm] in the end of the segment
    //  We determine a new value of the parameter u_tilda
    // Arguments    : const queue_coder *ctx_q_splines
    //                double ctx_cfg_NGridLengthSpline
    //                CurvStruct *b_CurvStruct
    //                double d0
    // Return Type  : void
    //
    static void b_CutCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        CurvStruct *b_CurvStruct, double d0)
    {
        CurvStruct b_ctx_q_splines;
        double unusedU0[3];
        double r1D0[3];
        double L_tot;
        coder::array<double, 2U> Integrand;
        coder::array<double, 2U> u_mid_tilda;
        coder::array<double, 2U> du_tilda;
        double unusedU1[3];
        double r1D1[3];
        double u0_tilda;
        double u1_tilda;
        double L;
        if (b_CurvStruct->Type == CurveType_Spline) {
            ctx_q_splines->get(b_CurvStruct->sp_index, (&b_ctx_q_splines));

            //  discretizing along the total spline
            //  from u=0 to u=1
            d_SplineLengthApprox(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->sp_index,
                                 b_CurvStruct->b_param, b_CurvStruct->a_param +
                                 b_CurvStruct->b_param, &L_tot, Integrand, u_mid_tilda, du_tilda);
            if (d0 != 0.0) {
                unsigned int k;

                //  spline-long length calculation by rectangles method
                //  beginning from u=0
                //  until d0 is reached
                L = 0.0;
                k = 1U;
                while ((L < d0) && (k <= static_cast<unsigned int>(du_tilda.size(1)))) {
                    int L_tmp;
                    L_tmp = static_cast<int>(k) - 1;
                    L += Integrand[L_tmp] * du_tilda[L_tmp];
                    k++;
                }

                u0_tilda = u_mid_tilda[static_cast<int>(k) - 1];
            } else {
                u0_tilda = b_CurvStruct->b_param;
            }

            u1_tilda = b_CurvStruct->a_param + b_CurvStruct->b_param;
        } else {
            //  In case of helix and line, ||r'(u)||=const,
            //  for 0 < u < 1
            //  r1D0 and r1D1 are with respect to u
            f_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                             b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                             b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                             b_CurvStruct->b_param, unusedU0, r1D0);
            e_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                             b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                             b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                             b_CurvStruct->b_param, unusedU1, r1D1);

            //  d0 = Integral_0_u0 ||r'(u)||du
            //  d1 = Integral_u1_1 ||r'(u)||du
            //  conversion to native curve parameter u_tilda
            u0_tilda = b_CurvStruct->a_param * (d0 / std::sqrt((std::pow(r1D0[0], 2.0) + std::pow
                (r1D0[1], 2.0)) + std::pow(r1D0[2], 2.0))) + b_CurvStruct->b_param;
            u1_tilda = b_CurvStruct->a_param * (1.0 - 0.0 / std::sqrt((std::pow(r1D1[0], 2.0) + std::
                pow(r1D1[1], 2.0)) + std::pow(r1D1[2], 2.0))) + b_CurvStruct->b_param;
        }

        b_CurvStruct->a_param = u1_tilda - u0_tilda;
        b_CurvStruct->b_param = u0_tilda;
    }

    //
    // Arguments    : const queue_coder *ctx_q_gcode
    //                const queue_coder *ctx_q_splines
    //                int ctx_cfg_NHorz
    //                const double ctx_cfg_amax[3]
    //                const double ctx_cfg_jmax[3]
    //                double ctx_cfg_dt
    //                double ctx_cfg_ZeroStartAccLimit
    //                double ctx_cfg_ZeroStartJerkLimit
    //                double ctx_cfg_ZeroStartVelLimit
    //                double ctx_cfg_NGridLengthSpline
    //                const CurvStruct *b_CurvStruct
    //                CurvStruct *CurvStruct1
    //                CurvStruct *CurvStruct2
    // Return Type  : void
    //
    static void b_CutZeroEnd(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int
        ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3], double ctx_cfg_dt,
        double ctx_cfg_ZeroStartAccLimit, double ctx_cfg_ZeroStartJerkLimit, double
        ctx_cfg_ZeroStartVelLimit, double ctx_cfg_NGridLengthSpline, const CurvStruct *b_CurvStruct,
        CurvStruct *CurvStruct1, CurvStruct *CurvStruct2)
    {
        double unusedU0[3];
        double r1D[3];
        double ex;
        double z1_idx_1;
        double z1_idx_2;
        double ex_tmp;
        double b_ex;
        double tmax;
        double jps;
        coder::array<double, 2U> t;
        coder::array<double, 2U> z1;
        int N;
        coder::array<double, 2U> uk;
        int b_loop_ub;
        int scalarLB;
        int vectorUB;
        int i1;
        int b_N;
        coder::array<double, 2U> d1uk;
        int c_loop_ub;
        int b_scalarLB;
        int b_vectorUB;
        int i2;
        coder::array<double, 2U> d2uk;
        int d_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int i3;
        coder::array<double, 2U> b_uk;
        int e_loop_ub;
        coder::array<double, 2U> unusedU1;
        coder::array<double, 2U> b_r1D;
        coder::array<double, 2U> r2D;
        coder::array<double, 2U> r3D;
        double b_vmax;
        bool p;
        bool blarge;
        unsigned long alarge_tmp;
        bool alarge;
        unsigned long c_N;
        unsigned long c_k;
        bool exitg1;
        CurvStruct expl_temp;
        int d_N;
        double TmpCurv_P0[3];
        double TmpCurv_P1[3];
        double TmpCurv_evec[3];
        coder::array<double, 2U> c;
        coder::array<double, 2U> r3;
        coder::array<double, 2U> b_d1uk;
        int f_loop_ub;
        int d_scalarLB;
        int d_vectorUB;
        int i7;
        double TmpCurv_CoeffP5[6][3];
        coder::array<double, 2U> r6;
        coder::array<double, 2U> a;
        int g_loop_ub;
        coder::array<double, 2U> x;
        coder::array<double, 2U> jt;
        coder::array<double, 2U> b_z1;
        int e_N;
        int j_loop_ub;
        coder::array<double, 2U> at;
        int m;
        coder::array<double, 1U> max_jt;
        int b_m;
        coder::array<double, 1U> max_at;
        coder::array<bool, 2U> b_max_jt;
        int m_loop_ub;
        int tmp_data[1];
        int tmp_size[2];
        int cut_index_jerk_size_idx_1;
        int n_loop_ub;
        int cut_index_jerk_data[1];
        coder::array<bool, 2U> b_max_at;
        int o_loop_ub;
        int cut_index_acc_size_idx_1;
        int p_loop_ub;
        int cut_index_acc_data[1];
        coder::array<double, 2U> b_a;
        coder::array<double, 2U> c_z1;
        int f_N;
        coder::array<double, 2U> b_x;
        int i26;
        int e_scalarLB;
        int e_vectorUB;
        int p_k;
        coder::array<bool, 2U> c_x;
        int q_loop_ub;
        int cut_index_vel_size_idx_1;
        int r_loop_ub;
        int cut_index_vel_data[1];
        int varargin_1_data[3];
        int c_ex;
        int cut_index;
        double L;
        f_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                         b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                         b_CurvStruct->b_param, unusedU0, r1D);
        ex = ctx_cfg_jmax[0];
        if (ctx_cfg_jmax[0] > ctx_cfg_jmax[1]) {
            ex = ctx_cfg_jmax[1];
        }

        if (ex > ctx_cfg_jmax[2]) {
            ex = ctx_cfg_jmax[2];
        }

        z1_idx_1 = std::abs(r1D[1]);
        z1_idx_2 = std::abs(r1D[2]);
        ex_tmp = std::abs(r1D[0]);
        b_ex = ex_tmp;
        if (ex_tmp < z1_idx_1) {
            b_ex = z1_idx_1;
        }

        if (b_ex < z1_idx_2) {
            b_ex = z1_idx_2;
        }

        tmax = std::ceil(std::pow(6.0 / (ex / b_ex), 0.33333333333333331) / ctx_cfg_dt) * ctx_cfg_dt;
        jps = 6.0 / std::pow(tmax, 3.0);
        if ((-ctx_cfg_dt == 0.0) || ((tmax < 0.0) && (-ctx_cfg_dt < 0.0)) || ((0.0 < tmax) &&
                (-ctx_cfg_dt > 0.0))) {
            t.set_size(1, 0);
        } else if ((std::floor(tmax) == tmax) && (std::floor(-ctx_cfg_dt) == -ctx_cfg_dt)) {
            int loop_ub;
            loop_ub = static_cast<int>(std::floor((0.0 - tmax) / -ctx_cfg_dt));
            t.set_size(1, (loop_ub + 1));
            for (int i = 0; i <= loop_ub; i++) {
                t[i] = tmax + -ctx_cfg_dt * static_cast<double>(i);
            }
        } else {
            b_eml_float_colon(tmax, -ctx_cfg_dt, t);
        }

        z1.set_size(1, t.size(1));
        N = t.size(1);
        for (int k = 0; k < N; k++) {
            z1[k] = std::pow(t[k], 3.0);
        }

        uk.set_size(1, z1.size(1));
        b_loop_ub = z1.size(1);
        scalarLB = z1.size(1) & -4;
        vectorUB = scalarLB - 4;
        for (i1 = 0; i1 <= vectorUB; i1 += 4) {
            __m256d r;
            r = _mm256_loadu_pd(&z1[i1]);
            _mm256_storeu_pd(&uk[i1], _mm256_div_pd(_mm256_mul_pd(_mm256_set1_pd(jps), r),
                              _mm256_set1_pd(6.0)));
        }

        for (i1 = scalarLB; i1 < b_loop_ub; i1++) {
            uk[i1] = jps * z1[i1] / 6.0;
        }

        z1.set_size(1, t.size(1));
        b_N = t.size(1);
        for (int b_k = 0; b_k < b_N; b_k++) {
            z1[b_k] = std::pow(t[b_k], 2.0);
        }

        d1uk.set_size(1, z1.size(1));
        c_loop_ub = z1.size(1);
        b_scalarLB = z1.size(1) & -4;
        b_vectorUB = b_scalarLB - 4;
        for (i2 = 0; i2 <= b_vectorUB; i2 += 4) {
            __m256d r1;
            r1 = _mm256_loadu_pd(&z1[i2]);
            _mm256_storeu_pd(&d1uk[i2], _mm256_div_pd(_mm256_mul_pd(_mm256_set1_pd(jps), r1),
                              _mm256_set1_pd(2.0)));
        }

        for (i2 = b_scalarLB; i2 < c_loop_ub; i2++) {
            d1uk[i2] = jps * z1[i2] / 2.0;
        }

        d2uk.set_size(1, t.size(1));
        d_loop_ub = t.size(1);
        c_scalarLB = t.size(1) & -4;
        c_vectorUB = c_scalarLB - 4;
        for (i3 = 0; i3 <= c_vectorUB; i3 += 4) {
            __m256d r2;
            r2 = _mm256_loadu_pd(&t[i3]);
            _mm256_storeu_pd(&d2uk[i3], _mm256_mul_pd(_mm256_set1_pd(jps), r2));
        }

        for (i3 = c_scalarLB; i3 < d_loop_ub; i3++) {
            d2uk[i3] = jps * t[i3];
        }

        b_uk.set_size(1, uk.size(1));
        e_loop_ub = uk.size(1) - 1;
        for (int i4 = 0; i4 <= e_loop_ub; i4++) {
            b_uk[i4] = uk[i4];
        }

        double DBLMAXFLINT;
        h_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                         b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                         b_CurvStruct->b_param, b_uk, unusedU1, b_r1D, r2D, r3D);
        b_vmax = b_CurvStruct->FeedRate;
        p = false;
        DBLMAXFLINT = std::pow(2.0, 52.0);
        blarge = (1.0 >= DBLMAXFLINT);
        alarge_tmp = 2UL - ctx_cfg_NHorz;
        alarge = (alarge_tmp >= static_cast<unsigned long>(std::round(DBLMAXFLINT)));
        if ((!alarge) && blarge) {
            p = true;
        } else if (alarge && blarge) {
            p = (alarge_tmp < 1UL);
        } else {
            if (!alarge) {
                p = (alarge_tmp < 1.0);
            }
        }

        if (p) {
            c_N = 1UL;
        } else {
            c_N = 2UL - ctx_cfg_NHorz;
        }

        c_k = 1UL;
        exitg1 = false;
        while ((!exitg1) && (c_k >= c_N)) {
            ctx_q_gcode->get(c_k, (&expl_temp));
            TmpCurv_P0[0] = expl_temp.P0[0];
            TmpCurv_P1[0] = expl_temp.P1[0];
            TmpCurv_evec[0] = expl_temp.evec[0];
            TmpCurv_P0[1] = expl_temp.P0[1];
            TmpCurv_P1[1] = expl_temp.P1[1];
            TmpCurv_evec[1] = expl_temp.evec[1];
            TmpCurv_P0[2] = expl_temp.P0[2];
            TmpCurv_P1[2] = expl_temp.P1[2];
            TmpCurv_evec[2] = expl_temp.evec[2];
            for (int i6 = 0; i6 < 6; i6++) {
                TmpCurv_CoeffP5[i6][0] = expl_temp.CoeffP5[i6][0];
                TmpCurv_CoeffP5[i6][1] = expl_temp.CoeffP5[i6][1];
                TmpCurv_CoeffP5[i6][2] = expl_temp.CoeffP5[i6][2];
            }

            double y;
            y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                                   TmpCurv_P0, TmpCurv_P1, TmpCurv_evec, expl_temp.theta,
                                   expl_temp.pitch, TmpCurv_CoeffP5, expl_temp.sp_index,
                                   expl_temp.FeedRate, expl_temp.a_param, expl_temp.b_param);
            b_vmax = std::fmin(b_vmax, y);
            if (expl_temp.zspdmode == ZSpdMode_ZN) {
                exitg1 = true;
            } else {
                c_k--;
            }
        }

        z1.set_size(1, d1uk.size(1));
        d_N = d1uk.size(1);
        for (int d_k = 0; d_k < d_N; d_k++) {
            z1[d_k] = std::pow(d1uk[d_k], 3.0);
        }

        c.set_size(3, b_r1D.size(1));
        if (b_r1D.size(1) != 0) {
            int acoef;
            int i5;
            acoef = (b_r1D.size(1) != 1);
            i5 = b_r1D.size(1) - 1;
            for (int e_k = 0; e_k <= i5; e_k++) {
                int varargin_2;
                varargin_2 = acoef * e_k;
                c[3 * e_k] = b_r1D[3 * varargin_2] * jps;
                c[3 * e_k + 1] = b_r1D[3 * varargin_2 + 1] * jps;
                c[3 * e_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
            }
        }

        bsxfun(r3D, z1, r3);
        b_d1uk.set_size(1, d1uk.size(1));
        f_loop_ub = d1uk.size(1);
        d_scalarLB = d1uk.size(1) & -4;
        d_vectorUB = d_scalarLB - 4;
        for (i7 = 0; i7 <= d_vectorUB; i7 += 4) {
            __m256d r4;
            __m256d r5;
            r4 = _mm256_loadu_pd(&d1uk[i7]);
            r5 = _mm256_loadu_pd(&d2uk[i7]);
            _mm256_storeu_pd(&b_d1uk[i7], _mm256_mul_pd(r4, r5));
        }

        for (i7 = d_scalarLB; i7 < f_loop_ub; i7++) {
            b_d1uk[i7] = d1uk[i7] * d2uk[i7];
        }

        bsxfun(r2D, b_d1uk, r6);
        a.set_size(r3.size(1), 3);
        g_loop_ub = r3.size(1);
        for (int i8 = 0; i8 < 3; i8++) {
            for (int i9 = 0; i9 < g_loop_ub; i9++) {
                a[i9 + a.size(0) * i8] = (r3[i8 + 3 * i9] + 3.0 * r6[i8 + 3 * i9]) + c[i8 + 3 * i9];
            }
        }

        x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int b_acoef;
            b_acoef = (a.size(0) != 1);
            for (int f_k = 0; f_k < 3; f_k++) {
                int i10;
                i10 = x.size(0) - 1;
                for (int g_k = 0; g_k <= i10; g_k++) {
                    x[g_k + x.size(0) * f_k] = a[b_acoef * g_k + a.size(0) * f_k] / ctx_cfg_jmax[f_k];
                }
            }
        }

        jt.set_size(x.size(0), 3);
        if (x.size(0) != 0) {
            int h_loop_ub;
            int i_loop_ub;
            b_z1.set_size(x.size(0), 3);
            h_loop_ub = x.size(0);
            for (int i11 = 0; i11 < 3; i11++) {
                for (int i12 = 0; i12 < h_loop_ub; i12++) {
                    b_z1[i12 + b_z1.size(0) * i11] = jt[i12 + jt.size(0) * i11];
                }
            }

            for (int i_k = 0; i_k < 3; i_k++) {
                int i13;
                i13 = b_z1.size(0);
                for (int j_k = 0; j_k < i13; j_k++) {
                    b_z1[j_k + b_z1.size(0) * i_k] = std::abs(x[j_k + x.size(0) * i_k]);
                }
            }

            jt.set_size(b_z1.size(0), 3);
            i_loop_ub = b_z1.size(0);
            for (int i14 = 0; i14 < 3; i14++) {
                for (int i16 = 0; i16 < i_loop_ub; i16++) {
                    jt[i16 + jt.size(0) * i14] = b_z1[i16 + b_z1.size(0) * i14];
                }
            }
        }

        z1.set_size(1, d1uk.size(1));
        e_N = d1uk.size(1);
        for (int h_k = 0; h_k < e_N; h_k++) {
            z1[h_k] = std::pow(d1uk[h_k], 2.0);
        }

        bsxfun(r2D, z1, r3);
        bsxfun(b_r1D, d2uk, r6);
        a.set_size(r3.size(1), 3);
        j_loop_ub = r3.size(1);
        for (int i15 = 0; i15 < 3; i15++) {
            for (int i17 = 0; i17 < j_loop_ub; i17++) {
                a[i17 + a.size(0) * i15] = r3[i15 + 3 * i17] + r6[i15 + 3 * i17];
            }
        }

        x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int c_acoef;
            c_acoef = (a.size(0) != 1);
            for (int k_k = 0; k_k < 3; k_k++) {
                int i18;
                i18 = x.size(0) - 1;
                for (int l_k = 0; l_k <= i18; l_k++) {
                    x[l_k + x.size(0) * k_k] = a[c_acoef * l_k + a.size(0) * k_k] / ctx_cfg_amax[k_k];
                }
            }
        }

        at.set_size(x.size(0), 3);
        if (x.size(0) != 0) {
            int k_loop_ub;
            int l_loop_ub;
            b_z1.set_size(x.size(0), 3);
            k_loop_ub = x.size(0);
            for (int i19 = 0; i19 < 3; i19++) {
                for (int i20 = 0; i20 < k_loop_ub; i20++) {
                    b_z1[i20 + b_z1.size(0) * i19] = at[i20 + at.size(0) * i19];
                }
            }

            for (int m_k = 0; m_k < 3; m_k++) {
                int i21;
                i21 = b_z1.size(0);
                for (int n_k = 0; n_k < i21; n_k++) {
                    b_z1[n_k + b_z1.size(0) * m_k] = std::abs(x[n_k + x.size(0) * m_k]);
                }
            }

            at.set_size(b_z1.size(0), 3);
            l_loop_ub = b_z1.size(0);
            for (int i22 = 0; i22 < 3; i22++) {
                for (int i23 = 0; i23 < l_loop_ub; i23++) {
                    at[i23 + at.size(0) * i22] = b_z1[i23 + b_z1.size(0) * i22];
                }
            }
        }

        m = jt.size(0) - 1;
        max_jt.set_size(jt.size(0));
        if (jt.size(0) >= 1) {
            int c_i;
            double d;
            for (int b_i = 0; b_i <= m; b_i++) {
                max_jt[b_i] = jt[b_i];
            }

            for (c_i = 0; c_i <= m; c_i++) {
                d = jt[c_i + jt.size(0)];
                if (max_jt[c_i] < d) {
                    max_jt[c_i] = d;
                }
            }

            for (c_i = 0; c_i <= m; c_i++) {
                d = jt[c_i + jt.size(0) * 2];
                if (max_jt[c_i] < d) {
                    max_jt[c_i] = d;
                }
            }
        }

        b_m = at.size(0) - 1;
        max_at.set_size(at.size(0));
        if (at.size(0) >= 1) {
            int e_i;
            double d1;
            for (int d_i = 0; d_i <= b_m; d_i++) {
                max_at[d_i] = at[d_i];
            }

            for (e_i = 0; e_i <= b_m; e_i++) {
                d1 = at[e_i + at.size(0)];
                if (max_at[e_i] < d1) {
                    max_at[e_i] = d1;
                }
            }

            for (e_i = 0; e_i <= b_m; e_i++) {
                d1 = at[e_i + at.size(0) * 2];
                if (max_at[e_i] < d1) {
                    max_at[e_i] = d1;
                }
            }
        }

        b_max_jt.set_size(1, max_jt.size(0));
        m_loop_ub = max_jt.size(0);
        for (int i24 = 0; i24 < m_loop_ub; i24++) {
            b_max_jt[i24] = (max_jt[i24] > ctx_cfg_ZeroStartJerkLimit);
        }

        b_eml_find(b_max_jt, tmp_data, tmp_size);
        cut_index_jerk_size_idx_1 = tmp_size[1];
        n_loop_ub = tmp_size[1];
        if (0 <= n_loop_ub - 1) {
            std::memcpy(&cut_index_jerk_data[0], &tmp_data[0], n_loop_ub * sizeof(int));
        }

        if (tmp_size[1] == 0) {
            cut_index_jerk_size_idx_1 = 1;
            cut_index_jerk_data[0] = 1;
        }

        b_max_at.set_size(1, max_at.size(0));
        o_loop_ub = max_at.size(0);
        for (int i25 = 0; i25 < o_loop_ub; i25++) {
            b_max_at[i25] = (max_at[i25] > ctx_cfg_ZeroStartAccLimit);
        }

        b_eml_find(b_max_at, tmp_data, tmp_size);
        cut_index_acc_size_idx_1 = tmp_size[1];
        p_loop_ub = tmp_size[1];
        if (0 <= p_loop_ub - 1) {
            std::memcpy(&cut_index_acc_data[0], &tmp_data[0], p_loop_ub * sizeof(int));
        }

        if (tmp_size[1] == 0) {
            cut_index_acc_size_idx_1 = 1;
            cut_index_acc_data[0] = 1;
        }

        bsxfun(b_r1D, d1uk, b_a);
        c_z1.set_size(3, b_a.size(1));
        f_N = b_a.size(1);
        for (int o_k = 0; o_k < f_N; o_k++) {
            c_z1[3 * o_k] = std::pow(b_a[3 * o_k], 2.0);
            c_z1[3 * o_k + 1] = std::pow(b_a[3 * o_k + 1], 2.0);
            c_z1[3 * o_k + 2] = std::pow(b_a[3 * o_k + 2], 2.0);
        }

        sum(c_z1, b_x);
        i26 = b_x.size(1);
        e_scalarLB = b_x.size(1) & -4;
        e_vectorUB = e_scalarLB - 4;
        for (p_k = 0; p_k <= e_vectorUB; p_k += 4) {
            __m256d r7;
            r7 = _mm256_loadu_pd(&b_x[p_k]);
            _mm256_storeu_pd(&b_x[p_k], _mm256_sqrt_pd(r7));
        }

        for (p_k = e_scalarLB; p_k < i26; p_k++) {
            b_x[p_k] = std::sqrt(b_x[p_k]);
        }

        c_x.set_size(1, b_x.size(1));
        q_loop_ub = b_x.size(1);
        for (int i27 = 0; i27 < q_loop_ub; i27++) {
            c_x[i27] = (b_x[i27] / b_vmax > ctx_cfg_ZeroStartVelLimit);
        }

        b_eml_find(c_x, tmp_data, tmp_size);
        cut_index_vel_size_idx_1 = tmp_size[1];
        r_loop_ub = tmp_size[1];
        if (0 <= r_loop_ub - 1) {
            std::memcpy(&cut_index_vel_data[0], &tmp_data[0], r_loop_ub * sizeof(int));
        }

        if (tmp_size[1] == 0) {
            cut_index_vel_size_idx_1 = 1;
            cut_index_vel_data[0] = 1;
        }

        if (0 <= cut_index_acc_size_idx_1 - 1) {
            std::memcpy(&varargin_1_data[0], &cut_index_acc_data[0], cut_index_acc_size_idx_1 *
                        sizeof(int));
        }

        for (int i28 = 0; i28 < cut_index_jerk_size_idx_1; i28++) {
            varargin_1_data[i28 + cut_index_acc_size_idx_1] = cut_index_jerk_data[i28];
        }

        for (int i29 = 0; i29 < cut_index_vel_size_idx_1; i29++) {
            varargin_1_data[(i29 + cut_index_acc_size_idx_1) + cut_index_jerk_size_idx_1] =
                cut_index_vel_data[i29];
        }

        c_ex = varargin_1_data[0];
        if (varargin_1_data[0] < varargin_1_data[1]) {
            c_ex = varargin_1_data[1];
        }

        if (c_ex < varargin_1_data[2]) {
            c_ex = varargin_1_data[2];
        }

        cut_index = (max_at.size(0) - static_cast<int>(std::fmax(2.0, (static_cast<double>
                        (max_at.size(0)) - static_cast<double>(c_ex)) + 1.0))) - 1;

        //      actual_jps = jps;
        //      cut_index = N + 1 - cut_index;
        L = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->Type,
                       b_CurvStruct->P0, b_CurvStruct->P1, b_CurvStruct->evec, b_CurvStruct->theta,
                       b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                       b_CurvStruct->a_param, b_CurvStruct->b_param);
        *CurvStruct1 = *b_CurvStruct;
        CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1, uk[cut_index] * L);
        *CurvStruct2 = *b_CurvStruct;
        b_CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2, L - uk[cut_index] * L);
        CurvStruct2->ConstJerkMaxIterations = max_at.size(0) - cut_index;
        CurvStruct2->UseConstJerk = true;
        CurvStruct2->ConstJerk = 6.0 / std::pow(t[cut_index], 3.0);
        CurvStruct1->zspdmode = ZSpdMode_NN;
        CurvStruct2->zspdmode = ZSpdMode_NZ;
        CurvStruct1->gcode_source_line = b_CurvStruct->gcode_source_line;
        CurvStruct2->gcode_source_line = b_CurvStruct->gcode_source_line;
    }

    //
    // Arguments    : const queue_coder *ctx_q_gcode
    //                const queue_coder *ctx_q_splines
    //                int ctx_cfg_NHorz
    //                const double ctx_cfg_amax[3]
    //                const double ctx_cfg_jmax[3]
    //                double ctx_cfg_dt
    //                double ctx_cfg_ZeroStartAccLimit
    //                double ctx_cfg_ZeroStartJerkLimit
    //                double ctx_cfg_ZeroStartVelLimit
    //                bool ctx_cfg_DebugCutZero
    //                double ctx_cfg_NGridLengthSpline
    //                const CurvStruct *b_CurvStruct
    //                CurvStruct *CurvStruct1
    //                CurvStruct *CurvStruct2
    // Return Type  : void
    //
    static void b_CutZeroStart(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int
        ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3], double ctx_cfg_dt,
        double ctx_cfg_ZeroStartAccLimit, double ctx_cfg_ZeroStartJerkLimit, double
        ctx_cfg_ZeroStartVelLimit, bool ctx_cfg_DebugCutZero, double ctx_cfg_NGridLengthSpline,
        const CurvStruct *b_CurvStruct, CurvStruct *CurvStruct1, CurvStruct *CurvStruct2)
    {
        double unusedU0[3];
        double r1D[3];
        double ex;
        double z1_idx_1;
        double z1_idx_2;
        double ex_tmp;
        double b_ex;
        double tmax;
        double jps;
        coder::array<double, 2U> t;
        coder::array<double, 2U> z1;
        int N;
        coder::array<double, 2U> uk;
        int b_loop_ub;
        int scalarLB;
        int vectorUB;
        int i1;
        int b_N;
        coder::array<double, 2U> d1uk;
        int c_loop_ub;
        int b_scalarLB;
        int b_vectorUB;
        int i2;
        coder::array<double, 2U> d2uk;
        int d_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int i3;
        coder::array<double, 2U> b_uk;
        int e_loop_ub;
        coder::array<double, 2U> unusedU1;
        coder::array<double, 2U> b_r1D;
        coder::array<double, 2U> r2D;
        coder::array<double, 2U> r3D;
        double b_vmax;
        long y;
        long c_N;
        long c_k;
        bool exitg1;
        CurvStruct expl_temp;
        int d_N;
        double TmpCurv_P0[3];
        double TmpCurv_P1[3];
        double TmpCurv_evec[3];
        coder::array<double, 2U> c;
        coder::array<double, 2U> r3;
        coder::array<double, 2U> b_d1uk;
        int f_loop_ub;
        int d_scalarLB;
        int d_vectorUB;
        int i7;
        double TmpCurv_CoeffP5[6][3];
        coder::array<double, 2U> r6;
        coder::array<double, 2U> a;
        int g_loop_ub;
        coder::array<double, 2U> x;
        coder::array<double, 2U> jt;
        coder::array<double, 2U> b_z1;
        int e_N;
        int j_loop_ub;
        coder::array<double, 2U> at;
        coder::array<double, 2U> b_a;
        coder::array<double, 2U> c_z1;
        int f_N;
        coder::array<double, 2U> b_x;
        int i22;
        int e_scalarLB;
        int e_vectorUB;
        int p_k;
        coder::array<double, 1U> norm_vt;
        int m_loop_ub;
        int f_scalarLB;
        int f_vectorUB;
        int i25;
        int m;
        coder::array<double, 1U> max_jt;
        int b_m;
        coder::array<double, 1U> max_at;
        coder::array<bool, 2U> b_max_jt;
        int n_loop_ub;
        int tmp_data[1];
        int tmp_size[2];
        int cut_index_jerk_size_idx_1;
        int o_loop_ub;
        int cut_index_jerk_data[1];
        coder::array<bool, 2U> b_max_at;
        int p_loop_ub;
        int cut_index_acc_size_idx_1;
        int q_loop_ub;
        int cut_index_acc_data[1];
        coder::array<bool, 2U> b_norm_vt;
        int r_loop_ub;
        int cut_index_vel_size_idx_1;
        int s_loop_ub;
        int cut_index_vel_data[1];
        int varargin_1_data[3];
        int c_ex;
        int u0;
        int u1;
        int cut_index;
        double L;
        f_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                         b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                         b_CurvStruct->b_param, unusedU0, r1D);
        ex = ctx_cfg_jmax[0];
        if (ctx_cfg_jmax[0] > ctx_cfg_jmax[1]) {
            ex = ctx_cfg_jmax[1];
        }

        if (ex > ctx_cfg_jmax[2]) {
            ex = ctx_cfg_jmax[2];
        }

        z1_idx_1 = std::abs(r1D[1]);
        z1_idx_2 = std::abs(r1D[2]);
        ex_tmp = std::abs(r1D[0]);
        b_ex = ex_tmp;
        if (ex_tmp < z1_idx_1) {
            b_ex = z1_idx_1;
        }

        if (b_ex < z1_idx_2) {
            b_ex = z1_idx_2;
        }

        tmax = std::ceil(std::pow(6.0 / (ex / b_ex), 0.33333333333333331) / ctx_cfg_dt) * ctx_cfg_dt;
        jps = 6.0 / std::pow(tmax, 3.0);
        if ((ctx_cfg_dt == 0.0) || ((0.0 < tmax) && (ctx_cfg_dt < 0.0)) || ((tmax < 0.0) &&
                (ctx_cfg_dt > 0.0))) {
            t.set_size(1, 0);
        } else if (std::floor(ctx_cfg_dt) == ctx_cfg_dt) {
            int loop_ub;
            loop_ub = static_cast<int>(std::floor(tmax / ctx_cfg_dt));
            t.set_size(1, (loop_ub + 1));
            for (int i = 0; i <= loop_ub; i++) {
                t[i] = ctx_cfg_dt * static_cast<double>(i);
            }
        } else {
            eml_float_colon(ctx_cfg_dt, tmax, t);
        }

        z1.set_size(1, t.size(1));
        N = t.size(1);
        for (int k = 0; k < N; k++) {
            z1[k] = std::pow(t[k], 3.0);
        }

        uk.set_size(1, z1.size(1));
        b_loop_ub = z1.size(1);
        scalarLB = z1.size(1) & -4;
        vectorUB = scalarLB - 4;
        for (i1 = 0; i1 <= vectorUB; i1 += 4) {
            __m256d r;
            r = _mm256_loadu_pd(&z1[i1]);
            _mm256_storeu_pd(&uk[i1], _mm256_div_pd(_mm256_mul_pd(_mm256_set1_pd(jps), r),
                              _mm256_set1_pd(6.0)));
        }

        for (i1 = scalarLB; i1 < b_loop_ub; i1++) {
            uk[i1] = jps * z1[i1] / 6.0;
        }

        z1.set_size(1, t.size(1));
        b_N = t.size(1);
        for (int b_k = 0; b_k < b_N; b_k++) {
            z1[b_k] = std::pow(t[b_k], 2.0);
        }

        d1uk.set_size(1, z1.size(1));
        c_loop_ub = z1.size(1);
        b_scalarLB = z1.size(1) & -4;
        b_vectorUB = b_scalarLB - 4;
        for (i2 = 0; i2 <= b_vectorUB; i2 += 4) {
            __m256d r1;
            r1 = _mm256_loadu_pd(&z1[i2]);
            _mm256_storeu_pd(&d1uk[i2], _mm256_div_pd(_mm256_mul_pd(_mm256_set1_pd(jps), r1),
                              _mm256_set1_pd(2.0)));
        }

        for (i2 = b_scalarLB; i2 < c_loop_ub; i2++) {
            d1uk[i2] = jps * z1[i2] / 2.0;
        }

        d2uk.set_size(1, t.size(1));
        d_loop_ub = t.size(1);
        c_scalarLB = t.size(1) & -4;
        c_vectorUB = c_scalarLB - 4;
        for (i3 = 0; i3 <= c_vectorUB; i3 += 4) {
            __m256d r2;
            r2 = _mm256_loadu_pd(&t[i3]);
            _mm256_storeu_pd(&d2uk[i3], _mm256_mul_pd(_mm256_set1_pd(jps), r2));
        }

        for (i3 = c_scalarLB; i3 < d_loop_ub; i3++) {
            d2uk[i3] = jps * t[i3];
        }

        b_uk.set_size(1, uk.size(1));
        e_loop_ub = uk.size(1) - 1;
        for (int i4 = 0; i4 <= e_loop_ub; i4++) {
            b_uk[i4] = uk[i4];
        }

        h_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                         b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                         b_CurvStruct->b_param, b_uk, unusedU1, b_r1D, r2D, r3D);
        b_vmax = b_CurvStruct->FeedRate;
        y = ctx_q_gcode->size();
        if (ctx_cfg_NHorz > y) {
            c_N = y;
        } else {
            c_N = ctx_cfg_NHorz;
        }

        c_k = 1L;
        exitg1 = false;
        while ((!exitg1) && (c_k <= c_N)) {
            ctx_q_gcode->get(c_k, (&expl_temp));
            TmpCurv_P0[0] = expl_temp.P0[0];
            TmpCurv_P1[0] = expl_temp.P1[0];
            TmpCurv_evec[0] = expl_temp.evec[0];
            TmpCurv_P0[1] = expl_temp.P0[1];
            TmpCurv_P1[1] = expl_temp.P1[1];
            TmpCurv_evec[1] = expl_temp.evec[1];
            TmpCurv_P0[2] = expl_temp.P0[2];
            TmpCurv_P1[2] = expl_temp.P1[2];
            TmpCurv_evec[2] = expl_temp.evec[2];
            for (int i6 = 0; i6 < 6; i6++) {
                TmpCurv_CoeffP5[i6][0] = expl_temp.CoeffP5[i6][0];
                TmpCurv_CoeffP5[i6][1] = expl_temp.CoeffP5[i6][1];
                TmpCurv_CoeffP5[i6][2] = expl_temp.CoeffP5[i6][2];
            }

            double b_y;
            b_y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                TmpCurv_P0, TmpCurv_P1, TmpCurv_evec, expl_temp.theta, expl_temp.pitch,
                TmpCurv_CoeffP5, expl_temp.sp_index, expl_temp.FeedRate, expl_temp.a_param,
                expl_temp.b_param);
            b_vmax = std::fmin(b_vmax, b_y);
            if (expl_temp.zspdmode == ZSpdMode_NZ) {
                exitg1 = true;
            } else {
                c_k++;
            }
        }

        z1.set_size(1, d1uk.size(1));
        d_N = d1uk.size(1);
        for (int d_k = 0; d_k < d_N; d_k++) {
            z1[d_k] = std::pow(d1uk[d_k], 3.0);
        }

        c.set_size(3, b_r1D.size(1));
        if (b_r1D.size(1) != 0) {
            int acoef;
            int i5;
            acoef = (b_r1D.size(1) != 1);
            i5 = b_r1D.size(1) - 1;
            for (int e_k = 0; e_k <= i5; e_k++) {
                int varargin_2;
                varargin_2 = acoef * e_k;
                c[3 * e_k] = b_r1D[3 * varargin_2] * jps;
                c[3 * e_k + 1] = b_r1D[3 * varargin_2 + 1] * jps;
                c[3 * e_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
            }
        }

        bsxfun(r3D, z1, r3);
        b_d1uk.set_size(1, d1uk.size(1));
        f_loop_ub = d1uk.size(1);
        d_scalarLB = d1uk.size(1) & -4;
        d_vectorUB = d_scalarLB - 4;
        for (i7 = 0; i7 <= d_vectorUB; i7 += 4) {
            __m256d r4;
            __m256d r5;
            r4 = _mm256_loadu_pd(&d1uk[i7]);
            r5 = _mm256_loadu_pd(&d2uk[i7]);
            _mm256_storeu_pd(&b_d1uk[i7], _mm256_mul_pd(r4, r5));
        }

        for (i7 = d_scalarLB; i7 < f_loop_ub; i7++) {
            b_d1uk[i7] = d1uk[i7] * d2uk[i7];
        }

        bsxfun(r2D, b_d1uk, r6);
        a.set_size(r3.size(1), 3);
        g_loop_ub = r3.size(1);
        for (int i8 = 0; i8 < 3; i8++) {
            for (int i9 = 0; i9 < g_loop_ub; i9++) {
                a[i9 + a.size(0) * i8] = (r3[i8 + 3 * i9] + 3.0 * r6[i8 + 3 * i9]) + c[i8 + 3 * i9];
            }
        }

        x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int b_acoef;
            b_acoef = (a.size(0) != 1);
            for (int f_k = 0; f_k < 3; f_k++) {
                int i10;
                i10 = x.size(0) - 1;
                for (int g_k = 0; g_k <= i10; g_k++) {
                    x[g_k + x.size(0) * f_k] = a[b_acoef * g_k + a.size(0) * f_k] / ctx_cfg_jmax[f_k];
                }
            }
        }

        jt.set_size(x.size(0), 3);
        if (x.size(0) != 0) {
            int h_loop_ub;
            int i_loop_ub;
            b_z1.set_size(x.size(0), 3);
            h_loop_ub = x.size(0);
            for (int i11 = 0; i11 < 3; i11++) {
                for (int i12 = 0; i12 < h_loop_ub; i12++) {
                    b_z1[i12 + b_z1.size(0) * i11] = jt[i12 + jt.size(0) * i11];
                }
            }

            for (int i_k = 0; i_k < 3; i_k++) {
                int i13;
                i13 = b_z1.size(0);
                for (int j_k = 0; j_k < i13; j_k++) {
                    b_z1[j_k + b_z1.size(0) * i_k] = std::abs(x[j_k + x.size(0) * i_k]);
                }
            }

            jt.set_size(b_z1.size(0), 3);
            i_loop_ub = b_z1.size(0);
            for (int i14 = 0; i14 < 3; i14++) {
                for (int i16 = 0; i16 < i_loop_ub; i16++) {
                    jt[i16 + jt.size(0) * i14] = b_z1[i16 + b_z1.size(0) * i14];
                }
            }
        }

        z1.set_size(1, d1uk.size(1));
        e_N = d1uk.size(1);
        for (int h_k = 0; h_k < e_N; h_k++) {
            z1[h_k] = std::pow(d1uk[h_k], 2.0);
        }

        bsxfun(r2D, z1, r3);
        bsxfun(b_r1D, d2uk, r6);
        a.set_size(r3.size(1), 3);
        j_loop_ub = r3.size(1);
        for (int i15 = 0; i15 < 3; i15++) {
            for (int i17 = 0; i17 < j_loop_ub; i17++) {
                a[i17 + a.size(0) * i15] = r3[i15 + 3 * i17] + r6[i15 + 3 * i17];
            }
        }

        x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int c_acoef;
            c_acoef = (a.size(0) != 1);
            for (int k_k = 0; k_k < 3; k_k++) {
                int i18;
                i18 = x.size(0) - 1;
                for (int l_k = 0; l_k <= i18; l_k++) {
                    x[l_k + x.size(0) * k_k] = a[c_acoef * l_k + a.size(0) * k_k] / ctx_cfg_amax[k_k];
                }
            }
        }

        at.set_size(x.size(0), 3);
        if (x.size(0) != 0) {
            int k_loop_ub;
            int l_loop_ub;
            b_z1.set_size(x.size(0), 3);
            k_loop_ub = x.size(0);
            for (int i19 = 0; i19 < 3; i19++) {
                for (int i20 = 0; i20 < k_loop_ub; i20++) {
                    b_z1[i20 + b_z1.size(0) * i19] = at[i20 + at.size(0) * i19];
                }
            }

            for (int n_k = 0; n_k < 3; n_k++) {
                int i21;
                i21 = b_z1.size(0);
                for (int o_k = 0; o_k < i21; o_k++) {
                    b_z1[o_k + b_z1.size(0) * n_k] = std::abs(x[o_k + x.size(0) * n_k]);
                }
            }

            at.set_size(b_z1.size(0), 3);
            l_loop_ub = b_z1.size(0);
            for (int i23 = 0; i23 < 3; i23++) {
                for (int i24 = 0; i24 < l_loop_ub; i24++) {
                    at[i24 + at.size(0) * i23] = b_z1[i24 + b_z1.size(0) * i23];
                }
            }
        }

        bsxfun(b_r1D, d1uk, b_a);
        c_z1.set_size(3, b_a.size(1));
        f_N = b_a.size(1);
        for (int m_k = 0; m_k < f_N; m_k++) {
            c_z1[3 * m_k] = std::pow(b_a[3 * m_k], 2.0);
            c_z1[3 * m_k + 1] = std::pow(b_a[3 * m_k + 1], 2.0);
            c_z1[3 * m_k + 2] = std::pow(b_a[3 * m_k + 2], 2.0);
        }

        sum(c_z1, b_x);
        i22 = b_x.size(1);
        e_scalarLB = b_x.size(1) & -4;
        e_vectorUB = e_scalarLB - 4;
        for (p_k = 0; p_k <= e_vectorUB; p_k += 4) {
            __m256d r7;
            r7 = _mm256_loadu_pd(&b_x[p_k]);
            _mm256_storeu_pd(&b_x[p_k], _mm256_sqrt_pd(r7));
        }

        for (p_k = e_scalarLB; p_k < i22; p_k++) {
            b_x[p_k] = std::sqrt(b_x[p_k]);
        }

        norm_vt.set_size(b_x.size(1));
        m_loop_ub = b_x.size(1);
        f_scalarLB = b_x.size(1) & -4;
        f_vectorUB = f_scalarLB - 4;
        for (i25 = 0; i25 <= f_vectorUB; i25 += 4) {
            __m256d r8;
            r8 = _mm256_loadu_pd(&b_x[i25]);
            _mm256_storeu_pd(&norm_vt[i25], _mm256_div_pd(r8, _mm256_set1_pd(b_vmax)));
        }

        for (i25 = f_scalarLB; i25 < m_loop_ub; i25++) {
            norm_vt[i25] = b_x[i25] / b_vmax;
        }

        m = jt.size(0) - 1;
        max_jt.set_size(jt.size(0));
        if (jt.size(0) >= 1) {
            int c_i;
            double d;
            for (int b_i = 0; b_i <= m; b_i++) {
                max_jt[b_i] = jt[b_i];
            }

            for (c_i = 0; c_i <= m; c_i++) {
                d = jt[c_i + jt.size(0)];
                if (max_jt[c_i] < d) {
                    max_jt[c_i] = d;
                }
            }

            for (c_i = 0; c_i <= m; c_i++) {
                d = jt[c_i + jt.size(0) * 2];
                if (max_jt[c_i] < d) {
                    max_jt[c_i] = d;
                }
            }
        }

        b_m = at.size(0) - 1;
        max_at.set_size(at.size(0));
        if (at.size(0) >= 1) {
            int e_i;
            double d1;
            for (int d_i = 0; d_i <= b_m; d_i++) {
                max_at[d_i] = at[d_i];
            }

            for (e_i = 0; e_i <= b_m; e_i++) {
                d1 = at[e_i + at.size(0)];
                if (max_at[e_i] < d1) {
                    max_at[e_i] = d1;
                }
            }

            for (e_i = 0; e_i <= b_m; e_i++) {
                d1 = at[e_i + at.size(0) * 2];
                if (max_at[e_i] < d1) {
                    max_at[e_i] = d1;
                }
            }
        }

        b_max_jt.set_size(1, max_jt.size(0));
        n_loop_ub = max_jt.size(0);
        for (int i26 = 0; i26 < n_loop_ub; i26++) {
            b_max_jt[i26] = (max_jt[i26] > ctx_cfg_ZeroStartJerkLimit);
        }

        eml_find(b_max_jt, tmp_data, tmp_size);
        cut_index_jerk_size_idx_1 = tmp_size[1];
        o_loop_ub = tmp_size[1];
        if (0 <= o_loop_ub - 1) {
            std::memcpy(&cut_index_jerk_data[0], &tmp_data[0], o_loop_ub * sizeof(int));
        }

        if (tmp_size[1] == 0) {
            cut_index_jerk_size_idx_1 = 1;
            cut_index_jerk_data[0] = max_jt.size(0);
        }

        b_max_at.set_size(1, max_at.size(0));
        p_loop_ub = max_at.size(0);
        for (int i27 = 0; i27 < p_loop_ub; i27++) {
            b_max_at[i27] = (max_at[i27] > ctx_cfg_ZeroStartAccLimit);
        }

        eml_find(b_max_at, tmp_data, tmp_size);
        cut_index_acc_size_idx_1 = tmp_size[1];
        q_loop_ub = tmp_size[1];
        if (0 <= q_loop_ub - 1) {
            std::memcpy(&cut_index_acc_data[0], &tmp_data[0], q_loop_ub * sizeof(int));
        }

        if (tmp_size[1] == 0) {
            cut_index_acc_size_idx_1 = 1;
            cut_index_acc_data[0] = max_jt.size(0);
        }

        b_norm_vt.set_size(1, norm_vt.size(0));
        r_loop_ub = norm_vt.size(0);
        for (int i28 = 0; i28 < r_loop_ub; i28++) {
            b_norm_vt[i28] = (norm_vt[i28] > ctx_cfg_ZeroStartVelLimit);
        }

        eml_find(b_norm_vt, tmp_data, tmp_size);
        cut_index_vel_size_idx_1 = tmp_size[1];
        s_loop_ub = tmp_size[1];
        if (0 <= s_loop_ub - 1) {
            std::memcpy(&cut_index_vel_data[0], &tmp_data[0], s_loop_ub * sizeof(int));
        }

        if (tmp_size[1] == 0) {
            cut_index_vel_size_idx_1 = 1;
            cut_index_vel_data[0] = max_jt.size(0);
        }

        if (0 <= cut_index_acc_size_idx_1 - 1) {
            std::memcpy(&varargin_1_data[0], &cut_index_acc_data[0], cut_index_acc_size_idx_1 *
                        sizeof(int));
        }

        for (int i29 = 0; i29 < cut_index_jerk_size_idx_1; i29++) {
            varargin_1_data[i29 + cut_index_acc_size_idx_1] = cut_index_jerk_data[i29];
        }

        for (int i30 = 0; i30 < cut_index_vel_size_idx_1; i30++) {
            varargin_1_data[(i30 + cut_index_acc_size_idx_1) + cut_index_jerk_size_idx_1] =
                cut_index_vel_data[i30];
        }

        c_ex = varargin_1_data[0];
        if (varargin_1_data[0] > varargin_1_data[1]) {
            c_ex = varargin_1_data[1];
        }

        if (c_ex > varargin_1_data[2]) {
            c_ex = varargin_1_data[2];
        }

        u0 = static_cast<int>(std::round(static_cast<double>(max_jt.size(0)) / 2.0));
        if (2 < c_ex - 1) {
            u1 = c_ex - 1;
        } else {
            u1 = 2;
        }

        if (u0 < u1) {
            cut_index = u0;
        } else {
            cut_index = u1;
        }

        L = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->Type,
                       b_CurvStruct->P0, b_CurvStruct->P1, b_CurvStruct->evec, b_CurvStruct->theta,
                       b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                       b_CurvStruct->a_param, b_CurvStruct->b_param);
        *CurvStruct1 = *b_CurvStruct;
        CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1, L - uk[cut_index - 1] *
                      L);
        CurvStruct1->UseConstJerk = true;
        CurvStruct1->ConstJerk = 6.0 / std::pow(t[cut_index - 1], 3.0);

        //      CurvStruct1.ConstJerkTime = t_cut;
        CurvStruct1->ConstJerkMaxIterations = cut_index;
        *CurvStruct2 = *b_CurvStruct;
        b_CutCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2, uk[cut_index - 1] * L);
        CurvStruct1->zspdmode = ZSpdMode_ZN;
        CurvStruct2->zspdmode = ZSpdMode_NN;
        CurvStruct1->gcode_source_line = b_CurvStruct->gcode_source_line;
        CurvStruct2->gcode_source_line = b_CurvStruct->gcode_source_line;
        if (ctx_cfg_DebugCutZero) {
            printf("======== CUT ZERO START =========\n");
            fflush(stdout);
            printf("Initial: \n");
            fflush(stdout);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->Type,
                              b_CurvStruct->zspdmode, b_CurvStruct->P0, b_CurvStruct->P1,
                              b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                              b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->FeedRate,
                              b_CurvStruct->UseConstJerk, b_CurvStruct->ConstJerk,
                              b_CurvStruct->a_param, b_CurvStruct->b_param);
            printf("\nCut:\n");
            fflush(stdout);
            printf("Index = %d, t_cut = %e, vmax = %.1f\n", cut_index, t[cut_index - 1], b_vmax);
            fflush(stdout);
            printf("jps = %e, norm_vt(%d) = %f\n", jps, cut_index, norm_vt[cut_index - 1]);
            fflush(stdout);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1->Type,
                              ZSpdMode_ZN, CurvStruct1->P0, CurvStruct1->P1, CurvStruct1->evec,
                              CurvStruct1->theta, CurvStruct1->pitch, CurvStruct1->CoeffP5,
                              CurvStruct1->sp_index, CurvStruct1->FeedRate, true,
                              CurvStruct1->ConstJerk, CurvStruct1->a_param, CurvStruct1->b_param);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2->Type,
                              ZSpdMode_NN, CurvStruct2->P0, CurvStruct2->P1, CurvStruct2->evec,
                              CurvStruct2->theta, CurvStruct2->pitch, CurvStruct2->CoeffP5,
                              CurvStruct2->sp_index, CurvStruct2->FeedRate,
                              CurvStruct2->UseConstJerk, CurvStruct2->ConstJerk,
                              CurvStruct2->a_param, CurvStruct2->b_param);
        }
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double CurvStruct_CoeffP5[6][3]
    //                int CurvStruct_sp_index
    //                double CurvStruct_b_param
    //                double r0D[3]
    // Return Type  : void
    //
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_b_param, double r0D[3])
    {
        double r1D[3];
        double r2D[3];
        double r3D[3];
        CurvStruct expl_temp;
        char message[30];
        coder::array<double, 2U> Spline_sp_CoeffX;
        coder::array<double, 2U> Spline_sp_CoeffY;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        double r0Dx;
        double r1Dx;
        double r2Dx;
        double r3Dx;
        double r0Dy;
        double r1Dy;
        double r2Dy;
        double r3Dy;
        double r0Dz;
        double r1Dz;
        double r2Dz;
        double r3Dz;

        //
        //
        r0D[0] = 0.0;
        r0D[1] = 0.0;
        r0D[2] = 0.0;
        switch (CurvStruct_Type) {
          case CurveType_Line:
            //  line (G01)
            //
            //  parametrization of a straight line between P0 and P1
            //
            r0D[0] = CurvStruct_P1[0] * CurvStruct_b_param + CurvStruct_P0[0] * (1.0 -
                CurvStruct_b_param);
            r0D[1] = CurvStruct_P1[1] * CurvStruct_b_param + CurvStruct_P0[1] * (1.0 -
                CurvStruct_b_param);
            r0D[2] = CurvStruct_P1[2] * CurvStruct_b_param + CurvStruct_P0[2] * (1.0 -
                CurvStruct_b_param);

            //
            //
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            b_EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_evec, CurvStruct_theta,
                        CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            b_EvalTransP5(CurvStruct_CoeffP5, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            {
                int loop_ub;
                int b_loop_ub;
                int c_loop_ub;

                //  BSpline
                ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
                Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
                loop_ub = expl_temp.sp.CoeffX.size(1);
                for (int i1 = 0; i1 < loop_ub; i1++) {
                    Spline_sp_CoeffX[i1] = expl_temp.sp.CoeffX[i1];
                }

                Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
                b_loop_ub = expl_temp.sp.CoeffY.size(1);
                for (int i2 = 0; i2 < b_loop_ub; i2++) {
                    Spline_sp_CoeffY[i2] = expl_temp.sp.CoeffY[i2];
                }

                Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
                c_loop_ub = expl_temp.sp.CoeffZ.size(1);
                for (int i3 = 0; i3 < c_loop_ub; i3++) {
                    Spline_sp_CoeffZ[i3] = expl_temp.sp.CoeffZ[i3];
                }

                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, CurvStruct_b_param,
                                   &r0Dx, &r1Dx, &r2Dx, &r3Dx);
                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, CurvStruct_b_param,
                                   &r0Dy, &r1Dy, &r2Dy, &r3Dy);
                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, CurvStruct_b_param,
                                   &r0Dz, &r1Dz, &r2Dz, &r3Dz);
                r0D[0] = r0Dx;
                r0D[1] = r0Dy;
                r0D[2] = r0Dz;
            }
            break;

          default:
            for (int i = 0; i < 30; i++) {
                message[i] = cv[i];
            }

            c_assert_(&message[0]);
            break;
        }
    }

    //
    // Arguments    : const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                double u_vec
    //                double r0D[3]
    //                double r1D[3]
    //                double r2D[3]
    //                double r3D[3]
    // Return Type  : void
    //
    static void b_EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const
                            double CurvStruct_evec[3], double CurvStruct_theta, double
                            CurvStruct_pitch, double u_vec, double r0D[3], double r1D[3], double
                            r2D[3], double r3D[3])
    {
        double P0P1_idx_0;
        double P0P1_idx_1;
        double P0P1_idx_2;
        double EcrP0P1_idx_0;
        double EcrP0P1_idx_1;
        double EcrP0P1_idx_2;
        char message[16];

        //
        P0P1_idx_0 = CurvStruct_P1[0] - CurvStruct_P0[0];
        r0D[0] = 0.0;
        r1D[0] = 0.0;
        r2D[0] = 0.0;
        r3D[0] = 0.0;
        P0P1_idx_1 = CurvStruct_P1[1] - CurvStruct_P0[1];
        r0D[1] = 0.0;
        r1D[1] = 0.0;
        r2D[1] = 0.0;
        r3D[1] = 0.0;
        P0P1_idx_2 = CurvStruct_P1[2] - CurvStruct_P0[2];
        r0D[2] = 0.0;
        r1D[2] = 0.0;
        r2D[2] = 0.0;
        r3D[2] = 0.0;
        EcrP0P1_idx_0 = CurvStruct_evec[1] * P0P1_idx_2 - CurvStruct_evec[2] * P0P1_idx_1;
        EcrP0P1_idx_1 = CurvStruct_evec[2] * P0P1_idx_0 - CurvStruct_evec[0] * P0P1_idx_2;
        EcrP0P1_idx_2 = CurvStruct_evec[0] * P0P1_idx_1 - CurvStruct_evec[1] * P0P1_idx_0;
        if (std::sqrt((std::pow(EcrP0P1_idx_0, 2.0) + std::pow(EcrP0P1_idx_1, 2.0)) + std::pow
                      (EcrP0P1_idx_2, 2.0)) <= 2.2204460492503131E-16) {
            for (int i = 0; i < 16; i++) {
                message[i] = cv1[i];
            }

            c_assert_(&message[0]);
        } else {
            double P0P1;
            double a;
            double d;
            double C_idx_0;
            double CP0_idx_0;
            double C_idx_1;
            double CP0_idx_1;
            double CP0_idx_2;
            double phi_vec;
            double EcrCP0_idx_0;
            double EcrCP0_idx_1;
            double EcrCP0_idx_2;
            double b_a;
            double c_a;
            double cphiTCP0_idx_0;
            double sphiTCP0_idx_0;
            double cphiTCP0_idx_1;
            double sphiTCP0_idx_1;
            double cphiTCP0_idx_2;
            double sphiTCP0_idx_2;
            double cphiTEcrCP0_idx_0;
            double sphiTEcrCP0_idx_0;
            double cphiTEcrCP0_idx_1;
            double sphiTEcrCP0_idx_1;
            double cphiTEcrCP0_idx_2;
            double sphiTEcrCP0_idx_2;
            double d_a;
            double a_tmp;
            double b_a_tmp;
            double r0D_tmp;

            //  if pitch == 0
            //      if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
            //          return;
            //      end
            //  end
            //
            P0P1 = (P0P1_idx_0 * CurvStruct_evec[0] + P0P1_idx_1 * CurvStruct_evec[1]) + P0P1_idx_2 *
                CurvStruct_evec[2];
            a = 1.0 / std::tan(CurvStruct_theta / 2.0);
            d = ((CurvStruct_P0[0] + (CurvStruct_P1[0] - P0P1 * CurvStruct_evec[0])) + a *
                 EcrP0P1_idx_0) / 2.0;
            C_idx_0 = d;
            CP0_idx_0 = CurvStruct_P0[0] - d;
            d = ((CurvStruct_P0[1] + (CurvStruct_P1[1] - P0P1 * CurvStruct_evec[1])) + a *
                 EcrP0P1_idx_1) / 2.0;
            C_idx_1 = d;
            CP0_idx_1 = CurvStruct_P0[1] - d;
            d = ((CurvStruct_P0[2] + (CurvStruct_P1[2] - P0P1 * CurvStruct_evec[2])) + a *
                 EcrP0P1_idx_2) / 2.0;
            CP0_idx_2 = CurvStruct_P0[2] - d;
            phi_vec = CurvStruct_theta * u_vec;
            EcrCP0_idx_0 = CurvStruct_evec[1] * CP0_idx_2 - CurvStruct_evec[2] * CP0_idx_1;
            EcrCP0_idx_1 = CurvStruct_evec[2] * CP0_idx_0 - CurvStruct_evec[0] * CP0_idx_2;
            EcrCP0_idx_2 = CurvStruct_evec[0] * CP0_idx_1 - CurvStruct_evec[1] * CP0_idx_0;
            b_a = std::cos(phi_vec);
            c_a = std::sin(phi_vec);

            //
            cphiTCP0_idx_0 = b_a * CP0_idx_0;
            sphiTCP0_idx_0 = c_a * CP0_idx_0;
            cphiTCP0_idx_1 = b_a * CP0_idx_1;
            sphiTCP0_idx_1 = c_a * CP0_idx_1;
            cphiTCP0_idx_2 = b_a * CP0_idx_2;
            sphiTCP0_idx_2 = c_a * CP0_idx_2;
            cphiTEcrCP0_idx_0 = b_a * EcrCP0_idx_0;
            sphiTEcrCP0_idx_0 = c_a * EcrCP0_idx_0;
            cphiTEcrCP0_idx_1 = b_a * EcrCP0_idx_1;
            sphiTEcrCP0_idx_1 = c_a * EcrCP0_idx_1;
            cphiTEcrCP0_idx_2 = b_a * EcrCP0_idx_2;
            sphiTEcrCP0_idx_2 = c_a * EcrCP0_idx_2;

            //
            d_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
            a_tmp = std::pow(CurvStruct_theta, 2.0);
            b_a_tmp = std::pow(CurvStruct_theta, 3.0);
            r0D_tmp = CurvStruct_pitch / 6.2831853071795862 * phi_vec;
            r0D[0] = ((C_idx_0 + cphiTCP0_idx_0) + sphiTEcrCP0_idx_0) + r0D_tmp * CurvStruct_evec[0];
            r1D[0] = (-CurvStruct_theta * sphiTCP0_idx_0 + CurvStruct_theta * cphiTEcrCP0_idx_0) +
                d_a * CurvStruct_evec[0];
            r2D[0] = -a_tmp * cphiTCP0_idx_0 - a_tmp * sphiTEcrCP0_idx_0;
            r3D[0] = b_a_tmp * sphiTCP0_idx_0 - b_a_tmp * cphiTEcrCP0_idx_0;
            r0D[1] = ((C_idx_1 + cphiTCP0_idx_1) + sphiTEcrCP0_idx_1) + r0D_tmp * CurvStruct_evec[1];
            r1D[1] = (-CurvStruct_theta * sphiTCP0_idx_1 + CurvStruct_theta * cphiTEcrCP0_idx_1) +
                d_a * CurvStruct_evec[1];
            r2D[1] = -a_tmp * cphiTCP0_idx_1 - a_tmp * sphiTEcrCP0_idx_1;
            r3D[1] = b_a_tmp * sphiTCP0_idx_1 - b_a_tmp * cphiTEcrCP0_idx_1;
            r0D[2] = ((d + cphiTCP0_idx_2) + sphiTEcrCP0_idx_2) + r0D_tmp * CurvStruct_evec[2];
            r1D[2] = (-CurvStruct_theta * sphiTCP0_idx_2 + CurvStruct_theta * cphiTEcrCP0_idx_2) +
                d_a * CurvStruct_evec[2];
            r2D[2] = -a_tmp * cphiTCP0_idx_2 - a_tmp * sphiTEcrCP0_idx_2;
            r3D[2] = b_a_tmp * sphiTCP0_idx_2 - b_a_tmp * cphiTEcrCP0_idx_2;
        }
    }

    //
    // Arguments    : const double CurvStruct_CoeffP5[6][3]
    //                double u_vec
    //                double r_0D[3]
    //                double r_1D[3]
    //                double r_2D[3]
    //                double r_3D[3]
    // Return Type  : void
    //
    static void b_EvalTransP5(const double CurvStruct_CoeffP5[6][3], double u_vec, double r_0D[3],
        double r_1D[3], double r_2D[3], double r_3D[3])
    {
        double p5_1D[5][3];
        double p5_2D[4][3];
        double d;
        double d1;
        double p5_3D[3][3];
        double d2;
        double d3;
        double d4;
        double d5;
        double d6;
        double d7;
        double d8;
        double d9;
        double d10;
        double d11;

        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        for (int k = 0; k < 5; k++) {
            int p5_1D_tmp;
            p5_1D_tmp = 5 - k;
            p5_1D[k][0] = CurvStruct_CoeffP5[k][0] * static_cast<double>(p5_1D_tmp);
            p5_1D[k][1] = CurvStruct_CoeffP5[k][1] * static_cast<double>(p5_1D_tmp);
            p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * static_cast<double>(p5_1D_tmp);
        }

        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        for (int b_k = 0; b_k < 4; b_k++) {
            int p5_2D_tmp;
            p5_2D_tmp = 4 - b_k;
            p5_2D[b_k][0] = p5_1D[b_k][0] * static_cast<double>(p5_2D_tmp);
            p5_2D[b_k][1] = p5_1D[b_k][1] * static_cast<double>(p5_2D_tmp);
            p5_2D[b_k][2] = p5_1D[b_k][2] * static_cast<double>(p5_2D_tmp);
        }

        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        //
        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        for (int c_k = 0; c_k < 3; c_k++) {
            int p5_3D_tmp;
            p5_3D_tmp = 3 - c_k;
            p5_3D[c_k][0] = p5_2D[c_k][0] * static_cast<double>(p5_3D_tmp);
            p5_3D[c_k][1] = p5_2D[c_k][1] * static_cast<double>(p5_3D_tmp);
            p5_3D[c_k][2] = p5_2D[c_k][2] * static_cast<double>(p5_3D_tmp);
            r_0D[c_k] = CurvStruct_CoeffP5[0][c_k];
        }

        d = r_0D[0];
        d1 = r_0D[1];
        d2 = r_0D[2];
        for (int i = 0; i < 5; i++) {
            d = u_vec * d + CurvStruct_CoeffP5[i + 1][0];
            d1 = u_vec * d1 + CurvStruct_CoeffP5[i + 1][1];
            d2 = u_vec * d2 + CurvStruct_CoeffP5[i + 1][2];
        }

        r_0D[2] = d2;
        r_0D[1] = d1;
        r_0D[0] = d;

        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        d3 = p5_1D[0][0];
        d4 = p5_1D[0][1];
        d5 = p5_1D[0][2];
        for (int b_i = 0; b_i < 4; b_i++) {
            d3 = u_vec * d3 + p5_1D[b_i + 1][0];
            d4 = u_vec * d4 + p5_1D[b_i + 1][1];
            d5 = u_vec * d5 + p5_1D[b_i + 1][2];
        }

        r_1D[2] = d5;
        r_1D[1] = d4;
        r_1D[0] = d3;

        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        d6 = p5_2D[0][0];
        d7 = p5_2D[0][1];
        d8 = p5_2D[0][2];
        for (int c_i = 0; c_i < 3; c_i++) {
            d6 = u_vec * d6 + p5_2D[c_i + 1][0];
            d7 = u_vec * d7 + p5_2D[c_i + 1][1];
            d8 = u_vec * d8 + p5_2D[c_i + 1][2];
            r_3D[c_i] = p5_3D[0][c_i];
        }

        r_2D[2] = d8;
        r_2D[1] = d7;
        r_2D[0] = d6;
        d9 = r_3D[0];
        d10 = r_3D[1];
        d11 = r_3D[2];
        for (int d_i = 0; d_i < 2; d_i++) {
            d9 = u_vec * d9 + p5_3D[d_i + 1][0];
            d10 = u_vec * d10 + p5_3D[d_i + 1][1];
            d11 = u_vec * d11 + p5_3D[d_i + 1][2];
        }

        r_3D[2] = d11;
        r_3D[1] = d10;
        r_3D[0] = d9;
    }

    //
    // Arguments    : const queue_coder *ctx_q_splines
    //                double ctx_cfg_NGridLengthSpline
    //                CurveType S_Type
    //                ZSpdMode S_zspdmode
    //                const double S_P0[3]
    //                const double S_P1[3]
    //                const double S_evec[3]
    //                double S_theta
    //                double S_pitch
    //                const double S_CoeffP5[6][3]
    //                int S_sp_index
    //                double S_FeedRate
    //                bool S_UseConstJerk
    //                double S_ConstJerk
    //                double S_a_param
    //                double S_b_param
    // Return Type  : void
    //
    static void b_PrintCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        CurveType S_Type, ZSpdMode S_zspdmode, const double S_P0[3], const double S_P1[3], const
        double S_evec[3], double S_theta, double S_pitch, const double S_CoeffP5[6][3], int
        S_sp_index, double S_FeedRate, bool S_UseConstJerk, double S_ConstJerk, double S_a_param,
        double S_b_param)
    {
        int varargin_1_size_idx_1;
        char varargin_1_data[9];
        static const char b_cv[5] = { 'H', 'e', 'l', 'i', 'x' };

        static const char b_cv1[7] = { 'T', 'r', 'a', 'n', 's', 'P', '5' };

        static const char b_cv2[6] = { 'S', 'p', 'l', 'i', 'n', 'e' };

        int c_validatedHoleFilling_f2_size_;
        char validatedHoleFilling_f2_data[10];
        char varargin_2_data[10];
        double P0[3];
        double P1[3];
        double validatedHoleFilling_f2;
        double dv[3][6];
        rtString formatSpec;
        char argC_data[9];
        int argC_size[2];
        cell_wrap_9 validatedHoleFilling[1];
        int loop_ub;
        int b_loop_ub;
        char b_varargin_1_data[10];
        double validatedHoleFilling_idx_0;
        double b_validatedHoleFilling_idx_0;
        printf("--------- CURVE STRUCT ---------\n");
        fflush(stdout);
        switch (S_Type) {
          case CurveType_Line:
            varargin_1_size_idx_1 = 4;
            varargin_1_data[0] = 'L';
            varargin_1_data[1] = 'i';
            varargin_1_data[2] = 'n';
            varargin_1_data[3] = 'e';
            break;

          case CurveType_Helix:
            varargin_1_size_idx_1 = 5;
            for (int i1 = 0; i1 < 5; i1++) {
                varargin_1_data[i1] = b_cv[i1];
            }
            break;

          case CurveType_TransP5:
            varargin_1_size_idx_1 = 7;
            for (int i2 = 0; i2 < 7; i2++) {
                varargin_1_data[i2] = b_cv1[i2];
            }
            break;

          case CurveType_Spline:
            varargin_1_size_idx_1 = 6;
            for (int i3 = 0; i3 < 6; i3++) {
                varargin_1_data[i3] = b_cv2[i3];
            }
            break;

          default:
            varargin_1_size_idx_1 = 9;
            for (int i = 0; i < 9; i++) {
                varargin_1_data[i] = cv2[i];
            }
            break;
        }

        c_validatedHoleFilling_f2_size_ = varargin_1_size_idx_1 + 1;
        if (0 <= varargin_1_size_idx_1 - 1) {
            std::memcpy(&validatedHoleFilling_f2_data[0], &varargin_1_data[0], varargin_1_size_idx_1
                        * sizeof(char));
        }

        validatedHoleFilling_f2_data[varargin_1_size_idx_1] = '\x00';
        if (0 <= c_validatedHoleFilling_f2_size_ - 1) {
            std::memcpy(&varargin_2_data[0], &validatedHoleFilling_f2_data[0],
                        c_validatedHoleFilling_f2_size_ * sizeof(char));
        }

        printf("%10s: %s\n", "Type", &varargin_2_data[0]);
        fflush(stdout);
        switch (S_Type) {
          case CurveType_Line:
          case CurveType_Spline:
            break;

          case CurveType_Helix:
            printf("%10s: [%.3f %.3f %.3f]\n", "evec", S_evec[0], S_evec[1], S_evec[2]);
            fflush(stdout);
            printf("%10s: %.3f\n", "theta", S_theta);
            fflush(stdout);
            printf("%10s: %.3f\n", "pitch", S_pitch);
            fflush(stdout);
            break;

          case CurveType_TransP5:
            printf(" CoeffP5: \n");
            fflush(stdout);
            printf("| ");
            fflush(stdout);
            for (int i4 = 0; i4 < 3; i4++) {
                for (int i5 = 0; i5 < 6; i5++) {
                    dv[i4][i5] = S_CoeffP5[i5][i4];
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
            printf("FeedRate: %.2f\n", S_FeedRate);
            fflush(stdout);
            break;

          default:
            printf("!!! Type = %d, UNKNOWN !!!\n", static_cast<int>(S_Type));
            fflush(stdout);
            break;
        }

        b_EvalCurvStruct(ctx_q_splines, S_Type, S_P0, S_P1, S_evec, S_theta, S_pitch, S_CoeffP5,
                         S_sp_index, S_b_param, P0);
        c_EvalCurvStruct(ctx_q_splines, S_Type, S_P0, S_P1, S_evec, S_theta, S_pitch, S_CoeffP5,
                         S_sp_index, S_a_param, S_b_param, P1);
        printf("%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n", "P", P0[0], P0[1], P0[2], P1[0], P1[1],
               P1[2]);
        fflush(stdout);
        validatedHoleFilling_f2 = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, S_Type, S_P0,
            S_P1, S_evec, S_theta, S_pitch, S_CoeffP5, S_sp_index, S_a_param, S_b_param);
        printf("%10s: %e\n", "Length", validatedHoleFilling_f2);
        fflush(stdout);
        switch (S_zspdmode) {
          case ZSpdMode_NN:
            formatSpec.init();
            break;

          case ZSpdMode_ZN:
            formatSpec.b_init();
            break;

          case ZSpdMode_NZ:
            formatSpec.c_init();
            break;

          default:
            formatSpec.d_init();
            break;
        }

        formatSpec.uncheckedChar(argC_data, argC_size);
        validatedHoleFilling[0].f1.size[1] = argC_size[1] + 1;
        loop_ub = argC_size[1];
        for (int i6 = 0; i6 < loop_ub; i6++) {
            validatedHoleFilling[0].f1.data[i6] = argC_data[i6];
        }

        validatedHoleFilling[0].f1.data[argC_size[1]] = '\x00';
        b_loop_ub = validatedHoleFilling[0].f1.size[1];
        for (int i7 = 0; i7 < b_loop_ub; i7++) {
            b_varargin_1_data[i7] = validatedHoleFilling[0].f1.data[i7];
        }

        printf("ZSpdMode: %s\n", &b_varargin_1_data[0]);
        fflush(stdout);
        printf("FeedRate: %.2f\n", S_FeedRate);
        fflush(stdout);
        if (S_UseConstJerk) {
            CalcZeroStartConstraints(ctx_q_splines, S_Type, S_P0, S_P1, S_evec, S_theta, S_pitch,
                S_CoeffP5, S_sp_index, true, S_ConstJerk, S_a_param, S_b_param, 1.0,
                &validatedHoleFilling_idx_0, &b_validatedHoleFilling_idx_0);
            printf("ConstJerk: %e\n", S_ConstJerk);
            fflush(stdout);
            printf("v_0      : %f\n", validatedHoleFilling_idx_0);
            fflush(stdout);
            printf("at_0     : %f\n", b_validatedHoleFilling_idx_0);
            fflush(stdout);
        }
    }

    //
    // computes approximately the arc length of a parametric spline
    // Arguments    : const queue_coder *ctx_q_splines
    //                double ctx_cfg_NGridLengthSpline
    //                int Curv_sp_index
    //                const double u0_tilda_data[]
    //                const int u0_tilda_size[2]
    //                double u1_tilda
    // Return Type  : double
    //
    static double b_SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, const double u0_tilda_data[], const int
        u0_tilda_size[2], double u1_tilda)
    {
        double L;
        CurvStruct expl_temp;
        coder::array<double, 2U> Spline_sp_CoeffX;
        int loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffY;
        int b_loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        int c_loop_ub;
        coder::array<double, 2U> Spline_sp_knots;
        int d_loop_ub;
        coder::array<bool, 2U> x;
        int e_loop_ub;
        int k;
        int ii;
        int idx;
        int ii_size_idx_1;
        bool exitg1;
        int ii_data[1];
        unsigned int Idx2_data[1];
        int f_loop_ub;
        coder::array<double, 2U> u_vec_tilda;
        int g_loop_ub;
        coder::array<double, 2U> u_tilda;
        int i7;
        int i8;
        int h_loop_ub;
        coder::array<double, 2U> r;
        int i9;
        coder::array<double, 2U> u_mid_tilda;
        int scalarLB;
        int vectorUB;
        int i11;
        coder::array<double, 2U> unusedU0;
        coder::array<double, 2U> r1Dx;
        coder::array<double, 2U> unusedU1;
        coder::array<double, 2U> r1Dy;
        coder::array<double, 2U> unusedU2;
        coder::array<double, 2U> r1Dz;
        coder::array<double, 2U> a;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        coder::array<double, 2U> z1;
        int N;
        coder::array<double, 2U> b_x;
        int i17;
        int b_scalarLB;
        int b_vectorUB;
        int e_k;
        int m_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int i18;
        int vlen;

        //  get the sp structure
        ctx_q_splines->get(Curv_sp_index, (&expl_temp));
        Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
        loop_ub = expl_temp.sp.CoeffX.size(1);
        for (int i = 0; i < loop_ub; i++) {
            Spline_sp_CoeffX[i] = expl_temp.sp.CoeffX[i];
        }

        Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
        b_loop_ub = expl_temp.sp.CoeffY.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            Spline_sp_CoeffY[i1] = expl_temp.sp.CoeffY[i1];
        }

        Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
        c_loop_ub = expl_temp.sp.CoeffZ.size(1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            Spline_sp_CoeffZ[i2] = expl_temp.sp.CoeffZ[i2];
        }

        Spline_sp_knots.set_size(1, expl_temp.sp.knots.size(1));
        d_loop_ub = expl_temp.sp.knots.size(1);
        for (int i3 = 0; i3 < d_loop_ub; i3++) {
            Spline_sp_knots[i3] = expl_temp.sp.knots[i3];
        }

        //  the ORIGINAL spline is parametrized with u_tilda
        //  after cut-off, new parameter is called u.
        //  u=0 corresponds to the first lift-off point
        //  u=1 corresponds to the second lift-off point
        //  u is NOT used in this function
        x.set_size(1, Spline_sp_knots.size(1));
        e_loop_ub = Spline_sp_knots.size(1);
        for (int i4 = 0; i4 < e_loop_ub; i4++) {
            x[i4] = (Spline_sp_knots[i4] < u1_tilda);
        }

        k = (1 <= x.size(1));
        ii = x.size(1);
        idx = 0;
        ii_size_idx_1 = k;
        exitg1 = false;
        while ((!exitg1) && (ii > 0)) {
            if (x[ii - 1]) {
                idx = 1;
                ii_data[0] = ii;
                exitg1 = true;
            } else {
                ii--;
            }
        }

        if (k == 1) {
            if (idx == 0) {
                ii_size_idx_1 = 0;
            }
        } else {
            ii_size_idx_1 = (1 <= idx);
        }

        if (0 <= ii_size_idx_1 - 1) {
            Idx2_data[0] = static_cast<unsigned int>(ii_data[0]);
        }

        f_loop_ub = static_cast<int>(Idx2_data[0]);
        u_vec_tilda.set_size(1, ((u0_tilda_size[1] + static_cast<int>(Idx2_data[0])) + 1));
        g_loop_ub = u0_tilda_size[1];
        for (int i5 = 0; i5 < g_loop_ub; i5++) {
            u_vec_tilda[i5] = u0_tilda_data[i5];
        }

        for (int i6 = 0; i6 < f_loop_ub; i6++) {
            u_vec_tilda[i6 + u0_tilda_size[1]] = Spline_sp_knots[i6];
        }

        u_vec_tilda[u0_tilda_size[1] + static_cast<int>(Idx2_data[0])] = u1_tilda;
        u_tilda.set_size(1, 0);

        //  N equally spaced u_tilda values between each pair of knots
        //  from u0_tilda until u1_tilda
        i7 = u_vec_tilda.size(1);
        for (int b_k = 0; b_k <= i7 - 2; b_k++) {
            int i10;
            int i_loop_ub;
            i8 = u_tilda.size(1);
            if (u_tilda.size(1) != 0) {
                if (1 > u_tilda.size(1) - 1) {
                    i8 = 0;
                } else {
                    i8 = u_tilda.size(1) - 1;
                }
            }

            linspace(u_vec_tilda[b_k], u_vec_tilda[b_k + 1], ctx_cfg_NGridLengthSpline, r);
            i10 = i8;
            i_loop_ub = r.size(1);
            i8 += r.size(1);
            u_tilda.set_size(u_tilda.size(0), i8);
            for (int i12 = 0; i12 < i_loop_ub; i12++) {
                u_tilda[i10 + i12] = r[i12];
            }
        }

        //  midpoint values
        if (1 > u_tilda.size(1) - 1) {
            h_loop_ub = 0;
        } else {
            h_loop_ub = u_tilda.size(1) - 1;
        }

        i9 = (2 <= u_tilda.size(1));
        u_mid_tilda.set_size(1, h_loop_ub);
        scalarLB = h_loop_ub & -4;
        vectorUB = scalarLB - 4;
        for (i11 = 0; i11 <= vectorUB; i11 += 4) {
            __m256d r1;
            __m256d r2;
            r1 = _mm256_loadu_pd(&u_tilda[i11]);
            r2 = _mm256_loadu_pd(&u_tilda[i9 + i11]);
            _mm256_storeu_pd(&u_mid_tilda[i11], _mm256_mul_pd(_mm256_set1_pd(0.5), _mm256_add_pd(r1,
                               r2)));
        }

        for (i11 = scalarLB; i11 < h_loop_ub; i11++) {
            u_mid_tilda[i11] = 0.5 * (u_tilda[i11] + u_tilda[i9 + i11]);
        }

        //  midpoint values
        //  parametric derivative calculation at each midpoint value
        //  with respect to u_tilda
        c_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, u_mid_tilda, unusedU0, r1Dx);
        c_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, u_mid_tilda, unusedU1, r1Dy);
        c_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, u_mid_tilda, unusedU2, r1Dz);

        //  length (between u0_tilda and u1_tilda) calculation by rectangles method
        a.set_size(3, r1Dx.size(1));
        j_loop_ub = r1Dx.size(1);
        for (int i13 = 0; i13 < j_loop_ub; i13++) {
            a[3 * i13] = r1Dx[i13];
        }

        k_loop_ub = r1Dy.size(1);
        for (int i14 = 0; i14 < k_loop_ub; i14++) {
            a[3 * i14 + 1] = r1Dy[i14];
        }

        l_loop_ub = r1Dz.size(1);
        for (int i15 = 0; i15 < l_loop_ub; i15++) {
            a[3 * i15 + 2] = r1Dz[i15];
        }

        z1.set_size(3, a.size(1));
        N = a.size(1);
        for (int c_k = 0; c_k < N; c_k++) {
            z1[3 * c_k] = std::pow(a[3 * c_k], 2.0);
            z1[3 * c_k + 1] = std::pow(a[3 * c_k + 1], 2.0);
            z1[3 * c_k + 2] = std::pow(a[3 * c_k + 2], 2.0);
        }

        if (z1.size(1) == 0) {
            b_x.set_size(1, 0);
        } else {
            int i16;
            b_x.set_size(1, z1.size(1));
            i16 = z1.size(1);
            for (int d_k = 0; d_k < i16; d_k++) {
                b_x[d_k] = z1[3 * d_k];
                b_x[d_k] = b_x[d_k] + z1[3 * d_k + 1];
                b_x[d_k] = b_x[d_k] + z1[3 * d_k + 2];
            }
        }

        i17 = b_x.size(1);
        b_scalarLB = b_x.size(1) & -4;
        b_vectorUB = b_scalarLB - 4;
        for (e_k = 0; e_k <= b_vectorUB; e_k += 4) {
            __m256d r3;
            r3 = _mm256_loadu_pd(&b_x[e_k]);
            _mm256_storeu_pd(&b_x[e_k], _mm256_sqrt_pd(r3));
        }

        for (e_k = b_scalarLB; e_k < i17; e_k++) {
            b_x[e_k] = std::sqrt(b_x[e_k]);
        }

        diff(u_tilda, r);
        b_x.set_size(1, b_x.size(1));
        m_loop_ub = b_x.size(1);
        c_scalarLB = b_x.size(1) & -4;
        c_vectorUB = c_scalarLB - 4;
        for (i18 = 0; i18 <= c_vectorUB; i18 += 4) {
            __m256d r4;
            __m256d r5;
            r4 = _mm256_loadu_pd(&b_x[i18]);
            r5 = _mm256_loadu_pd(&r[i18]);
            _mm256_storeu_pd(&b_x[i18], _mm256_mul_pd(r4, r5));
        }

        for (i18 = c_scalarLB; i18 < m_loop_ub; i18++) {
            b_x[i18] = b_x[i18] * r[i18];
        }

        vlen = b_x.size(1);
        if (b_x.size(1) == 0) {
            L = 0.0;
        } else {
            double y;
            y = b_x[0];
            for (int f_k = 2; f_k <= vlen; f_k++) {
                double b_y;
                b_y = y;
                if (vlen >= 2) {
                    b_y = y + b_x[f_k - 1];
                }

                y = b_y;
            }

            L = y;
        }

        return L;
    }

    //
    // Arguments    : int degree
    //                const coder::array<double, 2U> &breakpoints
    //                int *Bl_ncoeff
    //                coder::array<double, 2U> &Bl_breakpoints
    //                unsigned long *Bl_handle
    //                int *Bl_degree
    // Return Type  : void
    //
    static void b_bspline_create(int degree, const coder::array<double, 2U> &breakpoints, int
        *Bl_ncoeff, coder::array<double, 2U> &Bl_breakpoints, unsigned long *Bl_handle, int
        *Bl_degree)
    {
        int b_Bl_ncoeff;
        coder::array<double, 2U> b_breakpoints;
        int loop_ub;
        unsigned long b_Bl_handle;
        int b_loop_ub;
        b_Bl_ncoeff = (breakpoints.size(1) + degree) - 2;
        b_breakpoints.set_size(1, breakpoints.size(1));
        loop_ub = breakpoints.size(1);
        for (int i = 0; i < loop_ub; i++) {
            b_breakpoints[i] = breakpoints[i];
        }

        c_bspline_create_with_breakpoints(&b_Bl_handle, degree, &b_breakpoints[0], breakpoints.size
            (1));
        Bl_breakpoints.set_size(1, breakpoints.size(1));
        b_loop_ub = breakpoints.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            Bl_breakpoints[i1] = breakpoints[i1];
        }

        *Bl_ncoeff = b_Bl_ncoeff;
        *Bl_handle = b_Bl_handle;
        *Bl_degree = degree;
    }

    //
    // void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
    // Arguments    : unsigned long Bl_handle
    //                const coder::array<double, 1U> &coeffs
    //                double *x
    //                double *xd
    //                double *xdd
    // Return Type  : void
    //
    static void b_bspline_eval(unsigned long Bl_handle, const coder::array<double, 1U> &coeffs,
        double *x, double *xd, double *xdd)
    {
        double X[4];
        if (*x < 0.0) {
            printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", *x);
            fflush(stdout);
            *x = 0.0;
        } else {
            if (*x > 1.0) {
                printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", *x);
                fflush(stdout);
                *x = 1.0;
            }
        }

        c_bspline_eval(&Bl_handle, &(((coder::array<double, 1U> *)&coeffs)->data())[0], *x, &X[0]);
        *x = X[0];
        *xd = X[1];
        *xdd = X[2];
    }

    //
    // Arguments    : unsigned long Bl_handle
    //                const coder::array<double, 2U> &coeffs
    //                double u
    //                double *x
    //                double *xd
    //                double *xdd
    //                double *xddd
    // Return Type  : void
    //
    static void b_bspline_eval_vec(unsigned long Bl_handle, const coder::array<double, 2U> &coeffs,
        double u, double *x, double *xd, double *xdd, double *xddd)
    {
        *x = u;
        bspline_eval(Bl_handle, coeffs, x, xd, xdd, xddd);
    }

    //
    // Arguments    : const coder::array<double, 1U> &a
    //                const coder::array<double, 2U> &b
    //                coder::array<double, 2U> &c
    // Return Type  : void
    //
    static void b_bsxfun(const coder::array<double, 1U> &a, const coder::array<double, 2U> &b, coder::
                         array<double, 2U> &c)
    {
        int u0;
        int u1;
        int y;
        int i;
        int b_u0;
        int b_u1;
        int b_y;
        int i1;
        u0 = b.size(0);
        u1 = a.size(0);
        if (u0 < u1) {
            y = u0;
        } else {
            y = u1;
        }

        if (b.size(0) == 1) {
            i = a.size(0);
        } else if (a.size(0) == 1) {
            i = b.size(0);
        } else if (a.size(0) == b.size(0)) {
            i = a.size(0);
        } else {
            i = y;
        }

        c.set_size(i, b.size(1));
        b_u0 = b.size(0);
        b_u1 = a.size(0);
        if (b_u0 < b_u1) {
            b_y = b_u0;
        } else {
            b_y = b_u1;
        }

        if (b.size(0) == 1) {
            i1 = a.size(0);
        } else if (a.size(0) == 1) {
            i1 = b.size(0);
        } else if (a.size(0) == b.size(0)) {
            i1 = a.size(0);
        } else {
            i1 = b_y;
        }

        if ((i1 != 0) && (b.size(1) != 0)) {
            int bcoef;
            int i2;
            bcoef = (b.size(1) != 1);
            i2 = b.size(1) - 1;
            for (int k = 0; k <= i2; k++) {
                int varargin_3;
                int acoef;
                int b_bcoef;
                int i3;
                varargin_3 = bcoef * k;
                acoef = (a.size(0) != 1);
                b_bcoef = (b.size(0) != 1);
                i3 = c.size(0) - 1;
                for (int b_k = 0; b_k <= i3; b_k++) {
                    c[b_k + c.size(0) * k] = a[acoef * b_k] * b[b_bcoef * b_k + b.size(0) *
                        varargin_3];
                }
            }
        }
    }

    //
    // Arguments    : double *x
    // Return Type  : void
    //
    static void b_cosd(double *x)
    {
        double b_x;
        double absx;
        signed char n;
        b_x = rt_remd(*x, 360.0);
        absx = std::abs(b_x);
        if (absx > 180.0) {
            if (b_x > 0.0) {
                b_x -= 360.0;
            } else {
                b_x += 360.0;
            }

            absx = std::abs(b_x);
        }

        if (absx <= 45.0) {
            b_x *= 0.017453292519943295;
            n = 0;
        } else if (absx <= 135.0) {
            if (b_x > 0.0) {
                b_x = 0.017453292519943295 * (b_x - 90.0);
                n = 1;
            } else {
                b_x = 0.017453292519943295 * (b_x + 90.0);
                n = -1;
            }
        } else if (b_x > 0.0) {
            b_x = 0.017453292519943295 * (b_x - 180.0);
            n = 2;
        } else {
            b_x = 0.017453292519943295 * (b_x + 180.0);
            n = -2;
        }

        if (n == 0) {
            *x = std::cos(b_x);
        } else if (n == 1) {
            *x = -std::sin(b_x);
        } else if (n == -1) {
            *x = std::sin(b_x);
        } else {
            *x = -std::cos(b_x);
        }
    }

    //
    // Arguments    : const coder::array<bool, 2U> &x
    //                int i_data[]
    //                int i_size[2]
    // Return Type  : void
    //
    static void b_eml_find(const coder::array<bool, 2U> &x, int i_data[], int i_size[2])
    {
        int k;
        int ii;
        int idx;
        bool exitg1;
        k = (1 <= x.size(1));
        ii = x.size(1);
        idx = 0;
        i_size[0] = 1;
        i_size[1] = k;
        exitg1 = false;
        while ((!exitg1) && (ii > 0)) {
            if (x[ii - 1]) {
                idx = 1;
                i_data[0] = ii;
                exitg1 = true;
            } else {
                ii--;
            }
        }

        if (k == 1) {
            if (idx == 0) {
                i_size[0] = 1;
                i_size[1] = 0;
            }
        } else {
            i_size[1] = (1 <= idx);
        }
    }

    //
    // Arguments    : double a
    //                double d
    //                coder::array<double, 2U> &y
    // Return Type  : void
    //
    static void b_eml_float_colon(double a, double d, coder::array<double, 2U> &y)
    {
        double ndbl;
        double apnd;
        double cdiff;
        double bnew;
        int n;
        ndbl = std::floor((0.0 - a) / d + 0.5);
        apnd = a + ndbl * d;
        if (d > 0.0) {
            cdiff = apnd;
        } else {
            cdiff = 0.0 - apnd;
        }

        if (std::abs(cdiff) < 4.4408920985006262E-16 * std::fmax(std::abs(a), 0.0)) {
            ndbl++;
            bnew = 0.0;
        } else if (cdiff > 0.0) {
            bnew = a + (ndbl - 1.0) * d;
        } else {
            ndbl++;
            bnew = apnd;
        }

        if (ndbl >= 0.0) {
            n = static_cast<int>(ndbl);
        } else {
            n = 0;
        }

        y.set_size(1, n);
        if (n > 0) {
            y[0] = a;
            if (n > 1) {
                int nm1d2;
                double kd;
                y[n - 1] = bnew;
                nm1d2 = (n - 1) / 2;
                for (int k = 0; k <= nm1d2 - 2; k++) {
                    kd = (static_cast<double>(k) + 1.0) * d;
                    y[k + 1] = a + kd;
                    y[(n - k) - 2] = bnew - kd;
                }

                if (nm1d2 << 1 == n - 1) {
                    y[nm1d2] = (a + bnew) / 2.0;
                } else {
                    kd = static_cast<double>(nm1d2) * d;
                    y[nm1d2] = a + kd;
                    y[nm1d2 + 1] = bnew - kd;
                }
            }
        }
    }

    //
    // Arguments    : int n1
    //                coder::array<double, 2U> &y
    // Return Type  : void
    //
    static void b_linspace(int n1, coder::array<double, 2U> &y)
    {
        if (n1 < 0) {
            n1 = 0;
        }

        y.set_size(1, n1);
        if (n1 >= 1) {
            y[n1 - 1] = 0.0;
            if (y.size(1) >= 2) {
                y[0] = -1.0;
                if (y.size(1) >= 3) {
                    double delta1;
                    int i;
                    delta1 = 1.0 / (static_cast<double>(y.size(1)) - 1.0);
                    i = y.size(1);
                    for (int k = 0; k <= i - 3; k++) {
                        y[k + 1] = (static_cast<double>(k) + 1.0) * delta1 + -1.0;
                    }
                }
            }
        }
    }

    //
    // Arguments    : const double x[3]
    // Return Type  : double
    //
    static double b_norm(const double x[3])
    {
        double y;
        double scale;
        double absxk;
        double t;
        scale = 3.3121686421112381E-170;
        absxk = std::abs(x[0]);
        if (absxk > 3.3121686421112381E-170) {
            y = 1.0;
            scale = absxk;
        } else {
            t = absxk / 3.3121686421112381E-170;
            y = t * t;
        }

        absxk = std::abs(x[1]);
        if (absxk > scale) {
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
        } else {
            t = absxk / scale;
            y += t * t;
        }

        absxk = std::abs(x[2]);
        if (absxk > scale) {
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
        } else {
            t = absxk / scale;
            y += t * t;
        }

        return scale * std::sqrt(y);
    }

    //
    // Arguments    : int Bl_ncoeff
    //                unsigned long Bl_handle
    //                const coder::array<double, 2U> &xvec
    //                coder::array<double, 2U> &BasisVal
    //                coder::array<double, 2U> &BasisValD
    // Return Type  : void
    //
    static void bspline_base_eval(int Bl_ncoeff, unsigned long Bl_handle, const coder::array<double,
        2U> &xvec, coder::array<double, 2U> &BasisVal, coder::array<double, 2U> &BasisValD)
    {
        coder::array<double, 2U> BasisValDD;
        coder::array<double, 2U> BasisValDDD;
        coder::array<double, 1U> BasisIntegr;

        //  n, bspline_n
        BasisVal.set_size(xvec.size(1), Bl_ncoeff);
        BasisValD.set_size(xvec.size(1), Bl_ncoeff);
        BasisValDD.set_size(xvec.size(1), Bl_ncoeff);
        BasisValDDD.set_size(xvec.size(1), Bl_ncoeff);
        BasisIntegr.set_size(Bl_ncoeff);
        for (int i = 0; i < Bl_ncoeff; i++) {
            int loop_ub;
            int b_loop_ub;
            int c_loop_ub;
            int d_loop_ub;
            loop_ub = xvec.size(1);
            for (int i1 = 0; i1 < loop_ub; i1++) {
                BasisVal[i1 + BasisVal.size(0) * i] = 0.0;
            }

            b_loop_ub = xvec.size(1);
            for (int i2 = 0; i2 < b_loop_ub; i2++) {
                BasisValD[i2 + BasisValD.size(0) * i] = 0.0;
            }

            c_loop_ub = xvec.size(1);
            for (int i3 = 0; i3 < c_loop_ub; i3++) {
                BasisValDD[i3 + BasisValDD.size(0) * i] = 0.0;
            }

            d_loop_ub = xvec.size(1);
            for (int i4 = 0; i4 < d_loop_ub; i4++) {
                BasisValDDD[i4 + BasisValDDD.size(0) * i] = 0.0;
            }

            BasisIntegr[i] = 0.0;
        }

        // ,
        c_bspline_base_eval(&Bl_handle, xvec.size(1), &xvec[0], &BasisVal[0], &BasisValD[0],
                            &BasisValDD[0], &BasisValDDD[0], &(BasisIntegr.data())[0]);
    }

    //
    // void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
    // Arguments    : unsigned long Bl_handle
    //                const coder::array<double, 2U> &coeffs
    //                double *x
    //                double *xd
    //                double *xdd
    //                double *xddd
    // Return Type  : void
    //
    static void bspline_eval(unsigned long Bl_handle, const coder::array<double, 2U> &coeffs, double
        *x, double *xd, double *xdd, double *xddd)
    {
        double X[4];
        if (*x < 0.0) {
            printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", *x);
            fflush(stdout);
            *x = 0.0;
        } else {
            if (*x > 1.0) {
                printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", *x);
                fflush(stdout);
                *x = 1.0;
            }
        }

        c_bspline_eval(&Bl_handle, &coeffs[0], *x, &X[0]);
        *x = X[0];
        *xd = X[1];
        *xdd = X[2];
        *xddd = X[3];
    }

    //
    // Arguments    : unsigned long Bl_handle
    //                const coder::array<double, 2U> &coeffs
    //                const coder::array<double, 2U> &u
    //                coder::array<double, 2U> &x
    //                coder::array<double, 2U> &xd
    //                coder::array<double, 2U> &xdd
    //                coder::array<double, 2U> &xddd
    // Return Type  : void
    //
    static void bspline_eval_vec(unsigned long Bl_handle, const coder::array<double, 2U> &coeffs,
        const coder::array<double, 2U> &u, coder::array<double, 2U> &x, coder::array<double, 2U> &xd,
        coder::array<double, 2U> &xdd, coder::array<double, 2U> &xddd)
    {
        unsigned int unnamed_idx_1;
        int loop_ub;
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int i4;
        unnamed_idx_1 = static_cast<unsigned int>(u.size(1));
        x.set_size(1, (static_cast<int>(unnamed_idx_1)));
        loop_ub = static_cast<int>(unnamed_idx_1);
        for (int i = 0; i < loop_ub; i++) {
            x[i] = 0.0;
        }

        unnamed_idx_1 = static_cast<unsigned int>(u.size(1));
        xd.set_size(1, (static_cast<int>(unnamed_idx_1)));
        b_loop_ub = static_cast<int>(unnamed_idx_1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            xd[i1] = 0.0;
        }

        unnamed_idx_1 = static_cast<unsigned int>(u.size(1));
        xdd.set_size(1, (static_cast<int>(unnamed_idx_1)));
        c_loop_ub = static_cast<int>(unnamed_idx_1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            xdd[i2] = 0.0;
        }

        unnamed_idx_1 = static_cast<unsigned int>(u.size(1));
        xddd.set_size(1, (static_cast<int>(unnamed_idx_1)));
        d_loop_ub = static_cast<int>(unnamed_idx_1);
        for (int i3 = 0; i3 < d_loop_ub; i3++) {
            xddd[i3] = 0.0;
        }

        i4 = u.size(1);
        for (int k = 0; k < i4; k++) {
            x[k] = u[k];
            bspline_eval(Bl_handle, coeffs, &x[k], &xd[k], &xdd[k], &xddd[k]);
        }
    }

    //
    // Arguments    : const coder::array<double, 2U> &a
    //                const coder::array<double, 2U> &b
    //                coder::array<double, 2U> &c
    // Return Type  : void
    //
    static void bsxfun(const coder::array<double, 2U> &a, const coder::array<double, 2U> &b, coder::
                       array<double, 2U> &c)
    {
        int u0;
        int u1;
        int y;
        int csz_idx_1;
        int b_u0;
        int b_u1;
        int b_y;
        int i;
        u0 = b.size(1);
        u1 = a.size(1);
        if (u0 < u1) {
            y = u0;
        } else {
            y = u1;
        }

        if (b.size(1) == 1) {
            csz_idx_1 = a.size(1);
        } else if (a.size(1) == 1) {
            csz_idx_1 = b.size(1);
        } else if (a.size(1) == b.size(1)) {
            csz_idx_1 = a.size(1);
        } else {
            csz_idx_1 = y;
        }

        b_u0 = b.size(1);
        b_u1 = a.size(1);
        if (b_u0 < b_u1) {
            b_y = b_u0;
        } else {
            b_y = b_u1;
        }

        if (b.size(1) == 1) {
            i = a.size(1);
        } else if (a.size(1) == 1) {
            i = b.size(1);
        } else if (a.size(1) == b.size(1)) {
            i = a.size(1);
        } else {
            i = b_y;
        }

        c.set_size(3, i);
        if (csz_idx_1 != 0) {
            int acoef;
            int bcoef;
            int i1;
            acoef = (a.size(1) != 1);
            bcoef = (b.size(1) != 1);
            i1 = csz_idx_1 - 1;
            for (int k = 0; k <= i1; k++) {
                int varargin_2;
                int varargin_3;
                varargin_2 = acoef * k;
                varargin_3 = bcoef * k;
                c[3 * k] = a[3 * varargin_2] * b[varargin_3];
                c[3 * k + 1] = a[3 * varargin_2 + 1] * b[varargin_3];
                c[3 * k + 2] = a[3 * varargin_2 + 2] * b[varargin_3];
            }
        }
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double CurvStruct_CoeffP5[6][3]
    //                int CurvStruct_sp_index
    //                double CurvStruct_a_param
    //                double CurvStruct_b_param
    //                double r0D[3]
    // Return Type  : void
    //
    static void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, double r0D[3])
    {
        double u_vec_tilda;
        double r1D[3];
        double r2D[3];
        double r3D[3];
        CurvStruct expl_temp;
        char message[30];
        coder::array<double, 2U> Spline_sp_CoeffX;
        coder::array<double, 2U> Spline_sp_CoeffY;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        double r0Dx;
        double r1Dx;
        double r2Dx;
        double r3Dx;
        double r0Dy;
        double r1Dy;
        double r2Dy;
        double r3Dy;
        double r0Dz;
        double r1Dz;
        double r2Dz;
        double r3Dz;

        //
        //
        r0D[0] = 0.0;
        r0D[1] = 0.0;
        r0D[2] = 0.0;
        u_vec_tilda = CurvStruct_a_param + CurvStruct_b_param;
        switch (CurvStruct_Type) {
          case CurveType_Line:
            //  line (G01)
            //
            //  parametrization of a straight line between P0 and P1
            //
            r0D[0] = CurvStruct_P1[0] * u_vec_tilda + CurvStruct_P0[0] * (1.0 - u_vec_tilda);
            r0D[1] = CurvStruct_P1[1] * u_vec_tilda + CurvStruct_P0[1] * (1.0 - u_vec_tilda);
            r0D[2] = CurvStruct_P1[2] * u_vec_tilda + CurvStruct_P0[2] * (1.0 - u_vec_tilda);

            //
            //
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            b_EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_evec, CurvStruct_theta,
                        CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            b_EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            {
                int loop_ub;
                int b_loop_ub;
                int c_loop_ub;

                //  BSpline
                ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
                Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
                loop_ub = expl_temp.sp.CoeffX.size(1);
                for (int i1 = 0; i1 < loop_ub; i1++) {
                    Spline_sp_CoeffX[i1] = expl_temp.sp.CoeffX[i1];
                }

                Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
                b_loop_ub = expl_temp.sp.CoeffY.size(1);
                for (int i2 = 0; i2 < b_loop_ub; i2++) {
                    Spline_sp_CoeffY[i2] = expl_temp.sp.CoeffY[i2];
                }

                Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
                c_loop_ub = expl_temp.sp.CoeffZ.size(1);
                for (int i3 = 0; i3 < c_loop_ub; i3++) {
                    Spline_sp_CoeffZ[i3] = expl_temp.sp.CoeffZ[i3];
                }

                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, u_vec_tilda, &r0Dx,
                                   &r1Dx, &r2Dx, &r3Dx);
                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, u_vec_tilda, &r0Dy,
                                   &r1Dy, &r2Dy, &r3Dy);
                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, u_vec_tilda, &r0Dz,
                                   &r1Dz, &r2Dz, &r3Dz);
                r0D[0] = r0Dx;
                r0D[1] = r0Dy;
                r0D[2] = r0Dz;
            }
            break;

          default:
            for (int i = 0; i < 30; i++) {
                message[i] = cv[i];
            }

            c_assert_(&message[0]);
            break;
        }
    }

    //
    // Arguments    : const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double u_vec[10]
    //                double r0D[10][3]
    //                double r1D[10][3]
    //                double r2D[10][3]
    //                double r3D[10][3]
    // Return Type  : void
    //
    static void c_EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const
                            double CurvStruct_evec[3], double CurvStruct_theta, double
                            CurvStruct_pitch, const double u_vec[10], double r0D[10][3], double r1D
                            [10][3], double r2D[10][3], double r3D[10][3])
    {
        double P0P1_idx_0;
        double P0P1_idx_1;
        double P0P1_idx_2;
        double EcrP0P1_idx_0;
        double EcrP0P1_idx_1;
        double EcrP0P1_idx_2;
        char message[16];

        //
        P0P1_idx_0 = CurvStruct_P1[0] - CurvStruct_P0[0];
        P0P1_idx_1 = CurvStruct_P1[1] - CurvStruct_P0[1];
        P0P1_idx_2 = CurvStruct_P1[2] - CurvStruct_P0[2];
        EcrP0P1_idx_0 = CurvStruct_evec[1] * P0P1_idx_2 - CurvStruct_evec[2] * P0P1_idx_1;
        EcrP0P1_idx_1 = CurvStruct_evec[2] * P0P1_idx_0 - CurvStruct_evec[0] * P0P1_idx_2;
        EcrP0P1_idx_2 = CurvStruct_evec[0] * P0P1_idx_1 - CurvStruct_evec[1] * P0P1_idx_0;
        for (int i = 0; i < 10; i++) {
            r0D[i][0] = 0.0;
            r1D[i][0] = 0.0;
            r2D[i][0] = 0.0;
            r3D[i][0] = 0.0;
            r0D[i][1] = 0.0;
            r1D[i][1] = 0.0;
            r2D[i][1] = 0.0;
            r3D[i][1] = 0.0;
            r0D[i][2] = 0.0;
            r1D[i][2] = 0.0;
            r2D[i][2] = 0.0;
            r3D[i][2] = 0.0;
        }

        if (std::sqrt((std::pow(EcrP0P1_idx_0, 2.0) + std::pow(EcrP0P1_idx_1, 2.0)) + std::pow
                      (EcrP0P1_idx_2, 2.0)) <= 2.2204460492503131E-16) {
            for (int i1 = 0; i1 < 16; i1++) {
                message[i1] = cv1[i1];
            }

            c_assert_(&message[0]);
        } else {
            double P0P1;
            double a;
            double d;
            double C_idx_0;
            double CP0_idx_0;
            double C_idx_1;
            double CP0_idx_1;
            double CP0_idx_2;
            double EcrCP0_idx_0;
            double EcrCP0_idx_1;
            double EcrCP0_idx_2;
            double b_a;
            double c_a;
            double a_tmp;
            double b_a_tmp;
            double d1;
            double d2;
            double d3;

            //  if pitch == 0
            //      if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
            //          return;
            //      end
            //  end
            //
            P0P1 = (P0P1_idx_0 * CurvStruct_evec[0] + P0P1_idx_1 * CurvStruct_evec[1]) + P0P1_idx_2 *
                CurvStruct_evec[2];
            a = 1.0 / std::tan(CurvStruct_theta / 2.0);
            d = ((CurvStruct_P0[0] + (CurvStruct_P1[0] - P0P1 * CurvStruct_evec[0])) + a *
                 EcrP0P1_idx_0) / 2.0;
            C_idx_0 = d;
            CP0_idx_0 = CurvStruct_P0[0] - d;
            d = ((CurvStruct_P0[1] + (CurvStruct_P1[1] - P0P1 * CurvStruct_evec[1])) + a *
                 EcrP0P1_idx_1) / 2.0;
            C_idx_1 = d;
            CP0_idx_1 = CurvStruct_P0[1] - d;
            d = ((CurvStruct_P0[2] + (CurvStruct_P1[2] - P0P1 * CurvStruct_evec[2])) + a *
                 EcrP0P1_idx_2) / 2.0;
            CP0_idx_2 = CurvStruct_P0[2] - d;
            EcrCP0_idx_0 = CurvStruct_evec[1] * CP0_idx_2 - CurvStruct_evec[2] * CP0_idx_1;
            EcrCP0_idx_1 = CurvStruct_evec[2] * CP0_idx_0 - CurvStruct_evec[0] * CP0_idx_2;
            EcrCP0_idx_2 = CurvStruct_evec[0] * CP0_idx_1 - CurvStruct_evec[1] * CP0_idx_0;

            //
            //
            b_a = CurvStruct_pitch / 6.2831853071795862;
            c_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
            a_tmp = std::pow(CurvStruct_theta, 2.0);
            b_a_tmp = std::pow(CurvStruct_theta, 3.0);
            d1 = CurvStruct_evec[0];
            d2 = CurvStruct_evec[1];
            d3 = CurvStruct_evec[2];
            for (int k = 0; k < 10; k++) {
                double d4;
                double d5;
                double d6;
                double d7;
                double d8;
                double d9;
                double d10;
                double d11;
                double d12;
                double d13;
                double d14;
                double d15;
                double d16;
                double d17;
                double d18;
                double r0D_tmp;
                d4 = CurvStruct_theta * u_vec[k];
                d5 = std::cos(d4);
                d6 = std::sin(d4);
                d7 = d5 * CP0_idx_0;
                d8 = d6 * CP0_idx_0;
                d9 = d5 * CP0_idx_1;
                d10 = d6 * CP0_idx_1;
                d11 = d5 * CP0_idx_2;
                d12 = d6 * CP0_idx_2;
                d13 = d5 * EcrCP0_idx_0;
                d14 = d6 * EcrCP0_idx_0;
                d15 = d5 * EcrCP0_idx_1;
                d16 = d6 * EcrCP0_idx_1;
                d17 = d5 * EcrCP0_idx_2;
                d18 = d6 * EcrCP0_idx_2;
                r0D_tmp = b_a * d4;
                r0D[k][0] = ((C_idx_0 + d7) + d14) + r0D_tmp * d1;
                r1D[k][0] = (-CurvStruct_theta * d8 + CurvStruct_theta * d13) + c_a * d1;
                r2D[k][0] = -a_tmp * d7 - a_tmp * d14;
                r3D[k][0] = b_a_tmp * d8 - b_a_tmp * d13;
                r0D[k][1] = ((C_idx_1 + d9) + d16) + r0D_tmp * d2;
                r1D[k][1] = (-CurvStruct_theta * d10 + CurvStruct_theta * d15) + c_a * d2;
                r2D[k][1] = -a_tmp * d9 - a_tmp * d16;
                r3D[k][1] = b_a_tmp * d10 - b_a_tmp * d15;
                r0D[k][2] = ((d + d11) + d18) + r0D_tmp * d3;
                r1D[k][2] = (-CurvStruct_theta * d12 + CurvStruct_theta * d17) + c_a * d3;
                r2D[k][2] = -a_tmp * d11 - a_tmp * d18;
                r3D[k][2] = b_a_tmp * d12 - b_a_tmp * d17;
            }
        }
    }

    //
    // computes approximately the arc length of a parametric spline
    // Arguments    : const queue_coder *ctx_q_splines
    //                double ctx_cfg_NGridLengthSpline
    //                int Curv_sp_index
    //                double u0_tilda
    //                const double u1_tilda_data[]
    //                const int u1_tilda_size[2]
    // Return Type  : double
    //
    static double c_SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, double u0_tilda, const double u1_tilda_data[],
        const int u1_tilda_size[2])
    {
        double L;
        CurvStruct expl_temp;
        coder::array<double, 2U> Spline_sp_CoeffX;
        int loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffY;
        int b_loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        int c_loop_ub;
        coder::array<double, 2U> Spline_sp_knots;
        int d_loop_ub;
        coder::array<bool, 2U> x;
        int e_loop_ub;
        int k;
        int idx;
        int ii_size_idx_1;
        int ii;
        bool exitg1;
        int ii_data[1];
        unsigned int Idx1_data[1];
        int i5;
        int i6;
        int f_loop_ub;
        int u_vec_tilda_size_idx_1;
        double u_vec_tilda_data[3];
        int g_loop_ub;
        coder::array<double, 2U> u_tilda;
        int i9;
        int h_loop_ub;
        coder::array<double, 2U> r;
        int i10;
        coder::array<double, 2U> u_mid_tilda;
        int scalarLB;
        int vectorUB;
        int i12;
        coder::array<double, 2U> unusedU0;
        coder::array<double, 2U> r1Dx;
        coder::array<double, 2U> unusedU1;
        coder::array<double, 2U> r1Dy;
        coder::array<double, 2U> unusedU2;
        coder::array<double, 2U> r1Dz;
        coder::array<double, 2U> a;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        coder::array<double, 2U> z1;
        int N;
        coder::array<double, 2U> b_x;
        int i18;
        int b_scalarLB;
        int b_vectorUB;
        int e_k;
        int m_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int i19;
        int vlen;

        //  get the sp structure
        ctx_q_splines->get(Curv_sp_index, (&expl_temp));
        Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
        loop_ub = expl_temp.sp.CoeffX.size(1);
        for (int i = 0; i < loop_ub; i++) {
            Spline_sp_CoeffX[i] = expl_temp.sp.CoeffX[i];
        }

        Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
        b_loop_ub = expl_temp.sp.CoeffY.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            Spline_sp_CoeffY[i1] = expl_temp.sp.CoeffY[i1];
        }

        Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
        c_loop_ub = expl_temp.sp.CoeffZ.size(1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            Spline_sp_CoeffZ[i2] = expl_temp.sp.CoeffZ[i2];
        }

        Spline_sp_knots.set_size(1, expl_temp.sp.knots.size(1));
        d_loop_ub = expl_temp.sp.knots.size(1);
        for (int i3 = 0; i3 < d_loop_ub; i3++) {
            Spline_sp_knots[i3] = expl_temp.sp.knots[i3];
        }

        //  the ORIGINAL spline is parametrized with u_tilda
        //  after cut-off, new parameter is called u.
        //  u=0 corresponds to the first lift-off point
        //  u=1 corresponds to the second lift-off point
        //  u is NOT used in this function
        x.set_size(1, Spline_sp_knots.size(1));
        e_loop_ub = Spline_sp_knots.size(1);
        for (int i4 = 0; i4 < e_loop_ub; i4++) {
            x[i4] = (Spline_sp_knots[i4] > u0_tilda);
        }

        k = (1 <= x.size(1));
        idx = 0;
        ii_size_idx_1 = k;
        ii = 0;
        exitg1 = false;
        while ((!exitg1) && (ii <= x.size(1) - 1)) {
            if (x[ii]) {
                idx = 1;
                ii_data[0] = ii + 1;
                exitg1 = true;
            } else {
                ii++;
            }
        }

        if (k == 1) {
            if (idx == 0) {
                ii_size_idx_1 = 0;
            }
        } else {
            ii_size_idx_1 = (1 <= idx);
        }

        if (0 <= ii_size_idx_1 - 1) {
            Idx1_data[0] = static_cast<unsigned int>(ii_data[0]);
        }

        if (static_cast<int>(Idx1_data[0]) > 1) {
            i5 = -2;
            i6 = -1;
        } else {
            i5 = static_cast<int>(Idx1_data[0]) - 3;
            i6 = 0;
        }

        f_loop_ub = i6 - i5;
        u_vec_tilda_size_idx_1 = f_loop_ub + u1_tilda_size[1];
        u_vec_tilda_data[0] = u0_tilda;
        for (int i7 = 0; i7 <= f_loop_ub - 2; i7++) {
            u_vec_tilda_data[i7 + 1] = Spline_sp_knots[(i5 + i7) + 2];
        }

        g_loop_ub = u1_tilda_size[1];
        for (int i8 = 0; i8 < g_loop_ub; i8++) {
            u_vec_tilda_data[(i8 + i6) - i5] = u1_tilda_data[i8];
        }

        u_tilda.set_size(1, 0);

        //  N equally spaced u_tilda values between each pair of knots
        //  from u0_tilda until u1_tilda
        for (int b_k = 0; b_k <= u_vec_tilda_size_idx_1 - 2; b_k++) {
            int i11;
            int i_loop_ub;
            i9 = u_tilda.size(1);
            if (u_tilda.size(1) != 0) {
                if (1 > u_tilda.size(1) - 1) {
                    i9 = 0;
                } else {
                    i9 = u_tilda.size(1) - 1;
                }
            }

            linspace(u_vec_tilda_data[b_k], u_vec_tilda_data[b_k + 1], ctx_cfg_NGridLengthSpline, r);
            i11 = i9;
            i_loop_ub = r.size(1);
            i9 += r.size(1);
            u_tilda.set_size(u_tilda.size(0), i9);
            for (int i13 = 0; i13 < i_loop_ub; i13++) {
                u_tilda[i11 + i13] = r[i13];
            }
        }

        //  midpoint values
        if (1 > u_tilda.size(1) - 1) {
            h_loop_ub = 0;
        } else {
            h_loop_ub = u_tilda.size(1) - 1;
        }

        i10 = (2 <= u_tilda.size(1));
        u_mid_tilda.set_size(1, h_loop_ub);
        scalarLB = h_loop_ub & -4;
        vectorUB = scalarLB - 4;
        for (i12 = 0; i12 <= vectorUB; i12 += 4) {
            __m256d r1;
            __m256d r2;
            r1 = _mm256_loadu_pd(&u_tilda[i12]);
            r2 = _mm256_loadu_pd(&u_tilda[i10 + i12]);
            _mm256_storeu_pd(&u_mid_tilda[i12], _mm256_mul_pd(_mm256_set1_pd(0.5), _mm256_add_pd(r1,
                               r2)));
        }

        for (i12 = scalarLB; i12 < h_loop_ub; i12++) {
            u_mid_tilda[i12] = 0.5 * (u_tilda[i12] + u_tilda[i10 + i12]);
        }

        //  midpoint values
        //  parametric derivative calculation at each midpoint value
        //  with respect to u_tilda
        c_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, u_mid_tilda, unusedU0, r1Dx);
        c_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, u_mid_tilda, unusedU1, r1Dy);
        c_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, u_mid_tilda, unusedU2, r1Dz);

        //  length (between u0_tilda and u1_tilda) calculation by rectangles method
        a.set_size(3, r1Dx.size(1));
        j_loop_ub = r1Dx.size(1);
        for (int i14 = 0; i14 < j_loop_ub; i14++) {
            a[3 * i14] = r1Dx[i14];
        }

        k_loop_ub = r1Dy.size(1);
        for (int i15 = 0; i15 < k_loop_ub; i15++) {
            a[3 * i15 + 1] = r1Dy[i15];
        }

        l_loop_ub = r1Dz.size(1);
        for (int i16 = 0; i16 < l_loop_ub; i16++) {
            a[3 * i16 + 2] = r1Dz[i16];
        }

        z1.set_size(3, a.size(1));
        N = a.size(1);
        for (int c_k = 0; c_k < N; c_k++) {
            z1[3 * c_k] = std::pow(a[3 * c_k], 2.0);
            z1[3 * c_k + 1] = std::pow(a[3 * c_k + 1], 2.0);
            z1[3 * c_k + 2] = std::pow(a[3 * c_k + 2], 2.0);
        }

        if (z1.size(1) == 0) {
            b_x.set_size(1, 0);
        } else {
            int i17;
            b_x.set_size(1, z1.size(1));
            i17 = z1.size(1);
            for (int d_k = 0; d_k < i17; d_k++) {
                b_x[d_k] = z1[3 * d_k];
                b_x[d_k] = b_x[d_k] + z1[3 * d_k + 1];
                b_x[d_k] = b_x[d_k] + z1[3 * d_k + 2];
            }
        }

        i18 = b_x.size(1);
        b_scalarLB = b_x.size(1) & -4;
        b_vectorUB = b_scalarLB - 4;
        for (e_k = 0; e_k <= b_vectorUB; e_k += 4) {
            __m256d r3;
            r3 = _mm256_loadu_pd(&b_x[e_k]);
            _mm256_storeu_pd(&b_x[e_k], _mm256_sqrt_pd(r3));
        }

        for (e_k = b_scalarLB; e_k < i18; e_k++) {
            b_x[e_k] = std::sqrt(b_x[e_k]);
        }

        diff(u_tilda, r);
        b_x.set_size(1, b_x.size(1));
        m_loop_ub = b_x.size(1);
        c_scalarLB = b_x.size(1) & -4;
        c_vectorUB = c_scalarLB - 4;
        for (i19 = 0; i19 <= c_vectorUB; i19 += 4) {
            __m256d r4;
            __m256d r5;
            r4 = _mm256_loadu_pd(&b_x[i19]);
            r5 = _mm256_loadu_pd(&r[i19]);
            _mm256_storeu_pd(&b_x[i19], _mm256_mul_pd(r4, r5));
        }

        for (i19 = c_scalarLB; i19 < m_loop_ub; i19++) {
            b_x[i19] = b_x[i19] * r[i19];
        }

        vlen = b_x.size(1);
        if (b_x.size(1) == 0) {
            L = 0.0;
        } else {
            double y;
            y = b_x[0];
            for (int f_k = 2; f_k <= vlen; f_k++) {
                double b_y;
                b_y = y;
                if (vlen >= 2) {
                    b_y = y + b_x[f_k - 1];
                }

                y = b_y;
            }

            L = y;
        }

        return L;
    }

    //
    // Arguments    : unsigned long Bl_handle
    //                const coder::array<double, 2U> &coeffs
    //                const coder::array<double, 2U> &u
    //                coder::array<double, 2U> &x
    //                coder::array<double, 2U> &xd
    // Return Type  : void
    //
    static void c_bspline_eval_vec(unsigned long Bl_handle, const coder::array<double, 2U> &coeffs,
        const coder::array<double, 2U> &u, coder::array<double, 2U> &x, coder::array<double, 2U> &xd)
    {
        unsigned int unnamed_idx_1;
        int loop_ub;
        int b_loop_ub;
        coder::array<double, 2U> xdd;
        int c_loop_ub;
        coder::array<double, 2U> xddd;
        int d_loop_ub;
        int i4;
        unnamed_idx_1 = static_cast<unsigned int>(u.size(1));
        x.set_size(1, (static_cast<int>(unnamed_idx_1)));
        loop_ub = static_cast<int>(unnamed_idx_1);
        for (int i = 0; i < loop_ub; i++) {
            x[i] = 0.0;
        }

        unnamed_idx_1 = static_cast<unsigned int>(u.size(1));
        xd.set_size(1, (static_cast<int>(unnamed_idx_1)));
        b_loop_ub = static_cast<int>(unnamed_idx_1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            xd[i1] = 0.0;
        }

        unnamed_idx_1 = static_cast<unsigned int>(u.size(1));
        xdd.set_size(1, (static_cast<int>(unnamed_idx_1)));
        c_loop_ub = static_cast<int>(unnamed_idx_1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            xdd[i2] = 0.0;
        }

        unnamed_idx_1 = static_cast<unsigned int>(u.size(1));
        xddd.set_size(1, (static_cast<int>(unnamed_idx_1)));
        d_loop_ub = static_cast<int>(unnamed_idx_1);
        for (int i3 = 0; i3 < d_loop_ub; i3++) {
            xddd[i3] = 0.0;
        }

        i4 = u.size(1);
        for (int k = 0; k < i4; k++) {
            x[k] = u[k];
            bspline_eval(Bl_handle, coeffs, &x[k], &xd[k], &xdd[k], &xddd[k]);
        }
    }

    //
    // Arguments    : const coder::array<double, 2U> &a
    //                const coder::array<double, 1U> &b
    //                coder::array<double, 2U> &c
    // Return Type  : void
    //
    static void c_bsxfun(const coder::array<double, 2U> &a, const coder::array<double, 1U> &b, coder::
                         array<double, 2U> &c)
    {
        int u0;
        int u1;
        int y;
        int i;
        int b_u0;
        int b_u1;
        int b_y;
        int i1;
        u0 = b.size(0);
        u1 = a.size(0);
        if (u0 < u1) {
            y = u0;
        } else {
            y = u1;
        }

        if (b.size(0) == 1) {
            i = a.size(0);
        } else if (a.size(0) == 1) {
            i = b.size(0);
        } else if (a.size(0) == b.size(0)) {
            i = a.size(0);
        } else {
            i = y;
        }

        c.set_size(i, a.size(1));
        b_u0 = b.size(0);
        b_u1 = a.size(0);
        if (b_u0 < b_u1) {
            b_y = b_u0;
        } else {
            b_y = b_u1;
        }

        if (b.size(0) == 1) {
            i1 = a.size(0);
        } else if (a.size(0) == 1) {
            i1 = b.size(0);
        } else if (a.size(0) == b.size(0)) {
            i1 = a.size(0);
        } else {
            i1 = b_y;
        }

        if ((i1 != 0) && (a.size(1) != 0)) {
            int acoef;
            int i2;
            acoef = (a.size(1) != 1);
            i2 = a.size(1) - 1;
            for (int k = 0; k <= i2; k++) {
                int varargin_2;
                int b_acoef;
                int bcoef;
                int i3;
                varargin_2 = acoef * k;
                b_acoef = (a.size(0) != 1);
                bcoef = (b.size(0) != 1);
                i3 = c.size(0) - 1;
                for (int b_k = 0; b_k <= i3; b_k++) {
                    c[b_k + c.size(0) * k] = a[b_acoef * b_k + a.size(0) * varargin_2] * b[bcoef *
                        b_k];
                }
            }
        }
    }

    //
    // Arguments    : const bool x_data[]
    //                const int x_size[1]
    //                int i_data[]
    //                int i_size[1]
    // Return Type  : void
    //
    static void c_eml_find(const bool x_data[], const int x_size[1], int i_data[], int i_size[1])
    {
        int nx;
        int idx;
        int ii;
        bool exitg1;
        nx = x_size[0];
        idx = 0;
        i_size[0] = x_size[0];
        ii = 0;
        exitg1 = false;
        while ((!exitg1) && (ii <= nx - 1)) {
            if (x_data[ii]) {
                idx++;
                i_data[idx - 1] = ii + 1;
                if (idx >= nx) {
                    exitg1 = true;
                } else {
                    ii++;
                }
            } else {
                ii++;
            }
        }

        if (x_size[0] == 1) {
            if (idx == 0) {
                i_size[0] = 0;
            }
        } else if (1 > idx) {
            i_size[0] = 0;
        } else {
            i_size[0] = idx;
        }
    }

    //
    // Arguments    : const coder::array<double, 2U> &f
    //                const coder_internal_sparse *A
    //                coder::array<double, 2U> &b
    //                const coder::array<double, 2U> &Aeq
    //                const coder::array<double, 2U> &beq
    //                coder::array<double, 2U> &C
    //                bool *success
    //                int *status
    // Return Type  : void
    //
    static void c_simplex(const coder::array<double, 2U> &f, const coder_internal_sparse *A, coder::
                          array<double, 2U> &b, const coder::array<double, 2U> &Aeq, const coder::
                          array<double, 2U> &beq, coder::array<double, 2U> &C, bool *success, int
                          *status)
    {
        coder_internal_sparse Atot;
        int loop_ub;
        int nx;
        coder::array<int, 1U> b_i;
        coder::array<int, 1U> ii;
        coder::array<int, 1U> j;
        coder::array<int, 1U> jj;
        coder::array<double, 1U> v;
        coder::array<double, 1U> Avs;
        coder::array<int, 1U> Ais;
        int c_loop_ub;
        coder::array<int, 1U> Ajs;
        int d_loop_ub;
        int fsize[2];
        int Asize[2];
        int n;
        int i7;
        int bsize[2];
        int beqsize[2];
        int Csize[2];
        A->vertcat(Aeq, (&Atot));

        //      MaxCoeff = FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz;
        C.set_size(f.size(0), f.size(1));
        loop_ub = f.size(1);
        for (int i = 0; i < loop_ub; i++) {
            int b_loop_ub;
            b_loop_ub = f.size(0);
            for (int i1 = 0; i1 < b_loop_ub; i1++) {
                C[i1 + C.size(0) * i] = 0.0;
            }
        }

        nx = Atot.nnzInt();
        if (nx == 0) {
            ii.set_size(0);
            jj.set_size(0);
            Avs.set_size(0);
        } else {
            int b_idx;
            int col;
            int e_loop_ub;
            int f_loop_ub;
            int g_loop_ub;
            b_i.set_size(nx);
            j.set_size(nx);
            v.set_size(nx);
            for (int idx = 0; idx < nx; idx++) {
                b_i[idx] = Atot.rowidx[idx];
                v[idx] = Atot.d[idx];
            }

            b_idx = 0;
            col = 1;
            while (b_idx < nx) {
                if (b_idx == Atot.colidx[col] - 1) {
                    col++;
                } else {
                    b_idx++;
                    j[b_idx - 1] = col;
                }
            }

            if (nx == 1) {
                if (b_idx == 0) {
                    b_i.set_size(0);
                    j.set_size(0);
                    v.set_size(0);
                }
            } else {
                int i4;
                int i5;
                int i8;
                if (1 > b_idx) {
                    i4 = 0;
                } else {
                    i4 = b_idx;
                }

                b_i.set_size(i4);
                if (1 > b_idx) {
                    i5 = 0;
                } else {
                    i5 = b_idx;
                }

                j.set_size(i5);
                if (1 > b_idx) {
                    i8 = 0;
                } else {
                    i8 = b_idx;
                }

                v.set_size(i8);
            }

            ii.set_size(b_i.size(0));
            e_loop_ub = b_i.size(0);
            for (int i6 = 0; i6 < e_loop_ub; i6++) {
                ii[i6] = b_i[i6];
            }

            jj.set_size(j.size(0));
            f_loop_ub = j.size(0);
            for (int i9 = 0; i9 < f_loop_ub; i9++) {
                jj[i9] = j[i9];
            }

            Avs.set_size(v.size(0));
            g_loop_ub = v.size(0);
            for (int i10 = 0; i10 < g_loop_ub; i10++) {
                Avs[i10] = v[i10];
            }
        }

        Ais.set_size(ii.size(0));
        c_loop_ub = ii.size(0);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            Ais[i2] = ii[i2] - 1;
        }

        Ajs.set_size(jj.size(0));
        d_loop_ub = jj.size(0);
        for (int i3 = 0; i3 < d_loop_ub; i3++) {
            Ajs[i3] = jj[i3] - 1;
        }

        fsize[0] = f.size(0);
        fsize[1] = f.size(1);
        Asize[0] = Atot.m;
        Asize[1] = Atot.n;
        n = 0;
        i7 = Avs.size(0);
        for (int k = 0; k < i7; k++) {
            if (Avs[k] != 0.0) {
                n++;
            }
        }

        int b_status;
        bsize[0] = b.size(0);
        beqsize[0] = beq.size(0);
        bsize[1] = b.size(1);
        beqsize[1] = beq.size(1);
        Csize[0] = f.size(0);
        Csize[1] = f.size(1);
        b_status = simplex_solve(&f[0], &fsize[0], &(Avs.data())[0], &(Ais.data())[0], &(Ajs.data())
            [0], &Asize[0], n, &b[0], &bsize[0], &beq[0], &beqsize[0], &C[0], &Csize[0]);

        //          C = solution.solution;
        *success = (b_status == 0);
        *status = b_status;
    }

    //
    // Arguments    : const double u[3]
    //                const double v[3]
    //                double tol_angle_d
    // Return Type  : bool
    //
    static bool collinear(const double u[3], const double v[3], double tol_angle_d)
    {
        bool value;
        double scale;
        double absxk;
        double t;
        double d;
        double d1;
        double d2;
        double d3;
        scale = 3.3121686421112381E-170;
        absxk = std::abs(u[0]);
        if (absxk > 3.3121686421112381E-170) {
            d = 1.0;
            scale = absxk;
        } else {
            t = absxk / 3.3121686421112381E-170;
            d = t * t;
        }

        absxk = std::abs(u[1]);
        if (absxk > scale) {
            t = scale / absxk;
            d = d * t * t + 1.0;
            scale = absxk;
        } else {
            t = absxk / scale;
            d += t * t;
        }

        absxk = std::abs(u[2]);
        if (absxk > scale) {
            t = scale / absxk;
            d = d * t * t + 1.0;
            scale = absxk;
        } else {
            t = absxk / scale;
            d += t * t;
        }

        d = scale * std::sqrt(d);
        if (d < 2.2204460492503131E-16) {
            value = true;
        } else {
            double b_scale;
            double b_absxk;
            double b_t;
            b_scale = 3.3121686421112381E-170;
            b_absxk = std::abs(v[0]);
            if (b_absxk > 3.3121686421112381E-170) {
                d1 = 1.0;
                b_scale = b_absxk;
            } else {
                b_t = b_absxk / 3.3121686421112381E-170;
                d1 = b_t * b_t;
            }

            b_absxk = std::abs(v[1]);
            if (b_absxk > b_scale) {
                b_t = b_scale / b_absxk;
                d1 = d1 * b_t * b_t + 1.0;
                b_scale = b_absxk;
            } else {
                b_t = b_absxk / b_scale;
                d1 += b_t * b_t;
            }

            b_absxk = std::abs(v[2]);
            if (b_absxk > b_scale) {
                b_t = b_scale / b_absxk;
                d1 = d1 * b_t * b_t + 1.0;
                b_scale = b_absxk;
            } else {
                b_t = b_absxk / b_scale;
                d1 += b_t * b_t;
            }

            d1 = b_scale * std::sqrt(d1);
            if (d1 < 2.2204460492503131E-16) {
                value = true;
            } else {
                d2 = 57.295779513082323 * std::acos(((u[0] * v[0] + u[1] * v[1]) + u[2] * v[2]) / (d
                    * d1));
                b_cosd(&d2);
                d3 = tol_angle_d;
                b_cosd(&d3);
                value = (d2 > d3);
            }
        }

        return value;
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double CurvStruct_CoeffP5[6][3]
    //                int CurvStruct_sp_index
    //                double CurvStruct_a_param
    //                double CurvStruct_b_param
    //                double r0D[3]
    //                double r1D[3]
    //                double r2D[3]
    // Return Type  : void
    //
    static void d_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, double r0D[3],
        double r1D[3], double r2D[3])
    {
        double u_vec_tilda;
        double r3D[3];
        CurvStruct expl_temp;
        char message[30];
        coder::array<double, 2U> Spline_sp_CoeffX;
        double c;
        coder::array<double, 2U> Spline_sp_CoeffY;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        double r0Dx;
        double r1Dx;
        double r2Dx;
        double r3Dx;
        double r0Dy;
        double r1Dy;
        double r2Dy;
        double r3Dy;
        double r0Dz;
        double r1Dz;
        double r2Dz;
        double r3Dz;

        //
        //
        r0D[0] = 0.0;
        r1D[0] = 0.0;
        r2D[0] = 0.0;
        r0D[1] = 0.0;
        r1D[1] = 0.0;
        r2D[1] = 0.0;
        r0D[2] = 0.0;
        r1D[2] = 0.0;
        r2D[2] = 0.0;
        u_vec_tilda = CurvStruct_a_param + CurvStruct_b_param;
        switch (CurvStruct_Type) {
          case CurveType_Line:
            //  line (G01)
            //
            //  parametrization of a straight line between P0 and P1
            //
            r0D[0] = CurvStruct_P1[0] * u_vec_tilda + CurvStruct_P0[0] * (1.0 - u_vec_tilda);
            r0D[1] = CurvStruct_P1[1] * u_vec_tilda + CurvStruct_P0[1] * (1.0 - u_vec_tilda);
            r0D[2] = CurvStruct_P1[2] * u_vec_tilda + CurvStruct_P0[2] * (1.0 - u_vec_tilda);

            //
            r1D[0] = CurvStruct_P1[0] - CurvStruct_P0[0];
            r1D[1] = CurvStruct_P1[1] - CurvStruct_P0[1];
            r1D[2] = CurvStruct_P1[2] - CurvStruct_P0[2];

            //
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            b_EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_evec, CurvStruct_theta,
                        CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            b_EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            {
                int loop_ub;
                int b_loop_ub;
                int c_loop_ub;

                //  BSpline
                ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
                Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
                loop_ub = expl_temp.sp.CoeffX.size(1);
                for (int i1 = 0; i1 < loop_ub; i1++) {
                    Spline_sp_CoeffX[i1] = expl_temp.sp.CoeffX[i1];
                }

                Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
                b_loop_ub = expl_temp.sp.CoeffY.size(1);
                for (int i2 = 0; i2 < b_loop_ub; i2++) {
                    Spline_sp_CoeffY[i2] = expl_temp.sp.CoeffY[i2];
                }

                Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
                c_loop_ub = expl_temp.sp.CoeffZ.size(1);
                for (int i3 = 0; i3 < c_loop_ub; i3++) {
                    Spline_sp_CoeffZ[i3] = expl_temp.sp.CoeffZ[i3];
                }

                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, u_vec_tilda, &r0Dx,
                                   &r1Dx, &r2Dx, &r3Dx);
                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, u_vec_tilda, &r0Dy,
                                   &r1Dy, &r2Dy, &r3Dy);
                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, u_vec_tilda, &r0Dz,
                                   &r1Dz, &r2Dz, &r3Dz);
                r0D[0] = r0Dx;
                r0D[1] = r0Dy;
                r0D[2] = r0Dz;
                r1D[0] = r1Dx;
                r1D[1] = r1Dy;
                r1D[2] = r1Dz;
                r2D[0] = r2Dx;
                r2D[1] = r2Dy;
                r2D[2] = r2Dz;
            }
            break;

          default:
            for (int i = 0; i < 30; i++) {
                message[i] = cv[i];
            }

            c_assert_(&message[0]);
            break;
        }

        c = std::pow(CurvStruct_a_param, 2.0);
        r1D[0] *= CurvStruct_a_param;
        r2D[0] *= c;
        r1D[1] *= CurvStruct_a_param;
        r2D[1] *= c;
        r1D[2] *= CurvStruct_a_param;
        r2D[2] *= c;
    }

    //
    // computes approximately the arc length of a parametric spline
    // Arguments    : const queue_coder *ctx_q_splines
    //                double ctx_cfg_NGridLengthSpline
    //                int Curv_sp_index
    //                double u0_tilda
    //                double u1_tilda
    //                double *L
    //                coder::array<double, 2U> &Integrand
    //                coder::array<double, 2U> &u_mid_tilda
    //                coder::array<double, 2U> &du_tilda
    // Return Type  : void
    //
    static void d_SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, double u0_tilda, double u1_tilda, double *L,
        coder::array<double, 2U> &Integrand, coder::array<double, 2U> &u_mid_tilda, coder::array<
        double, 2U> &du_tilda)
    {
        CurvStruct expl_temp;
        coder::array<double, 2U> Spline_sp_CoeffX;
        int loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffY;
        int b_loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        int c_loop_ub;
        coder::array<double, 2U> Spline_sp_knots;
        int d_loop_ub;
        coder::array<bool, 2U> x;
        int e_loop_ub;
        int k;
        int idx;
        int ii_size_idx_1;
        int ii;
        bool exitg1;
        int ii_data[1];
        unsigned int Idx1_data[1];
        int f_loop_ub;
        int b_k;
        int b_ii;
        int b_idx;
        unsigned int Idx2_data[1];
        int i6;
        int i7;
        int g_loop_ub;
        coder::array<double, 2U> u_vec_tilda;
        coder::array<double, 2U> u_tilda;
        int i9;
        int i10;
        int h_loop_ub;
        coder::array<double, 2U> r;
        int i11;
        int scalarLB;
        int vectorUB;
        int i13;
        coder::array<double, 2U> unusedU0;
        coder::array<double, 2U> r1Dx;
        coder::array<double, 2U> unusedU1;
        coder::array<double, 2U> r1Dy;
        coder::array<double, 2U> unusedU2;
        coder::array<double, 2U> r1Dz;
        coder::array<double, 2U> a;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        coder::array<double, 2U> z1;
        int N;
        int i18;
        int b_scalarLB;
        int b_vectorUB;
        int e_k;
        coder::array<double, 2U> b_x;
        int m_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int i19;
        int vlen;
        double b_L;

        //  get the sp structure
        ctx_q_splines->get(Curv_sp_index, (&expl_temp));
        Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
        loop_ub = expl_temp.sp.CoeffX.size(1);
        for (int i = 0; i < loop_ub; i++) {
            Spline_sp_CoeffX[i] = expl_temp.sp.CoeffX[i];
        }

        Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
        b_loop_ub = expl_temp.sp.CoeffY.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            Spline_sp_CoeffY[i1] = expl_temp.sp.CoeffY[i1];
        }

        Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
        c_loop_ub = expl_temp.sp.CoeffZ.size(1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            Spline_sp_CoeffZ[i2] = expl_temp.sp.CoeffZ[i2];
        }

        Spline_sp_knots.set_size(1, expl_temp.sp.knots.size(1));
        d_loop_ub = expl_temp.sp.knots.size(1);
        for (int i3 = 0; i3 < d_loop_ub; i3++) {
            Spline_sp_knots[i3] = expl_temp.sp.knots[i3];
        }

        //  the ORIGINAL spline is parametrized with u_tilda
        //  after cut-off, new parameter is called u.
        //  u=0 corresponds to the first lift-off point
        //  u=1 corresponds to the second lift-off point
        //  u is NOT used in this function
        x.set_size(1, Spline_sp_knots.size(1));
        e_loop_ub = Spline_sp_knots.size(1);
        for (int i4 = 0; i4 < e_loop_ub; i4++) {
            x[i4] = (Spline_sp_knots[i4] > u0_tilda);
        }

        k = (1 <= x.size(1));
        idx = 0;
        ii_size_idx_1 = k;
        ii = 0;
        exitg1 = false;
        while ((!exitg1) && (ii <= x.size(1) - 1)) {
            if (x[ii]) {
                idx = 1;
                ii_data[0] = ii + 1;
                exitg1 = true;
            } else {
                ii++;
            }
        }

        if (k == 1) {
            if (idx == 0) {
                ii_size_idx_1 = 0;
            }
        } else {
            ii_size_idx_1 = (1 <= idx);
        }

        if (0 <= ii_size_idx_1 - 1) {
            Idx1_data[0] = static_cast<unsigned int>(ii_data[0]);
        }

        x.set_size(1, Spline_sp_knots.size(1));
        f_loop_ub = Spline_sp_knots.size(1);
        for (int i5 = 0; i5 < f_loop_ub; i5++) {
            x[i5] = (Spline_sp_knots[i5] < u1_tilda);
        }

        b_k = (1 <= x.size(1));
        b_ii = x.size(1);
        b_idx = 0;
        ii_size_idx_1 = b_k;
        exitg1 = false;
        while ((!exitg1) && (b_ii > 0)) {
            if (x[b_ii - 1]) {
                b_idx = 1;
                ii_data[0] = b_ii;
                exitg1 = true;
            } else {
                b_ii--;
            }
        }

        if (b_k == 1) {
            if (b_idx == 0) {
                ii_size_idx_1 = 0;
            }
        } else {
            ii_size_idx_1 = (1 <= b_idx);
        }

        if (0 <= ii_size_idx_1 - 1) {
            Idx2_data[0] = static_cast<unsigned int>(ii_data[0]);
        }

        if (static_cast<int>(Idx1_data[0]) > static_cast<int>(Idx2_data[0])) {
            i6 = 0;
            i7 = 0;
        } else {
            i6 = static_cast<int>(Idx1_data[0]) - 1;
            i7 = static_cast<int>(Idx2_data[0]);
        }

        g_loop_ub = i7 - i6;
        u_vec_tilda.set_size(1, (g_loop_ub + 2));
        u_vec_tilda[0] = u0_tilda;
        for (int i8 = 0; i8 < g_loop_ub; i8++) {
            u_vec_tilda[i8 + 1] = Spline_sp_knots[i6 + i8];
        }

        u_vec_tilda[g_loop_ub + 1] = u1_tilda;
        u_tilda.set_size(1, 0);

        //  N equally spaced u_tilda values between each pair of knots
        //  from u0_tilda until u1_tilda
        i9 = u_vec_tilda.size(1);
        for (int c_k = 0; c_k <= i9 - 2; c_k++) {
            int i12;
            int i_loop_ub;
            i10 = u_tilda.size(1);
            if (u_tilda.size(1) != 0) {
                if (1 > u_tilda.size(1) - 1) {
                    i10 = 0;
                } else {
                    i10 = u_tilda.size(1) - 1;
                }
            }

            linspace(u_vec_tilda[c_k], u_vec_tilda[c_k + 1], ctx_cfg_NGridLengthSpline, r);
            i12 = i10;
            i_loop_ub = r.size(1);
            i10 += r.size(1);
            u_tilda.set_size(u_tilda.size(0), i10);
            for (int i14 = 0; i14 < i_loop_ub; i14++) {
                u_tilda[i12 + i14] = r[i14];
            }
        }

        //  midpoint values
        if (1 > u_tilda.size(1) - 1) {
            h_loop_ub = 0;
        } else {
            h_loop_ub = u_tilda.size(1) - 1;
        }

        i11 = (2 <= u_tilda.size(1));
        u_mid_tilda.set_size(1, h_loop_ub);
        scalarLB = h_loop_ub & -4;
        vectorUB = scalarLB - 4;
        for (i13 = 0; i13 <= vectorUB; i13 += 4) {
            __m256d r1;
            __m256d r2;
            r1 = _mm256_loadu_pd(&u_tilda[i13]);
            r2 = _mm256_loadu_pd(&u_tilda[i11 + i13]);
            _mm256_storeu_pd(&u_mid_tilda[i13], _mm256_mul_pd(_mm256_set1_pd(0.5), _mm256_add_pd(r1,
                               r2)));
        }

        for (i13 = scalarLB; i13 < h_loop_ub; i13++) {
            u_mid_tilda[i13] = 0.5 * (u_tilda[i13] + u_tilda[i11 + i13]);
        }

        //  midpoint values
        diff(u_tilda, du_tilda);

        //  parametric derivative calculation at each midpoint value
        //  with respect to u_tilda
        c_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, u_mid_tilda, unusedU0, r1Dx);
        c_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, u_mid_tilda, unusedU1, r1Dy);
        c_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, u_mid_tilda, unusedU2, r1Dz);

        //  length (between u0_tilda and u1_tilda) calculation by rectangles method
        a.set_size(3, r1Dx.size(1));
        j_loop_ub = r1Dx.size(1);
        for (int i15 = 0; i15 < j_loop_ub; i15++) {
            a[3 * i15] = r1Dx[i15];
        }

        k_loop_ub = r1Dy.size(1);
        for (int i16 = 0; i16 < k_loop_ub; i16++) {
            a[3 * i16 + 1] = r1Dy[i16];
        }

        l_loop_ub = r1Dz.size(1);
        for (int i17 = 0; i17 < l_loop_ub; i17++) {
            a[3 * i17 + 2] = r1Dz[i17];
        }

        z1.set_size(3, a.size(1));
        N = a.size(1);
        for (int d_k = 0; d_k < N; d_k++) {
            z1[3 * d_k] = std::pow(a[3 * d_k], 2.0);
            z1[3 * d_k + 1] = std::pow(a[3 * d_k + 1], 2.0);
            z1[3 * d_k + 2] = std::pow(a[3 * d_k + 2], 2.0);
        }

        sum(z1, Integrand);
        i18 = Integrand.size(1);
        b_scalarLB = Integrand.size(1) & -4;
        b_vectorUB = b_scalarLB - 4;
        for (e_k = 0; e_k <= b_vectorUB; e_k += 4) {
            __m256d r3;
            r3 = _mm256_loadu_pd(&Integrand[e_k]);
            _mm256_storeu_pd(&Integrand[e_k], _mm256_sqrt_pd(r3));
        }

        for (e_k = b_scalarLB; e_k < i18; e_k++) {
            Integrand[e_k] = std::sqrt(Integrand[e_k]);
        }

        b_x.set_size(1, Integrand.size(1));
        m_loop_ub = Integrand.size(1);
        c_scalarLB = Integrand.size(1) & -4;
        c_vectorUB = c_scalarLB - 4;
        for (i19 = 0; i19 <= c_vectorUB; i19 += 4) {
            __m256d r4;
            __m256d r5;
            r4 = _mm256_loadu_pd(&Integrand[i19]);
            r5 = _mm256_loadu_pd(&du_tilda[i19]);
            _mm256_storeu_pd(&b_x[i19], _mm256_mul_pd(r4, r5));
        }

        for (i19 = c_scalarLB; i19 < m_loop_ub; i19++) {
            b_x[i19] = Integrand[i19] * du_tilda[i19];
        }

        vlen = b_x.size(1);
        if (b_x.size(1) == 0) {
            b_L = 0.0;
        } else {
            double y;
            y = b_x[0];
            for (int f_k = 2; f_k <= vlen; f_k++) {
                double b_y;
                b_y = y;
                if (vlen >= 2) {
                    b_y = y + b_x[f_k - 1];
                }

                y = b_y;
            }

            b_L = y;
        }

        *L = b_L;
    }

    //
    // Arguments    : unsigned long Bl_handle
    //                const coder::array<double, 2U> &coeffs
    //                const double u[10]
    //                double x[10]
    //                double xd[10]
    //                double xdd[10]
    //                double xddd[10]
    // Return Type  : void
    //
    static void d_bspline_eval_vec(unsigned long Bl_handle, const coder::array<double, 2U> &coeffs,
        const double u[10], double x[10], double xd[10], double xdd[10], double xddd[10])
    {
        for (int k = 0; k < 10; k++) {
            x[k] = u[k];
            bspline_eval(Bl_handle, coeffs, &x[k], &xd[k], &xdd[k], &xddd[k]);
        }
    }

    //
    // Arguments    : const coder::array<double, 2U> &x
    //                coder::array<double, 2U> &y
    // Return Type  : void
    //
    static void diff(const coder::array<double, 2U> &x, coder::array<double, 2U> &y)
    {
        int dimSize;
        coder::array<double, 2U> b_y1;
        double tmp1;
        dimSize = x.size(1);
        if (x.size(1) == 0) {
            y.set_size(1, 0);
        } else {
            int u0;
            int b_y;
            u0 = x.size(1) - 1;
            if (u0 < 1) {
                b_y = u0;
            } else {
                b_y = 1;
            }

            if (b_y < 1) {
                y.set_size(1, 0);
            } else {
                int loop_ub;
                b_y1.set_size(1, (x.size(1) - 1));
                if (x.size(1) - 1 != 0) {
                    int ixLead;
                    int iyLead;
                    double work_data_idx_0;
                    ixLead = 1;
                    iyLead = 0;
                    work_data_idx_0 = x[0];
                    for (int m = 2; m <= dimSize; m++) {
                        double d;
                        tmp1 = x[ixLead];
                        d = tmp1;
                        tmp1 -= work_data_idx_0;
                        work_data_idx_0 = d;
                        ixLead++;
                        b_y1[iyLead] = tmp1;
                        iyLead++;
                    }
                }

                y.set_size(1, b_y1.size(1));
                loop_ub = b_y1.size(1);
                for (int i = 0; i < loop_ub; i++) {
                    y[i] = b_y1[i];
                }
            }
        }
    }

    //
    // Arguments    : int numerator
    //                int denominator
    // Return Type  : int
    //
    static int div_s32_floor(int numerator, int denominator)
    {
        int quotient;
        unsigned int absNumerator;
        if (denominator == 0) {
            if (numerator >= 0) {
                quotient = MAX_int32_T;
            } else {
                quotient = MIN_int32_T;
            }
        } else {
            unsigned int absDenominator;
            bool quotientNeedsNegation;
            unsigned int tempAbsQuotient;
            if (numerator < 0) {
                absNumerator = ~static_cast<unsigned int>(numerator) + 1U;
            } else {
                absNumerator = static_cast<unsigned int>(numerator);
            }

            if (denominator < 0) {
                absDenominator = ~static_cast<unsigned int>(denominator) + 1U;
            } else {
                absDenominator = static_cast<unsigned int>(denominator);
            }

            quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
            tempAbsQuotient = absNumerator / absDenominator;
            if (quotientNeedsNegation) {
                absNumerator %= absDenominator;
                if (absNumerator > 0U) {
                    tempAbsQuotient++;
                }

                quotient = -static_cast<int>(tempAbsQuotient);
            } else {
                quotient = static_cast<int>(tempAbsQuotient);
            }
        }

        return quotient;
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double CurvStruct_CoeffP5[6][3]
    //                int CurvStruct_sp_index
    //                double CurvStruct_a_param
    //                double CurvStruct_b_param
    //                double r0D[3]
    //                double r1D[3]
    // Return Type  : void
    //
    static void e_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, double r0D[3],
        double r1D[3])
    {
        double u_vec_tilda;
        double r2D[3];
        double r3D[3];
        CurvStruct expl_temp;
        char message[30];
        coder::array<double, 2U> Spline_sp_CoeffX;
        coder::array<double, 2U> Spline_sp_CoeffY;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        double r0Dx;
        double r1Dx;
        double r2Dx;
        double r3Dx;
        double r0Dy;
        double r1Dy;
        double r2Dy;
        double r3Dy;
        double r0Dz;
        double r1Dz;
        double r2Dz;
        double r3Dz;

        //
        //
        r0D[0] = 0.0;
        r1D[0] = 0.0;
        r0D[1] = 0.0;
        r1D[1] = 0.0;
        r0D[2] = 0.0;
        r1D[2] = 0.0;
        u_vec_tilda = CurvStruct_a_param + CurvStruct_b_param;
        switch (CurvStruct_Type) {
          case CurveType_Line:
            //  line (G01)
            //
            //  parametrization of a straight line between P0 and P1
            //
            r0D[0] = CurvStruct_P1[0] * u_vec_tilda + CurvStruct_P0[0] * (1.0 - u_vec_tilda);
            r0D[1] = CurvStruct_P1[1] * u_vec_tilda + CurvStruct_P0[1] * (1.0 - u_vec_tilda);
            r0D[2] = CurvStruct_P1[2] * u_vec_tilda + CurvStruct_P0[2] * (1.0 - u_vec_tilda);

            //
            r1D[0] = CurvStruct_P1[0] - CurvStruct_P0[0];
            r1D[1] = CurvStruct_P1[1] - CurvStruct_P0[1];
            r1D[2] = CurvStruct_P1[2] - CurvStruct_P0[2];

            //
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            b_EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_evec, CurvStruct_theta,
                        CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            b_EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            {
                int loop_ub;
                int b_loop_ub;
                int c_loop_ub;

                //  BSpline
                ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
                Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
                loop_ub = expl_temp.sp.CoeffX.size(1);
                for (int i1 = 0; i1 < loop_ub; i1++) {
                    Spline_sp_CoeffX[i1] = expl_temp.sp.CoeffX[i1];
                }

                Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
                b_loop_ub = expl_temp.sp.CoeffY.size(1);
                for (int i2 = 0; i2 < b_loop_ub; i2++) {
                    Spline_sp_CoeffY[i2] = expl_temp.sp.CoeffY[i2];
                }

                Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
                c_loop_ub = expl_temp.sp.CoeffZ.size(1);
                for (int i3 = 0; i3 < c_loop_ub; i3++) {
                    Spline_sp_CoeffZ[i3] = expl_temp.sp.CoeffZ[i3];
                }

                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, u_vec_tilda, &r0Dx,
                                   &r1Dx, &r2Dx, &r3Dx);
                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, u_vec_tilda, &r0Dy,
                                   &r1Dy, &r2Dy, &r3Dy);
                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, u_vec_tilda, &r0Dz,
                                   &r1Dz, &r2Dz, &r3Dz);
                r0D[0] = r0Dx;
                r0D[1] = r0Dy;
                r0D[2] = r0Dz;
                r1D[0] = r1Dx;
                r1D[1] = r1Dy;
                r1D[2] = r1Dz;
            }
            break;

          default:
            for (int i = 0; i < 30; i++) {
                message[i] = cv[i];
            }

            c_assert_(&message[0]);
            break;
        }

        r1D[0] *= CurvStruct_a_param;
        r1D[1] *= CurvStruct_a_param;
        r1D[2] *= CurvStruct_a_param;
    }

    //
    // Arguments    : const coder::array<bool, 2U> &x
    //                int i_data[]
    //                int i_size[2]
    // Return Type  : void
    //
    static void eml_find(const coder::array<bool, 2U> &x, int i_data[], int i_size[2])
    {
        int k;
        int idx;
        int ii;
        bool exitg1;
        k = (1 <= x.size(1));
        idx = 0;
        i_size[0] = 1;
        i_size[1] = k;
        ii = 0;
        exitg1 = false;
        while ((!exitg1) && (ii <= x.size(1) - 1)) {
            if (x[ii]) {
                idx = 1;
                i_data[0] = ii + 1;
                exitg1 = true;
            } else {
                ii++;
            }
        }

        if (k == 1) {
            if (idx == 0) {
                i_size[0] = 1;
                i_size[1] = 0;
            }
        } else {
            i_size[1] = (1 <= idx);
        }
    }

    //
    // Arguments    : double d
    //                double b
    //                coder::array<double, 2U> &y
    // Return Type  : void
    //
    static void eml_float_colon(double d, double b, coder::array<double, 2U> &y)
    {
        double ndbl;
        double apnd;
        double cdiff;
        double bnew;
        int n;
        ndbl = std::floor(b / d + 0.5);
        apnd = ndbl * d;
        if (d > 0.0) {
            cdiff = apnd - b;
        } else {
            cdiff = b - apnd;
        }

        if (std::abs(cdiff) < 4.4408920985006262E-16 * std::abs(b)) {
            ndbl++;
            bnew = b;
        } else if (cdiff > 0.0) {
            bnew = (ndbl - 1.0) * d;
        } else {
            ndbl++;
            bnew = apnd;
        }

        if (ndbl >= 0.0) {
            n = static_cast<int>(ndbl);
        } else {
            n = 0;
        }

        y.set_size(1, n);
        if (n > 0) {
            y[0] = 0.0;
            if (n > 1) {
                int nm1d2;
                double kd;
                y[n - 1] = bnew;
                nm1d2 = (n - 1) / 2;
                for (int k = 0; k <= nm1d2 - 2; k++) {
                    kd = (static_cast<double>(k) + 1.0) * d;
                    y[k + 1] = kd;
                    y[(n - k) - 2] = bnew - kd;
                }

                if (nm1d2 << 1 == n - 1) {
                    y[nm1d2] = bnew / 2.0;
                } else {
                    kd = static_cast<double>(nm1d2) * d;
                    y[nm1d2] = kd;
                    y[nm1d2 + 1] = bnew - kd;
                }
            }
        }
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double CurvStruct_CoeffP5[6][3]
    //                int CurvStruct_sp_index
    //                double CurvStruct_a_param
    //                double CurvStruct_b_param
    //                double r0D[3]
    //                double r1D[3]
    // Return Type  : void
    //
    static void f_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, double r0D[3],
        double r1D[3])
    {
        double r2D[3];
        double r3D[3];
        CurvStruct expl_temp;
        char message[30];
        coder::array<double, 2U> Spline_sp_CoeffX;
        coder::array<double, 2U> Spline_sp_CoeffY;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        double r0Dx;
        double r1Dx;
        double r2Dx;
        double r3Dx;
        double r0Dy;
        double r1Dy;
        double r2Dy;
        double r3Dy;
        double r0Dz;
        double r1Dz;
        double r2Dz;
        double r3Dz;

        //
        //
        r0D[0] = 0.0;
        r1D[0] = 0.0;
        r0D[1] = 0.0;
        r1D[1] = 0.0;
        r0D[2] = 0.0;
        r1D[2] = 0.0;
        switch (CurvStruct_Type) {
          case CurveType_Line:
            //  line (G01)
            //
            //  parametrization of a straight line between P0 and P1
            //
            r0D[0] = CurvStruct_P1[0] * CurvStruct_b_param + CurvStruct_P0[0] * (1.0 -
                CurvStruct_b_param);
            r0D[1] = CurvStruct_P1[1] * CurvStruct_b_param + CurvStruct_P0[1] * (1.0 -
                CurvStruct_b_param);
            r0D[2] = CurvStruct_P1[2] * CurvStruct_b_param + CurvStruct_P0[2] * (1.0 -
                CurvStruct_b_param);

            //
            r1D[0] = CurvStruct_P1[0] - CurvStruct_P0[0];
            r1D[1] = CurvStruct_P1[1] - CurvStruct_P0[1];
            r1D[2] = CurvStruct_P1[2] - CurvStruct_P0[2];

            //
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            b_EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_evec, CurvStruct_theta,
                        CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            b_EvalTransP5(CurvStruct_CoeffP5, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            {
                int loop_ub;
                int b_loop_ub;
                int c_loop_ub;

                //  BSpline
                ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
                Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
                loop_ub = expl_temp.sp.CoeffX.size(1);
                for (int i1 = 0; i1 < loop_ub; i1++) {
                    Spline_sp_CoeffX[i1] = expl_temp.sp.CoeffX[i1];
                }

                Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
                b_loop_ub = expl_temp.sp.CoeffY.size(1);
                for (int i2 = 0; i2 < b_loop_ub; i2++) {
                    Spline_sp_CoeffY[i2] = expl_temp.sp.CoeffY[i2];
                }

                Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
                c_loop_ub = expl_temp.sp.CoeffZ.size(1);
                for (int i3 = 0; i3 < c_loop_ub; i3++) {
                    Spline_sp_CoeffZ[i3] = expl_temp.sp.CoeffZ[i3];
                }

                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, CurvStruct_b_param,
                                   &r0Dx, &r1Dx, &r2Dx, &r3Dx);
                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, CurvStruct_b_param,
                                   &r0Dy, &r1Dy, &r2Dy, &r3Dy);
                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, CurvStruct_b_param,
                                   &r0Dz, &r1Dz, &r2Dz, &r3Dz);
                r0D[0] = r0Dx;
                r0D[1] = r0Dy;
                r0D[2] = r0Dz;
                r1D[0] = r1Dx;
                r1D[1] = r1Dy;
                r1D[2] = r1Dz;
            }
            break;

          default:
            for (int i = 0; i < 30; i++) {
                message[i] = cv[i];
            }

            c_assert_(&message[0]);
            break;
        }

        r1D[0] *= CurvStruct_a_param;
        r1D[1] *= CurvStruct_a_param;
        r1D[2] *= CurvStruct_a_param;
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double CurvStruct_CoeffP5[6][3]
    //                int CurvStruct_sp_index
    //                double CurvStruct_a_param
    //                double CurvStruct_b_param
    //                double r0D[3]
    //                double r1D[3]
    //                double r2D[3]
    // Return Type  : void
    //
    static void g_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, double r0D[3],
        double r1D[3], double r2D[3])
    {
        double r3D[3];
        CurvStruct expl_temp;
        char message[30];
        coder::array<double, 2U> Spline_sp_CoeffX;
        double c;
        coder::array<double, 2U> Spline_sp_CoeffY;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        double r0Dx;
        double r1Dx;
        double r2Dx;
        double r3Dx;
        double r0Dy;
        double r1Dy;
        double r2Dy;
        double r3Dy;
        double r0Dz;
        double r1Dz;
        double r2Dz;
        double r3Dz;

        //
        //
        r0D[0] = 0.0;
        r1D[0] = 0.0;
        r2D[0] = 0.0;
        r0D[1] = 0.0;
        r1D[1] = 0.0;
        r2D[1] = 0.0;
        r0D[2] = 0.0;
        r1D[2] = 0.0;
        r2D[2] = 0.0;
        switch (CurvStruct_Type) {
          case CurveType_Line:
            //  line (G01)
            //
            //  parametrization of a straight line between P0 and P1
            //
            r0D[0] = CurvStruct_P1[0] * CurvStruct_b_param + CurvStruct_P0[0] * (1.0 -
                CurvStruct_b_param);
            r0D[1] = CurvStruct_P1[1] * CurvStruct_b_param + CurvStruct_P0[1] * (1.0 -
                CurvStruct_b_param);
            r0D[2] = CurvStruct_P1[2] * CurvStruct_b_param + CurvStruct_P0[2] * (1.0 -
                CurvStruct_b_param);

            //
            r1D[0] = CurvStruct_P1[0] - CurvStruct_P0[0];
            r1D[1] = CurvStruct_P1[1] - CurvStruct_P0[1];
            r1D[2] = CurvStruct_P1[2] - CurvStruct_P0[2];

            //
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            b_EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_evec, CurvStruct_theta,
                        CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            b_EvalTransP5(CurvStruct_CoeffP5, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            {
                int loop_ub;
                int b_loop_ub;
                int c_loop_ub;

                //  BSpline
                ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
                Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
                loop_ub = expl_temp.sp.CoeffX.size(1);
                for (int i1 = 0; i1 < loop_ub; i1++) {
                    Spline_sp_CoeffX[i1] = expl_temp.sp.CoeffX[i1];
                }

                Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
                b_loop_ub = expl_temp.sp.CoeffY.size(1);
                for (int i2 = 0; i2 < b_loop_ub; i2++) {
                    Spline_sp_CoeffY[i2] = expl_temp.sp.CoeffY[i2];
                }

                Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
                c_loop_ub = expl_temp.sp.CoeffZ.size(1);
                for (int i3 = 0; i3 < c_loop_ub; i3++) {
                    Spline_sp_CoeffZ[i3] = expl_temp.sp.CoeffZ[i3];
                }

                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, CurvStruct_b_param,
                                   &r0Dx, &r1Dx, &r2Dx, &r3Dx);
                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, CurvStruct_b_param,
                                   &r0Dy, &r1Dy, &r2Dy, &r3Dy);
                b_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, CurvStruct_b_param,
                                   &r0Dz, &r1Dz, &r2Dz, &r3Dz);
                r0D[0] = r0Dx;
                r0D[1] = r0Dy;
                r0D[2] = r0Dz;
                r1D[0] = r1Dx;
                r1D[1] = r1Dy;
                r1D[2] = r1Dz;
                r2D[0] = r2Dx;
                r2D[1] = r2Dy;
                r2D[2] = r2Dz;
            }
            break;

          default:
            for (int i = 0; i < 30; i++) {
                message[i] = cv[i];
            }

            c_assert_(&message[0]);
            break;
        }

        c = std::pow(CurvStruct_a_param, 2.0);
        r1D[0] *= CurvStruct_a_param;
        r2D[0] *= c;
        r1D[1] *= CurvStruct_a_param;
        r2D[1] *= c;
        r1D[2] *= CurvStruct_a_param;
        r2D[2] *= c;
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double CurvStruct_CoeffP5[6][3]
    //                int CurvStruct_sp_index
    //                double CurvStruct_a_param
    //                double CurvStruct_b_param
    //                coder::array<double, 2U> &u_vec
    //                coder::array<double, 2U> &r0D
    //                coder::array<double, 2U> &r1D
    //                coder::array<double, 2U> &r2D
    //                coder::array<double, 2U> &r3D
    // Return Type  : void
    //
    static void h_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, coder::array<
        double, 2U> &u_vec, coder::array<double, 2U> &r0D, coder::array<double, 2U> &r1D, coder::
        array<double, 2U> &r2D, coder::array<double, 2U> &r3D)
    {
        coder::array<bool, 2U> x;
        int loop_ub;
        bool y;
        int k;
        bool exitg1;
        int b_loop_ub;
        bool b_y;
        int b_k;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        coder::array<double, 2U> u_vec_tilda;
        int g_loop_ub;
        int scalarLB;
        int vectorUB;
        int i6;
        CurvStruct expl_temp;
        char message[30];
        coder::array<double, 2U> Spline_sp_CoeffX;
        int i_loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffY;
        double c;
        int m_loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        double b_c;
        int p_loop_ub;
        coder::array<double, 2U> r0Dx;
        coder::array<double, 2U> r1Dx;
        coder::array<double, 2U> r2Dx;
        coder::array<double, 2U> r3Dx;
        coder::array<double, 2U> r0Dy;
        coder::array<double, 2U> r1Dy;
        coder::array<double, 2U> r2Dy;
        coder::array<double, 2U> r3Dy;
        coder::array<double, 2U> r0Dz;
        coder::array<double, 2U> r1Dz;
        coder::array<double, 2U> r2Dz;
        coder::array<double, 2U> r3Dz;
        x.set_size(1, u_vec.size(1));
        loop_ub = u_vec.size(1);
        for (int i = 0; i < loop_ub; i++) {
            x[i] = (u_vec[i] - 1.0 > 2.2204460492503131E-15);
        }

        y = false;
        k = 0;
        exitg1 = false;
        while ((!exitg1) && (k <= x.size(1) - 1)) {
            if (!x[k]) {
                k++;
            } else {
                y = true;
                exitg1 = true;
            }
        }

        if (y) {
            int end;
            printf("EvalCurvStruct: u_vec > 1\n");
            fflush(stdout);
            end = u_vec.size(1);
            for (int b_i = 0; b_i < end; b_i++) {
                if (u_vec[b_i] > 1.0) {
                    u_vec[b_i] = 1.0;
                }
            }
        }

        x.set_size(1, u_vec.size(1));
        b_loop_ub = u_vec.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            x[i1] = (u_vec[i1] < 0.0);
        }

        b_y = false;
        b_k = 0;
        exitg1 = false;
        while ((!exitg1) && (b_k <= x.size(1) - 1)) {
            if (!x[b_k]) {
                b_k++;
            } else {
                b_y = true;
                exitg1 = true;
            }
        }

        if (b_y) {
            int b_end;
            printf("EvalCurvStruct: u_vec < 0\n");
            fflush(stdout);
            b_end = u_vec.size(1);
            for (int c_i = 0; c_i < b_end; c_i++) {
                if (u_vec[c_i] < 0.0) {
                    u_vec[c_i] = 0.0;
                }
            }
        }

        //
        //
        r0D.set_size(3, u_vec.size(1));
        c_loop_ub = u_vec.size(1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            r0D[3 * i2] = 0.0;
            r0D[3 * i2 + 1] = 0.0;
            r0D[3 * i2 + 2] = 0.0;
        }

        r1D.set_size(3, u_vec.size(1));
        d_loop_ub = u_vec.size(1);
        for (int i3 = 0; i3 < d_loop_ub; i3++) {
            r1D[3 * i3] = 0.0;
            r1D[3 * i3 + 1] = 0.0;
            r1D[3 * i3 + 2] = 0.0;
        }

        r2D.set_size(3, u_vec.size(1));
        e_loop_ub = u_vec.size(1);
        for (int i4 = 0; i4 < e_loop_ub; i4++) {
            r2D[3 * i4] = 0.0;
            r2D[3 * i4 + 1] = 0.0;
            r2D[3 * i4 + 2] = 0.0;
        }

        r3D.set_size(3, u_vec.size(1));
        f_loop_ub = u_vec.size(1);
        for (int i5 = 0; i5 < f_loop_ub; i5++) {
            r3D[3 * i5] = 0.0;
            r3D[3 * i5 + 1] = 0.0;
            r3D[3 * i5 + 2] = 0.0;
        }

        u_vec_tilda.set_size(1, u_vec.size(1));
        g_loop_ub = u_vec.size(1);
        scalarLB = u_vec.size(1) & -4;
        vectorUB = scalarLB - 4;
        for (i6 = 0; i6 <= vectorUB; i6 += 4) {
            __m256d r;
            r = _mm256_loadu_pd(&u_vec[i6]);
            _mm256_storeu_pd(&u_vec_tilda[i6], _mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd
                               (CurvStruct_a_param), r), _mm256_set1_pd(CurvStruct_b_param)));
        }

        for (i6 = scalarLB; i6 < g_loop_ub; i6++) {
            u_vec_tilda[i6] = CurvStruct_a_param * u_vec[i6] + CurvStruct_b_param;
        }

        switch (CurvStruct_Type) {
          case CurveType_Line:
            {
                int j_loop_ub;
                int l_loop_ub;
                int n_loop_ub;
                double a_idx_0;
                double a_idx_1;
                double a_idx_2;
                int s_loop_ub;
                int u_loop_ub;

                //  line (G01)
                //
                //  parametrization of a straight line between P0 and P1
                //
                r0D.set_size(3, u_vec_tilda.size(1));
                j_loop_ub = u_vec_tilda.size(1);
                for (int i10 = 0; i10 < j_loop_ub; i10++) {
                    double d;
                    d = u_vec_tilda[i10];
                    r0D[3 * i10] = CurvStruct_P1[0] * d + CurvStruct_P0[0] * (1.0 - d);
                }

                l_loop_ub = u_vec_tilda.size(1);
                for (int i12 = 0; i12 < l_loop_ub; i12++) {
                    double d1;
                    d1 = u_vec_tilda[i12];
                    r0D[3 * i12 + 1] = CurvStruct_P1[1] * d1 + CurvStruct_P0[1] * (1.0 - d1);
                }

                n_loop_ub = u_vec_tilda.size(1);
                for (int i14 = 0; i14 < n_loop_ub; i14++) {
                    double d2;
                    d2 = u_vec_tilda[i14];
                    r0D[3 * i14 + 2] = CurvStruct_P1[2] * d2 + CurvStruct_P0[2] * (1.0 - d2);
                }

                //
                a_idx_0 = CurvStruct_P1[0] - CurvStruct_P0[0];
                a_idx_1 = CurvStruct_P1[1] - CurvStruct_P0[1];
                a_idx_2 = CurvStruct_P1[2] - CurvStruct_P0[2];
                r1D.set_size(3, u_vec_tilda.size(1));
                if (u_vec_tilda.size(1) != 0) {
                    int i18;
                    i18 = u_vec_tilda.size(1) - 1;
                    for (int t = 0; t <= i18; t++) {
                        r1D[3 * t] = a_idx_0;
                        r1D[3 * t + 1] = a_idx_1;
                        r1D[3 * t + 2] = a_idx_2;
                    }
                }

                //
                r2D.set_size(3, u_vec_tilda.size(1));
                s_loop_ub = u_vec_tilda.size(1);
                for (int i20 = 0; i20 < s_loop_ub; i20++) {
                    r2D[3 * i20] = 0.0;
                    r2D[3 * i20 + 1] = 0.0;
                    r2D[3 * i20 + 2] = 0.0;
                }

                r3D.set_size(3, u_vec_tilda.size(1));
                u_loop_ub = u_vec_tilda.size(1);
                for (int i22 = 0; i22 < u_loop_ub; i22++) {
                    r3D[3 * i22] = 0.0;
                    r3D[3 * i22 + 1] = 0.0;
                    r3D[3 * i22 + 2] = 0.0;
                }
            }
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_evec, CurvStruct_theta,
                      CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            {
                int h_loop_ub;
                int k_loop_ub;
                int o_loop_ub;
                int q_loop_ub;
                int r_loop_ub;
                int t_loop_ub;
                int v_loop_ub;
                int w_loop_ub;
                int x_loop_ub;
                int y_loop_ub;
                int ab_loop_ub;
                int bb_loop_ub;
                int cb_loop_ub;
                int db_loop_ub;
                int eb_loop_ub;

                //  BSpline
                ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
                Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
                h_loop_ub = expl_temp.sp.CoeffX.size(1);
                for (int i8 = 0; i8 < h_loop_ub; i8++) {
                    Spline_sp_CoeffX[i8] = expl_temp.sp.CoeffX[i8];
                }

                Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
                k_loop_ub = expl_temp.sp.CoeffY.size(1);
                for (int i11 = 0; i11 < k_loop_ub; i11++) {
                    Spline_sp_CoeffY[i11] = expl_temp.sp.CoeffY[i11];
                }

                Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
                o_loop_ub = expl_temp.sp.CoeffZ.size(1);
                for (int i15 = 0; i15 < o_loop_ub; i15++) {
                    Spline_sp_CoeffZ[i15] = expl_temp.sp.CoeffZ[i15];
                }

                bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, u_vec_tilda, r0Dx, r1Dx,
                                 r2Dx, r3Dx);
                bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, u_vec_tilda, r0Dy, r1Dy,
                                 r2Dy, r3Dy);
                bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, u_vec_tilda, r0Dz, r1Dz,
                                 r2Dz, r3Dz);
                r0D.set_size(3, r0Dx.size(1));
                q_loop_ub = r0Dx.size(1);
                for (int i17 = 0; i17 < q_loop_ub; i17++) {
                    r0D[3 * i17] = r0Dx[i17];
                }

                r_loop_ub = r0Dy.size(1);
                for (int i19 = 0; i19 < r_loop_ub; i19++) {
                    r0D[3 * i19 + 1] = r0Dy[i19];
                }

                t_loop_ub = r0Dz.size(1);
                for (int i21 = 0; i21 < t_loop_ub; i21++) {
                    r0D[3 * i21 + 2] = r0Dz[i21];
                }

                r1D.set_size(3, r1Dx.size(1));
                v_loop_ub = r1Dx.size(1);
                for (int i23 = 0; i23 < v_loop_ub; i23++) {
                    r1D[3 * i23] = r1Dx[i23];
                }

                w_loop_ub = r1Dy.size(1);
                for (int i24 = 0; i24 < w_loop_ub; i24++) {
                    r1D[3 * i24 + 1] = r1Dy[i24];
                }

                x_loop_ub = r1Dz.size(1);
                for (int i25 = 0; i25 < x_loop_ub; i25++) {
                    r1D[3 * i25 + 2] = r1Dz[i25];
                }

                r2D.set_size(3, r2Dx.size(1));
                y_loop_ub = r2Dx.size(1);
                for (int i26 = 0; i26 < y_loop_ub; i26++) {
                    r2D[3 * i26] = r2Dx[i26];
                }

                ab_loop_ub = r2Dy.size(1);
                for (int i27 = 0; i27 < ab_loop_ub; i27++) {
                    r2D[3 * i27 + 1] = r2Dy[i27];
                }

                bb_loop_ub = r2Dz.size(1);
                for (int i28 = 0; i28 < bb_loop_ub; i28++) {
                    r2D[3 * i28 + 2] = r2Dz[i28];
                }

                r3D.set_size(3, r3Dx.size(1));
                cb_loop_ub = r3Dx.size(1);
                for (int i29 = 0; i29 < cb_loop_ub; i29++) {
                    r3D[3 * i29] = r3Dx[i29];
                }

                db_loop_ub = r3Dy.size(1);
                for (int i30 = 0; i30 < db_loop_ub; i30++) {
                    r3D[3 * i30 + 1] = r3Dy[i30];
                }

                eb_loop_ub = r3Dz.size(1);
                for (int i31 = 0; i31 < eb_loop_ub; i31++) {
                    r3D[3 * i31 + 2] = r3Dz[i31];
                }
            }
            break;

          default:
            for (int i7 = 0; i7 < 30; i7++) {
                message[i7] = cv[i7];
            }

            c_assert_(&message[0]);
            break;
        }

        r1D.set_size(3, r1D.size(1));
        i_loop_ub = r1D.size(1);
        for (int i9 = 0; i9 < i_loop_ub; i9++) {
            r1D[3 * i9] = CurvStruct_a_param * r1D[3 * i9];
            r1D[3 * i9 + 1] = CurvStruct_a_param * r1D[3 * i9 + 1];
            r1D[3 * i9 + 2] = CurvStruct_a_param * r1D[3 * i9 + 2];
        }

        c = std::pow(CurvStruct_a_param, 2.0);
        r2D.set_size(3, r2D.size(1));
        m_loop_ub = r2D.size(1);
        for (int i13 = 0; i13 < m_loop_ub; i13++) {
            r2D[3 * i13] = c * r2D[3 * i13];
            r2D[3 * i13 + 1] = c * r2D[3 * i13 + 1];
            r2D[3 * i13 + 2] = c * r2D[3 * i13 + 2];
        }

        b_c = std::pow(CurvStruct_a_param, 3.0);
        r3D.set_size(3, r3D.size(1));
        p_loop_ub = r3D.size(1);
        for (int i16 = 0; i16 < p_loop_ub; i16++) {
            r3D[3 * i16] = b_c * r3D[3 * i16];
            r3D[3 * i16 + 1] = b_c * r3D[3 * i16 + 1];
            r3D[3 * i16 + 2] = b_c * r3D[3 * i16 + 2];
        }
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double CurvStruct_CoeffP5[6][3]
    //                int CurvStruct_sp_index
    //                double CurvStruct_a_param
    //                double CurvStruct_b_param
    //                double r0D[10][3]
    //                double r1D[10][3]
    //                double r2D[10][3]
    //                double r3D[10][3]
    // Return Type  : void
    //
    static void i_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, double r0D[10][3],
        double r1D[10][3], double r2D[10][3], double r3D[10][3])
    {
        double u_vec_tilda[10];
        CurvStruct expl_temp;
        char message[30];
        coder::array<double, 2U> Spline_sp_CoeffX;
        double c;
        double b_c;
        coder::array<double, 2U> Spline_sp_CoeffY;
        double p5_1D[5][3];
        coder::array<double, 2U> Spline_sp_CoeffZ;
        double p5_2D[4][3];
        double r0Dx[10];
        double r1Dx[10];
        double r2Dx[10];
        double r3Dx[10];
        double r0Dy[10];
        double r1Dy[10];
        double r2Dy[10];
        double r3Dy[10];
        double r0Dz[10];
        double r1Dz[10];
        double r2Dz[10];
        double r3Dz[10];
        double p5_3D[3][3];

        //
        //
        for (int i = 0; i < 10; i++) {
            r0D[i][0] = 0.0;
            r1D[i][0] = 0.0;
            r2D[i][0] = 0.0;
            r3D[i][0] = 0.0;
            r0D[i][1] = 0.0;
            r1D[i][1] = 0.0;
            r2D[i][1] = 0.0;
            r3D[i][1] = 0.0;
            r0D[i][2] = 0.0;
            r1D[i][2] = 0.0;
            r2D[i][2] = 0.0;
            r3D[i][2] = 0.0;
            u_vec_tilda[i] = CurvStruct_a_param * (0.1111111111111111 * static_cast<double>(i)) +
                CurvStruct_b_param;
        }

        switch (CurvStruct_Type) {
          case CurveType_Line:
            {
                double a_idx_0;
                double a_idx_1;
                double a_idx_2;

                //  line (G01)
                //
                //  parametrization of a straight line between P0 and P1
                //
                //
                a_idx_0 = CurvStruct_P1[0] - CurvStruct_P0[0];
                a_idx_1 = CurvStruct_P1[1] - CurvStruct_P0[1];
                a_idx_2 = CurvStruct_P1[2] - CurvStruct_P0[2];
                for (int t = 0; t < 10; t++) {
                    r0D[t][0] = CurvStruct_P1[0] * u_vec_tilda[t] + CurvStruct_P0[0] * (1.0 -
                        u_vec_tilda[t]);
                    r0D[t][1] = CurvStruct_P1[1] * u_vec_tilda[t] + CurvStruct_P0[1] * (1.0 -
                        u_vec_tilda[t]);
                    r0D[t][2] = CurvStruct_P1[2] * u_vec_tilda[t] + CurvStruct_P0[2] * (1.0 -
                        u_vec_tilda[t]);
                    r1D[t][0] = a_idx_0;
                    r1D[t][1] = a_idx_1;
                    r1D[t][2] = a_idx_2;
                }

                //
            }
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            c_EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_evec, CurvStruct_theta,
                        CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            {
                //  polynomial transition
                //
                // MYPOLYDER Differentiate polynomial.
                //
                // u  = u(:).';
                for (int k = 0; k < 5; k++) {
                    int p5_1D_tmp;
                    p5_1D_tmp = 5 - k;
                    p5_1D[k][0] = CurvStruct_CoeffP5[k][0] * static_cast<double>(p5_1D_tmp);
                    p5_1D[k][1] = CurvStruct_CoeffP5[k][1] * static_cast<double>(p5_1D_tmp);
                    p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * static_cast<double>(p5_1D_tmp);
                }

                // MYPOLYDER Differentiate polynomial.
                //
                // u  = u(:).';
                for (int b_k = 0; b_k < 4; b_k++) {
                    int p5_2D_tmp;
                    p5_2D_tmp = 4 - b_k;
                    p5_2D[b_k][0] = p5_1D[b_k][0] * static_cast<double>(p5_2D_tmp);
                    p5_2D[b_k][1] = p5_1D[b_k][1] * static_cast<double>(p5_2D_tmp);
                    p5_2D[b_k][2] = p5_1D[b_k][2] * static_cast<double>(p5_2D_tmp);
                }

                // MYPOLYDER Differentiate polynomial.
                //
                // u  = u(:).';
                for (int c_k = 0; c_k < 3; c_k++) {
                    int p5_3D_tmp;
                    p5_3D_tmp = 3 - c_k;
                    p5_3D[c_k][0] = p5_2D[c_k][0] * static_cast<double>(p5_3D_tmp);
                    p5_3D[c_k][1] = p5_2D[c_k][1] * static_cast<double>(p5_3D_tmp);
                    p5_3D[c_k][2] = p5_2D[c_k][2] * static_cast<double>(p5_3D_tmp);
                }

                //
                // POLYVAL Evaluate array of polynomials with same degree.
                //
                //
                //  Use Horner's method for general case where X is an array.
                for (int b_t = 0; b_t < 10; b_t++) {
                    r0D[b_t][0] = CurvStruct_CoeffP5[0][0];
                    r0D[b_t][1] = CurvStruct_CoeffP5[0][1];
                    r0D[b_t][2] = CurvStruct_CoeffP5[0][2];
                }

                for (int b_i = 0; b_i < 5; b_i++) {
                    double d;
                    double d1;
                    double d2;
                    d = CurvStruct_CoeffP5[b_i + 1][0];
                    d1 = CurvStruct_CoeffP5[b_i + 1][1];
                    d2 = CurvStruct_CoeffP5[b_i + 1][2];
                    for (int d_k = 0; d_k < 10; d_k++) {
                        r0D[d_k][0] = u_vec_tilda[d_k] * r0D[d_k][0] + d;
                        r0D[d_k][1] = u_vec_tilda[d_k] * r0D[d_k][1] + d1;
                        r0D[d_k][2] = u_vec_tilda[d_k] * r0D[d_k][2] + d2;
                    }
                }

                // POLYVAL Evaluate array of polynomials with same degree.
                //
                //
                //  Use Horner's method for general case where X is an array.
                for (int c_t = 0; c_t < 10; c_t++) {
                    r1D[c_t][0] = p5_1D[0][0];
                    r1D[c_t][1] = p5_1D[0][1];
                    r1D[c_t][2] = p5_1D[0][2];
                }

                for (int c_i = 0; c_i < 4; c_i++) {
                    double d3;
                    double d4;
                    double d5;
                    d3 = p5_1D[c_i + 1][0];
                    d4 = p5_1D[c_i + 1][1];
                    d5 = p5_1D[c_i + 1][2];
                    for (int e_k = 0; e_k < 10; e_k++) {
                        r1D[e_k][0] = u_vec_tilda[e_k] * r1D[e_k][0] + d3;
                        r1D[e_k][1] = u_vec_tilda[e_k] * r1D[e_k][1] + d4;
                        r1D[e_k][2] = u_vec_tilda[e_k] * r1D[e_k][2] + d5;
                    }
                }

                // POLYVAL Evaluate array of polynomials with same degree.
                //
                //
                //  Use Horner's method for general case where X is an array.
                for (int d_t = 0; d_t < 10; d_t++) {
                    r2D[d_t][0] = p5_2D[0][0];
                    r2D[d_t][1] = p5_2D[0][1];
                    r2D[d_t][2] = p5_2D[0][2];
                }

                for (int d_i = 0; d_i < 3; d_i++) {
                    double d6;
                    double d7;
                    double d8;
                    d6 = p5_2D[d_i + 1][0];
                    d7 = p5_2D[d_i + 1][1];
                    d8 = p5_2D[d_i + 1][2];
                    for (int f_k = 0; f_k < 10; f_k++) {
                        r2D[f_k][0] = u_vec_tilda[f_k] * r2D[f_k][0] + d6;
                        r2D[f_k][1] = u_vec_tilda[f_k] * r2D[f_k][1] + d7;
                        r2D[f_k][2] = u_vec_tilda[f_k] * r2D[f_k][2] + d8;
                    }
                }

                // POLYVAL Evaluate array of polynomials with same degree.
                //
                //
                //  Use Horner's method for general case where X is an array.
                for (int e_t = 0; e_t < 10; e_t++) {
                    r3D[e_t][0] = p5_3D[0][0];
                    r3D[e_t][1] = p5_3D[0][1];
                    r3D[e_t][2] = p5_3D[0][2];
                }

                for (int e_i = 0; e_i < 2; e_i++) {
                    double d9;
                    double d10;
                    double d11;
                    d9 = p5_3D[e_i + 1][0];
                    d10 = p5_3D[e_i + 1][1];
                    d11 = p5_3D[e_i + 1][2];
                    for (int g_k = 0; g_k < 10; g_k++) {
                        r3D[g_k][0] = u_vec_tilda[g_k] * r3D[g_k][0] + d9;
                        r3D[g_k][1] = u_vec_tilda[g_k] * r3D[g_k][1] + d10;
                        r3D[g_k][2] = u_vec_tilda[g_k] * r3D[g_k][2] + d11;
                    }
                }
            }
            break;

          case CurveType_Spline:
            {
                int loop_ub;
                int b_loop_ub;
                int c_loop_ub;

                //  BSpline
                ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
                Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
                loop_ub = expl_temp.sp.CoeffX.size(1);
                for (int i2 = 0; i2 < loop_ub; i2++) {
                    Spline_sp_CoeffX[i2] = expl_temp.sp.CoeffX[i2];
                }

                Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
                b_loop_ub = expl_temp.sp.CoeffY.size(1);
                for (int i4 = 0; i4 < b_loop_ub; i4++) {
                    Spline_sp_CoeffY[i4] = expl_temp.sp.CoeffY[i4];
                }

                Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
                c_loop_ub = expl_temp.sp.CoeffZ.size(1);
                for (int i5 = 0; i5 < c_loop_ub; i5++) {
                    Spline_sp_CoeffZ[i5] = expl_temp.sp.CoeffZ[i5];
                }

                d_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, u_vec_tilda, r0Dx, r1Dx,
                                   r2Dx, r3Dx);
                d_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, u_vec_tilda, r0Dy, r1Dy,
                                   r2Dy, r3Dy);
                d_bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, u_vec_tilda, r0Dz, r1Dz,
                                   r2Dz, r3Dz);
                for (int i6 = 0; i6 < 10; i6++) {
                    r0D[i6][0] = r0Dx[i6];
                    r0D[i6][1] = r0Dy[i6];
                    r0D[i6][2] = r0Dz[i6];
                    r1D[i6][0] = r1Dx[i6];
                    r1D[i6][1] = r1Dy[i6];
                    r1D[i6][2] = r1Dz[i6];
                    r2D[i6][0] = r2Dx[i6];
                    r2D[i6][1] = r2Dy[i6];
                    r2D[i6][2] = r2Dz[i6];
                    r3D[i6][0] = r3Dx[i6];
                    r3D[i6][1] = r3Dy[i6];
                    r3D[i6][2] = r3Dz[i6];
                }
            }
            break;

          default:
            for (int i1 = 0; i1 < 30; i1++) {
                message[i1] = cv[i1];
            }

            c_assert_(&message[0]);
            break;
        }

        c = std::pow(CurvStruct_a_param, 2.0);
        b_c = std::pow(CurvStruct_a_param, 3.0);
        for (int i3 = 0; i3 < 10; i3++) {
            r1D[i3][0] *= CurvStruct_a_param;
            r2D[i3][0] *= c;
            r3D[i3][0] *= b_c;
            r1D[i3][1] *= CurvStruct_a_param;
            r2D[i3][1] *= c;
            r3D[i3][1] *= b_c;
            r1D[i3][2] *= CurvStruct_a_param;
            r2D[i3][2] *= c;
            r3D[i3][2] *= b_c;
        }
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double CurvStruct_CoeffP5[6][3]
    //                int CurvStruct_sp_index
    //                double CurvStruct_a_param
    //                double CurvStruct_b_param
    //                coder::array<double, 2U> &u_vec
    //                coder::array<double, 2U> &r0D
    //                coder::array<double, 2U> &r1D
    //                coder::array<double, 2U> &r2D
    // Return Type  : void
    //
    static void j_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_evec[3],
        double CurvStruct_theta, double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3], int
        CurvStruct_sp_index, double CurvStruct_a_param, double CurvStruct_b_param, coder::array<
        double, 2U> &u_vec, coder::array<double, 2U> &r0D, coder::array<double, 2U> &r1D, coder::
        array<double, 2U> &r2D)
    {
        coder::array<bool, 2U> x;
        int loop_ub;
        bool y;
        int k;
        bool exitg1;
        int b_loop_ub;
        bool b_y;
        int b_k;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        coder::array<double, 2U> u_vec_tilda;
        int f_loop_ub;
        int scalarLB;
        int vectorUB;
        int i5;
        coder::array<double, 2U> r3D;
        CurvStruct expl_temp;
        char message[30];
        coder::array<double, 2U> Spline_sp_CoeffX;
        int h_loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffY;
        double c;
        int l_loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        coder::array<double, 2U> r0Dx;
        coder::array<double, 2U> r1Dx;
        coder::array<double, 2U> r2Dx;
        coder::array<double, 2U> r3Dx;
        coder::array<double, 2U> r0Dy;
        coder::array<double, 2U> r1Dy;
        coder::array<double, 2U> r2Dy;
        coder::array<double, 2U> r3Dy;
        coder::array<double, 2U> r0Dz;
        coder::array<double, 2U> r1Dz;
        coder::array<double, 2U> r2Dz;
        coder::array<double, 2U> r3Dz;
        x.set_size(1, u_vec.size(1));
        loop_ub = u_vec.size(1);
        for (int i = 0; i < loop_ub; i++) {
            x[i] = (u_vec[i] - 1.0 > 2.2204460492503131E-15);
        }

        y = false;
        k = 0;
        exitg1 = false;
        while ((!exitg1) && (k <= x.size(1) - 1)) {
            if (!x[k]) {
                k++;
            } else {
                y = true;
                exitg1 = true;
            }
        }

        if (y) {
            int end;
            printf("EvalCurvStruct: u_vec > 1\n");
            fflush(stdout);
            end = u_vec.size(1);
            for (int b_i = 0; b_i < end; b_i++) {
                if (u_vec[b_i] > 1.0) {
                    u_vec[b_i] = 1.0;
                }
            }
        }

        x.set_size(1, u_vec.size(1));
        b_loop_ub = u_vec.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            x[i1] = (u_vec[i1] < 0.0);
        }

        b_y = false;
        b_k = 0;
        exitg1 = false;
        while ((!exitg1) && (b_k <= x.size(1) - 1)) {
            if (!x[b_k]) {
                b_k++;
            } else {
                b_y = true;
                exitg1 = true;
            }
        }

        if (b_y) {
            int b_end;
            printf("EvalCurvStruct: u_vec < 0\n");
            fflush(stdout);
            b_end = u_vec.size(1);
            for (int c_i = 0; c_i < b_end; c_i++) {
                if (u_vec[c_i] < 0.0) {
                    u_vec[c_i] = 0.0;
                }
            }
        }

        //
        //
        r0D.set_size(3, u_vec.size(1));
        c_loop_ub = u_vec.size(1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            r0D[3 * i2] = 0.0;
            r0D[3 * i2 + 1] = 0.0;
            r0D[3 * i2 + 2] = 0.0;
        }

        r1D.set_size(3, u_vec.size(1));
        d_loop_ub = u_vec.size(1);
        for (int i3 = 0; i3 < d_loop_ub; i3++) {
            r1D[3 * i3] = 0.0;
            r1D[3 * i3 + 1] = 0.0;
            r1D[3 * i3 + 2] = 0.0;
        }

        r2D.set_size(3, u_vec.size(1));
        e_loop_ub = u_vec.size(1);
        for (int i4 = 0; i4 < e_loop_ub; i4++) {
            r2D[3 * i4] = 0.0;
            r2D[3 * i4 + 1] = 0.0;
            r2D[3 * i4 + 2] = 0.0;
        }

        u_vec_tilda.set_size(1, u_vec.size(1));
        f_loop_ub = u_vec.size(1);
        scalarLB = u_vec.size(1) & -4;
        vectorUB = scalarLB - 4;
        for (i5 = 0; i5 <= vectorUB; i5 += 4) {
            __m256d r;
            r = _mm256_loadu_pd(&u_vec[i5]);
            _mm256_storeu_pd(&u_vec_tilda[i5], _mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd
                               (CurvStruct_a_param), r), _mm256_set1_pd(CurvStruct_b_param)));
        }

        for (i5 = scalarLB; i5 < f_loop_ub; i5++) {
            u_vec_tilda[i5] = CurvStruct_a_param * u_vec[i5] + CurvStruct_b_param;
        }

        switch (CurvStruct_Type) {
          case CurveType_Line:
            {
                int i_loop_ub;
                int k_loop_ub;
                int m_loop_ub;
                double a_idx_0;
                double a_idx_1;
                double a_idx_2;
                int q_loop_ub;

                //  line (G01)
                //
                //  parametrization of a straight line between P0 and P1
                //
                r0D.set_size(3, u_vec_tilda.size(1));
                i_loop_ub = u_vec_tilda.size(1);
                for (int i9 = 0; i9 < i_loop_ub; i9++) {
                    double d;
                    d = u_vec_tilda[i9];
                    r0D[3 * i9] = CurvStruct_P1[0] * d + CurvStruct_P0[0] * (1.0 - d);
                }

                k_loop_ub = u_vec_tilda.size(1);
                for (int i11 = 0; i11 < k_loop_ub; i11++) {
                    double d1;
                    d1 = u_vec_tilda[i11];
                    r0D[3 * i11 + 1] = CurvStruct_P1[1] * d1 + CurvStruct_P0[1] * (1.0 - d1);
                }

                m_loop_ub = u_vec_tilda.size(1);
                for (int i13 = 0; i13 < m_loop_ub; i13++) {
                    double d2;
                    d2 = u_vec_tilda[i13];
                    r0D[3 * i13 + 2] = CurvStruct_P1[2] * d2 + CurvStruct_P0[2] * (1.0 - d2);
                }

                //
                a_idx_0 = CurvStruct_P1[0] - CurvStruct_P0[0];
                a_idx_1 = CurvStruct_P1[1] - CurvStruct_P0[1];
                a_idx_2 = CurvStruct_P1[2] - CurvStruct_P0[2];
                r1D.set_size(3, u_vec_tilda.size(1));
                if (u_vec_tilda.size(1) != 0) {
                    int i16;
                    i16 = u_vec_tilda.size(1) - 1;
                    for (int t = 0; t <= i16; t++) {
                        r1D[3 * t] = a_idx_0;
                        r1D[3 * t + 1] = a_idx_1;
                        r1D[3 * t + 2] = a_idx_2;
                    }
                }

                //
                r2D.set_size(3, u_vec_tilda.size(1));
                q_loop_ub = u_vec_tilda.size(1);
                for (int i18 = 0; i18 < q_loop_ub; i18++) {
                    r2D[3 * i18] = 0.0;
                    r2D[3 * i18 + 1] = 0.0;
                    r2D[3 * i18 + 2] = 0.0;
                }
            }
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_evec, CurvStruct_theta,
                      CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            {
                int g_loop_ub;
                int j_loop_ub;
                int n_loop_ub;
                int o_loop_ub;
                int p_loop_ub;
                int r_loop_ub;
                int s_loop_ub;
                int t_loop_ub;
                int u_loop_ub;
                int v_loop_ub;
                int w_loop_ub;
                int x_loop_ub;

                //  BSpline
                ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
                Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
                g_loop_ub = expl_temp.sp.CoeffX.size(1);
                for (int i7 = 0; i7 < g_loop_ub; i7++) {
                    Spline_sp_CoeffX[i7] = expl_temp.sp.CoeffX[i7];
                }

                Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
                j_loop_ub = expl_temp.sp.CoeffY.size(1);
                for (int i10 = 0; i10 < j_loop_ub; i10++) {
                    Spline_sp_CoeffY[i10] = expl_temp.sp.CoeffY[i10];
                }

                Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
                n_loop_ub = expl_temp.sp.CoeffZ.size(1);
                for (int i14 = 0; i14 < n_loop_ub; i14++) {
                    Spline_sp_CoeffZ[i14] = expl_temp.sp.CoeffZ[i14];
                }

                bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, u_vec_tilda, r0Dx, r1Dx,
                                 r2Dx, r3Dx);
                bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, u_vec_tilda, r0Dy, r1Dy,
                                 r2Dy, r3Dy);
                bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, u_vec_tilda, r0Dz, r1Dz,
                                 r2Dz, r3Dz);
                r0D.set_size(3, r0Dx.size(1));
                o_loop_ub = r0Dx.size(1);
                for (int i15 = 0; i15 < o_loop_ub; i15++) {
                    r0D[3 * i15] = r0Dx[i15];
                }

                p_loop_ub = r0Dy.size(1);
                for (int i17 = 0; i17 < p_loop_ub; i17++) {
                    r0D[3 * i17 + 1] = r0Dy[i17];
                }

                r_loop_ub = r0Dz.size(1);
                for (int i19 = 0; i19 < r_loop_ub; i19++) {
                    r0D[3 * i19 + 2] = r0Dz[i19];
                }

                r1D.set_size(3, r1Dx.size(1));
                s_loop_ub = r1Dx.size(1);
                for (int i20 = 0; i20 < s_loop_ub; i20++) {
                    r1D[3 * i20] = r1Dx[i20];
                }

                t_loop_ub = r1Dy.size(1);
                for (int i21 = 0; i21 < t_loop_ub; i21++) {
                    r1D[3 * i21 + 1] = r1Dy[i21];
                }

                u_loop_ub = r1Dz.size(1);
                for (int i22 = 0; i22 < u_loop_ub; i22++) {
                    r1D[3 * i22 + 2] = r1Dz[i22];
                }

                r2D.set_size(3, r2Dx.size(1));
                v_loop_ub = r2Dx.size(1);
                for (int i23 = 0; i23 < v_loop_ub; i23++) {
                    r2D[3 * i23] = r2Dx[i23];
                }

                w_loop_ub = r2Dy.size(1);
                for (int i24 = 0; i24 < w_loop_ub; i24++) {
                    r2D[3 * i24 + 1] = r2Dy[i24];
                }

                x_loop_ub = r2Dz.size(1);
                for (int i25 = 0; i25 < x_loop_ub; i25++) {
                    r2D[3 * i25 + 2] = r2Dz[i25];
                }
            }
            break;

          default:
            for (int i6 = 0; i6 < 30; i6++) {
                message[i6] = cv[i6];
            }

            c_assert_(&message[0]);
            break;
        }

        r1D.set_size(3, r1D.size(1));
        h_loop_ub = r1D.size(1);
        for (int i8 = 0; i8 < h_loop_ub; i8++) {
            r1D[3 * i8] = CurvStruct_a_param * r1D[3 * i8];
            r1D[3 * i8 + 1] = CurvStruct_a_param * r1D[3 * i8 + 1];
            r1D[3 * i8 + 2] = CurvStruct_a_param * r1D[3 * i8 + 2];
        }

        c = std::pow(CurvStruct_a_param, 2.0);
        r2D.set_size(3, r2D.size(1));
        l_loop_ub = r2D.size(1);
        for (int i12 = 0; i12 < l_loop_ub; i12++) {
            r2D[3 * i12] = c * r2D[3 * i12];
            r2D[3 * i12 + 1] = c * r2D[3 * i12 + 1];
            r2D[3 * i12 + 2] = c * r2D[3 * i12 + 2];
        }
    }

    //
    // Arguments    : const double x_data[]
    //                const int x_size[1]
    //                double *ex
    //                int *idx
    // Return Type  : void
    //
    static void minimum(const double x_data[], const int x_size[1], double *ex, int *idx)
    {
        int n;
        n = x_size[0];
        if (x_size[0] <= 2) {
            if (x_size[0] == 1) {
                *ex = x_data[0];
                *idx = 1;
            } else if (x_data[0] > x_data[1]) {
                *ex = x_data[1];
                *idx = 2;
            } else {
                *ex = x_data[0];
                *idx = 1;
            }
        } else {
            double b_ex;
            b_ex = x_data[0];
            *idx = 1;
            for (int k = 2; k <= n; k++) {
                double d;
                d = x_data[k - 1];
                if (b_ex > d) {
                    b_ex = d;
                    *idx = k;
                }
            }

            *ex = b_ex;
        }
    }

    //
    // Arguments    : const coder::array<double, 2U> &A
    //                const coder::array<double, 1U> &B
    //                coder::array<double, 1U> &Y
    // Return Type  : void
    //
    static void mldiv(const coder::array<double, 2U> &A, const coder::array<double, 1U> &B, coder::
                      array<double, 1U> &Y)
    {
        coder::array<int, 2U> jpvt;
        coder::array<double, 2U> b_A;
        coder::array<int, 2U> ipiv;
        coder::array<double, 1U> tau;
        coder::array<double, 1U> b_B;
        int jy;
        int jA;
        int iy;
        int b_ix;
        coder::array<double, 2U> x;
        double wj;
        int i_i;
        if (A.size(0) == A.size(1)) {
            int u0;
            int u1;
            int y;
            int c_u0;
            int b_n;
            int LDA;
            int b_loop_ub;
            int yk;
            int ldap1;
            int d_u0;
            int i6;
            int f_loop_ub;
            int b_LDA;
            int i_loop_ub;
            u0 = A.size(0);
            u1 = A.size(1);
            if (u0 < u1) {
                y = u0;
            } else {
                y = u1;
            }

            c_u0 = B.size(0);
            if (c_u0 < y) {
                b_n = c_u0;
            } else {
                b_n = y;
            }

            LDA = A.size(0);
            b_A.set_size(A.size(0), A.size(1));
            b_loop_ub = A.size(1);
            for (int i1 = 0; i1 < b_loop_ub; i1++) {
                int d_loop_ub;
                d_loop_ub = A.size(0);
                for (int i3 = 0; i3 < d_loop_ub; i3++) {
                    b_A[i3 + b_A.size(0) * i1] = A[i3 + A.size(0) * i1];
                }
            }

            ipiv.set_size(1, b_n);
            ipiv[0] = 1;
            yk = 1;
            for (int b_k = 2; b_k <= b_n; b_k++) {
                yk++;
                ipiv[b_k - 1] = yk;
            }

            ldap1 = A.size(0);
            d_u0 = b_n - 1;
            if (d_u0 < b_n) {
                i6 = d_u0;
            } else {
                i6 = b_n;
            }

            for (int j = 0; j < i6; j++) {
                int mmj_tmp;
                int b;
                int jj;
                int jp1j;
                int a;
                mmj_tmp = b_n - j;
                b = j * (LDA + 1);
                jj = j * (ldap1 + 1);
                jp1j = b + 2;
                if (mmj_tmp < 1) {
                    a = -1;
                } else {
                    a = 0;
                    if (mmj_tmp > 1) {
                        int ix;
                        double smax;
                        ix = b;
                        smax = std::abs(b_A[jj]);
                        for (int e_k = 2; e_k <= mmj_tmp; e_k++) {
                            double s;
                            ix++;
                            s = std::abs(b_A[ix]);
                            if (s > smax) {
                                a = e_k - 1;
                                smax = s;
                            }
                        }
                    }
                }

                if (b_A[jj + a] != 0.0) {
                    int i11;
                    if (a != 0) {
                        int ipiv_tmp;
                        int j_loop_ub;
                        int l_loop_ub;
                        ipiv_tmp = j + a;
                        ipiv[j] = ipiv_tmp + 1;
                        iy = ipiv_tmp;
                        b_ix = j;
                        x.set_size(b_A.size(0), b_A.size(1));
                        j_loop_ub = b_A.size(1);
                        for (int i14 = 0; i14 < j_loop_ub; i14++) {
                            int k_loop_ub;
                            k_loop_ub = b_A.size(0);
                            for (int i17 = 0; i17 < k_loop_ub; i17++) {
                                x[i17 + x.size(0) * i14] = b_A[i17 + b_A.size(0) * i14];
                            }
                        }

                        for (int f_k = 0; f_k < b_n; f_k++) {
                            double b_temp;
                            b_temp = x[b_ix];
                            x[b_ix] = x[iy];
                            x[iy] = b_temp;
                            b_ix += LDA;
                            iy += LDA;
                        }

                        b_A.set_size(x.size(0), x.size(1));
                        l_loop_ub = x.size(1);
                        for (int i19 = 0; i19 < l_loop_ub; i19++) {
                            int m_loop_ub;
                            m_loop_ub = x.size(0);
                            for (int i21 = 0; i21 < m_loop_ub; i21++) {
                                b_A[i21 + b_A.size(0) * i19] = x[i21 + x.size(0) * i19];
                            }
                        }
                    }

                    i11 = jj + mmj_tmp;
                    for (int c_i = jp1j; c_i <= i11; c_i++) {
                        b_A[c_i - 1] = b_A[c_i - 1] / b_A[jj];
                    }
                }

                jy = b + LDA;
                jA = jj + ldap1;
                for (int b_j = 0; b_j <= mmj_tmp - 2; b_j++) {
                    double yjy;
                    yjy = b_A[jy];
                    if (b_A[jy] != 0.0) {
                        int c_ix;
                        int i15;
                        int i16;
                        c_ix = jj + 1;
                        i15 = jA + 2;
                        i16 = mmj_tmp + jA;
                        for (int ijA = i15; ijA <= i16; ijA++) {
                            b_A[ijA - 1] = b_A[ijA - 1] + b_A[c_ix] * -yjy;
                            c_ix++;
                        }
                    }

                    jy += LDA;
                    jA += LDA;
                }
            }

            b_B.set_size(B.size(0));
            f_loop_ub = B.size(0);
            for (int i7 = 0; i7 < f_loop_ub; i7++) {
                b_B[i7] = B[i7];
            }

            b_LDA = b_A.size(0);
            for (int b_i = 0; b_i <= b_n - 2; b_i++) {
                int i9;
                i9 = ipiv[b_i];
                if (i9 != b_i + 1) {
                    double temp;
                    temp = b_B[b_i];
                    b_B[b_i] = b_B[i9 - 1];
                    b_B[i9 - 1] = temp;
                }
            }

            for (int c_k = 0; c_k < b_n; c_k++) {
                int kAcol;
                kAcol = b_LDA * c_k;
                if (b_B[c_k] != 0.0) {
                    int i12;
                    i12 = c_k + 2;
                    for (int d_i = i12; d_i <= b_n; d_i++) {
                        b_B[d_i - 1] = b_B[d_i - 1] - b_B[c_k] * b_A[(d_i + kAcol) - 1];
                    }
                }
            }

            for (int d_k = b_n; d_k >= 1; d_k--) {
                int b_kAcol;
                double d;
                b_kAcol = b_LDA * (d_k - 1);
                d = b_B[d_k - 1];
                if (d != 0.0) {
                    b_B[d_k - 1] = d / b_A[(d_k + b_kAcol) - 1];
                    for (int e_i = 0; e_i <= d_k - 2; e_i++) {
                        b_B[e_i] = b_B[e_i] - b_B[d_k - 1] * b_A[e_i + b_kAcol];
                    }
                }
            }

            Y.set_size(b_B.size(0));
            i_loop_ub = b_B.size(0);
            for (int i13 = 0; i13 < i_loop_ub; i13++) {
                Y[i13] = b_B[i13];
            }
        } else {
            int n;
            int b_u0;
            int b_u1;
            int minmana;
            int loop_ub;
            int c_loop_ub;
            int rankR;
            int minmn;
            int maxmn;
            double tol;
            int g_loop_ub;
            int h_loop_ub;
            int m;
            int e_u0;
            int c_u1;
            int mn;
            n = A.size(1);
            b_u0 = A.size(0);
            b_u1 = A.size(1);
            if (b_u0 < b_u1) {
                minmana = b_u0;
            } else {
                minmana = b_u1;
            }

            jpvt.set_size(1, A.size(1));
            loop_ub = A.size(1);
            for (int i = 0; i < loop_ub; i++) {
                jpvt[i] = 0;
            }

            for (int k = 0; k < n; k++) {
                jpvt[k] = k + 1;
            }

            b_A.set_size(A.size(0), A.size(1));
            c_loop_ub = A.size(1);
            for (int i2 = 0; i2 < c_loop_ub; i2++) {
                int e_loop_ub;
                e_loop_ub = A.size(0);
                for (int i5 = 0; i5 < e_loop_ub; i5++) {
                    b_A[i5 + b_A.size(0) * i2] = A[i5 + A.size(0) * i2];
                }
            }

            tau.set_size(minmana);
            for (int i4 = 0; i4 < minmana; i4++) {
                tau[i4] = 0.0;
            }

            qrpf(b_A, A.size(0), A.size(1), tau, jpvt);
            rankR = 0;
            if (b_A.size(0) < b_A.size(1)) {
                minmn = b_A.size(0);
                maxmn = b_A.size(1);
            } else {
                minmn = b_A.size(1);
                maxmn = b_A.size(0);
            }

            tol = std::fmin(1.4901161193847656E-8, 2.2204460492503131E-15 * static_cast<double>
                            (maxmn)) * std::abs(b_A[0]);
            while ((rankR < minmn) && (std::abs(b_A[rankR + b_A.size(0) * rankR]) > tol)) {
                rankR++;
            }

            b_B.set_size(B.size(0));
            g_loop_ub = B.size(0);
            for (int i8 = 0; i8 < g_loop_ub; i8++) {
                b_B[i8] = B[i8];
            }

            Y.set_size(b_A.size(1));
            h_loop_ub = b_A.size(1);
            for (int i10 = 0; i10 < h_loop_ub; i10++) {
                Y[i10] = 0.0;
            }

            m = b_A.size(0);
            e_u0 = b_A.size(0);
            c_u1 = b_A.size(1);
            if (e_u0 < c_u1) {
                mn = e_u0;
            } else {
                mn = c_u1;
            }

            for (int c_j = 0; c_j < mn; c_j++) {
                if (tau[c_j] != 0.0) {
                    int i18;
                    wj = b_B[c_j];
                    i18 = c_j + 2;
                    for (int g_i = i18; g_i <= m; g_i++) {
                        wj += b_A[(g_i + b_A.size(0) * c_j) - 1] * b_B[g_i - 1];
                    }

                    wj *= tau[c_j];
                    if (wj != 0.0) {
                        int i22;
                        int scalarLB;
                        int vectorUB;
                        b_B[c_j] = b_B[c_j] - wj;
                        i22 = c_j + 2;
                        scalarLB = ((((m - c_j) - 1) & -4) + c_j) + 2;
                        vectorUB = scalarLB - 4;
                        for (i_i = i22; i_i <= vectorUB; i_i += 4) {
                            __m256d r;
                            __m256d r1;
                            r = _mm256_loadu_pd(&b_A[(i_i + b_A.size(0) * c_j) - 1]);
                            r1 = _mm256_loadu_pd(&b_B[i_i - 1]);
                            _mm256_storeu_pd(&b_B[i_i - 1], _mm256_sub_pd(r1, _mm256_mul_pd(r,
                                               _mm256_set1_pd(wj))));
                        }

                        for (i_i = scalarLB; i_i <= m; i_i++) {
                            b_B[i_i - 1] = b_B[i_i - 1] - b_A[(i_i + b_A.size(0) * c_j) - 1] * wj;
                        }
                    }
                }
            }

            for (int f_i = 0; f_i < rankR; f_i++) {
                Y[jpvt[f_i] - 1] = b_B[f_i];
            }

            for (int d_j = rankR; d_j >= 1; d_j--) {
                int i20;
                i20 = jpvt[d_j - 1];
                Y[i20 - 1] = Y[i20 - 1] / b_A[(d_j + b_A.size(0) * (d_j - 1)) - 1];
                for (int h_i = 0; h_i <= d_j - 2; h_i++) {
                    Y[jpvt[h_i] - 1] = Y[jpvt[h_i] - 1] - Y[jpvt[d_j - 1] - 1] * b_A[h_i + b_A.size
                        (0) * (d_j - 1)];
                }
            }
        }
    }

    //
    // Arguments    : const double A[3]
    //                const coder::array<double, 2U> &B
    //                coder::array<double, 2U> &C
    // Return Type  : void
    //
    static void mtimes(const double A[3], const coder::array<double, 2U> &B, coder::array<double, 2U>
                       &C)
    {
        int n;
        n = B.size(1);
        C.set_size(1, B.size(1));
        for (int j = 0; j < n; j++) {
            C[j] = (A[0] * B[3 * j] + A[1] * B[3 * j + 1]) + A[2] * B[3 * j + 2];
        }
    }

    //
    // Arguments    : const coder::array<double, 2U> &a
    //                coder::array<double, 2U> &y
    // Return Type  : void
    //
    static void power(const coder::array<double, 2U> &a, coder::array<double, 2U> &y)
    {
        coder::array<double, 2U> z1;
        int loop_ub;
        int N;
        int b_loop_ub;
        y.set_size(3, a.size(1));
        z1.set_size(3, a.size(1));
        loop_ub = a.size(1);
        for (int i = 0; i < loop_ub; i++) {
            z1[3 * i] = y[3 * i];
            z1[3 * i + 1] = y[3 * i + 1];
            z1[3 * i + 2] = y[3 * i + 2];
        }

        N = a.size(1);
        for (int k = 0; k < N; k++) {
            z1[3 * k] = std::pow(a[3 * k], 2.0);
            z1[3 * k + 1] = std::pow(a[3 * k + 1], 2.0);
            z1[3 * k + 2] = std::pow(a[3 * k + 2], 2.0);
        }

        y.set_size(3, z1.size(1));
        b_loop_ub = z1.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            y[3 * i1] = z1[3 * i1];
            y[3 * i1 + 1] = z1[3 * i1 + 1];
            y[3 * i1 + 2] = z1[3 * i1 + 2];
        }
    }

    //
    // Arguments    : coder::array<double, 2U> &A
    //                int m
    //                int n
    //                coder::array<double, 1U> &tau
    //                coder::array<int, 2U> &jpvt
    // Return Type  : void
    //
    static void qrpf(coder::array<double, 2U> &A, int m, int n, coder::array<double, 1U> &tau, coder::
                     array<int, 2U> &jpvt)
    {
        int ma;
        int minmn;
        int A_idx_0;
        coder::array<double, 1U> work;
        coder::array<double, 1U> vn1;
        coder::array<double, 1U> vn2;
        double atmp;
        coder::array<double, 2U> x;
        double beta1;
        int jA;
        int iac;
        double c;
        ma = A.size(0);
        if (m < n) {
            minmn = m;
        } else {
            minmn = n;
        }

        A_idx_0 = A.size(1);
        work.set_size(A_idx_0);
        for (int i = 0; i < A_idx_0; i++) {
            work[i] = 0.0;
        }

        A_idx_0 = A.size(1);
        vn1.set_size(A_idx_0);
        for (int i1 = 0; i1 < A_idx_0; i1++) {
            vn1[i1] = 0.0;
        }

        A_idx_0 = A.size(1);
        vn2.set_size(A_idx_0);
        for (int i2 = 0; i2 < A_idx_0; i2++) {
            vn2[i2] = 0.0;
        }

        for (int j = 0; j < n; j++) {
            double d;
            d = xnrm2(m, A, j * ma + 1);
            vn1[j] = d;
            vn2[j] = d;
        }

        for (int b_i = 0; b_i < minmn; b_i++) {
            int ip1;
            int ii_tmp;
            int ii;
            int nmi;
            int mmi;
            int idxmax;
            int pvt;
            ip1 = b_i + 2;
            ii_tmp = b_i * ma;
            ii = ii_tmp + b_i;
            nmi = n - b_i;
            mmi = m - b_i;
            if (nmi < 1) {
                idxmax = -1;
            } else {
                idxmax = 0;
                if (nmi > 1) {
                    int ix;
                    double smax;
                    ix = b_i;
                    smax = std::abs(vn1[b_i]);
                    for (int k = 2; k <= nmi; k++) {
                        double s;
                        ix++;
                        s = std::abs(vn1[ix]);
                        if (s > smax) {
                            idxmax = k - 1;
                            smax = s;
                        }
                    }
                }
            }

            pvt = b_i + idxmax;
            if (pvt + 1 != b_i + 1) {
                int b_ix;
                int iy;
                int loop_ub;
                int c_loop_ub;
                b_ix = pvt * ma;
                iy = ii_tmp;
                x.set_size(A.size(0), A.size(1));
                loop_ub = A.size(1);
                for (int i3 = 0; i3 < loop_ub; i3++) {
                    int b_loop_ub;
                    b_loop_ub = A.size(0);
                    for (int i4 = 0; i4 < b_loop_ub; i4++) {
                        x[i4 + x.size(0) * i3] = A[i4 + A.size(0) * i3];
                    }
                }

                for (int b_k = 0; b_k < m; b_k++) {
                    double temp;
                    temp = x[b_ix];
                    x[b_ix] = x[iy];
                    x[iy] = temp;
                    b_ix++;
                    iy++;
                }

                A.set_size(x.size(0), x.size(1));
                c_loop_ub = x.size(1);
                for (int i5 = 0; i5 < c_loop_ub; i5++) {
                    int d_loop_ub;
                    d_loop_ub = x.size(0);
                    for (int i7 = 0; i7 < d_loop_ub; i7++) {
                        A[i7 + A.size(0) * i5] = x[i7 + x.size(0) * i5];
                    }
                }

                int itemp;
                itemp = jpvt[pvt];
                jpvt[pvt] = jpvt[b_i];
                jpvt[b_i] = itemp;
                vn1[pvt] = vn1[b_i];
                vn2[pvt] = vn2[b_i];
            }

            if (b_i + 1 < m) {
                int ix0;
                atmp = A[ii];
                ix0 = ii + 2;
                tau[b_i] = 0.0;
                if (mmi > 0) {
                    double xnorm;
                    xnorm = xnrm2(mmi - 1, A, ii + 2);
                    if (xnorm != 0.0) {
                        beta1 = rt_hypotd(A[ii], xnorm);
                        if (A[ii] >= 0.0) {
                            beta1 = -beta1;
                        }

                        if (std::abs(beta1) < 1.0020841800044864E-292) {
                            int knt;
                            int i6;
                            double b_a;
                            knt = -1;
                            i6 = ii + mmi;
                            do {
                                knt++;
                                for (int d_k = ix0; d_k <= i6; d_k++) {
                                    A[d_k - 1] = 9.9792015476736E+291 * A[d_k - 1];
                                }

                                beta1 *= 9.9792015476736E+291;
                                atmp *= 9.9792015476736E+291;
                            } while (!(std::abs(beta1) >= 1.0020841800044864E-292));

                            beta1 = rt_hypotd(atmp, xnrm2(mmi - 1, A, ii + 2));
                            if (atmp >= 0.0) {
                                beta1 = -beta1;
                            }

                            tau[b_i] = (beta1 - atmp) / beta1;
                            b_a = 1.0 / (atmp - beta1);
                            for (int e_k = ix0; e_k <= i6; e_k++) {
                                A[e_k - 1] = b_a * A[e_k - 1];
                            }

                            for (int f_k = 0; f_k <= knt; f_k++) {
                                beta1 *= 1.0020841800044864E-292;
                            }

                            atmp = beta1;
                        } else {
                            double a;
                            int i8;
                            tau[b_i] = (beta1 - A[ii]) / beta1;
                            a = 1.0 / (A[ii] - beta1);
                            i8 = ii + mmi;
                            for (int c_k = ix0; c_k <= i8; c_k++) {
                                A[c_k - 1] = a * A[c_k - 1];
                            }

                            atmp = beta1;
                        }
                    }
                }

                A[ii] = atmp;
            } else {
                tau[b_i] = 0.0;
            }

            if (b_i + 1 < n) {
                double b_atmp;
                int ic0;
                int lastv;
                int lastc;
                b_atmp = A[ii];
                A[ii] = 1.0;
                ic0 = (ii + ma) + 1;
                if (tau[b_i] != 0.0) {
                    int c_i;
                    int b_lastc;
                    bool exitg2;
                    lastv = mmi - 1;
                    c_i = (ii + mmi) - 1;
                    while ((lastv + 1 > 0) && (A[c_i] == 0.0)) {
                        lastv--;
                        c_i--;
                    }

                    b_lastc = nmi - 2;
                    exitg2 = false;
                    while ((!exitg2) && (b_lastc + 1 > 0)) {
                        int coltop;
                        int ia;
                        int exitg1;
                        coltop = ic0 + b_lastc * ma;
                        ia = coltop;
                        do {
                            exitg1 = 0;
                            if (ia <= coltop + lastv) {
                                if (A[ia - 1] != 0.0) {
                                    exitg1 = 1;
                                } else {
                                    ia++;
                                }
                            } else {
                                b_lastc--;
                                exitg1 = 2;
                            }
                        } while (exitg1 == 0);

                        if (exitg1 == 1) {
                            exitg2 = true;
                        }
                    }

                    lastc = b_lastc;
                } else {
                    lastv = -1;
                    lastc = -1;
                }

                if (lastv + 1 > 0) {
                    if (lastc + 1 != 0) {
                        int c_iy;
                        int i9;
                        for (int b_iy = 0; b_iy <= lastc; b_iy++) {
                            work[b_iy] = 0.0;
                        }

                        c_iy = 0;
                        i9 = ic0 + ma * lastc;
                        for (iac = ic0; ma < 0 ? iac >= i9 : iac <= i9; iac += ma) {
                            int c_ix;
                            int i10;
                            c_ix = ii;
                            c = 0.0;
                            i10 = iac + lastv;
                            for (int b_ia = iac; b_ia <= i10; b_ia++) {
                                c += A[b_ia - 1] * A[c_ix];
                                c_ix++;
                            }

                            work[c_iy] = work[c_iy] + c;
                            c_iy++;
                        }
                    }

                    if (-tau[b_i] != 0.0) {
                        int jy;
                        jA = ic0;
                        jy = 0;
                        for (int c_j = 0; c_j <= lastc; c_j++) {
                            if (work[jy] != 0.0) {
                                double b_temp;
                                int d_ix;
                                int i11;
                                b_temp = work[jy] * -tau[b_i];
                                d_ix = ii;
                                i11 = lastv + jA;
                                for (int ijA = jA; ijA <= i11; ijA++) {
                                    A[ijA - 1] = A[ijA - 1] + A[d_ix] * b_temp;
                                    d_ix++;
                                }
                            }

                            jy++;
                            jA += ma;
                        }
                    }
                }

                A[ii] = b_atmp;
            }

            for (int b_j = ip1; b_j <= n; b_j++) {
                int ij;
                double d1;
                ij = b_i + (b_j - 1) * ma;
                d1 = vn1[b_j - 1];
                if (d1 != 0.0) {
                    double temp1;
                    double temp2;
                    temp1 = std::abs(A[ij]) / d1;
                    temp1 = 1.0 - temp1 * temp1;
                    if (temp1 < 0.0) {
                        temp1 = 0.0;
                    }

                    temp2 = d1 / vn2[b_j - 1];
                    temp2 = temp1 * (temp2 * temp2);
                    if (temp2 <= 1.4901161193847656E-8) {
                        if (b_i + 1 < m) {
                            double d2;
                            d2 = xnrm2(mmi - 1, A, ij + 2);
                            vn1[b_j - 1] = d2;
                            vn2[b_j - 1] = d2;
                        } else {
                            vn1[b_j - 1] = 0.0;
                            vn2[b_j - 1] = 0.0;
                        }
                    } else {
                        vn1[b_j - 1] = d1 * std::sqrt(temp1);
                    }
                }
            }
        }
    }

    //
    // Arguments    : double u0
    //                double u1
    // Return Type  : double
    //
    static double rt_hypotd(double u0, double u1)
    {
        double y;
        double a;
        double b;
        a = std::abs(u0);
        b = std::abs(u1);
        if (a < b) {
            a /= b;
            y = b * std::sqrt(a * a + 1.0);
        } else if (a > b) {
            b /= a;
            y = a * std::sqrt(b * b + 1.0);
        } else {
            y = a * 1.4142135623730951;
        }

        return y;
    }

    //
    // Arguments    : double u0
    //                double u1
    // Return Type  : double
    //
    static double rt_remd(double u0, double u1)
    {
        double y;
        if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
            double q;
            q = std::abs(u0 / u1);
            if (std::abs(q - std::floor(q + 0.5)) <= DBL_EPSILON * q) {
                y = 0.0;
            } else {
                y = std::fmod(u0, u1);
            }
        } else {
            y = std::fmod(u0, u1);
        }

        return y;
    }

    //
    // Arguments    : const coder::array<double, 2U> &x
    //                coder::array<double, 2U> &y
    // Return Type  : void
    //
    static void sum(const coder::array<double, 2U> &x, coder::array<double, 2U> &y)
    {
        if (x.size(1) == 0) {
            y.set_size(1, 0);
        } else {
            int i;
            y.set_size(1, x.size(1));
            i = x.size(1);
            for (int k = 0; k < i; k++) {
                y[k] = x[3 * k];
                y[k] = y[k] + x[3 * k + 1];
                y[k] = y[k] + x[3 * k + 2];
            }
        }
    }

    //
    // Arguments    : int n
    //                const coder::array<double, 2U> &x
    //                int ix0
    // Return Type  : double
    //
    static double xnrm2(int n, const coder::array<double, 2U> &x, int ix0)
    {
        double y;
        y = 0.0;
        if (n >= 1) {
            if (n == 1) {
                y = std::abs(x[ix0 - 1]);
            } else {
                double scale;
                int kend;
                scale = 3.3121686421112381E-170;
                kend = (ix0 + n) - 1;
                for (int k = ix0; k <= kend; k++) {
                    double absxk;
                    absxk = std::abs(x[k - 1]);
                    if (absxk > scale) {
                        double t;
                        t = scale / absxk;
                        y = y * t * t + 1.0;
                        scale = absxk;
                    } else {
                        double t;
                        t = absxk / scale;
                        y += t * t;
                    }
                }

                y = scale * std::sqrt(y);
            }
        }

        return y;
    }

    //
    // Arguments    : const FeedoptContext *ctx
    //                const CurvStruct *CurvStruct1
    //                const CurvStruct *CurvStruct2
    //                CurvStruct *CurvStruct1_C
    //                CurvStruct *CurvStruct_T
    //                CurvStruct *CurvStruct2_C
    //                TransitionResult *status
    // Return Type  : void
    //
    void CalcTransition(const FeedoptContext *ctx, const CurvStruct *CurvStruct1, const CurvStruct
                        *CurvStruct2, CurvStruct *CurvStruct1_C, CurvStruct *CurvStruct_T,
                        CurvStruct *CurvStruct2_C, TransitionResult *status)
    {
        double CutOff;
        double Length_Threshold;
        unsigned long u;
        unsigned long u1;
        double unusedU0[3];
        double r0D1_1[3];
        double unusedU1[3];
        double r1D1_1[3];
        TransitionResult b_status;
        CurvStruct expl_temp;
        coder::array<double, 2U> Spline_sp_knots;
        double r0D0[3];
        double r0D1[3];
        double r0D2[3];
        double r1D0[3];
        double r1D1[3];
        double r1D2[3];
        coder::array<bool, 2U> b_x;
        double p5[6][3];
        int c_status;
        double alpha0;
        double alpha1;
        int ii_data[1];
        int Spline_sp_knots_size[2];
        double Spline_sp_knots_data[1];
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        CutOff = ctx->cfg.CutOff;
        Length_Threshold = 3.0 * ctx->cfg.CutOff;

        //  1 -> stdout
        //  2 -> stderr
        u = static_cast<unsigned long>(std::round(DebugConfig));
        u1 = u & 8UL;
        if (u1 != 0UL) {
            printf("========== CalcTransition ==========\n");
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u1 != 0UL) {
            printf("CutOff = %.3f\n", ctx->cfg.CutOff);
            fflush(stdout);
            b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct1->Type,
                              CurvStruct1->zspdmode, CurvStruct1->P0, CurvStruct1->P1,
                              CurvStruct1->evec, CurvStruct1->theta, CurvStruct1->pitch,
                              CurvStruct1->CoeffP5, CurvStruct1->sp_index, CurvStruct1->FeedRate,
                              CurvStruct1->UseConstJerk, CurvStruct1->ConstJerk,
                              CurvStruct1->a_param, CurvStruct1->b_param);
            b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct2->Type,
                              CurvStruct2->zspdmode, CurvStruct2->P0, CurvStruct2->P1,
                              CurvStruct2->evec, CurvStruct2->theta, CurvStruct2->pitch,
                              CurvStruct2->CoeffP5, CurvStruct2->sp_index, CurvStruct2->FeedRate,
                              CurvStruct2->UseConstJerk, CurvStruct2->ConstJerk,
                              CurvStruct2->a_param, CurvStruct2->b_param);
        }

        *CurvStruct_T = *CurvStruct1;

        // default value
        e_EvalCurvStruct(&ctx->q_splines, CurvStruct1->Type, CurvStruct1->P0, CurvStruct1->P1,
                         CurvStruct1->evec, CurvStruct1->theta, CurvStruct1->pitch,
                         CurvStruct1->CoeffP5, CurvStruct1->sp_index, CurvStruct1->a_param,
                         CurvStruct1->b_param, unusedU0, r0D1_1);
        f_EvalCurvStruct(&ctx->q_splines, CurvStruct2->Type, CurvStruct2->P0, CurvStruct2->P1,
                         CurvStruct2->evec, CurvStruct2->theta, CurvStruct2->pitch,
                         CurvStruct2->CoeffP5, CurvStruct2->sp_index, CurvStruct2->a_param,
                         CurvStruct2->b_param, unusedU1, r1D1_1);

        //  colinearity test
        if ((CurvStruct1->Type != CurveType_Helix) && (CurvStruct2->Type != CurveType_Helix) &&
                collinear(r0D1_1, r1D1_1, ctx->cfg.CollTolDeg)) {
            //  && norm(r0D2 - r1D2) < 10*eps && collinear(r0D2, r1D2, 1e-2)
            b_status = TransitionResult_Collinear;
            *CurvStruct1_C = *CurvStruct1;
            *CurvStruct2_C = *CurvStruct2;
        } else {
            double L1;
            double L2;
            L1 = LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct1->Type,
                            CurvStruct1->P0, CurvStruct1->P1, CurvStruct1->evec, CurvStruct1->theta,
                            CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                            CurvStruct1->a_param, CurvStruct1->b_param);
            L2 = LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct2->Type,
                            CurvStruct2->P0, CurvStruct2->P1, CurvStruct2->evec, CurvStruct2->theta,
                            CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                            CurvStruct2->a_param, CurvStruct2->b_param);

            //  CutOff calculation
            if ((CurvStruct1->Type != CurveType_Spline) && (CurvStruct2->Type != CurveType_Spline))
            {
                if ((L1 < Length_Threshold) || (L2 < Length_Threshold)) {
                    CutOff = std::fmin(L1, L2) / 3.0;
                }
            } else {
                double x;
                double y;
                int ii_size_idx_1;
                bool exitg1;
                if (CurvStruct1->Type == CurveType_Spline) {
                    int loop_ub;
                    double u1_tilda;
                    int c_loop_ub;
                    int k;
                    int ii;
                    int idx;
                    ctx->q_splines.get(CurvStruct1->sp_index, (&expl_temp));
                    Spline_sp_knots.set_size(1, expl_temp.sp.knots.size(1));
                    loop_ub = expl_temp.sp.knots.size(1);
                    for (int i = 0; i < loop_ub; i++) {
                        Spline_sp_knots[i] = expl_temp.sp.knots[i];
                    }

                    //  In a very general case we may cut a spline several times
                    //  at the end;
                    //  If a spline had already been cut at the end,
                    //  we must compute the corresponding
                    //  native spline parameter (u1_tilda) value
                    //  This value will be different from 1 in this special case
                    u1_tilda = CurvStruct1->a_param + CurvStruct1->b_param;

                    //  We need to find the previous spline knot u0_tilda...
                    b_x.set_size(1, Spline_sp_knots.size(1));
                    c_loop_ub = Spline_sp_knots.size(1);
                    for (int i2 = 0; i2 < c_loop_ub; i2++) {
                        b_x[i2] = (Spline_sp_knots[i2] < u1_tilda);
                    }

                    k = (1 <= b_x.size(1));
                    ii = b_x.size(1);
                    idx = 0;
                    ii_size_idx_1 = k;
                    exitg1 = false;
                    while ((!exitg1) && (ii > 0)) {
                        if (b_x[ii - 1]) {
                            idx = 1;
                            ii_data[0] = ii;
                            exitg1 = true;
                        } else {
                            ii--;
                        }
                    }

                    if (k == 1) {
                        if (idx == 0) {
                            ii_size_idx_1 = 0;
                        }
                    } else {
                        ii_size_idx_1 = (1 <= idx);
                    }

                    Spline_sp_knots_size[0] = 1;
                    Spline_sp_knots_size[1] = ii_size_idx_1;
                    if (0 <= ii_size_idx_1 - 1) {
                        Spline_sp_knots_data[0] = Spline_sp_knots[ii_data[0] - 1];
                    }

                    x = b_SplineLengthApprox(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                        CurvStruct1->sp_index, Spline_sp_knots_data, Spline_sp_knots_size, u1_tilda)
                        / 2.0;
                } else if (L1 < Length_Threshold) {
                    x = L1 / 3.0;
                } else {
                    x = ctx->cfg.CutOff;
                }

                if (CurvStruct2->Type == CurveType_Spline) {
                    int b_loop_ub;
                    int d_loop_ub;
                    int b_k;
                    int b_idx;
                    int b_ii;
                    ctx->q_splines.get(CurvStruct2->sp_index, (&expl_temp));
                    Spline_sp_knots.set_size(1, expl_temp.sp.knots.size(1));
                    b_loop_ub = expl_temp.sp.knots.size(1);
                    for (int i1 = 0; i1 < b_loop_ub; i1++) {
                        Spline_sp_knots[i1] = expl_temp.sp.knots[i1];
                    }

                    //  In a very general case we may cut a spline several times
                    //  at the beginning;
                    //  If a spline had already been cut at the beginning,
                    //  we must compute the corresponding
                    //  native spline parameter (u0_tilda) value
                    //  This value will be different from 0 in this special case
                    //  We need to find the next spline knot u1_tilda...
                    b_x.set_size(1, Spline_sp_knots.size(1));
                    d_loop_ub = Spline_sp_knots.size(1);
                    for (int i3 = 0; i3 < d_loop_ub; i3++) {
                        b_x[i3] = (Spline_sp_knots[i3] > CurvStruct2->b_param);
                    }

                    b_k = (1 <= b_x.size(1));
                    b_idx = 0;
                    ii_size_idx_1 = b_k;
                    b_ii = 0;
                    exitg1 = false;
                    while ((!exitg1) && (b_ii <= b_x.size(1) - 1)) {
                        if (b_x[b_ii]) {
                            b_idx = 1;
                            ii_data[0] = b_ii + 1;
                            exitg1 = true;
                        } else {
                            b_ii++;
                        }
                    }

                    if (b_k == 1) {
                        if (b_idx == 0) {
                            ii_size_idx_1 = 0;
                        }
                    } else {
                        ii_size_idx_1 = (1 <= b_idx);
                    }

                    Spline_sp_knots_size[0] = 1;
                    Spline_sp_knots_size[1] = ii_size_idx_1;
                    if (0 <= ii_size_idx_1 - 1) {
                        Spline_sp_knots_data[0] = Spline_sp_knots[ii_data[0] - 1];
                    }

                    y = c_SplineLengthApprox(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                        CurvStruct2->sp_index, CurvStruct2->b_param, Spline_sp_knots_data,
                        Spline_sp_knots_size) / 2.0;
                } else if (L2 < Length_Threshold) {
                    y = L2 / 3.0;
                } else {
                    y = ctx->cfg.CutOff;
                }

                CutOff = std::fmin(x, y);
            }

            *CurvStruct1_C = *CurvStruct1;
            CutCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct1_C, CutOff);
            *CurvStruct2_C = *CurvStruct2;
            b_CutCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct2_C, CutOff);

            //  1 -> stdout
            //  2 -> stderr
            if (u1 != 0UL) {
                printf("========== AFTER CUTTING \n");
                fflush(stdout);
                b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct1_C->Type,
                                  CurvStruct1_C->zspdmode, CurvStruct1_C->P0, CurvStruct1_C->P1,
                                  CurvStruct1_C->evec, CurvStruct1_C->theta, CurvStruct1_C->pitch,
                                  CurvStruct1_C->CoeffP5, CurvStruct1_C->sp_index,
                                  CurvStruct1_C->FeedRate, CurvStruct1_C->UseConstJerk,
                                  CurvStruct1_C->ConstJerk, CurvStruct1_C->a_param,
                                  CurvStruct1_C->b_param);
                b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct2_C->Type,
                                  CurvStruct2_C->zspdmode, CurvStruct2_C->P0, CurvStruct2_C->P1,
                                  CurvStruct2_C->evec, CurvStruct2_C->theta, CurvStruct2_C->pitch,
                                  CurvStruct2_C->CoeffP5, CurvStruct2_C->sp_index,
                                  CurvStruct2_C->FeedRate, CurvStruct2_C->UseConstJerk,
                                  CurvStruct2_C->ConstJerk, CurvStruct2_C->a_param,
                                  CurvStruct2_C->b_param);
            }

            d_EvalCurvStruct(&ctx->q_splines, CurvStruct1_C->Type, CurvStruct1_C->P0,
                             CurvStruct1_C->P1, CurvStruct1_C->evec, CurvStruct1_C->theta,
                             CurvStruct1_C->pitch, CurvStruct1_C->CoeffP5, CurvStruct1_C->sp_index,
                             CurvStruct1_C->a_param, CurvStruct1_C->b_param, r0D0, r0D1, r0D2);
            g_EvalCurvStruct(&ctx->q_splines, CurvStruct2_C->Type, CurvStruct2_C->P0,
                             CurvStruct2_C->P1, CurvStruct2_C->evec, CurvStruct2_C->theta,
                             CurvStruct2_C->pitch, CurvStruct2_C->CoeffP5, CurvStruct2_C->sp_index,
                             CurvStruct2_C->a_param, CurvStruct2_C->b_param, r1D0, r1D1, r1D2);

            //  G2 transition calculation
            G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2, p5, &c_status, &alpha0,
                &alpha1);
            if (c_status == 1) {
                //  standard case
                //  transition CurvStruct calculation
                ConstrTransP5Struct(p5, CurvStruct1->FeedRate, CurvStruct_T);
                b_status = TransitionResult_Ok;
            } else if (c_status == 6) {
                unsigned long u3;

                //  TODO: decide in the future...
                //  Now we ignore and construct the transition curve anyway
                ConstrTransP5Struct(p5, CurvStruct1->FeedRate, CurvStruct_T);
                b_status = TransitionResult_Ok;

                //  1 -> stdout
                //  2 -> stderr
                u3 = static_cast<unsigned long>(std::round(DebugConfig)) & 1UL;
                if (u3 != 0UL) {
                    printf("========== CalcTransition ==========\n");
                    fflush(stdout);
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u3 != 0UL) {
                    printf("=========== status = 6 ==========\n");
                    fflush(stdout);
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u3 != 0UL) {
                    printf("Lines: %d, %d\n\n", CurvStruct1->gcode_source_line,
                           CurvStruct2->gcode_source_line);
                    fflush(stdout);
                }
            } else {
                unsigned long u2;
                b_status = TransitionResult_NoSolution;

                //  1 -> stdout
                //  2 -> stderr
                u2 = u & 1UL;
                if (u2 != 0UL) {
                    printf("========== CalcTransition ==========\n");
                    fflush(stdout);
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u2 != 0UL) {
                    printf("=========== No Solution ==========\n");
                    fflush(stdout);
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u2 != 0UL) {
                    printf("Lines: %d, %d\n\n", CurvStruct1->gcode_source_line,
                           CurvStruct2->gcode_source_line);
                    fflush(stdout);
                }
            }

            CurvStruct1_C->gcode_source_line = CurvStruct1->gcode_source_line;
            CurvStruct_T->gcode_source_line = CurvStruct2->gcode_source_line;
            CurvStruct2_C->gcode_source_line = CurvStruct2->gcode_source_line;
        }

        *status = b_status;
    }

    //
    // Arguments    : FeedoptConfig *cfg
    //                const char filename_data[]
    //                const int filename_size[2]
    // Return Type  : void
    //
    void ConfigSetSource(FeedoptConfig *cfg, const char filename_data[], const int filename_size[2])
    {
        int loop_ub;
        int i;
        int i1;
        int b_loop_ub;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        if (1 > filename_size[1]) {
            loop_ub = 0;
        } else {
            loop_ub = filename_size[1];
        }

        if (0 <= loop_ub - 1) {
            std::memcpy(&cfg->source[0], &filename_data[0], loop_ub * sizeof(char));
        }

        if (filename_size[1] + 1 > 1024) {
            i = 0;
            i1 = -1;
        } else {
            i = filename_size[1];
            i1 = 1023;
        }

        b_loop_ub = (i1 - i) + 1;
        if (0 <= b_loop_ub - 1) {
            std::memset(&cfg->source[i], 0, ((b_loop_ub + i) - i) * sizeof(char));
        }
    }

    //
    // Arguments    : CurvStruct *C
    // Return Type  : void
    //
    void ConstrCurvStructType(CurvStruct *C)
    {
        double dv[3];
        double dv1[3];
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        dv[0] = 0.0;
        dv1[0] = 0.0;
        dv[1] = 0.0;
        dv1[1] = 0.0;
        dv[2] = 0.0;
        dv1[2] = 0.0;
        ConstrLineStruct(dv, dv1, 0.2, ZSpdMode_NN, C);
    }

    //
    // Arguments    : const double P0[3]
    //                const double P1[3]
    //                const double evec[3]
    //                double theta
    //                double pitch
    //                double FeedRate
    //                ZSpdMode b_ZSpdMode
    //                CurvStruct *b_CurvStruct
    // Return Type  : void
    //
    void ConstrHelixStruct(const double P0[3], const double P1[3], const double evec[3], double
                           theta, double pitch, double FeedRate, ZSpdMode b_ZSpdMode, CurvStruct
                           *b_CurvStruct)
    {
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        //
        //
        //  ctxType = coder.OutputType('InitFeedoptPlan');
        b_CurvStruct->Type = CurveType_Helix;
        b_CurvStruct->zspdmode = b_ZSpdMode;
        b_CurvStruct->P0[0] = P0[0];
        b_CurvStruct->P1[0] = P1[0];
        b_CurvStruct->evec[0] = evec[0];
        b_CurvStruct->P0[1] = P0[1];
        b_CurvStruct->P1[1] = P1[1];
        b_CurvStruct->evec[1] = evec[1];
        b_CurvStruct->P0[2] = P0[2];
        b_CurvStruct->P1[2] = P1[2];
        b_CurvStruct->evec[2] = evec[2];
        b_CurvStruct->theta = theta;
        b_CurvStruct->pitch = pitch;
        for (int i = 0; i < 6; i++) {
            b_CurvStruct->CoeffP5[i][0] = 0.0;
            b_CurvStruct->CoeffP5[i][1] = 0.0;
            b_CurvStruct->CoeffP5[i][2] = 0.0;
        }

        b_CurvStruct->sp_index = 1;
        b_CurvStruct->FeedRate = FeedRate;
        b_CurvStruct->MaxConstantFeedRate = 0.0;
        b_CurvStruct->i_begin_sp = 0;
        b_CurvStruct->i_end_sp = 0;
        b_CurvStruct->gcode_source_line = 0;
        b_CurvStruct->index_smooth = 0;
        b_CurvStruct->UseConstJerk = false;
        b_CurvStruct->ConstJerk = 0.0;
        b_CurvStruct->ConstJerkMaxIterations = 0;
        b_CurvStruct->Coeff.set_size(0);
        b_CurvStruct->a_param = 1.0;
        b_CurvStruct->b_param = 0.0;
        b_CurvStruct->sp.CoeffX.set_size(1, 1);
        b_CurvStruct->sp.CoeffX[0] = 0.0;
        b_CurvStruct->sp.CoeffY.set_size(1, 1);
        b_CurvStruct->sp.CoeffY[0] = 0.0;
        b_CurvStruct->sp.CoeffZ.set_size(1, 1);
        b_CurvStruct->sp.CoeffZ[0] = 0.0;
        b_CurvStruct->sp.Bl.ncoeff = 0;
        b_CurvStruct->sp.Bl.breakpoints.set_size(1, 0);
        b_CurvStruct->sp.Bl.handle = 0UL;
        b_CurvStruct->sp.Bl.degree = 0;
        b_CurvStruct->sp.knots.set_size(1, 1);
        b_CurvStruct->sp.knots[0] = 0.0;
    }

    //
    // Arguments    : double p0x
    //                double p0y
    //                double p0z
    //                double p1x
    //                double p1y
    //                double p1z
    //                double cx
    //                double cy
    //                double cz
    //                double rotation
    //                const double evec[3]
    //                CurvStruct *b_CurvStruct
    // Return Type  : void
    //
    void ConstrHelixStructFromArcFeed(double p0x, double p0y, double p0z, double p1x, double p1y,
        double p1z, double cx, double cy, double cz, double rotation, const double evec[3],
        CurvStruct *b_CurvStruct)
    {
        double P0[3];
        double P1[3];
        double b_idx_0;
        double b_idx_1;
        double b_idx_2;
        double R0_idx_0;
        double R0_idx_1;
        double R0_idx_2;
        double R1_idx_0;
        double R1_idx_1;
        double R1_idx_2;
        double phi0;
        double phi1;
        double theta;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        P0[0] = p0x;
        P0[1] = p0y;
        P0[2] = p0z;
        P1[0] = p1x;
        P1[1] = p1y;
        P1[2] = p1z;
        b_idx_0 = p0x - cx;
        b_idx_1 = p0y - cy;
        b_idx_2 = p0z - cz;
        R0_idx_0 = evec[1] * b_idx_2 - evec[2] * b_idx_1;
        R0_idx_1 = evec[2] * b_idx_0 - evec[0] * b_idx_2;
        R0_idx_2 = evec[0] * b_idx_1 - evec[1] * b_idx_0;
        b_idx_0 = p1x - cx;
        b_idx_1 = p1y - cy;
        b_idx_2 = p1z - cz;
        R1_idx_0 = evec[1] * b_idx_2 - evec[2] * b_idx_1;
        R1_idx_1 = evec[2] * b_idx_0 - evec[0] * b_idx_2;
        R1_idx_2 = evec[0] * b_idx_1 - evec[1] * b_idx_0;
        if (evec[0] > 0.5) {
            phi0 = atan2(R0_idx_2, R0_idx_1);
            phi1 = atan2(R1_idx_2, R1_idx_1);
        } else if (evec[1] > 0.5) {
            phi1 = atan2(R0_idx_2, R0_idx_0);
            phi0 = atan2(R1_idx_2, R1_idx_0);

            //      rotation = -rotation;
        } else {
            phi0 = atan2(R0_idx_1, R0_idx_0);
            phi1 = atan2(R1_idx_1, R1_idx_0);
        }

        theta = phi1 - phi0;
        if (rotation > 0.0) {
            if (theta <= 0.0) {
                theta += 6.2831853071795862;
            }

            theta += (rotation - 1.0) * 2.0 * 3.1415926535897931;
        } else {
            if (theta >= 0.0) {
                theta -= 6.2831853071795862;
            }

            theta += (rotation + 1.0) * 2.0 * 3.1415926535897931;
        }

        ConstrHelixStruct(P0, P1, evec, theta, (((evec[0] * p1x + evec[1] * p1y) + evec[2] * p1z) -
                           ((evec[0] * p0x + evec[1] * p0y) + evec[2] * p0z)) / theta * 2.0 *
                          3.1415926535897931, 1.0, ZSpdMode_NN, b_CurvStruct);
    }

    //
    // Arguments    : const double P0[3]
    //                const double P1[3]
    //                double FeedRate
    //                ZSpdMode b_ZSpdMode
    //                CurvStruct *b_CurvStruct
    // Return Type  : void
    //
    void ConstrLineStruct(const double P0[3], const double P1[3], double FeedRate, ZSpdMode
                          b_ZSpdMode, CurvStruct *b_CurvStruct)
    {
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        //
        //
        //  ctxType = coder.OutputType('InitFeedoptPlan');
        b_CurvStruct->Type = CurveType_Line;
        b_CurvStruct->zspdmode = b_ZSpdMode;
        b_CurvStruct->P0[0] = P0[0];
        b_CurvStruct->P1[0] = P1[0];
        b_CurvStruct->evec[0] = 0.0;
        b_CurvStruct->P0[1] = P0[1];
        b_CurvStruct->P1[1] = P1[1];
        b_CurvStruct->evec[1] = 0.0;
        b_CurvStruct->P0[2] = P0[2];
        b_CurvStruct->P1[2] = P1[2];
        b_CurvStruct->evec[2] = 0.0;
        b_CurvStruct->theta = 0.0;
        b_CurvStruct->pitch = 0.0;
        for (int i = 0; i < 6; i++) {
            b_CurvStruct->CoeffP5[i][0] = 0.0;
            b_CurvStruct->CoeffP5[i][1] = 0.0;
            b_CurvStruct->CoeffP5[i][2] = 0.0;
        }

        b_CurvStruct->sp_index = 1;
        b_CurvStruct->FeedRate = FeedRate;
        b_CurvStruct->MaxConstantFeedRate = 0.0;
        b_CurvStruct->i_begin_sp = 0;
        b_CurvStruct->i_end_sp = 0;
        b_CurvStruct->gcode_source_line = 0;
        b_CurvStruct->index_smooth = 0;
        b_CurvStruct->UseConstJerk = false;
        b_CurvStruct->ConstJerk = 0.0;
        b_CurvStruct->ConstJerkMaxIterations = 0;
        b_CurvStruct->Coeff.set_size(0);
        b_CurvStruct->a_param = 1.0;
        b_CurvStruct->b_param = 0.0;
        b_CurvStruct->sp.CoeffX.set_size(1, 1);
        b_CurvStruct->sp.CoeffX[0] = 0.0;
        b_CurvStruct->sp.CoeffY.set_size(1, 1);
        b_CurvStruct->sp.CoeffY[0] = 0.0;
        b_CurvStruct->sp.CoeffZ.set_size(1, 1);
        b_CurvStruct->sp.CoeffZ[0] = 0.0;
        b_CurvStruct->sp.Bl.ncoeff = 0;
        b_CurvStruct->sp.Bl.breakpoints.set_size(1, 0);
        b_CurvStruct->sp.Bl.handle = 0UL;
        b_CurvStruct->sp.Bl.degree = 0;
        b_CurvStruct->sp.knots.set_size(1, 1);
        b_CurvStruct->sp.knots[0] = 0.0;
    }

    //
    // Arguments    : const CurvStruct *Curv
    //                CurvStruct *Copy
    // Return Type  : void
    //
    void CopyCurvStruct(const CurvStruct *Curv, CurvStruct *Copy)
    {
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        *Copy = *Curv;
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const FeedoptContext *ctx
    //                const CurvStruct *b_CurvStruct
    //                coder::array<double, 2U> *u_vec
    //                coder::array<double, 2U> *r0D
    //                coder::array<double, 2U> *r1D
    //                coder::array<double, 2U> *r2D
    //                coder::array<double, 2U> *r3D
    // Return Type  : void
    //
    void EvalCurvStruct(const FeedoptContext *ctx, const CurvStruct *b_CurvStruct, coder::array<
                        double, 2U> &u_vec, coder::array<double, 2U> &r0D, coder::array<double, 2U>
                        &r1D, coder::array<double, 2U> &r2D, coder::array<double, 2U> &r3D)
    {
        coder::array<bool, 2U> x;
        int loop_ub;
        bool y;
        int k;
        bool exitg1;
        int b_loop_ub;
        bool b_y;
        int b_k;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        coder::array<double, 2U> u_vec_tilda;
        int g_loop_ub;
        int scalarLB;
        int vectorUB;
        int i6;
        CurvStruct expl_temp;
        char message[30];
        coder::array<double, 2U> Spline_sp_CoeffX;
        int i_loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffY;
        double c;
        int m_loop_ub;
        coder::array<double, 2U> Spline_sp_CoeffZ;
        double b_c;
        int p_loop_ub;
        coder::array<double, 2U> r0Dx;
        coder::array<double, 2U> r1Dx;
        coder::array<double, 2U> r2Dx;
        coder::array<double, 2U> r3Dx;
        coder::array<double, 2U> r0Dy;
        coder::array<double, 2U> r1Dy;
        coder::array<double, 2U> r2Dy;
        coder::array<double, 2U> r3Dy;
        coder::array<double, 2U> r0Dz;
        coder::array<double, 2U> r1Dz;
        coder::array<double, 2U> r2Dz;
        coder::array<double, 2U> r3Dz;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        x.set_size(1, u_vec.size(1));
        loop_ub = u_vec.size(1);
        for (int i = 0; i < loop_ub; i++) {
            x[i] = (u_vec[i] - 1.0 > 2.2204460492503131E-15);
        }

        y = false;
        k = 0;
        exitg1 = false;
        while ((!exitg1) && (k <= x.size(1) - 1)) {
            if (!x[k]) {
                k++;
            } else {
                y = true;
                exitg1 = true;
            }
        }

        if (y) {
            int end;
            printf("EvalCurvStruct: u_vec > 1\n");
            fflush(stdout);
            end = u_vec.size(1);
            for (int b_i = 0; b_i < end; b_i++) {
                if (u_vec[b_i] > 1.0) {
                    u_vec[b_i] = 1.0;
                }
            }
        }

        x.set_size(1, u_vec.size(1));
        b_loop_ub = u_vec.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            x[i1] = (u_vec[i1] < 0.0);
        }

        b_y = false;
        b_k = 0;
        exitg1 = false;
        while ((!exitg1) && (b_k <= x.size(1) - 1)) {
            if (!x[b_k]) {
                b_k++;
            } else {
                b_y = true;
                exitg1 = true;
            }
        }

        if (b_y) {
            int b_end;
            printf("EvalCurvStruct: u_vec < 0\n");
            fflush(stdout);
            b_end = u_vec.size(1);
            for (int c_i = 0; c_i < b_end; c_i++) {
                if (u_vec[c_i] < 0.0) {
                    u_vec[c_i] = 0.0;
                }
            }
        }

        //
        //
        r0D.set_size(3, u_vec.size(1));
        c_loop_ub = u_vec.size(1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            r0D[3 * i2] = 0.0;
            r0D[3 * i2 + 1] = 0.0;
            r0D[3 * i2 + 2] = 0.0;
        }

        r1D.set_size(3, u_vec.size(1));
        d_loop_ub = u_vec.size(1);
        for (int i3 = 0; i3 < d_loop_ub; i3++) {
            r1D[3 * i3] = 0.0;
            r1D[3 * i3 + 1] = 0.0;
            r1D[3 * i3 + 2] = 0.0;
        }

        r2D.set_size(3, u_vec.size(1));
        e_loop_ub = u_vec.size(1);
        for (int i4 = 0; i4 < e_loop_ub; i4++) {
            r2D[3 * i4] = 0.0;
            r2D[3 * i4 + 1] = 0.0;
            r2D[3 * i4 + 2] = 0.0;
        }

        r3D.set_size(3, u_vec.size(1));
        f_loop_ub = u_vec.size(1);
        for (int i5 = 0; i5 < f_loop_ub; i5++) {
            r3D[3 * i5] = 0.0;
            r3D[3 * i5 + 1] = 0.0;
            r3D[3 * i5 + 2] = 0.0;
        }

        u_vec_tilda.set_size(1, u_vec.size(1));
        g_loop_ub = u_vec.size(1);
        scalarLB = u_vec.size(1) & -4;
        vectorUB = scalarLB - 4;
        for (i6 = 0; i6 <= vectorUB; i6 += 4) {
            __m256d r;
            r = _mm256_loadu_pd(&u_vec[i6]);
            _mm256_storeu_pd(&u_vec_tilda[i6], _mm256_add_pd(_mm256_mul_pd(_mm256_set1_pd
                               (b_CurvStruct->a_param), r), _mm256_set1_pd(b_CurvStruct->b_param)));
        }

        for (i6 = scalarLB; i6 < g_loop_ub; i6++) {
            u_vec_tilda[i6] = b_CurvStruct->a_param * u_vec[i6] + b_CurvStruct->b_param;
        }

        switch (b_CurvStruct->Type) {
          case CurveType_Line:
            {
                int j_loop_ub;
                int l_loop_ub;
                int n_loop_ub;
                double a_idx_0;
                double a_idx_1;
                double a_idx_2;
                int s_loop_ub;
                int u_loop_ub;

                //  line (G01)
                //
                //  parametrization of a straight line between P0 and P1
                //
                r0D.set_size(3, u_vec_tilda.size(1));
                j_loop_ub = u_vec_tilda.size(1);
                for (int i10 = 0; i10 < j_loop_ub; i10++) {
                    double d;
                    d = u_vec_tilda[i10];
                    r0D[3 * i10] = b_CurvStruct->P1[0] * d + b_CurvStruct->P0[0] * (1.0 - d);
                }

                l_loop_ub = u_vec_tilda.size(1);
                for (int i12 = 0; i12 < l_loop_ub; i12++) {
                    double d1;
                    d1 = u_vec_tilda[i12];
                    r0D[3 * i12 + 1] = b_CurvStruct->P1[1] * d1 + b_CurvStruct->P0[1] * (1.0 - d1);
                }

                n_loop_ub = u_vec_tilda.size(1);
                for (int i14 = 0; i14 < n_loop_ub; i14++) {
                    double d2;
                    d2 = u_vec_tilda[i14];
                    r0D[3 * i14 + 2] = b_CurvStruct->P1[2] * d2 + b_CurvStruct->P0[2] * (1.0 - d2);
                }

                //
                a_idx_0 = b_CurvStruct->P1[0] - b_CurvStruct->P0[0];
                a_idx_1 = b_CurvStruct->P1[1] - b_CurvStruct->P0[1];
                a_idx_2 = b_CurvStruct->P1[2] - b_CurvStruct->P0[2];
                r1D.set_size(3, u_vec_tilda.size(1));
                if (u_vec_tilda.size(1) != 0) {
                    int i18;
                    i18 = u_vec_tilda.size(1) - 1;
                    for (int t = 0; t <= i18; t++) {
                        r1D[3 * t] = a_idx_0;
                        r1D[3 * t + 1] = a_idx_1;
                        r1D[3 * t + 2] = a_idx_2;
                    }
                }

                //
                r2D.set_size(3, u_vec_tilda.size(1));
                s_loop_ub = u_vec_tilda.size(1);
                for (int i20 = 0; i20 < s_loop_ub; i20++) {
                    r2D[3 * i20] = 0.0;
                    r2D[3 * i20 + 1] = 0.0;
                    r2D[3 * i20 + 2] = 0.0;
                }

                r3D.set_size(3, u_vec_tilda.size(1));
                u_loop_ub = u_vec_tilda.size(1);
                for (int i22 = 0; i22 < u_loop_ub; i22++) {
                    r3D[3 * i22] = 0.0;
                    r3D[3 * i22 + 1] = 0.0;
                    r3D[3 * i22 + 2] = 0.0;
                }
            }
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(b_CurvStruct->P0, b_CurvStruct->P1, b_CurvStruct->evec, b_CurvStruct->theta,
                      b_CurvStruct->pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(b_CurvStruct->CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            {
                int h_loop_ub;
                int k_loop_ub;
                int o_loop_ub;
                int q_loop_ub;
                int r_loop_ub;
                int t_loop_ub;
                int v_loop_ub;
                int w_loop_ub;
                int x_loop_ub;
                int y_loop_ub;
                int ab_loop_ub;
                int bb_loop_ub;
                int cb_loop_ub;
                int db_loop_ub;
                int eb_loop_ub;

                //  BSpline
                ctx->q_splines.get(b_CurvStruct->sp_index, (&expl_temp));
                Spline_sp_CoeffX.set_size(1, expl_temp.sp.CoeffX.size(1));
                h_loop_ub = expl_temp.sp.CoeffX.size(1);
                for (int i8 = 0; i8 < h_loop_ub; i8++) {
                    Spline_sp_CoeffX[i8] = expl_temp.sp.CoeffX[i8];
                }

                Spline_sp_CoeffY.set_size(1, expl_temp.sp.CoeffY.size(1));
                k_loop_ub = expl_temp.sp.CoeffY.size(1);
                for (int i11 = 0; i11 < k_loop_ub; i11++) {
                    Spline_sp_CoeffY[i11] = expl_temp.sp.CoeffY[i11];
                }

                Spline_sp_CoeffZ.set_size(1, expl_temp.sp.CoeffZ.size(1));
                o_loop_ub = expl_temp.sp.CoeffZ.size(1);
                for (int i15 = 0; i15 < o_loop_ub; i15++) {
                    Spline_sp_CoeffZ[i15] = expl_temp.sp.CoeffZ[i15];
                }

                bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffX, u_vec_tilda, r0Dx, r1Dx,
                                 r2Dx, r3Dx);
                bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffY, u_vec_tilda, r0Dy, r1Dy,
                                 r2Dy, r3Dy);
                bspline_eval_vec(expl_temp.sp.Bl.handle, Spline_sp_CoeffZ, u_vec_tilda, r0Dz, r1Dz,
                                 r2Dz, r3Dz);
                r0D.set_size(3, r0Dx.size(1));
                q_loop_ub = r0Dx.size(1);
                for (int i17 = 0; i17 < q_loop_ub; i17++) {
                    r0D[3 * i17] = r0Dx[i17];
                }

                r_loop_ub = r0Dy.size(1);
                for (int i19 = 0; i19 < r_loop_ub; i19++) {
                    r0D[3 * i19 + 1] = r0Dy[i19];
                }

                t_loop_ub = r0Dz.size(1);
                for (int i21 = 0; i21 < t_loop_ub; i21++) {
                    r0D[3 * i21 + 2] = r0Dz[i21];
                }

                r1D.set_size(3, r1Dx.size(1));
                v_loop_ub = r1Dx.size(1);
                for (int i23 = 0; i23 < v_loop_ub; i23++) {
                    r1D[3 * i23] = r1Dx[i23];
                }

                w_loop_ub = r1Dy.size(1);
                for (int i24 = 0; i24 < w_loop_ub; i24++) {
                    r1D[3 * i24 + 1] = r1Dy[i24];
                }

                x_loop_ub = r1Dz.size(1);
                for (int i25 = 0; i25 < x_loop_ub; i25++) {
                    r1D[3 * i25 + 2] = r1Dz[i25];
                }

                r2D.set_size(3, r2Dx.size(1));
                y_loop_ub = r2Dx.size(1);
                for (int i26 = 0; i26 < y_loop_ub; i26++) {
                    r2D[3 * i26] = r2Dx[i26];
                }

                ab_loop_ub = r2Dy.size(1);
                for (int i27 = 0; i27 < ab_loop_ub; i27++) {
                    r2D[3 * i27 + 1] = r2Dy[i27];
                }

                bb_loop_ub = r2Dz.size(1);
                for (int i28 = 0; i28 < bb_loop_ub; i28++) {
                    r2D[3 * i28 + 2] = r2Dz[i28];
                }

                r3D.set_size(3, r3Dx.size(1));
                cb_loop_ub = r3Dx.size(1);
                for (int i29 = 0; i29 < cb_loop_ub; i29++) {
                    r3D[3 * i29] = r3Dx[i29];
                }

                db_loop_ub = r3Dy.size(1);
                for (int i30 = 0; i30 < db_loop_ub; i30++) {
                    r3D[3 * i30 + 1] = r3Dy[i30];
                }

                eb_loop_ub = r3Dz.size(1);
                for (int i31 = 0; i31 < eb_loop_ub; i31++) {
                    r3D[3 * i31 + 2] = r3Dz[i31];
                }
            }
            break;

          default:
            for (int i7 = 0; i7 < 30; i7++) {
                message[i7] = cv[i7];
            }

            c_assert_(&message[0]);
            break;
        }

        r1D.set_size(3, r1D.size(1));
        i_loop_ub = r1D.size(1);
        for (int i9 = 0; i9 < i_loop_ub; i9++) {
            r1D[3 * i9] = b_CurvStruct->a_param * r1D[3 * i9];
            r1D[3 * i9 + 1] = b_CurvStruct->a_param * r1D[3 * i9 + 1];
            r1D[3 * i9 + 2] = b_CurvStruct->a_param * r1D[3 * i9 + 2];
        }

        c = std::pow(b_CurvStruct->a_param, 2.0);
        r2D.set_size(3, r2D.size(1));
        m_loop_ub = r2D.size(1);
        for (int i13 = 0; i13 < m_loop_ub; i13++) {
            r2D[3 * i13] = c * r2D[3 * i13];
            r2D[3 * i13 + 1] = c * r2D[3 * i13 + 1];
            r2D[3 * i13 + 2] = c * r2D[3 * i13 + 2];
        }

        b_c = std::pow(b_CurvStruct->a_param, 3.0);
        r3D.set_size(3, r3D.size(1));
        p_loop_ub = r3D.size(1);
        for (int i16 = 0; i16 < p_loop_ub; i16++) {
            r3D[3 * i16] = b_c * r3D[3 * i16];
            r3D[3 * i16 + 1] = b_c * r3D[3 * i16 + 1];
            r3D[3 * i16 + 2] = b_c * r3D[3 * i16 + 2];
        }
    }

    //
    // Arguments    : const CurvStruct *Curv
    //                const CurvStruct *Spline
    //                double u
    //                double r0D[3]
    // Return Type  : void
    //
    void EvalPosition(const CurvStruct *Curv, const CurvStruct *Spline, double u, double r0D[3])
    {
        double u_vec;
        double u_vec_tilda;
        double r1D[3];
        double r2D[3];
        double r3D[3];
        double r0Dx;
        double r1Dx;
        double r2Dx;
        double r3Dx;
        char message[30];
        double r0Dy;
        double r1Dy;
        double r2Dy;
        double r3Dy;
        double r0Dz;
        double r1Dz;
        double r2Dz;
        double r3Dz;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        u_vec = u;

        //  coder.cstructname(CurvStruct, 'CurvStruct')
        if (u - 1.0 > 2.2204460492503131E-15) {
            double unnamed_idx_0;
            printf("EvalCurvStruct: u_vec > 1\n");
            fflush(stdout);
            unnamed_idx_0 = u;
            if (u > 1.0) {
                unnamed_idx_0 = 1.0;
            }

            u_vec = unnamed_idx_0;
        }

        if (u_vec < 0.0) {
            printf("EvalCurvStruct: u_vec < 0\n");
            fflush(stdout);
            u_vec = 0.0;
        }

        //
        //
        r0D[0] = 0.0;
        r0D[1] = 0.0;
        r0D[2] = 0.0;
        u_vec_tilda = Curv->a_param * u_vec + Curv->b_param;
        switch (Curv->Type) {
          case CurveType_Line:
            //  line (G01)
            //
            //  parametrization of a straight line between P0 and P1
            //
            r0D[0] = Curv->P1[0] * u_vec_tilda + Curv->P0[0] * (1.0 - u_vec_tilda);
            r0D[1] = Curv->P1[1] * u_vec_tilda + Curv->P0[1] * (1.0 - u_vec_tilda);
            r0D[2] = Curv->P1[2] * u_vec_tilda + Curv->P0[2] * (1.0 - u_vec_tilda);

            //
            //
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            b_EvalHelix(Curv->P0, Curv->P1, Curv->evec, Curv->theta, Curv->pitch, u_vec_tilda, r0D,
                        r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            b_EvalTransP5(Curv->CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            //  BSpline
            b_bspline_eval_vec(Spline->sp.Bl.handle, Spline->sp.CoeffX, u_vec_tilda, &r0Dx, &r1Dx,
                               &r2Dx, &r3Dx);
            b_bspline_eval_vec(Spline->sp.Bl.handle, Spline->sp.CoeffY, u_vec_tilda, &r0Dy, &r1Dy,
                               &r2Dy, &r3Dy);
            b_bspline_eval_vec(Spline->sp.Bl.handle, Spline->sp.CoeffZ, u_vec_tilda, &r0Dz, &r1Dz,
                               &r2Dz, &r3Dz);
            r0D[0] = r0Dx;
            r0D[1] = r0Dy;
            r0D[2] = r0Dz;
            break;

          default:
            for (int i = 0; i < 30; i++) {
                message[i] = cv[i];
            }

            c_assert_(&message[0]);
            break;
        }
    }

    //
    // % Use a variable number of breakpoints for different lengths
    //    % Use a linear distribution of breakpoints (else sinspace)
    //  % Distance between two breakpoints in mm
    // Arguments    : FeedoptConfig *cfg
    // Return Type  : void
    //
    void FeedoptDefaultConfig(FeedoptConfig *cfg)
    {
        static const char b_cv[9] = { 'l', 'o', 'g', 's', '/', 'l', 'o', 'g', 's' };

        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        cfg->NDiscr = 20;
        cfg->NBreak = 10;
        cfg->UseDynamicBreakpoints = false;
        cfg->UseLinearBreakpoints = false;
        cfg->DynamicBreakpointsDistance = 0.1;
        cfg->NHorz = 5;
        cfg->vmax = 150.0;
        cfg->amax[0] = 20000.0;
        cfg->jmax[0] = 1.5E+6;
        cfg->amax[1] = 20000.0;
        cfg->jmax[1] = 1.5E+6;
        cfg->amax[2] = 20000.0;
        cfg->jmax[2] = 1.5E+6;
        cfg->SplineDegree = 4;
        cfg->CutOff = 0.1;
        cfg->LSplit = 3.0;
        cfg->LThreshold = 0.3;
        cfg->CuspThreshold = 45.0;
        cfg->v_0 = 0.1;
        cfg->at_0 = 0.0;
        cfg->v_1 = 0.1;
        cfg->at_1 = 0.0;
        cfg->dt = 0.0001;
        cfg->ZeroStartAccLimit = 0.01;
        cfg->ZeroStartJerkLimit = 1.0;
        cfg->ZeroStartVelLimit = 0.5;
        std::memset(&cfg->source[0], 0, 1024U * sizeof(char));
        cfg->DebugCutZero = false;
        cfg->SkipCompressing = false;
        cfg->CollTolDeg = 1.0E-6;
        cfg->NGridLengthSpline = 10.0;
        for (int i = 0; i < 9; i++) {
            cfg->LogFileName[i] = b_cv[i];
        }

        //      coder.varsize('cfg.source', [1024, 1], [0,1]);;
        //          'MaxNHorz', FeedoptLimits.MaxNHorz,...
        //          'MaxNDiscr', FeedoptLimits.MaxNDiscr,...
        //          'MaxNCoeff', FeedoptLimits.MaxNCoeff,...
        //  coder.varsize('cfg.source', [1, Inf], [0, 1]);
    }

    //
    // See InitFeedoptPlan for information about the context variable ctx
    // Arguments    : FeedoptContext *ctx
    //                bool *optimized
    //                CurvStruct *opt_struct
    // Return Type  : void
    //
    void FeedoptPlan(FeedoptContext *ctx, bool *optimized, CurvStruct *opt_struct)
    {
        bool b_optimized;
        char message[39];
        static const char b_message[39] = { 'F', 'e', 'e', 'd', 'o', 'p', 't', 'P', 'l', 'a', 'n',
            ':', ' ', 'e', 'r', 'r', 'o', 'r', ' ', 'c', 'o', 'd', 'e', ' ', 'w', 'a', 's', ' ', 'n',
            'o', 't', ' ', 'h', 'a', 'n', 'd', 'l', 'e', 'd' };

        double dv[3];
        double dv1[3];
        bool guard1 = false;
        CurvStruct b_CurvStruct;
        char b_cv[1025];
        CurvStruct a;
        coder::array<CurvStruct, 2U> OptSegment;
        CurvStruct first;
        coder::array<double, 2U> c_ctx;
        queue_coder d_ctx;
        CurvStruct last;
        CurvStruct NextCurv;
        coder::array<double, 2U> Coeff;
        CurvStruct expl_temp;
        queue_coder e_ctx;
        double at_0;
        double dv2[3];
        double dv3[3];
        coder::array<double, 2U> r;
        coder::array<double, 2U> r1;
        coder::array<double, 2U> r2;
        coder::array<double, 1U> r3;
        coder::array<double, 2U> r4;
        int unusedU0;
        bool b_success;
        double t0_P0[3];
        double t0_P1[3];
        double t0_evec[3];
        queue_coder g_ctx;
        double t0_CoeffP5[6][3];
        queue_coder h_ctx;
        double b_at_0;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        if (!(ctx->errcode == FeedoptPlanError_Success)) {
            for (int i = 0; i < 39; i++) {
                message[i] = b_message[i];
            }

            c_assert_(&message[0]);
        }

        b_optimized = false;

        //  opt_struct = struct('Coeff', zeros(ctx.cfg.MaxNCoeff, 1),...
        //      'CurvStruct', ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN));
        //  coder.cstructname(opt_struct, 'OptCurvStruct');
        dv[0] = 0.0;
        dv1[0] = 0.0;
        dv[1] = 0.0;
        dv1[1] = 0.0;
        dv[2] = 0.0;
        dv1[2] = 0.0;
        ConstrLineStruct(dv, dv1, 0.2, ZSpdMode_NN, opt_struct);
        guard1 = false;
        switch (ctx->op) {
          case Fopt_Init:
            ctx->op = Fopt_GCode;

            //          coder.varsize('OptSegment', [1, FeedoptLimits.MaxNHorz], [0, 0]);
            //          coder.varsize('Coeff', [FeedoptLimits.MaxNCoeff, FeedoptLimits.MaxNHorz], [1,1]); 
            //  fprintf('Starting optimization with NHorz = %d\n', ctx.cfg.NHorz);
            //
            break;

          case Fopt_GCode:
            {
                int status;
                unsigned long u;

                //  coder.extrinsic('ReadGCode_mex');
                //  Wrapper for pulling the next gcode line from the interpreter
                dv[0] = 1.0;
                dv1[0] = 4.0;
                dv[1] = 2.0;
                dv1[1] = 5.0;
                dv[2] = 3.0;
                dv1[2] = 6.0;
                ConstrLineStruct(dv, dv1, 0.2, ZSpdMode_NN, &b_CurvStruct);
                std::memcpy(&b_cv[0], &ctx->cfg.source[0], 1024U * sizeof(char));
                b_cv[1024] = '\x00';
                status = c_open_gcode(&b_cv[0], &b_CurvStruct);

                //  1 -> stdout
                //  2 -> stderr
                u = static_cast<unsigned long>(std::round(DebugConfig));
                if ((u & 1UL) != 0UL) {
                    printf("Reading G-code...\n");
                    fflush(stdout);
                }

                if (status != 0) {
                    dv[0] = 1.0;
                    dv1[0] = 4.0;
                    dv[1] = 2.0;
                    dv1[1] = 5.0;
                    dv[2] = 3.0;
                    dv1[2] = 6.0;
                }

                while (status != 0) {
                    int b_status;

                    //  coder.extrinsic('ReadGCode_mex');
                    //  Wrapper for pulling the next gcode line from the interpreter
                    ConstrLineStruct(dv, dv1, 0.2, ZSpdMode_NN, &b_CurvStruct);
                    b_status = c_read_and_exec_gcode(NULL, &b_CurvStruct);
                    status = b_status;
                    if ((b_status == 1) && (static_cast<int>(b_CurvStruct.Type) != 0)) {
                        ctx->q_gcode.push((&b_CurvStruct));
                    }
                }

                if (ctx->q_gcode.isempty()) {
                    ctx->op = Fopt_Finished;

                    //  1 -> stdout
                    //  2 -> stderr
                    if ((u & 16UL) != 0UL) {
                        printf("ERROR: Optimization failed, Gcode queue is empty\n");
                        fflush(stdout);
                    }
                } else {
                    ctx->q_gcode.rget((&last));
                    if (last.zspdmode == ZSpdMode_NN) {
                        last.zspdmode = ZSpdMode_NZ;
                    } else {
                        if (last.zspdmode == ZSpdMode_ZN) {
                            last.zspdmode = ZSpdMode_ZZ;
                        }
                    }

                    ctx->q_gcode.set(ctx->q_gcode.size(), (&last));
                    ctx->op = Fopt_Check;
                }
            }
            break;

          case Fopt_Check:
            CheckCurvStructs(ctx);
            ctx->op = Fopt_Compress;
            break;

          case Fopt_Compress:
            if (ctx->cfg.SkipCompressing) {
                ExpandZeroStructs(ctx);
            } else {
                CompressCurvStructs(ctx);
            }

            ctx->op = Fopt_Smooth;
            break;

          case Fopt_Smooth:
            SmoothCurvStructs(ctx);
            ctx->op = Fopt_Split;
            break;

          case Fopt_Split:
            SplitCurvStructs(ctx);
            ctx->op = Fopt_Opt;
            break;

          case Fopt_Opt:
            {
                if (ctx->q_split.isempty()) {
                    ctx->op = Fopt_Finished;
                } else {
                    ctx->op = Fopt_Opt;
                    if ((static_cast<unsigned long>(std::round(DebugConfig)) & 2UL) != 0UL) {
                        unsigned int validatedHoleFilling_f2;
                        validatedHoleFilling_f2 = ctx->q_split.size();
                        printf("%4d/%u\n", ctx->k0, validatedHoleFilling_f2);
                        fflush(stdout);
                    }

                    if (ctx->go_next) {
                        ctx->k0++;
                        ctx->n_optimized++;
                    }

                    if (static_cast<double>(ctx->n_optimized) < ctx->q_split.size()) {
                        if (ctx->try_push_again) {
                            //  Do nothing, we already have the last one optimized
                            guard1 = true;
                        } else if (!ctx->reached_end) {
                            int outsize_idx_1;
                            ctx->q_split.get(1.0, (&a));
                            outsize_idx_1 = ctx->cfg.NHorz;
                            OptSegment.set_size(1, outsize_idx_1);
                            for (int i3 = 0; i3 < outsize_idx_1; i3++) {
                                OptSegment[i3] = a;
                            }

                            ctx->q_split.get(ctx->k0, (&first));
                            if (first.zspdmode == ZSpdMode_ZN) {
                                *opt_struct = first;
                                b_optimized = true;
                                d_ctx = ctx->q_splines;
                                CalcZeroStartConstraints(&d_ctx, first.Type, first.P0, first.P1,
                                    first.evec, first.theta, first.pitch, first.CoeffP5,
                                    first.sp_index, first.UseConstJerk, first.ConstJerk,
                                    first.a_param, first.b_param, 1.0, &ctx->v_0, &ctx->at_0);
                                ctx->zero_start = true;
                            } else {
                                int k1temp;
                                int k1;
                                unsigned int nopt;
                                unsigned long u1;
                                int kend;
                                int k;
                                bool exitg1;
                                int Retry;
                                bool success;
                                int e_loop_ub;
                                k1temp = (ctx->k0 + ctx->cfg.NHorz) - 1;
                                if (static_cast<double>(k1temp) > ctx->q_split.size()) {
                                    ctx->reached_end = true;
                                    k1 = static_cast<int>(ctx->q_split.size());
                                } else {
                                    k1 = k1temp;
                                }

                                ctx->at_1 = 0.0;
                                ctx->v_1 = 0.0;
                                nopt = 0U;

                                //  1 -> stdout
                                //  2 -> stderr
                                u1 = static_cast<unsigned long>(std::round(DebugConfig)) & 8UL;
                                if (u1 != 0UL) {
                                    printf("FEEDRATE PLANNING...\n");
                                    fflush(stdout);
                                }

                                kend = ctx->k0;
                                k = ctx->k0;
                                exitg1 = false;
                                while ((!exitg1) && (k <= k1)) {
                                    ctx->q_split.get(k, (&NextCurv));
                                    if (NextCurv.zspdmode == ZSpdMode_NZ) {
                                        //  If we reach an NZ segment, we set the final velocity
                                        //  and tangent acceleration constraints to the ones
                                        //  specified by the segment, and pretend this is the
                                        //  end of all segments
                                        e_ctx = ctx->q_splines;
                                        CalcZeroStartConstraints(&e_ctx, NextCurv.Type, NextCurv.P0,
                                            NextCurv.P1, NextCurv.evec, NextCurv.theta,
                                            NextCurv.pitch, NextCurv.CoeffP5, NextCurv.sp_index,
                                            NextCurv.UseConstJerk, NextCurv.ConstJerk,
                                            NextCurv.a_param, NextCurv.b_param, 1.0, &ctx->v_1,
                                            &at_0);
                                        ctx->at_1 = -at_0;
                                        ctx->zero_end = true;
                                        ctx->reached_end = true;
                                        kend = k;
                                        exitg1 = true;
                                    } else {
                                        if (NextCurv.zspdmode == ZSpdMode_NN) {
                                            nopt++;
                                            OptSegment[static_cast<int>(nopt) - 1] = NextCurv;
                                            if (u1 != 0UL) {
                                                expl_temp = OptSegment[k - ctx->k0];
                                                b_PrintCurvStruct(&ctx->q_splines,
                                                                  ctx->cfg.NGridLengthSpline,
                                                                  expl_temp.Type, expl_temp.zspdmode,
                                                                  expl_temp.P0, expl_temp.P1,
                                                                  expl_temp.evec, expl_temp.theta,
                                                                  expl_temp.pitch, expl_temp.CoeffP5,
                                                                  expl_temp.sp_index,
                                                                  expl_temp.FeedRate,
                                                                  expl_temp.UseConstJerk,
                                                                  expl_temp.ConstJerk,
                                                                  expl_temp.a_param,
                                                                  expl_temp.b_param);
                                            }

                                            if ((k < k1) && (u1 != 0UL)) {
                                                //  1 -> stdout
                                                //  2 -> stderr
                                                printf("-----------------------------------\n");
                                                fflush(stdout);
                                            }
                                        }

                                        k++;
                                    }
                                }

                                //  1 -> stdout
                                //  2 -> stderr
                                if (u1 != 0UL) {
                                    printf("================================================\n");
                                    fflush(stdout);
                                }

                                Retry = 0;
                                success = false;
                                Coeff.set_size(0, 0);
                                while ((Retry < 100) && (!success)) {
                                    int g_loop_ub;
                                    int i_loop_ub;
                                    int k_loop_ub;
                                    int m_loop_ub;
                                    int n_loop_ub;
                                    int f_ctx;
                                    dv2[0] = ctx->cfg.amax[0];
                                    dv3[0] = ctx->cfg.jmax[0];
                                    dv2[1] = ctx->cfg.amax[1];
                                    dv3[1] = ctx->cfg.jmax[1];
                                    dv2[2] = ctx->cfg.amax[2];
                                    dv3[2] = ctx->cfg.jmax[2];
                                    r.set_size(ctx->BasisVal.size(0), ctx->BasisVal.size(1));
                                    g_loop_ub = ctx->BasisVal.size(1);
                                    for (int i12 = 0; i12 < g_loop_ub; i12++) {
                                        int h_loop_ub;
                                        h_loop_ub = ctx->BasisVal.size(0);
                                        for (int i13 = 0; i13 < h_loop_ub; i13++) {
                                            r[i13 + r.size(0) * i12] = ctx->BasisVal[i13 +
                                                ctx->BasisVal.size(0) * i12];
                                        }
                                    }

                                    r1.set_size(ctx->BasisValD.size(0), ctx->BasisValD.size(1));
                                    i_loop_ub = ctx->BasisValD.size(1);
                                    for (int i14 = 0; i14 < i_loop_ub; i14++) {
                                        int j_loop_ub;
                                        j_loop_ub = ctx->BasisValD.size(0);
                                        for (int i15 = 0; i15 < j_loop_ub; i15++) {
                                            r1[i15 + r1.size(0) * i14] = ctx->BasisValD[i15 +
                                                ctx->BasisValD.size(0) * i14];
                                        }
                                    }

                                    r2.set_size(ctx->BasisValDD.size(0), ctx->BasisValDD.size(1));
                                    k_loop_ub = ctx->BasisValDD.size(1);
                                    for (int i16 = 0; i16 < k_loop_ub; i16++) {
                                        int l_loop_ub;
                                        l_loop_ub = ctx->BasisValDD.size(0);
                                        for (int i17 = 0; i17 < l_loop_ub; i17++) {
                                            r2[i17 + r2.size(0) * i16] = ctx->BasisValDD[i17 +
                                                ctx->BasisValDD.size(0) * i16];
                                        }
                                    }

                                    r3.set_size(ctx->BasisIntegr.size(0));
                                    m_loop_ub = ctx->BasisIntegr.size(0);
                                    for (int i18 = 0; i18 < m_loop_ub; i18++) {
                                        r3[i18] = ctx->BasisIntegr[i18];
                                    }

                                    r4.set_size(1, ctx->u_vec.size(1));
                                    n_loop_ub = ctx->u_vec.size(1);
                                    for (int i19 = 0; i19 < n_loop_ub; i19++) {
                                        r4[i19] = ctx->u_vec[i19];
                                    }

                                    if (ctx->cfg.NHorz > static_cast<int>(nopt)) {
                                        f_ctx = static_cast<int>(nopt);
                                    } else {
                                        f_ctx = ctx->cfg.NHorz;
                                    }

                                    FeedratePlanning_v4(ctx, OptSegment, dv2, dv3, r, r1, r2, r3,
                                                        ctx->Bl.handle, r4, f_ctx, Coeff, &unusedU0,
                                                        &b_success);
                                    success = b_success;
                                    if ((!b_success) && ctx->zero_start) {
                                        //  1 -> stdout
                                        //  2 -> stderr
                                        if ((static_cast<unsigned long>(std::round(DebugConfig)) &
                                                16UL) != 0UL) {
                                            printf("ZeroStart at k = %d failed, halving jerk\n",
                                                   ctx->k0 - 1);
                                            fflush(stdout);
                                        }

                                        ctx->q_split.get((ctx->k0 - 1), (&expl_temp));
                                        t0_P0[0] = expl_temp.P0[0];
                                        t0_P1[0] = expl_temp.P1[0];
                                        t0_evec[0] = expl_temp.evec[0];
                                        t0_P0[1] = expl_temp.P0[1];
                                        t0_P1[1] = expl_temp.P1[1];
                                        t0_evec[1] = expl_temp.evec[1];
                                        t0_P0[2] = expl_temp.P0[2];
                                        t0_P1[2] = expl_temp.P1[2];
                                        t0_evec[2] = expl_temp.evec[2];
                                        for (int i20 = 0; i20 < 6; i20++) {
                                            t0_CoeffP5[i20][0] = expl_temp.CoeffP5[i20][0];
                                            t0_CoeffP5[i20][1] = expl_temp.CoeffP5[i20][1];
                                            t0_CoeffP5[i20][2] = expl_temp.CoeffP5[i20][2];
                                        }

                                        g_ctx = ctx->q_splines;
                                        CalcZeroStartConstraints(&g_ctx, expl_temp.Type, t0_P0,
                                            t0_P1, t0_evec, expl_temp.theta, expl_temp.pitch,
                                            t0_CoeffP5, expl_temp.sp_index, expl_temp.UseConstJerk,
                                            expl_temp.ConstJerk, expl_temp.a_param,
                                            expl_temp.b_param, std::pow(0.5, static_cast<double>
                                            (Retry)), &ctx->v_0, &ctx->at_0);
                                    }

                                    if ((!b_success) && ctx->zero_end) {
                                        //  1 -> stdout
                                        //  2 -> stderr
                                        if ((static_cast<unsigned long>(std::round(DebugConfig)) &
                                                16UL) != 0UL) {
                                            printf("ZeroEnd at k = %d failed, halving jerk\n", kend);
                                            fflush(stdout);
                                        }

                                        ctx->q_split.get(kend, (&expl_temp));
                                        t0_P0[0] = expl_temp.P0[0];
                                        t0_P1[0] = expl_temp.P1[0];
                                        t0_evec[0] = expl_temp.evec[0];
                                        t0_P0[1] = expl_temp.P0[1];
                                        t0_P1[1] = expl_temp.P1[1];
                                        t0_evec[1] = expl_temp.evec[1];
                                        t0_P0[2] = expl_temp.P0[2];
                                        t0_P1[2] = expl_temp.P1[2];
                                        t0_evec[2] = expl_temp.evec[2];
                                        for (int i21 = 0; i21 < 6; i21++) {
                                            t0_CoeffP5[i21][0] = expl_temp.CoeffP5[i21][0];
                                            t0_CoeffP5[i21][1] = expl_temp.CoeffP5[i21][1];
                                            t0_CoeffP5[i21][2] = expl_temp.CoeffP5[i21][2];
                                        }

                                        h_ctx = ctx->q_splines;
                                        CalcZeroStartConstraints(&h_ctx, expl_temp.Type, t0_P0,
                                            t0_P1, t0_evec, expl_temp.theta, expl_temp.pitch,
                                            t0_CoeffP5, expl_temp.sp_index, expl_temp.UseConstJerk,
                                            expl_temp.ConstJerk, expl_temp.a_param,
                                            expl_temp.b_param, std::pow(0.5, static_cast<double>
                                            (Retry)), &ctx->v_1, &b_at_0);
                                        ctx->at_1 = -b_at_0;
                                    }

                                    Retry++;
                                }

                                ctx->zero_start = false;
                                ctx->zero_end = false;
                                ctx->Coeff.set_size(Coeff.size(0), Coeff.size(1));
                                e_loop_ub = Coeff.size(1);
                                for (int i9 = 0; i9 < e_loop_ub; i9++) {
                                    int f_loop_ub;
                                    f_loop_ub = Coeff.size(0);
                                    for (int i11 = 0; i11 < f_loop_ub; i11++) {
                                        ctx->Coeff[i11 + ctx->Coeff.size(0) * i9] = Coeff[i11 +
                                            Coeff.size(0) * i9];
                                    }
                                }

                                if (!success) {
                                    int i10;
                                    i10 = ctx->cfg.NHorz;
                                    for (int nprint = 0; nprint < i10; nprint++) {
                                        if (u1 != 0UL) {
                                            b_PrintCurvStruct(&ctx->q_splines,
                                                              ctx->cfg.NGridLengthSpline,
                                                              OptSegment[0].Type, OptSegment[0].
                                                              zspdmode, OptSegment[0].P0,
                                                              OptSegment[0].P1, OptSegment[0].evec,
                                                              OptSegment[0].theta, OptSegment[0].
                                                              pitch, OptSegment[0].CoeffP5,
                                                              OptSegment[0].sp_index, OptSegment[0].
                                                              FeedRate, OptSegment[0].UseConstJerk,
                                                              OptSegment[0].ConstJerk, OptSegment[0]
                                                              .a_param, OptSegment[0].b_param);
                                        }
                                    }

                                    //  1 -> stdout
                                    //  2 -> stderr
                                    if (u1 != 0UL) {
                                        printf("OPTIMIZATION FAILED!\n");
                                        fflush(stdout);
                                    }

                                    ctx->errcode = c_FeedoptPlanError_Optimization;
                                    ctx->op = Fopt_Finished;
                                } else {
                                    guard1 = true;
                                }
                            }
                        } else {
                            int i2;
                            int i4;
                            int b_ctx;
                            int b_loop_ub;
                            int c_loop_ub;

                            //  If we have reached the end of the optimizing segment, we
                            //  can just copy out the coefficients for the whole horizon
                            if (2 > ctx->Coeff.size(1)) {
                                i2 = 0;
                                i4 = 0;
                            } else {
                                i2 = 1;
                                i4 = ctx->Coeff.size(1);
                            }

                            b_ctx = ctx->Coeff.size(0) - 1;
                            b_loop_ub = i4 - i2;
                            c_ctx.set_size((b_ctx + 1), b_loop_ub);
                            for (int i5 = 0; i5 < b_loop_ub; i5++) {
                                for (int i6 = 0; i6 <= b_ctx; i6++) {
                                    c_ctx[i6 + c_ctx.size(0) * i5] = ctx->Coeff[i6 + ctx->Coeff.size
                                        (0) * (i2 + i5)];
                                }
                            }

                            c_loop_ub = c_ctx.size(1);
                            for (int i7 = 0; i7 < c_loop_ub; i7++) {
                                int d_loop_ub;
                                d_loop_ub = c_ctx.size(0);
                                for (int i8 = 0; i8 < d_loop_ub; i8++) {
                                    ctx->Coeff[i8 + ctx->Coeff.size(0) * i7] = c_ctx[i8 + c_ctx.size
                                        (0) * i7];
                                }
                            }

                            guard1 = true;
                        }
                    } else {
                        ctx->op = Fopt_Finished;
                    }
                }
            }
            break;

          case Fopt_Finished:
            ctx->op = Fopt_Finished;
            break;

          default:
            //  1 -> stdout
            //  2 -> stderr
            if ((static_cast<unsigned long>(std::round(DebugConfig)) & 8UL) != 0UL) {
                printf("FEEDOPT: WRONG STATE\n");
                fflush(stdout);
            }

            ctx->op = Fopt_Finished;
            break;
        }

        if (guard1) {
            int loop_ub;
            b_optimized = true;
            ctx->q_split.get((ctx->n_optimized + 1), opt_struct);
            loop_ub = ctx->Coeff.size(0);
            opt_struct->Coeff.set_size(loop_ub);
            for (int i1 = 0; i1 < loop_ub; i1++) {
                opt_struct->Coeff[i1] = ctx->Coeff[i1];
            }

            if (opt_struct->zspdmode == ZSpdMode_NZ) {
                ctx->reached_end = false;
            }
        }

        *optimized = b_optimized;
    }

    //
    // ctx is the context variable, it should contain:
    //  - op: Operation to execute
    //  - go_next: Should we optimize the next segment
    //  - q_gcode: GCode queue
    //  - q_smooth: Queue for smoothed segments
    //  - q_split: Queue after splitting
    //  - q_opt: Queue after optimization
    // Arguments    : const FeedoptConfig cfg
    //                FeedoptContext *ctx
    // Return Type  : void
    //
    void InitFeedoptPlan(const FeedoptConfig cfg, FeedoptContext *ctx)
    {
        coder::array<double, 2U> r;
        coder::array<double, 2U> y;
        int i;
        int Bl_ncoeff;
        coder::array<double, 2U> breakpoints;
        coder::array<double, 2U> x;
        unsigned long Bl_handle;
        coder::array<double, 2U> Bl_breakpoints;
        int i5;
        int Bl_degree;
        int e_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int i7;
        int i8;
        coder::array<double, 2U> u_vec;
        int h_loop_ub;
        int d_scalarLB;
        int d_vectorUB;
        int i10;
        coder::array<double, 2U> BasisVal;
        coder::array<double, 2U> BasisValD;
        coder::array<double, 2U> BasisValDD;
        coder::array<double, 2U> unusedU0;
        double dv[3];
        double dv1[3];
        CurvStruct Curv;
        int m_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        int q_loop_ub;
        int s_loop_ub;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        if (cfg.UseLinearBreakpoints) {
            int n1;
            int b_loop_ub;
            int d_loop_ub;
            n1 = cfg.NBreak;
            if (cfg.NBreak < 0) {
                n1 = 0;
            }

            y.set_size(1, n1);
            if (n1 >= 1) {
                y[n1 - 1] = 1.0;
                if (y.size(1) >= 2) {
                    y[0] = 0.0;
                    if (y.size(1) >= 3) {
                        double delta1;
                        int i3;
                        delta1 = 1.0 / (static_cast<double>(y.size(1)) - 1.0);
                        i3 = y.size(1);
                        for (int b_k = 0; b_k <= i3 - 3; b_k++) {
                            y[b_k + 1] = (static_cast<double>(b_k) + 1.0) * delta1;
                        }
                    }
                }
            }

            Bl_ncoeff = (y.size(1) + cfg.SplineDegree) - 2;
            breakpoints.set_size(1, y.size(1));
            b_loop_ub = y.size(1);
            for (int i2 = 0; i2 < b_loop_ub; i2++) {
                breakpoints[i2] = y[i2];
            }

            c_bspline_create_with_breakpoints(&Bl_handle, cfg.SplineDegree, &breakpoints[0], y.size
                (1));
            Bl_breakpoints.set_size(1, y.size(1));
            d_loop_ub = y.size(1);
            for (int i4 = 0; i4 < d_loop_ub; i4++) {
                Bl_breakpoints[i4] = y[i4];
            }

            Bl_degree = cfg.SplineDegree;
        } else {
            int loop_ub;
            int scalarLB;
            int vectorUB;
            int i1;
            int c_loop_ub;
            int b_scalarLB;
            int b_vectorUB;
            int f_loop_ub;
            int g_loop_ub;
            b_linspace(cfg.NBreak, r);
            y.set_size(1, r.size(1));
            loop_ub = r.size(1);
            scalarLB = r.size(1) & -4;
            vectorUB = scalarLB - 4;
            for (i = 0; i <= vectorUB; i += 4) {
                __m256d r1;
                r1 = _mm256_loadu_pd(&r[i]);
                _mm256_storeu_pd(&y[i], _mm256_mul_pd(_mm256_set1_pd(3.1415926535897931), r1));
            }

            for (i = scalarLB; i < loop_ub; i++) {
                y[i] = 3.1415926535897931 * r[i];
            }

            i1 = y.size(1);
            for (int k = 0; k < i1; k++) {
                y[k] = std::cos(y[k]);
            }

            x.set_size(1, y.size(1));
            c_loop_ub = y.size(1);
            b_scalarLB = y.size(1) & -4;
            b_vectorUB = b_scalarLB - 4;
            for (i5 = 0; i5 <= b_vectorUB; i5 += 4) {
                __m256d r2;
                __m256d r3;
                r2 = _mm256_loadu_pd(&y[i5]);
                r3 = _mm256_set1_pd(0.5);
                _mm256_storeu_pd(&x[i5], _mm256_add_pd(_mm256_mul_pd(r2, r3), r3));
            }

            for (i5 = b_scalarLB; i5 < c_loop_ub; i5++) {
                x[i5] = y[i5] * 0.5 + 0.5;
            }

            Bl_ncoeff = (x.size(1) + cfg.SplineDegree) - 2;
            breakpoints.set_size(1, x.size(1));
            f_loop_ub = x.size(1);
            for (int i6 = 0; i6 < f_loop_ub; i6++) {
                breakpoints[i6] = x[i6];
            }

            c_bspline_create_with_breakpoints(&Bl_handle, cfg.SplineDegree, &breakpoints[0], x.size
                (1));
            Bl_breakpoints.set_size(1, x.size(1));
            g_loop_ub = x.size(1);
            for (int i9 = 0; i9 < g_loop_ub; i9++) {
                Bl_breakpoints[i9] = x[i9];
            }

            Bl_degree = cfg.SplineDegree;
        }

        b_linspace(cfg.NDiscr, r);
        y.set_size(1, r.size(1));
        e_loop_ub = r.size(1);
        c_scalarLB = r.size(1) & -4;
        c_vectorUB = c_scalarLB - 4;
        for (i7 = 0; i7 <= c_vectorUB; i7 += 4) {
            __m256d r4;
            r4 = _mm256_loadu_pd(&r[i7]);
            _mm256_storeu_pd(&y[i7], _mm256_mul_pd(_mm256_set1_pd(3.1415926535897931), r4));
        }

        for (i7 = c_scalarLB; i7 < e_loop_ub; i7++) {
            y[i7] = 3.1415926535897931 * r[i7];
        }

        i8 = y.size(1);
        for (int c_k = 0; c_k < i8; c_k++) {
            y[c_k] = std::cos(y[c_k]);
        }

        u_vec.set_size(1, y.size(1));
        h_loop_ub = y.size(1);
        d_scalarLB = y.size(1) & -4;
        d_vectorUB = d_scalarLB - 4;
        for (i10 = 0; i10 <= d_vectorUB; i10 += 4) {
            __m256d r5;
            __m256d r6;
            r5 = _mm256_loadu_pd(&y[i10]);
            r6 = _mm256_set1_pd(0.5);
            _mm256_storeu_pd(&u_vec[i10], _mm256_add_pd(_mm256_mul_pd(r5, r6), r6));
        }

        for (i10 = d_scalarLB; i10 < h_loop_ub; i10++) {
            u_vec[i10] = y[i10] * 0.5 + 0.5;
        }

        //  n, bspline_n
        BasisVal.set_size(u_vec.size(1), Bl_ncoeff);
        BasisValD.set_size(u_vec.size(1), Bl_ncoeff);
        BasisValDD.set_size(u_vec.size(1), Bl_ncoeff);
        unusedU0.set_size(u_vec.size(1), Bl_ncoeff);
        ctx->BasisIntegr.set_size(Bl_ncoeff);
        for (int i11 = 0; i11 < Bl_ncoeff; i11++) {
            int i_loop_ub;
            int j_loop_ub;
            int k_loop_ub;
            int l_loop_ub;
            i_loop_ub = u_vec.size(1);
            for (int i12 = 0; i12 < i_loop_ub; i12++) {
                BasisVal[i12 + BasisVal.size(0) * i11] = 0.0;
            }

            j_loop_ub = u_vec.size(1);
            for (int i13 = 0; i13 < j_loop_ub; i13++) {
                BasisValD[i13 + BasisValD.size(0) * i11] = 0.0;
            }

            k_loop_ub = u_vec.size(1);
            for (int i14 = 0; i14 < k_loop_ub; i14++) {
                BasisValDD[i14 + BasisValDD.size(0) * i11] = 0.0;
            }

            l_loop_ub = u_vec.size(1);
            for (int i15 = 0; i15 < l_loop_ub; i15++) {
                unusedU0[i15 + unusedU0.size(0) * i11] = 0.0;
            }

            ctx->BasisIntegr[i11] = 0.0;
        }

        // ,
        c_bspline_base_eval(&Bl_handle, u_vec.size(1), &u_vec[0], &BasisVal[0], &BasisValD[0],
                            &BasisValDD[0], &unusedU0[0], &(ctx->BasisIntegr.data())[0]);
        dv[0] = 0.0;
        dv1[0] = 0.0;
        dv[1] = 0.0;
        dv1[1] = 0.0;
        dv[2] = 0.0;
        dv1[2] = 0.0;
        ConstrLineStruct(dv, dv1, 1.0, ZSpdMode_NN, &Curv);

        //      Spline = CalcBspline_Lee(cfg, [[0,0,0]', [1,1,1]']);
        ctx->op = Fopt_Init;
        ctx->go_next = false;
        ctx->q_gcode.init((&Curv));
        ctx->q_compress.init((&Curv));
        ctx->q_splines.init((&Curv));
        ctx->q_smooth.init((&Curv));
        ctx->q_split.init((&Curv));
        ctx->q_opt.init((&Curv));
        ctx->try_push_again = false;
        ctx->n_optimized = 0;
        ctx->reached_end = false;
        ctx->k0 = 1;
        ctx->v_0 = cfg.v_0;
        ctx->v_1 = cfg.v_1;
        ctx->at_0 = cfg.at_0;
        ctx->at_1 = cfg.at_1;
        ctx->cfg = cfg;
        ctx->Bl.ncoeff = Bl_ncoeff;
        ctx->Bl.breakpoints.set_size(1, Bl_breakpoints.size(1));
        m_loop_ub = Bl_breakpoints.size(1);
        for (int i16 = 0; i16 < m_loop_ub; i16++) {
            ctx->Bl.breakpoints[i16] = Bl_breakpoints[i16];
        }

        ctx->Bl.handle = Bl_handle;
        ctx->Bl.degree = Bl_degree;
        ctx->u_vec.set_size(1, u_vec.size(1));
        n_loop_ub = u_vec.size(1);
        for (int i17 = 0; i17 < n_loop_ub; i17++) {
            ctx->u_vec[i17] = u_vec[i17];
        }

        ctx->errcode = FeedoptPlanError_Success;
        ctx->jmax_increase_count = 0;
        ctx->zero_start = false;
        ctx->zero_end = false;
        ctx->BasisVal.set_size(BasisVal.size(0), BasisVal.size(1));
        o_loop_ub = BasisVal.size(1);
        for (int i18 = 0; i18 < o_loop_ub; i18++) {
            int p_loop_ub;
            p_loop_ub = BasisVal.size(0);
            for (int i19 = 0; i19 < p_loop_ub; i19++) {
                ctx->BasisVal[i19 + ctx->BasisVal.size(0) * i18] = BasisVal[i19 + BasisVal.size(0) *
                    i18];
            }
        }

        ctx->BasisValD.set_size(BasisValD.size(0), BasisValD.size(1));
        q_loop_ub = BasisValD.size(1);
        for (int i20 = 0; i20 < q_loop_ub; i20++) {
            int r_loop_ub;
            r_loop_ub = BasisValD.size(0);
            for (int i21 = 0; i21 < r_loop_ub; i21++) {
                ctx->BasisValD[i21 + ctx->BasisValD.size(0) * i20] = BasisValD[i21 + BasisValD.size
                    (0) * i20];
            }
        }

        ctx->BasisValDD.set_size(BasisValDD.size(0), BasisValDD.size(1));
        s_loop_ub = BasisValDD.size(1);
        for (int i22 = 0; i22 < s_loop_ub; i22++) {
            int t_loop_ub;
            t_loop_ub = BasisValDD.size(0);
            for (int i23 = 0; i23 < t_loop_ub; i23++) {
                ctx->BasisValDD[i23 + ctx->BasisValDD.size(0) * i22] = BasisValDD[i23 +
                    BasisValDD.size(0) * i22];
            }
        }

        ctx->Coeff.set_size(0, 0);
        ctx->Skipped = 0;

        //  Push the dummy spline curv
        ctx->q_splines.push((&Curv));
    }

    //
    // Arguments    : const FeedoptContext *ctx
    //                const CurvStruct *S
    // Return Type  : void
    //
    void PrintCurvStruct(const FeedoptContext *ctx, const CurvStruct *S)
    {
        int varargin_1_size_idx_1;
        char varargin_1_data[9];
        static const char b_cv[5] = { 'H', 'e', 'l', 'i', 'x' };

        static const char b_cv1[7] = { 'T', 'r', 'a', 'n', 's', 'P', '5' };

        static const char b_cv2[6] = { 'S', 'p', 'l', 'i', 'n', 'e' };

        int c_validatedHoleFilling_f2_size_;
        char validatedHoleFilling_f2_data[10];
        char varargin_2_data[10];
        double P0[3];
        double P1[3];
        double validatedHoleFilling_f2;
        double dv[3][6];
        rtString formatSpec;
        char argC_data[9];
        int argC_size[2];
        cell_wrap_9 validatedHoleFilling[1];
        int loop_ub;
        int b_loop_ub;
        char b_varargin_1_data[10];
        double validatedHoleFilling_idx_0;
        double b_validatedHoleFilling_idx_0;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        printf("--------- CURVE STRUCT ---------\n");
        fflush(stdout);
        switch (S->Type) {
          case CurveType_Line:
            varargin_1_size_idx_1 = 4;
            varargin_1_data[0] = 'L';
            varargin_1_data[1] = 'i';
            varargin_1_data[2] = 'n';
            varargin_1_data[3] = 'e';
            break;

          case CurveType_Helix:
            varargin_1_size_idx_1 = 5;
            for (int i1 = 0; i1 < 5; i1++) {
                varargin_1_data[i1] = b_cv[i1];
            }
            break;

          case CurveType_TransP5:
            varargin_1_size_idx_1 = 7;
            for (int i2 = 0; i2 < 7; i2++) {
                varargin_1_data[i2] = b_cv1[i2];
            }
            break;

          case CurveType_Spline:
            varargin_1_size_idx_1 = 6;
            for (int i3 = 0; i3 < 6; i3++) {
                varargin_1_data[i3] = b_cv2[i3];
            }
            break;

          default:
            varargin_1_size_idx_1 = 9;
            for (int i = 0; i < 9; i++) {
                varargin_1_data[i] = cv2[i];
            }
            break;
        }

        c_validatedHoleFilling_f2_size_ = varargin_1_size_idx_1 + 1;
        if (0 <= varargin_1_size_idx_1 - 1) {
            std::memcpy(&validatedHoleFilling_f2_data[0], &varargin_1_data[0], varargin_1_size_idx_1
                        * sizeof(char));
        }

        validatedHoleFilling_f2_data[varargin_1_size_idx_1] = '\x00';
        if (0 <= c_validatedHoleFilling_f2_size_ - 1) {
            std::memcpy(&varargin_2_data[0], &validatedHoleFilling_f2_data[0],
                        c_validatedHoleFilling_f2_size_ * sizeof(char));
        }

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
            for (int i4 = 0; i4 < 3; i4++) {
                for (int i5 = 0; i5 < 6; i5++) {
                    dv[i4][i5] = S->CoeffP5[i5][i4];
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

        b_EvalCurvStruct(&ctx->q_splines, S->Type, S->P0, S->P1, S->evec, S->theta, S->pitch,
                         S->CoeffP5, S->sp_index, S->b_param, P0);
        c_EvalCurvStruct(&ctx->q_splines, S->Type, S->P0, S->P1, S->evec, S->theta, S->pitch,
                         S->CoeffP5, S->sp_index, S->a_param, S->b_param, P1);
        printf("%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n", "P", P0[0], P0[1], P0[2], P1[0], P1[1],
               P1[2]);
        fflush(stdout);
        validatedHoleFilling_f2 = LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, S->Type,
            S->P0, S->P1, S->evec, S->theta, S->pitch, S->CoeffP5, S->sp_index, S->a_param,
            S->b_param);
        printf("%10s: %e\n", "Length", validatedHoleFilling_f2);
        fflush(stdout);
        switch (S->zspdmode) {
          case ZSpdMode_NN:
            formatSpec.init();
            break;

          case ZSpdMode_ZN:
            formatSpec.b_init();
            break;

          case ZSpdMode_NZ:
            formatSpec.c_init();
            break;

          default:
            formatSpec.d_init();
            break;
        }

        formatSpec.uncheckedChar(argC_data, argC_size);
        validatedHoleFilling[0].f1.size[1] = argC_size[1] + 1;
        loop_ub = argC_size[1];
        for (int i6 = 0; i6 < loop_ub; i6++) {
            validatedHoleFilling[0].f1.data[i6] = argC_data[i6];
        }

        validatedHoleFilling[0].f1.data[argC_size[1]] = '\x00';
        b_loop_ub = validatedHoleFilling[0].f1.size[1];
        for (int i7 = 0; i7 < b_loop_ub; i7++) {
            b_varargin_1_data[i7] = validatedHoleFilling[0].f1.data[i7];
        }

        printf("ZSpdMode: %s\n", &b_varargin_1_data[0]);
        fflush(stdout);
        printf("FeedRate: %.2f\n", S->FeedRate);
        fflush(stdout);
        if (S->UseConstJerk) {
            CalcZeroStartConstraints(&ctx->q_splines, S->Type, S->P0, S->P1, S->evec, S->theta,
                S->pitch, S->CoeffP5, S->sp_index, S->UseConstJerk, S->ConstJerk, S->a_param,
                S->b_param, 1.0, &validatedHoleFilling_idx_0, &b_validatedHoleFilling_idx_0);
            printf("ConstJerk: %e\n", S->ConstJerk);
            fflush(stdout);
            printf("v_0      : %f\n", validatedHoleFilling_idx_0);
            fflush(stdout);
            printf("at_0     : %f\n", b_validatedHoleFilling_idx_0);
            fflush(stdout);
        }
    }

    //
    // Arguments    : ResampleStateClass *state
    //                const SplineBase *Bl
    //                const CurvStruct *Curv
    // Return Type  : void
    //
    void ResampleNoCtx(ResampleStateClass *state, const SplineBase *Bl, const CurvStruct *Curv)
    {
        double ukp1;
        double qk;
        double unusedU0;
        double b_ukp1;
        double unusedU1;
        double x;
        double unusedU2;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        Resample(Curv->zspdmode, Curv->UseConstJerk, Curv->ConstJerk, Curv->Coeff, Bl->handle,
                 state->u, state->dt, &ukp1, &qk, &unusedU0);
        b_ukp1 = ukp1;
        if (ukp1 < state->u) {
            b_ukp1 = 1.0;
        }

        if (b_ukp1 - state->u < 2.2204460492503131E-16) {
            b_ukp1 = state->u + 2.2204460492503131E-16;
        }

        if (b_ukp1 < 1.0) {
            state->set_u(b_ukp1);
        } else {
            double Trest;
            double dt_begin;
            Resample(Curv->zspdmode, Curv->UseConstJerk, Curv->ConstJerk, Curv->Coeff, Bl->handle,
                     1.0, state->dt, &unusedU1, &x, &unusedU2);
            x = std::sqrt(x);
            Trest = 2.0 * (1.0 - state->u) / (x + std::sqrt(qk));
            if (Trest > state->dt) {
                dt_begin = 0.0;
            } else {
                dt_begin = state->dt - Trest;
            }

            state->set_u();
            state->b_set_go_next();
            state->set_dt(dt_begin);

            //  This recursive call was replaced by the 'again' output params
            //  Callers should make sure to use them
            //     ctx = ResampleTick(ctx, dt_begin);
        }
    }

    //
    // Arguments    : double dt
    //                ResampleStateClass *state
    // Return Type  : void
    //
    void ResampleState(double dt, ResampleStateClass *state)
    {
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        state->init(dt);
    }

    //
    // Arguments    : const SplineBase *Bl
    //                SplineBase *Copy
    // Return Type  : void
    //
    void bspline_copy(const SplineBase *Bl, SplineBase *Copy)
    {
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        b_bspline_create(Bl->degree, Bl->breakpoints, &Copy->ncoeff, Copy->breakpoints,
                         &Copy->handle, &Copy->degree);
    }

    //
    // Arguments    : int degree
    //                const double breakpoints[10]
    //                SplineBase *Bl
    // Return Type  : void
    //
    void bspline_create(int degree, const double breakpoints[10], SplineBase *Bl)
    {
        double b_breakpoints[10];
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        Bl->ncoeff = degree + 8;
        std::memcpy(&b_breakpoints[0], &breakpoints[0], 10U * sizeof(double));
        c_bspline_create_with_breakpoints(&Bl->handle, degree, &b_breakpoints[0], 10);
        Bl->breakpoints.set_size(1, 10);
        for (int i = 0; i < 10; i++) {
            Bl->breakpoints[i] = breakpoints[i];
        }

        Bl->degree = degree;
    }

    //
    // Arguments    : const double coeffs_data[]
    //                const int coeffs_size[2]
    //                creal_T Y_data[]
    //                int Y_size[1]
    // Return Type  : void
    //
    void c_roots_(const double coeffs_data[], const int coeffs_size[2], creal_T Y_data[], int
                  Y_size[1])
    {
        int loop_ub;
        int i;
        int i1;
        int i2;
        int b_loop_ub;
        double tmp_data[13];
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        Y_size[0] = coeffs_size[1] - 1;
        loop_ub = coeffs_size[1] - 1;
        if (0 <= loop_ub - 1) {
            std::memset(&Y_data[0], 0, loop_ub * sizeof(creal_T));
        }

        if (1 > coeffs_size[1]) {
            i = 0;
            i1 = 1;
            i2 = -1;
        } else {
            i = coeffs_size[1] - 1;
            i1 = -1;
            i2 = 0;
        }

        b_loop_ub = div_s32_floor(i2 - i, i1);
        for (int i3 = 0; i3 <= b_loop_ub; i3++) {
            tmp_data[i3] = coeffs_data[i + i1 * i3];
        }

        c_roots(&tmp_data[0], &Y_data[0], coeffs_size[1]);
    }

    //
    // Arguments    : double d1
    //                double d2
    //                double n1
    //                coder::array<double, 2U> *y
    // Return Type  : void
    //
    void linspace(double d1, double d2, double n1, coder::array<double, 2U> &y)
    {
        int i;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        if (n1 < 0.0) {
            n1 = 0.0;
        }

        i = static_cast<int>(std::floor(n1));
        y.set_size(1, i);
        if (i >= 1) {
            int y_tmp;
            y_tmp = i - 1;
            y[y_tmp] = d2;
            if (y.size(1) >= 2) {
                y[0] = d1;
                if (y.size(1) >= 3) {
                    if ((d1 == -d2) && (i > 2)) {
                        for (int k = 2; k <= y_tmp; k++) {
                            y[k - 1] = d2 * (static_cast<double>(((k << 1) - i) - 1) / (static_cast<
                                              double>(i) - 1.0));
                        }

                        if ((i & 1) == 1) {
                            y[i >> 1] = 0.0;
                        }
                    } else if (((d1 < 0.0) != (d2 < 0.0)) && ((std::abs(d1) >
                                 8.9884656743115785E+307) || (std::abs(d2) > 8.9884656743115785E+307)))
                    {
                        double delta1;
                        double delta2;
                        int i2;
                        delta1 = d1 / (static_cast<double>(y.size(1)) - 1.0);
                        delta2 = d2 / (static_cast<double>(y.size(1)) - 1.0);
                        i2 = y.size(1);
                        for (int c_k = 0; c_k <= i2 - 3; c_k++) {
                            y[c_k + 1] = (d1 + delta2 * (static_cast<double>(c_k) + 1.0)) - delta1 *
                                (static_cast<double>(c_k) + 1.0);
                        }
                    } else {
                        double delta1;
                        int i1;
                        delta1 = (d2 - d1) / (static_cast<double>(y.size(1)) - 1.0);
                        i1 = y.size(1);
                        for (int b_k = 0; b_k <= i1 - 3; b_k++) {
                            y[b_k + 1] = d1 + (static_cast<double>(b_k) + 1.0) * delta1;
                        }
                    }
                }
            }
        }
    }

    //
    // Arguments    : double x0
    //                double x1
    //                int N
    //                coder::array<double, 2U> *x
    // Return Type  : void
    //
    void sinspace(double x0, double x1, int N, coder::array<double, 2U> &x)
    {
        coder::array<double, 2U> r;
        coder::array<double, 2U> y;
        int loop_ub;
        int scalarLB;
        int vectorUB;
        int i;
        int i1;
        double b;
        int b_loop_ub;
        int b_scalarLB;
        int b_vectorUB;
        int i2;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        b_linspace(N, r);
        y.set_size(1, r.size(1));
        loop_ub = r.size(1);
        scalarLB = r.size(1) & -4;
        vectorUB = scalarLB - 4;
        for (i = 0; i <= vectorUB; i += 4) {
            __m256d r1;
            r1 = _mm256_loadu_pd(&r[i]);
            _mm256_storeu_pd(&y[i], _mm256_mul_pd(_mm256_set1_pd(3.1415926535897931), r1));
        }

        for (i = scalarLB; i < loop_ub; i++) {
            y[i] = 3.1415926535897931 * r[i];
        }

        i1 = y.size(1);
        for (int k = 0; k < i1; k++) {
            y[k] = std::cos(y[k]);
        }

        b = x1 - x0;
        x.set_size(1, y.size(1));
        b_loop_ub = y.size(1);
        b_scalarLB = y.size(1) & -4;
        b_vectorUB = b_scalarLB - 4;
        for (i2 = 0; i2 <= b_vectorUB; i2 += 4) {
            __m256d r2;
            __m256d r3;
            r2 = _mm256_loadu_pd(&y[i2]);
            r3 = _mm256_set1_pd(0.5);
            _mm256_storeu_pd(&x[i2], _mm256_add_pd(_mm256_mul_pd(_mm256_add_pd(_mm256_mul_pd(r2, r3),
                                r3), _mm256_set1_pd(b)), _mm256_set1_pd(x0)));
        }

        for (i2 = b_scalarLB; i2 < b_loop_ub; i2++) {
            x[i2] = (y[i2] * 0.5 + 0.5) * b + x0;
        }
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void sinspace_initialize()
    {
        DebugConfig = 0.0;
        isInitialized_sinspace = true;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    void sinspace_terminate()
    {
        // (no terminate code required)
        isInitialized_sinspace = false;
    }
}

//
// File trailer for sinspace.cpp
//
// [EOF]
//
