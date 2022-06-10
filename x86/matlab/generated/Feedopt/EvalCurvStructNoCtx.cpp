//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStructNoCtx.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

// Include Files
#include "EvalCurvStructNoCtx.h"
#include "EvalHelix.h"
#include "EvalLine.h"
#include "EvalTransP5.h"
#include "bspline_eval.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>
#include <stdio.h>

// Variable Definitions
namespace ocn {
static const char cv[30]{'U', 'n', 'k', 'n', 'o', 'w', 'n', ' ', 'C',  'u',
                         'r', 'v', 'e', ' ', 'T', 'y', 'p', 'e', ' ',  'f',
                         'o', 'r', ' ', 'E', 'v', 'a', 'l', '.', '\\', 'n'};

}

// Function Definitions
//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : int cfg_NumberAxis
//                int cfg_NCart
//                int cfg_NRot
//                const int cfg_indCart_data[]
//                int cfg_indCart_size
//                const int cfg_indRot_data[]
//                int cfg_indRot_size
//                const int cfg_indTot_data[]
//                int cfg_indTot_size
//                CurveType curv_Info_Type
//                const double curv_R0[6]
//                const double curv_R1[6]
//                const double curv_CorrectedHelixCenter[3]
//                const double curv_evec[3]
//                double curv_theta
//                double curv_pitch
//                const ::coder::array<double, 2U> &curv_CoeffP5
//                double curv_a_param
//                double curv_b_param
//                const CurvStruct *spline
//                double u_vec
//                ::coder::array<double, 1U> &r0D
// Return Type  : void
//
namespace ocn {
void EvalCurvStructNoCtx(int cfg_NumberAxis, int cfg_NCart, int cfg_NRot,
                         const int cfg_indCart_data[], int cfg_indCart_size,
                         const int cfg_indRot_data[], int cfg_indRot_size,
                         const int cfg_indTot_data[], int cfg_indTot_size, CurveType curv_Info_Type,
                         const double curv_R0[6], const double curv_R1[6],
                         const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                         double curv_theta, double curv_pitch,
                         const ::coder::array<double, 2U> &curv_CoeffP5, double curv_a_param,
                         double curv_b_param, const CurvStruct *spline, double u_vec,
                         ::coder::array<double, 1U> &r0D)
{
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    double b_tmp_data[6];
    double c_tmp_data[6];
    double d_tmp_data[6];
    double r0D_data[6];
    double r1D_data[6];
    double r2D_data[6];
    double r3D_data[6];
    double tmp_data[6];
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double d;
    double d1;
    double d2;
    double u_vec_tilda;
    int e_tmp_data[3];
    int b_tmp_size;
    int c_tmp_size;
    int d_tmp_size;
    int r0D_size;
    int r1D_size;
    int r2D_size;
    int r3D_size;
    int tmp_size;
    char message[30];
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:6' if any( u_vec - 1.0 > 10 * eps )
    if (u_vec - 1.0 > 2.2204460492503131E-15) {
        double unnamed_idx_0;
        // 'EvalCurvStructNoCtx:7' u_vec( u_vec > 1.0 ) = 1.0;
        unnamed_idx_0 = u_vec;
        if (u_vec > 1.0) {
            unnamed_idx_0 = 1.0;
        }
        u_vec = unnamed_idx_0;
        // 'EvalCurvStructNoCtx:7' printMsg( "Error : u_vec > 1\n" );
        //  printMsg : Print erro message according to the coder.target.
        // 'EvalCurvStructNoCtx:58' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:59' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:61' else
        // 'EvalCurvStructNoCtx:62' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec > 1\n");
        fflush(stdout);
    }
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    if (u_vec < 0.0) {
        // 'EvalCurvStructNoCtx:11' u_vec( u_vec < 0.0 ) = 0.0;
        u_vec = 0.0;
        // 'EvalCurvStructNoCtx:11' printMsg( "Error : u_vec < 0\n" );
        //  printMsg : Print erro message according to the coder.target.
        // 'EvalCurvStructNoCtx:58' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:59' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:61' else
        // 'EvalCurvStructNoCtx:62' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec < 0\n");
        fflush(stdout);
    }
    //
    // 'EvalCurvStructNoCtx:15' Type  = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N   = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M   = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:19' r0D = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:20' r1D = r0D;
    // 'EvalCurvStructNoCtx:21' r2D = r0D;
    // 'EvalCurvStructNoCtx:22' r3D = r0D;
    // 'EvalCurvStructNoCtx:24' a = curv.a_param;
    // 'EvalCurvStructNoCtx:25' b = curv.b_param;
    // 'EvalCurvStructNoCtx:27' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv_a_param * u_vec + curv_b_param;
    // 'EvalCurvStructNoCtx:29' indC   = cfg.indCart;
    // 'EvalCurvStructNoCtx:30' indR   = cfg.indRot;
    // 'EvalCurvStructNoCtx:31' indTot = cfg.indTot;
    // 'EvalCurvStructNoCtx:33' switch Type
    switch (curv_Info_Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:34' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:35' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, indTot );
        EvalLine(curv_R0, curv_R1, u_vec_tilda, cfg_indTot_data, cfg_indTot_size, r0D_data,
                 &r0D_size, r1D_data, &r1D_size, r2D_data, &r2D_size, r3D_data, &r3D_size);
        r0D.set_size(r0D_size);
        for (int i2{0}; i2 < r0D_size; i2++) {
            r0D[i2] = r0D_data[i2];
        }
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:36' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:37' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int i4;
            int scalarLB;
            int vectorUB;
            //  Only rotation
            // 'EvalCurvStructNoCtx:38' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:39'                 EvalHelix( curv, u_vec_tilda,
            // indC );
            EvalHelix(curv_R0, curv_CorrectedHelixCenter, curv_evec, curv_theta, curv_pitch,
                      u_vec_tilda, cfg_indCart_data, cfg_indCart_size, dv, dv1, dv2, dv3);
            scalarLB = (cfg_indCart_size / 4) << 2;
            vectorUB = scalarLB - 4;
            for (i4 = 0; i4 <= vectorUB; i4 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i4 = scalarLB; i4 < cfg_indCart_size; i4++) {
                e_tmp_data[i4] = cfg_indCart_data[i4] - 1;
            }
            for (int i5{0}; i5 < cfg_indCart_size; i5++) {
                r0D[e_tmp_data[i5]] = dv[i5];
            }
        } else if (cfg_NRot > 0) {
            // 'EvalCurvStructNoCtx:40' elseif( cfg.NRot > 0 )
            //  Only cartesian
            // 'EvalCurvStructNoCtx:41' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:42'                 EvalLine( curv, u_vec_tilda, indR
            // );
            EvalLine(curv_R0, curv_R1, u_vec_tilda, cfg_indRot_data, cfg_indRot_size, tmp_data,
                     &tmp_size, b_tmp_data, &b_tmp_size, c_tmp_data, &c_tmp_size, d_tmp_data,
                     &d_tmp_size);
            for (int i3{0}; i3 < tmp_size; i3++) {
                r0D[cfg_indRot_data[i3] - 1] = tmp_data[i3];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:44' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:45' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda );
        EvalTransP5(curv_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int i10;
        int loop_ub;
        // 'EvalCurvStructNoCtx:46' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:47' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        //  EvalBSpline
        //
        //  INPUT
        //  spline        : struct : Spline structure
        //  u_vec         :    1xn : Vector for evaluation of the curv
        //
        //  OUTPUT
        //  r0D           :   nDxn : The evaluated B spline at u\_vec points
        //  r1D           :   nDxn : 1rst order parametric derivative for the B spline at u\_vec
        //  points r2D           :   nDxn : 2nd order parametric derivative for the B spline at
        //  u\_vec points r3D           :   nDxn : 3rd order parametric derivative for the B spline
        //  at u\_vec points
        // 'EvalBSpline:14' sp = spline.sp;
        // 'EvalBSpline:15' N  = length( u_vec );
        // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
        // 'EvalBSpline:18' r0D = zeros( M, N );
        r0D.set_size(spline->sp.coeff.size(0));
        loop_ub = spline->sp.coeff.size(0);
        for (int i6{0}; i6 < loop_ub; i6++) {
            r0D[i6] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        b_loop_ub = spline->sp.coeff.size(0);
        for (int i7{0}; i7 < b_loop_ub; i7++) {
            r1D[i7] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        c_loop_ub = spline->sp.coeff.size(0);
        for (int i8{0}; i8 < c_loop_ub; i8++) {
            r2D[i8] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        d_loop_ub = spline->sp.coeff.size(0);
        for (int i9{0}; i9 < d_loop_ub; i9++) {
            r3D[i9] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i10 = spline->sp.coeff.size(0);
        for (int j{0}; j < i10; j++) {
            int e_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0D[j] = u_vec_tilda;
            e_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i11{0}; i11 < e_loop_ub; i11++) {
                b_spline[i11] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i11];
            }
            bspline_eval(spline->sp.Bl.handle, b_spline, &r0D[j], &d, &d1, &d2);
            r3D[j] = d2;
            r2D[j] = d1;
            r1D[j] = d;
            // 'bspline_eval_vec:10' x(k)    = xk;
            // 'bspline_eval_vec:11' xd(k)   = xdk;
            // 'bspline_eval_vec:12' xdd(k)  = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:48' otherwise
        // 'EvalCurvStructNoCtx:49' c_assert( false, 'Unknown Curve Type for Eval.\n' );
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i1{0}; i1 < 30; i1++) {
            message[i1] = cv[i1];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStructNoCtx:52' r1D = a   .* r1D;
    // 'EvalCurvStructNoCtx:53' r2D = a^2 .* r2D;
    // 'EvalCurvStructNoCtx:54' r3D = a^3 .* r3D;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : int cfg_NumberAxis
//                int cfg_NCart
//                int cfg_NRot
//                const int cfg_indCart_data[]
//                int cfg_indCart_size
//                const int cfg_indRot_data[]
//                int cfg_indRot_size
//                const int cfg_indTot_data[]
//                int cfg_indTot_size
//                CurveType curv_Info_Type
//                const double curv_R0[6]
//                const double curv_R1[6]
//                const double curv_CorrectedHelixCenter[3]
//                const double curv_evec[3]
//                double curv_theta
//                double curv_pitch
//                const ::coder::array<double, 2U> &curv_CoeffP5
//                double curv_a_param
//                double curv_b_param
//                const CurvStruct *spline
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void EvalCurvStructNoCtx(int cfg_NumberAxis, int cfg_NCart, int cfg_NRot,
                         const int cfg_indCart_data[], int cfg_indCart_size,
                         const int cfg_indRot_data[], int cfg_indRot_size,
                         const int cfg_indTot_data[], int cfg_indTot_size, CurveType curv_Info_Type,
                         const double curv_R0[6], const double curv_R1[6],
                         const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                         double curv_theta, double curv_pitch,
                         const ::coder::array<double, 2U> &curv_CoeffP5, double curv_a_param,
                         double curv_b_param, const CurvStruct *spline,
                         ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                         ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D)
{
    ::coder::array<double, 2U> b_spline;
    double b_tmp_data[6];
    double c_tmp_data[6];
    double d_tmp_data[6];
    double r0D_data[6];
    double r1D_data[6];
    double r2D_data[6];
    double r3D_data[6];
    double tmp_data[6];
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double b_c;
    double c;
    double d;
    double d1;
    double d2;
    double u_vec_tilda;
    int e_tmp_data[3];
    int b_loop_ub;
    int b_scalarLB;
    int b_tmp_size;
    int c_scalarLB;
    int c_tmp_size;
    int d_loop_ub;
    int d_tmp_size;
    int d_vectorUB;
    int f_vectorUB;
    int i14;
    int i19;
    int i4;
    int loop_ub;
    int r0D_size;
    int r1D_size;
    int r2D_size;
    int r3D_size;
    int scalarLB;
    int tmp_size;
    int vectorUB;
    char message[30];
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:6' if any( u_vec - 1.0 > 10 * eps )
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    //
    // 'EvalCurvStructNoCtx:15' Type  = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N   = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M   = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:19' r0D = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:20' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:22' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:24' a = curv.a_param;
    // 'EvalCurvStructNoCtx:25' b = curv.b_param;
    // 'EvalCurvStructNoCtx:27' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv_a_param + curv_b_param;
    // 'EvalCurvStructNoCtx:29' indC   = cfg.indCart;
    // 'EvalCurvStructNoCtx:30' indR   = cfg.indRot;
    // 'EvalCurvStructNoCtx:31' indTot = cfg.indTot;
    // 'EvalCurvStructNoCtx:33' switch Type
    switch (curv_Info_Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:34' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:35' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, indTot );
        EvalLine(curv_R0, curv_R1, u_vec_tilda, cfg_indTot_data, cfg_indTot_size, r0D_data,
                 &r0D_size, r1D_data, &r1D_size, r2D_data, &r2D_size, r3D_data, &r3D_size);
        r0D.set_size(r0D_size);
        for (int i2{0}; i2 < r0D_size; i2++) {
            r0D[i2] = r0D_data[i2];
        }
        r1D.set_size(r1D_size);
        for (int i3{0}; i3 < r1D_size; i3++) {
            r1D[i3] = r1D_data[i3];
        }
        r2D.set_size(r2D_size);
        for (int i7{0}; i7 < r2D_size; i7++) {
            r2D[i7] = r2D_data[i7];
        }
        r3D.set_size(r3D_size);
        for (int i9{0}; i9 < r3D_size; i9++) {
            r3D[i9] = r3D_data[i9];
        }
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:36' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:37' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int b_vectorUB;
            int c_vectorUB;
            int e_vectorUB;
            int g_vectorUB;
            int i13;
            int i17;
            int i22;
            int i6;
            int scalarLB_tmp;
            //  Only rotation
            // 'EvalCurvStructNoCtx:38' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:39'                 EvalHelix( curv, u_vec_tilda,
            // indC );
            EvalHelix(curv_R0, curv_CorrectedHelixCenter, curv_evec, curv_theta, curv_pitch,
                      u_vec_tilda, cfg_indCart_data, cfg_indCart_size, dv, dv1, dv2, dv3);
            scalarLB_tmp = (cfg_indCart_size / 4) << 2;
            b_vectorUB = scalarLB_tmp - 4;
            for (i6 = 0; i6 <= b_vectorUB; i6 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i6 = scalarLB_tmp; i6 < cfg_indCart_size; i6++) {
                e_tmp_data[i6] = cfg_indCart_data[i6] - 1;
            }
            for (int i11{0}; i11 < cfg_indCart_size; i11++) {
                r0D[e_tmp_data[i11]] = dv[i11];
            }
            c_vectorUB = scalarLB_tmp - 4;
            for (i13 = 0; i13 <= c_vectorUB; i13 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i13 = scalarLB_tmp; i13 < cfg_indCart_size; i13++) {
                e_tmp_data[i13] = cfg_indCart_data[i13] - 1;
            }
            for (int i16{0}; i16 < cfg_indCart_size; i16++) {
                r1D[e_tmp_data[i16]] = dv1[i16];
            }
            e_vectorUB = scalarLB_tmp - 4;
            for (i17 = 0; i17 <= e_vectorUB; i17 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i17 = scalarLB_tmp; i17 < cfg_indCart_size; i17++) {
                e_tmp_data[i17] = cfg_indCart_data[i17] - 1;
            }
            for (int i20{0}; i20 < cfg_indCart_size; i20++) {
                r2D[e_tmp_data[i20]] = dv2[i20];
            }
            g_vectorUB = scalarLB_tmp - 4;
            for (i22 = 0; i22 <= g_vectorUB; i22 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i22 = scalarLB_tmp; i22 < cfg_indCart_size; i22++) {
                e_tmp_data[i22] = cfg_indCart_data[i22] - 1;
            }
            for (int i23{0}; i23 < cfg_indCart_size; i23++) {
                r3D[e_tmp_data[i23]] = dv3[i23];
            }
        } else if (cfg_NRot > 0) {
            // 'EvalCurvStructNoCtx:40' elseif( cfg.NRot > 0 )
            //  Only cartesian
            // 'EvalCurvStructNoCtx:41' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:42'                 EvalLine( curv, u_vec_tilda, indR
            // );
            EvalLine(curv_R0, curv_R1, u_vec_tilda, cfg_indRot_data, cfg_indRot_size, tmp_data,
                     &tmp_size, b_tmp_data, &b_tmp_size, c_tmp_data, &c_tmp_size, d_tmp_data,
                     &d_tmp_size);
            for (int i5{0}; i5 < tmp_size; i5++) {
                r0D[cfg_indRot_data[i5] - 1] = tmp_data[i5];
            }
            for (int i8{0}; i8 < b_tmp_size; i8++) {
                r1D[cfg_indRot_data[i8] - 1] = b_tmp_data[i8];
            }
            for (int i10{0}; i10 < c_tmp_size; i10++) {
                r2D[cfg_indRot_data[i10] - 1] = c_tmp_data[i10];
            }
            for (int i12{0}; i12 < d_tmp_size; i12++) {
                r3D[cfg_indRot_data[i12] - 1] = d_tmp_data[i12];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:44' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:45' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda );
        EvalTransP5(curv_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int c_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int i25;
        // 'EvalCurvStructNoCtx:46' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:47' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        //  EvalBSpline
        //
        //  INPUT
        //  spline        : struct : Spline structure
        //  u_vec         :    1xn : Vector for evaluation of the curv
        //
        //  OUTPUT
        //  r0D           :   nDxn : The evaluated B spline at u\_vec points
        //  r1D           :   nDxn : 1rst order parametric derivative for the B spline at u\_vec
        //  points r2D           :   nDxn : 2nd order parametric derivative for the B spline at
        //  u\_vec points r3D           :   nDxn : 3rd order parametric derivative for the B spline
        //  at u\_vec points
        // 'EvalBSpline:14' sp = spline.sp;
        // 'EvalBSpline:15' N  = length( u_vec );
        // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
        // 'EvalBSpline:18' r0D = zeros( M, N );
        r0D.set_size(spline->sp.coeff.size(0));
        c_loop_ub = spline->sp.coeff.size(0);
        for (int i15{0}; i15 < c_loop_ub; i15++) {
            r0D[i15] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        e_loop_ub = spline->sp.coeff.size(0);
        for (int i18{0}; i18 < e_loop_ub; i18++) {
            r1D[i18] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        f_loop_ub = spline->sp.coeff.size(0);
        for (int i21{0}; i21 < f_loop_ub; i21++) {
            r2D[i21] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        g_loop_ub = spline->sp.coeff.size(0);
        for (int i24{0}; i24 < g_loop_ub; i24++) {
            r3D[i24] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i25 = spline->sp.coeff.size(0);
        for (int j{0}; j < i25; j++) {
            int h_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0D[j] = u_vec_tilda;
            h_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i26{0}; i26 < h_loop_ub; i26++) {
                b_spline[i26] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i26];
            }
            bspline_eval(spline->sp.Bl.handle, b_spline, &r0D[j], &d, &d1, &d2);
            r3D[j] = d2;
            r2D[j] = d1;
            r1D[j] = d;
            // 'bspline_eval_vec:10' x(k)    = xk;
            // 'bspline_eval_vec:11' xd(k)   = xdk;
            // 'bspline_eval_vec:12' xdd(k)  = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:48' otherwise
        // 'EvalCurvStructNoCtx:49' c_assert( false, 'Unknown Curve Type for Eval.\n' );
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i1{0}; i1 < 30; i1++) {
            message[i1] = cv[i1];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStructNoCtx:52' r1D = a   .* r1D;
    loop_ub = r1D.size(0);
    scalarLB = (r1D.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i4 = 0; i4 <= vectorUB; i4 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&r1D[i4]);
        _mm_storeu_pd(&r1D[i4], _mm_mul_pd(_mm_set1_pd(curv_a_param), r));
    }
    for (i4 = scalarLB; i4 < loop_ub; i4++) {
        r1D[i4] = curv_a_param * r1D[i4];
    }
    // 'EvalCurvStructNoCtx:53' r2D = a^2 .* r2D;
    c = curv_a_param * curv_a_param;
    b_loop_ub = r2D.size(0);
    b_scalarLB = (r2D.size(0) / 2) << 1;
    d_vectorUB = b_scalarLB - 2;
    for (i14 = 0; i14 <= d_vectorUB; i14 += 2) {
        __m128d r1;
        r1 = _mm_loadu_pd(&r2D[i14]);
        _mm_storeu_pd(&r2D[i14], _mm_mul_pd(_mm_set1_pd(c), r1));
    }
    for (i14 = b_scalarLB; i14 < b_loop_ub; i14++) {
        r2D[i14] = c * r2D[i14];
    }
    // 'EvalCurvStructNoCtx:54' r3D = a^3 .* r3D;
    b_c = std::pow(curv_a_param, 3.0);
    d_loop_ub = r3D.size(0);
    c_scalarLB = (r3D.size(0) / 2) << 1;
    f_vectorUB = c_scalarLB - 2;
    for (i19 = 0; i19 <= f_vectorUB; i19 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r3D[i19]);
        _mm_storeu_pd(&r3D[i19], _mm_mul_pd(_mm_set1_pd(b_c), r2));
    }
    for (i19 = c_scalarLB; i19 < d_loop_ub; i19++) {
        r3D[i19] = b_c * r3D[i19];
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : int cfg_NumberAxis
//                int cfg_NCart
//                int cfg_NRot
//                const int cfg_indCart_data[]
//                int cfg_indCart_size
//                const int cfg_indRot_data[]
//                int cfg_indRot_size
//                const int cfg_indTot_data[]
//                int cfg_indTot_size
//                CurveType curv_Info_Type
//                const double curv_R0[6]
//                const double curv_R1[6]
//                const double curv_CorrectedHelixCenter[3]
//                const double curv_evec[3]
//                double curv_theta
//                double curv_pitch
//                const ::coder::array<double, 2U> &curv_CoeffP5
//                double curv_a_param
//                double curv_b_param
//                const CurvStruct *spline
//                ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void EvalCurvStructNoCtx(int cfg_NumberAxis, int cfg_NCart, int cfg_NRot,
                         const int cfg_indCart_data[], int cfg_indCart_size,
                         const int cfg_indRot_data[], int cfg_indRot_size,
                         const int cfg_indTot_data[], int cfg_indTot_size, CurveType curv_Info_Type,
                         const double curv_R0[6], const double curv_R1[6],
                         const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                         double curv_theta, double curv_pitch,
                         const ::coder::array<double, 2U> &curv_CoeffP5, double curv_a_param,
                         double curv_b_param, const CurvStruct *spline,
                         ::coder::array<double, 2U> &u_vec, ::coder::array<double, 2U> &r0D,
                         ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                         ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> b_r0D;
    ::coder::array<double, 2U> b_r1D;
    ::coder::array<double, 2U> b_r2D;
    ::coder::array<double, 2U> b_r3D;
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r12;
    ::coder::array<double, 2U> r13;
    ::coder::array<double, 2U> r14;
    ::coder::array<double, 2U> r15;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> r5;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> r7;
    ::coder::array<double, 2U> r8;
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<bool, 2U> x;
    double b_c;
    double c;
    double d;
    double d1;
    double d2;
    int ab_loop_ub;
    int b_k;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int i10;
    int i_loop_ub;
    int k;
    int loop_ub;
    int p_loop_ub;
    int scalarLB;
    int vectorUB;
    char message[30];
    bool b_y;
    bool exitg1;
    bool y;
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:6' if any( u_vec - 1.0 > 10 * eps )
    x.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        x[i] = (u_vec[i] - 1.0 > 2.2204460492503131E-15);
    }
    y = false;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(1) - 1)) {
        if (x[k]) {
            y = true;
            exitg1 = true;
        } else {
            k++;
        }
    }
    if (y) {
        int end;
        // 'EvalCurvStructNoCtx:7' u_vec( u_vec > 1.0 ) = 1.0;
        end = u_vec.size(1);
        for (int b_i{0}; b_i < end; b_i++) {
            if (u_vec[b_i] > 1.0) {
                u_vec[b_i] = 1.0;
            }
        }
        // 'EvalCurvStructNoCtx:7' printMsg( "Error : u_vec > 1\n" );
        //  printMsg : Print erro message according to the coder.target.
        // 'EvalCurvStructNoCtx:58' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:59' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:61' else
        // 'EvalCurvStructNoCtx:62' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec > 1\n");
        fflush(stdout);
    }
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    x.set_size(1, u_vec.size(1));
    b_loop_ub = u_vec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        x[i1] = (u_vec[i1] < 0.0);
    }
    b_y = false;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k <= x.size(1) - 1)) {
        if (x[b_k]) {
            b_y = true;
            exitg1 = true;
        } else {
            b_k++;
        }
    }
    if (b_y) {
        int b_end;
        // 'EvalCurvStructNoCtx:11' u_vec( u_vec < 0.0 ) = 0.0;
        b_end = u_vec.size(1);
        for (int c_i{0}; c_i < b_end; c_i++) {
            if (u_vec[c_i] < 0.0) {
                u_vec[c_i] = 0.0;
            }
        }
        // 'EvalCurvStructNoCtx:11' printMsg( "Error : u_vec < 0\n" );
        //  printMsg : Print erro message according to the coder.target.
        // 'EvalCurvStructNoCtx:58' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:59' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:61' else
        // 'EvalCurvStructNoCtx:62' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec < 0\n");
        fflush(stdout);
    }
    //
    // 'EvalCurvStructNoCtx:15' Type  = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N   = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M   = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:19' r0D = zeros( M, N );
    r0D.set_size(cfg_NumberAxis, u_vec.size(1));
    c_loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        for (int i3{0}; i3 < cfg_NumberAxis; i3++) {
            r0D[i3 + r0D.size(0) * i2] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:20' r1D = r0D;
    r1D.set_size(cfg_NumberAxis, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        for (int i5{0}; i5 < cfg_NumberAxis; i5++) {
            r1D[i5 + r1D.size(0) * i4] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:21' r2D = r0D;
    r2D.set_size(cfg_NumberAxis, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i6{0}; i6 < e_loop_ub; i6++) {
        for (int i7{0}; i7 < cfg_NumberAxis; i7++) {
            r2D[i7 + r2D.size(0) * i6] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:22' r3D = r0D;
    r3D.set_size(cfg_NumberAxis, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        for (int i9{0}; i9 < cfg_NumberAxis; i9++) {
            r3D[i9 + r3D.size(0) * i8] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:24' a = curv.a_param;
    // 'EvalCurvStructNoCtx:25' b = curv.b_param;
    // 'EvalCurvStructNoCtx:27' u_vec_tilda = a * u_vec + b;
    u_vec_tilda.set_size(1, u_vec.size(1));
    g_loop_ub = u_vec.size(1);
    scalarLB = (u_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i10 = 0; i10 <= vectorUB; i10 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&u_vec[i10]);
        _mm_storeu_pd(&u_vec_tilda[i10], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(curv_a_param), r),
                                                    _mm_set1_pd(curv_b_param)));
    }
    for (i10 = scalarLB; i10 < g_loop_ub; i10++) {
        u_vec_tilda[i10] = curv_a_param * u_vec[i10] + curv_b_param;
    }
    // 'EvalCurvStructNoCtx:29' indC   = cfg.indCart;
    // 'EvalCurvStructNoCtx:30' indR   = cfg.indRot;
    // 'EvalCurvStructNoCtx:31' indTot = cfg.indTot;
    // 'EvalCurvStructNoCtx:33' switch Type
    switch (curv_Info_Type) {
    case CurveType_Line: {
        int bb_loop_ub;
        int h_loop_ub;
        int l_loop_ub;
        int r_loop_ub;
        // 'EvalCurvStructNoCtx:34' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:35' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, indTot );
        EvalLine(curv_R0, curv_R1, u_vec_tilda, cfg_indTot_data, cfg_indTot_size, b_r0D, b_r1D,
                 b_r2D, b_r3D);
        r0D.set_size(b_r0D.size(0), b_r0D.size(1));
        h_loop_ub = b_r0D.size(1);
        for (int i12{0}; i12 < h_loop_ub; i12++) {
            int j_loop_ub;
            j_loop_ub = b_r0D.size(0);
            for (int i14{0}; i14 < j_loop_ub; i14++) {
                r0D[i14 + r0D.size(0) * i12] = b_r0D[i14 + b_r0D.size(0) * i12];
            }
        }
        r1D.set_size(b_r1D.size(0), b_r1D.size(1));
        l_loop_ub = b_r1D.size(1);
        for (int i16{0}; i16 < l_loop_ub; i16++) {
            int q_loop_ub;
            q_loop_ub = b_r1D.size(0);
            for (int i21{0}; i21 < q_loop_ub; i21++) {
                r1D[i21 + r1D.size(0) * i16] = b_r1D[i21 + b_r1D.size(0) * i16];
            }
        }
        r2D.set_size(b_r2D.size(0), b_r2D.size(1));
        r_loop_ub = b_r2D.size(1);
        for (int i22{0}; i22 < r_loop_ub; i22++) {
            int w_loop_ub;
            w_loop_ub = b_r2D.size(0);
            for (int i26{0}; i26 < w_loop_ub; i26++) {
                r2D[i26 + r2D.size(0) * i22] = b_r2D[i26 + b_r2D.size(0) * i22];
            }
        }
        r3D.set_size(b_r3D.size(0), b_r3D.size(1));
        bb_loop_ub = b_r3D.size(1);
        for (int i31{0}; i31 < bb_loop_ub; i31++) {
            int gb_loop_ub;
            gb_loop_ub = b_r3D.size(0);
            for (int i35{0}; i35 < gb_loop_ub; i35++) {
                r3D[i35 + r3D.size(0) * i31] = b_r3D[i35 + b_r3D.size(0) * i31];
            }
        }
    } break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:36' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:37' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int cb_loop_ub;
            int k_loop_ub;
            int o_loop_ub;
            int u_loop_ub;
            //  Only rotation
            // 'EvalCurvStructNoCtx:38' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:39'                 EvalHelix( curv, u_vec_tilda,
            // indC );
            EvalHelix(curv_R0, curv_CorrectedHelixCenter, curv_evec, curv_theta, curv_pitch,
                      u_vec_tilda, cfg_indCart_data, cfg_indCart_size, r1, r2, r3, r4);
            k_loop_ub = r1.size(1);
            for (int i15{0}; i15 < k_loop_ub; i15++) {
                r0D[(cfg_indCart_data[0] + r0D.size(0) * i15) - 1] = r1[3 * i15];
                r0D[(cfg_indCart_data[1] + r0D.size(0) * i15) - 1] = r1[3 * i15 + 1];
                r0D[(cfg_indCart_data[2] + r0D.size(0) * i15) - 1] = r1[3 * i15 + 2];
            }
            o_loop_ub = r2.size(1);
            for (int i18{0}; i18 < o_loop_ub; i18++) {
                r1D[(cfg_indCart_data[0] + r1D.size(0) * i18) - 1] = r2[3 * i18];
                r1D[(cfg_indCart_data[1] + r1D.size(0) * i18) - 1] = r2[3 * i18 + 1];
                r1D[(cfg_indCart_data[2] + r1D.size(0) * i18) - 1] = r2[3 * i18 + 2];
            }
            u_loop_ub = r3.size(1);
            for (int i25{0}; i25 < u_loop_ub; i25++) {
                r2D[(cfg_indCart_data[0] + r2D.size(0) * i25) - 1] = r3[3 * i25];
                r2D[(cfg_indCart_data[1] + r2D.size(0) * i25) - 1] = r3[3 * i25 + 1];
                r2D[(cfg_indCart_data[2] + r2D.size(0) * i25) - 1] = r3[3 * i25 + 2];
            }
            cb_loop_ub = r4.size(1);
            for (int i32{0}; i32 < cb_loop_ub; i32++) {
                r3D[(cfg_indCart_data[0] + r3D.size(0) * i32) - 1] = r4[3 * i32];
                r3D[(cfg_indCart_data[1] + r3D.size(0) * i32) - 1] = r4[3 * i32 + 1];
                r3D[(cfg_indCart_data[2] + r3D.size(0) * i32) - 1] = r4[3 * i32 + 2];
            }
        } else if (cfg_NRot > 0) {
            int db_loop_ub;
            int n_loop_ub;
            int s_loop_ub;
            int x_loop_ub;
            // 'EvalCurvStructNoCtx:40' elseif( cfg.NRot > 0 )
            //  Only cartesian
            // 'EvalCurvStructNoCtx:41' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:42'                 EvalLine( curv, u_vec_tilda, indR
            // );
            EvalLine(curv_R0, curv_R1, u_vec_tilda, cfg_indRot_data, cfg_indRot_size, r5, r6, r7,
                     r8);
            n_loop_ub = r5.size(1);
            for (int i17{0}; i17 < n_loop_ub; i17++) {
                int t_loop_ub;
                t_loop_ub = r5.size(0);
                for (int i24{0}; i24 < t_loop_ub; i24++) {
                    r0D[(cfg_indRot_data[i24] + r0D.size(0) * i17) - 1] =
                        r5[i24 + r5.size(0) * i17];
                }
            }
            s_loop_ub = r6.size(1);
            for (int i23{0}; i23 < s_loop_ub; i23++) {
                int y_loop_ub;
                y_loop_ub = r6.size(0);
                for (int i28{0}; i28 < y_loop_ub; i28++) {
                    r1D[(cfg_indRot_data[i28] + r1D.size(0) * i23) - 1] =
                        r6[i28 + r6.size(0) * i23];
                }
            }
            x_loop_ub = r7.size(1);
            for (int i27{0}; i27 < x_loop_ub; i27++) {
                int eb_loop_ub;
                eb_loop_ub = r7.size(0);
                for (int i34{0}; i34 < eb_loop_ub; i34++) {
                    r2D[(cfg_indRot_data[i34] + r2D.size(0) * i27) - 1] =
                        r7[i34 + r7.size(0) * i27];
                }
            }
            db_loop_ub = r8.size(1);
            for (int i33{0}; i33 < db_loop_ub; i33++) {
                int ib_loop_ub;
                ib_loop_ub = r8.size(0);
                for (int i38{0}; i38 < ib_loop_ub; i38++) {
                    r3D[(cfg_indRot_data[i38] + r3D.size(0) * i33) - 1] =
                        r8[i38 + r8.size(0) * i33];
                }
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:44' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:45' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda );
        EvalTransP5(curv_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int hb_loop_ub;
        int i44;
        int jb_loop_ub;
        int kb_loop_ub;
        int unnamed_idx_0;
        // 'EvalCurvStructNoCtx:46' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:47' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        //  EvalBSpline
        //
        //  INPUT
        //  spline        : struct : Spline structure
        //  u_vec         :    1xn : Vector for evaluation of the curv
        //
        //  OUTPUT
        //  r0D           :   nDxn : The evaluated B spline at u\_vec points
        //  r1D           :   nDxn : 1rst order parametric derivative for the B spline at u\_vec
        //  points r2D           :   nDxn : 2nd order parametric derivative for the B spline at
        //  u\_vec points r3D           :   nDxn : 3rd order parametric derivative for the B spline
        //  at u\_vec points
        // 'EvalBSpline:14' sp = spline.sp;
        // 'EvalBSpline:15' N  = length( u_vec );
        // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
        // 'EvalBSpline:18' r0D = zeros( M, N );
        unnamed_idx_0 = spline->sp.coeff.size(0);
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        hb_loop_ub = u_vec_tilda.size(1);
        for (int i37{0}; i37 < hb_loop_ub; i37++) {
            for (int i39{0}; i39 < unnamed_idx_0; i39++) {
                r1D[i39 + r1D.size(0) * i37] = 0.0;
            }
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        jb_loop_ub = u_vec_tilda.size(1);
        for (int i40{0}; i40 < jb_loop_ub; i40++) {
            for (int i41{0}; i41 < unnamed_idx_0; i41++) {
                r2D[i41 + r2D.size(0) * i40] = 0.0;
            }
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        kb_loop_ub = u_vec_tilda.size(1);
        for (int i42{0}; i42 < kb_loop_ub; i42++) {
            for (int i43{0}; i43 < unnamed_idx_0; i43++) {
                r3D[i43 + r3D.size(0) * i42] = 0.0;
            }
        }
        // 'EvalBSpline:20' for j = 1 : M
        i44 = spline->sp.coeff.size(0);
        r0D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        for (int j{0}; j < i44; j++) {
            int i49;
            int lb_loop_ub;
            int mb_loop_ub;
            int nb_loop_ub;
            int ob_loop_ub;
            int pb_loop_ub;
            int rb_loop_ub;
            int sb_loop_ub;
            int tb_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
            r12.set_size(1, u_vec_tilda.size(1));
            lb_loop_ub = u_vec_tilda.size(1);
            for (int i45{0}; i45 < lb_loop_ub; i45++) {
                r12[i45] = 0.0;
            }
            // 'bspline_eval_vec:4' xd      = zeros(size(u));
            r13.set_size(1, u_vec_tilda.size(1));
            mb_loop_ub = u_vec_tilda.size(1);
            for (int i46{0}; i46 < mb_loop_ub; i46++) {
                r13[i46] = 0.0;
            }
            // 'bspline_eval_vec:5' xdd     = zeros(size(u));
            r14.set_size(1, u_vec_tilda.size(1));
            nb_loop_ub = u_vec_tilda.size(1);
            for (int i47{0}; i47 < nb_loop_ub; i47++) {
                r14[i47] = 0.0;
            }
            // 'bspline_eval_vec:6' xddd    = zeros(size(u));
            r15.set_size(1, u_vec_tilda.size(1));
            ob_loop_ub = u_vec_tilda.size(1);
            for (int i48{0}; i48 < ob_loop_ub; i48++) {
                r15[i48] = 0.0;
            }
            // 'bspline_eval_vec:8' for k = 1:length(u)
            i49 = u_vec_tilda.size(1);
            for (int c_k{0}; c_k < i49; c_k++) {
                int qb_loop_ub;
                // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
                r12[c_k] = u_vec_tilda[c_k];
                qb_loop_ub = spline->sp.coeff.size(1);
                b_spline.set_size(1, spline->sp.coeff.size(1));
                for (int i52{0}; i52 < qb_loop_ub; i52++) {
                    b_spline[i52] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i52];
                }
                bspline_eval(spline->sp.Bl.handle, b_spline, &r12[c_k], &d, &d1, &d2);
                r15[c_k] = d2;
                r14[c_k] = d1;
                r13[c_k] = d;
                // 'bspline_eval_vec:10' x(k)    = xk;
                // 'bspline_eval_vec:11' xd(k)   = xdk;
                // 'bspline_eval_vec:12' xdd(k)  = xddk;
                // 'bspline_eval_vec:13' xddd(k) = xdddk;
            }
            pb_loop_ub = r12.size(1);
            for (int i50{0}; i50 < pb_loop_ub; i50++) {
                r0D[j + r0D.size(0) * i50] = r12[i50];
            }
            rb_loop_ub = r13.size(1);
            for (int i51{0}; i51 < rb_loop_ub; i51++) {
                r1D[j + r1D.size(0) * i51] = r13[i51];
            }
            sb_loop_ub = r14.size(1);
            for (int i53{0}; i53 < sb_loop_ub; i53++) {
                r2D[j + r2D.size(0) * i53] = r14[i53];
            }
            tb_loop_ub = r15.size(1);
            for (int i54{0}; i54 < tb_loop_ub; i54++) {
                r3D[j + r3D.size(0) * i54] = r15[i54];
            }
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:48' otherwise
        // 'EvalCurvStructNoCtx:49' c_assert( false, 'Unknown Curve Type for Eval.\n' );
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i11{0}; i11 < 30; i11++) {
            message[i11] = cv[i11];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStructNoCtx:52' r1D = a   .* r1D;
    i_loop_ub = r1D.size(1);
    for (int i13{0}; i13 < i_loop_ub; i13++) {
        int b_scalarLB;
        int b_vectorUB;
        int i20;
        int m_loop_ub;
        m_loop_ub = r1D.size(0);
        b_scalarLB = (r1D.size(0) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (i20 = 0; i20 <= b_vectorUB; i20 += 2) {
            __m128d r9;
            r9 = _mm_loadu_pd(&r1D[i20 + r1D.size(0) * i13]);
            _mm_storeu_pd(&r1D[i20 + r1D.size(0) * i13], _mm_mul_pd(_mm_set1_pd(curv_a_param), r9));
        }
        for (i20 = b_scalarLB; i20 < m_loop_ub; i20++) {
            r1D[i20 + r1D.size(0) * i13] = curv_a_param * r1D[i20 + r1D.size(0) * i13];
        }
    }
    // 'EvalCurvStructNoCtx:53' r2D = a^2 .* r2D;
    c = curv_a_param * curv_a_param;
    p_loop_ub = r2D.size(1);
    for (int i19{0}; i19 < p_loop_ub; i19++) {
        int c_scalarLB;
        int c_vectorUB;
        int i30;
        int v_loop_ub;
        v_loop_ub = r2D.size(0);
        c_scalarLB = (r2D.size(0) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (i30 = 0; i30 <= c_vectorUB; i30 += 2) {
            __m128d r10;
            r10 = _mm_loadu_pd(&r2D[i30 + r2D.size(0) * i19]);
            _mm_storeu_pd(&r2D[i30 + r2D.size(0) * i19], _mm_mul_pd(_mm_set1_pd(c), r10));
        }
        for (i30 = c_scalarLB; i30 < v_loop_ub; i30++) {
            r2D[i30 + r2D.size(0) * i19] = c * r2D[i30 + r2D.size(0) * i19];
        }
    }
    // 'EvalCurvStructNoCtx:54' r3D = a^3 .* r3D;
    b_c = std::pow(curv_a_param, 3.0);
    ab_loop_ub = r3D.size(1);
    for (int i29{0}; i29 < ab_loop_ub; i29++) {
        int d_scalarLB;
        int d_vectorUB;
        int fb_loop_ub;
        int i36;
        fb_loop_ub = r3D.size(0);
        d_scalarLB = (r3D.size(0) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (i36 = 0; i36 <= d_vectorUB; i36 += 2) {
            __m128d r11;
            r11 = _mm_loadu_pd(&r3D[i36 + r3D.size(0) * i29]);
            _mm_storeu_pd(&r3D[i36 + r3D.size(0) * i29], _mm_mul_pd(_mm_set1_pd(b_c), r11));
        }
        for (i36 = d_scalarLB; i36 < fb_loop_ub; i36++) {
            r3D[i36 + r3D.size(0) * i29] = b_c * r3D[i36 + r3D.size(0) * i29];
        }
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : int cfg_NumberAxis
//                int cfg_NCart
//                int cfg_NRot
//                const int cfg_indCart_data[]
//                int cfg_indCart_size
//                const int cfg_indRot_data[]
//                int cfg_indRot_size
//                const int cfg_indTot_data[]
//                int cfg_indTot_size
//                CurveType curv_Info_Type
//                const double curv_R0[6]
//                const double curv_R1[6]
//                const double curv_CorrectedHelixCenter[3]
//                const double curv_evec[3]
//                double curv_theta
//                double curv_pitch
//                const ::coder::array<double, 2U> &curv_CoeffP5
//                double curv_a_param
//                double curv_b_param
//                const CurvStruct *spline
//                double u_vec
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void EvalCurvStructNoCtx(int cfg_NumberAxis, int cfg_NCart, int cfg_NRot,
                         const int cfg_indCart_data[], int cfg_indCart_size,
                         const int cfg_indRot_data[], int cfg_indRot_size,
                         const int cfg_indTot_data[], int cfg_indTot_size, CurveType curv_Info_Type,
                         const double curv_R0[6], const double curv_R1[6],
                         const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                         double curv_theta, double curv_pitch,
                         const ::coder::array<double, 2U> &curv_CoeffP5, double curv_a_param,
                         double curv_b_param, const CurvStruct *spline, double u_vec,
                         ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                         ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D)
{
    ::coder::array<double, 2U> b_spline;
    double b_tmp_data[6];
    double c_tmp_data[6];
    double d_tmp_data[6];
    double r0D_data[6];
    double r1D_data[6];
    double r2D_data[6];
    double r3D_data[6];
    double tmp_data[6];
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double b_c;
    double c;
    double d;
    double d1;
    double d2;
    double u_vec_tilda;
    int e_tmp_data[3];
    int b_loop_ub;
    int b_scalarLB;
    int b_tmp_size;
    int c_scalarLB;
    int c_tmp_size;
    int d_loop_ub;
    int d_tmp_size;
    int d_vectorUB;
    int f_vectorUB;
    int i14;
    int i19;
    int i4;
    int loop_ub;
    int r0D_size;
    int r1D_size;
    int r2D_size;
    int r3D_size;
    int scalarLB;
    int tmp_size;
    int vectorUB;
    char message[30];
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:6' if any( u_vec - 1.0 > 10 * eps )
    if (u_vec - 1.0 > 2.2204460492503131E-15) {
        double unnamed_idx_0;
        // 'EvalCurvStructNoCtx:7' u_vec( u_vec > 1.0 ) = 1.0;
        unnamed_idx_0 = u_vec;
        if (u_vec > 1.0) {
            unnamed_idx_0 = 1.0;
        }
        u_vec = unnamed_idx_0;
        // 'EvalCurvStructNoCtx:7' printMsg( "Error : u_vec > 1\n" );
        //  printMsg : Print erro message according to the coder.target.
        // 'EvalCurvStructNoCtx:58' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:59' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:61' else
        // 'EvalCurvStructNoCtx:62' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec > 1\n");
        fflush(stdout);
    }
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    if (u_vec < 0.0) {
        // 'EvalCurvStructNoCtx:11' u_vec( u_vec < 0.0 ) = 0.0;
        u_vec = 0.0;
        // 'EvalCurvStructNoCtx:11' printMsg( "Error : u_vec < 0\n" );
        //  printMsg : Print erro message according to the coder.target.
        // 'EvalCurvStructNoCtx:58' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:59' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:61' else
        // 'EvalCurvStructNoCtx:62' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec < 0\n");
        fflush(stdout);
    }
    //
    // 'EvalCurvStructNoCtx:15' Type  = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N   = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M   = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:19' r0D = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:20' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:22' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:24' a = curv.a_param;
    // 'EvalCurvStructNoCtx:25' b = curv.b_param;
    // 'EvalCurvStructNoCtx:27' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv_a_param * u_vec + curv_b_param;
    // 'EvalCurvStructNoCtx:29' indC   = cfg.indCart;
    // 'EvalCurvStructNoCtx:30' indR   = cfg.indRot;
    // 'EvalCurvStructNoCtx:31' indTot = cfg.indTot;
    // 'EvalCurvStructNoCtx:33' switch Type
    switch (curv_Info_Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:34' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:35' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, indTot );
        EvalLine(curv_R0, curv_R1, u_vec_tilda, cfg_indTot_data, cfg_indTot_size, r0D_data,
                 &r0D_size, r1D_data, &r1D_size, r2D_data, &r2D_size, r3D_data, &r3D_size);
        r0D.set_size(r0D_size);
        for (int i2{0}; i2 < r0D_size; i2++) {
            r0D[i2] = r0D_data[i2];
        }
        r1D.set_size(r1D_size);
        for (int i3{0}; i3 < r1D_size; i3++) {
            r1D[i3] = r1D_data[i3];
        }
        r2D.set_size(r2D_size);
        for (int i7{0}; i7 < r2D_size; i7++) {
            r2D[i7] = r2D_data[i7];
        }
        r3D.set_size(r3D_size);
        for (int i9{0}; i9 < r3D_size; i9++) {
            r3D[i9] = r3D_data[i9];
        }
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:36' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:37' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int b_vectorUB;
            int c_vectorUB;
            int e_vectorUB;
            int g_vectorUB;
            int i13;
            int i17;
            int i22;
            int i6;
            int scalarLB_tmp;
            //  Only rotation
            // 'EvalCurvStructNoCtx:38' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:39'                 EvalHelix( curv, u_vec_tilda,
            // indC );
            EvalHelix(curv_R0, curv_CorrectedHelixCenter, curv_evec, curv_theta, curv_pitch,
                      u_vec_tilda, cfg_indCart_data, cfg_indCart_size, dv, dv1, dv2, dv3);
            scalarLB_tmp = (cfg_indCart_size / 4) << 2;
            b_vectorUB = scalarLB_tmp - 4;
            for (i6 = 0; i6 <= b_vectorUB; i6 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i6 = scalarLB_tmp; i6 < cfg_indCart_size; i6++) {
                e_tmp_data[i6] = cfg_indCart_data[i6] - 1;
            }
            for (int i11{0}; i11 < cfg_indCart_size; i11++) {
                r0D[e_tmp_data[i11]] = dv[i11];
            }
            c_vectorUB = scalarLB_tmp - 4;
            for (i13 = 0; i13 <= c_vectorUB; i13 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i13 = scalarLB_tmp; i13 < cfg_indCart_size; i13++) {
                e_tmp_data[i13] = cfg_indCart_data[i13] - 1;
            }
            for (int i16{0}; i16 < cfg_indCart_size; i16++) {
                r1D[e_tmp_data[i16]] = dv1[i16];
            }
            e_vectorUB = scalarLB_tmp - 4;
            for (i17 = 0; i17 <= e_vectorUB; i17 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i17 = scalarLB_tmp; i17 < cfg_indCart_size; i17++) {
                e_tmp_data[i17] = cfg_indCart_data[i17] - 1;
            }
            for (int i20{0}; i20 < cfg_indCart_size; i20++) {
                r2D[e_tmp_data[i20]] = dv2[i20];
            }
            g_vectorUB = scalarLB_tmp - 4;
            for (i22 = 0; i22 <= g_vectorUB; i22 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i22 = scalarLB_tmp; i22 < cfg_indCart_size; i22++) {
                e_tmp_data[i22] = cfg_indCart_data[i22] - 1;
            }
            for (int i23{0}; i23 < cfg_indCart_size; i23++) {
                r3D[e_tmp_data[i23]] = dv3[i23];
            }
        } else if (cfg_NRot > 0) {
            // 'EvalCurvStructNoCtx:40' elseif( cfg.NRot > 0 )
            //  Only cartesian
            // 'EvalCurvStructNoCtx:41' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:42'                 EvalLine( curv, u_vec_tilda, indR
            // );
            EvalLine(curv_R0, curv_R1, u_vec_tilda, cfg_indRot_data, cfg_indRot_size, tmp_data,
                     &tmp_size, b_tmp_data, &b_tmp_size, c_tmp_data, &c_tmp_size, d_tmp_data,
                     &d_tmp_size);
            for (int i5{0}; i5 < tmp_size; i5++) {
                r0D[cfg_indRot_data[i5] - 1] = tmp_data[i5];
            }
            for (int i8{0}; i8 < b_tmp_size; i8++) {
                r1D[cfg_indRot_data[i8] - 1] = b_tmp_data[i8];
            }
            for (int i10{0}; i10 < c_tmp_size; i10++) {
                r2D[cfg_indRot_data[i10] - 1] = c_tmp_data[i10];
            }
            for (int i12{0}; i12 < d_tmp_size; i12++) {
                r3D[cfg_indRot_data[i12] - 1] = d_tmp_data[i12];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:44' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:45' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda );
        EvalTransP5(curv_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int c_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int i25;
        // 'EvalCurvStructNoCtx:46' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:47' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        //  EvalBSpline
        //
        //  INPUT
        //  spline        : struct : Spline structure
        //  u_vec         :    1xn : Vector for evaluation of the curv
        //
        //  OUTPUT
        //  r0D           :   nDxn : The evaluated B spline at u\_vec points
        //  r1D           :   nDxn : 1rst order parametric derivative for the B spline at u\_vec
        //  points r2D           :   nDxn : 2nd order parametric derivative for the B spline at
        //  u\_vec points r3D           :   nDxn : 3rd order parametric derivative for the B spline
        //  at u\_vec points
        // 'EvalBSpline:14' sp = spline.sp;
        // 'EvalBSpline:15' N  = length( u_vec );
        // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
        // 'EvalBSpline:18' r0D = zeros( M, N );
        r0D.set_size(spline->sp.coeff.size(0));
        c_loop_ub = spline->sp.coeff.size(0);
        for (int i15{0}; i15 < c_loop_ub; i15++) {
            r0D[i15] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        e_loop_ub = spline->sp.coeff.size(0);
        for (int i18{0}; i18 < e_loop_ub; i18++) {
            r1D[i18] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        f_loop_ub = spline->sp.coeff.size(0);
        for (int i21{0}; i21 < f_loop_ub; i21++) {
            r2D[i21] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        g_loop_ub = spline->sp.coeff.size(0);
        for (int i24{0}; i24 < g_loop_ub; i24++) {
            r3D[i24] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i25 = spline->sp.coeff.size(0);
        for (int j{0}; j < i25; j++) {
            int h_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0D[j] = u_vec_tilda;
            h_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i26{0}; i26 < h_loop_ub; i26++) {
                b_spline[i26] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i26];
            }
            bspline_eval(spline->sp.Bl.handle, b_spline, &r0D[j], &d, &d1, &d2);
            r3D[j] = d2;
            r2D[j] = d1;
            r1D[j] = d;
            // 'bspline_eval_vec:10' x(k)    = xk;
            // 'bspline_eval_vec:11' xd(k)   = xdk;
            // 'bspline_eval_vec:12' xdd(k)  = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:48' otherwise
        // 'EvalCurvStructNoCtx:49' c_assert( false, 'Unknown Curve Type for Eval.\n' );
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i1{0}; i1 < 30; i1++) {
            message[i1] = cv[i1];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStructNoCtx:52' r1D = a   .* r1D;
    loop_ub = r1D.size(0);
    scalarLB = (r1D.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i4 = 0; i4 <= vectorUB; i4 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&r1D[i4]);
        _mm_storeu_pd(&r1D[i4], _mm_mul_pd(_mm_set1_pd(curv_a_param), r));
    }
    for (i4 = scalarLB; i4 < loop_ub; i4++) {
        r1D[i4] = curv_a_param * r1D[i4];
    }
    // 'EvalCurvStructNoCtx:53' r2D = a^2 .* r2D;
    c = curv_a_param * curv_a_param;
    b_loop_ub = r2D.size(0);
    b_scalarLB = (r2D.size(0) / 2) << 1;
    d_vectorUB = b_scalarLB - 2;
    for (i14 = 0; i14 <= d_vectorUB; i14 += 2) {
        __m128d r1;
        r1 = _mm_loadu_pd(&r2D[i14]);
        _mm_storeu_pd(&r2D[i14], _mm_mul_pd(_mm_set1_pd(c), r1));
    }
    for (i14 = b_scalarLB; i14 < b_loop_ub; i14++) {
        r2D[i14] = c * r2D[i14];
    }
    // 'EvalCurvStructNoCtx:54' r3D = a^3 .* r3D;
    b_c = std::pow(curv_a_param, 3.0);
    d_loop_ub = r3D.size(0);
    c_scalarLB = (r3D.size(0) / 2) << 1;
    f_vectorUB = c_scalarLB - 2;
    for (i19 = 0; i19 <= f_vectorUB; i19 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r3D[i19]);
        _mm_storeu_pd(&r3D[i19], _mm_mul_pd(_mm_set1_pd(b_c), r2));
    }
    for (i19 = c_scalarLB; i19 < d_loop_ub; i19++) {
        r3D[i19] = b_c * r3D[i19];
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : int cfg_NumberAxis
//                int cfg_NCart
//                int cfg_NRot
//                const int cfg_indCart_data[]
//                int cfg_indCart_size
//                const int cfg_indRot_data[]
//                int cfg_indRot_size
//                const int cfg_indTot_data[]
//                int cfg_indTot_size
//                CurveType curv_Info_Type
//                const double curv_R0[6]
//                const double curv_R1[6]
//                const double curv_CorrectedHelixCenter[3]
//                const double curv_evec[3]
//                double curv_theta
//                double curv_pitch
//                const ::coder::array<double, 2U> &curv_CoeffP5
//                double curv_a_param
//                double curv_b_param
//                const CurvStruct *spline
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void b_EvalCurvStructNoCtx(int cfg_NumberAxis, int cfg_NCart, int cfg_NRot,
                           const int cfg_indCart_data[], int cfg_indCart_size,
                           const int cfg_indRot_data[], int cfg_indRot_size,
                           const int cfg_indTot_data[], int cfg_indTot_size,
                           CurveType curv_Info_Type, const double curv_R0[6],
                           const double curv_R1[6], const double curv_CorrectedHelixCenter[3],
                           const double curv_evec[3], double curv_theta, double curv_pitch,
                           const ::coder::array<double, 2U> &curv_CoeffP5, double curv_a_param,
                           double curv_b_param, const CurvStruct *spline,
                           ::coder::array<double, 1U> &r0D, ::coder::array<double, 1U> &r1D,
                           ::coder::array<double, 1U> &r2D, ::coder::array<double, 1U> &r3D)
{
    ::coder::array<double, 2U> b_spline;
    double b_tmp_data[6];
    double c_tmp_data[6];
    double d_tmp_data[6];
    double r0D_data[6];
    double r1D_data[6];
    double r2D_data[6];
    double r3D_data[6];
    double tmp_data[6];
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double b_c;
    double c;
    double d;
    double d1;
    double d2;
    int e_tmp_data[3];
    int b_loop_ub;
    int b_scalarLB;
    int b_tmp_size;
    int c_scalarLB;
    int c_tmp_size;
    int d_loop_ub;
    int d_tmp_size;
    int d_vectorUB;
    int f_vectorUB;
    int i14;
    int i19;
    int i4;
    int loop_ub;
    int r0D_size;
    int r1D_size;
    int r2D_size;
    int r3D_size;
    int scalarLB;
    int tmp_size;
    int vectorUB;
    char message[30];
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:6' if any( u_vec - 1.0 > 10 * eps )
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    //
    // 'EvalCurvStructNoCtx:15' Type  = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N   = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M   = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:19' r0D = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:20' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:22' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:24' a = curv.a_param;
    // 'EvalCurvStructNoCtx:25' b = curv.b_param;
    // 'EvalCurvStructNoCtx:27' u_vec_tilda = a * u_vec + b;
    // 'EvalCurvStructNoCtx:29' indC   = cfg.indCart;
    // 'EvalCurvStructNoCtx:30' indR   = cfg.indRot;
    // 'EvalCurvStructNoCtx:31' indTot = cfg.indTot;
    // 'EvalCurvStructNoCtx:33' switch Type
    switch (curv_Info_Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:34' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:35' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, indTot );
        EvalLine(curv_R0, curv_R1, curv_b_param, cfg_indTot_data, cfg_indTot_size, r0D_data,
                 &r0D_size, r1D_data, &r1D_size, r2D_data, &r2D_size, r3D_data, &r3D_size);
        r0D.set_size(r0D_size);
        for (int i2{0}; i2 < r0D_size; i2++) {
            r0D[i2] = r0D_data[i2];
        }
        r1D.set_size(r1D_size);
        for (int i3{0}; i3 < r1D_size; i3++) {
            r1D[i3] = r1D_data[i3];
        }
        r2D.set_size(r2D_size);
        for (int i7{0}; i7 < r2D_size; i7++) {
            r2D[i7] = r2D_data[i7];
        }
        r3D.set_size(r3D_size);
        for (int i9{0}; i9 < r3D_size; i9++) {
            r3D[i9] = r3D_data[i9];
        }
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:36' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:37' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int b_vectorUB;
            int c_vectorUB;
            int e_vectorUB;
            int g_vectorUB;
            int i13;
            int i17;
            int i22;
            int i6;
            int scalarLB_tmp;
            //  Only rotation
            // 'EvalCurvStructNoCtx:38' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:39'                 EvalHelix( curv, u_vec_tilda,
            // indC );
            EvalHelix(curv_R0, curv_CorrectedHelixCenter, curv_evec, curv_theta, curv_pitch,
                      curv_b_param, cfg_indCart_data, cfg_indCart_size, dv, dv1, dv2, dv3);
            scalarLB_tmp = (cfg_indCart_size / 4) << 2;
            b_vectorUB = scalarLB_tmp - 4;
            for (i6 = 0; i6 <= b_vectorUB; i6 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i6 = scalarLB_tmp; i6 < cfg_indCart_size; i6++) {
                e_tmp_data[i6] = cfg_indCart_data[i6] - 1;
            }
            for (int i11{0}; i11 < cfg_indCart_size; i11++) {
                r0D[e_tmp_data[i11]] = dv[i11];
            }
            c_vectorUB = scalarLB_tmp - 4;
            for (i13 = 0; i13 <= c_vectorUB; i13 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i13 = scalarLB_tmp; i13 < cfg_indCart_size; i13++) {
                e_tmp_data[i13] = cfg_indCart_data[i13] - 1;
            }
            for (int i16{0}; i16 < cfg_indCart_size; i16++) {
                r1D[e_tmp_data[i16]] = dv1[i16];
            }
            e_vectorUB = scalarLB_tmp - 4;
            for (i17 = 0; i17 <= e_vectorUB; i17 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i17 = scalarLB_tmp; i17 < cfg_indCart_size; i17++) {
                e_tmp_data[i17] = cfg_indCart_data[i17] - 1;
            }
            for (int i20{0}; i20 < cfg_indCart_size; i20++) {
                r2D[e_tmp_data[i20]] = dv2[i20];
            }
            g_vectorUB = scalarLB_tmp - 4;
            for (i22 = 0; i22 <= g_vectorUB; i22 += 4) {
                _mm_storeu_si128(
                    (__m128i *)&e_tmp_data[0],
                    _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart_data[0]),
                                  _mm_set1_epi32(1)));
            }
            for (i22 = scalarLB_tmp; i22 < cfg_indCart_size; i22++) {
                e_tmp_data[i22] = cfg_indCart_data[i22] - 1;
            }
            for (int i23{0}; i23 < cfg_indCart_size; i23++) {
                r3D[e_tmp_data[i23]] = dv3[i23];
            }
        } else if (cfg_NRot > 0) {
            // 'EvalCurvStructNoCtx:40' elseif( cfg.NRot > 0 )
            //  Only cartesian
            // 'EvalCurvStructNoCtx:41' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:42'                 EvalLine( curv, u_vec_tilda, indR
            // );
            EvalLine(curv_R0, curv_R1, curv_b_param, cfg_indRot_data, cfg_indRot_size, tmp_data,
                     &tmp_size, b_tmp_data, &b_tmp_size, c_tmp_data, &c_tmp_size, d_tmp_data,
                     &d_tmp_size);
            for (int i5{0}; i5 < tmp_size; i5++) {
                r0D[cfg_indRot_data[i5] - 1] = tmp_data[i5];
            }
            for (int i8{0}; i8 < b_tmp_size; i8++) {
                r1D[cfg_indRot_data[i8] - 1] = b_tmp_data[i8];
            }
            for (int i10{0}; i10 < c_tmp_size; i10++) {
                r2D[cfg_indRot_data[i10] - 1] = c_tmp_data[i10];
            }
            for (int i12{0}; i12 < d_tmp_size; i12++) {
                r3D[cfg_indRot_data[i12] - 1] = d_tmp_data[i12];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:44' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:45' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda );
        EvalTransP5(curv_CoeffP5, curv_b_param, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int c_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int i25;
        // 'EvalCurvStructNoCtx:46' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:47' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        //  EvalBSpline
        //
        //  INPUT
        //  spline        : struct : Spline structure
        //  u_vec         :    1xn : Vector for evaluation of the curv
        //
        //  OUTPUT
        //  r0D           :   nDxn : The evaluated B spline at u\_vec points
        //  r1D           :   nDxn : 1rst order parametric derivative for the B spline at u\_vec
        //  points r2D           :   nDxn : 2nd order parametric derivative for the B spline at
        //  u\_vec points r3D           :   nDxn : 3rd order parametric derivative for the B spline
        //  at u\_vec points
        // 'EvalBSpline:14' sp = spline.sp;
        // 'EvalBSpline:15' N  = length( u_vec );
        // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
        // 'EvalBSpline:18' r0D = zeros( M, N );
        r0D.set_size(spline->sp.coeff.size(0));
        c_loop_ub = spline->sp.coeff.size(0);
        for (int i15{0}; i15 < c_loop_ub; i15++) {
            r0D[i15] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        e_loop_ub = spline->sp.coeff.size(0);
        for (int i18{0}; i18 < e_loop_ub; i18++) {
            r1D[i18] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        f_loop_ub = spline->sp.coeff.size(0);
        for (int i21{0}; i21 < f_loop_ub; i21++) {
            r2D[i21] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        g_loop_ub = spline->sp.coeff.size(0);
        for (int i24{0}; i24 < g_loop_ub; i24++) {
            r3D[i24] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i25 = spline->sp.coeff.size(0);
        for (int j{0}; j < i25; j++) {
            int h_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0D[j] = curv_b_param;
            h_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i26{0}; i26 < h_loop_ub; i26++) {
                b_spline[i26] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i26];
            }
            bspline_eval(spline->sp.Bl.handle, b_spline, &r0D[j], &d, &d1, &d2);
            r3D[j] = d2;
            r2D[j] = d1;
            r1D[j] = d;
            // 'bspline_eval_vec:10' x(k)    = xk;
            // 'bspline_eval_vec:11' xd(k)   = xdk;
            // 'bspline_eval_vec:12' xdd(k)  = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:48' otherwise
        // 'EvalCurvStructNoCtx:49' c_assert( false, 'Unknown Curve Type for Eval.\n' );
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i1{0}; i1 < 30; i1++) {
            message[i1] = cv[i1];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        break;
    }
    // 'EvalCurvStructNoCtx:52' r1D = a   .* r1D;
    loop_ub = r1D.size(0);
    scalarLB = (r1D.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i4 = 0; i4 <= vectorUB; i4 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&r1D[i4]);
        _mm_storeu_pd(&r1D[i4], _mm_mul_pd(_mm_set1_pd(curv_a_param), r));
    }
    for (i4 = scalarLB; i4 < loop_ub; i4++) {
        r1D[i4] = curv_a_param * r1D[i4];
    }
    // 'EvalCurvStructNoCtx:53' r2D = a^2 .* r2D;
    c = curv_a_param * curv_a_param;
    b_loop_ub = r2D.size(0);
    b_scalarLB = (r2D.size(0) / 2) << 1;
    d_vectorUB = b_scalarLB - 2;
    for (i14 = 0; i14 <= d_vectorUB; i14 += 2) {
        __m128d r1;
        r1 = _mm_loadu_pd(&r2D[i14]);
        _mm_storeu_pd(&r2D[i14], _mm_mul_pd(_mm_set1_pd(c), r1));
    }
    for (i14 = b_scalarLB; i14 < b_loop_ub; i14++) {
        r2D[i14] = c * r2D[i14];
    }
    // 'EvalCurvStructNoCtx:54' r3D = a^3 .* r3D;
    b_c = std::pow(curv_a_param, 3.0);
    d_loop_ub = r3D.size(0);
    c_scalarLB = (r3D.size(0) / 2) << 1;
    f_vectorUB = c_scalarLB - 2;
    for (i19 = 0; i19 <= f_vectorUB; i19 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r3D[i19]);
        _mm_storeu_pd(&r3D[i19], _mm_mul_pd(_mm_set1_pd(b_c), r2));
    }
    for (i19 = c_scalarLB; i19 < d_loop_ub; i19++) {
        r3D[i19] = b_c * r3D[i19];
    }
}

} // namespace ocn

//
// File trailer for EvalCurvStructNoCtx.cpp
//
// [EOF]
//
