//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 27-Apr-2022 10:08:40
//

// Include Files
#include "ConstrCurvStruct.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"

// Function Definitions
//
// function CStrct = ConstrCurvStruct(Type, ZSpdMode, trafo, HSC,...
//                                    Poff, Aoff, Uoff, Doff, P0, P1, A0, ...
//                                    A1, U0, U1, Cprim, delta, evec, theta,...
//                                    pitch, CoeffP5, FeedRate)
//
// Construct a struct for the curves.
//
//  Type      : Type of curve
//  ZSpdMode  : Zero speed mode
//  trafo     : Flag for the trafo directive
//  HSC       : High speed cutting (true : on, false : off)
//  Poff      : Offset on the position {X, Y, Z}
//  Aoff      : Offset on the angle {A, B, C}
//  Uoff      : Offset on the sub-axis {U, V, W}
//  Doff      : Offset for the diameter of the tool
//  P0        : vector of the position at starting time
//  P1        : vector of the position at ending time
//  A0        : Vector of the orientation angles at starting time
//  A1        : Vector of the orientation angles at ending time
//  U0        : Vector of for the secondary axes at starting time
//  U1        : Vector of for the secondary axes at ending time
//  Cprim     : Corrected center for the circle
//  delta     : Difference between the radii
//  evec      : Unit vector in the linear direction for the helix
//  theta     : Rotation angle of the helix
//  pitch     : Linear step for the helix
//  CoeffP5   : Coefficient of the 5th order polynom
//  Feedrate  : Feedrate of the spindle
//
//  CStrct    : The resulting structure
//
// Arguments    : CurveType Type
//                ZSpdMode b_ZSpdMode
//                bool trafo
//                bool HSC
//                const double Poff[3]
//                const double Aoff[3]
//                const double Uoff[3]
//                double Doff
//                const double P0[3]
//                const double P1[3]
//                const double A0[3]
//                const double A1[3]
//                const double U0[3]
//                const double U1[3]
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
void ConstrCurvStruct(CurveType Type, ZSpdMode b_ZSpdMode, bool trafo, bool HSC,
                      const double Poff[3], const double Aoff[3], const double Uoff[3], double Doff,
                      const double P0[3], const double P1[3], const double A0[3],
                      const double A1[3], const double U0[3], const double U1[3],
                      const double Cprim[3], double delta, const double evec[3], double theta,
                      double pitch, const double CoeffP5[6][3], double FeedRate, CurvStruct *CStrct)
{
    //  ctxType = coder.OutputType('InitFeedoptPlan');
    // 'ConstrCurvStruct:33' CStrct = struct('Type', Type, ...
    // 'ConstrCurvStruct:34'                 'zspdmode', ZSpdMode, ...
    // 'ConstrCurvStruct:35'                 'TRAFO', trafo, ...
    // 'ConstrCurvStruct:36'                 'HSC', HSC, ...
    // 'ConstrCurvStruct:37'                 'Poff', Poff, ...
    // 'ConstrCurvStruct:38'                 'Aoff', Aoff, ...
    // 'ConstrCurvStruct:39'                 'Uoff', Uoff, ...
    // 'ConstrCurvStruct:40'                 'Doff', Doff, ...
    // 'ConstrCurvStruct:41'                 'P0', P0, ...
    // 'ConstrCurvStruct:42'                 'P1', P1, ...
    // 'ConstrCurvStruct:43'                 'A0', A0,...
    // 'ConstrCurvStruct:44'                 'A1', A1,...
    // 'ConstrCurvStruct:45'                 'U0', U0,...
    // 'ConstrCurvStruct:46'                 'U1', U1,...
    // 'ConstrCurvStruct:47' 				'CorrectedHelixCenter', Cprim, ...
    // 'ConstrCurvStruct:48'                 'delta', delta, ...
    // 'ConstrCurvStruct:49'                 'evec', evec,...
    // 'ConstrCurvStruct:50'                 'theta', theta,...
    // 'ConstrCurvStruct:51'                 'pitch', pitch,...
    // 'ConstrCurvStruct:52'                 'CoeffP5', CoeffP5,...
    // 'ConstrCurvStruct:53'                 'sp_index', int32(1),...
    // 'ConstrCurvStruct:54'                 'FeedRate', FeedRate,...
    // 'ConstrCurvStruct:55'                 'SpindleSpeed', 0,...
    // 'ConstrCurvStruct:56'                 'MaxConstantFeedRate', 0,...
    // 'ConstrCurvStruct:57'                 'i_begin_sp', int32(0),...
    // 'ConstrCurvStruct:58'                 'i_end_sp', int32(0),...
    // 'ConstrCurvStruct:59'                 'gcode_source_line', int32(0),...
    // 'ConstrCurvStruct:60'                 'UseConstJerk', false,...
    // 'ConstrCurvStruct:61'                 'ConstJerk', 0,...
    // 'ConstrCurvStruct:62'                 'ConstJerkMaxIterations', int32(0),...
    // 'ConstrCurvStruct:63'                 'Coeff', zeros(0, 1),...
    // 'ConstrCurvStruct:64'                 'a_param', 1,...
    // 'ConstrCurvStruct:65'                 'b_param', 0,...
    // 'ConstrCurvStruct:66'                 'sp', struct('CoeffX', 0,...
    // 'ConstrCurvStruct:67'                     'CoeffY', 0,...
    // 'ConstrCurvStruct:68'                     'CoeffZ', 0,...
    // 'ConstrCurvStruct:69'                     'Bl', struct(...
    // 'ConstrCurvStruct:70'                         'ncoeff', int32(0),...
    // 'ConstrCurvStruct:71'                         'breakpoints', zeros(1, 0),...
    // 'ConstrCurvStruct:72'                         'handle', uint64(0),...
    // 'ConstrCurvStruct:73'                         'degree', int32(0)),...
    // 'ConstrCurvStruct:74'                     'knots', 0,...
    // 'ConstrCurvStruct:75'                     'Ltot', 0,...
    // 'ConstrCurvStruct:76'                     'Lk', 0));
    CStrct->Type = Type;
    CStrct->zspdmode = b_ZSpdMode;
    CStrct->TRAFO = trafo;
    CStrct->HSC = HSC;
    CStrct->Doff = Doff;
    CStrct->delta = delta;
    CStrct->Poff[0] = Poff[0];
    CStrct->Aoff[0] = Aoff[0];
    CStrct->Uoff[0] = Uoff[0];
    CStrct->P0[0] = P0[0];
    CStrct->P1[0] = P1[0];
    CStrct->A0[0] = A0[0];
    CStrct->A1[0] = A1[0];
    CStrct->U0[0] = U0[0];
    CStrct->U1[0] = U1[0];
    CStrct->CorrectedHelixCenter[0] = Cprim[0];
    CStrct->evec[0] = evec[0];
    CStrct->Poff[1] = Poff[1];
    CStrct->Aoff[1] = Aoff[1];
    CStrct->Uoff[1] = Uoff[1];
    CStrct->P0[1] = P0[1];
    CStrct->P1[1] = P1[1];
    CStrct->A0[1] = A0[1];
    CStrct->A1[1] = A1[1];
    CStrct->U0[1] = U0[1];
    CStrct->U1[1] = U1[1];
    CStrct->CorrectedHelixCenter[1] = Cprim[1];
    CStrct->evec[1] = evec[1];
    CStrct->Poff[2] = Poff[2];
    CStrct->Aoff[2] = Aoff[2];
    CStrct->Uoff[2] = Uoff[2];
    CStrct->P0[2] = P0[2];
    CStrct->P1[2] = P1[2];
    CStrct->A0[2] = A0[2];
    CStrct->A1[2] = A1[2];
    CStrct->U0[2] = U0[2];
    CStrct->U1[2] = U1[2];
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
    // 'ConstrCurvStruct:78' if ~coder.target('matlab')
    // 'ConstrCurvStruct:79' coder.cstructname(CStrct, 'CurvStruct');
    // 'ConstrCurvStruct:80' coder.cstructname(CStrct.sp, 'SplineStruct');
    // 'ConstrCurvStruct:81' coder.cstructname(CStrct.sp.Bl, 'SplineBase');
    // 'ConstrCurvStruct:83' coder.varsize('CStrct.sp.Bl.breakpoints', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:85' coder.varsize('CStrct.Coeff', [Inf, 1], [1, 0]);
    // 'ConstrCurvStruct:86' coder.varsize('CStrct.sp.CoeffX', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:87' coder.varsize('CStrct.sp.CoeffY', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:88' coder.varsize('CStrct.sp.CoeffZ', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:89' coder.varsize('CStrct.sp.knots',  [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:90' coder.varsize('CStrct.sp.Lk',     [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:92' coder.varsize('CStrct.CoeffP5', [3, 6], [0, 0]);
}

} // namespace ocn

//
// File trailer for ConstrCurvStruct.cpp
//
// [EOF]
//
