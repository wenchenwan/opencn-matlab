
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: constJerkU.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "constJerkU.h"
#include "coder_array.h"
#include <cmath>
#include <emmintrin.h>

// Function Definitions
//
// function [ u, ud, udd, uddd ] = constJerkU( pseudoJerk, k_vec, isEnd, forceLimits )
//
// constJerkU : Compute u and its derivative based on the pseudo jerk
//  approximation.
//
//  Inputs :
//    pseudoJerk      :  [ N x 1 ] The constant Jerk value
//    k_vec           :  [ 1 x M ] The time vector
//    isEnd           :  ( Boolean ) Is the end of the Curve.
//    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
//
//  Outputs :
//    u               :  [ N x M ]
//    ud              :  [ N x M ]
//    udd             :  [ N x M ]
//    uddd            :  [ N x M ]
//
//
// Arguments    : double pseudoJerk
//                ::coder::array<double, 2U> &k_vec
//                ::coder::array<double, 2U> &u
//                ::coder::array<double, 2U> &ud
//                ::coder::array<double, 2U> &udd
//                ::coder::array<double, 2U> &uddd
// Return Type  : void
//
namespace ocn {
void b_constJerkU(double pseudoJerk, ::coder::array<double, 2U> &k_vec,
                  ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &ud,
                  ::coder::array<double, 2U> &udd, ::coder::array<double, 2U> &uddd)
{
    ::coder::array<double, 2U> r1;
    double k_max;
    int b_end;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int c_loop_ub;
    int c_scalarLB;
    int c_vectorUB;
    int d_loop_ub;
    int d_scalarLB;
    int d_vectorUB;
    int e_loop_ub;
    int e_scalarLB;
    int e_vectorUB;
    int end;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    // 'constJerkU:18' if( coder.target( "MATLAB" ) )
    // 'constJerkU:24' if( isEnd )
    // 'constJerkU:25' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
    k_max = std::pow(6.0 / pseudoJerk, 0.33333333333333331);
    // 'constJerkU:26' k_vec  = k_max - k_vec;
    k_vec.set_size(1, k_vec.size(1));
    loop_ub = k_vec.size(1);
    scalarLB = (k_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i{0}; i <= vectorUB; i += 2) {
        __m128d r;
        r = _mm_loadu_pd(&k_vec[i]);
        _mm_storeu_pd(&k_vec[i], _mm_sub_pd(_mm_set1_pd(k_max), r));
    }
    for (int i{scalarLB}; i < loop_ub; i++) {
        k_vec[i] = k_max - k_vec[i];
    }
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:30' uddd    = pseudoJerk .* ones( size( k_vec ) );
    uddd.set_size(1, k_vec.size(1));
    b_loop_ub = k_vec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        uddd[i1] = pseudoJerk;
    }
    // 'constJerkU:31' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:32' ud      = pseudoJerk .* k_vec .^2 / 2;
    r1.set_size(1, k_vec.size(1));
    c_loop_ub = k_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        double varargin_1;
        varargin_1 = k_vec[i2];
        r1[i2] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r1.size(1));
    d_loop_ub = r1.size(1);
    b_scalarLB = (r1.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (int i3{0}; i3 <= b_vectorUB; i3 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r1[i3]);
        _mm_storeu_pd(&ud[i3],
                      _mm_div_pd(_mm_mul_pd(_mm_set1_pd(pseudoJerk), r2), _mm_set1_pd(2.0)));
    }
    for (int i3{b_scalarLB}; i3 < d_loop_ub; i3++) {
        ud[i3] = pseudoJerk * r1[i3] / 2.0;
    }
    // 'constJerkU:33' u       = pseudoJerk .* k_vec .^3 / 6;
    r1.set_size(1, k_vec.size(1));
    e_loop_ub = k_vec.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        double b_varargin_1;
        b_varargin_1 = k_vec[i4];
        r1[i4] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r1.size(1));
    f_loop_ub = r1.size(1);
    c_scalarLB = (r1.size(1) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (int i5{0}; i5 <= c_vectorUB; i5 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&r1[i5]);
        _mm_storeu_pd(&u[i5],
                      _mm_div_pd(_mm_mul_pd(_mm_set1_pd(pseudoJerk), r3), _mm_set1_pd(6.0)));
    }
    for (int i5{c_scalarLB}; i5 < f_loop_ub; i5++) {
        u[i5] = pseudoJerk * r1[i5] / 6.0;
    }
    // 'constJerkU:35' if( forceLimits )
    // 'constJerkU:36' u( u > 1 ) = 1;
    end = u.size(1);
    for (int b_i{0}; b_i < end; b_i++) {
        if (u[b_i] > 1.0) {
            u[b_i] = 1.0;
        }
    }
    // 'constJerkU:37' u( u < 0 ) = 0;
    b_end = u.size(1);
    for (int c_i{0}; c_i < b_end; c_i++) {
        if (u[c_i] < 0.0) {
            u[c_i] = 0.0;
        }
    }
    // 'constJerkU:40' if( isEnd )
    //  Reverse time ( Backward-like integration )
    // 'constJerkU:41' u    = 1 - u;
    u.set_size(1, u.size(1));
    g_loop_ub = u.size(1);
    d_scalarLB = (u.size(1) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i6{0}; i6 <= d_vectorUB; i6 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&u[i6]);
        _mm_storeu_pd(&u[i6], _mm_sub_pd(_mm_set1_pd(1.0), r4));
    }
    for (int i6{d_scalarLB}; i6 < g_loop_ub; i6++) {
        u[i6] = 1.0 - u[i6];
    }
    // 'constJerkU:42' ud   = ud;
    // 'constJerkU:43' udd  = -udd;
    udd.set_size(1, k_vec.size(1));
    h_loop_ub = k_vec.size(1);
    e_scalarLB = (k_vec.size(1) / 2) << 1;
    e_vectorUB = e_scalarLB - 2;
    for (int i7{0}; i7 <= e_vectorUB; i7 += 2) {
        __m128d r5;
        r5 = _mm_loadu_pd(&k_vec[i7]);
        _mm_storeu_pd(&udd[i7],
                      _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(pseudoJerk), r5), _mm_set1_pd(-1.0)));
    }
    for (int i7{e_scalarLB}; i7 < h_loop_ub; i7++) {
        udd[i7] = -(pseudoJerk * k_vec[i7]);
    }
    // 'constJerkU:44' uddd = uddd;
}

//
// function [ u, ud, udd, uddd ] = constJerkU( pseudoJerk, k_vec, isEnd, forceLimits )
//
// constJerkU : Compute u and its derivative based on the pseudo jerk
//  approximation.
//
//  Inputs :
//    pseudoJerk      :  [ N x 1 ] The constant Jerk value
//    k_vec           :  [ 1 x M ] The time vector
//    isEnd           :  ( Boolean ) Is the end of the Curve.
//    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
//
//  Outputs :
//    u               :  [ N x M ]
//    ud              :  [ N x M ]
//    udd             :  [ N x M ]
//    uddd            :  [ N x M ]
//
//
// Arguments    : double pseudoJerk
//                ::coder::array<double, 2U> &k_vec
//                ::coder::array<double, 2U> &u
//                ::coder::array<double, 2U> &ud
//                ::coder::array<double, 2U> &udd
// Return Type  : void
//
void constJerkU(double pseudoJerk, ::coder::array<double, 2U> &k_vec, ::coder::array<double, 2U> &u,
                ::coder::array<double, 2U> &ud, ::coder::array<double, 2U> &udd)
{
    ::coder::array<double, 2U> r1;
    double k_max;
    int b_end;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int c_loop_ub;
    int c_scalarLB;
    int c_vectorUB;
    int d_loop_ub;
    int d_scalarLB;
    int d_vectorUB;
    int e_loop_ub;
    int e_scalarLB;
    int e_vectorUB;
    int end;
    int f_loop_ub;
    int g_loop_ub;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    // 'constJerkU:18' if( coder.target( "MATLAB" ) )
    // 'constJerkU:24' if( isEnd )
    // 'constJerkU:25' k_max  = ( 6 / pseudoJerk )^( 1 / 3 );
    k_max = std::pow(6.0 / pseudoJerk, 0.33333333333333331);
    // 'constJerkU:26' k_vec  = k_max - k_vec;
    k_vec.set_size(1, k_vec.size(1));
    loop_ub = k_vec.size(1);
    scalarLB = (k_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i{0}; i <= vectorUB; i += 2) {
        __m128d r;
        r = _mm_loadu_pd(&k_vec[i]);
        _mm_storeu_pd(&k_vec[i], _mm_sub_pd(_mm_set1_pd(k_max), r));
    }
    for (int i{scalarLB}; i < loop_ub; i++) {
        k_vec[i] = k_max - k_vec[i];
    }
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:30' uddd    = pseudoJerk .* ones( size( k_vec ) );
    // 'constJerkU:31' udd     = pseudoJerk .* k_vec;
    // 'constJerkU:32' ud      = pseudoJerk .* k_vec .^2 / 2;
    r1.set_size(1, k_vec.size(1));
    b_loop_ub = k_vec.size(1);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        double varargin_1;
        varargin_1 = k_vec[i1];
        r1[i1] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r1.size(1));
    c_loop_ub = r1.size(1);
    b_scalarLB = (r1.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (int i2{0}; i2 <= b_vectorUB; i2 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r1[i2]);
        _mm_storeu_pd(&ud[i2],
                      _mm_div_pd(_mm_mul_pd(_mm_set1_pd(pseudoJerk), r2), _mm_set1_pd(2.0)));
    }
    for (int i2{b_scalarLB}; i2 < c_loop_ub; i2++) {
        ud[i2] = pseudoJerk * r1[i2] / 2.0;
    }
    // 'constJerkU:33' u       = pseudoJerk .* k_vec .^3 / 6;
    r1.set_size(1, k_vec.size(1));
    d_loop_ub = k_vec.size(1);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        double b_varargin_1;
        b_varargin_1 = k_vec[i3];
        r1[i3] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r1.size(1));
    e_loop_ub = r1.size(1);
    c_scalarLB = (r1.size(1) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (int i4{0}; i4 <= c_vectorUB; i4 += 2) {
        __m128d r3;
        r3 = _mm_loadu_pd(&r1[i4]);
        _mm_storeu_pd(&u[i4],
                      _mm_div_pd(_mm_mul_pd(_mm_set1_pd(pseudoJerk), r3), _mm_set1_pd(6.0)));
    }
    for (int i4{c_scalarLB}; i4 < e_loop_ub; i4++) {
        u[i4] = pseudoJerk * r1[i4] / 6.0;
    }
    // 'constJerkU:35' if( forceLimits )
    // 'constJerkU:36' u( u > 1 ) = 1;
    end = u.size(1);
    for (int b_i{0}; b_i < end; b_i++) {
        if (u[b_i] > 1.0) {
            u[b_i] = 1.0;
        }
    }
    // 'constJerkU:37' u( u < 0 ) = 0;
    b_end = u.size(1);
    for (int c_i{0}; c_i < b_end; c_i++) {
        if (u[c_i] < 0.0) {
            u[c_i] = 0.0;
        }
    }
    // 'constJerkU:40' if( isEnd )
    //  Reverse time ( Backward-like integration )
    // 'constJerkU:41' u    = 1 - u;
    u.set_size(1, u.size(1));
    f_loop_ub = u.size(1);
    d_scalarLB = (u.size(1) / 2) << 1;
    d_vectorUB = d_scalarLB - 2;
    for (int i5{0}; i5 <= d_vectorUB; i5 += 2) {
        __m128d r4;
        r4 = _mm_loadu_pd(&u[i5]);
        _mm_storeu_pd(&u[i5], _mm_sub_pd(_mm_set1_pd(1.0), r4));
    }
    for (int i5{d_scalarLB}; i5 < f_loop_ub; i5++) {
        u[i5] = 1.0 - u[i5];
    }
    // 'constJerkU:42' ud   = ud;
    // 'constJerkU:43' udd  = -udd;
    udd.set_size(1, k_vec.size(1));
    g_loop_ub = k_vec.size(1);
    e_scalarLB = (k_vec.size(1) / 2) << 1;
    e_vectorUB = e_scalarLB - 2;
    for (int i6{0}; i6 <= e_vectorUB; i6 += 2) {
        __m128d r5;
        r5 = _mm_loadu_pd(&k_vec[i6]);
        _mm_storeu_pd(&udd[i6],
                      _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(pseudoJerk), r5), _mm_set1_pd(-1.0)));
    }
    for (int i6{e_scalarLB}; i6 < g_loop_ub; i6++) {
        udd[i6] = -(pseudoJerk * k_vec[i6]);
    }
    // 'constJerkU:44' uddd = uddd;
}

//
// function [ u, ud, udd, uddd ] = constJerkU( pseudoJerk, k_vec, isEnd, forceLimits )
//
// constJerkU : Compute u and its derivative based on the pseudo jerk
//  approximation.
//
//  Inputs :
//    pseudoJerk      :  [ N x 1 ] The constant Jerk value
//    k_vec           :  [ 1 x M ] The time vector
//    isEnd           :  ( Boolean ) Is the end of the Curve.
//    forceLimits     :  ( Boolean ) Force u to stay in bewteen 0 and 1
//
//  Outputs :
//    u               :  [ N x M ]
//    ud              :  [ N x M ]
//    udd             :  [ N x M ]
//    uddd            :  [ N x M ]
//
//
// Arguments    : double pseudoJerk
//                const ::coder::array<double, 2U> &k_vec
//                ::coder::array<double, 2U> &u
//                ::coder::array<double, 2U> &ud
//                ::coder::array<double, 2U> &udd
//                ::coder::array<double, 2U> &uddd
// Return Type  : void
//
void constJerkU(double pseudoJerk, const ::coder::array<double, 2U> &k_vec,
                ::coder::array<double, 2U> &u, ::coder::array<double, 2U> &ud,
                ::coder::array<double, 2U> &udd, ::coder::array<double, 2U> &uddd)
{
    ::coder::array<double, 2U> r;
    int b_end;
    int b_loop_ub;
    int b_scalarLB;
    int b_vectorUB;
    int c_loop_ub;
    int c_scalarLB;
    int c_vectorUB;
    int d_loop_ub;
    int e_loop_ub;
    int end;
    int f_loop_ub;
    int loop_ub;
    int scalarLB;
    int vectorUB;
    // 'constJerkU:18' if( coder.target( "MATLAB" ) )
    // 'constJerkU:24' if( isEnd )
    //  Compute u and its derivatives based on constant jerk
    // 'constJerkU:30' uddd    = pseudoJerk .* ones( size( k_vec ) );
    uddd.set_size(1, k_vec.size(1));
    loop_ub = k_vec.size(1);
    for (int i{0}; i < loop_ub; i++) {
        uddd[i] = pseudoJerk;
    }
    // 'constJerkU:31' udd     = pseudoJerk .* k_vec;
    udd.set_size(1, k_vec.size(1));
    b_loop_ub = k_vec.size(1);
    scalarLB = (k_vec.size(1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i1{0}; i1 <= vectorUB; i1 += 2) {
        _mm_storeu_pd(&udd[i1], _mm_mul_pd(_mm_set1_pd(pseudoJerk),
                                           _mm_loadu_pd((const double *)&k_vec[i1])));
    }
    for (int i1{scalarLB}; i1 < b_loop_ub; i1++) {
        udd[i1] = pseudoJerk * k_vec[i1];
    }
    // 'constJerkU:32' ud      = pseudoJerk .* k_vec .^2 / 2;
    r.set_size(1, k_vec.size(1));
    c_loop_ub = k_vec.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        double varargin_1;
        varargin_1 = k_vec[i2];
        r[i2] = std::pow(varargin_1, 2.0);
    }
    ud.set_size(1, r.size(1));
    d_loop_ub = r.size(1);
    b_scalarLB = (r.size(1) / 2) << 1;
    b_vectorUB = b_scalarLB - 2;
    for (int i3{0}; i3 <= b_vectorUB; i3 += 2) {
        __m128d r1;
        r1 = _mm_loadu_pd(&r[i3]);
        _mm_storeu_pd(&ud[i3],
                      _mm_div_pd(_mm_mul_pd(_mm_set1_pd(pseudoJerk), r1), _mm_set1_pd(2.0)));
    }
    for (int i3{b_scalarLB}; i3 < d_loop_ub; i3++) {
        ud[i3] = pseudoJerk * r[i3] / 2.0;
    }
    // 'constJerkU:33' u       = pseudoJerk .* k_vec .^3 / 6;
    r.set_size(1, k_vec.size(1));
    e_loop_ub = k_vec.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        double b_varargin_1;
        b_varargin_1 = k_vec[i4];
        r[i4] = std::pow(b_varargin_1, 3.0);
    }
    u.set_size(1, r.size(1));
    f_loop_ub = r.size(1);
    c_scalarLB = (r.size(1) / 2) << 1;
    c_vectorUB = c_scalarLB - 2;
    for (int i5{0}; i5 <= c_vectorUB; i5 += 2) {
        __m128d r2;
        r2 = _mm_loadu_pd(&r[i5]);
        _mm_storeu_pd(&u[i5],
                      _mm_div_pd(_mm_mul_pd(_mm_set1_pd(pseudoJerk), r2), _mm_set1_pd(6.0)));
    }
    for (int i5{c_scalarLB}; i5 < f_loop_ub; i5++) {
        u[i5] = pseudoJerk * r[i5] / 6.0;
    }
    // 'constJerkU:35' if( forceLimits )
    // 'constJerkU:36' u( u > 1 ) = 1;
    end = u.size(1);
    for (int b_i{0}; b_i < end; b_i++) {
        if (u[b_i] > 1.0) {
            u[b_i] = 1.0;
        }
    }
    // 'constJerkU:37' u( u < 0 ) = 0;
    b_end = u.size(1);
    for (int c_i{0}; c_i < b_end; c_i++) {
        if (u[c_i] < 0.0) {
            u[c_i] = 0.0;
        }
    }
    // 'constJerkU:40' if( isEnd )
}

} // namespace ocn

//
// File trailer for constJerkU.cpp
//
// [EOF]
//
