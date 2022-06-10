//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: LengthCurv.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

// Include Files
#include "LengthCurv.h"
#include "EvalCurvStruct.h"
#include "SplineLengthApproxGL_bounds.h"
#include "combineVectorElements.h"
#include "mypolyder.h"
#include "mypolyval.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// function L = LengthCurv(ctx, curv, u0, u1)
//
// Arguments    : const queue_coder *ctx_q_spline
//                int ctx_cfg_NumberAxis
//                int ctx_cfg_NCart
//                int ctx_cfg_NRot
//                const int ctx_cfg_indCart_data[]
//                int ctx_cfg_indCart_size
//                const int ctx_cfg_indRot_data[]
//                int ctx_cfg_indRot_size
//                const int ctx_cfg_indTot_data[]
//                int ctx_cfg_indTot_size
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                CurveType curv_Info_Type
//                const double curv_R0[6]
//                const double curv_R1[6]
//                const double curv_CorrectedHelixCenter[3]
//                const double curv_evec[3]
//                double curv_theta
//                double curv_pitch
//                const ::coder::array<double, 2U> &curv_CoeffP5
//                unsigned int curv_sp_index
//                double curv_a_param
//                double curv_b_param
// Return Type  : double
//
namespace ocn {
double LengthCurv(const queue_coder *ctx_q_spline, int ctx_cfg_NumberAxis, int ctx_cfg_NCart,
                  int ctx_cfg_NRot, const int ctx_cfg_indCart_data[], int ctx_cfg_indCart_size,
                  const int ctx_cfg_indRot_data[], int ctx_cfg_indRot_size,
                  const int ctx_cfg_indTot_data[], int ctx_cfg_indTot_size,
                  const double ctx_cfg_GaussLegendreX[5], const double ctx_cfg_GaussLegendreW[5],
                  CurveType curv_Info_Type, const double curv_R0[6], const double curv_R1[6],
                  const double curv_CorrectedHelixCenter[3], const double curv_evec[3],
                  double curv_theta, double curv_pitch,
                  const ::coder::array<double, 2U> &curv_CoeffP5, unsigned int curv_sp_index,
                  double curv_a_param, double curv_b_param)
{
    static const double a[9]{
        0.055555555555555552, 0.16666666666666666, 0.27777777777777779, 0.38888888888888884, 0.5,
        0.61111111111111116,  0.7222222222222221,  0.83333333333333326, 0.94444444444444442};
    static const char b_message[29]{'B', 'A', 'D', ' ', 'C', 'U', 'R', 'V', 'E', ' ',
                                    'T', 'Y', 'P', 'E', ' ', 'I', 'N', ' ', 'L', 'E',
                                    'N', 'G', 'T', 'H', ' ', 'C', 'U', 'R', 'V'};
    ::coder::array<double, 2U> p5_1D;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 2U> y;
    ::coder::array<double, 1U> a__1;
    ::coder::array<double, 1U> a__2;
    ::coder::array<double, 1U> a__3;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1D;
    ::coder::array<signed char, 2U> b;
    double Integrand[9];
    double b_y1[9];
    double x[9];
    double L;
    int xsubs_idx_1;
    short ysubs_idx_1;
    char message[29];
    // 'LengthCurv:3' if ( curv.Info.Type == CurveType.Helix ) || ( curv.Info.Type == CurveType.Line
    // )
    if ((curv_Info_Type == CurveType_Helix) || (curv_Info_Type == CurveType_Line)) {
        int loop_ub;
        // 'LengthCurv:4' [~, r1D, ~, ~] = EvalCurvStruct( ctx, curv, u0 );
        b_EvalCurvStruct(ctx_cfg_NumberAxis, ctx_cfg_NCart, ctx_cfg_NRot, ctx_cfg_indCart_data,
                         ctx_cfg_indCart_size, ctx_cfg_indRot_data, ctx_cfg_indRot_size,
                         ctx_cfg_indTot_data, ctx_cfg_indTot_size, curv_Info_Type, curv_R0, curv_R1,
                         curv_CorrectedHelixCenter, curv_evec, curv_theta, curv_pitch, curv_CoeffP5,
                         curv_a_param, curv_b_param, a__1, r1D, a__2, a__3);
        // 'LengthCurv:5' L = MyNorm( r1D ) * ( u1 - u0 );
        // 'MyNorm:2' coder.inline('always');
        // 'MyNorm:3' n = mysqrt(sum(x.^2));
        // 'mysqrt:3' y = sqrt(x);
        r.set_size(r1D.size(0));
        loop_ub = r1D.size(0);
        for (int i1{0}; i1 < loop_ub; i1++) {
            double varargin_1;
            varargin_1 = r1D[i1];
            r[i1] = std::pow(varargin_1, 2.0);
        }
        L = std::sqrt(coder::combineVectorElements(r));
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
    } else if (curv_Info_Type == CurveType_Spline) {
        // 'LengthCurv:6' elseif curv.Info.Type == CurveType.Spline
        // 'LengthCurv:7' a = curv.a_param;
        // 'LengthCurv:8' b = curv.b_param;
        // 'LengthCurv:9' u0_tilda = a * u0 + b;
        // 'LengthCurv:10' u1_tilda = a * u1 + b;
        // 'LengthCurv:11' L = SplineLengthApproxGL_bounds(ctx, curv, u0_tilda, u1_tilda);
        L = SplineLengthApproxGL_bounds(ctx_q_spline, ctx_cfg_GaussLegendreX,
                                        ctx_cfg_GaussLegendreW, curv_sp_index, curv_b_param,
                                        curv_a_param + curv_b_param);
    } else if (curv_Info_Type == CurveType_TransP5) {
        double b_y;
        double work;
        int ixLead;
        int nD;
        int vlen;
        // 'LengthCurv:12' elseif curv.Info.Type == CurveType.TransP5
        // 'LengthCurv:13' L = TransP5LengthApprox(curv);
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
        b.set_size(curv_CoeffP5.size(0), 5);
        if (curv_CoeffP5.size(0) != 0) {
            int i2;
            i2 = curv_CoeffP5.size(0) - 1;
            for (int k{0}; k < 5; k++) {
                for (int t{0}; t <= i2; t++) {
                    b[t + b.size(0) * k] = static_cast<signed char>(5 - k);
                }
            }
        }
        if (curv_CoeffP5.size(0) == b.size(0)) {
            int b_loop_ub;
            b_loop_ub = curv_CoeffP5.size(0);
            p5_1D.set_size(curv_CoeffP5.size(0), 5);
            for (int i3{0}; i3 < 5; i3++) {
                for (int i4{0}; i4 < b_loop_ub; i4++) {
                    p5_1D[i4 + p5_1D.size(0) * i3] = curv_CoeffP5[i4 + curv_CoeffP5.size(0) * i3] *
                                                     static_cast<double>(b[i4 + b.size(0) * i3]);
                }
            }
        } else {
            c_binary_expand_op(p5_1D, curv_CoeffP5, b);
        }
        //  Derivative
        // 'TransP5LengthApprox:5' u_vec     = linspace(0,1,10);
        // 'TransP5LengthApprox:6' u_mid     = 0.5*(u_vec(1:end-1) +u_vec(2:end));
        //  Midpoint values
        // 'TransP5LengthApprox:7' du        = diff(u_vec);
        ixLead = 1;
        work = 0.0;
        for (int m{0}; m < 9; m++) {
            double tmp2;
            double work_tmp;
            tmp2 = work;
            work_tmp = 0.1111111111111111 * static_cast<double>(ixLead);
            work = work_tmp;
            b_y1[m] = work_tmp - tmp2;
            ixLead++;
        }
        // 'TransP5LengthApprox:8' Integrand = mysqrt(sum(mypolyval(p5_1D, u_mid).^2));
        // POLYVAL Evaluate array of polynomials with same degree.
        //
        // 'mypolyval:4' [nD, nc] = size(p);
        nD = p5_1D.size(0);
        // 'mypolyval:5' siz_x    = length(x);
        //
        //  Use Horner's method for general case where X is an array.
        // 'mypolyval:8' y = zeros(nD, siz_x);
        // 'mypolyval:9' if nc > 0
        // 'mypolyval:10' y(:) = repmat(p(:, 1), 1, siz_x);
        y.set_size(p5_1D.size(0), 9);
        if (p5_1D.size(0) != 0) {
            int i5;
            i5 = p5_1D.size(0) - 1;
            for (int b_t{0}; b_t < 9; b_t++) {
                for (int b_k{0}; b_k <= i5; b_k++) {
                    y[b_k + y.size(0) * b_t] = p5_1D[b_k];
                }
            }
        }
        // 'mypolyval:12' for i=2:nc
        for (int b_i{0}; b_i < 4; b_i++) {
            int i10;
            // 'mypolyval:13' y = repmat(x, nD, 1) .* y + repmat(p(:, i), 1, siz_x);
            r1.set_size(nD, 9);
            if (p5_1D.size(0) != 0) {
                int i7;
                i7 = nD - 1;
                for (int c_k{0}; c_k < 9; c_k++) {
                    for (int c_t{0}; c_t <= i7; c_t++) {
                        r1[c_t + r1.size(0) * c_k] = a[c_k];
                    }
                }
            }
            r2.set_size(p5_1D.size(0), 9);
            if (p5_1D.size(0) != 0) {
                int i9;
                i9 = p5_1D.size(0) - 1;
                for (int d_t{0}; d_t < 9; d_t++) {
                    for (int d_k{0}; d_k <= i9; d_k++) {
                        r2[d_k + r2.size(0) * d_t] = p5_1D[d_k + p5_1D.size(0) * (b_i + 1)];
                    }
                }
            }
            if (r1.size(0) == 1) {
                i10 = y.size(0);
            } else {
                i10 = r1.size(0);
            }
            if ((r1.size(0) == y.size(0)) && (i10 == r2.size(0))) {
                int d_loop_ub;
                y.set_size(r1.size(0), 9);
                d_loop_ub = r1.size(0);
                for (int i11{0}; i11 < 9; i11++) {
                    for (int i12{0}; i12 < d_loop_ub; i12++) {
                        y[i12 + y.size(0) * i11] =
                            r1[i12 + r1.size(0) * i11] * y[i12 + y.size(0) * i11] +
                            r2[i12 + r2.size(0) * i11];
                    }
                }
            } else {
                b_binary_expand_op(y, r1, r2);
            }
        }
        y.set_size(y.size(0), 9);
        for (int i6{0}; i6 < 9; i6++) {
            int c_loop_ub;
            c_loop_ub = y.size(0);
            for (int i8{0}; i8 < c_loop_ub; i8++) {
                double b_varargin_1;
                b_varargin_1 = y[i8 + y.size(0) * i6];
                y[i8 + y.size(0) * i6] = std::pow(b_varargin_1, 2.0);
            }
        }
        vlen = y.size(0);
        if (y.size(0) == 0) {
            std::memset(&Integrand[0], 0, 9U * sizeof(double));
        } else {
            int firstBlockLength;
            int lastBlockLength;
            int nblocks;
            if (y.size(0) <= 1024) {
                firstBlockLength = y.size(0);
                lastBlockLength = 0;
                nblocks = 1;
            } else {
                firstBlockLength = 1024;
                nblocks = y.size(0) / 1024;
                lastBlockLength = y.size(0) - (nblocks << 10);
                if (lastBlockLength > 0) {
                    nblocks++;
                } else {
                    lastBlockLength = 1024;
                }
            }
            for (int e_k{0}; e_k < 9; e_k++) {
                Integrand[e_k] = y[y.size(0) * e_k];
                for (int g_k{2}; g_k <= firstBlockLength; g_k++) {
                    if (vlen >= 2) {
                        ysubs_idx_1 = static_cast<short>(e_k + 1);
                        Integrand[e_k] += y[(g_k + y.size(0) * e_k) - 1];
                    }
                }
                if (2 <= nblocks) {
                    xsubs_idx_1 = e_k + 1;
                    ysubs_idx_1 = static_cast<short>(e_k + 1);
                }
                for (int ib{2}; ib <= nblocks; ib++) {
                    double bsum;
                    int hi;
                    int offset;
                    offset = (ib - 1) << 10;
                    bsum = y[offset + y.size(0) * (xsubs_idx_1 - 1)];
                    if (ib == nblocks) {
                        hi = lastBlockLength;
                    } else {
                        hi = 1024;
                    }
                    for (int i_k{2}; i_k <= hi; i_k++) {
                        double b_bsum;
                        b_bsum = bsum;
                        if (vlen >= 2) {
                            b_bsum = bsum + y[((offset + i_k) + y.size(0) * e_k) - 1];
                        }
                        bsum = b_bsum;
                    }
                    Integrand[ysubs_idx_1 - 1] += bsum;
                }
            }
        }
        // 'mysqrt:3' y = sqrt(x);
        // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
        sqrt_calls++;
        // 'TransP5LengthApprox:9' L         = sum(Integrand.*du);
        for (int f_k{0}; f_k < 9; f_k++) {
            double d;
            d = std::sqrt(Integrand[f_k]);
            Integrand[f_k] = d;
            x[f_k] = d * b_y1[f_k];
        }
        b_y = x[0];
        for (int h_k{0}; h_k < 8; h_k++) {
            b_y += x[h_k + 1];
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
