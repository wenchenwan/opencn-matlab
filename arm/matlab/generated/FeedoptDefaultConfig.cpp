//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptDefaultConfig.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Feb-2022 15:00:32
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
    xtmp = cfg->GaussLegendreX[0];
    cfg->GaussLegendreX[0] = cfg->GaussLegendreX[4];
    cfg->GaussLegendreX[4] = xtmp;
    xtmp = cfg->GaussLegendreX[1];
    cfg->GaussLegendreX[1] = cfg->GaussLegendreX[3];
    cfg->GaussLegendreX[3] = xtmp;
    // 'FeedoptDefaultConfig:13' cfg = struct(...
    // 'FeedoptDefaultConfig:14' 		'NDiscr', int32(20),...
    // 'FeedoptDefaultConfig:15' 		'NBreak', int32(10),...
    // 'FeedoptDefaultConfig:16'         'UseDynamicBreakpoints',false,... % Use a variable number
    // of breakpoints for different lengths 'FeedoptDefaultConfig:17'
    // 'UseLinearBreakpoints',false,...   % Use a linear distribution of breakpoints (else sinspace)
    // 'FeedoptDefaultConfig:18'         'DynamicBreakpointsDistance', 0.1,... % Distance between
    // two breakpoints in mm 'FeedoptDefaultConfig:19' 		'NHorz', int32(5),...
    // 'FeedoptDefaultConfig:20' 		'vmax', 150,...
    // 'FeedoptDefaultConfig:21' 		'amax', [20000,20000,20000],...
    // 'FeedoptDefaultConfig:22' 		'jmax', [1500000,1500000,1500000],...
    // 'FeedoptDefaultConfig:23' 		'SplineDegree', int32(4),...
    // 'FeedoptDefaultConfig:24'         'CutOff', 0.1,...
    // 'FeedoptDefaultConfig:25'         'LSplit', 3.0,...
    // 'FeedoptDefaultConfig:26'         'LThreshold', 0.3,...
    // 'FeedoptDefaultConfig:27'         'CuspThreshold', 45,...
    // 'FeedoptDefaultConfig:28'         'v_0', 0.1, 'at_0', 0,...
    // 'FeedoptDefaultConfig:29'         'v_1', 0.1, 'at_1', 0,...
    // 'FeedoptDefaultConfig:30'         'dt', 1e-4, ...
    // 'FeedoptDefaultConfig:31'         'ZeroStartAccLimit', 0.01, ...
    // 'FeedoptDefaultConfig:32'         'ZeroStartJerkLimit', 1, ...
    // 'FeedoptDefaultConfig:33'         'ZeroStartVelLimit', 0.5, ...
    // 'FeedoptDefaultConfig:34'         'source', repmat(char(0), [1, 1024]),...
    // 'FeedoptDefaultConfig:35'         'DebugCutZero', false,...
    // 'FeedoptDefaultConfig:36'         'Compressing', struct(...
    // 'FeedoptDefaultConfig:37'             'Skip', false,...
    // 'FeedoptDefaultConfig:38'             'ColTolCos', cosd(tol_col_compress_deg)),...
    // 'FeedoptDefaultConfig:39'         'ColTolCos', cosd(tol_col_smooth_deg), ...
    // 'FeedoptDefaultConfig:40'         'GaussLegendreN', GaussLegendreN, ...
    // 'FeedoptDefaultConfig:41'         'GaussLegendreX', GaussLegendreX, ...
    // 'FeedoptDefaultConfig:42'         'GaussLegendreW', GaussLegendreW, ...
    // 'FeedoptDefaultConfig:43'         'LogFileName', 'logs', ...
    // 'FeedoptDefaultConfig:44'         'Simplex_params', [1e-6; 1e-6; 1; 1e-6]);
    cfg->NDiscr = 20;
    cfg->NBreak = 10;
    cfg->UseDynamicBreakpoints = false;
    cfg->UseLinearBreakpoints = false;
    cfg->DynamicBreakpointsDistance = 0.1;
    cfg->NHorz = 5;
    cfg->vmax = 150.0;
    cfg->amax[0] = 20000.0;
    cfg->jmax[0] = 1.5E+6;
    cfg->amax[1] = 20000.0;
    cfg->jmax[1] = 1.5E+6;
    cfg->amax[2] = 20000.0;
    cfg->jmax[2] = 1.5E+6;
    cfg->SplineDegree = 4;
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
    cfg->LogFileName[0] = 'l';
    cfg->Simplex_params[0] = 1.0E-6;
    cfg->LogFileName[1] = 'o';
    cfg->Simplex_params[1] = 1.0E-6;
    cfg->LogFileName[2] = 'g';
    cfg->Simplex_params[2] = 1.0;
    cfg->LogFileName[3] = 's';
    cfg->Simplex_params[3] = 1.0E-6;
    //  % Use a variable number of breakpoints for different lengths
    //    % Use a linear distribution of breakpoints (else sinspace)
    //  % Distance between two breakpoints in mm
    //  1: Dual; 2: Barrier; 3: Primal
    //      coder.varsize('cfg.source', [1024, 1], [0,1]);;
    //          'MaxNHorz', FeedoptLimits.MaxNHorz,...
    //          'MaxNDiscr', FeedoptLimits.MaxNDiscr,...
    //          'MaxNCoeff', FeedoptLimits.MaxNCoeff,...
    //  coder.varsize('cfg.source', [1, Inf], [0, 1]);
    // 'FeedoptDefaultConfig:51' coder.cstructname(cfg, 'FeedoptConfig');
}

} // namespace ocn

//
// File trailer for FeedoptDefaultConfig.cpp
//
// [EOF]
//
