//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: FeedoptDefaultConfig.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 07-Feb-2022 12:46:09
//

// Include Files
#include "FeedoptDefaultConfig.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "sinspace_types.h"
#include <cstring>

// Function Definitions
//
// Arguments    : FeedoptConfig *cfg
// Return Type  : void
//
namespace ocn {
void FeedoptDefaultConfig(FeedoptConfig *cfg)
{
    static const char b_cv[9]{'l', 'o', 'g', 's', '/', 'l', 'o', 'g', 's'};
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
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
    cfg->Compressing.ColTolDeg = 5.0;
    cfg->CollTolDeg = 1.0E-6;
    cfg->NGridLengthSpline = 10.0;
    for (int i{0}; i < 9; i++) {
        cfg->LogFileName[i] = b_cv[i];
    }
    //  % Use a variable number of breakpoints for different lengths
    //    % Use a linear distribution of breakpoints (else sinspace)
    //  % Distance between two breakpoints in mm
    //      coder.varsize('cfg.source', [1024, 1], [0,1]);;
    //          'MaxNHorz', FeedoptLimits.MaxNHorz,...
    //          'MaxNDiscr', FeedoptLimits.MaxNDiscr,...
    //          'MaxNCoeff', FeedoptLimits.MaxNCoeff,...
    //  coder.varsize('cfg.source', [1, Inf], [0, 1]);
}

} // namespace ocn

//
// File trailer for FeedoptDefaultConfig.cpp
//
// [EOF]
//
