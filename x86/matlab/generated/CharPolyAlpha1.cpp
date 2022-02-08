//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CharPolyAlpha1.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 08-Feb-2022 09:15:12
//

// Include Files
#include "CharPolyAlpha1.h"
#include <cmath>

// Function Definitions
//
// CHARPOLYALPHA1
//     COEFF_POLY_ALPHA1 = CHARPOLYALPHA1(IN1)
//
// Arguments    : const double in1[16]
//                double Coeff_Poly_Alpha1[10]
// Return Type  : void
//
namespace ocn {
void CharPolyAlpha1(const double in1[16], double Coeff_Poly_Alpha1[10])
{
    double Coeff_Poly_Alpha1_tmp;
    double Coeff_Poly_Alpha1_tmp_tmp;
    double Coeff_Poly_Alpha1_tmp_tmp_tmp;
    double ab_Coeff_Poly_Alpha1_tmp;
    double ac_Coeff_Poly_Alpha1_tmp;
    double ad_Coeff_Poly_Alpha1_tmp;
    double ae_Coeff_Poly_Alpha1_tmp;
    double b_Coeff_Poly_Alpha1_tmp;
    double b_Coeff_Poly_Alpha1_tmp_tmp;
    double bb_Coeff_Poly_Alpha1_tmp;
    double bc_Coeff_Poly_Alpha1_tmp;
    double bd_Coeff_Poly_Alpha1_tmp;
    double be_Coeff_Poly_Alpha1_tmp;
    double c_Coeff_Poly_Alpha1_tmp;
    double c_Coeff_Poly_Alpha1_tmp_tmp;
    double cb_Coeff_Poly_Alpha1_tmp;
    double cc_Coeff_Poly_Alpha1_tmp;
    double cd_Coeff_Poly_Alpha1_tmp;
    double ce_Coeff_Poly_Alpha1_tmp;
    double d;
    double d1;
    double d10;
    double d11;
    double d12;
    double d13;
    double d14;
    double d15;
    double d16;
    double d17;
    double d18;
    double d19;
    double d2;
    double d20;
    double d21;
    double d22;
    double d23;
    double d24;
    double d25;
    double d26;
    double d27;
    double d28;
    double d29;
    double d3;
    double d30;
    double d31;
    double d32;
    double d33;
    double d34;
    double d35;
    double d36;
    double d37;
    double d38;
    double d39;
    double d4;
    double d40;
    double d41;
    double d42;
    double d43;
    double d44;
    double d45;
    double d46;
    double d47;
    double d48;
    double d49;
    double d5;
    double d50;
    double d51;
    double d6;
    double d7;
    double d8;
    double d9;
    double d_Coeff_Poly_Alpha1_tmp;
    double d_Coeff_Poly_Alpha1_tmp_tmp;
    double db_Coeff_Poly_Alpha1_tmp;
    double dc_Coeff_Poly_Alpha1_tmp;
    double dd_Coeff_Poly_Alpha1_tmp;
    double e_Coeff_Poly_Alpha1_tmp;
    double e_Coeff_Poly_Alpha1_tmp_tmp;
    double eb_Coeff_Poly_Alpha1_tmp;
    double ec_Coeff_Poly_Alpha1_tmp;
    double ed_Coeff_Poly_Alpha1_tmp;
    double f_Coeff_Poly_Alpha1_tmp;
    double f_Coeff_Poly_Alpha1_tmp_tmp;
    double fb_Coeff_Poly_Alpha1_tmp;
    double fc_Coeff_Poly_Alpha1_tmp;
    double fd_Coeff_Poly_Alpha1_tmp;
    double g_Coeff_Poly_Alpha1_tmp;
    double g_Coeff_Poly_Alpha1_tmp_tmp;
    double gb_Coeff_Poly_Alpha1_tmp;
    double gc_Coeff_Poly_Alpha1_tmp;
    double gd_Coeff_Poly_Alpha1_tmp;
    double h_Coeff_Poly_Alpha1_tmp;
    double h_Coeff_Poly_Alpha1_tmp_tmp;
    double hb_Coeff_Poly_Alpha1_tmp;
    double hc_Coeff_Poly_Alpha1_tmp;
    double hd_Coeff_Poly_Alpha1_tmp;
    double i_Coeff_Poly_Alpha1_tmp;
    double i_Coeff_Poly_Alpha1_tmp_tmp;
    double ib_Coeff_Poly_Alpha1_tmp;
    double ic_Coeff_Poly_Alpha1_tmp;
    double id_Coeff_Poly_Alpha1_tmp;
    double j_Coeff_Poly_Alpha1_tmp;
    double jb_Coeff_Poly_Alpha1_tmp;
    double jc_Coeff_Poly_Alpha1_tmp;
    double jd_Coeff_Poly_Alpha1_tmp;
    double k_Coeff_Poly_Alpha1_tmp;
    double kb_Coeff_Poly_Alpha1_tmp;
    double kc_Coeff_Poly_Alpha1_tmp;
    double kd_Coeff_Poly_Alpha1_tmp;
    double l_Coeff_Poly_Alpha1_tmp;
    double lb_Coeff_Poly_Alpha1_tmp;
    double lc_Coeff_Poly_Alpha1_tmp;
    double ld_Coeff_Poly_Alpha1_tmp;
    double m_Coeff_Poly_Alpha1_tmp;
    double mb_Coeff_Poly_Alpha1_tmp;
    double mc_Coeff_Poly_Alpha1_tmp;
    double md_Coeff_Poly_Alpha1_tmp;
    double n_Coeff_Poly_Alpha1_tmp;
    double nb_Coeff_Poly_Alpha1_tmp;
    double nc_Coeff_Poly_Alpha1_tmp;
    double nd_Coeff_Poly_Alpha1_tmp;
    double o_Coeff_Poly_Alpha1_tmp;
    double ob_Coeff_Poly_Alpha1_tmp;
    double oc_Coeff_Poly_Alpha1_tmp;
    double od_Coeff_Poly_Alpha1_tmp;
    double p_Coeff_Poly_Alpha1_tmp;
    double pb_Coeff_Poly_Alpha1_tmp;
    double pc_Coeff_Poly_Alpha1_tmp;
    double pd_Coeff_Poly_Alpha1_tmp;
    double q_Coeff_Poly_Alpha1_tmp;
    double qb_Coeff_Poly_Alpha1_tmp;
    double qc_Coeff_Poly_Alpha1_tmp;
    double qd_Coeff_Poly_Alpha1_tmp;
    double r_Coeff_Poly_Alpha1_tmp;
    double rb_Coeff_Poly_Alpha1_tmp;
    double rc_Coeff_Poly_Alpha1_tmp;
    double rd_Coeff_Poly_Alpha1_tmp;
    double s_Coeff_Poly_Alpha1_tmp;
    double sb_Coeff_Poly_Alpha1_tmp;
    double sc_Coeff_Poly_Alpha1_tmp;
    double sd_Coeff_Poly_Alpha1_tmp;
    double t10;
    double t11;
    double t12;
    double t13;
    double t14;
    double t15;
    double t16;
    double t17;
    double t18;
    double t19;
    double t2;
    double t20;
    double t21;
    double t3;
    double t4;
    double t5;
    double t6;
    double t7;
    double t8;
    double t9;
    double t_Coeff_Poly_Alpha1_tmp;
    double tb_Coeff_Poly_Alpha1_tmp;
    double tc_Coeff_Poly_Alpha1_tmp;
    double td_Coeff_Poly_Alpha1_tmp;
    double u_Coeff_Poly_Alpha1_tmp;
    double ub_Coeff_Poly_Alpha1_tmp;
    double uc_Coeff_Poly_Alpha1_tmp;
    double ud_Coeff_Poly_Alpha1_tmp;
    double v_Coeff_Poly_Alpha1_tmp;
    double vb_Coeff_Poly_Alpha1_tmp;
    double vc_Coeff_Poly_Alpha1_tmp;
    double vd_Coeff_Poly_Alpha1_tmp;
    double w_Coeff_Poly_Alpha1_tmp;
    double wb_Coeff_Poly_Alpha1_tmp;
    double wc_Coeff_Poly_Alpha1_tmp;
    double wd_Coeff_Poly_Alpha1_tmp;
    double x_Coeff_Poly_Alpha1_tmp;
    double xb_Coeff_Poly_Alpha1_tmp;
    double xc_Coeff_Poly_Alpha1_tmp;
    double xd_Coeff_Poly_Alpha1_tmp;
    double y_Coeff_Poly_Alpha1_tmp;
    double yb_Coeff_Poly_Alpha1_tmp;
    double yc_Coeff_Poly_Alpha1_tmp;
    double yd_Coeff_Poly_Alpha1_tmp;
    //     This function was generated by the Symbolic Math Toolbox version 8.3.
    //     25-May-2019 09:07:33
    t2 = std::pow(in1[0], 2.0);
    t3 = std::pow(in1[0], 3.0);
    t4 = std::pow(in1[1], 2.0);
    t5 = std::pow(in1[1], 3.0);
    t6 = std::pow(in1[2], 2.0);
    t7 = std::pow(in1[2], 3.0);
    t8 = std::pow(in1[3], 2.0);
    t9 = std::pow(in1[3], 3.0);
    t10 = std::pow(in1[4], 2.0);
    t11 = std::pow(in1[5], 2.0);
    t12 = std::pow(in1[6], 2.0);
    t13 = std::pow(in1[7], 2.0);
    t14 = std::pow(in1[8], 2.0);
    t15 = std::pow(in1[9], 2.0);
    t16 = std::pow(in1[10], 2.0);
    t17 = std::pow(in1[11], 2.0);
    t18 = std::pow(in1[12], 2.0);
    t19 = std::pow(in1[13], 2.0);
    t20 = std::pow(in1[14], 2.0);
    t21 = std::pow(in1[15], 2.0);
    Coeff_Poly_Alpha1_tmp = in1[4] * t2;
    b_Coeff_Poly_Alpha1_tmp = in1[0] * in1[8] * in1[12];
    Coeff_Poly_Alpha1[0] = (std::pow(in1[4], 3.0) * t18 + Coeff_Poly_Alpha1_tmp * t14) -
                           b_Coeff_Poly_Alpha1_tmp * t10 * 2.0;
    c_Coeff_Poly_Alpha1_tmp = in1[0] * in1[1];
    d_Coeff_Poly_Alpha1_tmp = in1[4] * in1[8];
    e_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp * in1[4];
    f_Coeff_Poly_Alpha1_tmp = in1[0] * in1[4];
    g_Coeff_Poly_Alpha1_tmp = f_Coeff_Poly_Alpha1_tmp * in1[5];
    h_Coeff_Poly_Alpha1_tmp = in1[5] * t2;
    i_Coeff_Poly_Alpha1_tmp = in1[1] * in1[8] * in1[12];
    j_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp * in1[10];
    k_Coeff_Poly_Alpha1_tmp = in1[0] * in1[10] * in1[12];
    Coeff_Poly_Alpha1[1] = (((((h_Coeff_Poly_Alpha1_tmp * t14 + in1[5] * t10 * t18 * 3.0) +
                               e_Coeff_Poly_Alpha1_tmp * t14 * 2.0) -
                              i_Coeff_Poly_Alpha1_tmp * t10 * 2.0) +
                             j_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                            k_Coeff_Poly_Alpha1_tmp * t10 * 2.0) -
                           g_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0;
    Coeff_Poly_Alpha1_tmp_tmp = in1[0] * in1[2];
    l_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp * in1[4];
    m_Coeff_Poly_Alpha1_tmp = in1[2] * in1[8];
    n_Coeff_Poly_Alpha1_tmp = in1[5] * in1[8];
    o_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp * in1[5];
    p_Coeff_Poly_Alpha1_tmp = e_Coeff_Poly_Alpha1_tmp * in1[8];
    q_Coeff_Poly_Alpha1_tmp = in1[1] * in1[4];
    r_Coeff_Poly_Alpha1_tmp = f_Coeff_Poly_Alpha1_tmp * in1[6];
    s_Coeff_Poly_Alpha1_tmp = q_Coeff_Poly_Alpha1_tmp * in1[5];
    t_Coeff_Poly_Alpha1_tmp = in1[4] * t4;
    u_Coeff_Poly_Alpha1_tmp = in1[6] * t2;
    v_Coeff_Poly_Alpha1_tmp = m_Coeff_Poly_Alpha1_tmp * in1[9];
    w_Coeff_Poly_Alpha1_tmp = n_Coeff_Poly_Alpha1_tmp * in1[10];
    x_Coeff_Poly_Alpha1_tmp = in1[1] * in1[10] * in1[12];
    y_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp * in1[12];
    ab_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp * in1[14];
    bb_Coeff_Poly_Alpha1_tmp = in1[4] * in1[9] * in1[13];
    cb_Coeff_Poly_Alpha1_tmp = in1[0] * in1[12] * in1[14];
    b_Coeff_Poly_Alpha1_tmp_tmp = in1[2] * in1[12];
    db_Coeff_Poly_Alpha1_tmp = b_Coeff_Poly_Alpha1_tmp_tmp * in1[13];
    Coeff_Poly_Alpha1[2] =
        (((((((((((((((((((((t3 * t15 + in1[0] * t10 * t19) + Coeff_Poly_Alpha1_tmp * t16) +
                           t_Coeff_Poly_Alpha1_tmp * t14) +
                          in1[4] * t11 * t18 * 3.0) +
                         u_Coeff_Poly_Alpha1_tmp * t14) +
                        in1[6] * t10 * t18 * 3.0) +
                       o_Coeff_Poly_Alpha1_tmp * t14 * 2.0) -
                      v_Coeff_Poly_Alpha1_tmp * t2) -
                     b_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
                    w_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                   x_Coeff_Poly_Alpha1_tmp * t10 * 2.0) +
                  y_Coeff_Poly_Alpha1_tmp * t6) +
                 ab_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                bb_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
               cb_Coeff_Poly_Alpha1_tmp * t10 * 2.0) -
              db_Coeff_Poly_Alpha1_tmp * t10) +
             p_Coeff_Poly_Alpha1_tmp * in1[10] * 4.0) -
            l_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
           l_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
          r_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
         s_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
        g_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0;
    d = in1[9] * in1[11];
    d1 = in1[1] * t2;
    eb_Coeff_Poly_Alpha1_tmp = in1[4] * in1[10];
    fb_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp * in1[5];
    c_Coeff_Poly_Alpha1_tmp_tmp = in1[0] * in1[3];
    gb_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp_tmp * in1[4];
    d_Coeff_Poly_Alpha1_tmp_tmp = in1[1] * in1[2];
    hb_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[4];
    ib_Coeff_Poly_Alpha1_tmp = in1[4] * in1[5];
    jb_Coeff_Poly_Alpha1_tmp = in1[3] * in1[8];
    kb_Coeff_Poly_Alpha1_tmp = in1[2] * in1[9];
    e_Coeff_Poly_Alpha1_tmp_tmp = in1[6] * in1[8];
    Coeff_Poly_Alpha1_tmp_tmp_tmp = c_Coeff_Poly_Alpha1_tmp * in1[2];
    lb_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp_tmp * in1[8];
    mb_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp * in1[6];
    nb_Coeff_Poly_Alpha1_tmp = o_Coeff_Poly_Alpha1_tmp * in1[8];
    ob_Coeff_Poly_Alpha1_tmp = in1[2] * in1[3];
    pb_Coeff_Poly_Alpha1_tmp = ob_Coeff_Poly_Alpha1_tmp * in1[4];
    qb_Coeff_Poly_Alpha1_tmp = in1[0] * in1[5];
    rb_Coeff_Poly_Alpha1_tmp = f_Coeff_Poly_Alpha1_tmp * in1[7];
    sb_Coeff_Poly_Alpha1_tmp = qb_Coeff_Poly_Alpha1_tmp * in1[6];
    tb_Coeff_Poly_Alpha1_tmp = q_Coeff_Poly_Alpha1_tmp * in1[6];
    ub_Coeff_Poly_Alpha1_tmp = in1[2] * in1[4];
    vb_Coeff_Poly_Alpha1_tmp = in1[5] * t4;
    wb_Coeff_Poly_Alpha1_tmp = in1[7] * t2;
    xb_Coeff_Poly_Alpha1_tmp = jb_Coeff_Poly_Alpha1_tmp * in1[9];
    yb_Coeff_Poly_Alpha1_tmp = m_Coeff_Poly_Alpha1_tmp * in1[11];
    ac_Coeff_Poly_Alpha1_tmp = kb_Coeff_Poly_Alpha1_tmp * in1[10];
    bc_Coeff_Poly_Alpha1_tmp = e_Coeff_Poly_Alpha1_tmp_tmp * in1[10];
    cc_Coeff_Poly_Alpha1_tmp = n_Coeff_Poly_Alpha1_tmp * in1[12];
    dc_Coeff_Poly_Alpha1_tmp = eb_Coeff_Poly_Alpha1_tmp * in1[12];
    ec_Coeff_Poly_Alpha1_tmp = n_Coeff_Poly_Alpha1_tmp * in1[14];
    fc_Coeff_Poly_Alpha1_tmp = in1[5] * in1[9] * in1[13];
    gc_Coeff_Poly_Alpha1_tmp = in1[1] * in1[12] * in1[14];
    hc_Coeff_Poly_Alpha1_tmp = eb_Coeff_Poly_Alpha1_tmp * in1[14];
    ic_Coeff_Poly_Alpha1_tmp = in1[4] * in1[11] * in1[13];
    f_Coeff_Poly_Alpha1_tmp_tmp = in1[3] * in1[12];
    jc_Coeff_Poly_Alpha1_tmp = f_Coeff_Poly_Alpha1_tmp_tmp * in1[13];
    Coeff_Poly_Alpha1[3] =
        (((((((((((((((((((((((((((((((((((((((((((((std::pow(in1[5], 3.0) * t18 + d * t3 * 2.0) +
                                                    d1 * t15 * 3.0) +
                                                   in1[1] * t10 * t19) +
                                                  h_Coeff_Poly_Alpha1_tmp * t16) +
                                                 vb_Coeff_Poly_Alpha1_tmp * t14) +
                                                wb_Coeff_Poly_Alpha1_tmp * t14) +
                                               in1[7] * t10 * t18 * 3.0) +
                                              e_Coeff_Poly_Alpha1_tmp * t16 * 2.0) +
                                             mb_Coeff_Poly_Alpha1_tmp * t14 * 2.0) +
                                            g_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
                                           ib_Coeff_Poly_Alpha1_tmp * in1[6] * t18 * 6.0) -
                                          xb_Coeff_Poly_Alpha1_tmp * t2) -
                                         yb_Coeff_Poly_Alpha1_tmp * t2) -
                                        ac_Coeff_Poly_Alpha1_tmp * t2) -
                                       i_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
                                      j_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
                                     k_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
                                    bc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) +
                                   cc_Coeff_Poly_Alpha1_tmp * t6) +
                                  dc_Coeff_Poly_Alpha1_tmp * t6) +
                                 ec_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                                fc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                               gc_Coeff_Poly_Alpha1_tmp * t10 * 2.0) +
                              hc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                             ic_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                            jc_Coeff_Poly_Alpha1_tmp * t10) -
                           lb_Coeff_Poly_Alpha1_tmp * in1[9] * 2.0) +
                          nb_Coeff_Poly_Alpha1_tmp * in1[10] * 4.0) +
                         p_Coeff_Poly_Alpha1_tmp * in1[14] * 4.0) -
                        e_Coeff_Poly_Alpha1_tmp * in1[9] * in1[13] * 4.0) -
                       fb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                      fb_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
                     gb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                    gb_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
                   hb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                  hb_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
                 l_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                l_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) +
               pb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 2.0) -
              rb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
             sb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
            tb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
           r_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) -
          s_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) -
         g_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
        ub_Coeff_Poly_Alpha1_tmp * in1[5] * in1[12] * in1[13] * 2.0;
    d2 = in1[0] * in1[9];
    d3 = in1[1] * in1[9];
    d4 = in1[3] * in1[9];
    d5 = in1[2] * in1[10];
    d6 = c_Coeff_Poly_Alpha1_tmp * in1[7];
    d7 = in1[0] * t4;
    d8 = in1[6] * t4;
    d9 = jb_Coeff_Poly_Alpha1_tmp * in1[11];
    d10 = d4 * in1[10];
    d11 = d2 * in1[13];
    d12 = d5 * in1[11];
    d13 = m_Coeff_Poly_Alpha1_tmp * in1[15];
    d14 = kb_Coeff_Poly_Alpha1_tmp * in1[14];
    d15 = in1[9] * in1[12];
    d16 = in1[9] * in1[15];
    d17 = in1[7] * in1[8];
    d18 = d17 * in1[10];
    kc_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp * in1[6];
    lc_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp_tmp * in1[5];
    mc_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[5];
    g_Coeff_Poly_Alpha1_tmp_tmp = in1[1] * in1[3];
    nc_Coeff_Poly_Alpha1_tmp = g_Coeff_Poly_Alpha1_tmp_tmp * in1[4];
    h_Coeff_Poly_Alpha1_tmp_tmp = c_Coeff_Poly_Alpha1_tmp * in1[3];
    oc_Coeff_Poly_Alpha1_tmp = h_Coeff_Poly_Alpha1_tmp_tmp * in1[8];
    pc_Coeff_Poly_Alpha1_tmp = ob_Coeff_Poly_Alpha1_tmp * in1[5];
    qc_Coeff_Poly_Alpha1_tmp = in1[1] * in1[5];
    rc_Coeff_Poly_Alpha1_tmp = qb_Coeff_Poly_Alpha1_tmp * in1[7];
    sc_Coeff_Poly_Alpha1_tmp = q_Coeff_Poly_Alpha1_tmp * in1[7];
    tc_Coeff_Poly_Alpha1_tmp = qc_Coeff_Poly_Alpha1_tmp * in1[6];
    uc_Coeff_Poly_Alpha1_tmp = in1[3] * in1[4];
    vc_Coeff_Poly_Alpha1_tmp = in1[6] * in1[9] * in1[13];
    i_Coeff_Poly_Alpha1_tmp_tmp = in1[5] * in1[10];
    wc_Coeff_Poly_Alpha1_tmp = i_Coeff_Poly_Alpha1_tmp_tmp * in1[14];
    xc_Coeff_Poly_Alpha1_tmp = in1[5] * in1[11] * in1[13];
    yc_Coeff_Poly_Alpha1_tmp = in1[4] * in1[12] * in1[14];
    ad_Coeff_Poly_Alpha1_tmp = in1[4] * in1[13] * in1[15];
    bd_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp_tmp * in1[9];
    cd_Coeff_Poly_Alpha1_tmp = i_Coeff_Poly_Alpha1_tmp_tmp * in1[12];
    dd_Coeff_Poly_Alpha1_tmp = e_Coeff_Poly_Alpha1_tmp_tmp * in1[14];
    Coeff_Poly_Alpha1[4] = (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t3 * t17 - d15 * t7) + d16 * t3 * 2.0) + d7 * t15 * 3.0) + in1[0] * t11 * t19) + t_Coeff_Poly_Alpha1_tmp * t16) + Coeff_Poly_Alpha1_tmp * t20) + in1[4] * t12 * t18 * 3.0) + u_Coeff_Poly_Alpha1_tmp * t16) + d8 * t14) + in1[6] * t11 * t18 * 3.0) + o_Coeff_Poly_Alpha1_tmp * t16 * 2.0) + d6 * t14 * 2.0) + r_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + s_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + ib_Coeff_Poly_Alpha1_tmp * in1[7] * t18 * 6.0) - v_Coeff_Poly_Alpha1_tmp * t4) - b_Coeff_Poly_Alpha1_tmp * t12 * 2.0) + d3 * in1[11] * t2 * 6.0) - d9 * t2) - d10 * t2) + d11 * t6) - d12 * t2) + w_Coeff_Poly_Alpha1_tmp * t4 * 2.0) - x_Coeff_Poly_Alpha1_tmp * t11 * 2.0) + y_Coeff_Poly_Alpha1_tmp * t8) - d13 * t2) - d14 * t2) + d18 * t2 * 2.0) + ab_Coeff_Poly_Alpha1_tmp * t4 * 2.0) - bb_Coeff_Poly_Alpha1_tmp * t4 * 2.0) + e_Coeff_Poly_Alpha1_tmp_tmp * in1[12] * t6) - cb_Coeff_Poly_Alpha1_tmp * t11 * 2.0) + cd_Coeff_Poly_Alpha1_tmp * t6) - db_Coeff_Poly_Alpha1_tmp * t11) + dd_Coeff_Poly_Alpha1_tmp * t2 * 2.0) - vc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) + wc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) - xc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) + yc_Coeff_Poly_Alpha1_tmp * t6) - ad_Coeff_Poly_Alpha1_tmp * t2 * 2.0) - oc_Coeff_Poly_Alpha1_tmp * in1[9] * 2.0) - lb_Coeff_Poly_Alpha1_tmp * in1[11] * 2.0) - bd_Coeff_Poly_Alpha1_tmp * in1[10] * 2.0) + mb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[10] * 4.0) + nb_Coeff_Poly_Alpha1_tmp * in1[14] * 4.0) - o_Coeff_Poly_Alpha1_tmp * in1[9] * in1[13] * 4.0) + e_Coeff_Poly_Alpha1_tmp * in1[10] * in1[14] * 4.0) - e_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 4.0) - kc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + kc_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - lc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + lc_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - mc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + mc_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - nc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + nc_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - fb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + fb_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - gb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + gb_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - hb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + hb_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) + pc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 2.0) + pb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 2.0) - rc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) - sc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) - tc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) + l_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - l_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) - rb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) - sb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) - tb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) - r_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - s_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - ub_Coeff_Poly_Alpha1_tmp * in1[6] * in1[12] * in1[13] * 2.0) - uc_Coeff_Poly_Alpha1_tmp * in1[5] * in1[12] * in1[13] * 2.0;
    d19 = in1[11] * in1[15];
    d20 = in1[6] * in1[10];
    d21 = in1[3] * in1[10];
    d22 = in1[7] * t4;
    d23 = d3 * in1[13];
    d24 = d21 * in1[11];
    d25 = in1[0] * in1[11];
    d26 = d25 * in1[13];
    d27 = in1[2] * in1[11];
    d28 = jb_Coeff_Poly_Alpha1_tmp * in1[15];
    d29 = d4 * in1[14];
    d30 = d5 * in1[15];
    d31 = d27 * in1[14];
    d32 = in1[7] * in1[9] * in1[13];
    d33 = d20 * in1[14];
    d34 = in1[6] * in1[11] * in1[13];
    d35 = in1[5] * in1[12] * in1[14];
    d36 = in1[5] * in1[13] * in1[15];
    ed_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp * in1[7];
    fd_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp_tmp * in1[6];
    gd_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[6];
    hd_Coeff_Poly_Alpha1_tmp = g_Coeff_Poly_Alpha1_tmp_tmp * in1[5];
    id_Coeff_Poly_Alpha1_tmp = ob_Coeff_Poly_Alpha1_tmp * in1[6];
    jd_Coeff_Poly_Alpha1_tmp = in1[0] * in1[6] * in1[7];
    kd_Coeff_Poly_Alpha1_tmp = qc_Coeff_Poly_Alpha1_tmp * in1[7];
    ld_Coeff_Poly_Alpha1_tmp = in1[2] * in1[5];
    md_Coeff_Poly_Alpha1_tmp = h_Coeff_Poly_Alpha1_tmp_tmp * in1[9];
    nd_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp_tmp * in1[10];
    od_Coeff_Poly_Alpha1_tmp = d17 * in1[12];
    Coeff_Poly_Alpha1[5] = (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t5 * t15 - in1[11] * in1[12] * t7) + d19 * t3 * 2.0) + d1 * t17 * 3.0) + in1[1] * t11 * t19) + vb_Coeff_Poly_Alpha1_tmp * t16) + h_Coeff_Poly_Alpha1_tmp * t20) + in1[5] * t12 * t18 * 3.0) + wb_Coeff_Poly_Alpha1_tmp * t16) + d22 * t14) + in1[7] * t11 * t18 * 3.0) + e_Coeff_Poly_Alpha1_tmp * t20 * 2.0) + mb_Coeff_Poly_Alpha1_tmp * t16 * 2.0) + rb_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + sb_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + tb_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + in1[4] * in1[6] * in1[7] * t18 * 6.0) + d2 * in1[11] * t4 * 6.0) - xb_Coeff_Poly_Alpha1_tmp * t4) - yb_Coeff_Poly_Alpha1_tmp * t4) - ac_Coeff_Poly_Alpha1_tmp * t4) - i_Coeff_Poly_Alpha1_tmp * t12 * 2.0) - k_Coeff_Poly_Alpha1_tmp * t12 * 2.0) + d23 * t6) - d24 * t2) + bc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) + d26 * t6) - d4 * in1[12] * t6 * 3.0) + d3 * in1[15] * t2 * 6.0) + cc_Coeff_Poly_Alpha1_tmp * t8) - d28 * t2) - d29 * t2) + dc_Coeff_Poly_Alpha1_tmp * t8) - d30 * t2) - d31 * t2) + ec_Coeff_Poly_Alpha1_tmp * t4 * 2.0) - fc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) + od_Coeff_Poly_Alpha1_tmp * t6) - gc_Coeff_Poly_Alpha1_tmp * t11 * 2.0) + hc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) - ic_Coeff_Poly_Alpha1_tmp * t4 * 2.0) + d20 * in1[12] * t6) - jc_Coeff_Poly_Alpha1_tmp * t11) + d17 * in1[14] * t2 * 2.0) - d32 * t2 * 2.0) + d33 * t2 * 2.0) - d34 * t2 * 2.0) + d35 * t6) - d36 * t2 * 2.0) - oc_Coeff_Poly_Alpha1_tmp * in1[11] * 2.0) - md_Coeff_Poly_Alpha1_tmp * in1[10] * 2.0) - nd_Coeff_Poly_Alpha1_tmp * in1[11] * 2.0) - lb_Coeff_Poly_Alpha1_tmp * in1[15] * 2.0) - bd_Coeff_Poly_Alpha1_tmp * in1[14] * 2.0) + d6 * in1[8] * in1[10] * 4.0) + Coeff_Poly_Alpha1_tmp_tmp * in1[3] * in1[9] * in1[13] * 2.0) + c_Coeff_Poly_Alpha1_tmp * in1[6] * in1[8] * in1[14] * 4.0) - in1[0] * in1[1] * in1[6] * in1[9] * in1[13] * 4.0) + o_Coeff_Poly_Alpha1_tmp * in1[10] * in1[14] * 4.0) - o_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 4.0) - ed_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + ed_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - fd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + fd_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - gd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + gd_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - hd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + hd_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - kc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + kc_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - lc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + lc_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - mc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + mc_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - nc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + nc_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) + id_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 2.0) + pc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 2.0) - e_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 4.0) - jd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) - kd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) + fb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - fb_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) + gb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - gb_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) - rc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) + hb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - hb_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) - sc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) - tc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) + pb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 2.0) - rb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - sb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - tb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - ub_Coeff_Poly_Alpha1_tmp * in1[7] * in1[12] * in1[13] * 2.0) - ld_Coeff_Poly_Alpha1_tmp * in1[6] * in1[12] * in1[13] * 2.0) - uc_Coeff_Poly_Alpha1_tmp * in1[6] * in1[12] * in1[13] * 2.0;
    d37 = in1[1] * in1[11];
    d38 = in1[3] * in1[11];
    d39 = in1[7] * in1[10];
    d40 = d37 * in1[13];
    d41 = d21 * in1[15];
    d42 = d38 * in1[14];
    d43 = in1[0] * in1[13] * in1[15];
    d44 = d39 * in1[12];
    d45 = in1[2] * in1[14] * in1[15];
    d46 = d39 * in1[14];
    d47 = in1[7] * in1[11] * in1[13];
    d48 = in1[12] * in1[15];
    d49 = in1[6] * in1[12] * in1[14];
    d50 = in1[6] * in1[13] * in1[15];
    d51 = h_Coeff_Poly_Alpha1_tmp_tmp * in1[10];
    pd_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp_tmp * in1[7];
    qd_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[7];
    rd_Coeff_Poly_Alpha1_tmp = g_Coeff_Poly_Alpha1_tmp_tmp * in1[6];
    sd_Coeff_Poly_Alpha1_tmp = ob_Coeff_Poly_Alpha1_tmp * in1[7];
    td_Coeff_Poly_Alpha1_tmp = in1[1] * in1[6] * in1[7];
    ud_Coeff_Poly_Alpha1_tmp = in1[3] * in1[5];
    vd_Coeff_Poly_Alpha1_tmp = in1[0] * in1[2] * in1[3];
    Coeff_Poly_Alpha1[6] = (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t3 * t21 + std::pow(in1[6], 3.0) * t18) + d * t5 * 2.0) - d48 * t7) + d7 * t17 * 3.0) + in1[0] * t12 * t19) + t_Coeff_Poly_Alpha1_tmp * t20) + in1[4] * t13 * t18 * 3.0) + d8 * t16) + u_Coeff_Poly_Alpha1_tmp * t20) + o_Coeff_Poly_Alpha1_tmp * t20 * 2.0) + d6 * t16 * 2.0) + rc_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + sc_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + tc_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + in1[5] * in1[6] * in1[7] * t18 * 6.0) - b_Coeff_Poly_Alpha1_tmp * t13 * 2.0) - d9 * t4) - d10 * t4) + d11 * t8) - d12 * t4) - kb_Coeff_Poly_Alpha1_tmp * in1[12] * t8 * 3.0) - x_Coeff_Poly_Alpha1_tmp * t12 * 2.0) + d2 * in1[15] * t4 * 6.0) - d13 * t4) - d14 * t4) + d18 * t4 * 2.0) + d40 * t6) - d38 * in1[12] * t6 * 3.0) + in1[6] * in1[8] * in1[12] * t8) - cb_Coeff_Poly_Alpha1_tmp * t12 * 2.0) + d37 * in1[15] * t2 * 6.0) + cd_Coeff_Poly_Alpha1_tmp * t8) - db_Coeff_Poly_Alpha1_tmp * t12) - d41 * t2) - d42 * t2) + dd_Coeff_Poly_Alpha1_tmp * t4 * 2.0) - vc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) + d43 * t6) + wc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) - xc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) + d44 * t6) + yc_Coeff_Poly_Alpha1_tmp * t8) - d45 * t2) + d46 * t2 * 2.0) - d47 * t2 * 2.0) - ad_Coeff_Poly_Alpha1_tmp * t4 * 2.0) + d49 * t6) - d50 * t2 * 2.0) - d51 * in1[11] * 2.0) - oc_Coeff_Poly_Alpha1_tmp * in1[15] * 2.0) - md_Coeff_Poly_Alpha1_tmp * in1[14] * 2.0) - nd_Coeff_Poly_Alpha1_tmp * in1[15] * 2.0) - Coeff_Poly_Alpha1_tmp_tmp_tmp * in1[11] * in1[14] * 2.0) + d_Coeff_Poly_Alpha1_tmp_tmp * in1[3] * in1[9] * in1[13] * 2.0) + vd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 2.0) + in1[0] * in1[1] * in1[7] * in1[8] * in1[14] * 4.0) - d6 * in1[9] * in1[13] * 4.0) + mb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[14] * 4.0) - mb_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 4.0) - pd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + pd_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - qd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + qd_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - rd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + rd_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) - ed_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + ed_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - fd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + fd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - gd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + gd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - hd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + hd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) + sd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 2.0) + id_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 2.0) - o_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 4.0) - td_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) + kc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - kc_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) + lc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - lc_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) - jd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) + mc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - mc_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) + nc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - nc_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) - kd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) + pc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 2.0) - rc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - sc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - tc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - ld_Coeff_Poly_Alpha1_tmp * in1[7] * in1[12] * in1[13] * 2.0) - uc_Coeff_Poly_Alpha1_tmp * in1[7] * in1[12] * in1[13] * 2.0) - ud_Coeff_Poly_Alpha1_tmp * in1[6] * in1[12] * in1[13] * 2.0;
    wd_Coeff_Poly_Alpha1_tmp = g_Coeff_Poly_Alpha1_tmp_tmp * in1[7];
    xd_Coeff_Poly_Alpha1_tmp = in1[1] * in1[2] * in1[3];
    yd_Coeff_Poly_Alpha1_tmp = in1[1] * in1[13] * in1[15];
    ae_Coeff_Poly_Alpha1_tmp = in1[3] * in1[14] * in1[15];
    be_Coeff_Poly_Alpha1_tmp = in1[7] * in1[12] * in1[14];
    ce_Coeff_Poly_Alpha1_tmp = in1[7] * in1[13] * in1[15];
    Coeff_Poly_Alpha1[7] = ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t5 * t17 - d15 * t9) + d16 * t5 * 2.0) + d1 * t21 * 3.0) + in1[1] * t12 * t19) + vb_Coeff_Poly_Alpha1_tmp * t20) + in1[5] * t13 * t18 * 3.0) + d22 * t16) + wb_Coeff_Poly_Alpha1_tmp * t20) + in1[7] * t12 * t18 * 3.0) + mb_Coeff_Poly_Alpha1_tmp * t20 * 2.0) + jd_Coeff_Poly_Alpha1_tmp * t19 * 2.0) + kd_Coeff_Poly_Alpha1_tmp * t19 * 2.0) - i_Coeff_Poly_Alpha1_tmp * t13 * 2.0) - k_Coeff_Poly_Alpha1_tmp * t13 * 2.0) + d23 * t8) - d24 * t4) + d26 * t8) - d27 * in1[12] * t8 * 3.0) + d25 * in1[15] * t4 * 6.0) - d28 * t4) - d29 * t4) - d30 * t4) - d31 * t4) + od_Coeff_Poly_Alpha1_tmp * t8) - gc_Coeff_Poly_Alpha1_tmp * t12 * 2.0) + in1[6] * in1[10] * in1[12] * t8) - jc_Coeff_Poly_Alpha1_tmp * t12) + in1[7] * in1[8] * in1[14] * t4 * 2.0) - d32 * t4 * 2.0) + yd_Coeff_Poly_Alpha1_tmp * t6) + d33 * t4 * 2.0) - d34 * t4 * 2.0) - f_Coeff_Poly_Alpha1_tmp_tmp * in1[15] * t6 * 3.0) + d35 * t8) - ae_Coeff_Poly_Alpha1_tmp * t2) - d36 * t4 * 2.0) + be_Coeff_Poly_Alpha1_tmp * t6) - ce_Coeff_Poly_Alpha1_tmp * t2 * 2.0) - d51 * in1[15] * 2.0) - h_Coeff_Poly_Alpha1_tmp_tmp * in1[11] * in1[14] * 2.0) + xd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 2.0) - Coeff_Poly_Alpha1_tmp_tmp_tmp * in1[14] * in1[15] * 2.0) + d6 * in1[10] * in1[14] * 4.0) - d6 * in1[11] * in1[13] * 4.0) - wd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) + wd_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) + vd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 2.0) - pd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + pd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - qd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + qd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) - rd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) + rd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) + sd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 2.0) - mb_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 4.0) + ed_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - ed_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) + fd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - fd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) + gd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - gd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) + hd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) - hd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) - td_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) + id_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 2.0) - jd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - kd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) - in1[2] * in1[6] * in1[7] * in1[12] * in1[13] * 2.0) - ud_Coeff_Poly_Alpha1_tmp * in1[7] * in1[12] * in1[13] * 2.0;
    Coeff_Poly_Alpha1[8] =
        ((((((((((((((((((((((((((((((((((-in1[11] * in1[12] * t9 + d19 * t5 * 2.0) +
                                         d7 * t21 * 3.0) +
                                        in1[0] * t13 * t19) +
                                       d8 * t20) +
                                      in1[6] * t13 * t18 * 3.0) +
                                     d6 * t20 * 2.0) +
                                    td_Coeff_Poly_Alpha1_tmp * t19 * 2.0) -
                                   x_Coeff_Poly_Alpha1_tmp * t13 * 2.0) +
                                  d40 * t8) -
                                 cb_Coeff_Poly_Alpha1_tmp * t13 * 2.0) -
                                db_Coeff_Poly_Alpha1_tmp * t13) -
                               d41 * t4) -
                              d42 * t4) +
                             d43 * t8) -
                            b_Coeff_Poly_Alpha1_tmp_tmp * in1[15] * t8 * 3.0) +
                           d44 * t8) -
                          d45 * t4) +
                         d46 * t4 * 2.0) -
                        d47 * t4 * 2.0) +
                       d49 * t8) -
                      d50 * t4 * 2.0) -
                     h_Coeff_Poly_Alpha1_tmp_tmp * in1[14] * in1[15] * 2.0) +
                    xd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 2.0) -
                   wd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                  wd_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                 d6 * in1[13] * in1[15] * 4.0) +
                pd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
               pd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
              qd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
             qd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
            rd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
           rd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
          sd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 2.0) -
         td_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
        in1[3] * in1[6] * in1[7] * in1[12] * in1[13] * 2.0;
    Coeff_Poly_Alpha1[9] =
        (((((((((((t5 * t21 + std::pow(in1[7], 3.0) * t18) - d48 * t9) + in1[1] * t13 * t19) +
                d22 * t20) -
               gc_Coeff_Poly_Alpha1_tmp * t13 * 2.0) -
              jc_Coeff_Poly_Alpha1_tmp * t13) +
             yd_Coeff_Poly_Alpha1_tmp * t8) -
            ae_Coeff_Poly_Alpha1_tmp * t4) +
           be_Coeff_Poly_Alpha1_tmp * t8) -
          ce_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
         wd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
        wd_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14];
}

} // namespace ocn

//
// File trailer for CharPolyAlpha1.cpp
//
// [EOF]
//
