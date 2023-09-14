//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: compressCurvStructs.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 12:49:58
//

// Include Files
#include "compressCurvStructs.h"
#include "EvalCurvStruct.h"
#include "LengthCurv.h"
#include "SplineLengthApproxGL_tot.h"
#include "bspline_eval.h"
#include "bsxfun.h"
#include "constrBaseSpline.h"
#include "constrCurvStruct.h"
#include "constrSplineStruct.h"
#include "diag.h"
#include "diff.h"
#include "norm.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "sum.h"
#include "tridiag.h"
#include "c_spline.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <cmath>
#include <emmintrin.h>
#include <stdio.h>

// Function Declarations
namespace ocn {
static void
create_spline(const bool ctx_cfg_maskTot_data[], const int ctx_cfg_maskTot_size[2],
              int ctx_cfg_NumberAxis, int ctx_cfg_LeeSplineDegree, double ctx_cfg_GaussLegendreN,
              const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
              const ::coder::array<double, 2U> &batch_pvec, bool batch_lastCurv_Info_TRAFO,
              bool batch_lastCurv_Info_HSC, double batch_lastCurv_Info_FeedRate,
              double batch_lastCurv_Info_SpindleSpeed, int batch_lastCurv_Info_gcode_source_line,
              bool batch_lastCurv_Info_G91, bool batch_lastCurv_Info_G91_1,
              const Tool *batch_lastCurv_tool, ZSpdMode batch_zspdmode, unsigned int *spline_index,
              CurvStruct *curv, CurvStruct *spline);

}

// Function Definitions
//
// function [ curv, spline, spline_index ] = create_spline( ctx, batch, spline_index )
//
// Arguments    : const bool ctx_cfg_maskTot_data[]
//                const int ctx_cfg_maskTot_size[2]
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_LeeSplineDegree
//                double ctx_cfg_GaussLegendreN
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const ::coder::array<double, 2U> &batch_pvec
//                bool batch_lastCurv_Info_TRAFO
//                bool batch_lastCurv_Info_HSC
//                double batch_lastCurv_Info_FeedRate
//                double batch_lastCurv_Info_SpindleSpeed
//                int batch_lastCurv_Info_gcode_source_line
//                bool batch_lastCurv_Info_G91
//                bool batch_lastCurv_Info_G91_1
//                const Tool *batch_lastCurv_tool
//                ZSpdMode batch_zspdmode
//                unsigned int *spline_index
//                CurvStruct *curv
//                CurvStruct *spline
// Return Type  : void
//
namespace ocn {
static void
create_spline(const bool ctx_cfg_maskTot_data[], const int ctx_cfg_maskTot_size[2],
              int ctx_cfg_NumberAxis, int ctx_cfg_LeeSplineDegree, double ctx_cfg_GaussLegendreN,
              const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
              const ::coder::array<double, 2U> &batch_pvec, bool batch_lastCurv_Info_TRAFO,
              bool batch_lastCurv_Info_HSC, double batch_lastCurv_Info_FeedRate,
              double batch_lastCurv_Info_SpindleSpeed, int batch_lastCurv_Info_gcode_source_line,
              bool batch_lastCurv_Info_G91, bool batch_lastCurv_Info_G91_1,
              const Tool *batch_lastCurv_tool, ZSpdMode batch_zspdmode, unsigned int *spline_index,
              CurvStruct *curv, CurvStruct *spline)
{
    __m128d r5;
    ::coder::array<double, 2U> A;
    ::coder::array<double, 2U> B;
    ::coder::array<double, 2U> BasisVal;
    ::coder::array<double, 2U> BasisValDD0;
    ::coder::array<double, 2U> BasisValDD1;
    ::coder::array<double, 2U> Umat;
    ::coder::array<double, 2U> b_spline;
    ::coder::array<double, 2U> breakpoints;
    ::coder::array<double, 2U> c;
    ::coder::array<double, 2U> c_A;
    ::coder::array<double, 2U> c_B;
    ::coder::array<double, 2U> c_c;
    ::coder::array<double, 2U> d_B;
    ::coder::array<double, 2U> d_c;
    ::coder::array<double, 2U> du_tmp;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r11;
    ::coder::array<double, 2U> r13;
    ::coder::array<double, 2U> r14;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r1Dnorm;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> r7;
    ::coder::array<double, 2U> u;
    ::coder::array<double, 1U> d;
    ::coder::array<double, 1U> r4;
    ::coder::array<double, 1U> v;
    ::coder::array<double, 1U> v_l;
    ::coder::array<double, 1U> v_m;
    ::coder::array<double, 1U> v_u;
    double dv[6];
    double dv1[6];
    double b_ctx_cfg_GaussLegendreX[5];
    double dv2[5];
    double b_u;
    double d1;
    double d2;
    double d3;
    double w;
    int ab_loop_ub;
    int b_A;
    int b_B;
    int b_dlen;
    int b_input_sizes_idx_0;
    int b_input_sizes_idx_0_tmp;
    int b_loop_ub;
    int b_result;
    int b_scalarLB;
    int b_u0;
    int b_u1;
    int b_unnamed_idx_2;
    int b_unnamed_idx_3;
    int b_vectorUB;
    int cb_loop_ub;
    int d_loop_ub;
    int db_loop_ub;
    int dlen;
    int e_input_sizes_idx_0;
    int end;
    int f_loop_ub;
    int g_loop_ub;
    int gb_loop_ub;
    int h_loop_ub;
    int hb_loop_ub;
    int i35;
    int i37;
    int i43;
    int i44;
    int i51;
    int i52;
    int i53;
    int i54;
    int i55;
    int i61;
    int i62;
    int i63;
    int i67;
    int i73;
    int i_loop_ub;
    int input_sizes_idx_0_tmp;
    int j_loop_ub;
    int k_loop_ub;
    int loop_ub;
    int loop_ub_tmp;
    int nCoeff;
    int o_loop_ub;
    int p_loop_ub;
    int partialTrueCount;
    int q_loop_ub;
    int r_loop_ub;
    int result;
    int s_loop_ub;
    int scalarLB;
    int t_loop_ub;
    int trueCount;
    int u0;
    int u1;
    unsigned int unnamed_idx_0;
    int unnamed_idx_1;
    int unnamed_idx_2;
    int unnamed_idx_3;
    int v_loop_ub;
    int vectorUB;
    signed char tmp_data[6];
    signed char c_input_sizes_idx_0;
    signed char d_input_sizes_idx_0;
    signed char f_input_sizes_idx_0;
    signed char input_sizes_idx_0;
    bool b_empty_non_axis_sizes;
    bool empty_non_axis_sizes;
    // 'compressCurvStructs:182' batch.lastCurv.Info.zspdmode = batch.zspdmode;
    // 'compressCurvStructs:184' curv    = constrSplineStruct( ...
    // 'compressCurvStructs:185'                               batch.lastCurv.Info, ...
    // 'compressCurvStructs:186'                               batch.lastCurv.tool, ...
    // 'compressCurvStructs:187'                               batch.pvec( :, 1 ), ...
    // 'compressCurvStructs:188'                               batch.pvec( :,end ), ...
    // 'compressCurvStructs:189'                               uint32( spline_index ) );
    for (int i{0}; i < 6; i++) {
        dv[i] = (*(double(*)[6]) & batch_pvec[0])[i];
    }
    for (int i1{0}; i1 < 6; i1++) {
        dv1[i1] = (*(double(*)[6]) & batch_pvec[6 * (batch_pvec.size(1) - 1)])[i1];
    }
    constrSplineStruct(batch_zspdmode, batch_lastCurv_Info_TRAFO, batch_lastCurv_Info_HSC,
                       batch_lastCurv_Info_FeedRate, batch_lastCurv_Info_SpindleSpeed,
                       batch_lastCurv_Info_gcode_source_line, batch_lastCurv_Info_G91,
                       batch_lastCurv_Info_G91_1, batch_lastCurv_tool->toolno,
                       batch_lastCurv_tool->pocketno, &batch_lastCurv_tool->offset,
                       batch_lastCurv_tool->diameter, batch_lastCurv_tool->frontangle,
                       batch_lastCurv_tool->backangle, batch_lastCurv_tool->orientation, dv, dv1,
                       *spline_index, curv);
    // 'compressCurvStructs:191' spline            = curv;
    *spline = *curv;
    // 'compressCurvStructs:192' spline.sp         = CalcBspline_Lee( ctx.cfg, batch.pvec(
    // ctx.cfg.maskTot, : ) );
    end = ctx_cfg_maskTot_size[1] - 1;
    trueCount = 0;
    partialTrueCount = 0;
    for (int b_i{0}; b_i <= end; b_i++) {
        if (ctx_cfg_maskTot_data[b_i]) {
            trueCount++;
            tmp_data[partialTrueCount] = static_cast<signed char>(b_i + 1);
            partialTrueCount++;
        }
    }
    //  CalcBspline_Lee :
    //
    //  INPUT
    //  cfg       : struct : Configuration variables
    //  points    :   nDxN : Set of points in n dimension for the spline
    //
    //  OUTPUT
    //  spnD      : struct : Output spline structure
    // 'CalcBspline_Lee:11' [ ~, N ] = size( points );
    //  number of points in nD space
    // 'CalcBspline_Lee:12' nAxis    = cfg.NumberAxis;
    // 'CalcBspline_Lee:13' nMult    = cfg.LeeSplineDegree - 1;
    //  Number of multiplicity at start and end ( clamped BSpline )
    // 'CalcBspline_Lee:14' nCoeff   = N + 2;
    // 'CalcBspline_Lee:16' du     = sum( ( diff( points.' ).^2 ).' );
    loop_ub = batch_pvec.size(1);
    du_tmp.set_size(batch_pvec.size(1), trueCount);
    for (int i2{0}; i2 < trueCount; i2++) {
        for (int i3{0}; i3 < loop_ub; i3++) {
            du_tmp[i3 + du_tmp.size(0) * i2] = batch_pvec[(tmp_data[i2] + 6 * i3) - 1];
        }
    }
    // 'CalcBspline_Lee:17' u      = cumsum( [ 0, du.^( 1 / 4 ) ] );
    coder::diff(du_tmp, r);
    b_loop_ub = r.size(1);
    for (int i4{0}; i4 < b_loop_ub; i4++) {
        int c_loop_ub;
        c_loop_ub = r.size(0);
        for (int i5{0}; i5 < c_loop_ub; i5++) {
            double varargin_1;
            varargin_1 = r[i5 + r.size(0) * i4];
            r[i5 + r.size(0) * i4] = std::pow(varargin_1, 2.0);
        }
    }
    r1.set_size(r.size(1), r.size(0));
    d_loop_ub = r.size(0);
    for (int i6{0}; i6 < d_loop_ub; i6++) {
        int e_loop_ub;
        e_loop_ub = r.size(1);
        for (int i7{0}; i7 < e_loop_ub; i7++) {
            r1[i7 + r1.size(0) * i6] = r[i6 + r.size(0) * i7];
        }
    }
    coder::sum(r1, r2);
    r2.set_size(1, r2.size(1));
    f_loop_ub = r2.size(1);
    for (int i8{0}; i8 < f_loop_ub; i8++) {
        double b_varargin_1;
        b_varargin_1 = r2[i8];
        r2[i8] = std::pow(b_varargin_1, 0.25);
    }
    u.set_size(1, r2.size(1) + 1);
    u[0] = 0.0;
    g_loop_ub = r2.size(1);
    for (int i9{0}; i9 < g_loop_ub; i9++) {
        u[i9 + 1] = r2[i9];
    }
    if (u.size(1) != 1) {
        int i10;
        i10 = u.size(1);
        for (int k{0}; k <= i10 - 2; k++) {
            u[k + 1] = u[k] + u[k + 1];
        }
    }
    // 'CalcBspline_Lee:18' u      = u / u( end );
    b_u = u[u.size(1) - 1];
    u.set_size(1, u.size(1));
    h_loop_ub = u.size(1);
    scalarLB = (u.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i11{0}; i11 <= vectorUB; i11 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&u[i11]);
        _mm_storeu_pd(&u[i11], _mm_div_pd(r3, _mm_set1_pd(b_u)));
    }
    for (int i11{scalarLB}; i11 < h_loop_ub; i11++) {
        u[i11] = u[i11] / b_u;
    }
    //  normalize knots to interval [0...1]
    // 'CalcBspline_Lee:19' knots  = [ zeros( 1, nMult ), u, ones( 1, nMult ) ];
    spline->sp.knots.set_size(1, ((ctx_cfg_LeeSplineDegree + u.size(1)) + ctx_cfg_LeeSplineDegree) -
                                     2);
    loop_ub_tmp = ctx_cfg_LeeSplineDegree - 1;
    for (int i12{0}; i12 < loop_ub_tmp; i12++) {
        spline->sp.knots[i12] = 0.0;
    }
    i_loop_ub = u.size(1);
    for (int i13{0}; i13 < i_loop_ub; i13++) {
        spline->sp.knots[(i13 + ctx_cfg_LeeSplineDegree) - 1] = u[i13];
    }
    for (int i14{0}; i14 < loop_ub_tmp; i14++) {
        spline->sp.knots[((i14 + ctx_cfg_LeeSplineDegree) + u.size(1)) - 1] = 1.0;
    }
    // 'CalcBspline_Lee:21' Bl = bspline_create( cfg.LeeSplineDegree, u );
    // 'bspline_create:2' if  coder.target('rtw') || coder.target('mex')
    // 'bspline_create:3' nbreak = length(breakpoints);
    // 'bspline_create:4' ncoeff = nbreak + degree - 2;
    // 'bspline_create:5' h = uint64(0);
    // 'bspline_create:6' my_path = StructTypeName.WDIR + "/src";
    // 'bspline_create:7' coder.updateBuildInfo('addIncludePaths',my_path);
    // 'bspline_create:8' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
    // 'bspline_create:9' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_create:10' coder.cinclude('c_spline.h');
    // 'bspline_create:11' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), degree,
    // breakpoints, int32(nbreak) );
    breakpoints.set_size(1, u.size(1));
    j_loop_ub = u.size(1);
    for (int i15{0}; i15 < j_loop_ub; i15++) {
        breakpoints[i15] = u[i15];
    }
    unsigned long h;
    c_bspline_create_with_breakpoints(&h, ctx_cfg_LeeSplineDegree, &breakpoints[0], u.size(1));
    // 'bspline_create:12' Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
    constrBaseSpline((u.size(1) + ctx_cfg_LeeSplineDegree) - 2, u, h, ctx_cfg_LeeSplineDegree,
                     &spline->sp.Bl);
    // 'CalcBspline_Lee:23' [ BasisVal, BasisValDD0, BasisValDD1 ] = bspline_eval_lee( Bl, int32(
    // nCoeff ), u );
    nCoeff = batch_pvec.size(1) + 2;
    // 'bspline_eval_lee:3' assert( all( u_vec >= 0, 'all' ), "ERROR : u_vec should be greater or
    // equal to 0" ); 'bspline_eval_lee:4' assert( all( u_vec <= 1, 'all' ), "ERROR : u_vec should
    // be lower or equal to 1" ); 'bspline_eval_lee:6' if ( coder.target('rtw') ||
    // coder.target('mex') ) 'bspline_eval_lee:7' N = numel( u_vec ); 'bspline_eval_lee:9' BasisVal
    // = zeros( N, nCoeff );
    BasisVal.set_size(u.size(1), batch_pvec.size(1) + 2);
    k_loop_ub = batch_pvec.size(1) + 2;
    for (int i16{0}; i16 < k_loop_ub; i16++) {
        int l_loop_ub;
        l_loop_ub = u.size(1);
        for (int i17{0}; i17 < l_loop_ub; i17++) {
            BasisVal[i17 + BasisVal.size(0) * i16] = 0.0;
        }
    }
    // 'bspline_eval_lee:10' BasisValDD0 = BasisVal( 1, : );
    BasisValDD0.set_size(1, batch_pvec.size(1) + 2);
    // 'bspline_eval_lee:11' BasisValDD1 = BasisValDD0;
    BasisValDD1.set_size(1, batch_pvec.size(1) + 2);
    for (int i18{0}; i18 < nCoeff; i18++) {
        BasisValDD0[i18] = 0.0;
        BasisValDD1[i18] = 0.0;
    }
    // 'bspline_eval_lee:13' my_path = StructTypeName.WDIR + "/src";
    // 'bspline_eval_lee:14' coder.updateBuildInfo('addIncludePaths',my_path);
    // 'bspline_eval_lee:15' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
    // 'bspline_eval_lee:16' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_eval_lee:17' coder.cinclude('c_spline.h');
    // 'bspline_eval_lee:19' coder.ceval('c_bspline_base_eval_lee', coder.rref(Bl.handle), ...
    // 'bspline_eval_lee:20'             int32( nCoeff ), int32( N ), coder.rref( u_vec ), ...
    // 'bspline_eval_lee:21'             coder.wref( BasisVal ), coder.wref( BasisValDD0 ), ...
    // 'bspline_eval_lee:22'             coder.wref( BasisValDD1 ) );
    c_bspline_base_eval_lee(&spline->sp.Bl.handle, batch_pvec.size(1) + 2, u.size(1), &u[0],
                            &BasisVal[0], &BasisValDD0[0], &BasisValDD1[0]);
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
    for (int i19{0}; i19 < result; i19++) {
        for (int i21{0}; i21 < input_sizes_idx_0_tmp; i21++) {
            A[A.size(0) * i19] = BasisValDD0[input_sizes_idx_0 * i19];
        }
    }
    for (int i20{0}; i20 < result; i20++) {
        for (int i23{0}; i23 < b_input_sizes_idx_0; i23++) {
            A[(i23 + input_sizes_idx_0) + A.size(0) * i20] =
                BasisVal[i23 + b_input_sizes_idx_0 * i20];
        }
    }
    for (int i22{0}; i22 < result; i22++) {
        for (int i24{0}; i24 < b_input_sizes_idx_0_tmp; i24++) {
            A[(input_sizes_idx_0 + b_input_sizes_idx_0) + A.size(0) * i22] =
                BasisValDD1[c_input_sizes_idx_0 * i22];
        }
    }
    //
    // 'CalcBspline_Lee:28' B = [zeros(1, nAxis);
    // 'CalcBspline_Lee:29'             points.';
    // 'CalcBspline_Lee:30'      zeros(1, nAxis)];
    if (ctx_cfg_NumberAxis != 0) {
        b_result = ctx_cfg_NumberAxis;
    } else if ((du_tmp.size(0) != 0) && (du_tmp.size(1) != 0)) {
        b_result = du_tmp.size(1);
    } else {
        b_result = 0;
        if (du_tmp.size(1) > 0) {
            b_result = du_tmp.size(1);
        }
    }
    b_empty_non_axis_sizes = (b_result == 0);
    if (b_empty_non_axis_sizes || (ctx_cfg_NumberAxis != 0)) {
        d_input_sizes_idx_0 = 1;
    } else {
        d_input_sizes_idx_0 = 0;
    }
    if (b_empty_non_axis_sizes || ((du_tmp.size(0) != 0) && (du_tmp.size(1) != 0))) {
        e_input_sizes_idx_0 = du_tmp.size(0);
    } else {
        e_input_sizes_idx_0 = 0;
    }
    if (b_empty_non_axis_sizes || (ctx_cfg_NumberAxis != 0)) {
        f_input_sizes_idx_0 = 1;
    } else {
        f_input_sizes_idx_0 = 0;
    }
    B.set_size((d_input_sizes_idx_0 + e_input_sizes_idx_0) + f_input_sizes_idx_0, b_result);
    for (int i25{0}; i25 < b_result; i25++) {
        int m_loop_ub;
        m_loop_ub = d_input_sizes_idx_0;
        for (int i27{0}; i27 < m_loop_ub; i27++) {
            B[B.size(0) * i25] = 0.0;
        }
    }
    for (int i26{0}; i26 < b_result; i26++) {
        for (int i29{0}; i29 < e_input_sizes_idx_0; i29++) {
            B[(i29 + d_input_sizes_idx_0) + B.size(0) * i26] =
                du_tmp[i29 + e_input_sizes_idx_0 * i26];
        }
    }
    for (int i28{0}; i28 < b_result; i28++) {
        int n_loop_ub;
        n_loop_ub = f_input_sizes_idx_0;
        for (int i30{0}; i30 < n_loop_ub; i30++) {
            B[(d_input_sizes_idx_0 + e_input_sizes_idx_0) + B.size(0) * i28] = 0.0;
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
    for (int i31{0}; i31 <= b_A; i31++) {
        c_A[4 * i31] = A[A.size(0) * i31 + 1];
        c_A[4 * i31 + 1] = A[A.size(0) * i31];
        c_A[4 * i31 + 2] = A[b_unnamed_idx_2 + A.size(0) * i31];
        c_A[4 * i31 + 3] = A[b_unnamed_idx_3 + A.size(0) * i31];
    }
    o_loop_ub = c_A.size(1);
    for (int i32{0}; i32 < o_loop_ub; i32++) {
        A[A.size(0) * i32] = c_A[4 * i32];
        A[A.size(0) * i32 + 1] = c_A[4 * i32 + 1];
        A[unnamed_idx_2 + A.size(0) * i32] = c_A[4 * i32 + 2];
        A[unnamed_idx_3 + A.size(0) * i32] = c_A[4 * i32 + 3];
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
    for (int i33{0}; i33 <= b_B; i33++) {
        c_B[4 * i33] = B[B.size(0) * i33 + 1];
        c_B[4 * i33 + 1] = B[B.size(0) * i33];
        c_B[4 * i33 + 2] = B[b_unnamed_idx_2 + B.size(0) * i33];
        c_B[4 * i33 + 3] = B[b_unnamed_idx_3 + B.size(0) * i33];
    }
    p_loop_ub = c_B.size(1);
    for (int i34{0}; i34 < p_loop_ub; i34++) {
        B[B.size(0) * i34] = c_B[4 * i34];
        B[B.size(0) * i34 + 1] = c_B[4 * i34 + 1];
        B[unnamed_idx_2 + B.size(0) * i34] = c_B[4 * i34 + 2];
        B[unnamed_idx_3 + B.size(0) * i34] = c_B[4 * i34 + 3];
    }
    // 'CalcBspline_Lee:34' [ v_m, v_l, v_u ] = extract_vectors( A );
    //  Extract the three vectors of the triagonal matrix A.
    //  Output :
    //  v_m   :   The vector of the middle of the matrix
    //  v_l   :   The vector of the lower diagonal of the matrix
    //  v_u   :   The vector of the upper diagonal of the matrix
    // 'CalcBspline_Lee:55' v_m = diag( A );
    u0 = A.size(0);
    u1 = A.size(1);
    if (u0 <= u1) {
        dlen = u0;
    } else {
        dlen = u1;
    }
    v_m.set_size(dlen);
    i35 = dlen - 1;
    for (int b_k{0}; b_k <= i35; b_k++) {
        v_m[b_k] = A[b_k + A.size(0) * b_k];
    }
    // 'CalcBspline_Lee:56' v_l = [ 0; diag( A, -1 ) ];
    coder::diag(A, r4);
    v_l.set_size(r4.size(0) + 1);
    v_l[0] = 0.0;
    q_loop_ub = r4.size(0);
    for (int i36{0}; i36 < q_loop_ub; i36++) {
        v_l[i36 + 1] = r4[i36];
    }
    // 'CalcBspline_Lee:57' v_u = [ diag( A, 1 ); 0 ];
    b_u0 = A.size(0);
    b_u1 = A.size(1) - 1;
    if (b_u0 <= b_u1) {
        b_dlen = b_u0;
    } else {
        b_dlen = b_u1;
    }
    d.set_size(b_dlen);
    i37 = b_dlen - 1;
    for (int c_k{0}; c_k <= i37; c_k++) {
        d[c_k] = A[c_k + A.size(0) * (c_k + 1)];
    }
    v_u.set_size(d.size(0) + 1);
    r_loop_ub = d.size(0);
    for (int i38{0}; i38 < r_loop_ub; i38++) {
        v_u[i38] = d[i38];
    }
    v_u[d.size(0)] = 0.0;
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
    s_loop_ub = B.size(0);
    for (int i39{0}; i39 < s_loop_ub; i39++) {
        v[i39] = 0.0;
    }
    // 'tridiag:20' y         = zeros( size( f ) );
    unnamed_idx_0 = static_cast<unsigned int>(B.size(0));
    c.set_size(B.size(0), B.size(1));
    t_loop_ub = B.size(1);
    for (int i40{0}; i40 < t_loop_ub; i40++) {
        int u_loop_ub;
        u_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i41{0}; i41 < u_loop_ub; i41++) {
            c[i41 + c.size(0) * i40] = 0.0;
        }
    }
    // 'tridiag:21' w         = a( 1 );
    w = v_m[0];
    // 'tridiag:22' y( 1, : ) = f( 1, : ) / w;
    v_loop_ub = B.size(1);
    for (int i42{0}; i42 < v_loop_ub; i42++) {
        c[c.size(0) * i42] = B[B.size(0) * i42] / v_m[0];
    }
    // 'tridiag:24' for i = 2 : n
    i43 = B.size(0);
    for (int c_i{0}; c_i <= i43 - 2; c_i++) {
        double b_d;
        double w_tmp;
        int w_loop_ub;
        // 'tridiag:25' v( i -1 ) = c( i -1 ) / w;
        b_d = v_u[c_i] / w;
        v[c_i] = b_d;
        // 'tridiag:26' w         = a( i ) - b( i ) * v( i -1 );
        w_tmp = v_l[c_i + 1];
        w = v_m[c_i + 1] - w_tmp * b_d;
        // 'tridiag:27' y( i, : ) = ( f( i, : ) - b( i ) * y( i -1, : ) ) / w;
        w_loop_ub = B.size(1);
        if (B.size(1) == c.size(1)) {
            int y_loop_ub;
            d_B.set_size(1, B.size(1));
            for (int i46{0}; i46 < w_loop_ub; i46++) {
                d_B[i46] = (B[(c_i + B.size(0) * i46) + 1] - w_tmp * c[c_i + c.size(0) * i46]) / w;
            }
            y_loop_ub = d_B.size(1);
            for (int i48{0}; i48 < y_loop_ub; i48++) {
                c[(c_i + c.size(0) * i48) + 1] = d_B[i48];
            }
        } else {
            binary_expand_op(c, c_i, B, v_l, w);
        }
    }
    // 'tridiag:30' for j = n-1 : -1 : 1
    i44 = B.size(0);
    for (int j{0}; j <= i44 - 2; j++) {
        int b_c;
        int b_j;
        int x_loop_ub;
        b_j = (B.size(0) - j) - 2;
        // 'tridiag:31' y( j, : ) = y( j, : ) - v( j ) * y( j + 1, : );
        b_c = c.size(1) - 1;
        c_c.set_size(1, c.size(1));
        for (int i45{0}; i45 <= b_c; i45++) {
            c_c[i45] = c[b_j + c.size(0) * i45] - v[b_j] * c[(b_j + c.size(0) * i45) + 1];
        }
        x_loop_ub = c_c.size(1);
        for (int i47{0}; i47 < x_loop_ub; i47++) {
            c[b_j + c.size(0) * i47] = c_c[i47];
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
    spline->sp.coeff.set_size(c.size(1), c.size(0));
    ab_loop_ub = c.size(0);
    for (int i49{0}; i49 < ab_loop_ub; i49++) {
        int bb_loop_ub;
        bb_loop_ub = c.size(1);
        for (int i50{0}; i50 < bb_loop_ub; i50++) {
            spline->sp.coeff[i50 + spline->sp.coeff.size(0) * i49] = c[i49 + c.size(0) * i50];
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
    // 'constrSpline:23' if ~coder.target( 'MATLAB' )
    // 'constrSpline:24' coder.varsize( 'SplineStrct.Lk',    StructTypeName.dimLk{ : } );
    // 'constrSpline:25' coder.varsize( 'SplineStrct.coeff', StructTypeName.dimCoeffs{ : } );
    // 'constrSpline:26' coder.varsize( 'SplineStrct.knots', StructTypeName.dimKnots{ : } );
    // 'constrSpline:27' coder.cstructname( SplineStrct.Bl, StructTypeName.BaseSpline );
    // 'constrSpline:28' coder.cstructname( SplineStrct, StructTypeName.Spline );
    // 'compressCurvStructs:193' [ Ltot, Lk ]      = SplineLengthApproxGL_tot( ctx.cfg, spline );
    //  Precomputes approximately the total arc length L as well as the individual
    //  arc lengths between knot points of a parametric spline.
    //  The computation is based on numerical Gauss Legendre integration.
    //  SplineLengthApproxGL_tot should only be called once since the result
    //  of the computation is stored and reused later.
    //  get the sp structure
    //  Spline = ctx.q_spline.get(Curv.sp_index);
    //  sp     = Spline.sp;
    // 'SplineLengthApproxGL_tot:11' sp     = Curv.sp;
    // 'SplineLengthApproxGL_tot:12' Knots  = sp.knots(4:end-3);
    if (spline->sp.knots.size(1) - 3 < 4) {
        i51 = 0;
        i52 = -1;
    } else {
        i51 = 3;
        i52 = spline->sp.knots.size(1) - 4;
    }
    //  eliminate multiplicities at the end points
    // 'SplineLengthApproxGL_tot:13' a      = Knots(1:end-1);
    i53 = i52 - i51;
    if (i53 < 1) {
        cb_loop_ub = 0;
    } else {
        cb_loop_ub = i52 - i51;
    }
    //  lower integration limits
    // 'SplineLengthApproxGL_tot:14' b      = Knots(2:end);
    if (i53 + 1 < 2) {
        i54 = -1;
        i55 = -1;
    } else {
        i54 = 0;
        i55 = i53;
    }
    //  upper integration limits
    //  get Gauss-Legendre knots and weights
    // 'SplineLengthApproxGL_tot:16' GL_N   = cfg.GaussLegendreN;
    // 'SplineLengthApproxGL_tot:17' GL_X   = cfg.GaussLegendreX;
    // 'SplineLengthApproxGL_tot:18' GL_W   = cfg.GaussLegendreW;
    //  apply linear map from[-1, 1] to [a, b]
    // 'SplineLengthApproxGL_tot:20' Umat   = (bsxfun(@times, a, (1-GL_X)) + bsxfun(@times, b,
    // (1+GL_X)))/2;
    b_spline.set_size(1, cb_loop_ub);
    for (int i56{0}; i56 < cb_loop_ub; i56++) {
        b_spline[i56] = spline->sp.knots[i51 + i56];
    }
    r5 = _mm_set1_pd(1.0);
    _mm_storeu_pd(&dv2[0],
                  _mm_sub_pd(r5, _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0])));
    _mm_storeu_pd(&dv2[2],
                  _mm_sub_pd(r5, _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2])));
    dv2[4] = 1.0 - ctx_cfg_GaussLegendreX[4];
    coder::bsxfun(b_spline, dv2, r6);
    db_loop_ub = i55 - i54;
    b_spline.set_size(1, db_loop_ub);
    for (int i57{0}; i57 < db_loop_ub; i57++) {
        b_spline[i57] = spline->sp.knots[((i51 + i54) + i57) + 1];
    }
    _mm_storeu_pd(&b_ctx_cfg_GaussLegendreX[0],
                  _mm_add_pd(_mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0]), r5));
    _mm_storeu_pd(&b_ctx_cfg_GaussLegendreX[2],
                  _mm_add_pd(_mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2]), r5));
    b_ctx_cfg_GaussLegendreX[4] = ctx_cfg_GaussLegendreX[4] + 1.0;
    coder::bsxfun(b_spline, b_ctx_cfg_GaussLegendreX, r7);
    if (r6.size(1) == r7.size(1)) {
        int eb_loop_ub;
        Umat.set_size(5, r6.size(1));
        eb_loop_ub = r6.size(1);
        for (int i58{0}; i58 < eb_loop_ub; i58++) {
            __m128d r10;
            __m128d r8;
            __m128d r9;
            r8 = _mm_loadu_pd(&r6[5 * i58]);
            r9 = _mm_loadu_pd(&r7[5 * i58]);
            r10 = _mm_set1_pd(2.0);
            _mm_storeu_pd(&Umat[5 * i58], _mm_div_pd(_mm_add_pd(r8, r9), r10));
            r8 = _mm_loadu_pd(&r6[5 * i58 + 2]);
            r9 = _mm_loadu_pd(&r7[5 * i58 + 2]);
            _mm_storeu_pd(&Umat[5 * i58 + 2], _mm_div_pd(_mm_add_pd(r8, r9), r10));
            Umat[5 * i58 + 4] = (r6[5 * i58 + 4] + r7[5 * i58 + 4]) / 2.0;
        }
    } else {
        c_binary_expand_op(Umat, r6, r7);
    }
    // 'SplineLengthApproxGL_tot:21' Uvec   = Umat(:)';
    //  all evaluation points as row vector
    // 'SplineLengthApproxGL_tot:23' [~, r1D]  = EvalBSpline(Curv, Uvec);
    //  EvalBSpline
    //
    //  INPUT
    //  spline        : struct : Spline structure
    //  u_vec         :    1xn : Vector for evaluation of the curv
    //
    //  OUTPUT
    //  r0D           :   nDxn : The evaluated B spline at u\_vec points
    //  r1D           :   nDxn : 1rst order parametric derivative for the B spline at u\_vec points
    //  r2D           :   nDxn : 2nd order parametric derivative for the B spline at u\_vec points
    //  r3D           :   nDxn : 3rd order parametric derivative for the B spline at u\_vec points
    // 'EvalBSpline:14' sp = spline.sp;
    // 'EvalBSpline:15' N  = length( u_vec );
    // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
    // 'EvalBSpline:18' r0D = zeros( M, N );
    unnamed_idx_1 = 5 * Umat.size(1);
    // 'EvalBSpline:18' r1D = r0D;
    r1D.set_size(spline->sp.coeff.size(0), unnamed_idx_1);
    for (int i59{0}; i59 < unnamed_idx_1; i59++) {
        int fb_loop_ub;
        fb_loop_ub = spline->sp.coeff.size(0);
        for (int i60{0}; i60 < fb_loop_ub; i60++) {
            r1D[i60 + r1D.size(0) * i59] = 0.0;
        }
    }
    // 'EvalBSpline:18' r2D = r1D;
    // 'EvalBSpline:18' r3D = r2D;
    // 'EvalBSpline:20' for j = 1 : M
    i61 = spline->sp.coeff.size(0);
    if (spline->sp.coeff.size(0) - 1 >= 0) {
        i62 = 5 * Umat.size(1);
        if (i62 - 1 >= 0) {
            i63 = spline->sp.coeff.size(1);
            gb_loop_ub = spline->sp.coeff.size(1);
        }
    }
    for (int c_j{0}; c_j < i61; c_j++) {
        unsigned int b_unnamed_idx_1;
        int ib_loop_ub;
        int kb_loop_ub;
        int lb_loop_ub;
        int mb_loop_ub;
        int nb_loop_ub;
        // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
        // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, : ),
        // u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u));
        b_unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
        r2.set_size(1, static_cast<int>(b_unnamed_idx_1));
        ib_loop_ub = static_cast<int>(b_unnamed_idx_1);
        for (int i65{0}; i65 < ib_loop_ub; i65++) {
            r2[i65] = 0.0;
        }
        // 'bspline_eval_vec:4' xd      = zeros(size(u));
        b_unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
        r11.set_size(1, static_cast<int>(b_unnamed_idx_1));
        kb_loop_ub = static_cast<int>(b_unnamed_idx_1);
        for (int i68{0}; i68 < kb_loop_ub; i68++) {
            r11[i68] = 0.0;
        }
        // 'bspline_eval_vec:5' xdd     = zeros(size(u));
        b_unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
        r13.set_size(1, static_cast<int>(b_unnamed_idx_1));
        lb_loop_ub = static_cast<int>(b_unnamed_idx_1);
        for (int i69{0}; i69 < lb_loop_ub; i69++) {
            r13[i69] = 0.0;
        }
        // 'bspline_eval_vec:6' xddd    = zeros(size(u));
        b_unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
        r14.set_size(1, static_cast<int>(b_unnamed_idx_1));
        mb_loop_ub = static_cast<int>(b_unnamed_idx_1);
        for (int i71{0}; i71 < mb_loop_ub; i71++) {
            r14[i71] = 0.0;
        }
        // 'bspline_eval_vec:8' for k = 1:length(u)
        for (int g_k{0}; g_k < i62; g_k++) {
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            r2[g_k] = Umat[g_k];
            b_spline.set_size(1, i63);
            for (int i75{0}; i75 < gb_loop_ub; i75++) {
                b_spline[i75] = spline->sp.coeff[c_j + spline->sp.coeff.size(0) * i75];
            }
            bspline_eval(spline->sp.Bl.handle, b_spline, &r2[g_k], &d1, &d2, &d3);
            r14[g_k] = d3;
            r13[g_k] = d2;
            r11[g_k] = d1;
            // 'bspline_eval_vec:10' x(k)    = xk;
            // 'bspline_eval_vec:11' xd(k)   = xdk;
            // 'bspline_eval_vec:12' xdd(k)  = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
        nb_loop_ub = r11.size(1);
        for (int i74{0}; i74 < nb_loop_ub; i74++) {
            r1D[c_j + r1D.size(0) * i74] = r11[i74];
        }
    }
    // 'SplineLengthApproxGL_tot:24' r1Dnorm   = MyNorm(r1D);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    r.set_size(r1D.size(0), r1D.size(1));
    hb_loop_ub = r1D.size(1);
    for (int i64{0}; i64 < hb_loop_ub; i64++) {
        int jb_loop_ub;
        jb_loop_ub = r1D.size(0);
        for (int i66{0}; i66 < jb_loop_ub; i66++) {
            double c_varargin_1;
            c_varargin_1 = r1D[i66 + r1D.size(0) * i64];
            r[i66 + r.size(0) * i64] = std::pow(c_varargin_1, 2.0);
        }
    }
    coder::sum(r, r1Dnorm);
    // 'mysqrt:3' y = sqrt(x);
    i67 = r1Dnorm.size(1);
    b_scalarLB = (r1Dnorm.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (int d_k{0}; d_k <= b_vectorUB; d_k += 2) {
        __m128d r12;
        r12 = _mm_loadu_pd(&r1Dnorm[d_k]);
        _mm_storeu_pd(&r1Dnorm[d_k], _mm_sqrt_pd(r12));
    }
    for (int d_k{b_scalarLB}; d_k < i67; d_k++) {
        r1Dnorm[d_k] = std::sqrt(r1Dnorm[d_k]);
    }
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'SplineLengthApproxGL_tot:25' r1DnormM  = reshape(r1Dnorm, GL_N, length(Knots)-1);
    // 'SplineLengthApproxGL_tot:26' Lk        = sum(bsxfun(@times, GL_W, r1DnormM)) .* (b-a)/2;
    d_c.set_size(5, i53);
    if (i53 != 0) {
        int b_bcoef;
        int bcoef;
        int i70;
        bcoef = (i53 != 1);
        i70 = i53 - 1;
        b_bcoef = (static_cast<int>(ctx_cfg_GaussLegendreN) != 1);
        for (int e_k{0}; e_k <= i70; e_k++) {
            int varargin_3;
            varargin_3 = bcoef * e_k;
            for (int h_k{0}; h_k < 5; h_k++) {
                d_c[h_k + 5 * e_k] =
                    ctx_cfg_GaussLegendreW[h_k] *
                    r1Dnorm[b_bcoef * h_k + static_cast<int>(ctx_cfg_GaussLegendreN) * varargin_3];
            }
        }
    }
    if (d_c.size(1) == 0) {
        r2.set_size(1, 0);
    } else {
        int i72;
        r2.set_size(1, d_c.size(1));
        i72 = d_c.size(1);
        for (int f_k{0}; f_k < i72; f_k++) {
            r2[f_k] = d_c[5 * f_k];
            r2[f_k] = r2[f_k] + d_c[5 * f_k + 1];
            r2[f_k] = r2[f_k] + d_c[5 * f_k + 2];
            r2[f_k] = r2[f_k] + d_c[5 * f_k + 3];
            r2[f_k] = r2[f_k] + d_c[5 * f_k + 4];
        }
    }
    if (i55 - i54 == 1) {
        i73 = cb_loop_ub;
    } else {
        i73 = i55 - i54;
    }
    if ((db_loop_ub == cb_loop_ub) && (r2.size(1) == i73)) {
        int c_scalarLB;
        int c_vectorUB;
        int ob_loop_ub;
        spline->sp.Lk.set_size(1, r2.size(1));
        ob_loop_ub = r2.size(1);
        c_scalarLB = (r2.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (int i76{0}; i76 <= c_vectorUB; i76 += 2) {
            __m128d r15;
            __m128d r16;
            __m128d r17;
            r15 = _mm_loadu_pd(&spline->sp.knots[((i51 + i54) + i76) + 1]);
            r16 = _mm_loadu_pd(&spline->sp.knots[i51 + i76]);
            r17 = _mm_loadu_pd(&r2[i76]);
            _mm_storeu_pd(&spline->sp.Lk[i76],
                          _mm_div_pd(_mm_mul_pd(r17, _mm_sub_pd(r15, r16)), _mm_set1_pd(2.0)));
        }
        for (int i76{c_scalarLB}; i76 < ob_loop_ub; i76++) {
            spline->sp.Lk[i76] =
                r2[i76] *
                (spline->sp.knots[((i51 + i54) + i76) + 1] - spline->sp.knots[i51 + i76]) / 2.0;
        }
    } else {
        binary_expand_op(spline, r2, i51, i54 + 1, i55, cb_loop_ub - 1);
    }
    //  Gauss Legendre integration
    // 'SplineLengthApproxGL_tot:27' L         = sum(Lk);
    spline->sp.Ltot = coder::sum(spline->sp.Lk);
    // 'compressCurvStructs:194' spline.sp.Ltot    = Ltot;
    // 'compressCurvStructs:195' spline.sp.Lk      = Lk;
    // 'compressCurvStructs:196' spline_index      = spline_index + 1;
    (*spline_index)++;
}

//
// function [ ctx ] = compressCurvStructs( ctx )
//
// CompressCurvStructs :
//  - Is feeded by the queue : q_gcode
//  - Check if a compression is possible based on the individual curves
//  length, the cummulative length and the collinearity of two consecutive
//  segment.
//  - Check speed boundaries conditions (ZZ,ZN,NZ,NN) and split the curves
//  accordingly.
//  - Create a Bspline based on Lee89.
//  - Fill the queue : q_compress
//
//  Note : If compression is not required call ExpandZeroStructs
//
// Arguments    : const b_FeedoptContext *ctx
// Return Type  : void
//
void compressCurvStructs(const b_FeedoptContext *ctx)
{
    ::coder::array<double, 2U> batch_pvec;
    ::coder::array<double, 1U> V0;
    ::coder::array<double, 1U> V1;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    ::coder::array<double, 1U> u;
    ::coder::array<double, 1U> v;
    Axes params_tmp_tool_offset;
    CurvStruct batch_lastCurv;
    CurvStruct batch_lastCurv_tmp;
    CurvStruct curv;
    CurvStruct curvCompressed;
    CurvStruct spline;
    SplineStruct params_tmp_spline;
    double params_tmp_CoeffP5[6];
    double params_tmp_R0[6];
    double params_tmp_R1[6];
    double params_tmp_Cprim[3];
    double params_tmp_evec[3];
    double b_expl_temp;
    double c_expl_temp;
    double d_expl_temp;
    double expl_temp;
    double params_tmp_gcodeInfoStruct_FeedRate;
    double params_tmp_gcodeInfoStruct_SpindleSpeed;
    double params_tmp_tool_backangle;
    double params_tmp_tool_diameter;
    double params_tmp_tool_frontangle;
    unsigned int b_spline_index;
    int params_tmp_gcodeInfoStruct_gcode_source_line;
    int params_tmp_tool_orientation;
    int params_tmp_tool_pocketno;
    int params_tmp_tool_toolno;
    unsigned int spline_index;
    bool params_tmp_gcodeInfoStruct_G91;
    bool params_tmp_gcodeInfoStruct_G91_1;
    bool params_tmp_gcodeInfoStruct_HSC;
    bool params_tmp_gcodeInfoStruct_TRAFO;
    CurveType params_tmp_gcodeInfoStruct_Type;
    ZSpdMode params_tmp_gcodeInfoStruct_zspdmode;
    // 'compressCurvStructs:14' if ctx.q_gcode.isempty()
    if (!ctx->q_gcode.isempty()) {
        double batch_size;
        unsigned int Ncrv;
        int i1;
        ZSpdMode batch_zspdmode;
        // 'compressCurvStructs:16' spline_index        = ctx.q_spline.size() + 1;
        spline_index = ctx->q_spline.size() + 1U;
        //  New index in q_spline
        // 'compressCurvStructs:17' Ncrv                = ctx.q_gcode.size;
        Ncrv = ctx->q_gcode.size();
        //  Number of curve in queue
        // 'compressCurvStructs:18' [ batch ]           = batch_init();
        // 'compressCurvStructs:122' batch = struct( ...
        // 'compressCurvStructs:123'     'pvec',          zeros( StructTypeName.NumberAxisMax, 1
        // ),... 'compressCurvStructs:124'     'lastCurv',      constrCurvStructType,...
        // 'compressCurvStructs:125'     'size',          0, ...
        // 'compressCurvStructs:126'     'zspdmode',      ZSpdMode.NN ...
        // 'compressCurvStructs:127'     );
        //  constrCurvStructType : Constructs a constrCurvStruct with default values.
        // 'constrCurvStructType:4' if( nargin > 0 )
        // 'constrCurvStructType:6' else
        // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
        paramsDefaultCurv(
            &params_tmp_gcodeInfoStruct_Type, &params_tmp_gcodeInfoStruct_zspdmode,
            &params_tmp_gcodeInfoStruct_TRAFO, &params_tmp_gcodeInfoStruct_HSC,
            &params_tmp_gcodeInfoStruct_FeedRate, &params_tmp_gcodeInfoStruct_SpindleSpeed,
            &params_tmp_gcodeInfoStruct_gcode_source_line, &params_tmp_gcodeInfoStruct_G91,
            &params_tmp_gcodeInfoStruct_G91_1, &params_tmp_tool_toolno, &params_tmp_tool_pocketno,
            &params_tmp_tool_offset, &params_tmp_tool_diameter, &params_tmp_tool_frontangle,
            &params_tmp_tool_backangle, &params_tmp_tool_orientation, &params_tmp_spline,
            params_tmp_R0, params_tmp_R1, params_tmp_Cprim, &expl_temp, params_tmp_evec,
            &b_expl_temp, &c_expl_temp, params_tmp_CoeffP5, &d_expl_temp);
        // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
        // 'constrCurvStructType:12' else
        // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct, params.tool, ...
        // 'constrCurvStructType:14'         params.spline, params.R0, params.R1, params.Cprim, ...
        // 'constrCurvStructType:15'         params.delta, params.evec, params.theta, params.pitch,
        // ... 'constrCurvStructType:16'         params.CoeffP5, params.Coeff );
        batch_pvec.set_size(6, 1);
        for (int i{0}; i < 6; i++) {
            batch_pvec[i] = 0.0;
        }
        b_constrCurvStruct(
            params_tmp_gcodeInfoStruct_Type, params_tmp_gcodeInfoStruct_zspdmode,
            params_tmp_gcodeInfoStruct_TRAFO, params_tmp_gcodeInfoStruct_HSC,
            params_tmp_gcodeInfoStruct_FeedRate, params_tmp_gcodeInfoStruct_SpindleSpeed,
            params_tmp_gcodeInfoStruct_gcode_source_line, params_tmp_gcodeInfoStruct_G91,
            params_tmp_gcodeInfoStruct_G91_1, params_tmp_tool_toolno, params_tmp_tool_pocketno,
            &params_tmp_tool_offset, params_tmp_tool_diameter, params_tmp_tool_frontangle,
            params_tmp_tool_backangle, params_tmp_tool_orientation, &params_tmp_spline,
            params_tmp_R0, params_tmp_R1, params_tmp_Cprim, params_tmp_evec, params_tmp_CoeffP5,
            &batch_lastCurv_tmp);
        batch_lastCurv = batch_lastCurv_tmp;
        batch_size = 0.0;
        batch_zspdmode = ZSpdMode_NN;
        // 'compressCurvStructs:129' if( ~coder.target( "MATLAB" ) )
        // 'compressCurvStructs:130' coder.varsize( 'batch.pvec', StructTypeName.dimPvec{ : } );
        // 'compressCurvStructs:20' DebugLog(DebugCfg.Validate, 'Compressing...\n');
        //  1 -> stdout
        //  2 -> stderr
        // 'DebugLog:5' if IsEnabledDebugLog(cfg)
        // 'IsEnabledDebugLog:4' value = false;
        // 'IsEnabledDebugLog:6' if bitget(DebugConfig, int32(cfg))
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:7' value = true;
            // 'DebugLog:6' fprintf( 1, varargin{:} );
            printf("Compressing...\n");
            fflush(stdout);
        }
        // 'compressCurvStructs:22' if( coder.target( "MATLAB" ) )
        // 'compressCurvStructs:26' for k = 1 : Ncrv
        i1 = static_cast<int>(Ncrv);
        for (int k{0}; k < i1; k++) {
            bool addBatch;
            bool closeBatch;
            // 'compressCurvStructs:27' curv = ctx.q_gcode.get( k );
            ctx->q_gcode.get(k + 1U, &curv);
            //  Get next Curve in the queue
            // 'compressCurvStructs:29' [ addBatch ]    = check_add_batch( ctx, curv );
            // -------------------------------------------------------------------------%
            // 'compressCurvStructs:51' if( coder.target( "MATLAB" ) )
            // 'compressCurvStructs:53' addBatch    = true;
            addBatch = true;
            //  Cond 1. Keep only line segments
            // 'compressCurvStructs:56' if( curv.Info.Type ~= CurveType.Line )
            if (curv.Info.Type != CurveType_Line) {
                // 'compressCurvStructs:57' if( coder.target( "MATLAB" ) )
                // 'compressCurvStructs:60' addBatch = false;
                addBatch = false;

                //  Cond 2. Remove to large segment
                // 'compressCurvStructs:63' if( LengthCurv( ctx, curv, 0, 1 ) >
                // ctx.cfg.LThresholdMax )
            } else if (LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                  ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                  ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                  ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                  ctx->cfg.NRot, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                  &curv) > ctx->cfg.LThresholdMax) {
                // 'compressCurvStructs:64' if( coder.target( "MATLAB" ) )
                // 'compressCurvStructs:67' addBatch = false;
                addBatch = false;
            }
            // 'compressCurvStructs:30' [ closeBatch ]  = check_close_batch( ctx, batch, curv,
            // addBatch); 'compressCurvStructs:73' if( coder.target( "MATLAB" ) )
            // 'compressCurvStructs:75' closeBatch = false;
            closeBatch = false;
            // 'compressCurvStructs:77' if( batch.size == 0 )
            if (batch_size != 0.0) {
                bool isSame;
                bool zeroFlag;
                //  Cond 1. Curv not in the batch
                // 'compressCurvStructs:80' if( ~addBatch )
                if (!addBatch) {
                    // 'compressCurvStructs:81' closeBatch = true;
                    closeBatch = true;
                }
                //  Cond 2. Curv require a stop
                // 'compressCurvStructs:85' if( isAZeroStart( curv ) )
                //  isAZeroStart : Return true if the curv starts with zero speed
                //  Input :
                //  curv / Info / ZSpdMode : A structure containning the information of the
                //  curv zero speed.
                // 'isAZeroStart:6' zeroFlag = false;
                zeroFlag = false;
                // 'isAZeroStart:8' [zspdmode, error] = getZspdmode( speed );
                //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                // 'getZspdmode:3' error = false;
                // 'getZspdmode:5' if( isenum( speed ) )
                // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                // 'isAZeroStart:10' if( error )
                // 'isAZeroStart:12' if( zspdmode == ZSpdMode.ZN || ...
                // 'isAZeroStart:13'     zspdmode == ZSpdMode.ZZ )
                if ((curv.Info.zspdmode == ZSpdMode_ZN) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroStart:14' zeroFlag = true;
                    zeroFlag = true;
                }
                if (zeroFlag) {
                    // 'compressCurvStructs:86' if( coder.target( "MATLAB" ) )
                    // 'compressCurvStructs:89' closeBatch = true;
                    closeBatch = true;
                }
                //  Cond 3. Machine parameters are not the same
                // 'compressCurvStructs:93' if( ~isSameMachiningParameters( batch.lastCurv, curv ) )
                //  Check if the machine parameters are equals
                // 'isSameMachiningParameters:3' isSame = false;
                isSame = false;
                // if( curv1.Info.FeedRate ~= curv2.Info.FeedRate ),           return; end
                // 'isSameMachiningParameters:5' if( curv1.Info.SpindleSpeed ~=
                // curv2.Info.SpindleSpeed )
                if ((batch_lastCurv.Info.SpindleSpeed == curv.Info.SpindleSpeed) &&
                    (batch_lastCurv.Info.TRAFO == curv.Info.TRAFO)) {
                    // 'isSameMachiningParameters:6' if( curv1.Info.TRAFO ~= curv2.Info.TRAFO )
                    // 'isSameMachiningParameters:7' isSame = true;
                    isSame = true;
                }
                if (!isSame) {
                    // 'compressCurvStructs:94' if( coder.target( "MATLAB" ) )
                    // 'compressCurvStructs:98' closeBatch = true;
                    closeBatch = true;
                }
                //  Cond 4. If to small don't test the collinearity
                // 'compressCurvStructs:102' if( LengthCurv( ctx, curv, 0, 1 ) <=
                // ctx.cfg.LThresholdMin )
                if (LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                               ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                               ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                               ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                               ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                               &curv) > ctx->cfg.LThresholdMin) {
                    int b_loop_ub;
                    int loop_ub;
                    bool collinear;
                    //  Cond 5. If not collinear lines, create a new batch
                    // 'compressCurvStructs:110' collinear = curvCollinear( ctx, batch.lastCurv,
                    // curv, ... 'compressCurvStructs:111'     ctx.cfg.Compressing.ColTolCosLee );
                    // 'curvCollinear:2' [~, V0] = EvalCurvStruct(ctx, Curv1, 1);
                    d_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                     ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                     ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                     ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                     ctx->cfg.NRot, &batch_lastCurv, a__1, V0);
                    // 'curvCollinear:3' [~, V1] = EvalCurvStruct(ctx, Curv2, 0);
                    e_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                     ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                     ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                     ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                     ctx->cfg.NRot, &curv, a__2, V1);
                    // 'curvCollinear:5' result = collinear(V0(ctx.cfg.indCart),
                    // V1(ctx.cfg.indCart), ToleranceCos);
                    u.set_size(ctx->cfg.indCart.size(0));
                    loop_ub = ctx->cfg.indCart.size(0);
                    for (int i8{0}; i8 < loop_ub; i8++) {
                        u[i8] = V0[ctx->cfg.indCart[i8] - 1];
                    }
                    v.set_size(ctx->cfg.indCart.size(0));
                    b_loop_ub = ctx->cfg.indCart.size(0);
                    for (int i9{0}; i9 < b_loop_ub; i9++) {
                        v[i9] = V1[ctx->cfg.indCart[i9] - 1];
                    }
                    // 'collinear:2' if (norm(u) < eps || norm(v) < eps)
                    if ((coder::b_norm(u) < 2.2204460492503131E-16) ||
                        (coder::b_norm(v) < 2.2204460492503131E-16)) {
                        // 'collinear:3' value = true;
                        collinear = true;
                    } else {
                        double c;
                        int c_loop_ub;
                        int d_loop_ub;
                        // 'collinear:6' cos_angle = dot(u,v)/(MyNorm(u)*MyNorm(v));
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        // 'mysqrt:3' y = sqrt(x);
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                        // 'MyNorm:2' coder.inline('always');
                        // 'MyNorm:3' n = mysqrt(sum(x.^2));
                        // 'mysqrt:3' y = sqrt(x);
                        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
                        sqrt_calls++;
                        // 'collinear:7' value = cos_angle >= tol_cos;
                        c = 0.0;
                        if (ctx->cfg.indCart.size(0) >= 1) {
                            int ixlast;
                            ixlast = ctx->cfg.indCart.size(0);
                            for (int b_k{0}; b_k < ixlast; b_k++) {
                                c += V0[ctx->cfg.indCart[b_k] - 1] * V1[ctx->cfg.indCart[b_k] - 1];
                            }
                        }
                        r.set_size(u.size(0));
                        c_loop_ub = u.size(0);
                        for (int i10{0}; i10 < c_loop_ub; i10++) {
                            double varargin_1;
                            varargin_1 = u[i10];
                            r[i10] = std::pow(varargin_1, 2.0);
                        }
                        r1.set_size(v.size(0));
                        d_loop_ub = v.size(0);
                        for (int i11{0}; i11 < d_loop_ub; i11++) {
                            double b_varargin_1;
                            b_varargin_1 = v[i11];
                            r1[i11] = std::pow(b_varargin_1, 2.0);
                        }
                        collinear = (c / (std::sqrt(coder::sum(r)) * std::sqrt(coder::sum(r1))) >=
                                     ctx->cfg.Compressing.ColTolCosLee);
                    }
                    // 'compressCurvStructs:112' if( ~collinear )
                    if (!collinear) {
                        // 'compressCurvStructs:113' if( coder.target( "MATLAB" ) )
                        // 'compressCurvStructs:116' closeBatch = true;
                        closeBatch = true;
                    }
                } else {
                    // 'compressCurvStructs:103' if( coder.target( "MATLAB" ) )
                }
            }
            // 'compressCurvStructs:32' if( closeBatch )
            if (closeBatch) {
                // 'compressCurvStructs:33' [ ctx, batch, spline_index ] = batch_close( ctx, batch,
                // spline_index ); 'compressCurvStructs:136' if( batch.size == 0 )
                if (batch_size == 0.0) {
                    // 'compressCurvStructs:137' batch = batch_init();
                    // 'compressCurvStructs:122' batch = struct( ...
                    // 'compressCurvStructs:123'     'pvec',          zeros(
                    // StructTypeName.NumberAxisMax, 1 ),... 'compressCurvStructs:124' 'lastCurv',
                    // constrCurvStructType,... 'compressCurvStructs:125'     'size',          0,
                    // ... 'compressCurvStructs:126'     'zspdmode',      ZSpdMode.NN ...
                    // 'compressCurvStructs:127'     );
                    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
                    // 'constrCurvStructType:4' if( nargin > 0 )
                    // 'constrCurvStructType:6' else
                    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
                    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
                    // 'constrCurvStructType:12' else
                    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct,
                    // params.tool, ... 'constrCurvStructType:14'         params.spline, params.R0,
                    // params.R1, params.Cprim, ... 'constrCurvStructType:15'         params.delta,
                    // params.evec, params.theta, params.pitch, ... 'constrCurvStructType:16'
                    // params.CoeffP5, params.Coeff );
                    batch_lastCurv = batch_lastCurv_tmp;
                    // 'compressCurvStructs:129' if( ~coder.target( "MATLAB" ) )
                    // 'compressCurvStructs:130' coder.varsize( 'batch.pvec',
                    // StructTypeName.dimPvec{ : } );
                } else {
                    // 'compressCurvStructs:141' if( batch.size > 1 )
                    if (batch_size > 1.0) {
                        // 'compressCurvStructs:142' [ curvCompressed, spline, spline_index ] = ...
                        // 'compressCurvStructs:143'         create_spline( ctx, batch, spline_index
                        // );
                        create_spline(
                            ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.NumberAxis,
                            ctx->cfg.LeeSplineDegree, ctx->cfg.GaussLegendreN,
                            ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, batch_pvec,
                            batch_lastCurv.Info.TRAFO, batch_lastCurv.Info.HSC,
                            batch_lastCurv.Info.FeedRate, batch_lastCurv.Info.SpindleSpeed,
                            batch_lastCurv.Info.gcode_source_line, batch_lastCurv.Info.G91,
                            batch_lastCurv.Info.G91_1, &batch_lastCurv.tool, batch_zspdmode,
                            &spline_index, &curvCompressed, &spline);
                        // 'compressCurvStructs:145' ctx.q_compress.push( curvCompressed );
                        ctx->q_compress.push(&curvCompressed);
                        // 'compressCurvStructs:146' ctx.q_spline.push( spline );
                        ctx->q_spline.push(&spline);
                    } else {
                        // 'compressCurvStructs:147' else
                        // 'compressCurvStructs:148' ctx.q_compress.push( batch.lastCurv );
                        ctx->q_compress.push(&batch_lastCurv);
                    }
                    // 'compressCurvStructs:151' if( coder.target( "MATLAB" ) )
                    // 'compressCurvStructs:155' batch = batch_init();
                    // 'compressCurvStructs:122' batch = struct( ...
                    // 'compressCurvStructs:123'     'pvec',          zeros(
                    // StructTypeName.NumberAxisMax, 1 ),... 'compressCurvStructs:124' 'lastCurv',
                    // constrCurvStructType,... 'compressCurvStructs:125'     'size',          0,
                    // ... 'compressCurvStructs:126'     'zspdmode',      ZSpdMode.NN ...
                    // 'compressCurvStructs:127'     );
                    //  constrCurvStructType : Constructs a constrCurvStruct with default values.
                    // 'constrCurvStructType:4' if( nargin > 0 )
                    // 'constrCurvStructType:6' else
                    // 'constrCurvStructType:7' [ params ] = paramsDefaultCurv;
                    // 'constrCurvStructType:10' if( coder.target( "MATLAB" ) )
                    // 'constrCurvStructType:12' else
                    // 'constrCurvStructType:13' C = constrCurvStruct( params.gcodeInfoStruct,
                    // params.tool, ... 'constrCurvStructType:14'         params.spline, params.R0,
                    // params.R1, params.Cprim, ... 'constrCurvStructType:15'         params.delta,
                    // params.evec, params.theta, params.pitch, ... 'constrCurvStructType:16'
                    // params.CoeffP5, params.Coeff );
                    batch_lastCurv = batch_lastCurv_tmp;
                    // 'compressCurvStructs:129' if( ~coder.target( "MATLAB" ) )
                    // 'compressCurvStructs:130' coder.varsize( 'batch.pvec',
                    // StructTypeName.dimPvec{ : } );
                }
                batch_pvec.set_size(6, 1);
                for (int i7{0}; i7 < 6; i7++) {
                    batch_pvec[i7] = 0.0;
                }
                batch_size = 0.0;
                batch_zspdmode = ZSpdMode_NN;
            }
            // 'compressCurvStructs:36' if( addBatch )
            if (addBatch) {
                // 'compressCurvStructs:37' [ batch ] = batch_add_curv( batch, curv );
                // 'compressCurvStructs:160' if( batch.size == 0 )
                if (batch_size == 0.0) {
                    double b_curv[2][6];
                    // 'compressCurvStructs:161' batch.pvec      = [ curv.R0, curv.R1 ];
                    for (int i3{0}; i3 < 6; i3++) {
                        b_curv[0][i3] = curv.R0[i3];
                        b_curv[1][i3] = curv.R1[i3];
                    }
                    batch_pvec.set_size(6, 2);
                    for (int i5{0}; i5 < 2; i5++) {
                        for (int i6{0}; i6 < 6; i6++) {
                            batch_pvec[i6 + 6 * i5] = b_curv[i5][i6];
                        }
                    }
                    // 'compressCurvStructs:162' batch.lastCurv  = curv;
                    batch_lastCurv = curv;
                    // 'compressCurvStructs:163' batch.size      = 1;
                    batch_size = 1.0;
                    // 'compressCurvStructs:164' batch.zspdmode  = curv.Info.zspdmode;
                    batch_zspdmode = curv.Info.zspdmode;
                } else {
                    int i2;
                    bool b_zeroFlag;
                    // 'compressCurvStructs:165' else
                    // 'compressCurvStructs:166' batch.pvec      = [ batch.pvec, curv.R1 ];
                    i2 = batch_pvec.size(1);
                    batch_pvec.set_size(6, batch_pvec.size(1) + 1);
                    for (int i4{0}; i4 < 6; i4++) {
                        batch_pvec[i4 + 6 * i2] = curv.R1[i4];
                    }
                    // 'compressCurvStructs:167' batch.lastCurv  = curv;
                    batch_lastCurv = curv;
                    // 'compressCurvStructs:168' batch.size      = batch.size + 1;
                    batch_size++;
                    // 'compressCurvStructs:169' if( isAZeroEnd( curv ) )
                    //  isAZeroEnd : Return true if the curv ends with zero speed
                    //  Input :
                    //  curv / Info / ZSpdMode : A structure containning the information of the
                    //  curv zero speed.
                    // 'isAZeroEnd:6' zeroFlag = false;
                    b_zeroFlag = false;
                    // 'isAZeroEnd:8' [zspdmode, error] = getZspdmode( speed );
                    //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                    // 'getZspdmode:3' error = false;
                    // 'getZspdmode:5' if( isenum( speed ) )
                    // 'getZspdmode:7' elseif( isfield( speed, "Info") )
                    // 'getZspdmode:8' zspdmode = speed.Info.zspdmode;
                    // 'isAZeroEnd:10' if( error )
                    // 'isAZeroEnd:12' if( zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:13'     zspdmode == ZSpdMode.ZZ )
                    if ((curv.Info.zspdmode == ZSpdMode_NZ) ||
                        (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroEnd:14' zeroFlag = true;
                        b_zeroFlag = true;
                    }
                    if (b_zeroFlag) {
                        bool c_zeroFlag;
                        // 'compressCurvStructs:170' if( isAZeroStart( batch.zspdmode ) )
                        //  isAZeroStart : Return true if the curv starts with zero speed
                        //  Input :
                        //  curv / Info / ZSpdMode : A structure containning the information of the
                        //  curv zero speed.
                        // 'isAZeroStart:6' zeroFlag = false;
                        c_zeroFlag = false;
                        // 'isAZeroStart:8' [zspdmode, error] = getZspdmode( speed );
                        //  Get the zspdmode enum from either a curvStruct, infoStruct or zspdMode.
                        // 'getZspdmode:3' error = false;
                        // 'getZspdmode:5' if( isenum( speed ) )
                        // 'getZspdmode:6' zspdmode = speed;
                        // 'isAZeroStart:10' if( error )
                        // 'isAZeroStart:12' if( zspdmode == ZSpdMode.ZN || ...
                        // 'isAZeroStart:13'     zspdmode == ZSpdMode.ZZ )
                        if ((batch_zspdmode == ZSpdMode_ZN) || (batch_zspdmode == ZSpdMode_ZZ)) {
                            // 'isAZeroStart:14' zeroFlag = true;
                            c_zeroFlag = true;
                        }
                        if (c_zeroFlag) {
                            // 'compressCurvStructs:171' batch.zspdmode = ZSpdMode.ZZ;
                            batch_zspdmode = ZSpdMode_ZZ;
                        } else {
                            // 'compressCurvStructs:172' else
                            // 'compressCurvStructs:173' batch.zspdmode = ZSpdMode.NZ;
                            batch_zspdmode = ZSpdMode_NZ;
                        }
                    }
                }
            } else {
                // 'compressCurvStructs:38' else
                // 'compressCurvStructs:39' ctx.q_compress.push( curv );
                ctx->q_compress.push(&curv);
            }
        }
        // 'compressCurvStructs:44' [ ctx ] = batch_close( ctx, batch, spline_index );
        // 'compressCurvStructs:136' if( batch.size == 0 )
        if (batch_size != 0.0) {
            // 'compressCurvStructs:141' if( batch.size > 1 )
            if (batch_size > 1.0) {
                // 'compressCurvStructs:142' [ curvCompressed, spline, spline_index ] = ...
                // 'compressCurvStructs:143'         create_spline( ctx, batch, spline_index );
                b_spline_index = spline_index;
                create_spline(ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.NumberAxis,
                              ctx->cfg.LeeSplineDegree, ctx->cfg.GaussLegendreN,
                              ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, batch_pvec,
                              batch_lastCurv.Info.TRAFO, batch_lastCurv.Info.HSC,
                              batch_lastCurv.Info.FeedRate, batch_lastCurv.Info.SpindleSpeed,
                              batch_lastCurv.Info.gcode_source_line, batch_lastCurv.Info.G91,
                              batch_lastCurv.Info.G91_1, &batch_lastCurv.tool, batch_zspdmode,
                              &b_spline_index, &curvCompressed, &spline);
                // 'compressCurvStructs:145' ctx.q_compress.push( curvCompressed );
                ctx->q_compress.push(&curvCompressed);
                // 'compressCurvStructs:146' ctx.q_spline.push( spline );
                ctx->q_spline.push(&spline);
            } else {
                // 'compressCurvStructs:147' else
                // 'compressCurvStructs:148' ctx.q_compress.push( batch.lastCurv );
                ctx->q_compress.push(&batch_lastCurv);
            }
            // 'compressCurvStructs:151' if( coder.target( "MATLAB" ) )
            // 'compressCurvStructs:155' batch = batch_init();
        } else {
            // 'compressCurvStructs:137' batch = batch_init();
        }
    }
}

} // namespace ocn

//
// File trailer for compressCurvStructs.cpp
//
// [EOF]
//
