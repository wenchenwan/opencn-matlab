
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutZeroEnd.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "cutZeroEnd.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "LengthCurv.h"
#include "ocn_assert.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include "splineLengthFindU.h"
#include "sum.h"
#include "zeroSpeedCurv.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [ ret, curv1, curv2 ] = cutZeroEnd( ctx, curv )
//
// cutZeroEnd : Cut the end of the given to handle the zero speed.
//
//  Inputs :
//  ctx       : The context used in the computational chain.
//  curv      : The curve to cut the end.
//
//  Outputs :
//  ret       : The returned value of the operation : 1 means
//  curvLeft  : Resulting NN Curve struct
//  curvRight : Resulting NZ Curve struct with constant jerk speed profile
//
//
// Arguments    : const queue_coder *ctx_q_spline
//                const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                const bool ctx_cfg_maskCart_data[]
//                const int ctx_cfg_maskCart_size[2]
//                const bool ctx_cfg_maskRot_data[]
//                const int ctx_cfg_maskRot_size[2]
//                const ::coder::array<int, 1U> &ctx_cfg_indCart
//                const ::coder::array<int, 1U> &ctx_cfg_indRot
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const double ctx_cfg_vmax[6]
//                const double ctx_cfg_amax[6]
//                const double ctx_cfg_jmax[6]
//                double ctx_cfg_LSplitZero
//                double ctx_cfg_dt
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const Kinematics *ctx_kin
//                const CurvStruct *curv
//                double *ret
//                CurvStruct *curv1
//                CurvStruct *curv2
// Return Type  : void
//
namespace ocn {
void cutZeroEnd(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
                const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_vmax[6],
                const double ctx_cfg_amax[6], const double ctx_cfg_jmax[6],
                double ctx_cfg_LSplitZero, double ctx_cfg_dt,
                const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
                const Kinematics *ctx_kin, const CurvStruct *curv, double *ret, CurvStruct *curv1,
                CurvStruct *curv2)
{
    static const signed char ind1[2][3]{{1, 1, 2}, {1, 2, 2}};
    static const signed char ind2[2][3]{{2, 3, 3}, {1, 2, 1}};
    Kinematics b_ctx_kin;
    Kinematics c_ctx_kin;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> a__4;
    ::coder::array<double, 2U> a__5;
    ::coder::array<double, 2U> a__6;
    ::coder::array<double, 2U> b_a__1;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> b_z1;
    ::coder::array<double, 1U> c_x;
    ::coder::array<double, 1U> c_z1;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D1;
    ::coder::array<double, 1U> z1;
    ::coder::array<bool, 1U> d_x;
    CurvStruct curv_vec[3];
    CurvStruct b_curv1;
    CurvStruct b_curv2;
    CurvStruct expl_temp;
    double L;
    double Lcut;
    double u_tilda;
    int b_ret;
    signed char tmp_data[6];
    // 'cutZeroEnd:14' L       = LengthCurv( ctx, curv, 0, 1 );
    L = c_LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                     curv);
    // 'cutZeroEnd:15' Lcut    = ctx.cfg.LSplitZero;
    Lcut = ctx_cfg_LSplitZero;
    // 'cutZeroEnd:17' if( Lcut > L / 3 )
    if (ctx_cfg_LSplitZero > L / 3.0) {
        // 'cutZeroEnd:17' Lcut = L / 3;
        Lcut = L / 3.0;
    }
    // 'cutZeroEnd:19' [ ret, curv1, curv2 ] = cutCurvStruct( ctx, curv, 1, Lcut, true );
    //  cutCurvStruct: Cut a piece of the structure with a size of L
    //  starting at point u0.
    //
    //  Inputs :
    //  ctx   : Context
    //  curv  : Curvature
    //  u0    : Starting point of the spline
    //  L     : Length of the segment of curv
    //  isEnd : Is a zero stop curv
    //
    //  Outputs :
    //  ret       : Return 0 if operation fails
    //  curvLeft  : Left curve after cutting
    //  curvRight : Right curve after cutting
    //
    // 'cutCurvStruct:18' curvLeft = curv;
    *curv1 = *curv;
    // 'cutCurvStruct:18' curvRight = curvLeft;
    *curv2 = *curv1;
    // 'cutCurvStruct:19' ret   = 0;
    b_ret = 0;
    // 'cutCurvStruct:21' u_tilda = cutCurvStructU( ctx, curv, u0, L, isEnd );
    //  cutCurvStructU : Cut a piece of the structure with a size of L
    //  starting at point u0.
    //
    //  Inputs :
    //  ctx       : Context
    //  curv      : Curvature
    //  u0        : Starting point of the spline
    //  L         : Length of the segment of curv
    //  isEnd     : Is a cut from the end
    //
    //  Outputs :
    //  u1_tilda  : The last point of the splitted curve. A value of -1 means a
    //              faillure of the operation.
    //
    // 'cutCurvStructU:18' if( LengthCurv( ctx, curv, 0, 1 ) <= L )
    if (c_LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                     curv) <= Lcut) {
        // 'cutCurvStructU:18' u1_tilda = -1;
        u_tilda = -1.0;

        // 'cutCurvStructU:20' a = curv.a_param;
        // 'cutCurvStructU:21' b = curv.b_param;
        // 'cutCurvStructU:23' if ( curv.Info.Type == CurveType.Spline )
    } else if (curv->Info.Type == CurveType_Spline) {
        // 'cutCurvStructU:24' spline = ctx.q_spline.get( curv.sp_index );
        ctx_q_spline->get(curv->sp_index, &expl_temp);
        // 'cutCurvStructU:25' u1_tilda = splineLengthFindU( ctx.cfg, spline, L, a * u0 + b, isEnd
        // );
        u_tilda = b_splineLengthFindU(ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                                      expl_temp.sp.Bl.handle, expl_temp.sp.Bl.order,
                                      expl_temp.sp.coeff, expl_temp.sp.knots, expl_temp.sp.Lk, Lcut,
                                      curv->a_param + curv->b_param);
    } else {
        int loop_ub;
        // 'cutCurvStructU:26' else
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        // 'cutCurvStructU:30' if( isEnd )
        // 'cutCurvStructU:31' [ ~, r1D1 ] = EvalCurvStruct( ctx, curv, 1 );
        n_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, a__1, r1D1);
        // 'cutCurvStructU:32' u1 = u0 - L / MyNorm( r1D1 );
        //  MyNorm : My implementation of the norm computation.
        //
        //  Inputs :
        //    x   : The input vector.
        //
        //  Outputs :
        //    n   : The resulting norm.
        //
        // 'MyNorm:10' coder.inline( 'always' );
        // 'MyNorm:11' n = mysqrt( sum( x.^2 ) );
        r.set_size(r1D1.size(0));
        loop_ub = r1D1.size(0);
        for (int i{0}; i < loop_ub; i++) {
            double varargin_1;
            varargin_1 = r1D1[i];
            r[i] = std::pow(varargin_1, 2.0);
        }
        double b_x;
        b_x = coder::sum(r);
        //  mysqrt : Custom implementation of the sqrt method.
        //
        //  Inputs :
        //    x : Value used for the computation
        //  Outputs :
        //    y : Resulting value
        //
        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
        ocn_assert(b_x >= 0.0);
        // 'mysqrt:11' y = sqrt(x);
        // 'cutCurvStructU:37' u1_tilda = a * u1 + b;
        u_tilda = curv->a_param * (1.0 - Lcut / std::sqrt(b_x)) + curv->b_param;
    }
    // 'cutCurvStruct:23' if( u_tilda <= 0 )
    if (u_tilda <= 0.0) {
        // 'cutCurvStruct:23' ret = -1;
        b_ret = -1;
    } else {
        double b_curv_a_param;
        double curv_a_param;
        double curv_b_param;
        bool b_valid;
        bool b_zeroFlag;
        bool valid;
        bool zeroFlag;
        // 'cutCurvStruct:25' a = curv.a_param;
        // 'cutCurvStruct:26' b = curv.b_param;
        // 'cutCurvStruct:28' curvRight.b_param = u_tilda;
        curv2->b_param = u_tilda;
        // 'cutCurvStruct:29' curvRight.a_param = a + b - curvRight.b_param;
        curv2->a_param = (curv->a_param + curv->b_param) - u_tilda;
        // 'cutCurvStruct:31' if( isAZeroEnd( curvRight ) )
        //  isAZeroEnd : Return true if the curv ends with zero speed
        //
        //  Inputs :
        //  curv / Info / ZSpdMode : A structure containning the information of the
        //  curv zero speed.
        //
        //  Outputs :
        //  zeroFlag : Boolean value. TRUE mean zero flag
        // 'isAZeroEnd:10' zeroFlag = false;
        zeroFlag = false;
        // 'isAZeroEnd:12' [zspdmode, error] = getZspdmode( speed );
        //  getZspdmode: Get the current zero speed mode
        //
        //  Inputs :
        //    speed    : structure with zspdmode for the speed
        //
        //  Outputs :
        //    zspdmode : Zero speed mode
        //    error    : Error bolean value. TRUE if no zspdmode has been found.
        //
        // 'getZspdmode:13' error = false;
        // 'getZspdmode:15' if( isenum( speed ) )
        // 'getZspdmode:17' elseif( isfield( speed, "Info") )
        // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
        // 'isAZeroEnd:14' if( error )
        // 'isAZeroEnd:16' if( zspdmode == ZSpdMode.NZ || ...
        // 'isAZeroEnd:17'     zspdmode == ZSpdMode.ZZ )
        if ((curv2->Info.zspdmode == ZSpdMode_NZ) || (curv2->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroEnd:18' zeroFlag = true;
            zeroFlag = true;
        }
        if (zeroFlag) {
            // 'cutCurvStruct:32' curvRight.Info.zspdmode = ZSpdMode.NZ;
            curv2->Info.zspdmode = ZSpdMode_NZ;
        } else {
            // 'cutCurvStruct:33' else
            // 'cutCurvStruct:34' curvRight.Info.zspdmode = ZSpdMode.NN;
            curv2->Info.zspdmode = ZSpdMode_NN;
        }
        // 'cutCurvStruct:37' ocn_assert( checkParametrisation( curvRight ), ...
        // 'cutCurvStruct:38'     "Parametrisation is not correct...", mfilename );
        curv_a_param = curv2->a_param;
        //  checkParametrisation : Check whether the curv parametrisation is correct
        //  or not.
        //
        //  Inputs :
        //    curv        : A curvStruct
        //
        //  Outputs :
        //    valid       : Boolean value, TRUE means the parametrisation is sound.
        //
        // 'checkParametrisation:11' valid = false;
        valid = false;
        // 'checkParametrisation:12' if( ~(curv.a_param > 0 && curv.a_param <= 1) )
        if ((curv_a_param > 0.0) && (curv_a_param <= 1.0) && (u_tilda >= 0.0) && (u_tilda < 1.0) &&
            ((curv_a_param + u_tilda) - 1.0 <= 2.2204460492503131E-16)) {
            // 'checkParametrisation:13' if( ~(curv.b_param >= 0 && curv.b_param < 1) )
            // 'checkParametrisation:14' if( curv.a_param + curv.b_param -1 > eps )
            // 'checkParametrisation:15' valid = true;
            valid = true;
        }
        v_ocn_assert(valid);
        // 'cutCurvStruct:40' curvLeft.a_param = u_tilda - curvLeft.b_param;
        curv1->a_param = u_tilda - curv1->b_param;
        // 'cutCurvStruct:41' if( isAZeroStart( curvLeft ) )
        //  isAZeroStart : Return true if the curv starts with zero speed
        //
        //  Inputs :
        //  curv / Info / ZSpdMode : A structure containning the information of the
        //  curv zero speed.
        //
        //  Outputs :
        //  zeroflag : Boolean value. TRUE means zero structure with a zero speed.
        //
        // 'isAZeroStart:11' zeroFlag = false;
        b_zeroFlag = false;
        // 'isAZeroStart:13' [zspdmode, error] = getZspdmode( speed );
        //  getZspdmode: Get the current zero speed mode
        //
        //  Inputs :
        //    speed    : structure with zspdmode for the speed
        //
        //  Outputs :
        //    zspdmode : Zero speed mode
        //    error    : Error bolean value. TRUE if no zspdmode has been found.
        //
        // 'getZspdmode:13' error = false;
        // 'getZspdmode:15' if( isenum( speed ) )
        // 'getZspdmode:17' elseif( isfield( speed, "Info") )
        // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
        // 'isAZeroStart:15' if( error )
        // 'isAZeroStart:17' if( zspdmode == ZSpdMode.ZN || ...
        // 'isAZeroStart:18'     zspdmode == ZSpdMode.ZZ )
        if ((curv1->Info.zspdmode == ZSpdMode_ZN) || (curv1->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroStart:19' zeroFlag = true;
            b_zeroFlag = true;
        }
        if (b_zeroFlag) {
            // 'cutCurvStruct:42' curvLeft.Info.zspdmode = ZSpdMode.ZN;
            curv1->Info.zspdmode = ZSpdMode_ZN;
        } else {
            // 'cutCurvStruct:43' else
            // 'cutCurvStruct:44' curvLeft.Info.zspdmode = ZSpdMode.NN;
            curv1->Info.zspdmode = ZSpdMode_NN;
        }
        // 'cutCurvStruct:47' ocn_assert( checkParametrisation( curvLeft ), ...
        // 'cutCurvStruct:48'     "Parametrisation is not correct...", mfilename  );
        b_curv_a_param = curv1->a_param;
        curv_b_param = curv1->b_param;
        //  checkParametrisation : Check whether the curv parametrisation is correct
        //  or not.
        //
        //  Inputs :
        //    curv        : A curvStruct
        //
        //  Outputs :
        //    valid       : Boolean value, TRUE means the parametrisation is sound.
        //
        // 'checkParametrisation:11' valid = false;
        b_valid = false;
        // 'checkParametrisation:12' if( ~(curv.a_param > 0 && curv.a_param <= 1) )
        if ((b_curv_a_param > 0.0) && (b_curv_a_param <= 1.0) && (curv_b_param >= 0.0) &&
            (curv_b_param < 1.0) &&
            ((b_curv_a_param + curv_b_param) - 1.0 <= 2.2204460492503131E-16)) {
            // 'checkParametrisation:13' if( ~(curv.b_param >= 0 && curv.b_param < 1) )
            // 'checkParametrisation:14' if( curv.a_param + curv.b_param -1 > eps )
            // 'checkParametrisation:15' valid = true;
            b_valid = true;
        }
        v_ocn_assert(b_valid);
    }
    // 'cutZeroEnd:21' if( ret < 0 )
    if (b_ret < 0) {
        // 'cutZeroEnd:22' curv1 = curv;
        *curv1 = *curv;
        // 'cutZeroEnd:23' curv1.UseConstJerk      = true;
        curv1->UseConstJerk = true;
        // 'cutZeroEnd:24' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1, true );
        b_ctx_kin = *ctx_kin;
        b_curv1 = *curv1;
        b_zeroSpeedCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                        ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                        ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_vmax, ctx_cfg_amax, ctx_cfg_jmax,
                        ctx_cfg_dt, &b_ctx_kin, &b_curv1, b_a__1, a__2, a__3, &curv1->ConstJerk);
        // 'cutZeroEnd:25' curv1.ConstJerk         = jps;
    } else {
        double r_data[36];
        double rd_data[36];
        double rdd_data[36];
        double x;
        int end;
        int partialTrueCount;
        int rd;
        int rdd;
        int trueCount;
        // 'cutZeroEnd:26' else
        // 'cutZeroEnd:27' ocn_assert( check_curv_length( ctx, curv2, Lcut ), "Curve Length not
        // valide", mfilename ); 'cutZeroStart:112' tol = 1E-1; 'cutZeroStart:114' isValid = ( abs(
        // LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
        x = c_LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX,
                         ctx_cfg_GaussLegendreW, curv2) -
            Lcut;
        fb_ocn_assert(std::abs(x) <= 0.1);
        // 'cutZeroEnd:28' curv2.UseConstJerk      = true;
        curv2->UseConstJerk = true;
        // 'cutZeroEnd:29' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2, true );
        c_ctx_kin = *ctx_kin;
        b_curv2 = *curv2;
        b_zeroSpeedCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                        ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                        ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_vmax, ctx_cfg_amax, ctx_cfg_jmax,
                        ctx_cfg_dt, &c_ctx_kin, &b_curv2, a__4, a__5, a__6, &curv2->ConstJerk);
        // 'cutZeroEnd:30' curv2.ConstJerk         = jps;
        // 'cutZeroEnd:31' curv1.UseConstJerk      = false;
        curv1->UseConstJerk = false;
        // 'cutZeroEnd:32' check_continuity( ctx, curv, curv1, curv2 );
        // 'cutZeroEnd:64' curv_vec    = [ curv; curv1; curv2 ];
        curv_vec[0] = *curv;
        curv_vec[1] = *curv1;
        curv_vec[2] = *curv2;
        // 'cutZeroEnd:65' u_vec       = [ 0, 1 ];
        // 'cutZeroEnd:66' r           = repmat( curv.R0( ctx.cfg.maskTot ), 1, 2, 3 );
        end = ctx_cfg_maskTot_size[1] - 1;
        trueCount = 0;
        partialTrueCount = 0;
        for (int b_i{0}; b_i <= end; b_i++) {
            if (ctx_cfg_maskTot_data[b_i]) {
                trueCount++;
                tmp_data[partialTrueCount] = static_cast<signed char>(b_i + 1);
                partialTrueCount++;
            }
        }
        if (trueCount != 0) {
            for (int t{0}; t < 3; t++) {
                for (int b_t{0}; b_t < 2; b_t++) {
                    for (int k{0}; k < trueCount; k++) {
                        r_data[(k + trueCount * b_t) + trueCount * 2 * t] =
                            curv->R0[tmp_data[k] - 1];
                    }
                }
            }
        }
        // 'cutZeroEnd:67' rd          = r;
        // 'cutZeroEnd:68' rdd         = r;
        for (int i1{0}; i1 < 3; i1++) {
            for (int i2{0}; i2 < 2; i2++) {
                for (int i3{0}; i3 < trueCount; i3++) {
                    double d;
                    d = r_data[(i3 + trueCount * i2) + trueCount * 2 * i1];
                    rd_data[(i3 + trueCount * i2) + trueCount * 2 * i1] = d;
                    rdd_data[(i3 + trueCount * i2) + trueCount * 2 * i1] = d;
                }
            }
        }
        // 'cutZeroEnd:70' for j = 1 : 3
        rd = trueCount - 1;
        rdd = trueCount - 1;
        for (int j{0}; j < 3; j++) {
            double b_rd_data[12];
            double b_rdd_data[12];
            double c;
            int b_loop_ub;
            int c_loop_ub;
            int d_loop_ub;
            // 'cutZeroEnd:71' [ r( :, :, j ) , rd( :, :, j ), rdd( :, :, j ) ] = ...
            // 'cutZeroEnd:72'         EvalCurvStruct( ctx, curv_vec( j ),  u_vec );
            j_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                             ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                             ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot,
                             ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot, &curv_vec[j], r1, r2,
                             r3);
            b_loop_ub = r1.size(0);
            c_loop_ub = r2.size(0);
            d_loop_ub = r3.size(0);
            for (int i4{0}; i4 < 2; i4++) {
                for (int i5{0}; i5 < b_loop_ub; i5++) {
                    r_data[(i5 + trueCount * i4) + trueCount * 2 * j] = r1[i5 + r1.size(0) * i4];
                }
                for (int i7{0}; i7 < c_loop_ub; i7++) {
                    rd_data[(i7 + trueCount * i4) + trueCount * 2 * j] = r2[i7 + r2.size(0) * i4];
                }
                for (int i9{0}; i9 < d_loop_ub; i9++) {
                    rdd_data[(i9 + trueCount * i4) + trueCount * 2 * j] = r3[i9 + r3.size(0) * i4];
                }
            }
            // 'cutZeroEnd:73' rd( :, :, j )    = rd( :, :, j )  / curv_vec( j ).a_param;
            for (int i6{0}; i6 < 2; i6++) {
                for (int i8{0}; i8 <= rd; i8++) {
                    b_rd_data[i8 + trueCount * i6] =
                        rd_data[(i8 + trueCount * i6) + trueCount * 2 * j] / curv_vec[j].a_param;
                }
            }
            double c_tmp;
            // 'cutZeroEnd:74' if( 1 )
            // 'cutZeroEnd:75' rdd( :, :, j )   = rdd( :, :, j ) / curv_vec( j ).a_param^2;
            c_tmp = curv_vec[j].a_param;
            c = c_tmp * c_tmp;
            for (int i11{0}; i11 < 2; i11++) {
                for (int i14{0}; i14 < trueCount; i14++) {
                    rd_data[(i14 + trueCount * i11) + trueCount * 2 * j] =
                        b_rd_data[i14 + trueCount * i11];
                }
                for (int i17{0}; i17 <= rdd; i17++) {
                    b_rdd_data[i17 + trueCount * i11] =
                        rdd_data[(i17 + trueCount * i11) + trueCount * 2 * j] / c;
                }
            }
            for (int i13{0}; i13 < 2; i13++) {
                for (int i16{0}; i16 < trueCount; i16++) {
                    rdd_data[(i16 + trueCount * i13) + trueCount * 2 * j] =
                        b_rdd_data[i16 + trueCount * i13];
                }
            }
        }
        // 'cutZeroEnd:81' ind1 = [ 1, 1; 1, 2; 2, 2 ];
        // 'cutZeroEnd:82' ind2 = [ 2, 1; 3, 2; 3, 1 ];
        // 'cutZeroEnd:84' for j = 1 : 3
        for (int b_j{0}; b_j < 3; b_j++) {
            int e_k;
            int e_loop_ub;
            int f_k;
            int f_loop_ub;
            int g_k;
            int g_loop_ub;
            bool b_varargout_1;
            bool c_varargout_1;
            bool exitg1;
            bool varargout_1;
            // 'cutZeroEnd:85' r1   = r( : , ind1( j, 2 ), ind1( j, 1 ) );
            // 'cutZeroEnd:86' r1d  = rd( : , ind1( j, 2 ), ind1( j, 1 ) );
            // 'cutZeroEnd:87' r1dd = rdd( : , ind1( j, 2 ), ind1( j, 1 ) );
            // 'cutZeroEnd:88' r2   = r( : , ind2( j, 2 ), ind2( j, 1 ) );
            // 'cutZeroEnd:89' r2d  = rd( : , ind2( j, 2 ), ind2( j, 1 ) );
            // 'cutZeroEnd:90' r2dd = rdd( : , ind2( j, 2 ), ind2( j, 1 ) );
            // 'cutZeroEnd:91' assert_continuity( r1, r1d, r1dd, r2, r2d, r2dd );
            // 'cutZeroEnd:98' diff_r      = abs( r1    -r2 );
            c_x.set_size(trueCount);
            for (int i10{0}; i10 < trueCount; i10++) {
                c_x[i10] = r_data[(i10 + trueCount * (ind1[1][b_j] - 1)) +
                                  trueCount * 2 * (ind1[0][b_j] - 1)] -
                           r_data[(i10 + trueCount * (ind2[1][b_j] - 1)) +
                                  trueCount * 2 * (ind2[0][b_j] - 1)];
            }
            z1.set_size(c_x.size(0));
            if (c_x.size(0) != 0) {
                int i12;
                i12 = c_x.size(0);
                for (int b_k{0}; b_k < i12; b_k++) {
                    z1[b_k] = std::abs(c_x[b_k]);
                }
            }
            // 'cutZeroEnd:99' diff_rd     = abs( r1d   -r2d );
            c_x.set_size(trueCount);
            for (int i15{0}; i15 < trueCount; i15++) {
                c_x[i15] = rd_data[(i15 + trueCount * (ind1[1][b_j] - 1)) +
                                   trueCount * 2 * (ind1[0][b_j] - 1)] -
                           rd_data[(i15 + trueCount * (ind2[1][b_j] - 1)) +
                                   trueCount * 2 * (ind2[0][b_j] - 1)];
            }
            b_z1.set_size(c_x.size(0));
            if (c_x.size(0) != 0) {
                int i18;
                i18 = c_x.size(0);
                for (int c_k{0}; c_k < i18; c_k++) {
                    b_z1[c_k] = std::abs(c_x[c_k]);
                }
            }
            // 'cutZeroEnd:100' diff_rdd    = abs( r1dd  -r2dd );
            c_x.set_size(trueCount);
            for (int i19{0}; i19 < trueCount; i19++) {
                c_x[i19] = rdd_data[(i19 + trueCount * (ind1[1][b_j] - 1)) +
                                    trueCount * 2 * (ind1[0][b_j] - 1)] -
                           rdd_data[(i19 + trueCount * (ind2[1][b_j] - 1)) +
                                    trueCount * 2 * (ind2[0][b_j] - 1)];
            }
            c_z1.set_size(c_x.size(0));
            if (c_x.size(0) != 0) {
                int i20;
                i20 = c_x.size(0);
                for (int d_k{0}; d_k < i20; d_k++) {
                    c_z1[d_k] = std::abs(c_x[d_k]);
                }
            }
            // 'cutZeroEnd:102' tol = 1E-9;
            // 'cutZeroEnd:104' ocn_assert( all( diff_r    < tol, 'all' ), "Continuity C0 failed",
            // mfilename );
            d_x.set_size(z1.size(0));
            e_loop_ub = z1.size(0);
            for (int i21{0}; i21 < e_loop_ub; i21++) {
                d_x[i21] = (z1[i21] < 1.0E-9);
            }
            varargout_1 = true;
            e_k = 0;
            exitg1 = false;
            while ((!exitg1) && (e_k <= d_x.size(0) - 1)) {
                if (!d_x[e_k]) {
                    varargout_1 = false;
                    exitg1 = true;
                } else {
                    e_k++;
                }
            }
            gb_ocn_assert(varargout_1);
            // 'cutZeroEnd:105' ocn_assert( all( diff_rd   < tol, 'all' ), "Continuity C1 failed",
            // mfilename );
            d_x.set_size(b_z1.size(0));
            f_loop_ub = b_z1.size(0);
            for (int i22{0}; i22 < f_loop_ub; i22++) {
                d_x[i22] = (b_z1[i22] < 1.0E-9);
            }
            b_varargout_1 = true;
            f_k = 0;
            exitg1 = false;
            while ((!exitg1) && (f_k <= d_x.size(0) - 1)) {
                if (!d_x[f_k]) {
                    b_varargout_1 = false;
                    exitg1 = true;
                } else {
                    f_k++;
                }
            }
            hb_ocn_assert(b_varargout_1);
            // 'cutZeroEnd:106' ocn_assert( all( diff_rdd   < tol, 'all' ),"Continuity C2 failed",
            // mfilename );
            d_x.set_size(c_z1.size(0));
            g_loop_ub = c_z1.size(0);
            for (int i23{0}; i23 < g_loop_ub; i23++) {
                d_x[i23] = (c_z1[i23] < 1.0E-9);
            }
            c_varargout_1 = true;
            g_k = 0;
            exitg1 = false;
            while ((!exitg1) && (g_k <= d_x.size(0) - 1)) {
                if (!d_x[g_k]) {
                    c_varargout_1 = false;
                    exitg1 = true;
                } else {
                    g_k++;
                }
            }
            ib_ocn_assert(c_varargout_1);
        }
    }
    //      if( u >= curv.b_param + curv.a_param || u <= curv.b_param)
    //          u = curv.a_param / 2 + curv.b_param;
    //      end
    //      curv2                   = curv;
    //  curv2.UseConstJerk      = true;
    //  curv2.b_param           = u;
    //  curv2.a_param           = curv.a_param  + curv.b_param - curv2.b_param;
    //  [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2, true );
    //  curv2.ConstJerk         = jps;
    //  curv2.Info.zspdmode     = ZSpdMode.NZ;
    //
    //  curv1                   = curv;
    //  curv1.a_param           = u - curv1.b_param;
    //  curv1.UseConstJerk      = false;
    //  curv1.Info.gcode_source_line = curv.Info.gcode_source_line;
    //
    //  if( isAZeroStart( curv ) )
    //      curv1.Info.zspdmode = ZSpdMode.ZN;
    //  else
    //      curv1.Info.zspdmode = ZSpdMode.NN;
    //  end
    //
    //  if( coder.target("MATLAB") )
    //      check_continuity( ctx, curv, curv1, curv2 );
    //  end
    *ret = b_ret;
}

} // namespace ocn

//
// File trailer for cutZeroEnd.cpp
//
// [EOF]
//
