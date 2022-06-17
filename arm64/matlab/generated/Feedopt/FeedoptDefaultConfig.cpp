//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptDefaultConfig.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

// Include Files
#include "FeedoptDefaultConfig.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "string1.h"
#include "coder_array.h"
#include <algorithm>
#include <cstring>

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
    static const double dv[12]{0.0, 0.0, 0.0, 0.0,    0.0,    -82.377,
                               0.0, 0.0, 0.0, 24.876, 57.501, 0.0};
    static const double GaussLegendreW[5]{0.23692688505618911, 0.47862867049936625,
                                          0.56888888888888889, 0.47862867049936625,
                                          0.23692688505618911};
    static const double GaussLegendreX[5]{-0.90617984593866385, -0.538469310105683, 0.0,
                                          0.538469310105683, 0.90617984593866385};
    static const int iv2[6]{750000, 750000, 3000000, 0, 10000, 50000};
    static const short iv[6]{500, 500, 800, 0, 40, 50};
    static const short iv1[6]{15000, 15000, 15000, 0, 200, 1000};
    static const char b_cv1[9]{'l', 'o', 'g', 's', '/', 'l', 'o', 'g', 's'};
    static const char b_cv[5]{'x', 'y', 'z', 'b', 'c'};
    static const bool bv[6]{true, true, true, false, false, false};
    static const bool bv1[6]{false, false, false, true, true, true};
    static const bool t3_maskTot[6]{true, true, true, false, true, true};
    ::coder::array<int, 2U> c_y;
    ::coder::array<int, 1U> t4_indCart;
    ::coder::array<int, 1U> t4_indRot;
    ::coder::array<bool, 2U> t4_maskCart;
    ::coder::array<bool, 2U> x;
    int b_y;
    int c_loop_ub;
    int d_loop_ub;
    int t4_NRot;
    int y;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'FeedoptDefaultConfig:3' coder.inline("never");
    // 'FeedoptDefaultConfig:5' tol_col_compress_deg    = 10;
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
    // 'FeedoptDefaultConfig:34'     'kin_params', reshape( [ 0, 0, 0, 24.8760; 0, 0, 0, 57.5010; 0,
    // -82.3770, 0, 0 ], [], 1 ), ... 'FeedoptDefaultConfig:35'     'kin_type', "xyzbc", ...
    // 'FeedoptDefaultConfig:36'     'NDiscr', int32( 10 ),...
    // 'FeedoptDefaultConfig:37'     'NBreak', int32( 5 ),...
    // 'FeedoptDefaultConfig:38'     'UseDynamicBreakpoints',false,...       % Use a variable number
    // of breakpoints for different lengths 'FeedoptDefaultConfig:39'
    // 'UseLinearBreakpoints',false,...        % Use a linear distribution of breakpoints (else
    // sinspace) 'FeedoptDefaultConfig:40'     'DynamicBreakpointsDistance', 0.1,...   % Distance
    // between two breakpoints in mm 'FeedoptDefaultConfig:41'     'NHorz', int32( 5 ),...
    // 'FeedoptDefaultConfig:42'     'fmax', 150,...
    // 'FeedoptDefaultConfig:43'     'smax', 75000,...
    // 'FeedoptDefaultConfig:44'     'vmax', [500,500,800,0, 40,50],... %[mm] [rad]
    // 'FeedoptDefaultConfig:45'     'amax', [15000,15000,15000,0, 200,1000],...
    // 'FeedoptDefaultConfig:46'     'jmax', [750000,750000,3000000,0,10000,50000],...
    // 'FeedoptDefaultConfig:47'     'LeeSplineDegree', int32( 4 ),...
    // 'FeedoptDefaultConfig:48'     'SplineDegree',    int32( 3 ),...
    // 'FeedoptDefaultConfig:49'     'CutOff', 0.1,...
    // 'FeedoptDefaultConfig:50'     'LSplit', 3.0,...
    // 'FeedoptDefaultConfig:51'     'LSplitZero', 0.1,...
    // 'FeedoptDefaultConfig:52'     'LThreshold', 5,...
    // 'FeedoptDefaultConfig:53'     'CuspThreshold', 45,...
    // 'FeedoptDefaultConfig:54'     'v_0', 0, 'at_0', 0,...
    // 'FeedoptDefaultConfig:55'     'v_1', 0, 'at_1', 0,...
    // 'FeedoptDefaultConfig:56'     'dt', 1e-3, ...
    // 'FeedoptDefaultConfig:57'     'ZeroStartAccLimit', 0.01, ...
    // 'FeedoptDefaultConfig:58'     'ZeroStartJerkLimit', 1E6, ...
    // 'FeedoptDefaultConfig:59'     'ZeroStartVelLimit', 0.5, ...
    // 'FeedoptDefaultConfig:60'     'source', repmat(char(0), [1, 1024]),...
    // 'FeedoptDefaultConfig:61'     'DebugCutZero', false,...
    // 'FeedoptDefaultConfig:62'     'Compressing', struct(...
    // 'FeedoptDefaultConfig:63'     'Skip', false,...
    // 'FeedoptDefaultConfig:64'     'ColTolCosLee',     cosd(tol_col_compress_deg)),...
    // 'FeedoptDefaultConfig:65'     'ColTolCosSmooth',  cosd(tol_col_smooth_deg), ...
    // 'FeedoptDefaultConfig:66'     'GaussLegendreN', GaussLegendreN, ...
    // 'FeedoptDefaultConfig:67'     'GaussLegendreX', GaussLegendreX, ...
    // 'FeedoptDefaultConfig:68'     'GaussLegendreW', GaussLegendreW, ...
    // 'FeedoptDefaultConfig:69'     'opt', LP,...
    // 'FeedoptDefaultConfig:70'     'LogFileName', 'logs/logs');
    for (int i{0}; i < 5; i++) {
        cfg->kin_type.Value[i] = b_cv[i];
    }
    cfg->indCart.size[0] = 1;
    cfg->indCart.data[0] = 0;
    cfg->indRot.size[0] = 1;
    cfg->indRot.data[0] = 0;
    for (int i1{0}; i1 < 6; i1++) {
        cfg->vmax[i1] = iv[i1];
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
    //        % Use a variable number of breakpoints for different lengths
    //         % Use a linear distribution of breakpoints (else sinspace)
    //    % Distance between two breakpoints in mm
    //  %[mm] [rad]
    // 'FeedoptDefaultConfig:72' if ~coder.target( 'MATLAB' )
    // 'FeedoptDefaultConfig:73' coder.varsize( 'cfg.indCart',   StructTypeName.dimInd{ : } );
    // 'FeedoptDefaultConfig:74' coder.varsize( 'cfg.indRot',    StructTypeName.dimInd{ : } );
    // 'FeedoptDefaultConfig:75' coder.varsize( 'cfg.maskTot',   StructTypeName.dimMask{ : } );
    // 'FeedoptDefaultConfig:76' coder.varsize( 'cfg.maskCart',  StructTypeName.dimMask{ : } );
    // 'FeedoptDefaultConfig:77' coder.varsize( 'cfg.maskRot',   StructTypeName.dimMask{ : } );
    // 'FeedoptDefaultConfig:78' coder.varsize( 'cfg.kin_params',StructTypeName.dimKinParams{ : } );
    // 'FeedoptDefaultConfig:79' coder.cstructname( cfg,         StructTypeName.FeedoptCfg );
    // 'FeedoptDefaultConfig:82' cfg = check_values( cfg );
    t4_indCart.set_size(1);
    t4_indCart[0] = 0;
    t4_indRot.set_size(1);
    t4_indRot[0] = 0;
    // 'FeedoptDefaultConfig:86' cfg.maskCart   = and( cfg.maskTot, logical( [ 1, 1, 1, 0, 0, 0 ] )
    // );
    t4_maskCart.set_size(1, 6);
    // 'FeedoptDefaultConfig:87' cfg.maskRot    = and( cfg.maskTot, logical( [ 0, 0, 0, 1, 1, 1 ] )
    // ); 'FeedoptDefaultConfig:88' cfg.NumberAxis = int32( sum( cfg.maskTot ) );
    x.set_size(1, 6);
    for (int i3{0}; i3 < 6; i3++) {
        bool b;
        b = t3_maskTot[i3];
        t4_maskCart[i3] = (b && bv[i3]);
        x[i3] = b;
    }
    y = x[0];
    // 'FeedoptDefaultConfig:89' cfg.NCart      = int32( sum( cfg.maskCart ) );
    b_y = t4_maskCart[0];
    for (int k{0}; k < 5; k++) {
        y += x[k + 1];
        b_y += t4_maskCart[k + 1];
    }
    // 'FeedoptDefaultConfig:90' cfg.NRot       = cfg.NumberAxis - cfg.NCart;
    t4_NRot = y - b_y;
    // 'FeedoptDefaultConfig:92' if( cfg.NCart > 0 )
    if (b_y > 0) {
        int loop_ub;
        int yk;
        // 'FeedoptDefaultConfig:93' cfg.indCart = [ 1 : cfg.NCart ].';
        c_y.set_size(1, b_y);
        c_y[0] = 1;
        yk = 1;
        for (int b_k{2}; b_k <= b_y; b_k++) {
            yk++;
            c_y[b_k - 1] = yk;
        }
        t4_indCart.set_size(c_y.size(1));
        loop_ub = c_y.size(1);
        for (int i4{0}; i4 < loop_ub; i4++) {
            t4_indCart[i4] = c_y[i4];
        }
    }
    // 'FeedoptDefaultConfig:96' if( cfg.NRot > 0 )
    if (t4_NRot > 0) {
        int b_loop_ub;
        int b_yk;
        // 'FeedoptDefaultConfig:97' cfg.indRot = [ 1 : cfg.NRot ].' + cfg.NCart;
        c_y.set_size(1, t4_NRot);
        c_y[0] = 1;
        b_yk = 1;
        for (int c_k{2}; c_k <= t4_NRot; c_k++) {
            b_yk++;
            c_y[c_k - 1] = b_yk;
        }
        t4_indRot.set_size(c_y.size(1));
        b_loop_ub = c_y.size(1);
        for (int i6{0}; i6 < b_loop_ub; i6++) {
            t4_indRot[i6] = c_y[i6] + b_y;
        }
    }
    cfg->maskTot.size[0] = 1;
    cfg->maskTot.size[1] = 6;
    cfg->maskCart.size[0] = 1;
    cfg->maskCart.size[1] = 6;
    cfg->maskRot.size[0] = 1;
    cfg->maskRot.size[1] = 6;
    for (int i5{0}; i5 < 6; i5++) {
        bool b1;
        b1 = t3_maskTot[i5];
        cfg->maskTot.data[i5] = b1;
        cfg->maskCart.data[i5] = t4_maskCart[i5];
        cfg->maskRot.data[i5] = (b1 && bv1[i5]);
    }
    cfg->indCart.size[0] = t4_indCart.size(0);
    c_loop_ub = t4_indCart.size(0);
    for (int i7{0}; i7 < c_loop_ub; i7++) {
        cfg->indCart.data[i7] = t4_indCart[i7];
    }
    cfg->indRot.size[0] = t4_indRot.size(0);
    d_loop_ub = t4_indRot.size(0);
    for (int i8{0}; i8 < d_loop_ub; i8++) {
        cfg->indRot.data[i8] = t4_indRot[i8];
    }
    cfg->NumberAxis = y;
    cfg->NCart = b_y;
    cfg->NRot = t4_NRot;
    cfg->kin_params.size[0] = 12;
    std::copy(&dv[0], &dv[12], &cfg->kin_params.data[0]);
    cfg->NDiscr = 10;
    cfg->NBreak = 5;
    cfg->UseDynamicBreakpoints = false;
    cfg->UseLinearBreakpoints = false;
    cfg->DynamicBreakpointsDistance = 0.1;
    cfg->NHorz = 5;
    cfg->fmax = 150.0;
    cfg->smax = 75000.0;
    cfg->LeeSplineDegree = 4;
    cfg->SplineDegree = 3;
    cfg->CutOff = 0.1;
    cfg->LSplit = 3.0;
    cfg->LSplitZero = 0.1;
    cfg->LThreshold = 5.0;
    cfg->CuspThreshold = 45.0;
    cfg->v_0 = 0.0;
    cfg->at_0 = 0.0;
    cfg->v_1 = 0.0;
    cfg->at_1 = 0.0;
    cfg->dt = 0.001;
    cfg->ZeroStartAccLimit = 0.01;
    cfg->ZeroStartJerkLimit = 1.0E+6;
    cfg->ZeroStartVelLimit = 0.5;
    std::memset(&cfg->source[0], 0, 1024U * sizeof(char));
    cfg->DebugCutZero = false;
    cfg->Compressing.Skip = false;
    cfg->Compressing.ColTolCosLee = 0.984807753012208;
    cfg->ColTolCosSmooth = 0.984807753012208;
    cfg->GaussLegendreN = 5.0;
}

} // namespace ocn

//
// File trailer for FeedoptDefaultConfig.cpp
//
// [EOF]
//
