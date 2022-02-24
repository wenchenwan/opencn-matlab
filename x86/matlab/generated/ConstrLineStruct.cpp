//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrLineStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 24-Feb-2022 11:51:03
//

// Include Files
#include "ConstrLineStruct.h"
#include "ConstrCurvStruct.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_rtwutil.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types21.h"
#include <cstring>

// Function Definitions
//
// function CurvStruct = ConstrLineStruct(trafo,  HSC, HSC_cmd, Poff, Aoff, ...
//                                        Uoff, Doff, P0, P1, A0, A1, U0, U1,...
//                                        FeedRate, ZSpdMode)
//
// Arguments    : bool trafo
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
//                double FeedRate
//                ZSpdMode b_ZSpdMode
//                CurvStruct *b_CurvStruct
// Return Type  : void
//
namespace ocn {
void ConstrLineStruct(bool trafo, bool HSC, const char HSC_cmd[256], const double Poff[3],
                      const double Aoff[3], const double Uoff[3], double Doff, const double P0[3],
                      const double P1[3], const double A0[3], const double A1[3],
                      const double U0[3], const double U1[3], double FeedRate, ZSpdMode b_ZSpdMode,
                      CurvStruct *b_CurvStruct)
{
    double dv2[6][3];
    double dv[3];
    double dv1[3];
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'ConstrLineStruct:4' coder.inline("never");
    // 'ConstrLineStruct:5' CoeffP5     = zeros(3, 6);
    // 'ConstrLineStruct:6' evec        = zeros(3, 1);
    // 'ConstrLineStruct:7' Cprim       = zeros(3, 1);
    // 'ConstrLineStruct:8' delta       = 0.0;
    // 'ConstrLineStruct:9' theta       = 0;
    // 'ConstrLineStruct:10' pitch       = 0;
    // 'ConstrLineStruct:13' CurvStruct  = ConstrCurvStruct(CurveType.Line, ZSpdMode, trafo,  HSC,
    // ... 'ConstrLineStruct:14'                                 HSC_cmd, Poff, Aoff, Uoff, Doff,
    // P0, P1,... 'ConstrLineStruct:15'                                 A0, A1, U0, U1, Cprim,
    // delta, evec, ... 'ConstrLineStruct:16'                                 theta, pitch, CoeffP5,
    // FeedRate);
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    for (int i{0}; i < 6; i++) {
        dv2[i][0] = 0.0;
        dv2[i][1] = 0.0;
        dv2[i][2] = 0.0;
    }
    ConstrCurvStruct(CurveType_Line, b_ZSpdMode, trafo, HSC, HSC_cmd, Poff, Aoff, Uoff, Doff, P0,
                     P1, A0, A1, U0, U1, dv, 0.0, dv1, 0.0, 0.0, dv2, FeedRate, b_CurvStruct);
    // 'ConstrLineStruct:19' coder.cstructname(CurvStruct, 'CurvStruct');
}

//
// function CurvStruct = ConstrLineStruct(trafo,  HSC, HSC_cmd, Poff, Aoff, ...
//                                        Uoff, Doff, P0, P1, A0, A1, U0, U1,...
//                                        FeedRate, ZSpdMode)
//
// Arguments    : const double P0[3]
//                const double P1[3]
//                double FeedRate
//                CurvStruct *b_CurvStruct
// Return Type  : void
//
void b_ConstrLineStruct(const double P0[3], const double P1[3], double FeedRate,
                        CurvStruct *b_CurvStruct)
{
    c_struct_T expl_temp;
    // 'ConstrLineStruct:4' coder.inline("never");
    // 'ConstrLineStruct:5' CoeffP5     = zeros(3, 6);
    // 'ConstrLineStruct:6' evec        = zeros(3, 1);
    // 'ConstrLineStruct:7' Cprim       = zeros(3, 1);
    // 'ConstrLineStruct:8' delta       = 0.0;
    // 'ConstrLineStruct:9' theta       = 0;
    // 'ConstrLineStruct:10' pitch       = 0;
    // 'ConstrLineStruct:13' CurvStruct  = ConstrCurvStruct(CurveType.Line, ZSpdMode, trafo,  HSC,
    // ... 'ConstrLineStruct:14'                                 HSC_cmd, Poff, Aoff, Uoff, Doff,
    // P0, P1,... 'ConstrLineStruct:15'                                 A0, A1, U0, U1, Cprim,
    // delta, evec, ... 'ConstrLineStruct:16'                                 theta, pitch, CoeffP5,
    // FeedRate);
    //  Construct a struct for the curves.
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
    std::memset(&expl_temp.HSC_cmd[0], 0, 256U * sizeof(char));
    expl_temp.sp.CoeffX = 0.0;
    expl_temp.sp.CoeffY = 0.0;
    expl_temp.sp.CoeffZ = 0.0;
    expl_temp.sp.Bl.ncoeff = 0;
    expl_temp.sp.Bl.handle = 0UL;
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
        expl_temp.CoeffP5[i][0] = 0.0;
        expl_temp.CoeffP5[i][1] = 0.0;
        expl_temp.CoeffP5[i][2] = 0.0;
    }
    expl_temp.pitch = 0.0;
    expl_temp.theta = 0.0;
    expl_temp.delta = 0.0;
    expl_temp.Doff = 0.0;
    expl_temp.evec[0] = 0.0;
    expl_temp.CorrectedHelixCenter[0] = 0.0;
    expl_temp.U1[0] = 0.0;
    expl_temp.U0[0] = 0.0;
    expl_temp.A1[0] = 0.0;
    expl_temp.A0[0] = 0.0;
    expl_temp.P1[0] = P1[0];
    expl_temp.P0[0] = P0[0];
    expl_temp.Uoff[0] = 0.0;
    expl_temp.Aoff[0] = 0.0;
    expl_temp.Poff[0] = 0.0;
    expl_temp.evec[1] = 0.0;
    expl_temp.CorrectedHelixCenter[1] = 0.0;
    expl_temp.U1[1] = 0.0;
    expl_temp.U0[1] = 0.0;
    expl_temp.A1[1] = 0.0;
    expl_temp.A0[1] = 0.0;
    expl_temp.P1[1] = P1[1];
    expl_temp.P0[1] = P0[1];
    expl_temp.Uoff[1] = 0.0;
    expl_temp.Aoff[1] = 0.0;
    expl_temp.Poff[1] = 0.0;
    expl_temp.evec[2] = 0.0;
    expl_temp.CorrectedHelixCenter[2] = 0.0;
    expl_temp.U1[2] = 0.0;
    expl_temp.U0[2] = 0.0;
    expl_temp.A1[2] = 0.0;
    expl_temp.A0[2] = 0.0;
    expl_temp.P1[2] = P1[2];
    expl_temp.P0[2] = P0[2];
    expl_temp.Uoff[2] = 0.0;
    expl_temp.Aoff[2] = 0.0;
    expl_temp.Poff[2] = 0.0;
    expl_temp.HSC = false;
    expl_temp.TRAFO = false;
    expl_temp.zspdmode = ZSpdMode_NN;
    expl_temp.Type = CurveType_Line;
    cast(&expl_temp, b_CurvStruct);
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
    // 'ConstrLineStruct:19' coder.cstructname(CurvStruct, 'CurvStruct');
}

} // namespace ocn

//
// File trailer for ConstrLineStruct.cpp
//
// [EOF]
//
