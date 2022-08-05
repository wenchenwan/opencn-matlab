//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Calc_beta0_beta1.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-Aug-2022 16:07:54
//

// Include Files
#include "Calc_beta0_beta1.h"
#include <cmath>

// Function Definitions
//
// function [beta0,beta1] = Calc_beta0_beta1(alpha0,alpha1,in3,in4,in5,in6,in7,in8,in9)
//
// Calc_beta0_beta1
//     [BETA0,BETA1] = Calc_beta0_beta1(ALPHA0,ALPHA1,IN3,IN4,IN5,IN6,IN7,IN8,IN9)
//
// Arguments    : double alpha0
//                double alpha1
//                const double in3[5]
//                const double in4[5]
//                const double in5[5]
//                const double in6[5]
//                const double in7[5]
//                const double in8[5]
//                const double in9_data[]
//                double *beta0
//                double *beta1
// Return Type  : void
//
namespace ocn {
void Calc_beta0_beta1(double alpha0, double alpha1, const double in3[5], const double in4[5],
                      const double in5[5], const double in6[5], const double in7[5],
                      const double in8[5], const double in9_data[], double *beta0, double *beta1)
{
    double ab_beta0_tmp;
    double ac_beta0_tmp;
    double ad_beta0_tmp;
    double ae_beta0_tmp;
    double af_beta0_tmp;
    double ag_beta0_tmp;
    double ah_beta0_tmp;
    double b_beta0_tmp;
    double b_t65_tmp;
    double bb_beta0_tmp;
    double bc_beta0_tmp;
    double bd_beta0_tmp;
    double be_beta0_tmp;
    double beta0_tmp;
    double bf_beta0_tmp;
    double bg_beta0_tmp;
    double bh_beta0_tmp;
    double c_beta0_tmp;
    double c_t65_tmp;
    double cb_beta0_tmp;
    double cc_beta0_tmp;
    double cd_beta0_tmp;
    double ce_beta0_tmp;
    double cf_beta0_tmp;
    double cg_beta0_tmp;
    double ch_beta0_tmp;
    double d_beta0_tmp;
    double d_t65_tmp;
    double db_beta0_tmp;
    double dc_beta0_tmp;
    double dd_beta0_tmp;
    double de_beta0_tmp;
    double df_beta0_tmp;
    double dg_beta0_tmp;
    double dh_beta0_tmp;
    double e_beta0_tmp;
    double e_t65_tmp;
    double eb_beta0_tmp;
    double ec_beta0_tmp;
    double ed_beta0_tmp;
    double ee_beta0_tmp;
    double ef_beta0_tmp;
    double eg_beta0_tmp;
    double eh_beta0_tmp;
    double f_beta0_tmp;
    double f_t65_tmp;
    double fb_beta0_tmp;
    double fc_beta0_tmp;
    double fd_beta0_tmp;
    double fe_beta0_tmp;
    double ff_beta0_tmp;
    double fg_beta0_tmp;
    double g_beta0_tmp;
    double g_t65_tmp;
    double gb_beta0_tmp;
    double gc_beta0_tmp;
    double gd_beta0_tmp;
    double ge_beta0_tmp;
    double gf_beta0_tmp;
    double gg_beta0_tmp;
    double h_beta0_tmp;
    double h_t65_tmp;
    double hb_beta0_tmp;
    double hc_beta0_tmp;
    double hd_beta0_tmp;
    double he_beta0_tmp;
    double hf_beta0_tmp;
    double hg_beta0_tmp;
    double i_beta0_tmp;
    double i_t65_tmp;
    double ib_beta0_tmp;
    double ic_beta0_tmp;
    double id_beta0_tmp;
    double ie_beta0_tmp;
    double if_beta0_tmp;
    double ig_beta0_tmp;
    double j_beta0_tmp;
    double j_t65_tmp;
    double jb_beta0_tmp;
    double jc_beta0_tmp;
    double jd_beta0_tmp;
    double je_beta0_tmp;
    double jf_beta0_tmp;
    double jg_beta0_tmp;
    double k_beta0_tmp;
    double kb_beta0_tmp;
    double kc_beta0_tmp;
    double kd_beta0_tmp;
    double ke_beta0_tmp;
    double kf_beta0_tmp;
    double kg_beta0_tmp;
    double l_beta0_tmp;
    double lb_beta0_tmp;
    double lc_beta0_tmp;
    double ld_beta0_tmp;
    double le_beta0_tmp;
    double lf_beta0_tmp;
    double lg_beta0_tmp;
    double m_beta0_tmp;
    double mb_beta0_tmp;
    double mc_beta0_tmp;
    double md_beta0_tmp;
    double me_beta0_tmp;
    double mf_beta0_tmp;
    double mg_beta0_tmp;
    double n_beta0_tmp;
    double nb_beta0_tmp;
    double nc_beta0_tmp;
    double nd_beta0_tmp;
    double ne_beta0_tmp;
    double nf_beta0_tmp;
    double ng_beta0_tmp;
    double o_beta0_tmp;
    double ob_beta0_tmp;
    double oc_beta0_tmp;
    double od_beta0_tmp;
    double oe_beta0_tmp;
    double of_beta0_tmp;
    double og_beta0_tmp;
    double p_beta0_tmp;
    double pb_beta0_tmp;
    double pc_beta0_tmp;
    double pd_beta0_tmp;
    double pe_beta0_tmp;
    double pf_beta0_tmp;
    double pg_beta0_tmp;
    double q_beta0_tmp;
    double qb_beta0_tmp;
    double qc_beta0_tmp;
    double qd_beta0_tmp;
    double qe_beta0_tmp;
    double qf_beta0_tmp;
    double qg_beta0_tmp;
    double r_beta0_tmp;
    double rb_beta0_tmp;
    double rc_beta0_tmp;
    double rd_beta0_tmp;
    double re_beta0_tmp;
    double rf_beta0_tmp;
    double rg_beta0_tmp;
    double s_beta0_tmp;
    double sb_beta0_tmp;
    double sc_beta0_tmp;
    double sd_beta0_tmp;
    double se_beta0_tmp;
    double sf_beta0_tmp;
    double sg_beta0_tmp;
    double t10;
    double t11;
    double t12;
    double t13;
    double t14;
    double t15;
    double t16;
    double t17;
    double t18;
    double t2;
    double t3;
    double t4;
    double t5;
    double t6;
    double t65;
    double t65_tmp;
    double t7;
    double t8;
    double t9;
    double t_beta0_tmp;
    double tb_beta0_tmp;
    double tc_beta0_tmp;
    double td_beta0_tmp;
    double te_beta0_tmp;
    double tf_beta0_tmp;
    double tg_beta0_tmp;
    double u_beta0_tmp;
    double ub_beta0_tmp;
    double uc_beta0_tmp;
    double ud_beta0_tmp;
    double ue_beta0_tmp;
    double uf_beta0_tmp;
    double ug_beta0_tmp;
    double v_beta0_tmp;
    double vb_beta0_tmp;
    double vc_beta0_tmp;
    double vd_beta0_tmp;
    double ve_beta0_tmp;
    double vf_beta0_tmp;
    double vg_beta0_tmp;
    double w_beta0_tmp;
    double wb_beta0_tmp;
    double wc_beta0_tmp;
    double wd_beta0_tmp;
    double we_beta0_tmp;
    double wf_beta0_tmp;
    double wg_beta0_tmp;
    double x_beta0_tmp;
    double xb_beta0_tmp;
    double xc_beta0_tmp;
    double xd_beta0_tmp;
    double xe_beta0_tmp;
    double xf_beta0_tmp;
    double xg_beta0_tmp;
    double y_beta0_tmp;
    double yb_beta0_tmp;
    double yc_beta0_tmp;
    double yd_beta0_tmp;
    double ye_beta0_tmp;
    double yf_beta0_tmp;
    double yg_beta0_tmp;
    //     This function was generated by the Symbolic Math Toolbox version 9.0.
    //     10-Jun-2022 12:30:37
    // 'Calc_beta0_beta1:8' D_vec1 = in9(1,:);
    // 'Calc_beta0_beta1:9' D_vec2 = in9(2,:);
    // 'Calc_beta0_beta1:10' D_vec3 = in9(3,:);
    // 'Calc_beta0_beta1:11' D_vec4 = in9(4,:);
    // 'Calc_beta0_beta1:12' D_vec5 = in9(5,:);
    // 'Calc_beta0_beta1:13' nk0_vec1 = in5(1,:);
    // 'Calc_beta0_beta1:14' nk0_vec2 = in5(2,:);
    // 'Calc_beta0_beta1:15' nk0_vec3 = in5(3,:);
    // 'Calc_beta0_beta1:16' nk0_vec4 = in5(4,:);
    // 'Calc_beta0_beta1:17' nk0_vec5 = in5(5,:);
    // 'Calc_beta0_beta1:18' nk1_vec1 = in8(1,:);
    // 'Calc_beta0_beta1:19' nk1_vec2 = in8(2,:);
    // 'Calc_beta0_beta1:20' nk1_vec3 = in8(3,:);
    // 'Calc_beta0_beta1:21' nk1_vec4 = in8(4,:);
    // 'Calc_beta0_beta1:22' nk1_vec5 = in8(5,:);
    // 'Calc_beta0_beta1:23' p0_vec1 = in3(1,:);
    // 'Calc_beta0_beta1:24' p0_vec2 = in3(2,:);
    // 'Calc_beta0_beta1:25' p0_vec3 = in3(3,:);
    // 'Calc_beta0_beta1:26' p0_vec4 = in3(4,:);
    // 'Calc_beta0_beta1:27' p0_vec5 = in3(5,:);
    // 'Calc_beta0_beta1:28' p1_vec1 = in6(1,:);
    // 'Calc_beta0_beta1:29' p1_vec2 = in6(2,:);
    // 'Calc_beta0_beta1:30' p1_vec3 = in6(3,:);
    // 'Calc_beta0_beta1:31' p1_vec4 = in6(4,:);
    // 'Calc_beta0_beta1:32' p1_vec5 = in6(5,:);
    // 'Calc_beta0_beta1:33' t0_vec1 = in4(1,:);
    // 'Calc_beta0_beta1:34' t0_vec2 = in4(2,:);
    // 'Calc_beta0_beta1:35' t0_vec3 = in4(3,:);
    // 'Calc_beta0_beta1:36' t0_vec4 = in4(4,:);
    // 'Calc_beta0_beta1:37' t0_vec5 = in4(5,:);
    // 'Calc_beta0_beta1:38' t1_vec1 = in7(1,:);
    // 'Calc_beta0_beta1:39' t1_vec2 = in7(2,:);
    // 'Calc_beta0_beta1:40' t1_vec3 = in7(3,:);
    // 'Calc_beta0_beta1:41' t1_vec4 = in7(4,:);
    // 'Calc_beta0_beta1:42' t1_vec5 = in7(5,:);
    // 'Calc_beta0_beta1:43' t2 = D_vec1.^2;
    t2 = std::pow(in9_data[0], 2.0);
    // 'Calc_beta0_beta1:44' t3 = D_vec2.^2;
    t3 = std::pow(in9_data[1], 2.0);
    // 'Calc_beta0_beta1:45' t4 = D_vec3.^2;
    t4 = std::pow(in9_data[2], 2.0);
    // 'Calc_beta0_beta1:46' t5 = D_vec4.^2;
    t5 = std::pow(in9_data[3], 2.0);
    // 'Calc_beta0_beta1:47' t6 = D_vec5.^2;
    t6 = std::pow(in9_data[4], 2.0);
    // 'Calc_beta0_beta1:48' t7 = alpha0.^2;
    t7 = std::pow(alpha0, 2.0);
    // 'Calc_beta0_beta1:49' t8 = alpha1.^2;
    t8 = std::pow(alpha1, 2.0);
    // 'Calc_beta0_beta1:50' t9 = t0_vec1.^2;
    t9 = std::pow(in4[0], 2.0);
    // 'Calc_beta0_beta1:51' t10 = t0_vec2.^2;
    t10 = std::pow(in4[1], 2.0);
    // 'Calc_beta0_beta1:52' t11 = t0_vec3.^2;
    t11 = std::pow(in4[2], 2.0);
    // 'Calc_beta0_beta1:53' t12 = t0_vec4.^2;
    t12 = std::pow(in4[3], 2.0);
    // 'Calc_beta0_beta1:54' t13 = t0_vec5.^2;
    t13 = std::pow(in4[4], 2.0);
    // 'Calc_beta0_beta1:55' t14 = t1_vec1.^2;
    t14 = std::pow(in7[0], 2.0);
    // 'Calc_beta0_beta1:56' t15 = t1_vec2.^2;
    t15 = std::pow(in7[1], 2.0);
    // 'Calc_beta0_beta1:57' t16 = t1_vec3.^2;
    t16 = std::pow(in7[2], 2.0);
    // 'Calc_beta0_beta1:58' t17 = t1_vec4.^2;
    t17 = std::pow(in7[3], 2.0);
    // 'Calc_beta0_beta1:59' t18 = t1_vec5.^2;
    t18 = std::pow(in7[4], 2.0);
    // 'Calc_beta0_beta1:60' t19 = D_vec1.*D_vec2.*t0_vec1.*t0_vec2.*t1_vec1.*t1_vec2.*2.0;
    // 'Calc_beta0_beta1:61' t20 = D_vec1.*D_vec3.*t0_vec1.*t0_vec3.*t1_vec1.*t1_vec3.*2.0;
    // 'Calc_beta0_beta1:62' t21 = D_vec1.*D_vec4.*t0_vec1.*t0_vec4.*t1_vec1.*t1_vec4.*2.0;
    // 'Calc_beta0_beta1:63' t22 = D_vec2.*D_vec3.*t0_vec2.*t0_vec3.*t1_vec2.*t1_vec3.*2.0;
    // 'Calc_beta0_beta1:64' t23 = D_vec1.*D_vec5.*t0_vec1.*t0_vec5.*t1_vec1.*t1_vec5.*2.0;
    // 'Calc_beta0_beta1:65' t24 = D_vec2.*D_vec4.*t0_vec2.*t0_vec4.*t1_vec2.*t1_vec4.*2.0;
    // 'Calc_beta0_beta1:66' t25 = D_vec2.*D_vec5.*t0_vec2.*t0_vec5.*t1_vec2.*t1_vec5.*2.0;
    // 'Calc_beta0_beta1:67' t26 = D_vec3.*D_vec4.*t0_vec3.*t0_vec4.*t1_vec3.*t1_vec4.*2.0;
    // 'Calc_beta0_beta1:68' t27 = D_vec3.*D_vec5.*t0_vec3.*t0_vec5.*t1_vec3.*t1_vec5.*2.0;
    // 'Calc_beta0_beta1:69' t28 = D_vec4.*D_vec5.*t0_vec4.*t0_vec5.*t1_vec4.*t1_vec5.*2.0;
    // 'Calc_beta0_beta1:70' t29 = -t19;
    // 'Calc_beta0_beta1:71' t30 = -t20;
    // 'Calc_beta0_beta1:72' t31 = -t21;
    // 'Calc_beta0_beta1:73' t32 = -t22;
    // 'Calc_beta0_beta1:74' t33 = -t23;
    // 'Calc_beta0_beta1:75' t34 = -t24;
    // 'Calc_beta0_beta1:76' t35 = -t25;
    // 'Calc_beta0_beta1:77' t36 = -t26;
    // 'Calc_beta0_beta1:78' t37 = -t27;
    // 'Calc_beta0_beta1:79' t38 = -t28;
    // 'Calc_beta0_beta1:80' t39 = D_vec1.*D_vec2.*t9.*t15.*9.0;
    // 'Calc_beta0_beta1:81' t40 = D_vec1.*D_vec2.*t10.*t14.*9.0;
    // 'Calc_beta0_beta1:82' t41 = D_vec1.*D_vec3.*t9.*t16.*9.0;
    // 'Calc_beta0_beta1:83' t42 = D_vec1.*D_vec3.*t11.*t14.*9.0;
    // 'Calc_beta0_beta1:84' t43 = D_vec1.*D_vec4.*t9.*t17.*9.0;
    // 'Calc_beta0_beta1:85' t44 = D_vec1.*D_vec4.*t12.*t14.*9.0;
    // 'Calc_beta0_beta1:86' t45 = D_vec2.*D_vec3.*t10.*t16.*9.0;
    // 'Calc_beta0_beta1:87' t46 = D_vec2.*D_vec3.*t11.*t15.*9.0;
    // 'Calc_beta0_beta1:88' t47 = D_vec1.*D_vec5.*t9.*t18.*9.0;
    // 'Calc_beta0_beta1:89' t48 = D_vec1.*D_vec5.*t13.*t14.*9.0;
    // 'Calc_beta0_beta1:90' t49 = D_vec2.*D_vec4.*t10.*t17.*9.0;
    // 'Calc_beta0_beta1:91' t50 = D_vec2.*D_vec4.*t12.*t15.*9.0;
    // 'Calc_beta0_beta1:92' t51 = D_vec2.*D_vec5.*t10.*t18.*9.0;
    // 'Calc_beta0_beta1:93' t52 = D_vec2.*D_vec5.*t13.*t15.*9.0;
    // 'Calc_beta0_beta1:94' t53 = D_vec3.*D_vec4.*t11.*t17.*9.0;
    // 'Calc_beta0_beta1:95' t54 = D_vec3.*D_vec4.*t12.*t16.*9.0;
    // 'Calc_beta0_beta1:96' t55 = D_vec3.*D_vec5.*t11.*t18.*9.0;
    // 'Calc_beta0_beta1:97' t56 = D_vec3.*D_vec5.*t13.*t16.*9.0;
    // 'Calc_beta0_beta1:98' t57 = D_vec4.*D_vec5.*t12.*t18.*9.0;
    // 'Calc_beta0_beta1:99' t58 = D_vec4.*D_vec5.*t13.*t17.*9.0;
    // 'Calc_beta0_beta1:100' t59 = t2.*t9.*t14.*8.0;
    // 'Calc_beta0_beta1:101' t60 = t3.*t10.*t15.*8.0;
    // 'Calc_beta0_beta1:102' t61 = t4.*t11.*t16.*8.0;
    // 'Calc_beta0_beta1:103' t62 = t5.*t12.*t17.*8.0;
    // 'Calc_beta0_beta1:104' t63 = t6.*t13.*t18.*8.0;
    // 'Calc_beta0_beta1:105' t64 =
    // t29+t30+t31+t32+t33+t34+t35+t36+t37+t38+t39+t40+t41+t42+t43+t44+t45+t46+t47+t48+t49+t50+t51+t52+t53+t54+t55+t56+t57+t58+t59+t60+t61+t62+t63;
    // 'Calc_beta0_beta1:106' t65 = 1.0./t64;
    t65_tmp = in9_data[0] * in9_data[1];
    b_t65_tmp = in9_data[0] * in9_data[2];
    c_t65_tmp = in9_data[0] * in9_data[3];
    d_t65_tmp = in9_data[1] * in9_data[2];
    e_t65_tmp = in9_data[0] * in9_data[4];
    f_t65_tmp = in9_data[1] * in9_data[3];
    g_t65_tmp = in9_data[1] * in9_data[4];
    h_t65_tmp = in9_data[2] * in9_data[3];
    i_t65_tmp = in9_data[2] * in9_data[4];
    j_t65_tmp = in9_data[3] * in9_data[4];
    t65 =
        1.0 /
        ((((((((((((((((((((((((((((((((((-(t65_tmp * in4[0] * in4[1] * in7[0] * in7[1] * 2.0) +
                                          -(b_t65_tmp * in4[0] * in4[2] * in7[0] * in7[2] * 2.0)) +
                                         -(c_t65_tmp * in4[0] * in4[3] * in7[0] * in7[3] * 2.0)) +
                                        -(d_t65_tmp * in4[1] * in4[2] * in7[1] * in7[2] * 2.0)) +
                                       -(e_t65_tmp * in4[0] * in4[4] * in7[0] * in7[4] * 2.0)) +
                                      -(f_t65_tmp * in4[1] * in4[3] * in7[1] * in7[3] * 2.0)) +
                                     -(g_t65_tmp * in4[1] * in4[4] * in7[1] * in7[4] * 2.0)) +
                                    -(h_t65_tmp * in4[2] * in4[3] * in7[2] * in7[3] * 2.0)) +
                                   -(i_t65_tmp * in4[2] * in4[4] * in7[2] * in7[4] * 2.0)) +
                                  -(j_t65_tmp * in4[3] * in4[4] * in7[3] * in7[4] * 2.0)) +
                                 t65_tmp * t9 * t15 * 9.0) +
                                t65_tmp * t10 * t14 * 9.0) +
                               b_t65_tmp * t9 * t16 * 9.0) +
                              b_t65_tmp * t11 * t14 * 9.0) +
                             c_t65_tmp * t9 * t17 * 9.0) +
                            c_t65_tmp * t12 * t14 * 9.0) +
                           d_t65_tmp * t10 * t16 * 9.0) +
                          d_t65_tmp * t11 * t15 * 9.0) +
                         e_t65_tmp * t9 * t18 * 9.0) +
                        e_t65_tmp * t13 * t14 * 9.0) +
                       f_t65_tmp * t10 * t17 * 9.0) +
                      f_t65_tmp * t12 * t15 * 9.0) +
                     g_t65_tmp * t10 * t18 * 9.0) +
                    g_t65_tmp * t13 * t15 * 9.0) +
                   h_t65_tmp * t11 * t17 * 9.0) +
                  h_t65_tmp * t12 * t16 * 9.0) +
                 i_t65_tmp * t11 * t18 * 9.0) +
                i_t65_tmp * t13 * t16 * 9.0) +
               j_t65_tmp * t12 * t18 * 9.0) +
              j_t65_tmp * t13 * t17 * 9.0) +
             t2 * t9 * t14 * 8.0) +
            t3 * t10 * t15 * 8.0) +
           t4 * t11 * t16 * 8.0) +
          t5 * t12 * t17 * 8.0) +
         t6 * t13 * t18 * 8.0);
    // 'Calc_beta0_beta1:107' et1 =
    // alpha0.*t2.*t9.*t14.*2.8e+1+alpha0.*t3.*t10.*t15.*2.8e+1+alpha0.*t4.*t11.*t16.*2.8e+1+alpha0.*t5.*t12.*t17.*2.8e+1+alpha0.*t6.*t13.*t18.*2.8e+1+p0_vec1.*t2.*t14.*t0_vec1.*4.0e+1+p0_vec2.*t3.*t15.*t0_vec2.*4.0e+1+p0_vec3.*t4.*t16.*t0_vec3.*4.0e+1-p1_vec1.*t2.*t14.*t0_vec1.*4.0e+1+p0_vec4.*t5.*t17.*t0_vec4.*4.0e+1-p1_vec2.*t3.*t15.*t0_vec2.*4.0e+1+p0_vec5.*t6.*t18.*t0_vec5.*4.0e+1-p1_vec3.*t4.*t16.*t0_vec3.*4.0e+1-p1_vec4.*t5.*t17.*t0_vec4.*4.0e+1-p1_vec5.*t6.*t18.*t0_vec5.*4.0e+1+alpha1.*t2.*t0_vec1.*t1_vec1.^3.*1.2e+1+alpha1.*t3.*t0_vec2.*t1_vec2.^3.*1.2e+1+alpha1.*t4.*t0_vec3.*t1_vec3.^3.*1.2e+1+alpha1.*t5.*t0_vec4.*t1_vec4.^3.*1.2e+1+alpha1.*t6.*t0_vec5.*t1_vec5.^3.*1.2e+1+D_vec1.*D_vec2.*alpha0.*t9.*t15.*3.6e+1+D_vec1.*D_vec2.*alpha0.*t10.*t14.*3.6e+1+D_vec1.*D_vec3.*alpha0.*t9.*t16.*3.6e+1+D_vec1.*D_vec3.*alpha0.*t11.*t14.*3.6e+1+D_vec1.*D_vec4.*alpha0.*t9.*t17.*3.6e+1;
    // 'Calc_beta0_beta1:108' et2 =
    // D_vec1.*D_vec4.*alpha0.*t12.*t14.*3.6e+1+D_vec2.*D_vec3.*alpha0.*t10.*t16.*3.6e+1+D_vec2.*D_vec3.*alpha0.*t11.*t15.*3.6e+1+D_vec1.*D_vec5.*alpha0.*t9.*t18.*3.6e+1+D_vec1.*D_vec5.*alpha0.*t13.*t14.*3.6e+1+D_vec2.*D_vec4.*alpha0.*t10.*t17.*3.6e+1+D_vec2.*D_vec4.*alpha0.*t12.*t15.*3.6e+1+D_vec2.*D_vec5.*alpha0.*t10.*t18.*3.6e+1+D_vec2.*D_vec5.*alpha0.*t13.*t15.*3.6e+1+D_vec3.*D_vec4.*alpha0.*t11.*t17.*3.6e+1+D_vec3.*D_vec4.*alpha0.*t12.*t16.*3.6e+1+D_vec3.*D_vec5.*alpha0.*t11.*t18.*3.6e+1+D_vec3.*D_vec5.*alpha0.*t13.*t16.*3.6e+1+D_vec4.*D_vec5.*alpha0.*t12.*t18.*3.6e+1+D_vec4.*D_vec5.*alpha0.*t13.*t17.*3.6e+1+D_vec1.*D_vec2.*p0_vec1.*t15.*t0_vec1.*6.0e+1+D_vec1.*D_vec2.*p0_vec2.*t14.*t0_vec2.*6.0e+1+D_vec1.*D_vec3.*p0_vec1.*t16.*t0_vec1.*6.0e+1+D_vec1.*D_vec3.*p0_vec3.*t14.*t0_vec3.*6.0e+1+D_vec1.*D_vec4.*p0_vec1.*t17.*t0_vec1.*6.0e+1+D_vec2.*D_vec3.*p0_vec2.*t16.*t0_vec2.*6.0e+1+D_vec1.*D_vec5.*p0_vec1.*t18.*t0_vec1.*6.0e+1+D_vec2.*D_vec3.*p0_vec3.*t15.*t0_vec3.*6.0e+1+D_vec1.*D_vec4.*p0_vec4.*t14.*t0_vec4.*6.0e+1+D_vec2.*D_vec4.*p0_vec2.*t17.*t0_vec2.*6.0e+1;
    // 'Calc_beta0_beta1:109' et3 =
    // D_vec2.*D_vec4.*p0_vec4.*t15.*t0_vec4.*6.0e+1+D_vec2.*D_vec5.*p0_vec2.*t18.*t0_vec2.*6.0e+1-D_vec1.*D_vec2.*p1_vec1.*t15.*t0_vec1.*6.0e+1+D_vec1.*D_vec5.*p0_vec5.*t14.*t0_vec5.*6.0e+1+D_vec3.*D_vec4.*p0_vec3.*t17.*t0_vec3.*6.0e+1-D_vec1.*D_vec2.*p1_vec2.*t14.*t0_vec2.*6.0e+1+D_vec3.*D_vec4.*p0_vec4.*t16.*t0_vec4.*6.0e+1-D_vec1.*D_vec3.*p1_vec1.*t16.*t0_vec1.*6.0e+1+D_vec2.*D_vec5.*p0_vec5.*t15.*t0_vec5.*6.0e+1+D_vec3.*D_vec5.*p0_vec3.*t18.*t0_vec3.*6.0e+1-D_vec1.*D_vec3.*p1_vec3.*t14.*t0_vec3.*6.0e+1-D_vec1.*D_vec4.*p1_vec1.*t17.*t0_vec1.*6.0e+1+D_vec3.*D_vec5.*p0_vec5.*t16.*t0_vec5.*6.0e+1-D_vec2.*D_vec3.*p1_vec2.*t16.*t0_vec2.*6.0e+1+D_vec4.*D_vec5.*p0_vec4.*t18.*t0_vec4.*6.0e+1-D_vec1.*D_vec5.*p1_vec1.*t18.*t0_vec1.*6.0e+1-D_vec2.*D_vec3.*p1_vec3.*t15.*t0_vec3.*6.0e+1+D_vec4.*D_vec5.*p0_vec5.*t17.*t0_vec5.*6.0e+1-D_vec1.*D_vec4.*p1_vec4.*t14.*t0_vec4.*6.0e+1-D_vec2.*D_vec4.*p1_vec2.*t17.*t0_vec2.*6.0e+1-D_vec2.*D_vec4.*p1_vec4.*t15.*t0_vec4.*6.0e+1-D_vec2.*D_vec5.*p1_vec2.*t18.*t0_vec2.*6.0e+1-D_vec1.*D_vec5.*p1_vec5.*t14.*t0_vec5.*6.0e+1;
    // 'Calc_beta0_beta1:110' et4 =
    // D_vec3.*D_vec4.*p1_vec3.*t17.*t0_vec3.*-6.0e+1-D_vec3.*D_vec4.*p1_vec4.*t16.*t0_vec4.*6.0e+1-D_vec2.*D_vec5.*p1_vec5.*t15.*t0_vec5.*6.0e+1-D_vec3.*D_vec5.*p1_vec3.*t18.*t0_vec3.*6.0e+1-D_vec3.*D_vec5.*p1_vec5.*t16.*t0_vec5.*6.0e+1-D_vec4.*D_vec5.*p1_vec4.*t18.*t0_vec4.*6.0e+1-D_vec4.*D_vec5.*p1_vec5.*t17.*t0_vec5.*6.0e+1+nk0_vec1.*t2.*t7.*t14.*t0_vec1.*8.0+nk0_vec2.*t3.*t7.*t15.*t0_vec2.*8.0+nk0_vec3.*t4.*t7.*t16.*t0_vec3.*8.0+nk0_vec4.*t5.*t7.*t17.*t0_vec4.*8.0+nk0_vec5.*t6.*t7.*t18.*t0_vec5.*8.0+D_vec1.*D_vec2.*alpha1.*t15.*t0_vec1.*t1_vec1.*1.2e+1+D_vec1.*D_vec2.*alpha1.*t14.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec3.*alpha1.*t16.*t0_vec1.*t1_vec1.*1.2e+1+D_vec1.*D_vec3.*alpha1.*t14.*t0_vec3.*t1_vec3.*1.2e+1+D_vec1.*D_vec4.*alpha1.*t17.*t0_vec1.*t1_vec1.*1.2e+1+D_vec2.*D_vec3.*alpha1.*t16.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec5.*alpha1.*t18.*t0_vec1.*t1_vec1.*1.2e+1+D_vec2.*D_vec3.*alpha1.*t15.*t0_vec3.*t1_vec3.*1.2e+1+D_vec1.*D_vec4.*alpha1.*t14.*t0_vec4.*t1_vec4.*1.2e+1+D_vec2.*D_vec4.*alpha1.*t17.*t0_vec2.*t1_vec2.*1.2e+1;
    // 'Calc_beta0_beta1:111' et5 =
    // D_vec2.*D_vec4.*alpha1.*t15.*t0_vec4.*t1_vec4.*1.2e+1+D_vec2.*D_vec5.*alpha1.*t18.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec5.*alpha1.*t14.*t0_vec5.*t1_vec5.*1.2e+1+D_vec3.*D_vec4.*alpha1.*t17.*t0_vec3.*t1_vec3.*1.2e+1+D_vec3.*D_vec4.*alpha1.*t16.*t0_vec4.*t1_vec4.*1.2e+1+D_vec2.*D_vec5.*alpha1.*t15.*t0_vec5.*t1_vec5.*1.2e+1+D_vec3.*D_vec5.*alpha1.*t18.*t0_vec3.*t1_vec3.*1.2e+1+D_vec3.*D_vec5.*alpha1.*t16.*t0_vec5.*t1_vec5.*1.2e+1+D_vec4.*D_vec5.*alpha1.*t18.*t0_vec4.*t1_vec4.*1.2e+1+D_vec4.*D_vec5.*alpha1.*t17.*t0_vec5.*t1_vec5.*1.2e+1+D_vec1.*D_vec2.*nk0_vec1.*t7.*t15.*t0_vec1.*9.0+D_vec1.*D_vec2.*nk0_vec2.*t7.*t14.*t0_vec2.*9.0+D_vec1.*D_vec3.*nk0_vec1.*t7.*t16.*t0_vec1.*9.0+D_vec1.*D_vec3.*nk0_vec3.*t7.*t14.*t0_vec3.*9.0+D_vec1.*D_vec4.*nk0_vec1.*t7.*t17.*t0_vec1.*9.0+D_vec2.*D_vec3.*nk0_vec2.*t7.*t16.*t0_vec2.*9.0+D_vec1.*D_vec5.*nk0_vec1.*t7.*t18.*t0_vec1.*9.0+D_vec2.*D_vec3.*nk0_vec3.*t7.*t15.*t0_vec3.*9.0+D_vec1.*D_vec4.*nk0_vec4.*t7.*t14.*t0_vec4.*9.0+D_vec2.*D_vec4.*nk0_vec2.*t7.*t17.*t0_vec2.*9.0+D_vec2.*D_vec4.*nk0_vec4.*t7.*t15.*t0_vec4.*9.0+D_vec2.*D_vec5.*nk0_vec2.*t7.*t18.*t0_vec2.*9.0;
    // 'Calc_beta0_beta1:112' et6 =
    // D_vec1.*D_vec5.*nk0_vec5.*t7.*t14.*t0_vec5.*9.0+D_vec3.*D_vec4.*nk0_vec3.*t7.*t17.*t0_vec3.*9.0-D_vec1.*D_vec2.*nk1_vec1.*t8.*t15.*t0_vec1.*3.0+D_vec3.*D_vec4.*nk0_vec4.*t7.*t16.*t0_vec4.*9.0-D_vec1.*D_vec2.*nk1_vec2.*t8.*t14.*t0_vec2.*3.0+D_vec2.*D_vec5.*nk0_vec5.*t7.*t15.*t0_vec5.*9.0+D_vec3.*D_vec5.*nk0_vec3.*t7.*t18.*t0_vec3.*9.0-D_vec1.*D_vec3.*nk1_vec1.*t8.*t16.*t0_vec1.*3.0+D_vec3.*D_vec5.*nk0_vec5.*t7.*t16.*t0_vec5.*9.0-D_vec1.*D_vec3.*nk1_vec3.*t8.*t14.*t0_vec3.*3.0-D_vec1.*D_vec4.*nk1_vec1.*t8.*t17.*t0_vec1.*3.0+D_vec4.*D_vec5.*nk0_vec4.*t7.*t18.*t0_vec4.*9.0-D_vec2.*D_vec3.*nk1_vec2.*t8.*t16.*t0_vec2.*3.0+D_vec4.*D_vec5.*nk0_vec5.*t7.*t17.*t0_vec5.*9.0-D_vec1.*D_vec5.*nk1_vec1.*t8.*t18.*t0_vec1.*3.0-D_vec2.*D_vec3.*nk1_vec3.*t8.*t15.*t0_vec3.*3.0-D_vec1.*D_vec4.*nk1_vec4.*t8.*t14.*t0_vec4.*3.0-D_vec2.*D_vec4.*nk1_vec2.*t8.*t17.*t0_vec2.*3.0-D_vec2.*D_vec4.*nk1_vec4.*t8.*t15.*t0_vec4.*3.0-D_vec2.*D_vec5.*nk1_vec2.*t8.*t18.*t0_vec2.*3.0-D_vec1.*D_vec5.*nk1_vec5.*t8.*t14.*t0_vec5.*3.0-D_vec3.*D_vec4.*nk1_vec3.*t8.*t17.*t0_vec3.*3.0;
    // 'Calc_beta0_beta1:113' et7 =
    // D_vec3.*D_vec4.*nk1_vec4.*t8.*t16.*t0_vec4.*-3.0-D_vec2.*D_vec5.*nk1_vec5.*t8.*t15.*t0_vec5.*3.0-D_vec3.*D_vec5.*nk1_vec3.*t8.*t18.*t0_vec3.*3.0-D_vec3.*D_vec5.*nk1_vec5.*t8.*t16.*t0_vec5.*3.0-D_vec4.*D_vec5.*nk1_vec4.*t8.*t18.*t0_vec4.*3.0-D_vec4.*D_vec5.*nk1_vec5.*t8.*t17.*t0_vec5.*3.0-D_vec1.*D_vec2.*p0_vec1.*t0_vec2.*t1_vec1.*t1_vec2.*2.0e+1-D_vec1.*D_vec2.*p0_vec2.*t0_vec1.*t1_vec1.*t1_vec2.*2.0e+1-D_vec1.*D_vec3.*p0_vec1.*t0_vec3.*t1_vec1.*t1_vec3.*2.0e+1-D_vec1.*D_vec3.*p0_vec3.*t0_vec1.*t1_vec1.*t1_vec3.*2.0e+1-D_vec1.*D_vec4.*p0_vec1.*t0_vec4.*t1_vec1.*t1_vec4.*2.0e+1-D_vec1.*D_vec4.*p0_vec4.*t0_vec1.*t1_vec1.*t1_vec4.*2.0e+1-D_vec2.*D_vec3.*p0_vec2.*t0_vec3.*t1_vec2.*t1_vec3.*2.0e+1-D_vec2.*D_vec3.*p0_vec3.*t0_vec2.*t1_vec2.*t1_vec3.*2.0e+1-D_vec1.*D_vec5.*p0_vec1.*t0_vec5.*t1_vec1.*t1_vec5.*2.0e+1-D_vec1.*D_vec5.*p0_vec5.*t0_vec1.*t1_vec1.*t1_vec5.*2.0e+1-D_vec2.*D_vec4.*p0_vec2.*t0_vec4.*t1_vec2.*t1_vec4.*2.0e+1-D_vec2.*D_vec4.*p0_vec4.*t0_vec2.*t1_vec2.*t1_vec4.*2.0e+1+D_vec1.*D_vec2.*p1_vec1.*t0_vec2.*t1_vec1.*t1_vec2.*2.0e+1+D_vec1.*D_vec2.*p1_vec2.*t0_vec1.*t1_vec1.*t1_vec2.*2.0e+1;
    // 'Calc_beta0_beta1:114' et8 =
    // D_vec2.*D_vec5.*p0_vec2.*t0_vec5.*t1_vec2.*t1_vec5.*-2.0e+1-D_vec2.*D_vec5.*p0_vec5.*t0_vec2.*t1_vec2.*t1_vec5.*2.0e+1-D_vec3.*D_vec4.*p0_vec3.*t0_vec4.*t1_vec3.*t1_vec4.*2.0e+1-D_vec3.*D_vec4.*p0_vec4.*t0_vec3.*t1_vec3.*t1_vec4.*2.0e+1+D_vec1.*D_vec3.*p1_vec1.*t0_vec3.*t1_vec1.*t1_vec3.*2.0e+1+D_vec1.*D_vec3.*p1_vec3.*t0_vec1.*t1_vec1.*t1_vec3.*2.0e+1-D_vec3.*D_vec5.*p0_vec3.*t0_vec5.*t1_vec3.*t1_vec5.*2.0e+1-D_vec3.*D_vec5.*p0_vec5.*t0_vec3.*t1_vec3.*t1_vec5.*2.0e+1+D_vec1.*D_vec4.*p1_vec1.*t0_vec4.*t1_vec1.*t1_vec4.*2.0e+1+D_vec1.*D_vec4.*p1_vec4.*t0_vec1.*t1_vec1.*t1_vec4.*2.0e+1+D_vec2.*D_vec3.*p1_vec2.*t0_vec3.*t1_vec2.*t1_vec3.*2.0e+1+D_vec2.*D_vec3.*p1_vec3.*t0_vec2.*t1_vec2.*t1_vec3.*2.0e+1-D_vec4.*D_vec5.*p0_vec4.*t0_vec5.*t1_vec4.*t1_vec5.*2.0e+1-D_vec4.*D_vec5.*p0_vec5.*t0_vec4.*t1_vec4.*t1_vec5.*2.0e+1+D_vec1.*D_vec5.*p1_vec1.*t0_vec5.*t1_vec1.*t1_vec5.*2.0e+1+D_vec1.*D_vec5.*p1_vec5.*t0_vec1.*t1_vec1.*t1_vec5.*2.0e+1+D_vec2.*D_vec4.*p1_vec2.*t0_vec4.*t1_vec2.*t1_vec4.*2.0e+1+D_vec2.*D_vec4.*p1_vec4.*t0_vec2.*t1_vec2.*t1_vec4.*2.0e+1+D_vec2.*D_vec5.*p1_vec2.*t0_vec5.*t1_vec2.*t1_vec5.*2.0e+1+D_vec2.*D_vec5.*p1_vec5.*t0_vec2.*t1_vec2.*t1_vec5.*2.0e+1+D_vec3.*D_vec4.*p1_vec3.*t0_vec4.*t1_vec3.*t1_vec4.*2.0e+1;
    // 'Calc_beta0_beta1:115' et9 =
    // D_vec3.*D_vec4.*p1_vec4.*t0_vec3.*t1_vec3.*t1_vec4.*2.0e+1+D_vec3.*D_vec5.*p1_vec3.*t0_vec5.*t1_vec3.*t1_vec5.*2.0e+1+D_vec3.*D_vec5.*p1_vec5.*t0_vec3.*t1_vec3.*t1_vec5.*2.0e+1+D_vec4.*D_vec5.*p1_vec4.*t0_vec5.*t1_vec4.*t1_vec5.*2.0e+1+D_vec4.*D_vec5.*p1_vec5.*t0_vec4.*t1_vec4.*t1_vec5.*2.0e+1-D_vec1.*D_vec2.*alpha0.*t0_vec1.*t0_vec2.*t1_vec1.*t1_vec2.*1.6e+1-D_vec1.*D_vec3.*alpha0.*t0_vec1.*t0_vec3.*t1_vec1.*t1_vec3.*1.6e+1-D_vec1.*D_vec4.*alpha0.*t0_vec1.*t0_vec4.*t1_vec1.*t1_vec4.*1.6e+1-D_vec2.*D_vec3.*alpha0.*t0_vec2.*t0_vec3.*t1_vec2.*t1_vec3.*1.6e+1-D_vec1.*D_vec5.*alpha0.*t0_vec1.*t0_vec5.*t1_vec1.*t1_vec5.*1.6e+1-D_vec2.*D_vec4.*alpha0.*t0_vec2.*t0_vec4.*t1_vec2.*t1_vec4.*1.6e+1-D_vec2.*D_vec5.*alpha0.*t0_vec2.*t0_vec5.*t1_vec2.*t1_vec5.*1.6e+1-D_vec3.*D_vec4.*alpha0.*t0_vec3.*t0_vec4.*t1_vec3.*t1_vec4.*1.6e+1-D_vec3.*D_vec5.*alpha0.*t0_vec3.*t0_vec5.*t1_vec3.*t1_vec5.*1.6e+1-D_vec4.*D_vec5.*alpha0.*t0_vec4.*t0_vec5.*t1_vec4.*t1_vec5.*1.6e+1-D_vec1.*D_vec2.*nk0_vec1.*t7.*t0_vec2.*t1_vec1.*t1_vec2-D_vec1.*D_vec2.*nk0_vec2.*t7.*t0_vec1.*t1_vec1.*t1_vec2-D_vec1.*D_vec3.*nk0_vec1.*t7.*t0_vec3.*t1_vec1.*t1_vec3-D_vec1.*D_vec3.*nk0_vec3.*t7.*t0_vec1.*t1_vec1.*t1_vec3;
    // 'Calc_beta0_beta1:116' et10 =
    // -D_vec1.*D_vec4.*nk0_vec1.*t7.*t0_vec4.*t1_vec1.*t1_vec4-D_vec1.*D_vec4.*nk0_vec4.*t7.*t0_vec1.*t1_vec1.*t1_vec4-D_vec2.*D_vec3.*nk0_vec2.*t7.*t0_vec3.*t1_vec2.*t1_vec3-D_vec2.*D_vec3.*nk0_vec3.*t7.*t0_vec2.*t1_vec2.*t1_vec3-D_vec1.*D_vec5.*nk0_vec1.*t7.*t0_vec5.*t1_vec1.*t1_vec5-D_vec1.*D_vec5.*nk0_vec5.*t7.*t0_vec1.*t1_vec1.*t1_vec5-D_vec2.*D_vec4.*nk0_vec2.*t7.*t0_vec4.*t1_vec2.*t1_vec4-D_vec2.*D_vec4.*nk0_vec4.*t7.*t0_vec2.*t1_vec2.*t1_vec4+D_vec1.*D_vec2.*nk1_vec1.*t8.*t0_vec2.*t1_vec1.*t1_vec2.*3.0+D_vec1.*D_vec2.*nk1_vec2.*t8.*t0_vec1.*t1_vec1.*t1_vec2.*3.0-D_vec2.*D_vec5.*nk0_vec2.*t7.*t0_vec5.*t1_vec2.*t1_vec5-D_vec2.*D_vec5.*nk0_vec5.*t7.*t0_vec2.*t1_vec2.*t1_vec5-D_vec3.*D_vec4.*nk0_vec3.*t7.*t0_vec4.*t1_vec3.*t1_vec4-D_vec3.*D_vec4.*nk0_vec4.*t7.*t0_vec3.*t1_vec3.*t1_vec4+D_vec1.*D_vec3.*nk1_vec1.*t8.*t0_vec3.*t1_vec1.*t1_vec3.*3.0+D_vec1.*D_vec3.*nk1_vec3.*t8.*t0_vec1.*t1_vec1.*t1_vec3.*3.0-D_vec3.*D_vec5.*nk0_vec3.*t7.*t0_vec5.*t1_vec3.*t1_vec5-D_vec3.*D_vec5.*nk0_vec5.*t7.*t0_vec3.*t1_vec3.*t1_vec5+D_vec1.*D_vec4.*nk1_vec1.*t8.*t0_vec4.*t1_vec1.*t1_vec4.*3.0+D_vec1.*D_vec4.*nk1_vec4.*t8.*t0_vec1.*t1_vec1.*t1_vec4.*3.0;
    // 'Calc_beta0_beta1:117' et11 =
    // D_vec2.*D_vec3.*nk1_vec2.*t8.*t0_vec3.*t1_vec2.*t1_vec3.*3.0+D_vec2.*D_vec3.*nk1_vec3.*t8.*t0_vec2.*t1_vec2.*t1_vec3.*3.0-D_vec4.*D_vec5.*nk0_vec4.*t7.*t0_vec5.*t1_vec4.*t1_vec5-D_vec4.*D_vec5.*nk0_vec5.*t7.*t0_vec4.*t1_vec4.*t1_vec5+D_vec1.*D_vec5.*nk1_vec1.*t8.*t0_vec5.*t1_vec1.*t1_vec5.*3.0+D_vec1.*D_vec5.*nk1_vec5.*t8.*t0_vec1.*t1_vec1.*t1_vec5.*3.0+D_vec2.*D_vec4.*nk1_vec2.*t8.*t0_vec4.*t1_vec2.*t1_vec4.*3.0+D_vec2.*D_vec4.*nk1_vec4.*t8.*t0_vec2.*t1_vec2.*t1_vec4.*3.0+D_vec2.*D_vec5.*nk1_vec2.*t8.*t0_vec5.*t1_vec2.*t1_vec5.*3.0+D_vec2.*D_vec5.*nk1_vec5.*t8.*t0_vec2.*t1_vec2.*t1_vec5.*3.0+D_vec3.*D_vec4.*nk1_vec3.*t8.*t0_vec4.*t1_vec3.*t1_vec4.*3.0+D_vec3.*D_vec4.*nk1_vec4.*t8.*t0_vec3.*t1_vec3.*t1_vec4.*3.0+D_vec3.*D_vec5.*nk1_vec3.*t8.*t0_vec5.*t1_vec3.*t1_vec5.*3.0+D_vec3.*D_vec5.*nk1_vec5.*t8.*t0_vec3.*t1_vec3.*t1_vec5.*3.0+D_vec4.*D_vec5.*nk1_vec4.*t8.*t0_vec5.*t1_vec4.*t1_vec5.*3.0+D_vec4.*D_vec5.*nk1_vec5.*t8.*t0_vec4.*t1_vec4.*t1_vec5.*3.0;
    // 'Calc_beta0_beta1:118' beta0 = -t65.*(et1+et2+et3+et4+et5+et6+et7+et8+et9+et10+et11);
    beta0_tmp = t65_tmp * alpha0;
    b_beta0_tmp = b_t65_tmp * alpha0;
    c_beta0_tmp = c_t65_tmp * alpha0;
    d_beta0_tmp = d_t65_tmp * alpha0;
    e_beta0_tmp = e_t65_tmp * alpha0;
    f_beta0_tmp = f_t65_tmp * alpha0;
    g_beta0_tmp = g_t65_tmp * alpha0;
    h_beta0_tmp = h_t65_tmp * alpha0;
    i_beta0_tmp = i_t65_tmp * alpha0;
    j_beta0_tmp = j_t65_tmp * alpha0;
    k_beta0_tmp = t65_tmp * alpha1;
    l_beta0_tmp = b_t65_tmp * alpha1;
    m_beta0_tmp = d_t65_tmp * alpha1;
    n_beta0_tmp = c_t65_tmp * alpha1;
    o_beta0_tmp = f_t65_tmp * alpha1;
    p_beta0_tmp = e_t65_tmp * alpha1;
    q_beta0_tmp = h_t65_tmp * alpha1;
    r_beta0_tmp = g_t65_tmp * alpha1;
    s_beta0_tmp = i_t65_tmp * alpha1;
    t_beta0_tmp = j_t65_tmp * alpha1;
    u_beta0_tmp = t65_tmp * in3[0];
    v_beta0_tmp = t65_tmp * in3[1];
    w_beta0_tmp = b_t65_tmp * in3[0];
    x_beta0_tmp = b_t65_tmp * in3[2];
    y_beta0_tmp = c_t65_tmp * in3[0];
    ab_beta0_tmp = c_t65_tmp * in3[3];
    bb_beta0_tmp = d_t65_tmp * in3[1];
    cb_beta0_tmp = d_t65_tmp * in3[2];
    db_beta0_tmp = e_t65_tmp * in3[0];
    eb_beta0_tmp = e_t65_tmp * in3[4];
    fb_beta0_tmp = f_t65_tmp * in3[1];
    gb_beta0_tmp = f_t65_tmp * in3[3];
    hb_beta0_tmp = t65_tmp * in6[0];
    ib_beta0_tmp = t65_tmp * in6[1];
    jb_beta0_tmp = g_t65_tmp * in3[1];
    kb_beta0_tmp = g_t65_tmp * in3[4];
    lb_beta0_tmp = h_t65_tmp * in3[2];
    mb_beta0_tmp = h_t65_tmp * in3[3];
    nb_beta0_tmp = b_t65_tmp * in6[0];
    ob_beta0_tmp = b_t65_tmp * in6[2];
    pb_beta0_tmp = i_t65_tmp * in3[2];
    qb_beta0_tmp = i_t65_tmp * in3[4];
    rb_beta0_tmp = c_t65_tmp * in6[0];
    sb_beta0_tmp = c_t65_tmp * in6[3];
    tb_beta0_tmp = d_t65_tmp * in6[1];
    ub_beta0_tmp = d_t65_tmp * in6[2];
    vb_beta0_tmp = j_t65_tmp * in3[3];
    wb_beta0_tmp = j_t65_tmp * in3[4];
    xb_beta0_tmp = e_t65_tmp * in6[0];
    yb_beta0_tmp = e_t65_tmp * in6[4];
    ac_beta0_tmp = f_t65_tmp * in6[1];
    bc_beta0_tmp = f_t65_tmp * in6[3];
    cc_beta0_tmp = g_t65_tmp * in6[1];
    dc_beta0_tmp = g_t65_tmp * in6[4];
    ec_beta0_tmp = h_t65_tmp * in6[2];
    fc_beta0_tmp = h_t65_tmp * in6[3];
    gc_beta0_tmp = i_t65_tmp * in6[2];
    hc_beta0_tmp = i_t65_tmp * in6[4];
    ic_beta0_tmp = j_t65_tmp * in6[3];
    jc_beta0_tmp = j_t65_tmp * in6[4];
    kc_beta0_tmp = t65_tmp * in5[0] * t7;
    lc_beta0_tmp = t65_tmp * in5[1] * t7;
    mc_beta0_tmp = b_t65_tmp * in5[0] * t7;
    nc_beta0_tmp = b_t65_tmp * in5[2] * t7;
    oc_beta0_tmp = c_t65_tmp * in5[3] * t7;
    pc_beta0_tmp = d_t65_tmp * in5[1] * t7;
    qc_beta0_tmp = d_t65_tmp * in5[2] * t7;
    rc_beta0_tmp = e_t65_tmp * in5[0] * t7;
    sc_beta0_tmp = e_t65_tmp * in5[4] * t7;
    tc_beta0_tmp = f_t65_tmp * in5[1] * t7;
    uc_beta0_tmp = f_t65_tmp * in5[3] * t7;
    vc_beta0_tmp = t65_tmp * in8[0] * t8;
    wc_beta0_tmp = t65_tmp * in8[1] * t8;
    xc_beta0_tmp = g_t65_tmp * in5[1] * t7;
    yc_beta0_tmp = g_t65_tmp * in5[4] * t7;
    ad_beta0_tmp = h_t65_tmp * in5[2] * t7;
    bd_beta0_tmp = h_t65_tmp * in5[3] * t7;
    cd_beta0_tmp = b_t65_tmp * in8[0] * t8;
    dd_beta0_tmp = b_t65_tmp * in8[2] * t8;
    ed_beta0_tmp = i_t65_tmp * in5[2] * t7;
    fd_beta0_tmp = i_t65_tmp * in5[4] * t7;
    gd_beta0_tmp = c_t65_tmp * in8[0] * t8;
    hd_beta0_tmp = c_t65_tmp * in8[3] * t8;
    id_beta0_tmp = d_t65_tmp * in8[1] * t8;
    jd_beta0_tmp = d_t65_tmp * in8[2] * t8;
    kd_beta0_tmp = j_t65_tmp * in5[3] * t7;
    ld_beta0_tmp = j_t65_tmp * in5[4] * t7;
    md_beta0_tmp = e_t65_tmp * in8[0] * t8;
    nd_beta0_tmp = e_t65_tmp * in8[4] * t8;
    od_beta0_tmp = f_t65_tmp * in8[1] * t8;
    pd_beta0_tmp = f_t65_tmp * in8[3] * t8;
    qd_beta0_tmp = g_t65_tmp * in8[1] * t8;
    rd_beta0_tmp = g_t65_tmp * in8[4] * t8;
    sd_beta0_tmp = h_t65_tmp * in8[2] * t8;
    td_beta0_tmp = h_t65_tmp * in8[3] * t8;
    ud_beta0_tmp = i_t65_tmp * in8[2] * t8;
    vd_beta0_tmp = i_t65_tmp * in8[4] * t8;
    wd_beta0_tmp = j_t65_tmp * in8[3] * t8;
    xd_beta0_tmp = j_t65_tmp * in8[4] * t8;
    yd_beta0_tmp = alpha1 * t2;
    ae_beta0_tmp = alpha1 * t3;
    be_beta0_tmp = alpha1 * t4;
    ce_beta0_tmp = alpha1 * t5;
    de_beta0_tmp = alpha1 * t6;
    ee_beta0_tmp = in3[0] * t2;
    fe_beta0_tmp = in3[1] * t3;
    ge_beta0_tmp = in3[2] * t4;
    he_beta0_tmp = in6[0] * t2;
    ie_beta0_tmp = in3[3] * t5;
    je_beta0_tmp = in6[1] * t3;
    ke_beta0_tmp = in3[4] * t6;
    le_beta0_tmp = in6[2] * t4;
    me_beta0_tmp = in6[3] * t5;
    ne_beta0_tmp = in6[4] * t6;
    oe_beta0_tmp = alpha0 * t2;
    pe_beta0_tmp = alpha0 * t3;
    qe_beta0_tmp = alpha0 * t4;
    re_beta0_tmp = alpha0 * t5;
    se_beta0_tmp = alpha0 * t6;
    te_beta0_tmp = beta0_tmp * t10;
    ue_beta0_tmp = beta0_tmp * t9;
    ve_beta0_tmp = b_beta0_tmp * t11;
    we_beta0_tmp = b_beta0_tmp * t9;
    xe_beta0_tmp = c_beta0_tmp * t12;
    ye_beta0_tmp = d_beta0_tmp * t11;
    af_beta0_tmp = e_beta0_tmp * t13;
    bf_beta0_tmp = d_beta0_tmp * t10;
    cf_beta0_tmp = c_beta0_tmp * t9;
    df_beta0_tmp = f_beta0_tmp * t12;
    ef_beta0_tmp = f_beta0_tmp * t10;
    ff_beta0_tmp = g_beta0_tmp * t13;
    gf_beta0_tmp = e_beta0_tmp * t9;
    hf_beta0_tmp = h_beta0_tmp * t12;
    if_beta0_tmp = h_beta0_tmp * t11;
    jf_beta0_tmp = g_beta0_tmp * t10;
    kf_beta0_tmp = i_beta0_tmp * t13;
    lf_beta0_tmp = i_beta0_tmp * t11;
    mf_beta0_tmp = j_beta0_tmp * t13;
    nf_beta0_tmp = j_beta0_tmp * t12;
    of_beta0_tmp = c_t65_tmp * in5[0] * t7;
    pf_beta0_tmp = v_beta0_tmp * in4[0];
    qf_beta0_tmp = x_beta0_tmp * in4[0];
    rf_beta0_tmp = ab_beta0_tmp * in4[0];
    sf_beta0_tmp = cb_beta0_tmp * in4[1];
    tf_beta0_tmp = eb_beta0_tmp * in4[0];
    uf_beta0_tmp = gb_beta0_tmp * in4[1];
    vf_beta0_tmp = ib_beta0_tmp * in4[0];
    wf_beta0_tmp = kb_beta0_tmp * in4[1];
    xf_beta0_tmp = mb_beta0_tmp * in4[2];
    yf_beta0_tmp = ob_beta0_tmp * in4[0];
    ag_beta0_tmp = qb_beta0_tmp * in4[2];
    bg_beta0_tmp = sb_beta0_tmp * in4[0];
    cg_beta0_tmp = ub_beta0_tmp * in4[1];
    dg_beta0_tmp = wb_beta0_tmp * in4[3];
    eg_beta0_tmp = yb_beta0_tmp * in4[0];
    fg_beta0_tmp = bc_beta0_tmp * in4[1];
    gg_beta0_tmp = dc_beta0_tmp * in4[1];
    hg_beta0_tmp = fc_beta0_tmp * in4[2];
    ig_beta0_tmp = hc_beta0_tmp * in4[2];
    jg_beta0_tmp = jc_beta0_tmp * in4[3];
    kg_beta0_tmp = lc_beta0_tmp * in4[0];
    lg_beta0_tmp = nc_beta0_tmp * in4[0];
    mg_beta0_tmp = oc_beta0_tmp * in4[0];
    ng_beta0_tmp = qc_beta0_tmp * in4[1];
    og_beta0_tmp = sc_beta0_tmp * in4[0];
    pg_beta0_tmp = uc_beta0_tmp * in4[1];
    qg_beta0_tmp = wc_beta0_tmp * in4[0];
    rg_beta0_tmp = yc_beta0_tmp * in4[1];
    sg_beta0_tmp = bd_beta0_tmp * in4[2];
    tg_beta0_tmp = dd_beta0_tmp * in4[0];
    ug_beta0_tmp = fd_beta0_tmp * in4[2];
    vg_beta0_tmp = hd_beta0_tmp * in4[0];
    wg_beta0_tmp = jd_beta0_tmp * in4[1];
    xg_beta0_tmp = ld_beta0_tmp * in4[3];
    yg_beta0_tmp = nd_beta0_tmp * in4[0];
    ah_beta0_tmp = pd_beta0_tmp * in4[1];
    bh_beta0_tmp = rd_beta0_tmp * in4[1];
    ch_beta0_tmp = td_beta0_tmp * in4[2];
    dh_beta0_tmp = vd_beta0_tmp * in4[2];
    eh_beta0_tmp = xd_beta0_tmp * in4[3];
    *beta0 =
        -t65 *
        ((((((((((((((((((((((((((((((((((oe_beta0_tmp * t9 * t14 * 28.0 +
                                          pe_beta0_tmp * t10 * t15 * 28.0) +
                                         qe_beta0_tmp * t11 * t16 * 28.0) +
                                        re_beta0_tmp * t12 * t17 * 28.0) +
                                       se_beta0_tmp * t13 * t18 * 28.0) +
                                      ee_beta0_tmp * t14 * in4[0] * 40.0) +
                                     fe_beta0_tmp * t15 * in4[1] * 40.0) +
                                    ge_beta0_tmp * t16 * in4[2] * 40.0) -
                                   he_beta0_tmp * t14 * in4[0] * 40.0) +
                                  ie_beta0_tmp * t17 * in4[3] * 40.0) -
                                 je_beta0_tmp * t15 * in4[1] * 40.0) +
                                ke_beta0_tmp * t18 * in4[4] * 40.0) -
                               le_beta0_tmp * t16 * in4[2] * 40.0) -
                              me_beta0_tmp * t17 * in4[3] * 40.0) -
                             ne_beta0_tmp * t18 * in4[4] * 40.0) +
                            yd_beta0_tmp * in4[0] * std::pow(in7[0], 3.0) * 12.0) +
                           ae_beta0_tmp * in4[1] * std::pow(in7[1], 3.0) * 12.0) +
                          be_beta0_tmp * in4[2] * std::pow(in7[2], 3.0) * 12.0) +
                         ce_beta0_tmp * in4[3] * std::pow(in7[3], 3.0) * 12.0) +
                        de_beta0_tmp * in4[4] * std::pow(in7[4], 3.0) * 12.0) +
                       ue_beta0_tmp * t15 * 36.0) +
                      te_beta0_tmp * t14 * 36.0) +
                     we_beta0_tmp * t16 * 36.0) +
                    ve_beta0_tmp * t14 * 36.0) +
                   cf_beta0_tmp * t17 * 36.0) +
                  ((((((((((((((((((((((((xe_beta0_tmp * t14 * 36.0 + bf_beta0_tmp * t16 * 36.0) +
                                         ye_beta0_tmp * t15 * 36.0) +
                                        gf_beta0_tmp * t18 * 36.0) +
                                       af_beta0_tmp * t14 * 36.0) +
                                      ef_beta0_tmp * t17 * 36.0) +
                                     df_beta0_tmp * t15 * 36.0) +
                                    jf_beta0_tmp * t18 * 36.0) +
                                   ff_beta0_tmp * t15 * 36.0) +
                                  if_beta0_tmp * t17 * 36.0) +
                                 hf_beta0_tmp * t16 * 36.0) +
                                lf_beta0_tmp * t18 * 36.0) +
                               kf_beta0_tmp * t16 * 36.0) +
                              nf_beta0_tmp * t18 * 36.0) +
                             mf_beta0_tmp * t17 * 36.0) +
                            u_beta0_tmp * t15 * in4[0] * 60.0) +
                           v_beta0_tmp * t14 * in4[1] * 60.0) +
                          w_beta0_tmp * t16 * in4[0] * 60.0) +
                         x_beta0_tmp * t14 * in4[2] * 60.0) +
                        y_beta0_tmp * t17 * in4[0] * 60.0) +
                       bb_beta0_tmp * t16 * in4[1] * 60.0) +
                      db_beta0_tmp * t18 * in4[0] * 60.0) +
                     cb_beta0_tmp * t15 * in4[2] * 60.0) +
                    ab_beta0_tmp * t14 * in4[3] * 60.0) +
                   fb_beta0_tmp * t17 * in4[1] * 60.0)) +
                 ((((((((((((((((((((((gb_beta0_tmp * t15 * in4[3] * 60.0 +
                                       jb_beta0_tmp * t18 * in4[1] * 60.0) -
                                      hb_beta0_tmp * t15 * in4[0] * 60.0) +
                                     eb_beta0_tmp * t14 * in4[4] * 60.0) +
                                    lb_beta0_tmp * t17 * in4[2] * 60.0) -
                                   ib_beta0_tmp * t14 * in4[1] * 60.0) +
                                  mb_beta0_tmp * t16 * in4[3] * 60.0) -
                                 nb_beta0_tmp * t16 * in4[0] * 60.0) +
                                kb_beta0_tmp * t15 * in4[4] * 60.0) +
                               pb_beta0_tmp * t18 * in4[2] * 60.0) -
                              ob_beta0_tmp * t14 * in4[2] * 60.0) -
                             rb_beta0_tmp * t17 * in4[0] * 60.0) +
                            qb_beta0_tmp * t16 * in4[4] * 60.0) -
                           tb_beta0_tmp * t16 * in4[1] * 60.0) +
                          vb_beta0_tmp * t18 * in4[3] * 60.0) -
                         xb_beta0_tmp * t18 * in4[0] * 60.0) -
                        ub_beta0_tmp * t15 * in4[2] * 60.0) +
                       wb_beta0_tmp * t17 * in4[4] * 60.0) -
                      sb_beta0_tmp * t14 * in4[3] * 60.0) -
                     ac_beta0_tmp * t17 * in4[1] * 60.0) -
                    bc_beta0_tmp * t15 * in4[3] * 60.0) -
                   cc_beta0_tmp * t18 * in4[1] * 60.0) -
                  yb_beta0_tmp * t14 * in4[4] * 60.0)) +
                (((((((((((((((((((((ec_beta0_tmp * t17 * in4[2] * -60.0 -
                                     fc_beta0_tmp * t16 * in4[3] * 60.0) -
                                    dc_beta0_tmp * t15 * in4[4] * 60.0) -
                                   gc_beta0_tmp * t18 * in4[2] * 60.0) -
                                  hc_beta0_tmp * t16 * in4[4] * 60.0) -
                                 ic_beta0_tmp * t18 * in4[3] * 60.0) -
                                jc_beta0_tmp * t17 * in4[4] * 60.0) +
                               in5[0] * t2 * t7 * t14 * in4[0] * 8.0) +
                              in5[1] * t3 * t7 * t15 * in4[1] * 8.0) +
                             in5[2] * t4 * t7 * t16 * in4[2] * 8.0) +
                            in5[3] * t5 * t7 * t17 * in4[3] * 8.0) +
                           in5[4] * t6 * t7 * t18 * in4[4] * 8.0) +
                          k_beta0_tmp * t15 * in4[0] * in7[0] * 12.0) +
                         k_beta0_tmp * t14 * in4[1] * in7[1] * 12.0) +
                        l_beta0_tmp * t16 * in4[0] * in7[0] * 12.0) +
                       l_beta0_tmp * t14 * in4[2] * in7[2] * 12.0) +
                      n_beta0_tmp * t17 * in4[0] * in7[0] * 12.0) +
                     m_beta0_tmp * t16 * in4[1] * in7[1] * 12.0) +
                    p_beta0_tmp * t18 * in4[0] * in7[0] * 12.0) +
                   m_beta0_tmp * t15 * in4[2] * in7[2] * 12.0) +
                  n_beta0_tmp * t14 * in4[3] * in7[3] * 12.0) +
                 o_beta0_tmp * t17 * in4[1] * in7[1] * 12.0)) +
               (((((((((((((((((((((o_beta0_tmp * t15 * in4[3] * in7[3] * 12.0 +
                                    r_beta0_tmp * t18 * in4[1] * in7[1] * 12.0) +
                                   p_beta0_tmp * t14 * in4[4] * in7[4] * 12.0) +
                                  q_beta0_tmp * t17 * in4[2] * in7[2] * 12.0) +
                                 q_beta0_tmp * t16 * in4[3] * in7[3] * 12.0) +
                                r_beta0_tmp * t15 * in4[4] * in7[4] * 12.0) +
                               s_beta0_tmp * t18 * in4[2] * in7[2] * 12.0) +
                              s_beta0_tmp * t16 * in4[4] * in7[4] * 12.0) +
                             t_beta0_tmp * t18 * in4[3] * in7[3] * 12.0) +
                            t_beta0_tmp * t17 * in4[4] * in7[4] * 12.0) +
                           kc_beta0_tmp * t15 * in4[0] * 9.0) +
                          lc_beta0_tmp * t14 * in4[1] * 9.0) +
                         mc_beta0_tmp * t16 * in4[0] * 9.0) +
                        nc_beta0_tmp * t14 * in4[2] * 9.0) +
                       of_beta0_tmp * t17 * in4[0] * 9.0) +
                      pc_beta0_tmp * t16 * in4[1] * 9.0) +
                     rc_beta0_tmp * t18 * in4[0] * 9.0) +
                    qc_beta0_tmp * t15 * in4[2] * 9.0) +
                   oc_beta0_tmp * t14 * in4[3] * 9.0) +
                  tc_beta0_tmp * t17 * in4[1] * 9.0) +
                 uc_beta0_tmp * t15 * in4[3] * 9.0) +
                xc_beta0_tmp * t18 * in4[1] * 9.0)) +
              (((((((((((((((((((((sc_beta0_tmp * t14 * in4[4] * 9.0 +
                                   ad_beta0_tmp * t17 * in4[2] * 9.0) -
                                  vc_beta0_tmp * t15 * in4[0] * 3.0) +
                                 bd_beta0_tmp * t16 * in4[3] * 9.0) -
                                wc_beta0_tmp * t14 * in4[1] * 3.0) +
                               yc_beta0_tmp * t15 * in4[4] * 9.0) +
                              ed_beta0_tmp * t18 * in4[2] * 9.0) -
                             cd_beta0_tmp * t16 * in4[0] * 3.0) +
                            fd_beta0_tmp * t16 * in4[4] * 9.0) -
                           dd_beta0_tmp * t14 * in4[2] * 3.0) -
                          gd_beta0_tmp * t17 * in4[0] * 3.0) +
                         kd_beta0_tmp * t18 * in4[3] * 9.0) -
                        id_beta0_tmp * t16 * in4[1] * 3.0) +
                       ld_beta0_tmp * t17 * in4[4] * 9.0) -
                      md_beta0_tmp * t18 * in4[0] * 3.0) -
                     jd_beta0_tmp * t15 * in4[2] * 3.0) -
                    hd_beta0_tmp * t14 * in4[3] * 3.0) -
                   od_beta0_tmp * t17 * in4[1] * 3.0) -
                  pd_beta0_tmp * t15 * in4[3] * 3.0) -
                 qd_beta0_tmp * t18 * in4[1] * 3.0) -
                nd_beta0_tmp * t14 * in4[4] * 3.0) -
               sd_beta0_tmp * t17 * in4[2] * 3.0)) +
             (((((((((((((((((((td_beta0_tmp * t16 * in4[3] * -3.0 -
                                rd_beta0_tmp * t15 * in4[4] * 3.0) -
                               ud_beta0_tmp * t18 * in4[2] * 3.0) -
                              vd_beta0_tmp * t16 * in4[4] * 3.0) -
                             wd_beta0_tmp * t18 * in4[3] * 3.0) -
                            xd_beta0_tmp * t17 * in4[4] * 3.0) -
                           u_beta0_tmp * in4[1] * in7[0] * in7[1] * 20.0) -
                          pf_beta0_tmp * in7[0] * in7[1] * 20.0) -
                         w_beta0_tmp * in4[2] * in7[0] * in7[2] * 20.0) -
                        qf_beta0_tmp * in7[0] * in7[2] * 20.0) -
                       y_beta0_tmp * in4[3] * in7[0] * in7[3] * 20.0) -
                      rf_beta0_tmp * in7[0] * in7[3] * 20.0) -
                     bb_beta0_tmp * in4[2] * in7[1] * in7[2] * 20.0) -
                    sf_beta0_tmp * in7[1] * in7[2] * 20.0) -
                   db_beta0_tmp * in4[4] * in7[0] * in7[4] * 20.0) -
                  tf_beta0_tmp * in7[0] * in7[4] * 20.0) -
                 fb_beta0_tmp * in4[3] * in7[1] * in7[3] * 20.0) -
                uf_beta0_tmp * in7[1] * in7[3] * 20.0) +
               hb_beta0_tmp * in4[1] * in7[0] * in7[1] * 20.0) +
              vf_beta0_tmp * in7[0] * in7[1] * 20.0)) +
            ((((((((((((((((((((jb_beta0_tmp * in4[4] * in7[1] * in7[4] * -20.0 -
                                wf_beta0_tmp * in7[1] * in7[4] * 20.0) -
                               lb_beta0_tmp * in4[3] * in7[2] * in7[3] * 20.0) -
                              xf_beta0_tmp * in7[2] * in7[3] * 20.0) +
                             nb_beta0_tmp * in4[2] * in7[0] * in7[2] * 20.0) +
                            yf_beta0_tmp * in7[0] * in7[2] * 20.0) -
                           pb_beta0_tmp * in4[4] * in7[2] * in7[4] * 20.0) -
                          ag_beta0_tmp * in7[2] * in7[4] * 20.0) +
                         rb_beta0_tmp * in4[3] * in7[0] * in7[3] * 20.0) +
                        bg_beta0_tmp * in7[0] * in7[3] * 20.0) +
                       tb_beta0_tmp * in4[2] * in7[1] * in7[2] * 20.0) +
                      cg_beta0_tmp * in7[1] * in7[2] * 20.0) -
                     vb_beta0_tmp * in4[4] * in7[3] * in7[4] * 20.0) -
                    dg_beta0_tmp * in7[3] * in7[4] * 20.0) +
                   xb_beta0_tmp * in4[4] * in7[0] * in7[4] * 20.0) +
                  eg_beta0_tmp * in7[0] * in7[4] * 20.0) +
                 ac_beta0_tmp * in4[3] * in7[1] * in7[3] * 20.0) +
                fg_beta0_tmp * in7[1] * in7[3] * 20.0) +
               cc_beta0_tmp * in4[4] * in7[1] * in7[4] * 20.0) +
              gg_beta0_tmp * in7[1] * in7[4] * 20.0) +
             ec_beta0_tmp * in4[3] * in7[2] * in7[3] * 20.0)) +
           ((((((((((((((((((hg_beta0_tmp * in7[2] * in7[3] * 20.0 +
                             gc_beta0_tmp * in4[4] * in7[2] * in7[4] * 20.0) +
                            ig_beta0_tmp * in7[2] * in7[4] * 20.0) +
                           ic_beta0_tmp * in4[4] * in7[3] * in7[4] * 20.0) +
                          jg_beta0_tmp * in7[3] * in7[4] * 20.0) -
                         beta0_tmp * in4[0] * in4[1] * in7[0] * in7[1] * 16.0) -
                        b_beta0_tmp * in4[0] * in4[2] * in7[0] * in7[2] * 16.0) -
                       c_beta0_tmp * in4[0] * in4[3] * in7[0] * in7[3] * 16.0) -
                      d_beta0_tmp * in4[1] * in4[2] * in7[1] * in7[2] * 16.0) -
                     e_beta0_tmp * in4[0] * in4[4] * in7[0] * in7[4] * 16.0) -
                    f_beta0_tmp * in4[1] * in4[3] * in7[1] * in7[3] * 16.0) -
                   g_beta0_tmp * in4[1] * in4[4] * in7[1] * in7[4] * 16.0) -
                  h_beta0_tmp * in4[2] * in4[3] * in7[2] * in7[3] * 16.0) -
                 i_beta0_tmp * in4[2] * in4[4] * in7[2] * in7[4] * 16.0) -
                j_beta0_tmp * in4[3] * in4[4] * in7[3] * in7[4] * 16.0) -
               kc_beta0_tmp * in4[1] * in7[0] * in7[1]) -
              kg_beta0_tmp * in7[0] * in7[1]) -
             mc_beta0_tmp * in4[2] * in7[0] * in7[2]) -
            lg_beta0_tmp * in7[0] * in7[2])) +
          (((((((((((((((((((-in9_data[0] * in9_data[3] * in5[0] * t7 * in4[3] * in7[0] * in7[3] -
                             mg_beta0_tmp * in7[0] * in7[3]) -
                            pc_beta0_tmp * in4[2] * in7[1] * in7[2]) -
                           ng_beta0_tmp * in7[1] * in7[2]) -
                          rc_beta0_tmp * in4[4] * in7[0] * in7[4]) -
                         og_beta0_tmp * in7[0] * in7[4]) -
                        tc_beta0_tmp * in4[3] * in7[1] * in7[3]) -
                       pg_beta0_tmp * in7[1] * in7[3]) +
                      vc_beta0_tmp * in4[1] * in7[0] * in7[1] * 3.0) +
                     qg_beta0_tmp * in7[0] * in7[1] * 3.0) -
                    xc_beta0_tmp * in4[4] * in7[1] * in7[4]) -
                   rg_beta0_tmp * in7[1] * in7[4]) -
                  ad_beta0_tmp * in4[3] * in7[2] * in7[3]) -
                 sg_beta0_tmp * in7[2] * in7[3]) +
                cd_beta0_tmp * in4[2] * in7[0] * in7[2] * 3.0) +
               tg_beta0_tmp * in7[0] * in7[2] * 3.0) -
              ed_beta0_tmp * in4[4] * in7[2] * in7[4]) -
             ug_beta0_tmp * in7[2] * in7[4]) +
            gd_beta0_tmp * in4[3] * in7[0] * in7[3] * 3.0) +
           vg_beta0_tmp * in7[0] * in7[3] * 3.0)) +
         (((((((((((((((id_beta0_tmp * in4[2] * in7[1] * in7[2] * 3.0 +
                        wg_beta0_tmp * in7[1] * in7[2] * 3.0) -
                       kd_beta0_tmp * in4[4] * in7[3] * in7[4]) -
                      xg_beta0_tmp * in7[3] * in7[4]) +
                     md_beta0_tmp * in4[4] * in7[0] * in7[4] * 3.0) +
                    yg_beta0_tmp * in7[0] * in7[4] * 3.0) +
                   od_beta0_tmp * in4[3] * in7[1] * in7[3] * 3.0) +
                  ah_beta0_tmp * in7[1] * in7[3] * 3.0) +
                 qd_beta0_tmp * in4[4] * in7[1] * in7[4] * 3.0) +
                bh_beta0_tmp * in7[1] * in7[4] * 3.0) +
               sd_beta0_tmp * in4[3] * in7[2] * in7[3] * 3.0) +
              ch_beta0_tmp * in7[2] * in7[3] * 3.0) +
             ud_beta0_tmp * in4[4] * in7[2] * in7[4] * 3.0) +
            dh_beta0_tmp * in7[2] * in7[4] * 3.0) +
           wd_beta0_tmp * in4[4] * in7[3] * in7[4] * 3.0) +
          eh_beta0_tmp * in7[3] * in7[4] * 3.0));
    // 'Calc_beta0_beta1:119' if nargout > 1
    // 'Calc_beta0_beta1:120' et12 =
    // alpha1.*t2.*t9.*t14.*2.8e+1+alpha1.*t3.*t10.*t15.*2.8e+1+alpha1.*t4.*t11.*t16.*2.8e+1+alpha1.*t5.*t12.*t17.*2.8e+1+alpha1.*t6.*t13.*t18.*2.8e+1+p0_vec1.*t2.*t9.*t1_vec1.*4.0e+1+p0_vec2.*t3.*t10.*t1_vec2.*4.0e+1+p0_vec3.*t4.*t11.*t1_vec3.*4.0e+1-p1_vec1.*t2.*t9.*t1_vec1.*4.0e+1+p0_vec4.*t5.*t12.*t1_vec4.*4.0e+1-p1_vec2.*t3.*t10.*t1_vec2.*4.0e+1+p0_vec5.*t6.*t13.*t1_vec5.*4.0e+1-p1_vec3.*t4.*t11.*t1_vec3.*4.0e+1-p1_vec4.*t5.*t12.*t1_vec4.*4.0e+1-p1_vec5.*t6.*t13.*t1_vec5.*4.0e+1+alpha0.*t2.*t0_vec1.^3.*t1_vec1.*1.2e+1+alpha0.*t3.*t0_vec2.^3.*t1_vec2.*1.2e+1+alpha0.*t4.*t0_vec3.^3.*t1_vec3.*1.2e+1+alpha0.*t5.*t0_vec4.^3.*t1_vec4.*1.2e+1+alpha0.*t6.*t0_vec5.^3.*t1_vec5.*1.2e+1+D_vec1.*D_vec2.*alpha1.*t9.*t15.*3.6e+1+D_vec1.*D_vec2.*alpha1.*t10.*t14.*3.6e+1+D_vec1.*D_vec3.*alpha1.*t9.*t16.*3.6e+1+D_vec1.*D_vec3.*alpha1.*t11.*t14.*3.6e+1+D_vec1.*D_vec4.*alpha1.*t9.*t17.*3.6e+1;
    // 'Calc_beta0_beta1:121' et13 =
    // D_vec1.*D_vec4.*alpha1.*t12.*t14.*3.6e+1+D_vec2.*D_vec3.*alpha1.*t10.*t16.*3.6e+1+D_vec2.*D_vec3.*alpha1.*t11.*t15.*3.6e+1+D_vec1.*D_vec5.*alpha1.*t9.*t18.*3.6e+1+D_vec1.*D_vec5.*alpha1.*t13.*t14.*3.6e+1+D_vec2.*D_vec4.*alpha1.*t10.*t17.*3.6e+1+D_vec2.*D_vec4.*alpha1.*t12.*t15.*3.6e+1+D_vec2.*D_vec5.*alpha1.*t10.*t18.*3.6e+1+D_vec2.*D_vec5.*alpha1.*t13.*t15.*3.6e+1+D_vec3.*D_vec4.*alpha1.*t11.*t17.*3.6e+1+D_vec3.*D_vec4.*alpha1.*t12.*t16.*3.6e+1+D_vec3.*D_vec5.*alpha1.*t11.*t18.*3.6e+1+D_vec3.*D_vec5.*alpha1.*t13.*t16.*3.6e+1+D_vec4.*D_vec5.*alpha1.*t12.*t18.*3.6e+1+D_vec4.*D_vec5.*alpha1.*t13.*t17.*3.6e+1+D_vec1.*D_vec2.*p0_vec1.*t10.*t1_vec1.*6.0e+1+D_vec1.*D_vec2.*p0_vec2.*t9.*t1_vec2.*6.0e+1+D_vec1.*D_vec3.*p0_vec1.*t11.*t1_vec1.*6.0e+1+D_vec1.*D_vec3.*p0_vec3.*t9.*t1_vec3.*6.0e+1+D_vec1.*D_vec4.*p0_vec1.*t12.*t1_vec1.*6.0e+1+D_vec2.*D_vec3.*p0_vec2.*t11.*t1_vec2.*6.0e+1+D_vec1.*D_vec5.*p0_vec1.*t13.*t1_vec1.*6.0e+1+D_vec2.*D_vec3.*p0_vec3.*t10.*t1_vec3.*6.0e+1+D_vec1.*D_vec4.*p0_vec4.*t9.*t1_vec4.*6.0e+1+D_vec2.*D_vec4.*p0_vec2.*t12.*t1_vec2.*6.0e+1;
    // 'Calc_beta0_beta1:122' et14 =
    // D_vec2.*D_vec4.*p0_vec4.*t10.*t1_vec4.*6.0e+1+D_vec2.*D_vec5.*p0_vec2.*t13.*t1_vec2.*6.0e+1-D_vec1.*D_vec2.*p1_vec1.*t10.*t1_vec1.*6.0e+1+D_vec1.*D_vec5.*p0_vec5.*t9.*t1_vec5.*6.0e+1+D_vec3.*D_vec4.*p0_vec3.*t12.*t1_vec3.*6.0e+1-D_vec1.*D_vec2.*p1_vec2.*t9.*t1_vec2.*6.0e+1+D_vec3.*D_vec4.*p0_vec4.*t11.*t1_vec4.*6.0e+1-D_vec1.*D_vec3.*p1_vec1.*t11.*t1_vec1.*6.0e+1+D_vec2.*D_vec5.*p0_vec5.*t10.*t1_vec5.*6.0e+1+D_vec3.*D_vec5.*p0_vec3.*t13.*t1_vec3.*6.0e+1-D_vec1.*D_vec3.*p1_vec3.*t9.*t1_vec3.*6.0e+1-D_vec1.*D_vec4.*p1_vec1.*t12.*t1_vec1.*6.0e+1+D_vec3.*D_vec5.*p0_vec5.*t11.*t1_vec5.*6.0e+1-D_vec2.*D_vec3.*p1_vec2.*t11.*t1_vec2.*6.0e+1+D_vec4.*D_vec5.*p0_vec4.*t13.*t1_vec4.*6.0e+1-D_vec1.*D_vec5.*p1_vec1.*t13.*t1_vec1.*6.0e+1-D_vec2.*D_vec3.*p1_vec3.*t10.*t1_vec3.*6.0e+1+D_vec4.*D_vec5.*p0_vec5.*t12.*t1_vec5.*6.0e+1-D_vec1.*D_vec4.*p1_vec4.*t9.*t1_vec4.*6.0e+1-D_vec2.*D_vec4.*p1_vec2.*t12.*t1_vec2.*6.0e+1-D_vec2.*D_vec4.*p1_vec4.*t10.*t1_vec4.*6.0e+1-D_vec2.*D_vec5.*p1_vec2.*t13.*t1_vec2.*6.0e+1-D_vec1.*D_vec5.*p1_vec5.*t9.*t1_vec5.*6.0e+1;
    // 'Calc_beta0_beta1:123' et15 =
    // D_vec3.*D_vec4.*p1_vec3.*t12.*t1_vec3.*-6.0e+1-D_vec3.*D_vec4.*p1_vec4.*t11.*t1_vec4.*6.0e+1-D_vec2.*D_vec5.*p1_vec5.*t10.*t1_vec5.*6.0e+1-D_vec3.*D_vec5.*p1_vec3.*t13.*t1_vec3.*6.0e+1-D_vec3.*D_vec5.*p1_vec5.*t11.*t1_vec5.*6.0e+1-D_vec4.*D_vec5.*p1_vec4.*t13.*t1_vec4.*6.0e+1-D_vec4.*D_vec5.*p1_vec5.*t12.*t1_vec5.*6.0e+1-nk1_vec1.*t2.*t8.*t9.*t1_vec1.*8.0-nk1_vec2.*t3.*t8.*t10.*t1_vec2.*8.0-nk1_vec3.*t4.*t8.*t11.*t1_vec3.*8.0-nk1_vec4.*t5.*t8.*t12.*t1_vec4.*8.0-nk1_vec5.*t6.*t8.*t13.*t1_vec5.*8.0+D_vec1.*D_vec2.*alpha0.*t10.*t0_vec1.*t1_vec1.*1.2e+1+D_vec1.*D_vec2.*alpha0.*t9.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec3.*alpha0.*t11.*t0_vec1.*t1_vec1.*1.2e+1+D_vec1.*D_vec3.*alpha0.*t9.*t0_vec3.*t1_vec3.*1.2e+1+D_vec1.*D_vec4.*alpha0.*t12.*t0_vec1.*t1_vec1.*1.2e+1+D_vec2.*D_vec3.*alpha0.*t11.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec5.*alpha0.*t13.*t0_vec1.*t1_vec1.*1.2e+1+D_vec2.*D_vec3.*alpha0.*t10.*t0_vec3.*t1_vec3.*1.2e+1+D_vec1.*D_vec4.*alpha0.*t9.*t0_vec4.*t1_vec4.*1.2e+1+D_vec2.*D_vec4.*alpha0.*t12.*t0_vec2.*t1_vec2.*1.2e+1;
    // 'Calc_beta0_beta1:124' et16 =
    // D_vec2.*D_vec4.*alpha0.*t10.*t0_vec4.*t1_vec4.*1.2e+1+D_vec2.*D_vec5.*alpha0.*t13.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec5.*alpha0.*t9.*t0_vec5.*t1_vec5.*1.2e+1+D_vec3.*D_vec4.*alpha0.*t12.*t0_vec3.*t1_vec3.*1.2e+1+D_vec3.*D_vec4.*alpha0.*t11.*t0_vec4.*t1_vec4.*1.2e+1+D_vec2.*D_vec5.*alpha0.*t10.*t0_vec5.*t1_vec5.*1.2e+1+D_vec3.*D_vec5.*alpha0.*t13.*t0_vec3.*t1_vec3.*1.2e+1+D_vec3.*D_vec5.*alpha0.*t11.*t0_vec5.*t1_vec5.*1.2e+1+D_vec4.*D_vec5.*alpha0.*t13.*t0_vec4.*t1_vec4.*1.2e+1+D_vec4.*D_vec5.*alpha0.*t12.*t0_vec5.*t1_vec5.*1.2e+1+D_vec1.*D_vec2.*nk0_vec1.*t7.*t10.*t1_vec1.*3.0+D_vec1.*D_vec2.*nk0_vec2.*t7.*t9.*t1_vec2.*3.0+D_vec1.*D_vec3.*nk0_vec1.*t7.*t11.*t1_vec1.*3.0+D_vec1.*D_vec3.*nk0_vec3.*t7.*t9.*t1_vec3.*3.0+D_vec1.*D_vec4.*nk0_vec1.*t7.*t12.*t1_vec1.*3.0+D_vec2.*D_vec3.*nk0_vec2.*t7.*t11.*t1_vec2.*3.0+D_vec1.*D_vec5.*nk0_vec1.*t7.*t13.*t1_vec1.*3.0+D_vec2.*D_vec3.*nk0_vec3.*t7.*t10.*t1_vec3.*3.0+D_vec1.*D_vec4.*nk0_vec4.*t7.*t9.*t1_vec4.*3.0+D_vec2.*D_vec4.*nk0_vec2.*t7.*t12.*t1_vec2.*3.0+D_vec2.*D_vec4.*nk0_vec4.*t7.*t10.*t1_vec4.*3.0+D_vec2.*D_vec5.*nk0_vec2.*t7.*t13.*t1_vec2.*3.0+D_vec1.*D_vec5.*nk0_vec5.*t7.*t9.*t1_vec5.*3.0;
    // 'Calc_beta0_beta1:125' et17 =
    // D_vec3.*D_vec4.*nk0_vec3.*t7.*t12.*t1_vec3.*3.0-D_vec1.*D_vec2.*nk1_vec1.*t8.*t10.*t1_vec1.*9.0+D_vec3.*D_vec4.*nk0_vec4.*t7.*t11.*t1_vec4.*3.0-D_vec1.*D_vec2.*nk1_vec2.*t8.*t9.*t1_vec2.*9.0+D_vec2.*D_vec5.*nk0_vec5.*t7.*t10.*t1_vec5.*3.0+D_vec3.*D_vec5.*nk0_vec3.*t7.*t13.*t1_vec3.*3.0-D_vec1.*D_vec3.*nk1_vec1.*t8.*t11.*t1_vec1.*9.0+D_vec3.*D_vec5.*nk0_vec5.*t7.*t11.*t1_vec5.*3.0-D_vec1.*D_vec3.*nk1_vec3.*t8.*t9.*t1_vec3.*9.0-D_vec1.*D_vec4.*nk1_vec1.*t8.*t12.*t1_vec1.*9.0+D_vec4.*D_vec5.*nk0_vec4.*t7.*t13.*t1_vec4.*3.0-D_vec2.*D_vec3.*nk1_vec2.*t8.*t11.*t1_vec2.*9.0+D_vec4.*D_vec5.*nk0_vec5.*t7.*t12.*t1_vec5.*3.0-D_vec1.*D_vec5.*nk1_vec1.*t8.*t13.*t1_vec1.*9.0-D_vec2.*D_vec3.*nk1_vec3.*t8.*t10.*t1_vec3.*9.0-D_vec1.*D_vec4.*nk1_vec4.*t8.*t9.*t1_vec4.*9.0-D_vec2.*D_vec4.*nk1_vec2.*t8.*t12.*t1_vec2.*9.0-D_vec2.*D_vec4.*nk1_vec4.*t8.*t10.*t1_vec4.*9.0-D_vec2.*D_vec5.*nk1_vec2.*t8.*t13.*t1_vec2.*9.0-D_vec1.*D_vec5.*nk1_vec5.*t8.*t9.*t1_vec5.*9.0-D_vec3.*D_vec4.*nk1_vec3.*t8.*t12.*t1_vec3.*9.0;
    // 'Calc_beta0_beta1:126' et18 =
    // D_vec3.*D_vec4.*nk1_vec4.*t8.*t11.*t1_vec4.*-9.0-D_vec2.*D_vec5.*nk1_vec5.*t8.*t10.*t1_vec5.*9.0-D_vec3.*D_vec5.*nk1_vec3.*t8.*t13.*t1_vec3.*9.0-D_vec3.*D_vec5.*nk1_vec5.*t8.*t11.*t1_vec5.*9.0-D_vec4.*D_vec5.*nk1_vec4.*t8.*t13.*t1_vec4.*9.0-D_vec4.*D_vec5.*nk1_vec5.*t8.*t12.*t1_vec5.*9.0-D_vec1.*D_vec2.*p0_vec1.*t0_vec1.*t0_vec2.*t1_vec2.*2.0e+1-D_vec1.*D_vec2.*p0_vec2.*t0_vec1.*t0_vec2.*t1_vec1.*2.0e+1-D_vec1.*D_vec3.*p0_vec1.*t0_vec1.*t0_vec3.*t1_vec3.*2.0e+1-D_vec1.*D_vec3.*p0_vec3.*t0_vec1.*t0_vec3.*t1_vec1.*2.0e+1-D_vec1.*D_vec4.*p0_vec1.*t0_vec1.*t0_vec4.*t1_vec4.*2.0e+1-D_vec1.*D_vec4.*p0_vec4.*t0_vec1.*t0_vec4.*t1_vec1.*2.0e+1-D_vec2.*D_vec3.*p0_vec2.*t0_vec2.*t0_vec3.*t1_vec3.*2.0e+1-D_vec2.*D_vec3.*p0_vec3.*t0_vec2.*t0_vec3.*t1_vec2.*2.0e+1-D_vec1.*D_vec5.*p0_vec1.*t0_vec1.*t0_vec5.*t1_vec5.*2.0e+1-D_vec1.*D_vec5.*p0_vec5.*t0_vec1.*t0_vec5.*t1_vec1.*2.0e+1-D_vec2.*D_vec4.*p0_vec2.*t0_vec2.*t0_vec4.*t1_vec4.*2.0e+1-D_vec2.*D_vec4.*p0_vec4.*t0_vec2.*t0_vec4.*t1_vec2.*2.0e+1+D_vec1.*D_vec2.*p1_vec1.*t0_vec1.*t0_vec2.*t1_vec2.*2.0e+1+D_vec1.*D_vec2.*p1_vec2.*t0_vec1.*t0_vec2.*t1_vec1.*2.0e+1;
    // 'Calc_beta0_beta1:127' et19 =
    // D_vec2.*D_vec5.*p0_vec2.*t0_vec2.*t0_vec5.*t1_vec5.*-2.0e+1-D_vec2.*D_vec5.*p0_vec5.*t0_vec2.*t0_vec5.*t1_vec2.*2.0e+1-D_vec3.*D_vec4.*p0_vec3.*t0_vec3.*t0_vec4.*t1_vec4.*2.0e+1-D_vec3.*D_vec4.*p0_vec4.*t0_vec3.*t0_vec4.*t1_vec3.*2.0e+1+D_vec1.*D_vec3.*p1_vec1.*t0_vec1.*t0_vec3.*t1_vec3.*2.0e+1+D_vec1.*D_vec3.*p1_vec3.*t0_vec1.*t0_vec3.*t1_vec1.*2.0e+1-D_vec3.*D_vec5.*p0_vec3.*t0_vec3.*t0_vec5.*t1_vec5.*2.0e+1-D_vec3.*D_vec5.*p0_vec5.*t0_vec3.*t0_vec5.*t1_vec3.*2.0e+1+D_vec1.*D_vec4.*p1_vec1.*t0_vec1.*t0_vec4.*t1_vec4.*2.0e+1+D_vec1.*D_vec4.*p1_vec4.*t0_vec1.*t0_vec4.*t1_vec1.*2.0e+1+D_vec2.*D_vec3.*p1_vec2.*t0_vec2.*t0_vec3.*t1_vec3.*2.0e+1+D_vec2.*D_vec3.*p1_vec3.*t0_vec2.*t0_vec3.*t1_vec2.*2.0e+1-D_vec4.*D_vec5.*p0_vec4.*t0_vec4.*t0_vec5.*t1_vec5.*2.0e+1-D_vec4.*D_vec5.*p0_vec5.*t0_vec4.*t0_vec5.*t1_vec4.*2.0e+1+D_vec1.*D_vec5.*p1_vec1.*t0_vec1.*t0_vec5.*t1_vec5.*2.0e+1+D_vec1.*D_vec5.*p1_vec5.*t0_vec1.*t0_vec5.*t1_vec1.*2.0e+1+D_vec2.*D_vec4.*p1_vec2.*t0_vec2.*t0_vec4.*t1_vec4.*2.0e+1+D_vec2.*D_vec4.*p1_vec4.*t0_vec2.*t0_vec4.*t1_vec2.*2.0e+1+D_vec2.*D_vec5.*p1_vec2.*t0_vec2.*t0_vec5.*t1_vec5.*2.0e+1+D_vec2.*D_vec5.*p1_vec5.*t0_vec2.*t0_vec5.*t1_vec2.*2.0e+1+D_vec3.*D_vec4.*p1_vec3.*t0_vec3.*t0_vec4.*t1_vec4.*2.0e+1;
    // 'Calc_beta0_beta1:128' et20 =
    // D_vec3.*D_vec4.*p1_vec4.*t0_vec3.*t0_vec4.*t1_vec3.*2.0e+1+D_vec3.*D_vec5.*p1_vec3.*t0_vec3.*t0_vec5.*t1_vec5.*2.0e+1+D_vec3.*D_vec5.*p1_vec5.*t0_vec3.*t0_vec5.*t1_vec3.*2.0e+1+D_vec4.*D_vec5.*p1_vec4.*t0_vec4.*t0_vec5.*t1_vec5.*2.0e+1+D_vec4.*D_vec5.*p1_vec5.*t0_vec4.*t0_vec5.*t1_vec4.*2.0e+1-D_vec1.*D_vec2.*alpha1.*t0_vec1.*t0_vec2.*t1_vec1.*t1_vec2.*1.6e+1-D_vec1.*D_vec3.*alpha1.*t0_vec1.*t0_vec3.*t1_vec1.*t1_vec3.*1.6e+1-D_vec1.*D_vec4.*alpha1.*t0_vec1.*t0_vec4.*t1_vec1.*t1_vec4.*1.6e+1-D_vec2.*D_vec3.*alpha1.*t0_vec2.*t0_vec3.*t1_vec2.*t1_vec3.*1.6e+1-D_vec1.*D_vec5.*alpha1.*t0_vec1.*t0_vec5.*t1_vec1.*t1_vec5.*1.6e+1-D_vec2.*D_vec4.*alpha1.*t0_vec2.*t0_vec4.*t1_vec2.*t1_vec4.*1.6e+1-D_vec2.*D_vec5.*alpha1.*t0_vec2.*t0_vec5.*t1_vec2.*t1_vec5.*1.6e+1-D_vec3.*D_vec4.*alpha1.*t0_vec3.*t0_vec4.*t1_vec3.*t1_vec4.*1.6e+1-D_vec3.*D_vec5.*alpha1.*t0_vec3.*t0_vec5.*t1_vec3.*t1_vec5.*1.6e+1-D_vec4.*D_vec5.*alpha1.*t0_vec4.*t0_vec5.*t1_vec4.*t1_vec5.*1.6e+1-D_vec1.*D_vec2.*nk0_vec1.*t7.*t0_vec1.*t0_vec2.*t1_vec2.*3.0-D_vec1.*D_vec2.*nk0_vec2.*t7.*t0_vec1.*t0_vec2.*t1_vec1.*3.0-D_vec1.*D_vec3.*nk0_vec1.*t7.*t0_vec1.*t0_vec3.*t1_vec3.*3.0-D_vec1.*D_vec3.*nk0_vec3.*t7.*t0_vec1.*t0_vec3.*t1_vec1.*3.0;
    // 'Calc_beta0_beta1:129' et21 =
    // D_vec1.*D_vec4.*nk0_vec1.*t7.*t0_vec1.*t0_vec4.*t1_vec4.*-3.0-D_vec1.*D_vec4.*nk0_vec4.*t7.*t0_vec1.*t0_vec4.*t1_vec1.*3.0-D_vec2.*D_vec3.*nk0_vec2.*t7.*t0_vec2.*t0_vec3.*t1_vec3.*3.0-D_vec2.*D_vec3.*nk0_vec3.*t7.*t0_vec2.*t0_vec3.*t1_vec2.*3.0-D_vec1.*D_vec5.*nk0_vec1.*t7.*t0_vec1.*t0_vec5.*t1_vec5.*3.0-D_vec1.*D_vec5.*nk0_vec5.*t7.*t0_vec1.*t0_vec5.*t1_vec1.*3.0-D_vec2.*D_vec4.*nk0_vec2.*t7.*t0_vec2.*t0_vec4.*t1_vec4.*3.0-D_vec2.*D_vec4.*nk0_vec4.*t7.*t0_vec2.*t0_vec4.*t1_vec2.*3.0+D_vec1.*D_vec2.*nk1_vec1.*t8.*t0_vec1.*t0_vec2.*t1_vec2+D_vec1.*D_vec2.*nk1_vec2.*t8.*t0_vec1.*t0_vec2.*t1_vec1-D_vec2.*D_vec5.*nk0_vec2.*t7.*t0_vec2.*t0_vec5.*t1_vec5.*3.0-D_vec2.*D_vec5.*nk0_vec5.*t7.*t0_vec2.*t0_vec5.*t1_vec2.*3.0-D_vec3.*D_vec4.*nk0_vec3.*t7.*t0_vec3.*t0_vec4.*t1_vec4.*3.0-D_vec3.*D_vec4.*nk0_vec4.*t7.*t0_vec3.*t0_vec4.*t1_vec3.*3.0+D_vec1.*D_vec3.*nk1_vec1.*t8.*t0_vec1.*t0_vec3.*t1_vec3+D_vec1.*D_vec3.*nk1_vec3.*t8.*t0_vec1.*t0_vec3.*t1_vec1-D_vec3.*D_vec5.*nk0_vec3.*t7.*t0_vec3.*t0_vec5.*t1_vec5.*3.0-D_vec3.*D_vec5.*nk0_vec5.*t7.*t0_vec3.*t0_vec5.*t1_vec3.*3.0+D_vec1.*D_vec4.*nk1_vec1.*t8.*t0_vec1.*t0_vec4.*t1_vec4+D_vec1.*D_vec4.*nk1_vec4.*t8.*t0_vec1.*t0_vec4.*t1_vec1+D_vec2.*D_vec3.*nk1_vec2.*t8.*t0_vec2.*t0_vec3.*t1_vec3;
    // 'Calc_beta0_beta1:130' et22 =
    // D_vec2.*D_vec3.*nk1_vec3.*t8.*t0_vec2.*t0_vec3.*t1_vec2-D_vec4.*D_vec5.*nk0_vec4.*t7.*t0_vec4.*t0_vec5.*t1_vec5.*3.0-D_vec4.*D_vec5.*nk0_vec5.*t7.*t0_vec4.*t0_vec5.*t1_vec4.*3.0+D_vec1.*D_vec5.*nk1_vec1.*t8.*t0_vec1.*t0_vec5.*t1_vec5+D_vec1.*D_vec5.*nk1_vec5.*t8.*t0_vec1.*t0_vec5.*t1_vec1+D_vec2.*D_vec4.*nk1_vec2.*t8.*t0_vec2.*t0_vec4.*t1_vec4+D_vec2.*D_vec4.*nk1_vec4.*t8.*t0_vec2.*t0_vec4.*t1_vec2+D_vec2.*D_vec5.*nk1_vec2.*t8.*t0_vec2.*t0_vec5.*t1_vec5+D_vec2.*D_vec5.*nk1_vec5.*t8.*t0_vec2.*t0_vec5.*t1_vec2+D_vec3.*D_vec4.*nk1_vec3.*t8.*t0_vec3.*t0_vec4.*t1_vec4+D_vec3.*D_vec4.*nk1_vec4.*t8.*t0_vec3.*t0_vec4.*t1_vec3+D_vec3.*D_vec5.*nk1_vec3.*t8.*t0_vec3.*t0_vec5.*t1_vec5+D_vec3.*D_vec5.*nk1_vec5.*t8.*t0_vec3.*t0_vec5.*t1_vec3+D_vec4.*D_vec5.*nk1_vec4.*t8.*t0_vec4.*t0_vec5.*t1_vec5+D_vec4.*D_vec5.*nk1_vec5.*t8.*t0_vec4.*t0_vec5.*t1_vec4;
    // 'Calc_beta0_beta1:131' beta1 = t65.*(et12+et13+et14+et15+et16+et17+et18+et19+et20+et21+et22);
    *beta1 = t65 * ((((((((((((((((((((((((((((((((((yd_beta0_tmp * t9 * t14 * 28.0 +
                                                     ae_beta0_tmp * t10 * t15 * 28.0) +
                                                    be_beta0_tmp * t11 * t16 * 28.0) +
                                                   ce_beta0_tmp * t12 * t17 * 28.0) +
                                                  de_beta0_tmp * t13 * t18 * 28.0) +
                                                 ee_beta0_tmp * t9 * in7[0] * 40.0) +
                                                fe_beta0_tmp * t10 * in7[1] * 40.0) +
                                               ge_beta0_tmp * t11 * in7[2] * 40.0) -
                                              he_beta0_tmp * t9 * in7[0] * 40.0) +
                                             ie_beta0_tmp * t12 * in7[3] * 40.0) -
                                            je_beta0_tmp * t10 * in7[1] * 40.0) +
                                           ke_beta0_tmp * t13 * in7[4] * 40.0) -
                                          le_beta0_tmp * t11 * in7[2] * 40.0) -
                                         me_beta0_tmp * t12 * in7[3] * 40.0) -
                                        ne_beta0_tmp * t13 * in7[4] * 40.0) +
                                       oe_beta0_tmp * std::pow(in4[0], 3.0) * in7[0] * 12.0) +
                                      pe_beta0_tmp * std::pow(in4[1], 3.0) * in7[1] * 12.0) +
                                     qe_beta0_tmp * std::pow(in4[2], 3.0) * in7[2] * 12.0) +
                                    re_beta0_tmp * std::pow(in4[3], 3.0) * in7[3] * 12.0) +
                                   se_beta0_tmp * std::pow(in4[4], 3.0) * in7[4] * 12.0) +
                                  k_beta0_tmp * t9 * t15 * 36.0) +
                                 k_beta0_tmp * t10 * t14 * 36.0) +
                                l_beta0_tmp * t9 * t16 * 36.0) +
                               l_beta0_tmp * t11 * t14 * 36.0) +
                              n_beta0_tmp * t9 * t17 * 36.0) +
                             ((((((((((((((((((((((((n_beta0_tmp * t12 * t14 * 36.0 +
                                                     m_beta0_tmp * t10 * t16 * 36.0) +
                                                    m_beta0_tmp * t11 * t15 * 36.0) +
                                                   p_beta0_tmp * t9 * t18 * 36.0) +
                                                  p_beta0_tmp * t13 * t14 * 36.0) +
                                                 o_beta0_tmp * t10 * t17 * 36.0) +
                                                o_beta0_tmp * t12 * t15 * 36.0) +
                                               r_beta0_tmp * t10 * t18 * 36.0) +
                                              r_beta0_tmp * t13 * t15 * 36.0) +
                                             q_beta0_tmp * t11 * t17 * 36.0) +
                                            q_beta0_tmp * t12 * t16 * 36.0) +
                                           s_beta0_tmp * t11 * t18 * 36.0) +
                                          s_beta0_tmp * t13 * t16 * 36.0) +
                                         t_beta0_tmp * t12 * t18 * 36.0) +
                                        t_beta0_tmp * t13 * t17 * 36.0) +
                                       u_beta0_tmp * t10 * in7[0] * 60.0) +
                                      v_beta0_tmp * t9 * in7[1] * 60.0) +
                                     w_beta0_tmp * t11 * in7[0] * 60.0) +
                                    x_beta0_tmp * t9 * in7[2] * 60.0) +
                                   y_beta0_tmp * t12 * in7[0] * 60.0) +
                                  bb_beta0_tmp * t11 * in7[1] * 60.0) +
                                 db_beta0_tmp * t13 * in7[0] * 60.0) +
                                cb_beta0_tmp * t10 * in7[2] * 60.0) +
                               ab_beta0_tmp * t9 * in7[3] * 60.0) +
                              fb_beta0_tmp * t12 * in7[1] * 60.0)) +
                            ((((((((((((((((((((((gb_beta0_tmp * t10 * in7[3] * 60.0 +
                                                  jb_beta0_tmp * t13 * in7[1] * 60.0) -
                                                 hb_beta0_tmp * t10 * in7[0] * 60.0) +
                                                eb_beta0_tmp * t9 * in7[4] * 60.0) +
                                               lb_beta0_tmp * t12 * in7[2] * 60.0) -
                                              ib_beta0_tmp * t9 * in7[1] * 60.0) +
                                             mb_beta0_tmp * t11 * in7[3] * 60.0) -
                                            nb_beta0_tmp * t11 * in7[0] * 60.0) +
                                           kb_beta0_tmp * t10 * in7[4] * 60.0) +
                                          pb_beta0_tmp * t13 * in7[2] * 60.0) -
                                         ob_beta0_tmp * t9 * in7[2] * 60.0) -
                                        rb_beta0_tmp * t12 * in7[0] * 60.0) +
                                       qb_beta0_tmp * t11 * in7[4] * 60.0) -
                                      tb_beta0_tmp * t11 * in7[1] * 60.0) +
                                     vb_beta0_tmp * t13 * in7[3] * 60.0) -
                                    xb_beta0_tmp * t13 * in7[0] * 60.0) -
                                   ub_beta0_tmp * t10 * in7[2] * 60.0) +
                                  wb_beta0_tmp * t12 * in7[4] * 60.0) -
                                 sb_beta0_tmp * t9 * in7[3] * 60.0) -
                                ac_beta0_tmp * t12 * in7[1] * 60.0) -
                               bc_beta0_tmp * t10 * in7[3] * 60.0) -
                              cc_beta0_tmp * t13 * in7[1] * 60.0) -
                             yb_beta0_tmp * t9 * in7[4] * 60.0)) +
                           (((((((((((((((((((((ec_beta0_tmp * t12 * in7[2] * -60.0 -
                                                fc_beta0_tmp * t11 * in7[3] * 60.0) -
                                               dc_beta0_tmp * t10 * in7[4] * 60.0) -
                                              gc_beta0_tmp * t13 * in7[2] * 60.0) -
                                             hc_beta0_tmp * t11 * in7[4] * 60.0) -
                                            ic_beta0_tmp * t13 * in7[3] * 60.0) -
                                           jc_beta0_tmp * t12 * in7[4] * 60.0) -
                                          in8[0] * t2 * t8 * t9 * in7[0] * 8.0) -
                                         in8[1] * t3 * t8 * t10 * in7[1] * 8.0) -
                                        in8[2] * t4 * t8 * t11 * in7[2] * 8.0) -
                                       in8[3] * t5 * t8 * t12 * in7[3] * 8.0) -
                                      in8[4] * t6 * t8 * t13 * in7[4] * 8.0) +
                                     te_beta0_tmp * in4[0] * in7[0] * 12.0) +
                                    ue_beta0_tmp * in4[1] * in7[1] * 12.0) +
                                   ve_beta0_tmp * in4[0] * in7[0] * 12.0) +
                                  we_beta0_tmp * in4[2] * in7[2] * 12.0) +
                                 xe_beta0_tmp * in4[0] * in7[0] * 12.0) +
                                ye_beta0_tmp * in4[1] * in7[1] * 12.0) +
                               af_beta0_tmp * in4[0] * in7[0] * 12.0) +
                              bf_beta0_tmp * in4[2] * in7[2] * 12.0) +
                             cf_beta0_tmp * in4[3] * in7[3] * 12.0) +
                            df_beta0_tmp * in4[1] * in7[1] * 12.0)) +
                          ((((((((((((((((((((((ef_beta0_tmp * in4[3] * in7[3] * 12.0 +
                                                ff_beta0_tmp * in4[1] * in7[1] * 12.0) +
                                               gf_beta0_tmp * in4[4] * in7[4] * 12.0) +
                                              hf_beta0_tmp * in4[2] * in7[2] * 12.0) +
                                             if_beta0_tmp * in4[3] * in7[3] * 12.0) +
                                            jf_beta0_tmp * in4[4] * in7[4] * 12.0) +
                                           kf_beta0_tmp * in4[2] * in7[2] * 12.0) +
                                          lf_beta0_tmp * in4[4] * in7[4] * 12.0) +
                                         mf_beta0_tmp * in4[3] * in7[3] * 12.0) +
                                        nf_beta0_tmp * in4[4] * in7[4] * 12.0) +
                                       kc_beta0_tmp * t10 * in7[0] * 3.0) +
                                      lc_beta0_tmp * t9 * in7[1] * 3.0) +
                                     mc_beta0_tmp * t11 * in7[0] * 3.0) +
                                    nc_beta0_tmp * t9 * in7[2] * 3.0) +
                                   of_beta0_tmp * t12 * in7[0] * 3.0) +
                                  pc_beta0_tmp * t11 * in7[1] * 3.0) +
                                 rc_beta0_tmp * t13 * in7[0] * 3.0) +
                                qc_beta0_tmp * t10 * in7[2] * 3.0) +
                               oc_beta0_tmp * t9 * in7[3] * 3.0) +
                              tc_beta0_tmp * t12 * in7[1] * 3.0) +
                             uc_beta0_tmp * t10 * in7[3] * 3.0) +
                            xc_beta0_tmp * t13 * in7[1] * 3.0) +
                           sc_beta0_tmp * t9 * in7[4] * 3.0)) +
                         ((((((((((((((((((((ad_beta0_tmp * t12 * in7[2] * 3.0 -
                                             vc_beta0_tmp * t10 * in7[0] * 9.0) +
                                            bd_beta0_tmp * t11 * in7[3] * 3.0) -
                                           wc_beta0_tmp * t9 * in7[1] * 9.0) +
                                          yc_beta0_tmp * t10 * in7[4] * 3.0) +
                                         ed_beta0_tmp * t13 * in7[2] * 3.0) -
                                        cd_beta0_tmp * t11 * in7[0] * 9.0) +
                                       fd_beta0_tmp * t11 * in7[4] * 3.0) -
                                      dd_beta0_tmp * t9 * in7[2] * 9.0) -
                                     gd_beta0_tmp * t12 * in7[0] * 9.0) +
                                    kd_beta0_tmp * t13 * in7[3] * 3.0) -
                                   id_beta0_tmp * t11 * in7[1] * 9.0) +
                                  ld_beta0_tmp * t12 * in7[4] * 3.0) -
                                 md_beta0_tmp * t13 * in7[0] * 9.0) -
                                jd_beta0_tmp * t10 * in7[2] * 9.0) -
                               hd_beta0_tmp * t9 * in7[3] * 9.0) -
                              od_beta0_tmp * t12 * in7[1] * 9.0) -
                             pd_beta0_tmp * t10 * in7[3] * 9.0) -
                            qd_beta0_tmp * t13 * in7[1] * 9.0) -
                           nd_beta0_tmp * t9 * in7[4] * 9.0) -
                          sd_beta0_tmp * t12 * in7[2] * 9.0)) +
                        (((((((((((((((((((td_beta0_tmp * t11 * in7[3] * -9.0 -
                                           rd_beta0_tmp * t10 * in7[4] * 9.0) -
                                          ud_beta0_tmp * t13 * in7[2] * 9.0) -
                                         vd_beta0_tmp * t11 * in7[4] * 9.0) -
                                        wd_beta0_tmp * t13 * in7[3] * 9.0) -
                                       xd_beta0_tmp * t12 * in7[4] * 9.0) -
                                      u_beta0_tmp * in4[0] * in4[1] * in7[1] * 20.0) -
                                     pf_beta0_tmp * in4[1] * in7[0] * 20.0) -
                                    w_beta0_tmp * in4[0] * in4[2] * in7[2] * 20.0) -
                                   qf_beta0_tmp * in4[2] * in7[0] * 20.0) -
                                  y_beta0_tmp * in4[0] * in4[3] * in7[3] * 20.0) -
                                 rf_beta0_tmp * in4[3] * in7[0] * 20.0) -
                                bb_beta0_tmp * in4[1] * in4[2] * in7[2] * 20.0) -
                               sf_beta0_tmp * in4[2] * in7[1] * 20.0) -
                              db_beta0_tmp * in4[0] * in4[4] * in7[4] * 20.0) -
                             tf_beta0_tmp * in4[4] * in7[0] * 20.0) -
                            fb_beta0_tmp * in4[1] * in4[3] * in7[3] * 20.0) -
                           uf_beta0_tmp * in4[3] * in7[1] * 20.0) +
                          hb_beta0_tmp * in4[0] * in4[1] * in7[1] * 20.0) +
                         vf_beta0_tmp * in4[1] * in7[0] * 20.0)) +
                       ((((((((((((((((((((jb_beta0_tmp * in4[1] * in4[4] * in7[4] * -20.0 -
                                           wf_beta0_tmp * in4[4] * in7[1] * 20.0) -
                                          lb_beta0_tmp * in4[2] * in4[3] * in7[3] * 20.0) -
                                         xf_beta0_tmp * in4[3] * in7[2] * 20.0) +
                                        nb_beta0_tmp * in4[0] * in4[2] * in7[2] * 20.0) +
                                       yf_beta0_tmp * in4[2] * in7[0] * 20.0) -
                                      pb_beta0_tmp * in4[2] * in4[4] * in7[4] * 20.0) -
                                     ag_beta0_tmp * in4[4] * in7[2] * 20.0) +
                                    rb_beta0_tmp * in4[0] * in4[3] * in7[3] * 20.0) +
                                   bg_beta0_tmp * in4[3] * in7[0] * 20.0) +
                                  tb_beta0_tmp * in4[1] * in4[2] * in7[2] * 20.0) +
                                 cg_beta0_tmp * in4[2] * in7[1] * 20.0) -
                                vb_beta0_tmp * in4[3] * in4[4] * in7[4] * 20.0) -
                               dg_beta0_tmp * in4[4] * in7[3] * 20.0) +
                              xb_beta0_tmp * in4[0] * in4[4] * in7[4] * 20.0) +
                             eg_beta0_tmp * in4[4] * in7[0] * 20.0) +
                            ac_beta0_tmp * in4[1] * in4[3] * in7[3] * 20.0) +
                           fg_beta0_tmp * in4[3] * in7[1] * 20.0) +
                          cc_beta0_tmp * in4[1] * in4[4] * in7[4] * 20.0) +
                         gg_beta0_tmp * in4[4] * in7[1] * 20.0) +
                        ec_beta0_tmp * in4[2] * in4[3] * in7[3] * 20.0)) +
                      ((((((((((((((((((hg_beta0_tmp * in4[3] * in7[2] * 20.0 +
                                        gc_beta0_tmp * in4[2] * in4[4] * in7[4] * 20.0) +
                                       ig_beta0_tmp * in4[4] * in7[2] * 20.0) +
                                      ic_beta0_tmp * in4[3] * in4[4] * in7[4] * 20.0) +
                                     jg_beta0_tmp * in4[4] * in7[3] * 20.0) -
                                    k_beta0_tmp * in4[0] * in4[1] * in7[0] * in7[1] * 16.0) -
                                   l_beta0_tmp * in4[0] * in4[2] * in7[0] * in7[2] * 16.0) -
                                  n_beta0_tmp * in4[0] * in4[3] * in7[0] * in7[3] * 16.0) -
                                 m_beta0_tmp * in4[1] * in4[2] * in7[1] * in7[2] * 16.0) -
                                p_beta0_tmp * in4[0] * in4[4] * in7[0] * in7[4] * 16.0) -
                               o_beta0_tmp * in4[1] * in4[3] * in7[1] * in7[3] * 16.0) -
                              r_beta0_tmp * in4[1] * in4[4] * in7[1] * in7[4] * 16.0) -
                             q_beta0_tmp * in4[2] * in4[3] * in7[2] * in7[3] * 16.0) -
                            s_beta0_tmp * in4[2] * in4[4] * in7[2] * in7[4] * 16.0) -
                           t_beta0_tmp * in4[3] * in4[4] * in7[3] * in7[4] * 16.0) -
                          kc_beta0_tmp * in4[0] * in4[1] * in7[1] * 3.0) -
                         kg_beta0_tmp * in4[1] * in7[0] * 3.0) -
                        mc_beta0_tmp * in4[0] * in4[2] * in7[2] * 3.0) -
                       lg_beta0_tmp * in4[2] * in7[0] * 3.0)) +
                     ((((((((((((((((((((of_beta0_tmp * in4[0] * in4[3] * in7[3] * -3.0 -
                                         mg_beta0_tmp * in4[3] * in7[0] * 3.0) -
                                        pc_beta0_tmp * in4[1] * in4[2] * in7[2] * 3.0) -
                                       ng_beta0_tmp * in4[2] * in7[1] * 3.0) -
                                      rc_beta0_tmp * in4[0] * in4[4] * in7[4] * 3.0) -
                                     og_beta0_tmp * in4[4] * in7[0] * 3.0) -
                                    tc_beta0_tmp * in4[1] * in4[3] * in7[3] * 3.0) -
                                   pg_beta0_tmp * in4[3] * in7[1] * 3.0) +
                                  vc_beta0_tmp * in4[0] * in4[1] * in7[1]) +
                                 qg_beta0_tmp * in4[1] * in7[0]) -
                                xc_beta0_tmp * in4[1] * in4[4] * in7[4] * 3.0) -
                               rg_beta0_tmp * in4[4] * in7[1] * 3.0) -
                              ad_beta0_tmp * in4[2] * in4[3] * in7[3] * 3.0) -
                             sg_beta0_tmp * in4[3] * in7[2] * 3.0) +
                            cd_beta0_tmp * in4[0] * in4[2] * in7[2]) +
                           tg_beta0_tmp * in4[2] * in7[0]) -
                          ed_beta0_tmp * in4[2] * in4[4] * in7[4] * 3.0) -
                         ug_beta0_tmp * in4[4] * in7[2] * 3.0) +
                        gd_beta0_tmp * in4[0] * in4[3] * in7[3]) +
                       vg_beta0_tmp * in4[3] * in7[0]) +
                      id_beta0_tmp * in4[1] * in4[2] * in7[2])) +
                    ((((((((((((((wg_beta0_tmp * in4[2] * in7[1] -
                                  kd_beta0_tmp * in4[3] * in4[4] * in7[4] * 3.0) -
                                 xg_beta0_tmp * in4[4] * in7[3] * 3.0) +
                                md_beta0_tmp * in4[0] * in4[4] * in7[4]) +
                               yg_beta0_tmp * in4[4] * in7[0]) +
                              od_beta0_tmp * in4[1] * in4[3] * in7[3]) +
                             ah_beta0_tmp * in4[3] * in7[1]) +
                            qd_beta0_tmp * in4[1] * in4[4] * in7[4]) +
                           bh_beta0_tmp * in4[4] * in7[1]) +
                          sd_beta0_tmp * in4[2] * in4[3] * in7[3]) +
                         ch_beta0_tmp * in4[3] * in7[2]) +
                        ud_beta0_tmp * in4[2] * in4[4] * in7[4]) +
                       dh_beta0_tmp * in4[4] * in7[2]) +
                      wd_beta0_tmp * in4[3] * in4[4] * in7[4]) +
                     eh_beta0_tmp * in4[4] * in7[3]));
}

} // namespace ocn

//
// File trailer for Calc_beta0_beta1.cpp
//
// [EOF]
//
