//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: SplineLengthApprox_Interval1.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

// Include Files
#include "SplineLengthApprox_Interval1.h"
#include "bspline_eval.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_types1.h"
#include "opencn_matlab_types2.h"
#include "opencn_matlab_types3.h"
#include "queue_coder.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// function L = SplineLengthApprox_Interval1(ctx, Curv, u0, u1)
//
// computes approximately the arc length L with integration bounds u1 and u2.
//  IMPORTANT : u1 and u2 should lie in the same knot interval.
//  The computation is based on numerical Gauss Legendre integration
//
//  get the spline
//
// Arguments    : const queue_coder *ctx_q_spline
//                const double ctx_cfg_GaussLegendreX[5]
//                const double ctx_cfg_GaussLegendreW[5]
//                unsigned int Curv_sp_index
//                double u0
//                double u1
// Return Type  : double
//
namespace ocn {
double SplineLengthApprox_Interval1(const queue_coder *ctx_q_spline,
                                    const double ctx_cfg_GaussLegendreX[5],
                                    const double ctx_cfg_GaussLegendreW[5],
                                    unsigned int Curv_sp_index, double u0, double u1)
{
    ::coder::array<double, 2U> b_expl_temp;
    ::coder::array<double, 2U> r1D;
    ::coder::array<double, 2U> y;
    CurvStruct expl_temp;
    double dv[5];
    double dv1[5];
    double dv2[5];
    double dv3[5];
    double r1Dnorm[5];
    double uvec[5];
    double b_r1Dnorm;
    int b_loop_ub;
    int i2;
    int loop_ub;
    int vlen;
    int xsubs_idx_1;
    short ysubs_idx_1;
    // 'SplineLengthApprox_Interval1:7' Spline = ctx.q_spline.get(Curv.sp_index);
    ctx_q_spline->get(Curv_sp_index, &expl_temp);
    //  get Gauss-Legendre knots and weights
    // 'SplineLengthApprox_Interval1:9' GL_X   = ctx.cfg.GaussLegendreX;
    // 'SplineLengthApprox_Interval1:10' GL_W   = ctx.cfg.GaussLegendreW;
    //  apply linear map from[-1, 1] to [u0, u1]
    // 'SplineLengthApprox_Interval1:12' uvec   = ((u0*(1-GL_X) + u1*(1+GL_X))/2)';
    //
    // 'SplineLengthApprox_Interval1:14' [~, r1D]  = EvalBSpline(Spline, uvec);
    //  EvalBSpline
    //
    //  INPUT
    //  spline        : struct : Spline structure
    //  u_vec         :    1xn : Vector for evaluation of the curv
    //
    //  OUTPUT
    //  r0D           :   nDxn : The evaluated B spline at u\_vec points
    //  r1D           :   nDxn : 1rst order parametric derivative for the B spline at u\_vec points
    //  r2D           :   nDxn : 2nd order parametric derivative for the B spline at u\_vec points
    //  r3D           :   nDxn : 3rd order parametric derivative for the B spline at u\_vec points
    // 'EvalBSpline:14' sp = spline.sp;
    // 'EvalBSpline:15' N  = length( u_vec );
    // 'EvalBSpline:16' M  = size( sp.coeff, 1 );
    // 'EvalBSpline:18' r0D = zeros( M, N );
    // 'EvalBSpline:18' r1D = r0D;
    r1D.set_size(expl_temp.sp.coeff.size(0), 5);
    loop_ub = expl_temp.sp.coeff.size(0);
    for (int i{0}; i < 5; i++) {
        double d;
        d = ctx_cfg_GaussLegendreX[i];
        uvec[i] = (u0 * (1.0 - d) + u1 * (d + 1.0)) / 2.0;
        for (int i1{0}; i1 < loop_ub; i1++) {
            r1D[i1 + r1D.size(0) * i] = 0.0;
        }
    }
    // 'EvalBSpline:18' r2D = r1D;
    // 'EvalBSpline:18' r3D = r2D;
    // 'EvalBSpline:20' for j = 1 : M
    i2 = expl_temp.sp.coeff.size(0);
    for (int j{0}; j < i2; j++) {
        int c_loop_ub;
        // 'EvalBSpline:21' [r0D( j , : ), r1D( j , : ), r2D( j , : ), r3D( j , : ) ] = ...
        // 'EvalBSpline:22'                             bspline_eval_vec( sp.Bl, sp.coeff( j, : ),
        // u_vec ); 'bspline_eval_vec:3' x       = zeros(size(u)); 'bspline_eval_vec:4' xd      =
        // zeros(size(u)); 'bspline_eval_vec:5' xdd     = zeros(size(u)); 'bspline_eval_vec:6' xddd
        // = zeros(size(u)); 'bspline_eval_vec:8' for k = 1:length(u)
        c_loop_ub = expl_temp.sp.coeff.size(1);
        for (int k{0}; k < 5; k++) {
            // 'bspline_eval_vec:9' [xk, xdk, xddk, xdddk] = bspline_eval(Bl, coeffs, u(k));
            dv[k] = uvec[k];
            b_expl_temp.set_size(1, c_loop_ub);
            for (int i7{0}; i7 < c_loop_ub; i7++) {
                b_expl_temp[i7] = expl_temp.sp.coeff[j + expl_temp.sp.coeff.size(0) * i7];
            }
            bspline_eval(expl_temp.sp.Bl.handle, b_expl_temp, &dv[k], &dv1[k], &dv2[k], &dv3[k]);
            // 'bspline_eval_vec:10' x(k)    = xk;
            // 'bspline_eval_vec:11' xd(k)   = xdk;
            // 'bspline_eval_vec:12' xdd(k)  = xddk;
            // 'bspline_eval_vec:13' xddd(k) = xdddk;
        }
        for (int i6{0}; i6 < 5; i6++) {
            r1D[j + r1D.size(0) * i6] = dv1[i6];
        }
    }
    // 'SplineLengthApprox_Interval1:15' r1Dnorm   = MyNorm(r1D);
    // 'MyNorm:2' coder.inline('always');
    // 'MyNorm:3' n = mysqrt(sum(x.^2));
    y.set_size(r1D.size(0), 5);
    b_loop_ub = r1D.size(0);
    for (int i3{0}; i3 < 5; i3++) {
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            double varargin_1;
            varargin_1 = r1D[i4 + r1D.size(0) * i3];
            y[i4 + y.size(0) * i3] = std::pow(varargin_1, 2.0);
        }
    }
    vlen = y.size(0);
    if (y.size(0) == 0) {
        for (int i5{0}; i5 < 5; i5++) {
            r1Dnorm[i5] = 0.0;
        }
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
        for (int b_k{0}; b_k < 5; b_k++) {
            r1Dnorm[b_k] = y[y.size(0) * b_k];
            for (int c_k{2}; c_k <= firstBlockLength; c_k++) {
                if (vlen >= 2) {
                    ysubs_idx_1 = static_cast<short>(b_k + 1);
                    r1Dnorm[b_k] += y[(c_k + y.size(0) * b_k) - 1];
                }
            }
            if (2 <= nblocks) {
                xsubs_idx_1 = b_k + 1;
                ysubs_idx_1 = static_cast<short>(b_k + 1);
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
                for (int e_k{2}; e_k <= hi; e_k++) {
                    double b_bsum;
                    b_bsum = bsum;
                    if (vlen >= 2) {
                        b_bsum = bsum + y[((offset + e_k) + y.size(0) * b_k) - 1];
                    }
                    bsum = b_bsum;
                }
                r1Dnorm[ysubs_idx_1 - 1] += bsum;
            }
        }
    }
    // 'mysqrt:3' y = sqrt(x);
    // 'mysqrt:4' sqrt_calls = sqrt_calls + 1;
    sqrt_calls++;
    // 'SplineLengthApprox_Interval1:16' L         = r1Dnorm * GL_W * (u1-u0)/2;
    b_r1Dnorm = 0.0;
    for (int d_k{0}; d_k < 5; d_k++) {
        double d1;
        d1 = std::sqrt(r1Dnorm[d_k]);
        r1Dnorm[d_k] = d1;
        b_r1Dnorm += d1 * ctx_cfg_GaussLegendreW[d_k];
    }
    return b_r1Dnorm * (u1 - u0) / 2.0;
    //  Gauss Legendre integration
    // 'SplineLengthApprox_Interval1:17' L = L(1);
    //  to satisfy Matlab Coder
}

} // namespace ocn

//
// File trailer for SplineLengthApprox_Interval1.cpp
//
// [EOF]
//
