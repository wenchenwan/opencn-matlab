//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: anglesNormDin.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-May-2022 15:12:49
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

// Function Declarations
namespace ocn {
static void lt(::coder::array<bool, 1U> &x, const ::coder::array<double, 1U> &delta_CCW,
               const ::coder::array<double, 1U> &delta);

static void minus(::coder::array<double, 1U> &A_din, const ::coder::array<double, 1U> &A_prev,
                  const ::coder::array<double, 1U> &delta_CCW);

static void plus(::coder::array<double, 1U> &A_din, const ::coder::array<double, 1U> &A_prev,
                 const ::coder::array<double, 1U> &delta);

} // namespace ocn

// Function Definitions
//
// Arguments    : ::coder::array<bool, 1U> &x
//                const ::coder::array<double, 1U> &delta_CCW
//                const ::coder::array<double, 1U> &delta
// Return Type  : void
//
namespace ocn {
static void lt(::coder::array<bool, 1U> &x, const ::coder::array<double, 1U> &delta_CCW,
               const ::coder::array<double, 1U> &delta)
{
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (delta.size(0) == 1) {
        i = delta_CCW.size(0);
    } else {
        i = delta.size(0);
    }
    x.set_size(i);
    stride_0_0 = (delta_CCW.size(0) != 1);
    stride_1_0 = (delta.size(0) != 1);
    if (delta.size(0) == 1) {
        loop_ub = delta_CCW.size(0);
    } else {
        loop_ub = delta.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        x[i1] = (delta_CCW[i1 * stride_0_0] < delta[i1 * stride_1_0]);
    }
}

//
// Arguments    : ::coder::array<double, 1U> &A_din
//                const ::coder::array<double, 1U> &A_prev
//                const ::coder::array<double, 1U> &delta_CCW
// Return Type  : void
//
static void minus(::coder::array<double, 1U> &A_din, const ::coder::array<double, 1U> &A_prev,
                  const ::coder::array<double, 1U> &delta_CCW)
{
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (delta_CCW.size(0) == 1) {
        i = A_prev.size(0);
    } else {
        i = delta_CCW.size(0);
    }
    A_din.set_size(i);
    stride_0_0 = (A_prev.size(0) != 1);
    stride_1_0 = (delta_CCW.size(0) != 1);
    if (delta_CCW.size(0) == 1) {
        loop_ub = A_prev.size(0);
    } else {
        loop_ub = delta_CCW.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        A_din[i1] = A_prev[i1 * stride_0_0] - delta_CCW[i1 * stride_1_0];
    }
}

//
// Arguments    : ::coder::array<double, 1U> &A_din
//                const ::coder::array<double, 1U> &A_prev
//                const ::coder::array<double, 1U> &delta
// Return Type  : void
//
static void plus(::coder::array<double, 1U> &A_din, const ::coder::array<double, 1U> &A_prev,
                 const ::coder::array<double, 1U> &delta)
{
    int i;
    int loop_ub;
    int stride_0_0;
    int stride_1_0;
    if (delta.size(0) == 1) {
        i = A_prev.size(0);
    } else {
        i = delta.size(0);
    }
    A_din.set_size(i);
    stride_0_0 = (A_prev.size(0) != 1);
    stride_1_0 = (delta.size(0) != 1);
    if (delta.size(0) == 1) {
        loop_ub = A_prev.size(0);
    } else {
        loop_ub = delta.size(0);
    }
    for (int i1{0}; i1 < loop_ub; i1++) {
        A_din[i1] = A_prev[i1 * stride_0_0] + delta[i1 * stride_1_0];
    }
}

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
// Arguments    : const ::coder::array<double, 1U> &A_prev
//                const ::coder::array<double, 1U> &A
//                const ::coder::array<int, 1U> &A_mode
//                bool G90
//                ::coder::array<double, 1U> &A_din
// Return Type  : void
//
void anglesNormDin(const ::coder::array<double, 1U> &A_prev, const ::coder::array<double, 1U> &A,
                   const ::coder::array<int, 1U> &A_mode, bool G90,
                   ::coder::array<double, 1U> &A_din)
{
    ::coder::array<double, 1U> delta;
    ::coder::array<double, 1U> delta_CCW;
    ::coder::array<double, 1U> r;
    ::coder::array<double, 1U> r1;
    ::coder::array<bool, 1U> x;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'anglesNormDin:11' if( G90 )
    if (G90) {
        int b_index;
        int b_loop_ub;
        int c_loop_ub;
        int d_loop_ub;
        int f_loop_ub;
        int g_loop_ub;
        bool exitg1;
        bool y;
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
        A_din.set_size(A_prev.size(0));
        b_loop_ub = A_prev.size(0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            A_din[i1] = A_prev[i1];
        }
        //  Store actual angles
        // 'anglesNormDin:29' A_prev_wrapped  = mod( A_prev, MAX_DEGREE );
        //  Wrapped angle
        // 'anglesNormDin:30' A_wrapped       = mod( A, MAX_DEGREE );
        //  Wrapped angle
        //  Compute different distances
        // 'anglesNormDin:33' [ delta_CW, delta_CCW ] = computeDeltaDegree( A_prev_wrapped, ...
        // 'anglesNormDin:34'                                               A_wrapped, MAX_DEGREE );
        //  computeDeltaDegree : Compute the distance [ 0 , 360 ] between the angles.
        // 'anglesNormDin:54' delta_CW     = mod( A - A_prev, MAX_DEGREE );
        r.set_size(A.size(0));
        c_loop_ub = A.size(0);
        for (int i2{0}; i2 < c_loop_ub; i2++) {
            double varargin_1;
            double varargout_1;
            varargin_1 = A[i2];
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
        r1.set_size(A_prev.size(0));
        d_loop_ub = A_prev.size(0);
        for (int i3{0}; i3 < d_loop_ub; i3++) {
            double b_varargin_1;
            double b_varargout_1;
            b_varargin_1 = A_prev[i3];
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
            delta.set_size(r.size(0));
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
                delta[i4] = c_varargout_1;
            }
        } else {
            binary_expand_op(delta, r, r1);
        }
        // 'anglesNormDin:55' delta_CCW    = MAX_DEGREE - delta_CW;
        delta_CCW.set_size(delta.size(0));
        f_loop_ub = delta.size(0);
        for (int i5{0}; i5 < f_loop_ub; i5++) {
            delta_CCW[i5] = 360.0 - delta[i5];
        }
        // 'anglesNormDin:36' switch( A_mode )
        x.set_size(A_mode.size(0));
        g_loop_ub = A_mode.size(0);
        for (int i6{0}; i6 < g_loop_ub; i6++) {
            x[i6] = (static_cast<int>(AngleMode_CW) == A_mode[i6]);
        }
        y = (x.size(0) != 0);
        if (y) {
            int k;
            k = 0;
            exitg1 = false;
            while ((!exitg1) && (k <= x.size(0) - 1)) {
                if (!x[k]) {
                    y = false;
                    exitg1 = true;
                } else {
                    k++;
                }
            }
        }
        if (y) {
            b_index = 0;
        } else {
            int h_loop_ub;
            bool b_y;
            x.set_size(A_mode.size(0));
            h_loop_ub = A_mode.size(0);
            for (int i7{0}; i7 < h_loop_ub; i7++) {
                x[i7] = (static_cast<int>(AngleMode_CCW) == A_mode[i7]);
            }
            b_y = (x.size(0) != 0);
            if (b_y) {
                int b_k;
                b_k = 0;
                exitg1 = false;
                while ((!exitg1) && (b_k <= x.size(0) - 1)) {
                    if (!x[b_k]) {
                        b_y = false;
                        exitg1 = true;
                    } else {
                        b_k++;
                    }
                }
            }
            if (b_y) {
                b_index = 1;
            } else {
                int l_loop_ub;
                bool d_y;
                x.set_size(A_mode.size(0));
                l_loop_ub = A_mode.size(0);
                for (int i11{0}; i11 < l_loop_ub; i11++) {
                    x[i11] = (static_cast<int>(AngleMode_Closest) == A_mode[i11]);
                }
                d_y = (x.size(0) != 0);
                if (d_y) {
                    int d_k;
                    d_k = 0;
                    exitg1 = false;
                    while ((!exitg1) && (d_k <= x.size(0) - 1)) {
                        if (!x[d_k]) {
                            d_y = false;
                            exitg1 = true;
                        } else {
                            d_k++;
                        }
                    }
                }
                if (d_y) {
                    b_index = 2;
                } else {
                    b_index = -1;
                }
            }
        }
        switch (b_index) {
        case 0: {
            // 'anglesNormDin:37' case ( AngleMode.CW )
            //  Clockwise mode
            // 'anglesNormDin:38' A_din = A_din + delta_CW;
            if (A_prev.size(0) == delta.size(0)) {
                int i_loop_ub;
                A_din.set_size(A_prev.size(0));
                i_loop_ub = A_prev.size(0);
                for (int i8{0}; i8 < i_loop_ub; i8++) {
                    A_din[i8] = A_prev[i8] + delta[i8];
                }
            } else {
                plus(A_din, A_prev, delta);
            }
        } break;
        case 1: {
            // 'anglesNormDin:39' case ( AngleMode.CCW )
            //  Counterlockwise mode
            // 'anglesNormDin:40' A_din = A_din - delta_CCW;
            if (A_prev.size(0) == delta_CCW.size(0)) {
                int j_loop_ub;
                A_din.set_size(A_prev.size(0));
                j_loop_ub = A_prev.size(0);
                for (int i9{0}; i9 < j_loop_ub; i9++) {
                    A_din[i9] = A_prev[i9] - delta_CCW[i9];
                }
            } else {
                minus(A_din, A_prev, delta_CCW);
            }
        } break;
        case 2: {
            bool c_y;
            // 'anglesNormDin:41' case ( AngleMode.Closest )
            //  Shortest distance mode
            // 'anglesNormDin:42' if( delta_CCW < delta_CW )
            if (delta_CCW.size(0) == delta.size(0)) {
                int k_loop_ub;
                x.set_size(delta_CCW.size(0));
                k_loop_ub = delta_CCW.size(0);
                for (int i10{0}; i10 < k_loop_ub; i10++) {
                    x[i10] = (delta_CCW[i10] < delta[i10]);
                }
            } else {
                lt(x, delta_CCW, delta);
            }
            c_y = (x.size(0) != 0);
            if (c_y) {
                int c_k;
                c_k = 0;
                exitg1 = false;
                while ((!exitg1) && (c_k <= x.size(0) - 1)) {
                    if (!x[c_k]) {
                        c_y = false;
                        exitg1 = true;
                    } else {
                        c_k++;
                    }
                }
            }
            if (c_y) {
                int m_loop_ub;
                // 'anglesNormDin:43' delta = -delta_CCW;
                delta.set_size(delta_CCW.size(0));
                m_loop_ub = delta_CCW.size(0);
                for (int i12{0}; i12 < m_loop_ub; i12++) {
                    delta[i12] = -delta_CCW[i12];
                }
            } else {
                // 'anglesNormDin:44' else
                // 'anglesNormDin:45' delta = delta_CW;
            }
            // 'anglesNormDin:47' A_din = A_din + delta;
            if (A_prev.size(0) == delta.size(0)) {
                int n_loop_ub;
                A_din.set_size(A_prev.size(0));
                n_loop_ub = A_prev.size(0);
                for (int i13{0}; i13 < n_loop_ub; i13++) {
                    A_din[i13] = A_prev[i13] + delta[i13];
                }
            } else {
                plus(A_din, A_prev, delta);
            }
        } break;
        }
    } else {
        int loop_ub;
        // 'anglesNormDin:13' else
        //  Incremental   : The angle is already correct
        // 'anglesNormDin:14' A_din = A;
        A_din.set_size(A.size(0));
        loop_ub = A.size(0);
        for (int i{0}; i < loop_ub; i++) {
            A_din[i] = A[i];
        }
    }
}

} // namespace ocn

//
// File trailer for anglesNormDin.cpp
//
// [EOF]
//
