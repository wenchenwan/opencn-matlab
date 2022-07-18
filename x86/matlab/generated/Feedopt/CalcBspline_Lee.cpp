//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcBspline_Lee.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Jul-2022 08:54:02
//

// Include Files
#include "CalcBspline_Lee.h"
#include "constrBaseSpline.h"
#include "opencn_matlab_types3.h"
#include "sum.h"
#include "tridiag.h"
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
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> B;
    ::coder::array<double, 2U> BasisVal;
    ::coder::array<double, 2U> BasisValDD0;
    ::coder::array<double, 2U> BasisValDD1;
    ::coder::array<double, 2U> b_y1;
    ::coder::array<double, 2U> breakpoints;
    ::coder::array<double, 2U> c;
    ::coder::array<double, 2U> c_A;
    ::coder::array<double, 2U> c_B;
    ::coder::array<double, 2U> c_c;
    ::coder::array<double, 2U> d_B;
    ::coder::array<double, 2U> du_tmp;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> u;
    ::coder::array<double, 1U> b_d;
    ::coder::array<double, 1U> v;
    ::coder::array<double, 1U> v_l;
    ::coder::array<double, 1U> v_m;
    ::coder::array<double, 1U> v_u;
    BaseSplineStruct expl_temp;
    double b_u;
    double w;
    unsigned long h;
    int b_A;
    int b_B;
    int b_input_sizes_idx_0;
    int b_input_sizes_idx_0_tmp;
    int b_result;
    int b_u0;
    int b_unnamed_idx_2;
    int b_unnamed_idx_3;
    int bb_loop_ub;
    int c_dlen;
    int c_loop_ub;
    int c_u1;
    int d_u0;
    int db_loop_ub;
    int dimSize;
    int dlen;
    int e_input_sizes_idx_0;
    int e_loop_ub;
    int eb_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i33;
    int i36;
    int i42;
    int i43;
    int i9;
    int i_loop_ub;
    int input_sizes_idx_0_tmp;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int loop_ub_tmp;
    int nCoeff;
    int p_loop_ub;
    int q_loop_ub;
    int r_loop_ub;
    int result;
    int s_loop_ub;
    int scalarLB;
    int t_loop_ub;
    int u0;
    int u1;
    int u_loop_ub;
    unsigned int unnamed_idx_0;
    int unnamed_idx_2;
    int unnamed_idx_3;
    int vectorUB;
    int w_loop_ub;
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
    // 'CalcBspline_Lee:23' [ BasisVal, BasisValDD0, BasisValDD1 ] = bspline_eval_lee( Bl, int32(
    // nCoeff ), u );
    nCoeff = points.size(1) + 2;
    // 'bspline_eval_lee:3' assert( all( u_vec >= 0, 'all' ), "ERROR : u_vec should be greater or
    // equal to 0" ); 'bspline_eval_lee:4' assert( all( u_vec <= 1, 'all' ), "ERROR : u_vec should
    // be lower or equal to 1" ); 'bspline_eval_lee:6' if ( coder.target('rtw') ||
    // coder.target('mex') ) 'bspline_eval_lee:7' N = numel( u_vec ); 'bspline_eval_lee:9' BasisVal
    // = zeros( N, nCoeff );
    BasisVal.set_size(u.size(1), points.size(1) + 2);
    l_loop_ub = points.size(1) + 2;
    for (int i14{0}; i14 < l_loop_ub; i14++) {
        int m_loop_ub;
        m_loop_ub = u.size(1);
        for (int i15{0}; i15 < m_loop_ub; i15++) {
            BasisVal[i15 + BasisVal.size(0) * i14] = 0.0;
        }
    }
    // 'bspline_eval_lee:10' BasisValDD0 = BasisVal( 1, : );
    BasisValDD0.set_size(1, points.size(1) + 2);
    // 'bspline_eval_lee:11' BasisValDD1 = BasisValDD0;
    BasisValDD1.set_size(1, points.size(1) + 2);
    for (int i16{0}; i16 < nCoeff; i16++) {
        BasisValDD0[i16] = 0.0;
        BasisValDD1[i16] = 0.0;
    }
    // 'bspline_eval_lee:13' coder.updateBuildInfo('addSourceFiles','c_spline.c',
    // '$(START_DIR)/src'); 'bspline_eval_lee:14' coder.updateBuildInfo('addLinkFlags',
    // LibInfo.gsl.lflags); 'bspline_eval_lee:15' coder.cinclude('src/c_spline.h');
    // 'bspline_eval_lee:16' coder.ceval('c_bspline_base_eval_lee', coder.rref(Bl.handle), ...
    // 'bspline_eval_lee:17'             int32( nCoeff ), int32( N ), coder.rref( u_vec ), ...
    // 'bspline_eval_lee:18'             coder.wref( BasisVal ), coder.wref( BasisValDD0 ), ...
    // 'bspline_eval_lee:19'             coder.wref( BasisValDD1 ) );
    c_bspline_base_eval_lee(&expl_temp.handle, points.size(1) + 2, u.size(1), &u[0], &BasisVal[0],
                            &BasisValDD0[0], &BasisValDD1[0]);
    //
    // 'CalcBspline_Lee:26' A = [ BasisValDD0; BasisVal; BasisValDD1 ];
    if (BasisValDD0.size(1) != 0) {
        result = BasisValDD0.size(1);
    } else if (BasisVal.size(1) != 0) {
        result = BasisVal.size(1);
    } else if (BasisValDD1.size(1) != 0) {
        result = BasisValDD1.size(1);
    } else {
        result = 0;
    }
    empty_non_axis_sizes = (result == 0);
    if (empty_non_axis_sizes || (BasisValDD0.size(1) != 0)) {
        input_sizes_idx_0 = 1;
    } else {
        input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (BasisVal.size(1) != 0)) {
        b_input_sizes_idx_0 = BasisVal.size(0);
    } else {
        b_input_sizes_idx_0 = 0;
    }
    if (empty_non_axis_sizes || (BasisValDD1.size(1) != 0)) {
        c_input_sizes_idx_0 = 1;
    } else {
        c_input_sizes_idx_0 = 0;
    }
    input_sizes_idx_0_tmp = input_sizes_idx_0;
    b_input_sizes_idx_0_tmp = c_input_sizes_idx_0;
    A.set_size((input_sizes_idx_0 + b_input_sizes_idx_0) + c_input_sizes_idx_0, result);
    for (int i17{0}; i17 < result; i17++) {
        for (int i19{0}; i19 < input_sizes_idx_0_tmp; i19++) {
            A[A.size(0) * i17] = BasisValDD0[input_sizes_idx_0 * i17];
        }
    }
    for (int i18{0}; i18 < result; i18++) {
        for (int i21{0}; i21 < b_input_sizes_idx_0; i21++) {
            A[(i21 + input_sizes_idx_0) + A.size(0) * i18] =
                BasisVal[i21 + b_input_sizes_idx_0 * i18];
        }
    }
    for (int i20{0}; i20 < result; i20++) {
        for (int i22{0}; i22 < b_input_sizes_idx_0_tmp; i22++) {
            A[(input_sizes_idx_0 + b_input_sizes_idx_0) + A.size(0) * i20] =
                BasisValDD1[c_input_sizes_idx_0 * i20];
        }
    }
    //
    // 'CalcBspline_Lee:28' B = [zeros(1, nAxis);
    // 'CalcBspline_Lee:29'             points.';
    // 'CalcBspline_Lee:30'      zeros(1, nAxis)];
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
    B.set_size((d_input_sizes_idx_0 + e_input_sizes_idx_0) + f_input_sizes_idx_0, b_result);
    for (int i23{0}; i23 < b_result; i23++) {
        int n_loop_ub;
        n_loop_ub = d_input_sizes_idx_0;
        for (int i25{0}; i25 < n_loop_ub; i25++) {
            B[B.size(0) * i23] = 0.0;
        }
    }
    for (int i24{0}; i24 < b_result; i24++) {
        for (int i27{0}; i27 < e_input_sizes_idx_0; i27++) {
            B[(i27 + d_input_sizes_idx_0) + B.size(0) * i24] =
                du_tmp[i27 + e_input_sizes_idx_0 * i24];
        }
    }
    for (int i26{0}; i26 < b_result; i26++) {
        int o_loop_ub;
        o_loop_ub = f_input_sizes_idx_0;
        for (int i28{0}; i28 < o_loop_ub; i28++) {
            B[(d_input_sizes_idx_0 + e_input_sizes_idx_0) + B.size(0) * i26] = 0.0;
        }
    }
    //
    // 'CalcBspline_Lee:32' [ A ] = swap_lines( A );
    //  Swap the lines of the matrice M. The goal is to obtain a tridiagonal
    //  matrice.
    // 'CalcBspline_Lee:45' M( [ 1, 2, end-1, end ], : ) = M( [ 2, 1, end, end-1 ], :);
    unnamed_idx_2 = A.size(0) - 2;
    unnamed_idx_3 = A.size(0) - 1;
    b_A = A.size(1) - 1;
    b_unnamed_idx_2 = A.size(0) - 1;
    b_unnamed_idx_3 = A.size(0) - 2;
    c_A.set_size(4, A.size(1));
    for (int i29{0}; i29 <= b_A; i29++) {
        c_A[4 * i29] = A[A.size(0) * i29 + 1];
        c_A[4 * i29 + 1] = A[A.size(0) * i29];
        c_A[4 * i29 + 2] = A[b_unnamed_idx_2 + A.size(0) * i29];
        c_A[4 * i29 + 3] = A[b_unnamed_idx_3 + A.size(0) * i29];
    }
    p_loop_ub = c_A.size(1);
    for (int i30{0}; i30 < p_loop_ub; i30++) {
        A[A.size(0) * i30] = c_A[4 * i30];
        A[A.size(0) * i30 + 1] = c_A[4 * i30 + 1];
        A[unnamed_idx_2 + A.size(0) * i30] = c_A[4 * i30 + 2];
        A[unnamed_idx_3 + A.size(0) * i30] = c_A[4 * i30 + 3];
    }
    // 'CalcBspline_Lee:33' [ B ] = swap_lines( B );
    //  Swap the lines of the matrice M. The goal is to obtain a tridiagonal
    //  matrice.
    // 'CalcBspline_Lee:45' M( [ 1, 2, end-1, end ], : ) = M( [ 2, 1, end, end-1 ], :);
    unnamed_idx_2 = B.size(0) - 2;
    unnamed_idx_3 = B.size(0) - 1;
    b_B = B.size(1) - 1;
    b_unnamed_idx_2 = B.size(0) - 1;
    b_unnamed_idx_3 = B.size(0) - 2;
    c_B.set_size(4, B.size(1));
    for (int i31{0}; i31 <= b_B; i31++) {
        c_B[4 * i31] = B[B.size(0) * i31 + 1];
        c_B[4 * i31 + 1] = B[B.size(0) * i31];
        c_B[4 * i31 + 2] = B[b_unnamed_idx_2 + B.size(0) * i31];
        c_B[4 * i31 + 3] = B[b_unnamed_idx_3 + B.size(0) * i31];
    }
    q_loop_ub = c_B.size(1);
    for (int i32{0}; i32 < q_loop_ub; i32++) {
        B[B.size(0) * i32] = c_B[4 * i32];
        B[B.size(0) * i32 + 1] = c_B[4 * i32 + 1];
        B[unnamed_idx_2 + B.size(0) * i32] = c_B[4 * i32 + 2];
        B[unnamed_idx_3 + B.size(0) * i32] = c_B[4 * i32 + 3];
    }
    // 'CalcBspline_Lee:34' [ v_m, v_l, v_u ] = extract_vectors( A );
    //  Extract the three vectors of the triagonal matrix A.
    //  Output :
    //  v_m   :   The vector of the middle of the matrix
    //  v_l   :   The vector of the lower diagonal of the matrix
    //  v_u   :   The vector of the upper diagonal of the matrix
    // 'CalcBspline_Lee:55' v_m = diag( A );
    b_u0 = A.size(0);
    u1 = A.size(1);
    if (b_u0 <= u1) {
        dlen = b_u0;
    } else {
        dlen = u1;
    }
    v_m.set_size(dlen);
    i33 = dlen - 1;
    for (int b_k{0}; b_k <= i33; b_k++) {
        v_m[b_k] = A[b_k + A.size(0) * b_k];
    }
    // 'CalcBspline_Lee:56' v_l = [ 0; diag( A, -1 ) ];
    if (1 > A.size(0)) {
        b_d.set_size(0);
    } else {
        int b_dlen;
        int b_i;
        int i34;
        if (1 < A.size(0)) {
            int b_u1;
            int c_u0;
            c_u0 = A.size(0) - 1;
            b_u1 = A.size(1);
            if (c_u0 <= b_u1) {
                b_dlen = c_u0;
            } else {
                b_dlen = b_u1;
            }
            b_i = 1;
        } else {
            b_dlen = 0;
            b_i = 0;
        }
        b_d.set_size(b_dlen);
        i34 = b_dlen - 1;
        for (int c_k{0}; c_k <= i34; c_k++) {
            b_d[c_k] = A[(b_i + c_k) + A.size(0) * c_k];
        }
    }
    v_l.set_size(b_d.size(0) + 1);
    v_l[0] = 0.0;
    r_loop_ub = b_d.size(0);
    for (int i35{0}; i35 < r_loop_ub; i35++) {
        v_l[i35 + 1] = b_d[i35];
    }
    // 'CalcBspline_Lee:57' v_u = [ diag( A, 1 ); 0 ];
    d_u0 = A.size(0);
    c_u1 = A.size(1) - 1;
    if (d_u0 <= c_u1) {
        c_dlen = d_u0;
    } else {
        c_dlen = c_u1;
    }
    b_d.set_size(c_dlen);
    i36 = c_dlen - 1;
    for (int d_k{0}; d_k <= i36; d_k++) {
        b_d[d_k] = A[d_k + A.size(0) * (d_k + 1)];
    }
    v_u.set_size(b_d.size(0) + 1);
    s_loop_ub = b_d.size(0);
    for (int i37{0}; i37 < s_loop_ub; i37++) {
        v_u[i37] = b_d[i37];
    }
    v_u[b_d.size(0)] = 0.0;
    // 'CalcBspline_Lee:36' c = tridiag( v_m, v_l, v_u, B );
    // 'tridiag:2' if( ~coder.target( "MATLAB" ) )
    //   Solve the  n x n  tridiagonal system for y:
    //
    //   [ a(1)  c(1)                                  ] [  y(1)  ]   [  f(1)  ]
    //   [ b(2)  a(2)  c(2)                            ] [  y(2)  ]   [  f(2)  ]
    //   [       b(3)  a(3)  c(3)                      ] [        ]   [        ]
    //   [            ...   ...   ...                  ] [  ...   ] = [  ...   ]
    //   [                    ...    ...    ...        ] [        ]   [        ]
    //   [                        b(n-1) a(n-1) c(n-1) ] [ y(n-1) ]   [ f(n-1) ]
    //   [                                 b(n)  a(n)  ] [  y(n)  ]   [  f(n)  ]
    //
    //   The right hand side f may be a matrix composed of column vectors of length n
    //   a, b, c must be vectors of length n (note that b(1) and c(n) are not used)
    //  some additional information is at the end of the file
    // 'tridiag:18' [ n, ~ ]  = size( f );
    // 'tridiag:19' v         = zeros( n, 1 );
    v.set_size(B.size(0));
    t_loop_ub = B.size(0);
    for (int i38{0}; i38 < t_loop_ub; i38++) {
        v[i38] = 0.0;
    }
    // 'tridiag:20' y         = zeros( size( f ) );
    unnamed_idx_0 = static_cast<unsigned int>(B.size(0));
    c.set_size(B.size(0), B.size(1));
    u_loop_ub = B.size(1);
    for (int i39{0}; i39 < u_loop_ub; i39++) {
        int v_loop_ub;
        v_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i40{0}; i40 < v_loop_ub; i40++) {
            c[i40 + c.size(0) * i39] = 0.0;
        }
    }
    // 'tridiag:21' w         = a( 1 );
    w = v_m[0];
    // 'tridiag:22' y( 1, : ) = f( 1, : ) / w;
    w_loop_ub = B.size(1);
    for (int i41{0}; i41 < w_loop_ub; i41++) {
        c[c.size(0) * i41] = B[B.size(0) * i41] / v_m[0];
    }
    // 'tridiag:24' for i = 2 : n
    i42 = B.size(0);
    for (int c_i{0}; c_i <= i42 - 2; c_i++) {
        double d1;
        double w_tmp;
        int x_loop_ub;
        // 'tridiag:25' v( i -1 ) = c( i -1 ) / w;
        d1 = v_u[c_i] / w;
        v[c_i] = d1;
        // 'tridiag:26' w         = a( i ) - b( i ) * v( i -1 );
        w_tmp = v_l[c_i + 1];
        w = v_m[c_i + 1] - w_tmp * d1;
        // 'tridiag:27' y( i, : ) = ( f( i, : ) - b( i ) * y( i -1, : ) ) / w;
        x_loop_ub = B.size(1);
        if (B.size(1) == c.size(1)) {
            int ab_loop_ub;
            d_B.set_size(1, B.size(1));
            for (int i45{0}; i45 < x_loop_ub; i45++) {
                d_B[i45] = (B[(c_i + B.size(0) * i45) + 1] - w_tmp * c[c_i + c.size(0) * i45]) / w;
            }
            ab_loop_ub = d_B.size(1);
            for (int i47{0}; i47 < ab_loop_ub; i47++) {
                c[(c_i + c.size(0) * i47) + 1] = d_B[i47];
            }
        } else {
            binary_expand_op(c, c_i, B, v_l, w);
        }
    }
    // 'tridiag:30' for j = n-1 : -1 : 1
    i43 = B.size(0);
    for (int j{0}; j <= i43 - 2; j++) {
        int b_c;
        int b_j;
        int y_loop_ub;
        b_j = (B.size(0) - j) - 2;
        // 'tridiag:31' y( j, : ) = y( j, : ) - v( j ) * y( j + 1, : );
        b_c = c.size(1) - 1;
        c_c.set_size(1, c.size(1));
        for (int i44{0}; i44 <= b_c; i44++) {
            c_c[i44] = c[b_j + c.size(0) * i44] - v[b_j] * c[(b_j + c.size(0) * i44) + 1];
        }
        y_loop_ub = c_c.size(1);
        for (int i46{0}; i46 < y_loop_ub; i46++) {
            c[b_j + c.size(0) * i46] = c_c[i46];
        }
    }
    //   This is an implementation of the Thomas algorithm.  It does not overwrite a, b, c, f but
    //   it does introduce a working n-vector (v).
    // %%%%  Example
    //  n = 5; a = 4*ones(n,1); b = ones(n,1); c = 3*ones(n,1);
    //  f = rand(n,1);
    //  y = tridiag(a,b,c,f);
    // %%%%  check solution
    //  A = diag(a,0) + diag(ones(n-1,1),-1) + diag(3*ones(n-1,1),1)
    //  A*y - f
    // %%%% Conditions that will guarantee the matrix equation can be solved using this algorithm:
    // %%%%  1. matrix strictly diagonally dominant
    // %%%%  2. matrix diagonally dominant, c_i not zero for all i, and abs(b_n) < abs(a_n)
    //   It has been tested on MATLAB, version R2010b and version R2012a
    //   version: 1.0
    //   March 9, 2013
    // 'CalcBspline_Lee:38' spnD = constrSpline( c.', knots, Bl );
    spnD_coeff.set_size(c.size(1), c.size(0));
    bb_loop_ub = c.size(0);
    for (int i48{0}; i48 < bb_loop_ub; i48++) {
        int cb_loop_ub;
        cb_loop_ub = c.size(1);
        for (int i49{0}; i49 < cb_loop_ub; i49++) {
            spnD_coeff[i49 + spnD_coeff.size(0) * i48] = c[i48 + c.size(0) * i49];
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
    db_loop_ub = expl_temp.breakpoints.size(1);
    for (int i50{0}; i50 < db_loop_ub; i50++) {
        spnD_Bl_breakpoints[i50] = expl_temp.breakpoints[i50];
    }
    spnD_Lk.set_size(1, spnD_knots.size(1));
    eb_loop_ub = spnD_knots.size(1);
    for (int i51{0}; i51 < eb_loop_ub; i51++) {
        spnD_Lk[i51] = spnD_knots[i51];
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
