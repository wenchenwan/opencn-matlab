//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: angles2rad.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 05-May-2022 09:00:19
//

// Include Files
#include "angles2rad.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include <emmintrin.h>

// Function Definitions
//
// function [ angles ] = angles2rad( angles )
//
// angles2deg : Rad to degree conversion on a vector of angles.
//
//  Inputs :
//  angles : Vector of angles expressed in degree
//
//  Outputs:
//  angles : Vector of angles expressed in rad
//
// Arguments    : double angles[3]
// Return Type  : void
//
namespace ocn {
void angles2rad(double angles[3])
{
    __m128d r;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'angles2rad:9' angles = deg2rad( angles );
    r = _mm_loadu_pd(&angles[0]);
    _mm_storeu_pd(&angles[0], _mm_mul_pd(_mm_set1_pd(0.017453292519943295), r));
    angles[2] *= 0.017453292519943295;
}

} // namespace ocn

//
// File trailer for angles2rad.cpp
//
// [EOF]
//
