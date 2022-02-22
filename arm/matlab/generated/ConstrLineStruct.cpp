//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrLineStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 21-Feb-2022 17:59:00
//

// Include Files
#include "ConstrLineStruct.h"
#include "ConstrCurvStruct.h"
#include "EvalCurvStruct_data.h"
#include "EvalCurvStruct_initialize.h"
#include "EvalCurvStruct_types1.h"
#include "EvalCurvStruct_types2.h"

// Function Definitions
//
// function CurvStruct = ConstrLineStruct(trafo, Poff, Aoff, ...
//                                        Uoff, Doff, P0, P1, A0, A1, U0, U1,...
//                                        FeedRate, ZSpdMode)
//
// Arguments    : bool trafo
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
void ConstrLineStruct(bool trafo, const double Poff[3], const double Aoff[3], const double Uoff[3],
                      double Doff, const double P0[3], const double P1[3], const double A0[3],
                      const double A1[3], const double U0[3], const double U1[3], double FeedRate,
                      ZSpdMode b_ZSpdMode, CurvStruct *b_CurvStruct)
{
    double dv2[6][3];
    double dv[3];
    double dv1[3];
    if (!isInitialized_EvalCurvStruct) {
        EvalCurvStruct_initialize();
    }
    // 'ConstrLineStruct:5' coder.inline("never");
    // 'ConstrLineStruct:6' CoeffP5     = zeros(3, 6);
    // 'ConstrLineStruct:7' evec        = zeros(3, 1);
    // 'ConstrLineStruct:8' Cprim       = zeros(3, 1);
    // 'ConstrLineStruct:9' delta       = 0.0;
    // 'ConstrLineStruct:10' theta       = 0;
    // 'ConstrLineStruct:11' pitch       = 0;
    // 'ConstrLineStruct:14' CurvStruct  = ConstrCurvStruct(CurveType.Line, ZSpdMode, trafo, Poff,
    // ... 'ConstrLineStruct:15'                                 Aoff, Uoff, Doff, P0, P1, A0, A1,
    // U0, U1, ... 'ConstrLineStruct:16'                                 Cprim, delta, evec, theta,
    // pitch, ... 'ConstrLineStruct:17'                                 CoeffP5, FeedRate);
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
    ConstrCurvStruct(CurveType_Line, b_ZSpdMode, trafo, Poff, Aoff, Uoff, Doff, P0, P1, A0, A1, U0,
                     U1, dv, 0.0, dv1, 0.0, 0.0, dv2, FeedRate, b_CurvStruct);
    // 'ConstrLineStruct:19' coder.cstructname(CurvStruct, 'CurvStruct');
}

} // namespace ocn

//
// File trailer for ConstrLineStruct.cpp
//
// [EOF]
//
