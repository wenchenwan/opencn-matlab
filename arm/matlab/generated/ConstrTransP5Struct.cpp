//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrTransP5Struct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "ConstrTransP5Struct.h"
#include "ConstrCurvStruct.h"
#include "mypolyval.h"
#include "sinspace_data.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"

// Function Definitions
//
// Arguments    : const double CoeffP5[6][3]
//                double FeedRate
//                CurvStruct *b_CurvStruct
// Return Type  : void
//
namespace ocn {
void ConstrTransP5Struct(const double CoeffP5[6][3], double FeedRate, CurvStruct *b_CurvStruct)
{
    double dv[3];
    double dv1[3];
    double dv2[3];
    double y[3];
    // POLYVAL Evaluate array of polynomials with same degree.
    //
    //
    //  Use Horner's method for general case where X is an array.
    for (int i{0}; i < 5; i++) {
        y[0] = CoeffP5[i + 1][0];
        y[1] = CoeffP5[i + 1][1];
        y[2] = CoeffP5[i + 1][2];
    }
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    b_mypolyval(CoeffP5, dv2);
    ConstrCurvStruct(CurveType_TransP5, ZSpdMode_NN, y, dv2, dv, 0.0, dv1, 0.0, 0.0, CoeffP5,
                     FeedRate, b_CurvStruct);
}

} // namespace ocn

//
// File trailer for ConstrTransP5Struct.cpp
//
// [EOF]
//
