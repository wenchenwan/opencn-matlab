//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutCurvStructU.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:25:45
//

// Include Files
#include "cutCurvStructU.h"
#include "EvalCurvStruct.h"
#include "SplineLengthApprox_Interval1.h"
#include "bspline_eval.h"
#include "combineVectorElements.h"
#include "find.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "opencn_matlab_types31.h"
#include "queue_coder.h"
#include "sum.h"
#include "coder_array.h"
#include <cmath>

// Variable Definitions
namespace ocn {
static const char cv2[54]{'u', '1', ' ', 'm', 'u', 's', 't', ' ', 'b', 'e', ' ', 's', 'm', 'a',
                          'l', 'l', 'e', 'r', ' ', 'o', 'r', ' ', 'e', 'q', 'u', 'a', 'l', ' ',
                          't', 'h', 'a', 'n', ' ', 't', 'h', 'e', ' ', 'f', 'i', 'r', 's', 't',
                          ' ', 's', 'p', 'l', 'i', 'n', 'e', ' ', 'k', 'n', 'o', 't'};

}

// Function Definitions
//
// function [ u1_tilda ] = cutCurvStructU( ctx, curv, u0, L, isEnd )
//
// cutCurvStructU: Cut a piece of the structure with a size of L
//  starting at point u0
//  Inputs :
//  ctx   : Context
//  curv  : Curvature
//  u0    : Starting point of the spline
//  L     : Length of the segment of curv
//  isEnd : Is a cut from the end
//  Outputs :
//  u1    : The last point of the splitted curv
//
// Arguments    : const queue_coder *ctx_q_spline
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const int ctx_cfg_indCart_data[]
//                int ctx_cfg_indCart_size
//                const int ctx_cfg_indRot_data[]
//                int ctx_cfg_indRot_size
//                const int ctx_cfg_indTot_data[]
//                int ctx_cfg_indTot_size
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                CurveType curv_Info_Type
//                const double curv_R0[6]
//                const double curv_R1[6]
//                const double curv_CorrectedHelixCenter[3]
//                const double curv_evec[3]
//                double curv_theta
//                double curv_pitch
//                const ::coder::array<double, 2U> &curv_CoeffP5
//                unsigned int curv_sp_index
//                double curv_a_param
//                double curv_b_param
//                double L
// Return Type  : double
//
namespace ocn {
double b_cutCurvStructU(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                        int ctx_cfg_NRot, const int ctx_cfg_indCart_data[],
                        int ctx_cfg_indCart_size, const int ctx_cfg_indRot_data[],
                        int ctx_cfg_indRot_size, const int ctx_cfg_indTot_data[],
                        int ctx_cfg_indTot_size, const double ctx_cfg_GaussLegendreX[5],
                        const double ctx_cfg_GaussLegendreW[5], CurveType curv_Info_Type,
                        const double curv_R0[6], const double curv_R1[6],
                        const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                        double curv_theta, double curv_pitch,
                        const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
                        double curv_a_param, double curv_b_param, double L)
{
    ::coder::array<double, 2U> c_expl_temp;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r1D1;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    ::coder::array<int, 2U> k_vec;
    ::coder::array<bool, 2U> b_expl_temp;
    CurvStruct expl_temp;
    double d;
    double d1;
    double d2;
    double u1_tilda;
    char message[54];
    // 'cutCurvStructU:13' a = curv.a_param;
    // 'cutCurvStructU:14' b = curv.b_param;
    // 'cutCurvStructU:16' if ( curv.Info.Type == CurveType.Spline )
    if (curv_Info_Type == CurveType_Spline) {
        double b_L;
        double u1;
        int b_loop_ub;
        int c_loop_ub;
        int i1;
        int i2;
        int i3;
        int i7;
        int i8;
        int k;
        // 'cutCurvStructU:17' u1_tilda = splineLengthFindU( ctx, curv, L, a * u0 + b, isEnd );
        //  Computes approximately the value of curve parameter u such that the arc
        //  length starting from u1 equals L.
        //  This function takes usage of the precalculated arc lengths between knots.
        //  The last integration interval is approximated by the trapezoidal rule.
        //  u1 must satisfy 0 < u1 < 1.
        //  In the normal case, u must satisfy 0 < u < u1. If L is too large, u is
        //  set to -1
        //  Warning : This function works only for B-spline of degree 3
        //  Get the sp structure
        // 'splineLengthFindU:12' spline = ctx.q_spline.get( curv.sp_index );
        ctx_q_spline->get(curv_sp_index, &expl_temp);
        // 'splineLengthFindU:13' sp     = spline.sp;
        // 'splineLengthFindU:15' DEFAULT_TOL_NR  = 1e-6;
        //  Default tolerance for Newton Raphson
        // 'splineLengthFindU:16' IND_KNOTS_MULT  = sp.Bl.order;
        //  Index used to remove multiple knots
        //                               (ONLY TRUE FOR CUBIC SPLINE)
        //  Eliminate multiplicities at the end points
        // 'splineLengthFindU:20' Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
        i1 = (expl_temp.sp.knots.size(1) - expl_temp.sp.Bl.order) + 1;
        if (expl_temp.sp.Bl.order > i1) {
            i2 = 0;
            i3 = 0;
        } else {
            i2 = expl_temp.sp.Bl.order - 1;
            i3 = i1;
        }
        // 'splineLengthFindU:21' Lk     = sp.Lk;
        // 'splineLengthFindU:22' KMax   = length( Lk );
        // 'splineLengthFindU:24' if( isEnd )
        // 'splineLengthFindU:25' u1 = 1 - u1;
        u1 = 1.0 - (curv_a_param + curv_b_param);
        //
        // 'splineLengthFindU:29' C_ASSERT_MSG = 'u1 must be %s or equal than the first spline
        // knot'; 'splineLengthFindU:30' c_assert( u1 >= Knots(1),   sprintf(C_ASSERT_MSG,
        // 'greater') ); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
        if (u1 < expl_temp.sp.knots[i2]) {
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i4{0}; i4 < 54; i4++) {
                message[i4] = cv1[i4];
            }
            c_assert_(&message[0]);
        }
        // 'c_assert:6' value = condition;
        // 'splineLengthFindU:31' c_assert( u1 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller') );
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        if (u1 > expl_temp.sp.knots[i3 - 1]) {
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i5{0}; i5 < 54; i5++) {
                message[i5] = cv2[i5];
            }
            c_assert_(&message[0]);
        }
        // 'c_assert:6' value = condition;
        //
        // 'splineLengthFindU:33' k_vec = find( Knots < u1 );
        b_loop_ub = i3 - i2;
        b_expl_temp.set_size(1, b_loop_ub);
        for (int i6{0}; i6 < b_loop_ub; i6++) {
            b_expl_temp[i6] = (expl_temp.sp.knots[i2 + i6] < u1);
        }
        coder::eml_find(b_expl_temp, k_vec);
        // 'splineLengthFindU:34' if( isempty( k_vec ) )
        if (k_vec.size(1) == 0) {
            // 'splineLengthFindU:35' k = 1;
            k = 0;
        } else {
            // 'splineLengthFindU:36' else
            // 'splineLengthFindU:37' k = k_vec( end );
            k = k_vec[k_vec.size(1) - 1] - 1;
        }
        // 'splineLengthFindU:40' if( isEnd )
        // 'splineLengthFindU:41' L  = sum( Lk( k : end ) ) - L;
        if (k + 1 > expl_temp.sp.Lk.size(1)) {
            i7 = 0;
            i8 = 0;
        } else {
            i7 = k;
            i8 = expl_temp.sp.Lk.size(1);
        }
        c_loop_ub = i8 - i7;
        c_expl_temp.set_size(1, c_loop_ub);
        for (int i9{0}; i9 < c_loop_ub; i9++) {
            c_expl_temp[i9] = expl_temp.sp.Lk[i7 + i9];
        }
        b_L = coder::sum(c_expl_temp) - L;
        // 'splineLengthFindU:42' if( L < 0 )
        if (b_L < 0.0) {
            // 'splineLengthFindU:42' u = 1;
            u1_tilda = 1.0;
        } else {
            double Lcum;
            double Lremain;
            double uk;
            double uk_old;
            //
            //  Length to next break point
            // 'splineLengthFindU:49' Lcum = Lk( k ) - SplineLengthApprox_Interval1( ctx, curv,
            // Knots( k ), u1 );
            Lcum = expl_temp.sp.Lk[k] -
                   SplineLengthApprox_Interval1(ctx_q_spline, ctx_cfg_GaussLegendreX,
                                                ctx_cfg_GaussLegendreW, curv_sp_index,
                                                expl_temp.sp.knots[i2 + k], u1);
            //
            // 'splineLengthFindU:51' while ( Lcum < L ) && ( k < KMax )
            while ((Lcum < b_L) && (k + 1 < expl_temp.sp.Lk.size(1))) {
                // 'splineLengthFindU:52' k = k + 1;
                k++;
                // 'splineLengthFindU:53' Lcum = Lcum + Lk( k );
                Lcum += expl_temp.sp.Lk[k];
                //  Sum up precalculated length between knots
            }
            int u1_tmp;
            //  undo last increment
            // 'splineLengthFindU:57' k         = k - 1;
            // 'splineLengthFindU:58' Lcum      = Lcum - Lk( k );
            Lcum -= expl_temp.sp.Lk[k - 1];
            // 'splineLengthFindU:59' Lremain   = L - Lcum;
            Lremain = b_L - Lcum;
            //
            // 'splineLengthFindU:62' u1     = Knots( k+1 );
            u1_tmp = i2 + k;
            u1 = expl_temp.sp.knots[u1_tmp];
            //  Initial guess for Newton Raphson iteration
            // 'splineLengthFindU:64' uk     = 0.5 * ( Knots( k ) + Knots( k + 1 ) );
            uk = 0.5 * (expl_temp.sp.knots[u1_tmp - 1] + expl_temp.sp.knots[u1_tmp]);
            //  Dummy value to ensure that while loop enters
            // 'splineLengthFindU:66' uk_old = 2;
            uk_old = 2.0;
            //  Iterate until new value of uk is close to old value
            // 'splineLengthFindU:69' while abs( uk - uk_old ) > DEFAULT_TOL_NR
            while (std::abs(uk - uk_old) > 1.0E-6) {
                double fk;
                int d_loop_ub;
                int e_loop_ub;
                int f_loop_ub;
                int g_loop_ub;
                int i14;
                int i_loop_ub;
                //  Evaluation of function which should become zero
                // 'splineLengthFindU:71' fk = SplineLengthApprox_Interval1( ctx, curv, uk, u1 ) -
                // Lremain;
                fk = SplineLengthApprox_Interval1(ctx_q_spline, ctx_cfg_GaussLegendreX,
                                                  ctx_cfg_GaussLegendreW, curv_sp_index, uk, u1) -
                     Lremain;
                // 'splineLengthFindU:72' [ ~, r1D ]  = EvalBSpline( spline, uk );
                //  EvalBSpline
                //
                //  INPUT
                //  spline        : struct : Spline structure
                //  u_vec         :    1xn : Vector for evaluation of the curv
                //
                //  OUTPUT
                //  r0D           :   nDxn : The evaluated B spline at u\_vec points
                //  r1D           :   nDxn : 1rst order parametric derivative for the B spline at
                //  u\_vec points r2D           :   nDxn : 2nd order parametric derivative for the B
                //  spline at u\_vec points r3D           :   nDxn : 3rd order parametric derivative
                //  for the B spline at u\_vec points
                // 'EvalBSpline:14' sp = spline.sp;
                // 'EvalBSpline:15' N  = length( u_vec );
                // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
                // 'EvalBSpline:18' r0D = zeros( M, N );
                a__1.set_size(expl_temp.sp.coeff.size(0));
                d_loop_ub = expl_temp.sp.coeff.size(0);
                for (int i10{0}; i10 < d_loop_ub; i10++) {
                    a__1[i10] = 0.0;
                }
                // 'EvalBSpline:18' r1D = r0D;
                r1D.set_size(expl_temp.sp.coeff.size(0));
                e_loop_ub = expl_temp.sp.coeff.size(0);
                for (int i11{0}; i11 < e_loop_ub; i11++) {
                    r1D[i11] = 0.0;
                }
                // 'EvalBSpline:18' r2D = r1D;
                r2D.set_size(expl_temp.sp.coeff.size(0));
                f_loop_ub = expl_temp.sp.coeff.size(0);
                for (int i12{0}; i12 < f_loop_ub; i12++) {
                    r2D[i12] = 0.0;
                }
                // 'EvalBSpline:18' r3D = r2D;
                r3D.set_size(expl_temp.sp.coeff.size(0));
                g_loop_ub = expl_temp.sp.coeff.size(0);
                for (int i13{0}; i13 < g_loop_ub; i13++) {
                    r3D[i13] = 0.0;
                }
                // 'EvalBSpline:20' for j = 1 : M
                i14 = expl_temp.sp.coeff.size(0);
                for (int j{0}; j < i14; j++) {
                    int h_loop_ub;
                    // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] =
                    // ... 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl,
                    // sp.coeff( j, : ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
                    // 'bspline_eval_vec:4' xd      = zeros(size(u));
                    // 'bspline_eval_vec:5' xdd     = zeros(size(u));
                    // 'bspline_eval_vec:6' xddd    = zeros(size(u));
                    // 'bspline_eval_vec:8' for k = 1:length(u)
                    // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
                    a__1[j] = uk;
                    h_loop_ub = expl_temp.sp.coeff.size(1);
                    c_expl_temp.set_size(1, expl_temp.sp.coeff.size(1));
                    for (int i15{0}; i15 < h_loop_ub; i15++) {
                        c_expl_temp[i15] = expl_temp.sp.coeff[j + expl_temp.sp.coeff.size(0) * i15];
                    }
                    bspline_eval(expl_temp.sp.Bl.handle, c_expl_temp, &a__1[j], &d, &d1, &d2);
                    r3D[j] = d2;
                    r2D[j] = d1;
                    r1D[j] = d;
                    // 'bspline_eval_vec:10' x(k)    = xk;
                    // 'bspline_eval_vec:11' xd(k)   = xdk;
                    // 'bspline_eval_vec:12' xdd(k)  = xddk;
                    // 'bspline_eval_vec:13' xddd(k) = xdddk;
                }
                //  Evaluation of the derivative of the function which should become zero
                // 'splineLengthFindU:74' Dfk    = -MyNorm(r1D);
                // 'MyNorm:2' coder.inline('always');
                // 'MyNorm:3' n = mysqrt(sum(x.^2));
                // 'mysqrt:3' y = sqrt(x);
                // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                sqrt_calls++;
                //
                // 'splineLengthFindU:76' uk_old = uk;
                uk_old = uk;
                // 'splineLengthFindU:77' uk     = uk_old - fk / Dfk;
                r.set_size(r1D.size(0));
                i_loop_ub = r1D.size(0);
                for (int i16{0}; i16 < i_loop_ub; i16++) {
                    double b_varargin_1;
                    b_varargin_1 = r1D[i16];
                    r[i16] = std::pow(b_varargin_1, 2.0);
                }
                uk -= fk / -std::sqrt(coder::combineVectorElements(r));
                //  Newton Raphson update
                // 'splineLengthFindU:78' if uk > u1
                if (uk > u1) {
                    // 'splineLengthFindU:79' uk = u1;
                    uk = u1;
                    //  Make sure not to run away
                }
            }
            //
            // 'splineLengthFindU:83' u  = uk;
            u1_tilda = uk;
        }
    } else {
        int loop_ub;
        // 'cutCurvStructU:18' else
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        // 'cutCurvStructU:22' if( isEnd )
        // 'cutCurvStructU:23' [ ~, r1D1 ] = EvalCurvStruct( ctx, curv, 1 );
        b_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                         ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                         ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                         curv_Info_Type, curv_R0, curv_R1, curv_CorrectedHelixCenter, curv_evec,
                         curv_theta, curv_pitch, curv_CoeffP5, curv_sp_index, curv_a_param,
                         curv_b_param, a__1, r1D1);
        // 'cutCurvStructU:24' u1 = u0 - L / MyNorm( r1D1 );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'cutCurvStructU:29' u1_tilda = a * u1 + b;
        r.set_size(r1D1.size(0));
        loop_ub = r1D1.size(0);
        for (int i{0}; i < loop_ub; i++) {
            double varargin_1;
            varargin_1 = r1D1[i];
            r[i] = std::pow(varargin_1, 2.0);
        }
        u1_tilda =
            curv_a_param * (1.0 - L / std::sqrt(coder::combineVectorElements(r))) + curv_b_param;
    }
    return u1_tilda;
}

//
// function [ u1_tilda ] = cutCurvStructU( ctx, curv, u0, L, isEnd )
//
// cutCurvStructU: Cut a piece of the structure with a size of L
//  starting at point u0
//  Inputs :
//  ctx   : Context
//  curv  : Curvature
//  u0    : Starting point of the spline
//  L     : Length of the segment of curv
//  isEnd : Is a cut from the end
//  Outputs :
//  u1    : The last point of the splitted curv
//
// Arguments    : const queue_coder *ctx_q_spline
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const int ctx_cfg_indCart_data[]
//                int ctx_cfg_indCart_size
//                const int ctx_cfg_indRot_data[]
//                int ctx_cfg_indRot_size
//                const int ctx_cfg_indTot_data[]
//                int ctx_cfg_indTot_size
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                CurveType curv_Info_Type
//                const double curv_R0[6]
//                const double curv_R1[6]
//                const double curv_CorrectedHelixCenter[3]
//                const double curv_evec[3]
//                double curv_theta
//                double curv_pitch
//                const ::coder::array<double, 2U> &curv_CoeffP5
//                unsigned int curv_sp_index
//                double curv_a_param
//                double curv_b_param
//                double L
// Return Type  : double
//
double cutCurvStructU(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                      int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                      const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                      const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                      const double ctx_cfg_GaussLegendreX[5],
                      const double ctx_cfg_GaussLegendreW[5], CurveType curv_Info_Type,
                      const double curv_R0[6], const double curv_R1[6],
                      const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                      double curv_theta, double curv_pitch,
                      const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
                      double curv_a_param, double curv_b_param, double L)
{
    ::coder::array<double, 2U> c_expl_temp;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r1D0;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    ::coder::array<int, 2U> k_vec;
    ::coder::array<bool, 2U> b_expl_temp;
    CurvStruct expl_temp;
    double d;
    double d1;
    double d2;
    double u1_tilda;
    char message[54];
    // 'cutCurvStructU:13' a = curv.a_param;
    // 'cutCurvStructU:14' b = curv.b_param;
    // 'cutCurvStructU:16' if ( curv.Info.Type == CurveType.Spline )
    if (curv_Info_Type == CurveType_Spline) {
        int b_loop_ub;
        int c_loop_ub;
        int i1;
        int i2;
        int i3;
        int i7;
        int i8;
        int k;
        // 'cutCurvStructU:17' u1_tilda = splineLengthFindU( ctx, curv, L, a * u0 + b, isEnd );
        //  Computes approximately the value of curve parameter u such that the arc
        //  length starting from u1 equals L.
        //  This function takes usage of the precalculated arc lengths between knots.
        //  The last integration interval is approximated by the trapezoidal rule.
        //  u1 must satisfy 0 < u1 < 1.
        //  In the normal case, u must satisfy 0 < u < u1. If L is too large, u is
        //  set to -1
        //  Warning : This function works only for B-spline of degree 3
        //  Get the sp structure
        // 'splineLengthFindU:12' spline = ctx.q_spline.get( curv.sp_index );
        ctx_q_spline->get(curv_sp_index, &expl_temp);
        // 'splineLengthFindU:13' sp     = spline.sp;
        // 'splineLengthFindU:15' DEFAULT_TOL_NR  = 1e-6;
        //  Default tolerance for Newton Raphson
        // 'splineLengthFindU:16' IND_KNOTS_MULT  = sp.Bl.order;
        //  Index used to remove multiple knots
        //                               (ONLY TRUE FOR CUBIC SPLINE)
        //  Eliminate multiplicities at the end points
        // 'splineLengthFindU:20' Knots  = sp.knots( 1, IND_KNOTS_MULT : end - IND_KNOTS_MULT + 1 );
        i1 = (expl_temp.sp.knots.size(1) - expl_temp.sp.Bl.order) + 1;
        if (expl_temp.sp.Bl.order > i1) {
            i2 = 0;
            i3 = 0;
        } else {
            i2 = expl_temp.sp.Bl.order - 1;
            i3 = i1;
        }
        // 'splineLengthFindU:21' Lk     = sp.Lk;
        // 'splineLengthFindU:22' KMax   = length( Lk );
        // 'splineLengthFindU:24' if( isEnd )
        //
        // 'splineLengthFindU:29' C_ASSERT_MSG = 'u1 must be %s or equal than the first spline
        // knot'; 'splineLengthFindU:30' c_assert( u1 >= Knots(1),   sprintf(C_ASSERT_MSG,
        // 'greater') ); 'c_assert:2' if coder.target('rtw') 'c_assert:3' if ~condition
        if (curv_b_param < expl_temp.sp.knots[i2]) {
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i4{0}; i4 < 54; i4++) {
                message[i4] = cv1[i4];
            }
            c_assert_(&message[0]);
        }
        // 'c_assert:6' value = condition;
        // 'splineLengthFindU:31' c_assert( u1 <= Knots(end), sprintf(C_ASSERT_MSG, 'smaller') );
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        if (curv_b_param > expl_temp.sp.knots[i3 - 1]) {
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i5{0}; i5 < 54; i5++) {
                message[i5] = cv2[i5];
            }
            c_assert_(&message[0]);
        }
        // 'c_assert:6' value = condition;
        //
        // 'splineLengthFindU:33' k_vec = find( Knots < u1 );
        b_loop_ub = i3 - i2;
        b_expl_temp.set_size(1, b_loop_ub);
        for (int i6{0}; i6 < b_loop_ub; i6++) {
            b_expl_temp[i6] = (expl_temp.sp.knots[i2 + i6] < curv_b_param);
        }
        coder::eml_find(b_expl_temp, k_vec);
        // 'splineLengthFindU:34' if( isempty( k_vec ) )
        if (k_vec.size(1) == 0) {
            // 'splineLengthFindU:35' k = 1;
            k = 0;
        } else {
            // 'splineLengthFindU:36' else
            // 'splineLengthFindU:37' k = k_vec( end );
            k = k_vec[k_vec.size(1) - 1] - 1;
        }
        // 'splineLengthFindU:40' if( isEnd )
        // 'splineLengthFindU:43' else
        // 'splineLengthFindU:44' if( L > sum( Lk( k : end ) ) )
        if (k + 1 > expl_temp.sp.Lk.size(1)) {
            i7 = 0;
            i8 = 0;
        } else {
            i7 = k;
            i8 = expl_temp.sp.Lk.size(1);
        }
        c_loop_ub = i8 - i7;
        c_expl_temp.set_size(1, c_loop_ub);
        for (int i9{0}; i9 < c_loop_ub; i9++) {
            c_expl_temp[i9] = expl_temp.sp.Lk[i7 + i9];
        }
        if (L > coder::sum(c_expl_temp)) {
            // 'splineLengthFindU:44' u = 1;
            u1_tilda = 1.0;
        } else {
            double Lcum;
            double Lremain;
            double u1;
            double uk;
            double uk_old;
            //
            //  Length to next break point
            // 'splineLengthFindU:49' Lcum = Lk( k ) - SplineLengthApprox_Interval1( ctx, curv,
            // Knots( k ), u1 );
            Lcum = expl_temp.sp.Lk[k] -
                   SplineLengthApprox_Interval1(ctx_q_spline, ctx_cfg_GaussLegendreX,
                                                ctx_cfg_GaussLegendreW, curv_sp_index,
                                                expl_temp.sp.knots[i2 + k], curv_b_param);
            //
            // 'splineLengthFindU:51' while ( Lcum < L ) && ( k < KMax )
            while ((Lcum < L) && (k + 1 < expl_temp.sp.Lk.size(1))) {
                // 'splineLengthFindU:52' k = k + 1;
                k++;
                // 'splineLengthFindU:53' Lcum = Lcum + Lk( k );
                Lcum += expl_temp.sp.Lk[k];
                //  Sum up precalculated length between knots
            }
            int u1_tmp;
            //  undo last increment
            // 'splineLengthFindU:57' k         = k - 1;
            // 'splineLengthFindU:58' Lcum      = Lcum - Lk( k );
            Lcum -= expl_temp.sp.Lk[k - 1];
            // 'splineLengthFindU:59' Lremain   = L - Lcum;
            Lremain = L - Lcum;
            //
            // 'splineLengthFindU:62' u1     = Knots( k+1 );
            u1_tmp = i2 + k;
            u1 = expl_temp.sp.knots[u1_tmp];
            //  Initial guess for Newton Raphson iteration
            // 'splineLengthFindU:64' uk     = 0.5 * ( Knots( k ) + Knots( k + 1 ) );
            uk = 0.5 * (expl_temp.sp.knots[u1_tmp - 1] + expl_temp.sp.knots[u1_tmp]);
            //  Dummy value to ensure that while loop enters
            // 'splineLengthFindU:66' uk_old = 2;
            uk_old = 2.0;
            //  Iterate until new value of uk is close to old value
            // 'splineLengthFindU:69' while abs( uk - uk_old ) > DEFAULT_TOL_NR
            while (std::abs(uk - uk_old) > 1.0E-6) {
                double fk;
                int d_loop_ub;
                int e_loop_ub;
                int f_loop_ub;
                int g_loop_ub;
                int i14;
                int i_loop_ub;
                //  Evaluation of function which should become zero
                // 'splineLengthFindU:71' fk = SplineLengthApprox_Interval1( ctx, curv, uk, u1 ) -
                // Lremain;
                fk = SplineLengthApprox_Interval1(ctx_q_spline, ctx_cfg_GaussLegendreX,
                                                  ctx_cfg_GaussLegendreW, curv_sp_index, uk, u1) -
                     Lremain;
                // 'splineLengthFindU:72' [ ~, r1D ]  = EvalBSpline( spline, uk );
                //  EvalBSpline
                //
                //  INPUT
                //  spline        : struct : Spline structure
                //  u_vec         :    1xn : Vector for evaluation of the curv
                //
                //  OUTPUT
                //  r0D           :   nDxn : The evaluated B spline at u\_vec points
                //  r1D           :   nDxn : 1rst order parametric derivative for the B spline at
                //  u\_vec points r2D           :   nDxn : 2nd order parametric derivative for the B
                //  spline at u\_vec points r3D           :   nDxn : 3rd order parametric derivative
                //  for the B spline at u\_vec points
                // 'EvalBSpline:14' sp = spline.sp;
                // 'EvalBSpline:15' N  = length( u_vec );
                // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
                // 'EvalBSpline:18' r0D = zeros( M, N );
                a__1.set_size(expl_temp.sp.coeff.size(0));
                d_loop_ub = expl_temp.sp.coeff.size(0);
                for (int i10{0}; i10 < d_loop_ub; i10++) {
                    a__1[i10] = 0.0;
                }
                // 'EvalBSpline:18' r1D = r0D;
                r1D.set_size(expl_temp.sp.coeff.size(0));
                e_loop_ub = expl_temp.sp.coeff.size(0);
                for (int i11{0}; i11 < e_loop_ub; i11++) {
                    r1D[i11] = 0.0;
                }
                // 'EvalBSpline:18' r2D = r1D;
                r2D.set_size(expl_temp.sp.coeff.size(0));
                f_loop_ub = expl_temp.sp.coeff.size(0);
                for (int i12{0}; i12 < f_loop_ub; i12++) {
                    r2D[i12] = 0.0;
                }
                // 'EvalBSpline:18' r3D = r2D;
                r3D.set_size(expl_temp.sp.coeff.size(0));
                g_loop_ub = expl_temp.sp.coeff.size(0);
                for (int i13{0}; i13 < g_loop_ub; i13++) {
                    r3D[i13] = 0.0;
                }
                // 'EvalBSpline:20' for j = 1 : M
                i14 = expl_temp.sp.coeff.size(0);
                for (int j{0}; j < i14; j++) {
                    int h_loop_ub;
                    // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] =
                    // ... 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl,
                    // sp.coeff( j, : ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
                    // 'bspline_eval_vec:4' xd      = zeros(size(u));
                    // 'bspline_eval_vec:5' xdd     = zeros(size(u));
                    // 'bspline_eval_vec:6' xddd    = zeros(size(u));
                    // 'bspline_eval_vec:8' for k = 1:length(u)
                    // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
                    a__1[j] = uk;
                    h_loop_ub = expl_temp.sp.coeff.size(1);
                    c_expl_temp.set_size(1, expl_temp.sp.coeff.size(1));
                    for (int i15{0}; i15 < h_loop_ub; i15++) {
                        c_expl_temp[i15] = expl_temp.sp.coeff[j + expl_temp.sp.coeff.size(0) * i15];
                    }
                    bspline_eval(expl_temp.sp.Bl.handle, c_expl_temp, &a__1[j], &d, &d1, &d2);
                    r3D[j] = d2;
                    r2D[j] = d1;
                    r1D[j] = d;
                    // 'bspline_eval_vec:10' x(k)    = xk;
                    // 'bspline_eval_vec:11' xd(k)   = xdk;
                    // 'bspline_eval_vec:12' xdd(k)  = xddk;
                    // 'bspline_eval_vec:13' xddd(k) = xdddk;
                }
                //  Evaluation of the derivative of the function which should become zero
                // 'splineLengthFindU:74' Dfk    = -MyNorm(r1D);
                // 'MyNorm:2' coder.inline('always');
                // 'MyNorm:3' n = mysqrt(sum(x.^2));
                // 'mysqrt:3' y = sqrt(x);
                // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                sqrt_calls++;
                //
                // 'splineLengthFindU:76' uk_old = uk;
                uk_old = uk;
                // 'splineLengthFindU:77' uk     = uk_old - fk / Dfk;
                r.set_size(r1D.size(0));
                i_loop_ub = r1D.size(0);
                for (int i16{0}; i16 < i_loop_ub; i16++) {
                    double b_varargin_1;
                    b_varargin_1 = r1D[i16];
                    r[i16] = std::pow(b_varargin_1, 2.0);
                }
                uk -= fk / -std::sqrt(coder::combineVectorElements(r));
                //  Newton Raphson update
                // 'splineLengthFindU:78' if uk > u1
                if (uk > u1) {
                    // 'splineLengthFindU:79' uk = u1;
                    uk = u1;
                    //  Make sure not to run away
                }
            }
            //
            // 'splineLengthFindU:83' u  = uk;
            u1_tilda = uk;
        }
    } else {
        int loop_ub;
        // 'cutCurvStructU:18' else
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        // 'cutCurvStructU:22' if( isEnd )
        // 'cutCurvStructU:25' else
        // 'cutCurvStructU:26' [ ~, r1D0 ] = EvalCurvStruct( ctx, curv, 0 );
        c_EvalCurvStruct(ctx_q_spline, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                         ctx_cfg_indCart_data, ctx_cfg_indCart_size, ctx_cfg_indRot_data,
                         ctx_cfg_indRot_size, ctx_cfg_indTot_data, ctx_cfg_indTot_size,
                         curv_Info_Type, curv_R0, curv_R1, curv_CorrectedHelixCenter, curv_evec,
                         curv_theta, curv_pitch, curv_CoeffP5, curv_sp_index, curv_a_param,
                         curv_b_param, a__2, r1D0);
        // 'cutCurvStructU:27' u1 = u0 + L / MyNorm( r1D0 );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'cutCurvStructU:29' u1_tilda = a * u1 + b;
        r.set_size(r1D0.size(0));
        loop_ub = r1D0.size(0);
        for (int i{0}; i < loop_ub; i++) {
            double varargin_1;
            varargin_1 = r1D0[i];
            r[i] = std::pow(varargin_1, 2.0);
        }
        u1_tilda = curv_a_param * (L / std::sqrt(coder::combineVectorElements(r))) + curv_b_param;
    }
    return u1_tilda;
}

} // namespace ocn

//
// File trailer for cutCurvStructU.cpp
//
// [EOF]
//
