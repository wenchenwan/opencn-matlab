/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: kinematics.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 10-Jun-2022 11:26:56
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
extern void J_ar(const double in1[6], double in2[4][3], double b_J_ar[6][3]);

extern void J_arP(const double in1[6], const double in2[6], double in3[4][3], double b_J_arP[6][3]);

extern void J_arPP(const double in1[6], const double in2[6], const double in3[6], double in4[4][3],
                   double b_J_arPP[6][3]);

extern void MGD(const double in1[6], double in2[4][3], double b_MGD[6]);

extern void MGI(const double in1[6], double in2[4][3], double b_MGI[6]);

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
