//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptDefaultConfig.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 29-Jun-2022 18:46:44
//

// Include Files
#include "FeedoptDefaultConfig.h"
#include "cosd.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "coder_array.h"
#include <algorithm>
#include <cstring>
#include <emmintrin.h>

// Function Definitions
//
// function [ cfg ] = FeedoptDefaultConfig()
//
// Arguments    : FeedoptConfig *cfg
// Return Type  : void
//
namespace ocn {
void FeedoptDefaultConfig(FeedoptConfig *cfg)
{
    static const double dv[12]{0.0, 0.0, 0.0, 0.0, 0.0, -24.876, 0.0, 0.0, 0.0, 24.876, 0.0, 0.0};
    static const double GaussLegendreW[5]{0.23692688505618911, 0.47862867049936625,
                                          0.56888888888888889, 0.47862867049936625,
                                          0.23692688505618911};
    static const double GaussLegendreX[5]{-0.90617984593866385, -0.538469310105683, 0.0,
                                          0.538469310105683, 0.90617984593866385};
    static const int iv2[6]{750000, 750000, 3000000, 0, 10000, 50000};
    static const short b_iv[6]{500, 500, 800, 0, 40, 50};
    static const short iv1[6]{15000, 15000, 15000, 0, 200, 1000};
    static const char b_cv1[9]{'l', 'o', 'g', 's', '/', 'l', 'o', 'g', 's'};
    static const char b_cv[5]{'x', 'y', 'z', 'b', 'c'};
    static const bool bv[6]{true, true, true, false, false, false};
    static const bool bv1[6]{false, false, false, true, true, true};
    static const bool t9_maskTot[6]{true, true, true, false, true, true};
    ::coder::array<int, 2U> c_y;
    ::coder::array<int, 1U> t10_indCart;
    ::coder::array<int, 1U> t10_indRot;
    ::coder::array<signed char, 1U> t10_D;
    double t9_Smoothing_ColTolCosSmooth;
    int b_y;
    int c_loop_ub;
    int d_loop_ub;
    int f_loop_ub;
    int t10_NRot;
    int y;
    bool x_data[6];
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'FeedoptDefaultConfig:3' coder.inline("never");
    // 'FeedoptDefaultConfig:5' tol_col_compress_deg    = 180;
    // 'FeedoptDefaultConfig:6' tol_col_smooth_deg      = 10;
    //  Computation of Gauss-Legendre knots and weights for numerical integration
    // 'FeedoptDefaultConfig:9' GaussLegendreN = 5;
    //  number of evaluation points
    // 'FeedoptDefaultConfig:10' [GaussLegendreX, GaussLegendreW] = lgwt(GaussLegendreN, -1, 1);
    //  normalized to integration interval [-1, 1]
    // 'FeedoptDefaultConfig:11' GaussLegendreX = flipud(GaussLegendreX);
    // 'FeedoptDefaultConfig:13' LP = struct(...
    // 'FeedoptDefaultConfig:14'     'Type', 'LP', ...
    // 'FeedoptDefaultConfig:15'     'EnableFindReasonInfeasibility', true,...
    // 'FeedoptDefaultConfig:16'     'ACC_RAMP_OVER_WINDOWS', 1.0 - 1E-3,...
    // 'FeedoptDefaultConfig:17'     'VEL_RAMP_OVER_WINDOWS', 1.0 - 1E-3,...
    // 'FeedoptDefaultConfig:18'     'SLACK_PENALTY', 10000, ...
    // 'FeedoptDefaultConfig:19'     'USE_LINPROG', false);
    // 'FeedoptDefaultConfig:21' if( ~coder.target('MATLAB') )
    // 'FeedoptDefaultConfig:22' coder.cstructname( LP,          StructTypeName.LPCfg );
    // 'FeedoptDefaultConfig:25' cfg = struct(...
    // 'FeedoptDefaultConfig:26'     'maskTot',  logical( [ 1, 1, 1, 0, 1, 1 ] ),... % [X,Y,Z,A,B,C]
    // 'FeedoptDefaultConfig:27'     'maskCart', logical( 0 ),...                    % Do not modify
    // 'FeedoptDefaultConfig:28'     'maskRot',  logical( 0 ),...                    % Do not modify
    // 'FeedoptDefaultConfig:29'     'indCart', int32( 0 ), ...                      % Do not modify
    // 'FeedoptDefaultConfig:30'     'indRot',  int32( 0 ),...                       % Do not modify
    // 'FeedoptDefaultConfig:31'     'NumberAxis', int32( 0 ), ...                   % Do not modify
    // 'FeedoptDefaultConfig:32'     'NCart',   int32( 0 ), ...                      % Do not modify
    // 'FeedoptDefaultConfig:33'     'NRot',    int32( 0 ), ...                      % Do not modify
    // 'FeedoptDefaultConfig:34'     'D', 0, ...                                     % Do not modify
    // 'FeedoptDefaultConfig:35'     'coeffD', 1, ...                                % Coefficient
    // between cartésian and rotativ axis 'FeedoptDefaultConfig:36'     'kin_params', reshape( [ 0,
    // 0, 0, 24.8760; 0, 0, 0, 0; 0, -24.8760, 0, 0 ], [], 1 ), ... 'FeedoptDefaultConfig:37'
    // 'kin_type', 'xyzbc', ... 'FeedoptDefaultConfig:38'     'NDiscr', int32( 10 ),...
    // 'FeedoptDefaultConfig:39'     'NBreak', int32( 5 ),...
    // 'FeedoptDefaultConfig:40'     'UseDynamicBreakpoints',false,...       % Use a variable number
    // of breakpoints for different lengths 'FeedoptDefaultConfig:41'
    // 'UseLinearBreakpoints',false,...        % Use a linear distribution of breakpoints (else
    // sinspace) 'FeedoptDefaultConfig:42'     'DynamicBreakpointsDistance', 0.1,...   % Distance
    // between two breakpoints in mm 'FeedoptDefaultConfig:43'     'NHorz', int32( 5 ),...
    // 'FeedoptDefaultConfig:44'     'fmax', 500,...
    // 'FeedoptDefaultConfig:45'     'smax', 75000,...
    // 'FeedoptDefaultConfig:46'     'vmax', [500,500,800,0, 40,50],... %[mm] [rad]
    // 'FeedoptDefaultConfig:47'     'amax', [15000,15000,15000,0, 200,1000],...
    // 'FeedoptDefaultConfig:48'     'jmax', [750000,750000,3000000,0,10000,50000],...
    // 'FeedoptDefaultConfig:49'     'LeeSplineDegree', int32( 4 ),...
    // 'FeedoptDefaultConfig:50'     'SplineDegree',    int32( 3 ),...
    // 'FeedoptDefaultConfig:51'     'CutOff', 0.1,...
    // 'FeedoptDefaultConfig:52'     'LSplit', 3.0,...
    // 'FeedoptDefaultConfig:53'     'LSplitZero', 0.1,...
    // 'FeedoptDefaultConfig:54'     'LThreshold', 5.0,...
    // 'FeedoptDefaultConfig:55'     'CuspThreshold', 0,...
    // 'FeedoptDefaultConfig:56'     'v_0', 0, 'at_0', 0,...
    // 'FeedoptDefaultConfig:57'     'v_1', 0, 'at_1', 0,...
    // 'FeedoptDefaultConfig:58'     'dt', 1e-4, ...
    // 'FeedoptDefaultConfig:59'     'ZeroStartAccLimit', 0.01, ...
    // 'FeedoptDefaultConfig:60'     'ZeroStartJerkLimit', 1E6, ...
    // 'FeedoptDefaultConfig:61'     'ZeroStartVelLimit', 0.5, ...
    // 'FeedoptDefaultConfig:62'     'source', repmat(char(0), [1, 1024]),...
    // 'FeedoptDefaultConfig:63'     'DebugCutZero', false,...
    // 'FeedoptDefaultConfig:64'     'Compressing', struct(...
    // 'FeedoptDefaultConfig:65'     'Skip', false,...
    // 'FeedoptDefaultConfig:66'     'ColTolCosLee',     cosd(tol_col_compress_deg)),...
    // 'FeedoptDefaultConfig:67'     'Smoothing', struct( ...
    // 'FeedoptDefaultConfig:68'     'Skip', false,...
    // 'FeedoptDefaultConfig:69'     'ColTolCosSmooth',  cosd(tol_col_smooth_deg), ...
    // 'FeedoptDefaultConfig:70'     'ColTolSmooth',     1E-5 ),...
    // 'FeedoptDefaultConfig:71'     'GaussLegendreN', GaussLegendreN, ...
    // 'FeedoptDefaultConfig:72'     'GaussLegendreX', GaussLegendreX, ...
    // 'FeedoptDefaultConfig:73'     'GaussLegendreW', GaussLegendreW, ...
    // 'FeedoptDefaultConfig:74'     'opt', LP,...
    // 'FeedoptDefaultConfig:75'     'LogFileName', 'logs/logs');
    t9_Smoothing_ColTolCosSmooth = 10.0;
    coder::b_cosd(&t9_Smoothing_ColTolCosSmooth);
    cfg->indCart.size[0] = 1;
    cfg->indCart.data[0] = 0;
    cfg->indRot.size[0] = 1;
    cfg->indRot.data[0] = 0;
    for (int i{0}; i < 5; i++) {
        cfg->kin_type[i] = b_cv[i];
    }
    for (int i1{0}; i1 < 6; i1++) {
        cfg->vmax[i1] = b_iv[i1];
        cfg->amax[i1] = iv1[i1];
        cfg->jmax[i1] = iv2[i1];
    }
    for (int b_i{0}; b_i < 5; b_i++) {
        cfg->GaussLegendreX[b_i] = GaussLegendreX[b_i];
        cfg->GaussLegendreW[b_i] = GaussLegendreW[b_i];
    }
    cfg->opt.Type[0] = 'L';
    cfg->opt.Type[1] = 'P';
    cfg->opt.EnableFindReasonInfeasibility = true;
    cfg->opt.ACC_RAMP_OVER_WINDOWS = 0.999;
    cfg->opt.VEL_RAMP_OVER_WINDOWS = 0.999;
    cfg->opt.SLACK_PENALTY = 10000.0;
    cfg->opt.USE_LINPROG = false;
    for (int i2{0}; i2 < 9; i2++) {
        cfg->LogFileName[i2] = b_cv1[i2];
    }
    //  % [X,Y,Z,A,B,C]
    //                     % Do not modify
    //                       % Do not modify
    //                        % Do not modify
    //                    % Do not modify
    //                       % Do not modify
    //                                      % Do not modify
    //                                 % Coefficient between cartésian and rotativ axis
    //        % Use a variable number of breakpoints for different lengths
    //         % Use a linear distribution of breakpoints (else sinspace)
    //    % Distance between two breakpoints in mm
    //  %[mm] [rad]
    // 'FeedoptDefaultConfig:77' if ~coder.target( 'MATLAB' )
    // 'FeedoptDefaultConfig:78' coder.varsize( 'cfg.indCart',   StructTypeName.dimInd{ : } );
    // 'FeedoptDefaultConfig:79' coder.varsize( 'cfg.indRot',    StructTypeName.dimInd{ : } );
    // 'FeedoptDefaultConfig:80' coder.varsize( 'cfg.maskTot',   StructTypeName.dimMask{ : } );
    // 'FeedoptDefaultConfig:81' coder.varsize( 'cfg.maskCart',  StructTypeName.dimMask{ : } );
    // 'FeedoptDefaultConfig:82' coder.varsize( 'cfg.maskRot',   StructTypeName.dimMask{ : } );
    // 'FeedoptDefaultConfig:83' coder.varsize( 'cfg.D',         StructTypeName.dimD{ : } );
    // 'FeedoptDefaultConfig:84' coder.varsize( 'cfg.kin_params',StructTypeName.dimKinParams{ : } );
    // 'FeedoptDefaultConfig:85' coder.cstructname( cfg,         StructTypeName.FeedoptCfg );
    // 'FeedoptDefaultConfig:88' cfg = check_values( cfg );
    t10_indCart.set_size(1);
    t10_indCart[0] = 0;
    t10_indRot.set_size(1);
    t10_indRot[0] = 0;
    // 'FeedoptDefaultConfig:93' cfg.maskCart   = and( cfg.maskTot, logical( [ 1, 1, 1, 0, 0, 0 ] )
    // );
    cfg->maskCart.size[0] = 1;
    cfg->maskCart.size[1] = 6;
    // 'FeedoptDefaultConfig:94' cfg.maskRot    = and( cfg.maskTot, logical( [ 0, 0, 0, 1, 1, 1 ] )
    // ); 'FeedoptDefaultConfig:95' cfg.NumberAxis = int32( sum( cfg.maskTot ) );
    for (int i3{0}; i3 < 6; i3++) {
        bool b;
        b = t9_maskTot[i3];
        cfg->maskCart.data[i3] = (b && bv[i3]);
        x_data[i3] = b;
    }
    y = x_data[0];
    // 'FeedoptDefaultConfig:96' cfg.NCart      = int32( sum( cfg.maskCart ) );
    b_y = cfg->maskCart.data[0];
    for (int k{0}; k < 5; k++) {
        y += x_data[k + 1];
        b_y += cfg->maskCart.data[k + 1];
    }
    // 'FeedoptDefaultConfig:97' cfg.NRot       = cfg.NumberAxis - cfg.NCart;
    t10_NRot = y - b_y;
    // 'FeedoptDefaultConfig:98' cfg.D          = ones(cfg.NumberAxis, 1);
    t10_D.set_size(y);
    for (int i4{0}; i4 < y; i4++) {
        t10_D[i4] = 1;
    }
    // 'FeedoptDefaultConfig:100' if( cfg.NCart > 0 )
    if (b_y > 0) {
        int loop_ub;
        int yk;
        // 'FeedoptDefaultConfig:101' cfg.indCart = [ 1 : cfg.NCart ].';
        c_y.set_size(1, b_y);
        c_y[0] = 1;
        yk = 1;
        for (int b_k{2}; b_k <= b_y; b_k++) {
            yk++;
            c_y[b_k - 1] = yk;
        }
        t10_indCart.set_size(c_y.size(1));
        loop_ub = c_y.size(1);
        for (int i6{0}; i6 < loop_ub; i6++) {
            t10_indCart[i6] = c_y[i6];
        }
    }
    // 'FeedoptDefaultConfig:104' if( cfg.NRot > 0 )
    if (t10_NRot > 0) {
        int b_loop_ub;
        int b_yk;
        int e_loop_ub;
        int i8;
        int scalarLB;
        int vectorUB;
        // 'FeedoptDefaultConfig:105' cfg.indRot = [ 1 : cfg.NRot ].' + cfg.NCart;
        c_y.set_size(1, t10_NRot);
        c_y[0] = 1;
        b_yk = 1;
        for (int c_k{2}; c_k <= t10_NRot; c_k++) {
            b_yk++;
            c_y[c_k - 1] = b_yk;
        }
        t10_indRot.set_size(c_y.size(1));
        b_loop_ub = c_y.size(1);
        scalarLB = (c_y.size(1) / 4) << 2;
        vectorUB = scalarLB - 4;
        for (i8 = 0; i8 <= vectorUB; i8 += 4) {
            __m128i r;
            r = _mm_loadu_si128((const __m128i *)&c_y[i8]);
            _mm_storeu_si128((__m128i *)&t10_indRot[i8], _mm_add_epi32(r, _mm_set1_epi32(b_y)));
        }
        for (i8 = scalarLB; i8 < b_loop_ub; i8++) {
            t10_indRot[i8] = c_y[i8] + b_y;
        }
        // 'FeedoptDefaultConfig:106' cfg.D(cfg.indRot) = cfg.coeffD;
        e_loop_ub = t10_indRot.size(0);
        for (int i10{0}; i10 < e_loop_ub; i10++) {
            t10_D[t10_indRot[i10] - 1] = 1;
        }
    }
    cfg->maskTot.size[0] = 1;
    cfg->maskTot.size[1] = 6;
    cfg->maskRot.size[0] = 1;
    cfg->maskRot.size[1] = 6;
    for (int i5{0}; i5 < 6; i5++) {
        bool b1;
        b1 = t9_maskTot[i5];
        cfg->maskTot.data[i5] = b1;
        cfg->maskRot.data[i5] = (b1 && bv1[i5]);
    }
    cfg->indCart.size[0] = t10_indCart.size(0);
    c_loop_ub = t10_indCart.size(0);
    for (int i7{0}; i7 < c_loop_ub; i7++) {
        cfg->indCart.data[i7] = t10_indCart[i7];
    }
    cfg->indRot.size[0] = t10_indRot.size(0);
    d_loop_ub = t10_indRot.size(0);
    for (int i9{0}; i9 < d_loop_ub; i9++) {
        cfg->indRot.data[i9] = t10_indRot[i9];
    }
    cfg->NumberAxis = y;
    cfg->NCart = b_y;
    cfg->NRot = t10_NRot;
    cfg->D.size[0] = t10_D.size(0);
    f_loop_ub = t10_D.size(0);
    for (int i11{0}; i11 < f_loop_ub; i11++) {
        cfg->D.data[i11] = 1.0;
    }
    cfg->coeffD = 1.0;
    cfg->kin_params.size[0] = 12;
    std::copy(&dv[0], &dv[12], &cfg->kin_params.data[0]);
    cfg->NDiscr = 10;
    cfg->NBreak = 5;
    cfg->UseDynamicBreakpoints = false;
    cfg->UseLinearBreakpoints = false;
    cfg->DynamicBreakpointsDistance = 0.1;
    cfg->NHorz = 5;
    cfg->fmax = 9000.0;
    cfg->smax = 75000.0;
    cfg->LeeSplineDegree = 4;
    cfg->SplineDegree = 3;
    cfg->CutOff = 0.1;
    cfg->LSplit = 3.0;
    cfg->LSplitZero = 0.1;
    cfg->LThreshold = 5.0;
    cfg->CuspThreshold = 0.0;
    cfg->v_0 = 0.0;
    cfg->at_0 = 0.0;
    cfg->v_1 = 0.0;
    cfg->at_1 = 0.0;
    cfg->dt = 0.0001;
    cfg->ZeroStartAccLimit = 0.01;
    cfg->ZeroStartJerkLimit = 1.0E+6;
    cfg->ZeroStartVelLimit = 0.5;
    std::memset(&cfg->source[0], 0, 1024U * sizeof(char));
    cfg->DebugCutZero = false;
    cfg->Compressing.Skip = false;
    cfg->Compressing.ColTolCosLee = t9_Smoothing_ColTolCosSmooth;
    cfg->Smoothing.Skip = true;
    cfg->Smoothing.ColTolCosSmooth = t9_Smoothing_ColTolCosSmooth;
    cfg->Smoothing.ColTolSmooth = 1.0E-5;
    cfg->GaussLegendreN = 5.0;
}

} // namespace ocn

//
// File trailer for FeedoptDefaultConfig.cpp
//
// [EOF]
//
