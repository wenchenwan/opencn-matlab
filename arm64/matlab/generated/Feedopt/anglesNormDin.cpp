//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: anglesNormDin.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:07:56
//

// Include Files
#include "anglesNormDin.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include <cmath>

// Type Definitions
namespace ocn {
enum AngleMode : int
{
    AngleMode_CW = 0, // Default value
    AngleMode_CCW,
    AngleMode_Closest
};

}

// Function Definitions
//
// function [ A_din ] = anglesNormDin( A_prev, A, A_mode, G90 )
//
// anglesNormDin : Compute the given vector of angles expressed in degree
//  ( A_prev ) based on the Din norm for the angle used by Beckhoff.
//
//  A_prev    : Vector of angles expressed in degree ( Starting angle )
//  A         : Vector of angles expressed in degree ( End angle )
//  A_mode    : Vector mode based on the sign before the value
//  G90       : (boolean) Is the absolute mode enable
//
// Arguments    : double A_prev
//                double A
//                int A_mode
//                bool G90
// Return Type  : double
//
namespace ocn {
double anglesNormDin(double A_prev, double A, int A_mode, bool G90)
{
    double A_din;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'anglesNormDin:11' if( G90 )
    if (G90) {
        double A_prev_wrapped;
        double A_wrapped;
        double delta_CW;
        double x;
        //  Absolute mode : Recompute the correct angle
        // 'anglesNormDin:12' A_din = recompute_angles( A_prev, A, A_mode );
        //  recompute_angles : Recompute the angles bases on the Din norm.
        //        - CW        : CLockwise movement        (wrapped)
        //        - CCW       : Counterclockwise movement (wrapped)
        //        - Shortest  : Shorter distance          (wrapped)
        //
        //  A_din : Corrected angle
        // 'anglesNormDin:26' MAX_DEGREE = 360;
        //  Maximum value in degree
        // 'anglesNormDin:28' A_din           = A_prev;
        A_din = A_prev;
        //  Store actual angles
        // 'anglesNormDin:29' A_prev_wrapped  = mod( A_prev, MAX_DEGREE );
        if (A_prev == 0.0) {
            A_prev_wrapped = 0.0;
        } else {
            A_prev_wrapped = std::fmod(A_prev, 360.0);
            if (A_prev_wrapped == 0.0) {
                A_prev_wrapped = 0.0;
            } else if (A_prev < 0.0) {
                A_prev_wrapped += 360.0;
            }
        }
        //  Wrapped angle
        // 'anglesNormDin:30' A_wrapped       = mod( A, MAX_DEGREE );
        if (A == 0.0) {
            A_wrapped = 0.0;
        } else {
            A_wrapped = std::fmod(A, 360.0);
            if (A_wrapped == 0.0) {
                A_wrapped = 0.0;
            } else if (A < 0.0) {
                A_wrapped += 360.0;
            }
        }
        //  Wrapped angle
        //  Compute different distances
        // 'anglesNormDin:33' [ delta_CW, delta_CCW ] = computeDeltaDegree( A_prev_wrapped, ...
        // 'anglesNormDin:34'                                               A_wrapped, MAX_DEGREE );
        //  computeDeltaDegree : Compute the distance [ 0 , 360 ] between the angles.
        // 'anglesNormDin:54' delta_CW     = mod( A - A_prev, MAX_DEGREE );
        x = A_wrapped - A_prev_wrapped;
        if (x == 0.0) {
            delta_CW = 0.0;
        } else {
            delta_CW = std::fmod(x, 360.0);
            if (delta_CW == 0.0) {
                delta_CW = 0.0;
            } else if (x < 0.0) {
                delta_CW += 360.0;
            }
        }
        // 'anglesNormDin:55' delta_CCW    = MAX_DEGREE - delta_CW;
        // 'anglesNormDin:36' switch( A_mode )
        switch (A_mode) {
        case AngleMode_CW:
            // 'anglesNormDin:37' case ( AngleMode.CW )
            //  Clockwise mode
            // 'anglesNormDin:38' A_din = A_din + delta_CW;
            A_din = A_prev + delta_CW;
            break;
        case AngleMode_CCW:
            // 'anglesNormDin:39' case ( AngleMode.CCW )
            //  Counterlockwise mode
            // 'anglesNormDin:40' A_din = A_din - delta_CCW;
            A_din = A_prev - (360.0 - delta_CW);
            break;
        case AngleMode_Closest: {
            double delta;
            // 'anglesNormDin:41' case ( AngleMode.Closest )
            //  Shortest distance mode
            // 'anglesNormDin:42' if( delta_CCW < delta_CW )
            if (360.0 - delta_CW < delta_CW) {
                // 'anglesNormDin:43' delta = -delta_CCW;
                delta = -(360.0 - delta_CW);
            } else {
                // 'anglesNormDin:44' else
                // 'anglesNormDin:45' delta = delta_CW;
                delta = delta_CW;
            }
            // 'anglesNormDin:47' A_din = A_din + delta;
            A_din = A_prev + delta;
        } break;
        }
    } else {
        // 'anglesNormDin:13' else
        //  Incremental   : The angle is already correct
        // 'anglesNormDin:14' A_din = A;
        A_din = A;
    }
    return A_din;
}

} // namespace ocn

//
// File trailer for anglesNormDin.cpp
//
// [EOF]
//
