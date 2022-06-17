//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrCurvStruct.h
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:45:22
//

#ifndef CONSTRCURVSTRUCT_H
#define CONSTRCURVSTRUCT_H

// Include Files
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types31.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Type Declarations
namespace ocn {
struct uint64m_T;

}

// Function Declarations
namespace ocn {
void b_constrCurvStruct(CurveType gcodeInfoStruct_Type, ZSpdMode gcodeInfoStruct_zspdmode,
                        bool gcodeInfoStruct_TRAFO, bool gcodeInfoStruct_HSC,
                        double gcodeInfoStruct_FeedRate, double gcodeInfoStruct_SpindleSpeed,
                        int gcodeInfoStruct_gcode_source_line, bool gcodeInfoStruct_G91,
                        bool gcodeInfoStruct_G91_1, int spline_Bl_ncoeff,
                        const ::coder::array<double, 2U> &spline_Bl_breakpoints,
                        const uint64m_T spline_Bl_handle, int spline_Bl_order,
                        const ::coder::array<double, 2U> &spline_coeff,
                        const ::coder::array<double, 2U> &spline_knots, double spline_Ltot,
                        const ::coder::array<double, 2U> &spline_Lk, const double R0[6],
                        const double R1[6], const double Cprim[3], const double evec[3],
                        const double CoeffP5[6], CurvStruct *CStrct);

void c_constrCurvStruct(const GcodeInfoStruct gcodeInfoStruct, const SplineStruct *spline,
                        const double R0[6], const double R1[6], const double Cprim[3], double delta,
                        const double evec[3], double theta, double pitch, const double CoeffP5[6],
                        CurvStruct *CStrct);

void c_constrCurvStruct(const GcodeInfoStruct gcodeInfoStruct, int spline_Bl_ncoeff,
                        const ::coder::array<double, 2U> &spline_Bl_breakpoints,
                        const uint64m_T spline_Bl_handle, int spline_Bl_order,
                        const ::coder::array<double, 2U> &spline_coeff,
                        const ::coder::array<double, 2U> &spline_knots, double spline_Ltot,
                        const ::coder::array<double, 2U> &spline_Lk, const double R0[6],
                        const double R1[6], const double Cprim[3], const double evec[3],
                        const ::coder::array<double, 2U> &CoeffP5, CurvStruct *CStrct);

extern void constrCurvStruct(const GcodeInfoStruct *gcodeInfoStruct, const SplineStruct *spline,
                             const double R0[6], const double R1[6], const double Cprim[3],
                             double delta, const double evec[3], double theta, double pitch,
                             const ::coder::array<double, 2U> &CoeffP5,
                             const ::coder::array<double, 1U> &Coeff, CurvStruct *CStrct);

void d_constrCurvStruct(ZSpdMode gcodeInfoStruct_zspdmode, bool gcodeInfoStruct_TRAFO,
                        bool gcodeInfoStruct_HSC, double gcodeInfoStruct_FeedRate,
                        double gcodeInfoStruct_SpindleSpeed, int gcodeInfoStruct_gcode_source_line,
                        bool gcodeInfoStruct_G91, bool gcodeInfoStruct_G91_1, int spline_Bl_ncoeff,
                        const ::coder::array<double, 2U> &spline_Bl_breakpoints,
                        const uint64m_T spline_Bl_handle, int spline_Bl_order,
                        const ::coder::array<double, 2U> &spline_coeff,
                        const ::coder::array<double, 2U> &spline_knots, double spline_Ltot,
                        const ::coder::array<double, 2U> &spline_Lk, const double R0[6],
                        const double R1[6], const double Cprim[3], const double evec[3],
                        const double CoeffP5[6][5], CurvStruct *CStrct);

} // namespace ocn

#endif
//
// File trailer for constrCurvStruct.h
//
// [EOF]
//
