//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalBSplineNoCtx.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "EvalBSplineNoCtx.h"
#include "bspline_eval.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY
//                const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ
//                unsigned long CurvSpline_sp_Bl_handle
//                double uvec
//                double r0D[3]
//                double r1D[3]
//                double r2D[3]
//                double r3D[3]
// Return Type  : void
//
namespace ocn {
void EvalBSplineNoCtx(const ::coder::array<double, 2U> &CurvSpline_sp_CoeffX,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffY,
                      const ::coder::array<double, 2U> &CurvSpline_sp_CoeffZ,
                      unsigned long CurvSpline_sp_Bl_handle, double uvec, double r0D[3],
                      double r1D[3], double r2D[3], double r3D[3])
{
    double r0Dx;
    double r0Dy;
    double r0Dz;
    double r1Dx;
    double r1Dy;
    double r1Dz;
    double r2Dx;
    double r2Dy;
    double r2Dz;
    double r3Dx;
    double r3Dy;
    double r3Dz;
    ZoneScopedN("EvalBSpline");
    r0Dx = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffX, &r0Dx, &r1Dx, &r2Dx, &r3Dx);
    r0Dy = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffY, &r0Dy, &r1Dy, &r2Dy, &r3Dy);
    r0Dz = uvec;
    bspline_eval(CurvSpline_sp_Bl_handle, CurvSpline_sp_CoeffZ, &r0Dz, &r1Dz, &r2Dz, &r3Dz);
    r0D[0] = r0Dx;
    r0D[1] = r0Dy;
    r0D[2] = r0Dz;
    r1D[0] = r1Dx;
    r1D[1] = r1Dy;
    r1D[2] = r1Dz;
    r2D[0] = r2Dx;
    r2D[1] = r2Dy;
    r2D[2] = r2Dz;
    r3D[0] = r3Dx;
    r3D[1] = r3Dy;
    r3D[2] = r3Dz;
}

} // namespace ocn

//
// File trailer for EvalBSplineNoCtx.cpp
//
// [EOF]
//
