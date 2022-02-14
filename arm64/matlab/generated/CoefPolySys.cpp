//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: CoefPolySys.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 14-Feb-2022 16:27:55
//

// Include Files
#include "CoefPolySys.h"
#include <cmath>

// Function Definitions
//
// function CoefPS = CoefPolySys(in1,in2,in3,kappa0,in5,in6,in7,kappa1)
//
// COEFPOLYSYS
//     COEFPS = COEFPOLYSYS(IN1,IN2,IN3,KAPPA0,IN5,IN6,IN7,KAPPA1)
//
// Arguments    : const double in1[3]
//                const double in2[3]
//                const double in3[3]
//                double kappa0
//                const double in5[3]
//                const double in6[3]
//                const double in7[3]
//                double kappa1
//                double CoefPS[16]
// Return Type  : void
//
namespace ocn {
void CoefPolySys(const double in1[3], const double in2[3], const double in3[3], double kappa0,
                 const double in5[3], const double in6[3], const double in7[3], double kappa1,
                 double CoefPS[16])
{
    double CoefPS_tmp;
    double CoefPS_tmp_tmp;
    double CoefPS_tmp_tmp_tmp;
    double ab_CoefPS_tmp;
    double ac_CoefPS_tmp;
    double b_CoefPS_tmp;
    double b_CoefPS_tmp_tmp;
    double b_t201_tmp;
    double b_t203_tmp;
    double bb_CoefPS_tmp;
    double bc_CoefPS_tmp;
    double c_CoefPS_tmp;
    double c_CoefPS_tmp_tmp;
    double c_t201_tmp;
    double c_t203_tmp;
    double cb_CoefPS_tmp;
    double cc_CoefPS_tmp;
    double d;
    double d1;
    double d10;
    double d100;
    double d101;
    double d102;
    double d103;
    double d104;
    double d105;
    double d106;
    double d107;
    double d108;
    double d109;
    double d11;
    double d110;
    double d111;
    double d112;
    double d113;
    double d114;
    double d115;
    double d116;
    double d117;
    double d118;
    double d119;
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
    double d52;
    double d53;
    double d54;
    double d55;
    double d56;
    double d57;
    double d58;
    double d59;
    double d6;
    double d60;
    double d61;
    double d62;
    double d63;
    double d64;
    double d65;
    double d66;
    double d67;
    double d68;
    double d69;
    double d7;
    double d70;
    double d71;
    double d72;
    double d73;
    double d74;
    double d75;
    double d76;
    double d77;
    double d78;
    double d79;
    double d8;
    double d80;
    double d81;
    double d82;
    double d83;
    double d84;
    double d85;
    double d86;
    double d87;
    double d88;
    double d89;
    double d9;
    double d90;
    double d91;
    double d92;
    double d93;
    double d94;
    double d95;
    double d96;
    double d97;
    double d98;
    double d99;
    double d_CoefPS_tmp;
    double d_CoefPS_tmp_tmp;
    double d_t203_tmp;
    double db_CoefPS_tmp;
    double dc_CoefPS_tmp;
    double e_CoefPS_tmp;
    double e_CoefPS_tmp_tmp;
    double e_t203_tmp;
    double eb_CoefPS_tmp;
    double ec_CoefPS_tmp;
    double f_CoefPS_tmp;
    double f_CoefPS_tmp_tmp;
    double f_t203_tmp;
    double fb_CoefPS_tmp;
    double fc_CoefPS_tmp;
    double g_CoefPS_tmp;
    double g_CoefPS_tmp_tmp;
    double g_t203_tmp;
    double gb_CoefPS_tmp;
    double gc_CoefPS_tmp;
    double h_CoefPS_tmp;
    double h_t203_tmp;
    double hb_CoefPS_tmp;
    double hc_CoefPS_tmp;
    double i_CoefPS_tmp;
    double i_t203_tmp;
    double ib_CoefPS_tmp;
    double ic_CoefPS_tmp;
    double j_CoefPS_tmp;
    double jb_CoefPS_tmp;
    double jc_CoefPS_tmp;
    double k_CoefPS_tmp;
    double kb_CoefPS_tmp;
    double l_CoefPS_tmp;
    double lb_CoefPS_tmp;
    double m_CoefPS_tmp;
    double mb_CoefPS_tmp;
    double n_CoefPS_tmp;
    double nb_CoefPS_tmp;
    double o_CoefPS_tmp;
    double ob_CoefPS_tmp;
    double p_CoefPS_tmp;
    double pb_CoefPS_tmp;
    double q_CoefPS_tmp;
    double qb_CoefPS_tmp;
    double r_CoefPS_tmp;
    double rb_CoefPS_tmp;
    double s_CoefPS_tmp;
    double sb_CoefPS_tmp;
    double t10;
    double t111;
    double t14;
    double t15;
    double t16;
    double t17;
    double t18;
    double t19;
    double t2;
    double t20;
    double t201;
    double t201_tmp;
    double t203;
    double t203_tmp;
    double t205;
    double t205_tmp;
    double t21;
    double t22;
    double t23;
    double t24;
    double t25;
    double t26;
    double t27;
    double t28;
    double t29;
    double t3;
    double t30;
    double t31;
    double t32;
    double t32_tmp;
    double t33;
    double t33_tmp;
    double t34;
    double t35;
    double t36;
    double t37;
    double t37_tmp;
    double t38;
    double t39;
    double t4;
    double t40;
    double t41;
    double t42;
    double t43;
    double t44;
    double t44_tmp;
    double t45;
    double t46;
    double t46_tmp;
    double t47;
    double t48;
    double t48_tmp;
    double t49;
    double t5;
    double t50;
    double t50_tmp;
    double t51;
    double t52;
    double t52_tmp;
    double t53;
    double t54;
    double t54_tmp;
    double t55;
    double t6;
    double t7;
    double t8;
    double t83;
    double t83_tmp;
    double t84;
    double t84_tmp;
    double t85;
    double t85_tmp;
    double t86;
    double t86_tmp;
    double t87;
    double t88;
    double t88_tmp;
    double t89;
    double t9;
    double t90;
    double t91;
    double t91_tmp;
    double t_CoefPS_tmp;
    double tb_CoefPS_tmp;
    double u_CoefPS_tmp;
    double ub_CoefPS_tmp;
    double v_CoefPS_tmp;
    double vb_CoefPS_tmp;
    double w_CoefPS_tmp;
    double wb_CoefPS_tmp;
    double x_CoefPS_tmp;
    double xb_CoefPS_tmp;
    double y_CoefPS_tmp;
    double yb_CoefPS_tmp;
    //     This function was generated by the Symbolic Math Toolbox version 8.3.
    //     25-May-2019 09:07:21
    // 'CoefPolySys:8' n01 = in3(1,:);
    // 'CoefPolySys:9' n02 = in3(2,:);
    // 'CoefPolySys:10' n03 = in3(3,:);
    // 'CoefPolySys:11' n11 = in7(1,:);
    // 'CoefPolySys:12' n12 = in7(2,:);
    // 'CoefPolySys:13' n13 = in7(3,:);
    // 'CoefPolySys:14' p01 = in1(1,:);
    // 'CoefPolySys:15' p02 = in1(2,:);
    // 'CoefPolySys:16' p03 = in1(3,:);
    // 'CoefPolySys:17' p11 = in5(1,:);
    // 'CoefPolySys:18' p12 = in5(2,:);
    // 'CoefPolySys:19' p13 = in5(3,:);
    // 'CoefPolySys:20' t01 = in2(1,:);
    // 'CoefPolySys:21' t02 = in2(2,:);
    // 'CoefPolySys:22' t03 = in2(3,:);
    // 'CoefPolySys:23' t11 = in6(1,:);
    // 'CoefPolySys:24' t12 = in6(2,:);
    // 'CoefPolySys:25' t13 = in6(3,:);
    // 'CoefPolySys:26' t2 = t01.*t11;
    t2 = in2[0] * in6[0];
    // 'CoefPolySys:27' t3 = t02.*t12;
    t3 = in2[1] * in6[1];
    // 'CoefPolySys:28' t4 = t03.*t13;
    t4 = in2[2] * in6[2];
    // 'CoefPolySys:29' t5 = n01.^2;
    t5 = std::pow(in3[0], 2.0);
    // 'CoefPolySys:30' t6 = n02.^2;
    t6 = std::pow(in3[1], 2.0);
    // 'CoefPolySys:31' t7 = n03.^2;
    t7 = std::pow(in3[2], 2.0);
    // 'CoefPolySys:32' t8 = n11.^2;
    t8 = std::pow(in7[0], 2.0);
    // 'CoefPolySys:33' t9 = n12.^2;
    t9 = std::pow(in7[1], 2.0);
    // 'CoefPolySys:34' t10 = n13.^2;
    t10 = std::pow(in7[2], 2.0);
    // 'CoefPolySys:35' t14 = t01.^2;
    t14 = std::pow(in2[0], 2.0);
    // 'CoefPolySys:36' t15 = t01.^3;
    t15 = std::pow(in2[0], 3.0);
    // 'CoefPolySys:37' t16 = t02.^2;
    t16 = std::pow(in2[1], 2.0);
    // 'CoefPolySys:38' t18 = t02.^3;
    t18 = std::pow(in2[1], 3.0);
    // 'CoefPolySys:39' t19 = t03.^2;
    t19 = std::pow(in2[2], 2.0);
    // 'CoefPolySys:40' t21 = t03.^3;
    t21 = std::pow(in2[2], 3.0);
    // 'CoefPolySys:41' t23 = t11.^2;
    t23 = std::pow(in6[0], 2.0);
    // 'CoefPolySys:42' t24 = t11.^3;
    t24 = std::pow(in6[0], 3.0);
    // 'CoefPolySys:43' t25 = t12.^2;
    t25 = std::pow(in6[1], 2.0);
    // 'CoefPolySys:44' t27 = t12.^3;
    t27 = std::pow(in6[1], 3.0);
    // 'CoefPolySys:45' t28 = t13.^2;
    t28 = std::pow(in6[2], 2.0);
    // 'CoefPolySys:46' t30 = t13.^3;
    t30 = std::pow(in6[2], 3.0);
    // 'CoefPolySys:47' t17 = t14.^2;
    t17 = std::pow(t14, 2.0);
    // 'CoefPolySys:48' t20 = t16.^2;
    t20 = std::pow(t16, 2.0);
    // 'CoefPolySys:49' t22 = t19.^2;
    t22 = std::pow(t19, 2.0);
    // 'CoefPolySys:50' t26 = t23.^2;
    t26 = std::pow(t23, 2.0);
    // 'CoefPolySys:51' t29 = t25.^2;
    t29 = std::pow(t25, 2.0);
    // 'CoefPolySys:52' t31 = t28.^2;
    t31 = std::pow(t28, 2.0);
    // 'CoefPolySys:53' t32 = n01.*t01.*t3;
    t32_tmp = in3[0] * in2[0];
    t32 = t32_tmp * t3;
    // 'CoefPolySys:54' t33 = n02.*t02.*t2;
    t33_tmp = in3[1] * in2[1];
    t33 = t33_tmp * t2;
    // 'CoefPolySys:55' t34 = n01.*t01.*t4;
    t34 = t32_tmp * t4;
    // 'CoefPolySys:56' t35 = n03.*t2.*t03;
    t35 = in3[2] * t2 * in2[2];
    // 'CoefPolySys:57' t36 = n02.*t02.*t4;
    t36 = t33_tmp * t4;
    // 'CoefPolySys:58' t37 = n03.*t03.*t3;
    t37_tmp = in3[2] * in2[2];
    t37 = t37_tmp * t3;
    // 'CoefPolySys:59' t38 = n11.*t3.*t11;
    t38 = in7[0] * t3 * in6[0];
    // 'CoefPolySys:60' t39 = n12.*t2.*t12;
    t39 = in7[1] * t2 * in6[1];
    // 'CoefPolySys:61' t40 = n11.*t4.*t11;
    t40 = in7[0] * t4 * in6[0];
    // 'CoefPolySys:62' t41 = n13.*t2.*t13;
    t41 = in7[2] * t2 * in6[2];
    // 'CoefPolySys:63' t42 = n12.*t4.*t12;
    t42 = in7[1] * t4 * in6[1];
    // 'CoefPolySys:64' t43 = n13.*t3.*t13;
    t43 = in7[2] * t3 * in6[2];
    // 'CoefPolySys:65' t44 = n01.*t11.*t16;
    t44_tmp = in3[0] * in6[0];
    t44 = t44_tmp * t16;
    // 'CoefPolySys:66' t45 = n01.*t11.*t19;
    t45 = t44_tmp * t19;
    // 'CoefPolySys:67' t46 = n02.*t12.*t14;
    t46_tmp = in3[1] * in6[1];
    t46 = t46_tmp * t14;
    // 'CoefPolySys:68' t47 = n02.*t12.*t19;
    t47 = t46_tmp * t19;
    // 'CoefPolySys:69' t48 = n03.*t13.*t14;
    t48_tmp = in3[2] * in6[2];
    t48 = t48_tmp * t14;
    // 'CoefPolySys:70' t49 = n03.*t13.*t16;
    t49 = t48_tmp * t16;
    // 'CoefPolySys:71' t50 = n11.*t01.*t25;
    t50_tmp = in7[0] * in2[0];
    t50 = t50_tmp * t25;
    // 'CoefPolySys:72' t51 = n11.*t01.*t28;
    t51 = t50_tmp * t28;
    // 'CoefPolySys:73' t52 = n12.*t02.*t23;
    t52_tmp = in7[1] * in2[1];
    t52 = t52_tmp * t23;
    // 'CoefPolySys:74' t53 = n12.*t02.*t28;
    t53 = t52_tmp * t28;
    // 'CoefPolySys:75' t54 = n13.*t03.*t23;
    t54_tmp = in7[2] * in2[2];
    t54 = t54_tmp * t23;
    // 'CoefPolySys:76' t55 = n13.*t03.*t25;
    t55 = t54_tmp * t25;
    // 'CoefPolySys:77' t56 = t2.*t3.*2.0;
    // 'CoefPolySys:78' t57 = t2.*t4.*2.0;
    // 'CoefPolySys:79' t58 = t3.*t4.*2.0;
    // 'CoefPolySys:80' t59 = n01.*n12.*t02.*t4.*t11;
    // 'CoefPolySys:81' t60 = n01.*n13.*t03.*t3.*t11;
    // 'CoefPolySys:82' t61 = n02.*n11.*t01.*t4.*t12;
    // 'CoefPolySys:83' t62 = n02.*n13.*t2.*t03.*t12;
    // 'CoefPolySys:84' t63 = n03.*n11.*t01.*t3.*t13;
    // 'CoefPolySys:85' t64 = n03.*n12.*t02.*t2.*t13;
    // 'CoefPolySys:86' t83 = t2.^2.*8.0;
    t83_tmp = std::pow(t2, 2.0);
    t83 = t83_tmp * 8.0;
    // 'CoefPolySys:87' t84 = t14.*t25.*9.0;
    t84_tmp = t14 * t25;
    t84 = t84_tmp * 9.0;
    // 'CoefPolySys:88' t85 = t16.*t23.*9.0;
    t85_tmp = t16 * t23;
    t85 = t85_tmp * 9.0;
    // 'CoefPolySys:89' t86 = t3.^2.*8.0;
    t86_tmp = std::pow(t3, 2.0);
    t86 = t86_tmp * 8.0;
    // 'CoefPolySys:90' t87 = t14.*t28.*9.0;
    t87 = t14 * t28 * 9.0;
    // 'CoefPolySys:91' t88 = t19.*t23.*9.0;
    t88_tmp = t19 * t23;
    t88 = t88_tmp * 9.0;
    // 'CoefPolySys:92' t89 = t16.*t28.*9.0;
    t89 = t16 * t28 * 9.0;
    // 'CoefPolySys:93' t90 = t19.*t25.*9.0;
    t90 = t19 * t25 * 9.0;
    // 'CoefPolySys:94' t91 = t4.^2.*8.0;
    t91_tmp = std::pow(t4, 2.0);
    t91 = t91_tmp * 8.0;
    // 'CoefPolySys:95' t92 = t2.^3.*4.0e+1;
    // 'CoefPolySys:96' t93 = t3.^3.*4.0e+1;
    // 'CoefPolySys:97' t94 = t4.^3.*4.0e+1;
    // 'CoefPolySys:98' t95 = n01.*n11.*t3.*t4.*-2.0;
    // 'CoefPolySys:99' t96 = n02.*n12.*t2.*t4.*-2.0;
    // 'CoefPolySys:100' t97 = n03.*n13.*t2.*t3.*-2.0;
    // 'CoefPolySys:101' t98 = n01.*n11.*t2.*t3.*8.0;
    // 'CoefPolySys:102' t99 = n01.*n11.*t2.*t4.*8.0;
    // 'CoefPolySys:103' t100 = n02.*n12.*t2.*t3.*8.0;
    // 'CoefPolySys:104' t107 = n02.*n12.*t3.*t4.*8.0;
    // 'CoefPolySys:105' t108 = n03.*n13.*t2.*t4.*8.0;
    // 'CoefPolySys:106' t109 = n03.*n13.*t3.*t4.*8.0;
    // 'CoefPolySys:107' t110 = t2.*t3.*t4.*2.4e+1;
    // 'CoefPolySys:108' t111 = t2+t3+t4;
    t111 = (t2 + t3) + t4;
    // 'CoefPolySys:109' t112 = t2.*t16.*t23.*3.6e+1;
    // 'CoefPolySys:110' t113 = t2.*t19.*t23.*3.6e+1;
    // 'CoefPolySys:111' t114 = t3.*t14.*t25.*3.6e+1;
    // 'CoefPolySys:112' t115 = t3.*t19.*t25.*3.6e+1;
    // 'CoefPolySys:113' t116 = t4.*t14.*t28.*3.6e+1;
    // 'CoefPolySys:114' t117 = t4.*t16.*t28.*3.6e+1;
    // 'CoefPolySys:115' t118 = t2.*t14.*t25.*3.6e+1;
    // 'CoefPolySys:116' t119 = t2.*t14.*t28.*3.6e+1;
    // 'CoefPolySys:117' t120 = t3.*t16.*t23.*3.6e+1;
    // 'CoefPolySys:118' t121 = t3.*t16.*t28.*3.6e+1;
    // 'CoefPolySys:119' t122 = t4.*t19.*t23.*3.6e+1;
    // 'CoefPolySys:120' t123 = t4.*t19.*t25.*3.6e+1;
    // 'CoefPolySys:121' t124 = t14+t16+t19;
    // 'CoefPolySys:122' t125 = t23+t25+t28;
    // 'CoefPolySys:123' t126 = n01.*n12.*t02.*t2.*t11.*8.0;
    // 'CoefPolySys:124' t127 = n02.*n11.*t01.*t3.*t12.*8.0;
    // 'CoefPolySys:125' t128 = n01.*n13.*t2.*t03.*t11.*8.0;
    // 'CoefPolySys:126' t133 = n03.*n11.*t01.*t4.*t13.*8.0;
    // 'CoefPolySys:127' t135 = n02.*n13.*t03.*t3.*t12.*8.0;
    // 'CoefPolySys:128' t137 = n03.*n12.*t02.*t4.*t13.*8.0;
    // 'CoefPolySys:129' t138 = n02.*n11.*t01.*t2.*t12.*8.0;
    // 'CoefPolySys:130' t139 = n01.*n12.*t02.*t3.*t11.*8.0;
    // 'CoefPolySys:131' t140 = n03.*n11.*t01.*t2.*t13.*8.0;
    // 'CoefPolySys:132' t144 = n01.*n13.*t03.*t4.*t11.*8.0;
    // 'CoefPolySys:133' t148 = n03.*n12.*t02.*t3.*t13.*8.0;
    // 'CoefPolySys:134' t149 = n02.*n13.*t03.*t4.*t12.*8.0;
    // 'CoefPolySys:135' t162 = t2.*t16.*t28.*3.6e+1;
    // 'CoefPolySys:136' t163 = t2.*t19.*t25.*3.6e+1;
    // 'CoefPolySys:137' t164 = t3.*t19.*t23.*3.6e+1;
    // 'CoefPolySys:138' t165 = t3.*t14.*t28.*3.6e+1;
    // 'CoefPolySys:139' t166 = t4.*t14.*t25.*3.6e+1;
    // 'CoefPolySys:140' t167 = t4.*t16.*t23.*3.6e+1;
    // 'CoefPolySys:141' t168 = t2.*t3.^2.*4.8e+1;
    // 'CoefPolySys:142' t169 = t2.^2.*t3.*4.8e+1;
    // 'CoefPolySys:143' t170 = t2.*t4.^2.*4.8e+1;
    // 'CoefPolySys:144' t171 = t2.^2.*t4.*4.8e+1;
    // 'CoefPolySys:145' t172 = t3.*t4.^2.*4.8e+1;
    // 'CoefPolySys:146' t173 = t3.^2.*t4.*4.8e+1;
    // 'CoefPolySys:147' t65 = -t32;
    // 'CoefPolySys:148' t66 = -t33;
    // 'CoefPolySys:149' t67 = -t34;
    // 'CoefPolySys:150' t68 = -t35;
    // 'CoefPolySys:151' t69 = -t36;
    // 'CoefPolySys:152' t70 = -t37;
    // 'CoefPolySys:153' t71 = -t38;
    // 'CoefPolySys:154' t72 = -t39;
    // 'CoefPolySys:155' t73 = -t40;
    // 'CoefPolySys:156' t74 = -t41;
    // 'CoefPolySys:157' t75 = -t42;
    // 'CoefPolySys:158' t76 = -t43;
    // 'CoefPolySys:159' t77 = -t56;
    // 'CoefPolySys:160' t78 = -t57;
    // 'CoefPolySys:161' t79 = -t58;
    // 'CoefPolySys:162' t80 = n01.*n11.*t58;
    // 'CoefPolySys:163' t81 = n02.*n12.*t57;
    // 'CoefPolySys:164' t82 = n03.*n13.*t56;
    // 'CoefPolySys:165' t101 = n12.*t12.*t34.*9.0;
    // 'CoefPolySys:166' t102 = n13.*t13.*t32.*9.0;
    // 'CoefPolySys:167' t103 = n11.*t11.*t36.*9.0;
    // 'CoefPolySys:168' t104 = n13.*t13.*t33.*9.0;
    // 'CoefPolySys:169' t105 = n11.*t11.*t37.*9.0;
    // 'CoefPolySys:170' t106 = n12.*t12.*t35.*9.0;
    // 'CoefPolySys:171' t129 = n01.*t01.*t53.*9.0;
    // 'CoefPolySys:172' t130 = n02.*t02.*t51.*9.0;
    // 'CoefPolySys:173' t131 = n01.*t01.*t55.*9.0;
    // 'CoefPolySys:174' t132 = n03.*t03.*t50.*9.0;
    // 'CoefPolySys:175' t134 = n02.*t02.*t54.*9.0;
    // 'CoefPolySys:176' t136 = n03.*t03.*t52.*9.0;
    // 'CoefPolySys:177' t141 = n12.*t12.*t45.*9.0;
    // 'CoefPolySys:178' t142 = n11.*t11.*t47.*9.0;
    // 'CoefPolySys:179' t143 = n13.*t13.*t44.*9.0;
    // 'CoefPolySys:180' t145 = n11.*t11.*t49.*9.0;
    // 'CoefPolySys:181' t146 = n13.*t13.*t46.*9.0;
    // 'CoefPolySys:182' t147 = n12.*t12.*t48.*9.0;
    // 'CoefPolySys:183' t150 = n01.*n11.*t86;
    // 'CoefPolySys:184' t151 = n02.*n12.*t83;
    // 'CoefPolySys:185' t152 = n01.*n11.*t89;
    // 'CoefPolySys:186' t153 = n01.*n11.*t90;
    // 'CoefPolySys:187' t154 = n01.*n11.*t91;
    // 'CoefPolySys:188' t155 = n03.*n13.*t83;
    // 'CoefPolySys:189' t156 = n02.*n12.*t87;
    // 'CoefPolySys:190' t157 = n02.*n12.*t88;
    // 'CoefPolySys:191' t158 = n02.*n12.*t91;
    // 'CoefPolySys:192' t159 = n03.*n13.*t84;
    // 'CoefPolySys:193' t160 = n03.*n13.*t85;
    // 'CoefPolySys:194' t161 = n03.*n13.*t86;
    // 'CoefPolySys:195' t174 = -t126;
    // 'CoefPolySys:196' t175 = -t127;
    // 'CoefPolySys:197' t176 = -t128;
    // 'CoefPolySys:198' t181 = -t133;
    // 'CoefPolySys:199' t183 = -t135;
    // 'CoefPolySys:200' t185 = -t137;
    // 'CoefPolySys:201' t186 = -t138;
    // 'CoefPolySys:202' t187 = -t139;
    // 'CoefPolySys:203' t188 = -t140;
    // 'CoefPolySys:204' t192 = -t144;
    // 'CoefPolySys:205' t196 = -t148;
    // 'CoefPolySys:206' t197 = -t149;
    // 'CoefPolySys:207' t202 =
    // t92+t93+t94+t110+t112+t113+t114+t115+t116+t117+t118+t119+t120+t121+t122+t123+t162+t163+t164+t165+t166+t167+t168+t169+t170+t171+t172+t173;
    // 'CoefPolySys:208' t177 = -t129;
    // 'CoefPolySys:209' t178 = -t130;
    // 'CoefPolySys:210' t179 = -t131;
    // 'CoefPolySys:211' t180 = -t132;
    // 'CoefPolySys:212' t182 = -t134;
    // 'CoefPolySys:213' t184 = -t136;
    // 'CoefPolySys:214' t189 = -t141;
    // 'CoefPolySys:215' t190 = -t142;
    // 'CoefPolySys:216' t191 = -t143;
    // 'CoefPolySys:217' t193 = -t145;
    // 'CoefPolySys:218' t194 = -t146;
    // 'CoefPolySys:219' t195 = -t147;
    // 'CoefPolySys:220' t198 = t44+t45+t46+t47+t48+t49+t65+t66+t67+t68+t69+t70;
    // 'CoefPolySys:221' t199 = t50+t51+t52+t53+t54+t55+t71+t72+t73+t74+t75+t76;
    // 'CoefPolySys:222' t200 = t77+t78+t79+t83+t84+t85+t86+t87+t88+t89+t90+t91;
    // 'CoefPolySys:223' t201 = 1.0./t200;
    t201_tmp = t2 * t3;
    b_t201_tmp = t2 * t4;
    c_t201_tmp = t3 * t4;
    t201 =
        1.0 /
        (((((((((((-(t201_tmp * 2.0) + -(b_t201_tmp * 2.0)) + -(c_t201_tmp * 2.0)) + t83) + t84) +
               t85) +
              t86) +
             t87) +
            t88) +
           t89) +
          t90) +
         t91);
    // 'CoefPolySys:224' t204 =
    // t59+t60+t61+t62+t63+t64+t95+t96+t97+t98+t99+t100+t101+t102+t103+t104+t105+t106+t107+t108+t109+t150+t151+t152+t153+t154+t155+t156+t157+t158+t159+t160+t161+t174+t175+t176+t177+t178+t179+t180+t181+t182+t183+t184+t185+t186+t187+t188+t189+t190+t191+t192+t193+t194+t195+t196+t197;
    // 'CoefPolySys:225' t203 = t201.*t202.*6.0;
    t203_tmp = t2 * t14;
    b_t203_tmp = t3 * t16;
    c_t203_tmp = t4 * t19;
    d_t203_tmp = t2 * t16;
    e_t203_tmp = t2 * t19;
    f_t203_tmp = t3 * t19;
    g_t203_tmp = t3 * t14;
    h_t203_tmp = t4 * t14;
    i_t203_tmp = t4 * t16;
    t203 = t201 *
           (((((((((((((((((((((((((((std::pow(t2, 3.0) * 40.0 + std::pow(t3, 3.0) * 40.0) +
                                     std::pow(t4, 3.0) * 40.0) +
                                    t201_tmp * t4 * 24.0) +
                                   d_t203_tmp * t23 * 36.0) +
                                  e_t203_tmp * t23 * 36.0) +
                                 g_t203_tmp * t25 * 36.0) +
                                f_t203_tmp * t25 * 36.0) +
                               h_t203_tmp * t28 * 36.0) +
                              i_t203_tmp * t28 * 36.0) +
                             t203_tmp * t25 * 36.0) +
                            t203_tmp * t28 * 36.0) +
                           b_t203_tmp * t23 * 36.0) +
                          b_t203_tmp * t28 * 36.0) +
                         c_t203_tmp * t23 * 36.0) +
                        c_t203_tmp * t25 * 36.0) +
                       d_t203_tmp * t28 * 36.0) +
                      e_t203_tmp * t25 * 36.0) +
                     f_t203_tmp * t23 * 36.0) +
                    g_t203_tmp * t28 * 36.0) +
                   h_t203_tmp * t25 * 36.0) +
                  i_t203_tmp * t23 * 36.0) +
                 t2 * t86_tmp * 48.0) +
                t83_tmp * t3 * 48.0) +
               t2 * t91_tmp * 48.0) +
              t83_tmp * t4 * 48.0) +
             t3 * t91_tmp * 48.0) +
            t86_tmp * t4 * 48.0) *
           6.0;
    // 'CoefPolySys:226' t205 = kappa0.*kappa1.*t201.*t204.*6.0;
    d = in3[0] * in7[0];
    d1 = d * t2;
    d2 = in3[1] * in7[1];
    d3 = d2 * t2;
    d4 = in3[2] * in7[2];
    d5 = in3[0] * in7[1] * in2[1];
    d6 = in7[0] * in3[1] * in2[0];
    d7 = in3[0] * in7[2];
    d8 = in7[0] * in3[2] * in2[0];
    d9 = in3[1] * in7[2];
    d10 = in7[1] * in3[2] * in2[1];
    d11 = d7 * in2[2];
    d12 = in7[1] * in6[1];
    d13 = in7[2] * in6[2];
    d14 = in7[0] * in6[0];
    t205_tmp = d9 * in2[2];
    t205 = kappa0 * kappa1 * t201 * ((((((((((((((((((((((((((((((((((((((((((((((((((((((((d5 * t4 * in6[0] + d11 * t3 * in6[0]) + d6 * t4 * in6[1]) + d9 * t2 * in2[2] * in6[1]) + d8 * t3 * in6[2]) + d10 * t2 * in6[2]) + d * t3 * t4 * -2.0) + d3 * t4 * -2.0) + d4 * t2 * t3 * -2.0) + d1 * t3 * 8.0) + d1 * t4 * 8.0) + d3 * t3 * 8.0) + d12 * t34 * 9.0) + d13 * t32 * 9.0) + d14 * t36 * 9.0) + d13 * t33 * 9.0) + d14 * t37 * 9.0) + d12 * t35 * 9.0) + d2 * t3 * t4 * 8.0) + in3[2] * in7[2] * t2 * t4 * 8.0) + d4 * t3 * t4 * 8.0) + d * t86) + d2 * t83) + d * t89) + d * t90) + d * t91) + d4 * t83) + d2 * t87) + d2 * t88) + d2 * t91) + d4 * t84) + d4 * t85) + d4 * t86) + -(d5 * t2 * in6[0] * 8.0)) + -(d6 * t3 * in6[1] * 8.0)) + -(d7 * t2 * in2[2] * in6[0] * 8.0)) + -(t32_tmp * t53 * 9.0)) + -(t33_tmp * t51 * 9.0)) + -(t32_tmp * t55 * 9.0)) + -(t37_tmp * t50 * 9.0)) + -(d8 * t4 * in6[2] * 8.0)) + -(t33_tmp * t54 * 9.0)) + -(t205_tmp * t3 * in6[1] * 8.0)) + -(t37_tmp * t52 * 9.0)) + -(d10 * t4 * in6[2] * 8.0)) + -(d6 * t2 * in6[1] * 8.0)) + -(d5 * t3 * in6[0] * 8.0)) + -(d8 * t2 * in6[2] * 8.0)) + -(d12 * t45 * 9.0)) + -(d14 * t47 * 9.0)) + -(d13 * t44 * 9.0)) + -(d11 * t4 * in6[0] * 8.0)) + -(d14 * t49 * 9.0)) + -(d13 * t46 * 9.0)) + -(d12 * t48 * 9.0)) + -(d10 * t3 * in6[2] * 8.0)) + -(t205_tmp * t4 * in6[1] * 8.0)) * 6.0;
    // 'CoefPolySys:227' CoefPS =
    // [-t205,kappa0.*t125.*t201.*(t32+t33+t34+t35+t36+t37-t44-t45-t46-t47-t48-t49).*-1.08e+2,kappa1.*t124.*t201.*(t38+t39+t40+t41+t42+t43-t50-t51-t52-t53-t54-t55).*2.16e+2,t203,kappa1.^2.*t201.*(t9.*t83+t10.*t83+t8.*t86+t10.*t84+t10.*t85+t9.*t87+t10.*t86+t8.*t89+t9.*t88+t8.*t90+t8.*t91+t9.*t91-n11.*t01.*t39.*1.6e+1-n12.*t02.*t38.*1.6e+1-n11.*t01.*t41.*1.6e+1+n11.*t01.*t42.*2.0+n12.*t02.*t40.*2.0+n13.*t03.*t38.*2.0+n11.*t01.*t43.*2.0+n12.*t02.*t41.*2.0+n13.*t03.*t39.*2.0-n13.*t03.*t40.*1.6e+1-n12.*t02.*t43.*1.6e+1-n13.*t03.*t42.*1.6e+1-n12.*t02.*t51.*2.0-n13.*t03.*t50.*2.0-n13.*t03.*t52.*2.0-t2.*t3.*t10.*2.0-t2.*t4.*t9.*2.0-t3.*t4.*t8.*2.0+t8.*t14.*t25.*8.0+t9.*t16.*t23.*8.0+t8.*t14.*t28.*8.0+t10.*t19.*t23.*8.0+t9.*t16.*t28.*8.0+t10.*t19.*t25.*8.0-n11.*n13.*t11.*t13.*t16.*1.8e+1-n12.*n13.*t12.*t13.*t14.*1.8e+1-n11.*n12.*t11.*t12.*t19.*1.8e+1).*1.8e+1,kappa1.*t111.*t201.*(t38+t39+t40+t41+t42+t43-t50-t51-t52-t53-t54-t55).*-1.08e+2,t201.*(t16.*t26.*7.2e+1+t14.*t29.*7.2e+1+t14.*t31.*7.2e+1+t19.*t26.*7.2e+1+t16.*t31.*7.2e+1+t19.*t29.*7.2e+1+t2.^2.*t23.*4.0e+1+t3.^2.*t23.*1.12e+2+t2.^2.*t25.*1.12e+2+t4.^2.*t23.*1.12e+2+t3.^2.*t25.*4.0e+1+t4.^2.*t25.*1.12e+2+t2.^2.*t28.*1.12e+2+t3.^2.*t28.*1.12e+2+t4.^2.*t28.*4.0e+1-t2.*t3.*t23.*6.4e+1-t2.*t4.*t23.*6.4e+1-t2.*t3.*t25.*6.4e+1-t3.*t4.*t23.*6.4e+1-t2.*t4.*t25.*6.4e+1-t3.*t4.*t25.*6.4e+1-t2.*t3.*t28.*6.4e+1-t2.*t4.*t28.*6.4e+1-t3.*t4.*t28.*6.4e+1+t14.*t25.*t28.*1.44e+2+t16.*t23.*t28.*1.44e+2+t19.*t23.*t25.*1.44e+2+kappa1.*p01.*t01.*t39.*1.2e+2+kappa1.*p02.*t02.*t38.*1.2e+2+kappa1.*p01.*t01.*t41.*1.2e+2-kappa1.*p01.*t01.*t42.*6.0e+1-kappa1.*p02.*t02.*t40.*6.0e+1-kappa1.*p03.*t03.*t38.*6.0e+1-kappa1.*p01.*t01.*t43.*6.0e+1-kappa1.*p02.*t02.*t41.*6.0e+1-kappa1.*p03.*t03.*t39.*6.0e+1+kappa1.*p03.*t03.*t40.*1.2e+2+kappa1.*p02.*t02.*t43.*1.2e+2+kappa1.*p03.*t03.*t42.*1.2e+2-kappa1.*p11.*t01.*t39.*1.2e+2-kappa1.*p12.*t02.*t38.*1.2e+2-kappa1.*p11.*t01.*t41.*1.2e+2+kappa1.*p11.*t01.*t42.*6.0e+1+kappa1.*p12.*t02.*t40.*6.0e+1+kappa1.*p13.*t03.*t38.*6.0e+1+kappa1.*p01.*t01.*t53.*6.0e+1+kappa1.*p02.*t02.*t51.*6.0e+1+kappa1.*p11.*t01.*t43.*6.0e+1+kappa1.*p12.*t02.*t41.*6.0e+1+kappa1.*p13.*t03.*t39.*6.0e+1+kappa1.*p03.*t03.*t50.*6.0e+1-kappa1.*p13.*t03.*t40.*1.2e+2+kappa1.*p01.*t01.*t55.*6.0e+1-kappa1.*p12.*t02.*t43.*1.2e+2+kappa1.*p02.*t02.*t54.*6.0e+1+kappa1.*p03.*t03.*t52.*6.0e+1-kappa1.*p13.*t03.*t42.*1.2e+2-kappa1.*p11.*t01.*t53.*6.0e+1-kappa1.*p12.*t02.*t51.*6.0e+1-kappa1.*p13.*t03.*t50.*6.0e+1-kappa1.*p11.*t01.*t55.*6.0e+1-kappa1.*p12.*t02.*t54.*6.0e+1-kappa1.*p13.*t03.*t52.*6.0e+1-kappa1.*n11.*p01.*t3.^2.*1.6e+2-kappa1.*n11.*p01.*t4.^2.*1.6e+2-kappa1.*n12.*p02.*t2.^2.*1.6e+2-kappa1.*n12.*p02.*t4.^2.*1.6e+2-kappa1.*n13.*p03.*t2.^2.*1.6e+2-kappa1.*n13.*p03.*t3.^2.*1.6e+2+kappa1.*n11.*p11.*t3.^2.*1.6e+2+kappa1.*n11.*p11.*t4.^2.*1.6e+2+kappa1.*n12.*p12.*t2.^2.*1.6e+2+kappa1.*n12.*p12.*t4.^2.*1.6e+2+kappa1.*n13.*p13.*t2.^2.*1.6e+2+kappa1.*n13.*p13.*t3.^2.*1.6e+2-kappa1.*n11.*p01.*t2.*t3.*4.0e+1-kappa1.*n11.*p01.*t2.*t4.*4.0e+1+kappa1.*n11.*p01.*t3.*t4.*4.0e+1-kappa1.*n12.*p02.*t2.*t3.*4.0e+1+kappa1.*n12.*p02.*t2.*t4.*4.0e+1-kappa1.*n12.*p02.*t3.*t4.*4.0e+1+kappa1.*n13.*p03.*t2.*t3.*4.0e+1-kappa1.*n13.*p03.*t2.*t4.*4.0e+1-kappa1.*n13.*p03.*t3.*t4.*4.0e+1+kappa1.*n11.*p11.*t2.*t3.*4.0e+1+kappa1.*n11.*p11.*t2.*t4.*4.0e+1-kappa1.*n11.*p11.*t3.*t4.*4.0e+1+kappa1.*n12.*p12.*t2.*t3.*4.0e+1-kappa1.*n12.*p12.*t2.*t4.*4.0e+1+kappa1.*n12.*p12.*t3.*t4.*4.0e+1-kappa1.*n13.*p13.*t2.*t3.*4.0e+1+kappa1.*n13.*p13.*t2.*t4.*4.0e+1+kappa1.*n13.*p13.*t3.*t4.*4.0e+1-kappa1.*n11.*p01.*t14.*t25.*1.2e+2-kappa1.*n12.*p02.*t16.*t23.*1.2e+2-kappa1.*n11.*p01.*t14.*t28.*1.2e+2-kappa1.*n13.*p03.*t14.*t25.*1.8e+2-kappa1.*n13.*p03.*t16.*t23.*1.8e+2-kappa1.*n11.*p01.*t16.*t28.*1.8e+2-kappa1.*n11.*p01.*t19.*t25.*1.8e+2-kappa1.*n12.*p02.*t14.*t28.*1.8e+2-kappa1.*n12.*p02.*t19.*t23.*1.8e+2-kappa1.*n12.*p02.*t16.*t28.*1.2e+2-kappa1.*n13.*p03.*t19.*t23.*1.2e+2-kappa1.*n13.*p03.*t19.*t25.*1.2e+2+kappa1.*n11.*p11.*t14.*t25.*1.2e+2+kappa1.*n12.*p12.*t16.*t23.*1.2e+2+kappa1.*n11.*p11.*t14.*t28.*1.2e+2+kappa1.*n13.*p13.*t14.*t25.*1.8e+2+kappa1.*n13.*p13.*t16.*t23.*1.8e+2+kappa1.*n11.*p11.*t16.*t28.*1.8e+2+kappa1.*n11.*p11.*t19.*t25.*1.8e+2+kappa1.*n12.*p12.*t14.*t28.*1.8e+2+kappa1.*n12.*p12.*t19.*t23.*1.8e+2+kappa1.*n12.*p12.*t16.*t28.*1.2e+2+kappa1.*n13.*p13.*t19.*t23.*1.2e+2+kappa1.*n13.*p13.*t19.*t25.*1.2e+2+kappa1.*n11.*p02.*t01.*t2.*t12.*1.6e+2+kappa1.*n12.*p01.*t02.*t2.*t11.*4.0e+1+kappa1.*n11.*p02.*t01.*t3.*t12.*4.0e+1+kappa1.*n12.*p01.*t02.*t3.*t11.*1.6e+2-kappa1.*n11.*p02.*t01.*t4.*t12.*2.0e+1+kappa1.*n11.*p03.*t01.*t2.*t13.*1.6e+2-kappa1.*n12.*p01.*t02.*t4.*t11.*2.0e+1+kappa1.*n13.*p01.*t2.*t03.*t11.*4.0e+1-kappa1.*n11.*p03.*t01.*t3.*t13.*2.0e+1-kappa1.*n13.*p01.*t03.*t3.*t11.*2.0e+1+kappa1.*n11.*p03.*t01.*t4.*t13.*4.0e+1-kappa1.*n12.*p03.*t02.*t2.*t13.*2.0e+1+kappa1.*n13.*p01.*t03.*t4.*t11.*1.6e+2-kappa1.*n13.*p02.*t2.*t03.*t12.*2.0e+1+kappa1.*n12.*p03.*t02.*t3.*t13.*1.6e+2+kappa1.*n13.*p02.*t03.*t3.*t12.*4.0e+1+kappa1.*n12.*p03.*t02.*t4.*t13.*4.0e+1+kappa1.*n13.*p02.*t03.*t4.*t12.*1.6e+2-kappa1.*n11.*p12.*t01.*t2.*t12.*1.6e+2-kappa1.*n12.*p11.*t02.*t2.*t11.*4.0e+1-kappa1.*n11.*p12.*t01.*t3.*t12.*4.0e+1-kappa1.*n12.*p11.*t02.*t3.*t11.*1.6e+2+kappa1.*n11.*p12.*t01.*t4.*t12.*2.0e+1-kappa1.*n11.*p13.*t01.*t2.*t13.*1.6e+2+kappa1.*n12.*p11.*t02.*t4.*t11.*2.0e+1-kappa1.*n13.*p11.*t2.*t03.*t11.*4.0e+1+kappa1.*n11.*p13.*t01.*t3.*t13.*2.0e+1+kappa1.*n13.*p11.*t03.*t3.*t11.*2.0e+1-kappa1.*n11.*p13.*t01.*t4.*t13.*4.0e+1+kappa1.*n12.*p13.*t02.*t2.*t13.*2.0e+1-kappa1.*n13.*p11.*t03.*t4.*t11.*1.6e+2+kappa1.*n13.*p12.*t2.*t03.*t12.*2.0e+1-kappa1.*n12.*p13.*t02.*t3.*t13.*1.6e+2-kappa1.*n13.*p12.*t03.*t3.*t12.*4.0e+1-kappa1.*n12.*p13.*t02.*t4.*t13.*4.0e+1-kappa1.*n13.*p12.*t03.*t4.*t12.*1.6e+2+kappa1.*n11.*p03.*t11.*t13.*t16.*1.8e+2+kappa1.*n12.*p03.*t12.*t13.*t14.*1.8e+2+kappa1.*n13.*p01.*t11.*t13.*t16.*1.8e+2+kappa1.*n13.*p02.*t12.*t13.*t14.*1.8e+2+kappa1.*n11.*p02.*t11.*t12.*t19.*1.8e+2+kappa1.*n12.*p01.*t11.*t12.*t19.*1.8e+2-kappa1.*n11.*p13.*t11.*t13.*t16.*1.8e+2-kappa1.*n12.*p13.*t12.*t13.*t14.*1.8e+2-kappa1.*n13.*p11.*t11.*t13.*t16.*1.8e+2-kappa1.*n13.*p12.*t12.*t13.*t14.*1.8e+2-kappa1.*n11.*p12.*t11.*t12.*t19.*1.8e+2-kappa1.*n12.*p11.*t11.*t12.*t19.*1.8e+2).*6.0,t201.*(p01.*t2.^2.*t11.*8.0e+1+p01.*t3.^2.*t11.*2.0e+2+p01.*t4.^2.*t11.*2.0e+2+p02.*t2.^2.*t12.*2.0e+2+p02.*t3.^2.*t12.*8.0e+1+p02.*t4.^2.*t12.*2.0e+2+p03.*t2.^2.*t13.*2.0e+2+p03.*t3.^2.*t13.*2.0e+2+p03.*t4.^2.*t13.*8.0e+1-p11.*t2.^2.*t11.*8.0e+1-p11.*t3.^2.*t11.*2.0e+2-p11.*t4.^2.*t11.*2.0e+2-p12.*t2.^2.*t12.*2.0e+2-p12.*t3.^2.*t12.*8.0e+1-p12.*t4.^2.*t12.*2.0e+2-p13.*t2.^2.*t13.*2.0e+2-p13.*t3.^2.*t13.*2.0e+2-p13.*t4.^2.*t13.*8.0e+1+p01.*t16.*t24.*1.8e+2+p02.*t14.*t27.*1.8e+2+p01.*t19.*t24.*1.8e+2+p03.*t14.*t30.*1.8e+2+p02.*t19.*t27.*1.8e+2+p03.*t16.*t30.*1.8e+2-p11.*t16.*t24.*1.8e+2-p12.*t14.*t27.*1.8e+2-p11.*t19.*t24.*1.8e+2-p13.*t14.*t30.*1.8e+2-p12.*t19.*t27.*1.8e+2-p13.*t16.*t30.*1.8e+2-p01.*t2.*t3.*t11.*8.0e+1-p01.*t2.*t4.*t11.*8.0e+1+p01.*t3.*t4.*t11.*4.0e+1-p02.*t2.*t3.*t12.*8.0e+1+p02.*t2.*t4.*t12.*4.0e+1-p02.*t3.*t4.*t12.*8.0e+1+p03.*t2.*t3.*t13.*4.0e+1-p03.*t2.*t4.*t13.*8.0e+1-p03.*t3.*t4.*t13.*8.0e+1+p11.*t2.*t3.*t11.*8.0e+1+p11.*t2.*t4.*t11.*8.0e+1+p01.*t01.*t2.*t25.*6.0e+1-p02.*t02.*t2.*t23.*1.2e+2-p11.*t3.*t4.*t11.*4.0e+1+p12.*t2.*t3.*t12.*8.0e+1-p01.*t01.*t3.*t25.*1.2e+2+p02.*t02.*t3.*t23.*6.0e+1-p12.*t2.*t4.*t12.*4.0e+1-p01.*t01.*t4.*t25.*1.2e+2-p02.*t02.*t4.*t23.*1.2e+2-p03.*t2.*t03.*t23.*1.2e+2+p12.*t3.*t4.*t12.*8.0e+1-p13.*t2.*t3.*t13.*4.0e+1+p01.*t01.*t2.*t28.*6.0e+1-p03.*t03.*t3.*t23.*1.2e+2+p13.*t2.*t4.*t13.*8.0e+1-p01.*t01.*t3.*t28.*1.2e+2-p03.*t2.*t03.*t25.*1.2e+2+p03.*t03.*t4.*t23.*6.0e+1+p13.*t3.*t4.*t13.*8.0e+1-p01.*t01.*t4.*t28.*1.2e+2-p02.*t02.*t2.*t28.*1.2e+2-p03.*t03.*t3.*t25.*1.2e+2+p02.*t02.*t3.*t28.*6.0e+1+p03.*t03.*t4.*t25.*6.0e+1-p02.*t02.*t4.*t28.*1.2e+2-p11.*t01.*t2.*t25.*6.0e+1+p12.*t02.*t2.*t23.*1.2e+2+p11.*t01.*t3.*t25.*1.2e+2-p12.*t02.*t3.*t23.*6.0e+1+p11.*t01.*t4.*t25.*1.2e+2+p12.*t02.*t4.*t23.*1.2e+2+p13.*t2.*t03.*t23.*1.2e+2-p11.*t01.*t2.*t28.*6.0e+1+p13.*t03.*t3.*t23.*1.2e+2+p11.*t01.*t3.*t28.*1.2e+2+p13.*t2.*t03.*t25.*1.2e+2-p13.*t03.*t4.*t23.*6.0e+1+p11.*t01.*t4.*t28.*1.2e+2+p12.*t02.*t2.*t28.*1.2e+2+p13.*t03.*t3.*t25.*1.2e+2-p12.*t02.*t3.*t28.*6.0e+1-p13.*t03.*t4.*t25.*6.0e+1+p12.*t02.*t4.*t28.*1.2e+2+p03.*t13.*t14.*t25.*1.8e+2+p03.*t13.*t16.*t23.*1.8e+2+p01.*t11.*t16.*t28.*1.8e+2+p01.*t11.*t19.*t25.*1.8e+2+p02.*t12.*t14.*t28.*1.8e+2+p02.*t12.*t19.*t23.*1.8e+2-p13.*t13.*t14.*t25.*1.8e+2-p13.*t13.*t16.*t23.*1.8e+2-p11.*t11.*t16.*t28.*1.8e+2-p11.*t11.*t19.*t25.*1.8e+2-p12.*t12.*t14.*t28.*1.8e+2-p12.*t12.*t19.*t23.*1.8e+2).*6.0,t205,kappa1.*t124.*t201.*(t38+t39+t40+t41+t42+t43-t50-t51-t52-t53-t54-t55).*-1.08e+2,kappa0.*t125.*t201.*(t32+t33+t34+t35+t36+t37-t44-t45-t46-t47-t48-t49).*2.16e+2,-t203,kappa0.^2.*t201.*(t6.*t83+t7.*t83+t5.*t86+t7.*t84+t7.*t85+t6.*t87+t7.*t86+t5.*t89+t6.*t88+t5.*t90+t5.*t91+t6.*t91-n01.*t11.*t33.*1.6e+1-n02.*t12.*t32.*1.6e+1-n01.*t11.*t35.*1.6e+1+n01.*t11.*t36.*2.0+n02.*t12.*t34.*2.0+n03.*t13.*t32.*2.0+n01.*t11.*t37.*2.0+n02.*t12.*t35.*2.0+n03.*t13.*t33.*2.0-n03.*t13.*t34.*1.6e+1-n02.*t12.*t37.*1.6e+1-n03.*t13.*t36.*1.6e+1-n02.*t12.*t45.*2.0-n03.*t13.*t44.*2.0-n03.*t13.*t46.*2.0-t2.*t3.*t7.*2.0-t2.*t4.*t6.*2.0-t3.*t4.*t5.*2.0+t5.*t16.*t23.*8.0+t6.*t14.*t25.*8.0+t5.*t19.*t23.*8.0+t7.*t14.*t28.*8.0+t6.*t19.*t25.*8.0+t7.*t16.*t28.*8.0-n01.*n03.*t01.*t03.*t25.*1.8e+1-n02.*n03.*t02.*t03.*t23.*1.8e+1-n01.*n02.*t01.*t02.*t28.*1.8e+1).*-1.8e+1,kappa0.*t111.*t201.*(t32+t33+t34+t35+t36+t37-t44-t45-t46-t47-t48-t49).*-1.08e+2,t201.*(t17.*t25.*7.2e+1+t20.*t23.*7.2e+1+t17.*t28.*7.2e+1+t22.*t23.*7.2e+1+t22.*t25.*7.2e+1+t20.*t28.*7.2e+1+t2.^2.*t14.*4.0e+1+t3.^2.*t14.*1.12e+2+t2.^2.*t16.*1.12e+2+t4.^2.*t14.*1.12e+2+t3.^2.*t16.*4.0e+1+t4.^2.*t16.*1.12e+2+t2.^2.*t19.*1.12e+2+t3.^2.*t19.*1.12e+2+t4.^2.*t19.*4.0e+1-t2.*t3.*t14.*6.4e+1-t2.*t4.*t14.*6.4e+1-t2.*t3.*t16.*6.4e+1-t3.*t4.*t14.*6.4e+1-t2.*t4.*t16.*6.4e+1-t3.*t4.*t16.*6.4e+1-t2.*t3.*t19.*6.4e+1-t2.*t4.*t19.*6.4e+1-t3.*t4.*t19.*6.4e+1+t14.*t16.*t28.*1.44e+2+t14.*t19.*t25.*1.44e+2+t16.*t19.*t23.*1.44e+2-kappa0.*p01.*t11.*t33.*1.2e+2-kappa0.*p02.*t12.*t32.*1.2e+2-kappa0.*p01.*t11.*t35.*1.2e+2+kappa0.*p01.*t11.*t36.*6.0e+1+kappa0.*p02.*t12.*t34.*6.0e+1+kappa0.*p03.*t13.*t32.*6.0e+1+kappa0.*p01.*t11.*t37.*6.0e+1+kappa0.*p02.*t12.*t35.*6.0e+1+kappa0.*p03.*t13.*t33.*6.0e+1-kappa0.*p03.*t13.*t34.*1.2e+2-kappa0.*p02.*t12.*t37.*1.2e+2-kappa0.*p03.*t13.*t36.*1.2e+2+kappa0.*p11.*t11.*t33.*1.2e+2+kappa0.*p12.*t12.*t32.*1.2e+2+kappa0.*p11.*t11.*t35.*1.2e+2-kappa0.*p11.*t11.*t36.*6.0e+1-kappa0.*p12.*t12.*t34.*6.0e+1-kappa0.*p13.*t13.*t32.*6.0e+1-kappa0.*p01.*t11.*t47.*6.0e+1-kappa0.*p02.*t12.*t45.*6.0e+1-kappa0.*p11.*t11.*t37.*6.0e+1-kappa0.*p12.*t12.*t35.*6.0e+1-kappa0.*p13.*t13.*t33.*6.0e+1-kappa0.*p03.*t13.*t44.*6.0e+1+kappa0.*p13.*t13.*t34.*1.2e+2-kappa0.*p01.*t11.*t49.*6.0e+1+kappa0.*p12.*t12.*t37.*1.2e+2-kappa0.*p02.*t12.*t48.*6.0e+1-kappa0.*p03.*t13.*t46.*6.0e+1+kappa0.*p13.*t13.*t36.*1.2e+2+kappa0.*p11.*t11.*t47.*6.0e+1+kappa0.*p12.*t12.*t45.*6.0e+1+kappa0.*p13.*t13.*t44.*6.0e+1+kappa0.*p11.*t11.*t49.*6.0e+1+kappa0.*p12.*t12.*t48.*6.0e+1+kappa0.*p13.*t13.*t46.*6.0e+1+kappa0.*n01.*p01.*t3.^2.*1.6e+2+kappa0.*n01.*p01.*t4.^2.*1.6e+2+kappa0.*n02.*p02.*t2.^2.*1.6e+2+kappa0.*n02.*p02.*t4.^2.*1.6e+2+kappa0.*n03.*p03.*t2.^2.*1.6e+2+kappa0.*n03.*p03.*t3.^2.*1.6e+2-kappa0.*n01.*p11.*t3.^2.*1.6e+2-kappa0.*n01.*p11.*t4.^2.*1.6e+2-kappa0.*n02.*p12.*t2.^2.*1.6e+2-kappa0.*n02.*p12.*t4.^2.*1.6e+2-kappa0.*n03.*p13.*t2.^2.*1.6e+2-kappa0.*n03.*p13.*t3.^2.*1.6e+2+kappa0.*n01.*p01.*t2.*t3.*4.0e+1+kappa0.*n01.*p01.*t2.*t4.*4.0e+1-kappa0.*n01.*p01.*t3.*t4.*4.0e+1+kappa0.*n02.*p02.*t2.*t3.*4.0e+1-kappa0.*n02.*p02.*t2.*t4.*4.0e+1+kappa0.*n02.*p02.*t3.*t4.*4.0e+1-kappa0.*n03.*p03.*t2.*t3.*4.0e+1+kappa0.*n03.*p03.*t2.*t4.*4.0e+1+kappa0.*n03.*p03.*t3.*t4.*4.0e+1-kappa0.*n01.*p11.*t2.*t3.*4.0e+1-kappa0.*n01.*p11.*t2.*t4.*4.0e+1+kappa0.*n01.*p11.*t3.*t4.*4.0e+1-kappa0.*n02.*p12.*t2.*t3.*4.0e+1+kappa0.*n02.*p12.*t2.*t4.*4.0e+1-kappa0.*n02.*p12.*t3.*t4.*4.0e+1+kappa0.*n03.*p13.*t2.*t3.*4.0e+1-kappa0.*n03.*p13.*t2.*t4.*4.0e+1-kappa0.*n03.*p13.*t3.*t4.*4.0e+1+kappa0.*n01.*p01.*t16.*t23.*1.2e+2+kappa0.*n02.*p02.*t14.*t25.*1.2e+2+kappa0.*n01.*p01.*t19.*t23.*1.2e+2+kappa0.*n03.*p03.*t14.*t25.*1.8e+2+kappa0.*n03.*p03.*t16.*t23.*1.8e+2+kappa0.*n01.*p01.*t16.*t28.*1.8e+2+kappa0.*n01.*p01.*t19.*t25.*1.8e+2+kappa0.*n02.*p02.*t14.*t28.*1.8e+2+kappa0.*n02.*p02.*t19.*t23.*1.8e+2+kappa0.*n02.*p02.*t19.*t25.*1.2e+2+kappa0.*n03.*p03.*t14.*t28.*1.2e+2+kappa0.*n03.*p03.*t16.*t28.*1.2e+2-kappa0.*n01.*p11.*t16.*t23.*1.2e+2-kappa0.*n02.*p12.*t14.*t25.*1.2e+2-kappa0.*n01.*p11.*t19.*t23.*1.2e+2-kappa0.*n03.*p13.*t14.*t25.*1.8e+2-kappa0.*n03.*p13.*t16.*t23.*1.8e+2-kappa0.*n01.*p11.*t16.*t28.*1.8e+2-kappa0.*n01.*p11.*t19.*t25.*1.8e+2-kappa0.*n02.*p12.*t14.*t28.*1.8e+2-kappa0.*n02.*p12.*t19.*t23.*1.8e+2-kappa0.*n02.*p12.*t19.*t25.*1.2e+2-kappa0.*n03.*p13.*t14.*t28.*1.2e+2-kappa0.*n03.*p13.*t16.*t28.*1.2e+2-kappa0.*n01.*p02.*t02.*t2.*t11.*1.6e+2-kappa0.*n02.*p01.*t01.*t2.*t12.*4.0e+1-kappa0.*n01.*p02.*t02.*t3.*t11.*4.0e+1-kappa0.*n02.*p01.*t01.*t3.*t12.*1.6e+2+kappa0.*n01.*p02.*t02.*t4.*t11.*2.0e+1-kappa0.*n01.*p03.*t2.*t03.*t11.*1.6e+2+kappa0.*n02.*p01.*t01.*t4.*t12.*2.0e+1-kappa0.*n03.*p01.*t01.*t2.*t13.*4.0e+1+kappa0.*n01.*p03.*t03.*t3.*t11.*2.0e+1+kappa0.*n03.*p01.*t01.*t3.*t13.*2.0e+1-kappa0.*n01.*p03.*t03.*t4.*t11.*4.0e+1+kappa0.*n02.*p03.*t2.*t03.*t12.*2.0e+1-kappa0.*n03.*p01.*t01.*t4.*t13.*1.6e+2+kappa0.*n03.*p02.*t02.*t2.*t13.*2.0e+1-kappa0.*n02.*p03.*t03.*t3.*t12.*1.6e+2-kappa0.*n03.*p02.*t02.*t3.*t13.*4.0e+1-kappa0.*n02.*p03.*t03.*t4.*t12.*4.0e+1-kappa0.*n03.*p02.*t02.*t4.*t13.*1.6e+2+kappa0.*n01.*p12.*t02.*t2.*t11.*1.6e+2+kappa0.*n02.*p11.*t01.*t2.*t12.*4.0e+1+kappa0.*n01.*p12.*t02.*t3.*t11.*4.0e+1+kappa0.*n02.*p11.*t01.*t3.*t12.*1.6e+2-kappa0.*n01.*p12.*t02.*t4.*t11.*2.0e+1+kappa0.*n01.*p13.*t2.*t03.*t11.*1.6e+2-kappa0.*n02.*p11.*t01.*t4.*t12.*2.0e+1+kappa0.*n03.*p11.*t01.*t2.*t13.*4.0e+1-kappa0.*n01.*p13.*t03.*t3.*t11.*2.0e+1-kappa0.*n03.*p11.*t01.*t3.*t13.*2.0e+1+kappa0.*n01.*p13.*t03.*t4.*t11.*4.0e+1-kappa0.*n02.*p13.*t2.*t03.*t12.*2.0e+1+kappa0.*n03.*p11.*t01.*t4.*t13.*1.6e+2-kappa0.*n03.*p12.*t02.*t2.*t13.*2.0e+1-kappa0.*n01.*p03.*t01.*t03.*t25.*1.8e+2-kappa0.*n02.*p03.*t02.*t03.*t23.*1.8e+2+kappa0.*n02.*p13.*t03.*t3.*t12.*1.6e+2-kappa0.*n03.*p01.*t01.*t03.*t25.*1.8e+2-kappa0.*n03.*p02.*t02.*t03.*t23.*1.8e+2+kappa0.*n03.*p12.*t02.*t3.*t13.*4.0e+1-kappa0.*n01.*p02.*t01.*t02.*t28.*1.8e+2-kappa0.*n02.*p01.*t01.*t02.*t28.*1.8e+2+kappa0.*n02.*p13.*t03.*t4.*t12.*4.0e+1+kappa0.*n03.*p12.*t02.*t4.*t13.*1.6e+2+kappa0.*n01.*p13.*t01.*t03.*t25.*1.8e+2+kappa0.*n02.*p13.*t02.*t03.*t23.*1.8e+2+kappa0.*n03.*p11.*t01.*t03.*t25.*1.8e+2+kappa0.*n03.*p12.*t02.*t03.*t23.*1.8e+2+kappa0.*n01.*p12.*t01.*t02.*t28.*1.8e+2+kappa0.*n02.*p11.*t01.*t02.*t28.*1.8e+2).*-6.0,t201.*(p01.*t01.*t2.^2.*8.0e+1+p01.*t01.*t3.^2.*2.0e+2+p01.*t01.*t4.^2.*2.0e+2+p02.*t02.*t2.^2.*2.0e+2+p02.*t02.*t3.^2.*8.0e+1+p02.*t02.*t4.^2.*2.0e+2+p03.*t2.^2.*t03.*2.0e+2+p03.*t03.*t3.^2.*2.0e+2+p03.*t03.*t4.^2.*8.0e+1-p11.*t01.*t2.^2.*8.0e+1-p11.*t01.*t3.^2.*2.0e+2-p11.*t01.*t4.^2.*2.0e+2-p12.*t02.*t2.^2.*2.0e+2-p12.*t02.*t3.^2.*8.0e+1-p12.*t02.*t4.^2.*2.0e+2-p13.*t2.^2.*t03.*2.0e+2-p13.*t03.*t3.^2.*2.0e+2-p13.*t03.*t4.^2.*8.0e+1+p01.*t15.*t25.*1.8e+2+p02.*t18.*t23.*1.8e+2+p01.*t15.*t28.*1.8e+2+p03.*t21.*t23.*1.8e+2+p02.*t18.*t28.*1.8e+2+p03.*t21.*t25.*1.8e+2-p11.*t15.*t25.*1.8e+2-p12.*t18.*t23.*1.8e+2-p11.*t15.*t28.*1.8e+2-p13.*t21.*t23.*1.8e+2-p12.*t18.*t28.*1.8e+2-p13.*t21.*t25.*1.8e+2-p01.*t01.*t2.*t3.*8.0e+1-p01.*t01.*t2.*t4.*8.0e+1+p01.*t01.*t3.*t4.*4.0e+1-p02.*t02.*t2.*t3.*8.0e+1+p02.*t02.*t2.*t4.*4.0e+1-p02.*t02.*t3.*t4.*8.0e+1+p03.*t2.*t03.*t3.*4.0e+1-p03.*t2.*t03.*t4.*8.0e+1-p03.*t03.*t3.*t4.*8.0e+1+p11.*t01.*t2.*t3.*8.0e+1+p11.*t01.*t2.*t4.*8.0e+1-p11.*t01.*t3.*t4.*4.0e+1+p12.*t02.*t2.*t3.*8.0e+1-p12.*t02.*t2.*t4.*4.0e+1+p12.*t02.*t3.*t4.*8.0e+1-p13.*t2.*t03.*t3.*4.0e+1+p13.*t2.*t03.*t4.*8.0e+1+p13.*t03.*t3.*t4.*8.0e+1+p01.*t2.*t11.*t16.*6.0e+1-p02.*t2.*t12.*t14.*1.2e+2-p01.*t3.*t11.*t16.*1.2e+2+p02.*t3.*t12.*t14.*6.0e+1-p01.*t4.*t11.*t16.*1.2e+2-p02.*t4.*t12.*t14.*1.2e+2-p03.*t2.*t13.*t14.*1.2e+2+p01.*t2.*t11.*t19.*6.0e+1-p03.*t3.*t13.*t14.*1.2e+2-p01.*t3.*t11.*t19.*1.2e+2-p03.*t2.*t13.*t16.*1.2e+2+p03.*t4.*t13.*t14.*6.0e+1-p01.*t4.*t11.*t19.*1.2e+2-p02.*t2.*t12.*t19.*1.2e+2-p03.*t3.*t13.*t16.*1.2e+2+p02.*t3.*t12.*t19.*6.0e+1+p03.*t4.*t13.*t16.*6.0e+1-p02.*t4.*t12.*t19.*1.2e+2-p11.*t2.*t11.*t16.*6.0e+1+p12.*t2.*t12.*t14.*1.2e+2+p11.*t3.*t11.*t16.*1.2e+2-p12.*t3.*t12.*t14.*6.0e+1+p11.*t4.*t11.*t16.*1.2e+2+p12.*t4.*t12.*t14.*1.2e+2+p13.*t2.*t13.*t14.*1.2e+2-p11.*t2.*t11.*t19.*6.0e+1+p13.*t3.*t13.*t14.*1.2e+2+p11.*t3.*t11.*t19.*1.2e+2+p13.*t2.*t13.*t16.*1.2e+2-p13.*t4.*t13.*t14.*6.0e+1+p03.*t03.*t14.*t25.*1.8e+2+p03.*t03.*t16.*t23.*1.8e+2+p11.*t4.*t11.*t19.*1.2e+2+p12.*t2.*t12.*t19.*1.2e+2+p13.*t3.*t13.*t16.*1.2e+2+p01.*t01.*t16.*t28.*1.8e+2+p01.*t01.*t19.*t25.*1.8e+2+p02.*t02.*t14.*t28.*1.8e+2+p02.*t02.*t19.*t23.*1.8e+2-p12.*t3.*t12.*t19.*6.0e+1-p13.*t4.*t13.*t16.*6.0e+1+p12.*t4.*t12.*t19.*1.2e+2-p13.*t03.*t14.*t25.*1.8e+2-p13.*t03.*t16.*t23.*1.8e+2-p11.*t01.*t16.*t28.*1.8e+2-p11.*t01.*t19.*t25.*1.8e+2-p12.*t02.*t14.*t28.*1.8e+2-p12.*t02.*t19.*t23.*1.8e+2).*-6.0];
    CoefPS[0] = -t205;
    CoefPS_tmp_tmp =
        ((((((((((t32 + t33) + t34) + t35) + t36) + t37) - t44) - t45) - t46) - t47) - t48) - t49;
    CoefPS_tmp = kappa0 * ((t23 + t25) + t28) * t201 * CoefPS_tmp_tmp;
    CoefPS[1] = CoefPS_tmp * -108.0;
    b_CoefPS_tmp =
        ((((((((((t38 + t39) + t40) + t41) + t42) + t43) - t50) - t51) - t52) - t53) - t54) - t55;
    c_CoefPS_tmp = kappa1 * ((t14 + t16) + t19) * t201 * b_CoefPS_tmp;
    CoefPS[2] = c_CoefPS_tmp * 216.0;
    CoefPS[3] = t203;
    d_CoefPS_tmp = t8 * t14;
    e_CoefPS_tmp = t9 * t16;
    f_CoefPS_tmp = t10 * t19;
    CoefPS[4] =
        std::pow(kappa1, 2.0) * t201 *
        ((((((((((((((((((((((((((((((((((((((t9 * t83 + t10 * t83) + t8 * t86) + t10 * t84) +
                                           t10 * t85) +
                                          t9 * t87) +
                                         t10 * t86) +
                                        t8 * t89) +
                                       t9 * t88) +
                                      t8 * t90) +
                                     t8 * t91) +
                                    t9 * t91) -
                                   t50_tmp * t39 * 16.0) -
                                  t52_tmp * t38 * 16.0) -
                                 t50_tmp * t41 * 16.0) +
                                t50_tmp * t42 * 2.0) +
                               t52_tmp * t40 * 2.0) +
                              t54_tmp * t38 * 2.0) +
                             t50_tmp * t43 * 2.0) +
                            t52_tmp * t41 * 2.0) +
                           t54_tmp * t39 * 2.0) -
                          t54_tmp * t40 * 16.0) -
                         t52_tmp * t43 * 16.0) -
                        t54_tmp * t42 * 16.0) -
                       t52_tmp * t51 * 2.0) -
                      t54_tmp * t50 * 2.0) -
                     t54_tmp * t52 * 2.0) -
                    t201_tmp * t10 * 2.0) -
                   b_t201_tmp * t9 * 2.0) -
                  c_t201_tmp * t8 * 2.0) +
                 d_CoefPS_tmp * t25 * 8.0) +
                e_CoefPS_tmp * t23 * 8.0) +
               d_CoefPS_tmp * t28 * 8.0) +
              f_CoefPS_tmp * t23 * 8.0) +
             e_CoefPS_tmp * t28 * 8.0) +
            f_CoefPS_tmp * t25 * 8.0) -
           in7[0] * in7[2] * in6[0] * in6[2] * t16 * 18.0) -
          in7[1] * in7[2] * in6[1] * in6[2] * t14 * 18.0) -
         in7[0] * in7[1] * in6[0] * in6[1] * t19 * 18.0) *
        18.0;
    CoefPS[5] = kappa1 * t111 * t201 * b_CoefPS_tmp * -108.0;
    d15 = kappa1 * in1[0] * in2[0];
    d16 = kappa1 * in1[1] * in2[1];
    d17 = kappa1 * in1[2] * in2[2];
    d18 = kappa1 * in5[0] * in2[0];
    d19 = kappa1 * in5[1] * in2[1];
    d20 = kappa1 * in5[2] * in2[2];
    d21 = kappa1 * in7[0];
    d22 = d21 * in1[0];
    d23 = kappa1 * in7[1];
    d24 = d23 * in1[1];
    d25 = kappa1 * in7[2];
    d26 = d25 * in1[2];
    d27 = d21 * in5[0];
    d28 = d23 * in5[1];
    d29 = d25 * in5[2];
    d30 = d26 * t2;
    d31 = d27 * t2;
    d32 = d28 * t2;
    d33 = d29 * t2;
    d34 = d22 * t14;
    d35 = d24 * t16;
    d36 = d26 * t19;
    d37 = d27 * t14;
    d38 = d28 * t16;
    d39 = d29 * t19;
    d40 = d21 * in1[1];
    d41 = d40 * in2[0];
    d42 = d23 * in1[0];
    d43 = d42 * in2[1];
    d44 = d21 * in1[2];
    d45 = d44 * in2[0];
    d46 = d25 * in1[0];
    d47 = d23 * in1[2];
    CoefPS_tmp_tmp_tmp = d25 * in1[1];
    g_CoefPS_tmp = CoefPS_tmp_tmp_tmp * in2[2];
    b_CoefPS_tmp_tmp = d21 * in5[1];
    h_CoefPS_tmp = b_CoefPS_tmp_tmp * in2[0];
    c_CoefPS_tmp_tmp = d23 * in5[0];
    i_CoefPS_tmp = c_CoefPS_tmp_tmp * in2[1];
    d_CoefPS_tmp_tmp = d21 * in5[2];
    j_CoefPS_tmp = d_CoefPS_tmp_tmp * in2[0];
    k_CoefPS_tmp = d25 * in5[0];
    l_CoefPS_tmp = k_CoefPS_tmp * in2[2];
    e_CoefPS_tmp_tmp = d23 * in5[2];
    m_CoefPS_tmp = e_CoefPS_tmp_tmp * in2[1];
    n_CoefPS_tmp = d25 * in5[1];
    o_CoefPS_tmp = n_CoefPS_tmp * in2[2];
    p_CoefPS_tmp = d22 * t2;
    q_CoefPS_tmp = d24 * t2;
    r_CoefPS_tmp = kappa1 * in7[1] * in1[2] * in2[1];
    CoefPS[6] = t201 * ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t16 * t26 * 72.0 + t14 * t29 * 72.0) + t14 * t31 * 72.0) + t19 * t26 * 72.0) + t16 * t31 * 72.0) + t19 * t29 * 72.0) + t83_tmp * t23 * 40.0) + t86_tmp * t23 * 112.0) + t83_tmp * t25 * 112.0) + t91_tmp * t23 * 112.0) + t86_tmp * t25 * 40.0) + t91_tmp * t25 * 112.0) + t83_tmp * t28 * 112.0) + t86_tmp * t28 * 112.0) + t91_tmp * t28 * 40.0) - t201_tmp * t23 * 64.0) - b_t201_tmp * t23 * 64.0) - t201_tmp * t25 * 64.0) - c_t201_tmp * t23 * 64.0) - b_t201_tmp * t25 * 64.0) - c_t201_tmp * t25 * 64.0) - t201_tmp * t28 * 64.0) - b_t201_tmp * t28 * 64.0) - c_t201_tmp * t28 * 64.0) + t84_tmp * t28 * 144.0) + t85_tmp * t28 * 144.0) + t88_tmp * t25 * 144.0) + d15 * t39 * 120.0) + d16 * t38 * 120.0) + d15 * t41 * 120.0) - d15 * t42 * 60.0) - d16 * t40 * 60.0) - d17 * t38 * 60.0) - d15 * t43 * 60.0) - d16 * t41 * 60.0) - d17 * t39 * 60.0) + d17 * t40 * 120.0) + d16 * t43 * 120.0) + d17 * t42 * 120.0) - d18 * t39 * 120.0) - d19 * t38 * 120.0) - d18 * t41 * 120.0) + d18 * t42 * 60.0) + d19 * t40 * 60.0) + d20 * t38 * 60.0) + d15 * t53 * 60.0) + d16 * t51 * 60.0) + d18 * t43 * 60.0) + d19 * t41 * 60.0) + d20 * t39 * 60.0) + d17 * t50 * 60.0) - d20 * t40 * 120.0) + d15 * t55 * 60.0) - d19 * t43 * 120.0) + d16 * t54 * 60.0) + d17 * t52 * 60.0) - d20 * t42 * 120.0) - d18 * t53 * 60.0) - d19 * t51 * 60.0) - d20 * t50 * 60.0) - d18 * t55 * 60.0) - d19 * t54 * 60.0) - d20 * t52 * 60.0) - d22 * t86_tmp * 160.0) - d22 * t91_tmp * 160.0) - d24 * t83_tmp * 160.0) - d24 * t91_tmp * 160.0) - d26 * t83_tmp * 160.0) - d26 * t86_tmp * 160.0) + d27 * t86_tmp * 160.0) + d27 * t91_tmp * 160.0) + d28 * t83_tmp * 160.0) + d28 * t91_tmp * 160.0) + d29 * t83_tmp * 160.0) + d29 * t86_tmp * 160.0) - p_CoefPS_tmp * t3 * 40.0) - p_CoefPS_tmp * t4 * 40.0) + d22 * t3 * t4 * 40.0) - q_CoefPS_tmp * t3 * 40.0) + q_CoefPS_tmp * t4 * 40.0) - d24 * t3 * t4 * 40.0) + d30 * t3 * 40.0) - d30 * t4 * 40.0) - d26 * t3 * t4 * 40.0) + d31 * t3 * 40.0) + d31 * t4 * 40.0) - d27 * t3 * t4 * 40.0) + d32 * t3 * 40.0) - d32 * t4 * 40.0) + d28 * t3 * t4 * 40.0) - d33 * t3 * 40.0) + d33 * t4 * 40.0) + d29 * t3 * t4 * 40.0) - d34 * t25 * 120.0) - d35 * t23 * 120.0) - d34 * t28 * 120.0) - d26 * t14 * t25 * 180.0) - d26 * t16 * t23 * 180.0) - d22 * t16 * t28 * 180.0) - d22 * t19 * t25 * 180.0) - d24 * t14 * t28 * 180.0) - d24 * t19 * t23 * 180.0) - d35 * t28 * 120.0) - d36 * t23 * 120.0) - d36 * t25 * 120.0) + d37 * t25 * 120.0) + d38 * t23 * 120.0) + d37 * t28 * 120.0) + d29 * t14 * t25 * 180.0) + d29 * t16 * t23 * 180.0) + d27 * t16 * t28 * 180.0) + d27 * t19 * t25 * 180.0) + d28 * t14 * t28 * 180.0) + d28 * t19 * t23 * 180.0) + d38 * t28 * 120.0) + d39 * t23 * 120.0) + d39 * t25 * 120.0) + d41 * t2 * in6[1] * 160.0) + d43 * t2 * in6[0] * 40.0) + d41 * t3 * in6[1] * 40.0) + d43 * t3 * in6[0] * 160.0) - d41 * t4 * in6[1] * 20.0) + d45 * t2 * in6[2] * 160.0) - d43 * t4 * in6[0] * 20.0) + d46 * t2 * in2[2] * in6[0] * 40.0) - d45 * t3 * in6[2] * 20.0) - d46 * in2[2] * t3 * in6[0] * 20.0) + d45 * t4 * in6[2] * 40.0) - d47 * in2[1] * t2 * in6[2] * 20.0) + d25 * in1[0] * in2[2] * t4 * in6[0] * 160.0) - CoefPS_tmp_tmp_tmp * t2 * in2[2] * in6[1] * 20.0) + r_CoefPS_tmp * t3 * in6[2] * 160.0) + g_CoefPS_tmp * t3 * in6[1] * 40.0) + r_CoefPS_tmp * t4 * in6[2] * 40.0) + g_CoefPS_tmp * t4 * in6[1] * 160.0) - h_CoefPS_tmp * t2 * in6[1] * 160.0) - i_CoefPS_tmp * t2 * in6[0] * 40.0) - h_CoefPS_tmp * t3 * in6[1] * 40.0) - i_CoefPS_tmp * t3 * in6[0] * 160.0) + h_CoefPS_tmp * t4 * in6[1] * 20.0) - j_CoefPS_tmp * t2 * in6[2] * 160.0) + i_CoefPS_tmp * t4 * in6[0] * 20.0) - k_CoefPS_tmp * t2 * in2[2] * in6[0] * 40.0) + j_CoefPS_tmp * t3 * in6[2] * 20.0) + l_CoefPS_tmp * t3 * in6[0] * 20.0) - j_CoefPS_tmp * t4 * in6[2] * 40.0) + m_CoefPS_tmp * t2 * in6[2] * 20.0) - l_CoefPS_tmp * t4 * in6[0] * 160.0) + n_CoefPS_tmp * t2 * in2[2] * in6[1] * 20.0) - m_CoefPS_tmp * t3 * in6[2] * 160.0) - o_CoefPS_tmp * t3 * in6[1] * 40.0) - m_CoefPS_tmp * t4 * in6[2] * 40.0) - o_CoefPS_tmp * t4 * in6[1] * 160.0) + d44 * in6[0] * in6[2] * t16 * 180.0) + d47 * in6[1] * in6[2] * t14 * 180.0) + d46 * in6[0] * in6[2] * t16 * 180.0) + CoefPS_tmp_tmp_tmp * in6[1] * in6[2] * t14 * 180.0) + d40 * in6[0] * in6[1] * t19 * 180.0) + d42 * in6[0] * in6[1] * t19 * 180.0) - d_CoefPS_tmp_tmp * in6[0] * in6[2] * t16 * 180.0) - e_CoefPS_tmp_tmp * in6[1] * in6[2] * t14 * 180.0) - k_CoefPS_tmp * in6[0] * in6[2] * t16 * 180.0) - n_CoefPS_tmp * in6[1] * in6[2] * t14 * 180.0) - b_CoefPS_tmp_tmp * in6[0] * in6[1] * t19 * 180.0) - c_CoefPS_tmp_tmp * in6[0] * in6[1] * t19 * 180.0) * 6.0;
    d48 = in1[2] * t83_tmp;
    d49 = in1[0] * t2;
    d50 = in1[1] * t2;
    d51 = in1[2] * t2;
    d52 = in5[0] * t2;
    d53 = in1[0] * in2[0];
    d54 = in1[1] * in2[1];
    d55 = in5[1] * t2;
    d56 = d53 * t2;
    d57 = d53 * t4;
    d58 = d54 * t2;
    d59 = d54 * t3;
    d60 = d54 * t4;
    d61 = in5[2] * t83_tmp;
    d62 = d53 * t3;
    d63 = d51 * in2[2];
    d64 = in1[0] * t3;
    d65 = in1[1] * t3;
    d66 = in1[2] * t3;
    d67 = in5[0] * t3;
    d68 = in5[1] * t3;
    d69 = in5[2] * t2;
    d70 = in1[2] * in2[2];
    d71 = d70 * t3;
    s_CoefPS_tmp = in5[0] * in2[0];
    t_CoefPS_tmp = in5[1] * in2[1];
    u_CoefPS_tmp = s_CoefPS_tmp * t2;
    v_CoefPS_tmp = s_CoefPS_tmp * t3;
    w_CoefPS_tmp = d69 * in2[2];
    x_CoefPS_tmp = in5[2] * in2[2];
    y_CoefPS_tmp = s_CoefPS_tmp * t4;
    ab_CoefPS_tmp = t_CoefPS_tmp * t2;
    bb_CoefPS_tmp = x_CoefPS_tmp * t3;
    cb_CoefPS_tmp = t_CoefPS_tmp * t3;
    db_CoefPS_tmp = x_CoefPS_tmp * t4;
    eb_CoefPS_tmp = t_CoefPS_tmp * t4;
    fb_CoefPS_tmp = in1[2] * in6[2];
    gb_CoefPS_tmp = in1[0] * in6[0];
    hb_CoefPS_tmp = in1[1] * in6[1];
    ib_CoefPS_tmp = in5[2] * in6[2];
    jb_CoefPS_tmp = in5[0] * in6[0];
    kb_CoefPS_tmp = in5[1] * in6[1];
    lb_CoefPS_tmp = in5[2] * t3;
    mb_CoefPS_tmp = d70 * t4;
    CoefPS[7] = t201 * (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((in1[0] * t83_tmp * in6[0] * 80.0 + in1[0] * t86_tmp * in6[0] * 200.0) + in1[0] * t91_tmp * in6[0] * 200.0) + in1[1] * t83_tmp * in6[1] * 200.0) + in1[1] * t86_tmp * in6[1] * 80.0) + in1[1] * t91_tmp * in6[1] * 200.0) + d48 * in6[2] * 200.0) + in1[2] * t86_tmp * in6[2] * 200.0) + in1[2] * t91_tmp * in6[2] * 80.0) - in5[0] * t83_tmp * in6[0] * 80.0) - in5[0] * t86_tmp * in6[0] * 200.0) - in5[0] * t91_tmp * in6[0] * 200.0) - in5[1] * t83_tmp * in6[1] * 200.0) - in5[1] * t86_tmp * in6[1] * 80.0) - in5[1] * t91_tmp * in6[1] * 200.0) - d61 * in6[2] * 200.0) - in5[2] * t86_tmp * in6[2] * 200.0) - in5[2] * t91_tmp * in6[2] * 80.0) + in1[0] * t16 * t24 * 180.0) + in1[1] * t14 * t27 * 180.0) + in1[0] * t19 * t24 * 180.0) + in1[2] * t14 * t30 * 180.0) + in1[1] * t19 * t27 * 180.0) + in1[2] * t16 * t30 * 180.0) - in5[0] * t16 * t24 * 180.0) - in5[1] * t14 * t27 * 180.0) - in5[0] * t19 * t24 * 180.0) - in5[2] * t14 * t30 * 180.0) - in5[1] * t19 * t27 * 180.0) - in5[2] * t16 * t30 * 180.0) - d49 * t3 * in6[0] * 80.0) - d49 * t4 * in6[0] * 80.0) + d64 * t4 * in6[0] * 40.0) - d50 * t3 * in6[1] * 80.0) + d50 * t4 * in6[1] * 40.0) - d65 * t4 * in6[1] * 80.0) + d51 * t3 * in6[2] * 40.0) - d51 * t4 * in6[2] * 80.0) - d66 * t4 * in6[2] * 80.0) + d52 * t3 * in6[0] * 80.0) + d52 * t4 * in6[0] * 80.0) + d56 * t25 * 60.0) - d58 * t23 * 120.0) - d67 * t4 * in6[0] * 40.0) + d55 * t3 * in6[1] * 80.0) - d62 * t25 * 120.0) + d59 * t23 * 60.0) - d55 * t4 * in6[1] * 40.0) - d57 * t25 * 120.0) - d60 * t23 * 120.0) - d63 * t23 * 120.0) + d68 * t4 * in6[1] * 80.0) - d69 * t3 * in6[2] * 40.0) + d56 * t28 * 60.0) - d71 * t23 * 120.0) + d69 * t4 * in6[2] * 80.0) - d62 * t28 * 120.0) - d63 * t25 * 120.0) + mb_CoefPS_tmp * t23 * 60.0) + lb_CoefPS_tmp * t4 * in6[2] * 80.0) - d57 * t28 * 120.0) - d58 * t28 * 120.0) - d71 * t25 * 120.0) + d59 * t28 * 60.0) + mb_CoefPS_tmp * t25 * 60.0) - d60 * t28 * 120.0) - u_CoefPS_tmp * t25 * 60.0) + ab_CoefPS_tmp * t23 * 120.0) + v_CoefPS_tmp * t25 * 120.0) - cb_CoefPS_tmp * t23 * 60.0) + y_CoefPS_tmp * t25 * 120.0) + eb_CoefPS_tmp * t23 * 120.0) + w_CoefPS_tmp * t23 * 120.0) - u_CoefPS_tmp * t28 * 60.0) + bb_CoefPS_tmp * t23 * 120.0) + v_CoefPS_tmp * t28 * 120.0) + w_CoefPS_tmp * t25 * 120.0) - db_CoefPS_tmp * t23 * 60.0) + y_CoefPS_tmp * t28 * 120.0) + ab_CoefPS_tmp * t28 * 120.0) + bb_CoefPS_tmp * t25 * 120.0) - cb_CoefPS_tmp * t28 * 60.0) - db_CoefPS_tmp * t25 * 60.0) + eb_CoefPS_tmp * t28 * 120.0) + fb_CoefPS_tmp * t14 * t25 * 180.0) + fb_CoefPS_tmp * t16 * t23 * 180.0) + gb_CoefPS_tmp * t16 * t28 * 180.0) + gb_CoefPS_tmp * t19 * t25 * 180.0) + hb_CoefPS_tmp * t14 * t28 * 180.0) + hb_CoefPS_tmp * t19 * t23 * 180.0) - ib_CoefPS_tmp * t14 * t25 * 180.0) - ib_CoefPS_tmp * t16 * t23 * 180.0) - jb_CoefPS_tmp * t16 * t28 * 180.0) - jb_CoefPS_tmp * t19 * t25 * 180.0) - kb_CoefPS_tmp * t14 * t28 * 180.0) - kb_CoefPS_tmp * t19 * t23 * 180.0) * 6.0;
    CoefPS[8] = t205;
    CoefPS[9] = c_CoefPS_tmp * -108.0;
    CoefPS[10] = CoefPS_tmp * 216.0;
    CoefPS[11] = -t203;
    CoefPS[12] =
        std::pow(kappa0, 2.0) * t201 *
        ((((((((((((((((((((((((((((((((((((((t6 * t83 + t7 * t83) + t5 * t86) + t7 * t84) +
                                           t7 * t85) +
                                          t6 * t87) +
                                         t7 * t86) +
                                        t5 * t89) +
                                       t6 * t88) +
                                      t5 * t90) +
                                     t5 * t91) +
                                    t6 * t91) -
                                   t44_tmp * t33 * 16.0) -
                                  t46_tmp * t32 * 16.0) -
                                 t44_tmp * t35 * 16.0) +
                                t44_tmp * t36 * 2.0) +
                               t46_tmp * t34 * 2.0) +
                              t48_tmp * t32 * 2.0) +
                             t44_tmp * t37 * 2.0) +
                            t46_tmp * t35 * 2.0) +
                           t48_tmp * t33 * 2.0) -
                          t48_tmp * t34 * 16.0) -
                         t46_tmp * t37 * 16.0) -
                        t48_tmp * t36 * 16.0) -
                       t46_tmp * t45 * 2.0) -
                      t48_tmp * t44 * 2.0) -
                     t48_tmp * t46 * 2.0) -
                    t201_tmp * t7 * 2.0) -
                   b_t201_tmp * t6 * 2.0) -
                  c_t201_tmp * t5 * 2.0) +
                 t5 * t16 * t23 * 8.0) +
                t6 * t14 * t25 * 8.0) +
               t5 * t19 * t23 * 8.0) +
              t7 * t14 * t28 * 8.0) +
             t6 * t19 * t25 * 8.0) +
            t7 * t16 * t28 * 8.0) -
           in3[0] * in3[2] * in2[0] * in2[2] * t25 * 18.0) -
          in3[1] * in3[2] * in2[1] * in2[2] * t23 * 18.0) -
         in3[0] * in3[1] * in2[0] * in2[1] * t28 * 18.0) *
        -18.0;
    CoefPS[13] = kappa0 * t111 * t201 * CoefPS_tmp_tmp * -108.0;
    d72 = kappa0 * in1[0] * in6[0];
    d73 = kappa0 * in1[1] * in6[1];
    d74 = kappa0 * in1[2] * in6[2];
    d75 = kappa0 * in5[0] * in6[0];
    d76 = kappa0 * in5[1] * in6[1];
    d77 = kappa0 * in5[2] * in6[2];
    d78 = kappa0 * in3[0];
    d79 = d78 * in1[0];
    d80 = kappa0 * in3[1];
    d81 = d80 * in1[1];
    d82 = kappa0 * in3[2];
    d83 = d82 * in1[2];
    d84 = d78 * in5[0];
    d85 = d80 * in5[1];
    d86 = d82 * in5[2];
    d87 = d83 * t2;
    d88 = d84 * t2;
    d89 = d85 * t2;
    d90 = d86 * t2;
    d91 = d79 * t16;
    d92 = d79 * t19;
    d93 = d81 * t14;
    d94 = d81 * t19;
    d95 = d83 * t14;
    d96 = d83 * t16;
    d97 = d84 * t16;
    d98 = d84 * t19;
    d99 = d85 * t14;
    d100 = d85 * t19;
    d101 = d86 * t14;
    d102 = d86 * t16;
    d103 = d78 * in1[1];
    d104 = d103 * in2[1];
    d105 = d80 * in1[0] * in2[0];
    d106 = d78 * in1[2];
    d107 = d82 * in1[0] * in2[0];
    d108 = d80 * in1[2];
    f_CoefPS_tmp_tmp = d82 * in1[1] * in2[1];
    g_CoefPS_tmp_tmp = d78 * in5[1];
    nb_CoefPS_tmp = g_CoefPS_tmp_tmp * in2[1];
    ob_CoefPS_tmp = d80 * in5[0] * in2[0];
    pb_CoefPS_tmp = d78 * in5[2];
    qb_CoefPS_tmp = d82 * in5[0] * in2[0];
    rb_CoefPS_tmp = pb_CoefPS_tmp * in2[2];
    sb_CoefPS_tmp = d80 * in5[2];
    tb_CoefPS_tmp = d82 * in5[1] * in2[1];
    ub_CoefPS_tmp = sb_CoefPS_tmp * in2[2];
    vb_CoefPS_tmp = d79 * t2;
    wb_CoefPS_tmp = d81 * t2;
    xb_CoefPS_tmp = d106 * in2[2];
    CoefPS[14] = t201 * ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((t17 * t25 * 72.0 + t20 * t23 * 72.0) + t17 * t28 * 72.0) + t22 * t23 * 72.0) + t22 * t25 * 72.0) + t20 * t28 * 72.0) + t83_tmp * t14 * 40.0) + t86_tmp * t14 * 112.0) + t83_tmp * t16 * 112.0) + t91_tmp * t14 * 112.0) + t86_tmp * t16 * 40.0) + t91_tmp * t16 * 112.0) + t83_tmp * t19 * 112.0) + t86_tmp * t19 * 112.0) + t91_tmp * t19 * 40.0) - t201_tmp * t14 * 64.0) - b_t201_tmp * t14 * 64.0) - t201_tmp * t16 * 64.0) - c_t201_tmp * t14 * 64.0) - b_t201_tmp * t16 * 64.0) - c_t201_tmp * t16 * 64.0) - t201_tmp * t19 * 64.0) - b_t201_tmp * t19 * 64.0) - c_t201_tmp * t19 * 64.0) + t14 * t16 * t28 * 144.0) + t14 * t19 * t25 * 144.0) + t16 * t19 * t23 * 144.0) - d72 * t33 * 120.0) - d73 * t32 * 120.0) - d72 * t35 * 120.0) + d72 * t36 * 60.0) + d73 * t34 * 60.0) + d74 * t32 * 60.0) + d72 * t37 * 60.0) + d73 * t35 * 60.0) + d74 * t33 * 60.0) - d74 * t34 * 120.0) - d73 * t37 * 120.0) - d74 * t36 * 120.0) + d75 * t33 * 120.0) + d76 * t32 * 120.0) + d75 * t35 * 120.0) - d75 * t36 * 60.0) - d76 * t34 * 60.0) - d77 * t32 * 60.0) - d72 * t47 * 60.0) - d73 * t45 * 60.0) - d75 * t37 * 60.0) - d76 * t35 * 60.0) - d77 * t33 * 60.0) - d74 * t44 * 60.0) + d77 * t34 * 120.0) - d72 * t49 * 60.0) + d76 * t37 * 120.0) - d73 * t48 * 60.0) - d74 * t46 * 60.0) + d77 * t36 * 120.0) + d75 * t47 * 60.0) + d76 * t45 * 60.0) + d77 * t44 * 60.0) + d75 * t49 * 60.0) + d76 * t48 * 60.0) + d77 * t46 * 60.0) + d79 * t86_tmp * 160.0) + d79 * t91_tmp * 160.0) + d81 * t83_tmp * 160.0) + d81 * t91_tmp * 160.0) + d83 * t83_tmp * 160.0) + d83 * t86_tmp * 160.0) - d84 * t86_tmp * 160.0) - d84 * t91_tmp * 160.0) - d85 * t83_tmp * 160.0) - d85 * t91_tmp * 160.0) - d86 * t83_tmp * 160.0) - d86 * t86_tmp * 160.0) + vb_CoefPS_tmp * t3 * 40.0) + vb_CoefPS_tmp * t4 * 40.0) - d79 * t3 * t4 * 40.0) + wb_CoefPS_tmp * t3 * 40.0) - wb_CoefPS_tmp * t4 * 40.0) + d81 * t3 * t4 * 40.0) - d87 * t3 * 40.0) + d87 * t4 * 40.0) + d83 * t3 * t4 * 40.0) - d88 * t3 * 40.0) - d88 * t4 * 40.0) + d84 * t3 * t4 * 40.0) - d89 * t3 * 40.0) + d89 * t4 * 40.0) - d85 * t3 * t4 * 40.0) + d90 * t3 * 40.0) - d90 * t4 * 40.0) - d86 * t3 * t4 * 40.0) + d91 * t23 * 120.0) + d93 * t25 * 120.0) + d92 * t23 * 120.0) + d95 * t25 * 180.0) + d96 * t23 * 180.0) + d91 * t28 * 180.0) + d92 * t25 * 180.0) + d93 * t28 * 180.0) + d94 * t23 * 180.0) + d94 * t25 * 120.0) + d95 * t28 * 120.0) + d96 * t28 * 120.0) - d97 * t23 * 120.0) - d99 * t25 * 120.0) - d98 * t23 * 120.0) - d101 * t25 * 180.0) - d102 * t23 * 180.0) - d97 * t28 * 180.0) - d98 * t25 * 180.0) - d99 * t28 * 180.0) - d100 * t23 * 180.0) - d100 * t25 * 120.0) - d101 * t28 * 120.0) - d102 * t28 * 120.0) - d104 * t2 * in6[0] * 160.0) - d105 * t2 * in6[1] * 40.0) - d104 * t3 * in6[0] * 40.0) - d105 * t3 * in6[1] * 160.0) + d104 * t4 * in6[0] * 20.0) - d106 * t2 * in2[2] * in6[0] * 160.0) + d105 * t4 * in6[1] * 20.0) - d107 * t2 * in6[2] * 40.0) + xb_CoefPS_tmp * t3 * in6[0] * 20.0) + d107 * t3 * in6[2] * 20.0) - xb_CoefPS_tmp * t4 * in6[0] * 40.0) + d108 * t2 * in2[2] * in6[1] * 20.0) - d107 * t4 * in6[2] * 160.0) + f_CoefPS_tmp_tmp * t2 * in6[2] * 20.0) - kappa0 * in3[1] * in1[2] * in2[2] * t3 * in6[1] * 160.0) - f_CoefPS_tmp_tmp * t3 * in6[2] * 40.0) - d108 * in2[2] * t4 * in6[1] * 40.0) - f_CoefPS_tmp_tmp * t4 * in6[2] * 160.0) + nb_CoefPS_tmp * t2 * in6[0] * 160.0) + ob_CoefPS_tmp * t2 * in6[1] * 40.0) + nb_CoefPS_tmp * t3 * in6[0] * 40.0) + ob_CoefPS_tmp * t3 * in6[1] * 160.0) - nb_CoefPS_tmp * t4 * in6[0] * 20.0) + pb_CoefPS_tmp * t2 * in2[2] * in6[0] * 160.0) - ob_CoefPS_tmp * t4 * in6[1] * 20.0) + qb_CoefPS_tmp * t2 * in6[2] * 40.0) - rb_CoefPS_tmp * t3 * in6[0] * 20.0) - qb_CoefPS_tmp * t3 * in6[2] * 20.0) + rb_CoefPS_tmp * t4 * in6[0] * 40.0) - sb_CoefPS_tmp * t2 * in2[2] * in6[1] * 20.0) + qb_CoefPS_tmp * t4 * in6[2] * 160.0) - tb_CoefPS_tmp * t2 * in6[2] * 20.0) - d106 * in2[0] * in2[2] * t25 * 180.0) - d108 * in2[1] * in2[2] * t23 * 180.0) + ub_CoefPS_tmp * t3 * in6[1] * 160.0) - d107 * in2[2] * t25 * 180.0) - f_CoefPS_tmp_tmp * in2[2] * t23 * 180.0) + tb_CoefPS_tmp * t3 * in6[2] * 40.0) - d103 * in2[0] * in2[1] * t28 * 180.0) - d105 * in2[1] * t28 * 180.0) + ub_CoefPS_tmp * t4 * in6[1] * 40.0) + tb_CoefPS_tmp * t4 * in6[2] * 160.0) + pb_CoefPS_tmp * in2[0] * in2[2] * t25 * 180.0) + sb_CoefPS_tmp * in2[1] * in2[2] * t23 * 180.0) + qb_CoefPS_tmp * in2[2] * t25 * 180.0) + tb_CoefPS_tmp * in2[2] * t23 * 180.0) + g_CoefPS_tmp_tmp * in2[0] * in2[1] * t28 * 180.0) + ob_CoefPS_tmp * in2[1] * t28 * 180.0) * -6.0;
    d109 = in1[0] * t15;
    d110 = in1[1] * t18;
    d111 = in1[2] * t21;
    d112 = in5[0] * t15;
    d113 = in5[1] * t18;
    d114 = in5[2] * t21;
    d115 = d49 * in6[0];
    d116 = d50 * in6[1];
    d117 = d65 * in6[1];
    d118 = in1[0] * t4 * in6[0];
    d119 = in1[1] * t4 * in6[1];
    yb_CoefPS_tmp = in1[2] * t4 * in6[2];
    ac_CoefPS_tmp = d52 * in6[0];
    bc_CoefPS_tmp = d67 * in6[0];
    cc_CoefPS_tmp = d69 * in6[2];
    dc_CoefPS_tmp = in5[0] * t4 * in6[0];
    ec_CoefPS_tmp = d55 * in6[1];
    fc_CoefPS_tmp = lb_CoefPS_tmp * in6[2];
    gc_CoefPS_tmp = d68 * in6[1];
    hc_CoefPS_tmp = in5[2] * t4 * in6[2];
    ic_CoefPS_tmp = in5[1] * t4 * in6[1];
    jc_CoefPS_tmp = d64 * in6[0];
    CoefPS[15] = t201 * (((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((d53 * t83_tmp * 80.0 + d53 * t86_tmp * 200.0) + d53 * t91_tmp * 200.0) + d54 * t83_tmp * 200.0) + d54 * t86_tmp * 80.0) + d54 * t91_tmp * 200.0) + d48 * in2[2] * 200.0) + d70 * t86_tmp * 200.0) + d70 * t91_tmp * 80.0) - s_CoefPS_tmp * t83_tmp * 80.0) - s_CoefPS_tmp * t86_tmp * 200.0) - s_CoefPS_tmp * t91_tmp * 200.0) - t_CoefPS_tmp * t83_tmp * 200.0) - t_CoefPS_tmp * t86_tmp * 80.0) - t_CoefPS_tmp * t91_tmp * 200.0) - d61 * in2[2] * 200.0) - x_CoefPS_tmp * t86_tmp * 200.0) - x_CoefPS_tmp * t91_tmp * 80.0) + d109 * t25 * 180.0) + d110 * t23 * 180.0) + d109 * t28 * 180.0) + d111 * t23 * 180.0) + d110 * t28 * 180.0) + d111 * t25 * 180.0) - d112 * t25 * 180.0) - d113 * t23 * 180.0) - d112 * t28 * 180.0) - d114 * t23 * 180.0) - d113 * t28 * 180.0) - d114 * t25 * 180.0) - d56 * t3 * 80.0) - d56 * t4 * 80.0) + d62 * t4 * 40.0) - d58 * t3 * 80.0) + d58 * t4 * 40.0) - d59 * t4 * 80.0) + d63 * t3 * 40.0) - d63 * t4 * 80.0) - d71 * t4 * 80.0) + u_CoefPS_tmp * t3 * 80.0) + u_CoefPS_tmp * t4 * 80.0) - v_CoefPS_tmp * t4 * 40.0) + ab_CoefPS_tmp * t3 * 80.0) - ab_CoefPS_tmp * t4 * 40.0) + cb_CoefPS_tmp * t4 * 80.0) - w_CoefPS_tmp * t3 * 40.0) + w_CoefPS_tmp * t4 * 80.0) + bb_CoefPS_tmp * t4 * 80.0) + d115 * t16 * 60.0) - d116 * t14 * 120.0) - jc_CoefPS_tmp * t16 * 120.0) + d117 * t14 * 60.0) - d118 * t16 * 120.0) - d119 * t14 * 120.0) - d51 * in6[2] * t14 * 120.0) + d115 * t19 * 60.0) - d66 * in6[2] * t14 * 120.0) - jc_CoefPS_tmp * t19 * 120.0) - in1[2] * t2 * in6[2] * t16 * 120.0) + yb_CoefPS_tmp * t14 * 60.0) - d118 * t19 * 120.0) - d116 * t19 * 120.0) - in1[2] * t3 * in6[2] * t16 * 120.0) + d117 * t19 * 60.0) + yb_CoefPS_tmp * t16 * 60.0) - d119 * t19 * 120.0) - ac_CoefPS_tmp * t16 * 60.0) + ec_CoefPS_tmp * t14 * 120.0) + bc_CoefPS_tmp * t16 * 120.0) - gc_CoefPS_tmp * t14 * 60.0) + dc_CoefPS_tmp * t16 * 120.0) + ic_CoefPS_tmp * t14 * 120.0) + cc_CoefPS_tmp * t14 * 120.0) - ac_CoefPS_tmp * t19 * 60.0) + fc_CoefPS_tmp * t14 * 120.0) + bc_CoefPS_tmp * t19 * 120.0) + cc_CoefPS_tmp * t16 * 120.0) - hc_CoefPS_tmp * t14 * 60.0) + d70 * t14 * t25 * 180.0) + d70 * t16 * t23 * 180.0) + dc_CoefPS_tmp * t19 * 120.0) + ec_CoefPS_tmp * t19 * 120.0) + fc_CoefPS_tmp * t16 * 120.0) + d53 * t16 * t28 * 180.0) + d53 * t19 * t25 * 180.0) + d54 * t14 * t28 * 180.0) + d54 * t19 * t23 * 180.0) - gc_CoefPS_tmp * t19 * 60.0) - hc_CoefPS_tmp * t16 * 60.0) + ic_CoefPS_tmp * t19 * 120.0) - x_CoefPS_tmp * t14 * t25 * 180.0) - x_CoefPS_tmp * t16 * t23 * 180.0) - s_CoefPS_tmp * t16 * t28 * 180.0) - s_CoefPS_tmp * t19 * t25 * 180.0) - t_CoefPS_tmp * t14 * t28 * 180.0) - t_CoefPS_tmp * t19 * t23 * 180.0) * -6.0;
}

} // namespace ocn

//
// File trailer for CoefPolySys.cpp
//
// [EOF]
//
