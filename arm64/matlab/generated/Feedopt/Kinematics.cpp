
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
#include "kin_J2P_ar_xyzbc.h"
#include "kin_J2P_ra_xyzbc.h"
#include "kin_JP_ar_xyzbc.h"
#include "kin_JP_ra_xyzbc.h"
#include "kin_J_ar_xyzbc.h"
#include "kin_J_ra_xyzbc.h"
#include "kin_forward_xyzbc.h"
#include "kin_inverse_xyzbc.h"
#include "coder_array.h"

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
// function [ a_a ] = a_joint( this, r_r, v_r, a_r )
//
// Arguments    : const ::coder::array<double, 2U> &r_r
//                const ::coder::array<double, 2U> &v_r
//                const ::coder::array<double, 2U> &a_r
//                ::coder::array<double, 2U> &a_a
// Return Type  : void
//
void Kinematics::a_joint(const ::coder::array<double, 2U> &r_r,
                         const ::coder::array<double, 2U> &v_r,
                         const ::coder::array<double, 2U> &a_r,
                         ::coder::array<double, 2U> &a_a) const
{
    ::coder::array<double, 1U> b_r_r;
    ::coder::array<double, 1U> b_v_r;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // 'Kinematics:167' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:170' N   = size( r_r, 2 );
    // 'Kinematics:171' a_a = zeros( size( a_r ) );
    unnamed_idx_0 = static_cast<unsigned int>(a_r.size(0));
    a_a.set_size(a_r.size(0), a_r.size(1));
    loop_ub = a_r.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            a_a[i2 + a_a.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:173' for j = 1 : N
    i1 = r_r.size(1);
    for (int j{0}; j < i1; j++) {
        double J[5][5];
        double JP[5][5];
        double b_J[5];
        double b_JP[5];
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        // 'Kinematics:174' J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
        c_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_r[i3] = r_r[i3 + r_r.size(0) * j];
        }
        kin_J_ar_xyzbc(b_r_r, parameters, J);
        // 'Kinematics:175' JP  = kin_JP_ar_xyzbc( r_r( :, j ), v_r( :, j ), this.parameters );
        d_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            b_r_r[i4] = r_r[i4 + r_r.size(0) * j];
        }
        e_loop_ub = v_r.size(0);
        b_v_r.set_size(v_r.size(0));
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            b_v_r[i5] = v_r[i5 + v_r.size(0) * j];
        }
        kin_JP_ar_xyzbc(b_r_r, b_v_r, parameters, JP);
        // 'Kinematics:176' a_a( :, j ) = JP * v_r( :, j ) + J * a_r( :, j );
        for (int i6{0}; i6 < 5; i6++) {
            double d;
            double d1;
            d = 0.0;
            d1 = 0.0;
            for (int i8{0}; i8 < 5; i8++) {
                d += JP[i8][i6] * v_r[i8 + v_r.size(0) * j];
                d1 += J[i8][i6] * a_r[i8 + a_r.size(0) * j];
            }
            b_J[i6] = d1;
            b_JP[i6] = d;
        }
        f_loop_ub = a_a.size(0);
        for (int i7{0}; i7 < f_loop_ub; i7++) {
            a_a[i7 + a_a.size(0) * j] = b_JP[i7] + b_J[i7];
        }
    }
    //              end
}

//
// function [ a_r ] = a_relative( this, r_a, v_a, a_a )
//
// Arguments    : const ::coder::array<double, 2U> &r_a
//                const ::coder::array<double, 2U> &v_a
//                const ::coder::array<double, 2U> &a_a
//                ::coder::array<double, 2U> &a_r
// Return Type  : void
//
void Kinematics::a_relative(const ::coder::array<double, 2U> &r_a,
                            const ::coder::array<double, 2U> &v_a,
                            const ::coder::array<double, 2U> &a_a,
                            ::coder::array<double, 2U> &a_r) const
{
    ::coder::array<double, 1U> b_r_a;
    ::coder::array<double, 1U> b_v_a;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    //         %% Jacobian - First derivative
    // 'Kinematics:154' coder.inline( "never" );
    // 'Kinematics:156' N   = size( r_a, 2 );
    // 'Kinematics:157' a_r = zeros( size( a_a ) );
    unnamed_idx_0 = static_cast<unsigned int>(a_a.size(0));
    a_r.set_size(a_a.size(0), a_a.size(1));
    loop_ub = a_a.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            a_r[i2 + a_r.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:159' for j = 1 : N
    i1 = r_a.size(1);
    for (int j{0}; j < i1; j++) {
        double J[5][5];
        double JP[5][5];
        double b_J[5];
        double b_JP[5];
        int c_loop_ub;
        int d_loop_ub;
        int e_loop_ub;
        int f_loop_ub;
        // 'Kinematics:160' J   = kin_J_ra_xyzbc( r_a( :, j ), this.parameters );
        c_loop_ub = r_a.size(0);
        b_r_a.set_size(r_a.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_a[i3] = r_a[i3 + r_a.size(0) * j];
        }
        kin_J_ra_xyzbc(b_r_a, parameters, J);
        // 'Kinematics:161' JP  = kin_JP_ra_xyzbc( r_a( :, j ), v_a( :, j ), this.parameters );
        d_loop_ub = r_a.size(0);
        b_r_a.set_size(r_a.size(0));
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            b_r_a[i4] = r_a[i4 + r_a.size(0) * j];
        }
        e_loop_ub = v_a.size(0);
        b_v_a.set_size(v_a.size(0));
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            b_v_a[i5] = v_a[i5 + v_a.size(0) * j];
        }
        kin_JP_ra_xyzbc(b_r_a, b_v_a,
                        (const double *)((::coder::array<double, 1U> *)&parameters)->data(), JP);
        // 'Kinematics:162' a_r( :, j ) = JP * v_a( :, j ) + J * a_a( :, j );
        for (int i6{0}; i6 < 5; i6++) {
            double d;
            double d1;
            d = 0.0;
            d1 = 0.0;
            for (int i8{0}; i8 < 5; i8++) {
                d += JP[i8][i6] * v_a[i8 + v_a.size(0) * j];
                d1 += J[i8][i6] * a_a[i8 + a_a.size(0) * j];
            }
            b_J[i6] = d1;
            b_JP[i6] = d;
        }
        f_loop_ub = a_r.size(0);
        for (int i7{0}; i7 < f_loop_ub; i7++) {
            a_r[i7 + a_r.size(0) * j] = b_JP[i7] + b_J[i7];
        }
    }
}

//
// function [ this ] = Kinematics( type, parameters )
//
// Arguments    : const char b_type[5]
//                const double parameters_data[]
//                int parameters_size
// Return Type  : void
//
void Kinematics::init(const char b_type[5], const double parameters_data[], int parameters_size)
{
    // ----------------------------------------------------------------%
    //  Kinematics Wrapper class to C interfaces
    // ----------------------------------------------------------------%
    // 'Kinematics:17' coder.inline( "never" );
    // 'Kinematics:18' this.type       = type;
    for (int i{0}; i < 5; i++) {
        type[i] = b_type[i];
    }
    // 'Kinematics:19' this.parameters = parameters( : );
    parameters.set_size(parameters_size);
    for (int i1{0}; i1 < parameters_size; i1++) {
        parameters[i1] = parameters_data[i1];
    }
    // 'Kinematics:20' [ this ] = set_function_ptr( this );
    //  Not implemented due to problem of support in code
    //  generation...
    // ----------------------------------------------------------------%
    //  Support for different kinematics only for matlab flow
    // ----------------------------------------------------------------%
}

//
// function [ j_a ] = j_joint( this, r_r, v_r, a_r, j_r )
//
// Arguments    : const ::coder::array<double, 2U> &r_r
//                const ::coder::array<double, 2U> &v_r
//                const ::coder::array<double, 2U> &a_r
//                const ::coder::array<double, 2U> &j_r
//                ::coder::array<double, 2U> &j_a
// Return Type  : void
//
void Kinematics::j_joint(const ::coder::array<double, 2U> &r_r,
                         const ::coder::array<double, 2U> &v_r,
                         const ::coder::array<double, 2U> &a_r,
                         const ::coder::array<double, 2U> &j_r,
                         ::coder::array<double, 2U> &j_a) const
{
    ::coder::array<double, 1U> b_a_r;
    ::coder::array<double, 1U> b_r_r;
    ::coder::array<double, 1U> b_v_r;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // 'Kinematics:199' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:202' N   = size( r_r, 2 );
    // 'Kinematics:203' j_a = zeros( size( j_r ) );
    unnamed_idx_0 = static_cast<unsigned int>(j_r.size(0));
    j_a.set_size(j_r.size(0), j_r.size(1));
    loop_ub = j_r.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            j_a[i2 + j_a.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:205' for j = 1 : N
    i1 = r_r.size(1);
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
        // 'Kinematics:206' J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
        c_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_r[i3] = r_r[i3 + r_r.size(0) * j];
        }
        kin_J_ar_xyzbc(b_r_r, parameters, J);
        // 'Kinematics:207' JP  = kin_JP_ar_xyzbc( r_r( :, j ), v_r( :, j ), this.parameters );
        d_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            b_r_r[i4] = r_r[i4 + r_r.size(0) * j];
        }
        e_loop_ub = v_r.size(0);
        b_v_r.set_size(v_r.size(0));
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            b_v_r[i5] = v_r[i5 + v_r.size(0) * j];
        }
        kin_JP_ar_xyzbc(b_r_r, b_v_r, parameters, JP);
        // 'Kinematics:208' J2P = kin_J2P_ar_xyzbc( r_r( :, j ), v_r( :, j ), a_r( :, j ),
        // this.parameters );
        f_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i6{0}; i6 < f_loop_ub; i6++) {
            b_r_r[i6] = r_r[i6 + r_r.size(0) * j];
        }
        g_loop_ub = v_r.size(0);
        b_v_r.set_size(v_r.size(0));
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            b_v_r[i7] = v_r[i7 + v_r.size(0) * j];
        }
        h_loop_ub = a_r.size(0);
        b_a_r.set_size(a_r.size(0));
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            b_a_r[i8] = a_r[i8 + a_r.size(0) * j];
        }
        kin_J2P_ar_xyzbc(b_r_r, b_v_r, b_a_r, parameters, J2P);
        // 'Kinematics:209' j_a( :, j ) = J2P * v_r( :, j ) + 2 * JP * a_r( :, j ) + J * j_r( :, j
        // );
        for (int i9{0}; i9 < 5; i9++) {
            double d;
            double d1;
            double d2;
            d = 0.0;
            d1 = 0.0;
            d2 = 0.0;
            for (int i11{0}; i11 < 5; i11++) {
                d1 += J2P[i11][i9] * v_r[i11 + v_r.size(0) * j];
                d2 += 2.0 * JP[i11][i9] * a_r[i11 + a_r.size(0) * j];
                d += J[i11][i9] * j_r[i11 + j_r.size(0) * j];
            }
            b_J2P[i9] = (d1 + d2) + d;
        }
        i_loop_ub = j_a.size(0);
        for (int i10{0}; i10 < i_loop_ub; i10++) {
            j_a[i10 + j_a.size(0) * j] = b_J2P[i10];
        }
    }
    //              end
}

//
// function [ j_r ] = j_relative( this, r_a, v_a, a_a, j_a )
//
// Arguments    : const ::coder::array<double, 2U> &r_a
//                const ::coder::array<double, 2U> &v_a
//                const ::coder::array<double, 2U> &a_a
//                const ::coder::array<double, 2U> &j_a
//                ::coder::array<double, 2U> &j_r
// Return Type  : void
//
void Kinematics::j_relative(const ::coder::array<double, 2U> &r_a,
                            const ::coder::array<double, 2U> &v_a,
                            const ::coder::array<double, 2U> &a_a,
                            const ::coder::array<double, 2U> &j_a,
                            ::coder::array<double, 2U> &j_r) const
{
    ::coder::array<double, 1U> b_a_a;
    ::coder::array<double, 1U> b_r_a;
    ::coder::array<double, 1U> b_v_a;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    //         %% Jacobian - Second derivative
    // 'Kinematics:183' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:186' N   = size( r_a, 2 );
    // 'Kinematics:187' j_r = zeros( size( j_a ) );
    unnamed_idx_0 = static_cast<unsigned int>(j_a.size(0));
    j_r.set_size(j_a.size(0), j_a.size(1));
    loop_ub = j_a.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            j_r[i2 + j_r.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:189' for j = 1 : N
    i1 = r_a.size(1);
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
        // 'Kinematics:190' J   = kin_J_ra_xyzbc( r_a( :, j ), this.parameters );
        c_loop_ub = r_a.size(0);
        b_r_a.set_size(r_a.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_a[i3] = r_a[i3 + r_a.size(0) * j];
        }
        kin_J_ra_xyzbc(b_r_a, parameters, J);
        // 'Kinematics:191' JP  = kin_JP_ra_xyzbc( r_a( :, j ), v_a( :, j ), this.parameters );
        d_loop_ub = r_a.size(0);
        b_r_a.set_size(r_a.size(0));
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            b_r_a[i4] = r_a[i4 + r_a.size(0) * j];
        }
        e_loop_ub = v_a.size(0);
        b_v_a.set_size(v_a.size(0));
        for (int i5{0}; i5 < e_loop_ub; i5++) {
            b_v_a[i5] = v_a[i5 + v_a.size(0) * j];
        }
        kin_JP_ra_xyzbc(b_r_a, b_v_a,
                        (const double *)((::coder::array<double, 1U> *)&parameters)->data(), JP);
        // 'Kinematics:192' J2P = kin_J2P_ra_xyzbc( r_a( :, j ), v_a( :, j ), a_a( :, j ),
        // this.parameters );
        f_loop_ub = r_a.size(0);
        b_r_a.set_size(r_a.size(0));
        for (int i6{0}; i6 < f_loop_ub; i6++) {
            b_r_a[i6] = r_a[i6 + r_a.size(0) * j];
        }
        g_loop_ub = v_a.size(0);
        b_v_a.set_size(v_a.size(0));
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            b_v_a[i7] = v_a[i7 + v_a.size(0) * j];
        }
        h_loop_ub = a_a.size(0);
        b_a_a.set_size(a_a.size(0));
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            b_a_a[i8] = a_a[i8 + a_a.size(0) * j];
        }
        kin_J2P_ra_xyzbc(b_r_a, b_v_a, b_a_a,
                         (const double *)((::coder::array<double, 1U> *)&parameters)->data(), J2P);
        // 'Kinematics:193' j_r( :, j ) = J2P * v_a( :, j ) + 2 * JP * a_a( :, j ) + J * j_a( :, j
        // );
        for (int i9{0}; i9 < 5; i9++) {
            double d;
            double d1;
            double d2;
            d = 0.0;
            d1 = 0.0;
            d2 = 0.0;
            for (int i11{0}; i11 < 5; i11++) {
                d1 += J2P[i11][i9] * v_a[i11 + v_a.size(0) * j];
                d2 += 2.0 * JP[i11][i9] * a_a[i11 + a_a.size(0) * j];
                d += J[i11][i9] * j_a[i11 + j_a.size(0) * j];
            }
            b_J2P[i9] = (d1 + d2) + d;
        }
        i_loop_ub = j_r.size(0);
        for (int i10{0}; i10 < i_loop_ub; i10++) {
            j_r[i10 + j_r.size(0) * j] = b_J2P[i10];
        }
    }
    //              end
}

//
// function [ r_a, v_a, a_a, j_a ] = joint( this, r_r, v_r, a_r, j_r )
//
// Arguments    : const ::coder::array<double, 2U> &r_r
//                const ::coder::array<double, 2U> &v_r
//                const ::coder::array<double, 2U> &a_r
//                ::coder::array<double, 2U> &r_a
//                ::coder::array<double, 2U> &v_a
//                ::coder::array<double, 2U> &a_a
// Return Type  : void
//
void Kinematics::joint(const ::coder::array<double, 2U> &r_r, const ::coder::array<double, 2U> &v_r,
                       const ::coder::array<double, 2U> &a_r, ::coder::array<double, 2U> &r_a,
                       ::coder::array<double, 2U> &v_a, ::coder::array<double, 2U> &a_a) const
{
    ::coder::array<double, 1U> b_r_r;
    ::coder::array<double, 1U> b_v_r;
    int c_loop_ub;
    int e_loop_ub;
    int i6;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // 'Kinematics:103' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:106' N   = size( r_r, 2 );
    // 'Kinematics:107' r_a = zeros( size( r_r ) );
    unnamed_idx_0 = static_cast<unsigned int>(r_r.size(0));
    r_a.set_size(r_r.size(0), r_r.size(1));
    loop_ub = r_r.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            r_a[i1 + r_a.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:108' v_a = zeros( size( v_r ) );
    unnamed_idx_0 = static_cast<unsigned int>(v_r.size(0));
    v_a.set_size(v_r.size(0), v_r.size(1));
    c_loop_ub = v_r.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            v_a[i3 + v_a.size(0) * i2] = 0.0;
        }
    }
    // 'Kinematics:109' a_a = zeros( size( a_r ) );
    unnamed_idx_0 = static_cast<unsigned int>(a_r.size(0));
    a_a.set_size(a_r.size(0), a_r.size(1));
    e_loop_ub = a_r.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        int f_loop_ub;
        f_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            a_a[i5 + a_a.size(0) * i4] = 0.0;
        }
    }
    // 'Kinematics:110' j_a = zeros( size( j_r ) );
    // 'Kinematics:112' for j = 1 : N
    i6 = r_r.size(1);
    for (int j{0}; j < i6; j++) {
        double J[5][5];
        double JP[5][5];
        double b_J[5];
        double b_JP[5];
        double dv[5];
        int g_loop_ub;
        int h_loop_ub;
        int i_loop_ub;
        int j_loop_ub;
        int k_loop_ub;
        int l_loop_ub;
        int m_loop_ub;
        // 'Kinematics:113' J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
        g_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i7{0}; i7 < g_loop_ub; i7++) {
            b_r_r[i7] = r_r[i7 + r_r.size(0) * j];
        }
        kin_J_ar_xyzbc(b_r_r, parameters, J);
        // 'Kinematics:114' JP  = kin_JP_ar_xyzbc( r_r( :, j ), v_r( :, j ), this.parameters );
        h_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            b_r_r[i8] = r_r[i8 + r_r.size(0) * j];
        }
        i_loop_ub = v_r.size(0);
        b_v_r.set_size(v_r.size(0));
        for (int i9{0}; i9 < i_loop_ub; i9++) {
            b_v_r[i9] = v_r[i9 + v_r.size(0) * j];
        }
        kin_JP_ar_xyzbc(b_r_r, b_v_r, parameters, JP);
        // 'Kinematics:115' J2P = kin_J2P_ar_xyzbc( r_r( :, j ), v_r( :, j ), a_r( :, j ),
        // this.parameters ); 'Kinematics:116' r_a( :, j ) = kin_inverse_xyzbc( r_r( :, j ),
        // this.parameters );
        j_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i10{0}; i10 < j_loop_ub; i10++) {
            b_r_r[i10] = r_r[i10 + r_r.size(0) * j];
        }
        kin_inverse_xyzbc(b_r_r, parameters, dv);
        k_loop_ub = r_a.size(0);
        for (int i11{0}; i11 < k_loop_ub; i11++) {
            r_a[i11 + r_a.size(0) * j] = dv[i11];
        }
        // 'Kinematics:117' v_a( :, j ) = J * v_r( :, j );
        for (int i12{0}; i12 < 5; i12++) {
            double d;
            d = 0.0;
            for (int i14{0}; i14 < 5; i14++) {
                d += J[i14][i12] * v_r[i14 + v_r.size(0) * j];
            }
            b_J[i12] = d;
        }
        l_loop_ub = v_a.size(0);
        for (int i13{0}; i13 < l_loop_ub; i13++) {
            v_a[i13 + v_a.size(0) * j] = b_J[i13];
        }
        // 'Kinematics:118' a_a( :, j ) = JP * v_r( :, j ) + J * a_r( :, j );
        for (int i15{0}; i15 < 5; i15++) {
            double d1;
            double d2;
            d1 = 0.0;
            d2 = 0.0;
            for (int i17{0}; i17 < 5; i17++) {
                d1 += JP[i17][i15] * v_r[i17 + v_r.size(0) * j];
                d2 += J[i17][i15] * a_r[i17 + a_r.size(0) * j];
            }
            b_J[i15] = d2;
            b_JP[i15] = d1;
        }
        m_loop_ub = a_a.size(0);
        for (int i16{0}; i16 < m_loop_ub; i16++) {
            a_a[i16 + a_a.size(0) * j] = b_JP[i16] + b_J[i16];
        }
        // 'Kinematics:119' j_a( :, j ) = J2P * v_r( :, j ) + 2 * JP * a_r( :, j ) + J * j_r( :, j
        // );
    }
    //              end
}

//
// function [ r_a, v_a, a_a, j_a ] = joint( this, r_r, v_r, a_r, j_r )
//
// Arguments    : const ::coder::array<double, 2U> &r_r
//                const ::coder::array<double, 2U> &v_r
//                const ::coder::array<double, 2U> &a_r
//                const ::coder::array<double, 2U> &j_r
//                ::coder::array<double, 2U> &r_a
//                ::coder::array<double, 2U> &v_a
//                ::coder::array<double, 2U> &a_a
//                ::coder::array<double, 2U> &j_a
// Return Type  : void
//
void Kinematics::joint(const ::coder::array<double, 2U> &r_r, const ::coder::array<double, 2U> &v_r,
                       const ::coder::array<double, 2U> &a_r, const ::coder::array<double, 2U> &j_r,
                       ::coder::array<double, 2U> &r_a, ::coder::array<double, 2U> &v_a,
                       ::coder::array<double, 2U> &a_a, ::coder::array<double, 2U> &j_a) const
{
    ::coder::array<double, 1U> b_a_r;
    ::coder::array<double, 1U> b_r_r;
    ::coder::array<double, 1U> b_v_r;
    int c_loop_ub;
    int e_loop_ub;
    int g_loop_ub;
    int i7;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // 'Kinematics:103' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:106' N   = size( r_r, 2 );
    // 'Kinematics:107' r_a = zeros( size( r_r ) );
    unnamed_idx_0 = static_cast<unsigned int>(r_r.size(0));
    r_a.set_size(r_r.size(0), r_r.size(1));
    loop_ub = r_r.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            r_a[i1 + r_a.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:108' v_a = zeros( size( v_r ) );
    unnamed_idx_0 = static_cast<unsigned int>(v_r.size(0));
    v_a.set_size(v_r.size(0), v_r.size(1));
    c_loop_ub = v_r.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            v_a[i3 + v_a.size(0) * i2] = 0.0;
        }
    }
    // 'Kinematics:109' a_a = zeros( size( a_r ) );
    unnamed_idx_0 = static_cast<unsigned int>(a_r.size(0));
    a_a.set_size(a_r.size(0), a_r.size(1));
    e_loop_ub = a_r.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        int f_loop_ub;
        f_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            a_a[i5 + a_a.size(0) * i4] = 0.0;
        }
    }
    // 'Kinematics:110' j_a = zeros( size( j_r ) );
    unnamed_idx_0 = static_cast<unsigned int>(j_r.size(0));
    j_a.set_size(j_r.size(0), j_r.size(1));
    g_loop_ub = j_r.size(1);
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        int h_loop_ub;
        h_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            j_a[i8 + j_a.size(0) * i6] = 0.0;
        }
    }
    // 'Kinematics:112' for j = 1 : N
    i7 = r_r.size(1);
    for (int j{0}; j < i7; j++) {
        double J[5][5];
        double J2P[5][5];
        double JP[5][5];
        double b_J[5];
        double b_J2P[5];
        double b_JP[5];
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
        // 'Kinematics:113' J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
        i_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i9{0}; i9 < i_loop_ub; i9++) {
            b_r_r[i9] = r_r[i9 + r_r.size(0) * j];
        }
        kin_J_ar_xyzbc(b_r_r, parameters, J);
        // 'Kinematics:114' JP  = kin_JP_ar_xyzbc( r_r( :, j ), v_r( :, j ), this.parameters );
        j_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i10{0}; i10 < j_loop_ub; i10++) {
            b_r_r[i10] = r_r[i10 + r_r.size(0) * j];
        }
        k_loop_ub = v_r.size(0);
        b_v_r.set_size(v_r.size(0));
        for (int i11{0}; i11 < k_loop_ub; i11++) {
            b_v_r[i11] = v_r[i11 + v_r.size(0) * j];
        }
        kin_JP_ar_xyzbc(b_r_r, b_v_r, parameters, JP);
        // 'Kinematics:115' J2P = kin_J2P_ar_xyzbc( r_r( :, j ), v_r( :, j ), a_r( :, j ),
        // this.parameters );
        l_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i12{0}; i12 < l_loop_ub; i12++) {
            b_r_r[i12] = r_r[i12 + r_r.size(0) * j];
        }
        m_loop_ub = v_r.size(0);
        b_v_r.set_size(v_r.size(0));
        for (int i13{0}; i13 < m_loop_ub; i13++) {
            b_v_r[i13] = v_r[i13 + v_r.size(0) * j];
        }
        n_loop_ub = a_r.size(0);
        b_a_r.set_size(a_r.size(0));
        for (int i14{0}; i14 < n_loop_ub; i14++) {
            b_a_r[i14] = a_r[i14 + a_r.size(0) * j];
        }
        kin_J2P_ar_xyzbc(b_r_r, b_v_r, b_a_r, parameters, J2P);
        // 'Kinematics:116' r_a( :, j ) = kin_inverse_xyzbc( r_r( :, j ), this.parameters );
        o_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i15{0}; i15 < o_loop_ub; i15++) {
            b_r_r[i15] = r_r[i15 + r_r.size(0) * j];
        }
        kin_inverse_xyzbc(b_r_r, parameters, dv);
        p_loop_ub = r_a.size(0);
        for (int i16{0}; i16 < p_loop_ub; i16++) {
            r_a[i16 + r_a.size(0) * j] = dv[i16];
        }
        // 'Kinematics:117' v_a( :, j ) = J * v_r( :, j );
        for (int i17{0}; i17 < 5; i17++) {
            double d;
            d = 0.0;
            for (int i19{0}; i19 < 5; i19++) {
                d += J[i19][i17] * v_r[i19 + v_r.size(0) * j];
            }
            b_J[i17] = d;
        }
        q_loop_ub = v_a.size(0);
        for (int i18{0}; i18 < q_loop_ub; i18++) {
            v_a[i18 + v_a.size(0) * j] = b_J[i18];
        }
        // 'Kinematics:118' a_a( :, j ) = JP * v_r( :, j ) + J * a_r( :, j );
        for (int i20{0}; i20 < 5; i20++) {
            double d1;
            double d2;
            d1 = 0.0;
            d2 = 0.0;
            for (int i22{0}; i22 < 5; i22++) {
                d1 += JP[i22][i20] * v_r[i22 + v_r.size(0) * j];
                d2 += J[i22][i20] * a_r[i22 + a_r.size(0) * j];
            }
            b_J[i20] = d2;
            b_JP[i20] = d1;
        }
        r_loop_ub = a_a.size(0);
        for (int i21{0}; i21 < r_loop_ub; i21++) {
            a_a[i21 + a_a.size(0) * j] = b_JP[i21] + b_J[i21];
        }
        // 'Kinematics:119' j_a( :, j ) = J2P * v_r( :, j ) + 2 * JP * a_r( :, j ) + J * j_r( :, j
        // );
        for (int i23{0}; i23 < 5; i23++) {
            double d3;
            double d4;
            double d5;
            d3 = 0.0;
            d4 = 0.0;
            d5 = 0.0;
            for (int i25{0}; i25 < 5; i25++) {
                d4 += J2P[i25][i23] * v_r[i25 + v_r.size(0) * j];
                d5 += 2.0 * JP[i25][i23] * a_r[i25 + a_r.size(0) * j];
                d3 += J[i25][i23] * j_r[i25 + j_r.size(0) * j];
            }
            b_J2P[i23] = (d4 + d5) + d3;
        }
        s_loop_ub = j_a.size(0);
        for (int i24{0}; i24 < s_loop_ub; i24++) {
            j_a[i24 + j_a.size(0) * j] = b_J2P[i24];
        }
    }
    //              end
}

//
// function [ r_a ] = r_joint( this, r_r )
//
// Arguments    : const ::coder::array<double, 2U> &r_r
//                ::coder::array<double, 2U> &r_a
// Return Type  : void
//
void Kinematics::r_joint(const ::coder::array<double, 2U> &r_r,
                         ::coder::array<double, 2U> &r_a) const
{
    ::coder::array<double, 1U> b_r_r;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // 'Kinematics:65' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:68' N   = size( r_r, 2 );
    // 'Kinematics:69' r_a = zeros( size( r_r ) );
    unnamed_idx_0 = static_cast<unsigned int>(r_r.size(0));
    r_a.set_size(r_r.size(0), r_r.size(1));
    loop_ub = r_r.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            r_a[i2 + r_a.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:70' for j = 1 : N
    i1 = r_r.size(1);
    for (int j{0}; j < i1; j++) {
        double dv[5];
        int c_loop_ub;
        int d_loop_ub;
        // 'Kinematics:71' r_a( :, j ) = kin_inverse_xyzbc( r_r( : , j ), this.parameters );
        c_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_r[i3] = r_r[i3 + r_r.size(0) * j];
        }
        kin_inverse_xyzbc(b_r_r, parameters, dv);
        d_loop_ub = r_a.size(0);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            r_a[i4 + r_a.size(0) * j] = dv[i4];
        }
    }
    //              end
}

//
// function [ r_r ] = r_relative( this, r_a )
//
// Arguments    : const ::coder::array<double, 2U> &r_a
//                ::coder::array<double, 2U> &r_r
// Return Type  : void
//
void Kinematics::r_relative(const ::coder::array<double, 2U> &r_a,
                            ::coder::array<double, 2U> &r_r) const
{
    ::coder::array<double, 1U> b_r_a;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // ----------------------------------------------------------------%
    //  Basic kinematics
    // ----------------------------------------------------------------%
    // 'Kinematics:53' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:56' N   = size( r_a, 2 );
    // 'Kinematics:57' r_r = zeros( size( r_a ) );
    unnamed_idx_0 = static_cast<unsigned int>(r_a.size(0));
    r_r.set_size(r_a.size(0), r_a.size(1));
    loop_ub = r_a.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            r_r[i2 + r_r.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:58' for j = 1 : N
    i1 = r_a.size(1);
    for (int j{0}; j < i1; j++) {
        double dv[5];
        int c_loop_ub;
        int d_loop_ub;
        // 'Kinematics:59' r_r( :, j ) = kin_forward_xyzbc( r_a( : , j ), this.parameters );
        c_loop_ub = r_a.size(0);
        b_r_a.set_size(r_a.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_a[i3] = r_a[i3 + r_a.size(0) * j];
        }
        kin_forward_xyzbc(b_r_a,
                          (const double *)((::coder::array<double, 1U> *)&parameters)->data(), dv);
        d_loop_ub = r_r.size(0);
        for (int i4{0}; i4 < d_loop_ub; i4++) {
            r_r[i4 + r_r.size(0) * j] = dv[i4];
        }
    }
    //              end
}

//
// function [ r_r, v_r, a_r, j_r ] = relative( this, r_a, v_a, a_a, j_a )
//
// Arguments    : const ::coder::array<double, 2U> &r_a
//                const ::coder::array<double, 2U> &v_a
//                const ::coder::array<double, 2U> &a_a
//                const ::coder::array<double, 2U> &j_a
//                ::coder::array<double, 2U> &r_r
//                ::coder::array<double, 2U> &v_r
//                ::coder::array<double, 2U> &a_r
//                ::coder::array<double, 2U> &j_r
// Return Type  : void
//
void Kinematics::relative(const ::coder::array<double, 2U> &r_a,
                          const ::coder::array<double, 2U> &v_a,
                          const ::coder::array<double, 2U> &a_a,
                          const ::coder::array<double, 2U> &j_a, ::coder::array<double, 2U> &r_r,
                          ::coder::array<double, 2U> &v_r, ::coder::array<double, 2U> &a_r,
                          ::coder::array<double, 2U> &j_r) const
{
    ::coder::array<double, 1U> b_a_a;
    ::coder::array<double, 1U> b_r_a;
    ::coder::array<double, 1U> b_v_a;
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
    // 'Kinematics:81' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:84' N   = size( r_a, 2 );
    // 'Kinematics:85' r_r = zeros( size( r_a ) );
    unnamed_idx_0 = static_cast<unsigned int>(r_a.size(0));
    r_r.set_size(r_a.size(0), r_a.size(1));
    loop_ub = r_a.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            r_r[i1 + r_r.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:86' v_r = zeros( size( v_a ) );
    unnamed_idx_0 = static_cast<unsigned int>(v_a.size(0));
    v_r.set_size(v_a.size(0), v_a.size(1));
    c_loop_ub = v_a.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            v_r[i3 + v_r.size(0) * i2] = 0.0;
        }
    }
    // 'Kinematics:87' a_r = zeros( size( a_a ) );
    unnamed_idx_0 = static_cast<unsigned int>(a_a.size(0));
    a_r.set_size(a_a.size(0), a_a.size(1));
    e_loop_ub = a_a.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        int f_loop_ub;
        f_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            a_r[i5 + a_r.size(0) * i4] = 0.0;
        }
    }
    // 'Kinematics:88' j_r = zeros( size( j_a ) );
    unnamed_idx_0 = static_cast<unsigned int>(j_a.size(0));
    j_r.set_size(j_a.size(0), j_a.size(1));
    g_loop_ub = j_a.size(1);
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        int h_loop_ub;
        h_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i8{0}; i8 < h_loop_ub; i8++) {
            j_r[i8 + j_r.size(0) * i6] = 0.0;
        }
    }
    // 'Kinematics:90' for j = 1 : N
    i7 = r_a.size(1);
    for (int j{0}; j < i7; j++) {
        double J[5][5];
        double J2P[5][5];
        double JP[5][5];
        double b_J[5];
        double b_J2P[5];
        double b_JP[5];
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
        // 'Kinematics:91' J   = kin_J_ra_xyzbc( r_a( :, j ), this.parameters );
        i_loop_ub = r_a.size(0);
        b_r_a.set_size(r_a.size(0));
        for (int i9{0}; i9 < i_loop_ub; i9++) {
            b_r_a[i9] = r_a[i9 + r_a.size(0) * j];
        }
        kin_J_ra_xyzbc(b_r_a, parameters, J);
        // 'Kinematics:92' JP  = kin_JP_ra_xyzbc( r_a( :, j ), v_a( :, j ), this.parameters );
        j_loop_ub = r_a.size(0);
        b_r_a.set_size(r_a.size(0));
        for (int i10{0}; i10 < j_loop_ub; i10++) {
            b_r_a[i10] = r_a[i10 + r_a.size(0) * j];
        }
        k_loop_ub = v_a.size(0);
        b_v_a.set_size(v_a.size(0));
        for (int i11{0}; i11 < k_loop_ub; i11++) {
            b_v_a[i11] = v_a[i11 + v_a.size(0) * j];
        }
        kin_JP_ra_xyzbc(b_r_a, b_v_a,
                        (const double *)((::coder::array<double, 1U> *)&parameters)->data(), JP);
        // 'Kinematics:93' J2P = kin_J2P_ra_xyzbc( r_a( :, j ), v_a( :, j ), a_a( :, j ),
        // this.parameters );
        l_loop_ub = r_a.size(0);
        b_r_a.set_size(r_a.size(0));
        for (int i12{0}; i12 < l_loop_ub; i12++) {
            b_r_a[i12] = r_a[i12 + r_a.size(0) * j];
        }
        m_loop_ub = v_a.size(0);
        b_v_a.set_size(v_a.size(0));
        for (int i13{0}; i13 < m_loop_ub; i13++) {
            b_v_a[i13] = v_a[i13 + v_a.size(0) * j];
        }
        n_loop_ub = a_a.size(0);
        b_a_a.set_size(a_a.size(0));
        for (int i14{0}; i14 < n_loop_ub; i14++) {
            b_a_a[i14] = a_a[i14 + a_a.size(0) * j];
        }
        kin_J2P_ra_xyzbc(b_r_a, b_v_a, b_a_a,
                         (const double *)((::coder::array<double, 1U> *)&parameters)->data(), J2P);
        // 'Kinematics:94' r_r( :, j ) = kin_forward_xyzbc( r_a( :, j ), this.parameters );
        o_loop_ub = r_a.size(0);
        b_r_a.set_size(r_a.size(0));
        for (int i15{0}; i15 < o_loop_ub; i15++) {
            b_r_a[i15] = r_a[i15 + r_a.size(0) * j];
        }
        kin_forward_xyzbc(b_r_a,
                          (const double *)((::coder::array<double, 1U> *)&parameters)->data(), dv);
        p_loop_ub = r_r.size(0);
        for (int i16{0}; i16 < p_loop_ub; i16++) {
            r_r[i16 + r_r.size(0) * j] = dv[i16];
        }
        // 'Kinematics:95' v_r( :, j ) = J * v_a( :, j );
        for (int i17{0}; i17 < 5; i17++) {
            double d;
            d = 0.0;
            for (int i19{0}; i19 < 5; i19++) {
                d += J[i19][i17] * v_a[i19 + v_a.size(0) * j];
            }
            b_J[i17] = d;
        }
        q_loop_ub = v_r.size(0);
        for (int i18{0}; i18 < q_loop_ub; i18++) {
            v_r[i18 + v_r.size(0) * j] = b_J[i18];
        }
        // 'Kinematics:96' a_r( :, j ) = JP * v_a( :, j )  + J * a_a( :, j );
        for (int i20{0}; i20 < 5; i20++) {
            double d1;
            double d2;
            d1 = 0.0;
            d2 = 0.0;
            for (int i22{0}; i22 < 5; i22++) {
                d1 += JP[i22][i20] * v_a[i22 + v_a.size(0) * j];
                d2 += J[i22][i20] * a_a[i22 + a_a.size(0) * j];
            }
            b_J[i20] = d2;
            b_JP[i20] = d1;
        }
        r_loop_ub = a_r.size(0);
        for (int i21{0}; i21 < r_loop_ub; i21++) {
            a_r[i21 + a_r.size(0) * j] = b_JP[i21] + b_J[i21];
        }
        // 'Kinematics:97' j_r( :, j ) = J2P * v_a( :, j ) + 2 * JP * a_a( :, j ) + J * j_a( :, j );
        for (int i23{0}; i23 < 5; i23++) {
            double d3;
            double d4;
            double d5;
            d3 = 0.0;
            d4 = 0.0;
            d5 = 0.0;
            for (int i25{0}; i25 < 5; i25++) {
                d4 += J2P[i25][i23] * v_a[i25 + v_a.size(0) * j];
                d5 += 2.0 * JP[i25][i23] * a_a[i25 + a_a.size(0) * j];
                d3 += J[i25][i23] * j_a[i25 + j_a.size(0) * j];
            }
            b_J2P[i23] = (d4 + d5) + d3;
        }
        s_loop_ub = j_r.size(0);
        for (int i24{0}; i24 < s_loop_ub; i24++) {
            j_r[i24 + j_r.size(0) * j] = b_J2P[i24];
        }
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
    // 'Kinematics:24' coder.inline( "never" );
    // 'Kinematics:25' this.parameters = parameters( : );
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
    // 'Kinematics:34' coder.inline( "never" );
    // 'Kinematics:35' this.parameters(end)    = tool_length;
    parameters[parameters.size(0) - 1] = tool_length;
    // 'Kinematics:36' this.parameters(9)      = tool_length;
    parameters[8] = tool_length;
}

//
// function [ this ] = set_type( this, type )
//
// Arguments    : const char b_type[5]
// Return Type  : void
//
void Kinematics::set_type(const char b_type[5])
{
    // 'Kinematics:29' coder.inline( "never" );
    // 'Kinematics:30' this.type = type;
    for (int i{0}; i < 5; i++) {
        type[i] = b_type[i];
    }
}

//
// function [ v_a ] = v_joint( this, r_r, v_r )
//
// Arguments    : const ::coder::array<double, 2U> &r_r
//                const ::coder::array<double, 2U> &v_r
//                ::coder::array<double, 2U> &v_a
// Return Type  : void
//
void Kinematics::v_joint(const ::coder::array<double, 2U> &r_r,
                         const ::coder::array<double, 2U> &v_r,
                         ::coder::array<double, 2U> &v_a) const
{
    ::coder::array<double, 1U> b_r_r;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    // 'Kinematics:139' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:142' N   = size( r_r, 2 );
    // 'Kinematics:143' v_a = zeros( size( v_r ) );
    unnamed_idx_0 = static_cast<unsigned int>(v_r.size(0));
    v_a.set_size(v_r.size(0), v_r.size(1));
    loop_ub = v_r.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            v_a[i2 + v_a.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:145' for j = 1 : N
    i1 = r_r.size(1);
    for (int j{0}; j < i1; j++) {
        double J[5][5];
        double b_J[5];
        int c_loop_ub;
        int d_loop_ub;
        // 'Kinematics:146' J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
        c_loop_ub = r_r.size(0);
        b_r_r.set_size(r_r.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_r[i3] = r_r[i3 + r_r.size(0) * j];
        }
        kin_J_ar_xyzbc(b_r_r, parameters, J);
        // 'Kinematics:147' v_a( :, j ) = J * v_r( :, j );
        for (int i4{0}; i4 < 5; i4++) {
            double d;
            d = 0.0;
            for (int i6{0}; i6 < 5; i6++) {
                d += J[i6][i4] * v_r[i6 + v_r.size(0) * j];
            }
            b_J[i4] = d;
        }
        d_loop_ub = v_a.size(0);
        for (int i5{0}; i5 < d_loop_ub; i5++) {
            v_a[i5 + v_a.size(0) * j] = b_J[i5];
        }
    }
    //              end
}

//
// function [ v_a ] = v_joint( this, r_r, v_r )
//
// Arguments    : const ::coder::array<double, 1U> &r_r
//                const ::coder::array<double, 1U> &v_r
//                ::coder::array<double, 1U> &v_a
// Return Type  : void
//
void Kinematics::v_joint(const ::coder::array<double, 1U> &r_r,
                         const ::coder::array<double, 1U> &v_r,
                         ::coder::array<double, 1U> &v_a) const
{
    ::coder::array<double, 1U> b_r_r;
    double J[5][5];
    double b_J[5];
    int b_loop_ub;
    int c_loop_ub;
    int loop_ub;
    // 'Kinematics:139' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:142' N   = size( r_r, 2 );
    // 'Kinematics:143' v_a = zeros( size( v_r ) );
    v_a.set_size(v_r.size(0));
    loop_ub = v_r.size(0);
    for (int i{0}; i < loop_ub; i++) {
        v_a[i] = 0.0;
    }
    // 'Kinematics:145' for j = 1 : N
    // 'Kinematics:146' J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
    b_loop_ub = r_r.size(0);
    b_r_r.set_size(r_r.size(0));
    for (int i1{0}; i1 < b_loop_ub; i1++) {
        b_r_r[i1] = r_r[i1];
    }
    kin_J_ar_xyzbc(b_r_r, parameters, J);
    // 'Kinematics:147' v_a( :, j ) = J * v_r( :, j );
    for (int i2{0}; i2 < 5; i2++) {
        double d;
        d = 0.0;
        for (int i4{0}; i4 < 5; i4++) {
            d += J[i4][i2] * v_r[i4];
        }
        b_J[i2] = d;
    }
    c_loop_ub = v_r.size(0);
    for (int i3{0}; i3 < c_loop_ub; i3++) {
        v_a[i3] = b_J[i3];
    }
    //              end
}

//
// function [ v_r ] = v_relative( this, r_a, v_a )
//
// Arguments    : const ::coder::array<double, 2U> &r_a
//                const ::coder::array<double, 2U> &v_a
//                ::coder::array<double, 2U> &v_r
// Return Type  : void
//
void Kinematics::v_relative(const ::coder::array<double, 2U> &r_a,
                            const ::coder::array<double, 2U> &v_a,
                            ::coder::array<double, 2U> &v_r) const
{
    ::coder::array<double, 1U> b_r_a;
    int i1;
    int loop_ub;
    unsigned int unnamed_idx_0;
    //         %% Jacobian
    // 'Kinematics:126' coder.inline( "never" );
    //              if( coder.target( 'MATLAB' ) )
    // 'Kinematics:129' N   = size( r_a, 2 );
    // 'Kinematics:130' v_r = zeros( size( v_a ) );
    unnamed_idx_0 = static_cast<unsigned int>(v_a.size(0));
    v_r.set_size(v_a.size(0), v_a.size(1));
    loop_ub = v_a.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = static_cast<int>(unnamed_idx_0);
        for (int i2{0}; i2 < b_loop_ub; i2++) {
            v_r[i2 + v_r.size(0) * i] = 0.0;
        }
    }
    // 'Kinematics:131' for j = 1 : N
    i1 = r_a.size(1);
    for (int j{0}; j < i1; j++) {
        double J[5][5];
        double b_J[5];
        int c_loop_ub;
        int d_loop_ub;
        // 'Kinematics:132' J   = kin_J_ra_xyzbc( r_a( :, j ), this.parameters );
        c_loop_ub = r_a.size(0);
        b_r_a.set_size(r_a.size(0));
        for (int i3{0}; i3 < c_loop_ub; i3++) {
            b_r_a[i3] = r_a[i3 + r_a.size(0) * j];
        }
        kin_J_ra_xyzbc(b_r_a, parameters, J);
        // 'Kinematics:133' v_r( :, j ) = J * v_a( :, j );
        for (int i4{0}; i4 < 5; i4++) {
            double d;
            d = 0.0;
            for (int i6{0}; i6 < 5; i6++) {
                d += J[i6][i4] * v_a[i6 + v_a.size(0) * j];
            }
            b_J[i4] = d;
        }
        d_loop_ub = v_r.size(0);
        for (int i5{0}; i5 < d_loop_ub; i5++) {
            v_r[i5 + v_r.size(0) * j] = b_J[i5];
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
