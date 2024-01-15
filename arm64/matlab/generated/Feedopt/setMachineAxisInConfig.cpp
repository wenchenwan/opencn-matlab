
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: setMachineAxisInConfig.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "setMachineAxisInConfig.h"
#include "ocn_assert.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "coder_array.h"
#include "coder_bounded_array.h"
#include <algorithm>

// Function Declarations
namespace ocn {
static void check_values(b_FeedoptConfig *cfg);

static void i_binary_expand_op(b_FeedoptConfig *in1, const bool in2[6]);

static void j_binary_expand_op(b_FeedoptConfig *in1, const bool in2[6]);

} // namespace ocn

// Function Definitions
//
// function [ cfg ] = check_values( cfg )
//
// Arguments    : b_FeedoptConfig *cfg
// Return Type  : void
//
namespace ocn {
static void check_values(b_FeedoptConfig *cfg)
{
    static const bool bv[6]{true, true, true, false, false, false};
    static const bool bv1[6]{false, false, false, true, true, true};
    ::coder::array<int, 2U> g_y;
    int b_vlen;
    int d_y;
    int vlen;
    int y;
    // 'setMachineAxisInConfig:22' cfg.maskCart   = and( cfg.maskTot, logical( [ 1, 1, 1, 0, 0, 0 ]
    // ) );
    if (cfg->maskTot.size[1] == 6) {
        cfg->maskCart.size[0] = 1;
        cfg->maskCart.size[1] = 6;
        for (int i{0}; i < 6; i++) {
            cfg->maskCart.data[i] = (cfg->maskTot.data[i] && bv[i]);
        }
    } else {
        j_binary_expand_op(cfg, bv);
    }
    // 'setMachineAxisInConfig:23' cfg.maskRot    = and( cfg.maskTot, logical( [ 0, 0, 0, 1, 1, 1 ]
    // ) );
    if (cfg->maskTot.size[1] == 6) {
        cfg->maskRot.size[0] = 1;
        cfg->maskRot.size[1] = 6;
        for (int i1{0}; i1 < 6; i1++) {
            cfg->maskRot.data[i1] = (cfg->maskTot.data[i1] && bv1[i1]);
        }
    } else {
        i_binary_expand_op(cfg, bv1);
    }
    // 'setMachineAxisInConfig:24' cfg.NumberAxis = int32( sum( cfg.maskTot ) );
    vlen = cfg->maskTot.size[1];
    if (cfg->maskTot.size[1] == 0) {
        y = 0;
    } else {
        int b_y;
        b_y = cfg->maskTot.data[0];
        for (int k{2}; k <= vlen; k++) {
            int c_y;
            c_y = b_y;
            if (vlen >= 2) {
                c_y = b_y + cfg->maskTot.data[k - 1];
            }
            b_y = c_y;
        }
        y = b_y;
    }
    cfg->NumberAxis = y;
    // 'setMachineAxisInConfig:25' cfg.NCart      = int32( sum( cfg.maskCart ) );
    b_vlen = cfg->maskCart.size[1];
    if (cfg->maskCart.size[1] == 0) {
        d_y = 0;
    } else {
        int e_y;
        e_y = cfg->maskCart.data[0];
        for (int b_k{2}; b_k <= b_vlen; b_k++) {
            int f_y;
            f_y = e_y;
            if (b_vlen >= 2) {
                f_y = e_y + cfg->maskCart.data[b_k - 1];
            }
            e_y = f_y;
        }
        d_y = e_y;
    }
    cfg->NCart = d_y;
    // 'setMachineAxisInConfig:26' cfg.NRot       = cfg.NumberAxis - cfg.NCart;
    cfg->NRot = y - d_y;
    // 'setMachineAxisInConfig:27' cfg.D          = ones(cfg.NumberAxis, 1);
    cfg->D.set_size(y);
    for (int i2{0}; i2 < y; i2++) {
        cfg->D[i2] = 1.0;
    }
    // 'setMachineAxisInConfig:29' if( cfg.NCart > 0 )
    if (d_y > 0) {
        int loop_ub;
        int yk;
        // 'setMachineAxisInConfig:30' cfg.indCart = [ 1 : cfg.NCart ].';
        g_y.set_size(1, d_y);
        g_y[0] = 1;
        yk = 1;
        for (int c_k{2}; c_k <= d_y; c_k++) {
            yk++;
            g_y[c_k - 1] = yk;
        }
        cfg->indCart.set_size(g_y.size(1));
        loop_ub = g_y.size(1);
        for (int i3{0}; i3 < loop_ub; i3++) {
            cfg->indCart[i3] = g_y[i3];
        }
    } else {
        // 'setMachineAxisInConfig:31' else
        // 'setMachineAxisInConfig:32' cfg.indCart = int32( 0 );
        cfg->indCart.set_size(1);
        cfg->indCart[0] = 0;
    }
    // 'setMachineAxisInConfig:35' if( cfg.NRot > 0 )
    if (cfg->NRot > 0) {
        int b_loop_ub;
        int c_loop_ub;
        int n;
        // 'setMachineAxisInConfig:36' cfg.indRot = [ 1 : cfg.NRot ].' + cfg.NCart;
        if (cfg->NRot < 1) {
            n = 0;
        } else {
            n = cfg->NRot;
        }
        g_y.set_size(1, n);
        if (n > 0) {
            int b_yk;
            g_y[0] = 1;
            b_yk = 1;
            for (int d_k{2}; d_k <= n; d_k++) {
                b_yk++;
                g_y[d_k - 1] = b_yk;
            }
        }
        cfg->indRot.set_size(g_y.size(1));
        b_loop_ub = g_y.size(1);
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            cfg->indRot[i4] = g_y[i4] + d_y;
        }
        // 'setMachineAxisInConfig:37' cfg.D(cfg.indRot) = cfg.coeffD;
        c_loop_ub = cfg->indRot.size(0);
        for (int i5{0}; i5 < c_loop_ub; i5++) {
            cfg->D[cfg->indRot[i5] - 1] = cfg->coeffD;
        }
    } else {
        // 'setMachineAxisInConfig:38' else
        // 'setMachineAxisInConfig:39' cfg.indRot = int32( 0 );
        cfg->indRot.set_size(1);
        cfg->indRot[0] = 0;
    }
}

//
// Arguments    : b_FeedoptConfig *in1
//                const bool in2[6]
// Return Type  : void
//
static void i_binary_expand_op(b_FeedoptConfig *in1, const bool in2[6])
{
    int stride_0_1;
    in1->maskRot.size[0] = 1;
    in1->maskRot.size[1] = 6;
    stride_0_1 = (in1->maskTot.size[1] != 1);
    for (int i{0}; i < 6; i++) {
        in1->maskRot.data[i] = (in1->maskTot.data[i * stride_0_1] && in2[i]);
    }
}

//
// Arguments    : b_FeedoptConfig *in1
//                const bool in2[6]
// Return Type  : void
//
static void j_binary_expand_op(b_FeedoptConfig *in1, const bool in2[6])
{
    int stride_0_1;
    in1->maskCart.size[0] = 1;
    in1->maskCart.size[1] = 6;
    stride_0_1 = (in1->maskTot.size[1] != 1);
    for (int i{0}; i < 6; i++) {
        in1->maskCart.data[i] = (in1->maskTot.data[i * stride_0_1] && in2[i]);
    }
}

//
// function [ cfg ] = setMachineAxisInConfig( cfg, maskTot )
//
// setMachineAxisInConfig: Use maskTot to specify the axis used by the
//  machine
//  Inputs :
//  cfg       : The configuration structure
//  maskTot   : [ 1 x 6 ] logical vector [x,y,z,a,b,c]
//
//  Outputs :
//  cfg       : The configuration structure
//
// Arguments    : b_FeedoptConfig *cfg
//                const bool maskTot_data[]
// Return Type  : void
//
void b_setMachineAxisInConfig(b_FeedoptConfig *cfg, const bool maskTot_data[])
{
    // 'setMachineAxisInConfig:12' coder.inline("never");
    // 'setMachineAxisInConfig:13' ocn_assert( numel( maskTot ) == 6, "MaskTot should have 6
    // elements...", mfilename);
    b_ocn_assert(true);
    // 'setMachineAxisInConfig:15' cfg.maskTot = maskTot;
    cfg->maskTot.size[0] = 1;
    cfg->maskTot.size[1] = 6;
    for (int i{0}; i < 6; i++) {
        cfg->maskTot.data[i] = maskTot_data[i];
    }
    // 'setMachineAxisInConfig:17' cfg = check_values( cfg );
    check_values(cfg);
}

//
// function [ cfg ] = setMachineAxisInConfig( cfg, maskTot )
//
// setMachineAxisInConfig: Use maskTot to specify the axis used by the
//  machine
//  Inputs :
//  cfg       : The configuration structure
//  maskTot   : [ 1 x 6 ] logical vector [x,y,z,a,b,c]
//
//  Outputs :
//  cfg       : The configuration structure
//
// Arguments    : FeedoptConfig *cfg
//                const bool maskTot_data[]
//                const int maskTot_size[2]
// Return Type  : void
//
void setMachineAxisInConfig(FeedoptConfig *cfg, const bool maskTot_data[],
                            const int maskTot_size[2])
{
    b_FeedoptConfig r;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i_loop_ub;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int n_loop_ub;
    int o_loop_ub;
    int p_loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'setMachineAxisInConfig:12' coder.inline("never");
    // 'setMachineAxisInConfig:13' ocn_assert( numel( maskTot ) == 6, "MaskTot should have 6
    // elements...", mfilename);
    b_ocn_assert(maskTot_size[1] == 6);
    // 'setMachineAxisInConfig:15' cfg.maskTot = maskTot;
    // 'setMachineAxisInConfig:17' cfg = check_values( cfg );
    r.ENABLE_PRINT_MSG = cfg->ENABLE_PRINT_MSG;
    r.maskTot.size[0] = 1;
    r.maskTot.size[1] = maskTot_size[1];
    loop_ub = maskTot_size[1];
    if (loop_ub - 1 >= 0) {
        std::copy(&maskTot_data[0], &maskTot_data[loop_ub], &r.maskTot.data[0]);
    }
    r.maskCart.size[0] = 1;
    r.maskCart.size[1] = cfg->maskCart.size[1];
    b_loop_ub = cfg->maskCart.size[1];
    if (b_loop_ub - 1 >= 0) {
        std::copy(&cfg->maskCart.data[0], &cfg->maskCart.data[b_loop_ub], &r.maskCart.data[0]);
    }
    r.maskRot.size[0] = 1;
    r.maskRot.size[1] = cfg->maskRot.size[1];
    c_loop_ub = cfg->maskRot.size[1];
    if (c_loop_ub - 1 >= 0) {
        std::copy(&cfg->maskRot.data[0], &cfg->maskRot.data[c_loop_ub], &r.maskRot.data[0]);
    }
    r.indCart.set_size(cfg->indCart.size[0]);
    d_loop_ub = cfg->indCart.size[0];
    for (int i{0}; i < d_loop_ub; i++) {
        r.indCart[i] = cfg->indCart.data[i];
    }
    r.indRot.set_size(cfg->indRot.size[0]);
    e_loop_ub = cfg->indRot.size[0];
    for (int i1{0}; i1 < e_loop_ub; i1++) {
        r.indRot[i1] = cfg->indRot.data[i1];
    }
    r.NumberAxis = cfg->NumberAxis;
    r.NCart = cfg->NCart;
    r.NRot = cfg->NRot;
    r.D.set_size(cfg->D.size[0]);
    f_loop_ub = cfg->D.size[0];
    for (int i2{0}; i2 < f_loop_ub; i2++) {
        r.D[i2] = cfg->D.data[i2];
    }
    r.coeffD = cfg->coeffD;
    r.kin_params.size[0] = cfg->kin_params.size[0];
    g_loop_ub = cfg->kin_params.size[0];
    if (g_loop_ub - 1 >= 0) {
        std::copy(&cfg->kin_params.data[0], &cfg->kin_params.data[g_loop_ub],
                  &r.kin_params.data[0]);
    }
    for (int i3{0}; i3 < 8; i3++) {
        r.kin_type[i3] = cfg->kin_type[i3];
    }
    r.NDiscr = cfg->NDiscr;
    r.NBreak = cfg->NBreak;
    r.SplitSpecialSpline = cfg->SplitSpecialSpline;
    r.ReleaseMemoryOfTheQueues = cfg->ReleaseMemoryOfTheQueues;
    r.UseDynamicBreakpoints = cfg->UseDynamicBreakpoints;
    r.UseLinearBreakpoints = cfg->UseLinearBreakpoints;
    r.DynamicBreakpointsDistance = cfg->DynamicBreakpointsDistance;
    r.NHorz = cfg->NHorz;
    for (int i4{0}; i4 < 6; i4++) {
        r.vmax[i4] = cfg->vmax[i4];
        r.amax[i4] = cfg->amax[i4];
        r.jmax[i4] = cfg->jmax[i4];
    }
    r.LeeSplineDegree = cfg->LeeSplineDegree;
    r.SplineDegree = cfg->SplineDegree;
    r.CutOff = cfg->CutOff;
    r.LSplit = cfg->LSplit;
    r.LSplitZero = cfg->LSplitZero;
    r.LThresholdMax = cfg->LThresholdMax;
    r.LThresholdMin = cfg->LThresholdMin;
    r.v_0 = cfg->v_0;
    r.at_0 = cfg->at_0;
    r.v_1 = cfg->v_1;
    r.at_1 = cfg->at_1;
    r.dt = cfg->dt;
    r.DefaultZeroStopCount = cfg->DefaultZeroStopCount;
    r.source.size[0] = 1;
    r.source.size[1] = cfg->source.size[1];
    h_loop_ub = cfg->source.size[1];
    if (h_loop_ub - 1 >= 0) {
        std::copy(&cfg->source.data[0], &cfg->source.data[h_loop_ub], &r.source.data[0]);
    }
    r.Cusp = cfg->Cusp;
    r.Compressing = cfg->Compressing;
    r.Smoothing = cfg->Smoothing;
    r.GaussLegendreN = cfg->GaussLegendreN;
    for (int b_i{0}; b_i < 5; b_i++) {
        r.GaussLegendreX[b_i] = cfg->GaussLegendreX[b_i];
        r.GaussLegendreW[b_i] = cfg->GaussLegendreW[b_i];
    }
    r.opt = cfg->opt;
    for (int i5{0}; i5 < 9; i5++) {
        r.LogFileName[i5] = cfg->LogFileName[i5];
    }
    check_values(&r);
    cfg->ENABLE_PRINT_MSG = r.ENABLE_PRINT_MSG;
    cfg->maskTot.size[0] = 1;
    cfg->maskTot.size[1] = r.maskTot.size[1];
    i_loop_ub = r.maskTot.size[1];
    if (i_loop_ub - 1 >= 0) {
        std::copy(&r.maskTot.data[0], &r.maskTot.data[i_loop_ub], &cfg->maskTot.data[0]);
    }
    cfg->maskCart.size[0] = 1;
    cfg->maskCart.size[1] = r.maskCart.size[1];
    j_loop_ub = r.maskCart.size[1];
    if (j_loop_ub - 1 >= 0) {
        std::copy(&r.maskCart.data[0], &r.maskCart.data[j_loop_ub], &cfg->maskCart.data[0]);
    }
    cfg->maskRot.size[0] = 1;
    cfg->maskRot.size[1] = r.maskRot.size[1];
    k_loop_ub = r.maskRot.size[1];
    if (k_loop_ub - 1 >= 0) {
        std::copy(&r.maskRot.data[0], &r.maskRot.data[k_loop_ub], &cfg->maskRot.data[0]);
    }
    cfg->indCart.size[0] = r.indCart.size(0);
    l_loop_ub = r.indCart.size(0);
    for (int i6{0}; i6 < l_loop_ub; i6++) {
        cfg->indCart.data[i6] = r.indCart[i6];
    }
    cfg->indRot.size[0] = r.indRot.size(0);
    m_loop_ub = r.indRot.size(0);
    for (int i7{0}; i7 < m_loop_ub; i7++) {
        cfg->indRot.data[i7] = r.indRot[i7];
    }
    cfg->NumberAxis = r.NumberAxis;
    cfg->NCart = r.NCart;
    cfg->NRot = r.NRot;
    cfg->D.size[0] = r.D.size(0);
    n_loop_ub = r.D.size(0);
    for (int i8{0}; i8 < n_loop_ub; i8++) {
        cfg->D.data[i8] = r.D[i8];
    }
    cfg->coeffD = r.coeffD;
    cfg->kin_params.size[0] = r.kin_params.size[0];
    o_loop_ub = r.kin_params.size[0];
    if (o_loop_ub - 1 >= 0) {
        std::copy(&r.kin_params.data[0], &r.kin_params.data[o_loop_ub], &cfg->kin_params.data[0]);
    }
    for (int i9{0}; i9 < 8; i9++) {
        cfg->kin_type[i9] = r.kin_type[i9];
    }
    cfg->NDiscr = r.NDiscr;
    cfg->NBreak = r.NBreak;
    cfg->SplitSpecialSpline = r.SplitSpecialSpline;
    cfg->ReleaseMemoryOfTheQueues = r.ReleaseMemoryOfTheQueues;
    cfg->UseDynamicBreakpoints = r.UseDynamicBreakpoints;
    cfg->UseLinearBreakpoints = r.UseLinearBreakpoints;
    cfg->DynamicBreakpointsDistance = r.DynamicBreakpointsDistance;
    cfg->NHorz = r.NHorz;
    for (int i10{0}; i10 < 6; i10++) {
        cfg->vmax[i10] = r.vmax[i10];
        cfg->amax[i10] = r.amax[i10];
        cfg->jmax[i10] = r.jmax[i10];
    }
    cfg->LeeSplineDegree = r.LeeSplineDegree;
    cfg->SplineDegree = r.SplineDegree;
    cfg->CutOff = r.CutOff;
    cfg->LSplit = r.LSplit;
    cfg->LSplitZero = r.LSplitZero;
    cfg->LThresholdMax = r.LThresholdMax;
    cfg->LThresholdMin = r.LThresholdMin;
    cfg->v_0 = r.v_0;
    cfg->at_0 = r.at_0;
    cfg->v_1 = r.v_1;
    cfg->at_1 = r.at_1;
    cfg->dt = r.dt;
    cfg->DefaultZeroStopCount = r.DefaultZeroStopCount;
    cfg->source.size[0] = 1;
    cfg->source.size[1] = r.source.size[1];
    p_loop_ub = r.source.size[1];
    if (p_loop_ub - 1 >= 0) {
        std::copy(&r.source.data[0], &r.source.data[p_loop_ub], &cfg->source.data[0]);
    }
    cfg->Cusp = r.Cusp;
    cfg->Compressing = r.Compressing;
    cfg->Smoothing = r.Smoothing;
    cfg->GaussLegendreN = r.GaussLegendreN;
    for (int c_i{0}; c_i < 5; c_i++) {
        cfg->GaussLegendreX[c_i] = r.GaussLegendreX[c_i];
        cfg->GaussLegendreW[c_i] = r.GaussLegendreW[c_i];
    }
    cfg->opt = r.opt;
    for (int i11{0}; i11 < 9; i11++) {
        cfg->LogFileName[i11] = r.LogFileName[i11];
    }
}

} // namespace ocn

//
// File trailer for setMachineAxisInConfig.cpp
//
// [EOF]
//
