
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutCurvStruct.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "cutCurvStruct.h"
#include "EvalCurvStruct.h"
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
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function [ ret, curvLeft, curvRight ] = cutCurvStruct( ctx, curv, u0, L, isEnd )
//
// cutCurvStruct: Cut a piece of the structure with a size of L
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
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                CurvStruct *curv
//                double L
//                double *ret
//                CurvStruct *curvRight
// Return Type  : void
//
namespace ocn {
void b_cutCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                     const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                     const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                     const int ctx_cfg_maskRot_size[2],
                     const ::coder::array<int, 1U> &ctx_cfg_indCart,
                     const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                     int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_GaussLegendreX[5],
                     const double ctx_cfg_GaussLegendreW[5], CurvStruct *curv, double L,
                     double *ret, CurvStruct *curvRight)
{
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D1;
    CurvStruct expl_temp;
    double u_tilda;
    int b_ret;
    // 'cutCurvStruct:18' curvLeft = curv;
    // 'cutCurvStruct:18' curvRight = curvLeft;
    *curvRight = *curv;
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
    if (b_LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                     curv) <= L) {
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
                                      expl_temp.sp.coeff, expl_temp.sp.knots, expl_temp.sp.Lk, L,
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
        double x;
        x = coder::sum(r);
        //  mysqrt : Custom implementation of the sqrt method.
        //
        //  Inputs :
        //    x : Value used for the computation
        //  Outputs :
        //    y : Resulting value
        //
        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
        ocn_assert(x >= 0.0);
        // 'mysqrt:11' y = sqrt(x);
        // 'cutCurvStructU:37' u1_tilda = a * u1 + b;
        u_tilda = curv->a_param * (1.0 - L / std::sqrt(x)) + curv->b_param;
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
        curvRight->b_param = u_tilda;
        // 'cutCurvStruct:29' curvRight.a_param = a + b - curvRight.b_param;
        curvRight->a_param = (curv->a_param + curv->b_param) - u_tilda;
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
        if ((curv->Info.zspdmode == ZSpdMode_NZ) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroEnd:18' zeroFlag = true;
            zeroFlag = true;
        }
        if (zeroFlag) {
            // 'cutCurvStruct:32' curvRight.Info.zspdmode = ZSpdMode.NZ;
            curvRight->Info.zspdmode = ZSpdMode_NZ;
        } else {
            // 'cutCurvStruct:33' else
            // 'cutCurvStruct:34' curvRight.Info.zspdmode = ZSpdMode.NN;
            curvRight->Info.zspdmode = ZSpdMode_NN;
        }
        // 'cutCurvStruct:37' ocn_assert( checkParametrisation( curvRight ), ...
        // 'cutCurvStruct:38'     "Parametrisation is not correct...", mfilename );
        curv_a_param = curvRight->a_param;
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
        curv->a_param = u_tilda - curv->b_param;
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
        if ((curv->Info.zspdmode == ZSpdMode_ZN) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroStart:19' zeroFlag = true;
            b_zeroFlag = true;
        }
        if (b_zeroFlag) {
            // 'cutCurvStruct:42' curvLeft.Info.zspdmode = ZSpdMode.ZN;
            curv->Info.zspdmode = ZSpdMode_ZN;
        } else {
            // 'cutCurvStruct:43' else
            // 'cutCurvStruct:44' curvLeft.Info.zspdmode = ZSpdMode.NN;
            curv->Info.zspdmode = ZSpdMode_NN;
        }
        // 'cutCurvStruct:47' ocn_assert( checkParametrisation( curvLeft ), ...
        // 'cutCurvStruct:48'     "Parametrisation is not correct...", mfilename  );
        b_curv_a_param = curv->a_param;
        curv_b_param = curv->b_param;
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
    *ret = b_ret;
}

//
// function [ ret, curvLeft, curvRight ] = cutCurvStruct( ctx, curv, u0, L, isEnd )
//
// cutCurvStruct: Cut a piece of the structure with a size of L
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
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                CurvStruct *curv
//                double L
//                double *ret
//                CurvStruct *curvRight
// Return Type  : void
//
void c_cutCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                     const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                     const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                     const int ctx_cfg_maskRot_size[2],
                     const ::coder::array<int, 1U> &ctx_cfg_indCart,
                     const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                     int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_GaussLegendreX[5],
                     const double ctx_cfg_GaussLegendreW[5], CurvStruct *curv, double L,
                     double *ret, CurvStruct *curvRight)
{
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D0;
    CurvStruct expl_temp;
    double u_tilda;
    int b_ret;
    // 'cutCurvStruct:18' curvLeft = curv;
    // 'cutCurvStruct:18' curvRight = curvLeft;
    *curvRight = *curv;
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
                     curv) <= L) {
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
        u_tilda =
            splineLengthFindU(ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                              expl_temp.sp.Bl.handle, expl_temp.sp.Bl.order, expl_temp.sp.coeff,
                              expl_temp.sp.knots, expl_temp.sp.Lk, L, curv->b_param);
    } else {
        int loop_ub;
        // 'cutCurvStructU:26' else
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        // 'cutCurvStructU:30' if( isEnd )
        // 'cutCurvStructU:33' else
        // 'cutCurvStructU:34' [ ~, r1D0 ] = EvalCurvStruct( ctx, curv, 0 );
        r_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, a__2, r1D0);
        // 'cutCurvStructU:35' u1 = u0 + L / MyNorm( r1D0 );
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
        r.set_size(r1D0.size(0));
        loop_ub = r1D0.size(0);
        for (int i{0}; i < loop_ub; i++) {
            double varargin_1;
            varargin_1 = r1D0[i];
            r[i] = std::pow(varargin_1, 2.0);
        }
        double x;
        x = coder::sum(r);
        //  mysqrt : Custom implementation of the sqrt method.
        //
        //  Inputs :
        //    x : Value used for the computation
        //  Outputs :
        //    y : Resulting value
        //
        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
        ocn_assert(x >= 0.0);
        // 'mysqrt:11' y = sqrt(x);
        // 'cutCurvStructU:37' u1_tilda = a * u1 + b;
        u_tilda = curv->a_param * (L / std::sqrt(x)) + curv->b_param;
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
        curvRight->b_param = u_tilda;
        // 'cutCurvStruct:29' curvRight.a_param = a + b - curvRight.b_param;
        curvRight->a_param = (curv->a_param + curv->b_param) - u_tilda;
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
        if ((curv->Info.zspdmode == ZSpdMode_NZ) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroEnd:18' zeroFlag = true;
            zeroFlag = true;
        }
        if (zeroFlag) {
            // 'cutCurvStruct:32' curvRight.Info.zspdmode = ZSpdMode.NZ;
            curvRight->Info.zspdmode = ZSpdMode_NZ;
        } else {
            // 'cutCurvStruct:33' else
            // 'cutCurvStruct:34' curvRight.Info.zspdmode = ZSpdMode.NN;
            curvRight->Info.zspdmode = ZSpdMode_NN;
        }
        // 'cutCurvStruct:37' ocn_assert( checkParametrisation( curvRight ), ...
        // 'cutCurvStruct:38'     "Parametrisation is not correct...", mfilename );
        curv_a_param = curvRight->a_param;
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
        curv->a_param = u_tilda - curv->b_param;
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
        if ((curv->Info.zspdmode == ZSpdMode_ZN) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroStart:19' zeroFlag = true;
            b_zeroFlag = true;
        }
        if (b_zeroFlag) {
            // 'cutCurvStruct:42' curvLeft.Info.zspdmode = ZSpdMode.ZN;
            curv->Info.zspdmode = ZSpdMode_ZN;
        } else {
            // 'cutCurvStruct:43' else
            // 'cutCurvStruct:44' curvLeft.Info.zspdmode = ZSpdMode.NN;
            curv->Info.zspdmode = ZSpdMode_NN;
        }
        // 'cutCurvStruct:47' ocn_assert( checkParametrisation( curvLeft ), ...
        // 'cutCurvStruct:48'     "Parametrisation is not correct...", mfilename  );
        b_curv_a_param = curv->a_param;
        curv_b_param = curv->b_param;
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
    *ret = b_ret;
}

//
// function [ ret, curvLeft, curvRight ] = cutCurvStruct( ctx, curv, u0, L, isEnd )
//
// cutCurvStruct: Cut a piece of the structure with a size of L
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
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                CurvStruct *curv
//                double L
//                double *ret
//                CurvStruct *curvRight
// Return Type  : void
//
void cutCurvStruct(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                   const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                   const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                   const int ctx_cfg_maskRot_size[2],
                   const ::coder::array<int, 1U> &ctx_cfg_indCart,
                   const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                   int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_GaussLegendreX[5],
                   const double ctx_cfg_GaussLegendreW[5], CurvStruct *curv, double L, double *ret,
                   CurvStruct *curvRight)
{
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D0;
    CurvStruct expl_temp;
    double u_tilda;
    int b_ret;
    // 'cutCurvStruct:18' curvLeft = curv;
    // 'cutCurvStruct:18' curvRight = curvLeft;
    *curvRight = *curv;
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
    if (b_LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                     ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                     ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                     ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                     curv) <= L) {
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
        u_tilda =
            splineLengthFindU(ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                              expl_temp.sp.Bl.handle, expl_temp.sp.Bl.order, expl_temp.sp.coeff,
                              expl_temp.sp.knots, expl_temp.sp.Lk, L, curv->b_param);
    } else {
        int loop_ub;
        // 'cutCurvStructU:26' else
        //  In case of helix and line, ||r'(u)||=const,
        //  for 0 < u < 1
        // 'cutCurvStructU:30' if( isEnd )
        // 'cutCurvStructU:33' else
        // 'cutCurvStructU:34' [ ~, r1D0 ] = EvalCurvStruct( ctx, curv, 0 );
        r_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                         ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                         ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                         ctx_cfg_NCart, ctx_cfg_NRot, curv, a__2, r1D0);
        // 'cutCurvStructU:35' u1 = u0 + L / MyNorm( r1D0 );
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
        r.set_size(r1D0.size(0));
        loop_ub = r1D0.size(0);
        for (int i{0}; i < loop_ub; i++) {
            double varargin_1;
            varargin_1 = r1D0[i];
            r[i] = std::pow(varargin_1, 2.0);
        }
        double x;
        x = coder::sum(r);
        //  mysqrt : Custom implementation of the sqrt method.
        //
        //  Inputs :
        //    x : Value used for the computation
        //  Outputs :
        //    y : Resulting value
        //
        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
        ocn_assert(x >= 0.0);
        // 'mysqrt:11' y = sqrt(x);
        // 'cutCurvStructU:37' u1_tilda = a * u1 + b;
        u_tilda = curv->a_param * (L / std::sqrt(x)) + curv->b_param;
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
        curvRight->b_param = u_tilda;
        // 'cutCurvStruct:29' curvRight.a_param = a + b - curvRight.b_param;
        curvRight->a_param = (curv->a_param + curv->b_param) - u_tilda;
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
        if ((curv->Info.zspdmode == ZSpdMode_NZ) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroEnd:18' zeroFlag = true;
            zeroFlag = true;
        }
        if (zeroFlag) {
            // 'cutCurvStruct:32' curvRight.Info.zspdmode = ZSpdMode.NZ;
            curvRight->Info.zspdmode = ZSpdMode_NZ;
        } else {
            // 'cutCurvStruct:33' else
            // 'cutCurvStruct:34' curvRight.Info.zspdmode = ZSpdMode.NN;
            curvRight->Info.zspdmode = ZSpdMode_NN;
        }
        // 'cutCurvStruct:37' ocn_assert( checkParametrisation( curvRight ), ...
        // 'cutCurvStruct:38'     "Parametrisation is not correct...", mfilename );
        curv_a_param = curvRight->a_param;
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
        curv->a_param = u_tilda - curv->b_param;
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
        if ((curv->Info.zspdmode == ZSpdMode_ZN) || (curv->Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroStart:19' zeroFlag = true;
            b_zeroFlag = true;
        }
        if (b_zeroFlag) {
            // 'cutCurvStruct:42' curvLeft.Info.zspdmode = ZSpdMode.ZN;
            curv->Info.zspdmode = ZSpdMode_ZN;
        } else {
            // 'cutCurvStruct:43' else
            // 'cutCurvStruct:44' curvLeft.Info.zspdmode = ZSpdMode.NN;
            curv->Info.zspdmode = ZSpdMode_NN;
        }
        // 'cutCurvStruct:47' ocn_assert( checkParametrisation( curvLeft ), ...
        // 'cutCurvStruct:48'     "Parametrisation is not correct...", mfilename  );
        b_curv_a_param = curv->a_param;
        curv_b_param = curv->b_param;
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
    *ret = b_ret;
}

} // namespace ocn

//
// File trailer for cutCurvStruct.cpp
//
// [EOF]
//
