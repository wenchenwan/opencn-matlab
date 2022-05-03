//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: anglesNormDin.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:31:06
//

// Include Files
#include "anglesNormDin.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "unsafeSxfun.h"
#include "coder_array.h"
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
// function [ angles_deg ] = anglesNormDin( A0_deg, A1_deg, A1_mode, G90 )
//
// anglesNormDin : Compute the given vector of angles expressed in degree
//  ( A1_deg ) based on the Din norm for the angle used by Beckhoff.
//
//  A0_deg    : Vector of angles expressed in degree ( Starting angle )
//  A1_deg    : Vector of angles expressed in degree ( End angle )
//  A1_mode   : Vector mode based on the sign before the value
//  G90       : (boolean) Is the absolute mode enable
//
// Arguments    : const ::coder::array<double, 1U> &A0_deg
//                const ::coder::array<double, 1U> &A1_deg
//                const ::coder::array<int, 1U> &A1_mode
//                bool G90
//                ::coder::array<double, 1U> &angles_deg
// Return Type  : void
//
namespace ocn {
void anglesNormDin(const ::coder::array<double, 1U> &A0_deg,
                   const ::coder::array<double, 1U> &A1_deg, const ::coder::array<int, 1U> &A1_mode,
                   bool G90, ::coder::array<double, 1U> &angles_deg)
{
    ::coder::array<double, 1U> delta_CCW;
    ::coder::array<double, 1U> delta_CW;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'anglesNormDin:11' if( G90 )
    if (G90) {
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int f_loop_ub;
        int i6;
        //  Absolute mode : Recompute the correct angle
        // 'anglesNormDin:12' angles_deg = recompute_angles( A0_deg, A1_deg, A1_mode );
        //  recompute_angles : Recompute the angles bases on the Din norm.
        //        - CW        : CLockwise movement        (wrapped)
        //        - CCW       : Counterclockwise movement (wrapped)
        //        - Shortest  : Shorter distance          (wrapped)
        //  A0_deg    : See headers
        //  A1_deg    : See headers
        //  A1_mode   : See headers
        //
        //  angles_deg : Correct angle to reach
        // 'anglesNormDin:29' MAX_DEGREE = 360;
        //  Maximum value in degree
        // 'anglesNormDin:31' angles_deg      = A0_deg;
        angles_deg.set_size(A0_deg.size(0));
        b_loop_ub = A0_deg.size(0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            angles_deg[i1] = A0_deg[i1];
        }
        //  Store actual angles
        // 'anglesNormDin:32' A0_deg_wrapped  = mod( A0_deg, MAX_DEGREE );
        //  Wrapped angle
        // 'anglesNormDin:33' A1_deg_wrapped  = mod( A1_deg, MAX_DEGREE );
        //  Wrapped angle
        //  Compute different distances
        // 'anglesNormDin:36' [ delta_CW, delta_CCW ] = computeDeltaDegree( A0_deg_wrapped, ...
        // 'anglesNormDin:37'                                        A1_deg_wrapped, MAX_DEGREE );
        //  computeDeltaDegree : Compute the distance [ 0 , 360 ] between the angles.
        // 'anglesNormDin:61' delta_CW     = mod( A1 - A0, MAX_DEGREE );
        r.set_size(A1_deg.size(0));
        c_loop_ub = A1_deg.size(0);
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            double varargin_1;
            double varargout_1;
            varargin_1 = A1_deg[i2];
            if (varargin_1 == 0.0) {
                varargout_1 = 0.0;
            } else {
                varargout_1 = std::fmod(varargin_1, 360.0);
                if (varargout_1 == 0.0) {
                    varargout_1 = 0.0;
                } else if (varargin_1 < 0.0) {
                    varargout_1 += 360.0;
                }
            }
            r[i2] = varargout_1;
        }
        r1.set_size(A0_deg.size(0));
        d_loop_ub = A0_deg.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            double b_varargin_1;
            double b_varargout_1;
            b_varargin_1 = A0_deg[i3];
            if (b_varargin_1 == 0.0) {
                b_varargout_1 = 0.0;
            } else {
                b_varargout_1 = std::fmod(b_varargin_1, 360.0);
                if (b_varargout_1 == 0.0) {
                    b_varargout_1 = 0.0;
                } else if (b_varargin_1 < 0.0) {
                    b_varargout_1 += 360.0;
                }
            }
            r1[i3] = b_varargout_1;
        }
        if (r.size(0) == r1.size(0)) {
            int e_loop_ub;
            delta_CW.set_size(r.size(0));
            e_loop_ub = r.size(0);
            for (int i4{0}; i4 < e_loop_ub; i4++) {
                double c_varargin_1;
                double c_varargout_1;
                c_varargin_1 = r[i4] - r1[i4];
                if (c_varargin_1 == 0.0) {
                    c_varargout_1 = 0.0;
                } else {
                    c_varargout_1 = std::fmod(c_varargin_1, 360.0);
                    if (c_varargout_1 == 0.0) {
                        c_varargout_1 = 0.0;
                    } else if (c_varargin_1 < 0.0) {
                        c_varargout_1 += 360.0;
                    }
                }
                delta_CW[i4] = c_varargout_1;
            }
        } else {
            binary_expand_op(delta_CW, r, r1);
        }
        // 'anglesNormDin:62' delta_CCW    = MAX_DEGREE - delta_CW;
        delta_CCW.set_size(delta_CW.size(0));
        f_loop_ub = delta_CW.size(0);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            delta_CCW[i5] = 360.0 - delta_CW[i5];
        }
        // 'anglesNormDin:39' N = length( A1_mode );
        // 'anglesNormDin:41' for j = 1 : N
        i6 = A1_mode.size(0);
        for (int j{0}; j < i6; j++) {
            //  Loop over the vector elements
            // 'anglesNormDin:42' switch( A1_mode( j ) )
            switch (A1_mode[j]) {
            case AngleMode_CW:
                // 'anglesNormDin:43' case ( AngleMode.CW )
                //  Clockwise mode
                // 'anglesNormDin:44' angles_deg( j ) = angles_deg( j ) + delta_CW( j );
                angles_deg[j] = angles_deg[j] + delta_CW[j];
                break;
            case AngleMode_CCW:
                // 'anglesNormDin:45' case ( AngleMode.CCW )
                //  Counterlockwise mode
                // 'anglesNormDin:46' angles_deg( j ) = angles_deg( j ) - delta_CCW( j );
                angles_deg[j] = angles_deg[j] - delta_CCW[j];
                break;
            case AngleMode_Closest: {
                double delta;
                // 'anglesNormDin:47' case ( AngleMode.Closest )
                //  Shortest distance mode
                // 'anglesNormDin:48' if( delta_CCW( j ) < delta_CW( j ) )
                if (delta_CCW[j] < delta_CW[j]) {
                    // 'anglesNormDin:49' delta = -delta_CCW( j );
                    delta = -delta_CCW[j];
                } else {
                    // 'anglesNormDin:50' else
                    // 'anglesNormDin:51' delta = delta_CW( j );
                    delta = delta_CW[j];
                }
                // 'anglesNormDin:53' angles_deg( j ) = angles_deg( j ) + delta;
                angles_deg[j] = angles_deg[j] + delta;
            } break;
            }
        }
    } else {
        int loop_ub;
        // 'anglesNormDin:13' else
        //  Incremental   : The angle is already correct
        // 'anglesNormDin:14' angles_deg = A1_deg;
        angles_deg.set_size(A1_deg.size(0));
        loop_ub = A1_deg.size(0);
        for (int i{0}; i < loop_ub; i++) {
            angles_deg[i] = A1_deg[i];
        }
    }
}

} // namespace ocn

//
// File trailer for anglesNormDin.cpp
//
// [EOF]
//
