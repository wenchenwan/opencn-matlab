
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
#include "rand.h"
#include "coder_array.h"
#include "coder_bounded_array.h"

// Function Definitions
//
// function  [res, resd, resdd, resddd] = export_kinematic_class( cfg, vec, vecd, vecdd, vecddd )
//
// Arguments    : const FeedoptConfig cfg
//                const ::coder::array<double, 2U> &vec
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
void export_kinematic_class(const FeedoptConfig cfg, const ::coder::array<double, 2U> &vec,
                            const ::coder::array<double, 2U> &vecd,
                            const ::coder::array<double, 2U> &vecdd,
                            const ::coder::array<double, 2U> &vecddd,
                            ::coder::array<double, 2U> &res, ::coder::array<double, 2U> &resd,
                            ::coder::array<double, 2U> &resdd, ::coder::array<double, 2U> &resddd)
{
    Kinematics kin;
    ::coder::array<double, 2U> b_res;
    ::coder::array<double, 2U> b_resd;
    ::coder::array<double, 2U> b_resdd;
    ::coder::array<double, 2U> b_resddd;
    ::coder::array<double, 2U> r;
    double d;
    double d1;
    double d10;
    double d11;
    double d2;
    double d3;
    double d4;
    double d5;
    double d6;
    double d7;
    double d8;
    double d9;
    int c_loop_ub;
    int e_loop_ub;
    int g_loop_ub;
    int i_loop_ub;
    int k_loop_ub;
    int loop_ub;
    int m_loop_ub;
    int o_loop_ub;
    int q_loop_ub;
    int r_loop_ub;
    int t_loop_ub;
    int v_loop_ub;
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
    // 'export_kinematic_class:28' res = kin.r_joint( vec ) + rand;
    kin.r_joint(vec, r);
    d = coder::b_rand();
    res.set_size(r.size(0), r.size(1));
    loop_ub = r.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = r.size(0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            res[i1 + res.size(0) * i] = r[i1 + r.size(0) * i] + d;
        }
    }
    // 'export_kinematic_class:29' res = kin.r_relative( res) + rand;
    kin.r_relative(res, r);
    d1 = coder::b_rand();
    res.set_size(r.size(0), r.size(1));
    c_loop_ub = r.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int d_loop_ub;
        d_loop_ub = r.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            res[i3 + res.size(0) * i2] = r[i3 + r.size(0) * i2] + d1;
        }
    }
    // ----------------------------------------------------------------%
    //  Advanced kinematics
    // ----------------------------------------------------------------%
    //  Speed
    // 'export_kinematic_class:36' resd = kin.v_joint( res, vecd ) + rand;
    kin.v_joint(res, vecd, r);
    d2 = coder::b_rand();
    resd.set_size(r.size(0), r.size(1));
    e_loop_ub = r.size(1);
    for (int i4{0}; i4 < e_loop_ub; i4++) {
        int f_loop_ub;
        f_loop_ub = r.size(0);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            resd[i5 + resd.size(0) * i4] = r[i5 + r.size(0) * i4] + d2;
        }
    }
    // 'export_kinematic_class:37' resd = kin.v_relative( res, resd ) + rand;
    kin.v_relative(res, resd, r);
    d3 = coder::b_rand();
    resd.set_size(r.size(0), r.size(1));
    g_loop_ub = r.size(1);
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        int h_loop_ub;
        h_loop_ub = r.size(0);
        for (int i7{0}; i7 < h_loop_ub; i7++) {
            resd[i7 + resd.size(0) * i6] = r[i7 + r.size(0) * i6] + d3;
        }
    }
    //  Acceleration
    // 'export_kinematic_class:40' resdd = kin.a_joint( res, resd, vecdd ) + rand;
    kin.a_joint(res, resd, vecdd, r);
    d4 = coder::b_rand();
    resdd.set_size(r.size(0), r.size(1));
    i_loop_ub = r.size(1);
    for (int i8{0}; i8 < i_loop_ub; i8++) {
        int j_loop_ub;
        j_loop_ub = r.size(0);
        for (int i9{0}; i9 < j_loop_ub; i9++) {
            resdd[i9 + resdd.size(0) * i8] = r[i9 + r.size(0) * i8] + d4;
        }
    }
    // 'export_kinematic_class:41' resdd = kin.a_relative( res, resd, resdd ) + rand;
    kin.a_relative(res, resd, resdd, r);
    d5 = coder::b_rand();
    resdd.set_size(r.size(0), r.size(1));
    k_loop_ub = r.size(1);
    for (int i10{0}; i10 < k_loop_ub; i10++) {
        int l_loop_ub;
        l_loop_ub = r.size(0);
        for (int i11{0}; i11 < l_loop_ub; i11++) {
            resdd[i11 + resdd.size(0) * i10] = r[i11 + r.size(0) * i10] + d5;
        }
    }
    //  Jerk
    // 'export_kinematic_class:44' resddd = kin.j_joint( res, resd, resdd, vecddd ) + rand;
    kin.j_joint(res, resd, resdd, vecddd, r);
    d6 = coder::b_rand();
    resddd.set_size(r.size(0), r.size(1));
    m_loop_ub = r.size(1);
    for (int i12{0}; i12 < m_loop_ub; i12++) {
        int n_loop_ub;
        n_loop_ub = r.size(0);
        for (int i13{0}; i13 < n_loop_ub; i13++) {
            resddd[i13 + resddd.size(0) * i12] = r[i13 + r.size(0) * i12] + d6;
        }
    }
    // 'export_kinematic_class:45' resddd = kin.j_relative( res, resd, resdd, resddd ) + rand;
    kin.j_relative(res, resd, resdd, resddd, r);
    d7 = coder::b_rand();
    resddd.set_size(r.size(0), r.size(1));
    o_loop_ub = r.size(1);
    for (int i14{0}; i14 < o_loop_ub; i14++) {
        int p_loop_ub;
        p_loop_ub = r.size(0);
        for (int i15{0}; i15 < p_loop_ub; i15++) {
            resddd[i15 + resddd.size(0) * i14] = r[i15 + r.size(0) * i14] + d7;
        }
    }
    //  All
    // 'export_kinematic_class:48' [ res, resd, resdd, resddd] = kin.relative( res, resd,resdd,
    // resddd );
    kin.relative(res, resd, resdd, resddd, b_res, b_resd, b_resdd, b_resddd);
    // 'export_kinematic_class:49' [ res, resd, resdd, resddd ] = kin.joint( res + rand, resd +
    // rand, resdd + rand, resddd + rand );
    d8 = coder::b_rand();
    d9 = coder::b_rand();
    d10 = coder::b_rand();
    d11 = coder::b_rand();
    q_loop_ub = b_res.size(1);
    for (int i16{0}; i16 < q_loop_ub; i16++) {
        int s_loop_ub;
        s_loop_ub = b_res.size(0);
        for (int i18{0}; i18 < s_loop_ub; i18++) {
            b_res[i18 + b_res.size(0) * i16] = b_res[i18 + b_res.size(0) * i16] + d8;
        }
    }
    r_loop_ub = b_resd.size(1);
    for (int i17{0}; i17 < r_loop_ub; i17++) {
        int u_loop_ub;
        u_loop_ub = b_resd.size(0);
        for (int i20{0}; i20 < u_loop_ub; i20++) {
            b_resd[i20 + b_resd.size(0) * i17] = b_resd[i20 + b_resd.size(0) * i17] + d9;
        }
    }
    t_loop_ub = b_resdd.size(1);
    for (int i19{0}; i19 < t_loop_ub; i19++) {
        int w_loop_ub;
        w_loop_ub = b_resdd.size(0);
        for (int i22{0}; i22 < w_loop_ub; i22++) {
            b_resdd[i22 + b_resdd.size(0) * i19] = b_resdd[i22 + b_resdd.size(0) * i19] + d10;
        }
    }
    v_loop_ub = b_resddd.size(1);
    for (int i21{0}; i21 < v_loop_ub; i21++) {
        int x_loop_ub;
        x_loop_ub = b_resddd.size(0);
        for (int i23{0}; i23 < x_loop_ub; i23++) {
            b_resddd[i23 + b_resddd.size(0) * i21] = b_resddd[i23 + b_resddd.size(0) * i21] + d11;
        }
    }
    kin.joint(b_res, b_resd, b_resdd, b_resddd, res, resd, resdd, resddd);
}

} // namespace ocn

//
// File trailer for export_kinematic_class.cpp
//
// [EOF]
//
