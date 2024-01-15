
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: mypolyval.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "mypolyval.h"
#include "coder_array.h"

// Function Declarations
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 1U> &in2,
                             const ::coder::array<double, 2U> &in3);

static void binary_expand_op(::coder::array<double, 1U> &in1, double in2, const int in3[2],
                             const ::coder::array<double, 1U> &in4);

static void h_binary_expand_op(::coder::array<double, 2U> &in1,
                               const ::coder::array<double, 2U> &in2,
                               const ::coder::array<double, 2U> &in3);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 1U> &in2
//                const ::coder::array<double, 2U> &in3
// Return Type  : void
//
namespace ocn {
static void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 1U> &in2,
                             const ::coder::array<double, 2U> &in3)
{
    ::coder::array<double, 2U> b_in2;
    int aux_1_1;
    int aux_2_1;
    int b_loop_ub;
    int i;
    int i1;
    int in2_idx_0;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_1_1;
    int stride_2_0;
    int stride_2_1;
    in2_idx_0 = in2.size(0);
    if (in3.size(0) == 1) {
        if (in1.size(0) == 1) {
            i = in2_idx_0;
        } else {
            i = in1.size(0);
        }
    } else {
        i = in3.size(0);
    }
    if (in3.size(1) == 1) {
        if (in1.size(1) == 1) {
            i1 = 1;
        } else {
            i1 = in1.size(1);
        }
    } else {
        i1 = in3.size(1);
    }
    b_in2.set_size(i, i1);
    stride_0_0 = (in2_idx_0 != 1);
    stride_1_0 = (in1.size(0) != 1);
    stride_1_1 = (in1.size(1) != 1);
    stride_2_0 = (in3.size(0) != 1);
    stride_2_1 = (in3.size(1) != 1);
    aux_1_1 = 0;
    aux_2_1 = 0;
    if (in3.size(1) == 1) {
        if (in1.size(1) == 1) {
            loop_ub = 1;
        } else {
            loop_ub = in1.size(1);
        }
    } else {
        loop_ub = in3.size(1);
    }
    for (int i2{0}; i2 < loop_ub; i2++) {
        int c_loop_ub;
        if (in3.size(0) == 1) {
            if (in1.size(0) == 1) {
                c_loop_ub = in2_idx_0;
            } else {
                c_loop_ub = in1.size(0);
            }
        } else {
            c_loop_ub = in3.size(0);
        }
        for (int i4{0}; i4 < c_loop_ub; i4++) {
            b_in2[i4 + b_in2.size(0) * i2] =
                in2[i4 * stride_0_0] * in1[i4 * stride_1_0 + in1.size(0) * aux_1_1] +
                in3[i4 * stride_2_0 + in3.size(0) * aux_2_1];
        }
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
    }
    in1.set_size(b_in2.size(0), b_in2.size(1));
    b_loop_ub = b_in2.size(1);
    for (int i3{0}; i3 < b_loop_ub; i3++) {
        int d_loop_ub;
        d_loop_ub = b_in2.size(0);
        for (int i5{0}; i5 < d_loop_ub; i5++) {
            in1[i5 + in1.size(0) * i3] = b_in2[i5 + b_in2.size(0) * i3];
        }
    }
}

//
// Arguments    : ::coder::array<double, 1U> &in1
//                double in2
//                const int in3[2]
//                const ::coder::array<double, 1U> &in4
// Return Type  : void
//
static void binary_expand_op(::coder::array<double, 1U> &in1, double in2, const int in3[2],
                             const ::coder::array<double, 1U> &in4)
{
    ::coder::array<double, 1U> b_in2;
    int b_loop_ub;
    int i;
    int in3_idx_0;
    int loop_ub;
    int stride_1_0;
    int stride_2_0;
    in3_idx_0 = in3[0];
    if (in4.size(0) == 1) {
        if (in1.size(0) == 1) {
            i = in3_idx_0;
        } else {
            i = in1.size(0);
        }
    } else {
        i = in4.size(0);
    }
    b_in2.set_size(i);
    stride_1_0 = (in1.size(0) != 1);
    stride_2_0 = (in4.size(0) != 1);
    if (in4.size(0) == 1) {
        if (in1.size(0) == 1) {
            loop_ub = in3_idx_0;
        } else {
            loop_ub = in1.size(0);
        }
    } else {
        loop_ub = in4.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        b_in2[i1] = in2 * in1[i1 * stride_1_0] + in4[i1 * stride_2_0];
    }
    in1.set_size(b_in2.size(0));
    b_loop_ub = b_in2.size(0);
    for (int i2{0}; i2 < b_loop_ub; i2++) {
        in1[i2] = b_in2[i2];
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<double, 2U> &in3
// Return Type  : void
//
static void h_binary_expand_op(::coder::array<double, 2U> &in1,
                               const ::coder::array<double, 2U> &in2,
                               const ::coder::array<double, 2U> &in3)
{
    ::coder::array<double, 2U> b_in2;
    int b_loop_ub;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    if (in3.size(0) == 1) {
        if (in1.size(0) == 1) {
            i = in2.size(0);
        } else {
            i = in1.size(0);
        }
    } else {
        i = in3.size(0);
    }
    b_in2.set_size(i, 2);
    stride_0_0 = (in2.size(0) != 1);
    stride_1_0 = (in1.size(0) != 1);
    stride_2_0 = (in3.size(0) != 1);
    if (in3.size(0) == 1) {
        if (in1.size(0) == 1) {
            loop_ub = in2.size(0);
        } else {
            loop_ub = in1.size(0);
        }
    } else {
        loop_ub = in3.size(0);
    }
    for (int i1{0}; i1 < 2; i1++) {
        for (int i2{0}; i2 < loop_ub; i2++) {
            b_in2[i2 + b_in2.size(0) * i1] =
                in2[i2 * stride_0_0 + in2.size(0) * i1] * in1[i2 * stride_1_0 + in1.size(0) * i1] +
                in3[i2 * stride_2_0 + in3.size(0) * i1];
        }
    }
    in1.set_size(b_in2.size(0), 2);
    b_loop_ub = b_in2.size(0);
    for (int i3{0}; i3 < 2; i3++) {
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            in1[i4 + in1.size(0) * i3] = b_in2[i4 + b_in2.size(0) * i3];
        }
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<double, 2U> &in3
// Return Type  : void
//
void binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                      const ::coder::array<double, 2U> &in3)
{
    ::coder::array<double, 2U> b_in2;
    int b_loop_ub;
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    int stride_2_0;
    if (in3.size(0) == 1) {
        if (in1.size(0) == 1) {
            i = in2.size(0);
        } else {
            i = in1.size(0);
        }
    } else {
        i = in3.size(0);
    }
    b_in2.set_size(i, 9);
    stride_0_0 = (in2.size(0) != 1);
    stride_1_0 = (in1.size(0) != 1);
    stride_2_0 = (in3.size(0) != 1);
    if (in3.size(0) == 1) {
        if (in1.size(0) == 1) {
            loop_ub = in2.size(0);
        } else {
            loop_ub = in1.size(0);
        }
    } else {
        loop_ub = in3.size(0);
    }
    for (int i1{0}; i1 < 9; i1++) {
        for (int i2{0}; i2 < loop_ub; i2++) {
            b_in2[i2 + b_in2.size(0) * i1] =
                in2[i2 * stride_0_0 + in2.size(0) * i1] * in1[i2 * stride_1_0 + in1.size(0) * i1] +
                in3[i2 * stride_2_0 + in3.size(0) * i1];
        }
    }
    in1.set_size(b_in2.size(0), 9);
    b_loop_ub = b_in2.size(0);
    for (int i3{0}; i3 < 9; i3++) {
        for (int i4{0}; i4 < b_loop_ub; i4++) {
            in1[i4 + in1.size(0) * i3] = b_in2[i4 + b_in2.size(0) * i3];
        }
    }
}

//
// Arguments    : ::coder::array<double, 2U> &in1
//                const ::coder::array<double, 2U> &in2
//                const ::coder::array<double, 2U> &in3
// Return Type  : void
//
void e_binary_expand_op(::coder::array<double, 2U> &in1, const ::coder::array<double, 2U> &in2,
                        const ::coder::array<double, 2U> &in3)
{
    ::coder::array<double, 2U> b_in2;
    int aux_0_1;
    int aux_1_1;
    int aux_2_1;
    int b_loop_ub;
    int i;
    int i1;
    int loop_ub;
    int stride_0_0;
    int stride_0_1;
    int stride_1_0;
    int stride_1_1;
    int stride_2_0;
    int stride_2_1;
    if (in3.size(0) == 1) {
        if (in1.size(0) == 1) {
            i = in2.size(0);
        } else {
            i = in1.size(0);
        }
    } else {
        i = in3.size(0);
    }
    if (in3.size(1) == 1) {
        if (in1.size(1) == 1) {
            i1 = in2.size(1);
        } else {
            i1 = in1.size(1);
        }
    } else {
        i1 = in3.size(1);
    }
    b_in2.set_size(i, i1);
    stride_0_0 = (in2.size(0) != 1);
    stride_0_1 = (in2.size(1) != 1);
    stride_1_0 = (in1.size(0) != 1);
    stride_1_1 = (in1.size(1) != 1);
    stride_2_0 = (in3.size(0) != 1);
    stride_2_1 = (in3.size(1) != 1);
    aux_0_1 = 0;
    aux_1_1 = 0;
    aux_2_1 = 0;
    if (in3.size(1) == 1) {
        if (in1.size(1) == 1) {
            loop_ub = in2.size(1);
        } else {
            loop_ub = in1.size(1);
        }
    } else {
        loop_ub = in3.size(1);
    }
    for (int i2{0}; i2 < loop_ub; i2++) {
        int c_loop_ub;
        if (in3.size(0) == 1) {
            if (in1.size(0) == 1) {
                c_loop_ub = in2.size(0);
            } else {
                c_loop_ub = in1.size(0);
            }
        } else {
            c_loop_ub = in3.size(0);
        }
        for (int i4{0}; i4 < c_loop_ub; i4++) {
            b_in2[i4 + b_in2.size(0) * i2] = in2[i4 * stride_0_0 + in2.size(0) * aux_0_1] *
                                                 in1[i4 * stride_1_0 + in1.size(0) * aux_1_1] +
                                             in3[i4 * stride_2_0 + in3.size(0) * aux_2_1];
        }
        aux_2_1 += stride_2_1;
        aux_1_1 += stride_1_1;
        aux_0_1 += stride_0_1;
    }
    in1.set_size(b_in2.size(0), b_in2.size(1));
    b_loop_ub = b_in2.size(1);
    for (int i3{0}; i3 < b_loop_ub; i3++) {
        int d_loop_ub;
        d_loop_ub = b_in2.size(0);
        for (int i5{0}; i5 < d_loop_ub; i5++) {
            in1[i5 + in1.size(0) * i3] = b_in2[i5 + b_in2.size(0) * i3];
        }
    }
}

//
// function [ y ] = mypolyval( p, x )
//
// Polyval : Evaluate array of polynomials with same degree.
//
//  Inputs :
//    p : Polynom coefficients
//    x : Polynom x values
//  Outputs :
//    y : Resulting values
//
//
// Arguments    : const ::coder::array<double, 2U> &p
//                const ::coder::array<double, 1U> &x
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
void mypolyval(const ::coder::array<double, 2U> &p, const ::coder::array<double, 1U> &x,
               ::coder::array<double, 2U> &y)
{
    ::coder::array<double, 2U> r1;
    ::coder::array<double, 2U> r2;
    ::coder::array<double, 1U> r;
    int b_outsize_idx_0;
    int i2;
    int loop_ub;
    int outsize_idx_0;
    int outsize_idx_1;
    // 'mypolyval:10' [ nD, nc ] = size( p );
    // 'mypolyval:11' siz_x      = length( x );
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:14' y = zeros( nD, siz_x );
    y.set_size(p.size(0), x.size(0));
    loop_ub = x.size(0);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = p.size(0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            y[i1 + y.size(0) * i] = 0.0;
        }
    }
    // 'mypolyval:15' if nc > 0
    if (p.size(1) > 0) {
        // 'mypolyval:16' y( : ) = repmat( p( :, 1 ), 1, siz_x );
        y.set_size(p.size(0), x.size(0));
        if ((p.size(0) != 0) && (x.size(0) != 0)) {
            int i3;
            int na;
            i3 = x.size(0) - 1;
            na = p.size(0) - 1;
            for (int t{0}; t <= i3; t++) {
                for (int k{0}; k <= na; k++) {
                    y[k + y.size(0) * t] = p[k];
                }
            }
        }
    }
    // 'mypolyval:18' for i = 2 : nc
    i2 = p.size(1);
    if (p.size(1) - 2 >= 0) {
        outsize_idx_0 = x.size(0) * p.size(0);
        b_outsize_idx_0 = p.size(0);
        outsize_idx_1 = x.size(0);
    }
    for (int b_i{0}; b_i <= i2 - 2; b_i++) {
        int i6;
        // 'mypolyval:19' y = repmat( x, nD, 1 ) .* y + repmat( p( :, i ), 1, siz_x );
        r.set_size(outsize_idx_0);
        if (outsize_idx_0 != 0) {
            int b_na;
            int i4;
            b_na = x.size(0);
            i4 = p.size(0) - 1;
            for (int b_t{0}; b_t <= i4; b_t++) {
                int offset;
                offset = b_t * b_na;
                for (int b_k{0}; b_k < b_na; b_k++) {
                    r[offset + b_k] = x[b_k];
                }
            }
        }
        r1.set_size(b_outsize_idx_0, outsize_idx_1);
        if ((b_outsize_idx_0 != 0) && (outsize_idx_1 != 0)) {
            int i5;
            i5 = x.size(0) - 1;
            for (int c_t{0}; c_t <= i5; c_t++) {
                int c_na;
                c_na = p.size(0) - 1;
                for (int c_k{0}; c_k <= c_na; c_k++) {
                    r1[c_k + r1.size(0) * c_t] = p[c_k + p.size(0) * (b_i + 1)];
                }
            }
        }
        if (r.size(0) == 1) {
            i6 = y.size(0);
        } else {
            i6 = r.size(0);
        }
        if ((r.size(0) == y.size(0)) && (i6 == r1.size(0)) && (y.size(1) == r1.size(1))) {
            int c_loop_ub;
            int e_loop_ub;
            int g_loop_ub;
            r2.set_size(r1.size(0), r1.size(1));
            c_loop_ub = r1.size(1);
            for (int i7{0}; i7 < c_loop_ub; i7++) {
                int d_loop_ub;
                d_loop_ub = r1.size(0);
                for (int i8{0}; i8 < d_loop_ub; i8++) {
                    r2[i8 + r2.size(0) * i7] =
                        r[i8] * y[i8 + y.size(0) * i7] + r1[i8 + r1.size(0) * i7];
                }
            }
            r1.set_size(r2.size(0), r2.size(1));
            e_loop_ub = r2.size(1);
            for (int i9{0}; i9 < e_loop_ub; i9++) {
                int f_loop_ub;
                f_loop_ub = r2.size(0);
                for (int i10{0}; i10 < f_loop_ub; i10++) {
                    r1[i10 + r1.size(0) * i9] = r2[i10 + r2.size(0) * i9];
                }
            }
            y.set_size(r1.size(0), r1.size(1));
            g_loop_ub = r1.size(1);
            for (int i11{0}; i11 < g_loop_ub; i11++) {
                int h_loop_ub;
                h_loop_ub = r1.size(0);
                for (int i12{0}; i12 < h_loop_ub; i12++) {
                    y[i12 + y.size(0) * i11] = r1[i12 + r1.size(0) * i11];
                }
            }
        } else {
            binary_expand_op(y, r, r1);
        }
    }
}

//
// function [ y ] = mypolyval( p, x )
//
// Polyval : Evaluate array of polynomials with same degree.
//
//  Inputs :
//    p : Polynom coefficients
//    x : Polynom x values
//  Outputs :
//    y : Resulting values
//
//
// Arguments    : const ::coder::array<double, 2U> &p
//                const double x[2]
//                ::coder::array<double, 2U> &y
// Return Type  : void
//
void mypolyval(const ::coder::array<double, 2U> &p, const double x[2],
               ::coder::array<double, 2U> &y)
{
    ::coder::array<double, 2U> r;
    ::coder::array<double, 2U> r1;
    int b_outsize_idx_0;
    int i2;
    int loop_ub;
    int outsize_idx_0;
    // 'mypolyval:10' [ nD, nc ] = size( p );
    // 'mypolyval:11' siz_x      = length( x );
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:14' y = zeros( nD, siz_x );
    y.set_size(p.size(0), 2);
    loop_ub = p.size(0);
    for (int i{0}; i < 2; i++) {
        for (int i1{0}; i1 < loop_ub; i1++) {
            y[i1 + y.size(0) * i] = 0.0;
        }
    }
    // 'mypolyval:15' if nc > 0
    if (p.size(1) > 0) {
        // 'mypolyval:16' y( : ) = repmat( p( :, 1 ), 1, siz_x );
        y.set_size(p.size(0), 2);
        if (p.size(0) != 0) {
            int i3;
            i3 = p.size(0) - 1;
            for (int t{0}; t < 2; t++) {
                for (int k{0}; k <= i3; k++) {
                    y[k + y.size(0) * t] = p[k];
                }
            }
        }
    }
    // 'mypolyval:18' for i = 2 : nc
    i2 = p.size(1);
    if (p.size(1) - 2 >= 0) {
        outsize_idx_0 = p.size(0);
        b_outsize_idx_0 = p.size(0);
    }
    for (int b_i{0}; b_i <= i2 - 2; b_i++) {
        int i6;
        // 'mypolyval:19' y = repmat( x, nD, 1 ) .* y + repmat( p( :, i ), 1, siz_x );
        r.set_size(outsize_idx_0, 2);
        if (outsize_idx_0 != 0) {
            int i4;
            i4 = p.size(0) - 1;
            for (int b_k{0}; b_k < 2; b_k++) {
                for (int b_t{0}; b_t <= i4; b_t++) {
                    r[b_t + r.size(0) * b_k] = x[b_k];
                }
            }
        }
        r1.set_size(b_outsize_idx_0, 2);
        if (b_outsize_idx_0 != 0) {
            int i5;
            i5 = p.size(0) - 1;
            for (int c_t{0}; c_t < 2; c_t++) {
                for (int c_k{0}; c_k <= i5; c_k++) {
                    r1[c_k + r1.size(0) * c_t] = p[c_k + p.size(0) * (b_i + 1)];
                }
            }
        }
        if (r.size(0) == 1) {
            i6 = y.size(0);
        } else {
            i6 = r.size(0);
        }
        if ((r.size(0) == y.size(0)) && (i6 == r1.size(0))) {
            int b_loop_ub;
            y.set_size(r.size(0), 2);
            b_loop_ub = r.size(0);
            for (int i7{0}; i7 < 2; i7++) {
                for (int i8{0}; i8 < b_loop_ub; i8++) {
                    y[i8 + y.size(0) * i7] =
                        r[i8 + r.size(0) * i7] * y[i8 + y.size(0) * i7] + r1[i8 + r1.size(0) * i7];
                }
            }
        } else {
            h_binary_expand_op(y, r, r1);
        }
    }
}

//
// function [ y ] = mypolyval( p, x )
//
// Polyval : Evaluate array of polynomials with same degree.
//
//  Inputs :
//    p : Polynom coefficients
//    x : Polynom x values
//  Outputs :
//    y : Resulting values
//
//
// Arguments    : const ::coder::array<double, 2U> &p
//                double x
//                ::coder::array<double, 1U> &y
// Return Type  : void
//
void mypolyval(const ::coder::array<double, 2U> &p, double x, ::coder::array<double, 1U> &y)
{
    ::coder::array<double, 1U> r;
    int outsize[2];
    int i1;
    int loop_ub;
    int outsize_idx_0;
    // 'mypolyval:10' [ nD, nc ] = size( p );
    // 'mypolyval:11' siz_x      = length( x );
    //
    //  Use Horner's method for general case where X is an array.
    // 'mypolyval:14' y = zeros( nD, siz_x );
    y.set_size(p.size(0));
    loop_ub = p.size(0);
    for (int i{0}; i < loop_ub; i++) {
        y[i] = 0.0;
    }
    // 'mypolyval:15' if nc > 0
    if (p.size(1) > 0) {
        // 'mypolyval:16' y( : ) = repmat( p( :, 1 ), 1, siz_x );
        y.set_size(p.size(0));
        if (p.size(0) != 0) {
            int i2;
            i2 = p.size(0) - 1;
            for (int k{0}; k <= i2; k++) {
                y[k] = p[k];
            }
        }
    }
    // 'mypolyval:18' for i = 2 : nc
    i1 = p.size(1);
    if (p.size(1) - 2 >= 0) {
        outsize_idx_0 = p.size(0);
    }
    if (i1 - 2 >= 0) {
        outsize[0] = p.size(0);
    }
    for (int b_i{0}; b_i <= i1 - 2; b_i++) {
        int b_loop_ub;
        int i4;
        // 'mypolyval:19' y = repmat( x, nD, 1 ) .* y + repmat( p( :, i ), 1, siz_x );
        r.set_size(outsize_idx_0);
        if (outsize_idx_0 != 0) {
            int i3;
            i3 = p.size(0) - 1;
            for (int b_k{0}; b_k <= i3; b_k++) {
                r[b_k] = p[b_k + p.size(0) * (b_i + 1)];
            }
        }
        b_loop_ub = y.size(0);
        if (p.size(0) == 1) {
            i4 = y.size(0);
        } else {
            i4 = p.size(0);
        }
        if ((p.size(0) == y.size(0)) && (i4 == r.size(0))) {
            for (int i5{0}; i5 < b_loop_ub; i5++) {
                y[i5] = x * y[i5] + r[i5];
            }
        } else {
            binary_expand_op(y, x, outsize, r);
        }
    }
}

} // namespace ocn

//
// File trailer for mypolyval.cpp
//
// [EOF]
//
