
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: feedratePlanningForceZeroStop.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "feedratePlanningForceZeroStop.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "LengthCurv.h"
#include "constrCurvStruct.h"
#include "cutCurvStruct.h"
#include "feedratePlanningSetupCurves.h"
#include "ocn_assert.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "zeroSpeedCurv.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
#include <cmath>

// Function Definitions
//
// function [ ctx, window, NWindow ] = feedratePlanningForceZeroStop( ctx, window, NWindow )
//
// feedratePlanningForceZeroStop : This is a work around to handle an
//  infeasibility during the optimization.
//
//  Inputs :
//    ctx         : The context of the computational chain
//    window      : Window of curves
//    NWindow     : Number of curves in the window
//
//  Outputs :
//    ctx         : The context of the computational chain
//    window      : Window of curves
//    NWindow     : Number of curves in the window
//
//
// Arguments    : b_FeedoptContext *ctx
//                ::coder::array<CurvStruct, 2U> &window
//                double *NWindow
// Return Type  : void
//
namespace ocn {
void feedratePlanningForceZeroStop(b_FeedoptContext *ctx, ::coder::array<CurvStruct, 2U> &window,
                                   double *NWindow)
{
    static const signed char ind1[2][3]{{1, 1, 2}, {1, 2, 2}};
    static const signed char ind2[2][3]{{2, 3, 3}, {1, 2, 1}};
    Kinematics b_ctx;
    Kinematics c_ctx;
    Kinematics e_ctx;
    Kinematics g_ctx;
    queue_coder curvQueue;
    ::coder::array<CurvStruct, 2U> b_window;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> a__4;
    ::coder::array<double, 2U> a__5;
    ::coder::array<double, 2U> a__6;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 1U> c_r_data;
    ::coder::array<double, 1U> d_r_data;
    ::coder::array<double, 1U> d_rd_data;
    ::coder::array<double, 1U> d_rdd_data;
    ::coder::array<double, 1U> e_rd_data;
    ::coder::array<double, 1U> e_rdd_data;
    ::coder::array<double, 1U> r3;
    ::coder::array<bool, 1U> b_x;
    Axes params_tool_offset;
    CurvStruct curv_vec[3];
    CurvStruct C;
    CurvStruct b_curv1NN;
    CurvStruct curv;
    CurvStruct curv1;
    CurvStruct curv1NN;
    CurvStruct curv2;
    CurvStruct curv2NN;
    CurvStruct d_ctx;
    CurvStruct f_ctx;
    CurvStruct h_ctx;
    SplineStruct params_spline;
    b_CurvStruct e_expl_temp;
    b_CurvStruct j_expl_temp;
    double r_data[36];
    double rd_data[36];
    double rdd_data[36];
    double b_rd_data[12];
    double b_rdd_data[12];
    double b_r_data[6];
    double c_rd_data[6];
    double c_rdd_data[6];
    double params_CoeffP5[6];
    double params_R0[6];
    double params_R1[6];
    double params_Cprim[3];
    double params_evec[3];
    double L;
    double Lcut;
    double b_expl_temp;
    double b_ret;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double f_expl_temp;
    double g_expl_temp;
    double h_expl_temp;
    double i_expl_temp;
    double params_gcodeInfoStruct_FeedRate;
    double params_gcodeInfoStruct_SpindleSpeed;
    double params_tool_backangle;
    double params_tool_diameter;
    double params_tool_frontangle;
    double ret;
    int ab_loop_ub;
    int cb_loop_ub;
    int curv1_tmp;
    int curv_ind;
    int i60;
    unsigned int ind;
    int ind1_tmp_tmp;
    unsigned int kend;
    int o_loop_ub;
    int outsize_idx_1;
    int p_loop_ub;
    int params_gcodeInfoStruct_gcode_source_line;
    int params_tool_orientation;
    int params_tool_pocketno;
    int params_tool_toolno;
    int q_loop_ub;
    int s_loop_ub;
    int u_loop_ub;
    int v_loop_ub;
    int x_loop_ub;
    unsigned int y;
    signed char b_tmp_data[6];
    signed char tmp_data[6];
    bool b_zeroFlag;
    bool exitg1;
    bool params_gcodeInfoStruct_G91;
    bool params_gcodeInfoStruct_G91_1;
    bool params_gcodeInfoStruct_HSC;
    bool params_gcodeInfoStruct_TRAFO;
    bool zeroFlag;
    CurveType params_gcodeInfoStruct_Type;
    ZSpdMode params_gcodeInfoStruct_zspdmode;
    //  NN case :
    //  Optimization failed due to small coefficient, so force a stop
    // 'feedratePlanningForceZeroStop:20' curvQueue       = ctx.q_split;
    curvQueue = ctx->q_split;
    // 'feedratePlanningForceZeroStop:21' ctx.zero_forced = true;
    ctx->zero_forced = true;
    // 'feedratePlanningForceZeroStop:22' ocn_assert( ctx.k0 > 1, "Should not be called one the
    // first set of curves", ... 'feedratePlanningForceZeroStop:23'     mfilename );
    ob_ocn_assert(ctx->k0 > 1);
    // 'feedratePlanningForceZeroStop:25' curv0           = window( 1 );
    // 'feedratePlanningForceZeroStop:26' curv1           = window( NWindow );
    curv1_tmp = static_cast<int>(*NWindow) - 1;
    curv1 = window[curv1_tmp];
    // 'feedratePlanningForceZeroStop:27' ind1            = ctx.k0 + NWindow;
    ind1_tmp_tmp = static_cast<int>(std::round(static_cast<double>(ctx->k0) + *NWindow));
    // 'feedratePlanningForceZeroStop:29' msg = "Curve should be a Zero Stop";
    // 'feedratePlanningForceZeroStop:30' ocn_assert( ~isAZeroStart( curv0 ), msg, mfilename );
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
    zeroFlag = false;
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
    if ((window[0].Info.zspdmode == ZSpdMode_ZN) || (window[0].Info.zspdmode == ZSpdMode_ZZ)) {
        // 'isAZeroStart:19' zeroFlag = true;
        zeroFlag = true;
    }
    pb_ocn_assert(!zeroFlag);
    // 'feedratePlanningForceZeroStop:31' ocn_assert( ~isAZeroEnd( curv1 ),   msg, mfilename );
    //  isAZeroEnd : Return true if the curv ends with zero speed
    //
    //  Inputs :
    //  curv / Info / ZSpdMode : A structure containning the information of the
    //  curv zero speed.
    //
    //  Outputs :
    //  zeroFlag : Boolean value. TRUE mean zero flag
    // 'isAZeroEnd:10' zeroFlag = false;
    b_zeroFlag = false;
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
    if ((window[curv1_tmp].Info.zspdmode == ZSpdMode_NZ) ||
        (window[curv1_tmp].Info.zspdmode == ZSpdMode_ZZ)) {
        // 'isAZeroEnd:18' zeroFlag = true;
        b_zeroFlag = true;
    }
    pb_ocn_assert(!b_zeroFlag);
    // 'feedratePlanningForceZeroStop:32' curv1.Info.zspdmode = ZSpdMode.NZ;
    curv1.Info.zspdmode = ZSpdMode_NZ;
    // 'feedratePlanningForceZeroStop:34' [ ~, curv1NN, curv1NZ ]     = cutZeroEnd( ctx,  curv1 );
    //  cutZeroEnd : Cut the end of the given to handle the zero speed.
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
    // 'cutZeroEnd:14' L       = LengthCurv( ctx, curv, 0, 1 );
    L = b_LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                     ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                     ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                     ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.GaussLegendreX,
                     ctx->cfg.GaussLegendreW, &curv1);
    // 'cutZeroEnd:15' Lcut    = ctx.cfg.LSplitZero;
    Lcut = ctx->cfg.LSplitZero;
    // 'cutZeroEnd:17' if( Lcut > L / 3 )
    if (ctx->cfg.LSplitZero > L / 3.0) {
        // 'cutZeroEnd:17' Lcut = L / 3;
        Lcut = L / 3.0;
    }
    // 'cutZeroEnd:19' [ ret, curv1, curv2 ] = cutCurvStruct( ctx, curv, 1, Lcut, true );
    curv1NN = curv1;
    b_cutCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                    ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                    ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                    ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                    &curv1NN, Lcut, &ret, &ctx->zero_forced_buffer[0]);
    // 'cutZeroEnd:21' if( ret < 0 )
    if (ret < 0.0) {
        // 'cutZeroEnd:22' curv1 = curv;
        curv1NN = curv1;
        // 'cutZeroEnd:23' curv1.UseConstJerk      = true;
        curv1NN.UseConstJerk = true;
        // 'cutZeroEnd:24' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1, true );
        b_ctx = ctx->kin;
        b_curv1NN = curv1NN;
        c_zeroSpeedCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                        ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                        ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                        ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.vmax,
                        ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt, &b_ctx, &b_curv1NN, a__1, a__2,
                        a__3, &curv1NN.ConstJerk);
        // 'cutZeroEnd:25' curv1.ConstJerk         = jps;
    } else {
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
        x = b_LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                         ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                         ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                         ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                         ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                         &ctx->zero_forced_buffer[0]) -
            Lcut;
        fb_ocn_assert(std::abs(x) <= 0.1);
        // 'cutZeroEnd:28' curv2.UseConstJerk      = true;
        ctx->zero_forced_buffer[0].UseConstJerk = true;
        // 'cutZeroEnd:29' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2, true );
        c_ctx = ctx->kin;
        d_ctx = ctx->zero_forced_buffer[0];
        c_zeroSpeedCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                        ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                        ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                        ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.vmax,
                        ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt, &c_ctx, &d_ctx, a__4, a__5, a__6,
                        &ctx->zero_forced_buffer[0].ConstJerk);
        // 'cutZeroEnd:30' curv2.ConstJerk         = jps;
        // 'cutZeroEnd:31' curv1.UseConstJerk      = false;
        curv1NN.UseConstJerk = false;
        // 'cutZeroEnd:32' check_continuity( ctx, curv, curv1, curv2 );
        // 'cutZeroEnd:64' curv_vec    = [ curv; curv1; curv2 ];
        curv_vec[0] = curv1;
        curv_vec[1] = curv1NN;
        curv_vec[2] = ctx->zero_forced_buffer[0];
        // 'cutZeroEnd:65' u_vec       = [ 0, 1 ];
        // 'cutZeroEnd:66' r           = repmat( curv.R0( ctx.cfg.maskTot ), 1, 2, 3 );
        end = ctx->cfg.maskTot.size[1] - 1;
        trueCount = 0;
        partialTrueCount = 0;
        for (int i{0}; i <= end; i++) {
            if (ctx->cfg.maskTot.data[i]) {
                trueCount++;
            }
            if (ctx->cfg.maskTot.data[i]) {
                tmp_data[partialTrueCount] = static_cast<signed char>(i + 1);
                partialTrueCount++;
            }
        }
        if (trueCount != 0) {
            for (int t{0}; t < 3; t++) {
                for (int b_t{0}; b_t < 2; b_t++) {
                    for (int k{0}; k < trueCount; k++) {
                        r_data[(k + trueCount * b_t) + trueCount * 2 * t] =
                            window[curv1_tmp].R0[tmp_data[k] - 1];
                    }
                }
            }
        }
        // 'cutZeroEnd:67' rd          = r;
        // 'cutZeroEnd:68' rdd         = r;
        for (int b_i{0}; b_i < 3; b_i++) {
            for (int i1{0}; i1 < 2; i1++) {
                for (int i2{0}; i2 < trueCount; i2++) {
                    double d;
                    d = r_data[(i2 + trueCount * i1) + trueCount * 2 * b_i];
                    rd_data[(i2 + trueCount * i1) + trueCount * 2 * b_i] = d;
                    rdd_data[(i2 + trueCount * i1) + trueCount * 2 * b_i] = d;
                }
            }
        }
        // 'cutZeroEnd:70' for j = 1 : 3
        rd = trueCount - 1;
        rdd = trueCount - 1;
        for (int j{0}; j < 3; j++) {
            double c;
            int b_loop_ub;
            int c_loop_ub;
            int loop_ub;
            // 'cutZeroEnd:71' [ r( :, :, j ) , rd( :, :, j ), rdd( :, :, j ) ] = ...
            // 'cutZeroEnd:72'         EvalCurvStruct( ctx, curv_vec( j ),  u_vec );
            p_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                             ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                             ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                             ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, &curv_vec[j], r,
                             r1, r2);
            loop_ub = r.size(0);
            b_loop_ub = r1.size(0);
            c_loop_ub = r2.size(0);
            for (int i3{0}; i3 < 2; i3++) {
                for (int i4{0}; i4 < loop_ub; i4++) {
                    r_data[(i4 + trueCount * i3) + trueCount * 2 * j] = r[i4 + r.size(0) * i3];
                }
                for (int i6{0}; i6 < b_loop_ub; i6++) {
                    rd_data[(i6 + trueCount * i3) + trueCount * 2 * j] = r1[i6 + r1.size(0) * i3];
                }
                for (int i8{0}; i8 < c_loop_ub; i8++) {
                    rdd_data[(i8 + trueCount * i3) + trueCount * 2 * j] = r2[i8 + r2.size(0) * i3];
                }
            }
            // 'cutZeroEnd:73' rd( :, :, j )    = rd( :, :, j )  / curv_vec( j ).a_param;
            for (int i5{0}; i5 < 2; i5++) {
                for (int i7{0}; i7 <= rd; i7++) {
                    b_rd_data[i7 + trueCount * i5] =
                        rd_data[(i7 + trueCount * i5) + trueCount * 2 * j] / curv_vec[j].a_param;
                }
            }
            double c_tmp;
            // 'cutZeroEnd:74' if( 1 )
            // 'cutZeroEnd:75' rdd( :, :, j )   = rdd( :, :, j ) / curv_vec( j ).a_param^2;
            c_tmp = curv_vec[j].a_param;
            c = c_tmp * c_tmp;
            for (int i9{0}; i9 < 2; i9++) {
                for (int i13{0}; i13 < trueCount; i13++) {
                    rd_data[(i13 + trueCount * i9) + trueCount * 2 * j] =
                        b_rd_data[i13 + trueCount * i9];
                }
                for (int i15{0}; i15 <= rdd; i15++) {
                    b_rdd_data[i15 + trueCount * i9] =
                        rdd_data[(i15 + trueCount * i9) + trueCount * 2 * j] / c;
                }
            }
            for (int i12{0}; i12 < 2; i12++) {
                for (int i14{0}; i14 < trueCount; i14++) {
                    rdd_data[(i14 + trueCount * i12) + trueCount * 2 * j] =
                        b_rdd_data[i14 + trueCount * i12];
                }
            }
        }
        // 'cutZeroEnd:81' ind1 = [ 1, 1; 1, 2; 2, 2 ];
        // 'cutZeroEnd:82' ind2 = [ 2, 1; 3, 2; 3, 1 ];
        // 'cutZeroEnd:84' for j = 1 : 3
        for (int b_j{0}; b_j < 3; b_j++) {
            int c_k;
            int e_k;
            int f_loop_ub;
            int h_k;
            int i_loop_ub;
            int k_loop_ub;
            bool b_varargout_1;
            bool c_varargout_1;
            bool varargout_1;
            // 'cutZeroEnd:85' r1   = r( : , ind1( j, 2 ), ind1( j, 1 ) );
            // 'cutZeroEnd:86' r1d  = rd( : , ind1( j, 2 ), ind1( j, 1 ) );
            // 'cutZeroEnd:87' r1dd = rdd( : , ind1( j, 2 ), ind1( j, 1 ) );
            // 'cutZeroEnd:88' r2   = r( : , ind2( j, 2 ), ind2( j, 1 ) );
            // 'cutZeroEnd:89' r2d  = rd( : , ind2( j, 2 ), ind2( j, 1 ) );
            // 'cutZeroEnd:90' r2dd = rdd( : , ind2( j, 2 ), ind2( j, 1 ) );
            // 'cutZeroEnd:91' assert_continuity( r1, r1d, r1dd, r2, r2d, r2dd );
            // 'cutZeroEnd:98' diff_r      = abs( r1    -r2 );
            // 'cutZeroEnd:99' diff_rd     = abs( r1d   -r2d );
            // 'cutZeroEnd:100' diff_rdd    = abs( r1dd  -r2dd );
            // 'cutZeroEnd:102' tol = 1E-9;
            // 'cutZeroEnd:104' ocn_assert( all( diff_r    < tol, 'all' ), "Continuity C0 failed",
            // mfilename );
            for (int i10{0}; i10 < trueCount; i10++) {
                b_r_data[i10] = r_data[(i10 + trueCount * (ind1[1][b_j] - 1)) +
                                       trueCount * 2 * (ind1[0][b_j] - 1)] -
                                r_data[(i10 + trueCount * (ind2[1][b_j] - 1)) +
                                       trueCount * 2 * (ind2[0][b_j] - 1)];
            }
            c_r_data.set(&b_r_data[0], trueCount);
            r3.set_size(c_r_data.size(0));
            if (c_r_data.size(0) != 0) {
                int i17;
                i17 = c_r_data.size(0);
                for (int b_k{0}; b_k < i17; b_k++) {
                    r3[b_k] = std::abs(c_r_data[b_k]);
                }
            }
            b_x.set_size(r3.size(0));
            f_loop_ub = r3.size(0);
            for (int i18{0}; i18 < f_loop_ub; i18++) {
                b_x[i18] = (r3[i18] < 1.0E-9);
            }
            varargout_1 = true;
            c_k = 0;
            exitg1 = false;
            while ((!exitg1) && (c_k <= b_x.size(0) - 1)) {
                if (!b_x[c_k]) {
                    varargout_1 = false;
                    exitg1 = true;
                } else {
                    c_k++;
                }
            }
            gb_ocn_assert(varargout_1);
            // 'cutZeroEnd:105' ocn_assert( all( diff_rd   < tol, 'all' ), "Continuity C1 failed",
            // mfilename );
            for (int i20{0}; i20 < trueCount; i20++) {
                c_rd_data[i20] = rd_data[(i20 + trueCount * (ind1[1][b_j] - 1)) +
                                         trueCount * 2 * (ind1[0][b_j] - 1)] -
                                 rd_data[(i20 + trueCount * (ind2[1][b_j] - 1)) +
                                         trueCount * 2 * (ind2[0][b_j] - 1)];
            }
            d_rd_data.set(&c_rd_data[0], trueCount);
            r3.set_size(d_rd_data.size(0));
            if (d_rd_data.size(0) != 0) {
                int i22;
                i22 = d_rd_data.size(0);
                for (int d_k{0}; d_k < i22; d_k++) {
                    r3[d_k] = std::abs(d_rd_data[d_k]);
                }
            }
            b_x.set_size(r3.size(0));
            i_loop_ub = r3.size(0);
            for (int i23{0}; i23 < i_loop_ub; i23++) {
                b_x[i23] = (r3[i23] < 1.0E-9);
            }
            b_varargout_1 = true;
            e_k = 0;
            exitg1 = false;
            while ((!exitg1) && (e_k <= b_x.size(0) - 1)) {
                if (!b_x[e_k]) {
                    b_varargout_1 = false;
                    exitg1 = true;
                } else {
                    e_k++;
                }
            }
            hb_ocn_assert(b_varargout_1);
            // 'cutZeroEnd:106' ocn_assert( all( diff_rdd   < tol, 'all' ),"Continuity C2 failed",
            // mfilename );
            for (int i25{0}; i25 < trueCount; i25++) {
                c_rdd_data[i25] = rdd_data[(i25 + trueCount * (ind1[1][b_j] - 1)) +
                                           trueCount * 2 * (ind1[0][b_j] - 1)] -
                                  rdd_data[(i25 + trueCount * (ind2[1][b_j] - 1)) +
                                           trueCount * 2 * (ind2[0][b_j] - 1)];
            }
            d_rdd_data.set(&c_rdd_data[0], trueCount);
            r3.set_size(d_rdd_data.size(0));
            if (d_rdd_data.size(0) != 0) {
                int i26;
                i26 = d_rdd_data.size(0);
                for (int g_k{0}; g_k < i26; g_k++) {
                    r3[g_k] = std::abs(d_rdd_data[g_k]);
                }
            }
            b_x.set_size(r3.size(0));
            k_loop_ub = r3.size(0);
            for (int i28{0}; i28 < k_loop_ub; i28++) {
                b_x[i28] = (r3[i28] < 1.0E-9);
            }
            c_varargout_1 = true;
            h_k = 0;
            exitg1 = false;
            while ((!exitg1) && (h_k <= b_x.size(0) - 1)) {
                if (!b_x[h_k]) {
                    c_varargout_1 = false;
                    exitg1 = true;
                } else {
                    h_k++;
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
    // 'feedratePlanningForceZeroStop:35' ctx.zero_forced_buffer( 1 ) = curv1NZ;
    // 'feedratePlanningForceZeroStop:36' curvQueue.set( ind1, curv1NN );
    ctx->q_split.set(ind1_tmp_tmp, &curv1NN);
    // 'feedratePlanningForceZeroStop:38' ind2            = ind1 + 1;
    // 'feedratePlanningForceZeroStop:39' if( ind2 <= curvQueue.size() )
    if (static_cast<double>(ind1_tmp_tmp + 1) <= ctx->q_split.size()) {
        double b_L;
        double b_Lcut;
        // 'feedratePlanningForceZeroStop:40' curv2       = ctx.q_split.get( ind2 );
        ctx->q_split.get(ind1_tmp_tmp + 1, &curv2);
        // 'feedratePlanningForceZeroStop:41' curv2.Info.zspdmode = ZSpdMode.ZN;
        curv2.Info.zspdmode = ZSpdMode_ZN;
        // 'feedratePlanningForceZeroStop:42' [ ~, curv2ZN, curv2NN ]     = cutZeroStart( ctx, curv2
        // );
        //  cutZeroStart : Cut the start of the given to handle the zero speed.
        //
        //  Inputs :
        //  ctx       : The context used in the computational chain.
        //  curv      : The curve to cut the end.
        //
        //  Outputs :
        //  ret       : The returned value of the operation : 1 means
        //  curvLeft  : Resulting ZN Curve struct with constant jerk speed profile
        //  curvRight : Resulting NN Curve struct
        //
        // 'cutZeroStart:14' L       = LengthCurv( ctx, curv, 0, 1 );
        b_L = b_LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                           ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                           ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                           ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                           ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, &curv2);
        // 'cutZeroStart:15' Lcut    = ctx.cfg.LSplitZero;
        b_Lcut = ctx->cfg.LSplitZero;
        // 'cutZeroStart:17' if( Lcut > L / 3 )
        if (ctx->cfg.LSplitZero > b_L / 3.0) {
            // 'cutZeroStart:17' Lcut = L / 3;
            b_Lcut = b_L / 3.0;
        }
        // 'cutZeroStart:19' [ ret, curv1, curv2 ] = cutCurvStruct( ctx, curv, 0, Lcut, false );
        ctx->zero_forced_buffer[1] = curv2;
        cutCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                      ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                      ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot, ctx->cfg.NumberAxis,
                      ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.GaussLegendreX,
                      ctx->cfg.GaussLegendreW, &ctx->zero_forced_buffer[1], b_Lcut, &b_ret,
                      &curv2NN);
        // 'cutZeroStart:21' if( ret < 0 )
        if (b_ret < 0.0) {
            // 'cutZeroStart:22' curv1                   = curv;
            ctx->zero_forced_buffer[1] = curv2;
            // 'cutZeroStart:23' curv1.UseConstJerk      = true;
            ctx->zero_forced_buffer[1].UseConstJerk = true;
            // 'cutZeroStart:24' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1, false );
            e_ctx = ctx->kin;
            f_ctx = ctx->zero_forced_buffer[1];
            d_zeroSpeedCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                            ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                            ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                            ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.vmax,
                            ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt, &e_ctx, &f_ctx, a__1, a__2,
                            a__3, &ctx->zero_forced_buffer[1].ConstJerk);
            // 'cutZeroStart:25' curv1.ConstJerk         = jps;
        } else {
            double c_x;
            int b_end;
            int b_partialTrueCount;
            int b_rd;
            int b_rdd;
            int b_trueCount;
            // 'cutZeroStart:26' else
            // 'cutZeroStart:27' ocn_assert( check_curv_length( ctx, curv1, Lcut ), "Curve Length
            // not valide", mfilename ); 'cutZeroStart:112' tol = 1E-1; 'cutZeroStart:114' isValid =
            // ( abs( LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
            c_x = b_LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                               ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                               ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                               ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                               ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                               &ctx->zero_forced_buffer[1]) -
                  b_Lcut;
            bb_ocn_assert(std::abs(c_x) <= 0.1);
            // 'cutZeroStart:28' curv1.UseConstJerk      = true;
            ctx->zero_forced_buffer[1].UseConstJerk = true;
            // 'cutZeroStart:29' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1, false );
            g_ctx = ctx->kin;
            h_ctx = ctx->zero_forced_buffer[1];
            d_zeroSpeedCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                            ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                            ctx->cfg.maskRot.size, ctx->cfg.indCart, ctx->cfg.indRot,
                            ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, ctx->cfg.vmax,
                            ctx->cfg.amax, ctx->cfg.jmax, ctx->cfg.dt, &g_ctx, &h_ctx, a__4, a__5,
                            a__6, &ctx->zero_forced_buffer[1].ConstJerk);
            // 'cutZeroStart:30' curv1.ConstJerk         = jps;
            // 'cutZeroStart:31' curv2.UseConstJerk      = false;
            curv2NN.UseConstJerk = false;
            // 'cutZeroStart:32' check_continuity( ctx, curv, curv1, curv2 );
            // 'cutZeroStart:65' curv_vec    = [ curv; curv1; curv2 ];
            curv_vec[0] = curv2;
            curv_vec[1] = ctx->zero_forced_buffer[1];
            curv_vec[2] = curv2NN;
            // 'cutZeroStart:66' u_vec       = [ 0, 1 ];
            // 'cutZeroStart:67' r           = repmat( curv.R0( ctx.cfg.maskTot ), 1, 2, 3 );
            b_end = ctx->cfg.maskTot.size[1] - 1;
            b_trueCount = 0;
            b_partialTrueCount = 0;
            for (int c_i{0}; c_i <= b_end; c_i++) {
                if (ctx->cfg.maskTot.data[c_i]) {
                    b_trueCount++;
                }
                if (ctx->cfg.maskTot.data[c_i]) {
                    b_tmp_data[b_partialTrueCount] = static_cast<signed char>(c_i + 1);
                    b_partialTrueCount++;
                }
            }
            if (b_trueCount != 0) {
                for (int c_t{0}; c_t < 3; c_t++) {
                    for (int d_t{0}; d_t < 2; d_t++) {
                        for (int f_k{0}; f_k < b_trueCount; f_k++) {
                            r_data[(f_k + b_trueCount * d_t) + b_trueCount * 2 * c_t] =
                                curv2.R0[b_tmp_data[f_k] - 1];
                        }
                    }
                }
            }
            // 'cutZeroStart:68' rd          = r;
            // 'cutZeroStart:69' rdd         = r;
            for (int i27{0}; i27 < 3; i27++) {
                for (int i29{0}; i29 < 2; i29++) {
                    for (int i30{0}; i30 < b_trueCount; i30++) {
                        double d1;
                        d1 = r_data[(i30 + b_trueCount * i29) + b_trueCount * 2 * i27];
                        rd_data[(i30 + b_trueCount * i29) + b_trueCount * 2 * i27] = d1;
                        rdd_data[(i30 + b_trueCount * i29) + b_trueCount * 2 * i27] = d1;
                    }
                }
            }
            // 'cutZeroStart:71' for j = 1 : 3
            b_rd = b_trueCount - 1;
            b_rdd = b_trueCount - 1;
            for (int c_j{0}; c_j < 3; c_j++) {
                double b_c;
                int l_loop_ub;
                int m_loop_ub;
                int n_loop_ub;
                // 'cutZeroStart:72' [ r( :, :, j ) , rd( :, :, j ), rdd( :, :, j ) ] = ...
                // 'cutZeroStart:73'         EvalCurvStruct( ctx, curv_vec( j ),  u_vec );
                p_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                 ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                 ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                 ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                 ctx->cfg.NRot, &curv_vec[c_j], r, r1, r2);
                l_loop_ub = r.size(0);
                m_loop_ub = r1.size(0);
                n_loop_ub = r2.size(0);
                for (int i31{0}; i31 < 2; i31++) {
                    for (int i32{0}; i32 < l_loop_ub; i32++) {
                        r_data[(i32 + b_trueCount * i31) + b_trueCount * 2 * c_j] =
                            r[i32 + r.size(0) * i31];
                    }
                    for (int i34{0}; i34 < m_loop_ub; i34++) {
                        rd_data[(i34 + b_trueCount * i31) + b_trueCount * 2 * c_j] =
                            r1[i34 + r1.size(0) * i31];
                    }
                    for (int i36{0}; i36 < n_loop_ub; i36++) {
                        rdd_data[(i36 + b_trueCount * i31) + b_trueCount * 2 * c_j] =
                            r2[i36 + r2.size(0) * i31];
                    }
                }
                // 'cutZeroStart:74' rd( :, :, j )    = rd( :, :, j )  / curv_vec( j ).a_param;
                for (int i33{0}; i33 < 2; i33++) {
                    for (int i35{0}; i35 <= b_rd; i35++) {
                        b_rd_data[i35 + b_trueCount * i33] =
                            rd_data[(i35 + b_trueCount * i33) + b_trueCount * 2 * c_j] /
                            curv_vec[c_j].a_param;
                    }
                }
                double b_c_tmp;
                // 'cutZeroStart:75' if( 1 )
                // 'cutZeroStart:76' rdd( :, :, j )   = rdd( :, :, j ) / curv_vec( j ).a_param^2;
                b_c_tmp = curv_vec[c_j].a_param;
                b_c = b_c_tmp * b_c_tmp;
                for (int i38{0}; i38 < 2; i38++) {
                    for (int i41{0}; i41 < b_trueCount; i41++) {
                        rd_data[(i41 + b_trueCount * i38) + b_trueCount * 2 * c_j] =
                            b_rd_data[i41 + b_trueCount * i38];
                    }
                    for (int i45{0}; i45 <= b_rdd; i45++) {
                        b_rdd_data[i45 + b_trueCount * i38] =
                            rdd_data[(i45 + b_trueCount * i38) + b_trueCount * 2 * c_j] / b_c;
                    }
                }
                for (int i40{0}; i40 < 2; i40++) {
                    for (int i44{0}; i44 < b_trueCount; i44++) {
                        rdd_data[(i44 + b_trueCount * i40) + b_trueCount * 2 * c_j] =
                            b_rdd_data[i44 + b_trueCount * i40];
                    }
                }
            }
            // 'cutZeroStart:82' ind1 = [ 1, 1; 1, 2; 2, 2 ];
            // 'cutZeroStart:83' ind2 = [ 2, 1; 3, 2; 3, 1 ];
            // 'cutZeroStart:85' for j = 1 : 3
            for (int d_j{0}; d_j < 3; d_j++) {
                int bb_loop_ub;
                int j_k;
                int l_k;
                int n_k;
                int t_loop_ub;
                int w_loop_ub;
                bool d_varargout_1;
                bool e_varargout_1;
                bool f_varargout_1;
                // 'cutZeroStart:86' r1   = r( : , ind1( j, 2 ), ind1( j, 1 ) );
                // 'cutZeroStart:87' r1d  = rd( : , ind1( j, 2 ), ind1( j, 1 ) );
                // 'cutZeroStart:88' r1dd = rdd( : , ind1( j, 2 ), ind1( j, 1 ) );
                // 'cutZeroStart:89' r2   = r( : , ind2( j, 2 ), ind2( j, 1 ) );
                // 'cutZeroStart:90' r2d  = rd( : , ind2( j, 2 ), ind2( j, 1 ) );
                // 'cutZeroStart:91' r2dd = rdd( : , ind2( j, 2 ), ind2( j, 1 ) );
                // 'cutZeroStart:92' assert_continuity( r1, r1d, r1dd, r2, r2d, r2dd );
                // 'cutZeroStart:99' diff_r      = abs( r1    -r2 );
                // 'cutZeroStart:100' diff_rd     = abs( r1d   -r2d );
                // 'cutZeroStart:101' diff_rdd    = abs( r1dd  -r2dd );
                // 'cutZeroStart:103' tol = 1E-6;
                // 'cutZeroStart:106' ocn_assert( all( diff_r    < tol, 'all' ), "Continuity C0
                // failed", mfilename );
                for (int i39{0}; i39 < b_trueCount; i39++) {
                    b_r_data[i39] = r_data[(i39 + b_trueCount * (ind1[1][d_j] - 1)) +
                                           b_trueCount * 2 * (ind1[0][d_j] - 1)] -
                                    r_data[(i39 + b_trueCount * (ind2[1][d_j] - 1)) +
                                           b_trueCount * 2 * (ind2[0][d_j] - 1)];
                }
                d_r_data.set(&b_r_data[0], b_trueCount);
                r3.set_size(d_r_data.size(0));
                if (d_r_data.size(0) != 0) {
                    int i46;
                    i46 = d_r_data.size(0);
                    for (int i_k{0}; i_k < i46; i_k++) {
                        r3[i_k] = std::abs(d_r_data[i_k]);
                    }
                }
                b_x.set_size(r3.size(0));
                t_loop_ub = r3.size(0);
                for (int i47{0}; i47 < t_loop_ub; i47++) {
                    b_x[i47] = (r3[i47] < 1.0E-6);
                }
                d_varargout_1 = true;
                j_k = 0;
                exitg1 = false;
                while ((!exitg1) && (j_k <= b_x.size(0) - 1)) {
                    if (!b_x[j_k]) {
                        d_varargout_1 = false;
                        exitg1 = true;
                    } else {
                        j_k++;
                    }
                }
                cb_ocn_assert(d_varargout_1);
                // 'cutZeroStart:107' ocn_assert( all( diff_rd   < tol, 'all' ), "Continuity C1
                // failed", mfilename );
                for (int i50{0}; i50 < b_trueCount; i50++) {
                    c_rd_data[i50] = rd_data[(i50 + b_trueCount * (ind1[1][d_j] - 1)) +
                                             b_trueCount * 2 * (ind1[0][d_j] - 1)] -
                                     rd_data[(i50 + b_trueCount * (ind2[1][d_j] - 1)) +
                                             b_trueCount * 2 * (ind2[0][d_j] - 1)];
                }
                e_rd_data.set(&c_rd_data[0], b_trueCount);
                r3.set_size(e_rd_data.size(0));
                if (e_rd_data.size(0) != 0) {
                    int i51;
                    i51 = e_rd_data.size(0);
                    for (int k_k{0}; k_k < i51; k_k++) {
                        r3[k_k] = std::abs(e_rd_data[k_k]);
                    }
                }
                b_x.set_size(r3.size(0));
                w_loop_ub = r3.size(0);
                for (int i52{0}; i52 < w_loop_ub; i52++) {
                    b_x[i52] = (r3[i52] < 1.0E-6);
                }
                e_varargout_1 = true;
                l_k = 0;
                exitg1 = false;
                while ((!exitg1) && (l_k <= b_x.size(0) - 1)) {
                    if (!b_x[l_k]) {
                        e_varargout_1 = false;
                        exitg1 = true;
                    } else {
                        l_k++;
                    }
                }
                db_ocn_assert(e_varargout_1);
                // 'cutZeroStart:108' ocn_assert( all( diff_rdd   < tol, 'all' ),"Continuity C2
                // failed", mfilename );
                for (int i55{0}; i55 < b_trueCount; i55++) {
                    c_rdd_data[i55] = rdd_data[(i55 + b_trueCount * (ind1[1][d_j] - 1)) +
                                               b_trueCount * 2 * (ind1[0][d_j] - 1)] -
                                      rdd_data[(i55 + b_trueCount * (ind2[1][d_j] - 1)) +
                                               b_trueCount * 2 * (ind2[0][d_j] - 1)];
                }
                e_rdd_data.set(&c_rdd_data[0], b_trueCount);
                r3.set_size(e_rdd_data.size(0));
                if (e_rdd_data.size(0) != 0) {
                    int i57;
                    i57 = e_rdd_data.size(0);
                    for (int m_k{0}; m_k < i57; m_k++) {
                        r3[m_k] = std::abs(e_rdd_data[m_k]);
                    }
                }
                b_x.set_size(r3.size(0));
                bb_loop_ub = r3.size(0);
                for (int i59{0}; i59 < bb_loop_ub; i59++) {
                    b_x[i59] = (r3[i59] < 1.0E-6);
                }
                f_varargout_1 = true;
                n_k = 0;
                exitg1 = false;
                while ((!exitg1) && (n_k <= b_x.size(0) - 1)) {
                    if (!b_x[n_k]) {
                        f_varargout_1 = false;
                        exitg1 = true;
                    } else {
                        n_k++;
                    }
                }
                eb_ocn_assert(f_varargout_1);
            }
        }
        //      if( u >= curv.b_param + curv.a_param || u <= curv.b_param)
        //          u = curv.a_param / 2 + curv.b_param;
        //      end
        //      curv1               = curv;
        //      curv1.a_param       = u -curv1.b_param;
        //  curv1.UseConstJerk  = true;
        //  [ ~, ~, ~, jps ]    = zeroSpeedCurv( ctx, curv1, false );
        //  curv1.ConstJerk     = jps;
        //      curv1.Info.zspdmode = ZSpdMode.ZN;
        //      curv1.Info.gcode_source_line = curv.Info.gcode_source_line;
        //      curv2               = curv;
        //  curv2.UseConstJerk  = false;
        //      curv2.b_param       = u;
        //      curv2.a_param       = curv.a_param  + curv.b_param - curv2.b_param;
        //
        //      if( isAZeroEnd( curv ) )
        //          curv2.Info.zspdmode = ZSpdMode.NZ;
        //      else
        //          curv2.Info.zspdmode = ZSpdMode.NN;
        //      end
        //  if( coder.target("MATLAB") )
        //      check_continuity( ctx, curv, curv1, curv2 );
        //  end
        // 'feedratePlanningForceZeroStop:43' ctx.zero_forced_buffer( 2 ) = curv2ZN;
        // 'feedratePlanningForceZeroStop:44' curvQueue.set( ind2, curv2NN );
        ctx->q_split.set(ind1_tmp_tmp + 1, &curv2NN);
    } else {
        int d_loop_ub;
        int e_loop_ub;
        int g_loop_ub;
        int j_loop_ub;
        // 'feedratePlanningForceZeroStop:45' else
        //  Empty curve
        // 'feedratePlanningForceZeroStop:47' ctx.zero_forced_buffer( 2 ) = constrCurvStructType;
        //  constrCurvStructType : Constructs a constrCurvStruct with default values.
        // 'constrCurvStructType:4' if( nargin > 0 )
        // 'constrCurvStructType:6' else
        // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
        paramsDefaultCurv(&params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                          &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                          &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                          &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                          &params_gcodeInfoStruct_G91_1, &params_tool_toolno, &params_tool_pocketno,
                          &params_tool_offset, &params_tool_diameter, &params_tool_frontangle,
                          &params_tool_backangle, &params_tool_orientation, &params_spline,
                          params_R0, params_R1, params_Cprim, &expl_temp, params_evec, &b_expl_temp,
                          &c_expl_temp, params_CoeffP5, &d_expl_temp);
        // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
        // 'constrCurvStructType:12' else
        // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.tool, ...
        // 'constrCurvStructType:14'         params.spline, params.R0, params.R1, params.Cprim, ...
        // 'constrCurvStructType:15'         params.delta, params.evec, params.theta, params.pitch,
        // ... 'constrCurvStructType:16'         params.CoeffP5, params.Coeff );
        b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                           params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                           params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                           params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                           params_gcodeInfoStruct_G91_1, params_tool_toolno, params_tool_pocketno,
                           &params_tool_offset, params_tool_diameter, params_tool_frontangle,
                           params_tool_backangle, params_tool_orientation, &params_spline,
                           params_R0, params_R1, params_Cprim, params_evec, params_CoeffP5,
                           &e_expl_temp);
        ctx->zero_forced_buffer[1].Info = e_expl_temp.Info;
        ctx->zero_forced_buffer[1].tool = e_expl_temp.tool;
        ctx->zero_forced_buffer[1].sp = e_expl_temp.sp;
        ctx->zero_forced_buffer[1].R0.set_size(e_expl_temp.R0.size[0]);
        d_loop_ub = e_expl_temp.R0.size[0];
        for (int i11{0}; i11 < d_loop_ub; i11++) {
            ctx->zero_forced_buffer[1].R0[i11] = e_expl_temp.R0.data[i11];
        }
        ctx->zero_forced_buffer[1].R1.set_size(e_expl_temp.R1.size[0]);
        e_loop_ub = e_expl_temp.R1.size[0];
        for (int i16{0}; i16 < e_loop_ub; i16++) {
            ctx->zero_forced_buffer[1].R1[i16] = e_expl_temp.R1.data[i16];
        }
        ctx->zero_forced_buffer[1].delta = e_expl_temp.delta;
        ctx->zero_forced_buffer[1].CorrectedHelixCenter[0] = e_expl_temp.CorrectedHelixCenter[0];
        ctx->zero_forced_buffer[1].evec[0] = e_expl_temp.evec[0];
        ctx->zero_forced_buffer[1].CorrectedHelixCenter[1] = e_expl_temp.CorrectedHelixCenter[1];
        ctx->zero_forced_buffer[1].evec[1] = e_expl_temp.evec[1];
        ctx->zero_forced_buffer[1].CorrectedHelixCenter[2] = e_expl_temp.CorrectedHelixCenter[2];
        ctx->zero_forced_buffer[1].evec[2] = e_expl_temp.evec[2];
        ctx->zero_forced_buffer[1].theta = e_expl_temp.theta;
        ctx->zero_forced_buffer[1].pitch = e_expl_temp.pitch;
        ctx->zero_forced_buffer[1].CoeffP5.set_size(e_expl_temp.CoeffP5.size(0),
                                                    e_expl_temp.CoeffP5.size(1));
        g_loop_ub = e_expl_temp.CoeffP5.size(1);
        for (int i19{0}; i19 < g_loop_ub; i19++) {
            int h_loop_ub;
            h_loop_ub = e_expl_temp.CoeffP5.size(0);
            for (int i21{0}; i21 < h_loop_ub; i21++) {
                ctx->zero_forced_buffer[1]
                    .CoeffP5[i21 + ctx->zero_forced_buffer[1].CoeffP5.size(0) * i19] =
                    e_expl_temp.CoeffP5[i21 + e_expl_temp.CoeffP5.size(0) * i19];
            }
        }
        ctx->zero_forced_buffer[1].sp_index = e_expl_temp.sp_index;
        ctx->zero_forced_buffer[1].i_begin_sp = e_expl_temp.i_begin_sp;
        ctx->zero_forced_buffer[1].i_end_sp = e_expl_temp.i_end_sp;
        ctx->zero_forced_buffer[1].index_smooth = e_expl_temp.index_smooth;
        ctx->zero_forced_buffer[1].UseConstJerk = e_expl_temp.UseConstJerk;
        ctx->zero_forced_buffer[1].ConstJerk = e_expl_temp.ConstJerk;
        ctx->zero_forced_buffer[1].Coeff.set_size(e_expl_temp.Coeff.size(0));
        j_loop_ub = e_expl_temp.Coeff.size(0);
        for (int i24{0}; i24 < j_loop_ub; i24++) {
            ctx->zero_forced_buffer[1].Coeff[i24] = e_expl_temp.Coeff[i24];
        }
        ctx->zero_forced_buffer[1].a_param = e_expl_temp.a_param;
        ctx->zero_forced_buffer[1].b_param = e_expl_temp.b_param;
    }
    //  Get window of interest in from a given queue
    // 'feedratePlanningForceZeroStop:51' [ window, NWindow ] = feedratePlanningGetwindow( ctx.k0,
    // NWindow, curvQueue );
    //  feedratePlanningGetwindow :
    //
    //  Inputs :
    //    k0          : Index in the optimization
    //    NHorz       : Number of curves in the optimization window
    //    q_curves    : Queue of curve structures
    //
    //  Outputs :
    //    window      : Window of curves structure
    //    NWindow     : Number of curves in the structures
    //
    // 'feedratePlanningGetwindow:15' window = repmat( constrCurvStructType, 1, NHorz );
    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
    // 'constrCurvStructType:4' if( nargin > 0 )
    // 'constrCurvStructType:6' else
    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
    paramsDefaultCurv(&params_gcodeInfoStruct_Type, &params_gcodeInfoStruct_zspdmode,
                      &params_gcodeInfoStruct_TRAFO, &params_gcodeInfoStruct_HSC,
                      &params_gcodeInfoStruct_FeedRate, &params_gcodeInfoStruct_SpindleSpeed,
                      &params_gcodeInfoStruct_gcode_source_line, &params_gcodeInfoStruct_G91,
                      &params_gcodeInfoStruct_G91_1, &params_tool_toolno, &params_tool_pocketno,
                      &params_tool_offset, &params_tool_diameter, &params_tool_frontangle,
                      &params_tool_backangle, &params_tool_orientation, &params_spline, params_R0,
                      params_R1, params_Cprim, &f_expl_temp, params_evec, &g_expl_temp,
                      &h_expl_temp, params_CoeffP5, &i_expl_temp);
    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
    // 'constrCurvStructType:12' else
    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.tool, ...
    // 'constrCurvStructType:14'         params.spline, params.R0, params.R1, params.Cprim, ...
    // 'constrCurvStructType:15'         params.delta, params.evec, params.theta, params.pitch, ...
    // 'constrCurvStructType:16'         params.CoeffP5, params.Coeff );
    b_constrCurvStruct(params_gcodeInfoStruct_Type, params_gcodeInfoStruct_zspdmode,
                       params_gcodeInfoStruct_TRAFO, params_gcodeInfoStruct_HSC,
                       params_gcodeInfoStruct_FeedRate, params_gcodeInfoStruct_SpindleSpeed,
                       params_gcodeInfoStruct_gcode_source_line, params_gcodeInfoStruct_G91,
                       params_gcodeInfoStruct_G91_1, params_tool_toolno, params_tool_pocketno,
                       &params_tool_offset, params_tool_diameter, params_tool_frontangle,
                       params_tool_backangle, params_tool_orientation, &params_spline, params_R0,
                       params_R1, params_Cprim, params_evec, params_CoeffP5, &j_expl_temp);
    e_expl_temp.R0.size[0] = j_expl_temp.R0.size[0];
    o_loop_ub = j_expl_temp.R0.size[0];
    if (o_loop_ub - 1 >= 0) {
        std::copy(&j_expl_temp.R0.data[0], &j_expl_temp.R0.data[o_loop_ub],
                  &e_expl_temp.R0.data[0]);
    }
    e_expl_temp.R1.size[0] = j_expl_temp.R1.size[0];
    p_loop_ub = j_expl_temp.R1.size[0];
    if (p_loop_ub - 1 >= 0) {
        std::copy(&j_expl_temp.R1.data[0], &j_expl_temp.R1.data[p_loop_ub],
                  &e_expl_temp.R1.data[0]);
    }
    e_expl_temp.CoeffP5.set_size(j_expl_temp.CoeffP5.size(0), j_expl_temp.CoeffP5.size(1));
    q_loop_ub = j_expl_temp.CoeffP5.size(1);
    for (int i37{0}; i37 < q_loop_ub; i37++) {
        int r_loop_ub;
        r_loop_ub = j_expl_temp.CoeffP5.size(0);
        for (int i42{0}; i42 < r_loop_ub; i42++) {
            e_expl_temp.CoeffP5[i42 + e_expl_temp.CoeffP5.size(0) * i37] =
                j_expl_temp.CoeffP5[i42 + j_expl_temp.CoeffP5.size(0) * i37];
        }
    }
    e_expl_temp.Coeff.set_size(j_expl_temp.Coeff.size(0));
    s_loop_ub = j_expl_temp.Coeff.size(0);
    for (int i43{0}; i43 < s_loop_ub; i43++) {
        e_expl_temp.Coeff[i43] = j_expl_temp.Coeff[i43];
    }
    C.Info = j_expl_temp.Info;
    C.tool = j_expl_temp.tool;
    C.sp = j_expl_temp.sp;
    C.R0.set_size(e_expl_temp.R0.size[0]);
    u_loop_ub = e_expl_temp.R0.size[0];
    for (int i48{0}; i48 < u_loop_ub; i48++) {
        C.R0[i48] = e_expl_temp.R0.data[i48];
    }
    C.R1.set_size(e_expl_temp.R1.size[0]);
    v_loop_ub = e_expl_temp.R1.size[0];
    for (int i49{0}; i49 < v_loop_ub; i49++) {
        C.R1[i49] = e_expl_temp.R1.data[i49];
    }
    C.delta = j_expl_temp.delta;
    C.CorrectedHelixCenter[0] = j_expl_temp.CorrectedHelixCenter[0];
    C.evec[0] = j_expl_temp.evec[0];
    C.CorrectedHelixCenter[1] = j_expl_temp.CorrectedHelixCenter[1];
    C.evec[1] = j_expl_temp.evec[1];
    C.CorrectedHelixCenter[2] = j_expl_temp.CorrectedHelixCenter[2];
    C.evec[2] = j_expl_temp.evec[2];
    C.theta = j_expl_temp.theta;
    C.pitch = j_expl_temp.pitch;
    C.CoeffP5.set_size(e_expl_temp.CoeffP5.size(0), e_expl_temp.CoeffP5.size(1));
    x_loop_ub = e_expl_temp.CoeffP5.size(1);
    for (int i53{0}; i53 < x_loop_ub; i53++) {
        int y_loop_ub;
        y_loop_ub = e_expl_temp.CoeffP5.size(0);
        for (int i54{0}; i54 < y_loop_ub; i54++) {
            C.CoeffP5[i54 + C.CoeffP5.size(0) * i53] =
                e_expl_temp.CoeffP5[i54 + e_expl_temp.CoeffP5.size(0) * i53];
        }
    }
    C.sp_index = j_expl_temp.sp_index;
    C.i_begin_sp = j_expl_temp.i_begin_sp;
    C.i_end_sp = j_expl_temp.i_end_sp;
    C.index_smooth = j_expl_temp.index_smooth;
    C.UseConstJerk = j_expl_temp.UseConstJerk;
    C.ConstJerk = j_expl_temp.ConstJerk;
    C.Coeff.set_size(e_expl_temp.Coeff.size(0));
    ab_loop_ub = e_expl_temp.Coeff.size(0);
    for (int i56{0}; i56 < ab_loop_ub; i56++) {
        C.Coeff[i56] = e_expl_temp.Coeff[i56];
    }
    C.a_param = j_expl_temp.a_param;
    C.b_param = j_expl_temp.b_param;
    outsize_idx_1 = static_cast<int>(*NWindow);
    b_window.set_size(1, outsize_idx_1);
    for (int i58{0}; i58 < outsize_idx_1; i58++) {
        b_window[i58] = C;
    }
    // 'feedratePlanningGetwindow:17' kend = min( double( k0 + NHorz -1 ), q_curves.size );
    i60 = static_cast<int>(std::round(static_cast<double>(ctx->k0) + *NWindow));
    y = ctx->q_split.size();
    if (static_cast<double>(i60 - 1) > y) {
        kend = y;
    } else {
        kend = static_cast<unsigned int>(i60 - 1);
    }
    // 'feedratePlanningGetwindow:19' ind = 0;
    ind = 0U;
    // 'feedratePlanningGetwindow:21' for curv_ind = k0 : int32( kend )
    curv_ind = ctx->k0;
    exitg1 = false;
    while ((!exitg1) && (curv_ind <= static_cast<int>(kend))) {
        bool c_zeroFlag;
        // 'feedratePlanningGetwindow:22' ind = ind + 1;
        ind++;
        //  store the value in the queue
        // 'feedratePlanningGetwindow:25' curv            = q_curves.get( curv_ind );
        ctx->q_split.get(curv_ind, &curv);
        // 'feedratePlanningGetwindow:26' window( ind )   = curv;
        b_window[static_cast<int>(ind) - 1] = curv;
        //  Check if zero speed at the end
        // 'feedratePlanningGetwindow:28' if( isAZeroEnd( curv ) )
        //  isAZeroEnd : Return true if the curv ends with zero speed
        //
        //  Inputs :
        //  curv / Info / ZSpdMode : A structure containning the information of the
        //  curv zero speed.
        //
        //  Outputs :
        //  zeroFlag : Boolean value. TRUE mean zero flag
        // 'isAZeroEnd:10' zeroFlag = false;
        c_zeroFlag = false;
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
        if ((curv.Info.zspdmode == ZSpdMode_NZ) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
            // 'isAZeroEnd:18' zeroFlag = true;
            c_zeroFlag = true;
        }
        if (c_zeroFlag) {
            exitg1 = true;
        } else {
            curv_ind++;
        }
    }
    // 'feedratePlanningGetwindow:31' NWindow = ind;
    // 'feedratePlanningForceZeroStop:53' window  = [ window, ctx.zero_forced_buffer( 1 ) ];
    // 'feedratePlanningForceZeroStop:54' NWindow = NWindow + 1;
    //  Prepare the boundaries conditions of the problem
    // 'feedratePlanningForceZeroStop:57' [ ctx, window, NWindow ] = feedratePlanningSetupCurves(
    // ... 'feedratePlanningForceZeroStop:58'     ctx, window, NWindow );
    window.set_size(1, b_window.size(1) + 1);
    cb_loop_ub = b_window.size(1);
    for (int i61{0}; i61 < cb_loop_ub; i61++) {
        window[i61] = b_window[i61];
    }
    window[b_window.size(1)] = ctx->zero_forced_buffer[0];
    *NWindow = static_cast<double>(ind) + 1.0;
    feedratePlanningSetupCurves(ctx, window, NWindow);
    // 'feedratePlanningForceZeroStop:60' ctx.q_split = curvQueue;
    ctx->q_split = curvQueue;
}

} // namespace ocn

//
// File trailer for feedratePlanningForceZeroStop.cpp
//
// [EOF]
//
