//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrBSplineStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:36:47
//

// Include Files
#include "ConstrBSplineStruct.h"
#include "ConstrCurvStruct.h"
#include "c_assert.h"
#include "sinspace_data.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &pvec
//                double FeedRate
//                CurvStruct *b_CurvStruct
// Return Type  : void
//
namespace ocn {
void ConstrBSplineStruct(const ::coder::array<double, 2U> &pvec, double FeedRate,
                         CurvStruct *b_CurvStruct)
{
    double dv3[6][3];
    double dv[3];
    double dv1[3];
    double dv2[3];
    double dv4[3];
    int b_pvec;
    h_c_assert(pvec.size(1) > 2);
    b_pvec = pvec.size(1);
    dv[0] = 0.0;
    dv1[0] = 0.0;
    dv[1] = 0.0;
    dv1[1] = 0.0;
    dv[2] = 0.0;
    dv1[2] = 0.0;
    for (int i{0}; i < 6; i++) {
        dv3[i][0] = 0.0;
        dv3[i][1] = 0.0;
        dv3[i][2] = 0.0;
    }
    dv2[0] = (*(double(*)[3]) & pvec[0])[0];
    dv2[1] = (*(double(*)[3]) & pvec[0])[1];
    dv2[2] = (*(double(*)[3]) & pvec[0])[2];
    dv4[0] = (*(double(*)[3]) & pvec[3 * (b_pvec - 1)])[0];
    dv4[1] = (*(double(*)[3]) & pvec[3 * (b_pvec - 1)])[1];
    dv4[2] = (*(double(*)[3]) & pvec[3 * (b_pvec - 1)])[2];
    ConstrCurvStruct(CurveType_Spline, ZSpdMode_NN, dv2, dv4, dv, 0.0, dv1, 0.0, 0.0, dv3, FeedRate,
                     b_CurvStruct);
}

} // namespace ocn

//
// File trailer for ConstrBSplineStruct.cpp
//
// [EOF]
//
