//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Kinematics.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 06-Sep-2023 16:04:28
//

// Include Files
#include "Kinematics.h"
#include "kin_J2P_ar_xyzbc.h"
#include "kin_JP_ar_xyzbc.h"
#include "kin_J_ar_xyzbc.h"
#include "kin_inverse_xyzbc.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : void
// Return Type  : Kinematics
//
namespace ocn {
Kinematics::Kinematics() = default;

//
// Arguments    : void
// Return Type  : void
//
Kinematics::~Kinematics() = default;

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
    double t2[5][5];
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
    if (r_a.size(1) - 1 >= 0) {
        t2[0][3] = 0.0;
        t2[0][4] = 0.0;
        t2[1][2] = 0.0;
        t2[1][3] = 0.0;
        t2[1][4] = 0.0;
        t2[2][3] = 0.0;
        t2[2][4] = 0.0;
        t2[3][3] = 1.0;
        t2[3][4] = 0.0;
        t2[4][2] = 0.0;
        t2[4][3] = 0.0;
        t2[4][4] = 1.0;
    }
    for (int j{0}; j < i1; j++) {
        double c_t2[5];
        double b_t2;
        double b_t2_tmp;
        double c_t2_tmp;
        double d;
        double d1;
        double d2;
        double d3;
        double d4;
        double d_t2_tmp;
        double e_t2_tmp;
        double f_t2_tmp;
        double t14;
        double t2_tmp;
        double t3;
        double t4;
        double t5;
        int c_loop_ub;
        // 'Kinematics:132' J   = kin_J_ra_xyzbc( r_a( :, j ), this.parameters );
        // kin_J_ra_xyzbc
        //     J_ra = kin_J_ra_xyzbc(IN1,IN2)
        //     This function was generated by the Symbolic Math Toolbox version 9.1.
        //     01-Sep-2023 14:01:21
        // Jacobian Kinematics ( forward ) :
        // INPUTS :
        // 	r_a : 5 x 1 : pose vector( joint )
        // 	v_a : 5 x 1 : speed vector( joint )
        // 	p   : 5 x 1 : parameters
        // OUTPUTS :
        // 	M   : 5 x 5 : resulting matrix
        // 'kin_J_ra_xyzbc:16' A1 = in1(1,:);
        // 'kin_J_ra_xyzbc:17' A2 = in1(2,:);
        // 'kin_J_ra_xyzbc:18' A3 = in1(3,:);
        // 'kin_J_ra_xyzbc:19' A4 = in1(4,:);
        // 'kin_J_ra_xyzbc:20' A5 = in1(5,:);
        // 'kin_J_ra_xyzbc:21' P1_1 = in2(1);
        // 'kin_J_ra_xyzbc:22' P1_4 = in2(10);
        // 'kin_J_ra_xyzbc:23' P2_1 = in2(2);
        // 'kin_J_ra_xyzbc:24' P3_1 = in2(3);
        // 'kin_J_ra_xyzbc:25' P3_4 = in2(12);
        // 'kin_J_ra_xyzbc:26' t2 = cos(A4);
        d = r_a[r_a.size(0) * j + 3];
        b_t2 = std::cos(d);
        // 'kin_J_ra_xyzbc:27' t3 = cos(A5);
        d1 = r_a[r_a.size(0) * j + 4];
        t3 = std::cos(d1);
        // 'kin_J_ra_xyzbc:28' t4 = sin(A4);
        t4 = std::sin(d);
        // 'kin_J_ra_xyzbc:29' t5 = sin(A5);
        t5 = std::sin(d1);
        // 'kin_J_ra_xyzbc:30' t6 = A3.*t2;
        // 'kin_J_ra_xyzbc:31' t7 = P1_4.*t2;
        // 'kin_J_ra_xyzbc:32' t8 = P3_1.*t2;
        // 'kin_J_ra_xyzbc:33' t9 = P3_4.*t2;
        // 'kin_J_ra_xyzbc:34' t10 = A1.*t4;
        // 'kin_J_ra_xyzbc:35' t11 = P1_1.*t4;
        // 'kin_J_ra_xyzbc:36' t12 = -t6;
        // 'kin_J_ra_xyzbc:37' t13 = -t10;
        // 'kin_J_ra_xyzbc:38' t14 = t7+t8+t9+t11+t12+t13;
        d2 = r_a[r_a.size(0) * j + 2];
        d3 = r_a[r_a.size(0) * j];
        t14 = ((((parameters[9] * b_t2 + parameters[2] * b_t2) + parameters[11] * b_t2) +
                parameters[0] * t4) +
               -(d2 * b_t2)) +
              -(d3 * t4);
        // 'kin_J_ra_xyzbc:39' J_ra =
        // reshape([t2.*t3,t2.*t5,t4,0.0,0.0,-t5,t3,0.0,0.0,0.0,-t3.*t4,-t4.*t5,t2,0.0,0.0,t3.*t14,t5.*t14,A1.*t2-A3.*t4-P1_1.*t2+P1_4.*t4+P3_1.*t4+P3_4.*t4,1.0,0.0,-A2.*t3-P2_1.*t3-A1.*t2.*t5+A3.*t4.*t5+P1_1.*t2.*t5-P1_4.*t4.*t5-P3_1.*t4.*t5-P3_4.*t4.*t5,-A2.*t5-P2_1.*t5+A1.*t2.*t3-A3.*t3.*t4-P1_1.*t2.*t3+P1_4.*t3.*t4+P3_1.*t3.*t4+P3_4.*t3.*t4,0.0,0.0,1.0],[5,5]);
        // 'Kinematics:133' v_r( :, j ) = J * v_a( :, j );
        t2[0][0] = b_t2 * t3;
        t2[0][1] = b_t2 * t5;
        t2[0][2] = t4;
        t2[1][0] = -t5;
        t2[1][1] = t3;
        t2[2][0] = -t3 * t4;
        t2[2][1] = -t4 * t5;
        t2[2][2] = b_t2;
        t2[3][0] = t3 * t14;
        t2[3][1] = t5 * t14;
        t2_tmp = d3 * b_t2;
        b_t2_tmp = d2 * t4;
        c_t2_tmp = parameters[0] * b_t2;
        d_t2_tmp = parameters[9] * t4;
        e_t2_tmp = parameters[2] * t4;
        f_t2_tmp = parameters[11] * t4;
        t2[3][2] = ((((t2_tmp - b_t2_tmp) - c_t2_tmp) + d_t2_tmp) + e_t2_tmp) + f_t2_tmp;
        d4 = r_a[r_a.size(0) * j + 1];
        t2[4][0] =
            ((((((-d4 * t3 - parameters[1] * t3) - t2_tmp * t5) + b_t2_tmp * t5) + c_t2_tmp * t5) -
              d_t2_tmp * t5) -
             e_t2_tmp * t5) -
            f_t2_tmp * t5;
        t2[4][1] =
            ((((((-d4 * t5 - parameters[1] * t5) + t2_tmp * t3) - d2 * t3 * t4) - c_t2_tmp * t3) +
              parameters[9] * t3 * t4) +
             parameters[2] * t3 * t4) +
            parameters[11] * t3 * t4;
        for (int i3{0}; i3 < 5; i3++) {
            double d5;
            d5 = 0.0;
            for (int i5{0}; i5 < 5; i5++) {
                d5 += t2[i5][i3] * v_a[i5 + v_a.size(0) * j];
            }
            c_t2[i3] = d5;
        }
        c_loop_ub = v_r.size(0);
        for (int i4{0}; i4 < c_loop_ub; i4++) {
            v_r[i4 + v_r.size(0) * j] = c_t2[i4];
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
