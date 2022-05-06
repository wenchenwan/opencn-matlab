/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: J_arPP.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 06-May-2022 16:42:55
 */

#ifndef J_ARPP_H
#define J_ARPP_H

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
extern void J_arPP(double x, double y, double z, double b, double c, double xP, double yP,
                   double zP, double bP, double cP, double xPP, double yPP, double zPP, double bPP,
                   double cPP, double mx, double my, double mz, double tx, double ty, double tz,
                   double px, double p_y, double pz, double d1, double d2, double t_l,
                   double b_J_arPP[5][3]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for J_arPP.h
 *
 * [EOF]
 */
