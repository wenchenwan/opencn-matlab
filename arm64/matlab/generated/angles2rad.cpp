//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: angles2rad.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 03-May-2022 09:04:53
//

// Include Files
#include "angles2rad.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"
#include "coder_array.h"

// Function Definitions
//
// function [ angles_rad ] = angles2rad( angles_deg )
//
// angles2rad : Degree to rad conversion on a vector of angles.
//
//  angles_deg : Vector of angles expressed in degree
//
//  angles_rad : Vector of angles expressed in rad
//
// Arguments    : const ::coder::array<double, 2U> &angles_deg
//                ::coder::array<double, 2U> &angles_rad
// Return Type  : void
//
namespace ocn {
void angles2rad(const ::coder::array<double, 2U> &angles_deg,
                ::coder::array<double, 2U> &angles_rad)
{
    int loop_ub;
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'angles2rad:7' angles_rad = deg2rad( angles_deg );
    angles_rad.set_size(angles_deg.size(0), angles_deg.size(1));
    loop_ub = angles_deg.size(1);
    for (int i{0}; i < loop_ub; i++) {
        int b_loop_ub;
        b_loop_ub = angles_deg.size(0);
        for (int i1{0}; i1 < b_loop_ub; i1++) {
            angles_rad[i1 + angles_rad.size(0) * i] =
                0.017453292519943295 * angles_deg[i1 + angles_deg.size(0) * i];
        }
    }
}

} // namespace ocn

//
// File trailer for angles2rad.cpp
//
// [EOF]
//
