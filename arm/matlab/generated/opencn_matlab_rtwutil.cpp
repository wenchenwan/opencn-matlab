//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: opencn_matlab_rtwutil.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 24-Feb-2022 11:48:06
//

// Include Files
#include "opencn_matlab_rtwutil.h"
#include "opencn_matlab_types.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "coder_array.h"
#include <algorithm>
#include <cmath>
#include <math.h>

// Function Definitions
//
// Arguments    : double u1
//                unsigned int y[]
// Return Type  : void
//
namespace ocn {
void Double2MultiWord(double u1, unsigned int y[])
{
    double b_y0;
    double b_yn;
    int cb;
    int currExp;
    int i;
    int msl;
    int prevExp;
    bool isNegative;
    isNegative = (u1 < 0.0);
    b_yn = frexp(u1, &currExp);
    if (currExp <= 0) {
        msl = -1;
    } else {
        msl = (currExp - 1) / 32;
    }
    cb = 1;
    for (i = msl + 1; i < 2; i++) {
        y[i] = 0U;
    }
    if (isNegative) {
        b_y0 = -b_yn;
    } else {
        b_y0 = b_yn;
    }
    prevExp = 32 * msl;
    for (i = msl; i >= 0; i--) {
        double yd;
        b_y0 = std::ldexp(b_y0, currExp - prevExp);
        yd = std::floor(b_y0);
        b_y0 -= yd;
        if (i < 2) {
            y[i] = static_cast<unsigned int>(yd);
        }
        currExp = prevExp;
        prevExp -= 32;
    }
    if (isNegative) {
        for (i = 0; i < 2; i++) {
            unsigned int u1i;
            unsigned int yi;
            u1i = ~y[i];
            yi = u1i + cb;
            y[i] = yi;
            cb = (yi < u1i);
        }
    }
}

//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
//                unsigned int y[]
// Return Type  : void
//
void MultiWordAdd(const unsigned int u1[], const unsigned int u2[], unsigned int y[])
{
    int carry{0};
    for (int i{0}; i < 2; i++) {
        unsigned int u1i;
        unsigned int yi;
        u1i = u1[i];
        yi = (u1i + u2[i]) + carry;
        y[i] = yi;
        if (static_cast<unsigned int>(carry) != 0U) {
            carry = (yi <= u1i);
        } else {
            carry = (yi < u1i);
        }
    }
}

//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
//                unsigned int y[]
// Return Type  : void
//
void MultiWordAnd(const unsigned int u1[], const unsigned int u2[], unsigned int y[])
{
    for (int i{0}; i < 2; i++) {
        y[i] = u1[i] & u2[i];
    }
}

//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
//                unsigned int y[]
// Return Type  : void
//
void MultiWordSub(const unsigned int u1[], const unsigned int u2[], unsigned int y[])
{
    int borrow{0};
    for (int i{0}; i < 2; i++) {
        unsigned int u1i;
        unsigned int yi;
        u1i = u1[i];
        yi = (u1i - u2[i]) - borrow;
        y[i] = yi;
        if (static_cast<unsigned int>(borrow) != 0U) {
            borrow = (yi >= u1i);
        } else {
            borrow = (yi > u1i);
        }
    }
}

//
// Arguments    : const c_struct_T *r
//                CurvStruct *r1
// Return Type  : void
//
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

//
// Arguments    : int u
//                unsigned int y[]
// Return Type  : void
//
void sLong2MultiWord(int u, unsigned int y[])
{
    y[0] = static_cast<unsigned int>(u);
    if (u < 0) {
        y[1] = MAX_uint32_T;
    } else {
        y[1] = 0U;
    }
}

//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
// Return Type  : int
//
int uMultiWordCmp(const unsigned int u1[], const unsigned int u2[])
{
    int cmp;
    int i;
    cmp = 0;
    i = 2;
    while ((cmp == 0) && (i > 0)) {
        unsigned int u1i;
        unsigned int u2i;
        i--;
        u1i = u1[i];
        u2i = u2[i];
        if (u1i != u2i) {
            if (u1i > u2i) {
                cmp = 1;
            } else {
                cmp = -1;
            }
        }
    }
    return cmp;
}

//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
// Return Type  : bool
//
bool uMultiWordGe(const unsigned int u1[], const unsigned int u2[])
{
    return uMultiWordCmp(u1, u2) >= 0;
}

//
// Arguments    : const unsigned int u1[]
//                const unsigned int u2[]
// Return Type  : bool
//
bool uMultiWordNe(const unsigned int u1[], const unsigned int u2[])
{
    return uMultiWordCmp(u1, u2) != 0;
}

} // namespace ocn

//
// File trailer for opencn_matlab_rtwutil.cpp
//
// [EOF]
//
