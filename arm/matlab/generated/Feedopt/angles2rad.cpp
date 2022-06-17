//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: angles2rad.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 17-Jun-2022 15:45:22
//

// Include Files
#include "angles2rad.h"
#include "opencn_matlab_data.h"
#include "opencn_matlab_initialize.h"

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
    if (!isInitialized_opencn_matlab) {
        opencn_matlab_initialize();
    }
    // 'angles2rad:9' angles = deg2rad( angles );
    angles[0] *= 0.017453292519943295;
    angles[1] *= 0.017453292519943295;
    angles[2] *= 0.017453292519943295;
}

} // namespace ocn

//
// File trailer for angles2rad.cpp
//
// [EOF]
//
