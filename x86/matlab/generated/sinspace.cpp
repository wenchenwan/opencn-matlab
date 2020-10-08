//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sinspace.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 08-Oct-2020 13:35:40
//

// Include Files
#include "sinspace.h"
#include "sinspace_types.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"
#include "cpp_simplex.hpp"
#include "functions.h"
#include "src/c_spline.h"
#include <cfloat>
#include <cmath>
#include <cstring>
#include <emmintrin.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

// Type Definitions
namespace ocn
{
    namespace coder
    {
        class rtString
        {
          public:
            void init();
            void b_init();
            void c_init();
            void d_init();
            void uncheckedChar(char result_data[], int result_size[2]) const;
          private:
            ::coder::bounded_array<char, 9U, 2U> Value;
        };

        class sparse
        {
          public:
            void init(double ridx, double cidx);
            int nnzInt() const;
            void vertcat(const ::coder::array<double, 2U> &varargin_2, sparse *c) const;
            bool isempty() const;
            static void spallocLike(int b_m, int b_n, int nzmax, sparse *s);
            void init(int b_m, int b_n, int nzmaxval);
            void vertcat(const sparse *varargin_2, sparse *c) const;
            void parenAssign(const ::coder::array<double, 2U> &rhs, const ::coder::array<double, 2U>
                             &varargin_1, const ::coder::array<double, 2U> &varargin_2);
            void parenAssign2D(const ::coder::array<double, 2U> &rhs, const ::coder::array<double,
                               2U> &r, const ::coder::array<double, 2U> &c);
            ::coder::array<double, 1U> d;
            ::coder::array<int, 1U> colidx;
            ::coder::array<int, 1U> rowidx;
            int m;
            int n;
            int maxnz;
        };
    }
}

// Variable Definitions
namespace ocn
{
    double sqrt_calls;
    double cos_calls;
    double sin_calls;
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
    static void BuildConstrJerk_v4(const queue_coder *ctx_q_splines, const ::coder::array<CurvStruct,
        2U> &CurvStructs, const ::coder::array<double, 2U> &Coeff, const double jmax[3], const ::
        coder::array<double, 2U> &BasisVal, const ::coder::array<double, 2U> &BasisValD, const ::
        coder::array<double, 2U> &BasisValDD, const ::coder::array<double, 2U> &u_vec, coder::sparse
        *A, ::coder::array<double, 1U> &b);
    static void BuildConstr_v4(const queue_coder *ctx_q_splines, bool ctx_cfg_UseDynamicBreakpoints,
        bool ctx_cfg_UseLinearBreakpoints, double ctx_cfg_DynamicBreakpointsDistance, int
        ctx_cfg_SplineDegree, double ctx_cfg_NGridLengthSpline, int ctx_Bl_ncoeff, unsigned long
        ctx_Bl_handle, const ::coder::array<CurvStruct, 2U> &CurvStructs, const double amax[3],
        double v_0, double at_0, double v_1, double at_1, ::coder::array<double, 2U> &BasisVal, ::
        coder::array<double, 2U> &BasisValD, const ::coder::array<double, 2U> &u_vec, coder::sparse *
        A, ::coder::array<double, 1U> &b, ::coder::array<double, 2U> &Aeq, ::coder::array<double, 1U>
        &beq);
    static void CalcBspline_Lee(int cfg_SplineDegree, const ::coder::array<double, 2U> &points, ::
        coder::array<double, 2U> &sp3D_CoeffX, ::coder::array<double, 2U> &sp3D_CoeffY, ::coder::
        array<double, 2U> &sp3D_CoeffZ, int *sp3D_Bl_ncoeff, ::coder::array<double, 2U>
        &sp3D_Bl_breakpoints, unsigned long *sp3D_Bl_handle, int *sp3D_Bl_degree, ::coder::array<
        double, 2U> &sp3D_knots);
    static void CalcFrenet(const double rD1[3], const double rD2[3], double t[3], double n[3],
                           double *kappa);
    static void CalcZeroStartConstraints(const queue_coder *ctx_q_splines, CurveType Curv_Type,
        const double Curv_P0[3], const double Curv_P1[3], const double Curv_HelixCenter[3], const
        double Curv_evec[3], double Curv_theta, double Curv_pitch, const double Curv_CoeffP5[6][3],
        int Curv_sp_index, bool Curv_UseConstJerk, double Curv_ConstJerk, double Curv_a_param,
        double Curv_b_param, double JerkScale, double *v_0, double *at_0);
    static void Calc_beta0_beta1(double alpha0, double alpha1, const double in3[3], const double
        in4[3], const double in5[3], double kappa0, const double in7[3], const double in8[3], const
        double in9[3], double kappa1, double *beta0, double *beta1);
    static void CheckCurvStructs(const FeedoptContext *ctx);
    static void CoefPolySys(const double in1[3], const double in2[3], const double in3[3], double
                            kappa0, const double in5[3], const double in6[3], const double in7[3],
                            double kappa1, double CoefPS[16]);
    static void CompressCurvStructs(const FeedoptContext *ctx);
    static void ConstrCurvStruct(CurveType Type, ZSpdMode b_ZSpdMode, const double P0[3], const
        double P1[3], const double C[3], const double evec[3], double theta, double pitch, const
        double CoeffP5[6][3], double FeedRate, CurvStruct *CStrct);
    static void CutCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        CurvStruct *b_CurvStruct, double d1);
    static void CutZeroEnd(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int
                           ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3],
                           double ctx_cfg_dt, double ctx_cfg_ZeroStartAccLimit, double
                           ctx_cfg_ZeroStartJerkLimit, double ctx_cfg_ZeroStartVelLimit, double
                           ctx_cfg_NGridLengthSpline, const CurvStruct *b_CurvStruct, CurvStruct
                           *CurvStruct1, CurvStruct *CurvStruct2);
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
    static void EvalBSplineNoCtx(const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX, const ::
        coder::array<double, 2U> &CurvSpline_sp_CoeffY, const ::coder::array<double, 2U>
        &CurvSpline_sp_CoeffZ, unsigned long CurvSpline_sp_Bl_handle, double uvec, double r0D[3],
        double r1D[3], double r2D[3], double r3D[3]);
    static double EvalCostIntegral(double alpha0, double beta0, double alpha1, double beta1, const
        double in5[3], const double in6[3], const double in7[3], double kappa0, const double in9[3],
        const double in10[3], const double in11[3], double kappa1);
    static void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const double
                          CurvStruct_HelixCenter[3], const double CurvStruct_evec[3], double
                          CurvStruct_theta, double CurvStruct_pitch, const ::coder::array<double, 2U>
                          &u_vec, ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D, ::
                          coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D);
    static void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const double
                          CurvStruct_HelixCenter[3], const double CurvStruct_evec[3], double
                          CurvStruct_theta, double CurvStruct_pitch, double u_vec, double r0D[3],
                          double r1D[3], double r2D[3], double r3D[3]);
    static void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const double
                          CurvStruct_HelixCenter[3], const double CurvStruct_evec[3], double
                          CurvStruct_theta, double CurvStruct_pitch, const double u_vec[10], double
                          r0D[10][3], double r1D[10][3], double r2D[10][3], double r3D[10][3]);
    static void EvalLine(const double CurvStruct_P0[3], const double CurvStruct_P1[3], double u_vec,
                         double r0D[3], double r1D[3], double r2D[3], double r3D[3]);
    static void EvalLine(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const ::coder::
                         array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D, ::coder::array<
                         double, 2U> &r1D, ::coder::array<double, 2U> &r2D, ::coder::array<double,
                         2U> &r3D);
    static void EvalLine(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const double
                         u_vec[10], double r0D[10][3], double r1D[10][3], double r2D[10][3], double
                         r3D[10][3]);
    static void EvalTransP5(const double CurvStruct_CoeffP5[6][3], const ::coder::array<double, 2U>
                            &u_vec, ::coder::array<double, 2U> &r_0D, ::coder::array<double, 2U>
                            &r_1D, ::coder::array<double, 2U> &r_2D, ::coder::array<double, 2U>
                            &r_3D);
    static void EvalTransP5(const double CurvStruct_CoeffP5[6][3], double u_vec, double r_0D[3],
                            double r_1D[3], double r_2D[3], double r_3D[3]);
    static void EvalTransP5(const double CurvStruct_CoeffP5[6][3], const double u_vec[10], double
                            r_0D[10][3], double r_1D[10][3], double r_2D[10][3], double r_3D[10][3]);
    static void ExpandZeroStructs(const FeedoptContext *ctx);
    static void FeedratePlanning_v4(FeedoptContext *ctx, const ::coder::array<CurvStruct, 2U>
        &CurvStructs0, const double amax[3], double jmax[3], const ::coder::array<double, 2U>
        &BasisVal, const ::coder::array<double, 2U> &BasisValD, const ::coder::array<double, 2U>
        &BasisValDD, const ::coder::array<double, 1U> &BasisIntegr, unsigned long Bl_handle, const ::
        coder::array<double, 2U> &u_vec, int N_Hor, ::coder::array<double, 2U> &Coeff, int *NCoeff,
        bool *success);
    static void G2_Hermite_Interpolation(const double r0D0[3], const double r0D1[3], const double
        r0D2[3], const double r1D0[3], const double r1D1[3], const double r1D2[3], double p5_3D[6][3],
        int *status, double *alpha0, double *alpha1);
    static double GetCurvMaxFeedrate(const queue_coder *ctx_q_splines, const double ctx_cfg_amax[3],
        const double ctx_cfg_jmax[3], CurveType CurvStruct_Type, const double CurvStruct_P0[3],
        const double CurvStruct_P1[3], const double CurvStruct_HelixCenter[3], const double
        CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch, const double
        CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_FeedRate, double
        CurvStruct_a_param, double CurvStruct_b_param);
    static double LengthCurv(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        CurveType Curv_Type, const double Curv_P0[3], const double Curv_P1[3], const double
        Curv_HelixCenter[3], const double Curv_evec[3], double Curv_theta, double Curv_pitch, const
        double Curv_CoeffP5[6][3], int Curv_sp_index, double Curv_a_param, double Curv_b_param);
    static void Resample(ZSpdMode CurOptStruct_zspdmode, bool CurOptStruct_UseConstJerk, double
                         CurOptStruct_ConstJerk, const ::coder::array<double, 1U>
                         &CurOptStruct_Coeff, unsigned long Bl_handle, double u, double dt, double
                         *ukp1, double *qk, double *dk);
    static void SmoothCurvStructs(const FeedoptContext *ctx);
    static double SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, const double u0_tilda_data[], const int
        u0_tilda_size[2], double u1_tilda);
    static double SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, double u0_tilda, const double u1_tilda_data[],
        const int u1_tilda_size[2]);
    static double SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, double u0_tilda, double u1_tilda);
    static void SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, double u0_tilda, double u1_tilda, double *L, ::
        coder::array<double, 2U> &Integrand, ::coder::array<double, 2U> &u_mid_tilda, ::coder::array<
        double, 2U> &du_tilda);
    static void SplitCurvStructs(const FeedoptContext *ctx);
    static void b_CutCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        CurvStruct *b_CurvStruct, double d0);
    static void b_CutZeroStart(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int
        ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3], double ctx_cfg_dt,
        double ctx_cfg_ZeroStartAccLimit, double ctx_cfg_ZeroStartJerkLimit, double
        ctx_cfg_ZeroStartVelLimit, bool ctx_cfg_DebugCutZero, double ctx_cfg_NGridLengthSpline,
        const CurvStruct *b_CurvStruct, CurvStruct *CurvStruct1, CurvStruct *CurvStruct2);
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U>
        &r0D, ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D);
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, double r0D[3], double r1D[3], double r2D[3]);
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, double r0D[3]);
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U>
        &r0D, ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D, ::coder::array<
        double, 2U> &r3D);
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_b_param,
        double r0D[3]);
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, double r0D[3], double r1D[3]);
    static void b_PrintCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        const CurvStruct *S);
    static void b_bspline_create(int degree, const ::coder::array<double, 2U> &breakpoints, int
        *Bl_ncoeff, ::coder::array<double, 2U> &Bl_breakpoints, unsigned long *Bl_handle, int
        *Bl_degree);
    static void bspline_base_eval(int Bl_ncoeff, unsigned long Bl_handle, const ::coder::array<
        double, 2U> &xvec, ::coder::array<double, 2U> &BasisVal, ::coder::array<double, 2U>
        &BasisValD);
    static void bspline_eval(unsigned long Bl_handle, const ::coder::array<double, 1U> &coeffs,
        double *x, double *xd, double *xdd);
    static void bspline_eval(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
        double *x, double *xd, double *xdd, double *xddd);
    static void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
        const double u[10], double x[10], double xd[10], double xdd[10], double xddd[10]);
    static void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
        double u, double *x, double *xd, double *xdd, double *xddd);
    static void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
        const ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &x, ::coder::array<double,
        2U> &xd);
    static void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
        const ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &x, ::coder::array<double,
        2U> &xd, ::coder::array<double, 2U> &xdd, ::coder::array<double, 2U> &xddd);
    static void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, double r0D[3], double r1D[3], double r2D[3]);
    static void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, double r0D[3], double r1D[3]);
    static void c_simplex(const ::coder::array<double, 2U> &f, const coder::sparse *A, ::coder::
                          array<double, 2U> &b, const ::coder::array<double, 2U> &Aeq, const ::coder::
                          array<double, 2U> &beq, ::coder::array<double, 2U> &C, bool *success, int *
                          status);
    namespace coder
    {
        static void b_cosd(double *x);
        static void b_eml_find(const ::coder::array<bool, 2U> &x, int i_data[], int i_size[2]);
        static void b_eml_float_colon(double a, double d, ::coder::array<double, 2U> &y);
        static void b_linspace(int n, ::coder::array<double, 2U> &y);
        static double b_norm(const double x[3]);
        static void bsxfun(const ::coder::array<double, 1U> &a, const ::coder::array<double, 2U> &b,
                           ::coder::array<double, 2U> &c);
        static void bsxfun(const ::coder::array<double, 2U> &a, const ::coder::array<double, 1U> &b,
                           ::coder::array<double, 2U> &c);
        static void bsxfun(const ::coder::array<double, 2U> &a, const ::coder::array<double, 2U> &b,
                           ::coder::array<double, 2U> &c);
        static void c_eml_find(const bool x_data[], const int x_size[1], int i_data[], int i_size[1]);
        static void diff(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y);
        static void eml_find(const ::coder::array<bool, 2U> &x, int i_data[], int i_size[2]);
        static void eml_float_colon(double d, double b, ::coder::array<double, 2U> &y);
        namespace internal
        {
            namespace blas
            {
                static void mtimes(const double A[3], const ::coder::array<double, 2U> &B, ::coder::
                                   array<double, 2U> &C);
                static double xnrm2(int n, const ::coder::array<double, 2U> &x, int ix0);
            }

            static unsigned long maximum2(unsigned long x);
            static void minimum(const double x_data[], const int x_size[1], double *ex, int *idx);
            static void qrsolve(const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U>
                                &B, ::coder::array<double, 1U> &Y);
        }

        static void mldivide(const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U>
                             &B, ::coder::array<double, 1U> &Y);
        static void power(const double a_data[], const int a_size[1], double y_data[], int y_size[1]);
        static void sum(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y);
    }

    static int div_s32_floor(int numerator, int denominator);
    static double rt_hypotd(double u0, double u1);
    static double rt_remd(double u0, double u1);
}

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace ocn
{
    void ResampleStateClass::b_set_go_next()
    {
        this->go_next = true;
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    namespace coder
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
        // Arguments    : int b_m
        //                int b_n
        //                int nzmaxval
        // Return Type  : void
        //
        void sparse::init(int b_m, int b_n, int nzmaxval)
        {
            int i1;
            int numalloc;
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
        // Arguments    : double ridx
        //                double cidx
        // Return Type  : void
        //
        void sparse::init(double ridx, double cidx)
        {
            int loop_ub;
            this->m = static_cast<int>(ridx);
            this->n = static_cast<int>(cidx);
            this->d.set_size(1);
            this->d[0] = 0.0;
            this->colidx.set_size((static_cast<int>(cidx) + 1));
            loop_ub = static_cast<int>(cidx) + 1;
            for (int i = 0; i < loop_ub; i++) {
                this->colidx[i] = 1;
            }

            this->rowidx.set_size(1);
            this->rowidx[0] = 1;
            this->maxnz = 1;
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
        // Arguments    : void
        // Return Type  : bool
        //
        bool sparse::isempty() const
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
        int sparse::nnzInt() const
        {
            return this->colidx[this->colidx.size(0) - 1] - 1;
        }

        //
        // Arguments    : const ::coder::array<double, 2U> &rhs
        //                const ::coder::array<double, 2U> &varargin_1
        //                const ::coder::array<double, 2U> &varargin_2
        // Return Type  : void
        //
        void sparse::parenAssign(const ::coder::array<double, 2U> &rhs, const ::coder::array<double,
            2U> &varargin_1, const ::coder::array<double, 2U> &varargin_2)
        {
            this->parenAssign2D(rhs, varargin_1, varargin_2);
        }

        //
        // Arguments    : const ::coder::array<double, 2U> &rhs
        //                const ::coder::array<double, 2U> &r
        //                const ::coder::array<double, 2U> &c
        // Return Type  : void
        //
        void sparse::parenAssign2D(const ::coder::array<double, 2U> &rhs, const ::coder::array<
            double, 2U> &r, const ::coder::array<double, 2U> &c)
        {
            ::coder::array<double, 1U> dt;
            ::coder::array<int, 1U> rowidxt;
            int b_k;
            int k;
            int rhsIter_idx;
            int sm;
            int sn;
            sm = r.size(1);
            sn = c.size(1);
            rhsIter_idx = 0;
            for (int cidx = 0; cidx < sn; cidx++) {
                double b_d;
                b_d = c[cidx];
                for (int ridx = 0; ridx < sm; ridx++) {
                    double nt;
                    double rhsv;
                    double thisv;
                    int i;
                    int i1;
                    int vidx;
                    bool found;
                    nt = r[ridx];
                    i = this->colidx[static_cast<int>(b_d) - 1];
                    i1 = this->colidx[static_cast<int>(b_d)];
                    if (i < i1) {
                        if (static_cast<int>(nt) < this->rowidx[i - 1]) {
                            vidx = i - 1;
                            found = false;
                        } else {
                            int high_i;
                            int low_i;
                            int low_ip1;
                            high_i = i1;
                            low_i = i;
                            low_ip1 = this->colidx[static_cast<int>(b_d) - 1];
                            while (high_i > low_ip1 + 1) {
                                int mid_i;
                                mid_i = (low_i >> 1) + (high_i >> 1);
                                if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
                                    mid_i++;
                                }

                                if (static_cast<int>(nt) >= this->rowidx[mid_i - 1]) {
                                    low_i = mid_i;
                                    low_ip1 = mid_i;
                                } else {
                                    high_i = mid_i;
                                }
                            }

                            vidx = low_i;
                            found = (this->rowidx[low_i - 1] == static_cast<int>(nt));
                        }
                    } else if (i == i1) {
                        vidx = this->colidx[static_cast<int>(b_d) - 1] - 1;
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
                            int b_scalarLB;
                            int b_vectorUB;
                            int i5;
                            int i7;
                            int idx;
                            idx = vidx + 1;
                            if (n_tmp == this->maxnz) {
                                int b_loop_ub;
                                int highOrderA;
                                int highOrderB;
                                int loop_ub;
                                int lowOrderB;
                                int numAlloc;
                                int overflow;
                                int partialResults_idx_0_tmp;
                                int partialResults_idx_1;
                                int tmp;
                                rowidxt.set_size(this->rowidx.size(0));
                                loop_ub = this->rowidx.size(0);
                                for (int i4 = 0; i4 < loop_ub; i4++) {
                                    rowidxt[i4] = this->rowidx[i4];
                                }

                                dt.set_size(this->d.size(0));
                                b_loop_ub = this->d.size(0);
                                for (int i6 = 0; i6 < b_loop_ub; i6++) {
                                    dt[i6] = this->d[i6];
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
                                    int b;
                                    int y;
                                    y = this->m * this->n;
                                    if (n_tmp + 10 <= y) {
                                        b = n_tmp + 10;
                                    } else {
                                        b = y;
                                    }

                                    if (1 >= b) {
                                        numAlloc = 1;
                                    } else {
                                        numAlloc = b;
                                    }
                                } else if (1 >= n_tmp + 10) {
                                    numAlloc = 1;
                                } else {
                                    numAlloc = n_tmp + 10;
                                }

                                this->rowidx.set_size(numAlloc);
                                for (int i8 = 0; i8 < numAlloc; i8++) {
                                    this->rowidx[i8] = 0;
                                }

                                this->d.set_size(numAlloc);
                                for (int i9 = 0; i9 < numAlloc; i9++) {
                                    this->d[i9] = 0.0;
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
                                    std::memmove((void *)&this->rowidx[vidx + 1], (void *)
                                                 &this->rowidx[vidx], (unsigned int)((size_t)b_nelem
                                                  * sizeof(int)));
                                    std::memmove((void *)&this->d[vidx + 1], (void *)&this->d[vidx],
                                                 (unsigned int)((size_t)b_nelem * sizeof(double)));
                                }

                                this->d[vidx] = rhsv;
                                this->rowidx[vidx] = static_cast<int>(nt);
                            }

                            i5 = static_cast<int>(b_d) + 1;
                            i7 = this->n + 1;
                            b_scalarLB = (((i7 - static_cast<int>(b_d)) & -4) + static_cast<int>(b_d))
                                + 1;
                            b_vectorUB = b_scalarLB - 4;
                            for (b_k = i5; b_k <= b_vectorUB; b_k += 4) {
                                __m128i r1;
                                r1 = _mm_loadu_si128((__m128i *)&this->colidx[b_k - 1]);
                                _mm_storeu_si128((__m128i *)&this->colidx[b_k - 1], _mm_add_epi32(r1,
                                                  _mm_set1_epi32(1)));
                            }

                            for (b_k = b_scalarLB; b_k <= i7; b_k++) {
                                this->colidx[b_k - 1] = this->colidx[b_k - 1] + 1;
                            }
                        } else {
                            int i2;
                            int i3;
                            int nelem;
                            int scalarLB;
                            int vectorUB;
                            nelem = n_tmp - vidx;
                            if (nelem > 0) {
                                std::memmove((void *)&this->rowidx[vidx - 1], (void *)&this->
                                             rowidx[vidx], (unsigned int)((size_t)nelem * sizeof(int)));
                                std::memmove((void *)&this->d[vidx - 1], (void *)&this->d[vidx],
                                             (unsigned int)((size_t)nelem * sizeof(double)));
                            }

                            i2 = static_cast<int>(b_d) + 1;
                            i3 = this->n + 1;
                            scalarLB = (((i3 - static_cast<int>(b_d)) & -4) + static_cast<int>(b_d))
                                + 1;
                            vectorUB = scalarLB - 4;
                            for (k = i2; k <= vectorUB; k += 4) {
                                __m128i b_r;
                                b_r = _mm_loadu_si128((__m128i *)&this->colidx[k - 1]);
                                _mm_storeu_si128((__m128i *)&this->colidx[k - 1], _mm_sub_epi32(b_r,
                                                  _mm_set1_epi32(1)));
                            }

                            for (k = scalarLB; k <= i3; k++) {
                                this->colidx[k - 1] = this->colidx[k - 1] - 1;
                            }
                        }
                    }
                }
            }
        }

        //
        // Arguments    : int b_m
        //                int b_n
        //                int nzmax
        //                sparse *s
        // Return Type  : void
        //
        void sparse::spallocLike(int b_m, int b_n, int nzmax, sparse *s)
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
            rtString localCopyOfThis;
            int loop_ub;
            localCopyOfThis = *this;
            result_size[0] = 1;
            result_size[1] = localCopyOfThis.Value.size[1];
            loop_ub = localCopyOfThis.Value.size[1];
            if (0 <= loop_ub - 1) {
                std::memcpy(&result_data[0], &localCopyOfThis.Value.data[0], loop_ub * sizeof(char));
            }
        }

        //
        // Arguments    : const ::coder::array<double, 2U> &varargin_2
        //                sparse *c
        // Return Type  : void
        //
        void sparse::vertcat(const ::coder::array<double, 2U> &varargin_2, sparse *c) const
        {
            int cnfixeddim;
            int cnnz;
            int cnvardim;
            int i1;
            int nzCount;
            bool allEmpty;
            bool emptyflag_idx_1;
            bool isAcceptableEmpty;
            bool isAcceptableEmpty_tmp_tmp;
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

            sparse::spallocLike((cnvardim), (cnfixeddim), (cnnz), (c));
            nzCount = -1;
            emptyflag_idx_1 = (varargin_2.size(1) == 0);
            i1 = c->n;
            for (int ccol = 0; ccol < i1; ccol++) {
                int cidx;
                int crowoffs;
                crowoffs = 1;
                if (!isAcceptableEmpty_tmp_tmp) {
                    int kpend;
                    int kpend_tmp;
                    int kpstart;
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
        // Arguments    : const sparse *varargin_2
        //                sparse *c
        // Return Type  : void
        //
        void sparse::vertcat(const sparse *varargin_2, sparse *c) const
        {
            int cnfixeddim;
            int cnnz;
            int cnvardim;
            int i;
            int nzCount;
            bool allEmpty;
            bool b_isAcceptableEmpty_tmp_tmp;
            bool isAcceptableEmpty_tmp_tmp;
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

            sparse::spallocLike((cnvardim), (cnfixeddim), (cnnz), (c));
            nzCount = -1;
            i = c->n;
            for (int ccol = 0; ccol < i; ccol++) {
                int cidx;
                int crowoffs;
                int kpend;
                int kpstart;
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
        // Arguments    : unsigned long b_index
        //                CurvStruct *value
        // Return Type  : void
        //
    }

    void queue_coder::get(unsigned long b_index, CurvStruct *value) const
    {
        *value = this->value_type;

        // ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);
        c_queue_get(this->ptr, static_cast<unsigned int>(b_index), value);
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
    // Arguments    : void
    // Return Type  : bool
    //
    bool queue_coder::isempty() const
    {
        return this->size() == 0U;
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
    // Arguments    : double val
    // Return Type  : void
    //
    void ResampleStateClass::set_u(double val)
    {
        this->u = val;
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
    // Arguments    : void
    // Return Type  : unsigned int
    //
    unsigned int queue_coder::size() const
    {
        return c_queue_size(this->ptr);
    }

    //
    // Arguments    : const queue_coder *ctx_q_splines
    //                const ::coder::array<CurvStruct, 2U> &CurvStructs
    //                const ::coder::array<double, 2U> &Coeff
    //                const double jmax[3]
    //                const ::coder::array<double, 2U> &BasisVal
    //                const ::coder::array<double, 2U> &BasisValD
    //                const ::coder::array<double, 2U> &BasisValDD
    //                const ::coder::array<double, 2U> &u_vec
    //                coder::sparse *A
    //                ::coder::array<double, 1U> &b
    // Return Type  : void
    //
    static void BuildConstrJerk_v4(const queue_coder *ctx_q_splines, const ::coder::array<CurvStruct,
        2U> &CurvStructs, const ::coder::array<double, 2U> &Coeff, const double jmax[3], const ::
        coder::array<double, 2U> &BasisVal, const ::coder::array<double, 2U> &BasisValD, const ::
        coder::array<double, 2U> &BasisValDD, const ::coder::array<double, 2U> &u_vec, coder::sparse
        *A, ::coder::array<double, 1U> &b)
    {
        ::coder::array<double, 2U> R1;
        ::coder::array<double, 2U> R2;
        ::coder::array<double, 2U> R3;
        ::coder::array<double, 2U> b_R1;
        ::coder::array<double, 2U> b_u_vec;
        ::coder::array<double, 2U> b_y;
        ::coder::array<double, 2U> c_u_vec;
        ::coder::array<double, 2U> r1D;
        ::coder::array<double, 2U> r2;
        ::coder::array<double, 2U> r2D;
        ::coder::array<double, 2U> r3;
        ::coder::array<double, 2U> r3D;
        ::coder::array<double, 2U> r4;
        ::coder::array<double, 2U> unusedU0;
        ::coder::array<double, 2U> unusedU1;
        ::coder::array<double, 2U> varargin_2;
        ::coder::array<double, 2U> varargin_4;
        ::coder::array<double, 2U> varargin_6;
        ::coder::array<double, 2U> y;
        ::coder::array<double, 1U> bC2;
        ::coder::array<double, 1U> bC3;
        ::coder::array<double, 1U> bC4;
        ::coder::array<double, 1U> b_r1D;
        ::coder::array<double, 1U> b_r2D;
        ::coder::array<double, 1U> b_r3D;
        ::coder::array<double, 1U> r17;
        ::coder::array<double, 1U> y_tmp;
        double b_b;
        double d;
        int M;
        int N;
        int ab_loop_ub;
        int b_inner;
        int b_input_sizes_idx_0;
        int b_k;
        int b_loop_ub;
        int b_mc;
        int b_scalarLB;
        int b_vectorUB;
        int bb_loop_ub;
        int c_i;
        int c_input_sizes_idx_0;
        int c_loop_ub;
        int cb_loop_ub;
        int d_input_sizes_idx_0;
        int d_loop_ub;
        int db_loop_ub;
        int e_i;
        int e_input_sizes_idx_0;
        int e_k;
        int e_loop_ub;
        int eb_loop_ub;
        int f_input_sizes_idx_0;
        int fb_loop_ub;
        int g_input_sizes_idx_0;
        int g_loop_ub;
        int gb_loop_ub;
        int h_loop_ub;
        int hb_loop_ub;
        int i12;
        int i17;
        int i2;
        int i20;
        int i22;
        int i23;
        int i26;
        int i49;
        int i56;
        int i61;
        int i66;
        int i69;
        int i7;
        int i71;
        int i72;
        int i_loop_ub;
        int ib_loop_ub;
        int inner;
        int input_sizes_idx_0;
        int j_loop_ub;
        int l_loop_ub;
        int loop_ub;
        int m_loop_ub;
        int mc;
        int n_loop_ub;
        int o_loop_ub;
        int q_loop_ub;
        int result;
        int s_loop_ub;
        int u_loop_ub;
        int unnamed_idx_0;
        int y_loop_ub;
        bool empty_non_axis_sizes;

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

        b_EvalCurvStruct(ctx_q_splines, CurvStructs[0].Type, CurvStructs[0].P0, CurvStructs[0].P1,
                         CurvStructs[0].HelixCenter, CurvStructs[0].evec, CurvStructs[0].theta,
                         CurvStructs[0].pitch, CurvStructs[0].CoeffP5, CurvStructs[0].sp_index,
                         CurvStructs[0].a_param, CurvStructs[0].b_param, b_u_vec, unusedU0, r1D, r2D,
                         r3D);

        //
        mc = BasisVal.size(0) - 1;
        inner = BasisVal.size(1);
        y_tmp.set_size(BasisVal.size(0));
        for (int b_i = 0; b_i <= mc; b_i++) {
            y_tmp[b_i] = 0.0;
        }

        for (int k = 0; k < inner; k++) {
            int scalarLB;
            int vectorUB;
            scalarLB = (mc + 1) & -2;
            vectorUB = scalarLB - 2;
            for (c_i = 0; c_i <= vectorUB; c_i += 2) {
                __m128d r;
                r = _mm_loadu_pd(&y_tmp[c_i]);
                _mm_storeu_pd(&y_tmp[c_i], _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd((double *)
                                 &BasisVal[c_i + BasisVal.size(0) * k]), _mm_set1_pd(Coeff[k]))));
            }

            for (c_i = scalarLB; c_i <= mc; c_i++) {
                y_tmp[c_i] = y_tmp[c_i] + BasisVal[c_i + BasisVal.size(0) * k] * Coeff[k];
            }
        }

        i2 = y_tmp.size(0);
        b_scalarLB = y_tmp.size(0) & -2;
        b_vectorUB = b_scalarLB - 2;
        for (b_k = 0; b_k <= b_vectorUB; b_k += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&y_tmp[b_k]);
            _mm_storeu_pd(&y_tmp[b_k], _mm_sqrt_pd(r1));
        }

        for (b_k = b_scalarLB; b_k < i2; b_k++) {
            y_tmp[b_k] = std::sqrt(y_tmp[b_k]);
        }

        sqrt_calls++;
        b_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i3 = 0; i3 < b_loop_ub; i3++) {
            b_r3D[i3] = r3D[3 * i3];
        }

        coder::bsxfun(BasisVal, b_r3D, r2);
        c_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i4 = 0; i4 < c_loop_ub; i4++) {
            b_r2D[i4] = r2D[3 * i4];
        }

        coder::bsxfun(BasisValD, b_r2D, r3);
        d_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i5 = 0; i5 < d_loop_ub; i5++) {
            b_r1D[i5] = r1D[3 * i5];
        }

        coder::bsxfun(BasisValDD, b_r1D, r4);
        e_loop_ub = r2.size(1);
        for (int i6 = 0; i6 < e_loop_ub; i6++) {
            int c_scalarLB;
            int c_vectorUB;
            int f_loop_ub;
            f_loop_ub = r2.size(0);
            c_scalarLB = r2.size(0) & -2;
            c_vectorUB = c_scalarLB - 2;
            for (i7 = 0; i7 <= c_vectorUB; i7 += 2) {
                __m128d r5;
                __m128d r6;
                __m128d r7;
                r5 = _mm_loadu_pd(&r3[i7 + r3.size(0) * i6]);
                r6 = _mm_loadu_pd(&r2[i7 + r2.size(0) * i6]);
                r7 = _mm_loadu_pd(&r4[i7 + r4.size(0) * i6]);
                _mm_storeu_pd(&r2[i7 + r2.size(0) * i6], _mm_add_pd(_mm_add_pd(r6, _mm_mul_pd
                                (_mm_set1_pd(1.5), r5)), _mm_mul_pd(_mm_set1_pd(0.5), r7)));
            }

            for (i7 = c_scalarLB; i7 < f_loop_ub; i7++) {
                r2[i7 + r2.size(0) * i6] = (r2[i7 + r2.size(0) * i6] + 1.5 * r3[i7 + r3.size(0) * i6])
                    + 0.5 * r4[i7 + r4.size(0) * i6];
            }
        }

        coder::bsxfun(r2, y_tmp, R1);
        sqrt_calls++;
        g_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i8 = 0; i8 < g_loop_ub; i8++) {
            b_r3D[i8] = r3D[3 * i8 + 1];
        }

        coder::bsxfun(BasisVal, b_r3D, r2);
        h_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i9 = 0; i9 < h_loop_ub; i9++) {
            b_r2D[i9] = r2D[3 * i9 + 1];
        }

        coder::bsxfun(BasisValD, b_r2D, r3);
        i_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i10 = 0; i10 < i_loop_ub; i10++) {
            b_r1D[i10] = r1D[3 * i10 + 1];
        }

        coder::bsxfun(BasisValDD, b_r1D, r4);
        j_loop_ub = r2.size(1);
        for (int i11 = 0; i11 < j_loop_ub; i11++) {
            int d_scalarLB;
            int d_vectorUB;
            int k_loop_ub;
            k_loop_ub = r2.size(0);
            d_scalarLB = r2.size(0) & -2;
            d_vectorUB = d_scalarLB - 2;
            for (i12 = 0; i12 <= d_vectorUB; i12 += 2) {
                __m128d r10;
                __m128d r8;
                __m128d r9;
                r8 = _mm_loadu_pd(&r3[i12 + r3.size(0) * i11]);
                r9 = _mm_loadu_pd(&r2[i12 + r2.size(0) * i11]);
                r10 = _mm_loadu_pd(&r4[i12 + r4.size(0) * i11]);
                _mm_storeu_pd(&r2[i12 + r2.size(0) * i11], _mm_add_pd(_mm_add_pd(r9, _mm_mul_pd
                                (_mm_set1_pd(1.5), r8)), _mm_mul_pd(_mm_set1_pd(0.5), r10)));
            }

            for (i12 = d_scalarLB; i12 < k_loop_ub; i12++) {
                r2[i12 + r2.size(0) * i11] = (r2[i12 + r2.size(0) * i11] + 1.5 * r3[i12 + r3.size(0)
                    * i11]) + 0.5 * r4[i12 + r4.size(0) * i11];
            }
        }

        coder::bsxfun(r2, y_tmp, R2);
        sqrt_calls++;
        l_loop_ub = r3D.size(1);
        b_r3D.set_size(r3D.size(1));
        for (int i13 = 0; i13 < l_loop_ub; i13++) {
            b_r3D[i13] = r3D[3 * i13 + 2];
        }

        coder::bsxfun(BasisVal, b_r3D, r2);
        m_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i14 = 0; i14 < m_loop_ub; i14++) {
            b_r2D[i14] = r2D[3 * i14 + 2];
        }

        coder::bsxfun(BasisValD, b_r2D, r3);
        n_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i15 = 0; i15 < n_loop_ub; i15++) {
            b_r1D[i15] = r1D[3 * i15 + 2];
        }

        coder::bsxfun(BasisValDD, b_r1D, r4);
        o_loop_ub = r2.size(1);
        for (int i16 = 0; i16 < o_loop_ub; i16++) {
            int e_scalarLB;
            int e_vectorUB;
            int p_loop_ub;
            p_loop_ub = r2.size(0);
            e_scalarLB = r2.size(0) & -2;
            e_vectorUB = e_scalarLB - 2;
            for (i17 = 0; i17 <= e_vectorUB; i17 += 2) {
                __m128d r11;
                __m128d r12;
                __m128d r13;
                r11 = _mm_loadu_pd(&r3[i17 + r3.size(0) * i16]);
                r12 = _mm_loadu_pd(&r2[i17 + r2.size(0) * i16]);
                r13 = _mm_loadu_pd(&r4[i17 + r4.size(0) * i16]);
                _mm_storeu_pd(&r2[i17 + r2.size(0) * i16], _mm_add_pd(_mm_add_pd(r12, _mm_mul_pd
                                (_mm_set1_pd(1.5), r11)), _mm_mul_pd(_mm_set1_pd(0.5), r13)));
            }

            for (i17 = e_scalarLB; i17 < p_loop_ub; i17++) {
                r2[i17 + r2.size(0) * i16] = (r2[i17 + r2.size(0) * i16] + 1.5 * r3[i17 + r3.size(0)
                    * i16]) + 0.5 * r4[i17 + r4.size(0) * i16];
            }
        }

        coder::bsxfun(r2, y_tmp, R3);

        //  R2 = (BasisVal .* r3D(2, :)' + ...
        //        1.5*BasisValD .* r2D(2, :)' + ...
        //        0.5*BasisValDD.*r1D(2, :)') .* mysqrt(q_val);
        //  R3 = (BasisVal .* r3D(3, :)' + ...
        //        1.5*BasisValD .* r2D(3, :)' + ...
        //        0.5*BasisValDD.*r1D(3, :)') .* mysqrt(q_val);
        //
        varargin_2.set_size(R1.size(0), R1.size(1));
        q_loop_ub = R1.size(1);
        for (int i18 = 0; i18 < q_loop_ub; i18++) {
            int f_scalarLB;
            int f_vectorUB;
            int r_loop_ub;
            r_loop_ub = R1.size(0);
            f_scalarLB = R1.size(0) & -2;
            f_vectorUB = f_scalarLB - 2;
            for (i20 = 0; i20 <= f_vectorUB; i20 += 2) {
                __m128d r14;
                r14 = _mm_loadu_pd(&R1[i20 + R1.size(0) * i18]);
                _mm_storeu_pd(&varargin_2[i20 + varargin_2.size(0) * i18], _mm_mul_pd(r14,
                               _mm_set1_pd(-1.0)));
            }

            for (i20 = f_scalarLB; i20 < r_loop_ub; i20++) {
                varargin_2[i20 + varargin_2.size(0) * i18] = -R1[i20 + R1.size(0) * i18];
            }
        }

        varargin_4.set_size(R2.size(0), R2.size(1));
        s_loop_ub = R2.size(1);
        for (int i19 = 0; i19 < s_loop_ub; i19++) {
            int g_scalarLB;
            int g_vectorUB;
            int t_loop_ub;
            t_loop_ub = R2.size(0);
            g_scalarLB = R2.size(0) & -2;
            g_vectorUB = g_scalarLB - 2;
            for (i22 = 0; i22 <= g_vectorUB; i22 += 2) {
                __m128d r15;
                r15 = _mm_loadu_pd(&R2[i22 + R2.size(0) * i19]);
                _mm_storeu_pd(&varargin_4[i22 + varargin_4.size(0) * i19], _mm_mul_pd(r15,
                               _mm_set1_pd(-1.0)));
            }

            for (i22 = g_scalarLB; i22 < t_loop_ub; i22++) {
                varargin_4[i22 + varargin_4.size(0) * i19] = -R2[i22 + R2.size(0) * i19];
            }
        }

        varargin_6.set_size(R3.size(0), R3.size(1));
        u_loop_ub = R3.size(1);
        for (int i21 = 0; i21 < u_loop_ub; i21++) {
            int h_scalarLB;
            int h_vectorUB;
            int v_loop_ub;
            v_loop_ub = R3.size(0);
            h_scalarLB = R3.size(0) & -2;
            h_vectorUB = h_scalarLB - 2;
            for (i23 = 0; i23 <= h_vectorUB; i23 += 2) {
                __m128d r16;
                r16 = _mm_loadu_pd(&R3[i23 + R3.size(0) * i21]);
                _mm_storeu_pd(&varargin_6[i23 + varargin_6.size(0) * i21], _mm_mul_pd(r16,
                               _mm_set1_pd(-1.0)));
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
            y.set_size(1, (static_cast<int>(b_b - 1.0) + 1));
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
            double a;
            double a_tmp;
            double b_tmp;
            double c_b;
            int ac_loop_ub;
            int b_result;
            int cc_loop_ub;
            int ec_loop_ub;
            int h_input_sizes_idx_0;
            int i51;
            int i87;
            int i88;
            int i_input_sizes_idx_0;
            int ic_loop_ub;
            int j_input_sizes_idx_0;
            int j_scalarLB;
            int j_vectorUB;
            int jb_loop_ub;
            int k_input_sizes_idx_0;
            int kb_loop_ub;
            int l_input_sizes_idx_0;
            int lb_loop_ub;
            int m_input_sizes_idx_0;
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
            bool b_empty_non_axis_sizes;
            c_u_vec.set_size(1, u_vec.size(1));
            jb_loop_ub = u_vec.size(1) - 1;
            for (int i50 = 0; i50 <= jb_loop_ub; i50++) {
                c_u_vec[i50] = u_vec[i50];
            }

            b_EvalCurvStruct(ctx_q_splines, CurvStructs[c_k + 1].Type, CurvStructs[c_k + 1].P0,
                             CurvStructs[c_k + 1].P1, CurvStructs[c_k + 1].HelixCenter,
                             CurvStructs[c_k + 1].evec, CurvStructs[c_k + 1].theta, CurvStructs[c_k
                             + 1].pitch, CurvStructs[c_k + 1].CoeffP5, CurvStructs[c_k + 1].sp_index,
                             CurvStructs[c_k + 1].a_param, CurvStructs[c_k + 1].b_param, c_u_vec,
                             unusedU1, r1D, r2D, r3D);

            //
            //      q_opt  = Function(Bl, Coeff(:, k+1));
            //      q_val  = q_opt.fast_eval(u_vec);
            //
            y_tmp.set_size(BasisVal.size(0));
            for (int d_i = 0; d_i <= b_mc; d_i++) {
                y_tmp[d_i] = 0.0;
            }

            for (int d_k = 0; d_k < b_inner; d_k++) {
                int i_scalarLB;
                int i_vectorUB;
                i_scalarLB = (b_mc + 1) & -2;
                i_vectorUB = i_scalarLB - 2;
                for (e_i = 0; e_i <= i_vectorUB; e_i += 2) {
                    __m128d r18;
                    r18 = _mm_loadu_pd(&y_tmp[e_i]);
                    _mm_storeu_pd(&y_tmp[e_i], _mm_add_pd(r18, _mm_mul_pd(_mm_loadu_pd((double *)
                                     &BasisVal[e_i + BasisVal.size(0) * d_k]), _mm_set1_pd(Coeff[d_k
                                     + Coeff.size(0) * (c_k + 1)]))));
                }

                for (e_i = i_scalarLB; e_i <= b_mc; e_i++) {
                    y_tmp[e_i] = y_tmp[e_i] + BasisVal[e_i + BasisVal.size(0) * d_k] * Coeff[d_k +
                        Coeff.size(0) * (c_k + 1)];
                }
            }

            i51 = y_tmp.size(0);
            j_scalarLB = y_tmp.size(0) & -2;
            j_vectorUB = j_scalarLB - 2;
            for (e_k = 0; e_k <= j_vectorUB; e_k += 2) {
                __m128d r19;
                r19 = _mm_loadu_pd(&y_tmp[e_k]);
                _mm_storeu_pd(&y_tmp[e_k], _mm_sqrt_pd(r19));
            }

            for (e_k = j_scalarLB; e_k < i51; e_k++) {
                y_tmp[e_k] = std::sqrt(y_tmp[e_k]);
            }

            sqrt_calls++;
            kb_loop_ub = r3D.size(1);
            b_r3D.set_size(r3D.size(1));
            for (int i52 = 0; i52 < kb_loop_ub; i52++) {
                b_r3D[i52] = r3D[3 * i52];
            }

            coder::bsxfun(BasisVal, b_r3D, r2);
            lb_loop_ub = r2D.size(1);
            b_r2D.set_size(r2D.size(1));
            for (int i53 = 0; i53 < lb_loop_ub; i53++) {
                b_r2D[i53] = r2D[3 * i53];
            }

            coder::bsxfun(BasisValD, b_r2D, r3);
            mb_loop_ub = r1D.size(1);
            b_r1D.set_size(r1D.size(1));
            for (int i54 = 0; i54 < mb_loop_ub; i54++) {
                b_r1D[i54] = r1D[3 * i54];
            }

            coder::bsxfun(BasisValDD, b_r1D, r4);
            nb_loop_ub = r2.size(1);
            for (int i55 = 0; i55 < nb_loop_ub; i55++) {
                int k_scalarLB;
                int k_vectorUB;
                int ob_loop_ub;
                ob_loop_ub = r2.size(0);
                k_scalarLB = r2.size(0) & -2;
                k_vectorUB = k_scalarLB - 2;
                for (i56 = 0; i56 <= k_vectorUB; i56 += 2) {
                    __m128d r20;
                    __m128d r21;
                    __m128d r22;
                    r20 = _mm_loadu_pd(&r3[i56 + r3.size(0) * i55]);
                    r21 = _mm_loadu_pd(&r2[i56 + r2.size(0) * i55]);
                    r22 = _mm_loadu_pd(&r4[i56 + r4.size(0) * i55]);
                    _mm_storeu_pd(&r2[i56 + r2.size(0) * i55], _mm_add_pd(_mm_add_pd(r21, _mm_mul_pd
                                    (_mm_set1_pd(1.5), r20)), _mm_mul_pd(_mm_set1_pd(0.5), r22)));
                }

                for (i56 = k_scalarLB; i56 < ob_loop_ub; i56++) {
                    r2[i56 + r2.size(0) * i55] = (r2[i56 + r2.size(0) * i55] + 1.5 * r3[i56 +
                        r3.size(0) * i55]) + 0.5 * r4[i56 + r4.size(0) * i55];
                }
            }

            coder::bsxfun(r2, y_tmp, R1);
            sqrt_calls++;
            pb_loop_ub = r3D.size(1);
            b_r3D.set_size(r3D.size(1));
            for (int i57 = 0; i57 < pb_loop_ub; i57++) {
                b_r3D[i57] = r3D[3 * i57 + 1];
            }

            coder::bsxfun(BasisVal, b_r3D, r2);
            qb_loop_ub = r2D.size(1);
            b_r2D.set_size(r2D.size(1));
            for (int i58 = 0; i58 < qb_loop_ub; i58++) {
                b_r2D[i58] = r2D[3 * i58 + 1];
            }

            coder::bsxfun(BasisValD, b_r2D, r3);
            rb_loop_ub = r1D.size(1);
            b_r1D.set_size(r1D.size(1));
            for (int i59 = 0; i59 < rb_loop_ub; i59++) {
                b_r1D[i59] = r1D[3 * i59 + 1];
            }

            coder::bsxfun(BasisValDD, b_r1D, r4);
            sb_loop_ub = r2.size(1);
            for (int i60 = 0; i60 < sb_loop_ub; i60++) {
                int l_scalarLB;
                int l_vectorUB;
                int tb_loop_ub;
                tb_loop_ub = r2.size(0);
                l_scalarLB = r2.size(0) & -2;
                l_vectorUB = l_scalarLB - 2;
                for (i61 = 0; i61 <= l_vectorUB; i61 += 2) {
                    __m128d r23;
                    __m128d r24;
                    __m128d r25;
                    r23 = _mm_loadu_pd(&r3[i61 + r3.size(0) * i60]);
                    r24 = _mm_loadu_pd(&r2[i61 + r2.size(0) * i60]);
                    r25 = _mm_loadu_pd(&r4[i61 + r4.size(0) * i60]);
                    _mm_storeu_pd(&r2[i61 + r2.size(0) * i60], _mm_add_pd(_mm_add_pd(r24, _mm_mul_pd
                                    (_mm_set1_pd(1.5), r23)), _mm_mul_pd(_mm_set1_pd(0.5), r25)));
                }

                for (i61 = l_scalarLB; i61 < tb_loop_ub; i61++) {
                    r2[i61 + r2.size(0) * i60] = (r2[i61 + r2.size(0) * i60] + 1.5 * r3[i61 +
                        r3.size(0) * i60]) + 0.5 * r4[i61 + r4.size(0) * i60];
                }
            }

            coder::bsxfun(r2, y_tmp, R2);
            sqrt_calls++;
            ub_loop_ub = r3D.size(1);
            b_r3D.set_size(r3D.size(1));
            for (int i62 = 0; i62 < ub_loop_ub; i62++) {
                b_r3D[i62] = r3D[3 * i62 + 2];
            }

            coder::bsxfun(BasisVal, b_r3D, r2);
            vb_loop_ub = r2D.size(1);
            b_r2D.set_size(r2D.size(1));
            for (int i63 = 0; i63 < vb_loop_ub; i63++) {
                b_r2D[i63] = r2D[3 * i63 + 2];
            }

            coder::bsxfun(BasisValD, b_r2D, r3);
            wb_loop_ub = r1D.size(1);
            b_r1D.set_size(r1D.size(1));
            for (int i64 = 0; i64 < wb_loop_ub; i64++) {
                b_r1D[i64] = r1D[3 * i64 + 2];
            }

            coder::bsxfun(BasisValDD, b_r1D, r4);
            xb_loop_ub = r2.size(1);
            for (int i65 = 0; i65 < xb_loop_ub; i65++) {
                int m_scalarLB;
                int m_vectorUB;
                int yb_loop_ub;
                yb_loop_ub = r2.size(0);
                m_scalarLB = r2.size(0) & -2;
                m_vectorUB = m_scalarLB - 2;
                for (i66 = 0; i66 <= m_vectorUB; i66 += 2) {
                    __m128d r26;
                    __m128d r27;
                    __m128d r28;
                    r26 = _mm_loadu_pd(&r3[i66 + r3.size(0) * i65]);
                    r27 = _mm_loadu_pd(&r2[i66 + r2.size(0) * i65]);
                    r28 = _mm_loadu_pd(&r4[i66 + r4.size(0) * i65]);
                    _mm_storeu_pd(&r2[i66 + r2.size(0) * i65], _mm_add_pd(_mm_add_pd(r27, _mm_mul_pd
                                    (_mm_set1_pd(1.5), r26)), _mm_mul_pd(_mm_set1_pd(0.5), r28)));
                }

                for (i66 = m_scalarLB; i66 < yb_loop_ub; i66++) {
                    r2[i66 + r2.size(0) * i65] = (r2[i66 + r2.size(0) * i65] + 1.5 * r3[i66 +
                        r3.size(0) * i65]) + 0.5 * r4[i66 + r4.size(0) * i65];
                }
            }

            coder::bsxfun(r2, y_tmp, R3);

            //      R2 = (BasisVal .* r3D(2, :)' + ...
            //            1.5*BasisValD .* r2D(2, :)' + ...
            //            0.5*BasisValDD.*r1D(2, :)') .* mysqrt(q_val);
            //      R3 = (BasisVal .* r3D(3, :)' + ...
            //            1.5*BasisValD .* r2D(3, :)' + ...
            //            0.5*BasisValDD.*r1D(3, :)') .* mysqrt(q_val);
            //
            varargin_2.set_size(R1.size(0), R1.size(1));
            ac_loop_ub = R1.size(1);
            for (int i67 = 0; i67 < ac_loop_ub; i67++) {
                int bc_loop_ub;
                int n_scalarLB;
                int n_vectorUB;
                bc_loop_ub = R1.size(0);
                n_scalarLB = R1.size(0) & -2;
                n_vectorUB = n_scalarLB - 2;
                for (i69 = 0; i69 <= n_vectorUB; i69 += 2) {
                    __m128d r29;
                    r29 = _mm_loadu_pd(&R1[i69 + R1.size(0) * i67]);
                    _mm_storeu_pd(&varargin_2[i69 + varargin_2.size(0) * i67], _mm_mul_pd(r29,
                                   _mm_set1_pd(-1.0)));
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
                o_scalarLB = R2.size(0) & -2;
                o_vectorUB = o_scalarLB - 2;
                for (i71 = 0; i71 <= o_vectorUB; i71 += 2) {
                    __m128d r30;
                    r30 = _mm_loadu_pd(&R2[i71 + R2.size(0) * i68]);
                    _mm_storeu_pd(&varargin_4[i71 + varargin_4.size(0) * i68], _mm_mul_pd(r30,
                                   _mm_set1_pd(-1.0)));
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
                p_scalarLB = R3.size(0) & -2;
                p_vectorUB = p_scalarLB - 2;
                for (i72 = 0; i72 <= p_vectorUB; i72 += 2) {
                    __m128d r31;
                    r31 = _mm_loadu_pd(&R3[i72 + R3.size(0) * i70]);
                    _mm_storeu_pd(&varargin_6[i72 + varargin_6.size(0) * i70], _mm_mul_pd(r31,
                                   _mm_set1_pd(-1.0)));
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
    //                double ctx_cfg_DynamicBreakpointsDistance
    //                int ctx_cfg_SplineDegree
    //                double ctx_cfg_NGridLengthSpline
    //                int ctx_Bl_ncoeff
    //                unsigned long ctx_Bl_handle
    //                const ::coder::array<CurvStruct, 2U> &CurvStructs
    //                const double amax[3]
    //                double v_0
    //                double at_0
    //                double v_1
    //                double at_1
    //                ::coder::array<double, 2U> &BasisVal
    //                ::coder::array<double, 2U> &BasisValD
    //                const ::coder::array<double, 2U> &u_vec
    //                coder::sparse *A
    //                ::coder::array<double, 1U> &b
    //                ::coder::array<double, 2U> &Aeq
    //                ::coder::array<double, 1U> &beq
    // Return Type  : void
    //
    static void BuildConstr_v4(const queue_coder *ctx_q_splines, bool ctx_cfg_UseDynamicBreakpoints,
        bool ctx_cfg_UseLinearBreakpoints, double ctx_cfg_DynamicBreakpointsDistance, int
        ctx_cfg_SplineDegree, double ctx_cfg_NGridLengthSpline, int ctx_Bl_ncoeff, unsigned long
        ctx_Bl_handle, const ::coder::array<CurvStruct, 2U> &CurvStructs, const double amax[3],
        double v_0, double at_0, double v_1, double at_1, ::coder::array<double, 2U> &BasisVal, ::
        coder::array<double, 2U> &BasisValD, const ::coder::array<double, 2U> &u_vec, coder::sparse *
        A, ::coder::array<double, 1U> &b, ::coder::array<double, 2U> &Aeq, ::coder::array<double, 1U>
        &beq)
    {
        __m128d r17;
        ::coder::array<double, 2U> R1;
        ::coder::array<double, 2U> R2;
        ::coder::array<double, 2U> R3;
        ::coder::array<double, 2U> b_BasisVal;
        ::coder::array<double, 2U> b_u_vec;
        ::coder::array<double, 2U> b_y;
        ::coder::array<double, 2U> breakpoints;
        ::coder::array<double, 2U> c_u_vec;
        ::coder::array<double, 2U> g_a;
        ::coder::array<double, 2U> r;
        ::coder::array<double, 2U> r1;
        ::coder::array<double, 2U> r15;
        ::coder::array<double, 2U> r16;
        ::coder::array<double, 2U> r1D;
        ::coder::array<double, 2U> r1D_sqnorm;
        ::coder::array<double, 2U> r1Dn;
        ::coder::array<double, 2U> r2;
        ::coder::array<double, 2U> r2D;
        ::coder::array<double, 2U> r2Dn;
        ::coder::array<double, 2U> unusedU0;
        ::coder::array<double, 2U> unusedU1;
        ::coder::array<double, 2U> varargin_3;
        ::coder::array<double, 2U> varargin_5;
        ::coder::array<double, 2U> varargin_7;
        ::coder::array<double, 2U> y;
        ::coder::array<double, 1U> bC2;
        ::coder::array<double, 1U> bC3;
        ::coder::array<double, 1U> bC4;
        ::coder::array<double, 1U> b_r1D;
        ::coder::array<double, 1U> b_r1Dn;
        ::coder::array<double, 1U> b_r2D;
        ::coder::array<double, 1U> b_r2Dn;
        ::coder::array<double, 1U> r12;
        double c_r1D[3];
        double t_1[3];
        double a;
        double b_a;
        double b_b;
        double c_a;
        double d1;
        double d2;
        double d_a;
        double e_a;
        double f_a;
        double h_a;
        double i_a;
        double j_a;
        double k_a;
        double l_a;
        double m_a;
        double x;
        unsigned long Bl_handle;
        int Bl_ncoeff;
        int N;
        int ab_loop_ub;
        int b_N;
        int b_input_sizes_idx_0;
        int b_loop_ub;
        int b_unnamed_idx_0;
        int b_unnamed_idx_1;
        int bb_loop_ub;
        int bc_loop_ub;
        int c_input_sizes_idx_0;
        int c_loop_ub;
        int c_unnamed_idx_1;
        int cb_loop_ub;
        int d_input_sizes_idx_0;
        int d_loop_ub;
        int d_r1D;
        int d_unnamed_idx_1;
        int db_loop_ub;
        int e_input_sizes_idx_0;
        int e_loop_ub;
        int e_unnamed_idx_1;
        int eb_loop_ub;
        int f_input_sizes_idx_0;
        int f_r1D;
        int f_unnamed_idx_1;
        int fb_loop_ub;
        int g_input_sizes_idx_0;
        int g_loop_ub;
        int g_scalarLB;
        int g_vectorUB;
        int gb_loop_ub;
        int h_input_sizes_idx_0;
        int h_loop_ub;
        int hb_loop_ub;
        int i10;
        int i14;
        int i18;
        int i20;
        int i22;
        int i23;
        int i26;
        int i27;
        int i46;
        int i58;
        int i62;
        int i72;
        int i76;
        int i80;
        int i82;
        int i84;
        int i85;
        int i_loop_ub;
        int ib_loop_ub;
        int input_sizes_idx_0;
        int jb_loop_ub;
        int k_loop_ub;
        int kb_loop_ub;
        int l_loop_ub;
        int lb_loop_ub;
        int loop_ub;
        int mb_loop_ub;
        int n_loop_ub;
        int nb_loop_ub;
        int p_loop_ub;
        int pb_loop_ub;
        int qb_loop_ub;
        int r_loop_ub;
        int rb_loop_ub;
        int result;
        int sb_loop_ub;
        int tb_loop_ub;
        int ub_loop_ub;
        int unnamed_idx_0;
        int unnamed_idx_1;
        int v_loop_ub;
        int vb_loop_ub;
        int w_loop_ub;
        int x_loop_ub;
        int y_loop_ub;
        int yb_loop_ub;
        bool empty_non_axis_sizes;

        //  1 -> stdout
        //  2 -> stderr
        if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
            printf("BuildConstr_v4 with Ncrv = %d, amax = [%f, %f, %f], v_0 = %f, at_0 = %f, v_1 = %f, at_1 = %f\n",
                   CurvStructs.size(1), amax[0], amax[1], amax[2], v_0, at_0, v_1, at_1);
            fflush(stdout);
        }

        Bl_ncoeff = ctx_Bl_ncoeff;
        Bl_handle = ctx_Bl_handle;
        if (ctx_cfg_UseDynamicBreakpoints) {
            double varargin_1;
            varargin_1 = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStructs[0].Type,
                                    CurvStructs[0].P0, CurvStructs[0].P1, CurvStructs[0].HelixCenter,
                                    CurvStructs[0].evec, CurvStructs[0].theta, CurvStructs[0].pitch,
                                    CurvStructs[0].CoeffP5, CurvStructs[0].sp_index, CurvStructs[0].
                                    a_param, CurvStructs[0].b_param) /
                ctx_cfg_DynamicBreakpointsDistance;
            if (ctx_cfg_UseLinearBreakpoints) {
                double delta1;
                int i;
                breakpoints.set_size(1, (static_cast<int>(std::fmax(std::floor(varargin_1), 4.0))));
                breakpoints[static_cast<int>(std::fmax(std::floor(varargin_1), 4.0)) - 1] = 1.0;
                breakpoints[0] = 0.0;
                delta1 = 1.0 / (static_cast<double>(breakpoints.size(1)) - 1.0);
                i = breakpoints.size(1);
                for (int k = 0; k <= i - 3; k++) {
                    breakpoints[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
                }

                Bl_ncoeff = (breakpoints.size(1) + ctx_cfg_SplineDegree) - 2;
                c_bspline_create_with_breakpoints(&Bl_handle, ctx_cfg_SplineDegree, &breakpoints[0],
                    breakpoints.size(1));
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
            for (int i3 = 0; i3 < b_unnamed_idx_0; i3++) {
                Aeq[i3 + Aeq.size(0) * i2] = 0.0;
            }
        }

        //  preallocation
        unnamed_idx_0 = static_cast<int>(2.0 * (static_cast<double>(CurvStructs.size(1)) + 1.0));
        beq.set_size(unnamed_idx_0);
        for (int i4 = 0; i4 < unnamed_idx_0; i4++) {
            beq[i4] = 0.0;
        }

        //  preallocation
        //  coder.varsize('b', [7*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz, 1], [1,0]);
        //  coder.varsize('Aeq', [2*(FeedoptLimits.MaxNHorz+1), FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz], [1,1]); 
        //  coder.varsize('beq', [2*(FeedoptLimits.MaxNHorz+1), 1], [1,0]);
        //
        b_u_vec.set_size(1, u_vec.size(1));
        loop_ub = u_vec.size(1) - 1;
        for (int i5 = 0; i5 <= loop_ub; i5++) {
            b_u_vec[i5] = u_vec[i5];
        }

        b_EvalCurvStruct(ctx_q_splines, CurvStructs[0].Type, CurvStructs[0].P0, CurvStructs[0].P1,
                         CurvStructs[0].HelixCenter, CurvStructs[0].evec, CurvStructs[0].theta,
                         CurvStructs[0].pitch, CurvStructs[0].CoeffP5, CurvStructs[0].sp_index,
                         CurvStructs[0].a_param, CurvStructs[0].b_param, b_u_vec, unusedU0, r1D, r2D);
        r.set_size(3, r1D.size(1));
        b_N = r1D.size(1);
        for (int b_k = 0; b_k < b_N; b_k++) {
            r[3 * b_k] = std::pow(r1D[3 * b_k], 2.0);
            r[3 * b_k + 1] = std::pow(r1D[3 * b_k + 1], 2.0);
            r[3 * b_k + 2] = std::pow(r1D[3 * b_k + 2], 2.0);
        }

        coder::sum(r, r1D_sqnorm);

        //  squared norm
        //
        //  unit tangent vector @ start
        //
        //
        b_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i6 = 0; i6 < b_loop_ub; i6++) {
            b_r2D[i6] = r2D[3 * i6];
        }

        coder::bsxfun(b_r2D, BasisVal, r1);
        c_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i7 = 0; i7 < c_loop_ub; i7++) {
            b_r1D[i7] = r1D[3 * i7];
        }

        coder::bsxfun(b_r1D, BasisValD, r2);
        R1.set_size(r1.size(0), r1.size(1));
        d_loop_ub = r1.size(1);
        for (int i8 = 0; i8 < d_loop_ub; i8++) {
            int f_loop_ub;
            int scalarLB;
            int vectorUB;
            f_loop_ub = r1.size(0);
            scalarLB = r1.size(0) & -2;
            vectorUB = scalarLB - 2;
            for (i10 = 0; i10 <= vectorUB; i10 += 2) {
                __m128d r3;
                __m128d r4;
                r3 = _mm_loadu_pd(&r2[i10 + r2.size(0) * i8]);
                r4 = _mm_loadu_pd(&r1[i10 + r1.size(0) * i8]);
                _mm_storeu_pd(&R1[i10 + R1.size(0) * i8], _mm_add_pd(r4, _mm_mul_pd(_mm_set1_pd(0.5),
                                r3)));
            }

            for (i10 = scalarLB; i10 < f_loop_ub; i10++) {
                R1[i10 + R1.size(0) * i8] = r1[i10 + r1.size(0) * i8] + 0.5 * r2[i10 + r2.size(0) *
                    i8];
            }
        }

        e_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i9 = 0; i9 < e_loop_ub; i9++) {
            b_r2D[i9] = r2D[3 * i9 + 1];
        }

        coder::bsxfun(b_r2D, BasisVal, r1);
        g_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i11 = 0; i11 < g_loop_ub; i11++) {
            b_r1D[i11] = r1D[3 * i11 + 1];
        }

        coder::bsxfun(b_r1D, BasisValD, r2);
        R2.set_size(r1.size(0), r1.size(1));
        h_loop_ub = r1.size(1);
        for (int i12 = 0; i12 < h_loop_ub; i12++) {
            int b_scalarLB;
            int b_vectorUB;
            int j_loop_ub;
            j_loop_ub = r1.size(0);
            b_scalarLB = r1.size(0) & -2;
            b_vectorUB = b_scalarLB - 2;
            for (i14 = 0; i14 <= b_vectorUB; i14 += 2) {
                __m128d r5;
                __m128d r6;
                r5 = _mm_loadu_pd(&r2[i14 + r2.size(0) * i12]);
                r6 = _mm_loadu_pd(&r1[i14 + r1.size(0) * i12]);
                _mm_storeu_pd(&R2[i14 + R2.size(0) * i12], _mm_add_pd(r6, _mm_mul_pd(_mm_set1_pd(0.5),
                                r5)));
            }

            for (i14 = b_scalarLB; i14 < j_loop_ub; i14++) {
                R2[i14 + R2.size(0) * i12] = r1[i14 + r1.size(0) * i12] + 0.5 * r2[i14 + r2.size(0) *
                    i12];
            }
        }

        i_loop_ub = r2D.size(1);
        b_r2D.set_size(r2D.size(1));
        for (int i13 = 0; i13 < i_loop_ub; i13++) {
            b_r2D[i13] = r2D[3 * i13 + 2];
        }

        coder::bsxfun(b_r2D, BasisVal, r1);
        k_loop_ub = r1D.size(1);
        b_r1D.set_size(r1D.size(1));
        for (int i15 = 0; i15 < k_loop_ub; i15++) {
            b_r1D[i15] = r1D[3 * i15 + 2];
        }

        coder::bsxfun(b_r1D, BasisValD, r2);
        R3.set_size(r1.size(0), r1.size(1));
        l_loop_ub = r1.size(1);
        for (int i16 = 0; i16 < l_loop_ub; i16++) {
            int c_scalarLB;
            int c_vectorUB;
            int m_loop_ub;
            m_loop_ub = r1.size(0);
            c_scalarLB = r1.size(0) & -2;
            c_vectorUB = c_scalarLB - 2;
            for (i18 = 0; i18 <= c_vectorUB; i18 += 2) {
                __m128d r7;
                __m128d r8;
                r7 = _mm_loadu_pd(&r2[i18 + r2.size(0) * i16]);
                r8 = _mm_loadu_pd(&r1[i18 + r1.size(0) * i16]);
                _mm_storeu_pd(&R3[i18 + R3.size(0) * i16], _mm_add_pd(r8, _mm_mul_pd(_mm_set1_pd(0.5),
                                r7)));
            }

            for (i18 = c_scalarLB; i18 < m_loop_ub; i18++) {
                R3[i18 + R3.size(0) * i16] = r1[i18 + r1.size(0) * i16] + 0.5 * r2[i18 + r2.size(0) *
                    i16];
            }
        }

        //
        varargin_3.set_size(R1.size(0), R1.size(1));
        n_loop_ub = R1.size(1);
        for (int i17 = 0; i17 < n_loop_ub; i17++) {
            int d_scalarLB;
            int d_vectorUB;
            int o_loop_ub;
            o_loop_ub = R1.size(0);
            d_scalarLB = R1.size(0) & -2;
            d_vectorUB = d_scalarLB - 2;
            for (i20 = 0; i20 <= d_vectorUB; i20 += 2) {
                __m128d r9;
                r9 = _mm_loadu_pd(&R1[i20 + R1.size(0) * i17]);
                _mm_storeu_pd(&varargin_3[i20 + varargin_3.size(0) * i17], _mm_mul_pd(r9,
                               _mm_set1_pd(-1.0)));
            }

            for (i20 = d_scalarLB; i20 < o_loop_ub; i20++) {
                varargin_3[i20 + varargin_3.size(0) * i17] = -R1[i20 + R1.size(0) * i17];
            }
        }

        varargin_5.set_size(R2.size(0), R2.size(1));
        p_loop_ub = R2.size(1);
        for (int i19 = 0; i19 < p_loop_ub; i19++) {
            int e_scalarLB;
            int e_vectorUB;
            int q_loop_ub;
            q_loop_ub = R2.size(0);
            e_scalarLB = R2.size(0) & -2;
            e_vectorUB = e_scalarLB - 2;
            for (i22 = 0; i22 <= e_vectorUB; i22 += 2) {
                __m128d r10;
                r10 = _mm_loadu_pd(&R2[i22 + R2.size(0) * i19]);
                _mm_storeu_pd(&varargin_5[i22 + varargin_5.size(0) * i19], _mm_mul_pd(r10,
                               _mm_set1_pd(-1.0)));
            }

            for (i22 = e_scalarLB; i22 < q_loop_ub; i22++) {
                varargin_5[i22 + varargin_5.size(0) * i19] = -R2[i22 + R2.size(0) * i19];
            }
        }

        varargin_7.set_size(R3.size(0), R3.size(1));
        r_loop_ub = R3.size(1);
        for (int i21 = 0; i21 < r_loop_ub; i21++) {
            int f_scalarLB;
            int f_vectorUB;
            int s_loop_ub;
            s_loop_ub = R3.size(0);
            f_scalarLB = R3.size(0) & -2;
            f_vectorUB = f_scalarLB - 2;
            for (i23 = 0; i23 <= f_vectorUB; i23 += 2) {
                __m128d r11;
                r11 = _mm_loadu_pd(&R3[i23 + R3.size(0) * i21]);
                _mm_storeu_pd(&varargin_7[i23 + varargin_7.size(0) * i21], _mm_mul_pd(r11,
                               _mm_set1_pd(-1.0)));
            }

            for (i23 = f_scalarLB; i23 < s_loop_ub; i23++) {
                varargin_7[i23 + varargin_7.size(0) * i21] = -R3[i23 + R3.size(0) * i21];
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
            int t_loop_ub;
            t_loop_ub = static_cast<int>(b_b - 1.0);
            y.set_size(1, (static_cast<int>(b_b - 1.0) + 1));
            for (int i24 = 0; i24 <= t_loop_ub; i24++) {
                y[i24] = static_cast<double>(i24) + 1.0;
            }
        }

        if (BasisVal.size(1) < 1) {
            b_y.set_size(1, 0);
        } else {
            int u_loop_ub;
            b_y.set_size(1, BasisVal.size(1));
            u_loop_ub = BasisVal.size(1) - 1;
            for (int i25 = 0; i25 <= u_loop_ub; i25++) {
                b_y[i25] = static_cast<double>(i25) + 1.0;
            }
        }

        h_input_sizes_idx_0 = input_sizes_idx_0;
        input_sizes_idx_0 = b_input_sizes_idx_0;
        b_input_sizes_idx_0 = c_input_sizes_idx_0;
        c_input_sizes_idx_0 = d_input_sizes_idx_0;
        d_input_sizes_idx_0 = e_input_sizes_idx_0;
        i26 = h_input_sizes_idx_0 + input_sizes_idx_0;
        i27 = i26 + b_input_sizes_idx_0;
        b_BasisVal.set_size(((((i27 + c_input_sizes_idx_0) + d_input_sizes_idx_0) +
                              f_input_sizes_idx_0) + g_input_sizes_idx_0), result);
        for (int i28 = 0; i28 < result; i28++) {
            for (int i30 = 0; i30 < h_input_sizes_idx_0; i30++) {
                b_BasisVal[i30 + b_BasisVal.size(0) * i28] = BasisVal[i30 + h_input_sizes_idx_0 *
                    i28];
            }
        }

        for (int i29 = 0; i29 < result; i29++) {
            for (int i32 = 0; i32 < input_sizes_idx_0; i32++) {
                b_BasisVal[(i32 + h_input_sizes_idx_0) + b_BasisVal.size(0) * i29] = R1[i32 +
                    input_sizes_idx_0 * i29];
            }
        }

        for (int i31 = 0; i31 < result; i31++) {
            for (int i34 = 0; i34 < b_input_sizes_idx_0; i34++) {
                b_BasisVal[((i34 + h_input_sizes_idx_0) + input_sizes_idx_0) + b_BasisVal.size(0) *
                    i31] = varargin_3[i34 + b_input_sizes_idx_0 * i31];
            }
        }

        for (int i33 = 0; i33 < result; i33++) {
            for (int i36 = 0; i36 < c_input_sizes_idx_0; i36++) {
                b_BasisVal[(((i36 + h_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0)
                    + b_BasisVal.size(0) * i33] = R2[i36 + c_input_sizes_idx_0 * i33];
            }
        }

        for (int i35 = 0; i35 < result; i35++) {
            for (int i38 = 0; i38 < d_input_sizes_idx_0; i38++) {
                b_BasisVal[((((i38 + h_input_sizes_idx_0) + input_sizes_idx_0) + b_input_sizes_idx_0)
                            + c_input_sizes_idx_0) + b_BasisVal.size(0) * i35] = varargin_5[i38 +
                    d_input_sizes_idx_0 * i35];
            }
        }

        for (int i37 = 0; i37 < result; i37++) {
            for (int i40 = 0; i40 < f_input_sizes_idx_0; i40++) {
                b_BasisVal[((((i40 + i26) + b_input_sizes_idx_0) + c_input_sizes_idx_0) +
                            d_input_sizes_idx_0) + b_BasisVal.size(0) * i37] = R3[i40 +
                    f_input_sizes_idx_0 * i37];
            }
        }

        for (int i39 = 0; i39 < result; i39++) {
            for (int i41 = 0; i41 < g_input_sizes_idx_0; i41++) {
                b_BasisVal[((((i41 + i27) + c_input_sizes_idx_0) + d_input_sizes_idx_0) +
                            f_input_sizes_idx_0) + b_BasisVal.size(0) * i39] = varargin_7[i41 +
                    g_input_sizes_idx_0 * i39];
            }
        }

        A->parenAssign(b_BasisVal, y, b_y);

        //
        x = std::pow(CurvStructs[0].FeedRate, 2.0);
        bC2.set_size(BasisVal.size(0));
        v_loop_ub = BasisVal.size(0);
        for (int i42 = 0; i42 < v_loop_ub; i42++) {
            bC2[i42] = amax[0];
        }

        bC3.set_size(BasisVal.size(0));
        w_loop_ub = BasisVal.size(0);
        for (int i43 = 0; i43 < w_loop_ub; i43++) {
            bC3[i43] = amax[1];
        }

        bC4.set_size(BasisVal.size(0));
        x_loop_ub = BasisVal.size(0);
        for (int i44 = 0; i44 < x_loop_ub; i44++) {
            bC4[i44] = amax[2];
        }

        //
        r12.set_size(r1D_sqnorm.size(1));
        y_loop_ub = r1D_sqnorm.size(1);
        for (int i45 = 0; i45 < y_loop_ub; i45++) {
            r12[i45] = r1D_sqnorm[i45];
        }

        unnamed_idx_1 = r12.size(0);
        b_unnamed_idx_1 = bC2.size(0);
        c_unnamed_idx_1 = bC2.size(0);
        d_unnamed_idx_1 = bC3.size(0);
        e_unnamed_idx_1 = bC3.size(0);
        f_unnamed_idx_1 = bC4.size(0);
        ab_loop_ub = r12.size(0);
        g_scalarLB = r12.size(0) & -2;
        g_vectorUB = g_scalarLB - 2;
        for (i46 = 0; i46 <= g_vectorUB; i46 += 2) {
            __m128d r13;
            r13 = _mm_loadu_pd(&r12[i46]);
            _mm_storeu_pd(&b[i46], _mm_div_pd(_mm_set1_pd(x), r13));
        }

        for (i46 = g_scalarLB; i46 < ab_loop_ub; i46++) {
            b[i46] = x / r12[i46];
        }

        bb_loop_ub = bC2.size(0);
        for (int i47 = 0; i47 < bb_loop_ub; i47++) {
            b[i47 + unnamed_idx_1] = bC2[i47];
        }

        cb_loop_ub = bC2.size(0);
        for (int i48 = 0; i48 < cb_loop_ub; i48++) {
            b[(i48 + unnamed_idx_1) + b_unnamed_idx_1] = bC2[i48];
        }

        db_loop_ub = bC3.size(0);
        for (int i49 = 0; i49 < db_loop_ub; i49++) {
            b[((i49 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1] = bC3[i49];
        }

        eb_loop_ub = bC3.size(0);
        for (int i50 = 0; i50 < eb_loop_ub; i50++) {
            b[(((i50 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1] =
                bC3[i50];
        }

        fb_loop_ub = bC4.size(0);
        for (int i51 = 0; i51 < fb_loop_ub; i51++) {
            b[((((i51 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1) +
                e_unnamed_idx_1] = bC4[i51];
        }

        gb_loop_ub = bC4.size(0);
        for (int i52 = 0; i52 < gb_loop_ub; i52++) {
            b[(((((i52 + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) + d_unnamed_idx_1) +
                e_unnamed_idx_1) + f_unnamed_idx_1] = bC4[i52];
        }

        __m128d r14;
        double d;

        //
        a = r2D[0];
        b_a = 0.5 * r1D[0];
        c_a = r2D[1];
        d_a = 0.5 * r1D[1];
        e_a = r2D[2];
        f_a = 0.5 * r1D[2];
        d = coder::b_norm(*(double (*)[3])&r1D[0]);
        r14 = _mm_loadu_pd(&r1D[0]);
        _mm_storeu_pd(&c_r1D[0], _mm_div_pd(r14, _mm_set1_pd(d)));
        c_r1D[2] = r1D[2] / d;
        hb_loop_ub = BasisVal.size(1);
        ib_loop_ub = BasisVal.size(1);
        jb_loop_ub = BasisVal.size(1);
        g_a.set_size(3, BasisVal.size(1));
        for (int i53 = 0; i53 < hb_loop_ub; i53++) {
            g_a[3 * i53] = a * BasisVal[BasisVal.size(0) * i53] + b_a * BasisValD[BasisValD.size(0) *
                i53];
        }

        for (int i54 = 0; i54 < ib_loop_ub; i54++) {
            g_a[3 * i54 + 1] = c_a * BasisVal[BasisVal.size(0) * i54] + d_a *
                BasisValD[BasisValD.size(0) * i54];
        }

        for (int i55 = 0; i55 < jb_loop_ub; i55++) {
            g_a[3 * i55 + 2] = e_a * BasisVal[BasisVal.size(0) * i55] + f_a *
                BasisValD[BasisValD.size(0) * i55];
        }

        coder::internal::blas::mtimes(c_r1D, g_a, r15);
        kb_loop_ub = BasisVal.size(1);
        for (int i56 = 0; i56 < kb_loop_ub; i56++) {
            Aeq[Aeq.size(0) * i56] = BasisVal[BasisVal.size(0) * i56];
        }

        lb_loop_ub = r15.size(1);
        for (int i57 = 0; i57 < lb_loop_ub; i57++) {
            Aeq[Aeq.size(0) * i57 + 1] = r15[i57];
        }

        beq[0] = std::pow(v_0, 2.0) / r1D_sqnorm[0];
        beq[1] = at_0;

        //  This should be the correct behavior for a single segment,
        //  reusing the r1D norm
        i58 = CurvStructs.size(1);
        if (0 <= CurvStructs.size(1) - 2) {
            b_unnamed_idx_1 = bC2.size(0);
            c_unnamed_idx_1 = bC2.size(0);
            d_unnamed_idx_1 = bC3.size(0);
            e_unnamed_idx_1 = bC3.size(0);
            f_unnamed_idx_1 = bC4.size(0);
            mb_loop_ub = bC2.size(0);
            nb_loop_ub = bC2.size(0);
            pb_loop_ub = bC3.size(0);
            qb_loop_ub = bC3.size(0);
            rb_loop_ub = bC4.size(0);
            sb_loop_ub = bC4.size(0);
        }

        for (int c_k = 0; c_k <= i58 - 2; c_k++) {
            double a_tmp;
            double ab_a;
            double b_tmp;
            double b_x;
            double bb_a;
            double c;
            double c_b;
            double cb_a;
            double d10;
            double d4;
            double d5;
            double d6;
            double d7;
            double d_b;
            double n_a;
            double o_a;
            double p_a;
            double q_a;
            double r_a;
            double s_a;
            double t_a;
            double u_a;
            double v_a;
            double w_a;
            double x_a;
            double y_a;
            int ac_loop_ub;
            int ad_loop_ub;
            int b_result;
            int bd_loop_ub;
            int c_N;
            int cc_loop_ub;
            int cd_loop_ub;
            int dd_loop_ub;
            int ec_loop_ub;
            int fc_loop_ub;
            int gc_loop_ub;
            int i102;
            int i111;
            int i112;
            int i114;
            int i116;
            int i119;
            int i_input_sizes_idx_0;
            int ic_loop_ub;
            int j_input_sizes_idx_0;
            int jc_loop_ub;
            int k_input_sizes_idx_0;
            int l_input_sizes_idx_0;
            int lc_loop_ub;
            int m_input_sizes_idx_0;
            int n_input_sizes_idx_0;
            int nc_loop_ub;
            int o_input_sizes_idx_0;
            int ob_loop_ub;
            int pc_loop_ub;
            int tc_loop_ub;
            int uc_loop_ub;
            int vc_loop_ub;
            int wb_loop_ub;
            int wc_loop_ub;
            int xb_loop_ub;
            int xc_loop_ub;
            int yc_loop_ub;
            bool b_empty_non_axis_sizes;
            if (ctx_cfg_UseDynamicBreakpoints) {
                double varargin_2;
                varargin_2 = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStructs[c_k +
                                        1].Type, CurvStructs[c_k + 1].P0, CurvStructs[c_k + 1].P1,
                                        CurvStructs[c_k + 1].HelixCenter, CurvStructs[c_k + 1].evec,
                                        CurvStructs[c_k + 1].theta, CurvStructs[c_k + 1].pitch,
                                        CurvStructs[c_k + 1].CoeffP5, CurvStructs[c_k + 1].sp_index,
                                        CurvStructs[c_k + 1].a_param, CurvStructs[c_k + 1].b_param) /
                    ctx_cfg_DynamicBreakpointsDistance;
                if (ctx_cfg_UseLinearBreakpoints) {
                    double b_delta1;
                    int i59;
                    int i61;
                    i59 = static_cast<int>(std::fmax(4.0, std::floor(varargin_2)));
                    breakpoints.set_size(1, i59);
                    breakpoints[i59 - 1] = 1.0;
                    breakpoints[0] = 0.0;
                    b_delta1 = 1.0 / (static_cast<double>(breakpoints.size(1)) - 1.0);
                    i61 = breakpoints.size(1);
                    for (int d_k = 0; d_k <= i61 - 3; d_k++) {
                        breakpoints[d_k + 1] = (static_cast<double>(d_k) + 1.0) * b_delta1;
                    }

                    Bl_ncoeff = (breakpoints.size(1) + ctx_cfg_SplineDegree) - 2;
                    c_bspline_create_with_breakpoints(&Bl_handle, ctx_cfg_SplineDegree,
                        &breakpoints[0], breakpoints.size(1));
                }

                bspline_base_eval(Bl_ncoeff, Bl_handle, u_vec, BasisVal, BasisValD);
            }

            N = BasisVal.size(1);
            c_u_vec.set_size(1, u_vec.size(1));
            ob_loop_ub = u_vec.size(1) - 1;
            for (int i60 = 0; i60 <= ob_loop_ub; i60++) {
                c_u_vec[i60] = u_vec[i60];
            }

            b_EvalCurvStruct(ctx_q_splines, CurvStructs[c_k + 1].Type, CurvStructs[c_k + 1].P0,
                             CurvStructs[c_k + 1].P1, CurvStructs[c_k + 1].HelixCenter,
                             CurvStructs[c_k + 1].evec, CurvStructs[c_k + 1].theta, CurvStructs[c_k
                             + 1].pitch, CurvStructs[c_k + 1].CoeffP5, CurvStructs[c_k + 1].sp_index,
                             CurvStructs[c_k + 1].a_param, CurvStructs[c_k + 1].b_param, c_u_vec,
                             unusedU1, r1Dn, r2Dn);
            r16.set_size(3, r1Dn.size(1));
            c_N = r1Dn.size(1);
            for (int e_k = 0; e_k < c_N; e_k++) {
                r16[3 * e_k] = std::pow(r1Dn[3 * e_k], 2.0);
                r16[3 * e_k + 1] = std::pow(r1Dn[3 * e_k + 1], 2.0);
                r16[3 * e_k + 2] = std::pow(r1Dn[3 * e_k + 2], 2.0);
            }

            __m128d r18;
            double d3;
            int e_r1D;
            int g_r1D;
            coder::sum(r16, r1D_sqnorm);

            //  squared norm
            b_x = std::pow(CurvStructs[c_k + 1].FeedRate, 2.0);
            e_r1D = r1D.size(1);
            g_r1D = r1D.size(1);
            d3 = coder::b_norm(*(double (*)[3])&r1D[3 * (g_r1D - 1)]);
            r18 = _mm_loadu_pd(&r1D[3 * (e_r1D - 1)]);
            _mm_storeu_pd(&t_1[0], _mm_div_pd(r18, _mm_set1_pd(d3)));
            t_1[2] = r1D[3 * (r1D.size(1) - 1) + 2] / d3;

            //  unit tangent vector @ end of previous piece
            //
            wb_loop_ub = r2Dn.size(1);
            b_r2Dn.set_size(r2Dn.size(1));
            for (int i64 = 0; i64 < wb_loop_ub; i64++) {
                b_r2Dn[i64] = r2Dn[3 * i64];
            }

            coder::bsxfun(b_r2Dn, BasisVal, r1);
            xb_loop_ub = r1Dn.size(1);
            b_r1Dn.set_size(r1Dn.size(1));
            for (int i67 = 0; i67 < xb_loop_ub; i67++) {
                b_r1Dn[i67] = r1Dn[3 * i67];
            }

            coder::bsxfun(b_r1Dn, BasisValD, r2);
            R1.set_size(r1.size(0), r1.size(1));
            ac_loop_ub = r1.size(1);
            for (int i69 = 0; i69 < ac_loop_ub; i69++) {
                int dc_loop_ub;
                int h_scalarLB;
                int h_vectorUB;
                dc_loop_ub = r1.size(0);
                h_scalarLB = r1.size(0) & -2;
                h_vectorUB = h_scalarLB - 2;
                for (i72 = 0; i72 <= h_vectorUB; i72 += 2) {
                    __m128d r19;
                    __m128d r20;
                    r19 = _mm_loadu_pd(&r2[i72 + r2.size(0) * i69]);
                    r20 = _mm_loadu_pd(&r1[i72 + r1.size(0) * i69]);
                    _mm_storeu_pd(&R1[i72 + R1.size(0) * i69], _mm_add_pd(r20, _mm_mul_pd
                                   (_mm_set1_pd(0.5), r19)));
                }

                for (i72 = h_scalarLB; i72 < dc_loop_ub; i72++) {
                    R1[i72 + R1.size(0) * i69] = r1[i72 + r1.size(0) * i69] + 0.5 * r2[i72 + r2.size
                        (0) * i69];
                }
            }

            cc_loop_ub = r2Dn.size(1);
            b_r2Dn.set_size(r2Dn.size(1));
            for (int i71 = 0; i71 < cc_loop_ub; i71++) {
                b_r2Dn[i71] = r2Dn[3 * i71 + 1];
            }

            coder::bsxfun(b_r2Dn, BasisVal, r1);
            ec_loop_ub = r1Dn.size(1);
            b_r1Dn.set_size(r1Dn.size(1));
            for (int i73 = 0; i73 < ec_loop_ub; i73++) {
                b_r1Dn[i73] = r1Dn[3 * i73 + 1];
            }

            coder::bsxfun(b_r1Dn, BasisValD, r2);
            R2.set_size(r1.size(0), r1.size(1));
            fc_loop_ub = r1.size(1);
            for (int i74 = 0; i74 < fc_loop_ub; i74++) {
                int hc_loop_ub;
                int i_scalarLB;
                int i_vectorUB;
                hc_loop_ub = r1.size(0);
                i_scalarLB = r1.size(0) & -2;
                i_vectorUB = i_scalarLB - 2;
                for (i76 = 0; i76 <= i_vectorUB; i76 += 2) {
                    __m128d r21;
                    __m128d r22;
                    r21 = _mm_loadu_pd(&r2[i76 + r2.size(0) * i74]);
                    r22 = _mm_loadu_pd(&r1[i76 + r1.size(0) * i74]);
                    _mm_storeu_pd(&R2[i76 + R2.size(0) * i74], _mm_add_pd(r22, _mm_mul_pd
                                   (_mm_set1_pd(0.5), r21)));
                }

                for (i76 = i_scalarLB; i76 < hc_loop_ub; i76++) {
                    R2[i76 + R2.size(0) * i74] = r1[i76 + r1.size(0) * i74] + 0.5 * r2[i76 + r2.size
                        (0) * i74];
                }
            }

            gc_loop_ub = r2Dn.size(1);
            b_r2Dn.set_size(r2Dn.size(1));
            for (int i75 = 0; i75 < gc_loop_ub; i75++) {
                b_r2Dn[i75] = r2Dn[3 * i75 + 2];
            }

            coder::bsxfun(b_r2Dn, BasisVal, r1);
            ic_loop_ub = r1Dn.size(1);
            b_r1Dn.set_size(r1Dn.size(1));
            for (int i77 = 0; i77 < ic_loop_ub; i77++) {
                b_r1Dn[i77] = r1Dn[3 * i77 + 2];
            }

            coder::bsxfun(b_r1Dn, BasisValD, r2);
            R3.set_size(r1.size(0), r1.size(1));
            jc_loop_ub = r1.size(1);
            for (int i78 = 0; i78 < jc_loop_ub; i78++) {
                int j_scalarLB;
                int j_vectorUB;
                int kc_loop_ub;
                kc_loop_ub = r1.size(0);
                j_scalarLB = r1.size(0) & -2;
                j_vectorUB = j_scalarLB - 2;
                for (i80 = 0; i80 <= j_vectorUB; i80 += 2) {
                    __m128d r23;
                    __m128d r24;
                    r23 = _mm_loadu_pd(&r2[i80 + r2.size(0) * i78]);
                    r24 = _mm_loadu_pd(&r1[i80 + r1.size(0) * i78]);
                    _mm_storeu_pd(&R3[i80 + R3.size(0) * i78], _mm_add_pd(r24, _mm_mul_pd
                                   (_mm_set1_pd(0.5), r23)));
                }

                for (i80 = j_scalarLB; i80 < kc_loop_ub; i80++) {
                    R3[i80 + R3.size(0) * i78] = r1[i80 + r1.size(0) * i78] + 0.5 * r2[i80 + r2.size
                        (0) * i78];
                }
            }

            //
            varargin_3.set_size(R1.size(0), R1.size(1));
            lc_loop_ub = R1.size(1);
            for (int i79 = 0; i79 < lc_loop_ub; i79++) {
                int k_scalarLB;
                int k_vectorUB;
                int mc_loop_ub;
                mc_loop_ub = R1.size(0);
                k_scalarLB = R1.size(0) & -2;
                k_vectorUB = k_scalarLB - 2;
                for (i82 = 0; i82 <= k_vectorUB; i82 += 2) {
                    __m128d r25;
                    r25 = _mm_loadu_pd(&R1[i82 + R1.size(0) * i79]);
                    _mm_storeu_pd(&varargin_3[i82 + varargin_3.size(0) * i79], _mm_mul_pd(r25,
                                   _mm_set1_pd(-1.0)));
                }

                for (i82 = k_scalarLB; i82 < mc_loop_ub; i82++) {
                    varargin_3[i82 + varargin_3.size(0) * i79] = -R1[i82 + R1.size(0) * i79];
                }
            }

            varargin_5.set_size(R2.size(0), R2.size(1));
            nc_loop_ub = R2.size(1);
            for (int i81 = 0; i81 < nc_loop_ub; i81++) {
                int l_scalarLB;
                int l_vectorUB;
                int oc_loop_ub;
                oc_loop_ub = R2.size(0);
                l_scalarLB = R2.size(0) & -2;
                l_vectorUB = l_scalarLB - 2;
                for (i84 = 0; i84 <= l_vectorUB; i84 += 2) {
                    __m128d r26;
                    r26 = _mm_loadu_pd(&R2[i84 + R2.size(0) * i81]);
                    _mm_storeu_pd(&varargin_5[i84 + varargin_5.size(0) * i81], _mm_mul_pd(r26,
                                   _mm_set1_pd(-1.0)));
                }

                for (i84 = l_scalarLB; i84 < oc_loop_ub; i84++) {
                    varargin_5[i84 + varargin_5.size(0) * i81] = -R2[i84 + R2.size(0) * i81];
                }
            }

            varargin_7.set_size(R3.size(0), R3.size(1));
            pc_loop_ub = R3.size(1);
            for (int i83 = 0; i83 < pc_loop_ub; i83++) {
                int m_scalarLB;
                int m_vectorUB;
                int qc_loop_ub;
                qc_loop_ub = R3.size(0);
                m_scalarLB = R3.size(0) & -2;
                m_vectorUB = m_scalarLB - 2;
                for (i85 = 0; i85 <= m_vectorUB; i85 += 2) {
                    __m128d r27;
                    r27 = _mm_loadu_pd(&R3[i85 + R3.size(0) * i83]);
                    _mm_storeu_pd(&varargin_7[i85 + varargin_7.size(0) * i83], _mm_mul_pd(r27,
                                   _mm_set1_pd(-1.0)));
                }

                for (i85 = m_scalarLB; i85 < qc_loop_ub; i85++) {
                    varargin_7[i85 + varargin_7.size(0) * i83] = -R3[i85 + R3.size(0) * i83];
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

            a_tmp = (static_cast<double>(c_k) + 1.0) * 7.0;
            n_a = a_tmp * static_cast<double>(BasisVal.size(0)) + 1.0;
            b_tmp = ((static_cast<double>(c_k) + 1.0) + 1.0) * 7.0;
            c_b = b_tmp * static_cast<double>(BasisVal.size(0));
            if (c_b < n_a) {
                y.set_size(1, 0);
            } else {
                int rc_loop_ub;
                rc_loop_ub = static_cast<int>(c_b - n_a);
                y.set_size(1, (rc_loop_ub + 1));
                for (int i86 = 0; i86 <= rc_loop_ub; i86++) {
                    y[i86] = n_a + static_cast<double>(i86);
                }
            }

            o_a = (static_cast<double>(c_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
            d_b = ((static_cast<double>(c_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1));
            if (d_b < o_a) {
                b_y.set_size(1, 0);
            } else {
                int sc_loop_ub;
                sc_loop_ub = static_cast<int>(d_b - o_a);
                b_y.set_size(1, (sc_loop_ub + 1));
                for (int i87 = 0; i87 <= sc_loop_ub; i87++) {
                    b_y[i87] = o_a + static_cast<double>(i87);
                }
            }

            b_BasisVal.set_size(((((((i_input_sizes_idx_0 + j_input_sizes_idx_0) +
                k_input_sizes_idx_0) + l_input_sizes_idx_0) + m_input_sizes_idx_0) +
                                  n_input_sizes_idx_0) + o_input_sizes_idx_0), b_result);
            for (int i88 = 0; i88 < b_result; i88++) {
                for (int i90 = 0; i90 < i_input_sizes_idx_0; i90++) {
                    b_BasisVal[i90 + b_BasisVal.size(0) * i88] = BasisVal[i90 + i_input_sizes_idx_0 *
                        i88];
                }
            }

            for (int i89 = 0; i89 < b_result; i89++) {
                for (int i92 = 0; i92 < j_input_sizes_idx_0; i92++) {
                    b_BasisVal[(i92 + i_input_sizes_idx_0) + b_BasisVal.size(0) * i89] = R1[i92 +
                        j_input_sizes_idx_0 * i89];
                }
            }

            for (int i91 = 0; i91 < b_result; i91++) {
                for (int i94 = 0; i94 < k_input_sizes_idx_0; i94++) {
                    b_BasisVal[((i94 + i_input_sizes_idx_0) + j_input_sizes_idx_0) + b_BasisVal.size
                        (0) * i91] = varargin_3[i94 + k_input_sizes_idx_0 * i91];
                }
            }

            for (int i93 = 0; i93 < b_result; i93++) {
                for (int i96 = 0; i96 < l_input_sizes_idx_0; i96++) {
                    b_BasisVal[(((i96 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                                k_input_sizes_idx_0) + b_BasisVal.size(0) * i93] = R2[i96 +
                        l_input_sizes_idx_0 * i93];
                }
            }

            for (int i95 = 0; i95 < b_result; i95++) {
                for (int i98 = 0; i98 < m_input_sizes_idx_0; i98++) {
                    b_BasisVal[((((i98 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                                 k_input_sizes_idx_0) + l_input_sizes_idx_0) + b_BasisVal.size(0) *
                        i95] = varargin_5[i98 + m_input_sizes_idx_0 * i95];
                }
            }

            for (int i97 = 0; i97 < b_result; i97++) {
                for (int i100 = 0; i100 < n_input_sizes_idx_0; i100++) {
                    b_BasisVal[(((((i100 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                                  k_input_sizes_idx_0) + l_input_sizes_idx_0) + m_input_sizes_idx_0)
                        + b_BasisVal.size(0) * i97] = R3[i100 + n_input_sizes_idx_0 * i97];
                }
            }

            for (int i99 = 0; i99 < b_result; i99++) {
                for (int i101 = 0; i101 < o_input_sizes_idx_0; i101++) {
                    b_BasisVal[((((((i101 + i_input_sizes_idx_0) + j_input_sizes_idx_0) +
                                   k_input_sizes_idx_0) + l_input_sizes_idx_0) + m_input_sizes_idx_0)
                                + n_input_sizes_idx_0) + b_BasisVal.size(0) * i99] = varargin_7[i101
                        + o_input_sizes_idx_0 * i99];
                }
            }

            A->parenAssign(b_BasisVal, y, b_y);

            //
            d4 = a_tmp * static_cast<double>(BasisVal.size(0)) + 1.0;
            if (d4 > b_tmp * static_cast<double>(BasisVal.size(0))) {
                i102 = 0;
            } else {
                i102 = static_cast<int>(d4) - 1;
            }

            r12.set_size(r1D_sqnorm.size(1));
            tc_loop_ub = r1D_sqnorm.size(1);
            for (int i103 = 0; i103 < tc_loop_ub; i103++) {
                r12[i103] = r1D_sqnorm[i103];
            }

            unnamed_idx_1 = r12.size(0);
            uc_loop_ub = r12.size(0);
            for (int i104 = 0; i104 < uc_loop_ub; i104++) {
                b[i102 + i104] = b_x / r12[i104];
            }

            for (int i105 = 0; i105 < mb_loop_ub; i105++) {
                b[(i102 + i105) + unnamed_idx_1] = bC2[i105];
            }

            for (int i106 = 0; i106 < nb_loop_ub; i106++) {
                b[((i102 + i106) + unnamed_idx_1) + b_unnamed_idx_1] = bC2[i106];
            }

            for (int i107 = 0; i107 < pb_loop_ub; i107++) {
                b[(((i102 + i107) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1] = bC3[i107];
            }

            for (int i108 = 0; i108 < qb_loop_ub; i108++) {
                b[((((i102 + i108) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
                    d_unnamed_idx_1] = bC3[i108];
            }

            for (int i109 = 0; i109 < rb_loop_ub; i109++) {
                b[(((((i102 + i109) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
                    d_unnamed_idx_1) + e_unnamed_idx_1] = bC4[i109];
            }

            for (int i110 = 0; i110 < sb_loop_ub; i110++) {
                b[((((((i102 + i110) + unnamed_idx_1) + b_unnamed_idx_1) + c_unnamed_idx_1) +
                    d_unnamed_idx_1) + e_unnamed_idx_1) + f_unnamed_idx_1] = bC4[i110];
            }

            //
            vc_loop_ub = BasisVal.size(1);
            d5 = ((static_cast<double>(c_k) + 1.0) - 1.0) * static_cast<double>(BasisVal.size(1)) +
                1.0;
            if (d5 > (static_cast<double>(c_k) + 1.0) * static_cast<double>(BasisVal.size(1))) {
                i111 = 1;
            } else {
                i111 = static_cast<int>(d5);
            }

            i112 = static_cast<int>(static_cast<unsigned int>(c_k + 1) << 1);
            p_a = std::pow((t_1[0] * r1D[3 * (r1D.size(1) - 1)] + t_1[1] * r1D[3 * (r1D.size(1) - 1)
                            + 1]) + t_1[2] * r1D[3 * (r1D.size(1) - 1) + 2], 2.0);
            for (int i113 = 0; i113 < vc_loop_ub; i113++) {
                Aeq[i112 + Aeq.size(0) * ((i111 + i113) - 1)] = p_a * BasisVal[(BasisVal.size(0) +
                    BasisVal.size(0) * i113) - 1];
            }

            wc_loop_ub = BasisVal.size(1);
            d6 = (static_cast<double>(c_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
            if (d6 > ((static_cast<double>(c_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1)))
            {
                i114 = 1;
            } else {
                i114 = static_cast<int>(d6);
            }

            c = std::pow((t_1[0] * r1Dn[0] + t_1[1] * r1Dn[1]) + t_1[2] * r1Dn[2], 2.0);
            for (int i115 = 0; i115 < wc_loop_ub; i115++) {
                Aeq[i112 + Aeq.size(0) * ((i114 + i115) - 1)] = -c * BasisVal[BasisVal.size(0) *
                    i115];
            }

            q_a = r2D[3 * (r2D.size(1) - 1)];
            r_a = 0.5 * r1D[3 * (r1D.size(1) - 1)];
            s_a = r2D[3 * (r2D.size(1) - 1) + 1];
            t_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 1];
            u_a = r2D[3 * (r2D.size(1) - 1) + 2];
            v_a = 0.5 * r1D[3 * (r1D.size(1) - 1) + 2];
            xc_loop_ub = BasisVal.size(1);
            d7 = ((static_cast<double>(c_k) + 1.0) - 1.0) * static_cast<double>(BasisVal.size(1)) +
                1.0;
            if (d7 > (static_cast<double>(c_k) + 1.0) * static_cast<double>(BasisVal.size(1))) {
                i116 = 1;
            } else {
                i116 = static_cast<int>(d7);
            }

            g_a.set_size(3, BasisVal.size(1));
            for (int i117 = 0; i117 < xc_loop_ub; i117++) {
                double d8;
                double d9;
                d8 = BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i117) - 1];
                d9 = BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i117) - 1];
                g_a[3 * i117] = q_a * d8 + r_a * d9;
                g_a[3 * i117 + 1] = s_a * d8 + t_a * d9;
                g_a[3 * i117 + 2] = u_a * d8 + v_a * d9;
            }

            coder::internal::blas::mtimes(t_1, g_a, r15);
            yc_loop_ub = r15.size(1);
            for (int i118 = 0; i118 < yc_loop_ub; i118++) {
                Aeq[(i112 + Aeq.size(0) * ((i116 + i118) - 1)) + 1] = r15[i118];
            }

            //
            w_a = r2Dn[0];
            x_a = 0.5 * r1Dn[0];
            y_a = r2Dn[1];
            ab_a = 0.5 * r1Dn[1];
            bb_a = r2Dn[2];
            cb_a = 0.5 * r1Dn[2];
            ad_loop_ub = BasisVal.size(1);
            d10 = (static_cast<double>(c_k) + 1.0) * static_cast<double>(BasisVal.size(1)) + 1.0;
            if (d10 > ((static_cast<double>(c_k) + 1.0) + 1.0) * static_cast<double>(BasisVal.size(1)))
            {
                i119 = 1;
            } else {
                i119 = static_cast<int>(d10);
            }

            g_a.set_size(3, BasisVal.size(1));
            for (int i120 = 0; i120 < ad_loop_ub; i120++) {
                double d11;
                double d12;
                d11 = BasisVal[BasisVal.size(0) * i120];
                d12 = BasisValD[BasisValD.size(0) * i120];
                g_a[3 * i120] = w_a * d11 + x_a * d12;
                g_a[3 * i120 + 1] = y_a * d11 + ab_a * d12;
                g_a[3 * i120 + 2] = bb_a * d11 + cb_a * d12;
            }

            coder::internal::blas::mtimes(t_1, g_a, r15);
            bd_loop_ub = r15.size(1);
            for (int i121 = 0; i121 < bd_loop_ub; i121++) {
                Aeq[(i112 + Aeq.size(0) * ((i119 + i121) - 1)) + 1] = -r15[i121];
            }

            //
            r1D.set_size(3, r1Dn.size(1));
            cd_loop_ub = r1Dn.size(1);
            for (int i122 = 0; i122 < cd_loop_ub; i122++) {
                r1D[3 * i122] = r1Dn[3 * i122];
                r1D[3 * i122 + 1] = r1Dn[3 * i122 + 1];
                r1D[3 * i122 + 2] = r1Dn[3 * i122 + 2];
            }

            dd_loop_ub = r2Dn.size(1);
            r2D.set_size(3, r2Dn.size(1));
            for (int i123 = 0; i123 < dd_loop_ub; i123++) {
                r2D[3 * i123] = r2Dn[3 * i123];
                r2D[3 * i123 + 1] = r2Dn[3 * i123 + 1];
                r2D[3 * i123 + 2] = r2Dn[3 * i123 + 2];
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
            i62 = 0;
        } else {
            i62 = static_cast<int>(d1) - 1;
        }

        b_unnamed_idx_0 = Aeq.size(0) - 2;
        unnamed_idx_1 = Aeq.size(0) - 1;
        d_r1D = r1D.size(1);
        f_r1D = r1D.size(1);
        d2 = coder::b_norm(*(double (*)[3])&r1D[3 * (f_r1D - 1)]);
        r17 = _mm_loadu_pd(&r1D[3 * (d_r1D - 1)]);
        _mm_storeu_pd(&c_r1D[0], _mm_div_pd(r17, _mm_set1_pd(d2)));
        c_r1D[2] = r1D[3 * (r1D.size(1) - 1) + 2] / d2;
        tb_loop_ub = BasisVal.size(1);
        ub_loop_ub = BasisVal.size(1);
        vb_loop_ub = BasisVal.size(1);
        g_a.set_size(3, BasisVal.size(1));
        for (int i63 = 0; i63 < tb_loop_ub; i63++) {
            g_a[3 * i63] = h_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i63) - 1] + i_a *
                BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i63) - 1];
        }

        for (int i65 = 0; i65 < ub_loop_ub; i65++) {
            g_a[3 * i65 + 1] = j_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i65) - 1] + k_a
                * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i65) - 1];
        }

        for (int i66 = 0; i66 < vb_loop_ub; i66++) {
            g_a[3 * i66 + 2] = l_a * BasisVal[(BasisVal.size(0) + BasisVal.size(0) * i66) - 1] + m_a
                * BasisValD[(BasisValD.size(0) + BasisValD.size(0) * i66) - 1];
        }

        coder::internal::blas::mtimes(c_r1D, g_a, r15);
        yb_loop_ub = BasisVal.size(1);
        for (int i68 = 0; i68 < yb_loop_ub; i68++) {
            Aeq[b_unnamed_idx_0 + Aeq.size(0) * (i62 + i68)] = BasisVal[(BasisVal.size(0) +
                BasisVal.size(0) * i68) - 1];
        }

        bc_loop_ub = r15.size(1);
        for (int i70 = 0; i70 < bc_loop_ub; i70++) {
            Aeq[unnamed_idx_1 + Aeq.size(0) * (i62 + i70)] = r15[i70];
        }

        int b_beq;

        //
        b_beq = beq.size(0) - 1;
        beq[beq.size(0) - 2] = std::pow(v_1, 2.0) / r1D_sqnorm[r1D_sqnorm.size(1) - 1];
        beq[b_beq] = at_1;
    }

    //
    // Arguments    : int cfg_SplineDegree
    //                const ::coder::array<double, 2U> &points
    //                ::coder::array<double, 2U> &sp3D_CoeffX
    //                ::coder::array<double, 2U> &sp3D_CoeffY
    //                ::coder::array<double, 2U> &sp3D_CoeffZ
    //                int *sp3D_Bl_ncoeff
    //                ::coder::array<double, 2U> &sp3D_Bl_breakpoints
    //                unsigned long *sp3D_Bl_handle
    //                int *sp3D_Bl_degree
    //                ::coder::array<double, 2U> &sp3D_knots
    // Return Type  : void
    //
    static void CalcBspline_Lee(int cfg_SplineDegree, const ::coder::array<double, 2U> &points, ::
        coder::array<double, 2U> &sp3D_CoeffX, ::coder::array<double, 2U> &sp3D_CoeffY, ::coder::
        array<double, 2U> &sp3D_CoeffZ, int *sp3D_Bl_ncoeff, ::coder::array<double, 2U>
        &sp3D_Bl_breakpoints, unsigned long *sp3D_Bl_handle, int *sp3D_Bl_degree, ::coder::array<
        double, 2U> &sp3D_knots)
    {
        ::coder::array<double, 2U> A;
        ::coder::array<double, 2U> BasisVal;
        ::coder::array<double, 2U> BasisValDD0;
        ::coder::array<double, 2U> BasisValDD1;
        ::coder::array<double, 2U> b_y1;
        ::coder::array<double, 2U> b_z1;
        ::coder::array<double, 2U> breakpoints;
        ::coder::array<double, 2U> c_z1;
        ::coder::array<double, 2U> du;
        ::coder::array<double, 2U> r1;
        ::coder::array<double, 2U> x;
        ::coder::array<double, 2U> z1;
        ::coder::array<double, 1U> b_coef;
        ::coder::array<double, 1U> coeffs;
        ::coder::array<double, 1U> r2;
        ::coder::array<double, 1U> r3;
        ::coder::array<signed char, 2U> coef;
        double X[4];
        double b_sp3D_Bl_breakpoints;
        double tmp1;
        double unusedU1;
        double unusedU2;
        double unusedU3;
        double unusedU4;
        unsigned long Bl_handle;
        int N;
        int b_loop_ub;
        int c_N;
        int c_loop_ub;
        int d_loop_ub;
        int dimSize;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int i13;
        int i6;
        int i_loop_ub;
        int input_sizes_idx_0;
        int ixStart;
        int j_loop_ub;
        int l_loop_ub;
        int loop_ub;
        int m_loop_ub;
        int o_loop_ub;
        int scalarLB;
        int t_loop_ub;
        int u_loop_ub;
        unsigned int unnamed_idx_1;
        int v_loop_ub;
        int vectorUB;
        int w_loop_ub;
        int x_loop_ub;
        int y_loop_ub;
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
                        double work_data_idx_0;
                        int ixLead;
                        int iyLead;
                        ixLead = ixStart + 1;
                        iyLead = iyStart;
                        work_data_idx_0 = x[ixStart];
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

        sp3D_Bl_breakpoints.set_size(1, (c_z1.size(1) + 1));
        sp3D_Bl_breakpoints[0] = 0.0;
        c_loop_ub = c_z1.size(1);
        for (int i4 = 0; i4 < c_loop_ub; i4++) {
            sp3D_Bl_breakpoints[i4 + 1] = c_z1[i4];
        }

        if (sp3D_Bl_breakpoints.size(1) != 1) {
            int i5;
            i5 = sp3D_Bl_breakpoints.size(1);
            for (int e_k = 0; e_k <= i5 - 2; e_k++) {
                sp3D_Bl_breakpoints[e_k + 1] = sp3D_Bl_breakpoints[e_k] + sp3D_Bl_breakpoints[e_k +
                    1];
            }
        }

        b_sp3D_Bl_breakpoints = sp3D_Bl_breakpoints[sp3D_Bl_breakpoints.size(1) - 1];
        sp3D_Bl_breakpoints.set_size(1, sp3D_Bl_breakpoints.size(1));
        d_loop_ub = sp3D_Bl_breakpoints.size(1);
        scalarLB = sp3D_Bl_breakpoints.size(1) & -2;
        vectorUB = scalarLB - 2;
        for (i6 = 0; i6 <= vectorUB; i6 += 2) {
            __m128d b_r;
            b_r = _mm_loadu_pd(&sp3D_Bl_breakpoints[i6]);
            _mm_storeu_pd(&sp3D_Bl_breakpoints[i6], _mm_div_pd(b_r, _mm_set1_pd
                           (b_sp3D_Bl_breakpoints)));
        }

        for (i6 = scalarLB; i6 < d_loop_ub; i6++) {
            sp3D_Bl_breakpoints[i6] = sp3D_Bl_breakpoints[i6] / b_sp3D_Bl_breakpoints;
        }

        //  normalize knots to interval [0...1]
        sp3D_knots.set_size(1, (sp3D_Bl_breakpoints.size(1) + 6));
        sp3D_knots[0] = 0.0;
        sp3D_knots[1] = 0.0;
        sp3D_knots[2] = 0.0;
        e_loop_ub = sp3D_Bl_breakpoints.size(1);
        for (int i7 = 0; i7 < e_loop_ub; i7++) {
            sp3D_knots[i7 + 3] = sp3D_Bl_breakpoints[i7];
        }

        sp3D_knots[sp3D_Bl_breakpoints.size(1) + 3] = 1.0;
        sp3D_knots[sp3D_Bl_breakpoints.size(1) + 4] = 1.0;
        sp3D_knots[sp3D_Bl_breakpoints.size(1) + 5] = 1.0;
        breakpoints.set_size(1, sp3D_Bl_breakpoints.size(1));
        f_loop_ub = sp3D_Bl_breakpoints.size(1);
        for (int i8 = 0; i8 < f_loop_ub; i8++) {
            breakpoints[i8] = sp3D_Bl_breakpoints[i8];
        }

        c_bspline_create_with_breakpoints(&Bl_handle, cfg_SplineDegree, &breakpoints[0],
            sp3D_Bl_breakpoints.size(1));
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
            unnamed_idx_1 = static_cast<unsigned int>(sp3D_Bl_breakpoints.size(1));
        }

        for (int f_k = 0; f_k <= i13; f_k++) {
            int i22;
            int k_loop_ub;
            int n_loop_ub;
            int p_loop_ub;
            int q_loop_ub;
            int r_loop_ub;
            int s_loop_ub;

            //  evaluate basis functions at the knots
            coef.set_size(1, (N + 2));
            k_loop_ub = N + 2;
            for (int i14 = 0; i14 < k_loop_ub; i14++) {
                coef[i14] = 0;
            }

            coef[f_k] = 1;

            //      sp             = spmak(knots, coef);
            //      BasisVal(:, k) = spval(sp, u);          % tridiagonal matrix
            coeffs.set_size(coef.size(1));
            n_loop_ub = coef.size(1);
            for (int i17 = 0; i17 < n_loop_ub; i17++) {
                coeffs[i17] = coef[i17];
            }

            r1.set_size(1, (static_cast<int>(unnamed_idx_1)));
            p_loop_ub = static_cast<int>(unnamed_idx_1);
            for (int i21 = 0; i21 < p_loop_ub; i21++) {
                r1[i21] = 0.0;
            }

            i22 = sp3D_Bl_breakpoints.size(1);
            for (int g_k = 0; g_k < i22; g_k++) {
                double d1;
                double xk;
                d1 = sp3D_Bl_breakpoints[g_k];
                xk = d1;

                //  void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
                if (d1 < 0.0) {
                    printf("ERROR: C_BSPLINE_EVAL: X < 0 (%f)\n", d1);
                    fflush(stdout);
                    xk = 0.0;
                } else {
                    if (d1 > 1.0) {
                        printf("ERROR: C_BSPLINE_EVAL: X > 1 (%f)\n", d1);
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

            bspline_eval(Bl_handle, b_coef, &unusedU1, &unusedU2, &BasisValDD0[f_k]);
            unusedU3 = 1.0;
            b_coef.set_size(coef.size(1));
            s_loop_ub = coef.size(1);
            for (int i25 = 0; i25 < s_loop_ub; i25++) {
                b_coef[i25] = coef[i25];
            }

            bspline_eval(Bl_handle, b_coef, &unusedU3, &unusedU4, &BasisValDD1[f_k]);

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
        l_loop_ub = BasisValDD0.size(1);
        for (int i15 = 0; i15 < l_loop_ub; i15++) {
            A[A.size(0) * i15] = BasisValDD0[i15];
        }

        m_loop_ub = BasisValDD0.size(1);
        for (int i16 = 0; i16 < m_loop_ub; i16++) {
            for (int i18 = 0; i18 < input_sizes_idx_0; i18++) {
                A[(i18 + A.size(0) * i16) + 1] = BasisVal[i18 + input_sizes_idx_0 * i16];
            }
        }

        o_loop_ub = BasisValDD0.size(1);
        for (int i19 = 0; i19 < o_loop_ub; i19++) {
            for (int i20 = 0; i20 < 1; i20++) {
                A[(input_sizes_idx_0 + A.size(0) * i19) + 1] = BasisValDD1[i19];
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
        coder::mldivide(A, r2, r3);
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
        coder::mldivide(A, r2, r3);
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
        coder::mldivide(A, r2, r3);
        sp3D_CoeffZ.set_size(1, r3.size(0));
        y_loop_ub = r3.size(0);
        for (int i31 = 0; i31 < y_loop_ub; i31++) {
            sp3D_CoeffZ[i31] = r3[i31];
        }

        int b_sp3D_Bl_ncoeff;
        b_sp3D_Bl_ncoeff = (sp3D_Bl_breakpoints.size(1) + cfg_SplineDegree) - 2;
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
        double b[3];
        double n_tmp;

        //  computes the local Frenet frame (t, n, b) of a curve in R^3
        //  [t, n, b, kappa] = CalcFrenet(rD1, rD2)
        //  where rD1 is the first derivative and rD2 the second one
        n_tmp = std::sqrt((std::pow(rD1[0], 2.0) + std::pow(rD1[1], 2.0)) + std::pow(rD1[2], 2.0));
        sqrt_calls++;

        //  tangential unit vector
        //
        t[0] = rD1[0] / n_tmp;
        t[1] = rD1[1] / n_tmp;
        t[2] = rD1[2] / n_tmp;
        sqrt_calls++;
        if (std::abs(std::abs((t[0] * rD2[0] + t[1] * rD2[1]) + t[2] * rD2[2]) - std::sqrt((std::pow
                (rD2[0], 2.0) + std::pow(rD2[1], 2.0)) + std::pow(rD2[2], 2.0))) >
                2.2204460492503131E-16) {
            __m128d r;
            double b_b_tmp;
            double b_n_tmp;
            double b_tmp;
            double c_b_tmp;

            //  regular case
            b_tmp = rD1[1] * rD2[2] - rD1[2] * rD2[1];
            b[0] = b_tmp;
            b_b_tmp = rD1[2] * rD2[0] - rD1[0] * rD2[2];
            b[1] = b_b_tmp;
            c_b_tmp = rD1[0] * rD2[1] - rD1[1] * rD2[0];
            b[2] = c_b_tmp;
            b_n_tmp = std::sqrt((std::pow(b_tmp, 2.0) + std::pow(b_b_tmp, 2.0)) + std::pow(c_b_tmp,
                                 2.0));
            sqrt_calls++;
            r = _mm_loadu_pd(&b[0]);
            _mm_storeu_pd(&b[0], _mm_div_pd(r, _mm_set1_pd(b_n_tmp)));
            b[2] /= b_n_tmp;

            //  binormal unit vector
            n[0] = b[1] * t[2] - b[2] * t[1];
            n[1] = b[2] * t[0] - b[0] * t[2];
            n[2] = b[0] * t[1] - b[1] * t[0];

            //  normal unit vector
            sqrt_calls++;
            sqrt_calls++;
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
    //                const double Curv_HelixCenter[3]
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
        const double Curv_P0[3], const double Curv_P1[3], const double Curv_HelixCenter[3], const
        double Curv_evec[3], double Curv_theta, double Curv_pitch, const double Curv_CoeffP5[6][3],
        int Curv_sp_index, bool Curv_UseConstJerk, double Curv_ConstJerk, double Curv_a_param,
        double Curv_b_param, double JerkScale, double *v_0, double *at_0)
    {
        static const char b_message[50]{
            'C', 'a', 'l', 'c', 'Z', 'e', 'r', 'o', 'S', 't', 'a', 'r', 't', 'C', 'o', 'n', 's', 't',
                'r', 'a', 'i', 'n', 't', 's', ':', ' ', 'C', 'a', 'l', 'l', 'e', 'd', ' ', 'o', 'n',
                ' ', 'n', 'o', 'n', '-', 'c', 'o', 'n', 's', 't', ' ', 'j', 'e', 'r', 'k'
        };

        double r1D[3];
        double r2D[3];
        double unusedU0[3];
        double absxk;
        double b;
        double b_b;
        double b_t;
        double d1uk;
        double jps;
        double n;
        double scale;
        double t;
        char message[50];
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
        b_EvalCurvStruct(ctx_q_splines, Curv_Type, Curv_P0, Curv_P1, Curv_HelixCenter, Curv_evec,
                         Curv_theta, Curv_pitch, Curv_CoeffP5, Curv_sp_index, Curv_a_param,
                         Curv_b_param, unusedU0, r1D, r2D);
        b_b = std::pow(d1uk, 2.0);
        *v_0 = std::sqrt((std::pow(r1D[0] * d1uk, 2.0) + std::pow(r1D[1] * d1uk, 2.0)) + std::pow
                         (r1D[2] * d1uk, 2.0));
        sqrt_calls++;
        n = std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0));
        sqrt_calls++;
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
        double b_beta0_tmp;
        double b_beta0_tmp_tmp;
        double b_beta1_tmp;
        double beta0_tmp;
        double beta0_tmp_tmp;
        double beta1_tmp;
        double c_beta0_tmp;
        double c_beta0_tmp_tmp;
        double c_beta1_tmp;
        double d;
        double d1;
        double d10;
        double d11;
        double d12;
        double d13;
        double d14;
        double d15;
        double d16;
        double d2;
        double d3;
        double d4;
        double d5;
        double d6;
        double d7;
        double d8;
        double d9;
        double d_beta0_tmp;
        double d_beta0_tmp_tmp;
        double e_beta0_tmp;
        double e_beta0_tmp_tmp;
        double f_beta0_tmp;
        double f_beta0_tmp_tmp;
        double g_beta0_tmp;
        double g_beta0_tmp_tmp;
        double h_beta0_tmp;
        double h_beta0_tmp_tmp;
        double i_beta0_tmp;
        double i_beta0_tmp_tmp;
        double j_beta0_tmp;
        double j_beta0_tmp_tmp;
        double k_beta0_tmp;
        double l_beta0_tmp;
        double m_beta0_tmp;
        double n_beta0_tmp;
        double o_beta0_tmp;
        double p_beta0_tmp;
        double q_beta0_tmp;
        double r_beta0_tmp;
        double s_beta0_tmp;
        double t2;
        double t29;
        double t3;
        double t4;
        double t5;
        double t6;
        double t7;
        double t8;
        double t9;
        double t_beta0_tmp;
        double u_beta0_tmp;

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
    // Arguments    : const FeedoptContext *ctx
    // Return Type  : void
    //
    static void CheckCurvStructs(const FeedoptContext *ctx)
    {
        CurvStruct Curv1;
        CurvStruct Curv2;
        double r0D1[3];
        double r1D1[3];
        double unusedU0[3];
        double unusedU1[3];
        double b_y;
        double d;
        double y;
        unsigned int N;
        int i;
        N = ctx->q_gcode.size();

        //  1 -> stdout
        //  2 -> stderr
        if ((static_cast<unsigned long>(DebugConfig) & 1UL) != 0UL) {
            printf("Checking for cusps...\n");
            fflush(stdout);
        }

        i = static_cast<int>(N - 1U);
        for (int k = 0; k < i; k++) {
            double absxk;
            double b_absxk;
            double b_scale;
            double b_t;
            double scale;
            double t;
            ctx->q_gcode.get((k + 1U), (&Curv1));
            ctx->q_gcode.get((k - 4294967294U), (&Curv2));
            c_EvalCurvStruct(&ctx->q_splines, Curv1.Type, Curv1.P0, Curv1.P1, Curv1.HelixCenter,
                             Curv1.evec, Curv1.theta, Curv1.pitch, Curv1.CoeffP5, Curv1.sp_index,
                             Curv1.a_param, Curv1.b_param, unusedU0, r0D1);
            b_EvalCurvStruct(&ctx->q_splines, Curv2.Type, Curv2.P0, Curv2.P1, Curv2.HelixCenter,
                             Curv2.evec, Curv2.theta, Curv2.pitch, Curv2.CoeffP5, Curv2.sp_index,
                             Curv2.a_param, Curv2.b_param, unusedU1, r1D1);
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
            coder::b_cosd(&d);
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
        double CoefPS_tmp;
        double CoefPS_tmp_tmp;
        double CoefPS_tmp_tmp_tmp;
        double ab_CoefPS_tmp;
        double ac_CoefPS_tmp;
        double b_CoefPS_tmp;
        double b_CoefPS_tmp_tmp;
        double b_t201_tmp;
        double b_t203_tmp;
        double bb_CoefPS_tmp;
        double bc_CoefPS_tmp;
        double c_CoefPS_tmp;
        double c_CoefPS_tmp_tmp;
        double c_t201_tmp;
        double c_t203_tmp;
        double cb_CoefPS_tmp;
        double cc_CoefPS_tmp;
        double d;
        double d1;
        double d10;
        double d100;
        double d101;
        double d102;
        double d103;
        double d104;
        double d105;
        double d106;
        double d107;
        double d108;
        double d109;
        double d11;
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
        double d12;
        double d13;
        double d14;
        double d15;
        double d16;
        double d17;
        double d18;
        double d19;
        double d2;
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
        double d3;
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
        double d4;
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
        double d5;
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
        double d6;
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
        double d7;
        double d70;
        double d71;
        double d72;
        double d73;
        double d74;
        double d75;
        double d76;
        double d77;
        double d78;
        double d79;
        double d8;
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
        double d9;
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
        double d_CoefPS_tmp;
        double d_CoefPS_tmp_tmp;
        double d_t203_tmp;
        double db_CoefPS_tmp;
        double dc_CoefPS_tmp;
        double e_CoefPS_tmp;
        double e_CoefPS_tmp_tmp;
        double e_t203_tmp;
        double eb_CoefPS_tmp;
        double ec_CoefPS_tmp;
        double f_CoefPS_tmp;
        double f_CoefPS_tmp_tmp;
        double f_t203_tmp;
        double fb_CoefPS_tmp;
        double fc_CoefPS_tmp;
        double g_CoefPS_tmp;
        double g_CoefPS_tmp_tmp;
        double g_t203_tmp;
        double gb_CoefPS_tmp;
        double gc_CoefPS_tmp;
        double h_CoefPS_tmp;
        double h_t203_tmp;
        double hb_CoefPS_tmp;
        double hc_CoefPS_tmp;
        double i_CoefPS_tmp;
        double i_t203_tmp;
        double ib_CoefPS_tmp;
        double ic_CoefPS_tmp;
        double j_CoefPS_tmp;
        double jb_CoefPS_tmp;
        double jc_CoefPS_tmp;
        double k_CoefPS_tmp;
        double kb_CoefPS_tmp;
        double l_CoefPS_tmp;
        double lb_CoefPS_tmp;
        double m_CoefPS_tmp;
        double mb_CoefPS_tmp;
        double n_CoefPS_tmp;
        double nb_CoefPS_tmp;
        double o_CoefPS_tmp;
        double ob_CoefPS_tmp;
        double p_CoefPS_tmp;
        double pb_CoefPS_tmp;
        double q_CoefPS_tmp;
        double qb_CoefPS_tmp;
        double r_CoefPS_tmp;
        double rb_CoefPS_tmp;
        double s_CoefPS_tmp;
        double sb_CoefPS_tmp;
        double t10;
        double t111;
        double t14;
        double t15;
        double t16;
        double t17;
        double t18;
        double t19;
        double t2;
        double t20;
        double t201;
        double t201_tmp;
        double t203;
        double t203_tmp;
        double t205;
        double t205_tmp;
        double t21;
        double t22;
        double t23;
        double t24;
        double t25;
        double t26;
        double t27;
        double t28;
        double t29;
        double t3;
        double t30;
        double t31;
        double t32;
        double t32_tmp;
        double t33;
        double t33_tmp;
        double t34;
        double t35;
        double t36;
        double t37;
        double t37_tmp;
        double t38;
        double t39;
        double t4;
        double t40;
        double t41;
        double t42;
        double t43;
        double t44;
        double t44_tmp;
        double t45;
        double t46;
        double t46_tmp;
        double t47;
        double t48;
        double t48_tmp;
        double t49;
        double t5;
        double t50;
        double t50_tmp;
        double t51;
        double t52;
        double t52_tmp;
        double t53;
        double t54;
        double t54_tmp;
        double t55;
        double t6;
        double t7;
        double t8;
        double t83;
        double t83_tmp;
        double t84;
        double t84_tmp;
        double t85;
        double t85_tmp;
        double t86;
        double t86_tmp;
        double t87;
        double t88;
        double t88_tmp;
        double t89;
        double t9;
        double t90;
        double t91;
        double t91_tmp;
        double t_CoefPS_tmp;
        double tb_CoefPS_tmp;
        double u_CoefPS_tmp;
        double ub_CoefPS_tmp;
        double v_CoefPS_tmp;
        double vb_CoefPS_tmp;
        double w_CoefPS_tmp;
        double wb_CoefPS_tmp;
        double x_CoefPS_tmp;
        double xb_CoefPS_tmp;
        double y_CoefPS_tmp;
        double yb_CoefPS_tmp;

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
        ::coder::array<double, 2U> d_pvec;
        ::coder::array<double, 2U> pvec;
        CurvStruct C;
        CurvStruct Curv;
        CurvStruct CurvStruct1_C;
        CurvStruct CurvStruct2_C;
        CurvStruct CurvStruct3_C;
        CurvStruct SplineCurve;
        CurvStruct b_CurvStruct2_C;
        CurvStruct b_ctx;
        CurvStruct spline;
        double dv2[6][3];
        double P0[3];
        double P1[3];
        double dv[3];
        double dv1[3];
        double CumulatedLength;
        if (!ctx->q_gcode.isempty()) {
            double spindle_speed;
            unsigned int Ncrv;
            unsigned int spline_index;
            spline_index = ctx->q_splines.size() + 1U;
            Ncrv = ctx->q_gcode.size();
            CumulatedLength = 0.0;

            //  [mm]
            //  1 -> stdout
            //  2 -> stderr
            if ((static_cast<unsigned long>(DebugConfig) & 1UL) != 0UL) {
                printf("Compressing...\n");
                fflush(stdout);
            }

            spindle_speed = 75000.0;

            //  Satisfy coder
            //  -------------
            pvec.set_size(3, 0);
            ctx->q_gcode.get((static_cast<double>(1.0)), (&b_ctx));

            //  -------------
            for (double k = 1.0; k <= Ncrv; k++) {
                ctx->q_gcode.get(k, (&Curv));
                if ((LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, Curv.Type, Curv.P0,
                                Curv.P1, Curv.HelixCenter, Curv.evec, Curv.theta, Curv.pitch,
                                Curv.CoeffP5, Curv.sp_index, Curv.a_param, Curv.b_param) >=
                        ctx->cfg.LThreshold) || (Curv.zspdmode != ZSpdMode_NN)) {
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
                            int c_pvec;
                            ConstrCurvStructType(&SplineCurve);
                            CalcBspline_Lee(ctx->cfg.SplineDegree, pvec, SplineCurve.sp.CoeffX,
                                            SplineCurve.sp.CoeffY, SplineCurve.sp.CoeffZ,
                                            &SplineCurve.sp.Bl.ncoeff, SplineCurve.sp.Bl.breakpoints,
                                            &SplineCurve.sp.Bl.handle, &SplineCurve.sp.Bl.degree,
                                            SplineCurve.sp.knots);
                            ctx->q_splines.push((&SplineCurve));
                            c_pvec = pvec.size(1);
                            dv[0] = 0.0;
                            dv1[0] = 0.0;
                            dv[1] = 0.0;
                            dv1[1] = 0.0;
                            dv[2] = 0.0;
                            dv1[2] = 0.0;
                            for (int i2 = 0; i2 < 6; i2++) {
                                dv2[i2][0] = 0.0;
                                dv2[i2][1] = 0.0;
                                dv2[i2][2] = 0.0;
                            }

                            ConstrCurvStruct(CurveType_Spline, ZSpdMode_NN, *(double (*)[3])&pvec[0],
                                             *(double (*)[3])&pvec[3 * (c_pvec - 1)], dv, dv1, 0.0,
                                             0.0, dv2, Curv.FeedRate, &spline);
                            spline.gcode_source_line = Curv.gcode_source_line;
                            spline.sp_index = static_cast<int>(spline_index);
                            spline_index++;
                            spline.SpindleSpeed = spindle_speed;
                            spindle_speed = 75000.0;
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
                    int b_pvec;
                    ConstrCurvStructType(&SplineCurve);
                    CalcBspline_Lee(ctx->cfg.SplineDegree, pvec, SplineCurve.sp.CoeffX,
                                    SplineCurve.sp.CoeffY, SplineCurve.sp.CoeffZ,
                                    &SplineCurve.sp.Bl.ncoeff, SplineCurve.sp.Bl.breakpoints,
                                    &SplineCurve.sp.Bl.handle, &SplineCurve.sp.Bl.degree,
                                    SplineCurve.sp.knots);
                    ctx->q_splines.push((&SplineCurve));
                    b_pvec = pvec.size(1);
                    dv[0] = 0.0;
                    dv1[0] = 0.0;
                    dv[1] = 0.0;
                    dv1[1] = 0.0;
                    dv[2] = 0.0;
                    dv1[2] = 0.0;
                    for (int i1 = 0; i1 < 6; i1++) {
                        dv2[i1][0] = 0.0;
                        dv2[i1][1] = 0.0;
                        dv2[i1][2] = 0.0;
                    }

                    ConstrCurvStruct(CurveType_Spline, ZSpdMode_NN, *(double (*)[3])&pvec[0],
                                     *(double (*)[3])&pvec[3 * (b_pvec - 1)], dv, dv1, 0.0, 0.0, dv2,
                                     Curv.FeedRate, &spline);
                    spline.gcode_source_line = Curv.gcode_source_line;
                    spline.sp_index = static_cast<int>(spline_index);
                    spline.SpindleSpeed = spindle_speed;
                    ctx->q_compress.push((&spline));
                } else if (k == 1.0) {
                    ctx->q_compress.push((&Curv));
                } else {
                    int b_loop_ub;
                    int loop_ub;
                    if (CumulatedLength == 0.0) {
                        b_EvalCurvStruct(&ctx->q_splines, Curv.Type, Curv.P0, Curv.P1,
                                         Curv.HelixCenter, Curv.evec, Curv.theta, Curv.pitch,
                                         Curv.CoeffP5, Curv.sp_index, Curv.b_param, P0);
                        pvec.set_size(3, 1);
                        pvec[0] = P0[0];
                        pvec[1] = P0[1];
                        pvec[2] = P0[2];
                        spindle_speed = Curv.SpindleSpeed;
                    }

                    CumulatedLength += LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                        Curv.Type, Curv.P0, Curv.P1, Curv.HelixCenter, Curv.evec, Curv.theta,
                        Curv.pitch, Curv.CoeffP5, Curv.sp_index, Curv.a_param, Curv.b_param);
                    b_EvalCurvStruct(&ctx->q_splines, Curv.Type, Curv.P0, Curv.P1, Curv.HelixCenter,
                                     Curv.evec, Curv.theta, Curv.pitch, Curv.CoeffP5, Curv.sp_index,
                                     Curv.a_param, Curv.b_param, P1);
                    d_pvec.set_size(3, (pvec.size(1) + 1));
                    loop_ub = pvec.size(1);
                    for (int i = 0; i < loop_ub; i++) {
                        d_pvec[3 * i] = pvec[3 * i];
                        d_pvec[3 * i + 1] = pvec[3 * i + 1];
                        d_pvec[3 * i + 2] = pvec[3 * i + 2];
                    }

                    d_pvec[3 * pvec.size(1)] = P1[0];
                    d_pvec[3 * pvec.size(1) + 1] = P1[1];
                    d_pvec[3 * pvec.size(1) + 2] = P1[2];
                    pvec.set_size(3, d_pvec.size(1));
                    b_loop_ub = d_pvec.size(1);
                    for (int i3 = 0; i3 < b_loop_ub; i3++) {
                        pvec[3 * i3] = d_pvec[3 * i3];
                        pvec[3 * i3 + 1] = d_pvec[3 * i3 + 1];
                        pvec[3 * i3 + 2] = d_pvec[3 * i3 + 2];
                    }

                    spindle_speed = std::fmin(spindle_speed, Curv.SpindleSpeed);
                }
            }
        }
    }

    //
    // ctxType = coder.OutputType('InitFeedoptPlan');
    // Arguments    : CurveType Type
    //                ZSpdMode b_ZSpdMode
    //                const double P0[3]
    //                const double P1[3]
    //                const double C[3]
    //                const double evec[3]
    //                double theta
    //                double pitch
    //                const double CoeffP5[6][3]
    //                double FeedRate
    //                CurvStruct *CStrct
    // Return Type  : void
    //
    static void ConstrCurvStruct(CurveType Type, ZSpdMode b_ZSpdMode, const double P0[3], const
        double P1[3], const double C[3], const double evec[3], double theta, double pitch, const
        double CoeffP5[6][3], double FeedRate, CurvStruct *CStrct)
    {
        CStrct->Type = Type;
        CStrct->zspdmode = b_ZSpdMode;
        CStrct->P0[0] = P0[0];
        CStrct->P1[0] = P1[0];
        CStrct->HelixCenter[0] = C[0];
        CStrct->evec[0] = evec[0];
        CStrct->P0[1] = P0[1];
        CStrct->P1[1] = P1[1];
        CStrct->HelixCenter[1] = C[1];
        CStrct->evec[1] = evec[1];
        CStrct->P0[2] = P0[2];
        CStrct->P1[2] = P1[2];
        CStrct->HelixCenter[2] = C[2];
        CStrct->evec[2] = evec[2];
        CStrct->theta = theta;
        CStrct->pitch = pitch;
        for (int i = 0; i < 6; i++) {
            CStrct->CoeffP5[i][0] = CoeffP5[i][0];
            CStrct->CoeffP5[i][1] = CoeffP5[i][1];
            CStrct->CoeffP5[i][2] = CoeffP5[i][2];
        }

        CStrct->sp_index = 1;
        CStrct->FeedRate = FeedRate;
        CStrct->SpindleSpeed = 0.0;
        CStrct->MaxConstantFeedRate = 0.0;
        CStrct->i_begin_sp = 0;
        CStrct->i_end_sp = 0;
        CStrct->gcode_source_line = 0;
        CStrct->index_smooth = 0;
        CStrct->UseConstJerk = false;
        CStrct->ConstJerk = 0.0;
        CStrct->ConstJerkMaxIterations = 0;
        CStrct->Coeff.set_size(0);
        CStrct->a_param = 1.0;
        CStrct->b_param = 0.0;
        CStrct->sp.CoeffX.set_size(1, 1);
        CStrct->sp.CoeffX[0] = 0.0;
        CStrct->sp.CoeffY.set_size(1, 1);
        CStrct->sp.CoeffY[0] = 0.0;
        CStrct->sp.CoeffZ.set_size(1, 1);
        CStrct->sp.CoeffZ[0] = 0.0;
        CStrct->sp.Bl.ncoeff = 0;
        CStrct->sp.Bl.breakpoints.set_size(1, 0);
        CStrct->sp.Bl.handle = 0UL;
        CStrct->sp.Bl.degree = 0;
        CStrct->sp.knots.set_size(1, 1);
        CStrct->sp.knots[0] = 0.0;
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
        ::coder::array<double, 2U> Integrand;
        ::coder::array<double, 2U> du_tilda;
        ::coder::array<double, 2U> u_mid_tilda;
        CurvStruct b_ctx_q_splines;
        double r1D0[3];
        double r1D1[3];
        double unusedU0[3];
        double unusedU1[3];
        double L;
        double L_tot;
        double u0_tilda;
        double u1_tilda;
        if (b_CurvStruct->Type == CurveType_Spline) {
            ctx_q_splines->get(b_CurvStruct->sp_index, (&b_ctx_q_splines));

            //  discretizing along the total spline
            //  from u=0 to u=1
            SplineLengthApprox(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->sp_index,
                               b_CurvStruct->b_param, b_CurvStruct->a_param + b_CurvStruct->b_param,
                               &L_tot, Integrand, u_mid_tilda, du_tilda);
            u0_tilda = b_CurvStruct->b_param;
            if (d1 != 0.0) {
                unsigned int k;

                //  spline-long length calculation by rectangles method
                //  beginning from u=0
                //  until L_tot-d1 is reached
                L = 0.0;
                k = 1U;
                while ((L < L_tot - d1) && (k <= static_cast<unsigned int>(du_tilda.size(1)))) {
                    L += Integrand[static_cast<int>(k) - 1] * du_tilda[static_cast<int>(k) - 1];
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
            b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                             b_CurvStruct->HelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                             b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                             b_CurvStruct->a_param, b_CurvStruct->b_param, unusedU0, r1D0);
            c_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                             b_CurvStruct->HelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                             b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                             b_CurvStruct->a_param, b_CurvStruct->b_param, unusedU1, r1D1);

            //  d0 = Integral_0_u0 ||r'(u)||du
            //  d1 = Integral_u1_1 ||r'(u)||du
            sqrt_calls++;
            sqrt_calls++;

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
    //                CurvStruct *CurvStruct1
    //                CurvStruct *CurvStruct2
    // Return Type  : void
    //
    static void CutZeroEnd(const queue_coder *ctx_q_gcode, const queue_coder *ctx_q_splines, int
                           ctx_cfg_NHorz, const double ctx_cfg_amax[3], const double ctx_cfg_jmax[3],
                           double ctx_cfg_dt, double ctx_cfg_ZeroStartAccLimit, double
                           ctx_cfg_ZeroStartJerkLimit, double ctx_cfg_ZeroStartVelLimit, double
                           ctx_cfg_NGridLengthSpline, const CurvStruct *b_CurvStruct, CurvStruct
                           *CurvStruct1, CurvStruct *CurvStruct2)
    {
        ::coder::array<double, 2U> a;
        ::coder::array<double, 2U> at;
        ::coder::array<double, 2U> b_a;
        ::coder::array<double, 2U> b_d1uk;
        ::coder::array<double, 2U> b_r1D;
        ::coder::array<double, 2U> b_uk;
        ::coder::array<double, 2U> b_x;
        ::coder::array<double, 2U> b_z1;
        ::coder::array<double, 2U> c;
        ::coder::array<double, 2U> d1uk;
        ::coder::array<double, 2U> d2uk;
        ::coder::array<double, 2U> jt;
        ::coder::array<double, 2U> r2D;
        ::coder::array<double, 2U> r3;
        ::coder::array<double, 2U> r3D;
        ::coder::array<double, 2U> r7;
        ::coder::array<double, 2U> t;
        ::coder::array<double, 2U> uk;
        ::coder::array<double, 2U> unusedU1;
        ::coder::array<double, 2U> x;
        ::coder::array<double, 2U> z1;
        ::coder::array<double, 1U> max_at;
        ::coder::array<double, 1U> max_jt;
        ::coder::array<bool, 2U> b_max_at;
        ::coder::array<bool, 2U> b_max_jt;
        ::coder::array<bool, 2U> c_x;
        CurvStruct expl_temp;
        double r1D[3];
        double unusedU0[3];
        double L;
        double b_ex;
        double b_vmax;
        double ex;
        double ex_tmp;
        double jps;
        double tmax;
        double z1_idx_1;
        double z1_idx_2;
        unsigned long c_N;
        unsigned long c_k;
        int x_data[3];
        int cut_index_vel_size[2];
        int cut_index_acc_data[1];
        int cut_index_jerk_data[1];
        int cut_index_vel_data[1];
        int N;
        int b_N;
        int b_loop_ub;
        int b_m;
        int b_scalarLB;
        int b_vectorUB;
        int c_ex;
        int c_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int cut_index;
        int cut_index_acc_size_idx_1;
        int cut_index_jerk_size_idx_1;
        int d_N;
        int d_loop_ub;
        int d_scalarLB;
        int d_vectorUB;
        int e_N;
        int e_loop_ub;
        int e_scalarLB;
        int e_vectorUB;
        int f_N;
        int f_loop_ub;
        int g_loop_ub;
        int i1;
        int i2;
        int i21;
        int i3;
        int i6;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        int m;
        int m_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        int p_k;
        int p_loop_ub;
        int scalarLB;
        int vectorUB;
        bool exitg1;
        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->HelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                         b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                         b_CurvStruct->a_param, b_CurvStruct->b_param, unusedU0, r1D);
        z1_idx_1 = std::abs(r1D[1]);
        z1_idx_2 = std::abs(r1D[2]);
        ex = ctx_cfg_jmax[0];
        ex_tmp = std::abs(r1D[0]);
        b_ex = ex_tmp;
        if (ctx_cfg_jmax[0] > ctx_cfg_jmax[1]) {
            ex = ctx_cfg_jmax[1];
        }

        if (ex_tmp < z1_idx_1) {
            b_ex = z1_idx_1;
        }

        if (ex > ctx_cfg_jmax[2]) {
            ex = ctx_cfg_jmax[2];
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
            coder::b_eml_float_colon(tmax, -ctx_cfg_dt, t);
        }

        z1.set_size(1, t.size(1));
        N = t.size(1);
        for (int k = 0; k < N; k++) {
            z1[k] = std::pow(t[k], 3.0);
        }

        uk.set_size(1, z1.size(1));
        b_loop_ub = z1.size(1);
        scalarLB = z1.size(1) & -2;
        vectorUB = scalarLB - 2;
        for (i1 = 0; i1 <= vectorUB; i1 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&z1[i1]);
            _mm_storeu_pd(&uk[i1], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r), _mm_set1_pd(6.0)));
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
        b_scalarLB = z1.size(1) & -2;
        b_vectorUB = b_scalarLB - 2;
        for (i2 = 0; i2 <= b_vectorUB; i2 += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&z1[i2]);
            _mm_storeu_pd(&d1uk[i2], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r1), _mm_set1_pd(2.0)));
        }

        for (i2 = b_scalarLB; i2 < c_loop_ub; i2++) {
            d1uk[i2] = jps * z1[i2] / 2.0;
        }

        d2uk.set_size(1, t.size(1));
        d_loop_ub = t.size(1);
        c_scalarLB = t.size(1) & -2;
        c_vectorUB = c_scalarLB - 2;
        for (i3 = 0; i3 <= c_vectorUB; i3 += 2) {
            __m128d r2;
            r2 = _mm_loadu_pd(&t[i3]);
            _mm_storeu_pd(&d2uk[i3], _mm_mul_pd(_mm_set1_pd(jps), r2));
        }

        for (i3 = c_scalarLB; i3 < d_loop_ub; i3++) {
            d2uk[i3] = jps * t[i3];
        }

        b_uk.set_size(1, uk.size(1));
        e_loop_ub = uk.size(1) - 1;
        for (int i4 = 0; i4 <= e_loop_ub; i4++) {
            b_uk[i4] = uk[i4];
        }

        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->HelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                         b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                         b_CurvStruct->a_param, b_CurvStruct->b_param, b_uk, unusedU1, b_r1D, r2D,
                         r3D);
        b_vmax = b_CurvStruct->FeedRate;
        c_N = coder::internal::maximum2(2UL - ctx_cfg_NHorz);
        c_k = 1UL;
        exitg1 = false;
        while ((!exitg1) && (c_k >= c_N)) {
            double y;
            ctx_q_gcode->get(c_k, (&expl_temp));
            y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                                   expl_temp.P0, expl_temp.P1, expl_temp.HelixCenter, expl_temp.evec,
                                   expl_temp.theta, expl_temp.pitch, expl_temp.CoeffP5,
                                   expl_temp.sp_index, expl_temp.FeedRate, expl_temp.a_param,
                                   expl_temp.b_param);
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
                __m128d r4;
                int varargin_2;
                varargin_2 = acoef * e_k;
                r4 = _mm_loadu_pd(&b_r1D[3 * varargin_2]);
                _mm_storeu_pd(&c[3 * e_k], _mm_mul_pd(r4, _mm_set1_pd(jps)));
                c[3 * e_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
            }
        }

        coder::bsxfun(r3D, z1, r3);
        b_d1uk.set_size(1, d1uk.size(1));
        f_loop_ub = d1uk.size(1);
        d_scalarLB = d1uk.size(1) & -2;
        d_vectorUB = d_scalarLB - 2;
        for (i6 = 0; i6 <= d_vectorUB; i6 += 2) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&d1uk[i6]);
            r6 = _mm_loadu_pd(&d2uk[i6]);
            _mm_storeu_pd(&b_d1uk[i6], _mm_mul_pd(r5, r6));
        }

        for (i6 = d_scalarLB; i6 < f_loop_ub; i6++) {
            b_d1uk[i6] = d1uk[i6] * d2uk[i6];
        }

        coder::bsxfun(r2D, b_d1uk, r7);
        a.set_size(r3.size(1), 3);
        g_loop_ub = r3.size(1);
        for (int i7 = 0; i7 < 3; i7++) {
            for (int i8 = 0; i8 < g_loop_ub; i8++) {
                a[i8 + a.size(0) * i7] = (r3[i7 + 3 * i8] + 3.0 * r7[i7 + 3 * i8]) + c[i7 + 3 * i8];
            }
        }

        x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int b_acoef;
            b_acoef = (a.size(0) != 1);
            for (int f_k = 0; f_k < 3; f_k++) {
                int i9;
                i9 = x.size(0) - 1;
                for (int g_k = 0; g_k <= i9; g_k++) {
                    x[g_k + x.size(0) * f_k] = a[b_acoef * g_k + a.size(0) * f_k] / ctx_cfg_jmax[f_k];
                }
            }
        }

        jt.set_size(x.size(0), 3);
        if (x.size(0) != 0) {
            int h_loop_ub;
            int i_loop_ub;
            at.set_size(x.size(0), 3);
            h_loop_ub = x.size(0);
            for (int i10 = 0; i10 < 3; i10++) {
                for (int i11 = 0; i11 < h_loop_ub; i11++) {
                    at[i11 + at.size(0) * i10] = jt[i11 + jt.size(0) * i10];
                }
            }

            for (int i_k = 0; i_k < 3; i_k++) {
                int i12;
                i12 = at.size(0);
                for (int j_k = 0; j_k < i12; j_k++) {
                    at[j_k + at.size(0) * i_k] = std::abs(x[j_k + x.size(0) * i_k]);
                }
            }

            jt.set_size(at.size(0), 3);
            i_loop_ub = at.size(0);
            for (int i13 = 0; i13 < 3; i13++) {
                for (int i15 = 0; i15 < i_loop_ub; i15++) {
                    jt[i15 + jt.size(0) * i13] = at[i15 + at.size(0) * i13];
                }
            }
        }

        z1.set_size(1, d1uk.size(1));
        e_N = d1uk.size(1);
        for (int h_k = 0; h_k < e_N; h_k++) {
            z1[h_k] = std::pow(d1uk[h_k], 2.0);
        }

        coder::bsxfun(r2D, z1, r3);
        coder::bsxfun(b_r1D, d2uk, r7);
        a.set_size(r3.size(1), 3);
        j_loop_ub = r3.size(1);
        for (int i14 = 0; i14 < 3; i14++) {
            for (int i16 = 0; i16 < j_loop_ub; i16++) {
                a[i16 + a.size(0) * i14] = r3[i14 + 3 * i16] + r7[i14 + 3 * i16];
            }
        }

        x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int c_acoef;
            c_acoef = (a.size(0) != 1);
            for (int k_k = 0; k_k < 3; k_k++) {
                int i17;
                i17 = x.size(0) - 1;
                for (int m_k = 0; m_k <= i17; m_k++) {
                    x[m_k + x.size(0) * k_k] = a[c_acoef * m_k + a.size(0) * k_k] / ctx_cfg_amax[k_k];
                }
            }
        }

        at.set_size(x.size(0), 3);
        if (x.size(0) != 0) {
            for (int l_k = 0; l_k < 3; l_k++) {
                int i18;
                i18 = at.size(0);
                for (int n_k = 0; n_k < i18; n_k++) {
                    at[n_k + at.size(0) * l_k] = std::abs(x[n_k + x.size(0) * l_k]);
                }
            }
        }

        sqrt_calls++;
        m = jt.size(0) - 1;
        max_jt.set_size(jt.size(0));
        if (jt.size(0) >= 1) {
            double d;
            int c_i;
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
            double d1;
            int e_i;
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
        k_loop_ub = max_jt.size(0);
        for (int i19 = 0; i19 < k_loop_ub; i19++) {
            b_max_jt[i19] = (max_jt[i19] > ctx_cfg_ZeroStartJerkLimit);
        }

        coder::b_eml_find(b_max_jt, cut_index_vel_data, cut_index_vel_size);
        cut_index_jerk_size_idx_1 = cut_index_vel_size[1];
        l_loop_ub = cut_index_vel_size[1];
        if (0 <= l_loop_ub - 1) {
            std::memcpy(&cut_index_jerk_data[0], &cut_index_vel_data[0], l_loop_ub * sizeof(int));
        }

        if (cut_index_vel_size[1] == 0) {
            cut_index_jerk_size_idx_1 = 1;
            cut_index_jerk_data[0] = 1;
        }

        b_max_at.set_size(1, max_at.size(0));
        m_loop_ub = max_at.size(0);
        for (int i20 = 0; i20 < m_loop_ub; i20++) {
            b_max_at[i20] = (max_at[i20] > ctx_cfg_ZeroStartAccLimit);
        }

        coder::b_eml_find(b_max_at, cut_index_vel_data, cut_index_vel_size);
        cut_index_acc_size_idx_1 = cut_index_vel_size[1];
        n_loop_ub = cut_index_vel_size[1];
        if (0 <= n_loop_ub - 1) {
            std::memcpy(&cut_index_acc_data[0], &cut_index_vel_data[0], n_loop_ub * sizeof(int));
        }

        if (cut_index_vel_size[1] == 0) {
            cut_index_acc_size_idx_1 = 1;
            cut_index_acc_data[0] = 1;
        }

        coder::bsxfun(b_r1D, d1uk, b_a);
        b_z1.set_size(3, b_a.size(1));
        f_N = b_a.size(1);
        for (int o_k = 0; o_k < f_N; o_k++) {
            b_z1[3 * o_k] = std::pow(b_a[3 * o_k], 2.0);
            b_z1[3 * o_k + 1] = std::pow(b_a[3 * o_k + 1], 2.0);
            b_z1[3 * o_k + 2] = std::pow(b_a[3 * o_k + 2], 2.0);
        }

        coder::sum(b_z1, b_x);
        i21 = b_x.size(1);
        e_scalarLB = b_x.size(1) & -2;
        e_vectorUB = e_scalarLB - 2;
        for (p_k = 0; p_k <= e_vectorUB; p_k += 2) {
            __m128d r8;
            r8 = _mm_loadu_pd(&b_x[p_k]);
            _mm_storeu_pd(&b_x[p_k], _mm_sqrt_pd(r8));
        }

        for (p_k = e_scalarLB; p_k < i21; p_k++) {
            b_x[p_k] = std::sqrt(b_x[p_k]);
        }

        c_x.set_size(1, b_x.size(1));
        o_loop_ub = b_x.size(1);
        for (int i22 = 0; i22 < o_loop_ub; i22++) {
            c_x[i22] = (b_x[i22] / b_vmax > ctx_cfg_ZeroStartVelLimit);
        }

        coder::b_eml_find(c_x, cut_index_vel_data, cut_index_vel_size);
        if (cut_index_vel_size[1] == 0) {
            cut_index_vel_size[1] = 1;
            cut_index_vel_data[0] = 1;
        }

        if (0 <= cut_index_acc_size_idx_1 - 1) {
            std::memcpy(&x_data[0], &cut_index_acc_data[0], cut_index_acc_size_idx_1 * sizeof(int));
        }

        for (int i23 = 0; i23 < cut_index_jerk_size_idx_1; i23++) {
            x_data[i23 + cut_index_acc_size_idx_1] = cut_index_jerk_data[i23];
        }

        p_loop_ub = cut_index_vel_size[1];
        for (int i24 = 0; i24 < p_loop_ub; i24++) {
            x_data[(i24 + cut_index_acc_size_idx_1) + cut_index_jerk_size_idx_1] =
                cut_index_vel_data[i24];
        }

        c_ex = x_data[0];
        if (x_data[0] < x_data[1]) {
            c_ex = x_data[1];
        }

        if (c_ex < x_data[2]) {
            c_ex = x_data[2];
        }

        cut_index = (max_at.size(0) - static_cast<int>(std::fmax(2.0, (static_cast<double>
                        (max_at.size(0)) - static_cast<double>(c_ex)) + 1.0))) - 1;

        //      actual_jps = jps;
        //      cut_index = N + 1 - cut_index;
        L = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->Type,
                       b_CurvStruct->P0, b_CurvStruct->P1, b_CurvStruct->HelixCenter,
                       b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                       b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                       b_CurvStruct->b_param);
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
        ::coder::array<double, 2U> a;
        ::coder::array<double, 2U> at;
        ::coder::array<double, 2U> b_a;
        ::coder::array<double, 2U> b_d1uk;
        ::coder::array<double, 2U> b_r1D;
        ::coder::array<double, 2U> b_uk;
        ::coder::array<double, 2U> b_x;
        ::coder::array<double, 2U> b_z1;
        ::coder::array<double, 2U> c;
        ::coder::array<double, 2U> d1uk;
        ::coder::array<double, 2U> d2uk;
        ::coder::array<double, 2U> jt;
        ::coder::array<double, 2U> r2D;
        ::coder::array<double, 2U> r3;
        ::coder::array<double, 2U> r3D;
        ::coder::array<double, 2U> r7;
        ::coder::array<double, 2U> t;
        ::coder::array<double, 2U> uk;
        ::coder::array<double, 2U> unusedU1;
        ::coder::array<double, 2U> x;
        ::coder::array<double, 2U> z1;
        ::coder::array<double, 1U> max_at;
        ::coder::array<double, 1U> max_jt;
        ::coder::array<bool, 2U> b_max_at;
        ::coder::array<bool, 2U> b_max_jt;
        ::coder::array<bool, 2U> c_x;
        CurvStruct expl_temp;
        double r1D[3];
        double unusedU0[3];
        double L;
        double b_ex;
        double b_vmax;
        double ex;
        double ex_tmp;
        double jps;
        double tmax;
        double z1_idx_1;
        double z1_idx_2;
        unsigned long c_N;
        unsigned long c_k;
        unsigned long z;
        int x_data[3];
        int cut_index_vel_size[2];
        int cut_index_acc_data[1];
        int cut_index_jerk_data[1];
        int cut_index_vel_data[1];
        int N;
        int b_N;
        int b_exp;
        int b_loop_ub;
        int b_m;
        int b_scalarLB;
        int b_vectorUB;
        int c_ex;
        int c_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int cut_index;
        int cut_index_acc_size_idx_1;
        int cut_index_jerk_size_idx_1;
        int d_N;
        int d_loop_ub;
        int d_scalarLB;
        int d_vectorUB;
        int e_N;
        int e_loop_ub;
        int e_scalarLB;
        int e_vectorUB;
        int f_N;
        int f_loop_ub;
        int g_loop_ub;
        int i1;
        int i2;
        int i21;
        int i3;
        int i6;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        int m;
        int m_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        int p_k;
        int p_loop_ub;
        int scalarLB;
        int vectorUB;
        bool exitg1;
        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->HelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                         b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                         b_CurvStruct->a_param, b_CurvStruct->b_param, unusedU0, r1D);
        z1_idx_1 = std::abs(r1D[1]);
        z1_idx_2 = std::abs(r1D[2]);
        ex = ctx_cfg_jmax[0];
        ex_tmp = std::abs(r1D[0]);
        b_ex = ex_tmp;
        if (ctx_cfg_jmax[0] > ctx_cfg_jmax[1]) {
            ex = ctx_cfg_jmax[1];
        }

        if (ex_tmp < z1_idx_1) {
            b_ex = z1_idx_1;
        }

        if (ex > ctx_cfg_jmax[2]) {
            ex = ctx_cfg_jmax[2];
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
            coder::b_eml_float_colon(tmax, -ctx_cfg_dt, t);
        }

        z1.set_size(1, t.size(1));
        N = t.size(1);
        for (int k = 0; k < N; k++) {
            z1[k] = std::pow(t[k], 3.0);
        }

        uk.set_size(1, z1.size(1));
        b_loop_ub = z1.size(1);
        scalarLB = z1.size(1) & -2;
        vectorUB = scalarLB - 2;
        for (i1 = 0; i1 <= vectorUB; i1 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&z1[i1]);
            _mm_storeu_pd(&uk[i1], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r), _mm_set1_pd(6.0)));
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
        b_scalarLB = z1.size(1) & -2;
        b_vectorUB = b_scalarLB - 2;
        for (i2 = 0; i2 <= b_vectorUB; i2 += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&z1[i2]);
            _mm_storeu_pd(&d1uk[i2], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r1), _mm_set1_pd(2.0)));
        }

        for (i2 = b_scalarLB; i2 < c_loop_ub; i2++) {
            d1uk[i2] = jps * z1[i2] / 2.0;
        }

        d2uk.set_size(1, t.size(1));
        d_loop_ub = t.size(1);
        c_scalarLB = t.size(1) & -2;
        c_vectorUB = c_scalarLB - 2;
        for (i3 = 0; i3 <= c_vectorUB; i3 += 2) {
            __m128d r2;
            r2 = _mm_loadu_pd(&t[i3]);
            _mm_storeu_pd(&d2uk[i3], _mm_mul_pd(_mm_set1_pd(jps), r2));
        }

        for (i3 = c_scalarLB; i3 < d_loop_ub; i3++) {
            d2uk[i3] = jps * t[i3];
        }

        b_uk.set_size(1, uk.size(1));
        e_loop_ub = uk.size(1) - 1;
        for (int i4 = 0; i4 <= e_loop_ub; i4++) {
            b_uk[i4] = uk[i4];
        }

        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->HelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                         b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                         b_CurvStruct->a_param, b_CurvStruct->b_param, b_uk, unusedU1, b_r1D, r2D,
                         r3D);
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

        c_N = coder::internal::maximum2(z + 1UL);
        c_k = static_cast<unsigned long>(std::round(k0));
        exitg1 = false;
        while ((!exitg1) && (c_k >= c_N)) {
            double y;
            ctx_q_gcode->get(c_k, (&expl_temp));
            y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                                   expl_temp.P0, expl_temp.P1, expl_temp.HelixCenter, expl_temp.evec,
                                   expl_temp.theta, expl_temp.pitch, expl_temp.CoeffP5,
                                   expl_temp.sp_index, expl_temp.FeedRate, expl_temp.a_param,
                                   expl_temp.b_param);
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
                __m128d r4;
                int varargin_2;
                varargin_2 = acoef * e_k;
                r4 = _mm_loadu_pd(&b_r1D[3 * varargin_2]);
                _mm_storeu_pd(&c[3 * e_k], _mm_mul_pd(r4, _mm_set1_pd(jps)));
                c[3 * e_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
            }
        }

        coder::bsxfun(r3D, z1, r3);
        b_d1uk.set_size(1, d1uk.size(1));
        f_loop_ub = d1uk.size(1);
        d_scalarLB = d1uk.size(1) & -2;
        d_vectorUB = d_scalarLB - 2;
        for (i6 = 0; i6 <= d_vectorUB; i6 += 2) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&d1uk[i6]);
            r6 = _mm_loadu_pd(&d2uk[i6]);
            _mm_storeu_pd(&b_d1uk[i6], _mm_mul_pd(r5, r6));
        }

        for (i6 = d_scalarLB; i6 < f_loop_ub; i6++) {
            b_d1uk[i6] = d1uk[i6] * d2uk[i6];
        }

        coder::bsxfun(r2D, b_d1uk, r7);
        a.set_size(r3.size(1), 3);
        g_loop_ub = r3.size(1);
        for (int i7 = 0; i7 < 3; i7++) {
            for (int i8 = 0; i8 < g_loop_ub; i8++) {
                a[i8 + a.size(0) * i7] = (r3[i7 + 3 * i8] + 3.0 * r7[i7 + 3 * i8]) + c[i7 + 3 * i8];
            }
        }

        x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int b_acoef;
            b_acoef = (a.size(0) != 1);
            for (int f_k = 0; f_k < 3; f_k++) {
                int i9;
                i9 = x.size(0) - 1;
                for (int g_k = 0; g_k <= i9; g_k++) {
                    x[g_k + x.size(0) * f_k] = a[b_acoef * g_k + a.size(0) * f_k] / ctx_cfg_jmax[f_k];
                }
            }
        }

        jt.set_size(x.size(0), 3);
        if (x.size(0) != 0) {
            int h_loop_ub;
            int i_loop_ub;
            at.set_size(x.size(0), 3);
            h_loop_ub = x.size(0);
            for (int i10 = 0; i10 < 3; i10++) {
                for (int i11 = 0; i11 < h_loop_ub; i11++) {
                    at[i11 + at.size(0) * i10] = jt[i11 + jt.size(0) * i10];
                }
            }

            for (int i_k = 0; i_k < 3; i_k++) {
                int i12;
                i12 = at.size(0);
                for (int j_k = 0; j_k < i12; j_k++) {
                    at[j_k + at.size(0) * i_k] = std::abs(x[j_k + x.size(0) * i_k]);
                }
            }

            jt.set_size(at.size(0), 3);
            i_loop_ub = at.size(0);
            for (int i13 = 0; i13 < 3; i13++) {
                for (int i15 = 0; i15 < i_loop_ub; i15++) {
                    jt[i15 + jt.size(0) * i13] = at[i15 + at.size(0) * i13];
                }
            }
        }

        z1.set_size(1, d1uk.size(1));
        e_N = d1uk.size(1);
        for (int h_k = 0; h_k < e_N; h_k++) {
            z1[h_k] = std::pow(d1uk[h_k], 2.0);
        }

        coder::bsxfun(r2D, z1, r3);
        coder::bsxfun(b_r1D, d2uk, r7);
        a.set_size(r3.size(1), 3);
        j_loop_ub = r3.size(1);
        for (int i14 = 0; i14 < 3; i14++) {
            for (int i16 = 0; i16 < j_loop_ub; i16++) {
                a[i16 + a.size(0) * i14] = r3[i14 + 3 * i16] + r7[i14 + 3 * i16];
            }
        }

        x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int c_acoef;
            c_acoef = (a.size(0) != 1);
            for (int k_k = 0; k_k < 3; k_k++) {
                int i17;
                i17 = x.size(0) - 1;
                for (int m_k = 0; m_k <= i17; m_k++) {
                    x[m_k + x.size(0) * k_k] = a[c_acoef * m_k + a.size(0) * k_k] / ctx_cfg_amax[k_k];
                }
            }
        }

        at.set_size(x.size(0), 3);
        if (x.size(0) != 0) {
            for (int l_k = 0; l_k < 3; l_k++) {
                int i18;
                i18 = at.size(0);
                for (int n_k = 0; n_k < i18; n_k++) {
                    at[n_k + at.size(0) * l_k] = std::abs(x[n_k + x.size(0) * l_k]);
                }
            }
        }

        sqrt_calls++;
        m = jt.size(0) - 1;
        max_jt.set_size(jt.size(0));
        if (jt.size(0) >= 1) {
            double d;
            int c_i;
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
            double d1;
            int e_i;
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
        k_loop_ub = max_jt.size(0);
        for (int i19 = 0; i19 < k_loop_ub; i19++) {
            b_max_jt[i19] = (max_jt[i19] > ctx_cfg_ZeroStartJerkLimit);
        }

        coder::b_eml_find(b_max_jt, cut_index_vel_data, cut_index_vel_size);
        cut_index_jerk_size_idx_1 = cut_index_vel_size[1];
        l_loop_ub = cut_index_vel_size[1];
        if (0 <= l_loop_ub - 1) {
            std::memcpy(&cut_index_jerk_data[0], &cut_index_vel_data[0], l_loop_ub * sizeof(int));
        }

        if (cut_index_vel_size[1] == 0) {
            cut_index_jerk_size_idx_1 = 1;
            cut_index_jerk_data[0] = 1;
        }

        b_max_at.set_size(1, max_at.size(0));
        m_loop_ub = max_at.size(0);
        for (int i20 = 0; i20 < m_loop_ub; i20++) {
            b_max_at[i20] = (max_at[i20] > ctx_cfg_ZeroStartAccLimit);
        }

        coder::b_eml_find(b_max_at, cut_index_vel_data, cut_index_vel_size);
        cut_index_acc_size_idx_1 = cut_index_vel_size[1];
        n_loop_ub = cut_index_vel_size[1];
        if (0 <= n_loop_ub - 1) {
            std::memcpy(&cut_index_acc_data[0], &cut_index_vel_data[0], n_loop_ub * sizeof(int));
        }

        if (cut_index_vel_size[1] == 0) {
            cut_index_acc_size_idx_1 = 1;
            cut_index_acc_data[0] = 1;
        }

        coder::bsxfun(b_r1D, d1uk, b_a);
        b_z1.set_size(3, b_a.size(1));
        f_N = b_a.size(1);
        for (int o_k = 0; o_k < f_N; o_k++) {
            b_z1[3 * o_k] = std::pow(b_a[3 * o_k], 2.0);
            b_z1[3 * o_k + 1] = std::pow(b_a[3 * o_k + 1], 2.0);
            b_z1[3 * o_k + 2] = std::pow(b_a[3 * o_k + 2], 2.0);
        }

        coder::sum(b_z1, b_x);
        i21 = b_x.size(1);
        e_scalarLB = b_x.size(1) & -2;
        e_vectorUB = e_scalarLB - 2;
        for (p_k = 0; p_k <= e_vectorUB; p_k += 2) {
            __m128d r8;
            r8 = _mm_loadu_pd(&b_x[p_k]);
            _mm_storeu_pd(&b_x[p_k], _mm_sqrt_pd(r8));
        }

        for (p_k = e_scalarLB; p_k < i21; p_k++) {
            b_x[p_k] = std::sqrt(b_x[p_k]);
        }

        c_x.set_size(1, b_x.size(1));
        o_loop_ub = b_x.size(1);
        for (int i22 = 0; i22 < o_loop_ub; i22++) {
            c_x[i22] = (b_x[i22] / b_vmax > ctx_cfg_ZeroStartVelLimit);
        }

        coder::b_eml_find(c_x, cut_index_vel_data, cut_index_vel_size);
        if (cut_index_vel_size[1] == 0) {
            cut_index_vel_size[1] = 1;
            cut_index_vel_data[0] = 1;
        }

        if (0 <= cut_index_acc_size_idx_1 - 1) {
            std::memcpy(&x_data[0], &cut_index_acc_data[0], cut_index_acc_size_idx_1 * sizeof(int));
        }

        for (int i23 = 0; i23 < cut_index_jerk_size_idx_1; i23++) {
            x_data[i23 + cut_index_acc_size_idx_1] = cut_index_jerk_data[i23];
        }

        p_loop_ub = cut_index_vel_size[1];
        for (int i24 = 0; i24 < p_loop_ub; i24++) {
            x_data[(i24 + cut_index_acc_size_idx_1) + cut_index_jerk_size_idx_1] =
                cut_index_vel_data[i24];
        }

        c_ex = x_data[0];
        if (x_data[0] < x_data[1]) {
            c_ex = x_data[1];
        }

        if (c_ex < x_data[2]) {
            c_ex = x_data[2];
        }

        cut_index = (max_at.size(0) - static_cast<int>(std::fmax(2.0, (static_cast<double>
                        (max_at.size(0)) - static_cast<double>(c_ex)) + 1.0))) - 1;

        //      actual_jps = jps;
        //      cut_index = N + 1 - cut_index;
        L = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->Type,
                       b_CurvStruct->P0, b_CurvStruct->P1, b_CurvStruct->HelixCenter,
                       b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                       b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                       b_CurvStruct->b_param);
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
        ::coder::array<double, 2U> a;
        ::coder::array<double, 2U> at;
        ::coder::array<double, 2U> b_a;
        ::coder::array<double, 2U> b_d1uk;
        ::coder::array<double, 2U> b_r1D;
        ::coder::array<double, 2U> b_uk;
        ::coder::array<double, 2U> b_x;
        ::coder::array<double, 2U> b_z1;
        ::coder::array<double, 2U> c;
        ::coder::array<double, 2U> c_x;
        ::coder::array<double, 2U> d1uk;
        ::coder::array<double, 2U> d2uk;
        ::coder::array<double, 2U> jt;
        ::coder::array<double, 2U> r2D;
        ::coder::array<double, 2U> r3;
        ::coder::array<double, 2U> r3D;
        ::coder::array<double, 2U> r7;
        ::coder::array<double, 2U> t;
        ::coder::array<double, 2U> uk;
        ::coder::array<double, 2U> unusedU1;
        ::coder::array<double, 2U> z1;
        ::coder::array<double, 1U> max_at;
        ::coder::array<double, 1U> max_jt;
        ::coder::array<double, 1U> norm_vt;
        ::coder::array<bool, 2U> b_max_at;
        ::coder::array<bool, 2U> b_max_jt;
        ::coder::array<bool, 2U> b_norm_vt;
        CurvStruct expl_temp;
        double r1D[3];
        double unusedU0[3];
        double L;
        double b_ex;
        double b_vmax;
        double ex;
        double ex_tmp;
        double jps;
        double tmax;
        double z1_idx_1;
        double z1_idx_2;
        long c_N;
        long c_k;
        long x;
        long y;
        int x_data[3];
        int cut_index_vel_size[2];
        int cut_index_acc_data[1];
        int cut_index_jerk_data[1];
        int cut_index_vel_data[1];
        int N;
        int b_N;
        int b_loop_ub;
        int b_m;
        int b_scalarLB;
        int b_vectorUB;
        int c_ex;
        int c_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int cut_index;
        int cut_index_acc_size_idx_1;
        int cut_index_jerk_size_idx_1;
        int d_N;
        int d_loop_ub;
        int d_scalarLB;
        int d_vectorUB;
        int e_N;
        int e_loop_ub;
        int e_scalarLB;
        int e_vectorUB;
        int f_N;
        int f_loop_ub;
        int f_scalarLB;
        int f_vectorUB;
        int g_loop_ub;
        int i1;
        int i19;
        int i2;
        int i20;
        int i3;
        int i6;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        int m;
        int m_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        int p_k;
        int p_loop_ub;
        int q_loop_ub;
        int scalarLB;
        int u0;
        int u1;
        int vectorUB;
        bool exitg1;
        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->HelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                         b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                         b_CurvStruct->a_param, b_CurvStruct->b_param, unusedU0, r1D);
        z1_idx_1 = std::abs(r1D[1]);
        z1_idx_2 = std::abs(r1D[2]);
        ex = ctx_cfg_jmax[0];
        ex_tmp = std::abs(r1D[0]);
        b_ex = ex_tmp;
        if (ctx_cfg_jmax[0] > ctx_cfg_jmax[1]) {
            ex = ctx_cfg_jmax[1];
        }

        if (ex_tmp < z1_idx_1) {
            b_ex = z1_idx_1;
        }

        if (ex > ctx_cfg_jmax[2]) {
            ex = ctx_cfg_jmax[2];
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
            coder::eml_float_colon(ctx_cfg_dt, tmax, t);
        }

        z1.set_size(1, t.size(1));
        N = t.size(1);
        for (int k = 0; k < N; k++) {
            z1[k] = std::pow(t[k], 3.0);
        }

        uk.set_size(1, z1.size(1));
        b_loop_ub = z1.size(1);
        scalarLB = z1.size(1) & -2;
        vectorUB = scalarLB - 2;
        for (i1 = 0; i1 <= vectorUB; i1 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&z1[i1]);
            _mm_storeu_pd(&uk[i1], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r), _mm_set1_pd(6.0)));
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
        b_scalarLB = z1.size(1) & -2;
        b_vectorUB = b_scalarLB - 2;
        for (i2 = 0; i2 <= b_vectorUB; i2 += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&z1[i2]);
            _mm_storeu_pd(&d1uk[i2], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r1), _mm_set1_pd(2.0)));
        }

        for (i2 = b_scalarLB; i2 < c_loop_ub; i2++) {
            d1uk[i2] = jps * z1[i2] / 2.0;
        }

        d2uk.set_size(1, t.size(1));
        d_loop_ub = t.size(1);
        c_scalarLB = t.size(1) & -2;
        c_vectorUB = c_scalarLB - 2;
        for (i3 = 0; i3 <= c_vectorUB; i3 += 2) {
            __m128d r2;
            r2 = _mm_loadu_pd(&t[i3]);
            _mm_storeu_pd(&d2uk[i3], _mm_mul_pd(_mm_set1_pd(jps), r2));
        }

        for (i3 = c_scalarLB; i3 < d_loop_ub; i3++) {
            d2uk[i3] = jps * t[i3];
        }

        b_uk.set_size(1, uk.size(1));
        e_loop_ub = uk.size(1) - 1;
        for (int i4 = 0; i4 <= e_loop_ub; i4++) {
            b_uk[i4] = uk[i4];
        }

        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->HelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                         b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                         b_CurvStruct->a_param, b_CurvStruct->b_param, b_uk, unusedU1, b_r1D, r2D,
                         r3D);
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
            double b_y;
            ctx_q_gcode->get(c_k, (&expl_temp));
            b_y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                expl_temp.P0, expl_temp.P1, expl_temp.HelixCenter, expl_temp.evec, expl_temp.theta,
                expl_temp.pitch, expl_temp.CoeffP5, expl_temp.sp_index, expl_temp.FeedRate,
                expl_temp.a_param, expl_temp.b_param);
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
                __m128d r4;
                int varargin_2;
                varargin_2 = acoef * e_k;
                r4 = _mm_loadu_pd(&b_r1D[3 * varargin_2]);
                _mm_storeu_pd(&c[3 * e_k], _mm_mul_pd(r4, _mm_set1_pd(jps)));
                c[3 * e_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
            }
        }

        coder::bsxfun(r3D, z1, r3);
        b_d1uk.set_size(1, d1uk.size(1));
        f_loop_ub = d1uk.size(1);
        d_scalarLB = d1uk.size(1) & -2;
        d_vectorUB = d_scalarLB - 2;
        for (i6 = 0; i6 <= d_vectorUB; i6 += 2) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&d1uk[i6]);
            r6 = _mm_loadu_pd(&d2uk[i6]);
            _mm_storeu_pd(&b_d1uk[i6], _mm_mul_pd(r5, r6));
        }

        for (i6 = d_scalarLB; i6 < f_loop_ub; i6++) {
            b_d1uk[i6] = d1uk[i6] * d2uk[i6];
        }

        coder::bsxfun(r2D, b_d1uk, r7);
        a.set_size(r3.size(1), 3);
        g_loop_ub = r3.size(1);
        for (int i7 = 0; i7 < 3; i7++) {
            for (int i8 = 0; i8 < g_loop_ub; i8++) {
                a[i8 + a.size(0) * i7] = (r3[i7 + 3 * i8] + 3.0 * r7[i7 + 3 * i8]) + c[i7 + 3 * i8];
            }
        }

        b_x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int b_acoef;
            b_acoef = (a.size(0) != 1);
            for (int f_k = 0; f_k < 3; f_k++) {
                int i9;
                i9 = b_x.size(0) - 1;
                for (int g_k = 0; g_k <= i9; g_k++) {
                    b_x[g_k + b_x.size(0) * f_k] = a[b_acoef * g_k + a.size(0) * f_k] /
                        ctx_cfg_jmax[f_k];
                }
            }
        }

        jt.set_size(b_x.size(0), 3);
        if (b_x.size(0) != 0) {
            int h_loop_ub;
            int i_loop_ub;
            at.set_size(b_x.size(0), 3);
            h_loop_ub = b_x.size(0);
            for (int i10 = 0; i10 < 3; i10++) {
                for (int i11 = 0; i11 < h_loop_ub; i11++) {
                    at[i11 + at.size(0) * i10] = jt[i11 + jt.size(0) * i10];
                }
            }

            for (int i_k = 0; i_k < 3; i_k++) {
                int i12;
                i12 = at.size(0);
                for (int j_k = 0; j_k < i12; j_k++) {
                    at[j_k + at.size(0) * i_k] = std::abs(b_x[j_k + b_x.size(0) * i_k]);
                }
            }

            jt.set_size(at.size(0), 3);
            i_loop_ub = at.size(0);
            for (int i13 = 0; i13 < 3; i13++) {
                for (int i15 = 0; i15 < i_loop_ub; i15++) {
                    jt[i15 + jt.size(0) * i13] = at[i15 + at.size(0) * i13];
                }
            }
        }

        z1.set_size(1, d1uk.size(1));
        e_N = d1uk.size(1);
        for (int h_k = 0; h_k < e_N; h_k++) {
            z1[h_k] = std::pow(d1uk[h_k], 2.0);
        }

        coder::bsxfun(r2D, z1, r3);
        coder::bsxfun(b_r1D, d2uk, r7);
        a.set_size(r3.size(1), 3);
        j_loop_ub = r3.size(1);
        for (int i14 = 0; i14 < 3; i14++) {
            for (int i16 = 0; i16 < j_loop_ub; i16++) {
                a[i16 + a.size(0) * i14] = r3[i14 + 3 * i16] + r7[i14 + 3 * i16];
            }
        }

        b_x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int c_acoef;
            c_acoef = (a.size(0) != 1);
            for (int k_k = 0; k_k < 3; k_k++) {
                int i17;
                i17 = b_x.size(0) - 1;
                for (int m_k = 0; m_k <= i17; m_k++) {
                    b_x[m_k + b_x.size(0) * k_k] = a[c_acoef * m_k + a.size(0) * k_k] /
                        ctx_cfg_amax[k_k];
                }
            }
        }

        at.set_size(b_x.size(0), 3);
        if (b_x.size(0) != 0) {
            for (int l_k = 0; l_k < 3; l_k++) {
                int i18;
                i18 = at.size(0);
                for (int n_k = 0; n_k < i18; n_k++) {
                    at[n_k + at.size(0) * l_k] = std::abs(b_x[n_k + b_x.size(0) * l_k]);
                }
            }
        }

        sqrt_calls++;
        coder::bsxfun(b_r1D, d1uk, b_a);
        b_z1.set_size(3, b_a.size(1));
        f_N = b_a.size(1);
        for (int o_k = 0; o_k < f_N; o_k++) {
            b_z1[3 * o_k] = std::pow(b_a[3 * o_k], 2.0);
            b_z1[3 * o_k + 1] = std::pow(b_a[3 * o_k + 1], 2.0);
            b_z1[3 * o_k + 2] = std::pow(b_a[3 * o_k + 2], 2.0);
        }

        coder::sum(b_z1, c_x);
        i19 = c_x.size(1);
        e_scalarLB = c_x.size(1) & -2;
        e_vectorUB = e_scalarLB - 2;
        for (p_k = 0; p_k <= e_vectorUB; p_k += 2) {
            __m128d r8;
            r8 = _mm_loadu_pd(&c_x[p_k]);
            _mm_storeu_pd(&c_x[p_k], _mm_sqrt_pd(r8));
        }

        for (p_k = e_scalarLB; p_k < i19; p_k++) {
            c_x[p_k] = std::sqrt(c_x[p_k]);
        }

        norm_vt.set_size(c_x.size(1));
        k_loop_ub = c_x.size(1);
        f_scalarLB = c_x.size(1) & -2;
        f_vectorUB = f_scalarLB - 2;
        for (i20 = 0; i20 <= f_vectorUB; i20 += 2) {
            __m128d r9;
            r9 = _mm_loadu_pd(&c_x[i20]);
            _mm_storeu_pd(&norm_vt[i20], _mm_div_pd(r9, _mm_set1_pd(b_vmax)));
        }

        for (i20 = f_scalarLB; i20 < k_loop_ub; i20++) {
            norm_vt[i20] = c_x[i20] / b_vmax;
        }

        m = jt.size(0) - 1;
        max_jt.set_size(jt.size(0));
        if (jt.size(0) >= 1) {
            double d;
            int c_i;
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
            double d1;
            int e_i;
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
        l_loop_ub = max_jt.size(0);
        for (int i21 = 0; i21 < l_loop_ub; i21++) {
            b_max_jt[i21] = (max_jt[i21] > ctx_cfg_ZeroStartJerkLimit);
        }

        coder::eml_find(b_max_jt, cut_index_vel_data, cut_index_vel_size);
        cut_index_jerk_size_idx_1 = cut_index_vel_size[1];
        m_loop_ub = cut_index_vel_size[1];
        if (0 <= m_loop_ub - 1) {
            std::memcpy(&cut_index_jerk_data[0], &cut_index_vel_data[0], m_loop_ub * sizeof(int));
        }

        if (cut_index_vel_size[1] == 0) {
            cut_index_jerk_size_idx_1 = 1;
            cut_index_jerk_data[0] = max_jt.size(0);
        }

        b_max_at.set_size(1, max_at.size(0));
        n_loop_ub = max_at.size(0);
        for (int i22 = 0; i22 < n_loop_ub; i22++) {
            b_max_at[i22] = (max_at[i22] > ctx_cfg_ZeroStartAccLimit);
        }

        coder::eml_find(b_max_at, cut_index_vel_data, cut_index_vel_size);
        cut_index_acc_size_idx_1 = cut_index_vel_size[1];
        o_loop_ub = cut_index_vel_size[1];
        if (0 <= o_loop_ub - 1) {
            std::memcpy(&cut_index_acc_data[0], &cut_index_vel_data[0], o_loop_ub * sizeof(int));
        }

        if (cut_index_vel_size[1] == 0) {
            cut_index_acc_size_idx_1 = 1;
            cut_index_acc_data[0] = max_jt.size(0);
        }

        b_norm_vt.set_size(1, norm_vt.size(0));
        p_loop_ub = norm_vt.size(0);
        for (int i23 = 0; i23 < p_loop_ub; i23++) {
            b_norm_vt[i23] = (norm_vt[i23] > ctx_cfg_ZeroStartVelLimit);
        }

        coder::eml_find(b_norm_vt, cut_index_vel_data, cut_index_vel_size);
        if (cut_index_vel_size[1] == 0) {
            cut_index_vel_size[1] = 1;
            cut_index_vel_data[0] = max_jt.size(0);
        }

        if (0 <= cut_index_acc_size_idx_1 - 1) {
            std::memcpy(&x_data[0], &cut_index_acc_data[0], cut_index_acc_size_idx_1 * sizeof(int));
        }

        for (int i24 = 0; i24 < cut_index_jerk_size_idx_1; i24++) {
            x_data[i24 + cut_index_acc_size_idx_1] = cut_index_jerk_data[i24];
        }

        q_loop_ub = cut_index_vel_size[1];
        for (int i25 = 0; i25 < q_loop_ub; i25++) {
            x_data[(i25 + cut_index_acc_size_idx_1) + cut_index_jerk_size_idx_1] =
                cut_index_vel_data[i25];
        }

        c_ex = x_data[0];
        if (x_data[0] > x_data[1]) {
            c_ex = x_data[1];
        }

        if (c_ex > x_data[2]) {
            c_ex = x_data[2];
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
                       b_CurvStruct->P0, b_CurvStruct->P1, b_CurvStruct->HelixCenter,
                       b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                       b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                       b_CurvStruct->b_param);
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
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct);
            printf("\nCut:\n");
            fflush(stdout);
            printf("Index = %d, t_cut = %e, vmax = %.1f\n", cut_index, t[cut_index - 1], b_vmax);
            fflush(stdout);
            printf("jps = %e, norm_vt(%d) = %f\n", jps, cut_index, norm_vt[cut_index - 1]);
            fflush(stdout);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2);
        }
    }

    //
    // Arguments    : const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX
    //                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY
    //                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ
    //                unsigned long CurvSpline_sp_Bl_handle
    //                double uvec
    //                double r0D[3]
    //                double r1D[3]
    //                double r2D[3]
    //                double r3D[3]
    // Return Type  : void
    //
    static void EvalBSplineNoCtx(const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX, const ::
        coder::array<double, 2U> &CurvSpline_sp_CoeffY, const ::coder::array<double, 2U>
        &CurvSpline_sp_CoeffZ, unsigned long CurvSpline_sp_Bl_handle, double uvec, double r0D[3],
        double r1D[3], double r2D[3], double r3D[3])
    {
        double r0Dx;
        double r0Dy;
        double r0Dz;
        double r1Dx;
        double r1Dy;
        double r1Dz;
        double r2Dx;
        double r2Dy;
        double r2Dz;
        double r3Dx;
        double r3Dy;
        double r3Dz;
        ZoneScopedN("EvalBSpline");
        bspline_eval_vec(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffX, uvec, &r0Dx, &r1Dx, &r2Dx,
                         &r3Dx);
        bspline_eval_vec(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffY, uvec, &r0Dy, &r1Dy, &r2Dy,
                         &r3Dy);
        bspline_eval_vec(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffZ, uvec, &r0Dz, &r1Dz, &r2Dz,
                         &r3Dz);
        r0D[0] = r0Dx;
        r0D[1] = r0Dy;
        r0D[2] = r0Dz;
        r1D[0] = r1Dx;
        r1D[1] = r1Dy;
        r1D[2] = r1Dz;
        r2D[0] = r2Dx;
        r2D[1] = r2Dy;
        r2D[2] = r2Dz;
        r3D[0] = r3Dx;
        r3D[1] = r3Dy;
        r3D[2] = r3Dz;
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
        double I_tmp;
        double I_tmp_tmp;
        double b_I_tmp;
        double c_I_tmp;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
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
        double t10;
        double t14;
        double t15;
        double t16;
        double t17;
        double t18;
        double t19;
        double t2;
        double t20;
        double t3;
        double t4;
        double t5;
        double t6;
        double t7;
        double t8;
        double t9;

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
    //                const double CurvStruct_HelixCenter[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const ::coder::array<double, 2U> &u_vec
    //                ::coder::array<double, 2U> &r0D
    //                ::coder::array<double, 2U> &r1D
    //                ::coder::array<double, 2U> &r2D
    //                ::coder::array<double, 2U> &r3D
    // Return Type  : void
    //
    static void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const double
                          CurvStruct_HelixCenter[3], const double CurvStruct_evec[3], double
                          CurvStruct_theta, double CurvStruct_pitch, const ::coder::array<double, 2U>
                          &u_vec, ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D, ::
                          coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D)
    {
        __m128d r;
        ::coder::array<double, 2U> b;
        ::coder::array<double, 2U> c_a;
        ::coder::array<double, 2U> cphi;
        ::coder::array<double, 2U> cphiTCP0;
        ::coder::array<double, 2U> cphiTEcrCP0;
        ::coder::array<double, 2U> phi_vec;
        ::coder::array<double, 2U> sphi;
        ::coder::array<double, 2U> sphiTCP0;
        ::coder::array<double, 2U> sphiTEcrCP0;
        double CP0[3];
        double EcrCP0[3];
        double P0P1[3];
        double y[3];
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int i5;
        int loop_ub;
        char message[16];
        ZoneScopedN("EvalHelix");

        //
        //
        r = _mm_loadu_pd((double *)&CurvStruct_P0[0]);
        _mm_storeu_pd(&P0P1[0], _mm_sub_pd(_mm_loadu_pd((double *)&CurvStruct_P1[0]), r));
        P0P1[2] = CurvStruct_P1[2] - CurvStruct_P0[2];
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

        sqrt_calls++;
        if (std::sqrt((std::pow(CurvStruct_evec[1] * P0P1[2] - CurvStruct_evec[2] * P0P1[1], 2.0) +
                       std::pow(CurvStruct_evec[2] * P0P1[0] - CurvStruct_evec[0] * P0P1[2], 2.0)) +
                      std::pow(CurvStruct_evec[0] * P0P1[1] - CurvStruct_evec[1] * P0P1[0], 2.0)) <=
            2.2204460492503131E-16) {
            for (int i4 = 0; i4 < 16; i4++) {
                message[i4] = cv1[i4];
            }

            c_assert_(&message[0]);
        } else {
            __m128d r1;
            double a;
            double a_tmp;
            double b_a;
            double b_a_tmp;
            int e_loop_ub;
            int f_loop_ub;
            int g_loop_ub;
            int h_loop_ub;
            int i7;
            int i9;
            int i_loop_ub;
            int j_loop_ub;
            int k_loop_ub;
            int l_loop_ub;
            int m_loop_ub;
            int n_loop_ub;
            int o_loop_ub;
            int scalarLB;
            int vectorUB;

            //  if pitch == 0
            //      if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
            //          return;
            //      end
            //  end
            //
            r1 = _mm_loadu_pd((double *)&CurvStruct_HelixCenter[0]);
            _mm_storeu_pd(&CP0[0], _mm_sub_pd(r, r1));
            CP0[2] = CurvStruct_P0[2] - CurvStruct_HelixCenter[2];
            phi_vec.set_size(1, u_vec.size(1));
            e_loop_ub = u_vec.size(1);
            scalarLB = u_vec.size(1) & -2;
            vectorUB = scalarLB - 2;
            for (i5 = 0; i5 <= vectorUB; i5 += 2) {
                _mm_storeu_pd(&phi_vec[i5], _mm_mul_pd(_mm_set1_pd(CurvStruct_theta), _mm_loadu_pd
                               ((double *)&u_vec[i5])));
            }

            for (i5 = scalarLB; i5 < e_loop_ub; i5++) {
                phi_vec[i5] = CurvStruct_theta * u_vec[i5];
            }

            EcrCP0[0] = CurvStruct_evec[1] * CP0[2] - CurvStruct_evec[2] * CP0[1];
            EcrCP0[1] = CurvStruct_evec[2] * CP0[0] - CurvStruct_evec[0] * CP0[2];
            EcrCP0[2] = CurvStruct_evec[0] * CP0[1] - CurvStruct_evec[1] * CP0[0];
            cphi.set_size(1, phi_vec.size(1));
            f_loop_ub = phi_vec.size(1);
            for (int i6 = 0; i6 < f_loop_ub; i6++) {
                cphi[i6] = phi_vec[i6];
            }

            i7 = phi_vec.size(1);
            for (int k = 0; k < i7; k++) {
                cphi[k] = std::cos(cphi[k]);
            }

            cos_calls++;
            sphi.set_size(1, phi_vec.size(1));
            g_loop_ub = phi_vec.size(1);
            for (int i8 = 0; i8 < g_loop_ub; i8++) {
                sphi[i8] = phi_vec[i8];
            }

            i9 = phi_vec.size(1);
            for (int b_k = 0; b_k < i9; b_k++) {
                sphi[b_k] = std::sin(sphi[b_k]);
            }

            sin_calls++;

            //
            cphiTCP0.set_size(3, cphi.size(1));
            h_loop_ub = cphi.size(1);
            for (int i10 = 0; i10 < h_loop_ub; i10++) {
                __m128d r2;
                r2 = _mm_loadu_pd(&CP0[0]);
                _mm_storeu_pd(&cphiTCP0[3 * i10], _mm_mul_pd(r2, _mm_set1_pd(cphi[i10])));
                cphiTCP0[3 * i10 + 2] = CP0[2] * cphi[i10];
            }

            sphiTCP0.set_size(3, sphi.size(1));
            i_loop_ub = sphi.size(1);
            for (int i11 = 0; i11 < i_loop_ub; i11++) {
                __m128d r3;
                r3 = _mm_loadu_pd(&CP0[0]);
                _mm_storeu_pd(&sphiTCP0[3 * i11], _mm_mul_pd(r3, _mm_set1_pd(sphi[i11])));
                sphiTCP0[3 * i11 + 2] = CP0[2] * sphi[i11];
            }

            cphiTEcrCP0.set_size(3, cphi.size(1));
            j_loop_ub = cphi.size(1);
            for (int i12 = 0; i12 < j_loop_ub; i12++) {
                __m128d r4;
                r4 = _mm_loadu_pd(&EcrCP0[0]);
                _mm_storeu_pd(&cphiTEcrCP0[3 * i12], _mm_mul_pd(r4, _mm_set1_pd(cphi[i12])));
                cphiTEcrCP0[3 * i12 + 2] = EcrCP0[2] * cphi[i12];
            }

            sphiTEcrCP0.set_size(3, sphi.size(1));
            k_loop_ub = sphi.size(1);
            for (int i13 = 0; i13 < k_loop_ub; i13++) {
                __m128d r5;
                r5 = _mm_loadu_pd(&EcrCP0[0]);
                _mm_storeu_pd(&sphiTEcrCP0[3 * i13], _mm_mul_pd(r5, _mm_set1_pd(sphi[i13])));
                sphiTEcrCP0[3 * i13 + 2] = EcrCP0[2] * sphi[i13];
            }

            //
            a = CurvStruct_pitch / 6.2831853071795862;
            b.set_size(3, phi_vec.size(1));
            l_loop_ub = phi_vec.size(1);
            for (int i14 = 0; i14 < l_loop_ub; i14++) {
                __m128d r6;
                __m128d r7;
                r6 = _mm_loadu_pd(&cphiTCP0[3 * i14]);
                r7 = _mm_loadu_pd(&sphiTEcrCP0[3 * i14]);
                _mm_storeu_pd(&b[3 * i14], _mm_add_pd(_mm_add_pd(r6, r7), _mm_add_pd(_mm_set1_pd(0.0),
                                _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a), _mm_loadu_pd((double *)
                                   &CurvStruct_evec[0])), _mm_set1_pd(phi_vec[i14])))));
                b[3 * i14 + 2] = (cphiTCP0[3 * i14 + 2] + sphiTEcrCP0[3 * i14 + 2]) + a *
                    CurvStruct_evec[2] * phi_vec[i14];
            }

            r0D.set_size(3, b.size(1));
            if (b.size(1) != 0) {
                int bcoef;
                int i15;
                bcoef = (b.size(1) != 1);
                i15 = b.size(1) - 1;
                for (int c_k = 0; c_k <= i15; c_k++) {
                    __m128d r8;
                    int varargin_3;
                    varargin_3 = bcoef * c_k;
                    r8 = _mm_loadu_pd(&b[3 * varargin_3]);
                    _mm_storeu_pd(&r0D[3 * c_k], _mm_add_pd(r1, r8));
                    r0D[3 * c_k + 2] = CurvStruct_HelixCenter[2] + b[3 * varargin_3 + 2];
                }
            }

            b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
            _mm_storeu_pd(&y[0], _mm_mul_pd(_mm_set1_pd(b_a), _mm_loadu_pd((double *)
                            &CurvStruct_evec[0])));
            y[2] = b_a * CurvStruct_evec[2];
            c_a.set_size(3, sphiTCP0.size(1));
            m_loop_ub = sphiTCP0.size(1);
            for (int i16 = 0; i16 < m_loop_ub; i16++) {
                __m128d r10;
                __m128d r9;
                r9 = _mm_loadu_pd(&sphiTCP0[3 * i16]);
                r10 = _mm_loadu_pd(&cphiTEcrCP0[3 * i16]);
                _mm_storeu_pd(&c_a[3 * i16], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(-CurvStruct_theta),
                                r9), _mm_mul_pd(_mm_set1_pd(CurvStruct_theta), r10)));
                c_a[3 * i16 + 2] = -CurvStruct_theta * sphiTCP0[3 * i16 + 2] + CurvStruct_theta *
                    cphiTEcrCP0[3 * i16 + 2];
            }

            r1D.set_size(3, c_a.size(1));
            if (c_a.size(1) != 0) {
                int acoef;
                int i17;
                acoef = (c_a.size(1) != 1);
                i17 = c_a.size(1) - 1;
                for (int d_k = 0; d_k <= i17; d_k++) {
                    __m128d r11;
                    __m128d r13;
                    int varargin_2;
                    varargin_2 = acoef * d_k;
                    r11 = _mm_loadu_pd(&c_a[3 * varargin_2]);
                    r13 = _mm_loadu_pd(&y[0]);
                    _mm_storeu_pd(&r1D[3 * d_k], _mm_add_pd(r11, r13));
                    r1D[3 * d_k + 2] = c_a[3 * varargin_2 + 2] + y[2];
                }
            }

            a_tmp = std::pow(CurvStruct_theta, 2.0);
            r2D.set_size(3, cphiTCP0.size(1));
            n_loop_ub = cphiTCP0.size(1);
            for (int i18 = 0; i18 < n_loop_ub; i18++) {
                __m128d r12;
                __m128d r14;
                r12 = _mm_loadu_pd(&cphiTCP0[3 * i18]);
                r14 = _mm_loadu_pd(&sphiTEcrCP0[3 * i18]);
                _mm_storeu_pd(&r2D[3 * i18], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(-a_tmp), r12),
                               _mm_mul_pd(_mm_set1_pd(a_tmp), r14)));
                r2D[3 * i18 + 2] = -a_tmp * cphiTCP0[3 * i18 + 2] - a_tmp * sphiTEcrCP0[3 * i18 + 2];
            }

            b_a_tmp = std::pow(CurvStruct_theta, 3.0);
            r3D.set_size(3, sphiTCP0.size(1));
            o_loop_ub = sphiTCP0.size(1);
            for (int i19 = 0; i19 < o_loop_ub; i19++) {
                __m128d r15;
                __m128d r16;
                __m128d r17;
                r15 = _mm_loadu_pd(&sphiTCP0[3 * i19]);
                r16 = _mm_loadu_pd(&cphiTEcrCP0[3 * i19]);
                r17 = _mm_set1_pd(b_a_tmp);
                _mm_storeu_pd(&r3D[3 * i19], _mm_sub_pd(_mm_mul_pd(r17, r15), _mm_mul_pd(r17, r16)));
                r3D[3 * i19 + 2] = b_a_tmp * sphiTCP0[3 * i19 + 2] - b_a_tmp * cphiTEcrCP0[3 * i19 +
                    2];
            }
        }
    }

    //
    // Arguments    : const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_HelixCenter[3]
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
    static void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const double
                          CurvStruct_HelixCenter[3], const double CurvStruct_evec[3], double
                          CurvStruct_theta, double CurvStruct_pitch, double u_vec, double r0D[3],
                          double r1D[3], double r2D[3], double r3D[3])
    {
        __m128d r;
        __m128d r1;
        double CP0[3];
        double EcrCP0[3];
        double P0P1[3];
        double cphiTCP0[3];
        double sphiTCP0[3];
        char message[16];
        ZoneScopedN("EvalHelix");

        //
        //
        r = _mm_loadu_pd((double *)&CurvStruct_P0[0]);
        _mm_storeu_pd(&P0P1[0], _mm_sub_pd(_mm_loadu_pd((double *)&CurvStruct_P1[0]), r));
        r1 = _mm_set1_pd(0.0);
        _mm_storeu_pd(&r0D[0], r1);
        _mm_storeu_pd(&r1D[0], r1);
        _mm_storeu_pd(&r2D[0], r1);
        _mm_storeu_pd(&r3D[0], r1);
        P0P1[2] = CurvStruct_P1[2] - CurvStruct_P0[2];
        r0D[2] = 0.0;
        r1D[2] = 0.0;
        r2D[2] = 0.0;
        r3D[2] = 0.0;
        sqrt_calls++;
        if (std::sqrt((std::pow(CurvStruct_evec[1] * P0P1[2] - CurvStruct_evec[2] * P0P1[1], 2.0) +
                       std::pow(CurvStruct_evec[2] * P0P1[0] - CurvStruct_evec[0] * P0P1[2], 2.0)) +
                      std::pow(CurvStruct_evec[0] * P0P1[1] - CurvStruct_evec[1] * P0P1[0], 2.0)) <=
            2.2204460492503131E-16) {
            for (int i = 0; i < 16; i++) {
                message[i] = cv1[i];
            }

            c_assert_(&message[0]);
        } else {
            __m128d r10;
            __m128d r11;
            __m128d r12;
            __m128d r2;
            __m128d r3;
            __m128d r4;
            __m128d r5;
            __m128d r6;
            __m128d r7;
            __m128d r8;
            __m128d r9;
            double a;
            double a_tmp;
            double b_a;
            double b_a_tmp;
            double cphi;
            double d;
            double d1;
            double d2;
            double phi_vec;
            double sphi;

            //  if pitch == 0
            //      if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
            //          return;
            //      end
            //  end
            //
            phi_vec = CurvStruct_theta * u_vec;
            cphi = std::cos(phi_vec);
            cos_calls++;
            sphi = std::sin(phi_vec);
            sin_calls++;

            //
            r2 = _mm_loadu_pd((double *)&CurvStruct_HelixCenter[0]);
            r3 = _mm_sub_pd(r, r2);
            _mm_storeu_pd(&CP0[0], r3);
            r4 = _mm_set1_pd(cphi);
            _mm_storeu_pd(&cphiTCP0[0], _mm_mul_pd(r3, r4));
            r5 = _mm_set1_pd(sphi);
            _mm_storeu_pd(&sphiTCP0[0], _mm_mul_pd(r3, r5));
            d = CurvStruct_P0[2] - CurvStruct_HelixCenter[2];
            cphiTCP0[2] = d * cphi;
            sphiTCP0[2] = d * sphi;
            EcrCP0[0] = CurvStruct_evec[1] * d - CurvStruct_evec[2] * CP0[1];
            EcrCP0[1] = CurvStruct_evec[2] * CP0[0] - CurvStruct_evec[0] * d;
            EcrCP0[2] = CurvStruct_evec[0] * CP0[1] - CurvStruct_evec[1] * CP0[0];

            //
            a = CurvStruct_pitch / 6.2831853071795862;
            b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
            a_tmp = std::pow(CurvStruct_theta, 2.0);
            b_a_tmp = std::pow(CurvStruct_theta, 3.0);
            r6 = _mm_loadu_pd(&EcrCP0[0]);
            r7 = _mm_mul_pd(r6, r4);
            r8 = _mm_mul_pd(r6, r5);
            r9 = _mm_loadu_pd(&cphiTCP0[0]);
            r10 = _mm_loadu_pd((double *)&CurvStruct_evec[0]);
            _mm_storeu_pd(&r0D[0], _mm_add_pd(r2, _mm_add_pd(_mm_add_pd(r9, r8), _mm_mul_pd
                            (_mm_mul_pd(_mm_set1_pd(a), r10), _mm_set1_pd(phi_vec)))));
            r11 = _mm_loadu_pd(&sphiTCP0[0]);
            _mm_storeu_pd(&r1D[0], _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd(-CurvStruct_theta),
                             r11), _mm_mul_pd(_mm_set1_pd(CurvStruct_theta), r7)), _mm_mul_pd
                           (_mm_set1_pd(b_a), r10)));
            _mm_storeu_pd(&r2D[0], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(-a_tmp), r9), _mm_mul_pd
                           (_mm_set1_pd(a_tmp), r8)));
            r12 = _mm_set1_pd(b_a_tmp);
            _mm_storeu_pd(&r3D[0], _mm_sub_pd(_mm_mul_pd(r12, r11), _mm_mul_pd(r12, r7)));
            d1 = EcrCP0[2] * cphi;
            d2 = EcrCP0[2] * sphi;
            r0D[2] = CurvStruct_HelixCenter[2] + ((cphiTCP0[2] + d2) + a * CurvStruct_evec[2] *
                phi_vec);
            r1D[2] = (-CurvStruct_theta * sphiTCP0[2] + CurvStruct_theta * d1) + b_a *
                CurvStruct_evec[2];
            r2D[2] = -a_tmp * cphiTCP0[2] - a_tmp * d2;
            r3D[2] = b_a_tmp * sphiTCP0[2] - b_a_tmp * d1;
        }
    }

    //
    // Arguments    : const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_HelixCenter[3]
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
    static void EvalHelix(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const double
                          CurvStruct_HelixCenter[3], const double CurvStruct_evec[3], double
                          CurvStruct_theta, double CurvStruct_pitch, const double u_vec[10], double
                          r0D[10][3], double r1D[10][3], double r2D[10][3], double r3D[10][3])
    {
        __m128d r;
        double cphiTCP0[10][3];
        double cphiTEcrCP0[10][3];
        double sphiTCP0[10][3];
        double sphiTEcrCP0[10][3];
        double CP0[3];
        double EcrCP0[3];
        double P0P1[3];
        double y[3];
        char message[16];
        ZoneScopedN("EvalHelix");

        //
        //
        r = _mm_loadu_pd((double *)&CurvStruct_P0[0]);
        _mm_storeu_pd(&P0P1[0], _mm_sub_pd(_mm_loadu_pd((double *)&CurvStruct_P1[0]), r));
        P0P1[2] = CurvStruct_P1[2] - CurvStruct_P0[2];
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

        sqrt_calls++;
        if (std::sqrt((std::pow(CurvStruct_evec[1] * P0P1[2] - CurvStruct_evec[2] * P0P1[1], 2.0) +
                       std::pow(CurvStruct_evec[2] * P0P1[0] - CurvStruct_evec[0] * P0P1[2], 2.0)) +
                      std::pow(CurvStruct_evec[0] * P0P1[1] - CurvStruct_evec[1] * P0P1[0], 2.0)) <=
            2.2204460492503131E-16) {
            for (int i1 = 0; i1 < 16; i1++) {
                message[i1] = cv1[i1];
            }

            c_assert_(&message[0]);
        } else {
            __m128d r1;
            __m128d r2;
            __m128d r3;
            __m128d r6;
            __m128d r7;
            double a;
            double a_tmp;
            double b_a_tmp;

            //  if pitch == 0
            //      if ~c_assert(evec'*P0P1 > eps, 'e'' * P0P1 = 0')
            //          return;
            //      end
            //  end
            //
            r1 = _mm_loadu_pd((double *)&CurvStruct_HelixCenter[0]);
            _mm_storeu_pd(&CP0[0], _mm_sub_pd(r, r1));
            CP0[2] = CurvStruct_P0[2] - CurvStruct_HelixCenter[2];
            EcrCP0[0] = CurvStruct_evec[1] * CP0[2] - CurvStruct_evec[2] * CP0[1];
            EcrCP0[1] = CurvStruct_evec[2] * CP0[0] - CurvStruct_evec[0] * CP0[2];
            EcrCP0[2] = CurvStruct_evec[0] * CP0[1] - CurvStruct_evec[1] * CP0[0];
            cos_calls++;
            sin_calls++;

            //
            //
            a = CurvStruct_pitch / 6.2831853071795862;
            r2 = _mm_loadu_pd(&CP0[0]);
            r3 = _mm_loadu_pd(&EcrCP0[0]);
            for (int k = 0; k < 10; k++) {
                __m128d r10;
                __m128d r4;
                __m128d r5;
                __m128d r8;
                double d;
                double d1;
                double d2;
                double d3;
                double d5;
                d = CurvStruct_theta * u_vec[k];
                d1 = std::cos(d);
                d2 = std::sin(d);
                r4 = _mm_set1_pd(d1);
                r5 = _mm_mul_pd(r2, r4);
                _mm_storeu_pd(&cphiTCP0[k][0], r5);
                r8 = _mm_set1_pd(d2);
                _mm_storeu_pd(&sphiTCP0[k][0], _mm_mul_pd(r2, r8));
                _mm_storeu_pd(&cphiTEcrCP0[k][0], _mm_mul_pd(r3, r4));
                r10 = _mm_mul_pd(r3, r8);
                _mm_storeu_pd(&sphiTEcrCP0[k][0], r10);
                _mm_storeu_pd(&r0D[k][0], _mm_add_pd(r1, _mm_add_pd(_mm_add_pd(r5, r10), _mm_add_pd
                                (_mm_set1_pd(0.0), _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(a),
                                   _mm_loadu_pd((double *)&CurvStruct_evec[0])), _mm_set1_pd(d))))));
                d3 = CP0[2] * d1;
                cphiTCP0[k][2] = d3;
                sphiTCP0[k][2] = CP0[2] * d2;
                cphiTEcrCP0[k][2] = EcrCP0[2] * d1;
                d5 = EcrCP0[2] * d2;
                sphiTEcrCP0[k][2] = d5;
                r0D[k][2] = CurvStruct_HelixCenter[2] + ((d3 + d5) + a * CurvStruct_evec[2] * d);
            }

            double b_a;
            b_a = CurvStruct_theta * CurvStruct_pitch / 6.2831853071795862;
            _mm_storeu_pd(&y[0], _mm_mul_pd(_mm_set1_pd(b_a), _mm_loadu_pd((double *)
                            &CurvStruct_evec[0])));
            y[2] = b_a * CurvStruct_evec[2];
            a_tmp = std::pow(CurvStruct_theta, 2.0);
            b_a_tmp = std::pow(CurvStruct_theta, 3.0);
            r6 = _mm_loadu_pd(&y[0]);
            r7 = _mm_set1_pd(b_a_tmp);
            for (int b_k = 0; b_k < 10; b_k++) {
                __m128d r11;
                __m128d r12;
                __m128d r13;
                __m128d r9;
                double d4;
                double d6;
                r9 = _mm_loadu_pd(&sphiTCP0[b_k][0]);
                r11 = _mm_loadu_pd(&cphiTEcrCP0[b_k][0]);
                _mm_storeu_pd(&r1D[b_k][0], _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_set1_pd
                                 (-CurvStruct_theta), r9), _mm_mul_pd(_mm_set1_pd(CurvStruct_theta),
                                 r11)), r6));
                r12 = _mm_loadu_pd(&cphiTCP0[b_k][0]);
                r13 = _mm_loadu_pd(&sphiTEcrCP0[b_k][0]);
                _mm_storeu_pd(&r2D[b_k][0], _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(-a_tmp), r12),
                               _mm_mul_pd(_mm_set1_pd(a_tmp), r13)));
                _mm_storeu_pd(&r3D[b_k][0], _mm_sub_pd(_mm_mul_pd(r7, r9), _mm_mul_pd(r7, r11)));
                d4 = sphiTCP0[b_k][2];
                d6 = cphiTEcrCP0[b_k][2];
                r1D[b_k][2] = (-CurvStruct_theta * d4 + CurvStruct_theta * d6) + y[2];
                r2D[b_k][2] = -a_tmp * cphiTCP0[b_k][2] - a_tmp * sphiTEcrCP0[b_k][2];
                r3D[b_k][2] = b_a_tmp * d4 - b_a_tmp * d6;
            }
        }
    }

    //
    // Arguments    : const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                double u_vec
    //                double r0D[3]
    //                double r1D[3]
    //                double r2D[3]
    //                double r3D[3]
    // Return Type  : void
    //
    static void EvalLine(const double CurvStruct_P0[3], const double CurvStruct_P1[3], double u_vec,
                         double r0D[3], double r1D[3], double r2D[3], double r3D[3])
    {
        __m128d r;
        ZoneScopedN("EvalLine");

        //
        //  parametrization of a straight line between P0 and P1
        //
        r0D[0] = CurvStruct_P1[0] * u_vec + CurvStruct_P0[0] * (1.0 - u_vec);
        r0D[1] = CurvStruct_P1[1] * u_vec + CurvStruct_P0[1] * (1.0 - u_vec);
        r0D[2] = CurvStruct_P1[2] * u_vec + CurvStruct_P0[2] * (1.0 - u_vec);

        //
        //
        _mm_storeu_pd(&r1D[0], _mm_sub_pd(_mm_loadu_pd((double *)&CurvStruct_P1[0]), _mm_loadu_pd
                       ((double *)&CurvStruct_P0[0])));
        r = _mm_set1_pd(0.0);
        _mm_storeu_pd(&r2D[0], r);
        _mm_storeu_pd(&r3D[0], r);
        r1D[2] = CurvStruct_P1[2] - CurvStruct_P0[2];
        r2D[2] = 0.0;
        r3D[2] = 0.0;
    }

    //
    // Arguments    : const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const ::coder::array<double, 2U> &u_vec
    //                ::coder::array<double, 2U> &r0D
    //                ::coder::array<double, 2U> &r1D
    //                ::coder::array<double, 2U> &r2D
    //                ::coder::array<double, 2U> &r3D
    // Return Type  : void
    //
    static void EvalLine(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const ::coder::
                         array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D, ::coder::array<
                         double, 2U> &r1D, ::coder::array<double, 2U> &r2D, ::coder::array<double,
                         2U> &r3D)
    {
        ::coder::array<double, 2U> b_tmp;
        double a[3];
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int i;
        int loop_ub;
        int scalarLB;
        int vectorUB;
        ZoneScopedN("EvalLine");

        //
        //  parametrization of a straight line between P0 and P1
        //
        b_tmp.set_size(1, u_vec.size(1));
        loop_ub = u_vec.size(1);
        scalarLB = u_vec.size(1) & -2;
        vectorUB = scalarLB - 2;
        for (i = 0; i <= vectorUB; i += 2) {
            _mm_storeu_pd(&b_tmp[i], _mm_sub_pd(_mm_set1_pd(1.0), _mm_loadu_pd((double *)&u_vec[i])));
        }

        for (i = scalarLB; i < loop_ub; i++) {
            b_tmp[i] = 1.0 - u_vec[i];
        }

        r0D.set_size(3, u_vec.size(1));
        b_loop_ub = u_vec.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            r0D[3 * i1] = CurvStruct_P1[0] * u_vec[i1] + CurvStruct_P0[0] * b_tmp[i1];
        }

        c_loop_ub = u_vec.size(1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            r0D[3 * i2 + 1] = CurvStruct_P1[1] * u_vec[i2] + CurvStruct_P0[1] * b_tmp[i2];
        }

        d_loop_ub = u_vec.size(1);
        for (int i3 = 0; i3 < d_loop_ub; i3++) {
            r0D[3 * i3 + 2] = CurvStruct_P1[2] * u_vec[i3] + CurvStruct_P0[2] * b_tmp[i3];
        }

        //
        _mm_storeu_pd(&a[0], _mm_sub_pd(_mm_loadu_pd((double *)&CurvStruct_P1[0]), _mm_loadu_pd
                       ((double *)&CurvStruct_P0[0])));
        a[2] = CurvStruct_P1[2] - CurvStruct_P0[2];
        r1D.set_size(3, u_vec.size(1));
        if (u_vec.size(1) != 0) {
            int i4;
            i4 = u_vec.size(1) - 1;
            for (int t = 0; t <= i4; t++) {
                r1D[3 * t] = a[0];
                r1D[3 * t + 1] = a[1];
                r1D[3 * t + 2] = a[2];
            }
        }

        //
        r2D.set_size(3, u_vec.size(1));
        e_loop_ub = u_vec.size(1);
        for (int i5 = 0; i5 < e_loop_ub; i5++) {
            r2D[3 * i5] = 0.0;
            r2D[3 * i5 + 1] = 0.0;
            r2D[3 * i5 + 2] = 0.0;
        }

        r3D.set_size(3, u_vec.size(1));
        f_loop_ub = u_vec.size(1);
        for (int i6 = 0; i6 < f_loop_ub; i6++) {
            r3D[3 * i6] = 0.0;
            r3D[3 * i6 + 1] = 0.0;
            r3D[3 * i6 + 2] = 0.0;
        }
    }

    //
    // Arguments    : const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double u_vec[10]
    //                double r0D[10][3]
    //                double r1D[10][3]
    //                double r2D[10][3]
    //                double r3D[10][3]
    // Return Type  : void
    //
    static void EvalLine(const double CurvStruct_P0[3], const double CurvStruct_P1[3], const double
                         u_vec[10], double r0D[10][3], double r1D[10][3], double r2D[10][3], double
                         r3D[10][3])
    {
        double a[3];
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        double d5;
        double d6;
        double d7;
        double d8;
        ZoneScopedN("EvalLine");

        //
        //  parametrization of a straight line between P0 and P1
        //
        //
        _mm_storeu_pd(&a[0], _mm_sub_pd(_mm_loadu_pd((double *)&CurvStruct_P1[0]), _mm_loadu_pd
                       ((double *)&CurvStruct_P0[0])));

        //
        d = CurvStruct_P1[0];
        d1 = CurvStruct_P1[1];
        d2 = CurvStruct_P1[2];
        d3 = CurvStruct_P0[0];
        d4 = CurvStruct_P0[1];
        d5 = CurvStruct_P0[2];
        d6 = a[0];
        d7 = a[1];
        d8 = CurvStruct_P1[2] - CurvStruct_P0[2];
        for (int t = 0; t < 10; t++) {
            double d9;
            d9 = u_vec[t];
            r0D[t][0] = d * d9 + d3 * (1.0 - d9);
            r0D[t][1] = d1 * d9 + d4 * (1.0 - d9);
            r0D[t][2] = d2 * d9 + d5 * (1.0 - d9);
            r1D[t][0] = d6;
            r2D[t][0] = 0.0;
            r3D[t][0] = 0.0;
            r1D[t][1] = d7;
            r2D[t][1] = 0.0;
            r3D[t][1] = 0.0;
            r1D[t][2] = d8;
            r2D[t][2] = 0.0;
            r3D[t][2] = 0.0;
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
    static void EvalTransP5(const double CurvStruct_CoeffP5[6][3], double u_vec, double r_0D[3],
                            double r_1D[3], double r_2D[3], double r_3D[3])
    {
        __m128d r;
        __m128d r1;
        __m128d r2;
        double p5_1D[5][3];
        double p5_2D[4][3];
        double p5_3D[3][3];
        ZoneScopedN("EvalTransP5");

        //
        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        r = _mm_set1_pd(3.0);
        r1 = _mm_set1_pd(2.0);
        r2 = _mm_set1_pd(1.0);

        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        //
        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        r_0D[0] = CurvStruct_CoeffP5[0][0];
        r_0D[1] = CurvStruct_CoeffP5[0][1];
        r_0D[2] = CurvStruct_CoeffP5[0][2];
        for (int i = 0; i < 5; i++) {
            __m128d r4;
            _mm_storeu_pd(&p5_1D[i][0], _mm_mul_pd(_mm_loadu_pd((double *)&CurvStruct_CoeffP5[i][0]),
                           _mm_set1_pd(5.0 - static_cast<double>(i))));
            p5_1D[i][2] = CurvStruct_CoeffP5[i][2] * (5.0 - static_cast<double>(i));
            r4 = _mm_loadu_pd(&r_0D[0]);
            _mm_storeu_pd(&r_0D[0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(u_vec), r4), _mm_loadu_pd
                           ((double *)&CurvStruct_CoeffP5[i + 1][0])));
            r_0D[2] = u_vec * r_0D[2] + CurvStruct_CoeffP5[i + 1][2];
        }

        __m128d r10;
        __m128d r11;
        __m128d r12;
        __m128d r3;
        __m128d r5;
        __m128d r6;
        __m128d r7;
        __m128d r8;
        __m128d r9;
        r3 = _mm_loadu_pd(&p5_1D[0][0]);
        _mm_storeu_pd(&p5_2D[0][0], _mm_mul_pd(r3, _mm_set1_pd(4.0)));
        p5_2D[0][2] = p5_1D[0][2] * 4.0;
        r3 = _mm_loadu_pd(&p5_1D[1][0]);
        _mm_storeu_pd(&p5_2D[1][0], _mm_mul_pd(r3, r));
        p5_2D[1][2] = p5_1D[1][2] * 3.0;
        r3 = _mm_loadu_pd(&p5_1D[2][0]);
        _mm_storeu_pd(&p5_2D[2][0], _mm_mul_pd(r3, r1));
        p5_2D[2][2] = p5_1D[2][2] * 2.0;
        r3 = _mm_loadu_pd(&p5_1D[3][0]);
        _mm_storeu_pd(&p5_2D[3][0], _mm_mul_pd(r3, r2));
        p5_2D[3][2] = p5_1D[3][2];
        r5 = _mm_loadu_pd(&p5_2D[0][0]);
        _mm_storeu_pd(&p5_3D[0][0], _mm_mul_pd(r5, r));
        p5_3D[0][2] = p5_2D[0][2] * 3.0;
        r5 = _mm_loadu_pd(&p5_2D[1][0]);
        _mm_storeu_pd(&p5_3D[1][0], _mm_mul_pd(r5, r1));
        p5_3D[1][2] = p5_2D[1][2] * 2.0;
        r5 = _mm_loadu_pd(&p5_2D[2][0]);
        _mm_storeu_pd(&p5_3D[2][0], _mm_mul_pd(r5, r2));
        p5_3D[2][2] = p5_2D[2][2];

        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        r_1D[0] = p5_1D[0][0];
        r_1D[1] = p5_1D[0][1];
        r_1D[2] = p5_1D[0][2];
        r6 = _mm_loadu_pd(&r_1D[0]);
        r7 = _mm_loadu_pd(&p5_1D[1][0]);
        r8 = _mm_set1_pd(u_vec);
        _mm_storeu_pd(&r_1D[0], _mm_add_pd(_mm_mul_pd(r8, r6), r7));
        r_1D[2] = u_vec * r_1D[2] + p5_1D[1][2];
        r6 = _mm_loadu_pd(&r_1D[0]);
        r7 = _mm_loadu_pd(&p5_1D[2][0]);
        _mm_storeu_pd(&r_1D[0], _mm_add_pd(_mm_mul_pd(r8, r6), r7));
        r_1D[2] = u_vec * r_1D[2] + p5_1D[2][2];
        r6 = _mm_loadu_pd(&r_1D[0]);
        r7 = _mm_loadu_pd(&p5_1D[3][0]);
        _mm_storeu_pd(&r_1D[0], _mm_add_pd(_mm_mul_pd(r8, r6), r7));
        r_1D[2] = u_vec * r_1D[2] + p5_1D[3][2];
        r6 = _mm_loadu_pd(&r_1D[0]);
        r7 = _mm_loadu_pd(&p5_1D[4][0]);
        _mm_storeu_pd(&r_1D[0], _mm_add_pd(_mm_mul_pd(r8, r6), r7));
        r_1D[2] = u_vec * r_1D[2] + p5_1D[4][2];

        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        r_2D[0] = p5_2D[0][0];
        r_2D[1] = p5_2D[0][1];
        r_2D[2] = p5_2D[0][2];

        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        r9 = _mm_loadu_pd(&r_2D[0]);
        r10 = _mm_loadu_pd(&p5_2D[1][0]);
        _mm_storeu_pd(&r_2D[0], _mm_add_pd(_mm_mul_pd(r8, r9), r10));
        r_2D[2] = u_vec * r_2D[2] + p5_2D[1][2];
        r_3D[0] = p5_3D[0][0];
        r9 = _mm_loadu_pd(&r_2D[0]);
        r10 = _mm_loadu_pd(&p5_2D[2][0]);
        _mm_storeu_pd(&r_2D[0], _mm_add_pd(_mm_mul_pd(r8, r9), r10));
        r_2D[2] = u_vec * r_2D[2] + p5_2D[2][2];
        r_3D[1] = p5_3D[0][1];
        r9 = _mm_loadu_pd(&r_2D[0]);
        r10 = _mm_loadu_pd(&p5_2D[3][0]);
        _mm_storeu_pd(&r_2D[0], _mm_add_pd(_mm_mul_pd(r8, r9), r10));
        r_2D[2] = u_vec * r_2D[2] + p5_1D[3][2];
        r_3D[2] = p5_3D[0][2];
        r11 = _mm_loadu_pd(&r_3D[0]);
        r12 = _mm_loadu_pd(&p5_3D[1][0]);
        _mm_storeu_pd(&r_3D[0], _mm_add_pd(_mm_mul_pd(r8, r11), r12));
        r_3D[2] = u_vec * r_3D[2] + p5_3D[1][2];
        r11 = _mm_loadu_pd(&r_3D[0]);
        r12 = _mm_loadu_pd(&p5_3D[2][0]);
        _mm_storeu_pd(&r_3D[0], _mm_add_pd(_mm_mul_pd(r8, r11), r12));
        r_3D[2] = u_vec * r_3D[2] + p5_2D[2][2];
    }

    //
    // Arguments    : const double CurvStruct_CoeffP5[6][3]
    //                const double u_vec[10]
    //                double r_0D[10][3]
    //                double r_1D[10][3]
    //                double r_2D[10][3]
    //                double r_3D[10][3]
    // Return Type  : void
    //
    static void EvalTransP5(const double CurvStruct_CoeffP5[6][3], const double u_vec[10], double
                            r_0D[10][3], double r_1D[10][3], double r_2D[10][3], double r_3D[10][3])
    {
        double p5_1D[5][3];
        double p5_2D[4][3];
        double p5_3D[3][3];
        double d;
        double d1;
        double d10;
        double d11;
        double d13;
        double d14;
        double d2;
        double d4;
        double d5;
        double d6;
        double d7;
        double d9;
        ZoneScopedN("EvalTransP5");

        //
        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        for (int k = 0; k < 5; k++) {
            _mm_storeu_pd(&p5_1D[k][0], _mm_mul_pd(_mm_loadu_pd((double *)&CurvStruct_CoeffP5[k][0]),
                           _mm_set1_pd(5.0 - static_cast<double>(k))));
            p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
        }

        __m128d r;
        __m128d r1;
        __m128d r2;
        __m128d r3;
        __m128d r4;

        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        r = _mm_loadu_pd(&p5_1D[0][0]);
        _mm_storeu_pd(&p5_2D[0][0], _mm_mul_pd(r, _mm_set1_pd(4.0)));
        p5_2D[0][2] = p5_1D[0][2] * 4.0;
        r = _mm_loadu_pd(&p5_1D[1][0]);
        r1 = _mm_set1_pd(3.0);
        _mm_storeu_pd(&p5_2D[1][0], _mm_mul_pd(r, r1));
        p5_2D[1][2] = p5_1D[1][2] * 3.0;
        r = _mm_loadu_pd(&p5_1D[2][0]);
        r2 = _mm_set1_pd(2.0);
        _mm_storeu_pd(&p5_2D[2][0], _mm_mul_pd(r, r2));
        p5_2D[2][2] = p5_1D[2][2] * 2.0;
        r = _mm_loadu_pd(&p5_1D[3][0]);
        r3 = _mm_set1_pd(1.0);
        _mm_storeu_pd(&p5_2D[3][0], _mm_mul_pd(r, r3));
        p5_2D[3][2] = p5_1D[3][2];

        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        r4 = _mm_loadu_pd(&p5_2D[0][0]);
        _mm_storeu_pd(&p5_3D[0][0], _mm_mul_pd(r4, r1));
        p5_3D[0][2] = p5_2D[0][2] * 3.0;
        r4 = _mm_loadu_pd(&p5_2D[1][0]);
        _mm_storeu_pd(&p5_3D[1][0], _mm_mul_pd(r4, r2));
        p5_3D[1][2] = p5_2D[1][2] * 2.0;
        r4 = _mm_loadu_pd(&p5_2D[2][0]);
        _mm_storeu_pd(&p5_3D[2][0], _mm_mul_pd(r4, r3));
        p5_3D[2][2] = p5_2D[2][2];

        //
        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        d = CurvStruct_CoeffP5[0][0];
        d1 = CurvStruct_CoeffP5[0][1];
        d2 = CurvStruct_CoeffP5[0][2];
        for (int t = 0; t < 10; t++) {
            r_0D[t][0] = d;
            r_0D[t][1] = d1;
            r_0D[t][2] = d2;
        }

        for (int i = 0; i < 5; i++) {
            for (int b_k = 0; b_k < 10; b_k++) {
                __m128d r5;
                double d3;
                r5 = _mm_loadu_pd(&r_0D[b_k][0]);
                d3 = u_vec[b_k];
                _mm_storeu_pd(&r_0D[b_k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d3), r5),
                               _mm_loadu_pd((double *)&CurvStruct_CoeffP5[i + 1][0])));
                r_0D[b_k][2] = d3 * r_0D[b_k][2] + CurvStruct_CoeffP5[i + 1][2];
            }
        }

        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        d4 = p5_1D[0][0];
        d5 = p5_1D[0][1];
        d6 = p5_1D[0][2];
        for (int b_t = 0; b_t < 10; b_t++) {
            r_1D[b_t][0] = d4;
            r_1D[b_t][1] = d5;
            r_1D[b_t][2] = d6;
        }

        for (int b_i = 0; b_i < 4; b_i++) {
            __m128d r6;
            r6 = _mm_loadu_pd(&p5_1D[b_i + 1][0]);
            for (int c_k = 0; c_k < 10; c_k++) {
                __m128d r7;
                double d8;
                r7 = _mm_loadu_pd(&r_1D[c_k][0]);
                d8 = u_vec[c_k];
                _mm_storeu_pd(&r_1D[c_k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d8), r7), r6));
                r_1D[c_k][2] = d8 * r_1D[c_k][2] + p5_1D[b_i + 1][2];
            }
        }

        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        d7 = p5_2D[0][0];
        d9 = p5_2D[0][1];
        d10 = p5_2D[0][2];
        for (int c_t = 0; c_t < 10; c_t++) {
            r_2D[c_t][0] = d7;
            r_2D[c_t][1] = d9;
            r_2D[c_t][2] = d10;
        }

        for (int c_i = 0; c_i < 3; c_i++) {
            __m128d r8;
            r8 = _mm_loadu_pd(&p5_2D[c_i + 1][0]);
            for (int d_k = 0; d_k < 10; d_k++) {
                __m128d r9;
                double d12;
                r9 = _mm_loadu_pd(&r_2D[d_k][0]);
                d12 = u_vec[d_k];
                _mm_storeu_pd(&r_2D[d_k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d12), r9), r8));
                r_2D[d_k][2] = d12 * r_2D[d_k][2] + p5_2D[c_i + 1][2];
            }
        }

        // POLYVAL Evaluate array of polynomials with same degree.
        //
        //
        //  Use Horner's method for general case where X is an array.
        d11 = p5_3D[0][0];
        d13 = p5_3D[0][1];
        d14 = p5_3D[0][2];
        for (int d_t = 0; d_t < 10; d_t++) {
            r_3D[d_t][0] = d11;
            r_3D[d_t][1] = d13;
            r_3D[d_t][2] = d14;
        }

        for (int d_i = 0; d_i < 2; d_i++) {
            __m128d r10;
            r10 = _mm_loadu_pd(&p5_3D[d_i + 1][0]);
            for (int e_k = 0; e_k < 10; e_k++) {
                __m128d r11;
                double d15;
                r11 = _mm_loadu_pd(&r_3D[e_k][0]);
                d15 = u_vec[e_k];
                _mm_storeu_pd(&r_3D[e_k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d15), r11), r10));
                r_3D[e_k][2] = d15 * r_3D[e_k][2] + p5_3D[d_i + 1][2];
            }
        }
    }

    //
    // Arguments    : const double CurvStruct_CoeffP5[6][3]
    //                const ::coder::array<double, 2U> &u_vec
    //                ::coder::array<double, 2U> &r_0D
    //                ::coder::array<double, 2U> &r_1D
    //                ::coder::array<double, 2U> &r_2D
    //                ::coder::array<double, 2U> &r_3D
    // Return Type  : void
    //
    static void EvalTransP5(const double CurvStruct_CoeffP5[6][3], const ::coder::array<double, 2U>
                            &u_vec, ::coder::array<double, 2U> &r_0D, ::coder::array<double, 2U>
                            &r_1D, ::coder::array<double, 2U> &r_2D, ::coder::array<double, 2U>
                            &r_3D)
    {
        ::coder::array<double, 2U> b;
        ::coder::array<double, 2U> r5;
        double p5_1D[5][3];
        double p5_2D[4][3];
        double p5_3D[3][3];
        ZoneScopedN("EvalTransP5");

        //
        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        for (int k = 0; k < 5; k++) {
            _mm_storeu_pd(&p5_1D[k][0], _mm_mul_pd(_mm_loadu_pd((double *)&CurvStruct_CoeffP5[k][0]),
                           _mm_set1_pd(5.0 - static_cast<double>(k))));
            p5_1D[k][2] = CurvStruct_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
        }

        __m128d r;
        __m128d r1;
        __m128d r2;
        __m128d r3;
        __m128d r4;

        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        r = _mm_loadu_pd(&p5_1D[0][0]);
        _mm_storeu_pd(&p5_2D[0][0], _mm_mul_pd(r, _mm_set1_pd(4.0)));
        p5_2D[0][2] = p5_1D[0][2] * 4.0;
        r = _mm_loadu_pd(&p5_1D[1][0]);
        r1 = _mm_set1_pd(3.0);
        _mm_storeu_pd(&p5_2D[1][0], _mm_mul_pd(r, r1));
        p5_2D[1][2] = p5_1D[1][2] * 3.0;
        r = _mm_loadu_pd(&p5_1D[2][0]);
        r2 = _mm_set1_pd(2.0);
        _mm_storeu_pd(&p5_2D[2][0], _mm_mul_pd(r, r2));
        p5_2D[2][2] = p5_1D[2][2] * 2.0;
        r = _mm_loadu_pd(&p5_1D[3][0]);
        r3 = _mm_set1_pd(1.0);
        _mm_storeu_pd(&p5_2D[3][0], _mm_mul_pd(r, r3));
        p5_2D[3][2] = p5_1D[3][2];

        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        r4 = _mm_loadu_pd(&p5_2D[0][0]);
        _mm_storeu_pd(&p5_3D[0][0], _mm_mul_pd(r4, r1));
        p5_3D[0][2] = p5_2D[0][2] * 3.0;
        r4 = _mm_loadu_pd(&p5_2D[1][0]);
        _mm_storeu_pd(&p5_3D[1][0], _mm_mul_pd(r4, r2));
        p5_3D[1][2] = p5_2D[1][2] * 2.0;
        r4 = _mm_loadu_pd(&p5_2D[2][0]);
        _mm_storeu_pd(&p5_3D[2][0], _mm_mul_pd(r4, r3));
        p5_3D[2][2] = p5_2D[2][2];

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
            r5.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int na;
                na = u_vec.size(1);
                for (int b_k = 0; b_k < na; b_k++) {
                    r5[3 * b_k] = u_vec[b_k];
                    r5[3 * b_k + 1] = u_vec[b_k];
                    r5[3 * b_k + 2] = u_vec[b_k];
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

            r_0D.set_size(3, r5.size(1));
            loop_ub = r5.size(1);
            for (int i3 = 0; i3 < loop_ub; i3++) {
                __m128d r6;
                __m128d r7;
                __m128d r8;
                r6 = _mm_loadu_pd(&r5[3 * i3]);
                r7 = _mm_loadu_pd(&r_0D[3 * i3]);
                r8 = _mm_loadu_pd(&b[3 * i3]);
                _mm_storeu_pd(&r_0D[3 * i3], _mm_add_pd(_mm_mul_pd(r6, r7), r8));
                r_0D[3 * i3 + 2] = r5[3 * i3 + 2] * r_0D[3 * i3 + 2] + b[3 * i3 + 2];
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
            r5.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int b_na;
                b_na = u_vec.size(1);
                for (int c_k = 0; c_k < b_na; c_k++) {
                    r5[3 * c_k] = u_vec[c_k];
                    r5[3 * c_k + 1] = u_vec[c_k];
                    r5[3 * c_k + 2] = u_vec[c_k];
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

            r_1D.set_size(3, r5.size(1));
            b_loop_ub = r5.size(1);
            for (int i6 = 0; i6 < b_loop_ub; i6++) {
                __m128d r10;
                __m128d r11;
                __m128d r9;
                r9 = _mm_loadu_pd(&r5[3 * i6]);
                r10 = _mm_loadu_pd(&r_1D[3 * i6]);
                r11 = _mm_loadu_pd(&b[3 * i6]);
                _mm_storeu_pd(&r_1D[3 * i6], _mm_add_pd(_mm_mul_pd(r9, r10), r11));
                r_1D[3 * i6 + 2] = r5[3 * i6 + 2] * r_1D[3 * i6 + 2] + b[3 * i6 + 2];
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
            r5.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int c_na;
                c_na = u_vec.size(1);
                for (int d_k = 0; d_k < c_na; d_k++) {
                    r5[3 * d_k] = u_vec[d_k];
                    r5[3 * d_k + 1] = u_vec[d_k];
                    r5[3 * d_k + 2] = u_vec[d_k];
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

            r_2D.set_size(3, r5.size(1));
            c_loop_ub = r5.size(1);
            for (int i9 = 0; i9 < c_loop_ub; i9++) {
                __m128d r12;
                __m128d r13;
                __m128d r14;
                r12 = _mm_loadu_pd(&r5[3 * i9]);
                r13 = _mm_loadu_pd(&r_2D[3 * i9]);
                r14 = _mm_loadu_pd(&b[3 * i9]);
                _mm_storeu_pd(&r_2D[3 * i9], _mm_add_pd(_mm_mul_pd(r12, r13), r14));
                r_2D[3 * i9 + 2] = r5[3 * i9 + 2] * r_2D[3 * i9 + 2] + b[3 * i9 + 2];
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
            r5.set_size(3, u_vec.size(1));
            if (u_vec.size(1) != 0) {
                int d_na;
                d_na = u_vec.size(1);
                for (int e_k = 0; e_k < d_na; e_k++) {
                    r5[3 * e_k] = u_vec[e_k];
                    r5[3 * e_k + 1] = u_vec[e_k];
                    r5[3 * e_k + 2] = u_vec[e_k];
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

            r_3D.set_size(3, r5.size(1));
            d_loop_ub = r5.size(1);
            for (int i11 = 0; i11 < d_loop_ub; i11++) {
                __m128d r15;
                __m128d r16;
                __m128d r17;
                r15 = _mm_loadu_pd(&r5[3 * i11]);
                r16 = _mm_loadu_pd(&r_3D[3 * i11]);
                r17 = _mm_loadu_pd(&b[3 * i11]);
                _mm_storeu_pd(&r_3D[3 * i11], _mm_add_pd(_mm_mul_pd(r15, r16), r17));
                r_3D[3 * i11 + 2] = r5[3 * i11 + 2] * r_3D[3 * i11 + 2] + b[3 * i11 + 2];
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
        CurvStruct CurvStruct3_C;
        CurvStruct b_CurvStruct2_C;
        if (!ctx->q_gcode.isempty()) {
            unsigned int Ncrv;
            int i;
            Ncrv = ctx->q_gcode.size();

            //  1 -> stdout
            //  2 -> stderr
            if ((static_cast<unsigned long>(DebugConfig) & 1UL) != 0UL) {
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
    //                const ::coder::array<CurvStruct, 2U> &CurvStructs0
    //                const double amax[3]
    //                double jmax[3]
    //                const ::coder::array<double, 2U> &BasisVal
    //                const ::coder::array<double, 2U> &BasisValD
    //                const ::coder::array<double, 2U> &BasisValDD
    //                const ::coder::array<double, 1U> &BasisIntegr
    //                unsigned long Bl_handle
    //                const ::coder::array<double, 2U> &u_vec
    //                int N_Hor
    //                ::coder::array<double, 2U> &Coeff
    //                int *NCoeff
    //                bool *success
    // Return Type  : void
    //
    static void FeedratePlanning_v4(FeedoptContext *ctx, const ::coder::array<CurvStruct, 2U>
        &CurvStructs0, const double amax[3], double jmax[3], const ::coder::array<double, 2U>
        &BasisVal, const ::coder::array<double, 2U> &BasisValD, const ::coder::array<double, 2U>
        &BasisValDD, const ::coder::array<double, 1U> &BasisIntegr, unsigned long Bl_handle, const ::
        coder::array<double, 2U> &u_vec, int N_Hor, ::coder::array<double, 2U> &Coeff, int *NCoeff,
        bool *success)
    {
        coder::sparse A;
        coder::sparse A_jerk;
        coder::sparse r1;
        ::coder::array<CurvStruct, 2U> b_CurvStructs0;
        ::coder::array<double, 2U> Aeq;
        ::coder::array<double, 2U> Coeff0;
        ::coder::array<double, 2U> Coeff2;
        ::coder::array<double, 2U> b;
        ::coder::array<double, 2U> b_BasisVal;
        ::coder::array<double, 2U> b_BasisValD;
        ::coder::array<double, 2U> b_beq;
        ::coder::array<double, 2U> c_b;
        ::coder::array<double, 2U> c_beq;
        ::coder::array<double, 2U> d_b;
        ::coder::array<double, 2U> f;
        ::coder::array<double, 1U> b_Coeff2;
        ::coder::array<double, 1U> b_b;
        ::coder::array<double, 1U> b_jerk;
        ::coder::array<double, 1U> beq;
        CurvStruct expl_temp;
        double b_c[3];
        double e_b[3];
        double r1D[3];
        double r2D[3];
        double r3D[3];
        double unusedU0[3];
        double unusedU1[3];
        double qD_val;
        double q_val;
        double r0Dx;
        double r0Dy;
        double r0Dz;
        double r1Dx;
        double r1Dy;
        double r1Dz;
        double r2Dx;
        double r2Dy;
        double r2Dz;
        double r3Dx;
        double r3Dy;
        double r3Dz;
        double v3;
        unsigned long u;
        int N;
        int b_NCoeff;
        int b_status;
        int beq_idx_0;
        int c_loop_ub;
        int e_loop_ub;
        int g_loop_ub;
        int i2;
        int loop_ub;
        int status;
        int varargin_2;
        char message[30];
        bool b_success;
        bool c_success;
        bool d_success;
        if (1 > N_Hor) {
            varargin_2 = 0;
        } else {
            varargin_2 = N_Hor;
        }

        N = BasisVal.size(1);

        //  1 -> stdout
        //  2 -> stderr
        u = static_cast<unsigned long>(DebugConfig) & 4UL;
        if (u != 0UL) {
            printf("===============================\n");
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u != 0UL) {
            printf("====== FEEDRATE PLANNING ======\n");
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u != 0UL) {
            printf("===============================\n");
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u != 0UL) {
            printf("v_0  = %f\n", ctx->v_0);
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u != 0UL) {
            printf("at_0 = %f\n", ctx->at_0);
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u != 0UL) {
            printf("v_1  = %f\n", ctx->v_1);
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u != 0UL) {
            printf("at_1 = %f\n", ctx->at_1);
            fflush(stdout);
            for (int k = 0; k < varargin_2; k++) {
                b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, &CurvStructs0[k]);
            }
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u != 0UL) {
            printf("===============================\n");
            fflush(stdout);
        }

        //  1 -> stdout
        //  2 -> stderr
        if (u != 0UL) {
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
            scalarLB = b.size(0) & -2;
            vectorUB = scalarLB - 2;
            for (i2 = 0; i2 <= vectorUB; i2 += 2) {
                __m128d r;
                r = _mm_loadu_pd(&b[i2 + b.size(0) * i1]);
                _mm_storeu_pd(&f[i2 + f.size(0) * i1], _mm_mul_pd(r, _mm_set1_pd(-1.0)));
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
            unsigned long u1;
            int i9;
            int max_increase;

            //  1 -> stdout
            //  2 -> stderr
            u1 = static_cast<unsigned long>(DebugConfig) & 8UL;
            if (u1 != 0UL) {
                printf("Coeff1 = ");
                fflush(stdout);
            }

            i9 = BasisVal.size(1);
            for (int c_k = 0; c_k < i9; c_k++) {
                //  1 -> stdout
                //  2 -> stderr
                if (u1 != 0UL) {
                    printf("%.4f ", Coeff0[c_k]);
                    fflush(stdout);
                }
            }

            //  1 -> stdout
            //  2 -> stderr
            if (u1 != 0UL) {
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
                int b_input_sizes_idx_0;
                int c_input_sizes_idx_0;
                int input_sizes_idx_0;
                b_CurvStructs0.set_size(1, varargin_2);
                for (int i12 = 0; i12 < varargin_2; i12++) {
                    b_CurvStructs0[i12] = CurvStructs0[i12];
                }

                ::coder::array<double, 2U> b_Coeff0;
                b_Coeff0 = Coeff0.reshape(N, varargin_2);
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
                    __m128d r2;

                    //          amax = amax*1.1;
                    ctx->jmax_increase_count++;
                    r2 = _mm_loadu_pd(&jmax[0]);
                    _mm_storeu_pd(&jmax[0], _mm_mul_pd(r2, _mm_set1_pd(2.0)));
                    jmax[2] *= 2.0;

                    //  TODO: valeur à ajuster, avant: 1.1...
                    //  1 -> stdout
                    //  2 -> stderr
                    if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
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
                __m128d r3;
                __m128d r4;
                double c;
                double d;
                double n;
                double u_vec_tilda;
                double z1_idx_0;
                double z1_idx_1;
                int BasisVal_idx_0;
                int i13;

                //
                //  tic
                //  Coeff1 = linprog(f, Atot, btot, Aeq, beq, [], [], options);
                //  toc
                //
                //  1 -> stdout
                //  2 -> stderr
                if (u1 != 0UL) {
                    printf("Coeff3 = ");
                    fflush(stdout);
                }

                i13 = BasisVal.size(1);
                for (int d_k = 0; d_k < i13; d_k++) {
                    //  1 -> stdout
                    //  2 -> stderr
                    if (u1 != 0UL) {
                        printf("%.4f ", Coeff2[d_k]);
                        fflush(stdout);
                    }
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u1 != 0UL) {
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
                    EvalLine(CurvStructs0[0].P0, CurvStructs0[0].P1, u_vec_tilda, unusedU0, r1D, r2D,
                             r3D);
                    break;

                  case CurveType_Helix:
                    //  arc of circle / helix (G02, G03)
                    EvalHelix(CurvStructs0[0].P0, CurvStructs0[0].P1, CurvStructs0[0].HelixCenter,
                              CurvStructs0[0].evec, CurvStructs0[0].theta, CurvStructs0[0].pitch,
                              u_vec_tilda, unusedU0, r1D, r2D, r3D);
                    break;

                  case CurveType_TransP5:
                    //  polynomial transition
                    EvalTransP5(CurvStructs0[0].CoeffP5, u_vec_tilda, unusedU0, r1D, r2D, r3D);
                    break;

                  case CurveType_Spline:
                    //  BSpline
                    ctx->q_splines.get(CurvStructs0[0].sp_index, (&expl_temp));
                    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_vec_tilda, &r0Dx,
                                     &r1Dx, &r2Dx, &r3Dx);
                    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_vec_tilda, &r0Dy,
                                     &r1Dy, &r2Dy, &r3Dy);
                    bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_vec_tilda, &r0Dz,
                                     &r1Dz, &r2Dz, &r3Dz);
                    r1D[0] = r1Dx;
                    r1D[1] = r1Dy;
                    r1D[2] = r1Dz;
                    r2D[0] = r2Dx;
                    r2D[1] = r2Dy;
                    r2D[2] = r2Dz;
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
                r1D[2] = d;
                r2D[2] *= c;
                sqrt_calls++;

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
                        int i_loop_ub;

                        //  ZSpdMode.NN
                        q_val = 1.0;
                        i_loop_ub = BasisVal.size(1);
                        b_Coeff2.set_size(BasisVal.size(1));
                        for (int i17 = 0; i17 < i_loop_ub; i17++) {
                            b_Coeff2[i17] = Coeff2[i17];
                        }

                        bspline_eval(Bl_handle, b_Coeff2, &q_val, &qD_val, &v3);
                    }
                }

                sqrt_calls++;
                r3 = _mm_loadu_pd(&r1D[0]);
                _mm_storeu_pd(&e_b[0], _mm_mul_pd(r3, _mm_set1_pd(qD_val)));
                r4 = _mm_loadu_pd(&r2D[0]);
                _mm_storeu_pd(&b_c[0], _mm_mul_pd(r4, _mm_set1_pd(q_val)));
                sqrt_calls++;
                sqrt_calls++;

                // zeros(3, size(tmp2, 2));
                c_EvalCurvStruct(&ctx->q_splines, CurvStructs0[0].Type, CurvStructs0[0].P0,
                                 CurvStructs0[0].P1, CurvStructs0[0].HelixCenter, CurvStructs0[0].
                                 evec, CurvStructs0[0].theta, CurvStructs0[0].pitch, CurvStructs0[0]
                                 .CoeffP5, CurvStructs0[0].sp_index, CurvStructs0[0].a_param,
                                 CurvStructs0[0].b_param, unusedU1, r1D);
                n = std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0));
                sqrt_calls++;

                //  unit tangential vector
                ctx->at_0 = ((b_c[0] + 0.5 * e_b[0]) * (r1D[0] / n) + (b_c[1] + 0.5 * e_b[1]) *
                             (r1D[1] / n)) + (r2D[2] * q_val + 0.5 * (d * qD_val)) * (r1D[2] / n);

                //  tangential acceleration at the end of first piece in horizon
                ctx->v_0 = std::sqrt((z1_idx_0 + z1_idx_1) + std::pow(d, 2.0)) * std::sqrt(q_val);

                //  Coeff = Coeff3(:, 1);
                //  Coeff = zeros(FeedoptLimits.MaxNCoeff, FeedoptLimits.MaxNHorz);
                //  coder.varsize('Coeff', [Inf, Inf], [1,1]);
                BasisVal_idx_0 = BasisVal.size(1);
                Coeff.set_size(BasisVal.size(1), varargin_2);
                for (int i18 = 0; i18 < varargin_2; i18++) {
                    for (int i19 = 0; i19 < BasisVal_idx_0; i19++) {
                        Coeff[i19 + Coeff.size(0) * i18] = Coeff2[i19 + BasisVal_idx_0 * i18];
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
        static const double c_b[6]{
            -0.5, 1.5, -1.5, 0.5, 0.0, 0.0
        };

        static const double f_b[6]{
            0.5, -1.0, 0.5, 0.0, 0.0, 0.0
        };

        static const signed char b[6]{
            -6, 15, -10, 0, 0, 1
        };

        static const signed char b_b[6]{
            -3, 8, -6, 0, 1, 0
        };

        static const signed char d_b[6]{
            6, -15, 10, 0, 0, 0
        };

        static const signed char e_b[6]{
            -3, 7, -4, 0, 0, 0
        };

        creal_T b_alpha1_v[9];
        creal_T alpha0_v[3];
        creal_T alpha1_v[3];
        double b_alpha0[6][3];
        double b_r0D0[6][3];
        double b_r1D0[6][3];
        double c_r0D0[6][3];
        double CoefPS[16];
        double dv1[10];
        double dv2[10];
        double CostInt_data[9];
        double alpha0_t_data[9];
        double alpha1_t_data[9];
        double b_tmp_data[9];
        double beta0_u_data[9];
        double beta1_u_data[9];
        double c_tmp_data[9];
        double t10_data[9];
        double t11_data[9];
        double t12_data[9];
        double t5_data[9];
        double z1_data[9];
        double A[2][2];
        double dv[4];
        double e_a[3];
        double n0[3];
        double n1[3];
        double t0[3];
        double t1[3];
        double B[2];
        double a;
        double b_a;
        double kappa0;
        double kappa1;
        double unusedU0;
        double unusedU1;
        double unusedU2;
        int Idx_data[9];
        int CostInt_size[1];
        int Idx_size[1];
        int alpha0_t_size[1];
        int alpha1_t_size[1];
        int b_alpha0_t_size[1];
        int b_alpha1_t_size[1];
        int b_tmp_size[1];
        int c_alpha0_t_size[1];
        int t10_size[1];
        int t11_size[1];
        int t5_size[1];
        int tmp_size[1];
        int b_iindx;
        int c_iindx;
        int i10;
        int i12;
        int i13;
        int i21;
        int i22;
        int i23;
        int i24;
        int i9;
        int iindx;
        signed char tmp_data[3];
        bool c_alpha0_t_data[9];
        bool b_alpha0_t_data[3];
        bool b_alpha1_t_data[3];
        bool guard1{
            false
        };

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
            double X_idx_0;
            double X_idx_1;
            double a21;
            int r1;
            int r2;

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
            int c_loop_ub;
            int partialTrueCount;
            int trueCount;
            bool unnamed_idx_0;
            bool unnamed_idx_1;
            bool unnamed_idx_2;

            //  compute resultant of the polynomial system
            //
            alpha1_v[0].re = 0.0;
            alpha1_v[0].im = 0.0;
            alpha1_v[1].re = 0.0;
            alpha1_v[1].im = 0.0;
            alpha1_v[2].re = 0.0;
            alpha1_v[2].im = 0.0;
            dv[0] = CoefPS[3] * CoefPS[15] - CoefPS[7] * CoefPS[14];
            dv[1] = (CoefPS[3] * CoefPS[11] + CoefPS[2] * CoefPS[15]) - CoefPS[6] * CoefPS[14];
            dv[2] = (CoefPS[3] * CoefPS[9] + CoefPS[2] * CoefPS[11]) - CoefPS[5] * CoefPS[14];
            dv[3] = CoefPS[2] * CoefPS[9] - CoefPS[4] * CoefPS[14];
            c_roots(&dv[0], &alpha1_v[0], 4);

            //  all roots of 3th degree polynomial in alpha1
            trueCount = 0;
            unnamed_idx_2 = (std::abs(alpha1_v[0].im) < 1.0E-11);
            unnamed_idx_0 = unnamed_idx_2;
            if (unnamed_idx_2 && (alpha1_v[0].re > 0.0)) {
                trueCount = 1;
            }

            unnamed_idx_2 = (std::abs(alpha1_v[1].im) < 1.0E-11);
            unnamed_idx_1 = unnamed_idx_2;
            if (unnamed_idx_2 && (alpha1_v[1].re > 0.0)) {
                trueCount++;
            }

            unnamed_idx_2 = (std::abs(alpha1_v[2].im) < 1.0E-11);
            if (unnamed_idx_2 && (alpha1_v[2].re > 0.0)) {
                trueCount++;
            }

            partialTrueCount = 0;
            if (unnamed_idx_0 && (alpha1_v[0].re > 0.0)) {
                tmp_data[0] = 1;
                partialTrueCount = 1;
            }

            if (unnamed_idx_1 && (alpha1_v[1].re > 0.0)) {
                tmp_data[partialTrueCount] = 2;
                partialTrueCount++;
            }

            if (unnamed_idx_2 && (alpha1_v[2].re > 0.0)) {
                tmp_data[partialTrueCount] = 3;
            }

            alpha1_t_size[0] = trueCount;
            for (int i3 = 0; i3 < trueCount; i3++) {
                alpha1_t_data[i3] = alpha1_v[tmp_data[i3] - 1].re;
            }

            //  retain only positive real roots
            if ((std::abs(CoefPS[2]) < 1.0E-11) && (std::abs(CoefPS[3]) < 1.0E-11)) {
                double b_CoefPS;
                double c_CoefPS;
                double f_CoefPS;
                double i_CoefPS;
                int loop_ub;
                int scalarLB;
                int vectorUB;
                coder::power(alpha1_t_data, alpha1_t_size, b_tmp_data, tmp_size);
                b_CoefPS = CoefPS[9];
                c_CoefPS = CoefPS[11];
                f_CoefPS = CoefPS[15];
                i_CoefPS = CoefPS[14];
                alpha0_t_size[0] = tmp_size[0];
                loop_ub = tmp_size[0];
                scalarLB = tmp_size[0] & -2;
                vectorUB = scalarLB - 2;
                for (i9 = 0; i9 <= vectorUB; i9 += 2) {
                    __m128d r12;
                    __m128d r13;
                    r12 = _mm_loadu_pd(&b_tmp_data[i9]);
                    r13 = _mm_loadu_pd(&alpha1_t_data[i9]);
                    _mm_storeu_pd(&alpha0_t_data[i9], _mm_div_pd(_mm_mul_pd(_mm_add_pd(_mm_add_pd
                                     (_mm_mul_pd(_mm_set1_pd(b_CoefPS), r12), _mm_mul_pd(_mm_set1_pd
                                       (c_CoefPS), r13)), _mm_set1_pd(f_CoefPS)), _mm_set1_pd(-1.0)),
                                   _mm_set1_pd(i_CoefPS)));
                }

                for (i9 = scalarLB; i9 < loop_ub; i9++) {
                    alpha0_t_data[i9] = -((b_CoefPS * b_tmp_data[i9] + c_CoefPS * alpha1_t_data[i9])
                                          + f_CoefPS) / i_CoefPS;
                }
            } else {
                double e_CoefPS;
                double h_CoefPS;
                double l_CoefPS;
                double o_CoefPS;
                double q_CoefPS;
                double s_CoefPS;
                int c_scalarLB;
                int c_vectorUB;
                for (int k = 0; k < trueCount; k++) {
                    z1_data[k] = std::pow(alpha1_t_data[k], 3.0);
                }

                coder::power(alpha1_t_data, alpha1_t_size, b_tmp_data, tmp_size);
                e_CoefPS = CoefPS[4];
                h_CoefPS = CoefPS[5];
                l_CoefPS = CoefPS[6];
                o_CoefPS = CoefPS[7];
                q_CoefPS = CoefPS[2];
                s_CoefPS = CoefPS[3];
                alpha0_t_size[0] = trueCount;
                c_scalarLB = trueCount & -2;
                c_vectorUB = c_scalarLB - 2;
                for (i12 = 0; i12 <= c_vectorUB; i12 += 2) {
                    __m128d r16;
                    __m128d r17;
                    __m128d r19;
                    r16 = _mm_loadu_pd(&z1_data[0]);
                    r17 = _mm_loadu_pd(&b_tmp_data[0]);
                    r19 = _mm_loadu_pd(&alpha1_t_data[0]);
                    _mm_storeu_pd(&alpha0_t_data[0], _mm_div_pd(_mm_mul_pd(_mm_add_pd(_mm_add_pd
                                     (_mm_add_pd(_mm_mul_pd(_mm_set1_pd(e_CoefPS), r16), _mm_mul_pd
                                       (_mm_set1_pd(h_CoefPS), r17)), _mm_mul_pd(_mm_set1_pd
                                       (l_CoefPS), r19)), _mm_set1_pd(o_CoefPS)), _mm_set1_pd(-1.0)),
                                   _mm_add_pd(_mm_mul_pd(_mm_set1_pd(q_CoefPS), r19), _mm_set1_pd
                                    (s_CoefPS))));
                }

                for (i12 = c_scalarLB; i12 < trueCount; i12++) {
                    double d27;
                    d27 = alpha1_t_data[i12];
                    alpha0_t_data[i12] = -(((e_CoefPS * z1_data[i12] + h_CoefPS * b_tmp_data[i12]) +
                                            l_CoefPS * d27) + o_CoefPS) / (q_CoefPS * d27 + s_CoefPS);
                }
            }

            b_alpha0_t_size[0] = alpha0_t_size[0];
            c_loop_ub = alpha0_t_size[0];
            for (int i14 = 0; i14 < c_loop_ub; i14++) {
                b_alpha0_t_data[i14] = (alpha0_t_data[i14] > 0.0);
            }

            coder::c_eml_find(b_alpha0_t_data, b_alpha0_t_size, Idx_data, Idx_size);
            if (Idx_size[0] <= 0) {
                *status = 3;
            } else {
                // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
                if (Idx_size[0] > 1) {
                    int e_loop_ub;
                    int g_loop_ub;
                    int i16;
                    int i_loop_ub;
                    CostInt_size[0] = static_cast<signed char>(Idx_size[0]);
                    e_loop_ub = static_cast<signed char>(Idx_size[0]);
                    if (0 <= e_loop_ub - 1) {
                        std::memset(&CostInt_data[0], 0, e_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    g_loop_ub = static_cast<signed char>(Idx_size[0]);
                    if (0 <= g_loop_ub - 1) {
                        std::memset(&beta0_u_data[0], 0, g_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    i_loop_ub = static_cast<signed char>(Idx_size[0]);
                    if (0 <= i_loop_ub - 1) {
                        std::memset(&beta1_u_data[0], 0, i_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    i16 = Idx_size[0];
                    for (int c_k = 0; c_k < i16; c_k++) {
                        int i18;
                        i18 = Idx_data[c_k];
                        Calc_beta0_beta1(alpha0_t_data[i18 - 1], alpha1_t_data[i18 - 1], r0D0, t0,
                                         n0, kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[c_k],
                                         &beta1_u_data[c_k]);
                        CostInt_data[c_k] = EvalCostIntegral(alpha0_t_data[i18 - 1],
                            beta0_u_data[c_k], alpha1_t_data[i18 - 1], beta1_u_data[c_k], r0D0, t0,
                            n0, kappa0, r1D0, t1, n1, kappa1);
                    }

                    int alpha0_tmp;
                    coder::internal::minimum(CostInt_data, CostInt_size, &unusedU0, &iindx);
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
        } else if (kappa1 == 0.0) {
            int b_partialTrueCount;
            int b_trueCount;
            int d_loop_ub;
            bool b_unnamed_idx_2;
            bool unnamed_idx_0;
            bool unnamed_idx_1;

            //
            //  compute resultant of the polynomial system
            //
            alpha0_v[0].re = 0.0;
            alpha0_v[0].im = 0.0;
            alpha0_v[1].re = 0.0;
            alpha0_v[1].im = 0.0;
            alpha0_v[2].re = 0.0;
            alpha0_v[2].im = 0.0;
            dv[0] = CoefPS[6] * CoefPS[15] - CoefPS[7] * CoefPS[11];
            dv[1] = (CoefPS[6] * CoefPS[14] - CoefPS[7] * CoefPS[10]) - CoefPS[3] * CoefPS[11];
            dv[2] = (CoefPS[6] * CoefPS[13] - CoefPS[3] * CoefPS[10]) - CoefPS[1] * CoefPS[11];
            dv[3] = CoefPS[6] * CoefPS[12] - CoefPS[1] * CoefPS[10];
            c_roots(&dv[0], &alpha0_v[0], 4);

            //  all roots of 3th degree polynomial in alpha0
            b_trueCount = 0;
            b_unnamed_idx_2 = (std::abs(alpha0_v[0].im) < 1.0E-11);
            unnamed_idx_0 = b_unnamed_idx_2;
            if (b_unnamed_idx_2 && (alpha0_v[0].re > 0.0)) {
                b_trueCount = 1;
            }

            b_unnamed_idx_2 = (std::abs(alpha0_v[1].im) < 1.0E-11);
            unnamed_idx_1 = b_unnamed_idx_2;
            if (b_unnamed_idx_2 && (alpha0_v[1].re > 0.0)) {
                b_trueCount++;
            }

            b_unnamed_idx_2 = (std::abs(alpha0_v[2].im) < 1.0E-11);
            if (b_unnamed_idx_2 && (alpha0_v[2].re > 0.0)) {
                b_trueCount++;
            }

            b_partialTrueCount = 0;
            if (unnamed_idx_0 && (alpha0_v[0].re > 0.0)) {
                tmp_data[0] = 1;
                b_partialTrueCount = 1;
            }

            if (unnamed_idx_1 && (alpha0_v[1].re > 0.0)) {
                tmp_data[b_partialTrueCount] = 2;
                b_partialTrueCount++;
            }

            if (b_unnamed_idx_2 && (alpha0_v[2].re > 0.0)) {
                tmp_data[b_partialTrueCount] = 3;
            }

            alpha0_t_size[0] = b_trueCount;
            for (int i5 = 0; i5 < b_trueCount; i5++) {
                alpha0_t_data[i5] = alpha0_v[tmp_data[i5] - 1].re;
            }

            //  retain only positive real roots
            if ((std::abs(CoefPS[10]) < 1.0E-11) && (std::abs(CoefPS[11]) < 1.0E-11)) {
                double d_CoefPS;
                double g_CoefPS;
                double k_CoefPS;
                double n_CoefPS;
                int b_loop_ub;
                int b_scalarLB;
                int b_vectorUB;
                coder::power(alpha0_t_data, alpha0_t_size, b_tmp_data, tmp_size);
                d_CoefPS = CoefPS[1];
                g_CoefPS = CoefPS[3];
                k_CoefPS = CoefPS[7];
                n_CoefPS = CoefPS[6];
                alpha1_t_size[0] = tmp_size[0];
                b_loop_ub = tmp_size[0];
                b_scalarLB = tmp_size[0] & -2;
                b_vectorUB = b_scalarLB - 2;
                for (i10 = 0; i10 <= b_vectorUB; i10 += 2) {
                    __m128d r14;
                    __m128d r15;
                    r14 = _mm_loadu_pd(&b_tmp_data[i10]);
                    r15 = _mm_loadu_pd(&alpha0_t_data[i10]);
                    _mm_storeu_pd(&alpha1_t_data[i10], _mm_div_pd(_mm_mul_pd(_mm_add_pd(_mm_add_pd
                                     (_mm_mul_pd(_mm_set1_pd(d_CoefPS), r14), _mm_mul_pd(_mm_set1_pd
                                       (g_CoefPS), r15)), _mm_set1_pd(k_CoefPS)), _mm_set1_pd(-1.0)),
                                   _mm_set1_pd(n_CoefPS)));
                }

                for (i10 = b_scalarLB; i10 < b_loop_ub; i10++) {
                    alpha1_t_data[i10] = -((d_CoefPS * b_tmp_data[i10] + g_CoefPS *
                                            alpha0_t_data[i10]) + k_CoefPS) / n_CoefPS;
                }
            } else {
                double j_CoefPS;
                double m_CoefPS;
                double p_CoefPS;
                double r_CoefPS;
                double t_CoefPS;
                double u_CoefPS;
                int d_scalarLB;
                int d_vectorUB;
                for (int b_k = 0; b_k < b_trueCount; b_k++) {
                    z1_data[b_k] = std::pow(alpha0_t_data[b_k], 3.0);
                }

                coder::power(alpha0_t_data, alpha0_t_size, b_tmp_data, tmp_size);
                j_CoefPS = CoefPS[12];
                m_CoefPS = CoefPS[13];
                p_CoefPS = CoefPS[14];
                r_CoefPS = CoefPS[15];
                t_CoefPS = CoefPS[10];
                u_CoefPS = CoefPS[11];
                alpha1_t_size[0] = b_trueCount;
                d_scalarLB = b_trueCount & -2;
                d_vectorUB = d_scalarLB - 2;
                for (i13 = 0; i13 <= d_vectorUB; i13 += 2) {
                    __m128d r18;
                    __m128d r20;
                    __m128d r21;
                    r18 = _mm_loadu_pd(&z1_data[0]);
                    r20 = _mm_loadu_pd(&b_tmp_data[0]);
                    r21 = _mm_loadu_pd(&alpha0_t_data[0]);
                    _mm_storeu_pd(&alpha1_t_data[0], _mm_div_pd(_mm_mul_pd(_mm_add_pd(_mm_add_pd
                                     (_mm_add_pd(_mm_mul_pd(_mm_set1_pd(j_CoefPS), r18), _mm_mul_pd
                                       (_mm_set1_pd(m_CoefPS), r20)), _mm_mul_pd(_mm_set1_pd
                                       (p_CoefPS), r21)), _mm_set1_pd(r_CoefPS)), _mm_set1_pd(-1.0)),
                                   _mm_add_pd(_mm_mul_pd(_mm_set1_pd(t_CoefPS), r21), _mm_set1_pd
                                    (u_CoefPS))));
                }

                for (i13 = d_scalarLB; i13 < b_trueCount; i13++) {
                    double d30;
                    d30 = alpha0_t_data[i13];
                    alpha1_t_data[i13] = -(((j_CoefPS * z1_data[i13] + m_CoefPS * b_tmp_data[i13]) +
                                            p_CoefPS * d30) + r_CoefPS) / (t_CoefPS * d30 + u_CoefPS);
                }
            }

            b_alpha1_t_size[0] = alpha1_t_size[0];
            d_loop_ub = alpha1_t_size[0];
            for (int i15 = 0; i15 < d_loop_ub; i15++) {
                b_alpha1_t_data[i15] = (alpha1_t_data[i15] > 0.0);
            }

            coder::c_eml_find(b_alpha1_t_data, b_alpha1_t_size, Idx_data, Idx_size);

            //
            if (Idx_size[0] <= 0) {
                *status = 4;
            } else {
                // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
                if (Idx_size[0] > 1) {
                    int f_loop_ub;
                    int h_loop_ub;
                    int i17;
                    int j_loop_ub;
                    CostInt_size[0] = static_cast<signed char>(Idx_size[0]);
                    f_loop_ub = static_cast<signed char>(Idx_size[0]);
                    if (0 <= f_loop_ub - 1) {
                        std::memset(&CostInt_data[0], 0, f_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    h_loop_ub = static_cast<signed char>(Idx_size[0]);
                    if (0 <= h_loop_ub - 1) {
                        std::memset(&beta0_u_data[0], 0, h_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    j_loop_ub = static_cast<signed char>(Idx_size[0]);
                    if (0 <= j_loop_ub - 1) {
                        std::memset(&beta1_u_data[0], 0, j_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    i17 = Idx_size[0];
                    for (int d_k = 0; d_k < i17; d_k++) {
                        int i19;
                        i19 = Idx_data[d_k];
                        Calc_beta0_beta1(alpha0_t_data[i19 - 1], alpha1_t_data[i19 - 1], r0D0, t0,
                                         n0, kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[d_k],
                                         &beta1_u_data[d_k]);
                        CostInt_data[d_k] = EvalCostIntegral(alpha0_t_data[i19 - 1],
                            beta0_u_data[d_k], alpha1_t_data[i19 - 1], beta1_u_data[d_k], r0D0, t0,
                            n0, kappa0, r1D0, t1, n1, kappa1);
                    }

                    int b_alpha0_tmp;
                    coder::internal::minimum(CostInt_data, CostInt_size, &unusedU1, &b_iindx);
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

                //
                guard1 = true;
            }
        } else {
            double ab_CoefPS;
            double bb_CoefPS;
            double cb_CoefPS;
            double d;
            double d1;
            double d10;
            double d100;
            double d101;
            double d102;
            double d103;
            double d104;
            double d105;
            double d106;
            double d107;
            double d108;
            double d109;
            double d11;
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
            double d120;
            double d121;
            double d122;
            double d123;
            double d124;
            double d125;
            double d126;
            double d127;
            double d128;
            double d129;
            double d13;
            double d130;
            double d131;
            double d132;
            double d133;
            double d134;
            double d135;
            double d136;
            double d137;
            double d138;
            double d139;
            double d14;
            double d140;
            double d141;
            double d142;
            double d143;
            double d144;
            double d145;
            double d146;
            double d147;
            double d148;
            double d149;
            double d15;
            double d150;
            double d151;
            double d152;
            double d153;
            double d154;
            double d155;
            double d156;
            double d157;
            double d158;
            double d159;
            double d16;
            double d160;
            double d161;
            double d162;
            double d163;
            double d164;
            double d165;
            double d166;
            double d167;
            double d168;
            double d17;
            double d18;
            double d19;
            double d2;
            double d20;
            double d21;
            double d23;
            double d24;
            double d25;
            double d26;
            double d28;
            double d29;
            double d3;
            double d31;
            double d32;
            double d33;
            double d34;
            double d35;
            double d36;
            double d37;
            double d38;
            double d39;
            double d4;
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
            double d5;
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
            double d6;
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
            double d7;
            double d70;
            double d71;
            double d72;
            double d73;
            double d74;
            double d75;
            double d76;
            double d77;
            double d78;
            double d79;
            double d8;
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
            double d9;
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
            double db_CoefPS;
            double eb_CoefPS;
            double fb_CoefPS;
            double gb_CoefPS;
            double hb_CoefPS;
            double ib_CoefPS;
            double jb_CoefPS;
            double kb_CoefPS;
            double lb_CoefPS;
            double mb_CoefPS;
            double nb_CoefPS;
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
            double t2;
            double t20;
            double t21;
            double t3;
            double t4;
            double t5;
            double t6;
            double t7;
            double t8;
            double t9;
            double v_CoefPS;
            double w_CoefPS;
            double x_CoefPS;
            double y_CoefPS;
            int c_partialTrueCount;
            int c_trueCount;
            int e_vectorUB;
            int f_vectorUB;
            int g_vectorUB;
            int h_vectorUB;
            int scalarLB_tmp;

            //  compute resultant of the polynomial system
            //
            // CHARPOLYALPHA1
            //     COEFF_POLY_ALPHA1 = CHARPOLYALPHA1(IN1)
            //     This function was generated by the Symbolic Math Toolbox version 8.3.
            //     25-May-2019 09:07:33
            t2 = std::pow(CoefPS[0], 2.0);
            t3 = std::pow(CoefPS[0], 3.0);
            t4 = std::pow(CoefPS[1], 2.0);
            t5 = std::pow(CoefPS[1], 3.0);
            t6 = std::pow(CoefPS[2], 2.0);
            t7 = std::pow(CoefPS[2], 3.0);
            t8 = std::pow(CoefPS[3], 2.0);
            t9 = std::pow(CoefPS[3], 3.0);
            t10 = std::pow(CoefPS[4], 2.0);
            t11 = std::pow(CoefPS[5], 2.0);
            t12 = std::pow(CoefPS[6], 2.0);
            t13 = std::pow(CoefPS[7], 2.0);
            t14 = std::pow(CoefPS[8], 2.0);
            t15 = std::pow(CoefPS[9], 2.0);
            t16 = std::pow(CoefPS[10], 2.0);
            t17 = std::pow(CoefPS[11], 2.0);
            t18 = std::pow(CoefPS[12], 2.0);
            t19 = std::pow(CoefPS[13], 2.0);
            t20 = std::pow(CoefPS[14], 2.0);
            t21 = std::pow(CoefPS[15], 2.0);
            std::memset(&b_alpha1_v[0], 0, 9U * sizeof(creal_T));
            d = CoefPS[4] * t2;
            d1 = CoefPS[0] * CoefPS[8] * CoefPS[12];
            dv1[0] = (std::pow(CoefPS[4], 3.0) * t18 + d * t14) - d1 * t10 * 2.0;
            d2 = CoefPS[0] * CoefPS[1];
            d3 = CoefPS[4] * CoefPS[8];
            d4 = d2 * CoefPS[4];
            d5 = CoefPS[0] * CoefPS[4];
            d6 = d5 * CoefPS[5];
            d7 = CoefPS[5] * t2;
            d8 = CoefPS[1] * CoefPS[8] * CoefPS[12];
            d9 = d3 * CoefPS[10];
            d10 = CoefPS[0] * CoefPS[10] * CoefPS[12];
            dv1[1] = (((((d7 * t14 + CoefPS[5] * t10 * t18 * 3.0) + d4 * t14 * 2.0) - d8 * t10 * 2.0)
                       + d9 * t2 * 2.0) - d10 * t10 * 2.0) - d6 * CoefPS[8] * CoefPS[12] * 4.0;
            d11 = CoefPS[0] * CoefPS[2];
            d13 = d11 * CoefPS[4];
            d14 = CoefPS[2] * CoefPS[8];
            d15 = CoefPS[5] * CoefPS[8];
            d16 = d2 * CoefPS[5];
            d17 = d4 * CoefPS[8];
            d18 = CoefPS[1] * CoefPS[4];
            d19 = d5 * CoefPS[6];
            d20 = d18 * CoefPS[5];
            d21 = CoefPS[4] * t4;
            d23 = CoefPS[6] * t2;
            d24 = d14 * CoefPS[9];
            d25 = d15 * CoefPS[10];
            d26 = CoefPS[1] * CoefPS[10] * CoefPS[12];
            d28 = d3 * CoefPS[12];
            d29 = d3 * CoefPS[14];
            d31 = CoefPS[4] * CoefPS[9] * CoefPS[13];
            d32 = CoefPS[0] * CoefPS[12] * CoefPS[14];
            d33 = CoefPS[2] * CoefPS[12];
            d34 = d33 * CoefPS[13];
            dv1[2] = (((((((((((((((((((((t3 * t15 + CoefPS[0] * t10 * t19) + d * t16) + d21 * t14)
                + CoefPS[4] * t11 * t18 * 3.0) + d23 * t14) + CoefPS[6] * t10 * t18 * 3.0) + d16 *
                                    t14 * 2.0) - d24 * t2) - d1 * t11 * 2.0) + d25 * t2 * 2.0) - d26
                                * t10 * 2.0) + d28 * t6) + d29 * t2 * 2.0) - d31 * t2 * 2.0) - d32 *
                            t10 * 2.0) - d34 * t10) + d17 * CoefPS[10] * 4.0) - d13 * CoefPS[8] *
                         CoefPS[13]) + d13 * CoefPS[9] * CoefPS[12] * 3.0) - d19 * CoefPS[8] *
                       CoefPS[12] * 4.0) - d20 * CoefPS[8] * CoefPS[12] * 4.0) - d6 * CoefPS[10] *
                CoefPS[12] * 4.0;
            d35 = CoefPS[9] * CoefPS[11];
            d36 = CoefPS[1] * t2;
            d37 = CoefPS[4] * CoefPS[10];
            d38 = d11 * CoefPS[5];
            d39 = CoefPS[0] * CoefPS[3];
            d40 = d39 * CoefPS[4];
            d41 = CoefPS[1] * CoefPS[2];
            d42 = d41 * CoefPS[4];
            d43 = CoefPS[4] * CoefPS[5];
            d44 = CoefPS[3] * CoefPS[8];
            d45 = CoefPS[2] * CoefPS[9];
            d46 = CoefPS[6] * CoefPS[8];
            d47 = d2 * CoefPS[2];
            d48 = d47 * CoefPS[8];
            d49 = d2 * CoefPS[6];
            d50 = d16 * CoefPS[8];
            d51 = CoefPS[2] * CoefPS[3];
            d52 = d51 * CoefPS[4];
            d53 = CoefPS[0] * CoefPS[5];
            d54 = d5 * CoefPS[7];
            d55 = d53 * CoefPS[6];
            d56 = d18 * CoefPS[6];
            d57 = CoefPS[2] * CoefPS[4];
            d58 = CoefPS[5] * t4;
            d59 = CoefPS[7] * t2;
            d60 = d44 * CoefPS[9];
            d61 = d14 * CoefPS[11];
            d62 = d45 * CoefPS[10];
            d63 = d46 * CoefPS[10];
            d64 = d15 * CoefPS[12];
            d65 = d37 * CoefPS[12];
            d66 = d15 * CoefPS[14];
            d67 = CoefPS[5] * CoefPS[9] * CoefPS[13];
            d68 = CoefPS[1] * CoefPS[12] * CoefPS[14];
            d69 = d37 * CoefPS[14];
            d70 = CoefPS[4] * CoefPS[11] * CoefPS[13];
            d71 = CoefPS[3] * CoefPS[12];
            d72 = d71 * CoefPS[13];
            dv1[3] = (((((((((((((((((((((((((((((((((((((((((((((std::pow(CoefPS[5], 3.0) * t18 +
                d35 * t3 * 2.0) + d36 * t15 * 3.0) + CoefPS[1] * t10 * t19) + d7 * t16) + d58 * t14)
                + d59 * t14) + CoefPS[7] * t10 * t18 * 3.0) + d4 * t16 * 2.0) + d49 * t14 * 2.0) +
                d6 * t19 * 2.0) + d43 * CoefPS[6] * t18 * 6.0) - d60 * t2) - d61 * t2) - d62 * t2) -
                d8 * t11 * 2.0) + d9 * t4 * 2.0) - d10 * t11 * 2.0) + d63 * t2 * 2.0) + d64 * t6) +
                d65 * t6) + d66 * t2 * 2.0) - d67 * t2 * 2.0) - d68 * t10 * 2.0) + d69 * t2 * 2.0) -
                d70 * t2 * 2.0) - d72 * t10) - d48 * CoefPS[9] * 2.0) + d50 * CoefPS[10] * 4.0) +
                d17 * CoefPS[14] * 4.0) - d4 * CoefPS[9] * CoefPS[13] * 4.0) - d38 * CoefPS[8] *
                                    CoefPS[13]) + d38 * CoefPS[9] * CoefPS[12] * 3.0) - d40 *
                                  CoefPS[8] * CoefPS[13]) + d40 * CoefPS[9] * CoefPS[12] * 3.0) -
                                d42 * CoefPS[8] * CoefPS[13]) + d42 * CoefPS[9] * CoefPS[12] * 3.0)
                              - d13 * CoefPS[10] * CoefPS[13]) + d13 * CoefPS[11] * CoefPS[12] * 3.0)
                            + d52 * CoefPS[8] * CoefPS[12] * 2.0) - d54 * CoefPS[8] * CoefPS[12] *
                           4.0) - d55 * CoefPS[8] * CoefPS[12] * 4.0) - d56 * CoefPS[8] * CoefPS[12]
                         * 4.0) - d19 * CoefPS[10] * CoefPS[12] * 4.0) - d20 * CoefPS[10] * CoefPS
                       [12] * 4.0) - d6 * CoefPS[12] * CoefPS[14] * 4.0) - d57 * CoefPS[5] * CoefPS
                [12] * CoefPS[13] * 2.0;
            d73 = CoefPS[0] * CoefPS[9];
            d74 = CoefPS[1] * CoefPS[9];
            d75 = CoefPS[3] * CoefPS[9];
            d76 = CoefPS[2] * CoefPS[10];
            d77 = d2 * CoefPS[7];
            d78 = CoefPS[0] * t4;
            d79 = CoefPS[6] * t4;
            d80 = d44 * CoefPS[11];
            d81 = d75 * CoefPS[10];
            d82 = d73 * CoefPS[13];
            d83 = d76 * CoefPS[11];
            d84 = d14 * CoefPS[15];
            d85 = d45 * CoefPS[14];
            d86 = CoefPS[9] * CoefPS[12];
            d87 = CoefPS[9] * CoefPS[15];
            d88 = CoefPS[7] * CoefPS[8];
            d89 = d88 * CoefPS[10];
            d90 = d11 * CoefPS[6];
            d91 = d39 * CoefPS[5];
            d92 = d41 * CoefPS[5];
            d93 = CoefPS[1] * CoefPS[3];
            d94 = d93 * CoefPS[4];
            d95 = d2 * CoefPS[3];
            d96 = d95 * CoefPS[8];
            d97 = d51 * CoefPS[5];
            d98 = CoefPS[1] * CoefPS[5];
            d99 = d53 * CoefPS[7];
            d100 = d18 * CoefPS[7];
            d101 = d98 * CoefPS[6];
            d102 = CoefPS[3] * CoefPS[4];
            d103 = CoefPS[6] * CoefPS[9] * CoefPS[13];
            d104 = CoefPS[5] * CoefPS[10];
            d105 = d104 * CoefPS[14];
            d106 = CoefPS[5] * CoefPS[11] * CoefPS[13];
            d107 = CoefPS[4] * CoefPS[12] * CoefPS[14];
            d108 = CoefPS[4] * CoefPS[13] * CoefPS[15];
            d109 = d47 * CoefPS[9];
            d110 = d104 * CoefPS[12];
            d111 = d46 * CoefPS[14];
            dv1[4] = (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t3 *
                t17 - d86 * t7) + d87 * t3 * 2.0) + d78 * t15 * 3.0) + CoefPS[0] * t11 * t19) + d21 *
                t16) + d * t20) + CoefPS[4] * t12 * t18 * 3.0) + d23 * t16) + d79 * t14) + CoefPS[6]
                * t11 * t18 * 3.0) + d16 * t16 * 2.0) + d77 * t14 * 2.0) + d19 * t19 * 2.0) + d20 *
                t19 * 2.0) + d43 * CoefPS[7] * t18 * 6.0) - d24 * t4) - d1 * t12 * 2.0) + d74 *
                CoefPS[11] * t2 * 6.0) - d80 * t2) - d81 * t2) + d82 * t6) - d83 * t2) + d25 * t4 *
                2.0) - d26 * t11 * 2.0) + d28 * t8) - d84 * t2) - d85 * t2) + d89 * t2 * 2.0) + d29 *
                t4 * 2.0) - d31 * t4 * 2.0) + d46 * CoefPS[12] * t6) - d32 * t11 * 2.0) + d110 * t6)
                - d34 * t11) + d111 * t2 * 2.0) - d103 * t2 * 2.0) + d105 * t2 * 2.0) - d106 * t2 *
                2.0) + d107 * t6) - d108 * t2 * 2.0) - d96 * CoefPS[9] * 2.0) - d48 * CoefPS[11] *
                2.0) - d109 * CoefPS[10] * 2.0) + d49 * CoefPS[8] * CoefPS[10] * 4.0) + d50 *
                CoefPS[14] * 4.0) - d16 * CoefPS[9] * CoefPS[13] * 4.0) + d4 * CoefPS[10] * CoefPS
                [14] * 4.0) - d4 * CoefPS[11] * CoefPS[13] * 4.0) - d90 * CoefPS[8] * CoefPS[13]) +
                d90 * CoefPS[9] * CoefPS[12] * 3.0) - d91 * CoefPS[8] * CoefPS[13]) + d91 * CoefPS[9]
                * CoefPS[12] * 3.0) - d92 * CoefPS[8] * CoefPS[13]) + d92 * CoefPS[9] * CoefPS[12] *
                3.0) - d94 * CoefPS[8] * CoefPS[13]) + d94 * CoefPS[9] * CoefPS[12] * 3.0) - d38 *
                CoefPS[10] * CoefPS[13]) + d38 * CoefPS[11] * CoefPS[12] * 3.0) - d40 * CoefPS[10] *
                CoefPS[13]) + d40 * CoefPS[11] * CoefPS[12] * 3.0) - d42 * CoefPS[10] * CoefPS[13])
                                   + d42 * CoefPS[11] * CoefPS[12] * 3.0) + d97 * CoefPS[8] *
                                  CoefPS[12] * 2.0) + d52 * CoefPS[10] * CoefPS[12] * 2.0) - d99 *
                                CoefPS[8] * CoefPS[12] * 4.0) - d100 * CoefPS[8] * CoefPS[12] * 4.0)
                              - d101 * CoefPS[8] * CoefPS[12] * 4.0) + d13 * CoefPS[12] * CoefPS[15]
                             * 3.0) - d13 * CoefPS[13] * CoefPS[14]) - d54 * CoefPS[10] * CoefPS[12]
                           * 4.0) - d55 * CoefPS[10] * CoefPS[12] * 4.0) - d56 * CoefPS[10] *
                         CoefPS[12] * 4.0) - d19 * CoefPS[12] * CoefPS[14] * 4.0) - d20 * CoefPS[12]
                       * CoefPS[14] * 4.0) - d57 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0) - d102
                * CoefPS[5] * CoefPS[12] * CoefPS[13] * 2.0;
            d112 = CoefPS[11] * CoefPS[15];
            d113 = CoefPS[6] * CoefPS[10];
            d114 = CoefPS[3] * CoefPS[10];
            d115 = CoefPS[7] * t4;
            d116 = d74 * CoefPS[13];
            d117 = d114 * CoefPS[11];
            d118 = CoefPS[0] * CoefPS[11];
            d119 = d118 * CoefPS[13];
            d120 = CoefPS[2] * CoefPS[11];
            d121 = d44 * CoefPS[15];
            d122 = d75 * CoefPS[14];
            d123 = d76 * CoefPS[15];
            d124 = d120 * CoefPS[14];
            d125 = CoefPS[7] * CoefPS[9] * CoefPS[13];
            d126 = d113 * CoefPS[14];
            d127 = CoefPS[6] * CoefPS[11] * CoefPS[13];
            d128 = CoefPS[5] * CoefPS[12] * CoefPS[14];
            d129 = CoefPS[5] * CoefPS[13] * CoefPS[15];
            d130 = d11 * CoefPS[7];
            d131 = d39 * CoefPS[6];
            d132 = d41 * CoefPS[6];
            d133 = d93 * CoefPS[5];
            d134 = d51 * CoefPS[6];
            d135 = CoefPS[0] * CoefPS[6] * CoefPS[7];
            d136 = d98 * CoefPS[7];
            d137 = CoefPS[2] * CoefPS[5];
            d138 = d95 * CoefPS[9];
            d139 = d47 * CoefPS[10];
            d140 = d88 * CoefPS[12];
            d141 = d11 * CoefPS[3];
            dv1[5] =
                (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
                ((((((((((t5 * t15 - CoefPS[11] * CoefPS[12] * t7) + d112 * t3 * 2.0) + d36 * t17 *
                3.0) + CoefPS[1] * t11 * t19) + d58 * t16) + d7 * t20) + CoefPS[5] * t12 * t18 * 3.0)
                + d59 * t16) + d115 * t14) + CoefPS[7] * t11 * t18 * 3.0) + d4 * t20 * 2.0) + d49 *
                t16 * 2.0) + d54 * t19 * 2.0) + d55 * t19 * 2.0) + d56 * t19 * 2.0) + CoefPS[4] *
                CoefPS[6] * CoefPS[7] * t18 * 6.0) + d73 * CoefPS[11] * t4 * 6.0) - d60 * t4) - d61 *
                t4) - d62 * t4) - d8 * t12 * 2.0) - d10 * t12 * 2.0) + d116 * t6) - d117 * t2) + d63
                * t4 * 2.0) + d119 * t6) - d75 * CoefPS[12] * t6 * 3.0) + d74 * CoefPS[15] * t2 *
                6.0) + d64 * t8) - d121 * t2) - d122 * t2) + d65 * t8) - d123 * t2) - d124 * t2) +
                d66 * t4 * 2.0) - d67 * t4 * 2.0) + d140 * t6) - d68 * t11 * 2.0) + d69 * t4 * 2.0)
                - d70 * t4 * 2.0) + d113 * CoefPS[12] * t6) - d72 * t11) + d88 * CoefPS[14] * t2 *
                2.0) - d125 * t2 * 2.0) + d126 * t2 * 2.0) - d127 * t2 * 2.0) + d128 * t6) - d129 *
                t2 * 2.0) - d96 * CoefPS[11] * 2.0) - d138 * CoefPS[10] * 2.0) - d139 * CoefPS[11] *
                2.0) - d48 * CoefPS[15] * 2.0) - d109 * CoefPS[14] * 2.0) + d77 * CoefPS[8] *
                CoefPS[10] * 4.0) + d141 * CoefPS[9] * CoefPS[13] * 2.0) + d2 * CoefPS[6] * CoefPS[8]
                * CoefPS[14] * 4.0) - CoefPS[0] * CoefPS[1] * CoefPS[6] * CoefPS[9] * CoefPS[13] *
                4.0) + d16 * CoefPS[10] * CoefPS[14] * 4.0) - d16 * CoefPS[11] * CoefPS[13] * 4.0) -
                d130 * CoefPS[8] * CoefPS[13]) + d130 * CoefPS[9] * CoefPS[12] * 3.0) - d131 *
                CoefPS[8] * CoefPS[13]) + d131 * CoefPS[9] * CoefPS[12] * 3.0) - d132 * CoefPS[8] *
                CoefPS[13]) + d132 * CoefPS[9] * CoefPS[12] * 3.0) - d133 * CoefPS[8] * CoefPS[13])
                + d133 * CoefPS[9] * CoefPS[12] * 3.0) - d90 * CoefPS[10] * CoefPS[13]) + d90 *
                CoefPS[11] * CoefPS[12] * 3.0) - d91 * CoefPS[10] * CoefPS[13]) + d91 * CoefPS[11] *
                CoefPS[12] * 3.0) - d92 * CoefPS[10] * CoefPS[13]) + d92 * CoefPS[11] * CoefPS[12] *
                3.0) - d94 * CoefPS[10] * CoefPS[13]) + d94 * CoefPS[11] * CoefPS[12] * 3.0) + d134 *
                CoefPS[8] * CoefPS[12] * 2.0) + d97 * CoefPS[10] * CoefPS[12] * 2.0) - d4 * CoefPS
                                  [13] * CoefPS[15] * 4.0) - d135 * CoefPS[8] * CoefPS[12] * 4.0) -
                                d136 * CoefPS[8] * CoefPS[12] * 4.0) + d38 * CoefPS[12] * CoefPS[15]
                               * 3.0) - d38 * CoefPS[13] * CoefPS[14]) + d40 * CoefPS[12] * CoefPS
                             [15] * 3.0) - d40 * CoefPS[13] * CoefPS[14]) - d99 * CoefPS[10] *
                           CoefPS[12] * 4.0) + d42 * CoefPS[12] * CoefPS[15] * 3.0) - d42 * CoefPS
                         [13] * CoefPS[14]) - d100 * CoefPS[10] * CoefPS[12] * 4.0) - d101 * CoefPS
                       [10] * CoefPS[12] * 4.0) + d52 * CoefPS[12] * CoefPS[14] * 2.0) - d54 *
                     CoefPS[12] * CoefPS[14] * 4.0) - d55 * CoefPS[12] * CoefPS[14] * 4.0) - d56 *
                   CoefPS[12] * CoefPS[14] * 4.0) - d57 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0)
                 - d137 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0) - d102 * CoefPS[6] * CoefPS[12]
                * CoefPS[13] * 2.0;
            d142 = CoefPS[1] * CoefPS[11];
            d143 = CoefPS[3] * CoefPS[11];
            d144 = CoefPS[7] * CoefPS[10];
            d145 = d142 * CoefPS[13];
            d146 = d114 * CoefPS[15];
            d147 = d143 * CoefPS[14];
            d148 = CoefPS[0] * CoefPS[13] * CoefPS[15];
            d149 = d144 * CoefPS[12];
            d150 = CoefPS[2] * CoefPS[14] * CoefPS[15];
            d151 = d144 * CoefPS[14];
            d152 = CoefPS[7] * CoefPS[11] * CoefPS[13];
            d153 = CoefPS[12] * CoefPS[15];
            d154 = CoefPS[6] * CoefPS[12] * CoefPS[14];
            d155 = CoefPS[6] * CoefPS[13] * CoefPS[15];
            d156 = d95 * CoefPS[10];
            d157 = d39 * CoefPS[7];
            d158 = d41 * CoefPS[7];
            d159 = d93 * CoefPS[6];
            d160 = d51 * CoefPS[7];
            d161 = CoefPS[1] * CoefPS[6] * CoefPS[7];
            d162 = CoefPS[3] * CoefPS[5];
            dv1[6] =
                (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((
                ((((((((t3 * t21 + std::pow(CoefPS[6], 3.0) * t18) + d35 * t5 * 2.0) - d153 * t7) +
                d78 * t17 * 3.0) + CoefPS[0] * t12 * t19) + d21 * t20) + CoefPS[4] * t13 * t18 * 3.0)
                + d79 * t16) + d23 * t20) + d16 * t20 * 2.0) + d77 * t16 * 2.0) + d99 * t19 * 2.0) +
                d100 * t19 * 2.0) + d101 * t19 * 2.0) + CoefPS[5] * CoefPS[6] * CoefPS[7] * t18 *
                6.0) - d1 * t13 * 2.0) - d80 * t4) - d81 * t4) + d82 * t8) - d83 * t4) - d45 *
                CoefPS[12] * t8 * 3.0) - d26 * t12 * 2.0) + d73 * CoefPS[15] * t4 * 6.0) - d84 * t4)
                - d85 * t4) + d89 * t4 * 2.0) + d145 * t6) - d143 * CoefPS[12] * t6 * 3.0) + CoefPS
                [6] * CoefPS[8] * CoefPS[12] * t8) - d32 * t12 * 2.0) + d142 * CoefPS[15] * t2 * 6.0)
                + d110 * t8) - d34 * t12) - d146 * t2) - d147 * t2) + d111 * t4 * 2.0) - d103 * t4 *
                2.0) + d148 * t6) + d105 * t4 * 2.0) - d106 * t4 * 2.0) + d149 * t6) + d107 * t8) -
                d150 * t2) + d151 * t2 * 2.0) - d152 * t2 * 2.0) - d108 * t4 * 2.0) + d154 * t6) -
                d155 * t2 * 2.0) - d156 * CoefPS[11] * 2.0) - d96 * CoefPS[15] * 2.0) - d138 *
                CoefPS[14] * 2.0) - d139 * CoefPS[15] * 2.0) - d47 * CoefPS[11] * CoefPS[14] * 2.0)
                + d41 * CoefPS[3] * CoefPS[9] * CoefPS[13] * 2.0) + CoefPS[0] * CoefPS[2] * CoefPS[3]
                * CoefPS[11] * CoefPS[13] * 2.0) + CoefPS[0] * CoefPS[1] * CoefPS[7] * CoefPS[8] *
                CoefPS[14] * 4.0) - d77 * CoefPS[9] * CoefPS[13] * 4.0) + d49 * CoefPS[10] * CoefPS
                [14] * 4.0) - d49 * CoefPS[11] * CoefPS[13] * 4.0) - d157 * CoefPS[8] * CoefPS[13])
                + d157 * CoefPS[9] * CoefPS[12] * 3.0) - d158 * CoefPS[8] * CoefPS[13]) + d158 *
                CoefPS[9] * CoefPS[12] * 3.0) - d159 * CoefPS[8] * CoefPS[13]) + d159 * CoefPS[9] *
                CoefPS[12] * 3.0) - d130 * CoefPS[10] * CoefPS[13]) + d130 * CoefPS[11] * CoefPS[12]
                * 3.0) - d131 * CoefPS[10] * CoefPS[13]) + d131 * CoefPS[11] * CoefPS[12] * 3.0) -
                d132 * CoefPS[10] * CoefPS[13]) + d132 * CoefPS[11] * CoefPS[12] * 3.0) - d133 *
                CoefPS[10] * CoefPS[13]) + d133 * CoefPS[11] * CoefPS[12] * 3.0) + d160 * CoefPS[8] *
                CoefPS[12] * 2.0) + d134 * CoefPS[10] * CoefPS[12] * 2.0) - d16 * CoefPS[13] *
                                  CoefPS[15] * 4.0) - d161 * CoefPS[8] * CoefPS[12] * 4.0) + d90 *
                                CoefPS[12] * CoefPS[15] * 3.0) - d90 * CoefPS[13] * CoefPS[14]) +
                              d91 * CoefPS[12] * CoefPS[15] * 3.0) - d91 * CoefPS[13] * CoefPS[14])
                            - d135 * CoefPS[10] * CoefPS[12] * 4.0) + d92 * CoefPS[12] * CoefPS[15] *
                           3.0) - d92 * CoefPS[13] * CoefPS[14]) + d94 * CoefPS[12] * CoefPS[15] *
                         3.0) - d94 * CoefPS[13] * CoefPS[14]) - d136 * CoefPS[10] * CoefPS[12] *
                       4.0) + d97 * CoefPS[12] * CoefPS[14] * 2.0) - d99 * CoefPS[12] * CoefPS[14] *
                     4.0) - d100 * CoefPS[12] * CoefPS[14] * 4.0) - d101 * CoefPS[12] * CoefPS[14] *
                   4.0) - d137 * CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) - d102 * CoefPS[7] *
                 CoefPS[12] * CoefPS[13] * 2.0) - d162 * CoefPS[6] * CoefPS[12] * CoefPS[13] * 2.0;
            d163 = d93 * CoefPS[7];
            d164 = CoefPS[1] * CoefPS[2] * CoefPS[3];
            d165 = CoefPS[1] * CoefPS[13] * CoefPS[15];
            d166 = CoefPS[3] * CoefPS[14] * CoefPS[15];
            d167 = CoefPS[7] * CoefPS[12] * CoefPS[14];
            d168 = CoefPS[7] * CoefPS[13] * CoefPS[15];
            dv1[7] = ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t5 * t17 -
                d86 * t9) + d87 * t5 * 2.0) + d36 * t21 * 3.0) + CoefPS[1] * t12 * t19) + d58 * t20)
                + CoefPS[5] * t13 * t18 * 3.0) + d115 * t16) + d59 * t20) + CoefPS[7] * t12 * t18 *
                3.0) + d49 * t20 * 2.0) + d135 * t19 * 2.0) + d136 * t19 * 2.0) - d8 * t13 * 2.0) -
                d10 * t13 * 2.0) + d116 * t8) - d117 * t4) + d119 * t8) - d120 * CoefPS[12] * t8 *
                3.0) + d118 * CoefPS[15] * t4 * 6.0) - d121 * t4) - d122 * t4) - d123 * t4) - d124 *
                t4) + d140 * t8) - d68 * t12 * 2.0) + CoefPS[6] * CoefPS[10] * CoefPS[12] * t8) -
                d72 * t12) + CoefPS[7] * CoefPS[8] * CoefPS[14] * t4 * 2.0) - d125 * t4 * 2.0) +
                d165 * t6) + d126 * t4 * 2.0) - d127 * t4 * 2.0) - d71 * CoefPS[15] * t6 * 3.0) +
                d128 * t8) - d166 * t2) - d129 * t4 * 2.0) + d167 * t6) - d168 * t2 * 2.0) - d156 *
                CoefPS[15] * 2.0) - d95 * CoefPS[11] * CoefPS[14] * 2.0) + d164 * CoefPS[11] *
                CoefPS[13] * 2.0) - d47 * CoefPS[14] * CoefPS[15] * 2.0) + d77 * CoefPS[10] *
                CoefPS[14] * 4.0) - d77 * CoefPS[11] * CoefPS[13] * 4.0) - d163 * CoefPS[8] *
                CoefPS[13]) + d163 * CoefPS[9] * CoefPS[12] * 3.0) + d141 * CoefPS[13] * CoefPS[15] *
                2.0) - d157 * CoefPS[10] * CoefPS[13]) + d157 * CoefPS[11] * CoefPS[12] * 3.0) -
                d158 * CoefPS[10] * CoefPS[13]) + d158 * CoefPS[11] * CoefPS[12] * 3.0) - d159 *
                CoefPS[10] * CoefPS[13]) + d159 * CoefPS[11] * CoefPS[12] * 3.0) + d160 * CoefPS[10]
                                    * CoefPS[12] * 2.0) - d49 * CoefPS[13] * CoefPS[15] * 4.0) +
                                  d130 * CoefPS[12] * CoefPS[15] * 3.0) - d130 * CoefPS[13] *
                                 CoefPS[14]) + d131 * CoefPS[12] * CoefPS[15] * 3.0) - d131 *
                               CoefPS[13] * CoefPS[14]) + d132 * CoefPS[12] * CoefPS[15] * 3.0) -
                             d132 * CoefPS[13] * CoefPS[14]) + d133 * CoefPS[12] * CoefPS[15] * 3.0)
                           - d133 * CoefPS[13] * CoefPS[14]) - d161 * CoefPS[10] * CoefPS[12] * 4.0)
                         + d134 * CoefPS[12] * CoefPS[14] * 2.0) - d135 * CoefPS[12] * CoefPS[14] *
                        4.0) - d136 * CoefPS[12] * CoefPS[14] * 4.0) - CoefPS[2] * CoefPS[6] *
                      CoefPS[7] * CoefPS[12] * CoefPS[13] * 2.0) - d162 * CoefPS[7] * CoefPS[12] *
                CoefPS[13] * 2.0;
            dv1[8] = ((((((((((((((((((((((((((((((((((-CoefPS[11] * CoefPS[12] * t9 + d112 * t5 *
                2.0) + d78 * t21 * 3.0) + CoefPS[0] * t13 * t19) + d79 * t20) + CoefPS[6] * t13 *
                t18 * 3.0) + d77 * t20 * 2.0) + d161 * t19 * 2.0) - d26 * t13 * 2.0) + d145 * t8) -
                d32 * t13 * 2.0) - d34 * t13) - d146 * t4) - d147 * t4) + d148 * t8) - d33 * CoefPS
                [15] * t8 * 3.0) + d149 * t8) - d150 * t4) + d151 * t4 * 2.0) - d152 * t4 * 2.0) +
                                    d154 * t8) - d155 * t4 * 2.0) - d95 * CoefPS[14] * CoefPS[15] *
                                  2.0) + d164 * CoefPS[13] * CoefPS[15] * 2.0) - d163 * CoefPS[10] *
                                CoefPS[13]) + d163 * CoefPS[11] * CoefPS[12] * 3.0) - d77 * CoefPS
                              [13] * CoefPS[15] * 4.0) + d157 * CoefPS[12] * CoefPS[15] * 3.0) -
                            d157 * CoefPS[13] * CoefPS[14]) + d158 * CoefPS[12] * CoefPS[15] * 3.0)
                          - d158 * CoefPS[13] * CoefPS[14]) + d159 * CoefPS[12] * CoefPS[15] * 3.0)
                        - d159 * CoefPS[13] * CoefPS[14]) + d160 * CoefPS[12] * CoefPS[14] * 2.0) -
                      d161 * CoefPS[12] * CoefPS[14] * 4.0) - CoefPS[3] * CoefPS[6] * CoefPS[7] *
                CoefPS[12] * CoefPS[13] * 2.0;
            dv1[9] = (((((((((((t5 * t21 + std::pow(CoefPS[7], 3.0) * t18) - d153 * t9) + CoefPS[1] *
                              t13 * t19) + d115 * t20) - d68 * t13 * 2.0) - d72 * t13) + d165 * t8)
                         - d166 * t4) + d167 * t8) - d168 * t4 * 2.0) + d163 * CoefPS[12] * CoefPS
                      [15] * 3.0) - d163 * CoefPS[13] * CoefPS[14];
            for (int i20 = 0; i20 < 10; i20++) {
                dv2[i20] = dv1[9 - i20];
            }

            c_roots(&dv2[0], &b_alpha1_v[0], 10);

            //  all roots of 9th degree polynomial in alpha1
            c_trueCount = 0;
            c_partialTrueCount = 0;
            for (int e_k = 0; e_k < 9; e_k++) {
                double d169;
                bool g_b;
                g_b = (std::abs(b_alpha1_v[e_k].im) < 1.0E-11);
                d169 = b_alpha1_v[e_k].re;
                if (g_b && (d169 > 0.0)) {
                    c_trueCount++;
                    alpha1_t_data[c_partialTrueCount] = d169;
                    c_partialTrueCount++;
                }
            }

            alpha1_t_size[0] = c_trueCount;

            //  retain only positive real roots
            //  compute corresponding values of alpha0
            // CALCALPHA0
            //     ALPHA0_S = CALCALPHA0(ALPHA1,IN2)
            //     This function was generated by the Symbolic Math Toolbox version 8.3.
            //     25-May-2019 09:07:35
            coder::power(alpha1_t_data, alpha1_t_size, t5_data, t5_size);
            v_CoefPS = CoefPS[3];
            w_CoefPS = CoefPS[2];
            t10_size[0] = c_trueCount;
            scalarLB_tmp = c_trueCount & -2;
            e_vectorUB = scalarLB_tmp - 2;
            for (i21 = 0; i21 <= e_vectorUB; i21 += 2) {
                __m128d r22;
                r22 = _mm_loadu_pd(&alpha1_t_data[i21]);
                _mm_storeu_pd(&t10_data[i21], _mm_add_pd(_mm_set1_pd(v_CoefPS), _mm_mul_pd(r22,
                                _mm_set1_pd(w_CoefPS))));
            }

            for (i21 = scalarLB_tmp; i21 < c_trueCount; i21++) {
                t10_data[i21] = v_CoefPS + alpha1_t_data[i21] * w_CoefPS;
            }

            x_CoefPS = CoefPS[1];
            y_CoefPS = CoefPS[0];
            t11_size[0] = c_trueCount;
            f_vectorUB = scalarLB_tmp - 2;
            for (i22 = 0; i22 <= f_vectorUB; i22 += 2) {
                __m128d r23;
                r23 = _mm_loadu_pd(&alpha1_t_data[i22]);
                _mm_storeu_pd(&t11_data[i22], _mm_div_pd(_mm_set1_pd(1.0), _mm_add_pd(_mm_set1_pd
                                (x_CoefPS), _mm_mul_pd(_mm_set1_pd(y_CoefPS), r23))));
            }

            for (i22 = scalarLB_tmp; i22 < c_trueCount; i22++) {
                t11_data[i22] = 1.0 / (x_CoefPS + y_CoefPS * alpha1_t_data[i22]);
            }

            for (int f_k = 0; f_k < c_trueCount; f_k++) {
                z1_data[f_k] = std::pow(alpha1_t_data[f_k], 3.0);
            }

            ab_CoefPS = CoefPS[7];
            bb_CoefPS = CoefPS[6];
            cb_CoefPS = CoefPS[5];
            db_CoefPS = CoefPS[4];
            g_vectorUB = scalarLB_tmp - 2;
            for (i23 = 0; i23 <= g_vectorUB; i23 += 2) {
                __m128d r24;
                __m128d r25;
                __m128d r26;
                r24 = _mm_loadu_pd(&alpha1_t_data[i23]);
                r25 = _mm_loadu_pd(&t5_data[i23]);
                r26 = _mm_loadu_pd(&z1_data[i23]);
                _mm_storeu_pd(&t12_data[i23], _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_set1_pd(ab_CoefPS),
                                 _mm_mul_pd(r24, _mm_set1_pd(bb_CoefPS))), _mm_mul_pd(_mm_set1_pd
                                 (cb_CoefPS), r25)), _mm_mul_pd(_mm_set1_pd(db_CoefPS), r26)));
            }

            for (i23 = scalarLB_tmp; i23 < c_trueCount; i23++) {
                t12_data[i23] = ((ab_CoefPS + alpha1_t_data[i23] * bb_CoefPS) + cb_CoefPS *
                                 t5_data[i23]) + db_CoefPS * z1_data[i23];
            }

            coder::power(t11_data, t11_size, b_tmp_data, tmp_size);
            coder::power(t10_data, t10_size, c_tmp_data, b_tmp_size);
            eb_CoefPS = CoefPS[15];
            fb_CoefPS = CoefPS[11];
            gb_CoefPS = CoefPS[9];
            hb_CoefPS = CoefPS[13];
            ib_CoefPS = CoefPS[12];
            jb_CoefPS = CoefPS[14];
            kb_CoefPS = CoefPS[10];
            lb_CoefPS = CoefPS[8];
            mb_CoefPS = CoefPS[13];
            nb_CoefPS = CoefPS[12];
            h_vectorUB = scalarLB_tmp - 2;
            for (i24 = 0; i24 <= h_vectorUB; i24 += 2) {
                __m128d r27;
                __m128d r28;
                __m128d r29;
                __m128d r30;
                __m128d r31;
                __m128d r32;
                __m128d r33;
                r27 = _mm_loadu_pd(&alpha1_t_data[i24]);
                r28 = _mm_loadu_pd(&t5_data[i24]);
                r29 = _mm_loadu_pd(&t11_data[i24]);
                r30 = _mm_loadu_pd(&t12_data[i24]);
                r31 = _mm_loadu_pd(&t10_data[i24]);
                r32 = _mm_loadu_pd(&b_tmp_data[i24]);
                r33 = _mm_loadu_pd(&c_tmp_data[i24]);
                _mm_storeu_pd(&alpha0_t_data[i24], _mm_div_pd(_mm_mul_pd(_mm_add_pd(_mm_sub_pd
                                 (_mm_add_pd(_mm_add_pd(_mm_set1_pd(eb_CoefPS), _mm_mul_pd(r27,
                                     _mm_set1_pd(fb_CoefPS))), _mm_mul_pd(_mm_set1_pd(gb_CoefPS),
                                    r28)), _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(hb_CoefPS), r29), r30)),
                                 _mm_mul_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(ib_CoefPS), r31), r32),
                                  r30)), _mm_set1_pd(-1.0)), _mm_sub_pd(_mm_sub_pd(_mm_add_pd
                                 (_mm_add_pd(_mm_set1_pd(jb_CoefPS), _mm_mul_pd(r27, _mm_set1_pd
                                    (kb_CoefPS))), _mm_mul_pd(_mm_set1_pd(lb_CoefPS), r28)),
                                 _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(mb_CoefPS), r31), r29)),
                                _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(nb_CoefPS), r29), _mm_sub_pd(r30,
                                  _mm_mul_pd(r33, r29))))));
            }

            for (i24 = scalarLB_tmp; i24 < c_trueCount; i24++) {
                double d170;
                double d171;
                double d172;
                double d173;
                double d174;
                d170 = alpha1_t_data[i24];
                d171 = t5_data[i24];
                d172 = t11_data[i24];
                d173 = t12_data[i24];
                d174 = t10_data[i24];
                alpha0_t_data[i24] = -((((eb_CoefPS + d170 * fb_CoefPS) + gb_CoefPS * d171) -
                                        hb_CoefPS * d172 * d173) + ib_CoefPS * d174 * b_tmp_data[i24]
                                       * d173) / ((((jb_CoefPS + d170 * kb_CoefPS) + lb_CoefPS *
                    d171) - mb_CoefPS * d174 * d172) - nb_CoefPS * d172 * (d173 - c_tmp_data[i24] *
                    d172));
            }

            //
            c_alpha0_t_size[0] = c_trueCount;
            for (int i25 = 0; i25 < c_trueCount; i25++) {
                c_alpha0_t_data[i25] = (alpha0_t_data[i25] > 0.0);
            }

            coder::c_eml_find(c_alpha0_t_data, c_alpha0_t_size, Idx_data, Idx_size);

            //
            if (Idx_size[0] <= 0) {
                *status = 5;
            } else {
                // c_assert(numel(alpha0_u) > 0, 'no positive solution of polynomial system');
                if (Idx_size[0] > 1) {
                    int i26;
                    int k_loop_ub;
                    int l_loop_ub;
                    int m_loop_ub;
                    CostInt_size[0] = static_cast<signed char>(Idx_size[0]);
                    k_loop_ub = static_cast<signed char>(Idx_size[0]);
                    if (0 <= k_loop_ub - 1) {
                        std::memset(&CostInt_data[0], 0, k_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    l_loop_ub = static_cast<signed char>(Idx_size[0]);
                    if (0 <= l_loop_ub - 1) {
                        std::memset(&beta0_u_data[0], 0, l_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    m_loop_ub = static_cast<signed char>(Idx_size[0]);
                    if (0 <= m_loop_ub - 1) {
                        std::memset(&beta1_u_data[0], 0, m_loop_ub * sizeof(double));
                    }

                    //  preallocating
                    i26 = Idx_size[0];
                    for (int g_k = 0; g_k < i26; g_k++) {
                        int i27;
                        i27 = Idx_data[g_k];
                        Calc_beta0_beta1(alpha0_t_data[i27 - 1], alpha1_t_data[i27 - 1], r0D0, t0,
                                         n0, kappa0, r1D0, t1, n1, kappa1, &beta0_u_data[g_k],
                                         &beta1_u_data[g_k]);
                        CostInt_data[g_k] = EvalCostIntegral(alpha0_t_data[i27 - 1],
                            beta0_u_data[g_k], alpha1_t_data[i27 - 1], beta1_u_data[g_k], r0D0, t0,
                            n0, kappa0, r1D0, t1, n1, kappa1);
                    }

                    int c_alpha0_tmp;
                    coder::internal::minimum(CostInt_data, CostInt_size, &unusedU2, &c_iindx);
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

                guard1 = true;
            }
        }

        if (guard1) {
            __m128d r;
            __m128d r3;
            __m128d r8;
            __m128d r9;
            double a_tmp;
            double b_a_tmp;
            double c_a;
            double d_a;

            //
            //  Hermite basis
            //  evaluate coefficients as sum of basis functions
            a_tmp = std::pow(*alpha0, 2.0);
            c_a = kappa0 * a_tmp;
            b_a_tmp = std::pow(*alpha1, 2.0);
            d_a = kappa1 * b_a_tmp;
            r = _mm_loadu_pd(&t0[0]);
            for (int i1 = 0; i1 < 6; i1++) {
                int i2;
                int i4;
                i2 = b[i1];
                _mm_storeu_pd(&b_r0D0[i1][0], _mm_mul_pd(_mm_loadu_pd((double *)&r0D0[0]),
                               _mm_set1_pd(static_cast<double>(i2))));
                i4 = b_b[i1];
                _mm_storeu_pd(&b_alpha0[i1][0], _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(*alpha0), r),
                               _mm_set1_pd(static_cast<double>(i4))));
                b_r0D0[i1][2] = r0D0[2] * static_cast<double>(i2);
                b_alpha0[i1][2] = *alpha0 * t0[2] * static_cast<double>(i4);
            }

            __m128d b_r1;
            __m128d b_r2;
            b_r1 = _mm_loadu_pd(&t0[0]);
            b_r2 = _mm_loadu_pd(&n0[0]);
            _mm_storeu_pd(&e_a[0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(a), b_r1), _mm_mul_pd
                           (_mm_set1_pd(c_a), b_r2)));
            e_a[2] = a * t0[2] + c_a * n0[2];
            r3 = _mm_loadu_pd(&e_a[0]);
            for (int i6 = 0; i6 < 6; i6++) {
                __m128d r5;
                __m128d r7;
                double d12;
                int i7;
                r5 = _mm_loadu_pd(&b_r0D0[i6][0]);
                r7 = _mm_loadu_pd(&b_alpha0[i6][0]);
                d12 = c_b[i6];
                _mm_storeu_pd(&c_r0D0[i6][0], _mm_add_pd(_mm_add_pd(r5, r7), _mm_add_pd(_mm_set1_pd
                                (0.0), _mm_mul_pd(r3, _mm_set1_pd(d12)))));
                i7 = d_b[i6];
                _mm_storeu_pd(&b_r1D0[i6][0], _mm_mul_pd(_mm_loadu_pd((double *)&r1D0[0]),
                               _mm_set1_pd(static_cast<double>(i7))));
                c_r0D0[i6][2] = (b_r0D0[i6][2] + b_alpha0[i6][2]) + e_a[2] * d12;
                b_r1D0[i6][2] = r1D0[2] * static_cast<double>(i7);
            }

            __m128d r4;
            __m128d r6;
            r4 = _mm_loadu_pd(&t1[0]);
            r6 = _mm_loadu_pd(&n1[0]);
            _mm_storeu_pd(&e_a[0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(b_a), r4), _mm_mul_pd
                           (_mm_set1_pd(d_a), r6)));
            e_a[2] = b_a * t1[2] + d_a * n1[2];
            r8 = _mm_loadu_pd(&t1[0]);
            r9 = _mm_loadu_pd(&e_a[0]);
            for (int i8 = 0; i8 < 6; i8++) {
                __m128d r10;
                __m128d r11;
                double d22;
                int i11;
                r10 = _mm_loadu_pd(&c_r0D0[i8][0]);
                r11 = _mm_loadu_pd(&b_r1D0[i8][0]);
                i11 = e_b[i8];
                d22 = f_b[i8];
                _mm_storeu_pd(&p5_3D[i8][0], _mm_add_pd(_mm_add_pd(_mm_add_pd(r10, r11), _mm_add_pd
                                (_mm_set1_pd(0.0), _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(*alpha1), r8),
                                  _mm_set1_pd(static_cast<double>(i11))))), _mm_mul_pd(r9,
                                _mm_set1_pd(d22))));
                p5_3D[i8][2] = ((c_r0D0[i8][2] + b_r1D0[i8][2]) + *alpha1 * t1[2] * static_cast<
                                double>(i11)) + e_a[2] * d22;
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
    //                const double CurvStruct_HelixCenter[3]
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
        const double CurvStruct_P1[3], const double CurvStruct_HelixCenter[3], const double
        CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch, const double
        CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_FeedRate, double
        CurvStruct_a_param, double CurvStruct_b_param)
    {
        CurvStruct expl_temp;
        double r1D[10][3];
        double r2D[10][3];
        double r2t[10][3];
        double r3D[10][3];
        double r3t[10][3];
        double unusedU0[10][3];
        double z1[10][3];
        double r0Dx[10];
        double r0Dy[10];
        double r0Dz[10];
        double r1Dx[10];
        double r1Dy[10];
        double r1Dz[10];
        double r2Dx[10];
        double r2Dy[10];
        double r2Dz[10];
        double r3Dx[10];
        double r3Dy[10];
        double r3Dz[10];
        double u_vec_tilda[10];
        double b_z_data[9];
        double z_data[9];
        double A[3];
        double J[3];
        double Feedrate;
        double b_c;
        double c;
        double d;
        double d10;
        double d2;
        double d4;
        double d7;
        double d8;
        int b_partialTrueCount;
        int b_trueCount;
        int partialTrueCount;
        int trueCount;
        char message[30];
        signed char b_tmp_data[3];
        signed char tmp_data[3];

        //  rdot = r1D * u1d
        //  rdot'*rdot = r1D'*r1D * u1d
        //  ConstantFeedrate = r1D'*r1D * u1d     (1)
        //  coder.cstructname(CurvStruct, 'CurvStruct')
        //
        //
        for (int i = 0; i < 10; i++) {
            r1D[i][0] = 0.0;
            r2D[i][0] = 0.0;
            r3D[i][0] = 0.0;
            r1D[i][1] = 0.0;
            r2D[i][1] = 0.0;
            r3D[i][1] = 0.0;
            r1D[i][2] = 0.0;
            r2D[i][2] = 0.0;
            r3D[i][2] = 0.0;
            u_vec_tilda[i] = CurvStruct_a_param * (0.1111111111111111 * static_cast<double>(i)) +
                CurvStruct_b_param;
        }

        switch (CurvStruct_Type) {
          case CurveType_Line:
            //  line (G01)
            EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, unusedU0, r1D, r2D, r3D);
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_HelixCenter, CurvStruct_evec,
                      CurvStruct_theta, CurvStruct_pitch, u_vec_tilda, unusedU0, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, unusedU0, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            //  BSpline
            ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_vec_tilda, r0Dx, r1Dx,
                             r2Dx, r3Dx);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_vec_tilda, r0Dy, r1Dy,
                             r2Dy, r3Dy);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_vec_tilda, r0Dz, r1Dz,
                             r2Dz, r3Dz);
            for (int i2 = 0; i2 < 10; i2++) {
                r1D[i2][0] = r1Dx[i2];
                r1D[i2][1] = r1Dy[i2];
                r1D[i2][2] = r1Dz[i2];
                r2D[i2][0] = r2Dx[i2];
                r2D[i2][1] = r2Dy[i2];
                r2D[i2][2] = r2Dz[i2];
                r3D[i2][0] = r3Dx[i2];
                r3D[i2][1] = r3Dy[i2];
                r3D[i2][2] = r3Dz[i2];
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

        //  from (1):
        for (int i3 = 0; i3 < 10; i3++) {
            __m128d r;
            __m128d r1;
            __m128d r2;
            r = _mm_loadu_pd(&r1D[i3][0]);
            _mm_storeu_pd(&r1D[i3][0], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r));
            r1 = _mm_loadu_pd(&r2D[i3][0]);
            _mm_storeu_pd(&r2D[i3][0], _mm_mul_pd(_mm_set1_pd(c), r1));
            r2 = _mm_loadu_pd(&r3D[i3][0]);
            _mm_storeu_pd(&r3D[i3][0], _mm_mul_pd(_mm_set1_pd(b_c), r2));
            r1D[i3][2] *= CurvStruct_a_param;
            r2D[i3][2] *= c;
            r3D[i3][2] *= b_c;
        }

        //  u2d = 0;
        //  u3d = 0;
        //  + r1D*u2d
        //  + 3*r2D*u1d*u2d + r1d*u3d
        //  These 2 equations tell us that to obtain the values for other
        //  feedrates, they have to be multiplied by the scale.^2 and scale.^3
        for (int k = 0; k < 10; k++) {
            __m128d r3;
            double d1;
            double d3;
            d1 = 1.0 / ((std::abs(r1D[k][0]) + std::abs(r1D[k][1])) + std::abs(r1D[k][2]));
            d3 = std::pow(d1, 2.0);
            r3 = _mm_loadu_pd(&r2D[k][0]);
            _mm_storeu_pd(&r2t[k][0], _mm_mul_pd(r3, _mm_set1_pd(d3)));
            r2t[k][2] = r2D[k][2] * d3;
            d3 = std::pow(d1, 3.0);
            r3t[k][0] = r3D[k][0] * d3;
            z1[k][0] = std::abs(r2t[k][0]);
            r3t[k][1] = r3D[k][1] * d3;
            z1[k][1] = std::abs(r2t[k][1]);
            r3t[k][2] = r3D[k][2] * d3;
            z1[k][2] = std::abs(r2t[k][2]);
        }

        d = z1[0][0];
        d2 = z1[0][1];
        d4 = z1[0][2];
        for (int j = 0; j < 9; j++) {
            double d5;
            double d6;
            double d9;
            d5 = z1[j + 1][0];
            if (d < d5) {
                d = d5;
            }

            d6 = z1[j + 1][1];
            if (d2 < d6) {
                d2 = d6;
            }

            d9 = z1[j + 1][2];
            if (d4 < d9) {
                d4 = d9;
            }
        }

        A[2] = d4;
        A[1] = d2;
        A[0] = d;
        for (int b_k = 0; b_k < 10; b_k++) {
            z1[b_k][0] = std::abs(r3t[b_k][0]);
            z1[b_k][1] = std::abs(r3t[b_k][1]);
            z1[b_k][2] = std::abs(r3t[b_k][2]);
        }

        d7 = z1[0][0];
        d8 = z1[0][1];
        d10 = z1[0][2];
        for (int b_j = 0; b_j < 9; b_j++) {
            double d11;
            double d12;
            double d13;
            d11 = z1[b_j + 1][0];
            if (d7 < d11) {
                d7 = d11;
            }

            d12 = z1[b_j + 1][1];
            if (d8 < d12) {
                d8 = d12;
            }

            d13 = z1[b_j + 1][2];
            if (d10 < d13) {
                d10 = d13;
            }
        }

        J[2] = d10;
        J[1] = d8;
        J[0] = d7;
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

        for (int i4 = 0; i4 < trueCount; i4++) {
            int z_tmp;
            z_tmp = tmp_data[i4] - 1;
            z_data[i4] = A[z_tmp] / ctx_cfg_amax[z_tmp];
        }

        b_trueCount = 0;
        if (d7 != 0.0) {
            b_trueCount = 1;
        }

        if (d8 != 0.0) {
            b_trueCount++;
        }

        if (d10 != 0.0) {
            b_trueCount++;
        }

        b_partialTrueCount = 0;
        if (d7 != 0.0) {
            b_tmp_data[0] = 1;
            b_partialTrueCount = 1;
        }

        if (d8 != 0.0) {
            b_tmp_data[b_partialTrueCount] = 2;
            b_partialTrueCount++;
        }

        if (d10 != 0.0) {
            b_tmp_data[b_partialTrueCount] = 3;
        }

        for (int i5 = 0; i5 < b_trueCount; i5++) {
            int b_z_tmp;
            b_z_tmp = b_tmp_data[i5] - 1;
            b_z_data[i5] = J[b_z_tmp] / ctx_cfg_jmax[b_z_tmp];
        }

        if ((trueCount == 0) || (b_trueCount == 0)) {
            Feedrate = CurvStruct_FeedRate;
        } else {
            double b_ex;
            double d_ex;
            double e_ex;
            double ex_tmp;
            double x_idx_1;
            if (trueCount <= 2) {
                if (trueCount == 1) {
                    b_ex = z_data[0];
                } else if (z_data[0] < z_data[1]) {
                    b_ex = z_data[1];
                } else {
                    b_ex = z_data[0];
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

                b_ex = ex;
            }

            if (b_trueCount <= 2) {
                if (b_trueCount == 1) {
                    d_ex = b_z_data[0];
                } else if (b_z_data[0] < b_z_data[1]) {
                    d_ex = b_z_data[1];
                } else {
                    d_ex = b_z_data[0];
                }
            } else {
                double c_ex;
                c_ex = b_z_data[0];
                if (b_z_data[0] < b_z_data[1]) {
                    c_ex = b_z_data[1];
                }

                if (c_ex < b_z_data[2]) {
                    c_ex = b_z_data[2];
                }

                d_ex = c_ex;
            }

            x_idx_1 = 1.0 / std::pow(d_ex, 0.33333333333333331);
            ex_tmp = 1.0 / std::pow(b_ex, 0.5);
            e_ex = ex_tmp;
            if (ex_tmp > x_idx_1) {
                e_ex = x_idx_1;
            }

            if (e_ex > CurvStruct_FeedRate) {
                e_ex = CurvStruct_FeedRate;
            }

            Feedrate = e_ex;
        }

        return Feedrate;
    }

    //
    // Arguments    : const queue_coder *ctx_q_splines
    //                double ctx_cfg_NGridLengthSpline
    //                CurveType Curv_Type
    //                const double Curv_P0[3]
    //                const double Curv_P1[3]
    //                const double Curv_HelixCenter[3]
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
        Curv_HelixCenter[3], const double Curv_evec[3], double Curv_theta, double Curv_pitch, const
        double Curv_CoeffP5[6][3], int Curv_sp_index, double Curv_a_param, double Curv_b_param)
    {
        static const double a[9]{
            0.055555555555555552, 0.16666666666666666, 0.27777777777777779, 0.38888888888888884, 0.5,
                0.61111111111111116, 0.7222222222222221, 0.83333333333333326, 0.94444444444444442
        };

        static const char b_message[29]{
            'B', 'A', 'D', ' ', 'C', 'U', 'R', 'V', 'E', ' ', 'T', 'Y', 'P', 'E', ' ', 'I', 'N', ' ',
                'L', 'E', 'N', 'G', 'T', 'H', ' ', 'C', 'U', 'R', 'V'
        };

        double y[9][3];
        double p5_1D[5][3];
        double Integrand[9];
        double b_y1[9];
        double x[9];
        double r1D[3];
        double unusedU0[3];
        double unusedU1[3];
        double unusedU2[3];
        double L;
        double b_y;
        char message[29];
        if ((Curv_Type == CurveType_Helix) || (Curv_Type == CurveType_Line)) {
            //  coder.cstructname(CurvStruct, 'CurvStruct')
            //
            //
            if (Curv_Type == CurveType_Line) {
                //  line (G01)
                EvalLine(Curv_P0, Curv_P1, Curv_b_param, unusedU0, r1D, unusedU1, unusedU2);
            } else {
                //  arc of circle / helix (G02, G03)
                EvalHelix(Curv_P0, Curv_P1, Curv_HelixCenter, Curv_evec, Curv_theta, Curv_pitch,
                          Curv_b_param, unusedU0, r1D, unusedU1, unusedU2);
            }

            L = std::sqrt((std::pow(Curv_a_param * r1D[0], 2.0) + std::pow(Curv_a_param * r1D[1],
                            2.0)) + std::pow(Curv_a_param * r1D[2], 2.0));
            sqrt_calls++;
        } else if (Curv_Type == CurveType_Spline) {
            L = SplineLengthApprox(ctx_q_splines, ctx_cfg_NGridLengthSpline, Curv_sp_index,
                                   Curv_b_param, Curv_a_param + Curv_b_param);
        } else if (Curv_Type == CurveType_TransP5) {
            double d;
            double d1;
            double d2;
            double work;
            int ixLead;
            int iyLead;

            //  computes approximately the arc length of a parametric spline / RHG
            // MYPOLYDER Differentiate polynomial.
            //
            // u  = u(:).';
            for (int k = 0; k < 5; k++) {
                _mm_storeu_pd(&p5_1D[k][0], _mm_mul_pd(_mm_loadu_pd((double *)&Curv_CoeffP5[k][0]),
                               _mm_set1_pd(5.0 - static_cast<double>(k))));
                p5_1D[k][2] = Curv_CoeffP5[k][2] * (5.0 - static_cast<double>(k));
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
            d = p5_1D[0][0];
            d1 = p5_1D[0][1];
            d2 = p5_1D[0][2];
            for (int t = 0; t < 9; t++) {
                double tmp2;
                double work_tmp;
                tmp2 = work;
                work_tmp = 0.1111111111111111 * static_cast<double>(ixLead);
                work = work_tmp;
                b_y1[iyLead] = work_tmp - tmp2;
                ixLead++;
                iyLead++;
                y[t][0] = d;
                y[t][1] = d1;
                y[t][2] = d2;
            }

            for (int b_i = 0; b_i < 4; b_i++) {
                __m128d r;
                r = _mm_loadu_pd(&p5_1D[b_i + 1][0]);
                for (int c_k = 0; c_k < 9; c_k++) {
                    __m128d r2;
                    double d3;
                    r2 = _mm_loadu_pd(&y[c_k][0]);
                    d3 = a[c_k];
                    _mm_storeu_pd(&y[c_k][0], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(d3), r2), r));
                    y[c_k][2] = d3 * y[c_k][2] + p5_1D[b_i + 1][2];
                }
            }

            for (int b_k = 0; b_k < 9; b_k++) {
                Integrand[b_k] = std::pow(y[b_k][0], 2.0);
                Integrand[b_k] += std::pow(y[b_k][1], 2.0);
                Integrand[b_k] += std::pow(y[b_k][2], 2.0);
            }

            __m128d r1;
            __m128d r3;
            __m128d r4;
            sqrt_calls++;
            r1 = _mm_loadu_pd(&Integrand[0]);
            r3 = _mm_sqrt_pd(r1);
            _mm_storeu_pd(&Integrand[0], r3);
            r4 = _mm_loadu_pd(&b_y1[0]);
            _mm_storeu_pd(&x[0], _mm_mul_pd(r3, r4));
            r1 = _mm_loadu_pd(&Integrand[2]);
            r3 = _mm_sqrt_pd(r1);
            _mm_storeu_pd(&Integrand[2], r3);
            r4 = _mm_loadu_pd(&b_y1[2]);
            _mm_storeu_pd(&x[2], _mm_mul_pd(r3, r4));
            r1 = _mm_loadu_pd(&Integrand[4]);
            r3 = _mm_sqrt_pd(r1);
            _mm_storeu_pd(&Integrand[4], r3);
            r4 = _mm_loadu_pd(&b_y1[4]);
            _mm_storeu_pd(&x[4], _mm_mul_pd(r3, r4));
            r1 = _mm_loadu_pd(&Integrand[6]);
            r3 = _mm_sqrt_pd(r1);
            _mm_storeu_pd(&Integrand[6], r3);
            r4 = _mm_loadu_pd(&b_y1[6]);
            _mm_storeu_pd(&x[6], _mm_mul_pd(r3, r4));
            x[8] = std::sqrt(Integrand[8]) * b_y1[8];
            b_y = x[0];
            for (int d_k = 0; d_k < 8; d_k++) {
                b_y += x[d_k + 1];
            }

            L = b_y;
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
    //                const ::coder::array<double, 1U> &CurOptStruct_Coeff
    //                unsigned long Bl_handle
    //                double u
    //                double dt
    //                double *ukp1
    //                double *qk
    //                double *dk
    // Return Type  : void
    //
    static void Resample(ZSpdMode CurOptStruct_zspdmode, bool CurOptStruct_UseConstJerk, double
                         CurOptStruct_ConstJerk, const ::coder::array<double, 1U>
                         &CurOptStruct_Coeff, unsigned long Bl_handle, double u, double dt, double
                         *ukp1, double *qk, double *dk)
    {
        static const char b_message[26]{
            'Z', 'N', ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'u', 's', 'i', 'n', 'g', ' ', 'c', 'o',
                'n', 's', 't', ' ', 'j', 'e', 'r', 'k'
        };

        static const char e_message[26]{
            'N', 'Z', ' ', 'i', 's', ' ', 'n', 'o', 't', ' ', 'u', 's', 'i', 'n', 'g', ' ', 'c', 'o',
                'n', 's', 't', ' ', 'j', 'e', 'r', 'k'
        };

        static const char d_message[16]{
            'N', 'N', ' ', 'i', 's', ' ', 'u', 's', 'i', 'n', 'g', ' ', 'j', 'e', 'r', 'k'
        };

        double b_dk;
        double b_qk;
        double unusedU3;
        char message[26];
        char c_message[16];
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
            bspline_eval(Bl_handle, CurOptStruct_Coeff, &b_qk, &b_dk, &unusedU3);
            *qk = b_qk;
            *dk = b_dk;
            sqrt_calls++;
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
        static const char b_message[27]{
            'C', 'o', 'm', 'p', 'r', 'e', 's', 's', 'i', 'n', 'g', ' ', 'q', 'u', 'e', 'u', 'e', ' ',
                'i', 's', ' ', 'e', 'm', 'p', 't', 'y', '!'
        };

        ::coder::array<bool, 2U> c_expl_temp;
        CurvStruct CurvStruct1;
        CurvStruct CurvStruct1_C;
        CurvStruct CurvStruct2_C;
        CurvStruct CurvStruct3_C;
        CurvStruct CurvStruct_T;
        CurvStruct NextCurv;
        CurvStruct b_CurvStruct2_C;
        CurvStruct b_ctx;
        CurvStruct b_expl_temp;
        CurvStruct expl_temp;
        double p5[6][3];
        double P0[3];
        double P1[3];
        double dv[3];
        double dv1[3];
        double r0D0[3];
        double r0D0_1[3];
        double r0D0_2[3];
        double r0D1[3];
        double r0D1_1[3];
        double r0D1_2[3];
        double r0D2[3];
        double r1D0[3];
        double r1D0_1[3];
        double r1D0_2[3];
        double r1D1[3];
        double r1D1_1[3];
        double r1D1_2[3];
        double r1D2[3];
        double expl_temp_data[1];
        double alpha0;
        double alpha1;
        double d;
        double d1;
        double d2;
        double d3;
        int expl_temp_size[2];
        int tmp_size[2];
        int tmp_data[1];
        int ret;
        char message[27];
        TransitionResult status;
        if (!ctx->q_compress.isempty()) {
            unsigned int Ncrv;
            unsigned int k;
            ctx->q_compress.get((static_cast<double>(1.0)), (&b_ctx));

            //  to satisfy the coder
            Ncrv = ctx->q_compress.size();

            //  1 -> stdout
            //  2 -> stderr
            if ((static_cast<unsigned long>(DebugConfig) & 1UL) != 0UL) {
                printf("Smoothing...\n");
                fflush(stdout);
            }

            k = 1U;
            if (Ncrv > 1U) {
                ctx->q_compress.get((static_cast<double>(1.0)), (&CurvStruct1));
                while (k < Ncrv) {
                    ctx->q_compress.get((static_cast<double>(k) + 1.0), (&NextCurv));
                    if ((CurvStruct1.zspdmode == ZSpdMode_NN) && (NextCurv.zspdmode == ZSpdMode_NN))
                    {
                        double CutOff;
                        double Length_Threshold;
                        unsigned long u;
                        bool guard1{
                            false
                        };

                        CutOff = ctx->cfg.CutOff;
                        Length_Threshold = 3.0 * ctx->cfg.CutOff;

                        //  DebugLog(DebugCfg.Transitions, ...
                        //      '========== CalcTransition ==========\n')
                        u = static_cast<unsigned long>(DebugConfig) & 8UL;
                        if (u != 0UL) {
                            b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                                              &CurvStruct1);
                            b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, &NextCurv);
                        }

                        CurvStruct_T = CurvStruct1;

                        // default value
                        b_EvalCurvStruct(&ctx->q_splines, CurvStruct1.Type, CurvStruct1.P0,
                                         CurvStruct1.P1, CurvStruct1.HelixCenter, CurvStruct1.evec,
                                         CurvStruct1.theta, CurvStruct1.pitch, CurvStruct1.CoeffP5,
                                         CurvStruct1.sp_index, CurvStruct1.a_param,
                                         CurvStruct1.b_param, r0D0_1, r0D1_1);
                        c_EvalCurvStruct(&ctx->q_splines, CurvStruct1.Type, CurvStruct1.P0,
                                         CurvStruct1.P1, CurvStruct1.HelixCenter, CurvStruct1.evec,
                                         CurvStruct1.theta, CurvStruct1.pitch, CurvStruct1.CoeffP5,
                                         CurvStruct1.sp_index, CurvStruct1.a_param,
                                         CurvStruct1.b_param, r0D0_2, r0D1_2);
                        b_EvalCurvStruct(&ctx->q_splines, NextCurv.Type, NextCurv.P0, NextCurv.P1,
                                         NextCurv.HelixCenter, NextCurv.evec, NextCurv.theta,
                                         NextCurv.pitch, NextCurv.CoeffP5, NextCurv.sp_index,
                                         NextCurv.a_param, NextCurv.b_param, r1D0_1, r1D1_1);
                        c_EvalCurvStruct(&ctx->q_splines, NextCurv.Type, NextCurv.P0, NextCurv.P1,
                                         NextCurv.HelixCenter, NextCurv.evec, NextCurv.theta,
                                         NextCurv.pitch, NextCurv.CoeffP5, NextCurv.sp_index,
                                         NextCurv.a_param, NextCurv.b_param, r1D0_2, r1D1_2);

                        //  colinearity test
                        guard1 = false;
                        if ((CurvStruct1.Type != CurveType_Helix) && (NextCurv.Type !=
                                CurveType_Helix)) {
                            double absxk;
                            double scale;
                            double t;
                            bool value;
                            scale = 3.3121686421112381E-170;
                            absxk = std::abs(r0D1_2[0]);
                            if (absxk > 3.3121686421112381E-170) {
                                d = 1.0;
                                scale = absxk;
                            } else {
                                t = absxk / 3.3121686421112381E-170;
                                d = t * t;
                            }

                            absxk = std::abs(r0D1_2[1]);
                            if (absxk > scale) {
                                t = scale / absxk;
                                d = d * t * t + 1.0;
                                scale = absxk;
                            } else {
                                t = absxk / scale;
                                d += t * t;
                            }

                            absxk = std::abs(r0D1_2[2]);
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
                                double b_absxk;
                                double b_scale;
                                double b_t;
                                b_scale = 3.3121686421112381E-170;
                                b_absxk = std::abs(r1D1_1[0]);
                                if (b_absxk > 3.3121686421112381E-170) {
                                    d1 = 1.0;
                                    b_scale = b_absxk;
                                } else {
                                    b_t = b_absxk / 3.3121686421112381E-170;
                                    d1 = b_t * b_t;
                                }

                                b_absxk = std::abs(r1D1_1[1]);
                                if (b_absxk > b_scale) {
                                    b_t = b_scale / b_absxk;
                                    d1 = d1 * b_t * b_t + 1.0;
                                    b_scale = b_absxk;
                                } else {
                                    b_t = b_absxk / b_scale;
                                    d1 += b_t * b_t;
                                }

                                b_absxk = std::abs(r1D1_1[2]);
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
                                    d2 = 57.295779513082323 * std::acos(((r0D1_2[0] * r1D1_1[0] +
                                        r0D1_2[1] * r1D1_1[1]) + r0D1_2[2] * r1D1_1[2]) / (d * d1));
                                    coder::b_cosd(&d2);
                                    d3 = ctx->cfg.CollTolDeg;
                                    coder::b_cosd(&d3);
                                    value = (d2 > d3);
                                }
                            }

                            if (value) {
                                //  && norm(r0D2 - r1D2) < 10*eps && collinear(r0D2, r1D2, 1e-2)
                                status = TransitionResult_Collinear;
                                CurvStruct1_C = CurvStruct1;
                                CurvStruct2_C = NextCurv;
                            } else {
                                guard1 = true;
                            }
                        } else {
                            guard1 = true;
                        }

                        if (guard1) {
                            double L1;
                            double L2;
                            L1 = LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                                            CurvStruct1.Type, CurvStruct1.P0, CurvStruct1.P1,
                                            CurvStruct1.HelixCenter, CurvStruct1.evec,
                                            CurvStruct1.theta, CurvStruct1.pitch,
                                            CurvStruct1.CoeffP5, CurvStruct1.sp_index,
                                            CurvStruct1.a_param, CurvStruct1.b_param);
                            L2 = LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                                            NextCurv.Type, NextCurv.P0, NextCurv.P1,
                                            NextCurv.HelixCenter, NextCurv.evec, NextCurv.theta,
                                            NextCurv.pitch, NextCurv.CoeffP5, NextCurv.sp_index,
                                            NextCurv.a_param, NextCurv.b_param);

                            //  CutOff calculation
                            if ((CurvStruct1.Type != CurveType_Spline) && (NextCurv.Type !=
                                    CurveType_Spline)) {
                                if ((L1 < Length_Threshold) || (L2 < Length_Threshold)) {
                                    CutOff = std::fmin(L1, L2) / 3.0;
                                }
                            } else {
                                double x;
                                double y;
                                if (CurvStruct1.Type == CurveType_Spline) {
                                    double u1_tilda;
                                    int b_loop_ub;
                                    int c_loop_ub;
                                    ctx->q_splines.get(CurvStruct1.sp_index, (&expl_temp));

                                    //  In a very general case we may cut a spline several times
                                    //  at the end;
                                    //  If a spline had already been cut at the end,
                                    //  we must compute the corresponding
                                    //  native spline parameter (u1_tilda) value
                                    //  This value will be different from 1 in this special case
                                    u1_tilda = CurvStruct1.a_param + CurvStruct1.b_param;

                                    //  We need to find the previous spline knot u0_tilda...
                                    c_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
                                    b_loop_ub = expl_temp.sp.knots.size(1);
                                    for (int i2 = 0; i2 < b_loop_ub; i2++) {
                                        c_expl_temp[i2] = (expl_temp.sp.knots[i2] < u1_tilda);
                                    }

                                    coder::b_eml_find(c_expl_temp, tmp_data, tmp_size);
                                    expl_temp_size[0] = 1;
                                    expl_temp_size[1] = tmp_size[1];
                                    c_loop_ub = tmp_size[1];
                                    for (int i3 = 0; i3 < c_loop_ub; i3++) {
                                        expl_temp_data[i3] = expl_temp.sp.knots[tmp_data[i3] - 1];
                                    }

                                    x = SplineLengthApprox(&ctx->q_splines,
                                                           ctx->cfg.NGridLengthSpline,
                                                           CurvStruct1.sp_index, expl_temp_data,
                                                           expl_temp_size, u1_tilda) / 2.0;
                                } else if (L1 < Length_Threshold) {
                                    x = L1 / 3.0;
                                } else {
                                    x = ctx->cfg.CutOff;
                                }

                                if (NextCurv.Type == CurveType_Spline) {
                                    int d_loop_ub;
                                    int e_loop_ub;
                                    int loop_ub;
                                    ctx->q_splines.get(NextCurv.sp_index, (&b_expl_temp));
                                    expl_temp.sp.knots.set_size(1, b_expl_temp.sp.knots.size(1));
                                    loop_ub = b_expl_temp.sp.knots.size(1);
                                    for (int i1 = 0; i1 < loop_ub; i1++) {
                                        expl_temp.sp.knots[i1] = b_expl_temp.sp.knots[i1];
                                    }

                                    //  In a very general case we may cut a spline several times
                                    //  at the beginning;
                                    //  If a spline had already been cut at the beginning,
                                    //  we must compute the corresponding
                                    //  native spline parameter (u0_tilda) value
                                    //  This value will be different from 0 in this special case
                                    //  We need to find the next spline knot u1_tilda...
                                    c_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
                                    d_loop_ub = expl_temp.sp.knots.size(1);
                                    for (int i4 = 0; i4 < d_loop_ub; i4++) {
                                        c_expl_temp[i4] = (expl_temp.sp.knots[i4] > NextCurv.b_param);
                                    }

                                    coder::eml_find(c_expl_temp, tmp_data, tmp_size);
                                    expl_temp_size[0] = 1;
                                    expl_temp_size[1] = tmp_size[1];
                                    e_loop_ub = tmp_size[1];
                                    for (int i5 = 0; i5 < e_loop_ub; i5++) {
                                        expl_temp_data[i5] = expl_temp.sp.knots[tmp_data[i5] - 1];
                                    }

                                    y = SplineLengthApprox(&ctx->q_splines,
                                                           ctx->cfg.NGridLengthSpline,
                                                           NextCurv.sp_index, NextCurv.b_param,
                                                           expl_temp_data, expl_temp_size) / 2.0;
                                } else if (L2 < Length_Threshold) {
                                    y = L2 / 3.0;
                                } else {
                                    y = ctx->cfg.CutOff;
                                }

                                CutOff = std::fmin(x, y);
                            }

                            //  DebugLog(DebugCfg.Transitions, ...
                            //      'CutOff = %.3f\n', CutOff)
                            CurvStruct1_C = CurvStruct1;
                            CutCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                                          &CurvStruct1_C, CutOff);
                            CurvStruct2_C = NextCurv;
                            b_CutCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                                            &CurvStruct2_C, CutOff);

                            //  1 -> stdout
                            //  2 -> stderr
                            if (u != 0UL) {
                                printf("========== AFTER CUTTING \n");
                                fflush(stdout);
                                b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                                                  &CurvStruct1_C);
                                b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                                                  &CurvStruct2_C);
                            }

                            b_EvalCurvStruct(&ctx->q_splines, CurvStruct1_C.Type, CurvStruct1_C.P0,
                                             CurvStruct1_C.P1, CurvStruct1_C.HelixCenter,
                                             CurvStruct1_C.evec, CurvStruct1_C.theta,
                                             CurvStruct1_C.pitch, CurvStruct1_C.CoeffP5,
                                             CurvStruct1_C.sp_index, CurvStruct1_C.a_param,
                                             CurvStruct1_C.b_param, r0D0, r0D1, r0D2);
                            c_EvalCurvStruct(&ctx->q_splines, CurvStruct2_C.Type, CurvStruct2_C.P0,
                                             CurvStruct2_C.P1, CurvStruct2_C.HelixCenter,
                                             CurvStruct2_C.evec, CurvStruct2_C.theta,
                                             CurvStruct2_C.pitch, CurvStruct2_C.CoeffP5,
                                             CurvStruct2_C.sp_index, CurvStruct2_C.a_param,
                                             CurvStruct2_C.b_param, r1D0, r1D1, r1D2);

                            //  G2 transition calculation
                            G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2, p5, &ret,
                                &alpha0, &alpha1);
                            if (ret == 1) {
                                //  standard case
                                //  transition CurvStruct calculation
                                // POLYVAL Evaluate array of polynomials with same degree.
                                //
                                //
                                //  Use Horner's method for general case where X is an array.
                                // POLYVAL Evaluate array of polynomials with same degree.
                                //
                                //
                                //  Use Horner's method for general case where X is an array.
                                P1[0] = p5[0][0];
                                P1[1] = p5[0][1];
                                P1[2] = p5[0][2];
                                for (int b_i = 0; b_i < 5; b_i++) {
                                    __m128d r;
                                    __m128d r2;
                                    double P0_tmp;
                                    P0[0] = p5[b_i + 1][0];
                                    P0[1] = p5[b_i + 1][1];
                                    P0_tmp = p5[b_i + 1][2];
                                    P0[2] = P0_tmp;
                                    r = _mm_loadu_pd(&P1[0]);
                                    r2 = _mm_loadu_pd(&p5[b_i + 1][0]);
                                    _mm_storeu_pd(&P1[0], _mm_add_pd(r, r2));
                                    P1[2] += P0_tmp;
                                }

                                dv[0] = 0.0;
                                dv1[0] = 0.0;
                                dv[1] = 0.0;
                                dv1[1] = 0.0;
                                dv[2] = 0.0;
                                dv1[2] = 0.0;
                                ConstrCurvStruct(CurveType_TransP5, ZSpdMode_NN, P0, P1, dv, dv1,
                                                 0.0, 0.0, p5, CurvStruct1.FeedRate, &CurvStruct_T);
                                status = TransitionResult_Ok;
                            } else if (ret == 6) {
                                unsigned long u2;

                                //  TODO: decide in the future...
                                //  Now we ignore and construct the transition curve anyway
                                // POLYVAL Evaluate array of polynomials with same degree.
                                //
                                //
                                //  Use Horner's method for general case where X is an array.
                                // POLYVAL Evaluate array of polynomials with same degree.
                                //
                                //
                                //  Use Horner's method for general case where X is an array.
                                P1[0] = p5[0][0];
                                P1[1] = p5[0][1];
                                P1[2] = p5[0][2];
                                for (int c_i = 0; c_i < 5; c_i++) {
                                    __m128d r1;
                                    __m128d r3;
                                    double b_P0_tmp;
                                    P0[0] = p5[c_i + 1][0];
                                    P0[1] = p5[c_i + 1][1];
                                    b_P0_tmp = p5[c_i + 1][2];
                                    P0[2] = b_P0_tmp;
                                    r1 = _mm_loadu_pd(&P1[0]);
                                    r3 = _mm_loadu_pd(&p5[c_i + 1][0]);
                                    _mm_storeu_pd(&P1[0], _mm_add_pd(r1, r3));
                                    P1[2] += b_P0_tmp;
                                }

                                dv[0] = 0.0;
                                dv1[0] = 0.0;
                                dv[1] = 0.0;
                                dv1[1] = 0.0;
                                dv[2] = 0.0;
                                dv1[2] = 0.0;
                                ConstrCurvStruct(CurveType_TransP5, ZSpdMode_NN, P0, P1, dv, dv1,
                                                 0.0, 0.0, p5, CurvStruct1.FeedRate, &CurvStruct_T);
                                status = TransitionResult_Ok;

                                //  1 -> stdout
                                //  2 -> stderr
                                u2 = static_cast<unsigned long>(DebugConfig) & 16UL;
                                if (u2 != 0UL) {
                                    printf("========== CalcTransition ==========\n");
                                    fflush(stdout);
                                }

                                //  1 -> stdout
                                //  2 -> stderr
                                if (u2 != 0UL) {
                                    printf("=========== status = 6 ==========\n");
                                    fflush(stdout);
                                }

                                //  1 -> stdout
                                //  2 -> stderr
                                if (u2 != 0UL) {
                                    printf("Lines: %d, %d\n\n", CurvStruct1.gcode_source_line,
                                           NextCurv.gcode_source_line);
                                    fflush(stdout);
                                }

                                //      if coder.target('matlab')
                                //
                                //          figure;
                                //          PlotCurvStructsBR(ctx, [CurvStruct1 CurvStruct_T CurvStruct2]); 
                                //          hold on;
                                //          plot3(r0D0(1), r0D0(2), r0D0(3), 'xr', 'LineWidth', 3);
                                //          hold on;
                                //          plot3(r1D0(1), r1D0(2), r1D0(3), 'xr', 'LineWidth', 3);
                                //          title({ctx.cfg.source, 'status_G2_Hermite=6'}, 'Interpreter', 'none'); 
                                //          axis equal;
                                //          camproj('perspective');
                                //
                                //      end
                            } else {
                                unsigned long u1;
                                status = TransitionResult_NoSolution;

                                //  1 -> stdout
                                //  2 -> stderr
                                u1 = static_cast<unsigned long>(DebugConfig) & 32UL;
                                if (u1 != 0UL) {
                                    printf("========== CalcTransition ==========\n");
                                    fflush(stdout);
                                }

                                //  1 -> stdout
                                //  2 -> stderr
                                if (u1 != 0UL) {
                                    printf("=========== No Solution ==========\n");
                                    fflush(stdout);
                                }

                                //  1 -> stdout
                                //  2 -> stderr
                                if (u1 != 0UL) {
                                    printf("Lines: %d, %d\n\n", CurvStruct1.gcode_source_line,
                                           NextCurv.gcode_source_line);
                                    fflush(stdout);
                                }
                            }

                            CurvStruct1_C.gcode_source_line = CurvStruct1.gcode_source_line;
                            CurvStruct_T.gcode_source_line = NextCurv.gcode_source_line;
                            CurvStruct2_C.gcode_source_line = NextCurv.gcode_source_line;
                            CurvStruct1_C.SpindleSpeed = CurvStruct1.SpindleSpeed;
                            CurvStruct_T.SpindleSpeed = std::fmin(CurvStruct1.SpindleSpeed,
                                NextCurv.SpindleSpeed);
                            CurvStruct2_C.SpindleSpeed = NextCurv.SpindleSpeed;
                        }

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
                ctx->q_compress.get((static_cast<double>(1.0)), (&CurvStruct1));
                if (CurvStruct1.zspdmode == ZSpdMode_ZZ) {
                    b_CutZeroStart(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
                                   ctx->cfg.jmax, ctx->cfg.dt, ctx->cfg.ZeroStartAccLimit,
                                   ctx->cfg.ZeroStartJerkLimit, ctx->cfg.ZeroStartVelLimit,
                                   ctx->cfg.DebugCutZero, ctx->cfg.NGridLengthSpline, &CurvStruct1,
                                   &CurvStruct1_C, &CurvStruct2_C);
                    CutZeroEnd(&ctx->q_gcode, &ctx->q_splines, ctx->cfg.NHorz, ctx->cfg.amax,
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
        ::coder::array<double, 2U> a;
        ::coder::array<double, 2U> r;
        ::coder::array<double, 2U> r1Dx;
        ::coder::array<double, 2U> r1Dy;
        ::coder::array<double, 2U> r1Dz;
        ::coder::array<double, 2U> u_mid_tilda;
        ::coder::array<double, 2U> u_tilda;
        ::coder::array<double, 2U> u_vec_tilda;
        ::coder::array<double, 2U> unusedU0;
        ::coder::array<double, 2U> unusedU1;
        ::coder::array<double, 2U> unusedU2;
        ::coder::array<double, 2U> x;
        ::coder::array<double, 2U> z1;
        ::coder::array<bool, 2U> b_expl_temp;
        CurvStruct expl_temp;
        double L;
        int Idx2_size[2];
        int Idx1_data[1];
        int Idx2_data[1];
        int N;
        int b_loop_ub;
        int b_scalarLB;
        int b_vectorUB;
        int c_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int d_k;
        int d_loop_ub;
        int e_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i15;
        int i16;
        int i2;
        int i3;
        int i5;
        int i6;
        int i7;
        int i9;
        int i_loop_ub;
        int j_loop_ub;
        int loop_ub;
        int scalarLB;
        int vectorUB;
        int vlen;

        //  get the sp structure
        ctx_q_splines->get(Curv_sp_index, (&expl_temp));

        //  the ORIGINAL spline is parametrized with u_tilda
        //  after cut-off, new parameter is called u.
        //  u=0 corresponds to the first lift-off point
        //  u=1 corresponds to the second lift-off point
        //  u is NOT used in this function
        b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
        loop_ub = expl_temp.sp.knots.size(1);
        for (int i = 0; i < loop_ub; i++) {
            b_expl_temp[i] = (expl_temp.sp.knots[i] > u0_tilda);
        }

        coder::eml_find(b_expl_temp, Idx2_data, Idx2_size);
        b_loop_ub = Idx2_size[1];
        if (0 <= b_loop_ub - 1) {
            std::memcpy(&Idx1_data[0], &Idx2_data[0], b_loop_ub * sizeof(int));
        }

        b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
        c_loop_ub = expl_temp.sp.knots.size(1);
        for (int i1 = 0; i1 < c_loop_ub; i1++) {
            b_expl_temp[i1] = (expl_temp.sp.knots[i1] < u1_tilda);
        }

        coder::b_eml_find(b_expl_temp, Idx2_data, Idx2_size);
        if (Idx1_data[0] > Idx2_data[0]) {
            i2 = 0;
            i3 = 0;
        } else {
            i2 = Idx1_data[0] - 1;
            i3 = Idx2_data[0];
        }

        d_loop_ub = i3 - i2;
        u_vec_tilda.set_size(1, (d_loop_ub + 2));
        u_vec_tilda[0] = u0_tilda;
        for (int i4 = 0; i4 < d_loop_ub; i4++) {
            u_vec_tilda[i4 + 1] = expl_temp.sp.knots[i2 + i4];
        }

        u_vec_tilda[d_loop_ub + 1] = u1_tilda;
        u_tilda.set_size(1, 0);

        //  N equally spaced u_tilda values between each pair of knots
        //  from u0_tilda until u1_tilda
        i5 = u_vec_tilda.size(1);
        for (int k = 0; k <= i5 - 2; k++) {
            int f_loop_ub;
            int i8;
            i6 = u_tilda.size(1);
            if (u_tilda.size(1) != 0) {
                if (1 > u_tilda.size(1) - 1) {
                    i6 = 0;
                } else {
                    i6 = u_tilda.size(1) - 1;
                }
            }

            coder::linspace(u_vec_tilda[k], u_vec_tilda[k + 1], ctx_cfg_NGridLengthSpline, r);
            i8 = i6;
            f_loop_ub = r.size(1);
            i6 += r.size(1);
            u_tilda.set_size(u_tilda.size(0), i6);
            for (int i10 = 0; i10 < f_loop_ub; i10++) {
                u_tilda[i8 + i10] = r[i10];
            }
        }

        //  midpoint values
        if (1 > u_tilda.size(1) - 1) {
            e_loop_ub = 0;
        } else {
            e_loop_ub = u_tilda.size(1) - 1;
        }

        i7 = (2 <= u_tilda.size(1));
        u_mid_tilda.set_size(1, e_loop_ub);
        scalarLB = e_loop_ub & -2;
        vectorUB = scalarLB - 2;
        for (i9 = 0; i9 <= vectorUB; i9 += 2) {
            __m128d r1;
            __m128d r2;
            r1 = _mm_loadu_pd(&u_tilda[i9]);
            r2 = _mm_loadu_pd(&u_tilda[i7 + i9]);
            _mm_storeu_pd(&u_mid_tilda[i9], _mm_mul_pd(_mm_set1_pd(0.5), _mm_add_pd(r1, r2)));
        }

        for (i9 = scalarLB; i9 < e_loop_ub; i9++) {
            u_mid_tilda[i9] = 0.5 * (u_tilda[i9] + u_tilda[i7 + i9]);
        }

        //  midpoint values
        //  parametric derivative calculation at each midpoint value
        //  with respect to u_tilda
        bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_mid_tilda, unusedU0, r1Dx);
        bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_mid_tilda, unusedU1, r1Dy);
        bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_mid_tilda, unusedU2, r1Dz);

        //  length (between u0_tilda and u1_tilda) calculation by rectangles method
        sqrt_calls++;
        a.set_size(3, r1Dx.size(1));
        g_loop_ub = r1Dx.size(1);
        for (int i11 = 0; i11 < g_loop_ub; i11++) {
            a[3 * i11] = r1Dx[i11];
        }

        h_loop_ub = r1Dy.size(1);
        for (int i12 = 0; i12 < h_loop_ub; i12++) {
            a[3 * i12 + 1] = r1Dy[i12];
        }

        i_loop_ub = r1Dz.size(1);
        for (int i13 = 0; i13 < i_loop_ub; i13++) {
            a[3 * i13 + 2] = r1Dz[i13];
        }

        z1.set_size(3, a.size(1));
        N = a.size(1);
        for (int b_k = 0; b_k < N; b_k++) {
            z1[3 * b_k] = std::pow(a[3 * b_k], 2.0);
            z1[3 * b_k + 1] = std::pow(a[3 * b_k + 1], 2.0);
            z1[3 * b_k + 2] = std::pow(a[3 * b_k + 2], 2.0);
        }

        if (z1.size(1) == 0) {
            x.set_size(1, 0);
        } else {
            int i14;
            x.set_size(1, z1.size(1));
            i14 = z1.size(1);
            for (int c_k = 0; c_k < i14; c_k++) {
                x[c_k] = z1[3 * c_k];
                x[c_k] = x[c_k] + z1[3 * c_k + 1];
                x[c_k] = x[c_k] + z1[3 * c_k + 2];
            }
        }

        i15 = x.size(1);
        b_scalarLB = x.size(1) & -2;
        b_vectorUB = b_scalarLB - 2;
        for (d_k = 0; d_k <= b_vectorUB; d_k += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&x[d_k]);
            _mm_storeu_pd(&x[d_k], _mm_sqrt_pd(r3));
        }

        for (d_k = b_scalarLB; d_k < i15; d_k++) {
            x[d_k] = std::sqrt(x[d_k]);
        }

        coder::diff(u_tilda, r);
        x.set_size(1, x.size(1));
        j_loop_ub = x.size(1);
        c_scalarLB = x.size(1) & -2;
        c_vectorUB = c_scalarLB - 2;
        for (i16 = 0; i16 <= c_vectorUB; i16 += 2) {
            __m128d r4;
            __m128d r5;
            r4 = _mm_loadu_pd(&x[i16]);
            r5 = _mm_loadu_pd(&r[i16]);
            _mm_storeu_pd(&x[i16], _mm_mul_pd(r4, r5));
        }

        for (i16 = c_scalarLB; i16 < j_loop_ub; i16++) {
            x[i16] = x[i16] * r[i16];
        }

        vlen = x.size(1);
        if (x.size(1) == 0) {
            L = 0.0;
        } else {
            double y;
            y = x[0];
            for (int e_k = 2; e_k <= vlen; e_k++) {
                double b_y;
                b_y = y;
                if (vlen >= 2) {
                    b_y = y + x[e_k - 1];
                }

                y = b_y;
            }

            L = y;
        }

        return L;
    }

    //
    // computes approximately the arc length of a parametric spline
    // Arguments    : const queue_coder *ctx_q_splines
    //                double ctx_cfg_NGridLengthSpline
    //                int Curv_sp_index
    //                double u0_tilda
    //                double u1_tilda
    //                double *L
    //                ::coder::array<double, 2U> &Integrand
    //                ::coder::array<double, 2U> &u_mid_tilda
    //                ::coder::array<double, 2U> &du_tilda
    // Return Type  : void
    //
    static void SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, double u0_tilda, double u1_tilda, double *L, ::
        coder::array<double, 2U> &Integrand, ::coder::array<double, 2U> &u_mid_tilda, ::coder::array<
        double, 2U> &du_tilda)
    {
        ::coder::array<double, 2U> a;
        ::coder::array<double, 2U> r;
        ::coder::array<double, 2U> r1Dx;
        ::coder::array<double, 2U> r1Dy;
        ::coder::array<double, 2U> r1Dz;
        ::coder::array<double, 2U> u_tilda;
        ::coder::array<double, 2U> u_vec_tilda;
        ::coder::array<double, 2U> unusedU0;
        ::coder::array<double, 2U> unusedU1;
        ::coder::array<double, 2U> unusedU2;
        ::coder::array<double, 2U> x;
        ::coder::array<double, 2U> z1;
        ::coder::array<bool, 2U> b_expl_temp;
        CurvStruct expl_temp;
        double b_L;
        int Idx2_size[2];
        int Idx1_data[1];
        int Idx2_data[1];
        int N;
        int b_loop_ub;
        int b_scalarLB;
        int b_vectorUB;
        int c_k;
        int c_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int d_loop_ub;
        int e_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i14;
        int i15;
        int i2;
        int i3;
        int i5;
        int i6;
        int i7;
        int i9;
        int i_loop_ub;
        int j_loop_ub;
        int loop_ub;
        int scalarLB;
        int vectorUB;
        int vlen;

        //  get the sp structure
        ctx_q_splines->get(Curv_sp_index, (&expl_temp));

        //  the ORIGINAL spline is parametrized with u_tilda
        //  after cut-off, new parameter is called u.
        //  u=0 corresponds to the first lift-off point
        //  u=1 corresponds to the second lift-off point
        //  u is NOT used in this function
        b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
        loop_ub = expl_temp.sp.knots.size(1);
        for (int i = 0; i < loop_ub; i++) {
            b_expl_temp[i] = (expl_temp.sp.knots[i] > u0_tilda);
        }

        coder::eml_find(b_expl_temp, Idx2_data, Idx2_size);
        b_loop_ub = Idx2_size[1];
        if (0 <= b_loop_ub - 1) {
            std::memcpy(&Idx1_data[0], &Idx2_data[0], b_loop_ub * sizeof(int));
        }

        b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
        c_loop_ub = expl_temp.sp.knots.size(1);
        for (int i1 = 0; i1 < c_loop_ub; i1++) {
            b_expl_temp[i1] = (expl_temp.sp.knots[i1] < u1_tilda);
        }

        coder::b_eml_find(b_expl_temp, Idx2_data, Idx2_size);
        if (Idx1_data[0] > Idx2_data[0]) {
            i2 = 0;
            i3 = 0;
        } else {
            i2 = Idx1_data[0] - 1;
            i3 = Idx2_data[0];
        }

        d_loop_ub = i3 - i2;
        u_vec_tilda.set_size(1, (d_loop_ub + 2));
        u_vec_tilda[0] = u0_tilda;
        for (int i4 = 0; i4 < d_loop_ub; i4++) {
            u_vec_tilda[i4 + 1] = expl_temp.sp.knots[i2 + i4];
        }

        u_vec_tilda[d_loop_ub + 1] = u1_tilda;
        u_tilda.set_size(1, 0);

        //  N equally spaced u_tilda values between each pair of knots
        //  from u0_tilda until u1_tilda
        i5 = u_vec_tilda.size(1);
        for (int k = 0; k <= i5 - 2; k++) {
            int f_loop_ub;
            int i8;
            i6 = u_tilda.size(1);
            if (u_tilda.size(1) != 0) {
                if (1 > u_tilda.size(1) - 1) {
                    i6 = 0;
                } else {
                    i6 = u_tilda.size(1) - 1;
                }
            }

            coder::linspace(u_vec_tilda[k], u_vec_tilda[k + 1], ctx_cfg_NGridLengthSpline, r);
            i8 = i6;
            f_loop_ub = r.size(1);
            i6 += r.size(1);
            u_tilda.set_size(u_tilda.size(0), i6);
            for (int i10 = 0; i10 < f_loop_ub; i10++) {
                u_tilda[i8 + i10] = r[i10];
            }
        }

        //  midpoint values
        if (1 > u_tilda.size(1) - 1) {
            e_loop_ub = 0;
        } else {
            e_loop_ub = u_tilda.size(1) - 1;
        }

        i7 = (2 <= u_tilda.size(1));
        u_mid_tilda.set_size(1, e_loop_ub);
        scalarLB = e_loop_ub & -2;
        vectorUB = scalarLB - 2;
        for (i9 = 0; i9 <= vectorUB; i9 += 2) {
            __m128d r1;
            __m128d r2;
            r1 = _mm_loadu_pd(&u_tilda[i9]);
            r2 = _mm_loadu_pd(&u_tilda[i7 + i9]);
            _mm_storeu_pd(&u_mid_tilda[i9], _mm_mul_pd(_mm_set1_pd(0.5), _mm_add_pd(r1, r2)));
        }

        for (i9 = scalarLB; i9 < e_loop_ub; i9++) {
            u_mid_tilda[i9] = 0.5 * (u_tilda[i9] + u_tilda[i7 + i9]);
        }

        //  midpoint values
        coder::diff(u_tilda, du_tilda);

        //  parametric derivative calculation at each midpoint value
        //  with respect to u_tilda
        bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_mid_tilda, unusedU0, r1Dx);
        bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_mid_tilda, unusedU1, r1Dy);
        bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_mid_tilda, unusedU2, r1Dz);

        //  length (between u0_tilda and u1_tilda) calculation by rectangles method
        a.set_size(3, r1Dx.size(1));
        g_loop_ub = r1Dx.size(1);
        for (int i11 = 0; i11 < g_loop_ub; i11++) {
            a[3 * i11] = r1Dx[i11];
        }

        h_loop_ub = r1Dy.size(1);
        for (int i12 = 0; i12 < h_loop_ub; i12++) {
            a[3 * i12 + 1] = r1Dy[i12];
        }

        i_loop_ub = r1Dz.size(1);
        for (int i13 = 0; i13 < i_loop_ub; i13++) {
            a[3 * i13 + 2] = r1Dz[i13];
        }

        z1.set_size(3, a.size(1));
        N = a.size(1);
        for (int b_k = 0; b_k < N; b_k++) {
            z1[3 * b_k] = std::pow(a[3 * b_k], 2.0);
            z1[3 * b_k + 1] = std::pow(a[3 * b_k + 1], 2.0);
            z1[3 * b_k + 2] = std::pow(a[3 * b_k + 2], 2.0);
        }

        coder::sum(z1, Integrand);
        i14 = Integrand.size(1);
        b_scalarLB = Integrand.size(1) & -2;
        b_vectorUB = b_scalarLB - 2;
        for (c_k = 0; c_k <= b_vectorUB; c_k += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&Integrand[c_k]);
            _mm_storeu_pd(&Integrand[c_k], _mm_sqrt_pd(r3));
        }

        for (c_k = b_scalarLB; c_k < i14; c_k++) {
            Integrand[c_k] = std::sqrt(Integrand[c_k]);
        }

        sqrt_calls++;
        x.set_size(1, Integrand.size(1));
        j_loop_ub = Integrand.size(1);
        c_scalarLB = Integrand.size(1) & -2;
        c_vectorUB = c_scalarLB - 2;
        for (i15 = 0; i15 <= c_vectorUB; i15 += 2) {
            __m128d r4;
            __m128d r5;
            r4 = _mm_loadu_pd(&Integrand[i15]);
            r5 = _mm_loadu_pd(&du_tilda[i15]);
            _mm_storeu_pd(&x[i15], _mm_mul_pd(r4, r5));
        }

        for (i15 = c_scalarLB; i15 < j_loop_ub; i15++) {
            x[i15] = Integrand[i15] * du_tilda[i15];
        }

        vlen = x.size(1);
        if (x.size(1) == 0) {
            b_L = 0.0;
        } else {
            double y;
            y = x[0];
            for (int d_k = 2; d_k <= vlen; d_k++) {
                double b_y;
                b_y = y;
                if (vlen >= 2) {
                    b_y = y + x[d_k - 1];
                }

                y = b_y;
            }

            b_L = y;
        }

        *L = b_L;
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
    static double SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, double u0_tilda, const double u1_tilda_data[],
        const int u1_tilda_size[2])
    {
        ::coder::array<double, 2U> a;
        ::coder::array<double, 2U> r;
        ::coder::array<double, 2U> r1Dx;
        ::coder::array<double, 2U> r1Dy;
        ::coder::array<double, 2U> r1Dz;
        ::coder::array<double, 2U> u_mid_tilda;
        ::coder::array<double, 2U> u_tilda;
        ::coder::array<double, 2U> unusedU0;
        ::coder::array<double, 2U> unusedU1;
        ::coder::array<double, 2U> unusedU2;
        ::coder::array<double, 2U> x;
        ::coder::array<double, 2U> z1;
        ::coder::array<bool, 2U> b_expl_temp;
        CurvStruct expl_temp;
        double u_vec_tilda_data[3];
        double L;
        int Idx1_size[2];
        int Idx1_data[1];
        int N;
        int b_loop_ub;
        int b_scalarLB;
        int b_vectorUB;
        int c_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int d_k;
        int d_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i1;
        int i14;
        int i15;
        int i2;
        int i5;
        int i6;
        int i8;
        int i_loop_ub;
        int loop_ub;
        int scalarLB;
        int u_vec_tilda_size_idx_1;
        int vectorUB;
        int vlen;

        //  get the sp structure
        ctx_q_splines->get(Curv_sp_index, (&expl_temp));

        //  the ORIGINAL spline is parametrized with u_tilda
        //  after cut-off, new parameter is called u.
        //  u=0 corresponds to the first lift-off point
        //  u=1 corresponds to the second lift-off point
        //  u is NOT used in this function
        b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
        loop_ub = expl_temp.sp.knots.size(1);
        for (int i = 0; i < loop_ub; i++) {
            b_expl_temp[i] = (expl_temp.sp.knots[i] > u0_tilda);
        }

        coder::eml_find(b_expl_temp, Idx1_data, Idx1_size);
        if (Idx1_data[0] > 1) {
            i1 = -2;
            i2 = -1;
        } else {
            i1 = Idx1_data[0] - 3;
            i2 = 0;
        }

        b_loop_ub = i2 - i1;
        u_vec_tilda_size_idx_1 = b_loop_ub + u1_tilda_size[1];
        u_vec_tilda_data[0] = u0_tilda;
        for (int i3 = 0; i3 <= b_loop_ub - 2; i3++) {
            u_vec_tilda_data[i3 + 1] = expl_temp.sp.knots[(i1 + i3) + 2];
        }

        c_loop_ub = u1_tilda_size[1];
        for (int i4 = 0; i4 < c_loop_ub; i4++) {
            u_vec_tilda_data[(i4 + i2) - i1] = u1_tilda_data[i4];
        }

        u_tilda.set_size(1, 0);

        //  N equally spaced u_tilda values between each pair of knots
        //  from u0_tilda until u1_tilda
        for (int k = 0; k <= u_vec_tilda_size_idx_1 - 2; k++) {
            int e_loop_ub;
            int i7;
            i5 = u_tilda.size(1);
            if (u_tilda.size(1) != 0) {
                if (1 > u_tilda.size(1) - 1) {
                    i5 = 0;
                } else {
                    i5 = u_tilda.size(1) - 1;
                }
            }

            coder::linspace(u_vec_tilda_data[k], u_vec_tilda_data[k + 1], ctx_cfg_NGridLengthSpline,
                            r);
            i7 = i5;
            e_loop_ub = r.size(1);
            i5 += r.size(1);
            u_tilda.set_size(u_tilda.size(0), i5);
            for (int i9 = 0; i9 < e_loop_ub; i9++) {
                u_tilda[i7 + i9] = r[i9];
            }
        }

        //  midpoint values
        if (1 > u_tilda.size(1) - 1) {
            d_loop_ub = 0;
        } else {
            d_loop_ub = u_tilda.size(1) - 1;
        }

        i6 = (2 <= u_tilda.size(1));
        u_mid_tilda.set_size(1, d_loop_ub);
        scalarLB = d_loop_ub & -2;
        vectorUB = scalarLB - 2;
        for (i8 = 0; i8 <= vectorUB; i8 += 2) {
            __m128d r1;
            __m128d r2;
            r1 = _mm_loadu_pd(&u_tilda[i8]);
            r2 = _mm_loadu_pd(&u_tilda[i6 + i8]);
            _mm_storeu_pd(&u_mid_tilda[i8], _mm_mul_pd(_mm_set1_pd(0.5), _mm_add_pd(r1, r2)));
        }

        for (i8 = scalarLB; i8 < d_loop_ub; i8++) {
            u_mid_tilda[i8] = 0.5 * (u_tilda[i8] + u_tilda[i6 + i8]);
        }

        //  midpoint values
        //  parametric derivative calculation at each midpoint value
        //  with respect to u_tilda
        bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_mid_tilda, unusedU0, r1Dx);
        bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_mid_tilda, unusedU1, r1Dy);
        bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_mid_tilda, unusedU2, r1Dz);

        //  length (between u0_tilda and u1_tilda) calculation by rectangles method
        sqrt_calls++;
        a.set_size(3, r1Dx.size(1));
        f_loop_ub = r1Dx.size(1);
        for (int i10 = 0; i10 < f_loop_ub; i10++) {
            a[3 * i10] = r1Dx[i10];
        }

        g_loop_ub = r1Dy.size(1);
        for (int i11 = 0; i11 < g_loop_ub; i11++) {
            a[3 * i11 + 1] = r1Dy[i11];
        }

        h_loop_ub = r1Dz.size(1);
        for (int i12 = 0; i12 < h_loop_ub; i12++) {
            a[3 * i12 + 2] = r1Dz[i12];
        }

        z1.set_size(3, a.size(1));
        N = a.size(1);
        for (int b_k = 0; b_k < N; b_k++) {
            z1[3 * b_k] = std::pow(a[3 * b_k], 2.0);
            z1[3 * b_k + 1] = std::pow(a[3 * b_k + 1], 2.0);
            z1[3 * b_k + 2] = std::pow(a[3 * b_k + 2], 2.0);
        }

        if (z1.size(1) == 0) {
            x.set_size(1, 0);
        } else {
            int i13;
            x.set_size(1, z1.size(1));
            i13 = z1.size(1);
            for (int c_k = 0; c_k < i13; c_k++) {
                x[c_k] = z1[3 * c_k];
                x[c_k] = x[c_k] + z1[3 * c_k + 1];
                x[c_k] = x[c_k] + z1[3 * c_k + 2];
            }
        }

        i14 = x.size(1);
        b_scalarLB = x.size(1) & -2;
        b_vectorUB = b_scalarLB - 2;
        for (d_k = 0; d_k <= b_vectorUB; d_k += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&x[d_k]);
            _mm_storeu_pd(&x[d_k], _mm_sqrt_pd(r3));
        }

        for (d_k = b_scalarLB; d_k < i14; d_k++) {
            x[d_k] = std::sqrt(x[d_k]);
        }

        coder::diff(u_tilda, r);
        x.set_size(1, x.size(1));
        i_loop_ub = x.size(1);
        c_scalarLB = x.size(1) & -2;
        c_vectorUB = c_scalarLB - 2;
        for (i15 = 0; i15 <= c_vectorUB; i15 += 2) {
            __m128d r4;
            __m128d r5;
            r4 = _mm_loadu_pd(&x[i15]);
            r5 = _mm_loadu_pd(&r[i15]);
            _mm_storeu_pd(&x[i15], _mm_mul_pd(r4, r5));
        }

        for (i15 = c_scalarLB; i15 < i_loop_ub; i15++) {
            x[i15] = x[i15] * r[i15];
        }

        vlen = x.size(1);
        if (x.size(1) == 0) {
            L = 0.0;
        } else {
            double y;
            y = x[0];
            for (int e_k = 2; e_k <= vlen; e_k++) {
                double b_y;
                b_y = y;
                if (vlen >= 2) {
                    b_y = y + x[e_k - 1];
                }

                y = b_y;
            }

            L = y;
        }

        return L;
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
    static double SplineLengthApprox(const queue_coder *ctx_q_splines, double
        ctx_cfg_NGridLengthSpline, int Curv_sp_index, const double u0_tilda_data[], const int
        u0_tilda_size[2], double u1_tilda)
    {
        ::coder::array<double, 2U> a;
        ::coder::array<double, 2U> r;
        ::coder::array<double, 2U> r1Dx;
        ::coder::array<double, 2U> r1Dy;
        ::coder::array<double, 2U> r1Dz;
        ::coder::array<double, 2U> u_mid_tilda;
        ::coder::array<double, 2U> u_tilda;
        ::coder::array<double, 2U> u_vec_tilda;
        ::coder::array<double, 2U> unusedU0;
        ::coder::array<double, 2U> unusedU1;
        ::coder::array<double, 2U> unusedU2;
        ::coder::array<double, 2U> x;
        ::coder::array<double, 2U> z1;
        ::coder::array<bool, 2U> b_expl_temp;
        CurvStruct expl_temp;
        double L;
        int tmp_size[2];
        int tmp_data[1];
        int N;
        int b_loop_ub;
        int b_scalarLB;
        int b_vectorUB;
        int c_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int d_k;
        int d_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i13;
        int i14;
        int i3;
        int i4;
        int i5;
        int i7;
        int i_loop_ub;
        int loop_ub;
        int scalarLB;
        int vectorUB;
        int vlen;

        //  get the sp structure
        ctx_q_splines->get(Curv_sp_index, (&expl_temp));

        //  the ORIGINAL spline is parametrized with u_tilda
        //  after cut-off, new parameter is called u.
        //  u=0 corresponds to the first lift-off point
        //  u=1 corresponds to the second lift-off point
        //  u is NOT used in this function
        b_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
        loop_ub = expl_temp.sp.knots.size(1);
        for (int i = 0; i < loop_ub; i++) {
            b_expl_temp[i] = (expl_temp.sp.knots[i] < u1_tilda);
        }

        coder::b_eml_find(b_expl_temp, tmp_data, tmp_size);
        b_loop_ub = tmp_data[0];
        u_vec_tilda.set_size(1, ((u0_tilda_size[1] + tmp_data[0]) + 1));
        c_loop_ub = u0_tilda_size[1];
        for (int i1 = 0; i1 < c_loop_ub; i1++) {
            u_vec_tilda[i1] = u0_tilda_data[i1];
        }

        for (int i2 = 0; i2 < b_loop_ub; i2++) {
            u_vec_tilda[i2 + u0_tilda_size[1]] = expl_temp.sp.knots[i2];
        }

        u_vec_tilda[u0_tilda_size[1] + tmp_data[0]] = u1_tilda;
        u_tilda.set_size(1, 0);

        //  N equally spaced u_tilda values between each pair of knots
        //  from u0_tilda until u1_tilda
        i3 = u_vec_tilda.size(1);
        for (int k = 0; k <= i3 - 2; k++) {
            int e_loop_ub;
            int i6;
            i4 = u_tilda.size(1);
            if (u_tilda.size(1) != 0) {
                if (1 > u_tilda.size(1) - 1) {
                    i4 = 0;
                } else {
                    i4 = u_tilda.size(1) - 1;
                }
            }

            coder::linspace(u_vec_tilda[k], u_vec_tilda[k + 1], ctx_cfg_NGridLengthSpline, r);
            i6 = i4;
            e_loop_ub = r.size(1);
            i4 += r.size(1);
            u_tilda.set_size(u_tilda.size(0), i4);
            for (int i8 = 0; i8 < e_loop_ub; i8++) {
                u_tilda[i6 + i8] = r[i8];
            }
        }

        //  midpoint values
        if (1 > u_tilda.size(1) - 1) {
            d_loop_ub = 0;
        } else {
            d_loop_ub = u_tilda.size(1) - 1;
        }

        i5 = (2 <= u_tilda.size(1));
        u_mid_tilda.set_size(1, d_loop_ub);
        scalarLB = d_loop_ub & -2;
        vectorUB = scalarLB - 2;
        for (i7 = 0; i7 <= vectorUB; i7 += 2) {
            __m128d r1;
            __m128d r2;
            r1 = _mm_loadu_pd(&u_tilda[i7]);
            r2 = _mm_loadu_pd(&u_tilda[i5 + i7]);
            _mm_storeu_pd(&u_mid_tilda[i7], _mm_mul_pd(_mm_set1_pd(0.5), _mm_add_pd(r1, r2)));
        }

        for (i7 = scalarLB; i7 < d_loop_ub; i7++) {
            u_mid_tilda[i7] = 0.5 * (u_tilda[i7] + u_tilda[i5 + i7]);
        }

        //  midpoint values
        //  parametric derivative calculation at each midpoint value
        //  with respect to u_tilda
        bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_mid_tilda, unusedU0, r1Dx);
        bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_mid_tilda, unusedU1, r1Dy);
        bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_mid_tilda, unusedU2, r1Dz);

        //  length (between u0_tilda and u1_tilda) calculation by rectangles method
        sqrt_calls++;
        a.set_size(3, r1Dx.size(1));
        f_loop_ub = r1Dx.size(1);
        for (int i9 = 0; i9 < f_loop_ub; i9++) {
            a[3 * i9] = r1Dx[i9];
        }

        g_loop_ub = r1Dy.size(1);
        for (int i10 = 0; i10 < g_loop_ub; i10++) {
            a[3 * i10 + 1] = r1Dy[i10];
        }

        h_loop_ub = r1Dz.size(1);
        for (int i11 = 0; i11 < h_loop_ub; i11++) {
            a[3 * i11 + 2] = r1Dz[i11];
        }

        z1.set_size(3, a.size(1));
        N = a.size(1);
        for (int b_k = 0; b_k < N; b_k++) {
            z1[3 * b_k] = std::pow(a[3 * b_k], 2.0);
            z1[3 * b_k + 1] = std::pow(a[3 * b_k + 1], 2.0);
            z1[3 * b_k + 2] = std::pow(a[3 * b_k + 2], 2.0);
        }

        if (z1.size(1) == 0) {
            x.set_size(1, 0);
        } else {
            int i12;
            x.set_size(1, z1.size(1));
            i12 = z1.size(1);
            for (int c_k = 0; c_k < i12; c_k++) {
                x[c_k] = z1[3 * c_k];
                x[c_k] = x[c_k] + z1[3 * c_k + 1];
                x[c_k] = x[c_k] + z1[3 * c_k + 2];
            }
        }

        i13 = x.size(1);
        b_scalarLB = x.size(1) & -2;
        b_vectorUB = b_scalarLB - 2;
        for (d_k = 0; d_k <= b_vectorUB; d_k += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&x[d_k]);
            _mm_storeu_pd(&x[d_k], _mm_sqrt_pd(r3));
        }

        for (d_k = b_scalarLB; d_k < i13; d_k++) {
            x[d_k] = std::sqrt(x[d_k]);
        }

        coder::diff(u_tilda, r);
        x.set_size(1, x.size(1));
        i_loop_ub = x.size(1);
        c_scalarLB = x.size(1) & -2;
        c_vectorUB = c_scalarLB - 2;
        for (i14 = 0; i14 <= c_vectorUB; i14 += 2) {
            __m128d r4;
            __m128d r5;
            r4 = _mm_loadu_pd(&x[i14]);
            r5 = _mm_loadu_pd(&r[i14]);
            _mm_storeu_pd(&x[i14], _mm_mul_pd(r4, r5));
        }

        for (i14 = c_scalarLB; i14 < i_loop_ub; i14++) {
            x[i14] = x[i14] * r[i14];
        }

        vlen = x.size(1);
        if (x.size(1) == 0) {
            L = 0.0;
        } else {
            double y;
            y = x[0];
            for (int e_k = 2; e_k <= vlen; e_k++) {
                double b_y;
                b_y = y;
                if (vlen >= 2) {
                    b_y = y + x[e_k - 1];
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
        ::coder::array<double, 2U> knots;
        ::coder::array<bool, 2U> b_expl_temp;
        CurvStruct CurvStrct;
        CurvStruct expl_temp;
        double b_L;
        int Idx2_size[2];
        int Idx1_data[1];
        int Idx2_data[1];
        if (!ctx->q_smooth.isempty()) {
            unsigned int N;
            int i;
            N = ctx->q_smooth.size();

            //  1 -> stdout
            //  2 -> stderr
            if ((static_cast<unsigned long>(DebugConfig) & 1UL) != 0UL) {
                printf("Splitting...\n");
                fflush(stdout);
            }

            i = static_cast<int>(N);
            for (int k = 0; k < i; k++) {
                ctx->q_smooth.get((k + 1U), (&CurvStrct));

                //  coder.varsize('CrvStructs', [1, 100], [0, 1]);
                //
                if ((CurvStrct.Type != CurveType_TransP5) && (!CurvStrct.UseConstJerk)) {
                    if ((CurvStrct.Type == CurveType_Line) || (CurvStrct.Type == CurveType_Helix)) {
                        double L;
                        double a;
                        double b;
                        a = CurvStrct.a_param;
                        b = CurvStrct.b_param;
                        L = LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStrct.Type,
                                       CurvStrct.P0, CurvStrct.P1, CurvStrct.HelixCenter,
                                       CurvStrct.evec, CurvStrct.theta, CurvStrct.pitch,
                                       CurvStrct.CoeffP5, CurvStrct.sp_index, CurvStrct.a_param,
                                       CurvStrct.b_param);
                        if (L < 2.0 * ctx->cfg.LSplit) {
                            ctx->q_split.push((&CurvStrct));
                        } else {
                            double L_split;
                            double b_N;
                            int i3;
                            b_N = std::ceil(L / ctx->cfg.LSplit);
                            L_split = L / b_N;
                            i3 = static_cast<int>(b_N);
                            for (int b_k = 0; b_k < i3; b_k++) {
                                double u_tilda_0;
                                double u_tilda_0_tmp;
                                u_tilda_0_tmp = L_split / L;
                                u_tilda_0 = a * (((static_cast<double>(b_k) + 1.0) - 1.0) *
                                                 u_tilda_0_tmp) + b;
                                CurvStrct.a_param = (a * ((static_cast<double>(b_k) + 1.0) *
                                                      u_tilda_0_tmp) + b) - u_tilda_0;
                                CurvStrct.b_param = u_tilda_0;
                                ctx->q_split.push((&CurvStrct));
                            }
                        }
                    } else {
                        double u1_tilda;
                        int b_loop_ub;
                        int c_k;
                        int c_loop_ub;
                        int i1;
                        int i2;
                        int i6;
                        int i7;
                        int loop_ub;
                        ctx->q_splines.get(CurvStrct.sp_index, (&expl_temp));
                        u1_tilda = CurvStrct.a_param + CurvStrct.b_param;
                        if (4 > expl_temp.sp.knots.size(1) - 3) {
                            i1 = 0;
                            i2 = -1;
                        } else {
                            i1 = 3;
                            i2 = expl_temp.sp.knots.size(1) - 4;
                        }

                        loop_ub = i2 - i1;
                        b_expl_temp.set_size(1, (loop_ub + 1));
                        for (int i4 = 0; i4 <= loop_ub; i4++) {
                            b_expl_temp[i4] = (expl_temp.sp.knots[i1 + i4] > CurvStrct.b_param);
                        }

                        coder::eml_find(b_expl_temp, Idx2_data, Idx2_size);
                        b_loop_ub = Idx2_size[1];
                        if (0 <= b_loop_ub - 1) {
                            std::memcpy(&Idx1_data[0], &Idx2_data[0], b_loop_ub * sizeof(int));
                        }

                        b_expl_temp.set_size(1, ((i2 - i1) + 1));
                        for (int i5 = 0; i5 <= loop_ub; i5++) {
                            b_expl_temp[i5] = (expl_temp.sp.knots[i1 + i5] < u1_tilda);
                        }

                        coder::b_eml_find(b_expl_temp, Idx2_data, Idx2_size);
                        if (Idx1_data[0] > Idx2_data[0]) {
                            i6 = 0;
                            i7 = 0;
                        } else {
                            i6 = Idx1_data[0] - 1;
                            i7 = Idx2_data[0];
                        }

                        c_loop_ub = i7 - i6;
                        knots.set_size(1, (c_loop_ub + 2));
                        knots[0] = CurvStrct.b_param;
                        for (int i8 = 0; i8 < c_loop_ub; i8++) {
                            knots[i8 + 1] = expl_temp.sp.knots[(i1 + i6) + i8];
                        }

                        knots[c_loop_ub + 1] = u1_tilda;
                        b_L = 0.0;
                        c_k = 0;
                        while (c_k + 1 < knots.size(1)) {
                            int b_i;
                            b_i = c_k;
                            while ((b_L < ctx->cfg.LSplit) && (c_k + 1 < knots.size(1))) {
                                double delta_L;
                                delta_L = SplineLengthApprox(&ctx->q_splines,
                                    ctx->cfg.NGridLengthSpline, CurvStrct.sp_index, knots[c_k],
                                    knots[c_k + 1]);
                                b_L += delta_L;
                                c_k++;
                            }

                            CurvStrct.a_param = knots[c_k] - knots[b_i];
                            CurvStrct.b_param = knots[b_i];
                            ctx->q_split.push((&CurvStrct));
                            b_L = 0.0;
                        }
                    }
                } else {
                    ctx->q_split.push((&CurvStrct));
                }
            }
        }
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
        ::coder::array<double, 2U> Integrand;
        ::coder::array<double, 2U> du_tilda;
        ::coder::array<double, 2U> u_mid_tilda;
        CurvStruct b_ctx_q_splines;
        double r1D0[3];
        double r1D1[3];
        double unusedU0[3];
        double unusedU1[3];
        double L;
        double L_tot;
        double u0_tilda;
        double u1_tilda;
        if (b_CurvStruct->Type == CurveType_Spline) {
            ctx_q_splines->get(b_CurvStruct->sp_index, (&b_ctx_q_splines));

            //  discretizing along the total spline
            //  from u=0 to u=1
            SplineLengthApprox(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct->sp_index,
                               b_CurvStruct->b_param, b_CurvStruct->a_param + b_CurvStruct->b_param,
                               &L_tot, Integrand, u_mid_tilda, du_tilda);
            if (d0 != 0.0) {
                unsigned int k;

                //  spline-long length calculation by rectangles method
                //  beginning from u=0
                //  until d0 is reached
                L = 0.0;
                k = 1U;
                while ((L < d0) && (k <= static_cast<unsigned int>(du_tilda.size(1)))) {
                    L += Integrand[static_cast<int>(k) - 1] * du_tilda[static_cast<int>(k) - 1];
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
            b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                             b_CurvStruct->HelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                             b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                             b_CurvStruct->a_param, b_CurvStruct->b_param, unusedU0, r1D0);
            c_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                             b_CurvStruct->HelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                             b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                             b_CurvStruct->a_param, b_CurvStruct->b_param, unusedU1, r1D1);

            //  d0 = Integral_0_u0 ||r'(u)||du
            //  d1 = Integral_u1_1 ||r'(u)||du
            sqrt_calls++;
            sqrt_calls++;

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
        ::coder::array<double, 2U> a;
        ::coder::array<double, 2U> at;
        ::coder::array<double, 2U> b_a;
        ::coder::array<double, 2U> b_d1uk;
        ::coder::array<double, 2U> b_r1D;
        ::coder::array<double, 2U> b_uk;
        ::coder::array<double, 2U> b_x;
        ::coder::array<double, 2U> b_z1;
        ::coder::array<double, 2U> c;
        ::coder::array<double, 2U> d1uk;
        ::coder::array<double, 2U> d2uk;
        ::coder::array<double, 2U> jt;
        ::coder::array<double, 2U> r2D;
        ::coder::array<double, 2U> r3;
        ::coder::array<double, 2U> r3D;
        ::coder::array<double, 2U> r7;
        ::coder::array<double, 2U> t;
        ::coder::array<double, 2U> uk;
        ::coder::array<double, 2U> unusedU1;
        ::coder::array<double, 2U> x;
        ::coder::array<double, 2U> z1;
        ::coder::array<double, 1U> max_at;
        ::coder::array<double, 1U> max_jt;
        ::coder::array<double, 1U> norm_vt;
        ::coder::array<bool, 2U> b_max_at;
        ::coder::array<bool, 2U> b_max_jt;
        ::coder::array<bool, 2U> b_norm_vt;
        CurvStruct expl_temp;
        double r1D[3];
        double unusedU0[3];
        double L;
        double b_ex;
        double b_vmax;
        double ex;
        double ex_tmp;
        double jps;
        double tmax;
        double z1_idx_1;
        double z1_idx_2;
        long c_N;
        long c_k;
        long y;
        int x_data[3];
        int cut_index_vel_size[2];
        int cut_index_acc_data[1];
        int cut_index_jerk_data[1];
        int cut_index_vel_data[1];
        int N;
        int b_N;
        int b_loop_ub;
        int b_m;
        int b_scalarLB;
        int b_vectorUB;
        int c_ex;
        int c_loop_ub;
        int c_scalarLB;
        int c_vectorUB;
        int cut_index;
        int cut_index_acc_size_idx_1;
        int cut_index_jerk_size_idx_1;
        int d_N;
        int d_loop_ub;
        int d_scalarLB;
        int d_vectorUB;
        int e_N;
        int e_loop_ub;
        int e_scalarLB;
        int e_vectorUB;
        int f_N;
        int f_loop_ub;
        int f_scalarLB;
        int f_vectorUB;
        int g_loop_ub;
        int i1;
        int i19;
        int i2;
        int i20;
        int i3;
        int i6;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        int m;
        int m_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        int p_k;
        int p_loop_ub;
        int q_loop_ub;
        int scalarLB;
        int u0;
        int u1;
        int vectorUB;
        bool exitg1;
        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->HelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                         b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                         b_CurvStruct->a_param, b_CurvStruct->b_param, unusedU0, r1D);
        z1_idx_1 = std::abs(r1D[1]);
        z1_idx_2 = std::abs(r1D[2]);
        ex = ctx_cfg_jmax[0];
        ex_tmp = std::abs(r1D[0]);
        b_ex = ex_tmp;
        if (ctx_cfg_jmax[0] > ctx_cfg_jmax[1]) {
            ex = ctx_cfg_jmax[1];
        }

        if (ex_tmp < z1_idx_1) {
            b_ex = z1_idx_1;
        }

        if (ex > ctx_cfg_jmax[2]) {
            ex = ctx_cfg_jmax[2];
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
            coder::eml_float_colon(ctx_cfg_dt, tmax, t);
        }

        z1.set_size(1, t.size(1));
        N = t.size(1);
        for (int k = 0; k < N; k++) {
            z1[k] = std::pow(t[k], 3.0);
        }

        uk.set_size(1, z1.size(1));
        b_loop_ub = z1.size(1);
        scalarLB = z1.size(1) & -2;
        vectorUB = scalarLB - 2;
        for (i1 = 0; i1 <= vectorUB; i1 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&z1[i1]);
            _mm_storeu_pd(&uk[i1], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r), _mm_set1_pd(6.0)));
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
        b_scalarLB = z1.size(1) & -2;
        b_vectorUB = b_scalarLB - 2;
        for (i2 = 0; i2 <= b_vectorUB; i2 += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&z1[i2]);
            _mm_storeu_pd(&d1uk[i2], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(jps), r1), _mm_set1_pd(2.0)));
        }

        for (i2 = b_scalarLB; i2 < c_loop_ub; i2++) {
            d1uk[i2] = jps * z1[i2] / 2.0;
        }

        d2uk.set_size(1, t.size(1));
        d_loop_ub = t.size(1);
        c_scalarLB = t.size(1) & -2;
        c_vectorUB = c_scalarLB - 2;
        for (i3 = 0; i3 <= c_vectorUB; i3 += 2) {
            __m128d r2;
            r2 = _mm_loadu_pd(&t[i3]);
            _mm_storeu_pd(&d2uk[i3], _mm_mul_pd(_mm_set1_pd(jps), r2));
        }

        for (i3 = c_scalarLB; i3 < d_loop_ub; i3++) {
            d2uk[i3] = jps * t[i3];
        }

        b_uk.set_size(1, uk.size(1));
        e_loop_ub = uk.size(1) - 1;
        for (int i4 = 0; i4 <= e_loop_ub; i4++) {
            b_uk[i4] = uk[i4];
        }

        b_EvalCurvStruct(ctx_q_splines, b_CurvStruct->Type, b_CurvStruct->P0, b_CurvStruct->P1,
                         b_CurvStruct->HelixCenter, b_CurvStruct->evec, b_CurvStruct->theta,
                         b_CurvStruct->pitch, b_CurvStruct->CoeffP5, b_CurvStruct->sp_index,
                         b_CurvStruct->a_param, b_CurvStruct->b_param, b_uk, unusedU1, b_r1D, r2D,
                         r3D);
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
            double b_y;
            ctx_q_gcode->get(c_k, (&expl_temp));
            b_y = GetCurvMaxFeedrate(ctx_q_splines, ctx_cfg_amax, ctx_cfg_jmax, expl_temp.Type,
                expl_temp.P0, expl_temp.P1, expl_temp.HelixCenter, expl_temp.evec, expl_temp.theta,
                expl_temp.pitch, expl_temp.CoeffP5, expl_temp.sp_index, expl_temp.FeedRate,
                expl_temp.a_param, expl_temp.b_param);
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
                __m128d r4;
                int varargin_2;
                varargin_2 = acoef * e_k;
                r4 = _mm_loadu_pd(&b_r1D[3 * varargin_2]);
                _mm_storeu_pd(&c[3 * e_k], _mm_mul_pd(r4, _mm_set1_pd(jps)));
                c[3 * e_k + 2] = b_r1D[3 * varargin_2 + 2] * jps;
            }
        }

        coder::bsxfun(r3D, z1, r3);
        b_d1uk.set_size(1, d1uk.size(1));
        f_loop_ub = d1uk.size(1);
        d_scalarLB = d1uk.size(1) & -2;
        d_vectorUB = d_scalarLB - 2;
        for (i6 = 0; i6 <= d_vectorUB; i6 += 2) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&d1uk[i6]);
            r6 = _mm_loadu_pd(&d2uk[i6]);
            _mm_storeu_pd(&b_d1uk[i6], _mm_mul_pd(r5, r6));
        }

        for (i6 = d_scalarLB; i6 < f_loop_ub; i6++) {
            b_d1uk[i6] = d1uk[i6] * d2uk[i6];
        }

        coder::bsxfun(r2D, b_d1uk, r7);
        a.set_size(r3.size(1), 3);
        g_loop_ub = r3.size(1);
        for (int i7 = 0; i7 < 3; i7++) {
            for (int i8 = 0; i8 < g_loop_ub; i8++) {
                a[i8 + a.size(0) * i7] = (r3[i7 + 3 * i8] + 3.0 * r7[i7 + 3 * i8]) + c[i7 + 3 * i8];
            }
        }

        x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int b_acoef;
            b_acoef = (a.size(0) != 1);
            for (int f_k = 0; f_k < 3; f_k++) {
                int i9;
                i9 = x.size(0) - 1;
                for (int g_k = 0; g_k <= i9; g_k++) {
                    x[g_k + x.size(0) * f_k] = a[b_acoef * g_k + a.size(0) * f_k] / ctx_cfg_jmax[f_k];
                }
            }
        }

        jt.set_size(x.size(0), 3);
        if (x.size(0) != 0) {
            int h_loop_ub;
            int i_loop_ub;
            at.set_size(x.size(0), 3);
            h_loop_ub = x.size(0);
            for (int i10 = 0; i10 < 3; i10++) {
                for (int i11 = 0; i11 < h_loop_ub; i11++) {
                    at[i11 + at.size(0) * i10] = jt[i11 + jt.size(0) * i10];
                }
            }

            for (int i_k = 0; i_k < 3; i_k++) {
                int i12;
                i12 = at.size(0);
                for (int j_k = 0; j_k < i12; j_k++) {
                    at[j_k + at.size(0) * i_k] = std::abs(x[j_k + x.size(0) * i_k]);
                }
            }

            jt.set_size(at.size(0), 3);
            i_loop_ub = at.size(0);
            for (int i13 = 0; i13 < 3; i13++) {
                for (int i15 = 0; i15 < i_loop_ub; i15++) {
                    jt[i15 + jt.size(0) * i13] = at[i15 + at.size(0) * i13];
                }
            }
        }

        z1.set_size(1, d1uk.size(1));
        e_N = d1uk.size(1);
        for (int h_k = 0; h_k < e_N; h_k++) {
            z1[h_k] = std::pow(d1uk[h_k], 2.0);
        }

        coder::bsxfun(r2D, z1, r3);
        coder::bsxfun(b_r1D, d2uk, r7);
        a.set_size(r3.size(1), 3);
        j_loop_ub = r3.size(1);
        for (int i14 = 0; i14 < 3; i14++) {
            for (int i16 = 0; i16 < j_loop_ub; i16++) {
                a[i16 + a.size(0) * i14] = r3[i14 + 3 * i16] + r7[i14 + 3 * i16];
            }
        }

        x.set_size(a.size(0), 3);
        if (a.size(0) != 0) {
            int c_acoef;
            c_acoef = (a.size(0) != 1);
            for (int k_k = 0; k_k < 3; k_k++) {
                int i17;
                i17 = x.size(0) - 1;
                for (int m_k = 0; m_k <= i17; m_k++) {
                    x[m_k + x.size(0) * k_k] = a[c_acoef * m_k + a.size(0) * k_k] / ctx_cfg_amax[k_k];
                }
            }
        }

        at.set_size(x.size(0), 3);
        if (x.size(0) != 0) {
            for (int l_k = 0; l_k < 3; l_k++) {
                int i18;
                i18 = at.size(0);
                for (int n_k = 0; n_k < i18; n_k++) {
                    at[n_k + at.size(0) * l_k] = std::abs(x[n_k + x.size(0) * l_k]);
                }
            }
        }

        sqrt_calls++;
        coder::bsxfun(b_r1D, d1uk, b_a);
        b_z1.set_size(3, b_a.size(1));
        f_N = b_a.size(1);
        for (int o_k = 0; o_k < f_N; o_k++) {
            b_z1[3 * o_k] = std::pow(b_a[3 * o_k], 2.0);
            b_z1[3 * o_k + 1] = std::pow(b_a[3 * o_k + 1], 2.0);
            b_z1[3 * o_k + 2] = std::pow(b_a[3 * o_k + 2], 2.0);
        }

        coder::sum(b_z1, b_x);
        i19 = b_x.size(1);
        e_scalarLB = b_x.size(1) & -2;
        e_vectorUB = e_scalarLB - 2;
        for (p_k = 0; p_k <= e_vectorUB; p_k += 2) {
            __m128d r8;
            r8 = _mm_loadu_pd(&b_x[p_k]);
            _mm_storeu_pd(&b_x[p_k], _mm_sqrt_pd(r8));
        }

        for (p_k = e_scalarLB; p_k < i19; p_k++) {
            b_x[p_k] = std::sqrt(b_x[p_k]);
        }

        norm_vt.set_size(b_x.size(1));
        k_loop_ub = b_x.size(1);
        f_scalarLB = b_x.size(1) & -2;
        f_vectorUB = f_scalarLB - 2;
        for (i20 = 0; i20 <= f_vectorUB; i20 += 2) {
            __m128d r9;
            r9 = _mm_loadu_pd(&b_x[i20]);
            _mm_storeu_pd(&norm_vt[i20], _mm_div_pd(r9, _mm_set1_pd(b_vmax)));
        }

        for (i20 = f_scalarLB; i20 < k_loop_ub; i20++) {
            norm_vt[i20] = b_x[i20] / b_vmax;
        }

        m = jt.size(0) - 1;
        max_jt.set_size(jt.size(0));
        if (jt.size(0) >= 1) {
            double d;
            int c_i;
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
            double d1;
            int e_i;
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
        l_loop_ub = max_jt.size(0);
        for (int i21 = 0; i21 < l_loop_ub; i21++) {
            b_max_jt[i21] = (max_jt[i21] > ctx_cfg_ZeroStartJerkLimit);
        }

        coder::eml_find(b_max_jt, cut_index_vel_data, cut_index_vel_size);
        cut_index_jerk_size_idx_1 = cut_index_vel_size[1];
        m_loop_ub = cut_index_vel_size[1];
        if (0 <= m_loop_ub - 1) {
            std::memcpy(&cut_index_jerk_data[0], &cut_index_vel_data[0], m_loop_ub * sizeof(int));
        }

        if (cut_index_vel_size[1] == 0) {
            cut_index_jerk_size_idx_1 = 1;
            cut_index_jerk_data[0] = max_jt.size(0);
        }

        b_max_at.set_size(1, max_at.size(0));
        n_loop_ub = max_at.size(0);
        for (int i22 = 0; i22 < n_loop_ub; i22++) {
            b_max_at[i22] = (max_at[i22] > ctx_cfg_ZeroStartAccLimit);
        }

        coder::eml_find(b_max_at, cut_index_vel_data, cut_index_vel_size);
        cut_index_acc_size_idx_1 = cut_index_vel_size[1];
        o_loop_ub = cut_index_vel_size[1];
        if (0 <= o_loop_ub - 1) {
            std::memcpy(&cut_index_acc_data[0], &cut_index_vel_data[0], o_loop_ub * sizeof(int));
        }

        if (cut_index_vel_size[1] == 0) {
            cut_index_acc_size_idx_1 = 1;
            cut_index_acc_data[0] = max_jt.size(0);
        }

        b_norm_vt.set_size(1, norm_vt.size(0));
        p_loop_ub = norm_vt.size(0);
        for (int i23 = 0; i23 < p_loop_ub; i23++) {
            b_norm_vt[i23] = (norm_vt[i23] > ctx_cfg_ZeroStartVelLimit);
        }

        coder::eml_find(b_norm_vt, cut_index_vel_data, cut_index_vel_size);
        if (cut_index_vel_size[1] == 0) {
            cut_index_vel_size[1] = 1;
            cut_index_vel_data[0] = max_jt.size(0);
        }

        if (0 <= cut_index_acc_size_idx_1 - 1) {
            std::memcpy(&x_data[0], &cut_index_acc_data[0], cut_index_acc_size_idx_1 * sizeof(int));
        }

        for (int i24 = 0; i24 < cut_index_jerk_size_idx_1; i24++) {
            x_data[i24 + cut_index_acc_size_idx_1] = cut_index_jerk_data[i24];
        }

        q_loop_ub = cut_index_vel_size[1];
        for (int i25 = 0; i25 < q_loop_ub; i25++) {
            x_data[(i25 + cut_index_acc_size_idx_1) + cut_index_jerk_size_idx_1] =
                cut_index_vel_data[i25];
        }

        c_ex = x_data[0];
        if (x_data[0] > x_data[1]) {
            c_ex = x_data[1];
        }

        if (c_ex > x_data[2]) {
            c_ex = x_data[2];
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
                       b_CurvStruct->P0, b_CurvStruct->P1, b_CurvStruct->HelixCenter,
                       b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch,
                       b_CurvStruct->CoeffP5, b_CurvStruct->sp_index, b_CurvStruct->a_param,
                       b_CurvStruct->b_param);
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
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, b_CurvStruct);
            printf("\nCut:\n");
            fflush(stdout);
            printf("Index = %d, t_cut = %e, vmax = %.1f\n", cut_index, t[cut_index - 1], b_vmax);
            fflush(stdout);
            printf("jps = %e, norm_vt(%d) = %f\n", jps, cut_index, norm_vt[cut_index - 1]);
            fflush(stdout);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct1);
            b_PrintCurvStruct(ctx_q_splines, ctx_cfg_NGridLengthSpline, CurvStruct2);
        }
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_HelixCenter[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double CurvStruct_CoeffP5[6][3]
    //                int CurvStruct_sp_index
    //                double CurvStruct_a_param
    //                double CurvStruct_b_param
    //                ::coder::array<double, 2U> &u_vec
    //                ::coder::array<double, 2U> &r0D
    //                ::coder::array<double, 2U> &r1D
    //                ::coder::array<double, 2U> &r2D
    // Return Type  : void
    //
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U>
        &r0D, ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D)
    {
        ::coder::array<double, 2U> r0Dx;
        ::coder::array<double, 2U> r0Dy;
        ::coder::array<double, 2U> r0Dz;
        ::coder::array<double, 2U> r1Dx;
        ::coder::array<double, 2U> r1Dy;
        ::coder::array<double, 2U> r1Dz;
        ::coder::array<double, 2U> r2Dx;
        ::coder::array<double, 2U> r2Dy;
        ::coder::array<double, 2U> r2Dz;
        ::coder::array<double, 2U> r3D;
        ::coder::array<double, 2U> r3Dx;
        ::coder::array<double, 2U> r3Dy;
        ::coder::array<double, 2U> r3Dz;
        ::coder::array<double, 2U> u_vec_tilda;
        ::coder::array<bool, 2U> x;
        CurvStruct expl_temp;
        double c;
        int b_k;
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int i5;
        int i_loop_ub;
        int k;
        int loop_ub;
        int scalarLB;
        int vectorUB;
        char message[30];
        bool b_y;
        bool exitg1;
        bool y;
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
        scalarLB = u_vec.size(1) & -2;
        vectorUB = scalarLB - 2;
        for (i5 = 0; i5 <= vectorUB; i5 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&u_vec[i5]);
            _mm_storeu_pd(&u_vec_tilda[i5], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r),
                           _mm_set1_pd(CurvStruct_b_param)));
        }

        for (i5 = scalarLB; i5 < f_loop_ub; i5++) {
            u_vec_tilda[i5] = CurvStruct_a_param * u_vec[i5] + CurvStruct_b_param;
        }

        switch (CurvStruct_Type) {
          case CurveType_Line:
            //  line (G01)
            EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_HelixCenter, CurvStruct_evec,
                      CurvStruct_theta, CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            {
                int h_loop_ub;
                int j_loop_ub;
                int k_loop_ub;
                int l_loop_ub;
                int m_loop_ub;
                int n_loop_ub;
                int o_loop_ub;
                int p_loop_ub;
                int q_loop_ub;

                //  BSpline
                ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
                bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_vec_tilda, r0Dx,
                                 r1Dx, r2Dx, r3Dx);
                bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_vec_tilda, r0Dy,
                                 r1Dy, r2Dy, r3Dy);
                bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_vec_tilda, r0Dz,
                                 r1Dz, r2Dz, r3Dz);
                r0D.set_size(3, r0Dx.size(1));
                h_loop_ub = r0Dx.size(1);
                for (int i8 = 0; i8 < h_loop_ub; i8++) {
                    r0D[3 * i8] = r0Dx[i8];
                }

                j_loop_ub = r0Dy.size(1);
                for (int i10 = 0; i10 < j_loop_ub; i10++) {
                    r0D[3 * i10 + 1] = r0Dy[i10];
                }

                k_loop_ub = r0Dz.size(1);
                for (int i11 = 0; i11 < k_loop_ub; i11++) {
                    r0D[3 * i11 + 2] = r0Dz[i11];
                }

                r1D.set_size(3, r1Dx.size(1));
                l_loop_ub = r1Dx.size(1);
                for (int i12 = 0; i12 < l_loop_ub; i12++) {
                    r1D[3 * i12] = r1Dx[i12];
                }

                m_loop_ub = r1Dy.size(1);
                for (int i13 = 0; i13 < m_loop_ub; i13++) {
                    r1D[3 * i13 + 1] = r1Dy[i13];
                }

                n_loop_ub = r1Dz.size(1);
                for (int i14 = 0; i14 < n_loop_ub; i14++) {
                    r1D[3 * i14 + 2] = r1Dz[i14];
                }

                r2D.set_size(3, r2Dx.size(1));
                o_loop_ub = r2Dx.size(1);
                for (int i15 = 0; i15 < o_loop_ub; i15++) {
                    r2D[3 * i15] = r2Dx[i15];
                }

                p_loop_ub = r2Dy.size(1);
                for (int i16 = 0; i16 < p_loop_ub; i16++) {
                    r2D[3 * i16 + 1] = r2Dy[i16];
                }

                q_loop_ub = r2Dz.size(1);
                for (int i17 = 0; i17 < q_loop_ub; i17++) {
                    r2D[3 * i17 + 2] = r2Dz[i17];
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
        g_loop_ub = r1D.size(1);
        for (int i7 = 0; i7 < g_loop_ub; i7++) {
            __m128d r1;
            r1 = _mm_loadu_pd(&r1D[3 * i7]);
            _mm_storeu_pd(&r1D[3 * i7], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r1));
            r1D[3 * i7 + 2] = CurvStruct_a_param * r1D[3 * i7 + 2];
        }

        c = std::pow(CurvStruct_a_param, 2.0);
        r2D.set_size(3, r2D.size(1));
        i_loop_ub = r2D.size(1);
        for (int i9 = 0; i9 < i_loop_ub; i9++) {
            __m128d r2;
            r2 = _mm_loadu_pd(&r2D[3 * i9]);
            _mm_storeu_pd(&r2D[3 * i9], _mm_mul_pd(_mm_set1_pd(c), r2));
            r2D[3 * i9 + 2] = c * r2D[3 * i9 + 2];
        }
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_HelixCenter[3]
    //                const double CurvStruct_evec[3]
    //                double CurvStruct_theta
    //                double CurvStruct_pitch
    //                const double CurvStruct_CoeffP5[6][3]
    //                int CurvStruct_sp_index
    //                double CurvStruct_a_param
    //                double CurvStruct_b_param
    //                ::coder::array<double, 2U> &u_vec
    //                ::coder::array<double, 2U> &r0D
    //                ::coder::array<double, 2U> &r1D
    //                ::coder::array<double, 2U> &r2D
    //                ::coder::array<double, 2U> &r3D
    // Return Type  : void
    //
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U>
        &r0D, ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D, ::coder::array<
        double, 2U> &r3D)
    {
        ::coder::array<double, 2U> r0Dx;
        ::coder::array<double, 2U> r0Dy;
        ::coder::array<double, 2U> r0Dz;
        ::coder::array<double, 2U> r1Dx;
        ::coder::array<double, 2U> r1Dy;
        ::coder::array<double, 2U> r1Dz;
        ::coder::array<double, 2U> r2Dx;
        ::coder::array<double, 2U> r2Dy;
        ::coder::array<double, 2U> r2Dz;
        ::coder::array<double, 2U> r3Dx;
        ::coder::array<double, 2U> r3Dy;
        ::coder::array<double, 2U> r3Dz;
        ::coder::array<double, 2U> u_vec_tilda;
        ::coder::array<bool, 2U> x;
        CurvStruct expl_temp;
        double b_c;
        double c;
        int b_k;
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i6;
        int j_loop_ub;
        int k;
        int loop_ub;
        int m_loop_ub;
        int scalarLB;
        int vectorUB;
        char message[30];
        bool b_y;
        bool exitg1;
        bool y;
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
        scalarLB = u_vec.size(1) & -2;
        vectorUB = scalarLB - 2;
        for (i6 = 0; i6 <= vectorUB; i6 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&u_vec[i6]);
            _mm_storeu_pd(&u_vec_tilda[i6], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r),
                           _mm_set1_pd(CurvStruct_b_param)));
        }

        for (i6 = scalarLB; i6 < g_loop_ub; i6++) {
            u_vec_tilda[i6] = CurvStruct_a_param * u_vec[i6] + CurvStruct_b_param;
        }

        switch (CurvStruct_Type) {
          case CurveType_Line:
            //  line (G01)
            EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_HelixCenter, CurvStruct_evec,
                      CurvStruct_theta, CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            {
                int i_loop_ub;
                int k_loop_ub;
                int l_loop_ub;
                int n_loop_ub;
                int o_loop_ub;
                int p_loop_ub;
                int q_loop_ub;
                int r_loop_ub;
                int s_loop_ub;
                int t_loop_ub;
                int u_loop_ub;
                int v_loop_ub;

                //  BSpline
                ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
                bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_vec_tilda, r0Dx,
                                 r1Dx, r2Dx, r3Dx);
                bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_vec_tilda, r0Dy,
                                 r1Dy, r2Dy, r3Dy);
                bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_vec_tilda, r0Dz,
                                 r1Dz, r2Dz, r3Dz);
                r0D.set_size(3, r0Dx.size(1));
                i_loop_ub = r0Dx.size(1);
                for (int i9 = 0; i9 < i_loop_ub; i9++) {
                    r0D[3 * i9] = r0Dx[i9];
                }

                k_loop_ub = r0Dy.size(1);
                for (int i11 = 0; i11 < k_loop_ub; i11++) {
                    r0D[3 * i11 + 1] = r0Dy[i11];
                }

                l_loop_ub = r0Dz.size(1);
                for (int i12 = 0; i12 < l_loop_ub; i12++) {
                    r0D[3 * i12 + 2] = r0Dz[i12];
                }

                r1D.set_size(3, r1Dx.size(1));
                n_loop_ub = r1Dx.size(1);
                for (int i14 = 0; i14 < n_loop_ub; i14++) {
                    r1D[3 * i14] = r1Dx[i14];
                }

                o_loop_ub = r1Dy.size(1);
                for (int i15 = 0; i15 < o_loop_ub; i15++) {
                    r1D[3 * i15 + 1] = r1Dy[i15];
                }

                p_loop_ub = r1Dz.size(1);
                for (int i16 = 0; i16 < p_loop_ub; i16++) {
                    r1D[3 * i16 + 2] = r1Dz[i16];
                }

                r2D.set_size(3, r2Dx.size(1));
                q_loop_ub = r2Dx.size(1);
                for (int i17 = 0; i17 < q_loop_ub; i17++) {
                    r2D[3 * i17] = r2Dx[i17];
                }

                r_loop_ub = r2Dy.size(1);
                for (int i18 = 0; i18 < r_loop_ub; i18++) {
                    r2D[3 * i18 + 1] = r2Dy[i18];
                }

                s_loop_ub = r2Dz.size(1);
                for (int i19 = 0; i19 < s_loop_ub; i19++) {
                    r2D[3 * i19 + 2] = r2Dz[i19];
                }

                r3D.set_size(3, r3Dx.size(1));
                t_loop_ub = r3Dx.size(1);
                for (int i20 = 0; i20 < t_loop_ub; i20++) {
                    r3D[3 * i20] = r3Dx[i20];
                }

                u_loop_ub = r3Dy.size(1);
                for (int i21 = 0; i21 < u_loop_ub; i21++) {
                    r3D[3 * i21 + 1] = r3Dy[i21];
                }

                v_loop_ub = r3Dz.size(1);
                for (int i22 = 0; i22 < v_loop_ub; i22++) {
                    r3D[3 * i22 + 2] = r3Dz[i22];
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
        h_loop_ub = r1D.size(1);
        for (int i8 = 0; i8 < h_loop_ub; i8++) {
            __m128d r1;
            r1 = _mm_loadu_pd(&r1D[3 * i8]);
            _mm_storeu_pd(&r1D[3 * i8], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r1));
            r1D[3 * i8 + 2] = CurvStruct_a_param * r1D[3 * i8 + 2];
        }

        c = std::pow(CurvStruct_a_param, 2.0);
        r2D.set_size(3, r2D.size(1));
        j_loop_ub = r2D.size(1);
        for (int i10 = 0; i10 < j_loop_ub; i10++) {
            __m128d r2;
            r2 = _mm_loadu_pd(&r2D[3 * i10]);
            _mm_storeu_pd(&r2D[3 * i10], _mm_mul_pd(_mm_set1_pd(c), r2));
            r2D[3 * i10 + 2] = c * r2D[3 * i10 + 2];
        }

        b_c = std::pow(CurvStruct_a_param, 3.0);
        r3D.set_size(3, r3D.size(1));
        m_loop_ub = r3D.size(1);
        for (int i13 = 0; i13 < m_loop_ub; i13++) {
            __m128d r3;
            r3 = _mm_loadu_pd(&r3D[3 * i13]);
            _mm_storeu_pd(&r3D[3 * i13], _mm_mul_pd(_mm_set1_pd(b_c), r3));
            r3D[3 * i13 + 2] = b_c * r3D[3 * i13 + 2];
        }
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_HelixCenter[3]
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
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, double r0D[3], double r1D[3], double r2D[3])
    {
        __m128d r;
        __m128d r1;
        CurvStruct expl_temp;
        double r3D[3];
        double c;
        double r0Dx;
        double r0Dy;
        double r0Dz;
        double r1Dx;
        double r1Dy;
        double r1Dz;
        double r2Dx;
        double r2Dy;
        double r2Dz;
        double r3Dx;
        double r3Dy;
        double r3Dz;
        double u_vec_tilda;
        char message[30];

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
            EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_HelixCenter, CurvStruct_evec,
                      CurvStruct_theta, CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            //  BSpline
            ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_vec_tilda, &r0Dx, &r1Dx,
                             &r2Dx, &r3Dx);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_vec_tilda, &r0Dy, &r1Dy,
                             &r2Dy, &r3Dy);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_vec_tilda, &r0Dz, &r1Dz,
                             &r2Dz, &r3Dz);
            r0D[0] = r0Dx;
            r0D[1] = r0Dy;
            r0D[2] = r0Dz;
            r1D[0] = r1Dx;
            r1D[1] = r1Dy;
            r1D[2] = r1Dz;
            r2D[0] = r2Dx;
            r2D[1] = r2Dy;
            r2D[2] = r2Dz;
            break;

          default:
            for (int i = 0; i < 30; i++) {
                message[i] = cv[i];
            }

            c_assert_(&message[0]);
            break;
        }

        c = std::pow(CurvStruct_a_param, 2.0);
        r = _mm_loadu_pd(&r1D[0]);
        _mm_storeu_pd(&r1D[0], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r));
        r1 = _mm_loadu_pd(&r2D[0]);
        _mm_storeu_pd(&r2D[0], _mm_mul_pd(_mm_set1_pd(c), r1));
        r1D[2] *= CurvStruct_a_param;
        r2D[2] *= c;
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_HelixCenter[3]
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
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_b_param,
        double r0D[3])
    {
        CurvStruct expl_temp;
        double r1D[3];
        double r2D[3];
        double r3D[3];
        double r0Dx;
        double r0Dy;
        double r0Dz;
        double r1Dx;
        double r1Dy;
        double r1Dz;
        double r2Dx;
        double r2Dy;
        double r2Dz;
        double r3Dx;
        double r3Dy;
        double r3Dz;
        char message[30];

        //
        //
        r0D[0] = 0.0;
        r0D[1] = 0.0;
        r0D[2] = 0.0;
        switch (CurvStruct_Type) {
          case CurveType_Line:
            //  line (G01)
            EvalLine(CurvStruct_P0, CurvStruct_P1, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_HelixCenter, CurvStruct_evec,
                      CurvStruct_theta, CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(CurvStruct_CoeffP5, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            //  BSpline
            ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, CurvStruct_b_param, &r0Dx,
                             &r1Dx, &r2Dx, &r3Dx);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, CurvStruct_b_param, &r0Dy,
                             &r1Dy, &r2Dy, &r3Dy);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, CurvStruct_b_param, &r0Dz,
                             &r1Dz, &r2Dz, &r3Dz);
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
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_HelixCenter[3]
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
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, double r0D[3], double r1D[3])
    {
        __m128d r;
        CurvStruct expl_temp;
        double r2D[3];
        double r3D[3];
        double r0Dx;
        double r0Dy;
        double r0Dz;
        double r1Dx;
        double r1Dy;
        double r1Dz;
        double r2Dx;
        double r2Dy;
        double r2Dz;
        double r3Dx;
        double r3Dy;
        double r3Dz;
        char message[30];

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
            EvalLine(CurvStruct_P0, CurvStruct_P1, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_HelixCenter, CurvStruct_evec,
                      CurvStruct_theta, CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(CurvStruct_CoeffP5, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            //  BSpline
            ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, CurvStruct_b_param, &r0Dx,
                             &r1Dx, &r2Dx, &r3Dx);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, CurvStruct_b_param, &r0Dy,
                             &r1Dy, &r2Dy, &r3Dy);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, CurvStruct_b_param, &r0Dz,
                             &r1Dz, &r2Dz, &r3Dz);
            r0D[0] = r0Dx;
            r0D[1] = r0Dy;
            r0D[2] = r0Dz;
            r1D[0] = r1Dx;
            r1D[1] = r1Dy;
            r1D[2] = r1Dz;
            break;

          default:
            for (int i = 0; i < 30; i++) {
                message[i] = cv[i];
            }

            c_assert_(&message[0]);
            break;
        }

        r = _mm_loadu_pd(&r1D[0]);
        _mm_storeu_pd(&r1D[0], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r));
        r1D[2] *= CurvStruct_a_param;
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_HelixCenter[3]
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
    static void b_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, double r0D[3])
    {
        CurvStruct expl_temp;
        double r1D[3];
        double r2D[3];
        double r3D[3];
        double r0Dx;
        double r0Dy;
        double r0Dz;
        double r1Dx;
        double r1Dy;
        double r1Dz;
        double r2Dx;
        double r2Dy;
        double r2Dz;
        double r3Dx;
        double r3Dy;
        double r3Dz;
        double u_vec_tilda;
        char message[30];

        //
        //
        r0D[0] = 0.0;
        r0D[1] = 0.0;
        r0D[2] = 0.0;
        u_vec_tilda = CurvStruct_a_param + CurvStruct_b_param;
        switch (CurvStruct_Type) {
          case CurveType_Line:
            //  line (G01)
            EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_HelixCenter, CurvStruct_evec,
                      CurvStruct_theta, CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            //  BSpline
            ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_vec_tilda, &r0Dx, &r1Dx,
                             &r2Dx, &r3Dx);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_vec_tilda, &r0Dy, &r1Dy,
                             &r2Dy, &r3Dy);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_vec_tilda, &r0Dz, &r1Dz,
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
    // Arguments    : const queue_coder *ctx_q_splines
    //                double ctx_cfg_NGridLengthSpline
    //                const CurvStruct *S
    // Return Type  : void
    //
    static void b_PrintCurvStruct(const queue_coder *ctx_q_splines, double ctx_cfg_NGridLengthSpline,
        const CurvStruct *S)
    {
        static const char b_cv1[7]{
            'T', 'r', 'a', 'n', 's', 'P', '5'
        };

        static const char b_cv2[6]{
            'S', 'p', 'l', 'i', 'n', 'e'
        };

        static const char b_cv[5]{
            'H', 'e', 'l', 'i', 'x'
        };

        coder::rtString formatSpec;
        double dv[3][6];
        double P0[3];
        double P1[3];
        double b_validatedHoleFilling_idx_0;
        double validatedHoleFilling_f2;
        double validatedHoleFilling_idx_0;
        int argC_size[2];
        int loop_ub;
        int varargin_1_size_idx_1;
        char b_varargin_1_data[10];
        char varargin_2_data[10];
        char argC_data[9];
        char varargin_1_data[9];
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

        if (0 <= varargin_1_size_idx_1 - 1) {
            std::memcpy(&varargin_2_data[0], &varargin_1_data[0], varargin_1_size_idx_1 * sizeof
                        (char));
        }

        varargin_2_data[varargin_1_size_idx_1] = '\x00';
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

        b_EvalCurvStruct(ctx_q_splines, S->Type, S->P0, S->P1, S->HelixCenter, S->evec, S->theta,
                         S->pitch, S->CoeffP5, S->sp_index, S->b_param, P0);
        b_EvalCurvStruct(ctx_q_splines, S->Type, S->P0, S->P1, S->HelixCenter, S->evec, S->theta,
                         S->pitch, S->CoeffP5, S->sp_index, S->a_param, S->b_param, P1);
        printf("%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n", "P", P0[0], P0[1], P0[2], P1[0], P1[1],
               P1[2]);
        fflush(stdout);
        validatedHoleFilling_f2 = LengthCurv(ctx_q_splines, ctx_cfg_NGridLengthSpline, S->Type,
            S->P0, S->P1, S->HelixCenter, S->evec, S->theta, S->pitch, S->CoeffP5, S->sp_index,
            S->a_param, S->b_param);
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
        loop_ub = argC_size[1];
        if (0 <= loop_ub - 1) {
            std::memcpy(&b_varargin_1_data[0], &argC_data[0], loop_ub * sizeof(char));
        }

        b_varargin_1_data[argC_size[1]] = '\x00';
        printf("ZSpdMode: %s\n", &b_varargin_1_data[0]);
        fflush(stdout);
        printf("FeedRate: %.2f\n", S->FeedRate);
        fflush(stdout);
        if (S->UseConstJerk) {
            CalcZeroStartConstraints(ctx_q_splines, S->Type, S->P0, S->P1, S->HelixCenter, S->evec,
                S->theta, S->pitch, S->CoeffP5, S->sp_index, S->UseConstJerk, S->ConstJerk,
                S->a_param, S->b_param, 1.0, &validatedHoleFilling_idx_0,
                &b_validatedHoleFilling_idx_0);
            printf("ConstJerk: %e\n", S->ConstJerk);
            fflush(stdout);
            printf("v_0      : %f\n", validatedHoleFilling_idx_0);
            fflush(stdout);
            printf("at_0     : %f\n", b_validatedHoleFilling_idx_0);
            fflush(stdout);
        }
    }

    //
    // Arguments    : int degree
    //                const ::coder::array<double, 2U> &breakpoints
    //                int *Bl_ncoeff
    //                ::coder::array<double, 2U> &Bl_breakpoints
    //                unsigned long *Bl_handle
    //                int *Bl_degree
    // Return Type  : void
    //
    static void b_bspline_create(int degree, const ::coder::array<double, 2U> &breakpoints, int
        *Bl_ncoeff, ::coder::array<double, 2U> &Bl_breakpoints, unsigned long *Bl_handle, int
        *Bl_degree)
    {
        ::coder::array<double, 2U> b_breakpoints;
        unsigned long b_Bl_handle;
        int b_Bl_ncoeff;
        int b_loop_ub;
        int loop_ub;
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
    // Arguments    : int Bl_ncoeff
    //                unsigned long Bl_handle
    //                const ::coder::array<double, 2U> &xvec
    //                ::coder::array<double, 2U> &BasisVal
    //                ::coder::array<double, 2U> &BasisValD
    // Return Type  : void
    //
    static void bspline_base_eval(int Bl_ncoeff, unsigned long Bl_handle, const ::coder::array<
        double, 2U> &xvec, ::coder::array<double, 2U> &BasisVal, ::coder::array<double, 2U>
        &BasisValD)
    {
        ::coder::array<double, 2U> BasisValDD;
        ::coder::array<double, 2U> BasisValDDD;
        ::coder::array<double, 1U> BasisIntegr;

        //  n, bspline_n
        BasisVal.set_size(xvec.size(1), Bl_ncoeff);
        BasisValD.set_size(xvec.size(1), Bl_ncoeff);
        BasisValDD.set_size(xvec.size(1), Bl_ncoeff);
        BasisValDDD.set_size(xvec.size(1), Bl_ncoeff);
        BasisIntegr.set_size(Bl_ncoeff);
        for (int i = 0; i < Bl_ncoeff; i++) {
            int b_loop_ub;
            int c_loop_ub;
            int d_loop_ub;
            int loop_ub;
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
    //                const ::coder::array<double, 1U> &coeffs
    //                double *x
    //                double *xd
    //                double *xdd
    // Return Type  : void
    //
    static void bspline_eval(unsigned long Bl_handle, const ::coder::array<double, 1U> &coeffs,
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

        c_bspline_eval(&Bl_handle, &(((::coder::array<double, 1U> *)&coeffs)->data())[0], *x, &X[0]);
        *x = X[0];
        *xd = X[1];
        *xdd = X[2];
    }

    //
    // void c_bspline_eval(uint64_t *handle, const double *c, double x, double X[3]);
    // Arguments    : unsigned long Bl_handle
    //                const ::coder::array<double, 2U> &coeffs
    //                double *x
    //                double *xd
    //                double *xdd
    //                double *xddd
    // Return Type  : void
    //
    static void bspline_eval(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
        double *x, double *xd, double *xdd, double *xddd)
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
    //                const ::coder::array<double, 2U> &coeffs
    //                const double u[10]
    //                double x[10]
    //                double xd[10]
    //                double xdd[10]
    //                double xddd[10]
    // Return Type  : void
    //
    static void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
        const double u[10], double x[10], double xd[10], double xdd[10], double xddd[10])
    {
        for (int k = 0; k < 10; k++) {
            x[k] = u[k];
            bspline_eval(Bl_handle, coeffs, &x[k], &xd[k], &xdd[k], &xddd[k]);
        }
    }

    //
    // Arguments    : unsigned long Bl_handle
    //                const ::coder::array<double, 2U> &coeffs
    //                double u
    //                double *x
    //                double *xd
    //                double *xdd
    //                double *xddd
    // Return Type  : void
    //
    static void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
        double u, double *x, double *xd, double *xdd, double *xddd)
    {
        *x = u;
        bspline_eval(Bl_handle, coeffs, x, xd, xdd, xddd);
    }

    //
    // Arguments    : unsigned long Bl_handle
    //                const ::coder::array<double, 2U> &coeffs
    //                const ::coder::array<double, 2U> &u
    //                ::coder::array<double, 2U> &x
    //                ::coder::array<double, 2U> &xd
    //                ::coder::array<double, 2U> &xdd
    //                ::coder::array<double, 2U> &xddd
    // Return Type  : void
    //
    static void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
        const ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &x, ::coder::array<double,
        2U> &xd, ::coder::array<double, 2U> &xdd, ::coder::array<double, 2U> &xddd)
    {
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int i4;
        int loop_ub;
        x.set_size(1, u.size(1));
        loop_ub = u.size(1);
        for (int i = 0; i < loop_ub; i++) {
            x[i] = 0.0;
        }

        xd.set_size(1, u.size(1));
        b_loop_ub = u.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            xd[i1] = 0.0;
        }

        xdd.set_size(1, u.size(1));
        c_loop_ub = u.size(1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            xdd[i2] = 0.0;
        }

        xddd.set_size(1, u.size(1));
        d_loop_ub = u.size(1);
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
    // Arguments    : unsigned long Bl_handle
    //                const ::coder::array<double, 2U> &coeffs
    //                const ::coder::array<double, 2U> &u
    //                ::coder::array<double, 2U> &x
    //                ::coder::array<double, 2U> &xd
    // Return Type  : void
    //
    static void bspline_eval_vec(unsigned long Bl_handle, const ::coder::array<double, 2U> &coeffs,
        const ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &x, ::coder::array<double,
        2U> &xd)
    {
        ::coder::array<double, 2U> xdd;
        ::coder::array<double, 2U> xddd;
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int i4;
        int loop_ub;
        x.set_size(1, u.size(1));
        loop_ub = u.size(1);
        for (int i = 0; i < loop_ub; i++) {
            x[i] = 0.0;
        }

        xd.set_size(1, u.size(1));
        b_loop_ub = u.size(1);
        for (int i1 = 0; i1 < b_loop_ub; i1++) {
            xd[i1] = 0.0;
        }

        xdd.set_size(1, u.size(1));
        c_loop_ub = u.size(1);
        for (int i2 = 0; i2 < c_loop_ub; i2++) {
            xdd[i2] = 0.0;
        }

        xddd.set_size(1, u.size(1));
        d_loop_ub = u.size(1);
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
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_HelixCenter[3]
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
    static void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, double r0D[3], double r1D[3])
    {
        __m128d r;
        CurvStruct expl_temp;
        double r2D[3];
        double r3D[3];
        double r0Dx;
        double r0Dy;
        double r0Dz;
        double r1Dx;
        double r1Dy;
        double r1Dz;
        double r2Dx;
        double r2Dy;
        double r2Dz;
        double r3Dx;
        double r3Dy;
        double r3Dz;
        double u_vec_tilda;
        char message[30];

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
            EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_HelixCenter, CurvStruct_evec,
                      CurvStruct_theta, CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            //  BSpline
            ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_vec_tilda, &r0Dx, &r1Dx,
                             &r2Dx, &r3Dx);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_vec_tilda, &r0Dy, &r1Dy,
                             &r2Dy, &r3Dy);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_vec_tilda, &r0Dz, &r1Dz,
                             &r2Dz, &r3Dz);
            r0D[0] = r0Dx;
            r0D[1] = r0Dy;
            r0D[2] = r0Dz;
            r1D[0] = r1Dx;
            r1D[1] = r1Dy;
            r1D[2] = r1Dz;
            break;

          default:
            for (int i = 0; i < 30; i++) {
                message[i] = cv[i];
            }

            c_assert_(&message[0]);
            break;
        }

        r = _mm_loadu_pd(&r1D[0]);
        _mm_storeu_pd(&r1D[0], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r));
        r1D[2] *= CurvStruct_a_param;
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const queue_coder *ctx_q_splines
    //                CurveType CurvStruct_Type
    //                const double CurvStruct_P0[3]
    //                const double CurvStruct_P1[3]
    //                const double CurvStruct_HelixCenter[3]
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
    static void c_EvalCurvStruct(const queue_coder *ctx_q_splines, CurveType CurvStruct_Type, const
        double CurvStruct_P0[3], const double CurvStruct_P1[3], const double CurvStruct_HelixCenter
        [3], const double CurvStruct_evec[3], double CurvStruct_theta, double CurvStruct_pitch,
        const double CurvStruct_CoeffP5[6][3], int CurvStruct_sp_index, double CurvStruct_a_param,
        double CurvStruct_b_param, double r0D[3], double r1D[3], double r2D[3])
    {
        __m128d r;
        __m128d r1;
        CurvStruct expl_temp;
        double r3D[3];
        double c;
        double r0Dx;
        double r0Dy;
        double r0Dz;
        double r1Dx;
        double r1Dy;
        double r1Dz;
        double r2Dx;
        double r2Dy;
        double r2Dz;
        double r3Dx;
        double r3Dy;
        double r3Dz;
        char message[30];

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
            EvalLine(CurvStruct_P0, CurvStruct_P1, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_HelixCenter, CurvStruct_evec,
                      CurvStruct_theta, CurvStruct_pitch, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(CurvStruct_CoeffP5, CurvStruct_b_param, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            //  BSpline
            ctx_q_splines->get(CurvStruct_sp_index, (&expl_temp));
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, CurvStruct_b_param, &r0Dx,
                             &r1Dx, &r2Dx, &r3Dx);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, CurvStruct_b_param, &r0Dy,
                             &r1Dy, &r2Dy, &r3Dy);
            bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, CurvStruct_b_param, &r0Dz,
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
            break;

          default:
            for (int i = 0; i < 30; i++) {
                message[i] = cv[i];
            }

            c_assert_(&message[0]);
            break;
        }

        c = std::pow(CurvStruct_a_param, 2.0);
        r = _mm_loadu_pd(&r1D[0]);
        _mm_storeu_pd(&r1D[0], _mm_mul_pd(_mm_set1_pd(CurvStruct_a_param), r));
        r1 = _mm_loadu_pd(&r2D[0]);
        _mm_storeu_pd(&r2D[0], _mm_mul_pd(_mm_set1_pd(c), r1));
        r1D[2] *= CurvStruct_a_param;
        r2D[2] *= c;
    }

    //
    // Arguments    : const ::coder::array<double, 2U> &f
    //                const coder::sparse *A
    //                ::coder::array<double, 2U> &b
    //                const ::coder::array<double, 2U> &Aeq
    //                const ::coder::array<double, 2U> &beq
    //                ::coder::array<double, 2U> &C
    //                bool *success
    //                int *status
    // Return Type  : void
    //
    static void c_simplex(const ::coder::array<double, 2U> &f, const coder::sparse *A, ::coder::
                          array<double, 2U> &b, const ::coder::array<double, 2U> &Aeq, const ::coder::
                          array<double, 2U> &beq, ::coder::array<double, 2U> &C, bool *success, int *
                          status)
    {
        coder::sparse Atot;
        ::coder::array<double, 1U> v;
        ::coder::array<int, 1U> Ais;
        ::coder::array<int, 1U> Ajs;
        ::coder::array<int, 1U> i_tmp;
        ::coder::array<int, 1U> j;
        int Asize[2];
        int Csize[2];
        int beqsize[2];
        int bsize[2];
        int fsize[2];
        int b_scalarLB;
        int b_vectorUB;
        int c_loop_ub;
        int d_loop_ub;
        int i2;
        int i5;
        int i7;
        int loop_ub;
        int n;
        int nx;
        int scalarLB;
        int vectorUB;
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
            i_tmp.set_size(0);
            j.set_size(0);
            v.set_size(0);
        } else {
            int b_idx;
            int col;
            i_tmp.set_size(nx);
            j.set_size(nx);
            v.set_size(nx);
            for (int idx = 0; idx < nx; idx++) {
                i_tmp[idx] = Atot.rowidx[idx];
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
                    i_tmp.set_size(0);
                    j.set_size(0);
                    v.set_size(0);
                }
            } else {
                int i3;
                int i4;
                int i6;
                if (1 > b_idx) {
                    i3 = 0;
                } else {
                    i3 = b_idx;
                }

                i_tmp.set_size(i3);
                if (1 > b_idx) {
                    i4 = 0;
                } else {
                    i4 = b_idx;
                }

                j.set_size(i4);
                if (1 > b_idx) {
                    i6 = 0;
                } else {
                    i6 = b_idx;
                }

                v.set_size(i6);
            }
        }

        Ais.set_size(i_tmp.size(0));
        c_loop_ub = i_tmp.size(0);
        scalarLB = i_tmp.size(0) & -4;
        vectorUB = scalarLB - 4;
        for (i2 = 0; i2 <= vectorUB; i2 += 4) {
            __m128i r;
            r = _mm_loadu_si128((__m128i *)&i_tmp[i2]);
            _mm_storeu_si128((__m128i *)&Ais[i2], _mm_sub_epi32(r, _mm_set1_epi32(1)));
        }

        for (i2 = scalarLB; i2 < c_loop_ub; i2++) {
            Ais[i2] = i_tmp[i2] - 1;
        }

        Ajs.set_size(j.size(0));
        d_loop_ub = j.size(0);
        b_scalarLB = j.size(0) & -4;
        b_vectorUB = b_scalarLB - 4;
        for (i5 = 0; i5 <= b_vectorUB; i5 += 4) {
            __m128i r1;
            r1 = _mm_loadu_si128((__m128i *)&j[i5]);
            _mm_storeu_si128((__m128i *)&Ajs[i5], _mm_sub_epi32(r1, _mm_set1_epi32(1)));
        }

        for (i5 = b_scalarLB; i5 < d_loop_ub; i5++) {
            Ajs[i5] = j[i5] - 1;
        }

        fsize[0] = f.size(0);
        fsize[1] = f.size(1);
        Asize[0] = Atot.m;
        Asize[1] = Atot.n;
        n = 0;
        i7 = v.size(0);
        for (int k = 0; k < i7; k++) {
            if (v[k] != 0.0) {
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
        b_status = simplex_solve(&f[0], &fsize[0], &(v.data())[0], &(Ais.data())[0], &(Ajs.data())[0],
            &Asize[0], n, &b[0], &bsize[0], &beq[0], &beqsize[0], &C[0], &Csize[0]);

        //          C = solution.solution;
        *success = (b_status == 0);
        *status = b_status;
    }

    //
    // Arguments    : double *x
    // Return Type  : void
    //
    namespace coder
    {
        static void b_cosd(double *x)
        {
            double absx;
            double b_x;
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
        // Arguments    : const ::coder::array<bool, 2U> &x
        //                int i_data[]
        //                int i_size[2]
        // Return Type  : void
        //
        static void b_eml_find(const ::coder::array<bool, 2U> &x, int i_data[], int i_size[2])
        {
            int idx;
            int ii;
            int k;
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
        //                ::coder::array<double, 2U> &y
        // Return Type  : void
        //
        static void b_eml_float_colon(double a, double d, ::coder::array<double, 2U> &y)
        {
            double apnd;
            double b1;
            double cdiff;
            double ndbl;
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
                b1 = 0.0;
            } else if (cdiff > 0.0) {
                b1 = a + (ndbl - 1.0) * d;
            } else {
                ndbl++;
                b1 = apnd;
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
                    double kd;
                    int nm1d2;
                    y[n - 1] = b1;
                    nm1d2 = (n - 1) / 2;
                    for (int k = 0; k <= nm1d2 - 2; k++) {
                        kd = (static_cast<double>(k) + 1.0) * d;
                        y[k + 1] = a + kd;
                        y[(n - k) - 2] = b1 - kd;
                    }

                    if (nm1d2 << 1 == n - 1) {
                        y[nm1d2] = (a + b1) / 2.0;
                    } else {
                        kd = static_cast<double>(nm1d2) * d;
                        y[nm1d2] = a + kd;
                        y[nm1d2 + 1] = b1 - kd;
                    }
                }
            }
        }

        //
        // Arguments    : int n
        //                ::coder::array<double, 2U> &y
        // Return Type  : void
        //
        static void b_linspace(int n, ::coder::array<double, 2U> &y)
        {
            if (n < 0) {
                y.set_size(1, 0);
            } else {
                y.set_size(1, n);
                if (n >= 1) {
                    y[n - 1] = 0.0;
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
        }

        //
        // Arguments    : const double x[3]
        // Return Type  : double
        //
        static double b_norm(const double x[3])
        {
            double absxk;
            double scale;
            double t;
            double y;
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
        // Arguments    : const ::coder::array<double, 2U> &a
        //                const ::coder::array<double, 2U> &b
        //                ::coder::array<double, 2U> &c
        // Return Type  : void
        //
        static void bsxfun(const ::coder::array<double, 2U> &a, const ::coder::array<double, 2U> &b,
                           ::coder::array<double, 2U> &c)
        {
            int b_u0;
            int b_u1;
            int b_y;
            int csz_idx_1;
            int i;
            int u0;
            int u1;
            int y;
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
                    _mm_storeu_pd(&c[3 * k], _mm_mul_pd(_mm_loadu_pd((double *)&a[3 * varargin_2]),
                                   _mm_set1_pd(b[varargin_3])));
                    c[3 * k + 2] = a[3 * varargin_2 + 2] * b[varargin_3];
                }
            }
        }

        //
        // Arguments    : const ::coder::array<double, 1U> &a
        //                const ::coder::array<double, 2U> &b
        //                ::coder::array<double, 2U> &c
        // Return Type  : void
        //
        static void bsxfun(const ::coder::array<double, 1U> &a, const ::coder::array<double, 2U> &b,
                           ::coder::array<double, 2U> &c)
        {
            int b_u0;
            int b_u1;
            int b_y;
            int i;
            int i1;
            int u0;
            int u1;
            int y;
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
                    int acoef;
                    int b_bcoef;
                    int i3;
                    int varargin_3;
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
        // Arguments    : const ::coder::array<double, 2U> &a
        //                const ::coder::array<double, 1U> &b
        //                ::coder::array<double, 2U> &c
        // Return Type  : void
        //
        static void bsxfun(const ::coder::array<double, 2U> &a, const ::coder::array<double, 1U> &b,
                           ::coder::array<double, 2U> &c)
        {
            int b_u0;
            int b_u1;
            int b_y;
            int i;
            int i1;
            int u0;
            int u1;
            int y;
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
                    int b_acoef;
                    int bcoef;
                    int i3;
                    int varargin_2;
                    varargin_2 = acoef * k;
                    b_acoef = (a.size(0) != 1);
                    bcoef = (b.size(0) != 1);
                    i3 = c.size(0) - 1;
                    for (int b_k = 0; b_k <= i3; b_k++) {
                        c[b_k + c.size(0) * k] = a[b_acoef * b_k + a.size(0) * varargin_2] * b[bcoef
                            * b_k];
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
            int idx;
            int ii;
            int nx;
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
        // Arguments    : const ::coder::array<double, 2U> &x
        //                ::coder::array<double, 2U> &y
        // Return Type  : void
        //
        static void diff(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y)
        {
            double tmp1;
            int dimSize;
            dimSize = x.size(1);
            if (x.size(1) == 0) {
                y.set_size(1, 0);
            } else {
                int b_y;
                int u0;
                u0 = x.size(1) - 1;
                if (u0 < 1) {
                    b_y = u0;
                } else {
                    b_y = 1;
                }

                if (b_y < 1) {
                    y.set_size(1, 0);
                } else {
                    y.set_size(1, (x.size(1) - 1));
                    if (x.size(1) - 1 != 0) {
                        double work_data_idx_0;
                        int ixLead;
                        int iyLead;
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
                            y[iyLead] = tmp1;
                            iyLead++;
                        }
                    }
                }
            }
        }

        //
        // Arguments    : const ::coder::array<bool, 2U> &x
        //                int i_data[]
        //                int i_size[2]
        // Return Type  : void
        //
        static void eml_find(const ::coder::array<bool, 2U> &x, int i_data[], int i_size[2])
        {
            int idx;
            int ii;
            int k;
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
        //                ::coder::array<double, 2U> &y
        // Return Type  : void
        //
        static void eml_float_colon(double d, double b, ::coder::array<double, 2U> &y)
        {
            double apnd;
            double b1;
            double cdiff;
            double ndbl;
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
                b1 = b;
            } else if (cdiff > 0.0) {
                b1 = (ndbl - 1.0) * d;
            } else {
                ndbl++;
                b1 = apnd;
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
                    double kd;
                    int nm1d2;
                    y[n - 1] = b1;
                    nm1d2 = (n - 1) / 2;
                    for (int k = 0; k <= nm1d2 - 2; k++) {
                        kd = (static_cast<double>(k) + 1.0) * d;
                        y[k + 1] = kd;
                        y[(n - k) - 2] = b1 - kd;
                    }

                    if (nm1d2 << 1 == n - 1) {
                        y[nm1d2] = b1 / 2.0;
                    } else {
                        kd = static_cast<double>(nm1d2) * d;
                        y[nm1d2] = kd;
                        y[nm1d2 + 1] = b1 - kd;
                    }
                }
            }
        }

        //
        // Arguments    : const double A[3]
        //                const ::coder::array<double, 2U> &B
        //                ::coder::array<double, 2U> &C
        // Return Type  : void
        //
        namespace internal
        {
            namespace blas
            {
                static void mtimes(const double A[3], const ::coder::array<double, 2U> &B, ::coder::
                                   array<double, 2U> &C)
                {
                    int n;
                    n = B.size(1);
                    C.set_size(1, B.size(1));
                    for (int j = 0; j < n; j++) {
                        C[j] = (A[0] * B[3 * j] + A[1] * B[3 * j + 1]) + A[2] * B[3 * j + 2];
                    }
                }

                //
                // Arguments    : int n
                //                const ::coder::array<double, 2U> &x
                //                int ix0
                // Return Type  : double
                //
                static double xnrm2(int n, const ::coder::array<double, 2U> &x, int ix0)
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
                // Arguments    : unsigned long x
                // Return Type  : unsigned long
                //
            }

            static unsigned long maximum2(unsigned long x)
            {
                double DBLMAXFLINT;
                unsigned long ex;
                bool alarge;
                bool blarge;
                bool p;
                p = false;
                DBLMAXFLINT = std::pow(2.0, 52.0);
                blarge = (1.0 >= DBLMAXFLINT);
                alarge = (x >= static_cast<unsigned long>(std::round(DBLMAXFLINT)));
                if ((!alarge) && blarge) {
                    p = true;
                } else if (alarge && blarge) {
                    p = (x < 1UL);
                } else {
                    if (!alarge) {
                        p = (x < 1.0);
                    }
                }

                if (p) {
                    ex = 1UL;
                } else {
                    ex = x;
                }

                return ex;
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
                    if (x_data[0] > x_data[1]) {
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
            // Arguments    : const ::coder::array<double, 2U> &A
            //                const ::coder::array<double, 1U> &B
            //                ::coder::array<double, 1U> &Y
            // Return Type  : void
            //
            static void qrsolve(const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U>
                                &B, ::coder::array<double, 1U> &Y)
            {
                static const int offsets[4]{
                    0, 1, 2, 3
                };

                ::coder::array<double, 2U> b_A;
                ::coder::array<double, 1U> b_B;
                ::coder::array<double, 1U> tau;
                ::coder::array<double, 1U> vn1;
                ::coder::array<double, 1U> vn2;
                ::coder::array<double, 1U> work;
                ::coder::array<int, 2U> jpvt;
                double atmp;
                double beta1;
                double c;
                double tol;
                double wj;
                int b_loop_ub;
                int b_m;
                int b_minmn;
                int b_u0;
                int b_u1;
                int c_u0;
                int c_u1;
                int d_loop_ub;
                int e_loop_ub;
                int f_loop_ub;
                int g_i;
                int g_loop_ub;
                int h_loop_ub;
                int iac;
                int jA;
                int k;
                int loop_ub;
                int m;
                int ma;
                int maxmn;
                int minmana;
                int minmn;
                int mn;
                int n;
                int rankR;
                int scalarLB;
                int u0;
                int u1;
                int vectorUB;
                m = A.size(0);
                n = A.size(1);
                u0 = A.size(0);
                u1 = A.size(1);
                if (u0 < u1) {
                    minmana = u0;
                } else {
                    minmana = u1;
                }

                tau.set_size(minmana);
                for (int i = 0; i < minmana; i++) {
                    tau[i] = 0.0;
                }

                jpvt.set_size(1, A.size(1));
                loop_ub = A.size(1);
                for (int i1 = 0; i1 < loop_ub; i1++) {
                    jpvt[i1] = 0;
                }

                scalarLB = A.size(1) & -4;
                vectorUB = scalarLB - 4;
                for (k = 0; k <= vectorUB; k += 4) {
                    _mm_storeu_si128((__m128i *)&jpvt[k], _mm_add_epi32(_mm_add_epi32(_mm_set1_epi32
                                       (k), _mm_loadu_si128((__m128i *)&offsets[0])), _mm_set1_epi32
                                      (1)));
                }

                for (k = scalarLB; k < n; k++) {
                    jpvt[k] = k + 1;
                }

                b_A.set_size(A.size(0), A.size(1));
                b_loop_ub = A.size(1);
                for (int i2 = 0; i2 < b_loop_ub; i2++) {
                    int c_loop_ub;
                    c_loop_ub = A.size(0);
                    for (int i3 = 0; i3 < c_loop_ub; i3++) {
                        b_A[i3 + b_A.size(0) * i2] = A[i3 + A.size(0) * i2];
                    }
                }

                ma = A.size(0);
                b_u0 = A.size(0);
                b_u1 = A.size(1);
                if (b_u0 < b_u1) {
                    minmn = b_u0;
                } else {
                    minmn = b_u1;
                }

                work.set_size(A.size(1));
                d_loop_ub = A.size(1);
                for (int i4 = 0; i4 < d_loop_ub; i4++) {
                    work[i4] = 0.0;
                }

                vn1.set_size(A.size(1));
                e_loop_ub = A.size(1);
                for (int i5 = 0; i5 < e_loop_ub; i5++) {
                    vn1[i5] = 0.0;
                }

                vn2.set_size(A.size(1));
                f_loop_ub = A.size(1);
                for (int i6 = 0; i6 < f_loop_ub; i6++) {
                    vn2[i6] = 0.0;
                }

                for (int j = 0; j < n; j++) {
                    double d;
                    d = blas::xnrm2(m, A, j * ma + 1);
                    vn1[j] = d;
                    vn2[j] = d;
                }

                for (int b_i = 0; b_i < minmn; b_i++) {
                    int idxmax;
                    int ii;
                    int ii_tmp;
                    int ip1;
                    int mmi;
                    int nmi;
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
                            double smax;
                            int ix;
                            ix = b_i;
                            smax = std::abs(vn1[b_i]);
                            for (int b_k = 2; b_k <= nmi; b_k++) {
                                double s;
                                ix++;
                                s = std::abs(vn1[ix]);
                                if (s > smax) {
                                    idxmax = b_k - 1;
                                    smax = s;
                                }
                            }
                        }
                    }

                    pvt = b_i + idxmax;
                    if (pvt + 1 != b_i + 1) {
                        int b_ix;
                        int iy;
                        b_ix = pvt * ma;
                        iy = ii_tmp;
                        for (int c_k = 0; c_k < m; c_k++) {
                            double temp;
                            temp = b_A[b_ix];
                            b_A[b_ix] = b_A[iy];
                            b_A[iy] = temp;
                            b_ix++;
                            iy++;
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
                        atmp = b_A[ii];
                        ix0 = ii + 2;
                        tau[b_i] = 0.0;
                        if (mmi > 0) {
                            double xnorm_tmp;
                            xnorm_tmp = blas::xnrm2(mmi - 1, b_A, ii + 2);
                            if (xnorm_tmp != 0.0) {
                                beta1 = rt_hypotd(b_A[ii], xnorm_tmp);
                                if (b_A[ii] >= 0.0) {
                                    beta1 = -beta1;
                                }

                                if (std::abs(beta1) < 1.0020841800044864E-292) {
                                    double b_a;
                                    int i9;
                                    int knt;
                                    knt = -1;
                                    i9 = ii + mmi;
                                    do {
                                        knt++;
                                        for (int e_k = ix0; e_k <= i9; e_k++) {
                                            b_A[e_k - 1] = 9.9792015476736E+291 * b_A[e_k - 1];
                                        }

                                        beta1 *= 9.9792015476736E+291;
                                        atmp *= 9.9792015476736E+291;
                                    } while (!(std::abs(beta1) >= 1.0020841800044864E-292));

                                    beta1 = rt_hypotd(atmp, blas::xnrm2(mmi - 1, b_A, ii + 2));
                                    if (atmp >= 0.0) {
                                        beta1 = -beta1;
                                    }

                                    tau[b_i] = (beta1 - atmp) / beta1;
                                    b_a = 1.0 / (atmp - beta1);
                                    for (int f_k = ix0; f_k <= i9; f_k++) {
                                        b_A[f_k - 1] = b_a * b_A[f_k - 1];
                                    }

                                    for (int g_k = 0; g_k <= knt; g_k++) {
                                        beta1 *= 1.0020841800044864E-292;
                                    }

                                    atmp = beta1;
                                } else {
                                    double a;
                                    int i10;
                                    tau[b_i] = (beta1 - b_A[ii]) / beta1;
                                    a = 1.0 / (b_A[ii] - beta1);
                                    i10 = ii + mmi;
                                    for (int d_k = ix0; d_k <= i10; d_k++) {
                                        b_A[d_k - 1] = a * b_A[d_k - 1];
                                    }

                                    atmp = beta1;
                                }
                            }
                        }

                        b_A[ii] = atmp;
                    } else {
                        tau[b_i] = 0.0;
                    }

                    if (b_i + 1 < n) {
                        double b_atmp;
                        int ic0;
                        int lastc;
                        int lastv;
                        b_atmp = b_A[ii];
                        b_A[ii] = 1.0;
                        ic0 = (ii + ma) + 1;
                        if (tau[b_i] != 0.0) {
                            int b_lastc;
                            int c_i;
                            bool exitg2;
                            lastv = mmi - 1;
                            c_i = (ii + mmi) - 1;
                            while ((lastv + 1 > 0) && (b_A[c_i] == 0.0)) {
                                lastv--;
                                c_i--;
                            }

                            b_lastc = nmi - 2;
                            exitg2 = false;
                            while ((!exitg2) && (b_lastc + 1 > 0)) {
                                int coltop;
                                int exitg1;
                                int ia;
                                coltop = ic0 + b_lastc * ma;
                                ia = coltop;
                                do {
                                    exitg1 = 0;
                                    if (ia <= coltop + lastv) {
                                        if (b_A[ia - 1] != 0.0) {
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
                                int i12;
                                for (int b_iy = 0; b_iy <= lastc; b_iy++) {
                                    work[b_iy] = 0.0;
                                }

                                c_iy = 0;
                                i12 = ic0 + ma * lastc;
                                for (iac = ic0; ma < 0 ? iac >= i12 : iac <= i12; iac += ma) {
                                    int c_ix;
                                    int i15;
                                    c_ix = ii;
                                    c = 0.0;
                                    i15 = iac + lastv;
                                    for (int b_ia = iac; b_ia <= i15; b_ia++) {
                                        c += b_A[b_ia - 1] * b_A[c_ix];
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
                                for (int e_j = 0; e_j <= lastc; e_j++) {
                                    if (work[jy] != 0.0) {
                                        double b_temp;
                                        int d_ix;
                                        int i16;
                                        b_temp = work[jy] * -tau[b_i];
                                        d_ix = ii;
                                        i16 = lastv + jA;
                                        for (int ijA = jA; ijA <= i16; ijA++) {
                                            b_A[ijA - 1] = b_A[ijA - 1] + b_A[d_ix] * b_temp;
                                            d_ix++;
                                        }
                                    }

                                    jy++;
                                    jA += ma;
                                }
                            }
                        }

                        b_A[ii] = b_atmp;
                    }

                    for (int b_j = ip1; b_j <= n; b_j++) {
                        double d1;
                        int ij;
                        ij = b_i + (b_j - 1) * ma;
                        d1 = vn1[b_j - 1];
                        if (d1 != 0.0) {
                            double temp1;
                            double temp2;
                            temp1 = std::abs(b_A[ij]) / d1;
                            temp1 = 1.0 - temp1 * temp1;
                            if (temp1 < 0.0) {
                                temp1 = 0.0;
                            }

                            temp2 = d1 / vn2[b_j - 1];
                            temp2 = temp1 * (temp2 * temp2);
                            if (temp2 <= 1.4901161193847656E-8) {
                                if (b_i + 1 < m) {
                                    double d2;
                                    d2 = blas::xnrm2(mmi - 1, b_A, ij + 2);
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

                rankR = 0;
                if (b_A.size(0) < b_A.size(1)) {
                    b_minmn = b_A.size(0);
                    maxmn = b_A.size(1);
                } else {
                    b_minmn = b_A.size(1);
                    maxmn = b_A.size(0);
                }

                tol = std::fmin(1.4901161193847656E-8, 2.2204460492503131E-15 * static_cast<double>
                                (maxmn)) * std::abs(b_A[0]);
                while ((rankR < b_minmn) && (std::abs(b_A[rankR + b_A.size(0) * rankR]) > tol)) {
                    rankR++;
                }

                b_B.set_size(B.size(0));
                g_loop_ub = B.size(0);
                for (int i7 = 0; i7 < g_loop_ub; i7++) {
                    b_B[i7] = B[i7];
                }

                Y.set_size(b_A.size(1));
                h_loop_ub = b_A.size(1);
                for (int i8 = 0; i8 < h_loop_ub; i8++) {
                    Y[i8] = 0.0;
                }

                b_m = b_A.size(0);
                c_u0 = b_A.size(0);
                c_u1 = b_A.size(1);
                if (c_u0 < c_u1) {
                    mn = c_u0;
                } else {
                    mn = c_u1;
                }

                for (int c_j = 0; c_j < mn; c_j++) {
                    if (tau[c_j] != 0.0) {
                        int i11;
                        wj = b_B[c_j];
                        i11 = c_j + 2;
                        for (int e_i = i11; e_i <= b_m; e_i++) {
                            wj += b_A[(e_i + b_A.size(0) * c_j) - 1] * b_B[e_i - 1];
                        }

                        wj *= tau[c_j];
                        if (wj != 0.0) {
                            int b_scalarLB;
                            int b_vectorUB;
                            int i14;
                            b_B[c_j] = b_B[c_j] - wj;
                            i14 = c_j + 2;
                            b_scalarLB = ((((b_m - c_j) - 1) & -2) + c_j) + 2;
                            b_vectorUB = b_scalarLB - 2;
                            for (g_i = i14; g_i <= b_vectorUB; g_i += 2) {
                                __m128d r;
                                __m128d r1;
                                r = _mm_loadu_pd(&b_A[(g_i + b_A.size(0) * c_j) - 1]);
                                r1 = _mm_loadu_pd(&b_B[g_i - 1]);
                                _mm_storeu_pd(&b_B[g_i - 1], _mm_sub_pd(r1, _mm_mul_pd(r,
                                                _mm_set1_pd(wj))));
                            }

                            for (g_i = b_scalarLB; g_i <= b_m; g_i++) {
                                b_B[g_i - 1] = b_B[g_i - 1] - b_A[(g_i + b_A.size(0) * c_j) - 1] *
                                    wj;
                            }
                        }
                    }
                }

                for (int d_i = 0; d_i < rankR; d_i++) {
                    Y[jpvt[d_i] - 1] = b_B[d_i];
                }

                for (int d_j = rankR; d_j >= 1; d_j--) {
                    int i13;
                    i13 = jpvt[d_j - 1];
                    Y[i13 - 1] = Y[i13 - 1] / b_A[(d_j + b_A.size(0) * (d_j - 1)) - 1];
                    for (int f_i = 0; f_i <= d_j - 2; f_i++) {
                        Y[jpvt[f_i] - 1] = Y[jpvt[f_i] - 1] - Y[jpvt[d_j - 1] - 1] * b_A[f_i +
                            b_A.size(0) * (d_j - 1)];
                    }
                }
            }

            //
            // Arguments    : const ::coder::array<double, 2U> &A
            //                const ::coder::array<double, 1U> &B
            //                ::coder::array<double, 1U> &Y
            // Return Type  : void
            //
        }

        static void mldivide(const ::coder::array<double, 2U> &A, const ::coder::array<double, 1U>
                             &B, ::coder::array<double, 1U> &Y)
        {
            ::coder::array<double, 2U> b_A;
            ::coder::array<int, 2U> ipiv;
            int b_ix;
            int iy;
            int jA;
            int jy;
            if (A.size(0) == A.size(1)) {
                int LDA;
                int b_LDA;
                int b_u0;
                int c_loop_ub;
                int c_u0;
                int i2;
                int ldap1;
                int loop_ub;
                int n;
                int u0;
                int u1;
                int y;
                int yk;
                u0 = A.size(0);
                u1 = A.size(1);
                if (u0 < u1) {
                    y = u0;
                } else {
                    y = u1;
                }

                b_u0 = B.size(0);
                if (b_u0 < y) {
                    n = b_u0;
                } else {
                    n = y;
                }

                LDA = A.size(0);
                b_A.set_size(A.size(0), A.size(1));
                loop_ub = A.size(1);
                for (int i = 0; i < loop_ub; i++) {
                    int b_loop_ub;
                    b_loop_ub = A.size(0);
                    for (int i1 = 0; i1 < b_loop_ub; i1++) {
                        b_A[i1 + b_A.size(0) * i] = A[i1 + A.size(0) * i];
                    }
                }

                ipiv.set_size(1, n);
                ipiv[0] = 1;
                yk = 1;
                for (int k = 2; k <= n; k++) {
                    yk++;
                    ipiv[k - 1] = yk;
                }

                ldap1 = A.size(0);
                c_u0 = n - 1;
                if (c_u0 < n) {
                    i2 = c_u0;
                } else {
                    i2 = n;
                }

                for (int j = 0; j < i2; j++) {
                    int a;
                    int b;
                    int jj;
                    int jp1j;
                    int mmj_tmp;
                    mmj_tmp = n - j;
                    b = j * (LDA + 1);
                    jj = j * (ldap1 + 1);
                    jp1j = b + 2;
                    if (mmj_tmp < 1) {
                        a = -1;
                    } else {
                        a = 0;
                        if (mmj_tmp > 1) {
                            double smax;
                            int ix;
                            ix = b;
                            smax = std::abs(b_A[jj]);
                            for (int d_k = 2; d_k <= mmj_tmp; d_k++) {
                                double s;
                                ix++;
                                s = std::abs(b_A[ix]);
                                if (s > smax) {
                                    a = d_k - 1;
                                    smax = s;
                                }
                            }
                        }
                    }

                    if (b_A[jj + a] != 0.0) {
                        int i5;
                        if (a != 0) {
                            int ipiv_tmp;
                            ipiv_tmp = j + a;
                            ipiv[j] = ipiv_tmp + 1;
                            iy = ipiv_tmp;
                            b_ix = j;
                            for (int e_k = 0; e_k < n; e_k++) {
                                double b_temp;
                                b_temp = b_A[b_ix];
                                b_A[b_ix] = b_A[iy];
                                b_A[iy] = b_temp;
                                b_ix += LDA;
                                iy += LDA;
                            }
                        }

                        i5 = jj + mmj_tmp;
                        for (int c_i = jp1j; c_i <= i5; c_i++) {
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
                            int i7;
                            int i8;
                            c_ix = jj + 1;
                            i7 = jA + 2;
                            i8 = mmj_tmp + jA;
                            for (int ijA = i7; ijA <= i8; ijA++) {
                                b_A[ijA - 1] = b_A[ijA - 1] + b_A[c_ix] * -yjy;
                                c_ix++;
                            }
                        }

                        jy += LDA;
                        jA += LDA;
                    }
                }

                Y.set_size(B.size(0));
                c_loop_ub = B.size(0);
                for (int i3 = 0; i3 < c_loop_ub; i3++) {
                    Y[i3] = B[i3];
                }

                b_LDA = b_A.size(0);
                for (int b_i = 0; b_i <= n - 2; b_i++) {
                    int i4;
                    i4 = ipiv[b_i];
                    if (i4 != b_i + 1) {
                        double temp;
                        temp = Y[b_i];
                        Y[b_i] = Y[i4 - 1];
                        Y[i4 - 1] = temp;
                    }
                }

                for (int b_k = 0; b_k < n; b_k++) {
                    int kAcol;
                    kAcol = b_LDA * b_k;
                    if (Y[b_k] != 0.0) {
                        int i6;
                        i6 = b_k + 2;
                        for (int d_i = i6; d_i <= n; d_i++) {
                            Y[d_i - 1] = Y[d_i - 1] - Y[b_k] * b_A[(d_i + kAcol) - 1];
                        }
                    }
                }

                for (int c_k = n; c_k >= 1; c_k--) {
                    double d;
                    int b_kAcol;
                    b_kAcol = b_LDA * (c_k - 1);
                    d = Y[c_k - 1];
                    if (d != 0.0) {
                        Y[c_k - 1] = d / b_A[(c_k + b_kAcol) - 1];
                        for (int e_i = 0; e_i <= c_k - 2; e_i++) {
                            Y[e_i] = Y[e_i] - Y[c_k - 1] * b_A[e_i + b_kAcol];
                        }
                    }
                }
            } else {
                internal::qrsolve(A, B, Y);
            }
        }

        //
        // Arguments    : const double a_data[]
        //                const int a_size[1]
        //                double y_data[]
        //                int y_size[1]
        // Return Type  : void
        //
        static void power(const double a_data[], const int a_size[1], double y_data[], int y_size[1])
        {
            int N;
            y_size[0] = a_size[0];
            N = a_size[0];
            for (int k = 0; k < N; k++) {
                y_data[k] = std::pow(a_data[k], 2.0);
            }
        }

        //
        // Arguments    : const ::coder::array<double, 2U> &x
        //                ::coder::array<double, 2U> &y
        // Return Type  : void
        //
        static void sum(const ::coder::array<double, 2U> &x, ::coder::array<double, 2U> &y)
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
        // Arguments    : int numerator
        //                int denominator
        // Return Type  : int
        //
    }

    static int div_s32_floor(int numerator, int denominator)
    {
        unsigned int absNumerator;
        int quotient;
        if (denominator == 0) {
            if (numerator >= 0) {
                quotient = MAX_int32_T;
            } else {
                quotient = MIN_int32_T;
            }
        } else {
            unsigned int absDenominator;
            unsigned int tempAbsQuotient;
            bool quotientNeedsNegation;
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
    // Arguments    : double u0
    //                double u1
    // Return Type  : double
    //
    static double rt_hypotd(double u0, double u1)
    {
        double a;
        double b;
        double y;
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
    // Arguments    : void
    // Return Type  : void
    //
    ResampleStateClass::ResampleStateClass()
    {
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    ResampleStateClass::~ResampleStateClass()
    {
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    queue_coder::queue_coder()
    {
    }

    //
    // Arguments    : void
    // Return Type  : void
    //
    queue_coder::~queue_coder()
    {
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
        ::coder::array<bool, 2U> c_expl_temp;
        CurvStruct b_expl_temp;
        CurvStruct expl_temp;
        double p5[6][3];
        double P0[3];
        double P1[3];
        double dv[3];
        double dv1[3];
        double r0D0[3];
        double r0D0_1[3];
        double r0D0_2[3];
        double r0D1[3];
        double r0D1_1[3];
        double r0D1_2[3];
        double r0D2[3];
        double r1D0[3];
        double r1D0_1[3];
        double r1D0_2[3];
        double r1D1[3];
        double r1D1_1[3];
        double r1D1_2[3];
        double r1D2[3];
        double expl_temp_data[1];
        double CutOff;
        double Length_Threshold;
        double alpha0;
        double alpha1;
        double d;
        double d1;
        double d2;
        double d3;
        unsigned long u;
        int expl_temp_size[2];
        int tmp_size[2];
        int tmp_data[1];
        int ret;
        bool guard1{
            false
        };

        TransitionResult b_status;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        CutOff = ctx->cfg.CutOff;
        Length_Threshold = 3.0 * ctx->cfg.CutOff;

        //  DebugLog(DebugCfg.Transitions, ...
        //      '========== CalcTransition ==========\n')
        u = static_cast<unsigned long>(DebugConfig) & 8UL;
        if (u != 0UL) {
            b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct1);
            b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct2);
        }

        *CurvStruct_T = *CurvStruct1;

        // default value
        b_EvalCurvStruct(&ctx->q_splines, CurvStruct1->Type, CurvStruct1->P0, CurvStruct1->P1,
                         CurvStruct1->HelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                         CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                         CurvStruct1->a_param, CurvStruct1->b_param, r0D0_1, r0D1_1);
        c_EvalCurvStruct(&ctx->q_splines, CurvStruct1->Type, CurvStruct1->P0, CurvStruct1->P1,
                         CurvStruct1->HelixCenter, CurvStruct1->evec, CurvStruct1->theta,
                         CurvStruct1->pitch, CurvStruct1->CoeffP5, CurvStruct1->sp_index,
                         CurvStruct1->a_param, CurvStruct1->b_param, r0D0_2, r0D1_2);
        b_EvalCurvStruct(&ctx->q_splines, CurvStruct2->Type, CurvStruct2->P0, CurvStruct2->P1,
                         CurvStruct2->HelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                         CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                         CurvStruct2->a_param, CurvStruct2->b_param, r1D0_1, r1D1_1);
        c_EvalCurvStruct(&ctx->q_splines, CurvStruct2->Type, CurvStruct2->P0, CurvStruct2->P1,
                         CurvStruct2->HelixCenter, CurvStruct2->evec, CurvStruct2->theta,
                         CurvStruct2->pitch, CurvStruct2->CoeffP5, CurvStruct2->sp_index,
                         CurvStruct2->a_param, CurvStruct2->b_param, r1D0_2, r1D1_2);

        //  colinearity test
        guard1 = false;
        if ((CurvStruct1->Type != CurveType_Helix) && (CurvStruct2->Type != CurveType_Helix)) {
            double absxk;
            double scale;
            double t;
            bool value;
            scale = 3.3121686421112381E-170;
            absxk = std::abs(r0D1_2[0]);
            if (absxk > 3.3121686421112381E-170) {
                d = 1.0;
                scale = absxk;
            } else {
                t = absxk / 3.3121686421112381E-170;
                d = t * t;
            }

            absxk = std::abs(r0D1_2[1]);
            if (absxk > scale) {
                t = scale / absxk;
                d = d * t * t + 1.0;
                scale = absxk;
            } else {
                t = absxk / scale;
                d += t * t;
            }

            absxk = std::abs(r0D1_2[2]);
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
                double b_absxk;
                double b_scale;
                double b_t;
                b_scale = 3.3121686421112381E-170;
                b_absxk = std::abs(r1D1_1[0]);
                if (b_absxk > 3.3121686421112381E-170) {
                    d1 = 1.0;
                    b_scale = b_absxk;
                } else {
                    b_t = b_absxk / 3.3121686421112381E-170;
                    d1 = b_t * b_t;
                }

                b_absxk = std::abs(r1D1_1[1]);
                if (b_absxk > b_scale) {
                    b_t = b_scale / b_absxk;
                    d1 = d1 * b_t * b_t + 1.0;
                    b_scale = b_absxk;
                } else {
                    b_t = b_absxk / b_scale;
                    d1 += b_t * b_t;
                }

                b_absxk = std::abs(r1D1_1[2]);
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
                    d2 = 57.295779513082323 * std::acos(((r0D1_2[0] * r1D1_1[0] + r0D1_2[1] *
                        r1D1_1[1]) + r0D1_2[2] * r1D1_1[2]) / (d * d1));
                    coder::b_cosd(&d2);
                    d3 = ctx->cfg.CollTolDeg;
                    coder::b_cosd(&d3);
                    value = (d2 > d3);
                }
            }

            if (value) {
                //  && norm(r0D2 - r1D2) < 10*eps && collinear(r0D2, r1D2, 1e-2)
                b_status = TransitionResult_Collinear;
                *CurvStruct1_C = *CurvStruct1;
                *CurvStruct2_C = *CurvStruct2;
            } else {
                guard1 = true;
            }
        } else {
            guard1 = true;
        }

        if (guard1) {
            double L1;
            double L2;
            L1 = LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct1->Type,
                            CurvStruct1->P0, CurvStruct1->P1, CurvStruct1->HelixCenter,
                            CurvStruct1->evec, CurvStruct1->theta, CurvStruct1->pitch,
                            CurvStruct1->CoeffP5, CurvStruct1->sp_index, CurvStruct1->a_param,
                            CurvStruct1->b_param);
            L2 = LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct2->Type,
                            CurvStruct2->P0, CurvStruct2->P1, CurvStruct2->HelixCenter,
                            CurvStruct2->evec, CurvStruct2->theta, CurvStruct2->pitch,
                            CurvStruct2->CoeffP5, CurvStruct2->sp_index, CurvStruct2->a_param,
                            CurvStruct2->b_param);

            //  CutOff calculation
            if ((CurvStruct1->Type != CurveType_Spline) && (CurvStruct2->Type != CurveType_Spline))
            {
                if ((L1 < Length_Threshold) || (L2 < Length_Threshold)) {
                    CutOff = std::fmin(L1, L2) / 3.0;
                }
            } else {
                double x;
                double y;
                if (CurvStruct1->Type == CurveType_Spline) {
                    double u1_tilda;
                    int b_loop_ub;
                    int c_loop_ub;
                    ctx->q_splines.get(CurvStruct1->sp_index, (&expl_temp));

                    //  In a very general case we may cut a spline several times
                    //  at the end;
                    //  If a spline had already been cut at the end,
                    //  we must compute the corresponding
                    //  native spline parameter (u1_tilda) value
                    //  This value will be different from 1 in this special case
                    u1_tilda = CurvStruct1->a_param + CurvStruct1->b_param;

                    //  We need to find the previous spline knot u0_tilda...
                    c_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
                    b_loop_ub = expl_temp.sp.knots.size(1);
                    for (int i1 = 0; i1 < b_loop_ub; i1++) {
                        c_expl_temp[i1] = (expl_temp.sp.knots[i1] < u1_tilda);
                    }

                    coder::b_eml_find(c_expl_temp, tmp_data, tmp_size);
                    expl_temp_size[0] = 1;
                    expl_temp_size[1] = tmp_size[1];
                    c_loop_ub = tmp_size[1];
                    for (int i2 = 0; i2 < c_loop_ub; i2++) {
                        expl_temp_data[i2] = expl_temp.sp.knots[tmp_data[i2] - 1];
                    }

                    x = SplineLengthApprox(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                                           CurvStruct1->sp_index, expl_temp_data, expl_temp_size,
                                           u1_tilda) / 2.0;
                } else if (L1 < Length_Threshold) {
                    x = L1 / 3.0;
                } else {
                    x = ctx->cfg.CutOff;
                }

                if (CurvStruct2->Type == CurveType_Spline) {
                    int d_loop_ub;
                    int e_loop_ub;
                    int loop_ub;
                    ctx->q_splines.get(CurvStruct2->sp_index, (&b_expl_temp));
                    expl_temp.sp.knots.set_size(1, b_expl_temp.sp.knots.size(1));
                    loop_ub = b_expl_temp.sp.knots.size(1);
                    for (int i = 0; i < loop_ub; i++) {
                        expl_temp.sp.knots[i] = b_expl_temp.sp.knots[i];
                    }

                    //  In a very general case we may cut a spline several times
                    //  at the beginning;
                    //  If a spline had already been cut at the beginning,
                    //  we must compute the corresponding
                    //  native spline parameter (u0_tilda) value
                    //  This value will be different from 0 in this special case
                    //  We need to find the next spline knot u1_tilda...
                    c_expl_temp.set_size(1, expl_temp.sp.knots.size(1));
                    d_loop_ub = expl_temp.sp.knots.size(1);
                    for (int i3 = 0; i3 < d_loop_ub; i3++) {
                        c_expl_temp[i3] = (expl_temp.sp.knots[i3] > CurvStruct2->b_param);
                    }

                    coder::eml_find(c_expl_temp, tmp_data, tmp_size);
                    expl_temp_size[0] = 1;
                    expl_temp_size[1] = tmp_size[1];
                    e_loop_ub = tmp_size[1];
                    for (int i4 = 0; i4 < e_loop_ub; i4++) {
                        expl_temp_data[i4] = expl_temp.sp.knots[tmp_data[i4] - 1];
                    }

                    y = SplineLengthApprox(&ctx->q_splines, ctx->cfg.NGridLengthSpline,
                                           CurvStruct2->sp_index, CurvStruct2->b_param,
                                           expl_temp_data, expl_temp_size) / 2.0;
                } else if (L2 < Length_Threshold) {
                    y = L2 / 3.0;
                } else {
                    y = ctx->cfg.CutOff;
                }

                CutOff = std::fmin(x, y);
            }

            //  DebugLog(DebugCfg.Transitions, ...
            //      'CutOff = %.3f\n', CutOff)
            *CurvStruct1_C = *CurvStruct1;
            CutCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct1_C, CutOff);
            *CurvStruct2_C = *CurvStruct2;
            b_CutCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct2_C, CutOff);

            //  1 -> stdout
            //  2 -> stderr
            if (u != 0UL) {
                printf("========== AFTER CUTTING \n");
                fflush(stdout);
                b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct1_C);
                b_PrintCurvStruct(&ctx->q_splines, ctx->cfg.NGridLengthSpline, CurvStruct2_C);
            }

            b_EvalCurvStruct(&ctx->q_splines, CurvStruct1_C->Type, CurvStruct1_C->P0,
                             CurvStruct1_C->P1, CurvStruct1_C->HelixCenter, CurvStruct1_C->evec,
                             CurvStruct1_C->theta, CurvStruct1_C->pitch, CurvStruct1_C->CoeffP5,
                             CurvStruct1_C->sp_index, CurvStruct1_C->a_param, CurvStruct1_C->b_param,
                             r0D0, r0D1, r0D2);
            c_EvalCurvStruct(&ctx->q_splines, CurvStruct2_C->Type, CurvStruct2_C->P0,
                             CurvStruct2_C->P1, CurvStruct2_C->HelixCenter, CurvStruct2_C->evec,
                             CurvStruct2_C->theta, CurvStruct2_C->pitch, CurvStruct2_C->CoeffP5,
                             CurvStruct2_C->sp_index, CurvStruct2_C->a_param, CurvStruct2_C->b_param,
                             r1D0, r1D1, r1D2);

            //  G2 transition calculation
            G2_Hermite_Interpolation(r0D0, r0D1, r0D2, r1D0, r1D1, r1D2, p5, &ret, &alpha0, &alpha1);
            if (ret == 1) {
                //  standard case
                //  transition CurvStruct calculation
                // POLYVAL Evaluate array of polynomials with same degree.
                //
                //
                //  Use Horner's method for general case where X is an array.
                // POLYVAL Evaluate array of polynomials with same degree.
                //
                //
                //  Use Horner's method for general case where X is an array.
                P1[0] = p5[0][0];
                P1[1] = p5[0][1];
                P1[2] = p5[0][2];
                for (int b_i = 0; b_i < 5; b_i++) {
                    __m128d r;
                    __m128d r2;
                    double P0_tmp;
                    P0[0] = p5[b_i + 1][0];
                    P0[1] = p5[b_i + 1][1];
                    P0_tmp = p5[b_i + 1][2];
                    P0[2] = P0_tmp;
                    r = _mm_loadu_pd(&P1[0]);
                    r2 = _mm_loadu_pd(&p5[b_i + 1][0]);
                    _mm_storeu_pd(&P1[0], _mm_add_pd(r, r2));
                    P1[2] += P0_tmp;
                }

                dv[0] = 0.0;
                dv1[0] = 0.0;
                dv[1] = 0.0;
                dv1[1] = 0.0;
                dv[2] = 0.0;
                dv1[2] = 0.0;
                ConstrCurvStruct(CurveType_TransP5, ZSpdMode_NN, P0, P1, dv, dv1, 0.0, 0.0, p5,
                                 CurvStruct1->FeedRate, CurvStruct_T);
                b_status = TransitionResult_Ok;
            } else if (ret == 6) {
                unsigned long u2;

                //  TODO: decide in the future...
                //  Now we ignore and construct the transition curve anyway
                // POLYVAL Evaluate array of polynomials with same degree.
                //
                //
                //  Use Horner's method for general case where X is an array.
                // POLYVAL Evaluate array of polynomials with same degree.
                //
                //
                //  Use Horner's method for general case where X is an array.
                P1[0] = p5[0][0];
                P1[1] = p5[0][1];
                P1[2] = p5[0][2];
                for (int c_i = 0; c_i < 5; c_i++) {
                    __m128d r1;
                    __m128d r3;
                    double b_P0_tmp;
                    P0[0] = p5[c_i + 1][0];
                    P0[1] = p5[c_i + 1][1];
                    b_P0_tmp = p5[c_i + 1][2];
                    P0[2] = b_P0_tmp;
                    r1 = _mm_loadu_pd(&P1[0]);
                    r3 = _mm_loadu_pd(&p5[c_i + 1][0]);
                    _mm_storeu_pd(&P1[0], _mm_add_pd(r1, r3));
                    P1[2] += b_P0_tmp;
                }

                dv[0] = 0.0;
                dv1[0] = 0.0;
                dv[1] = 0.0;
                dv1[1] = 0.0;
                dv[2] = 0.0;
                dv1[2] = 0.0;
                ConstrCurvStruct(CurveType_TransP5, ZSpdMode_NN, P0, P1, dv, dv1, 0.0, 0.0, p5,
                                 CurvStruct1->FeedRate, CurvStruct_T);
                b_status = TransitionResult_Ok;

                //  1 -> stdout
                //  2 -> stderr
                u2 = static_cast<unsigned long>(DebugConfig) & 16UL;
                if (u2 != 0UL) {
                    printf("========== CalcTransition ==========\n");
                    fflush(stdout);
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u2 != 0UL) {
                    printf("=========== status = 6 ==========\n");
                    fflush(stdout);
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u2 != 0UL) {
                    printf("Lines: %d, %d\n\n", CurvStruct1->gcode_source_line,
                           CurvStruct2->gcode_source_line);
                    fflush(stdout);
                }

                //      if coder.target('matlab')
                //
                //          figure;
                //          PlotCurvStructsBR(ctx, [CurvStruct1 CurvStruct_T CurvStruct2]);
                //          hold on;
                //          plot3(r0D0(1), r0D0(2), r0D0(3), 'xr', 'LineWidth', 3);
                //          hold on;
                //          plot3(r1D0(1), r1D0(2), r1D0(3), 'xr', 'LineWidth', 3);
                //          title({ctx.cfg.source, 'status_G2_Hermite=6'}, 'Interpreter', 'none');
                //          axis equal;
                //          camproj('perspective');
                //
                //      end
            } else {
                unsigned long u1;
                b_status = TransitionResult_NoSolution;

                //  1 -> stdout
                //  2 -> stderr
                u1 = static_cast<unsigned long>(DebugConfig) & 32UL;
                if (u1 != 0UL) {
                    printf("========== CalcTransition ==========\n");
                    fflush(stdout);
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u1 != 0UL) {
                    printf("=========== No Solution ==========\n");
                    fflush(stdout);
                }

                //  1 -> stdout
                //  2 -> stderr
                if (u1 != 0UL) {
                    printf("Lines: %d, %d\n\n", CurvStruct1->gcode_source_line,
                           CurvStruct2->gcode_source_line);
                    fflush(stdout);
                }
            }

            CurvStruct1_C->gcode_source_line = CurvStruct1->gcode_source_line;
            CurvStruct_T->gcode_source_line = CurvStruct2->gcode_source_line;
            CurvStruct2_C->gcode_source_line = CurvStruct2->gcode_source_line;
            CurvStruct1_C->SpindleSpeed = CurvStruct1->SpindleSpeed;
            CurvStruct_T->SpindleSpeed = std::fmin(CurvStruct1->SpindleSpeed,
                CurvStruct2->SpindleSpeed);
            CurvStruct2_C->SpindleSpeed = CurvStruct2->SpindleSpeed;
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
        int b_loop_ub;
        int i;
        int i1;
        int loop_ub;
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
    //                const double C[3]
    //                const double evec[3]
    //                double theta
    //                double pitch
    //                double FeedRate
    //                ZSpdMode b_ZSpdMode
    //                CurvStruct *b_CurvStruct
    // Return Type  : void
    //
    void ConstrHelixStruct(const double P0[3], const double P1[3], const double C[3], const double
                           evec[3], double theta, double pitch, double FeedRate, ZSpdMode b_ZSpdMode,
                           CurvStruct *b_CurvStruct)
    {
        double dv[6][3];
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        for (int i = 0; i < 6; i++) {
            dv[i][0] = 0.0;
            dv[i][1] = 0.0;
            dv[i][2] = 0.0;
        }

        ConstrCurvStruct(CurveType_Helix, b_ZSpdMode, P0, P1, C, evec, theta, pitch, dv, FeedRate,
                         b_CurvStruct);
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
        __m128d r;
        __m128d r1;
        __m128d r2;
        __m128d r3;
        double C[3];
        double P0[3];
        double P1[3];
        double b[3];
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
        C[0] = cx;
        C[1] = cy;
        C[2] = cz;
        r = _mm_loadu_pd(&P0[0]);
        r1 = _mm_loadu_pd(&C[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r, r1));
        b[2] = p0z - cz;
        R0_idx_0 = evec[1] * b[2] - evec[2] * b[1];
        R0_idx_1 = evec[2] * b[0] - evec[0] * b[2];
        R0_idx_2 = evec[0] * b[1] - evec[1] * b[0];
        r2 = _mm_loadu_pd(&P1[0]);
        r3 = _mm_loadu_pd(&C[0]);
        _mm_storeu_pd(&b[0], _mm_sub_pd(r2, r3));
        b[2] = p1z - cz;
        R1_idx_0 = evec[1] * b[2] - evec[2] * b[1];
        R1_idx_1 = evec[2] * b[0] - evec[0] * b[2];
        R1_idx_2 = evec[0] * b[1] - evec[1] * b[0];
        if (evec[0] > 0.5) {
            phi0 = std::atan2(R0_idx_2, R0_idx_1);
            phi1 = std::atan2(R1_idx_2, R1_idx_1);
        } else if (evec[1] > 0.5) {
            phi1 = std::atan2(R0_idx_2, R0_idx_0);
            phi0 = std::atan2(R1_idx_2, R1_idx_0);

            //      rotation = -rotation;
        } else {
            phi0 = std::atan2(R0_idx_1, R0_idx_0);
            phi1 = std::atan2(R1_idx_1, R1_idx_0);
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

        ConstrHelixStruct(P0, P1, C, evec, theta, (((evec[0] * p1x + evec[1] * p1y) + evec[2] * p1z)
                           - ((evec[0] * p0x + evec[1] * p0y) + evec[2] * p0z)) / theta * 2.0 *
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
        double dv2[6][3];
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
        for (int i = 0; i < 6; i++) {
            dv2[i][0] = 0.0;
            dv2[i][1] = 0.0;
            dv2[i][2] = 0.0;
        }

        ConstrCurvStruct(CurveType_Line, b_ZSpdMode, P0, P1, dv, dv1, 0.0, 0.0, dv2, FeedRate,
                         b_CurvStruct);
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
    // Arguments    : DebugCfg cfg
    // Return Type  : void
    //
    void DisableDebugLog(DebugCfg cfg)
    {
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        DebugConfig = static_cast<double>(static_cast<unsigned long>(DebugConfig) & ~(1UL << (
            static_cast<int>(cfg) - 1)));
    }

    //
    // Arguments    : DebugCfg cfg
    // Return Type  : void
    //
    void EnableDebugLog(DebugCfg cfg)
    {
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        DebugConfig = static_cast<double>(static_cast<unsigned long>(DebugConfig) | 1UL << (
            static_cast<int>(cfg) - 1));
    }

    //
    // coder.cstructname(CurvStruct, 'CurvStruct')
    // Arguments    : const FeedoptContext *ctx
    //                const CurvStruct *b_CurvStruct
    //                ::coder::array<double, 2U> &u_vec
    //                ::coder::array<double, 2U> &r0D
    //                ::coder::array<double, 2U> &r1D
    //                ::coder::array<double, 2U> &r2D
    //                ::coder::array<double, 2U> &r3D
    // Return Type  : void
    //
    void EvalCurvStruct(const FeedoptContext *ctx, const CurvStruct *b_CurvStruct, ::coder::array<
                        double, 2U> &u_vec, ::coder::array<double, 2U> &r0D, ::coder::array<double,
                        2U> &r1D, ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D)
    {
        ::coder::array<double, 2U> r0Dx;
        ::coder::array<double, 2U> r0Dy;
        ::coder::array<double, 2U> r0Dz;
        ::coder::array<double, 2U> r1Dx;
        ::coder::array<double, 2U> r1Dy;
        ::coder::array<double, 2U> r1Dz;
        ::coder::array<double, 2U> r2Dx;
        ::coder::array<double, 2U> r2Dy;
        ::coder::array<double, 2U> r2Dz;
        ::coder::array<double, 2U> r3Dx;
        ::coder::array<double, 2U> r3Dy;
        ::coder::array<double, 2U> r3Dz;
        ::coder::array<double, 2U> u_vec_tilda;
        ::coder::array<bool, 2U> x;
        CurvStruct expl_temp;
        double b_c;
        double c;
        int b_k;
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i6;
        int j_loop_ub;
        int k;
        int loop_ub;
        int m_loop_ub;
        int scalarLB;
        int vectorUB;
        char message[30];
        bool b_y;
        bool exitg1;
        bool y;
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
        scalarLB = u_vec.size(1) & -2;
        vectorUB = scalarLB - 2;
        for (i6 = 0; i6 <= vectorUB; i6 += 2) {
            __m128d r;
            r = _mm_loadu_pd(&u_vec[i6]);
            _mm_storeu_pd(&u_vec_tilda[i6], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(b_CurvStruct->a_param),
                            r), _mm_set1_pd(b_CurvStruct->b_param)));
        }

        for (i6 = scalarLB; i6 < g_loop_ub; i6++) {
            u_vec_tilda[i6] = b_CurvStruct->a_param * u_vec[i6] + b_CurvStruct->b_param;
        }

        switch (b_CurvStruct->Type) {
          case CurveType_Line:
            //  line (G01)
            EvalLine(b_CurvStruct->P0, b_CurvStruct->P1, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(b_CurvStruct->P0, b_CurvStruct->P1, b_CurvStruct->HelixCenter,
                      b_CurvStruct->evec, b_CurvStruct->theta, b_CurvStruct->pitch, u_vec_tilda, r0D,
                      r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(b_CurvStruct->CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            {
                int i_loop_ub;
                int k_loop_ub;
                int l_loop_ub;
                int n_loop_ub;
                int o_loop_ub;
                int p_loop_ub;
                int q_loop_ub;
                int r_loop_ub;
                int s_loop_ub;
                int t_loop_ub;
                int u_loop_ub;
                int v_loop_ub;

                //  BSpline
                ctx->q_splines.get(b_CurvStruct->sp_index, (&expl_temp));
                bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffX, u_vec_tilda, r0Dx,
                                 r1Dx, r2Dx, r3Dx);
                bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffY, u_vec_tilda, r0Dy,
                                 r1Dy, r2Dy, r3Dy);
                bspline_eval_vec(expl_temp.sp.Bl.handle, expl_temp.sp.CoeffZ, u_vec_tilda, r0Dz,
                                 r1Dz, r2Dz, r3Dz);
                r0D.set_size(3, r0Dx.size(1));
                i_loop_ub = r0Dx.size(1);
                for (int i9 = 0; i9 < i_loop_ub; i9++) {
                    r0D[3 * i9] = r0Dx[i9];
                }

                k_loop_ub = r0Dy.size(1);
                for (int i11 = 0; i11 < k_loop_ub; i11++) {
                    r0D[3 * i11 + 1] = r0Dy[i11];
                }

                l_loop_ub = r0Dz.size(1);
                for (int i12 = 0; i12 < l_loop_ub; i12++) {
                    r0D[3 * i12 + 2] = r0Dz[i12];
                }

                r1D.set_size(3, r1Dx.size(1));
                n_loop_ub = r1Dx.size(1);
                for (int i14 = 0; i14 < n_loop_ub; i14++) {
                    r1D[3 * i14] = r1Dx[i14];
                }

                o_loop_ub = r1Dy.size(1);
                for (int i15 = 0; i15 < o_loop_ub; i15++) {
                    r1D[3 * i15 + 1] = r1Dy[i15];
                }

                p_loop_ub = r1Dz.size(1);
                for (int i16 = 0; i16 < p_loop_ub; i16++) {
                    r1D[3 * i16 + 2] = r1Dz[i16];
                }

                r2D.set_size(3, r2Dx.size(1));
                q_loop_ub = r2Dx.size(1);
                for (int i17 = 0; i17 < q_loop_ub; i17++) {
                    r2D[3 * i17] = r2Dx[i17];
                }

                r_loop_ub = r2Dy.size(1);
                for (int i18 = 0; i18 < r_loop_ub; i18++) {
                    r2D[3 * i18 + 1] = r2Dy[i18];
                }

                s_loop_ub = r2Dz.size(1);
                for (int i19 = 0; i19 < s_loop_ub; i19++) {
                    r2D[3 * i19 + 2] = r2Dz[i19];
                }

                r3D.set_size(3, r3Dx.size(1));
                t_loop_ub = r3Dx.size(1);
                for (int i20 = 0; i20 < t_loop_ub; i20++) {
                    r3D[3 * i20] = r3Dx[i20];
                }

                u_loop_ub = r3Dy.size(1);
                for (int i21 = 0; i21 < u_loop_ub; i21++) {
                    r3D[3 * i21 + 1] = r3Dy[i21];
                }

                v_loop_ub = r3Dz.size(1);
                for (int i22 = 0; i22 < v_loop_ub; i22++) {
                    r3D[3 * i22 + 2] = r3Dz[i22];
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
        h_loop_ub = r1D.size(1);
        for (int i8 = 0; i8 < h_loop_ub; i8++) {
            __m128d r1;
            r1 = _mm_loadu_pd(&r1D[3 * i8]);
            _mm_storeu_pd(&r1D[3 * i8], _mm_mul_pd(_mm_set1_pd(b_CurvStruct->a_param), r1));
            r1D[3 * i8 + 2] = b_CurvStruct->a_param * r1D[3 * i8 + 2];
        }

        c = std::pow(b_CurvStruct->a_param, 2.0);
        r2D.set_size(3, r2D.size(1));
        j_loop_ub = r2D.size(1);
        for (int i10 = 0; i10 < j_loop_ub; i10++) {
            __m128d r2;
            r2 = _mm_loadu_pd(&r2D[3 * i10]);
            _mm_storeu_pd(&r2D[3 * i10], _mm_mul_pd(_mm_set1_pd(c), r2));
            r2D[3 * i10 + 2] = c * r2D[3 * i10 + 2];
        }

        b_c = std::pow(b_CurvStruct->a_param, 3.0);
        r3D.set_size(3, r3D.size(1));
        m_loop_ub = r3D.size(1);
        for (int i13 = 0; i13 < m_loop_ub; i13++) {
            __m128d r3;
            r3 = _mm_loadu_pd(&r3D[3 * i13]);
            _mm_storeu_pd(&r3D[3 * i13], _mm_mul_pd(_mm_set1_pd(b_c), r3));
            r3D[3 * i13 + 2] = b_c * r3D[3 * i13 + 2];
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
        double r1D[3];
        double r2D[3];
        double r3D[3];
        double u_vec;
        double u_vec_tilda;
        char message[30];
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
            EvalLine(Curv->P0, Curv->P1, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Helix:
            //  arc of circle / helix (G02, G03)
            EvalHelix(Curv->P0, Curv->P1, Curv->HelixCenter, Curv->evec, Curv->theta, Curv->pitch,
                      u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_TransP5:
            //  polynomial transition
            EvalTransP5(Curv->CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
            break;

          case CurveType_Spline:
            //  BSpline
            EvalBSplineNoCtx(Spline->sp.CoeffX, Spline->sp.CoeffY, Spline->sp.CoeffZ,
                             Spline->sp.Bl.handle, u_vec_tilda, r0D, r1D, r2D, r3D);
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
        static const char b_cv[9]{
            'l', 'o', 'g', 's', '/', 'l', 'o', 'g', 's'
        };

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
        static const char b_message[39]{
            'F', 'e', 'e', 'd', 'o', 'p', 't', 'P', 'l', 'a', 'n', ':', ' ', 'e', 'r', 'r', 'o', 'r',
                ' ', 'c', 'o', 'd', 'e', ' ', 'w', 'a', 's', ' ', 'n', 'o', 't', ' ', 'h', 'a', 'n',
                'd', 'l', 'e', 'd'
        };

        queue_coder d_ctx;
        queue_coder e_ctx;
        queue_coder h_ctx;
        queue_coder i_ctx;
        ::coder::array<CurvStruct, 2U> OptSegment;
        ::coder::array<double, 2U> Coeff;
        ::coder::array<double, 2U> c_ctx;
        CurvStruct NextCurv;
        CurvStruct b_CurvStruct;
        CurvStruct b_first;
        CurvStruct last;
        CurvStruct r;
        double dv[3];
        double dv1[3];
        double g_ctx[3];
        double at_0;
        double b_at_0;
        int unusedU0;
        char b_cv[1025];
        char message[39];
        bool b_optimized;
        bool b_success;
        bool guard1{
            false
        };

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
                if ((static_cast<unsigned long>(DebugConfig) & 1UL) != 0UL) {
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
                    if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
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

            //  1 -> stdout
            //  2 -> stderr
            if ((static_cast<unsigned long>(DebugConfig) & 1UL) != 0UL) {
                printf("Feedrate Planning...\n");
                fflush(stdout);
            }
            break;

          case Fopt_Opt:
            {
                if (ctx->q_split.isempty()) {
                    //  1 -> stdout
                    //  2 -> stderr
                    if ((static_cast<unsigned long>(DebugConfig) & 1UL) != 0UL) {
                        printf("Queue empty...\n");
                        fflush(stdout);
                    }

                    ctx->op = Fopt_Finished;
                } else {
                    ctx->op = Fopt_Opt;
                    if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
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
                            int varargin_2;
                            ctx->q_split.get((static_cast<double>(1.0)), (&r));
                            varargin_2 = ctx->cfg.NHorz;
                            OptSegment.set_size(1, varargin_2);
                            for (int i3 = 0; i3 < varargin_2; i3++) {
                                OptSegment[i3] = r;
                            }

                            ctx->q_split.get(ctx->k0, (&b_first));
                            if (b_first.zspdmode == ZSpdMode_ZN) {
                                *opt_struct = b_first;
                                b_optimized = true;
                                d_ctx = ctx->q_splines;
                                CalcZeroStartConstraints(&d_ctx, b_first.Type, b_first.P0,
                                    b_first.P1, b_first.HelixCenter, b_first.evec, b_first.theta,
                                    b_first.pitch, b_first.CoeffP5, b_first.sp_index,
                                    b_first.UseConstJerk, b_first.ConstJerk, b_first.a_param,
                                    b_first.b_param, 1.0, &ctx->v_0, &ctx->at_0);
                                ctx->zero_start = true;
                            } else {
                                unsigned long u;
                                int Retry;
                                int e_loop_ub;
                                int k;
                                int k1;
                                int k1temp;
                                int kend;
                                unsigned int nopt;
                                bool exitg1;
                                bool success;
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
                                u = static_cast<unsigned long>(DebugConfig) & 8UL;
                                if (u != 0UL) {
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
                                            NextCurv.P1, NextCurv.HelixCenter, NextCurv.evec,
                                            NextCurv.theta, NextCurv.pitch, NextCurv.CoeffP5,
                                            NextCurv.sp_index, NextCurv.UseConstJerk,
                                            NextCurv.ConstJerk, NextCurv.a_param, NextCurv.b_param,
                                            1.0, &ctx->v_1, &at_0);
                                        ctx->at_1 = -at_0;
                                        ctx->zero_end = true;
                                        ctx->reached_end = true;
                                        kend = k;
                                        exitg1 = true;
                                    } else {
                                        if (NextCurv.zspdmode == ZSpdMode_NN) {
                                            nopt++;
                                            OptSegment[static_cast<int>(nopt) - 1] = NextCurv;
                                            if (u != 0UL) {
                                                b_PrintCurvStruct(&ctx->q_splines,
                                                                  ctx->cfg.NGridLengthSpline,
                                                                  &OptSegment[k - ctx->k0]);
                                            }

                                            if ((k < k1) && (u != 0UL)) {
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
                                if (u != 0UL) {
                                    printf("================================================\n");
                                    fflush(stdout);
                                }

                                Retry = 0;
                                success = false;
                                Coeff.set_size(0, 0);
                                while ((Retry < 100) && (!success)) {
                                    int f_ctx;
                                    if (ctx->cfg.NHorz > static_cast<int>(nopt)) {
                                        f_ctx = static_cast<int>(nopt);
                                    } else {
                                        f_ctx = ctx->cfg.NHorz;
                                    }

                                    g_ctx[0] = ctx->cfg.jmax[0];
                                    g_ctx[1] = ctx->cfg.jmax[1];
                                    g_ctx[2] = ctx->cfg.jmax[2];
                                    FeedratePlanning_v4(ctx, OptSegment, ctx->cfg.amax, g_ctx,
                                                        ctx->BasisVal, ctx->BasisValD,
                                                        ctx->BasisValDD, ctx->BasisIntegr,
                                                        ctx->Bl.handle, ctx->u_vec, f_ctx, Coeff,
                                                        &unusedU0, &b_success);
                                    success = b_success;
                                    if ((!b_success) && ctx->zero_start) {
                                        //  1 -> stdout
                                        //  2 -> stderr
                                        if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL)
                                        {
                                            printf("ZeroStart at k = %d failed, halving jerk\n",
                                                   ctx->k0 - 1);
                                            fflush(stdout);
                                        }

                                        ctx->q_split.get((ctx->k0 - 1), (&r));
                                        h_ctx = ctx->q_splines;
                                        CalcZeroStartConstraints(&h_ctx, r.Type, r.P0, r.P1,
                                            r.HelixCenter, r.evec, r.theta, r.pitch, r.CoeffP5,
                                            r.sp_index, r.UseConstJerk, r.ConstJerk, r.a_param,
                                            r.b_param, std::pow(0.5, static_cast<double>(Retry)),
                                            &ctx->v_0, &ctx->at_0);
                                    }

                                    if ((!b_success) && ctx->zero_end) {
                                        //  1 -> stdout
                                        //  2 -> stderr
                                        if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL)
                                        {
                                            printf("ZeroEnd at k = %d failed, halving jerk\n", kend);
                                            fflush(stdout);
                                        }

                                        ctx->q_split.get(kend, (&r));
                                        i_ctx = ctx->q_splines;
                                        CalcZeroStartConstraints(&i_ctx, r.Type, r.P0, r.P1,
                                            r.HelixCenter, r.evec, r.theta, r.pitch, r.CoeffP5,
                                            r.sp_index, r.UseConstJerk, r.ConstJerk, r.a_param,
                                            r.b_param, std::pow(0.5, static_cast<double>(Retry)),
                                            &ctx->v_1, &b_at_0);
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
                                        if (u != 0UL) {
                                            b_PrintCurvStruct(&ctx->q_splines,
                                                              ctx->cfg.NGridLengthSpline,
                                                              &OptSegment[0]);
                                        }
                                    }

                                    //  1 -> stdout
                                    //  2 -> stderr
                                    if (u != 0UL) {
                                        printf("OPTIMIZATION FAILED!\n");
                                        fflush(stdout);
                                    }

                                    ctx->errcode = FeedoptPlanError_OptimizationFailed;
                                    ctx->op = Fopt_Finished;
                                } else {
                                    guard1 = true;
                                }
                            }
                        } else {
                            int b_ctx;
                            int b_loop_ub;
                            int c_loop_ub;
                            int i2;
                            int i4;

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
            if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
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
        ::coder::array<double, 2U> BasisVal;
        ::coder::array<double, 2U> BasisValD;
        ::coder::array<double, 2U> BasisValDD;
        ::coder::array<double, 2U> breakpoints;
        ::coder::array<double, 2U> r;
        ::coder::array<double, 2U> unusedU0;
        ::coder::array<double, 2U> x;
        ::coder::array<double, 2U> y;
        CurvStruct Curv;
        double dv[3];
        double dv1[3];
        unsigned long Bl_handle;
        int Bl_degree;
        int Bl_ncoeff;
        int c_scalarLB;
        int c_vectorUB;
        int d_loop_ub;
        int d_scalarLB;
        int d_vectorUB;
        int f_loop_ub;
        int i;
        int i4;
        int i5;
        int i6;
        int i8;
        int l_loop_ub;
        int n_loop_ub;
        int p_loop_ub;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        if (cfg.UseLinearBreakpoints) {
            int b_loop_ub;
            if (cfg.NBreak < 0) {
                ctx->Bl.breakpoints.set_size(1, 0);
            } else {
                ctx->Bl.breakpoints.set_size(1, cfg.NBreak);
                if (cfg.NBreak >= 1) {
                    ctx->Bl.breakpoints[cfg.NBreak - 1] = 1.0;
                    if (ctx->Bl.breakpoints.size(1) >= 2) {
                        ctx->Bl.breakpoints[0] = 0.0;
                        if (ctx->Bl.breakpoints.size(1) >= 3) {
                            double delta1;
                            int i2;
                            delta1 = 1.0 / (static_cast<double>(ctx->Bl.breakpoints.size(1)) - 1.0);
                            i2 = ctx->Bl.breakpoints.size(1);
                            for (int k = 0; k <= i2 - 3; k++) {
                                ctx->Bl.breakpoints[k + 1] = (static_cast<double>(k) + 1.0) * delta1;
                            }
                        }
                    }
                }
            }

            Bl_ncoeff = (ctx->Bl.breakpoints.size(1) + cfg.SplineDegree) - 2;
            breakpoints.set_size(1, ctx->Bl.breakpoints.size(1));
            b_loop_ub = ctx->Bl.breakpoints.size(1);
            for (int i1 = 0; i1 < b_loop_ub; i1++) {
                breakpoints[i1] = ctx->Bl.breakpoints[i1];
            }

            c_bspline_create_with_breakpoints(&Bl_handle, cfg.SplineDegree, &breakpoints[0],
                ctx->Bl.breakpoints.size(1));
            Bl_degree = cfg.SplineDegree;
        } else {
            int b_scalarLB;
            int b_vectorUB;
            int c_loop_ub;
            int e_loop_ub;
            int g_loop_ub;
            int i3;
            int loop_ub;
            int scalarLB;
            int vectorUB;
            coder::b_linspace(cfg.NBreak, r);
            y.set_size(1, r.size(1));
            loop_ub = r.size(1);
            scalarLB = r.size(1) & -2;
            vectorUB = scalarLB - 2;
            for (i = 0; i <= vectorUB; i += 2) {
                __m128d r1;
                r1 = _mm_loadu_pd(&r[i]);
                _mm_storeu_pd(&y[i], _mm_mul_pd(_mm_set1_pd(3.1415926535897931), r1));
            }

            for (i = scalarLB; i < loop_ub; i++) {
                y[i] = 3.1415926535897931 * r[i];
            }

            i3 = y.size(1);
            for (int b_k = 0; b_k < i3; b_k++) {
                y[b_k] = std::cos(y[b_k]);
            }

            x.set_size(1, y.size(1));
            c_loop_ub = y.size(1);
            b_scalarLB = y.size(1) & -2;
            b_vectorUB = b_scalarLB - 2;
            for (i4 = 0; i4 <= b_vectorUB; i4 += 2) {
                __m128d r2;
                __m128d r4;
                r2 = _mm_loadu_pd(&y[i4]);
                r4 = _mm_set1_pd(0.5);
                _mm_storeu_pd(&x[i4], _mm_add_pd(_mm_mul_pd(r2, r4), r4));
            }

            for (i4 = b_scalarLB; i4 < c_loop_ub; i4++) {
                x[i4] = y[i4] * 0.5 + 0.5;
            }

            Bl_ncoeff = (x.size(1) + cfg.SplineDegree) - 2;
            ctx->Bl.breakpoints.set_size(1, x.size(1));
            e_loop_ub = x.size(1);
            for (int i7 = 0; i7 < e_loop_ub; i7++) {
                ctx->Bl.breakpoints[i7] = x[i7];
            }

            c_bspline_create_with_breakpoints(&Bl_handle, cfg.SplineDegree, &ctx->Bl.breakpoints[0],
                x.size(1));
            ctx->Bl.breakpoints.set_size(1, x.size(1));
            g_loop_ub = x.size(1);
            for (int i9 = 0; i9 < g_loop_ub; i9++) {
                ctx->Bl.breakpoints[i9] = x[i9];
            }

            Bl_degree = cfg.SplineDegree;
        }

        coder::b_linspace(cfg.NDiscr, r);
        y.set_size(1, r.size(1));
        d_loop_ub = r.size(1);
        c_scalarLB = r.size(1) & -2;
        c_vectorUB = c_scalarLB - 2;
        for (i5 = 0; i5 <= c_vectorUB; i5 += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&r[i5]);
            _mm_storeu_pd(&y[i5], _mm_mul_pd(_mm_set1_pd(3.1415926535897931), r3));
        }

        for (i5 = c_scalarLB; i5 < d_loop_ub; i5++) {
            y[i5] = 3.1415926535897931 * r[i5];
        }

        i6 = y.size(1);
        for (int c_k = 0; c_k < i6; c_k++) {
            y[c_k] = std::cos(y[c_k]);
        }

        ctx->u_vec.set_size(1, y.size(1));
        f_loop_ub = y.size(1);
        d_scalarLB = y.size(1) & -2;
        d_vectorUB = d_scalarLB - 2;
        for (i8 = 0; i8 <= d_vectorUB; i8 += 2) {
            __m128d r5;
            __m128d r6;
            r5 = _mm_loadu_pd(&y[i8]);
            r6 = _mm_set1_pd(0.5);
            _mm_storeu_pd(&ctx->u_vec[i8], _mm_add_pd(_mm_mul_pd(r5, r6), r6));
        }

        for (i8 = d_scalarLB; i8 < f_loop_ub; i8++) {
            ctx->u_vec[i8] = y[i8] * 0.5 + 0.5;
        }

        //  n, bspline_n
        BasisVal.set_size(ctx->u_vec.size(1), Bl_ncoeff);
        BasisValD.set_size(ctx->u_vec.size(1), Bl_ncoeff);
        BasisValDD.set_size(ctx->u_vec.size(1), Bl_ncoeff);
        unusedU0.set_size(ctx->u_vec.size(1), Bl_ncoeff);
        ctx->BasisIntegr.set_size(Bl_ncoeff);
        for (int i10 = 0; i10 < Bl_ncoeff; i10++) {
            int h_loop_ub;
            int i_loop_ub;
            int j_loop_ub;
            int k_loop_ub;
            h_loop_ub = ctx->u_vec.size(1);
            for (int i11 = 0; i11 < h_loop_ub; i11++) {
                BasisVal[i11 + BasisVal.size(0) * i10] = 0.0;
            }

            i_loop_ub = ctx->u_vec.size(1);
            for (int i12 = 0; i12 < i_loop_ub; i12++) {
                BasisValD[i12 + BasisValD.size(0) * i10] = 0.0;
            }

            j_loop_ub = ctx->u_vec.size(1);
            for (int i13 = 0; i13 < j_loop_ub; i13++) {
                BasisValDD[i13 + BasisValDD.size(0) * i10] = 0.0;
            }

            k_loop_ub = ctx->u_vec.size(1);
            for (int i14 = 0; i14 < k_loop_ub; i14++) {
                unusedU0[i14 + unusedU0.size(0) * i10] = 0.0;
            }

            ctx->BasisIntegr[i10] = 0.0;
        }

        // ,
        c_bspline_base_eval(&Bl_handle, ctx->u_vec.size(1), &ctx->u_vec[0], &BasisVal[0],
                            &BasisValD[0], &BasisValDD[0], &unusedU0[0], &(ctx->BasisIntegr.data())
                            [0]);
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
        ctx->Bl.handle = Bl_handle;
        ctx->Bl.degree = Bl_degree;
        ctx->errcode = FeedoptPlanError_Success;
        ctx->jmax_increase_count = 0;
        ctx->zero_start = false;
        ctx->zero_end = false;
        ctx->BasisVal.set_size(BasisVal.size(0), BasisVal.size(1));
        l_loop_ub = BasisVal.size(1);
        for (int i15 = 0; i15 < l_loop_ub; i15++) {
            int m_loop_ub;
            m_loop_ub = BasisVal.size(0);
            for (int i16 = 0; i16 < m_loop_ub; i16++) {
                ctx->BasisVal[i16 + ctx->BasisVal.size(0) * i15] = BasisVal[i16 + BasisVal.size(0) *
                    i15];
            }
        }

        ctx->BasisValD.set_size(BasisValD.size(0), BasisValD.size(1));
        n_loop_ub = BasisValD.size(1);
        for (int i17 = 0; i17 < n_loop_ub; i17++) {
            int o_loop_ub;
            o_loop_ub = BasisValD.size(0);
            for (int i18 = 0; i18 < o_loop_ub; i18++) {
                ctx->BasisValD[i18 + ctx->BasisValD.size(0) * i17] = BasisValD[i18 + BasisValD.size
                    (0) * i17];
            }
        }

        ctx->BasisValDD.set_size(BasisValDD.size(0), BasisValDD.size(1));
        p_loop_ub = BasisValDD.size(1);
        for (int i19 = 0; i19 < p_loop_ub; i19++) {
            int q_loop_ub;
            q_loop_ub = BasisValDD.size(0);
            for (int i20 = 0; i20 < q_loop_ub; i20++) {
                ctx->BasisValDD[i20 + ctx->BasisValDD.size(0) * i19] = BasisValDD[i20 +
                    BasisValDD.size(0) * i19];
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
        static const char b_cv1[7]{
            'T', 'r', 'a', 'n', 's', 'P', '5'
        };

        static const char b_cv2[6]{
            'S', 'p', 'l', 'i', 'n', 'e'
        };

        static const char b_cv[5]{
            'H', 'e', 'l', 'i', 'x'
        };

        coder::rtString formatSpec;
        double dv[3][6];
        double P0[3];
        double P1[3];
        double b_validatedHoleFilling_idx_0;
        double validatedHoleFilling_f2;
        double validatedHoleFilling_idx_0;
        int argC_size[2];
        int loop_ub;
        int varargin_1_size_idx_1;
        char b_varargin_1_data[10];
        char varargin_2_data[10];
        char argC_data[9];
        char varargin_1_data[9];
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

        if (0 <= varargin_1_size_idx_1 - 1) {
            std::memcpy(&varargin_2_data[0], &varargin_1_data[0], varargin_1_size_idx_1 * sizeof
                        (char));
        }

        varargin_2_data[varargin_1_size_idx_1] = '\x00';
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

        b_EvalCurvStruct(&ctx->q_splines, S->Type, S->P0, S->P1, S->HelixCenter, S->evec, S->theta,
                         S->pitch, S->CoeffP5, S->sp_index, S->b_param, P0);
        b_EvalCurvStruct(&ctx->q_splines, S->Type, S->P0, S->P1, S->HelixCenter, S->evec, S->theta,
                         S->pitch, S->CoeffP5, S->sp_index, S->a_param, S->b_param, P1);
        printf("%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n", "P", P0[0], P0[1], P0[2], P1[0], P1[1],
               P1[2]);
        fflush(stdout);
        validatedHoleFilling_f2 = LengthCurv(&ctx->q_splines, ctx->cfg.NGridLengthSpline, S->Type,
            S->P0, S->P1, S->HelixCenter, S->evec, S->theta, S->pitch, S->CoeffP5, S->sp_index,
            S->a_param, S->b_param);
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
        loop_ub = argC_size[1];
        if (0 <= loop_ub - 1) {
            std::memcpy(&b_varargin_1_data[0], &argC_data[0], loop_ub * sizeof(char));
        }

        b_varargin_1_data[argC_size[1]] = '\x00';
        printf("ZSpdMode: %s\n", &b_varargin_1_data[0]);
        fflush(stdout);
        printf("FeedRate: %.2f\n", S->FeedRate);
        fflush(stdout);
        if (S->UseConstJerk) {
            CalcZeroStartConstraints(&ctx->q_splines, S->Type, S->P0, S->P1, S->HelixCenter, S->evec,
                S->theta, S->pitch, S->CoeffP5, S->sp_index, S->UseConstJerk, S->ConstJerk,
                S->a_param, S->b_param, 1.0, &validatedHoleFilling_idx_0,
                &b_validatedHoleFilling_idx_0);
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
        double b_ukp1;
        double qk;
        double ukp1;
        double unusedU0;
        double unusedU1;
        double unusedU2;
        double y;
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
                     1.0, state->dt, &unusedU1, &y, &unusedU2);
            y = std::sqrt(y);
            sqrt_calls++;
            sqrt_calls++;
            Trest = 2.0 * (1.0 - state->u) / (y + std::sqrt(qk));
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
        double tmp_data[13];
        int b_loop_ub;
        int i;
        int i1;
        int i2;
        int loop_ub;
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
    //                double n
    //                ::coder::array<double, 2U> &y
    // Return Type  : void
    //
    namespace coder
    {
        void linspace(double d1, double d2, double n, ::coder::array<double, 2U> &y)
        {
            if (!isInitialized_sinspace) {
                sinspace_initialize();
            }

            if (n < 0.0) {
                y.set_size(1, 0);
            } else {
                double d;
                d = std::floor(n);
                y.set_size(1, (static_cast<int>(d)));
                if (static_cast<int>(d) >= 1) {
                    int y_tmp;
                    y_tmp = static_cast<int>(d) - 1;
                    y[static_cast<int>(d) - 1] = d2;
                    if (y.size(1) >= 2) {
                        y[0] = d1;
                        if (y.size(1) >= 3) {
                            if ((d1 == -d2) && (static_cast<int>(d) > 2)) {
                                for (int k = 2; k <= y_tmp; k++) {
                                    y[k - 1] = d2 * (static_cast<double>(((k << 1) - static_cast<int>
                                                       (d)) - 1) / (static_cast<double>(static_cast<
                                                       int>(d)) - 1.0));
                                }

                                if ((static_cast<int>(d) & 1) == 1) {
                                    y[static_cast<int>(d) >> 1] = 0.0;
                                }
                            } else if (((d1 < 0.0) != (d2 < 0.0)) && ((std::abs(d1) >
                                         8.9884656743115785E+307) || (std::abs(d2) >
                                         8.9884656743115785E+307))) {
                                double delta1;
                                double delta2;
                                int i1;
                                delta1 = d1 / (static_cast<double>(y.size(1)) - 1.0);
                                delta2 = d2 / (static_cast<double>(y.size(1)) - 1.0);
                                i1 = y.size(1);
                                for (int c_k = 0; c_k <= i1 - 3; c_k++) {
                                    y[c_k + 1] = (d1 + delta2 * (static_cast<double>(c_k) + 1.0)) -
                                        delta1 * (static_cast<double>(c_k) + 1.0);
                                }
                            } else {
                                double delta1;
                                int i;
                                delta1 = (d2 - d1) / (static_cast<double>(y.size(1)) - 1.0);
                                i = y.size(1);
                                for (int b_k = 0; b_k <= i - 3; b_k++) {
                                    y[b_k + 1] = d1 + (static_cast<double>(b_k) + 1.0) * delta1;
                                }
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
        //                ::coder::array<double, 2U> &x
        // Return Type  : void
        //
    }

    void sinspace(double x0, double x1, int N, ::coder::array<double, 2U> &x)
    {
        ::coder::array<double, 2U> r;
        ::coder::array<double, 2U> y;
        double b;
        int b_loop_ub;
        int b_scalarLB;
        int b_vectorUB;
        int i;
        int i1;
        int i2;
        int loop_ub;
        int scalarLB;
        int vectorUB;
        if (!isInitialized_sinspace) {
            sinspace_initialize();
        }

        coder::b_linspace(N, r);
        y.set_size(1, r.size(1));
        loop_ub = r.size(1);
        scalarLB = r.size(1) & -2;
        vectorUB = scalarLB - 2;
        for (i = 0; i <= vectorUB; i += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&r[i]);
            _mm_storeu_pd(&y[i], _mm_mul_pd(_mm_set1_pd(3.1415926535897931), r1));
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
        b_scalarLB = y.size(1) & -2;
        b_vectorUB = b_scalarLB - 2;
        for (i2 = 0; i2 <= b_vectorUB; i2 += 2) {
            __m128d r2;
            __m128d r3;
            r2 = _mm_loadu_pd(&y[i2]);
            r3 = _mm_set1_pd(0.5);
            _mm_storeu_pd(&x[i2], _mm_add_pd(_mm_mul_pd(_mm_add_pd(_mm_mul_pd(r2, r3), r3),
                            _mm_set1_pd(b)), _mm_set1_pd(x0)));
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
        sin_calls = 0.0;
        cos_calls = 0.0;
        sqrt_calls = 0.0;
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
