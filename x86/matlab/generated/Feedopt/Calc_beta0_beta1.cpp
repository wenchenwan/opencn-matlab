
//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: Calc_beta0_beta1.cpp
//
// MATLAB Coder version            : 5.4
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
//                const double in3[6]
//                const double in4[6]
//                const double in5[6]
//                const double in6[6]
//                const double in7[6]
//                const double in8[6]
//                const double in9[6]
//                double *beta0
//                double *beta1
// Return Type  : void
//
namespace ocn {
void Calc_beta0_beta1(double alpha0, double alpha1, const double in3[6], const double in4[6],
                      const double in5[6], const double in6[6], const double in7[6],
                      const double in8[6], const double in9[6], double *beta0, double *beta1)
{
    double ab_beta0_tmp;
    double ac_beta0_tmp;
    double ad_beta0_tmp;
    double ae_beta0_tmp;
    double af_beta0_tmp;
    double ag_beta0_tmp;
    double ah_beta0_tmp;
    double ai_beta0_tmp;
    double aj_beta0_tmp;
    double ak_beta0_tmp;
    double b_beta0_tmp;
    double b_beta0_tmp_tmp;
    double bb_beta0_tmp;
    double bc_beta0_tmp;
    double bd_beta0_tmp;
    double be_beta0_tmp;
    double beta0_tmp;
    double beta0_tmp_tmp;
    double bf_beta0_tmp;
    double bg_beta0_tmp;
    double bh_beta0_tmp;
    double bi_beta0_tmp;
    double bj_beta0_tmp;
    double bk_beta0_tmp;
    double c_beta0_tmp;
    double c_beta0_tmp_tmp;
    double cb_beta0_tmp;
    double cc_beta0_tmp;
    double cd_beta0_tmp;
    double ce_beta0_tmp;
    double cf_beta0_tmp;
    double cg_beta0_tmp;
    double ch_beta0_tmp;
    double ci_beta0_tmp;
    double cj_beta0_tmp;
    double ck_beta0_tmp;
    double d;
    double d1;
    double d10;
    double d11;
    double d12;
    double d13;
    double d14;
    double d2;
    double d3;
    double d4;
    double d5;
    double d6;
    double d7;
    double d8;
    double d9;
    double d_beta0_tmp;
    double db_beta0_tmp;
    double dc_beta0_tmp;
    double dd_beta0_tmp;
    double de_beta0_tmp;
    double df_beta0_tmp;
    double dg_beta0_tmp;
    double dh_beta0_tmp;
    double di_beta0_tmp;
    double dj_beta0_tmp;
    double dk_beta0_tmp;
    double e_beta0_tmp;
    double eb_beta0_tmp;
    double ec_beta0_tmp;
    double ed_beta0_tmp;
    double ee_beta0_tmp;
    double ef_beta0_tmp;
    double eg_beta0_tmp;
    double eh_beta0_tmp;
    double ei_beta0_tmp;
    double ej_beta0_tmp;
    double ek_beta0_tmp;
    double f_beta0_tmp;
    double fb_beta0_tmp;
    double fc_beta0_tmp;
    double fd_beta0_tmp;
    double fe_beta0_tmp;
    double ff_beta0_tmp;
    double fg_beta0_tmp;
    double fh_beta0_tmp;
    double fi_beta0_tmp;
    double fj_beta0_tmp;
    double fk_beta0_tmp;
    double g_beta0_tmp;
    double gb_beta0_tmp;
    double gc_beta0_tmp;
    double gd_beta0_tmp;
    double ge_beta0_tmp;
    double gf_beta0_tmp;
    double gg_beta0_tmp;
    double gh_beta0_tmp;
    double gi_beta0_tmp;
    double gj_beta0_tmp;
    double gk_beta0_tmp;
    double h_beta0_tmp;
    double hb_beta0_tmp;
    double hc_beta0_tmp;
    double hd_beta0_tmp;
    double he_beta0_tmp;
    double hf_beta0_tmp;
    double hg_beta0_tmp;
    double hh_beta0_tmp;
    double hi_beta0_tmp;
    double hj_beta0_tmp;
    double i_beta0_tmp;
    double ib_beta0_tmp;
    double ic_beta0_tmp;
    double id_beta0_tmp;
    double ie_beta0_tmp;
    double if_beta0_tmp;
    double ig_beta0_tmp;
    double ih_beta0_tmp;
    double ii_beta0_tmp;
    double ij_beta0_tmp;
    double j_beta0_tmp;
    double jb_beta0_tmp;
    double jc_beta0_tmp;
    double jd_beta0_tmp;
    double je_beta0_tmp;
    double jf_beta0_tmp;
    double jg_beta0_tmp;
    double jh_beta0_tmp;
    double ji_beta0_tmp;
    double jj_beta0_tmp;
    double k_beta0_tmp;
    double kb_beta0_tmp;
    double kc_beta0_tmp;
    double kd_beta0_tmp;
    double ke_beta0_tmp;
    double kf_beta0_tmp;
    double kg_beta0_tmp;
    double kh_beta0_tmp;
    double ki_beta0_tmp;
    double kj_beta0_tmp;
    double l_beta0_tmp;
    double lb_beta0_tmp;
    double lc_beta0_tmp;
    double ld_beta0_tmp;
    double le_beta0_tmp;
    double lf_beta0_tmp;
    double lg_beta0_tmp;
    double lh_beta0_tmp;
    double li_beta0_tmp;
    double lj_beta0_tmp;
    double m_beta0_tmp;
    double mb_beta0_tmp;
    double mc_beta0_tmp;
    double md_beta0_tmp;
    double me_beta0_tmp;
    double mf_beta0_tmp;
    double mg_beta0_tmp;
    double mh_beta0_tmp;
    double mi_beta0_tmp;
    double mj_beta0_tmp;
    double n_beta0_tmp;
    double nb_beta0_tmp;
    double nc_beta0_tmp;
    double nd_beta0_tmp;
    double ne_beta0_tmp;
    double nf_beta0_tmp;
    double ng_beta0_tmp;
    double nh_beta0_tmp;
    double ni_beta0_tmp;
    double nj_beta0_tmp;
    double o_beta0_tmp;
    double ob_beta0_tmp;
    double oc_beta0_tmp;
    double od_beta0_tmp;
    double oe_beta0_tmp;
    double of_beta0_tmp;
    double og_beta0_tmp;
    double oh_beta0_tmp;
    double oi_beta0_tmp;
    double oj_beta0_tmp;
    double p_beta0_tmp;
    double pb_beta0_tmp;
    double pc_beta0_tmp;
    double pd_beta0_tmp;
    double pe_beta0_tmp;
    double pf_beta0_tmp;
    double pg_beta0_tmp;
    double ph_beta0_tmp;
    double pi_beta0_tmp;
    double pj_beta0_tmp;
    double q_beta0_tmp;
    double qb_beta0_tmp;
    double qc_beta0_tmp;
    double qd_beta0_tmp;
    double qe_beta0_tmp;
    double qf_beta0_tmp;
    double qg_beta0_tmp;
    double qh_beta0_tmp;
    double qi_beta0_tmp;
    double qj_beta0_tmp;
    double r_beta0_tmp;
    double rb_beta0_tmp;
    double rc_beta0_tmp;
    double rd_beta0_tmp;
    double re_beta0_tmp;
    double rf_beta0_tmp;
    double rg_beta0_tmp;
    double rh_beta0_tmp;
    double ri_beta0_tmp;
    double rj_beta0_tmp;
    double s_beta0_tmp;
    double sb_beta0_tmp;
    double sc_beta0_tmp;
    double sd_beta0_tmp;
    double se_beta0_tmp;
    double sf_beta0_tmp;
    double sg_beta0_tmp;
    double sh_beta0_tmp;
    double si_beta0_tmp;
    double sj_beta0_tmp;
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
    double t89;
    double t9;
    double t_beta0_tmp;
    double tb_beta0_tmp;
    double tc_beta0_tmp;
    double td_beta0_tmp;
    double te_beta0_tmp;
    double tf_beta0_tmp;
    double tg_beta0_tmp;
    double th_beta0_tmp;
    double ti_beta0_tmp;
    double tj_beta0_tmp;
    double u_beta0_tmp;
    double ub_beta0_tmp;
    double uc_beta0_tmp;
    double ud_beta0_tmp;
    double ue_beta0_tmp;
    double uf_beta0_tmp;
    double ug_beta0_tmp;
    double uh_beta0_tmp;
    double ui_beta0_tmp;
    double uj_beta0_tmp;
    double v_beta0_tmp;
    double vb_beta0_tmp;
    double vc_beta0_tmp;
    double vd_beta0_tmp;
    double ve_beta0_tmp;
    double vf_beta0_tmp;
    double vg_beta0_tmp;
    double vh_beta0_tmp;
    double vi_beta0_tmp;
    double vj_beta0_tmp;
    double w_beta0_tmp;
    double wb_beta0_tmp;
    double wc_beta0_tmp;
    double wd_beta0_tmp;
    double we_beta0_tmp;
    double wf_beta0_tmp;
    double wg_beta0_tmp;
    double wh_beta0_tmp;
    double wi_beta0_tmp;
    double wj_beta0_tmp;
    double x_beta0_tmp;
    double xb_beta0_tmp;
    double xc_beta0_tmp;
    double xd_beta0_tmp;
    double xe_beta0_tmp;
    double xf_beta0_tmp;
    double xg_beta0_tmp;
    double xh_beta0_tmp;
    double xi_beta0_tmp;
    double xj_beta0_tmp;
    double y_beta0_tmp;
    double yb_beta0_tmp;
    double yc_beta0_tmp;
    double yd_beta0_tmp;
    double ye_beta0_tmp;
    double yf_beta0_tmp;
    double yg_beta0_tmp;
    double yh_beta0_tmp;
    double yi_beta0_tmp;
    double yj_beta0_tmp;
    //     This function was generated by the Symbolic Math Toolbox version 9.1.
    //     11-Oct-2023 12:58:47
    // 'Calc_beta0_beta1:8' D_vec1 = in9(1,:);
    // 'Calc_beta0_beta1:9' D_vec2 = in9(2,:);
    // 'Calc_beta0_beta1:10' D_vec3 = in9(3,:);
    // 'Calc_beta0_beta1:11' D_vec4 = in9(4,:);
    // 'Calc_beta0_beta1:12' D_vec5 = in9(5,:);
    // 'Calc_beta0_beta1:13' D_vec6 = in9(6,:);
    // 'Calc_beta0_beta1:14' nk0_vec1 = in5(1,:);
    // 'Calc_beta0_beta1:15' nk0_vec2 = in5(2,:);
    // 'Calc_beta0_beta1:16' nk0_vec3 = in5(3,:);
    // 'Calc_beta0_beta1:17' nk0_vec4 = in5(4,:);
    // 'Calc_beta0_beta1:18' nk0_vec5 = in5(5,:);
    // 'Calc_beta0_beta1:19' nk0_vec6 = in5(6,:);
    // 'Calc_beta0_beta1:20' nk1_vec1 = in8(1,:);
    // 'Calc_beta0_beta1:21' nk1_vec2 = in8(2,:);
    // 'Calc_beta0_beta1:22' nk1_vec3 = in8(3,:);
    // 'Calc_beta0_beta1:23' nk1_vec4 = in8(4,:);
    // 'Calc_beta0_beta1:24' nk1_vec5 = in8(5,:);
    // 'Calc_beta0_beta1:25' nk1_vec6 = in8(6,:);
    // 'Calc_beta0_beta1:26' p0_vec1 = in3(1,:);
    // 'Calc_beta0_beta1:27' p0_vec2 = in3(2,:);
    // 'Calc_beta0_beta1:28' p0_vec3 = in3(3,:);
    // 'Calc_beta0_beta1:29' p0_vec4 = in3(4,:);
    // 'Calc_beta0_beta1:30' p0_vec5 = in3(5,:);
    // 'Calc_beta0_beta1:31' p0_vec6 = in3(6,:);
    // 'Calc_beta0_beta1:32' p1_vec1 = in6(1,:);
    // 'Calc_beta0_beta1:33' p1_vec2 = in6(2,:);
    // 'Calc_beta0_beta1:34' p1_vec3 = in6(3,:);
    // 'Calc_beta0_beta1:35' p1_vec4 = in6(4,:);
    // 'Calc_beta0_beta1:36' p1_vec5 = in6(5,:);
    // 'Calc_beta0_beta1:37' p1_vec6 = in6(6,:);
    // 'Calc_beta0_beta1:38' t0_vec1 = in4(1,:);
    // 'Calc_beta0_beta1:39' t0_vec2 = in4(2,:);
    // 'Calc_beta0_beta1:40' t0_vec3 = in4(3,:);
    // 'Calc_beta0_beta1:41' t0_vec4 = in4(4,:);
    // 'Calc_beta0_beta1:42' t0_vec5 = in4(5,:);
    // 'Calc_beta0_beta1:43' t0_vec6 = in4(6,:);
    // 'Calc_beta0_beta1:44' t1_vec1 = in7(1,:);
    // 'Calc_beta0_beta1:45' t1_vec2 = in7(2,:);
    // 'Calc_beta0_beta1:46' t1_vec3 = in7(3,:);
    // 'Calc_beta0_beta1:47' t1_vec4 = in7(4,:);
    // 'Calc_beta0_beta1:48' t1_vec5 = in7(5,:);
    // 'Calc_beta0_beta1:49' t1_vec6 = in7(6,:);
    // 'Calc_beta0_beta1:50' t2 = D_vec1.^2;
    t2 = in9[0] * in9[0];
    // 'Calc_beta0_beta1:51' t3 = D_vec2.^2;
    t3 = in9[1] * in9[1];
    // 'Calc_beta0_beta1:52' t4 = D_vec3.^2;
    t4 = in9[2] * in9[2];
    // 'Calc_beta0_beta1:53' t5 = D_vec4.^2;
    t5 = in9[3] * in9[3];
    // 'Calc_beta0_beta1:54' t6 = D_vec5.^2;
    t6 = in9[4] * in9[4];
    // 'Calc_beta0_beta1:55' t7 = D_vec6.^2;
    t7 = in9[5] * in9[5];
    // 'Calc_beta0_beta1:56' t8 = alpha0.^2;
    t8 = alpha0 * alpha0;
    // 'Calc_beta0_beta1:57' t9 = alpha1.^2;
    t9 = alpha1 * alpha1;
    // 'Calc_beta0_beta1:58' t10 = t0_vec1.^2;
    t10 = in4[0] * in4[0];
    // 'Calc_beta0_beta1:59' t11 = t0_vec2.^2;
    t11 = in4[1] * in4[1];
    // 'Calc_beta0_beta1:60' t12 = t0_vec3.^2;
    t12 = in4[2] * in4[2];
    // 'Calc_beta0_beta1:61' t13 = t0_vec4.^2;
    t13 = in4[3] * in4[3];
    // 'Calc_beta0_beta1:62' t14 = t0_vec5.^2;
    t14 = in4[4] * in4[4];
    // 'Calc_beta0_beta1:63' t15 = t0_vec6.^2;
    t15 = in4[5] * in4[5];
    // 'Calc_beta0_beta1:64' t16 = t1_vec1.^2;
    t16 = in7[0] * in7[0];
    // 'Calc_beta0_beta1:65' t17 = t1_vec2.^2;
    t17 = in7[1] * in7[1];
    // 'Calc_beta0_beta1:66' t18 = t1_vec3.^2;
    t18 = in7[2] * in7[2];
    // 'Calc_beta0_beta1:67' t19 = t1_vec4.^2;
    t19 = in7[3] * in7[3];
    // 'Calc_beta0_beta1:68' t20 = t1_vec5.^2;
    t20 = in7[4] * in7[4];
    // 'Calc_beta0_beta1:69' t21 = t1_vec6.^2;
    t21 = in7[5] * in7[5];
    // 'Calc_beta0_beta1:70' t22 = D_vec1.*D_vec2.*t0_vec1.*t0_vec2.*t1_vec1.*t1_vec2.*2.0;
    // 'Calc_beta0_beta1:71' t23 = D_vec1.*D_vec3.*t0_vec1.*t0_vec3.*t1_vec1.*t1_vec3.*2.0;
    // 'Calc_beta0_beta1:72' t24 = D_vec1.*D_vec4.*t0_vec1.*t0_vec4.*t1_vec1.*t1_vec4.*2.0;
    // 'Calc_beta0_beta1:73' t25 = D_vec2.*D_vec3.*t0_vec2.*t0_vec3.*t1_vec2.*t1_vec3.*2.0;
    // 'Calc_beta0_beta1:74' t26 = D_vec1.*D_vec5.*t0_vec1.*t0_vec5.*t1_vec1.*t1_vec5.*2.0;
    // 'Calc_beta0_beta1:75' t27 = D_vec2.*D_vec4.*t0_vec2.*t0_vec4.*t1_vec2.*t1_vec4.*2.0;
    // 'Calc_beta0_beta1:76' t28 = D_vec1.*D_vec6.*t0_vec1.*t0_vec6.*t1_vec1.*t1_vec6.*2.0;
    // 'Calc_beta0_beta1:77' t29 = D_vec2.*D_vec5.*t0_vec2.*t0_vec5.*t1_vec2.*t1_vec5.*2.0;
    // 'Calc_beta0_beta1:78' t30 = D_vec3.*D_vec4.*t0_vec3.*t0_vec4.*t1_vec3.*t1_vec4.*2.0;
    // 'Calc_beta0_beta1:79' t31 = D_vec2.*D_vec6.*t0_vec2.*t0_vec6.*t1_vec2.*t1_vec6.*2.0;
    // 'Calc_beta0_beta1:80' t32 = D_vec3.*D_vec5.*t0_vec3.*t0_vec5.*t1_vec3.*t1_vec5.*2.0;
    // 'Calc_beta0_beta1:81' t33 = D_vec3.*D_vec6.*t0_vec3.*t0_vec6.*t1_vec3.*t1_vec6.*2.0;
    // 'Calc_beta0_beta1:82' t34 = D_vec4.*D_vec5.*t0_vec4.*t0_vec5.*t1_vec4.*t1_vec5.*2.0;
    // 'Calc_beta0_beta1:83' t35 = D_vec4.*D_vec6.*t0_vec4.*t0_vec6.*t1_vec4.*t1_vec6.*2.0;
    // 'Calc_beta0_beta1:84' t36 = D_vec5.*D_vec6.*t0_vec5.*t0_vec6.*t1_vec5.*t1_vec6.*2.0;
    // 'Calc_beta0_beta1:85' t37 = -t22;
    // 'Calc_beta0_beta1:86' t38 = -t23;
    // 'Calc_beta0_beta1:87' t39 = -t24;
    // 'Calc_beta0_beta1:88' t40 = -t25;
    // 'Calc_beta0_beta1:89' t41 = -t26;
    // 'Calc_beta0_beta1:90' t42 = -t27;
    // 'Calc_beta0_beta1:91' t43 = -t28;
    // 'Calc_beta0_beta1:92' t44 = -t29;
    // 'Calc_beta0_beta1:93' t45 = -t30;
    // 'Calc_beta0_beta1:94' t46 = -t31;
    // 'Calc_beta0_beta1:95' t47 = -t32;
    // 'Calc_beta0_beta1:96' t48 = -t33;
    // 'Calc_beta0_beta1:97' t49 = -t34;
    // 'Calc_beta0_beta1:98' t50 = -t35;
    // 'Calc_beta0_beta1:99' t51 = -t36;
    // 'Calc_beta0_beta1:100' t52 = D_vec1.*D_vec2.*t10.*t17.*9.0;
    // 'Calc_beta0_beta1:101' t53 = D_vec1.*D_vec2.*t11.*t16.*9.0;
    // 'Calc_beta0_beta1:102' t54 = D_vec1.*D_vec3.*t10.*t18.*9.0;
    // 'Calc_beta0_beta1:103' t55 = D_vec1.*D_vec3.*t12.*t16.*9.0;
    // 'Calc_beta0_beta1:104' t56 = D_vec1.*D_vec4.*t10.*t19.*9.0;
    // 'Calc_beta0_beta1:105' t57 = D_vec1.*D_vec4.*t13.*t16.*9.0;
    // 'Calc_beta0_beta1:106' t58 = D_vec2.*D_vec3.*t11.*t18.*9.0;
    // 'Calc_beta0_beta1:107' t59 = D_vec2.*D_vec3.*t12.*t17.*9.0;
    // 'Calc_beta0_beta1:108' t60 = D_vec1.*D_vec5.*t10.*t20.*9.0;
    // 'Calc_beta0_beta1:109' t61 = D_vec1.*D_vec5.*t14.*t16.*9.0;
    // 'Calc_beta0_beta1:110' t62 = D_vec2.*D_vec4.*t11.*t19.*9.0;
    // 'Calc_beta0_beta1:111' t63 = D_vec2.*D_vec4.*t13.*t17.*9.0;
    // 'Calc_beta0_beta1:112' t64 = D_vec1.*D_vec6.*t10.*t21.*9.0;
    // 'Calc_beta0_beta1:113' t65 = D_vec1.*D_vec6.*t15.*t16.*9.0;
    // 'Calc_beta0_beta1:114' t66 = D_vec2.*D_vec5.*t11.*t20.*9.0;
    // 'Calc_beta0_beta1:115' t67 = D_vec2.*D_vec5.*t14.*t17.*9.0;
    // 'Calc_beta0_beta1:116' t68 = D_vec3.*D_vec4.*t12.*t19.*9.0;
    // 'Calc_beta0_beta1:117' t69 = D_vec3.*D_vec4.*t13.*t18.*9.0;
    // 'Calc_beta0_beta1:118' t70 = D_vec2.*D_vec6.*t11.*t21.*9.0;
    // 'Calc_beta0_beta1:119' t71 = D_vec2.*D_vec6.*t15.*t17.*9.0;
    // 'Calc_beta0_beta1:120' t72 = D_vec3.*D_vec5.*t12.*t20.*9.0;
    // 'Calc_beta0_beta1:121' t73 = D_vec3.*D_vec5.*t14.*t18.*9.0;
    // 'Calc_beta0_beta1:122' t74 = D_vec3.*D_vec6.*t12.*t21.*9.0;
    // 'Calc_beta0_beta1:123' t75 = D_vec3.*D_vec6.*t15.*t18.*9.0;
    // 'Calc_beta0_beta1:124' t76 = D_vec4.*D_vec5.*t13.*t20.*9.0;
    // 'Calc_beta0_beta1:125' t77 = D_vec4.*D_vec5.*t14.*t19.*9.0;
    // 'Calc_beta0_beta1:126' t78 = D_vec4.*D_vec6.*t13.*t21.*9.0;
    // 'Calc_beta0_beta1:127' t79 = D_vec4.*D_vec6.*t15.*t19.*9.0;
    // 'Calc_beta0_beta1:128' t80 = D_vec5.*D_vec6.*t14.*t21.*9.0;
    // 'Calc_beta0_beta1:129' t81 = D_vec5.*D_vec6.*t15.*t20.*9.0;
    // 'Calc_beta0_beta1:130' t82 = t2.*t10.*t16.*8.0;
    // 'Calc_beta0_beta1:131' t83 = t3.*t11.*t17.*8.0;
    // 'Calc_beta0_beta1:132' t84 = t4.*t12.*t18.*8.0;
    // 'Calc_beta0_beta1:133' t85 = t5.*t13.*t19.*8.0;
    // 'Calc_beta0_beta1:134' t86 = t6.*t14.*t20.*8.0;
    // 'Calc_beta0_beta1:135' t87 = t7.*t15.*t21.*8.0;
    // 'Calc_beta0_beta1:136' t88 =
    // t37+t38+t39+t40+t41+t42+t43+t44+t45+t46+t47+t48+t49+t50+t51+t52+t53+t54+t55+t56+t57+t58+t59+t60+t61+t62+t63+t64+t65+t66+t67+t68+t69+t70+t71+t72+t73+t74+t75+t76+t77+t78+t79+t80+t81+t82+t83+t84+t85+t86+t87;
    // 'Calc_beta0_beta1:137' t89 = 1.0./t88;
    d = in9[0] * in9[1];
    d1 = in9[0] * in9[2];
    d2 = in9[0] * in9[3];
    d3 = in9[1] * in9[2];
    d4 = in9[0] * in9[4];
    d5 = in9[1] * in9[3];
    d6 = in9[0] * in9[5];
    d7 = in9[1] * in9[4];
    d8 = in9[2] * in9[3];
    d9 = in9[1] * in9[5];
    d10 = in9[2] * in9[4];
    d11 = in9[2] * in9[5];
    d12 = in9[3] * in9[4];
    d13 = in9[3] * in9[5];
    d14 = in9[4] * in9[5];
    t89 = 1.0 / ((((((((((((((((((((((((((((((((((((((((((((((((((-(d * in4[0] * in4[1] * in7[0] * in7[1] * 2.0) + -(d1 * in4[0] * in4[2] * in7[0] * in7[2] * 2.0)) + -(d2 * in4[0] * in4[3] * in7[0] * in7[3] * 2.0)) + -(d3 * in4[1] * in4[2] * in7[1] * in7[2] * 2.0)) + -(d4 * in4[0] * in4[4] * in7[0] * in7[4] * 2.0)) + -(d5 * in4[1] * in4[3] * in7[1] * in7[3] * 2.0)) + -(d6 * in4[0] * in4[5] * in7[0] * in7[5] * 2.0)) + -(d7 * in4[1] * in4[4] * in7[1] * in7[4] * 2.0)) + -(d8 * in4[2] * in4[3] * in7[2] * in7[3] * 2.0)) + -(d9 * in4[1] * in4[5] * in7[1] * in7[5] * 2.0)) + -(d10 * in4[2] * in4[4] * in7[2] * in7[4] * 2.0)) + -(d11 * in4[2] * in4[5] * in7[2] * in7[5] * 2.0)) + -(d12 * in4[3] * in4[4] * in7[3] * in7[4] * 2.0)) + -(d13 * in4[3] * in4[5] * in7[3] * in7[5] * 2.0)) + -(d14 * in4[4] * in4[5] * in7[4] * in7[5] * 2.0)) + d * t10 * t17 * 9.0) + d * t11 * t16 * 9.0) + d1 * t10 * t18 * 9.0) + d1 * t12 * t16 * 9.0) + d2 * t10 * t19 * 9.0) + d2 * t13 * t16 * 9.0) + d3 * t11 * t18 * 9.0) + d3 * t12 * t17 * 9.0) + d4 * t10 * t20 * 9.0) + d4 * t14 * t16 * 9.0) + d5 * t11 * t19 * 9.0) + d5 * t13 * t17 * 9.0) + d6 * t10 * t21 * 9.0) + d6 * t15 * t16 * 9.0) + d7 * t11 * t20 * 9.0) + d7 * t14 * t17 * 9.0) + d8 * t12 * t19 * 9.0) + d8 * t13 * t18 * 9.0) + d9 * t11 * t21 * 9.0) + d9 * t15 * t17 * 9.0) + d10 * t12 * t20 * 9.0) + d10 * t14 * t18 * 9.0) + d11 * t12 * t21 * 9.0) + d11 * t15 * t18 * 9.0) + d12 * t13 * t20 * 9.0) + d12 * t14 * t19 * 9.0) + d13 * t13 * t21 * 9.0) + d13 * t15 * t19 * 9.0) + d14 * t14 * t21 * 9.0) + d14 * t15 * t20 * 9.0) + t2 * t10 * t16 * 8.0) + t3 * t11 * t17 * 8.0) + t4 * t12 * t18 * 8.0) + t5 * t13 * t19 * 8.0) + t6 * t14 * t20 * 8.0) + t7 * t15 * t21 * 8.0);
    // 'Calc_beta0_beta1:138' et1 =
    // alpha0.*t2.*t10.*t16.*2.8e+1+alpha0.*t3.*t11.*t17.*2.8e+1+alpha0.*t4.*t12.*t18.*2.8e+1+alpha0.*t5.*t13.*t19.*2.8e+1+alpha0.*t6.*t14.*t20.*2.8e+1+alpha0.*t7.*t15.*t21.*2.8e+1+p0_vec1.*t2.*t16.*t0_vec1.*4.0e+1+p0_vec2.*t3.*t17.*t0_vec2.*4.0e+1+p0_vec3.*t4.*t18.*t0_vec3.*4.0e+1-p1_vec1.*t2.*t16.*t0_vec1.*4.0e+1+p0_vec4.*t5.*t19.*t0_vec4.*4.0e+1-p1_vec2.*t3.*t17.*t0_vec2.*4.0e+1+p0_vec5.*t6.*t20.*t0_vec5.*4.0e+1-p1_vec3.*t4.*t18.*t0_vec3.*4.0e+1+p0_vec6.*t7.*t21.*t0_vec6.*4.0e+1-p1_vec4.*t5.*t19.*t0_vec4.*4.0e+1-p1_vec5.*t6.*t20.*t0_vec5.*4.0e+1-p1_vec6.*t7.*t21.*t0_vec6.*4.0e+1+alpha1.*t2.*t0_vec1.*t1_vec1.^3.*1.2e+1+alpha1.*t3.*t0_vec2.*t1_vec2.^3.*1.2e+1+alpha1.*t4.*t0_vec3.*t1_vec3.^3.*1.2e+1+alpha1.*t5.*t0_vec4.*t1_vec4.^3.*1.2e+1+alpha1.*t6.*t0_vec5.*t1_vec5.^3.*1.2e+1+alpha1.*t7.*t0_vec6.*t1_vec6.^3.*1.2e+1+D_vec1.*D_vec2.*alpha0.*t10.*t17.*3.6e+1;
    // 'Calc_beta0_beta1:139' et2 =
    // D_vec1.*D_vec2.*alpha0.*t11.*t16.*3.6e+1+D_vec1.*D_vec3.*alpha0.*t10.*t18.*3.6e+1+D_vec1.*D_vec3.*alpha0.*t12.*t16.*3.6e+1+D_vec1.*D_vec4.*alpha0.*t10.*t19.*3.6e+1+D_vec1.*D_vec4.*alpha0.*t13.*t16.*3.6e+1+D_vec2.*D_vec3.*alpha0.*t11.*t18.*3.6e+1+D_vec2.*D_vec3.*alpha0.*t12.*t17.*3.6e+1+D_vec1.*D_vec5.*alpha0.*t10.*t20.*3.6e+1+D_vec1.*D_vec5.*alpha0.*t14.*t16.*3.6e+1+D_vec2.*D_vec4.*alpha0.*t11.*t19.*3.6e+1+D_vec2.*D_vec4.*alpha0.*t13.*t17.*3.6e+1+D_vec1.*D_vec6.*alpha0.*t10.*t21.*3.6e+1+D_vec1.*D_vec6.*alpha0.*t15.*t16.*3.6e+1+D_vec2.*D_vec5.*alpha0.*t11.*t20.*3.6e+1+D_vec2.*D_vec5.*alpha0.*t14.*t17.*3.6e+1+D_vec3.*D_vec4.*alpha0.*t12.*t19.*3.6e+1+D_vec3.*D_vec4.*alpha0.*t13.*t18.*3.6e+1+D_vec2.*D_vec6.*alpha0.*t11.*t21.*3.6e+1+D_vec2.*D_vec6.*alpha0.*t15.*t17.*3.6e+1+D_vec3.*D_vec5.*alpha0.*t12.*t20.*3.6e+1+D_vec3.*D_vec5.*alpha0.*t14.*t18.*3.6e+1+D_vec3.*D_vec6.*alpha0.*t12.*t21.*3.6e+1+D_vec3.*D_vec6.*alpha0.*t15.*t18.*3.6e+1+D_vec4.*D_vec5.*alpha0.*t13.*t20.*3.6e+1+D_vec4.*D_vec5.*alpha0.*t14.*t19.*3.6e+1;
    // 'Calc_beta0_beta1:140' et3 =
    // D_vec4.*D_vec6.*alpha0.*t13.*t21.*3.6e+1+D_vec4.*D_vec6.*alpha0.*t15.*t19.*3.6e+1+D_vec5.*D_vec6.*alpha0.*t14.*t21.*3.6e+1+D_vec5.*D_vec6.*alpha0.*t15.*t20.*3.6e+1+D_vec1.*D_vec2.*p0_vec1.*t17.*t0_vec1.*6.0e+1+D_vec1.*D_vec2.*p0_vec2.*t16.*t0_vec2.*6.0e+1+D_vec1.*D_vec3.*p0_vec1.*t18.*t0_vec1.*6.0e+1+D_vec1.*D_vec3.*p0_vec3.*t16.*t0_vec3.*6.0e+1+D_vec1.*D_vec4.*p0_vec1.*t19.*t0_vec1.*6.0e+1+D_vec2.*D_vec3.*p0_vec2.*t18.*t0_vec2.*6.0e+1+D_vec1.*D_vec5.*p0_vec1.*t20.*t0_vec1.*6.0e+1+D_vec2.*D_vec3.*p0_vec3.*t17.*t0_vec3.*6.0e+1+D_vec1.*D_vec4.*p0_vec4.*t16.*t0_vec4.*6.0e+1+D_vec2.*D_vec4.*p0_vec2.*t19.*t0_vec2.*6.0e+1+D_vec1.*D_vec6.*p0_vec1.*t21.*t0_vec1.*6.0e+1+D_vec2.*D_vec4.*p0_vec4.*t17.*t0_vec4.*6.0e+1+D_vec2.*D_vec5.*p0_vec2.*t20.*t0_vec2.*6.0e+1-D_vec1.*D_vec2.*p1_vec1.*t17.*t0_vec1.*6.0e+1+D_vec1.*D_vec5.*p0_vec5.*t16.*t0_vec5.*6.0e+1+D_vec3.*D_vec4.*p0_vec3.*t19.*t0_vec3.*6.0e+1-D_vec1.*D_vec2.*p1_vec2.*t16.*t0_vec2.*6.0e+1+D_vec2.*D_vec6.*p0_vec2.*t21.*t0_vec2.*6.0e+1+D_vec3.*D_vec4.*p0_vec4.*t18.*t0_vec4.*6.0e+1-D_vec1.*D_vec3.*p1_vec1.*t18.*t0_vec1.*6.0e+1;
    // 'Calc_beta0_beta1:141' et4 =
    // D_vec2.*D_vec5.*p0_vec5.*t17.*t0_vec5.*6.0e+1+D_vec3.*D_vec5.*p0_vec3.*t20.*t0_vec3.*6.0e+1+D_vec1.*D_vec6.*p0_vec6.*t16.*t0_vec6.*6.0e+1-D_vec1.*D_vec3.*p1_vec3.*t16.*t0_vec3.*6.0e+1-D_vec1.*D_vec4.*p1_vec1.*t19.*t0_vec1.*6.0e+1+D_vec3.*D_vec5.*p0_vec5.*t18.*t0_vec5.*6.0e+1+D_vec3.*D_vec6.*p0_vec3.*t21.*t0_vec3.*6.0e+1-D_vec2.*D_vec3.*p1_vec2.*t18.*t0_vec2.*6.0e+1+D_vec2.*D_vec6.*p0_vec6.*t17.*t0_vec6.*6.0e+1+D_vec4.*D_vec5.*p0_vec4.*t20.*t0_vec4.*6.0e+1-D_vec1.*D_vec5.*p1_vec1.*t20.*t0_vec1.*6.0e+1-D_vec2.*D_vec3.*p1_vec3.*t17.*t0_vec3.*6.0e+1+D_vec4.*D_vec5.*p0_vec5.*t19.*t0_vec5.*6.0e+1-D_vec1.*D_vec4.*p1_vec4.*t16.*t0_vec4.*6.0e+1-D_vec2.*D_vec4.*p1_vec2.*t19.*t0_vec2.*6.0e+1+D_vec3.*D_vec6.*p0_vec6.*t18.*t0_vec6.*6.0e+1+D_vec4.*D_vec6.*p0_vec4.*t21.*t0_vec4.*6.0e+1-D_vec1.*D_vec6.*p1_vec1.*t21.*t0_vec1.*6.0e+1-D_vec2.*D_vec4.*p1_vec4.*t17.*t0_vec4.*6.0e+1-D_vec2.*D_vec5.*p1_vec2.*t20.*t0_vec2.*6.0e+1+D_vec4.*D_vec6.*p0_vec6.*t19.*t0_vec6.*6.0e+1-D_vec1.*D_vec5.*p1_vec5.*t16.*t0_vec5.*6.0e+1-D_vec3.*D_vec4.*p1_vec3.*t19.*t0_vec3.*6.0e+1;
    // 'Calc_beta0_beta1:142' et5 =
    // D_vec5.*D_vec6.*p0_vec5.*t21.*t0_vec5.*6.0e+1-D_vec2.*D_vec6.*p1_vec2.*t21.*t0_vec2.*6.0e+1-D_vec3.*D_vec4.*p1_vec4.*t18.*t0_vec4.*6.0e+1+D_vec5.*D_vec6.*p0_vec6.*t20.*t0_vec6.*6.0e+1-D_vec2.*D_vec5.*p1_vec5.*t17.*t0_vec5.*6.0e+1-D_vec3.*D_vec5.*p1_vec3.*t20.*t0_vec3.*6.0e+1-D_vec1.*D_vec6.*p1_vec6.*t16.*t0_vec6.*6.0e+1-D_vec3.*D_vec5.*p1_vec5.*t18.*t0_vec5.*6.0e+1-D_vec3.*D_vec6.*p1_vec3.*t21.*t0_vec3.*6.0e+1-D_vec2.*D_vec6.*p1_vec6.*t17.*t0_vec6.*6.0e+1-D_vec4.*D_vec5.*p1_vec4.*t20.*t0_vec4.*6.0e+1-D_vec4.*D_vec5.*p1_vec5.*t19.*t0_vec5.*6.0e+1-D_vec3.*D_vec6.*p1_vec6.*t18.*t0_vec6.*6.0e+1-D_vec4.*D_vec6.*p1_vec4.*t21.*t0_vec4.*6.0e+1-D_vec4.*D_vec6.*p1_vec6.*t19.*t0_vec6.*6.0e+1-D_vec5.*D_vec6.*p1_vec5.*t21.*t0_vec5.*6.0e+1-D_vec5.*D_vec6.*p1_vec6.*t20.*t0_vec6.*6.0e+1+nk0_vec1.*t2.*t8.*t16.*t0_vec1.*8.0+nk0_vec2.*t3.*t8.*t17.*t0_vec2.*8.0+nk0_vec3.*t4.*t8.*t18.*t0_vec3.*8.0+nk0_vec4.*t5.*t8.*t19.*t0_vec4.*8.0+nk0_vec5.*t6.*t8.*t20.*t0_vec5.*8.0+nk0_vec6.*t7.*t8.*t21.*t0_vec6.*8.0;
    // 'Calc_beta0_beta1:143' et6 =
    // D_vec1.*D_vec2.*alpha1.*t17.*t0_vec1.*t1_vec1.*1.2e+1+D_vec1.*D_vec2.*alpha1.*t16.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec3.*alpha1.*t18.*t0_vec1.*t1_vec1.*1.2e+1+D_vec1.*D_vec3.*alpha1.*t16.*t0_vec3.*t1_vec3.*1.2e+1+D_vec1.*D_vec4.*alpha1.*t19.*t0_vec1.*t1_vec1.*1.2e+1+D_vec2.*D_vec3.*alpha1.*t18.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec5.*alpha1.*t20.*t0_vec1.*t1_vec1.*1.2e+1+D_vec2.*D_vec3.*alpha1.*t17.*t0_vec3.*t1_vec3.*1.2e+1+D_vec1.*D_vec4.*alpha1.*t16.*t0_vec4.*t1_vec4.*1.2e+1+D_vec2.*D_vec4.*alpha1.*t19.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec6.*alpha1.*t21.*t0_vec1.*t1_vec1.*1.2e+1+D_vec2.*D_vec4.*alpha1.*t17.*t0_vec4.*t1_vec4.*1.2e+1+D_vec2.*D_vec5.*alpha1.*t20.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec5.*alpha1.*t16.*t0_vec5.*t1_vec5.*1.2e+1+D_vec3.*D_vec4.*alpha1.*t19.*t0_vec3.*t1_vec3.*1.2e+1+D_vec2.*D_vec6.*alpha1.*t21.*t0_vec2.*t1_vec2.*1.2e+1+D_vec3.*D_vec4.*alpha1.*t18.*t0_vec4.*t1_vec4.*1.2e+1+D_vec2.*D_vec5.*alpha1.*t17.*t0_vec5.*t1_vec5.*1.2e+1+D_vec3.*D_vec5.*alpha1.*t20.*t0_vec3.*t1_vec3.*1.2e+1+D_vec1.*D_vec6.*alpha1.*t16.*t0_vec6.*t1_vec6.*1.2e+1+D_vec3.*D_vec5.*alpha1.*t18.*t0_vec5.*t1_vec5.*1.2e+1+D_vec3.*D_vec6.*alpha1.*t21.*t0_vec3.*t1_vec3.*1.2e+1;
    // 'Calc_beta0_beta1:144' et7 =
    // D_vec2.*D_vec6.*alpha1.*t17.*t0_vec6.*t1_vec6.*1.2e+1+D_vec4.*D_vec5.*alpha1.*t20.*t0_vec4.*t1_vec4.*1.2e+1+D_vec4.*D_vec5.*alpha1.*t19.*t0_vec5.*t1_vec5.*1.2e+1+D_vec3.*D_vec6.*alpha1.*t18.*t0_vec6.*t1_vec6.*1.2e+1+D_vec4.*D_vec6.*alpha1.*t21.*t0_vec4.*t1_vec4.*1.2e+1+D_vec4.*D_vec6.*alpha1.*t19.*t0_vec6.*t1_vec6.*1.2e+1+D_vec5.*D_vec6.*alpha1.*t21.*t0_vec5.*t1_vec5.*1.2e+1+D_vec5.*D_vec6.*alpha1.*t20.*t0_vec6.*t1_vec6.*1.2e+1+D_vec1.*D_vec2.*nk0_vec1.*t8.*t17.*t0_vec1.*9.0+D_vec1.*D_vec2.*nk0_vec2.*t8.*t16.*t0_vec2.*9.0+D_vec1.*D_vec3.*nk0_vec1.*t8.*t18.*t0_vec1.*9.0+D_vec1.*D_vec3.*nk0_vec3.*t8.*t16.*t0_vec3.*9.0+D_vec1.*D_vec4.*nk0_vec1.*t8.*t19.*t0_vec1.*9.0+D_vec2.*D_vec3.*nk0_vec2.*t8.*t18.*t0_vec2.*9.0+D_vec1.*D_vec5.*nk0_vec1.*t8.*t20.*t0_vec1.*9.0+D_vec2.*D_vec3.*nk0_vec3.*t8.*t17.*t0_vec3.*9.0+D_vec1.*D_vec4.*nk0_vec4.*t8.*t16.*t0_vec4.*9.0+D_vec2.*D_vec4.*nk0_vec2.*t8.*t19.*t0_vec2.*9.0+D_vec1.*D_vec6.*nk0_vec1.*t8.*t21.*t0_vec1.*9.0+D_vec2.*D_vec4.*nk0_vec4.*t8.*t17.*t0_vec4.*9.0+D_vec2.*D_vec5.*nk0_vec2.*t8.*t20.*t0_vec2.*9.0+D_vec1.*D_vec5.*nk0_vec5.*t8.*t16.*t0_vec5.*9.0;
    // 'Calc_beta0_beta1:145' et8 =
    // D_vec3.*D_vec4.*nk0_vec3.*t8.*t19.*t0_vec3.*9.0-D_vec1.*D_vec2.*nk1_vec1.*t9.*t17.*t0_vec1.*3.0+D_vec2.*D_vec6.*nk0_vec2.*t8.*t21.*t0_vec2.*9.0+D_vec3.*D_vec4.*nk0_vec4.*t8.*t18.*t0_vec4.*9.0-D_vec1.*D_vec2.*nk1_vec2.*t9.*t16.*t0_vec2.*3.0+D_vec2.*D_vec5.*nk0_vec5.*t8.*t17.*t0_vec5.*9.0+D_vec3.*D_vec5.*nk0_vec3.*t8.*t20.*t0_vec3.*9.0-D_vec1.*D_vec3.*nk1_vec1.*t9.*t18.*t0_vec1.*3.0+D_vec1.*D_vec6.*nk0_vec6.*t8.*t16.*t0_vec6.*9.0+D_vec3.*D_vec5.*nk0_vec5.*t8.*t18.*t0_vec5.*9.0+D_vec3.*D_vec6.*nk0_vec3.*t8.*t21.*t0_vec3.*9.0-D_vec1.*D_vec3.*nk1_vec3.*t9.*t16.*t0_vec3.*3.0-D_vec1.*D_vec4.*nk1_vec1.*t9.*t19.*t0_vec1.*3.0+D_vec2.*D_vec6.*nk0_vec6.*t8.*t17.*t0_vec6.*9.0+D_vec4.*D_vec5.*nk0_vec4.*t8.*t20.*t0_vec4.*9.0-D_vec2.*D_vec3.*nk1_vec2.*t9.*t18.*t0_vec2.*3.0+D_vec4.*D_vec5.*nk0_vec5.*t8.*t19.*t0_vec5.*9.0-D_vec1.*D_vec5.*nk1_vec1.*t9.*t20.*t0_vec1.*3.0-D_vec2.*D_vec3.*nk1_vec3.*t9.*t17.*t0_vec3.*3.0+D_vec3.*D_vec6.*nk0_vec6.*t8.*t18.*t0_vec6.*9.0+D_vec4.*D_vec6.*nk0_vec4.*t8.*t21.*t0_vec4.*9.0-D_vec1.*D_vec4.*nk1_vec4.*t9.*t16.*t0_vec4.*3.0;
    // 'Calc_beta0_beta1:146' et9 =
    // D_vec2.*D_vec4.*nk1_vec2.*t9.*t19.*t0_vec2.*-3.0-D_vec1.*D_vec6.*nk1_vec1.*t9.*t21.*t0_vec1.*3.0+D_vec4.*D_vec6.*nk0_vec6.*t8.*t19.*t0_vec6.*9.0-D_vec2.*D_vec4.*nk1_vec4.*t9.*t17.*t0_vec4.*3.0-D_vec2.*D_vec5.*nk1_vec2.*t9.*t20.*t0_vec2.*3.0+D_vec5.*D_vec6.*nk0_vec5.*t8.*t21.*t0_vec5.*9.0-D_vec1.*D_vec5.*nk1_vec5.*t9.*t16.*t0_vec5.*3.0-D_vec3.*D_vec4.*nk1_vec3.*t9.*t19.*t0_vec3.*3.0+D_vec5.*D_vec6.*nk0_vec6.*t8.*t20.*t0_vec6.*9.0-D_vec2.*D_vec6.*nk1_vec2.*t9.*t21.*t0_vec2.*3.0-D_vec3.*D_vec4.*nk1_vec4.*t9.*t18.*t0_vec4.*3.0-D_vec2.*D_vec5.*nk1_vec5.*t9.*t17.*t0_vec5.*3.0-D_vec3.*D_vec5.*nk1_vec3.*t9.*t20.*t0_vec3.*3.0-D_vec1.*D_vec6.*nk1_vec6.*t9.*t16.*t0_vec6.*3.0-D_vec3.*D_vec5.*nk1_vec5.*t9.*t18.*t0_vec5.*3.0-D_vec3.*D_vec6.*nk1_vec3.*t9.*t21.*t0_vec3.*3.0-D_vec2.*D_vec6.*nk1_vec6.*t9.*t17.*t0_vec6.*3.0-D_vec4.*D_vec5.*nk1_vec4.*t9.*t20.*t0_vec4.*3.0-D_vec4.*D_vec5.*nk1_vec5.*t9.*t19.*t0_vec5.*3.0-D_vec3.*D_vec6.*nk1_vec6.*t9.*t18.*t0_vec6.*3.0-D_vec4.*D_vec6.*nk1_vec4.*t9.*t21.*t0_vec4.*3.0-D_vec4.*D_vec6.*nk1_vec6.*t9.*t19.*t0_vec6.*3.0;
    // 'Calc_beta0_beta1:147' et10 =
    // D_vec5.*D_vec6.*nk1_vec5.*t9.*t21.*t0_vec5.*-3.0-D_vec5.*D_vec6.*nk1_vec6.*t9.*t20.*t0_vec6.*3.0-D_vec1.*D_vec2.*p0_vec1.*t0_vec2.*t1_vec1.*t1_vec2.*2.0e+1-D_vec1.*D_vec2.*p0_vec2.*t0_vec1.*t1_vec1.*t1_vec2.*2.0e+1-D_vec1.*D_vec3.*p0_vec1.*t0_vec3.*t1_vec1.*t1_vec3.*2.0e+1-D_vec1.*D_vec3.*p0_vec3.*t0_vec1.*t1_vec1.*t1_vec3.*2.0e+1-D_vec1.*D_vec4.*p0_vec1.*t0_vec4.*t1_vec1.*t1_vec4.*2.0e+1-D_vec1.*D_vec4.*p0_vec4.*t0_vec1.*t1_vec1.*t1_vec4.*2.0e+1-D_vec2.*D_vec3.*p0_vec2.*t0_vec3.*t1_vec2.*t1_vec3.*2.0e+1-D_vec2.*D_vec3.*p0_vec3.*t0_vec2.*t1_vec2.*t1_vec3.*2.0e+1-D_vec1.*D_vec5.*p0_vec1.*t0_vec5.*t1_vec1.*t1_vec5.*2.0e+1-D_vec1.*D_vec5.*p0_vec5.*t0_vec1.*t1_vec1.*t1_vec5.*2.0e+1-D_vec2.*D_vec4.*p0_vec2.*t0_vec4.*t1_vec2.*t1_vec4.*2.0e+1-D_vec2.*D_vec4.*p0_vec4.*t0_vec2.*t1_vec2.*t1_vec4.*2.0e+1+D_vec1.*D_vec2.*p1_vec1.*t0_vec2.*t1_vec1.*t1_vec2.*2.0e+1+D_vec1.*D_vec2.*p1_vec2.*t0_vec1.*t1_vec1.*t1_vec2.*2.0e+1-D_vec1.*D_vec6.*p0_vec1.*t0_vec6.*t1_vec1.*t1_vec6.*2.0e+1-D_vec1.*D_vec6.*p0_vec6.*t0_vec1.*t1_vec1.*t1_vec6.*2.0e+1-D_vec2.*D_vec5.*p0_vec2.*t0_vec5.*t1_vec2.*t1_vec5.*2.0e+1-D_vec2.*D_vec5.*p0_vec5.*t0_vec2.*t1_vec2.*t1_vec5.*2.0e+1;
    // 'Calc_beta0_beta1:148' et11 =
    // D_vec3.*D_vec4.*p0_vec3.*t0_vec4.*t1_vec3.*t1_vec4.*-2.0e+1-D_vec3.*D_vec4.*p0_vec4.*t0_vec3.*t1_vec3.*t1_vec4.*2.0e+1+D_vec1.*D_vec3.*p1_vec1.*t0_vec3.*t1_vec1.*t1_vec3.*2.0e+1+D_vec1.*D_vec3.*p1_vec3.*t0_vec1.*t1_vec1.*t1_vec3.*2.0e+1-D_vec2.*D_vec6.*p0_vec2.*t0_vec6.*t1_vec2.*t1_vec6.*2.0e+1-D_vec2.*D_vec6.*p0_vec6.*t0_vec2.*t1_vec2.*t1_vec6.*2.0e+1-D_vec3.*D_vec5.*p0_vec3.*t0_vec5.*t1_vec3.*t1_vec5.*2.0e+1-D_vec3.*D_vec5.*p0_vec5.*t0_vec3.*t1_vec3.*t1_vec5.*2.0e+1+D_vec1.*D_vec4.*p1_vec1.*t0_vec4.*t1_vec1.*t1_vec4.*2.0e+1+D_vec1.*D_vec4.*p1_vec4.*t0_vec1.*t1_vec1.*t1_vec4.*2.0e+1+D_vec2.*D_vec3.*p1_vec2.*t0_vec3.*t1_vec2.*t1_vec3.*2.0e+1+D_vec2.*D_vec3.*p1_vec3.*t0_vec2.*t1_vec2.*t1_vec3.*2.0e+1-D_vec3.*D_vec6.*p0_vec3.*t0_vec6.*t1_vec3.*t1_vec6.*2.0e+1-D_vec3.*D_vec6.*p0_vec6.*t0_vec3.*t1_vec3.*t1_vec6.*2.0e+1-D_vec4.*D_vec5.*p0_vec4.*t0_vec5.*t1_vec4.*t1_vec5.*2.0e+1-D_vec4.*D_vec5.*p0_vec5.*t0_vec4.*t1_vec4.*t1_vec5.*2.0e+1+D_vec1.*D_vec5.*p1_vec1.*t0_vec5.*t1_vec1.*t1_vec5.*2.0e+1+D_vec1.*D_vec5.*p1_vec5.*t0_vec1.*t1_vec1.*t1_vec5.*2.0e+1+D_vec2.*D_vec4.*p1_vec2.*t0_vec4.*t1_vec2.*t1_vec4.*2.0e+1+D_vec2.*D_vec4.*p1_vec4.*t0_vec2.*t1_vec2.*t1_vec4.*2.0e+1-D_vec4.*D_vec6.*p0_vec4.*t0_vec6.*t1_vec4.*t1_vec6.*2.0e+1;
    // 'Calc_beta0_beta1:149' et12 =
    // D_vec4.*D_vec6.*p0_vec6.*t0_vec4.*t1_vec4.*t1_vec6.*-2.0e+1+D_vec1.*D_vec6.*p1_vec1.*t0_vec6.*t1_vec1.*t1_vec6.*2.0e+1+D_vec1.*D_vec6.*p1_vec6.*t0_vec1.*t1_vec1.*t1_vec6.*2.0e+1+D_vec2.*D_vec5.*p1_vec2.*t0_vec5.*t1_vec2.*t1_vec5.*2.0e+1+D_vec2.*D_vec5.*p1_vec5.*t0_vec2.*t1_vec2.*t1_vec5.*2.0e+1+D_vec3.*D_vec4.*p1_vec3.*t0_vec4.*t1_vec3.*t1_vec4.*2.0e+1+D_vec3.*D_vec4.*p1_vec4.*t0_vec3.*t1_vec3.*t1_vec4.*2.0e+1-D_vec5.*D_vec6.*p0_vec5.*t0_vec6.*t1_vec5.*t1_vec6.*2.0e+1-D_vec5.*D_vec6.*p0_vec6.*t0_vec5.*t1_vec5.*t1_vec6.*2.0e+1+D_vec2.*D_vec6.*p1_vec2.*t0_vec6.*t1_vec2.*t1_vec6.*2.0e+1+D_vec2.*D_vec6.*p1_vec6.*t0_vec2.*t1_vec2.*t1_vec6.*2.0e+1+D_vec3.*D_vec5.*p1_vec3.*t0_vec5.*t1_vec3.*t1_vec5.*2.0e+1+D_vec3.*D_vec5.*p1_vec5.*t0_vec3.*t1_vec3.*t1_vec5.*2.0e+1+D_vec3.*D_vec6.*p1_vec3.*t0_vec6.*t1_vec3.*t1_vec6.*2.0e+1+D_vec3.*D_vec6.*p1_vec6.*t0_vec3.*t1_vec3.*t1_vec6.*2.0e+1+D_vec4.*D_vec5.*p1_vec4.*t0_vec5.*t1_vec4.*t1_vec5.*2.0e+1+D_vec4.*D_vec5.*p1_vec5.*t0_vec4.*t1_vec4.*t1_vec5.*2.0e+1+D_vec4.*D_vec6.*p1_vec4.*t0_vec6.*t1_vec4.*t1_vec6.*2.0e+1+D_vec4.*D_vec6.*p1_vec6.*t0_vec4.*t1_vec4.*t1_vec6.*2.0e+1+D_vec5.*D_vec6.*p1_vec5.*t0_vec6.*t1_vec5.*t1_vec6.*2.0e+1+D_vec5.*D_vec6.*p1_vec6.*t0_vec5.*t1_vec5.*t1_vec6.*2.0e+1;
    // 'Calc_beta0_beta1:150' et13 =
    // D_vec1.*D_vec2.*alpha0.*t0_vec1.*t0_vec2.*t1_vec1.*t1_vec2.*-1.6e+1-D_vec1.*D_vec3.*alpha0.*t0_vec1.*t0_vec3.*t1_vec1.*t1_vec3.*1.6e+1-D_vec1.*D_vec4.*alpha0.*t0_vec1.*t0_vec4.*t1_vec1.*t1_vec4.*1.6e+1-D_vec2.*D_vec3.*alpha0.*t0_vec2.*t0_vec3.*t1_vec2.*t1_vec3.*1.6e+1-D_vec1.*D_vec5.*alpha0.*t0_vec1.*t0_vec5.*t1_vec1.*t1_vec5.*1.6e+1-D_vec2.*D_vec4.*alpha0.*t0_vec2.*t0_vec4.*t1_vec2.*t1_vec4.*1.6e+1-D_vec1.*D_vec6.*alpha0.*t0_vec1.*t0_vec6.*t1_vec1.*t1_vec6.*1.6e+1-D_vec2.*D_vec5.*alpha0.*t0_vec2.*t0_vec5.*t1_vec2.*t1_vec5.*1.6e+1-D_vec3.*D_vec4.*alpha0.*t0_vec3.*t0_vec4.*t1_vec3.*t1_vec4.*1.6e+1-D_vec2.*D_vec6.*alpha0.*t0_vec2.*t0_vec6.*t1_vec2.*t1_vec6.*1.6e+1-D_vec3.*D_vec5.*alpha0.*t0_vec3.*t0_vec5.*t1_vec3.*t1_vec5.*1.6e+1-D_vec3.*D_vec6.*alpha0.*t0_vec3.*t0_vec6.*t1_vec3.*t1_vec6.*1.6e+1-D_vec4.*D_vec5.*alpha0.*t0_vec4.*t0_vec5.*t1_vec4.*t1_vec5.*1.6e+1-D_vec4.*D_vec6.*alpha0.*t0_vec4.*t0_vec6.*t1_vec4.*t1_vec6.*1.6e+1-D_vec5.*D_vec6.*alpha0.*t0_vec5.*t0_vec6.*t1_vec5.*t1_vec6.*1.6e+1-D_vec1.*D_vec2.*nk0_vec1.*t8.*t0_vec2.*t1_vec1.*t1_vec2-D_vec1.*D_vec2.*nk0_vec2.*t8.*t0_vec1.*t1_vec1.*t1_vec2-D_vec1.*D_vec3.*nk0_vec1.*t8.*t0_vec3.*t1_vec1.*t1_vec3;
    // 'Calc_beta0_beta1:151' et14 =
    // -D_vec1.*D_vec3.*nk0_vec3.*t8.*t0_vec1.*t1_vec1.*t1_vec3-D_vec1.*D_vec4.*nk0_vec1.*t8.*t0_vec4.*t1_vec1.*t1_vec4-D_vec1.*D_vec4.*nk0_vec4.*t8.*t0_vec1.*t1_vec1.*t1_vec4-D_vec2.*D_vec3.*nk0_vec2.*t8.*t0_vec3.*t1_vec2.*t1_vec3-D_vec2.*D_vec3.*nk0_vec3.*t8.*t0_vec2.*t1_vec2.*t1_vec3-D_vec1.*D_vec5.*nk0_vec1.*t8.*t0_vec5.*t1_vec1.*t1_vec5-D_vec1.*D_vec5.*nk0_vec5.*t8.*t0_vec1.*t1_vec1.*t1_vec5-D_vec2.*D_vec4.*nk0_vec2.*t8.*t0_vec4.*t1_vec2.*t1_vec4-D_vec2.*D_vec4.*nk0_vec4.*t8.*t0_vec2.*t1_vec2.*t1_vec4+D_vec1.*D_vec2.*nk1_vec1.*t9.*t0_vec2.*t1_vec1.*t1_vec2.*3.0+D_vec1.*D_vec2.*nk1_vec2.*t9.*t0_vec1.*t1_vec1.*t1_vec2.*3.0-D_vec1.*D_vec6.*nk0_vec1.*t8.*t0_vec6.*t1_vec1.*t1_vec6-D_vec1.*D_vec6.*nk0_vec6.*t8.*t0_vec1.*t1_vec1.*t1_vec6-D_vec2.*D_vec5.*nk0_vec2.*t8.*t0_vec5.*t1_vec2.*t1_vec5-D_vec2.*D_vec5.*nk0_vec5.*t8.*t0_vec2.*t1_vec2.*t1_vec5-D_vec3.*D_vec4.*nk0_vec3.*t8.*t0_vec4.*t1_vec3.*t1_vec4-D_vec3.*D_vec4.*nk0_vec4.*t8.*t0_vec3.*t1_vec3.*t1_vec4+D_vec1.*D_vec3.*nk1_vec1.*t9.*t0_vec3.*t1_vec1.*t1_vec3.*3.0+D_vec1.*D_vec3.*nk1_vec3.*t9.*t0_vec1.*t1_vec1.*t1_vec3.*3.0-D_vec2.*D_vec6.*nk0_vec2.*t8.*t0_vec6.*t1_vec2.*t1_vec6;
    // 'Calc_beta0_beta1:152' et15 =
    // -D_vec2.*D_vec6.*nk0_vec6.*t8.*t0_vec2.*t1_vec2.*t1_vec6-D_vec3.*D_vec5.*nk0_vec3.*t8.*t0_vec5.*t1_vec3.*t1_vec5-D_vec3.*D_vec5.*nk0_vec5.*t8.*t0_vec3.*t1_vec3.*t1_vec5+D_vec1.*D_vec4.*nk1_vec1.*t9.*t0_vec4.*t1_vec1.*t1_vec4.*3.0+D_vec1.*D_vec4.*nk1_vec4.*t9.*t0_vec1.*t1_vec1.*t1_vec4.*3.0+D_vec2.*D_vec3.*nk1_vec2.*t9.*t0_vec3.*t1_vec2.*t1_vec3.*3.0+D_vec2.*D_vec3.*nk1_vec3.*t9.*t0_vec2.*t1_vec2.*t1_vec3.*3.0-D_vec3.*D_vec6.*nk0_vec3.*t8.*t0_vec6.*t1_vec3.*t1_vec6-D_vec3.*D_vec6.*nk0_vec6.*t8.*t0_vec3.*t1_vec3.*t1_vec6-D_vec4.*D_vec5.*nk0_vec4.*t8.*t0_vec5.*t1_vec4.*t1_vec5-D_vec4.*D_vec5.*nk0_vec5.*t8.*t0_vec4.*t1_vec4.*t1_vec5+D_vec1.*D_vec5.*nk1_vec1.*t9.*t0_vec5.*t1_vec1.*t1_vec5.*3.0+D_vec1.*D_vec5.*nk1_vec5.*t9.*t0_vec1.*t1_vec1.*t1_vec5.*3.0+D_vec2.*D_vec4.*nk1_vec2.*t9.*t0_vec4.*t1_vec2.*t1_vec4.*3.0+D_vec2.*D_vec4.*nk1_vec4.*t9.*t0_vec2.*t1_vec2.*t1_vec4.*3.0-D_vec4.*D_vec6.*nk0_vec4.*t8.*t0_vec6.*t1_vec4.*t1_vec6-D_vec4.*D_vec6.*nk0_vec6.*t8.*t0_vec4.*t1_vec4.*t1_vec6+D_vec1.*D_vec6.*nk1_vec1.*t9.*t0_vec6.*t1_vec1.*t1_vec6.*3.0+D_vec1.*D_vec6.*nk1_vec6.*t9.*t0_vec1.*t1_vec1.*t1_vec6.*3.0+D_vec2.*D_vec5.*nk1_vec2.*t9.*t0_vec5.*t1_vec2.*t1_vec5.*3.0+D_vec2.*D_vec5.*nk1_vec5.*t9.*t0_vec2.*t1_vec2.*t1_vec5.*3.0;
    // 'Calc_beta0_beta1:153' et16 =
    // D_vec3.*D_vec4.*nk1_vec3.*t9.*t0_vec4.*t1_vec3.*t1_vec4.*3.0+D_vec3.*D_vec4.*nk1_vec4.*t9.*t0_vec3.*t1_vec3.*t1_vec4.*3.0-D_vec5.*D_vec6.*nk0_vec5.*t8.*t0_vec6.*t1_vec5.*t1_vec6-D_vec5.*D_vec6.*nk0_vec6.*t8.*t0_vec5.*t1_vec5.*t1_vec6+D_vec2.*D_vec6.*nk1_vec2.*t9.*t0_vec6.*t1_vec2.*t1_vec6.*3.0+D_vec2.*D_vec6.*nk1_vec6.*t9.*t0_vec2.*t1_vec2.*t1_vec6.*3.0+D_vec3.*D_vec5.*nk1_vec3.*t9.*t0_vec5.*t1_vec3.*t1_vec5.*3.0+D_vec3.*D_vec5.*nk1_vec5.*t9.*t0_vec3.*t1_vec3.*t1_vec5.*3.0+D_vec3.*D_vec6.*nk1_vec3.*t9.*t0_vec6.*t1_vec3.*t1_vec6.*3.0+D_vec3.*D_vec6.*nk1_vec6.*t9.*t0_vec3.*t1_vec3.*t1_vec6.*3.0+D_vec4.*D_vec5.*nk1_vec4.*t9.*t0_vec5.*t1_vec4.*t1_vec5.*3.0+D_vec4.*D_vec5.*nk1_vec5.*t9.*t0_vec4.*t1_vec4.*t1_vec5.*3.0+D_vec4.*D_vec6.*nk1_vec4.*t9.*t0_vec6.*t1_vec4.*t1_vec6.*3.0+D_vec4.*D_vec6.*nk1_vec6.*t9.*t0_vec4.*t1_vec4.*t1_vec6.*3.0+D_vec5.*D_vec6.*nk1_vec5.*t9.*t0_vec6.*t1_vec5.*t1_vec6.*3.0+D_vec5.*D_vec6.*nk1_vec6.*t9.*t0_vec5.*t1_vec5.*t1_vec6.*3.0;
    // 'Calc_beta0_beta1:154' beta0 =
    // -t89.*(et1+et2+et3+et4+et5+et6+et7+et8+et9+et10+et11+et12+et13+et14+et15+et16);
    beta0_tmp = d2 * alpha0;
    b_beta0_tmp = d3 * alpha0;
    c_beta0_tmp = d4 * alpha0;
    d_beta0_tmp = d5 * alpha0;
    e_beta0_tmp = d6 * alpha0;
    f_beta0_tmp = d7 * alpha0;
    g_beta0_tmp = d8 * alpha0;
    h_beta0_tmp = d9 * alpha0;
    i_beta0_tmp = d10 * alpha0;
    j_beta0_tmp = d11 * alpha0;
    k_beta0_tmp = d12 * alpha0;
    l_beta0_tmp = d13 * alpha0;
    m_beta0_tmp = d14 * alpha0;
    beta0_tmp_tmp = d * alpha1;
    b_beta0_tmp_tmp = d1 * alpha1;
    n_beta0_tmp = d3 * alpha1;
    o_beta0_tmp = d2 * alpha1;
    p_beta0_tmp = d5 * alpha1;
    q_beta0_tmp = d4 * alpha1;
    r_beta0_tmp = d8 * alpha1;
    s_beta0_tmp = d7 * alpha1;
    t_beta0_tmp = d6 * alpha1;
    u_beta0_tmp = d10 * alpha1;
    v_beta0_tmp = d9 * alpha1;
    w_beta0_tmp = d12 * alpha1;
    x_beta0_tmp = d11 * alpha1;
    y_beta0_tmp = d13 * alpha1;
    ab_beta0_tmp = d14 * alpha1;
    bb_beta0_tmp = d * in3[0];
    cb_beta0_tmp = d * in3[1];
    db_beta0_tmp = d1 * in3[0];
    eb_beta0_tmp = d1 * in3[2];
    fb_beta0_tmp = d2 * in3[0];
    gb_beta0_tmp = d2 * in3[3];
    hb_beta0_tmp = d3 * in3[1];
    ib_beta0_tmp = d3 * in3[2];
    jb_beta0_tmp = d4 * in3[0];
    kb_beta0_tmp = d4 * in3[4];
    lb_beta0_tmp = d5 * in3[1];
    mb_beta0_tmp = d5 * in3[3];
    nb_beta0_tmp = d * in6[0];
    ob_beta0_tmp = d * in6[1];
    pb_beta0_tmp = d6 * in3[0];
    qb_beta0_tmp = d6 * in3[5];
    rb_beta0_tmp = d7 * in3[1];
    sb_beta0_tmp = d7 * in3[4];
    tb_beta0_tmp = d8 * in3[2];
    ub_beta0_tmp = d8 * in3[3];
    vb_beta0_tmp = d1 * in6[0];
    wb_beta0_tmp = d1 * in6[2];
    xb_beta0_tmp = d9 * in3[1];
    yb_beta0_tmp = d9 * in3[5];
    ac_beta0_tmp = d10 * in3[2];
    bc_beta0_tmp = d10 * in3[4];
    cc_beta0_tmp = d2 * in6[0];
    dc_beta0_tmp = d2 * in6[3];
    ec_beta0_tmp = d3 * in6[1];
    fc_beta0_tmp = d3 * in6[2];
    gc_beta0_tmp = d11 * in3[2];
    hc_beta0_tmp = d11 * in3[5];
    ic_beta0_tmp = d12 * in3[3];
    jc_beta0_tmp = d12 * in3[4];
    kc_beta0_tmp = d4 * in6[0];
    lc_beta0_tmp = d4 * in6[4];
    mc_beta0_tmp = d5 * in6[1];
    nc_beta0_tmp = d5 * in6[3];
    oc_beta0_tmp = d13 * in3[3];
    pc_beta0_tmp = d13 * in3[5];
    qc_beta0_tmp = d6 * in6[0];
    rc_beta0_tmp = d6 * in6[5];
    sc_beta0_tmp = d7 * in6[1];
    tc_beta0_tmp = d7 * in6[4];
    uc_beta0_tmp = d8 * in6[2];
    vc_beta0_tmp = d8 * in6[3];
    wc_beta0_tmp = d14 * in3[4];
    xc_beta0_tmp = d14 * in3[5];
    yc_beta0_tmp = d9 * in6[1];
    ad_beta0_tmp = d9 * in6[5];
    bd_beta0_tmp = d10 * in6[2];
    cd_beta0_tmp = d10 * in6[4];
    dd_beta0_tmp = d11 * in6[2];
    ed_beta0_tmp = d11 * in6[5];
    fd_beta0_tmp = d12 * in6[3];
    gd_beta0_tmp = d12 * in6[4];
    hd_beta0_tmp = d13 * in6[3];
    id_beta0_tmp = d13 * in6[5];
    jd_beta0_tmp = d14 * in6[4];
    kd_beta0_tmp = d14 * in6[5];
    c_beta0_tmp_tmp = d * alpha0;
    ld_beta0_tmp = d * in5[0] * t8;
    md_beta0_tmp = d * in5[1] * t8;
    nd_beta0_tmp = d1 * in5[0] * t8;
    od_beta0_tmp = d2 * in5[0] * t8;
    pd_beta0_tmp = d2 * in5[3] * t8;
    qd_beta0_tmp = d3 * in5[1] * t8;
    rd_beta0_tmp = d3 * in5[2] * t8;
    sd_beta0_tmp = d4 * in5[0] * t8;
    td_beta0_tmp = d4 * in5[4] * t8;
    ud_beta0_tmp = d5 * in5[1] * t8;
    vd_beta0_tmp = d5 * in5[3] * t8;
    wd_beta0_tmp = d * in8[0] * t9;
    xd_beta0_tmp = d * in8[1] * t9;
    yd_beta0_tmp = d6 * in5[0] * t8;
    ae_beta0_tmp = d6 * in5[5] * t8;
    be_beta0_tmp = d7 * in5[1] * t8;
    ce_beta0_tmp = d7 * in5[4] * t8;
    de_beta0_tmp = d8 * in5[2] * t8;
    ee_beta0_tmp = d8 * in5[3] * t8;
    fe_beta0_tmp = d1 * in8[0] * t9;
    ge_beta0_tmp = d1 * in8[2] * t9;
    he_beta0_tmp = d9 * in5[1] * t8;
    ie_beta0_tmp = d10 * in5[2] * t8;
    je_beta0_tmp = d10 * in5[4] * t8;
    ke_beta0_tmp = d2 * in8[0] * t9;
    le_beta0_tmp = d2 * in8[3] * t9;
    me_beta0_tmp = d3 * in8[1] * t9;
    ne_beta0_tmp = d3 * in8[2] * t9;
    oe_beta0_tmp = d11 * in5[2] * t8;
    pe_beta0_tmp = d11 * in5[5] * t8;
    qe_beta0_tmp = d12 * in5[3] * t8;
    re_beta0_tmp = d12 * in5[4] * t8;
    se_beta0_tmp = d4 * in8[0] * t9;
    te_beta0_tmp = d4 * in8[4] * t9;
    ue_beta0_tmp = d5 * in8[1] * t9;
    ve_beta0_tmp = d5 * in8[3] * t9;
    we_beta0_tmp = d13 * in5[3] * t8;
    xe_beta0_tmp = d13 * in5[5] * t8;
    ye_beta0_tmp = d6 * in8[0] * t9;
    af_beta0_tmp = d6 * in8[5] * t9;
    bf_beta0_tmp = d7 * in8[1] * t9;
    cf_beta0_tmp = d7 * in8[4] * t9;
    df_beta0_tmp = d8 * in8[2] * t9;
    ef_beta0_tmp = d8 * in8[3] * t9;
    ff_beta0_tmp = d14 * in5[4] * t8;
    gf_beta0_tmp = d14 * in5[5] * t8;
    hf_beta0_tmp = d9 * in8[1] * t9;
    if_beta0_tmp = d9 * in8[5] * t9;
    jf_beta0_tmp = d10 * in8[2] * t9;
    kf_beta0_tmp = d10 * in8[4] * t9;
    lf_beta0_tmp = d11 * in8[2] * t9;
    mf_beta0_tmp = d11 * in8[5] * t9;
    nf_beta0_tmp = d12 * in8[3] * t9;
    of_beta0_tmp = d12 * in8[4] * t9;
    pf_beta0_tmp = d13 * in8[3] * t9;
    qf_beta0_tmp = d13 * in8[5] * t9;
    rf_beta0_tmp = d14 * in8[4] * t9;
    sf_beta0_tmp = d14 * in8[5] * t9;
    tf_beta0_tmp = alpha1 * t2;
    uf_beta0_tmp = alpha1 * t3;
    vf_beta0_tmp = alpha1 * t4;
    wf_beta0_tmp = alpha1 * t5;
    xf_beta0_tmp = alpha1 * t6;
    yf_beta0_tmp = alpha1 * t7;
    ag_beta0_tmp = in3[0] * t2;
    bg_beta0_tmp = in3[1] * t3;
    cg_beta0_tmp = in3[2] * t4;
    dg_beta0_tmp = in6[0] * t2;
    eg_beta0_tmp = in3[3] * t5;
    fg_beta0_tmp = in6[1] * t3;
    gg_beta0_tmp = in3[4] * t6;
    hg_beta0_tmp = in6[2] * t4;
    ig_beta0_tmp = in3[5] * t7;
    jg_beta0_tmp = in6[3] * t5;
    kg_beta0_tmp = in6[4] * t6;
    lg_beta0_tmp = in6[5] * t7;
    mg_beta0_tmp = alpha0 * t2;
    ng_beta0_tmp = alpha0 * t3;
    og_beta0_tmp = alpha0 * t4;
    pg_beta0_tmp = alpha0 * t5;
    qg_beta0_tmp = alpha0 * t6;
    rg_beta0_tmp = alpha0 * t7;
    sg_beta0_tmp = c_beta0_tmp_tmp * t10;
    tg_beta0_tmp = beta0_tmp * t13;
    ug_beta0_tmp = b_beta0_tmp * t12;
    vg_beta0_tmp = c_beta0_tmp * t14;
    wg_beta0_tmp = b_beta0_tmp * t11;
    xg_beta0_tmp = beta0_tmp * t10;
    yg_beta0_tmp = d_beta0_tmp * t13;
    ah_beta0_tmp = e_beta0_tmp * t15;
    bh_beta0_tmp = d_beta0_tmp * t11;
    ch_beta0_tmp = f_beta0_tmp * t14;
    dh_beta0_tmp = c_beta0_tmp * t10;
    eh_beta0_tmp = g_beta0_tmp * t13;
    fh_beta0_tmp = h_beta0_tmp * t15;
    gh_beta0_tmp = g_beta0_tmp * t12;
    hh_beta0_tmp = f_beta0_tmp * t11;
    ih_beta0_tmp = i_beta0_tmp * t14;
    jh_beta0_tmp = e_beta0_tmp * t10;
    kh_beta0_tmp = i_beta0_tmp * t12;
    lh_beta0_tmp = j_beta0_tmp * t15;
    mh_beta0_tmp = h_beta0_tmp * t11;
    nh_beta0_tmp = k_beta0_tmp * t14;
    oh_beta0_tmp = k_beta0_tmp * t13;
    ph_beta0_tmp = j_beta0_tmp * t12;
    qh_beta0_tmp = l_beta0_tmp * t15;
    rh_beta0_tmp = l_beta0_tmp * t13;
    sh_beta0_tmp = m_beta0_tmp * t15;
    th_beta0_tmp = m_beta0_tmp * t14;
    uh_beta0_tmp = d1 * in5[2] * t8;
    vh_beta0_tmp = d9 * in5[5] * t8;
    wh_beta0_tmp = cb_beta0_tmp * in4[0];
    xh_beta0_tmp = eb_beta0_tmp * in4[0];
    yh_beta0_tmp = gb_beta0_tmp * in4[0];
    ai_beta0_tmp = ib_beta0_tmp * in4[1];
    bi_beta0_tmp = kb_beta0_tmp * in4[0];
    ci_beta0_tmp = mb_beta0_tmp * in4[1];
    di_beta0_tmp = ob_beta0_tmp * in4[0];
    ei_beta0_tmp = qb_beta0_tmp * in4[0];
    fi_beta0_tmp = sb_beta0_tmp * in4[1];
    gi_beta0_tmp = ub_beta0_tmp * in4[2];
    hi_beta0_tmp = wb_beta0_tmp * in4[0];
    ii_beta0_tmp = yb_beta0_tmp * in4[1];
    ji_beta0_tmp = bc_beta0_tmp * in4[2];
    ki_beta0_tmp = dc_beta0_tmp * in4[0];
    li_beta0_tmp = fc_beta0_tmp * in4[1];
    mi_beta0_tmp = hc_beta0_tmp * in4[2];
    ni_beta0_tmp = jc_beta0_tmp * in4[3];
    oi_beta0_tmp = lc_beta0_tmp * in4[0];
    pi_beta0_tmp = nc_beta0_tmp * in4[1];
    qi_beta0_tmp = pc_beta0_tmp * in4[3];
    ri_beta0_tmp = rc_beta0_tmp * in4[0];
    si_beta0_tmp = tc_beta0_tmp * in4[1];
    ti_beta0_tmp = vc_beta0_tmp * in4[2];
    ui_beta0_tmp = xc_beta0_tmp * in4[4];
    vi_beta0_tmp = ad_beta0_tmp * in4[1];
    wi_beta0_tmp = cd_beta0_tmp * in4[2];
    xi_beta0_tmp = ed_beta0_tmp * in4[2];
    yi_beta0_tmp = gd_beta0_tmp * in4[3];
    aj_beta0_tmp = id_beta0_tmp * in4[3];
    bj_beta0_tmp = kd_beta0_tmp * in4[4];
    cj_beta0_tmp = md_beta0_tmp * in4[0];
    dj_beta0_tmp = pd_beta0_tmp * in4[0];
    ej_beta0_tmp = rd_beta0_tmp * in4[1];
    fj_beta0_tmp = td_beta0_tmp * in4[0];
    gj_beta0_tmp = vd_beta0_tmp * in4[1];
    hj_beta0_tmp = xd_beta0_tmp * in4[0];
    ij_beta0_tmp = ae_beta0_tmp * in4[0];
    jj_beta0_tmp = ce_beta0_tmp * in4[1];
    kj_beta0_tmp = ee_beta0_tmp * in4[2];
    lj_beta0_tmp = ge_beta0_tmp * in4[0];
    mj_beta0_tmp = je_beta0_tmp * in4[2];
    nj_beta0_tmp = le_beta0_tmp * in4[0];
    oj_beta0_tmp = ne_beta0_tmp * in4[1];
    pj_beta0_tmp = pe_beta0_tmp * in4[2];
    qj_beta0_tmp = re_beta0_tmp * in4[3];
    rj_beta0_tmp = te_beta0_tmp * in4[0];
    sj_beta0_tmp = ve_beta0_tmp * in4[1];
    tj_beta0_tmp = xe_beta0_tmp * in4[3];
    uj_beta0_tmp = af_beta0_tmp * in4[0];
    vj_beta0_tmp = cf_beta0_tmp * in4[1];
    wj_beta0_tmp = ef_beta0_tmp * in4[2];
    xj_beta0_tmp = gf_beta0_tmp * in4[4];
    yj_beta0_tmp = if_beta0_tmp * in4[1];
    ak_beta0_tmp = kf_beta0_tmp * in4[2];
    bk_beta0_tmp = mf_beta0_tmp * in4[2];
    ck_beta0_tmp = of_beta0_tmp * in4[3];
    dk_beta0_tmp = qf_beta0_tmp * in4[3];
    ek_beta0_tmp = sf_beta0_tmp * in4[4];
    fk_beta0_tmp = in9[0] * in9[2] * alpha0;
    gk_beta0_tmp = fk_beta0_tmp * t12;
    *beta0 =
        -t89 * (((((((((((((((((((((((((((((((((((((((mg_beta0_tmp * t10 * t16 * 28.0 +
                                                      ng_beta0_tmp * t11 * t17 * 28.0) +
                                                     og_beta0_tmp * t12 * t18 * 28.0) +
                                                    pg_beta0_tmp * t13 * t19 * 28.0) +
                                                   qg_beta0_tmp * t14 * t20 * 28.0) +
                                                  rg_beta0_tmp * t15 * t21 * 28.0) +
                                                 ag_beta0_tmp * t16 * in4[0] * 40.0) +
                                                bg_beta0_tmp * t17 * in4[1] * 40.0) +
                                               cg_beta0_tmp * t18 * in4[2] * 40.0) -
                                              dg_beta0_tmp * t16 * in4[0] * 40.0) +
                                             eg_beta0_tmp * t19 * in4[3] * 40.0) -
                                            fg_beta0_tmp * t17 * in4[1] * 40.0) +
                                           gg_beta0_tmp * t20 * in4[4] * 40.0) -
                                          hg_beta0_tmp * t18 * in4[2] * 40.0) +
                                         ig_beta0_tmp * t21 * in4[5] * 40.0) -
                                        jg_beta0_tmp * t19 * in4[3] * 40.0) -
                                       kg_beta0_tmp * t20 * in4[4] * 40.0) -
                                      lg_beta0_tmp * t21 * in4[5] * 40.0) +
                                     tf_beta0_tmp * in4[0] * std::pow(in7[0], 3.0) * 12.0) +
                                    uf_beta0_tmp * in4[1] * std::pow(in7[1], 3.0) * 12.0) +
                                   vf_beta0_tmp * in4[2] * std::pow(in7[2], 3.0) * 12.0) +
                                  wf_beta0_tmp * in4[3] * std::pow(in7[3], 3.0) * 12.0) +
                                 xf_beta0_tmp * in4[4] * std::pow(in7[4], 3.0) * 12.0) +
                                yf_beta0_tmp * in4[5] * std::pow(in7[5], 3.0) * 12.0) +
                               sg_beta0_tmp * t17 * 36.0) +
                              ((((((((((((((((((((((((c_beta0_tmp_tmp * t11 * t16 * 36.0 +
                                                      d1 * alpha0 * t10 * t18 * 36.0) +
                                                     gk_beta0_tmp * t16 * 36.0) +
                                                    xg_beta0_tmp * t19 * 36.0) +
                                                   tg_beta0_tmp * t16 * 36.0) +
                                                  wg_beta0_tmp * t18 * 36.0) +
                                                 ug_beta0_tmp * t17 * 36.0) +
                                                dh_beta0_tmp * t20 * 36.0) +
                                               vg_beta0_tmp * t16 * 36.0) +
                                              bh_beta0_tmp * t19 * 36.0) +
                                             yg_beta0_tmp * t17 * 36.0) +
                                            jh_beta0_tmp * t21 * 36.0) +
                                           ah_beta0_tmp * t16 * 36.0) +
                                          hh_beta0_tmp * t20 * 36.0) +
                                         ch_beta0_tmp * t17 * 36.0) +
                                        gh_beta0_tmp * t19 * 36.0) +
                                       eh_beta0_tmp * t18 * 36.0) +
                                      mh_beta0_tmp * t21 * 36.0) +
                                     fh_beta0_tmp * t17 * 36.0) +
                                    kh_beta0_tmp * t20 * 36.0) +
                                   ih_beta0_tmp * t18 * 36.0) +
                                  ph_beta0_tmp * t21 * 36.0) +
                                 lh_beta0_tmp * t18 * 36.0) +
                                oh_beta0_tmp * t20 * 36.0) +
                               nh_beta0_tmp * t19 * 36.0)) +
                             (((((((((((((((((((((((rh_beta0_tmp * t21 * 36.0 +
                                                    qh_beta0_tmp * t19 * 36.0) +
                                                   th_beta0_tmp * t21 * 36.0) +
                                                  sh_beta0_tmp * t20 * 36.0) +
                                                 bb_beta0_tmp * t17 * in4[0] * 60.0) +
                                                cb_beta0_tmp * t16 * in4[1] * 60.0) +
                                               db_beta0_tmp * t18 * in4[0] * 60.0) +
                                              eb_beta0_tmp * t16 * in4[2] * 60.0) +
                                             fb_beta0_tmp * t19 * in4[0] * 60.0) +
                                            hb_beta0_tmp * t18 * in4[1] * 60.0) +
                                           jb_beta0_tmp * t20 * in4[0] * 60.0) +
                                          ib_beta0_tmp * t17 * in4[2] * 60.0) +
                                         gb_beta0_tmp * t16 * in4[3] * 60.0) +
                                        lb_beta0_tmp * t19 * in4[1] * 60.0) +
                                       pb_beta0_tmp * t21 * in4[0] * 60.0) +
                                      mb_beta0_tmp * t17 * in4[3] * 60.0) +
                                     rb_beta0_tmp * t20 * in4[1] * 60.0) -
                                    nb_beta0_tmp * t17 * in4[0] * 60.0) +
                                   kb_beta0_tmp * t16 * in4[4] * 60.0) +
                                  tb_beta0_tmp * t19 * in4[2] * 60.0) -
                                 ob_beta0_tmp * t16 * in4[1] * 60.0) +
                                xb_beta0_tmp * t21 * in4[1] * 60.0) +
                               ub_beta0_tmp * t18 * in4[3] * 60.0) -
                              vb_beta0_tmp * t18 * in4[0] * 60.0)) +
                            ((((((((((((((((((((((sb_beta0_tmp * t17 * in4[4] * 60.0 +
                                                  ac_beta0_tmp * t20 * in4[2] * 60.0) +
                                                 qb_beta0_tmp * t16 * in4[5] * 60.0) -
                                                wb_beta0_tmp * t16 * in4[2] * 60.0) -
                                               cc_beta0_tmp * t19 * in4[0] * 60.0) +
                                              bc_beta0_tmp * t18 * in4[4] * 60.0) +
                                             gc_beta0_tmp * t21 * in4[2] * 60.0) -
                                            ec_beta0_tmp * t18 * in4[1] * 60.0) +
                                           yb_beta0_tmp * t17 * in4[5] * 60.0) +
                                          ic_beta0_tmp * t20 * in4[3] * 60.0) -
                                         kc_beta0_tmp * t20 * in4[0] * 60.0) -
                                        fc_beta0_tmp * t17 * in4[2] * 60.0) +
                                       jc_beta0_tmp * t19 * in4[4] * 60.0) -
                                      dc_beta0_tmp * t16 * in4[3] * 60.0) -
                                     mc_beta0_tmp * t19 * in4[1] * 60.0) +
                                    hc_beta0_tmp * t18 * in4[5] * 60.0) +
                                   oc_beta0_tmp * t21 * in4[3] * 60.0) -
                                  qc_beta0_tmp * t21 * in4[0] * 60.0) -
                                 nc_beta0_tmp * t17 * in4[3] * 60.0) -
                                sc_beta0_tmp * t20 * in4[1] * 60.0) +
                               pc_beta0_tmp * t19 * in4[5] * 60.0) -
                              lc_beta0_tmp * t16 * in4[4] * 60.0) -
                             uc_beta0_tmp * t19 * in4[2] * 60.0)) +
                           ((((((((((((((((((((((wc_beta0_tmp * t21 * in4[4] * 60.0 -
                                                 yc_beta0_tmp * t21 * in4[1] * 60.0) -
                                                vc_beta0_tmp * t18 * in4[3] * 60.0) +
                                               xc_beta0_tmp * t20 * in4[5] * 60.0) -
                                              tc_beta0_tmp * t17 * in4[4] * 60.0) -
                                             bd_beta0_tmp * t20 * in4[2] * 60.0) -
                                            rc_beta0_tmp * t16 * in4[5] * 60.0) -
                                           cd_beta0_tmp * t18 * in4[4] * 60.0) -
                                          dd_beta0_tmp * t21 * in4[2] * 60.0) -
                                         ad_beta0_tmp * t17 * in4[5] * 60.0) -
                                        fd_beta0_tmp * t20 * in4[3] * 60.0) -
                                       gd_beta0_tmp * t19 * in4[4] * 60.0) -
                                      ed_beta0_tmp * t18 * in4[5] * 60.0) -
                                     hd_beta0_tmp * t21 * in4[3] * 60.0) -
                                    id_beta0_tmp * t19 * in4[5] * 60.0) -
                                   jd_beta0_tmp * t21 * in4[4] * 60.0) -
                                  kd_beta0_tmp * t20 * in4[5] * 60.0) +
                                 in5[0] * t2 * t8 * t16 * in4[0] * 8.0) +
                                in5[1] * t3 * t8 * t17 * in4[1] * 8.0) +
                               in5[2] * t4 * t8 * t18 * in4[2] * 8.0) +
                              in5[3] * t5 * t8 * t19 * in4[3] * 8.0) +
                             in5[4] * t6 * t8 * t20 * in4[4] * 8.0) +
                            in5[5] * t7 * t8 * t21 * in4[5] * 8.0)) +
                          (((((((((((((((((((((beta0_tmp_tmp * t17 * in4[0] * in7[0] * 12.0 +
                                               beta0_tmp_tmp * t16 * in4[1] * in7[1] * 12.0) +
                                              b_beta0_tmp_tmp * t18 * in4[0] * in7[0] * 12.0) +
                                             b_beta0_tmp_tmp * t16 * in4[2] * in7[2] * 12.0) +
                                            o_beta0_tmp * t19 * in4[0] * in7[0] * 12.0) +
                                           n_beta0_tmp * t18 * in4[1] * in7[1] * 12.0) +
                                          q_beta0_tmp * t20 * in4[0] * in7[0] * 12.0) +
                                         n_beta0_tmp * t17 * in4[2] * in7[2] * 12.0) +
                                        o_beta0_tmp * t16 * in4[3] * in7[3] * 12.0) +
                                       p_beta0_tmp * t19 * in4[1] * in7[1] * 12.0) +
                                      t_beta0_tmp * t21 * in4[0] * in7[0] * 12.0) +
                                     p_beta0_tmp * t17 * in4[3] * in7[3] * 12.0) +
                                    s_beta0_tmp * t20 * in4[1] * in7[1] * 12.0) +
                                   q_beta0_tmp * t16 * in4[4] * in7[4] * 12.0) +
                                  r_beta0_tmp * t19 * in4[2] * in7[2] * 12.0) +
                                 v_beta0_tmp * t21 * in4[1] * in7[1] * 12.0) +
                                r_beta0_tmp * t18 * in4[3] * in7[3] * 12.0) +
                               s_beta0_tmp * t17 * in4[4] * in7[4] * 12.0) +
                              u_beta0_tmp * t20 * in4[2] * in7[2] * 12.0) +
                             t_beta0_tmp * t16 * in4[5] * in7[5] * 12.0) +
                            u_beta0_tmp * t18 * in4[4] * in7[4] * 12.0) +
                           x_beta0_tmp * t21 * in4[2] * in7[2] * 12.0)) +
                         (((((((((((((((((((((v_beta0_tmp * t17 * in4[5] * in7[5] * 12.0 +
                                              w_beta0_tmp * t20 * in4[3] * in7[3] * 12.0) +
                                             w_beta0_tmp * t19 * in4[4] * in7[4] * 12.0) +
                                            x_beta0_tmp * t18 * in4[5] * in7[5] * 12.0) +
                                           y_beta0_tmp * t21 * in4[3] * in7[3] * 12.0) +
                                          y_beta0_tmp * t19 * in4[5] * in7[5] * 12.0) +
                                         ab_beta0_tmp * t21 * in4[4] * in7[4] * 12.0) +
                                        ab_beta0_tmp * t20 * in4[5] * in7[5] * 12.0) +
                                       ld_beta0_tmp * t17 * in4[0] * 9.0) +
                                      md_beta0_tmp * t16 * in4[1] * 9.0) +
                                     nd_beta0_tmp * t18 * in4[0] * 9.0) +
                                    uh_beta0_tmp * t16 * in4[2] * 9.0) +
                                   od_beta0_tmp * t19 * in4[0] * 9.0) +
                                  qd_beta0_tmp * t18 * in4[1] * 9.0) +
                                 sd_beta0_tmp * t20 * in4[0] * 9.0) +
                                rd_beta0_tmp * t17 * in4[2] * 9.0) +
                               pd_beta0_tmp * t16 * in4[3] * 9.0) +
                              ud_beta0_tmp * t19 * in4[1] * 9.0) +
                             yd_beta0_tmp * t21 * in4[0] * 9.0) +
                            vd_beta0_tmp * t17 * in4[3] * 9.0) +
                           be_beta0_tmp * t20 * in4[1] * 9.0) +
                          td_beta0_tmp * t16 * in4[4] * 9.0)) +
                        (((((((((((((((((((((de_beta0_tmp * t19 * in4[2] * 9.0 -
                                             wd_beta0_tmp * t17 * in4[0] * 3.0) +
                                            he_beta0_tmp * t21 * in4[1] * 9.0) +
                                           ee_beta0_tmp * t18 * in4[3] * 9.0) -
                                          xd_beta0_tmp * t16 * in4[1] * 3.0) +
                                         ce_beta0_tmp * t17 * in4[4] * 9.0) +
                                        ie_beta0_tmp * t20 * in4[2] * 9.0) -
                                       fe_beta0_tmp * t18 * in4[0] * 3.0) +
                                      ae_beta0_tmp * t16 * in4[5] * 9.0) +
                                     je_beta0_tmp * t18 * in4[4] * 9.0) +
                                    oe_beta0_tmp * t21 * in4[2] * 9.0) -
                                   ge_beta0_tmp * t16 * in4[2] * 3.0) -
                                  ke_beta0_tmp * t19 * in4[0] * 3.0) +
                                 vh_beta0_tmp * t17 * in4[5] * 9.0) +
                                qe_beta0_tmp * t20 * in4[3] * 9.0) -
                               me_beta0_tmp * t18 * in4[1] * 3.0) +
                              re_beta0_tmp * t19 * in4[4] * 9.0) -
                             se_beta0_tmp * t20 * in4[0] * 3.0) -
                            ne_beta0_tmp * t17 * in4[2] * 3.0) +
                           pe_beta0_tmp * t18 * in4[5] * 9.0) +
                          we_beta0_tmp * t21 * in4[3] * 9.0) -
                         le_beta0_tmp * t16 * in4[3] * 3.0)) +
                       (((((((((((((((((((((ue_beta0_tmp * t19 * in4[1] * -3.0 -
                                            ye_beta0_tmp * t21 * in4[0] * 3.0) +
                                           xe_beta0_tmp * t19 * in4[5] * 9.0) -
                                          ve_beta0_tmp * t17 * in4[3] * 3.0) -
                                         bf_beta0_tmp * t20 * in4[1] * 3.0) +
                                        ff_beta0_tmp * t21 * in4[4] * 9.0) -
                                       te_beta0_tmp * t16 * in4[4] * 3.0) -
                                      df_beta0_tmp * t19 * in4[2] * 3.0) +
                                     gf_beta0_tmp * t20 * in4[5] * 9.0) -
                                    hf_beta0_tmp * t21 * in4[1] * 3.0) -
                                   ef_beta0_tmp * t18 * in4[3] * 3.0) -
                                  cf_beta0_tmp * t17 * in4[4] * 3.0) -
                                 jf_beta0_tmp * t20 * in4[2] * 3.0) -
                                af_beta0_tmp * t16 * in4[5] * 3.0) -
                               kf_beta0_tmp * t18 * in4[4] * 3.0) -
                              lf_beta0_tmp * t21 * in4[2] * 3.0) -
                             if_beta0_tmp * t17 * in4[5] * 3.0) -
                            nf_beta0_tmp * t20 * in4[3] * 3.0) -
                           of_beta0_tmp * t19 * in4[4] * 3.0) -
                          mf_beta0_tmp * t18 * in4[5] * 3.0) -
                         pf_beta0_tmp * t21 * in4[3] * 3.0) -
                        qf_beta0_tmp * t19 * in4[5] * 3.0)) +
                      (((((((((((((((((((rf_beta0_tmp * t21 * in4[4] * -3.0 -
                                         sf_beta0_tmp * t20 * in4[5] * 3.0) -
                                        bb_beta0_tmp * in4[1] * in7[0] * in7[1] * 20.0) -
                                       wh_beta0_tmp * in7[0] * in7[1] * 20.0) -
                                      db_beta0_tmp * in4[2] * in7[0] * in7[2] * 20.0) -
                                     xh_beta0_tmp * in7[0] * in7[2] * 20.0) -
                                    fb_beta0_tmp * in4[3] * in7[0] * in7[3] * 20.0) -
                                   yh_beta0_tmp * in7[0] * in7[3] * 20.0) -
                                  hb_beta0_tmp * in4[2] * in7[1] * in7[2] * 20.0) -
                                 ai_beta0_tmp * in7[1] * in7[2] * 20.0) -
                                jb_beta0_tmp * in4[4] * in7[0] * in7[4] * 20.0) -
                               bi_beta0_tmp * in7[0] * in7[4] * 20.0) -
                              lb_beta0_tmp * in4[3] * in7[1] * in7[3] * 20.0) -
                             ci_beta0_tmp * in7[1] * in7[3] * 20.0) +
                            nb_beta0_tmp * in4[1] * in7[0] * in7[1] * 20.0) +
                           di_beta0_tmp * in7[0] * in7[1] * 20.0) -
                          pb_beta0_tmp * in4[5] * in7[0] * in7[5] * 20.0) -
                         ei_beta0_tmp * in7[0] * in7[5] * 20.0) -
                        rb_beta0_tmp * in4[4] * in7[1] * in7[4] * 20.0) -
                       fi_beta0_tmp * in7[1] * in7[4] * 20.0)) +
                     ((((((((((((((((((((tb_beta0_tmp * in4[3] * in7[2] * in7[3] * -20.0 -
                                         gi_beta0_tmp * in7[2] * in7[3] * 20.0) +
                                        vb_beta0_tmp * in4[2] * in7[0] * in7[2] * 20.0) +
                                       hi_beta0_tmp * in7[0] * in7[2] * 20.0) -
                                      xb_beta0_tmp * in4[5] * in7[1] * in7[5] * 20.0) -
                                     ii_beta0_tmp * in7[1] * in7[5] * 20.0) -
                                    ac_beta0_tmp * in4[4] * in7[2] * in7[4] * 20.0) -
                                   ji_beta0_tmp * in7[2] * in7[4] * 20.0) +
                                  cc_beta0_tmp * in4[3] * in7[0] * in7[3] * 20.0) +
                                 ki_beta0_tmp * in7[0] * in7[3] * 20.0) +
                                ec_beta0_tmp * in4[2] * in7[1] * in7[2] * 20.0) +
                               li_beta0_tmp * in7[1] * in7[2] * 20.0) -
                              gc_beta0_tmp * in4[5] * in7[2] * in7[5] * 20.0) -
                             mi_beta0_tmp * in7[2] * in7[5] * 20.0) -
                            ic_beta0_tmp * in4[4] * in7[3] * in7[4] * 20.0) -
                           ni_beta0_tmp * in7[3] * in7[4] * 20.0) +
                          kc_beta0_tmp * in4[4] * in7[0] * in7[4] * 20.0) +
                         oi_beta0_tmp * in7[0] * in7[4] * 20.0) +
                        mc_beta0_tmp * in4[3] * in7[1] * in7[3] * 20.0) +
                       pi_beta0_tmp * in7[1] * in7[3] * 20.0) -
                      oc_beta0_tmp * in4[5] * in7[3] * in7[5] * 20.0)) +
                    ((((((((((((((((((((qi_beta0_tmp * in7[3] * in7[5] * -20.0 +
                                        qc_beta0_tmp * in4[5] * in7[0] * in7[5] * 20.0) +
                                       ri_beta0_tmp * in7[0] * in7[5] * 20.0) +
                                      sc_beta0_tmp * in4[4] * in7[1] * in7[4] * 20.0) +
                                     si_beta0_tmp * in7[1] * in7[4] * 20.0) +
                                    uc_beta0_tmp * in4[3] * in7[2] * in7[3] * 20.0) +
                                   ti_beta0_tmp * in7[2] * in7[3] * 20.0) -
                                  wc_beta0_tmp * in4[5] * in7[4] * in7[5] * 20.0) -
                                 ui_beta0_tmp * in7[4] * in7[5] * 20.0) +
                                yc_beta0_tmp * in4[5] * in7[1] * in7[5] * 20.0) +
                               vi_beta0_tmp * in7[1] * in7[5] * 20.0) +
                              bd_beta0_tmp * in4[4] * in7[2] * in7[4] * 20.0) +
                             wi_beta0_tmp * in7[2] * in7[4] * 20.0) +
                            dd_beta0_tmp * in4[5] * in7[2] * in7[5] * 20.0) +
                           xi_beta0_tmp * in7[2] * in7[5] * 20.0) +
                          fd_beta0_tmp * in4[4] * in7[3] * in7[4] * 20.0) +
                         yi_beta0_tmp * in7[3] * in7[4] * 20.0) +
                        hd_beta0_tmp * in4[5] * in7[3] * in7[5] * 20.0) +
                       aj_beta0_tmp * in7[3] * in7[5] * 20.0) +
                      jd_beta0_tmp * in4[5] * in7[4] * in7[5] * 20.0) +
                     bj_beta0_tmp * in7[4] * in7[5] * 20.0)) +
                   (((((((((((((((((c_beta0_tmp_tmp * in4[0] * in4[1] * in7[0] * in7[1] * -16.0 -
                                    fk_beta0_tmp * in4[0] * in4[2] * in7[0] * in7[2] * 16.0) -
                                   beta0_tmp * in4[0] * in4[3] * in7[0] * in7[3] * 16.0) -
                                  b_beta0_tmp * in4[1] * in4[2] * in7[1] * in7[2] * 16.0) -
                                 c_beta0_tmp * in4[0] * in4[4] * in7[0] * in7[4] * 16.0) -
                                d_beta0_tmp * in4[1] * in4[3] * in7[1] * in7[3] * 16.0) -
                               e_beta0_tmp * in4[0] * in4[5] * in7[0] * in7[5] * 16.0) -
                              f_beta0_tmp * in4[1] * in4[4] * in7[1] * in7[4] * 16.0) -
                             g_beta0_tmp * in4[2] * in4[3] * in7[2] * in7[3] * 16.0) -
                            h_beta0_tmp * in4[1] * in4[5] * in7[1] * in7[5] * 16.0) -
                           i_beta0_tmp * in4[2] * in4[4] * in7[2] * in7[4] * 16.0) -
                          j_beta0_tmp * in4[2] * in4[5] * in7[2] * in7[5] * 16.0) -
                         k_beta0_tmp * in4[3] * in4[4] * in7[3] * in7[4] * 16.0) -
                        l_beta0_tmp * in4[3] * in4[5] * in7[3] * in7[5] * 16.0) -
                       m_beta0_tmp * in4[4] * in4[5] * in7[4] * in7[5] * 16.0) -
                      ld_beta0_tmp * in4[1] * in7[0] * in7[1]) -
                     cj_beta0_tmp * in7[0] * in7[1]) -
                    nd_beta0_tmp * in4[2] * in7[0] * in7[2])) +
                  (((((((((((((((((((-in9[0] * in9[2] * in5[2] * t8 * in4[0] * in7[0] * in7[2] -
                                     od_beta0_tmp * in4[3] * in7[0] * in7[3]) -
                                    dj_beta0_tmp * in7[0] * in7[3]) -
                                   qd_beta0_tmp * in4[2] * in7[1] * in7[2]) -
                                  ej_beta0_tmp * in7[1] * in7[2]) -
                                 sd_beta0_tmp * in4[4] * in7[0] * in7[4]) -
                                fj_beta0_tmp * in7[0] * in7[4]) -
                               ud_beta0_tmp * in4[3] * in7[1] * in7[3]) -
                              gj_beta0_tmp * in7[1] * in7[3]) +
                             wd_beta0_tmp * in4[1] * in7[0] * in7[1] * 3.0) +
                            hj_beta0_tmp * in7[0] * in7[1] * 3.0) -
                           yd_beta0_tmp * in4[5] * in7[0] * in7[5]) -
                          ij_beta0_tmp * in7[0] * in7[5]) -
                         be_beta0_tmp * in4[4] * in7[1] * in7[4]) -
                        jj_beta0_tmp * in7[1] * in7[4]) -
                       de_beta0_tmp * in4[3] * in7[2] * in7[3]) -
                      kj_beta0_tmp * in7[2] * in7[3]) +
                     fe_beta0_tmp * in4[2] * in7[0] * in7[2] * 3.0) +
                    lj_beta0_tmp * in7[0] * in7[2] * 3.0) -
                   he_beta0_tmp * in4[5] * in7[1] * in7[5])) +
                 ((((((((((((((((((((-in9[1] * in9[5] * in5[5] * t8 * in4[1] * in7[1] * in7[5] -
                                     ie_beta0_tmp * in4[4] * in7[2] * in7[4]) -
                                    mj_beta0_tmp * in7[2] * in7[4]) +
                                   ke_beta0_tmp * in4[3] * in7[0] * in7[3] * 3.0) +
                                  nj_beta0_tmp * in7[0] * in7[3] * 3.0) +
                                 me_beta0_tmp * in4[2] * in7[1] * in7[2] * 3.0) +
                                oj_beta0_tmp * in7[1] * in7[2] * 3.0) -
                               oe_beta0_tmp * in4[5] * in7[2] * in7[5]) -
                              pj_beta0_tmp * in7[2] * in7[5]) -
                             qe_beta0_tmp * in4[4] * in7[3] * in7[4]) -
                            qj_beta0_tmp * in7[3] * in7[4]) +
                           se_beta0_tmp * in4[4] * in7[0] * in7[4] * 3.0) +
                          rj_beta0_tmp * in7[0] * in7[4] * 3.0) +
                         ue_beta0_tmp * in4[3] * in7[1] * in7[3] * 3.0) +
                        sj_beta0_tmp * in7[1] * in7[3] * 3.0) -
                       we_beta0_tmp * in4[5] * in7[3] * in7[5]) -
                      tj_beta0_tmp * in7[3] * in7[5]) +
                     ye_beta0_tmp * in4[5] * in7[0] * in7[5] * 3.0) +
                    uj_beta0_tmp * in7[0] * in7[5] * 3.0) +
                   bf_beta0_tmp * in4[4] * in7[1] * in7[4] * 3.0) +
                  vj_beta0_tmp * in7[1] * in7[4] * 3.0)) +
                (((((((((((((((df_beta0_tmp * in4[3] * in7[2] * in7[3] * 3.0 +
                               wj_beta0_tmp * in7[2] * in7[3] * 3.0) -
                              ff_beta0_tmp * in4[5] * in7[4] * in7[5]) -
                             xj_beta0_tmp * in7[4] * in7[5]) +
                            hf_beta0_tmp * in4[5] * in7[1] * in7[5] * 3.0) +
                           yj_beta0_tmp * in7[1] * in7[5] * 3.0) +
                          jf_beta0_tmp * in4[4] * in7[2] * in7[4] * 3.0) +
                         ak_beta0_tmp * in7[2] * in7[4] * 3.0) +
                        lf_beta0_tmp * in4[5] * in7[2] * in7[5] * 3.0) +
                       bk_beta0_tmp * in7[2] * in7[5] * 3.0) +
                      nf_beta0_tmp * in4[4] * in7[3] * in7[4] * 3.0) +
                     ck_beta0_tmp * in7[3] * in7[4] * 3.0) +
                    pf_beta0_tmp * in4[5] * in7[3] * in7[5] * 3.0) +
                   dk_beta0_tmp * in7[3] * in7[5] * 3.0) +
                  rf_beta0_tmp * in4[5] * in7[4] * in7[5] * 3.0) +
                 ek_beta0_tmp * in7[4] * in7[5] * 3.0));
    // 'Calc_beta0_beta1:155' if nargout > 1
    // 'Calc_beta0_beta1:156' et17 =
    // alpha1.*t2.*t10.*t16.*2.8e+1+alpha1.*t3.*t11.*t17.*2.8e+1+alpha1.*t4.*t12.*t18.*2.8e+1+alpha1.*t5.*t13.*t19.*2.8e+1+alpha1.*t6.*t14.*t20.*2.8e+1+alpha1.*t7.*t15.*t21.*2.8e+1+p0_vec1.*t2.*t10.*t1_vec1.*4.0e+1+p0_vec2.*t3.*t11.*t1_vec2.*4.0e+1+p0_vec3.*t4.*t12.*t1_vec3.*4.0e+1-p1_vec1.*t2.*t10.*t1_vec1.*4.0e+1+p0_vec4.*t5.*t13.*t1_vec4.*4.0e+1-p1_vec2.*t3.*t11.*t1_vec2.*4.0e+1+p0_vec5.*t6.*t14.*t1_vec5.*4.0e+1-p1_vec3.*t4.*t12.*t1_vec3.*4.0e+1+p0_vec6.*t7.*t15.*t1_vec6.*4.0e+1-p1_vec4.*t5.*t13.*t1_vec4.*4.0e+1-p1_vec5.*t6.*t14.*t1_vec5.*4.0e+1-p1_vec6.*t7.*t15.*t1_vec6.*4.0e+1+alpha0.*t2.*t0_vec1.^3.*t1_vec1.*1.2e+1+alpha0.*t3.*t0_vec2.^3.*t1_vec2.*1.2e+1+alpha0.*t4.*t0_vec3.^3.*t1_vec3.*1.2e+1+alpha0.*t5.*t0_vec4.^3.*t1_vec4.*1.2e+1+alpha0.*t6.*t0_vec5.^3.*t1_vec5.*1.2e+1+alpha0.*t7.*t0_vec6.^3.*t1_vec6.*1.2e+1+D_vec1.*D_vec2.*alpha1.*t10.*t17.*3.6e+1;
    // 'Calc_beta0_beta1:157' et18 =
    // D_vec1.*D_vec2.*alpha1.*t11.*t16.*3.6e+1+D_vec1.*D_vec3.*alpha1.*t10.*t18.*3.6e+1+D_vec1.*D_vec3.*alpha1.*t12.*t16.*3.6e+1+D_vec1.*D_vec4.*alpha1.*t10.*t19.*3.6e+1+D_vec1.*D_vec4.*alpha1.*t13.*t16.*3.6e+1+D_vec2.*D_vec3.*alpha1.*t11.*t18.*3.6e+1+D_vec2.*D_vec3.*alpha1.*t12.*t17.*3.6e+1+D_vec1.*D_vec5.*alpha1.*t10.*t20.*3.6e+1+D_vec1.*D_vec5.*alpha1.*t14.*t16.*3.6e+1+D_vec2.*D_vec4.*alpha1.*t11.*t19.*3.6e+1+D_vec2.*D_vec4.*alpha1.*t13.*t17.*3.6e+1+D_vec1.*D_vec6.*alpha1.*t10.*t21.*3.6e+1+D_vec1.*D_vec6.*alpha1.*t15.*t16.*3.6e+1+D_vec2.*D_vec5.*alpha1.*t11.*t20.*3.6e+1+D_vec2.*D_vec5.*alpha1.*t14.*t17.*3.6e+1+D_vec3.*D_vec4.*alpha1.*t12.*t19.*3.6e+1+D_vec3.*D_vec4.*alpha1.*t13.*t18.*3.6e+1+D_vec2.*D_vec6.*alpha1.*t11.*t21.*3.6e+1+D_vec2.*D_vec6.*alpha1.*t15.*t17.*3.6e+1+D_vec3.*D_vec5.*alpha1.*t12.*t20.*3.6e+1+D_vec3.*D_vec5.*alpha1.*t14.*t18.*3.6e+1+D_vec3.*D_vec6.*alpha1.*t12.*t21.*3.6e+1+D_vec3.*D_vec6.*alpha1.*t15.*t18.*3.6e+1+D_vec4.*D_vec5.*alpha1.*t13.*t20.*3.6e+1+D_vec4.*D_vec5.*alpha1.*t14.*t19.*3.6e+1;
    // 'Calc_beta0_beta1:158' et19 =
    // D_vec4.*D_vec6.*alpha1.*t13.*t21.*3.6e+1+D_vec4.*D_vec6.*alpha1.*t15.*t19.*3.6e+1+D_vec5.*D_vec6.*alpha1.*t14.*t21.*3.6e+1+D_vec5.*D_vec6.*alpha1.*t15.*t20.*3.6e+1+D_vec1.*D_vec2.*p0_vec1.*t11.*t1_vec1.*6.0e+1+D_vec1.*D_vec2.*p0_vec2.*t10.*t1_vec2.*6.0e+1+D_vec1.*D_vec3.*p0_vec1.*t12.*t1_vec1.*6.0e+1+D_vec1.*D_vec3.*p0_vec3.*t10.*t1_vec3.*6.0e+1+D_vec1.*D_vec4.*p0_vec1.*t13.*t1_vec1.*6.0e+1+D_vec2.*D_vec3.*p0_vec2.*t12.*t1_vec2.*6.0e+1+D_vec1.*D_vec5.*p0_vec1.*t14.*t1_vec1.*6.0e+1+D_vec2.*D_vec3.*p0_vec3.*t11.*t1_vec3.*6.0e+1+D_vec1.*D_vec4.*p0_vec4.*t10.*t1_vec4.*6.0e+1+D_vec2.*D_vec4.*p0_vec2.*t13.*t1_vec2.*6.0e+1+D_vec1.*D_vec6.*p0_vec1.*t15.*t1_vec1.*6.0e+1+D_vec2.*D_vec4.*p0_vec4.*t11.*t1_vec4.*6.0e+1+D_vec2.*D_vec5.*p0_vec2.*t14.*t1_vec2.*6.0e+1-D_vec1.*D_vec2.*p1_vec1.*t11.*t1_vec1.*6.0e+1+D_vec1.*D_vec5.*p0_vec5.*t10.*t1_vec5.*6.0e+1+D_vec3.*D_vec4.*p0_vec3.*t13.*t1_vec3.*6.0e+1-D_vec1.*D_vec2.*p1_vec2.*t10.*t1_vec2.*6.0e+1+D_vec2.*D_vec6.*p0_vec2.*t15.*t1_vec2.*6.0e+1+D_vec3.*D_vec4.*p0_vec4.*t12.*t1_vec4.*6.0e+1-D_vec1.*D_vec3.*p1_vec1.*t12.*t1_vec1.*6.0e+1;
    // 'Calc_beta0_beta1:159' et20 =
    // D_vec2.*D_vec5.*p0_vec5.*t11.*t1_vec5.*6.0e+1+D_vec3.*D_vec5.*p0_vec3.*t14.*t1_vec3.*6.0e+1+D_vec1.*D_vec6.*p0_vec6.*t10.*t1_vec6.*6.0e+1-D_vec1.*D_vec3.*p1_vec3.*t10.*t1_vec3.*6.0e+1-D_vec1.*D_vec4.*p1_vec1.*t13.*t1_vec1.*6.0e+1+D_vec3.*D_vec5.*p0_vec5.*t12.*t1_vec5.*6.0e+1+D_vec3.*D_vec6.*p0_vec3.*t15.*t1_vec3.*6.0e+1-D_vec2.*D_vec3.*p1_vec2.*t12.*t1_vec2.*6.0e+1+D_vec2.*D_vec6.*p0_vec6.*t11.*t1_vec6.*6.0e+1+D_vec4.*D_vec5.*p0_vec4.*t14.*t1_vec4.*6.0e+1-D_vec1.*D_vec5.*p1_vec1.*t14.*t1_vec1.*6.0e+1-D_vec2.*D_vec3.*p1_vec3.*t11.*t1_vec3.*6.0e+1+D_vec4.*D_vec5.*p0_vec5.*t13.*t1_vec5.*6.0e+1-D_vec1.*D_vec4.*p1_vec4.*t10.*t1_vec4.*6.0e+1-D_vec2.*D_vec4.*p1_vec2.*t13.*t1_vec2.*6.0e+1+D_vec3.*D_vec6.*p0_vec6.*t12.*t1_vec6.*6.0e+1+D_vec4.*D_vec6.*p0_vec4.*t15.*t1_vec4.*6.0e+1-D_vec1.*D_vec6.*p1_vec1.*t15.*t1_vec1.*6.0e+1-D_vec2.*D_vec4.*p1_vec4.*t11.*t1_vec4.*6.0e+1-D_vec2.*D_vec5.*p1_vec2.*t14.*t1_vec2.*6.0e+1+D_vec4.*D_vec6.*p0_vec6.*t13.*t1_vec6.*6.0e+1-D_vec1.*D_vec5.*p1_vec5.*t10.*t1_vec5.*6.0e+1-D_vec3.*D_vec4.*p1_vec3.*t13.*t1_vec3.*6.0e+1;
    // 'Calc_beta0_beta1:160' et21 =
    // D_vec5.*D_vec6.*p0_vec5.*t15.*t1_vec5.*6.0e+1-D_vec2.*D_vec6.*p1_vec2.*t15.*t1_vec2.*6.0e+1-D_vec3.*D_vec4.*p1_vec4.*t12.*t1_vec4.*6.0e+1+D_vec5.*D_vec6.*p0_vec6.*t14.*t1_vec6.*6.0e+1-D_vec2.*D_vec5.*p1_vec5.*t11.*t1_vec5.*6.0e+1-D_vec3.*D_vec5.*p1_vec3.*t14.*t1_vec3.*6.0e+1-D_vec1.*D_vec6.*p1_vec6.*t10.*t1_vec6.*6.0e+1-D_vec3.*D_vec5.*p1_vec5.*t12.*t1_vec5.*6.0e+1-D_vec3.*D_vec6.*p1_vec3.*t15.*t1_vec3.*6.0e+1-D_vec2.*D_vec6.*p1_vec6.*t11.*t1_vec6.*6.0e+1-D_vec4.*D_vec5.*p1_vec4.*t14.*t1_vec4.*6.0e+1-D_vec4.*D_vec5.*p1_vec5.*t13.*t1_vec5.*6.0e+1-D_vec3.*D_vec6.*p1_vec6.*t12.*t1_vec6.*6.0e+1-D_vec4.*D_vec6.*p1_vec4.*t15.*t1_vec4.*6.0e+1-D_vec4.*D_vec6.*p1_vec6.*t13.*t1_vec6.*6.0e+1-D_vec5.*D_vec6.*p1_vec5.*t15.*t1_vec5.*6.0e+1-D_vec5.*D_vec6.*p1_vec6.*t14.*t1_vec6.*6.0e+1-nk1_vec1.*t2.*t9.*t10.*t1_vec1.*8.0-nk1_vec2.*t3.*t9.*t11.*t1_vec2.*8.0-nk1_vec3.*t4.*t9.*t12.*t1_vec3.*8.0-nk1_vec4.*t5.*t9.*t13.*t1_vec4.*8.0-nk1_vec5.*t6.*t9.*t14.*t1_vec5.*8.0;
    // 'Calc_beta0_beta1:161' et22 =
    // nk1_vec6.*t7.*t9.*t15.*t1_vec6.*-8.0+D_vec1.*D_vec2.*alpha0.*t11.*t0_vec1.*t1_vec1.*1.2e+1+D_vec1.*D_vec2.*alpha0.*t10.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec3.*alpha0.*t12.*t0_vec1.*t1_vec1.*1.2e+1+D_vec1.*D_vec3.*alpha0.*t10.*t0_vec3.*t1_vec3.*1.2e+1+D_vec1.*D_vec4.*alpha0.*t13.*t0_vec1.*t1_vec1.*1.2e+1+D_vec2.*D_vec3.*alpha0.*t12.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec5.*alpha0.*t14.*t0_vec1.*t1_vec1.*1.2e+1+D_vec2.*D_vec3.*alpha0.*t11.*t0_vec3.*t1_vec3.*1.2e+1+D_vec1.*D_vec4.*alpha0.*t10.*t0_vec4.*t1_vec4.*1.2e+1+D_vec2.*D_vec4.*alpha0.*t13.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec6.*alpha0.*t15.*t0_vec1.*t1_vec1.*1.2e+1+D_vec2.*D_vec4.*alpha0.*t11.*t0_vec4.*t1_vec4.*1.2e+1+D_vec2.*D_vec5.*alpha0.*t14.*t0_vec2.*t1_vec2.*1.2e+1+D_vec1.*D_vec5.*alpha0.*t10.*t0_vec5.*t1_vec5.*1.2e+1+D_vec3.*D_vec4.*alpha0.*t13.*t0_vec3.*t1_vec3.*1.2e+1+D_vec2.*D_vec6.*alpha0.*t15.*t0_vec2.*t1_vec2.*1.2e+1+D_vec3.*D_vec4.*alpha0.*t12.*t0_vec4.*t1_vec4.*1.2e+1+D_vec2.*D_vec5.*alpha0.*t11.*t0_vec5.*t1_vec5.*1.2e+1+D_vec3.*D_vec5.*alpha0.*t14.*t0_vec3.*t1_vec3.*1.2e+1+D_vec1.*D_vec6.*alpha0.*t10.*t0_vec6.*t1_vec6.*1.2e+1+D_vec3.*D_vec5.*alpha0.*t12.*t0_vec5.*t1_vec5.*1.2e+1;
    // 'Calc_beta0_beta1:162' et23 =
    // D_vec3.*D_vec6.*alpha0.*t15.*t0_vec3.*t1_vec3.*1.2e+1+D_vec2.*D_vec6.*alpha0.*t11.*t0_vec6.*t1_vec6.*1.2e+1+D_vec4.*D_vec5.*alpha0.*t14.*t0_vec4.*t1_vec4.*1.2e+1+D_vec4.*D_vec5.*alpha0.*t13.*t0_vec5.*t1_vec5.*1.2e+1+D_vec3.*D_vec6.*alpha0.*t12.*t0_vec6.*t1_vec6.*1.2e+1+D_vec4.*D_vec6.*alpha0.*t15.*t0_vec4.*t1_vec4.*1.2e+1+D_vec4.*D_vec6.*alpha0.*t13.*t0_vec6.*t1_vec6.*1.2e+1+D_vec5.*D_vec6.*alpha0.*t15.*t0_vec5.*t1_vec5.*1.2e+1+D_vec5.*D_vec6.*alpha0.*t14.*t0_vec6.*t1_vec6.*1.2e+1+D_vec1.*D_vec2.*nk0_vec1.*t8.*t11.*t1_vec1.*3.0+D_vec1.*D_vec2.*nk0_vec2.*t8.*t10.*t1_vec2.*3.0+D_vec1.*D_vec3.*nk0_vec1.*t8.*t12.*t1_vec1.*3.0+D_vec1.*D_vec3.*nk0_vec3.*t8.*t10.*t1_vec3.*3.0+D_vec1.*D_vec4.*nk0_vec1.*t8.*t13.*t1_vec1.*3.0+D_vec2.*D_vec3.*nk0_vec2.*t8.*t12.*t1_vec2.*3.0+D_vec1.*D_vec5.*nk0_vec1.*t8.*t14.*t1_vec1.*3.0+D_vec2.*D_vec3.*nk0_vec3.*t8.*t11.*t1_vec3.*3.0+D_vec1.*D_vec4.*nk0_vec4.*t8.*t10.*t1_vec4.*3.0+D_vec2.*D_vec4.*nk0_vec2.*t8.*t13.*t1_vec2.*3.0+D_vec1.*D_vec6.*nk0_vec1.*t8.*t15.*t1_vec1.*3.0+D_vec2.*D_vec4.*nk0_vec4.*t8.*t11.*t1_vec4.*3.0+D_vec2.*D_vec5.*nk0_vec2.*t8.*t14.*t1_vec2.*3.0+D_vec1.*D_vec5.*nk0_vec5.*t8.*t10.*t1_vec5.*3.0;
    // 'Calc_beta0_beta1:163' et24 =
    // D_vec3.*D_vec4.*nk0_vec3.*t8.*t13.*t1_vec3.*3.0-D_vec1.*D_vec2.*nk1_vec1.*t9.*t11.*t1_vec1.*9.0+D_vec2.*D_vec6.*nk0_vec2.*t8.*t15.*t1_vec2.*3.0+D_vec3.*D_vec4.*nk0_vec4.*t8.*t12.*t1_vec4.*3.0-D_vec1.*D_vec2.*nk1_vec2.*t9.*t10.*t1_vec2.*9.0+D_vec2.*D_vec5.*nk0_vec5.*t8.*t11.*t1_vec5.*3.0+D_vec3.*D_vec5.*nk0_vec3.*t8.*t14.*t1_vec3.*3.0-D_vec1.*D_vec3.*nk1_vec1.*t9.*t12.*t1_vec1.*9.0+D_vec1.*D_vec6.*nk0_vec6.*t8.*t10.*t1_vec6.*3.0+D_vec3.*D_vec5.*nk0_vec5.*t8.*t12.*t1_vec5.*3.0+D_vec3.*D_vec6.*nk0_vec3.*t8.*t15.*t1_vec3.*3.0-D_vec1.*D_vec3.*nk1_vec3.*t9.*t10.*t1_vec3.*9.0-D_vec1.*D_vec4.*nk1_vec1.*t9.*t13.*t1_vec1.*9.0+D_vec2.*D_vec6.*nk0_vec6.*t8.*t11.*t1_vec6.*3.0+D_vec4.*D_vec5.*nk0_vec4.*t8.*t14.*t1_vec4.*3.0-D_vec2.*D_vec3.*nk1_vec2.*t9.*t12.*t1_vec2.*9.0+D_vec4.*D_vec5.*nk0_vec5.*t8.*t13.*t1_vec5.*3.0-D_vec1.*D_vec5.*nk1_vec1.*t9.*t14.*t1_vec1.*9.0-D_vec2.*D_vec3.*nk1_vec3.*t9.*t11.*t1_vec3.*9.0+D_vec3.*D_vec6.*nk0_vec6.*t8.*t12.*t1_vec6.*3.0+D_vec4.*D_vec6.*nk0_vec4.*t8.*t15.*t1_vec4.*3.0-D_vec1.*D_vec4.*nk1_vec4.*t9.*t10.*t1_vec4.*9.0;
    // 'Calc_beta0_beta1:164' et25 =
    // D_vec2.*D_vec4.*nk1_vec2.*t9.*t13.*t1_vec2.*-9.0-D_vec1.*D_vec6.*nk1_vec1.*t9.*t15.*t1_vec1.*9.0+D_vec4.*D_vec6.*nk0_vec6.*t8.*t13.*t1_vec6.*3.0-D_vec2.*D_vec4.*nk1_vec4.*t9.*t11.*t1_vec4.*9.0-D_vec2.*D_vec5.*nk1_vec2.*t9.*t14.*t1_vec2.*9.0+D_vec5.*D_vec6.*nk0_vec5.*t8.*t15.*t1_vec5.*3.0-D_vec1.*D_vec5.*nk1_vec5.*t9.*t10.*t1_vec5.*9.0-D_vec3.*D_vec4.*nk1_vec3.*t9.*t13.*t1_vec3.*9.0+D_vec5.*D_vec6.*nk0_vec6.*t8.*t14.*t1_vec6.*3.0-D_vec2.*D_vec6.*nk1_vec2.*t9.*t15.*t1_vec2.*9.0-D_vec3.*D_vec4.*nk1_vec4.*t9.*t12.*t1_vec4.*9.0-D_vec2.*D_vec5.*nk1_vec5.*t9.*t11.*t1_vec5.*9.0-D_vec3.*D_vec5.*nk1_vec3.*t9.*t14.*t1_vec3.*9.0-D_vec1.*D_vec6.*nk1_vec6.*t9.*t10.*t1_vec6.*9.0-D_vec3.*D_vec5.*nk1_vec5.*t9.*t12.*t1_vec5.*9.0-D_vec3.*D_vec6.*nk1_vec3.*t9.*t15.*t1_vec3.*9.0-D_vec2.*D_vec6.*nk1_vec6.*t9.*t11.*t1_vec6.*9.0-D_vec4.*D_vec5.*nk1_vec4.*t9.*t14.*t1_vec4.*9.0-D_vec4.*D_vec5.*nk1_vec5.*t9.*t13.*t1_vec5.*9.0-D_vec3.*D_vec6.*nk1_vec6.*t9.*t12.*t1_vec6.*9.0;
    // 'Calc_beta0_beta1:165' et26 =
    // D_vec4.*D_vec6.*nk1_vec4.*t9.*t15.*t1_vec4.*-9.0-D_vec4.*D_vec6.*nk1_vec6.*t9.*t13.*t1_vec6.*9.0-D_vec5.*D_vec6.*nk1_vec5.*t9.*t15.*t1_vec5.*9.0-D_vec5.*D_vec6.*nk1_vec6.*t9.*t14.*t1_vec6.*9.0-D_vec1.*D_vec2.*p0_vec1.*t0_vec1.*t0_vec2.*t1_vec2.*2.0e+1-D_vec1.*D_vec2.*p0_vec2.*t0_vec1.*t0_vec2.*t1_vec1.*2.0e+1-D_vec1.*D_vec3.*p0_vec1.*t0_vec1.*t0_vec3.*t1_vec3.*2.0e+1-D_vec1.*D_vec3.*p0_vec3.*t0_vec1.*t0_vec3.*t1_vec1.*2.0e+1-D_vec1.*D_vec4.*p0_vec1.*t0_vec1.*t0_vec4.*t1_vec4.*2.0e+1-D_vec1.*D_vec4.*p0_vec4.*t0_vec1.*t0_vec4.*t1_vec1.*2.0e+1-D_vec2.*D_vec3.*p0_vec2.*t0_vec2.*t0_vec3.*t1_vec3.*2.0e+1-D_vec2.*D_vec3.*p0_vec3.*t0_vec2.*t0_vec3.*t1_vec2.*2.0e+1-D_vec1.*D_vec5.*p0_vec1.*t0_vec1.*t0_vec5.*t1_vec5.*2.0e+1-D_vec1.*D_vec5.*p0_vec5.*t0_vec1.*t0_vec5.*t1_vec1.*2.0e+1-D_vec2.*D_vec4.*p0_vec2.*t0_vec2.*t0_vec4.*t1_vec4.*2.0e+1-D_vec2.*D_vec4.*p0_vec4.*t0_vec2.*t0_vec4.*t1_vec2.*2.0e+1+D_vec1.*D_vec2.*p1_vec1.*t0_vec1.*t0_vec2.*t1_vec2.*2.0e+1+D_vec1.*D_vec2.*p1_vec2.*t0_vec1.*t0_vec2.*t1_vec1.*2.0e+1-D_vec1.*D_vec6.*p0_vec1.*t0_vec1.*t0_vec6.*t1_vec6.*2.0e+1-D_vec1.*D_vec6.*p0_vec6.*t0_vec1.*t0_vec6.*t1_vec1.*2.0e+1;
    // 'Calc_beta0_beta1:166' et27 =
    // D_vec2.*D_vec5.*p0_vec2.*t0_vec2.*t0_vec5.*t1_vec5.*-2.0e+1-D_vec2.*D_vec5.*p0_vec5.*t0_vec2.*t0_vec5.*t1_vec2.*2.0e+1-D_vec3.*D_vec4.*p0_vec3.*t0_vec3.*t0_vec4.*t1_vec4.*2.0e+1-D_vec3.*D_vec4.*p0_vec4.*t0_vec3.*t0_vec4.*t1_vec3.*2.0e+1+D_vec1.*D_vec3.*p1_vec1.*t0_vec1.*t0_vec3.*t1_vec3.*2.0e+1+D_vec1.*D_vec3.*p1_vec3.*t0_vec1.*t0_vec3.*t1_vec1.*2.0e+1-D_vec2.*D_vec6.*p0_vec2.*t0_vec2.*t0_vec6.*t1_vec6.*2.0e+1-D_vec2.*D_vec6.*p0_vec6.*t0_vec2.*t0_vec6.*t1_vec2.*2.0e+1-D_vec3.*D_vec5.*p0_vec3.*t0_vec3.*t0_vec5.*t1_vec5.*2.0e+1-D_vec3.*D_vec5.*p0_vec5.*t0_vec3.*t0_vec5.*t1_vec3.*2.0e+1+D_vec1.*D_vec4.*p1_vec1.*t0_vec1.*t0_vec4.*t1_vec4.*2.0e+1+D_vec1.*D_vec4.*p1_vec4.*t0_vec1.*t0_vec4.*t1_vec1.*2.0e+1+D_vec2.*D_vec3.*p1_vec2.*t0_vec2.*t0_vec3.*t1_vec3.*2.0e+1+D_vec2.*D_vec3.*p1_vec3.*t0_vec2.*t0_vec3.*t1_vec2.*2.0e+1-D_vec3.*D_vec6.*p0_vec3.*t0_vec3.*t0_vec6.*t1_vec6.*2.0e+1-D_vec3.*D_vec6.*p0_vec6.*t0_vec3.*t0_vec6.*t1_vec3.*2.0e+1-D_vec4.*D_vec5.*p0_vec4.*t0_vec4.*t0_vec5.*t1_vec5.*2.0e+1-D_vec4.*D_vec5.*p0_vec5.*t0_vec4.*t0_vec5.*t1_vec4.*2.0e+1+D_vec1.*D_vec5.*p1_vec1.*t0_vec1.*t0_vec5.*t1_vec5.*2.0e+1+D_vec1.*D_vec5.*p1_vec5.*t0_vec1.*t0_vec5.*t1_vec1.*2.0e+1;
    // 'Calc_beta0_beta1:167' et28 =
    // D_vec2.*D_vec4.*p1_vec2.*t0_vec2.*t0_vec4.*t1_vec4.*2.0e+1+D_vec2.*D_vec4.*p1_vec4.*t0_vec2.*t0_vec4.*t1_vec2.*2.0e+1-D_vec4.*D_vec6.*p0_vec4.*t0_vec4.*t0_vec6.*t1_vec6.*2.0e+1-D_vec4.*D_vec6.*p0_vec6.*t0_vec4.*t0_vec6.*t1_vec4.*2.0e+1+D_vec1.*D_vec6.*p1_vec1.*t0_vec1.*t0_vec6.*t1_vec6.*2.0e+1+D_vec1.*D_vec6.*p1_vec6.*t0_vec1.*t0_vec6.*t1_vec1.*2.0e+1+D_vec2.*D_vec5.*p1_vec2.*t0_vec2.*t0_vec5.*t1_vec5.*2.0e+1+D_vec2.*D_vec5.*p1_vec5.*t0_vec2.*t0_vec5.*t1_vec2.*2.0e+1+D_vec3.*D_vec4.*p1_vec3.*t0_vec3.*t0_vec4.*t1_vec4.*2.0e+1+D_vec3.*D_vec4.*p1_vec4.*t0_vec3.*t0_vec4.*t1_vec3.*2.0e+1-D_vec5.*D_vec6.*p0_vec5.*t0_vec5.*t0_vec6.*t1_vec6.*2.0e+1-D_vec5.*D_vec6.*p0_vec6.*t0_vec5.*t0_vec6.*t1_vec5.*2.0e+1+D_vec2.*D_vec6.*p1_vec2.*t0_vec2.*t0_vec6.*t1_vec6.*2.0e+1+D_vec2.*D_vec6.*p1_vec6.*t0_vec2.*t0_vec6.*t1_vec2.*2.0e+1+D_vec3.*D_vec5.*p1_vec3.*t0_vec3.*t0_vec5.*t1_vec5.*2.0e+1+D_vec3.*D_vec5.*p1_vec5.*t0_vec3.*t0_vec5.*t1_vec3.*2.0e+1+D_vec3.*D_vec6.*p1_vec3.*t0_vec3.*t0_vec6.*t1_vec6.*2.0e+1+D_vec3.*D_vec6.*p1_vec6.*t0_vec3.*t0_vec6.*t1_vec3.*2.0e+1+D_vec4.*D_vec5.*p1_vec4.*t0_vec4.*t0_vec5.*t1_vec5.*2.0e+1+D_vec4.*D_vec5.*p1_vec5.*t0_vec4.*t0_vec5.*t1_vec4.*2.0e+1+D_vec4.*D_vec6.*p1_vec4.*t0_vec4.*t0_vec6.*t1_vec6.*2.0e+1;
    // 'Calc_beta0_beta1:168' et29 =
    // D_vec4.*D_vec6.*p1_vec6.*t0_vec4.*t0_vec6.*t1_vec4.*2.0e+1+D_vec5.*D_vec6.*p1_vec5.*t0_vec5.*t0_vec6.*t1_vec6.*2.0e+1+D_vec5.*D_vec6.*p1_vec6.*t0_vec5.*t0_vec6.*t1_vec5.*2.0e+1-D_vec1.*D_vec2.*alpha1.*t0_vec1.*t0_vec2.*t1_vec1.*t1_vec2.*1.6e+1-D_vec1.*D_vec3.*alpha1.*t0_vec1.*t0_vec3.*t1_vec1.*t1_vec3.*1.6e+1-D_vec1.*D_vec4.*alpha1.*t0_vec1.*t0_vec4.*t1_vec1.*t1_vec4.*1.6e+1-D_vec2.*D_vec3.*alpha1.*t0_vec2.*t0_vec3.*t1_vec2.*t1_vec3.*1.6e+1-D_vec1.*D_vec5.*alpha1.*t0_vec1.*t0_vec5.*t1_vec1.*t1_vec5.*1.6e+1-D_vec2.*D_vec4.*alpha1.*t0_vec2.*t0_vec4.*t1_vec2.*t1_vec4.*1.6e+1-D_vec1.*D_vec6.*alpha1.*t0_vec1.*t0_vec6.*t1_vec1.*t1_vec6.*1.6e+1-D_vec2.*D_vec5.*alpha1.*t0_vec2.*t0_vec5.*t1_vec2.*t1_vec5.*1.6e+1-D_vec3.*D_vec4.*alpha1.*t0_vec3.*t0_vec4.*t1_vec3.*t1_vec4.*1.6e+1-D_vec2.*D_vec6.*alpha1.*t0_vec2.*t0_vec6.*t1_vec2.*t1_vec6.*1.6e+1-D_vec3.*D_vec5.*alpha1.*t0_vec3.*t0_vec5.*t1_vec3.*t1_vec5.*1.6e+1-D_vec3.*D_vec6.*alpha1.*t0_vec3.*t0_vec6.*t1_vec3.*t1_vec6.*1.6e+1-D_vec4.*D_vec5.*alpha1.*t0_vec4.*t0_vec5.*t1_vec4.*t1_vec5.*1.6e+1-D_vec4.*D_vec6.*alpha1.*t0_vec4.*t0_vec6.*t1_vec4.*t1_vec6.*1.6e+1-D_vec5.*D_vec6.*alpha1.*t0_vec5.*t0_vec6.*t1_vec5.*t1_vec6.*1.6e+1;
    // 'Calc_beta0_beta1:169' et30 =
    // D_vec1.*D_vec2.*nk0_vec1.*t8.*t0_vec1.*t0_vec2.*t1_vec2.*-3.0-D_vec1.*D_vec2.*nk0_vec2.*t8.*t0_vec1.*t0_vec2.*t1_vec1.*3.0-D_vec1.*D_vec3.*nk0_vec1.*t8.*t0_vec1.*t0_vec3.*t1_vec3.*3.0-D_vec1.*D_vec3.*nk0_vec3.*t8.*t0_vec1.*t0_vec3.*t1_vec1.*3.0-D_vec1.*D_vec4.*nk0_vec1.*t8.*t0_vec1.*t0_vec4.*t1_vec4.*3.0-D_vec1.*D_vec4.*nk0_vec4.*t8.*t0_vec1.*t0_vec4.*t1_vec1.*3.0-D_vec2.*D_vec3.*nk0_vec2.*t8.*t0_vec2.*t0_vec3.*t1_vec3.*3.0-D_vec2.*D_vec3.*nk0_vec3.*t8.*t0_vec2.*t0_vec3.*t1_vec2.*3.0-D_vec1.*D_vec5.*nk0_vec1.*t8.*t0_vec1.*t0_vec5.*t1_vec5.*3.0-D_vec1.*D_vec5.*nk0_vec5.*t8.*t0_vec1.*t0_vec5.*t1_vec1.*3.0-D_vec2.*D_vec4.*nk0_vec2.*t8.*t0_vec2.*t0_vec4.*t1_vec4.*3.0-D_vec2.*D_vec4.*nk0_vec4.*t8.*t0_vec2.*t0_vec4.*t1_vec2.*3.0+D_vec1.*D_vec2.*nk1_vec1.*t9.*t0_vec1.*t0_vec2.*t1_vec2+D_vec1.*D_vec2.*nk1_vec2.*t9.*t0_vec1.*t0_vec2.*t1_vec1-D_vec1.*D_vec6.*nk0_vec1.*t8.*t0_vec1.*t0_vec6.*t1_vec6.*3.0-D_vec1.*D_vec6.*nk0_vec6.*t8.*t0_vec1.*t0_vec6.*t1_vec1.*3.0-D_vec2.*D_vec5.*nk0_vec2.*t8.*t0_vec2.*t0_vec5.*t1_vec5.*3.0-D_vec2.*D_vec5.*nk0_vec5.*t8.*t0_vec2.*t0_vec5.*t1_vec2.*3.0-D_vec3.*D_vec4.*nk0_vec3.*t8.*t0_vec3.*t0_vec4.*t1_vec4.*3.0-D_vec3.*D_vec4.*nk0_vec4.*t8.*t0_vec3.*t0_vec4.*t1_vec3.*3.0;
    // 'Calc_beta0_beta1:170' et31 =
    // D_vec1.*D_vec3.*nk1_vec1.*t9.*t0_vec1.*t0_vec3.*t1_vec3+D_vec1.*D_vec3.*nk1_vec3.*t9.*t0_vec1.*t0_vec3.*t1_vec1-D_vec2.*D_vec6.*nk0_vec2.*t8.*t0_vec2.*t0_vec6.*t1_vec6.*3.0-D_vec2.*D_vec6.*nk0_vec6.*t8.*t0_vec2.*t0_vec6.*t1_vec2.*3.0-D_vec3.*D_vec5.*nk0_vec3.*t8.*t0_vec3.*t0_vec5.*t1_vec5.*3.0-D_vec3.*D_vec5.*nk0_vec5.*t8.*t0_vec3.*t0_vec5.*t1_vec3.*3.0+D_vec1.*D_vec4.*nk1_vec1.*t9.*t0_vec1.*t0_vec4.*t1_vec4+D_vec1.*D_vec4.*nk1_vec4.*t9.*t0_vec1.*t0_vec4.*t1_vec1+D_vec2.*D_vec3.*nk1_vec2.*t9.*t0_vec2.*t0_vec3.*t1_vec3+D_vec2.*D_vec3.*nk1_vec3.*t9.*t0_vec2.*t0_vec3.*t1_vec2-D_vec3.*D_vec6.*nk0_vec3.*t8.*t0_vec3.*t0_vec6.*t1_vec6.*3.0-D_vec3.*D_vec6.*nk0_vec6.*t8.*t0_vec3.*t0_vec6.*t1_vec3.*3.0-D_vec4.*D_vec5.*nk0_vec4.*t8.*t0_vec4.*t0_vec5.*t1_vec5.*3.0-D_vec4.*D_vec5.*nk0_vec5.*t8.*t0_vec4.*t0_vec5.*t1_vec4.*3.0+D_vec1.*D_vec5.*nk1_vec1.*t9.*t0_vec1.*t0_vec5.*t1_vec5+D_vec1.*D_vec5.*nk1_vec5.*t9.*t0_vec1.*t0_vec5.*t1_vec1+D_vec2.*D_vec4.*nk1_vec2.*t9.*t0_vec2.*t0_vec4.*t1_vec4+D_vec2.*D_vec4.*nk1_vec4.*t9.*t0_vec2.*t0_vec4.*t1_vec2-D_vec4.*D_vec6.*nk0_vec4.*t8.*t0_vec4.*t0_vec6.*t1_vec6.*3.0-D_vec4.*D_vec6.*nk0_vec6.*t8.*t0_vec4.*t0_vec6.*t1_vec4.*3.0+D_vec1.*D_vec6.*nk1_vec1.*t9.*t0_vec1.*t0_vec6.*t1_vec6+D_vec1.*D_vec6.*nk1_vec6.*t9.*t0_vec1.*t0_vec6.*t1_vec1;
    // 'Calc_beta0_beta1:171' et32 =
    // D_vec2.*D_vec5.*nk1_vec2.*t9.*t0_vec2.*t0_vec5.*t1_vec5+D_vec2.*D_vec5.*nk1_vec5.*t9.*t0_vec2.*t0_vec5.*t1_vec2+D_vec3.*D_vec4.*nk1_vec3.*t9.*t0_vec3.*t0_vec4.*t1_vec4+D_vec3.*D_vec4.*nk1_vec4.*t9.*t0_vec3.*t0_vec4.*t1_vec3-D_vec5.*D_vec6.*nk0_vec5.*t8.*t0_vec5.*t0_vec6.*t1_vec6.*3.0-D_vec5.*D_vec6.*nk0_vec6.*t8.*t0_vec5.*t0_vec6.*t1_vec5.*3.0+D_vec2.*D_vec6.*nk1_vec2.*t9.*t0_vec2.*t0_vec6.*t1_vec6+D_vec2.*D_vec6.*nk1_vec6.*t9.*t0_vec2.*t0_vec6.*t1_vec2+D_vec3.*D_vec5.*nk1_vec3.*t9.*t0_vec3.*t0_vec5.*t1_vec5+D_vec3.*D_vec5.*nk1_vec5.*t9.*t0_vec3.*t0_vec5.*t1_vec3+D_vec3.*D_vec6.*nk1_vec3.*t9.*t0_vec3.*t0_vec6.*t1_vec6+D_vec3.*D_vec6.*nk1_vec6.*t9.*t0_vec3.*t0_vec6.*t1_vec3+D_vec4.*D_vec5.*nk1_vec4.*t9.*t0_vec4.*t0_vec5.*t1_vec5+D_vec4.*D_vec5.*nk1_vec5.*t9.*t0_vec4.*t0_vec5.*t1_vec4+D_vec4.*D_vec6.*nk1_vec4.*t9.*t0_vec4.*t0_vec6.*t1_vec6+D_vec4.*D_vec6.*nk1_vec6.*t9.*t0_vec4.*t0_vec6.*t1_vec4+D_vec5.*D_vec6.*nk1_vec5.*t9.*t0_vec5.*t0_vec6.*t1_vec6+D_vec5.*D_vec6.*nk1_vec6.*t9.*t0_vec5.*t0_vec6.*t1_vec5;
    // 'Calc_beta0_beta1:172' beta1 =
    // t89.*(et17+et18+et19+et20+et21+et22+et23+et24+et25+et26+et27+et28+et29+et30+et31+et32);
    *beta1 =
        t89 *
        (((((((((((((((((((((((((((((((((((((((tf_beta0_tmp * t10 * t16 * 28.0 +
                                               uf_beta0_tmp * t11 * t17 * 28.0) +
                                              vf_beta0_tmp * t12 * t18 * 28.0) +
                                             wf_beta0_tmp * t13 * t19 * 28.0) +
                                            xf_beta0_tmp * t14 * t20 * 28.0) +
                                           yf_beta0_tmp * t15 * t21 * 28.0) +
                                          ag_beta0_tmp * t10 * in7[0] * 40.0) +
                                         bg_beta0_tmp * t11 * in7[1] * 40.0) +
                                        cg_beta0_tmp * t12 * in7[2] * 40.0) -
                                       dg_beta0_tmp * t10 * in7[0] * 40.0) +
                                      eg_beta0_tmp * t13 * in7[3] * 40.0) -
                                     fg_beta0_tmp * t11 * in7[1] * 40.0) +
                                    gg_beta0_tmp * t14 * in7[4] * 40.0) -
                                   hg_beta0_tmp * t12 * in7[2] * 40.0) +
                                  ig_beta0_tmp * t15 * in7[5] * 40.0) -
                                 jg_beta0_tmp * t13 * in7[3] * 40.0) -
                                kg_beta0_tmp * t14 * in7[4] * 40.0) -
                               lg_beta0_tmp * t15 * in7[5] * 40.0) +
                              mg_beta0_tmp * std::pow(in4[0], 3.0) * in7[0] * 12.0) +
                             ng_beta0_tmp * std::pow(in4[1], 3.0) * in7[1] * 12.0) +
                            og_beta0_tmp * std::pow(in4[2], 3.0) * in7[2] * 12.0) +
                           pg_beta0_tmp * std::pow(in4[3], 3.0) * in7[3] * 12.0) +
                          qg_beta0_tmp * std::pow(in4[4], 3.0) * in7[4] * 12.0) +
                         rg_beta0_tmp * std::pow(in4[5], 3.0) * in7[5] * 12.0) +
                        beta0_tmp_tmp * t10 * t17 * 36.0) +
                       ((((((((((((((((((((((((beta0_tmp_tmp * t11 * t16 * 36.0 +
                                               b_beta0_tmp_tmp * t10 * t18 * 36.0) +
                                              in9[0] * in9[2] * alpha1 * t12 * t16 * 36.0) +
                                             o_beta0_tmp * t10 * t19 * 36.0) +
                                            o_beta0_tmp * t13 * t16 * 36.0) +
                                           n_beta0_tmp * t11 * t18 * 36.0) +
                                          n_beta0_tmp * t12 * t17 * 36.0) +
                                         q_beta0_tmp * t10 * t20 * 36.0) +
                                        q_beta0_tmp * t14 * t16 * 36.0) +
                                       p_beta0_tmp * t11 * t19 * 36.0) +
                                      p_beta0_tmp * t13 * t17 * 36.0) +
                                     t_beta0_tmp * t10 * t21 * 36.0) +
                                    t_beta0_tmp * t15 * t16 * 36.0) +
                                   s_beta0_tmp * t11 * t20 * 36.0) +
                                  s_beta0_tmp * t14 * t17 * 36.0) +
                                 r_beta0_tmp * t12 * t19 * 36.0) +
                                r_beta0_tmp * t13 * t18 * 36.0) +
                               v_beta0_tmp * t11 * t21 * 36.0) +
                              v_beta0_tmp * t15 * t17 * 36.0) +
                             u_beta0_tmp * t12 * t20 * 36.0) +
                            u_beta0_tmp * t14 * t18 * 36.0) +
                           x_beta0_tmp * t12 * t21 * 36.0) +
                          x_beta0_tmp * t15 * t18 * 36.0) +
                         w_beta0_tmp * t13 * t20 * 36.0) +
                        w_beta0_tmp * t14 * t19 * 36.0)) +
                      (((((((((((((((((((((((y_beta0_tmp * t13 * t21 * 36.0 +
                                             y_beta0_tmp * t15 * t19 * 36.0) +
                                            ab_beta0_tmp * t14 * t21 * 36.0) +
                                           ab_beta0_tmp * t15 * t20 * 36.0) +
                                          bb_beta0_tmp * t11 * in7[0] * 60.0) +
                                         cb_beta0_tmp * t10 * in7[1] * 60.0) +
                                        db_beta0_tmp * t12 * in7[0] * 60.0) +
                                       eb_beta0_tmp * t10 * in7[2] * 60.0) +
                                      fb_beta0_tmp * t13 * in7[0] * 60.0) +
                                     hb_beta0_tmp * t12 * in7[1] * 60.0) +
                                    jb_beta0_tmp * t14 * in7[0] * 60.0) +
                                   ib_beta0_tmp * t11 * in7[2] * 60.0) +
                                  gb_beta0_tmp * t10 * in7[3] * 60.0) +
                                 lb_beta0_tmp * t13 * in7[1] * 60.0) +
                                pb_beta0_tmp * t15 * in7[0] * 60.0) +
                               mb_beta0_tmp * t11 * in7[3] * 60.0) +
                              rb_beta0_tmp * t14 * in7[1] * 60.0) -
                             nb_beta0_tmp * t11 * in7[0] * 60.0) +
                            kb_beta0_tmp * t10 * in7[4] * 60.0) +
                           tb_beta0_tmp * t13 * in7[2] * 60.0) -
                          ob_beta0_tmp * t10 * in7[1] * 60.0) +
                         xb_beta0_tmp * t15 * in7[1] * 60.0) +
                        ub_beta0_tmp * t12 * in7[3] * 60.0) -
                       vb_beta0_tmp * t12 * in7[0] * 60.0)) +
                     ((((((((((((((((((((((sb_beta0_tmp * t11 * in7[4] * 60.0 +
                                           ac_beta0_tmp * t14 * in7[2] * 60.0) +
                                          qb_beta0_tmp * t10 * in7[5] * 60.0) -
                                         wb_beta0_tmp * t10 * in7[2] * 60.0) -
                                        cc_beta0_tmp * t13 * in7[0] * 60.0) +
                                       bc_beta0_tmp * t12 * in7[4] * 60.0) +
                                      gc_beta0_tmp * t15 * in7[2] * 60.0) -
                                     ec_beta0_tmp * t12 * in7[1] * 60.0) +
                                    yb_beta0_tmp * t11 * in7[5] * 60.0) +
                                   ic_beta0_tmp * t14 * in7[3] * 60.0) -
                                  kc_beta0_tmp * t14 * in7[0] * 60.0) -
                                 fc_beta0_tmp * t11 * in7[2] * 60.0) +
                                jc_beta0_tmp * t13 * in7[4] * 60.0) -
                               dc_beta0_tmp * t10 * in7[3] * 60.0) -
                              mc_beta0_tmp * t13 * in7[1] * 60.0) +
                             hc_beta0_tmp * t12 * in7[5] * 60.0) +
                            oc_beta0_tmp * t15 * in7[3] * 60.0) -
                           qc_beta0_tmp * t15 * in7[0] * 60.0) -
                          nc_beta0_tmp * t11 * in7[3] * 60.0) -
                         sc_beta0_tmp * t14 * in7[1] * 60.0) +
                        pc_beta0_tmp * t13 * in7[5] * 60.0) -
                       lc_beta0_tmp * t10 * in7[4] * 60.0) -
                      uc_beta0_tmp * t13 * in7[2] * 60.0)) +
                    (((((((((((((((((((((wc_beta0_tmp * t15 * in7[4] * 60.0 -
                                         yc_beta0_tmp * t15 * in7[1] * 60.0) -
                                        vc_beta0_tmp * t12 * in7[3] * 60.0) +
                                       xc_beta0_tmp * t14 * in7[5] * 60.0) -
                                      tc_beta0_tmp * t11 * in7[4] * 60.0) -
                                     bd_beta0_tmp * t14 * in7[2] * 60.0) -
                                    rc_beta0_tmp * t10 * in7[5] * 60.0) -
                                   cd_beta0_tmp * t12 * in7[4] * 60.0) -
                                  dd_beta0_tmp * t15 * in7[2] * 60.0) -
                                 ad_beta0_tmp * t11 * in7[5] * 60.0) -
                                fd_beta0_tmp * t14 * in7[3] * 60.0) -
                               gd_beta0_tmp * t13 * in7[4] * 60.0) -
                              ed_beta0_tmp * t12 * in7[5] * 60.0) -
                             hd_beta0_tmp * t15 * in7[3] * 60.0) -
                            id_beta0_tmp * t13 * in7[5] * 60.0) -
                           jd_beta0_tmp * t15 * in7[4] * 60.0) -
                          kd_beta0_tmp * t14 * in7[5] * 60.0) -
                         in8[0] * t2 * t9 * t10 * in7[0] * 8.0) -
                        in8[1] * t3 * t9 * t11 * in7[1] * 8.0) -
                       in8[2] * t4 * t9 * t12 * in7[2] * 8.0) -
                      in8[3] * t5 * t9 * t13 * in7[3] * 8.0) -
                     in8[4] * t6 * t9 * t14 * in7[4] * 8.0)) +
                   (((((((((((((((((((((in8[5] * t7 * t9 * t15 * in7[5] * -8.0 +
                                        in9[0] * in9[1] * alpha0 * t11 * in4[0] * in7[0] * 12.0) +
                                       sg_beta0_tmp * in4[1] * in7[1] * 12.0) +
                                      gk_beta0_tmp * in4[0] * in7[0] * 12.0) +
                                     in9[0] * in9[2] * alpha0 * t10 * in4[2] * in7[2] * 12.0) +
                                    tg_beta0_tmp * in4[0] * in7[0] * 12.0) +
                                   ug_beta0_tmp * in4[1] * in7[1] * 12.0) +
                                  vg_beta0_tmp * in4[0] * in7[0] * 12.0) +
                                 wg_beta0_tmp * in4[2] * in7[2] * 12.0) +
                                xg_beta0_tmp * in4[3] * in7[3] * 12.0) +
                               yg_beta0_tmp * in4[1] * in7[1] * 12.0) +
                              ah_beta0_tmp * in4[0] * in7[0] * 12.0) +
                             bh_beta0_tmp * in4[3] * in7[3] * 12.0) +
                            ch_beta0_tmp * in4[1] * in7[1] * 12.0) +
                           dh_beta0_tmp * in4[4] * in7[4] * 12.0) +
                          eh_beta0_tmp * in4[2] * in7[2] * 12.0) +
                         fh_beta0_tmp * in4[1] * in7[1] * 12.0) +
                        gh_beta0_tmp * in4[3] * in7[3] * 12.0) +
                       hh_beta0_tmp * in4[4] * in7[4] * 12.0) +
                      ih_beta0_tmp * in4[2] * in7[2] * 12.0) +
                     jh_beta0_tmp * in4[5] * in7[5] * 12.0) +
                    kh_beta0_tmp * in4[4] * in7[4] * 12.0)) +
                  ((((((((((((((((((((((lh_beta0_tmp * in4[2] * in7[2] * 12.0 +
                                        mh_beta0_tmp * in4[5] * in7[5] * 12.0) +
                                       nh_beta0_tmp * in4[3] * in7[3] * 12.0) +
                                      oh_beta0_tmp * in4[4] * in7[4] * 12.0) +
                                     ph_beta0_tmp * in4[5] * in7[5] * 12.0) +
                                    qh_beta0_tmp * in4[3] * in7[3] * 12.0) +
                                   rh_beta0_tmp * in4[5] * in7[5] * 12.0) +
                                  sh_beta0_tmp * in4[4] * in7[4] * 12.0) +
                                 th_beta0_tmp * in4[5] * in7[5] * 12.0) +
                                ld_beta0_tmp * t11 * in7[0] * 3.0) +
                               md_beta0_tmp * t10 * in7[1] * 3.0) +
                              nd_beta0_tmp * t12 * in7[0] * 3.0) +
                             uh_beta0_tmp * t10 * in7[2] * 3.0) +
                            od_beta0_tmp * t13 * in7[0] * 3.0) +
                           qd_beta0_tmp * t12 * in7[1] * 3.0) +
                          sd_beta0_tmp * t14 * in7[0] * 3.0) +
                         rd_beta0_tmp * t11 * in7[2] * 3.0) +
                        pd_beta0_tmp * t10 * in7[3] * 3.0) +
                       ud_beta0_tmp * t13 * in7[1] * 3.0) +
                      yd_beta0_tmp * t15 * in7[0] * 3.0) +
                     vd_beta0_tmp * t11 * in7[3] * 3.0) +
                    be_beta0_tmp * t14 * in7[1] * 3.0) +
                   td_beta0_tmp * t10 * in7[4] * 3.0)) +
                 (((((((((((((((((((((de_beta0_tmp * t13 * in7[2] * 3.0 -
                                      wd_beta0_tmp * t11 * in7[0] * 9.0) +
                                     he_beta0_tmp * t15 * in7[1] * 3.0) +
                                    ee_beta0_tmp * t12 * in7[3] * 3.0) -
                                   xd_beta0_tmp * t10 * in7[1] * 9.0) +
                                  ce_beta0_tmp * t11 * in7[4] * 3.0) +
                                 ie_beta0_tmp * t14 * in7[2] * 3.0) -
                                fe_beta0_tmp * t12 * in7[0] * 9.0) +
                               ae_beta0_tmp * t10 * in7[5] * 3.0) +
                              je_beta0_tmp * t12 * in7[4] * 3.0) +
                             oe_beta0_tmp * t15 * in7[2] * 3.0) -
                            ge_beta0_tmp * t10 * in7[2] * 9.0) -
                           ke_beta0_tmp * t13 * in7[0] * 9.0) +
                          vh_beta0_tmp * t11 * in7[5] * 3.0) +
                         qe_beta0_tmp * t14 * in7[3] * 3.0) -
                        me_beta0_tmp * t12 * in7[1] * 9.0) +
                       re_beta0_tmp * t13 * in7[4] * 3.0) -
                      se_beta0_tmp * t14 * in7[0] * 9.0) -
                     ne_beta0_tmp * t11 * in7[2] * 9.0) +
                    pe_beta0_tmp * t12 * in7[5] * 3.0) +
                   we_beta0_tmp * t15 * in7[3] * 3.0) -
                  le_beta0_tmp * t10 * in7[3] * 9.0)) +
                (((((((((((((((((((ue_beta0_tmp * t13 * in7[1] * -9.0 -
                                   ye_beta0_tmp * t15 * in7[0] * 9.0) +
                                  xe_beta0_tmp * t13 * in7[5] * 3.0) -
                                 ve_beta0_tmp * t11 * in7[3] * 9.0) -
                                bf_beta0_tmp * t14 * in7[1] * 9.0) +
                               ff_beta0_tmp * t15 * in7[4] * 3.0) -
                              te_beta0_tmp * t10 * in7[4] * 9.0) -
                             df_beta0_tmp * t13 * in7[2] * 9.0) +
                            gf_beta0_tmp * t14 * in7[5] * 3.0) -
                           hf_beta0_tmp * t15 * in7[1] * 9.0) -
                          ef_beta0_tmp * t12 * in7[3] * 9.0) -
                         cf_beta0_tmp * t11 * in7[4] * 9.0) -
                        jf_beta0_tmp * t14 * in7[2] * 9.0) -
                       af_beta0_tmp * t10 * in7[5] * 9.0) -
                      kf_beta0_tmp * t12 * in7[4] * 9.0) -
                     lf_beta0_tmp * t15 * in7[2] * 9.0) -
                    if_beta0_tmp * t11 * in7[5] * 9.0) -
                   nf_beta0_tmp * t14 * in7[3] * 9.0) -
                  of_beta0_tmp * t13 * in7[4] * 9.0) -
                 mf_beta0_tmp * t12 * in7[5] * 9.0)) +
               (((((((((((((((((((pf_beta0_tmp * t15 * in7[3] * -9.0 -
                                  qf_beta0_tmp * t13 * in7[5] * 9.0) -
                                 rf_beta0_tmp * t15 * in7[4] * 9.0) -
                                sf_beta0_tmp * t14 * in7[5] * 9.0) -
                               bb_beta0_tmp * in4[0] * in4[1] * in7[1] * 20.0) -
                              wh_beta0_tmp * in4[1] * in7[0] * 20.0) -
                             db_beta0_tmp * in4[0] * in4[2] * in7[2] * 20.0) -
                            xh_beta0_tmp * in4[2] * in7[0] * 20.0) -
                           fb_beta0_tmp * in4[0] * in4[3] * in7[3] * 20.0) -
                          yh_beta0_tmp * in4[3] * in7[0] * 20.0) -
                         hb_beta0_tmp * in4[1] * in4[2] * in7[2] * 20.0) -
                        ai_beta0_tmp * in4[2] * in7[1] * 20.0) -
                       jb_beta0_tmp * in4[0] * in4[4] * in7[4] * 20.0) -
                      bi_beta0_tmp * in4[4] * in7[0] * 20.0) -
                     lb_beta0_tmp * in4[1] * in4[3] * in7[3] * 20.0) -
                    ci_beta0_tmp * in4[3] * in7[1] * 20.0) +
                   nb_beta0_tmp * in4[0] * in4[1] * in7[1] * 20.0) +
                  di_beta0_tmp * in4[1] * in7[0] * 20.0) -
                 pb_beta0_tmp * in4[0] * in4[5] * in7[5] * 20.0) -
                ei_beta0_tmp * in4[5] * in7[0] * 20.0)) +
              (((((((((((((((((((rb_beta0_tmp * in4[1] * in4[4] * in7[4] * -20.0 -
                                 fi_beta0_tmp * in4[4] * in7[1] * 20.0) -
                                tb_beta0_tmp * in4[2] * in4[3] * in7[3] * 20.0) -
                               gi_beta0_tmp * in4[3] * in7[2] * 20.0) +
                              vb_beta0_tmp * in4[0] * in4[2] * in7[2] * 20.0) +
                             hi_beta0_tmp * in4[2] * in7[0] * 20.0) -
                            xb_beta0_tmp * in4[1] * in4[5] * in7[5] * 20.0) -
                           ii_beta0_tmp * in4[5] * in7[1] * 20.0) -
                          ac_beta0_tmp * in4[2] * in4[4] * in7[4] * 20.0) -
                         ji_beta0_tmp * in4[4] * in7[2] * 20.0) +
                        cc_beta0_tmp * in4[0] * in4[3] * in7[3] * 20.0) +
                       ki_beta0_tmp * in4[3] * in7[0] * 20.0) +
                      ec_beta0_tmp * in4[1] * in4[2] * in7[2] * 20.0) +
                     li_beta0_tmp * in4[2] * in7[1] * 20.0) -
                    gc_beta0_tmp * in4[2] * in4[5] * in7[5] * 20.0) -
                   mi_beta0_tmp * in4[5] * in7[2] * 20.0) -
                  ic_beta0_tmp * in4[3] * in4[4] * in7[4] * 20.0) -
                 ni_beta0_tmp * in4[4] * in7[3] * 20.0) +
                kc_beta0_tmp * in4[0] * in4[4] * in7[4] * 20.0) +
               oi_beta0_tmp * in4[4] * in7[0] * 20.0)) +
             ((((((((((((((((((((mc_beta0_tmp * in4[1] * in4[3] * in7[3] * 20.0 +
                                 pi_beta0_tmp * in4[3] * in7[1] * 20.0) -
                                oc_beta0_tmp * in4[3] * in4[5] * in7[5] * 20.0) -
                               qi_beta0_tmp * in4[5] * in7[3] * 20.0) +
                              qc_beta0_tmp * in4[0] * in4[5] * in7[5] * 20.0) +
                             ri_beta0_tmp * in4[5] * in7[0] * 20.0) +
                            sc_beta0_tmp * in4[1] * in4[4] * in7[4] * 20.0) +
                           si_beta0_tmp * in4[4] * in7[1] * 20.0) +
                          uc_beta0_tmp * in4[2] * in4[3] * in7[3] * 20.0) +
                         ti_beta0_tmp * in4[3] * in7[2] * 20.0) -
                        wc_beta0_tmp * in4[4] * in4[5] * in7[5] * 20.0) -
                       ui_beta0_tmp * in4[5] * in7[4] * 20.0) +
                      yc_beta0_tmp * in4[1] * in4[5] * in7[5] * 20.0) +
                     vi_beta0_tmp * in4[5] * in7[1] * 20.0) +
                    bd_beta0_tmp * in4[2] * in4[4] * in7[4] * 20.0) +
                   wi_beta0_tmp * in4[4] * in7[2] * 20.0) +
                  dd_beta0_tmp * in4[2] * in4[5] * in7[5] * 20.0) +
                 xi_beta0_tmp * in4[5] * in7[2] * 20.0) +
                fd_beta0_tmp * in4[3] * in4[4] * in7[4] * 20.0) +
               yi_beta0_tmp * in4[4] * in7[3] * 20.0) +
              hd_beta0_tmp * in4[3] * in4[5] * in7[5] * 20.0)) +
            (((((((((((((((((aj_beta0_tmp * in4[5] * in7[3] * 20.0 +
                             jd_beta0_tmp * in4[4] * in4[5] * in7[5] * 20.0) +
                            bj_beta0_tmp * in4[5] * in7[4] * 20.0) -
                           beta0_tmp_tmp * in4[0] * in4[1] * in7[0] * in7[1] * 16.0) -
                          b_beta0_tmp_tmp * in4[0] * in4[2] * in7[0] * in7[2] * 16.0) -
                         o_beta0_tmp * in4[0] * in4[3] * in7[0] * in7[3] * 16.0) -
                        n_beta0_tmp * in4[1] * in4[2] * in7[1] * in7[2] * 16.0) -
                       q_beta0_tmp * in4[0] * in4[4] * in7[0] * in7[4] * 16.0) -
                      p_beta0_tmp * in4[1] * in4[3] * in7[1] * in7[3] * 16.0) -
                     t_beta0_tmp * in4[0] * in4[5] * in7[0] * in7[5] * 16.0) -
                    s_beta0_tmp * in4[1] * in4[4] * in7[1] * in7[4] * 16.0) -
                   r_beta0_tmp * in4[2] * in4[3] * in7[2] * in7[3] * 16.0) -
                  v_beta0_tmp * in4[1] * in4[5] * in7[1] * in7[5] * 16.0) -
                 u_beta0_tmp * in4[2] * in4[4] * in7[2] * in7[4] * 16.0) -
                x_beta0_tmp * in4[2] * in4[5] * in7[2] * in7[5] * 16.0) -
               w_beta0_tmp * in4[3] * in4[4] * in7[3] * in7[4] * 16.0) -
              y_beta0_tmp * in4[3] * in4[5] * in7[3] * in7[5] * 16.0) -
             ab_beta0_tmp * in4[4] * in4[5] * in7[4] * in7[5] * 16.0)) +
           (((((((((((((((((((ld_beta0_tmp * in4[0] * in4[1] * in7[1] * -3.0 -
                              cj_beta0_tmp * in4[1] * in7[0] * 3.0) -
                             nd_beta0_tmp * in4[0] * in4[2] * in7[2] * 3.0) -
                            uh_beta0_tmp * in4[0] * in4[2] * in7[0] * 3.0) -
                           od_beta0_tmp * in4[0] * in4[3] * in7[3] * 3.0) -
                          dj_beta0_tmp * in4[3] * in7[0] * 3.0) -
                         qd_beta0_tmp * in4[1] * in4[2] * in7[2] * 3.0) -
                        ej_beta0_tmp * in4[2] * in7[1] * 3.0) -
                       sd_beta0_tmp * in4[0] * in4[4] * in7[4] * 3.0) -
                      fj_beta0_tmp * in4[4] * in7[0] * 3.0) -
                     ud_beta0_tmp * in4[1] * in4[3] * in7[3] * 3.0) -
                    gj_beta0_tmp * in4[3] * in7[1] * 3.0) +
                   wd_beta0_tmp * in4[0] * in4[1] * in7[1]) +
                  hj_beta0_tmp * in4[1] * in7[0]) -
                 yd_beta0_tmp * in4[0] * in4[5] * in7[5] * 3.0) -
                ij_beta0_tmp * in4[5] * in7[0] * 3.0) -
               be_beta0_tmp * in4[1] * in4[4] * in7[4] * 3.0) -
              jj_beta0_tmp * in4[4] * in7[1] * 3.0) -
             de_beta0_tmp * in4[2] * in4[3] * in7[3] * 3.0) -
            kj_beta0_tmp * in4[3] * in7[2] * 3.0)) +
          (((((((((((((((((((((fe_beta0_tmp * in4[0] * in4[2] * in7[2] +
                               lj_beta0_tmp * in4[2] * in7[0]) -
                              he_beta0_tmp * in4[1] * in4[5] * in7[5] * 3.0) -
                             vh_beta0_tmp * in4[1] * in4[5] * in7[1] * 3.0) -
                            ie_beta0_tmp * in4[2] * in4[4] * in7[4] * 3.0) -
                           mj_beta0_tmp * in4[4] * in7[2] * 3.0) +
                          ke_beta0_tmp * in4[0] * in4[3] * in7[3]) +
                         nj_beta0_tmp * in4[3] * in7[0]) +
                        me_beta0_tmp * in4[1] * in4[2] * in7[2]) +
                       oj_beta0_tmp * in4[2] * in7[1]) -
                      oe_beta0_tmp * in4[2] * in4[5] * in7[5] * 3.0) -
                     pj_beta0_tmp * in4[5] * in7[2] * 3.0) -
                    qe_beta0_tmp * in4[3] * in4[4] * in7[4] * 3.0) -
                   qj_beta0_tmp * in4[4] * in7[3] * 3.0) +
                  se_beta0_tmp * in4[0] * in4[4] * in7[4]) +
                 rj_beta0_tmp * in4[4] * in7[0]) +
                ue_beta0_tmp * in4[1] * in4[3] * in7[3]) +
               sj_beta0_tmp * in4[3] * in7[1]) -
              we_beta0_tmp * in4[3] * in4[5] * in7[5] * 3.0) -
             tj_beta0_tmp * in4[5] * in7[3] * 3.0) +
            ye_beta0_tmp * in4[0] * in4[5] * in7[5]) +
           uj_beta0_tmp * in4[5] * in7[0])) +
         (((((((((((((((((bf_beta0_tmp * in4[1] * in4[4] * in7[4] +
                          vj_beta0_tmp * in4[4] * in7[1]) +
                         df_beta0_tmp * in4[2] * in4[3] * in7[3]) +
                        wj_beta0_tmp * in4[3] * in7[2]) -
                       ff_beta0_tmp * in4[4] * in4[5] * in7[5] * 3.0) -
                      xj_beta0_tmp * in4[5] * in7[4] * 3.0) +
                     hf_beta0_tmp * in4[1] * in4[5] * in7[5]) +
                    yj_beta0_tmp * in4[5] * in7[1]) +
                   jf_beta0_tmp * in4[2] * in4[4] * in7[4]) +
                  ak_beta0_tmp * in4[4] * in7[2]) +
                 lf_beta0_tmp * in4[2] * in4[5] * in7[5]) +
                bk_beta0_tmp * in4[5] * in7[2]) +
               nf_beta0_tmp * in4[3] * in4[4] * in7[4]) +
              ck_beta0_tmp * in4[4] * in7[3]) +
             pf_beta0_tmp * in4[3] * in4[5] * in7[5]) +
            dk_beta0_tmp * in4[5] * in7[3]) +
           rf_beta0_tmp * in4[4] * in4[5] * in7[5]) +
          ek_beta0_tmp * in4[5] * in7[4]));
}

} // namespace ocn

//
// File trailer for Calc_beta0_beta1.cpp
//
// [EOF]
//
