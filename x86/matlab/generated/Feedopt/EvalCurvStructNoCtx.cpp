
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
#include "ocn_assert.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
// EvalCurvStructNoCtx : Eval curve structure and its derivatives on
//  a set of u points without any need of the context structure.
//
//  Inputs :
//  cfg       : The configuration structure of the computational chain
//  curv      : The curve used in the evaluation
//  spline    : The required spline for the evaluation
//  u_vec     : U vectors
//
//  Outputs :
//  r0D   : Matrix of points for a given set of u values
//  r1D   : Matrix of points (first derivative) for a given set of u values
//  r2D   : Matrix of points (second derivative) for a given set of u values
//  r3D   : Matrix of points (third derivative) for a given set of u values
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
    ::coder::array<double, 1U> r7;
    ::coder::array<double, 1U> r8;
    ::coder::array<double, 1U> r9;
    ::coder::array<double, 1U> u_vec_tilda;
    ::coder::array<bool, 1U> x;
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
    int j_loop_ub;
    int k;
    int loop_ub;
    int n_loop_ub;
    int scalarLB;
    int vectorUB;
    bool b_varargout_1;
    bool exitg1;
    bool varargout_1;
    // 'EvalCurvStructNoCtx:18' coder.inline("never");
    // 'EvalCurvStructNoCtx:20' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    x.set_size(u_vec.size(0));
    loop_ub = u_vec.size(0);
    for (int i{0}; i < loop_ub; i++) {
        x[i] = (u_vec[i] > 1.0);
    }
    varargout_1 = false;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(0) - 1)) {
        if (x[k]) {
            varargout_1 = true;
            exitg1 = true;
        } else {
            k++;
        }
    }
    c_ocn_assert(!varargout_1);
    // 'EvalCurvStructNoCtx:21' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    x.set_size(u_vec.size(0));
    b_loop_ub = u_vec.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        x[i1] = (u_vec[i1] < 0.0);
    }
    b_varargout_1 = false;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k <= x.size(0) - 1)) {
        if (x[b_k]) {
            b_varargout_1 = true;
            exitg1 = true;
        } else {
            b_k++;
        }
    }
    d_ocn_assert(!b_varargout_1);
    //
    // 'EvalCurvStructNoCtx:24' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:26' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:27' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:29' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis, u_vec.size(0));
    c_loop_ub = u_vec.size(0);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        for (int i3{0}; i3 < cfg_NumberAxis; i3++) {
            r0D[i3 + r0D.size(0) * i2] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:30' r1D = r0D;
    r1D.set_size(cfg_NumberAxis, u_vec.size(0));
    d_loop_ub = u_vec.size(0);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        for (int i5{0}; i5 < cfg_NumberAxis; i5++) {
            r1D[i5 + r1D.size(0) * i4] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:30' r2D = r0D;
    r2D.set_size(cfg_NumberAxis, u_vec.size(0));
    e_loop_ub = u_vec.size(0);
    for (int i6{0}; i6 < e_loop_ub; i6++) {
        for (int i7{0}; i7 < cfg_NumberAxis; i7++) {
            r2D[i7 + r2D.size(0) * i6] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:30' r3D = r0D;
    r3D.set_size(cfg_NumberAxis, u_vec.size(0));
    f_loop_ub = u_vec.size(0);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        for (int i9{0}; i9 < cfg_NumberAxis; i9++) {
            r3D[i9 + r3D.size(0) * i8] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:32' a = curv.a_param;
    // 'EvalCurvStructNoCtx:33' b = curv.b_param;
    // 'EvalCurvStructNoCtx:35' u_vec_tilda = a * u_vec + b;
    u_vec_tilda.set_size(u_vec.size(0));
    g_loop_ub = u_vec.size(0);
    scalarLB = (u_vec.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i10{0}; i10 <= vectorUB; i10 += 2) {
        _mm_storeu_pd(&u_vec_tilda[i10],
                      _mm_add_pd(_mm_mul_pd(_mm_set1_pd(curv->a_param),
                                            _mm_loadu_pd((const double *)&u_vec[i10])),
                                 _mm_set1_pd(curv->b_param)));
    }
    for (int i10{scalarLB}; i10 < g_loop_ub; i10++) {
        u_vec_tilda[i10] = curv->a_param * u_vec[i10] + curv->b_param;
    }
    // 'EvalCurvStructNoCtx:37' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:38' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:39' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:40' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:41' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:43' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line: {
        int r0D_idx_0;
        // 'EvalCurvStructNoCtx:44' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:45' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size, b_r0D, r1D,
                 r2D, r3D);
        r0D_idx_0 = b_r0D.size(0);
        r0D.set_size(b_r0D.size(0), 1);
        for (int i11{0}; i11 < r0D_idx_0; i11++) {
            r0D[i11] = b_r0D[i11];
        }
    } break;
    case CurveType_Helix: {
        int tmp_data[3];
        int tmp_size;
        // 'EvalCurvStructNoCtx:46' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:47' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            double dv[3];
            double dv1[3];
            double dv2[3];
            double dv3[3];
            int bb_loop_ub;
            int db_loop_ub;
            int e_scalarLB;
            int e_vectorUB;
            int eb_loop_ub;
            int fb_loop_ub;
            int g_scalarLB;
            int g_vectorUB;
            int gb_loop_ub;
            int h_scalarLB;
            int h_vectorUB;
            int i_scalarLB;
            int i_vectorUB;
            int m_loop_ub;
            int q_loop_ub;
            int v_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:48' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:49'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                      u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            e_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            e_vectorUB = e_scalarLB - 4;
            for (int i18{0}; i18 <= e_vectorUB; i18 += 4) {
                _mm_storeu_si128((__m128i *)&tmp_data[i18],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i18]),
                                               _mm_set1_epi32(1)));
            }
            for (int i18{e_scalarLB}; i18 < m_loop_ub; i18++) {
                tmp_data[i18] = cfg_indCart[i18] - 1;
            }
            q_loop_ub = u_vec.size(0);
            for (int i21{0}; i21 < q_loop_ub; i21++) {
                for (int i24{0}; i24 < tmp_size; i24++) {
                    r0D[tmp_data[i24] + r0D.size(0) * i21] = dv[i24 + tmp_size * i21];
                }
            }
            tmp_size = cfg_indCart.size(0);
            v_loop_ub = cfg_indCart.size(0);
            g_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            g_vectorUB = g_scalarLB - 4;
            for (int i29{0}; i29 <= g_vectorUB; i29 += 4) {
                _mm_storeu_si128((__m128i *)&tmp_data[i29],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i29]),
                                               _mm_set1_epi32(1)));
            }
            for (int i29{g_scalarLB}; i29 < v_loop_ub; i29++) {
                tmp_data[i29] = cfg_indCart[i29] - 1;
            }
            bb_loop_ub = u_vec.size(0);
            for (int i35{0}; i35 < bb_loop_ub; i35++) {
                for (int i36{0}; i36 < tmp_size; i36++) {
                    r1D[tmp_data[i36] + r1D.size(0) * i35] = dv1[i36 + tmp_size * i35];
                }
            }
            tmp_size = cfg_indCart.size(0);
            db_loop_ub = cfg_indCart.size(0);
            h_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            h_vectorUB = h_scalarLB - 4;
            for (int i40{0}; i40 <= h_vectorUB; i40 += 4) {
                _mm_storeu_si128((__m128i *)&tmp_data[i40],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i40]),
                                               _mm_set1_epi32(1)));
            }
            for (int i40{h_scalarLB}; i40 < db_loop_ub; i40++) {
                tmp_data[i40] = cfg_indCart[i40] - 1;
            }
            eb_loop_ub = u_vec.size(0);
            for (int i41{0}; i41 < eb_loop_ub; i41++) {
                for (int i42{0}; i42 < tmp_size; i42++) {
                    r2D[tmp_data[i42] + r2D.size(0) * i41] = dv2[i42 + tmp_size * i41];
                }
            }
            tmp_size = cfg_indCart.size(0);
            fb_loop_ub = cfg_indCart.size(0);
            i_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            i_vectorUB = i_scalarLB - 4;
            for (int i43{0}; i43 <= i_vectorUB; i43 += 4) {
                _mm_storeu_si128((__m128i *)&tmp_data[i43],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i43]),
                                               _mm_set1_epi32(1)));
            }
            for (int i43{i_scalarLB}; i43 < fb_loop_ub; i43++) {
                tmp_data[i43] = cfg_indCart[i43] - 1;
            }
            gb_loop_ub = u_vec.size(0);
            for (int i44{0}; i44 < gb_loop_ub; i44++) {
                for (int i45{0}; i45 < tmp_size; i45++) {
                    r3D[tmp_data[i45] + r3D.size(0) * i44] = dv3[i45 + tmp_size * i44];
                }
            }
        }
        // 'EvalCurvStructNoCtx:51' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int c_scalarLB;
            int c_vectorUB;
            int k_loop_ub;
            int p_loop_ub;
            int r_loop_ub;
            int t_loop_ub;
            int w_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:52' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:53'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size, r, r1, r2,
                     r3);
            tmp_size = cfg_indRot.size(0);
            k_loop_ub = cfg_indRot.size(0);
            c_scalarLB = (cfg_indRot.size(0) / 4) << 2;
            c_vectorUB = c_scalarLB - 4;
            for (int i15{0}; i15 <= c_vectorUB; i15 += 4) {
                _mm_storeu_si128((__m128i *)&tmp_data[i15],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indRot[i15]),
                                               _mm_set1_epi32(1)));
            }
            for (int i15{c_scalarLB}; i15 < k_loop_ub; i15++) {
                tmp_data[i15] = cfg_indRot[i15] - 1;
            }
            p_loop_ub = r0D.size(1);
            for (int i19{0}; i19 < p_loop_ub; i19++) {
                for (int i22{0}; i22 < tmp_size; i22++) {
                    r0D[tmp_data[i22] + r0D.size(0) * i19] = r[i22 + tmp_size * i19];
                }
            }
            r_loop_ub = r1.size(1);
            for (int i23{0}; i23 < r_loop_ub; i23++) {
                int u_loop_ub;
                u_loop_ub = r1.size(0);
                for (int i27{0}; i27 < u_loop_ub; i27++) {
                    r1D[(cfg_indRot[i27] + r1D.size(0) * i23) - 1] = r1[i27 + r1.size(0) * i23];
                }
            }
            t_loop_ub = r2.size(1);
            for (int i26{0}; i26 < t_loop_ub; i26++) {
                int x_loop_ub;
                x_loop_ub = r2.size(0);
                for (int i31{0}; i31 < x_loop_ub; i31++) {
                    r2D[(cfg_indRot[i31] + r2D.size(0) * i26) - 1] = r2[i31 + r2.size(0) * i26];
                }
            }
            w_loop_ub = r3.size(1);
            for (int i30{0}; i30 < w_loop_ub; i30++) {
                int ab_loop_ub;
                ab_loop_ub = r3.size(0);
                for (int i33{0}; i33 < ab_loop_ub; i33++) {
                    r3D[(cfg_indRot[i33] + r3D.size(0) * i30) - 1] = r3[i33 + r3.size(0) * i30];
                }
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:55' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:56' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // maskTot );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size, r0D, r1D, r2D,
                    r3D);
        break;
    case CurveType_Spline: {
        int cb_loop_ub;
        int i39;
        int s_loop_ub;
        int unnamed_idx_0;
        int y_loop_ub;
        // 'EvalCurvStructNoCtx:57' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:58' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        //  EvalBSpline
        //
        //  Inputs :
        //  spline        : struct : Spline structure
        //  u_vec         :    1xn : Vector for evaluation of the curv
        //
        //  Outputs:
        //  r0D           :   nDxn : The evaluated B spline at u_vec points
        //  r1D           :   nDxn : 1rst order parametric derivative for the Bspline
        //                    at u_vec points
        //  r2D           :   nDxn : 2nd order parametric derivative for the Bspline
        //                    at u_vec points
        //  r3D           :   nDxn : 3rd order parametric derivative for the B spline
        //                    at u_vec points
        //
        // 'EvalBSpline:19' sp  = spline.sp;
        // 'EvalBSpline:20' N   = length( u_vec );
        // 'EvalBSpline:21' M   = size( sp.coeff, 1 );
        // 'EvalBSpline:22' r0D = zeros( M, N );
        unnamed_idx_0 = spline->sp.coeff.size(0);
        // 'EvalBSpline:22' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(0));
        s_loop_ub = u_vec_tilda.size(0);
        for (int i25{0}; i25 < s_loop_ub; i25++) {
            for (int i28{0}; i28 < unnamed_idx_0; i28++) {
                r1D[i28 + r1D.size(0) * i25] = 0.0;
            }
        }
        // 'EvalBSpline:22' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(0));
        y_loop_ub = u_vec_tilda.size(0);
        for (int i32{0}; i32 < y_loop_ub; i32++) {
            for (int i34{0}; i34 < unnamed_idx_0; i34++) {
                r2D[i34 + r2D.size(0) * i32] = 0.0;
            }
        }
        // 'EvalBSpline:22' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(0));
        cb_loop_ub = u_vec_tilda.size(0);
        for (int i37{0}; i37 < cb_loop_ub; i37++) {
            for (int i38{0}; i38 < unnamed_idx_0; i38++) {
                r3D[i38 + r3D.size(0) * i37] = 0.0;
            }
        }
        // 'EvalBSpline:24' for j = 1 : M
        i39 = spline->sp.coeff.size(0);
        r0D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(0));
        for (int j{0}; j < i39; j++) {
            int hb_loop_ub;
            int i50;
            int ib_loop_ub;
            int jb_loop_ub;
            int kb_loop_ub;
            int lb_loop_ub;
            int nb_loop_ub;
            int ob_loop_ub;
            int pb_loop_ub;
            // 'EvalBSpline:25' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:26'                         bspline_eval_vec( sp.Bl, sp.coeff( j, : ),
            // u_vec );
            //  bspline_eval_vec  : Eval Bspline bases for a given set of u value.
            //
            //  Inputs    :
            //  Bl            : BSpline bases
            //  coeffs        : BSpline coefficients
            //  uVec          : U vector of points to evaluate
            //
            //  Outputs   :
            //  x             : Evaluation of the BSpline
            //  xd            : Evaluation of the first derivative of the BSpline
            //  xdd           : Evaluation of the second derivative of the BSpline
            //  xddd          : Evaluation of the third derivative of the BSpline
            //
            // 'bspline_eval_vec:15' x       = zeros(size(uVec));
            r.set_size(u_vec_tilda.size(0));
            hb_loop_ub = u_vec_tilda.size(0);
            for (int i46{0}; i46 < hb_loop_ub; i46++) {
                r[i46] = 0.0;
            }
            // 'bspline_eval_vec:16' xd      = zeros(size(uVec));
            r7.set_size(u_vec_tilda.size(0));
            ib_loop_ub = u_vec_tilda.size(0);
            for (int i47{0}; i47 < ib_loop_ub; i47++) {
                r7[i47] = 0.0;
            }
            // 'bspline_eval_vec:17' xdd     = zeros(size(uVec));
            r8.set_size(u_vec_tilda.size(0));
            jb_loop_ub = u_vec_tilda.size(0);
            for (int i48{0}; i48 < jb_loop_ub; i48++) {
                r8[i48] = 0.0;
            }
            // 'bspline_eval_vec:18' xddd    = zeros(size(uVec));
            r9.set_size(u_vec_tilda.size(0));
            kb_loop_ub = u_vec_tilda.size(0);
            for (int i49{0}; i49 < kb_loop_ub; i49++) {
                r9[i49] = 0.0;
            }
            // 'bspline_eval_vec:20' for k = 1:length(uVec)
            i50 = u_vec_tilda.size(0);
            for (int c_k{0}; c_k < i50; c_k++) {
                int mb_loop_ub;
                // 'bspline_eval_vec:21' [xk, xdk, xddk, xdddk] = bspline_eval( Bl, coeffs, uVec( k
                // ) );
                r[c_k] = u_vec_tilda[c_k];
                mb_loop_ub = spline->sp.coeff.size(1);
                b_spline.set_size(1, spline->sp.coeff.size(1));
                for (int i53{0}; i53 < mb_loop_ub; i53++) {
                    b_spline[i53] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i53];
                }
                bspline_eval(spline->sp.Bl.handle, b_spline, &r[c_k], &d, &d1, &d2);
                r9[c_k] = d2;
                r8[c_k] = d1;
                r7[c_k] = d;
                // 'bspline_eval_vec:22' x(k)    = xk;
                // 'bspline_eval_vec:23' xd(k)   = xdk;
                // 'bspline_eval_vec:24' xdd(k)  = xddk;
                // 'bspline_eval_vec:25' xddd(k) = xdddk;
            }
            lb_loop_ub = r0D.size(1);
            for (int i51{0}; i51 < lb_loop_ub; i51++) {
                r0D[j + r0D.size(0) * i51] = r[i51];
            }
            nb_loop_ub = r1D.size(1);
            for (int i52{0}; i52 < nb_loop_ub; i52++) {
                r1D[j + r1D.size(0) * i52] = r7[i52];
            }
            ob_loop_ub = r2D.size(1);
            for (int i54{0}; i54 < ob_loop_ub; i54++) {
                r2D[j + r2D.size(0) * i54] = r8[i54];
            }
            pb_loop_ub = r3D.size(1);
            for (int i55{0}; i55 < pb_loop_ub; i55++) {
                r3D[j + r3D.size(0) * i55] = r9[i55];
            }
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:59' otherwise
        // 'EvalCurvStructNoCtx:60' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        qb_ocn_assert();
        break;
    }
    // 'EvalCurvStructNoCtx:63' if( 1 )
    // 'EvalCurvStructNoCtx:64' r1D = a     .* r1D;
    h_loop_ub = r1D.size(1);
    for (int i12{0}; i12 < h_loop_ub; i12++) {
        int b_scalarLB;
        int b_vectorUB;
        int i_loop_ub;
        i_loop_ub = r1D.size(0);
        b_scalarLB = (r1D.size(0) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i14{0}; i14 <= b_vectorUB; i14 += 2) {
            __m128d r4;
            r4 = _mm_loadu_pd(&r1D[i14 + r1D.size(0) * i12]);
            _mm_storeu_pd(&r1D[i14 + r1D.size(0) * i12],
                          _mm_mul_pd(_mm_set1_pd(curv->a_param), r4));
        }
        for (int i14{b_scalarLB}; i14 < i_loop_ub; i14++) {
            r1D[i14 + r1D.size(0) * i12] = curv->a_param * r1D[i14 + r1D.size(0) * i12];
        }
    }
    // 'EvalCurvStructNoCtx:65' r2D = a^2   .* r2D;
    c = curv->a_param * curv->a_param;
    j_loop_ub = r2D.size(1);
    for (int i13{0}; i13 < j_loop_ub; i13++) {
        int d_scalarLB;
        int d_vectorUB;
        int l_loop_ub;
        l_loop_ub = r2D.size(0);
        d_scalarLB = (r2D.size(0) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (int i17{0}; i17 <= d_vectorUB; i17 += 2) {
            __m128d r5;
            r5 = _mm_loadu_pd(&r2D[i17 + r2D.size(0) * i13]);
            _mm_storeu_pd(&r2D[i17 + r2D.size(0) * i13], _mm_mul_pd(_mm_set1_pd(c), r5));
        }
        for (int i17{d_scalarLB}; i17 < l_loop_ub; i17++) {
            r2D[i17 + r2D.size(0) * i13] = c * r2D[i17 + r2D.size(0) * i13];
        }
    }
    // 'EvalCurvStructNoCtx:66' r3D = a^3   .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    n_loop_ub = r3D.size(1);
    for (int i16{0}; i16 < n_loop_ub; i16++) {
        int f_scalarLB;
        int f_vectorUB;
        int o_loop_ub;
        o_loop_ub = r3D.size(0);
        f_scalarLB = (r3D.size(0) / 2) << 1;
        f_vectorUB = f_scalarLB - 2;
        for (int i20{0}; i20 <= f_vectorUB; i20 += 2) {
            __m128d r6;
            r6 = _mm_loadu_pd(&r3D[i20 + r3D.size(0) * i16]);
            _mm_storeu_pd(&r3D[i20 + r3D.size(0) * i16], _mm_mul_pd(_mm_set1_pd(b_c), r6));
        }
        for (int i20{f_scalarLB}; i20 < o_loop_ub; i20++) {
            r3D[i20 + r3D.size(0) * i16] = b_c * r3D[i20 + r3D.size(0) * i16];
        }
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
// EvalCurvStructNoCtx : Eval curve structure and its derivatives on
//  a set of u points without any need of the context structure.
//
//  Inputs :
//  cfg       : The configuration structure of the computational chain
//  curv      : The curve used in the evaluation
//  spline    : The required spline for the evaluation
//  u_vec     : U vectors
//
//  Outputs :
//  r0D   : Matrix of points for a given set of u values
//  r1D   : Matrix of points (first derivative) for a given set of u values
//  r2D   : Matrix of points (second derivative) for a given set of u values
//  r3D   : Matrix of points (third derivative) for a given set of u values
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
    double r2D_data[6];
    double r3D_data[6];
    double tmp_data[6];
    double d;
    double d1;
    double d2;
    double u_vec_tilda;
    int b_tmp_size;
    int i1;
    int r1D_size;
    int r2D_size;
    int r3D_size;
    int tmp_size;
    // 'EvalCurvStructNoCtx:18' coder.inline("never");
    // 'EvalCurvStructNoCtx:20' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    c_ocn_assert(u_vec <= 1.0);
    // 'EvalCurvStructNoCtx:21' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    d_ocn_assert(u_vec >= 0.0);
    //
    // 'EvalCurvStructNoCtx:24' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:26' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:27' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:29' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:30' r1D = r0D;
    // 'EvalCurvStructNoCtx:30' r2D = r0D;
    // 'EvalCurvStructNoCtx:30' r3D = r0D;
    // 'EvalCurvStructNoCtx:32' a = curv.a_param;
    // 'EvalCurvStructNoCtx:33' b = curv.b_param;
    // 'EvalCurvStructNoCtx:35' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv->a_param * u_vec + curv->b_param;
    // 'EvalCurvStructNoCtx:37' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:38' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:39' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:40' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:41' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:43' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:44' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:45' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(6);
        b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), &(*(int(*)[1])r0D.size())[0], r1D_data, &r1D_size, r2D,
                   r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:46' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:47' if( cfg.NCart > 0 )
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
            // 'EvalCurvStructNoCtx:48' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:49'                 EvalHelix( curv, u_vec_tilda,
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
            for (int i4{0}; i4 < c_tmp_size; i4++) {
                r0D[c_tmp_data[i4]] = dv[i4];
            }
        }
        // 'EvalCurvStructNoCtx:51' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            //  Rotative axis
            // 'EvalCurvStructNoCtx:52' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:53'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, &tmp_size, b_tmp_data, &b_tmp_size, r, r1);
            for (int i2{0}; i2 < tmp_size; i2++) {
                r0D[cfg_indRot[i2] - 1] = tmp_data[i2];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:55' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:56' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // maskTot );
        r0D.reserve(6);
        b_EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                      (double *)r0D.data(), &i1, r1D_data, &r1D_size, r2D_data, &r2D_size, r3D_data,
                      &r3D_size);
        (*(int(*)[1])r0D.size())[0] = i1;
        break;
    case CurveType_Spline: {
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int i9;
        // 'EvalCurvStructNoCtx:57' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:58' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        //  EvalBSpline
        //
        //  Inputs :
        //  spline        : struct : Spline structure
        //  u_vec         :    1xn : Vector for evaluation of the curv
        //
        //  Outputs:
        //  r0D           :   nDxn : The evaluated B spline at u_vec points
        //  r1D           :   nDxn : 1rst order parametric derivative for the Bspline
        //                    at u_vec points
        //  r2D           :   nDxn : 2nd order parametric derivative for the Bspline
        //                    at u_vec points
        //  r3D           :   nDxn : 3rd order parametric derivative for the B spline
        //                    at u_vec points
        //
        // 'EvalBSpline:19' sp  = spline.sp;
        // 'EvalBSpline:20' N   = length( u_vec );
        // 'EvalBSpline:21' M   = size( sp.coeff, 1 );
        // 'EvalBSpline:22' r0D = zeros( M, N );
        r0D.set_size(spline->sp.coeff.size(0));
        b_loop_ub = spline->sp.coeff.size(0);
        for (int i5{0}; i5 < b_loop_ub; i5++) {
            r0D[i5] = 0.0;
        }
        // 'EvalBSpline:22' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        c_loop_ub = spline->sp.coeff.size(0);
        for (int i6{0}; i6 < c_loop_ub; i6++) {
            r1D[i6] = 0.0;
        }
        // 'EvalBSpline:22' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        d_loop_ub = spline->sp.coeff.size(0);
        for (int i7{0}; i7 < d_loop_ub; i7++) {
            r2D[i7] = 0.0;
        }
        // 'EvalBSpline:22' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        e_loop_ub = spline->sp.coeff.size(0);
        for (int i8{0}; i8 < e_loop_ub; i8++) {
            r3D[i8] = 0.0;
        }
        // 'EvalBSpline:24' for j = 1 : M
        i9 = spline->sp.coeff.size(0);
        for (int j{0}; j < i9; j++) {
            int f_loop_ub;
            // 'EvalBSpline:25' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:26'                         bspline_eval_vec( sp.Bl, sp.coeff( j, : ),
            // u_vec );
            //  bspline_eval_vec  : Eval Bspline bases for a given set of u value.
            //
            //  Inputs    :
            //  Bl            : BSpline bases
            //  coeffs        : BSpline coefficients
            //  uVec          : U vector of points to evaluate
            //
            //  Outputs   :
            //  x             : Evaluation of the BSpline
            //  xd            : Evaluation of the first derivative of the BSpline
            //  xdd           : Evaluation of the second derivative of the BSpline
            //  xddd          : Evaluation of the third derivative of the BSpline
            //
            // 'bspline_eval_vec:15' x       = zeros(size(uVec));
            // 'bspline_eval_vec:16' xd      = zeros(size(uVec));
            // 'bspline_eval_vec:17' xdd     = zeros(size(uVec));
            // 'bspline_eval_vec:18' xddd    = zeros(size(uVec));
            // 'bspline_eval_vec:20' for k = 1:length(uVec)
            // 'bspline_eval_vec:21' [xk, xdk, xddk, xdddk] = bspline_eval( Bl, coeffs, uVec( k ) );
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
            // 'bspline_eval_vec:22' x(k)    = xk;
            // 'bspline_eval_vec:23' xd(k)   = xdk;
            // 'bspline_eval_vec:24' xdd(k)  = xddk;
            // 'bspline_eval_vec:25' xddd(k) = xdddk;
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:59' otherwise
        // 'EvalCurvStructNoCtx:60' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        qb_ocn_assert();
        break;
    }
    // 'EvalCurvStructNoCtx:63' if( 1 )
    // 'EvalCurvStructNoCtx:64' r1D = a     .* r1D;
    // 'EvalCurvStructNoCtx:65' r2D = a^2   .* r2D;
    // 'EvalCurvStructNoCtx:66' r3D = a^3   .* r3D;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
// EvalCurvStructNoCtx : Eval curve structure and its derivatives on
//  a set of u points without any need of the context structure.
//
//  Inputs :
//  cfg       : The configuration structure of the computational chain
//  curv      : The curve used in the evaluation
//  spline    : The required spline for the evaluation
//  u_vec     : U vectors
//
//  Outputs :
//  r0D   : Matrix of points for a given set of u values
//  r1D   : Matrix of points (first derivative) for a given set of u values
//  r2D   : Matrix of points (second derivative) for a given set of u values
//  r3D   : Matrix of points (third derivative) for a given set of u values
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
    int c_loop_ub;
    int c_scalarLB;
    int c_vectorUB;
    int d_scalarLB;
    int d_vectorUB;
    int g_loop_ub;
    int i1;
    int i2;
    int i4;
    int i5;
    int loop_ub;
    int scalarLB;
    int tmp_size;
    int vectorUB;
    // 'EvalCurvStructNoCtx:18' coder.inline("never");
    // 'EvalCurvStructNoCtx:20' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    c_ocn_assert(true);
    // 'EvalCurvStructNoCtx:21' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    d_ocn_assert(true);
    //
    // 'EvalCurvStructNoCtx:24' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:26' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:27' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:29' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:30' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:30' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:30' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:32' a = curv.a_param;
    // 'EvalCurvStructNoCtx:33' b = curv.b_param;
    // 'EvalCurvStructNoCtx:35' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv->a_param + curv->b_param;
    // 'EvalCurvStructNoCtx:37' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:38' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:39' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:40' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:41' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:43' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:44' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:45' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(6);
        r1D.reserve(6);
        b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), &(*(int(*)[1])r0D.size())[0], (double *)r1D.data(),
                   &(*(int(*)[1])r1D.size())[0], r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:46' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:47' if( cfg.NCart > 0 )
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
            int h_loop_ub;
            int k_loop_ub;
            int m_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:48' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:49'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            b_loop_ub = cfg_indCart.size(0);
            b_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            b_vectorUB = b_scalarLB - 4;
            for (int i9{0}; i9 <= b_vectorUB; i9 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i9],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i9]),
                                               _mm_set1_epi32(1)));
            }
            for (int i9{b_scalarLB}; i9 < b_loop_ub; i9++) {
                c_tmp_data[i9] = cfg_indCart[i9] - 1;
            }
            for (int i12{0}; i12 < c_tmp_size; i12++) {
                r0D[c_tmp_data[i12]] = dv[i12];
            }
            c_tmp_size = cfg_indCart.size(0);
            h_loop_ub = cfg_indCart.size(0);
            e_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            e_vectorUB = e_scalarLB - 4;
            for (int i15{0}; i15 <= e_vectorUB; i15 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i15],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i15]),
                                               _mm_set1_epi32(1)));
            }
            for (int i15{e_scalarLB}; i15 < h_loop_ub; i15++) {
                c_tmp_data[i15] = cfg_indCart[i15] - 1;
            }
            for (int i17{0}; i17 < c_tmp_size; i17++) {
                r1D[c_tmp_data[i17]] = dv1[i17];
            }
            c_tmp_size = cfg_indCart.size(0);
            k_loop_ub = cfg_indCart.size(0);
            f_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            f_vectorUB = f_scalarLB - 4;
            for (int i19{0}; i19 <= f_vectorUB; i19 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i19],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i19]),
                                               _mm_set1_epi32(1)));
            }
            for (int i19{f_scalarLB}; i19 < k_loop_ub; i19++) {
                c_tmp_data[i19] = cfg_indCart[i19] - 1;
            }
            for (int i22{0}; i22 < c_tmp_size; i22++) {
                r2D[c_tmp_data[i22]] = dv2[i22];
            }
            c_tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            g_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            g_vectorUB = g_scalarLB - 4;
            for (int i23{0}; i23 <= g_vectorUB; i23 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i23],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i23]),
                                               _mm_set1_epi32(1)));
            }
            for (int i23{g_scalarLB}; i23 < m_loop_ub; i23++) {
                c_tmp_data[i23] = cfg_indCart[i23] - 1;
            }
            for (int i24{0}; i24 < c_tmp_size; i24++) {
                r3D[c_tmp_data[i24]] = dv3[i24];
            }
        }
        // 'EvalCurvStructNoCtx:51' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int d_loop_ub;
            int e_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:52' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:53'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, &tmp_size, b_tmp_data, &b_tmp_size, r, r1);
            for (int i6{0}; i6 < tmp_size; i6++) {
                r0D[cfg_indRot[i6] - 1] = tmp_data[i6];
            }
            for (int i7{0}; i7 < b_tmp_size; i7++) {
                r1D[cfg_indRot[i7] - 1] = b_tmp_data[i7];
            }
            d_loop_ub = r.size(0);
            for (int i8{0}; i8 < d_loop_ub; i8++) {
                r2D[cfg_indRot[i8] - 1] = r[i8];
            }
            e_loop_ub = r1.size(0);
            for (int i11{0}; i11 < e_loop_ub; i11++) {
                r3D[cfg_indRot[i11] - 1] = r1[i11];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:55' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:56' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // maskTot );
        r0D.reserve(6);
        r1D.reserve(6);
        r2D.reserve(6);
        r3D.reserve(6);
        b_EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                      (double *)r0D.data(), &i1, (double *)r1D.data(), &i2, (double *)r2D.data(),
                      &i4, (double *)r3D.data(), &i5);
        (*(int(*)[1])r3D.size())[0] = i5;
        (*(int(*)[1])r2D.size())[0] = i4;
        (*(int(*)[1])r1D.size())[0] = i2;
        (*(int(*)[1])r0D.size())[0] = i1;
        break;
    case CurveType_Spline: {
        int f_loop_ub;
        int i21;
        int i_loop_ub;
        int j_loop_ub;
        int l_loop_ub;
        // 'EvalCurvStructNoCtx:57' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:58' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        //  EvalBSpline
        //
        //  Inputs :
        //  spline        : struct : Spline structure
        //  u_vec         :    1xn : Vector for evaluation of the curv
        //
        //  Outputs:
        //  r0D           :   nDxn : The evaluated B spline at u_vec points
        //  r1D           :   nDxn : 1rst order parametric derivative for the Bspline
        //                    at u_vec points
        //  r2D           :   nDxn : 2nd order parametric derivative for the Bspline
        //                    at u_vec points
        //  r3D           :   nDxn : 3rd order parametric derivative for the B spline
        //                    at u_vec points
        //
        // 'EvalBSpline:19' sp  = spline.sp;
        // 'EvalBSpline:20' N   = length( u_vec );
        // 'EvalBSpline:21' M   = size( sp.coeff, 1 );
        // 'EvalBSpline:22' r0D = zeros( M, N );
        r0D.set_size(spline->sp.coeff.size(0));
        f_loop_ub = spline->sp.coeff.size(0);
        for (int i13{0}; i13 < f_loop_ub; i13++) {
            r0D[i13] = 0.0;
        }
        // 'EvalBSpline:22' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        i_loop_ub = spline->sp.coeff.size(0);
        for (int i16{0}; i16 < i_loop_ub; i16++) {
            r1D[i16] = 0.0;
        }
        // 'EvalBSpline:22' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        j_loop_ub = spline->sp.coeff.size(0);
        for (int i18{0}; i18 < j_loop_ub; i18++) {
            r2D[i18] = 0.0;
        }
        // 'EvalBSpline:22' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        l_loop_ub = spline->sp.coeff.size(0);
        for (int i20{0}; i20 < l_loop_ub; i20++) {
            r3D[i20] = 0.0;
        }
        // 'EvalBSpline:24' for j = 1 : M
        i21 = spline->sp.coeff.size(0);
        for (int j{0}; j < i21; j++) {
            int n_loop_ub;
            // 'EvalBSpline:25' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:26'                         bspline_eval_vec( sp.Bl, sp.coeff( j, : ),
            // u_vec );
            //  bspline_eval_vec  : Eval Bspline bases for a given set of u value.
            //
            //  Inputs    :
            //  Bl            : BSpline bases
            //  coeffs        : BSpline coefficients
            //  uVec          : U vector of points to evaluate
            //
            //  Outputs   :
            //  x             : Evaluation of the BSpline
            //  xd            : Evaluation of the first derivative of the BSpline
            //  xdd           : Evaluation of the second derivative of the BSpline
            //  xddd          : Evaluation of the third derivative of the BSpline
            //
            // 'bspline_eval_vec:15' x       = zeros(size(uVec));
            // 'bspline_eval_vec:16' xd      = zeros(size(uVec));
            // 'bspline_eval_vec:17' xdd     = zeros(size(uVec));
            // 'bspline_eval_vec:18' xddd    = zeros(size(uVec));
            // 'bspline_eval_vec:20' for k = 1:length(uVec)
            // 'bspline_eval_vec:21' [xk, xdk, xddk, xdddk] = bspline_eval( Bl, coeffs, uVec( k ) );
            r0D[j] = u_vec_tilda;
            n_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i25{0}; i25 < n_loop_ub; i25++) {
                b_spline[i25] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i25];
            }
            bspline_eval(spline->sp.Bl.handle, b_spline, &r0D[j], &d, &d1, &d2);
            r3D[j] = d2;
            r2D[j] = d1;
            r1D[j] = d;
            // 'bspline_eval_vec:22' x(k)    = xk;
            // 'bspline_eval_vec:23' xd(k)   = xdk;
            // 'bspline_eval_vec:24' xdd(k)  = xddk;
            // 'bspline_eval_vec:25' xddd(k) = xdddk;
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:59' otherwise
        // 'EvalCurvStructNoCtx:60' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        qb_ocn_assert();
        break;
    }
    // 'EvalCurvStructNoCtx:63' if( 1 )
    // 'EvalCurvStructNoCtx:64' r1D = a     .* r1D;
    loop_ub = r1D.size(0);
    scalarLB = (r1D.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i3{0}; i3 <= vectorUB; i3 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r1D[i3]);
        _mm_storeu_pd(&r1D[i3], _mm_mul_pd(_mm_set1_pd(curv->a_param), r2));
    }
    for (int i3{scalarLB}; i3 < loop_ub; i3++) {
        r1D[i3] = curv->a_param * r1D[i3];
    }
    // 'EvalCurvStructNoCtx:65' r2D = a^2   .* r2D;
    c = curv->a_param * curv->a_param;
    c_loop_ub = r2D.size(0);
    c_scalarLB = (r2D.size(0) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (int i10{0}; i10 <= c_vectorUB; i10 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&r2D[i10]);
        _mm_storeu_pd(&r2D[i10], _mm_mul_pd(_mm_set1_pd(c), r3));
    }
    for (int i10{c_scalarLB}; i10 < c_loop_ub; i10++) {
        r2D[i10] = c * r2D[i10];
    }
    // 'EvalCurvStructNoCtx:66' r3D = a^3   .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    g_loop_ub = r3D.size(0);
    d_scalarLB = (r3D.size(0) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i14{0}; i14 <= d_vectorUB; i14 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r3D[i14]);
        _mm_storeu_pd(&r3D[i14], _mm_mul_pd(_mm_set1_pd(b_c), r4));
    }
    for (int i14{d_scalarLB}; i14 < g_loop_ub; i14++) {
        r3D[i14] = b_c * r3D[i14];
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
// EvalCurvStructNoCtx : Eval curve structure and its derivatives on
//  a set of u points without any need of the context structure.
//
//  Inputs :
//  cfg       : The configuration structure of the computational chain
//  curv      : The curve used in the evaluation
//  spline    : The required spline for the evaluation
//  u_vec     : U vectors
//
//  Outputs :
//  r0D   : Matrix of points for a given set of u values
//  r1D   : Matrix of points (first derivative) for a given set of u values
//  r2D   : Matrix of points (second derivative) for a given set of u values
//  r3D   : Matrix of points (third derivative) for a given set of u values
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
    int c_loop_ub;
    int c_scalarLB;
    int c_vectorUB;
    int d_scalarLB;
    int d_vectorUB;
    int g_loop_ub;
    int i1;
    int i2;
    int i4;
    int i5;
    int loop_ub;
    int scalarLB;
    int tmp_size;
    int vectorUB;
    // 'EvalCurvStructNoCtx:18' coder.inline("never");
    // 'EvalCurvStructNoCtx:20' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    c_ocn_assert(true);
    // 'EvalCurvStructNoCtx:21' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    d_ocn_assert(true);
    //
    // 'EvalCurvStructNoCtx:24' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:26' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:27' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:29' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:30' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:30' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:30' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:32' a = curv.a_param;
    // 'EvalCurvStructNoCtx:33' b = curv.b_param;
    // 'EvalCurvStructNoCtx:35' u_vec_tilda = a * u_vec + b;
    // 'EvalCurvStructNoCtx:37' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:38' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:39' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:40' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:41' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:43' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:44' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:45' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(6);
        r1D.reserve(6);
        b_EvalLine(curv->R0, curv->R1, curv->b_param, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), &(*(int(*)[1])r0D.size())[0], (double *)r1D.data(),
                   &(*(int(*)[1])r1D.size())[0], r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:46' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:47' if( cfg.NCart > 0 )
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
            int h_loop_ub;
            int k_loop_ub;
            int m_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:48' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:49'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        curv->b_param, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            b_loop_ub = cfg_indCart.size(0);
            b_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            b_vectorUB = b_scalarLB - 4;
            for (int i9{0}; i9 <= b_vectorUB; i9 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i9],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i9]),
                                               _mm_set1_epi32(1)));
            }
            for (int i9{b_scalarLB}; i9 < b_loop_ub; i9++) {
                c_tmp_data[i9] = cfg_indCart[i9] - 1;
            }
            for (int i12{0}; i12 < c_tmp_size; i12++) {
                r0D[c_tmp_data[i12]] = dv[i12];
            }
            c_tmp_size = cfg_indCart.size(0);
            h_loop_ub = cfg_indCart.size(0);
            e_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            e_vectorUB = e_scalarLB - 4;
            for (int i15{0}; i15 <= e_vectorUB; i15 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i15],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i15]),
                                               _mm_set1_epi32(1)));
            }
            for (int i15{e_scalarLB}; i15 < h_loop_ub; i15++) {
                c_tmp_data[i15] = cfg_indCart[i15] - 1;
            }
            for (int i17{0}; i17 < c_tmp_size; i17++) {
                r1D[c_tmp_data[i17]] = dv1[i17];
            }
            c_tmp_size = cfg_indCart.size(0);
            k_loop_ub = cfg_indCart.size(0);
            f_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            f_vectorUB = f_scalarLB - 4;
            for (int i19{0}; i19 <= f_vectorUB; i19 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i19],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i19]),
                                               _mm_set1_epi32(1)));
            }
            for (int i19{f_scalarLB}; i19 < k_loop_ub; i19++) {
                c_tmp_data[i19] = cfg_indCart[i19] - 1;
            }
            for (int i22{0}; i22 < c_tmp_size; i22++) {
                r2D[c_tmp_data[i22]] = dv2[i22];
            }
            c_tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            g_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            g_vectorUB = g_scalarLB - 4;
            for (int i23{0}; i23 <= g_vectorUB; i23 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i23],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i23]),
                                               _mm_set1_epi32(1)));
            }
            for (int i23{g_scalarLB}; i23 < m_loop_ub; i23++) {
                c_tmp_data[i23] = cfg_indCart[i23] - 1;
            }
            for (int i24{0}; i24 < c_tmp_size; i24++) {
                r3D[c_tmp_data[i24]] = dv3[i24];
            }
        }
        // 'EvalCurvStructNoCtx:51' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int d_loop_ub;
            int e_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:52' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:53'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, curv->b_param, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, &tmp_size, b_tmp_data, &b_tmp_size, r, r1);
            for (int i6{0}; i6 < tmp_size; i6++) {
                r0D[cfg_indRot[i6] - 1] = tmp_data[i6];
            }
            for (int i7{0}; i7 < b_tmp_size; i7++) {
                r1D[cfg_indRot[i7] - 1] = b_tmp_data[i7];
            }
            d_loop_ub = r.size(0);
            for (int i8{0}; i8 < d_loop_ub; i8++) {
                r2D[cfg_indRot[i8] - 1] = r[i8];
            }
            e_loop_ub = r1.size(0);
            for (int i11{0}; i11 < e_loop_ub; i11++) {
                r3D[cfg_indRot[i11] - 1] = r1[i11];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:55' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:56' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // maskTot );
        r0D.reserve(6);
        r1D.reserve(6);
        r2D.reserve(6);
        r3D.reserve(6);
        b_EvalTransP5(curv->CoeffP5, curv->b_param, cfg_maskTot_data, cfg_maskTot_size,
                      (double *)r0D.data(), &i1, (double *)r1D.data(), &i2, (double *)r2D.data(),
                      &i4, (double *)r3D.data(), &i5);
        (*(int(*)[1])r3D.size())[0] = i5;
        (*(int(*)[1])r2D.size())[0] = i4;
        (*(int(*)[1])r1D.size())[0] = i2;
        (*(int(*)[1])r0D.size())[0] = i1;
        break;
    case CurveType_Spline: {
        int f_loop_ub;
        int i21;
        int i_loop_ub;
        int j_loop_ub;
        int l_loop_ub;
        // 'EvalCurvStructNoCtx:57' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:58' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        //  EvalBSpline
        //
        //  Inputs :
        //  spline        : struct : Spline structure
        //  u_vec         :    1xn : Vector for evaluation of the curv
        //
        //  Outputs:
        //  r0D           :   nDxn : The evaluated B spline at u_vec points
        //  r1D           :   nDxn : 1rst order parametric derivative for the Bspline
        //                    at u_vec points
        //  r2D           :   nDxn : 2nd order parametric derivative for the Bspline
        //                    at u_vec points
        //  r3D           :   nDxn : 3rd order parametric derivative for the B spline
        //                    at u_vec points
        //
        // 'EvalBSpline:19' sp  = spline.sp;
        // 'EvalBSpline:20' N   = length( u_vec );
        // 'EvalBSpline:21' M   = size( sp.coeff, 1 );
        // 'EvalBSpline:22' r0D = zeros( M, N );
        r0D.set_size(spline->sp.coeff.size(0));
        f_loop_ub = spline->sp.coeff.size(0);
        for (int i13{0}; i13 < f_loop_ub; i13++) {
            r0D[i13] = 0.0;
        }
        // 'EvalBSpline:22' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        i_loop_ub = spline->sp.coeff.size(0);
        for (int i16{0}; i16 < i_loop_ub; i16++) {
            r1D[i16] = 0.0;
        }
        // 'EvalBSpline:22' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        j_loop_ub = spline->sp.coeff.size(0);
        for (int i18{0}; i18 < j_loop_ub; i18++) {
            r2D[i18] = 0.0;
        }
        // 'EvalBSpline:22' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        l_loop_ub = spline->sp.coeff.size(0);
        for (int i20{0}; i20 < l_loop_ub; i20++) {
            r3D[i20] = 0.0;
        }
        // 'EvalBSpline:24' for j = 1 : M
        i21 = spline->sp.coeff.size(0);
        for (int j{0}; j < i21; j++) {
            int n_loop_ub;
            // 'EvalBSpline:25' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:26'                         bspline_eval_vec( sp.Bl, sp.coeff( j, : ),
            // u_vec );
            //  bspline_eval_vec  : Eval Bspline bases for a given set of u value.
            //
            //  Inputs    :
            //  Bl            : BSpline bases
            //  coeffs        : BSpline coefficients
            //  uVec          : U vector of points to evaluate
            //
            //  Outputs   :
            //  x             : Evaluation of the BSpline
            //  xd            : Evaluation of the first derivative of the BSpline
            //  xdd           : Evaluation of the second derivative of the BSpline
            //  xddd          : Evaluation of the third derivative of the BSpline
            //
            // 'bspline_eval_vec:15' x       = zeros(size(uVec));
            // 'bspline_eval_vec:16' xd      = zeros(size(uVec));
            // 'bspline_eval_vec:17' xdd     = zeros(size(uVec));
            // 'bspline_eval_vec:18' xddd    = zeros(size(uVec));
            // 'bspline_eval_vec:20' for k = 1:length(uVec)
            // 'bspline_eval_vec:21' [xk, xdk, xddk, xdddk] = bspline_eval( Bl, coeffs, uVec( k ) );
            r0D[j] = curv->b_param;
            n_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i25{0}; i25 < n_loop_ub; i25++) {
                b_spline[i25] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i25];
            }
            bspline_eval(spline->sp.Bl.handle, b_spline, &r0D[j], &d, &d1, &d2);
            r3D[j] = d2;
            r2D[j] = d1;
            r1D[j] = d;
            // 'bspline_eval_vec:22' x(k)    = xk;
            // 'bspline_eval_vec:23' xd(k)   = xdk;
            // 'bspline_eval_vec:24' xdd(k)  = xddk;
            // 'bspline_eval_vec:25' xddd(k) = xdddk;
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:59' otherwise
        // 'EvalCurvStructNoCtx:60' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        qb_ocn_assert();
        break;
    }
    // 'EvalCurvStructNoCtx:63' if( 1 )
    // 'EvalCurvStructNoCtx:64' r1D = a     .* r1D;
    loop_ub = r1D.size(0);
    scalarLB = (r1D.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i3{0}; i3 <= vectorUB; i3 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r1D[i3]);
        _mm_storeu_pd(&r1D[i3], _mm_mul_pd(_mm_set1_pd(curv->a_param), r2));
    }
    for (int i3{scalarLB}; i3 < loop_ub; i3++) {
        r1D[i3] = curv->a_param * r1D[i3];
    }
    // 'EvalCurvStructNoCtx:65' r2D = a^2   .* r2D;
    c = curv->a_param * curv->a_param;
    c_loop_ub = r2D.size(0);
    c_scalarLB = (r2D.size(0) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (int i10{0}; i10 <= c_vectorUB; i10 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&r2D[i10]);
        _mm_storeu_pd(&r2D[i10], _mm_mul_pd(_mm_set1_pd(c), r3));
    }
    for (int i10{c_scalarLB}; i10 < c_loop_ub; i10++) {
        r2D[i10] = c * r2D[i10];
    }
    // 'EvalCurvStructNoCtx:66' r3D = a^3   .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    g_loop_ub = r3D.size(0);
    d_scalarLB = (r3D.size(0) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i14{0}; i14 <= d_vectorUB; i14 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r3D[i14]);
        _mm_storeu_pd(&r3D[i14], _mm_mul_pd(_mm_set1_pd(b_c), r4));
    }
    for (int i14{d_scalarLB}; i14 < g_loop_ub; i14++) {
        r3D[i14] = b_c * r3D[i14];
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
// EvalCurvStructNoCtx : Eval curve structure and its derivatives on
//  a set of u points without any need of the context structure.
//
//  Inputs :
//  cfg       : The configuration structure of the computational chain
//  curv      : The curve used in the evaluation
//  spline    : The required spline for the evaluation
//  u_vec     : U vectors
//
//  Outputs :
//  r0D   : Matrix of points for a given set of u values
//  r1D   : Matrix of points (first derivative) for a given set of u values
//  r2D   : Matrix of points (second derivative) for a given set of u values
//  r3D   : Matrix of points (third derivative) for a given set of u values
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
    ::coder::array<double, 2U> r11;
    ::coder::array<double, 2U> r12;
    ::coder::array<double, 2U> r13;
    ::coder::array<double, 2U> r14;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> r5;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> r7;
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
    // 'EvalCurvStructNoCtx:18' coder.inline("never");
    // 'EvalCurvStructNoCtx:20' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
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
    c_ocn_assert(!y);
    // 'EvalCurvStructNoCtx:21' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
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
    d_ocn_assert(!b_y);
    //
    // 'EvalCurvStructNoCtx:24' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:26' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:27' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:29' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis, u_vec.size(1));
    c_loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        for (int i3{0}; i3 < cfg_NumberAxis; i3++) {
            r0D[i3 + r0D.size(0) * i2] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:30' r1D = r0D;
    r1D.set_size(cfg_NumberAxis, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        for (int i5{0}; i5 < cfg_NumberAxis; i5++) {
            r1D[i5 + r1D.size(0) * i4] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:30' r2D = r0D;
    r2D.set_size(cfg_NumberAxis, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i6{0}; i6 < e_loop_ub; i6++) {
        for (int i7{0}; i7 < cfg_NumberAxis; i7++) {
            r2D[i7 + r2D.size(0) * i6] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:30' r3D = r0D;
    r3D.set_size(cfg_NumberAxis, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        for (int i9{0}; i9 < cfg_NumberAxis; i9++) {
            r3D[i9 + r3D.size(0) * i8] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:32' a = curv.a_param;
    // 'EvalCurvStructNoCtx:33' b = curv.b_param;
    // 'EvalCurvStructNoCtx:35' u_vec_tilda = a * u_vec + b;
    u_vec_tilda.set_size(1, u_vec.size(1));
    g_loop_ub = u_vec.size(1);
    scalarLB = (u_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i10{0}; i10 <= vectorUB; i10 += 2) {
        _mm_storeu_pd(&u_vec_tilda[i10],
                      _mm_add_pd(_mm_mul_pd(_mm_set1_pd(curv->a_param),
                                            _mm_loadu_pd((const double *)&u_vec[i10])),
                                 _mm_set1_pd(curv->b_param)));
    }
    for (int i10{scalarLB}; i10 < g_loop_ub; i10++) {
        u_vec_tilda[i10] = curv->a_param * u_vec[i10] + curv->b_param;
    }
    // 'EvalCurvStructNoCtx:37' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:38' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:39' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:40' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:41' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:43' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:44' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:45' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        c_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size, r0D, r1D,
                   r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:46' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:47' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int i_loop_ub;
            int m_loop_ub;
            int q_loop_ub;
            int u_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:48' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:49'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            c_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, r, r1, r2, r3);
            i_loop_ub = r.size(1);
            for (int i12{0}; i12 < i_loop_ub; i12++) {
                r0D[(cfg_indCart[0] + r0D.size(0) * i12) - 1] = r[3 * i12];
                r0D[(cfg_indCart[1] + r0D.size(0) * i12) - 1] = r[3 * i12 + 1];
                r0D[(cfg_indCart[2] + r0D.size(0) * i12) - 1] = r[3 * i12 + 2];
            }
            m_loop_ub = r1.size(1);
            for (int i16{0}; i16 < m_loop_ub; i16++) {
                r1D[(cfg_indCart[0] + r1D.size(0) * i16) - 1] = r1[3 * i16];
                r1D[(cfg_indCart[1] + r1D.size(0) * i16) - 1] = r1[3 * i16 + 1];
                r1D[(cfg_indCart[2] + r1D.size(0) * i16) - 1] = r1[3 * i16 + 2];
            }
            q_loop_ub = r2.size(1);
            for (int i19{0}; i19 < q_loop_ub; i19++) {
                r2D[(cfg_indCart[0] + r2D.size(0) * i19) - 1] = r2[3 * i19];
                r2D[(cfg_indCart[1] + r2D.size(0) * i19) - 1] = r2[3 * i19 + 1];
                r2D[(cfg_indCart[2] + r2D.size(0) * i19) - 1] = r2[3 * i19 + 2];
            }
            u_loop_ub = r3.size(1);
            for (int i24{0}; i24 < u_loop_ub; i24++) {
                r3D[(cfg_indCart[0] + r3D.size(0) * i24) - 1] = r3[3 * i24];
                r3D[(cfg_indCart[1] + r3D.size(0) * i24) - 1] = r3[3 * i24 + 1];
                r3D[(cfg_indCart[2] + r3D.size(0) * i24) - 1] = r3[3 * i24 + 2];
            }
        }
        // 'EvalCurvStructNoCtx:51' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int l_loop_ub;
            int o_loop_ub;
            int s_loop_ub;
            int w_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:52' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:53'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            c_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size, r4, r5,
                       r6, r7);
            l_loop_ub = r4.size(1);
            for (int i15{0}; i15 < l_loop_ub; i15++) {
                int p_loop_ub;
                p_loop_ub = r4.size(0);
                for (int i18{0}; i18 < p_loop_ub; i18++) {
                    r0D[(cfg_indRot[i18] + r0D.size(0) * i15) - 1] = r4[i18 + r4.size(0) * i15];
                }
            }
            o_loop_ub = r5.size(1);
            for (int i17{0}; i17 < o_loop_ub; i17++) {
                int t_loop_ub;
                t_loop_ub = r5.size(0);
                for (int i23{0}; i23 < t_loop_ub; i23++) {
                    r1D[(cfg_indRot[i23] + r1D.size(0) * i17) - 1] = r5[i23 + r5.size(0) * i17];
                }
            }
            s_loop_ub = r6.size(1);
            for (int i22{0}; i22 < s_loop_ub; i22++) {
                int x_loop_ub;
                x_loop_ub = r6.size(0);
                for (int i26{0}; i26 < x_loop_ub; i26++) {
                    r2D[(cfg_indRot[i26] + r2D.size(0) * i22) - 1] = r6[i26 + r6.size(0) * i22];
                }
            }
            w_loop_ub = r7.size(1);
            for (int i25{0}; i25 < w_loop_ub; i25++) {
                int y_loop_ub;
                y_loop_ub = r7.size(0);
                for (int i28{0}; i28 < y_loop_ub; i28++) {
                    r3D[(cfg_indRot[i28] + r3D.size(0) * i25) - 1] = r7[i28 + r7.size(0) * i25];
                }
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:55' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:56' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // maskTot );
        c_EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size, r0D, r1D, r2D,
                      r3D);
        break;
    case CurveType_Spline: {
        int ab_loop_ub;
        int bb_loop_ub;
        int cb_loop_ub;
        int i35;
        int unnamed_idx_0;
        // 'EvalCurvStructNoCtx:57' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:58' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        //  EvalBSpline
        //
        //  Inputs :
        //  spline        : struct : Spline structure
        //  u_vec         :    1xn : Vector for evaluation of the curv
        //
        //  Outputs:
        //  r0D           :   nDxn : The evaluated B spline at u_vec points
        //  r1D           :   nDxn : 1rst order parametric derivative for the Bspline
        //                    at u_vec points
        //  r2D           :   nDxn : 2nd order parametric derivative for the Bspline
        //                    at u_vec points
        //  r3D           :   nDxn : 3rd order parametric derivative for the B spline
        //                    at u_vec points
        //
        // 'EvalBSpline:19' sp  = spline.sp;
        // 'EvalBSpline:20' N   = length( u_vec );
        // 'EvalBSpline:21' M   = size( sp.coeff, 1 );
        // 'EvalBSpline:22' r0D = zeros( M, N );
        unnamed_idx_0 = spline->sp.coeff.size(0);
        // 'EvalBSpline:22' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        ab_loop_ub = u_vec_tilda.size(1);
        for (int i29{0}; i29 < ab_loop_ub; i29++) {
            for (int i30{0}; i30 < unnamed_idx_0; i30++) {
                r1D[i30 + r1D.size(0) * i29] = 0.0;
            }
        }
        // 'EvalBSpline:22' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        bb_loop_ub = u_vec_tilda.size(1);
        for (int i31{0}; i31 < bb_loop_ub; i31++) {
            for (int i32{0}; i32 < unnamed_idx_0; i32++) {
                r2D[i32 + r2D.size(0) * i31] = 0.0;
            }
        }
        // 'EvalBSpline:22' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        cb_loop_ub = u_vec_tilda.size(1);
        for (int i33{0}; i33 < cb_loop_ub; i33++) {
            for (int i34{0}; i34 < unnamed_idx_0; i34++) {
                r3D[i34 + r3D.size(0) * i33] = 0.0;
            }
        }
        // 'EvalBSpline:24' for j = 1 : M
        i35 = spline->sp.coeff.size(0);
        r0D.set_size(spline->sp.coeff.size(0), u_vec_tilda.size(1));
        for (int j{0}; j < i35; j++) {
            int db_loop_ub;
            int eb_loop_ub;
            int fb_loop_ub;
            int gb_loop_ub;
            int hb_loop_ub;
            int i40;
            int jb_loop_ub;
            int kb_loop_ub;
            int lb_loop_ub;
            // 'EvalBSpline:25' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:26'                         bspline_eval_vec( sp.Bl, sp.coeff( j, : ),
            // u_vec );
            //  bspline_eval_vec  : Eval Bspline bases for a given set of u value.
            //
            //  Inputs    :
            //  Bl            : BSpline bases
            //  coeffs        : BSpline coefficients
            //  uVec          : U vector of points to evaluate
            //
            //  Outputs   :
            //  x             : Evaluation of the BSpline
            //  xd            : Evaluation of the first derivative of the BSpline
            //  xdd           : Evaluation of the second derivative of the BSpline
            //  xddd          : Evaluation of the third derivative of the BSpline
            //
            // 'bspline_eval_vec:15' x       = zeros(size(uVec));
            r11.set_size(1, u_vec_tilda.size(1));
            db_loop_ub = u_vec_tilda.size(1);
            for (int i36{0}; i36 < db_loop_ub; i36++) {
                r11[i36] = 0.0;
            }
            // 'bspline_eval_vec:16' xd      = zeros(size(uVec));
            r12.set_size(1, u_vec_tilda.size(1));
            eb_loop_ub = u_vec_tilda.size(1);
            for (int i37{0}; i37 < eb_loop_ub; i37++) {
                r12[i37] = 0.0;
            }
            // 'bspline_eval_vec:17' xdd     = zeros(size(uVec));
            r13.set_size(1, u_vec_tilda.size(1));
            fb_loop_ub = u_vec_tilda.size(1);
            for (int i38{0}; i38 < fb_loop_ub; i38++) {
                r13[i38] = 0.0;
            }
            // 'bspline_eval_vec:18' xddd    = zeros(size(uVec));
            r14.set_size(1, u_vec_tilda.size(1));
            gb_loop_ub = u_vec_tilda.size(1);
            for (int i39{0}; i39 < gb_loop_ub; i39++) {
                r14[i39] = 0.0;
            }
            // 'bspline_eval_vec:20' for k = 1:length(uVec)
            i40 = u_vec_tilda.size(1);
            for (int c_k{0}; c_k < i40; c_k++) {
                int ib_loop_ub;
                // 'bspline_eval_vec:21' [xk, xdk, xddk, xdddk] = bspline_eval( Bl, coeffs, uVec( k
                // ) );
                r11[c_k] = u_vec_tilda[c_k];
                ib_loop_ub = spline->sp.coeff.size(1);
                b_spline.set_size(1, spline->sp.coeff.size(1));
                for (int i43{0}; i43 < ib_loop_ub; i43++) {
                    b_spline[i43] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i43];
                }
                bspline_eval(spline->sp.Bl.handle, b_spline, &r11[c_k], &d, &d1, &d2);
                r14[c_k] = d2;
                r13[c_k] = d1;
                r12[c_k] = d;
                // 'bspline_eval_vec:22' x(k)    = xk;
                // 'bspline_eval_vec:23' xd(k)   = xdk;
                // 'bspline_eval_vec:24' xdd(k)  = xddk;
                // 'bspline_eval_vec:25' xddd(k) = xdddk;
            }
            hb_loop_ub = r11.size(1);
            for (int i41{0}; i41 < hb_loop_ub; i41++) {
                r0D[j + r0D.size(0) * i41] = r11[i41];
            }
            jb_loop_ub = r12.size(1);
            for (int i42{0}; i42 < jb_loop_ub; i42++) {
                r1D[j + r1D.size(0) * i42] = r12[i42];
            }
            kb_loop_ub = r13.size(1);
            for (int i44{0}; i44 < kb_loop_ub; i44++) {
                r2D[j + r2D.size(0) * i44] = r13[i44];
            }
            lb_loop_ub = r14.size(1);
            for (int i45{0}; i45 < lb_loop_ub; i45++) {
                r3D[j + r3D.size(0) * i45] = r14[i45];
            }
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:59' otherwise
        // 'EvalCurvStructNoCtx:60' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        qb_ocn_assert();
        break;
    }
    // 'EvalCurvStructNoCtx:63' if( 1 )
    // 'EvalCurvStructNoCtx:64' r1D = a     .* r1D;
    h_loop_ub = r1D.size(1);
    for (int i11{0}; i11 < h_loop_ub; i11++) {
        int b_scalarLB;
        int b_vectorUB;
        int j_loop_ub;
        j_loop_ub = r1D.size(0);
        b_scalarLB = (r1D.size(0) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i14{0}; i14 <= b_vectorUB; i14 += 2) {
            __m128d r8;
            r8 = _mm_loadu_pd(&r1D[i14 + r1D.size(0) * i11]);
            _mm_storeu_pd(&r1D[i14 + r1D.size(0) * i11],
                          _mm_mul_pd(_mm_set1_pd(curv->a_param), r8));
        }
        for (int i14{b_scalarLB}; i14 < j_loop_ub; i14++) {
            r1D[i14 + r1D.size(0) * i11] = curv->a_param * r1D[i14 + r1D.size(0) * i11];
        }
    }
    // 'EvalCurvStructNoCtx:65' r2D = a^2   .* r2D;
    c = curv->a_param * curv->a_param;
    k_loop_ub = r2D.size(1);
    for (int i13{0}; i13 < k_loop_ub; i13++) {
        int c_scalarLB;
        int c_vectorUB;
        int n_loop_ub;
        n_loop_ub = r2D.size(0);
        c_scalarLB = (r2D.size(0) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (int i21{0}; i21 <= c_vectorUB; i21 += 2) {
            __m128d r9;
            r9 = _mm_loadu_pd(&r2D[i21 + r2D.size(0) * i13]);
            _mm_storeu_pd(&r2D[i21 + r2D.size(0) * i13], _mm_mul_pd(_mm_set1_pd(c), r9));
        }
        for (int i21{c_scalarLB}; i21 < n_loop_ub; i21++) {
            r2D[i21 + r2D.size(0) * i13] = c * r2D[i21 + r2D.size(0) * i13];
        }
    }
    // 'EvalCurvStructNoCtx:66' r3D = a^3   .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    r_loop_ub = r3D.size(1);
    for (int i20{0}; i20 < r_loop_ub; i20++) {
        int d_scalarLB;
        int d_vectorUB;
        int v_loop_ub;
        v_loop_ub = r3D.size(0);
        d_scalarLB = (r3D.size(0) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (int i27{0}; i27 <= d_vectorUB; i27 += 2) {
            __m128d r10;
            r10 = _mm_loadu_pd(&r3D[i27 + r3D.size(0) * i20]);
            _mm_storeu_pd(&r3D[i27 + r3D.size(0) * i20], _mm_mul_pd(_mm_set1_pd(b_c), r10));
        }
        for (int i27{d_scalarLB}; i27 < v_loop_ub; i27++) {
            r3D[i27 + r3D.size(0) * i20] = b_c * r3D[i27 + r3D.size(0) * i20];
        }
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
// EvalCurvStructNoCtx : Eval curve structure and its derivatives on
//  a set of u points without any need of the context structure.
//
//  Inputs :
//  cfg       : The configuration structure of the computational chain
//  curv      : The curve used in the evaluation
//  spline    : The required spline for the evaluation
//  u_vec     : U vectors
//
//  Outputs :
//  r0D   : Matrix of points for a given set of u values
//  r1D   : Matrix of points (first derivative) for a given set of u values
//  r2D   : Matrix of points (second derivative) for a given set of u values
//  r3D   : Matrix of points (third derivative) for a given set of u values
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
    // 'EvalCurvStructNoCtx:18' coder.inline("never");
    // 'EvalCurvStructNoCtx:20' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    c_ocn_assert(true);
    // 'EvalCurvStructNoCtx:21' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    d_ocn_assert(true);
    //
    // 'EvalCurvStructNoCtx:24' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:26' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:27' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:29' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis, 2);
    // 'EvalCurvStructNoCtx:30' r1D = r0D;
    r1D.set_size(cfg_NumberAxis, 2);
    // 'EvalCurvStructNoCtx:30' r2D = r0D;
    r2D.set_size(cfg_NumberAxis, 2);
    // 'EvalCurvStructNoCtx:30' r3D = r0D;
    r3D.set_size(cfg_NumberAxis, 2);
    // 'EvalCurvStructNoCtx:32' a = curv.a_param;
    // 'EvalCurvStructNoCtx:33' b = curv.b_param;
    // 'EvalCurvStructNoCtx:35' u_vec_tilda = a * u_vec + b;
    for (int i{0}; i < 2; i++) {
        for (int i1{0}; i1 < cfg_NumberAxis; i1++) {
            r0D[i1 + r0D.size(0) * i] = 0.0;
            r1D[i1 + r1D.size(0) * i] = 0.0;
            r2D[i1 + r2D.size(0) * i] = 0.0;
            r3D[i1 + r3D.size(0) * i] = 0.0;
        }
        u_vec_tilda[i] = curv->a_param * static_cast<double>(i) + curv->b_param;
    }
    // 'EvalCurvStructNoCtx:37' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:38' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:39' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:40' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:41' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:43' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:44' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:45' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(12);
        r1D.reserve(12);
        d_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), *(int(*)[2])r0D.size(), (double *)r1D.data(),
                   *(int(*)[2])r1D.size(), r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:46' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:47' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            double dv[2][3];
            double dv1[2][3];
            double dv2[2][3];
            double dv3[2][3];
            int c_tmp_data[3];
            int c_tmp_size;
            int d_scalarLB;
            int d_vectorUB;
            int e_loop_ub;
            int f_scalarLB;
            int f_vectorUB;
            int g_scalarLB;
            int g_vectorUB;
            int h_loop_ub;
            int k_loop_ub;
            int l_loop_ub;
            int scalarLB;
            int vectorUB;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:48' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:49'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            d_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            e_loop_ub = cfg_indCart.size(0);
            scalarLB = (cfg_indCart.size(0) / 4) << 2;
            vectorUB = scalarLB - 4;
            for (int i5{0}; i5 <= vectorUB; i5 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i5],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i5]),
                                               _mm_set1_epi32(1)));
            }
            for (int i5{scalarLB}; i5 < e_loop_ub; i5++) {
                c_tmp_data[i5] = cfg_indCart[i5] - 1;
            }
            for (int i9{0}; i9 < 2; i9++) {
                for (int i11{0}; i11 < c_tmp_size; i11++) {
                    r0D[c_tmp_data[i11] + r0D.size(0) * i9] = dv[i9][i11];
                }
            }
            c_tmp_size = cfg_indCart.size(0);
            h_loop_ub = cfg_indCart.size(0);
            d_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            d_vectorUB = d_scalarLB - 4;
            for (int i13{0}; i13 <= d_vectorUB; i13 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i13],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i13]),
                                               _mm_set1_epi32(1)));
            }
            for (int i13{d_scalarLB}; i13 < h_loop_ub; i13++) {
                c_tmp_data[i13] = cfg_indCart[i13] - 1;
            }
            for (int i17{0}; i17 < 2; i17++) {
                for (int i19{0}; i19 < c_tmp_size; i19++) {
                    r1D[c_tmp_data[i19] + r1D.size(0) * i17] = dv1[i17][i19];
                }
            }
            c_tmp_size = cfg_indCart.size(0);
            k_loop_ub = cfg_indCart.size(0);
            f_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            f_vectorUB = f_scalarLB - 4;
            for (int i20{0}; i20 <= f_vectorUB; i20 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i20],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i20]),
                                               _mm_set1_epi32(1)));
            }
            for (int i20{f_scalarLB}; i20 < k_loop_ub; i20++) {
                c_tmp_data[i20] = cfg_indCart[i20] - 1;
            }
            for (int i21{0}; i21 < 2; i21++) {
                for (int i22{0}; i22 < c_tmp_size; i22++) {
                    r2D[c_tmp_data[i22] + r2D.size(0) * i21] = dv2[i21][i22];
                }
            }
            c_tmp_size = cfg_indCart.size(0);
            l_loop_ub = cfg_indCart.size(0);
            g_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            g_vectorUB = g_scalarLB - 4;
            for (int i23{0}; i23 <= g_vectorUB; i23 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i23],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i23]),
                                               _mm_set1_epi32(1)));
            }
            for (int i23{g_scalarLB}; i23 < l_loop_ub; i23++) {
                c_tmp_data[i23] = cfg_indCart[i23] - 1;
            }
            for (int i24{0}; i24 < 2; i24++) {
                for (int i25{0}; i25 < c_tmp_size; i25++) {
                    r3D[c_tmp_data[i25] + r3D.size(0) * i24] = dv3[i24][i25];
                }
            }
        }
        // 'EvalCurvStructNoCtx:51' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int b_loop_ub;
            int c_loop_ub;
            int d_loop_ub;
            int loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:52' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:53'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            d_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, tmp_size, b_tmp_data, b_tmp_size, r, r1);
            loop_ub = tmp_size[0];
            b_loop_ub = b_tmp_size[0];
            c_loop_ub = r.size(0);
            d_loop_ub = r1.size(0);
            for (int i3{0}; i3 < 2; i3++) {
                for (int i4{0}; i4 < loop_ub; i4++) {
                    r0D[(cfg_indRot[i4] + r0D.size(0) * i3) - 1] = tmp_data[i4 + tmp_size[0] * i3];
                }
                for (int i7{0}; i7 < b_loop_ub; i7++) {
                    r1D[(cfg_indRot[i7] + r1D.size(0) * i3) - 1] =
                        b_tmp_data[i7 + b_tmp_size[0] * i3];
                }
                for (int i8{0}; i8 < c_loop_ub; i8++) {
                    r2D[(cfg_indRot[i8] + r2D.size(0) * i3) - 1] = r[i8 + r.size(0) * i3];
                }
                for (int i10{0}; i10 < d_loop_ub; i10++) {
                    r3D[(cfg_indRot[i10] + r3D.size(0) * i3) - 1] = r1[i10 + r1.size(0) * i3];
                }
            }
        }
    } break;
    case CurveType_TransP5: {
        int iv[2];
        int iv1[2];
        int iv2[2];
        int iv3[2];
        // 'EvalCurvStructNoCtx:55' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:56' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // maskTot );
        r0D.reserve(12);
        r1D.reserve(12);
        r2D.reserve(12);
        r3D.reserve(12);
        d_EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                      (double *)r0D.data(), iv, (double *)r1D.data(), iv1, (double *)r2D.data(),
                      iv2, (double *)r3D.data(), iv3);
        (*(int(*)[2])r3D.size())[0] = iv3[0];
        (*(int(*)[2])r3D.size())[1] = iv3[1];
        (*(int(*)[2])r2D.size())[0] = iv2[0];
        (*(int(*)[2])r2D.size())[1] = iv2[1];
        (*(int(*)[2])r1D.size())[0] = iv1[0];
        (*(int(*)[2])r1D.size())[1] = iv1[1];
        (*(int(*)[2])r0D.size())[0] = iv[0];
        (*(int(*)[2])r0D.size())[1] = iv[1];
    } break;
    case CurveType_Spline: {
        int i18;
        int i_loop_ub;
        // 'EvalCurvStructNoCtx:57' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:58' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        //  EvalBSpline
        //
        //  Inputs :
        //  spline        : struct : Spline structure
        //  u_vec         :    1xn : Vector for evaluation of the curv
        //
        //  Outputs:
        //  r0D           :   nDxn : The evaluated B spline at u_vec points
        //  r1D           :   nDxn : 1rst order parametric derivative for the Bspline
        //                    at u_vec points
        //  r2D           :   nDxn : 2nd order parametric derivative for the Bspline
        //                    at u_vec points
        //  r3D           :   nDxn : 3rd order parametric derivative for the B spline
        //                    at u_vec points
        //
        // 'EvalBSpline:19' sp  = spline.sp;
        // 'EvalBSpline:20' N   = length( u_vec );
        // 'EvalBSpline:21' M   = size( sp.coeff, 1 );
        // 'EvalBSpline:22' r0D = zeros( M, N );
        // 'EvalBSpline:22' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0), 2);
        // 'EvalBSpline:22' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0), 2);
        // 'EvalBSpline:22' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0), 2);
        i_loop_ub = spline->sp.coeff.size(0);
        for (int i14{0}; i14 < 2; i14++) {
            for (int i15{0}; i15 < i_loop_ub; i15++) {
                r1D[i15 + r1D.size(0) * i14] = 0.0;
                r2D[i15 + r2D.size(0) * i14] = 0.0;
                r3D[i15 + r3D.size(0) * i14] = 0.0;
            }
        }
        // 'EvalBSpline:24' for j = 1 : M
        i18 = spline->sp.coeff.size(0);
        r0D.set_size(spline->sp.coeff.size(0), 2);
        for (int j{0}; j < i18; j++) {
            int m_loop_ub;
            // 'EvalBSpline:25' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:26'                         bspline_eval_vec( sp.Bl, sp.coeff( j, : ),
            // u_vec );
            //  bspline_eval_vec  : Eval Bspline bases for a given set of u value.
            //
            //  Inputs    :
            //  Bl            : BSpline bases
            //  coeffs        : BSpline coefficients
            //  uVec          : U vector of points to evaluate
            //
            //  Outputs   :
            //  x             : Evaluation of the BSpline
            //  xd            : Evaluation of the first derivative of the BSpline
            //  xdd           : Evaluation of the second derivative of the BSpline
            //  xddd          : Evaluation of the third derivative of the BSpline
            //
            // 'bspline_eval_vec:15' x       = zeros(size(uVec));
            // 'bspline_eval_vec:16' xd      = zeros(size(uVec));
            // 'bspline_eval_vec:17' xdd     = zeros(size(uVec));
            // 'bspline_eval_vec:18' xddd    = zeros(size(uVec));
            // 'bspline_eval_vec:20' for k = 1:length(uVec)
            m_loop_ub = spline->sp.coeff.size(1);
            for (int k{0}; k < 2; k++) {
                // 'bspline_eval_vec:21' [xk, xdk, xddk, xdddk] = bspline_eval( Bl, coeffs, uVec( k
                // ) );
                dv4[k] = u_vec_tilda[k];
                b_spline.set_size(1, m_loop_ub);
                for (int i26{0}; i26 < m_loop_ub; i26++) {
                    b_spline[i26] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i26];
                }
                bspline_eval(spline->sp.Bl.handle, b_spline, &dv4[k], &dv5[k], &dv6[k], &dv7[k]);
                // 'bspline_eval_vec:22' x(k)    = xk;
                // 'bspline_eval_vec:23' xd(k)   = xdk;
                // 'bspline_eval_vec:24' xdd(k)  = xddk;
                // 'bspline_eval_vec:25' xddd(k) = xdddk;
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
        // 'EvalCurvStructNoCtx:59' otherwise
        // 'EvalCurvStructNoCtx:60' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        qb_ocn_assert();
        break;
    }
    // 'EvalCurvStructNoCtx:63' if( 1 )
    // 'EvalCurvStructNoCtx:64' r1D = a     .* r1D;
    r1D.set_size(r1D.size(0), 2);
    // 'EvalCurvStructNoCtx:65' r2D = a^2   .* r2D;
    c = curv->a_param * curv->a_param;
    r2D.set_size(r2D.size(0), 2);
    // 'EvalCurvStructNoCtx:66' r3D = a^3   .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    r3D.set_size(r3D.size(0), 2);
    for (int i2{0}; i2 < 2; i2++) {
        int b_scalarLB;
        int b_vectorUB;
        int c_scalarLB;
        int c_vectorUB;
        int e_scalarLB;
        int e_vectorUB;
        int f_loop_ub;
        int g_loop_ub;
        int j_loop_ub;
        f_loop_ub = r1D.size(0);
        b_scalarLB = (r1D.size(0) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i6{0}; i6 <= b_vectorUB; i6 += 2) {
            __m128d r2;
            r2 = _mm_loadu_pd(&r1D[i6 + r1D.size(0) * i2]);
            _mm_storeu_pd(&r1D[i6 + r1D.size(0) * i2], _mm_mul_pd(_mm_set1_pd(curv->a_param), r2));
        }
        for (int i6{b_scalarLB}; i6 < f_loop_ub; i6++) {
            r1D[i6 + r1D.size(0) * i2] = curv->a_param * r1D[i6 + r1D.size(0) * i2];
        }
        g_loop_ub = r2D.size(0);
        c_scalarLB = (r2D.size(0) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (int i12{0}; i12 <= c_vectorUB; i12 += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&r2D[i12 + r2D.size(0) * i2]);
            _mm_storeu_pd(&r2D[i12 + r2D.size(0) * i2], _mm_mul_pd(_mm_set1_pd(c), r3));
        }
        for (int i12{c_scalarLB}; i12 < g_loop_ub; i12++) {
            r2D[i12 + r2D.size(0) * i2] = c * r2D[i12 + r2D.size(0) * i2];
        }
        j_loop_ub = r3D.size(0);
        e_scalarLB = (r3D.size(0) / 2) << 1;
        e_vectorUB = e_scalarLB - 2;
        for (int i16{0}; i16 <= e_vectorUB; i16 += 2) {
            __m128d r4;
            r4 = _mm_loadu_pd(&r3D[i16 + r3D.size(0) * i2]);
            _mm_storeu_pd(&r3D[i16 + r3D.size(0) * i2], _mm_mul_pd(_mm_set1_pd(b_c), r4));
        }
        for (int i16{e_scalarLB}; i16 < j_loop_ub; i16++) {
            r3D[i16 + r3D.size(0) * i2] = b_c * r3D[i16 + r3D.size(0) * i2];
        }
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
// EvalCurvStructNoCtx : Eval curve structure and its derivatives on
//  a set of u points without any need of the context structure.
//
//  Inputs :
//  cfg       : The configuration structure of the computational chain
//  curv      : The curve used in the evaluation
//  spline    : The required spline for the evaluation
//  u_vec     : U vectors
//
//  Outputs :
//  r0D   : Matrix of points for a given set of u values
//  r1D   : Matrix of points (first derivative) for a given set of u values
//  r2D   : Matrix of points (second derivative) for a given set of u values
//  r3D   : Matrix of points (third derivative) for a given set of u values
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
    int b_tmp_size;
    int c_loop_ub;
    int c_scalarLB;
    int c_vectorUB;
    int d_scalarLB;
    int d_vectorUB;
    int g_loop_ub;
    int i1;
    int i2;
    int i4;
    int i5;
    int loop_ub;
    int scalarLB;
    int tmp_size;
    int vectorUB;
    // 'EvalCurvStructNoCtx:18' coder.inline("never");
    // 'EvalCurvStructNoCtx:20' ocn_assert( ~any( u_vec > 1.0 ), "u_vec > 1", mfilename );
    c_ocn_assert(u_vec <= 1.0);
    // 'EvalCurvStructNoCtx:21' ocn_assert( ~any( u_vec < 0.0 ), "u_vec < 0", mfilename );
    d_ocn_assert(u_vec >= 0.0);
    //
    // 'EvalCurvStructNoCtx:24' Type    = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:26' N       = numel( u_vec );
    // 'EvalCurvStructNoCtx:27' M       = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:29' r0D     = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:30' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:30' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:30' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:32' a = curv.a_param;
    // 'EvalCurvStructNoCtx:33' b = curv.b_param;
    // 'EvalCurvStructNoCtx:35' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv->a_param * u_vec + curv->b_param;
    // 'EvalCurvStructNoCtx:37' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:38' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:39' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:40' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:41' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:43' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:44' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:45' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        r0D.reserve(6);
        r1D.reserve(6);
        b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                   (double *)r0D.data(), &(*(int(*)[1])r0D.size())[0], (double *)r1D.data(),
                   &(*(int(*)[1])r1D.size())[0], r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:46' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:47' if( cfg.NCart > 0 )
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
            int h_loop_ub;
            int k_loop_ub;
            int m_loop_ub;
            //  Cartesian axis
            // 'EvalCurvStructNoCtx:48' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:49'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart_data, cfg_maskCart_size, dv, dv1, dv2, dv3);
            c_tmp_size = cfg_indCart.size(0);
            b_loop_ub = cfg_indCart.size(0);
            b_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            b_vectorUB = b_scalarLB - 4;
            for (int i9{0}; i9 <= b_vectorUB; i9 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i9],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i9]),
                                               _mm_set1_epi32(1)));
            }
            for (int i9{b_scalarLB}; i9 < b_loop_ub; i9++) {
                c_tmp_data[i9] = cfg_indCart[i9] - 1;
            }
            for (int i12{0}; i12 < c_tmp_size; i12++) {
                r0D[c_tmp_data[i12]] = dv[i12];
            }
            c_tmp_size = cfg_indCart.size(0);
            h_loop_ub = cfg_indCart.size(0);
            e_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            e_vectorUB = e_scalarLB - 4;
            for (int i15{0}; i15 <= e_vectorUB; i15 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i15],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i15]),
                                               _mm_set1_epi32(1)));
            }
            for (int i15{e_scalarLB}; i15 < h_loop_ub; i15++) {
                c_tmp_data[i15] = cfg_indCart[i15] - 1;
            }
            for (int i17{0}; i17 < c_tmp_size; i17++) {
                r1D[c_tmp_data[i17]] = dv1[i17];
            }
            c_tmp_size = cfg_indCart.size(0);
            k_loop_ub = cfg_indCart.size(0);
            f_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            f_vectorUB = f_scalarLB - 4;
            for (int i19{0}; i19 <= f_vectorUB; i19 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i19],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i19]),
                                               _mm_set1_epi32(1)));
            }
            for (int i19{f_scalarLB}; i19 < k_loop_ub; i19++) {
                c_tmp_data[i19] = cfg_indCart[i19] - 1;
            }
            for (int i22{0}; i22 < c_tmp_size; i22++) {
                r2D[c_tmp_data[i22]] = dv2[i22];
            }
            c_tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            g_scalarLB = (cfg_indCart.size(0) / 4) << 2;
            g_vectorUB = g_scalarLB - 4;
            for (int i23{0}; i23 <= g_vectorUB; i23 += 4) {
                _mm_storeu_si128((__m128i *)&c_tmp_data[i23],
                                 _mm_sub_epi32(_mm_loadu_si128((const __m128i *)&cfg_indCart[i23]),
                                               _mm_set1_epi32(1)));
            }
            for (int i23{g_scalarLB}; i23 < m_loop_ub; i23++) {
                c_tmp_data[i23] = cfg_indCart[i23] - 1;
            }
            for (int i24{0}; i24 < c_tmp_size; i24++) {
                r3D[c_tmp_data[i24]] = dv3[i24];
            }
        }
        // 'EvalCurvStructNoCtx:51' if( cfg.NRot > 0 )
        if (cfg_NRot > 0) {
            int d_loop_ub;
            int e_loop_ub;
            //  Rotative axis
            // 'EvalCurvStructNoCtx:52' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:53'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot_data, cfg_maskRot_size,
                       tmp_data, &tmp_size, b_tmp_data, &b_tmp_size, r, r1);
            for (int i6{0}; i6 < tmp_size; i6++) {
                r0D[cfg_indRot[i6] - 1] = tmp_data[i6];
            }
            for (int i7{0}; i7 < b_tmp_size; i7++) {
                r1D[cfg_indRot[i7] - 1] = b_tmp_data[i7];
            }
            d_loop_ub = r.size(0);
            for (int i8{0}; i8 < d_loop_ub; i8++) {
                r2D[cfg_indRot[i8] - 1] = r[i8];
            }
            e_loop_ub = r1.size(0);
            for (int i11{0}; i11 < e_loop_ub; i11++) {
                r3D[cfg_indRot[i11] - 1] = r1[i11];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:55' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:56' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // maskTot );
        r0D.reserve(6);
        r1D.reserve(6);
        r2D.reserve(6);
        r3D.reserve(6);
        b_EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_maskTot_data, cfg_maskTot_size,
                      (double *)r0D.data(), &i1, (double *)r1D.data(), &i2, (double *)r2D.data(),
                      &i4, (double *)r3D.data(), &i5);
        (*(int(*)[1])r3D.size())[0] = i5;
        (*(int(*)[1])r2D.size())[0] = i4;
        (*(int(*)[1])r1D.size())[0] = i2;
        (*(int(*)[1])r0D.size())[0] = i1;
        break;
    case CurveType_Spline: {
        int f_loop_ub;
        int i21;
        int i_loop_ub;
        int j_loop_ub;
        int l_loop_ub;
        // 'EvalCurvStructNoCtx:57' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:58' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        //  EvalBSpline
        //
        //  Inputs :
        //  spline        : struct : Spline structure
        //  u_vec         :    1xn : Vector for evaluation of the curv
        //
        //  Outputs:
        //  r0D           :   nDxn : The evaluated B spline at u_vec points
        //  r1D           :   nDxn : 1rst order parametric derivative for the Bspline
        //                    at u_vec points
        //  r2D           :   nDxn : 2nd order parametric derivative for the Bspline
        //                    at u_vec points
        //  r3D           :   nDxn : 3rd order parametric derivative for the B spline
        //                    at u_vec points
        //
        // 'EvalBSpline:19' sp  = spline.sp;
        // 'EvalBSpline:20' N   = length( u_vec );
        // 'EvalBSpline:21' M   = size( sp.coeff, 1 );
        // 'EvalBSpline:22' r0D = zeros( M, N );
        r0D.set_size(spline->sp.coeff.size(0));
        f_loop_ub = spline->sp.coeff.size(0);
        for (int i13{0}; i13 < f_loop_ub; i13++) {
            r0D[i13] = 0.0;
        }
        // 'EvalBSpline:22' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        i_loop_ub = spline->sp.coeff.size(0);
        for (int i16{0}; i16 < i_loop_ub; i16++) {
            r1D[i16] = 0.0;
        }
        // 'EvalBSpline:22' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        j_loop_ub = spline->sp.coeff.size(0);
        for (int i18{0}; i18 < j_loop_ub; i18++) {
            r2D[i18] = 0.0;
        }
        // 'EvalBSpline:22' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        l_loop_ub = spline->sp.coeff.size(0);
        for (int i20{0}; i20 < l_loop_ub; i20++) {
            r3D[i20] = 0.0;
        }
        // 'EvalBSpline:24' for j = 1 : M
        i21 = spline->sp.coeff.size(0);
        for (int j{0}; j < i21; j++) {
            int n_loop_ub;
            // 'EvalBSpline:25' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:26'                         bspline_eval_vec( sp.Bl, sp.coeff( j, : ),
            // u_vec );
            //  bspline_eval_vec  : Eval Bspline bases for a given set of u value.
            //
            //  Inputs    :
            //  Bl            : BSpline bases
            //  coeffs        : BSpline coefficients
            //  uVec          : U vector of points to evaluate
            //
            //  Outputs   :
            //  x             : Evaluation of the BSpline
            //  xd            : Evaluation of the first derivative of the BSpline
            //  xdd           : Evaluation of the second derivative of the BSpline
            //  xddd          : Evaluation of the third derivative of the BSpline
            //
            // 'bspline_eval_vec:15' x       = zeros(size(uVec));
            // 'bspline_eval_vec:16' xd      = zeros(size(uVec));
            // 'bspline_eval_vec:17' xdd     = zeros(size(uVec));
            // 'bspline_eval_vec:18' xddd    = zeros(size(uVec));
            // 'bspline_eval_vec:20' for k = 1:length(uVec)
            // 'bspline_eval_vec:21' [xk, xdk, xddk, xdddk] = bspline_eval( Bl, coeffs, uVec( k ) );
            r0D[j] = u_vec_tilda;
            n_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i25{0}; i25 < n_loop_ub; i25++) {
                b_spline[i25] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i25];
            }
            bspline_eval(spline->sp.Bl.handle, b_spline, &r0D[j], &d, &d1, &d2);
            r3D[j] = d2;
            r2D[j] = d1;
            r1D[j] = d;
            // 'bspline_eval_vec:22' x(k)    = xk;
            // 'bspline_eval_vec:23' xd(k)   = xdk;
            // 'bspline_eval_vec:24' xdd(k)  = xddk;
            // 'bspline_eval_vec:25' xddd(k) = xdddk;
        }
    } break;
    default:
        // 'EvalCurvStructNoCtx:59' otherwise
        // 'EvalCurvStructNoCtx:60' ocn_assert( false, "Unknown Curve Type for Eval...", mfilename
        // );
        qb_ocn_assert();
        break;
    }
    // 'EvalCurvStructNoCtx:63' if( 1 )
    // 'EvalCurvStructNoCtx:64' r1D = a     .* r1D;
    loop_ub = r1D.size(0);
    scalarLB = (r1D.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i3{0}; i3 <= vectorUB; i3 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r1D[i3]);
        _mm_storeu_pd(&r1D[i3], _mm_mul_pd(_mm_set1_pd(curv->a_param), r2));
    }
    for (int i3{scalarLB}; i3 < loop_ub; i3++) {
        r1D[i3] = curv->a_param * r1D[i3];
    }
    // 'EvalCurvStructNoCtx:65' r2D = a^2   .* r2D;
    c = curv->a_param * curv->a_param;
    c_loop_ub = r2D.size(0);
    c_scalarLB = (r2D.size(0) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (int i10{0}; i10 <= c_vectorUB; i10 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&r2D[i10]);
        _mm_storeu_pd(&r2D[i10], _mm_mul_pd(_mm_set1_pd(c), r3));
    }
    for (int i10{c_scalarLB}; i10 < c_loop_ub; i10++) {
        r2D[i10] = c * r2D[i10];
    }
    // 'EvalCurvStructNoCtx:66' r3D = a^3   .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    g_loop_ub = r3D.size(0);
    d_scalarLB = (r3D.size(0) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i14{0}; i14 <= d_vectorUB; i14 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&r3D[i14]);
        _mm_storeu_pd(&r3D[i14], _mm_mul_pd(_mm_set1_pd(b_c), r4));
    }
    for (int i14{d_scalarLB}; i14 < g_loop_ub; i14++) {
        r3D[i14] = b_c * r3D[i14];
    }
}

} // namespace ocn

//
// File trailer for EvalCurvStructNoCtx.cpp
//
// [EOF]
//
