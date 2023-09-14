//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: angles2deg.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 14-Sep-2023 12:49:58
//

// Include Files
#include "angles2deg.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include <emmintrin.h>

// Function Definitions
//
// function [ angles ] = angles2deg( angles )
//
// angles2deg : Rad to degree conversion on a vector of angles.
//
//  Inputs :
//  angles : Vector of angles expressed in rad
//
//  Outputs:
//  angles : Vector of angles expressed in degree
//
// Arguments    : double angles[3]
// Return Type  : void
//
namespace ocn {
void angles2deg(double angles[3])
{
    __m128d r;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'angles2deg:9' angles = rad2deg( angles );
    r = _mm_loadu_pd(&angles[0]);
    _mm_storeu_pd(&angles[0], _mm_mul_pd(_mm_set1_pd(57.295779513082323), r));
    angles[2] *= 57.295779513082323;
}

} // namespace ocn

//
// File trailer for angles2deg.cpp
//
// [EOF]
//
