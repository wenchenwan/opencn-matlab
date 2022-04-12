//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptDefaultConfig.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 12-Apr-2022 10:51:01
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
    static const double dv[5]{0.90617984593866385, 0.538469310105683, 0.0, -0.538469310105683,
                              -0.90617984593866385};
    static const char b_cv[9]{'l', 'o', 'g', 's', '/', 'l', 'o', 'g', 's'};
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'FeedoptDefaultConfig:3' coder.inline("never");
    // 'FeedoptDefaultConfig:5' tol_col_compress_deg = 1e-2;
    // 'FeedoptDefaultConfig:6' tol_col_smooth_deg = 1e-2;
    //  Computation of Gauss-Legendre knots and weights for numerical integration
    // 'FeedoptDefaultConfig:9' GaussLegendreN = 5;
    //  number of evaluation points
    // 'FeedoptDefaultConfig:10' [GaussLegendreX, GaussLegendreW] = lgwt(GaussLegendreN, -1, 1);
    //  normalized to integration interval [-1, 1]
    // 'FeedoptDefaultConfig:11' GaussLegendreX = flipud(GaussLegendreX);
    for (int i{0}; i < 5; i++) {
        cfg->GaussLegendreX[i] = dv[i];
    }
    double xtmp;
    // 'FeedoptDefaultConfig:13' LP = struct(...
    // 'FeedoptDefaultConfig:14'             'Type', 'LP', ...
    // 'FeedoptDefaultConfig:15'             'EnableFindReasonInfeasibility', true,...
    // 'FeedoptDefaultConfig:16'             'ACC_RAMP_OVER_WINDOWS', 1.0 - 1E-3,...
    // 'FeedoptDefaultConfig:17'             'VEL_RAMP_OVER_WINDOWS', 1.0 - 1E-3,...
    // 'FeedoptDefaultConfig:18'             'USE_SLACK_ON_JERK', false ,...
    // 'FeedoptDefaultConfig:19'             'SLACK_PENALTY', 100, ...
    // 'FeedoptDefaultConfig:20'             'USE_LINPROG', false);
    xtmp = cfg->GaussLegendreX[0];
    cfg->GaussLegendreX[0] = cfg->GaussLegendreX[4];
    cfg->GaussLegendreX[4] = xtmp;
    cfg->opt.Type[0] = 'L';
    xtmp = cfg->GaussLegendreX[1];
    cfg->GaussLegendreX[1] = cfg->GaussLegendreX[3];
    cfg->GaussLegendreX[3] = xtmp;
    cfg->opt.Type[1] = 'P';
    cfg->opt.EnableFindReasonInfeasibility = true;
    cfg->opt.ACC_RAMP_OVER_WINDOWS = 0.999;
    cfg->opt.VEL_RAMP_OVER_WINDOWS = 0.999;
    cfg->opt.USE_SLACK_ON_JERK = false;
    cfg->opt.SLACK_PENALTY = 100.0;
    cfg->opt.USE_LINPROG = false;
    // 'FeedoptDefaultConfig:22' cfg = struct(...
    // 'FeedoptDefaultConfig:23'         'NumberAxis', int32(3),...
    // 'FeedoptDefaultConfig:24' 		'NDiscr', int32( 20 ),...
    // 'FeedoptDefaultConfig:25' 		'NBreak', int32( 10 ),...
    // 'FeedoptDefaultConfig:26'         'UseDynamicBreakpoints',false,... % Use a variable number
    // of breakpoints for different lengths 'FeedoptDefaultConfig:27'
    // 'UseLinearBreakpoints',false,...   % Use a linear distribution of breakpoints (else sinspace)
    // 'FeedoptDefaultConfig:28'         'DynamicBreakpointsDistance', 0.1,... % Distance between
    // two breakpoints in mm 'FeedoptDefaultConfig:29' 		'NHorz', int32(5),...
    // 'FeedoptDefaultConfig:30' 		'vmax', 150,...
    // 'FeedoptDefaultConfig:31' 		'amax', [20000,20000,20000],...
    // 'FeedoptDefaultConfig:32' 		'jmax', [1500000,1500000,1500000] / 10,...
    // 'FeedoptDefaultConfig:33' 		'LeeSplineDegree', int32( 4 ),...
    // 'FeedoptDefaultConfig:34' 		'SplineDegree',    int32( 3 ),...
    // 'FeedoptDefaultConfig:35'         'CutOff', 0.1,...
    // 'FeedoptDefaultConfig:36'         'LSplit', 3.0,...
    // 'FeedoptDefaultConfig:37'         'LThreshold', 0.3,...
    // 'FeedoptDefaultConfig:38'         'CuspThreshold', 45,...
    // 'FeedoptDefaultConfig:39'         'v_0', 0.1, 'at_0', 0,...
    // 'FeedoptDefaultConfig:40'         'v_1', 0.1, 'at_1', 0,...
    // 'FeedoptDefaultConfig:41'         'dt', 1e-4, ...
    // 'FeedoptDefaultConfig:42'         'ZeroStartAccLimit', 0.01, ...
    // 'FeedoptDefaultConfig:43'         'ZeroStartJerkLimit', 1, ...
    // 'FeedoptDefaultConfig:44'         'ZeroStartVelLimit', 0.5, ...
    // 'FeedoptDefaultConfig:45'         'source', repmat(char(0), [1, 1024]),...
    // 'FeedoptDefaultConfig:46'         'DebugCutZero', false,...
    // 'FeedoptDefaultConfig:47'         'Compressing', struct(...
    // 'FeedoptDefaultConfig:48'             'Skip', false,...
    // 'FeedoptDefaultConfig:49'             'ColTolCos', cosd(tol_col_compress_deg)),...
    // 'FeedoptDefaultConfig:50'         'ColTolCos', cosd(tol_col_smooth_deg), ...
    // 'FeedoptDefaultConfig:51'         'GaussLegendreN', GaussLegendreN, ...
    // 'FeedoptDefaultConfig:52'         'GaussLegendreX', GaussLegendreX, ...
    // 'FeedoptDefaultConfig:53'         'GaussLegendreW', GaussLegendreW, ...
    // 'FeedoptDefaultConfig:54'         'opt', LP,...
    // 'FeedoptDefaultConfig:55'         'LogFileName', 'logs/logs');
    cfg->NumberAxis = 3;
    cfg->NDiscr = 20;
    cfg->NBreak = 10;
    cfg->UseDynamicBreakpoints = false;
    cfg->UseLinearBreakpoints = false;
    cfg->DynamicBreakpointsDistance = 0.1;
    cfg->NHorz = 5;
    cfg->vmax = 150.0;
    cfg->amax[0] = 20000.0;
    cfg->jmax[0] = 150000.0;
    cfg->amax[1] = 20000.0;
    cfg->jmax[1] = 150000.0;
    cfg->amax[2] = 20000.0;
    cfg->jmax[2] = 150000.0;
    cfg->LeeSplineDegree = 4;
    cfg->SplineDegree = 3;
    cfg->CutOff = 0.1;
    cfg->LSplit = 3.0;
    cfg->LThreshold = 0.3;
    cfg->CuspThreshold = 45.0;
    cfg->v_0 = 0.1;
    cfg->at_0 = 0.0;
    cfg->v_1 = 0.1;
    cfg->at_1 = 0.0;
    cfg->dt = 0.0001;
    cfg->ZeroStartAccLimit = 0.01;
    cfg->ZeroStartJerkLimit = 1.0;
    cfg->ZeroStartVelLimit = 0.5;
    std::memset(&cfg->source[0], 0, 1024U * sizeof(char));
    cfg->DebugCutZero = false;
    cfg->Compressing.Skip = false;
    cfg->Compressing.ColTolCos = 0.9999999847691291;
    cfg->ColTolCos = 0.9999999847691291;
    cfg->GaussLegendreN = 5.0;
    for (int b_i{0}; b_i < 5; b_i++) {
        cfg->GaussLegendreW[b_i] = GaussLegendreW[b_i];
    }
    for (int c_i{0}; c_i < 9; c_i++) {
        cfg->LogFileName[c_i] = b_cv[c_i];
    }
    //  % Use a variable number of breakpoints for different lengths
    //    % Use a linear distribution of breakpoints (else sinspace)
    //  % Distance between two breakpoints in mm
    // 'FeedoptDefaultConfig:57' coder.cstructname(cfg, 'FeedoptConfig');
}

} // namespace ocn

//
// File trailer for FeedoptDefaultConfig.cpp
//
// [EOF]
//
