
/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: kinematics.h
 *
 * MATLAB Coder version            : 5.4
 */

#ifndef KINEMATICS_H
#define KINEMATICS_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

/* Custom Header Code */
#include "functions.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void kin_xyzbc_tt_J2P_jt(const double in1[5], const double in2[5], const double in3[5],
                                double in4[5][3], double J2P_jt[5][5]);

extern void kin_xyzbc_tt_J2P_tj(const double in1[5], const double in2[5], const double in3[5],
                                double in4[5][3], double J2P_tj[5][5]);

extern void kin_xyzbc_tt_JP_jt(const double in1[5], const double in2[5], double in3[5][3],
                               double JP_jt[5][5]);

extern void kin_xyzbc_tt_JP_tj(const double in1[5], const double in2[5], double in3[5][3],
                               double JP_tj[5][5]);

extern void kin_xyzbc_tt_J_jt(const double in1[5], double in2[5][3], double J_jt[5][5]);

extern void kin_xyzbc_tt_J_tj(const double in1[5], double in2[5][3], double J_tj[5][5]);

extern void kin_xyzbc_tt_forward(const double in1[5], double in2[5][3], double piece[5]);

extern void kin_xyzbc_tt_inverse(const double in1[5], double in2[5][3], double joint[5]);

extern void kinematics_initialize(void);

extern void kinematics_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for kinematics.h
 *
 * [EOF]
 */
