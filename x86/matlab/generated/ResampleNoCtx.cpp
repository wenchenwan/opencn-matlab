//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleNoCtx.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 14-Jul-2021 15:10:03
//

// Include Files
#include "ResampleNoCtx.h"
#include "ResampleStateClass.h"
#include "bspline_eval.h"
#include "c_assert.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_initialize.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
namespace ocn {
static void Resample(ZSpdMode CurOptStruct_zspdmode, bool CurOptStruct_UseConstJerk,
                     double CurOptStruct_ConstJerk,
                     const ::coder::array<double, 1U> &CurOptStruct_Coeff, unsigned long Bl_handle,
                     double u, double dt, double *ukp1, double *qk, double *dk);

static void ResampleNN(bool CurOptStruct_UseConstJerk,
                       const ::coder::array<double, 1U> &CurOptStruct_Coeff,
                       unsigned long Bl_handle, double u, double dt, double *ukp1, double *qk,
                       double *dk);

static void ResampleNZ(bool CurOptStruct_UseConstJerk, double CurOptStruct_ConstJerk, double u,
                       double dt, double *ukp1, double *qk, double *dk);

static void ResampleZN(bool CurOptStruct_UseConstJerk, double CurOptStruct_ConstJerk, double u,
                       double dt, double *ukp1, double *qk, double *dk);

} // namespace ocn

// Function Definitions
//
// Arguments    : ZSpdMode CurOptStruct_zspdmode
//                bool CurOptStruct_UseConstJerk
//                double CurOptStruct_ConstJerk
//                const ::coder::array<double, 1U> &CurOptStruct_Coeff
//                unsigned long Bl_handle
//                double u
//                double dt
//                double *ukp1
//                double *qk
//                double *dk
// Return Type  : void
//
namespace ocn {
static void Resample(ZSpdMode CurOptStruct_zspdmode, bool CurOptStruct_UseConstJerk,
                     double CurOptStruct_ConstJerk,
                     const ::coder::array<double, 1U> &CurOptStruct_Coeff, unsigned long Bl_handle,
                     double u, double dt, double *ukp1, double *qk, double *dk)
{
    if (CurOptStruct_zspdmode == ZSpdMode_ZN) {
        ResampleZN(CurOptStruct_UseConstJerk, CurOptStruct_ConstJerk, u, dt, ukp1, qk, dk);
    } else if (CurOptStruct_zspdmode == ZSpdMode_NN) {
        ResampleNN(CurOptStruct_UseConstJerk, CurOptStruct_Coeff, Bl_handle, u, dt, ukp1, qk, dk);
    } else if (CurOptStruct_zspdmode == ZSpdMode_NZ) {
        ResampleNZ(CurOptStruct_UseConstJerk, CurOptStruct_ConstJerk, u, dt, ukp1, qk, dk);
    }
}

//
// Arguments    : bool CurOptStruct_UseConstJerk
//                const ::coder::array<double, 1U> &CurOptStruct_Coeff
//                unsigned long Bl_handle
//                double u
//                double dt
//                double *ukp1
//                double *qk
//                double *dk
// Return Type  : void
//
static void ResampleNN(bool CurOptStruct_UseConstJerk,
                       const ::coder::array<double, 1U> &CurOptStruct_Coeff,
                       unsigned long Bl_handle, double u, double dt, double *ukp1, double *qk,
                       double *dk)
{
    ::coder::array<double, 2U> b_CurOptStruct_Coeff;
    double a__4;
    double b_dk;
    double b_qk;
    int loop_ub;
    f_c_assert(!CurOptStruct_UseConstJerk);
    b_qk = u;
    b_CurOptStruct_Coeff.set_size(1, CurOptStruct_Coeff.size(0));
    loop_ub = CurOptStruct_Coeff.size(0);
    for (int i{0}; i < loop_ub; i++) {
        b_CurOptStruct_Coeff[i] = CurOptStruct_Coeff[i];
    }
    bspline_eval(Bl_handle, b_CurOptStruct_Coeff, &b_qk, &b_dk, &a__4);
    *qk = b_qk;
    *dk = b_dk;
    sqrt_calls++;
    *ukp1 = (u + b_dk * std::pow(dt, 2.0) / 4.0) + std::sqrt(b_qk) * dt;
}

//
// Arguments    : bool CurOptStruct_UseConstJerk
//                double CurOptStruct_ConstJerk
//                double u
//                double dt
//                double *ukp1
//                double *qk
//                double *dk
// Return Type  : void
//
static void ResampleNZ(bool CurOptStruct_UseConstJerk, double CurOptStruct_ConstJerk, double u,
                       double dt, double *ukp1, double *qk, double *dk)
{
    double t;
    g_c_assert(CurOptStruct_UseConstJerk);
    t = std::pow(6.0 * (1.0 - u) / CurOptStruct_ConstJerk, 0.33333333333333331);
    *qk = std::pow(CurOptStruct_ConstJerk * std::pow(t, 2.0) / 2.0, 2.0);
    *dk = -2.0 * CurOptStruct_ConstJerk * t;
    *ukp1 = 1.0 - CurOptStruct_ConstJerk * std::pow(t - dt, 3.0) / 6.0;
}

//
// Arguments    : bool CurOptStruct_UseConstJerk
//                double CurOptStruct_ConstJerk
//                double u
//                double dt
//                double *ukp1
//                double *qk
//                double *dk
// Return Type  : void
//
static void ResampleZN(bool CurOptStruct_UseConstJerk, double CurOptStruct_ConstJerk, double u,
                       double dt, double *ukp1, double *qk, double *dk)
{
    double t;
    e_c_assert(CurOptStruct_UseConstJerk);
    t = std::pow(6.0 * u / CurOptStruct_ConstJerk, 0.33333333333333331);
    if (dt > 0.0) {
        t = std::round(t / dt) * dt;
    }
    *qk = std::pow(CurOptStruct_ConstJerk * std::pow(t, 2.0) / 2.0, 2.0);
    *dk = 2.0 * CurOptStruct_ConstJerk * t;
    *ukp1 = CurOptStruct_ConstJerk * std::pow(t + dt, 3.0) / 6.0;
}

//
// Arguments    : ResampleStateClass *state
//                const SplineBase *Bl
//                const CurvStruct *Curv
// Return Type  : void
//
void ResampleNoCtx(ResampleStateClass *state, const SplineBase *Bl, const CurvStruct *Curv)
{
    double a__1;
    double a__2;
    double a__3;
    double b_ukp1;
    double qk;
    double ukp1;
    double y;
    if (!isInitialized_sinspace) {
        sinspace_initialize();
    }
    Resample(Curv->zspdmode, Curv->UseConstJerk, Curv->ConstJerk, Curv->Coeff, Bl->handle, state->u,
             state->dt, &ukp1, &qk, &a__1);
    b_ukp1 = ukp1;
    if (ukp1 < state->u) {
        b_ukp1 = 1.0;
    }
    if (b_ukp1 - state->u < 2.2204460492503131E-16) {
        b_ukp1 = state->u + 2.2204460492503131E-16;
    }
    if (b_ukp1 < 1.0) {
        state->set_u(b_ukp1);
    } else {
        double Trest;
        double dt_begin;
        Resample(Curv->zspdmode, Curv->UseConstJerk, Curv->ConstJerk, Curv->Coeff, Bl->handle, 1.0,
                 state->dt, &a__2, &y, &a__3);
        y = std::sqrt(y);
        sqrt_calls++;
        sqrt_calls++;
        Trest = 2.0 * (1.0 - state->u) / (y + std::sqrt(qk));
        if (Trest > state->dt) {
            dt_begin = 0.0;
        } else {
            dt_begin = state->dt - Trest;
        }
        state->set_u();
        state->b_set_go_next();
        state->set_dt(dt_begin);
        //  This recursive call was replaced by the 'again' output params
        //  Callers should make sure to use them
        //     ctx = ResampleTick(ctx, dt_begin);
    }
}

} // namespace ocn

//
// File trailer for ResampleNoCtx.cpp
//
// [EOF]
//
