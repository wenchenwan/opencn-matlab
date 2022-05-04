//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: angles2deg.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 04-May-2022 15:12:00
//

// Include Files
#include "angles2deg.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "coder_array.h"
#include <emmintrin.h>

// Function Definitions
//
// function [ angles_deg ] = angles2deg( angles_rad )
//
// angles2deg : Rad to degree conversion on a vector of angles.
//
//  angles_rad : Vector of angles expressed in rad
//
//  angles_deg : Vector of angles expressed in degree
//
// Arguments    : const ::coder::array<double, 2U> &angles_rad
//                ::coder::array<double, 2U> &angles_deg
// Return Type  : void
//
namespace ocn {
void angles2deg(const ::coder::array<double, 2U> &angles_rad,
                ::coder::array<double, 2U> &angles_deg)
{
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'angles2deg:7' angles_deg = rad2deg( angles_rad );
    angles_deg.set_size(angles_rad.size(0), angles_rad.size(1));
    loop_ub = angles_rad.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        int i1;
        int scalarLB;
        int vectorUB;
        b_loop_ub = angles_rad.size(0);
        scalarLB = (angles_rad.size(0) / 2) << 1;
        vectorUB = scalarLB - 2;
        for (i1 = 0; i1 <= vectorUB; i1 += 2) {
            _mm_storeu_pd(
                &angles_deg[i1 + angles_deg.size(0) * i],
                _mm_mul_pd(_mm_set1_pd(57.295779513082323),
                           _mm_loadu_pd((const double *)&angles_rad[i1 + angles_rad.size(0) * i])));
        }
        for (i1 = scalarLB; i1 < b_loop_ub; i1++) {
            angles_deg[i1 + angles_deg.size(0) * i] =
                57.295779513082323 * angles_rad[i1 + angles_rad.size(0) * i];
        }
    }
}

} // namespace ocn

//
// File trailer for angles2deg.cpp
//
// [EOF]
//
