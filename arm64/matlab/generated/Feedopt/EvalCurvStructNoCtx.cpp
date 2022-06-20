//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStructNoCtx.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 20-Jun-2022 16:00:50
//

// Include Files
#include "EvalCurvStructNoCtx.h"
#include "EvalBSpline.h"
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
//                const ::coder::array<bool, 2U> &cfg_maskCart
//                const ::coder::array<bool, 2U> &cfg_maskRot
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
                         const ::coder::array<bool, 2U> &cfg_maskCart,
                         const ::coder::array<bool, 2U> &cfg_maskRot,
                         const ::coder::array<int, 1U> &cfg_indCart,
                         const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                         int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                         const CurvStruct *spline, ::coder::array<double, 2U> &u_vec,
                         ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D,
                         ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> r5;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> r7;
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<bool, 2U> b_cfg_maskTot_data;
    ::coder::array<bool, 2U> x;
    double b_c;
    double c;
    int b_k;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int k;
    int loop_ub;
    int m_loop_ub;
    int t_loop_ub;
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
        // 'EvalCurvStructNoCtx:62' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:63' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:65' else
        // 'EvalCurvStructNoCtx:66' fprintf(err_msg);
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
        // 'EvalCurvStructNoCtx:62' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:63' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:65' else
        // 'EvalCurvStructNoCtx:66' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec < 0\n");
        fflush(stdout);
    }
    //
    // 'EvalCurvStructNoCtx:15' Type  = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N   = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M   = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:20' r0D = zeros( M, N );
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
    // 'EvalCurvStructNoCtx:22' r2D = r0D;
    r2D.set_size(cfg_NumberAxis, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i6{0}; i6 < e_loop_ub; i6++) {
        for (int i7{0}; i7 < cfg_NumberAxis; i7++) {
            r2D[i7 + r2D.size(0) * i6] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:23' r3D = r0D;
    r3D.set_size(cfg_NumberAxis, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        for (int i9{0}; i9 < cfg_NumberAxis; i9++) {
            r3D[i9 + r3D.size(0) * i8] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:25' a = curv.a_param;
    // 'EvalCurvStructNoCtx:26' b = curv.b_param;
    // 'EvalCurvStructNoCtx:28' u_vec_tilda = a * u_vec + b;
    u_vec_tilda.set_size(1, u_vec.size(1));
    g_loop_ub = u_vec.size(1);
    for (int i10{0}; i10 < g_loop_ub; i10++) {
        u_vec_tilda[i10] = curv->a_param * u_vec[i10] + curv->b_param;
    }
    // 'EvalCurvStructNoCtx:30' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:31' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:32' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:33' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:34' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:36' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:37' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:38' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        b_cfg_maskTot_data.set((bool *)&cfg_maskTot_data[0], cfg_maskTot_size[0],
                               cfg_maskTot_size[1]);
        EvalLine(curv->R0, curv->R1, u_vec_tilda, b_cfg_maskTot_data, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:39' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:40' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int i_loop_ub;
            int l_loop_ub;
            int p_loop_ub;
            int u_loop_ub;
            //  Only rotation
            // 'EvalCurvStructNoCtx:41' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:42'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                      u_vec_tilda, cfg_maskCart, r, r1, r2, r3);
            i_loop_ub = r.size(1);
            for (int i13{0}; i13 < i_loop_ub; i13++) {
                r0D[(cfg_indCart[0] + r0D.size(0) * i13) - 1] = r[3 * i13];
                r0D[(cfg_indCart[1] + r0D.size(0) * i13) - 1] = r[3 * i13 + 1];
                r0D[(cfg_indCart[2] + r0D.size(0) * i13) - 1] = r[3 * i13 + 2];
            }
            l_loop_ub = r1.size(1);
            for (int i16{0}; i16 < l_loop_ub; i16++) {
                r1D[(cfg_indCart[0] + r1D.size(0) * i16) - 1] = r1[3 * i16];
                r1D[(cfg_indCart[1] + r1D.size(0) * i16) - 1] = r1[3 * i16 + 1];
                r1D[(cfg_indCart[2] + r1D.size(0) * i16) - 1] = r1[3 * i16 + 2];
            }
            p_loop_ub = r2.size(1);
            for (int i20{0}; i20 < p_loop_ub; i20++) {
                r2D[(cfg_indCart[0] + r2D.size(0) * i20) - 1] = r2[3 * i20];
                r2D[(cfg_indCart[1] + r2D.size(0) * i20) - 1] = r2[3 * i20 + 1];
                r2D[(cfg_indCart[2] + r2D.size(0) * i20) - 1] = r2[3 * i20 + 2];
            }
            u_loop_ub = r3.size(1);
            for (int i25{0}; i25 < u_loop_ub; i25++) {
                r3D[(cfg_indCart[0] + r3D.size(0) * i25) - 1] = r3[3 * i25];
                r3D[(cfg_indCart[1] + r3D.size(0) * i25) - 1] = r3[3 * i25 + 1];
                r3D[(cfg_indCart[2] + r3D.size(0) * i25) - 1] = r3[3 * i25 + 2];
            }
        } else if (cfg_NRot > 0) {
            int k_loop_ub;
            int n_loop_ub;
            int r_loop_ub;
            int v_loop_ub;
            // 'EvalCurvStructNoCtx:43' elseif( cfg.NRot > 0 )
            //  Only cartesian
            // 'EvalCurvStructNoCtx:44' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:45'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot, r4, r5, r6, r7);
            k_loop_ub = r4.size(1);
            for (int i15{0}; i15 < k_loop_ub; i15++) {
                int o_loop_ub;
                o_loop_ub = r4.size(0);
                for (int i19{0}; i19 < o_loop_ub; i19++) {
                    r0D[(cfg_indRot[i19] + r0D.size(0) * i15) - 1] = r4[i19 + r4.size(0) * i15];
                }
            }
            n_loop_ub = r5.size(1);
            for (int i18{0}; i18 < n_loop_ub; i18++) {
                int s_loop_ub;
                s_loop_ub = r5.size(0);
                for (int i23{0}; i23 < s_loop_ub; i23++) {
                    r1D[(cfg_indRot[i23] + r1D.size(0) * i18) - 1] = r5[i23 + r5.size(0) * i18];
                }
            }
            r_loop_ub = r6.size(1);
            for (int i22{0}; i22 < r_loop_ub; i22++) {
                int w_loop_ub;
                w_loop_ub = r6.size(0);
                for (int i27{0}; i27 < w_loop_ub; i27++) {
                    r2D[(cfg_indRot[i27] + r2D.size(0) * i22) - 1] = r6[i27 + r6.size(0) * i22];
                }
            }
            v_loop_ub = r7.size(1);
            for (int i26{0}; i26 < v_loop_ub; i26++) {
                int y_loop_ub;
                y_loop_ub = r7.size(0);
                for (int i29{0}; i29 < y_loop_ub; i29++) {
                    r3D[(cfg_indRot[i29] + r3D.size(0) * i26) - 1] = r7[i29 + r7.size(0) * i26];
                }
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:47' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:48' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        // 'EvalCurvStructNoCtx:49' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:50' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        EvalBSpline(spline->sp.Bl.handle, spline->sp.coeff, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        // 'EvalCurvStructNoCtx:51' otherwise
        // 'EvalCurvStructNoCtx:52' c_assert( false, 'Unknown Curve Type for Eval.\n' );
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
    // 'EvalCurvStructNoCtx:55' r1D = a   .* r1D;
    h_loop_ub = r1D.size(1);
    for (int i12{0}; i12 < h_loop_ub; i12++) {
        int j_loop_ub;
        j_loop_ub = r1D.size(0);
        for (int i14{0}; i14 < j_loop_ub; i14++) {
            r1D[i14 + r1D.size(0) * i12] = curv->a_param * r1D[i14 + r1D.size(0) * i12];
        }
    }
    // 'EvalCurvStructNoCtx:56' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    m_loop_ub = r2D.size(1);
    for (int i17{0}; i17 < m_loop_ub; i17++) {
        int q_loop_ub;
        q_loop_ub = r2D.size(0);
        for (int i21{0}; i21 < q_loop_ub; i21++) {
            r2D[i21 + r2D.size(0) * i17] = c * r2D[i21 + r2D.size(0) * i17];
        }
    }
    // 'EvalCurvStructNoCtx:57' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    t_loop_ub = r3D.size(1);
    for (int i24{0}; i24 < t_loop_ub; i24++) {
        int x_loop_ub;
        x_loop_ub = r3D.size(0);
        for (int i28{0}; i28 < x_loop_ub; i28++) {
            r3D[i28 + r3D.size(0) * i24] = b_c * r3D[i28 + r3D.size(0) * i24];
        }
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : const bool cfg_maskTot_data[]
//                const int cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &cfg_maskCart
//                const ::coder::array<bool, 2U> &cfg_maskRot
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
                           const ::coder::array<bool, 2U> &cfg_maskCart,
                           const ::coder::array<bool, 2U> &cfg_maskRot,
                           const ::coder::array<int, 1U> &cfg_indCart,
                           const ::coder::array<int, 1U> &cfg_indRot, int cfg_NumberAxis,
                           int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                           const CurvStruct *spline, double u_vec, ::coder::array<double, 1U> &r0D)
{
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    ::coder::array<double, 1U> r1D;
    ::coder::array<double, 1U> r2;
    ::coder::array<double, 1U> r2D;
    ::coder::array<double, 1U> r3;
    ::coder::array<double, 1U> r3D;
    ::coder::array<bool, 2U> b_cfg_maskTot_data;
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double d;
    double d1;
    double d2;
    double u_vec_tilda;
    int tmp_data[3];
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
        // 'EvalCurvStructNoCtx:62' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:63' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:65' else
        // 'EvalCurvStructNoCtx:66' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec > 1\n");
        fflush(stdout);
    }
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    if (u_vec < 0.0) {
        // 'EvalCurvStructNoCtx:11' u_vec( u_vec < 0.0 ) = 0.0;
        u_vec = 0.0;
        // 'EvalCurvStructNoCtx:11' printMsg( "Error : u_vec < 0\n" );
        //  printMsg : Print erro message according to the coder.target.
        // 'EvalCurvStructNoCtx:62' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:63' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:65' else
        // 'EvalCurvStructNoCtx:66' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec < 0\n");
        fflush(stdout);
    }
    //
    // 'EvalCurvStructNoCtx:15' Type  = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N   = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M   = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:20' r0D = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:21' r1D = r0D;
    // 'EvalCurvStructNoCtx:22' r2D = r0D;
    // 'EvalCurvStructNoCtx:23' r3D = r0D;
    // 'EvalCurvStructNoCtx:25' a = curv.a_param;
    // 'EvalCurvStructNoCtx:26' b = curv.b_param;
    // 'EvalCurvStructNoCtx:28' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv->a_param * u_vec + curv->b_param;
    // 'EvalCurvStructNoCtx:30' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:31' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:32' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:33' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:34' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:36' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:37' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:38' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        b_cfg_maskTot_data.set((bool *)&cfg_maskTot_data[0], cfg_maskTot_size[0],
                               cfg_maskTot_size[1]);
        b_EvalLine(curv->R0, curv->R1, u_vec_tilda, b_cfg_maskTot_data, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:39' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:40' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int loop_ub;
            int tmp_size;
            //  Only rotation
            // 'EvalCurvStructNoCtx:41' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:42'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart, dv, dv1, dv2, dv3);
            tmp_size = cfg_indCart.size(0);
            loop_ub = cfg_indCart.size(0);
            for (int i2{0}; i2 < loop_ub; i2++) {
                tmp_data[i2] = cfg_indCart[i2] - 1;
            }
            for (int i4{0}; i4 < tmp_size; i4++) {
                r0D[tmp_data[i4]] = dv[i4];
            }
        } else if (cfg_NRot > 0) {
            int b_loop_ub;
            // 'EvalCurvStructNoCtx:43' elseif( cfg.NRot > 0 )
            //  Only cartesian
            // 'EvalCurvStructNoCtx:44' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:45'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot, r, r1, r2, r3);
            b_loop_ub = r.size(0);
            for (int i3{0}; i3 < b_loop_ub; i3++) {
                r0D[cfg_indRot[i3] - 1] = r[i3];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:47' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:48' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int i9;
        // 'EvalCurvStructNoCtx:49' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:50' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        for (int i5{0}; i5 < c_loop_ub; i5++) {
            r0D[i5] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        d_loop_ub = spline->sp.coeff.size(0);
        for (int i6{0}; i6 < d_loop_ub; i6++) {
            r1D[i6] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        e_loop_ub = spline->sp.coeff.size(0);
        for (int i7{0}; i7 < e_loop_ub; i7++) {
            r2D[i7] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        f_loop_ub = spline->sp.coeff.size(0);
        for (int i8{0}; i8 < f_loop_ub; i8++) {
            r3D[i8] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i9 = spline->sp.coeff.size(0);
        for (int j{0}; j < i9; j++) {
            int g_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0D[j] = u_vec_tilda;
            g_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i10{0}; i10 < g_loop_ub; i10++) {
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
    default:
        // 'EvalCurvStructNoCtx:51' otherwise
        // 'EvalCurvStructNoCtx:52' c_assert( false, 'Unknown Curve Type for Eval.\n' );
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
    // 'EvalCurvStructNoCtx:55' r1D = a   .* r1D;
    // 'EvalCurvStructNoCtx:56' r2D = a^2 .* r2D;
    // 'EvalCurvStructNoCtx:57' r3D = a^3 .* r3D;
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : const bool cfg_maskTot_data[]
//                const int cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &cfg_maskCart
//                const ::coder::array<bool, 2U> &cfg_maskRot
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
                           const ::coder::array<bool, 2U> &cfg_maskCart,
                           const ::coder::array<bool, 2U> &cfg_maskRot,
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
    ::coder::array<double, 1U> r2;
    ::coder::array<double, 1U> r3;
    ::coder::array<bool, 2U> b_cfg_maskTot_data;
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
    int tmp_data[3];
    int d_loop_ub;
    int h_loop_ub;
    int loop_ub;
    char message[30];
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:6' if any( u_vec - 1.0 > 10 * eps )
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    //
    // 'EvalCurvStructNoCtx:15' Type  = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N   = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M   = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:20' r0D = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:22' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:23' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:25' a = curv.a_param;
    // 'EvalCurvStructNoCtx:26' b = curv.b_param;
    // 'EvalCurvStructNoCtx:28' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv->a_param + curv->b_param;
    // 'EvalCurvStructNoCtx:30' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:31' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:32' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:33' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:34' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:36' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:37' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:38' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        b_cfg_maskTot_data.set((bool *)&cfg_maskTot_data[0], cfg_maskTot_size[0],
                               cfg_maskTot_size[1]);
        b_EvalLine(curv->R0, curv->R1, u_vec_tilda, b_cfg_maskTot_data, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:39' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:40' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int b_loop_ub;
            int f_loop_ub;
            int k_loop_ub;
            int m_loop_ub;
            int tmp_size;
            //  Only rotation
            // 'EvalCurvStructNoCtx:41' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:42'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart, dv, dv1, dv2, dv3);
            tmp_size = cfg_indCart.size(0);
            b_loop_ub = cfg_indCart.size(0);
            for (int i3{0}; i3 < b_loop_ub; i3++) {
                tmp_data[i3] = cfg_indCart[i3] - 1;
            }
            for (int i5{0}; i5 < tmp_size; i5++) {
                r0D[tmp_data[i5]] = dv[i5];
            }
            tmp_size = cfg_indCart.size(0);
            f_loop_ub = cfg_indCart.size(0);
            for (int i8{0}; i8 < f_loop_ub; i8++) {
                tmp_data[i8] = cfg_indCart[i8] - 1;
            }
            for (int i11{0}; i11 < tmp_size; i11++) {
                r1D[tmp_data[i11]] = dv1[i11];
            }
            tmp_size = cfg_indCart.size(0);
            k_loop_ub = cfg_indCart.size(0);
            for (int i14{0}; i14 < k_loop_ub; i14++) {
                tmp_data[i14] = cfg_indCart[i14] - 1;
            }
            for (int i15{0}; i15 < tmp_size; i15++) {
                r2D[tmp_data[i15]] = dv2[i15];
            }
            tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            for (int i17{0}; i17 < m_loop_ub; i17++) {
                tmp_data[i17] = cfg_indCart[i17] - 1;
            }
            for (int i18{0}; i18 < tmp_size; i18++) {
                r3D[tmp_data[i18]] = dv3[i18];
            }
        } else if (cfg_NRot > 0) {
            int c_loop_ub;
            int e_loop_ub;
            int g_loop_ub;
            int i_loop_ub;
            // 'EvalCurvStructNoCtx:43' elseif( cfg.NRot > 0 )
            //  Only cartesian
            // 'EvalCurvStructNoCtx:44' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:45'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot, r, r1, r2, r3);
            c_loop_ub = r.size(0);
            for (int i4{0}; i4 < c_loop_ub; i4++) {
                r0D[cfg_indRot[i4] - 1] = r[i4];
            }
            e_loop_ub = r1.size(0);
            for (int i7{0}; i7 < e_loop_ub; i7++) {
                r1D[cfg_indRot[i7] - 1] = r1[i7];
            }
            g_loop_ub = r2.size(0);
            for (int i9{0}; i9 < g_loop_ub; i9++) {
                r2D[cfg_indRot[i9] - 1] = r2[i9];
            }
            i_loop_ub = r3.size(0);
            for (int i12{0}; i12 < i_loop_ub; i12++) {
                r3D[cfg_indRot[i12] - 1] = r3[i12];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:47' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:48' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int i21;
        int j_loop_ub;
        int l_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        // 'EvalCurvStructNoCtx:49' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:50' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        j_loop_ub = spline->sp.coeff.size(0);
        for (int i13{0}; i13 < j_loop_ub; i13++) {
            r0D[i13] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        l_loop_ub = spline->sp.coeff.size(0);
        for (int i16{0}; i16 < l_loop_ub; i16++) {
            r1D[i16] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        n_loop_ub = spline->sp.coeff.size(0);
        for (int i19{0}; i19 < n_loop_ub; i19++) {
            r2D[i19] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        o_loop_ub = spline->sp.coeff.size(0);
        for (int i20{0}; i20 < o_loop_ub; i20++) {
            r3D[i20] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i21 = spline->sp.coeff.size(0);
        for (int j{0}; j < i21; j++) {
            int p_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0D[j] = u_vec_tilda;
            p_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i22{0}; i22 < p_loop_ub; i22++) {
                b_spline[i22] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i22];
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
        // 'EvalCurvStructNoCtx:51' otherwise
        // 'EvalCurvStructNoCtx:52' c_assert( false, 'Unknown Curve Type for Eval.\n' );
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
    // 'EvalCurvStructNoCtx:55' r1D = a   .* r1D;
    loop_ub = r1D.size(0);
    for (int i2{0}; i2 < loop_ub; i2++) {
        r1D[i2] = curv->a_param * r1D[i2];
    }
    // 'EvalCurvStructNoCtx:56' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    d_loop_ub = r2D.size(0);
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        r2D[i6] = c * r2D[i6];
    }
    // 'EvalCurvStructNoCtx:57' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    h_loop_ub = r3D.size(0);
    for (int i10{0}; i10 < h_loop_ub; i10++) {
        r3D[i10] = b_c * r3D[i10];
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : const bool cfg_maskTot_data[]
//                const int cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &cfg_maskCart
//                const ::coder::array<bool, 2U> &cfg_maskRot
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
                           const ::coder::array<bool, 2U> &cfg_maskCart,
                           const ::coder::array<bool, 2U> &cfg_maskRot,
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
    ::coder::array<double, 1U> r2;
    ::coder::array<double, 1U> r3;
    ::coder::array<bool, 2U> b_cfg_maskTot_data;
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv3[3];
    double b_c;
    double c;
    double d;
    double d1;
    double d2;
    int tmp_data[3];
    int d_loop_ub;
    int h_loop_ub;
    int loop_ub;
    char message[30];
    // 'EvalCurvStructNoCtx:5' coder.inline("never");
    // 'EvalCurvStructNoCtx:6' if any( u_vec - 1.0 > 10 * eps )
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    //
    // 'EvalCurvStructNoCtx:15' Type  = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N   = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M   = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:20' r0D = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:22' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:23' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:25' a = curv.a_param;
    // 'EvalCurvStructNoCtx:26' b = curv.b_param;
    // 'EvalCurvStructNoCtx:28' u_vec_tilda = a * u_vec + b;
    // 'EvalCurvStructNoCtx:30' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:31' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:32' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:33' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:34' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:36' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:37' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:38' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        b_cfg_maskTot_data.set((bool *)&cfg_maskTot_data[0], cfg_maskTot_size[0],
                               cfg_maskTot_size[1]);
        b_EvalLine(curv->R0, curv->R1, curv->b_param, b_cfg_maskTot_data, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:39' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:40' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int b_loop_ub;
            int f_loop_ub;
            int k_loop_ub;
            int m_loop_ub;
            int tmp_size;
            //  Only rotation
            // 'EvalCurvStructNoCtx:41' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:42'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        curv->b_param, cfg_maskCart, dv, dv1, dv2, dv3);
            tmp_size = cfg_indCart.size(0);
            b_loop_ub = cfg_indCart.size(0);
            for (int i3{0}; i3 < b_loop_ub; i3++) {
                tmp_data[i3] = cfg_indCart[i3] - 1;
            }
            for (int i5{0}; i5 < tmp_size; i5++) {
                r0D[tmp_data[i5]] = dv[i5];
            }
            tmp_size = cfg_indCart.size(0);
            f_loop_ub = cfg_indCart.size(0);
            for (int i8{0}; i8 < f_loop_ub; i8++) {
                tmp_data[i8] = cfg_indCart[i8] - 1;
            }
            for (int i11{0}; i11 < tmp_size; i11++) {
                r1D[tmp_data[i11]] = dv1[i11];
            }
            tmp_size = cfg_indCart.size(0);
            k_loop_ub = cfg_indCart.size(0);
            for (int i14{0}; i14 < k_loop_ub; i14++) {
                tmp_data[i14] = cfg_indCart[i14] - 1;
            }
            for (int i15{0}; i15 < tmp_size; i15++) {
                r2D[tmp_data[i15]] = dv2[i15];
            }
            tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            for (int i17{0}; i17 < m_loop_ub; i17++) {
                tmp_data[i17] = cfg_indCart[i17] - 1;
            }
            for (int i18{0}; i18 < tmp_size; i18++) {
                r3D[tmp_data[i18]] = dv3[i18];
            }
        } else if (cfg_NRot > 0) {
            int c_loop_ub;
            int e_loop_ub;
            int g_loop_ub;
            int i_loop_ub;
            // 'EvalCurvStructNoCtx:43' elseif( cfg.NRot > 0 )
            //  Only cartesian
            // 'EvalCurvStructNoCtx:44' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:45'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, curv->b_param, cfg_maskRot, r, r1, r2, r3);
            c_loop_ub = r.size(0);
            for (int i4{0}; i4 < c_loop_ub; i4++) {
                r0D[cfg_indRot[i4] - 1] = r[i4];
            }
            e_loop_ub = r1.size(0);
            for (int i7{0}; i7 < e_loop_ub; i7++) {
                r1D[cfg_indRot[i7] - 1] = r1[i7];
            }
            g_loop_ub = r2.size(0);
            for (int i9{0}; i9 < g_loop_ub; i9++) {
                r2D[cfg_indRot[i9] - 1] = r2[i9];
            }
            i_loop_ub = r3.size(0);
            for (int i12{0}; i12 < i_loop_ub; i12++) {
                r3D[cfg_indRot[i12] - 1] = r3[i12];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:47' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:48' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, curv->b_param, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int i21;
        int j_loop_ub;
        int l_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        // 'EvalCurvStructNoCtx:49' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:50' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        j_loop_ub = spline->sp.coeff.size(0);
        for (int i13{0}; i13 < j_loop_ub; i13++) {
            r0D[i13] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        l_loop_ub = spline->sp.coeff.size(0);
        for (int i16{0}; i16 < l_loop_ub; i16++) {
            r1D[i16] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        n_loop_ub = spline->sp.coeff.size(0);
        for (int i19{0}; i19 < n_loop_ub; i19++) {
            r2D[i19] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        o_loop_ub = spline->sp.coeff.size(0);
        for (int i20{0}; i20 < o_loop_ub; i20++) {
            r3D[i20] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i21 = spline->sp.coeff.size(0);
        for (int j{0}; j < i21; j++) {
            int p_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0D[j] = curv->b_param;
            p_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i22{0}; i22 < p_loop_ub; i22++) {
                b_spline[i22] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i22];
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
        // 'EvalCurvStructNoCtx:51' otherwise
        // 'EvalCurvStructNoCtx:52' c_assert( false, 'Unknown Curve Type for Eval.\n' );
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
    // 'EvalCurvStructNoCtx:55' r1D = a   .* r1D;
    loop_ub = r1D.size(0);
    for (int i2{0}; i2 < loop_ub; i2++) {
        r1D[i2] = curv->a_param * r1D[i2];
    }
    // 'EvalCurvStructNoCtx:56' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    d_loop_ub = r2D.size(0);
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        r2D[i6] = c * r2D[i6];
    }
    // 'EvalCurvStructNoCtx:57' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    h_loop_ub = r3D.size(0);
    for (int i10{0}; i10 < h_loop_ub; i10++) {
        r3D[i10] = b_c * r3D[i10];
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : const bool cfg_maskTot_data[]
//                const int cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &cfg_maskCart
//                const ::coder::array<bool, 2U> &cfg_maskRot
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
                           const ::coder::array<bool, 2U> &cfg_maskCart,
                           const ::coder::array<bool, 2U> &cfg_maskRot,
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
    ::coder::array<double, 1U> r2;
    ::coder::array<double, 1U> r3;
    ::coder::array<bool, 2U> b_cfg_maskTot_data;
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
    int tmp_data[3];
    int d_loop_ub;
    int h_loop_ub;
    int loop_ub;
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
        // 'EvalCurvStructNoCtx:62' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:63' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:65' else
        // 'EvalCurvStructNoCtx:66' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec > 1\n");
        fflush(stdout);
    }
    // 'EvalCurvStructNoCtx:10' if any( u_vec < 0.0 )
    if (u_vec < 0.0) {
        // 'EvalCurvStructNoCtx:11' u_vec( u_vec < 0.0 ) = 0.0;
        u_vec = 0.0;
        // 'EvalCurvStructNoCtx:11' printMsg( "Error : u_vec < 0\n" );
        //  printMsg : Print erro message according to the coder.target.
        // 'EvalCurvStructNoCtx:62' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:63' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:65' else
        // 'EvalCurvStructNoCtx:66' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec < 0\n");
        fflush(stdout);
    }
    //
    // 'EvalCurvStructNoCtx:15' Type  = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N   = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M   = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:20' r0D = zeros( M, N );
    r0D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:21' r1D = r0D;
    r1D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:22' r2D = r0D;
    r2D.set_size(cfg_NumberAxis);
    // 'EvalCurvStructNoCtx:23' r3D = r0D;
    r3D.set_size(cfg_NumberAxis);
    for (int i{0}; i < cfg_NumberAxis; i++) {
        r0D[i] = 0.0;
        r1D[i] = 0.0;
        r2D[i] = 0.0;
        r3D[i] = 0.0;
    }
    // 'EvalCurvStructNoCtx:25' a = curv.a_param;
    // 'EvalCurvStructNoCtx:26' b = curv.b_param;
    // 'EvalCurvStructNoCtx:28' u_vec_tilda = a * u_vec + b;
    u_vec_tilda = curv->a_param * u_vec + curv->b_param;
    // 'EvalCurvStructNoCtx:30' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:31' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:32' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:33' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:34' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:36' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:37' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:38' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        b_cfg_maskTot_data.set((bool *)&cfg_maskTot_data[0], cfg_maskTot_size[0],
                               cfg_maskTot_size[1]);
        b_EvalLine(curv->R0, curv->R1, u_vec_tilda, b_cfg_maskTot_data, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:39' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:40' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int b_loop_ub;
            int f_loop_ub;
            int k_loop_ub;
            int m_loop_ub;
            int tmp_size;
            //  Only rotation
            // 'EvalCurvStructNoCtx:41' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:42'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            b_EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                        u_vec_tilda, cfg_maskCart, dv, dv1, dv2, dv3);
            tmp_size = cfg_indCart.size(0);
            b_loop_ub = cfg_indCart.size(0);
            for (int i3{0}; i3 < b_loop_ub; i3++) {
                tmp_data[i3] = cfg_indCart[i3] - 1;
            }
            for (int i5{0}; i5 < tmp_size; i5++) {
                r0D[tmp_data[i5]] = dv[i5];
            }
            tmp_size = cfg_indCart.size(0);
            f_loop_ub = cfg_indCart.size(0);
            for (int i8{0}; i8 < f_loop_ub; i8++) {
                tmp_data[i8] = cfg_indCart[i8] - 1;
            }
            for (int i11{0}; i11 < tmp_size; i11++) {
                r1D[tmp_data[i11]] = dv1[i11];
            }
            tmp_size = cfg_indCart.size(0);
            k_loop_ub = cfg_indCart.size(0);
            for (int i14{0}; i14 < k_loop_ub; i14++) {
                tmp_data[i14] = cfg_indCart[i14] - 1;
            }
            for (int i15{0}; i15 < tmp_size; i15++) {
                r2D[tmp_data[i15]] = dv2[i15];
            }
            tmp_size = cfg_indCart.size(0);
            m_loop_ub = cfg_indCart.size(0);
            for (int i17{0}; i17 < m_loop_ub; i17++) {
                tmp_data[i17] = cfg_indCart[i17] - 1;
            }
            for (int i18{0}; i18 < tmp_size; i18++) {
                r3D[tmp_data[i18]] = dv3[i18];
            }
        } else if (cfg_NRot > 0) {
            int c_loop_ub;
            int e_loop_ub;
            int g_loop_ub;
            int i_loop_ub;
            // 'EvalCurvStructNoCtx:43' elseif( cfg.NRot > 0 )
            //  Only cartesian
            // 'EvalCurvStructNoCtx:44' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:45'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            b_EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot, r, r1, r2, r3);
            c_loop_ub = r.size(0);
            for (int i4{0}; i4 < c_loop_ub; i4++) {
                r0D[cfg_indRot[i4] - 1] = r[i4];
            }
            e_loop_ub = r1.size(0);
            for (int i7{0}; i7 < e_loop_ub; i7++) {
                r1D[cfg_indRot[i7] - 1] = r1[i7];
            }
            g_loop_ub = r2.size(0);
            for (int i9{0}; i9 < g_loop_ub; i9++) {
                r2D[cfg_indRot[i9] - 1] = r2[i9];
            }
            i_loop_ub = r3.size(0);
            for (int i12{0}; i12 < i_loop_ub; i12++) {
                r3D[cfg_indRot[i12] - 1] = r3[i12];
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:47' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:48' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline: {
        int i21;
        int j_loop_ub;
        int l_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        // 'EvalCurvStructNoCtx:49' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:50' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
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
        j_loop_ub = spline->sp.coeff.size(0);
        for (int i13{0}; i13 < j_loop_ub; i13++) {
            r0D[i13] = 0.0;
        }
        // 'EvalBSpline:18' r1D = r0D;
        r1D.set_size(spline->sp.coeff.size(0));
        l_loop_ub = spline->sp.coeff.size(0);
        for (int i16{0}; i16 < l_loop_ub; i16++) {
            r1D[i16] = 0.0;
        }
        // 'EvalBSpline:18' r2D = r1D;
        r2D.set_size(spline->sp.coeff.size(0));
        n_loop_ub = spline->sp.coeff.size(0);
        for (int i19{0}; i19 < n_loop_ub; i19++) {
            r2D[i19] = 0.0;
        }
        // 'EvalBSpline:18' r3D = r2D;
        r3D.set_size(spline->sp.coeff.size(0));
        o_loop_ub = spline->sp.coeff.size(0);
        for (int i20{0}; i20 < o_loop_ub; i20++) {
            r3D[i20] = 0.0;
        }
        // 'EvalBSpline:20' for j = 1 : M
        i21 = spline->sp.coeff.size(0);
        for (int j{0}; j < i21; j++) {
            int p_loop_ub;
            // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
            // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, :
            // ), u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd =
            // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6'
            // xddd    = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r0D[j] = u_vec_tilda;
            p_loop_ub = spline->sp.coeff.size(1);
            b_spline.set_size(1, spline->sp.coeff.size(1));
            for (int i22{0}; i22 < p_loop_ub; i22++) {
                b_spline[i22] = spline->sp.coeff[j + spline->sp.coeff.size(0) * i22];
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
        // 'EvalCurvStructNoCtx:51' otherwise
        // 'EvalCurvStructNoCtx:52' c_assert( false, 'Unknown Curve Type for Eval.\n' );
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
    // 'EvalCurvStructNoCtx:55' r1D = a   .* r1D;
    loop_ub = r1D.size(0);
    for (int i2{0}; i2 < loop_ub; i2++) {
        r1D[i2] = curv->a_param * r1D[i2];
    }
    // 'EvalCurvStructNoCtx:56' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    d_loop_ub = r2D.size(0);
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        r2D[i6] = c * r2D[i6];
    }
    // 'EvalCurvStructNoCtx:57' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    h_loop_ub = r3D.size(0);
    for (int i10{0}; i10 < h_loop_ub; i10++) {
        r3D[i10] = b_c * r3D[i10];
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalCurvStructNoCtx( cfg, curv, spline, u_vec )
//
//
// Arguments    : const bool cfg_maskTot_data[]
//                const int cfg_maskTot_size[2]
//                const ::coder::array<bool, 2U> &cfg_maskCart
//                const ::coder::array<bool, 2U> &cfg_maskRot
//                const int cfg_indCart_data[]
//                const int cfg_indRot_data[]
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
void f_EvalCurvStructNoCtx(const bool cfg_maskTot_data[], const int cfg_maskTot_size[2],
                           const ::coder::array<bool, 2U> &cfg_maskCart,
                           const ::coder::array<bool, 2U> &cfg_maskRot,
                           const int cfg_indCart_data[], const int cfg_indRot_data[],
                           int cfg_NumberAxis, int cfg_NCart, int cfg_NRot, const CurvStruct *curv,
                           const CurvStruct *spline, ::coder::array<double, 2U> &u_vec,
                           ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D,
                           ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r3;
    ::coder::array<double, 2U> r4;
    ::coder::array<double, 2U> r5;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> r7;
    ::coder::array<double, 2U> u_vec_tilda;
    ::coder::array<bool, 2U> b_cfg_maskTot_data;
    ::coder::array<bool, 2U> x;
    double b_c;
    double c;
    int b_k;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int k;
    int loop_ub;
    int m_loop_ub;
    int t_loop_ub;
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
        // 'EvalCurvStructNoCtx:62' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:63' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:65' else
        // 'EvalCurvStructNoCtx:66' fprintf(err_msg);
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
        // 'EvalCurvStructNoCtx:62' err_msg = "EvalCurvStruct : " + err_msg;
        // 'EvalCurvStructNoCtx:63' if coder.target('matlab')
        // 'EvalCurvStructNoCtx:65' else
        // 'EvalCurvStructNoCtx:66' fprintf(err_msg);
        printf("EvalCurvStruct : Error : u_vec < 0\n");
        fflush(stdout);
    }
    //
    // 'EvalCurvStructNoCtx:15' Type  = curv.Info.Type;
    //
    // 'EvalCurvStructNoCtx:17' N   = numel( u_vec );
    // 'EvalCurvStructNoCtx:18' M   = cfg.NumberAxis;
    // 'EvalCurvStructNoCtx:20' r0D = zeros( M, N );
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
    // 'EvalCurvStructNoCtx:22' r2D = r0D;
    r2D.set_size(cfg_NumberAxis, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i6{0}; i6 < e_loop_ub; i6++) {
        for (int i7{0}; i7 < cfg_NumberAxis; i7++) {
            r2D[i7 + r2D.size(0) * i6] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:23' r3D = r0D;
    r3D.set_size(cfg_NumberAxis, u_vec.size(1));
    f_loop_ub = u_vec.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        for (int i9{0}; i9 < cfg_NumberAxis; i9++) {
            r3D[i9 + r3D.size(0) * i8] = 0.0;
        }
    }
    // 'EvalCurvStructNoCtx:25' a = curv.a_param;
    // 'EvalCurvStructNoCtx:26' b = curv.b_param;
    // 'EvalCurvStructNoCtx:28' u_vec_tilda = a * u_vec + b;
    u_vec_tilda.set_size(1, u_vec.size(1));
    g_loop_ub = u_vec.size(1);
    for (int i10{0}; i10 < g_loop_ub; i10++) {
        u_vec_tilda[i10] = curv->a_param * u_vec[i10] + curv->b_param;
    }
    // 'EvalCurvStructNoCtx:30' indC     = cfg.indCart;
    // 'EvalCurvStructNoCtx:31' indR     = cfg.indRot;
    // 'EvalCurvStructNoCtx:32' maskTot  = cfg.maskTot;
    // 'EvalCurvStructNoCtx:33' maskRot  = cfg.maskRot;
    // 'EvalCurvStructNoCtx:34' maskCart = cfg.maskCart;
    // 'EvalCurvStructNoCtx:36' switch Type
    switch (curv->Info.Type) {
    case CurveType_Line:
        // 'EvalCurvStructNoCtx:37' case CurveType.Line
        //  Line (G01)
        // 'EvalCurvStructNoCtx:38' [r0D, r1D, r2D, r3D] = EvalLine( curv, u_vec_tilda, maskTot );
        b_cfg_maskTot_data.set((bool *)&cfg_maskTot_data[0], cfg_maskTot_size[0],
                               cfg_maskTot_size[1]);
        EvalLine(curv->R0, curv->R1, u_vec_tilda, b_cfg_maskTot_data, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix: {
        // 'EvalCurvStructNoCtx:39' case CurveType.Helix
        //  Arc of circle / helix (G02, G03)
        // 'EvalCurvStructNoCtx:40' if( cfg.NCart > 0 )
        if (cfg_NCart > 0) {
            int i_loop_ub;
            int l_loop_ub;
            int p_loop_ub;
            int u_loop_ub;
            //  Only rotation
            // 'EvalCurvStructNoCtx:41' [r0D( indC, : ), r1D( indC, : ), r2D( indC, : ), r3D( indC,
            // : )] = ... 'EvalCurvStructNoCtx:42'                 EvalHelix( curv, u_vec_tilda,
            // maskCart );
            EvalHelix(curv->R0, curv->CorrectedHelixCenter, curv->evec, curv->theta, curv->pitch,
                      u_vec_tilda, cfg_maskCart, r, r1, r2, r3);
            i_loop_ub = r.size(1);
            for (int i13{0}; i13 < i_loop_ub; i13++) {
                r0D[(cfg_indCart_data[0] + r0D.size(0) * i13) - 1] = r[3 * i13];
                r0D[(cfg_indCart_data[1] + r0D.size(0) * i13) - 1] = r[3 * i13 + 1];
                r0D[(cfg_indCart_data[2] + r0D.size(0) * i13) - 1] = r[3 * i13 + 2];
            }
            l_loop_ub = r1.size(1);
            for (int i16{0}; i16 < l_loop_ub; i16++) {
                r1D[(cfg_indCart_data[0] + r1D.size(0) * i16) - 1] = r1[3 * i16];
                r1D[(cfg_indCart_data[1] + r1D.size(0) * i16) - 1] = r1[3 * i16 + 1];
                r1D[(cfg_indCart_data[2] + r1D.size(0) * i16) - 1] = r1[3 * i16 + 2];
            }
            p_loop_ub = r2.size(1);
            for (int i20{0}; i20 < p_loop_ub; i20++) {
                r2D[(cfg_indCart_data[0] + r2D.size(0) * i20) - 1] = r2[3 * i20];
                r2D[(cfg_indCart_data[1] + r2D.size(0) * i20) - 1] = r2[3 * i20 + 1];
                r2D[(cfg_indCart_data[2] + r2D.size(0) * i20) - 1] = r2[3 * i20 + 2];
            }
            u_loop_ub = r3.size(1);
            for (int i25{0}; i25 < u_loop_ub; i25++) {
                r3D[(cfg_indCart_data[0] + r3D.size(0) * i25) - 1] = r3[3 * i25];
                r3D[(cfg_indCart_data[1] + r3D.size(0) * i25) - 1] = r3[3 * i25 + 1];
                r3D[(cfg_indCart_data[2] + r3D.size(0) * i25) - 1] = r3[3 * i25 + 2];
            }
        } else if (cfg_NRot > 0) {
            int k_loop_ub;
            int n_loop_ub;
            int r_loop_ub;
            int v_loop_ub;
            // 'EvalCurvStructNoCtx:43' elseif( cfg.NRot > 0 )
            //  Only cartesian
            // 'EvalCurvStructNoCtx:44' [r0D( indR, : ), r1D( indR, : ), r2D( indR, : ), r3D( indR,
            // : )] = ... 'EvalCurvStructNoCtx:45'                 EvalLine( curv, u_vec_tilda,
            // maskRot );
            EvalLine(curv->R0, curv->R1, u_vec_tilda, cfg_maskRot, r4, r5, r6, r7);
            k_loop_ub = r4.size(1);
            for (int i15{0}; i15 < k_loop_ub; i15++) {
                int o_loop_ub;
                o_loop_ub = r4.size(0);
                for (int i19{0}; i19 < o_loop_ub; i19++) {
                    r0D[(cfg_indRot_data[i19] + r0D.size(0) * i15) - 1] =
                        r4[i19 + r4.size(0) * i15];
                }
            }
            n_loop_ub = r5.size(1);
            for (int i18{0}; i18 < n_loop_ub; i18++) {
                int s_loop_ub;
                s_loop_ub = r5.size(0);
                for (int i23{0}; i23 < s_loop_ub; i23++) {
                    r1D[(cfg_indRot_data[i23] + r1D.size(0) * i18) - 1] =
                        r5[i23 + r5.size(0) * i18];
                }
            }
            r_loop_ub = r6.size(1);
            for (int i22{0}; i22 < r_loop_ub; i22++) {
                int w_loop_ub;
                w_loop_ub = r6.size(0);
                for (int i27{0}; i27 < w_loop_ub; i27++) {
                    r2D[(cfg_indRot_data[i27] + r2D.size(0) * i22) - 1] =
                        r6[i27 + r6.size(0) * i22];
                }
            }
            v_loop_ub = r7.size(1);
            for (int i26{0}; i26 < v_loop_ub; i26++) {
                int y_loop_ub;
                y_loop_ub = r7.size(0);
                for (int i29{0}; i29 < y_loop_ub; i29++) {
                    r3D[(cfg_indRot_data[i29] + r3D.size(0) * i26) - 1] =
                        r7[i29 + r7.size(0) * i26];
                }
            }
        }
    } break;
    case CurveType_TransP5:
        // 'EvalCurvStructNoCtx:47' case CurveType.TransP5
        //  Polynomial transition
        // 'EvalCurvStructNoCtx:48' [r0D, r1D, r2D, r3D]    = EvalTransP5( curv, u_vec_tilda,
        // cfg.NumberAxis );
        EvalTransP5(curv->CoeffP5, u_vec_tilda, cfg_NumberAxis, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        // 'EvalCurvStructNoCtx:49' case CurveType.Spline
        //  Spline
        // 'EvalCurvStructNoCtx:50' [ r0D, r1D, r2D, r3D ]  = EvalBSpline( spline, u_vec_tilda );
        EvalBSpline(spline->sp.Bl.handle, spline->sp.coeff, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        // 'EvalCurvStructNoCtx:51' otherwise
        // 'EvalCurvStructNoCtx:52' c_assert( false, 'Unknown Curve Type for Eval.\n' );
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
    // 'EvalCurvStructNoCtx:55' r1D = a   .* r1D;
    h_loop_ub = r1D.size(1);
    for (int i12{0}; i12 < h_loop_ub; i12++) {
        int j_loop_ub;
        j_loop_ub = r1D.size(0);
        for (int i14{0}; i14 < j_loop_ub; i14++) {
            r1D[i14 + r1D.size(0) * i12] = curv->a_param * r1D[i14 + r1D.size(0) * i12];
        }
    }
    // 'EvalCurvStructNoCtx:56' r2D = a^2 .* r2D;
    c = curv->a_param * curv->a_param;
    m_loop_ub = r2D.size(1);
    for (int i17{0}; i17 < m_loop_ub; i17++) {
        int q_loop_ub;
        q_loop_ub = r2D.size(0);
        for (int i21{0}; i21 < q_loop_ub; i21++) {
            r2D[i21 + r2D.size(0) * i17] = c * r2D[i21 + r2D.size(0) * i17];
        }
    }
    // 'EvalCurvStructNoCtx:57' r3D = a^3 .* r3D;
    b_c = std::pow(curv->a_param, 3.0);
    t_loop_ub = r3D.size(1);
    for (int i24{0}; i24 < t_loop_ub; i24++) {
        int x_loop_ub;
        x_loop_ub = r3D.size(0);
        for (int i28{0}; i28 < x_loop_ub; i28++) {
            r3D[i28 + r3D.size(0) * i24] = b_c * r3D[i28 + r3D.size(0) * i24];
        }
    }
}

} // namespace ocn

//
// File trailer for EvalCurvStructNoCtx.cpp
//
// [EOF]
//
