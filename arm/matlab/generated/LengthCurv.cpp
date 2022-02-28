//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: LengthCurv.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 28-Feb-2022 15:00:32
//

// Include Files
#include "LengthCurv.h"
#include "EvalCurvStruct.h"
#include "SplineLengthApproxGL_bounds.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "queue_coder.h"
#include <cmath>

// Function Definitions
//
// function L = LengthCurv(ctx, Curv, u0, u1)
//
// Arguments    : const queue_coder *ctx_q_splines
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                const CurvStruct *Curv
// Return Type  : double
//
namespace ocn {
double LengthCurv(const queue_coder *ctx_q_splines, const double ctx_cfg_GaussLegendreX[5],
                  const double ctx_cfg_GaussLegendreW[5], const CurvStruct *Curv)
{
    static const double a[9]{
        0.055555555555555552, 0.16666666666666666, 0.27777777777777779, 0.38888888888888884, 0.5,
        0.61111111111111116,  0.7222222222222221,  0.83333333333333326, 0.94444444444444442};
    static const char b_message[29]{'B', 'A', 'D', ' ', 'C', 'U', 'R', 'V', 'E', ' ',
                                    'T', 'Y', 'P', 'E', ' ', 'I', 'N', ' ', 'L', 'E',
                                    'N', 'G', 'T', 'H', ' ', 'C', 'U', 'R', 'V'};
    double y[9][3];
    double p5_1D[5][3];
    double Integrand[9];
    double b_y1[9];
    double x[9];
    double a__1[3];
    double a__2[3];
    double a__3[3];
    double r1D[3];
    double L;
    char message[29];
    // 'LengthCurv:3' if (Curv.Type == CurveType.Helix) || (Curv.Type == CurveType.Line)
    if ((Curv->Type == CurveType_Helix) || (Curv->Type == CurveType_Line)) {
        // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct(ctx, Curv, u0);
        b_EvalCurvStruct(Curv->Type, Curv->P0, Curv->P1, Curv->CorrectedHelixCenter, Curv->evec,
                         Curv->theta, Curv->pitch, Curv->a_param, Curv->b_param, a__1, r1D, a__2,
                         a__3);
        // 'LengthCurv:5' L = MyNorm(r1D)*(u1-u0);
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        L = std::sqrt((std::pow(r1D[0], 2.0) + std::pow(r1D[1], 2.0)) + std::pow(r1D[2], 2.0));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
    } else if (Curv->Type == CurveType_Spline) {
        // 'LengthCurv:6' elseif Curv.Type == CurveType.Spline
        // 'LengthCurv:7' a = Curv.a_param;
        // 'LengthCurv:8' b = Curv.b_param;
        // 'LengthCurv:9' u0_tilda = a*u0+b;
        // 'LengthCurv:10' u1_tilda = a*u1+b;
        // 'LengthCurv:11' L = SplineLengthApproxGL_bounds(ctx, Curv, u0_tilda, u1_tilda);
        L = SplineLengthApproxGL_bounds(ctx_q_splines, ctx_cfg_GaussLegendreX,
                                        ctx_cfg_GaussLegendreW, Curv->sp_index, Curv->b_param,
                                        Curv->a_param + Curv->b_param);
    } else if (Curv->Type == CurveType_TransP5) {
        double b_y;
        double d;
        double d1;
        double d2;
        double work;
        int ixLead;
        // 'LengthCurv:12' elseif Curv.Type == CurveType.TransP5
        // 'LengthCurv:13' L = TransP5LengthApprox(Curv);
        //  Computes approximately the arc length of a parametric spline
        // 'TransP5LengthApprox:3' p5    = CurvStruct.CoeffP5;
        // 'TransP5LengthApprox:4' p5_1D = mypolyder(p5);
        // MYPOLYDER Differentiate polynomial.
        //
        // u  = u(:).';
        // 'mypolyder:5' [nD, nu] = size(u);
        // 'mypolyder:6' if nu < 2
        // 'mypolyder:8' else
        // 'mypolyder:9' a = u(:, 1:nu-1) .* repmat(nu-1:-1:1, nD, 1);
        for (int k{0}; k < 5; k++) {
            p5_1D[k][0] = Curv->CoeffP5[k][0] * (5.0 - static_cast<double>(k));
            p5_1D[k][1] = Curv->CoeffP5[k][1] * (5.0 - static_cast<double>(k));
            p5_1D[k][2] = Curv->CoeffP5[k][2] * (5.0 - static_cast<double>(k));
        }
        //  Derivative
        // 'TransP5LengthApprox:5' u_vec     = linspace(0,1,10);
        // 'TransP5LengthApprox:6' u_mid     = 0.5*(u_vec(1:end-1) +u_vec(2:end));
        //  Midpoint values
        // 'TransP5LengthApprox:7' du        = diff(u_vec);
        ixLead = 1;
        work = 0.0;
        // 'TransP5LengthApprox:8' Integrand = mysqrt(sum(mypolyval(p5_1D, u_mid).^2));
        // POLYVAL Evaluate array of polynomials with same degree.
        //
        // 'mypolyval:4' [nD, nc] = size(p);
        // 'mypolyval:5' siz_x    = length(x);
        //
        //  Use Horner's method for general case where X is an array.
        // 'mypolyval:8' y = zeros(nD, siz_x);
        // 'mypolyval:9' if nc > 0
        // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
        d = p5_1D[0][0];
        d1 = p5_1D[0][1];
        d2 = p5_1D[0][2];
        for (int t{0}; t < 9; t++) {
            double tmp2;
            double work_tmp;
            tmp2 = work;
            work_tmp = 0.1111111111111111 * static_cast<double>(ixLead);
            work = work_tmp;
            b_y1[t] = work_tmp - tmp2;
            ixLead++;
            y[t][0] = d;
            y[t][1] = d1;
            y[t][2] = d2;
        }
        // 'mypolyval:12' for i=2:nc
        for (int b_i{0}; b_i < 4; b_i++) {
            double d3;
            double d4;
            double d5;
            // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
            d3 = p5_1D[b_i + 1][0];
            d4 = p5_1D[b_i + 1][1];
            d5 = p5_1D[b_i + 1][2];
            for (int c_k{0}; c_k < 9; c_k++) {
                double d6;
                d6 = a[c_k];
                y[c_k][0] = d6 * y[c_k][0] + d3;
                y[c_k][1] = d6 * y[c_k][1] + d4;
                y[c_k][2] = d6 * y[c_k][2] + d5;
            }
        }
        for (int b_k{0}; b_k < 9; b_k++) {
            Integrand[b_k] = std::pow(y[b_k][0], 2.0);
            Integrand[b_k] += std::pow(y[b_k][1], 2.0);
            Integrand[b_k] += std::pow(y[b_k][2], 2.0);
        }
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'TransP5LengthApprox:9' L         = sum(Integrand.*du);
        for (int d_k{0}; d_k < 9; d_k++) {
            double d7;
            d7 = std::sqrt(Integrand[d_k]);
            Integrand[d_k] = d7;
            x[d_k] = d7 * b_y1[d_k];
        }
        b_y = x[0];
        for (int e_k{0}; e_k < 8; e_k++) {
            b_y += x[e_k + 1];
        }
        L = b_y;
    } else {
        // 'LengthCurv:14' else
        // 'LengthCurv:15' c_assert(false, 'BAD CURVE TYPE IN LENGTH CURV');
        // 'c_assert:2' if coder.target('rtw')
        // 'c_assert:3' if ~condition
        // 'c_assert:4' coder.ceval('c_assert_', message);
        for (int i{0}; i < 29; i++) {
            message[i] = b_message[i];
        }
        c_assert_(&message[0]);
        // 'c_assert:6' value = condition;
        // 'LengthCurv:16' L = 0;
        L = 0.0;
    }
    return L;
}

} // namespace ocn

//
// File trailer for LengthCurv.cpp
//
// [EOF]
//
