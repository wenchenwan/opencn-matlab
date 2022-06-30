/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: kinematics.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 29-Jun-2022 18:51:04
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
extern void kin_J2P_ar_xyzbc(const double in1[5], const double in2[5], const double in3[5],
                             double in4[4][3], double J2P_ar[5][5]);

extern void kin_J2P_ra_xyzbc(const double in1[5], const double in2[5], const double in3[5],
                             double in4[4][3], double J2P_ra[5][5]);

extern void kin_JP_ar_xyzbc(const double in1[5], const double in2[5], double in3[4][3],
                            double JP_ar[5][5]);

extern void kin_JP_ra_xyzbc(const double in1[5], const double in2[5], double in3[4][3],
                            double JP_ra[5][5]);

extern void kin_J_ar_xyzbc(const double in1[5], double in2[4][3], double J_ar[5][5]);

extern void kin_J_ra_xyzbc(const double in1[5], double in2[4][3], double J_ra[5][5]);

extern void kin_forward_xyzbc(const double in1[5], double in2[4][3], double world[5]);

extern void kin_inverse_xyzbc(const double in1[5], double in2[4][3], double joint[5]);

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
