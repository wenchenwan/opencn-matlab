
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: compressCurvStructs.cpp
//
// MATLAB Coder version            : 5.4
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
#include "ocn_assert.h"
#include "ocn_print1.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_internal_types.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types111.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "paramsDefaultCurv.h"
#include "queue_coder.h"
#include "string1.h"
#include "sum.h"
#include "tridiag.h"
#include "c_spline.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>
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
    ::coder::array<double, 2U> points;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r11;
    ::coder::array<double, 2U> r12;
    ::coder::array<double, 2U> r13;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> r1Dnorm;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> r6;
    ::coder::array<double, 2U> r7;
    ::coder::array<double, 2U> u;
    ::coder::array<double, 1U> b_batch_pvec;
    ::coder::array<double, 1U> c_batch_pvec;
    ::coder::array<double, 1U> d;
    ::coder::array<double, 1U> r4;
    ::coder::array<double, 1U> v;
    ::coder::array<double, 1U> v_l;
    ::coder::array<double, 1U> v_m;
    ::coder::array<double, 1U> v_u;
    ::coder::array<bool, 2U> b_r1Dnorm;
    ::coder::array<bool, 2U> x;
    double b_ctx_cfg_GaussLegendreX[5];
    double dv[5];
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
    int b_k;
    int b_loop_ub;
    int b_result;
    int b_scalarLB;
    int b_u0;
    int b_u1;
    int b_unnamed_idx_2;
    int b_unnamed_idx_3;
    int b_vectorUB;
    int c_k;
    int c_loop_ub;
    int cb_loop_ub;
    int d_loop_ub;
    int dlen;
    int e_input_sizes_idx_0;
    int end;
    int f_loop_ub;
    int gb_loop_ub;
    int h_loop_ub;
    int i39;
    int i41;
    int i47;
    int i48;
    int i55;
    int i56;
    int i57;
    int i58;
    int i59;
    int i65;
    int i66;
    int i67;
    int i73;
    int i80;
    int ib_loop_ub;
    int input_sizes_idx_0_tmp;
    int j_loop_ub;
    int jb_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int loop_ub_tmp;
    int m_loop_ub;
    int mb_loop_ub;
    int nCoeff;
    int n_loop_ub;
    int nb_loop_ub;
    int o_loop_ub;
    int p_loop_ub;
    int partialTrueCount;
    int q_loop_ub;
    int rb_loop_ub;
    int result;
    int scalarLB;
    int trueCount;
    int u0;
    int u1;
    int u_loop_ub;
    unsigned int unnamed_idx_0;
    int unnamed_idx_1;
    int unnamed_idx_2;
    int unnamed_idx_3;
    int v_loop_ub;
    int vectorUB;
    int w_loop_ub;
    int x_loop_ub;
    int y_loop_ub;
    signed char tmp_data[6];
    signed char c_input_sizes_idx_0;
    signed char d_input_sizes_idx_0;
    signed char f_input_sizes_idx_0;
    signed char input_sizes_idx_0;
    bool b_empty_non_axis_sizes;
    bool b_varargout_1;
    bool empty_non_axis_sizes;
    bool exitg1;
    bool varargout_1;
    // 'compressCurvStructs:197' batch.lastCurv.Info.zspdmode = batch.zspdmode;
    // 'compressCurvStructs:199' curv    = constrSplineStruct( ...
    // 'compressCurvStructs:200'                               batch.lastCurv.Info, ...
    // 'compressCurvStructs:201'                               batch.lastCurv.tool, ...
    // 'compressCurvStructs:202'                               batch.pvec( :, 1 ), ...
    // 'compressCurvStructs:203'                               batch.pvec( :,end ), ...
    // 'compressCurvStructs:204'                               uint32( spline_index ) );
    loop_ub = batch_pvec.size(0);
    b_batch_pvec.set_size(batch_pvec.size(0));
    for (int i{0}; i < loop_ub; i++) {
        b_batch_pvec[i] = batch_pvec[i];
    }
    b_loop_ub = batch_pvec.size(0);
    c_batch_pvec.set_size(batch_pvec.size(0));
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        c_batch_pvec[i1] = batch_pvec[i1 + batch_pvec.size(0) * (batch_pvec.size(1) - 1)];
    }
    constrSplineStruct(batch_zspdmode, batch_lastCurv_Info_TRAFO, batch_lastCurv_Info_HSC,
                       batch_lastCurv_Info_FeedRate, batch_lastCurv_Info_SpindleSpeed,
                       batch_lastCurv_Info_gcode_source_line, batch_lastCurv_Info_G91,
                       batch_lastCurv_Info_G91_1, batch_lastCurv_tool->toolno,
                       batch_lastCurv_tool->pocketno, &batch_lastCurv_tool->offset,
                       batch_lastCurv_tool->diameter, batch_lastCurv_tool->frontangle,
                       batch_lastCurv_tool->backangle, batch_lastCurv_tool->orientation,
                       b_batch_pvec, c_batch_pvec, *spline_index, curv);
    // 'compressCurvStructs:206' spline            = curv;
    *spline = *curv;
    // 'compressCurvStructs:207' spline.sp         = CalcBspline_Lee( ctx.cfg, batch.pvec(
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
    c_loop_ub = batch_pvec.size(1);
    points.set_size(trueCount, batch_pvec.size(1));
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        for (int i3{0}; i3 < trueCount; i3++) {
            points[i3 + points.size(0) * i2] =
                batch_pvec[(tmp_data[i3] + batch_pvec.size(0) * i2) - 1];
        }
    }
    //  CalcBspline_Lee :
    //
    //  Inputs :
    //  cfg       : struct : Configuration variables
    //  points    :   nDxN : Set of points in n dimension for the spline
    //
    //  Outputs
    //  spnD      : struct : Output spline structure
    //  number of points in nD space
    // 'CalcBspline_Lee:12' [ ~, N ] = size( points );
    // 'CalcBspline_Lee:13' nAxis    = cfg.NumberAxis;
    //  Number of multiplicity at start and end ( clamped BSpline )
    // 'CalcBspline_Lee:15' nMult    = cfg.LeeSplineDegree - 1;
    // 'CalcBspline_Lee:16' nCoeff   = N + 2;
    // 'CalcBspline_Lee:18' du     = sum( ( diff( points.' ).^2 ).' );
    du_tmp.set_size(points.size(1), points.size(0));
    d_loop_ub = points.size(0);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        int e_loop_ub;
        e_loop_ub = points.size(1);
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            du_tmp[i5 + du_tmp.size(0) * i4] = points[i4 + points.size(0) * i5];
        }
    }
    // 'CalcBspline_Lee:19' u      = cumsum( [ 0, du.^( 1 / 4 ) ] );
    coder::diff(du_tmp, r);
    f_loop_ub = r.size(1);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        int g_loop_ub;
        g_loop_ub = r.size(0);
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            double varargin_1;
            varargin_1 = r[i7 + r.size(0) * i6];
            r[i7 + r.size(0) * i6] = std::pow(varargin_1, 2.0);
        }
    }
    r1.set_size(r.size(1), r.size(0));
    h_loop_ub = r.size(0);
    for (int i8{0}; i8 < h_loop_ub; i8++) {
        int i_loop_ub;
        i_loop_ub = r.size(1);
        for (int i9{0}; i9 < i_loop_ub; i9++) {
            r1[i9 + r1.size(0) * i8] = r[i8 + r.size(0) * i9];
        }
    }
    coder::sum(r1, r2);
    r2.set_size(1, r2.size(1));
    j_loop_ub = r2.size(1);
    for (int i10{0}; i10 < j_loop_ub; i10++) {
        double b_varargin_1;
        b_varargin_1 = r2[i10];
        r2[i10] = std::pow(b_varargin_1, 0.25);
    }
    u.set_size(1, r2.size(1) + 1);
    u[0] = 0.0;
    k_loop_ub = r2.size(1);
    for (int i11{0}; i11 < k_loop_ub; i11++) {
        u[i11 + 1] = r2[i11];
    }
    if (u.size(1) != 1) {
        int i12;
        i12 = u.size(1);
        for (int k{0}; k <= i12 - 2; k++) {
            u[k + 1] = u[k] + u[k + 1];
        }
    }
    //  normalize knots to interval [0...1]
    // 'CalcBspline_Lee:21' u      = u / u( end );
    b_u = u[u.size(1) - 1];
    u.set_size(1, u.size(1));
    l_loop_ub = u.size(1);
    scalarLB = (u.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i13{0}; i13 <= vectorUB; i13 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&u[i13]);
        _mm_storeu_pd(&u[i13], _mm_div_pd(r3, _mm_set1_pd(b_u)));
    }
    for (int i13{scalarLB}; i13 < l_loop_ub; i13++) {
        u[i13] = u[i13] / b_u;
    }
    // 'CalcBspline_Lee:22' knots  = [ zeros( 1, nMult ), u, ones( 1, nMult ) ];
    spline->sp.knots.set_size(1, ((ctx_cfg_LeeSplineDegree + u.size(1)) + ctx_cfg_LeeSplineDegree) -
                                     2);
    loop_ub_tmp = ctx_cfg_LeeSplineDegree - 1;
    for (int i14{0}; i14 < loop_ub_tmp; i14++) {
        spline->sp.knots[i14] = 0.0;
    }
    m_loop_ub = u.size(1);
    for (int i15{0}; i15 < m_loop_ub; i15++) {
        spline->sp.knots[(i15 + ctx_cfg_LeeSplineDegree) - 1] = u[i15];
    }
    for (int i16{0}; i16 < loop_ub_tmp; i16++) {
        spline->sp.knots[((i16 + ctx_cfg_LeeSplineDegree) + u.size(1)) - 1] = 1.0;
    }
    // 'CalcBspline_Lee:24' Bl = bspline_create( cfg.LeeSplineDegree, u );
    //  bspline_create : Create the BSpline basis functions
    //
    //  Inputs :
    //  degree        : BSpline degree
    //  breakpoints   : Vector of breakpoints
    //
    //  Outputs :
    //  Bl            : Bspline basis
    // 'bspline_create:10' if  coder.target( "MATLAB" )
    // 'bspline_create:12' else
    // 'bspline_create:13' nbreak  = length(breakpoints);
    // 'bspline_create:14' ncoeff  = nbreak + degree - 2;
    // 'bspline_create:15' h       = uint64(0);
    // 'bspline_create:16' my_path = StructTypeName.WDIR + "/src";
    // 'bspline_create:17' coder.updateBuildInfo('addIncludePaths',my_path);
    // 'bspline_create:18' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
    // 'bspline_create:19' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_create:20' coder.cinclude('c_spline.h');
    // 'bspline_create:21' coder.ceval('c_bspline_create_with_breakpoints', coder.wref(h), ...
    // 'bspline_create:22'         degree, breakpoints, int32(nbreak) );
    breakpoints.set_size(1, u.size(1));
    n_loop_ub = u.size(1);
    for (int i17{0}; i17 < n_loop_ub; i17++) {
        breakpoints[i17] = u[i17];
    }
    unsigned long h;
    c_bspline_create_with_breakpoints(&h, ctx_cfg_LeeSplineDegree, &breakpoints[0], u.size(1));
    // 'bspline_create:23' Bl = constrBaseSpline( ncoeff, breakpoints, h, int32(degree) );
    constrBaseSpline((u.size(1) + ctx_cfg_LeeSplineDegree) - 2, u, h, ctx_cfg_LeeSplineDegree,
                     &spline->sp.Bl);
    //
    // 'CalcBspline_Lee:26' [ BasisVal, BasisValDD0, BasisValDD1 ] = bspline_eval_lee( Bl, int32(
    // nCoeff ), u );
    nCoeff = batch_pvec.size(1) + 2;
    //  bspline_eval_lee  : Eval Bspline bases for a given set of u value.
    //
    //  Inputs    :
    //  Bl            : BSpline bases
    //  nCoeff        : Number of Coefficient
    //  uVec          : U vector of points to evaluate
    //
    //  Outputs   :
    //  BasisVal      : Evaluation of the BSpline for a given set of points
    //  BasisValDD0   : Evaluation of the 2nd derivative of the BSpline a u = 0
    //  BasisValDD1   : Evaluation of the 2nd derivative of the BSpline a u = 1
    //
    // 'bspline_eval_lee:15' ocn_assert( all( uVec >= 0, 'all' ), ...
    // 'bspline_eval_lee:16'         "u_vec should be greater or equal to 0", mfilename );
    x.set_size(1, u.size(1));
    o_loop_ub = u.size(1);
    for (int i18{0}; i18 < o_loop_ub; i18++) {
        x[i18] = (u[i18] >= 0.0);
    }
    varargout_1 = true;
    b_k = 0;
    exitg1 = false;
    while ((!exitg1) && (b_k <= x.size(1) - 1)) {
        if (!x[b_k]) {
            varargout_1 = false;
            exitg1 = true;
        } else {
            b_k++;
        }
    }
    p_ocn_assert(varargout_1);
    // 'bspline_eval_lee:17' ocn_assert( all( uVec <= 1, 'all' ), ...
    // 'bspline_eval_lee:18'         "u_vec should be greater or equal to 1", mfilename );
    x.set_size(1, u.size(1));
    p_loop_ub = u.size(1);
    for (int i19{0}; i19 < p_loop_ub; i19++) {
        x[i19] = (u[i19] <= 1.0);
    }
    b_varargout_1 = true;
    c_k = 0;
    exitg1 = false;
    while ((!exitg1) && (c_k <= x.size(1) - 1)) {
        if (!x[c_k]) {
            b_varargout_1 = false;
            exitg1 = true;
        } else {
            c_k++;
        }
    }
    q_ocn_assert(b_varargout_1);
    // 'bspline_eval_lee:20' if ( coder.target( "MATLAB" ) )
    // 'bspline_eval_lee:23' else
    // 'bspline_eval_lee:24' N = numel( uVec );
    // 'bspline_eval_lee:26' BasisVal    = zeros( N, nCoeff );
    BasisVal.set_size(u.size(1), batch_pvec.size(1) + 2);
    q_loop_ub = batch_pvec.size(1) + 2;
    for (int i20{0}; i20 < q_loop_ub; i20++) {
        int r_loop_ub;
        r_loop_ub = u.size(1);
        for (int i21{0}; i21 < r_loop_ub; i21++) {
            BasisVal[i21 + BasisVal.size(0) * i20] = 0.0;
        }
    }
    // 'bspline_eval_lee:27' BasisValDD0 = BasisVal( 1, : );
    BasisValDD0.set_size(1, batch_pvec.size(1) + 2);
    // 'bspline_eval_lee:28' BasisValDD1 = BasisValDD0;
    BasisValDD1.set_size(1, batch_pvec.size(1) + 2);
    for (int i22{0}; i22 < nCoeff; i22++) {
        BasisValDD0[i22] = 0.0;
        BasisValDD1[i22] = 0.0;
    }
    // 'bspline_eval_lee:30' my_path = StructTypeName.WDIR + "/src";
    // 'bspline_eval_lee:31' coder.updateBuildInfo('addIncludePaths',my_path);
    // 'bspline_eval_lee:32' coder.updateBuildInfo('addSourceFiles','c_spline.c', my_path);
    // 'bspline_eval_lee:33' coder.updateBuildInfo('addLinkFlags', LibInfo.gsl.lflags);
    // 'bspline_eval_lee:34' coder.cinclude( 'c_spline.h' );
    // 'bspline_eval_lee:36' coder.ceval( 'c_bspline_base_eval_lee', coder.rref(Bl.handle), ...
    // 'bspline_eval_lee:37'             int32( nCoeff ), int32( N ), coder.rref( uVec ), ...
    // 'bspline_eval_lee:38'             coder.wref( BasisVal ), coder.wref( BasisValDD0 ), ...
    // 'bspline_eval_lee:39'             coder.wref( BasisValDD1 ) );
    c_bspline_base_eval_lee(&spline->sp.Bl.handle, batch_pvec.size(1) + 2, u.size(1), &u[0],
                            &BasisVal[0], &BasisValDD0[0], &BasisValDD1[0]);
    //
    // 'CalcBspline_Lee:28' A = [ BasisValDD0; BasisVal; BasisValDD1 ];
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
    for (int i23{0}; i23 < result; i23++) {
        for (int i25{0}; i25 < input_sizes_idx_0_tmp; i25++) {
            A[A.size(0) * i23] = BasisValDD0[input_sizes_idx_0 * i23];
        }
    }
    for (int i24{0}; i24 < result; i24++) {
        for (int i27{0}; i27 < b_input_sizes_idx_0; i27++) {
            A[(i27 + input_sizes_idx_0) + A.size(0) * i24] =
                BasisVal[i27 + b_input_sizes_idx_0 * i24];
        }
    }
    for (int i26{0}; i26 < result; i26++) {
        for (int i28{0}; i28 < b_input_sizes_idx_0_tmp; i28++) {
            A[(input_sizes_idx_0 + b_input_sizes_idx_0) + A.size(0) * i26] =
                BasisValDD1[c_input_sizes_idx_0 * i26];
        }
    }
    //
    // 'CalcBspline_Lee:30' B = [zeros(1, nAxis);
    // 'CalcBspline_Lee:31'     points.';
    // 'CalcBspline_Lee:32'     zeros(1, nAxis)];
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
    for (int i29{0}; i29 < b_result; i29++) {
        int s_loop_ub;
        s_loop_ub = d_input_sizes_idx_0;
        for (int i31{0}; i31 < s_loop_ub; i31++) {
            B[B.size(0) * i29] = 0.0;
        }
    }
    for (int i30{0}; i30 < b_result; i30++) {
        for (int i33{0}; i33 < e_input_sizes_idx_0; i33++) {
            B[(i33 + d_input_sizes_idx_0) + B.size(0) * i30] =
                du_tmp[i33 + e_input_sizes_idx_0 * i30];
        }
    }
    for (int i32{0}; i32 < b_result; i32++) {
        int t_loop_ub;
        t_loop_ub = f_input_sizes_idx_0;
        for (int i34{0}; i34 < t_loop_ub; i34++) {
            B[(d_input_sizes_idx_0 + e_input_sizes_idx_0) + B.size(0) * i32] = 0.0;
        }
    }
    //
    // 'CalcBspline_Lee:34' [ A ] = swap_lines( A );
    //  Swap the lines of the matrice M. The goal is to obtain a tridiagonal
    //  matrice.
    // 'CalcBspline_Lee:47' M( [ 1, 2, end-1, end ], : ) = M( [ 2, 1, end, end-1 ], :);
    unnamed_idx_2 = A.size(0) - 2;
    unnamed_idx_3 = A.size(0) - 1;
    b_A = A.size(1) - 1;
    b_unnamed_idx_2 = A.size(0) - 1;
    b_unnamed_idx_3 = A.size(0) - 2;
    c_A.set_size(4, A.size(1));
    for (int i35{0}; i35 <= b_A; i35++) {
        c_A[4 * i35] = A[A.size(0) * i35 + 1];
        c_A[4 * i35 + 1] = A[A.size(0) * i35];
        c_A[4 * i35 + 2] = A[b_unnamed_idx_2 + A.size(0) * i35];
        c_A[4 * i35 + 3] = A[b_unnamed_idx_3 + A.size(0) * i35];
    }
    u_loop_ub = c_A.size(1);
    for (int i36{0}; i36 < u_loop_ub; i36++) {
        A[A.size(0) * i36] = c_A[4 * i36];
        A[A.size(0) * i36 + 1] = c_A[4 * i36 + 1];
        A[unnamed_idx_2 + A.size(0) * i36] = c_A[4 * i36 + 2];
        A[unnamed_idx_3 + A.size(0) * i36] = c_A[4 * i36 + 3];
    }
    // 'CalcBspline_Lee:35' [ B ] = swap_lines( B );
    //  Swap the lines of the matrice M. The goal is to obtain a tridiagonal
    //  matrice.
    // 'CalcBspline_Lee:47' M( [ 1, 2, end-1, end ], : ) = M( [ 2, 1, end, end-1 ], :);
    unnamed_idx_2 = B.size(0) - 2;
    unnamed_idx_3 = B.size(0) - 1;
    b_B = B.size(1) - 1;
    b_unnamed_idx_2 = B.size(0) - 1;
    b_unnamed_idx_3 = B.size(0) - 2;
    c_B.set_size(4, B.size(1));
    for (int i37{0}; i37 <= b_B; i37++) {
        c_B[4 * i37] = B[B.size(0) * i37 + 1];
        c_B[4 * i37 + 1] = B[B.size(0) * i37];
        c_B[4 * i37 + 2] = B[b_unnamed_idx_2 + B.size(0) * i37];
        c_B[4 * i37 + 3] = B[b_unnamed_idx_3 + B.size(0) * i37];
    }
    v_loop_ub = c_B.size(1);
    for (int i38{0}; i38 < v_loop_ub; i38++) {
        B[B.size(0) * i38] = c_B[4 * i38];
        B[B.size(0) * i38 + 1] = c_B[4 * i38 + 1];
        B[unnamed_idx_2 + B.size(0) * i38] = c_B[4 * i38 + 2];
        B[unnamed_idx_3 + B.size(0) * i38] = c_B[4 * i38 + 3];
    }
    // 'CalcBspline_Lee:36' [ v_m, v_l, v_u ] = extract_vectors( A );
    //  Extract the three vectors of the triagonal matrix A.
    //  Output :
    //  v_m   :   The vector of the middle of the matrix
    //  v_l   :   The vector of the lower diagonal of the matrix
    //  v_u   :   The vector of the upper diagonal of the matrix
    // 'CalcBspline_Lee:57' v_m = diag( A );
    u0 = A.size(0);
    u1 = A.size(1);
    if (u0 <= u1) {
        dlen = u0;
    } else {
        dlen = u1;
    }
    v_m.set_size(dlen);
    i39 = dlen - 1;
    for (int d_k{0}; d_k <= i39; d_k++) {
        v_m[d_k] = A[d_k + A.size(0) * d_k];
    }
    // 'CalcBspline_Lee:58' v_l = [ 0; diag( A, -1 ) ];
    coder::diag(A, r4);
    v_l.set_size(r4.size(0) + 1);
    v_l[0] = 0.0;
    w_loop_ub = r4.size(0);
    for (int i40{0}; i40 < w_loop_ub; i40++) {
        v_l[i40 + 1] = r4[i40];
    }
    // 'CalcBspline_Lee:59' v_u = [ diag( A, 1 ); 0 ];
    b_u0 = A.size(0);
    b_u1 = A.size(1) - 1;
    if (b_u0 <= b_u1) {
        b_dlen = b_u0;
    } else {
        b_dlen = b_u1;
    }
    d.set_size(b_dlen);
    i41 = b_dlen - 1;
    for (int e_k{0}; e_k <= i41; e_k++) {
        d[e_k] = A[e_k + A.size(0) * (e_k + 1)];
    }
    v_u.set_size(d.size(0) + 1);
    x_loop_ub = d.size(0);
    for (int i42{0}; i42 < x_loop_ub; i42++) {
        v_u[i42] = d[i42];
    }
    v_u[d.size(0)] = 0.0;
    // 'CalcBspline_Lee:38' c = tridiag( v_m, v_l, v_u, B );
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
    // 'tridiag:16' if( coder.target( "MATLAB" ) )
    // 'tridiag:18' else
    //  some additional information is at the end of the file
    // 'tridiag:21' [ n, ~ ]  = size( f );
    // 'tridiag:22' v         = zeros( n, 1 );
    v.set_size(B.size(0));
    y_loop_ub = B.size(0);
    for (int i43{0}; i43 < y_loop_ub; i43++) {
        v[i43] = 0.0;
    }
    // 'tridiag:23' y         = zeros( size( f ) );
    unnamed_idx_0 = static_cast<unsigned int>(B.size(0));
    c.set_size(B.size(0), B.size(1));
    ab_loop_ub = B.size(1);
    for (int i44{0}; i44 < ab_loop_ub; i44++) {
        int bb_loop_ub;
        bb_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i45{0}; i45 < bb_loop_ub; i45++) {
            c[i45 + c.size(0) * i44] = 0.0;
        }
    }
    // 'tridiag:24' w         = a( 1 );
    w = v_m[0];
    // 'tridiag:25' y( 1, : ) = f( 1, : ) / w;
    cb_loop_ub = B.size(1);
    for (int i46{0}; i46 < cb_loop_ub; i46++) {
        c[c.size(0) * i46] = B[B.size(0) * i46] / v_m[0];
    }
    // 'tridiag:27' for i = 2 : n
    i47 = B.size(0);
    for (int c_i{0}; c_i <= i47 - 2; c_i++) {
        double b_d;
        double w_tmp;
        int db_loop_ub;
        // 'tridiag:28' v( i -1 ) = c( i -1 ) / w;
        b_d = v_u[c_i] / w;
        v[c_i] = b_d;
        // 'tridiag:29' w         = a( i ) - b( i ) * v( i -1 );
        w_tmp = v_l[c_i + 1];
        w = v_m[c_i + 1] - w_tmp * b_d;
        // 'tridiag:30' y( i, : ) = ( f( i, : ) - b( i ) * y( i -1, : ) ) / w;
        db_loop_ub = B.size(1);
        if (B.size(1) == c.size(1)) {
            int fb_loop_ub;
            d_B.set_size(1, B.size(1));
            for (int i50{0}; i50 < db_loop_ub; i50++) {
                d_B[i50] = (B[(c_i + B.size(0) * i50) + 1] - w_tmp * c[c_i + c.size(0) * i50]) / w;
            }
            fb_loop_ub = d_B.size(1);
            for (int i52{0}; i52 < fb_loop_ub; i52++) {
                c[(c_i + c.size(0) * i52) + 1] = d_B[i52];
            }
        } else {
            binary_expand_op(c, c_i, B, v_l, w);
        }
    }
    // 'tridiag:33' for j = n-1 : -1 : 1
    i48 = B.size(0);
    for (int j{0}; j <= i48 - 2; j++) {
        int b_c;
        int b_j;
        int eb_loop_ub;
        b_j = (B.size(0) - j) - 2;
        // 'tridiag:34' y( j, : ) = y( j, : ) - v( j ) * y( j + 1, : );
        b_c = c.size(1) - 1;
        c_c.set_size(1, c.size(1));
        for (int i49{0}; i49 <= b_c; i49++) {
            c_c[i49] = c[b_j + c.size(0) * i49] - v[b_j] * c[(b_j + c.size(0) * i49) + 1];
        }
        eb_loop_ub = c_c.size(1);
        for (int i51{0}; i51 < eb_loop_ub; i51++) {
            c[b_j + c.size(0) * i51] = c_c[i51];
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
    // 'CalcBspline_Lee:40' spnD = constrSpline( c.', knots, Bl );
    spline->sp.coeff.set_size(c.size(1), c.size(0));
    gb_loop_ub = c.size(0);
    for (int i53{0}; i53 < gb_loop_ub; i53++) {
        int hb_loop_ub;
        hb_loop_ub = c.size(1);
        for (int i54{0}; i54 < hb_loop_ub; i54++) {
            spline->sp.coeff[i54 + spline->sp.coeff.size(0) * i53] = c[i53 + c.size(0) * i54];
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
    // 'constrSpline:20'                     'Lk', knots ...
    // 'constrSpline:21'                     );
    // 'constrSpline:23' if ~coder.target( 'MATLAB' )
    // 'constrSpline:24' coder.varsize( 'SplineStrct.Lk',    StructTypeName.dimLk{ : } );
    // 'constrSpline:25' coder.varsize( 'SplineStrct.coeff', StructTypeName.dimCoeffs{ : } );
    // 'constrSpline:26' coder.varsize( 'SplineStrct.knots', StructTypeName.dimKnots{ : } );
    // 'constrSpline:27' coder.cstructname( SplineStrct.Bl, StructTypeName.BaseSpline );
    // 'constrSpline:28' coder.cstructname( SplineStrct, StructTypeName.Spline );
    // 'compressCurvStructs:208' [ Ltot, Lk ]      = SplineLengthApproxGL_tot( ctx.cfg, spline );
    //  SplineLengthApproxGL_tot : Precomputes approximately the total arc length
    //  L as well as the individual arc lengths between knot points of a
    //  parametric spline. The computation is based on numerical Gauss Legendre
    //  integration. SplineLengthApproxGL_tot should only be called once since
    //  the result of the computation is stored and reused later.
    //
    //  Inputs :
    //    cfg     : The configuration structure
    //    Curv    : The spline
    //
    //  Outputs :
    //    L       : The resulting length
    //    Lk      : The resulting length of each nodes intervals
    //
    //  get the sp structure
    //  Spline = ctx.q_spline.get(Curv.sp_index);
    //  sp     = Spline.sp;
    // 'SplineLengthApproxGL_tot:20' sp     = Curv.sp;
    // 'SplineLengthApproxGL_tot:21' Knots  = sp.knots(4:end-3);
    if (spline->sp.knots.size(1) - 3 < 4) {
        i55 = 0;
        i56 = -1;
    } else {
        i55 = 3;
        i56 = spline->sp.knots.size(1) - 4;
    }
    //  eliminate multiplicities at the end points
    // 'SplineLengthApproxGL_tot:22' a      = Knots(1:end-1);
    i57 = i56 - i55;
    if (i57 < 1) {
        ib_loop_ub = 0;
    } else {
        ib_loop_ub = i56 - i55;
    }
    //  lower integration limits
    // 'SplineLengthApproxGL_tot:23' b      = Knots(2:end);
    if (i57 + 1 < 2) {
        i58 = -1;
        i59 = -1;
    } else {
        i58 = 0;
        i59 = i57;
    }
    //  upper integration limits
    //  get Gauss-Legendre knots and weights
    // 'SplineLengthApproxGL_tot:25' GL_N   = cfg.GaussLegendreN;
    // 'SplineLengthApproxGL_tot:26' GL_X   = cfg.GaussLegendreX;
    // 'SplineLengthApproxGL_tot:27' GL_W   = cfg.GaussLegendreW;
    //  apply linear map from[-1, 1] to [a, b]
    // 'SplineLengthApproxGL_tot:29' Umat   = (bsxfun(@times, a, (1-GL_X)) + bsxfun(@times, b,
    // (1+GL_X)))/2;
    b_spline.set_size(1, ib_loop_ub);
    for (int i60{0}; i60 < ib_loop_ub; i60++) {
        b_spline[i60] = spline->sp.knots[i55 + i60];
    }
    r5 = _mm_set1_pd(1.0);
    _mm_storeu_pd(&dv[0], _mm_sub_pd(r5, _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0])));
    _mm_storeu_pd(&dv[2], _mm_sub_pd(r5, _mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2])));
    dv[4] = 1.0 - ctx_cfg_GaussLegendreX[4];
    coder::bsxfun(b_spline, dv, r6);
    jb_loop_ub = i59 - i58;
    b_spline.set_size(1, jb_loop_ub);
    for (int i61{0}; i61 < jb_loop_ub; i61++) {
        b_spline[i61] = spline->sp.knots[((i55 + i58) + i61) + 1];
    }
    _mm_storeu_pd(&b_ctx_cfg_GaussLegendreX[0],
                  _mm_add_pd(_mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[0]), r5));
    _mm_storeu_pd(&b_ctx_cfg_GaussLegendreX[2],
                  _mm_add_pd(_mm_loadu_pd((const double *)&ctx_cfg_GaussLegendreX[2]), r5));
    b_ctx_cfg_GaussLegendreX[4] = ctx_cfg_GaussLegendreX[4] + 1.0;
    coder::bsxfun(b_spline, b_ctx_cfg_GaussLegendreX, r7);
    if (r6.size(1) == r7.size(1)) {
        int kb_loop_ub;
        Umat.set_size(5, r6.size(1));
        kb_loop_ub = r6.size(1);
        for (int i62{0}; i62 < kb_loop_ub; i62++) {
            __m128d r10;
            __m128d r8;
            __m128d r9;
            r8 = _mm_loadu_pd(&r6[5 * i62]);
            r9 = _mm_loadu_pd(&r7[5 * i62]);
            r10 = _mm_set1_pd(2.0);
            _mm_storeu_pd(&Umat[5 * i62], _mm_div_pd(_mm_add_pd(r8, r9), r10));
            r8 = _mm_loadu_pd(&r6[5 * i62 + 2]);
            r9 = _mm_loadu_pd(&r7[5 * i62 + 2]);
            _mm_storeu_pd(&Umat[5 * i62 + 2], _mm_div_pd(_mm_add_pd(r8, r9), r10));
            Umat[5 * i62 + 4] = (r6[5 * i62 + 4] + r7[5 * i62 + 4]) / 2.0;
        }
    } else {
        k_binary_expand_op(Umat, r6, r7);
    }
    // 'SplineLengthApproxGL_tot:30' Uvec   = Umat(:)';
    //  all evaluation points as row vector
    // 'SplineLengthApproxGL_tot:32' [~, r1D]  = EvalBSpline(Curv, Uvec);
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
    unnamed_idx_1 = 5 * Umat.size(1);
    // 'EvalBSpline:22' r1D = r0D;
    r1D.set_size(spline->sp.coeff.size(0), unnamed_idx_1);
    for (int i63{0}; i63 < unnamed_idx_1; i63++) {
        int lb_loop_ub;
        lb_loop_ub = spline->sp.coeff.size(0);
        for (int i64{0}; i64 < lb_loop_ub; i64++) {
            r1D[i64 + r1D.size(0) * i63] = 0.0;
        }
    }
    // 'EvalBSpline:22' r2D = r1D;
    // 'EvalBSpline:22' r3D = r2D;
    // 'EvalBSpline:24' for j = 1 : M
    i65 = spline->sp.coeff.size(0);
    if (spline->sp.coeff.size(0) - 1 >= 0) {
        i66 = 5 * Umat.size(1);
        if (i66 - 1 >= 0) {
            i67 = spline->sp.coeff.size(1);
            mb_loop_ub = spline->sp.coeff.size(1);
        }
    }
    for (int c_j{0}; c_j < i65; c_j++) {
        unsigned int b_unnamed_idx_1;
        int pb_loop_ub;
        int qb_loop_ub;
        int sb_loop_ub;
        int tb_loop_ub;
        int ub_loop_ub;
        // 'EvalBSpline:25' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
        // 'EvalBSpline:26'                         bspline_eval_vec( sp.Bl, sp.coeff( j, : ), u_vec
        // );
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
        b_unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
        r2.set_size(1, static_cast<int>(b_unnamed_idx_1));
        pb_loop_ub = static_cast<int>(b_unnamed_idx_1);
        for (int i70{0}; i70 < pb_loop_ub; i70++) {
            r2[i70] = 0.0;
        }
        // 'bspline_eval_vec:16' xd      = zeros(size(uVec));
        b_unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
        r11.set_size(1, static_cast<int>(b_unnamed_idx_1));
        qb_loop_ub = static_cast<int>(b_unnamed_idx_1);
        for (int i71{0}; i71 < qb_loop_ub; i71++) {
            r11[i71] = 0.0;
        }
        // 'bspline_eval_vec:17' xdd     = zeros(size(uVec));
        b_unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
        r12.set_size(1, static_cast<int>(b_unnamed_idx_1));
        sb_loop_ub = static_cast<int>(b_unnamed_idx_1);
        for (int i74{0}; i74 < sb_loop_ub; i74++) {
            r12[i74] = 0.0;
        }
        // 'bspline_eval_vec:18' xddd    = zeros(size(uVec));
        b_unnamed_idx_1 = static_cast<unsigned int>(5 * Umat.size(1));
        r13.set_size(1, static_cast<int>(b_unnamed_idx_1));
        tb_loop_ub = static_cast<int>(b_unnamed_idx_1);
        for (int i75{0}; i75 < tb_loop_ub; i75++) {
            r13[i75] = 0.0;
        }
        // 'bspline_eval_vec:20' for k = 1:length(uVec)
        for (int g_k{0}; g_k < i66; g_k++) {
            // 'bspline_eval_vec:21' [xk, xdk, xddk, xdddk] = bspline_eval( Bl, coeffs, uVec( k ) );
            r2[g_k] = Umat[g_k];
            b_spline.set_size(1, i67);
            for (int i79{0}; i79 < mb_loop_ub; i79++) {
                b_spline[i79] = spline->sp.coeff[c_j + spline->sp.coeff.size(0) * i79];
            }
            bspline_eval(spline->sp.Bl.handle, b_spline, &r2[g_k], &d1, &d2, &d3);
            r13[g_k] = d3;
            r12[g_k] = d2;
            r11[g_k] = d1;
            // 'bspline_eval_vec:22' x(k)    = xk;
            // 'bspline_eval_vec:23' xd(k)   = xdk;
            // 'bspline_eval_vec:24' xdd(k)  = xddk;
            // 'bspline_eval_vec:25' xddd(k) = xdddk;
        }
        ub_loop_ub = r11.size(1);
        for (int i77{0}; i77 < ub_loop_ub; i77++) {
            r1D[c_j + r1D.size(0) * i77] = r11[i77];
        }
    }
    // 'SplineLengthApproxGL_tot:33' r1Dnorm   = MyNorm(r1D);
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
    r.set_size(r1D.size(0), r1D.size(1));
    nb_loop_ub = r1D.size(1);
    for (int i68{0}; i68 < nb_loop_ub; i68++) {
        int ob_loop_ub;
        ob_loop_ub = r1D.size(0);
        for (int i69{0}; i69 < ob_loop_ub; i69++) {
            double c_varargin_1;
            c_varargin_1 = r1D[i69 + r1D.size(0) * i68];
            r[i69 + r.size(0) * i68] = std::pow(c_varargin_1, 2.0);
        }
    }
    coder::sum(r, r1Dnorm);
    //  mysqrt : Custom implementation of the sqrt method.
    //
    //  Inputs :
    //    x : Value used for the computation
    //  Outputs :
    //    y : Resulting value
    //
    // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
    // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
    b_r1Dnorm.set_size(1, r1Dnorm.size(1));
    rb_loop_ub = r1Dnorm.size(1);
    for (int i72{0}; i72 < rb_loop_ub; i72++) {
        b_r1Dnorm[i72] = (r1Dnorm[i72] >= 0.0);
    }
    r_ocn_assert(b_r1Dnorm);
    // 'mysqrt:11' y = sqrt(x);
    i73 = r1Dnorm.size(1);
    b_scalarLB = (r1Dnorm.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (int f_k{0}; f_k <= b_vectorUB; f_k += 2) {
        __m128d r14;
        r14 = _mm_loadu_pd(&r1Dnorm[f_k]);
        _mm_storeu_pd(&r1Dnorm[f_k], _mm_sqrt_pd(r14));
    }
    for (int f_k{b_scalarLB}; f_k < i73; f_k++) {
        r1Dnorm[f_k] = std::sqrt(r1Dnorm[f_k]);
    }
    // 'SplineLengthApproxGL_tot:34' r1DnormM  = reshape(r1Dnorm, GL_N, length(Knots)-1);
    // 'SplineLengthApproxGL_tot:35' Lk        = sum(bsxfun(@times, GL_W, r1DnormM)) .* (b-a)/2;
    d_c.set_size(5, i57);
    if (i57 != 0) {
        int b_bcoef;
        int bcoef;
        int i76;
        bcoef = (i57 != 1);
        i76 = i57 - 1;
        b_bcoef = (static_cast<int>(ctx_cfg_GaussLegendreN) != 1);
        for (int h_k{0}; h_k <= i76; h_k++) {
            int varargin_3;
            varargin_3 = bcoef * h_k;
            for (int j_k{0}; j_k < 5; j_k++) {
                d_c[j_k + 5 * h_k] =
                    ctx_cfg_GaussLegendreW[j_k] *
                    r1Dnorm[b_bcoef * j_k + static_cast<int>(ctx_cfg_GaussLegendreN) * varargin_3];
            }
        }
    }
    if (d_c.size(1) == 0) {
        r2.set_size(1, 0);
    } else {
        int i78;
        r2.set_size(1, d_c.size(1));
        i78 = d_c.size(1);
        for (int i_k{0}; i_k < i78; i_k++) {
            r2[i_k] = d_c[5 * i_k];
            r2[i_k] = r2[i_k] + d_c[5 * i_k + 1];
            r2[i_k] = r2[i_k] + d_c[5 * i_k + 2];
            r2[i_k] = r2[i_k] + d_c[5 * i_k + 3];
            r2[i_k] = r2[i_k] + d_c[5 * i_k + 4];
        }
    }
    if (i59 - i58 == 1) {
        i80 = ib_loop_ub;
    } else {
        i80 = i59 - i58;
    }
    if ((jb_loop_ub == ib_loop_ub) && (r2.size(1) == i80)) {
        int c_scalarLB;
        int c_vectorUB;
        int vb_loop_ub;
        spline->sp.Lk.set_size(1, r2.size(1));
        vb_loop_ub = r2.size(1);
        c_scalarLB = (r2.size(1) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (int i81{0}; i81 <= c_vectorUB; i81 += 2) {
            __m128d r15;
            __m128d r16;
            __m128d r17;
            r15 = _mm_loadu_pd(&spline->sp.knots[((i55 + i58) + i81) + 1]);
            r16 = _mm_loadu_pd(&spline->sp.knots[i55 + i81]);
            r17 = _mm_loadu_pd(&r2[i81]);
            _mm_storeu_pd(&spline->sp.Lk[i81],
                          _mm_div_pd(_mm_mul_pd(r17, _mm_sub_pd(r15, r16)), _mm_set1_pd(2.0)));
        }
        for (int i81{c_scalarLB}; i81 < vb_loop_ub; i81++) {
            spline->sp.Lk[i81] =
                r2[i81] *
                (spline->sp.knots[((i55 + i58) + i81) + 1] - spline->sp.knots[i55 + i81]) / 2.0;
        }
    } else {
        binary_expand_op(spline, r2, i55, i58 + 1, i59, ib_loop_ub - 1);
    }
    //  Gauss Legendre integration
    // 'SplineLengthApproxGL_tot:36' L         = sum(Lk);
    spline->sp.Ltot = coder::sum(spline->sp.Lk);
    // 'compressCurvStructs:209' spline.sp.Ltot    = Ltot;
    // 'compressCurvStructs:210' spline.sp.Lk      = Lk;
    // 'compressCurvStructs:211' spline_index      = spline_index + 1;
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
//  - Create a Bspline based on ( Lee Algorithm : Lee89 ).
//  - Fill the queue : q_compress
//
//  Note : If compression is not required call ExpandZeroStructs
//
//  Inputs :
//    ctx     : The context of the computational chain
//
//  Outputs :
//    ctx     : The context of the computatinal chain
//
//
// Arguments    : b_FeedoptContext *ctx
// Return Type  : void
//
void compressCurvStructs(b_FeedoptContext *ctx)
{
    coder::rtString obj;
    ::coder::array<double, 2U> batch_pvec;
    ::coder::array<double, 1U> V0;
    ::coder::array<double, 1U> V1;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> u;
    ::coder::array<double, 1U> v;
    Axes params_tmp_tool_offset;
    CurvStruct batch_lastCurv;
    CurvStruct curv;
    CurvStruct curvCompressed;
    CurvStruct spline;
    SplineStruct params_tmp_spline;
    b_CurvStruct e_expl_temp;
    b_CurvStruct expl_temp_tmp;
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
    char st[12];
    char b_st[11];
    char obj2Value_data[11];
    char b_obj2Value_data[10];
    bool params_tmp_gcodeInfoStruct_G91;
    bool params_tmp_gcodeInfoStruct_G91_1;
    bool params_tmp_gcodeInfoStruct_HSC;
    bool params_tmp_gcodeInfoStruct_TRAFO;
    CurveType params_tmp_gcodeInfoStruct_Type;
    ZSpdMode params_tmp_gcodeInfoStruct_zspdmode;
    // 'compressCurvStructs:21' if ctx.q_gcode.isempty()
    if (!ctx->q_gcode.isempty()) {
        double batch_size;
        unsigned int Ncrv;
        int b_loop_ub;
        int c_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int h_loop_ub;
        int i11;
        int i_loop_ub;
        int j_loop_ub;
        int loop_ub;
        ZSpdMode batch_zspdmode;
        // 'compressCurvStructs:23' spline_index        = ctx.q_spline.size() + 1;
        spline_index = ctx->q_spline.size() + 1U;
        //  New index in q_spline
        // 'compressCurvStructs:24' Ncrv                = ctx.q_gcode.size;
        Ncrv = ctx->q_gcode.size();
        //  Number of curve in queue
        // 'compressCurvStructs:25' [ batch ]           = batch_init();
        // 'compressCurvStructs:129' batch = struct( ...
        // 'compressCurvStructs:130'     'pvec',          zeros( StructTypeName.NumberAxisMax, 1
        // ),... 'compressCurvStructs:131'     'lastCurv',      constrCurvStructType,...
        // 'compressCurvStructs:132'     'size',          0, ...
        // 'compressCurvStructs:133'     'zspdmode',      ZSpdMode.NN ...
        // 'compressCurvStructs:134'     );
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
        b_constrCurvStruct(
            params_tmp_gcodeInfoStruct_Type, params_tmp_gcodeInfoStruct_zspdmode,
            params_tmp_gcodeInfoStruct_TRAFO, params_tmp_gcodeInfoStruct_HSC,
            params_tmp_gcodeInfoStruct_FeedRate, params_tmp_gcodeInfoStruct_SpindleSpeed,
            params_tmp_gcodeInfoStruct_gcode_source_line, params_tmp_gcodeInfoStruct_G91,
            params_tmp_gcodeInfoStruct_G91_1, params_tmp_tool_toolno, params_tmp_tool_pocketno,
            &params_tmp_tool_offset, params_tmp_tool_diameter, params_tmp_tool_frontangle,
            params_tmp_tool_backangle, params_tmp_tool_orientation, &params_tmp_spline,
            params_tmp_R0, params_tmp_R1, params_tmp_Cprim, params_tmp_evec, params_tmp_CoeffP5,
            &expl_temp_tmp);
        e_expl_temp = expl_temp_tmp;
        batch_lastCurv.R0.set_size(e_expl_temp.R0.size[0]);
        loop_ub = e_expl_temp.R0.size[0];
        for (int i{0}; i < loop_ub; i++) {
            batch_lastCurv.R0[i] = e_expl_temp.R0.data[i];
        }
        batch_lastCurv.R1.set_size(e_expl_temp.R1.size[0]);
        b_loop_ub = e_expl_temp.R1.size[0];
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            batch_lastCurv.R1[i1] = e_expl_temp.R1.data[i1];
        }
        batch_lastCurv.CoeffP5.set_size(e_expl_temp.CoeffP5.size(0), e_expl_temp.CoeffP5.size(1));
        c_loop_ub = e_expl_temp.CoeffP5.size(1);
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            int d_loop_ub;
            d_loop_ub = e_expl_temp.CoeffP5.size(0);
            for (int i3{0}; i3 < d_loop_ub; i3++) {
                batch_lastCurv.CoeffP5[i3 + batch_lastCurv.CoeffP5.size(0) * i2] =
                    e_expl_temp.CoeffP5[i3 + e_expl_temp.CoeffP5.size(0) * i2];
            }
        }
        // 'compressCurvStructs:136' if( ~coder.target( "MATLAB" ) )
        // 'compressCurvStructs:137' coder.varsize( 'batch.pvec', StructTypeName.dimPvec{ : } );
        batch_pvec.set_size(6, 1);
        for (int i4{0}; i4 < 6; i4++) {
            batch_pvec[i4] = 0.0;
        }
        batch_lastCurv.Info = e_expl_temp.Info;
        batch_lastCurv.tool = e_expl_temp.tool;
        batch_lastCurv.sp.Bl.ncoeff = e_expl_temp.sp.Bl.ncoeff;
        batch_lastCurv.sp.Bl.breakpoints.set_size(1, e_expl_temp.sp.Bl.breakpoints.size(1));
        e_loop_ub = e_expl_temp.sp.Bl.breakpoints.size(1);
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            batch_lastCurv.sp.Bl.breakpoints[i5] = e_expl_temp.sp.Bl.breakpoints[i5];
        }
        batch_lastCurv.sp.Bl.handle = e_expl_temp.sp.Bl.handle;
        batch_lastCurv.sp.Bl.order = e_expl_temp.sp.Bl.order;
        batch_lastCurv.sp.coeff.set_size(e_expl_temp.sp.coeff.size(0),
                                         e_expl_temp.sp.coeff.size(1));
        f_loop_ub = e_expl_temp.sp.coeff.size(1);
        for (int i6{0}; i6 < f_loop_ub; i6++) {
            int g_loop_ub;
            g_loop_ub = e_expl_temp.sp.coeff.size(0);
            for (int i7{0}; i7 < g_loop_ub; i7++) {
                batch_lastCurv.sp.coeff[i7 + batch_lastCurv.sp.coeff.size(0) * i6] =
                    e_expl_temp.sp.coeff[i7 + e_expl_temp.sp.coeff.size(0) * i6];
            }
        }
        batch_lastCurv.sp.knots.set_size(1, e_expl_temp.sp.knots.size(1));
        h_loop_ub = e_expl_temp.sp.knots.size(1);
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            batch_lastCurv.sp.knots[i8] = e_expl_temp.sp.knots[i8];
        }
        batch_lastCurv.sp.Ltot = e_expl_temp.sp.Ltot;
        batch_lastCurv.sp.Lk.set_size(1, e_expl_temp.sp.Lk.size(1));
        i_loop_ub = e_expl_temp.sp.Lk.size(1);
        for (int i9{0}; i9 < i_loop_ub; i9++) {
            batch_lastCurv.sp.Lk[i9] = e_expl_temp.sp.Lk[i9];
        }
        batch_lastCurv.delta = e_expl_temp.delta;
        batch_lastCurv.CorrectedHelixCenter[0] = e_expl_temp.CorrectedHelixCenter[0];
        batch_lastCurv.evec[0] = e_expl_temp.evec[0];
        batch_lastCurv.CorrectedHelixCenter[1] = e_expl_temp.CorrectedHelixCenter[1];
        batch_lastCurv.evec[1] = e_expl_temp.evec[1];
        batch_lastCurv.CorrectedHelixCenter[2] = e_expl_temp.CorrectedHelixCenter[2];
        batch_lastCurv.evec[2] = e_expl_temp.evec[2];
        batch_lastCurv.theta = e_expl_temp.theta;
        batch_lastCurv.pitch = e_expl_temp.pitch;
        batch_lastCurv.sp_index = e_expl_temp.sp_index;
        batch_lastCurv.i_begin_sp = e_expl_temp.i_begin_sp;
        batch_lastCurv.i_end_sp = e_expl_temp.i_end_sp;
        batch_lastCurv.index_smooth = e_expl_temp.index_smooth;
        batch_lastCurv.UseConstJerk = e_expl_temp.UseConstJerk;
        batch_lastCurv.ConstJerk = e_expl_temp.ConstJerk;
        batch_lastCurv.Coeff.set_size(e_expl_temp.Coeff.size(0));
        j_loop_ub = e_expl_temp.Coeff.size(0);
        for (int i10{0}; i10 < j_loop_ub; i10++) {
            batch_lastCurv.Coeff[i10] = e_expl_temp.Coeff[i10];
        }
        batch_lastCurv.a_param = e_expl_temp.a_param;
        batch_lastCurv.b_param = e_expl_temp.b_param;
        batch_size = 0.0;
        batch_zspdmode = ZSpdMode_NN;
        // 'compressCurvStructs:27' DebugLog( DebugCfg.Validate, 'Compressing...\n' );
        //  DebugLog : Print msg in log pipe.
        //
        //  Inputs :
        //  cfg       : The configuration structure
        //  varargin  : Variable types of arguments (a.k.a print msg)
        //
        // 'DebugLog:9' if IsEnabledDebugLog( cfg )
        //  IsEnableDebugLog : Is the Debug log enable
        //
        //  Inputs :
        //    cfg : Configuration structure
        //
        //  Outputs :
        //  Value : Boolean Value. TRUE means the debug log is enable.
        //
        // 'IsEnabledDebugLog:13' value = false;
        // 'IsEnabledDebugLog:15' if bitget( DebugConfig, int32( cfg ) )
        if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
            // 'IsEnabledDebugLog:16' value = true;
            //    Output
            //    stdout : 1
            //    stderr : 2
            // 'DebugLog:13' output  = 1;
            // 'DebugLog:14' fprintf( output, varargin{ : } );
            printf("Compressing...\n");
            fflush(stdout);
        }
        // 'compressCurvStructs:29' ctx.k0 = int32( 1 );
        ctx->k0 = 1;
        // 'compressCurvStructs:31' for k = 1 : Ncrv
        i11 = static_cast<int>(Ncrv);
        for (int k{0}; k < i11; k++) {
            int b_resCount;
            int resCount;
            bool addBatch;
            bool closeBatch;
            // 'compressCurvStructs:33' ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" +
            // Ncrv, mfilename );
            resCount = sprintf(&st[0], "%d", ctx->k0);
            if (resCount - 1 >= 0) {
                std::copy(&st[0], &st[resCount], &obj2Value_data[0]);
            }
            b_resCount = sprintf(&b_st[0], "%u", Ncrv);
            if (b_resCount - 1 >= 0) {
                std::copy(&b_st[0], &b_st[b_resCount], &b_obj2Value_data[0]);
            }
            obj.Value.size[0] = 1;
            obj.Value.size[1] = (resCount + b_resCount) + 1;
            if (resCount - 1 >= 0) {
                std::copy(&obj2Value_data[0], &obj2Value_data[resCount], &obj.Value.data[0]);
            }
            obj.Value.data[resCount] = '/';
            for (int i12{0}; i12 < b_resCount; i12++) {
                obj.Value.data[(i12 + resCount) + 1] = b_obj2Value_data[i12];
            }
            g_ocn_print(ctx->cfg.ENABLE_PRINT_MSG, &obj);
            // 'compressCurvStructs:34' curv = ctx.q_gcode.get( k );
            ctx->q_gcode.get(k + 1U, &curv);
            //  Get next Curve in the queue
            // 'compressCurvStructs:36' [ addBatch ]    = check_add_batch( ctx, curv );
            // -------------------------------------------------------------------------%
            // 'compressCurvStructs:58' if( coder.target( "MATLAB" ) )
            // 'compressCurvStructs:60' addBatch    = true;
            addBatch = true;
            //  Cond 1. Keep only line segments
            // 'compressCurvStructs:63' if( curv.Info.Type ~= CurveType.Line )
            if (curv.Info.Type != CurveType_Line) {
                // 'compressCurvStructs:64' if( coder.target( "MATLAB" ) )
                // 'compressCurvStructs:67' addBatch = false;
                addBatch = false;

                //  Cond 2. Remove to large segment
                // 'compressCurvStructs:70' if( LengthCurv( ctx, curv, 0, 1 ) >
                // ctx.cfg.LThresholdMax )
            } else if (LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                  ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                  ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                  ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                  ctx->cfg.NRot, ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                                  &curv) > ctx->cfg.LThresholdMax) {
                // 'compressCurvStructs:71' if( coder.target( "MATLAB" ) )
                // 'compressCurvStructs:74' addBatch = false;
                addBatch = false;
            }
            // 'compressCurvStructs:37' [ closeBatch ]  = check_close_batch( ctx, batch, curv,
            // addBatch); 'compressCurvStructs:80' if( coder.target( "MATLAB" ) )
            // 'compressCurvStructs:82' closeBatch = false;
            closeBatch = false;
            // 'compressCurvStructs:84' if( batch.size == 0 )
            if (batch_size != 0.0) {
                bool isSame;
                bool zeroFlag;
                //  Cond 1. Curv not in the batch
                // 'compressCurvStructs:87' if( ~addBatch )
                if (!addBatch) {
                    // 'compressCurvStructs:88' closeBatch = true;
                    closeBatch = true;
                }
                //  Cond 2. Curv require a stop
                // 'compressCurvStructs:92' if( isAZeroStart( curv ) )
                //  isAZeroStart : Return true if the curv starts with zero speed
                //
                //  Inputs :
                //  curv / Info / ZSpdMode : A structure containning the information of the
                //  curv zero speed.
                //
                //  Outputs :
                //  zeroflag : Boolean value. TRUE means zero structure with a zero speed.
                //
                // 'isAZeroStart:11' zeroFlag = false;
                zeroFlag = false;
                // 'isAZeroStart:13' [zspdmode, error] = getZspdmode( speed );
                //  getZspdmode: Get the current zero speed mode
                //
                //  Inputs :
                //    speed    : structure with zspdmode for the speed
                //
                //  Outputs :
                //    zspdmode : Zero speed mode
                //    error    : Error bolean value. TRUE if no zspdmode has been found.
                //
                // 'getZspdmode:13' error = false;
                // 'getZspdmode:15' if( isenum( speed ) )
                // 'getZspdmode:17' elseif( isfield( speed, "Info") )
                // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
                // 'isAZeroStart:15' if( error )
                // 'isAZeroStart:17' if( zspdmode == ZSpdMode.ZN || ...
                // 'isAZeroStart:18'     zspdmode == ZSpdMode.ZZ )
                if ((curv.Info.zspdmode == ZSpdMode_ZN) || (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                    // 'isAZeroStart:19' zeroFlag = true;
                    zeroFlag = true;
                }
                if (zeroFlag) {
                    // 'compressCurvStructs:93' if( coder.target( "MATLAB" ) )
                    // 'compressCurvStructs:96' closeBatch = true;
                    closeBatch = true;
                }
                //  Cond 3. Machine parameters are not the same
                // 'compressCurvStructs:100' if( ~isSameMachiningParameters( batch.lastCurv, curv )
                // )
                //  isSameMachiningParameters : Check if the machine parameters are equal
                //
                //  Inputs :
                //    curv1 : First curve
                //    curv2 : Second curve
                //
                //  Outputs :
                //    value : Boolean value. TRUE means the two curves machine parameters are
                //    equals.
                //
                // 'isSameMachiningParameters:12' isSame = false;
                isSame = false;
                // if( curv1.Info.FeedRate ~= curv2.Info.FeedRate ),           return; end
                // 'isSameMachiningParameters:14' if( curv1.Info.SpindleSpeed ~=
                // curv2.Info.SpindleSpeed )
                if ((batch_lastCurv.Info.SpindleSpeed == curv.Info.SpindleSpeed) &&
                    (batch_lastCurv.Info.TRAFO == curv.Info.TRAFO)) {
                    // 'isSameMachiningParameters:15' if( curv1.Info.TRAFO ~= curv2.Info.TRAFO )
                    // 'isSameMachiningParameters:16' isSame = true;
                    isSame = true;
                }
                if (!isSame) {
                    // 'compressCurvStructs:101' if( coder.target( "MATLAB" ) )
                    // 'compressCurvStructs:105' closeBatch = true;
                    closeBatch = true;
                }
                //  Cond 4. If to small don't test the collinearity
                // 'compressCurvStructs:109' if( LengthCurv( ctx, curv, 0, 1 ) <=
                // ctx.cfg.LThresholdMin )
                if (LengthCurv(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                               ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                               ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                               ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart, ctx->cfg.NRot,
                               ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW,
                               &curv) > ctx->cfg.LThresholdMin) {
                    int rb_loop_ub;
                    int sb_loop_ub;
                    bool collinear;
                    //  Cond 5. If not collinear lines, create a new batch
                    // 'compressCurvStructs:117' collinear = curvCollinear( ctx, batch.lastCurv,
                    // curv, ... 'compressCurvStructs:118'     ctx.cfg.Compressing.ColTolCosLee );
                    //  curvCollinear : Check whether or not two curves are collinear.
                    //
                    //  Inputs :
                    //  ctx           : The context of the computational chain
                    //  curv1         : The first curve
                    //  curv2         : The second curve
                    //  toleranceCos  : The tolerance used to determinate the colinearity
                    //
                    //  Outputs :
                    //  areCollinear  : Are the two curves collinear
                    //
                    // 'curvCollinear:15' [~, V0] = EvalCurvStruct(ctx, curv1, 1);
                    e_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                     ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                     ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                     ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                     ctx->cfg.NRot, &batch_lastCurv, a__1, V0);
                    // 'curvCollinear:16' [~, V1] = EvalCurvStruct(ctx, curv2, 0);
                    d_EvalCurvStruct(&ctx->q_spline, ctx->cfg.maskTot.data, ctx->cfg.maskTot.size,
                                     ctx->cfg.maskCart.data, ctx->cfg.maskCart.size,
                                     ctx->cfg.maskRot.data, ctx->cfg.maskRot.size, ctx->cfg.indCart,
                                     ctx->cfg.indRot, ctx->cfg.NumberAxis, ctx->cfg.NCart,
                                     ctx->cfg.NRot, &curv, a__2, V1);
                    // 'curvCollinear:18' areCollinear = collinear(V0(ctx.cfg.indCart),
                    // V1(ctx.cfg.indCart), toleranceCos);
                    u.set_size(ctx->cfg.indCart.size(0));
                    rb_loop_ub = ctx->cfg.indCart.size(0);
                    for (int i44{0}; i44 < rb_loop_ub; i44++) {
                        u[i44] = V0[ctx->cfg.indCart[i44] - 1];
                    }
                    v.set_size(ctx->cfg.indCart.size(0));
                    sb_loop_ub = ctx->cfg.indCart.size(0);
                    for (int i45{0}; i45 < sb_loop_ub; i45++) {
                        v[i45] = V1[ctx->cfg.indCart[i45] - 1];
                    }
                    //  collinear : Check if the two vectors are collinear based on a given
                    //  cos tolerance.
                    //
                    //  Inputs :
                    //    u       : A vector in R^n
                    //    v       : A vector in R^n
                    //    tol_cos : A cos tolerance
                    //
                    //  Outputs :
                    //    valid   : Boolean value, TRUE if the two vectors are collinear
                    //
                    // 'collinear:13' if ( norm( u ) < eps || norm( v ) < eps )
                    if ((coder::b_norm(u) < 2.2204460492503131E-16) ||
                        (coder::b_norm(v) < 2.2204460492503131E-16)) {
                        // 'collinear:14' valid = true;
                        collinear = true;
                    } else {
                        double b_x;
                        double c;
                        double x;
                        int tb_loop_ub;
                        int ub_loop_ub;
                        // 'collinear:17' cos_angle   = dot( u, v ) / ( MyNorm( u ) * MyNorm( v ) );
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
                        r.set_size(u.size(0));
                        tb_loop_ub = u.size(0);
                        for (int i46{0}; i46 < tb_loop_ub; i46++) {
                            double varargin_1;
                            varargin_1 = u[i46];
                            r[i46] = std::pow(varargin_1, 2.0);
                        }
                        x = coder::sum(r);
                        //  mysqrt : Custom implementation of the sqrt method.
                        //
                        //  Inputs :
                        //    x : Value used for the computation
                        //  Outputs :
                        //    y : Resulting value
                        //
                        // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
                        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename
                        // );
                        ocn_assert(x >= 0.0);
                        // 'mysqrt:11' y = sqrt(x);
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
                        r.set_size(v.size(0));
                        ub_loop_ub = v.size(0);
                        for (int i48{0}; i48 < ub_loop_ub; i48++) {
                            double b_varargin_1;
                            b_varargin_1 = v[i48];
                            r[i48] = std::pow(b_varargin_1, 2.0);
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
                        // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename
                        // );
                        ocn_assert(b_x >= 0.0);
                        // 'mysqrt:11' y = sqrt(x);
                        // 'collinear:18' valid       = ( cos_angle >= tol_cos );
                        c = 0.0;
                        if (ctx->cfg.indCart.size(0) >= 1) {
                            int ixlast;
                            ixlast = ctx->cfg.indCart.size(0);
                            for (int b_k{0}; b_k < ixlast; b_k++) {
                                c += V0[ctx->cfg.indCart[b_k] - 1] * V1[ctx->cfg.indCart[b_k] - 1];
                            }
                        }
                        collinear = (c / (std::sqrt(x) * std::sqrt(b_x)) >=
                                     ctx->cfg.Compressing.ColTolCosLee);
                    }
                    // 'compressCurvStructs:119' if( ~collinear )
                    if (!collinear) {
                        // 'compressCurvStructs:120' if( coder.target( "MATLAB" ) )
                        // 'compressCurvStructs:123' closeBatch = true;
                        closeBatch = true;
                    }
                } else {
                    // 'compressCurvStructs:110' if( coder.target( "MATLAB" ) )
                }
            }
            // 'compressCurvStructs:39' if( closeBatch )
            if (closeBatch) {
                double batch_lastCurv_ConstJerk;
                double batch_lastCurv_Info_FeedRate;
                double batch_lastCurv_Info_SpindleSpeed;
                double batch_lastCurv_a_param;
                double batch_lastCurv_b_param;
                double batch_lastCurv_delta;
                double batch_lastCurv_pitch;
                double batch_lastCurv_sp_Ltot;
                double batch_lastCurv_theta;
                double batch_lastCurv_tool_backangle;
                double batch_lastCurv_tool_diameter;
                double batch_lastCurv_tool_frontangle;
                double batch_lastCurv_tool_offset_a;
                double batch_lastCurv_tool_offset_b;
                double batch_lastCurv_tool_offset_c;
                double batch_lastCurv_tool_offset_u;
                double batch_lastCurv_tool_offset_v;
                double batch_lastCurv_tool_offset_w;
                double batch_lastCurv_tool_offset_x;
                double batch_lastCurv_tool_offset_y;
                double batch_lastCurv_tool_offset_z;
                unsigned long batch_lastCurv_sp_Bl_handle;
                int ac_loop_ub;
                int batch_lastCurv_Info_gcode_source_line;
                int batch_lastCurv_i_begin_sp;
                int batch_lastCurv_i_end_sp;
                int batch_lastCurv_index_smooth;
                int batch_lastCurv_sp_Bl_ncoeff;
                int batch_lastCurv_sp_Bl_order;
                unsigned int batch_lastCurv_sp_index;
                int batch_lastCurv_tool_orientation;
                int batch_lastCurv_tool_pocketno;
                int batch_lastCurv_tool_toolno;
                int bc_loop_ub;
                int vb_loop_ub;
                int wb_loop_ub;
                int xb_loop_ub;
                bool batch_lastCurv_Info_G91;
                bool batch_lastCurv_Info_G91_1;
                bool batch_lastCurv_Info_HSC;
                bool batch_lastCurv_Info_TRAFO;
                bool batch_lastCurv_UseConstJerk;
                CurveType batch_lastCurv_Info_Type;
                ZSpdMode batch_lastCurv_Info_zspdmode;
                // 'compressCurvStructs:40' [ ctx, batch, spline_index ] = batch_close( ctx, batch,
                // spline_index ); 'compressCurvStructs:143' if( batch.size == 0 )
                if (batch_size == 0.0) {
                    int ab_loop_ub;
                    int db_loop_ub;
                    int fb_loop_ub;
                    int hb_loop_ub;
                    int kb_loop_ub;
                    int mb_loop_ub;
                    int o_loop_ub;
                    int p_loop_ub;
                    int s_loop_ub;
                    int u_loop_ub;
                    int x_loop_ub;
                    // 'compressCurvStructs:144' batch = batch_init();
                    // 'compressCurvStructs:129' batch = struct( ...
                    // 'compressCurvStructs:130'     'pvec',          zeros(
                    // StructTypeName.NumberAxisMax, 1 ),... 'compressCurvStructs:131' 'lastCurv',
                    // constrCurvStructType,... 'compressCurvStructs:132'     'size',          0,
                    // ... 'compressCurvStructs:133'     'zspdmode',      ZSpdMode.NN ...
                    // 'compressCurvStructs:134'     );
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
                    e_expl_temp.sp.Bl.breakpoints.set_size(1,
                                                           expl_temp_tmp.sp.Bl.breakpoints.size(1));
                    o_loop_ub = expl_temp_tmp.sp.Bl.breakpoints.size(1);
                    for (int i19{0}; i19 < o_loop_ub; i19++) {
                        e_expl_temp.sp.Bl.breakpoints[i19] = expl_temp_tmp.sp.Bl.breakpoints[i19];
                    }
                    e_expl_temp.sp.coeff.set_size(expl_temp_tmp.sp.coeff.size(0),
                                                  expl_temp_tmp.sp.coeff.size(1));
                    p_loop_ub = expl_temp_tmp.sp.coeff.size(1);
                    for (int i21{0}; i21 < p_loop_ub; i21++) {
                        int r_loop_ub;
                        r_loop_ub = expl_temp_tmp.sp.coeff.size(0);
                        for (int i23{0}; i23 < r_loop_ub; i23++) {
                            e_expl_temp.sp.coeff[i23 + e_expl_temp.sp.coeff.size(0) * i21] =
                                expl_temp_tmp.sp.coeff[i23 + expl_temp_tmp.sp.coeff.size(0) * i21];
                        }
                    }
                    e_expl_temp.sp.knots.set_size(1, expl_temp_tmp.sp.knots.size(1));
                    s_loop_ub = expl_temp_tmp.sp.knots.size(1);
                    for (int i24{0}; i24 < s_loop_ub; i24++) {
                        e_expl_temp.sp.knots[i24] = expl_temp_tmp.sp.knots[i24];
                    }
                    e_expl_temp.sp.Lk.set_size(1, expl_temp_tmp.sp.Lk.size(1));
                    u_loop_ub = expl_temp_tmp.sp.Lk.size(1);
                    for (int i26{0}; i26 < u_loop_ub; i26++) {
                        e_expl_temp.sp.Lk[i26] = expl_temp_tmp.sp.Lk[i26];
                    }
                    x_loop_ub = expl_temp_tmp.R0.size[0];
                    e_expl_temp.R0.size[0] = expl_temp_tmp.R0.size[0];
                    if (x_loop_ub - 1 >= 0) {
                        std::copy(&expl_temp_tmp.R0.data[0], &expl_temp_tmp.R0.data[x_loop_ub],
                                  &e_expl_temp.R0.data[0]);
                    }
                    ab_loop_ub = expl_temp_tmp.R1.size[0];
                    e_expl_temp.R1.size[0] = expl_temp_tmp.R1.size[0];
                    if (ab_loop_ub - 1 >= 0) {
                        std::copy(&expl_temp_tmp.R1.data[0], &expl_temp_tmp.R1.data[ab_loop_ub],
                                  &e_expl_temp.R1.data[0]);
                    }
                    e_expl_temp.CorrectedHelixCenter[0] = expl_temp_tmp.CorrectedHelixCenter[0];
                    e_expl_temp.evec[0] = expl_temp_tmp.evec[0];
                    e_expl_temp.CorrectedHelixCenter[1] = expl_temp_tmp.CorrectedHelixCenter[1];
                    e_expl_temp.evec[1] = expl_temp_tmp.evec[1];
                    e_expl_temp.CorrectedHelixCenter[2] = expl_temp_tmp.CorrectedHelixCenter[2];
                    e_expl_temp.evec[2] = expl_temp_tmp.evec[2];
                    e_expl_temp.CoeffP5.set_size(expl_temp_tmp.CoeffP5.size(0),
                                                 expl_temp_tmp.CoeffP5.size(1));
                    db_loop_ub = expl_temp_tmp.CoeffP5.size(1);
                    for (int i30{0}; i30 < db_loop_ub; i30++) {
                        int eb_loop_ub;
                        eb_loop_ub = expl_temp_tmp.CoeffP5.size(0);
                        for (int i31{0}; i31 < eb_loop_ub; i31++) {
                            e_expl_temp.CoeffP5[i31 + e_expl_temp.CoeffP5.size(0) * i30] =
                                expl_temp_tmp.CoeffP5[i31 + expl_temp_tmp.CoeffP5.size(0) * i30];
                        }
                    }
                    e_expl_temp.Coeff.set_size(expl_temp_tmp.Coeff.size(0));
                    fb_loop_ub = expl_temp_tmp.Coeff.size(0);
                    for (int i32{0}; i32 < fb_loop_ub; i32++) {
                        e_expl_temp.Coeff[i32] = expl_temp_tmp.Coeff[i32];
                    }
                    hb_loop_ub = e_expl_temp.R0.size[0];
                    batch_lastCurv.R0.set_size(e_expl_temp.R0.size[0]);
                    for (int i34{0}; i34 < hb_loop_ub; i34++) {
                        batch_lastCurv.R0[i34] = e_expl_temp.R0.data[i34];
                    }
                    kb_loop_ub = e_expl_temp.R1.size[0];
                    batch_lastCurv.R1.set_size(e_expl_temp.R1.size[0]);
                    for (int i37{0}; i37 < kb_loop_ub; i37++) {
                        batch_lastCurv.R1[i37] = e_expl_temp.R1.data[i37];
                    }
                    batch_lastCurv.CoeffP5.set_size(e_expl_temp.CoeffP5.size(0),
                                                    e_expl_temp.CoeffP5.size(1));
                    mb_loop_ub = e_expl_temp.CoeffP5.size(1);
                    for (int i39{0}; i39 < mb_loop_ub; i39++) {
                        int ob_loop_ub;
                        ob_loop_ub = e_expl_temp.CoeffP5.size(0);
                        for (int i41{0}; i41 < ob_loop_ub; i41++) {
                            batch_lastCurv.CoeffP5[i41 + batch_lastCurv.CoeffP5.size(0) * i39] =
                                e_expl_temp.CoeffP5[i41 + e_expl_temp.CoeffP5.size(0) * i39];
                        }
                    }
                    // 'compressCurvStructs:136' if( ~coder.target( "MATLAB" ) )
                    // 'compressCurvStructs:137' coder.varsize( 'batch.pvec',
                    // StructTypeName.dimPvec{ : } );
                    batch_lastCurv_Info_Type = expl_temp_tmp.Info.Type;
                    batch_lastCurv_Info_zspdmode = expl_temp_tmp.Info.zspdmode;
                    batch_lastCurv_Info_TRAFO = expl_temp_tmp.Info.TRAFO;
                    batch_lastCurv_Info_HSC = expl_temp_tmp.Info.HSC;
                    batch_lastCurv_Info_FeedRate = expl_temp_tmp.Info.FeedRate;
                    batch_lastCurv_Info_SpindleSpeed = expl_temp_tmp.Info.SpindleSpeed;
                    batch_lastCurv_Info_gcode_source_line = expl_temp_tmp.Info.gcode_source_line;
                    batch_lastCurv_Info_G91 = expl_temp_tmp.Info.G91;
                    batch_lastCurv_Info_G91_1 = expl_temp_tmp.Info.G91_1;
                    batch_lastCurv_tool_toolno = expl_temp_tmp.tool.toolno;
                    batch_lastCurv_tool_pocketno = expl_temp_tmp.tool.pocketno;
                    batch_lastCurv_tool_offset_x = expl_temp_tmp.tool.offset.x;
                    batch_lastCurv_tool_offset_y = expl_temp_tmp.tool.offset.y;
                    batch_lastCurv_tool_offset_z = expl_temp_tmp.tool.offset.z;
                    batch_lastCurv_tool_offset_a = expl_temp_tmp.tool.offset.a;
                    batch_lastCurv_tool_offset_b = expl_temp_tmp.tool.offset.b;
                    batch_lastCurv_tool_offset_c = expl_temp_tmp.tool.offset.c;
                    batch_lastCurv_tool_offset_u = expl_temp_tmp.tool.offset.u;
                    batch_lastCurv_tool_offset_v = expl_temp_tmp.tool.offset.v;
                    batch_lastCurv_tool_offset_w = expl_temp_tmp.tool.offset.w;
                    batch_lastCurv_tool_diameter = expl_temp_tmp.tool.diameter;
                    batch_lastCurv_tool_frontangle = expl_temp_tmp.tool.frontangle;
                    batch_lastCurv_tool_backangle = expl_temp_tmp.tool.backangle;
                    batch_lastCurv_tool_orientation = expl_temp_tmp.tool.orientation;
                    batch_lastCurv_sp_Bl_ncoeff = expl_temp_tmp.sp.Bl.ncoeff;
                    batch_lastCurv_sp_Bl_handle = expl_temp_tmp.sp.Bl.handle;
                    batch_lastCurv_sp_Bl_order = expl_temp_tmp.sp.Bl.order;
                    batch_lastCurv_sp_Ltot = expl_temp_tmp.sp.Ltot;
                    batch_lastCurv_delta = expl_temp_tmp.delta;
                    batch_lastCurv_theta = expl_temp_tmp.theta;
                    batch_lastCurv_pitch = expl_temp_tmp.pitch;
                    batch_lastCurv_sp_index = expl_temp_tmp.sp_index;
                    batch_lastCurv_i_begin_sp = expl_temp_tmp.i_begin_sp;
                    batch_lastCurv_i_end_sp = expl_temp_tmp.i_end_sp;
                    batch_lastCurv_index_smooth = expl_temp_tmp.index_smooth;
                    batch_lastCurv_UseConstJerk = expl_temp_tmp.UseConstJerk;
                    batch_lastCurv_ConstJerk = expl_temp_tmp.ConstJerk;
                    batch_lastCurv_a_param = expl_temp_tmp.a_param;
                    batch_lastCurv_b_param = expl_temp_tmp.b_param;
                } else {
                    int bb_loop_ub;
                    int cb_loop_ub;
                    int gb_loop_ub;
                    int jb_loop_ub;
                    int lb_loop_ub;
                    int nb_loop_ub;
                    int pb_loop_ub;
                    int q_loop_ub;
                    int t_loop_ub;
                    int w_loop_ub;
                    int y_loop_ub;
                    // 'compressCurvStructs:148' if( batch.size > 1 )
                    if (batch_size > 1.0) {
                        // 'compressCurvStructs:149' [ curvCompressed, spline, spline_index ] = ...
                        // 'compressCurvStructs:150'         create_spline( ctx, batch, spline_index
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
                        // 'compressCurvStructs:152' ctx.q_compress.push( curvCompressed );
                        ctx->q_compress.push(&curvCompressed);
                        // 'compressCurvStructs:153' ctx.q_spline.push( spline );
                        ctx->q_spline.push(&spline);
                        //      [r, rd, rdd, rddd ] = EvalCurvStruct( ctx, curvCompressed, [0, 1]);
                        // 'compressCurvStructs:157' if( coder.target( "MATLAB" ) )
                    } else {
                        // 'compressCurvStructs:162' else
                        // 'compressCurvStructs:163' ctx.q_compress.push( batch.lastCurv );
                        ctx->q_compress.push(&batch_lastCurv);
                    }
                    // 'compressCurvStructs:166' if( coder.target( "MATLAB" ) )
                    // 'compressCurvStructs:170' batch = batch_init();
                    // 'compressCurvStructs:129' batch = struct( ...
                    // 'compressCurvStructs:130'     'pvec',          zeros(
                    // StructTypeName.NumberAxisMax, 1 ),... 'compressCurvStructs:131' 'lastCurv',
                    // constrCurvStructType,... 'compressCurvStructs:132'     'size',          0,
                    // ... 'compressCurvStructs:133'     'zspdmode',      ZSpdMode.NN ...
                    // 'compressCurvStructs:134'     );
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
                    e_expl_temp.sp.Bl.breakpoints.set_size(1,
                                                           expl_temp_tmp.sp.Bl.breakpoints.size(1));
                    q_loop_ub = expl_temp_tmp.sp.Bl.breakpoints.size(1);
                    for (int i22{0}; i22 < q_loop_ub; i22++) {
                        e_expl_temp.sp.Bl.breakpoints[i22] = expl_temp_tmp.sp.Bl.breakpoints[i22];
                    }
                    e_expl_temp.sp.coeff.set_size(expl_temp_tmp.sp.coeff.size(0),
                                                  expl_temp_tmp.sp.coeff.size(1));
                    t_loop_ub = expl_temp_tmp.sp.coeff.size(1);
                    for (int i25{0}; i25 < t_loop_ub; i25++) {
                        int v_loop_ub;
                        v_loop_ub = expl_temp_tmp.sp.coeff.size(0);
                        for (int i27{0}; i27 < v_loop_ub; i27++) {
                            e_expl_temp.sp.coeff[i27 + e_expl_temp.sp.coeff.size(0) * i25] =
                                expl_temp_tmp.sp.coeff[i27 + expl_temp_tmp.sp.coeff.size(0) * i25];
                        }
                    }
                    e_expl_temp.sp.knots.set_size(1, expl_temp_tmp.sp.knots.size(1));
                    w_loop_ub = expl_temp_tmp.sp.knots.size(1);
                    for (int i28{0}; i28 < w_loop_ub; i28++) {
                        e_expl_temp.sp.knots[i28] = expl_temp_tmp.sp.knots[i28];
                    }
                    e_expl_temp.sp.Lk.set_size(1, expl_temp_tmp.sp.Lk.size(1));
                    y_loop_ub = expl_temp_tmp.sp.Lk.size(1);
                    for (int i29{0}; i29 < y_loop_ub; i29++) {
                        e_expl_temp.sp.Lk[i29] = expl_temp_tmp.sp.Lk[i29];
                    }
                    bb_loop_ub = expl_temp_tmp.R0.size[0];
                    e_expl_temp.R0.size[0] = expl_temp_tmp.R0.size[0];
                    if (bb_loop_ub - 1 >= 0) {
                        std::copy(&expl_temp_tmp.R0.data[0], &expl_temp_tmp.R0.data[bb_loop_ub],
                                  &e_expl_temp.R0.data[0]);
                    }
                    cb_loop_ub = expl_temp_tmp.R1.size[0];
                    e_expl_temp.R1.size[0] = expl_temp_tmp.R1.size[0];
                    if (cb_loop_ub - 1 >= 0) {
                        std::copy(&expl_temp_tmp.R1.data[0], &expl_temp_tmp.R1.data[cb_loop_ub],
                                  &e_expl_temp.R1.data[0]);
                    }
                    e_expl_temp.CorrectedHelixCenter[0] = expl_temp_tmp.CorrectedHelixCenter[0];
                    e_expl_temp.evec[0] = expl_temp_tmp.evec[0];
                    e_expl_temp.CorrectedHelixCenter[1] = expl_temp_tmp.CorrectedHelixCenter[1];
                    e_expl_temp.evec[1] = expl_temp_tmp.evec[1];
                    e_expl_temp.CorrectedHelixCenter[2] = expl_temp_tmp.CorrectedHelixCenter[2];
                    e_expl_temp.evec[2] = expl_temp_tmp.evec[2];
                    e_expl_temp.CoeffP5.set_size(expl_temp_tmp.CoeffP5.size(0),
                                                 expl_temp_tmp.CoeffP5.size(1));
                    gb_loop_ub = expl_temp_tmp.CoeffP5.size(1);
                    for (int i33{0}; i33 < gb_loop_ub; i33++) {
                        int ib_loop_ub;
                        ib_loop_ub = expl_temp_tmp.CoeffP5.size(0);
                        for (int i35{0}; i35 < ib_loop_ub; i35++) {
                            e_expl_temp.CoeffP5[i35 + e_expl_temp.CoeffP5.size(0) * i33] =
                                expl_temp_tmp.CoeffP5[i35 + expl_temp_tmp.CoeffP5.size(0) * i33];
                        }
                    }
                    e_expl_temp.Coeff.set_size(expl_temp_tmp.Coeff.size(0));
                    jb_loop_ub = expl_temp_tmp.Coeff.size(0);
                    for (int i36{0}; i36 < jb_loop_ub; i36++) {
                        e_expl_temp.Coeff[i36] = expl_temp_tmp.Coeff[i36];
                    }
                    lb_loop_ub = e_expl_temp.R0.size[0];
                    batch_lastCurv.R0.set_size(e_expl_temp.R0.size[0]);
                    for (int i38{0}; i38 < lb_loop_ub; i38++) {
                        batch_lastCurv.R0[i38] = e_expl_temp.R0.data[i38];
                    }
                    nb_loop_ub = e_expl_temp.R1.size[0];
                    batch_lastCurv.R1.set_size(e_expl_temp.R1.size[0]);
                    for (int i40{0}; i40 < nb_loop_ub; i40++) {
                        batch_lastCurv.R1[i40] = e_expl_temp.R1.data[i40];
                    }
                    batch_lastCurv.CoeffP5.set_size(e_expl_temp.CoeffP5.size(0),
                                                    e_expl_temp.CoeffP5.size(1));
                    pb_loop_ub = e_expl_temp.CoeffP5.size(1);
                    for (int i42{0}; i42 < pb_loop_ub; i42++) {
                        int qb_loop_ub;
                        qb_loop_ub = e_expl_temp.CoeffP5.size(0);
                        for (int i43{0}; i43 < qb_loop_ub; i43++) {
                            batch_lastCurv.CoeffP5[i43 + batch_lastCurv.CoeffP5.size(0) * i42] =
                                e_expl_temp.CoeffP5[i43 + e_expl_temp.CoeffP5.size(0) * i42];
                        }
                    }
                    // 'compressCurvStructs:136' if( ~coder.target( "MATLAB" ) )
                    // 'compressCurvStructs:137' coder.varsize( 'batch.pvec',
                    // StructTypeName.dimPvec{ : } );
                    batch_lastCurv_Info_Type = expl_temp_tmp.Info.Type;
                    batch_lastCurv_Info_zspdmode = expl_temp_tmp.Info.zspdmode;
                    batch_lastCurv_Info_TRAFO = expl_temp_tmp.Info.TRAFO;
                    batch_lastCurv_Info_HSC = expl_temp_tmp.Info.HSC;
                    batch_lastCurv_Info_FeedRate = expl_temp_tmp.Info.FeedRate;
                    batch_lastCurv_Info_SpindleSpeed = expl_temp_tmp.Info.SpindleSpeed;
                    batch_lastCurv_Info_gcode_source_line = expl_temp_tmp.Info.gcode_source_line;
                    batch_lastCurv_Info_G91 = expl_temp_tmp.Info.G91;
                    batch_lastCurv_Info_G91_1 = expl_temp_tmp.Info.G91_1;
                    batch_lastCurv_tool_toolno = expl_temp_tmp.tool.toolno;
                    batch_lastCurv_tool_pocketno = expl_temp_tmp.tool.pocketno;
                    batch_lastCurv_tool_offset_x = expl_temp_tmp.tool.offset.x;
                    batch_lastCurv_tool_offset_y = expl_temp_tmp.tool.offset.y;
                    batch_lastCurv_tool_offset_z = expl_temp_tmp.tool.offset.z;
                    batch_lastCurv_tool_offset_a = expl_temp_tmp.tool.offset.a;
                    batch_lastCurv_tool_offset_b = expl_temp_tmp.tool.offset.b;
                    batch_lastCurv_tool_offset_c = expl_temp_tmp.tool.offset.c;
                    batch_lastCurv_tool_offset_u = expl_temp_tmp.tool.offset.u;
                    batch_lastCurv_tool_offset_v = expl_temp_tmp.tool.offset.v;
                    batch_lastCurv_tool_offset_w = expl_temp_tmp.tool.offset.w;
                    batch_lastCurv_tool_diameter = expl_temp_tmp.tool.diameter;
                    batch_lastCurv_tool_frontangle = expl_temp_tmp.tool.frontangle;
                    batch_lastCurv_tool_backangle = expl_temp_tmp.tool.backangle;
                    batch_lastCurv_tool_orientation = expl_temp_tmp.tool.orientation;
                    batch_lastCurv_sp_Bl_ncoeff = expl_temp_tmp.sp.Bl.ncoeff;
                    batch_lastCurv_sp_Bl_handle = expl_temp_tmp.sp.Bl.handle;
                    batch_lastCurv_sp_Bl_order = expl_temp_tmp.sp.Bl.order;
                    batch_lastCurv_sp_Ltot = expl_temp_tmp.sp.Ltot;
                    batch_lastCurv_delta = expl_temp_tmp.delta;
                    batch_lastCurv_theta = expl_temp_tmp.theta;
                    batch_lastCurv_pitch = expl_temp_tmp.pitch;
                    batch_lastCurv_sp_index = expl_temp_tmp.sp_index;
                    batch_lastCurv_i_begin_sp = expl_temp_tmp.i_begin_sp;
                    batch_lastCurv_i_end_sp = expl_temp_tmp.i_end_sp;
                    batch_lastCurv_index_smooth = expl_temp_tmp.index_smooth;
                    batch_lastCurv_UseConstJerk = expl_temp_tmp.UseConstJerk;
                    batch_lastCurv_ConstJerk = expl_temp_tmp.ConstJerk;
                    batch_lastCurv_a_param = expl_temp_tmp.a_param;
                    batch_lastCurv_b_param = expl_temp_tmp.b_param;
                }
                batch_pvec.set_size(6, 1);
                for (int i47{0}; i47 < 6; i47++) {
                    batch_pvec[i47] = 0.0;
                }
                batch_lastCurv.Info.Type = batch_lastCurv_Info_Type;
                batch_lastCurv.Info.zspdmode = batch_lastCurv_Info_zspdmode;
                batch_lastCurv.Info.TRAFO = batch_lastCurv_Info_TRAFO;
                batch_lastCurv.Info.HSC = batch_lastCurv_Info_HSC;
                batch_lastCurv.Info.FeedRate = batch_lastCurv_Info_FeedRate;
                batch_lastCurv.Info.SpindleSpeed = batch_lastCurv_Info_SpindleSpeed;
                batch_lastCurv.Info.gcode_source_line = batch_lastCurv_Info_gcode_source_line;
                batch_lastCurv.Info.G91 = batch_lastCurv_Info_G91;
                batch_lastCurv.Info.G91_1 = batch_lastCurv_Info_G91_1;
                batch_lastCurv.tool.toolno = batch_lastCurv_tool_toolno;
                batch_lastCurv.tool.pocketno = batch_lastCurv_tool_pocketno;
                batch_lastCurv.tool.offset.x = batch_lastCurv_tool_offset_x;
                batch_lastCurv.tool.offset.y = batch_lastCurv_tool_offset_y;
                batch_lastCurv.tool.offset.z = batch_lastCurv_tool_offset_z;
                batch_lastCurv.tool.offset.a = batch_lastCurv_tool_offset_a;
                batch_lastCurv.tool.offset.b = batch_lastCurv_tool_offset_b;
                batch_lastCurv.tool.offset.c = batch_lastCurv_tool_offset_c;
                batch_lastCurv.tool.offset.u = batch_lastCurv_tool_offset_u;
                batch_lastCurv.tool.offset.v = batch_lastCurv_tool_offset_v;
                batch_lastCurv.tool.offset.w = batch_lastCurv_tool_offset_w;
                batch_lastCurv.tool.diameter = batch_lastCurv_tool_diameter;
                batch_lastCurv.tool.frontangle = batch_lastCurv_tool_frontangle;
                batch_lastCurv.tool.backangle = batch_lastCurv_tool_backangle;
                batch_lastCurv.tool.orientation = batch_lastCurv_tool_orientation;
                batch_lastCurv.sp.Bl.ncoeff = batch_lastCurv_sp_Bl_ncoeff;
                vb_loop_ub = e_expl_temp.sp.Bl.breakpoints.size(1);
                batch_lastCurv.sp.Bl.breakpoints.set_size(1, e_expl_temp.sp.Bl.breakpoints.size(1));
                for (int i49{0}; i49 < vb_loop_ub; i49++) {
                    batch_lastCurv.sp.Bl.breakpoints[i49] = e_expl_temp.sp.Bl.breakpoints[i49];
                }
                batch_lastCurv.sp.Bl.handle = batch_lastCurv_sp_Bl_handle;
                batch_lastCurv.sp.Bl.order = batch_lastCurv_sp_Bl_order;
                wb_loop_ub = e_expl_temp.sp.coeff.size(1);
                batch_lastCurv.sp.coeff.set_size(e_expl_temp.sp.coeff.size(0),
                                                 e_expl_temp.sp.coeff.size(1));
                for (int i50{0}; i50 < wb_loop_ub; i50++) {
                    int yb_loop_ub;
                    yb_loop_ub = e_expl_temp.sp.coeff.size(0);
                    for (int i51{0}; i51 < yb_loop_ub; i51++) {
                        batch_lastCurv.sp.coeff[i51 + batch_lastCurv.sp.coeff.size(0) * i50] =
                            e_expl_temp.sp.coeff[i51 + e_expl_temp.sp.coeff.size(0) * i50];
                    }
                }
                xb_loop_ub = e_expl_temp.sp.knots.size(1);
                batch_lastCurv.sp.knots.set_size(1, e_expl_temp.sp.knots.size(1));
                for (int i52{0}; i52 < xb_loop_ub; i52++) {
                    batch_lastCurv.sp.knots[i52] = e_expl_temp.sp.knots[i52];
                }
                batch_lastCurv.sp.Ltot = batch_lastCurv_sp_Ltot;
                ac_loop_ub = e_expl_temp.sp.Lk.size(1);
                batch_lastCurv.sp.Lk.set_size(1, e_expl_temp.sp.Lk.size(1));
                for (int i53{0}; i53 < ac_loop_ub; i53++) {
                    batch_lastCurv.sp.Lk[i53] = e_expl_temp.sp.Lk[i53];
                }
                batch_lastCurv.delta = batch_lastCurv_delta;
                batch_lastCurv.CorrectedHelixCenter[0] = e_expl_temp.CorrectedHelixCenter[0];
                batch_lastCurv.evec[0] = e_expl_temp.evec[0];
                batch_lastCurv.CorrectedHelixCenter[1] = e_expl_temp.CorrectedHelixCenter[1];
                batch_lastCurv.evec[1] = e_expl_temp.evec[1];
                batch_lastCurv.CorrectedHelixCenter[2] = e_expl_temp.CorrectedHelixCenter[2];
                batch_lastCurv.evec[2] = e_expl_temp.evec[2];
                batch_lastCurv.theta = batch_lastCurv_theta;
                batch_lastCurv.pitch = batch_lastCurv_pitch;
                batch_lastCurv.sp_index = batch_lastCurv_sp_index;
                batch_lastCurv.i_begin_sp = batch_lastCurv_i_begin_sp;
                batch_lastCurv.i_end_sp = batch_lastCurv_i_end_sp;
                batch_lastCurv.index_smooth = batch_lastCurv_index_smooth;
                batch_lastCurv.UseConstJerk = batch_lastCurv_UseConstJerk;
                batch_lastCurv.ConstJerk = batch_lastCurv_ConstJerk;
                bc_loop_ub = e_expl_temp.Coeff.size(0);
                batch_lastCurv.Coeff.set_size(e_expl_temp.Coeff.size(0));
                for (int i54{0}; i54 < bc_loop_ub; i54++) {
                    batch_lastCurv.Coeff[i54] = e_expl_temp.Coeff[i54];
                }
                batch_lastCurv.a_param = batch_lastCurv_a_param;
                batch_lastCurv.b_param = batch_lastCurv_b_param;
                batch_size = 0.0;
                batch_zspdmode = ZSpdMode_NN;
            }
            // 'compressCurvStructs:43' if( addBatch )
            if (addBatch) {
                // 'compressCurvStructs:44' [ batch ] = batch_add_curv( batch, curv );
                // 'compressCurvStructs:175' if( batch.size == 0 )
                if (batch_size == 0.0) {
                    int k_loop_ub;
                    int l_loop_ub;
                    // 'compressCurvStructs:176' batch.pvec      = [ curv.R0, curv.R1 ];
                    batch_pvec.set_size(curv.R0.size(0), 2);
                    k_loop_ub = curv.R0.size(0);
                    for (int i13{0}; i13 < k_loop_ub; i13++) {
                        batch_pvec[i13] = curv.R0[i13];
                    }
                    l_loop_ub = curv.R1.size(0);
                    for (int i14{0}; i14 < l_loop_ub; i14++) {
                        batch_pvec[i14 + batch_pvec.size(0)] = curv.R1[i14];
                    }
                    // 'compressCurvStructs:177' batch.lastCurv  = curv;
                    batch_lastCurv = curv;
                    // 'compressCurvStructs:178' batch.size      = 1;
                    batch_size = 1.0;
                    // 'compressCurvStructs:179' batch.zspdmode  = curv.Info.zspdmode;
                    batch_zspdmode = curv.Info.zspdmode;
                } else {
                    int m_loop_ub;
                    int n_loop_ub;
                    int result;
                    signed char i15;
                    bool b_zeroFlag;
                    bool empty_non_axis_sizes;
                    // 'compressCurvStructs:180' else
                    // 'compressCurvStructs:181' batch.pvec      = [ batch.pvec, curv.R1 ];
                    if ((batch_pvec.size(0) != 0) && (batch_pvec.size(1) != 0)) {
                        result = batch_pvec.size(0);
                    } else if (curv.R1.size(0) != 0) {
                        result = curv.R1.size(0);
                    } else {
                        result = batch_pvec.size(0);
                        if (curv.R1.size(0) > batch_pvec.size(0)) {
                            result = curv.R1.size(0);
                        }
                    }
                    empty_non_axis_sizes = (result == 0);
                    if (empty_non_axis_sizes ||
                        ((batch_pvec.size(0) != 0) && (batch_pvec.size(1) != 0))) {
                        m_loop_ub = batch_pvec.size(1);
                    } else {
                        m_loop_ub = 0;
                    }
                    if (empty_non_axis_sizes || (curv.R1.size(0) != 0)) {
                        i15 = 1;
                    } else {
                        i15 = 0;
                    }
                    for (int i16{0}; i16 < m_loop_ub; i16++) {
                        for (int i17{0}; i17 < result; i17++) {
                            batch_pvec[i17 + batch_pvec.size(0) * i16] =
                                batch_pvec[i17 + result * i16];
                        }
                    }
                    batch_pvec.set_size(result, m_loop_ub + i15);
                    n_loop_ub = i15;
                    for (int i18{0}; i18 < n_loop_ub; i18++) {
                        for (int i20{0}; i20 < result; i20++) {
                            batch_pvec[i20 + batch_pvec.size(0) * m_loop_ub] = curv.R1[i20];
                        }
                    }
                    // 'compressCurvStructs:182' batch.lastCurv  = curv;
                    batch_lastCurv = curv;
                    // 'compressCurvStructs:183' batch.size      = batch.size + 1;
                    batch_size++;
                    // 'compressCurvStructs:184' if( isAZeroEnd( curv ) )
                    //  isAZeroEnd : Return true if the curv ends with zero speed
                    //
                    //  Inputs :
                    //  curv / Info / ZSpdMode : A structure containning the information of the
                    //  curv zero speed.
                    //
                    //  Outputs :
                    //  zeroFlag : Boolean value. TRUE mean zero flag
                    // 'isAZeroEnd:10' zeroFlag = false;
                    b_zeroFlag = false;
                    // 'isAZeroEnd:12' [zspdmode, error] = getZspdmode( speed );
                    //  getZspdmode: Get the current zero speed mode
                    //
                    //  Inputs :
                    //    speed    : structure with zspdmode for the speed
                    //
                    //  Outputs :
                    //    zspdmode : Zero speed mode
                    //    error    : Error bolean value. TRUE if no zspdmode has been found.
                    //
                    // 'getZspdmode:13' error = false;
                    // 'getZspdmode:15' if( isenum( speed ) )
                    // 'getZspdmode:17' elseif( isfield( speed, "Info") )
                    // 'getZspdmode:18' zspdmode = speed.Info.zspdmode;
                    // 'isAZeroEnd:14' if( error )
                    // 'isAZeroEnd:16' if( zspdmode == ZSpdMode.NZ || ...
                    // 'isAZeroEnd:17'     zspdmode == ZSpdMode.ZZ )
                    if ((curv.Info.zspdmode == ZSpdMode_NZ) ||
                        (curv.Info.zspdmode == ZSpdMode_ZZ)) {
                        // 'isAZeroEnd:18' zeroFlag = true;
                        b_zeroFlag = true;
                    }
                    if (b_zeroFlag) {
                        bool c_zeroFlag;
                        // 'compressCurvStructs:185' if( isAZeroStart( batch.zspdmode ) )
                        //  isAZeroStart : Return true if the curv starts with zero speed
                        //
                        //  Inputs :
                        //  curv / Info / ZSpdMode : A structure containning the information of the
                        //  curv zero speed.
                        //
                        //  Outputs :
                        //  zeroflag : Boolean value. TRUE means zero structure with a zero speed.
                        //
                        // 'isAZeroStart:11' zeroFlag = false;
                        c_zeroFlag = false;
                        // 'isAZeroStart:13' [zspdmode, error] = getZspdmode( speed );
                        //  getZspdmode: Get the current zero speed mode
                        //
                        //  Inputs :
                        //    speed    : structure with zspdmode for the speed
                        //
                        //  Outputs :
                        //    zspdmode : Zero speed mode
                        //    error    : Error bolean value. TRUE if no zspdmode has been found.
                        //
                        // 'getZspdmode:13' error = false;
                        // 'getZspdmode:15' if( isenum( speed ) )
                        // 'getZspdmode:16' zspdmode = speed;
                        // 'isAZeroStart:15' if( error )
                        // 'isAZeroStart:17' if( zspdmode == ZSpdMode.ZN || ...
                        // 'isAZeroStart:18'     zspdmode == ZSpdMode.ZZ )
                        if ((batch_zspdmode == ZSpdMode_ZN) || (batch_zspdmode == ZSpdMode_ZZ)) {
                            // 'isAZeroStart:19' zeroFlag = true;
                            c_zeroFlag = true;
                        }
                        if (c_zeroFlag) {
                            // 'compressCurvStructs:186' batch.zspdmode = ZSpdMode.ZZ;
                            batch_zspdmode = ZSpdMode_ZZ;
                        } else {
                            // 'compressCurvStructs:187' else
                            // 'compressCurvStructs:188' batch.zspdmode = ZSpdMode.NZ;
                            batch_zspdmode = ZSpdMode_NZ;
                        }
                    }
                }
            } else {
                // 'compressCurvStructs:45' else
                // 'compressCurvStructs:46' ctx.q_compress.push( curv );
                ctx->q_compress.push(&curv);
            }
            // 'compressCurvStructs:48' ctx.k0 = ctx.k0 + 1;
            ctx->k0++;
        }
        // 'compressCurvStructs:51' [ ctx ] = batch_close( ctx, batch, spline_index );
        // 'compressCurvStructs:143' if( batch.size == 0 )
        if (batch_size != 0.0) {
            // 'compressCurvStructs:148' if( batch.size > 1 )
            if (batch_size > 1.0) {
                // 'compressCurvStructs:149' [ curvCompressed, spline, spline_index ] = ...
                // 'compressCurvStructs:150'         create_spline( ctx, batch, spline_index );
                b_spline_index = spline_index;
                create_spline(ctx->cfg.maskTot.data, ctx->cfg.maskTot.size, ctx->cfg.NumberAxis,
                              ctx->cfg.LeeSplineDegree, ctx->cfg.GaussLegendreN,
                              ctx->cfg.GaussLegendreX, ctx->cfg.GaussLegendreW, batch_pvec,
                              batch_lastCurv.Info.TRAFO, batch_lastCurv.Info.HSC,
                              batch_lastCurv.Info.FeedRate, batch_lastCurv.Info.SpindleSpeed,
                              batch_lastCurv.Info.gcode_source_line, batch_lastCurv.Info.G91,
                              batch_lastCurv.Info.G91_1, &batch_lastCurv.tool, batch_zspdmode,
                              &b_spline_index, &curvCompressed, &spline);
                // 'compressCurvStructs:152' ctx.q_compress.push( curvCompressed );
                ctx->q_compress.push(&curvCompressed);
                // 'compressCurvStructs:153' ctx.q_spline.push( spline );
                ctx->q_spline.push(&spline);
                //      [r, rd, rdd, rddd ] = EvalCurvStruct( ctx, curvCompressed, [0, 1]);
                // 'compressCurvStructs:157' if( coder.target( "MATLAB" ) )
            } else {
                // 'compressCurvStructs:162' else
                // 'compressCurvStructs:163' ctx.q_compress.push( batch.lastCurv );
                ctx->q_compress.push(&batch_lastCurv);
            }
            // 'compressCurvStructs:166' if( coder.target( "MATLAB" ) )
            // 'compressCurvStructs:170' batch = batch_init();
        } else {
            // 'compressCurvStructs:144' batch = batch_init();
        }
    }
}

} // namespace ocn

//
// File trailer for compressCurvStructs.cpp
//
// [EOF]
//
