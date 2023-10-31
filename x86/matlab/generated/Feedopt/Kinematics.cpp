
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Kinematics.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "Kinematics.h"
#include "kin_xyzbc_tt_J2P_jt.h"
#include "kin_xyzbc_tt_J2P_tj.h"
#include "kin_xyzbc_tt_JP_jt.h"
#include "kin_xyzbc_tt_JP_tj.h"
#include "kin_xyzbc_tt_J_jt.h"
#include "kin_xyzbc_tt_J_tj.h"
#include "kin_xyzbc_tt_forward.h"
#include "kin_xyzbc_tt_inverse.h"
#include "coder_array.h"
#include <emmintrin.h>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
namespace ocn {
Kinematics::~Kinematics() = default;

//
// Arguments    : void
// Return Type  : Kinematics
//
Kinematics::Kinematics() = default;

//
// function [ a_j ] = a_joint( this, r_t, v_t, a_t )
//
// Arguments    : const ::coder::array<double, 2U> &r_t
//                const ::coder::array<double, 2U> &v_t
//                const ::coder::array<double, 2U> &a_t
//                ::coder::array<double, 2U> &a_j
// Return Type  : void
//
void Kinematics::a_joint(const ::coder::array<double, 2U> &r_t,
                         const ::coder::array<double, 2U> &v_t,
                         const ::coder::array<double, 2U> &a_t,
                         ::coder::array<double, 2U> &a_j) const
{
    ::coder::array<double, 1U> b_r_t;
    ::coder::array<double, 1U> b_v_t;
    double b_J[5];
    double b_JP[5];
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // 'Kinematics:194' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:197' N   = size( r_t, 2 );
    // 'Kinematics:198' a_j = zeros( size( a_t ) );
    unnamed_idx_0 = static_cast<unsigned int>(a_t.size(0));
    a_j.set_size(a_t.size(0), a_t.size(1));
    loop_ub = a_t.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            a_j[i2 + a_j.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:200' for j = 1 : N
    i1 = r_t.size(1);
    for (int j{0}; j < i1; j++) {
        double J[5][5];
        double JP[5][5];
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int scalarLB;
        int vectorUB;
        // 'Kinematics:201' J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
        c_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_t[i3] = r_t[i3 + r_t.size(0) * j];
        }
        kin_xyzbc_tt_J_jt(b_r_t, parameters, J);
        // 'Kinematics:202' JP  = kin_xyzbc_tt_JP_jt( r_t( :, j ), v_t( :, j ), this.parameters );
        d_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            b_r_t[i4] = r_t[i4 + r_t.size(0) * j];
        }
        e_loop_ub = v_t.size(0);
        b_v_t.set_size(v_t.size(0));
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            b_v_t[i5] = v_t[i5 + v_t.size(0) * j];
        }
        kin_xyzbc_tt_JP_jt(b_r_t, b_v_t, parameters, JP);
        // 'Kinematics:203' a_j( :, j ) = JP * v_t( :, j ) + J * a_t( :, j );
        for (int i6{0}; i6 < 5; i6++) {
            double d;
            double d1;
            d = 0.0;
            d1 = 0.0;
            for (int i7{0}; i7 < 5; i7++) {
                d += JP[i7][i6] * v_t[i7 + v_t.size(0) * j];
                d1 += J[i7][i6] * a_t[i7 + a_t.size(0) * j];
            }
            b_J[i6] = d1;
            b_JP[i6] = d;
        }
        f_loop_ub = a_j.size(0);
        scalarLB = (a_j.size(0) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (int i8{0}; i8 <= vectorUB; i8 += 2) {
            __m128d r;
            __m128d r1;
            r = _mm_loadu_pd(&b_JP[i8]);
            r1 = _mm_loadu_pd(&b_J[i8]);
            _mm_storeu_pd(&a_j[i8 + a_j.size(0) * j], _mm_add_pd(r, r1));
        }
        for (int i8{scalarLB}; i8 < f_loop_ub; i8++) {
            a_j[i8 + a_j.size(0) * j] = b_JP[i8] + b_J[i8];
        }
    }
    //              end
}

//
// function [ a_t ] = a_relative( this, r_j, v_j, a_j )
//
// Arguments    : const ::coder::array<double, 2U> &r_j
//                const ::coder::array<double, 2U> &v_j
//                const ::coder::array<double, 2U> &a_j
//                ::coder::array<double, 2U> &a_t
// Return Type  : void
//
void Kinematics::a_relative(const ::coder::array<double, 2U> &r_j,
                            const ::coder::array<double, 2U> &v_j,
                            const ::coder::array<double, 2U> &a_j,
                            ::coder::array<double, 2U> &a_t) const
{
    ::coder::array<double, 1U> b_r_j;
    ::coder::array<double, 1U> b_v_j;
    double b_J[5];
    double b_JP[5];
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    //         %% Jacobian - First derivative
    // 'Kinematics:181' coder.inline( "never" );
    // 'Kinematics:183' N   = size( r_j, 2 );
    // 'Kinematics:184' a_t = zeros( size( a_j ) );
    unnamed_idx_0 = static_cast<unsigned int>(a_j.size(0));
    a_t.set_size(a_j.size(0), a_j.size(1));
    loop_ub = a_j.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            a_t[i2 + a_t.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:186' for j = 1 : N
    i1 = r_j.size(1);
    for (int j{0}; j < i1; j++) {
        double J[5][5];
        double JP[5][5];
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int scalarLB;
        int vectorUB;
        // 'Kinematics:187' J   = kin_xyzbc_tt_J_tj( r_j( :, j ), this.parameters );
        c_loop_ub = r_j.size(0);
        b_r_j.set_size(r_j.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_j[i3] = r_j[i3 + r_j.size(0) * j];
        }
        kin_xyzbc_tt_J_tj(b_r_j, parameters, J);
        // 'Kinematics:188' JP  = kin_xyzbc_tt_JP_tj( r_j( :, j ), v_j( :, j ), this.parameters );
        d_loop_ub = r_j.size(0);
        b_r_j.set_size(r_j.size(0));
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            b_r_j[i4] = r_j[i4 + r_j.size(0) * j];
        }
        e_loop_ub = v_j.size(0);
        b_v_j.set_size(v_j.size(0));
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            b_v_j[i5] = v_j[i5 + v_j.size(0) * j];
        }
        kin_xyzbc_tt_JP_tj(b_r_j, b_v_j, parameters, JP);
        // 'Kinematics:189' a_t( :, j ) = JP * v_j( :, j ) + J * a_j( :, j );
        for (int i6{0}; i6 < 5; i6++) {
            double d;
            double d1;
            d = 0.0;
            d1 = 0.0;
            for (int i7{0}; i7 < 5; i7++) {
                d += JP[i7][i6] * v_j[i7 + v_j.size(0) * j];
                d1 += J[i7][i6] * a_j[i7 + a_j.size(0) * j];
            }
            b_J[i6] = d1;
            b_JP[i6] = d;
        }
        f_loop_ub = a_t.size(0);
        scalarLB = (a_t.size(0) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (int i8{0}; i8 <= vectorUB; i8 += 2) {
            __m128d r;
            __m128d r1;
            r = _mm_loadu_pd(&b_JP[i8]);
            r1 = _mm_loadu_pd(&b_J[i8]);
            _mm_storeu_pd(&a_t[i8 + a_t.size(0) * j], _mm_add_pd(r, r1));
        }
        for (int i8{scalarLB}; i8 < f_loop_ub; i8++) {
            a_t[i8 + a_t.size(0) * j] = b_JP[i8] + b_J[i8];
        }
    }
}

//
// function [ this ] = Kinematics( type, parameters )
//
// Arguments    : const char b_type[8]
//                const double parameters_data[]
//                int parameters_size
// Return Type  : void
//
void Kinematics::init(const char b_type[8], const double parameters_data[], int parameters_size)
{
    // ----------------------------------------------------------------%
    //  Kinematics Wrapper class to C interfaces
    // ----------------------------------------------------------------%
    // 'Kinematics:29' coder.inline( "never" );
    // 'Kinematics:30' this            = this.set_index();
    // 'Kinematics:15' ind     = [ 1 : 3 ];
    // 'Kinematics:16' this.indM    = ind + 0;
    // 'Kinematics:17' this.indT    = ind + this.indM(end);
    // 'Kinematics:18' this.indP    = ind + this.indT(end);
    indM[0] = 1.0;
    indT[0] = 4.0;
    indP[0] = 7.0;
    indM[1] = 2.0;
    indT[1] = 5.0;
    indP[1] = 8.0;
    indM[2] = 3.0;
    indT[2] = 6.0;
    indP[2] = 9.0;
    // 'Kinematics:31' this.type       = type;
    for (int i{0}; i < 8; i++) {
        type[i] = b_type[i];
    }
    // 'Kinematics:32' this.parameters = parameters( : );
    parameters.set_size(parameters_size);
    for (int i1{0}; i1 < parameters_size; i1++) {
        parameters[i1] = parameters_data[i1];
    }
    // 'Kinematics:33' [ this ]        = set_function_ptr( this );
    //  Not implemented due to problem of support in code
    //  generation...
    // ----------------------------------------------------------------%
    //  Support for different kinematics only for matlab flow
    // ----------------------------------------------------------------%
}

//
// function [ j_j ] = j_joint( this, r_t, v_t, a_t, j_t )
//
// Arguments    : const ::coder::array<double, 2U> &r_t
//                const ::coder::array<double, 2U> &v_t
//                const ::coder::array<double, 2U> &a_t
//                const ::coder::array<double, 2U> &j_t
//                ::coder::array<double, 2U> &j_j
// Return Type  : void
//
void Kinematics::j_joint(const ::coder::array<double, 2U> &r_t,
                         const ::coder::array<double, 2U> &v_t,
                         const ::coder::array<double, 2U> &a_t,
                         const ::coder::array<double, 2U> &j_t,
                         ::coder::array<double, 2U> &j_j) const
{
    ::coder::array<double, 1U> b_a_t;
    ::coder::array<double, 1U> b_r_t;
    ::coder::array<double, 1U> b_v_t;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // 'Kinematics:226' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:229' N   = size( r_t, 2 );
    // 'Kinematics:230' j_j = zeros( size( j_t ) );
    unnamed_idx_0 = static_cast<unsigned int>(j_t.size(0));
    j_j.set_size(j_t.size(0), j_t.size(1));
    loop_ub = j_t.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            j_j[i2 + j_j.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:232' for j = 1 : N
    i1 = r_t.size(1);
    for (int j{0}; j < i1; j++) {
        double J[5][5];
        double J2P[5][5];
        double JP[5][5];
        double b_J2P[5];
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i_loop_ub;
        // 'Kinematics:233' J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
        c_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_t[i3] = r_t[i3 + r_t.size(0) * j];
        }
        kin_xyzbc_tt_J_jt(b_r_t, parameters, J);
        // 'Kinematics:234' JP  = kin_xyzbc_tt_JP_jt( r_t( :, j ), v_t( :, j ), this.parameters );
        d_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            b_r_t[i4] = r_t[i4 + r_t.size(0) * j];
        }
        e_loop_ub = v_t.size(0);
        b_v_t.set_size(v_t.size(0));
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            b_v_t[i5] = v_t[i5 + v_t.size(0) * j];
        }
        kin_xyzbc_tt_JP_jt(b_r_t, b_v_t, parameters, JP);
        // 'Kinematics:235' J2P = kin_xyzbc_tt_J2P_jt( r_t( :, j ), v_t( :, j ), a_t( :, j ),
        // this.parameters );
        f_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i6{0}; i6 < f_loop_ub; i6++) {
            b_r_t[i6] = r_t[i6 + r_t.size(0) * j];
        }
        g_loop_ub = v_t.size(0);
        b_v_t.set_size(v_t.size(0));
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            b_v_t[i7] = v_t[i7 + v_t.size(0) * j];
        }
        h_loop_ub = a_t.size(0);
        b_a_t.set_size(a_t.size(0));
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            b_a_t[i8] = a_t[i8 + a_t.size(0) * j];
        }
        kin_xyzbc_tt_J2P_jt(b_r_t, b_v_t, b_a_t, parameters, J2P);
        // 'Kinematics:236' j_j( :, j ) = J2P * v_t( :, j ) + 2 * JP * a_t( :, j ) + J * j_t( :, j
        // );
        for (int i9{0}; i9 < 5; i9++) {
            double d;
            double d1;
            double d2;
            d = 0.0;
            d1 = 0.0;
            d2 = 0.0;
            for (int i11{0}; i11 < 5; i11++) {
                d1 += J2P[i11][i9] * v_t[i11 + v_t.size(0) * j];
                d2 += 2.0 * JP[i11][i9] * a_t[i11 + a_t.size(0) * j];
                d += J[i11][i9] * j_t[i11 + j_t.size(0) * j];
            }
            b_J2P[i9] = (d1 + d2) + d;
        }
        i_loop_ub = j_j.size(0);
        for (int i10{0}; i10 < i_loop_ub; i10++) {
            j_j[i10 + j_j.size(0) * j] = b_J2P[i10];
        }
    }
    //              end
}

//
// function [ j_t ] = j_relative( this, r_j, v_j, a_j, j_j )
//
// Arguments    : const ::coder::array<double, 2U> &r_j
//                const ::coder::array<double, 2U> &v_j
//                const ::coder::array<double, 2U> &a_j
//                const ::coder::array<double, 2U> &j_j
//                ::coder::array<double, 2U> &j_t
// Return Type  : void
//
void Kinematics::j_relative(const ::coder::array<double, 2U> &r_j,
                            const ::coder::array<double, 2U> &v_j,
                            const ::coder::array<double, 2U> &a_j,
                            const ::coder::array<double, 2U> &j_j,
                            ::coder::array<double, 2U> &j_t) const
{
    ::coder::array<double, 1U> b_a_j;
    ::coder::array<double, 1U> b_r_j;
    ::coder::array<double, 1U> b_v_j;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    //         %% Jacobian - Second derivative
    // 'Kinematics:210' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:213' N   = size( r_j, 2 );
    // 'Kinematics:214' j_t = zeros( size( j_j ) );
    unnamed_idx_0 = static_cast<unsigned int>(j_j.size(0));
    j_t.set_size(j_j.size(0), j_j.size(1));
    loop_ub = j_j.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            j_t[i2 + j_t.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:216' for j = 1 : N
    i1 = r_j.size(1);
    for (int j{0}; j < i1; j++) {
        double J[5][5];
        double J2P[5][5];
        double JP[5][5];
        double b_J2P[5];
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        int h_loop_ub;
        int i_loop_ub;
        // 'Kinematics:217' J   = kin_xyzbc_tt_J_tj( r_j( :, j ), this.parameters );
        c_loop_ub = r_j.size(0);
        b_r_j.set_size(r_j.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_j[i3] = r_j[i3 + r_j.size(0) * j];
        }
        kin_xyzbc_tt_J_tj(b_r_j, parameters, J);
        // 'Kinematics:218' JP  = kin_xyzbc_tt_JP_tj( r_j( :, j ), v_j( :, j ), this.parameters );
        d_loop_ub = r_j.size(0);
        b_r_j.set_size(r_j.size(0));
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            b_r_j[i4] = r_j[i4 + r_j.size(0) * j];
        }
        e_loop_ub = v_j.size(0);
        b_v_j.set_size(v_j.size(0));
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            b_v_j[i5] = v_j[i5 + v_j.size(0) * j];
        }
        kin_xyzbc_tt_JP_tj(b_r_j, b_v_j, parameters, JP);
        // 'Kinematics:219' J2P = kin_xyzbc_tt_J2P_tj( r_j( :, j ), v_j( :, j ), a_j( :, j ),
        // this.parameters );
        f_loop_ub = r_j.size(0);
        b_r_j.set_size(r_j.size(0));
        for (int i6{0}; i6 < f_loop_ub; i6++) {
            b_r_j[i6] = r_j[i6 + r_j.size(0) * j];
        }
        g_loop_ub = v_j.size(0);
        b_v_j.set_size(v_j.size(0));
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            b_v_j[i7] = v_j[i7 + v_j.size(0) * j];
        }
        h_loop_ub = a_j.size(0);
        b_a_j.set_size(a_j.size(0));
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            b_a_j[i8] = a_j[i8 + a_j.size(0) * j];
        }
        kin_xyzbc_tt_J2P_tj(b_r_j, b_v_j, b_a_j, parameters, J2P);
        // 'Kinematics:220' j_t( :, j ) = J2P * v_j( :, j ) + 2 * JP * a_j( :, j ) + J * j_j( :, j
        // );
        for (int i9{0}; i9 < 5; i9++) {
            double d;
            double d1;
            double d2;
            d = 0.0;
            d1 = 0.0;
            d2 = 0.0;
            for (int i11{0}; i11 < 5; i11++) {
                d1 += J2P[i11][i9] * v_j[i11 + v_j.size(0) * j];
                d2 += 2.0 * JP[i11][i9] * a_j[i11 + a_j.size(0) * j];
                d += J[i11][i9] * j_j[i11 + j_j.size(0) * j];
            }
            b_J2P[i9] = (d1 + d2) + d;
        }
        i_loop_ub = j_t.size(0);
        for (int i10{0}; i10 < i_loop_ub; i10++) {
            j_t[i10 + j_t.size(0) * j] = b_J2P[i10];
        }
    }
    //              end
}

//
// function [ r_j, v_j, a_j, j_j ] = joint( this, r_t, v_t, a_t, j_t )
//
// Arguments    : const ::coder::array<double, 2U> &r_t
//                const ::coder::array<double, 2U> &v_t
//                const ::coder::array<double, 2U> &a_t
//                ::coder::array<double, 2U> &r_j
//                ::coder::array<double, 2U> &v_j
//                ::coder::array<double, 2U> &a_j
// Return Type  : void
//
void Kinematics::joint(const ::coder::array<double, 2U> &r_t, const ::coder::array<double, 2U> &v_t,
                       const ::coder::array<double, 2U> &a_t, ::coder::array<double, 2U> &r_j,
                       ::coder::array<double, 2U> &v_j, ::coder::array<double, 2U> &a_j) const
{
    ::coder::array<double, 1U> b_r_t;
    ::coder::array<double, 1U> b_v_t;
    double b_J[5];
    double b_JP[5];
    int c_loop_ub;
    int e_loop_ub;
    int i6;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // 'Kinematics:130' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:133' N   = size( r_t, 2 );
    // 'Kinematics:134' r_j = zeros( size( r_t ) );
    unnamed_idx_0 = static_cast<unsigned int>(r_t.size(0));
    r_j.set_size(r_t.size(0), r_t.size(1));
    loop_ub = r_t.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            r_j[i1 + r_j.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:135' v_j = zeros( size( v_t ) );
    unnamed_idx_0 = static_cast<unsigned int>(v_t.size(0));
    v_j.set_size(v_t.size(0), v_t.size(1));
    c_loop_ub = v_t.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            v_j[i3 + v_j.size(0) * i2] = 0.0;
        }
    }
    // 'Kinematics:136' a_j = zeros( size( a_t ) );
    unnamed_idx_0 = static_cast<unsigned int>(a_t.size(0));
    a_j.set_size(a_t.size(0), a_t.size(1));
    e_loop_ub = a_t.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        int f_loop_ub;
        f_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            a_j[i5 + a_j.size(0) * i4] = 0.0;
        }
    }
    // 'Kinematics:137' j_j = zeros( size( j_t ) );
    // 'Kinematics:139' for j = 1 : N
    i6 = r_t.size(1);
    for (int j{0}; j < i6; j++) {
        double J[5][5];
        double JP[5][5];
        double dv[5];
        int g_loop_ub;
        int h_loop_ub;
        int i_loop_ub;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        int m_loop_ub;
        int scalarLB;
        int vectorUB;
        // 'Kinematics:140' J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
        g_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            b_r_t[i7] = r_t[i7 + r_t.size(0) * j];
        }
        kin_xyzbc_tt_J_jt(b_r_t, parameters, J);
        // 'Kinematics:141' JP  = kin_xyzbc_tt_JP_jt( r_t( :, j ), v_t( :, j ), this.parameters );
        h_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            b_r_t[i8] = r_t[i8 + r_t.size(0) * j];
        }
        i_loop_ub = v_t.size(0);
        b_v_t.set_size(v_t.size(0));
        for (int i9{0}; i9 < i_loop_ub; i9++) {
            b_v_t[i9] = v_t[i9 + v_t.size(0) * j];
        }
        kin_xyzbc_tt_JP_jt(b_r_t, b_v_t, parameters, JP);
        // 'Kinematics:142' J2P = kin_xyzbc_tt_J2P_jt( r_t( :, j ), v_t( :, j ), a_t( :, j ),
        // this.parameters ); 'Kinematics:143' r_j( :, j ) = kin_xyzbc_tt_inverse( r_t( :, j ),
        // this.parameters );
        j_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i10{0}; i10 < j_loop_ub; i10++) {
            b_r_t[i10] = r_t[i10 + r_t.size(0) * j];
        }
        kin_xyzbc_tt_inverse(b_r_t, parameters, dv);
        k_loop_ub = r_j.size(0);
        for (int i11{0}; i11 < k_loop_ub; i11++) {
            r_j[i11 + r_j.size(0) * j] = dv[i11];
        }
        // 'Kinematics:144' v_j( :, j ) = J * v_t( :, j );
        for (int i12{0}; i12 < 5; i12++) {
            double d;
            d = 0.0;
            for (int i14{0}; i14 < 5; i14++) {
                d += J[i14][i12] * v_t[i14 + v_t.size(0) * j];
            }
            b_J[i12] = d;
        }
        l_loop_ub = v_j.size(0);
        for (int i13{0}; i13 < l_loop_ub; i13++) {
            v_j[i13 + v_j.size(0) * j] = b_J[i13];
        }
        // 'Kinematics:145' a_j( :, j ) = JP * v_t( :, j ) + J * a_t( :, j );
        for (int i15{0}; i15 < 5; i15++) {
            double d1;
            double d2;
            d1 = 0.0;
            d2 = 0.0;
            for (int i16{0}; i16 < 5; i16++) {
                d1 += JP[i16][i15] * v_t[i16 + v_t.size(0) * j];
                d2 += J[i16][i15] * a_t[i16 + a_t.size(0) * j];
            }
            b_J[i15] = d2;
            b_JP[i15] = d1;
        }
        m_loop_ub = a_j.size(0);
        scalarLB = (a_j.size(0) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (int i17{0}; i17 <= vectorUB; i17 += 2) {
            __m128d r;
            __m128d r1;
            r = _mm_loadu_pd(&b_JP[i17]);
            r1 = _mm_loadu_pd(&b_J[i17]);
            _mm_storeu_pd(&a_j[i17 + a_j.size(0) * j], _mm_add_pd(r, r1));
        }
        for (int i17{scalarLB}; i17 < m_loop_ub; i17++) {
            a_j[i17 + a_j.size(0) * j] = b_JP[i17] + b_J[i17];
        }
        // 'Kinematics:146' j_j( :, j ) = J2P * v_t( :, j ) + 2 * JP * a_t( :, j ) + J * j_t( :, j
        // );
    }
    //              end
}

//
// function [ r_j, v_j, a_j, j_j ] = joint( this, r_t, v_t, a_t, j_t )
//
// Arguments    : const ::coder::array<double, 2U> &r_t
//                const ::coder::array<double, 2U> &v_t
//                const ::coder::array<double, 2U> &a_t
//                const ::coder::array<double, 2U> &j_t
//                ::coder::array<double, 2U> &r_j
//                ::coder::array<double, 2U> &v_j
//                ::coder::array<double, 2U> &a_j
//                ::coder::array<double, 2U> &j_j
// Return Type  : void
//
void Kinematics::joint(const ::coder::array<double, 2U> &r_t, const ::coder::array<double, 2U> &v_t,
                       const ::coder::array<double, 2U> &a_t, const ::coder::array<double, 2U> &j_t,
                       ::coder::array<double, 2U> &r_j, ::coder::array<double, 2U> &v_j,
                       ::coder::array<double, 2U> &a_j, ::coder::array<double, 2U> &j_j) const
{
    ::coder::array<double, 1U> b_a_t;
    ::coder::array<double, 1U> b_r_t;
    ::coder::array<double, 1U> b_v_t;
    double b_J[5];
    double b_JP[5];
    int c_loop_ub;
    int e_loop_ub;
    int g_loop_ub;
    int i7;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // 'Kinematics:130' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:133' N   = size( r_t, 2 );
    // 'Kinematics:134' r_j = zeros( size( r_t ) );
    unnamed_idx_0 = static_cast<unsigned int>(r_t.size(0));
    r_j.set_size(r_t.size(0), r_t.size(1));
    loop_ub = r_t.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            r_j[i1 + r_j.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:135' v_j = zeros( size( v_t ) );
    unnamed_idx_0 = static_cast<unsigned int>(v_t.size(0));
    v_j.set_size(v_t.size(0), v_t.size(1));
    c_loop_ub = v_t.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            v_j[i3 + v_j.size(0) * i2] = 0.0;
        }
    }
    // 'Kinematics:136' a_j = zeros( size( a_t ) );
    unnamed_idx_0 = static_cast<unsigned int>(a_t.size(0));
    a_j.set_size(a_t.size(0), a_t.size(1));
    e_loop_ub = a_t.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        int f_loop_ub;
        f_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            a_j[i5 + a_j.size(0) * i4] = 0.0;
        }
    }
    // 'Kinematics:137' j_j = zeros( size( j_t ) );
    unnamed_idx_0 = static_cast<unsigned int>(j_t.size(0));
    j_j.set_size(j_t.size(0), j_t.size(1));
    g_loop_ub = j_t.size(1);
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        int h_loop_ub;
        h_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            j_j[i8 + j_j.size(0) * i6] = 0.0;
        }
    }
    // 'Kinematics:139' for j = 1 : N
    i7 = r_t.size(1);
    for (int j{0}; j < i7; j++) {
        double J[5][5];
        double J2P[5][5];
        double JP[5][5];
        double b_J2P[5];
        double dv[5];
        int i_loop_ub;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        int m_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        int p_loop_ub;
        int q_loop_ub;
        int r_loop_ub;
        int s_loop_ub;
        int scalarLB;
        int vectorUB;
        // 'Kinematics:140' J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
        i_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i9{0}; i9 < i_loop_ub; i9++) {
            b_r_t[i9] = r_t[i9 + r_t.size(0) * j];
        }
        kin_xyzbc_tt_J_jt(b_r_t, parameters, J);
        // 'Kinematics:141' JP  = kin_xyzbc_tt_JP_jt( r_t( :, j ), v_t( :, j ), this.parameters );
        j_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i10{0}; i10 < j_loop_ub; i10++) {
            b_r_t[i10] = r_t[i10 + r_t.size(0) * j];
        }
        k_loop_ub = v_t.size(0);
        b_v_t.set_size(v_t.size(0));
        for (int i11{0}; i11 < k_loop_ub; i11++) {
            b_v_t[i11] = v_t[i11 + v_t.size(0) * j];
        }
        kin_xyzbc_tt_JP_jt(b_r_t, b_v_t, parameters, JP);
        // 'Kinematics:142' J2P = kin_xyzbc_tt_J2P_jt( r_t( :, j ), v_t( :, j ), a_t( :, j ),
        // this.parameters );
        l_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i12{0}; i12 < l_loop_ub; i12++) {
            b_r_t[i12] = r_t[i12 + r_t.size(0) * j];
        }
        m_loop_ub = v_t.size(0);
        b_v_t.set_size(v_t.size(0));
        for (int i13{0}; i13 < m_loop_ub; i13++) {
            b_v_t[i13] = v_t[i13 + v_t.size(0) * j];
        }
        n_loop_ub = a_t.size(0);
        b_a_t.set_size(a_t.size(0));
        for (int i14{0}; i14 < n_loop_ub; i14++) {
            b_a_t[i14] = a_t[i14 + a_t.size(0) * j];
        }
        kin_xyzbc_tt_J2P_jt(b_r_t, b_v_t, b_a_t, parameters, J2P);
        // 'Kinematics:143' r_j( :, j ) = kin_xyzbc_tt_inverse( r_t( :, j ), this.parameters );
        o_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i15{0}; i15 < o_loop_ub; i15++) {
            b_r_t[i15] = r_t[i15 + r_t.size(0) * j];
        }
        kin_xyzbc_tt_inverse(b_r_t, parameters, dv);
        p_loop_ub = r_j.size(0);
        for (int i16{0}; i16 < p_loop_ub; i16++) {
            r_j[i16 + r_j.size(0) * j] = dv[i16];
        }
        // 'Kinematics:144' v_j( :, j ) = J * v_t( :, j );
        for (int i17{0}; i17 < 5; i17++) {
            double d;
            d = 0.0;
            for (int i19{0}; i19 < 5; i19++) {
                d += J[i19][i17] * v_t[i19 + v_t.size(0) * j];
            }
            b_J[i17] = d;
        }
        q_loop_ub = v_j.size(0);
        for (int i18{0}; i18 < q_loop_ub; i18++) {
            v_j[i18 + v_j.size(0) * j] = b_J[i18];
        }
        // 'Kinematics:145' a_j( :, j ) = JP * v_t( :, j ) + J * a_t( :, j );
        for (int i20{0}; i20 < 5; i20++) {
            double d1;
            double d2;
            d1 = 0.0;
            d2 = 0.0;
            for (int i21{0}; i21 < 5; i21++) {
                d1 += JP[i21][i20] * v_t[i21 + v_t.size(0) * j];
                d2 += J[i21][i20] * a_t[i21 + a_t.size(0) * j];
            }
            b_J[i20] = d2;
            b_JP[i20] = d1;
        }
        r_loop_ub = a_j.size(0);
        scalarLB = (a_j.size(0) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (int i22{0}; i22 <= vectorUB; i22 += 2) {
            __m128d r;
            __m128d r1;
            r = _mm_loadu_pd(&b_JP[i22]);
            r1 = _mm_loadu_pd(&b_J[i22]);
            _mm_storeu_pd(&a_j[i22 + a_j.size(0) * j], _mm_add_pd(r, r1));
        }
        for (int i22{scalarLB}; i22 < r_loop_ub; i22++) {
            a_j[i22 + a_j.size(0) * j] = b_JP[i22] + b_J[i22];
        }
        // 'Kinematics:146' j_j( :, j ) = J2P * v_t( :, j ) + 2 * JP * a_t( :, j ) + J * j_t( :, j
        // );
        for (int i23{0}; i23 < 5; i23++) {
            double d3;
            double d4;
            double d5;
            d3 = 0.0;
            d4 = 0.0;
            d5 = 0.0;
            for (int i25{0}; i25 < 5; i25++) {
                d4 += J2P[i25][i23] * v_t[i25 + v_t.size(0) * j];
                d5 += 2.0 * JP[i25][i23] * a_t[i25 + a_t.size(0) * j];
                d3 += J[i25][i23] * j_t[i25 + j_t.size(0) * j];
            }
            b_J2P[i23] = (d4 + d5) + d3;
        }
        s_loop_ub = j_j.size(0);
        for (int i24{0}; i24 < s_loop_ub; i24++) {
            j_j[i24 + j_j.size(0) * j] = b_J2P[i24];
        }
    }
    //              end
}

//
// function [ r_j ] = r_joint( this, r_t )
//
// Arguments    : const ::coder::array<double, 2U> &r_t
//                ::coder::array<double, 2U> &r_j
// Return Type  : void
//
void Kinematics::r_joint(const ::coder::array<double, 2U> &r_t,
                         ::coder::array<double, 2U> &r_j) const
{
    ::coder::array<double, 1U> b_r_t;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // 'Kinematics:92' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:95' N   = size( r_t, 2 );
    // 'Kinematics:96' r_j = zeros( size( r_t ) );
    unnamed_idx_0 = static_cast<unsigned int>(r_t.size(0));
    r_j.set_size(r_t.size(0), r_t.size(1));
    loop_ub = r_t.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            r_j[i2 + r_j.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:97' for j = 1 : N
    i1 = r_t.size(1);
    for (int j{0}; j < i1; j++) {
        double dv[5];
        int c_loop_ub;
        int d_loop_ub;
        // 'Kinematics:98' r_j( :, j ) = kin_xyzbc_tt_inverse( r_t( : , j ), this.parameters );
        c_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_t[i3] = r_t[i3 + r_t.size(0) * j];
        }
        kin_xyzbc_tt_inverse(b_r_t, parameters, dv);
        d_loop_ub = r_j.size(0);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            r_j[i4 + r_j.size(0) * j] = dv[i4];
        }
    }
    //              end
}

//
// function [ r_t ] = r_relative( this, r_j )
//
// Arguments    : const ::coder::array<double, 2U> &r_j
//                ::coder::array<double, 2U> &r_t
// Return Type  : void
//
void Kinematics::r_relative(const ::coder::array<double, 2U> &r_j,
                            ::coder::array<double, 2U> &r_t) const
{
    ::coder::array<double, 1U> b_r_j;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // ----------------------------------------------------------------%
    //  Basic kinematics
    // ----------------------------------------------------------------%
    // 'Kinematics:80' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:83' N   = size( r_j, 2 );
    // 'Kinematics:84' r_t = zeros( size( r_j ) );
    unnamed_idx_0 = static_cast<unsigned int>(r_j.size(0));
    r_t.set_size(r_j.size(0), r_j.size(1));
    loop_ub = r_j.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            r_t[i2 + r_t.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:85' for j = 1 : N
    i1 = r_j.size(1);
    for (int j{0}; j < i1; j++) {
        double dv[5];
        int c_loop_ub;
        int d_loop_ub;
        // 'Kinematics:86' r_t( :, j ) = kin_xyzbc_tt_forward( r_j( : , j ), this.parameters );
        c_loop_ub = r_j.size(0);
        b_r_j.set_size(r_j.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_j[i3] = r_j[i3 + r_j.size(0) * j];
        }
        kin_xyzbc_tt_forward(b_r_j, parameters, dv);
        d_loop_ub = r_t.size(0);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            r_t[i4 + r_t.size(0) * j] = dv[i4];
        }
    }
    //              end
}

//
// function [ r_t, v_t, a_t, j_t ] = relative( this, r_j, v_j, a_j, j_j )
//
// Arguments    : const ::coder::array<double, 2U> &r_j
//                const ::coder::array<double, 2U> &v_j
//                const ::coder::array<double, 2U> &a_j
//                const ::coder::array<double, 2U> &j_j
//                ::coder::array<double, 2U> &r_t
//                ::coder::array<double, 2U> &v_t
//                ::coder::array<double, 2U> &a_t
//                ::coder::array<double, 2U> &j_t
// Return Type  : void
//
void Kinematics::relative(const ::coder::array<double, 2U> &r_j,
                          const ::coder::array<double, 2U> &v_j,
                          const ::coder::array<double, 2U> &a_j,
                          const ::coder::array<double, 2U> &j_j, ::coder::array<double, 2U> &r_t,
                          ::coder::array<double, 2U> &v_t, ::coder::array<double, 2U> &a_t,
                          ::coder::array<double, 2U> &j_t) const
{
    ::coder::array<double, 1U> b_a_j;
    ::coder::array<double, 1U> b_r_j;
    ::coder::array<double, 1U> b_v_j;
    double b_J[5];
    double b_JP[5];
    int c_loop_ub;
    int e_loop_ub;
    int g_loop_ub;
    int i7;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // ----------------------------------------------------------------%
    //  Advanced kinematics
    // ----------------------------------------------------------------%
    //         %% All
    // 'Kinematics:108' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:111' N   = size( r_j, 2 );
    // 'Kinematics:112' r_t = zeros( size( r_j ) );
    unnamed_idx_0 = static_cast<unsigned int>(r_j.size(0));
    r_t.set_size(r_j.size(0), r_j.size(1));
    loop_ub = r_j.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            r_t[i1 + r_t.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:113' v_t = zeros( size( v_j ) );
    unnamed_idx_0 = static_cast<unsigned int>(v_j.size(0));
    v_t.set_size(v_j.size(0), v_j.size(1));
    c_loop_ub = v_j.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            v_t[i3 + v_t.size(0) * i2] = 0.0;
        }
    }
    // 'Kinematics:114' a_t = zeros( size( a_j ) );
    unnamed_idx_0 = static_cast<unsigned int>(a_j.size(0));
    a_t.set_size(a_j.size(0), a_j.size(1));
    e_loop_ub = a_j.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        int f_loop_ub;
        f_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            a_t[i5 + a_t.size(0) * i4] = 0.0;
        }
    }
    // 'Kinematics:115' j_t = zeros( size( j_j ) );
    unnamed_idx_0 = static_cast<unsigned int>(j_j.size(0));
    j_t.set_size(j_j.size(0), j_j.size(1));
    g_loop_ub = j_j.size(1);
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        int h_loop_ub;
        h_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            j_t[i8 + j_t.size(0) * i6] = 0.0;
        }
    }
    // 'Kinematics:117' for j = 1 : N
    i7 = r_j.size(1);
    for (int j{0}; j < i7; j++) {
        double J[5][5];
        double J2P[5][5];
        double JP[5][5];
        double b_J2P[5];
        double dv[5];
        int i_loop_ub;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        int m_loop_ub;
        int n_loop_ub;
        int o_loop_ub;
        int p_loop_ub;
        int q_loop_ub;
        int r_loop_ub;
        int s_loop_ub;
        int scalarLB;
        int vectorUB;
        // 'Kinematics:118' J   = kin_xyzbc_tt_J_tj( r_j( :, j ), this.parameters );
        i_loop_ub = r_j.size(0);
        b_r_j.set_size(r_j.size(0));
        for (int i9{0}; i9 < i_loop_ub; i9++) {
            b_r_j[i9] = r_j[i9 + r_j.size(0) * j];
        }
        kin_xyzbc_tt_J_tj(b_r_j, parameters, J);
        // 'Kinematics:119' JP  = kin_xyzbc_tt_JP_tj( r_j( :, j ), v_j( :, j ), this.parameters );
        j_loop_ub = r_j.size(0);
        b_r_j.set_size(r_j.size(0));
        for (int i10{0}; i10 < j_loop_ub; i10++) {
            b_r_j[i10] = r_j[i10 + r_j.size(0) * j];
        }
        k_loop_ub = v_j.size(0);
        b_v_j.set_size(v_j.size(0));
        for (int i11{0}; i11 < k_loop_ub; i11++) {
            b_v_j[i11] = v_j[i11 + v_j.size(0) * j];
        }
        kin_xyzbc_tt_JP_tj(b_r_j, b_v_j, parameters, JP);
        // 'Kinematics:120' J2P = kin_xyzbc_tt_J2P_tj( r_j( :, j ), v_j( :, j ), a_j( :, j ),
        // this.parameters );
        l_loop_ub = r_j.size(0);
        b_r_j.set_size(r_j.size(0));
        for (int i12{0}; i12 < l_loop_ub; i12++) {
            b_r_j[i12] = r_j[i12 + r_j.size(0) * j];
        }
        m_loop_ub = v_j.size(0);
        b_v_j.set_size(v_j.size(0));
        for (int i13{0}; i13 < m_loop_ub; i13++) {
            b_v_j[i13] = v_j[i13 + v_j.size(0) * j];
        }
        n_loop_ub = a_j.size(0);
        b_a_j.set_size(a_j.size(0));
        for (int i14{0}; i14 < n_loop_ub; i14++) {
            b_a_j[i14] = a_j[i14 + a_j.size(0) * j];
        }
        kin_xyzbc_tt_J2P_tj(b_r_j, b_v_j, b_a_j, parameters, J2P);
        // 'Kinematics:121' r_t( :, j ) = kin_xyzbc_tt_forward( r_j( :, j ), this.parameters );
        o_loop_ub = r_j.size(0);
        b_r_j.set_size(r_j.size(0));
        for (int i15{0}; i15 < o_loop_ub; i15++) {
            b_r_j[i15] = r_j[i15 + r_j.size(0) * j];
        }
        kin_xyzbc_tt_forward(b_r_j, parameters, dv);
        p_loop_ub = r_t.size(0);
        for (int i16{0}; i16 < p_loop_ub; i16++) {
            r_t[i16 + r_t.size(0) * j] = dv[i16];
        }
        // 'Kinematics:122' v_t( :, j ) = J * v_j( :, j );
        for (int i17{0}; i17 < 5; i17++) {
            double d;
            d = 0.0;
            for (int i19{0}; i19 < 5; i19++) {
                d += J[i19][i17] * v_j[i19 + v_j.size(0) * j];
            }
            b_J[i17] = d;
        }
        q_loop_ub = v_t.size(0);
        for (int i18{0}; i18 < q_loop_ub; i18++) {
            v_t[i18 + v_t.size(0) * j] = b_J[i18];
        }
        // 'Kinematics:123' a_t( :, j ) = JP * v_j( :, j )  + J * a_j( :, j );
        for (int i20{0}; i20 < 5; i20++) {
            double d1;
            double d2;
            d1 = 0.0;
            d2 = 0.0;
            for (int i21{0}; i21 < 5; i21++) {
                d1 += JP[i21][i20] * v_j[i21 + v_j.size(0) * j];
                d2 += J[i21][i20] * a_j[i21 + a_j.size(0) * j];
            }
            b_J[i20] = d2;
            b_JP[i20] = d1;
        }
        r_loop_ub = a_t.size(0);
        scalarLB = (a_t.size(0) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (int i22{0}; i22 <= vectorUB; i22 += 2) {
            __m128d r;
            __m128d r1;
            r = _mm_loadu_pd(&b_JP[i22]);
            r1 = _mm_loadu_pd(&b_J[i22]);
            _mm_storeu_pd(&a_t[i22 + a_t.size(0) * j], _mm_add_pd(r, r1));
        }
        for (int i22{scalarLB}; i22 < r_loop_ub; i22++) {
            a_t[i22 + a_t.size(0) * j] = b_JP[i22] + b_J[i22];
        }
        // 'Kinematics:124' j_t( :, j ) = J2P * v_j( :, j ) + 2 * JP * a_j( :, j ) + J * j_j( :, j
        // );
        for (int i23{0}; i23 < 5; i23++) {
            double d3;
            double d4;
            double d5;
            d3 = 0.0;
            d4 = 0.0;
            d5 = 0.0;
            for (int i25{0}; i25 < 5; i25++) {
                d4 += J2P[i25][i23] * v_j[i25 + v_j.size(0) * j];
                d5 += 2.0 * JP[i25][i23] * a_j[i25 + a_j.size(0) * j];
                d3 += J[i25][i23] * j_j[i25 + j_j.size(0) * j];
            }
            b_J2P[i23] = (d4 + d5) + d3;
        }
        s_loop_ub = j_t.size(0);
        for (int i24{0}; i24 < s_loop_ub; i24++) {
            j_t[i24 + j_t.size(0) * j] = b_J2P[i24];
        }
    }
    //              end
}

//
// function [ r_t, v_t, a_t, j_t ] = relative( this, r_j, v_j, a_j, j_j )
//
// Arguments    : const ::coder::array<double, 1U> &r_j
//                const ::coder::array<double, 1U> &v_j
//                const ::coder::array<double, 1U> &a_j
//                const ::coder::array<double, 1U> &j_j
//                ::coder::array<double, 1U> &r_t
//                ::coder::array<double, 1U> &v_t
//                ::coder::array<double, 1U> &a_t
//                ::coder::array<double, 1U> &j_t
// Return Type  : void
//
void Kinematics::relative(const ::coder::array<double, 1U> &r_j,
                          const ::coder::array<double, 1U> &v_j,
                          const ::coder::array<double, 1U> &a_j,
                          const ::coder::array<double, 1U> &j_j, ::coder::array<double, 1U> &r_t,
                          ::coder::array<double, 1U> &v_t, ::coder::array<double, 1U> &a_t,
                          ::coder::array<double, 1U> &j_t) const
{
    ::coder::array<double, 1U> b_a_j;
    ::coder::array<double, 1U> b_r_j;
    ::coder::array<double, 1U> b_v_j;
    double J[5][5];
    double J2P[5][5];
    double JP[5][5];
    double b_J[5];
    double b_J2P[5];
    double b_JP[5];
    double dv[5];
    int b_loop_ub;
    int c_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int f_loop_ub;
    int g_loop_ub;
    int h_loop_ub;
    int i_loop_ub;
    int j_loop_ub;
    int k_loop_ub;
    int l_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int n_loop_ub;
    int o_loop_ub;
    int scalarLB;
    int vectorUB;
    // ----------------------------------------------------------------%
    //  Advanced kinematics
    // ----------------------------------------------------------------%
    //         %% All
    // 'Kinematics:108' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:111' N   = size( r_j, 2 );
    // 'Kinematics:112' r_t = zeros( size( r_j ) );
    r_t.set_size(r_j.size(0));
    loop_ub = r_j.size(0);
    for (int i{0}; i < loop_ub; i++) {
        r_t[i] = 0.0;
    }
    // 'Kinematics:113' v_t = zeros( size( v_j ) );
    v_t.set_size(v_j.size(0));
    b_loop_ub = v_j.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        v_t[i1] = 0.0;
    }
    // 'Kinematics:114' a_t = zeros( size( a_j ) );
    a_t.set_size(a_j.size(0));
    c_loop_ub = a_j.size(0);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        a_t[i2] = 0.0;
    }
    // 'Kinematics:115' j_t = zeros( size( j_j ) );
    j_t.set_size(j_j.size(0));
    d_loop_ub = j_j.size(0);
    for (int i3{0}; i3 < d_loop_ub; i3++) {
        j_t[i3] = 0.0;
    }
    // 'Kinematics:117' for j = 1 : N
    // 'Kinematics:118' J   = kin_xyzbc_tt_J_tj( r_j( :, j ), this.parameters );
    e_loop_ub = r_j.size(0);
    b_r_j.set_size(r_j.size(0));
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        b_r_j[i4] = r_j[i4];
    }
    kin_xyzbc_tt_J_tj(b_r_j, parameters, J);
    // 'Kinematics:119' JP  = kin_xyzbc_tt_JP_tj( r_j( :, j ), v_j( :, j ), this.parameters );
    f_loop_ub = r_j.size(0);
    b_r_j.set_size(r_j.size(0));
    for (int i5{0}; i5 < f_loop_ub; i5++) {
        b_r_j[i5] = r_j[i5];
    }
    g_loop_ub = v_j.size(0);
    b_v_j.set_size(v_j.size(0));
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        b_v_j[i6] = v_j[i6];
    }
    kin_xyzbc_tt_JP_tj(b_r_j, b_v_j, parameters, JP);
    // 'Kinematics:120' J2P = kin_xyzbc_tt_J2P_tj( r_j( :, j ), v_j( :, j ), a_j( :, j ),
    // this.parameters );
    h_loop_ub = r_j.size(0);
    b_r_j.set_size(r_j.size(0));
    for (int i7{0}; i7 < h_loop_ub; i7++) {
        b_r_j[i7] = r_j[i7];
    }
    i_loop_ub = v_j.size(0);
    b_v_j.set_size(v_j.size(0));
    for (int i8{0}; i8 < i_loop_ub; i8++) {
        b_v_j[i8] = v_j[i8];
    }
    j_loop_ub = a_j.size(0);
    b_a_j.set_size(a_j.size(0));
    for (int i9{0}; i9 < j_loop_ub; i9++) {
        b_a_j[i9] = a_j[i9];
    }
    kin_xyzbc_tt_J2P_tj(b_r_j, b_v_j, b_a_j, parameters, J2P);
    // 'Kinematics:121' r_t( :, j ) = kin_xyzbc_tt_forward( r_j( :, j ), this.parameters );
    k_loop_ub = r_j.size(0);
    b_r_j.set_size(r_j.size(0));
    for (int i10{0}; i10 < k_loop_ub; i10++) {
        b_r_j[i10] = r_j[i10];
    }
    kin_xyzbc_tt_forward(b_r_j, parameters, dv);
    l_loop_ub = r_j.size(0);
    for (int i11{0}; i11 < l_loop_ub; i11++) {
        r_t[i11] = dv[i11];
    }
    // 'Kinematics:122' v_t( :, j ) = J * v_j( :, j );
    for (int i12{0}; i12 < 5; i12++) {
        double d;
        d = 0.0;
        for (int i14{0}; i14 < 5; i14++) {
            d += J[i14][i12] * v_j[i14];
        }
        b_J[i12] = d;
    }
    m_loop_ub = v_j.size(0);
    for (int i13{0}; i13 < m_loop_ub; i13++) {
        v_t[i13] = b_J[i13];
    }
    // 'Kinematics:123' a_t( :, j ) = JP * v_j( :, j )  + J * a_j( :, j );
    for (int i15{0}; i15 < 5; i15++) {
        double d1;
        double d2;
        d1 = 0.0;
        d2 = 0.0;
        for (int i16{0}; i16 < 5; i16++) {
            d1 += JP[i16][i15] * v_j[i16];
            d2 += J[i16][i15] * a_j[i16];
        }
        b_J[i15] = d2;
        b_JP[i15] = d1;
    }
    n_loop_ub = a_j.size(0);
    scalarLB = (a_j.size(0) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (int i17{0}; i17 <= vectorUB; i17 += 2) {
        __m128d r;
        __m128d r1;
        r = _mm_loadu_pd(&b_JP[i17]);
        r1 = _mm_loadu_pd(&b_J[i17]);
        _mm_storeu_pd(&a_t[i17], _mm_add_pd(r, r1));
    }
    for (int i17{scalarLB}; i17 < n_loop_ub; i17++) {
        a_t[i17] = b_JP[i17] + b_J[i17];
    }
    // 'Kinematics:124' j_t( :, j ) = J2P * v_j( :, j ) + 2 * JP * a_j( :, j ) + J * j_j( :, j );
    for (int i18{0}; i18 < 5; i18++) {
        double d3;
        double d4;
        double d5;
        d3 = 0.0;
        d4 = 0.0;
        d5 = 0.0;
        for (int i20{0}; i20 < 5; i20++) {
            d4 += J2P[i20][i18] * v_j[i20];
            d5 += 2.0 * JP[i20][i18] * a_j[i20];
            d3 += J[i20][i18] * j_j[i20];
        }
        b_J2P[i18] = (d4 + d5) + d3;
    }
    o_loop_ub = j_j.size(0);
    for (int i19{0}; i19 < o_loop_ub; i19++) {
        j_t[i19] = b_J2P[i19];
    }
    //              end
}

//
// function [ this ] = set_params( this, parameters )
//
// Arguments    : const double parameters_data[]
//                int parameters_size
// Return Type  : void
//
void Kinematics::set_params(const double parameters_data[], int parameters_size)
{
    // 'Kinematics:37' coder.inline( "never" );
    // 'Kinematics:38' this.parameters = parameters( : );
    parameters.set_size(parameters_size);
    for (int i{0}; i < parameters_size; i++) {
        parameters[i] = parameters_data[i];
    }
}

//
// function [ this ] = set_tool_length( this, tool_length )
//
// Arguments    : double tool_length
// Return Type  : void
//
void Kinematics::set_tool_length(double tool_length)
{
    // 'Kinematics:62' coder.inline( "never" );
    // 'Kinematics:63' this.parameters(this.indT(end)) = tool_length;
    parameters[static_cast<int>(indT[2]) - 1] = tool_length;
}

//
// function [ this ] = set_type( this, type )
//
// Arguments    : const char b_type[8]
// Return Type  : void
//
void Kinematics::set_type(const char b_type[8])
{
    // 'Kinematics:42' coder.inline( "never" );
    // 'Kinematics:43' this.type = type;
    for (int i{0}; i < 8; i++) {
        type[i] = b_type[i];
    }
}

//
// function [ v_j ] = v_joint( this, r_t, v_t )
//
// Arguments    : const ::coder::array<double, 2U> &r_t
//                const ::coder::array<double, 2U> &v_t
//                ::coder::array<double, 2U> &v_j
// Return Type  : void
//
void Kinematics::v_joint(const ::coder::array<double, 2U> &r_t,
                         const ::coder::array<double, 2U> &v_t,
                         ::coder::array<double, 2U> &v_j) const
{
    ::coder::array<double, 1U> b_r_t;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // 'Kinematics:166' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:169' N   = size( r_t, 2 );
    // 'Kinematics:170' v_j = zeros( size( v_t ) );
    unnamed_idx_0 = static_cast<unsigned int>(v_t.size(0));
    v_j.set_size(v_t.size(0), v_t.size(1));
    loop_ub = v_t.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            v_j[i2 + v_j.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:172' for j = 1 : N
    i1 = r_t.size(1);
    for (int j{0}; j < i1; j++) {
        double J[5][5];
        double b_J[5];
        int c_loop_ub;
        int d_loop_ub;
        // 'Kinematics:173' J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
        c_loop_ub = r_t.size(0);
        b_r_t.set_size(r_t.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_t[i3] = r_t[i3 + r_t.size(0) * j];
        }
        kin_xyzbc_tt_J_jt(b_r_t, parameters, J);
        // 'Kinematics:174' v_j( :, j ) = J * v_t( :, j );
        for (int i4{0}; i4 < 5; i4++) {
            double d;
            d = 0.0;
            for (int i6{0}; i6 < 5; i6++) {
                d += J[i6][i4] * v_t[i6 + v_t.size(0) * j];
            }
            b_J[i4] = d;
        }
        d_loop_ub = v_j.size(0);
        for (int i5{0}; i5 < d_loop_ub; i5++) {
            v_j[i5 + v_j.size(0) * j] = b_J[i5];
        }
    }
    //              end
}

//
// function [ v_j ] = v_joint( this, r_t, v_t )
//
// Arguments    : const ::coder::array<double, 1U> &r_t
//                const ::coder::array<double, 1U> &v_t
//                ::coder::array<double, 1U> &v_j
// Return Type  : void
//
void Kinematics::v_joint(const ::coder::array<double, 1U> &r_t,
                         const ::coder::array<double, 1U> &v_t,
                         ::coder::array<double, 1U> &v_j) const
{
    ::coder::array<double, 1U> b_r_t;
    double J[5][5];
    double b_J[5];
    int b_loop_ub;
    int c_loop_ub;
    int loop_ub;
    // 'Kinematics:166' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:169' N   = size( r_t, 2 );
    // 'Kinematics:170' v_j = zeros( size( v_t ) );
    v_j.set_size(v_t.size(0));
    loop_ub = v_t.size(0);
    for (int i{0}; i < loop_ub; i++) {
        v_j[i] = 0.0;
    }
    // 'Kinematics:172' for j = 1 : N
    // 'Kinematics:173' J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
    b_loop_ub = r_t.size(0);
    b_r_t.set_size(r_t.size(0));
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        b_r_t[i1] = r_t[i1];
    }
    kin_xyzbc_tt_J_jt(b_r_t, parameters, J);
    // 'Kinematics:174' v_j( :, j ) = J * v_t( :, j );
    for (int i2{0}; i2 < 5; i2++) {
        double d;
        d = 0.0;
        for (int i4{0}; i4 < 5; i4++) {
            d += J[i4][i2] * v_t[i4];
        }
        b_J[i2] = d;
    }
    c_loop_ub = v_t.size(0);
    for (int i3{0}; i3 < c_loop_ub; i3++) {
        v_j[i3] = b_J[i3];
    }
    //              end
}

//
// function [ v_t ] = v_relative( this, r_j, v_j )
//
// Arguments    : const ::coder::array<double, 2U> &r_j
//                const ::coder::array<double, 2U> &v_j
//                ::coder::array<double, 2U> &v_t
// Return Type  : void
//
void Kinematics::v_relative(const ::coder::array<double, 2U> &r_j,
                            const ::coder::array<double, 2U> &v_j,
                            ::coder::array<double, 2U> &v_t) const
{
    ::coder::array<double, 1U> b_r_j;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    //         %% Jacobian
    // 'Kinematics:153' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:156' N   = size( r_j, 2 );
    // 'Kinematics:157' v_t = zeros( size( v_j ) );
    unnamed_idx_0 = static_cast<unsigned int>(v_j.size(0));
    v_t.set_size(v_j.size(0), v_j.size(1));
    loop_ub = v_j.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            v_t[i2 + v_t.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:158' for j = 1 : N
    i1 = r_j.size(1);
    for (int j{0}; j < i1; j++) {
        double J[5][5];
        double b_J[5];
        int c_loop_ub;
        int d_loop_ub;
        // 'Kinematics:159' J   = kin_xyzbc_tt_J_tj( r_j( :, j ), this.parameters );
        c_loop_ub = r_j.size(0);
        b_r_j.set_size(r_j.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_j[i3] = r_j[i3 + r_j.size(0) * j];
        }
        kin_xyzbc_tt_J_tj(b_r_j, parameters, J);
        // 'Kinematics:160' v_t( :, j ) = J * v_j( :, j );
        for (int i4{0}; i4 < 5; i4++) {
            double d;
            d = 0.0;
            for (int i6{0}; i6 < 5; i6++) {
                d += J[i6][i4] * v_j[i6 + v_j.size(0) * j];
            }
            b_J[i4] = d;
        }
        d_loop_ub = v_t.size(0);
        for (int i5{0}; i5 < d_loop_ub; i5++) {
            v_t[i5 + v_t.size(0) * j] = b_J[i5];
        }
    }
    //              end
}

} // namespace ocn

//
// File trailer for Kinematics.cpp
//
// [EOF]
//
