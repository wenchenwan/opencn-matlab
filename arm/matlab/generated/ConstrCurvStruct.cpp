//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ConstrCurvStruct.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:54:59
//

// Include Files
#include "ConstrCurvStruct.h"
#include "sinspace_types1.h"
#include "sinspace_types11.h"
#include "sinspace_types2.h"
#include "sinspace_types3.h"
#include "coder_array.h"

// Function Declarations
namespace ocn {
static void cast(::coder::array<double, 2U> &t1_CoeffX, ::coder::array<double, 2U> &t1_CoeffY,
                 ::coder::array<double, 2U> &t1_CoeffZ, SplineBase *t1_Bl,
                 ::coder::array<double, 2U> &t1_knots, double *t1_Ltot,
                 ::coder::array<double, 2U> &t1_Lk);

static void cast(::coder::array<double, 2U> &r);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &t1_CoeffX
//                ::coder::array<double, 2U> &t1_CoeffY
//                ::coder::array<double, 2U> &t1_CoeffZ
//                SplineBase *t1_Bl
//                ::coder::array<double, 2U> &t1_knots
//                double *t1_Ltot
//                ::coder::array<double, 2U> &t1_Lk
// Return Type  : void
//
namespace ocn {
static void cast(::coder::array<double, 2U> &t1_CoeffX, ::coder::array<double, 2U> &t1_CoeffY,
                 ::coder::array<double, 2U> &t1_CoeffZ, SplineBase *t1_Bl,
                 ::coder::array<double, 2U> &t1_knots, double *t1_Ltot,
                 ::coder::array<double, 2U> &t1_Lk)
{
    static const uint64m_T r{
        {0U, 0U} // chunks
    };
    cast(t1_CoeffX);
    cast(t1_CoeffY);
    cast(t1_CoeffZ);
    t1_Bl->ncoeff = 0;
    t1_Bl->breakpoints.set_size(1, 0);
    t1_Bl->handle = r;
    t1_Bl->degree = 0;
    cast(t1_knots);
    cast(t1_Lk);
    *t1_Ltot = 0.0;
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
    cast(CStrct->sp.CoeffX, CStrct->sp.CoeffY, CStrct->sp.CoeffZ, &CStrct->sp.Bl, CStrct->sp.knots,
         &CStrct->sp.Ltot, CStrct->sp.Lk);
}

} // namespace ocn

//
// File trailer for ConstrCurvStruct.cpp
//
// [EOF]
//
