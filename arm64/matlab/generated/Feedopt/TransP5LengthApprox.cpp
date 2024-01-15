
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: TransP5LengthApprox.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "TransP5LengthApprox.h"
#include "mypolyder.h"
#include "mypolyval.h"
#include "ocn_assert.h"
#include "coder_array.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// function [ L ] = TransP5LengthApprox( CurvStruct, u0, u1 )
//
// TransP5LengthApprox : Compute the length of the transition (5th degree
//  polynomial) between u0 and u1.
//
//  Inputs :
//    CurvStruct  : Curve structure (5th degree polynomial)
//    u0          : Starting u
//    u1          : Ending u
//
//  Outputs :
//    L           : Approximative length
//
//
// Arguments    : const ::coder::array<double, 2U> &CurvStruct_CoeffP5
//                double u0
//                double u1
// Return Type  : double
//
namespace ocn {
double TransP5LengthApprox(const ::coder::array<double, 2U> &CurvStruct_CoeffP5, double u0,
                           double u1)
{
    ::coder::array<double, 2U> p5_1D;
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> y;
    ::coder::array<int, 2U> b;
    double u_vec[10];
    double b_y[9];
    double b_y1[9];
    double u_mid[9];
    double x[9];
    double d_y;
    double work;
    int b_outsize_idx_0;
    int c_loop_ub;
    int i3;
    int outsize_idx_0;
    int vlen;
    int xsubs_idx_1;
    short ysubs_idx_1;
    bool c_y[9];
    //  Computes approximately the arc length of a parametric spline
    // 'TransP5LengthApprox:16' p5          = CurvStruct.CoeffP5;
    // 'TransP5LengthApprox:17' p5_1D       = mypolyder( p5 );
    //  mypolyder : Compute the derivative of input polynom of coefficient u.
    //
    //  Inputs :
    //    u : Coefficients of the polynom vector.
    //  Outputs :
    //    a : Coefficient of the derivative of the polynom vector.
    //
    //  u  = u( : ).';
    // 'mypolyder:10' [ nD, nu ] = size( u );
    // 'mypolyder:11' if nu < 2
    if (CurvStruct_CoeffP5.size(1) < 2) {
        // 'mypolyder:12' a = 0;
        p5_1D.set_size(1, 1);
        p5_1D[0] = 0.0;
    } else {
        // 'mypolyder:13' else
        // 'mypolyder:14' a = u( :, 1 : nu-1 ) .* repmat( nu-1 :-1 : 1 , nD, 1 );
        b.set_size(CurvStruct_CoeffP5.size(0), CurvStruct_CoeffP5.size(1) - 1);
        if (CurvStruct_CoeffP5.size(0) != 0) {
            int i;
            int na;
            na = CurvStruct_CoeffP5.size(1) - 2;
            i = CurvStruct_CoeffP5.size(0) - 1;
            for (int k{0}; k <= na; k++) {
                for (int t{0}; t <= i; t++) {
                    b[t + b.size(0) * k] = (CurvStruct_CoeffP5.size(1) - k) - 1;
                }
            }
        }
        if ((CurvStruct_CoeffP5.size(0) == b.size(0)) &&
            (CurvStruct_CoeffP5.size(1) - 1 == b.size(1))) {
            int b_loop_ub;
            int loop_ub;
            loop_ub = CurvStruct_CoeffP5.size(0);
            b_loop_ub = CurvStruct_CoeffP5.size(1) - 1;
            p5_1D.set_size(CurvStruct_CoeffP5.size(0), CurvStruct_CoeffP5.size(1) - 1);
            for (int i1{0}; i1 < b_loop_ub; i1++) {
                for (int i2{0}; i2 < loop_ub; i2++) {
                    p5_1D[i2 + p5_1D.size(0) * i1] =
                        CurvStruct_CoeffP5[i2 + CurvStruct_CoeffP5.size(0) * i1] *
                        static_cast<double>(b[i2 + b.size(0) * i1]);
                }
            }
        } else {
            binary_expand_op(p5_1D, CurvStruct_CoeffP5, b);
        }
    }
    //  Derivative
    // 'TransP5LengthApprox:18' u_vec       = linspace( u0, u1, 10 );
    u_vec[9] = u1;
    u_vec[0] = u0;
    if (u0 == -u1) {
        double d2scaled;
        d2scaled = u1 / 9.0;
        for (int b_k{0}; b_k < 8; b_k++) {
            u_vec[b_k + 1] = (2.0 * (static_cast<double>(b_k) + 2.0) - 11.0) * d2scaled;
        }
    } else if (((u0 < 0.0) != (u1 < 0.0)) && ((std::abs(u0) > 8.9884656743115785E+307) ||
                                              (std::abs(u1) > 8.9884656743115785E+307))) {
        double delta1;
        double delta2;
        delta1 = u0 / 9.0;
        delta2 = u1 / 9.0;
        for (int d_k{0}; d_k < 8; d_k++) {
            u_vec[d_k + 1] = (u0 + delta2 * (static_cast<double>(d_k) + 1.0)) -
                             delta1 * (static_cast<double>(d_k) + 1.0);
        }
    } else {
        double delta1;
        delta1 = (u1 - u0) / 9.0;
        for (int c_k{0}; c_k < 8; c_k++) {
            u_vec[c_k + 1] = u0 + (static_cast<double>(c_k) + 1.0) * delta1;
        }
    }
    // 'TransP5LengthApprox:19' u_mid       = 0.5 * ( u_vec( 1 : end-1 ) + u_vec( 2 : end ) );
    //  Midpoint values
    // 'TransP5LengthApprox:20' du          = diff( u_vec );
    work = u_vec[0];
    // 'TransP5LengthApprox:21' Integrand   = mysqrt( sum( mypolyval( p5_1D, u_mid ) .^ 2 ) );
    //  Polyval : Evaluate array of polynomials with same degree.
    //
    //  Inputs :
    //    p : Polynom coefficients
    //    x : Polynom x values
    //  Outputs :
    //    y : Resulting values
    //
    // 'mypolyval:10' [ nD, nc ] = size( p );
    // 'mypolyval:11' siz_x      = length( x );
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:14' y = zeros( nD, siz_x );
    y.set_size(p5_1D.size(0), 9);
    c_loop_ub = p5_1D.size(0);
    for (int m{0}; m < 9; m++) {
        double tmp2;
        double u_mid_tmp;
        u_mid_tmp = u_vec[m + 1];
        u_mid[m] = 0.5 * (u_vec[m] + u_mid_tmp);
        tmp2 = work;
        work = u_mid_tmp;
        b_y1[m] = u_mid_tmp - tmp2;
        for (int i5{0}; i5 < c_loop_ub; i5++) {
            y[i5 + y.size(0) * m] = 0.0;
        }
    }
    // 'mypolyval:15' if nc > 0
    if (p5_1D.size(1) > 0) {
        // 'mypolyval:16' y( : ) = repmat( p( :, 1 ), 1, siz_x );
        y.set_size(p5_1D.size(0), 9);
        if (p5_1D.size(0) != 0) {
            int i4;
            i4 = p5_1D.size(0) - 1;
            for (int b_t{0}; b_t < 9; b_t++) {
                for (int e_k{0}; e_k <= i4; e_k++) {
                    y[e_k + y.size(0) * b_t] = p5_1D[e_k];
                }
            }
        }
    }
    // 'mypolyval:18' for i = 2 : nc
    i3 = p5_1D.size(1);
    if (p5_1D.size(1) - 2 >= 0) {
        outsize_idx_0 = p5_1D.size(0);
        b_outsize_idx_0 = p5_1D.size(0);
    }
    for (int b_i{0}; b_i <= i3 - 2; b_i++) {
        int i10;
        // 'mypolyval:19' y = repmat( x, nD, 1 ) .* y + repmat( p( :, i ), 1, siz_x );
        r.set_size(outsize_idx_0, 9);
        if (outsize_idx_0 != 0) {
            int i7;
            i7 = p5_1D.size(0) - 1;
            for (int f_k{0}; f_k < 9; f_k++) {
                for (int c_t{0}; c_t <= i7; c_t++) {
                    r[c_t + r.size(0) * f_k] = u_mid[f_k];
                }
            }
        }
        r1.set_size(b_outsize_idx_0, 9);
        if (b_outsize_idx_0 != 0) {
            int i9;
            i9 = p5_1D.size(0) - 1;
            for (int d_t{0}; d_t < 9; d_t++) {
                for (int g_k{0}; g_k <= i9; g_k++) {
                    r1[g_k + r1.size(0) * d_t] = p5_1D[g_k + p5_1D.size(0) * (b_i + 1)];
                }
            }
        }
        if (r.size(0) == 1) {
            i10 = y.size(0);
        } else {
            i10 = r.size(0);
        }
        if ((r.size(0) == y.size(0)) && (i10 == r1.size(0))) {
            int e_loop_ub;
            y.set_size(r.size(0), 9);
            e_loop_ub = r.size(0);
            for (int i11{0}; i11 < 9; i11++) {
                for (int i12{0}; i12 < e_loop_ub; i12++) {
                    y[i12 + y.size(0) * i11] = r[i12 + r.size(0) * i11] * y[i12 + y.size(0) * i11] +
                                               r1[i12 + r1.size(0) * i11];
                }
            }
        } else {
            binary_expand_op(y, r, r1);
        }
    }
    y.set_size(y.size(0), 9);
    for (int i6{0}; i6 < 9; i6++) {
        int d_loop_ub;
        d_loop_ub = y.size(0);
        for (int i8{0}; i8 < d_loop_ub; i8++) {
            double varargin_1;
            varargin_1 = y[i8 + y.size(0) * i6];
            y[i8 + y.size(0) * i6] = std::pow(varargin_1, 2.0);
        }
    }
    vlen = y.size(0);
    if (y.size(0) == 0) {
        std::memset(&b_y[0], 0, 9U * sizeof(double));
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
        for (int h_k{0}; h_k < 9; h_k++) {
            b_y[h_k] = y[y.size(0) * h_k];
            for (int i_k{2}; i_k <= firstBlockLength; i_k++) {
                if (vlen >= 2) {
                    ysubs_idx_1 = static_cast<short>(h_k + 1);
                    b_y[h_k] += y[(i_k + y.size(0) * h_k) - 1];
                }
            }
            if (nblocks >= 2) {
                xsubs_idx_1 = h_k + 1;
                ysubs_idx_1 = static_cast<short>(h_k + 1);
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
                for (int k_k{2}; k_k <= hi; k_k++) {
                    double b_bsum;
                    b_bsum = bsum;
                    if (vlen >= 2) {
                        b_bsum = bsum + y[((offset + k_k) + y.size(0) * h_k) - 1];
                    }
                    bsum = b_bsum;
                }
                b_y[ysubs_idx_1 - 1] += bsum;
            }
        }
    }
    //  mysqrt : Custom implementation of the sqrt method.
    //
    //  Inputs :
    //    x : Value used for the computation
    //  Outputs :
    //    y : Resulting value
    //
    // 'mysqrt:9' ocn_assert( isreal( x ), "x should be real...", mfilename );
    // 'mysqrt:10' ocn_assert( x >= 0, "x should not be negative...", mfilename );
    for (int i13{0}; i13 < 9; i13++) {
        c_y[i13] = (b_y[i13] >= 0.0);
    }
    o_ocn_assert(c_y);
    // 'mysqrt:11' y = sqrt(x);
    // 'TransP5LengthApprox:22' L           = sum( Integrand .* du );
    for (int j_k{0}; j_k < 9; j_k++) {
        double d;
        d = std::sqrt(b_y[j_k]);
        b_y[j_k] = d;
        x[j_k] = d * b_y1[j_k];
    }
    d_y = x[0];
    for (int l_k{0}; l_k < 8; l_k++) {
        d_y += x[l_k + 1];
    }
    return d_y;
}

} // namespace ocn

//
// File trailer for TransP5LengthApprox.cpp
//
// [EOF]
//
