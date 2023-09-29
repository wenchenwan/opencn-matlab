
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: export_kinematic_class.cpp
//
// MATLAB Coder version            : 5.4
//

// Include Files
#include "export_kinematic_class.h"
#include "Kinematics.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "opencn_matlab_types.h"
#include "coder_array.h"
#include "coder_bounded_array.h"

// Function Definitions
//
// function  [res, resd, resdd, resddd] = export_kinematic_class( cfg, vec, vecd, vecdd, vecddd )
//
// Arguments    : const FeedoptConfig cfg
//                ::coder::array<double, 2U> &vec
//                const ::coder::array<double, 2U> &vecd
//                const ::coder::array<double, 2U> &vecdd
//                const ::coder::array<double, 2U> &vecddd
//                ::coder::array<double, 2U> &res
//                ::coder::array<double, 2U> &resd
//                ::coder::array<double, 2U> &resdd
//                ::coder::array<double, 2U> &resddd
// Return Type  : void
//
namespace ocn {
void export_kinematic_class(const FeedoptConfig cfg, ::coder::array<double, 2U> &vec,
                            const ::coder::array<double, 2U> &vecd,
                            const ::coder::array<double, 2U> &vecdd,
                            const ::coder::array<double, 2U> &vecddd,
                            ::coder::array<double, 2U> &res, ::coder::array<double, 2U> &resd,
                            ::coder::array<double, 2U> &resdd, ::coder::array<double, 2U> &resddd)
{
    Kinematics kin;
    ::coder::array<double, 2U> b_vec;
    ::coder::array<double, 2U> b_vecd;
    ::coder::array<double, 2U> b_vecdd;
    ::coder::array<double, 2U> b_vecddd;
    ::coder::array<double, 2U> c_vec;
    ::coder::array<double, 2U> d_vec;
    ::coder::array<double, 2U> e_vec;
    ::coder::array<double, 2U> f_vec;
    ::coder::array<double, 2U> g_vec;
    ::coder::array<double, 2U> h_vec;
    ::coder::array<double, 2U> i_vec;
    ::coder::array<double, 2U> j_vec;
    int c_loop_ub;
    int e_loop_ub;
    int g_loop_ub;
    int i_loop_ub;
    int k_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int o_loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'export_kinematic_class:3' coder.inline( "never" );
    //  Constructor
    // 'export_kinematic_class:6' kin = Kinematics( cfg.kin_type, cfg.kin_params );
    //  Set parameters
    // 'export_kinematic_class:9' kin = kin.set_params( cfg.kin_params );
    //  Set type
    // 'export_kinematic_class:12' kin = kin.set_type( cfg.kin_type );
    //  Set tool length
    // 'export_kinematic_class:15' kin = kin.set_tool_length( 1.0 );
    kin.init(cfg.kin_type, cfg.kin_params.data, cfg.kin_params.size[0]);
    kin.set_params(cfg.kin_params.data, cfg.kin_params.size[0]);
    kin.set_type(cfg.kin_type);
    kin.set_tool_length(1.0);
    //  Get params
    // 'export_kinematic_class:18' params = kin.get_params();
    //  Get types
    // 'export_kinematic_class:21' type = kin.get_type();
    // ----------------------------------------------------------------%
    //  Basic kinematics
    // ----------------------------------------------------------------%
    //  Position
    // 'export_kinematic_class:28' vec = kin.r_joint( vec );
    b_vec.set_size(vec.size(0), vec.size(1));
    loop_ub = vec.size(1) - 1;
    for (int i{0}; i <= loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = vec.size(0) - 1;
        for (int i1{0}; i1 <= b_loop_ub; i1++) {
            b_vec[i1 + b_vec.size(0) * i] = vec[i1 + vec.size(0) * i];
        }
    }
    kin.r_joint(b_vec, vec);
    // 'export_kinematic_class:29' vec = kin.r_relative( vec);
    c_vec.set_size(vec.size(0), vec.size(1));
    c_loop_ub = vec.size(1) - 1;
    for (int i2{0}; i2 <= c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = vec.size(0) - 1;
        for (int i3{0}; i3 <= d_loop_ub; i3++) {
            c_vec[i3 + c_vec.size(0) * i2] = vec[i3 + vec.size(0) * i2];
        }
    }
    kin.r_relative(c_vec, vec);
    // ----------------------------------------------------------------%
    //  Advanced kinematics
    // ----------------------------------------------------------------%
    //  Speed
    // 'export_kinematic_class:36' vec = kin.v_joint( vec, vecd );
    d_vec.set_size(vec.size(0), vec.size(1));
    e_loop_ub = vec.size(1) - 1;
    for (int i4{0}; i4 <= e_loop_ub; i4++) {
        int f_loop_ub;
        f_loop_ub = vec.size(0) - 1;
        for (int i5{0}; i5 <= f_loop_ub; i5++) {
            d_vec[i5 + d_vec.size(0) * i4] = vec[i5 + vec.size(0) * i4];
        }
    }
    kin.v_joint(d_vec, vecd, vec);
    // 'export_kinematic_class:37' vec = kin.v_relative( vec, vecd );
    e_vec.set_size(vec.size(0), vec.size(1));
    g_loop_ub = vec.size(1) - 1;
    for (int i6{0}; i6 <= g_loop_ub; i6++) {
        int h_loop_ub;
        h_loop_ub = vec.size(0) - 1;
        for (int i7{0}; i7 <= h_loop_ub; i7++) {
            e_vec[i7 + e_vec.size(0) * i6] = vec[i7 + vec.size(0) * i6];
        }
    }
    kin.v_relative(e_vec, vecd, vec);
    //  Acceleration
    // 'export_kinematic_class:40' vec = kin.a_joint( vec, vecd, vecdd );
    f_vec.set_size(vec.size(0), vec.size(1));
    i_loop_ub = vec.size(1) - 1;
    for (int i8{0}; i8 <= i_loop_ub; i8++) {
        int j_loop_ub;
        j_loop_ub = vec.size(0) - 1;
        for (int i9{0}; i9 <= j_loop_ub; i9++) {
            f_vec[i9 + f_vec.size(0) * i8] = vec[i9 + vec.size(0) * i8];
        }
    }
    kin.a_joint(f_vec, vecd, vecdd, vec);
    // 'export_kinematic_class:41' vec = kin.a_relative( vec, vecd, vecdd );
    g_vec.set_size(vec.size(0), vec.size(1));
    k_loop_ub = vec.size(1) - 1;
    for (int i10{0}; i10 <= k_loop_ub; i10++) {
        int l_loop_ub;
        l_loop_ub = vec.size(0) - 1;
        for (int i11{0}; i11 <= l_loop_ub; i11++) {
            g_vec[i11 + g_vec.size(0) * i10] = vec[i11 + vec.size(0) * i10];
        }
    }
    kin.a_relative(g_vec, vecd, vecdd, vec);
    //  Jerk
    // 'export_kinematic_class:44' vec = kin.j_joint( vec, vecd, vecdd, vecddd );
    h_vec.set_size(vec.size(0), vec.size(1));
    m_loop_ub = vec.size(1) - 1;
    for (int i12{0}; i12 <= m_loop_ub; i12++) {
        int n_loop_ub;
        n_loop_ub = vec.size(0) - 1;
        for (int i13{0}; i13 <= n_loop_ub; i13++) {
            h_vec[i13 + h_vec.size(0) * i12] = vec[i13 + vec.size(0) * i12];
        }
    }
    kin.j_joint(h_vec, vecd, vecdd, vecddd, vec);
    // 'export_kinematic_class:45' vec = kin.j_relative( vec, vecd, vecdd, vecddd );
    i_vec.set_size(vec.size(0), vec.size(1));
    o_loop_ub = vec.size(1) - 1;
    for (int i14{0}; i14 <= o_loop_ub; i14++) {
        int p_loop_ub;
        p_loop_ub = vec.size(0) - 1;
        for (int i15{0}; i15 <= p_loop_ub; i15++) {
            i_vec[i15 + i_vec.size(0) * i14] = vec[i15 + vec.size(0) * i14];
        }
    }
    kin.j_relative(i_vec, vecd, vecdd, vecddd, vec);
    //  All
    // 'export_kinematic_class:48' [ vec, vecd, vecdd, vecddd] = kin.relative( vec, vecd, vecdd,
    // vecddd );
    kin.relative(vec, vecd, vecdd, vecddd, j_vec, b_vecd, b_vecdd, b_vecddd);
    // 'export_kinematic_class:49' [ res, resd, resdd, resddd ] = kin.joint( vec, vecd, vecdd,
    // vecddd );
    kin.joint(j_vec, b_vecd, b_vecdd, b_vecddd, res, resd, resdd, resddd);
}

} // namespace ocn

//
// File trailer for export_kinematic_class.cpp
//
// [EOF]
//
