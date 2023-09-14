//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStructNoCtx.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 12:49:58
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
#include "opencn_matlab_types21.h"
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
// Arguments    : const bool cfg_maskTot_data[]
//                const int cfg_maskTot_size[2]
//                const bool cfg_maskCart_data[]
//                const int cfg_maskCart_size[2]
//                const bool cfg_maskRot_data[]
//                const int cfg_maskRot_size[2]
//                const ::coder::array<int, 1U> &cfg_indCart
//                const ::coder::array<int, 1U> &cfg_indRot
//                int cfg_NumberAxis
//                int cfg_NCart
//                int cfg_NRot
//                const CurvStruct *curv
//                const CurvStruct *spline
//                ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
namespace ocn {
void EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                         const bool cfg_maskCart_data[], const int cfg_maskCart_size[2],
                         const bool cfg_maskRot_data[], const int cfg_maskRot_size[2],
                         const ::coder::array<int, 1U> &cfg_indCart,
                         const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                         int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                         const CurvStruct *spline, ::coder::array<double, 2U> &u_vec,
                         ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D,
                         ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D)
{
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
    int b_k;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int k;
    int k_loop_ub;
    int loop_ub;
    int r_loop_ub;
    int scalarLB;
    int vectorUB;
    bool b_y;
    bool exitg1;
    bool y;
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:6' if any( u_vec > 1.0 )
    x.set_size(1, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        x[i] = (u_vec[i] > 1.0);
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
        // 'EvalCurvStructNoCtx:61' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:62' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:64' else
        // 'EvalCurvStructNoCtx:65' fprintf(err_msg);
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
        // 'EvalCurvStructNoCtx:61' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:62' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:64' else
        // 'EvalCurvStructNoCtx:65' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec < 0\n");
        fflush(stdout);
    }
    //
    // 'EvalCurvStructNoCtx:15' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:20' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis, u_vec.size(1));
    c_loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        for (int i3{0}; i3 < cfg_NumberAxis; i3++) {
            r0D[i3 + r0D.size(0) * i2] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:21' r1D = r0D;
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
    // 'EvalCurvStructNoCtx:21' r3D = r0D;
    r3D.set_size(cfg_NumberAxis, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        for (int i9{0}; i9 < cfg_NumberAxis; i9++) {
            r3D[i9 + r3D.size(0) * i8] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:23' a = curv.a_param;
    // 'EvalCurvStructNoCtx:24' b = curv.b_param;
    // 'EvalCurvStructNoCtx:26' u_vec_tilda = a * u_vec + b;
    u_vec_tilda.set_size(1, u_vec.size(1));
    g_loop_ub = u_vec.size(1);
    scalarLB = (u_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i10{0}; i10 <= vectorUB; i10 += 2) {
        __m128d r;
        r = _mm_loadu_pd(&u_vec[i10]);
        _mm_storeu_pd(&u_vec_tilda[i10], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(curv->a_param), r),
                                                    _mm_set1_pd(curv->b_param)));
    }
    for (int i10{scalarLB}; i10 < g_loop_ub; i10++) {
        u_vec_tilda[i10] = curv->a_param * u_vec[i10] + curv->b_param;
    }
    // 'EvalCurvStructNoCtx:28' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:29' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:30' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:31' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:32' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:34' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:35' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:36' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size, r0D, r1D, r2D,
                 r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:37' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:38' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int i_loop_ub;
            int m_loop_ub;
            int q_loop_ub;
            int u_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:39' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:40'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                      u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, r1, r2, r3, r4);
            i_loop_ub = r1.size(1);
            for (int i13{0}; i13 < i_loop_ub; i13++) {
                r0D[(cfg_indCart[0] + r0D.size(0) * i13) - 1] = r1[3 * i13];
                r0D[(cfg_indCart[1] + r0D.size(0) * i13) - 1] = r1[3 * i13 + 1];
                r0D[(cfg_indCart[2] + r0D.size(0) * i13) - 1] = r1[3 * i13 + 2];
            }
            m_loop_ub = r2.size(1);
            for (int i17{0}; i17 < m_loop_ub; i17++) {
                r1D[(cfg_indCart[0] + r1D.size(0) * i17) - 1] = r2[3 * i17];
                r1D[(cfg_indCart[1] + r1D.size(0) * i17) - 1] = r2[3 * i17 + 1];
                r1D[(cfg_indCart[2] + r1D.size(0) * i17) - 1] = r2[3 * i17 + 2];
            }
            q_loop_ub = r3.size(1);
            for (int i20{0}; i20 < q_loop_ub; i20++) {
                r2D[(cfg_indCart[0] + r2D.size(0) * i20) - 1] = r3[3 * i20];
                r2D[(cfg_indCart[1] + r2D.size(0) * i20) - 1] = r3[3 * i20 + 1];
                r2D[(cfg_indCart[2] + r2D.size(0) * i20) - 1] = r3[3 * i20 + 2];
            }
            u_loop_ub = r4.size(1);
            for (int i25{0}; i25 < u_loop_ub; i25++) {
                r3D[(cfg_indCart[0] + r3D.size(0) * i25) - 1] = r4[3 * i25];
                r3D[(cfg_indCart[1] + r3D.size(0) * i25) - 1] = r4[3 * i25 + 1];
                r3D[(cfg_indCart[2] + r3D.size(0) * i25) - 1] = r4[3 * i25 + 2];
            }
        }
        // 'EvalCurvStructNoCtx:42' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int l_loop_ub;
            int o_loop_ub;
            int s_loop_ub;
            int w_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:43' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:44'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size, r5, r6,
                     r7, r8);
            l_loop_ub = r5.size(1);
            for (int i16{0}; i16 < l_loop_ub; i16++) {
                int p_loop_ub;
                p_loop_ub = r5.size(0);
                for (int i19{0}; i19 < p_loop_ub; i19++) {
                    r0D[(cfg_indRot[i19] + r0D.size(0) * i16) - 1] = r5[i19 + r5.size(0) * i16];
                }
            }
            o_loop_ub = r6.size(1);
            for (int i18{0}; i18 < o_loop_ub; i18++) {
                int t_loop_ub;
                t_loop_ub = r6.size(0);
                for (int i24{0}; i24 < t_loop_ub; i24++) {
                    r1D[(cfg_indRot[i24] + r1D.size(0) * i18) - 1] = r6[i24 + r6.size(0) * i18];
                }
            }
            s_loop_ub = r7.size(1);
            for (int i23{0}; i23 < s_loop_ub; i23++) {
                int x_loop_ub;
                x_loop_ub = r7.size(0);
                for (int i27{0}; i27 < x_loop_ub; i27++) {
                    r2D[(cfg_indRot[i27] + r2D.size(0) * i23) - 1] = r7[i27 + r7.size(0) * i23];
                }
            }
            w_loop_ub = r8.size(1);
            for (int i26{0}; i26 < w_loop_ub; i26++) {
                int ab_loop_ub;
                ab_loop_ub = r8.size(0);
                for (int i30{0}; i30 < ab_loop_ub; i30++) {
                    r3D[(cfg_indRot[i30] + r3D.size(0) * i26) - 1] = r8[i30 + r8.size(0) * i26];
                }
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:46' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:47' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int bb_loop_ub;
        int cb_loop_ub;
        int i36;
        int unnamed_idx_0;
        int y_loop_ub;
        // 'EvalCurvStructNoCtx:48' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:49' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        y_loop_ub = u_vec_tilda.size(1);
        for (int i29{0}; i29 < y_loop_ub; i29++) {
            for (int i31{0}; i31 < unnamed_idx_0; i31++) {
                r1D[i31 + r1D.size(0) * i29] = 0.0;
            }
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        bb_loop_ub = u_vec_tilda.size(1);
        for (int i32{0}; i32 < bb_loop_ub; i32++) {
            for (int i33{0}; i33 < unnamed_idx_0; i33++) {
                r2D[i33 + r2D.size(0) * i32] = 0.0;
            }
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        cb_loop_ub = u_vec_tilda.size(1);
        for (int i34{0}; i34 < cb_loop_ub; i34++) {
            for (int i35{0}; i35 < unnamed_idx_0; i35++) {
                r3D[i35 + r3D.size(0) * i34] = 0.0;
            }
        }
        // 'EvalBSpline:20' for j = 1 : M
        i36 = spline->sp.coeff.size(0);
        r0D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        for (int j{0}; j < i36; j++) {
            int db_loop_ub;
            int eb_loop_ub;
            int fb_loop_ub;
            int gb_loop_ub;
            int hb_loop_ub;
            int i41;
            int jb_loop_ub;
            int kb_loop_ub;
            int lb_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
            r12.set_size(1, u_vec_tilda.size(1));
            db_loop_ub = u_vec_tilda.size(1);
            for (int i37{0}; i37 < db_loop_ub; i37++) {
                r12[i37] = 0.0;
            }
            // 'bspline_eval_vec:4' xd      = zeros(size(u));
            r13.set_size(1, u_vec_tilda.size(1));
            eb_loop_ub = u_vec_tilda.size(1);
            for (int i38{0}; i38 < eb_loop_ub; i38++) {
                r13[i38] = 0.0;
            }
            // 'bspline_eval_vec:5' xdd     = zeros(size(u));
            r14.set_size(1, u_vec_tilda.size(1));
            fb_loop_ub = u_vec_tilda.size(1);
            for (int i39{0}; i39 < fb_loop_ub; i39++) {
                r14[i39] = 0.0;
            }
            // 'bspline_eval_vec:6' xddd    = zeros(size(u));
            r15.set_size(1, u_vec_tilda.size(1));
            gb_loop_ub = u_vec_tilda.size(1);
            for (int i40{0}; i40 < gb_loop_ub; i40++) {
                r15[i40] = 0.0;
            }
            // 'bspline_eval_vec:8' for k = 1:length(u)
            i41 = u_vec_tilda.size(1);
            for (int c_k{0}; c_k < i41; c_k++) {
                int ib_loop_ub;
                // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
                r12[c_k] = u_vec_tilda[c_k];
                ib_loop_ub = spline->sp.coeff.size(1);
                b_spline.set_size(1, spline->sp.coeff.size(1));
                for (int i44{0}; i44 < ib_loop_ub; i44++) {
                    b_spline[i44] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i44];
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
            hb_loop_ub = r12.size(1);
            for (int i42{0}; i42 < hb_loop_ub; i42++) {
                r0D[j + r0D.size(0) * i42] = r12[i42];
            }
            jb_loop_ub = r13.size(1);
            for (int i43{0}; i43 < jb_loop_ub; i43++) {
                r1D[j + r1D.size(0) * i43] = r13[i43];
            }
            kb_loop_ub = r14.size(1);
            for (int i45{0}; i45 < kb_loop_ub; i45++) {
                r2D[j + r2D.size(0) * i45] = r14[i45];
            }
            lb_loop_ub = r15.size(1);
            for (int i46{0}; i46 < lb_loop_ub; i46++) {
                r3D[j + r3D.size(0) * i46] = r15[i46];
            }
        }
    } break;
    default: {
        char message[30];
        // 'EvalCurvStructNoCtx:50' otherwise
        // 'EvalCurvStructNoCtx:51' c_assert( false, 'Unknown Curve Type for Eval.\n' );
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i11{0}; i11 < 30; i11++) {
            message[i11] = cv[i11];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
    } break;
    }
    // 'EvalCurvStructNoCtx:54' r1D = a   .* r1D;
    h_loop_ub = r1D.size(1);
    for (int i12{0}; i12 < h_loop_ub; i12++) {
        int b_scalarLB;
        int b_vectorUB;
        int j_loop_ub;
        j_loop_ub = r1D.size(0);
        b_scalarLB = (r1D.size(0) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i15{0}; i15 <= b_vectorUB; i15 += 2) {
            __m128d r9;
            r9 = _mm_loadu_pd(&r1D[i15 + r1D.size(0) * i12]);
            _mm_storeu_pd(&r1D[i15 + r1D.size(0) * i12],
                          _mm_mul_pd(_mm_set1_pd(curv->a_param), r9));
        }
        for (int i15{b_scalarLB}; i15 < j_loop_ub; i15++) {
            r1D[i15 + r1D.size(0) * i12] = curv->a_param * r1D[i15 + r1D.size(0) * i12];
        }
    }
    // 'EvalCurvStructNoCtx:55' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    k_loop_ub = r2D.size(1);
    for (int i14{0}; i14 < k_loop_ub; i14++) {
        int c_scalarLB;
        int c_vectorUB;
        int n_loop_ub;
        n_loop_ub = r2D.size(0);
        c_scalarLB = (r2D.size(0) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (int i22{0}; i22 <= c_vectorUB; i22 += 2) {
            __m128d r10;
            r10 = _mm_loadu_pd(&r2D[i22 + r2D.size(0) * i14]);
            _mm_storeu_pd(&r2D[i22 + r2D.size(0) * i14], _mm_mul_pd(_mm_set1_pd(c), r10));
        }
        for (int i22{c_scalarLB}; i22 < n_loop_ub; i22++) {
            r2D[i22 + r2D.size(0) * i14] = c * r2D[i22 + r2D.size(0) * i14];
        }
    }
    // 'EvalCurvStructNoCtx:56' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    r_loop_ub = r3D.size(1);
    for (int i21{0}; i21 < r_loop_ub; i21++) {
        int d_scalarLB;
        int d_vectorUB;
        int v_loop_ub;
        v_loop_ub = r3D.size(0);
        d_scalarLB = (r3D.size(0) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (int i28{0}; i28 <= d_vectorUB; i28 += 2) {
            __m128d r11;
            r11 = _mm_loadu_pd(&r3D[i28 + r3D.size(0) * i21]);
            _mm_storeu_pd(&r3D[i28 + r3D.size(0) * i21], _mm_mul_pd(_mm_set1_pd(b_c), r11));
        }
        for (int i28{d_scalarLB}; i28 < v_loop_ub; i28++) {
            r3D[i28 + r3D.size(0) * i21] = b_c * r3D[i28 + r3D.size(0) * i21];
        }
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : const bool cfg_maskTot_data[]
//                const int cfg_maskTot_size[2]
//                const bool cfg_maskCart_data[]
//                const int cfg_maskCart_size[2]
//                const bool cfg_maskRot_data[]
//                const int cfg_maskRot_size[2]
//                const ::coder::array<int, 1U> &cfg_indCart
//                const ::coder::array<int, 1U> &cfg_indRot
//                int cfg_NumberAxis
//                int cfg_NCart
//                int cfg_NRot
//                const CurvStruct *curv
//                const CurvStruct *spline
//                double u_vec
//                ::coder::array<double, 1U> &r0D
// Return Type  : void
//
void b_EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                           const bool cfg_maskCart_data[], const int cfg_maskCart_size[2],
                           const bool cfg_maskRot_data[], const int cfg_maskRot_size[2],
                           const ::coder::array<int, 1U> &cfg_indCart,
                           const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                           int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                           const CurvStruct *spline, double u_vec, ::coder::array<double, 1U> &r0D)
{
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3D;
    double b_tmp_data[6];
    double r1D_data[6];
    double tmp_data[6];
    double d;
    double d1;
    double d2;
    double u_vec_tilda;
    int b_tmp_size;
    int r1D_size;
    int tmp_size;
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:6' if any( u_vec > 1.0 )
    if (u_vec > 1.0) {
        // 'EvalCurvStructNoCtx:7' u_vec( u_vec > 1.0 ) = 1.0;
        u_vec = 1.0;
        // 'EvalCurvStructNoCtx:7' printMsg( "Error : u_vec > 1\n" );
        //  printMsg : Print erro message according to the coder.target.
        // 'EvalCurvStructNoCtx:61' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:62' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:64' else
        // 'EvalCurvStructNoCtx:65' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec > 1\n");
        fflush(stdout);
    }
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    if (u_vec < 0.0) {
        // 'EvalCurvStructNoCtx:11' u_vec( u_vec < 0.0 ) = 0.0;
        u_vec = 0.0;
        // 'EvalCurvStructNoCtx:11' printMsg( "Error : u_vec < 0\n" );
        //  printMsg : Print erro message according to the coder.target.
        // 'EvalCurvStructNoCtx:61' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:62' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:64' else
        // 'EvalCurvStructNoCtx:65' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec < 0\n");
        fflush(stdout);
    }
    //
    // 'EvalCurvStructNoCtx:15' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:20' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:21' r1D = r0D;
    // 'EvalCurvStructNoCtx:21' r2D = r0D;
    // 'EvalCurvStructNoCtx:21' r3D = r0D;
    // 'EvalCurvStructNoCtx:23' a = curv.a_param;
    // 'EvalCurvStructNoCtx:24' b = curv.b_param;
    // 'EvalCurvStructNoCtx:26' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv->a_param * u_vec + curv->b_param;
    // 'EvalCurvStructNoCtx:28' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:29' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:30' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:31' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:32' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:34' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:35' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:36' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(6);
        b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), &(*(int(*)[1])r0D.size())[0], r1D_data, &r1D_size, r2D,
                   r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:37' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:38' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            double dv[3];
            double dv1[3];
            double dv2[3];
            double dv3[3];
            int c_tmp_data[3];
            int c_tmp_size;
            int loop_ub;
            int scalarLB;
            int vectorUB;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:39' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:40'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            loop_ub = cfg_indCart.size(0);
            scalarLB = (cfg_indCart.size(0) / 4) << 2;
            vectorUB = scalarLB - 4;
            for (int i3{0}; i3 <= vectorUB; i3 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i3],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i3]),
                                               _mm_set1_epi32(1)));
            }
            for (int i3{scalarLB}; i3 < loop_ub; i3++) {
                c_tmp_data[i3] = cfg_indCart[i3] - 1;
            }
            for (int i5{0}; i5 < c_tmp_size; i5++) {
                r0D[c_tmp_data[i5]] = dv[i5];
            }
        }
        // 'EvalCurvStructNoCtx:42' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            //  Rotative axis
            // 'EvalCurvStructNoCtx:43' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:44'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, &tmp_size, b_tmp_data, &b_tmp_size, r, r1);
            for (int i2{0}; i2 < tmp_size; i2++) {
                r0D[cfg_indRot[i2] - 1] = tmp_data[i2];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:46' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:47' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int i9;
        // 'EvalCurvStructNoCtx:48' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:49' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        b_loop_ub = spline->sp.coeff.size(0);
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            r0D[i4] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        c_loop_ub = spline->sp.coeff.size(0);
        for (int i6{0}; i6 < c_loop_ub; i6++) {
            r1D[i6] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        d_loop_ub = spline->sp.coeff.size(0);
        for (int i7{0}; i7 < d_loop_ub; i7++) {
            r2D[i7] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        e_loop_ub = spline->sp.coeff.size(0);
        for (int i8{0}; i8 < e_loop_ub; i8++) {
            r3D[i8] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i9 = spline->sp.coeff.size(0);
        for (int j{0}; j < i9; j++) {
            int f_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0D[j] = u_vec_tilda;
            f_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i10{0}; i10 < f_loop_ub; i10++) {
                b_spline[i10] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i10];
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
    default: {
        char message[30];
        // 'EvalCurvStructNoCtx:50' otherwise
        // 'EvalCurvStructNoCtx:51' c_assert( false, 'Unknown Curve Type for Eval.\n' );
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i1{0}; i1 < 30; i1++) {
            message[i1] = cv[i1];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
    } break;
    }
    // 'EvalCurvStructNoCtx:54' r1D = a   .* r1D;
    // 'EvalCurvStructNoCtx:55' r2D = a^2 .* r2D;
    // 'EvalCurvStructNoCtx:56' r3D = a^3 .* r3D;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : const bool cfg_maskTot_data[]
//                const int cfg_maskTot_size[2]
//                const bool cfg_maskCart_data[]
//                const int cfg_maskCart_size[2]
//                const bool cfg_maskRot_data[]
//                const int cfg_maskRot_size[2]
//                const ::coder::array<int, 1U> &cfg_indCart
//                const ::coder::array<int, 1U> &cfg_indRot
//                int cfg_NumberAxis
//                int cfg_NCart
//                int cfg_NRot
//                const CurvStruct *curv
//                const CurvStruct *spline
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void c_EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                           const bool cfg_maskCart_data[], const int cfg_maskCart_size[2],
                           const bool cfg_maskRot_data[], const int cfg_maskRot_size[2],
                           const ::coder::array<int, 1U> &cfg_indCart,
                           const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                           int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                           const CurvStruct *spline, ::coder::array<double, 1U> &r0D,
                           ::coder::array<double, 1U> &r1D, ::coder::array<double, 1U> &r2D,
                           ::coder::array<double, 1U> &r3D)
{
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    double b_tmp_data[6];
    double tmp_data[6];
    double b_c;
    double c;
    double d;
    double d1;
    double d2;
    double u_vec_tilda;
    int b_tmp_size;
    int c_scalarLB;
    int c_vectorUB;
    int d_loop_ub;
    int d_scalarLB;
    int d_vectorUB;
    int g_loop_ub;
    int loop_ub;
    int scalarLB;
    int tmp_size;
    int vectorUB;
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:6' if any( u_vec > 1.0 )
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    //
    // 'EvalCurvStructNoCtx:15' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:20' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:23' a = curv.a_param;
    // 'EvalCurvStructNoCtx:24' b = curv.b_param;
    // 'EvalCurvStructNoCtx:26' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv->a_param + curv->b_param;
    // 'EvalCurvStructNoCtx:28' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:29' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:30' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:31' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:32' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:34' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:35' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:36' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(6);
        r1D.reserve(6);
        b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), &(*(int(*)[1])r0D.size())[0], (double *)r1D.data(),
                   &(*(int(*)[1])r1D.size())[0], r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:37' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:38' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            double dv[3];
            double dv1[3];
            double dv2[3];
            double dv3[3];
            int c_tmp_data[3];
            int b_loop_ub;
            int b_scalarLB;
            int b_vectorUB;
            int c_tmp_size;
            int e_scalarLB;
            int e_vectorUB;
            int f_scalarLB;
            int f_vectorUB;
            int g_scalarLB;
            int g_vectorUB;
            int i_loop_ub;
            int l_loop_ub;
            int m_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:39' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:40'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            b_loop_ub = cfg_indCart.size(0);
            b_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            b_vectorUB = b_scalarLB - 4;
            for (int i6{0}; i6 <= b_vectorUB; i6 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i6],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i6]),
                                               _mm_set1_epi32(1)));
            }
            for (int i6{b_scalarLB}; i6 < b_loop_ub; i6++) {
                c_tmp_data[i6] = cfg_indCart[i6] - 1;
            }
            for (int i10{0}; i10 < c_tmp_size; i10++) {
                r0D[c_tmp_data[i10]] = dv[i10];
            }
            c_tmp_size = cfg_indCart.size(0);
            i_loop_ub = cfg_indCart.size(0);
            e_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            e_vectorUB = e_scalarLB - 4;
            for (int i13{0}; i13 <= e_vectorUB; i13 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i13],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i13]),
                                               _mm_set1_epi32(1)));
            }
            for (int i13{e_scalarLB}; i13 < i_loop_ub; i13++) {
                c_tmp_data[i13] = cfg_indCart[i13] - 1;
            }
            for (int i15{0}; i15 < c_tmp_size; i15++) {
                r1D[c_tmp_data[i15]] = dv1[i15];
            }
            c_tmp_size = cfg_indCart.size(0);
            l_loop_ub = cfg_indCart.size(0);
            f_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            f_vectorUB = f_scalarLB - 4;
            for (int i18{0}; i18 <= f_vectorUB; i18 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i18],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i18]),
                                               _mm_set1_epi32(1)));
            }
            for (int i18{f_scalarLB}; i18 < l_loop_ub; i18++) {
                c_tmp_data[i18] = cfg_indCart[i18] - 1;
            }
            for (int i19{0}; i19 < c_tmp_size; i19++) {
                r2D[c_tmp_data[i19]] = dv2[i19];
            }
            c_tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            g_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            g_vectorUB = g_scalarLB - 4;
            for (int i20{0}; i20 <= g_vectorUB; i20 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i20],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i20]),
                                               _mm_set1_epi32(1)));
            }
            for (int i20{g_scalarLB}; i20 < m_loop_ub; i20++) {
                c_tmp_data[i20] = cfg_indCart[i20] - 1;
            }
            for (int i22{0}; i22 < c_tmp_size; i22++) {
                r3D[c_tmp_data[i22]] = dv3[i22];
            }
        }
        // 'EvalCurvStructNoCtx:42' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int c_loop_ub;
            int e_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:43' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:44'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, &tmp_size, b_tmp_data, &b_tmp_size, r, r1);
            for (int i3{0}; i3 < tmp_size; i3++) {
                r0D[cfg_indRot[i3] - 1] = tmp_data[i3];
            }
            for (int i4{0}; i4 < b_tmp_size; i4++) {
                r1D[cfg_indRot[i4] - 1] = b_tmp_data[i4];
            }
            c_loop_ub = r.size(0);
            for (int i5{0}; i5 < c_loop_ub; i5++) {
                r2D[cfg_indRot[i5] - 1] = r[i5];
            }
            e_loop_ub = r1.size(0);
            for (int i8{0}; i8 < e_loop_ub; i8++) {
                r3D[cfg_indRot[i8] - 1] = r1[i8];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:46' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:47' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int f_loop_ub;
        int h_loop_ub;
        int i17;
        int j_loop_ub;
        int k_loop_ub;
        // 'EvalCurvStructNoCtx:48' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:49' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        f_loop_ub = spline->sp.coeff.size(0);
        for (int i9{0}; i9 < f_loop_ub; i9++) {
            r0D[i9] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        h_loop_ub = spline->sp.coeff.size(0);
        for (int i11{0}; i11 < h_loop_ub; i11++) {
            r1D[i11] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        j_loop_ub = spline->sp.coeff.size(0);
        for (int i14{0}; i14 < j_loop_ub; i14++) {
            r2D[i14] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        k_loop_ub = spline->sp.coeff.size(0);
        for (int i16{0}; i16 < k_loop_ub; i16++) {
            r3D[i16] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i17 = spline->sp.coeff.size(0);
        for (int j{0}; j < i17; j++) {
            int n_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0D[j] = u_vec_tilda;
            n_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i21{0}; i21 < n_loop_ub; i21++) {
                b_spline[i21] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i21];
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
    default: {
        char message[30];
        // 'EvalCurvStructNoCtx:50' otherwise
        // 'EvalCurvStructNoCtx:51' c_assert( false, 'Unknown Curve Type for Eval.\n' );
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i1{0}; i1 < 30; i1++) {
            message[i1] = cv[i1];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
    } break;
    }
    // 'EvalCurvStructNoCtx:54' r1D = a   .* r1D;
    loop_ub = r1D.size(0);
    scalarLB = (r1D.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i2{0}; i2 <= vectorUB; i2 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r1D[i2]);
        _mm_storeu_pd(&r1D[i2], _mm_mul_pd(_mm_set1_pd(curv->a_param), r2));
    }
    for (int i2{scalarLB}; i2 < loop_ub; i2++) {
        r1D[i2] = curv->a_param * r1D[i2];
    }
    // 'EvalCurvStructNoCtx:55' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    d_loop_ub = r2D.size(0);
    c_scalarLB = (r2D.size(0) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (int i7{0}; i7 <= c_vectorUB; i7 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&r2D[i7]);
        _mm_storeu_pd(&r2D[i7], _mm_mul_pd(_mm_set1_pd(c), r3));
    }
    for (int i7{c_scalarLB}; i7 < d_loop_ub; i7++) {
        r2D[i7] = c * r2D[i7];
    }
    // 'EvalCurvStructNoCtx:56' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    g_loop_ub = r3D.size(0);
    d_scalarLB = (r3D.size(0) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i12{0}; i12 <= d_vectorUB; i12 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r3D[i12]);
        _mm_storeu_pd(&r3D[i12], _mm_mul_pd(_mm_set1_pd(b_c), r4));
    }
    for (int i12{d_scalarLB}; i12 < g_loop_ub; i12++) {
        r3D[i12] = b_c * r3D[i12];
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : const bool cfg_maskTot_data[]
//                const int cfg_maskTot_size[2]
//                const bool cfg_maskCart_data[]
//                const int cfg_maskCart_size[2]
//                const bool cfg_maskRot_data[]
//                const int cfg_maskRot_size[2]
//                const ::coder::array<int, 1U> &cfg_indCart
//                const ::coder::array<int, 1U> &cfg_indRot
//                int cfg_NumberAxis
//                int cfg_NCart
//                int cfg_NRot
//                const CurvStruct *curv
//                const CurvStruct *spline
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void d_EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                           const bool cfg_maskCart_data[], const int cfg_maskCart_size[2],
                           const bool cfg_maskRot_data[], const int cfg_maskRot_size[2],
                           const ::coder::array<int, 1U> &cfg_indCart,
                           const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                           int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                           const CurvStruct *spline, ::coder::array<double, 1U> &r0D,
                           ::coder::array<double, 1U> &r1D, ::coder::array<double, 1U> &r2D,
                           ::coder::array<double, 1U> &r3D)
{
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    double b_tmp_data[6];
    double tmp_data[6];
    double b_c;
    double c;
    double d;
    double d1;
    double d2;
    int b_tmp_size;
    int c_scalarLB;
    int c_vectorUB;
    int d_loop_ub;
    int d_scalarLB;
    int d_vectorUB;
    int g_loop_ub;
    int loop_ub;
    int scalarLB;
    int tmp_size;
    int vectorUB;
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:6' if any( u_vec > 1.0 )
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    //
    // 'EvalCurvStructNoCtx:15' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:20' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:23' a = curv.a_param;
    // 'EvalCurvStructNoCtx:24' b = curv.b_param;
    // 'EvalCurvStructNoCtx:26' u_vec_tilda = a * u_vec + b;
    // 'EvalCurvStructNoCtx:28' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:29' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:30' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:31' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:32' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:34' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:35' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:36' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(6);
        r1D.reserve(6);
        b_EvalLine(curv->R0, curv->R1, curv->b_param, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), &(*(int(*)[1])r0D.size())[0], (double *)r1D.data(),
                   &(*(int(*)[1])r1D.size())[0], r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:37' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:38' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            double dv[3];
            double dv1[3];
            double dv2[3];
            double dv3[3];
            int c_tmp_data[3];
            int b_loop_ub;
            int b_scalarLB;
            int b_vectorUB;
            int c_tmp_size;
            int e_scalarLB;
            int e_vectorUB;
            int f_scalarLB;
            int f_vectorUB;
            int g_scalarLB;
            int g_vectorUB;
            int i_loop_ub;
            int l_loop_ub;
            int m_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:39' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:40'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        curv->b_param, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            b_loop_ub = cfg_indCart.size(0);
            b_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            b_vectorUB = b_scalarLB - 4;
            for (int i6{0}; i6 <= b_vectorUB; i6 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i6],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i6]),
                                               _mm_set1_epi32(1)));
            }
            for (int i6{b_scalarLB}; i6 < b_loop_ub; i6++) {
                c_tmp_data[i6] = cfg_indCart[i6] - 1;
            }
            for (int i10{0}; i10 < c_tmp_size; i10++) {
                r0D[c_tmp_data[i10]] = dv[i10];
            }
            c_tmp_size = cfg_indCart.size(0);
            i_loop_ub = cfg_indCart.size(0);
            e_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            e_vectorUB = e_scalarLB - 4;
            for (int i13{0}; i13 <= e_vectorUB; i13 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i13],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i13]),
                                               _mm_set1_epi32(1)));
            }
            for (int i13{e_scalarLB}; i13 < i_loop_ub; i13++) {
                c_tmp_data[i13] = cfg_indCart[i13] - 1;
            }
            for (int i15{0}; i15 < c_tmp_size; i15++) {
                r1D[c_tmp_data[i15]] = dv1[i15];
            }
            c_tmp_size = cfg_indCart.size(0);
            l_loop_ub = cfg_indCart.size(0);
            f_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            f_vectorUB = f_scalarLB - 4;
            for (int i18{0}; i18 <= f_vectorUB; i18 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i18],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i18]),
                                               _mm_set1_epi32(1)));
            }
            for (int i18{f_scalarLB}; i18 < l_loop_ub; i18++) {
                c_tmp_data[i18] = cfg_indCart[i18] - 1;
            }
            for (int i19{0}; i19 < c_tmp_size; i19++) {
                r2D[c_tmp_data[i19]] = dv2[i19];
            }
            c_tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            g_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            g_vectorUB = g_scalarLB - 4;
            for (int i20{0}; i20 <= g_vectorUB; i20 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i20],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i20]),
                                               _mm_set1_epi32(1)));
            }
            for (int i20{g_scalarLB}; i20 < m_loop_ub; i20++) {
                c_tmp_data[i20] = cfg_indCart[i20] - 1;
            }
            for (int i22{0}; i22 < c_tmp_size; i22++) {
                r3D[c_tmp_data[i22]] = dv3[i22];
            }
        }
        // 'EvalCurvStructNoCtx:42' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int c_loop_ub;
            int e_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:43' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:44'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, curv->b_param, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, &tmp_size, b_tmp_data, &b_tmp_size, r, r1);
            for (int i3{0}; i3 < tmp_size; i3++) {
                r0D[cfg_indRot[i3] - 1] = tmp_data[i3];
            }
            for (int i4{0}; i4 < b_tmp_size; i4++) {
                r1D[cfg_indRot[i4] - 1] = b_tmp_data[i4];
            }
            c_loop_ub = r.size(0);
            for (int i5{0}; i5 < c_loop_ub; i5++) {
                r2D[cfg_indRot[i5] - 1] = r[i5];
            }
            e_loop_ub = r1.size(0);
            for (int i8{0}; i8 < e_loop_ub; i8++) {
                r3D[cfg_indRot[i8] - 1] = r1[i8];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:46' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:47' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, curv->b_param, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int f_loop_ub;
        int h_loop_ub;
        int i17;
        int j_loop_ub;
        int k_loop_ub;
        // 'EvalCurvStructNoCtx:48' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:49' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        f_loop_ub = spline->sp.coeff.size(0);
        for (int i9{0}; i9 < f_loop_ub; i9++) {
            r0D[i9] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        h_loop_ub = spline->sp.coeff.size(0);
        for (int i11{0}; i11 < h_loop_ub; i11++) {
            r1D[i11] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        j_loop_ub = spline->sp.coeff.size(0);
        for (int i14{0}; i14 < j_loop_ub; i14++) {
            r2D[i14] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        k_loop_ub = spline->sp.coeff.size(0);
        for (int i16{0}; i16 < k_loop_ub; i16++) {
            r3D[i16] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i17 = spline->sp.coeff.size(0);
        for (int j{0}; j < i17; j++) {
            int n_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0D[j] = curv->b_param;
            n_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i21{0}; i21 < n_loop_ub; i21++) {
                b_spline[i21] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i21];
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
    default: {
        char message[30];
        // 'EvalCurvStructNoCtx:50' otherwise
        // 'EvalCurvStructNoCtx:51' c_assert( false, 'Unknown Curve Type for Eval.\n' );
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i1{0}; i1 < 30; i1++) {
            message[i1] = cv[i1];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
    } break;
    }
    // 'EvalCurvStructNoCtx:54' r1D = a   .* r1D;
    loop_ub = r1D.size(0);
    scalarLB = (r1D.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i2{0}; i2 <= vectorUB; i2 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r1D[i2]);
        _mm_storeu_pd(&r1D[i2], _mm_mul_pd(_mm_set1_pd(curv->a_param), r2));
    }
    for (int i2{scalarLB}; i2 < loop_ub; i2++) {
        r1D[i2] = curv->a_param * r1D[i2];
    }
    // 'EvalCurvStructNoCtx:55' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    d_loop_ub = r2D.size(0);
    c_scalarLB = (r2D.size(0) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (int i7{0}; i7 <= c_vectorUB; i7 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&r2D[i7]);
        _mm_storeu_pd(&r2D[i7], _mm_mul_pd(_mm_set1_pd(c), r3));
    }
    for (int i7{c_scalarLB}; i7 < d_loop_ub; i7++) {
        r2D[i7] = c * r2D[i7];
    }
    // 'EvalCurvStructNoCtx:56' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    g_loop_ub = r3D.size(0);
    d_scalarLB = (r3D.size(0) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i12{0}; i12 <= d_vectorUB; i12 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r3D[i12]);
        _mm_storeu_pd(&r3D[i12], _mm_mul_pd(_mm_set1_pd(b_c), r4));
    }
    for (int i12{d_scalarLB}; i12 < g_loop_ub; i12++) {
        r3D[i12] = b_c * r3D[i12];
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : const bool cfg_maskTot_data[]
//                const int cfg_maskTot_size[2]
//                const bool cfg_maskCart_data[]
//                const int cfg_maskCart_size[2]
//                const bool cfg_maskRot_data[]
//                const int cfg_maskRot_size[2]
//                const ::coder::array<int, 1U> &cfg_indCart
//                const ::coder::array<int, 1U> &cfg_indRot
//                int cfg_NumberAxis
//                int cfg_NCart
//                int cfg_NRot
//                const CurvStruct *curv
//                const CurvStruct *spline
//                double u_vec
//                ::coder::array<double, 1U> &r0D
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void e_EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                           const bool cfg_maskCart_data[], const int cfg_maskCart_size[2],
                           const bool cfg_maskRot_data[], const int cfg_maskRot_size[2],
                           const ::coder::array<int, 1U> &cfg_indCart,
                           const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                           int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                           const CurvStruct *spline, double u_vec, ::coder::array<double, 1U> &r0D,
                           ::coder::array<double, 1U> &r1D, ::coder::array<double, 1U> &r2D,
                           ::coder::array<double, 1U> &r3D)
{
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    double b_tmp_data[6];
    double tmp_data[6];
    double b_c;
    double c;
    double d;
    double d1;
    double d2;
    double u_vec_tilda;
    int b_tmp_size;
    int c_scalarLB;
    int c_vectorUB;
    int d_loop_ub;
    int d_scalarLB;
    int d_vectorUB;
    int g_loop_ub;
    int loop_ub;
    int scalarLB;
    int tmp_size;
    int vectorUB;
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:6' if any( u_vec > 1.0 )
    if (u_vec > 1.0) {
        // 'EvalCurvStructNoCtx:7' u_vec( u_vec > 1.0 ) = 1.0;
        u_vec = 1.0;
        // 'EvalCurvStructNoCtx:7' printMsg( "Error : u_vec > 1\n" );
        //  printMsg : Print erro message according to the coder.target.
        // 'EvalCurvStructNoCtx:61' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:62' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:64' else
        // 'EvalCurvStructNoCtx:65' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec > 1\n");
        fflush(stdout);
    }
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    if (u_vec < 0.0) {
        // 'EvalCurvStructNoCtx:11' u_vec( u_vec < 0.0 ) = 0.0;
        u_vec = 0.0;
        // 'EvalCurvStructNoCtx:11' printMsg( "Error : u_vec < 0\n" );
        //  printMsg : Print erro message according to the coder.target.
        // 'EvalCurvStructNoCtx:61' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:62' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:64' else
        // 'EvalCurvStructNoCtx:65' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec < 0\n");
        fflush(stdout);
    }
    //
    // 'EvalCurvStructNoCtx:15' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:20' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:23' a = curv.a_param;
    // 'EvalCurvStructNoCtx:24' b = curv.b_param;
    // 'EvalCurvStructNoCtx:26' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv->a_param * u_vec + curv->b_param;
    // 'EvalCurvStructNoCtx:28' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:29' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:30' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:31' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:32' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:34' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:35' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:36' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(6);
        r1D.reserve(6);
        b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), &(*(int(*)[1])r0D.size())[0], (double *)r1D.data(),
                   &(*(int(*)[1])r1D.size())[0], r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:37' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:38' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            double dv[3];
            double dv1[3];
            double dv2[3];
            double dv3[3];
            int c_tmp_data[3];
            int b_loop_ub;
            int b_scalarLB;
            int b_vectorUB;
            int c_tmp_size;
            int e_scalarLB;
            int e_vectorUB;
            int f_scalarLB;
            int f_vectorUB;
            int g_scalarLB;
            int g_vectorUB;
            int i_loop_ub;
            int l_loop_ub;
            int m_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:39' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:40'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            b_loop_ub = cfg_indCart.size(0);
            b_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            b_vectorUB = b_scalarLB - 4;
            for (int i6{0}; i6 <= b_vectorUB; i6 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i6],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i6]),
                                               _mm_set1_epi32(1)));
            }
            for (int i6{b_scalarLB}; i6 < b_loop_ub; i6++) {
                c_tmp_data[i6] = cfg_indCart[i6] - 1;
            }
            for (int i10{0}; i10 < c_tmp_size; i10++) {
                r0D[c_tmp_data[i10]] = dv[i10];
            }
            c_tmp_size = cfg_indCart.size(0);
            i_loop_ub = cfg_indCart.size(0);
            e_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            e_vectorUB = e_scalarLB - 4;
            for (int i13{0}; i13 <= e_vectorUB; i13 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i13],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i13]),
                                               _mm_set1_epi32(1)));
            }
            for (int i13{e_scalarLB}; i13 < i_loop_ub; i13++) {
                c_tmp_data[i13] = cfg_indCart[i13] - 1;
            }
            for (int i15{0}; i15 < c_tmp_size; i15++) {
                r1D[c_tmp_data[i15]] = dv1[i15];
            }
            c_tmp_size = cfg_indCart.size(0);
            l_loop_ub = cfg_indCart.size(0);
            f_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            f_vectorUB = f_scalarLB - 4;
            for (int i18{0}; i18 <= f_vectorUB; i18 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i18],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i18]),
                                               _mm_set1_epi32(1)));
            }
            for (int i18{f_scalarLB}; i18 < l_loop_ub; i18++) {
                c_tmp_data[i18] = cfg_indCart[i18] - 1;
            }
            for (int i19{0}; i19 < c_tmp_size; i19++) {
                r2D[c_tmp_data[i19]] = dv2[i19];
            }
            c_tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            g_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            g_vectorUB = g_scalarLB - 4;
            for (int i20{0}; i20 <= g_vectorUB; i20 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i20],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i20]),
                                               _mm_set1_epi32(1)));
            }
            for (int i20{g_scalarLB}; i20 < m_loop_ub; i20++) {
                c_tmp_data[i20] = cfg_indCart[i20] - 1;
            }
            for (int i22{0}; i22 < c_tmp_size; i22++) {
                r3D[c_tmp_data[i22]] = dv3[i22];
            }
        }
        // 'EvalCurvStructNoCtx:42' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int c_loop_ub;
            int e_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:43' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:44'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, &tmp_size, b_tmp_data, &b_tmp_size, r, r1);
            for (int i3{0}; i3 < tmp_size; i3++) {
                r0D[cfg_indRot[i3] - 1] = tmp_data[i3];
            }
            for (int i4{0}; i4 < b_tmp_size; i4++) {
                r1D[cfg_indRot[i4] - 1] = b_tmp_data[i4];
            }
            c_loop_ub = r.size(0);
            for (int i5{0}; i5 < c_loop_ub; i5++) {
                r2D[cfg_indRot[i5] - 1] = r[i5];
            }
            e_loop_ub = r1.size(0);
            for (int i8{0}; i8 < e_loop_ub; i8++) {
                r3D[cfg_indRot[i8] - 1] = r1[i8];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:46' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:47' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int f_loop_ub;
        int h_loop_ub;
        int i17;
        int j_loop_ub;
        int k_loop_ub;
        // 'EvalCurvStructNoCtx:48' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:49' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        f_loop_ub = spline->sp.coeff.size(0);
        for (int i9{0}; i9 < f_loop_ub; i9++) {
            r0D[i9] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        h_loop_ub = spline->sp.coeff.size(0);
        for (int i11{0}; i11 < h_loop_ub; i11++) {
            r1D[i11] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        j_loop_ub = spline->sp.coeff.size(0);
        for (int i14{0}; i14 < j_loop_ub; i14++) {
            r2D[i14] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        k_loop_ub = spline->sp.coeff.size(0);
        for (int i16{0}; i16 < k_loop_ub; i16++) {
            r3D[i16] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i17 = spline->sp.coeff.size(0);
        for (int j{0}; j < i17; j++) {
            int n_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0D[j] = u_vec_tilda;
            n_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i21{0}; i21 < n_loop_ub; i21++) {
                b_spline[i21] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i21];
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
    default: {
        char message[30];
        // 'EvalCurvStructNoCtx:50' otherwise
        // 'EvalCurvStructNoCtx:51' c_assert( false, 'Unknown Curve Type for Eval.\n' );
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i1{0}; i1 < 30; i1++) {
            message[i1] = cv[i1];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
    } break;
    }
    // 'EvalCurvStructNoCtx:54' r1D = a   .* r1D;
    loop_ub = r1D.size(0);
    scalarLB = (r1D.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i2{0}; i2 <= vectorUB; i2 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r1D[i2]);
        _mm_storeu_pd(&r1D[i2], _mm_mul_pd(_mm_set1_pd(curv->a_param), r2));
    }
    for (int i2{scalarLB}; i2 < loop_ub; i2++) {
        r1D[i2] = curv->a_param * r1D[i2];
    }
    // 'EvalCurvStructNoCtx:55' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    d_loop_ub = r2D.size(0);
    c_scalarLB = (r2D.size(0) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (int i7{0}; i7 <= c_vectorUB; i7 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&r2D[i7]);
        _mm_storeu_pd(&r2D[i7], _mm_mul_pd(_mm_set1_pd(c), r3));
    }
    for (int i7{c_scalarLB}; i7 < d_loop_ub; i7++) {
        r2D[i7] = c * r2D[i7];
    }
    // 'EvalCurvStructNoCtx:56' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    g_loop_ub = r3D.size(0);
    d_scalarLB = (r3D.size(0) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i12{0}; i12 <= d_vectorUB; i12 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r3D[i12]);
        _mm_storeu_pd(&r3D[i12], _mm_mul_pd(_mm_set1_pd(b_c), r4));
    }
    for (int i12{d_scalarLB}; i12 < g_loop_ub; i12++) {
        r3D[i12] = b_c * r3D[i12];
    }
}

} // namespace ocn

//
// File trailer for EvalCurvStructNoCtx.cpp
//
// [EOF]
//
