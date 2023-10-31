
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
#include <emmintrin.h>

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
        int scalarLB;
        int vectorUB;
        b_loop_ub = r.size(0);
        scalarLB = (r.size(0) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (int i1{0}; i1 <= vectorUB; i1 += 2) {
            __m128d r1;
            r1 = _mm_loadu_pd(&r[i1 + r.size(0) * i]);
            _mm_storeu_pd(&res[i1 + res.size(0) * i], _mm_add_pd(r1, _mm_set1_pd(d)));
        }
        for (int i1{scalarLB}; i1 < b_loop_ub; i1++) {
            res[i1 + res.size(0) * i] = r[i1 + r.size(0) * i] + d;
        }
    }
    // 'export_kinematic_class:29' res = kin.r_relative( res) + rand;
    kin.r_relative(res, r);
    d1 = coder::b_rand();
    res.set_size(r.size(0), r.size(1));
    c_loop_ub = r.size(1);
    for (int i2{0}; i2 < c_loop_ub; i2++) {
        int b_scalarLB;
        int b_vectorUB;
        int d_loop_ub;
        d_loop_ub = r.size(0);
        b_scalarLB = (r.size(0) / 2) << 1;
        b_vectorUB = b_scalarLB - 2;
        for (int i3{0}; i3 <= b_vectorUB; i3 += 2) {
            __m128d r2;
            r2 = _mm_loadu_pd(&r[i3 + r.size(0) * i2]);
            _mm_storeu_pd(&res[i3 + res.size(0) * i2], _mm_add_pd(r2, _mm_set1_pd(d1)));
        }
        for (int i3{b_scalarLB}; i3 < d_loop_ub; i3++) {
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
        int c_scalarLB;
        int c_vectorUB;
        int f_loop_ub;
        f_loop_ub = r.size(0);
        c_scalarLB = (r.size(0) / 2) << 1;
        c_vectorUB = c_scalarLB - 2;
        for (int i5{0}; i5 <= c_vectorUB; i5 += 2) {
            __m128d r3;
            r3 = _mm_loadu_pd(&r[i5 + r.size(0) * i4]);
            _mm_storeu_pd(&resd[i5 + resd.size(0) * i4], _mm_add_pd(r3, _mm_set1_pd(d2)));
        }
        for (int i5{c_scalarLB}; i5 < f_loop_ub; i5++) {
            resd[i5 + resd.size(0) * i4] = r[i5 + r.size(0) * i4] + d2;
        }
    }
    // 'export_kinematic_class:37' resd = kin.v_relative( res, resd ) + rand;
    kin.v_relative(res, resd, r);
    d3 = coder::b_rand();
    resd.set_size(r.size(0), r.size(1));
    g_loop_ub = r.size(1);
    for (int i6{0}; i6 < g_loop_ub; i6++) {
        int d_scalarLB;
        int d_vectorUB;
        int h_loop_ub;
        h_loop_ub = r.size(0);
        d_scalarLB = (r.size(0) / 2) << 1;
        d_vectorUB = d_scalarLB - 2;
        for (int i7{0}; i7 <= d_vectorUB; i7 += 2) {
            __m128d r4;
            r4 = _mm_loadu_pd(&r[i7 + r.size(0) * i6]);
            _mm_storeu_pd(&resd[i7 + resd.size(0) * i6], _mm_add_pd(r4, _mm_set1_pd(d3)));
        }
        for (int i7{d_scalarLB}; i7 < h_loop_ub; i7++) {
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
        int e_scalarLB;
        int e_vectorUB;
        int j_loop_ub;
        j_loop_ub = r.size(0);
        e_scalarLB = (r.size(0) / 2) << 1;
        e_vectorUB = e_scalarLB - 2;
        for (int i9{0}; i9 <= e_vectorUB; i9 += 2) {
            __m128d r5;
            r5 = _mm_loadu_pd(&r[i9 + r.size(0) * i8]);
            _mm_storeu_pd(&resdd[i9 + resdd.size(0) * i8], _mm_add_pd(r5, _mm_set1_pd(d4)));
        }
        for (int i9{e_scalarLB}; i9 < j_loop_ub; i9++) {
            resdd[i9 + resdd.size(0) * i8] = r[i9 + r.size(0) * i8] + d4;
        }
    }
    // 'export_kinematic_class:41' resdd = kin.a_relative( res, resd, resdd ) + rand;
    kin.a_relative(res, resd, resdd, r);
    d5 = coder::b_rand();
    resdd.set_size(r.size(0), r.size(1));
    k_loop_ub = r.size(1);
    for (int i10{0}; i10 < k_loop_ub; i10++) {
        int f_scalarLB;
        int f_vectorUB;
        int l_loop_ub;
        l_loop_ub = r.size(0);
        f_scalarLB = (r.size(0) / 2) << 1;
        f_vectorUB = f_scalarLB - 2;
        for (int i11{0}; i11 <= f_vectorUB; i11 += 2) {
            __m128d r6;
            r6 = _mm_loadu_pd(&r[i11 + r.size(0) * i10]);
            _mm_storeu_pd(&resdd[i11 + resdd.size(0) * i10], _mm_add_pd(r6, _mm_set1_pd(d5)));
        }
        for (int i11{f_scalarLB}; i11 < l_loop_ub; i11++) {
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
        int g_scalarLB;
        int g_vectorUB;
        int n_loop_ub;
        n_loop_ub = r.size(0);
        g_scalarLB = (r.size(0) / 2) << 1;
        g_vectorUB = g_scalarLB - 2;
        for (int i13{0}; i13 <= g_vectorUB; i13 += 2) {
            __m128d r7;
            r7 = _mm_loadu_pd(&r[i13 + r.size(0) * i12]);
            _mm_storeu_pd(&resddd[i13 + resddd.size(0) * i12], _mm_add_pd(r7, _mm_set1_pd(d6)));
        }
        for (int i13{g_scalarLB}; i13 < n_loop_ub; i13++) {
            resddd[i13 + resddd.size(0) * i12] = r[i13 + r.size(0) * i12] + d6;
        }
    }
    // 'export_kinematic_class:45' resddd = kin.j_relative( res, resd, resdd, resddd ) + rand;
    kin.j_relative(res, resd, resdd, resddd, r);
    d7 = coder::b_rand();
    resddd.set_size(r.size(0), r.size(1));
    o_loop_ub = r.size(1);
    for (int i14{0}; i14 < o_loop_ub; i14++) {
        int h_scalarLB;
        int h_vectorUB;
        int p_loop_ub;
        p_loop_ub = r.size(0);
        h_scalarLB = (r.size(0) / 2) << 1;
        h_vectorUB = h_scalarLB - 2;
        for (int i15{0}; i15 <= h_vectorUB; i15 += 2) {
            __m128d r8;
            r8 = _mm_loadu_pd(&r[i15 + r.size(0) * i14]);
            _mm_storeu_pd(&resddd[i15 + resddd.size(0) * i14], _mm_add_pd(r8, _mm_set1_pd(d7)));
        }
        for (int i15{h_scalarLB}; i15 < p_loop_ub; i15++) {
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
        int i_scalarLB;
        int i_vectorUB;
        int s_loop_ub;
        s_loop_ub = b_res.size(0);
        i_scalarLB = (b_res.size(0) / 2) << 1;
        i_vectorUB = i_scalarLB - 2;
        for (int i18{0}; i18 <= i_vectorUB; i18 += 2) {
            __m128d r9;
            r9 = _mm_loadu_pd(&b_res[i18 + b_res.size(0) * i16]);
            _mm_storeu_pd(&b_res[i18 + b_res.size(0) * i16], _mm_add_pd(r9, _mm_set1_pd(d8)));
        }
        for (int i18{i_scalarLB}; i18 < s_loop_ub; i18++) {
            b_res[i18 + b_res.size(0) * i16] = b_res[i18 + b_res.size(0) * i16] + d8;
        }
    }
    r_loop_ub = b_resd.size(1);
    for (int i17{0}; i17 < r_loop_ub; i17++) {
        int j_scalarLB;
        int j_vectorUB;
        int u_loop_ub;
        u_loop_ub = b_resd.size(0);
        j_scalarLB = (b_resd.size(0) / 2) << 1;
        j_vectorUB = j_scalarLB - 2;
        for (int i20{0}; i20 <= j_vectorUB; i20 += 2) {
            __m128d r10;
            r10 = _mm_loadu_pd(&b_resd[i20 + b_resd.size(0) * i17]);
            _mm_storeu_pd(&b_resd[i20 + b_resd.size(0) * i17], _mm_add_pd(r10, _mm_set1_pd(d9)));
        }
        for (int i20{j_scalarLB}; i20 < u_loop_ub; i20++) {
            b_resd[i20 + b_resd.size(0) * i17] = b_resd[i20 + b_resd.size(0) * i17] + d9;
        }
    }
    t_loop_ub = b_resdd.size(1);
    for (int i19{0}; i19 < t_loop_ub; i19++) {
        int k_scalarLB;
        int k_vectorUB;
        int w_loop_ub;
        w_loop_ub = b_resdd.size(0);
        k_scalarLB = (b_resdd.size(0) / 2) << 1;
        k_vectorUB = k_scalarLB - 2;
        for (int i22{0}; i22 <= k_vectorUB; i22 += 2) {
            __m128d r11;
            r11 = _mm_loadu_pd(&b_resdd[i22 + b_resdd.size(0) * i19]);
            _mm_storeu_pd(&b_resdd[i22 + b_resdd.size(0) * i19], _mm_add_pd(r11, _mm_set1_pd(d10)));
        }
        for (int i22{k_scalarLB}; i22 < w_loop_ub; i22++) {
            b_resdd[i22 + b_resdd.size(0) * i19] = b_resdd[i22 + b_resdd.size(0) * i19] + d10;
        }
    }
    v_loop_ub = b_resddd.size(1);
    for (int i21{0}; i21 < v_loop_ub; i21++) {
        int l_scalarLB;
        int l_vectorUB;
        int x_loop_ub;
        x_loop_ub = b_resddd.size(0);
        l_scalarLB = (b_resddd.size(0) / 2) << 1;
        l_vectorUB = l_scalarLB - 2;
        for (int i23{0}; i23 <= l_vectorUB; i23 += 2) {
            __m128d r12;
            r12 = _mm_loadu_pd(&b_resddd[i23 + b_resddd.size(0) * i21]);
            _mm_storeu_pd(&b_resddd[i23 + b_resddd.size(0) * i21],
                          _mm_add_pd(r12, _mm_set1_pd(d11)));
        }
        for (int i23{l_scalarLB}; i23 < x_loop_ub; i23++) {
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
