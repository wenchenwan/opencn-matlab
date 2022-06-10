//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptDefaultConfig.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:28:52
//

// Include Files
#include "FeedoptDefaultConfig.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include <cstring>

// Function Definitions
//
// function cfg = FeedoptDefaultConfig()
//
// Arguments    : FeedoptConfig *cfg
// Return Type  : void
//
namespace ocn {
void FeedoptDefaultConfig(FeedoptConfig *cfg)
{
    static const double GaussLegendreW[5]{0.23692688505618911, 0.47862867049936625,
                                          0.56888888888888889, 0.47862867049936625,
                                          0.23692688505618911};
    static const double GaussLegendreX[5]{-0.90617984593866385, -0.538469310105683, 0.0,
                                          0.538469310105683, 0.90617984593866385};
    static const int iv1[6]{150000, 150000, 150000, 0, 150000, 150000};
    static const short b_iv[6]{20000, 20000, 20000, 0, 20000, 20000};
    static const char b_cv[9]{'l', 'o', 'g', 's', '/', 'l', 'o', 'g', 's'};
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
    // 'FeedoptDefaultConfig:18'     'SLACK_PENALTY', 100, ...
    // 'FeedoptDefaultConfig:19'     'USE_LINPROG', false);
    // 'FeedoptDefaultConfig:21' if( ~coder.target('MATLAB') )
    // 'FeedoptDefaultConfig:22' coder.cstructname( LP,          StructTypeName.LPCfg );
    // 'FeedoptDefaultConfig:25' cfg = struct(...
    // 'FeedoptDefaultConfig:26'     'NumberAxis', int32( 3 ), ...
    // 'FeedoptDefaultConfig:27'     'NCart', int32( 3 ), ...
    // 'FeedoptDefaultConfig:28'     'NRot', int32( 0 ), ...
    // 'FeedoptDefaultConfig:29'     'indCart', int32( [ 1, 2, 3 ]' ), ...
    // 'FeedoptDefaultConfig:30'     'indRot', int32( [ 0 ]' ),...
    // 'FeedoptDefaultConfig:31'     'indTot', int32( [ 0 ] ),...
    // 'FeedoptDefaultConfig:32'     'NDiscr', int32( 20 ),...
    // 'FeedoptDefaultConfig:33'     'NBreak', int32( 10 ),...
    // 'FeedoptDefaultConfig:34'     'UseDynamicBreakpoints',false,...       % Use a variable number
    // of breakpoints for different lengths 'FeedoptDefaultConfig:35'
    // 'UseLinearBreakpoints',false,...        % Use a linear distribution of breakpoints (else
    // sinspace) 'FeedoptDefaultConfig:36'     'DynamicBreakpointsDistance', 0.1,...   % Distance
    // between two breakpoints in mm 'FeedoptDefaultConfig:37'     'NHorz', int32( 5 ),...
    // 'FeedoptDefaultConfig:38'     'vmax', 150,...
    // 'FeedoptDefaultConfig:39'     'amax', [20000,20000,20000,0, 20000,20000],...
    // 'FeedoptDefaultConfig:40'     'jmax', [1500000,1500000,1500000,0,1500000,1500000] / 10,...
    // 'FeedoptDefaultConfig:41'     'LeeSplineDegree', int32( 4 ),...
    // 'FeedoptDefaultConfig:42'     'SplineDegree',    int32( 3 ),...
    // 'FeedoptDefaultConfig:43'     'CutOff', 0.1,...
    // 'FeedoptDefaultConfig:44'     'LSplit', 3.0,...
    // 'FeedoptDefaultConfig:45'     'LSplitZero', 0.1,...
    // 'FeedoptDefaultConfig:46'     'LThreshold', 0.3,...
    // 'FeedoptDefaultConfig:47'     'CuspThreshold', 45,...
    // 'FeedoptDefaultConfig:48'     'v_0', 0, 'at_0', 0,...
    // 'FeedoptDefaultConfig:49'     'v_1', 0, 'at_1', 0,...
    // 'FeedoptDefaultConfig:50'     'dt', 1e-4, ...
    // 'FeedoptDefaultConfig:51'     'ZeroStartAccLimit', 0.01, ...
    // 'FeedoptDefaultConfig:52'     'ZeroStartJerkLimit', 1, ...
    // 'FeedoptDefaultConfig:53'     'ZeroStartVelLimit', 0.5, ...
    // 'FeedoptDefaultConfig:54'     'source', repmat(char(0), [1, 1024]),...
    // 'FeedoptDefaultConfig:55'     'DebugCutZero', false,...
    // 'FeedoptDefaultConfig:56'     'Compressing', struct(...
    // 'FeedoptDefaultConfig:57'     'Skip', false,...
    // 'FeedoptDefaultConfig:58'     'ColTolCosLee',     cosd(tol_col_compress_deg)),...
    // 'FeedoptDefaultConfig:59'     'ColTolCosSmooth',  cosd(tol_col_smooth_deg), ...
    // 'FeedoptDefaultConfig:60'     'GaussLegendreN', GaussLegendreN, ...
    // 'FeedoptDefaultConfig:61'     'GaussLegendreX', GaussLegendreX, ...
    // 'FeedoptDefaultConfig:62'     'GaussLegendreW', GaussLegendreW, ...
    // 'FeedoptDefaultConfig:63'     'opt', LP,...
    // 'FeedoptDefaultConfig:64'     'LogFileName', 'logs/logs');
    cfg->indCart.size[0] = 3;
    cfg->indCart.data[0] = 1;
    cfg->indCart.data[1] = 2;
    cfg->indCart.data[2] = 3;
    cfg->indRot.size[0] = 1;
    cfg->indRot.data[0] = 0;
    cfg->NDiscr = 20;
    cfg->NBreak = 10;
    cfg->UseDynamicBreakpoints = false;
    cfg->UseLinearBreakpoints = false;
    cfg->DynamicBreakpointsDistance = 0.1;
    cfg->NHorz = 5;
    cfg->vmax = 150.0;
    for (int i{0}; i < 6; i++) {
        cfg->amax[i] = b_iv[i];
        cfg->jmax[i] = iv1[i];
    }
    cfg->LeeSplineDegree = 4;
    cfg->SplineDegree = 3;
    cfg->CutOff = 0.1;
    cfg->LSplit = 3.0;
    cfg->LSplitZero = 0.1;
    cfg->LThreshold = 0.3;
    cfg->CuspThreshold = 45.0;
    cfg->v_0 = 0.0;
    cfg->at_0 = 0.0;
    cfg->v_1 = 0.0;
    cfg->at_1 = 0.0;
    cfg->dt = 0.0001;
    cfg->ZeroStartAccLimit = 0.01;
    cfg->ZeroStartJerkLimit = 1.0;
    cfg->ZeroStartVelLimit = 0.5;
    std::memset(&cfg->source[0], 0, 1024U * sizeof(char));
    cfg->DebugCutZero = false;
    cfg->Compressing.Skip = false;
    cfg->Compressing.ColTolCosLee = 0.984807753012208;
    cfg->ColTolCosSmooth = 0.984807753012208;
    cfg->GaussLegendreN = 5.0;
    for (int b_i{0}; b_i < 5; b_i++) {
        cfg->GaussLegendreX[b_i] = GaussLegendreX[b_i];
        cfg->GaussLegendreW[b_i] = GaussLegendreW[b_i];
    }
    cfg->opt.Type[0] = 'L';
    cfg->opt.Type[1] = 'P';
    cfg->opt.EnableFindReasonInfeasibility = true;
    cfg->opt.ACC_RAMP_OVER_WINDOWS = 0.999;
    cfg->opt.VEL_RAMP_OVER_WINDOWS = 0.999;
    cfg->opt.SLACK_PENALTY = 100.0;
    cfg->opt.USE_LINPROG = false;
    for (int i1{0}; i1 < 9; i1++) {
        cfg->LogFileName[i1] = b_cv[i1];
    }
    //        % Use a variable number of breakpoints for different lengths
    //         % Use a linear distribution of breakpoints (else sinspace)
    //    % Distance between two breakpoints in mm
    // 'FeedoptDefaultConfig:66' if ~coder.target( 'MATLAB' )
    // 'FeedoptDefaultConfig:67' coder.varsize( 'cfg.indCart',   StructTypeName.dimInd{ : } );
    // 'FeedoptDefaultConfig:68' coder.varsize( 'cfg.indRot',    StructTypeName.dimInd{ : } );
    // 'FeedoptDefaultConfig:69' coder.varsize( 'cfg.indTot',    StructTypeName.dimIndTot{ : } );
    // 'FeedoptDefaultConfig:70' coder.cstructname( cfg,         StructTypeName.FeedoptCfg );
    // 'FeedoptDefaultConfig:73' cfg = check_values( cfg );
    //  Define index
    // 'FeedoptDefaultConfig:79' if( cfg.NCart == 0 )
    // 'FeedoptDefaultConfig:81' elseif( cfg.NRot == 0 )
    //  Only cartesian
    // 'FeedoptDefaultConfig:82' cfg.indTot = cfg.indCart;
    cfg->indTot.size[0] = 3;
    cfg->indTot.data[0] = 1;
    cfg->indTot.data[1] = 2;
    cfg->indTot.data[2] = 3;
    // 'FeedoptDefaultConfig:87' cfg.NumberAxis  = int32( length( cfg.indTot ) );
    cfg->NumberAxis = 3;
    // 'FeedoptDefaultConfig:88' cfg.NRot        = int32( length( cfg.indRot ) );
    cfg->NRot = 1;
    // 'FeedoptDefaultConfig:89' cfg.NCart       = int32( length( cfg.indCart ) );
    cfg->NCart = 3;
}

} // namespace ocn

//
// File trailer for FeedoptDefaultConfig.cpp
//
// [EOF]
//
