//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: EvalLine.cpp
//
// MATLAB Coder version            : 5.3
// C/C++ source code generated on  : 10-Jun-2022 11:30:18
//

// Include Files
#include "EvalLine.h"
#include "coder_array.h"
#include "common/tracy/Tracy.hpp"
#include <cstring>

// Function Definitions
//
// function [r0D, r1D, r2D, r3D] = EvalLine( CurvStruct, u_vec, ind )
//
// EvalLine :
//
//  Input
//  CurvStruct    : struct : Line segment
//  u_vec         :    1xn : Vector for evaluation of the curv
//  ind           :        : Vector of indices
//
//  Output
//  r0D           :   nDxn : Evaluation of the line at u\_vec points
//  r1D           :   nDxn : 1rst order parametric derivative for the line at u\_vec points
//  r2D           :   nDxn : 2nd order parametric derivative for the line at u\_vec points
//  r3D           :   nDxn : 3rd order parametric derivative for the line at u\_vec points
//
// Arguments    : const double CurvStruct_R0[6]
//                const double CurvStruct_R1[6]
//                const ::coder::array<double, 2U> &u_vec
//                const int ind_data[]
//                int ind_size
//                ::coder::array<double, 2U> &r0D
//                ::coder::array<double, 2U> &r1D
//                ::coder::array<double, 2U> &r2D
//                ::coder::array<double, 2U> &r3D
// Return Type  : void
//
namespace ocn {
void EvalLine(const double CurvStruct_R0[6], const double CurvStruct_R1[6],
              const ::coder::array<double, 2U> &u_vec, const int ind_data[], int ind_size,
              ::coder::array<double, 2U> &r0D, ::coder::array<double, 2U> &r1D,
              ::coder::array<double, 2U> &r2D, ::coder::array<double, 2U> &r3D)
{
    ::coder::array<double, 2U> b;
    ::coder::array<double, 1U> a;
    double P0_data[6];
    double P1_data[6];
    int b_loop_ub;
    int d_loop_ub;
    int e_loop_ub;
    int loop_ub;
    // 'EvalLine:16' if ~coder.target('MATLAB')
    // 'EvalLine:17' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalLine:18' coder.inline('never')
    // 'EvalLine:19' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalLine"'));
    ZoneScopedN("EvalLine");
    //
    //  parametrization of a straight line between P0 and P1
    // 'EvalLine:23' P0  = CurvStruct.R0( ind );
    for (int i{0}; i < ind_size; i++) {
        P0_data[i] = CurvStruct_R0[ind_data[i] - 1];
    }
    // 'EvalLine:24' P1  = CurvStruct.R1( ind );
    for (int i1{0}; i1 < ind_size; i1++) {
        P1_data[i1] = CurvStruct_R1[ind_data[i1] - 1];
    }
    //  Calculate the numbre of dimension
    // 'EvalLine:26' nD = length( ind );
    //
    // 'EvalLine:28' r0D = P1.*u_vec + P0.*(1-u_vec);
    r0D.set_size(ind_size, u_vec.size(1));
    loop_ub = u_vec.size(1);
    for (int i2{0}; i2 < loop_ub; i2++) {
        for (int i3{0}; i3 < ind_size; i3++) {
            double d;
            d = u_vec[i2];
            r0D[i3 + r0D.size(0) * i2] = P1_data[i3] * d + P0_data[i3] * (1.0 - d);
        }
    }
    //
    // 'EvalLine:30' N   = length( u_vec );
    // 'EvalLine:31' r1D = repmat( P1 - P0, 1, N );
    a.set_size(ind_size);
    for (int i4{0}; i4 < ind_size; i4++) {
        a[i4] = P1_data[i4] - P0_data[i4];
    }
    b.set_size(a.size(0), u_vec.size(1));
    if ((a.size(0) != 0) && (u_vec.size(1) != 0)) {
        int i5;
        i5 = u_vec.size(1) - 1;
        for (int t{0}; t <= i5; t++) {
            int na;
            na = a.size(0);
            for (int k{0}; k < na; k++) {
                b[k + b.size(0) * t] = a[k];
            }
        }
    }
    r1D.set_size(b.size(0), b.size(1));
    b_loop_ub = b.size(1);
    for (int i6{0}; i6 < b_loop_ub; i6++) {
        int c_loop_ub;
        c_loop_ub = b.size(0);
        for (int i7{0}; i7 < c_loop_ub; i7++) {
            r1D[i7 + r1D.size(0) * i6] = b[i7 + b.size(0) * i6];
        }
    }
    //
    // 'EvalLine:33' r2D = zeros(nD, N);
    r2D.set_size(ind_size, u_vec.size(1));
    d_loop_ub = u_vec.size(1);
    for (int i8{0}; i8 < d_loop_ub; i8++) {
        for (int i9{0}; i9 < ind_size; i9++) {
            r2D[i9 + r2D.size(0) * i8] = 0.0;
        }
    }
    // 'EvalLine:34' r3D = zeros(nD, N);
    r3D.set_size(ind_size, u_vec.size(1));
    e_loop_ub = u_vec.size(1);
    for (int i10{0}; i10 < e_loop_ub; i10++) {
        for (int i11{0}; i11 < ind_size; i11++) {
            r3D[i11 + r3D.size(0) * i10] = 0.0;
        }
    }
}

//
// function [r0D, r1D, r2D, r3D] = EvalLine( CurvStruct, u_vec, ind )
//
// EvalLine :
//
//  Input
//  CurvStruct    : struct : Line segment
//  u_vec         :    1xn : Vector for evaluation of the curv
//  ind           :        : Vector of indices
//
//  Output
//  r0D           :   nDxn : Evaluation of the line at u\_vec points
//  r1D           :   nDxn : 1rst order parametric derivative for the line at u\_vec points
//  r2D           :   nDxn : 2nd order parametric derivative for the line at u\_vec points
//  r3D           :   nDxn : 3rd order parametric derivative for the line at u\_vec points
//
// Arguments    : const double CurvStruct_R0[6]
//                const double CurvStruct_R1[6]
//                double u_vec
//                const int ind_data[]
//                int ind_size
//                double r0D_data[]
//                int *r0D_size
//                double r1D_data[]
//                int *r1D_size
//                double r2D_data[]
//                int *r2D_size
//                double r3D_data[]
//                int *r3D_size
// Return Type  : void
//
void EvalLine(const double CurvStruct_R0[6], const double CurvStruct_R1[6], double u_vec,
              const int ind_data[], int ind_size, double r0D_data[], int *r0D_size,
              double r1D_data[], int *r1D_size, double r2D_data[], int *r2D_size, double r3D_data[],
              int *r3D_size)
{
    ::coder::array<double, 1U> a;
    ::coder::array<double, 1U> b;
    double P0_data[6];
    double P1_data[6];
    int loop_ub;
    // 'EvalLine:16' if ~coder.target('MATLAB')
    // 'EvalLine:17' coder.cinclude('common/tracy/Tracy.hpp');
    // 'EvalLine:18' coder.inline('never')
    // 'EvalLine:19' coder.ceval('ZoneScopedN', coder.opaque('const char*', '"EvalLine"'));
    ZoneScopedN("EvalLine");
    //
    //  parametrization of a straight line between P0 and P1
    // 'EvalLine:23' P0  = CurvStruct.R0( ind );
    for (int i{0}; i < ind_size; i++) {
        P0_data[i] = CurvStruct_R0[ind_data[i] - 1];
    }
    // 'EvalLine:24' P1  = CurvStruct.R1( ind );
    for (int i1{0}; i1 < ind_size; i1++) {
        P1_data[i1] = CurvStruct_R1[ind_data[i1] - 1];
    }
    //  Calculate the numbre of dimension
    // 'EvalLine:26' nD = length( ind );
    //
    // 'EvalLine:28' r0D = P1.*u_vec + P0.*(1-u_vec);
    *r0D_size = ind_size;
    for (int i2{0}; i2 < ind_size; i2++) {
        r0D_data[i2] = P1_data[i2] * u_vec + P0_data[i2] * (1.0 - u_vec);
    }
    //
    // 'EvalLine:30' N   = length( u_vec );
    // 'EvalLine:31' r1D = repmat( P1 - P0, 1, N );
    a.set_size(ind_size);
    for (int i3{0}; i3 < ind_size; i3++) {
        a[i3] = P1_data[i3] - P0_data[i3];
    }
    b.set_size(static_cast<int>(static_cast<signed char>(a.size(0))));
    if (static_cast<signed char>(a.size(0)) != 0) {
        int na;
        na = a.size(0);
        for (int k{0}; k < na; k++) {
            b[k] = a[k];
        }
    }
    *r1D_size = b.size(0);
    loop_ub = b.size(0);
    for (int i4{0}; i4 < loop_ub; i4++) {
        r1D_data[i4] = b[i4];
    }
    //
    // 'EvalLine:33' r2D = zeros(nD, N);
    *r2D_size = ind_size;
    if (0 <= ind_size - 1) {
        std::memset(&r2D_data[0], 0, ind_size * sizeof(double));
    }
    // 'EvalLine:34' r3D = zeros(nD, N);
    *r3D_size = ind_size;
    if (0 <= ind_size - 1) {
        std::memset(&r3D_data[0], 0, ind_size * sizeof(double));
    }
}

} // namespace ocn

//
// File trailer for EvalLine.cpp
//
// [EOF]
//
