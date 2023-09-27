//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constrCurvStruct.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 09:15:18
//

#ifndef CONSTRCURVSTRUCT_H
#define CONSTRCURVSTRUCT_H

// Include Files
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "opencn_matlab_types3.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Custom Header Code
#include "functions.h"
// Function Declarations
namespace ocn {
void b_constrCurvStruct(CurveType gcodeInfoStruct_Type, ZSpdMode gcodeInfoStruct_zspdmode,
                        bool gcodeInfoStruct_TRAFO, bool gcodeInfoStruct_HSC,
                        double gcodeInfoStruct_FeedRate, double gcodeInfoStruct_SpindleSpeed,
                        int gcodeInfoStruct_gcode_source_line, bool gcodeInfoStruct_G91,
                        bool gcodeInfoStruct_G91_1, int toolStruct_toolno, int toolStruct_pocketno,
                        const Axes *toolStruct_offset, double toolStruct_diameter,
                        double toolStruct_frontangle, double toolStruct_backangle,
                        int toolStruct_orientation, const SplineStruct *spline, const double R0[6],
                        const double R1[6], const double Cprim[3], const double evec[3],
                        const double CoeffP5[6], CurvStruct *CStrct);

void c_constrCurvStruct(const GcodeInfoStruct gcodeInfoStruct, const Tool *toolStruct,
                        const SplineStruct *spline, const double R0[6], const double R1[6],
                        const double Cprim[3], double delta, const double evec[3], double theta,
                        double pitch, const double CoeffP5[6], CurvStruct *CStrct);

void c_constrCurvStruct(const GcodeInfoStruct gcodeInfoStruct, const Tool *toolStruct,
                        const SplineStruct *spline, const double R0[6], const double R1[6],
                        const double Cprim[3], const double evec[3],
                        const ::coder::array<double, 2U> &CoeffP5, CurvStruct *CStrct);

extern void constrCurvStruct(const GcodeInfoStruct *gcodeInfoStruct, const Tool *toolStruct,
                             const SplineStruct *spline, const double R0[6], const double R1[6],
                             const double Cprim[3], double delta, const double evec[3],
                             double theta, double pitch, const ::coder::array<double, 2U> &CoeffP5,
                             const ::coder::array<double, 1U> &Coeff, CurvStruct *CStrct);

void d_constrCurvStruct(bool gcodeInfoStruct_TRAFO, bool gcodeInfoStruct_HSC,
                        double gcodeInfoStruct_FeedRate, double gcodeInfoStruct_SpindleSpeed,
                        int gcodeInfoStruct_gcode_source_line, bool gcodeInfoStruct_G91,
                        bool gcodeInfoStruct_G91_1, int toolStruct_toolno, int toolStruct_pocketno,
                        const Axes *toolStruct_offset, double toolStruct_diameter,
                        double toolStruct_frontangle, double toolStruct_backangle,
                        int toolStruct_orientation, const SplineStruct *spline, const double R0[6],
                        const double R1[6], const double Cprim[3], const double evec[3],
                        const double CoeffP5[6][6], CurvStruct *CStrct);

} // namespace ocn

#endif
//
// File trailer for constrCurvStruct.h
//
// [EOF]
//
