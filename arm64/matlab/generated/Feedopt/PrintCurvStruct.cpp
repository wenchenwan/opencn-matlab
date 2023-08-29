//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PrintCurvStruct.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 29-Aug-2023 16:48:46
//

// Include Files
#include "PrintCurvStruct.h"
#include "EvalCurvStruct.h"
#include "TransP5LengthApprox.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "splineLength.h"
#include "string1.h"
#include "sum.h"
#include "unsafeSxfun.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
#include <cmath>
#include <stdio.h>

// Function Definitions
//
// function PrintCurvStruct(ctx, S)
//
// Arguments    : const FeedoptContext *ctx
//                const CurvStruct *S
// Return Type  : void
//
namespace ocn {
void PrintCurvStruct(const FeedoptContext *ctx, const CurvStruct *S)
{
    static const char cv3[9]{'<', 'U', 'N', 'K', 'N', 'O', 'W', 'N', '>'};
    static const char b_cv1[7]{'T', 'r', 'a', 'n', 's', 'P', '5'};
    static const char cv2[6]{'S', 'p', 'l', 'i', 'n', 'e'};
    static const char b_cv[5]{'H', 'e', 'l', 'i', 'x'};
    coder::rtString formatSpec;
    ::coder::array<double, 1U> P0;
    ::coder::array<double, 1U> P1;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> a__3;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    ::coder::array<int, 1U> t4_cfg_indCart;
    ::coder::array<int, 1U> t4_cfg_indRot;
    ::coder::array<int, 1U> t5_cfg_indCart;
    ::coder::array<int, 1U> t5_cfg_indRot;
    ::coder::array<int, 1U> t6_cfg_indCart;
    ::coder::array<int, 1U> t6_cfg_indRot;
    CurvStruct expl_temp;
    double validatedHoleFilling_f2;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int loop_ub;
    int varargin_1_size_idx_1;
    char b_varargin_1_data[10];
    char varargin_2_data[10];
    char varargin_1_data[9];
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'PrintCurvStruct:3' fprintf( '--------- CURVE STRUCT ---------\n' );
    printf("--------- CURVE STRUCT ---------\n");
    fflush(stdout);
    // 'PrintCurvStruct:4' fprintf( '%10s: %s\n', 'Type', CurveTypeToStr( S.Info.Type ) );
    // 'PrintCurvStruct:62' switch Type
    switch (S->Info.Type) {
    case CurveType_Line:
        // 'PrintCurvStruct:63' case CurveType.Line
        // 'PrintCurvStruct:64' str = 'Line';
        varargin_1_size_idx_1 = 4;
        varargin_1_data[0] = 'L';
        varargin_1_data[1] = 'i';
        varargin_1_data[2] = 'n';
        varargin_1_data[3] = 'e';
        break;
    case CurveType_Helix:
        // 'PrintCurvStruct:65' case CurveType.Helix
        // 'PrintCurvStruct:66' str = 'Helix';
        varargin_1_size_idx_1 = 5;
        for (int i{0}; i < 5; i++) {
            varargin_1_data[i] = b_cv[i];
        }
        break;
    case CurveType_TransP5:
        // 'PrintCurvStruct:67' case CurveType.TransP5
        // 'PrintCurvStruct:68' str = 'TransP5';
        varargin_1_size_idx_1 = 7;
        for (int i1{0}; i1 < 7; i1++) {
            varargin_1_data[i1] = b_cv1[i1];
        }
        break;
    case CurveType_Spline:
        // 'PrintCurvStruct:69' case CurveType.Spline
        // 'PrintCurvStruct:70' str = 'Spline';
        varargin_1_size_idx_1 = 6;
        for (int i2{0}; i2 < 6; i2++) {
            varargin_1_data[i2] = cv2[i2];
        }
        break;
    default:
        // 'PrintCurvStruct:71' otherwise
        // 'PrintCurvStruct:72' str = '<UNKNOWN>';
        varargin_1_size_idx_1 = 9;
        for (int i3{0}; i3 < 9; i3++) {
            varargin_1_data[i3] = cv3[i3];
        }
        break;
    }
    std::copy(&varargin_1_data[0], &varargin_1_data[varargin_1_size_idx_1], &varargin_2_data[0]);
    varargin_2_data[varargin_1_size_idx_1] = '\x00';
    printf("%10s: %s\n", "Type", &varargin_2_data[0]);
    fflush(stdout);
    // 'PrintCurvStruct:6' switch S.Info.Type
    switch (S->Info.Type) {
    case CurveType_Line:
        // 'PrintCurvStruct:7' case CurveType.Line
        break;
    case CurveType_Helix:
        // 'PrintCurvStruct:9' case CurveType.Helix
        // 'PrintCurvStruct:10' fprintf( '%10s: [%.3f %.3f %.3f]\n', 'evec', S.evec(1), S.evec(2),
        // S.evec(3) )
        printf("%10s: [%.3f %.3f %.3f]\n", "evec", S->evec[0], S->evec[1], S->evec[2]);
        fflush(stdout);
        // 'PrintCurvStruct:11' fprintf( '%10s: %.3f\n', 'theta', S.theta );
        printf("%10s: %.3f\n", "theta", S->theta);
        fflush(stdout);
        // 'PrintCurvStruct:12' fprintf( '%10s: %.3f\n', 'pitch', S.pitch );
        printf("%10s: %.3f\n", "pitch", S->pitch);
        fflush(stdout);
        break;
    case CurveType_TransP5: {
        int i6;
        // 'PrintCurvStruct:13' case CurveType.TransP5
        // 'PrintCurvStruct:14' fprintf( ' CoeffP5: \n' );
        printf(" CoeffP5: \n");
        fflush(stdout);
        // 'PrintCurvStruct:15' fprintf( '| ' )
        printf("| ");
        fflush(stdout);
        // 'PrintCurvStruct:16' [ NLine, NRow ] = size( S.CoeffP5 );
        // 'PrintCurvStruct:17' for j = 1 : NLine
        i6 = S->CoeffP5.size(0);
        for (int j{0}; j < i6; j++) {
            // 'PrintCurvStruct:18' for k = 1 : NRow
            for (int k{0}; k < 6; k++) {
                // 'PrintCurvStruct:19' fprintf( '%.3f ', S.CoeffP5( j, k ) )
                printf("%.3f ", S->CoeffP5[j + S->CoeffP5.size(0) * k]);
                fflush(stdout);
            }
            // 'PrintCurvStruct:21' fprintf( '| ' )
            printf("| ");
            fflush(stdout);
        }
        // 'PrintCurvStruct:23' fprintf( '\n' )
        printf("\n");
        fflush(stdout);
        // 'PrintCurvStruct:24' fprintf( 'FeedRate: %.2f\n', S.Info.FeedRate )
        printf("FeedRate: %.2f\n", S->Info.FeedRate);
        fflush(stdout);
    } break;
    case CurveType_Spline:
        // 'PrintCurvStruct:25' case CurveType.Spline
        break;
    default:
        // 'PrintCurvStruct:26' otherwise
        // 'PrintCurvStruct:27' fprintf( '!!! Type = %d, UNKNOWN !!!\n', int32( S.Info.Type ) )
        printf("!!! Type = %d, UNKNOWN !!!\n", static_cast<int>(S->Info.Type));
        fflush(stdout);
        break;
    }
    // 'PrintCurvStruct:29' P0 = EvalCurvStruct( ctx, S, 0 );
    t4_cfg_indCart.set_size(ctx->cfg.indCart.size[0]);
    loop_ub = ctx->cfg.indCart.size[0];
    for (int i4{0}; i4 < loop_ub; i4++) {
        t4_cfg_indCart[i4] = ctx->cfg.indCart.data[i4];
    }
    t4_cfg_indRot.set_size(ctx->cfg.indRot.size[0]);
    b_loop_ub = ctx->cfg.indRot.size[0];
    for (int i5{0}; i5 < b_loop_ub; i5++) {
        t4_cfg_indRot[i5] = ctx->cfg.indRot.data[i5];
    }
    j_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                     ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                     ctx->cfg.maskRot.size, t4_cfg_indCart, t4_cfg_indRot, ctx->cfg.NumberAxis,
                     ctx->cfg.NCart, ctx->cfg.NRot, S, P0);
    // 'PrintCurvStruct:30' P1 = EvalCurvStruct( ctx, S, 1 );
    t5_cfg_indCart.set_size(ctx->cfg.indCart.size[0]);
    c_loop_ub = ctx->cfg.indCart.size[0];
    for (int i7{0}; i7 < c_loop_ub; i7++) {
        t5_cfg_indCart[i7] = ctx->cfg.indCart.data[i7];
    }
    t5_cfg_indRot.set_size(ctx->cfg.indRot.size[0]);
    d_loop_ub = ctx->cfg.indRot.size[0];
    for (int i8{0}; i8 < d_loop_ub; i8++) {
        t5_cfg_indRot[i8] = ctx->cfg.indRot.data[i8];
    }
    k_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                     ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                     ctx->cfg.maskRot.size, t5_cfg_indCart, t5_cfg_indRot, ctx->cfg.NumberAxis,
                     ctx->cfg.NCart, ctx->cfg.NRot, S, P1);
    // 'PrintCurvStruct:31' fprintf( '%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n',...
    // 'PrintCurvStruct:32'     'P', P0(1), P0(2), P0(3), P1(1), P1(2), P1(3) )
    printf("%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n", "P", P0[0], P0[1], P0[2], P1[0], P1[1],
           P1[2]);
    fflush(stdout);
    // 'PrintCurvStruct:33' fprintf( '%10s: %e\n', 'Length', LengthCurv( ctx, S, 0, 1 ) );
    // 'LengthCurv:3' if ( curv.Info.Type == CurveType.Helix ) || ( curv.Info.Type == CurveType.Line
    // )
    if ((S->Info.Type == CurveType_Helix) || (S->Info.Type == CurveType_Line)) {
        int e_loop_ub;
        // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
        l_EvalCurvStruct(&ctx->cfg, S, a__1, r1D, a__2, a__3);
        // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        r.set_size(r1D.size(0));
        e_loop_ub = r1D.size(0);
        for (int i10{0}; i10 < e_loop_ub; i10++) {
            double varargin_1;
            varargin_1 = r1D[i10];
            r[i10] = std::pow(varargin_1, 2.0);
        }
        validatedHoleFilling_f2 = std::sqrt(coder::sum(r));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
    } else if (S->Info.Type == CurveType_Spline) {
        // 'LengthCurv:6' elseif ( curv.Info.Type == CurveType.Spline )
        // 'LengthCurv:7' a        = curv.a_param;
        // 'LengthCurv:8' b        = curv.b_param;
        // 'LengthCurv:9' u0_tilda = a * u0 + b;
        // 'LengthCurv:10' u1_tilda = a * u1 + b;
        // 'LengthCurv:11' spline   = ctx.q_spline.get( curv.sp_index );
        ctx->q_spline.get(S->sp_index, &expl_temp);
        // 'LengthCurv:12' [ L ]    = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda );
        validatedHoleFilling_f2 =
            splineLength(ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, expl_temp.sp.Bl.handle,
                         expl_temp.sp.Bl.order, expl_temp.sp.coeff, expl_temp.sp.knots,
                         expl_temp.sp.Lk, S->b_param, S->a_param + S->b_param);
    } else if (S->Info.Type == CurveType_TransP5) {
        // 'LengthCurv:13' elseif ( curv.Info.Type == CurveType.TransP5 )
        // 'LengthCurv:14' L = TransP5LengthApprox( curv );
        validatedHoleFilling_f2 = TransP5LengthApprox(S->CoeffP5);
    } else {
        char message[29];
        // 'LengthCurv:15' else
        // 'LengthCurv:16' c_assert(false, 'BAD CURVE TYPE IN LENGTH CURV');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i9{0}; i9 < 29; i9++) {
            message[i9] = cv1[i9];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        // 'LengthCurv:17' L = 0;
        validatedHoleFilling_f2 = 0.0;
    }
    printf("%10s: %e\n", "Length", validatedHoleFilling_f2);
    fflush(stdout);
    // 'PrintCurvStruct:34' fprintf( 'ZSpdMode: %s\n', PrintZSpdMode( S.Info.zspdmode ) )
    // 'PrintCurvStruct:47' switch m
    switch (S->Info.zspdmode) {
    case ZSpdMode_NN:
        // 'PrintCurvStruct:48' case ZSpdMode.NN
        // 'PrintCurvStruct:49' str = "NN";
        formatSpec.Value.size[0] = 1;
        formatSpec.Value.size[1] = 2;
        formatSpec.Value.data[0] = 'N';
        formatSpec.Value.data[1] = 'N';
        break;
    case ZSpdMode_ZN:
        // 'PrintCurvStruct:50' case ZSpdMode.ZN
        // 'PrintCurvStruct:51' str = "ZN";
        formatSpec.Value.size[0] = 1;
        formatSpec.Value.size[1] = 2;
        formatSpec.Value.data[0] = 'Z';
        formatSpec.Value.data[1] = 'N';
        break;
    case ZSpdMode_NZ:
        // 'PrintCurvStruct:52' case ZSpdMode.NZ
        // 'PrintCurvStruct:53' str = "NZ";
        formatSpec.Value.size[0] = 1;
        formatSpec.Value.size[1] = 2;
        formatSpec.Value.data[0] = 'N';
        formatSpec.Value.data[1] = 'Z';
        break;
    default:
        // 'PrintCurvStruct:54' case ZSpdMode.ZZ
        // 'PrintCurvStruct:55' str = "ZZ";
        formatSpec.Value.size[0] = 1;
        formatSpec.Value.size[1] = 2;
        formatSpec.Value.data[0] = 'Z';
        formatSpec.Value.data[1] = 'Z';
        break;
    }
    for (int i11{0}; i11 < 2; i11++) {
        b_varargin_1_data[i11] = formatSpec.Value.data[i11];
    }
    b_varargin_1_data[2] = '\x00';
    printf("ZSpdMode: %s\n", &b_varargin_1_data[0]);
    fflush(stdout);
    // 'PrintCurvStruct:35' fprintf( 'FeedRate: %.2f\n', S.Info.FeedRate )
    printf("FeedRate: %.2f\n", S->Info.FeedRate);
    fflush(stdout);
    // 'PrintCurvStruct:36' if S.UseConstJerk
    if (S->UseConstJerk) {
        double b_unnamed_idx_0;
        double k_vec;
        double n;
        double u;
        double ud_vec;
        double udd;
        double unnamed_idx_0;
        double y;
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i16;
        int i_loop_ub;
        bool isEnd;
        // 'PrintCurvStruct:37' isEnd = false;
        isEnd = false;
        // 'PrintCurvStruct:38' if( S.Info.zspdmode == ZSpdMode.NZ )
        if (S->Info.zspdmode == ZSpdMode_NZ) {
            // 'PrintCurvStruct:38' isEnd = true;
            isEnd = true;
        }
        // 'PrintCurvStruct:39' [v_0, at_0] = calcZeroConstraints( ctx, S, isEnd );
        t6_cfg_indCart.set_size(ctx->cfg.indCart.size[0]);
        f_loop_ub = ctx->cfg.indCart.size[0];
        for (int i12{0}; i12 < f_loop_ub; i12++) {
            t6_cfg_indCart[i12] = ctx->cfg.indCart.data[i12];
        }
        t6_cfg_indRot.set_size(ctx->cfg.indRot.size[0]);
        g_loop_ub = ctx->cfg.indRot.size[0];
        for (int i13{0}; i13 < g_loop_ub; i13++) {
            t6_cfg_indRot[i13] = ctx->cfg.indRot.data[i13];
        }
        //  calcZeroConstraints : Compute the velocity and acceleration
        //  required for the continuity at zero start.
        //  Inputs :
        //  ctx   : The context
        //  Curv  : The curve
        //  isEnd : (boolean) Is the end of the curve
        //  Outputs :
        //  v_0   : Norm of the velocity
        //  at_0  : Norm of the tangential acceleration
        // 'calcZeroConstraints:12' jps = curv.ConstJerk;
        // 'calcZeroConstraints:14' if( isEnd )
        if (isEnd) {
            // 'calcZeroConstraints:15' k  = 0;
            // 'constJerkU:23' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
            // 'constJerkU:24' k_vec  = k_max - k_vec;
            k_vec = std::pow(6.0 / S->ConstJerk, 0.33333333333333331);
        } else {
            // 'calcZeroConstraints:16' else
            // 'calcZeroConstraints:17' k   = ( 6 / jps )^( 1 / 3 );
            k_vec = std::pow(6.0 / S->ConstJerk, 0.33333333333333331);
        }
        // 'calcZeroConstraints:20' [ u, ud, udd, uddd ]    = constJerkU( jps, k, isEnd );
        //  constJerkU : Compute u and its derivative based on the pseudo jerk
        //  approximation.
        //  Inputs :
        //    pseudoJerk :  [ N x 1 ] The pseudo constant Jerk
        //    k_vec      :  [ 1 x M ] The time vector
        //    isEnd      :  ( Boolean ) Is the end of the Curve.
        //    a          :  Curve parameter a for affine transforme
        //    b          :  Curve parameter b for affine transforme
        //  Outputs :
        //    u          :  [ N x M ]
        //    ud         :  [ N x M ]
        //    udd        :  [ N x M ]
        //    uddd       :  [ N x M ]
        // 'constJerkU:16' if( coder.target( "MATLAB" ) )
        // 'constJerkU:22' if( isEnd )
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:28' uddd    = pseudoJerk .* ones( size( k_vec ) );
        // 'constJerkU:29' udd     = pseudoJerk .* k_vec;
        udd = S->ConstJerk * k_vec;
        // 'constJerkU:30' ud      = pseudoJerk .* k_vec .^2 / 2;
        // 'constJerkU:31' u       = pseudoJerk .* k_vec .^3 / 6;
        u = S->ConstJerk * std::pow(k_vec, 3.0) / 6.0;
        // 'constJerkU:33' u( u > 1 ) = 1;
        unnamed_idx_0 = u;
        if (u > 1.0) {
            unnamed_idx_0 = 1.0;
        }
        // 'constJerkU:34' u( u < 0 ) = 0;
        b_unnamed_idx_0 = unnamed_idx_0;
        if (unnamed_idx_0 < 0.0) {
            b_unnamed_idx_0 = 0.0;
        }
        u = b_unnamed_idx_0;
        // 'constJerkU:36' if( isEnd )
        if (isEnd) {
            //  Reverse time ( Backward-like integration )
            // 'constJerkU:37' u    = 1 - u;
            u = 1.0 - b_unnamed_idx_0;
            // 'constJerkU:38' ud   = ud;
            // 'constJerkU:39' udd  = -udd;
            udd = -udd;
            // 'constJerkU:40' uddd = uddd;
        }
        // 'calcZeroConstraints:22' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u );
        i_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                         ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                         ctx->cfg.maskRot.size, t6_cfg_indCart, t6_cfg_indRot, ctx->cfg.NumberAxis,
                         ctx->cfg.NCart, ctx->cfg.NRot, S, u, r0D, r1D, r2D, r3D);
        // 'calcZeroConstraints:24' [ ~, V, A, ~ ]          = calcRVAJfromUWithoutCurv( ud, udd,
        // uddd, r0D, ... 'calcZeroConstraints:25'                           r1D, r2D, r3D );
        ud_vec = S->ConstJerk * (k_vec * k_vec) / 2.0;
        //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
        //  jerk for a given set of u variable.
        //  Inputs :
        //    ud_vec  : [ 1 x M ] The vector of first derivative of u
        //    udd_vec : [ 1 x M ] The vector of second derivative of ddu
        //    uddd_vec: [ 1 x M ] The vector of third derivative of ddu
        //    r0D     : [ 1 x M ] The vector of r
        //    r1D     : [ 1 x M ] The vector of first derivative of r
        //    r2D     : [ 1 x M ] The vector of second derivative of r
        //    r3D     : [ 1 x M ] The vector of second derivative of r
        //  Outputs :
        //    R   : [ N x M ] pose
        //    V   : [ N x M ] velocity
        //    A   : [ N x M ] acceleration
        //    J   : [ N x M ] jerk
        // 'calcRVAJfromUWithoutCurv:18' R = r0D;
        // 'calcRVAJfromUWithoutCurv:19' V = r1D .* ud_vec;
        // 'calcRVAJfromUWithoutCurv:20' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        y = ud_vec * ud_vec;
        // 'calcRVAJfromUWithoutCurv:21' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec; 'calcZeroConstraints:27' [ vNorm, atNorm ]       = calcNormVNormAT( V, A,
        // r1D );
        //  calcNormVNormAT : Compute the norm of velocity and the norm of tangential
        //  acceleration.
        //  Inputs :
        //  V     : The velovity vector
        //  A     : The acceleration vector
        //  r1D   : The partial derivative of R
        //  Outputs :
        //  vNorm   : Norm of the velocity
        //  atNorm  : Norm of the tangential acceleration
        // 'calcNormVNormAT:12' vNorm   = MyNorm( V );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'calcNormVNormAT:13' t       = r1D / MyNorm( r1D );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        r.set_size(r1D.size(0));
        h_loop_ub = r1D.size(0);
        for (int i14{0}; i14 < h_loop_ub; i14++) {
            double b_varargin_1;
            b_varargin_1 = r1D[i14];
            r[i14] = std::pow(b_varargin_1, 2.0);
        }
        n = std::sqrt(coder::sum(r));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'calcNormVNormAT:14' atNorm  = MyNorm( A.*t );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'PrintCurvStruct:40' fprintf( 'ConstJerk: %e\n', S.ConstJerk )
        printf("ConstJerk: %e\n", S->ConstJerk);
        fflush(stdout);
        // 'PrintCurvStruct:41' fprintf( 'v_0      : %f\n', v_0 )
        r.set_size(r1D.size(0));
        i_loop_ub = r1D.size(0);
        for (int i15{0}; i15 < i_loop_ub; i15++) {
            double c_varargin_1;
            c_varargin_1 = r1D[i15] * ud_vec;
            r[i15] = std::pow(c_varargin_1, 2.0);
        }
        printf("v_0      : %f\n", std::sqrt(coder::sum(r)));
        fflush(stdout);
        // 'PrintCurvStruct:42' fprintf( 'at_0     : %f\n', at_0 )
        if (r2D.size(0) == 1) {
            i16 = r1D.size(0);
        } else {
            i16 = r2D.size(0);
        }
        if ((r2D.size(0) == r1D.size(0)) && (i16 == r1D.size(0))) {
            int j_loop_ub;
            r.set_size(r2D.size(0));
            j_loop_ub = r2D.size(0);
            for (int i17{0}; i17 < j_loop_ub; i17++) {
                double d_varargin_1;
                d_varargin_1 = (r2D[i17] * y + r1D[i17] * udd) * (r1D[i17] / n);
                r[i17] = std::pow(d_varargin_1, 2.0);
            }
        } else {
            binary_expand_op(r, r2D, y, r1D, udd, n);
        }
        printf("at_0     : %f\n", std::sqrt(coder::sum(r)));
        fflush(stdout);
    }
}

} // namespace ocn

//
// File trailer for PrintCurvStruct.cpp
//
// [EOF]
//
