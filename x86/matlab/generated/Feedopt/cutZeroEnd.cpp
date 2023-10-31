
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cutZeroEnd.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "cutZeroEnd.h"
#include "EvalCurvStruct.h"
#include "Kinematics.h"
#include "LengthCurv.h"
#include "cutCurvStruct.h"
#include "ocn_assert.h"
#include "opencn_matlab_types111.h"
#include "queue_coder.h"
#include "zeroSpeedCurv.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function [ ret, curv1, curv2 ] = cutZeroEnd( ctx, curv )
//
// cutZeroEnd : Cut the end of the given to handle the zero speed.
//  u  = cutCurvStructU( ctx, curv, 1, ctx.cfg.LSplitZero, true );
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
//                const double ctx_cfg_vmax[6]
//                const double ctx_cfg_amax[6]
//                const double ctx_cfg_jmax[6]
//                double ctx_cfg_LSplitZero
//                double ctx_cfg_dt
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const Kinematics *ctx_kin
//                const CurvStruct *curv
//                double *ret
//                CurvStruct *curv1
//                CurvStruct *curv2
// Return Type  : void
//
namespace ocn {
void cutZeroEnd(const queue_coder *ctx_q_spline, const bool ctx_cfg_maskTot_data[],
                const int ctx_cfg_maskTot_size[2], const bool ctx_cfg_maskCart_data[],
                const int ctx_cfg_maskCart_size[2], const bool ctx_cfg_maskRot_data[],
                const int ctx_cfg_maskRot_size[2], const ::coder::array<int, 1U> &ctx_cfg_indCart,
                const ::coder::array<int, 1U> &ctx_cfg_indRot, int ctx_cfg_NumberAxis,
                int ctx_cfg_NCart, int ctx_cfg_NRot, const double ctx_cfg_vmax[6],
                const double ctx_cfg_amax[6], const double ctx_cfg_jmax[6],
                double ctx_cfg_LSplitZero, double ctx_cfg_dt,
                const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
                const Kinematics *ctx_kin, const CurvStruct *curv, double *ret, CurvStruct *curv1,
                CurvStruct *curv2)
{
    static const signed char ind1[2][3]{{1, 1, 2}, {1, 2, 2}};
    static const signed char ind2[2][3]{{2, 3, 3}, {1, 2, 1}};
    Kinematics b_ctx_kin;
    Kinematics c_ctx_kin;
    ::coder::array<double, 2U> a__1;
    ::coder::array<double, 2U> a__2;
    ::coder::array<double, 2U> a__3;
    ::coder::array<double, 2U> a__4;
    ::coder::array<double, 2U> a__5;
    ::coder::array<double, 2U> a__6;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 1U> b_x;
    ::coder::array<double, 1U> b_z1;
    ::coder::array<double, 1U> c_z1;
    ::coder::array<double, 1U> z1;
    ::coder::array<bool, 1U> c_x;
    CurvStruct curv_vec[3];
    CurvStruct b_curv1;
    CurvStruct b_curv2;
    double r_data[36];
    double rd_data[36];
    double rdd_data[36];
    double b_rd_data[12];
    double b_rdd_data[12];
    double L;
    double Lcut;
    double b_ret;
    signed char tmp_data[6];
    // 'cutZeroEnd:5' L       = LengthCurv( ctx, curv, 0, 1 );
    L = LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                   ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                   ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot,
                   ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv);
    // 'cutZeroEnd:6' Lcut    = ctx.cfg.LSplitZero;
    Lcut = ctx_cfg_LSplitZero;
    // 'cutZeroEnd:8' if( Lcut > L / 3 )
    if (ctx_cfg_LSplitZero > L / 3.0) {
        // 'cutZeroEnd:9' Lcut = L / 3;
        Lcut = L / 3.0;
    }
    // 'cutZeroEnd:12' [ ret, curv1, curv2 ] = cutCurvStruct( ctx, curv, 1, Lcut, true );
    b_cutCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size, ctx_cfg_maskCart_data,
                    ctx_cfg_maskCart_size, ctx_cfg_maskRot_data, ctx_cfg_maskRot_size,
                    ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis, ctx_cfg_NCart,
                    ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW, curv, Lcut,
                    &b_ret, curv1, curv2);
    // 'cutZeroEnd:14' if( ret < 0 )
    if (b_ret < 0.0) {
        // 'cutZeroEnd:15' curv1 = curv;
        *curv1 = *curv;
        // 'cutZeroEnd:16' curv1.UseConstJerk      = true;
        curv1->UseConstJerk = true;
        // 'cutZeroEnd:17' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv1, true );
        b_ctx_kin = *ctx_kin;
        b_curv1 = *curv1;
        b_zeroSpeedCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                        ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                        ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_vmax, ctx_cfg_amax, ctx_cfg_jmax,
                        ctx_cfg_dt, &b_ctx_kin, &b_curv1, a__1, a__2, a__3, &curv1->ConstJerk);
        // 'cutZeroEnd:18' curv1.ConstJerk         = jps;
    } else {
        double x;
        int b_scalarLB;
        int b_vectorUB;
        int c_scalarLB;
        int c_vectorUB;
        int d_scalarLB;
        int d_vectorUB;
        int e_scalarLB;
        int e_vectorUB;
        int end;
        int partialTrueCount;
        int rd;
        int rdd;
        int scalarLB;
        int trueCount;
        int vectorUB;
        // 'cutZeroEnd:19' else
        // 'cutZeroEnd:20' ocn_assert( check_curv_length( ctx, curv2, Lcut ), "Curve Length not
        // valide", mfilename ); 'cutZeroStart:105' tol = 1E-1; 'cutZeroStart:107' isValid = ( abs(
        // LengthCurv( ctx, curv, 0, 1 ) - L ) <= tol );
        x = LengthCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                       ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                       ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                       ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_GaussLegendreX, ctx_cfg_GaussLegendreW,
                       curv2) -
            Lcut;
        w_ocn_assert(std::abs(x) <= 0.1);
        // 'cutZeroEnd:21' curv2.UseConstJerk      = true;
        curv2->UseConstJerk = true;
        // 'cutZeroEnd:22' [ ~, ~, ~, jps ]        = zeroSpeedCurv( ctx, curv2, true );
        c_ctx_kin = *ctx_kin;
        b_curv2 = *curv2;
        b_zeroSpeedCurv(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                        ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                        ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot, ctx_cfg_NumberAxis,
                        ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_vmax, ctx_cfg_amax, ctx_cfg_jmax,
                        ctx_cfg_dt, &c_ctx_kin, &b_curv2, a__4, a__5, a__6, &curv2->ConstJerk);
        // 'cutZeroEnd:23' curv2.ConstJerk         = jps;
        // 'cutZeroEnd:24' curv1.UseConstJerk      = false;
        curv1->UseConstJerk = false;
        // 'cutZeroEnd:25' check_continuity( ctx, curv, curv1, curv2 );
        // 'cutZeroEnd:57' curv_vec    = [ curv; curv1; curv2 ];
        curv_vec[0] = *curv;
        curv_vec[1] = *curv1;
        curv_vec[2] = *curv2;
        // 'cutZeroEnd:58' u_vec       = [ 0, 1 ];
        // 'cutZeroEnd:59' r           = repmat( curv.R0( ctx.cfg.maskTot ), 1, 2, 3 );
        end = ctx_cfg_maskTot_size[1] - 1;
        trueCount = 0;
        partialTrueCount = 0;
        for (int i{0}; i <= end; i++) {
            if (ctx_cfg_maskTot_data[i]) {
                trueCount++;
                tmp_data[partialTrueCount] = static_cast<signed char>(i + 1);
                partialTrueCount++;
            }
        }
        if (trueCount != 0) {
            for (int t{0}; t < 3; t++) {
                for (int b_t{0}; b_t < 2; b_t++) {
                    for (int k{0}; k < trueCount; k++) {
                        r_data[(k + trueCount * b_t) + trueCount * 2 * t] =
                            curv->R0[tmp_data[k] - 1];
                    }
                }
            }
        }
        // 'cutZeroEnd:60' rd          = r;
        // 'cutZeroEnd:61' rdd         = r;
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
        // 'cutZeroEnd:63' for j = 1 : 3
        rd = trueCount - 1;
        scalarLB = (trueCount / 2) << 1;
        vectorUB = scalarLB - 2;
        rdd = trueCount - 1;
        b_scalarLB = (trueCount / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int j{0}; j < 3; j++) {
            double c;
            int b_loop_ub;
            int c_loop_ub;
            int loop_ub;
            // 'cutZeroEnd:64' [ r( :, :, j ) , rd( :, :, j ), rdd( :, :, j ) ] = ...
            // 'cutZeroEnd:65'         EvalCurvStruct( ctx, curv_vec( j ),  u_vec );
            j_EvalCurvStruct(ctx_q_spline, ctx_cfg_maskTot_data, ctx_cfg_maskTot_size,
                             ctx_cfg_maskCart_data, ctx_cfg_maskCart_size, ctx_cfg_maskRot_data,
                             ctx_cfg_maskRot_size, ctx_cfg_indCart, ctx_cfg_indRot,
                             ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot, &curv_vec[j], r, r1,
                             r2);
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
            // 'cutZeroEnd:66' rd( :, :, j )    = rd( :, :, j )  / curv_vec( j ).a_param;
            for (int i5{0}; i5 < 2; i5++) {
                for (int i7{0}; i7 <= vectorUB; i7 += 2) {
                    __m128d r3;
                    r3 = _mm_loadu_pd(&rd_data[(i7 + trueCount * i5) + trueCount * 2 * j]);
                    _mm_storeu_pd(&b_rd_data[i7 + trueCount * i5],
                                  _mm_div_pd(r3, _mm_set1_pd(curv_vec[j].a_param)));
                }
                for (int i7{scalarLB}; i7 <= rd; i7++) {
                    b_rd_data[i7 + trueCount * i5] =
                        rd_data[(i7 + trueCount * i5) + trueCount * 2 * j] / curv_vec[j].a_param;
                }
            }
            double c_tmp;
            // 'cutZeroEnd:67' if( 1 )
            // 'cutZeroEnd:68' rdd( :, :, j )   = rdd( :, :, j ) / curv_vec( j ).a_param^2;
            c_tmp = curv_vec[j].a_param;
            c = c_tmp * c_tmp;
            for (int i9{0}; i9 < 2; i9++) {
                for (int i11{0}; i11 < trueCount; i11++) {
                    rd_data[(i11 + trueCount * i9) + trueCount * 2 * j] =
                        b_rd_data[i11 + trueCount * i9];
                }
                for (int i13{0}; i13 <= b_vectorUB; i13 += 2) {
                    __m128d r4;
                    r4 = _mm_loadu_pd(&rdd_data[(i13 + trueCount * i9) + trueCount * 2 * j]);
                    _mm_storeu_pd(&b_rdd_data[i13 + trueCount * i9],
                                  _mm_div_pd(r4, _mm_set1_pd(c)));
                }
                for (int i13{b_scalarLB}; i13 <= rdd; i13++) {
                    b_rdd_data[i13 + trueCount * i9] =
                        rdd_data[(i13 + trueCount * i9) + trueCount * 2 * j] / c;
                }
            }
            for (int i10{0}; i10 < 2; i10++) {
                for (int i12{0}; i12 < trueCount; i12++) {
                    rdd_data[(i12 + trueCount * i10) + trueCount * 2 * j] =
                        b_rdd_data[i12 + trueCount * i10];
                }
            }
        }
        // 'cutZeroEnd:74' ind1 = [ 1, 1; 1, 2; 2, 2 ];
        // 'cutZeroEnd:75' ind2 = [ 2, 1; 3, 2; 3, 1 ];
        // 'cutZeroEnd:77' for j = 1 : 3
        c_scalarLB = (trueCount / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        d_scalarLB = (trueCount / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        e_scalarLB = (trueCount / 2) << 1;
        e_vectorUB = e_scalarLB - 2;
        for (int b_j{0}; b_j < 3; b_j++) {
            int b_ind1_tmp;
            int b_ind2_tmp;
            int d_loop_ub;
            int e_k;
            int e_loop_ub;
            int f_k;
            int f_loop_ub;
            int g_k;
            int ind1_tmp;
            int ind2_tmp;
            bool b_varargout_1;
            bool c_varargout_1;
            bool exitg1;
            bool varargout_1;
            // 'cutZeroEnd:78' r1   = r( : , ind1( j, 2 ), ind1( j, 1 ) );
            // 'cutZeroEnd:79' r1d  = rd( : , ind1( j, 2 ), ind1( j, 1 ) );
            // 'cutZeroEnd:80' r1dd = rdd( : , ind1( j, 2 ), ind1( j, 1 ) );
            // 'cutZeroEnd:81' r2   = r( : , ind2( j, 2 ), ind2( j, 1 ) );
            // 'cutZeroEnd:82' r2d  = rd( : , ind2( j, 2 ), ind2( j, 1 ) );
            // 'cutZeroEnd:83' r2dd = rdd( : , ind2( j, 2 ), ind2( j, 1 ) );
            // 'cutZeroEnd:84' assert_continuity( r1, r1d, r1dd, r2, r2d, r2dd );
            // 'cutZeroEnd:91' diff_r      = abs( r1    -r2 );
            ind1_tmp = ind1[1][b_j];
            b_ind1_tmp = ind1[0][b_j];
            ind2_tmp = ind2[1][b_j];
            b_ind2_tmp = ind2[0][b_j];
            b_x.set_size(trueCount);
            for (int i14{0}; i14 <= c_vectorUB; i14 += 2) {
                __m128d r5;
                __m128d r6;
                r5 = _mm_loadu_pd(
                    &r_data[(i14 + trueCount * (ind1_tmp - 1)) + trueCount * 2 * (b_ind1_tmp - 1)]);
                r6 = _mm_loadu_pd(
                    &r_data[(i14 + trueCount * (ind2_tmp - 1)) + trueCount * 2 * (b_ind2_tmp - 1)]);
                _mm_storeu_pd(&b_x[i14], _mm_sub_pd(r5, r6));
            }
            for (int i14{c_scalarLB}; i14 < trueCount; i14++) {
                b_x[i14] =
                    r_data[(i14 + trueCount * (ind1_tmp - 1)) + trueCount * 2 * (b_ind1_tmp - 1)] -
                    r_data[(i14 + trueCount * (ind2_tmp - 1)) + trueCount * 2 * (b_ind2_tmp - 1)];
            }
            z1.set_size(b_x.size(0));
            if (b_x.size(0) != 0) {
                int i15;
                i15 = b_x.size(0);
                for (int b_k{0}; b_k < i15; b_k++) {
                    z1[b_k] = std::abs(b_x[b_k]);
                }
            }
            // 'cutZeroEnd:92' diff_rd     = abs( r1d   -r2d );
            b_x.set_size(trueCount);
            for (int i16{0}; i16 <= d_vectorUB; i16 += 2) {
                __m128d r7;
                __m128d r8;
                r7 = _mm_loadu_pd(&rd_data[(i16 + trueCount * (ind1_tmp - 1)) +
                                           trueCount * 2 * (b_ind1_tmp - 1)]);
                r8 = _mm_loadu_pd(&rd_data[(i16 + trueCount * (ind2_tmp - 1)) +
                                           trueCount * 2 * (b_ind2_tmp - 1)]);
                _mm_storeu_pd(&b_x[i16], _mm_sub_pd(r7, r8));
            }
            for (int i16{d_scalarLB}; i16 < trueCount; i16++) {
                b_x[i16] =
                    rd_data[(i16 + trueCount * (ind1_tmp - 1)) + trueCount * 2 * (b_ind1_tmp - 1)] -
                    rd_data[(i16 + trueCount * (ind2_tmp - 1)) + trueCount * 2 * (b_ind2_tmp - 1)];
            }
            b_z1.set_size(b_x.size(0));
            if (b_x.size(0) != 0) {
                int i17;
                i17 = b_x.size(0);
                for (int c_k{0}; c_k < i17; c_k++) {
                    b_z1[c_k] = std::abs(b_x[c_k]);
                }
            }
            // 'cutZeroEnd:93' diff_rdd    = abs( r1dd  -r2dd );
            b_x.set_size(trueCount);
            for (int i18{0}; i18 <= e_vectorUB; i18 += 2) {
                __m128d r10;
                __m128d r9;
                r9 = _mm_loadu_pd(&rdd_data[(i18 + trueCount * (ind1_tmp - 1)) +
                                            trueCount * 2 * (b_ind1_tmp - 1)]);
                r10 = _mm_loadu_pd(&rdd_data[(i18 + trueCount * (ind2_tmp - 1)) +
                                             trueCount * 2 * (b_ind2_tmp - 1)]);
                _mm_storeu_pd(&b_x[i18], _mm_sub_pd(r9, r10));
            }
            for (int i18{e_scalarLB}; i18 < trueCount; i18++) {
                b_x[i18] =
                    rdd_data[(i18 + trueCount * (ind1_tmp - 1)) +
                             trueCount * 2 * (b_ind1_tmp - 1)] -
                    rdd_data[(i18 + trueCount * (ind2_tmp - 1)) + trueCount * 2 * (b_ind2_tmp - 1)];
            }
            c_z1.set_size(b_x.size(0));
            if (b_x.size(0) != 0) {
                int i19;
                i19 = b_x.size(0);
                for (int d_k{0}; d_k < i19; d_k++) {
                    c_z1[d_k] = std::abs(b_x[d_k]);
                }
            }
            // 'cutZeroEnd:95' tol = 1E-9;
            // 'cutZeroEnd:97' ocn_assert( all( diff_r    < tol, 'all' ), "Continuity C0 failed",
            // mfilename );
            c_x.set_size(z1.size(0));
            d_loop_ub = z1.size(0);
            for (int i20{0}; i20 < d_loop_ub; i20++) {
                c_x[i20] = (z1[i20] < 1.0E-9);
            }
            varargout_1 = true;
            e_k = 0;
            exitg1 = false;
            while ((!exitg1) && (e_k <= c_x.size(0) - 1)) {
                if (!c_x[e_k]) {
                    varargout_1 = false;
                    exitg1 = true;
                } else {
                    e_k++;
                }
            }
            x_ocn_assert(varargout_1);
            // 'cutZeroEnd:98' ocn_assert( all( diff_rd   < tol, 'all' ), "Continuity C1 failed",
            // mfilename );
            c_x.set_size(b_z1.size(0));
            e_loop_ub = b_z1.size(0);
            for (int i21{0}; i21 < e_loop_ub; i21++) {
                c_x[i21] = (b_z1[i21] < 1.0E-9);
            }
            b_varargout_1 = true;
            f_k = 0;
            exitg1 = false;
            while ((!exitg1) && (f_k <= c_x.size(0) - 1)) {
                if (!c_x[f_k]) {
                    b_varargout_1 = false;
                    exitg1 = true;
                } else {
                    f_k++;
                }
            }
            y_ocn_assert(b_varargout_1);
            // 'cutZeroEnd:99' ocn_assert( all( diff_rdd   < tol, 'all' ),"Continuity C2 failed",
            // mfilename );
            c_x.set_size(c_z1.size(0));
            f_loop_ub = c_z1.size(0);
            for (int i22{0}; i22 < f_loop_ub; i22++) {
                c_x[i22] = (c_z1[i22] < 1.0E-9);
            }
            c_varargout_1 = true;
            g_k = 0;
            exitg1 = false;
            while ((!exitg1) && (g_k <= c_x.size(0) - 1)) {
                if (!c_x[g_k]) {
                    c_varargout_1 = false;
                    exitg1 = true;
                } else {
                    g_k++;
                }
            }
            ab_ocn_assert(c_varargout_1);
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
    *ret = b_ret;
}

} // namespace ocn

//
// File trailer for cutZeroEnd.cpp
//
// [EOF]
//
