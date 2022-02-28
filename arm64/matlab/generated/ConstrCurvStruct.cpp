//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Feb-2022 15:02:06
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
//  trafo     : Flag for the trafo directive
//  HSC       : High speed cutting (true : on, false : off)
//  Poff      : Offset on the position {X, Y, Z}
//  Aoff      : Offset on the angle {A, B, C}
//  Uoff      : Offset on the sub-axis {U, V, W}
//  Doff      : Offset for the diameter of the tool
//  p0x       : Value in the x axis of point P0
//  p0y       : Value in the y axis of point P0
//  p0z       : Value in the z axis of point P0
//  p1x       : Value in the x axis of point P1
//  p1y       : Value in the y axis of point P1
//  p1z       : Value in the z axis of point P1
//  cx        : Value in the x axis of the center C
//  cy        : Value in the y axis of the center C
//  cz        : Value in the z axis of the center C
//  A0        : Vector of the orientation angles at starting pose
//  A1        : Vector of the orientation angles at ending pose
//  U0        : Vector of for the secondary axes at starting pose
//  U1        : Vector of for the secondary axes at ending pose
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
    // 'ConstrCurvStruct:38' CStrct = struct('Type', Type, ...
    // 'ConstrCurvStruct:39'                 'zspdmode', ZSpdMode, ...
    // 'ConstrCurvStruct:40'                 'TRAFO', trafo, ...
    // 'ConstrCurvStruct:41'                 'HSC', HSC, ...
    // 'ConstrCurvStruct:42'                 'Poff', Poff, ...
    // 'ConstrCurvStruct:43'                 'Aoff', Aoff, ...
    // 'ConstrCurvStruct:44'                 'Uoff', Uoff, ...
    // 'ConstrCurvStruct:45'                 'Doff', Doff, ...
    // 'ConstrCurvStruct:46'                 'P0', P0, ...
    // 'ConstrCurvStruct:47'                 'P1', P1, ...
    // 'ConstrCurvStruct:48'                 'A0', A0,...
    // 'ConstrCurvStruct:49'                 'A1', A1,...
    // 'ConstrCurvStruct:50'                 'U0', U0,...
    // 'ConstrCurvStruct:51'                 'U1', U1,...
    // 'ConstrCurvStruct:52' 				'CorrectedHelixCenter', Cprim, ...
    // 'ConstrCurvStruct:53'                 'delta', delta, ...
    // 'ConstrCurvStruct:54'                 'evec', evec,...
    // 'ConstrCurvStruct:55'                 'theta', theta,...
    // 'ConstrCurvStruct:56'                 'pitch', pitch,...
    // 'ConstrCurvStruct:57'                 'CoeffP5', CoeffP5,...
    // 'ConstrCurvStruct:58'                 'sp_index', int32(1),...
    // 'ConstrCurvStruct:59'                 'FeedRate', FeedRate,...
    // 'ConstrCurvStruct:60'                 'SpindleSpeed', 0,...
    // 'ConstrCurvStruct:61'                 'MaxConstantFeedRate', 0,...
    // 'ConstrCurvStruct:62'                 'i_begin_sp', int32(0),...
    // 'ConstrCurvStruct:63'                 'i_end_sp', int32(0),...
    // 'ConstrCurvStruct:64'                 'gcode_source_line', int32(0),...
    // 'ConstrCurvStruct:65'                 'index_smooth', int32(0),...
    // 'ConstrCurvStruct:66'                 'UseConstJerk', false,...
    // 'ConstrCurvStruct:67'                 'ConstJerk', 0,...
    // 'ConstrCurvStruct:68'                 'ConstJerkMaxIterations', int32(0),...
    // 'ConstrCurvStruct:69'                 'Coeff', zeros(0, 1),...
    // 'ConstrCurvStruct:70'                 'a_param', 1,...
    // 'ConstrCurvStruct:71'                 'b_param', 0,...
    // 'ConstrCurvStruct:72'                 'sp', struct('CoeffX', 0,...
    // 'ConstrCurvStruct:73'                     'CoeffY', 0,...
    // 'ConstrCurvStruct:74'                     'CoeffZ', 0,...
    // 'ConstrCurvStruct:75'                     'Bl', struct(...
    // 'ConstrCurvStruct:76'                         'ncoeff', int32(0),...
    // 'ConstrCurvStruct:77'                         'breakpoints', zeros(1, 0),...
    // 'ConstrCurvStruct:78'                         'handle', uint64(0),...
    // 'ConstrCurvStruct:79'                         'degree', int32(0)),...
    // 'ConstrCurvStruct:80'                     'knots', 0,...
    // 'ConstrCurvStruct:81'                     'Ltot', 0,...
    // 'ConstrCurvStruct:82'                     'Lk', 0));
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
    // 'ConstrCurvStruct:84' if ~coder.target('matlab')
    // 'ConstrCurvStruct:85' coder.cstructname(CStrct, 'CurvStruct');
    // 'ConstrCurvStruct:86' coder.cstructname(CStrct.sp, 'SplineStruct');
    // 'ConstrCurvStruct:87' coder.cstructname(CStrct.sp.Bl, 'SplineBase');
    // 'ConstrCurvStruct:89' coder.varsize('CStrct.sp.Bl.breakpoints', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:91' coder.varsize('CStrct.Coeff', [Inf, 1], [1, 0]);
    // 'ConstrCurvStruct:92' coder.varsize('CStrct.sp.CoeffX', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:93' coder.varsize('CStrct.sp.CoeffY', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:94' coder.varsize('CStrct.sp.CoeffZ', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:95' coder.varsize('CStrct.sp.knots',  [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:96' coder.varsize('CStrct.sp.Lk',     [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:98' coder.varsize('CStrct.CoeffP5', [3, 6], [0, 0]);
}

} // namespace ocn

//
// File trailer for ConstrCurvStruct.cpp
//
// [EOF]
//
