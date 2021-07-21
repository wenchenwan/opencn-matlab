//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStruct.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "ConstrCurvStruct.h"
#include "queue_coder.h"
#include "coder_array.h"

// Function Declarations
namespace ocn {
static void cast(double t0_CoeffX, double t0_CoeffY, double t0_CoeffZ, int t0_Bl_ncoeff,
                 unsigned long t0_Bl_handle, int t0_Bl_degree, double t0_knots,
                 ::coder::array<double, 2U> &t1_CoeffX, ::coder::array<double, 2U> &t1_CoeffY,
                 ::coder::array<double, 2U> &t1_CoeffZ, int *t1_Bl_ncoeff,
                 ::coder::array<double, 2U> &t1_Bl_breakpoints, unsigned long *t1_Bl_handle,
                 int *t1_Bl_degree, ::coder::array<double, 2U> &t1_knots);

static void cast(double b, ::coder::array<double, 2U> &c);

} // namespace ocn

// Function Definitions
//
// Arguments    : double t0_CoeffX
//                double t0_CoeffY
//                double t0_CoeffZ
//                int t0_Bl_ncoeff
//                unsigned long t0_Bl_handle
//                int t0_Bl_degree
//                double t0_knots
//                ::coder::array<double, 2U> &t1_CoeffX
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
static void cast(double t0_CoeffX, double t0_CoeffY, double t0_CoeffZ, int t0_Bl_ncoeff,
                 unsigned long t0_Bl_handle, int t0_Bl_degree, double t0_knots,
                 ::coder::array<double, 2U> &t1_CoeffX, ::coder::array<double, 2U> &t1_CoeffY,
                 ::coder::array<double, 2U> &t1_CoeffZ, int *t1_Bl_ncoeff,
                 ::coder::array<double, 2U> &t1_Bl_breakpoints, unsigned long *t1_Bl_handle,
                 int *t1_Bl_degree, ::coder::array<double, 2U> &t1_knots)
{
    cast(t0_CoeffX, t1_CoeffX);
    cast(t0_CoeffY, t1_CoeffY);
    cast(t0_CoeffZ, t1_CoeffZ);
    t1_Bl_breakpoints.set_size(1, 0);
    cast(t0_knots, t1_knots);
    *t1_Bl_ncoeff = t0_Bl_ncoeff;
    *t1_Bl_handle = t0_Bl_handle;
    *t1_Bl_degree = t0_Bl_degree;
}

//
// Arguments    : double b
//                ::coder::array<double, 2U> &c
// Return Type  : void
//
static void cast(double b, ::coder::array<double, 2U> &c)
{
    c.set_size(1, 1);
    c[0] = b;
}

//
// ctxType = coder.OutputType('InitFeedoptPlan');
//
// Arguments    : CurveType Type
//                ZSpdMode b_ZSpdMode
//                const double P0[3]
//                const double P1[3]
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
void ConstrCurvStruct(CurveType Type, ZSpdMode b_ZSpdMode, const double P0[3], const double P1[3],
                      const double Cprim[3], double delta, const double evec[3], double theta,
                      double pitch, const double CoeffP5[6][3], double FeedRate, CurvStruct *CStrct)
{
    CStrct->Type = Type;
    CStrct->zspdmode = b_ZSpdMode;
    CStrct->delta = delta;
    CStrct->P0[0] = P0[0];
    CStrct->P1[0] = P1[0];
    CStrct->CorrectedHelixCenter[0] = Cprim[0];
    CStrct->evec[0] = evec[0];
    CStrct->P0[1] = P0[1];
    CStrct->P1[1] = P1[1];
    CStrct->CorrectedHelixCenter[1] = Cprim[1];
    CStrct->evec[1] = evec[1];
    CStrct->P0[2] = P0[2];
    CStrct->P1[2] = P1[2];
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
    cast(0.0, 0.0, 0.0, 0, 0UL, 0, 0.0, CStrct->sp.CoeffX, CStrct->sp.CoeffY, CStrct->sp.CoeffZ,
         &CStrct->sp.Bl.ncoeff, CStrct->sp.Bl.breakpoints, &CStrct->sp.Bl.handle,
         &CStrct->sp.Bl.degree, CStrct->sp.knots);
}

} // namespace ocn

//
// File trailer for ConstrCurvStruct.cpp
//
// [EOF]
//
