//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:27:55
//

// Include Files
#include "ConstrCurvStruct.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"

// Function Definitions
//
// function CStrct = ConstrCurvStruct(Type, ZSpdMode, P0, P1, Cprim, delta, evec, theta, pitch,
// CoeffP5, FeedRate)
//
// ctxType = coder.OutputType('InitFeedoptPlan');
//
// Arguments    : CurveType Type
//                ZSpdMode b_ZSpdMode
//                const double P0[3]
//                const double P1[3]
//                const double Cprim[3]
//                double delta
//                const double evec[3]
//                double theta
//                double pitch
//                const double CoeffP5[6][3]
//                double FeedRate
//                CurvStruct *CStrct
// Return Type  : void
//
namespace ocn {
void ConstrCurvStruct(CurveType Type, ZSpdMode b_ZSpdMode, const double P0[3], const double P1[3],
                      const double Cprim[3], double delta, const double evec[3], double theta,
                      double pitch, const double CoeffP5[6][3], double FeedRate, CurvStruct *CStrct)
{
    // 'ConstrCurvStruct:5' CStrct = struct('Type', Type,...
    // 'ConstrCurvStruct:6'                 'zspdmode', ZSpdMode,...
    // 'ConstrCurvStruct:7'                 'P0', P0,...
    // 'ConstrCurvStruct:8'                 'P1', P1,...
    // 'ConstrCurvStruct:9' 				'CorrectedHelixCenter', Cprim,...
    // 'ConstrCurvStruct:10'                 'delta', delta, ...
    // 'ConstrCurvStruct:11'                 'evec', evec,...
    // 'ConstrCurvStruct:12'                 'theta', theta,...
    // 'ConstrCurvStruct:13'                 'pitch', pitch,...
    // 'ConstrCurvStruct:14'                 'CoeffP5', CoeffP5,...
    // 'ConstrCurvStruct:15'                 'sp_index', int32(1),...
    // 'ConstrCurvStruct:16'                 'FeedRate', FeedRate,...
    // 'ConstrCurvStruct:17'                 'SpindleSpeed', 0,...
    // 'ConstrCurvStruct:18'                 'MaxConstantFeedRate', 0,...
    // 'ConstrCurvStruct:19'                 'i_begin_sp', int32(0),...
    // 'ConstrCurvStruct:20'                 'i_end_sp', int32(0),...
    // 'ConstrCurvStruct:21'                 'gcode_source_line', int32(0),...
    // 'ConstrCurvStruct:22'                 'index_smooth', int32(0),...
    // 'ConstrCurvStruct:23'                 'UseConstJerk', false,...
    // 'ConstrCurvStruct:24'                 'ConstJerk', 0,...
    // 'ConstrCurvStruct:25'                 'ConstJerkMaxIterations', int32(0),...
    // 'ConstrCurvStruct:26'                 'Coeff', zeros(0, 1),...
    // 'ConstrCurvStruct:27'                 'a_param', 1,...
    // 'ConstrCurvStruct:28'                 'b_param', 0,...
    // 'ConstrCurvStruct:29'                 'sp', struct('CoeffX', 0,...
    // 'ConstrCurvStruct:30'                     'CoeffY', 0,...
    // 'ConstrCurvStruct:31'                     'CoeffZ', 0,...
    // 'ConstrCurvStruct:32'                     'Bl', struct(...
    // 'ConstrCurvStruct:33'                         'ncoeff', int32(0),...
    // 'ConstrCurvStruct:34'                         'breakpoints', zeros(1, 0),...
    // 'ConstrCurvStruct:35'                         'handle', uint64(0),...
    // 'ConstrCurvStruct:36'                         'degree', int32(0)),...
    // 'ConstrCurvStruct:37'                     'knots', 0,...
    // 'ConstrCurvStruct:38'                     'Ltot', 0,...
    // 'ConstrCurvStruct:39'                     'Lk', 0));
    CStrct->Type = Type;
    CStrct->zspdmode = b_ZSpdMode;
    CStrct->delta = delta;
    CStrct->P0[0] = P0[0];
    CStrct->P1[0] = P1[0];
    CStrct->CorrectedHelixCenter[0] = Cprim[0];
    CStrct->evec[0] = evec[0];
    CStrct->P0[1] = P0[1];
    CStrct->P1[1] = P1[1];
    CStrct->CorrectedHelixCenter[1] = Cprim[1];
    CStrct->evec[1] = evec[1];
    CStrct->P0[2] = P0[2];
    CStrct->P1[2] = P1[2];
    CStrct->CorrectedHelixCenter[2] = Cprim[2];
    CStrct->evec[2] = evec[2];
    CStrct->theta = theta;
    CStrct->pitch = pitch;
    for (int i{0}; i < 6; i++) {
        CStrct->CoeffP5[i][0] = CoeffP5[i][0];
        CStrct->CoeffP5[i][1] = CoeffP5[i][1];
        CStrct->CoeffP5[i][2] = CoeffP5[i][2];
    }
    CStrct->sp_index = 1;
    CStrct->FeedRate = FeedRate;
    CStrct->SpindleSpeed = 0.0;
    CStrct->MaxConstantFeedRate = 0.0;
    CStrct->i_begin_sp = 0;
    CStrct->i_end_sp = 0;
    CStrct->gcode_source_line = 0;
    CStrct->index_smooth = 0;
    CStrct->UseConstJerk = false;
    CStrct->ConstJerk = 0.0;
    CStrct->ConstJerkMaxIterations = 0;
    CStrct->Coeff.set_size(0);
    CStrct->a_param = 1.0;
    CStrct->b_param = 0.0;
    CStrct->sp.CoeffX.set_size(1, 1);
    CStrct->sp.CoeffX[0] = 0.0;
    CStrct->sp.CoeffY.set_size(1, 1);
    CStrct->sp.CoeffY[0] = 0.0;
    CStrct->sp.CoeffZ.set_size(1, 1);
    CStrct->sp.CoeffZ[0] = 0.0;
    CStrct->sp.Bl.ncoeff = 0;
    CStrct->sp.Bl.breakpoints.set_size(1, 0);
    CStrct->sp.Bl.handle = 0UL;
    CStrct->sp.Bl.degree = 0;
    CStrct->sp.knots.set_size(1, 1);
    CStrct->sp.knots[0] = 0.0;
    CStrct->sp.Ltot = 0.0;
    CStrct->sp.Lk.set_size(1, 1);
    CStrct->sp.Lk[0] = 0.0;
    // 'ConstrCurvStruct:41' if ~coder.target('matlab')
    // 'ConstrCurvStruct:42' coder.cstructname(CStrct, 'CurvStruct');
    // 'ConstrCurvStruct:43' coder.cstructname(CStrct.sp, 'SplineStruct');
    // 'ConstrCurvStruct:44' coder.cstructname(CStrct.sp.Bl, 'SplineBase');
    // 'ConstrCurvStruct:46' coder.varsize('CStrct.sp.Bl.breakpoints', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:48' coder.varsize('CStrct.Coeff', [Inf, 1], [1, 0]);
    // 'ConstrCurvStruct:49' coder.varsize('CStrct.sp.CoeffX', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:50' coder.varsize('CStrct.sp.CoeffY', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:51' coder.varsize('CStrct.sp.CoeffZ', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:52' coder.varsize('CStrct.sp.knots',  [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:53' coder.varsize('CStrct.sp.Lk',     [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:55' coder.varsize('CStrct.CoeffP5', [3, 6], [0, 0]);
}

} // namespace ocn

//
// File trailer for ConstrCurvStruct.cpp
//
// [EOF]
//
