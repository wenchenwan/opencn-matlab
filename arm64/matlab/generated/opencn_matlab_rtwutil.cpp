//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_rtwutil.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 24-Feb-2022 11:52:48
//

// Include Files
#include "opencn_matlab_rtwutil.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types21.h"
#include "coder_array.h"
#include <algorithm>

// Function Definitions
//
// Arguments    : const c_struct_T *r
//                CurvStruct *r1
// Return Type  : void
//
namespace ocn {
void cast(const c_struct_T *r, CurvStruct *r1)
{
    r1->Type = r->Type;
    r1->zspdmode = r->zspdmode;
    r1->TRAFO = r->TRAFO;
    r1->HSC = r->HSC;
    std::copy(&r->HSC_cmd[0], &r->HSC_cmd[256], &r1->HSC_cmd[0]);
    r1->Doff = r->Doff;
    r1->delta = r->delta;
    r1->Poff[0] = r->Poff[0];
    r1->Aoff[0] = r->Aoff[0];
    r1->Uoff[0] = r->Uoff[0];
    r1->P0[0] = r->P0[0];
    r1->P1[0] = r->P1[0];
    r1->A0[0] = r->A0[0];
    r1->A1[0] = r->A1[0];
    r1->U0[0] = r->U0[0];
    r1->U1[0] = r->U1[0];
    r1->CorrectedHelixCenter[0] = r->CorrectedHelixCenter[0];
    r1->evec[0] = r->evec[0];
    r1->Poff[1] = r->Poff[1];
    r1->Aoff[1] = r->Aoff[1];
    r1->Uoff[1] = r->Uoff[1];
    r1->P0[1] = r->P0[1];
    r1->P1[1] = r->P1[1];
    r1->A0[1] = r->A0[1];
    r1->A1[1] = r->A1[1];
    r1->U0[1] = r->U0[1];
    r1->U1[1] = r->U1[1];
    r1->CorrectedHelixCenter[1] = r->CorrectedHelixCenter[1];
    r1->evec[1] = r->evec[1];
    r1->Poff[2] = r->Poff[2];
    r1->Aoff[2] = r->Aoff[2];
    r1->Uoff[2] = r->Uoff[2];
    r1->P0[2] = r->P0[2];
    r1->P1[2] = r->P1[2];
    r1->A0[2] = r->A0[2];
    r1->A1[2] = r->A1[2];
    r1->U0[2] = r->U0[2];
    r1->U1[2] = r->U1[2];
    r1->CorrectedHelixCenter[2] = r->CorrectedHelixCenter[2];
    r1->evec[2] = r->evec[2];
    r1->theta = r->theta;
    r1->pitch = r->pitch;
    for (int i{0}; i < 6; i++) {
        r1->CoeffP5[i][0] = r->CoeffP5[i][0];
        r1->CoeffP5[i][1] = r->CoeffP5[i][1];
        r1->CoeffP5[i][2] = r->CoeffP5[i][2];
    }
    r1->sp_index = r->sp_index;
    r1->FeedRate = r->FeedRate;
    r1->SpindleSpeed = r->SpindleSpeed;
    r1->MaxConstantFeedRate = r->MaxConstantFeedRate;
    r1->i_begin_sp = r->i_begin_sp;
    r1->i_end_sp = r->i_end_sp;
    r1->gcode_source_line = r->gcode_source_line;
    r1->index_smooth = r->index_smooth;
    r1->UseConstJerk = r->UseConstJerk;
    r1->ConstJerk = r->ConstJerk;
    r1->ConstJerkMaxIterations = r->ConstJerkMaxIterations;
    r1->Coeff.set_size(0);
    r1->a_param = r->a_param;
    r1->b_param = r->b_param;
    r1->sp.CoeffX.set_size(1, 1);
    r1->sp.CoeffX[0] = r->sp.CoeffX;
    r1->sp.CoeffY.set_size(1, 1);
    r1->sp.CoeffY[0] = r->sp.CoeffY;
    r1->sp.CoeffZ.set_size(1, 1);
    r1->sp.CoeffZ[0] = r->sp.CoeffZ;
    r1->sp.Bl.ncoeff = r->sp.Bl.ncoeff;
    r1->sp.Bl.breakpoints.set_size(1, 0);
    r1->sp.Bl.handle = r->sp.Bl.handle;
    r1->sp.Bl.degree = r->sp.Bl.degree;
    r1->sp.knots.set_size(1, 1);
    r1->sp.knots[0] = r->sp.knots;
    r1->sp.Ltot = r->sp.Ltot;
    r1->sp.Lk.set_size(1, 1);
    r1->sp.Lk[0] = r->sp.Lk;
}

} // namespace ocn

//
// File trailer for opencn_matlab_rtwutil.cpp
//
// [EOF]
//
