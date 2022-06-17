//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcBspline_Lee.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:17:54
//

// Include Files
#include "CalcBspline_Lee.h"
#include "bspline_eval.h"
#include "constrBaseSpline.h"
#include "mldivide.h"
#include "opencn_matlab_types3.h"
#include "sum.h"
#include "coder_array.h"
#include "src/c_spline.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function [ spnD ] = CalcBspline_Lee( cfg, points )
//
// CalcBspline_Lee :
//
//  INPUT
//  cfg       : struct : Configuration variables
//  points    :   nDxN : Set of points in n dimension for the spline
//
//  OUTPUT
//  spnD      : struct : Output spline structure
//
// Arguments    : int cfg_NumberAxis
//                int cfg_LeeSplineDegree
//                const ::coder::array<double, 2U> &points
//                int *spnD_Bl_ncoeff
//                ::coder::array<double, 2U> &spnD_Bl_breakpoints
//                unsigned long *spnD_Bl_handle
//                int *spnD_Bl_order
//                ::coder::array<double, 2U> &spnD_coeff
//                ::coder::array<double, 2U> &spnD_knots
//                double *spnD_Ltot
//                ::coder::array<double, 2U> &spnD_Lk
// Return Type  : void
//
namespace ocn {
void CalcBspline_Lee(int cfg_NumberAxis, int cfg_LeeSplineDegree,
                     const ::coder::array<double, 2U> &points, int *spnD_Bl_ncoeff,
                     ::coder::array<double, 2U> &spnD_Bl_breakpoints, unsigned long *spnD_Bl_handle,
                     int *spnD_Bl_order, ::coder::array<double, 2U> &spnD_coeff,
                     ::coder::array<double, 2U> &spnD_knots, double *spnD_Ltot,
                     ::coder::array<double, 2U> &spnD_Lk)
{
    ::coder::array<double, 2U> BasisVal;
    ::coder::array<double, 2U> BasisValDD0;
    ::coder::array<double, 2U> BasisValDD1;
    ::coder::array<double, 2U> X;
    ::coder::array<double, 2U> Xdd;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> b_BasisValDD0;
    ::coder::array<double, 2U> b_coef;
    ::coder::array<double, 2U> b_y1;
    ::coder::array<double, 2U> breakpoints;
    ::coder::array<double, 2U> du_tmp;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> u;
    ::coder::array<double, 2U> xddd;
    ::coder::array<signed char, 2U> coef;
    BaseSplineStruct expl_temp;
    double b_u;
    double d1;
    double d2;
    double d3;
    unsigned long h;
    int b_input_sizes_idx_0;
    int b_input_sizes_idx_0_tmp;
    int b_m;
    int b_result;
    int c_loop_ub;
    int dimSize;
    int e_input_sizes_idx_0;
    int e_loop_ub;
    int g_input_sizes_idx_0;
    int g_loop_ub;
    int h_loop_ub;
    int i16;
    int i29;
    int i9;
    int i_loop_ub;
    int input_sizes_idx_0_tmp;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int loop_ub_tmp;
    int result;
    int scalarLB;
    int u0;
    int u_loop_ub;
    int vectorUB;
    int w_loop_ub;
    int x_loop_ub;
    int y;
    signed char c_input_sizes_idx_0;
    signed char d_input_sizes_idx_0;
    signed char f_input_sizes_idx_0;
    signed char input_sizes_idx_0;
    bool b_empty_non_axis_sizes;
    bool empty_non_axis_sizes;
    // 'CalcBspline_Lee:11' [ ~, N ] = size( points );
    //  number of points in nD space
    // 'CalcBspline_Lee:12' nAxis    = cfg.NumberAxis;
    // 'CalcBspline_Lee:13' nMult    = cfg.LeeSplineDegree - 1;
    //  Number of multiplicity at start and end ( clamped BSpline )
    // 'CalcBspline_Lee:14' nCoeff   = N + 2;
    // 'CalcBspline_Lee:16' du     = sum( ( diff( points.' ).^2 ).' );
    du_tmp.set_size(points.size(1), points.size(0));
    loop_ub = points.size(0);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = points.size(1);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            du_tmp[i1 + du_tmp.size(0) * i] = points[i + points.size(0) * i1];
        }
    }
    // 'CalcBspline_Lee:17' u      = cumsum( [ 0, du.^( 1 / 4 ) ] );
    dimSize = du_tmp.size(0);
    u0 = du_tmp.size(0) - 1;
    if (u0 <= 1) {
        y = u0;
    } else {
        y = 1;
    }
    if (y < 1) {
        b_y1.set_size(0, du_tmp.size(1));
    } else {
        b_y1.set_size(du_tmp.size(0) - 1, du_tmp.size(1));
        if ((du_tmp.size(0) - 1 != 0) && (du_tmp.size(1) != 0)) {
            int iyStart;
            int nHigh;
            nHigh = du_tmp.size(1);
            iyStart = 0;
            for (int b_r{0}; b_r < nHigh; b_r++) {
                double work_data;
                int ixLead_tmp;
                ixLead_tmp = b_r * dimSize;
                work_data = du_tmp[ixLead_tmp];
                for (int m{2}; m <= dimSize; m++) {
                    double d;
                    double tmp1;
                    tmp1 = du_tmp[(ixLead_tmp + m) - 1];
                    d = tmp1;
                    tmp1 -= work_data;
                    work_data = d;
                    b_y1[(iyStart + m) - 2] = tmp1;
                }
                iyStart = (iyStart + dimSize) - 1;
            }
        }
    }
    r.set_size(b_y1.size(0), b_y1.size(1));
    c_loop_ub = b_y1.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = b_y1.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            double varargin_1;
            varargin_1 = b_y1[i3 + b_y1.size(0) * i2];
            r[i3 + r.size(0) * i2] = std::pow(varargin_1, 2.0);
        }
    }
    r1.set_size(r.size(1), r.size(0));
    e_loop_ub = r.size(0);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        int f_loop_ub;
        f_loop_ub = r.size(1);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            r1[i5 + r1.size(0) * i4] = r[i4 + r.size(0) * i5];
        }
    }
    coder::sum(r1, r2);
    r2.set_size(1, r2.size(1));
    g_loop_ub = r2.size(1);
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        double b_varargin_1;
        b_varargin_1 = r2[i6];
        r2[i6] = std::pow(b_varargin_1, 0.25);
    }
    u.set_size(1, r2.size(1) + 1);
    u[0] = 0.0;
    h_loop_ub = r2.size(1);
    for (int i7{0}; i7 < h_loop_ub; i7++) {
        u[i7 + 1] = r2[i7];
    }
    if (u.size(1) != 1) {
        int i8;
        i8 = u.size(1);
        for (int k{0}; k <= i8 - 2; k++) {
            u[k + 1] = u[k] + u[k + 1];
        }
    }
    // 'CalcBspline_Lee:18' u      = u / u( end );
    b_u = u[u.size(1) - 1];
    u.set_size(1, u.size(1));
    i_loop_ub = u.size(1);
    scalarLB = (u.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i9 = 0; i9 <= vectorUB; i9 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&u[i9]);
        _mm_storeu_pd(&u[i9], _mm_div_pd(r3, _mm_set1_pd(b_u)));
    }
    for (i9 = scalarLB; i9 < i_loop_ub; i9++) {
        u[i9] = u[i9] / b_u;
    }
    //  normalize knots to interval [0...1]
    // 'CalcBspline_Lee:19' knots  = [ zeros( 1, nMult ), u, ones( 1, nMult ) ];
    spnD_knots.set_size(1, ((cfg_LeeSplineDegree + u.size(1)) + cfg_LeeSplineDegree) - 2);
    loop_ub_tmp = cfg_LeeSplineDegree - 1;
    for (int i10{0}; i10 < loop_ub_tmp; i10++) {
        spnD_knots[i10] = 0.0;
    }
    j_loop_ub = u.size(1);
    for (int i11{0}; i11 < j_loop_ub; i11++) {
        spnD_knots[(i11 + cfg_LeeSplineDegree) - 1] = u[i11];
    }
    for (int i12{0}; i12 < loop_ub_tmp; i12++) {
        spnD_knots[((i12 + cfg_LeeSplineDegree) + u.size(1)) - 1] = 1.0;
    }
    // 'CalcBspline_Lee:21' Bl = bspline_create( cfg.LeeSplineDegree, u );
    // 'bspline_create:2' if coder.target('rtw') || coder.target('mex')
    // 'bspline_create:3' nbreak = length(breakpoints);
    // 'bspline_create:4' ncoeff = nbreak + degree - 2;
    // 'bspline_create:5' h = uint64(0);
    // 'bspline_create:7' coder.updateBuildInfo('addSourceFiles','c_spline.c', '$(START_DIR)/src');
    // 'bspline_create:8' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_create:9' coder.cinclude('src/c_spline.h');
    // 'bspline_create:10' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), degree,
    // breakpoints, int32(nbreak) );
    breakpoints.set_size(1, u.size(1));
    k_loop_ub = u.size(1);
    for (int i13{0}; i13 < k_loop_ub; i13++) {
        breakpoints[i13] = u[i13];
    }
    c_bspline_create_with_breakpoints(&h, cfg_LeeSplineDegree, &breakpoints[0], u.size(1));
    // 'bspline_create:11' Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
    constrBaseSpline((u.size(1) + cfg_LeeSplineDegree) - 2, u, h, cfg_LeeSplineDegree, &expl_temp);
    // 'CalcBspline_Lee:23' BasisVal    = zeros( N, nCoeff );
    BasisVal.set_size(points.size(1), points.size(1) + 2);
    //  preallocation
    // 'CalcBspline_Lee:24' BasisValDD0 = zeros( 1, nCoeff );
    BasisValDD0.set_size(1, points.size(1) + 2);
    //  preallocation
    // 'CalcBspline_Lee:25' BasisValDD1 = zeros( 1, nCoeff );
    BasisValDD1.set_size(1, points.size(1) + 2);
    //  preallocation
    //
    // 'CalcBspline_Lee:27' coef        = eye( nCoeff );
    b_m = points.size(1) + 1;
    coef.set_size(points.size(1) + 2, points.size(1) + 2);
    l_loop_ub = points.size(1) + 2;
    for (int i14{0}; i14 < l_loop_ub; i14++) {
        int m_loop_ub;
        m_loop_ub = points.size(1) + 2;
        for (int i15{0}; i15 < m_loop_ub; i15++) {
            coef[i15 + coef.size(0) * i14] = 0;
        }
    }
    for (int b_k{0}; b_k <= b_m; b_k++) {
        coef[b_k + coef.size(0) * b_k] = 1;
    }
    // 'CalcBspline_Lee:29' for k = 1: nCoeff
    i16 = points.size(1) + 1;
    for (int c_k{0}; c_k <= i16; c_k++) {
        int i21;
        int n_loop_ub;
        int o_loop_ub;
        int p_loop_ub;
        int q_loop_ub;
        int r_loop_ub;
        //  evaluate basis functions at the knots
        // 'CalcBspline_Lee:30' [ X, ~, Xdd ] = bspline_eval_vec(Bl, coef( k, : ), u);
        // 'bspline_eval_vec:3' x       = zeros(size(u));
        X.set_size(1, u.size(1));
        n_loop_ub = u.size(1);
        for (int i17{0}; i17 < n_loop_ub; i17++) {
            X[i17] = 0.0;
        }
        // 'bspline_eval_vec:4' xd      = zeros(size(u));
        a__2.set_size(1, u.size(1));
        o_loop_ub = u.size(1);
        for (int i18{0}; i18 < o_loop_ub; i18++) {
            a__2[i18] = 0.0;
        }
        // 'bspline_eval_vec:5' xdd     = zeros(size(u));
        Xdd.set_size(1, u.size(1));
        p_loop_ub = u.size(1);
        for (int i19{0}; i19 < p_loop_ub; i19++) {
            Xdd[i19] = 0.0;
        }
        // 'bspline_eval_vec:6' xddd    = zeros(size(u));
        xddd.set_size(1, u.size(1));
        q_loop_ub = u.size(1);
        for (int i20{0}; i20 < q_loop_ub; i20++) {
            xddd[i20] = 0.0;
        }
        // 'bspline_eval_vec:8' for k = 1:length(u)
        i21 = u.size(1);
        for (int d_k{0}; d_k < i21; d_k++) {
            int s_loop_ub;
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            X[d_k] = u[d_k];
            s_loop_ub = coef.size(1);
            b_coef.set_size(1, coef.size(1));
            for (int i23{0}; i23 < s_loop_ub; i23++) {
                b_coef[i23] = coef[c_k + coef.size(0) * i23];
            }
            bspline_eval(expl_temp.handle, b_coef, &X[d_k], &d1, &d2, &d3);
            xddd[d_k] = d3;
            Xdd[d_k] = d2;
            a__2[d_k] = d1;
            // 'bspline_eval_vec:10' x(k)    = xk;
            // 'bspline_eval_vec:11' xd(k)   = xdk;
            // 'bspline_eval_vec:12' xdd(k)  = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
        // 'CalcBspline_Lee:31' BasisVal(:, k)   = X';
        r_loop_ub = X.size(1);
        for (int i22{0}; i22 < r_loop_ub; i22++) {
            BasisVal[i22 + BasisVal.size(0) * c_k] = X[i22];
        }
        // 'CalcBspline_Lee:32' BasisValDD0( k ) = Xdd( 1 );
        BasisValDD0[c_k] = Xdd[0];
        // 'CalcBspline_Lee:33' BasisValDD1( k ) = Xdd( end );
        BasisValDD1[c_k] = Xdd[Xdd.size(1) - 1];
    }
    //
    // 'CalcBspline_Lee:36' A = [ BasisValDD0; BasisVal; BasisValDD1 ];
    if (BasisValDD0.size(1) != 0) {
        result = BasisValDD0.size(1);
    } else if ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0)) {
        result = BasisVal.size(1);
    } else if (BasisValDD1.size(1) != 0) {
        result = BasisValDD1.size(1);
    } else {
        result = 0;
        if (BasisVal.size(1) > 0) {
            result = BasisVal.size(1);
        }
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || (BasisValDD0.size(1) != 0)) {
        input_sizes_idx_0 = 1;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || ((BasisVal.size(0) != 0) && (BasisVal.size(1) != 0))) {
        b_input_sizes_idx_0 = BasisVal.size(0);
    } else {
        b_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (BasisValDD1.size(1) != 0)) {
        c_input_sizes_idx_0 = 1;
    } else {
        c_input_sizes_idx_0 = 0;
    }
    //
    // 'CalcBspline_Lee:38' b = [zeros(1, nAxis);
    // 'CalcBspline_Lee:39'             points.';
    // 'CalcBspline_Lee:40'      zeros(1, nAxis)];
    if (cfg_NumberAxis != 0) {
        b_result = cfg_NumberAxis;
    } else if ((du_tmp.size(0) != 0) && (du_tmp.size(1) != 0)) {
        b_result = du_tmp.size(1);
    } else {
        b_result = 0;
        if (du_tmp.size(1) > 0) {
            b_result = du_tmp.size(1);
        }
    }
    b_empty_non_axis_sizes = (b_result == 0);
    if (b_empty_non_axis_sizes || (cfg_NumberAxis != 0)) {
        d_input_sizes_idx_0 = 1;
    } else {
        d_input_sizes_idx_0 = 0;
    }
    if (b_empty_non_axis_sizes || ((du_tmp.size(0) != 0) && (du_tmp.size(1) != 0))) {
        e_input_sizes_idx_0 = du_tmp.size(0);
    } else {
        e_input_sizes_idx_0 = 0;
    }
    if (b_empty_non_axis_sizes || (cfg_NumberAxis != 0)) {
        f_input_sizes_idx_0 = 1;
    } else {
        f_input_sizes_idx_0 = 0;
    }
    //
    // 'CalcBspline_Lee:42' c = A \ b;
    //
    // 'CalcBspline_Lee:45' spnD = constrSpline( c.', knots, Bl );
    input_sizes_idx_0_tmp = input_sizes_idx_0;
    b_input_sizes_idx_0_tmp = c_input_sizes_idx_0;
    g_input_sizes_idx_0 = d_input_sizes_idx_0;
    b_BasisValDD0.set_size((input_sizes_idx_0 + b_input_sizes_idx_0) + c_input_sizes_idx_0, result);
    for (int i24{0}; i24 < result; i24++) {
        for (int i26{0}; i26 < input_sizes_idx_0_tmp; i26++) {
            b_BasisValDD0[b_BasisValDD0.size(0) * i24] = BasisValDD0[input_sizes_idx_0 * i24];
        }
    }
    for (int i25{0}; i25 < result; i25++) {
        for (int i28{0}; i28 < b_input_sizes_idx_0; i28++) {
            b_BasisValDD0[(i28 + input_sizes_idx_0) + b_BasisValDD0.size(0) * i25] =
                BasisVal[i28 + b_input_sizes_idx_0 * i25];
        }
    }
    for (int i27{0}; i27 < result; i27++) {
        for (int i30{0}; i30 < b_input_sizes_idx_0_tmp; i30++) {
            b_BasisValDD0[(input_sizes_idx_0 + b_input_sizes_idx_0) + b_BasisValDD0.size(0) * i27] =
                BasisValDD1[c_input_sizes_idx_0 * i27];
        }
    }
    i29 = d_input_sizes_idx_0 + e_input_sizes_idx_0;
    r1.set_size(i29 + f_input_sizes_idx_0, b_result);
    for (int i31{0}; i31 < b_result; i31++) {
        for (int i33{0}; i33 < g_input_sizes_idx_0; i33++) {
            r1[r1.size(0) * i31] = 0.0;
        }
    }
    for (int i32{0}; i32 < b_result; i32++) {
        for (int i35{0}; i35 < e_input_sizes_idx_0; i35++) {
            r1[(i35 + d_input_sizes_idx_0) + r1.size(0) * i32] =
                du_tmp[i35 + e_input_sizes_idx_0 * i32];
        }
    }
    for (int i34{0}; i34 < b_result; i34++) {
        int t_loop_ub;
        t_loop_ub = f_input_sizes_idx_0;
        for (int i36{0}; i36 < t_loop_ub; i36++) {
            r1[i29 + r1.size(0) * i34] = 0.0;
        }
    }
    coder::mldivide(b_BasisValDD0, r1, r);
    spnD_coeff.set_size(r.size(1), r.size(0));
    u_loop_ub = r.size(0);
    for (int i37{0}; i37 < u_loop_ub; i37++) {
        int v_loop_ub;
        v_loop_ub = r.size(1);
        for (int i38{0}; i38 < v_loop_ub; i38++) {
            spnD_coeff[i38 + spnD_coeff.size(0) * i37] = r[i37 + r.size(0) * i38];
        }
    }
    //  Construct a struct for the spline.
    //
    //  Inputs :
    //  BlStruct     : Base Spline structure
    //  coeff        : [ NDim x ncoeff ] Coefficient of the spline
    //  knots        : Knots of the spline
    //  Other fields:
    //  Ltot         : Total length of the spline
    //  Lk           : Individual length between two knots
    //
    //  Outputs :
    //  SplineStrct    : The resulting structure
    // 'constrSpline:15' SplineStrct = struct( ...
    // 'constrSpline:16'                     'Bl', BlStruct,...
    // 'constrSpline:17'                     'coeff', coeff,...
    // 'constrSpline:18'                     'knots', knots,...
    // 'constrSpline:19'                     'Ltot', 0.0, ...
    // 'constrSpline:20'                     'Lk', knots...
    // 'constrSpline:21'                     );
    spnD_Bl_breakpoints.set_size(1, expl_temp.breakpoints.size(1));
    w_loop_ub = expl_temp.breakpoints.size(1);
    for (int i39{0}; i39 < w_loop_ub; i39++) {
        spnD_Bl_breakpoints[i39] = expl_temp.breakpoints[i39];
    }
    spnD_Lk.set_size(1, spnD_knots.size(1));
    x_loop_ub = spnD_knots.size(1);
    for (int i40{0}; i40 < x_loop_ub; i40++) {
        spnD_Lk[i40] = spnD_knots[i40];
    }
    // 'constrSpline:23' if ~coder.target( 'MATLAB' )
    // 'constrSpline:24' coder.varsize( 'SplineStrct.Lk',    StructTypeName.dimLk{ : } );
    // 'constrSpline:25' coder.varsize( 'SplineStrct.coeff', StructTypeName.dimCoeffs{ : } );
    // 'constrSpline:26' coder.varsize( 'SplineStrct.knots', StructTypeName.dimKnots{ : } );
    // 'constrSpline:27' coder.cstructname( SplineStrct.Bl, StructTypeName.BaseSpline );
    // 'constrSpline:28' coder.cstructname( SplineStrct, StructTypeName.Spline );
    *spnD_Bl_ncoeff = expl_temp.ncoeff;
    *spnD_Bl_handle = expl_temp.handle;
    *spnD_Bl_order = expl_temp.order;
    *spnD_Ltot = 0.0;
}

} // namespace ocn

//
// File trailer for CalcBspline_Lee.cpp
//
// [EOF]
//
