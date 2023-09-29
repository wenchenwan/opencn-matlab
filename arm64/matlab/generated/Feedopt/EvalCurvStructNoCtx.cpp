
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStructNoCtx.cpp
//
// MATLAB Coder version            : 5.4
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
//                const ::coder::array<double, 1U> &u_vec
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
                         const CurvStruct *spline, const ::coder::array<double, 1U> &u_vec,
                         ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D,
                         ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 1U> b_r0D;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r4;
    ::coder::array<double, 1U> r5;
    ::coder::array<double, 1U> r6;
    ::coder::array<double, 1U> u_vec_tilda;
    double b_c;
    double c;
    double d;
    double d1;
    double d2;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int h_loop_ub;
    int k_loop_ub;
    int loop_ub;
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:7' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    // 'EvalCurvStructNoCtx:8' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    //
    // 'EvalCurvStructNoCtx:11' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:13' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:14' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:16' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis, u_vec.size(0));
    loop_ub = u_vec.size(0);
    for (int i{0}; i < loop_ub; i++) {
        for (int i1{0}; i1 < cfg_NumberAxis; i1++) {
            r0D[i1 + r0D.size(0) * i] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:17' r1D = r0D;
    r1D.set_size(cfg_NumberAxis, u_vec.size(0));
    b_loop_ub = u_vec.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        for (int i3{0}; i3 < cfg_NumberAxis; i3++) {
            r1D[i3 + r1D.size(0) * i2] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:17' r2D = r0D;
    r2D.set_size(cfg_NumberAxis, u_vec.size(0));
    c_loop_ub = u_vec.size(0);
    for (int i4{0}; i4 < c_loop_ub; i4++) {
        for (int i5{0}; i5 < cfg_NumberAxis; i5++) {
            r2D[i5 + r2D.size(0) * i4] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:17' r3D = r0D;
    r3D.set_size(cfg_NumberAxis, u_vec.size(0));
    d_loop_ub = u_vec.size(0);
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        for (int i7{0}; i7 < cfg_NumberAxis; i7++) {
            r3D[i7 + r3D.size(0) * i6] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:19' a = curv.a_param;
    // 'EvalCurvStructNoCtx:20' b = curv.b_param;
    // 'EvalCurvStructNoCtx:22' u_vec_tilda = a * u_vec + b;
    u_vec_tilda.set_size(u_vec.size(0));
    e_loop_ub = u_vec.size(0);
    for (int i8{0}; i8 < e_loop_ub; i8++) {
        u_vec_tilda[i8] = curv->a_param * u_vec[i8] + curv->b_param;
    }
    // 'EvalCurvStructNoCtx:24' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:25' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:26' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:27' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:28' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:30' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line: {
        int r0D_idx_0;
        // 'EvalCurvStructNoCtx:31' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:32' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size, b_r0D, r1D,
                 r2D, r3D);
        r0D_idx_0 = b_r0D.size(0);
        r0D.set_size(b_r0D.size(0), 1);
        for (int i10{0}; i10 < r0D_idx_0; i10++) {
            r0D[i10] = b_r0D[i10];
        }
    } break;
    case CurveType_Helix: {
        int tmp_data[3];
        int tmp_size;
        // 'EvalCurvStructNoCtx:33' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:34' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            double dv[3];
            double dv1[3];
            double dv2[3];
            double dv3[3];
            int ab_loop_ub;
            int cb_loop_ub;
            int db_loop_ub;
            int eb_loop_ub;
            int l_loop_ub;
            int o_loop_ub;
            int t_loop_ub;
            int w_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:35' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:36'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                      u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            tmp_size = cfg_indCart.size(0);
            l_loop_ub = cfg_indCart.size(0);
            for (int i16{0}; i16 < l_loop_ub; i16++) {
                tmp_data[i16] = cfg_indCart[i16] - 1;
            }
            o_loop_ub = u_vec.size(0);
            for (int i19{0}; i19 < o_loop_ub; i19++) {
                for (int i22{0}; i22 < tmp_size; i22++) {
                    r0D[tmp_data[i22] + r0D.size(0) * i19] = dv[i22 + tmp_size * i19];
                }
            }
            tmp_size = cfg_indCart.size(0);
            t_loop_ub = cfg_indCart.size(0);
            for (int i26{0}; i26 < t_loop_ub; i26++) {
                tmp_data[i26] = cfg_indCart[i26] - 1;
            }
            w_loop_ub = u_vec.size(0);
            for (int i30{0}; i30 < w_loop_ub; i30++) {
                for (int i32{0}; i32 < tmp_size; i32++) {
                    r1D[tmp_data[i32] + r1D.size(0) * i30] = dv1[i32 + tmp_size * i30];
                }
            }
            tmp_size = cfg_indCart.size(0);
            ab_loop_ub = cfg_indCart.size(0);
            for (int i35{0}; i35 < ab_loop_ub; i35++) {
                tmp_data[i35] = cfg_indCart[i35] - 1;
            }
            cb_loop_ub = u_vec.size(0);
            for (int i37{0}; i37 < cb_loop_ub; i37++) {
                for (int i40{0}; i40 < tmp_size; i40++) {
                    r2D[tmp_data[i40] + r2D.size(0) * i37] = dv2[i40 + tmp_size * i37];
                }
            }
            tmp_size = cfg_indCart.size(0);
            db_loop_ub = cfg_indCart.size(0);
            for (int i41{0}; i41 < db_loop_ub; i41++) {
                tmp_data[i41] = cfg_indCart[i41] - 1;
            }
            eb_loop_ub = u_vec.size(0);
            for (int i42{0}; i42 < eb_loop_ub; i42++) {
                for (int i43{0}; i43 < tmp_size; i43++) {
                    r3D[tmp_data[i43] + r3D.size(0) * i42] = dv3[i43 + tmp_size * i42];
                }
            }
        }
        // 'EvalCurvStructNoCtx:38' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int j_loop_ub;
            int m_loop_ub;
            int p_loop_ub;
            int r_loop_ub;
            int u_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:39' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:40'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size, r, r1, r2,
                     r3);
            tmp_size = cfg_indRot.size(0);
            j_loop_ub = cfg_indRot.size(0);
            for (int i14{0}; i14 < j_loop_ub; i14++) {
                tmp_data[i14] = cfg_indRot[i14] - 1;
            }
            m_loop_ub = r0D.size(1);
            for (int i17{0}; i17 < m_loop_ub; i17++) {
                for (int i20{0}; i20 < tmp_size; i20++) {
                    r0D[tmp_data[i20] + r0D.size(0) * i17] = r[i20 + tmp_size * i17];
                }
            }
            p_loop_ub = r1.size(1);
            for (int i21{0}; i21 < p_loop_ub; i21++) {
                int s_loop_ub;
                s_loop_ub = r1.size(0);
                for (int i25{0}; i25 < s_loop_ub; i25++) {
                    r1D[(cfg_indRot[i25] + r1D.size(0) * i21) - 1] = r1[i25 + r1.size(0) * i21];
                }
            }
            r_loop_ub = r2.size(1);
            for (int i24{0}; i24 < r_loop_ub; i24++) {
                int v_loop_ub;
                v_loop_ub = r2.size(0);
                for (int i29{0}; i29 < v_loop_ub; i29++) {
                    r2D[(cfg_indRot[i29] + r2D.size(0) * i24) - 1] = r2[i29 + r2.size(0) * i24];
                }
            }
            u_loop_ub = r3.size(1);
            for (int i28{0}; i28 < u_loop_ub; i28++) {
                int y_loop_ub;
                y_loop_ub = r3.size(0);
                for (int i33{0}; i33 < y_loop_ub; i33++) {
                    r3D[(cfg_indRot[i33] + r3D.size(0) * i28) - 1] = r3[i33 + r3.size(0) * i28];
                }
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:42' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:43' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int bb_loop_ub;
        int i39;
        int q_loop_ub;
        int unnamed_idx_0;
        int x_loop_ub;
        // 'EvalCurvStructNoCtx:44' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:45' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        r1D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(0));
        q_loop_ub = u_vec_tilda.size(0);
        for (int i23{0}; i23 < q_loop_ub; i23++) {
            for (int i27{0}; i27 < unnamed_idx_0; i27++) {
                r1D[i27 + r1D.size(0) * i23] = 0.0;
            }
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(0));
        x_loop_ub = u_vec_tilda.size(0);
        for (int i31{0}; i31 < x_loop_ub; i31++) {
            for (int i34{0}; i34 < unnamed_idx_0; i34++) {
                r2D[i34 + r2D.size(0) * i31] = 0.0;
            }
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(0));
        bb_loop_ub = u_vec_tilda.size(0);
        for (int i36{0}; i36 < bb_loop_ub; i36++) {
            for (int i38{0}; i38 < unnamed_idx_0; i38++) {
                r3D[i38 + r3D.size(0) * i36] = 0.0;
            }
        }
        // 'EvalBSpline:20' for j = 1 : M
        i39 = spline->sp.coeff.size(0);
        r0D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(0));
        for (int j{0}; j < i39; j++) {
            int fb_loop_ub;
            int gb_loop_ub;
            int hb_loop_ub;
            int i48;
            int ib_loop_ub;
            int jb_loop_ub;
            int lb_loop_ub;
            int mb_loop_ub;
            int nb_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
            r.set_size(u_vec_tilda.size(0));
            fb_loop_ub = u_vec_tilda.size(0);
            for (int i44{0}; i44 < fb_loop_ub; i44++) {
                r[i44] = 0.0;
            }
            // 'bspline_eval_vec:4' xd      = zeros(size(u));
            r4.set_size(u_vec_tilda.size(0));
            gb_loop_ub = u_vec_tilda.size(0);
            for (int i45{0}; i45 < gb_loop_ub; i45++) {
                r4[i45] = 0.0;
            }
            // 'bspline_eval_vec:5' xdd     = zeros(size(u));
            r5.set_size(u_vec_tilda.size(0));
            hb_loop_ub = u_vec_tilda.size(0);
            for (int i46{0}; i46 < hb_loop_ub; i46++) {
                r5[i46] = 0.0;
            }
            // 'bspline_eval_vec:6' xddd    = zeros(size(u));
            r6.set_size(u_vec_tilda.size(0));
            ib_loop_ub = u_vec_tilda.size(0);
            for (int i47{0}; i47 < ib_loop_ub; i47++) {
                r6[i47] = 0.0;
            }
            // 'bspline_eval_vec:8' for k = 1:length(u)
            i48 = u_vec_tilda.size(0);
            for (int k{0}; k < i48; k++) {
                int kb_loop_ub;
                // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
                r[k] = u_vec_tilda[k];
                kb_loop_ub = spline->sp.coeff.size(1);
                b_spline.set_size(1, spline->sp.coeff.size(1));
                for (int i51{0}; i51 < kb_loop_ub; i51++) {
                    b_spline[i51] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i51];
                }
                bspline_eval(spline->sp.Bl.handle, b_spline, &r[k], &d, &d1, &d2);
                r6[k] = d2;
                r5[k] = d1;
                r4[k] = d;
                // 'bspline_eval_vec:10' x(k)    = xk;
                // 'bspline_eval_vec:11' xd(k)   = xdk;
                // 'bspline_eval_vec:12' xdd(k)  = xddk;
                // 'bspline_eval_vec:13' xddd(k) = xdddk;
            }
            jb_loop_ub = r0D.size(1);
            for (int i49{0}; i49 < jb_loop_ub; i49++) {
                r0D[j + r0D.size(0) * i49] = r[i49];
            }
            lb_loop_ub = r1D.size(1);
            for (int i50{0}; i50 < lb_loop_ub; i50++) {
                r1D[j + r1D.size(0) * i50] = r4[i50];
            }
            mb_loop_ub = r2D.size(1);
            for (int i52{0}; i52 < mb_loop_ub; i52++) {
                r2D[j + r2D.size(0) * i52] = r5[i52];
            }
            nb_loop_ub = r3D.size(1);
            for (int i53{0}; i53 < nb_loop_ub; i53++) {
                r3D[j + r3D.size(0) * i53] = r6[i53];
            }
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:46' otherwise
        // 'EvalCurvStructNoCtx:47' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        break;
    }
    // 'EvalCurvStructNoCtx:50' r1D = a   .* r1D;
    f_loop_ub = r1D.size(1);
    for (int i9{0}; i9 < f_loop_ub; i9++) {
        int g_loop_ub;
        g_loop_ub = r1D.size(0);
        for (int i11{0}; i11 < g_loop_ub; i11++) {
            r1D[i11 + r1D.size(0) * i9] = curv->a_param * r1D[i11 + r1D.size(0) * i9];
        }
    }
    // 'EvalCurvStructNoCtx:51' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    h_loop_ub = r2D.size(1);
    for (int i12{0}; i12 < h_loop_ub; i12++) {
        int i_loop_ub;
        i_loop_ub = r2D.size(0);
        for (int i13{0}; i13 < i_loop_ub; i13++) {
            r2D[i13 + r2D.size(0) * i12] = c * r2D[i13 + r2D.size(0) * i12];
        }
    }
    // 'EvalCurvStructNoCtx:52' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    k_loop_ub = r3D.size(1);
    for (int i15{0}; i15 < k_loop_ub; i15++) {
        int n_loop_ub;
        n_loop_ub = r3D.size(0);
        for (int i18{0}; i18 < n_loop_ub; i18++) {
            r3D[i18 + r3D.size(0) * i15] = b_c * r3D[i18 + r3D.size(0) * i15];
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
    // 'EvalCurvStructNoCtx:7' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    // 'EvalCurvStructNoCtx:8' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    //
    // 'EvalCurvStructNoCtx:11' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:13' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:14' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:16' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:17' r1D = r0D;
    // 'EvalCurvStructNoCtx:17' r2D = r0D;
    // 'EvalCurvStructNoCtx:17' r3D = r0D;
    // 'EvalCurvStructNoCtx:19' a = curv.a_param;
    // 'EvalCurvStructNoCtx:20' b = curv.b_param;
    // 'EvalCurvStructNoCtx:22' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv->a_param * u_vec + curv->b_param;
    // 'EvalCurvStructNoCtx:24' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:25' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:26' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:27' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:28' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:30' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:31' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:32' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(6);
        b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), &(*(int(*)[1])r0D.size())[0], r1D_data, &r1D_size, r2D,
                   r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:33' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:34' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            double dv[3];
            double dv1[3];
            double dv2[3];
            double dv3[3];
            int c_tmp_data[3];
            int c_tmp_size;
            int loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:35' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:36'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            loop_ub = cfg_indCart.size(0);
            for (int i2{0}; i2 < loop_ub; i2++) {
                c_tmp_data[i2] = cfg_indCart[i2] - 1;
            }
            for (int i3{0}; i3 < c_tmp_size; i3++) {
                r0D[c_tmp_data[i3]] = dv[i3];
            }
        }
        // 'EvalCurvStructNoCtx:38' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            //  Rotative axis
            // 'EvalCurvStructNoCtx:39' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:40'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, &tmp_size, b_tmp_data, &b_tmp_size, r, r1);
            for (int i1{0}; i1 < tmp_size; i1++) {
                r0D[cfg_indRot[i1] - 1] = tmp_data[i1];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:42' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:43' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int i8;
        // 'EvalCurvStructNoCtx:44' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:45' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        for (int i5{0}; i5 < c_loop_ub; i5++) {
            r1D[i5] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        d_loop_ub = spline->sp.coeff.size(0);
        for (int i6{0}; i6 < d_loop_ub; i6++) {
            r2D[i6] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        e_loop_ub = spline->sp.coeff.size(0);
        for (int i7{0}; i7 < e_loop_ub; i7++) {
            r3D[i7] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i8 = spline->sp.coeff.size(0);
        for (int j{0}; j < i8; j++) {
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
            for (int i9{0}; i9 < f_loop_ub; i9++) {
                b_spline[i9] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i9];
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
        // 'EvalCurvStructNoCtx:46' otherwise
        // 'EvalCurvStructNoCtx:47' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        break;
    }
    // 'EvalCurvStructNoCtx:50' r1D = a   .* r1D;
    // 'EvalCurvStructNoCtx:51' r2D = a^2 .* r2D;
    // 'EvalCurvStructNoCtx:52' r3D = a^3 .* r3D;
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
    int b_loop_ub;
    int b_tmp_size;
    int c_loop_ub;
    int loop_ub;
    int tmp_size;
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:7' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    // 'EvalCurvStructNoCtx:8' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    //
    // 'EvalCurvStructNoCtx:11' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:13' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:14' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:16' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:17' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:17' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:17' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:19' a = curv.a_param;
    // 'EvalCurvStructNoCtx:20' b = curv.b_param;
    // 'EvalCurvStructNoCtx:22' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv->a_param + curv->b_param;
    // 'EvalCurvStructNoCtx:24' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:25' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:26' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:27' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:28' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:30' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:31' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:32' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(6);
        r1D.reserve(6);
        b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), &(*(int(*)[1])r0D.size())[0], (double *)r1D.data(),
                   &(*(int(*)[1])r1D.size())[0], r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:33' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:34' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            double dv[3];
            double dv1[3];
            double dv2[3];
            double dv3[3];
            int c_tmp_data[3];
            int c_tmp_size;
            int d_loop_ub;
            int h_loop_ub;
            int j_loop_ub;
            int m_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:35' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:36'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            d_loop_ub = cfg_indCart.size(0);
            for (int i6{0}; i6 < d_loop_ub; i6++) {
                c_tmp_data[i6] = cfg_indCart[i6] - 1;
            }
            for (int i8{0}; i8 < c_tmp_size; i8++) {
                r0D[c_tmp_data[i8]] = dv[i8];
            }
            c_tmp_size = cfg_indCart.size(0);
            h_loop_ub = cfg_indCart.size(0);
            for (int i11{0}; i11 < h_loop_ub; i11++) {
                c_tmp_data[i11] = cfg_indCart[i11] - 1;
            }
            for (int i12{0}; i12 < c_tmp_size; i12++) {
                r1D[c_tmp_data[i12]] = dv1[i12];
            }
            c_tmp_size = cfg_indCart.size(0);
            j_loop_ub = cfg_indCart.size(0);
            for (int i14{0}; i14 < j_loop_ub; i14++) {
                c_tmp_data[i14] = cfg_indCart[i14] - 1;
            }
            for (int i16{0}; i16 < c_tmp_size; i16++) {
                r2D[c_tmp_data[i16]] = dv2[i16];
            }
            c_tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            for (int i18{0}; i18 < m_loop_ub; i18++) {
                c_tmp_data[i18] = cfg_indCart[i18] - 1;
            }
            for (int i19{0}; i19 < c_tmp_size; i19++) {
                r3D[c_tmp_data[i19]] = dv3[i19];
            }
        }
        // 'EvalCurvStructNoCtx:38' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int e_loop_ub;
            int f_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:39' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:40'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, &tmp_size, b_tmp_data, &b_tmp_size, r, r1);
            for (int i3{0}; i3 < tmp_size; i3++) {
                r0D[cfg_indRot[i3] - 1] = tmp_data[i3];
            }
            for (int i4{0}; i4 < b_tmp_size; i4++) {
                r1D[cfg_indRot[i4] - 1] = b_tmp_data[i4];
            }
            e_loop_ub = r.size(0);
            for (int i7{0}; i7 < e_loop_ub; i7++) {
                r2D[cfg_indRot[i7] - 1] = r[i7];
            }
            f_loop_ub = r1.size(0);
            for (int i9{0}; i9 < f_loop_ub; i9++) {
                r3D[cfg_indRot[i9] - 1] = r1[i9];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:42' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:43' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int g_loop_ub;
        int i20;
        int i_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        // 'EvalCurvStructNoCtx:44' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:45' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        g_loop_ub = spline->sp.coeff.size(0);
        for (int i10{0}; i10 < g_loop_ub; i10++) {
            r0D[i10] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        i_loop_ub = spline->sp.coeff.size(0);
        for (int i13{0}; i13 < i_loop_ub; i13++) {
            r1D[i13] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        k_loop_ub = spline->sp.coeff.size(0);
        for (int i15{0}; i15 < k_loop_ub; i15++) {
            r2D[i15] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        l_loop_ub = spline->sp.coeff.size(0);
        for (int i17{0}; i17 < l_loop_ub; i17++) {
            r3D[i17] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i20 = spline->sp.coeff.size(0);
        for (int j{0}; j < i20; j++) {
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
    default:
        // 'EvalCurvStructNoCtx:46' otherwise
        // 'EvalCurvStructNoCtx:47' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        break;
    }
    // 'EvalCurvStructNoCtx:50' r1D = a   .* r1D;
    loop_ub = r1D.size(0);
    for (int i1{0}; i1 < loop_ub; i1++) {
        r1D[i1] = curv->a_param * r1D[i1];
    }
    // 'EvalCurvStructNoCtx:51' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    b_loop_ub = r2D.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        r2D[i2] = c * r2D[i2];
    }
    // 'EvalCurvStructNoCtx:52' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    c_loop_ub = r3D.size(0);
    for (int i5{0}; i5 < c_loop_ub; i5++) {
        r3D[i5] = b_c * r3D[i5];
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
    int b_loop_ub;
    int b_tmp_size;
    int c_loop_ub;
    int loop_ub;
    int tmp_size;
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:7' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    // 'EvalCurvStructNoCtx:8' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    //
    // 'EvalCurvStructNoCtx:11' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:13' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:14' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:16' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:17' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:17' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:17' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:19' a = curv.a_param;
    // 'EvalCurvStructNoCtx:20' b = curv.b_param;
    // 'EvalCurvStructNoCtx:22' u_vec_tilda = a * u_vec + b;
    // 'EvalCurvStructNoCtx:24' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:25' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:26' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:27' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:28' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:30' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:31' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:32' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(6);
        r1D.reserve(6);
        b_EvalLine(curv->R0, curv->R1, curv->b_param, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), &(*(int(*)[1])r0D.size())[0], (double *)r1D.data(),
                   &(*(int(*)[1])r1D.size())[0], r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:33' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:34' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            double dv[3];
            double dv1[3];
            double dv2[3];
            double dv3[3];
            int c_tmp_data[3];
            int c_tmp_size;
            int d_loop_ub;
            int h_loop_ub;
            int j_loop_ub;
            int m_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:35' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:36'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        curv->b_param, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            d_loop_ub = cfg_indCart.size(0);
            for (int i6{0}; i6 < d_loop_ub; i6++) {
                c_tmp_data[i6] = cfg_indCart[i6] - 1;
            }
            for (int i8{0}; i8 < c_tmp_size; i8++) {
                r0D[c_tmp_data[i8]] = dv[i8];
            }
            c_tmp_size = cfg_indCart.size(0);
            h_loop_ub = cfg_indCart.size(0);
            for (int i11{0}; i11 < h_loop_ub; i11++) {
                c_tmp_data[i11] = cfg_indCart[i11] - 1;
            }
            for (int i12{0}; i12 < c_tmp_size; i12++) {
                r1D[c_tmp_data[i12]] = dv1[i12];
            }
            c_tmp_size = cfg_indCart.size(0);
            j_loop_ub = cfg_indCart.size(0);
            for (int i14{0}; i14 < j_loop_ub; i14++) {
                c_tmp_data[i14] = cfg_indCart[i14] - 1;
            }
            for (int i16{0}; i16 < c_tmp_size; i16++) {
                r2D[c_tmp_data[i16]] = dv2[i16];
            }
            c_tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            for (int i18{0}; i18 < m_loop_ub; i18++) {
                c_tmp_data[i18] = cfg_indCart[i18] - 1;
            }
            for (int i19{0}; i19 < c_tmp_size; i19++) {
                r3D[c_tmp_data[i19]] = dv3[i19];
            }
        }
        // 'EvalCurvStructNoCtx:38' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int e_loop_ub;
            int f_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:39' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:40'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, curv->b_param, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, &tmp_size, b_tmp_data, &b_tmp_size, r, r1);
            for (int i3{0}; i3 < tmp_size; i3++) {
                r0D[cfg_indRot[i3] - 1] = tmp_data[i3];
            }
            for (int i4{0}; i4 < b_tmp_size; i4++) {
                r1D[cfg_indRot[i4] - 1] = b_tmp_data[i4];
            }
            e_loop_ub = r.size(0);
            for (int i7{0}; i7 < e_loop_ub; i7++) {
                r2D[cfg_indRot[i7] - 1] = r[i7];
            }
            f_loop_ub = r1.size(0);
            for (int i9{0}; i9 < f_loop_ub; i9++) {
                r3D[cfg_indRot[i9] - 1] = r1[i9];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:42' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:43' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, curv->b_param, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int g_loop_ub;
        int i20;
        int i_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        // 'EvalCurvStructNoCtx:44' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:45' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        g_loop_ub = spline->sp.coeff.size(0);
        for (int i10{0}; i10 < g_loop_ub; i10++) {
            r0D[i10] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        i_loop_ub = spline->sp.coeff.size(0);
        for (int i13{0}; i13 < i_loop_ub; i13++) {
            r1D[i13] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        k_loop_ub = spline->sp.coeff.size(0);
        for (int i15{0}; i15 < k_loop_ub; i15++) {
            r2D[i15] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        l_loop_ub = spline->sp.coeff.size(0);
        for (int i17{0}; i17 < l_loop_ub; i17++) {
            r3D[i17] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i20 = spline->sp.coeff.size(0);
        for (int j{0}; j < i20; j++) {
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
    default:
        // 'EvalCurvStructNoCtx:46' otherwise
        // 'EvalCurvStructNoCtx:47' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        break;
    }
    // 'EvalCurvStructNoCtx:50' r1D = a   .* r1D;
    loop_ub = r1D.size(0);
    for (int i1{0}; i1 < loop_ub; i1++) {
        r1D[i1] = curv->a_param * r1D[i1];
    }
    // 'EvalCurvStructNoCtx:51' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    b_loop_ub = r2D.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        r2D[i2] = c * r2D[i2];
    }
    // 'EvalCurvStructNoCtx:52' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    c_loop_ub = r3D.size(0);
    for (int i5{0}; i5 < c_loop_ub; i5++) {
        r3D[i5] = b_c * r3D[i5];
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
//                const ::coder::array<double, 2U> &u_vec
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void e_EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                           const bool cfg_maskCart_data[], const int cfg_maskCart_size[2],
                           const bool cfg_maskRot_data[], const int cfg_maskRot_size[2],
                           const ::coder::array<int, 1U> &cfg_indCart,
                           const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                           int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                           const CurvStruct *spline, const ::coder::array<double, 2U> &u_vec,
                           ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D,
                           ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r10;
    ::coder::array<double, 2U> r11;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> r5;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> r7;
    ::coder::array<double, 2U> r8;
    ::coder::array<double, 2U> r9;
    ::coder::array<double, 2U> u_vec_tilda;
    double b_c;
    double c;
    double d;
    double d1;
    double d2;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int i_loop_ub;
    int loop_ub;
    int m_loop_ub;
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:7' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    // 'EvalCurvStructNoCtx:8' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    //
    // 'EvalCurvStructNoCtx:11' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:13' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:14' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:16' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        for (int i1{0}; i1 < cfg_NumberAxis; i1++) {
            r0D[i1 + r0D.size(0) * i] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:17' r1D = r0D;
    r1D.set_size(cfg_NumberAxis, u_vec.size(1));
    b_loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        for (int i3{0}; i3 < cfg_NumberAxis; i3++) {
            r1D[i3 + r1D.size(0) * i2] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:17' r2D = r0D;
    r2D.set_size(cfg_NumberAxis, u_vec.size(1));
    c_loop_ub = u_vec.size(1);
    for (int i4{0}; i4 < c_loop_ub; i4++) {
        for (int i5{0}; i5 < cfg_NumberAxis; i5++) {
            r2D[i5 + r2D.size(0) * i4] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:17' r3D = r0D;
    r3D.set_size(cfg_NumberAxis, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        for (int i7{0}; i7 < cfg_NumberAxis; i7++) {
            r3D[i7 + r3D.size(0) * i6] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:19' a = curv.a_param;
    // 'EvalCurvStructNoCtx:20' b = curv.b_param;
    // 'EvalCurvStructNoCtx:22' u_vec_tilda = a * u_vec + b;
    u_vec_tilda.set_size(1, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i8{0}; i8 < e_loop_ub; i8++) {
        u_vec_tilda[i8] = curv->a_param * u_vec[i8] + curv->b_param;
    }
    // 'EvalCurvStructNoCtx:24' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:25' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:26' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:27' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:28' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:30' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:31' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:32' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        c_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size, r0D, r1D,
                   r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:33' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:34' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int h_loop_ub;
            int k_loop_ub;
            int p_loop_ub;
            int t_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:35' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:36'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            c_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, r, r1, r2, r3);
            h_loop_ub = r.size(1);
            for (int i11{0}; i11 < h_loop_ub; i11++) {
                r0D[(cfg_indCart[0] + r0D.size(0) * i11) - 1] = r[3 * i11];
                r0D[(cfg_indCart[1] + r0D.size(0) * i11) - 1] = r[3 * i11 + 1];
                r0D[(cfg_indCart[2] + r0D.size(0) * i11) - 1] = r[3 * i11 + 2];
            }
            k_loop_ub = r1.size(1);
            for (int i14{0}; i14 < k_loop_ub; i14++) {
                r1D[(cfg_indCart[0] + r1D.size(0) * i14) - 1] = r1[3 * i14];
                r1D[(cfg_indCart[1] + r1D.size(0) * i14) - 1] = r1[3 * i14 + 1];
                r1D[(cfg_indCart[2] + r1D.size(0) * i14) - 1] = r1[3 * i14 + 2];
            }
            p_loop_ub = r2.size(1);
            for (int i19{0}; i19 < p_loop_ub; i19++) {
                r2D[(cfg_indCart[0] + r2D.size(0) * i19) - 1] = r2[3 * i19];
                r2D[(cfg_indCart[1] + r2D.size(0) * i19) - 1] = r2[3 * i19 + 1];
                r2D[(cfg_indCart[2] + r2D.size(0) * i19) - 1] = r2[3 * i19 + 2];
            }
            t_loop_ub = r3.size(1);
            for (int i23{0}; i23 < t_loop_ub; i23++) {
                r3D[(cfg_indCart[0] + r3D.size(0) * i23) - 1] = r3[3 * i23];
                r3D[(cfg_indCart[1] + r3D.size(0) * i23) - 1] = r3[3 * i23 + 1];
                r3D[(cfg_indCart[2] + r3D.size(0) * i23) - 1] = r3[3 * i23 + 2];
            }
        }
        // 'EvalCurvStructNoCtx:38' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int j_loop_ub;
            int n_loop_ub;
            int r_loop_ub;
            int u_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:39' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:40'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            c_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size, r4, r5,
                       r6, r7);
            j_loop_ub = r4.size(1);
            for (int i13{0}; i13 < j_loop_ub; i13++) {
                int o_loop_ub;
                o_loop_ub = r4.size(0);
                for (int i18{0}; i18 < o_loop_ub; i18++) {
                    r0D[(cfg_indRot[i18] + r0D.size(0) * i13) - 1] = r4[i18 + r4.size(0) * i13];
                }
            }
            n_loop_ub = r5.size(1);
            for (int i17{0}; i17 < n_loop_ub; i17++) {
                int s_loop_ub;
                s_loop_ub = r5.size(0);
                for (int i22{0}; i22 < s_loop_ub; i22++) {
                    r1D[(cfg_indRot[i22] + r1D.size(0) * i17) - 1] = r5[i22 + r5.size(0) * i17];
                }
            }
            r_loop_ub = r6.size(1);
            for (int i21{0}; i21 < r_loop_ub; i21++) {
                int v_loop_ub;
                v_loop_ub = r6.size(0);
                for (int i25{0}; i25 < v_loop_ub; i25++) {
                    r2D[(cfg_indRot[i25] + r2D.size(0) * i21) - 1] = r6[i25 + r6.size(0) * i21];
                }
            }
            u_loop_ub = r7.size(1);
            for (int i24{0}; i24 < u_loop_ub; i24++) {
                int x_loop_ub;
                x_loop_ub = r7.size(0);
                for (int i27{0}; i27 < x_loop_ub; i27++) {
                    r3D[(cfg_indRot[i27] + r3D.size(0) * i24) - 1] = r7[i27 + r7.size(0) * i24];
                }
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:42' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:43' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int ab_loop_ub;
        int i33;
        int unnamed_idx_0;
        int w_loop_ub;
        int y_loop_ub;
        // 'EvalCurvStructNoCtx:44' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:45' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        w_loop_ub = u_vec_tilda.size(1);
        for (int i26{0}; i26 < w_loop_ub; i26++) {
            for (int i28{0}; i28 < unnamed_idx_0; i28++) {
                r1D[i28 + r1D.size(0) * i26] = 0.0;
            }
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        y_loop_ub = u_vec_tilda.size(1);
        for (int i29{0}; i29 < y_loop_ub; i29++) {
            for (int i30{0}; i30 < unnamed_idx_0; i30++) {
                r2D[i30 + r2D.size(0) * i29] = 0.0;
            }
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        ab_loop_ub = u_vec_tilda.size(1);
        for (int i31{0}; i31 < ab_loop_ub; i31++) {
            for (int i32{0}; i32 < unnamed_idx_0; i32++) {
                r3D[i32 + r3D.size(0) * i31] = 0.0;
            }
        }
        // 'EvalBSpline:20' for j = 1 : M
        i33 = spline->sp.coeff.size(0);
        r0D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        for (int j{0}; j < i33; j++) {
            int bb_loop_ub;
            int cb_loop_ub;
            int db_loop_ub;
            int eb_loop_ub;
            int fb_loop_ub;
            int hb_loop_ub;
            int i38;
            int ib_loop_ub;
            int jb_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
            r8.set_size(1, u_vec_tilda.size(1));
            bb_loop_ub = u_vec_tilda.size(1);
            for (int i34{0}; i34 < bb_loop_ub; i34++) {
                r8[i34] = 0.0;
            }
            // 'bspline_eval_vec:4' xd      = zeros(size(u));
            r9.set_size(1, u_vec_tilda.size(1));
            cb_loop_ub = u_vec_tilda.size(1);
            for (int i35{0}; i35 < cb_loop_ub; i35++) {
                r9[i35] = 0.0;
            }
            // 'bspline_eval_vec:5' xdd     = zeros(size(u));
            r10.set_size(1, u_vec_tilda.size(1));
            db_loop_ub = u_vec_tilda.size(1);
            for (int i36{0}; i36 < db_loop_ub; i36++) {
                r10[i36] = 0.0;
            }
            // 'bspline_eval_vec:6' xddd    = zeros(size(u));
            r11.set_size(1, u_vec_tilda.size(1));
            eb_loop_ub = u_vec_tilda.size(1);
            for (int i37{0}; i37 < eb_loop_ub; i37++) {
                r11[i37] = 0.0;
            }
            // 'bspline_eval_vec:8' for k = 1:length(u)
            i38 = u_vec_tilda.size(1);
            for (int k{0}; k < i38; k++) {
                int gb_loop_ub;
                // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
                r8[k] = u_vec_tilda[k];
                gb_loop_ub = spline->sp.coeff.size(1);
                b_spline.set_size(1, spline->sp.coeff.size(1));
                for (int i41{0}; i41 < gb_loop_ub; i41++) {
                    b_spline[i41] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i41];
                }
                bspline_eval(spline->sp.Bl.handle, b_spline, &r8[k], &d, &d1, &d2);
                r11[k] = d2;
                r10[k] = d1;
                r9[k] = d;
                // 'bspline_eval_vec:10' x(k)    = xk;
                // 'bspline_eval_vec:11' xd(k)   = xdk;
                // 'bspline_eval_vec:12' xdd(k)  = xddk;
                // 'bspline_eval_vec:13' xddd(k) = xdddk;
            }
            fb_loop_ub = r8.size(1);
            for (int i39{0}; i39 < fb_loop_ub; i39++) {
                r0D[j + r0D.size(0) * i39] = r8[i39];
            }
            hb_loop_ub = r9.size(1);
            for (int i40{0}; i40 < hb_loop_ub; i40++) {
                r1D[j + r1D.size(0) * i40] = r9[i40];
            }
            ib_loop_ub = r10.size(1);
            for (int i42{0}; i42 < ib_loop_ub; i42++) {
                r2D[j + r2D.size(0) * i42] = r10[i42];
            }
            jb_loop_ub = r11.size(1);
            for (int i43{0}; i43 < jb_loop_ub; i43++) {
                r3D[j + r3D.size(0) * i43] = r11[i43];
            }
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:46' otherwise
        // 'EvalCurvStructNoCtx:47' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        break;
    }
    // 'EvalCurvStructNoCtx:50' r1D = a   .* r1D;
    f_loop_ub = r1D.size(1);
    for (int i9{0}; i9 < f_loop_ub; i9++) {
        int g_loop_ub;
        g_loop_ub = r1D.size(0);
        for (int i10{0}; i10 < g_loop_ub; i10++) {
            r1D[i10 + r1D.size(0) * i9] = curv->a_param * r1D[i10 + r1D.size(0) * i9];
        }
    }
    // 'EvalCurvStructNoCtx:51' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    i_loop_ub = r2D.size(1);
    for (int i12{0}; i12 < i_loop_ub; i12++) {
        int l_loop_ub;
        l_loop_ub = r2D.size(0);
        for (int i15{0}; i15 < l_loop_ub; i15++) {
            r2D[i15 + r2D.size(0) * i12] = c * r2D[i15 + r2D.size(0) * i12];
        }
    }
    // 'EvalCurvStructNoCtx:52' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    m_loop_ub = r3D.size(1);
    for (int i16{0}; i16 < m_loop_ub; i16++) {
        int q_loop_ub;
        q_loop_ub = r3D.size(0);
        for (int i20{0}; i20 < q_loop_ub; i20++) {
            r3D[i20 + r3D.size(0) * i16] = b_c * r3D[i20 + r3D.size(0) * i16];
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
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
void f_EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                           const bool cfg_maskCart_data[], const int cfg_maskCart_size[2],
                           const bool cfg_maskRot_data[], const int cfg_maskRot_size[2],
                           const ::coder::array<int, 1U> &cfg_indCart,
                           const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                           int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                           const CurvStruct *spline, ::coder::array<double, 2U> &r0D,
                           ::coder::array<double, 2U> &r1D, ::coder::array<double, 2U> &r2D,
                           ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    double b_tmp_data[12];
    double tmp_data[12];
    double dv4[2];
    double dv5[2];
    double dv6[2];
    double dv7[2];
    double u_vec_tilda[2];
    double b_c;
    double c;
    int b_tmp_size[2];
    int tmp_size[2];
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:7' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    // 'EvalCurvStructNoCtx:8' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    //
    // 'EvalCurvStructNoCtx:11' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:13' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:14' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:16' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis, 2);
    // 'EvalCurvStructNoCtx:17' r1D = r0D;
    r1D.set_size(cfg_NumberAxis, 2);
    // 'EvalCurvStructNoCtx:17' r2D = r0D;
    r2D.set_size(cfg_NumberAxis, 2);
    // 'EvalCurvStructNoCtx:17' r3D = r0D;
    r3D.set_size(cfg_NumberAxis, 2);
    // 'EvalCurvStructNoCtx:19' a = curv.a_param;
    // 'EvalCurvStructNoCtx:20' b = curv.b_param;
    // 'EvalCurvStructNoCtx:22' u_vec_tilda = a * u_vec + b;
    for (int i{0}; i < 2; i++) {
        for (int i1{0}; i1 < cfg_NumberAxis; i1++) {
            r0D[i1 + r0D.size(0) * i] = 0.0;
            r1D[i1 + r1D.size(0) * i] = 0.0;
            r2D[i1 + r2D.size(0) * i] = 0.0;
            r3D[i1 + r3D.size(0) * i] = 0.0;
        }
        u_vec_tilda[i] = curv->a_param * static_cast<double>(i) + curv->b_param;
    }
    // 'EvalCurvStructNoCtx:24' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:25' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:26' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:27' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:28' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:30' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:31' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:32' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(12);
        r1D.reserve(12);
        d_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), *(int(*)[2])r0D.size(), (double *)r1D.data(),
                   *(int(*)[2])r1D.size(), r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:33' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:34' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            double dv[2][3];
            double dv1[2][3];
            double dv2[2][3];
            double dv3[2][3];
            int c_tmp_data[3];
            int c_tmp_size;
            int f_loop_ub;
            int i_loop_ub;
            int k_loop_ub;
            int l_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:35' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:36'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            d_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            f_loop_ub = cfg_indCart.size(0);
            for (int i5{0}; i5 < f_loop_ub; i5++) {
                c_tmp_data[i5] = cfg_indCart[i5] - 1;
            }
            for (int i8{0}; i8 < 2; i8++) {
                for (int i10{0}; i10 < c_tmp_size; i10++) {
                    r0D[c_tmp_data[i10] + r0D.size(0) * i8] = dv[i8][i10];
                }
            }
            c_tmp_size = cfg_indCart.size(0);
            i_loop_ub = cfg_indCart.size(0);
            for (int i13{0}; i13 < i_loop_ub; i13++) {
                c_tmp_data[i13] = cfg_indCart[i13] - 1;
            }
            for (int i15{0}; i15 < 2; i15++) {
                for (int i17{0}; i17 < c_tmp_size; i17++) {
                    r1D[c_tmp_data[i17] + r1D.size(0) * i15] = dv1[i15][i17];
                }
            }
            c_tmp_size = cfg_indCart.size(0);
            k_loop_ub = cfg_indCart.size(0);
            for (int i20{0}; i20 < k_loop_ub; i20++) {
                c_tmp_data[i20] = cfg_indCart[i20] - 1;
            }
            for (int i21{0}; i21 < 2; i21++) {
                for (int i22{0}; i22 < c_tmp_size; i22++) {
                    r2D[c_tmp_data[i22] + r2D.size(0) * i21] = dv2[i21][i22];
                }
            }
            c_tmp_size = cfg_indCart.size(0);
            l_loop_ub = cfg_indCart.size(0);
            for (int i23{0}; i23 < l_loop_ub; i23++) {
                c_tmp_data[i23] = cfg_indCart[i23] - 1;
            }
            for (int i24{0}; i24 < 2; i24++) {
                for (int i25{0}; i25 < c_tmp_size; i25++) {
                    r3D[c_tmp_data[i25] + r3D.size(0) * i24] = dv3[i24][i25];
                }
            }
        }
        // 'EvalCurvStructNoCtx:38' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int b_loop_ub;
            int d_loop_ub;
            int e_loop_ub;
            int loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:39' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:40'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            d_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, tmp_size, b_tmp_data, b_tmp_size, r, r1);
            loop_ub = tmp_size[0];
            b_loop_ub = b_tmp_size[0];
            d_loop_ub = r.size(0);
            e_loop_ub = r1.size(0);
            for (int i4{0}; i4 < 2; i4++) {
                for (int i7{0}; i7 < loop_ub; i7++) {
                    r0D[(cfg_indRot[i7] + r0D.size(0) * i4) - 1] = tmp_data[i7 + tmp_size[0] * i4];
                }
                for (int i9{0}; i9 < b_loop_ub; i9++) {
                    r1D[(cfg_indRot[i9] + r1D.size(0) * i4) - 1] =
                        b_tmp_data[i9 + b_tmp_size[0] * i4];
                }
                for (int i12{0}; i12 < d_loop_ub; i12++) {
                    r2D[(cfg_indRot[i12] + r2D.size(0) * i4) - 1] = r[i12 + r.size(0) * i4];
                }
                for (int i14{0}; i14 < e_loop_ub; i14++) {
                    r3D[(cfg_indRot[i14] + r3D.size(0) * i4) - 1] = r1[i14 + r1.size(0) * i4];
                }
            }
        }
    } break;
    case CurveType_Spline: {
        int i19;
        int j_loop_ub;
        // 'EvalCurvStructNoCtx:44' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:45' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0), 2);
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0), 2);
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0), 2);
        j_loop_ub = spline->sp.coeff.size(0);
        for (int i16{0}; i16 < 2; i16++) {
            for (int i18{0}; i18 < j_loop_ub; i18++) {
                r1D[i18 + r1D.size(0) * i16] = 0.0;
                r2D[i18 + r2D.size(0) * i16] = 0.0;
                r3D[i18 + r3D.size(0) * i16] = 0.0;
            }
        }
        // 'EvalBSpline:20' for j = 1 : M
        i19 = spline->sp.coeff.size(0);
        r0D.set_size(spline->sp.coeff.size(0), 2);
        for (int j{0}; j < i19; j++) {
            int m_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            m_loop_ub = spline->sp.coeff.size(1);
            for (int k{0}; k < 2; k++) {
                // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
                dv4[k] = u_vec_tilda[k];
                b_spline.set_size(1, m_loop_ub);
                for (int i26{0}; i26 < m_loop_ub; i26++) {
                    b_spline[i26] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i26];
                }
                bspline_eval(spline->sp.Bl.handle, b_spline, &dv4[k], &dv5[k], &dv6[k], &dv7[k]);
                // 'bspline_eval_vec:10' x(k)    = xk;
                // 'bspline_eval_vec:11' xd(k)   = xdk;
                // 'bspline_eval_vec:12' xdd(k)  = xddk;
                // 'bspline_eval_vec:13' xddd(k) = xdddk;
            }
            r0D[j] = dv4[0];
            r1D[j] = dv5[0];
            r2D[j] = dv6[0];
            r3D[j] = dv7[0];
            r0D[j + r0D.size(0)] = dv4[1];
            r1D[j + r1D.size(0)] = dv5[1];
            r2D[j + r2D.size(0)] = dv6[1];
            r3D[j + r3D.size(0)] = dv7[1];
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:46' otherwise
        // 'EvalCurvStructNoCtx:47' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        break;
    }
    // 'EvalCurvStructNoCtx:50' r1D = a   .* r1D;
    r1D.set_size(r1D.size(0), 2);
    // 'EvalCurvStructNoCtx:51' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    r2D.set_size(r2D.size(0), 2);
    // 'EvalCurvStructNoCtx:52' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    r3D.set_size(r3D.size(0), 2);
    for (int i2{0}; i2 < 2; i2++) {
        int c_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        c_loop_ub = r1D.size(0);
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            r1D[i3 + r1D.size(0) * i2] = curv->a_param * r1D[i3 + r1D.size(0) * i2];
        }
        g_loop_ub = r2D.size(0);
        for (int i6{0}; i6 < g_loop_ub; i6++) {
            r2D[i6 + r2D.size(0) * i2] = c * r2D[i6 + r2D.size(0) * i2];
        }
        h_loop_ub = r3D.size(0);
        for (int i11{0}; i11 < h_loop_ub; i11++) {
            r3D[i11 + r3D.size(0) * i2] = b_c * r3D[i11 + r3D.size(0) * i2];
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
//                ::coder::array<double, 1U> &r1D
//                ::coder::array<double, 1U> &r2D
//                ::coder::array<double, 1U> &r3D
// Return Type  : void
//
void g_EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
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
    int b_loop_ub;
    int b_tmp_size;
    int c_loop_ub;
    int loop_ub;
    int tmp_size;
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:7' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    // 'EvalCurvStructNoCtx:8' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    //
    // 'EvalCurvStructNoCtx:11' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:13' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:14' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:16' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:17' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:17' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:17' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:19' a = curv.a_param;
    // 'EvalCurvStructNoCtx:20' b = curv.b_param;
    // 'EvalCurvStructNoCtx:22' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv->a_param * u_vec + curv->b_param;
    // 'EvalCurvStructNoCtx:24' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:25' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:26' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:27' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:28' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:30' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:31' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:32' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(6);
        r1D.reserve(6);
        b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), &(*(int(*)[1])r0D.size())[0], (double *)r1D.data(),
                   &(*(int(*)[1])r1D.size())[0], r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:33' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:34' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            double dv[3];
            double dv1[3];
            double dv2[3];
            double dv3[3];
            int c_tmp_data[3];
            int c_tmp_size;
            int d_loop_ub;
            int h_loop_ub;
            int j_loop_ub;
            int m_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:35' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:36'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            d_loop_ub = cfg_indCart.size(0);
            for (int i6{0}; i6 < d_loop_ub; i6++) {
                c_tmp_data[i6] = cfg_indCart[i6] - 1;
            }
            for (int i8{0}; i8 < c_tmp_size; i8++) {
                r0D[c_tmp_data[i8]] = dv[i8];
            }
            c_tmp_size = cfg_indCart.size(0);
            h_loop_ub = cfg_indCart.size(0);
            for (int i11{0}; i11 < h_loop_ub; i11++) {
                c_tmp_data[i11] = cfg_indCart[i11] - 1;
            }
            for (int i12{0}; i12 < c_tmp_size; i12++) {
                r1D[c_tmp_data[i12]] = dv1[i12];
            }
            c_tmp_size = cfg_indCart.size(0);
            j_loop_ub = cfg_indCart.size(0);
            for (int i14{0}; i14 < j_loop_ub; i14++) {
                c_tmp_data[i14] = cfg_indCart[i14] - 1;
            }
            for (int i16{0}; i16 < c_tmp_size; i16++) {
                r2D[c_tmp_data[i16]] = dv2[i16];
            }
            c_tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            for (int i18{0}; i18 < m_loop_ub; i18++) {
                c_tmp_data[i18] = cfg_indCart[i18] - 1;
            }
            for (int i19{0}; i19 < c_tmp_size; i19++) {
                r3D[c_tmp_data[i19]] = dv3[i19];
            }
        }
        // 'EvalCurvStructNoCtx:38' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int e_loop_ub;
            int f_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:39' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:40'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, &tmp_size, b_tmp_data, &b_tmp_size, r, r1);
            for (int i3{0}; i3 < tmp_size; i3++) {
                r0D[cfg_indRot[i3] - 1] = tmp_data[i3];
            }
            for (int i4{0}; i4 < b_tmp_size; i4++) {
                r1D[cfg_indRot[i4] - 1] = b_tmp_data[i4];
            }
            e_loop_ub = r.size(0);
            for (int i7{0}; i7 < e_loop_ub; i7++) {
                r2D[cfg_indRot[i7] - 1] = r[i7];
            }
            f_loop_ub = r1.size(0);
            for (int i9{0}; i9 < f_loop_ub; i9++) {
                r3D[cfg_indRot[i9] - 1] = r1[i9];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:42' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:43' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int g_loop_ub;
        int i20;
        int i_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        // 'EvalCurvStructNoCtx:44' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:45' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        g_loop_ub = spline->sp.coeff.size(0);
        for (int i10{0}; i10 < g_loop_ub; i10++) {
            r0D[i10] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        i_loop_ub = spline->sp.coeff.size(0);
        for (int i13{0}; i13 < i_loop_ub; i13++) {
            r1D[i13] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        k_loop_ub = spline->sp.coeff.size(0);
        for (int i15{0}; i15 < k_loop_ub; i15++) {
            r2D[i15] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        l_loop_ub = spline->sp.coeff.size(0);
        for (int i17{0}; i17 < l_loop_ub; i17++) {
            r3D[i17] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i20 = spline->sp.coeff.size(0);
        for (int j{0}; j < i20; j++) {
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
    default:
        // 'EvalCurvStructNoCtx:46' otherwise
        // 'EvalCurvStructNoCtx:47' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        break;
    }
    // 'EvalCurvStructNoCtx:50' r1D = a   .* r1D;
    loop_ub = r1D.size(0);
    for (int i1{0}; i1 < loop_ub; i1++) {
        r1D[i1] = curv->a_param * r1D[i1];
    }
    // 'EvalCurvStructNoCtx:51' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    b_loop_ub = r2D.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        r2D[i2] = c * r2D[i2];
    }
    // 'EvalCurvStructNoCtx:52' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    c_loop_ub = r3D.size(0);
    for (int i5{0}; i5 < c_loop_ub; i5++) {
        r3D[i5] = b_c * r3D[i5];
    }
}

} // namespace ocn

//
// File trailer for EvalCurvStructNoCtx.cpp
//
// [EOF]
//
