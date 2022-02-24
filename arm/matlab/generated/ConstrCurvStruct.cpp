//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 24-Feb-2022 11:48:06
//

// Include Files
#include "ConstrCurvStruct.h"
#include "opencn_matlab_rtwutil.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include <algorithm>

// Function Definitions
//
// function CStrct = ConstrCurvStruct(Type, ZSpdMode, trafo, HSC, HSC_cmd,...
//                                    Poff, Aoff, Uoff, Doff, P0, P1, A0, ...
//                                    A1, U0, U1, Cprim, delta, evec, theta,...
//                                    pitch, CoeffP5, FeedRate)
//
// Construct a struct for the curves.
//
//  trafo     : Flag for the trafo directive
//  HSC       : High speed cutting (true : on, false : off)
//  HSC_cmd   : parameters for the algorithms (string)
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
//                const char HSC_cmd[256]
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
                      const char HSC_cmd[256], const double Poff[3], const double Aoff[3],
                      const double Uoff[3], double Doff, const double P0[3], const double P1[3],
                      const double A0[3], const double A1[3], const double U0[3],
                      const double U1[3], const double Cprim[3], double delta, const double evec[3],
                      double theta, double pitch, const double CoeffP5[6][3], double FeedRate,
                      CurvStruct *CStrct)
{
    static const uint64m_T r{
        {0U, 0U} // chunks
    };
    c_struct_T expl_temp;
    //  ctxType = coder.OutputType('InitFeedoptPlan');
    // 'ConstrCurvStruct:39' CStrct = struct('Type', Type, ...
    // 'ConstrCurvStruct:40'                 'zspdmode', ZSpdMode, ...
    // 'ConstrCurvStruct:41'                 'TRAFO', trafo, ...
    // 'ConstrCurvStruct:42'                 'HSC', HSC, ...
    // 'ConstrCurvStruct:43'                 'HSC_cmd', HSC_cmd, ...
    // 'ConstrCurvStruct:44'                 'Poff', Poff, ...
    // 'ConstrCurvStruct:45'                 'Aoff', Aoff, ...
    // 'ConstrCurvStruct:46'                 'Uoff', Uoff, ...
    // 'ConstrCurvStruct:47'                 'Doff', Doff, ...
    // 'ConstrCurvStruct:48'                 'P0', P0, ...
    // 'ConstrCurvStruct:49'                 'P1', P1, ...
    // 'ConstrCurvStruct:50'                 'A0', A0,...
    // 'ConstrCurvStruct:51'                 'A1', A1,...
    // 'ConstrCurvStruct:52'                 'U0', U0,...
    // 'ConstrCurvStruct:53'                 'U1', U1,...
    // 'ConstrCurvStruct:54' 				'CorrectedHelixCenter', Cprim, ...
    // 'ConstrCurvStruct:55'                 'delta', delta, ...
    // 'ConstrCurvStruct:56'                 'evec', evec,...
    // 'ConstrCurvStruct:57'                 'theta', theta,...
    // 'ConstrCurvStruct:58'                 'pitch', pitch,...
    // 'ConstrCurvStruct:59'                 'CoeffP5', CoeffP5,...
    // 'ConstrCurvStruct:60'                 'sp_index', int32(1),...
    // 'ConstrCurvStruct:61'                 'FeedRate', FeedRate,...
    // 'ConstrCurvStruct:62'                 'SpindleSpeed', 0,...
    // 'ConstrCurvStruct:63'                 'MaxConstantFeedRate', 0,...
    // 'ConstrCurvStruct:64'                 'i_begin_sp', int32(0),...
    // 'ConstrCurvStruct:65'                 'i_end_sp', int32(0),...
    // 'ConstrCurvStruct:66'                 'gcode_source_line', int32(0),...
    // 'ConstrCurvStruct:67'                 'index_smooth', int32(0),...
    // 'ConstrCurvStruct:68'                 'UseConstJerk', false,...
    // 'ConstrCurvStruct:69'                 'ConstJerk', 0,...
    // 'ConstrCurvStruct:70'                 'ConstJerkMaxIterations', int32(0),...
    // 'ConstrCurvStruct:71'                 'Coeff', zeros(0, 1),...
    // 'ConstrCurvStruct:72'                 'a_param', 1,...
    // 'ConstrCurvStruct:73'                 'b_param', 0,...
    // 'ConstrCurvStruct:74'                 'sp', struct('CoeffX', 0,...
    // 'ConstrCurvStruct:75'                     'CoeffY', 0,...
    // 'ConstrCurvStruct:76'                     'CoeffZ', 0,...
    // 'ConstrCurvStruct:77'                     'Bl', struct(...
    // 'ConstrCurvStruct:78'                         'ncoeff', int32(0),...
    // 'ConstrCurvStruct:79'                         'breakpoints', zeros(1, 0),...
    // 'ConstrCurvStruct:80'                         'handle', uint64(0),...
    // 'ConstrCurvStruct:81'                         'degree', int32(0)),...
    // 'ConstrCurvStruct:82'                     'knots', 0,...
    // 'ConstrCurvStruct:83'                     'Ltot', 0,...
    // 'ConstrCurvStruct:84'                     'Lk', 0));
    expl_temp.sp.CoeffX = 0.0;
    expl_temp.sp.CoeffY = 0.0;
    expl_temp.sp.CoeffZ = 0.0;
    expl_temp.sp.Bl.ncoeff = 0;
    expl_temp.sp.Bl.handle = r;
    expl_temp.sp.Bl.degree = 0;
    expl_temp.sp.knots = 0.0;
    expl_temp.sp.Ltot = 0.0;
    expl_temp.sp.Lk = 0.0;
    expl_temp.b_param = 0.0;
    expl_temp.a_param = 1.0;
    expl_temp.ConstJerkMaxIterations = 0;
    expl_temp.ConstJerk = 0.0;
    expl_temp.UseConstJerk = false;
    expl_temp.index_smooth = 0;
    expl_temp.gcode_source_line = 0;
    expl_temp.i_end_sp = 0;
    expl_temp.i_begin_sp = 0;
    expl_temp.MaxConstantFeedRate = 0.0;
    expl_temp.SpindleSpeed = 0.0;
    expl_temp.FeedRate = FeedRate;
    expl_temp.sp_index = 1;
    for (int i{0}; i < 6; i++) {
        expl_temp.CoeffP5[i][0] = CoeffP5[i][0];
        expl_temp.CoeffP5[i][1] = CoeffP5[i][1];
        expl_temp.CoeffP5[i][2] = CoeffP5[i][2];
    }
    expl_temp.pitch = pitch;
    expl_temp.theta = theta;
    expl_temp.delta = delta;
    expl_temp.Doff = Doff;
    expl_temp.evec[0] = evec[0];
    expl_temp.CorrectedHelixCenter[0] = Cprim[0];
    expl_temp.U1[0] = U1[0];
    expl_temp.U0[0] = U0[0];
    expl_temp.A1[0] = A1[0];
    expl_temp.A0[0] = A0[0];
    expl_temp.P1[0] = P1[0];
    expl_temp.P0[0] = P0[0];
    expl_temp.Uoff[0] = Uoff[0];
    expl_temp.Aoff[0] = Aoff[0];
    expl_temp.Poff[0] = Poff[0];
    expl_temp.evec[1] = evec[1];
    expl_temp.CorrectedHelixCenter[1] = Cprim[1];
    expl_temp.U1[1] = U1[1];
    expl_temp.U0[1] = U0[1];
    expl_temp.A1[1] = A1[1];
    expl_temp.A0[1] = A0[1];
    expl_temp.P1[1] = P1[1];
    expl_temp.P0[1] = P0[1];
    expl_temp.Uoff[1] = Uoff[1];
    expl_temp.Aoff[1] = Aoff[1];
    expl_temp.Poff[1] = Poff[1];
    expl_temp.evec[2] = evec[2];
    expl_temp.CorrectedHelixCenter[2] = Cprim[2];
    expl_temp.U1[2] = U1[2];
    expl_temp.U0[2] = U0[2];
    expl_temp.A1[2] = A1[2];
    expl_temp.A0[2] = A0[2];
    expl_temp.P1[2] = P1[2];
    expl_temp.P0[2] = P0[2];
    expl_temp.Uoff[2] = Uoff[2];
    expl_temp.Aoff[2] = Aoff[2];
    expl_temp.Poff[2] = Poff[2];
    std::copy(&HSC_cmd[0], &HSC_cmd[256], &expl_temp.HSC_cmd[0]);
    expl_temp.HSC = HSC;
    expl_temp.TRAFO = trafo;
    expl_temp.zspdmode = b_ZSpdMode;
    expl_temp.Type = Type;
    cast(&expl_temp, CStrct);
    // 'ConstrCurvStruct:86' if ~coder.target('matlab')
    // 'ConstrCurvStruct:87' coder.cstructname(CStrct, 'CurvStruct');
    // 'ConstrCurvStruct:88' coder.cstructname(CStrct.sp, 'SplineStruct');
    // 'ConstrCurvStruct:89' coder.cstructname(CStrct.sp.Bl, 'SplineBase');
    // 'ConstrCurvStruct:91' coder.varsize('CStrct.sp.Bl.breakpoints', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:93' coder.varsize('CStrct.Coeff', [Inf, 1], [1, 0]);
    // 'ConstrCurvStruct:94' coder.varsize('CStrct.sp.CoeffX', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:95' coder.varsize('CStrct.sp.CoeffY', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:96' coder.varsize('CStrct.sp.CoeffZ', [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:97' coder.varsize('CStrct.sp.knots',  [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:98' coder.varsize('CStrct.sp.Lk',     [1, Inf], [0, 1]);
    // 'ConstrCurvStruct:100' coder.varsize('CStrct.CoeffP5', [3, 6], [0, 0]);
}

} // namespace ocn

//
// File trailer for ConstrCurvStruct.cpp
//
// [EOF]
//
