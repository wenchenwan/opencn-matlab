
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: PrintCurvStruct.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "PrintCurvStruct.h"
#include "EvalCurvStruct.h"
#include "TransP5LengthApprox.h"
#include "ocn_assert.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
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
// function PrintCurvStruct( ctx, S )
//
// PrintCurvStruct : Print the input structure.
//
//  Inputs :
//    ctx :   The contexte of the compuational chain
//    S :     The Curvs structure to print
//
//
// Arguments    : const FeedoptContext *ctx
//                const CurvStruct *S
// Return Type  : void
//
namespace ocn {
void PrintCurvStruct(const FeedoptContext *ctx, const CurvStruct *S)
{
    static const char b_cv3[9]{'<', 'U', 'N', 'K', 'N', 'O', 'W', 'N', '>'};
    static const char b_cv1[7]{'T', 'r', 'a', 'n', 's', 'P', '5'};
    static const char b_cv2[6]{'S', 'p', 'l', 'i', 'n', 'e'};
    static const char b_cv[5]{'H', 'e', 'l', 'i', 'x'};
    coder::rtString formatSpec;
    ::coder::array<double, 1U> P0;
    ::coder::array<double, 1U> P1;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r0D;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    ::coder::array<int, 1U> t23_cfg_indCart;
    ::coder::array<int, 1U> t23_cfg_indRot;
    ::coder::array<int, 1U> t24_cfg_indCart;
    ::coder::array<int, 1U> t24_cfg_indRot;
    ::coder::array<int, 1U> t25_cfg_indCart;
    ::coder::array<int, 1U> t25_cfg_indRot;
    CurvStruct expl_temp;
    double validatedHoleFilling_f2;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int loop_ub;
    int varargin_1_size_idx_1;
    char b_varargin_1_data[2208];
    char varargin_2_data[10];
    char varargin_1_data[9];
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'PrintCurvStruct:9' fprintf( '--------- CURVE STRUCT ---------\n' );
    printf("--------- CURVE STRUCT ---------\n");
    fflush(stdout);
    // 'PrintCurvStruct:10' fprintf( '%10s: %s\n', 'Type', CurveTypeToStr( S.Info.Type ) );
    // 'PrintCurvStruct:68' switch Type
    switch (S->Info.Type) {
    case CurveType_Line:
        // 'PrintCurvStruct:69' case CurveType.Line
        // 'PrintCurvStruct:70' str = 'Line';
        varargin_1_size_idx_1 = 4;
        varargin_1_data[0] = 'L';
        varargin_1_data[1] = 'i';
        varargin_1_data[2] = 'n';
        varargin_1_data[3] = 'e';
        break;
    case CurveType_Helix:
        // 'PrintCurvStruct:71' case CurveType.Helix
        // 'PrintCurvStruct:72' str = 'Helix';
        varargin_1_size_idx_1 = 5;
        for (int i{0}; i < 5; i++) {
            varargin_1_data[i] = b_cv[i];
        }
        break;
    case CurveType_TransP5:
        // 'PrintCurvStruct:73' case CurveType.TransP5
        // 'PrintCurvStruct:74' str = 'TransP5';
        varargin_1_size_idx_1 = 7;
        for (int i1{0}; i1 < 7; i1++) {
            varargin_1_data[i1] = b_cv1[i1];
        }
        break;
    case CurveType_Spline:
        // 'PrintCurvStruct:75' case CurveType.Spline
        // 'PrintCurvStruct:76' str = 'Spline';
        varargin_1_size_idx_1 = 6;
        for (int i2{0}; i2 < 6; i2++) {
            varargin_1_data[i2] = b_cv2[i2];
        }
        break;
    default:
        // 'PrintCurvStruct:77' otherwise
        // 'PrintCurvStruct:78' str = '<UNKNOWN>';
        varargin_1_size_idx_1 = 9;
        for (int i3{0}; i3 < 9; i3++) {
            varargin_1_data[i3] = b_cv3[i3];
        }
        break;
    }
    std::copy(&varargin_1_data[0], &varargin_1_data[varargin_1_size_idx_1], &varargin_2_data[0]);
    varargin_2_data[varargin_1_size_idx_1] = '\x00';
    printf("%10s: %s\n", "Type", &varargin_2_data[0]);
    fflush(stdout);
    // 'PrintCurvStruct:12' switch S.Info.Type
    switch (S->Info.Type) {
    case CurveType_Line:
        // 'PrintCurvStruct:13' case CurveType.Line
        break;
    case CurveType_Helix:
        // 'PrintCurvStruct:15' case CurveType.Helix
        // 'PrintCurvStruct:16' fprintf( '%10s: [%.3f %.3f %.3f]\n', 'evec', S.evec(1), S.evec(2),
        // S.evec(3) )
        printf("%10s: [%.3f %.3f %.3f]\n", "evec", S->evec[0], S->evec[1], S->evec[2]);
        fflush(stdout);
        // 'PrintCurvStruct:17' fprintf( '%10s: %.3f\n', 'theta', S.theta );
        printf("%10s: %.3f\n", "theta", S->theta);
        fflush(stdout);
        // 'PrintCurvStruct:18' fprintf( '%10s: %.3f\n', 'pitch', S.pitch );
        printf("%10s: %.3f\n", "pitch", S->pitch);
        fflush(stdout);
        break;
    case CurveType_TransP5: {
        int i6;
        // 'PrintCurvStruct:19' case CurveType.TransP5
        // 'PrintCurvStruct:20' fprintf( ' CoeffP5: \n' );
        printf(" CoeffP5: \n");
        fflush(stdout);
        // 'PrintCurvStruct:21' fprintf( '| ' )
        printf("| ");
        fflush(stdout);
        // 'PrintCurvStruct:22' [ NLine, NRow ] = size( S.CoeffP5 );
        // 'PrintCurvStruct:23' for j = 1 : NLine
        i6 = S->CoeffP5.size(0);
        for (int j{0}; j < i6; j++) {
            int i7;
            // 'PrintCurvStruct:24' for k = 1 : NRow
            i7 = S->CoeffP5.size(1);
            for (int k{0}; k < i7; k++) {
                // 'PrintCurvStruct:25' fprintf( '%.3f ', S.CoeffP5( j, k ) )
                printf("%.3f ", S->CoeffP5[j + S->CoeffP5.size(0) * k]);
                fflush(stdout);
            }
            // 'PrintCurvStruct:27' fprintf( '| ' )
            printf("| ");
            fflush(stdout);
        }
        // 'PrintCurvStruct:29' fprintf( '\n' )
        printf("\n");
        fflush(stdout);
        // 'PrintCurvStruct:30' fprintf( 'FeedRate: %.2f\n', S.Info.FeedRate )
        printf("FeedRate: %.2f\n", S->Info.FeedRate);
        fflush(stdout);
    } break;
    case CurveType_Spline:
        // 'PrintCurvStruct:31' case CurveType.Spline
        break;
    default:
        // 'PrintCurvStruct:32' otherwise
        // 'PrintCurvStruct:33' fprintf( '!!! Type = %d, UNKNOWN !!!\n', int32( S.Info.Type ) )
        printf("!!! Type = %d, UNKNOWN !!!\n", static_cast<int>(S->Info.Type));
        fflush(stdout);
        break;
    }
    // 'PrintCurvStruct:35' P0 = EvalCurvStruct( ctx, S, 0 );
    t23_cfg_indCart.set_size(ctx->cfg.indCart.size[0]);
    loop_ub = ctx->cfg.indCart.size[0];
    for (int i4{0}; i4 < loop_ub; i4++) {
        t23_cfg_indCart[i4] = ctx->cfg.indCart.data[i4];
    }
    t23_cfg_indRot.set_size(ctx->cfg.indRot.size[0]);
    b_loop_ub = ctx->cfg.indRot.size[0];
    for (int i5{0}; i5 < b_loop_ub; i5++) {
        t23_cfg_indRot[i5] = ctx->cfg.indRot.data[i5];
    }
    l_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                     ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                     ctx->cfg.maskRot.size, t23_cfg_indCart, t23_cfg_indRot, ctx->cfg.NumberAxis,
                     ctx->cfg.NCart, ctx->cfg.NRot, S, P0);
    // 'PrintCurvStruct:36' P1 = EvalCurvStruct( ctx, S, 1 );
    t24_cfg_indCart.set_size(ctx->cfg.indCart.size[0]);
    c_loop_ub = ctx->cfg.indCart.size[0];
    for (int i8{0}; i8 < c_loop_ub; i8++) {
        t24_cfg_indCart[i8] = ctx->cfg.indCart.data[i8];
    }
    t24_cfg_indRot.set_size(ctx->cfg.indRot.size[0]);
    d_loop_ub = ctx->cfg.indRot.size[0];
    for (int i9{0}; i9 < d_loop_ub; i9++) {
        t24_cfg_indRot[i9] = ctx->cfg.indRot.data[i9];
    }
    m_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                     ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                     ctx->cfg.maskRot.size, t24_cfg_indCart, t24_cfg_indRot, ctx->cfg.NumberAxis,
                     ctx->cfg.NCart, ctx->cfg.NRot, S, P1);
    // 'PrintCurvStruct:37' fprintf( '%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n',...
    // 'PrintCurvStruct:38'     'P', P0(1), P0(2), P0(3), P1(1), P1(2), P1(3) )
    printf("%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n", "P", P0[0], P0[1], P0[2], P1[0], P1[1],
           P1[2]);
    fflush(stdout);
    // 'PrintCurvStruct:39' fprintf( '%10s: %e\n', 'Length', LengthCurv( ctx, S, 0, 1 ) );
    //  LengthCurv : Compute the curve length between  u0 and u1.
    //
    //  Inputs :
    //    ctx     : The context of the computational chain
    //    curv    : The curv to compute the length
    //    u0      : The starting u0
    //    u1      : The ending u1
    //
    //  Outputs :
    //    L       : The resulting length of the queue
    //
    // 'LengthCurv:13' if ( curv.Info.Type == CurveType.Helix ) || ...
    // 'LengthCurv:14'    ( curv.Info.Type == CurveType.Line )
    if ((S->Info.Type == CurveType_Helix) || (S->Info.Type == CurveType_Line)) {
        int e_loop_ub;
        // 'LengthCurv:15' [~, r1D] = EvalCurvStruct( ctx, curv, u0 );
        s_EvalCurvStruct(&ctx->cfg, S, a__1, r1D);
        // 'LengthCurv:16' L        = MyNorm( r1D ) * ( u1 - u0 );
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
        r.set_size(r1D.size(0));
        e_loop_ub = r1D.size(0);
        for (int i10{0}; i10 < e_loop_ub; i10++) {
            double varargin_1;
            varargin_1 = r1D[i10];
            r[i10] = std::pow(varargin_1, 2.0);
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
        validatedHoleFilling_f2 = std::sqrt(x);
    } else if (S->Info.Type == CurveType_Spline) {
        // 'LengthCurv:17' elseif ( curv.Info.Type == CurveType.Spline )
        // 'LengthCurv:18' a        = curv.a_param;
        // 'LengthCurv:19' b        = curv.b_param;
        // 'LengthCurv:20' u0_tilda = a * u0 + b;
        // 'LengthCurv:21' u1_tilda = a * u1 + b;
        // 'LengthCurv:22' spline   = ctx.q_spline.get( curv.sp_index );
        ctx->q_spline.get(S->sp_index, &expl_temp);
        // 'LengthCurv:23' [ L ]    = splineLength( ctx.cfg, spline, u0_tilda, u1_tilda );
        validatedHoleFilling_f2 =
            splineLength(ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, expl_temp.sp.Bl.handle,
                         expl_temp.sp.Bl.order, expl_temp.sp.coeff, expl_temp.sp.knots,
                         expl_temp.sp.Lk, S->b_param, S->a_param + S->b_param);
    } else if (S->Info.Type == CurveType_TransP5) {
        // 'LengthCurv:24' elseif ( curv.Info.Type == CurveType.TransP5 )
        // 'LengthCurv:25' a        = curv.a_param;
        // 'LengthCurv:26' b        = curv.b_param;
        // 'LengthCurv:27' u0_tilda = a * u0 + b;
        // 'LengthCurv:28' u1_tilda = a * u1 + b;
        // 'LengthCurv:29' L = TransP5LengthApprox( curv, u0_tilda, u1_tilda );
        validatedHoleFilling_f2 =
            TransP5LengthApprox(S->CoeffP5, S->b_param, S->a_param + S->b_param);
    } else {
        // 'LengthCurv:30' else
        // 'LengthCurv:31' ocn_assert( false, "BAD CURVE TYPE IN LENGTH CURV", mfilename );
        rb_ocn_assert();
        // 'LengthCurv:32' L = 0;
        validatedHoleFilling_f2 = 0.0;
    }
    printf("%10s: %e\n", "Length", validatedHoleFilling_f2);
    fflush(stdout);
    // 'PrintCurvStruct:40' fprintf( 'ZSpdMode: %s\n', PrintZSpdMode( S.Info.zspdmode ) )
    // 'PrintCurvStruct:53' switch m
    switch (S->Info.zspdmode) {
    case ZSpdMode_NN:
        // 'PrintCurvStruct:54' case ZSpdMode.NN
        // 'PrintCurvStruct:55' str = "NN";
        formatSpec.Value.size[0] = 1;
        formatSpec.Value.size[1] = 2;
        formatSpec.Value.data[0] = 'N';
        formatSpec.Value.data[1] = 'N';
        break;
    case ZSpdMode_ZN:
        // 'PrintCurvStruct:56' case ZSpdMode.ZN
        // 'PrintCurvStruct:57' str = "ZN";
        formatSpec.Value.size[0] = 1;
        formatSpec.Value.size[1] = 2;
        formatSpec.Value.data[0] = 'Z';
        formatSpec.Value.data[1] = 'N';
        break;
    case ZSpdMode_NZ:
        // 'PrintCurvStruct:58' case ZSpdMode.NZ
        // 'PrintCurvStruct:59' str = "NZ";
        formatSpec.Value.size[0] = 1;
        formatSpec.Value.size[1] = 2;
        formatSpec.Value.data[0] = 'N';
        formatSpec.Value.data[1] = 'Z';
        break;
    default:
        // 'PrintCurvStruct:60' case ZSpdMode.ZZ
        // 'PrintCurvStruct:61' str = "ZZ";
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
    // 'PrintCurvStruct:41' fprintf( 'FeedRate: %.2f\n', S.Info.FeedRate )
    printf("FeedRate: %.2f\n", S->Info.FeedRate);
    fflush(stdout);
    // 'PrintCurvStruct:42' if S.UseConstJerk
    if (S->UseConstJerk) {
        double b_unnamed_idx_0;
        double b_x;
        double d_x;
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
        // 'PrintCurvStruct:43' isEnd = false;
        isEnd = false;
        // 'PrintCurvStruct:44' if( S.Info.zspdmode == ZSpdMode.NZ )
        if (S->Info.zspdmode == ZSpdMode_NZ) {
            // 'PrintCurvStruct:44' isEnd = true;
            isEnd = true;
        }
        // 'PrintCurvStruct:45' [v_0, at_0] = calcZeroConstraints( ctx, S, isEnd );
        t25_cfg_indCart.set_size(ctx->cfg.indCart.size[0]);
        f_loop_ub = ctx->cfg.indCart.size[0];
        for (int i12{0}; i12 < f_loop_ub; i12++) {
            t25_cfg_indCart[i12] = ctx->cfg.indCart.data[i12];
        }
        t25_cfg_indRot.set_size(ctx->cfg.indRot.size[0]);
        g_loop_ub = ctx->cfg.indRot.size[0];
        for (int i13{0}; i13 < g_loop_ub; i13++) {
            t25_cfg_indRot[i13] = ctx->cfg.indRot.data[i13];
        }
        //  calcZeroConstraints : Compute the velocity and acceleration
        //  required for the continuity at zero start.
        //
        //  Inputs :
        //  ctx       : The context
        //  Curv      : The curve
        //  isEnd     : (boolean) Is the end of the curve
        //
        //  Outputs :
        //  vNorm     : Norm of the velocity
        //  atNorm    : Norm of the tangential acceleration
        //
        // 'calcZeroConstraints:15' jps = curv.ConstJerk;
        // 'calcZeroConstraints:17' if( isEnd )
        if (isEnd) {
            // 'calcZeroConstraints:18' k  = 0;
            // 'constJerkU:25' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
            // 'constJerkU:26' k_vec  = k_max - k_vec;
            k_vec = std::pow(6.0 / S->ConstJerk, 0.33333333333333331);
        } else {
            // 'calcZeroConstraints:19' else
            // 'calcZeroConstraints:20' k   = ( 6 / jps )^( 1 / 3 );
            k_vec = std::pow(6.0 / S->ConstJerk, 0.33333333333333331);
        }
        // 'calcZeroConstraints:23' [ u, ud, udd, uddd ]    = constJerkU( jps, k, isEnd, true );
        //  constJerkU : Compute u and its derivative based on the pseudo jerk
        //  approximation.
        //
        //  Inputs :
        //    pseudoJerk      :  [ N x 1 ] The constant Jerk value
        //    k_vec           :  [ 1 x M ] The time vector
        //    isEnd           :  ( Boolean ) Is the end of the Curve.
        //    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
        //
        //  Outputs :
        //    u               :  [ N x M ]
        //    ud              :  [ N x M ]
        //    udd             :  [ N x M ]
        //    uddd            :  [ N x M ]
        //
        // 'constJerkU:18' if( coder.target( "MATLAB" ) )
        // 'constJerkU:24' if( isEnd )
        //  Compute u and its derivatives based on constant jerk
        // 'constJerkU:30' uddd    = pseudoJerk .* ones( size( k_vec ) );
        // 'constJerkU:31' udd     = pseudoJerk .* k_vec;
        udd = S->ConstJerk * k_vec;
        // 'constJerkU:32' ud      = pseudoJerk .* k_vec .^2 / 2;
        // 'constJerkU:33' u       = pseudoJerk .* k_vec .^3 / 6;
        u = S->ConstJerk * std::pow(k_vec, 3.0) / 6.0;
        // 'constJerkU:35' if( forceLimits )
        // 'constJerkU:36' u( u > 1 ) = 1;
        unnamed_idx_0 = u;
        if (u > 1.0) {
            unnamed_idx_0 = 1.0;
        }
        // 'constJerkU:37' u( u < 0 ) = 0;
        b_unnamed_idx_0 = unnamed_idx_0;
        if (unnamed_idx_0 < 0.0) {
            b_unnamed_idx_0 = 0.0;
        }
        u = b_unnamed_idx_0;
        // 'constJerkU:40' if( isEnd )
        if (isEnd) {
            //  Reverse time ( Backward-like integration )
            // 'constJerkU:41' u    = 1 - u;
            u = 1.0 - b_unnamed_idx_0;
            // 'constJerkU:42' ud   = ud;
            // 'constJerkU:43' udd  = -udd;
            udd = -udd;
            // 'constJerkU:44' uddd = uddd;
        }
        // 'calcZeroConstraints:25' [ r0D, r1D, r2D, r3D ]  = EvalCurvStruct( ctx, curv, u );
        k_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                         ctx->cfg.maskCart.data, ctx->cfg.maskCart.size, ctx->cfg.maskRot.data,
                         ctx->cfg.maskRot.size, t25_cfg_indCart, t25_cfg_indRot,
                         ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot, S, u, r0D, r1D, r2D,
                         r3D);
        // 'calcZeroConstraints:27' [ ~, V, A, ~ ]          = calcRVAJfromUWithoutCurv( ud, udd,
        // uddd, r0D, ... 'calcZeroConstraints:28'                           r1D, r2D, r3D );
        ud_vec = S->ConstJerk * (k_vec * k_vec) / 2.0;
        //  calcRVAJfromU : Compute the pose, the velocity, the acceleration and the
        //  jerk for a given set of u variable.
        //
        //  Inputs :
        //    ud_vec      : [ 1 x M ] The vector of first derivative of u
        //    udd_vec     : [ 1 x M ] The vector of second derivative of ddu
        //    uddd_vec    : [ 1 x M ] The vector of third derivative of ddu
        //    r0D         : [ 1 x M ] The vector of r
        //    r1D         : [ 1 x M ] The vector of first derivative of r
        //    r2D         : [ 1 x M ] The vector of second derivative of r
        //    r3D         : [ 1 x M ] The vector of second derivative of r
        //
        //  Outputs :
        //    R           : [ N x M ] pose
        //    V           : [ N x M ] velocity
        //    A           : [ N x M ] acceleration
        //    J           : [ N x M ] jerk
        //
        // 'calcRVAJfromUWithoutCurv:21' R = r0D;
        // 'calcRVAJfromUWithoutCurv:22' V = r1D .* ud_vec;
        // 'calcRVAJfromUWithoutCurv:23' A = r2D .* ud_vec .^2 + r1D .* udd_vec;
        y = ud_vec * ud_vec;
        // 'calcRVAJfromUWithoutCurv:24' J = r3D .* ud_vec .^3 + 3 * r2D .* ud_vec .* udd_vec + r1D
        // .* uddd_vec; 'calcZeroConstraints:30' [ vNorm, atNorm ]       = calcNormVNormAT( V, A,
        // r1D );
        //  calcNormVNormAT : Compute the norm of velocity and the norm of tangential
        //  acceleration.
        //
        //  Inputs :
        //  V         : The velovity vector
        //  A         : The acceleration vector
        //  r1D       : The partial derivative of R
        //
        //  Outputs :
        //  vNorm     : Norm of the velocity
        //  atNorm    : Norm of the tangential acceleration
        //
        // 'calcNormVNormAT:15' vNorm   = MyNorm( V );
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
        r.set_size(r1D.size(0));
        h_loop_ub = r1D.size(0);
        for (int i14{0}; i14 < h_loop_ub; i14++) {
            double b_varargin_1;
            b_varargin_1 = r1D[i14] * ud_vec;
            r[i14] = std::pow(b_varargin_1, 2.0);
        }
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
        // 'calcNormVNormAT:16' t       = r1D / MyNorm( r1D );
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
        r.set_size(r1D.size(0));
        i_loop_ub = r1D.size(0);
        for (int i15{0}; i15 < i_loop_ub; i15++) {
            double c_varargin_1;
            c_varargin_1 = r1D[i15];
            r[i15] = std::pow(c_varargin_1, 2.0);
        }
        double c_x;
        c_x = coder::sum(r);
        //  mysqrt : Custom implementation of the sqrt method.
        //
        //  Inputs :
        //    x : Value used for the computation
        //  Outputs :
        //    y : Resulting value
        //
        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
        ocn_assert(c_x >= 0.0);
        // 'mysqrt:11' y = sqrt(x);
        n = std::sqrt(c_x);
        // 'calcNormVNormAT:17' atNorm  = MyNorm( A.*t );
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
        d_x = coder::sum(r);
        //  mysqrt : Custom implementation of the sqrt method.
        //
        //  Inputs :
        //    x : Value used for the computation
        //  Outputs :
        //    y : Resulting value
        //
        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
        ocn_assert(d_x >= 0.0);
        // 'mysqrt:11' y = sqrt(x);
        // 'PrintCurvStruct:46' fprintf( 'ConstJerk: %e\n', S.ConstJerk )
        printf("ConstJerk: %e\n", S->ConstJerk);
        fflush(stdout);
        // 'PrintCurvStruct:47' fprintf( 'v_0      : %f\n', v_0 )
        printf("v_0      : %f\n", std::sqrt(b_x));
        fflush(stdout);
        // 'PrintCurvStruct:48' fprintf( 'at_0     : %f\n', at_0 )
        printf("at_0     : %f\n", std::sqrt(d_x));
        fflush(stdout);
    }
}

} // namespace ocn

//
// File trailer for PrintCurvStruct.cpp
//
// [EOF]
//
