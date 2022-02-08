//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CalcVAJ_v5.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "CalcVAJ_v5.h"
#include "EvalCurvStruct.h"
#include "bspline_eval.h"
#include "queue_coder.h"
#include "sinspace_data.h"
#include "sinspace_types2.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// import splines.*
//
//  Ntot = 0;
//  for k = 1:Ncrv
//      Ntot = Ntot + size(u_cell{k}, 2);
//  end
//
// Arguments    : const queue_coder *ctx_q_splines
//                CurveType CurvStructs_Type
//                ZSpdMode CurvStructs_zspdmode
//                const double CurvStructs_P0[3]
//                const double CurvStructs_P1[3]
//                const double CurvStructs_CorrectedHelixCenter[3]
//                const double CurvStructs_evec[3]
//                double CurvStructs_theta
//                double CurvStructs_pitch
//                const double CurvStructs_CoeffP5[6][3]
//                int CurvStructs_sp_index
//                double CurvStructs_ConstJerk
//                double CurvStructs_a_param
//                double CurvStructs_b_param
//                unsigned long Bl_handle
//                const ::coder::array<double, 1U> &Coeff
//                double *v_norm
//                double a[3]
// Return Type  : void
//
namespace ocn {
void CalcVAJ_v5(const queue_coder *ctx_q_splines, CurveType CurvStructs_Type,
                ZSpdMode CurvStructs_zspdmode, const double CurvStructs_P0[3],
                const double CurvStructs_P1[3], const double CurvStructs_CorrectedHelixCenter[3],
                const double CurvStructs_evec[3], double CurvStructs_theta,
                double CurvStructs_pitch, const double CurvStructs_CoeffP5[6][3],
                int CurvStructs_sp_index, double CurvStructs_ConstJerk, double CurvStructs_a_param,
                double CurvStructs_b_param, unsigned long Bl_handle,
                const ::coder::array<double, 1U> &Coeff, double *v_norm, double a[3])
{
    __m128d r;
    __m128d r1;
    ::coder::array<double, 2U> b_Coeff;
    double a__1[3];
    double r1D[3];
    double r2D[3];
    double r3D[3];
    double qD_val;
    double q_val;
    double v3;
    //  v_norm = [];
    //  a = [];
    //  j = [];
    //
    //      qSpl = Function(Bl, Coeff(:, k));
    //
    c_EvalCurvStruct(ctx_q_splines, CurvStructs_Type, CurvStructs_P0, CurvStructs_P1,
                     CurvStructs_CorrectedHelixCenter, CurvStructs_evec, CurvStructs_theta,
                     CurvStructs_pitch, CurvStructs_CoeffP5, CurvStructs_sp_index,
                     CurvStructs_a_param, CurvStructs_b_param, a__1, r1D, r2D, r3D);
    sqrt_calls++;
    //  norm
    //
    //      q_val   = qSpl.fast_eval(u_vec);
    //      qD_val  = qSpl.derivative.fast_eval(u_vec);
    //      qDD_val = qSpl.derivative(2).fast_eval(u_vec);
    //  TODO: Optimize this with a single call to eval, and maybe a basis
    //  precompute?
    if (CurvStructs_zspdmode == ZSpdMode_ZN) {
        double b_a;
        double t;
        t = std::pow(6.0 / CurvStructs_ConstJerk, 0.33333333333333331);
        b_a = CurvStructs_ConstJerk * (t * t) / 2.0;
        q_val = b_a * b_a;
        qD_val = 2.0 * CurvStructs_ConstJerk * t;
    } else if (CurvStructs_zspdmode == ZSpdMode_NZ) {
        double c_a;
        double t;
        t = std::pow(0.0 / CurvStructs_ConstJerk, 0.33333333333333331);
        c_a = CurvStructs_ConstJerk * (t * t) / 2.0;
        q_val = c_a * c_a;
        qD_val = -2.0 * CurvStructs_ConstJerk * t;
    } else if (!(CurvStructs_zspdmode == ZSpdMode_ZZ)) {
        int loop_ub;
        //  ZSpdMode.NN
        q_val = 1.0;
        loop_ub = Coeff.size(0);
        b_Coeff.set_size(1, Coeff.size(0));
        for (int i{0}; i < loop_ub; i++) {
            b_Coeff[i] = Coeff[i];
        }
        bspline_eval(Bl_handle, b_Coeff, &q_val, &qD_val, &v3);
    }
    sqrt_calls++;
    *v_norm = std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0)) *
              std::sqrt(q_val);
    r = _mm_loadu_pd(&r1D[0]);
    r1 = _mm_loadu_pd(&r2D[0]);
    _mm_storeu_pd(&a[0],
                  _mm_add_pd(_mm_mul_pd(r1, _mm_set1_pd(q_val)),
                             _mm_mul_pd(_mm_set1_pd(0.5), _mm_mul_pd(r, _mm_set1_pd(qD_val)))));
    a[2] = r2D[2] * q_val + 0.5 * (r1D[2] * qD_val);
    sqrt_calls++;
    sqrt_calls++;
    // zeros(3, size(tmp2, 2));
}

} // namespace ocn

//
// File trailer for CalcVAJ_v5.cpp
//
// [EOF]
//
