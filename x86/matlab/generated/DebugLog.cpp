//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: DebugLog.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-Feb-2022 12:47:09
//

// Include Files
#include "DebugLog.h"
#include "sinspace_data.h"
#include <stdio.h>

// Function Definitions
//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : int varargin_2
//                double varargin_3
//                double varargin_4
//                double varargin_5
//                double varargin_6
//                double varargin_7
//                double varargin_8
//                double varargin_9
// Return Type  : void
//
namespace ocn {
void DebugLog(int varargin_2, double varargin_3, double varargin_4, double varargin_5,
              double varargin_6, double varargin_7, double varargin_8, double varargin_9)
{
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        printf("BuildConstr_v4 with Ncrv = %d, amax = [%f, %f, %f], v_0 = %f, at_0 = %f, v_1 = %f, "
               "at_1 = %f\n",
               varargin_2, varargin_3, varargin_4, varargin_5, varargin_6, varargin_7, varargin_8,
               varargin_9);
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : double varargin_2
// Return Type  : void
//
void DebugLog(double varargin_2)
{
    if ((static_cast<unsigned long>(DebugConfig) & 4UL) != 0UL) {
        printf("v_0  = %f\n", varargin_2);
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : double varargin_2
//                double varargin_3
//                double varargin_4
// Return Type  : void
//
void DebugLog(double varargin_2, double varargin_3, double varargin_4)
{
    if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
        printf("WARNING: (Jerk) Increasing jmax to [%f,%f,%f]\n", varargin_2, varargin_3,
               varargin_4);
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : int varargin_2
// Return Type  : void
//
void DebugLog(int varargin_2)
{
    if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
        printf("ZeroStart at k = %d failed, halving jerk\n", varargin_2);
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : int varargin_2
//                int varargin_3
// Return Type  : void
//
void DebugLog(int varargin_2, int varargin_3)
{
    if ((static_cast<unsigned long>(DebugConfig) & 32UL) != 0UL) {
        printf("Lines: %d, %d\n\n", varargin_2, varargin_3);
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 32UL) != 0UL) {
        printf("========== CalcTransition ==========\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void ab_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        printf("\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : double varargin_2
// Return Type  : void
//
void b_DebugLog(double varargin_2)
{
    if ((static_cast<unsigned long>(DebugConfig) & 4UL) != 0UL) {
        printf("at_0 = %f\n", varargin_2);
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : int varargin_2
// Return Type  : void
//
void b_DebugLog(int varargin_2)
{
    if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
        printf("ZeroEnd at k = %d failed, halving jerk\n", varargin_2);
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void b_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 32UL) != 0UL) {
        printf("=========== Badly Cond. Matrix in G2_Hermite() ==========\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : int varargin_2
//                int varargin_3
// Return Type  : void
//
void b_DebugLog(int varargin_2, int varargin_3)
{
    if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
        printf("Lines: %d, %d\n\n", varargin_2, varargin_3);
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void bb_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        printf("Coeff3 = ");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : double varargin_2
// Return Type  : void
//
void c_DebugLog(double varargin_2)
{
    if ((static_cast<unsigned long>(DebugConfig) & 4UL) != 0UL) {
        printf("v_1  = %f\n", varargin_2);
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void c_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
        printf("========== CalcTransition ==========\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void cb_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        printf("OPTIMIZATION FAILED!\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void d_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
        printf("=========== status = 6 ==========\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : double varargin_2
// Return Type  : void
//
void d_DebugLog(double varargin_2)
{
    if ((static_cast<unsigned long>(DebugConfig) & 4UL) != 0UL) {
        printf("at_1 = %f\n", varargin_2);
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void db_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        printf("FEEDOPT: WRONG STATE\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void e_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 32UL) != 0UL) {
        printf("=========== No Solution ==========\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : double varargin_2
// Return Type  : void
//
void e_DebugLog(double varargin_2)
{
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        printf("%.4f ", varargin_2);
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void f_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
        printf("Reading G-code...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void g_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
        printf("Reading G-code...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void h_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 16UL) != 0UL) {
        printf("ERROR: Optimization failed, Gcode queue is empty\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void i_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
        printf("Checking for cusps...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void j_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
        printf("Checking for cusps...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void k_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 1UL) != 0UL) {
        printf("Expanding ...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void l_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
        printf("Compressing...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void m_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
        printf("Compressing...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void n_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
        printf("Smoothing...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void o_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
        printf("Smoothing...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void p_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
        printf("Splitting...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void q_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 2UL) != 0UL) {
        printf("Splitting...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void r_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
        printf("Feedrate Planning...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void s_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 128UL) != 0UL) {
        printf("Queue empty...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void t_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        printf("FEEDRATE PLANNING...\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void u_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        printf("-----------------------------------\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void v_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        printf("================================================\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void w_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 4UL) != 0UL) {
        printf("===============================\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void x_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 4UL) != 0UL) {
        printf("====== FEEDRATE PLANNING ======\n");
        fflush(stdout);
    }
}

//
// 1 -> stdout
//  2 -> stderr
//
// Arguments    : void
// Return Type  : void
//
void y_DebugLog()
{
    if ((static_cast<unsigned long>(DebugConfig) & 8UL) != 0UL) {
        printf("Coeff1 = ");
        fflush(stdout);
    }
}

} // namespace ocn

//
// File trailer for DebugLog.cpp
//
// [EOF]
//
