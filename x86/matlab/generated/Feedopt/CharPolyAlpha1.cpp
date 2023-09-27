//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CharPolyAlpha1.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 27-Sep-2023 11:17:01
//

// Include Files
#include "CharPolyAlpha1.h"
#include <cmath>

// Function Definitions
//
// function Coeff_Poly_Alpha1 = CharPolyAlpha1(in1)
//
// CharPolyAlpha1
//     Coeff_Poly_Alpha1 = CharPolyAlpha1(IN1)
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
    double ab_Coeff_Poly_Alpha1_tmp;
    double ac_Coeff_Poly_Alpha1_tmp;
    double ad_Coeff_Poly_Alpha1_tmp;
    double ae_Coeff_Poly_Alpha1_tmp;
    double af_Coeff_Poly_Alpha1_tmp;
    double ag_Coeff_Poly_Alpha1_tmp;
    double b_Coeff_Poly_Alpha1_tmp;
    double b_Coeff_Poly_Alpha1_tmp_tmp;
    double bb_Coeff_Poly_Alpha1_tmp;
    double bc_Coeff_Poly_Alpha1_tmp;
    double bd_Coeff_Poly_Alpha1_tmp;
    double be_Coeff_Poly_Alpha1_tmp;
    double bf_Coeff_Poly_Alpha1_tmp;
    double bg_Coeff_Poly_Alpha1_tmp;
    double c_Coeff_Poly_Alpha1_tmp;
    double c_Coeff_Poly_Alpha1_tmp_tmp;
    double cb_Coeff_Poly_Alpha1_tmp;
    double cc_Coeff_Poly_Alpha1_tmp;
    double cd_Coeff_Poly_Alpha1_tmp;
    double ce_Coeff_Poly_Alpha1_tmp;
    double cf_Coeff_Poly_Alpha1_tmp;
    double cg_Coeff_Poly_Alpha1_tmp;
    double d_Coeff_Poly_Alpha1_tmp;
    double d_Coeff_Poly_Alpha1_tmp_tmp;
    double db_Coeff_Poly_Alpha1_tmp;
    double dc_Coeff_Poly_Alpha1_tmp;
    double dd_Coeff_Poly_Alpha1_tmp;
    double de_Coeff_Poly_Alpha1_tmp;
    double df_Coeff_Poly_Alpha1_tmp;
    double dg_Coeff_Poly_Alpha1_tmp;
    double e_Coeff_Poly_Alpha1_tmp;
    double e_Coeff_Poly_Alpha1_tmp_tmp;
    double eb_Coeff_Poly_Alpha1_tmp;
    double ec_Coeff_Poly_Alpha1_tmp;
    double ed_Coeff_Poly_Alpha1_tmp;
    double ee_Coeff_Poly_Alpha1_tmp;
    double ef_Coeff_Poly_Alpha1_tmp;
    double eg_Coeff_Poly_Alpha1_tmp;
    double f_Coeff_Poly_Alpha1_tmp;
    double f_Coeff_Poly_Alpha1_tmp_tmp;
    double fb_Coeff_Poly_Alpha1_tmp;
    double fc_Coeff_Poly_Alpha1_tmp;
    double fd_Coeff_Poly_Alpha1_tmp;
    double fe_Coeff_Poly_Alpha1_tmp;
    double ff_Coeff_Poly_Alpha1_tmp;
    double fg_Coeff_Poly_Alpha1_tmp;
    double g_Coeff_Poly_Alpha1_tmp;
    double g_Coeff_Poly_Alpha1_tmp_tmp;
    double gb_Coeff_Poly_Alpha1_tmp;
    double gc_Coeff_Poly_Alpha1_tmp;
    double gd_Coeff_Poly_Alpha1_tmp;
    double ge_Coeff_Poly_Alpha1_tmp;
    double gf_Coeff_Poly_Alpha1_tmp;
    double gg_Coeff_Poly_Alpha1_tmp;
    double h_Coeff_Poly_Alpha1_tmp;
    double h_Coeff_Poly_Alpha1_tmp_tmp;
    double hb_Coeff_Poly_Alpha1_tmp;
    double hc_Coeff_Poly_Alpha1_tmp;
    double hd_Coeff_Poly_Alpha1_tmp;
    double he_Coeff_Poly_Alpha1_tmp;
    double hf_Coeff_Poly_Alpha1_tmp;
    double hg_Coeff_Poly_Alpha1_tmp;
    double i_Coeff_Poly_Alpha1_tmp;
    double i_Coeff_Poly_Alpha1_tmp_tmp;
    double ib_Coeff_Poly_Alpha1_tmp;
    double ic_Coeff_Poly_Alpha1_tmp;
    double id_Coeff_Poly_Alpha1_tmp;
    double ie_Coeff_Poly_Alpha1_tmp;
    double if_Coeff_Poly_Alpha1_tmp;
    double ig_Coeff_Poly_Alpha1_tmp;
    double j_Coeff_Poly_Alpha1_tmp;
    double j_Coeff_Poly_Alpha1_tmp_tmp;
    double jb_Coeff_Poly_Alpha1_tmp;
    double jc_Coeff_Poly_Alpha1_tmp;
    double jd_Coeff_Poly_Alpha1_tmp;
    double je_Coeff_Poly_Alpha1_tmp;
    double jf_Coeff_Poly_Alpha1_tmp;
    double jg_Coeff_Poly_Alpha1_tmp;
    double k_Coeff_Poly_Alpha1_tmp;
    double kb_Coeff_Poly_Alpha1_tmp;
    double kc_Coeff_Poly_Alpha1_tmp;
    double kd_Coeff_Poly_Alpha1_tmp;
    double ke_Coeff_Poly_Alpha1_tmp;
    double kf_Coeff_Poly_Alpha1_tmp;
    double l_Coeff_Poly_Alpha1_tmp;
    double lb_Coeff_Poly_Alpha1_tmp;
    double lc_Coeff_Poly_Alpha1_tmp;
    double ld_Coeff_Poly_Alpha1_tmp;
    double le_Coeff_Poly_Alpha1_tmp;
    double lf_Coeff_Poly_Alpha1_tmp;
    double m_Coeff_Poly_Alpha1_tmp;
    double mb_Coeff_Poly_Alpha1_tmp;
    double mc_Coeff_Poly_Alpha1_tmp;
    double md_Coeff_Poly_Alpha1_tmp;
    double me_Coeff_Poly_Alpha1_tmp;
    double mf_Coeff_Poly_Alpha1_tmp;
    double n_Coeff_Poly_Alpha1_tmp;
    double nb_Coeff_Poly_Alpha1_tmp;
    double nc_Coeff_Poly_Alpha1_tmp;
    double nd_Coeff_Poly_Alpha1_tmp;
    double ne_Coeff_Poly_Alpha1_tmp;
    double nf_Coeff_Poly_Alpha1_tmp;
    double o_Coeff_Poly_Alpha1_tmp;
    double ob_Coeff_Poly_Alpha1_tmp;
    double oc_Coeff_Poly_Alpha1_tmp;
    double od_Coeff_Poly_Alpha1_tmp;
    double oe_Coeff_Poly_Alpha1_tmp;
    double of_Coeff_Poly_Alpha1_tmp;
    double p_Coeff_Poly_Alpha1_tmp;
    double pb_Coeff_Poly_Alpha1_tmp;
    double pc_Coeff_Poly_Alpha1_tmp;
    double pd_Coeff_Poly_Alpha1_tmp;
    double pe_Coeff_Poly_Alpha1_tmp;
    double pf_Coeff_Poly_Alpha1_tmp;
    double q_Coeff_Poly_Alpha1_tmp;
    double qb_Coeff_Poly_Alpha1_tmp;
    double qc_Coeff_Poly_Alpha1_tmp;
    double qd_Coeff_Poly_Alpha1_tmp;
    double qe_Coeff_Poly_Alpha1_tmp;
    double qf_Coeff_Poly_Alpha1_tmp;
    double r_Coeff_Poly_Alpha1_tmp;
    double rb_Coeff_Poly_Alpha1_tmp;
    double rc_Coeff_Poly_Alpha1_tmp;
    double rd_Coeff_Poly_Alpha1_tmp;
    double re_Coeff_Poly_Alpha1_tmp;
    double rf_Coeff_Poly_Alpha1_tmp;
    double s_Coeff_Poly_Alpha1_tmp;
    double sb_Coeff_Poly_Alpha1_tmp;
    double sc_Coeff_Poly_Alpha1_tmp;
    double sd_Coeff_Poly_Alpha1_tmp;
    double se_Coeff_Poly_Alpha1_tmp;
    double sf_Coeff_Poly_Alpha1_tmp;
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
    double te_Coeff_Poly_Alpha1_tmp;
    double tf_Coeff_Poly_Alpha1_tmp;
    double u_Coeff_Poly_Alpha1_tmp;
    double ub_Coeff_Poly_Alpha1_tmp;
    double uc_Coeff_Poly_Alpha1_tmp;
    double ud_Coeff_Poly_Alpha1_tmp;
    double ue_Coeff_Poly_Alpha1_tmp;
    double uf_Coeff_Poly_Alpha1_tmp;
    double v_Coeff_Poly_Alpha1_tmp;
    double vb_Coeff_Poly_Alpha1_tmp;
    double vc_Coeff_Poly_Alpha1_tmp;
    double vd_Coeff_Poly_Alpha1_tmp;
    double ve_Coeff_Poly_Alpha1_tmp;
    double vf_Coeff_Poly_Alpha1_tmp;
    double w_Coeff_Poly_Alpha1_tmp;
    double wb_Coeff_Poly_Alpha1_tmp;
    double wc_Coeff_Poly_Alpha1_tmp;
    double wd_Coeff_Poly_Alpha1_tmp;
    double we_Coeff_Poly_Alpha1_tmp;
    double wf_Coeff_Poly_Alpha1_tmp;
    double x_Coeff_Poly_Alpha1_tmp;
    double xb_Coeff_Poly_Alpha1_tmp;
    double xc_Coeff_Poly_Alpha1_tmp;
    double xd_Coeff_Poly_Alpha1_tmp;
    double xe_Coeff_Poly_Alpha1_tmp;
    double xf_Coeff_Poly_Alpha1_tmp;
    double y_Coeff_Poly_Alpha1_tmp;
    double yb_Coeff_Poly_Alpha1_tmp;
    double yc_Coeff_Poly_Alpha1_tmp;
    double yd_Coeff_Poly_Alpha1_tmp;
    double ye_Coeff_Poly_Alpha1_tmp;
    double yf_Coeff_Poly_Alpha1_tmp;
    //     This function was generated by the Symbolic Math Toolbox version 9.0.
    //     02-Nov-2022 16:01:02
    // 'CharPolyAlpha1:8' CoefPS1_1 = in1(1);
    // 'CharPolyAlpha1:9' CoefPS2_1 = in1(2);
    // 'CharPolyAlpha1:10' CoefPS3_1 = in1(3);
    // 'CharPolyAlpha1:11' CoefPS4_1 = in1(4);
    // 'CharPolyAlpha1:12' CoefPS5_1 = in1(5);
    // 'CharPolyAlpha1:13' CoefPS6_1 = in1(6);
    // 'CharPolyAlpha1:14' CoefPS7_1 = in1(7);
    // 'CharPolyAlpha1:15' CoefPS8_1 = in1(8);
    // 'CharPolyAlpha1:16' CoefPS9_1 = in1(9);
    // 'CharPolyAlpha1:17' CoefPS10_1 = in1(10);
    // 'CharPolyAlpha1:18' CoefPS11_1 = in1(11);
    // 'CharPolyAlpha1:19' CoefPS12_1 = in1(12);
    // 'CharPolyAlpha1:20' CoefPS13_1 = in1(13);
    // 'CharPolyAlpha1:21' CoefPS14_1 = in1(14);
    // 'CharPolyAlpha1:22' CoefPS15_1 = in1(15);
    // 'CharPolyAlpha1:23' CoefPS16_1 = in1(16);
    // 'CharPolyAlpha1:24' t2 = CoefPS1_1.^2;
    t2 = in1[0] * in1[0];
    // 'CharPolyAlpha1:25' t3 = CoefPS1_1.^3;
    t3 = std::pow(in1[0], 3.0);
    // 'CharPolyAlpha1:26' t4 = CoefPS2_1.^2;
    t4 = in1[1] * in1[1];
    // 'CharPolyAlpha1:27' t5 = CoefPS2_1.^3;
    t5 = std::pow(in1[1], 3.0);
    // 'CharPolyAlpha1:28' t6 = CoefPS3_1.^2;
    t6 = in1[2] * in1[2];
    // 'CharPolyAlpha1:29' t7 = CoefPS3_1.^3;
    t7 = std::pow(in1[2], 3.0);
    // 'CharPolyAlpha1:30' t8 = CoefPS4_1.^2;
    t8 = in1[3] * in1[3];
    // 'CharPolyAlpha1:31' t9 = CoefPS4_1.^3;
    t9 = std::pow(in1[3], 3.0);
    // 'CharPolyAlpha1:32' t10 = CoefPS5_1.^2;
    t10 = in1[4] * in1[4];
    // 'CharPolyAlpha1:33' t11 = CoefPS6_1.^2;
    t11 = in1[5] * in1[5];
    // 'CharPolyAlpha1:34' t12 = CoefPS7_1.^2;
    t12 = in1[6] * in1[6];
    // 'CharPolyAlpha1:35' t13 = CoefPS8_1.^2;
    t13 = in1[7] * in1[7];
    // 'CharPolyAlpha1:36' t14 = CoefPS9_1.^2;
    t14 = in1[8] * in1[8];
    // 'CharPolyAlpha1:37' t15 = CoefPS10_1.^2;
    t15 = in1[9] * in1[9];
    // 'CharPolyAlpha1:38' t16 = CoefPS11_1.^2;
    t16 = in1[10] * in1[10];
    // 'CharPolyAlpha1:39' t17 = CoefPS12_1.^2;
    t17 = in1[11] * in1[11];
    // 'CharPolyAlpha1:40' t18 = CoefPS13_1.^2;
    t18 = in1[12] * in1[12];
    // 'CharPolyAlpha1:41' t19 = CoefPS14_1.^2;
    t19 = in1[13] * in1[13];
    // 'CharPolyAlpha1:42' t20 = CoefPS15_1.^2;
    t20 = in1[14] * in1[14];
    // 'CharPolyAlpha1:43' t21 = CoefPS16_1.^2;
    t21 = in1[15] * in1[15];
    // 'CharPolyAlpha1:44' et1 =
    // CoefPS6_1.^3.*t18+CoefPS10_1.*CoefPS12_1.*t3.*2.0+CoefPS2_1.*t2.*t15.*3.0+CoefPS2_1.*t10.*t19+CoefPS6_1.*t2.*t16+CoefPS6_1.*t4.*t14+CoefPS8_1.*t2.*t14+CoefPS8_1.*t10.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*t16.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*t14.*2.0+CoefPS1_1.*CoefPS5_1.*CoefPS6_1.*t19.*2.0+CoefPS5_1.*CoefPS6_1.*CoefPS7_1.*t18.*6.0-CoefPS4_1.*CoefPS9_1.*CoefPS10_1.*t2-CoefPS3_1.*CoefPS9_1.*CoefPS12_1.*t2-CoefPS3_1.*CoefPS10_1.*CoefPS11_1.*t2-CoefPS2_1.*CoefPS9_1.*CoefPS13_1.*t11.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS11_1.*t4.*2.0-CoefPS1_1.*CoefPS11_1.*CoefPS13_1.*t11.*2.0+CoefPS7_1.*CoefPS9_1.*CoefPS11_1.*t2.*2.0+CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*t6+CoefPS5_1.*CoefPS11_1.*CoefPS13_1.*t6+CoefPS6_1.*CoefPS9_1.*CoefPS15_1.*t2.*2.0-CoefPS6_1.*CoefPS10_1.*CoefPS14_1.*t2.*2.0-CoefPS2_1.*CoefPS13_1.*CoefPS15_1.*t10.*2.0+CoefPS5_1.*CoefPS11_1.*CoefPS15_1.*t2.*2.0-CoefPS5_1.*CoefPS12_1.*CoefPS14_1.*t2.*2.0-CoefPS4_1.*CoefPS13_1.*CoefPS14_1.*t10-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS9_1.*CoefPS10_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS9_1.*CoefPS11_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS9_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS10_1.*CoefPS14_1.*4.0-CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS9_1.*CoefPS14_1;
    // 'CharPolyAlpha1:45' et2 =
    // CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS5_1.*CoefPS9_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS5_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS6_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS5_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS5_1.*CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS5_1.*CoefPS6_1.*CoefPS13_1.*CoefPS14_1.*2.0;
    // 'CharPolyAlpha1:46' et3 =
    // t3.*t17-CoefPS10_1.*CoefPS13_1.*t7+CoefPS10_1.*CoefPS16_1.*t3.*2.0+CoefPS1_1.*t4.*t15.*3.0+CoefPS1_1.*t11.*t19+CoefPS5_1.*t4.*t16+CoefPS5_1.*t2.*t20+CoefPS5_1.*t12.*t18.*3.0+CoefPS7_1.*t2.*t16+CoefPS7_1.*t4.*t14+CoefPS7_1.*t11.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*t16.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*t14.*2.0+CoefPS1_1.*CoefPS5_1.*CoefPS7_1.*t19.*2.0+CoefPS2_1.*CoefPS5_1.*CoefPS6_1.*t19.*2.0+CoefPS5_1.*CoefPS6_1.*CoefPS8_1.*t18.*6.0-CoefPS3_1.*CoefPS9_1.*CoefPS10_1.*t4-CoefPS1_1.*CoefPS9_1.*CoefPS13_1.*t12.*2.0+CoefPS2_1.*CoefPS10_1.*CoefPS12_1.*t2.*6.0-CoefPS4_1.*CoefPS9_1.*CoefPS12_1.*t2-CoefPS4_1.*CoefPS10_1.*CoefPS11_1.*t2+CoefPS1_1.*CoefPS10_1.*CoefPS14_1.*t6-CoefPS3_1.*CoefPS11_1.*CoefPS12_1.*t2+CoefPS6_1.*CoefPS9_1.*CoefPS11_1.*t4.*2.0-CoefPS2_1.*CoefPS11_1.*CoefPS13_1.*t11.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS13_1.*t8-CoefPS3_1.*CoefPS9_1.*CoefPS16_1.*t2-CoefPS3_1.*CoefPS10_1.*CoefPS15_1.*t2+CoefPS8_1.*CoefPS9_1.*CoefPS11_1.*t2.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS15_1.*t4.*2.0-CoefPS5_1.*CoefPS10_1.*CoefPS14_1.*t4.*2.0+CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*t6-CoefPS1_1.*CoefPS13_1.*CoefPS15_1.*t11.*2.0+CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*t6-CoefPS3_1.*CoefPS13_1.*CoefPS14_1.*t11;
    // 'CharPolyAlpha1:47' et4 =
    // CoefPS7_1.*CoefPS9_1.*CoefPS15_1.*t2.*2.0-CoefPS7_1.*CoefPS10_1.*CoefPS14_1.*t2.*2.0+CoefPS6_1.*CoefPS11_1.*CoefPS15_1.*t2.*2.0-CoefPS6_1.*CoefPS12_1.*CoefPS14_1.*t2.*2.0+CoefPS5_1.*CoefPS13_1.*CoefPS15_1.*t6-CoefPS5_1.*CoefPS14_1.*CoefPS16_1.*t2.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS9_1.*CoefPS10_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS9_1.*CoefPS12_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS10_1.*CoefPS11_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS9_1.*CoefPS11_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS9_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS10_1.*CoefPS14_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS11_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS12_1.*CoefPS14_1.*4.0-CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS11_1.*CoefPS14_1;
    // 'CharPolyAlpha1:48' et5 =
    // CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*2.0+CoefPS3_1.*CoefPS4_1.*CoefPS5_1.*CoefPS11_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS6_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS14_1.*CoefPS15_1-CoefPS1_1.*CoefPS5_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS6_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS5_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS5_1.*CoefPS7_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS5_1.*CoefPS6_1.*CoefPS13_1.*CoefPS14_1.*2.0;
    // 'CharPolyAlpha1:49' et6 =
    // t5.*t15-CoefPS12_1.*CoefPS13_1.*t7+CoefPS12_1.*CoefPS16_1.*t3.*2.0+CoefPS2_1.*t2.*t17.*3.0+CoefPS2_1.*t11.*t19+CoefPS6_1.*t4.*t16+CoefPS6_1.*t2.*t20+CoefPS6_1.*t12.*t18.*3.0+CoefPS8_1.*t2.*t16+CoefPS8_1.*t4.*t14+CoefPS8_1.*t11.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*t20.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*t16.*2.0+CoefPS1_1.*CoefPS5_1.*CoefPS8_1.*t19.*2.0+CoefPS1_1.*CoefPS6_1.*CoefPS7_1.*t19.*2.0+CoefPS2_1.*CoefPS5_1.*CoefPS7_1.*t19.*2.0+CoefPS5_1.*CoefPS7_1.*CoefPS8_1.*t18.*6.0+CoefPS1_1.*CoefPS10_1.*CoefPS12_1.*t4.*6.0-CoefPS4_1.*CoefPS9_1.*CoefPS10_1.*t4-CoefPS3_1.*CoefPS9_1.*CoefPS12_1.*t4-CoefPS3_1.*CoefPS10_1.*CoefPS11_1.*t4-CoefPS2_1.*CoefPS9_1.*CoefPS13_1.*t12.*2.0-CoefPS1_1.*CoefPS11_1.*CoefPS13_1.*t12.*2.0+CoefPS2_1.*CoefPS10_1.*CoefPS14_1.*t6-CoefPS4_1.*CoefPS11_1.*CoefPS12_1.*t2+CoefPS7_1.*CoefPS9_1.*CoefPS11_1.*t4.*2.0+CoefPS1_1.*CoefPS12_1.*CoefPS14_1.*t6-CoefPS4_1.*CoefPS10_1.*CoefPS13_1.*t6.*3.0+CoefPS2_1.*CoefPS10_1.*CoefPS16_1.*t2.*6.0+CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*t8-CoefPS4_1.*CoefPS9_1.*CoefPS16_1.*t2-CoefPS4_1.*CoefPS10_1.*CoefPS15_1.*t2+CoefPS5_1.*CoefPS11_1.*CoefPS13_1.*t8-CoefPS3_1.*CoefPS11_1.*CoefPS16_1.*t2-CoefPS3_1.*CoefPS12_1.*CoefPS15_1.*t2;
    // 'CharPolyAlpha1:50' et7 =
    // CoefPS6_1.*CoefPS9_1.*CoefPS15_1.*t4.*2.0-CoefPS6_1.*CoefPS10_1.*CoefPS14_1.*t4.*2.0+CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*t6-CoefPS2_1.*CoefPS13_1.*CoefPS15_1.*t11.*2.0+CoefPS5_1.*CoefPS11_1.*CoefPS15_1.*t4.*2.0-CoefPS5_1.*CoefPS12_1.*CoefPS14_1.*t4.*2.0+CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*t6-CoefPS4_1.*CoefPS13_1.*CoefPS14_1.*t11+CoefPS8_1.*CoefPS9_1.*CoefPS15_1.*t2.*2.0-CoefPS8_1.*CoefPS10_1.*CoefPS14_1.*t2.*2.0+CoefPS7_1.*CoefPS11_1.*CoefPS15_1.*t2.*2.0-CoefPS7_1.*CoefPS12_1.*CoefPS14_1.*t2.*2.0+CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*t6-CoefPS6_1.*CoefPS14_1.*CoefPS16_1.*t2.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS9_1.*CoefPS12_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS10_1.*CoefPS11_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS11_1.*CoefPS12_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS9_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS10_1.*CoefPS15_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS9_1.*CoefPS11_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS4_1.*CoefPS10_1.*CoefPS14_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS9_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS10_1.*CoefPS14_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS11_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS12_1.*CoefPS14_1.*4.0-CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS9_1.*CoefPS14_1;
    // 'CharPolyAlpha1:51' et8 =
    // CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*2.0+CoefPS3_1.*CoefPS4_1.*CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS14_1.*CoefPS16_1.*4.0-CoefPS1_1.*CoefPS7_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS6_1.*CoefPS14_1.*CoefPS15_1+CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS5_1.*CoefPS14_1.*CoefPS15_1-CoefPS1_1.*CoefPS6_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0+CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS5_1.*CoefPS14_1.*CoefPS15_1-CoefPS2_1.*CoefPS5_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0;
    // 'CharPolyAlpha1:52' et9 =
    // CoefPS2_1.*CoefPS6_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*-4.0+CoefPS3_1.*CoefPS4_1.*CoefPS5_1.*CoefPS13_1.*CoefPS15_1.*2.0-CoefPS1_1.*CoefPS5_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS6_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS5_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS3_1.*CoefPS6_1.*CoefPS7_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS5_1.*CoefPS7_1.*CoefPS13_1.*CoefPS14_1.*2.0;
    // 'CharPolyAlpha1:53' et10 =
    // t3.*t21+CoefPS7_1.^3.*t18+CoefPS10_1.*CoefPS12_1.*t5.*2.0-CoefPS13_1.*CoefPS16_1.*t7+CoefPS1_1.*t4.*t17.*3.0+CoefPS1_1.*t12.*t19+CoefPS5_1.*t4.*t20+CoefPS5_1.*t13.*t18.*3.0+CoefPS7_1.*t4.*t16+CoefPS7_1.*t2.*t20+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*t20.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*t16.*2.0+CoefPS1_1.*CoefPS6_1.*CoefPS8_1.*t19.*2.0+CoefPS2_1.*CoefPS5_1.*CoefPS8_1.*t19.*2.0+CoefPS2_1.*CoefPS6_1.*CoefPS7_1.*t19.*2.0+CoefPS6_1.*CoefPS7_1.*CoefPS8_1.*t18.*6.0-CoefPS1_1.*CoefPS9_1.*CoefPS13_1.*t13.*2.0-CoefPS4_1.*CoefPS9_1.*CoefPS12_1.*t4-CoefPS4_1.*CoefPS10_1.*CoefPS11_1.*t4+CoefPS1_1.*CoefPS10_1.*CoefPS14_1.*t8-CoefPS3_1.*CoefPS11_1.*CoefPS12_1.*t4-CoefPS3_1.*CoefPS10_1.*CoefPS13_1.*t8.*3.0-CoefPS2_1.*CoefPS11_1.*CoefPS13_1.*t12.*2.0+CoefPS1_1.*CoefPS10_1.*CoefPS16_1.*t4.*6.0-CoefPS3_1.*CoefPS9_1.*CoefPS16_1.*t4-CoefPS3_1.*CoefPS10_1.*CoefPS15_1.*t4+CoefPS8_1.*CoefPS9_1.*CoefPS11_1.*t4.*2.0+CoefPS2_1.*CoefPS12_1.*CoefPS14_1.*t6-CoefPS4_1.*CoefPS12_1.*CoefPS13_1.*t6.*3.0+CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*t8-CoefPS1_1.*CoefPS13_1.*CoefPS15_1.*t12.*2.0+CoefPS2_1.*CoefPS12_1.*CoefPS16_1.*t2.*6.0+CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*t8-CoefPS3_1.*CoefPS13_1.*CoefPS14_1.*t12;
    // 'CharPolyAlpha1:54' et11 =
    // -CoefPS4_1.*CoefPS11_1.*CoefPS16_1.*t2-CoefPS4_1.*CoefPS12_1.*CoefPS15_1.*t2+CoefPS7_1.*CoefPS9_1.*CoefPS15_1.*t4.*2.0-CoefPS7_1.*CoefPS10_1.*CoefPS14_1.*t4.*2.0+CoefPS1_1.*CoefPS14_1.*CoefPS16_1.*t6+CoefPS6_1.*CoefPS11_1.*CoefPS15_1.*t4.*2.0-CoefPS6_1.*CoefPS12_1.*CoefPS14_1.*t4.*2.0+CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*t6+CoefPS5_1.*CoefPS13_1.*CoefPS15_1.*t8-CoefPS3_1.*CoefPS15_1.*CoefPS16_1.*t2+CoefPS8_1.*CoefPS11_1.*CoefPS15_1.*t2.*2.0-CoefPS8_1.*CoefPS12_1.*CoefPS14_1.*t2.*2.0-CoefPS5_1.*CoefPS14_1.*CoefPS16_1.*t4.*2.0+CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*t6-CoefPS7_1.*CoefPS14_1.*CoefPS16_1.*t2.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS11_1.*CoefPS12_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS9_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS10_1.*CoefPS15_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS11_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS12_1.*CoefPS15_1.*2.0+CoefPS2_1.*CoefPS3_1.*CoefPS4_1.*CoefPS10_1.*CoefPS14_1.*2.0+CoefPS1_1.*CoefPS3_1.*CoefPS4_1.*CoefPS12_1.*CoefPS14_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS9_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS10_1.*CoefPS14_1.*4.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS11_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS12_1.*CoefPS14_1.*4.0-CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS10_1.*CoefPS13_1.*3.0;
    // 'CharPolyAlpha1:55' et12 =
    // -CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*2.0+CoefPS3_1.*CoefPS4_1.*CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*CoefPS14_1.*CoefPS16_1.*4.0-CoefPS2_1.*CoefPS7_1.*CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS7_1.*CoefPS14_1.*CoefPS15_1+CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS6_1.*CoefPS14_1.*CoefPS15_1-CoefPS1_1.*CoefPS7_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0+CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS6_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS5_1.*CoefPS14_1.*CoefPS15_1-CoefPS2_1.*CoefPS6_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0;
    // 'CharPolyAlpha1:56' et13 =
    // CoefPS3_1.*CoefPS4_1.*CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*2.0-CoefPS1_1.*CoefPS6_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS6_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS5_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS6_1.*CoefPS7_1.*CoefPS13_1.*CoefPS14_1.*2.0;
    // 'CharPolyAlpha1:57' et14 =
    // t5.*t17-CoefPS10_1.*CoefPS13_1.*t9+CoefPS10_1.*CoefPS16_1.*t5.*2.0+CoefPS2_1.*t2.*t21.*3.0+CoefPS2_1.*t12.*t19+CoefPS6_1.*t4.*t20+CoefPS6_1.*t13.*t18.*3.0+CoefPS8_1.*t4.*t16+CoefPS8_1.*t2.*t20+CoefPS8_1.*t12.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*t20.*2.0+CoefPS1_1.*CoefPS7_1.*CoefPS8_1.*t19.*2.0+CoefPS2_1.*CoefPS6_1.*CoefPS8_1.*t19.*2.0-CoefPS2_1.*CoefPS9_1.*CoefPS13_1.*t13.*2.0-CoefPS1_1.*CoefPS11_1.*CoefPS13_1.*t13.*2.0+CoefPS2_1.*CoefPS10_1.*CoefPS14_1.*t8-CoefPS4_1.*CoefPS11_1.*CoefPS12_1.*t4+CoefPS1_1.*CoefPS12_1.*CoefPS14_1.*t8-CoefPS3_1.*CoefPS12_1.*CoefPS13_1.*t8.*3.0+CoefPS1_1.*CoefPS12_1.*CoefPS16_1.*t4.*6.0-CoefPS4_1.*CoefPS9_1.*CoefPS16_1.*t4-CoefPS4_1.*CoefPS10_1.*CoefPS15_1.*t4-CoefPS3_1.*CoefPS11_1.*CoefPS16_1.*t4-CoefPS3_1.*CoefPS12_1.*CoefPS15_1.*t4+CoefPS8_1.*CoefPS9_1.*CoefPS13_1.*t8-CoefPS2_1.*CoefPS13_1.*CoefPS15_1.*t12.*2.0+CoefPS7_1.*CoefPS11_1.*CoefPS13_1.*t8-CoefPS4_1.*CoefPS13_1.*CoefPS14_1.*t12+CoefPS8_1.*CoefPS9_1.*CoefPS15_1.*t4.*2.0-CoefPS8_1.*CoefPS10_1.*CoefPS14_1.*t4.*2.0+CoefPS2_1.*CoefPS14_1.*CoefPS16_1.*t6+CoefPS7_1.*CoefPS11_1.*CoefPS15_1.*t4.*2.0-CoefPS7_1.*CoefPS12_1.*CoefPS14_1.*t4.*2.0-CoefPS4_1.*CoefPS13_1.*CoefPS16_1.*t6.*3.0;
    // 'CharPolyAlpha1:58' et15 =
    // CoefPS6_1.*CoefPS13_1.*CoefPS15_1.*t8-CoefPS4_1.*CoefPS15_1.*CoefPS16_1.*t2-CoefPS6_1.*CoefPS14_1.*CoefPS16_1.*t4.*2.0+CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*t6-CoefPS8_1.*CoefPS14_1.*CoefPS16_1.*t2.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS11_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS12_1.*CoefPS15_1.*2.0+CoefPS2_1.*CoefPS3_1.*CoefPS4_1.*CoefPS12_1.*CoefPS14_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS3_1.*CoefPS15_1.*CoefPS16_1.*2.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS11_1.*CoefPS15_1.*4.0-CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS12_1.*CoefPS14_1.*4.0-CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS9_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS10_1.*CoefPS13_1.*3.0+CoefPS1_1.*CoefPS3_1.*CoefPS4_1.*CoefPS14_1.*CoefPS16_1.*2.0-CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS11_1.*CoefPS14_1+CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS12_1.*CoefPS13_1.*3.0+CoefPS3_1.*CoefPS4_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS7_1.*CoefPS14_1.*CoefPS16_1.*4.0+CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS3_1.*CoefPS8_1.*CoefPS14_1.*CoefPS15_1+CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS7_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS13_1.*CoefPS16_1.*3.0;
    // 'CharPolyAlpha1:59' et16 =
    // -CoefPS2_1.*CoefPS3_1.*CoefPS7_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS6_1.*CoefPS14_1.*CoefPS15_1-CoefPS2_1.*CoefPS7_1.*CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*4.0+CoefPS3_1.*CoefPS4_1.*CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*2.0-CoefPS1_1.*CoefPS7_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS2_1.*CoefPS6_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS3_1.*CoefPS7_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0-CoefPS4_1.*CoefPS6_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0;
    // 'CharPolyAlpha1:60' et17 =
    // -CoefPS12_1.*CoefPS13_1.*t9+CoefPS12_1.*CoefPS16_1.*t5.*2.0+CoefPS1_1.*t4.*t21.*3.0+CoefPS1_1.*t13.*t19+CoefPS7_1.*t4.*t20+CoefPS7_1.*t13.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*t20.*2.0+CoefPS2_1.*CoefPS7_1.*CoefPS8_1.*t19.*2.0-CoefPS2_1.*CoefPS11_1.*CoefPS13_1.*t13.*2.0+CoefPS2_1.*CoefPS12_1.*CoefPS14_1.*t8-CoefPS1_1.*CoefPS13_1.*CoefPS15_1.*t13.*2.0-CoefPS3_1.*CoefPS13_1.*CoefPS14_1.*t13-CoefPS4_1.*CoefPS11_1.*CoefPS16_1.*t4-CoefPS4_1.*CoefPS12_1.*CoefPS15_1.*t4+CoefPS1_1.*CoefPS14_1.*CoefPS16_1.*t8-CoefPS3_1.*CoefPS13_1.*CoefPS16_1.*t8.*3.0+CoefPS8_1.*CoefPS11_1.*CoefPS13_1.*t8-CoefPS3_1.*CoefPS15_1.*CoefPS16_1.*t4+CoefPS8_1.*CoefPS11_1.*CoefPS15_1.*t4.*2.0-CoefPS8_1.*CoefPS12_1.*CoefPS14_1.*t4.*2.0+CoefPS7_1.*CoefPS13_1.*CoefPS15_1.*t8-CoefPS7_1.*CoefPS14_1.*CoefPS16_1.*t4.*2.0-CoefPS1_1.*CoefPS2_1.*CoefPS4_1.*CoefPS15_1.*CoefPS16_1.*2.0+CoefPS2_1.*CoefPS3_1.*CoefPS4_1.*CoefPS14_1.*CoefPS16_1.*2.0-CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS11_1.*CoefPS14_1+CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS12_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS2_1.*CoefPS8_1.*CoefPS14_1.*CoefPS16_1.*4.0+CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS1_1.*CoefPS4_1.*CoefPS8_1.*CoefPS14_1.*CoefPS15_1+CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS3_1.*CoefPS8_1.*CoefPS14_1.*CoefPS15_1;
    // 'CharPolyAlpha1:61' et18 =
    // CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS7_1.*CoefPS14_1.*CoefPS15_1+CoefPS3_1.*CoefPS4_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*2.0-CoefPS2_1.*CoefPS7_1.*CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*4.0-CoefPS4_1.*CoefPS7_1.*CoefPS8_1.*CoefPS13_1.*CoefPS14_1.*2.0;
    // 'CharPolyAlpha1:62' mt1 =
    // [CoefPS5_1.^3.*t18+CoefPS5_1.*t2.*t14-CoefPS1_1.*CoefPS9_1.*CoefPS13_1.*t10.*2.0,CoefPS6_1.*t2.*t14+CoefPS6_1.*t10.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*t14.*2.0-CoefPS2_1.*CoefPS9_1.*CoefPS13_1.*t10.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS11_1.*t2.*2.0-CoefPS1_1.*CoefPS11_1.*CoefPS13_1.*t10.*2.0-CoefPS1_1.*CoefPS5_1.*CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*4.0];
    // 'CharPolyAlpha1:63' mt2 =
    // [t3.*t15+CoefPS1_1.*t10.*t19+CoefPS5_1.*t2.*t16+CoefPS5_1.*t4.*t14+CoefPS5_1.*t11.*t18.*3.0+CoefPS7_1.*t2.*t14+CoefPS7_1.*t10.*t18.*3.0+CoefPS1_1.*CoefPS2_1.*CoefPS6_1.*t14.*2.0-CoefPS3_1.*CoefPS9_1.*CoefPS10_1.*t2-CoefPS1_1.*CoefPS9_1.*CoefPS13_1.*t11.*2.0+CoefPS6_1.*CoefPS9_1.*CoefPS11_1.*t2.*2.0-CoefPS2_1.*CoefPS11_1.*CoefPS13_1.*t10.*2.0+CoefPS5_1.*CoefPS9_1.*CoefPS13_1.*t6+CoefPS5_1.*CoefPS9_1.*CoefPS15_1.*t2.*2.0-CoefPS5_1.*CoefPS10_1.*CoefPS14_1.*t2.*2.0-CoefPS1_1.*CoefPS13_1.*CoefPS15_1.*t10.*2.0-CoefPS3_1.*CoefPS13_1.*CoefPS14_1.*t10+CoefPS1_1.*CoefPS2_1.*CoefPS5_1.*CoefPS9_1.*CoefPS11_1.*4.0-CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS9_1.*CoefPS14_1+CoefPS1_1.*CoefPS3_1.*CoefPS5_1.*CoefPS10_1.*CoefPS13_1.*3.0-CoefPS1_1.*CoefPS5_1.*CoefPS7_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS2_1.*CoefPS5_1.*CoefPS6_1.*CoefPS9_1.*CoefPS13_1.*4.0-CoefPS1_1.*CoefPS5_1.*CoefPS6_1.*CoefPS11_1.*CoefPS13_1.*4.0,et1+et2,et3+et4+et5,et6+et7+et8+et9,et10+et11+et12+et13,et14+et15+et16,et17+et18];
    // 'CharPolyAlpha1:64' mt3 =
    // [t5.*t21+CoefPS8_1.^3.*t18-CoefPS13_1.*CoefPS16_1.*t9+CoefPS2_1.*t13.*t19+CoefPS8_1.*t4.*t20-CoefPS2_1.*CoefPS13_1.*CoefPS15_1.*t13.*2.0-CoefPS4_1.*CoefPS13_1.*CoefPS14_1.*t13+CoefPS2_1.*CoefPS14_1.*CoefPS16_1.*t8-CoefPS4_1.*CoefPS15_1.*CoefPS16_1.*t4+CoefPS8_1.*CoefPS13_1.*CoefPS15_1.*t8-CoefPS8_1.*CoefPS14_1.*CoefPS16_1.*t4.*2.0+CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS13_1.*CoefPS16_1.*3.0-CoefPS2_1.*CoefPS4_1.*CoefPS8_1.*CoefPS14_1.*CoefPS15_1];
    // 'CharPolyAlpha1:65' Coeff_Poly_Alpha1 = [mt1,mt2,mt3];
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
    eb_Coeff_Poly_Alpha1_tmp = in1[4] * in1[10];
    fb_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp * in1[5];
    c_Coeff_Poly_Alpha1_tmp_tmp = in1[0] * in1[3];
    gb_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp_tmp * in1[4];
    d_Coeff_Poly_Alpha1_tmp_tmp = in1[1] * in1[2];
    hb_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[4];
    ib_Coeff_Poly_Alpha1_tmp = in1[4] * in1[5];
    jb_Coeff_Poly_Alpha1_tmp = in1[3] * in1[8];
    kb_Coeff_Poly_Alpha1_tmp = in1[2] * in1[9];
    lb_Coeff_Poly_Alpha1_tmp = in1[6] * in1[8];
    e_Coeff_Poly_Alpha1_tmp_tmp = c_Coeff_Poly_Alpha1_tmp * in1[2];
    mb_Coeff_Poly_Alpha1_tmp = e_Coeff_Poly_Alpha1_tmp_tmp * in1[8];
    nb_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp * in1[6];
    ob_Coeff_Poly_Alpha1_tmp = o_Coeff_Poly_Alpha1_tmp * in1[8];
    pb_Coeff_Poly_Alpha1_tmp = in1[2] * in1[3];
    qb_Coeff_Poly_Alpha1_tmp = pb_Coeff_Poly_Alpha1_tmp * in1[4];
    rb_Coeff_Poly_Alpha1_tmp = in1[0] * in1[5];
    sb_Coeff_Poly_Alpha1_tmp = f_Coeff_Poly_Alpha1_tmp * in1[7];
    tb_Coeff_Poly_Alpha1_tmp = rb_Coeff_Poly_Alpha1_tmp * in1[6];
    ub_Coeff_Poly_Alpha1_tmp = q_Coeff_Poly_Alpha1_tmp * in1[6];
    vb_Coeff_Poly_Alpha1_tmp = in1[2] * in1[4];
    wb_Coeff_Poly_Alpha1_tmp = in1[1] * t2;
    xb_Coeff_Poly_Alpha1_tmp = in1[5] * t4;
    yb_Coeff_Poly_Alpha1_tmp = in1[7] * t2;
    ac_Coeff_Poly_Alpha1_tmp = jb_Coeff_Poly_Alpha1_tmp * in1[9];
    bc_Coeff_Poly_Alpha1_tmp = m_Coeff_Poly_Alpha1_tmp * in1[11];
    cc_Coeff_Poly_Alpha1_tmp = kb_Coeff_Poly_Alpha1_tmp * in1[10];
    dc_Coeff_Poly_Alpha1_tmp = lb_Coeff_Poly_Alpha1_tmp * in1[10];
    ec_Coeff_Poly_Alpha1_tmp = n_Coeff_Poly_Alpha1_tmp * in1[12];
    fc_Coeff_Poly_Alpha1_tmp = eb_Coeff_Poly_Alpha1_tmp * in1[12];
    gc_Coeff_Poly_Alpha1_tmp = n_Coeff_Poly_Alpha1_tmp * in1[14];
    hc_Coeff_Poly_Alpha1_tmp = in1[5] * in1[9] * in1[13];
    ic_Coeff_Poly_Alpha1_tmp = in1[1] * in1[12] * in1[14];
    jc_Coeff_Poly_Alpha1_tmp = eb_Coeff_Poly_Alpha1_tmp * in1[14];
    kc_Coeff_Poly_Alpha1_tmp = in1[4] * in1[11] * in1[13];
    f_Coeff_Poly_Alpha1_tmp_tmp = in1[3] * in1[12];
    lc_Coeff_Poly_Alpha1_tmp = f_Coeff_Poly_Alpha1_tmp_tmp * in1[13];
    mc_Coeff_Poly_Alpha1_tmp = in1[9] * in1[11];
    Coeff_Poly_Alpha1[3] = (((((((((((((((((((((((((((((((std::pow(in1[5], 3.0) * t18 +
                                                          mc_Coeff_Poly_Alpha1_tmp * t3 * 2.0) +
                                                         wb_Coeff_Poly_Alpha1_tmp * t15 * 3.0) +
                                                        in1[1] * t10 * t19) +
                                                       h_Coeff_Poly_Alpha1_tmp * t16) +
                                                      xb_Coeff_Poly_Alpha1_tmp * t14) +
                                                     yb_Coeff_Poly_Alpha1_tmp * t14) +
                                                    in1[7] * t10 * t18 * 3.0) +
                                                   e_Coeff_Poly_Alpha1_tmp * t16 * 2.0) +
                                                  nb_Coeff_Poly_Alpha1_tmp * t14 * 2.0) +
                                                 g_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
                                                ib_Coeff_Poly_Alpha1_tmp * in1[6] * t18 * 6.0) -
                                               ac_Coeff_Poly_Alpha1_tmp * t2) -
                                              bc_Coeff_Poly_Alpha1_tmp * t2) -
                                             cc_Coeff_Poly_Alpha1_tmp * t2) -
                                            i_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
                                           j_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
                                          k_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
                                         dc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) +
                                        ec_Coeff_Poly_Alpha1_tmp * t6) +
                                       fc_Coeff_Poly_Alpha1_tmp * t6) +
                                      gc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                                     hc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                                    ic_Coeff_Poly_Alpha1_tmp * t10 * 2.0) +
                                   jc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                                  kc_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                                 lc_Coeff_Poly_Alpha1_tmp * t10) -
                                mb_Coeff_Poly_Alpha1_tmp * in1[9] * 2.0) +
                               ob_Coeff_Poly_Alpha1_tmp * in1[10] * 4.0) +
                              p_Coeff_Poly_Alpha1_tmp * in1[14] * 4.0) -
                             e_Coeff_Poly_Alpha1_tmp * in1[9] * in1[13] * 4.0) -
                            fb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                           ((((((((((((((fb_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0 -
                                         gb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                                        gb_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
                                       hb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                                      hb_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
                                     l_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                                    l_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) +
                                   qb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 2.0) -
                                  sb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
                                 tb_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
                                ub_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
                               r_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) -
                              s_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) -
                             g_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
                            vb_Coeff_Poly_Alpha1_tmp * in1[5] * in1[12] * in1[13] * 2.0);
    nc_Coeff_Poly_Alpha1_tmp = in1[5] * in1[10];
    oc_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp * in1[6];
    pc_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp_tmp * in1[5];
    qc_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[5];
    g_Coeff_Poly_Alpha1_tmp_tmp = in1[1] * in1[3];
    rc_Coeff_Poly_Alpha1_tmp = g_Coeff_Poly_Alpha1_tmp_tmp * in1[4];
    sc_Coeff_Poly_Alpha1_tmp = in1[0] * in1[9];
    tc_Coeff_Poly_Alpha1_tmp = in1[1] * in1[9];
    uc_Coeff_Poly_Alpha1_tmp = in1[3] * in1[9];
    vc_Coeff_Poly_Alpha1_tmp = in1[2] * in1[10];
    wc_Coeff_Poly_Alpha1_tmp = in1[7] * in1[8];
    h_Coeff_Poly_Alpha1_tmp_tmp = c_Coeff_Poly_Alpha1_tmp * in1[3];
    xc_Coeff_Poly_Alpha1_tmp = h_Coeff_Poly_Alpha1_tmp_tmp * in1[8];
    yc_Coeff_Poly_Alpha1_tmp = e_Coeff_Poly_Alpha1_tmp_tmp * in1[9];
    ad_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp * in1[7];
    bd_Coeff_Poly_Alpha1_tmp = nb_Coeff_Poly_Alpha1_tmp * in1[8];
    cd_Coeff_Poly_Alpha1_tmp = pb_Coeff_Poly_Alpha1_tmp * in1[5];
    dd_Coeff_Poly_Alpha1_tmp = in1[1] * in1[5];
    ed_Coeff_Poly_Alpha1_tmp = rb_Coeff_Poly_Alpha1_tmp * in1[7];
    fd_Coeff_Poly_Alpha1_tmp = q_Coeff_Poly_Alpha1_tmp * in1[7];
    gd_Coeff_Poly_Alpha1_tmp = dd_Coeff_Poly_Alpha1_tmp * in1[6];
    hd_Coeff_Poly_Alpha1_tmp = in1[3] * in1[4];
    id_Coeff_Poly_Alpha1_tmp = in1[0] * t4;
    jd_Coeff_Poly_Alpha1_tmp = in1[6] * t4;
    kd_Coeff_Poly_Alpha1_tmp = jb_Coeff_Poly_Alpha1_tmp * in1[11];
    ld_Coeff_Poly_Alpha1_tmp = uc_Coeff_Poly_Alpha1_tmp * in1[10];
    md_Coeff_Poly_Alpha1_tmp = sc_Coeff_Poly_Alpha1_tmp * in1[13];
    nd_Coeff_Poly_Alpha1_tmp = vc_Coeff_Poly_Alpha1_tmp * in1[11];
    od_Coeff_Poly_Alpha1_tmp = m_Coeff_Poly_Alpha1_tmp * in1[15];
    pd_Coeff_Poly_Alpha1_tmp = kb_Coeff_Poly_Alpha1_tmp * in1[14];
    qd_Coeff_Poly_Alpha1_tmp = wc_Coeff_Poly_Alpha1_tmp * in1[10];
    rd_Coeff_Poly_Alpha1_tmp = lb_Coeff_Poly_Alpha1_tmp * in1[12];
    sd_Coeff_Poly_Alpha1_tmp = nc_Coeff_Poly_Alpha1_tmp * in1[12];
    td_Coeff_Poly_Alpha1_tmp = lb_Coeff_Poly_Alpha1_tmp * in1[14];
    ud_Coeff_Poly_Alpha1_tmp = in1[6] * in1[9] * in1[13];
    vd_Coeff_Poly_Alpha1_tmp = nc_Coeff_Poly_Alpha1_tmp * in1[14];
    wd_Coeff_Poly_Alpha1_tmp = in1[5] * in1[11] * in1[13];
    xd_Coeff_Poly_Alpha1_tmp = in1[4] * in1[12] * in1[14];
    yd_Coeff_Poly_Alpha1_tmp = in1[4] * in1[13] * in1[15];
    ae_Coeff_Poly_Alpha1_tmp = in1[9] * in1[12];
    be_Coeff_Poly_Alpha1_tmp = in1[9] * in1[15];
    Coeff_Poly_Alpha1[4] =
        (((((((((((((((((((((((((((((((((((t3 * t17 - ae_Coeff_Poly_Alpha1_tmp * t7) +
                                          be_Coeff_Poly_Alpha1_tmp * t3 * 2.0) +
                                         id_Coeff_Poly_Alpha1_tmp * t15 * 3.0) +
                                        in1[0] * t11 * t19) +
                                       t_Coeff_Poly_Alpha1_tmp * t16) +
                                      Coeff_Poly_Alpha1_tmp * t20) +
                                     in1[4] * t12 * t18 * 3.0) +
                                    u_Coeff_Poly_Alpha1_tmp * t16) +
                                   jd_Coeff_Poly_Alpha1_tmp * t14) +
                                  in1[6] * t11 * t18 * 3.0) +
                                 o_Coeff_Poly_Alpha1_tmp * t16 * 2.0) +
                                ad_Coeff_Poly_Alpha1_tmp * t14 * 2.0) +
                               r_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
                              s_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
                             ib_Coeff_Poly_Alpha1_tmp * in1[7] * t18 * 6.0) -
                            v_Coeff_Poly_Alpha1_tmp * t4) -
                           b_Coeff_Poly_Alpha1_tmp * t12 * 2.0) +
                          tc_Coeff_Poly_Alpha1_tmp * in1[11] * t2 * 6.0) -
                         kd_Coeff_Poly_Alpha1_tmp * t2) -
                        ld_Coeff_Poly_Alpha1_tmp * t2) +
                       md_Coeff_Poly_Alpha1_tmp * t6) -
                      nd_Coeff_Poly_Alpha1_tmp * t2) +
                     w_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
                    x_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
                   y_Coeff_Poly_Alpha1_tmp * t8) -
                  od_Coeff_Poly_Alpha1_tmp * t2) -
                 pd_Coeff_Poly_Alpha1_tmp * t2) +
                qd_Coeff_Poly_Alpha1_tmp * t2 * 2.0) +
               ab_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
              bb_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
             rd_Coeff_Poly_Alpha1_tmp * t6) -
            cb_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
           sd_Coeff_Poly_Alpha1_tmp * t6) -
          db_Coeff_Poly_Alpha1_tmp * t11) +
         ((((((((((((((((((((((((((td_Coeff_Poly_Alpha1_tmp * t2 * 2.0 -
                                   ud_Coeff_Poly_Alpha1_tmp * t2 * 2.0) +
                                  vd_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                                 wd_Coeff_Poly_Alpha1_tmp * t2 * 2.0) +
                                xd_Coeff_Poly_Alpha1_tmp * t6) -
                               yd_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                              xc_Coeff_Poly_Alpha1_tmp * in1[9] * 2.0) -
                             mb_Coeff_Poly_Alpha1_tmp * in1[11] * 2.0) -
                            yc_Coeff_Poly_Alpha1_tmp * in1[10] * 2.0) +
                           bd_Coeff_Poly_Alpha1_tmp * in1[10] * 4.0) +
                          ob_Coeff_Poly_Alpha1_tmp * in1[14] * 4.0) -
                         o_Coeff_Poly_Alpha1_tmp * in1[9] * in1[13] * 4.0) +
                        e_Coeff_Poly_Alpha1_tmp * in1[10] * in1[14] * 4.0) -
                       e_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 4.0) -
                      oc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                     oc_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
                    pc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                   pc_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
                  qc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                 qc_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
                rc_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
               rc_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
              fb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
             fb_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
            gb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
           gb_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
          hb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13])) +
        ((((((((((((((hb_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0 +
                      cd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 2.0) +
                     qb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 2.0) -
                    ed_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
                   fd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
                  gd_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) +
                 l_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
                l_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) -
               sb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) -
              tb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) -
             ub_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) -
            r_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
           s_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
          vb_Coeff_Poly_Alpha1_tmp * in1[6] * in1[12] * in1[13] * 2.0) -
         hd_Coeff_Poly_Alpha1_tmp * in1[5] * in1[12] * in1[13] * 2.0);
    ce_Coeff_Poly_Alpha1_tmp = in1[6] * in1[10];
    de_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp * in1[7];
    ee_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp_tmp * in1[6];
    fe_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[6];
    ge_Coeff_Poly_Alpha1_tmp = g_Coeff_Poly_Alpha1_tmp_tmp * in1[5];
    he_Coeff_Poly_Alpha1_tmp = h_Coeff_Poly_Alpha1_tmp_tmp * in1[9];
    ie_Coeff_Poly_Alpha1_tmp = e_Coeff_Poly_Alpha1_tmp_tmp * in1[10];
    je_Coeff_Poly_Alpha1_tmp = Coeff_Poly_Alpha1_tmp_tmp * in1[3];
    ke_Coeff_Poly_Alpha1_tmp = ad_Coeff_Poly_Alpha1_tmp * in1[8];
    le_Coeff_Poly_Alpha1_tmp = pb_Coeff_Poly_Alpha1_tmp * in1[6];
    me_Coeff_Poly_Alpha1_tmp = in1[0] * in1[6] * in1[7];
    ne_Coeff_Poly_Alpha1_tmp = dd_Coeff_Poly_Alpha1_tmp * in1[7];
    oe_Coeff_Poly_Alpha1_tmp = in1[2] * in1[5];
    pe_Coeff_Poly_Alpha1_tmp = in1[7] * t4;
    qe_Coeff_Poly_Alpha1_tmp = tc_Coeff_Poly_Alpha1_tmp * in1[13];
    i_Coeff_Poly_Alpha1_tmp_tmp = in1[3] * in1[10];
    re_Coeff_Poly_Alpha1_tmp = i_Coeff_Poly_Alpha1_tmp_tmp * in1[11];
    j_Coeff_Poly_Alpha1_tmp_tmp = in1[0] * in1[11];
    se_Coeff_Poly_Alpha1_tmp = j_Coeff_Poly_Alpha1_tmp_tmp * in1[13];
    te_Coeff_Poly_Alpha1_tmp = in1[2] * in1[11];
    ue_Coeff_Poly_Alpha1_tmp = jb_Coeff_Poly_Alpha1_tmp * in1[15];
    ve_Coeff_Poly_Alpha1_tmp = uc_Coeff_Poly_Alpha1_tmp * in1[14];
    we_Coeff_Poly_Alpha1_tmp = vc_Coeff_Poly_Alpha1_tmp * in1[15];
    xe_Coeff_Poly_Alpha1_tmp = te_Coeff_Poly_Alpha1_tmp * in1[14];
    ye_Coeff_Poly_Alpha1_tmp = wc_Coeff_Poly_Alpha1_tmp * in1[12];
    af_Coeff_Poly_Alpha1_tmp = ce_Coeff_Poly_Alpha1_tmp * in1[12];
    bf_Coeff_Poly_Alpha1_tmp = wc_Coeff_Poly_Alpha1_tmp * in1[14];
    cf_Coeff_Poly_Alpha1_tmp = in1[7] * in1[9] * in1[13];
    df_Coeff_Poly_Alpha1_tmp = ce_Coeff_Poly_Alpha1_tmp * in1[14];
    ef_Coeff_Poly_Alpha1_tmp = in1[6] * in1[11] * in1[13];
    ff_Coeff_Poly_Alpha1_tmp = in1[5] * in1[12] * in1[14];
    gf_Coeff_Poly_Alpha1_tmp = in1[5] * in1[13] * in1[15];
    hf_Coeff_Poly_Alpha1_tmp = in1[11] * in1[15];
    Coeff_Poly_Alpha1[5] =
        ((((((((((((((((((((((((((((((((((((t5 * t15 - in1[11] * in1[12] * t7) +
                                           hf_Coeff_Poly_Alpha1_tmp * t3 * 2.0) +
                                          wb_Coeff_Poly_Alpha1_tmp * t17 * 3.0) +
                                         in1[1] * t11 * t19) +
                                        xb_Coeff_Poly_Alpha1_tmp * t16) +
                                       h_Coeff_Poly_Alpha1_tmp * t20) +
                                      in1[5] * t12 * t18 * 3.0) +
                                     yb_Coeff_Poly_Alpha1_tmp * t16) +
                                    pe_Coeff_Poly_Alpha1_tmp * t14) +
                                   in1[7] * t11 * t18 * 3.0) +
                                  e_Coeff_Poly_Alpha1_tmp * t20 * 2.0) +
                                 nb_Coeff_Poly_Alpha1_tmp * t16 * 2.0) +
                                sb_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
                               tb_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
                              ub_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
                             in1[4] * in1[6] * in1[7] * t18 * 6.0) +
                            sc_Coeff_Poly_Alpha1_tmp * in1[11] * t4 * 6.0) -
                           ac_Coeff_Poly_Alpha1_tmp * t4) -
                          bc_Coeff_Poly_Alpha1_tmp * t4) -
                         cc_Coeff_Poly_Alpha1_tmp * t4) -
                        i_Coeff_Poly_Alpha1_tmp * t12 * 2.0) -
                       k_Coeff_Poly_Alpha1_tmp * t12 * 2.0) +
                      qe_Coeff_Poly_Alpha1_tmp * t6) -
                     re_Coeff_Poly_Alpha1_tmp * t2) +
                    dc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
                   se_Coeff_Poly_Alpha1_tmp * t6) -
                  uc_Coeff_Poly_Alpha1_tmp * in1[12] * t6 * 3.0) +
                 tc_Coeff_Poly_Alpha1_tmp * in1[15] * t2 * 6.0) +
                ec_Coeff_Poly_Alpha1_tmp * t8) -
               ue_Coeff_Poly_Alpha1_tmp * t2) -
              ve_Coeff_Poly_Alpha1_tmp * t2) +
             fc_Coeff_Poly_Alpha1_tmp * t8) -
            we_Coeff_Poly_Alpha1_tmp * t2) -
           xe_Coeff_Poly_Alpha1_tmp * t2) +
          (((((((((((((((((((((((((((gc_Coeff_Poly_Alpha1_tmp * t4 * 2.0 -
                                     hc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
                                    ye_Coeff_Poly_Alpha1_tmp * t6) -
                                   ic_Coeff_Poly_Alpha1_tmp * t11 * 2.0) +
                                  jc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
                                 kc_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
                                af_Coeff_Poly_Alpha1_tmp * t6) -
                               lc_Coeff_Poly_Alpha1_tmp * t11) +
                              bf_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                             cf_Coeff_Poly_Alpha1_tmp * t2 * 2.0) +
                            df_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                           ef_Coeff_Poly_Alpha1_tmp * t2 * 2.0) +
                          ff_Coeff_Poly_Alpha1_tmp * t6) -
                         gf_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                        xc_Coeff_Poly_Alpha1_tmp * in1[11] * 2.0) -
                       he_Coeff_Poly_Alpha1_tmp * in1[10] * 2.0) -
                      ie_Coeff_Poly_Alpha1_tmp * in1[11] * 2.0) -
                     mb_Coeff_Poly_Alpha1_tmp * in1[15] * 2.0) -
                    yc_Coeff_Poly_Alpha1_tmp * in1[14] * 2.0) +
                   ke_Coeff_Poly_Alpha1_tmp * in1[10] * 4.0) +
                  je_Coeff_Poly_Alpha1_tmp * in1[9] * in1[13] * 2.0) +
                 bd_Coeff_Poly_Alpha1_tmp * in1[14] * 4.0) -
                nb_Coeff_Poly_Alpha1_tmp * in1[9] * in1[13] * 4.0) +
               o_Coeff_Poly_Alpha1_tmp * in1[10] * in1[14] * 4.0) -
              o_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 4.0) -
             de_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
            de_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
           ee_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13])) +
         (((((((((((((((((((((((((ee_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0 -
                                  fe_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                                 fe_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
                                ge_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                               ge_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
                              oc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                             oc_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                            pc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                           pc_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                          qc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                         qc_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                        rc_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                       rc_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) +
                      le_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 2.0) +
                     cd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 2.0) -
                    e_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 4.0) -
                   me_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) -
                  ne_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) +
                 fb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
                fb_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
               gb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
              gb_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) -
             ed_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) +
            hb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
           hb_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) -
          fd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0)) +
        (((((((gd_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * -4.0 +
               qb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 2.0) -
              sb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
             tb_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
            ub_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
           vb_Coeff_Poly_Alpha1_tmp * in1[7] * in1[12] * in1[13] * 2.0) -
          oe_Coeff_Poly_Alpha1_tmp * in1[6] * in1[12] * in1[13] * 2.0) -
         hd_Coeff_Poly_Alpha1_tmp * in1[6] * in1[12] * in1[13] * 2.0);
    if_Coeff_Poly_Alpha1_tmp = in1[1] * in1[11];
    jf_Coeff_Poly_Alpha1_tmp = in1[3] * in1[11];
    kf_Coeff_Poly_Alpha1_tmp = in1[7] * in1[10];
    lf_Coeff_Poly_Alpha1_tmp = c_Coeff_Poly_Alpha1_tmp_tmp * in1[7];
    mf_Coeff_Poly_Alpha1_tmp = g_Coeff_Poly_Alpha1_tmp_tmp * in1[6];
    nf_Coeff_Poly_Alpha1_tmp = h_Coeff_Poly_Alpha1_tmp_tmp * in1[10];
    of_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[3];
    pf_Coeff_Poly_Alpha1_tmp = d_Coeff_Poly_Alpha1_tmp_tmp * in1[7];
    qf_Coeff_Poly_Alpha1_tmp = pb_Coeff_Poly_Alpha1_tmp * in1[7];
    rf_Coeff_Poly_Alpha1_tmp = -in1[1] * in1[2];
    sf_Coeff_Poly_Alpha1_tmp = in1[1] * in1[6] * in1[7];
    tf_Coeff_Poly_Alpha1_tmp = in1[3] * in1[5];
    uf_Coeff_Poly_Alpha1_tmp = if_Coeff_Poly_Alpha1_tmp * in1[13];
    vf_Coeff_Poly_Alpha1_tmp = jf_Coeff_Poly_Alpha1_tmp * in1[14];
    wf_Coeff_Poly_Alpha1_tmp = in1[0] * in1[13] * in1[15];
    xf_Coeff_Poly_Alpha1_tmp = kf_Coeff_Poly_Alpha1_tmp * in1[12];
    yf_Coeff_Poly_Alpha1_tmp = in1[2] * in1[14] * in1[15];
    ag_Coeff_Poly_Alpha1_tmp = kf_Coeff_Poly_Alpha1_tmp * in1[14];
    bg_Coeff_Poly_Alpha1_tmp = in1[7] * in1[11] * in1[13];
    cg_Coeff_Poly_Alpha1_tmp = in1[6] * in1[12] * in1[14];
    dg_Coeff_Poly_Alpha1_tmp = in1[6] * in1[13] * in1[15];
    eg_Coeff_Poly_Alpha1_tmp = in1[12] * in1[15];
    Coeff_Poly_Alpha1[6] =
        (((((((((((((((((((((((((((((((((((t3 * t21 + std::pow(in1[6], 3.0) * t18) +
                                          mc_Coeff_Poly_Alpha1_tmp * t5 * 2.0) -
                                         eg_Coeff_Poly_Alpha1_tmp * t7) +
                                        id_Coeff_Poly_Alpha1_tmp * t17 * 3.0) +
                                       in1[0] * t12 * t19) +
                                      t_Coeff_Poly_Alpha1_tmp * t20) +
                                     in1[4] * t13 * t18 * 3.0) +
                                    jd_Coeff_Poly_Alpha1_tmp * t16) +
                                   u_Coeff_Poly_Alpha1_tmp * t20) +
                                  o_Coeff_Poly_Alpha1_tmp * t20 * 2.0) +
                                 ad_Coeff_Poly_Alpha1_tmp * t16 * 2.0) +
                                ed_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
                               fd_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
                              gd_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
                             in1[5] * in1[6] * in1[7] * t18 * 6.0) -
                            b_Coeff_Poly_Alpha1_tmp * t13 * 2.0) -
                           kd_Coeff_Poly_Alpha1_tmp * t4) -
                          ld_Coeff_Poly_Alpha1_tmp * t4) +
                         md_Coeff_Poly_Alpha1_tmp * t8) -
                        nd_Coeff_Poly_Alpha1_tmp * t4) -
                       kb_Coeff_Poly_Alpha1_tmp * in1[12] * t8 * 3.0) -
                      x_Coeff_Poly_Alpha1_tmp * t12 * 2.0) +
                     sc_Coeff_Poly_Alpha1_tmp * in1[15] * t4 * 6.0) -
                    od_Coeff_Poly_Alpha1_tmp * t4) -
                   pd_Coeff_Poly_Alpha1_tmp * t4) +
                  qd_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
                 uf_Coeff_Poly_Alpha1_tmp * t6) -
                jf_Coeff_Poly_Alpha1_tmp * in1[12] * t6 * 3.0) +
               rd_Coeff_Poly_Alpha1_tmp * t8) -
              cb_Coeff_Poly_Alpha1_tmp * t12 * 2.0) +
             if_Coeff_Poly_Alpha1_tmp * in1[15] * t2 * 6.0) +
            sd_Coeff_Poly_Alpha1_tmp * t8) -
           db_Coeff_Poly_Alpha1_tmp * t12) +
          (((((((((((((((((((((((((((-in1[3] * in1[10] * in1[15] * t2 -
                                     vf_Coeff_Poly_Alpha1_tmp * t2) +
                                    td_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
                                   ud_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
                                  wf_Coeff_Poly_Alpha1_tmp * t6) +
                                 vd_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
                                wd_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
                               xf_Coeff_Poly_Alpha1_tmp * t6) +
                              xd_Coeff_Poly_Alpha1_tmp * t8) -
                             yf_Coeff_Poly_Alpha1_tmp * t2) +
                            ag_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                           bg_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                          yd_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
                         cg_Coeff_Poly_Alpha1_tmp * t6) -
                        dg_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                       nf_Coeff_Poly_Alpha1_tmp * in1[11] * 2.0) -
                      xc_Coeff_Poly_Alpha1_tmp * in1[15] * 2.0) -
                     he_Coeff_Poly_Alpha1_tmp * in1[14] * 2.0) -
                    ie_Coeff_Poly_Alpha1_tmp * in1[15] * 2.0) -
                   e_Coeff_Poly_Alpha1_tmp_tmp * in1[11] * in1[14] * 2.0) +
                  of_Coeff_Poly_Alpha1_tmp * in1[9] * in1[13] * 2.0) +
                 je_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 2.0) +
                ke_Coeff_Poly_Alpha1_tmp * in1[14] * 4.0) -
               ad_Coeff_Poly_Alpha1_tmp * in1[9] * in1[13] * 4.0) +
              nb_Coeff_Poly_Alpha1_tmp * in1[10] * in1[14] * 4.0) -
             nb_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 4.0) -
            lf_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
           lf_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0)) +
         (((((((((((((((((((((((((rf_Coeff_Poly_Alpha1_tmp * in1[7] * in1[8] * in1[13] +
                                  pf_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
                                 mf_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                                mf_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) -
                               de_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                              de_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                             ee_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                            ee_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                           fe_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                          fe_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                         ge_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                        ge_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) +
                       qf_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 2.0) +
                      le_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 2.0) -
                     o_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 4.0) -
                    sf_Coeff_Poly_Alpha1_tmp * in1[8] * in1[12] * 4.0) +
                   oc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
                  oc_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
                 pc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
                pc_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) -
               me_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) +
              qc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
             qc_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
            rc_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
           rc_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) -
          ne_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0)) +
        ((((((cd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 2.0 -
              ed_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
             fd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
            gd_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
           oe_Coeff_Poly_Alpha1_tmp * in1[7] * in1[12] * in1[13] * 2.0) -
          hd_Coeff_Poly_Alpha1_tmp * in1[7] * in1[12] * in1[13] * 2.0) -
         tf_Coeff_Poly_Alpha1_tmp * in1[6] * in1[12] * in1[13] * 2.0);
    fg_Coeff_Poly_Alpha1_tmp = g_Coeff_Poly_Alpha1_tmp_tmp * in1[7];
    gg_Coeff_Poly_Alpha1_tmp = in1[1] * in1[13] * in1[15];
    hg_Coeff_Poly_Alpha1_tmp = in1[3] * in1[14] * in1[15];
    ig_Coeff_Poly_Alpha1_tmp = in1[7] * in1[12] * in1[14];
    jg_Coeff_Poly_Alpha1_tmp = in1[7] * in1[13] * in1[15];
    Coeff_Poly_Alpha1[7] =
        ((((((((((((((((((((((((((((((((((t5 * t17 - ae_Coeff_Poly_Alpha1_tmp * t9) +
                                         be_Coeff_Poly_Alpha1_tmp * t5 * 2.0) +
                                        wb_Coeff_Poly_Alpha1_tmp * t21 * 3.0) +
                                       in1[1] * t12 * t19) +
                                      xb_Coeff_Poly_Alpha1_tmp * t20) +
                                     in1[5] * t13 * t18 * 3.0) +
                                    pe_Coeff_Poly_Alpha1_tmp * t16) +
                                   yb_Coeff_Poly_Alpha1_tmp * t20) +
                                  in1[7] * t12 * t18 * 3.0) +
                                 nb_Coeff_Poly_Alpha1_tmp * t20 * 2.0) +
                                me_Coeff_Poly_Alpha1_tmp * t19 * 2.0) +
                               ne_Coeff_Poly_Alpha1_tmp * t19 * 2.0) -
                              i_Coeff_Poly_Alpha1_tmp * t13 * 2.0) -
                             k_Coeff_Poly_Alpha1_tmp * t13 * 2.0) +
                            qe_Coeff_Poly_Alpha1_tmp * t8) -
                           re_Coeff_Poly_Alpha1_tmp * t4) +
                          se_Coeff_Poly_Alpha1_tmp * t8) -
                         te_Coeff_Poly_Alpha1_tmp * in1[12] * t8 * 3.0) +
                        j_Coeff_Poly_Alpha1_tmp_tmp * in1[15] * t4 * 6.0) -
                       ue_Coeff_Poly_Alpha1_tmp * t4) -
                      ve_Coeff_Poly_Alpha1_tmp * t4) -
                     we_Coeff_Poly_Alpha1_tmp * t4) -
                    xe_Coeff_Poly_Alpha1_tmp * t4) +
                   ye_Coeff_Poly_Alpha1_tmp * t8) -
                  ic_Coeff_Poly_Alpha1_tmp * t12 * 2.0) +
                 af_Coeff_Poly_Alpha1_tmp * t8) -
                lc_Coeff_Poly_Alpha1_tmp * t12) +
               bf_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
              cf_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
             gg_Coeff_Poly_Alpha1_tmp * t6) +
            df_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
           ef_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
          f_Coeff_Poly_Alpha1_tmp_tmp * in1[15] * t6 * 3.0) +
         ((((((((((((((((((((((((((ff_Coeff_Poly_Alpha1_tmp * t8 - hg_Coeff_Poly_Alpha1_tmp * t2) -
                                  gf_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
                                 ig_Coeff_Poly_Alpha1_tmp * t6) -
                                jg_Coeff_Poly_Alpha1_tmp * t2 * 2.0) -
                               nf_Coeff_Poly_Alpha1_tmp * in1[15] * 2.0) -
                              h_Coeff_Poly_Alpha1_tmp_tmp * in1[11] * in1[14] * 2.0) +
                             of_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 2.0) -
                            e_Coeff_Poly_Alpha1_tmp_tmp * in1[14] * in1[15] * 2.0) +
                           ad_Coeff_Poly_Alpha1_tmp * in1[10] * in1[14] * 4.0) -
                          ad_Coeff_Poly_Alpha1_tmp * in1[11] * in1[13] * 4.0) -
                         fg_Coeff_Poly_Alpha1_tmp * in1[8] * in1[13]) +
                        fg_Coeff_Poly_Alpha1_tmp * in1[9] * in1[12] * 3.0) +
                       je_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 2.0) -
                      lf_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                     lf_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                    pf_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                   pf_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                  mf_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                 mf_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) +
                qf_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 2.0) -
               nb_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 4.0) +
              de_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
             de_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
            ee_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
           ee_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
          fe_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0)) +
        ((((((((rf_Coeff_Poly_Alpha1_tmp * in1[6] * in1[13] * in1[14] +
                ge_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
               ge_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) -
              sf_Coeff_Poly_Alpha1_tmp * in1[10] * in1[12] * 4.0) +
             le_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 2.0) -
            me_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
           ne_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
          in1[2] * in1[6] * in1[7] * in1[12] * in1[13] * 2.0) -
         tf_Coeff_Poly_Alpha1_tmp * in1[7] * in1[12] * in1[13] * 2.0);
    Coeff_Poly_Alpha1[8] = ((((((((((((((((((((((((((((((-in1[11] * in1[12] * t9 +
                                                         hf_Coeff_Poly_Alpha1_tmp * t5 * 2.0) +
                                                        id_Coeff_Poly_Alpha1_tmp * t21 * 3.0) +
                                                       in1[0] * t13 * t19) +
                                                      jd_Coeff_Poly_Alpha1_tmp * t20) +
                                                     in1[6] * t13 * t18 * 3.0) +
                                                    ad_Coeff_Poly_Alpha1_tmp * t20 * 2.0) +
                                                   sf_Coeff_Poly_Alpha1_tmp * t19 * 2.0) -
                                                  x_Coeff_Poly_Alpha1_tmp * t13 * 2.0) +
                                                 uf_Coeff_Poly_Alpha1_tmp * t8) -
                                                cb_Coeff_Poly_Alpha1_tmp * t13 * 2.0) -
                                               db_Coeff_Poly_Alpha1_tmp * t13) -
                                              i_Coeff_Poly_Alpha1_tmp_tmp * in1[15] * t4) -
                                             vf_Coeff_Poly_Alpha1_tmp * t4) +
                                            wf_Coeff_Poly_Alpha1_tmp * t8) -
                                           b_Coeff_Poly_Alpha1_tmp_tmp * in1[15] * t8 * 3.0) +
                                          xf_Coeff_Poly_Alpha1_tmp * t8) -
                                         yf_Coeff_Poly_Alpha1_tmp * t4) +
                                        ag_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
                                       bg_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
                                      cg_Coeff_Poly_Alpha1_tmp * t8) -
                                     dg_Coeff_Poly_Alpha1_tmp * t4 * 2.0) -
                                    h_Coeff_Poly_Alpha1_tmp_tmp * in1[14] * in1[15] * 2.0) +
                                   of_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 2.0) -
                                  fg_Coeff_Poly_Alpha1_tmp * in1[10] * in1[13]) +
                                 fg_Coeff_Poly_Alpha1_tmp * in1[11] * in1[12] * 3.0) -
                                ad_Coeff_Poly_Alpha1_tmp * in1[13] * in1[15] * 4.0) +
                               lf_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
                              lf_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
                             pf_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
                            pf_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
                           ((((mf_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0 -
                               mf_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14]) +
                              qf_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 2.0) -
                             sf_Coeff_Poly_Alpha1_tmp * in1[12] * in1[14] * 4.0) -
                            in1[3] * in1[6] * in1[7] * in1[12] * in1[13] * 2.0);
    Coeff_Poly_Alpha1[9] =
        (((((((((((t5 * t21 + std::pow(in1[7], 3.0) * t18) - eg_Coeff_Poly_Alpha1_tmp * t9) +
                 in1[1] * t13 * t19) +
                pe_Coeff_Poly_Alpha1_tmp * t20) -
               ic_Coeff_Poly_Alpha1_tmp * t13 * 2.0) -
              lc_Coeff_Poly_Alpha1_tmp * t13) +
             gg_Coeff_Poly_Alpha1_tmp * t8) -
            hg_Coeff_Poly_Alpha1_tmp * t4) +
           ig_Coeff_Poly_Alpha1_tmp * t8) -
          jg_Coeff_Poly_Alpha1_tmp * t4 * 2.0) +
         fg_Coeff_Poly_Alpha1_tmp * in1[12] * in1[15] * 3.0) -
        fg_Coeff_Poly_Alpha1_tmp * in1[13] * in1[14];
}

} // namespace ocn

//
// File trailer for CharPolyAlpha1.cpp
//
// [EOF]
//
