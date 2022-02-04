//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalCurvStructNoCtx.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:47:09
//

// Include Files
#include "EvalCurvStructNoCtx.h"
#include "EvalBSplineNoCtx.h"
#include "EvalHelix.h"
#include "EvalLine.h"
#include "EvalTransP5.h"
#include "sinspace_data.h"
#include "sinspace_types2.h"
#include "coder_array.h"
#include <stdio.h>

// Function Definitions
//
// coder.cstructname(CurvStruct, 'CurvStruct')
//
// Arguments    : CurveType CurvStruct_Type
//                const double CurvStruct_P0[3]
//                const double CurvStruct_P1[3]
//                const double CurvStruct_CorrectedHelixCenter[3]
//                const double CurvStruct_evec[3]
//                double CurvStruct_theta
//                double CurvStruct_pitch
//                const double CurvStruct_CoeffP5[6][3]
//                double CurvStruct_a_param
//                double CurvStruct_b_param
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ
//                unsigned long CurvSpline_sp_Bl_handle
//                double u_vec
//                double r0D[3]
// Return Type  : void
//
namespace ocn {
void EvalCurvStructNoCtx(CurveType CurvStruct_Type, const double CurvStruct_P0[3],
                         const double CurvStruct_P1[3],
                         const double CurvStruct_CorrectedHelixCenter[3],
                         const double CurvStruct_evec[3], double CurvStruct_theta,
                         double CurvStruct_pitch, const double CurvStruct_CoeffP5[6][3],
                         double CurvStruct_a_param, double CurvStruct_b_param,
                         const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX,
                         const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY,
                         const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ,
                         unsigned long CurvSpline_sp_Bl_handle, double u_vec, double r0D[3])
{
    double r1D[3];
    double r2D[3];
    double r3D[3];
    double u_vec_tilda;
    char message[30];
    if (u_vec - 1.0 > 2.2204460492503131E-15) {
        double unnamed_idx_0;
        printf("EvalCurvStruct: u_vec > 1\n");
        fflush(stdout);
        unnamed_idx_0 = u_vec;
        if (u_vec > 1.0) {
            unnamed_idx_0 = 1.0;
        }
        u_vec = unnamed_idx_0;
    }
    if (u_vec < 0.0) {
        printf("EvalCurvStruct: u_vec < 0\n");
        fflush(stdout);
        u_vec = 0.0;
    }
    //
    r0D[0] = 0.0;
    r0D[1] = 0.0;
    r0D[2] = 0.0;
    u_vec_tilda = CurvStruct_a_param * u_vec + CurvStruct_b_param;
    switch (CurvStruct_Type) {
    case CurveType_Line:
        //  line (G01)
        EvalLine(CurvStruct_P0, CurvStruct_P1, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Helix:
        //  arc of circle / helix (G02, G03)
        EvalHelix(CurvStruct_P0, CurvStruct_P1, CurvStruct_CorrectedHelixCenter, CurvStruct_evec,
                  CurvStruct_theta, CurvStruct_pitch, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_TransP5:
        //  polynomial transition
        EvalTransP5(CurvStruct_CoeffP5, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    case CurveType_Spline:
        //  BSpline
        EvalBSplineNoCtx(CurvSpline_sp_CoeffX, CurvSpline_sp_CoeffY, CurvSpline_sp_CoeffZ,
                         CurvSpline_sp_Bl_handle, u_vec_tilda, r0D, r1D, r2D, r3D);
        break;
    default:
        for (int i{0}; i < 30; i++) {
            message[i] = cv[i];
        }
        c_assert_(&message[0]);
        break;
    }
}

} // namespace ocn

//
// File trailer for EvalCurvStructNoCtx.cpp
//
// [EOF]
//
