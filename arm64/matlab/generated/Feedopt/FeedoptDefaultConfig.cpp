//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptDefaultConfig.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:02:16
//

// Include Files
#include "FeedoptDefaultConfig.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "setMachineAxisInConfig.h"
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
    static const double dv[12]{0.0, 0.0, 0.0, 0.0, 0.0, -24.876, 0.0, 0.0, 0.0, 24.876, 0.0, 0.0};
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
    static const bool bv[6]{true, true, true, false, true, true};
    b_FeedoptConfig r;
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int loop_ub;
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
    // 'FeedoptDefaultConfig:44'     'fmax', 1000,...
    // 'FeedoptDefaultConfig:45'     'smax', 75000,...
    // 'FeedoptDefaultConfig:46'     'vmax', [500,500,800,0, 40,50],... %[mm] [rad]
    // 'FeedoptDefaultConfig:47'     'amax', [15000,15000,15000,0, 200,1000],...
    // 'FeedoptDefaultConfig:48'     'jmax', [750000,750000,3000000,0,10000,50000],...
    // 'FeedoptDefaultConfig:49'     'LeeSplineDegree', int32( 4 ),...
    // 'FeedoptDefaultConfig:50'     'SplineDegree',    int32( 3 ),...
    // 'FeedoptDefaultConfig:51'     'CutOff', 1E-3,...
    // 'FeedoptDefaultConfig:52'     'LSplit', 1.0,...
    // 'FeedoptDefaultConfig:53'     'LSplitZero', 1E-3,...
    // 'FeedoptDefaultConfig:54'     'LThresholdMax', 5.0,...
    // 'FeedoptDefaultConfig:55'     'LThresholdMin', 1E-3,...
    // 'FeedoptDefaultConfig:56'     'v_0', 0, 'at_0', 0,...
    // 'FeedoptDefaultConfig:57'     'v_1', 0, 'at_1', 0,...
    // 'FeedoptDefaultConfig:58'     'dt', 1e-2, ...
    // 'FeedoptDefaultConfig:59'     'ZeroStartAccLimit', 0.01, ...
    // 'FeedoptDefaultConfig:60'     'ZeroStartJerkLimit', 1E6, ...
    // 'FeedoptDefaultConfig:61'     'ZeroStartVelLimit', 0.5, ...
    // 'FeedoptDefaultConfig:62'     'source', repmat(char(0), [1, 1024]),...
    // 'FeedoptDefaultConfig:63'     'DebugCutZero', false,...
    // 'FeedoptDefaultConfig:64'     'Cusp', struct(...
    // 'FeedoptDefaultConfig:65'     'Skip', false,...
    // 'FeedoptDefaultConfig:66'     'CuspThreshold', 45 ),...
    // 'FeedoptDefaultConfig:67'     'Compressing', struct(...
    // 'FeedoptDefaultConfig:68'     'Skip', false,...
    // 'FeedoptDefaultConfig:69'     'ColTolCosLee',     cosd(tol_col_compress_deg)),...
    // 'FeedoptDefaultConfig:70'     'Smoothing', struct( ...
    // 'FeedoptDefaultConfig:71'     'Skip', false,...
    // 'FeedoptDefaultConfig:72'     'ColTolCosSmooth',  cosd(tol_col_smooth_deg), ...
    // 'FeedoptDefaultConfig:73'     'ColTolSmooth',     1E-5 ),...
    // 'FeedoptDefaultConfig:74'     'GaussLegendreN', GaussLegendreN, ...
    // 'FeedoptDefaultConfig:75'     'GaussLegendreX', GaussLegendreX, ...
    // 'FeedoptDefaultConfig:76'     'GaussLegendreW', GaussLegendreW, ...
    // 'FeedoptDefaultConfig:77'     'opt', LP,...
    // 'FeedoptDefaultConfig:78'     'LogFileName', 'logs/logs');
    cfg->maskCart.size[0] = 1;
    cfg->maskCart.size[1] = 1;
    cfg->maskCart.data[0] = false;
    cfg->maskRot.size[0] = 1;
    cfg->maskRot.size[1] = 1;
    cfg->maskRot.data[0] = false;
    cfg->indCart.size[0] = 1;
    cfg->indCart.data[0] = 0;
    cfg->indRot.size[0] = 1;
    cfg->indRot.data[0] = 0;
    cfg->D.size[0] = 1;
    cfg->D.data[0] = 0.0;
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
    // 'FeedoptDefaultConfig:80' if ~coder.target( 'MATLAB' )
    // 'FeedoptDefaultConfig:81' coder.varsize( 'cfg.indCart',   StructTypeName.dimInd{ : } );
    // 'FeedoptDefaultConfig:82' coder.varsize( 'cfg.indRot',    StructTypeName.dimInd{ : } );
    // 'FeedoptDefaultConfig:83' coder.varsize( 'cfg.maskTot',   StructTypeName.dimMask{ : } );
    // 'FeedoptDefaultConfig:84' coder.varsize( 'cfg.maskCart',  StructTypeName.dimMask{ : } );
    // 'FeedoptDefaultConfig:85' coder.varsize( 'cfg.maskRot',   StructTypeName.dimMask{ : } );
    // 'FeedoptDefaultConfig:86' coder.varsize( 'cfg.D',         StructTypeName.dimD{ : } );
    // 'FeedoptDefaultConfig:87' coder.varsize( 'cfg.kin_params',StructTypeName.dimKinParams{ : } );
    // 'FeedoptDefaultConfig:88' coder.cstructname( cfg,         StructTypeName.FeedoptCfg );
    // 'FeedoptDefaultConfig:91' [ cfg ] = setMachineAxisInConfig( cfg, cfg.maskTot );
    r.maskTot.size[0] = 1;
    r.maskTot.size[1] = 6;
    for (int i{0}; i < 6; i++) {
        r.maskTot.data[i] = bv[i];
    }
    r.maskCart.size[0] = 1;
    r.maskCart.size[1] = 1;
    r.maskCart.data[0] = false;
    r.maskRot.size[0] = 1;
    r.maskRot.size[1] = 1;
    r.maskRot.data[0] = false;
    r.indCart.set_size(1);
    r.indCart[0] = 0;
    r.indRot.set_size(1);
    r.indRot[0] = 0;
    r.NumberAxis = 0;
    r.NCart = 0;
    r.NRot = 0;
    r.D.set_size(1);
    r.D[0] = 0.0;
    r.coeffD = 1.0;
    r.kin_params.size[0] = 12;
    std::copy(&dv[0], &dv[12], &r.kin_params.data[0]);
    for (int i1{0}; i1 < 5; i1++) {
        r.kin_type[i1] = b_cv[i1];
    }
    r.NDiscr = 10;
    r.NBreak = 5;
    r.UseDynamicBreakpoints = false;
    r.UseLinearBreakpoints = false;
    r.DynamicBreakpointsDistance = 0.1;
    r.NHorz = 5;
    r.fmax = 1000.0;
    r.smax = 75000.0;
    for (int i2{0}; i2 < 6; i2++) {
        r.vmax[i2] = iv[i2];
        r.amax[i2] = iv1[i2];
        r.jmax[i2] = iv2[i2];
    }
    r.LeeSplineDegree = 4;
    r.SplineDegree = 3;
    r.CutOff = 0.001;
    r.LSplit = 1.0;
    r.LSplitZero = 0.001;
    r.LThresholdMax = 5.0;
    r.LThresholdMin = 0.001;
    r.v_0 = 0.0;
    r.at_0 = 0.0;
    r.v_1 = 0.0;
    r.at_1 = 0.0;
    r.dt = 0.01;
    r.ZeroStartAccLimit = 0.01;
    r.ZeroStartJerkLimit = 1.0E+6;
    r.ZeroStartVelLimit = 0.5;
    std::memset(&r.source[0], 0, 1024U * sizeof(char));
    r.DebugCutZero = false;
    r.Cusp.Skip = false;
    r.Cusp.CuspThreshold = 45.0;
    r.Compressing.Skip = false;
    r.Compressing.ColTolCosLee = 0.984807753012208;
    r.Smoothing.Skip = false;
    r.Smoothing.ColTolCosSmooth = 0.984807753012208;
    r.Smoothing.ColTolSmooth = 1.0E-5;
    r.GaussLegendreN = 5.0;
    for (int b_i{0}; b_i < 5; b_i++) {
        r.GaussLegendreX[b_i] = GaussLegendreX[b_i];
        r.GaussLegendreW[b_i] = GaussLegendreW[b_i];
    }
    r.opt.Type[0] = 'L';
    r.opt.Type[1] = 'P';
    r.opt.EnableFindReasonInfeasibility = true;
    r.opt.ACC_RAMP_OVER_WINDOWS = 0.999;
    r.opt.VEL_RAMP_OVER_WINDOWS = 0.999;
    r.opt.SLACK_PENALTY = 10000.0;
    r.opt.USE_LINPROG = false;
    for (int i3{0}; i3 < 9; i3++) {
        r.LogFileName[i3] = b_cv1[i3];
    }
    b_setMachineAxisInConfig(&r, bv);
    cfg->maskTot.size[0] = 1;
    cfg->maskTot.size[1] = r.maskTot.size[1];
    loop_ub = r.maskTot.size[1];
    if (0 <= loop_ub - 1) {
        std::copy(&r.maskTot.data[0], &r.maskTot.data[loop_ub], &cfg->maskTot.data[0]);
    }
    cfg->maskCart.size[0] = 1;
    cfg->maskCart.size[1] = r.maskCart.size[1];
    b_loop_ub = r.maskCart.size[1];
    if (0 <= b_loop_ub - 1) {
        std::copy(&r.maskCart.data[0], &r.maskCart.data[b_loop_ub], &cfg->maskCart.data[0]);
    }
    cfg->maskRot.size[0] = 1;
    cfg->maskRot.size[1] = r.maskRot.size[1];
    c_loop_ub = r.maskRot.size[1];
    if (0 <= c_loop_ub - 1) {
        std::copy(&r.maskRot.data[0], &r.maskRot.data[c_loop_ub], &cfg->maskRot.data[0]);
    }
    cfg->indCart.size[0] = r.indCart.size(0);
    d_loop_ub = r.indCart.size(0);
    for (int i4{0}; i4 < d_loop_ub; i4++) {
        cfg->indCart.data[i4] = r.indCart[i4];
    }
    cfg->indRot.size[0] = r.indRot.size(0);
    e_loop_ub = r.indRot.size(0);
    for (int i5{0}; i5 < e_loop_ub; i5++) {
        cfg->indRot.data[i5] = r.indRot[i5];
    }
    cfg->NumberAxis = r.NumberAxis;
    cfg->NCart = r.NCart;
    cfg->NRot = r.NRot;
    cfg->D.size[0] = r.D.size(0);
    f_loop_ub = r.D.size(0);
    for (int i6{0}; i6 < f_loop_ub; i6++) {
        cfg->D.data[i6] = r.D[i6];
    }
    cfg->coeffD = r.coeffD;
    cfg->kin_params.size[0] = r.kin_params.size[0];
    g_loop_ub = r.kin_params.size[0];
    if (0 <= g_loop_ub - 1) {
        std::copy(&r.kin_params.data[0], &r.kin_params.data[g_loop_ub], &cfg->kin_params.data[0]);
    }
    for (int i7{0}; i7 < 5; i7++) {
        cfg->kin_type[i7] = r.kin_type[i7];
    }
    cfg->NDiscr = r.NDiscr;
    cfg->NBreak = r.NBreak;
    cfg->UseDynamicBreakpoints = r.UseDynamicBreakpoints;
    cfg->UseLinearBreakpoints = r.UseLinearBreakpoints;
    cfg->DynamicBreakpointsDistance = r.DynamicBreakpointsDistance;
    cfg->NHorz = r.NHorz;
    cfg->fmax = r.fmax;
    cfg->smax = r.smax;
    for (int i8{0}; i8 < 6; i8++) {
        cfg->vmax[i8] = r.vmax[i8];
        cfg->amax[i8] = r.amax[i8];
        cfg->jmax[i8] = r.jmax[i8];
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
    cfg->ZeroStartAccLimit = r.ZeroStartAccLimit;
    cfg->ZeroStartJerkLimit = r.ZeroStartJerkLimit;
    cfg->ZeroStartVelLimit = r.ZeroStartVelLimit;
    std::copy(&r.source[0], &r.source[1024], &cfg->source[0]);
    cfg->DebugCutZero = r.DebugCutZero;
    cfg->Cusp = r.Cusp;
    cfg->Compressing = r.Compressing;
    cfg->Smoothing = r.Smoothing;
    cfg->GaussLegendreN = r.GaussLegendreN;
    for (int c_i{0}; c_i < 5; c_i++) {
        cfg->GaussLegendreX[c_i] = r.GaussLegendreX[c_i];
        cfg->GaussLegendreW[c_i] = r.GaussLegendreW[c_i];
    }
    cfg->opt = r.opt;
    for (int i9{0}; i9 < 9; i9++) {
        cfg->LogFileName[i9] = r.LogFileName[i9];
    }
}

} // namespace ocn

//
// File trailer for FeedoptDefaultConfig.cpp
//
// [EOF]
//
