//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ResampleNoCtx.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 24-Feb-2022 11:51:03
//

// Include Files
#include "ResampleNoCtx.h"
#include "ResampleStateClass.h"
#include "bspline_eval.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types11.h"
#include "opencn_matlab_types21.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
namespace ocn {
static void Resample(ZSpdMode CurOptStruct_zspdmode, bool CurOptStruct_UseConstJerk,
                     double CurOptStruct_ConstJerk,
                     const ::coder::array<double, 1U> &CurOptStruct_Coeff, unsigned long Bl_handle,
                     double u, double dt, double *ukp1, double *qk, double *dk);

}

// Function Definitions
//
// function [ukp1, qk, dk] = Resample(CurOptStruct, Bl, u, dt)
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
    static const char b_message[26]{'Z', 'N', ' ', 'i', 's', ' ', 'n', 'o', 't',
                                    ' ', 'u', 's', 'i', 'n', 'g', ' ', 'c', 'o',
                                    'n', 's', 't', ' ', 'j', 'e', 'r', 'k'};
    static const char e_message[26]{'N', 'Z', ' ', 'i', 's', ' ', 'n', 'o', 't',
                                    ' ', 'u', 's', 'i', 'n', 'g', ' ', 'c', 'o',
                                    'n', 's', 't', ' ', 'j', 'e', 'r', 'k'};
    static const char d_message[16]{'N', 'N', ' ', 'i', 's', ' ', 'u', 's',
                                    'i', 'n', 'g', ' ', 'j', 'e', 'r', 'k'};
    ::coder::array<double, 2U> b_CurOptStruct_Coeff;
    double a__4;
    double b_dk;
    double b_qk;
    char message[26];
    char c_message[16];
    // 'ResampleNoCtx:44' if CurOptStruct.zspdmode == ZSpdMode.ZN
    if (CurOptStruct_zspdmode == ZSpdMode_ZN) {
        double b_a;
        double t;
        // 'ResampleNoCtx:45' [ukp1,qk, dk] = ResampleZN(CurOptStruct, u, dt);
        // 'ResampleNoCtx:56' c_assert(CurOptStruct.UseConstJerk, 'ZN is not using const jerk');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        if (!CurOptStruct_UseConstJerk) {
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i{0}; i < 26; i++) {
                message[i] = b_message[i];
            }
            c_assert_(&message[0]);
        }
        // 'c_assert:6' value = condition;
        // 'ResampleNoCtx:58' t = (6*u/CurOptStruct.ConstJerk)^(1/3);
        t = std::pow(6.0 * u / CurOptStruct_ConstJerk, 0.33333333333333331);
        // 'ResampleNoCtx:59' if dt > 0
        if (dt > 0.0) {
            // 'ResampleNoCtx:60' t = round(t/dt)*dt;
            t = std::round(t / dt) * dt;
        }
        // 'ResampleNoCtx:62' qk = (CurOptStruct.ConstJerk*t^2/2)^2;
        b_a = CurOptStruct_ConstJerk * (t * t) / 2.0;
        *qk = b_a * b_a;
        // 'ResampleNoCtx:63' dk = 2*CurOptStruct.ConstJerk*t;
        *dk = 2.0 * CurOptStruct_ConstJerk * t;
        // 'ResampleNoCtx:65' ukp1 = CurOptStruct.ConstJerk.*(t+dt).^3/6;
        *ukp1 = CurOptStruct_ConstJerk * std::pow(t + dt, 3.0) / 6.0;
    } else if (CurOptStruct_zspdmode == ZSpdMode_NN) {
        int loop_ub;
        // 'ResampleNoCtx:46' elseif CurOptStruct.zspdmode == ZSpdMode.NN
        // 'ResampleNoCtx:47' [ukp1, qk, dk] = ResampleNN(CurOptStruct, Bl, u, dt);
        // 'ResampleNoCtx:69' c_assert(~CurOptStruct.UseConstJerk, 'NN is using jerk');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        if (CurOptStruct_UseConstJerk) {
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i1{0}; i1 < 16; i1++) {
                c_message[i1] = d_message[i1];
            }
            c_assert_(&c_message[0]);
        }
        // 'c_assert:6' value = condition;
        // 'ResampleNoCtx:71' uk = u;
        // 'ResampleNoCtx:72' [qk, dk, ~] = bspline_eval(Bl, CurOptStruct.Coeff', uk);
        b_qk = u;
        b_CurOptStruct_Coeff.set_size(1, CurOptStruct_Coeff.size(0));
        loop_ub = CurOptStruct_Coeff.size(0);
        for (int i3{0}; i3 < loop_ub; i3++) {
            b_CurOptStruct_Coeff[i3] = CurOptStruct_Coeff[i3];
        }
        bspline_eval(Bl_handle, b_CurOptStruct_Coeff, &b_qk, &b_dk, &a__4);
        *qk = b_qk;
        *dk = b_dk;
        // 'ResampleNoCtx:73' ukp1 = uk + dk*dt^2/4 + mysqrt(qk)*dt;
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        *ukp1 = (u + b_dk * (dt * dt) / 4.0) + std::sqrt(b_qk) * dt;
    } else if (CurOptStruct_zspdmode == ZSpdMode_NZ) {
        double a;
        double b_t;
        // 'ResampleNoCtx:48' elseif CurOptStruct.zspdmode == ZSpdMode.NZ
        // 'ResampleNoCtx:49' [ukp1, qk, dk] = ResampleNZ(CurOptStruct, u, dt);
        // 'ResampleNoCtx:77' c_assert(CurOptStruct.UseConstJerk, 'NZ is not using const jerk');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        if (!CurOptStruct_UseConstJerk) {
            // 'c_assert:4' coder.ceval('c_assert_', message);
            for (int i2{0}; i2 < 26; i2++) {
                message[i2] = e_message[i2];
            }
            c_assert_(&message[0]);
        }
        // 'c_assert:6' value = condition;
        // 'ResampleNoCtx:79' t = (6*(1-u)/CurOptStruct.ConstJerk)^(1/3);
        b_t = std::pow(6.0 * (1.0 - u) / CurOptStruct_ConstJerk, 0.33333333333333331);
        // 'ResampleNoCtx:81' qk = (CurOptStruct.ConstJerk*t^2/2)^2;
        a = CurOptStruct_ConstJerk * (b_t * b_t) / 2.0;
        *qk = a * a;
        // 'ResampleNoCtx:82' dk = -2*CurOptStruct.ConstJerk*t;
        *dk = -2.0 * CurOptStruct_ConstJerk * b_t;
        // 'ResampleNoCtx:84' ukp1 = 1 - CurOptStruct.ConstJerk.*(t-dt).^3/6;
        *ukp1 = 1.0 - CurOptStruct_ConstJerk * std::pow(b_t - dt, 3.0) / 6.0;
    } else {
        // 'ResampleNoCtx:50' else
        // 'ResampleNoCtx:51' error('Should not get here');
    }
}

//
// function state = ResampleNoCtx(state, Bl, Curv)
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
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'ResampleNoCtx:2' coder.inline("never");
    // 'ResampleNoCtx:4' [ukp1, qk, ~] = Resample(Curv, Bl, state.u, state.dt);
    Resample(Curv->zspdmode, Curv->UseConstJerk, Curv->ConstJerk, Curv->Coeff, Bl->handle, state->u,
             state->dt, &ukp1, &qk, &a__1);
    b_ukp1 = ukp1;
    // 'ResampleNoCtx:7' if ukp1 < state.u
    if (ukp1 < state->u) {
        // 'ResampleNoCtx:8' ukp1 = 1;
        b_ukp1 = 1.0;
    }
    // 'ResampleNoCtx:11' if ukp1 - state.u < eps
    if (b_ukp1 - state->u < 2.2204460492503131E-16) {
        // 'ResampleNoCtx:12' ukp1 = state.u + eps;
        b_ukp1 = state->u + 2.2204460492503131E-16;
    }
    // 'ResampleNoCtx:17' if ukp1 < 1
    if (b_ukp1 < 1.0) {
        // 'ResampleNoCtx:18' state.u = ukp1;
        state->u = b_ukp1;
        // 'ResampleStateClass:3' double
        // 'ResampleStateClass:3' u
    } else {
        double Trest;
        // 'ResampleNoCtx:19' else
        // 'ResampleNoCtx:20' ukp1      = 1;
        // 'ResampleNoCtx:22' [~, qkp1, ~] = Resample(Curv, Bl, ukp1, state.dt);
        Resample(Curv->zspdmode, Curv->UseConstJerk, Curv->ConstJerk, Curv->Coeff, Bl->handle, 1.0,
                 state->dt, &a__2, &y, &a__3);
        // 'ResampleNoCtx:23' Trest     = 2*(ukp1 - state.u) / (mysqrt(qkp1) + mysqrt(qk));
        // 'mysqrt:3' y = sqrt(x);
        y = std::sqrt(y);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        Trest = 2.0 * (1.0 - state->u) / (y + std::sqrt(qk));
        // 'ResampleNoCtx:25' if Trest > state.dt
        if (Trest > state->dt) {
            // 'ResampleNoCtx:26' dt_begin = 0;
            state->dt = 0.0;
        } else {
            // 'ResampleNoCtx:27' else
            // 'ResampleNoCtx:28' dt_begin  = state.dt - Trest;
            state->dt -= Trest;
        }
        // 'ResampleNoCtx:31' state.u = 0;
        state->u = 0.0;
        // 'ResampleNoCtx:32' state.go_next = true;
        state->go_next = true;
        // 'ResampleNoCtx:33' state.dt = dt_begin;
        // 'ResampleStateClass:5' double
        // 'ResampleStateClass:5' dt
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
