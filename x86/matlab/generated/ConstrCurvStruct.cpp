//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 18-Feb-2022 13:18:06
//

// Include Files
#include "ConstrCurvStruct.h"
#include "sinspace_types1.h"
#include "sinspace_types2.h"
#include "sinspace_types3.h"
#include "coder_array.h"

// Function Declarations
namespace ocn {
static void cast(::coder::array<double, 2U> &t1_CoeffX, ::coder::array<double, 2U> &t1_CoeffY,
                 ::coder::array<double, 2U> &t1_CoeffZ, int *t1_Bl_ncoeff,
                 ::coder::array<double, 2U> &t1_Bl_breakpoints, unsigned long *t1_Bl_handle,
                 int *t1_Bl_degree, ::coder::array<double, 2U> &t1_knots);

static void cast(::coder::array<double, 2U> &r);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &t1_CoeffX
//                ::coder::array<double, 2U> &t1_CoeffY
//                ::coder::array<double, 2U> &t1_CoeffZ
//                int *t1_Bl_ncoeff
//                ::coder::array<double, 2U> &t1_Bl_breakpoints
//                unsigned long *t1_Bl_handle
//                int *t1_Bl_degree
//                ::coder::array<double, 2U> &t1_knots
// Return Type  : void
//
namespace ocn {
static void cast(::coder::array<double, 2U> &t1_CoeffX, ::coder::array<double, 2U> &t1_CoeffY,
                 ::coder::array<double, 2U> &t1_CoeffZ, int *t1_Bl_ncoeff,
                 ::coder::array<double, 2U> &t1_Bl_breakpoints, unsigned long *t1_Bl_handle,
                 int *t1_Bl_degree, ::coder::array<double, 2U> &t1_knots)
{
    cast(t1_CoeffX);
    cast(t1_CoeffY);
    cast(t1_CoeffZ);
    t1_Bl_breakpoints.set_size(1, 0);
    cast(t1_knots);
    *t1_Bl_ncoeff = 0;
    *t1_Bl_handle = 0UL;
    *t1_Bl_degree = 0;
}

//
// Arguments    : ::coder::array<double, 2U> &r
// Return Type  : void
//
static void cast(::coder::array<double, 2U> &r)
{
    r.set_size(1, 1);
    r[0] = 0.0;
}

//
// Construct a struct for the curves.
//
//  trafo     : Flag for the trafo directive
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
void ConstrCurvStruct(CurveType Type, ZSpdMode b_ZSpdMode, bool trafo, const double Poff[3],
                      const double Aoff[3], const double Uoff[3], double Doff, const double P0[3],
                      const double P1[3], const double A0[3], const double A1[3],
                      const double U0[3], const double U1[3], const double Cprim[3], double delta,
                      const double evec[3], double theta, double pitch, const double CoeffP5[6][3],
                      double FeedRate, CurvStruct *CStrct)
{
    //  ctxType = coder.OutputType('InitFeedoptPlan');
    CStrct->Type = Type;
    CStrct->zspdmode = b_ZSpdMode;
    CStrct->TRAFO = trafo;
    CStrct->Doff = Doff;
    CStrct->delta = delta;
    CStrct->Poff[0] = Poff[0];
    CStrct->Aoff[0] = Aoff[0];
    CStrct->Uoff[0] = Uoff[0];
    CStrct->P0[0] = P0[0];
    CStrct->P1[0] = P1[0];
    CStrct->A0[0] = A0[0];
    CStrct->A1[0] = A1[0];
    CStrct->U0[0] = U0[0];
    CStrct->U1[0] = U1[0];
    CStrct->CorrectedHelixCenter[0] = Cprim[0];
    CStrct->evec[0] = evec[0];
    CStrct->Poff[1] = Poff[1];
    CStrct->Aoff[1] = Aoff[1];
    CStrct->Uoff[1] = Uoff[1];
    CStrct->P0[1] = P0[1];
    CStrct->P1[1] = P1[1];
    CStrct->A0[1] = A0[1];
    CStrct->A1[1] = A1[1];
    CStrct->U0[1] = U0[1];
    CStrct->U1[1] = U1[1];
    CStrct->CorrectedHelixCenter[1] = Cprim[1];
    CStrct->evec[1] = evec[1];
    CStrct->Poff[2] = Poff[2];
    CStrct->Aoff[2] = Aoff[2];
    CStrct->Uoff[2] = Uoff[2];
    CStrct->P0[2] = P0[2];
    CStrct->P1[2] = P1[2];
    CStrct->A0[2] = A0[2];
    CStrct->A1[2] = A1[2];
    CStrct->U0[2] = U0[2];
    CStrct->U1[2] = U1[2];
    CStrct->CorrectedHelixCenter[2] = Cprim[2];
    CStrct->evec[2] = evec[2];
    CStrct->theta = theta;
    CStrct->pitch = pitch;
    for (int i{0}; i < 6; i++) {
        CStrct->CoeffP5[i][0] = CoeffP5[i][0];
        CStrct->CoeffP5[i][1] = CoeffP5[i][1];
        CStrct->CoeffP5[i][2] = CoeffP5[i][2];
    }
    CStrct->sp_index = 1;
    CStrct->FeedRate = FeedRate;
    CStrct->SpindleSpeed = 0.0;
    CStrct->MaxConstantFeedRate = 0.0;
    CStrct->i_begin_sp = 0;
    CStrct->i_end_sp = 0;
    CStrct->gcode_source_line = 0;
    CStrct->index_smooth = 0;
    CStrct->UseConstJerk = false;
    CStrct->ConstJerk = 0.0;
    CStrct->ConstJerkMaxIterations = 0;
    CStrct->Coeff.set_size(0);
    CStrct->a_param = 1.0;
    CStrct->b_param = 0.0;
    cast(CStrct->sp.CoeffX, CStrct->sp.CoeffY, CStrct->sp.CoeffZ, &CStrct->sp.Bl.ncoeff,
         CStrct->sp.Bl.breakpoints, &CStrct->sp.Bl.handle, &CStrct->sp.Bl.degree, CStrct->sp.knots);
}

} // namespace ocn

//
// File trailer for ConstrCurvStruct.cpp
//
// [EOF]
//
