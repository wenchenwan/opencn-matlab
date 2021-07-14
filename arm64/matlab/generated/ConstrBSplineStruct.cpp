//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrBSplineStruct.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:06:07
//

// Include Files
#include "ConstrBSplineStruct.h"
#include "ConstrCurvStruct.h"
#include "c_assert.h"
#include "queue_coder.h"
#include "sinspace_data.h"
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
    double dv2[6][3];
    double dv[3];
    double dv1[3];
    int b_pvec;
    d_c_assert(pvec.size(1) > 2);
    b_pvec = pvec.size(1);
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
    ConstrCurvStruct(CurveType_Spline, ZSpdMode_NN, *(double(*)[3]) & pvec[0],
                     *(double(*)[3]) & pvec[3 * (b_pvec - 1)], dv, 0.0, dv1, 0.0, 0.0, dv2,
                     FeedRate, b_CurvStruct);
}

} // namespace ocn

//
// File trailer for ConstrBSplineStruct.cpp
//
// [EOF]
//
