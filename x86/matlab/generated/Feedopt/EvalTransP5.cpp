
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalTransP5.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "EvalTransP5.h"
#include "mypolyder.h"
#include "mypolyval.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"
#include <emmintrin.h>

// Function Definitions
//
// function [ r_0D, r_1D, r_2D, r_3D ] = EvalTransP5( CurvStruct, u_vec, ...
//                                       maskTot )
//
// EvalTransP5 : Eval the 5th order polynom used to describe the transition.
//
//  Inputs :
//  CurvStruct    : A curve structure used for the evaluation of the polynom
//  u_vec         : A vector of u values
//  maskTot       : A mask with all the index of interest
//
//  Outputs :
//  r0D   : Matrix of points for a given set of u values
//  r1D   : Matrix of points (first derivative) for a given set of u values
//  r2D   : Matrix of points (second derivative) for a given set of u values
//  r3D   : Matrix of points (third derivative) for a given set of u values
//
//
// Arguments    : const ::coder::array<double, 2U> &CurvStruct_CoeffP5
//                const ::coder::array<double, 1U> &u_vec
//                const bool maskTot_data[]
//                const int maskTot_size[2]
//                ::coder::array<double, 2U> &r_0D
//                ::coder::array<double, 2U> &r_1D
//                ::coder::array<double, 2U> &r_2D
//                ::coder::array<double, 2U> &r_3D
// Return Type  : void
//
namespace ocn {
void EvalTransP5(const ::coder::array<double, 2U> &CurvStruct_CoeffP5,
                 const ::coder::array<double, 1U> &u_vec, const bool maskTot_data[],
                 const int maskTot_size[2], ::coder::array<double, 2U> &r_0D,
                 ::coder::array<double, 2U> &r_1D, ::coder::array<double, 2U> &r_2D,
                 ::coder::array<double, 2U> &r_3D)
{
    ::coder::array<double, 2U> D0;
    ::coder::array<double, 2U> D1;
    ::coder::array<double, 2U> D2;
    ::coder::array<double, 2U> D3;
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> b_a;
    ::coder::array<double, 2U> p5_1D;
    ::coder::array<int, 2U> b;
    int b_partialTrueCount;
    int b_trueCount;
    int c_partialTrueCount;
    int c_trueCount;
    int d_partialTrueCount;
    int d_trueCount;
    int end_tmp;
    int g_loop_ub;
    int h_loop_ub;
    int i_loop_ub;
    int j_loop_ub;
    int partialTrueCount;
    int trueCount;
    signed char b_tmp_data[6];
    signed char c_tmp_data[6];
    signed char d_tmp_data[6];
    signed char tmp_data[6];
    // 'EvalTransP5:17' if ~coder.target('MATLAB')
    // 'EvalTransP5:18' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalTransP5:19' coder.inline('never')
    // 'EvalTransP5:20' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalTransP5"'));
    ZoneScopedN("EvalTransP5");
    //
    // 'EvalTransP5:23' p5    = CurvStruct.CoeffP5;
    // 'EvalTransP5:24' p5_1D = mypolyder(p5);
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
    // 'EvalTransP5:25' p5_2D = mypolyder(p5_1D);
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
    if (p5_1D.size(1) < 2) {
        // 'mypolyder:12' a = 0;
        a.set_size(1, 1);
        a[0] = 0.0;
    } else {
        // 'mypolyder:13' else
        // 'mypolyder:14' a = u( :, 1 : nu-1 ) .* repmat( nu-1 :-1 : 1 , nD, 1 );
        b.set_size(p5_1D.size(0), p5_1D.size(1) - 1);
        if (p5_1D.size(0) != 0) {
            int b_na;
            int i3;
            b_na = p5_1D.size(1) - 2;
            i3 = p5_1D.size(0) - 1;
            for (int b_k{0}; b_k <= b_na; b_k++) {
                for (int b_t{0}; b_t <= i3; b_t++) {
                    b[b_t + b.size(0) * b_k] = (p5_1D.size(1) - b_k) - 1;
                }
            }
        }
        if ((p5_1D.size(0) == b.size(0)) && (p5_1D.size(1) - 1 == b.size(1))) {
            int c_loop_ub;
            int d_loop_ub;
            c_loop_ub = p5_1D.size(0);
            d_loop_ub = p5_1D.size(1) - 1;
            a.set_size(p5_1D.size(0), p5_1D.size(1) - 1);
            for (int i4{0}; i4 < d_loop_ub; i4++) {
                for (int i5{0}; i5 < c_loop_ub; i5++) {
                    a[i5 + a.size(0) * i4] = p5_1D[i5 + p5_1D.size(0) * i4] *
                                             static_cast<double>(b[i5 + b.size(0) * i4]);
                }
            }
        } else {
            binary_expand_op(a, p5_1D, b);
        }
    }
    // 'EvalTransP5:26' p5_3D = mypolyder(p5_2D);
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
    if (a.size(1) < 2) {
        // 'mypolyder:12' a = 0;
        b_a.set_size(1, 1);
        b_a[0] = 0.0;
    } else {
        // 'mypolyder:13' else
        // 'mypolyder:14' a = u( :, 1 : nu-1 ) .* repmat( nu-1 :-1 : 1 , nD, 1 );
        b.set_size(a.size(0), a.size(1) - 1);
        if (a.size(0) != 0) {
            int c_na;
            int i6;
            c_na = a.size(1) - 2;
            i6 = a.size(0) - 1;
            for (int c_k{0}; c_k <= c_na; c_k++) {
                for (int c_t{0}; c_t <= i6; c_t++) {
                    b[c_t + b.size(0) * c_k] = (a.size(1) - c_k) - 1;
                }
            }
        }
        if ((a.size(0) == b.size(0)) && (a.size(1) - 1 == b.size(1))) {
            int e_loop_ub;
            int f_loop_ub;
            e_loop_ub = a.size(0);
            f_loop_ub = a.size(1) - 1;
            b_a.set_size(a.size(0), a.size(1) - 1);
            for (int i7{0}; i7 < f_loop_ub; i7++) {
                for (int i8{0}; i8 < e_loop_ub; i8++) {
                    b_a[i8 + b_a.size(0) * i7] =
                        a[i8 + a.size(0) * i7] * static_cast<double>(b[i8 + b.size(0) * i7]);
                }
            }
        } else {
            binary_expand_op(b_a, a, b);
        }
    }
    //
    // 'EvalTransP5:28' D0 = mypolyval(p5,    u_vec);
    mypolyval(CurvStruct_CoeffP5, u_vec, D0);
    // 'EvalTransP5:29' D1 = mypolyval(p5_1D, u_vec);
    mypolyval(p5_1D, u_vec, D1);
    // 'EvalTransP5:30' D2 = mypolyval(p5_2D, u_vec);
    mypolyval(a, u_vec, D2);
    // 'EvalTransP5:31' D3 = mypolyval(p5_3D, u_vec);
    mypolyval(b_a, u_vec, D3);
    //
    // 'EvalTransP5:33' r_0D = D0( maskTot, : );
    end_tmp = maskTot_size[1] - 1;
    trueCount = 0;
    partialTrueCount = 0;
    for (int b_i{0}; b_i <= end_tmp; b_i++) {
        if (maskTot_data[b_i]) {
            trueCount++;
            tmp_data[partialTrueCount] = static_cast<signed char>(b_i + 1);
            partialTrueCount++;
        }
    }
    g_loop_ub = D0.size(1);
    r_0D.set_size(trueCount, D0.size(1));
    for (int i9{0}; i9 < g_loop_ub; i9++) {
        for (int i10{0}; i10 < trueCount; i10++) {
            r_0D[i10 + r_0D.size(0) * i9] = D0[(tmp_data[i10] + D0.size(0) * i9) - 1];
        }
    }
    // 'EvalTransP5:34' r_1D = D1( maskTot, : );
    b_trueCount = 0;
    b_partialTrueCount = 0;
    for (int c_i{0}; c_i <= end_tmp; c_i++) {
        if (maskTot_data[c_i]) {
            b_trueCount++;
            b_tmp_data[b_partialTrueCount] = static_cast<signed char>(c_i + 1);
            b_partialTrueCount++;
        }
    }
    h_loop_ub = D1.size(1);
    r_1D.set_size(b_trueCount, D1.size(1));
    for (int i11{0}; i11 < h_loop_ub; i11++) {
        for (int i12{0}; i12 < b_trueCount; i12++) {
            r_1D[i12 + r_1D.size(0) * i11] = D1[(b_tmp_data[i12] + D1.size(0) * i11) - 1];
        }
    }
    // 'EvalTransP5:35' r_2D = D2( maskTot, : );
    c_trueCount = 0;
    c_partialTrueCount = 0;
    for (int d_i{0}; d_i <= end_tmp; d_i++) {
        if (maskTot_data[d_i]) {
            c_trueCount++;
            c_tmp_data[c_partialTrueCount] = static_cast<signed char>(d_i + 1);
            c_partialTrueCount++;
        }
    }
    i_loop_ub = D2.size(1);
    r_2D.set_size(c_trueCount, D2.size(1));
    for (int i13{0}; i13 < i_loop_ub; i13++) {
        for (int i14{0}; i14 < c_trueCount; i14++) {
            r_2D[i14 + r_2D.size(0) * i13] = D2[(c_tmp_data[i14] + D2.size(0) * i13) - 1];
        }
    }
    // 'EvalTransP5:36' r_3D = D3( maskTot, : );
    d_trueCount = 0;
    d_partialTrueCount = 0;
    for (int e_i{0}; e_i <= end_tmp; e_i++) {
        if (maskTot_data[e_i]) {
            d_trueCount++;
            d_tmp_data[d_partialTrueCount] = static_cast<signed char>(e_i + 1);
            d_partialTrueCount++;
        }
    }
    j_loop_ub = D3.size(1);
    r_3D.set_size(d_trueCount, D3.size(1));
    for (int i15{0}; i15 < j_loop_ub; i15++) {
        for (int i16{0}; i16 < d_trueCount; i16++) {
            r_3D[i16 + r_3D.size(0) * i15] = D3[(d_tmp_data[i16] + D3.size(0) * i15) - 1];
        }
    }
}

//
// function [ r_0D, r_1D, r_2D, r_3D ] = EvalTransP5( CurvStruct, u_vec, ...
//                                       maskTot )
//
// EvalTransP5 : Eval the 5th order polynom used to describe the transition.
//
//  Inputs :
//  CurvStruct    : A curve structure used for the evaluation of the polynom
//  u_vec         : A vector of u values
//  maskTot       : A mask with all the index of interest
//
//  Outputs :
//  r0D   : Matrix of points for a given set of u values
//  r1D   : Matrix of points (first derivative) for a given set of u values
//  r2D   : Matrix of points (second derivative) for a given set of u values
//  r3D   : Matrix of points (third derivative) for a given set of u values
//
//
// Arguments    : const ::coder::array<double, 2U> &CurvStruct_CoeffP5
//                double u_vec
//                const bool maskTot_data[]
//                const int maskTot_size[2]
//                double r_0D_data[]
//                int *r_0D_size
//                double r_1D_data[]
//                int *r_1D_size
//                double r_2D_data[]
//                int *r_2D_size
//                double r_3D_data[]
//                int *r_3D_size
// Return Type  : void
//
void b_EvalTransP5(const ::coder::array<double, 2U> &CurvStruct_CoeffP5, double u_vec,
                   const bool maskTot_data[], const int maskTot_size[2], double r_0D_data[],
                   int *r_0D_size, double r_1D_data[], int *r_1D_size, double r_2D_data[],
                   int *r_2D_size, double r_3D_data[], int *r_3D_size)
{
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> b_a;
    ::coder::array<double, 2U> p5_1D;
    ::coder::array<double, 1U> D0;
    ::coder::array<double, 1U> D1;
    ::coder::array<double, 1U> D2;
    ::coder::array<double, 1U> D3;
    ::coder::array<int, 2U> b;
    int b_partialTrueCount;
    int b_trueCount;
    int c_partialTrueCount;
    int c_trueCount;
    int d_partialTrueCount;
    int d_trueCount;
    int end_tmp;
    int partialTrueCount;
    int trueCount;
    signed char b_tmp_data[6];
    signed char c_tmp_data[6];
    signed char d_tmp_data[6];
    signed char tmp_data[6];
    // 'EvalTransP5:17' if ~coder.target('MATLAB')
    // 'EvalTransP5:18' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalTransP5:19' coder.inline('never')
    // 'EvalTransP5:20' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalTransP5"'));
    ZoneScopedN("EvalTransP5");
    //
    // 'EvalTransP5:23' p5    = CurvStruct.CoeffP5;
    // 'EvalTransP5:24' p5_1D = mypolyder(p5);
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
    // 'EvalTransP5:25' p5_2D = mypolyder(p5_1D);
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
    if (p5_1D.size(1) < 2) {
        // 'mypolyder:12' a = 0;
        a.set_size(1, 1);
        a[0] = 0.0;
    } else {
        // 'mypolyder:13' else
        // 'mypolyder:14' a = u( :, 1 : nu-1 ) .* repmat( nu-1 :-1 : 1 , nD, 1 );
        b.set_size(p5_1D.size(0), p5_1D.size(1) - 1);
        if (p5_1D.size(0) != 0) {
            int b_na;
            int i3;
            b_na = p5_1D.size(1) - 2;
            i3 = p5_1D.size(0) - 1;
            for (int b_k{0}; b_k <= b_na; b_k++) {
                for (int b_t{0}; b_t <= i3; b_t++) {
                    b[b_t + b.size(0) * b_k] = (p5_1D.size(1) - b_k) - 1;
                }
            }
        }
        if ((p5_1D.size(0) == b.size(0)) && (p5_1D.size(1) - 1 == b.size(1))) {
            int c_loop_ub;
            int d_loop_ub;
            c_loop_ub = p5_1D.size(0);
            d_loop_ub = p5_1D.size(1) - 1;
            a.set_size(p5_1D.size(0), p5_1D.size(1) - 1);
            for (int i4{0}; i4 < d_loop_ub; i4++) {
                for (int i5{0}; i5 < c_loop_ub; i5++) {
                    a[i5 + a.size(0) * i4] = p5_1D[i5 + p5_1D.size(0) * i4] *
                                             static_cast<double>(b[i5 + b.size(0) * i4]);
                }
            }
        } else {
            binary_expand_op(a, p5_1D, b);
        }
    }
    // 'EvalTransP5:26' p5_3D = mypolyder(p5_2D);
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
    if (a.size(1) < 2) {
        // 'mypolyder:12' a = 0;
        b_a.set_size(1, 1);
        b_a[0] = 0.0;
    } else {
        // 'mypolyder:13' else
        // 'mypolyder:14' a = u( :, 1 : nu-1 ) .* repmat( nu-1 :-1 : 1 , nD, 1 );
        b.set_size(a.size(0), a.size(1) - 1);
        if (a.size(0) != 0) {
            int c_na;
            int i6;
            c_na = a.size(1) - 2;
            i6 = a.size(0) - 1;
            for (int c_k{0}; c_k <= c_na; c_k++) {
                for (int c_t{0}; c_t <= i6; c_t++) {
                    b[c_t + b.size(0) * c_k] = (a.size(1) - c_k) - 1;
                }
            }
        }
        if ((a.size(0) == b.size(0)) && (a.size(1) - 1 == b.size(1))) {
            int e_loop_ub;
            int f_loop_ub;
            e_loop_ub = a.size(0);
            f_loop_ub = a.size(1) - 1;
            b_a.set_size(a.size(0), a.size(1) - 1);
            for (int i7{0}; i7 < f_loop_ub; i7++) {
                for (int i8{0}; i8 < e_loop_ub; i8++) {
                    b_a[i8 + b_a.size(0) * i7] =
                        a[i8 + a.size(0) * i7] * static_cast<double>(b[i8 + b.size(0) * i7]);
                }
            }
        } else {
            binary_expand_op(b_a, a, b);
        }
    }
    //
    // 'EvalTransP5:28' D0 = mypolyval(p5,    u_vec);
    mypolyval(CurvStruct_CoeffP5, u_vec, D0);
    // 'EvalTransP5:29' D1 = mypolyval(p5_1D, u_vec);
    mypolyval(p5_1D, u_vec, D1);
    // 'EvalTransP5:30' D2 = mypolyval(p5_2D, u_vec);
    mypolyval(a, u_vec, D2);
    // 'EvalTransP5:31' D3 = mypolyval(p5_3D, u_vec);
    mypolyval(b_a, u_vec, D3);
    //
    // 'EvalTransP5:33' r_0D = D0( maskTot, : );
    end_tmp = maskTot_size[1] - 1;
    trueCount = 0;
    partialTrueCount = 0;
    for (int b_i{0}; b_i <= end_tmp; b_i++) {
        if (maskTot_data[b_i]) {
            trueCount++;
            tmp_data[partialTrueCount] = static_cast<signed char>(b_i + 1);
            partialTrueCount++;
        }
    }
    *r_0D_size = trueCount;
    for (int i9{0}; i9 < trueCount; i9++) {
        r_0D_data[i9] = D0[tmp_data[i9] - 1];
    }
    // 'EvalTransP5:34' r_1D = D1( maskTot, : );
    b_trueCount = 0;
    b_partialTrueCount = 0;
    for (int c_i{0}; c_i <= end_tmp; c_i++) {
        if (maskTot_data[c_i]) {
            b_trueCount++;
            b_tmp_data[b_partialTrueCount] = static_cast<signed char>(c_i + 1);
            b_partialTrueCount++;
        }
    }
    *r_1D_size = b_trueCount;
    for (int i10{0}; i10 < b_trueCount; i10++) {
        r_1D_data[i10] = D1[b_tmp_data[i10] - 1];
    }
    // 'EvalTransP5:35' r_2D = D2( maskTot, : );
    c_trueCount = 0;
    c_partialTrueCount = 0;
    for (int d_i{0}; d_i <= end_tmp; d_i++) {
        if (maskTot_data[d_i]) {
            c_trueCount++;
            c_tmp_data[c_partialTrueCount] = static_cast<signed char>(d_i + 1);
            c_partialTrueCount++;
        }
    }
    *r_2D_size = c_trueCount;
    for (int i11{0}; i11 < c_trueCount; i11++) {
        r_2D_data[i11] = D2[c_tmp_data[i11] - 1];
    }
    // 'EvalTransP5:36' r_3D = D3( maskTot, : );
    d_trueCount = 0;
    d_partialTrueCount = 0;
    for (int e_i{0}; e_i <= end_tmp; e_i++) {
        if (maskTot_data[e_i]) {
            d_trueCount++;
            d_tmp_data[d_partialTrueCount] = static_cast<signed char>(e_i + 1);
            d_partialTrueCount++;
        }
    }
    *r_3D_size = d_trueCount;
    for (int i12{0}; i12 < d_trueCount; i12++) {
        r_3D_data[i12] = D3[d_tmp_data[i12] - 1];
    }
}

//
// function [ r_0D, r_1D, r_2D, r_3D ] = EvalTransP5( CurvStruct, u_vec, ...
//                                       maskTot )
//
// EvalTransP5 : Eval the 5th order polynom used to describe the transition.
//
//  Inputs :
//  CurvStruct    : A curve structure used for the evaluation of the polynom
//  u_vec         : A vector of u values
//  maskTot       : A mask with all the index of interest
//
//  Outputs :
//  r0D   : Matrix of points for a given set of u values
//  r1D   : Matrix of points (first derivative) for a given set of u values
//  r2D   : Matrix of points (second derivative) for a given set of u values
//  r3D   : Matrix of points (third derivative) for a given set of u values
//
//
// Arguments    : const ::coder::array<double, 2U> &CurvStruct_CoeffP5
//                const ::coder::array<double, 2U> &u_vec
//                const bool maskTot_data[]
//                const int maskTot_size[2]
//                ::coder::array<double, 2U> &r_0D
//                ::coder::array<double, 2U> &r_1D
//                ::coder::array<double, 2U> &r_2D
//                ::coder::array<double, 2U> &r_3D
// Return Type  : void
//
void c_EvalTransP5(const ::coder::array<double, 2U> &CurvStruct_CoeffP5,
                   const ::coder::array<double, 2U> &u_vec, const bool maskTot_data[],
                   const int maskTot_size[2], ::coder::array<double, 2U> &r_0D,
                   ::coder::array<double, 2U> &r_1D, ::coder::array<double, 2U> &r_2D,
                   ::coder::array<double, 2U> &r_3D)
{
    ::coder::array<double, 2U> D0;
    ::coder::array<double, 2U> D1;
    ::coder::array<double, 2U> D2;
    ::coder::array<double, 2U> D3;
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> b;
    ::coder::array<double, 2U> b_a;
    ::coder::array<double, 2U> p5_1D;
    ::coder::array<double, 2U> r5;
    int ab_loop_ub;
    int b_outsize_idx_0;
    int b_outsize_idx_1;
    int b_partialTrueCount;
    int b_trueCount;
    int c_outsize_idx_0;
    int c_outsize_idx_1;
    int c_partialTrueCount;
    int c_trueCount;
    int d_outsize_idx_0;
    int d_outsize_idx_1;
    int d_partialTrueCount;
    int d_trueCount;
    int e_outsize_idx_0;
    int e_outsize_idx_1;
    int end_tmp;
    int f_outsize_idx_0;
    int f_outsize_idx_1;
    int g_loop_ub;
    int g_outsize_idx_0;
    int g_outsize_idx_1;
    int h_outsize_idx_0;
    int h_outsize_idx_1;
    int i11;
    int i21;
    int i31;
    int i41;
    int i_loop_ub;
    int m_loop_ub;
    int outsize_idx_0;
    int outsize_idx_1;
    int partialTrueCount;
    int q_loop_ub;
    int trueCount;
    int u_loop_ub;
    int w_loop_ub;
    int y_loop_ub;
    signed char b_tmp_data[6];
    signed char c_tmp_data[6];
    signed char d_tmp_data[6];
    signed char tmp_data[6];
    // 'EvalTransP5:17' if ~coder.target('MATLAB')
    // 'EvalTransP5:18' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalTransP5:19' coder.inline('never')
    // 'EvalTransP5:20' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalTransP5"'));
    ZoneScopedN("EvalTransP5");
    //
    // 'EvalTransP5:23' p5    = CurvStruct.CoeffP5;
    // 'EvalTransP5:24' p5_1D = mypolyder(p5);
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
            int scalarLB;
            int vectorUB;
            loop_ub = CurvStruct_CoeffP5.size(0);
            b_loop_ub = CurvStruct_CoeffP5.size(1) - 1;
            p5_1D.set_size(CurvStruct_CoeffP5.size(0), CurvStruct_CoeffP5.size(1) - 1);
            scalarLB = (loop_ub / 2) << 1;
            vectorUB = scalarLB - 2;
            for (int i1{0}; i1 < b_loop_ub; i1++) {
                for (int i2{0}; i2 <= vectorUB; i2 += 2) {
                    __m128d r;
                    r = _mm_loadu_pd(&b[i2 + b.size(0) * i1]);
                    _mm_storeu_pd(
                        &p5_1D[i2 + p5_1D.size(0) * i1],
                        _mm_mul_pd(
                            _mm_loadu_pd(
                                (const double
                                     *)&CurvStruct_CoeffP5[i2 + CurvStruct_CoeffP5.size(0) * i1]),
                            r));
                }
                for (int i2{scalarLB}; i2 < loop_ub; i2++) {
                    p5_1D[i2 + p5_1D.size(0) * i1] =
                        CurvStruct_CoeffP5[i2 + CurvStruct_CoeffP5.size(0) * i1] *
                        b[i2 + b.size(0) * i1];
                }
            }
        } else {
            g_binary_expand_op(p5_1D, CurvStruct_CoeffP5, b);
        }
    }
    // 'EvalTransP5:25' p5_2D = mypolyder(p5_1D);
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
    if (p5_1D.size(1) < 2) {
        // 'mypolyder:12' a = 0;
        a.set_size(1, 1);
        a[0] = 0.0;
    } else {
        // 'mypolyder:13' else
        // 'mypolyder:14' a = u( :, 1 : nu-1 ) .* repmat( nu-1 :-1 : 1 , nD, 1 );
        b.set_size(p5_1D.size(0), p5_1D.size(1) - 1);
        if (p5_1D.size(0) != 0) {
            int b_na;
            int i3;
            b_na = p5_1D.size(1) - 2;
            i3 = p5_1D.size(0) - 1;
            for (int b_k{0}; b_k <= b_na; b_k++) {
                for (int b_t{0}; b_t <= i3; b_t++) {
                    b[b_t + b.size(0) * b_k] = (p5_1D.size(1) - b_k) - 1;
                }
            }
        }
        if ((p5_1D.size(0) == b.size(0)) && (p5_1D.size(1) - 1 == b.size(1))) {
            int b_scalarLB;
            int b_vectorUB;
            int c_loop_ub;
            int d_loop_ub;
            c_loop_ub = p5_1D.size(0);
            d_loop_ub = p5_1D.size(1) - 1;
            a.set_size(p5_1D.size(0), p5_1D.size(1) - 1);
            b_scalarLB = (c_loop_ub / 2) << 1;
            b_vectorUB = b_scalarLB - 2;
            for (int i4{0}; i4 < d_loop_ub; i4++) {
                for (int i5{0}; i5 <= b_vectorUB; i5 += 2) {
                    __m128d r1;
                    __m128d r2;
                    r1 = _mm_loadu_pd(&p5_1D[i5 + p5_1D.size(0) * i4]);
                    r2 = _mm_loadu_pd(&b[i5 + b.size(0) * i4]);
                    _mm_storeu_pd(&a[i5 + a.size(0) * i4], _mm_mul_pd(r1, r2));
                }
                for (int i5{b_scalarLB}; i5 < c_loop_ub; i5++) {
                    a[i5 + a.size(0) * i4] =
                        p5_1D[i5 + p5_1D.size(0) * i4] * b[i5 + b.size(0) * i4];
                }
            }
        } else {
            g_binary_expand_op(a, p5_1D, b);
        }
    }
    // 'EvalTransP5:26' p5_3D = mypolyder(p5_2D);
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
    if (a.size(1) < 2) {
        // 'mypolyder:12' a = 0;
        b_a.set_size(1, 1);
        b_a[0] = 0.0;
    } else {
        // 'mypolyder:13' else
        // 'mypolyder:14' a = u( :, 1 : nu-1 ) .* repmat( nu-1 :-1 : 1 , nD, 1 );
        b.set_size(a.size(0), a.size(1) - 1);
        if (a.size(0) != 0) {
            int c_na;
            int i6;
            c_na = a.size(1) - 2;
            i6 = a.size(0) - 1;
            for (int c_k{0}; c_k <= c_na; c_k++) {
                for (int c_t{0}; c_t <= i6; c_t++) {
                    b[c_t + b.size(0) * c_k] = (a.size(1) - c_k) - 1;
                }
            }
        }
        if ((a.size(0) == b.size(0)) && (a.size(1) - 1 == b.size(1))) {
            int c_scalarLB;
            int c_vectorUB;
            int e_loop_ub;
            int f_loop_ub;
            e_loop_ub = a.size(0);
            f_loop_ub = a.size(1) - 1;
            b_a.set_size(a.size(0), a.size(1) - 1);
            c_scalarLB = (e_loop_ub / 2) << 1;
            c_vectorUB = c_scalarLB - 2;
            for (int i7{0}; i7 < f_loop_ub; i7++) {
                for (int i8{0}; i8 <= c_vectorUB; i8 += 2) {
                    __m128d r3;
                    __m128d r4;
                    r3 = _mm_loadu_pd(&a[i8 + a.size(0) * i7]);
                    r4 = _mm_loadu_pd(&b[i8 + b.size(0) * i7]);
                    _mm_storeu_pd(&b_a[i8 + b_a.size(0) * i7], _mm_mul_pd(r3, r4));
                }
                for (int i8{c_scalarLB}; i8 < e_loop_ub; i8++) {
                    b_a[i8 + b_a.size(0) * i7] = a[i8 + a.size(0) * i7] * b[i8 + b.size(0) * i7];
                }
            }
        } else {
            g_binary_expand_op(b_a, a, b);
        }
    }
    //
    // 'EvalTransP5:28' D0 = mypolyval(p5,    u_vec);
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
    D0.set_size(CurvStruct_CoeffP5.size(0), u_vec.size(1));
    g_loop_ub = u_vec.size(1);
    for (int i9{0}; i9 < g_loop_ub; i9++) {
        int h_loop_ub;
        h_loop_ub = CurvStruct_CoeffP5.size(0);
        for (int i10{0}; i10 < h_loop_ub; i10++) {
            D0[i10 + D0.size(0) * i9] = 0.0;
        }
    }
    // 'mypolyval:15' if nc > 0
    if (CurvStruct_CoeffP5.size(1) > 0) {
        // 'mypolyval:16' y( : ) = repmat( p( :, 1 ), 1, siz_x );
        D0.set_size(CurvStruct_CoeffP5.size(0), u_vec.size(1));
        if ((CurvStruct_CoeffP5.size(0) != 0) && (u_vec.size(1) != 0)) {
            int d_na;
            int i12;
            i12 = u_vec.size(1) - 1;
            d_na = CurvStruct_CoeffP5.size(0) - 1;
            for (int d_t{0}; d_t <= i12; d_t++) {
                for (int d_k{0}; d_k <= d_na; d_k++) {
                    D0[d_k + D0.size(0) * d_t] = CurvStruct_CoeffP5[d_k];
                }
            }
        }
    }
    // 'mypolyval:18' for i = 2 : nc
    i11 = CurvStruct_CoeffP5.size(1);
    if (CurvStruct_CoeffP5.size(1) - 2 >= 0) {
        outsize_idx_0 = CurvStruct_CoeffP5.size(0);
        outsize_idx_1 = u_vec.size(1);
        b_outsize_idx_0 = CurvStruct_CoeffP5.size(0);
        b_outsize_idx_1 = u_vec.size(1);
    }
    for (int b_i{0}; b_i <= i11 - 2; b_i++) {
        int i14;
        int i16;
        // 'mypolyval:19' y = repmat( x, nD, 1 ) .* y + repmat( p( :, i ), 1, siz_x );
        r5.set_size(outsize_idx_0, outsize_idx_1);
        if ((outsize_idx_0 != 0) && (outsize_idx_1 != 0)) {
            int i13;
            i13 = u_vec.size(1) - 1;
            for (int e_t{0}; e_t <= i13; e_t++) {
                int f_na;
                f_na = CurvStruct_CoeffP5.size(0) - 1;
                for (int f_k{0}; f_k <= f_na; f_k++) {
                    r5[f_k + r5.size(0) * e_t] =
                        CurvStruct_CoeffP5[f_k + CurvStruct_CoeffP5.size(0) * (b_i + 1)];
                }
            }
        }
        b.set_size(b_outsize_idx_0, b_outsize_idx_1);
        if ((b_outsize_idx_0 != 0) && (b_outsize_idx_1 != 0)) {
            int e_na;
            e_na = u_vec.size(1);
            for (int e_k{0}; e_k < e_na; e_k++) {
                int i15;
                i15 = CurvStruct_CoeffP5.size(0) - 1;
                for (int f_t{0}; f_t <= i15; f_t++) {
                    b[f_t + b.size(0) * e_k] = u_vec[e_k];
                }
            }
        }
        if (b.size(0) == 1) {
            i14 = D0.size(0);
        } else {
            i14 = b.size(0);
        }
        if (b.size(1) == 1) {
            i16 = D0.size(1);
        } else {
            i16 = b.size(1);
        }
        if ((b.size(0) == D0.size(0)) && (b.size(1) == D0.size(1)) && (i14 == r5.size(0)) &&
            (i16 == r5.size(1))) {
            int j_loop_ub;
            D0.set_size(b.size(0), b.size(1));
            j_loop_ub = b.size(1);
            for (int i18{0}; i18 < j_loop_ub; i18++) {
                int d_scalarLB;
                int d_vectorUB;
                int l_loop_ub;
                l_loop_ub = b.size(0);
                d_scalarLB = (b.size(0) / 2) << 1;
                d_vectorUB = d_scalarLB - 2;
                for (int i20{0}; i20 <= d_vectorUB; i20 += 2) {
                    __m128d r6;
                    __m128d r7;
                    __m128d r8;
                    r6 = _mm_loadu_pd(&b[i20 + b.size(0) * i18]);
                    r7 = _mm_loadu_pd(&D0[i20 + D0.size(0) * i18]);
                    r8 = _mm_loadu_pd(&r5[i20 + r5.size(0) * i18]);
                    _mm_storeu_pd(&D0[i20 + D0.size(0) * i18], _mm_add_pd(_mm_mul_pd(r6, r7), r8));
                }
                for (int i20{d_scalarLB}; i20 < l_loop_ub; i20++) {
                    D0[i20 + D0.size(0) * i18] =
                        b[i20 + b.size(0) * i18] * D0[i20 + D0.size(0) * i18] +
                        r5[i20 + r5.size(0) * i18];
                }
            }
        } else {
            e_binary_expand_op(D0, b, r5);
        }
    }
    // 'EvalTransP5:29' D1 = mypolyval(p5_1D, u_vec);
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
    D1.set_size(p5_1D.size(0), u_vec.size(1));
    i_loop_ub = u_vec.size(1);
    for (int i17{0}; i17 < i_loop_ub; i17++) {
        int k_loop_ub;
        k_loop_ub = p5_1D.size(0);
        for (int i19{0}; i19 < k_loop_ub; i19++) {
            D1[i19 + D1.size(0) * i17] = 0.0;
        }
    }
    // 'mypolyval:15' if nc > 0
    if (p5_1D.size(1) > 0) {
        // 'mypolyval:16' y( : ) = repmat( p( :, 1 ), 1, siz_x );
        D1.set_size(p5_1D.size(0), u_vec.size(1));
        if ((p5_1D.size(0) != 0) && (u_vec.size(1) != 0)) {
            int g_na;
            int i22;
            i22 = u_vec.size(1) - 1;
            g_na = p5_1D.size(0) - 1;
            for (int g_t{0}; g_t <= i22; g_t++) {
                for (int g_k{0}; g_k <= g_na; g_k++) {
                    D1[g_k + D1.size(0) * g_t] = p5_1D[g_k];
                }
            }
        }
    }
    // 'mypolyval:18' for i = 2 : nc
    i21 = p5_1D.size(1);
    if (p5_1D.size(1) - 2 >= 0) {
        c_outsize_idx_0 = p5_1D.size(0);
        c_outsize_idx_1 = u_vec.size(1);
        d_outsize_idx_0 = p5_1D.size(0);
        d_outsize_idx_1 = u_vec.size(1);
    }
    for (int c_i{0}; c_i <= i21 - 2; c_i++) {
        int i24;
        int i26;
        // 'mypolyval:19' y = repmat( x, nD, 1 ) .* y + repmat( p( :, i ), 1, siz_x );
        r5.set_size(c_outsize_idx_0, c_outsize_idx_1);
        if ((c_outsize_idx_0 != 0) && (c_outsize_idx_1 != 0)) {
            int i23;
            i23 = u_vec.size(1) - 1;
            for (int h_t{0}; h_t <= i23; h_t++) {
                int i_na;
                i_na = p5_1D.size(0) - 1;
                for (int i_k{0}; i_k <= i_na; i_k++) {
                    r5[i_k + r5.size(0) * h_t] = p5_1D[i_k + p5_1D.size(0) * (c_i + 1)];
                }
            }
        }
        b.set_size(d_outsize_idx_0, d_outsize_idx_1);
        if ((d_outsize_idx_0 != 0) && (d_outsize_idx_1 != 0)) {
            int h_na;
            h_na = u_vec.size(1);
            for (int h_k{0}; h_k < h_na; h_k++) {
                int i25;
                i25 = p5_1D.size(0) - 1;
                for (int i_t{0}; i_t <= i25; i_t++) {
                    b[i_t + b.size(0) * h_k] = u_vec[h_k];
                }
            }
        }
        if (b.size(0) == 1) {
            i24 = D1.size(0);
        } else {
            i24 = b.size(0);
        }
        if (b.size(1) == 1) {
            i26 = D1.size(1);
        } else {
            i26 = b.size(1);
        }
        if ((b.size(0) == D1.size(0)) && (b.size(1) == D1.size(1)) && (i24 == r5.size(0)) &&
            (i26 == r5.size(1))) {
            int n_loop_ub;
            D1.set_size(b.size(0), b.size(1));
            n_loop_ub = b.size(1);
            for (int i28{0}; i28 < n_loop_ub; i28++) {
                int e_scalarLB;
                int e_vectorUB;
                int p_loop_ub;
                p_loop_ub = b.size(0);
                e_scalarLB = (b.size(0) / 2) << 1;
                e_vectorUB = e_scalarLB - 2;
                for (int i30{0}; i30 <= e_vectorUB; i30 += 2) {
                    __m128d r10;
                    __m128d r11;
                    __m128d r9;
                    r9 = _mm_loadu_pd(&b[i30 + b.size(0) * i28]);
                    r10 = _mm_loadu_pd(&D1[i30 + D1.size(0) * i28]);
                    r11 = _mm_loadu_pd(&r5[i30 + r5.size(0) * i28]);
                    _mm_storeu_pd(&D1[i30 + D1.size(0) * i28],
                                  _mm_add_pd(_mm_mul_pd(r9, r10), r11));
                }
                for (int i30{e_scalarLB}; i30 < p_loop_ub; i30++) {
                    D1[i30 + D1.size(0) * i28] =
                        b[i30 + b.size(0) * i28] * D1[i30 + D1.size(0) * i28] +
                        r5[i30 + r5.size(0) * i28];
                }
            }
        } else {
            e_binary_expand_op(D1, b, r5);
        }
    }
    // 'EvalTransP5:30' D2 = mypolyval(p5_2D, u_vec);
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
    D2.set_size(a.size(0), u_vec.size(1));
    m_loop_ub = u_vec.size(1);
    for (int i27{0}; i27 < m_loop_ub; i27++) {
        int o_loop_ub;
        o_loop_ub = a.size(0);
        for (int i29{0}; i29 < o_loop_ub; i29++) {
            D2[i29 + D2.size(0) * i27] = 0.0;
        }
    }
    // 'mypolyval:15' if nc > 0
    if (a.size(1) > 0) {
        // 'mypolyval:16' y( : ) = repmat( p( :, 1 ), 1, siz_x );
        D2.set_size(a.size(0), u_vec.size(1));
        if ((a.size(0) != 0) && (u_vec.size(1) != 0)) {
            int i32;
            int j_na;
            i32 = u_vec.size(1) - 1;
            j_na = a.size(0) - 1;
            for (int j_t{0}; j_t <= i32; j_t++) {
                for (int j_k{0}; j_k <= j_na; j_k++) {
                    D2[j_k + D2.size(0) * j_t] = a[j_k];
                }
            }
        }
    }
    // 'mypolyval:18' for i = 2 : nc
    i31 = a.size(1);
    if (a.size(1) - 2 >= 0) {
        e_outsize_idx_0 = a.size(0);
        e_outsize_idx_1 = u_vec.size(1);
        f_outsize_idx_0 = a.size(0);
        f_outsize_idx_1 = u_vec.size(1);
    }
    for (int d_i{0}; d_i <= i31 - 2; d_i++) {
        int i34;
        int i36;
        // 'mypolyval:19' y = repmat( x, nD, 1 ) .* y + repmat( p( :, i ), 1, siz_x );
        r5.set_size(e_outsize_idx_0, e_outsize_idx_1);
        if ((e_outsize_idx_0 != 0) && (e_outsize_idx_1 != 0)) {
            int i33;
            i33 = u_vec.size(1) - 1;
            for (int k_t{0}; k_t <= i33; k_t++) {
                int l_na;
                l_na = a.size(0) - 1;
                for (int l_k{0}; l_k <= l_na; l_k++) {
                    r5[l_k + r5.size(0) * k_t] = a[l_k + a.size(0) * (d_i + 1)];
                }
            }
        }
        b.set_size(f_outsize_idx_0, f_outsize_idx_1);
        if ((f_outsize_idx_0 != 0) && (f_outsize_idx_1 != 0)) {
            int k_na;
            k_na = u_vec.size(1);
            for (int k_k{0}; k_k < k_na; k_k++) {
                int i35;
                i35 = a.size(0) - 1;
                for (int l_t{0}; l_t <= i35; l_t++) {
                    b[l_t + b.size(0) * k_k] = u_vec[k_k];
                }
            }
        }
        if (b.size(0) == 1) {
            i34 = D2.size(0);
        } else {
            i34 = b.size(0);
        }
        if (b.size(1) == 1) {
            i36 = D2.size(1);
        } else {
            i36 = b.size(1);
        }
        if ((b.size(0) == D2.size(0)) && (b.size(1) == D2.size(1)) && (i34 == r5.size(0)) &&
            (i36 == r5.size(1))) {
            int r_loop_ub;
            D2.set_size(b.size(0), b.size(1));
            r_loop_ub = b.size(1);
            for (int i38{0}; i38 < r_loop_ub; i38++) {
                int f_scalarLB;
                int f_vectorUB;
                int t_loop_ub;
                t_loop_ub = b.size(0);
                f_scalarLB = (b.size(0) / 2) << 1;
                f_vectorUB = f_scalarLB - 2;
                for (int i40{0}; i40 <= f_vectorUB; i40 += 2) {
                    __m128d r12;
                    __m128d r13;
                    __m128d r14;
                    r12 = _mm_loadu_pd(&b[i40 + b.size(0) * i38]);
                    r13 = _mm_loadu_pd(&D2[i40 + D2.size(0) * i38]);
                    r14 = _mm_loadu_pd(&r5[i40 + r5.size(0) * i38]);
                    _mm_storeu_pd(&D2[i40 + D2.size(0) * i38],
                                  _mm_add_pd(_mm_mul_pd(r12, r13), r14));
                }
                for (int i40{f_scalarLB}; i40 < t_loop_ub; i40++) {
                    D2[i40 + D2.size(0) * i38] =
                        b[i40 + b.size(0) * i38] * D2[i40 + D2.size(0) * i38] +
                        r5[i40 + r5.size(0) * i38];
                }
            }
        } else {
            e_binary_expand_op(D2, b, r5);
        }
    }
    // 'EvalTransP5:31' D3 = mypolyval(p5_3D, u_vec);
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
    D3.set_size(b_a.size(0), u_vec.size(1));
    q_loop_ub = u_vec.size(1);
    for (int i37{0}; i37 < q_loop_ub; i37++) {
        int s_loop_ub;
        s_loop_ub = b_a.size(0);
        for (int i39{0}; i39 < s_loop_ub; i39++) {
            D3[i39 + D3.size(0) * i37] = 0.0;
        }
    }
    // 'mypolyval:15' if nc > 0
    if (b_a.size(1) > 0) {
        // 'mypolyval:16' y( : ) = repmat( p( :, 1 ), 1, siz_x );
        D3.set_size(b_a.size(0), u_vec.size(1));
        if ((b_a.size(0) != 0) && (u_vec.size(1) != 0)) {
            int i42;
            int m_na;
            i42 = u_vec.size(1) - 1;
            m_na = b_a.size(0) - 1;
            for (int m_t{0}; m_t <= i42; m_t++) {
                for (int m_k{0}; m_k <= m_na; m_k++) {
                    D3[m_k + D3.size(0) * m_t] = b_a[m_k];
                }
            }
        }
    }
    // 'mypolyval:18' for i = 2 : nc
    i41 = b_a.size(1);
    if (b_a.size(1) - 2 >= 0) {
        g_outsize_idx_0 = b_a.size(0);
        g_outsize_idx_1 = u_vec.size(1);
        h_outsize_idx_0 = b_a.size(0);
        h_outsize_idx_1 = u_vec.size(1);
    }
    for (int e_i{0}; e_i <= i41 - 2; e_i++) {
        int i44;
        int i48;
        // 'mypolyval:19' y = repmat( x, nD, 1 ) .* y + repmat( p( :, i ), 1, siz_x );
        r5.set_size(g_outsize_idx_0, g_outsize_idx_1);
        if ((g_outsize_idx_0 != 0) && (g_outsize_idx_1 != 0)) {
            int i43;
            i43 = u_vec.size(1) - 1;
            for (int n_t{0}; n_t <= i43; n_t++) {
                int o_na;
                o_na = b_a.size(0) - 1;
                for (int o_k{0}; o_k <= o_na; o_k++) {
                    r5[o_k + r5.size(0) * n_t] = b_a[o_k + b_a.size(0) * (e_i + 1)];
                }
            }
        }
        b.set_size(h_outsize_idx_0, h_outsize_idx_1);
        if ((h_outsize_idx_0 != 0) && (h_outsize_idx_1 != 0)) {
            int n_na;
            n_na = u_vec.size(1);
            for (int n_k{0}; n_k < n_na; n_k++) {
                int i46;
                i46 = b_a.size(0) - 1;
                for (int o_t{0}; o_t <= i46; o_t++) {
                    b[o_t + b.size(0) * n_k] = u_vec[n_k];
                }
            }
        }
        if (b.size(0) == 1) {
            i44 = D3.size(0);
        } else {
            i44 = b.size(0);
        }
        if (b.size(1) == 1) {
            i48 = D3.size(1);
        } else {
            i48 = b.size(1);
        }
        if ((b.size(0) == D3.size(0)) && (b.size(1) == D3.size(1)) && (i44 == r5.size(0)) &&
            (i48 == r5.size(1))) {
            int v_loop_ub;
            D3.set_size(b.size(0), b.size(1));
            v_loop_ub = b.size(1);
            for (int i49{0}; i49 < v_loop_ub; i49++) {
                int g_scalarLB;
                int g_vectorUB;
                int x_loop_ub;
                x_loop_ub = b.size(0);
                g_scalarLB = (b.size(0) / 2) << 1;
                g_vectorUB = g_scalarLB - 2;
                for (int i52{0}; i52 <= g_vectorUB; i52 += 2) {
                    __m128d r15;
                    __m128d r16;
                    __m128d r17;
                    r15 = _mm_loadu_pd(&b[i52 + b.size(0) * i49]);
                    r16 = _mm_loadu_pd(&D3[i52 + D3.size(0) * i49]);
                    r17 = _mm_loadu_pd(&r5[i52 + r5.size(0) * i49]);
                    _mm_storeu_pd(&D3[i52 + D3.size(0) * i49],
                                  _mm_add_pd(_mm_mul_pd(r15, r16), r17));
                }
                for (int i52{g_scalarLB}; i52 < x_loop_ub; i52++) {
                    D3[i52 + D3.size(0) * i49] =
                        b[i52 + b.size(0) * i49] * D3[i52 + D3.size(0) * i49] +
                        r5[i52 + r5.size(0) * i49];
                }
            }
        } else {
            e_binary_expand_op(D3, b, r5);
        }
    }
    //
    // 'EvalTransP5:33' r_0D = D0( maskTot, : );
    end_tmp = maskTot_size[1] - 1;
    trueCount = 0;
    partialTrueCount = 0;
    for (int f_i{0}; f_i <= end_tmp; f_i++) {
        if (maskTot_data[f_i]) {
            trueCount++;
            tmp_data[partialTrueCount] = static_cast<signed char>(f_i + 1);
            partialTrueCount++;
        }
    }
    u_loop_ub = D0.size(1);
    r_0D.set_size(trueCount, D0.size(1));
    for (int i45{0}; i45 < u_loop_ub; i45++) {
        for (int i47{0}; i47 < trueCount; i47++) {
            r_0D[i47 + r_0D.size(0) * i45] = D0[(tmp_data[i47] + D0.size(0) * i45) - 1];
        }
    }
    // 'EvalTransP5:34' r_1D = D1( maskTot, : );
    b_trueCount = 0;
    b_partialTrueCount = 0;
    for (int g_i{0}; g_i <= end_tmp; g_i++) {
        if (maskTot_data[g_i]) {
            b_trueCount++;
            b_tmp_data[b_partialTrueCount] = static_cast<signed char>(g_i + 1);
            b_partialTrueCount++;
        }
    }
    w_loop_ub = D1.size(1);
    r_1D.set_size(b_trueCount, D1.size(1));
    for (int i50{0}; i50 < w_loop_ub; i50++) {
        for (int i51{0}; i51 < b_trueCount; i51++) {
            r_1D[i51 + r_1D.size(0) * i50] = D1[(b_tmp_data[i51] + D1.size(0) * i50) - 1];
        }
    }
    // 'EvalTransP5:35' r_2D = D2( maskTot, : );
    c_trueCount = 0;
    c_partialTrueCount = 0;
    for (int h_i{0}; h_i <= end_tmp; h_i++) {
        if (maskTot_data[h_i]) {
            c_trueCount++;
            c_tmp_data[c_partialTrueCount] = static_cast<signed char>(h_i + 1);
            c_partialTrueCount++;
        }
    }
    y_loop_ub = D2.size(1);
    r_2D.set_size(c_trueCount, D2.size(1));
    for (int i53{0}; i53 < y_loop_ub; i53++) {
        for (int i54{0}; i54 < c_trueCount; i54++) {
            r_2D[i54 + r_2D.size(0) * i53] = D2[(c_tmp_data[i54] + D2.size(0) * i53) - 1];
        }
    }
    // 'EvalTransP5:36' r_3D = D3( maskTot, : );
    d_trueCount = 0;
    d_partialTrueCount = 0;
    for (int i_i{0}; i_i <= end_tmp; i_i++) {
        if (maskTot_data[i_i]) {
            d_trueCount++;
            d_tmp_data[d_partialTrueCount] = static_cast<signed char>(i_i + 1);
            d_partialTrueCount++;
        }
    }
    ab_loop_ub = D3.size(1);
    r_3D.set_size(d_trueCount, D3.size(1));
    for (int i55{0}; i55 < ab_loop_ub; i55++) {
        for (int i56{0}; i56 < d_trueCount; i56++) {
            r_3D[i56 + r_3D.size(0) * i55] = D3[(d_tmp_data[i56] + D3.size(0) * i55) - 1];
        }
    }
}

//
// function [ r_0D, r_1D, r_2D, r_3D ] = EvalTransP5( CurvStruct, u_vec, ...
//                                       maskTot )
//
// EvalTransP5 : Eval the 5th order polynom used to describe the transition.
//
//  Inputs :
//  CurvStruct    : A curve structure used for the evaluation of the polynom
//  u_vec         : A vector of u values
//  maskTot       : A mask with all the index of interest
//
//  Outputs :
//  r0D   : Matrix of points for a given set of u values
//  r1D   : Matrix of points (first derivative) for a given set of u values
//  r2D   : Matrix of points (second derivative) for a given set of u values
//  r3D   : Matrix of points (third derivative) for a given set of u values
//
//
// Arguments    : const ::coder::array<double, 2U> &CurvStruct_CoeffP5
//                const double u_vec[2]
//                const bool maskTot_data[]
//                const int maskTot_size[2]
//                double r_0D_data[]
//                int r_0D_size[2]
//                double r_1D_data[]
//                int r_1D_size[2]
//                double r_2D_data[]
//                int r_2D_size[2]
//                double r_3D_data[]
//                int r_3D_size[2]
// Return Type  : void
//
void d_EvalTransP5(const ::coder::array<double, 2U> &CurvStruct_CoeffP5, const double u_vec[2],
                   const bool maskTot_data[], const int maskTot_size[2], double r_0D_data[],
                   int r_0D_size[2], double r_1D_data[], int r_1D_size[2], double r_2D_data[],
                   int r_2D_size[2], double r_3D_data[], int r_3D_size[2])
{
    ::coder::array<double, 2U> D0;
    ::coder::array<double, 2U> D1;
    ::coder::array<double, 2U> D2;
    ::coder::array<double, 2U> D3;
    ::coder::array<double, 2U> a;
    ::coder::array<double, 2U> b_a;
    ::coder::array<double, 2U> p5_1D;
    ::coder::array<int, 2U> b;
    int b_partialTrueCount;
    int b_trueCount;
    int c_partialTrueCount;
    int c_trueCount;
    int d_partialTrueCount;
    int d_trueCount;
    int end_tmp;
    int partialTrueCount;
    int trueCount;
    signed char b_tmp_data[6];
    signed char c_tmp_data[6];
    signed char d_tmp_data[6];
    signed char tmp_data[6];
    // 'EvalTransP5:17' if ~coder.target('MATLAB')
    // 'EvalTransP5:18' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalTransP5:19' coder.inline('never')
    // 'EvalTransP5:20' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalTransP5"'));
    ZoneScopedN("EvalTransP5");
    //
    // 'EvalTransP5:23' p5    = CurvStruct.CoeffP5;
    // 'EvalTransP5:24' p5_1D = mypolyder(p5);
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
    // 'EvalTransP5:25' p5_2D = mypolyder(p5_1D);
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
    if (p5_1D.size(1) < 2) {
        // 'mypolyder:12' a = 0;
        a.set_size(1, 1);
        a[0] = 0.0;
    } else {
        // 'mypolyder:13' else
        // 'mypolyder:14' a = u( :, 1 : nu-1 ) .* repmat( nu-1 :-1 : 1 , nD, 1 );
        b.set_size(p5_1D.size(0), p5_1D.size(1) - 1);
        if (p5_1D.size(0) != 0) {
            int b_na;
            int i3;
            b_na = p5_1D.size(1) - 2;
            i3 = p5_1D.size(0) - 1;
            for (int b_k{0}; b_k <= b_na; b_k++) {
                for (int b_t{0}; b_t <= i3; b_t++) {
                    b[b_t + b.size(0) * b_k] = (p5_1D.size(1) - b_k) - 1;
                }
            }
        }
        if ((p5_1D.size(0) == b.size(0)) && (p5_1D.size(1) - 1 == b.size(1))) {
            int c_loop_ub;
            int d_loop_ub;
            c_loop_ub = p5_1D.size(0);
            d_loop_ub = p5_1D.size(1) - 1;
            a.set_size(p5_1D.size(0), p5_1D.size(1) - 1);
            for (int i4{0}; i4 < d_loop_ub; i4++) {
                for (int i5{0}; i5 < c_loop_ub; i5++) {
                    a[i5 + a.size(0) * i4] = p5_1D[i5 + p5_1D.size(0) * i4] *
                                             static_cast<double>(b[i5 + b.size(0) * i4]);
                }
            }
        } else {
            binary_expand_op(a, p5_1D, b);
        }
    }
    // 'EvalTransP5:26' p5_3D = mypolyder(p5_2D);
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
    if (a.size(1) < 2) {
        // 'mypolyder:12' a = 0;
        b_a.set_size(1, 1);
        b_a[0] = 0.0;
    } else {
        // 'mypolyder:13' else
        // 'mypolyder:14' a = u( :, 1 : nu-1 ) .* repmat( nu-1 :-1 : 1 , nD, 1 );
        b.set_size(a.size(0), a.size(1) - 1);
        if (a.size(0) != 0) {
            int c_na;
            int i6;
            c_na = a.size(1) - 2;
            i6 = a.size(0) - 1;
            for (int c_k{0}; c_k <= c_na; c_k++) {
                for (int c_t{0}; c_t <= i6; c_t++) {
                    b[c_t + b.size(0) * c_k] = (a.size(1) - c_k) - 1;
                }
            }
        }
        if ((a.size(0) == b.size(0)) && (a.size(1) - 1 == b.size(1))) {
            int e_loop_ub;
            int f_loop_ub;
            e_loop_ub = a.size(0);
            f_loop_ub = a.size(1) - 1;
            b_a.set_size(a.size(0), a.size(1) - 1);
            for (int i7{0}; i7 < f_loop_ub; i7++) {
                for (int i8{0}; i8 < e_loop_ub; i8++) {
                    b_a[i8 + b_a.size(0) * i7] =
                        a[i8 + a.size(0) * i7] * static_cast<double>(b[i8 + b.size(0) * i7]);
                }
            }
        } else {
            binary_expand_op(b_a, a, b);
        }
    }
    //
    // 'EvalTransP5:28' D0 = mypolyval(p5,    u_vec);
    mypolyval(CurvStruct_CoeffP5, u_vec, D0);
    // 'EvalTransP5:29' D1 = mypolyval(p5_1D, u_vec);
    mypolyval(p5_1D, u_vec, D1);
    // 'EvalTransP5:30' D2 = mypolyval(p5_2D, u_vec);
    mypolyval(a, u_vec, D2);
    // 'EvalTransP5:31' D3 = mypolyval(p5_3D, u_vec);
    mypolyval(b_a, u_vec, D3);
    //
    // 'EvalTransP5:33' r_0D = D0( maskTot, : );
    end_tmp = maskTot_size[1] - 1;
    trueCount = 0;
    partialTrueCount = 0;
    for (int b_i{0}; b_i <= end_tmp; b_i++) {
        if (maskTot_data[b_i]) {
            trueCount++;
            tmp_data[partialTrueCount] = static_cast<signed char>(b_i + 1);
            partialTrueCount++;
        }
    }
    r_0D_size[0] = trueCount;
    r_0D_size[1] = 2;
    for (int i9{0}; i9 < 2; i9++) {
        for (int i10{0}; i10 < trueCount; i10++) {
            r_0D_data[i10 + trueCount * i9] = D0[(tmp_data[i10] + D0.size(0) * i9) - 1];
        }
    }
    // 'EvalTransP5:34' r_1D = D1( maskTot, : );
    b_trueCount = 0;
    b_partialTrueCount = 0;
    for (int c_i{0}; c_i <= end_tmp; c_i++) {
        if (maskTot_data[c_i]) {
            b_trueCount++;
            b_tmp_data[b_partialTrueCount] = static_cast<signed char>(c_i + 1);
            b_partialTrueCount++;
        }
    }
    r_1D_size[0] = b_trueCount;
    r_1D_size[1] = 2;
    for (int i11{0}; i11 < 2; i11++) {
        for (int i12{0}; i12 < b_trueCount; i12++) {
            r_1D_data[i12 + b_trueCount * i11] = D1[(b_tmp_data[i12] + D1.size(0) * i11) - 1];
        }
    }
    // 'EvalTransP5:35' r_2D = D2( maskTot, : );
    c_trueCount = 0;
    c_partialTrueCount = 0;
    for (int d_i{0}; d_i <= end_tmp; d_i++) {
        if (maskTot_data[d_i]) {
            c_trueCount++;
            c_tmp_data[c_partialTrueCount] = static_cast<signed char>(d_i + 1);
            c_partialTrueCount++;
        }
    }
    r_2D_size[0] = c_trueCount;
    r_2D_size[1] = 2;
    for (int i13{0}; i13 < 2; i13++) {
        for (int i14{0}; i14 < c_trueCount; i14++) {
            r_2D_data[i14 + c_trueCount * i13] = D2[(c_tmp_data[i14] + D2.size(0) * i13) - 1];
        }
    }
    // 'EvalTransP5:36' r_3D = D3( maskTot, : );
    d_trueCount = 0;
    d_partialTrueCount = 0;
    for (int e_i{0}; e_i <= end_tmp; e_i++) {
        if (maskTot_data[e_i]) {
            d_trueCount++;
            d_tmp_data[d_partialTrueCount] = static_cast<signed char>(e_i + 1);
            d_partialTrueCount++;
        }
    }
    r_3D_size[0] = d_trueCount;
    r_3D_size[1] = 2;
    for (int i15{0}; i15 < 2; i15++) {
        for (int i16{0}; i16 < d_trueCount; i16++) {
            r_3D_data[i16 + d_trueCount * i15] = D3[(d_tmp_data[i16] + D3.size(0) * i15) - 1];
        }
    }
}

} // namespace ocn

//
// File trailer for EvalTransP5.cpp
//
// [EOF]
//
